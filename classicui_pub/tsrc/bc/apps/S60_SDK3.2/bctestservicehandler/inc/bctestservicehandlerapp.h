/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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









#ifndef BCTESTSERVICEHANDLERAPP_H
#define BCTESTSERVICEHANDLERAPP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
const TUid KUidBCTestServiceHandler = { 0x20007628 }; // UID of the application.

// CLASS DECLARATION

/**
* CBCTestServiceHandlerApp application class.
* Provides factory to create concrete document object.
*/
class CBCTestServiceHandlerApp : public CAknApplication
    {
    private: // From CApaApplication

        /**
        * From CApaApplication, CreateDocumentL.
        * Creates CBCTestServiceHandlerDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();

        /**
        * From CApaApplication, AppDllUid.
        * Returns application's UID ( KUidBCTestServiceHandler ).
        * @return The value of KUidBCTestServiceHandler.
        */
        TUid AppDllUid() const;

    };

#endif // BCTESTSERVICEHANDLERAPP_H

// End of File
