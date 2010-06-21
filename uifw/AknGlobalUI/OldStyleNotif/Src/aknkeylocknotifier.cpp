/*
* Copyright (c) 2002-2010 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Avkon KeyLock Notifier
*
*/

#include "AknKeyLockNotifier.h"

#include <aknnotpi.rsg>
#include <eikenv.h>
#include <eikappui.h>
#include <apgwgnam.h>
#include <aknsoundsystem.h>
#include <avkon.rsg>
#include <eikkeysound.h>
#include <bautils.h>
#include <featmgr.h>

#include <AknTasHook.h>
#include <AknUtils.h>
#include <eikcba.h>
#include <aknnotecontrol.h>
#include <aknlayoutscalable_avkon.cdl.h>

#include <secondarydisplay/AknSecondaryDisplayDefs.h>
#include <avkondomainpskeys.h> // KPSUidAvkonDomain, KAknKeyguardStatus, TAknKeyguardStatus
#include <startupdomainpskeys.h> // KStartupSecurityCodeQueryStatus
#include <coreapplicationuisdomainpskeys.h> // KCoreAppUIsAutolockStatus
#include <AknNotifySignature.h>
#include "AknCapServerEntry.h"
#include <aknglobalpopupprioritycontroller.h>
#include "GlobalWindowPriorities.h"
#include <keylockpolicyapi.h>
#include <ScreensaverInternalPSKeys.h>

#include <PSVariables.h>   // Property values
#include <coreapplicationuisdomainpskeys.h>
#include <startupdomainpskeys.h>
#include <ctsydomainpskeys.h>
#include <bafindf.h>
#include "AknNotifyPlugin.hrh"
#include "akntrace.h"


#ifdef _DEBUG
    #define TRACES(x)   x
#else
    #define TRACES(x)
#endif

/** Autolock application UID. */
const TUid KAutolockUid = { 0x100059B5 };

/** SysAp application UID. */
const TUid KSysApUid    = { 0x100058F3 };

const TInt KAknObserverListGranularity = 4;

/** Timeout for the "offer keylock" note. */
const TInt KAknOfferKeyLockTimeout = 6000000; // 6sec

/** Command ID for note focus lost. */
const TInt KNoteCmdFocusLost = 3100;

// Asterisk key code for the keylock.
const TUint KAknAsterisk = '*';
const TUint KAknChineseAsterisk = 0xFF0A;

// Timeout defined in Keylock UI spesification.
// Custom value since Avkon note TTimeout values
// don't support 1 second timeout
const TInt KKeyLockCustomShortTimeout = 1000000;

// Timeout for display locked note
const TInt KKeyLockDisplayLockedTimeout = 3000000;

_LIT( KRESOURCEFILE, "\\resource\\aknnotpi.rsc" );
_LIT_SECURITY_POLICY_C1( KWritePolicy, ECapabilityWriteDeviceData );


/**
 *  CAknKeylockScreenSaverObserver captures primary keys
 *  from screensaver when screen saver is active.
 *
 *  @lib   aknoldstylenotif.lib
 *  @since 3.2
 */
NONSHARABLE_CLASS( CAknKeylockScreenSaverObserver ): public CActive
    {
public:

    /**
    * Creates instance of the CAknKeylockScreenSaverObserver class.
    *
    * @param aWindowGroup application window group used to capture primary keys
    * @return Returns the instance just created.
    */
    static CAknKeylockScreenSaverObserver* NewL( RWindowGroup& aWindowGroup );

    /**
    * Destructor.
    */
    ~CAknKeylockScreenSaverObserver();

public:

    /**
    * Starts asynchronic listening KUidCurrentCall event
    *
    * @return KErrNone: if no errors
    * @return KErrInUse: if already listening
    */
    TInt Start();

    /**
    * Stops asynchronic listening KUidAutolockStatus event
    */
    void Stop();

public:

    /**
     *  Method handles the lock state changes.
     *
     * @param aStatus The new lock state
     */
    void SetLockStatus( TBool aKeylockEnabled, TBool aAutolockEnabled );

private: // constructors

    /**
    * C++ default constructor.
    *
    * @param aAppUi (pointer to autolock appui)
    */
    CAknKeylockScreenSaverObserver( RWindowGroup& aWindowGroup );

    /**
    * Symbian OS constructor.
    */
    void ConstructL();

private: // from CActive

    /** @see CActive::RunL() */
    void RunL();

    /** @see CActive::DoCancel() */
    void DoCancel();

private:

    /**
    * Used to capture primary keys defined in keylocking policies
    */
    void CapturePrimaryKeys( TBool aCapture );

private: // data

    // screen saver on property
    RProperty  iScreenSaverActiveProperty;

    // if screensaver is active or not
    TBool iScreenSaverActive;

    // if primary keys have been captured
    TBool iCaptured;

    // locking states
    TBool iKeylockEnabled;
    TBool iAutolockEnabled;

    // left softkey capture
    TInt iLeftSoftKey;

    // a reference to application window group
    RWindowGroup& iWindowGroup;

    // keylockpolicy support (not owned)
    CKeyLockPolicyApi* iUnlockPolicyApi;

    // keylockpolicy support (not owned)
    CKeyLockPolicyApi* iDevicelockPolicyApi;

    // primary key captures
    RArray<TUint> iPrimaryKeyCaptures;
    };

// ===========================================================================
// class CAknKeylockScreenSaverObserver
// ===========================================================================

// ---------------------------------------------------------------------------
// Constructs a new entry with given values.
// ---------------------------------------------------------------------------
//
CAknKeylockScreenSaverObserver* CAknKeylockScreenSaverObserver::NewL(
    RWindowGroup& aWindowGroup )
    {
    CAknKeylockScreenSaverObserver* self =
        new (ELeave) CAknKeylockScreenSaverObserver( aWindowGroup );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CAknKeylockScreenSaverObserver::~CAknKeylockScreenSaverObserver()
    {
    Cancel();

    // Close the property handle.
    iScreenSaverActiveProperty.Close();

    // Release key captures.
    CapturePrimaryKeys( EFalse );

    // Delete policies.
    delete iUnlockPolicyApi;
    delete iDevicelockPolicyApi;
    }


// ---------------------------------------------------------------------------
// Starts listening to the KScreenSaverOn event.
// ---------------------------------------------------------------------------
//
TInt CAknKeylockScreenSaverObserver::Start()
    {
    _AKNTRACE_FUNC_ENTER;
    
    if ( IsActive() )
        {
        return KErrInUse;
        }
    iStatus = KRequestPending;
    iScreenSaverActiveProperty.Subscribe( iStatus );
    SetActive();
    
    _AKNTRACE_FUNC_EXIT;
    
    return KErrNone;
    }


// ---------------------------------------------------------------------------
// Stops listening to the KScreenSaverOn event.
// ---------------------------------------------------------------------------
//
void CAknKeylockScreenSaverObserver::Stop()
    {
    _AKNTRACE_FUNC_ENTER;
    
    if ( !IsActive() )
        {
        return;
        }
    Cancel();
    iScreenSaverActiveProperty.Cancel();
    
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// C++ constructor
// ---------------------------------------------------------------------------
//
CAknKeylockScreenSaverObserver::CAknKeylockScreenSaverObserver(
    RWindowGroup& aWindowGroup )
    : CActive( 0 ),
      iScreenSaverActive( EFalse ),
      iCaptured( EFalse ),
      iKeylockEnabled( EFalse ),
      iAutolockEnabled( EFalse ),
      iLeftSoftKey( NULL ),
      iWindowGroup( aWindowGroup )
    {
    }


// ---------------------------------------------------------------------------
// Second phase constructor.
// ---------------------------------------------------------------------------
//
void CAknKeylockScreenSaverObserver::ConstructL()
    {
    _AKNTRACE_FUNC_ENTER;
    
    // Add this active object to the scheduler.
    CActiveScheduler::Add( this );
    User::LeaveIfError( iScreenSaverActiveProperty.Attach( KPSUidScreenSaver,
                                                           KScreenSaverOn ) );

    // We need policies to poll primary keys.
    iUnlockPolicyApi = CKeyLockPolicyApi::NewL( EPolicyDeactivateKeyguard );
    if ( !iUnlockPolicyApi->HasConfiguration() )
        {
        delete iUnlockPolicyApi;
        iUnlockPolicyApi = NULL;
        }

    // we need policies to poll primary keys
    iDevicelockPolicyApi = CKeyLockPolicyApi::NewL( EPolicyDevicelockQuery );
    if ( !iDevicelockPolicyApi->HasConfiguration() )
        {
        delete iDevicelockPolicyApi;
        iDevicelockPolicyApi = NULL;
        }
    
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// From base class CActive.
// Handles change in the screen saver state.
// ---------------------------------------------------------------------------
//
void CAknKeylockScreenSaverObserver::RunL()
    {
    _AKNTRACE_FUNC_ENTER;
    
    if ( iKeylockEnabled || iAutolockEnabled )
        {
        // Resubscribe before processing new value to prevent missing updates.
        Start();
        }

    TInt screenSaverState;
    iScreenSaverActiveProperty.Get( screenSaverState );
    // Primary keys are captured from screensaver when screensaver
    // is the top most application.
    if ( screenSaverState > NULL )
        {
         __ASSERT_DEBUG( !iCaptured,
                         Panic( EAknPanicKeyLockObserverAlreadyExists ) );
        iScreenSaverActive = ETrue;
        CapturePrimaryKeys( ETrue );
        }
    else
        {
        // If screensaver is disabled, stop capturing primary key events.
        if ( iScreenSaverActive )
            {
            CapturePrimaryKeys( EFalse );
            }
        iScreenSaverActive = EFalse;
        }
    
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// Set the lock status.
// ---------------------------------------------------------------------------
//
void CAknKeylockScreenSaverObserver::SetLockStatus( TBool aKeylockEnabled,
                                                    TBool aAutolockEnabled )
    {
    _AKNTRACE_FUNC_ENTER;
    
    iKeylockEnabled  = aKeylockEnabled;
    iAutolockEnabled = aAutolockEnabled;

    if ( iKeylockEnabled || iAutolockEnabled )
        {
        // Start observing screensaver activation.
        Start();
        }
    else
        {
        if ( iScreenSaverActive )
            {
            CapturePrimaryKeys( EFalse );
            }
        // Screensaver is only observed when keylock is enabled.
        Stop();
        }
    
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// Capture or uncapture primary keys.
// ---------------------------------------------------------------------------
//
void CAknKeylockScreenSaverObserver::CapturePrimaryKeys( TBool aCapture )
    {
    _AKNTRACE_FUNC_ENTER;
    
    if ( aCapture )
        {
        if ( iScreenSaverActive && !iCaptured )
            {
            if ( iKeylockEnabled && !iAutolockEnabled )
                {
                iCaptured = ETrue;
                // If no unlocking policy has been defined,
                // the default primary key is the left soft key.
                if ( !iUnlockPolicyApi )
                    {
                    // Capture LSK (starts unlock prosess, capturing
                    // bypasses screensaver)
                    iLeftSoftKey = iWindowGroup.CaptureKey( EKeyDevice0, 0, 0 );
                    }
                else
                    {
                    iPrimaryKeyCaptures.Reset();
                    TUint32 index( 0 );
                    TUint32 primaryKey( 0 );
                    TUint32 secondaryKey( 0 );
                    while ( iUnlockPolicyApi->GetKeyCombination( index,
                                                                 primaryKey,
                                                                 secondaryKey ) == KErrNone )
                        {
                        if (KErrNone != iPrimaryKeyCaptures.Append(iWindowGroup.CaptureKeyUpAndDowns(primaryKey, 0, 0)))
                            {
                            return;
                            }
                        index++;
                        }
                    }
                }
            else
                {
                if ( iKeylockEnabled && iAutolockEnabled )
                    {
                    iCaptured = ETrue;
                    // If no devicelock query policy has been defined,
                    // the default primary key is the left soft key.
                    if ( !iDevicelockPolicyApi )
                        {
                        // Capture LSK (starts unlock prosess,
                        // capturing bypasses screensaver).
                        iLeftSoftKey = iWindowGroup.CaptureKey( EKeyDevice0, 0, 0 );
                        }
                    else
                        {
                        iPrimaryKeyCaptures.Reset();
                        TUint32 index( 0 );
                        TUint32 primaryKey( 0 );
                        TUint32 secondaryKey( 0 );
                        while ( iDevicelockPolicyApi->GetKeyCombination( index, primaryKey, secondaryKey ) == KErrNone )
                            {
                            if (KErrNone != iPrimaryKeyCaptures.Append(iWindowGroup.CaptureKeyUpAndDowns(primaryKey, 0, 0)))
                                {
                                return;
                                }
                            index++;
                            }
                        }
                    }
                }
            }
        }
    else
        {
        if (iCaptured)
            {
            if (iLeftSoftKey > 0)
                {
                iWindowGroup.CancelCaptureKey(iLeftSoftKey); 
                }
            iLeftSoftKey = 0;
            
            if (iPrimaryKeyCaptures.Count() > 0)
                {
                for (TInt x = 0; x < iPrimaryKeyCaptures.Count(); x++)
                    {
                    iWindowGroup.CancelCaptureKeyUpAndDowns(iPrimaryKeyCaptures[x]);
                    }
                iPrimaryKeyCaptures.Reset();
                }
            
            iCaptured = EFalse;
            }
        }
    
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// From base class CActive.
// Cancels event listening.
// ---------------------------------------------------------------------------
//
void CAknKeylockScreenSaverObserver::DoCancel()
    {
    _AKNTRACE_FUNC_ENTER;
    
    iScreenSaverActiveProperty.Cancel();
    
    _AKNTRACE_FUNC_EXIT;
    }


// ===========================================================================
// class CAknLockedNote.
// ===========================================================================

// ---------------------------------------------------------------------------
// C++ constructor.
// ---------------------------------------------------------------------------
//
CAknLockedNote::CAknLockedNote( TInt& aLocked,
                                MEikCommandObserver* aCommandObserver )
    : CAknSleepingNote( aCommandObserver ),
      iLocked( aLocked )
    {
    AKNTASHOOK_ADD( this, "CAknLockedNote" );
    }


// ---------------------------------------------------------------------------
// From base class CAknSleepingNote.
// Handles a dialog button press for the button with ID aCommand.
// ---------------------------------------------------------------------------
//
TBool CAknLockedNote::OkToExitL( TInt aCommand )
    {
    _AKNTRACE_FUNC_ENTER;
    
    iLocked = EFalse;
    if ( iCommandObserver )
        {
        iCommandObserver->ProcessCommandL( aCommand );
        }
    
    _AKNTRACE_FUNC_EXIT;
    
    return ETrue;
    }


// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CAknLockedNote::~CAknLockedNote()
    {
    AKNTASHOOK_REMOVE();
    iLocked = EFalse;
    }


// ---------------------------------------------------------------------------
// Cancels the note.
// ---------------------------------------------------------------------------
//
void CAknLockedNote::CancelNote()
    {
    _AKNTRACE_FUNC_ENTER;
    
    if ( iTimer )
        {
        iTimer->Cancel();
        }
    ExitSleepingDialog();
    iLocked = EFalse;
    
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// From base class CEikDialog.
// Handles focus change event.
// ---------------------------------------------------------------------------
//
void CAknLockedNote::FocusChanged( TDrawNow /*aDrawNow*/ )
    {
    _AKNTRACE_FUNC_ENTER;
    
    if ( !IsFocused() && iCommandObserver )
        {
        TRAP_IGNORE( iCommandObserver->ProcessCommandL( KNoteCmdFocusLost ) )
        }
  
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// From base class CEikDialog.
// For future use.
// ---------------------------------------------------------------------------
//
void CAknLockedNote::CEikDialog_Reserved_1()
    {
    }


// ---------------------------------------------------------------------------
// From base class CEikDialog.
// For future use.
// ---------------------------------------------------------------------------
//
void CAknLockedNote::CEikDialog_Reserved_2()
    {
    }


// ---------------------------------------------------------------------------
// From base class CAknNoteDialog.
// For future use.
// ---------------------------------------------------------------------------
//
void CAknLockedNote::CAknNoteDialog_Reserved()
    {
    }


// ---------------------------------------------------------------------------
// From base class CAknSleepingNote.
// For future use.
// ---------------------------------------------------------------------------
//
void CAknLockedNote::CAknSleepingNote_Reserved()
    {
    }


// ===========================================================================
// class CAknSleepingNote
// ===========================================================================

// ---------------------------------------------------------------------------
// C++ constructor.
// ---------------------------------------------------------------------------
//
CAknSleepingNote::CAknSleepingNote( MEikCommandObserver* aCommandObserver ) :
    iCommandObserver( aCommandObserver )
    {
    AKNTASHOOK_ADD( this, "CAknSleepingNote" );
    }


// ---------------------------------------------------------------------------
// Second-phase constructor.
// ---------------------------------------------------------------------------
//
void CAknSleepingNote::ConstructSleepingNoteL( TInt aResourceId )
    {
    iResourceId = aResourceId;
    CAknNoteDialog::ConstructSleepingDialogL( aResourceId );

    // Construct now rather than in PreLayoutDynInit.
    delete iTimer;
    iTimer = NULL;
    iTimer = CPeriodic::NewL( 0 );
    }


// ---------------------------------------------------------------------------
// Displays the note.
// ---------------------------------------------------------------------------
//
TInt CAknSleepingNote::ShowNote( const TInt aTimeout, const TTone aTone )
    {
    _AKNTRACE_FUNC_ENTER;
    
    TRAP_IGNORE(AknGlobalPopupPriorityController::SetPopupPriorityL( *this, KGlobalWindowPriority_KeyLock ));
    iTimeoutInMicroseconds = aTimeout;
    iTone = aTone;
    
    _AKNTRACE_FUNC_EXIT;
    
    return RouseSleepingDialog();
    }


// ---------------------------------------------------------------------------
// From base class CEikDialog.
// Handles a dialog button press for the button with ID aCommand.
// ---------------------------------------------------------------------------
//
TBool CAknSleepingNote::OkToExitL( TInt aCommand )
    {
    _AKNTRACE_FUNC_ENTER;
    
    if ( iCommandObserver )
        {
        iCommandObserver->ProcessCommandL( aCommand );
        }

    _AKNTRACE_FUNC_EXIT;

    return ETrue;
    }


// ---------------------------------------------------------------------------
// From base class CAknNoteDialog.
// Updates the note animation on skin change event.
// ---------------------------------------------------------------------------
//
void CAknSleepingNote::HandleResourceChange( TInt aType )
    {
    _AKNTRACE_FUNC_ENTER;
    
    if ( aType == KAknsMessageSkinChange )
        {
        TInt animationRes( 0 );
        switch ( iResourceId )
            {
            case R_KEYLOCK_NOTE_KEYLOCKED:
                {
                animationRes = R_QGN_NOTE_INFO_ANIM;
                break;
                }
            case R_KEYLOCK_NOTE_UNLOCK_CONFIRM:
                {
                animationRes = R_QGN_NOTE_QUERY_ANIM;
                break;
                }
            case R_KEYLOCK_NOTE_UNLOCK_ASTERISK:
                {
                animationRes = R_QGN_NOTE_INFO_ANIM;
                break;
                }
            case R_KEYLOCK_NOTE_LOCK_ON:
                {
                animationRes = R_QGN_NOTE_KEYGUARD_LOCKED_ANIM;
                break;
                }
            case R_KEYLOCK_NOTE_LOCK_OFF:
                {
                animationRes = R_QGN_NOTE_KEYGUARD_OPEN_ANIM;
                break;
                }
            case R_KEYLOCK_OFFER_LOCK_NOTE:
                {
                animationRes = R_QGN_NOTE_QUERY_ANIM;
                break;
                }
            default:
                {
                break;
                }
            } // end of switch

        if ( animationRes )
            {
            CAknNoteControl* ctrl = NULL;
            ctrl = NoteControl();
            if ( ctrl )
                {
                TRAP_IGNORE( ctrl->SetAnimationL( animationRes ) );
                }
            }
        }

    CAknNoteDialog::HandleResourceChange( aType );
    
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// From base class CEikDialog.
// For future use.
// ---------------------------------------------------------------------------
//
void CAknSleepingNote::CEikDialog_Reserved_1()
    {
    }


// ---------------------------------------------------------------------------
// From base class CEikDialog.
// For future use.
// ---------------------------------------------------------------------------
//
void CAknSleepingNote::CEikDialog_Reserved_2()
    {
    }


// ---------------------------------------------------------------------------
// From base class CAknNoteDialog.
// For future use.
// ---------------------------------------------------------------------------
//
void CAknSleepingNote::CAknNoteDialog_Reserved()
    {
    }


// ---------------------------------------------------------------------------
// For future use.
// ---------------------------------------------------------------------------
//
void CAknSleepingNote::CAknSleepingNote_Reserved()
    {
    }


/**
 *  CAknEcsNote implements the emergency number display during keylock.
 *
 *  @lib   aknoldstylenotif.lib
 *  @since 3.2
 */
NONSHARABLE_CLASS( CAknEcsNote ): public CAknSleepingNote
    {
public:

    /**
    * Constructor.
    */
    CAknEcsNote( MEikCommandObserver* aCommandObserver );

    /**
    * API to set the emergency number to be displayed
    *
    * @param  aMatchedNumber  Text to display (e.g. "112" )
    */
    void SetEmergencyNumber( const TDesC& aMatchedNumber );

    /**
    * Dismisses the sleeping note.
    */
    void SleepNote();

public:

    /** Is note currently displayed. */
    TBool iNoteOnScreen;
    };


// ---------------------------------------------------------------------------
// C++ constructor.
// ---------------------------------------------------------------------------
//
CAknEcsNote::CAknEcsNote( MEikCommandObserver* aCommandObserver ) :
    CAknSleepingNote( aCommandObserver )
    {
    }


// ---------------------------------------------------------------------------
// Sets the emergency number to be displayed.
// ---------------------------------------------------------------------------
//
void CAknEcsNote::SetEmergencyNumber( const TDesC& aMatchedNumber )
    {
    _AKNTRACE_FUNC_ENTER;
    
    TRect mainPane;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EPopupParent,
                                       mainPane );

    TAknLayoutRect popupNoteWindow;
    AknLayoutUtils::TAknCbaLocation cbaLocation(
        AknLayoutUtils::CbaLocation() );

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

    popupNoteWindow.LayoutRect(
        mainPane,
        AknLayoutScalable_Avkon::popup_note_window( variety ) );
    TAknLayoutText textRect;
    textRect.LayoutText( popupNoteWindow.Rect(),
                         AknLayoutScalable_Avkon::popup_note_window_t5( 2 ) );

    // Size of a temporary buffer that contains new lines, spaces and
    // emergency number for a note.
    TBuf16<KAknEcsMaxMatchingLength+80> number;
    number.Append( '\n' );
    number.Append( '\n' );

    TInt spaceCharWidthInPixels = textRect.Font()->CharWidthInPixels( ' ' );
    if ( spaceCharWidthInPixels < 1 )
        {
        // Avoid divide by zero situation in case the space character
        // would have zero width.
        spaceCharWidthInPixels = 1;
        }

    TInt length = ( textRect.TextRect().Width() -
                    textRect.Font()->TextWidthInPixels( aMatchedNumber ) ) /
                  spaceCharWidthInPixels;

    const TInt matchedNumberLength = aMatchedNumber.Length();
    const TInt numberLength = number.Length();
    const TInt numberMaxLength = number.MaxLength();

    if ( numberLength + length + matchedNumberLength > numberMaxLength )
        {
        // To make sure that buffer overflow does not happen.
        length = numberMaxLength - numberLength - matchedNumberLength;
        }
    for ( TInt i = 0; i < length; i++ )
        {
        number.Append( ' ' );
        }

    number.Append( aMatchedNumber );
    TRAP_IGNORE( SetTextL( number ) );
    
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// Makes the note go to sleep.
// ---------------------------------------------------------------------------
//
void CAknEcsNote::SleepNote()
    {
    _AKNTRACE_FUNC_ENTER;
    
    if ( iNoteOnScreen )
        {
        // Causes flicker to other notes if called when note is not on screen.
        ExitSleepingDialog();
        }
    iNoteOnScreen = EFalse;
    
    _AKNTRACE_FUNC_EXIT;
    }


// ===========================================================================
// class CAknKeyLockControl
// ===========================================================================


// ---------------------------------------------------------------------------
// Default constructor.
// ---------------------------------------------------------------------------
//
CAknKeyLockControl::CAknKeyLockControl() :
    iConsumeNextEventKey( EFalse )
    {
    AKNTASHOOK_ADD( this, "CAknKeyLockControl" );
    }


// ---------------------------------------------------------------------------
// C++ constructor.
// ---------------------------------------------------------------------------
//
CAknKeyLockControl::CAknKeyLockControl( CAknKeyLockNotifierSubject* aNotif ) :
    iNotif( aNotif )
    {
    _AKNTRACE_FUNC_ENTER;
    
    AKNTASHOOK_ADD( this, "CAknKeyLockControl" );
    
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CAknKeyLockControl::~CAknKeyLockControl()
    {
    _AKNTRACE_FUNC_ENTER;
    
    AKNTASHOOK_REMOVE();
    // We implicitely trust that Eikon env exists
    // (though in practice it does not make the
    // difference as this destructor is really never called...)
    RWindowGroup& groupWin = iEikonEnv->RootWin();

    groupWin.CancelCaptureKey( iEditKeyL );
    groupWin.CancelCaptureKey( iEditKeyR );

    AknGlobalPopupPriorityController::RemovePopupPriority( *this );
    FeatureManager::UnInitializeLib();
    iEikonEnv->EikAppUi()->RemoveFromStack( this );
    iStatusProperty.Close();

    delete iConfirmationNote;
    delete iConfirmationNoteAsterisk;
    delete iLockedNote;
    delete iKeypadUnlockedNote;
    delete iKeypadLockedNote;
    delete iEcsDetector;
    delete iKeyLockCba;
    delete iOfferLockNote;
    delete iEcsNote; // Ecs change
    delete iKeylockApi;
    delete iKeylockScreenSaverObserver;
    
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// Second phase construction.
// ---------------------------------------------------------------------------
//
void CAknKeyLockControl::ConstructL()
    {
    _AKNTRACE_FUNC_ENTER;

    FeatureManager::InitializeLibL();
    iFeatureKeypadNoSlider =
        FeatureManager::FeatureSupported( KFeatureIdKeypadNoSlider );
    iFeatureNoPowerkey =
        FeatureManager::FeatureSupported( KFeatureIdNoPowerkey );

    // Keyguard switch support.
    CRepository* repository = CRepository::NewLC( KCRUidLockConf );
    TInt hardwareSupport( 0 );
    repository->Get( KKeyguardHardwareConf, hardwareSupport );
    CleanupStack::PopAndDestroy( repository );
    iHardwareSupport = TLockHardware( hardwareSupport );

    CreateWindowL();
    Window().SetSize( TSize( 0, 0 ) );
    ActivateL();

    AknGlobalPopupPriorityController::SetPopupPriorityL(
        *this, KGlobalWindowPriority_KeyLock );

    // To allow HW keys for key filter even if keypad is locked.
    iEikonEnv->EikAppUi()->AddToStackL( this,
                                        ECoeStackPriorityEnvironmentFilter - 1,
                                        ECoeStackFlagRefusesFocus );

    iEcsNote = new (ELeave) CAknEcsNote( this );
    iEcsNote->ConstructSleepingNoteL( R_AVKON_EMERGENCY_CALL_NOTE );
    iEcsNote->ButtonGroupContainer().ButtonGroup()->AsControl()->DrawableWindow()->SetOrdinalPosition( 0, 2 );

    iOfferLockNote = new (ELeave) CAknLockedNote( iOfferLockEnabled, this );
    iOfferLockNote->ConstructSleepingNoteL( R_KEYLOCK_OFFER_LOCK_NOTE );
    iOfferLockNote->ButtonGroupContainer().ButtonGroup()->AsControl()->DrawableWindow()->SetOrdinalPosition( 0, 2 );

    TBool touchEnabled( AknLayoutUtils::PenEnabled() );

    TBool hasSlider = HasSliderKey();
    iKeyLockCba = CEikButtonGroupContainer::NewL(
                    CEikButtonGroupContainer::ECba,
                    CEikButtonGroupContainer::EHorizontal,
                    this,
                    (touchEnabled&&hasSlider) ? R_AVKON_SOFTKEYS_EMPTY :
                                   R_KEYLOCK_SOFTKEYS_UNLOCK_EMPTY );

    iKeyLockCba->ButtonGroup()->AsControl()->DrawableWindow()->SetOrdinalPosition(
                ECoeWinPriorityNeverAtFront );

    TRect screenRect;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, screenRect );
    iKeyLockCba->SetBoundingRect( screenRect );
    iKeyLockCba->MakeVisible( EFalse );

    // Construct the "keypad locked" note.
    iKeypadLockedNote = new (ELeave) CAknSleepingNote();
    iKeypadLockedNote->ConstructSleepingNoteL(
        touchEnabled ? R_KEYLOCK_NOTE_DISPLAY_LOCK_ON_TOUCH :
                       R_KEYLOCK_NOTE_LOCK_ON );
    iKeypadLockedNote->ButtonGroupContainer().ButtonGroup()->AsControl()->DrawableWindow()->SetOrdinalPosition( 0, 2 );
    iKeypadLockedNote->PublishDialogL( EAknKeysLockedNote );

    // Construct the "keypad unlocked" note.
    iKeypadUnlockedNote = new (ELeave) CAknSleepingNote();
    iKeypadUnlockedNote->ConstructSleepingNoteL(
        touchEnabled ? R_KEYLOCK_NOTE_DISPLAY_LOCK_OFF_TOUCH :
                       R_KEYLOCK_NOTE_LOCK_OFF );
    iKeypadUnlockedNote->ButtonGroupContainer().ButtonGroup()->AsControl()->DrawableWindow()->SetOrdinalPosition( 0, 2 );
    iKeypadUnlockedNote->PublishDialogL( EAknKeysReleasedNote );

    // Construct the locked note.
    iLockedNote = new (ELeave) CAknLockedNote( iLockedNoteDisplayed );
    if ( touchEnabled )
        {
        iLockedNote->ConstructSleepingNoteL( R_KEYLOCK_NOTE_DISPLAY_LOCKED_TOUCH );
        }
    else
        {
        switch ( iHardwareSupport )
            {
            case EKeyguardOnePositionSwitch:
            case EKeyguardTwoPositionSwitch:
                {
                iLockedNote->ConstructSleepingNoteL( R_KEYLOCK_NOTE_KEYLOCKED_SWITCH );
                break;
                }
            case EKeyguardDefaultHardware:
            default:
                {
                iLockedNote->ConstructSleepingNoteL( R_KEYLOCK_NOTE_KEYLOCKED );
                break;
                }
            }
        }
    iLockedNote->ButtonGroupContainer().ButtonGroup()->AsControl()->DrawableWindow()->SetOrdinalPosition( 0, 2 );

    if ( !(touchEnabled&&hasSlider) )
        {
        // These are created only if touch is not enabled, since
        // currently in touch devices the keylock state is controlled
        // with switch.

        // Construct the confirmation note for unlocking keypad.
        iConfirmationNote = new (ELeave) CAknLockedNote( iUnlockConfirmation );
        iConfirmationNote->ConstructSleepingNoteL( R_KEYLOCK_NOTE_UNLOCK_CONFIRM );
        iConfirmationNote->ButtonGroupContainer().ButtonGroup()->AsControl()->DrawableWindow()->SetOrdinalPosition( 0, 2 );

        if ( iFeatureKeypadNoSlider )
            {
            // Show note "Now press *".
            // Note is shown when user has pressed "Unlock" when
            // keypad is in locked state
            iConfirmationNoteAsterisk =
                new (ELeave) CAknLockedNote( iUnlockConfirmation );
            
            TInt fileExist = KErrNone;
            
            CFindFileByType* pFindFile = new (ELeave) CFindFileByType(iEikonEnv->FsSession());
            fileExist = pFindFile->FindFirst(UNLOCKKEY_MIF_FILE_UNICODE, _L(""), KNullUid);
            delete pFindFile;
            
            if (KErrNone != fileExist)
                {
                iConfirmationNoteAsterisk->ConstructSleepingNoteL(
                        R_KEYLOCK_NOTE_UNLOCK_ASTERISK);
                }
            else
                {
                iConfirmationNoteAsterisk->ConstructSleepingNoteL(
                        R_KEYLOCK_NOTE_UNLOCK_ASTERISK_ANIM_UNTOUCH);
                }
          
            iConfirmationNoteAsterisk->ButtonGroupContainer().ButtonGroup()->AsControl()->DrawableWindow()->SetOrdinalPosition( 0, 2 );
            }
        }

    // Emergency call support.
    iEcsDetector = CAknEcsDetector::NewL();
    iEcsDetector->SetObserver( this );

    // As edit keys (shifts) shouldn't be passed to application as
    // EEventKey, capture those here.
    RWindowGroup& groupWin = iEikonEnv->RootWin();
    iEditKeyL = groupWin.CaptureKey( EKeyLeftShift, 0, 0 );
    iEditKeyR = groupWin.CaptureKey( EKeyRightShift, 0, 0 );

    // Create keylock policy component if an unlocking policy has been defined.
    iKeylockApi = CKeyLockPolicyApi::NewL( EPolicyDeactivateKeyguard );
    if ( !iKeylockApi->HasConfiguration() )
        {
        // Keylock API not initialized.
        delete iKeylockApi;
        iKeylockApi = NULL;
        }

    iKeylockScreenSaverObserver =
        CAknKeylockScreenSaverObserver::NewL( groupWin );

    // Define P&S key that is used to publish the keyguard status.
    RProperty::Define( KPSUidAvkonDomain,
                       KAknKeyguardStatus,
                       RProperty::EInt,
                       TSecurityPolicy( TSecurityPolicy::EAlwaysPass ),
                       KWritePolicy );

    iStatusProperty.Attach( KPSUidAvkonDomain, KAknKeyguardStatus );
    iStatusProperty.Set( EKeyguardNotActive );
    
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// Enable key lock.
// ---------------------------------------------------------------------------
//
void CAknKeyLockControl::EnableKeylock( TBool aShowNote, TBool aNotifySysApp )
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE("aShowNote:%d",aShowNote);
    _AKNTRACE("aNotifySysApp:%d",aNotifySysApp);
    
    // Policy can be used to disable support for keyguard.
    if ( !iAutolockEnabled && !CKeyLockPolicyApi::KeyguardAllowed() )
        {
        // Keylock Disabled
        return;
        }
    // Keylock Enabled
    iKeylockScreenSaverObserver->SetLockStatus( ETrue, iAutolockEnabled );
    if ( iOfferLockEnabled )
        {
        iOfferLockNote->CancelNote();
        }

    // Update keyguard status to P&S system.
    iStatusProperty.Set( iAutolockEnabled ? EKeyguardAutolockEmulation :
                                            EKeyguardLocked );
    iKeyLockEnabled = ETrue;

    if ( !iAutolockEnabled && aNotifySysApp )
        {
        SendMessageToSysAp( EEikKeyLockEnabled );
        }
    TBool hasSliderKey = HasSliderKey();
    if ( !AknLayoutUtils::PenEnabled() || !hasSliderKey)
        {
        iKeyLockCba->MakeVisible( ETrue );
        }
    else
        {
        iKeyLockCba->MakeVisible( EFalse );
        }

    TBool areWeInIdleState = CEikStatusPaneBase::Current()->PaneCapabilities(
        TUid::Uid( EEikStatusPaneUidClock ) ).IsInCurrentLayout();

    if ( areWeInIdleState )
        { // idle state
        static_cast<CEikCba*>(
            iKeyLockCba->ButtonGroup() )->SetSkinBackgroundId(
                KAknsIIDQsnBgAreaControlIdle );
        }
    else
        {
        static_cast<CEikCba*>(
            iKeyLockCba->ButtonGroup() )->SetSkinBackgroundId(
                KAknsIIDQsnBgAreaControl );
        }

    AknGlobalPopupPriorityController::ShowPopup( *this, ETrue );

    if ( aShowNote )
        {
        DisplayLockedNote();
        }

    if ( !AknLayoutUtils::PenEnabled() || !hasSliderKey)
        {
        ShowKeylockCba();
        }
    else
        {
        // Set the window screen sized and make it transparent.
        TRect screenRect;
        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, screenRect );
        Window().SetSize( screenRect.Size() );
        Window().SetRequiredDisplayMode( EColor16MA );
        TInt err = Window().SetTransparencyAlphaChannel();
        if ( err == KErrNone )
            {
             Window().SetBackgroundColor( ~0 );
            }
        }

        // in case Telephone-app is topmost, then the user is confused because he sees but can't use it.
        // therefore it's required to hide it, by sending to background. ETMA-7M8A2Y 20090105
        if ( AknLayoutUtils::PenEnabled() )
            {
            TApaTaskList apaTaskList(CCoeEnv::Static()->WsSession());
            #define KPhoneAppUid TUid::Uid(0x100058B3)

            TApaTask apaTask = apaTaskList.FindApp(KPhoneAppUid);
            if (apaTask.Exists())
                {
                #if defined(_DEBUG)
                RDebug::Print(_L("(KeyGuard)CAknKeyLockControl::EnableKeylock() Bring phone to background"));
                #endif
                // Bring phone to background
                apaTask.SendToBackground();
                }
            }

    // Start capturing system keys.
    CaptureSystemKeys();

    // Capture all pointer events.
    CapturePointerEvents();

    iEcsDetector->ConnectToEventSource();

    if ( iNotif )
        {
        iNotif->NotifyStatusChange( EKeyLockEnabled );
        }

    if ( !iSoundsMuted )
        {
        CAknAppUiBase* appUi = iAvkonAppUiBase;
        TRAPD( err, appUi->KeySounds()->PushContextL( R_AVKON_SILENT_SKEY_LIST ) );
        if ( !err )
            {
            appUi->KeySounds()->BringToForeground();
            appUi->KeySounds()->LockContext();
            iSoundsMuted = ETrue;
            }
        }

    // Basically this cannot fail so we ignore return code.
    static_cast<CAknNotifierAppServerAppUi*>(
        iEikonEnv->EikAppUi() )->SuppressAppSwitching( ETrue );

    // Method HandleResourceChangeL with parameter KAknInternalFSWClose cannot
    // leave, but we trap it in just in case.
    TRAP_IGNORE( static_cast<CAknCapAppServerAppUi*>( iEikonEnv->EikAppUi() )->HandleResourceChangeL(
            KAknInternalFSWClose ); );
    
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// Disable key lock.
// ---------------------------------------------------------------------------
//
void CAknKeyLockControl::DisableKeylock(TBool aNotifySysApp)
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE("aShowNote:%d",aNotifySysApp);

    // Keep locking status in sync.
    iKeylockScreenSaverObserver->SetLockStatus( EFalse, iAutolockEnabled );
    if ( iSoundsMuted )
        {
        CAknAppUiBase* appUi= iAvkonAppUiBase;
        appUi->KeySounds()->ReleaseContext();
        appUi->KeySounds()->PopContext();
        iSoundsMuted = EFalse;
        }

    iEcsDetector->CloseEventSource();

    // Stop capturing system keys.
    UnCaptureSystemKeys();

    // Stop capturing pointer events.
    UnCapturePointerEvents();

    AknGlobalPopupPriorityController::ShowPopup( *this, EFalse );

    // Make the window "disappear".
    Window().SetSize( TSize( 0, 0 ) );

    iKeyLockCba->ButtonGroup()->AsControl()->DrawableWindow()->SetOrdinalPosition(
        ECoeWinPriorityNeverAtFront );
    iKeyLockCba->MakeVisible( EFalse );

    // Update keyguard status to P&S system.
    iStatusProperty.Set( EKeyguardNotActive );
    iKeyLockEnabled = EFalse;

    if ( !iAutolockEnabled )    // only when Autolock was user-activated
        {
        // in case Telephone-app was topmost and sent to background, then the user is confused because he expects to see it again.
        // therefore it's required to show it, by sending to foreground. 
        if ( AknLayoutUtils::PenEnabled() )
            {       
            TInt callState;
            RProperty::Get( KPSUidCtsyCallInformation, KCTsyCallState, callState );
            #if defined(_DEBUG)
            RDebug::Printf( "%s %s (%u) callState=%x", __FILE__, __PRETTY_FUNCTION__, __LINE__, callState );
            RDebug::Printf( "%s %s (%u) EPSCTsyCallStateNone=%x", __FILE__, __PRETTY_FUNCTION__, __LINE__, EPSCTsyCallStateNone );
            #endif
            if (callState != EPSCTsyCallStateNone )
                {
                TApaTaskList apaTaskList(CCoeEnv::Static()->WsSession());
                #define KPhoneAppUid TUid::Uid(0x100058B3)
                TApaTask apaTask = apaTaskList.FindApp(KPhoneAppUid);
                if (apaTask.Exists())
                    {
                    RDebug::Printf( "%s %s (%u) foreground=%x", __FILE__, __PRETTY_FUNCTION__, __LINE__, 1 );
                    #if defined(_DEBUG)
                    RDebug::Print(_L("(AUTOLOCK)CAknKeyLockControl::EnableKeylock() Send phone to foreground"));
                    #endif
                    // Bring phone to foreground
                    apaTask.BringToForeground();
                    }
                }
            }   // PenEnabled()
        }

	if (aNotifySysApp)
		{
		SendMessageToSysAp( EEikKeyLockDisabled );
		}

	if ( iNotif )
        {
        iNotif->NotifyStatusChange( EKeyLockDisabled );
        }

    // Basically this cannot fail so we ignore return code.
    static_cast<CAknNotifierAppServerAppUi*>(
        iEikonEnv->EikAppUi() )->SuppressAppSwitching( EFalse );

    iAutolockEnabled = EFalse;
    
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// Sends a message to the SysAp window group.
// ---------------------------------------------------------------------------
//
void CAknKeyLockControl::SendMessageToSysAp( TInt aMessage )
    {
    _AKNTRACE_FUNC_ENTER;
    
    RWsSession& ws = iEikonEnv->WsSession();
    TInt wgId = 0;
    CApaWindowGroupName::FindByAppUid( KSysApUid, ws, wgId );
    if ( wgId )
        {
        TWsEvent event;
        event.SetType( aMessage );
        event.SetTimeNow();
        ws.SendEventToWindowGroup( wgId, event );
        }
    
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// Displays the "offer keylock" note.
// ---------------------------------------------------------------------------
//
void CAknKeyLockControl::OfferKeylock()
    {
    _AKNTRACE_FUNC_ENTER;
    
    iOfferLockNote->ShowNote( (CAknNoteDialog::TTimeout)KAknOfferKeyLockTimeout,
                              CAknNoteDialog::ENoTone );
    iOfferLockEnabled = ETrue;
    
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// Displays the "locked" note.
// ---------------------------------------------------------------------------
//
void CAknKeyLockControl::DisplayLockedNote()
    {
    if ( !iAutolockEnabled )
        {
        }
    }


// ---------------------------------------------------------------------------
// Displays the "keys active" note.
// ---------------------------------------------------------------------------
//
void CAknKeyLockControl::DisplayKeyActiveNote()
    {
    if ( !iAutolockEnabled )
        {
        }
    }


// ---------------------------------------------------------------------------
// Unlocks the keypad and displays the "keys active" note.
// ---------------------------------------------------------------------------
//
void CAknKeyLockControl::DoUnlock()
    {
    _AKNTRACE_FUNC_ENTER;
    
    DisableKeylock();
    DisplayKeyActiveNote();
    
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// From base class CCoeControl.
// Handles resource change events.
// ---------------------------------------------------------------------------
//
void CAknKeyLockControl::HandleResourceChange( TInt aType )
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE("aType:%d",aType);

    if ( aType == KEikDynamicLayoutVariantSwitch )
        {
        TRect screenRect;
        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, screenRect );
        if ( !AknLayoutUtils::PenEnabled() )
            {
             iKeyLockCba->SetBoundingRect( screenRect );
            }
        else if ( iKeyLockEnabled )
            {
            // Only resize the window if keylock is active, as
            // the window size must be zero when keylock is not active.
            // The window is resized to correct size when keylock is activated.
            Window().SetSize( screenRect.Size() );
            Window().SetRequiredDisplayMode( EColor16MA );
            TInt err = Window().SetTransparencyAlphaChannel();
            if ( err == KErrNone )
                {
                 Window().SetBackgroundColor( ~0 );
                }
            }
        }
    
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// From base class MEikCommandObserver.
// Process commands.
// ---------------------------------------------------------------------------
//
void CAknKeyLockControl::ProcessCommandL( TInt aCommandId )
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE("aCommandId:%d",aCommandId);

    switch ( aCommandId )
        {
        case EAknSoftkeyUnlock:
            {
            if ( iAutolockEnabled && !iKeylockApi )
                {
                TApaTaskList tasklist( iCoeEnv->WsSession() );
                TApaTask autolocktask = tasklist.FindApp( KAutolockUid );
                if ( autolocktask.Exists() )
                    {
                    // if Autolock application is ready
                    DisableKeylock();
                    iNotif->NotifyStatusChange( EHideSoftNotifications );
                    TKeyEvent keyEvent;
                    keyEvent.iCode = EKeyBell;
                    autolocktask.SendKey( keyEvent );
                    }
                }
            else
                {
                LeftSoftKeyPressed();
                }
            break;
            }
        case EAknSoftkeyLock:
            {
            // Lock keys
            DoExitOfferKeylock();
            EnableKeylock();
            break;
            }
        case EAknSoftkeyExit:
            {
            // Cancel offer keylock CBA
            DoExitOfferKeylock();
            break;
            }
        case EAknSoftkeyEmpty:
            {
            if ( iKeyLockEnabled )
                {
                ShowLockedNote();
                }
            break;
            }
        case KNoteCmdFocusLost:
            {
            // Locked note has become unfocused - get rid of it.
            if ( iOfferLockEnabled )
                {
                DoExitOfferKeylock();
                }
            break;
            }
        default:
            {
            break;
            }
        }
    
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// From base class CCoeControl.
// Gets the amount of component controls.
// ---------------------------------------------------------------------------
//
TInt CAknKeyLockControl::CountComponentControls() const
    {
    if ( iKeyLockEnabled )
        {
        return 1;
        }
    else
        {
        return 0;
        }
    }


// ---------------------------------------------------------------------------
// From base class CCoeControl.
// Returns the pointer to a component control.
// ---------------------------------------------------------------------------
//
CCoeControl* CAknKeyLockControl::ComponentControl( TInt /*aIndex*/ ) const
    {
    if ( iKeyLockEnabled )
        {
        return iKeyLockCba;
        }
    else
        {
        return NULL;
        }
    }


// ---------------------------------------------------------------------------
// Handles LSK keypress.
// ---------------------------------------------------------------------------
//
void CAknKeyLockControl::LeftSoftKeyPressed()
    {
    _AKNTRACE_FUNC_ENTER; 
    
    // Check that the confirmation note exists, as it's not created on
    // startup if touch layout is in use. In emulator this might cause
    // a problem, as layout can be changed to a non-touch one, and
    // the confirmation notes do not exist.
    if ( iConfirmationNote )
        {
        if ( iFeatureKeypadNoSlider )
            {
            // Show note "Now press *".
            // Note is shown when user has pressed "Unlock" when keypad
            // is in locked state.
            iConfirmationNoteAsterisk->ShowNote( CAknNoteDialog::EShortTimeout,
                                                 CAknNoteDialog::EConfirmationTone );
            }
        else
            {
            iConfirmationNote->ShowNote( CAknNoteDialog::EShortTimeout,
                                         CAknNoteDialog::EConfirmationTone );
            }
        SendMessageToSysAp( EEikKeyLockLightsOnRequest );
        iUnlockConfirmation = ETrue;
        }
    
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// From base class CCoeControl.
// Handle key events.
// ---------------------------------------------------------------------------
//
TKeyResponse CAknKeyLockControl::OfferKeyEventL( const TKeyEvent& aKeyEvent,
                                                 TEventCode aType )
    {
    _AKNTRACE_FUNC_ENTER; 
    
    if ( AknLayoutUtils::PenEnabled() )
        {
        _AKNTRACE("(KeyGuard)CAknKeyLockControl::OfferKeyEventL: PenEnabled");
        if ( iAutolockEnabled )
            { // The case when touch device is locked and so must be unlocked by hold switch.
            _AKNTRACE("(KeyGuard)CAknKeyLockControl::OfferKeyEventL: Autolock Enabled");
            if ( aType == EEventKey && aKeyEvent.iCode == EKeyDeviceF )
                {
                _AKNTRACE("(KeyGuard)CAknKeyLockControl::OfferKeyEventL: SysAp message");
                SendMessageToSysAp( EEikKeyLockLightsOnRequest );
                if ( iAutolockEnabled && !iKeylockApi )
                    {
                    TApaTaskList tasklist( iCoeEnv->WsSession() );
                    TApaTask autolocktask = tasklist.FindApp( KAutolockUid );
                    if ( autolocktask.Exists() )
                        {
                        // If Autolock application is ready
                        DisableKeylock();
                        iNotif->NotifyStatusChange( EHideSoftNotifications );
                        TKeyEvent keyEvent;
                        keyEvent.iCode = EKeyBell;
                        autolocktask.SendKey( keyEvent );
                        }
                    }
                _AKNTRACE_FUNC_EXIT;
                return EKeyWasConsumed;
                }
            }
        }

    if ( !iOfferLockEnabled && !iKeyLockEnabled )
        {
        if ( aType == EEventKey &&
             ( aKeyEvent.iCode == EKeyLeftShift ||
               aKeyEvent.iCode == EKeyRightShift ) )
            {
            // Eat these events as they just cause problems elsewhere.
            return EKeyWasConsumed;
            }
        if ( iKeylockApi && iConsumeNextEventKey )
            {
            if ( aType == EEventKeyUp )
                {
                iConsumeNextEventKey = EFalse;
                }
            return EKeyWasConsumed;
            }
        return EKeyWasNotConsumed;
        }

    if ( ( aType == EEventKey && aKeyEvent.iRepeats == 0 ) ||
         ( aType == EEventKeyDown && aKeyEvent.iScanCode == EStdKeyDevice2 ) ) // Power key
        {
        // If power key pressed, tell SysAp about it.
        if ( ( aKeyEvent.iScanCode == EStdKeyDevice2 && aType == EEventKeyDown ) ||
             ( iFeatureNoPowerkey && aKeyEvent.iCode == EKeyNo ) )
            {
            SendMessageToSysAp( EEikKeyLockPowerKeyPressed );
            if ( iFeatureNoPowerkey )
                {
                SendMessageToSysAp( EEikKeyLockLightsOnRequest );
                }
            }
        }

    // Product uses a Keylock Policy API if there exists a defined
    // unlock configuration.
    if ( iKeylockApi && iKeyLockEnabled )
        {
        // For keyguard policy
        if ( !iAutolockEnabled )
            {
            // Send key events to KeylockPolicy first
            if ( iKeylockApi->HandleKeyEventL( aKeyEvent, aType ) )
                {
                // Key combinations has been pressed -> unlocking.
                DoUnlock();
                iConsumeNextEventKey = ETrue;
                }
            else
                {
                // Key combination is not complete.
                if ( iKeylockApi->PrimaryKeyPressed() )
                    {
                    if ( iKeylockApi->GetLastPrimaryKey() == aKeyEvent.iScanCode &&
                         aType == EEventKeyDown )
                        {
                        // Only primary key has been pressed - show
                        // how to unlock "Now press *"
                        LeftSoftKeyPressed();
                        }
                    }
                else
                    {
                    // Not the primary key has been pressed.
                    if ( aType == EEventKeyDown &&
                         !( iEcsNote->iNoteOnScreen && aKeyEvent.iCode == EKeyYes ) )
                        {
                        ShowLockedNote();
                        }
                    }
                }
            }
        // for autolock policy
        else
            {
            if ( aType == EEventKeyDown )
                {
                TApaTaskList tasklist( iCoeEnv->WsSession() );
                TApaTask autolocktask = tasklist.FindApp( KAutolockUid );
                if ( autolocktask.Exists() )
                    {
                    autolocktask.SendKey( aKeyEvent );
                    }
                }
            }
        return EKeyWasConsumed;
        }

    if ( ( aType == EEventKey && aKeyEvent.iRepeats == 0 ) ||
         ( aType == EEventKeyDown && aKeyEvent.iScanCode == EStdKeyDevice2 ) ) // Power key
        {
        if ( iOfferLockEnabled )
            {
            switch ( aKeyEvent.iCode )
                {
                case EKeyOK: // fallthrough to return EKeyWasConsumed
                    {
                    DoExitOfferKeylock();
                    EnableKeylock();
                    }
                case EKeyLeftArrow:
                case EKeyRightArrow:
                case EKeyUpArrow:
                case EKeyDownArrow:
                case EKeyApplication:
                    {
                    return EKeyWasConsumed;
                    }
                default:
                    {
                    // Normal response - send it to the CBA via the
                    // control stack.
                    return EKeyWasNotConsumed;
                    }
                }
            }
        else if ( iKeyLockEnabled )
            {
            if ( iLockedNoteDisplayed )
                {
                // See if 'Unlock' has been pressed.
                if ( aKeyEvent.iCode == EKeyCBA1 )
                    {
                    LeftSoftKeyPressed();
                    iLockedNote->CancelNote();
                    }
                // Locked note is on-screen - discard key.
                return EKeyWasConsumed;
                }
            else if ( iUnlockConfirmation )
                {
                // Confirmation note is on-screen - check for OK.
                // EStdKeyDevice1 is also needed since some applications generate
                // EKeyCBA2 key events and accidentally unlock the phone
                if ( ( ( aKeyEvent.iCode == KAknAsterisk ||
                         aKeyEvent.iCode == KAknChineseAsterisk ) &&
                       iFeatureKeypadNoSlider ) ||
                     ( aKeyEvent.iCode == EKeyCBA2 &&
                       aKeyEvent.iScanCode == EStdKeyDevice1 &&
                       !iFeatureKeypadNoSlider ) )
                    {
                    DoUnlock();
                    if ( iFeatureKeypadNoSlider )
                        {
                        // Show note "Now press *".
                        // Note is shown when user has pressed "Unlock"
                        // when keypad is in locked state
                        iConfirmationNoteAsterisk->CancelNote();
                        }
                    else
                        {
                        iConfirmationNote->CancelNote();
                        }
                    }
                else
                    {
                    if ( aKeyEvent.iCode != EKeyCBA1 &&
                         aKeyEvent.iCode != EKeyLeftShift &&
                         aKeyEvent.iCode != EKeyRightShift )
                        {
                        ShowLockedNote();
                        }
                    }
                }
            else
                {
                TKeyResponse cbaResponse = EKeyWasNotConsumed;
                // EKeyOK will be incorrectly translated to left soft key by the CBA.
                if ( aKeyEvent.iCode != EKeyOK )
                    {
                    // Normal response - send it to the CBA.
                    cbaResponse =
                        iKeyLockCba->ButtonGroup()->AsControl()->OfferKeyEventL(
                            aKeyEvent, aType );
                    }

                if ( cbaResponse == EKeyWasNotConsumed )
                    {
                    if ( !( iEcsNote->iNoteOnScreen &&
                            aKeyEvent.iCode == EKeyYes ) )
                        {
                        ShowLockedNote();
                        }
                    }
                }
            }
        }
    // Needed for the pencil key/shift keys to show "keys locked" note.
    else if ( iKeyLockEnabled )
        {
        if ( aType == EEventKeyDown &&
             aKeyEvent.iRepeats == 0 &&
             ( aKeyEvent.iScanCode == EStdKeyLeftShift ||
               aKeyEvent.iScanCode == EStdKeyRightShift ) )
            {
            ShowLockedNote();
            }
        }
    _AKNTRACE_FUNC_EXIT;
    return EKeyWasConsumed;
    }


// ---------------------------------------------------------------------------
// Shows the "locked" note.
// ---------------------------------------------------------------------------
//
void CAknKeyLockControl::ShowLockedNote()
    {
    _AKNTRACE_FUNC_ENTER;
    
    if ( !iLockedNoteDisplayed )
        {
        DoShowLockedNote();
        }
    
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// Shows the "locked" note.
// ---------------------------------------------------------------------------
//
void CAknKeyLockControl::DoShowLockedNote()
    {
    if ( !iAutolockEnabled )
        {
        }
    }


// ---------------------------------------------------------------------------
// Brings the keylock notifier's CBA visible.
// ---------------------------------------------------------------------------
//
void CAknKeyLockControl::ShowKeylockCba()
    {
    _AKNTRACE_FUNC_ENTER;
    
    RDrawableWindow* cbaWindow =
        iKeyLockCba->ButtonGroup()->AsControl()->DrawableWindow();
    cbaWindow->SetFaded( EFalse, RWindowTreeNode::EFadeWindowOnly );
    cbaWindow->SetOrdinalPosition( 0, 1 );
    cbaWindow->SetNonFading( ETrue );
    
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// Sets the necessary HW keys captured.
// ---------------------------------------------------------------------------
//
void CAknKeyLockControl::CaptureSystemKeys()
    {
    _AKNTRACE_FUNC_ENTER;
    
    if ( !iKeysCaptured )
        {
        RWindowGroup& groupWin = iCoeEnv->RootWin();

        // Capture app key (disable application switching).
        iAppKey = groupWin.CaptureKeyUpAndDowns( EStdKeyApplication0, 0, 0 );
        iAppKey2 = groupWin.CaptureKey( EKeyApplication0, 0, 0 );

        // Capture power key (for lights).
        iPowerKey = groupWin.CaptureKeyUpAndDowns( EStdKeyDevice2, 0, 0 );
        iPowerKey2 = groupWin.CaptureKey( EKeyDevice2, 0, 0 );

        // Capture voice key.
        iVoiceKey = groupWin.CaptureKeyUpAndDowns( EStdKeyDevice6, 0, 0 );
        iVoiceKey2 = groupWin.CaptureKey( EKeyDevice6, 0, 0 );

        // Capture end key (lights for combined power/end key).
        iEndKey = groupWin.CaptureKey( EKeyNo, 0, 0 );

        // Capture PoC key.
        iPoCKey = groupWin.CaptureKeyUpAndDowns( EStdKeyApplication1, 0, 0 );
        iPoCKey2 = groupWin.CaptureKey( EKeyApplication1, 0, 0 );

        iHoldSwitch = 0;

        if ( AknLayoutUtils::PenEnabled() )
            {
             _AKNTRACE("(KeyGuard)CAknKeyLockControl::CaptureSystemKeys PenEnabled");
            if ( iAutolockEnabled )
                { //Capture Hold Switch
             _AKNTRACE("(KeyGuard)CAknKeyLockControl::CaptureSystemKeys iAutolockEnabled");
                iHoldSwitch = groupWin.CaptureKey( EKeyDeviceF, 0, 0 );
                }
            }
        iKeysCaptured = ETrue;
        }
    
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// Releases captured HW keys.
// ---------------------------------------------------------------------------
//
void CAknKeyLockControl::UnCaptureSystemKeys()
    {
    _AKNTRACE_FUNC_ENTER;
    
    if ( iKeysCaptured )
        {
        RWindowGroup& groupWin = iCoeEnv->RootWin();
        groupWin.CancelCaptureKeyUpAndDowns( iAppKey );
        groupWin.CancelCaptureKeyUpAndDowns( iPowerKey );
        groupWin.CancelCaptureKeyUpAndDowns( iVoiceKey );
        groupWin.CancelCaptureKey( iAppKey2 );
        groupWin.CancelCaptureKey( iPowerKey2 );
        groupWin.CancelCaptureKey( iVoiceKey2 );
        groupWin.CancelCaptureKey( iEndKey );
        groupWin.CancelCaptureKeyUpAndDowns( iPoCKey );
        groupWin.CancelCaptureKey( iPoCKey2 );

        if ( iHoldSwitch > 0 )
            {
            groupWin.CancelCaptureKey( iHoldSwitch );
            }

        iKeysCaptured = EFalse;
        }
    
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// From base class MAknEcsObserver.
// Handles the ECS events.
// ---------------------------------------------------------------------------
//
void CAknKeyLockControl::HandleEcsEvent( CAknEcsDetector* aEcsDetector,
                                         CAknEcsDetector::TState aState )
    {
    _AKNTRACE_FUNC_ENTER;
    
    switch ( aState )
        {
        case CAknEcsDetector::ECompleteMatchThenSendKey:
            {
            // Do nothing since note will be removed on ECallAttempted event.
            break;
            }
        case CAknEcsDetector::ECompleteMatch:
        case CAknEcsDetector::EServiceNumMatch:
            {
            iEcsNote->SetEmergencyNumber( aEcsDetector->CurrentMatch() );
            iEcsNote->ShowNote( CAknNoteDialog::ENoTimeout,
                                CAknNoteDialog::ENoTone );

            // Tell SysAp to switch lights on.
            SendMessageToSysAp( EEikEcsQueryLights );
            iEcsNote->iNoteOnScreen = ETrue;
            break;
            }
        case CAknEcsDetector::EPartialMatch:
            {
            iEcsNote->SleepNote();
            break;
            }
        case CAknEcsDetector::ECallAttempted:
            {
            iEcsNote->SleepNote();
            break;
            }
        case CAknEcsDetector::EEmpty:
            {
            iEcsNote->SleepNote();
            break;
            }
        case CAknEcsDetector::ENoMatch:
            {
            iEcsNote->SleepNote();
            break;
            }
        default:
            {
            break;
            }
        }
    
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// Cancels the offer keylock note.
// ---------------------------------------------------------------------------
//
void CAknKeyLockControl::DoExitOfferKeylock()
    {
    _AKNTRACE_FUNC_ENTER;
    
    iOfferLockNote->CancelNote();
    
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// Cancels the offer keylock note.
// ---------------------------------------------------------------------------
//
void CAknKeyLockControl::OfferTimerExpired()
    {
    _AKNTRACE_FUNC_ENTER;
    
    DoExitOfferKeylock();
    
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// Sets the autolock state.
// ---------------------------------------------------------------------------
//
void CAknKeyLockControl::AutolockEnabled( TBool aAutoLockOn )
    {
    _AKNTRACE_FUNC_ENTER;
    
    iAutolockEnabled = aAutoLockOn;
    
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// For CDMA implementation.
// ---------------------------------------------------------------------------
//
void CAknKeyLockControl::CallNumberL( TDesC& /*aNumber*/ )
    {
    }


// ---------------------------------------------------------------------------
// For CDMA implementation.
// ---------------------------------------------------------------------------
//
void CAknKeyLockControl::ShowLockPhoneQueryL()
    {
    }


// ---------------------------------------------------------------------------
// For capturing pointer events when key lock is enabled.
// ---------------------------------------------------------------------------
//
void CAknKeyLockControl::CapturePointerEvents()
    {
    _AKNTRACE_FUNC_ENTER;
    
    if ( AknLayoutUtils::PenEnabled() )
        {
        Window().SetPointerCapture( RWindowBase::TCaptureDragDrop );
        Window().ClaimPointerGrab( ETrue );
        }
    
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// For releasing pointer events when key lock is disabled.
// ---------------------------------------------------------------------------
//
void CAknKeyLockControl::UnCapturePointerEvents()
    {
    _AKNTRACE_FUNC_ENTER;
    
    if ( AknLayoutUtils::PenEnabled() )
        {
        Window().SetPointerCapture( RWindowBase::TCaptureDisabled );
        Window().ClaimPointerGrab( EFalse );
        }
    
    _AKNTRACE_FUNC_EXIT;
    }

TBool CAknKeyLockControl::HasSliderKey()
    {
    _AKNTRACE_FUNC_ENTER;
    
    TBool hasSlider(iHardwareSupport != EKeyguardDefaultHardware);
    if( FeatureManager::FeatureSupported( KFeatureIdFfPowerKeyAsKeyguard ) )
        {
        hasSlider = ETrue;  // the only purpose is to display empty sotkeys
        }
    
    _AKNTRACE( "hasSlider:%d",hasSlider);
    _AKNTRACE_FUNC_EXIT;
    
    return hasSlider;
    }


// ===========================================================================
// class CAknKeyLockNotifierSubject
// ===========================================================================

// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CAknKeyLockNotifierSubject* CAknKeyLockNotifierSubject::NewL()
    {
    CAknKeyLockNotifierSubject* self = new (ELeave) CAknKeyLockNotifierSubject();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// Second-phase constructor.
// ---------------------------------------------------------------------------
//
void CAknKeyLockNotifierSubject::ConstructL()
    {
    CCoeEnv* environment = CCoeEnv::Static();

    TFileName resourceFile;
    resourceFile.Append( KRESOURCEFILE );
    BaflUtils::NearestLanguageFile( environment->FsSession(), resourceFile );

    iResourceFileOffset = environment->AddResourceFileL( resourceFile );

    iObserverList = new (ELeave) CArrayPtrFlat<MAknKeyLockObserver>(
        KAknObserverListGranularity );

    iKeyLockControl = new (ELeave) CAknKeyLockControl( this );
    iKeyLockControl->ConstructL();
    }


// ---------------------------------------------------------------------------
// Default C++ constructor.
// ---------------------------------------------------------------------------
//
CAknKeyLockNotifierSubject::CAknKeyLockNotifierSubject() :
    iAllowNotifications( ETrue )
    {
    }


// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CAknKeyLockNotifierSubject::~CAknKeyLockNotifierSubject()
    {
    if ( iResourceFileOffset )
        {
        CCoeEnv::Static()->DeleteResourceFile( iResourceFileOffset );
        }
    delete iKeyLockControl;
    delete iObserverList;
    iKeyLockControl = NULL;
    iObserverList = NULL;
    }


// ---------------------------------------------------------------------------
// From base class MEikSrvNotifierBase2.
// Frees all the resources owned by the keylock notifier.
// ---------------------------------------------------------------------------
//
void CAknKeyLockNotifierSubject::Release()
    {
    delete this;
    }


// ---------------------------------------------------------------------------
// From base class MEikSrvNotifierBase2.
// Initialises the keylock notifier.
// ---------------------------------------------------------------------------
//
CAknKeyLockNotifierSubject::TNotifierInfo CAknKeyLockNotifierSubject::RegisterL()
    {
    iInfo.iUid      = KAknKeyLockNotifierUid;
    iInfo.iChannel  = KAknKeyLockNotifierUid;
    iInfo.iPriority = ENotifierPriorityHigh;
    return iInfo;
    }


// ---------------------------------------------------------------------------
// From base class MEikSrvNotifierBase2.
// Gets the notifier parameters.
// ---------------------------------------------------------------------------
//
CAknKeyLockNotifierSubject::TNotifierInfo CAknKeyLockNotifierSubject::Info() const
    {
    return iInfo;
    }


// ---------------------------------------------------------------------------
// From base class MEikSrvNotifierBase2.
// Starts the keylock notifier synchronously.
// ---------------------------------------------------------------------------
//
TPtrC8 CAknKeyLockNotifierSubject::StartL( const TDesC8& aBuffer )
    {
    _AKNTRACE_FUNC_ENTER; 
    
    SAknNotifierPackage<SAknKeyLockNotifierParams>* params =
        ( SAknNotifierPackage<SAknKeyLockNotifierParams>*)aBuffer.Ptr();

    if ( aBuffer.Length() < 0 ||
         (TUint)aBuffer.Length() < sizeof(SAknNotifierPackage<SAknKeyLockNotifierParams>) ||
         params->iSignature != KAKNNOTIFIERSIGNATURE )
        {
        User::Leave( KErrArgument );
        }

    _AKNTRACE( "params->iParamData.iReason:%d",params->iParamData.iReason);
        
    switch ( params->iParamData.iReason )
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
            {
            break;
            }
        case EInquire:
            {
            iRetPckg().iEnabled = IsKeyLockEnabled();
            break;
            }
        default:
            {
            break;
            }
        }

    _AKNTRACE_FUNC_EXIT;
    
    return iRetPckg;
    }


// ---------------------------------------------------------------------------
// From base class MEikSrvNotifierBase2.
// Starts the keylock notifier asynchronously.
// ---------------------------------------------------------------------------
//
void CAknKeyLockNotifierSubject::StartL( const TDesC8& aBuffer,
                                         TInt /*aReplySlot*/,
                                         const RMessagePtr2& aMessage )
    {
    _AKNTRACE_FUNC_ENTER; 
    
    SAknNotifierPackage<SAknKeyLockNotifierParams>* params =
        ( SAknNotifierPackage<SAknKeyLockNotifierParams>*)aBuffer.Ptr();

    if ( aBuffer.Length() < 0 ||
         (TUint)aBuffer.Length() < sizeof(SAknNotifierPackage<SAknKeyLockNotifierParams>) ||
         params->iSignature != KAKNNOTIFIERSIGNATURE )
        {
        User::Leave( KErrArgument );
        }

    _AKNTRACE( "params->iParamData.iReason:%d",params->iParamData.iReason);
    
    switch ( params->iParamData.iReason )
        {
        case ELockEnabled:
            {
            if ( !iKeyLockControl->iAutolockEnabled )
                {
                DoEnableKeyLock();
                }
            break;
            }
        case ELockDisabled:
            {
            // Protect unlocking keys if autolock emulation enabled.
            // Either the application has the right capabilities, or EikSrvs does the calling.
            if ( !iKeyLockControl->iAutolockEnabled ||
                 aMessage.HasCapability( ECapabilityWriteDeviceData ) || aMessage.HasCapability( ECapabilityTrustedUI ) )
                {
                DoDisableKeyLock();
                }
            break;
            }
        case EOfferKeylock:
            {
            DoOfferKeyLock();
            break;
            }
        case EEnableAutoLockEmulation:
            {
            TInt queryActive( ESecurityQueryNotActive );
            TInt autolockActive( EAutolockOff );

            RProperty::Get( KPSUidStartup,
                            KStartupSecurityCodeQueryStatus,
                            queryActive );

            RProperty::Get( KPSUidCoreApplicationUIs,
                            KCoreAppUIsAutolockStatus,
                            autolockActive );

            // Don't activate autolock emulation if there is a sec code query up;
            // our softkey CBA will come on top of its CBA if we do.
            if ( queryActive == ESecurityQueryActive &&
                 autolockActive > EAutolockOff )
                {
                // Do nothing ... The emulation will be activated by Autolock
                // itself in case the query is canceled.
                }
            else
                {
                // Business as usual.
                NotifyStatusChange( EShowSoftNotifications );
                LockKeys( ETrue );
                }
            break;
            }
        case EDisableWithoutNote:
            {
            // Protect unlocking keys if autolock emulation enabled.
            // Either the application has the right capabilities, or EikSrvs does the calling.
            if ( !iKeyLockControl->iAutolockEnabled	||
                 aMessage.HasCapability( ECapabilityWriteDeviceData ) || aMessage.HasCapability( ECapabilityTrustedUI ) )
                {
                UnlockKeys();
                }
            break;
            }
        case EEnableWithoutNote:
            {
            if ( !iKeyLockControl->iAutolockEnabled )
                {
                if ( !IsKeyLockEnabled() )
                    {
                    iKeyLockControl->EnableKeylock( EFalse );
                    }
                }
            break;
            }
        default:
            {
            break;
            }
        };

    _AKNTRACE_FUNC_EXIT;
    
    aMessage.Complete( KErrNone );
    }


// ---------------------------------------------------------------------------
// From base class MEikSrvNotifierBase2.
// Called when the keylock notifier is cancelled.
// ---------------------------------------------------------------------------
//
void CAknKeyLockNotifierSubject::Cancel()
    {
    }


// ---------------------------------------------------------------------------
// From base class MEikSrvNotifierBase2.
// Called when the active keylock notifier's data is updated.
// ---------------------------------------------------------------------------
//
TPtrC8 CAknKeyLockNotifierSubject::UpdateL( const TDesC8& aBuffer )
    {
    return TPtrC8( aBuffer );
    }


// ---------------------------------------------------------------------------
// From base class MAknKeyLockController.
// Gets the current keylock status.
// ---------------------------------------------------------------------------
//
TBool CAknKeyLockNotifierSubject::IsKeyLockEnabled()
    {
    return iKeyLockControl->iKeyLockEnabled;
    }


// ---------------------------------------------------------------------------
// From base class MAknKeyLockController.
// Notifications are always allowed here.
// ---------------------------------------------------------------------------
//
TBool CAknKeyLockNotifierSubject::AllowNotifications()
    {
    return iAllowNotifications;
    }


// ---------------------------------------------------------------------------
// From base class MAknKeyLockController.
// Disables the keylock.
// ---------------------------------------------------------------------------
//
void CAknKeyLockNotifierSubject::UnlockKeys()
    {
    _AKNTRACE_FUNC_ENTER; 
    
    if ( IsKeyLockEnabled() )
        {
        iKeyLockControl->DisableKeylock();
        }
    
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// From base class MAknKeyLockController.
// Enables the keylock.
// ---------------------------------------------------------------------------
//
void CAknKeyLockNotifierSubject::LockKeys( TBool aAutoLockOn )
    {
    _AKNTRACE_FUNC_ENTER; 
    _AKNTRACE( "aAutoLockOn:%d",aAutoLockOn);
    
    // We'll have to disable keylock if we are changing autolock status.
    if ( IsKeyLockEnabled() && aAutoLockOn != iKeyLockControl->iAutolockEnabled )
        {
        iKeyLockControl->DisableKeylock(EFalse);
        }

    if ( !IsKeyLockEnabled() )
        {
        iKeyLockControl->AutolockEnabled( aAutoLockOn );
        iKeyLockControl->EnableKeylock(ETrue, EFalse);
        }
    
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// From base class MAknKeyLockController.
// Adds a keylock status change observer.
// ---------------------------------------------------------------------------
//
void CAknKeyLockNotifierSubject::AddObserverL( MAknKeyLockObserver* aObserver )
    {
    _AKNTRACE_FUNC_ENTER;
    
#if defined(_DEBUG)
    TInt count = iObserverList->Count();
    for ( TInt index = 0; index < count; index++ )
        {
        if ( ((*iObserverList)[index]) == aObserver )
            {
            Panic( EAknPanicKeyLockObserverAlreadyExists );
            }
        }
#endif
    iObserverList->AppendL( aObserver );

    // Make sure that the observer isn't obscuring the keylock CBA
    ShowKeylockCba();
    
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// From base class MAknKeyLockController.
// Removes a keylock status change observer.
// ---------------------------------------------------------------------------
//
void CAknKeyLockNotifierSubject::RemoveObserver( MAknKeyLockObserver* aObserver )
    {
    _AKNTRACE_FUNC_ENTER;
    
    TInt count = iObserverList->Count();
    for ( TInt index = 0; index < count; index++ )
        {
        if ( ((*iObserverList)[index]) == aObserver )
            {
            iObserverList->Delete( index );
            return;
            }
        }
#if defined(_DEBUG)
    Panic( EAknPanicKeyLockObserverNotFound );
#endif
    
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// Notifies the observers of a keylock status change.
// ---------------------------------------------------------------------------
//
void CAknKeyLockNotifierSubject::NotifyStatusChange( TKeyLockStatus aStatus )
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "aStatus:%d",aStatus);
    
    TInt count = iObserverList->Count();
    for ( TInt index = count - 1; index >= 0; index-- )
        {
        ((*iObserverList)[index])->KeyLockStatusChange( aStatus );
        }
    
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// Brings the keylock notifier's CBA visible.
// ---------------------------------------------------------------------------
//
void CAknKeyLockNotifierSubject::ShowKeylockCba()
    {
    _AKNTRACE_FUNC_ENTER;
    
    if ( IsKeyLockEnabled() )
        {
        iKeyLockControl->ShowKeylockCba();
        }
    
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// Enables the keylock.
// ---------------------------------------------------------------------------
//
void CAknKeyLockNotifierSubject::DoEnableKeyLock()
    {
    _AKNTRACE_FUNC_ENTER;
    
    if ( !IsKeyLockEnabled() )
        {
        iKeyLockControl->EnableKeylock();
        }
    
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// Disables the keylock if active.
// ---------------------------------------------------------------------------
//
void CAknKeyLockNotifierSubject::DoDisableKeyLock()
    {
    _AKNTRACE_FUNC_ENTER;
    
    if ( IsKeyLockEnabled() )
        {
        iKeyLockControl->DisableKeylock();
        // Attempt to display KeyActive note.
        iKeyLockControl->DisplayKeyActiveNote();
        }
    else if ( iKeyLockControl->iOfferLockEnabled )
        {
        // Remove the offer key lock CBA.
        iKeyLockControl->OfferTimerExpired();
        }
    
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// Displays the offer keylock note.
// ---------------------------------------------------------------------------
//
void CAknKeyLockNotifierSubject::DoOfferKeyLock()
    {
    _AKNTRACE_FUNC_ENTER;
    
    if ( !IsKeyLockEnabled() )
        {
        NotifyStatusChange( EKeyLockOffered );
        iKeyLockControl->OfferKeylock();
        }
    
    _AKNTRACE_FUNC_EXIT;
    }
