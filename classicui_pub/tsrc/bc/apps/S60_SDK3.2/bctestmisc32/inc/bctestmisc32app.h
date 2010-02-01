/*
* Copyright (c) 3232 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         Declares main application class.
*
*/









#ifndef C_BCTESTMISC32APP_H
#define C_BCTESTMISC32APP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
const TUid KUidBCTestmisc32 = { 0xA00040AA }; // UID of the application.

// CLASS DECLARATION

/**
* CBCTestmisc32App application class.
* Provides factory to create concrete document object.
*/
class CBCTestmisc32App : public CAknApplication
    {
    private: // From CApaApplication

        /**
        * From CApaApplication, CreateDocumentL.
        * Creates CBCTestmisc32Document document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();

        /**
        * From CApaApplication, AppDllUid.
        * Returns application's UID ( KUidBCTestmisc32 ).
        * @return The value of KUidBCTestmisc32.
        */
        TUid AppDllUid() const;

    };

#endif   //C_BCTESTMISC32APP_H

// End of File
