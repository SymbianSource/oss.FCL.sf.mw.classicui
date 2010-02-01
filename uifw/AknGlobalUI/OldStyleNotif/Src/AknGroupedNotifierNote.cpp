/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description: 
*
*/

#include "AknGroupedNotifierNote.h"
#include <eikbtgpc.h>
#include <avkon.rsg>
#include <avkon.hrh>
#include <eikfrlb.h>
#include <eikfrlbd.h>
#include <aknenv.h>
#include <aknnotpi.rsg>
#include <viewcli.h>
#include <StringLoader.h>
#include <aknlists.h>
#include <coreapplicationuisdomainpskeys.h> // KCoreAppUIsAutolockStatus

#include "AknCapServerEntry.h"

/// Maximum allocated space for custom softkeys.
const TInt KAknMaxCustomSoftkeyLength    = 30;

void CAknGroupedNotifierNote::ConstructL(MAknGroupedNotifierNoteObserver* aObserver)
    {
    iNoteObserver = aObserver;
    iOrder = new(ELeave) CArrayFixFlat<TInt>(4);
    
    iAutoLockStatus = EAutolockOff;
    RProperty autolockProperty;
    autolockProperty.Get(KPSUidCoreApplicationUIs, KCoreAppUIsAutolockStatus, iAutoLockStatus);
    }

void CAknGroupedNotifierNote::ActivateL()
    {
    CEikDialog::ActivateL();
    }

void CAknGroupedNotifierNote::PreLayoutDynInitL()
    {
    CAknListQueryDialog::PreLayoutDynInitL();
    iTexts = iCoeEnv->ReadDesCArrayResourceL(R_GROUPED_NOTIFIER_TEXTS);
    if (iNoteObserver)
        {
        // Allow observer to add new texts
        iNoteObserver->AddItemsL( *iTexts, *iOrder );
        }

    iTextsPlural = iCoeEnv->ReadDesCArrayResourceL(R_GROUPED_NOTIFIER_TEXTS_PLURAL);
    SetItemTextArray(this);
    SetOwnershipType(ELbmDoesNotOwnItemArray);
    
    CEikListBox* listbox = ListBox();
    if (listbox)
        {
        listbox->SetObserver(this);
        }

#ifdef RD_SCALABLE_UI_V2
    if ( AknLayoutUtils::PenEnabled() )
        {
        SetGloballyCapturing(ETrue); 
        SetPointerCapture(ETrue); 
        }
#endif        
    }

void CAknGroupedNotifierNote::PostLayoutDynInitL()
    {
    // A focused custom note might require different softkeys than the default ones.
    UpdateSoftkeysL();    
    }

void CAknGroupedNotifierNote::ProcessCommandL(TInt aCommandId)
    {
    // Note about to complete, so signal the notifier
    if (iNoteObserver)
        {
        // This should also inform the selected item to the observer!
        iNoteObserver->GroupedNoteCompletedL(aCommandId);
        }
    TryExitL(aCommandId);
    }

CAknGroupedNotifierNote::CAknGroupedNotifierNote()
    : CAknListQueryDialog(&iSelectedItem)
    {
    }

CAknGroupedNotifierNote::~CAknGroupedNotifierNote()
    {
    delete iTexts;
    delete iTextsPlural;
    delete iOrder;
    }

void CAknGroupedNotifierNote::HandlePointerEventL(
        const TPointerEvent& aPointerEvent
        ) 
    {
    if (!Rect().Contains(aPointerEvent.iPosition) && 
        aPointerEvent.iType == TPointerEvent::EButton1Down)
        {
        return;
        }
    
    CAknListQueryDialog::HandlePointerEventL(aPointerEvent);    
    }

TKeyResponse CAknGroupedNotifierNote::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    if (aType == EEventKey)
        {
        // Send number keys to phone app, and bring it for foreground
        if ((aKeyEvent.iCode >= '0' && aKeyEvent.iCode <= '9') 
            || aKeyEvent.iCode == '#' 
            || aKeyEvent.iCode == '*')
            {
            if (aKeyEvent.iRepeats == 0)
                {
                MAknPhoneKeyForwarder* keyf = STATIC_CAST(
                    CAknCapAppServerAppUi*, CEikonEnv::Static()->AppUi())->AsKeyForwarder();
                    
                keyf->ForwardKeyToPhoneAppL(aKeyEvent);    
                iNoteObserver->GroupedNoteCompletedL(KErrCancel);
                delete this;
                }
            return EKeyWasConsumed;
            }
        }

    if (aKeyEvent.iCode == EKeyEscape)
        {
        // Workaround the current problem where the SecUI sends an EKeyEscape
        // to the control stack when it wants to remove it's own dialog
        return EKeyWasNotConsumed;
        }

    return CAknListQueryDialog::OfferKeyEventL(aKeyEvent, aType);
    }

