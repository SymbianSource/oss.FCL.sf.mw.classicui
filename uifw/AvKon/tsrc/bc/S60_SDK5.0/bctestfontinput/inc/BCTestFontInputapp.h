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


#ifndef C_BCTestFontInputAPP_H
#define C_BCTestFontInputAPP_H

#include <aknapp.h>

const TUid KUidBCTestFontInput = { 0x0100130b }; // UID of the application.

/**
* CBCTestFontInputApp class.
* Provides factory to create concrete document object.
*/
class CBCTestFontInputApp : public CAknApplication
    {
    private: // From CApaApplication

        /**
        * From CApaApplication, CreateDocumentL.
        * Creates CBCTestFontInputDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();

        /**
        * From CApaApplication, AppDllUid.
        * Returns application's UID ( KUidBCTestFontInput ).
        * @return The value of KUidBCTestFontInput.
        */
        TUid AppDllUid() const;

    };

#endif // C_BCTestFontInputAPP_H

// End of File
