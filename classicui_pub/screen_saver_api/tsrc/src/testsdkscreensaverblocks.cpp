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
* Description:  test functions
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testsdkscreensaver.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctestsdkscreensaver::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKScreenSaver::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestSPIDNewL", CTestSDKScreenSaver::TestSPIDNewL ),
        ENTRY( "TestSPIDListImplementationsL",
                CTestSDKScreenSaver::TestSPIDListImplementationsL),
        ENTRY( "TestSPIDDelete", CTestSDKScreenSaver::TestSPIDDelete),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKScreenSaver::TestSPIDNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScreenSaver::TestSPIDNewL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( KSSTestModule, "SSTestModule" );
    _LIT( KSPIDNewL, "In SPIDNewL" );
    TestModuleIf().Printf( 0, KSSTestModule, KSPIDNewL );
    // Print to log file
    iLog->Log( KSPIDNewL );

    const TUid pluginUid = TUid::Uid( 0x1020744D );
    iSPIDef = CScreensaverPluginInterfaceDefinition::NewL( pluginUid );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKScreenSaver::TestSPIDListImplementationsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScreenSaver::TestSPIDListImplementationsL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( KSSTestModule, "SSTestModule" );
    _LIT( KSPIDListImplementations, "In SPIDListImplementationsL" );
    TestModuleIf().Printf( 0, KSSTestModule, KSPIDListImplementations );
    // Print to log file
    iLog->Log( KSPIDListImplementations );

    //Define RImplInfoPtrArray
    RImplInfoPtrArray iArray;
    TInt err = KErrNone;
    TRAP( err, CScreensaverPluginInterfaceDefinition::ListImplementationsL( iArray ));
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKScreenSaver::TestFSDNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScreenSaver::TestSPIDDelete( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( KSSTestModule, "SSTestModule" );
    _LIT( KSPIDDelete, "In SPIDDelete" );
    TestModuleIf().Printf( 0, KSSTestModule, KSPIDDelete );
    // Print to log file
    iLog->Log( KSPIDDelete );

    delete iSPIDef;
    iSPIDef = NULL;

    return KErrNone;
    }

//  [End of File]
