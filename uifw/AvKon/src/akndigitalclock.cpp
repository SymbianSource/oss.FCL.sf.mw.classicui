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
* Description:  Implementation for digital clock control.
*
*/


// SYSTEM INCLUDE FILES
#include <AknControl.h>
#include <AknUtils.h>
#include <AknsDrawUtils.h>
#include <AknLayoutFont.h>
#include <AknStatuspaneUtils.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <eikspane.h>
#include <AknSmallIndicator.h>
#include <touchfeedback.h>
#include <AknTasHook.h>

// USER INCLUDE FILES
#include "akndigitalclock.h"

// LOCAL CONSTANTS AND MACROS
static const TInt KIntervalTime( 60000000 ); // in microseconds
_LIT( KTimeFormat, "%-B%J%:1%T%+B" );

enum TAknDigitalClockFlags
    {
    EAknDigitalClockButton1DownReceived = 0x00000001,
    EAknDigitalClockInStatusPane        = 0x00000002
    };

// MODULE DATA STRUCTURES
class CAknDigitalClockChangeHandler : public CActive
    {
public: // Constructor and destructor
    static CAknDigitalClockChangeHandler* NewL(
        CAknDigitalClock& aClient )
        {
        CAknDigitalClockChangeHandler* self =
            new (ELeave) CAknDigitalClockChangeHandler( aClient );
        CleanupStack::PushL( self );
        self->ConstructL();
        CleanupStack::Pop( self );
        return self;
        }

    virtual ~CAknDigitalClockChangeHandler()
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
            iClient.AdjustPositionL();
            iClient.DrawDeferred();
            }

        User::LeaveIfError( iChangeNotifier.Logon( iStatus ) );
        SetActive();
        }

private: // Private constructors
    void ConstructL()
        {
        User::LeaveIfError( iChangeNotifier.Create() );
        User::LeaveIfError( iChangeNotifier.Logon( iStatus ) );
        SetActive();
        }

    CAknDigitalClockChangeHandler( CAknDigitalClock& aClient )
        : CActive( EPriorityStandard ), iClient( aClient )
        {
        CActiveScheduler::Add( this );
        }

private: // Data
    RChangeNotifier iChangeNotifier;
    CAknDigitalClock& iClient;
    };

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknDigitalClock::CAknDigitalClock
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CAknDigitalClock::CAknDigitalClock( TBool aInStatusPane )
    {
    if ( aInStatusPane )
        {
        iFlags |= EAknDigitalClockInStatusPane;
        }
    }


// -----------------------------------------------------------------------------
// CAknDigitalClock::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CAknDigitalClock::ConstructL()
    {
    iHandler = CAknDigitalClockChangeHandler::NewL( *this );

    iColor = KRgbBlack;

    iTimeFormat = TLocale().TimeFormat();
    AdjustPositionL();
    }


// -----------------------------------------------------------------------------
// CAknDigitalClock::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CAknDigitalClock* CAknDigitalClock::NewL( CCoeControl* aContainerWindow,
                                          TBool aInStatusPane )
    {
    CAknDigitalClock* self =
        new (ELeave) CAknDigitalClock( aInStatusPane );
    CleanupStack::PushL( self );
    self->SetContainerWindowL( *aContainerWindow );
    self->ConstructL();
    CleanupStack::Pop( self );
    AKNTASHOOK_ADDL( self, "CAknDigitalClock" );
    return self;
    }


// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------
//
CAknDigitalClock::~CAknDigitalClock()
    {
    AKNTASHOOK_REMOVE();
    MTouchFeedback* feedback = MTouchFeedback::Instance();
    if ( feedback )
        {
        feedback->RemoveFeedbackForControl(this);
        }

    delete iHandler;
    delete iTimer;
    }


// -----------------------------------------------------------------------------
// CAknDigitalClock::TimerCallback
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CAknDigitalClock::TimerCallback( TAny* aThis )
    {
    CAknDigitalClock* self = static_cast<CAknDigitalClock*>( aThis );

    self->DrawDeferred();

    // Adjust the timer delay if necessary
    TTime time;
    time.HomeTime();
    TDateTime dateTime = time.DateTime();
    if ( dateTime.Second() > 0 )
        {
        self->iTimer->Cancel();
        self->iTimer->After( KIntervalTime -
            1000000 * dateTime.Second() - dateTime.MicroSecond() );
        }

    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CAknDigitalClock::AdjustPositionL
// This method is called when the time format of the clock is changed.
// In nHD status pane layouts the small digital clock and universal indicator
// pane positions depend on the clock's time format.
// -----------------------------------------------------------------------------
//
void CAknDigitalClock::AdjustPositionL()
    {
    TInt format( TLocale().TimeFormat() );

    if ( iFlags & EAknDigitalClockInStatusPane &&
         AknStatuspaneUtils::HDLayoutActive() )
        {
        CEikStatusPaneBase* sp = CEikStatusPaneBase::Current();

        if ( sp && format != iTimeFormat )
            {
            CCoeControl* indicatorControl =
                sp->ContainerControlL(
                    TUid::Uid( EEikStatusPaneUidIndic ) );

            CCoeControl* clockControl =
                sp->ContainerControlL(
                    TUid::Uid( EEikStatusPaneUidDigitalClock ) );

            if ( indicatorControl )
                {
                TBool flatLayoutActive( AknStatuspaneUtils::FlatLayoutActive() );

                TRect spRect;
                AknLayoutUtils::LayoutMetricsRect(
                    AknLayoutUtils::EStatusPane,
                    spRect );

                TAknLayoutRect layoutRect;

                if ( !flatLayoutActive )
                    {
                    // Indicator pane position does not change in the
                    // flat layout.
                    layoutRect.LayoutRect(
                        spRect,
                        format == ETime12 ?
                            AknLayoutScalable_Avkon::indicator_nsta_pane( 3 ) :
                            AknLayoutScalable_Avkon::indicator_nsta_pane_cp_24( 3 ) );
                    TRect indicRect( layoutRect.Rect() );

                    indicatorControl->SetRect( indicRect );
                    }

                if ( clockControl )
                    {
                    layoutRect.LayoutRect(
                        spRect,
                        format == ETime12 ?
                            AknLayoutScalable_Avkon::clock_nsta_pane(
                                flatLayoutActive ? 3 : 2 ) :
                            AknLayoutScalable_Avkon::clock_nsta_pane_cp_24(
                                flatLayoutActive ? 11 : 2 ) );
                    TRect clockRect( layoutRect.Rect() );

                    clockControl->SetRect( clockRect );
                    }

                sp->DrawNow();
                }
            }
        }
    MTouchFeedback* feedback = MTouchFeedback::Instance();
    if (feedback )
        {
        CFeedbackSpec* fbSpec = CFeedbackSpec::New();
        if ( fbSpec )
            {
            fbSpec->AddFeedback( ETouchEventStylusDown,
                                 ETouchFeedbackSensitiveButton );
            fbSpec->AddFeedback( ETouchEventStylusUp,
                                 ETouchFeedbackSensitiveButton,
                                 ETouchFeedbackVibra );

            feedback->SetFeedbackArea( this,
                                       0,
                                       Rect(),
                                       fbSpec );
            delete fbSpec; 
            }        
        }

    iTimeFormat = format;

    }


// -----------------------------------------------------------------------------
// CAknDigitalClock::HandleResourceChange
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CAknDigitalClock::HandleResourceChange( TInt aType )
    {
    if ( aType == KAknsMessageSkinChange ||
         aType == KEikDynamicLayoutVariantSwitch )
        {
        DrawDeferred();
        }
    return;
    }


// -----------------------------------------------------------------------------
// CAknDigitalClock::Draw
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CAknDigitalClock::Draw( const TRect& /*aRect*/ ) const
    {
    // Draw the time only if text layout has been set and
    // the clock timer is running, which means that the clock is on
    // full or partial foreground. In case the clock is drawn when it's
    // on the background, then only the skin background gets drawn.
    if ( iTimeLayoutInUse && iTimer && iTimer->IsActive() )
        {
        CWindowGc& gc = SystemGc();

        TRect rect( Rect() );

        if ( iFlags & EAknDigitalClockInStatusPane )
            {
            MAknsSkinInstance* skin = AknsUtils::SkinInstance();
            MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );
            AknsDrawUtils::Background( skin, cc, this, gc, Rect() );
            }

        const TInt KMaxTextSize = 6 + KMaxAmPmName + 1;

        TBuf<KMaxTextSize> time;

        TAknLayoutText layoutText;
        layoutText.LayoutText( rect, iTimeLayout);

        TTime homeTime;
        homeTime.HomeTime();

        TRAP_IGNORE( homeTime.FormatL( time, KTimeFormat ) );

        // Before drawing do the arabic indic digit etc. conversions
        AknTextUtils::DisplayTextLanguageSpecificNumberConversion( time );

        // Finally draw.
        layoutText.DrawText( gc, time, ETrue, iColor);
        }
    }


