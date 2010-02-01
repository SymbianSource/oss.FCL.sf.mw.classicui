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
* Description:  signal_pane_api
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknsignal.h>
#include <testdomsignalpane.rsg>
#include <barsread.h>
#include <eikenv.h> 
#include <avkon.hrh>

#include "testdomsignalpane.h"
#include "testdomsignalprotected.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMSignalPane::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDOMSignalPane::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestSPConstructorL", CTestDOMSignalPane::TestSPConstructorL ),
        ENTRY( "TestSPDestructor", CTestDOMSignalPane::TestSPDestructor ),
        ENTRY( "TestSPConstructFromResourceL", CTestDOMSignalPane::TestSPConstructFromResourceL ),
        ENTRY( "TestSPSetSignalLevel", CTestDOMSignalPane::TestSPSetSignalLevel ),
        ENTRY( "TestSPShowGprsIcon", CTestDOMSignalPane::TestSPShowGprsIcon ),
        ENTRY( "TestSPShowCommonPacketDataIcon", CTestDOMSignalPane::TestSPShowCommonPacketDataIcon ),
        ENTRY( "TestSPShowWcdmaIcon", CTestDOMSignalPane::TestSPShowWcdmaIcon ),
        ENTRY( "TestSPShowHsdpaIcon", CTestDOMSignalPane::TestSPShowHsdpaIcon ),
        ENTRY( "TestSPShowCdmaIcon", CTestDOMSignalPane::TestSPShowCdmaIcon ),
        ENTRY( "TestSPShowEdgeIcon", CTestDOMSignalPane::TestSPShowEdgeIcon ),
        ENTRY( "TestSPSetNaviPaneBackgroundType", CTestDOMSignalPane::TestSPSetNaviPaneBackgroundType ),
        ENTRY( "TestSPSizeChangedL", CTestDOMSignalPane::TestSPSizeChangedL ),
        ENTRY( "TestSPPositionChangedL", CTestDOMSignalPane::TestSPPositionChangedL ),
        ENTRY( "TestSPHandleResourceChangeL", CTestDOMSignalPane::TestSPHandleResourceChangeL ),
        ENTRY( "TestSPCountComponentControlsL", CTestDOMSignalPane::TestSPCountComponentControlsL ),
        ENTRY( "TestSPComponentControlL", CTestDOMSignalPane::TestSPComponentControlL ),
        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestDOMSignalPane::TestSPConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestDOMSignalPane::TestSPConstructorL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomsignalpane, "testdomsignalpane" );
    _LIT( KTestSPConstructorL, "In TestSPConstructorL" );
    TestModuleIf().Printf( 0, Ktestdomsignalpane, KTestSPConstructorL );
    // Print to log file
    iLog->Log( KTestSPConstructorL );
    iSignalPane = new ( ELeave ) CAknSignalPane();
    STIF_ASSERT_NOT_NULL( iSignalPane );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMSignalPane::TestSPDestructor
// -----------------------------------------------------------------------------
//
TInt CTestDOMSignalPane::TestSPDestructor( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomsignalpane, "testdomsignalpane" );
    _LIT( KTestSPDestructor, "In TestSPDestructor" );
    TestModuleIf().Printf( 0, Ktestdomsignalpane, KTestSPDestructor );
    // Print to log file
    iLog->Log( KTestSPDestructor );
    delete iSignalPane;
    iSignalPane = NULL;
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMSignalPane::TestSPConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestDOMSignalPane::TestSPConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomsignalpane, "testdomsignalpane" );
    _LIT( KTestSPConstructFromResourceL, "In TestSPConstructFromResourceL" );
    TestModuleIf().Printf( 0, Ktestdomsignalpane, KTestSPConstructFromResourceL );
    // Print to log file
    iLog->Log( KTestSPConstructFromResourceL );
    TResourceReader reader;
    TBool err = KErrNone;
    CEikonEnv::Static()->CreateResourceReaderLC( reader, R_TESTDOMNOTIFIER_VIEW );
    TRAP( err, iSignalPane->ConstructFromResourceL( reader ) );
    CleanupStack::PopAndDestroy();
    return err;
    }
