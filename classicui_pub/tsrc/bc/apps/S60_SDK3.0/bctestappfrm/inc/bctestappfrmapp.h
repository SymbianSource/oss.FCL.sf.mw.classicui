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









#ifndef C_CBCTESTAPPFRMAPP_H
#define C_CBCTESTAPPFRMAPP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
const TUid KUidBCTestAppFrm = { 0x200045CC }; // UID of the application.

// CLASS DECLARATION

/**
* CBCTestAppFrmApp application class.
* Provides factory to create concrete document object.
*/
class CBCTestAppFrmApp : public CAknApplication
    {
    public:
        virtual void PreDocConstructL();

    private: // From CApaApplication

        /**
        * From CApaApplication, CreateDocumentL.
        * Creates CBCTestAppFrmDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();

        /**
        * From CApaApplication, AppDllUid.
        * Returns application's UID ( KUidBCTestAppFrm ).
        * @return The value of KUidBCTestAppFrm.
        */
        TUid AppDllUid() const;

    };

#endif


