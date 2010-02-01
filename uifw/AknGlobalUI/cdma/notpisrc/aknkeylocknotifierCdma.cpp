// PLEASE NOTE: THIS FILE HAS NOT YET BEEN MIGRATED TO NEW NOTIFIER SYSTEM !!!

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
* Description: Avkon KeyLock Notifier
*
*/


#include "AknKeyLockNotifier.h"
#include "AknNotifyPlugin.h"
#include "AknNotifyPlugin.hrh"

#include <aknnotpi.rsg>
#include <eikenv.h>
#include <eikappui.h>
#include <aknkeys.h>
#include <coedef.h>

#include <uikon/eiksrvui.h>
#include <eikon.hrh>
#include <apgwgnam.h>
#include <aknsoundsystem.h>
#include <avkon.rsg>
#include <akndlgshut.h>
#include <eikkeysound.h>
#include <bautils.h>
#include <FeatMgr.h>

#include <aknlayout.lag>
#include <aknutils.h>
#include <eikcba.h>
#include <aknsconstants.h>
#include <aknnotecontrol.h>
#include <AknLayoutScalable_Avkon.cdl.h>

#ifdef __COVER_DISPLAY
#include "AknPublishToCoverUI.h"
#endif // __COVER_DISPLAY

#include <AknNotifySignature.h>

#include <AiwServiceHandler.h>
#include <AiwCommon.hrh>

#include <akntashook.h>
#define KSysApUid TUid::Uid(0x100058F3)

const TInt KAknObserverListGranularity = 4;
const TInt KAknOfferKeyLockTimeout = 6000000; // 6sec

const TInt KNoteCmdFocusLost = 3100;

const TUint KAknAsterisk = '*';
const TUint KAknHash = '#';
const TInt KKeyLockControlAnyKey = 3300;    // phone query

_LIT(KRESOURCEFILE,"z:\\private\\10003a4a\\aknnotpi.rsc");

// CAknLockedNote

CAknLockedNote::CAknLockedNote(TInt& aLocked, MEikCommandObserver* aCommandObserver)
:CAknSleepingNote(aCommandObserver), iLocked(aLocked)
    {
    AKNTASHOOK_ADD( this, "CAknLockedNote" );
    }

TBool CAknLockedNote::OkToExitL(TInt aCommand)
    {
    iLocked = EFalse;

    if (iCommandObserver)
        {
        iCommandObserver->ProcessCommandL(aCommand);
        }

    return ETrue;
    }

CAknLockedNote::~CAknLockedNote()
    {
    AKNTASHOOK_REMOVE();
    iLocked = EFalse;
    }

void CAknLockedNote::CancelNote()
    {
    if ( iTimer )
        iTimer->Cancel();
    CAknNoteControl* ctrl = 0;
    ctrl = NoteControl();
    if ( ctrl )
        { // if there is no animation, just returns KErrGeneral
        ctrl->CancelAnimation();
        }
    ExitSleepingDialog();
    iLocked = EFalse;
    }

void CAknLockedNote::FocusChanged(TDrawNow /*aDrawNow*/)
    {
    if (!IsFocused() &&  iCommandObserver)
        {
        TRAP_IGNORE(iCommandObserver->ProcessCommandL(KNoteCmdFocusLost))
        }
    }


void CAknLockedNote::CEikDialog_Reserved_1()
    {
    }

void CAknLockedNote::CEikDialog_Reserved_2()
    {
    }

void CAknLockedNote::CAknNoteDialog_Reserved()
    {
    }

void CAknLockedNote::CAknSleepingNote_Reserved()
    {
    }


CAknSleepingNote::CAknSleepingNote(MEikCommandObserver* aCommandObserver)
:iCommandObserver(aCommandObserver)
    {
    AKNTASHOOK_ADD( this, "CAknSleepingNote" );
    }


void CAknSleepingNote::ConstructSleepingNoteL(TInt aResourceId)
    {
    iResourceId = aResourceId;
    CAknNoteDialog::ConstructSleepingDialogL(aResourceId);
    // Construct now rather than in PreLayoutDynInit
    delete iTimer;
    iTimer = 0;

    iTimer = CPeriodic::NewL(0);
    }

TInt CAknSleepingNote::ShowNote(const TTimeout aTimeout,const TTone aTone)
    {
    ReportUserActivity();
    iTimeoutInMicroseconds = aTimeout;
    iTone = aTone;
    return RouseSleepingDialog();
    }

TBool CAknSleepingNote::OkToExitL(TInt aCommand)
    {
    if (iCommandObserver)
        {
        iCommandObserver->ProcessCommandL(aCommand);
        }
    return ETrue;
    }

void CAknSleepingNote::HandleResourceChange(TInt aType)
    {
    if( aType == KAknsMessageSkinChange )
        {
        TInt animationRes(0);
        switch (iResourceId)
            {
        case R_KEYLOCK_NOTE_KEYLOCKED:
            animationRes = R_QGN_NOTE_INFO_ANIM;
            break;
        case R_KEYLOCK_NOTE_UNLOCK_CONFIRM:
            animationRes = R_QGN_NOTE_QUERY_ANIM;
            break;
        case R_KEYLOCK_NOTE_UNLOCK_ASTERISK:
            animationRes = R_QGN_NOTE_INFO_ANIM;
            break;
        case R_KEYLOCK_NOTE_LOCK_ON:
            animationRes = R_QGN_NOTE_KEYGUARD_LOCKED_ANIM;
            break;
        case R_KEYLOCK_NOTE_LOCK_OFF:
            animationRes = R_QGN_NOTE_KEYGUARD_OPEN_ANIM;
            break;
        case R_KEYLOCK_OFFER_LOCK_NOTE:
            animationRes = R_QGN_NOTE_QUERY_ANIM;
            break;
        default:
            break;
        } // end of switch

        if (animationRes)
            {
            CAknNoteControl* ctrl = 0;
            ctrl = NoteControl();
            if ( ctrl )
                {
                TRAP_IGNORE( ctrl->SetAnimationL( animationRes ));
                }
            }

        }

    CAknNoteDialog::HandleResourceChange(aType);
    }


void CAknSleepingNote::CEikDialog_Reserved_1()
    {
    }