// -----------------------------------------------------------------------------
// CTestDOMSignalPane::TestSPSetSignalLevel
// -----------------------------------------------------------------------------
//
TInt CTestDOMSignalPane::TestSPSetSignalLevel( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomsignalpane, "testdomsignalpane" );
    _LIT( KTestSPSetSignalLevel, "In TestSPSetSignalLevel" );
    TestModuleIf().Printf( 0, Ktestdomsignalpane, KTestSPSetSignalLevel );
    // Print to log file
    iLog->Log( KTestSPSetSignalLevel );
    TInt level = 0;
    iSignalPane->SetSignalLevel( level );

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMSignalPane::TestSPShowGprsIcon
// -----------------------------------------------------------------------------
//
TInt CTestDOMSignalPane::TestSPShowGprsIcon( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomsignalpane, "testdomsignalpane" );
    _LIT( KTestSPShowGprsIcon, "In TestSPShowGprsIcon" );
    TestModuleIf().Printf( 0, Ktestdomsignalpane, KTestSPShowGprsIcon );
    // Print to log file
    iLog->Log( KTestSPShowGprsIcon );

    iSignalPane->ShowGprsIcon( EAknSignalGprsIndicatorOff );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMSignalPane::TestSPShowCommonPacketDataIcon
// -----------------------------------------------------------------------------
//
TInt CTestDOMSignalPane::TestSPShowCommonPacketDataIcon( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomsignalpane, "testdomsignalpane" );
    _LIT( KTestSPShowCommonPacketDataIcon, "In TestSPShowCommonPacketDataIcon" );
    TestModuleIf().Printf( 0, Ktestdomsignalpane, KTestSPShowCommonPacketDataIcon );
    // Print to log file
    iLog->Log( KTestSPShowCommonPacketDataIcon );

    iSignalPane->ShowCommonPacketDataIcon( EAknSignalCommonPacketDataIndicatorOff );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMSignalPane::TestSPShowWcdmaIcon
// -----------------------------------------------------------------------------
//
TInt CTestDOMSignalPane::TestSPShowWcdmaIcon( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomsignalpane, "testdomsignalpane" );
    _LIT( KTestSPShowWcdmaIcon, "In TestSPShowWcdmaIcon" );
    TestModuleIf().Printf( 0, Ktestdomsignalpane, KTestSPShowWcdmaIcon );
    // Print to log file
    iLog->Log( KTestSPShowWcdmaIcon );

    iSignalPane->ShowWcdmaIcon( EAknSignalWcdmaIndicatorOff );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMSignalPane::TestSPShowHsdpaIcon
// -----------------------------------------------------------------------------
//
TInt CTestDOMSignalPane::TestSPShowHsdpaIcon( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomsignalpane, "testdomsignalpane" );
    _LIT( KTestSPShowHsdpaIcon, "In TestSPShowHsdpaIcon" );
    TestModuleIf().Printf( 0, Ktestdomsignalpane, KTestSPShowHsdpaIcon );
    // Print to log file
    iLog->Log( KTestSPShowHsdpaIcon );

    iSignalPane->ShowHsdpaIcon( EAknSignalHsdpaIndicatorOff );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMSignalPane::TestSPShowCdmaIcon
// -----------------------------------------------------------------------------
//
TInt CTestDOMSignalPane::TestSPShowCdmaIcon( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomsignalpane, "testdomsignalpane" );
    _LIT( KTestSPShowCdmaIcon, "In TestSPShowCdmaIcon" );
    TestModuleIf().Printf( 0, Ktestdomsignalpane, KTestSPShowCdmaIcon );
    // Print to log file
    iLog->Log( KTestSPShowCdmaIcon );

    iSignalPane->ShowCdmaIcon( EAknSignalCdmaIndicatorOff );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMSignalPane::TestSPShowEdgeIcon
// -----------------------------------------------------------------------------
//
TInt CTestDOMSignalPane::TestSPShowEdgeIcon( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomsignalpane, "testdomsignalpane" );
    _LIT( KTestSPShowEdgeIcon, "In TestSPShowEdgeIcon" );
    TestModuleIf().Printf( 0, Ktestdomsignalpane, KTestSPShowEdgeIcon );
    // Print to log file
    iLog->Log( KTestSPShowEdgeIcon );

    iSignalPane->ShowEdgeIcon( EAknSignalEdgeIndicatorOff );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMSignalPane::TestSPSetNaviPaneBackgroundType
// -----------------------------------------------------------------------------
//
TInt CTestDOMSignalPane::TestSPSetNaviPaneBackgroundType( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomsignalpane, "testdomsignalpane" );
    _LIT( KTestSPSetNaviPaneBackgroundType, "In TestSPSetNaviPaneBackgroundType" );
    TestModuleIf().Printf( 0, Ktestdomsignalpane, KTestSPSetNaviPaneBackgroundType );
    // Print to log file
    iLog->Log( KTestSPSetNaviPaneBackgroundType );

    iSignalPane->SetNaviPaneBackgroundType( EAknNaviPaneBackgroundTypeNotDefined );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMSignalPane::TestSPSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestDOMSignalPane::TestSPSizeChangedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomsignalpane, "testdomsignalpane" );
    _LIT( KTestSPSizeChangedL, "In TestSPSizeChangedL" );
    TestModuleIf().Printf( 0, Ktestdomsignalpane, KTestSPSizeChangedL );
    // Print to log file
    iLog->Log( KTestSPSizeChangedL );
    CTestDOMSignal* signal = new ( ELeave ) CTestDOMSignal();
    CleanupStack::PushL( signal );
    TResourceReader reader;
    CEikonEnv::Static()->CreateResourceReaderLC( reader, R_TESTDOMNOTIFIER_VIEW );
    signal->ConstructFromResourceL( reader );
    signal->SizeChanged();
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( signal );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMSignalPane::TestSPPositionChangedL
// -----------------------------------------------------------------------------
//
TInt CTestDOMSignalPane::TestSPPositionChangedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomsignalpane, "testdomsignalpane" );
    _LIT( KTestSPPositionChangedL, "In TestSPPositionChangedL" );
    TestModuleIf().Printf( 0, Ktestdomsignalpane, KTestSPPositionChangedL );
    // Print to log file
    iLog->Log( KTestSPPositionChangedL );
    CTestDOMSignal* signal = new ( ELeave ) CTestDOMSignal();
    CleanupStack::PushL( signal );
    TResourceReader reader;
    CEikonEnv::Static()->CreateResourceReaderLC( reader, R_TESTDOMNOTIFIER_VIEW );
    signal->ConstructFromResourceL( reader );
    signal->PositionChanged();
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( signal );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMSignalPane::TestSPHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestDOMSignalPane::TestSPHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomsignalpane, "testdomsignalpane" );
    _LIT( KTestSPHandleResourceChangeL, "In TestSPHandleResourceChangeL" );
    TestModuleIf().Printf( 0, Ktestdomsignalpane, KTestSPHandleResourceChangeL );
    // Print to log file
    iLog->Log( KTestSPHandleResourceChangeL );
    CTestDOMSignal* signal = new ( ELeave ) CTestDOMSignal();
    CleanupStack::PushL( signal );
    TResourceReader reader;
    TInt type = 0;
    CEikonEnv::Static()->CreateResourceReaderLC( reader, R_TESTDOMNOTIFIER_VIEW );
    signal->ConstructFromResourceL( reader );
    signal->HandleResourceChange( type );
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( signal );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMSignalPane::TestSPCountComponentControlsL
// -----------------------------------------------------------------------------
//
TInt CTestDOMSignalPane::TestSPCountComponentControlsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomsignalpane, "testdomsignalpane" );
    _LIT( KTestSPCountComponentControlsL, "In TestSPCountComponentControlsL" );
    TestModuleIf().Printf( 0, Ktestdomsignalpane, KTestSPCountComponentControlsL );
    // Print to log file
    iLog->Log( KTestSPCountComponentControlsL );
    CTestDOMSignal* signal = new ( ELeave ) CTestDOMSignal();
    CleanupStack::PushL( signal );
    TResourceReader reader;

    CEikonEnv::Static()->CreateResourceReaderLC( reader, R_TESTDOMNOTIFIER_VIEW );
    signal->ConstructFromResourceL( reader );
    TInt controls = signal->CountComponentControls();
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( signal );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMSignalPane::TestSPComponentControlL
// -----------------------------------------------------------------------------
//
TInt CTestDOMSignalPane::TestSPComponentControlL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomsignalpane, "testdomsignalpane" );
    _LIT( KTestSPComponentControlL, "In TestSPComponentControlL" );
    TestModuleIf().Printf( 0, Ktestdomsignalpane, KTestSPComponentControlL );
    // Print to log file
    iLog->Log( KTestSPComponentControlL );
    CTestDOMSignal* signal = new ( ELeave ) CTestDOMSignal();
    CleanupStack::PushL( signal );
    TResourceReader reader;

    CEikonEnv::Static()->CreateResourceReaderLC( reader, R_TESTDOMNOTIFIER_VIEW );
    signal->ConstructFromResourceL( reader );
    TInt cIndex = signal->CountComponentControls();
    CCoeControl* controls = signal->ComponentControl( cIndex-1 );
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( signal );
    STIF_ASSERT_NOT_NULL( controls );
    return KErrNone;
    }
//  [End of File]
