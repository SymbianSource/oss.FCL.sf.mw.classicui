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


#ifndef C_BCExtendedFontApiAPP_H
#define C_BCExtendedFontApiAPP_H

#include <aknapp.h>

const TUid KUidBCExtendedFontApi = { 0xA00040AF }; // UID of the application.

/**
* CBCExtendedFontApiApp class.
* Provides factory to create concrete document object.
*/
class CBCExtendedFontApiApp : public CAknApplication
    {
    private: // From CApaApplication

        /**
        * From CApaApplication, CreateDocumentL.
        * Creates CBCExtendedFontApiDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();

        /**
        * From CApaApplication, AppDllUid.
        * Returns application's UID ( KUidBCExtendedFontApi ).
        * @return The value of KUidBCExtendedFontApi.
        */
        TUid AppDllUid() const;

    };

#endif // C_BCExtendedFontApiAPP_H

// End of File
