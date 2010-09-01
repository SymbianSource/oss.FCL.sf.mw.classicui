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


#ifndef C_MultiDriverAPP_H
#define C_MultiDriverAPP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
const TUid KUidMultiDriver = { 0xA00040AE }; // UID of the application.

// CLASS DECLARATION

/**
* CMultiDriverApp application class.
* Provides factory to create concrete document object.
*/
class CMultiDriverApp : public CAknApplication
    {
    private: // From CApaApplication

        /**
        * From CApaApplication, CreateDocumentL.
        * Creates CMultiDriverDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();

        /**
        * From CApaApplication, AppDllUid.
        * Returns application's UID ( KUidMultiDriver ).
        * @return The value of KUidMultiDriver.
        */
        TUid AppDllUid() const;

    };

#endif // C_MultiDriverAPP_H

// End of File
