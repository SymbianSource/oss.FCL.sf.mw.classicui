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
* Description:  Cdl test app
*
*/


// INCLUDE FILES
#include <eikstart.h>

#include "bctestdomcdlapp.h"
#include "bctestdomcdldocument.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// TUid CBCTestDomCdlApp::AppDllUid()
// Returns application UID.
// ----------------------------------------------------------------------------
//
TUid CBCTestDomCdlApp::AppDllUid() const
    {
    return KUidBCTestCdl;
    }

// ----------------------------------------------------------------------------
// CApaDocument* CBCTestDomCdlApp::CreateDocumentL()
// Creates CBCTestDomCdlDocument object.
// ----------------------------------------------------------------------------
//
CApaDocument* CBCTestDomCdlApp::CreateDocumentL()
    {
    return CBCTestDomCdlDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS =================================
//
// ----------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCTestDomCdlApp.
// Returns: CApaDocument*: created application object
// ----------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestDomCdlApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }


