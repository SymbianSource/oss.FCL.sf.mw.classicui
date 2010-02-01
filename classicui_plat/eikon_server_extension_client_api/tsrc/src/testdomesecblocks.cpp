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
* Description:  eikon_server_extension_client_api
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <akneiksrvc.h>

#include "testdomesec.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMESEC::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDOMESEC::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestEAUSConstructorL", CTestDOMESEC::TestEAUSConstructorL ),
        ENTRY( "TestEAUSSetSgcParams", CTestDOMESEC::TestEAUSSetSgcParamsL ),
        ENTRY( "TestEAUSBlockServerStatusPaneRedraws",
                CTestDOMESEC::TestEAUSBlockServerStatusPaneRedrawsL ),
        ENTRY( "TestEAUSRedrawServerStatusPane",
                CTestDOMESEC::TestEAUSRedrawServerStatusPaneL ),
        ENTRY( "TestEAUSPrepareForAppExit", CTestDOMESEC::TestEAUSPrepareForAppExitL ),
        ENTRY( "TestEAUSSetSystemFaded", CTestDOMESEC::TestEAUSSetSystemFadedL ),
        ENTRY( "TestEAUSIsSystemFaded", CTestDOMESEC::TestEAUSIsSystemFadedL ),
        ENTRY( "TestEAUSShutdownApps", CTestDOMESEC::TestEAUSShutdownAppsL ),
        ENTRY( "TestEAUSAllowNotifierAppServersToLoad", 
                CTestDOMESEC::TestEAUSAllowNotifierAppServersToLoadL ),
        ENTRY( "TestEAUSDoSynchWaitForAknCapServer", 
                CTestDOMESEC::TestEAUSDoSynchWaitForAknCapServerL ),
        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestDOMESEC::TestEAUSConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestDOMESEC::TestEAUSConstructorL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomesec, "testdomesec" );
    _LIT( KTestEAUSConstructorL, "In TestEAUSConstructorL" );
    TestModuleIf().Printf( 0, Ktestdomesec, KTestEAUSConstructorL );
    // Print to log file
    iLog->Log( KTestEAUSConstructorL );
    RAknEikAppUiSession uiSession;
    TInt err = uiSession.Connect();

    uiSession.Close();
    return err;
    }
// -----------------------------------------------------------------------------
// CTestDOMESEC::TestEAUSSetSgcParamsL
// -----------------------------------------------------------------------------
//
TInt CTestDOMESEC::TestEAUSSetSgcParamsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomesec, "testdomesec" );
    _LIT( KTestEAUSSetSgcParams, "In TestEAUSSetSgcParams" );
    TestModuleIf().Printf( 0, Ktestdomesec, KTestEAUSSetSgcParams );
    // Print to log file
    iLog->Log( KTestEAUSSetSgcParams );
    TBitFlags flags;
    TInt spLayout = 0;
    TInt spFlags = 0;
    RAknEikAppUiSession uiSession;
    TInt err = uiSession.Connect();
    CleanupClosePushL( uiSession );
    uiSession.SetSgcParams( CCoeEnv::Static()->RootWin().Identifier(), flags, spLayout, spFlags );
    CleanupStack::Pop();
    uiSession.Close();
    return err;
    }
// -----------------------------------------------------------------------------
// CTestDOMESEC::TestEAUSBlockServerStatusPaneRedrawsL
// -----------------------------------------------------------------------------
//
TInt CTestDOMESEC::TestEAUSBlockServerStatusPaneRedrawsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomesec, "testdomesec" );
    _LIT( KTestEAUSBlockServerStatusPaneRedraws, "In TestEAUSBlockServerStatusPaneRedraws" );
    TestModuleIf().Printf( 0, Ktestdomesec, KTestEAUSBlockServerStatusPaneRedraws );
    // Print to log file
    iLog->Log( KTestEAUSBlockServerStatusPaneRedraws );
    RAknEikAppUiSession uiSession;
    TInt err = uiSession.Connect();
    CleanupClosePushL( uiSession );
    uiSession.BlockServerStatusPaneRedraws();
    CleanupStack::Pop();
    uiSession.Close();
    return err;
    }
// -----------------------------------------------------------------------------
// CTestDOMESEC::TestEAUSRedrawServerStatusPaneL
// -----------------------------------------------------------------------------
//
TInt CTestDOMESEC::TestEAUSRedrawServerStatusPaneL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomesec, "testdomesec" );
    _LIT( KTestEAUSRedrawServerStatusPane, "In TestEAUSRedrawServerStatusPane" );
    TestModuleIf().Printf( 0, Ktestdomesec, KTestEAUSRedrawServerStatusPane );
    // Print to log file
    iLog->Log( KTestEAUSRedrawServerStatusPane );
    RAknEikAppUiSession uiSession;
    TInt err = uiSession.Connect();
    CleanupClosePushL( uiSession );
    uiSession.RedrawServerStatusPane();
    CleanupStack::Pop();
    uiSession.Close();
    return err;
    }
// -----------------------------------------------------------------------------
// CTestDOMESEC::TestEAUSPrepareForAppExitL
// -----------------------------------------------------------------------------
//
TInt CTestDOMESEC::TestEAUSPrepareForAppExitL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomesec, "testdomesec" );
    _LIT( KTestEAUSPrepareForAppExit, "In TestEAUSPrepareForAppExit" );
    TestModuleIf().Printf( 0, Ktestdomesec, KTestEAUSPrepareForAppExit );
    // Print to log file
    iLog->Log( KTestEAUSPrepareForAppExit );
    RAknEikAppUiSession uiSession;
    TInt err = uiSession.Connect();
    CleanupClosePushL( uiSession );
    uiSession.PrepareForAppExit( CCoeEnv::Static()->RootWin().Identifier() );
    CleanupStack::Pop();
    uiSession.Close();
    return err;
    }
// -----------------------------------------------------------------------------
// CTestDOMESEC::TestEAUSSetSystemFadedL
// -----------------------------------------------------------------------------
//
TInt CTestDOMESEC::TestEAUSSetSystemFadedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomesec, "testdomesec" );
    _LIT( KTestEAUSSetSystemFaded, "In TestEAUSSetSystemFaded" );
    TestModuleIf().Printf( 0, Ktestdomesec, KTestEAUSSetSystemFaded );
    // Print to log file
    iLog->Log( KTestEAUSSetSystemFaded );
    RAknEikAppUiSession uiSession;
    TInt err = uiSession.Connect();
    CleanupClosePushL( uiSession );
    uiSession.SetSystemFaded( ETrue );
    CleanupStack::Pop();
    uiSession.Close();
    return err;
    }
// -----------------------------------------------------------------------------
// CTestDOMESEC::TestEAUSIsSystemFadedL
// -----------------------------------------------------------------------------
//
TInt CTestDOMESEC::TestEAUSIsSystemFadedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomesec, "testdomesec" );
    _LIT( KTestEAUSIsSystemFaded, "In TestEAUSIsSystemFaded" );
    TestModuleIf().Printf( 0, Ktestdomesec, KTestEAUSIsSystemFaded );
    // Print to log file
    iLog->Log( KTestEAUSIsSystemFaded );
    TBool systemFade;
    RAknEikAppUiSession uiSession;
    TInt err = uiSession.Connect();
    CleanupClosePushL( uiSession );
    uiSession.IsSystemFaded( systemFade );
    CleanupStack::Pop();
    uiSession.Close();
    return err;
    }
// -----------------------------------------------------------------------------
// CTestDOMESEC::TestEAUSShutdownAppsL
// -----------------------------------------------------------------------------
//
TInt CTestDOMESEC::TestEAUSShutdownAppsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomesec, "testdomesec" );
    _LIT( KTestEAUSShutdownApps, "In TestEAUSShutdownApps" );
    TestModuleIf().Printf( 0, Ktestdomesec, KTestEAUSShutdownApps );
    // Print to log file
    iLog->Log( KTestEAUSShutdownApps );
    TUid requesterUID = { 0x00000000 };
    TInt timeoutInMicroseconds = 5;
    RAknEikAppUiSession uiSession;
    
    TInt err = uiSession.Connect();
    CleanupClosePushL( uiSession );
    uiSession.ShutdownApps( requesterUID, timeoutInMicroseconds );
    
    CleanupStack::Pop();
    uiSession.Close();
    return err;
    }
// -----------------------------------------------------------------------------
// CTestDOMESEC::TestEAUSAllowNotifierAppServersToLoadL
// -----------------------------------------------------------------------------
//
TInt CTestDOMESEC::TestEAUSAllowNotifierAppServersToLoadL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomesec, "testdomesec" );
    _LIT( KTestEAUSAllowNotifierAppServersToLoad, "In TestEAUSAllowNotifierAppServersToLoad" );
    TestModuleIf().Printf( 0, Ktestdomesec, KTestEAUSAllowNotifierAppServersToLoad );
    // Print to log file
    iLog->Log( KTestEAUSAllowNotifierAppServersToLoad );
    RAknEikAppUiSession uiSession;

    TInt err = uiSession.Connect();
    CleanupClosePushL( uiSession );

    uiSession.AllowNotifierAppServersToLoad();
    CleanupStack::Pop();
    uiSession.Close();

    return err;
    }
// -----------------------------------------------------------------------------
// CTestDOMESEC::TestEAUSDoSynchWaitForAknCapServerL
// -----------------------------------------------------------------------------
//
TInt CTestDOMESEC::TestEAUSDoSynchWaitForAknCapServerL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomesec, "testdomesec" );
    _LIT( KTestEAUSDoSynchWaitForAknCapServer, "In TestEAUSDoSynchWaitForAknCapServer" );
    TestModuleIf().Printf( 0, Ktestdomesec, KTestEAUSDoSynchWaitForAknCapServer );
    // Print to log file
    iLog->Log( KTestEAUSDoSynchWaitForAknCapServer );
    RAknEikAppUiSession uiSession;
    TInt err = uiSession.Connect();
    CleanupClosePushL( uiSession );
    uiSession.DoSynchWaitForAknCapServer();
    CleanupStack::Pop();
    uiSession.Close();
    return err;
    }
//  [End of File]
