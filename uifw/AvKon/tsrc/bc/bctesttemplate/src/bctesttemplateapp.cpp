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

#include "bctesttemplateapp.h"
#include "bctesttemplatedocument.h"


// ================= MEMBER FUNCTIONS ========================================

// ---------------------------------------------------------------------------
// TUid CBCTestTemplateApp::AppDllUid()
// Returns application UID.
// ---------------------------------------------------------------------------
//
TUid CBCTestTemplateApp::AppDllUid() const
    {
    return KUidBCTestTemplate;
    }

// ---------------------------------------------------------------------------
// CApaDocument* CBCTestTemplateApp::CreateDocumentL()
// Creates CBCTestTemplateDocument object.
// ---------------------------------------------------------------------------
//
CApaDocument* CBCTestTemplateApp::CreateDocumentL()
    {
    return CBCTestTemplateDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS ================================
//
// ---------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCTestTemplateApp.
// Returns: CApaDocument*: created application object
// ---------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestTemplateApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication( NewApplication );
    }

// End of File
