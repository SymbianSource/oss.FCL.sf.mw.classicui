/*
* Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
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


#if !defined(__EIKLBO_H__)
#define __EIKLBO_H__

class CEikListBox; 

/**
* List box observer interface.
*
* Each list box observer may be registered with a number of list
* boxes; each of these send events to the list box observer through
* its HandeListBoxEventL() method.
*
* Writing derived classes: 
*
* Application authors should implement a class which derives from this
* interface to receive events from list boxes
*/
class MEikListBoxObserver
    {
    public:

        /**
        * List box event codes
        */
        enum TListBoxEvent
            {
            /**  Keypress event. */
            EEventEnterKeyPressed,
            /**  Item single-tap event */
            EEventItemClicked,
            /**  Item two-taps event. */
            EEventItemDoubleClicked,
            /**  Special event: reported by directory tree and directory contents list boxes. */
            EEventItemActioned,
            /**  Editing started. */
            EEventEditingStarted,
            /**  Editing stopped. */
            EEventEditingStopped,
            /**  Pen is down and over an item */
            EEventPenDownOnItem,
            /**  Pen is dragged from item to another */
            EEventItemDraggingActioned,
            /**  Panning is started */
            EEventPanningStarted,
            /**  Panning is stopped */
            EEventPanningStopped,
            /**  Flick is started */
            EEventFlickStarted,
            /**  Flick is stopped */
            EEventFlickStopped,
            /**  Item single-tap event. This event should be used
             by applications that are single click compatible. */
            EEventItemSingleClicked,
			/**  An empty listbox was clicked */
            EEventEmptyListClicked,
            /**  An empty area of non-empty listbox was clicked */
            EEventEmptyAreaClicked         
            };

    public:
        /**
        * Handles list box events.
        *
        * This pure virtual function is invoked by CEikListBox to
        * notify the observer of list box events.
        *
        * @param aListBox   The originating list box.
        * @param aEventType A code for the event. Further information 
        *                   may be obtained by accessing the list box itself.
        */
        virtual void HandleListBoxEventL(CEikListBox* aListBox, TListBoxEvent aEventType)=0;
    };

#endif
