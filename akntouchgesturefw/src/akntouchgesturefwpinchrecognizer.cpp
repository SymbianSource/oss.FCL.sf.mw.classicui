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
* Description:  Pinch touch gesture recognizer.
*
*/

#include "akntouchgesturefwdefs.h"
#include "akntouchgesturefwevent.h"
#include "akntouchgesturefwpinchrecognizer.h"
#include "akntouchgesturefwsettings.h"

using namespace AknTouchGestureFw;

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwPinchRecognizer* CAknTouchGestureFwPinchRecognizer::NewL(
    CAknTouchGestureFwRecognitionEngine& aEngine )
    {
    CAknTouchGestureFwPinchRecognizer* self =
        CAknTouchGestureFwPinchRecognizer::NewLC( aEngine );
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwPinchRecognizer* CAknTouchGestureFwPinchRecognizer::NewLC(
        CAknTouchGestureFwRecognitionEngine& aEngine )
    {
    CAknTouchGestureFwPinchRecognizer* self
        = new ( ELeave ) CAknTouchGestureFwPinchRecognizer( aEngine );
    CleanupStack::PushL( self );
    return self;
    }


// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwPinchRecognizer::~CAknTouchGestureFwPinchRecognizer()
    {
    }


// ---------------------------------------------------------------------------
// Returns the pinch gesture group.
// ---------------------------------------------------------------------------
//
TAknTouchGestureFwGroup CAknTouchGestureFwPinchRecognizer::GestureGroup() const
    {
    return EAknTouchGestureFwGroupPinch;
    }


// ---------------------------------------------------------------------------
// Cancels the gesture recognition.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwPinchRecognizer::CancelRecognizing()
    {
    if ( iContinuousFeedback )
        {
        StopContinuousFeedback();
        iContinuousFeedback = EFalse;
        }
    
    if ( iPinchDetected )
        {
        // We ignore the possible leave in order to ensure that the
        // state gets reset.
        TRAP_IGNORE( SendPinchEventL( EAknTouchGestureFwStop, 0 ) );
        }
    Reset();
    }


// ---------------------------------------------------------------------------
// Handles single-touch pointer events.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwPinchRecognizer::HandleSinglePointerEventL(
        const TPointerEventData& /*aPointerData*/ )
    {
    // No single touch event handling in pinch recognizer
    }


