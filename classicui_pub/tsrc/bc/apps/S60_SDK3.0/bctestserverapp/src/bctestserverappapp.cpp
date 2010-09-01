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
#include "BCTestServerappApp.h"
#include "BCTestServerappDocument.h"
#include "BCTestServerappcase.h"
#include <eikstart.h>

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// TUid CBCTestServerappApp::AppDllUid()
// Returns application UID.
// ----------------------------------------------------------------------------
//
TUid CBCTestServerappApp::AppDllUid() const
    {
    return KUidBCTestServerapp;
    }

// ----------------------------------------------------------------------------
// CApaDocument* CBCTestServerappApp::CreateDocumentL()
// Creates CBCTestServerappDocument object.
// ----------------------------------------------------------------------------
//
CApaDocument* CBCTestServerappApp::CreateDocumentL()
    {
    return CBCTestServerappDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS =================================
//
// ----------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCTestServerappApp.
// Returns: CApaDocument*: created application object
// ----------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestServerappApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }
    
/*void CBCTestServerappApp::NewAppServerL(CApaAppServer*& aAppServer)
	{
	aAppServer = new (ELeave) CMySimpleServer;
	}*/

// End of File
