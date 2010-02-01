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









#ifndef BCTESTSERVERAPPAPP_H
#define BCTESTSERVERAPPAPP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
const TUid KUidBCTestServerapp = { 0x2000475E }; // UID of the application.

// CLASS DECLARATION

/**
* CBCTestServerappApp application class.
* Provides factory to create concrete document object.
*/
class CBCTestServerappApp : public CAknApplication
    {
    private: // From CApaApplication

        /**
        * From CApaApplication, CreateDocumentL.
        * Creates CBCTestServerappDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();

        /**
        * From CApaApplication, AppDllUid.
        * Returns application's UID ( KUidBCTestServerapp ).
        * @return The value of KUidBCTestServerapp.
        */
        TUid AppDllUid() const;
    /*public:
    	void NewAppServerL(CApaAppServer*& aAppServer);*/

    };

#endif

// End of File
