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
* Description:         Avkon UnitEditor test app
*
*/









// INCLUDE FILES
#include "BCTestUnitEditorApp.h"
#include "BCTestUnitEditorDocument.h"
#include <eikstart.h>

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// TUid CBCTestUnitEditorApp::AppDllUid()
// Returns application UID.
// ----------------------------------------------------------------------------
//
TUid CBCTestUnitEditorApp::AppDllUid() const
    {
    return KUidBCTestUnitEditor;
    }

// ----------------------------------------------------------------------------
// CApaDocument* CBCTestUnitEditorApp::CreateDocumentL()
// Creates CBCTestUnitEditorDocument object.
// ----------------------------------------------------------------------------
//
CApaDocument* CBCTestUnitEditorApp::CreateDocumentL()
    {
    return CBCTestUnitEditorDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS =================================
//
// ----------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCTestUnitEditorApp.
// Returns: CApaDocument*: created application object
// ----------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestUnitEditorApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }

// End of File
