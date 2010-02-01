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
* Description:  test media_shared_document_api
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testdommediashareddoc.h"

_LIT( KFileName, "c:\\panel.txt" );


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomMediaSharedDoc::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDomMediaSharedDoc::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestMSDSetAppModeArgL", CTestDomMediaSharedDoc::TestMSDSetAppModeArgL ),
        ENTRY( "TestMSDGetAppModeArgL", CTestDomMediaSharedDoc::TestMSDGetAppModeArgL ),
        ENTRY( "TestMSDSetFileNameL", CTestDomMediaSharedDoc::TestMSDSetFileNameL ),
        ENTRY( "TestMSDGetFileNameL", CTestDomMediaSharedDoc::TestMSDGetFileNameL ),
        ENTRY( "TestMSDSetAppDataL", CTestDomMediaSharedDoc::TestMSDSetAppDataL ),
        ENTRY( "TestMSDGetAppDataL", CTestDomMediaSharedDoc::TestMSDGetAppDataL ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestDomMediaSharedDoc::TestMSDSetAppModeArgL
// -----------------------------------------------------------------------------
//

TInt CTestDomMediaSharedDoc::TestMSDSetAppModeArgL( CStifItemParser& /*aItem*/ )
    {
    CEikDocument* doc = CEikonEnv::Static()->EikAppUi()->Document();
    CMediaSharedDocument *mediashareddocument = static_cast <CMediaSharedDocument*> ( doc );
    CleanupStack::PushL( mediashareddocument );
    STIF_ASSERT_NOT_NULL( mediashareddocument );
    mediashareddocument->SetAppModeArg( 1 );
    CleanupStack::PopAndDestroy( mediashareddocument );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomMediaSharedDoc::TestMSDGetAppModeArgL
// -----------------------------------------------------------------------------
//

TInt CTestDomMediaSharedDoc::TestMSDGetAppModeArgL( CStifItemParser& /*aItem*/ )
    {
    CEikDocument* doc = CEikonEnv::Static()->EikAppUi()->Document();
    CMediaSharedDocument *mediashareddocument = static_cast <CMediaSharedDocument*> ( doc );
    CleanupStack::PushL( mediashareddocument );
    STIF_ASSERT_NOT_NULL( mediashareddocument );
    mediashareddocument->GetAppModeArg();
    CleanupStack::PopAndDestroy( mediashareddocument );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomMediaSharedDoc::TestMSDSetFileNameL
// -----------------------------------------------------------------------------
//

TInt CTestDomMediaSharedDoc::TestMSDSetFileNameL( CStifItemParser& /*aItem*/ )
    {
    CEikDocument* doc = CEikonEnv::Static()->EikAppUi()->Document();
    CMediaSharedDocument *mediashareddocument = static_cast <CMediaSharedDocument*> ( doc );
    CleanupStack::PushL( mediashareddocument );
    STIF_ASSERT_NOT_NULL( mediashareddocument );
    TFileName FileName( KFileName );
    mediashareddocument->SetFileName( FileName );
    CleanupStack::PopAndDestroy( mediashareddocument );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomMediaSharedDoc::TestMSDGetFileNameL
// -----------------------------------------------------------------------------
//

TInt CTestDomMediaSharedDoc::TestMSDGetFileNameL( CStifItemParser& /*aItem*/ )
    {
    CEikDocument* doc = CEikonEnv::Static()->EikAppUi()->Document();
    CMediaSharedDocument *mediashareddocument = static_cast <CMediaSharedDocument*> ( doc );
    CleanupStack::PushL( mediashareddocument );
    STIF_ASSERT_NOT_NULL( mediashareddocument );
    TFileName FileName( KFileName );
    mediashareddocument->GetFileName( FileName );
    CleanupStack::PopAndDestroy( mediashareddocument );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomMediaSharedDoc::TestMSDSetAppDataL
// -----------------------------------------------------------------------------
//

TInt CTestDomMediaSharedDoc::TestMSDSetAppDataL( CStifItemParser& /*aItem*/ )
    {
    CEikDocument* doc = CEikonEnv::Static()->EikAppUi()->Document();
    CMediaSharedDocument *mediashareddocument = static_cast <CMediaSharedDocument*> ( doc );
    CleanupStack::PushL( mediashareddocument );
    STIF_ASSERT_NOT_NULL( mediashareddocument );
    mediashareddocument->SetAppData( 1 );
    CleanupStack::PopAndDestroy( mediashareddocument );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDomMediaSharedDoc::TestMSDGetAppDataL
// -----------------------------------------------------------------------------
//

TInt CTestDomMediaSharedDoc::TestMSDGetAppDataL( CStifItemParser& /*aItem*/ )
    {
    CEikDocument* doc = CEikonEnv::Static()->EikAppUi()->Document();
    CMediaSharedDocument *mediashareddocument = static_cast <CMediaSharedDocument*> ( doc );
    CleanupStack::PushL( mediashareddocument );
    STIF_ASSERT_NOT_NULL( mediashareddocument );
    mediashareddocument->SetAppData( 1 );
    mediashareddocument->GetAppData();
    CleanupStack::PopAndDestroy( mediashareddocument );
    return KErrNone;
    }


//  [End of File]
