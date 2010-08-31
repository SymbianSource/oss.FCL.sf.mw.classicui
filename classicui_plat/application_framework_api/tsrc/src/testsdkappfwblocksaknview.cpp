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
* Description:  Test aknview.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <testsdkappfw.rsg>

#include "testsdkappfw.h"
#include "testsdkappfwview.h"

// CONSTANTS
const TUid KTestViewId = { 1 };

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewCAknViewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewCAknViewL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewCAknViewL, "TestViewCAknViewL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewCAknViewL );
    // Print to log file
    iLog->Log( KTestViewCAknViewL );

    CTestSDKAppFWView* view = new( ELeave ) CTestSDKAppFWView;
    CleanupStack::PushL( view );
    STIF_ASSERT_NOT_NULL( view );
    CleanupStack::PopAndDestroy( view );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewBaseConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewBaseConstructL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewBaseConstructL, "TestViewBaseConstructL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewBaseConstructL );
    // Print to log file
    iLog->Log( KTestViewBaseConstructL );

    CTestSDKAppFWView* view = new( ELeave ) CTestSDKAppFWView;
    CleanupStack::PushL( view );
    view->BaseConstructL();
    CleanupStack::PopAndDestroy( view );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewConstructMenuAndCbaEarlyL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewConstructMenuAndCbaEarlyL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewConstructMenuAndCbaEarlyL, "TestViewConstructMenuAndCbaEarlyL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewConstructMenuAndCbaEarlyL );
    // Print to log file
    iLog->Log( KTestViewConstructMenuAndCbaEarlyL );

    CTestSDKAppFWView* view = new( ELeave ) CTestSDKAppFWView;
    CleanupStack::PushL( view );
    view->BaseConstructL();
    view->ConstructMenuAndCbaEarlyL();
    CleanupStack::PopAndDestroy( view );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewActivateViewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewActivateViewL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewActivateViewL, "TestViewActivateViewL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewActivateViewL );
    // Print to log file
    iLog->Log( KTestViewActivateViewL );

    CTestSDKAppFWView* view = CTestSDKAppFWView::NewL();
    CleanupStack::PushL( view );

    TVwsViewId vwsViewId = view->ViewId();
    STIF_ASSERT_LEAVES( view->ActivateViewL( vwsViewId ) );

    CleanupStack::PopAndDestroy( view );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewActivateViewLCustomL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewActivateViewLCustomL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewActivateViewLCustomL, "TestViewActivateViewLCustomL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewActivateViewLCustomL );
    // Print to log file
    iLog->Log( KTestViewActivateViewLCustomL );

    CTestSDKAppFWView* view = CTestSDKAppFWView::NewL();
    CleanupStack::PushL( view );

    TVwsViewId vwsViewId = view->ViewId();
    STIF_ASSERT_LEAVES( view->ActivateViewL( vwsViewId, KNullUid, KNullDesC8 ) );

    CleanupStack::PopAndDestroy( view );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewIdL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewIdL, "TestViewIdL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewIdL );
    // Print to log file
    iLog->Log( KTestViewIdL );

    CTestSDKAppFWView* view = CTestSDKAppFWView::NewL();
    CleanupStack::PushL( view );
    TUid retValue = view->Id();
    STIF_ASSERT_EQUALS( KTestViewId, retValue );
    CleanupStack::PopAndDestroy( view );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewHandleStatusPaneSizeChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewHandleStatusPaneSizeChangeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewHandleStatusPaneSizeChangeL, "TestViewHandleStatusPaneSizeChangeL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewHandleStatusPaneSizeChangeL );
    // Print to log file
    iLog->Log( KTestViewHandleStatusPaneSizeChangeL );

    CTestSDKAppFWView* view = CTestSDKAppFWView::NewL();
    CleanupStack::PushL( view );
    view->HandleStatusPaneSizeChange();
    CleanupStack::PopAndDestroy( view );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewViewIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewViewIdL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewViewIdL, "TestViewViewIdL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewViewIdL );
    // Print to log file
    iLog->Log( KTestViewViewIdL );

    CTestSDKAppFWView* view = CTestSDKAppFWView::NewL();
    CleanupStack::PushL( view );
    TVwsViewId vwsViewId = view->ViewId();
    CleanupStack::PopAndDestroy( view );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewProcessCommandL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewProcessCommandL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewProcessCommandL, "TestViewProcessCommandL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewProcessCommandL );
    // Print to log file
    iLog->Log( KTestViewProcessCommandL );

    CTestSDKAppFWView* view = CTestSDKAppFWView::NewL();
    CleanupStack::PushL( view );
    view->ProcessCommandL( EAknSoftkeyOk );
    CleanupStack::PopAndDestroy( view );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewHandleCommandL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewHandleCommandL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewHandleCommandL, "TestViewHandleCommandL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewHandleCommandL );
    // Print to log file
    iLog->Log( KTestViewHandleCommandL );

    CTestSDKAppFWView* view = CTestSDKAppFWView::NewL();
    CleanupStack::PushL( view );
    view->HandleCommandL( EAknSoftkeyOk );
    CleanupStack::PopAndDestroy( view );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewMenuBarL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewMenuBarL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewMenuBarL, "TestViewMenuBarL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewMenuBarL );
    // Print to log file
    iLog->Log( KTestViewMenuBarL );

    CTestSDKAppFWView* view = CTestSDKAppFWView::NewL();
    CleanupStack::PushL( view );
    STIF_ASSERT_NOT_NULL( view->MenuBar() );
    CleanupStack::PopAndDestroy( view );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewClientRectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewClientRectL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewClientRectL, "TestViewClientRectL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewClientRectL );
    // Print to log file
    iLog->Log( KTestViewClientRectL );

    CTestSDKAppFWView* view = CTestSDKAppFWView::NewL();
    CleanupStack::PushL( view );
    view->ClientRect();
    CleanupStack::PopAndDestroy( view );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewStopDisplayingMenuBarL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewStopDisplayingMenuBarL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewStopDisplayingMenuBarL, "TestViewStopDisplayingMenuBarL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewStopDisplayingMenuBarL );
    // Print to log file
    iLog->Log( KTestViewStopDisplayingMenuBarL );

    CTestSDKAppFWView* view = CTestSDKAppFWView::NewL();
    CleanupStack::PushL( view );
    view->StopDisplayingMenuBar();
    CleanupStack::PopAndDestroy( view );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewIsForegroundL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewIsForegroundL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewIsForegroundL, "TestViewIsForegroundL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewIsForegroundL );
    // Print to log file
    iLog->Log( KTestViewIsForegroundL );

    CTestSDKAppFWView* view = CTestSDKAppFWView::NewL();
    CleanupStack::PushL( view );
    TBool status = view->IsForeground();
    STIF_ASSERT_FALSE( status );
    CleanupStack::PopAndDestroy( view );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewHandleViewRectChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewHandleViewRectChangeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewHandleViewRectChangeL, "TestViewHandleViewRectChangeL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewHandleViewRectChangeL );
    // Print to log file
    iLog->Log( KTestViewHandleViewRectChangeL );

    CTestSDKAppFWView* view = CTestSDKAppFWView::NewL();
    CleanupStack::PushL( view );
    view->HandleViewRectChange();
    CleanupStack::PopAndDestroy( view );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewRedrawL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewRedrawL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewRedrawL, "TestViewRedrawL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewRedrawL );
    // Print to log file
    iLog->Log( KTestViewRedrawL );

    CTestSDKAppFWView* view = CTestSDKAppFWView::NewL();
    CleanupStack::PushL( view );
    view->Redraw();
    CleanupStack::PopAndDestroy( view );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewAknViewActivatedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewAknViewActivatedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewAknViewActivatedL, "TestViewAknViewActivatedL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewAknViewActivatedL );
    // Print to log file
    iLog->Log( KTestViewAknViewActivatedL );

    CTestSDKAppFWView* view = CTestSDKAppFWView::NewL();
    CleanupStack::PushL( view );
    TVwsViewId vwsViewId = view->ViewId();
    view->AknViewActivatedL( vwsViewId, KNullUid, KNullDesC8 );
    CleanupStack::PopAndDestroy( view );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewAppUiL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewAppUiL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewAppUiL, "TestViewAppUiL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewAppUiL );
    // Print to log file
    iLog->Log( KTestViewAppUiL );

    CTestSDKAppFWView* view = CTestSDKAppFWView::NewL();
    CleanupStack::PushL( view );
    STIF_ASSERT_NOT_NULL( view->ProtectedAppUi() );
    CleanupStack::PopAndDestroy( view );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewStatusPaneL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewStatusPaneL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewStatusPaneL, "TestViewStatusPaneL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewStatusPaneL );
    // Print to log file
    iLog->Log( KTestViewStatusPaneL );

    CTestSDKAppFWView* view = CTestSDKAppFWView::NewL();
    CleanupStack::PushL( view );
    STIF_ASSERT_NOT_NULL( view->ProtectedStatusPane() );
    CleanupStack::PopAndDestroy( view );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewCbaL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewCbaL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewCbaL, "TestViewCbaL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewCbaL );
    // Print to log file
    iLog->Log( KTestViewCbaL );

    CTestSDKAppFWView* view = CTestSDKAppFWView::NewL();
    CleanupStack::PushL( view );
    STIF_ASSERT_NOT_NULL( view->ProtectedCba() );
    CleanupStack::PopAndDestroy( view );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewDoActivateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewDoActivateL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewDoActivateL, "TestViewDoActivateL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewDoActivateL );
    // Print to log file
    iLog->Log( KTestViewDoActivateL );

    CTestSDKAppFWView* view = CTestSDKAppFWView::NewL();
    CleanupStack::PushL( view );
    view->DoActivateL( view->ViewId(), KNullUid, KNullDesC8 );
    CleanupStack::PopAndDestroy( view );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewViewActivatedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewViewActivatedL( CStifItemParser& /*aItem*/ )
    {
    // !!! crash
    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewViewActivatedL, "TestViewViewActivatedL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewViewActivatedL );
    // Print to log file
    iLog->Log( KTestViewViewActivatedL );

    CTestSDKAppFWView* view = CTestSDKAppFWView::NewL();
    CleanupStack::PushL( view );
    view->BaseConstructL( 0 );
    CCoeEnv::Static()->AppUi()->RegisterViewL( *view );
    TVwsViewId vwsViewId = view->ViewId();
    view->AknViewActivatedL( vwsViewId, KNullUid, KNullDesC8 );
    view->ProtectedViewActivatedL( vwsViewId, KNullUid, KNullDesC8 );
    CCoeEnv::Static()->AppUi()->DeregisterView( *view ); 
    CleanupStack::PopAndDestroy( view );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewViewDeactivatedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewViewDeactivatedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewViewDeactivatedL, "TestViewViewDeactivatedL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewViewDeactivatedL );
    // Print to log file
    iLog->Log( KTestViewViewDeactivatedL );

    CTestSDKAppFWView* view = CTestSDKAppFWView::NewL();
    CleanupStack::PushL( view );
    view->ProtectedViewDeactivated();
    CleanupStack::PopAndDestroy( view );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewViewScreenDeviceChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewViewScreenDeviceChangedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewViewScreenDeviceChangedL, "TestViewViewScreenDeviceChangedL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewViewScreenDeviceChangedL );
    // Print to log file
    iLog->Log( KTestViewViewScreenDeviceChangedL );

    CTestSDKAppFWView* view = CTestSDKAppFWView::NewL();
    CleanupStack::PushL( view );
    view->ProtectedViewScreenDeviceChangedL();
    CleanupStack::PopAndDestroy( view );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewMopSupplyObjectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewMopSupplyObjectL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewMopSupplyObjectL, "TestViewMopSupplyObjectL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewMopSupplyObjectL );
    // Print to log file
    iLog->Log( KTestViewMopSupplyObjectL );

    CTestSDKAppFWView* view = CTestSDKAppFWView::NewL();
    CleanupStack::PushL( view );
    view->ProtectedMopSupplyObject( 0 );
    CleanupStack::PopAndDestroy( view );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewMopNextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewMopNextL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewMopNextL, "TestViewMopNextL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewMopNextL );
    // Print to log file
    iLog->Log( KTestViewMopNextL );

    CTestSDKAppFWView* view = CTestSDKAppFWView::NewL();
    CleanupStack::PushL( view );
    STIF_ASSERT_NOT_NULL( view->ProtectedMopNext() );
    CleanupStack::PopAndDestroy( view );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewSetEmphasisL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewSetEmphasisL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewSetEmphasisL, "TestViewSetEmphasisL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewSetEmphasisL );
    // Print to log file
    iLog->Log( KTestViewSetEmphasisL );

    CTestSDKAppFWView* view = CTestSDKAppFWView::NewL();
    CleanupStack::PushL( view );

    CCoeControl* menuControl = new ( ELeave ) CCoeControl;
    CCoeEnv::Static()->AppUi()->AddToStackL( menuControl );
    view->ProtectedSetEmphasis( menuControl, EFalse );
    CCoeEnv::Static()->AppUi()->RemoveFromStack( menuControl );
    
    CleanupStack::PopAndDestroy(); // menuControl, view

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewHandleForegroundEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewHandleForegroundEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewHandleForegroundEventL, "TestViewHandleForegroundEventL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewHandleForegroundEventL );
    // Print to log file
    iLog->Log( KTestViewHandleForegroundEventL );

    CTestSDKAppFWView* view = CTestSDKAppFWView::NewL();
    CleanupStack::PushL( view );
    view->ProtectedHandleForegroundEventL( ETrue );
    CleanupStack::PopAndDestroy( view );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewToolbarL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewToolbarL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewToolbarL, "TestViewToolbarL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewToolbarL );
    // Print to log file
    iLog->Log( KTestViewToolbarL );

    CTestSDKAppFWView* view = CTestSDKAppFWView::NewL();
    CleanupStack::PushL( view );
    STIF_ASSERT_NOT_NULL( view->Toolbar() );
    CleanupStack::PopAndDestroy( view );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewStopDisplayingToolbarL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewStopDisplayingToolbarL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewStopDisplayingToolbarL, "TestViewStopDisplayingToolbarL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewStopDisplayingToolbarL );
    // Print to log file
    iLog->Log( KTestViewStopDisplayingToolbarL );

    CTestSDKAppFWView* view = CTestSDKAppFWView::NewL();
    CleanupStack::PushL( view );
    view->StopDisplayingToolbar();
    CleanupStack::PopAndDestroy( view );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewToolbarShownOnViewActivationL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewToolbarShownOnViewActivationL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewToolbarShownOnViewActivationL, "TestViewToolbarShownOnViewActivationL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewToolbarShownOnViewActivationL );
    // Print to log file
    iLog->Log( KTestViewToolbarShownOnViewActivationL );

    CTestSDKAppFWView* view = CTestSDKAppFWView::NewL();
    CleanupStack::PushL( view );
    TBool flag = view->ToolbarShownOnViewActivation();
    STIF_ASSERT_FALSE( flag );
    CleanupStack::PopAndDestroy( view );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewShowToolbarOnViewActivationL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewShowToolbarOnViewActivationL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewShowToolbarOnViewActivationL, "TestViewShowToolbarOnViewActivationL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewShowToolbarOnViewActivationL );
    // Print to log file
    iLog->Log( KTestViewShowToolbarOnViewActivationL );

    CTestSDKAppFWView* view = CTestSDKAppFWView::NewL();
    CleanupStack::PushL( view );
    view->ShowToolbarOnViewActivation( ETrue );
    CleanupStack::PopAndDestroy( view );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewSetToolbarL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewSetToolbarL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewSetToolbarL, "TestViewSetToolbarL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewSetToolbarL );
    // Print to log file
    iLog->Log( KTestViewSetToolbarL );

    CTestSDKAppFWView* view = CTestSDKAppFWView::NewL();
    CleanupStack::PushL( view );
    CAknToolbar* toolbar = view->ProtectedAppUi()->CurrentFixedToolbar();
    view->SetToolbar( toolbar );
    CleanupStack::PopAndDestroy( view );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::TestViewCreateAndSetToolbarL
// -----------------------------------------------------------------------------
//
TInt CTestSDKAppFW::TestViewCreateAndSetToolbarL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKAppFW, "testsdkappfw" );
    _LIT( KTestViewCreateAndSetToolbarL, "TestViewCreateAndSetToolbarL" );
    TestModuleIf().Printf( 0, KTestSDKAppFW, KTestViewCreateAndSetToolbarL );
    // Print to log file
    iLog->Log( KTestViewCreateAndSetToolbarL );

    CTestSDKAppFWView* view = CTestSDKAppFWView::NewL();
    CleanupStack::PushL( view );
    view->CreateAndSetToolbarL( R_TEST_TOOLBAR );
    CleanupStack::PopAndDestroy( view );

    return KErrNone;

    }

//  [End of File]
