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

#ifndef C_AKNTOUCHGESTUREFWPINCHRECOGNIZER_H
#define C_AKNTOUCHGESTUREFWPINCHRECOGNIZER_H

#include "akntouchgesturefwbaserecognizer.h"

namespace AknTouchGestureFw {


/**
 *  Pinch touch gesture recognizer.
 *
 *  @lib akntouchgesturefw
 *  @since S60 v5.2
 */
NONSHARABLE_CLASS( CAknTouchGestureFwPinchRecognizer )
    : public CAknTouchGestureFwBaseRecognizer
    {

public:

    /**
     * Two-phased constructor.
     *
     * @param  aEngine  The gesture recognition engine.
     */ 
    static CAknTouchGestureFwPinchRecognizer* NewL(
            CAknTouchGestureFwRecognitionEngine& aEngine );

    /**
     * Two-phased constructor.
     *
     * @param  aEngine  The gesture recognition engine.
     */
    static CAknTouchGestureFwPinchRecognizer* NewLC(
            CAknTouchGestureFwRecognitionEngine& aEngine );

    /**
     * Destructor.
     */
    virtual ~CAknTouchGestureFwPinchRecognizer();

public: // From base class CAknTouchGestureFwBaseRecognizer.

    /**
     * Returns the recognizer gesture group.
     * 
     * @return @c EAknTouchGestureFwGroupPinch
     */
    TAknTouchGestureFwGroup GestureGroup() const;

    /**
     * Cancels the gesture recognition.
     */
    void CancelRecognizing();

    /**
     * Handles single pointer event.
     * 
     * @param  aPointerData  Pointer event related data.
     */
    void HandleSinglePointerEventL( const TPointerEventData& aPointerData );

    /**
     * Handles multi pointer event.
     *
     * @param  aPointerData            Pointer event related data.
     * @param  aFirstPointerPosition   First pointer position.
     * @param  aSecondPointerPosition  Second pointer position.
     */
    void HandleMultiPointerEventL( const TPointerEventData& aPointerData,
                                   const TPoint& aFirstPointerPosition,
                                   const TPoint& aSecondPointerPosition );

private:

    /**
     * C++ constructor.
     *
     * @param  aEngine  The gesture recognition engine.
     */
    CAknTouchGestureFwPinchRecognizer(
            CAknTouchGestureFwRecognitionEngine& aEngine );

    /**
     * Resets recognizer's state.
     */
    void Reset();

    /**
     * Starts multi-touch recognition.
     *
     * @param  aFirstPointerPos   Position of first pointer.
     * @param  aSecondPointerPos  Position of second pointer.
     */
    void StartMultiRecognizing(
            const TPoint& aFirstPointerPos,
            const TPoint& aSecondPointerPos );

    /**
     * Handles multi-touch recognition cycle.
     * Called for every drag event when one pointer is down. 
     *
     * @param aEventTime Time of pointer event.
     * @param  aFirstPointerPos   New position of first pointer.
     * @param  aSecondPointerPos  New position of second pointer.
     */
    void MultiRecognizeL(
            const TTime& aEventTime,
            const TPoint& aFirstPointerPos,
            const TPoint& aSecondPointerPos );

    /**
     * Completes multi touch recognition.
     * 
     * @param aEventTime Time of pointer event.
     */
    void CompleteMultiRecognizingL(
            const TTime& aEventTime );

    /**
     * Asks engine to send pinch event to observer.
     * 
     * @param aGestureState  Pinch gesture state.
     * @param aMovementDelta delta movement.
     */
    void SendPinchEventL( 
            TAknTouchGestureFwState aGestureState, 
            TInt aMovementDelta );

    /**
     * Returns pinch initial threshold.
     *
     * @return Pinch initial threshold.
     */
    TInt PinchInitialThreshold() const;
    
    /**
     * Returns pinch movement threshold.
     *
     * @return Pinch movement threshold.
     */
    TInt PinchMovementThreshold() const;
    
    /**
     * Returns pinch direction change sensitivity.
     * 
     * @return pinch direction change sensitivity.
     */
    TInt PinchDirectionChangeSensitivity() const;
    
    /**
     * Returns pinch direction reset sensitivity.
     *
     * @return pinch direction reset sensitivity.
     */
    TInt PinchDirectionResetSensitivity() const;
    
    /**
     * Returns pinch dimension threshold.
     * 
     * @return pinch dimension threshold.
     */
    TInt PinchDimensionThreshold() const;
    
    /**
     * Returns pinch maximum confirmation duration.
     * 
     * @return pinch maximum confirmation duration.
     */
    TInt PinchMaximumConfirmationDuration() const;
    
    /**
     * Calculates bounding rect so that both aPoint1 and aPoint2 are inside
     * the rectangle.
     *
     * @param aPoint1 First position.
     * @param aPoint2 Second position.
     * @return Bounding rect.
     */
    static TRect CalculateBoundingRect( 
            const TPoint& aPoint1, 
            const TPoint& aPoint2 );
    
    /**
     * Snaps aValue to aReference if they are sufficiently close 
     * (defined by aMargin).
     *
     * @param aValue Value to be checked.
     * @param aReference Reference value.
     * @param aMargin Margin (applied to all directions).
     */
    static void NormalizeValue( TInt& aValue, TInt aReference, TInt aMargin );
    
    /**
     * Calculates movement value from width & height delta.
     * 
     * @param aWidthDelta Width delta.
     * @param aHeightDelta Height delta.
     * @return movement value, 0 if no movement.
     */
    static TInt CalculateMovement( TInt aWidthDelta, TInt aHeightDelta );
    
    /**
     * Checks duration threshold.
     * @param aEventTime Current pointer event time.
     * @return ETrue if ok, EFalse otherwise.
     */
    TBool CheckDurationThreshold( const TTime& aEventTime ) const;
    
private: // data
    
    /**
     * Boolean flag to indicate whether pinch gesture has been detected.
     */
    TBool iPinchDetected;

    /**
     * Current bounding rectangle for pinch.
     */
	TRect iPinchRect;
	
	/**
	 * Direction tracer for width.
	 */
	TDirectionTracer iPinchWidthTracer;
	
	/**
	 * Direction tracer for height.
	 */
	TDirectionTracer iPinchHeightTracer;
    
    /**
     * Pinch width direction tracer reset counter.
     * If height changes repeatedly without any width changes,
     * then width direction tracer is reset.
     */
	TInt iResetPinchWidthTracer;
	
	/**
	 * Pinch height direction tracer reset counter.
	 * If width changes repeatedly without any height changes,
	 * then height direction tracer is reset.
	 */
	TInt iResetPinchHeightTracer;
    
	/**
	 * Time (from event) when iStoredWidthDelta & iStoredHeightDelta
	 * were updated.
	 */
	TTime iStoredTime;
	
	/**
	 * Stored width delta value.
	 */
	TInt iStoredWidthDelta;
	
	/**
	 * Stored height delta value.
	 */
	TInt iStoredHeightDelta;
	
	/**
	 * ETrue if continuous feedback ongoing.
	 */
	TBool iContinuousFeedback;
	
    };

} // namespace AknTouchGestureFw

#endif // C_AKNTOUCHGESTUREFWPINCHRECOGNIZER_H
