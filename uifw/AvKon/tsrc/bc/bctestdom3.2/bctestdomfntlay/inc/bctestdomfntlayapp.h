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
* Description:  Declares application UI class.
*
*/


#ifndef C_CBCTESTDOMFNTLAYAPP_H
#define C_CBCTESTDOMFNTLAYAPP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
const TUid KUidBCTestDomFntlay = { 0xA00040A3 }; // UID of the application.

// CLASS DECLARATION

/**
* CBCTestDomFntlayApp application class.
* Provides factory to create concrete document object.
*/
class CBCTestDomFntlayApp : public CAknApplication
    {
private: // From CApaApplication

    /**
    * From CApaApplication, CreateDocumentL.
    * Creates CBCTestDomFntlayDocument document object.
    * @return A pointer to the created document object.
    */
    CApaDocument* CreateDocumentL();

    /**
    * From CApaApplication, AppDllUid.
    * Returns application's UID ( KUidBCTestDomFntlay ).
    * @return The value of KUidBCTestDomFntlay.
    */
    TUid AppDllUid() const;

    };

#endif //C_CBCTESTDOMFNTLAYAPP_H
