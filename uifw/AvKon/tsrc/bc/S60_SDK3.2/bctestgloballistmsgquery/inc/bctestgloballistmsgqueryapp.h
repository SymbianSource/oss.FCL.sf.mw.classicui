/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Declares main application class.
*
*/

#ifndef BCTESTGLOBALLISTMSGQUERYAPP_H
#define BCTESTGLOBALLISTMSGQUERYAPP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
const TUid KUidBCTestGlobalListMsgQuery = { 0x2001E271 }; // UID of the application.

// CLASS DECLARATION

/**
* CBCTestGlobalListMsgQueryApp application class.
* Provides factory to create concrete document object.
*/
class CBCTestGlobalListMsgQueryApp : public CAknApplication
    {
private: // From CApaApplication
    /**
    * From CApaApplication.
    * Creates CBCTestGlobalListMsgQueryApp document object.
    *
    * @return A pointer to the created document object.
    */
    CApaDocument* CreateDocumentL();

    /**
    * From CApaApplication.
    * Returns application's UID.
    *
    * @return The application UID.
    */
    TUid AppDllUid() const;
    };

#endif

// End of file
