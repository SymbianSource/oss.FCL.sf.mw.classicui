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

#include "akntouchgesturefwevent.h"

using namespace AknTouchGestureFw;

// ======== MEMBER FUNCTIONS ========


// ---------------------------------------------------------------------------
// Returns the gesture group.
// ---------------------------------------------------------------------------
//
TAknTouchGestureFwGroup TAknTouchGestureFwUnknownEvent::Group() const
    {
    return EAknTouchGestureFwNoGroup;
    }


// ---------------------------------------------------------------------------
// Returns the gesture type.
// ---------------------------------------------------------------------------
//
TAknTouchGestureFwType TAknTouchGestureFwUnknownEvent::Type() const
    {
    return EAknTouchGestureFwUnknown;
    }


// ---------------------------------------------------------------------------
// Virtual method provided to allow extensibility.
// ---------------------------------------------------------------------------
//
TInt TAknTouchGestureFwUnknownEvent::Extension( TUid /*aInterface*/,
                                                TAny* /*aParam*/ )
    {
    return KErrNotSupported;
    }


// ---------------------------------------------------------------------------
// Sets the type of the tap gesture.
// ---------------------------------------------------------------------------
//
void TAknTouchGestureFwTapEvent::SetType( TAknTouchGestureFwType aType )
    {
    iType = aType;
    }


// ---------------------------------------------------------------------------
// Sets the position of the tap.
// ---------------------------------------------------------------------------
//
void TAknTouchGestureFwTapEvent::SetPosition( const TPoint& aPosition )
    {
    iPosition = aPosition;
    }


// ---------------------------------------------------------------------------
// Returns the gesture group.
// ---------------------------------------------------------------------------
//
TAknTouchGestureFwGroup TAknTouchGestureFwTapEvent::Group() const
    {
    return EAknTouchGestureFwGroupTap;
    }


// ---------------------------------------------------------------------------
// Returns the gesture type.
// ---------------------------------------------------------------------------
//
TAknTouchGestureFwType TAknTouchGestureFwTapEvent::Type() const
    {
    return iType;
    }


// ---------------------------------------------------------------------------
// Virtual method provided to allow extensibility.
// ---------------------------------------------------------------------------
//
TInt TAknTouchGestureFwTapEvent::Extension( TUid /*aInterface*/,
                                            TAny* /*aParam*/ )
    {
    return KErrNotSupported;
    }


// ---------------------------------------------------------------------------
// Returns the tap position.
// ---------------------------------------------------------------------------
//
TPoint TAknTouchGestureFwTapEvent::Position() const
    {
    return iPosition;
    }


// ---------------------------------------------------------------------------
// Sets the gesture state.
// ---------------------------------------------------------------------------
//
void TAknTouchGestureFwDragEvent::SetState( TAknTouchGestureFwState aState )
    {
    iState = aState;
    }


// ---------------------------------------------------------------------------
// Sets the start position of the drag.
// ---------------------------------------------------------------------------
//
void TAknTouchGestureFwDragEvent::SetStartPosition(
    const TPoint& aStartPosition )
    {
    iStartPosition = aStartPosition;
    }


// ---------------------------------------------------------------------------
// Sets the current position of the drag.
// ---------------------------------------------------------------------------
//
void TAknTouchGestureFwDragEvent::SetCurrentPosition(
    const TPoint& aCurrentPosition )
    {
    iCurrentPosition = aCurrentPosition;
    }


// ---------------------------------------------------------------------------
// Sets the previous position of the drag.
// ---------------------------------------------------------------------------
//
void TAknTouchGestureFwDragEvent::SetPreviousPosition(
    const TPoint& aPreviousPosition )
    {
    iPreviousPosition = aPreviousPosition;
    }


// ---------------------------------------------------------------------------
// Returns the gesture group.
// ---------------------------------------------------------------------------
//
TAknTouchGestureFwGroup TAknTouchGestureFwDragEvent::Group() const
    {
    return EAknTouchGestureFwGroupDrag;
    }


// ---------------------------------------------------------------------------
// Returns the gesture type.
// ---------------------------------------------------------------------------
//
TAknTouchGestureFwType TAknTouchGestureFwDragEvent::Type() const
    {
    return EAknTouchGestureFwDrag;
    }


// ---------------------------------------------------------------------------
// Returns the gesture state.
// ---------------------------------------------------------------------------
//
TAknTouchGestureFwState TAknTouchGestureFwDragEvent::State() const
    {
    return iState;
    }


// ---------------------------------------------------------------------------
// Virtual method provided to allow extensibility.
// ---------------------------------------------------------------------------
//
TInt TAknTouchGestureFwDragEvent::Extension( TUid /*aInterface*/,
                                             TAny* /*aParam*/ )
    {
    return KErrNotSupported;
    }


