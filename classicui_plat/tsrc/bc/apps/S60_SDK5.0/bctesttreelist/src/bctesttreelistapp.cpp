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
#include "BCTestTreeListApp.h"
#include "BCTestTreeListDocument.h"
#include <eikstart.h>

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// TUid CBCTestTemplateApp::AppDllUid()
// Returns application UID.
// ----------------------------------------------------------------------------
//
TUid CBCTestTreeListApp::AppDllUid() const
    {
    return KUidBCTestTreeList;
    }

// ----------------------------------------------------------------------------
// CApaDocument* CBCTestTemplateApp::CreateDocumentL()
// Creates CBCTestTemplateDocument object.
// ----------------------------------------------------------------------------
//
CApaDocument* CBCTestTreeListApp::CreateDocumentL()
    {
    return CBCTestTreeListDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS =================================
//
// ----------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCTestTemplateApp.
// Returns: CApaDocument*: created application object
// ----------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestTreeListApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }

// End of File
