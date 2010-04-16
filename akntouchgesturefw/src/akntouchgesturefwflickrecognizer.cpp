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
* Description:  Flick touch gesture recognizer.
*
*/

#include "akntouchgesturefwdefs.h"
#include "akntouchgesturefwdragtracer.h"
#include "akntouchgesturefwevent.h"
#include "akntouchgesturefwflickrecognizer.h"
#include "akntouchgesturefwsettings.h"

using namespace AknTouchGestureFw;


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwFlickRecognizer* CAknTouchGestureFwFlickRecognizer::NewL(
    CAknTouchGestureFwRecognitionEngine& aEngine )
    {
    CAknTouchGestureFwFlickRecognizer* self =
        CAknTouchGestureFwFlickRecognizer::NewLC( aEngine );
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwFlickRecognizer* CAknTouchGestureFwFlickRecognizer::NewLC(
    CAknTouchGestureFwRecognitionEngine& aEngine )
    {
    CAknTouchGestureFwFlickRecognizer* self
        = new ( ELeave ) CAknTouchGestureFwFlickRecognizer( aEngine );
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }


// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwFlickRecognizer::~CAknTouchGestureFwFlickRecognizer()
    {
    delete iDragTracer;
    iPoints.Close();
    }


// ---------------------------------------------------------------------------
// Returns the flick gesture group.
// ---------------------------------------------------------------------------
//
TAknTouchGestureFwGroup CAknTouchGestureFwFlickRecognizer::GestureGroup() const
    {
    return EAknTouchGestureFwGroupFlick;
    }


// ---------------------------------------------------------------------------
// Cancels gesture recognition.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwFlickRecognizer::CancelRecognizing()
    {
    Reset();
    }


// ---------------------------------------------------------------------------
// Handles single-touch pointer events.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwFlickRecognizer::HandleSinglePointerEventL(
    const TPointerEventData& aPointerData )
    {
    switch ( aPointerData.iPointerEvent.iType )
        {
        case TPointerEvent::EButton1Down:
            {
            StartSingleRecognizing( 
                    aPointerData.iPointerEvent.iPosition,
                    aPointerData.iTimeStamp );
            break;
            }
        case TPointerEvent::EDrag:
            {
            if ( iStartOnSingleTouchDrag )
                {
                // Start (via Reset) clears iStartOnSingleTouchDrag.
                StartSingleRecognizing( 
                    aPointerData.iPointerEvent.iPosition,
                    aPointerData.iTimeStamp );                
                }
            else
                {
                SingleRecognizeL( 
                    aPointerData.iPointerEvent.iPosition,
                    aPointerData.iTimeStamp );
                }
            break;
            }
        case TPointerEvent::EButton1Up:
            {
            CompleteSingleRecognizingL( 
                    aPointerData.iPointerEvent.iPosition,
                    aPointerData.iTimeStamp,
                    EFalse );
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
void CAknTouchGestureFwFlickRecognizer::HandleMultiPointerEventL(
    const TPointerEventData& aPointerData,
    const TPoint& aFirstPointerPosition,
    const TPoint& /*aSecondPointerPosition*/ )
    {
    switch ( aPointerData.iPointerEvent.iType )
        {
        case TPointerEvent::EButton1Down:
            {
            // Completes single recognizing but does not check if
            // flick is detected
            CompleteSingleRecognizingL( 
                    aFirstPointerPosition,
                    aPointerData.iTimeStamp,
                    ETrue );
            break;
            }
        case TPointerEvent::EDrag:
            {
            break;
            }
        case TPointerEvent::EButton1Up:
            {
            // Upon next single touch drag, start recognition.
            // Current position is not necessarily accurate.
            iStartOnSingleTouchDrag = ETrue;
            break;
            }
        default:
            {
            break;
            }
        }
    }


// ---------------------------------------------------------------------------
// C++ constructor.
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwFlickRecognizer::CAknTouchGestureFwFlickRecognizer(
        CAknTouchGestureFwRecognitionEngine& aEngine )
    : CAknTouchGestureFwBaseRecognizer( aEngine )
    {
    }


// ---------------------------------------------------------------------------
// Second-phase constructor.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwFlickRecognizer::ConstructL()
    {
    iDragTracer = CAknTouchGestureFwDragTracer::NewL();
    }


// ---------------------------------------------------------------------------
// Starts recognizing the flick gesture.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwFlickRecognizer::StartSingleRecognizing(
    const TPoint& aPointerPos,
    const TTime& aTimeStamp )
    {
    Reset();
    iDragTracer->Initialize( aPointerPos );
    AddPoint( aPointerPos, aTimeStamp );
    iDragArea.Start( aPointerPos );
    }


// ---------------------------------------------------------------------------
// Continues recognizing the flick gesture, called on drag events.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwFlickRecognizer::SingleRecognizeL(
    const TPoint& aPointerPos,
    const TTime& aTimeStamp )
    {
    AddPoint( aPointerPos, aTimeStamp );
    iThresholdExceeded =
        iThresholdExceeded || iDragArea.Check( aPointerPos, DragThreshold() );
    }


// ---------------------------------------------------------------------------
// Ends the flick gesture recognition.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwFlickRecognizer::CompleteSingleRecognizingL(
    const TPoint& aPointerPos,
    const TTime& aTimeStamp,
    TBool aStartMultiTouch )
    {
    // Try to detect flick if multi touch was not started
    if ( !aStartMultiTouch )
        {
        AddPoint( aPointerPos, aTimeStamp );
        }

    // Try to detect flick only if drag already detected and
    // caller wants to detect flick.
    if ( iThresholdExceeded && !aStartMultiTouch )
        {
        TAknTouchGestureFwType flickGestureType( EAknTouchGestureFwUnknown );
        TPoint flickSpeed( 0, 0 );
        TBool flickDetected = DetermineFlickTypeAndSpeed( flickGestureType,
                flickSpeed );

        // Send flick event if speed threshold is exceeded
        if( flickDetected )
            {
            TPoint flickPosition( iPoints[ iPoints.Count() - 1 ].iPos );
            iPoints.Reset();
            SendFlickEventL( flickGestureType, flickPosition, flickSpeed );
            iFlickSpeed = TPoint( 0, 0 );
            }
        }

    Reset();
    }


