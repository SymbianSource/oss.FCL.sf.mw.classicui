/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:  System for managing global popup window priorities
*
*/


#include "aknglobalpopupprioritycontroller.h"
#include "AknPopupFader.h"
#include <eikenv.h>
#include <e32hashtab.h>
#include <coecntrl.h>
#include <eikappui.h>

const TUid KAknGlobalPopupPriorityControllerStaticId = { 0x102835a0 };
const TInt KAknGlobalPopupPriorityControllerMaxStack = 10;

const TInt KControlStackSleepFlags = ECoeStackFlagRefusesAllKeys|ECoeStackFlagRefusesFocus;

enum TGppcPanic
    {
    EGppcPanic_DontSupportMultipleSubPopups,
    EGppcPanic_DontSupportMultipleParents
    };

void GppcPanic(TGppcPanic aReason)
    {
    _LIT(KReason, "AknGppc");
    User::Panic(KReason, aReason);
    }


// hash an identity functions required by RHashMap
template<typename T>
TUint32 GeneralPtrHash(T* const & aPtr)
    {
    return DefaultHash::Integer((TInt)aPtr);
    }

template<typename T>
TBool GeneralPtrIdentity(T* const & aP1, T* const & aP2)
    {
    return aP1 == aP2;
    }


NONSHARABLE_CLASS(CAknGlobalPopupPriorityController) : public CCoeStatic
    {
public:
    static void CreateInstanceL();
    static CAknGlobalPopupPriorityController* Instance();

    void AllowGlobalPopups(TBool aAllow);
    void SetPopupPriorityL(CCoeControl* aPopup, TInt aPriority);
    void RemovePopup(CCoeControl* aPopup);
    void ShowPopup(CCoeControl* aPopup, TBool aShow);
    void SetRootWinOrdinalPosition(TInt aOrdinalPosition);
    void AddSubPopupL(CCoeControl* aPopup, CCoeControl* aSubPopup);
    void AddPopupToControlStackL(CCoeControl* aPopup,TInt aPriority,TInt aStackingFlags);
    void FadeBehindPopupL(CCoeControl* aPopup, MAknFadedComponent* aFadedComponent);
    void RouseSleepingPopup(CCoeControl* aPopup, TBool aRoused);

    TBool GlobalPopupsAllowed();
private:
    CAknGlobalPopupPriorityController();
    ~CAknGlobalPopupPriorityController();
    void ConstructL();

    TInt PopupPriority(CCoeControl* aPopup) const;
    TBool AddToStack(CCoeControl* aPopup);
    TBool RemoveFromStack(CCoeControl* aPopup);
    void SetWindowGroupPriority();
    void SetPopupWindowPositions(CCoeControl* aPopup, TInt aWindowPos);
    void SetPopupChainKeyPositionsL(CCoeControl* aPopup);
    void SetPopupKeyPositionsL(CCoeControl* aPopup);
    CCoeControl* RootPopup(CCoeControl* aTip) const;
    CCoeControl* TopPopup() const;
    TBool PopupIsShown(CCoeControl* aPopup) const;
    void DoFadeBehindPopup(CCoeControl* aPopup);
    TInt MinChainWindowPosition(CCoeControl* aPopup) const;

private:
    struct TPopupInfo
        {
    public:
        TPopupInfo();

    public:
        TInt iPopupPriority;
        TInt iControlStackPriority;
        TInt iControlStackFlags;
        CCoeControl* iSubPopup;     // not owned
        CCoeControl* iParent;       // not owned
        MAknFadedComponent* iFadedComponent;    // not owned
        };

private:
    TPopupInfo* PopupInfo(CCoeControl* aPopup);
    const TPopupInfo* PopupInfo(CCoeControl* aPopup) const;
    TPopupInfo& PopupInfoL(CCoeControl* aPopup);

private:
    RHashMap<CCoeControl*, TPopupInfo> iPopupInfoMap;
    // The stack of currently shown popups (the CCoeControls are not owned)
    RArray<CCoeControl*> iShownStack;
    TBool iGlobalPopupsAllowed;
    TInt iOrdinalPosition;
    CEikAppUi* iAppUi;  // not owned
    };


CAknGlobalPopupPriorityController::TPopupInfo::TPopupInfo()
: iPopupPriority(0), iControlStackPriority(KErrNotFound), iControlStackFlags(0), iSubPopup(NULL), iParent(NULL), iFadedComponent(NULL)
    {
    }


void CAknGlobalPopupPriorityController::CreateInstanceL()
    {
    if (!CAknGlobalPopupPriorityController::Instance())
        {
        CAknGlobalPopupPriorityController* self = new(ELeave) CAknGlobalPopupPriorityController(); // CCoeEnv takes ownership immediately
        self->ConstructL();
        }
    }

CAknGlobalPopupPriorityController* CAknGlobalPopupPriorityController::Instance()
    {
    return static_cast<CAknGlobalPopupPriorityController*>(CCoeEnv::Static(KAknGlobalPopupPriorityControllerStaticId));
    }

void CAknGlobalPopupPriorityController::AllowGlobalPopups(TBool aAllow)
    {
    iGlobalPopupsAllowed = aAllow;
    SetWindowGroupPriority();
    CCoeControl* top = TopPopup();
    if (top)
        {
        TRAP_IGNORE(SetPopupChainKeyPositionsL(top));
        DoFadeBehindPopup(top);
        }
    }

TBool CAknGlobalPopupPriorityController::GlobalPopupsAllowed()
    {
    return iGlobalPopupsAllowed;
    }

void CAknGlobalPopupPriorityController::SetPopupPriorityL(CCoeControl* aPopup, TInt aPriority)
    {
    PopupInfoL(aPopup).iPopupPriority = aPriority;

    // Update the active popup stack
    if (PopupIsShown(aPopup))
        {
        ShowPopup(aPopup, ETrue);
        }
    }

void CAknGlobalPopupPriorityController::RemovePopup(CCoeControl* aPopup)
    {
    // Update the active popup stack
    if (PopupIsShown(aPopup))
        {
        ShowPopup(aPopup, EFalse);
        }

    // Remove sub-popup from parent
    TPopupInfo* info = PopupInfo(aPopup);
    if (info && info->iParent)
        {
        TPopupInfo* pInfo = PopupInfo(info->iParent);
        if (pInfo)
            pInfo->iSubPopup = NULL;
        }

    // Remove the popup and sub popups from the map
    CCoeControl* popup = aPopup;
    while (popup)
        {
        CCoeControl* next = NULL;
        TPopupInfo* info = PopupInfo(popup);
        if (info)
            next = info->iSubPopup;
        iPopupInfoMap.Remove(popup);
        popup = next;
        }
    }

TInt CAknGlobalPopupPriorityController::PopupPriority(CCoeControl* aPopup) const
    {
    const TPopupInfo* info = PopupInfo(aPopup);
    return info ? info->iPopupPriority : 0;
    }

void CAknGlobalPopupPriorityController::ShowPopup(CCoeControl* aPopup, TBool aShow)
    {
    // update the stack
    CCoeControl* oldTop = TopPopup();
    if (aShow)
        {
        AddToStack(aPopup);
        TRAP_IGNORE(SetPopupChainKeyPositionsL(aPopup));
        }
    else
        {
        RemoveFromStack(aPopup);
        }
    DoFadeBehindPopup(aPopup);
    CCoeControl* newTop = TopPopup();

    // update the top popup
    if (oldTop != newTop)
        {
        // set window group priority
        SetWindowGroupPriority();

        // an existing popup is now top
        if (newTop != aPopup)
            {
            TRAP_IGNORE(SetPopupChainKeyPositionsL(newTop));
            DoFadeBehindPopup(newTop);
            }
        }
    }

void CAknGlobalPopupPriorityController::SetRootWinOrdinalPosition(TInt aOrdinalPosition)
    {
    iOrdinalPosition = aOrdinalPosition;
    }

void CAknGlobalPopupPriorityController::SetWindowGroupPriority()
    {
    TInt newPriority;
    if (iShownStack.Count() > 0 && iGlobalPopupsAllowed)
        {
        CCoeControl* topPopup = iShownStack[0];
        TInt priority = PopupPriority(topPopup);
        newPriority = ECoeWinPriorityAlwaysAtFront + priority;
        }
    else
        {
        newPriority = ECoeWinPriorityNeverAtFront;
        }
    CEikonEnv::Static()->RootWin().SetOrdinalPosition(iOrdinalPosition, newPriority);
    }

TBool CAknGlobalPopupPriorityController::AddToStack(CCoeControl* aPopup)
    {
    // remove it from the stack if already there
    TInt priorPos = iShownStack.Find(aPopup);
    if (priorPos != KErrNotFound)
        {
        iShownStack.Remove(priorPos);
        }

    // stack size is limited, do not add new items if it would cause overflow
    TInt count = iShownStack.Count();
    if (count >= KAknGlobalPopupPriorityControllerMaxStack)
        {
        return EFalse;
        }

    // insert it at correct position in the stack
    // also calculate min and max window z-order position
    TInt priority = PopupPriority(aPopup);
    TInt insertPos = -1;
    TInt minWindowPosition = 0;
    TInt maxWindowPosition = KMaxTInt;
    for (TInt ii=0; ii<count; ii++)
        {
        CCoeControl* stacked = iShownStack[ii];
        TInt shownPriority = PopupPriority(stacked);
        if (priority >= shownPriority)
            {
            maxWindowPosition = MinChainWindowPosition(stacked);
            iShownStack.Insert(aPopup, ii); // will not fail because overflow is already checked
            insertPos = ii;
            break;
            }
        minWindowPosition = stacked->DrawableWindow()->OrdinalPosition();
        }
    if (insertPos == -1)
        {
        insertPos = count;
        iShownStack.Append(aPopup); // will not fail because overflow is already checked
        }

    // set popup window z-order position, if necessary
    // it should be behind any higher priority popup and infront
    // of any lower priority popup
    TInt popupWindowPosition = aPopup->DrawableWindow()->OrdinalPosition();
    if (popupWindowPosition < minWindowPosition)
        popupWindowPosition = minWindowPosition+1;
    else if (popupWindowPosition > maxWindowPosition)
        popupWindowPosition = maxWindowPosition;
    SetPopupWindowPositions(aPopup, popupWindowPosition);

    // return true (top changed) if top item was moved or added
    return priorPos == 0 || insertPos == 0;
    }

void CAknGlobalPopupPriorityController::SetPopupWindowPositions(
        CCoeControl* aPopup, TInt aWindowPos)
    {
    TBool isSub = EFalse;
    while (aPopup)
        {
        TInt currentPos = aPopup->DrawableWindow()->OrdinalPosition();
        if (isSub && currentPos < aWindowPos)
            {
            // adjust one forward, so that we don't go behind the parent window
            aWindowPos--;
            }

        aPopup->DrawableWindow()->SetOrdinalPosition(aWindowPos);
        const TPopupInfo* info = PopupInfo(aPopup);
        if (info)
            {
            aPopup = info->iSubPopup;
            }
        else
            {
            aPopup = NULL;
            }
        isSub = ETrue;
        }
    }

void CAknGlobalPopupPriorityController::SetPopupChainKeyPositionsL(CCoeControl* aPopup)
    {
    bool top = aPopup == TopPopup();
    while (aPopup)
        {
        const TPopupInfo* info = PopupInfo(aPopup);
        CCoeControl* next = NULL;
        if (info && info->iControlStackPriority != KErrNotFound)
            {
            next = info->iSubPopup;
            iAppUi->RemoveFromStack(aPopup);
            TInt flags = top ? info->iControlStackFlags : KControlStackSleepFlags;
            iAppUi->AddToStackL(aPopup, info->iControlStackPriority, flags);
            }
        aPopup = next;
        }
    }

void CAknGlobalPopupPriorityController::SetPopupKeyPositionsL(CCoeControl* aPopup)
    {
    bool top = RootPopup(aPopup) == TopPopup();
    const TPopupInfo* info = PopupInfo(aPopup);
    if (info && info->iControlStackPriority != KErrNotFound)
        {
        iAppUi->RemoveFromStack(aPopup);
        TInt flags = top ? info->iControlStackFlags : KControlStackSleepFlags;
        iAppUi->AddToStackL(aPopup, info->iControlStackPriority, flags);
        }
    }

TBool CAknGlobalPopupPriorityController::RemoveFromStack(CCoeControl* aPopup)
    {
    // only if it's already in the stack
    TInt pos = iShownStack.Find(aPopup);
    if (pos == KErrNotFound)
        {
        return EFalse;
        }
    else
        {
        iShownStack.Remove(pos);
        return pos == 0;
        }
    }

CAknGlobalPopupPriorityController::CAknGlobalPopupPriorityController()
: CCoeStatic(KAknGlobalPopupPriorityControllerStaticId),
  iPopupInfoMap(THashFunction32<CCoeControl*>(&GeneralPtrHash), TIdentityRelation<CCoeControl*>(&GeneralPtrIdentity)),
  iGlobalPopupsAllowed(EFalse),
  iAppUi(CEikonEnv::Static()->EikAppUi())
    {
    }

CAknGlobalPopupPriorityController::~CAknGlobalPopupPriorityController()
    {
    iPopupInfoMap.Close();
    iShownStack.Close();
    }

void CAknGlobalPopupPriorityController::ConstructL()
    {
    iShownStack.Reserve(KAknGlobalPopupPriorityControllerMaxStack);
    }

CAknGlobalPopupPriorityController::TPopupInfo* CAknGlobalPopupPriorityController::PopupInfo(CCoeControl* aPopup)
    {
    TPopupInfo* info = iPopupInfoMap.Find(aPopup);
    return info;
    }

