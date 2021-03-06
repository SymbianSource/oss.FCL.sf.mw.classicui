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









#ifndef BCTestPREVIEWPOPUPAPP_H
#define BCTestPREVIEWPOPUPAPP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
const TUid KUidBCTestPreviewPopup = { 0x101F84FF }; // UID of the application.

// CLASS DECLARATION

/**
* CBCTestPreviewPopupApp application class.
* Provides factory to create concrete document object.
*/
class CBCTestPreviewPopupApp : public CAknApplication
    {
    private: // From CApaApplication

        /**
        * From CApaApplication, CreateDocumentL.
        * Creates CBCTestPreviewPopupDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();

        /**
        * From CApaApplication, AppDllUid.
        * Returns application's UID ( KUidBCTestPreviewPopup ).
        * @return The value of KUidBCTestPreviewPopup.
        */
        TUid AppDllUid() const;

    };

#endif

// End of File
