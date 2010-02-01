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
#include "bctestpopupsapp.h" 
#include "bctestpopupsdocument.h"
#include <eikstart.h>

// ================= MEMBER FUNCTIONS ========================================

// ---------------------------------------------------------------------------
// TUid CBCTestPopupsApp::AppDllUid()
// Returns application UID.
// ---------------------------------------------------------------------------
//
TUid CBCTestPopupsApp::AppDllUid() const
    {
    return KUidBCTestPopups;  
  
    }

// ---------------------------------------------------------------------------
// CApaDocument* CBCTestPopupsApp::CreateDocumentL()
// Creates CBCTestPopupsDocument object.
// ---------------------------------------------------------------------------
//
CApaDocument* CBCTestPopupsApp::CreateDocumentL()
    {
    return CBCTestPopupsDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS ================================
//
// ---------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCTestPopupsApp.
// Returns: CApaDocument*: created application object
// ---------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestPopupsApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }
