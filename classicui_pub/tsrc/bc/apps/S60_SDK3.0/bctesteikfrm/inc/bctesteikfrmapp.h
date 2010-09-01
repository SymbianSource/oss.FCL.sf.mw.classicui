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









#ifndef BCTESTEIKFRMAPP_H
#define BCTESTEIKFRMAPP_H

// INCLUDES
#include <eikapp.h>

// CONSTANTS
const TUid KUidBCTestTemplate = { 0x200045CD }; // UID of the application.

// CLASS DECLARATION

/**
* CBCTestEikFrmApp application class.
* Provides factory to create concrete document object.
*/
class CBCTestEikFrmApp : public CEikApplication
    {
	public:
		CBCTestEikFrmApp();

		void NewAppServerL(CApaAppServer*& aAppServer);

    private: // From CApaApplication

        /**
        * From CApaApplication, CreateDocumentL.
        * Creates CBCTestTemplateDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();

        /**
        * From CApaApplication, AppDllUid.
        * Returns application's UID ( KUidBCTestTemplate ).
        * @return The value of KUidBCTestTemplate.
        */
        TUid AppDllUid() const;

    };

#endif

// End of File