// ---------------------------------------------------------------------------
// Returns the start position of the drag.
// ---------------------------------------------------------------------------
//
TPoint TAknTouchGestureFwDragEvent::StartPosition() const
    {
    return iStartPosition;
    }


// ---------------------------------------------------------------------------
// Returns the current position of the drag.
// ---------------------------------------------------------------------------
//
TPoint TAknTouchGestureFwDragEvent::CurrentPosition() const
    {
    return iCurrentPosition;
    }


// ---------------------------------------------------------------------------
// Returns the previous position of the drag.
// ---------------------------------------------------------------------------
//
TPoint TAknTouchGestureFwDragEvent::PreviousPosition() const
    {
    return iPreviousPosition;
    }


// ---------------------------------------------------------------------------
// Sets the flick gesture type.
// ---------------------------------------------------------------------------
//
void TAknTouchGestureFwFlickEvent::SetType( TAknTouchGestureFwType aType )
    {
    iType = aType;
    }


// ---------------------------------------------------------------------------
// Sets the flick position.
// ---------------------------------------------------------------------------
//
void TAknTouchGestureFwFlickEvent::SetPosition( const TPoint& aFlickPosition )
    {
    iFlickPosition = aFlickPosition;
    }


// ---------------------------------------------------------------------------
// Sets the flick speed.
// ---------------------------------------------------------------------------
//
void TAknTouchGestureFwFlickEvent::SetSpeed( const TPoint& aSpeed )
    {
    iSpeed = aSpeed;
    }


// ---------------------------------------------------------------------------
// Returns the gesture group.
// ---------------------------------------------------------------------------
//
TAknTouchGestureFwGroup TAknTouchGestureFwFlickEvent::Group() const
    {
    return EAknTouchGestureFwGroupFlick;
    }


// ---------------------------------------------------------------------------
// Returns the gesture type.
// ---------------------------------------------------------------------------
//
TAknTouchGestureFwType TAknTouchGestureFwFlickEvent::Type() const
    {
    return iType;
    }


// ---------------------------------------------------------------------------
// Virtual method provided to allow extensibility.
// ---------------------------------------------------------------------------
//
TInt TAknTouchGestureFwFlickEvent::Extension( TUid /*aInterface*/,
                                              TAny* /*aParam*/ )
    {
    return KErrNotSupported;
    }


// ---------------------------------------------------------------------------
// Returns the flick position.
// ---------------------------------------------------------------------------
//
TPoint TAknTouchGestureFwFlickEvent::Position() const
    {
    return iFlickPosition;
    }


// ---------------------------------------------------------------------------
// Returns the flick speed.
// ---------------------------------------------------------------------------
//
TPoint TAknTouchGestureFwFlickEvent::Speed() const
    {
    return iSpeed;
    }


// ---------------------------------------------------------------------------
// Sets the pinch gesture state.
// ---------------------------------------------------------------------------
//
void TAknTouchGestureFwPinchEvent::SetState( TAknTouchGestureFwState aState )
    {
    iState = aState;
    }


// ---------------------------------------------------------------------------
// Sets the pinch movement.
// ---------------------------------------------------------------------------
//
void TAknTouchGestureFwPinchEvent::SetMovement( TInt aMovement )
    {
    iMovement = aMovement;
    }


// ---------------------------------------------------------------------------
// Returns the gesture group.
// ---------------------------------------------------------------------------
//
TAknTouchGestureFwGroup TAknTouchGestureFwPinchEvent::Group() const
    {
    return EAknTouchGestureFwGroupPinch;
    }


// ---------------------------------------------------------------------------
// Returns the gesture type.
// ---------------------------------------------------------------------------
//
TAknTouchGestureFwType TAknTouchGestureFwPinchEvent::Type() const
    {
    return EAknTouchGestureFwPinch;
    }


// ---------------------------------------------------------------------------
// Returns the gesture state.
// ---------------------------------------------------------------------------
//
TAknTouchGestureFwState TAknTouchGestureFwPinchEvent::State() const
    {
    return iState;
    }


// ---------------------------------------------------------------------------
// Virtual method provided to allow extensibility.
// ---------------------------------------------------------------------------
//
TInt TAknTouchGestureFwPinchEvent::Extension( TUid /*aInterface*/,
                                              TAny* /*aParam*/ )
    {
    return KErrNotSupported;
    }


// ---------------------------------------------------------------------------
// Returns the pinch movement.
// ---------------------------------------------------------------------------
//
TInt TAknTouchGestureFwPinchEvent::Movement() const
    {
    return iMovement;
    }

// End of File
