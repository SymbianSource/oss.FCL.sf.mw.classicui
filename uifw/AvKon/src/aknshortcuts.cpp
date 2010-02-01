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


#include "aknshortcuts.h"

#include <AknPanic.h>
#include <avkon.rsg>
#include <eikbtgpc.h>
#include <eikenv.h>
#include <aknappui.h>
#include <avkon.hrh>

// The following are needed for template instantiations. aknlists.h
// tells the compiler which shortcuttemplates to instantiate.
#include <AknGrid.h>
#include <aknlists.h>


//
// Shortcut behavior.
//

EXPORT_C void AknListBoxShortCuts::RunL() 
    {
    TShortcutEvent event = EIdle;
    EndTimer();
    ChangeStateL(event);
    DoProcedureL();
    }

EXPORT_C void AknListBoxShortCuts::ConstructL()
    {
    CTimer::ConstructL();
    CActiveScheduler::Add(this);
    DoProcedureL();
    }

EXPORT_C AknListBoxShortCuts::AknListBoxShortCuts() 
    : CTimer(EActivePriorityClockTimer),
      iCurrentTimerType(ENoTimeout),
      iState(EState1),
      iIdleNextState(EStateNone),
      iNaviKeyNextState(EStateNone),
      iNumKeyNextState(EStateNone),
      iLocked(EFalse)
    { }

EXPORT_C TBool AknListBoxShortCuts::RecursionLock()
    {
    if (iLocked) return EFalse;
    iLocked = ETrue;
    return ETrue;
    }

EXPORT_C void AknListBoxShortCuts::RecursionUnlock()
    {
    iLocked = EFalse;
    }

// EndTimer() call must be in most derived class too -- we do not want timer events after destruction
// of most derived class.
EXPORT_C AknListBoxShortCuts::~AknListBoxShortCuts() { EndTimer(); }

EXPORT_C TKeyResponse AknListBoxShortCuts::OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode /*aType*/)
    {
    TShortcutEvent event=ENone;
    switch (aKeyEvent.iCode) 
	{
	case EKeyDownArrow:
	case EKeyUpArrow:
	    event = ENavi;
	    break;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case '*':
	case '#':
	    event = ENumber;
	    break;
	};
    
    if (event == ENone) return EKeyWasNotConsumed;
    ChangeStateL(event);
    DoProcedureL();
    return EKeyWasConsumed;
    }



EXPORT_C void AknListBoxShortCuts::ChangeStateL(TShortcutEvent aEvent) 
    {
    switch(aEvent)
		{
    	case EIdle:
			iState = iIdleNextState;
			break;
	    case ENavi:
			iState = iNaviKeyNextState;
			break;
		case ENumber:
			iState = iNumKeyNextState;
			break;
		case EStateToOne:
			EndTimer();
			iState=EState1;
			iIdleNextState=EStateNone;
			iNaviKeyNextState=EStateNone;
			iNumKeyNextState=EStateNone;
			DoProcedureL();
			break;
		case EStateToFive:
			iState = EState5;
			break;
		default:
			break;
		};
    }

EXPORT_C void AknListBoxShortCuts::EndTimer()
    {
    if (iCurrentTimerType == ENoTimeout) return;

    switch(iCurrentTimerType)
		{
		case EShortcutActiveTimeout:
		    TRAP_IGNORE(
		    DoActionL(EEnableSoftkeys)
		    );
		    break;
		default:
		    break;
		};
    Cancel();
    iCurrentTimerType = ENoTimeout;
    }
EXPORT_C void AknListBoxShortCuts::StartTimerL(TShortcutTimerType aTimer) 
    {
    TInt timeout = 0;
    EndTimer();
    iCurrentTimerType = aTimer;

    switch(iCurrentTimerType)
		{
		case ENoUserActionTimeout:
		    timeout = 20;
			break;
			case EIndexDisplayTimeout:
			    timeout = 30;
			break;
		case EShortcutActiveTimeout:
			// Softkeys are disabled during shortcutactivetimeout.
			DoActionL(EDisableSoftkeys);
			timeout = 20;
			break;
		default:
			break;
		};
    After(timeout);
    }

EXPORT_C void AknListBoxShortCuts::DoProcedureL() 
    {
    switch (iState)
		{
		case EState1:
			DoActionL(EBeginning);
			StartTimerL(ENoUserActionTimeout);
			iIdleNextState = EState2;
			iNaviKeyNextState = EState3;
			iNumKeyNextState = EState4;
			break;
		case EState2: // No action during ENoUserActionTimeout
			DoActionL(EAssertNotFetched);
			DoActionL(EShowShortcutNumber);
			StartTimerL(EIndexDisplayTimeout);
			iIdleNextState = EState2HideOnly;
			iNaviKeyNextState = EState2HideAndGoState3;
			iNumKeyNextState = EState2HideAndGoState4;
			break;
		case EState2HideOnly:
			DoActionL(EAssertNotFetched);
			DoActionL(EHideShortcutNumber);
			break;
		case EState2HideAndGoState3:
			DoActionL(EHideShortcutNumber);
			// FALL THROUGH
		case EState3: // Navigation keys
			DoActionL(EAssertNotFetched);
			DoActionL(EStoreFocusedItemPos);
			DoActionL(EForwardKeyEventToListBox);
			if (DoTest(ENewItemFocused)) 
				{
				// We're at state 1 again.
				StartTimerL(ENoUserActionTimeout);
				iIdleNextState = EState2;
				iNaviKeyNextState = EState3;
				iNumKeyNextState = EState4;	
				}
			break;
		case EState2HideAndGoState4:
			DoActionL(EHideShortcutNumber);
			// FALL THROUGH
		case EState4: // Numeric keys
			DoActionL(EAssertNotFetched);
			DoActionL(EAddKeyAsShortcutDigitAndMoveFocus);
			if (DoTest(ECheckForValidIndexNumber)) 
				{
				StartTimerL(EShortcutActiveTimeout);
				iIdleNextState = EState5;
				iNumKeyNextState = EState6;
				iNaviKeyNextState = EState3;
				}
			break;
		case EState5: // After EshortcutActiveTimeout, user did nothing
			DoActionL(ESelectListBoxItem);
			ChangeStateL(EStateToOne);
			break;
		case EState6: // pressed 0-9 during shortcutactivetimeout
			DoActionL(EAddKeyAsShortcutDigitAndMoveFocus);
			if (DoTest(ECheckForValidIndexNumber)) 
				{
				StartTimerL(EShortcutActiveTimeout);
				iIdleNextState = EState5;
				iNumKeyNextState = EState6;
				iNaviKeyNextState = EState3;	    
				} else {
				DoActionL(ERemoveKeyDigitFromIndexNumber);
				DoActionL(EPassDigitToNextList);
				DoActionL(ESelectListBoxItem);
				ChangeStateL(EStateToOne);

				}
			break;
		default:
			break;
		};
    }



EXPORT_C TInt AknListBoxShortCutsImplementation::ShortcutValueForNextList()
    {
    if (iStillNeedToFetchShortcutValue == EFalse)
	return 0;
    iStillNeedToFetchShortcutValue = EFalse;
    return iEvent.iCode;
    }

/* valid values for aValue are 0 and '0' <= aValue <= '9'. Application does not need to know
   this - they just pass the interger from one list to another. */
EXPORT_C void AknListBoxShortCutsImplementation::SetShortcutValueFromPrevList(TInt /*aValue*/)
    {
#if 0
    if (aValue == 0) return;

    __ASSERT_DEBUG(aValue>=int('0') && aValue<=int('9'), Panic(EAknPanicListboxShortcutInvalidValue));
    iEvent.iCode = aValue;
    TRAP_IGNORE( ChangeStateL(ENumber) ); // THIS MAY LEAVE
    TRAP_IGNORE( DoProcedureL() ); // THIS MAY LEAVE
#endif
    }


EXPORT_C TBool AknListBoxShortCutsImplementation::DoTest(TConcreteQuery q)
    {
    TInt focuspos;
    switch(q) 
	{
	case ENewItemFocused:
	    focuspos = iListBox->CurrentItemIndex();
	    if (iFocusItemPos == focuspos) return EFalse;
	    return ETrue;

	case ECheckForValidIndexNumber:
	    return iListBox->LastCharMatched();

	default:
	    break;
	};
    return TRUE;
    }

