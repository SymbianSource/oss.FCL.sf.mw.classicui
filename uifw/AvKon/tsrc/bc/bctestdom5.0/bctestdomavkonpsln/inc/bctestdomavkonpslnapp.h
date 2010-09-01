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
* Description:  declaration of app.
*
*/


#ifndef C_BCTESTDOMAVKONPSLNAPP_H
#define C_BCTESTDOMAVKONPSLNAPP_H

#include <aknapp.h>

const TUid KUidBCTestDomain = { 0xA00040A1 }; // UID of the application.

/**
* CBCTestDomAvkonPslnApp class.
* Provides factory to create concrete document object.
*/
class CBCTestDomAvkonPslnApp : public CAknApplication
    {
    
private: 
// From CApaApplication

    /**
    * From CApaApplication, CreateDocumentL.
    * Creates CBCTestDomAvkonPslnDocument document object.
    * @return A pointer to the created document object.
    */
    CApaDocument* CreateDocumentL();

    /**
    * From CApaApplication, AppDllUid.
    * Returns application's UID ( KUidBCTestDomain ).
    * @return The value of KUidBCTestDomain.
    */
    TUid AppDllUid() const;

    };

#endif // C_BCTESTDOMAVKONPSLNAPP_H

// End of File
