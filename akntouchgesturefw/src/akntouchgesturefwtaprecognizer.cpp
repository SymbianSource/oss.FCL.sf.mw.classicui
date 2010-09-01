/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Tap touch gesture recognizer.
*
*/

#include "akntouchgesturefwdefs.h"
#include "akntouchgesturefwevent.h"
#include "akntouchgesturefwsettings.h"
#include "akntouchgesturefwtaprecognizer.h"

using namespace AknTouchGestureFw;

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwTapRecognizer* CAknTouchGestureFwTapRecognizer::NewL(
        CAknTouchGestureFwRecognitionEngine& aEngine )
    {
    CAknTouchGestureFwTapRecognizer* self =
        CAknTouchGestureFwTapRecognizer::NewLC( aEngine );
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwTapRecognizer* CAknTouchGestureFwTapRecognizer::NewLC(
        CAknTouchGestureFwRecognitionEngine& aEngine )
    {
    CAknTouchGestureFwTapRecognizer* self
        = new ( ELeave ) CAknTouchGestureFwTapRecognizer( aEngine );
    CleanupStack::PushL( self );
    return self;
    }


// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwTapRecognizer::~CAknTouchGestureFwTapRecognizer()
    {
    if ( iLongTapTimer )
        {
        iLongTapTimer->Cancel();
        }
    delete iLongTapTimer;
    }


// ---------------------------------------------------------------------------
// Returns the tap gesture group.
// ---------------------------------------------------------------------------
//
TAknTouchGestureFwGroup CAknTouchGestureFwTapRecognizer::GestureGroup() const
    {
    return EAknTouchGestureFwGroupTap;
    }


// ---------------------------------------------------------------------------
// Cancels the tap recognition.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwTapRecognizer::CancelRecognizing()
    {
    DoCancelTapRecognition( ETrue );
    }


// ---------------------------------------------------------------------------
// Handles single-touch pointer events.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwTapRecognizer::HandleSinglePointerEventL(
        const TPointerEventData& aPointerData )
    {
    switch ( aPointerData.iPointerEvent.iType )
        {
        case TPointerEvent::EButton1Down:
            {
            // Start recognition on down event
            StartTapRecognition( 
                    aPointerData.iPointerEvent.iPosition,
                    aPointerData.iTimeStamp );
            break;
            }
        case TPointerEvent::EDrag:
            {
            // Continue tap recognizing.
            TapRecognize( aPointerData.iPointerEvent.iPosition );
            break;
            }
        case TPointerEvent::EButton1Up:
            {
            // Pointer up - complete recognition
            CompleteTapRecognitionL( aPointerData.iTimeStamp );
            break;
            }
        default:
            {
            break;
            }
        }
    }


// ---------------------------------------------------------------------------
// Handles multi-touch pointer events.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwTapRecognizer::HandleMultiPointerEventL(
    const TPointerEventData& aPointerData,
    const TPoint& /*aFirstPointerPosition*/,
    const TPoint& /*aSecondPointerPosition*/ )
    {
    if ( aPointerData.iPointerEvent.iType == TPointerEvent::EButton1Down )
        {
        // First pointer is already down, second pointer down cancels tap
        // recognizing because taps are allowed only for the first pointer.
        CancelRecognizing();
        }
    }


// ---------------------------------------------------------------------------
// C++ constructor.
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwTapRecognizer::CAknTouchGestureFwTapRecognizer(
        CAknTouchGestureFwRecognitionEngine& aEngine )
    : CAknTouchGestureFwBaseRecognizer( aEngine ),
    iThresholdArea(),
    iLongTapTimer( NULL ),
    iFirstTapDetected( EFalse ),
    iFirstTapTime(),
    iFirstTapPos(),
    iLongTapIntensity( 0 ),
    iFeedBackStarted( EFalse ) 
    {
    }


