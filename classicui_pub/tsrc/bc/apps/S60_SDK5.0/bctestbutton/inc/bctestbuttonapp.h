/*
* Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
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









#ifndef C_BCTESTBUTTONAPP_H
#define C_BCTESTBUTTONAPP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
const TUid KUidBCTestButton = { 0x200089C2 }; // UID of the application.

// CLASS DECLARATION

/**
* CBCTestButtonApp application class.
* Provides factory to create concrete document object.
*/
class CBCTestButtonApp : public CAknApplication
    {
    private: // From CApaApplication

        /**
        * From CApaApplication, CreateDocumentL.
        * Creates CBCTestButtonDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();

        /**
        * From CApaApplication, AppDllUid.
        * Returns application's UID ( KUidBCTestButton ).
        * @return The value of KUidBCTestButton.
        */
        TUid AppDllUid() const;

    };

#endif

// End of File
