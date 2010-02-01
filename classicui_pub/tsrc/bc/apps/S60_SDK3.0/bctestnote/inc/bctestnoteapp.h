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









#ifndef C_CBCTESTNOTEAPP_H
#define C_CBCTESTNOTEAPP_H

#include <aknapp.h>

const TUid KUidBCTestNote = { 0x20004749 }; // UID of the application.

/**
 * CBCTestNoteApp application class.
 * Provides factory to create concrete document object.
 */
class CBCTestNoteApp : public CAknApplication
    {
private: 

// From CApaApplication

    /**
    * From CApaApplication, CreateDocumentL.
    * Creates CBCTestNoteDocument document object.
    * @return A pointer to the created document object.
    */
    CApaDocument* CreateDocumentL();

    /**
    * From CApaApplication, AppDllUid.
    * Returns application's UID ( KUidBCTestNote ).
    * @return The value of KUidBCTestNote.
    */
    TUid AppDllUid() const;

    };

#endif // C_CBCTESTNOTEAPP_H
