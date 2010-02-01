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
* Description:  battery_pane_api
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <barsread.h>
#include <aknbattery.h>
#include <testdombatterypane.rsg>
#include "testdombatterypane.h"
#include "testdombpprotectedclass.h"



// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMBatteryPane::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDOMBatteryPane::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestDOMBPConstructorL", CTestDOMBatteryPane::TestDOMBPConstructorL ),
        ENTRY( "TestDOMBPDestructor", CTestDOMBatteryPane::TestDOMBPDestructor ),
        ENTRY( "TestDOMBPConstructFromResourceL", 
                CTestDOMBatteryPane::TestDOMBPConstructFromResourceL ),
        ENTRY( "TestDOMBPSetBatteryLevel", CTestDOMBatteryPane::TestDOMBPSetBatteryLevel ),
        ENTRY( "TestDOMBPSizeChangedL", CTestDOMBatteryPane::TestDOMBPSizeChangedL ),
        ENTRY( "TestDOMBPPositionChangedL", CTestDOMBatteryPane::TestDOMBPPositionChangedL ),
        ENTRY( "TestDOMBPHandleResourceChangeL", CTestDOMBatteryPane::TestDOMBPHandleResourceChangeL ),
        ENTRY( "TestDOMBPCountComponentControlsL", CTestDOMBatteryPane::TestDOMBPCountComponentControlsL ),
        ENTRY( "TestDOMBPComponentControlL", CTestDOMBatteryPane::TestDOMBPComponentControlL ),
                
        


        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestDOMBatteryPane::TestDOMBPConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestDOMBatteryPane::TestDOMBPConstructorL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdombatterypane, "testdombatterypane" );
    _LIT( KTestDOMBPConstructorL, "In TestDOMBPConstructorL" );
    TestModuleIf().Printf( 0, Ktestdombatterypane, KTestDOMBPConstructorL );
    // Print to log file
    iLog->Log( KTestDOMBPConstructorL );
    iBatteryPane = new (ELeave) CAknBatteryPane();
    STIF_ASSERT_NOT_NULL( iBatteryPane );

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestDOMBatteryPane::TestDOMBPDestructor
// -----------------------------------------------------------------------------
//
TInt CTestDOMBatteryPane::TestDOMBPDestructor( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdombatterypane, "testdombatterypane" );
    _LIT( KTestDOMBPDestructor, "In TestDOMBPDestructor" );
    TestModuleIf().Printf( 0, Ktestdombatterypane, KTestDOMBPDestructor );
    // Print to log file
    iLog->Log( KTestDOMBPDestructor );
    delete iBatteryPane;
    iBatteryPane = NULL;

    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestDOMBatteryPane::TestDOMBPConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestDOMBatteryPane::TestDOMBPConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdombatterypane, "testdombatterypane" );
    _LIT( KTestDOMBPConstructFromResourceL, "In TestDOMBPConstructFromResourceL" );
    TestModuleIf().Printf( 0, Ktestdombatterypane, KTestDOMBPConstructFromResourceL );
    // Print to log file
    iLog->Log( KTestDOMBPConstructFromResourceL );
    TResourceReader resourceReader;
    CCoeEnv::Static()->CreateResourceReaderLC(resourceReader,R_TESTBATTERY_PANE);
    TBool err = KErrNone;
    TRAP( err, iBatteryPane->ConstructFromResourceL(resourceReader) );
    CleanupStack::PopAndDestroy(); 

    return err;

    }

