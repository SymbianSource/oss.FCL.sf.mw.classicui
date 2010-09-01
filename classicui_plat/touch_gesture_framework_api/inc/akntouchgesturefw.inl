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
* Description:  Touch gesture framework inline functions.
*
*/

/**
 * Renamed event casting methods.
 *
 * Usage example:
 * if ( aEvent->GestureGroup == EAknTouchGestureFwGroupTap )
 *     {
 *     MAknTouchGestureFwTapEvent* tapEvent =
 *         AknTouchGestureFwEventTap( aEvent );
 *     ...
 *     }
 */
#define AknTouchGestureFwEventTap                       \
    AknTouchGestureFwEvent<MAknTouchGestureFwTapEvent>
#define AknTouchGestureFwEventDrag                      \
    AknTouchGestureFwEvent<MAknTouchGestureFwDragEvent>
#define AknTouchGestureFwEventFlick                     \
    AknTouchGestureFwEvent<MAknTouchGestureFwFlickEvent>
#define AknTouchGestureFwEventPinch                     \
    AknTouchGestureFwEvent<MAknTouchGestureFwPinchEvent>

/**
 * Help method for event casting.
 *
 * @since S60 v5.2
 * @param aEvent Gesture event.
 */
template <class Target>
inline Target* AknTouchGestureFwEvent( MAknTouchGestureFwEvent& aEvent )
    {
    return ( aEvent.Group() == Target::GROUP ) ?
        static_cast<Target*>( &aEvent ) : NULL;
    }
