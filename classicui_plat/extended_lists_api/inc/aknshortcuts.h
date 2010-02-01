/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef __AKNSHORTCUTS_H__
#define __AKNSHORTCUTS_H__

#include <eiklbx.h>
#include <eikcmobs.h>
#include <avkon.hrh>
class CEikButtonGroupContainer;

/* This file is needed only by people who want to build new styles of lists that have shortcuts
   - prefer using types from aknlists.h
*/

class AknListBoxShortCuts;
class CAknGridM;


template<class ListBox>
class AknListBoxShortCutTemplate : public ListBox
    {
    // All the following is used to test shortcuts
public:
    inline ~AknListBoxShortCutTemplate();
    inline void ConstructL(const CCoeControl* aParent, TInt aFlags);
    inline void ConstructFromResourceL(TResourceReader& aReader);
    inline TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
    inline TInt ShortcutValueForNextList();
    inline void SetShortcutValueFromPrevList(TInt aValue);
    inline void SetShortcutEnabledL(TBool aTrue);
private:
    AknListBoxShortCuts* iShortcuts;

    // End of shortcut test code.
    };


//
// Shortcut helper (will be placed inside listbox somewhere when it is
// ready.)  Much of this should be using existing IncrementalMatching
// feature of CEikListBox, but this class implements Series 60 -specific
// things with timers and things like that.  See "Menu for Series 60"
// specification/ Shortcut Procedure for Lists.
//
class AknListBoxShortCuts : public CTimer
    {
protected:
    enum TShortcutEvent
	{
	ENone,
	EIdle,
	ENavi,
	ENumber,
	EStateToOne,
	EStateToFive
	};
    enum TShortcutState
	{
	EStateNone,
	EState1,
	EState2,
	EState2HideOnly,
	EState2HideAndGoState3,
	EState2HideAndGoState4,
	EState3,
	EState4,
	EState5,
	EState6
	};
    enum TShortcutTimerType
	{
	ENoTimeout,
	ENoUserActionTimeout,
	EIndexDisplayTimeout,
	EShortcutActiveTimeout
	};
    enum TConcreteShortcutActions
	{
	EAddKeyAsShortcutDigitAndMoveFocus,
	ERemoveKeyDigitFromIndexNumber,
	EShowShortcutNumber,
	EHideShortcutNumber,
	EForwardKeyEventToListBox,
	ESelectListBoxItem,
	EPassDigitToNextList,
	EEnableSoftkeys,
	EDisableSoftkeys,
	EBeginning,
	EStoreFocusedItemPos,
	EAssertNotFetched
	};
    enum TConcreteQuery
	{
	ENewItemFocused,
	ECheckForValidIndexNumber
	};
public: // CCoeControl
    IMPORT_C virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

public: // public interface of shortcuts
    IMPORT_C AknListBoxShortCuts();
    IMPORT_C virtual ~AknListBoxShortCuts();
    IMPORT_C virtual void ConstructL();

    IMPORT_C TBool RecursionLock();
    IMPORT_C void RecursionUnlock();


    
public: // from CTimer
    // We use After() and Cancel() from CTimer too.
    IMPORT_C void RunL(); // timer elapsed

public: // State machine handling shortcut timers and behavior

    // State machine state change
    IMPORT_C void ChangeStateL(TShortcutEvent aEvent);

    IMPORT_C void DoProcedureL(); 

    IMPORT_C void StartTimerL(TShortcutTimerType aTimer);
    IMPORT_C void EndTimer();

    // Concrete actions (these will not change the state machine - They should only call methods of external objects to do their job)
    virtual TBool DoTest(TConcreteQuery q)=0;
    virtual void DoActionL(TConcreteShortcutActions a) =0;

    virtual TInt ShortcutValueForNextList()=0;
    virtual void SetShortcutValueFromPrevList(TInt aValue)=0;
private:
    TShortcutTimerType iCurrentTimerType;
    TShortcutState iState;    
    TShortcutState iIdleNextState, iNaviKeyNextState, iNumKeyNextState;
    TBool iLocked;
    };



class AknListBoxShortCutsImplementation : public AknListBoxShortCuts, public MEikCommandObserver
    {
public:
    IMPORT_C AknListBoxShortCutsImplementation(CEikListBox* aListBox);
    IMPORT_C ~AknListBoxShortCutsImplementation();
public: // from AknListBoxShortCuts
    IMPORT_C void ConstructL();
    IMPORT_C virtual TBool DoTest(TConcreteQuery q);
    IMPORT_C virtual void DoActionL(TConcreteShortcutActions a);
    IMPORT_C virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

    IMPORT_C virtual TInt ShortcutValueForNextList();
    IMPORT_C virtual void SetShortcutValueFromPrevList(TInt aValue);

public: // MEikCommandObserver
    IMPORT_C void ProcessCommandL(TInt); /* should be empty! */

protected: // from MObjectProvider
	IMPORT_C TTypeUid::Ptr MopSupplyObject(TTypeUid aId);

private:
    CEikListBox* iListBox; // We do not own this
    TKeyEvent iEvent;
    TEventCode iEventCode;
    CEikButtonGroupContainer *iCba; // We Do own this.
    TInt iFocusItemPos;
    TBool iStillNeedToFetchShortcutValue;
    };

template<class ListBox>
inline AknListBoxShortCutTemplate<ListBox>::~AknListBoxShortCutTemplate()
	{
	delete iShortcuts;
	}

template<class ListBox>
inline void AknListBoxShortCutTemplate<ListBox>::ConstructL(const CCoeControl* aParent, TInt aFlags)
	{
	ListBox::ConstructL(aParent,aFlags);

	if (this->iListBoxFlags & EAknListBoxIncrementalMatching) 
	    {
	    iShortcuts = new (ELeave) AknListBoxShortCutsImplementation(this);
	    iShortcuts->ConstructL();
	    }
	}

template<class ListBox>
inline void AknListBoxShortCutTemplate<ListBox>::ConstructFromResourceL(TResourceReader& aReader)
	{
	ListBox::ConstructFromResourceL(aReader);
	
	if (this->iListBoxFlags & EAknListBoxIncrementalMatching) 
	    {
	    iShortcuts = new (ELeave) AknListBoxShortCutsImplementation(this);
	    iShortcuts->ConstructL();
	    }
	}

template<class ListBox>
inline TKeyResponse AknListBoxShortCutTemplate<ListBox>::OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType)
	{
	    if (iShortcuts && iShortcuts->RecursionLock()) 
		{
		TKeyResponse retval = iShortcuts->OfferKeyEventL(aKeyEvent, aType);
		iShortcuts->RecursionUnlock();
		if (retval == EKeyWasNotConsumed) ListBox::OfferKeyEventL(aKeyEvent, aType);
		return retval;
		}
	    else
		return ListBox::OfferKeyEventL(aKeyEvent, aType);
	}
template<class ListBox>
inline TInt AknListBoxShortCutTemplate<ListBox>::ShortcutValueForNextList() 
	{ 
	return iShortcuts ? iShortcuts->ShortcutValueForNextList() : 0; 
	}

template<class ListBox>
inline void AknListBoxShortCutTemplate<ListBox>::SetShortcutValueFromPrevList(TInt aValue) 
	{
	if (iShortcuts) iShortcuts->SetShortcutValueFromPrevList(aValue); 
	}

template<class ListBox>
inline void AknListBoxShortCutTemplate<ListBox>::SetShortcutEnabledL(TInt aValue)
    {
    if (aValue && !iShortcuts)
	{
	if (this->iListBoxFlags & EAknListBoxIncrementalMatching) 
	    {
	    iShortcuts = new (ELeave) AknListBoxShortCutsImplementation(this);
	    iShortcuts->ConstructL();
	    }
	}
    else if (!aValue)
	{
	delete iShortcuts;
	iShortcuts = 0;
	}
    }

#endif







