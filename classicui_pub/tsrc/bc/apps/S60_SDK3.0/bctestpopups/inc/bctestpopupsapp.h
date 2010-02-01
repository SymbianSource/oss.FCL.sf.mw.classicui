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









#ifndef C_CBCTESTPOPUPSAPP_H
#define C_CBCTESTPOPUPSAPP_H

#include <aknapp.h>

const TUid KUidBCTestPopups = { 0x200045CA }; // UID of the application.

/**
 * CBCTestPopupsApp application class.
 * Provides factory to create concrete document object.
 */
class CBCTestPopupsApp : public CAknApplication
    {
private: 

// From CApaApplication

    /**
    * From CApaApplication, CreateDocumentL.
    * Creates CBCTestPopupsDocument document object.
    * @return A pointer to the created document object.
    */
    CApaDocument* CreateDocumentL();

    /**
    * From CApaApplication, AppDllUid.
    * Returns application's UID ( KUidBCTestPopups ).
    * @return The value of KUidBCTestPopups.
    */
    TUid AppDllUid() const;

    };

#endif // C_CBCTESTPOPUPSAPP_H