// ---------------------------------------------------------------------------
// Handles multi-touch pointer events.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwPinchRecognizer::HandleMultiPointerEventL(
        const TPointerEventData& aPointerData,
        const TPoint& aFirstPointerPosition,
        const TPoint& aSecondPointerPosition )
    {
    // Handle event
    switch ( aPointerData.iPointerEvent.iType )
        {
        case TPointerEvent::EButton1Down:
            {
            StartMultiRecognizing( 
                aFirstPointerPosition,
                aSecondPointerPosition );
            break;
            }
            
        case TPointerEvent::EDrag:
            {
            MultiRecognizeL( 
                aPointerData.iTimeStamp,
                aFirstPointerPosition,
                aSecondPointerPosition );
            break;
            }
        case TPointerEvent::EButton1Up:
            {
            CompleteMultiRecognizingL( aPointerData.iTimeStamp );
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
CAknTouchGestureFwPinchRecognizer::CAknTouchGestureFwPinchRecognizer(
    CAknTouchGestureFwRecognitionEngine& aEngine )
    : CAknTouchGestureFwBaseRecognizer( aEngine )
    {
    Reset();
    }


// ---------------------------------------------------------------------------
// Starts recognizing the pinch gesture.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwPinchRecognizer::StartMultiRecognizing(
        const TPoint& aFirstPointerPos,
        const TPoint& aSecondPointerPos )
    {
    // Initialize members for multi recognition.
    Reset();
    
    iPinchRect = CalculateBoundingRect( aFirstPointerPos, aSecondPointerPos );

    TTouchFeedbackType feedbackType( FeedbackType( EAknTouchGestureFwPinch ) );
    if ( feedbackType )
        {
        ImmediateFeedback( ETouchFeedbackSensitive, feedbackType );
        ImmediateFeedback( ETouchFeedbackSensitive, feedbackType );
        }
    }


// ---------------------------------------------------------------------------
// Continues recognizing the pinch gesture.
// Called for every drag-event when more than one pointer is down.
// Threshold handling for pinch is implemented here.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwPinchRecognizer::MultiRecognizeL(
        const TTime& aEventTime,
        const TPoint& aFirstPointerPos,
        const TPoint& aSecondPointerPos )
    {    
    const TInt pinchThreshold = iPinchDetected ? 
        PinchMovementThreshold() : PinchInitialThreshold();

    // We use boundingRect instead of individual positions, because
    // those positions are not stable with all HW. Instead, bounding rect is.
    TRect boundingRect = 
        CalculateBoundingRect( aFirstPointerPos, aSecondPointerPos );

    // Snap to iPinchRect values.
    TRect normalizedRect = boundingRect;
    NormalizeValue( normalizedRect.iTl.iX, iPinchRect.iTl.iX, pinchThreshold );
    NormalizeValue( normalizedRect.iTl.iY, iPinchRect.iTl.iY, pinchThreshold );
    NormalizeValue( normalizedRect.iBr.iX, iPinchRect.iBr.iX, pinchThreshold );
    NormalizeValue( normalizedRect.iBr.iY, iPinchRect.iBr.iY, pinchThreshold );

    // Determine if width or height should be ignored. 
    // If length of a dimension is close to zero, it's assumed that 
    // those values may be unreliable.
    const TInt dimensionThreshold = PinchDimensionThreshold();
    TBool ignoreWidth =
        ( boundingRect.Width() < dimensionThreshold ) ||
        ( normalizedRect.Width() < dimensionThreshold ) ||
        ( iPinchRect.Width() < dimensionThreshold );
    TBool ignoreHeight =
        ( boundingRect.Height() < dimensionThreshold ) ||
        ( normalizedRect.Height() < dimensionThreshold ) ||
        ( iPinchRect.Height() < dimensionThreshold );

    // Calculate change in width & height.
    TInt widthDelta = ( normalizedRect.Width() - iPinchRect.Width() );
    TInt heightDelta = ( normalizedRect.Height() - iPinchRect.Height() );
       
    TBool handleEvent = EFalse;
    if ( normalizedRect != iPinchRect )
        {
        handleEvent = ETrue;
        iPinchRect = normalizedRect;
        }

    if ( ignoreWidth )
        {
        widthDelta = 0;
        iStoredWidthDelta = 0;
        }
    
    if ( ignoreHeight )
        {
        heightDelta = 0;
        iStoredHeightDelta = 0;
        }

    // Pinch values are sent in a slight delay in order to prevent
    // sending of incorrect values when pointer coordinates are
    // snapped to horizontal/vertical line as snapping tends to
    // happen with two events (one for each pointer).
    //
    // Events are sent here.

    TInt oldStoredWidthDelta = iStoredWidthDelta;
    TInt oldStoredHeightDelta = iStoredHeightDelta;

    if ( oldStoredWidthDelta || oldStoredHeightDelta )
        {
        iStoredWidthDelta = 0;
        iStoredHeightDelta = 0;
    
        TInt movement = 0;
        
        if ( CheckDurationThreshold( aEventTime ) )
            {
            movement = 
                CalculateMovement( 
                    oldStoredWidthDelta,
                    oldStoredHeightDelta );
            }
            
    
        if ( movement )
            {
            if ( iPinchDetected )
                {
                SendPinchEventL( EAknTouchGestureFwOn, movement );
                }
            else
                {
                iPinchDetected = ETrue;
                SendPinchEventL( EAknTouchGestureFwStart, movement );
                }
            }
        }

    if ( !handleEvent )
        {
        // No change, no need to continue
        return;
        }
    
    // Now it is guaranteed that widthDelta or heightDelta does not equal
    // to zero.

    // Update width direction tracer
    if ( !ignoreWidth )
        {
        iPinchWidthTracer.Update( 
            widthDelta, 
            PinchDirectionChangeSensitivity() );
        }
    else
        {
        // Cannot say anything about this direction - snapped together
        iPinchWidthTracer.Reset();
        }
    
    // Update height direction tracer
    if ( !ignoreHeight )
        {
        iPinchHeightTracer.Update( 
            heightDelta, 
            PinchDirectionChangeSensitivity() );
        }
    else
        {
        // Cannot say anything about this direction - snapped together
        iPinchHeightTracer.Reset();
        }

    // Reset direction tracer if height changes but width stays the same.
    if ( widthDelta )
        {
        iResetPinchWidthTracer = 0;
        }

    if ( !widthDelta && heightDelta )
        {
        if ( iResetPinchWidthTracer >= PinchDirectionResetSensitivity() )
            {
            iPinchWidthTracer.Reset();
            iResetPinchWidthTracer = 0;
            }
        else
            {
            iResetPinchWidthTracer++;
            }
        }

    // Reset direction tracer if width changes but height stays the same.
    if ( heightDelta )
        {
        iResetPinchHeightTracer = 0;
        }
            
    if ( !heightDelta && widthDelta )
        {
        if ( iResetPinchHeightTracer >= PinchDirectionResetSensitivity() )
            {
            iPinchHeightTracer.Reset();
            iResetPinchHeightTracer = 0;
            }
        else
            {
            iResetPinchHeightTracer++;
            }
        }

    TInt pinchWidthDelta = 0;
    TInt pinchHeightDelta = 0;

    if ( widthDelta >= 0 && heightDelta >= 0 )
        {
        TDirectionTracer::TDirection widthDir = 
            iPinchWidthTracer.Direction();
        TDirectionTracer::TDirection heightDir = 
            iPinchHeightTracer.Direction();
                
        if ( ( widthDir == TDirectionTracer::EDirectionPositive && 
               heightDir != TDirectionTracer::EDirectionNegative ) || 
             ( heightDir == TDirectionTracer::EDirectionPositive && 
               widthDir != TDirectionTracer::EDirectionNegative ) )
            {
            pinchWidthDelta = widthDelta; 
            pinchHeightDelta = heightDelta; 
            }
        }
    else if ( widthDelta <= 0 && heightDelta <= 0 )
        {
        TDirectionTracer::TDirection widthDir = 
            iPinchWidthTracer.Direction();
        TDirectionTracer::TDirection heightDir = 
            iPinchHeightTracer.Direction();
                
        if ( ( widthDir == TDirectionTracer::EDirectionNegative && 
               heightDir != TDirectionTracer::EDirectionPositive ) || 
             ( heightDir == TDirectionTracer::EDirectionNegative && 
               widthDir != TDirectionTracer::EDirectionPositive ) )
            {
            pinchWidthDelta = widthDelta;
            pinchHeightDelta = heightDelta;
            }                
        }
    else
        {
        // Ignore mixed changes.
        }

    // Pinch values are sent in a slight delay in order to prevent
    // sending of incorrect values when pointer coordinates are
    // snapped to horizontal/vertical line.
    //
    // Now just store delta values here.
    
    iStoredTime = aEventTime;
    iStoredWidthDelta = pinchWidthDelta;
    iStoredHeightDelta = pinchHeightDelta;
    }


// ---------------------------------------------------------------------------
// Ends the recognition of the pinch gesture.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwPinchRecognizer::CompleteMultiRecognizingL(
        const TTime& aEventTime )
    {
    if ( iContinuousFeedback )
        {
        StopContinuousFeedback();
        iContinuousFeedback = EFalse;
        }
    // Send Pinch stopped event only if pinch was detected
    if ( iPinchDetected )
        {
        TInt movement = 0;
        
        if ( CheckDurationThreshold( aEventTime ) )
            {
            movement = 
                CalculateMovement( 
                    iStoredWidthDelta, 
                    iStoredHeightDelta );
            }

        iStoredWidthDelta = 0;
        iStoredHeightDelta = 0;

        SendPinchEventL( EAknTouchGestureFwStop, movement );
        }
    }


