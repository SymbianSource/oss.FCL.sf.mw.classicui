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









#ifndef BCTestTEMPLATEAPP_H
#define BCTestTEMPLATEAPP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
const TUid KUidBCTestFontInput = { 0x20004766 }; // UID of the application.

// CLASS DECLARATION

/**
* CBCTestFontInputApp application class.
* Provides factory to create concrete document object.
*/
class CBCTestFontInputApp : public CAknApplication
    {
    private: // From CApaApplication

        /**
        * From CApaApplication, CreateDocumentL.
        * Creates CBCTestFontInputDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();

        /**
        * From CApaApplication, AppDllUid.
        * Returns application's UID ( KUidBCTestFontInput ).
        * @return The value of KUidBCTestFontInput.
        */
        TUid AppDllUid() const;

    };

#endif

// End of File
