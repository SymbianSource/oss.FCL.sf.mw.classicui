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
* Description:  Test AknDoc.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testsdkappfw.h"
#include "testsdkappfwdoc.h"

_LIT( KFileName, "C:\\TestFramework\\testframework.ini" );

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestDocOpenFileL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestDocOpenFileL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestDocOpenFileL, "TestDocOpenFileL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestDocOpenFileL );
    // Print to log file
    iLog->Log( KTestDocOpenFileL );

    CEikDocument* doc = iEikonEnvPointer->EikAppUi()->Document();
    RFs& fs = iEikonEnvPointer->FsSession();
    STIF_ASSERT_NULL( doc->OpenFileL( EFalse, KFileName, fs ) );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestDocOpenFileLStoreL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestDocOpenFileLStoreL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestDocOpenFileLStoreL, "TestDocOpenFileLStoreL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestDocOpenFileLStoreL );
    // Print to log file
    iLog->Log( KTestDocOpenFileLStoreL );

    CEikDocument* doc = iEikonEnvPointer->EikAppUi()->Document();
    RFs& fs = iEikonEnvPointer->FsSession();
    CFileStore* store = NULL;
    RFile file;
    doc->OpenFileL( store, file );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestDocCAknDocumentL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestDocCAknDocumentL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestDocCAknDocumentL, "TestDocCAknDocumentL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestDocCAknDocumentL );
    // Print to log file
    iLog->Log( KTestDocCAknDocumentL );

    CEikApplication* app = iEikonEnvPointer->EikAppUi()->Application();
    CTestSDKAppFWDoc* doc = new ( ELeave ) CTestSDKAppFWDoc( *app );
    CleanupStack::PushL( doc );
    STIF_ASSERT_NOT_NULL( doc );
    CleanupStack::PopAndDestroy( doc );

    return KErrNone;

    }

//  [End of File]
