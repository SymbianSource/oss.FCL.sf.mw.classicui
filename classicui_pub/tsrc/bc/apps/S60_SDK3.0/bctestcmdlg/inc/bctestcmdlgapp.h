/*
* Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
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









#ifndef BCTESTCMDLGAPP_H
#define BCTESTCMDLGAPP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
const TUid KUidBCTestCmDlg = { 0x2000475D }; // UID of the application.

// CLASS DECLARATION

/**
* CBCTestCmDlgApp application class.
* Provides factory to create concrete document object.
*/
class CBCTestCmDlgApp : public CAknApplication
    {
    private: // From CApaApplication

        /**
        * From CApaApplication, CreateDocumentL.
        * Creates CBCTestCmDlgDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();

        /**
        * From CApaApplication, AppDllUid.
        * Returns application's UID ( KUidBCTestCmDlg ).
        * @return The value of KUidBCTestCmDlg.
        */
        TUid AppDllUid() const;

    };

#endif

// End of File
