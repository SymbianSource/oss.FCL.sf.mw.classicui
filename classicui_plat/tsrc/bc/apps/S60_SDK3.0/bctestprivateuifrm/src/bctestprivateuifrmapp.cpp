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
* Description:         Avkon PrivateUIFrm test app
*
*/









// INCLUDE FILES
#include "BCTestPrivateUIFrmApp.h"
#include "BCTestPrivateUIFrmDocument.h"
#include <eikstart.h>

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// TUid CBCTestPrivateUIFrmApp::AppDllUid()
// Returns application UID.
// ----------------------------------------------------------------------------
//
TUid CBCTestPrivateUIFrmApp::AppDllUid() const
    {
    return KUidBCTestPrivateUIFrm;
    }

// ----------------------------------------------------------------------------
// CApaDocument* CBCTestPrivateUIFrmApp::CreateDocumentL()
// Creates CBCTestPrivateUIFrmDocument object.
// ----------------------------------------------------------------------------
//
CApaDocument* CBCTestPrivateUIFrmApp::CreateDocumentL()
    {
    return CBCTestPrivateUIFrmDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS =================================
//
// ----------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCTestPrivateUIFrmApp.
// Returns: CApaDocument*: created application object
// ----------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestPrivateUIFrmApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }

// End of File
