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
* Description:         Avkon ScreenClearer test app
*
*/









// INCLUDE FILES
#include <eikstart.h>

#include "bctestscreenclearerapp.h"
#include "bctestscreenclearerdocument.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// TUid CBCTestScreenClearerApp::AppDllUid()
// Returns application UID.
// ----------------------------------------------------------------------------
//
TUid CBCTestScreenClearerApp::AppDllUid() const
    {
    return KUidBCTestScreenClearer;
    }

// ----------------------------------------------------------------------------
// CApaDocument* CBCTestScreenClearerApp::CreateDocumentL()
// Creates CBCTestScreenClearerDocument object.
// ----------------------------------------------------------------------------
//
CApaDocument* CBCTestScreenClearerApp::CreateDocumentL()
    {
    return CBCTestScreenClearerDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS =================================
//
// ----------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCTestScreenClearerApp.
// Returns: CApaDocument*: created application object
// ----------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestScreenClearerApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }
