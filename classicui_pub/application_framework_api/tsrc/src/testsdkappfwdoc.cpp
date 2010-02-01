/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Test application_framework_api
*
*/



// INCLUDE FILES
#include "testsdkappfwdoc.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKAppFWDoc::CTestSDKAppFWDoc
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CTestSDKAppFWDoc::CTestSDKAppFWDoc( CEikApplication& aApp ) : CAknDocument( aApp )
    {
    }

// -----------------------------------------------------------------------------
// Destructor.
// -----------------------------------------------------------------------------
//
CTestSDKAppFWDoc::~CTestSDKAppFWDoc()
    { 
    }

//-----------------------------------------------------------------------------
// CTestSDKAppFWDoc::CreateDocumentL
//-----------------------------------------------------------------------------
//
CApaDocument* CTestSDKAppFWDoc::CreateDocumentL( CApaProcess* /*aProcess*/ )
    {
    return NULL;
    }

//-----------------------------------------------------------------------------
// CTestSDKAppFWDoc::CreateAppUiL
//-----------------------------------------------------------------------------
//
CEikAppUi* CTestSDKAppFWDoc::CreateAppUiL()
    {
    return NULL;
    }

//  End of File
