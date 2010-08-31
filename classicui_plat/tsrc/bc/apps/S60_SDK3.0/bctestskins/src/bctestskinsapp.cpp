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
#include "BCTestSkinsApp.h"
#include "BCTestSkinsDocument.h"
#include <eikstart.h>

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// TUid CBCTestSkinsApp::AppDllUid()
// Returns application UID.
// ----------------------------------------------------------------------------
//
TUid CBCTestSkinsApp::AppDllUid() const
    {
    return KUidBCTestSkins;
    }

// ----------------------------------------------------------------------------
// CApaDocument* CBCTestSkinsApp::CreateDocumentL()
// Creates CBCTestSkinsDocument object.
// ----------------------------------------------------------------------------
//
CApaDocument* CBCTestSkinsApp::CreateDocumentL()
    {
    return CBCTestSkinsDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS =================================
//
// ----------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCTestSkinsApp.
// Returns: CApaDocument*: created application object
// ----------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestSkinsApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }

// End of File