// ---------------------------------------------------------------------------
// Sends a flick gesture event to the observer.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwFlickRecognizer::SendFlickEventL(
    TAknTouchGestureFwType aGestureType,
    const TPoint& aPosition,
    const TPoint& aSpeed )
    {
    TTouchFeedbackType feedbackType( FeedbackType( aGestureType ) );
    if ( feedbackType )
        {
        switch ( aGestureType )
            {
            case EAknTouchGestureFwFlickLeft:
            case EAknTouchGestureFwFlickRight:
            case EAknTouchGestureFwFlickUp:
            case EAknTouchGestureFwFlickDown:
                {
                ImmediateFeedback( ETouchFeedbackItemScroll, feedbackType );
                break;
                }
            default:
                {
                break;
                }
            }
        }
    
    TAknTouchGestureFwFlickEvent flick;
    flick.SetType( aGestureType );
    flick.SetPosition( aPosition );
    flick.SetSpeed( aSpeed );
    SendGestureEventL( flick );
    }


// ---------------------------------------------------------------------------
// Resets recognizer's state.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwFlickRecognizer::Reset()
    {
    iStartOnSingleTouchDrag = EFalse;
    iPoints.Reset();
    iDragArea.Reset();
    iThresholdExceeded = EFalse;
    }


// ---------------------------------------------------------------------------
// Adds a point to the sequences of points that forms the gesture.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwFlickRecognizer::AddPoint( const TPoint& aPoint,
    const TTime& aTimeStamp )
    {
    // Don't add duplicate points, but update time of latest point
    if ( iPoints.Count() > 0 &&
         iPoints[ iPoints.Count() - 1 ].iPos == aPoint )
        {
        iPoints[ iPoints.Count() - 1 ].iTime = aTimeStamp;
        return;
        }

    TInt err = iPoints.Append( TPointEntry( aPoint, aTimeStamp ) );
    if ( err == KErrNone )
        {
        // if buffer is full, remove oldest points
        if ( iPoints.Count() > MaximumBufferLength() )
            {
            iPoints.Remove( 0 );
            }
        // Handle changes in direction.
        // In practice, removes unnecessary points if direction changes
        HandleDirectionChanges( aPoint );
        }
    }


// ---------------------------------------------------------------------------
// Checks if the point array is empty.
// ---------------------------------------------------------------------------
//
TBool CAknTouchGestureFwFlickRecognizer::IsEmpty() const
    {
    return iPoints.Count() == 0;
    }


// ---------------------------------------------------------------------------
// Determines the direction and speed of a flick gesture.
// ---------------------------------------------------------------------------
//
TBool CAknTouchGestureFwFlickRecognizer::DetermineFlickTypeAndSpeed(
    TAknTouchGestureFwType& aFlickGestureType,
    TPoint& aSpeed )
    {
    // Calculate distance and speed based on first and last
    // point in the pointer array.

    TPoint distance;
    TPoint speed;
    if ( !CalculateFlickParameters( distance, speed ) )
        {
        return EFalse;
        }

    // If speed is over threshold, this movement is assumed to be flick
    TInt speedThreshold( FlickSpeedThreshold() );
    if ( Abs( speed.iX ) >= speedThreshold ||
         Abs ( speed.iY ) >= speedThreshold )
        {
        aFlickGestureType = EAknTouchGestureFwUnknown;

        // Flick detected - determine its direction.
        if ( Abs( distance.iX ) > Abs( distance. iY ) )
            {
            // Right or left
            if ( distance.iX > 0 )
                {
                aFlickGestureType = EAknTouchGestureFwFlickRight;
                }
            else
                {
                aFlickGestureType = EAknTouchGestureFwFlickLeft;
                }
            }
        else
            {
            // Up or down
            if ( distance.iY > 0 )
                {
                aFlickGestureType = EAknTouchGestureFwFlickDown;
                }
            else
                {
                aFlickGestureType = EAknTouchGestureFwFlickUp;
                }
            }

        // Set flick speed.
        aSpeed = speed;

        return ETrue;
        }

    return EFalse;
    }


