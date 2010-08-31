/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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


#include "aknmessagereaderlongpressdetector.h"
#include <AknUtils.h>
#include <aknkeylock.h>
#include <e32base.h>
#include <eikbtgrp.h>
#include <apgcli.h>
#include <e32property.h>
#include <avkondomainpskeys.h> // keyguard state (KPSUidAvkonDomain, KAknKeyguardStatus)
#include <layoutmetadata.cdl.h>
#include <aknlayoutscalable_avkon.cdl.h>

const TInt KMessageReaderUid = 0x10201B00;
const TInt KDefaultLongPressInterval = 800000; // default value is 0.8 seconds
const TInt KNegativePointerPosition = -1;

/**
*  CAknPhoneLockObserver class. 
*  Detects whether Keyguard is currently enabled or not
*
*  @lib   AknOldStyleNotif.lib
*  @since 3.2
*/  
NONSHARABLE_CLASS(CAknPhoneLockObserver) : public CActive
    {
public:
    /**
     * Creates instance of the CAknPhoneLockObserver class.
     *
     * @param aObserver (pointer to observer)
     */
    static CAknPhoneLockObserver* NewL( CAknMessageReaderLongPressDetector& aParent );

    /**
     * Destructor.
     */
    ~CAknPhoneLockObserver();

    /**
     * Start observing.
     */
    TInt Start();

    /**
     * Stop observing.
     */
    void Stop();

    /**
     * If either keyguard or devicelock is enabled
     *
     * @return ETrue if phone is locked
     */
     inline TBool PhoneLocked() 
        {
        return iPhoneLocked;
        };

protected:

    /**
     * C++ default constructor.
     *
     * @param aObserver observer
     */
    CAknPhoneLockObserver( CAknMessageReaderLongPressDetector& aParent );
    
    /**
     * Symbian OS constructor.
     */
    void ConstructL();

private: // from CActive    

    /** @see CActive::RunL() */
    void RunL();

    /** @see CActive::DoCancel() */
    void DoCancel();

    /**
     * Update phone lock status (phone locked if keyguard or autolock emulation is active)
     * @return symbian error value
     */
    TInt UpdatePhoneLockStatus();
    
private: // data

    RProperty iProperty;
    TBool iPhoneLocked;
    
    // reference to the parent
    CAknMessageReaderLongPressDetector& iParent;
    };

// ================= MEMBER FUNCTIONS =======================

// ----------------------------------------------------------
// Two-phased constructor.
// ----------------------------------------------------------
//
CAknPhoneLockObserver* CAknPhoneLockObserver::NewL( CAknMessageReaderLongPressDetector& aParent )
    {
    CAknPhoneLockObserver* self = new (ELeave) CAknPhoneLockObserver( aParent );
    CleanupStack::PushL( self );
    self->ConstructL( );
    CleanupStack::Pop( self ); //self
    return self;
    }

// ----------------------------------------------------------
// C++ default constructor
// ----------------------------------------------------------
//    
CAknPhoneLockObserver::CAknPhoneLockObserver( CAknMessageReaderLongPressDetector& aParent ) :
    CActive(0), iParent( aParent )
    {
    }

// ----------------------------------------------------------
// Destructor
// ----------------------------------------------------------
//
CAknPhoneLockObserver::~CAknPhoneLockObserver( )
    {
    Cancel( );
    iProperty.Close( );
    }

// ----------------------------------------------------------
// Symbian OS default constructor
// ----------------------------------------------------------
//    
void CAknPhoneLockObserver::ConstructL( )
    {
    // Add this active object to the scheduler.
    CActiveScheduler::Add( this );
    TRAPD(err, iProperty.Attach( KPSUidAvkonDomain, KAknKeyguardStatus ) )
    User::LeaveIfError( err );
    }
    
// ----------------------------------------------------------
// Starts listening 
// ----------------------------------------------------------
//
TInt CAknPhoneLockObserver::Start( )
    {
    if ( IsActive( ) )
        return KErrInUse;
    iStatus = KRequestPending;
    iProperty.Subscribe( iStatus );
    SetActive( );
    UpdatePhoneLockStatus();
    return KErrNone;
    }

// ----------------------------------------------------------
// Stops listening
// ----------------------------------------------------------
//
void CAknPhoneLockObserver::Stop( )
    {
    if ( !IsActive() )
        return;
    Cancel( );
    iProperty.Cancel( );
    }

TInt CAknPhoneLockObserver::UpdatePhoneLockStatus()
    {
    TInt value( NULL);
    TInt err( KErrNone );
    err = iProperty.Get( value );
    if ( err == KErrNone )
        {
        // either devicelock or keyguard is enabled
        iPhoneLocked = (value == EKeyguardNotActive) ? EFalse : ETrue;
        }
    return err;
    }
// ----------------------------------------------------------
// CAknPhoneLockObserver::RunL()
// ----------------------------------------------------------
// 
void CAknPhoneLockObserver::RunL( )
    {
    UpdatePhoneLockStatus();
    // re-subscribe to events
    iParent.KeysLocked( iPhoneLocked );     
    Start();
    }

// ----------------------------------------------------------
// Cancels event listening
// ----------------------------------------------------------
// 
void CAknPhoneLockObserver::DoCancel()
    {
    iProperty.Cancel();
    }
        
// ----------------------------------------------------------------------------
// Standard two-phased construction
// ----------------------------------------------------------------------------
//
CAknMessageReaderLongPressDetector* CAknMessageReaderLongPressDetector::NewL( CEikButtonGroupContainer* aGlobalNoteBGContainer, RWindow& aGlobalNoteWindow )
    {
    CAknMessageReaderLongPressDetector* self = new (ELeave) CAknMessageReaderLongPressDetector( aGlobalNoteBGContainer, aGlobalNoteWindow );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ----------------------------------------------------------------------------
// C++ destructor, only CPeriodic timer is owned
// ----------------------------------------------------------------------------
//
CAknMessageReaderLongPressDetector::~CAknMessageReaderLongPressDetector()
    {
    Disable();
    if ( iLongPressTimer )
        {
        delete iLongPressTimer;
        }    
    if ( iPhoneLockObserver )
        {
        delete iPhoneLockObserver;
        }
    }
    
// ----------------------------------------------------------------------------
// C++ constructor
// ----------------------------------------------------------------------------
//
CAknMessageReaderLongPressDetector::CAknMessageReaderLongPressDetector( CEikButtonGroupContainer* aGlobalNoteBGContainer, RWindow& aGlobalNoteWindow ) :
    iGlobalNoteBGContainer( aGlobalNoteBGContainer ), iGlobalNoteWindow( aGlobalNoteWindow )
    {
    // Do nothing
    }

// ----------------------------------------------------------------------------
// Symbian constructor
// ----------------------------------------------------------------------------
//
void CAknMessageReaderLongPressDetector::ConstructL()
    {
    TInt leftSoftKeyPosition( NULL );   
    MEikButtonGroup* buttonGroup = iGlobalNoteBGContainer->ButtonGroup();
    TInt commandId = buttonGroup->CommandId( leftSoftKeyPosition );
    iLeftSoftKeyControl = buttonGroup->GroupControlById( commandId );
        
    iPhoneLockObserver = CAknPhoneLockObserver::NewL( *this );
    }

// ----------------------------------------------------------------------------
// Determine if message reader has been installed on the device or not
// ----------------------------------------------------------------------------
//
TBool CAknMessageReaderLongPressDetector::MessageReaderInstalled()
    {
    TBool messageReaderDetected( EFalse );
    RApaLsSession appArcSession;
    TInt err = appArcSession.Connect();
    if ( err == KErrNone )
        {
        TApaAppInfo applicationInfo;
        err = appArcSession.GetAppInfo( applicationInfo, TUid::Uid(KMessageReaderUid));
        // GetAppInfo returns KErrNotFound if application hasn't been installed
        if ( err == KErrNone )
            {
            messageReaderDetected = ETrue;
            }
        }
    appArcSession.Close();    
    return messageReaderDetected;
    }

// ----------------------------------------------------------------------------
// Soft notification is on/off the screen
// ----------------------------------------------------------------------------
//
void CAknMessageReaderLongPressDetector::SoftNotifierVisible( TBool aVisible )
    {
    iSoftNotifierVisible = aVisible;
    if ( iSoftNotifierVisible )
        {
        // start observing keyguard value, only detect if keyguard is enabled
        iPhoneLockObserver->Start();        
        
        // enable detector if phone is not locked
        if ( !iPhoneLockObserver->PhoneLocked() )
            {
            Enable();
            }
        }
        
    // if the soft notifier is no longer on the screen, disable detector
    else
        {
        Disable();
        // phone lock observer is only active when any soft notifier is visible
        iPhoneLockObserver->Stop();        
        }
    }


// ----------------------------------------------------------------------------
// Phone keys are locked
// ----------------------------------------------------------------------------
//
void CAknMessageReaderLongPressDetector::KeysLocked( TBool aLocked )
    {
    // enable detector if soft notifiers are visible and keys aren't locked
    if ( iSoftNotifierVisible && !aLocked )
        {
        Enable();
        }
    // if keys were locked, disable detector
    else if ( aLocked )
        {
        Disable();
        }
    }

// ----------------------------------------------------------------------------
// Give global note subject a access to grouped note information
// ----------------------------------------------------------------------------
//        
void CAknMessageReaderLongPressDetector::SetMessageNotifierObserver( MAknMessageNotifierObserver* aMessageNotifierObserver )
    {
    iMessageNotifierObserver = aMessageNotifierObserver;
    }
        
// ----------------------------------------------------------------------------
// Enable left soft key long press detection (soft notifier is activated)
// ----------------------------------------------------------------------------
//
void CAknMessageReaderLongPressDetector::Enable()
    {
    // Only enable long press capture when messaging note is being displayed.
    if (!iDetectorEnabled && 
        iMessageNotifierObserver && iMessageNotifierObserver->MessageNotifierShown())
        {
        iDetectorEnabled = ETrue;
        if ( iCaptureLongKeyHandle == 0 ) 
            {   
            const TInt KCapturePriority = 10;
            RWindowGroup wg = CCoeEnv::Static()->RootWin();
             
            iCaptureLongKeyHandle = wg.CaptureLongKey( EKeyCBA1, EKeyCBA1, 0, 0, 
                                                       KCapturePriority, 
                                                       ELongCaptureWaitShort );
            }
        iLSKKeyDownDetect = EFalse;
#ifdef _DEBUG            
        RDebug::Print( _L("CAknMessageReaderLongPressDetector::Enable"));
#endif
        }
    }

// ----------------------------------------------------------------------------
// Disable left soft key long press detection (soft notifier is deactivated)
// ----------------------------------------------------------------------------
//
void CAknMessageReaderLongPressDetector::Disable()
    {
    if ( iDetectorEnabled )
        {
        iDetectorEnabled = EFalse;
        if ( iCaptureLongKeyHandle > 0 )    
            {
            RWindowGroup wg = CCoeEnv::Static()->RootWin();
              
            wg.CancelCaptureLongKey( iCaptureLongKeyHandle );
               
            iCaptureLongKeyHandle = 0;
            }
          
        // reset long press detection
        StopLongPressTimer();
#ifdef _DEBUG            
        RDebug::Print( _L("CAknMessageReaderLongPressDetector::Disable"));
#endif
        }
    }    

// ----------------------------------------------------------------------------
// Handle key and pointer events for detecting left soft key long presses
// ----------------------------------------------------------------------------
//
TBool CAknMessageReaderLongPressDetector::HandleWsEventL( const TWsEvent& aEvent, CCoeControl* aDestination )
    {
    TBool consumeEvent( EFalse );

    // only handle events when soft notifiers are visible and phone is not locked
    if ( iSoftNotifierVisible && !iPhoneLockObserver->PhoneLocked() )
        {
        // only detect long presses if there are unread message notifications
        if ( iMessageNotifierObserver && iMessageNotifierObserver->MessageNotifierShown() )
            {
            TInt eventType( aEvent.Type() );
            const TKeyEvent keyEvent( *aEvent.Key() );
            
            if (eventType == EEventKeyDown && (keyEvent.iScanCode == EStdKeyDevice0))
                {
                iLSKKeyDownDetect = ETrue;
                }

            if (eventType == EEventKey && iLSKKeyDownDetect)
                {
                if ( keyEvent.iCode == EKeyCBA1 && keyEvent.iRepeats == 1 )
                    {
                    consumeEvent = ETrue;
                    LaunchMessageReaderL();
                    }
                }
            else if ( eventType == EEventPointer )
                {
                consumeEvent = HandleLongTouchL( *aEvent.Pointer(), aDestination );
                }       
            }
        }
    
    return consumeEvent;
    }

TBool CAknMessageReaderLongPressDetector::IsPointerInLeftSoftKeyRect(TPoint aPoint, CCoeControl* aDestination)
    {
    TBool pointInLSK = EFalse;
    
    if (aDestination != NULL && iLeftSoftKeyControl != NULL)
        {
        if (aDestination == iLeftSoftKeyControl)
            {
            pointInLSK = ETrue;
            }
        else if (aDestination == iLeftSoftKeyControl->Parent())
            {
            // Copy codes from CEikCba class.
            TRect containerRect(aDestination->Rect());
            TAknLayoutRect layoutRect;
            TRect button1Rect(0, 0, 0, 0);
            
            if (Layout_Meta_Data::IsLandscapeOrientation())
                {
                TAknWindowComponentLayout rightAreaLayout(
                    AknLayoutScalable_Avkon::area_side_right_pane(0));
                    
                layoutRect.LayoutRect(
                        containerRect,
                        TAknWindowComponentLayout::Compose(
                                    rightAreaLayout,
                                    AknLayoutScalable_Avkon::sctrl_sk_bottom_pane()).LayoutLine());
                
                TRect bottomSKRect(layoutRect.Rect());

                layoutRect.LayoutRect(
                        bottomSKRect,
                        AknLayoutScalable_Avkon::aid_touch_sctrl_bottom().LayoutLine());
                
                button1Rect = layoutRect.Rect();
                }
            else
                {
                if (AknLayoutUtils::LayoutMirrored())
                    {
                    layoutRect.LayoutRect(
                            containerRect,
                            AknLayoutScalable_Avkon::aid_touch_ctrl_right().LayoutLine());
                    
                    button1Rect = layoutRect.Rect();
                    }
                else
                    {
                    layoutRect.LayoutRect(
                            containerRect,
                            AknLayoutScalable_Avkon::aid_touch_ctrl_left().LayoutLine());
                    
                    button1Rect = layoutRect.Rect();
                    }
                }
            
            if (button1Rect.Contains(aPoint))
                {
                pointInLSK = ETrue;
                }
            }
        }
    
    return pointInLSK;
    }


// ----------------------------------------------------------------------------
// Handle pointer events for detecting left soft key long presses
// ----------------------------------------------------------------------------
//
TBool CAknMessageReaderLongPressDetector::HandleLongTouchL(const TPointerEvent& aPointerEvent, CCoeControl* aDestination )
    {    
    // Only test the cba's pointer event, iLeftSoftKeyControl->Rect() only is the text rect of cba button.
    // So, we need to check the parent rect of iLeftSoftKeyControl.
    TBool leftSoftkeyClicked = IsPointerInLeftSoftKeyRect(aPointerEvent.iPosition, aDestination);
    
    // start the timer when the pointer event is in the left soft key area and pressed down
    if ( leftSoftkeyClicked && aPointerEvent.iType == TPointerEvent::EButton1Down ) 
        {
#ifdef _DEBUG            
    RDebug::Print( _L("CAknMessageReaderLongPressDetector::HandleLongTouchL - long LSK touch detection activated"));
#endif        
        StartLongPressTimerL();
        iPointerDestination = aDestination;
        }
        
    // stop the timer when the pointer event is outside the area or released
    if ( !leftSoftkeyClicked || aPointerEvent.iType == TPointerEvent::EButton1Up )
        {
        StopLongPressTimer();
#ifdef _DEBUG            
    RDebug::Print( _L("CAknMessageReaderLongPressDetector::HandleLongTouchL - short LSK touch press"));
#endif          
        }
        
    return EFalse;
    } 

// ----------------------------------------------------------------------------
// Launch message reader application
// ----------------------------------------------------------------------------
// 
void CAknMessageReaderLongPressDetector::LaunchMessageReaderL()
    {
    // disable detector
    Disable();

    // launch message reader    
    RApaLsSession ls;                   
    User::LeaveIfError(ls.Connect());   
    CleanupClosePushL(ls);
    CApaCommandLine* cmdLine=CApaCommandLine::NewLC();
    cmdLine->SetCommandL(EApaCommandRun); 
    TApaAppInfo applicationInfo; 
    ls.GetAppInfo( applicationInfo, TUid::Uid(KMessageReaderUid) );
    cmdLine->SetExecutableNameL( applicationInfo.iFullName );
    cmdLine->SetTailEndL( _L8("ui=read_new") );
    ls.StartApp( *cmdLine ); 
    CleanupStack::PopAndDestroy(2); // cmdLine, ls

#ifdef _DEBUG            
    RDebug::Print( _L("CAknMessageReaderLongPressDetector::LaunchMessageReaderL - Messagereader launched"));
#endif  
    }


// ----------------------------------------------------------------------------
// Long press timer calls this method when timeout is passed
// ----------------------------------------------------------------------------
// 
TInt CAknMessageReaderLongPressDetector::ReportLongPressL( TAny* aThis )
    {
    static_cast<CAknMessageReaderLongPressDetector*>( aThis )->DoReportLongPressL();
    return 0;
    }

// ----------------------------------------------------------------------------
// Long press timer calls this method when timeout is passed
// ----------------------------------------------------------------------------
// 
void CAknMessageReaderLongPressDetector::DoReportLongPressL()
    {
    // release the soft button 
    TPointerEvent releaseButton;
    releaseButton.iPosition = TPoint( NULL, KNegativePointerPosition );
    releaseButton.iType = TPointerEvent::EDrag;
    releaseButton.iModifiers = NULL;
    iPointerDestination->HandlePointerEventL( releaseButton );

    // launch message reader
    LaunchMessageReaderL();

#ifdef _DEBUG            
    RDebug::Print( _L("CAknMessageReaderLongPressDetector::DoReportLongPressL - long LSK key press"));
#endif          
    }

// ----------------------------------------------------------------------------
// Start long press timer
// ----------------------------------------------------------------------------
// 
void CAknMessageReaderLongPressDetector::StartLongPressTimerL()
    {
    // create timer if needed
    if ( !iLongPressTimer )
        {
        iLongPressTimer = CPeriodic::NewL( CActive::EPriorityStandard );
        }
    // reset timer if already active    
    else if ( iLongPressTimer->IsActive() )
        {
        iLongPressTimer->Cancel();
        }
    // start timer
    iLongPressTimer->Start( KDefaultLongPressInterval, KDefaultLongPressInterval,
        TCallBack( ReportLongPressL, this ) );
    
    }

// ----------------------------------------------------------------------------
// Stop long press timer
// ----------------------------------------------------------------------------
// 
void CAknMessageReaderLongPressDetector::StopLongPressTimer()
    {
    if ( iLongPressTimer && iLongPressTimer->IsActive() )
        {
        iLongPressTimer->Cancel();
        }
    }
    
// End of File.
