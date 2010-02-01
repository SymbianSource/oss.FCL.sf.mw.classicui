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
* Description:         Avkon Sound test app
*
*/









// INCLUDE FILES
#include "bctestappfrmapp.h"
#include "bctestappfrmdocument.h"
#include <eikstart.h>

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// TUid CBCTestAppFrmApp::AppDllUid()
// Returns application UID.
// ----------------------------------------------------------------------------
//
TUid CBCTestAppFrmApp::AppDllUid() const
    {
    return KUidBCTestAppFrm;
    }

// ----------------------------------------------------------------------------
// CApaDocument* CBCTestAppFrmApp::CreateDocumentL()
// Creates CBCTestAppFrmDocument object.
// ----------------------------------------------------------------------------
//
CApaDocument* CBCTestAppFrmApp::CreateDocumentL()
    {
    return CBCTestAppFrmDocument::NewL( *this );
    }

void CBCTestAppFrmApp::PreDocConstructL()
    {
    CAknApplication::PreDocConstructL();
    }

// ================= OTHER EXPORTED FUNCTIONS =================================
//
// ----------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCTestAppFrmApp.
// Returns: CApaDocument*: created application object
// ----------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestAppFrmApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }


