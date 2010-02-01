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
* Description:  Declares main application class.
*
*/


#ifndef C_CBCTESTDOMINPUTMETHODSAPP_H
#define C_CBCTESTDOMINPUTMETHODSAPP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
const TUid KUidBCTESTDomInputMethods = { 0xA00040A4 }; // UID of the application.

// CLASS DECLARATION

/**
* CBCTestDomInputMethodsApp application class.
* Provides factory to create concrete document object.
*/
class CBCTestDomInputMethodsApp : public CAknApplication
    {
    private: // From CApaApplication

        /**
        * From CApaApplication, CreateDocumentL.
        * Creates CBCTestDomInputMethodsDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();

        /**
        * From CApaApplication, AppDllUid.
        * Returns application's UID ( KUidBCTESTDomInputMethods ).
        * @return The value of KUidBCTESTDomInputMethods.
        */
        TUid AppDllUid() const;

    };

#endif

// End of File
