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
* Description:  ?Description
*
*/

#include <eikstart.h>

#include "bctestdomavkonpslnapp.h"
#include "bctestdomavkonpslndocument.h"


// ================= MEMBER FUNCTIONS ========================================

// ---------------------------------------------------------------------------
// TUid CBCTestDomAvkonPslnApp::AppDllUid()
// Returns application UID.
// ---------------------------------------------------------------------------
//
TUid CBCTestDomAvkonPslnApp::AppDllUid() const
    {
    return KUidBCTestDomain;
    }

// ---------------------------------------------------------------------------
// CApaDocument* CBCTestDomAvkonPslnApp::CreateDocumentL()
// Creates CBCTestDomAvkonPslnDocument object.
// ---------------------------------------------------------------------------
//
CApaDocument* CBCTestDomAvkonPslnApp::CreateDocumentL()
    {
    return CBCTestDomAvkonPslnDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS ================================
//
// ---------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCTestDomAvkonPslnApp.
// Returns: CApaDocument*: created application object
// ---------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestDomAvkonPslnApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication( NewApplication );
    }

// End of File
