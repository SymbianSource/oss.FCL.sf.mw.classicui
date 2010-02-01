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
* Description:  Filter interface for file selection.
*
*/


#ifndef MAKNFILEFILTER_H
#define MAKNFILEFILTER_H

// INCLUDES
#include <e32def.h> // TBool

// FORWARD DECLARATIONS
class TEntry;

//  CLASS DEFINITION
/**
*  An abstract interface class for filters.
*
*  @lib CommonDialogs.lib
*  @since 1.2
*/
class MAknFileFilter
    {
    public:     // Constructors and destructors
        /**
        * A virtual destructor to ensure that correct destructor gets called.
        * Must have an empty implementation.
        */
        virtual ~MAknFileFilter() { };

    public:
        /**
        * Checks if a file is accepted by the filter.
        * @param aDriveAndPath Drive and full path of the file.
        * @param aEntry A directory entry.
        * @return Returns ETrue if filter accepts the file.
        */
        virtual TBool Accept( const TDesC& aDriveAndPath, const TEntry& aEntry ) const = 0;

    };

#endif // MAKNFILEFILTER_H

// End of File
