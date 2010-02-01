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
* Description:         Application
*
*/









#include <eikstart.h>

#include "BCTestQueryApp.h"
#include "BCTestQueryDocument.h"


// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// TUid CBCTestQueryApp::AppDllUid()
// Returns application UID.
// ----------------------------------------------------------------------------
//
TUid CBCTestQueryApp::AppDllUid() const
    {
    return KUidBCTestQuery;
    }

// ----------------------------------------------------------------------------
// CApaDocument* CBCTestQueryApp::CreateDocumentL()
// Creates CBCTestQueryDocument object.
// ----------------------------------------------------------------------------
//
CApaDocument* CBCTestQueryApp::CreateDocumentL()
    {
    return CBCTestQueryDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS =================================
//
// ----------------------------------------------------------------------------
// NewApplication()
// Constructs CBCTestQueryApp.
// Returns: CApaDocument*: created application object
// ----------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestQueryApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }


