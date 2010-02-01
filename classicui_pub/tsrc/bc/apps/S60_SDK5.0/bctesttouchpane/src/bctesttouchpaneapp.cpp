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
* Description:         Avkon TouchPane test app
*
*/









// INCLUDE FILES
#include "bctesttouchpaneapp.h"
#include "bctesttouchpanedocument.h"
#include <eikstart.h>

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// TUid CBCTestTouchPaneApp::AppDllUid()
// Returns application UID.
// ----------------------------------------------------------------------------
//
TUid CBCTestTouchPaneApp::AppDllUid() const
    {
    return KUidBCTestTouchPane;
    }

// ----------------------------------------------------------------------------
// CApaDocument* CBCTestTouchPaneApp::CreateDocumentL()
// Creates CBCTestTouchPaneDocument object.
// ----------------------------------------------------------------------------
//
CApaDocument* CBCTestTouchPaneApp::CreateDocumentL()
    {
    return CBCTestTouchPaneDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS =================================
//
// ----------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCTestTouchPaneApp.
// Returns: CApaDocument*: created application object
// ----------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestTouchPaneApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }

