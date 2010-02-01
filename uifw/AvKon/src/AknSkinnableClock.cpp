/*
* Copyright (c) 2006-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implementation for skinnable clock.
*
*/


// SYSTEM INCLUDE FILES
#include <bitdev.h>
#include <eikenv.h>
#include <eikspane.h>
#include <AknsDrawUtils.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <akniconconfig.h>
#include <aknappui.h>
#include <apgcli.h>

#include <AknTasHook.h>
// USER INCLUDE FILES
#include "AknUtils.h"
#include "AknSkinnableClock.h"
#include "AknSkinnableClockFace.h"
#include "aknconsts.h"
#include "AknDef.h"
#include "AknStatuspaneUtils.h"
#include "layoutmetadata.cdl.h"

#include <touchfeedback.h>

// LOCAL CONSTANTS AND MACROS
static const TInt KIntervalTime(60000000); // in microseconds
_LIT( KClockApplication, "\\sys\\bin\\clock.exe" );

// MODULE DATA STRUCTURES
class CAknSkinnableClockChangeHandler : public CActive
    {
    public: // Constructor and destructor
        static CAknSkinnableClockChangeHandler* NewL(
            CAknSkinnableClock& aClient )
            {
            CAknSkinnableClockChangeHandler* self =
                new (ELeave) CAknSkinnableClockChangeHandler( aClient );
            CleanupStack::PushL( self );
            self->ConstructL();
            CleanupStack::Pop( self );
            return self;
            }

        virtual ~CAknSkinnableClockChangeHandler()
            {
            Cancel();
            iChangeNotifier.Close();
            }

    private: // From CActive
        void DoCancel()
            {
            iChangeNotifier.LogonCancel();
            // Return value is ignored.
            }

        void RunL()
            {
            if( iStatus.Int() & ( EChangesLocale | EChangesSystemTime ) )
                {
                iClient.TimeOrLocaleChanged();
                }

            User::LeaveIfError( iChangeNotifier.Logon(iStatus) );
            SetActive();
            }

    private: // Private constructors
        void ConstructL()
            {
            User::LeaveIfError( iChangeNotifier.Create() );
            User::LeaveIfError( iChangeNotifier.Logon( iStatus ) );
            SetActive();
            }

        CAknSkinnableClockChangeHandler( CAknSkinnableClock& aClient )
            : CActive( EPriorityStandard ), iClient( aClient )
            {
            CActiveScheduler::Add( this );
            }

    private: // Data
        RChangeNotifier     iChangeNotifier;
        CAknSkinnableClock& iClient;
    };

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknSkinnableClock::CAknSkinnableClock
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CAknSkinnableClock::CAknSkinnableClock( const TBool aFormatFromLocale,
                                        const TBool aContextPaneClock )
    {
    iFormatFromLocale = aFormatFromLocale;
    iContextPaneClock = aContextPaneClock;

    iClockFormat = TLocale().ClockFormat();
    }

// -----------------------------------------------------------------------------
// CAknSkinnableClock::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CAknSkinnableClock::ConstructL()
    {
    // We observe foreground events in order
    // to stop the clock timer if clock is not visible.
    iCoeEnv->AddMessageMonitorObserverL( *this );

    SetFormatL( iClockFormat );

    iHandler = CAknSkinnableClockChangeHandler::NewL( *this );

    SetHitTest( this );

    // Start timer if necessary.
    // Later on, timer is stopped & restarted in MonitorWsMessage.
    CAknAppUiBase* base =
        static_cast<CAknAppUiBase*>( iEikonEnv->EikAppUi() );
    iInForeground = base->HasFullOrPartialForeground();
    if ( iInForeground )
        {
        StartTimer();
        }

    /* Register MHWRMLightObserver */
    iLight = CHWRMLight::NewL( this );
    }


// -----------------------------------------------------------------------------
// CAknSkinnableClock::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
EXPORT_C CAknSkinnableClock* CAknSkinnableClock::NewL(
    CCoeControl* aContainerWindow,
    const TBool aFormatFromLocale,
    const TBool aContextPaneClock )
    {
    CAknSkinnableClock* self =
        new (ELeave) CAknSkinnableClock( aFormatFromLocale, aContextPaneClock );
    CleanupStack::PushL( self );
    self->SetContainerWindowL( *aContainerWindow );
    self->ConstructL();
    CleanupStack::Pop( self );
    AKNTASHOOK_ADDL( self, "CAknSkinnableClock" );
    return self;
    }


// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------
//
EXPORT_C CAknSkinnableClock::~CAknSkinnableClock()
    {
    AKNTASHOOK_REMOVE();
    iCoeEnv->RemoveMessageMonitorObserver( *this );

    delete iHandler;
    delete iTimer;
    delete iFace;

    delete iLight;
    }




// -----------------------------------------------------------------------------
// CAknSkinnableClock::UpdateDisplay
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknSkinnableClock::UpdateDisplay()
    {
    DrawDeferred();
    }


// -----------------------------------------------------------------------------
// CAknSkinnableClock::TimeOrLocaleChanged
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CAknSkinnableClock::TimeOrLocaleChanged()
    {
    TLocale locale;
    if ( ( locale.ClockFormat() != iClockFormat ) && iFormatFromLocale )
        {
        TRAP_IGNORE( SetFormatL( locale.ClockFormat() ) );
        }
    else
        {
        UpdateDisplay();
        }
    }


// -----------------------------------------------------------------------------
// CAknSkinnableClock::SetFormatL
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknSkinnableClock::SetFormatL( const TClockFormat aFormat )
    {
    if ( Size() != TSize(0,0) ) // Perf optimization
        {
        delete iFace;
        iFace = NULL;

        switch( aFormat )
            {
            case EClockAnalog:
                {
                iFace = CAknSkinnableClockFaceAnalogue::NewL(iContextPaneClock);
                break;
                }
            case EClockDigital:
                {
                iFace = CAknSkinnableClockFaceDigital::NewL();
                break;
                }
            };
        }

    iClockFormat = aFormat;

    UpdateDisplay();
    }





// -----------------------------------------------------------------------------
// CAknSkinnableClock::TimerCallback
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CAknSkinnableClock::TimerCallback( TAny* aThis )
    {
    CAknSkinnableClock* self = static_cast< CAknSkinnableClock* >( aThis );

    // Update the clock display
    self->UpdateDisplay();

    // Adjust the timer delay if necessary
    TTime time;
    time.HomeTime();
    TDateTime dateTime( time.DateTime() );
    if( dateTime.Second() > 0)
        {
        self->iTimer->Cancel();
        self->iTimer->After( KIntervalTime -
            1000000 * dateTime.Second() - dateTime.MicroSecond());
        }

    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CAknSkinnableClock::BufferDisplayMode
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TDisplayMode CAknSkinnableClock::BufferDisplayMode()
    {
    return EColor16MA;
    }


// -----------------------------------------------------------------------------
// CAknSkinnableClock::IsVisibleInContextPane
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TBool CAknSkinnableClock::IsVisibleInContextPane() const
    {
    CEikStatusPaneBase* statusPane = CEikStatusPaneBase::Current();
    TRect screenRect;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, screenRect );

    if ( statusPane && statusPane->PaneCapabilities(
        TUid::Uid( EEikStatusPaneUidClock ) ).IsInCurrentLayout() )
        {
        return ETrue;
        }
    else if ( screenRect.Width() > screenRect.Height() &&
              AknStatuspaneUtils::IdleLayoutActive() )
        {
        // in landscape phone/idle shows the clock
        return ETrue;
        }

    return EFalse;
    }


