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
* Description:         Avkon Template test app
*
*/









// INCLUDE FILES 
#include "BCTestEHApp.h"
#include "BCTestEHDocument.h"
#include <eikstart.h>

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// TUid CBCTestEHApp::AppDllUid()
// Returns application UID.
// ----------------------------------------------------------------------------
//
TUid CBCTestEHApp::AppDllUid() const
    {
    return KUidBCTestEH;
    }

// ----------------------------------------------------------------------------
// CApaDocument* CBCTestEHApp::CreateDocumentL()
// Creates CBCTestEHDocument object.
// ----------------------------------------------------------------------------
//
CApaDocument* CBCTestEHApp::CreateDocumentL()
    {
    return CBCTestEHDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS =================================
//
// ----------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCTestEHApp.
// Returns: CApaDocument*: created application object
// ----------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestEHApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }

// End of File
