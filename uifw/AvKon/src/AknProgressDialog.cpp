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
*   Implementation of CAknProgressDialog.
*
*/

// AknProgressDialog.cpp: implementation of the CAknProgressDialog class.
//
//////////////////////////////////////////////////////////////////////

#include <AknProgressDialog.h>
#include <aknprogresstimer.h>
#include <aknnotecontrol.h>
#include <eikenv.h>
#include <eikappui.h>
#include <eikcba.h>
#include <avkon.hrh>
#include "aknnoteattributes.h"
#include <akninputblock.h>


#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
#include <gfxtranseffect/gfxtranseffect.h>
#include <akntransitionutils.h>
#endif

#include <AknTasHook.h> // for testability hooks
NONSHARABLE_CLASS(CAknProgressDialog::CCancelWhileHidden) : public CBase, public MAknInputBlockCancelHandler
	{
public:
	static CCancelWhileHidden* NewL(CAknProgressDialog* aAknProgressDialog);
	~CCancelWhileHidden();
private: // from MAknInputBlockCancelHandler
	void AknInputBlockCancel();
private:
	CCancelWhileHidden(CAknProgressDialog* aAknProgressDialog);
	void ConstructL();
private:
	CAknProgressDialog* iAknProgressDialog;
	CAknInputBlock* iBlock;
	};
	
CAknProgressDialog::CCancelWhileHidden* CAknProgressDialog::CCancelWhileHidden::NewL(CAknProgressDialog* aAknProgressDialog)
	{
	CCancelWhileHidden* self = new(ELeave) CCancelWhileHidden(aAknProgressDialog);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}
	
CAknProgressDialog::CCancelWhileHidden::~CCancelWhileHidden()
	{
	if (iBlock)
		iBlock->SetCancelHandler(NULL);
	delete iBlock;
	}
	
void CAknProgressDialog::CCancelWhileHidden::AknInputBlockCancel()
	{
	TKeyEvent key;
	key.iRepeats=0;
	key.iCode=EKeyEscape;
	key.iModifiers=0;
	key.iScanCode = EStdKeyNull;
	iAknProgressDialog->OfferKeyEventL(key, EEventKey);
	}
	
CAknProgressDialog::CCancelWhileHidden::CCancelWhileHidden(CAknProgressDialog* aAknProgressDialog)
: iAknProgressDialog(aAknProgressDialog)
	{
	}
	
void CAknProgressDialog::CCancelWhileHidden::ConstructL()
	{
	iBlock = CAknInputBlock::NewCancelHandlerLC(this);
	CleanupStack::Pop(iBlock);
	}
	

const TInt KMinProcessTimeToShowDialog = 2000;	// 0.002 sec
const TInt KMinTimeDialogOnScreen = 1500000;	// 1.5 sec

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EXPORT_C CAknProgressDialog::CAknProgressDialog(TInt aFinalValue,TInt anIncrement,
         TInt anInterval,CEikDialog** aSelfPtr) :
         CAknNoteDialog(aSelfPtr),iInternalTimerControl(ETrue)
	{
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
	GfxTransEffect::Register( this, KGfxWaitNoteControlUid );
#endif
	iModel.iFinalValue = aFinalValue;
	iModel.iHundreths = anInterval;
	iModel.iIncrement = anIncrement;
	iModel.iRunning = EFalse;
	AKNTASHOOK_ADD( this, "CAknProgressDialog" );
	}

EXPORT_C CAknProgressDialog::CAknProgressDialog(CEikDialog** aSelfPtr) :
	CAknNoteDialog(aSelfPtr),iInternalTimerControl(EFalse)
	{
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
	GfxTransEffect::Register( this, KGfxWaitNoteControlUid );
#endif
	AKNTASHOOK_ADD( this, "CAknProgressDialog" );
	}

EXPORT_C CAknProgressDialog::CAknProgressDialog(CEikDialog** aSelfPtr,
                                                TBool aVisibilityDelayOff)
:	CAknNoteDialog(aSelfPtr),
	iVisibilityDelayOff( aVisibilityDelayOff ),
	iInternalTimerControl(EFalse)
	{
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
	GfxTransEffect::Register( this, KGfxWaitNoteControlUid );
#endif
	AKNTASHOOK_ADD( this, "CAknProgressDialog" );
	}

EXPORT_C CAknProgressDialog::~CAknProgressDialog()
	{
	AKNTASHOOK_REMOVE();
    if ( iInternalTimerControl )
        {
        PlayTone();
        }
    iEikonEnv->RemoveFromStack(this);
    delete iCancelWhileHidden;
    delete iProgressTimer;
	delete iProgressDialogTimer;
	}

EXPORT_C void CAknProgressDialog::PreLayoutDynInitL()
	{
	//If the progress bar is to be controlled externally, it won't be updated
	//through this dialog class
	if (iInternalTimerControl)
		{
        CAknNoteControl* note = NoteControl();
		if (!iProgressTimer)
			{
			iProgressTimer = new (ELeave) CAknProgressTimer;
			iProgressTimer->ConstructL(&iModel,note,TCallBack(StaticDeleteL,this));
			}
		}

	TransferControlAttributes();

    // Key events should be reveived even when invisible
    MEikButtonGroup* cba = ButtonGroupContainer().ButtonGroup();
    STATIC_CAST( CEikCba*, cba)->SetButtonGroupFlags( cba->ButtonGroupFlags() | 
                                EAknCBAFlagRespondWhenInvisible );
	}


TInt CAknProgressDialog::DialogTimerCallback(TAny* aPtr)
	{
	return STATIC_CAST(CAknProgressDialog*, aPtr)->DialogTimerEvent();
	}

TInt CAknProgressDialog::DialogTimerEvent()
    {
    switch ( iState )
        {
        case EProcessOnDisplayOff:
			{
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS			
            TBool doTransEffect = !IsVisible();
            GfxTransEffect::Abort();
            //register even if we don't do effect now so we can get one when closing dialog
            GfxTransEffect::Register( this, KGfxWaitNoteControlUid );
			TBool rsWasEnabled( EFalse );

            if ( doTransEffect )
                {
                CAknTransitionUtils::SetData(EDontAnimateBitmaps, (TAny*)this);
            if( !CAknEnv::Static()->TransparencyEnabled() && Window().IsRedrawStoreEnabled() )
                {
                rsWasEnabled = ETrue;
                // disable redrawstore during transition to avoid
                // drawing problems behind FSW
                Window().EnableRedrawStore( EFalse );
                }
			
			CAknTransitionUtils::SetAllParents(this);
		    GfxTransEffect::Begin(this, KGfxControlAppearAction);
		    GfxTransEffect::NotifyExternalState(ECaptureComponentsBegin, (const TDesC8*)this);
                }
#endif // RD_UI_TRANSITION_EFFECTS_POPUPS		
			
            // Display dialog
            iState = EProcessOnDisplayOn;
            ControlAttributes()->InvalidateLayout();
            Layout();
            CEikDialog::SlideDialog(); // this does nothing is sliding is disabled
			DrawableWindow()->SetOrdinalPosition(0);
            MakeVisible(ETrue);
   			CCoeControl* cba = ButtonGroupContainer().ButtonGroup()->AsControl();
			iEikonEnv->RemoveFromStack(cba);
			__ASSERT_DEBUG_NO_LEAVE(iEikonEnv->EikAppUi()->AddToStackL(cba, ECoeStackPriorityCba, ECoeStackFlagRefusesFocus));	// Won't fail since we just removed it (and array will not reallocate)
			cba->DrawableWindow()->SetOrdinalPosition(0);
            cba->MakeVisible(ETrue);
            ReportUserActivity();
			PlayTone();
			delete iCancelWhileHidden;
			iCancelWhileHidden = NULL;
			
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS							
            if ( doTransEffect )
                {
    		TRect demarcation;
    		CAknTransitionUtils::GetDemarcation(CAknTransitionUtils::EPopup, 
    		                                    demarcation);
    		    GfxTransEffect::SetDemarcation(this, demarcation);
    		
    		    GfxTransEffect::NotifyExternalState(ECaptureComponentsEnd, (const TDesC8*)this);
    		    GfxTransEffect::End(this);
    		    		    		
    		    if( !CAknEnv::Static()->TransparencyEnabled() && rsWasEnabled )
                    {
                    // if redrawstore was on before transition,
                    // enable it again
                    Window().EnableRedrawStore( ETrue );
                    }
                CAknTransitionUtils::RemoveData(EDontAnimateBitmaps); 
                }
 #endif // RD_UI_TRANSITION_EFFECTS_POPUPS	   		
            break;
			}
        case EProcessOnDisplayOn:
            iState = EProcessOnDisplayOnCanBeDismissed;
            delete iProgressDialogTimer;
            iProgressDialogTimer = NULL;
            break;
        case EProcessOffDisplayOff:
        case EProcessOffDisplayOn:
            delete iProgressDialogTimer;
            iProgressDialogTimer = NULL;
            ReportUserActivity();
            PlayTone();
            TRAP_IGNORE(TryExitL( EAknSoftkeyDone ));
            break;
        default:
            delete iProgressDialogTimer;
            iProgressDialogTimer = NULL;
        }
    return KErrNone;
    }

EXPORT_C void CAknProgressDialog::ProcessFinishedL()
    {        
        switch ( iState )
        {
        case EProcessOnDisplayOff:
        case EProcessOnDisplayOnCanBeDismissed:
            iState = EProcessOffDisplayOff;
            delete iProgressDialogTimer;
            iProgressDialogTimer = NULL;
            ReportUserActivity();
            PlayTone();
            TryExitL( EAknSoftkeyDone );
            break;
        case EProcessOnDisplayOn:
            iState = EProcessOffDisplayOn;
            break;
		default:
			break;
        }
    }

EXPORT_C TInt CAknProgressDialog::RunLD()
	{
    CAknNoteControl* note = NoteControl();
	note->CreateProgressBarL();

	if (iInternalTimerControl)
        {
        if ( ((iModel.iFinalValue/iModel.iIncrement*iModel.iHundreths)*10000) < KMinProcessTimeToShowDialog )
            {
            CleanupStack::Pop(); // this
            TryExitL( EAknSoftkeyDone );
            return 0;
            }
        iState = EProcessOnDisplayOn;
	    iModel.iRunning = ETrue;
	    iEikonEnv->EikAppUi()->AddToStackL(this,ECoeStackPriorityDialog,ECoeStackFlagRefusesAllKeys);
        return (CAknNoteDialog::RunLD());
        }

    iProgressDialogTimer = CPeriodic::NewL(CActive::EPriorityStandard);
    if ( !iVisibilityDelayOff )
        {
        //TR deregister since we'll show this transition in callback
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS                           
         GfxTransEffect::Deregister( this );
#endif        
        iState = EProcessOnDisplayOff;
        // start timer
        iProgressDialogTimer->Start(TTimeIntervalMicroSeconds32(KMinProcessTimeToShowDialog),
                                    TTimeIntervalMicroSeconds32(KMinTimeDialogOnScreen), 
                                    TCallBack(DialogTimerCallback, this) );
        // Make the dialog unvisible
        ButtonGroupContainer().MakeVisible(EFalse);
        MakeVisible(EFalse);
        // Add to stack to capture key events. This prevents user to continue working while
        // the dialog is unvisible
        iEikonEnv->EikAppUi()->AddToStackL(this,ECoeStackPriorityDialog);
        // Allow detection and cancellation as a dialog while hidden
        delete iCancelWhileHidden;
        iCancelWhileHidden = NULL;
        iCancelWhileHidden = CCancelWhileHidden::NewL(this);
        }
    else
        {
		MakeVisible( ETrue );
		ButtonGroupContainer().MakeVisible( ETrue );		
		
        iState = EProcessOnDisplayOn;
        // start timer
        iProgressDialogTimer->Start(TTimeIntervalMicroSeconds32(KMinTimeDialogOnScreen),
                                    TTimeIntervalMicroSeconds32(KMinTimeDialogOnScreen), 
                                    TCallBack(DialogTimerCallback, this) );
        
        iEikonEnv->EikAppUi()->AddToStackL(this,ECoeStackPriorityDialog,ECoeStackFlagRefusesAllKeys);
        }

    return CAknNoteDialog::RunLD();
    }

