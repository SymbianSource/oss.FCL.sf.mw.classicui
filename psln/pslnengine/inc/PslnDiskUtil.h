/*
* Copyright (c) 2003-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Utility class for disk operations.
*
*/


#ifndef PSLNDISKUTIL_H
#define PSLNDISKUTIL_H

#include <e32std.h>
#include <f32file.h>

// Removable drive is write protected.
const TInt KPslnDiskUtilReadOnly = 1;

/**
* Static utility class for general disk-related operations in Psln.
*
* @since S60 v2.1
*/
NONSHARABLE_CLASS( PslnDiskUtil )
    {
    public:

        /**
        * Checks the status of the memory card.
        *
        * @return KErrNone if memory card is available and can be accessed.
        *   System-wide error code if an error occured.
        */
        static TInt MmcStatus();

        /**
        * Sets the given file as automated DRM content.
        * Uses DRM helper to display the query, if needed.
        *
        * @since 2.6
        *
        * @param aSkinSrvSession skin server session.
        * @param aFileName filename.
        * @return ETrue if can be automated, EFalse otherwise.
        */
        static TBool QueryAndSetAutomatedL(
            RAknsSrvSession& aSkinSrvSession,
            const TDesC& aFileName );

    private:

        /**
        * Static class can not be instantiated.
        */
        PslnDiskUtil();
        //lint -esym(1526,PslnDiskUtil::PslnDiskUtil) Intentionally undefined

        /**
        * Static class can not be instantiated.
        */
        ~PslnDiskUtil();

    };

#endif // PSLNDISKUTIL_H

// End of File