// ---------------------------------------------------------------------------
// Starts the tap gesture recognition.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwTapRecognizer::StartTapRecognition(
    const TPoint& aStartPoint, 
    const TTime& aTimeStamp )
    {
    iThresholdArea.Start( aStartPoint );

    // Start timer to recognize long tap
    if ( !iLongTapTimer )
        {
        iLongTapTimer = CPeriodic::New( CActive::EPriorityStandard );
        }

    if ( iLongTapTimer )
        {
        iLongTapTimer->Cancel();
        // Set timer for initial long tap delay.
        iLongTapTimer->Start( KDefaultLongTapInitialDelay, 
                              KDefaultLongTapInitialDelay,
                              TCallBack( LongTapCallback, this ) );
        }

    if ( iFirstTapDetected )
        {
        // First tap already detected, check if this tap is double tap

        // Check if position of this tap is too far from
        // position of first tap.
        TInt xDistance = Abs( aStartPoint.iX - iFirstTapPos.iX );
        TInt yDistance = Abs( aStartPoint.iY - iFirstTapPos.iY );

        if ( xDistance > DragThreshold() || yDistance > DragThreshold() )
            {
            // Too far, this tap can't be double tap.
            iFirstTapDetected = EFalse;
            return;
            }

        // Check if delay between already detected tap and this tap is too long.
        TInt delay( aTimeStamp.MicroSecondsFrom( iFirstTapTime ).Int64() );

        if ( delay > DoubleTapMaximumDuration() )
            {
            // Delay is too long, this tap can't be double tap.
            iFirstTapDetected = EFalse;
            }
        }
    }


// ---------------------------------------------------------------------------
// Continues the tap gesture recognition, called on drag pointer events.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwTapRecognizer::TapRecognize( const TPoint& aPoint )
    {
    if ( iThresholdArea.Check( aPoint, TapThreshold() ) )
        {
        CancelRecognizing();
        }
    }


// ---------------------------------------------------------------------------
// Ends the tap gesture recognition.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwTapRecognizer::CompleteTapRecognitionL( 
    const TTime& aTimeStamp )
    {
    if ( iThresholdArea.IsActive() )
        {
        // Single pointer has been down and goes up now
        // and tap recognition hasn't been cancelled
        const TPoint startPos( iThresholdArea.InitialPosition() );

        // Cancel tap recognition of this tap, but don't
        // remove the possible info that first tap has already been detected
        DoCancelTapRecognition( EFalse );

        if ( iFirstTapDetected )
            {
            iFirstTapDetected = EFalse;
            // First tap already detected: Send Double Tap gesture event
            SendTapEventL( EAknTouchGestureFwDoubleTap, iFirstTapPos );
            }
        else
            {
            iFirstTapTime = aTimeStamp;
            iFirstTapDetected = ETrue;
            iFirstTapPos = startPos;

            // First tap not detected: Send normal Tap gesture event
            SendTapEventL( EAknTouchGestureFwTap, startPos );
            }
        }
    }


// ---------------------------------------------------------------------------
// Sends a tap gesture event to the observer.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwTapRecognizer::SendTapEventL(
    TAknTouchGestureFwType aGestureType,
    const TPoint& aPointerPos )
    {
    TTouchFeedbackType feedbackType( FeedbackType( aGestureType ) );
    if ( feedbackType )
        {
        switch ( aGestureType )
            {
            case EAknTouchGestureFwTap:
                {
                ImmediateFeedback( ETouchFeedbackSensitive, feedbackType );
                break;
                }
            case EAknTouchGestureFwDoubleTap:
                {
                ImmediateFeedback( ETouchFeedbackBasic, feedbackType );
                break;
                }
            case EAknTouchGestureFwLongTap:
                {
                ImmediateFeedback( ETouchFeedbackBasic, feedbackType );                                                       
                break;
                }
            default:
                {
                break;
                }
            }    
        }

    TAknTouchGestureFwTapEvent tap;
    tap.SetType( aGestureType );
    tap.SetPosition( aPointerPos );
    SendGestureEventL( tap );
    }