const CAknGlobalPopupPriorityController::TPopupInfo* CAknGlobalPopupPriorityController::PopupInfo(CCoeControl* aPopup) const
    {
    const TPopupInfo* info = iPopupInfoMap.Find(aPopup);
    return info;
    }

CAknGlobalPopupPriorityController::TPopupInfo& CAknGlobalPopupPriorityController::PopupInfoL(CCoeControl* aPopup)
    {
    TPopupInfo* info = PopupInfo(aPopup);
    if (info)
        return *info;
    iPopupInfoMap.InsertL(aPopup, TPopupInfo());
    return *PopupInfo(aPopup);
    }

void CAknGlobalPopupPriorityController::AddSubPopupL(CCoeControl* aPopup, CCoeControl* aSubPopup)
    {
    // Below 3 rows of calling PopupInfoL() look like a little uncomfortable,
    // because PopupInfoL will add new element in its hash map. 
    // So, a new element may be inserted when calling PopupInfoL(aSubPopup).
    // It may will lead to the change of aPopup address returned from the first calling PopupInfoL(aPopup).
    // So, we need to get the parent reference again.
    PopupInfoL(aPopup);
    TPopupInfo& sub = PopupInfoL(aSubPopup);
    TPopupInfo& parent = PopupInfoL(aPopup);
    
    __ASSERT_DEBUG(parent.iSubPopup == NULL || parent.iSubPopup == aSubPopup, GppcPanic(EGppcPanic_DontSupportMultipleSubPopups));
    __ASSERT_DEBUG(sub.iParent == NULL || sub.iParent == aPopup, GppcPanic(EGppcPanic_DontSupportMultipleParents));
    parent.iSubPopup = aSubPopup;
    sub.iParent = aPopup;
    // put it at the same window position as its parent
    aSubPopup->DrawableWindow()->SetOrdinalPosition(aPopup->DrawableWindow()->OrdinalPosition());
    }


void CAknGlobalPopupPriorityController::AddPopupToControlStackL(CCoeControl* aPopup,TInt aPriority,TInt aStackingFlags)
    {
    TPopupInfo& info = PopupInfoL(aPopup);
    info.iControlStackPriority = aPriority;
    info.iControlStackFlags = aStackingFlags;
    SetPopupKeyPositionsL(aPopup);
    }

CCoeControl* CAknGlobalPopupPriorityController::RootPopup(CCoeControl* aTip) const
    {
    const TPopupInfo* info;
    info = PopupInfo(aTip);
    while (info && info->iParent)
        {
        aTip = info->iParent;
        info = PopupInfo(aTip);
        }


    return aTip;
    }

CCoeControl* CAknGlobalPopupPriorityController::TopPopup() const
    {
    if (iShownStack.Count() > 0 && iGlobalPopupsAllowed)
        return iShownStack[0];
    else
        return NULL;
    }

TBool CAknGlobalPopupPriorityController::PopupIsShown(CCoeControl* aPopup) const
    {
    TInt pos = iShownStack.Find(aPopup);
    return pos != KErrNotFound;
    }

void CAknGlobalPopupPriorityController::FadeBehindPopupL(CCoeControl* aPopup, MAknFadedComponent* aFadedComponent)
    {
    TPopupInfo& info = PopupInfoL(aPopup);
    info.iFadedComponent = aFadedComponent;
    DoFadeBehindPopup(aPopup);
    }

void CAknGlobalPopupPriorityController::DoFadeBehindPopup(CCoeControl* aPopup)
    {
    TBool top = aPopup == TopPopup();
    TPopupInfo* info = PopupInfo(aPopup);
    if (!info || !info->iFadedComponent)
        return;
    TAknPopupFader fader;
    fader.FadeBehindPopup(info->iFadedComponent, aPopup, top);
    }

void CAknGlobalPopupPriorityController::RouseSleepingPopup(CCoeControl* aPopup, TBool aRoused)
    {
    TInt pri = ECoeStackPriorityDialog;
    TInt flags = 0;
    TPopupInfo* info = PopupInfo(aPopup);
    if (info)
        {
        pri = info->iControlStackPriority;
        flags = info->iControlStackFlags;
        }
    if (aRoused)
        flags = flags & ~KControlStackSleepFlags;
    else
        flags = flags | KControlStackSleepFlags;
    TRAP_IGNORE(AddPopupToControlStackL(aPopup, pri, flags));
    }

