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
* Description:  Touch gesture framework observer interface.
*
*/

#ifndef C_AKNTOUCHGESTUREFWOBSERVER_H
#define C_AKNTOUCHGESTUREFWOBSERVER_H

#include <e32std.h>

namespace AknTouchGestureFw
{

class MAknTouchGestureFwEvent;

/**
 * Touch gesture framework observer.
 *
 * Touch gesture framework notifies observer when user makes gestures in
 * the gesture control area. Observer class should implement this interface
 * and register itself to @c CAknTouchGestureFw in order to receive gesture
 * events. Gesture interest should also be set to enable correct gesture
 * event notifications.
 *
 * The sent events are of type @c MAknTouchGestureFwEvent. The event should be
 * casted according to event group before all data can be acquired.
 *
 * Example when observer is interested in drag and flick gestures:
 * @code
 * void CTouchGestureObserver::HandleTouchGestureL( MAknTouchGestureFwEvent& aEvent )
 *     {
 *     if ( ( MAknTouchGestureFwFlickEvent* flickEvent = AknTouchGestureFwEventFlick( aEvent ) ) )
 *         {
 *         ...
 *         }
 *     else if ( ( MAknTouchGestureFwDragEvent* dragEvent = AknTouchGestureFwEventDrag( aEvent ) ) )
 *         {
 *         ...
 *         }
 *     }
 * @endcode
 *
 * @lib akntouchgesturefw
 * @since S60 v5.2
 */
class MAknTouchGestureFwObserver
    {
public:

    /**
     * Handles the gesture event.
     * Do not start CActiveScheduler in this method implementation.
     *
     * @param  aEvent  Event describing the gesture.
     */
    virtual void HandleTouchGestureL( MAknTouchGestureFwEvent& aEvent ) = 0;
    };

} // namespace AknTouchGestureFw

#endif // C_AKNTOUCHGESTUREFWOBSERVER_H
