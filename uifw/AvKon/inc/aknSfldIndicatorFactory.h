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


#ifndef __AknSearchFieldIndicatorFactory_H__
#define __AknSearchFieldIndicatorFactory_H__

// INCLUDES
#include <e32base.h>

// FORWARD DECLARATIONS
class CAknSearchFieldIndicator;

/**
 * The CAknSearchFieldIndicator class implements the search mode
 * indicators used in Chinese find.
 * ONLY for internal use of CAknSearchField.
 */
class AknSearchFieldIndicatorFactory
    {
    public:     // constructors and destructor

        /**
        * Factory function for search field indicator
        *
        * @return In Apac variant, new CAknSearchFieldIndicator object
        *         In Elaf variant, NULL
        */
        static CAknSearchFieldIndicator* CreateIndicatorL();

    private:

        AknSearchFieldIndicatorFactory();
    };

#endif // __AknSearchFieldIndicatorFactory_H__
