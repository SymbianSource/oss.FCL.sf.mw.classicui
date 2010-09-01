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









#ifndef C_PBK2TESTAPP_H
#define C_PBK2TESTAPP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
const TUid KUidBCPopupChoicelist = { 0x200089C4 }; // UID of the application.

// CLASS DECLARATION

/**
* CBCPopupChoicelistApp application class.
* Provides factory to create concrete document object.
*/
class CBCPopupChoicelistApp : public CAknApplication
    {
    private: // From CApaApplication

        /**
        * From CApaApplication, CreateDocumentL.
        * Creates CBCPopupChoicelistDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();

        /**
        * From CApaApplication, AppDllUid.
        * Returns application's UID ( KUidBCPopupChoicelist ).
        * @return The value of KUidBCPopupChoicelist.
        */
        TUid AppDllUid() const;

    };

#endif // C_PBK2TESTAPP_H

// End of File