void CAknSleepingNote::CEikDialog_Reserved_2()
    {
    }

void CAknSleepingNote::CAknNoteDialog_Reserved()
    {
    }

void CAknSleepingNote::CAknSleepingNote_Reserved()
    {
    }


/**
* Private class to implement the emergency number display during keylock
*
*/
class CAknEcsNote: public CAknSleepingNote
    {
public:
    /**
    * Constructor
    */
    CAknEcsNote( MEikCommandObserver* aCommandObserver );
    /**
    * API to set the emergency number to be displayed
    *
    * aMatchedNumber    text to display (e.g. "112" )
    */
    void SetEmergencyNumber( const TDesC& aMatchedNumber );
    /**
    * Dismisses the sleeping note.
    */
    void SleepNote();

    TBool iNoteOnScreen;
    };

CAknEcsNote::CAknEcsNote( MEikCommandObserver* aCommandObserver ) : CAknSleepingNote( aCommandObserver )
    {}

void CAknEcsNote::SetEmergencyNumber( const TDesC& aMatchedNumber )
    {
    TRect screen(iAvkonAppUi->ApplicationRect());
    TAknLayoutRect mainPane;
    mainPane.LayoutRect(screen, AKN_LAYOUT_WINDOW_main_pane(screen, 0, 1, 1));
    TAknLayoutRect popupNoteWindow;
    AknLayoutUtils::TAknCbaLocation cbaLocation( AknLayoutUtils::CbaLocation() );
	TInt variety( 0 );
    if ( cbaLocation == AknLayoutUtils::EAknCbaLocationRight )
		{
		variety = 5;
		}
	else if ( cbaLocation == AknLayoutUtils::EAknCbaLocationLeft )
		{
		variety = 8;
		}
	else
		{
		variety = 2;
		}

    popupNoteWindow.LayoutRect(mainPane.Rect(), AknLayoutScalable_Avkon::popup_note_window( variety ));
    TAknLayoutText textRect;
    textRect.LayoutText(popupNoteWindow.Rect(), AKN_LAYOUT_TEXT_Note_pop_up_window_texts_Line_1(4));

    // Size of a temporary buffer that contains new lines, spaces and 
    // emergency number for a note.
    TBuf16<KAknEcsMaxMatchingLength+80> number;
    number.Append('\n');
    number.Append('\n');

    TInt spaceCharWidthInPixels = textRect.Font()->CharWidthInPixels(' ');
    if (spaceCharWidthInPixels < 1)
        {
        // Avoid divide by zero situation even the space char would have zero length.
        spaceCharWidthInPixels = 1;
        }
    
    TInt length = (textRect.TextRect().Width() - textRect.Font()->TextWidthInPixels(aMatchedNumber))
                    / spaceCharWidthInPixels;

    const TInt matchedNumberLength = aMatchedNumber.Length();
    const TInt numberLength = number.Length();
    const TInt numberMaxLength = number.MaxLength();
    
    if ( numberLength + length + matchedNumberLength > numberMaxLength)
        {
        // To make sure that buffer overflow does not happen.
        length = numberMaxLength - numberLength - matchedNumberLength;
        }
    for (int i = 0; i < length ; i++)
        {
        number.Append(' ');
        }

    number.Append(aMatchedNumber);
    TRAP_IGNORE(SetTextL(number));

    }

void CAknEcsNote::SleepNote()
    {
    if (iNoteOnScreen)
        ExitSleepingDialog(); // Causes flicker to other notes if called when note is not on screen
    iNoteOnScreen = EFalse;
    }

//CaknLockedPhoneQuery
CAknLockedPhoneQuery* CAknLockedPhoneQuery::NewL( TDes& aDataText )
    {
    CAknLockedPhoneQuery* self =
        new(ELeave) CAknLockedPhoneQuery( aDataText );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    AKNTASHOOK_ADDL( self, "CAknLockedPhoneQuery" );
    return self;
    }

CAknLockedPhoneQuery::~CAknLockedPhoneQuery()
    {
    AKNTASHOOK_REMOVE();
    if ( iInactivityTimer )
        {
        iInactivityTimer->Cancel();
        delete iInactivityTimer;
        }
    }

CAknLockedPhoneQuery::CAknLockedPhoneQuery(TDes& aDataText)
    : CAknTextQueryDialog(aDataText)
    {
    }

void CAknLockedPhoneQuery::ConstructL()
    {
    iInactivityTimer = CPeriodic::NewL(CActive::EPriorityUserInput);
    TCallBack callback(InactivityExitL, this);
    iInactivityTimer->Start(KEcsInterKeyTimeout,
        KEcsInterKeyTimeout, callback);
    }

TKeyResponse CAknLockedPhoneQuery::OfferKeyEventL(const TKeyEvent& aKeyEvent,
                                                  TEventCode aType)
    {
    ResetInactivityTimer();
    if(aKeyEvent.iCode == EKeyPhoneSend || aKeyEvent.iCode == EKeyOK)
        {
        TryExitL(EAknSoftkeyCall);
        return EKeyWasConsumed;
        }
    if(aKeyEvent.iCode == EKeyPhoneEnd)
        {
        TryExitL(EAknSoftkeyCancel);
        return EKeyWasConsumed;
        }
    return CAknTextQueryDialog::OfferKeyEventL(aKeyEvent, aType);
    }

void CAknLockedPhoneQuery::ResetInactivityTimer()
    {
    iInactivityTimer->Cancel();
    TCallBack callback(InactivityExitL, this);
    iInactivityTimer->Start(KEcsInterKeyTimeout,
        KEcsInterKeyTimeout, callback);
    }

TInt CAknLockedPhoneQuery::InactivityExitL(TAny *aThis)
    {
    static_cast<CAknLockedPhoneQuery*>(aThis)->DoInactivityExitL();
    return 0;
    }

void CAknLockedPhoneQuery::DoInactivityExitL()
    {
    TryExitL(EEikBidCancel);
    }

//CAknKeyLockControl

CAknKeyLockControl::CAknKeyLockControl()
    {
    AKNTASHOOK_ADD( this, "CAknKeyLockControl" );
    }

CAknKeyLockControl::CAknKeyLockControl(CAknKeyLockNotifierSubject* aNotif):iNotif(aNotif)
    {
    AKNTASHOOK_ADD( this, "CAknKeyLockControl" );
    }

CAknKeyLockControl::~CAknKeyLockControl()
    {
    AKNTASHOOK_REMOVE();
    FeatureManager::UnInitializeLib();
    iEikonEnv->EikAppUi()->RemoveFromStack(this);
    delete iConfirmationNote;
    //Show note "Now press *".
    //Note is shown when user has pressed "Unlock" when keypad is in locked state
    delete iConfirmationNoteAsterisk;
    delete iLockedNote;
    delete iKeypadUnlockedNote;
    delete iKeypadLockedNote;
    delete iEcsDetector;
    delete iKeyLockCba;
    delete iOfferLockNote;
    delete iEcsNote; // Ecs change
    }

void CAknKeyLockControl::ConstructL()
    {
    FeatureManager::InitializeLibL();
    iFeatureKeypadNoSlider =
        FeatureManager::FeatureSupported( KFeatureIdKeypadNoSlider );

    CreateWindowL();
    Window().SetSize(TSize(0,0));

    ActivateL();

    iEikonEnv->EikAppUi()->AddToStackL(this,ECoeStackPriorityEnvironmentFilter+10,ECoeStackFlagRefusesFocus);

    iKeyLockCba = CEikButtonGroupContainer::NewL(CEikButtonGroupContainer::ECba, CEikButtonGroupContainer::EHorizontal, this, R_KEYLOCK_SOFTKEYS_UNLOCK_EMPTY);
    iKeyLockCba->ButtonGroup()->AsControl()->DrawableWindow()->SetOrdinalPosition(ECoeWinPriorityNeverAtFront);
//    const TSize screenSize=TSize(AKN_LAYOUT_WINDOW_screen.iW,AKN_LAYOUT_WINDOW_screen.iH);  // Ok so far. 'screen' layout used.
    const TSize screenSize( iAvkonAppUi->ApplicationRect().Size() );
    iKeyLockCba->MakeVisible(EFalse);
    iKeyLockCba->SetBoundingRect(TRect(screenSize));

    iEcsNote = new (ELeave) CAknEcsNote( this );
    iEcsNote->ConstructSleepingNoteL(R_AVKON_EMERGENCY_CALL_NOTE);
    iEcsNote->ButtonGroupContainer().ButtonGroup()->AsControl()->DrawableWindow()->SetOrdinalPosition(0,2);

    iOfferLockNote = new(ELeave)CAknLockedNote(iOfferLockEnabled, this);
    iOfferLockNote->ConstructSleepingNoteL(R_KEYLOCK_OFFER_LOCK_NOTE);
    iOfferLockNote->ButtonGroupContainer().ButtonGroup()->AsControl()->DrawableWindow()->SetOrdinalPosition(0,2);

    iKeypadLockedNote = new(ELeave)CAknSleepingNote();
    iKeypadLockedNote->ConstructSleepingNoteL(R_KEYLOCK_NOTE_LOCK_ON);
    iKeypadLockedNote->ButtonGroupContainer().ButtonGroup()->AsControl()->DrawableWindow()->SetOrdinalPosition(0,2);

    iKeypadUnlockedNote = new(ELeave)CAknSleepingNote();
    iKeypadUnlockedNote->ConstructSleepingNoteL(R_KEYLOCK_NOTE_LOCK_OFF);
    iKeypadUnlockedNote->ButtonGroupContainer().ButtonGroup()->AsControl()->DrawableWindow()->SetOrdinalPosition(0,2);

    iLockedNote = new (ELeave)CAknLockedNote(iLockedNoteDisplayed);
    iLockedNote->ConstructSleepingNoteL(R_KEYLOCK_NOTE_KEYLOCKED);
    iLockedNote->ButtonGroupContainer().ButtonGroup()->AsControl()->DrawableWindow()->SetOrdinalPosition(0,2);

    iConfirmationNote = new (ELeave) CAknLockedNote(iUnlockConfirmation);
    iConfirmationNote->ConstructSleepingNoteL(R_KEYLOCK_NOTE_UNLOCK_CONFIRM);
    iConfirmationNote->ButtonGroupContainer().ButtonGroup()->AsControl()->DrawableWindow()->SetOrdinalPosition(0,2);

    if ( iFeatureKeypadNoSlider )
        {
        //Show note "Now press *".
        //Note is shown when user has pressed "Unlock" when keypad is in locked state
        iConfirmationNoteAsterisk = new (ELeave) CAknLockedNote(iUnlockConfirmation);
        iConfirmationNoteAsterisk->ConstructSleepingNoteL(R_KEYLOCK_NOTE_UNLOCK_ASTERISK);
        iConfirmationNoteAsterisk->ButtonGroupContainer().ButtonGroup()->AsControl()->DrawableWindow()->SetOrdinalPosition(0,2);
        }
    // Emergency call support
    iEcsDetector = CAknEcsDetector::NewL();
    iEcsDetector->SetObserver( this );

    iPhoneQueryOnScreen = EFalse;
    iPhoneNumber.Zero();
    }


void CAknKeyLockControl::EnableKeylock(TBool aShowNote)
    {
    if (iOfferLockEnabled)
        {
        iOfferLockNote->CancelNote();
        }
    iKeyLockEnabled = ETrue;

    if (!iAutolockEnabled)
        SendMessageToSysAp(EEikKeyLockEnabled);
    iKeyLockCba->MakeVisible(ETrue);

    TBool areWeInIdleState = CEikStatusPaneBase::Current()->PaneCapabilities(TUid::Uid(EEikStatusPaneUidClock)).IsInCurrentLayout();
        if (areWeInIdleState)
        { // idle state
        ((CEikCba*)iKeyLockCba->ButtonGroup())->SetSkinBackgroundId(KAknsIIDQsnBgAreaControlIdle);
        }
        else
            {
        ((CEikCba*)iKeyLockCba->ButtonGroup())->SetSkinBackgroundId(KAknsIIDQsnBgAreaControl);
        }

    iEikonEnv->BringForwards(ETrue);

    if ( aShowNote )
        DisplayLockedNote();
    ShowKeylockCba();
    CaptureSystemKeys();
    iEcsDetector->ConnectToEventSource();

    if ( iNotif )
        {
        iNotif->NotifyStatusChange(EKeyLockEnabled);
        }

    if ( !iSoundsMuted )
        {
        CAknAppUiBase* appUi = iAvkonAppUiBase;
        TRAPD(err, appUi->KeySounds()->PushContextL(R_AVKON_SILENT_SKEY_LIST));
        if ( !err )
            {
            appUi->KeySounds()->BringToForeground();
            appUi->KeySounds()->LockContext();
            iSoundsMuted = ETrue;
            }
        }
    }

void CAknKeyLockControl::DisableKeylock()
    {
    if ( iSoundsMuted )
        {
        CAknAppUiBase* appUi = iAvkonAppUiBase;
        appUi->KeySounds()->ReleaseContext();
        appUi->KeySounds()->PopContext();
        }

    iEcsDetector->CloseEventSource();
    UnCaptureSystemKeys();
    iEikonEnv->BringForwards(EFalse);
    iKeyLockCba->ButtonGroup()->AsControl()->DrawableWindow()->SetOrdinalPosition(ECoeWinPriorityNeverAtFront);
    iKeyLockCba->MakeVisible(EFalse);
    iKeyLockEnabled = EFalse;
    if (!iAutolockEnabled)
        SendMessageToSysAp(EEikKeyLockDisabled);
    if ( iNotif )
        {
        iNotif->NotifyStatusChange(EKeyLockDisabled);
        }
    iAutolockEnabled = EFalse;
    }

void CAknKeyLockControl::SendMessageToSysAp(TInt aMessage)
    {
    RWsSession& ws = iEikonEnv->WsSession();
    TInt wgId=0;
    CApaWindowGroupName::FindByAppUid(KSysApUid, ws, wgId);
    if (wgId)
        {
        TWsEvent event;
        event.SetType(aMessage);
        event.SetTimeNow();
        ws.SendEventToWindowGroup(wgId, event);
        }
    }

void CAknKeyLockControl::OfferKeylock()
    {
    iOfferLockNote->ShowNote((CAknNoteDialog::TTimeout)KAknOfferKeyLockTimeout, CAknNoteDialog::ENoTone);
    iOfferLockEnabled = ETrue;
    }


void CAknKeyLockControl::DisplayLockedNote()
    {
    if ( !iAutolockEnabled )
        {
    iKeypadLockedNote->ShowNote(CAknNoteDialog::EShortTimeout,CAknNoteDialog::ENoTone);
#ifdef __COVER_DISPLAY
#ifdef __SERIES60_30__ // different code for 3.0 and 2.8
        SAknKeyguardNotePS params;
        params.iIsLocked = ETrue;
        params.iTimeout = CAknNoteDialog::EShortTimeout;
        params.iTone = CAknNoteDialog::ENoTone;
        TRAP_IGNORE( AknPublishToCoverUI::PublishKeyguardNoteL( params ) );
#else // 2.8
        SAknKeyguardNotePSParams params;
        params.iIsLocked = ETrue;
        params.iTimeout = CAknNoteDialog::EShortTimeout;
        TRAP_IGNORE( AknPublishToCoverUI::PublishKeyguardNoteL( params ) );
#endif // __SERIES60_30__
#endif // __COVER_DISPLAY
        }
    }

void CAknKeyLockControl::DisplayKeyActiveNote()
    {
    if ( !iAutolockEnabled )
        {
    iKeypadUnlockedNote->ShowNote(CAknNoteDialog::EShortTimeout,CAknNoteDialog::ENoTone);
#ifdef __COVER_DISPLAY
#ifdef __SERIES60_30__ // different code for 3.0 and 2.8
        SAknKeyguardNotePS params;
        params.iIsLocked = EFalse;
        params.iTimeout = CAknNoteDialog::EShortTimeout;
        params.iTone = CAknNoteDialog::ENoTone;
        TRAP_IGNORE( AknPublishToCoverUI::PublishKeyguardNoteL( params ) );
#else // 2.8
        SAknKeyguardNotePSParams params;
        params.iIsLocked = EFalse;
        params.iTimeout = CAknNoteDialog::EShortTimeout;
        TRAP_IGNORE( AknPublishToCoverUI::PublishKeyguardNoteL( params ) );
#endif // __COVER_DISPLAY
#endif // __COVER_DISPLAY
        }
    }

void CAknKeyLockControl::DoUnlock()
    {
    DisableKeylock();
    DisplayKeyActiveNote();
    }

void CAknKeyLockControl::ProcessCommandL(TInt aCommandId)
    {
    if ( aCommandId == KKeyLockControlAnyKey )
        {
        if ( !iPhoneQueryOnScreen )
            {
            iPhoneQueryOnScreen = ETrue;

            // show phone query
            ShowLockPhoneQueryL();
            }
        }
    else if (aCommandId == EAknSoftkeyUnlock)
        {
        iPhoneQueryOnScreen = EFalse;
        if ( iAutolockEnabled )
            {
            TApaTaskList aList(iCoeEnv->WsSession());
            TApaTask aTask = aList.FindApp(TUid::Uid(0x100059B5));
            if ( aTask.Exists() )
                {
                DisableKeylock();
                iNotif->NotifyStatusChange(EHideSoftNotifications);
                TKeyEvent keyEvent;
                keyEvent.iCode = EKeyBell;
                aTask.SendKey(keyEvent);
                SendMessageToSysAp(EEikKeyLockPowerKeyPressed);
                }
            // else we do nothing, Autolock application was not ready yet.
            }
        else
            {
            if ( iFeatureKeypadNoSlider )
                {
                //Show note "Now press *".
                //Note is shown when user has pressed "Unlock" when keypad is in locked state
                iConfirmationNoteAsterisk->ShowNote(
                    CAknNoteDialog::EShortTimeout,CAknNoteDialog::EConfirmationTone);
                }
            else
                {
                iConfirmationNote->ShowNote(
                    CAknNoteDialog::EShortTimeout,CAknNoteDialog::EConfirmationTone);
                }
            iUnlockConfirmation = ETrue;
            }
        }
    else if (aCommandId == EAknSoftkeyLock)
        {
        // Lock keys
        DoExitOfferKeylock();
        EnableKeylock();
        }
    else if (aCommandId == EAknSoftkeyExit)
        {
        // Cancel offer keylock CBA
        DoExitOfferKeylock();
        }
    else if (aCommandId == EAknSoftkeyEmpty)
        {
        if (iKeyLockEnabled)
            {
            ShowLockedNote();
            }
        }
    else if (aCommandId == KNoteCmdFocusLost)
        {
        // Locked note has become unfocusd - get rid of it
        if (iOfferLockEnabled)
            {
            DoExitOfferKeylock();
            }
        }
    }

TInt CAknKeyLockControl::CountComponentControls() const
    {
    if (iKeyLockEnabled)
        return 1;
    else
        return 0;
    }

CCoeControl* CAknKeyLockControl::ComponentControl(TInt /*aIndex*/) const
    {
    if (iKeyLockEnabled)
        return iKeyLockCba;
    else
        return NULL;
    }


TKeyResponse CAknKeyLockControl::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    if (!iOfferLockEnabled && !iKeyLockEnabled)
        return EKeyWasNotConsumed;


    if ( (aType == EEventKey && aKeyEvent.iRepeats == 0) ||
         (aType == EEventKeyDown && aKeyEvent.iScanCode == EStdKeyDevice2) // Power key
         )
        {
        // If power key pressed, tell SysAp about if
        if(aKeyEvent.iScanCode == EStdKeyDevice2)
            {
            SendMessageToSysAp(EEikKeyLockPowerKeyPressed);
            }

        if (iOfferLockEnabled)
            {
            switch (aKeyEvent.iCode)
                {
                case EKeyOK:
                    {
                    DoExitOfferKeylock();
                    EnableKeylock();
                    }
                case EKeyLeftArrow:
                case EKeyRightArrow:
                case EKeyUpArrow:
                case EKeyDownArrow:
                case EKeyApplication:
                    return EKeyWasConsumed;
                    break;
                default:
            // Normal response - send it to the cba via the control stack
            return EKeyWasNotConsumed;
                }
            }
        else if (iKeyLockEnabled)
            {
            if (iLockedNoteDisplayed)
                {
                // See if 'Unlock' has been pressed
                if (aKeyEvent.iCode == EKeyCBA1)
                    {
                    if ( iFeatureKeypadNoSlider )
                        {
                        iConfirmationNoteAsterisk->ShowNote(
                            CAknNoteDialog::EShortTimeout,
                            CAknNoteDialog::EConfirmationTone);
                        }
                    else
                        {
                        iConfirmationNote->ShowNote(
                            CAknNoteDialog::EShortTimeout,
                            CAknNoteDialog::EConfirmationTone);
                        }

                    iUnlockConfirmation = ETrue;
                    iLockedNote->CancelNote();
                    }
                // Locked note is on-screen - discard key
                return EKeyWasConsumed;
                }
            else if (iUnlockConfirmation)
                {
                // Confirmation note is on-screen - check for OK

                if ( ( aKeyEvent.iCode == KAknAsterisk && iFeatureKeypadNoSlider )
                  || ( aKeyEvent.iCode == EKeyCBA2 && !iFeatureKeypadNoSlider ) )
                    {
                    DoUnlock();
                    if ( iFeatureKeypadNoSlider )
                        {
                        //Show note "Now press *".
                        //Note is shown when user has pressed "Unlock" when keypad is in locked state
                        iConfirmationNoteAsterisk->CancelNote();
                        }
                    else
                        {
                        iConfirmationNote->CancelNote();
                        }
                    }
                else
                    {
                    if ( aKeyEvent.iCode != EKeyCBA1 )
                        ShowLockedNote();
                    }
                }
            else
                {
                // Normal response - send it to the cba
                TKeyResponse cbaResponse = iKeyLockCba->ButtonGroup()->
                    AsControl()->OfferKeyEventL(aKeyEvent, aType);

                if (cbaResponse == EKeyWasNotConsumed)
                    {
                    if ( !iFeatureKeypadNoSlider )
                        {
                        // Selection key causes same action as 'Unlock'
                        if (aKeyEvent.iCode == EKeyOK)
                            {
                            iConfirmationNote->ShowNote(
                                CAknNoteDialog::EShortTimeout,
                                CAknNoteDialog::EConfirmationTone);

                            iUnlockConfirmation = ETrue;
                            }
                        else
                            {
                            ShowLockedNote();
                            }
                        }
                    else
                        {
                        if ( !(iEcsNote->iNoteOnScreen && aKeyEvent.iCode == EKeyYes) )
                            {
                            if ( !iAutolockEnabled )
                                {
                                ShowLockedNote();
                                }
                            else
                                {
                                if(aKeyEvent.iScanCode == EStdKeyDevice2)
                                    {
                                    SendMessageToSysAp(EEikKeyLockPowerKeyPressed);
                                    return EKeyWasConsumed;
                                    }
                                switch ( aKeyEvent.iCode )
                                    {
                                    case EKeyLeftArrow:
                                    case EKeyRightArrow:
                                    case EKeyUpArrow:
                                    case EKeyDownArrow:
                                    case EKeyApplication:
                                    case EKeyCamera:
                                    case EKeyVolumeUp:
                                    case EKeyVolumeDown:
                                    case EKeySide:
                                        return EKeyWasConsumed;
                                    case EKeyOK:
                                    case EKeyPhoneSend:
                                    case EKeyPhoneEnd:
                                    case EKeyBackspace:
                                        if ( !iPhoneQueryOnScreen )
                                        {
                                            return EKeyWasConsumed;
                                        }
                                    default:
                                        break;
                                    }
                                if ( iPhoneQueryOnScreen )
                                    {
                                    return EKeyWasNotConsumed;
                                    }

                                iPhoneNumber.Zero();
                                if (aKeyEvent.iScanCode == EStdKeyHash)
                                    {
                                    iPhoneNumber.Append( KAknHash );
                                    }
                                else
                                    {
                                    iPhoneNumber.Append( aKeyEvent.iScanCode );
                                    }
                                ProcessCommandL( KKeyLockControlAnyKey );
                                }
                            }
                        }
                    }
                }
            }
        }
    return EKeyWasConsumed;
    }