// -----------------------------------------------------------------------------
// CAknSkinnableClock::HandleResourceChange
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CAknSkinnableClock::HandleResourceChange( TInt aType )
    {
    if ( aType == KEikDynamicLayoutVariantSwitch )
        {
        // Face needs to be resized too...
        TRAP_IGNORE( SetFormatL( iClockFormat ) );
        // Setformat calls UpdateDisplay, no need to update it manually.
        }
    else if ( aType == KAknsMessageSkinChange )
        {
        UpdateDisplay();
        }
    }


// -----------------------------------------------------------------------------
// CAknSkinnableClock::HitRegionContains
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TBool CAknSkinnableClock::HitRegionContains(
    const TPoint &aPoint,
    const CCoeControl& /*aControl*/ ) const
    {
    TBool handleEvent( EFalse );

    if ( Rect().Contains( aPoint ) )
        {
        TVwsViewId idleView;
        TInt err = AknDef::GetPhoneIdleViewId( idleView );
        if ( !err )
            {
            RWsSession& wsSession = iCoeEnv->WsSession();

            TApaTaskList taskList( wsSession );
            TApaTask idle( taskList.FindApp( idleView.iAppUid ) );

            if ( idle.Exists() )
                {
                TThreadId id;
                wsSession.GetWindowGroupClientThreadId(
                    wsSession.GetFocusWindowGroup(), id );

                if ( id == idle.ThreadId() )
                    {
                    handleEvent = ETrue;
                    }
                }
            }
        }

    return handleEvent;
    }


// -----------------------------------------------------------------------------
// CAknSkinnableClock::PositionChanged
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknSkinnableClock::PositionChanged()
    {
    CCoeControl::PositionChanged();
    }


// -----------------------------------------------------------------------------
// CAknSkinnableClock::Draw
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CAknSkinnableClock::Draw( const TRect& /*aRect*/ ) const
    {

    CWindowGc& gc = SystemGc();
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = AknsDrawUtils::ControlContext(this);
    TRect rect(Rect());

    gc.SetPenStyle(CGraphicsContext::ENullPen);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.SetBrushColor(KRgbWhite);

    AknsDrawUtils::Background(skin, cc, this, gc, rect);

    gc.SetPenStyle(CGraphicsContext::ESolidPen);
    gc.SetBrushStyle(CGraphicsContext::ENullBrush);

    TTime homeTime;
    homeTime.HomeTime();
    if (iFace)
        {
        iFace->DrawTimeToBitmapL(rect, gc, homeTime);
        }
    }


// -----------------------------------------------------------------------------
// CAknSkinnableClock::HandlePointerEventL
// Changes clock format between digital and analog in down event.
// The clock format is saved then to TLocale
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknSkinnableClock::HandlePointerEventL(
    const TPointerEvent& aPointerEvent )
    {
    if ( AknLayoutUtils::PenEnabled() )
        {
        // Do nothing if dimmed.
        if ( IsDimmed() )
            {
            return;
            }

        // Tactile feedback is played on both down and up event    
        if ( aPointerEvent.iType == TPointerEvent::EButton1Down
                && Rect().Contains( aPointerEvent.iPosition ))
            {
            MTouchFeedback* feedback = MTouchFeedback::Instance();
            if (feedback)
                {
                feedback->InstantFeedback( this, 
                                           ETouchFeedbackSensitiveButton, 
                                           aPointerEvent );
                }
            }

        // Start clock application
        if ( aPointerEvent.iType == TPointerEvent::EButton1Up
                && Rect().Contains( aPointerEvent.iPosition ))
            {
            MTouchFeedback* feedback = MTouchFeedback::Instance();
            if (feedback)
                {
                // on up-event, only vibra feedback (no sound) is played
                feedback->InstantFeedback( this, 
                                           ETouchFeedbackSensitiveButton, 
                                           ETouchFeedbackVibra, 
                                           aPointerEvent );
                }
            RApaLsSession apa;
            User::LeaveIfError( apa.Connect() );
            CleanupClosePushL( apa );
            CApaCommandLine* cmdLine = CApaCommandLine::NewLC();
            cmdLine->SetExecutableNameL( KClockApplication );
            cmdLine->SetCommandL( EApaCommandRun );
            User::LeaveIfError( apa.StartApp( *cmdLine ) );
            CleanupStack::PopAndDestroy( 2, &apa ); // cmdLine and apa
            }
        }
    }


