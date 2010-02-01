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
* Description:  Concrete touch gesture event classes.
*
*/

#ifndef T_AKNTOUCHGESTUREFWEVENT_H
#define T_AKNTOUCHGESTUREFWEVENT_H

#include <akntouchgesturefwevents.h>

namespace AknTouchGestureFw {

/**
 *  Unknown touch gesture event class.
 */
NONSHARABLE_CLASS( TAknTouchGestureFwUnknownEvent )
    : public MAknTouchGestureFwEvent
    {

public: // From base class MAknTouchGestureFwEvent.

    /**
     * Returns the gesture group of the event.
     *
     * @return EAknTouchGestureFwNoGroup
     */
    TAknTouchGestureFwGroup Group() const;

    /**
     * Returns the gesture type of the event.
     *
     * @return EAknTouchGestureFwUnknown
     */
    TAknTouchGestureFwType Type() const;

private: // From base class MAknTouchGestureFwEvent.

    /**
     * Virtual method provided to allow extensibility.
     *
     * @param  aInterface  Extension UID.
     * @param  aParam      Parameter for the extension.
     *
     * @return KErrNotSupported as not currently implemented.
     */
    TInt Extension( TUid aInterface, TAny* aParam );
    };


/**
 *  Tap touch gesture event class.
 */
NONSHARABLE_CLASS( TAknTouchGestureFwTapEvent )
    : public MAknTouchGestureFwTapEvent
    {

public:

    /**
     * Sets the tap type.
     *
     * @param  aType  Type of the tap gesture.
     */
    void SetType( const TAknTouchGestureFwType aType );

    /**
     * Sets the tap position.
     *
     * @param  aPosition  The position at which the tap was received.
     */
    void SetPosition( const TPoint& aPosition );

public: // From base class MAknTouchGestureFwTapEvent.

    /**
     * Returns the gesture group of the event.
     *
     * @return EAknTouchGestureFwGroupTap
     */
    TAknTouchGestureFwGroup Group() const;

    /**
     * Returns the gesture type of the event.
     *
     * @return Gesture type.
     */
    TAknTouchGestureFwType Type() const;

    /**
     * Returns the tap event position.
     *
     * @return Tap event position.
     */
    TPoint Position() const;

private: // From base class MAknTouchGestureFwTapEvent.

    /**
     * Virtual method provided to allow extensibility.
     *
     * @param  aInterface  Extension UID.
     * @param  aParam      Parameter for the extension.
     *
     * @return KErrNotSupported as not currently implemented.
     */
    TInt Extension( TUid aInterface, TAny* aParam );

private:

    /**
     * Gesture type.
     */
    TAknTouchGestureFwType iType;

    /**
     * Tap position.
     */
    TPoint iPosition;
    };


/**
 *  Drag touch gesture event class.
 */
NONSHARABLE_CLASS( TAknTouchGestureFwDragEvent )
    : public MAknTouchGestureFwDragEvent
    {

public:

    /**
     * Sets the state of the drag gesture.
     *
     * @param  aState  State of the drag gesture.
     */
    void SetState( TAknTouchGestureFwState aState );

    /**
     * Sets the drag start position.
     *
     * @param  aStartPosition  Start position of the drag gesture.
     */
    void SetStartPosition( const TPoint& aStartPosition );

    /**
     * Sets the current position of the drag gesture.
     *
     * @param  aCurrentPosition  Current position in the drag gesture.
     */
    void SetCurrentPosition( const TPoint& aCurrentPosition );

    /**
     * Sets previous position of the drag gesture.
     *
     * @param  aPreviousPosition  Previous position in the drag gesture.
     */
    void SetPreviousPosition( const TPoint& aPreviousPosition );

public: // From base class MAknTouchGestureFwDragEvent.

    /**
     * Returns the gesture group of the event.
     *
     * @return EAknTouchGestureFwGroupDrag
     */
    TAknTouchGestureFwGroup Group() const;

    /**
     * Returns the gesture type of the event.
     *
     * @return EAknTouchGestureFwDrag
     */
    TAknTouchGestureFwType Type() const;

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
    TAknTouchGestureFwState State() const;

    /**
     * Returns the drag event start position.
     *
     * @return Drag event start position.
     */
    TPoint StartPosition() const;

    /**
     * Returns the drag event current position.
     *
     * @return Drag event current position.
     */
    TPoint CurrentPosition() const;

    /**
     * Returns the drag event previous position.
     *
     * @return Drag event previous position.
     */
    TPoint PreviousPosition() const;

private: // From base class MAknTouchGestureFwDragEvent.

    /**
     * Virtual method provided to allow extensibility.
     *
     * @param  aInterface  Extension UID.
     * @param  aParam      Parameter for the extension.
     *
     * @return KErrNotSupported as not currently implemented.
     */
    TInt Extension( TUid aInterface, TAny* aParam );

private:

    /**
     * Gesture state.
     */
    TAknTouchGestureFwState iState;

    /**
     * Drag start position.
     */
    TPoint iStartPosition;

    /**
     * Drag current position.
     */
    TPoint iCurrentPosition;

    /**
     * Drag previous position.
     */
    TPoint iPreviousPosition;
    };


/**
 *  Flick touch gesture event class.
 */
NONSHARABLE_CLASS( TAknTouchGestureFwFlickEvent )
    : public MAknTouchGestureFwFlickEvent
    {

public:

    /**
     * Sets the flick type.
     *
     * @param  aType  Type of the flick gesture.
     */
    void SetType( TAknTouchGestureFwType aType );

    /**
     * Sets the flick position.
     *
     * @param  aFlickPosition  Position of the flick.
     */
    void SetPosition( const TPoint& aFlickPosition );

    /**
     * Sets the flick speed.
     *
     * @param  aSpeed  Speed of the flick.
     */
    void SetSpeed( const TPoint& aSpeed );

public: // From base class MAknTouchGestureFwFlickEvent.

    /**
     * Returns the gesture group of the event.
     *
     * @return EAknTouchGestureFwGroupFlick
     */
    TAknTouchGestureFwGroup Group() const;

    /**
     * Returns the gesture type of the event.
     *
     * @return Gesture type.
     */
    TAknTouchGestureFwType Type() const;

    /**
     * Returns the flick position, which is the
     * position where pointer was released with speed.
     *
     * @return Flick position.
     */
    TPoint Position() const;

    /**
     * Flick speed in pixels per second.
     *
     * @return Flick speed.
     */
    TPoint Speed() const;

private: // From base class MAknTouchGestureFwFlickEvent.

    /**
     * Virtual method provided to allow extensibility.
     *
     * @param  aInterface  Extension UID.
     * @param  aParam      Parameter for the extension.
     *
     * @return KErrNotSupported as not currently implemented.
     */
    TInt Extension( TUid aInterface, TAny* aParam );

private:

    /**
     * Gesture type.
     */
    TAknTouchGestureFwType iType;

    /**
     * Flick position.
     */
    TPoint iFlickPosition;

    /**
     * Flick speed.
     */
    TPoint iSpeed;
    };


/**
 *  Pinch touch gesture event class.
 */
NONSHARABLE_CLASS( TAknTouchGestureFwPinchEvent )
    : public MAknTouchGestureFwPinchEvent
    {

public:

    /**
     * Sets the pinch state.
     *
     * @param  aState  State of the pinch gesture.
     */
    void SetState( TAknTouchGestureFwState aState );

    /**
     * Sets the pinch movement.
     *
     * @param  aMovement  The pinch movement in percents.
     */
    void SetMovement( TInt aMovement );

public: // From base class MAknTouchGestureFwPinchEvent.

    /**
     * Returns the gesture group of the event.
     *
     * @return EAknTouchGestureFwGroupPinch
     */
    TAknTouchGestureFwGroup Group() const;

    /**
     * Returns the gesture type of the event.
     *
     * @return EAknTouchGestureFwPinch
     */
    TAknTouchGestureFwType Type() const;

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
    TAknTouchGestureFwState State() const;

    /**
     * Returns pinch percent value, range is non-negative.
     *
     * @return Pinch percent value.
     */
    TInt Movement() const;

private: // From base class MAknTouchGestureFwPinchEvent.

    /**
     * Virtual method provided to allow extensibility.
     *
     * @param  aInterface  Extension UID.
     * @param  aParam      Parameter for the extension.
     *
     * @return KErrNotSupported as not currently implemented.
     */
    TInt Extension( TUid aInterface, TAny* aParam );

private:

    /**
     * Pinch state.
     */
    TAknTouchGestureFwState iState;

    /**
     * Pinch movement.
     */
    TInt iMovement;
    };

} // namespace AknTouchGestureFw

#endif // T_AKNTOUCHGESTUREFWEVENT_H

// End of File
