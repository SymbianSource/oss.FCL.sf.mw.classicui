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
* Description:         main application class
*
*/








#ifndef BCTESTFORMAPP_H
#define BCTESTFORMAPP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
const TUid KUidBCTestForm = { 0x20004747 }; // UID of the application

// CLASS DECLARATION

/**
* CBCTestFormApplication application class.
* Provides factory to create concrete document object.
*/
class CBCTestFormApplication : public CAknApplication
    {
    private: // From CApaApplication

        /**
        * From CApaApplication, CreateDocumentL.
        * Creates CBCTestFormDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();

        /**
        * From CApaApplication, AppDllUid.
        * Returns application's UID (KUidBCTestForm).
        * @return The value of KUidBCTestForm.
        */
        TUid AppDllUid() const;

    };

#endif

// End of File
