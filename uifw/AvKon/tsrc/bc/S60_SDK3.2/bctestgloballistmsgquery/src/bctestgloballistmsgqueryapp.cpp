/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Main application class implementation for BCTestGlobalListMsgQuery.
*
*/

// INCLUDE FILES
#include "bctestgloballistmsgqueryapp.h"
#include "bctestgloballistmsgquerydocument.h"
#include <eikstart.h>

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestGlobalListMsgQueryApp::AppDllUid()
// ----------------------------------------------------------------------------
//
TUid CBCTestGlobalListMsgQueryApp::AppDllUid() const
    {
    return KUidBCTestGlobalListMsgQuery;
    }

// ----------------------------------------------------------------------------
// CBCTestGlobalListMsgQueryApp::CreateDocumentL()
// ----------------------------------------------------------------------------
//
CApaDocument* CBCTestGlobalListMsgQueryApp::CreateDocumentL()
    {
    return CBCTestGlobalListMsgQueryDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS =================================
//
// ----------------------------------------------------------------------------
// NewApplication()
// ----------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestGlobalListMsgQueryApp;
    }

// ----------------------------------------------------------------------------
// E32Main()
// ----------------------------------------------------------------------------
//
GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }

// End of file
