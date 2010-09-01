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
* Description:  Drag touch gesture recognizer.
*
*/

#ifndef C_AKNTOUCHGESTUREFWDRAGRECOGNIZER_H
#define C_AKNTOUCHGESTUREFWDRAGRECOGNIZER_H


#include "akntouchgesturefwbaserecognizer.h"

namespace AknTouchGestureFw {

/**
 *  Drag touch gesture recognizer.
 *
 *  @lib akntouchgesturefw
 *  @since S60 v5.2
 */
NONSHARABLE_CLASS( CAknTouchGestureFwDragRecognizer )
    : public CAknTouchGestureFwBaseRecognizer
    {

public:

    /**
     * Two-phased constructor.
     *
     * @param  aEngine  The gesture recognition engine.
     */
    static CAknTouchGestureFwDragRecognizer* NewL(
            CAknTouchGestureFwRecognitionEngine& aEngine );

    /**
     * Two-phased constructor.
     *
     * @param  aEngine  The gesture recognition engine.
     */
    static CAknTouchGestureFwDragRecognizer* NewLC(
            CAknTouchGestureFwRecognitionEngine& aEngine );

    /**
     * Destructor.
     */
    virtual ~CAknTouchGestureFwDragRecognizer();

public: // From base class CAknTouchGestureFwBaseRecognizer.

    /**
     * Returns the recognizer's gesture group.
     *
     * @return Gesture group.
     */
    TAknTouchGestureFwGroup GestureGroup() const;

    /**
     * Cancels gesture recognition.
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
    CAknTouchGestureFwDragRecognizer(
            CAknTouchGestureFwRecognitionEngine& aEngine );

    /**
     * Starts single-touch recognition.
     *
     * @param  aPointerPos  Current pointer position.
     */
    void StartSingleRecognizing( const TPoint& aPointerPos );

    /**
     * Handles single-touch recognition cycle.
     * Called for every drag event when one pointer is down.
     *
     * @param  aPointerPos  New position of pointer.
     */
    void SingleRecognizeL( const TPoint& aPointerPos );

    /**
     * Completes single-touch recognition.
     */
    void CompleteSingleRecognizingL();

    /**
     * Asks engine to send drag event to observer.
     *
     * @param  aGestureState  Drag gesture state.
     */
    void SendDragEventL( TAknTouchGestureFwState aGestureState );

    /**
     * Resets the recognizer.
     */
    void Reset();

    /**
     * Returns current gesture position.
     *
     * @return Current gesture position.
     */
    TPoint CurrentPos() const;

    /**
     * Returns previous gesture position.
     *
     * @return Previous gesture position.
     */
    TPoint PreviousPos() const;

private: // data

    /**
     * Start position of gesture.
     */
    TPoint iStartPosition;

    /**
     * Current position of gesture.
     */
    TPoint iCurrentPosition;

    /**
     * Previous position of gesture.
     */
    TPoint iPreviousPosition;

    /**
     * ETrue if drag gesture already detected.
     */
    TBool iDragDetected;

    /**
     * Drag threshold area.
     */
    TThresholdArea iDragArea;
    
    /**
     * Boolean flag to indicate if drag recognition
     * should be started upon single touch drag.
     * This flag may be set when multi touch changes to
     * single (i.e. another pointer was released).
     */
    TBool iStartOnSingleTouchDrag;
    
    /**
     * ETrue if continuous feedback ongoing.
     */
    TBool iContinuousFeedback;
    };

} // namespace AknTouchGestureFw

#endif // C_AKNTOUCHGESTUREFWDRAGRECOGNIZER_H