// ---------------------------------------------------------------------------
// Resets the recognizer state.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwPinchRecognizer::Reset()
    {
    iPinchDetected = EFalse;
    iPinchRect.SetRect( 0, 0, 0, 0 );
    iPinchWidthTracer.Reset();
    iPinchHeightTracer.Reset();
    iResetPinchWidthTracer = 0;
    iResetPinchHeightTracer = 0;
    iStoredWidthDelta = 0;
    iStoredHeightDelta = 0;
    }


// ---------------------------------------------------------------------------
// Sends a pinch gesture event to the observer.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwPinchRecognizer::SendPinchEventL(
    TAknTouchGestureFwState aGestureState,
    TInt aMovementDelta )
    {
    if ( aGestureState != EAknTouchGestureFwStop )
        {
        TTouchFeedbackType feedbackType(
            FeedbackType( EAknTouchGestureFwPinch ) );
    
        if ( feedbackType & ETouchFeedbackVibra )
            {
            StartContinuousFeedback( ETouchContinuousSmooth,
                KAknTouchGestureFwFeedbackIntensity,
                KAknTouchGestureFwPinchFeedbackTimeout );
            iContinuousFeedback = ETrue;
            }
        }
        
    TAknTouchGestureFwPinchEvent pinch;
    pinch.SetState( aGestureState );
    pinch.SetMovement( aMovementDelta );
    SendGestureEventL( pinch );
    }


