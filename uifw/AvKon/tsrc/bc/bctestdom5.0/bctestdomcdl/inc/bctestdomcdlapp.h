/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Declares main application class.
*
*/


#ifndef C_CBCTESTDOMCDLAPP_H
#define C_CBCTESTDOMCDLAPP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
const TUid KUidBCTestCdl = { 0xA00040A5 }; // UID of the application.

// CLASS DECLARATION

/**
* CBCTestDomCdlApp application class.
* Provides factory to create concrete document object.
*/
class CBCTestDomCdlApp : public CAknApplication
    {
    private: // From CApaApplication

        /**
        * From CApaApplication, CreateDocumentL.
        * Creates CBCTestDomCdlDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();

        /**
        * From CApaApplication, AppDllUid.
        * Returns application's UID ( KUidBCTestCdl ).
        * @return The value of KUidBCTestCdl.
        */
        TUid AppDllUid() const;

    };

#endif