EXPORT_C AknListBoxShortCutsImplementation::AknListBoxShortCutsImplementation(CEikListBox* aListBox)
: iListBox(aListBox)
    {
    iStillNeedToFetchShortcutValue = EFalse;
    }

EXPORT_C AknListBoxShortCutsImplementation::~AknListBoxShortCutsImplementation()
    {
    EndTimer(); // This must be in most derived class too.
    delete iCba;
    }

EXPORT_C void AknListBoxShortCutsImplementation::ConstructL()
    {
    AknListBoxShortCuts::ConstructL();
    iListBox->CreateMatchBufferL();
    }

EXPORT_C void AknListBoxShortCutsImplementation::DoActionL(TConcreteShortcutActions a)
    {
    if (iListBox->Model()->NumberOfItems() == 0)
        return;

    TInt code = iEvent.iCode;
    switch(a) 
	{
	case EStoreFocusedItemPos:
	    // this is for use of ENewItemFocused
	    iFocusItemPos = iListBox->CurrentItemIndex();
	    break;
	case EBeginning:
	    iListBox->ClearMatchBuffer();
	    break;
	case EAddKeyAsShortcutDigitAndMoveFocus:
	    iListBox->ClearMatchBuffer();
	    iListBox->MatchTypedCharL(code);
	    break;
	case ERemoveKeyDigitFromIndexNumber:
	    break;
	case EShowShortcutNumber:
	    break;
	case EHideShortcutNumber:
	    break;
	case EForwardKeyEventToListBox:
	    iListBox->OfferKeyEventL(iEvent, iEventCode);
	    break;
	case ESelectListBoxItem:
	    iListBox->ReportListBoxEventL(MEikListBoxObserver::EEventEnterKeyPressed);
	    break;
	case EPassDigitToNextList:
	    break;
	case EDisableSoftkeys:
	    // uses MEikCommandObserver (it should not do anything)
#if 0
	    iCba = iAvkonAppUi->Cba();
	    iCba->AddCommandL(0, EAknSoftkeyDummyUsedWithShortcuts, _L(" "));
	    iCba->AddCommandL(1, EAknSoftkeyDummyUsedWithShortcuts, _L(" ")); 
#endif
#if NOT_NEEDED_ANYMORE
	    if (iCba)
	    	{
	    	delete iCba;
	    	iCba = NULL;
	    	}
	    iCba = CEikButtonGroupContainer::NewL(CEikButtonGroupContainer::ECba, CEikButtonGroupContainer::EHorizontal, this, R_AVKON_SOFTKEYS_EMPTY, *iListBox);
	    iCba->SetBoundingRect(TRect(TPoint(0,0),CEikonEnv::Static()->ScreenDevice()->SizeInPixels()));
	    iCba->MinimumSize();
	    iCba->MakeVisible(ETrue);
	    iListBox->UpdateScrollBarsL();
#endif
	    break;
	case EEnableSoftkeys:
#if 0
	    iCba = iAvkonAppUi->Cba();
	    iCba->RemoveCommandFromStack(0, EAknSoftkeyDummyUsedWithShortcuts);
	    iCba->RemoveCommandFromStack(1, EAknSoftkeyDummyUsedWithShortcuts);
#endif

#if NOT_NEEDED_ANYMORE
	    iCba->MakeVisible(EFalse);
	    delete iCba;
	    iCba = 0;
	    iListBox->UpdateScrollBarsL();
#endif
	    break;
	case EAssertNotFetched:
	    break;
	default:
	    break;
	};
    }


EXPORT_C void AknListBoxShortCutsImplementation::ProcessCommandL(TInt)
    {
    }

EXPORT_C TKeyResponse AknListBoxShortCutsImplementation::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    iEvent = aKeyEvent;
    iEventCode = aType;
    return AknListBoxShortCuts::OfferKeyEventL(aKeyEvent, aType);
    }

// End of File