// ---------------------------------------------------------------------------
// Calculates the flick distance and speed.
// ---------------------------------------------------------------------------
//
TBool CAknTouchGestureFwFlickRecognizer::CalculateFlickParameters(
    TPoint& aDistance,
    TPoint& aSpeed )
    {
    // Check that there are at least 2 points to calculate parameters.
    TInt count = iPoints.Count();
    if ( count < 2 )
        {
        return EFalse;
        }

    // Flick detection is done using latest points added during last
    // n seconds.
    // Ignore all points that are older than n seconds
    TTime endTime = iPoints[ count - 1 ].iTime;
    TInt startIndex = -1;

    for ( TInt i = 0; i < count - 1; i++ )
        {
        TInt elapsedTime = Elapsed( iPoints[ i ].iTime, endTime ).Int();

        if ( elapsedTime < FlickDetectionTime() )
            {
            startIndex = i;
            break;
            }
        }

    // If there is no new start point (within n seconds) found,
    // it means that time between two latest points have been over this time
    // and movement can't be flick
    if ( startIndex == -1 )
        {
        return EFalse;
        }

    // Calculate distance and speed based on new start- and endpoints
    aDistance = iPoints[ count - 1 ].iPos - iPoints[ startIndex ].iPos;

    TInt elapsedTime = Elapsed( iPoints[ startIndex ].iTime,
                                iPoints[ count - 1 ].iTime ).Int();

    if ( elapsedTime <= 0 )
        {
        return EFalse;
        }

    aSpeed.iX = KMicroSecondsInSecond * aDistance.iX / elapsedTime;
    aSpeed.iY = KMicroSecondsInSecond * aDistance.iY / elapsedTime;

    return ETrue;
    }


// ---------------------------------------------------------------------------
// Called when drag direction changes to clear the previous points.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwFlickRecognizer::HandleDirectionChanges(
    const TPoint& aPosition )
    {
    // Sensitivity tells how many points are needed to reversed direction
    // to detect change in direction.
    TInt sensitivity( DirectionChangeSensitivity() );

    if ( iDragTracer->IsDirectionChanged( aPosition, sensitivity ) )
        {
        // Remove all previous points so that latest points which
        // are to reversed direction + point where direction changes are left.
        RemovePreviousPoints( sensitivity + 1 );
        }
    }


// ---------------------------------------------------------------------------
// Calculates the elapsed time from the specified start time and end time.
// static
// ---------------------------------------------------------------------------
//
TTimeIntervalMicroSeconds32 CAknTouchGestureFwFlickRecognizer::Elapsed(
    const TTime& aStartTime,
    const TTime& aEndTime )
    {
    return aEndTime.MicroSecondsFrom( aStartTime ).Int64();
    }


// ---------------------------------------------------------------------------
// Removes the specified amount of stored points from the array.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwFlickRecognizer::RemovePreviousPoints(
    TInt aNumberOfPoints )
    {
    TInt count = iPoints.Count();
    if ( count - aNumberOfPoints > 0 )
        {
        for ( TInt i = 0; i < count - aNumberOfPoints; i++ )
            {
            iPoints.Remove( 0 );
            }
        }
    }


// ---------------------------------------------------------------------------
// CAknTouchGestureFwFlickRecognizer::MaximumBufferLength
// ---------------------------------------------------------------------------
//
TInt CAknTouchGestureFwFlickRecognizer::MaximumBufferLength() const
    {
    return Settings().FlickBuffer();
    }


// ---------------------------------------------------------------------------
// Returns the current value of flick speed threshold setting.
// ---------------------------------------------------------------------------
//
TInt CAknTouchGestureFwFlickRecognizer::FlickSpeedThreshold() const
    {
    return Settings().FlickSpeedThreshold();
    }


// ---------------------------------------------------------------------------
// Returns the current value of flick detection time setting.
// ---------------------------------------------------------------------------
//
TInt CAknTouchGestureFwFlickRecognizer::FlickDetectionTime() const
    {
    return Settings().FlickDetectionTime() * KMicroSecondsInMilliSecond;
    }


// ---------------------------------------------------------------------------
// Returns the current value of direction change sensitivity setting.
// ---------------------------------------------------------------------------
//
TInt CAknTouchGestureFwFlickRecognizer::DirectionChangeSensitivity() const
    {
    return Settings().FlickChangeSensitivity();
    }

// End of File
