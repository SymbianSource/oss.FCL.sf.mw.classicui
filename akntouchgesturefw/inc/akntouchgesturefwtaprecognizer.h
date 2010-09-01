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

#ifndef C_AKNTOUCHGESTUREFWTAPRECOGNIZER_H
#define C_AKNTOUCHGESTUREFWTAPRECOGNIZER_H

#include "akntouchgesturefwbaserecognizer.h"

namespace AknTouchGestureFw {

/**
 *  Tap touch gesture recognizer.
 *
 *  @lib akntouchgesturefw
 *  @since S60 v5.2
 */
NONSHARABLE_CLASS( CAknTouchGestureFwTapRecognizer )
    : public CAknTouchGestureFwBaseRecognizer
    {

public:

    /**
     * Two-phased constructor.
     *
     * @param  aEngine  The gesture recognition engine.
     */
    static CAknTouchGestureFwTapRecognizer* NewL(
            CAknTouchGestureFwRecognitionEngine& aEngine );

    /**
     * Two-phased constructor.
     *
     * @param  aEngine  The gesture recognition engine.
     */
    static CAknTouchGestureFwTapRecognizer* NewLC(
            CAknTouchGestureFwRecognitionEngine& aEngine );

    /**
     * Destructor.
     */
    virtual ~CAknTouchGestureFwTapRecognizer();

public: // From base class CAknTouchGestureFwBaseRecognizer.

    /**
     * Returns the recognizer gesture group.
     *
     * @return @c EAknTouchGestureFwGroupTap
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
    CAknTouchGestureFwTapRecognizer(
            CAknTouchGestureFwRecognitionEngine& aEngine );

    /**
     * Starts tap recognition.
     *
     * @param  aStartPoint  Position where pointer was pressed down.
     * @param  aTimeStamp   Pointer event time stamp.
     */
    void StartTapRecognition( const TPoint& aStartPoint,
                              const TTime& aTimeStamp );

    /**
     * Continues tap recognition.
     * This is called on pointer drag events, on which it's checked that
     * the pointer hasn't moved outside of the tap threshold area.
     *
     * @param  aPoint  New position.
     */
    void TapRecognize( const TPoint& aPoint );

    /**
     * Completes tap recognition.
     * This is called when pointer up event is received, after which
     * the possible tap gesture can be recognized.
     * 
     * @param  aTimeStamp   Pointer event time stamp.
     */
    void CompleteTapRecognitionL( const TTime& aTimeStamp );

    /**
     * Sends a tap gesture event
     *
     * @param  aGestureType  Type of tap gesture.
     * @param  aPointerPos   Tap position.
     */
    void SendTapEventL( TAknTouchGestureFwType aGestureType,
                        const TPoint& aPointerPos );

    /**
     * Called by long tap timer when the time interval is exceeded.
     *
     * @param  aThis  Self pointer.
     *
     * @return EFalse
     */
    static TInt LongTapCallback( TAny* aThis );

    /**
     * Handles long tap callback related actions.
     */
    void HandleLongTapCallbackL();

    /**
     * Internal helper method to cancel the tap recognition.
     *
     * @param  aResetFirstTapDetection  @c ETrue if double tap not allowed.
     */
    void DoCancelTapRecognition( TBool aResetFirstTapDetection );

    /**
     * Returns the long tap threshold.
     * Long tap threshold is the amount of time after pointer down event
     * after which the tap will be recognized as a long tap.
     *
     * @return Long tap threshold.
     */
    TInt LongTapThreshold() const;

    /**
     * Returns the tap threshold.
     * Tap threshold is the maximum distance in pixels that there can be
     * between the pointer down and pointer up events for a tap gesture.
     *
     * @return Tap threshold.
     */
    TInt TapThreshold() const;

    /**
     * Returns the maximum delay that is allowed between the two taps
     * in double tap gesture.
     *
     * @return Double tap maximum duration.
     */
    TInt DoubleTapMaximumDuration() const;

private: // data

    /**
     * Threshold area.
     */
    TThresholdArea iThresholdArea;

    /**
     * Long tap timer.
     */
    CPeriodic* iLongTapTimer;

    /**
     * Boolean flag to indicate if first tap has been detected.
     */
    TBool iFirstTapDetected;

    /**
     * Time of first tap.
     */
    TTime iFirstTapTime;

    /**
     * Position of first tap.
     */
    TPoint iFirstTapPos;
    
    /**
     * Intensity value for long tap detection.
     */  
    TInt iLongTapIntensity;
    
    /**
     * Boolean flag to indicate if long tap feedback has been started.
     */  
    TBool iFeedBackStarted;    
    
    };

} // namespace AknTouchGestureFw

#endif // C_AKNTOUCHGESTUREFWTAPRECOGNIZER_H
