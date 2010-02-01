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









#ifndef C_CBCTESRUTILITIESAPP_H
#define C_CBCTESRUTILITIESAPP_H

#include <aknapp.h>

const TUid KUidBCTestUtilities = { 0x200045C7 }; // UID of the application.

/**
* CBCTestUtilitiesApp application class.
* Provides factory to create concrete document object.
*/
class CBCTestUtilitiesApp : public CAknApplication
    {
private: // From CApaApplication

    /**
     * From CApaApplication, CreateDocumentL.
     * Creates CBCTestUtilitiesDocument document object.
     * @return A pointer to the created document object.
     */
    CApaDocument* CreateDocumentL();

    /**
     * From CApaApplication, AppDllUid.
     * Returns application's UID ( KUidBCTestUtilities ).
     * @return The value of KUidBCTestUtilities.
     */
    TUid AppDllUid() const;

    };

#endif // C_CBCTESRUTILITIESAPP_H