void CAknKeyLockControl::ShowLockedNote()
    {
    if ( !iLockedNoteDisplayed )
        {
        DoShowLockedNote();
        }
    }


void CAknKeyLockControl::DoShowLockedNote()
    {
    if ( !iAutolockEnabled )
        {
        iLockedNote->ShowNote(CAknNoteDialog::EShortTimeout,CAknNoteDialog::ENoTone);
        iLockedNoteDisplayed = ETrue;
        }
    }

void CAknKeyLockControl::ShowKeylockCba()
    {
    RDrawableWindow* cbaWindow = iKeyLockCba->ButtonGroup()->AsControl()->DrawableWindow();
    cbaWindow->SetFaded(EFalse, RWindowTreeNode::EFadeWindowOnly);
    cbaWindow->SetOrdinalPosition(0,1);
    cbaWindow->SetNonFading(ETrue);
    }

void CAknKeyLockControl::CaptureSystemKeys()
    {
    if (!iKeysCaptured)
        {
        RWindowGroup& groupWin=iCoeEnv->RootWin();
        iAppKey = groupWin.CaptureKeyUpAndDowns(EStdKeyApplication0, 0, 0); // Capture app key
        iPowerKey = groupWin.CaptureKeyUpAndDowns(EStdKeyDevice2, 0, 0);      // Capture power key
        iVoiceKey = groupWin.CaptureKeyUpAndDowns(EStdKeyDevice6, 0, 0);      // Capture power key
        iAppKey2 = groupWin.CaptureKey(EKeyApplication0, 0, 0); // Capture app key
        iPowerKey2 = groupWin.CaptureKey(EKeyDevice2, 0, 0);      // Capture power key
        iVoiceKey2 = groupWin.CaptureKey(EKeyDevice6, 0, 0);      // Capture power key
        iLeftSoftKey = groupWin.CaptureKey(EKeyDevice0,0,0);
        iEditKey = groupWin.CaptureKey(EKeyRightShift,0,0);
        iCameraKey = groupWin.CaptureKeyUpAndDowns(EKeyCamera,0,0);
        iVolumeUpKey = groupWin.CaptureKeyUpAndDowns(EStdKeyIncVolume,0,0);
        iVolumeDownKey = groupWin.CaptureKeyUpAndDowns(EStdKeyDecVolume,0,0);
        iCameraKey2 = groupWin.CaptureKey(EKeyDevice7,0,0);
        iVolumeUpKey2 = groupWin.CaptureKey(EKeyVolumeUp,0,0);
        iVolumeDownKey2 = groupWin.CaptureKey(EKeyVolumeDown,0,0);
        iKeysCaptured = ETrue;
        }
    }

void CAknKeyLockControl::UnCaptureSystemKeys()
    {
    if (iKeysCaptured)
        {
        RWindowGroup& groupWin=iCoeEnv->RootWin();
        groupWin.CancelCaptureKeyUpAndDowns(iAppKey);
        groupWin.CancelCaptureKeyUpAndDowns(iPowerKey);
        groupWin.CancelCaptureKeyUpAndDowns(iVoiceKey);
        groupWin.CancelCaptureKey(iAppKey2);
        groupWin.CancelCaptureKey(iPowerKey2);
        groupWin.CancelCaptureKey(iVoiceKey2);
        groupWin.CancelCaptureKey(iLeftSoftKey);
        groupWin.CancelCaptureKey(iEditKey);
        groupWin.CancelCaptureKey(iCameraKey);
        groupWin.CancelCaptureKey(iVolumeUpKey);
        groupWin.CancelCaptureKey(iVolumeDownKey);
        groupWin.CancelCaptureKey(iCameraKey2);
        groupWin.CancelCaptureKey(iVolumeUpKey2);
        groupWin.CancelCaptureKey(iVolumeDownKey2);
        iKeysCaptured = EFalse;
        }
    }

void CAknKeyLockControl::HandleEcsEvent( CAknEcsDetector* aEcsDetector, CAknEcsDetector::TState aState )
    {
    switch ( aState )
        {
        case CAknEcsDetector::ECompleteMatchThenSendKey:
            // Do nothing since note will be removed on ECallAttempted event
            break;
        case CAknEcsDetector::ECompleteMatch:
            if ( !iPhoneQueryOnScreen )
                {
                iEcsNote->SetEmergencyNumber( aEcsDetector->CurrentMatch() );
                iEcsNote->ShowNote( CAknNoteDialog::ENoTimeout,CAknNoteDialog::ENoTone );

                // Tell sysAp to switch lights on
                SendMessageToSysAp(EEikKeyLockPowerKeyPressed);
                iEcsNote->iNoteOnScreen =ETrue;
                }
            break;
        case CAknEcsDetector::EPartialMatch:
            iEcsNote->SleepNote();
            break;
        case CAknEcsDetector::ECallAttempted:
            iEcsNote->SleepNote();
            break;
        case CAknEcsDetector::EEmpty:
            iEcsNote->SleepNote();
            break;
        case CAknEcsDetector::ENoMatch:
            iEcsNote->SleepNote();
            break;
        default:
            break;
        }

    }

void CAknKeyLockControl::DoExitOfferKeylock()
    {
    iOfferLockNote->CancelNote();
    }

void CAknKeyLockControl::OfferTimerExpired()
    {
    DoExitOfferKeylock();
    }

void CAknKeyLockControl::AutolockEnabled(TBool aAutoLockOn)
    {
    iAutolockEnabled = aAutoLockOn;
    }

void CAknKeyLockControl::CallNumberL( TDesC& aNumber )
    {
    CAiwServiceHandler* serviceHandler;
    serviceHandler = CAiwServiceHandler::NewL();
    serviceHandler->AttachL(R_AKNNOTIFYPLUGIN_INTEREST);

    TAiwDialDataV1 dialData = TAiwDialDataV1();
    dialData.SetTelephoneNumber(aNumber);
    dialData.SetCallType(EAiwVoice);
    TAiwDialDataV1Pckg dialDataPckg = TAiwDialDataV1Pckg(dialData);
    CAiwGenericParamList& paramList = serviceHandler->InParamListL();
    TPtrC8 ptr;
    ptr.Set(dialDataPckg);
    TAiwVariant variant(ptr);
    TAiwGenericParam param(EGenericParamCallDialDataV1, variant);
    paramList.AppendL(param);

    serviceHandler->ExecuteServiceCmdL(KAiwCmdCall,
                                        paramList,
                                        serviceHandler->OutParamListL(),
                                        0,
                                        NULL);
    }

