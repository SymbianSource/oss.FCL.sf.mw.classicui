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









#ifndef BCTesteikbctrlAPP_H
#define BCTesteikbctrlAPP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
const TUid KUidBCTesteikbctrl = { 0x20004746 }; // UID of the application.

// CLASS DECLARATION

/**
* CBCTesteikbctrlApp application class.
* Provides factory to create concrete document object.
*/
class CBCTesteikbctrlApp : public CAknApplication
    {
    private: // From CApaApplication

        /**
        * From CApaApplication, CreateDocumentL.
        * Creates CBCTesteikbctrlDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();

        /**
        * From CApaApplication, AppDllUid.
        * Returns application's UID ( KUidBCTesteikbctrl ).
        * @return The value of KUidBCTesteikbctrl.
        */
        TUid AppDllUid() const;

    };

#endif

// End of File