// -----------------------------------------------------------------------------
// CAknDigitalClock::HandlePointerEventL
// Starts clock application in down event.
// -----------------------------------------------------------------------------
//
void CAknDigitalClock::HandlePointerEventL( const TPointerEvent& aPointerEvent )
    {
    CAknControl:: HandlePointerEventL( aPointerEvent );

    if ( AknLayoutUtils::PenEnabled() )
        {
        // Do nothing if dimmed.
        if ( IsDimmed() ||
             Window().IsFaded() )
            {
            return;
            }

        TRect rect( Rect() );

        // Currently the small digital clock pane and universal
        // indicator pane are regarded as one touch responsive area from
        // which the universal indicator popup should open on tap,
        // so upon pointer up event it must be checked here if
        // the down event happened inside this control, but the up event
        // inside indicator pane area.
        TRect indicatorRect( 0, 0, 0, 0 );

        if ( iFlags & EAknDigitalClockInStatusPane &&
             aPointerEvent.iType == TPointerEvent::EButton1Up )
            {
            CEikStatusPaneBase* sp = CEikStatusPaneBase::Current();

            if ( sp )
                {
                CCoeControl* indicatorPane = sp->ContainerControlL(
                    TUid::Uid( EEikStatusPaneUidIndic ) );
                if ( indicatorPane )
                    {
                    indicatorRect =
                        TRect( indicatorPane->PositionRelativeToScreen(),
                               indicatorPane->Size() );
                    }
                }
            }

        if ( aPointerEvent.iType == TPointerEvent::EButton1Down &&
             rect.Contains( aPointerEvent.iPosition ) )
            {
            // Set flag that down event was inside the clock.
            iFlags |= EAknDigitalClockButton1DownReceived;

            // tactile feedback is done with SetFeedbackArea
            }
        else if ( aPointerEvent.iType == TPointerEvent::EButton1Up &&
                  ( ( iFlags & EAknDigitalClockButton1DownReceived &&
                      rect.Contains( aPointerEvent.iPosition ) ) ||
                    ( indicatorRect.Contains( aPointerEvent.iParentPosition ) ) ) )
            {
            // Launch the universal indicator popup.
            CAknSmallIndicator* indicatorNotifier =
                CAknSmallIndicator::NewLC( TUid::Uid( 0 ) );
            indicatorNotifier->HandleIndicatorTapL();
            CleanupStack::PopAndDestroy( indicatorNotifier );

            // Up event received, reset button down flag.
            iFlags &= ( ~EAknDigitalClockButton1DownReceived );
            }
        }
    }


// -----------------------------------------------------------------------------
// CAknDigitalClock::SetColor
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CAknDigitalClock::SetColor( TRgb aColor )
    {
    iColor = aColor;
    }


// -----------------------------------------------------------------------------
// CAknDigitalClock::SetTimeLayout
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CAknDigitalClock::SetTimeLayout( TAknTextLineLayout aTimeLayout )
    {
    iTimeLayout = aTimeLayout;
    iTimeLayoutInUse = ETrue;
    }


// -----------------------------------------------------------------------------
// CAknDigitalClock::ClearTimeLayout
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CAknDigitalClock::ClearTimeLayout()
    {
    iTimeLayoutInUse = EFalse;
    }


// -----------------------------------------------------------------------------
// CAknDigitalClock::StartTimer
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CAknDigitalClock::StartTimer()
    {
    if ( !iTimer )
        {
        iTimer = CPeriodic::New( CActive::EPriorityHigh );
        }

    if ( iTimer && !iTimer->IsActive() )
        {
        TTime time;
        time.HomeTime();
        TDateTime dateTime( time.DateTime() );
        TCallBack callBack( TimerCallback, this );

        iTimer->Start( TTimeIntervalMicroSeconds32(
         KIntervalTime - 1000000 * dateTime.Second() - dateTime.MicroSecond() ),
         TTimeIntervalMicroSeconds32( KIntervalTime ), callBack );

        DrawDeferred();
        }
    }


// -----------------------------------------------------------------------------
// CAknDigitalClock::StopTimer
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CAknDigitalClock::StopTimer()
    {
    if ( iTimer && iTimer->IsActive() )
        {
        iTimer->Cancel();
        }

    // Ensure that the CPeriodic timer stops by destroying it, see Symbian SDK.
    delete iTimer;
    iTimer = NULL;
    }

//  End of File