// ---------------------------------------------------------------------------
// Called when long tap has been detected.
// ---------------------------------------------------------------------------
//
TInt CAknTouchGestureFwTapRecognizer::LongTapCallback( TAny* aThis )
    {
    CAknTouchGestureFwTapRecognizer* recognizer =
        static_cast<CAknTouchGestureFwTapRecognizer*>( aThis );
    if ( recognizer )
        {
        TRAP_IGNORE( recognizer->HandleLongTapCallbackL() );
        }
    return 0;
    }


// ---------------------------------------------------------------------------
// Handles long tap callback related actions.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwTapRecognizer::HandleLongTapCallbackL()
    {   
    if ( iLongTapIntensity == 0 && iLongTapTimer )
        {   
        iLongTapTimer->Cancel();

        TInt interval = ( LongTapThreshold() - KDefaultLongTapInitialDelay )
            / KDefaultMaxLongTapIntensitySteps;
        
        TInt timeOut = 
            interval * ( KDefaultMaxLongTapIntensitySteps + 1 );
        
        // Start timer again to increase long tap intensity on
        // regular interval until max intensity is reached.
        iLongTapTimer->Start( 0, interval,
            TCallBack( LongTapCallback, this ) );
        
        TTouchFeedbackType feedbackType(
            FeedbackType( EAknTouchGestureFwTap ) );       
           
        if ( feedbackType & ETouchFeedbackVibra )
            {      
            // Start feedback for long tap gesture.
            StartContinuousFeedback( ETouchContinuousSmooth, 0, timeOut ); 
            iFeedBackStarted = ETrue;
            }
        }
 
    // Calculate new long tap intensity value.
    iLongTapIntensity = iLongTapIntensity + 
        KDefaultMaxLongTapIntensity / KDefaultMaxLongTapIntensitySteps;
    
    if ( iFeedBackStarted )
        {
        // Modify existing continuous feedback. Intensity will grow 
        // from 0 to 100 and after that long tap is detected. 
        ModifyContinuousFeedback( iLongTapIntensity );
        }
    
    if ( iLongTapIntensity >= KDefaultMaxLongTapIntensity )
        {
        const TPoint startPos( iThresholdArea.InitialPosition() );
        CancelRecognizing();
        // Send Long Tap gesture event.
        SendTapEventL( EAknTouchGestureFwLongTap, startPos );
        }            
    }


// ---------------------------------------------------------------------------
// Cancels the tap gesture recognition.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwTapRecognizer::DoCancelTapRecognition(
        TBool aResetFirstTapDetection )
    {
    iThresholdArea.Reset();

    if ( aResetFirstTapDetection )
        {
        iFirstTapDetected = EFalse;
        }

    if ( iLongTapTimer )
        {
        iLongTapTimer->Cancel();
        
        if ( iLongTapIntensity > 0 )
            {
            StopContinuousFeedback();
            iFeedBackStarted = EFalse;
            iLongTapIntensity = 0;
            }
        }
    }


// ---------------------------------------------------------------------------
// Returns the value for the long tap threshold setting.
// ---------------------------------------------------------------------------
//
TInt CAknTouchGestureFwTapRecognizer::LongTapThreshold() const
    {
    return Settings().LongTapThreshold() * KMicroSecondsInMilliSecond;
    }


// ---------------------------------------------------------------------------
// Returns the value for the single tap threshold setting.
// ---------------------------------------------------------------------------
//
TInt CAknTouchGestureFwTapRecognizer::TapThreshold() const
    {
    return Settings().TapThreshold();
    }


// ---------------------------------------------------------------------------
// Returns the value for the double tap maximum duration setting.
// ---------------------------------------------------------------------------
//
TInt CAknTouchGestureFwTapRecognizer::DoubleTapMaximumDuration() const
    {
    return Settings().DoubleTapMaximumDuration() * KMicroSecondsInMilliSecond;
    }

// End of File
