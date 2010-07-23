/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:
*
*/


#if !defined(__EIKSBOBS_H__)
#define __EIKSBOBS_H__

/**
 *
 * Scroll bar events enumerations 
 *
 * Touch events for scroll bar. Reported to scroll bar observer through 
 * HandleScrollEventL method.
 *
 *  @since S60 0.9
 */
enum TEikScrollEvent
    {
    EEikScrollLeft=1, /** stulys was tapped on the left arrow of the scroll bar */
    EEikScrollUp, /** stulys was tapped on the up arrow of the scroll bar */
    EEikScrollRight, /** stulys was tapped on the right arrow of the scroll bar */
    EEikScrollDown, /** stulys was tapped on the down arrow of the scroll bar */
    EEikScrollPageLeft, /** stulys was tapped on left side of the scroll bar */
    EEikScrollPageUp, /** stulys was tapped above the scroll bar */
    EEikScrollPageRight, /** stulys was tapped on right side of the scroll bar */
    EEikScrollPageDown, /** stulys was tapped below the scroll bar */
    EEikScrollHome, /** @deprecated */
    EEikScrollTop, /** @deprecated */
    EEikScrollEnd, /** @deprecated */
    EEikScrollBottom, /** @deprecated */
    EEikScrollThumbDragHoriz, /** stulys is down on scroll bar thumb and dragged */
    EEikScrollThumbDragVert, /** stulys is down on scroll bar thumb and dragged */
    EEikScrollThumbReleaseHoriz, /** scrollbar thumb drag is stopped */
    EEikScrollThumbReleaseVert /** scrollbar thumb drag is stopped */
    };

class CEikScrollBar;

/**
 * Scroll bar observer interface
 *
 * Scroll bar clients can registers itself to observe scroll bar events. 
 * The scroll bar sends an event to the observer every time a touch event 
 * happens for the scroll bar.
 *
 * Clients should derive from MEikScrollBarObserver interface to get scroll bar events. 
 *
 *  @lib eikcoctl.lib
 *  @since S60 0.9
 */

class MEikScrollBarObserver
    {
public:

    /**
     * Callback method for scroll bar events
     *
     * Scroll bar observer should implement this method to get scroll bar events.
     *
     * @since S60 0.9
     * @param aScrollBar A pointer to scrollbar which created the event
     * @param aEventType The event occured on the scroll bar
     */
    virtual void HandleScrollEventL(CEikScrollBar* aScrollBar, TEikScrollEvent aEventType)=0;
    };

#endif // __EIKSBOBS_H__
