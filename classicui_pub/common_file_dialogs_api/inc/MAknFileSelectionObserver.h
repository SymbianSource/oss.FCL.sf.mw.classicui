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
* Description:  Observer interface for file selection.
*
*/


#ifndef MAKNFILESELECTIONOBSERVER_H
#define MAKNFILESELECTIONOBSERVER_H

// INCLUDES
#include <e32std.h>

// FORWARD DECLARATIONS
class TEntry;

//  CLASS DEFINITION
/**
*  Observer class that can be set to observe if selected item
*  e.g. has correct size or date before letting dialog exit.
*
*  @lib CommonDialogs.lib
*  @since 1.2
*/
class MAknFileSelectionObserver
    {
    public:     // Constructors and destructor

        /**
        * A virtual destructor to ensure that correct destructor gets called.
        * Must have an empty implementation.
        */
        virtual ~MAknFileSelectionObserver() { };

    public:     // New functions

        /**
        * Get's called when user selects an file.
        * @param aDriveAndPath Drive and full path of the file.
        * @param aEntry An entry containing all information of selected item.
        * @return Returns ETrue if it is ok to exit from dialog.
        */
        virtual TBool OkToExitL( const TDesC& aDriveAndPath, const TEntry& aEntry ) = 0;
    };

#endif // MAKNFILESELECTIONOBSERVER_H

// End of File
