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
* Description:  Touch gesture recognition engine.
*
*/

#ifndef C_AKNTOUCHGESTUREFWRECOGNITIONENGINE_H
#define C_AKNTOUCHGESTUREFWRECOGNITIONENGINE_H

#include <akntouchgesturefwevents.h>
#include <touchfeedback.h>

#include "akntouchgesturefwutils.h"

namespace AknTouchGestureFw {

class MAknTouchGestureFwObserver;
class CAknTouchGestureFwPointerState;
class CAknTouchGestureFwBaseRecognizer;
class CAknTouchGestureFwSettings;

/**
 *  Touch gesture recognition engine.
 *
 *  @lib akntouchgesturefw
 *  @since S60 v5.2
 */
NONSHARABLE_CLASS( CAknTouchGestureFwRecognitionEngine ) : public CBase
    {

public:

    /**
     * Two-phased constructor.
     *
     * @param  aObserver  Gesture observer to which the gesture events are
     *                    sent when a gesture is recognized.
     * @param  aControl   Control receiving the gesture pointer events.                    
     */
    static CAknTouchGestureFwRecognitionEngine* NewL(
            MAknTouchGestureFwObserver& aObserver,
            CCoeControl* aControl );

    /**
     * Two-phased constructor.
     *
     * @param  aObserver  Gesture observer to which the gesture events are
     *                    sent when a gesture is recognized.
     * @param  aControl   Control receiving the gesture pointer events.                    
     */
    static CAknTouchGestureFwRecognitionEngine* NewLC(
            MAknTouchGestureFwObserver& aObserver,
            CCoeControl* aControl );

    /**
     * Destructor.
     */
    virtual ~CAknTouchGestureFwRecognitionEngine();

    /**
     * Notifies observer of a gesture.
     *
     * @param  aEvent  Gesture event.
     */
    void NotifyObserverL( MAknTouchGestureFwEvent& aEvent );

    /**
     * Sets client gesture interest.
     *
     * @param  aGestureGroups  New client gesture interest.
     */
    void SetGestureInterestL( TUint aGestureGroups );

    /**
     * Provides client gesture interest.
     *
     * @return Client gesture interest.
     */
    TUint GestureInterest() const;

    /**
     * Cancels all gesture recognition.
     */
    void CancelRecognizing();

    /**
     * Handles gesture control targeted pointer event received
     * from window server.
     *
     * @param  aPointerData  Pointer event related data.
     */
    void HandlePointerEventL( const TPointerEventData& aPointerData );

    /**
     * Returns a reference to the Central Repository settings provider.
     *
     * @return Settings provider.
     */
    CAknTouchGestureFwSettings& Settings() const;

    /**
     * Enables testing features.
     */ 
    void EnableTestingFeatures();
    
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
     * Defines gesture groups, which trigger tactile feedback automatically.
     *
     * @param aGestureGroups - Those gesture groups, which trigger tactile
     *                         feedback automatically as touch gestures
     *                         are recognized or being in the process
     *                         of recognizing.   
     */ 
    void SetFeedbackForGroupsL( TUint aGestureGroups );

    /**
     * Sets gesture types which generate tactile and audio feedback.
     * 
     * @param aGestureGroup - Gesture group, which tactile- and audio feedback
     *                        is affected by this function call.     
     * @param  aGestureTypesForTactile Gesture types with tactile feedback
     * @param  aGestureTypesForAudio   Gesture types with audio feedback
     */
    void SetFeedbackForTypesL(
        TAknTouchGestureFwGroup aGestureGroup,
        TUint aGestureTypesForTactile,
        TUint aGestureTypesForAudio );
    

private:

    /**
     * C++ constructor.
     *
     * @param  aObserver  Gesture observer to which the gesture events are
     *                    sent when a gesture is recognized.
     * @param  aControl   Control receiving the gesture pointer events.
     */
    CAknTouchGestureFwRecognitionEngine(
            MAknTouchGestureFwObserver& aObserver,
            CCoeControl* aControl );

    /**
     * Symbian second-phase constructor.
     */
    void ConstructL();

    /**
     * Enables or disables the gesture recognizers on the recognizer array
     * based on the client's gesture interest.
     *
     * @param  aGestureInterest  Current gesture interest.
     */
    void UpdateRecognizersForInterest( TUint aGestureInterest );

    /**
     * Creates new gesture recognizer according to the gesture group.
     *
     * @param  aGroup   Gesture group.
     *
     * @return Pointer to the created recognizer.
     */
    CAknTouchGestureFwBaseRecognizer* CreateRecognizerL(
            TAknTouchGestureFwGroup aGroup );
    
    /**
     * returns existing gesture recognizer according to the gesture group.
     *
     * @param  aGroup   Gesture group.
     *
     * @return Pointer to the existing recognizer or NULL if not found.
     */
    CAknTouchGestureFwBaseRecognizer* Recognizer(
            TAknTouchGestureFwGroup aGroup );

    /**
     * Sends pointer event to recognizers.
     *
     * @param  aMultiPointer  @c ETrue if event is multi pointer event.
     * @param  aPointerData   Pointer event related data.
     */
    void SendPointerEventToRecognizersL(
            TBool aMultiPointer,
            const TPointerEventData& aPointerData );

private: // data

    /**
     * Observer for gestures being deduced from pointer events.
     * Not own.
     */
    MAknTouchGestureFwObserver& iObserver;

    /**
     * Pointer state.
     * Own.
     */
    CAknTouchGestureFwPointerState* iPointerState;

    /**
     * CenRep settings provider.
     * Own.
     */
    CAknTouchGestureFwSettings* iSettings;

    /**
     * Flags determing which gesture groups should be recognized.
     */
    TUint iGestureInterest;

    /**
     * Boolean flag to indicate if single touch recognition is ongoing.
     */
    TBool iSingleRecognizing;

    /**
     * Boolean flag to indicate if multi touch recognition is ongoing.
     */
    TBool iMultiRecognizing;

    /**
     * Array for recognizers.
     */
    RPointerArray<CAknTouchGestureFwBaseRecognizer> iRecognizers;

    /**
     * ETrue if testing features are enabled.
     */
    TBool iTestingEnabled;
    
    /**
     * Subcriber control.
     * Not own.
     */
    CCoeControl* iControl;
    
    /**
     * Touch feedback instance.
     * Not own.
     */
    MTouchFeedback* iFeedBack;    
    
    };

} // namespace AknTouchGestureFw

#endif // C_AKNTOUCHGESTUREFWRECOGNITIONENGINE_H
