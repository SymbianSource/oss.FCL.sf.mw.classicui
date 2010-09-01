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
* Description:  Base class for touch gesture recognizers.
*
*/

#ifndef C_AKNTOUCHGESTUREFWBASERECOGNIZER_H
#define C_AKNTOUCHGESTUREFWBASERECOGNIZER_H

#include <akntouchgesturefwevents.h>
#include <touchfeedback.h>

#include "akntouchgesturefwutils.h"

namespace AknTouchGestureFw {

class CAknTouchGestureFwRecognitionEngine;
class MAknTouchGestureFwEvent;
class CAknTouchGestureFwSettings;

/**
 *  Base class for touch gesture recognizers.
 *
 *  @lib akntouchgesturefw
 *  @since S60 v5.2
 */
NONSHARABLE_CLASS( CAknTouchGestureFwBaseRecognizer ) : public CBase
    {

public:

    /**
     * Returns @c ETrue if recognizer is enabled.
     *
     * @return @c ETrue if recognizer is enabled.
     */
    TBool Enabled() const;

    /**
     * Enables or disables recognizer.
     *
     * @param  aEnable  @c ETrue if recognizer is to be enabled,
     *                  @c EFalse otherwise.
     */
    void SetEnabled( TBool aEnable );

    /**
     * Returns recognizer gesture group.
     *
     * @return Gesture group.
     */
    virtual TAknTouchGestureFwGroup GestureGroup() const = 0;

    /**
     * Cancels gesture recognition.
     */
    virtual void CancelRecognizing() = 0;

    /**
     * Handles single pointer event. 
     * Single touch is expected to be always reliable.
     *
     * @param  aPointerData  Pointer event related data.
     */
    virtual void HandleSinglePointerEventL(
            const TPointerEventData& aPointerData ) = 0;

    /**
     * Handles multi pointer event.
     *
     * @param  aPointerData            Pointer event related data.
     * @param  aFirstPointerPosition   First pointer position.
     * @param  aSecondPointerPosition  Second pointer position.
     */
    virtual void HandleMultiPointerEventL(
            const TPointerEventData& aPointerData,
            const TPoint& aFirstPointerPosition,
            const TPoint& aSecondPointerPosition ) = 0;
    
    /**
     * Sets gesture types which generate tactile and audio feedback.
     * 
     * @param  aGestureTypesForTactile Gesture types with tactile feedback
     * @param  aGestureTypesForAudio   Gesture types with audio feedback
     */
    void SetFeedbackForTypesL(
            TUint aGestureTypesForTactile,
            TUint aGestureTypesForAudio );

protected:

    /**
     * C++ constructor.
     *
     * @param  aEngine  The gesture recognition engine.
     */
    CAknTouchGestureFwBaseRecognizer(
            CAknTouchGestureFwRecognitionEngine& aEngine );

    /**
     * Sends event to engine.
     *
     * @param  aEvent  Touch gesture event to send.
     */
    void SendGestureEventL( MAknTouchGestureFwEvent& aEvent );

    /**
     *  Returns a reference to the Central Repository settings provider.
     *
     * @return Settings provider.
     */
    CAknTouchGestureFwSettings& Settings() const;

    /**
     * Returns drag threshold.
     *
     * @return Drag threshold.
     */
    TInt DragThreshold() const;
    
    /**
     * Gives immediate direct feedback.
     *
     * @param aLogicalFeedback - The logical feedback type to play.
     * @param aFeedbackType - Feedback types to be played as a bitmask 
     *                        combination of enumeration items from
     *                        TTouchFeedbackType.  
     */
    void ImmediateFeedback(
        TTouchLogicalFeedback aLogicalFeedback,
        TTouchFeedbackType aFeedbackType );   
    
    /**
     * Starts continuous feedback.
     *
     * @param aType         - The continuous feedback type to play.
     * @param aIntensity    - Intensity of continuous feedback.
     * @param aTimeout      - Timeout value to automatically stop continuous 
     *                        feedback if there's no new Start call within the
     *                        timeout. Use value 0 if timeout is not used.
     */
    void StartContinuousFeedback(
        TTouchContinuousFeedback aContinuousFeedback,
        TInt aIntensity,
        TTimeIntervalMicroSeconds32 aTimeout );    
    
    /**
     * Modifies continuous feedback.
     *
     * @param aIntensity     - New intensity value for feedback.
     */    
    void ModifyContinuousFeedback( TInt aIntensity );    
       
    /**
     * Stops continuous feedback.
     */
    void StopContinuousFeedback();   

    /**
     * Returns feedback types of requested gesture type.
     * 
     * @return Feedback type
     */
    TTouchFeedbackType FeedbackType( TAknTouchGestureFwType aGestureType );
    
private: // data

    /**
     * Reference to the gesture recognition engine.
     * Not own.
     */
    CAknTouchGestureFwRecognitionEngine& iEngine;

    /**
     * Is the recognizer enabled or not.
     */
    TBool iEnabled;
    
    /**
     * Gesture types for tactile vibra.
     */
    TUint iGestureTypesForTactile;
    
    /**
     * Gesture types for audio.
     */
    TUint iGestureTypesForAudio; 
    };

} // namespace AknTouchGestureFw

#endif // C_AKNTOUCHGESTUREFWBASERECOGNIZER_H
