/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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









#ifndef C_CBCTESTMISCCONTROLAPP_H
#define C_CBCTESTMISCCONTROLAPP_H

#include <aknapp.h>

const TUid KUidBCTestMiscControl = { 0x20004759 }; // UID of the application.

/**
 * CBCTestMiscControlApp application class.
 * Provides factory to create concrete document object.
 */
class CBCTestMiscControlApp : public CAknApplication
    {

private: 

// From CApaApplication

    /**
    * From CApaApplication, CreateDocumentL.
    * Creates CBCTestMisccontrolDocument document object.
    * @return A pointer to the created document object.
    */
    CApaDocument* CreateDocumentL();

    /**
    * From CApaApplication, AppDllUid.
    * Returns application's UID ( KUidBCTestMisccontrol ).
    * @return The value of KUidBCTestMisccontrol.
    */
    TUid AppDllUid() const;

    };

#endif // C_CBCTESTMISCCONTROLAPP_H
