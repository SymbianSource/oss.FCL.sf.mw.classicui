/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Application class of bctestsingleclick.
*
*/

#include <eikstart.h>

#include "bctestsingleclickapp.h"
#include "bctestsingleclickdocument.h"


// ================= MEMBER FUNCTIONS ========================================

// ---------------------------------------------------------------------------
// TUid CBCTESTSingleClickApp::AppDllUid()
// Returns application UID.
// ---------------------------------------------------------------------------
//
TUid CBCTESTSingleClickApp::AppDllUid() const
    {
    return KUidBCTESTSingleClick;
    }

// ---------------------------------------------------------------------------
// CApaDocument* CBCTESTSingleClickApp::CreateDocumentL()
// Creates CBCTESTSingleClickDocument object.
// ---------------------------------------------------------------------------
//
CApaDocument* CBCTESTSingleClickApp::CreateDocumentL()
    {
    return CBCTESTSingleClickDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS ================================
//
// ---------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCTESTSingleClickApp.
// Returns: CApaDocument*: created application object
// ---------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTESTSingleClickApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication( NewApplication );
    }

// End of File
