/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef BCTestLOCATIONAPP_H
#define BCTestLOCATIONAPP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
const TUid KUidBCTestLocation = { 0x2000476A }; // UID of the application.

// CLASS DECLARATION

/**
* CBCTestLocationApp application class.
* Provides factory to create concrete document object.
*/
class CBCTestLocationApp : public CAknApplication
    {
    private: // From CApaApplication

        /**
        * From CApaApplication, CreateDocumentL.
        * Creates CBCTestLocationDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();

        /**
        * From CApaApplication, AppDllUid.
        * Returns application's UID ( KUidBCTestLocation ).
        * @return The value of KUidBCTestLocation.
        */
        TUid AppDllUid() const;

    };

#endif

// End of File