void CAknKeyLockControl::ShowLockPhoneQueryL()
    {
    iKeyLockCba->MakeVisible(EFalse);

    HBufC* phoneNumber = HBufC::NewLC(KPhoneNumberMaxLength);
    phoneNumber->Des() = iPhoneNumber;
    TPtr phonePtr(phoneNumber->Des());

    CAknLockedPhoneQuery* phoneQuery = CAknLockedPhoneQuery::NewL(phonePtr);
    TInt queryAction = phoneQuery->ExecuteLD(R_AVKON_LOCK_PHONE_QUERY);
    switch(queryAction)
        {
        case EAknSoftkeyCall:
            CallNumberL(phonePtr);
            break;
        default:
            break;
        }

    iPhoneQueryOnScreen = EFalse;
    CleanupStack::PopAndDestroy(phoneNumber);

    iKeyLockCba->MakeVisible(ETrue);
    }

// CAknKeyLockNotifierSubject

CAknKeyLockNotifierSubject* CAknKeyLockNotifierSubject::NewL()
    {
    CAknKeyLockNotifierSubject* self = new(ELeave)CAknKeyLockNotifierSubject();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }


void CAknKeyLockNotifierSubject::ConstructL()
    {
    CCoeEnv* environment = CCoeEnv::Static();

    TFileName resourceFile;
    resourceFile.Append(KRESOURCEFILE);
    BaflUtils::NearestLanguageFile(environment->FsSession(),resourceFile);

    iResourceFileOffset = environment->AddResourceFileL(resourceFile);

    iObserverList = new(ELeave)CArrayPtrFlat<MAknKeyLockObserver>(KAknObserverListGranularity);
    iKeyLockControl = new(ELeave)CAknKeyLockControl(this);
    iKeyLockControl->ConstructL();
    // Make sure AppUi has a pointer to this
    STATIC_CAST(CEikServAppUi*,CEikonEnv::Static()->AppUi())->iKeyLockController = this;
    }

CAknKeyLockNotifierSubject::CAknKeyLockNotifierSubject()
:iAllowNotifications(ETrue)
    {
    }


CAknKeyLockNotifierSubject::~CAknKeyLockNotifierSubject()
    {
    if ( iResourceFileOffset )
        CCoeEnv::Static()->DeleteResourceFile(iResourceFileOffset);
    delete iKeyLockControl;
    delete iObserverList;
    }

void CAknKeyLockNotifierSubject::Release()
    {
    delete this;
    }

CAknKeyLockNotifierSubject::TNotifierInfo CAknKeyLockNotifierSubject::RegisterL()
    {
    iInfo.iUid=KAknKeyLockNotifierUid;
    iInfo.iChannel=EAknNotifierChannelKeyLock;
    iInfo.iPriority=ENotifierPriorityHigh;
    return iInfo;
    }

CAknKeyLockNotifierSubject::TNotifierInfo CAknKeyLockNotifierSubject::Info() const
    {
    return iInfo;
    }

TPtrC8 CAknKeyLockNotifierSubject::StartL(const TDesC8& aBuffer)
    {
    SAknNotifierPackage<SAknKeyLockNotifierParams>* params
        = ( SAknNotifierPackage<SAknKeyLockNotifierParams>*)aBuffer.Ptr();

    if ( aBuffer.Length() < 0 || (TUint)aBuffer.Length() < sizeof(SAknNotifierPackage<SAknKeyLockNotifierParams>)
        || params->iSignature != KAKNNOTIFIERSIGNATURE )
        {
        User::Leave( KErrArgument );
        }

    switch (params->iParamData.iReason)
        {
        case ELockEnabled:
        case ELockDisabled:
        case EAllowNotifications:
        case EStopNotifications:
        case EOfferKeylock:
        case ECancelAllNotifications:
        case EEnableAutoLockEmulation:
        case EDisableWithoutNote:
        case EEnableWithoutNote:
            break;
        case EInquire:
            {
            iRetPckg().iEnabled = IsKeyLockEnabled();
            }
        default:
            break;
        }
    return iRetPckg;
    }

void CAknKeyLockNotifierSubject::StartL(const TDesC8& aBuffer, TInt /*aReplySlot*/, const RMessagePtr2& aMessage)
    {
    SAknNotifierPackage<SAknKeyLockNotifierParams>* params
        = ( SAknNotifierPackage<SAknKeyLockNotifierParams>*)aBuffer.Ptr();

    if ( aBuffer.Length() < 0 || (TUint)aBuffer.Length() < sizeof(SAknNotifierPackage<SAknKeyLockNotifierParams>)
        || params->iSignature != KAKNNOTIFIERSIGNATURE )
        {
        User::Leave( KErrArgument );
        }

    switch (params->iParamData.iReason)
        {
        case ELockEnabled:
            DoEnableKeyLock();
            break;
        case ELockDisabled:
            DoDisableKeyLock();
            break;
        case EAllowNotifications:
            DoAllowNotifications();
            break;
        case EStopNotifications:
            DoStopNotifications();
            break;
        case EOfferKeylock:
            DoOfferKeyLock();
            break;
        case ECancelAllNotifications:
            DoCancelAllNotificatons();
            break;
        case EEnableAutoLockEmulation:
            NotifyStatusChange(EShowSoftNotifications);
            LockKeys(ETrue);
            break;
        case EDisableWithoutNote:
            UnlockKeys();
            break;
        case EEnableWithoutNote:
            if (!IsKeyLockEnabled())
                {
                iKeyLockControl->EnableKeylock(EFalse);
                }
            break;
        case ECommandFSWToHideApplication:
            {
            TInt uid(0);
            TBool disable(EFalse);
            RDesReadStream readStream(aBuffer);
            readStream.ReadInt32L(); // signature
            readStream.ReadInt32L(); // op
            uid = readStream.ReadInt32L(); // uid
            disable = readStream.ReadInt32L(); // enable / disable
            STATIC_CAST(CEikServAppUi*,CEikonEnv::Static()->AppUi())->HideApplicationFromFswL(uid,disable);
            }
            break;
        default:
            break;
        };

    aMessage.Complete(KErrNone);
    }

