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


#ifndef C_BCTESTDOMNOTIFIERAPP_H
#define C_BCTESTDOMNOTIFIERAPP_H

#include <aknapp.h>

const TUid KUidBCDomainTestNotifier = { 0xA00040A0 }; // UID of the application.

/**
* CBCDomainTestNotifierApp class.
* Provides factory to create concrete document object.
*/
class CBCDomainTestNotifierApp : public CAknApplication
    {
private: 
// From CApaApplication

        /**
        * From CApaApplication, CreateDocumentL.
        * Creates CBCDomainTestNotifierDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();

        /**
        * From CApaApplication, AppDllUid.
        * Returns application's UID ( KUidBCDomainTestNotifier ).
        * @return The value of KUidBCDomainTestNotifier.
        */
        TUid AppDllUid() const;

    };

#endif // C_BCTESTDOMNOTIFIERAPP_H

// End of File
