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
* Description:         Declares application UI class.
*
*/









#ifndef C_BCTESTSEARCHFIELDAPP_H
#define C_BCTESTSEARCHFIELDAPP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
const TUid KUidBCTestSearchField = { 0x2000474B }; // UID of the application.

// CLASS DECLARATION

/**
* CBCTestTemplateApp application class.
* Provides factory to create concrete document object.
*/
class CBCTestSearchFieldApp : public CAknApplication
    {
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

#endif // C_BCTESTSEARCHFIELDAPP_H
