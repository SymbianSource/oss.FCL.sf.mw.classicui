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
#include "BCTestEikFrmApp.h"
#include "BCTestEikFrmDocument.h"
#include <eikstart.h>

// ================= MEMBER FUNCTIONS =========================================

CBCTestEikFrmApp::CBCTestEikFrmApp():CEikApplication()
	{
	}

// ----------------------------------------------------------------------------
// TUid CBCTestEikFrmApp::AppDllUid()
// Returns application UID.
// ----------------------------------------------------------------------------
//
TUid CBCTestEikFrmApp::AppDllUid() const
    {
    return KUidBCTestTemplate;
    }

// ----------------------------------------------------------------------------
// CApaDocument* CBCTestEikFrmApp::CreateDocumentL()
// Creates CBCTestTemplateDocument object.
// ----------------------------------------------------------------------------
//
CApaDocument* CBCTestEikFrmApp::CreateDocumentL()
    {
    return CBCTestEikFrmDocument::NewL( *this );
    }

void CBCTestEikFrmApp::NewAppServerL(CApaAppServer*& aAppServer)
	{
	CBCTestEikFrmApp::NewAppServerL(aAppServer);
	}

// ================= OTHER EXPORTED FUNCTIONS =================================
//
// ----------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCTestEikFrmApp.
// Returns: CApaDocument*: created application object
// ----------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestEikFrmApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }

// End of File
