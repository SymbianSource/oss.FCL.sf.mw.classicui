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
* Description:         test app
*
*/









// INCLUDE FILES
#include "bctesttoolbarapp.h"
#include "bctesttoolbardocument.h"
#include <eikstart.h>

// ================= MEMBER FUNCTIONS =======================================

// --------------------------------------------------------------------------
// TUid CBCTestToolBarApp::AppDllUid()
// Returns application UID.
// --------------------------------------------------------------------------
//
TUid CBCTestToolBarApp::AppDllUid() const
    {
    return KUidBCTestToolBar;
    }

// --------------------------------------------------------------------------
// CApaDocument* CBCTestToolBarApp::CreateDocumentL()
// Creates CBCTestToolBarDocument object.
// --------------------------------------------------------------------------
//
CApaDocument* CBCTestToolBarApp::CreateDocumentL()
    {
    return CBCTestToolBarDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS ===============================
//
// --------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCTestToolBarApp.
// Returns: CApaDocument*: created application object
// --------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestToolBarApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication( NewApplication );
    }

// End of File
