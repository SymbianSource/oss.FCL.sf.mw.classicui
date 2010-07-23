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
* Description:         ServiceHandler test app
*
*/









// INCLUDE FILES
#include "bctestservicehandlerapp.h"
#include "bctestservicehandlerdocument.h"
#include <eikstart.h>

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// TUid CBCTestServiceHandlerApp::AppDllUid()
// Returns application UID.
// ----------------------------------------------------------------------------
//
TUid CBCTestServiceHandlerApp::AppDllUid() const
    {
    return KUidBCTestServiceHandler;
    }

// ----------------------------------------------------------------------------
// CApaDocument* CBCTestServiceHandlerApp::CreateDocumentL()
// Creates CBCTestServiceHandlerDocument object.
// ----------------------------------------------------------------------------
//
CApaDocument* CBCTestServiceHandlerApp::CreateDocumentL()
    {
    return CBCTestServiceHandlerDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS =================================
//
// ----------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCTestServiceHandlerApp.
// Returns: CApaDocument*: created application object
// ----------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestServiceHandlerApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }

// End of File