// ----------------------------------------------------------------------------
// Returns pinch initial threshold.
// ----------------------------------------------------------------------------
//
TInt CAknTouchGestureFwPinchRecognizer::PinchInitialThreshold() const
    {
    return Settings().PinchInitialThreshold();    
    }


// ----------------------------------------------------------------------------
// Returns pinch movement threshold.
// ----------------------------------------------------------------------------
//
TInt CAknTouchGestureFwPinchRecognizer::PinchMovementThreshold() const
    {
    return Settings().PinchMovementThreshold();
    }


// ----------------------------------------------------------------------------
// Returns pinch direction change sensitivity.
// ----------------------------------------------------------------------------
//
TInt CAknTouchGestureFwPinchRecognizer::PinchDirectionChangeSensitivity() const
    {
    return Settings().PinchDirectionChangeSensitivity();
    }


// ----------------------------------------------------------------------------
// Returns pinch direction reset sensitivity.
// ----------------------------------------------------------------------------
//
TInt CAknTouchGestureFwPinchRecognizer::PinchDirectionResetSensitivity() const
    {
    return Settings().PinchDirectionResetSensitivity();
    }


// ----------------------------------------------------------------------------
// Returns pinch dimension threshold.
// ----------------------------------------------------------------------------
//
TInt CAknTouchGestureFwPinchRecognizer::PinchDimensionThreshold() const
    {
    return Settings().PinchDimensionThreshold();
    }

// ----------------------------------------------------------------------------
// Returns pinch maximum confirmation duration.
// ----------------------------------------------------------------------------
//
TInt CAknTouchGestureFwPinchRecognizer::PinchMaximumConfirmationDuration() 
    const
    {
    return Settings().PinchMaximumConfirmationDuration() * 
           KMicroSecondsInMilliSecond;
    }


// ---------------------------------------------------------------------------
// Calculates bounding rect so that both aPoint1 and aPoint2 are inside
// the rectangle.
// ---------------------------------------------------------------------------
//
TRect CAknTouchGestureFwPinchRecognizer::CalculateBoundingRect( 
        const TPoint& aPoint1, 
        const TPoint& aPoint2 )
    {
    TRect result;
    result.iTl.iX = Min( aPoint1.iX, aPoint2.iX );
    result.iTl.iY = Min( aPoint1.iY, aPoint2.iY );
    result.iBr.iX = Max( aPoint1.iX, aPoint2.iX ) + 1;  
    result.iBr.iY = Max( aPoint1.iY, aPoint2.iY ) + 1;
    return result;
    }


// ---------------------------------------------------------------------------
// Snaps aValue to aReference if they are sufficiently close 
// (defined by aMargin).
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwPinchRecognizer::NormalizeValue( 
        TInt& aValue, 
        TInt aReference, 
        TInt aMargin )
    {
    if ( Abs( aReference - aValue ) < aMargin )
        {
        aValue = aReference;
        }
    }

// ---------------------------------------------------------------------------
// Calculates movement value 
// ---------------------------------------------------------------------------
//
TInt CAknTouchGestureFwPinchRecognizer::CalculateMovement( 
        TInt aWidthDelta, 
        TInt aHeightDelta )
    {
    TInt result = 0;
    
    if ( aWidthDelta >= 0 && aHeightDelta >= 0 )
        {
        result = Max( aWidthDelta, aHeightDelta );
        }
    else if ( aWidthDelta <= 0 && aHeightDelta <= 0 )
        {
        result = Min( aWidthDelta, aHeightDelta );
        }
    else
        {
        // Mixed case, return 'no movement'.
        }

    return result;
    }

// ---------------------------------------------------------------------------
// Checks duration threshold. 
// ---------------------------------------------------------------------------
//
TBool CAknTouchGestureFwPinchRecognizer::CheckDurationThreshold( 
        const TTime& aEventTime ) const
    {
    TTimeIntervalMicroSeconds duration = 
        aEventTime.MicroSecondsFrom( iStoredTime );
    TTimeIntervalMicroSeconds durationThreshold( 
        PinchMaximumConfirmationDuration() );
    
    return ( duration < durationThreshold );
    }

// End of File