TInt CAknGlobalPopupPriorityController::MinChainWindowPosition(CCoeControl* aPopup) const
    {
    TInt pos = aPopup->DrawableWindow()->OrdinalPosition();
    const TPopupInfo* info = PopupInfo(aPopup);
    while (info && info->iSubPopup)
        {
        aPopup = info->iSubPopup;
        pos = Min(pos, aPopup->DrawableWindow()->OrdinalPosition());
        info = PopupInfo(aPopup);
        }
    return pos;
    }


EXPORT_C void AknGlobalPopupPriorityController::EnablePriorityControlL()
    {
    CAknGlobalPopupPriorityController::CreateInstanceL();
    }

EXPORT_C void AknGlobalPopupPriorityController::AllowGlobalPopups(TBool aAllow)
    {
    CAknGlobalPopupPriorityController* instance = CAknGlobalPopupPriorityController::Instance();
    if (instance)
        instance->AllowGlobalPopups(aAllow);
    }

EXPORT_C TBool AknGlobalPopupPriorityController::GlobalPopupsAllowed()
    {
    TBool globalPopupsAllowed = ETrue;
    CAknGlobalPopupPriorityController* instance = CAknGlobalPopupPriorityController::Instance();
    if (instance)
        globalPopupsAllowed = instance->GlobalPopupsAllowed();
    return globalPopupsAllowed;
    }

EXPORT_C void AknGlobalPopupPriorityController::SetPopupPriorityL(CCoeControl& aPopup, TInt aPriority)
    {
    CAknGlobalPopupPriorityController* instance = CAknGlobalPopupPriorityController::Instance();
    if (instance)
        instance->SetPopupPriorityL(&aPopup, aPriority);
    }

EXPORT_C void AknGlobalPopupPriorityController::RemovePopupPriority(CCoeControl& aPopup)
    {
    CAknGlobalPopupPriorityController* instance = CAknGlobalPopupPriorityController::Instance();
    if (instance)
        instance->RemovePopup(&aPopup);
    }

EXPORT_C void AknGlobalPopupPriorityController::ShowPopup(CCoeControl& aPopup, TBool aShow)
    {
    CAknGlobalPopupPriorityController* instance = CAknGlobalPopupPriorityController::Instance();
    if (instance)
        instance->ShowPopup(&aPopup, aShow);
    }

EXPORT_C void AknGlobalPopupPriorityController::SetRootWinOrdinalPosition(TInt aOrdinalPosition)
    {
    CAknGlobalPopupPriorityController* instance = CAknGlobalPopupPriorityController::Instance();
    if (instance)
        instance->SetRootWinOrdinalPosition(aOrdinalPosition);
    }

EXPORT_C void AknGlobalPopupPriorityController::AddSubPopupL(CCoeControl& aPopup, CCoeControl& aSubPopup)
    {
    CAknGlobalPopupPriorityController* instance = CAknGlobalPopupPriorityController::Instance();
    if (instance)
        instance->AddSubPopupL(&aPopup, &aSubPopup);
    }

EXPORT_C void AknGlobalPopupPriorityController::AddPopupToControlStackL(CCoeControl& aPopup,TInt aPriority,TInt aStackingFlags)
    {
    CAknGlobalPopupPriorityController* instance = CAknGlobalPopupPriorityController::Instance();
    if (instance)
        instance->AddPopupToControlStackL(&aPopup, aPriority, aStackingFlags);
    else
        {
        CEikAppUi* appUi = CEikonEnv::Static()->EikAppUi();
        if (appUi)
            {
            appUi->RemoveFromStack(&aPopup);
            appUi->AddToStackL(&aPopup, aPriority, aStackingFlags);
            }
        }
    }

EXPORT_C void AknGlobalPopupPriorityController::RouseSleepingPopup(CCoeControl& aPopup, TBool aRoused)
    {
    CAknGlobalPopupPriorityController* instance = CAknGlobalPopupPriorityController::Instance();
    if (instance)
        instance->RouseSleepingPopup(&aPopup, aRoused);
    else
        CEikonEnv::Static()->RouseSleepingDialog(&aPopup, aRoused);
    }

EXPORT_C void AknGlobalPopupPriorityController::FadeBehindPopup(CCoeControl& aPopup, TAknPopupFader& aFader, MAknFadedComponent& aFadedComponent, TBool aFade)
    {
    CAknGlobalPopupPriorityController* instance = CAknGlobalPopupPriorityController::Instance();
    if (instance)
        {
        TRAP_IGNORE(instance->FadeBehindPopupL(&aPopup, &aFadedComponent));
        }
    else
        {
        aFader.FadeBehindPopup(&aFadedComponent, &aPopup, aFade);
        }
    }
