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
#include <eikstart.h>

#include "bctestocrapp.h"
#include "bctestocrdocument.h"

// ================= MEMBER FUNCTIONS ========================================

// ---------------------------------------------------------------------------
// TUid CBCTestOCRApp::AppDllUid()
// Returns application UID.
// ---------------------------------------------------------------------------
//
TUid CBCTestOCRApp::AppDllUid() const
    {
    return KUidBCTestOCR;
    }

// ---------------------------------------------------------------------------
// CApaDocument* CBCTestOCRApp::CreateDocumentL()
// Creates CBCTestOCRDocument object.
// ---------------------------------------------------------------------------
//
CApaDocument* CBCTestOCRApp::CreateDocumentL()
    {
    return CBCTestOCRDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS ================================
//
// ---------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCTestOCRApp.
// Returns: CApaDocument*: created application object
// ---------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestOCRApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication( NewApplication );
    }
