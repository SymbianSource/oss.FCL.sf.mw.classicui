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
* Description:  emergency_call_support
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknecs.h>

#include "testdomemergencycallsupport.h"
#include "testdomecsprotectedclass.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMEmergencyCallSupport::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDOMEmergencyCallSupport::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestEDNewL", CTestDOMEmergencyCallSupport::TestEDNewL ),
        ENTRY( "TestEDDestructor", CTestDOMEmergencyCallSupport::TestEDDestructor ),
        ENTRY( "TestEDHandleWsEventL", CTestDOMEmergencyCallSupport::TestEDHandleWsEventL ),
        ENTRY( "TestEDAddChar", CTestDOMEmergencyCallSupport::TestEDAddChar ),
        ENTRY( "TestEDSetBuffer", CTestDOMEmergencyCallSupport::TestEDSetBuffer ),
        ENTRY( "TestEDReset", CTestDOMEmergencyCallSupport::TestEDReset ),
        ENTRY( "TestEDState", CTestDOMEmergencyCallSupport::TestEDState ),
        ENTRY( "TestEDCurrentMatch", CTestDOMEmergencyCallSupport::TestEDCurrentMatch ),
        ENTRY( "TestEDSetObserver", CTestDOMEmergencyCallSupport::TestEDSetObserver ),
        ENTRY( "TestEDConnectToEventSource", CTestDOMEmergencyCallSupport::TestEDConnectToEventSource ),
        ENTRY( "TestEDCloseEventSource", CTestDOMEmergencyCallSupport::TestEDCloseEventSource ),
        ENTRY( "TestEDConstructorL", CTestDOMEmergencyCallSupport::TestEDConstructorL ),
        ENTRY( "TestEDConstructL", CTestDOMEmergencyCallSupport::TestEDConstructL ),
        ENTRY( "TestEDReportEventL", CTestDOMEmergencyCallSupport::TestEDReportEventL ),
        ENTRY( "TestEDSetStateL", CTestDOMEmergencyCallSupport::TestEDSetStateL ),
        ENTRY( "TestEDOfferEmergencyCallL", CTestDOMEmergencyCallSupport::TestEDOfferEmergencyCallL ),


        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestDOMEmergencyCallSupport::TestEDNewL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEmergencyCallSupport::TestEDNewL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomemergencycallsupport, "testdomemergencycallsupport" );
    _LIT( KTestEDNewL, "In TestEDNewL" );
    TestModuleIf().Printf( 0, Ktestdomemergencycallsupport, KTestEDNewL );
    // Print to log file
    iLog->Log( KTestEDNewL );

    iEcsDetector = CAknEcsDetector::NewL();
    STIF_ASSERT_NOT_NULL( iEcsDetector );

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMEmergencyCallSupport::TestEDDestructor
// -----------------------------------------------------------------------------
//
TInt CTestDOMEmergencyCallSupport::TestEDDestructor( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomemergencycallsupport, "testdomemergencycallsupport" );
    _LIT( KTestEDDestructor, "In TestEDDestructor" );
    TestModuleIf().Printf( 0, Ktestdomemergencycallsupport, KTestEDDestructor );
    // Print to log file
    iLog->Log( KTestEDDestructor );

    delete iEcsDetector;
    iEcsDetector = NULL;
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMEmergencyCallSupport::TestEDHandleWsEventL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEmergencyCallSupport::TestEDHandleWsEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomemergencycallsupport, "testdomemergencycallsupport" );
    _LIT( KTestEDHandleWsEventL, "In TestEDHandleWsEventL" );
    TestModuleIf().Printf( 0, Ktestdomemergencycallsupport, KTestEDHandleWsEventL );
    // Print to log file
    iLog->Log( KTestEDHandleWsEventL );
    TBool err = KErrNone;
    TWsEvent wsEvent;
    wsEvent.SetType( EEventNull );
    TRAP( err, iEcsDetector->HandleWsEventL( wsEvent, NULL ) );
    return err;
    }
// -----------------------------------------------------------------------------
// CTestDOMEmergencyCallSupport::TestEDAddChar
// -----------------------------------------------------------------------------
//
TInt CTestDOMEmergencyCallSupport::TestEDAddChar( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomemergencycallsupport, "testdomemergencycallsupport" );
    _LIT( KTestEDAddChar, "In TestEDAddChar" );
    TestModuleIf().Printf( 0, Ktestdomemergencycallsupport, KTestEDAddChar );
    // Print to log file
    iLog->Log( KTestEDAddChar );

    iEcsDetector->AddChar( EStdKeyYes );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMEmergencyCallSupport::TestEDSetBuffer
// -----------------------------------------------------------------------------
//
TInt CTestDOMEmergencyCallSupport::TestEDSetBuffer( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomemergencycallsupport, "testdomemergencycallsupport" );
    _LIT( KTestEDSetBuffer, "In TestEDSetBuffer" );
    TestModuleIf().Printf( 0, Ktestdomemergencycallsupport, KTestEDSetBuffer );
    // Print to log file
    iLog->Log( KTestEDSetBuffer );
    TBuf<10> newBuf; 
    iEcsDetector->SetBuffer( newBuf );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMEmergencyCallSupport::TestEDReset
// -----------------------------------------------------------------------------
//
TInt CTestDOMEmergencyCallSupport::TestEDReset( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomemergencycallsupport, "testdomemergencycallsupport" );
    _LIT( KTestEDReset, "In TestEDReset" );
    TestModuleIf().Printf( 0, Ktestdomemergencycallsupport, KTestEDReset );
    // Print to log file
    iLog->Log( KTestEDReset );

    iEcsDetector->Reset();
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMEmergencyCallSupport::TestEDState
// -----------------------------------------------------------------------------
//
TInt CTestDOMEmergencyCallSupport::TestEDState( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomemergencycallsupport, "testdomemergencycallsupport" );
    _LIT( KTestEDState, "In TestEDState" );
    TestModuleIf().Printf( 0, Ktestdomemergencycallsupport, KTestEDState );
    // Print to log file
    iLog->Log( KTestEDState );

    CAknEcsDetector::TState state = iEcsDetector->State();

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMEmergencyCallSupport::TestEDCurrentMatch
// -----------------------------------------------------------------------------
//
TInt CTestDOMEmergencyCallSupport::TestEDCurrentMatch( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomemergencycallsupport, "testdomemergencycallsupport" );
    _LIT( KTestEDCurrentMatch, "In TestEDCurrentMatch" );
    TestModuleIf().Printf( 0, Ktestdomemergencycallsupport, KTestEDCurrentMatch );
    // Print to log file
    iLog->Log( KTestEDCurrentMatch );

    TPtrC state = iEcsDetector->CurrentMatch();

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMEmergencyCallSupport::TestEDSetObserver
// -----------------------------------------------------------------------------
//
TInt CTestDOMEmergencyCallSupport::TestEDSetObserver( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomemergencycallsupport, "testdomemergencycallsupport" );
    _LIT( KTestEDSetObserver, "In TestEDSetObserver" );
    TestModuleIf().Printf( 0, Ktestdomemergencycallsupport, KTestEDSetObserver );
    // Print to log file
    iLog->Log( KTestEDSetObserver );

    iEcsDetector->SetObserver( NULL );

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMEmergencyCallSupport::TestEDConnectToEventSource
// -----------------------------------------------------------------------------
//
TInt CTestDOMEmergencyCallSupport::TestEDConnectToEventSource( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomemergencycallsupport, "testdomemergencycallsupport" );
    _LIT( KTestEDConnectToEventSource, "In TestEDConnectToEventSource" );
    TestModuleIf().Printf( 0, Ktestdomemergencycallsupport, KTestEDConnectToEventSource );
    // Print to log file
    iLog->Log( KTestEDConnectToEventSource );

    TBool event = iEcsDetector->ConnectToEventSource();

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMEmergencyCallSupport::TestEDCloseEventSource
// -----------------------------------------------------------------------------
//
TInt CTestDOMEmergencyCallSupport::TestEDCloseEventSource( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomemergencycallsupport, "testdomemergencycallsupport" );
    _LIT( KTestEDCloseEventSource, "In TestEDCloseEventSource" );
    TestModuleIf().Printf( 0, Ktestdomemergencycallsupport, KTestEDCloseEventSource );
    // Print to log file
    iLog->Log( KTestEDCloseEventSource );

    iEcsDetector->CloseEventSource();

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMEmergencyCallSupport::TestEDConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEmergencyCallSupport::TestEDConstructorL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomemergencycallsupport, "testdomemergencycallsupport" );
    _LIT( KTestEDConstructorL, "In TestEDConstructorL" );
    TestModuleIf().Printf( 0, Ktestdomemergencycallsupport, KTestEDConstructorL );
    // Print to log file
    iLog->Log( KTestEDConstructorL );

    CTestEcsDetector* ecsDetector = new ( ELeave ) CTestEcsDetector();
    CleanupStack::PushL( ecsDetector );

    CleanupStack::PopAndDestroy( ecsDetector );

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMEmergencyCallSupport::TestEDConstructL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEmergencyCallSupport::TestEDConstructL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomemergencycallsupport, "testdomemergencycallsupport" );
    _LIT( KTestEDConstructL, "In TestEDConstructL" );
    TestModuleIf().Printf( 0, Ktestdomemergencycallsupport, KTestEDConstructL );
    // Print to log file
    iLog->Log( KTestEDConstructL );

    CTestEcsDetector* ecsDetector = new ( ELeave ) CTestEcsDetector();
    CleanupStack::PushL( ecsDetector );
    ecsDetector->ConstructL();
    CleanupStack::PopAndDestroy( ecsDetector );

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMEmergencyCallSupport::TestEDReportEventL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEmergencyCallSupport::TestEDReportEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomemergencycallsupport, "testdomemergencycallsupport" );
    _LIT( KTestEDReportEventL, "In TestEDReportEventL" );
    TestModuleIf().Printf( 0, Ktestdomemergencycallsupport, KTestEDReportEventL );
    // Print to log file
    iLog->Log( KTestEDReportEventL );

    CTestEcsDetector* ecsDetector = new ( ELeave ) CTestEcsDetector();
    CleanupStack::PushL( ecsDetector );
    ecsDetector->ReportEvent( CAknEcsDetector::ENotFullyConstructed );
    CleanupStack::PopAndDestroy( ecsDetector );

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMEmergencyCallSupport::TestEDSetStateL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEmergencyCallSupport::TestEDSetStateL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomemergencycallsupport, "testdomemergencycallsupport" );
    _LIT( KTestEDSetStateL, "In TestEDSetStateL" );
    TestModuleIf().Printf( 0, Ktestdomemergencycallsupport, KTestEDSetStateL );
    // Print to log file
    iLog->Log( KTestEDSetStateL );

    CTestEcsDetector* ecsDetector = new ( ELeave ) CTestEcsDetector();
    CleanupStack::PushL( ecsDetector );
    ecsDetector->SetState( CAknEcsDetector::ENotFullyConstructed );
    CleanupStack::PopAndDestroy( ecsDetector );

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMEmergencyCallSupport::TestEDOfferEmergencyCallL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEmergencyCallSupport::TestEDOfferEmergencyCallL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomemergencycallsupport, "testdomemergencycallsupport" );
    _LIT( KTestEDOfferEmergencyCallL, "In TestEDOfferEmergencyCallL" );
    TestModuleIf().Printf( 0, Ktestdomemergencycallsupport, KTestEDOfferEmergencyCallL );
    // Print to log file
    iLog->Log( KTestEDOfferEmergencyCallL );

    CTestEcsDetector* ecsDetector = new ( ELeave ) CTestEcsDetector();
    CleanupStack::PushL( ecsDetector );
    TBool detectot = ecsDetector->OfferEmergencyCall();
    CleanupStack::PopAndDestroy( ecsDetector );

    return KErrNone;
    }
//  [End of File]
