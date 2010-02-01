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
* Description:         Avkon Scroller test app
*
*/









// INCLUDE FILES
#include "BCTestScrollerApp.h"
#include "BCTestScrollerDocument.h"
#include <eikstart.h>

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// TUid CBCTestScrollerApp::AppDllUid()
// Returns application UID.
// ----------------------------------------------------------------------------
//
TUid CBCTestScrollerApp::AppDllUid() const
    { 
    return KUidBCTestScroller;
    }

// ----------------------------------------------------------------------------
// CApaDocument* CBCTestScrollerApp::CreateDocumentL()
// Creates CBCTestScrollerDocument object.
// ----------------------------------------------------------------------------
//
CApaDocument* CBCTestScrollerApp::CreateDocumentL()
    {
    return CBCTestScrollerDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS =================================
//
// ----------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCTestScrollerApp.
// Returns: CApaDocument*: created application object
// ----------------------------------------------------------------------------

LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestScrollerApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }

// End of File
