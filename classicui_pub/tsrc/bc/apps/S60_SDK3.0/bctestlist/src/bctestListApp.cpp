/*
* Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         Avkon list test application
*
*/









// INCLUDE FILES
#include <eikstart.h>

#include "BCTestListApp.h"
#include "BCTestListDocument.h"


// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// TUid CBCTestListApp::AppDllUid()
// Returns application UID.
// ----------------------------------------------------------------------------
//
TUid CBCTestListApp::AppDllUid() const
    {
    return KUidBCTestList;
    }

// ----------------------------------------------------------------------------
// CApaDocument* CBCTestListApp::CreateDocumentL()
// Creates CBCTestListDocument object.
// ----------------------------------------------------------------------------
//
CApaDocument* CBCTestListApp::CreateDocumentL()
    {
    return CBCTestListDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS =================================
//
// ----------------------------------------------------------------------------
// NewApplication()
// Constructs CBCTestListApp.
// Returns: CApaDocument*: created application object
// ----------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestListApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }

// End of File
