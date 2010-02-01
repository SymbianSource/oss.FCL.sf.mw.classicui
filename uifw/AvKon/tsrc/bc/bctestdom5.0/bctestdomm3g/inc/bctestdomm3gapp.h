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
* Description:  Define application class.
*
*/


#ifndef C_CBCTESTDOMM3GAPP_H
#define C_CBCTESTDOMM3GAPP_H

#include <aknapp.h>

const TUid KUidBCTestM3g = { 0xA00040A2 }; // UID of the application.

// CLASS DECLARATION

/**
 * CBCTestDomM3gApp application class.
 * Provides factory to create concrete document object.
 */
class CBCTestDomM3gApp : public CAknApplication
    {
private: // From CApaApplication

    /**
    * From CApaApplication, CreateDocumentL.
    * Creates CBCTestTemplateDocument document object.
    * @return A pointer to the created document object.
    */
    CApaDocument* CreateDocumentL();

    /**
    * From CApaApplication, AppDllUid.
    * Returns application's UID ( KUidBCTestTemplate ).
    * @return The value of KUidBCTestTemplate.
    */
    TUid AppDllUid() const;

    };

#endif //C_CBCTESTDOMM3GAPP_H
