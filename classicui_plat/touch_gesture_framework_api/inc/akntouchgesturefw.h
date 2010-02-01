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
* Description: Touch gesture framework interface.
*
*/

#ifndef C_AKNTOUCHGESTUREFW_H
#define C_AKNTOUCHGESTUREFW_H

#include <e32base.h>
#include <akntouchgesturefwobserver.h>
#include <akntouchgesturefwevents.h>

class CCoeControl;

namespace AknTouchGestureFw
{

class CAknTouchGestureFwImpl;

/**
 * CAknTouchGestureFw
 *
 * Touch gesture framework provides functionality to convert a stream of
 * pointer events into a logical gesture.
 *
 * Pointer to a control (@c CCoeControl deriving object) is provided
 * for the framework and gestures are recognized in the area of the control.
 * Recognized gestures are reported to the gesture observer. The gesture
 * observer should always set the gesture interest in order to receive
 * gesture events.
 *
 * Each gesture has its own gesture group (type @c TAknTouchGestureFwGroup).
 * The events that are sent to gesture observer vary according to the gesture
 * group.
 *
 * Example of gesture fw creation:
 * @code
 *     CAknTouchGestureFw* gestureFw =
 *         CAknTouchGestureFw::NewL( this, gestureControl );
 *     // Set gesture interest (drag and flick gestures)
 *     gestureFw->SetGestureInterestL(
 *         EAknTouchGestureFwGroupDrag | EAknTouchGestureFwGroupFlick );
 * @endcode
 *
 * Reset gesture interest (no events are sent to gesture observer):
 * @code
 *     gestureFw->SetGestureInterestL( EAknTouchGestureFwNoGroup );
 * @endcode
 *
 * @lib akntouchgesturefw
 * @since S60 v5.2
 */
NONSHARABLE_CLASS( CAknTouchGestureFw ) : public CBase
    {

public:

    /**
     * Two-phased constructor.
     *
     * The gesture observer and gesture receiving control need to be
     * provided to @c CAknTouchGestureFw upon construction.
     * Observer is notified about recognized gestures. Reference to the
     * subscriber control is needed so that gesture framework can monitor
     * the pointer events of the gesture receiving control.
     *
     * Note that the subscriber control must have a window (either be
     * a window-owning control itself or have a window-owning control as
     * an ancestor). Also the window hiearchy must not be changed for the
     * subscriber control after constructing the gesture framework
     * (e.g. changing the parent of the subscriber control).
     *
     * If the observer is interested in gestures that need
     * advanced pointer events when recognizing the gestures,
     * advanced pointer events are enabled for the control window. This means
     * that if the device is able to handle more than one pointer at the same
     * time, then events are delivered to control window from all detected
     * pointers.
     *
     * If the observer is interested in gestures that need pointer drag events
     * when recognizing the gestures, drag events are enabled for the control
     * window.
     * 
     * For those control windows that have advanced pointer or drag
     * events enabled are also enabled pointer grab. This ensures that gestures
     * are recognized also outside the control area (when gesture recognition
     * has begun inside control area). 
     *
     * @param  aObserver  Observer of the Gesture framework.
     * @param  aControl   Subscriber control for pointer events.
     *
     * @leave KErrNotFound In case the subscriber control has no window.
     */
    IMPORT_C static CAknTouchGestureFw* NewL(
            MAknTouchGestureFwObserver& aObserver,
            CCoeControl& aControl );

    /**
     * Destructor.
     */
    virtual ~CAknTouchGestureFw();

public:

    /**
     * Sets gesture interest. Use binary OR to choose several gesture groups.
     * Default value for the interest is @c EGestureNoGroup.
     *
     * This method may modify window attributes and so it should be called
     * before activating the window.
     *
     * @see TAknTouchGestureFwGroup
     *
     * @param  aGestureGroups  Interested gesture groups.
     * @param  aFlags          Additional flags, not used currently.
     */
    IMPORT_C void SetGestureInterestL( TUint aGestureGroups,
                                       TUint aFlags = 0 );

    /** 
     * Defines gesture groups, which trigger tactile feedback automatically.
     *
     * Tactile feedback is triggered according to default behaviour of
     * each group, that means that both vibra and audio feedback are on
     * for each gesture type in defined gesture groups.
     * 
     * Use SetFeedbackForTypesL function for more fine-grained
     * control over the generated feedback.
     *
     * Notice that any group must have been set as interested gesture
     * group with SetGestureInterestL function before it can trigger
     * tactile feedback at all.
     *  
     * Tactile feedback is off for all gesture groups as default
     * (if this function or SetFeedbackForGroupsL is not called).
     *                     
     * @since S60 v5.2
     * @param aGestureGroups - Those gesture groups, which trigger tactile
     *                         feedback automatically as touch gestures
     *                         are recognized or being in the process
     *                         of recognizing.               
     */    
    IMPORT_C void SetFeedbackForGroupsL( TUint aGestureGroups );

    /**
     * Defines gesture types, which trigger tactile feedback automatically.
     * 
     * This function defines, which gesture types in given gesture group
     * trigger feedback automatically according to default behaviour.
     *
     * It is possible to define tactile (haptic) and audio feedback behaviour
     * separately, although it is recommended that same bitmasks are used
     * for both of these.
     *
     * Notice that given gesture group must have been set as interested
     * gesture group with SetGestureInterestL function before it can trigger
     * tactile feedback at all.
     * 
     * Example use for enabling double tap and long tap haptic feedback, but
     * no feedback for single tap event, and no audio feedback:
     * @code 
     *     SetFeedbackForTypesL( 
     *         EAknTouchGestureFwGroupTap, 
     *         EAknTouchGestureFwDoubleTap | EAknTouchGestureFwLongTap,
     *         0 )
     * @endcode
     *                    
     * @since S60 v5.2
     * @param aGestureGroup - Gesture group, which tactile- and audio feedback
     *                        is affected by this function call.           
     * @param aGestureTypesForTactile - Bitmask of gesture types, which
     *                                  trigger tactile feedback automatically.
     * @param aGestureTypesForAudio - Bitmask of gesture types, which
     *                                trigger audio feedback automatically.
     */
    IMPORT_C void SetFeedbackForTypesL( TAknTouchGestureFwGroup aGestureGroup,
                                        TUint aGestureTypesForTactile,
                                        TUint aGestureTypesForAudio );

    /** 
     * Extension function.
     *
     * @param  aExtensionId  Extension id. 
     * @param  a0            First extension method parameter.
     * @param  a1            Second extension method parameter.
     */    
    TInt Extension_( TUint aExtensionId, TAny*& a0, TAny* a1 );

private:

    /**
     * C++ constructor.
     */
    CAknTouchGestureFw();

    /**
     * Symbian second-phase constructor.
     *
     * @param  aObserver  Observer of the Gesture framework.
     * @param  aControl   Subscriber control for pointer events.
     */
    void ConstructL( MAknTouchGestureFwObserver& aObserver,
                     CCoeControl& aControl );

private: // data

    /**
     * Interface implementation.
     * Own.
     */
    CAknTouchGestureFwImpl* iImpl;
    };

} // namespace AknGestureFw

#endif // C_AKNTOUCHGESTUREFW_H
