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
* Description:  test function implement of CTestDomExtInit
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testdomextinit.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomExtInit::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDomExtInit::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        // For CAknLibrary in AknLib.h
        ENTRY( "TestCAknLibraryResourceFile",
                CTestDomExtInit::TestCAknLibraryResourceFile ),
        ENTRY( "TestCAknLibraryPrivateResourceFile",
                CTestDomExtInit::TestCAknLibraryPrivateResourceFile ),
        ENTRY( "TestCAknLibraryControlFactory",
                CTestDomExtInit::TestCAknLibraryControlFactory ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomExtInit::TestCAknLibraryResourceFile
// -----------------------------------------------------------------------------
//
TInt CTestDomExtInit::TestCAknLibraryResourceFile( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtButtons, "TestDomInit" );
    _LIT( KTestCAknLibraryResourceFile, "TestCAknLibraryResourceFile" );
    TestModuleIf().Printf( 0, KTestDomExtButtons, KTestCAknLibraryResourceFile );
    // Print to log file
    iLog->Log( KTestCAknLibraryResourceFile );
    
    CAknLibrary::ResourceFile();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtInit::TestCAknLibraryPrivateResourceFile
// -----------------------------------------------------------------------------
//
TInt CTestDomExtInit::TestCAknLibraryPrivateResourceFile( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtInit, "TestDomExtInit" );
    _LIT( KTestCAknLibraryPrivateResourceFile, "TestCAknLibraryPrivateResourceFile" );
    TestModuleIf().Printf( 0, KTestDomExtInit, KTestCAknLibraryPrivateResourceFile );
    // Print to log file
    iLog->Log( KTestCAknLibraryPrivateResourceFile );
    
    CAknLibrary::PrivateResourceFile();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtInit::TestCAknLibraryControlFactory
// -----------------------------------------------------------------------------
//
TInt CTestDomExtInit::TestCAknLibraryControlFactory( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomExtInit, "TestDomExtInit" );
    _LIT( KTestCAknLibraryControlFactory, "TestCAknLibraryControlFactory" );
    TestModuleIf().Printf( 0, KTestDomExtInit, KTestCAknLibraryControlFactory );
    // Print to log file
    iLog->Log( KTestCAknLibraryControlFactory );
    
    CAknLibrary::ControlFactory();
    
    return KErrNone;
    }


//  [End of File]
