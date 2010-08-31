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
* Description:         Avkon KeyLock test app
*
*/









// INCLUDE FILES
#include "BCTestKeyLockApp.h"
#include "BCTestKeyLockDocument.h"
#include <eikstart.h>

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// TUid CBCTestKeyLockApp::AppDllUid()
// Returns application UID.
// ----------------------------------------------------------------------------
//
TUid CBCTestKeyLockApp::AppDllUid() const
    {
    return KUidBCTestKeyLock;
    }

// ----------------------------------------------------------------------------
// CApaDocument* CBCTestKeyLockApp::CreateDocumentL()
// Creates CBCTestKeyLockDocument object.
// ----------------------------------------------------------------------------
//
CApaDocument* CBCTestKeyLockApp::CreateDocumentL()
    {
    return CBCTestKeyLockDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS =================================
//
// ----------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCTestKeyLockApp.
// Returns: CApaDocument*: created application object
// ----------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestKeyLockApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }

// End of File
