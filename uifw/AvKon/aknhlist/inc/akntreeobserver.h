/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Observer interface for the tree structure.
*
*/


#ifndef M_AKNTREEOBSERVER_H
#define M_AKNTREEOBSERVER_H


class CAknTree;
class CAknTreeItem;


/**
 *  Observer interface for the tree structure.
 *
 *  Observers of the tree are notified of changes in the tree structure
 *  through this interface with appropriate events.
 *
 *  @lib aknhlist.lib
 *  @since S60 v3.2
 */
class MAknTreeObserver
    {

public:

    /**  Tree events. */
    enum TEvent
        {
        /** New item is added to the tree. */
        EItemAdded,
        /** Item is moved to another location in tree. */
        EItemMoved,
        /** Item is about to be removed from the tree. Observers are notified
            with this event before the item is removed. */
        EItemRemoveBegin,
        /** Item is removed from the tree. */
        EItemRemoveEnd,
        /** Tree node is expanded. */
        ENodeExpanded,
        /** Tree node is collapsed. */
        ENodeCollapsed,
        /** Content of a item is changed (item need to be redrawn if visible). */
        EItemModified,
        /** Tree has been sorted. */
        ETreeSorted
        };

    /**
     * Notification of a tree event. The event is specified as a parameter.
     *
     * @param aEvent Tree event.
     *
     * @param aItem Pointer to the tree item that is concerned by the event.
     *
     * @param aDrawNow @c ETrue, if the view should be redrawn after the
     *      event.
     */
    virtual void HandleTreeEvent( TEvent aEvent, CAknTreeItem* aItem,
        TBool aDrawNow ) = 0;

    };


#endif // M_AKNTREEOBSERVER_H
