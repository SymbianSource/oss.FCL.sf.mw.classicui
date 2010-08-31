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
* Description:         Application
*
*/









#ifndef C_BCTESTPANEAPP_H
#define C_BCTESTPANEAPP_H

#include <aknapp.h>

const TUid KUidBCTestPane = { 0x2000475A }; // UID of the application.

/**
 * CBCTestPaneApp application class.
 * Provides factory to create concrete document object.
 */
class CBCTestPaneApp : public CAknApplication
    {
private: // From CApaApplication

    /**
     * From CApaApplication, CreateDocumentL.
     * Creates CBCTestPaneDocument document object.
     * @return A pointer to the created document object.
     */
    CApaDocument* CreateDocumentL();

    /**
     * From CApaApplication, AppDllUid.
     * Returns application's UID ( KUidBCTestPane ).
     * @return The value of KUidBCTestPane.
     */
    TUid AppDllUid() const;

    };

#endif // C_BCTESTPANEAPP_H

