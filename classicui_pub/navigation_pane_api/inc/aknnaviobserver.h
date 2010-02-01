/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
*
*/

// AKNNAVIOBSERVER.H
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#if !defined(__AKNNAVIOBSERVER_H__)
#define __AKNNAVIOBSERVER_H__

class MAknNavigationObserver
    {
public:
    enum TAknNavigationEvent
        {
        /** Current tab index has changed */
        ENaviEventHandleNavigation = 0x0010,
        /** Current tab is the rightmost tab */
        ENaviEventLeftMostItemReached,
        /** Current tab is the leftmost tab */
        ENaviEventRightMostItemReached,
        /** Only one tab */
        ENaviEventOneItemExists,
        /** Draw tabs again */
        ENaviEventRedrawNeeded,
        /** Current tab is leftmost, but tried to move left */
        ENaviEventAlreadyLeftmostItem,
        /** Current tab is rightmost, but tried to move right */
        ENaviEventAlreadyRightmostItem
        };
    };

#endif // __AKNNAVIOBSERVER_H__