void CAknKeyLockNotifierSubject::Cancel()
    {
    }

TPtrC8 CAknKeyLockNotifierSubject::UpdateL(const TDesC8& aBuffer)
    {
    return TPtrC8(aBuffer);
    }



TBool CAknKeyLockNotifierSubject::IsKeyLockEnabled()
    {
    return iKeyLockControl->iKeyLockEnabled;
    }

TBool CAknKeyLockNotifierSubject::AllowNotifications()
    {
    return iAllowNotifications;
    }



void CAknKeyLockNotifierSubject::UnlockKeys()
    {
    if (IsKeyLockEnabled())
        {
        iKeyLockControl->DisableKeylock();
        }
    }

void CAknKeyLockNotifierSubject::LockKeys(TBool aAutoLockOn)
    {

    // Well have to disable keylock if we are changing autolock status
    if ( iKeyLockControl->iKeyLockEnabled &&
        aAutoLockOn != iKeyLockControl->iAutolockEnabled )
        {
        iKeyLockControl->DisableKeylock();
        }

    if (!IsKeyLockEnabled())
        {
        iKeyLockControl->AutolockEnabled(aAutoLockOn);

        iKeyLockControl->EnableKeylock();
        }
    }


void CAknKeyLockNotifierSubject::AddObserverL(MAknKeyLockObserver* aObserver)
    {
#if defined(_DEBUG)
    TInt count = iObserverList->Count();
    for (TInt ii=0; ii<count; ii++)
        {
        if ( ((*iObserverList)[ii]) == aObserver)
            {
            Panic(EAknPanicKeyLockObserverAlreadyExists);
            }
        }
#endif
    iObserverList->AppendL(aObserver);

    // Make sure that the observer isn't obscuring the keylock CBA
    ShowKeylockCba();
    }


void CAknKeyLockNotifierSubject::RemoveObserver(MAknKeyLockObserver* aObserver)
    {
    TInt count = iObserverList->Count();
    for (TInt ii=0; ii<count; ii++)
        {
        if ( ((*iObserverList)[ii]) == aObserver)
            {
            iObserverList->Delete(ii);
            return;
            }
        }
#if defined(_DEBUG)
    Panic(EAknPanicKeyLockObserverNotFound);
#endif
    }


void CAknKeyLockNotifierSubject::ShowKeylockCba()
    {
    if (iKeyLockControl->iKeyLockEnabled)
        {
        iKeyLockControl->ShowKeylockCba();
        }
    }

void CAknKeyLockNotifierSubject::NotifyStatusChange(TKeyLockStatus aStatus)
    {
    TInt count = iObserverList->Count();
    for (TInt ii=count-1; ii>=0; ii--)
        {
        ((*iObserverList)[ii])->KeyLockStatusChange(aStatus);
        }
    }

void CAknKeyLockNotifierSubject::DoAllowNotifications()
    {
    TBool lastvalue = iAllowNotifications;
    iAllowNotifications = ETrue;
    NotifyStatusChange(EKeyLockAllowNotifications);
    if (!lastvalue)
        {
        CEikonEnv* env = CEikonEnv::Static();
        // To prevent this being called more than once
        env->SetAutoForwarding(ETrue);
        while (iActiveWindowCount)
            {
            env->BringForwards(ETrue);
            iActiveWindowCount--;
            }
        env->RootWin().SetOrdinalPosition(0, ECoeWinPriorityAlwaysAtFront);
        env->BringForwards(ETrue);
        env->BringForwards(EFalse);

        // Enable FSW
        STATIC_CAST(CEikServAppUi*,env->AppUi())->SuppressAppSwitching(EFalse);
        }
    }

void CAknKeyLockNotifierSubject::DoStopNotifications()
    {
    TBool lastvalue = iAllowNotifications;
    iAllowNotifications = EFalse;
    NotifyStatusChange(EKeyLockStopNotifications);
    if (lastvalue)
        {
        // To prevent this being called more than once
        // Count number of times BringForwards is needed to make EikSrvUi go to background
        iActiveWindowCount = 0;
        CEikonEnv* env = CEikonEnv::Static();
        TInt windowId = env->RootWin().Identifier();
        while (env->WsSession().GetWindowGroupOrdinalPriority(windowId) > 0)
            {
            iActiveWindowCount++;
            env->BringForwards(EFalse);
            }
        env->SetAutoForwarding(EFalse);
        STATIC_CAST(CEikServAppUi*,env->AppUi())->SuppressAppSwitching(ETrue);
        }
    }

void CAknKeyLockNotifierSubject::DoCancelAllNotificatons()
    {
    // Used when end key is pressed, to allow phone app to cancel all
    // notifications. Global notes / soft notifications that would
    // not normally be shown (out of priority) are not cancelled

    if ( IsKeyLockEnabled() )
        {
        return;
        }

    NotifyStatusChange(EKeyLockCancelNotification);

    // Send cancel key event to all other notifications, and hope they cancel

    TRAPD(err, AknDialogShutter::ShutDialogsL(*CEikonEnv::Static()));
    // Ignore error message - there's nothing more we can do
    }



void CAknKeyLockNotifierSubject::DoEnableKeyLock()
    {
    if (!IsKeyLockEnabled())
        {
        iKeyLockControl->EnableKeylock();
        }
    }

void CAknKeyLockNotifierSubject::DoDisableKeyLock()
    {
    if (IsKeyLockEnabled())
        {
        iKeyLockControl->DisableKeylock();
        // Attempt to display KeyActive note
        iKeyLockControl->DisplayKeyActiveNote();
        }
    else if (iKeyLockControl->iOfferLockEnabled)
        {
        // Remove the offer key lock CBA
        iKeyLockControl->OfferTimerExpired();
        }
    }


void CAknKeyLockNotifierSubject::DoOfferKeyLock()
    {
    if (!IsKeyLockEnabled())
        {
        NotifyStatusChange(EKeyLockOffered);
        iKeyLockControl->OfferKeylock();
        }
    }
