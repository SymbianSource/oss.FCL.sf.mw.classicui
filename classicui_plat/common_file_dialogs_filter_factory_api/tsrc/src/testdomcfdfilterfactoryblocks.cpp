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
* Description:  for testing the cfd filer factory module
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknfilefilterfactory.h>
#include <testdomcfdfilterfactory.rsg>
#include <coemain.h>
#include <barsread.h>

#include "testdomcfdfilterfactory.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctestdomcfdfilterfactory::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDOMCFDFilterFactory::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
            ENTRY( "TestFFFCreateAttributeFilterLC", 
                CTestDOMCFDFilterFactory::TestFFFCreateAttributeFilterLC ),
            ENTRY( "TestFFFCreateFilenameFilterLC", 
                CTestDOMCFDFilterFactory::TestFFFCreateFilenameFilterLC ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestDOMCFDFilterFactory::TestFFFCreateAttributeFilterLC
// -----------------------------------------------------------------------------
//
TInt CTestDOMCFDFilterFactory::TestFFFCreateAttributeFilterLC( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomcfdfilterfactory, "testdomcfdfilterfactory" );
    _LIT( KTestFFFCreateAttributeFilterLC, "In TestFFFCreateAttributeFilterLC" );
    TestModuleIf().Printf( 0, Ktestdomcfdfilterfactory, KTestFFFCreateAttributeFilterLC );
    // Print to log file
    iLog->Log( KTestFFFCreateAttributeFilterLC );

    MAknFileFilter* fileFilter;
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TEST_ATTRIBUTE_FILTER_FACTORY );
        
    fileFilter = AknFileFilterFactory::CreateFilterLC( reader );
    STIF_ASSERT_NOT_NULL( fileFilter );
    CleanupStack::Pop();
    CleanupStack::PopAndDestroy();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDOMCFDFilterFactory::TestFFFCreateFilenameFilterLC
// -----------------------------------------------------------------------------
//
TInt CTestDOMCFDFilterFactory::TestFFFCreateFilenameFilterLC( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomcfdfilterfactory, "testdomcfdfilterfactory" );
    _LIT( KTestFFFCreateFilenameFilterLC, "In TestFFFCreateFilenameFilterLC" );
    TestModuleIf().Printf( 0, Ktestdomcfdfilterfactory, KTestFFFCreateFilenameFilterLC );
    // Print to log file
    iLog->Log( KTestFFFCreateFilenameFilterLC );

    MAknFileFilter* fileFilter;
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TEST_FILENAME_FILTER_FACTORY );
        
    fileFilter = AknFileFilterFactory::CreateFilterLC( reader );
    STIF_ASSERT_NOT_NULL( fileFilter );
    CleanupStack::Pop();
    CleanupStack::PopAndDestroy();
    
    return KErrNone;
    }

//  [End of File]

