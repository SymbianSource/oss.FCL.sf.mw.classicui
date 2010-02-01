/*
* Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         app
*
*/









#include <eikstart.h>

#include "bctestmix50app.h"
#include "bctestmix50document.h"


// ================= MEMBER FUNCTIONS ========================================

// ---------------------------------------------------------------------------
// TUid CBCTestMix50App::AppDllUid()
// Returns application UID
// ---------------------------------------------------------------------------
//
TUid CBCTestMix50App::AppDllUid() const
    {
    return KUidBCTestMix50;
    }


// ---------------------------------------------------------------------------
// CApaDocument* CBCTestMix50App::CreateDocumentL()
// Creates CBCTestMix50Document object
// ---------------------------------------------------------------------------
//
CApaDocument* CBCTestMix50App::CreateDocumentL()
    {
    return CBCTestMix50Document::NewL( *this );
    }


// ================= OTHER EXPORTED FUNCTIONS ================================
//
// ---------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCTestMix50App
// Returns: CApaDocument*: created application object
// ---------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestMix50App;
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
