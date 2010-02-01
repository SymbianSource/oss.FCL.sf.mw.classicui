/*
* Copyright (c) 2005, 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  File contains an interface for a touch pane observer.
*
*/



#ifndef AKNTOUCHPANEOBSERVER_H
#define AKNTOUCHPANEOBSERVER_H

// have been deprecated

// CLASS DECLARATION

/**
 * The MAknTouchPaneObserver interface allows a touch pane observer to pick up
 * changes in the size or position of the touch pane. Such events will be as a
 * result of layout changes which cause an actual change in the touch pane
 * rectangle.
 */
class MAknTouchPaneObserver
    {
    public:

        /**
        * Handles a change in the size or position of touch pane.
        * This function is called when touch pane changes its size or position.
        */
        virtual void HandleTouchPaneSizeChange() = 0;

    };

#endif // AKNTOUCHPANEOBSERVER_H

// End of file

