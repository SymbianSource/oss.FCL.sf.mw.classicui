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









#ifndef C_CBCTESTMISCAPP_H
#define C_CBCTESTMISCAPP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
const TUid KUidBCTestMisc = { 0x20004765 }; // UID of the application.

// CLASS DECLARATION

/**
* CBCTestMiscApp application class.
* Provides factory to create concrete document object.
*/
class CBCTestMiscApp : public CAknApplication
    {
private: // From CApaApplication

    /**
    * From CApaApplication, CreateDocumentL.
    * Creates CBCTestMiscDocument document object.
    * @return A pointer to the created document object.
    */
    CApaDocument* CreateDocumentL();

    /**
    * From CApaApplication, AppDllUid.
    * Returns application's UID ( KUidBCTestMisc ).
    * @return The value of KUidBCTestMisc.
    */
    TUid AppDllUid() const;

    };

#endif