TBool CAknGroupedNotifierNote::OkToExitL(TInt aButtonId)
    {
    // Generic method used to find out whether the command belongs to "cancel" commands.
    TInt mappedCommandId = MappedCommandId(aButtonId);    

    TNoteAction noteAction = EDoNothing;
    
    if (mappedCommandId == EEikBidCancel     ||
        mappedCommandId == EAknSoftkeyExit   ||
        mappedCommandId == EAknSoftkeyCancel ||
        mappedCommandId == EAknSoftkeyBack   ||
        mappedCommandId == EAknSoftkeyNo     ||
        mappedCommandId == EAknSoftkeyClose  ||
        mappedCommandId == EAknSoftkeyQuit   ||
        mappedCommandId == EAknSoftkeyDone)
        {
        // The command is a cancelling command.
        noteAction = EExitNote;        
        }
    else if (iCustomNoteAcceptKeyId)
        {
        // The grouped note item is a custom item. Check whether the command
        // is the accept key defined for that custom item.        
        if (mappedCommandId == iCustomNoteAcceptKeyId || mappedCommandId == EAknSoftkeyOk)
            {
            noteAction = ELaunchItemHandler;
            }
        }
    else 
        {
        // The grouped note item is not a custom item. Only "Show" or "Ok" commands
        // are used to launch the note.        
        if (mappedCommandId == EAknSoftkeyShow || mappedCommandId == EAknSoftkeyOk) 
            {
            noteAction = ELaunchItemHandler;
            }
        }

    // Now make the action... 

    if (noteAction == ELaunchItemHandler)
        {
        TInt itemindex = ListBox()->CurrentItemIndex();
        __ASSERT_DEBUG(itemindex != -1, Panic(EAknPanicOutOfRange));

#ifdef RD_SCALABLE_UI_V2
        if (AknLayoutUtils::PenEnabled())
            {
            SetGloballyCapturing(EFalse); 
            SetPointerCapture(EFalse); 
            }
#endif        

        if (itemindex == -1)
            {
            iNoteObserver->GroupedNoteCompletedL(EAknSoftkeyExit, EMaxItem);
            return ETrue;
            }
        
        // Use always Ok command.
        iNoteObserver->GroupedNoteCompletedL(
            EAknSoftkeyOk, 
            TAknGroupedNotifierItem(iOrder->At(itemindex)));
        
        return ETrue;
        }
    else if (noteAction == EExitNote)
        {
#ifdef RD_SCALABLE_UI_V2
        if (AknLayoutUtils::PenEnabled())
            {
            SetGloballyCapturing(EFalse); 
            SetPointerCapture(EFalse); 
            }
#endif        
        // Use always Exit command.
        iNoteObserver->GroupedNoteCompletedL(EAknSoftkeyExit, EMaxItem);
        return ETrue;        
        }

    else
        {
        // Unknown command, do nothing.
        return EFalse;                
        }
    }

void CAknGroupedNotifierNote::SetItemAmountL(TAknGroupedNotifierItem aItem, TInt aAmount, 
    TBool aHighlight)
    {
    TInt arrayIndex = aItem - EMissedCalls;
    TBool isDynamicText(EFalse);

    if (arrayIndex >= 0 && arrayIndex < EMaxItem) // traditional types
        {
        iCount[arrayIndex] = aAmount;
        }
    else
        {
        arrayIndex = aItem;
        isDynamicText = ETrue;
        }

    TKeyArrayFix key(0,ECmpTInt);
    TInt item;
    if (iOrder->Find(arrayIndex, key, item) == 0)
        {
        iOrder->Delete(item);
        if (isDynamicText)
            { // if it is in iOrder, it is also in iTexts
            iTexts->Delete(item);
            return; // only deletion of item is allowed in this method.
            }
        }

    if (aAmount > 0)
        {
        iOrder->AppendL(arrayIndex);
        }

    if (aHighlight)
        {
        if (aAmount)
            {
            iHighlightedItem = iOrder->Count() - 1;
            }
        else
            {
            iHighlightedItem = 0;
            }
        }
    }


TInt CAknGroupedNotifierNote::MdcaCount() const
    {
    return iOrder->Count();
    }

TPtrC CAknGroupedNotifierNote::MdcaPoint(TInt aIndex) const
    {
    // can I play with constness ;)
    TDes &des = MUTABLE_CAST(TBuf<KAknMaxGroupedNoteItemTextLength>&, iBuffer);
    des.Zero();
    TPtrC listItemText;
    TInt numOfItems = 0;

    TInt itemType = iOrder->At(aIndex);

    if (itemType >= 0 && itemType < EMaxItem) // traditional types
        {
        numOfItems = iCount[itemType];

        __ASSERT_DEBUG(numOfItems > 0, Panic(EAknPanicOutOfRange));
        // choose the item to show
        if (numOfItems == 1)
            {
            listItemText.Set(iTexts->MdcaPoint(itemType));
            }
        else
            {
            listItemText.Set(iTextsPlural->MdcaPoint(itemType));
            }
        }
    else // "Dynamic" texts 
        {
        // count text index
        for (TInt i = 0; i < EMaxItem; i++)
            {
            if (iCount[i] > 0) // static text in iOrder
                {
                aIndex--;
                }
            }
        
        aIndex += EMaxItem; // jump over static texts
        
        __ASSERT_ALWAYS(aIndex >= 0, User::Invariant());
        listItemText.Set(iTexts->MdcaPoint(aIndex));
        }
        
    // replace %N with the number
    _LIT(KNumber,"%N");
    TInt pos = listItemText.Find(KNumber);
    
    if (pos != KErrNotFound)
        {
        StringLoader::Format(des, listItemText, -1, numOfItems);           
        }
    else
        {
        des.Append(listItemText.Left(KAknMaxGroupedNoteItemTextLength));
        }

    // return result
    return iBuffer;
    }

TBool CAknGroupedNotifierNote::AutoLockEnabled()
    {
    return EFalse;
    }

void CAknGroupedNotifierNote::CEikDialog_Reserved_1()
    {
    }

void CAknGroupedNotifierNote::CEikDialog_Reserved_2()
    {
    }

void CAknGroupedNotifierNote::CAknDialog_Reserved()
    {
    }

void CAknGroupedNotifierNote::CAknQueryDialog_Reserved()
    {
    }
    
void CAknGroupedNotifierNote::HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType)
    {
    if (aEventType == EEventStateChanged)
        {
        // Focused item has changed, softkeys might require updating.
        UpdateSoftkeysL();
        }
        
    CAknListQueryDialog::HandleControlEventL(aControl, aEventType);
    }

void CAknGroupedNotifierNote::UpdateSoftkeysL()
    {
    CEikListBox* listbox = ListBox();
    if (listbox)
        {
        // Get the focused item and check that it is in valid range. 
        TInt itemindex = listbox->CurrentItemIndex();
        __ASSERT_DEBUG(itemindex >= 0 && itemindex < MdcaCount(), Panic(EAknPanicOutOfRange));

        if (itemindex >= 0 && itemindex < MdcaCount())
            {
            // If the focused item is a custom note, this method returns its resource id.        
            TAknGroupedNotifierItem item = TAknGroupedNotifierItem(iOrder->At(itemindex));

            HBufC* leftSK = HBufC::NewLC( KAknMaxCustomSoftkeyLength );
            HBufC* rightSK = HBufC::NewLC( KAknMaxCustomSoftkeyLength );
            
            TInt newSoftkeys = 0;
            if (item > EMaxItem || item < 0) 
                {
                // Note is out of "static" range, i.e. a custom note.
                TPtr left( leftSK->Des() );
                TPtr right( rightSK->Des() );
                iNoteObserver->SoftkeysForCustomItem(item, newSoftkeys, 
                    iCustomNoteAcceptKeyId, left, right );
                }
                
            if (!newSoftkeys)
                {
                newSoftkeys = R_AVKON_SOFTKEYS_SHOW_EXIT__SHOW;
                iCustomNoteAcceptKeyId = 0;
                }
                
            // Update softkeys only if necessary.
            if( newSoftkeys != iCustomNoteSoftkeys ||
                iCustomNoteSoftkeysAssigned || // custom text was used (force update)
                leftSK->Length() > 0 ||
                rightSK->Length() > 0 )
                {
                CEikButtonGroupContainer& buttonGroup = ButtonGroupContainer();
                buttonGroup.SetCommandSetL(newSoftkeys);            
                buttonGroup.DrawDeferred();
                iCustomNoteSoftkeys = newSoftkeys;
                
                iCustomNoteSoftkeysAssigned = EFalse;
                MEikButtonGroup* buttonGrp = buttonGroup.ButtonGroup();
                if( buttonGrp )
                    {
                    if( leftSK->Length() > 0 )
                        {
                        buttonGroup.SetCommandL( buttonGrp->CommandId( 
                            CEikButtonGroupContainer::ELeftSoftkeyPosition ), 
                            *leftSK );
                        iCustomNoteSoftkeysAssigned = ETrue;
                        }
                    if( rightSK->Length() > 0 )
                        {
                        buttonGroup.SetCommandL( buttonGrp->CommandId( 
                            CEikButtonGroupContainer::ERightSoftkeyPosition ),
                            *rightSK );
                        iCustomNoteSoftkeysAssigned = ETrue;
                        }
                    }
                }
            CleanupStack::PopAndDestroy( 2, leftSK ); // rightSK
            }
        }
    
    // If we are going to display the grouped list notification on the top of Autolock App,
    // So we need to invisible the softkey buttons.
    if (AknLayoutUtils::PenEnabled() && iAutoLockStatus > EAutolockOff)
        {
        CEikButtonGroupContainer& bgc = ButtonGroupContainer();
        MEikButtonGroup* buttonGrp = bgc.ButtonGroup();
        if (buttonGrp)
            {
            bgc.SetCommandL(buttonGrp->CommandId(CEikButtonGroupContainer::ELeftSoftkeyPosition), KNullDesC);
            bgc.SetCommandL(buttonGrp->CommandId(CEikButtonGroupContainer::ERightSoftkeyPosition), KNullDesC);
            }
        }
    }

// End of file
