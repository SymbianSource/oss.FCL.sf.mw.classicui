/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test aknsgcc.h
*
*/



#include <aknsgcc.h>
#include <aknconsts.h>

#include "testdomstatuspane.h"
#include "testdomstatuspanecontrol.h"

// CONSTANTS
const TInt KBufSize = 32;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestSgccCreateL
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestSgccCreateL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestSgccCreateL, "In SgccCreateL" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestSgccCreateL );
    // Print to log file
    iLog->Log( KTestSgccCreateL );

    CAknSgcClient::CreateL();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestSgccHandleChangeL
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestSgccHandleChangeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestSgccHandleChangeL, "In SgccHandleChangeL" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestSgccHandleChangeL );
    // Print to log file
    iLog->Log( KTestSgccHandleChangeL );

    CAknSgcClient::HandleChangeL();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestSgccAknSrvL
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestSgccAknSrvL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestSgccAknSrv, "In SgccAknSrv" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestSgccAknSrv );
    // Print to log file
    iLog->Log( KTestSgccAknSrv );

    RAknUiServer* srv = CAknSgcClient::AknSrv();
    STIF_ASSERT_NOT_NULL( srv );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestSgccSetStatusPaneRedrawCoordinator
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestSgccSetStatusPaneRedrawCoordinator( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestSgccSetStatusPaneRedrawCoordinator, "In SgccSetStatusPaneRedrawCoordinator" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestSgccSetStatusPaneRedrawCoordinator );
    // Print to log file
    iLog->Log( KTestSgccSetStatusPaneRedrawCoordinator );

    CAknSgcClient::SetStatusPaneRedrawCoordinator( NULL );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestSgccBlockServerStatusPaneRedrawsL
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestSgccBlockServerStatusPaneRedrawsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestSgccBlockServerStatusPaneRedrawsL, "In SgccBlockServerStatusPaneRedrawsL" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestSgccBlockServerStatusPaneRedrawsL );
    // Print to log file
    iLog->Log( KTestSgccBlockServerStatusPaneRedrawsL );

    CAknSgcClient::BlockServerStatusPaneRedrawsL();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestSgccRedrawServerStatusPane
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestSgccRedrawServerStatusPane( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestSgccRedrawServerStatusPane, "In SgccRedrawServerStatusPane" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestSgccRedrawServerStatusPane );
    // Print to log file
    iLog->Log( KTestSgccRedrawServerStatusPane );

    CAknSgcClient::RedrawServerStatusPane();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestSgccDrawSynchronizerL
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestSgccDrawSynchronizerL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestSgccDrawSynchronizer, "In SgccDrawSynchronizer" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestSgccDrawSynchronizer );
    // Print to log file
    iLog->Log( KTestSgccDrawSynchronizer );

    CAknDrawSynchronizer* drawSynchronizer = CAknSgcClient::DrawSynchronizer();
    STIF_ASSERT_NOT_NULL( drawSynchronizer );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestSgccPrepareForAppExit
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestSgccPrepareForAppExit( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestSgccPrepareForAppExit, "In SgccPrepareForAppExit" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestSgccPrepareForAppExit );
    // Print to log file
    iLog->Log( KTestSgccPrepareForAppExit );

    CAknSgcClient::PrepareForAppExit();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestSgccSetSystemFaded
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestSgccSetSystemFaded( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestSgccSetSystemFaded, "In SgccSetSystemFaded" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestSgccSetSystemFaded );
    // Print to log file
    iLog->Log( KTestSgccSetSystemFaded );

    CAknSgcClient::SetSystemFaded( ETrue );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestSgccIsSystemFaded
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestSgccIsSystemFaded( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestSgccIsSystemFaded, "In SgccIsSystemFaded" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestSgccIsSystemFaded );
    // Print to log file
    iLog->Log( KTestSgccIsSystemFaded );

    TBool systemFaded = CAknSgcClient::IsSystemFaded();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestSgccPixelsAndRotation
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestSgccPixelsAndRotation( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestSgccPixelsAndRotation, "In SgccPixelsAndRotation" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestSgccPixelsAndRotation );
    // Print to log file
    iLog->Log( KTestSgccPixelsAndRotation );

    TPixelsTwipsAndRotation pixAndRota = CAknSgcClient::PixelsAndRotation();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestSgccCalculatePixelsAndRotation
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestSgccCalculatePixelsAndRotation( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestSgccCalculatePixelsAndRotation, "In SgccCalculatePixelsAndRotation" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestSgccCalculatePixelsAndRotation );
    // Print to log file
    iLog->Log( KTestSgccCalculatePixelsAndRotation );

    TPixelsTwipsAndRotation pixAndRota = CAknSgcClient::
            CalculatePixelsAndRotation( ETrue, ETrue, ETrue, ETrue );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestSgccScreenMode
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestSgccScreenMode( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestSgccScreenMode, "In SgccScreenMode" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestSgccScreenMode );
    // Print to log file
    iLog->Log( KTestSgccScreenMode );

    CAknLayoutConfig::TScreenMode mode = CAknSgcClient::ScreenMode();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestSgccCalculateScreenMode
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestSgccCalculateScreenMode( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestSgccCalculateScreenMode, "In SgccCalculateScreenMode" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestSgccCalculateScreenMode );
    // Print to log file
    iLog->Log( KTestSgccCalculateScreenMode );

    CAknLayoutConfig::TScreenMode mode = CAknSgcClient::
            CalculateScreenMode( ETrue, ETrue, ETrue );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestSgccCalculateScreenModeWithInt
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestSgccCalculateScreenModeWithInt( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestSgccCalculateScreenModeWithInt, "In SgccCalculateScreenModeWithInt" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestSgccCalculateScreenModeWithInt );
    // Print to log file
    iLog->Log( KTestSgccCalculateScreenModeWithInt );

    CAknLayoutConfig::TScreenMode mode = CAknSgcClient::
            CalculateScreenMode( ETrue, ETrue, ETrue, KAknScreenModeUnset );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestSgccSetKeyBlockMode
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestSgccSetKeyBlockMode( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestSgccSetKeyBlockMode, "In SgccSetKeyBlockMode" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestSgccSetKeyBlockMode );
    // Print to log file
    iLog->Log( KTestSgccSetKeyBlockMode );

    CAknSgcClient::SetKeyBlockMode( EEnableKeyBlock );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestSgccSetKeyboardRepeatRate
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestSgccSetKeyboardRepeatRate( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestSgccSetKeyboardRepeatRate, "In SgccSetKeyboardRepeatRate" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestSgccSetKeyboardRepeatRate );
    // Print to log file
    iLog->Log( KTestSgccSetKeyboardRepeatRate );

    CAknSgcClient::SetKeyboardRepeatRate( EAknApplicationDefaulRepeatRate );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestSgccCurrentStatuspaneResource
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestSgccCurrentStatuspaneResource( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestSgccCurrentStatuspaneResource, "In SgccCurrentStatuspaneResource" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestSgccCurrentStatuspaneResource );
    // Print to log file
    iLog->Log( KTestSgccCurrentStatuspaneResource );

    TInt resource = CAknSgcClient::CurrentStatuspaneResource();
    STIF_ASSERT_NOT_EQUALS( 0, resource );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestSgccLayoutConfig
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestSgccLayoutConfig( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestSgccLayoutConfig, "In SgccLayoutConfig" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestSgccLayoutConfig );
    // Print to log file
    iLog->Log( KTestSgccLayoutConfig );

    CAknSgcClient::LayoutConfig();
    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestSgccLayoutConfigBuf
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestSgccLayoutConfigBuf( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestSgccLayoutConfigBuf, "In SgccLayoutConfigBuf" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestSgccLayoutConfigBuf );
    // Print to log file
    iLog->Log( KTestSgccLayoutConfigBuf );

    TBuf8<KBufSize> configBuf = CAknSgcClient::LayoutConfigBuf();
    STIF_ASSERT_TRUE( 0 == configBuf.Length() );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestSgccMoveApp
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestSgccMoveApp( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestSgccMoveApp, "In SgccMoveApp" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestSgccMoveApp );
    // Print to log file
    iLog->Log( KTestSgccMoveApp );

    CAknSgcClient::MoveApp( 0, ESgcMoveAppToForeground );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMStatusPane::TestSgccSetImplL
// -----------------------------------------------------------------------------
//
TInt CTestDOMStatusPane::TestSgccSetImplL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMStatusPane, "testdomstatuspane" );
    _LIT( KTestSgccSetImpl, "In SgccSetImpl" );
    TestModuleIf().Printf( 0, KTestDOMStatusPane, KTestSgccSetImpl );
    // Print to log file
    iLog->Log( KTestSgccSetImpl );

    CAknSgcImplExt* sgcImplExt = new ( ELeave ) CAknSgcImplExt;
    CleanupStack::PushL( sgcImplExt );
    CAknSgcClient::SetImpl( sgcImplExt );

    CleanupStack::PopAndDestroy( sgcImplExt );
    return KErrNone;

    }

