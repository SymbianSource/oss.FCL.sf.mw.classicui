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
* Description:  test function implement of CTestDomLayoutCfg
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknlayoutconfig.h>
#include <aknsgcc.h>

#include "testdomlayoutcfg.h"


// CONSTANTS
const TInt KScreenModeNumber = 0;
const TInt KHardwareStateNumber = 0;


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomLayoutCfg::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDomLayoutCfg::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        // for TScreenMode of CAknLayoutConfig in AknLayoutConfig.h
        ENTRY( "TestTSMPixelsTwipsAndRotation",
                CTestDomLayoutCfg::TestTSMPixelsTwipsAndRotationL ),
        ENTRY( "TestTSMSoftkeyLocation",
                CTestDomLayoutCfg::TestTSMSoftkeyLocationL ),
        ENTRY( "TestTSMScreenStyleHash",
                CTestDomLayoutCfg::TestTSMScreenStyleHashL ),

        // for TScreenModeArray of CAknLayoutConfig in AknLayoutConfig.h
        ENTRY( "TestTSMAAt",
                CTestDomLayoutCfg::TestTSMAAtL ),
        ENTRY( "TestTSMAFind",
                CTestDomLayoutCfg::TestTSMAFindL ),

        // for THardwareState of CAknLayoutConfig in AknLayoutConfig.h
        ENTRY( "TestTHSStateNumber",
                CTestDomLayoutCfg::TestTHSStateNumberL ),
        ENTRY( "TestTHSKeyCode",
                CTestDomLayoutCfg::TestTHSKeyCodeL ),
        ENTRY( "TestTHSScreenMode",
                CTestDomLayoutCfg::TestTHSScreenModeL ),
        ENTRY( "TestTHSAlternateScreenMode",
                CTestDomLayoutCfg::TestTHSAlternateScreenModeL ),

        // for THardwareStateArray of CAknLayoutConfig in AknLayoutConfig.h
        ENTRY( "TestTHSACount",
                CTestDomLayoutCfg::TestTHSACountL ),
        ENTRY( "TestTHSAAt",
                CTestDomLayoutCfg::TestTHSAAtL ),
        ENTRY( "TestTHSAFind",
                CTestDomLayoutCfg::TestTHSAFindL ),

        // for CAknLayoutConfig in AknLayoutConfig.h
        ENTRY( "TestCALCHardwareStates",
                CTestDomLayoutCfg::TestCALCHardwareStatesL ),
        ENTRY( "TestCALCScreenModes",
                CTestDomLayoutCfg::TestCALCScreenModesL ),
        ENTRY( "TestCALCConstructorL",
                CTestDomLayoutCfg::TestCALCConstructorL ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestDomLayoutCfg::TestTSMPixelsTwipsAndRotationL
// -----------------------------------------------------------------------------
//
TInt CTestDomLayoutCfg::TestTSMPixelsTwipsAndRotationL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomLayoutCfg, "TestDomLayoutCfg" );
    _LIT( KTestCAknLCPixelsTwipsAndRotation, "TestCAknLCPixelsTwipsAndRotation" );
    TestModuleIf().Printf( 0, KTestDomLayoutCfg, KTestCAknLCPixelsTwipsAndRotation );
    // Print to log file
    iLog->Log( KTestCAknLCPixelsTwipsAndRotation );
    
    CAknLayoutConfig* layoutCfg = CAknLayoutConfig::NewL();
    CleanupStack::PushL( layoutCfg );
    STIF_ASSERT_NOT_NULL( layoutCfg );
    CAknLayoutConfig::TScreenModeArray modeArray = layoutCfg->ScreenModes();
    CAknLayoutConfig::TScreenMode scrMode = modeArray.Find( KScreenModeNumber );
    scrMode.PixelsTwipsAndRotation();
    CleanupStack::PopAndDestroy( layoutCfg );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomLayoutCfg::TestTSMSoftkeyLocationL
// -----------------------------------------------------------------------------
//
TInt CTestDomLayoutCfg::TestTSMSoftkeyLocationL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomLayoutCfg, "TestDomLayoutCfg" );
    _LIT( KTestTSMSoftkeyLocation, "TestTSMSoftkeyLocation" );
    TestModuleIf().Printf( 0, KTestDomLayoutCfg, KTestTSMSoftkeyLocation );
    // Print to log file
    iLog->Log( KTestTSMSoftkeyLocation );
    
    CAknLayoutConfig* layoutCfg = CAknLayoutConfig::NewL();
    CleanupStack::PushL( layoutCfg );
    STIF_ASSERT_NOT_NULL( layoutCfg );
    CAknLayoutConfig::TScreenModeArray modeArray = layoutCfg->ScreenModes();
    CAknLayoutConfig::TScreenMode scrMode = modeArray.Find( KScreenModeNumber );
    scrMode.SoftkeyLocation();
    CleanupStack::PopAndDestroy( layoutCfg );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomLayoutCfg::TestTSMScreenStyleHashL
// -----------------------------------------------------------------------------
//
TInt CTestDomLayoutCfg::TestTSMScreenStyleHashL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomLayoutCfg, "TestDomLayoutCfg" );
    _LIT( KTestCAknLCScreenStyleHash, "TestCAknLCScreenStyleHash" );
    TestModuleIf().Printf( 0, KTestDomLayoutCfg, KTestCAknLCScreenStyleHash );
    // Print to log file
    iLog->Log( KTestCAknLCScreenStyleHash );
    
    CAknLayoutConfig* layoutCfg = CAknLayoutConfig::NewL();
    CleanupStack::PushL( layoutCfg );
    STIF_ASSERT_NOT_NULL( layoutCfg );
    CAknLayoutConfig::TScreenModeArray modeArray = layoutCfg->ScreenModes();
    CAknLayoutConfig::TScreenMode scrMode = modeArray.Find( KScreenModeNumber );
    scrMode.ScreenStyleHash();
    CleanupStack::PopAndDestroy( layoutCfg );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomLayoutCfg::TestTSMAAtL
// -----------------------------------------------------------------------------
//
TInt CTestDomLayoutCfg::TestTSMAAtL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomLayoutCfg, "TestDomLayoutCfg" );
    _LIT( KTestTSMAAt, "TestTSMAAt" );
    TestModuleIf().Printf( 0, KTestDomLayoutCfg, KTestTSMAAt );
    // Print to log file
    iLog->Log( KTestTSMAAt );
    
    CAknLayoutConfig* layoutCfg = CAknLayoutConfig::NewL();
    CleanupStack::PushL( layoutCfg );
    STIF_ASSERT_NOT_NULL( layoutCfg );
    CAknLayoutConfig::TScreenModeArray modeArray = layoutCfg->ScreenModes();
    modeArray.At( KScreenModeNumber );
    CleanupStack::PopAndDestroy( layoutCfg );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomLayoutCfg::TestTSMAFindL
// -----------------------------------------------------------------------------
//
TInt CTestDomLayoutCfg::TestTSMAFindL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomLayoutCfg, "TestDomLayoutCfg" );
    _LIT( KTestTSMAFind, "TestTSMAFind" );
    TestModuleIf().Printf( 0, KTestDomLayoutCfg, KTestTSMAFind );
    // Print to log file
    iLog->Log( KTestTSMAFind );
    
    CAknLayoutConfig* layoutCfg = CAknLayoutConfig::NewL();
    CleanupStack::PushL( layoutCfg );
    STIF_ASSERT_NOT_NULL( layoutCfg );
    CAknLayoutConfig::TScreenModeArray modeArray = layoutCfg->ScreenModes();
    modeArray.Find( KScreenModeNumber );
    CleanupStack::PopAndDestroy( layoutCfg );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomLayoutCfg::TestTHSStateNumberL
// -----------------------------------------------------------------------------
//
TInt CTestDomLayoutCfg::TestTHSStateNumberL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomLayoutCfg, "TestDomLayoutCfg" );
    _LIT( KTestTHSStateNumber, "TestTHSStateNumber" );
    TestModuleIf().Printf( 0, KTestDomLayoutCfg, KTestTHSStateNumber );
    // Print to log file
    iLog->Log( KTestTHSStateNumber );
    
    CAknLayoutConfig* layoutCfg = CAknLayoutConfig::NewL();
    CleanupStack::PushL( layoutCfg );
    STIF_ASSERT_NOT_NULL( layoutCfg );
    CAknLayoutConfig::THardwareStateArray stateArray = layoutCfg->HardwareStates();
    CAknLayoutConfig::THardwareState state = stateArray.Find( KHardwareStateNumber );
    state.StateNumber();
    CleanupStack::PopAndDestroy( layoutCfg );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomLayoutCfg::TestTHSKeyCodeL
// -----------------------------------------------------------------------------
//
TInt CTestDomLayoutCfg::TestTHSKeyCodeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomLayoutCfg, "TestDomLayoutCfg" );
    _LIT( KTestTHSKeyCode, "TestTHSKeyCode" );
    TestModuleIf().Printf( 0, KTestDomLayoutCfg, KTestTHSKeyCode );
    // Print to log file
    iLog->Log( KTestTHSKeyCode );
    
    CAknLayoutConfig* layoutCfg = CAknLayoutConfig::NewL();
    CleanupStack::PushL( layoutCfg );
    STIF_ASSERT_NOT_NULL( layoutCfg );
    CAknLayoutConfig::THardwareStateArray stateArray = layoutCfg->HardwareStates();
    CAknLayoutConfig::THardwareState state = stateArray.Find( KHardwareStateNumber );
    state.KeyCode();
    CleanupStack::PopAndDestroy( layoutCfg );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomLayoutCfg::TestTHSScreenModeL
// -----------------------------------------------------------------------------
//
TInt CTestDomLayoutCfg::TestTHSScreenModeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomLayoutCfg, "TestDomLayoutCfg" );
    _LIT( KTestTHSScreenMode, "TestTHSScreenMode" );
    TestModuleIf().Printf( 0, KTestDomLayoutCfg, KTestTHSScreenMode );
    // Print to log file
    iLog->Log( KTestTHSScreenMode );
    
    CAknLayoutConfig* layoutCfg = CAknLayoutConfig::NewL();
    CleanupStack::PushL( layoutCfg );
    STIF_ASSERT_NOT_NULL( layoutCfg );
    CAknLayoutConfig::THardwareStateArray stateArray = layoutCfg->HardwareStates();
    CAknLayoutConfig::THardwareState state = stateArray.Find( KHardwareStateNumber );
    state.ScreenMode();
    CleanupStack::PopAndDestroy( layoutCfg );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomLayoutCfg::TestTHSAlternateScreenModeL
// -----------------------------------------------------------------------------
//
TInt CTestDomLayoutCfg::TestTHSAlternateScreenModeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomLayoutCfg, "TestDomLayoutCfg" );
    _LIT( KTestTHSAlternateScreenMode, "TestTHSAlternateScreenMode" );
    TestModuleIf().Printf( 0, KTestDomLayoutCfg, KTestTHSAlternateScreenMode );
    // Print to log file
    iLog->Log( KTestTHSAlternateScreenMode );
    
    CAknLayoutConfig* layoutCfg = CAknLayoutConfig::NewL();
    CleanupStack::PushL( layoutCfg );
    STIF_ASSERT_NOT_NULL( layoutCfg );
    CAknLayoutConfig::THardwareStateArray stateArray = layoutCfg->HardwareStates();
    CAknLayoutConfig::THardwareState state = stateArray.Find( KHardwareStateNumber );
    state.AlternateScreenMode();
    CleanupStack::PopAndDestroy( layoutCfg );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomLayoutCfg::TestTHSACountL
// -----------------------------------------------------------------------------
//
TInt CTestDomLayoutCfg::TestTHSACountL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomLayoutCfg, "TestDomLayoutCfg" );
    _LIT( KTestTHSACount, "TestTHSACount" );
    TestModuleIf().Printf( 0, KTestDomLayoutCfg, KTestTHSACount );
    // Print to log file
    iLog->Log( KTestTHSACount );
    
    CAknLayoutConfig* layoutCfg = CAknLayoutConfig::NewL();
    CleanupStack::PushL( layoutCfg );
    STIF_ASSERT_NOT_NULL( layoutCfg );
    CAknLayoutConfig::THardwareStateArray stateArray = layoutCfg->HardwareStates();
    stateArray.Count();
    CleanupStack::PopAndDestroy( layoutCfg );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomLayoutCfg::TestTHSAAtL