// -----------------------------------------------------------------------------
// CTestDOMBatteryPane::TestDOMBPSetBatteryLevel
// -----------------------------------------------------------------------------
//
TInt CTestDOMBatteryPane::TestDOMBPSetBatteryLevel( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdombatterypane, "testdombatterypane" );
    _LIT( KTestDOMBPSetBatteryLevel, "In TestDOMBPSetBatteryLevel" );
    TestModuleIf().Printf( 0, Ktestdombatterypane, KTestDOMBPSetBatteryLevel );
    // Print to log file
    iLog->Log( KTestDOMBPSetBatteryLevel );
    TInt level = 0;
    iBatteryPane->SetBatteryLevel( level );
 
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestDOMBatteryPane::TestDOMBPSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestDOMBatteryPane::TestDOMBPSizeChangedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdombatterypane, "testdombatterypane" );
    _LIT( KTestDOMBPSizeChangedL, "In TestDOMBPSizeChangedL" );
    TestModuleIf().Printf( 0, Ktestdombatterypane, KTestDOMBPSizeChangedL );
    // Print to log file
    iLog->Log( KTestDOMBPSizeChangedL );
    CTestBatteryPane* batteryPane = new (ELeave) CTestBatteryPane();
    CleanupStack::PushL( batteryPane );
    

    TResourceReader resourceReader;
    CCoeEnv::Static()->CreateResourceReaderLC(resourceReader,R_TESTBATTERY_PANE);
    TBool err = KErrNone;
    TRAP( err, batteryPane->ConstructFromResourceL(resourceReader) );
    CleanupStack::PopAndDestroy(); 

    batteryPane->CAknBatteryPane::SizeChanged();
    CleanupStack::PopAndDestroy();
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestDOMBatteryPane::TestDOMBPPositionChangedL
// -----------------------------------------------------------------------------
//
TInt CTestDOMBatteryPane::TestDOMBPPositionChangedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdombatterypane, "testdombatterypane" );
    _LIT( KTestDOMBPPositionChangedL, "In TestDOMBPPositionChangedL" );
    TestModuleIf().Printf( 0, Ktestdombatterypane, KTestDOMBPPositionChangedL );
    // Print to log file
    iLog->Log( KTestDOMBPPositionChangedL );

    CTestBatteryPane* batteryPane = new (ELeave) CTestBatteryPane();
    CleanupStack::PushL( batteryPane );

    TResourceReader resourceReader;
    CCoeEnv::Static()->CreateResourceReaderLC(resourceReader, R_TESTBATTERY_PANE);
    TBool err = KErrNone;
    TRAP( err, batteryPane->ConstructFromResourceL(resourceReader) );
    CleanupStack::PopAndDestroy();
    
    batteryPane->CAknBatteryPane::PositionChanged();
    CleanupStack::PopAndDestroy();
 
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestDOMBatteryPane::TestDOMBPHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestDOMBatteryPane::TestDOMBPHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdombatterypane, "testdombatterypane" );
    _LIT( KTestDOMBPHandleResourceChangeL, "In TestDOMBPHandleResourceChange" );
    TestModuleIf().Printf( 0, Ktestdombatterypane, KTestDOMBPHandleResourceChangeL );
    // Print to log file
    iLog->Log( KTestDOMBPHandleResourceChangeL );

    CTestBatteryPane* batteryPane = new (ELeave) CTestBatteryPane();
    CleanupStack::PushL( batteryPane );

    TResourceReader resourceReader;
    CCoeEnv::Static()->CreateResourceReaderLC(resourceReader, R_TESTBATTERY_PANE);
    TBool err = KErrNone;
    TRAP( err, batteryPane->ConstructFromResourceL(resourceReader) );
    CleanupStack::PopAndDestroy();
    TInt type = 0;
    batteryPane->CAknBatteryPane::HandleResourceChange( type );
    CleanupStack::PopAndDestroy();
 
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestDOMBatteryPane::TestDOMBPCountComponentControlsL
// -----------------------------------------------------------------------------
//
TInt CTestDOMBatteryPane::TestDOMBPCountComponentControlsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdombatterypane, "testdombatterypane" );
    _LIT( KTestDOMBPCountComponentControlsL, "In TestDOMBPCountComponentControlsL" );
    TestModuleIf().Printf( 0, Ktestdombatterypane, KTestDOMBPCountComponentControlsL );
    // Print to log file
    iLog->Log( KTestDOMBPCountComponentControlsL );

    CTestBatteryPane* batteryPane = new (ELeave) CTestBatteryPane();
    CleanupStack::PushL( batteryPane );

    TResourceReader resourceReader;
    CCoeEnv::Static()->CreateResourceReaderLC(resourceReader, R_TESTBATTERY_PANE);
    TBool err = KErrNone;
    TRAP( err, batteryPane->ConstructFromResourceL(resourceReader) );
    CleanupStack::PopAndDestroy();
    TInt count = batteryPane->CAknBatteryPane::CountComponentControls();
    CleanupStack::PopAndDestroy();
 
    return KErrNone;

    }
// -----------------------------------------------------------------------------
// CTestDOMBatteryPane::TestDOMBPComponentControlL
// -----------------------------------------------------------------------------
//
TInt CTestDOMBatteryPane::TestDOMBPComponentControlL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdombatterypane, "testdombatterypane" );
    _LIT( KTestDOMBPComponentControlL, "In TestDOMBPComponentControlL" );
    TestModuleIf().Printf( 0, Ktestdombatterypane, KTestDOMBPComponentControlL );
    // Print to log file
    iLog->Log( KTestDOMBPComponentControlL );

    CTestBatteryPane* batteryPane = new (ELeave) CTestBatteryPane();
    CleanupStack::PushL( batteryPane );

    TResourceReader resourceReader;
    CCoeEnv::Static()->CreateResourceReaderLC(resourceReader, R_TESTBATTERY_PANE);
    TBool err = KErrNone;
    TRAP( err, batteryPane->ConstructFromResourceL(resourceReader) );
    CleanupStack::PopAndDestroy();
    TInt cindex = 0;
    CCoeControl* control = batteryPane->CAknBatteryPane::ComponentControl( cindex );
    STIF_ASSERT_NOT_NULL( control );
    CleanupStack::PopAndDestroy();
 
    return KErrNone;

    }
//  [End of File]