// -----------------------------------------------------------------------------
// CAknSkinnableClock::SizeChanged
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CAknSkinnableClock::SizeChanged()
    {
     TRAP_IGNORE( SetFormatL(iClockFormat) );
    }


// ---------------------------------------------------------------------------
// CAknSkinnableClock::MakeVisible
// (other items were commented in a header).
// ---------------------------------------------------------------------------
//
void CAknSkinnableClock::MakeVisible( TBool aVisible )
    {
    CCoeControl::MakeVisible( aVisible );

    if ( !aVisible )
        {
        // Stop the timer if this control is made non-visible.
        // This control may exist in status pane layouts which
        // don't show clock, and in those it's hidden via
        // this method, so no need to keep the timer running.
        StopTimer();
        }
    else if ( iInForeground )
        {
        StartTimer();
        }
    }


// ---------------------------------------------------------------------------
// CAknSkinnableClock::MonitorWsMessage
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CAknSkinnableClock::MonitorWsMessage( const TWsEvent& aEvent )
    {
    switch ( aEvent.Type() )
        {
        case KAknFullOrPartialForegroundGained:
            {
            iInForeground = ETrue;

            TRAP_IGNORE( ForegroundGainedL() );
            break;
            }

        case KAknFullOrPartialForegroundLost:
            {
            iInForeground = EFalse;
            StopTimer();

            // Ensure that the clock gets drawn with only skin background.
            // This has a similar kind of effect as clearing the redraw
            // store at this point, but produces less flicker.
            DrawDeferred();

            break;
            }

        default:
            break;
        }
    }


// -----------------------------------------------------------------------------
// CAknSkinnableClock::StartTimer
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CAknSkinnableClock::StartTimer()
    {
    if ( !iTimer )
        {
        iTimer = CPeriodic::New( CActive::EPriorityHigh );
        }

    if ( iTimer && !iTimer->IsActive() )
        {
        // Need to update first.
        UpdateDisplay();

        TTime time;
        time.HomeTime();
        TDateTime dateTime( time.DateTime() );
        TCallBack callBack( TimerCallback, this );

        iTimer->Start(
            TTimeIntervalMicroSeconds32(
                KIntervalTime - 1000000 * dateTime.Second() - dateTime.MicroSecond() ),
            TTimeIntervalMicroSeconds32( KIntervalTime ),
            callBack );
        }
    }


// -----------------------------------------------------------------------------
// CAknSkinnableClock::StopTimer
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CAknSkinnableClock::StopTimer()
    {
    if ( iTimer && iTimer->IsActive() )
        {
        iTimer->Cancel();
        }

    // Ensure the CPeriodic timer stops by destroying it, see Symbian SDK.
    delete iTimer;
    iTimer = NULL;
    }


// ---------------------------------------------------------------------------
// CAknSkinnableClock::ForegroundGainedL
// Contains the leaving function calls in the foreground gain situation.
// ---------------------------------------------------------------------------
//
void CAknSkinnableClock::ForegroundGainedL()
    {
    if ( IsVisible() )
	    {
	    StartTimer();
	    }
    }


void CAknSkinnableClock::LightStatusChanged(TInt aTarget,
                                            CHWRMLight::TLightStatus aStatus)
    {
    if( aTarget == CHWRMLight::EPrimaryDisplay
        || aTarget == CHWRMLight::EPrimaryDisplayAndKeyboard )
        {
        if( aStatus == CHWRMLight::ELightOn && iInForeground )
            {
            StartTimer();
            }
        else if( aStatus == CHWRMLight::ELightOff )
            {
            StopTimer();
            }
        }
    }

//  End of File
