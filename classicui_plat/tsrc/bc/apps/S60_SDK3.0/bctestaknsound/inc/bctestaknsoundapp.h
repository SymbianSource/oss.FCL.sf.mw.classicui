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









#ifndef C_CBCTESTAKNSOUNDAPP_H
#define C_CBCTESTAKNSOUNDAPP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
const TUid KUidBCTestAknSound = { 0x200045C8 }; // UID of the application.

// CLASS DECLARATION

/**
* CBCTestAknSoundApp application class.
* Provides factory to create concrete document object.
*/
class CBCTestAknSoundApp : public CAknApplication
    {
    private: // From CApaApplication

        /**
        * From CApaApplication, CreateDocumentL.
        * Creates CBCTestAknSoundDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();

        /**
        * From CApaApplication, AppDllUid.
        * Returns application's UID ( KUidBCTestAknSound ).
        * @return The value of KUidBCTestAknSound.
        */
        TUid AppDllUid() const;

    };

#endif