// -----------------------------------------------------------------------------
//
TInt CTestDomLayoutCfg::TestTHSAAtL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomLayoutCfg, "TestDomLayoutCfg" );
    _LIT( KTestTHSAAt, "TestTHSAAt" );
    TestModuleIf().Printf( 0, KTestDomLayoutCfg, KTestTHSAAt );
    // Print to log file
    iLog->Log( KTestTHSAAt );
    
    CAknLayoutConfig* layoutCfg = CAknLayoutConfig::NewL();
    CleanupStack::PushL( layoutCfg );
    STIF_ASSERT_NOT_NULL( layoutCfg );
    CAknLayoutConfig::THardwareStateArray stateArray = layoutCfg->HardwareStates();
    stateArray.At( 1 );
    CleanupStack::PopAndDestroy( layoutCfg );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomLayoutCfg::TestTHSAFindL
// -----------------------------------------------------------------------------
//
TInt CTestDomLayoutCfg::TestTHSAFindL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomLayoutCfg, "TestDomLayoutCfg" );
    _LIT( KTestTHSAFind, "TestTHSAFind" );
    TestModuleIf().Printf( 0, KTestDomLayoutCfg, KTestTHSAFind );
    // Print to log file
    iLog->Log( KTestTHSAFind );
    
    CAknLayoutConfig* layoutCfg = CAknLayoutConfig::NewL();
    CleanupStack::PushL( layoutCfg );
    STIF_ASSERT_NOT_NULL( layoutCfg );
    CAknLayoutConfig::THardwareStateArray stateArray = layoutCfg->HardwareStates();
    stateArray.Find( KHardwareStateNumber );
    CleanupStack::PopAndDestroy( layoutCfg );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomLayoutCfg::TestCALCHardwareStatesL
// -----------------------------------------------------------------------------
//
TInt CTestDomLayoutCfg::TestCALCHardwareStatesL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomLayoutCfg, "TestDomLayoutCfg" );
    _LIT( KTestCALCHardwareStates, "TestCALCHardwareStates" );
    TestModuleIf().Printf( 0, KTestDomLayoutCfg, KTestCALCHardwareStates );
    // Print to log file
    iLog->Log( KTestCALCHardwareStates );
    
    CAknLayoutConfig* layoutCfg = CAknLayoutConfig::NewL();
    CleanupStack::PushL( layoutCfg );
    STIF_ASSERT_NOT_NULL( layoutCfg );
    layoutCfg->HardwareStates();
    CleanupStack::PopAndDestroy( layoutCfg );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomLayoutCfg::TestCALCScreenModesL
// -----------------------------------------------------------------------------
//
TInt CTestDomLayoutCfg::TestCALCScreenModesL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomLayoutCfg, "TestDomLayoutCfg" );
    _LIT( KTestCALCScreenModes, "TestCALCScreenModes" );
    TestModuleIf().Printf( 0, KTestDomLayoutCfg, KTestCALCScreenModes );
    // Print to log file
    iLog->Log( KTestCALCScreenModes );
    
    CAknLayoutConfig* layoutCfg = CAknLayoutConfig::NewL();
    CleanupStack::PushL( layoutCfg );
    STIF_ASSERT_NOT_NULL( layoutCfg );
    layoutCfg->ScreenModes();
    CleanupStack::PopAndDestroy( layoutCfg );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomLayoutCfg::TestCALCConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestDomLayoutCfg::TestCALCConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestDomLayoutCfg, "TestDomLayoutCfg" );
    _LIT( KTestCALCConstructorL, "TestCALCConstructorL" );
    TestModuleIf().Printf( 0, KTestDomLayoutCfg, KTestCALCConstructorL );
    // Print to log file
    iLog->Log( KTestCALCConstructorL );
    
    CAknLayoutConfig* layoutCfg = CAknLayoutConfig::NewL();
    CleanupStack::PushL( layoutCfg );
    STIF_ASSERT_NOT_NULL( layoutCfg );
    CleanupStack::PopAndDestroy( layoutCfg );
    
    return KErrNone;
    }

//  [End of File]
