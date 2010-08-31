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









#ifndef BCTestKeyLockAPP_H
#define BCTestKeyLockAPP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
const TUid KUidBCTestKeyLock = { 0x20004764 }; // UID of the application.

// CLASS DECLARATION

/**
* CBCTestKeyLockApp application class.
* Provides factory to create concrete document object.
*/
class CBCTestKeyLockApp : public CAknApplication
    {
    private: // From CApaApplication

        /**
        * From CApaApplication, CreateDocumentL.
        * Creates CBCTestKeyLockDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();

        /**
        * From CApaApplication, AppDllUid.
        * Returns application's UID ( KUidBCTestKeyLock ).
        * @return The value of KUidBCTestKeyLock.
        */
        TUid AppDllUid() const;

    };

#endif

// End of File
