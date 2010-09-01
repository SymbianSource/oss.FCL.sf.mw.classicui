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

#ifndef C_AKNTOUCHGESTUREFWFLICKRECOGNIZER_H
#define C_AKNTOUCHGESTUREFWFLICKRECOGNIZER_H

#include "akntouchgesturefwbaserecognizer.h"

namespace AknTouchGestureFw {

class CAknTouchGestureFwDragTracer;

/**
 *  Flick touch gesture recognizer.
 *
 *  @lib akntouchgesturefw
 *  @since S60 v5.2
 */
NONSHARABLE_CLASS( CAknTouchGestureFwFlickRecognizer )
    : public CAknTouchGestureFwBaseRecognizer
    {

public:

    /**
     * Two-phased constructor.
     *
     * @param  aEngine  The gesture recognition engine.
     */
    static CAknTouchGestureFwFlickRecognizer* NewL(
            CAknTouchGestureFwRecognitionEngine& aEngine );

    /**
     * Two-phased constructor.
     *
     * @param  aEngine  The gesture recognition engine.
     */
    static CAknTouchGestureFwFlickRecognizer* NewLC(
            CAknTouchGestureFwRecognitionEngine& aEngine );

    /**
     * Destructor.
     */
    virtual ~CAknTouchGestureFwFlickRecognizer();

public: // From base class CAknTouchGestureFwBaseRecognizer.

    /**
     * Returns recognizer gesture group.
     *
     * @return EAknTouchGestureFwGroupFlick
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
    CAknTouchGestureFwFlickRecognizer(
            CAknTouchGestureFwRecognitionEngine& aEngine );

    /**
     * Symbian second-phase constructor.
     */
    void ConstructL();

    /**
     * Starts single-touch recognition.
     *
     * @param  aPointerPos  Current pointer position.
     * @param  aTimeStamp   Pointer event time stamp.
     */
    void StartSingleRecognizing( const TPoint& aPointerPos,
                                 const TTime& aTimeStamp );

    /**
     * Handles single-touch recognition cycle.
     * Called for every drag event when one pointer is down.
     *
     * @param  aPointerPos  New position of pointer.
     * @param  aTimeStamp   Pointer event time stamp.
     */
    void SingleRecognizeL( const TPoint& aPointerPos,
                           const TTime& aTimeStamp);

    /**
     * Completes single-touch recognition.
     *
     * @param  aPointerPos       New position of pointer, valid only if
     *                           parameter @c aStartMultiTouch is @c EFalse.
     * @param  aTimeStamp        Pointer event time stamp.                           
     * @param  aStartMultiTouch  If @c ETrue, recognition was cancelled
     *                           by multitouch.
     */
    void CompleteSingleRecognizingL( const TPoint& aPointerPos,
                                     const TTime& aTimeStamp,
                                     TBool aStartMultiTouch );

    /**
     * Asks engine to send flick event to observer.
     *
     * @param  aGestureType    Flick gesture type.
     * @param  aPosition       Flick position.
     * @param  aSpeed          Flick speed.
     */
    void SendFlickEventL( TAknTouchGestureFwType aGestureType,
                          const TPoint& aPosition,
                          const TPoint& aSpeed );

    /**
     * Resets recognizer.
     */
    void Reset();

    /**
     * Adds a point to the sequences of points that forms the gesture.
     *
     * @param  aPoint      The point to add.
     * @param  aTimeStamp  Pointer event time stamp.
     */
    void AddPoint( const TPoint& aPoint,
                   const TTime& aTimeStamp );

    /**
     * Returns @c ETrue if the gesture has no points.
     *
     * @return @c ETrue if the gesture has no points.
     */
    TBool IsEmpty() const;

    /**
     * Checks if flick is recognised. Determines its direction and speed.
     *
     * @param  aFlickGestureType  On return type of flick gesture.
     * @param  aSpeed             On return the speed of the flick.
     *
     * @return ETrue if flick is recognized (speed is over threshold).
     */
    TBool DetermineFlickTypeAndSpeed(
            TAknTouchGestureFwType& aFlickGestureType,
            TPoint& aSpeed );

    /**
     * Calculates distance and speed for flick.
     *
     * @param  aDistance  In return distance of flick.
     * @param  aSpeed     In return speed of flick is pixels per seconds.
     *
     * @return @c ETrue if there was enought information to calculate values.
     */
    TBool CalculateFlickParameters( TPoint& aDistance, TPoint& aSpeed );

    /**
     * Handles direction changes in drag.
     * If direction changes removes unnecessary points before
     * direction change point.
     *
     * @param  aPosition  New position.
     */
    void HandleDirectionChanges( const TPoint& aPosition );

    /**
     * Returns elapsed time.
     *
     * @param  aStartTime  Time of start point.
     * @param  aEndTime    Time of end point.
     *
     * @return Elapsed time between @c aStartTime and @c aEndTime.
     */
    static TTimeIntervalMicroSeconds32 Elapsed( const TTime& aStartTime,
                                                const TTime& aEndTime );

    /**
     * Removes unnecessary (oldest) points before direction change point.
     *
     * @param  aNumberOfPoints  Number of points to leave.
     */
    void RemovePreviousPoints( TInt aNumberOfPoints );

    /**
     * Returns maximum flick buffer length.
     *
     * @return Maximum flick buffer length.
     */
    TInt MaximumBufferLength() const;

    /**
     * Returns flick speed threshold.
     *
     * @return Flick speed threshold.
     */
    TInt FlickSpeedThreshold() const;

    /**
     * Returns flick detection time.
     *
     * @return Flick detection time.
     */
    TInt FlickDetectionTime() const;

    /**
     * Returns flick direction change sensitivity.
     *
     * @return Flick direction change sensitivity.
     */
    TInt DirectionChangeSensitivity() const;

private: // data

    /**
     * Sequence of points that make up the gesture.
     * Used only for single-touch gesture.
     */
    RArray<TPointEntry> iPoints;

    /**
     * Drag tracer instance to detect changes in drag direction
     * and remove unnecessary points.
     * Own.
     */
    CAknTouchGestureFwDragTracer* iDragTracer;

    /**
     * Is the drag threshold exceeded or not.
     */
    TBool iThresholdExceeded;

    /**
     * Drag threshold area.
     */
    TThresholdArea iDragArea;

    /**
     * Flick speed.
     */
    TPoint iFlickSpeed;
    
    /**
     * Boolean flag to indicate if drag recognition
     * should be started upon single touch drag.
     * This flag may be set when multi touch changes to
     * single (i.e. another pointer was released). 
     */
    TBool iStartOnSingleTouchDrag;
    };

} // namespace AknTouchGestureFw

#endif // C_AKNTOUCHGESTUREFWFLICKRECOGNIZER_H
