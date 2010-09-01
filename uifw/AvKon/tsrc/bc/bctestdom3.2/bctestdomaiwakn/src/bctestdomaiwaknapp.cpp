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
* Description:  app
*
*/




#include <eikstart.h>


#include "bctestdomaiwaknapp.h"
#include "bctestdomaiwakndocument.h"


// ================= MEMBER FUNCTIONS ========================================

// ---------------------------------------------------------------------------
// TUid CBCTestDomAiwAknApp::AppDllUid()
// Returns application UID.
// ---------------------------------------------------------------------------
//
TUid CBCTestDomAiwAknApp::AppDllUid() const
    {
    return KUidBCTestAiwAkn;
    }

// ---------------------------------------------------------------------------
// CApaDocument* CBCTestDomAiwAknApp::CreateDocumentL()
// Creates CBCTestDomAiwAknDocument object.
// ---------------------------------------------------------------------------
//
CApaDocument* CBCTestDomAiwAknApp::CreateDocumentL()
    {
    return CBCTestDomAiwAknDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS ================================
//
// ---------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCTestDomAiwAknApp.
// Returns: CApaDocument*: created application object
// ---------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestDomAiwAknApp;
    }
    
// ---------------------------------------------------------------------------
// Main function of the application executable.
// ---------------------------------------------------------------------------
//
GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication( NewApplication );
    }

// End of File
