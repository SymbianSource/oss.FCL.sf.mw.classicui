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
* Description:         Application
*
*/









#include <eikstart.h>

#include "BCTestPaneApp.h"
#include "BCTestPaneDocument.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// TUid CBCTestPaneApp::AppDllUid()
// Returns application UID.
// ----------------------------------------------------------------------------
//
TUid CBCTestPaneApp::AppDllUid() const
    {
    return KUidBCTestPane;
    }

// ----------------------------------------------------------------------------
// CApaDocument* CBCTestPaneApp::CreateDocumentL()
// Creates CBCTestPaneDocument object.
// ----------------------------------------------------------------------------
//
CApaDocument* CBCTestPaneApp::CreateDocumentL()
    {
    return CBCTestPaneDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS =================================
//
// ----------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCTestPaneApp.
// Returns: CApaDocument*: created application object
// ----------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestPaneApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }
