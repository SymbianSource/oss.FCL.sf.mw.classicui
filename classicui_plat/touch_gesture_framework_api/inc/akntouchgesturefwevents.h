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
* Description:  Touch gesture framework events.
*
*/

#ifndef C_AKNTOUCHGESTUREFWEVENTS_H
#define C_AKNTOUCHGESTUREFWEVENTS_H

#include <e32std.h>

namespace AknTouchGestureFw
{

class MAknTouchGestureFwEvent;

/**
 * Enum for touch gesture groups.
 */
enum TAknTouchGestureFwGroup
    {
    /**
     * Group for tap gestures.
     * @see MAknTouchGestureFwTapEvent
     */
    EAknTouchGestureFwGroupTap        = 0x00000001,

    /**
     * Group for flick gestures.
     * @see MAknTouchGestureFwFlickEvent
     */
    EAknTouchGestureFwGroupFlick      = 0x00000002,

    /**
     * Group for drag gesture.
     * @see MAknTouchGestureFwDragEvent
     */
    EAknTouchGestureFwGroupDrag      = 0x00000004,

    /**
     * Group for pinch gesture.
     * @see MAknTouchGestureFwPinchEvent
     */
    EAknTouchGestureFwGroupPinch      = 0x00000008,

    /**
     * Group for no gestures.
     */
    EAknTouchGestureFwNoGroup         = 0x80000000,

    /**
     * Group for all gestures.
     */
    EAknTouchGestureFwAll             = 0x7fffffff
    };

/**
 * Enum for touch gesture type.
 */
enum TAknTouchGestureFwType
    {
    /**
     * Tap gestures - group @c EAknTouchGestureFwGroupTap.
     */
    EAknTouchGestureFwTap                              = 0x00000001,
    EAknTouchGestureFwDoubleTap                        = 0x00000002,
    EAknTouchGestureFwLongTap                          = 0x00000004,

    /**
     * Flick gestures - group @c EAknTouchGestureFwGroupFlick.
     */
    EAknTouchGestureFwFlickLeft                        = 0x00000001,
    EAknTouchGestureFwFlickRight                       = 0x00000002,
    EAknTouchGestureFwFlickUp                          = 0x00000004,
    EAknTouchGestureFwFlickDown                        = 0x00000008,

    /**
     * Drag gesture - group @c EAknTouchGestureFwGroupDrag.
     */
    EAknTouchGestureFwDrag                             = 0x00000001,

    /**
     * Pinch gesture - group @c EAknTouchGestureFwGroupPinch.
     */
    EAknTouchGestureFwPinch                            = 0x00000001,

    /**
     * Unknown gesture.
     */
    EAknTouchGestureFwUnknown                          = 0x80000000
    };

/**
 * Enum for touch gesture states.
 */
enum TAknTouchGestureFwState
    {
    /**
     * Continuous gesture movement started.
     */
    EAknTouchGestureFwStart,

    /**
     * Continuous gesture movement ongoing or one-time gesture recognized.
     */
    EAknTouchGestureFwOn,

    /**
     * Continuous gesture movement stopped.
     */
    EAknTouchGestureFwStop
    };


/**
 * Touch gesture event. Common interface for all touch gesture events.
 * Touch gesture framework sends these type events to the gesture observer.
 * Events should be cast to some of the touch gesture event sub classes
 * according to the gesture event group.
 *
 * @lib akntouchgesturefw
 * @since S60 v5.2
 */
class MAknTouchGestureFwEvent
    {

public:

    /**
     * Returns the gesture group of the event.
     *
     * @return Gesture group.
     */
    virtual TAknTouchGestureFwGroup Group() const = 0;

    /**
     * Gesture type of the event.
     *
     * Note that gesture group has to be determined before it is possible
     * to determine gesture type.
     *
     * @return Gesture type.
     */
    virtual TAknTouchGestureFwType Type() const = 0;

private:

    /**
     * Virtual method provided to allow extensibility.
     *
     * @param  aInterface  Extension UID.
     * @param  aParam      Parameter for the extension.
     *
     * @return KErrNotSupported as not currently implemented.
     */
    virtual TInt Extension( TUid aInterface, TAny* aParam ) = 0;
    };


/**
 * Tap gesture event.
 *
 * @lib akntouchgesturefw
 * @since S60 v5.2
 */
class MAknTouchGestureFwTapEvent : public MAknTouchGestureFwEvent
    {

public:

    /**
     * Target group.
     */
    enum { GROUP = EAknTouchGestureFwGroupTap };

    /**
     * Returns tap event position.
     *
     * @return Tap event position.
     */
    virtual TPoint Position() const = 0;
    };


/**
 * Drag gesture event.
 *
 * @lib akntouchgesturefw
 * @since S60 v5.2
 */
class MAknTouchGestureFwDragEvent : public MAknTouchGestureFwEvent
    {

public:

    /**
     * Target group.
     */
    enum { GROUP = EAknTouchGestureFwGroupDrag };

    /**
     * Gesture state of the event.
     *
     * State can be one of the following values:
     *     - EAknTouchGestureFwStart, sent at the beginning of the gesture.
     *     - EAknTouchGestureFwStop, sent at the end of the gesture.
     *     - EAknTouchGestureFwOn, sent during the gesture recognition.
     *
     * @return Gesture state.
     */
    virtual TAknTouchGestureFwState State() const = 0;

    /**
     * Returns drag event start position.
     *
     * @return Drag event start position.
     */
    virtual TPoint StartPosition() const = 0;

    /**
     * Returns current position in the drag event.
     *
     * @return Current position in the drag event.
     */
    virtual TPoint CurrentPosition() const = 0;

    /**
     * Returns previous position in the drag event.
     *
     * @return Previous position in the drag event.
     */
    virtual TPoint PreviousPosition() const = 0;
    };


/**
 * Flick gesture event.
 *
 * @lib akntouchgesturefw
 * @since S60 v5.2
 */
class MAknTouchGestureFwFlickEvent : public MAknTouchGestureFwEvent
    {

public:

    /**
     * Target group.
     */
    enum { GROUP = EAknTouchGestureFwGroupFlick };

    /**
     * Returns the flick position, which is the
     * position where pointer was released with speed.
     *
     * @return Flick position.
     */
    virtual TPoint Position() const = 0;

    /**
     * Flick speed in pixels per second.
     *
     * @return Flick speed.
     */
    virtual TPoint Speed() const = 0;
    };

/**
 * Pinch gesture event.
 *
 * @lib akntouchgesturefw
 * @since S60 v5.2
 */
class MAknTouchGestureFwPinchEvent : public MAknTouchGestureFwEvent
    {

public:

    /**
     * Target group.
     */
    enum { GROUP = EAknTouchGestureFwGroupPinch };

    /**
     * Returns the gesture state of the event.
     *
     * State can be one of the following values:
     *     - EAknTouchGestureFwStart, sent at the beginning of the gesture.
     *     - EAknTouchGestureFwStop, sent at the end of the gesture.
     *     - EAknTouchGestureFwOn, sent during the gesture recognition.
     *
     * @return Gesture state.
     */
    virtual TAknTouchGestureFwState State() const = 0;

    /**
     * Returns pinch movement value. This is delta value,
     * it's negative for pinch in and positive for pinch out.
     *
     * @return Pinch movement value.
     */
    virtual TInt Movement() const = 0;
    };

#include <akntouchgesturefw.inl>

} // namespace AknTouchGestureFw

#endif // C_AKNTOUCHGESTUREFWEVENTS_H
