/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies). 
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of the License "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:    test findutil.h
*
*/





// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <findutil.h>

#include "testdomfindutil.h"

// CONSTANTS
const TInt KMaxLength = 10;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMFindUtil::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDOMFindUtil::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestMatchRefineL", CTestDOMFindUtil::TestMatchRefineL ),
        ENTRY( "TestMatch", CTestDOMFindUtil::TestMatchL ),
        ENTRY( "TestIsWordValidForMatching",
                CTestDOMFindUtil::TestIsWordValidForMatchingL ),
        ENTRY( "TestMatchAdaptiveRefineL",
                CTestDOMFindUtil::TestMatchAdaptiveRefineL),

        ENTRY( "TestNewL", CTestDOMFindUtil::TestNewL ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestDOMFindUtil::TestMatchRefineL
// -----------------------------------------------------------------------------
//
TInt CTestDOMFindUtil::TestMatchRefineL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( KTestDOMFindUtil, "testdomfindutil" );
    _LIT( KTestMatchRefineL, "In MatchRefineL" );
    TestModuleIf().Printf( 0, KTestDOMFindUtil, KTestMatchRefineL );
    // Print to log file
    iLog->Log( KTestMatchRefineL );

    CFindUtil* util = CFindUtil::NewL();
    CleanupStack::PushL( util );
    MFindUtil* findUtil = util->Interface();

    TPtrC firstRow, stringToFind;
    aItem.GetNextString( firstRow );
    aItem.GetNextString( stringToFind );

    TInt result = findUtil->MatchRefineL( firstRow, stringToFind );
    STIF_ASSERT_EQUALS( 0, result );

    CleanupStack::PopAndDestroy( util );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMFindUtil::TestMatchL
// -----------------------------------------------------------------------------
//
TInt CTestDOMFindUtil::TestMatchL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( KTestDOMFindUtil, "testdomfindutil" );
    _LIT( KTestMatch, "In Match" );
    TestModuleIf().Printf( 0, KTestDOMFindUtil, KTestMatch );
    // Print to log file
    iLog->Log( KTestMatch );

    CFindUtil* util = CFindUtil::NewL();
    CleanupStack::PushL( util );
    MFindUtil* findUtil = util->Interface();

    TPtrC firstWord, secondWord;
    aItem.GetNextString( firstWord );
    aItem.GetNextString( secondWord );

    TBool result = findUtil->Match( firstWord, secondWord );

    CleanupStack::PopAndDestroy( util );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMFindUtil::TestIsWordValidForMatchingL
// -----------------------------------------------------------------------------
//
TInt CTestDOMFindUtil::TestIsWordValidForMatchingL(
        CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( KTestDOMFindUtil, "testdomfindutil" );
    _LIT( KTestIsWordValidForMatching, "In IsWordValidForMatching" );
    TestModuleIf().Printf( 0, KTestDOMFindUtil, KTestIsWordValidForMatching );
    // Print to log file
    iLog->Log( KTestIsWordValidForMatching );

    CFindUtil* util = CFindUtil::NewL();
    CleanupStack::PushL( util );
    MFindUtil* findUtil = util->Interface();

    TPtrC word;
    aItem.GetNextString( word );

    TBool result = findUtil->IsWordValidForMatching( word );
    STIF_ASSERT_TRUE( result );

    CleanupStack::PopAndDestroy( util );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMFindUtil::TestMatchAdaptiveRefineL
// -----------------------------------------------------------------------------
//
TInt CTestDOMFindUtil::TestMatchAdaptiveRefineL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( KTestDOMFindUtil, "testdomfindutil" );
    _LIT( KTestMatchAdaptiveRefineL, "In MatchAdaptiveRefineL" );
    TestModuleIf().Printf( 0, KTestDOMFindUtil, KTestMatchAdaptiveRefineL );
    // Print to log file
    iLog->Log( KTestMatchAdaptiveRefineL );

    CFindUtil* util = CFindUtil::NewL();
    CleanupStack::PushL( util );
    MFindUtil* findUtil = util->Interface();

    TPtrC firstWord, secondWord, temp;

    HBufC* nextChar = HBufC::NewL( KMaxLength );
    CleanupStack::PushL( nextChar );

    aItem.GetNextString( firstWord );
    aItem.GetNextString( secondWord );
    aItem.GetNextString( temp );
    nextChar->Des().Copy( temp );

    TBool result = findUtil->MatchAdaptiveRefineL( firstWord, secondWord,
            nextChar );
    STIF_ASSERT_FALSE( result );

    CleanupStack::PopAndDestroy( nextChar );
    CleanupStack::PopAndDestroy( util );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMFindUtil::TestNewL
// -----------------------------------------------------------------------------
//
TInt CTestDOMFindUtil::TestNewL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMFindUtil, "testdomfindutil" );
    _LIT( KTestNewL, "In NewL" );
    TestModuleIf().Printf( 0, KTestDOMFindUtil, KTestNewL );
    // Print to log file
    iLog->Log( KTestNewL );

    CFindUtil* findUtil = CFindUtil::NewL();
    CleanupStack::PushL( findUtil );
    STIF_ASSERT_NOT_NULL( findUtil );

    CleanupStack::Pop( findUtil );
    delete findUtil;
    findUtil = NULL;

    return KErrNone;

    }


//  [End of File]