EXPORT_C CEikProgressInfo* CAknProgressDialog::GetProgressInfoL()
	{
	CAknNoteControl* note = NoteControl();
    if ( !(note->GetProgressInfo()) )
        {
    	note->CreateProgressBarL();
        }
    return note->GetProgressInfo();
	}

EXPORT_C TKeyResponse CAknProgressDialog::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
	{
    if ( aType != EEventKey )
        {
        return CAknNoteDialog::OfferKeyEventL(aKeyEvent,aType);        
        }

    TInt cmdLeft = ButtonGroupContainer().ButtonGroup()->CommandId(0);
    TInt cmdRight = ButtonGroupContainer().ButtonGroup()->CommandId(2);
    if ( iState != EProcessOnDisplayOff )
        {
        // If left softkey is empty, disable ok key
        if ( aKeyEvent.iCode == EKeyOK && 
            ( cmdLeft == 0 || cmdLeft == EAknSoftkeyEmpty ) )
            {
            return EKeyWasConsumed;
            }
         // If LSK and RSK are both empty, let note ignores enter key.
         if (cmdLeft == EAknSoftkeyEmpty &&  cmdRight== EAknSoftkeyEmpty &&
             aKeyEvent.iCode == EKeyEnter)
            {
            return EKeyWasConsumed;
            }
            
	    return CEikDialog::OfferKeyEventL(aKeyEvent,aType);
        }
    else
        { // a dialog should ALWAYS be dismissed on the escape key.
		if (aType == EEventKey  && aKeyEvent.iCode == EKeyEscape)
		    return CEikDialog::OfferKeyEventL(aKeyEvent,aType);
        return EKeyWasConsumed;
        }
	}

EXPORT_C TBool CAknProgressDialog::OkToExitL(TInt aButtonId)
    {
    // if dialog is invisible and app isn't exiting, eg during view switch,
    // don't stop the progress dialog - it's most likely part of some
    // asynchronous operation.
    if ((iState == EProcessOnDisplayOff && !CAknEnv::AppWithShutterRunning()) || 
    	aButtonId == EAknSoftkeyEmpty )
        {
		delete iCancelWhileHidden;
		iCancelWhileHidden = NULL;
        return EFalse;
        }
    if ( iCallback )
        {
        iCallback->DialogDismissedL(aButtonId);
        }
    return ETrue;
    }
        
//-------------------------------------------------------------------------------------
// CAknProgressDialog::HandlePointerEventL()
// Empty implementation to overwrite the implementation of CAknNoteDialog.
// CAknNoteDialog closes it self when up pointer event is captured. This 
// should not.
//-------------------------------------------------------------------------------------
//
EXPORT_C void CAknProgressDialog::HandlePointerEventL(const TPointerEvent& /*aPointerEvent*/ ) 
    { 
	// Empty overwriting of function
    }    

EXPORT_C void* CAknProgressDialog::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

EXPORT_C void CAknProgressDialog::SetCallback(MProgressDialogCallback* aCallback)
    {
    iCallback = aCallback;
    }
    
EXPORT_C void CAknProgressDialog::CEikDialog_Reserved_1()
    {
    }

EXPORT_C void CAknProgressDialog::CEikDialog_Reserved_2()
    {
    }

EXPORT_C void CAknProgressDialog::CAknNoteDialog_Reserved()
    {
    }

// End of File
