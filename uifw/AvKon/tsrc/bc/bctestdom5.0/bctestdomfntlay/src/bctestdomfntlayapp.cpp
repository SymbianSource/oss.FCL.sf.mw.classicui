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
* Description:  Implement of app of  bctestdomfntlay 
*
*/


// INCLUDE FILES
#include <eikstart.h>

#include "bctestdomfntlayapp.h"
#include "bctestdomfntlaydocument.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// TUid CBCTestDomFntlayApp::AppDllUid()
// Returns application UID.
// ----------------------------------------------------------------------------
//
TUid CBCTestDomFntlayApp::AppDllUid() const
    {
    return KUidBCTestDomFntlay;
    }

// ----------------------------------------------------------------------------
// CApaDocument* CBCTestDomFntlayApp::CreateDocumentL()
// Creates CBCTestDomFntlayDocument object.
// ----------------------------------------------------------------------------
//
CApaDocument* CBCTestDomFntlayApp::CreateDocumentL()
    {
    return CBCTestDomFntlayDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS =================================
//
// ----------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCTestDomFntlayApp.
// Returns: CApaDocument*: created application object
// ----------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestDomFntlayApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }
