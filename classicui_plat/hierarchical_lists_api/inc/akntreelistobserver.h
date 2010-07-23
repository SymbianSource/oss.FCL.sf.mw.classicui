/*
* Copyright (c) 2006, 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Observer interface for hierarchical list.
*
*/


#ifndef M_AKNTREELISTOBSERVER_H
#define M_AKNTREELISTOBSERVER_H


#include <akntreelistconstants.h>

class CAknTreeList;


/**
 *  Observer interface for hierarchical list.
 *
 *  Notifications of common hierarhicial list events are sent to the 
 *  list client through this interface. All hierarhical list clients must
 *  provide an implementation for the interface and then register it with
 *  @c CAknTreeList::AddObserverL() method.
 *
 *  List specializations can also provide extended observer interfaces derived
 *  from this interface, if this interface is not sufficient for the usage of
 *  some hierarhical list specialization.
 *
 *  @since S60 v3.2
 */
class MAknTreeListObserver
    {

public:

    /**
     * Hierarchical list events. These events are sent to hierarchical list
     * observer with @c HandleTreeListEvent() method.
     */
    enum TEvent
        {
        /** Node is being expanded. At this point the list client should
            update the content of expanded node, or add the content, if it
            has not been added or was removed when the node was collapsed. */
        ENodeExpanded,
        /** Node is being collapsed. This event is sent before a node is
            collapsed. After the event, all the content of the node is deleted
            unless it has been set persistent. */
        ENodeCollapsed,
        /** Focused item is changed. This event indicates that the focus is
            moved to another list item. The client can use this information,
            for example, for showing some additional information about the
            focused item. */
        EItemFocused,
        /** Item is selected. This event indicates that the focused item is
            selected with some key or pointer event. The client should respond
            to selection event, for example, by opening the selected item. */
        EItemSelected,
        /** Item was removed from the list. The specified item ID is no
            longer usable. */
        EItemRemoved,
        /** Marking mode enabled. This event is used for notifying the client
            that markable list has entered marking mode as a result of user
            keeping shift, control, edit, or hash key pressed. During marking
            mode, the list controls the MSK key, and to ensure proper MSK
            functionality, the client should not change MSK content. */
        EMarkingModeEnabled,
        /** Marking mode disabled. This event is sent when markable list
            exits the marking mode. After this, the list no longer controls
            the MSK key. */
        EMarkingModeDisabled,
        /** Item has been marked. This event is sent when either a node or
            a leaf has been marked. Note that when marked item is a node,
            its content is also set marked, but separate events are not
            sent for all of the marked descendants. */
        EItemMarked,
        /** Item has been unmarked. This event is sent when either a node or
            a leaf has been unmarked. Note that when unmarked item is a node,
            its content is also set unmarked, but separate events are not
            sent for all of the unmarked descendants. */
        EItemUnmarked,
        /** Panning is started. @ aItem in @c HandleTreeListEvent() 
         *  is @ KAknTreeIIDNone in this case.
         */
        EEventPanningStarted,
        /** Panning is stopeed. @ aItem in @c HandleTreeListEvent() 
         *  is @ KAknTreeIIDNone in this case.
         */
        EEventPanningStopped,
        /** Flick is started. @ aItem in @c HandleTreeListEvent() 
         *  is @ KAknTreeIIDNone in this case.
         */
        EEventFlickStarted,
        /** Flick is stopped. @ aItem in @c HandleTreeListEvent() 
         *  is @ KAknTreeIIDNone in this case.
         */
        EEventFlickStopped,
        /** Empty list clicked. This event is sent when completely empty list 
            is clicked */        
        EEmptyListClicked,
        /** Empty area clicked. This event is sent when empty area of a non-
            empty list is clicked. */        
        EEmptyAreaClicked        
        };

    /**
     * The list client is notified of hierarchical list events with this
     * method. Hierarchical list instance, item ID of the referred list item,
     * and the event code are sent to the client.
     *
     * Note: New events may be added to the @c MAknTreeListObserver::TEvent
     * enumeration in the future, and it should be taken in account in the
     * implementations of this method, and not, for example, panic when
     * receiving some currently unspecified event.
     *
     * @param aList The hierarchical list from where the event is originated.
     *
     * @param aItem Item ID of the list item the event is referring to.
     *
     * @param aEvent The hierarchical list event.
     *
     * @return Return value currently not used, value @c KErrNone should
     *      be used.
     */
    virtual TInt HandleTreeListEvent( CAknTreeList& aList,
        TAknTreeItemID aItem, TEvent aEvent ) = 0;

    };


#endif // M_AKNTREELISTOBSERVER_H
