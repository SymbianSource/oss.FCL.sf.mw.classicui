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
* Description:         Implements main application class.
*
*/









// INCLUDE FILES
#include "bctestnoteapp.h"
#include "bctestnotedocument.h"
#include <eikstart.h>

// ================= MEMBER FUNCTIONS ========================================

// ---------------------------------------------------------------------------
// TUid CBCTestNoteApp::AppDllUid()
// Returns application UID.
 
// ---------------------------------------------------------------------------
//
TUid CBCTestNoteApp::AppDllUid() const
    {
    return KUidBCTestNote;
    }

// ---------------------------------------------------------------------------
// CApaDocument* CBCTestNoteApp::CreateDocumentL()
// Creates CBCTestNoteDocument object.
// ---------------------------------------------------------------------------
//
CApaDocument* CBCTestNoteApp::CreateDocumentL()
    {
    return CBCTestNoteDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS ================================
//
// ---------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCTestNoteApp.
// Returns: CApaDocument*: created application object
// ---------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestNoteApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }
