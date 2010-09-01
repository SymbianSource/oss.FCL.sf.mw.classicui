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
* Description:  Touch gesture framework implementation.
*
*/

#ifndef C_AKNTOUCHGESTUREFWIMPL_H
#define C_AKNTOUCHGESTUREFWIMPL_H

#include <coemain.h>
#include <e32base.h>
#include <akntouchgesturefwevents.h>

#include "akntouchgesturefwutils.h"

class CCoeControl;

namespace AknTouchGestureFw
{

class MAknTouchGestureFwObserver;
class CAknTouchGestureFwRecognitionEngine;

/**
 * Implementation of CGestureFw interface
 */
NONSHARABLE_CLASS( CAknTouchGestureFwImpl ) : public CBase,
                                              public MCoeForegroundObserver,
                                              public MCoeMessageMonitorObserver
    {
public:

    /**
     * Two-phased constructor.
     * 
     * @param  aObserver  Gesture framework observer.
     * @param  aControl   Control receiving the gesture pointer events.
     */
    static CAknTouchGestureFwImpl* NewL(
            MAknTouchGestureFwObserver& aObserver,
            CCoeControl* aControl );

    /**
     * Two-phased constructor.
     * 
     * @param  aObserver  Gesture framework observer.
     * @param  aControl   Control receiving the gesture pointer events.
     */
    static CAknTouchGestureFwImpl* NewLC(
            MAknTouchGestureFwObserver& aObserver,
            CCoeControl* aControl );

    /**
     * Destructor.
     */
    virtual ~CAknTouchGestureFwImpl();

    /**
     * Handles simulated pointer events.
     *
     * @param  aPointerData  Pointer event related data.
     */
    void HandleSimulatedPointerEventL( const TPointerEventData& aPointerData );

    /**
     * Sets target control for window server events.
     *
     * @param  aControl  New subscriber control.
     *
     * @leave KErrNotFound In case the target control has no window.
     */
    void SetSubscriberControlL( CCoeControl* aControl );

    /**
     * Sets gesture groups which should be recognized.
     * 
     * @param  aGestureGroups  New gesture interest.
     */ 
    void SetGestureInterestL( TUint aGestureGroups );

    /**
     * Returns gesture groups which should be recognized.
     * 
     * @return Current gesture interest.
     */
    TUint GestureInterest() const;
    
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
     * Defines gesture types, which trigger tactile feedback automatically.
     *
     * @param aGestureGroup - Gesture group, which tactile- and audio feedback
     *                        is affected by this function call.     
     *
     * @param aGestureTypesForTactile - Bitmask of gesture types, which
     *                                  trigger tactile feedback automatically.
     * @param aGestureTypesForAudio - Bitmask of gesture types, which
     *                                trigger audio feedback automatically.   
     */                      
    void SetFeedbackForTypesL(
        TAknTouchGestureFwGroup aGestureGroup,
        TUint aGestureTypesForTactile,
        TUint aGestureTypesForAudio );

    /**
     * Enables testing features.
     */ 
    void EnableTestingFeatures();

private:

    /**
     * C++ constructor.
     * 
     * @param  aControl  Control receiving the gesture pointer events.
     */
    CAknTouchGestureFwImpl( CCoeControl* aControl );

    /**
     * Symbian second-phase constructor.
     *
     * @param  aObserver  Gesture framework observer.
     */
    void ConstructL( MAknTouchGestureFwObserver& aObserver );

    /**
     * Handles pointer events.
     *
     * @param  aPointerData  Pointer event related data.
     */ 
    void HandlePointerEventL( const TPointerEventData& aPointerData );

    /**
     * Cancels ongoing recognition.
     */
    void CancelRecognition();

    /**
     * Enables drag events and advanced pointer events for window if needed.
     */
    void EnableAdditionalEvents();

    /**
     * Returns @c ETrue if pointer event is targeted to gesture control.
     * 
     * @param  aTargetControl  Event target control.
     * @param  aEvent          Pointer event.
	 *
     * @return @c ETrue if pointer event is targeted to control.
     */
    TBool PointerEventTargetedToControl( CCoeControl* aTargetControl,
	                                     TPointerEvent& aEvent ) const;

    /**
     * Converts position in window area according to control window
     * coordinates.
     * 
     * @param  aWindow    Window with position.
     * @param  aPosition  Position to convert.
     */
    void ConvertPositionToControlWindow( RDrawableWindow* aWindow,
	                                     TPoint& aPosition ) const;

// from base class MCoeForegroundObserver

    /**
     * Handles the application coming to the foreground.
     */
    void HandleGainingForeground();

    /**
     * Handles the application going into the background.
     */
    void HandleLosingForeground();

public: // From base class MCoeMessageMonitorObserver.

    /**
     * Received windows messages for monitoring.
     *
     * @param  aEvent  The window server event data.
     */
    void MonitorWsMessage( const TWsEvent& aEvent );

private: // data

    /**
     * ETrue if gesture framework is monitoring WS events
     */
    TBool iMonitoringWs;

    /**
     * Control environment.
     * Not own.
     */
    CCoeEnv* iCoeEnv;

    /**
     * Subcriber control.
     * Not own.
     */
    CCoeControl* iSubscriberControl;

    /**
     * Window control.
     * Not own.
     */
    CCoeControl* iWindowControl;

    /**
     * Gesture recognition engine.
     * Own.
     */
    CAknTouchGestureFwRecognitionEngine* iRecognitionEngine;
    };

} // AknTouchGestureFw

#endif // C_AKNTOUCHGESTUREFWIMPL_H
