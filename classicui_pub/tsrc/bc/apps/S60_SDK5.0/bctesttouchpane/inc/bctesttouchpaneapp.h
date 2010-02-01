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









#ifndef C_CBCTESTTOUCHPANEAPP_H
#define C_CBCTESTTOUCHPANEAPP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
const TUid KUidBCTestTouchPane = { 0x20004769 }; // UID of the application.

// CLASS DECLARATION

/**
* CBCTestTouchPaneApp application class.
* Provides factory to create concrete document object.
*/
class CBCTestTouchPaneApp : public CAknApplication
    {
private: // From CApaApplication

    /**
    * From CApaApplication, CreateDocumentL.
    * Creates CBCTestTouchPaneDocument document object.
    * @return A pointer to the created document object.
    */
    CApaDocument* CreateDocumentL();

    /**
    * From CApaApplication, AppDllUid.
    * Returns application's UID ( KUidBCTestTouchPane ).
    * @return The value of KUidBCTestTouchPane.
    */
    TUid AppDllUid() const;

    };

#endif

