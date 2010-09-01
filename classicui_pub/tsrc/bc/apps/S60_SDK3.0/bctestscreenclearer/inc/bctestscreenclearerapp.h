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









#ifndef C_CBCTESTSCREENCLEARERAPP_H
#define C_CBCTESTSCREENCLEARERAPP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
const TUid KUidBCTestScreenClearer = { 
    0x2000474A }; // UID of the application.

// CLASS DECLARATION

/**
* CBCTestScreenClearerApp application class.
* Provides factory to create concrete document object.
*/
class CBCTestScreenClearerApp : public CAknApplication
    {
private: // From CApaApplication

    /**
     * From CApaApplication, CreateDocumentL.
     * Creates CBCTestScreenClearerDocument document object.
     * @return A pointer to the created document object.
     */
    CApaDocument* CreateDocumentL();

    /**
     * From CApaApplication, AppDllUid.
     * Returns application's UID ( KUidBCTestScreenClearer ).
     * @return The value of KUidBCTestScreenClearer.
     */
    TUid AppDllUid() const;

    };

#endif
