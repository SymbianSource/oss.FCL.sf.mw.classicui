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
* Description:  test errorui.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <errorui.h>

#include "testsdkerrui.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKErrorUI::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKErrorUI::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "testErrorNote", CTestSDKErrorUI::TestErrUIErrorNoteL ),
        ENTRY( "testErrorQuery", CTestSDKErrorUI::TestErrUIErrorQueryL ),
        ENTRY( "testNewL", CTestSDKErrorUI::TestErrUINewL ),
        ENTRY( "testNewLC", CTestSDKErrorUI::TestErrUINewLCL ),
        ENTRY( "testNewLWithParam", CTestSDKErrorUI::TestErrUINewLWithParamL ),
        ENTRY( "testNewLCWithParam", CTestSDKErrorUI::TestErrUINewLCWithParamL ),
        ENTRY( "testTextResolver", CTestSDKErrorUI::TestErrUITextResolverL ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestSDKErrorUI::TestErrorNoteL
// -----------------------------------------------------------------------------
//
TInt CTestSDKErrorUI::TestErrUIErrorNoteL( CStifItemParser& /*aItem*/ )
    {

    CErrorUI* errui = CErrorUI::NewL();
    CleanupStack::PushL( errui );

    TInt err = KErrDiskFull;
    errui->ShowGlobalErrorNoteL( err );
    CleanupStack::PopAndDestroy( errui );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKErrorUI::TestErrorQueryL
// -----------------------------------------------------------------------------
//
TInt CTestSDKErrorUI::TestErrUIErrorQueryL( CStifItemParser& /*aItem*/ )
    {
    CErrorUI* errui = CErrorUI::NewL();
    CleanupStack::PushL( errui );

    TInt err = KErrNoMemory;
    errui->ShowGlobalErrorQueryL( err );

    CleanupStack::PopAndDestroy( errui );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKErrorUI::TestNewLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKErrorUI::TestErrUINewL( CStifItemParser& /*aItem*/ )
    {
    CErrorUI* errui = CErrorUI::NewL();
    CleanupStack::PushL( errui );

    STIF_ASSERT_NOT_NULL( errui );

    CleanupStack::PopAndDestroy( errui );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKErrorUI::TestNewLCL
// -----------------------------------------------------------------------------
//
TInt CTestSDKErrorUI::TestErrUINewLCL( CStifItemParser& /*aItem*/ )
    {
    CErrorUI* errui = CErrorUI::NewLC();
    STIF_ASSERT_NOT_NULL( errui );

    CleanupStack::PopAndDestroy( errui );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKErrorUI::TestNewLWithParamL
// -----------------------------------------------------------------------------
//
TInt CTestSDKErrorUI::TestErrUINewLWithParamL( CStifItemParser& /*aItem*/ )
    {
    CCoeEnv* coeenv = CCoeEnv::Static();
    CErrorUI* errui = CErrorUI::NewL( *coeenv );
    CleanupStack::PushL( errui );

    STIF_ASSERT_NOT_NULL( errui );

    CleanupStack::PopAndDestroy( errui );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKErrorUI::TestNewLCWithParamL
// -----------------------------------------------------------------------------
//
TInt CTestSDKErrorUI::TestErrUINewLCWithParamL( CStifItemParser& /*aItem*/ )
    {
    CCoeEnv* coeenv = CCoeEnv::Static();
    CErrorUI* errui = CErrorUI::NewLC( *coeenv );

    STIF_ASSERT_NOT_NULL( errui );

    CleanupStack::PopAndDestroy( errui );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKErrorUI::TestTextResolverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKErrorUI::TestErrUITextResolverL( CStifItemParser& /*aItem*/ )
    {
    CErrorUI* errui = CErrorUI::NewL();
    CleanupStack::PushL( errui );

    CTextResolver* resolver = NULL;
    resolver = &( errui->TextResolver() );
    
    STIF_ASSERT_NOT_NULL( resolver );

    CleanupStack::PopAndDestroy( errui );
    return KErrNone;

    }


//  [End of File]
