/*
* Copyright (c) 2002-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Observer interface for reporting events.
*
*/


#ifndef MAKNCOMMONDIALOGSEVENTOBSERVER_H
#define MAKNCOMMONDIALOGSEVENTOBSERVER_H

// INCLUDES
#include <e32def.h>

// FORWARD DECLARATIONS
class CEikButtonGroupContainer;

//  CLASS DEFINITION
/**
*  An observer class which provides an interface for reporting events.
*
*  @lib CommonDialogs.lib
*  @since 1.2
*/
class MAknCommonDialogsEventObserver
    {
    public:     // Enumerations

        /**
        * Enumerations of actions that are returned to the caller of the observer.
        */
        enum TAction
            {
            ETryingToExit,
            EItemsUpdated,
            ELaunchEmptyPopup,
            EDidNothing,
            ECanceled
            };

        /**
        * Enumerations of events that are reported to the observer.
        */
        enum TEvent
            {
            ELeftSoftkeyPress,
            ERightSoftkeyPress,
            ESelectionKeyPress,
            EFocusChange,
            EEventClicked,
            ECancelAllActions
            };

    public:     // New functions

        /**
        * A pure virtual method that is meant to handle events.
        * @param aEvent Type of the event.
        * @param aFocusedItemIndex A reference to index of the currently
        *        selected item.
        * @param aTopItemIndex A reference to index of the first visible item
        *        in listbox.
        * @param aContainer A pointer to a button group container.
        * @return Returns the action that the ui class should do.
        */
        virtual TAction HandleEventL(
            TEvent aEvent,
            TInt& aFocusedItemIndex,
            TInt& aTopItemIndex,
            CEikButtonGroupContainer* aContainer ) = 0;
    };

#endif // MAKNCOMMONDIALOGSEVENTOBSERVER_H

// End of File
