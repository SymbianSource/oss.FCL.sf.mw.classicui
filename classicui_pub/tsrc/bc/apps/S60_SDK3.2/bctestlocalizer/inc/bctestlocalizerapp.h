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









#ifndef C_BCTESTLOCALIZERAPP_H
#define C_BCTESTLOCALIZERAPP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
const TUid KUidBCTestLocalizer = { 0x200089D2 }; // UID of the application.

// CLASS DECLARATION

/**
* CBCTestLocalizerApp application class.
* Provides factory to create concrete document object.
*/
class CBCTestLocalizerApp : public CAknApplication
    {
    private: // From CApaApplication

        /**
        * From CApaApplication, CreateDocumentL.
        * Creates CBCTestLocalizerDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();

        /**
        * From CApaApplication, AppDllUid.
        * Returns application's UID ( KUidBCTestLocalizer ).
        * @return The value of KUidBCTestLocalizer.
        */
        TUid AppDllUid() const;

    };

#endif // C_BCTESTLOCALIZERAPP_H

// End of File
