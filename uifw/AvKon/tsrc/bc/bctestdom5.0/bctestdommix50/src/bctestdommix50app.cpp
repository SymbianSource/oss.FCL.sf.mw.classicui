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

#include "bctestdommix50app.h"
#include "bctestdommix50document.h"


// ================= MEMBER FUNCTIONS ========================================

// ---------------------------------------------------------------------------
// TUid CBCTestDomMix50App::AppDllUid()
// Returns application UID
// ---------------------------------------------------------------------------
//
TUid CBCTestDomMix50App::AppDllUid() const
    {
    return KUidBCTestDomMix50;
    }


// ---------------------------------------------------------------------------
// CBCTestDomMix50App::CreateDocumentL()
// Creates CBCTestDomMix50Document object
// ---------------------------------------------------------------------------
//
CApaDocument* CBCTestDomMix50App::CreateDocumentL()
    {
    return CBCTestDomMix50Document::NewL( *this );
    }


// ================= OTHER EXPORTED FUNCTIONS ================================
//
// ---------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCTestDomMix50App
// Returns: CApaDocument*: created application object
// ---------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestDomMix50App;
    }


// ---------------------------------------------------------------------------
// E32Main
// the main function of this application
// ---------------------------------------------------------------------------
//
GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication( NewApplication );
    }
