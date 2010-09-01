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
* Description:  test app
*
*/


// INCLUDE FILES
#include <eikstart.h>

#include "bctestdomcoreuiapp.h"
#include "bctestdomcoreuidocument.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// TUid CBCTestDomCoreUiApp::AppDllUid()
// Returns application UID.
// ----------------------------------------------------------------------------
//
TUid CBCTestDomCoreUiApp::AppDllUid() const
    {
    return KUIDBCTESTDomCoreUi;
    }

// ----------------------------------------------------------------------------
// CApaDocument* CBCTestDomCoreUiApp::CreateDocumentL()
// Creates CBCTestDomCoreUiDocument object.
// ----------------------------------------------------------------------------
//
CApaDocument* CBCTestDomCoreUiApp::CreateDocumentL()
    {
    return CBCTestDomCoreUiDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS =================================
//
// ----------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCTestDomCoreUiApp.
// Returns: CApaDocument*: created application object
// ----------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestDomCoreUiApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }

