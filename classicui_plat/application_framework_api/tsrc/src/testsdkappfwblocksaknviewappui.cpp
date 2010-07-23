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
* Description:  Test AknViewAppUi.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <testsdkappfw.rsg>

#include "testsdkappfw.h"
#include "testsdkappfwviewappui.h"
#include "testsdkappfwview.h"

// CONSTANTS
const TUid KTestViewId = { 2 };

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewAppUiBaseConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewAppUiBaseConstructL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewAppUiBaseConstructL, "TestViewAppUiBaseConstructL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewAppUiBaseConstructL );
    // Print to log file
    iLog->Log( KTestViewAppUiBaseConstructL );

    CAknViewAppUi* viewAppUi = new ( ELeave ) CAknViewAppUi;
    CleanupStack::PushL( viewAppUi );
    viewAppUi->BaseConstructL( CEikAppUi::ENoAppResourceFile );
    CleanupStack::PopAndDestroy( viewAppUi );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewAppUiActivateLocalViewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewAppUiActivateLocalViewL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewAppUiActivateLocalViewL, "TestViewAppUiActivateLocalViewL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewAppUiActivateLocalViewL );
    // Print to log file
    iLog->Log( KTestViewAppUiActivateLocalViewL );
    CAknViewAppUi* viewAppUi = new ( ELeave ) CAknViewAppUi;
    CleanupStack::PushL( viewAppUi );
    CCoeAppUi* oldappui = CCoeEnv::Static()->AppUi();
    viewAppUi->BaseConstructL( CEikAppUi::ENoAppResourceFile );
    CCoeEnv::Static()->SetAppUi( viewAppUi );
    CTestSDKAppFWView* view = CTestSDKAppFWView::NewL();
    CleanupStack::PushL( view );
    view->BaseConstructL( 0 );
    TInt err = KErrNone;
    TRAP( err, viewAppUi->ActivateLocalViewL( view->Id() ) );
    CCoeEnv::Static()->SetAppUi( oldappui );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewAppUiActivateLocalViewLCustomL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewAppUiActivateLocalViewLCustomL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewAppUiActivateLocalViewLCustomL, "TestViewAppUiActivateLocalViewLCustomL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewAppUiActivateLocalViewLCustomL );
    // Print to log file
    iLog->Log( KTestViewAppUiActivateLocalViewLCustomL );
    // !!! crash
    CAknViewAppUi* viewAppUi = new ( ELeave ) CAknViewAppUi;
    CleanupStack::PushL( viewAppUi );
    viewAppUi->BaseConstructL( CEikAppUi::ENoAppResourceFile );
    STIF_ASSERT_LEAVES( viewAppUi->ActivateLocalViewL( KTestViewId, KNullUid, KNullDesC8 ) );
    CleanupStack::PopAndDestroy( viewAppUi );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewAppUiViewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewAppUiViewL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewAppUiViewL, "TestViewAppUiViewL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewAppUiViewL );
    // Print to log file
    iLog->Log( KTestViewAppUiViewL );

    CAknViewAppUi* viewAppUi = new ( ELeave ) CAknViewAppUi;
    CleanupStack::PushL( viewAppUi );
    viewAppUi->BaseConstructL( CEikAppUi::ENoAppResourceFile );
    STIF_ASSERT_NULL( viewAppUi->View( KTestViewId ) );
    CleanupStack::PopAndDestroy();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewAppUiAddViewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewAppUiAddViewL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewAppUiAddViewL, "TestViewAppUiAddViewL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewAppUiAddViewL );
    // Print to log file
    iLog->Log( KTestViewAppUiAddViewL );

    CAknViewAppUi* viewAppUi = new ( ELeave ) CAknViewAppUi;
    CleanupStack::PushL( viewAppUi );
    viewAppUi->BaseConstructL( CEikAppUi::ENoAppResourceFile );
    viewAppUi->AddViewL( viewAppUi->View( KTestViewId ) );
    CleanupStack::PopAndDestroy();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewAppUiRemoveViewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewAppUiRemoveViewL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewAppUiRemoveViewL, "TestViewAppUiRemoveViewL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewAppUiRemoveViewL );
    // Print to log file
    iLog->Log( KTestViewAppUiRemoveViewL );
// !!! crash
    CAknViewAppUi* viewAppUi = new ( ELeave ) CAknViewAppUi;
    CleanupStack::PushL( viewAppUi );
    viewAppUi->BaseConstructL( CEikAppUi::ENoAppResourceFile );
    CTestSDKAppFWView* view = new( ELeave ) CTestSDKAppFWView;
    CleanupStack::PushL( view );
    view->BaseConstructL();
    CleanupStack::Pop( view );
    viewAppUi->AddViewL( view );
    viewAppUi->RemoveView( KTestViewId );
    CleanupStack::PopAndDestroy();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewAppUiProcessCommandL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewAppUiProcessCommandL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewAppUiProcessCommandL, "TestViewAppUiProcessCommandL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewAppUiProcessCommandL );
    // Print to log file
    iLog->Log( KTestViewAppUiProcessCommandL );

    CAknViewAppUi* viewAppUi = new ( ELeave ) CAknViewAppUi;
    CleanupStack::PushL( viewAppUi );
    viewAppUi->BaseConstructL( CEikAppUi::ENoAppResourceFile );
    viewAppUi->ProcessCommandL( EAknSoftkeyMark );
    viewAppUi->ProcessCommandL( EAknSoftkeyOptions );
    viewAppUi->ProcessCommandL( EAknSoftkeyContextOptions );
    CleanupStack::PopAndDestroy();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewAppUiStopDisplayingMenuBarL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewAppUiStopDisplayingMenuBarL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewAppUiStopDisplayingMenuBarL, "TestViewAppUiStopDisplayingMenuBarL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewAppUiStopDisplayingMenuBarL );
    // Print to log file
    iLog->Log( KTestViewAppUiStopDisplayingMenuBarL );

    CAknViewAppUi* viewAppUi = new ( ELeave ) CAknViewAppUi;
    CleanupStack::PushL( viewAppUi );
    viewAppUi->BaseConstructL( CEikAppUi::ENoAppResourceFile );
    viewAppUi->StopDisplayingMenuBar();
    CleanupStack::PopAndDestroy();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewAppUiSetSplitViewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewAppUiSetSplitViewL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewAppUiSetSplitViewL, "TestViewAppUiSetSplitViewL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewAppUiSetSplitViewL );
    // Print to log file
    iLog->Log( KTestViewAppUiSetSplitViewL );

    CAknViewAppUi* viewAppUi = new ( ELeave ) CAknViewAppUi;
    CleanupStack::PushL( viewAppUi );
    viewAppUi->BaseConstructL( CEikAppUi::ENoAppResourceFile );
    viewAppUi->SetSplitViewL( KTestViewId, KTestViewId, 0 );
    CleanupStack::PopAndDestroy();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewAppUiRemoveSplitViewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewAppUiRemoveSplitViewL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewAppUiRemoveSplitViewL, "TestViewAppUiRemoveSplitViewL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewAppUiRemoveSplitViewL );
    // Print to log file
    iLog->Log( KTestViewAppUiRemoveSplitViewL );

    CAknViewAppUi* viewAppUi = new ( ELeave ) CAknViewAppUi;
    CleanupStack::PushL( viewAppUi );
    viewAppUi->BaseConstructL( CEikAppUi::ENoAppResourceFile );
    viewAppUi->RemoveSplitViewL( KTestViewId );
    CleanupStack::PopAndDestroy();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewAppUiSplitViewActiveL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewAppUiSplitViewActiveL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewAppUiSplitViewActiveL, "TestViewAppUiSplitViewActiveL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewAppUiSplitViewActiveL );
    // Print to log file
    iLog->Log( KTestViewAppUiSplitViewActiveL );

    CAknViewAppUi* viewAppUi = new ( ELeave ) CAknViewAppUi;
    CleanupStack::PushL( viewAppUi );
    viewAppUi->BaseConstructL( CEikAppUi::ENoAppResourceFile );
    TBool flag = viewAppUi->SplitViewActive();
    STIF_ASSERT_FALSE( flag );
    CleanupStack::PopAndDestroy();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewAppUiFocusedViewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewAppUiFocusedViewL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewAppUiFocusedViewL, "TestViewAppUiFocusedViewL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewAppUiFocusedViewL );
    // Print to log file
    iLog->Log( KTestViewAppUiFocusedViewL );

    CAknViewAppUi* viewAppUi = new ( ELeave ) CAknViewAppUi;
    CleanupStack::PushL( viewAppUi );
    viewAppUi->BaseConstructL( CEikAppUi::ENoAppResourceFile );
    TUid viewId = viewAppUi->FocusedView();
    STIF_ASSERT_EQUALS( KNullUid, viewId );
    CleanupStack::PopAndDestroy();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewAppUiViewShownL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewAppUiViewShownL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewAppUiViewShownL, "TestViewAppUiViewShownL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewAppUiViewShownL );
    // Print to log file
    iLog->Log( KTestViewAppUiViewShownL );

    CAknViewAppUi* viewAppUi = new ( ELeave ) CAknViewAppUi;
    CleanupStack::PushL( viewAppUi );
    viewAppUi->BaseConstructL( CEikAppUi::ENoAppResourceFile );
    TBool flag = viewAppUi->ViewShown( KTestViewId );
    STIF_ASSERT_FALSE( flag );
    CleanupStack::PopAndDestroy();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewAppUiEnableLocalScreenClearerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewAppUiEnableLocalScreenClearerL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewAppUiEnableLocalScreenClearerL, "TestViewAppUiEnableLocalScreenClearerL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewAppUiEnableLocalScreenClearerL );
    // Print to log file
    iLog->Log( KTestViewAppUiEnableLocalScreenClearerL );

    CAknViewAppUi* viewAppUi = new ( ELeave ) CAknViewAppUi;
    CleanupStack::PushL( viewAppUi );
    viewAppUi->BaseConstructL( CEikAppUi::ENoAppResourceFile );
    viewAppUi->EnableLocalScreenClearer();
    CleanupStack::PopAndDestroy();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewAppUiHandleStatusPaneSizeChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewAppUiHandleStatusPaneSizeChangeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewAppUiHandleStatusPaneSizeChangeL, "TestViewAppUiHandleStatusPaneSizeChangeL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewAppUiHandleStatusPaneSizeChangeL );
    // Print to log file
    iLog->Log( KTestViewAppUiHandleStatusPaneSizeChangeL );

    CTestSDKAppFWViewAppUi* viewAppUi = new ( ELeave ) CTestSDKAppFWViewAppUi;
    CleanupStack::PushL( viewAppUi );
    viewAppUi->BaseConstructL( CEikAppUi::ENoAppResourceFile );
    viewAppUi->ProtectedHandleStatusPaneSizeChange();
    CleanupStack::PopAndDestroy();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewAppUiHandleForegroundEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewAppUiHandleForegroundEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewAppUiHandleForegroundEventL, "TestViewAppUiHandleForegroundEventL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewAppUiHandleForegroundEventL );
    // Print to log file
    iLog->Log( KTestViewAppUiHandleForegroundEventL );

    CTestSDKAppFWViewAppUi* viewAppUi = new ( ELeave ) CTestSDKAppFWViewAppUi;
    CleanupStack::PushL( viewAppUi );
    viewAppUi->BaseConstructL( CEikAppUi::ENoAppResourceFile );
    viewAppUi->ProtectedHandleForegroundEventL( ETrue );
    CleanupStack::PopAndDestroy();

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewAppUiHandleWsEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewAppUiHandleWsEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewAppUiHandleWsEventL, "TestViewAppUiHandleWsEventL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewAppUiHandleWsEventL );
    // Print to log file
    iLog->Log( KTestViewAppUiHandleWsEventL );

    CTestSDKAppFWViewAppUi* viewAppUi = new ( ELeave ) CTestSDKAppFWViewAppUi;
    CleanupStack::PushL( viewAppUi );
    viewAppUi->BaseConstructL( CEikAppUi::ENoAppResourceFile );

    TWsEvent event ;
    CCoeControl* targetControl = new ( ELeave ) CCoeControl;
    CCoeEnv::Static()->AppUi()->AddToStackL( targetControl );

    viewAppUi->ProtectedHandleWsEventL( event, targetControl );
    CCoeEnv::Static()->AppUi()->RemoveFromStack( targetControl );

    CleanupStack::PopAndDestroy(); // targetControl/viewAppUi

    return KErrNone;

    }

//  [End of File]
