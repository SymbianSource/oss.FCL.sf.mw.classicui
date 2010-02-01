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
* Description:  container
*
*/

#ifndef C_BCTESTPHYSICSAPP_H
#define C_BCTESTPHYSICSAPP_H

#include <aknapp.h>

const TUid KUidBCTestPhysics = { 0xA00040B0 }; // UID of the application.

/**
* CBCTestPhysicsApp class.
* Provides factory to create concrete document object.
*/
class CBCTestPhysicsApp : public CAknApplication
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

#endif // C_BCTESTPHYSICSAPP_H

// End of File
