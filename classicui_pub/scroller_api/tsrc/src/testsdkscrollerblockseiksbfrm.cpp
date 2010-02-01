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
* Description:  test eiksbfrm.h
*
*/


// [INCLUDE FILES]
#include <eiksbfrm.h>
#include <coemain.h>
#include <coeaui.h>

#include "testsdkscroller.h"
#include "testsdkscrollercontrol.h"

// CONSTANTS
const TInt KWidth = 100;
const TInt KHeight = 100;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKSbFrmLaDefConsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKSbFrmLaDefConsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKSbFrmLaDefCons, "in SbFrmLaNewL" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKSbFrmLaDefCons );
    // Print to log file
    iLog->Log( KTestSDKSbFrmLaDefCons );

    TEikScrollBarFrameLayout* sbFrameLa = new ( ELeave ) TEikScrollBarFrameLayout;
    CleanupStack::PushL( sbFrameLa );
    STIF_ASSERT_NOT_NULL( sbFrameLa );

    CleanupStack::PopAndDestroy( sbFrameLa );
     return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKSbFrmLaSetInclusiveMarginL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKSbFrmLaSetInclusiveMarginL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKSbFrmLaSetInclusiveMargin, "in SbFrmLaSetInclusiveMargin" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKSbFrmLaSetInclusiveMargin );
    // Print to log file
    iLog->Log( KTestSDKSbFrmLaSetInclusiveMargin );

    TEikScrollBarFrameLayout* sbFrameLa = new ( ELeave ) TEikScrollBarFrameLayout;
    CleanupStack::PushL( sbFrameLa );

    TInt margin = 0;
    sbFrameLa->SetInclusiveMargin( margin );

    CleanupStack::PopAndDestroy( sbFrameLa );
     return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKSbFrmLaSetClientMarginL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKSbFrmLaSetClientMarginL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKSbFrmLaSetInclusiveMargin, "in SbFrmLaSetInclusiveMargin" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKSbFrmLaSetInclusiveMargin );
    // Print to log file
    iLog->Log( KTestSDKSbFrmLaSetInclusiveMargin );

    TEikScrollBarFrameLayout* sbFrameLa = new ( ELeave ) TEikScrollBarFrameLayout;
    CleanupStack::PushL( sbFrameLa );

    TInt margin = 0;
    sbFrameLa->SetClientMargin( margin );

    CleanupStack::PopAndDestroy( sbFrameLa );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKSbFrmDefConsWithPaL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKSbFrmDefConsWithPaL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKSbFrmDefConsWithPa, "in SbFrmDefConsWithPa" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKSbFrmDefConsWithPa );
    // Print to log file
    iLog->Log( KTestSDKSbFrmDefConsWithPa );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );

    CEikScrollBarFrame* sbFrame = new ( ELeave ) CEikScrollBarFrame( control, control );
    CleanupStack::PushL( sbFrame );
    STIF_ASSERT_NOT_NULL( sbFrame );

    CleanupStack::PopAndDestroy( sbFrame );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKSbFrmDrawSbsNowL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKSbFrmDrawSbsNowL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKSbFrmDrawSbsNow, "in SbFrmDrawSbsNow" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKSbFrmDrawSbsNow );
    // Print to log file
    iLog->Log( KTestSDKSbFrmDrawSbsNow );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CEikScrollBarFrame* sbFrame = new ( ELeave ) CEikScrollBarFrame( control, control );
    CleanupStack::PushL( sbFrame );
    sbFrame->CreateDoubleSpanScrollBarsL( ETrue, EFalse );

    sbFrame->DrawScrollBarsNow();

    CleanupStack::PopAndDestroy( sbFrame );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKSbFrmSetSbVisibilityL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKSbFrmSetSbVisibilityL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKSbFrmSetSbVisibilityL, "in SbFrmSbVisibilityL" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKSbFrmSetSbVisibilityL );
    // Print to log file
    iLog->Log( KTestSDKSbFrmSetSbVisibilityL );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CEikScrollBarFrame* sbFrame = new ( ELeave ) CEikScrollBarFrame( control, control );
    CleanupStack::PushL( sbFrame );
    sbFrame->CreateDoubleSpanScrollBarsL( ETrue, EFalse );

    CEikScrollBarFrame::TScrollBarVisibility hVisibility =
            CEikScrollBarFrame::EOff;
    CEikScrollBarFrame::TScrollBarVisibility vVisibility =
            CEikScrollBarFrame::EOff;
    sbFrame->SetScrollBarVisibilityL( hVisibility, vVisibility );

    CleanupStack::PopAndDestroy( sbFrame );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKSbFrmVSbVisibilityL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKSbFrmVSbVisibilityL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKSbFrmVSbVisibilityL, "in SbFrmVSbVisibilityL" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKSbFrmVSbVisibilityL );
    // Print to log file
    iLog->Log( KTestSDKSbFrmVSbVisibilityL );

    CEikScrollBarFrame* sbFrame = new ( ELeave ) CEikScrollBarFrame;
    CleanupStack::PushL( sbFrame );
    sbFrame->CreateDoubleSpanScrollBarsL( ETrue, EFalse );

    CEikScrollBarFrame::TScrollBarVisibility hVisibility =
            CEikScrollBarFrame::EOn;
    CEikScrollBarFrame::TScrollBarVisibility vVisibility =
            CEikScrollBarFrame::EOn;
    sbFrame->SetScrollBarVisibilityL( hVisibility, vVisibility );

    CEikScrollBarFrame::TScrollBarVisibility vSbVisibility =
        sbFrame->VScrollBarVisibility();
    STIF_ASSERT_EQUALS( vVisibility, vSbVisibility );

    CleanupStack::PopAndDestroy( sbFrame );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKSbFrmSetSbfrmObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKSbFrmSetSbfrmObserverL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKSbFrmSetSbfrmObserverL, "in SbFrmDefConsWithPa" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKSbFrmSetSbfrmObserverL );
    // Print to log file
    iLog->Log( KTestSDKSbFrmSetSbfrmObserverL );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CEikScrollBarFrame* sbFrame = new ( ELeave ) CEikScrollBarFrame( control, control );
    CleanupStack::PushL( sbFrame );

    sbFrame->SetScrollBarFrameObserver( control );

    CleanupStack::PopAndDestroy( sbFrame );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKSbFrmTileL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKSbFrmTileL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKSbFrmTile, "in SbFrmTile" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKSbFrmTile );
    // Print to log file
    iLog->Log( KTestSDKSbFrmTile );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CEikScrollBarFrame* sbFrame = new ( ELeave ) CEikScrollBarFrame( control, control );
    CleanupStack::PushL( sbFrame );
    sbFrame->CreateDoubleSpanScrollBarsL( ETrue, EFalse );

    TEikScrollBarModel* vModel = new ( ELeave ) TEikScrollBarModel;
    CleanupStack::PushL( vModel );
    TBool model = sbFrame->Tile( vModel );
    STIF_ASSERT_FALSE( model );

    CleanupStack::PopAndDestroy( vModel );
    CleanupStack::PopAndDestroy( sbFrame );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKSbFrmTileWithSbfrmLaL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKSbFrmTileWithSbfrmLaL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKSbFrmTileWithSbfrmLa, "in SbFrmTileWithSbfrmLa" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKSbFrmTileWithSbfrmLa );
    // Print to log file
    iLog->Log( KTestSDKSbFrmTileWithSbfrmLa );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CEikScrollBarFrame* sbFrame = new ( ELeave ) CEikScrollBarFrame( control, control );
    CleanupStack::PushL( sbFrame );
    sbFrame->CreateDoubleSpanScrollBarsL( ETrue, EFalse );

    TEikScrollBarModel* vModel = new ( ELeave ) TEikScrollBarModel;
    CleanupStack::PushL( vModel );
    TEikScrollBarModel* hModel = new ( ELeave ) TEikScrollBarModel;
    CleanupStack::PushL( hModel );
    TEikScrollBarFrameLayout* sbFrameLa = new ( ELeave ) TEikScrollBarFrameLayout;
    CleanupStack::PushL( sbFrameLa );
    TSize size( KWidth, KHeight );
    TRect clientRect( size );
    TRect inclusiveRect( size );
    
    TBool model = sbFrame->TileL( hModel, vModel, clientRect,
            inclusiveRect, *sbFrameLa );
    STIF_ASSERT_FALSE( model );

    CleanupStack::PopAndDestroy( sbFrameLa );
    CleanupStack::PopAndDestroy( hModel );
    CleanupStack::PopAndDestroy( vModel );
    CleanupStack::PopAndDestroy( sbFrame );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKSbFrmMoveThumbsByL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKSbFrmMoveThumbsByL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKSbFrmMoveThumbsBy, "in SbFrmMoveThumbsBy" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKSbFrmMoveThumbsBy );
    // Print to log file
    iLog->Log( KTestSDKSbFrmMoveThumbsBy );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CEikScrollBarFrame* sbFrame = new ( ELeave ) CEikScrollBarFrame( control, control );
    CleanupStack::PushL( sbFrame );
    sbFrame->CreateDoubleSpanScrollBarsL( ETrue, EFalse );

    TInt deltaX = 1;
    TInt deltaY = 1;
    sbFrame->MoveThumbsBy( deltaX, deltaY );

    CleanupStack::PopAndDestroy( sbFrame );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKSbFrmMoveHThumbToL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKSbFrmMoveHThumbToL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKSbFrmMoveHThumbTo, "in SbFrmMoveHThumbTo" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKSbFrmMoveHThumbTo );
    // Print to log file
    iLog->Log( KTestSDKSbFrmMoveHThumbTo );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CEikScrollBarFrame* sbFrame = new ( ELeave ) CEikScrollBarFrame( control, control );
    CleanupStack::PushL( sbFrame );
    sbFrame->CreateDoubleSpanScrollBarsL( ETrue, EFalse );

    TInt hThumbPos = 0;
    sbFrame->MoveHorizThumbTo( hThumbPos );

    CleanupStack::PopAndDestroy( sbFrame );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKSbFrmMoveVThumbToL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKSbFrmMoveVThumbToL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKSbFrmMoveVThumbTo, "in SbFrmMoveVThumbTo" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKSbFrmMoveVThumbTo );
    // Print to log file
    iLog->Log( KTestSDKSbFrmMoveVThumbTo );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CEikScrollBarFrame* sbFrame = new ( ELeave ) CEikScrollBarFrame( control, control );
    CleanupStack::PushL( sbFrame );
    sbFrame->CreateDoubleSpanScrollBarsL( ETrue, EFalse );

    TInt vThumbPos = 0;
    sbFrame->MoveVertThumbTo( vThumbPos );

    CleanupStack::PopAndDestroy( sbFrame );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKSbFrmSetVFocusPosToThumbPosL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKSbFrmSetVFocusPosToThumbPosL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKSbFrmSetVFocusPosToThumbPos, "in SbFrmSetVFocusPosToThumbPos" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKSbFrmSetVFocusPosToThumbPos );
    // Print to log file
    iLog->Log( KTestSDKSbFrmSetVFocusPosToThumbPos );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CEikScrollBarFrame* sbFrame = new ( ELeave ) CEikScrollBarFrame( control, control );
    CleanupStack::PushL( sbFrame );
    sbFrame->CreateDoubleSpanScrollBarsL( ETrue, EFalse );

    TInt focusPos = 0;
    sbFrame->SetVFocusPosToThumbPos( focusPos );

    CleanupStack::PopAndDestroy( sbFrame );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKSbFrmSbBreadthL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKSbFrmSbBreadthL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKSbFrmSbBreadth, "in SbFrmSbBreadth" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKSbFrmSbBreadth );
    // Print to log file
    iLog->Log( KTestSDKSbFrmSbBreadth );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CEikScrollBarFrame* sbFrame = new ( ELeave ) CEikScrollBarFrame( control, control );
    CleanupStack::PushL( sbFrame );
    sbFrame->CreateDoubleSpanScrollBarsL( ETrue, EFalse );

    CEikScrollBar::TOrientation orientation = CEikScrollBar::EHorizontal;
    TInt hOrientation = sbFrame->ScrollBarBreadth( orientation );
    STIF_ASSERT_EQUALS( 0, hOrientation );

    CleanupStack::PopAndDestroy( sbFrame );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKSbFrmSetAdjustsHModelL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKSbFrmSetAdjustsHModelL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKSbFrmSetAdjustsHModel, "in SbFrmSetAdjustsHModel" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKSbFrmSetAdjustsHModel );
    // Print to log file
    iLog->Log( KTestSDKSbFrmSetAdjustsHModel );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CEikScrollBarFrame* sbFrame = new ( ELeave ) CEikScrollBarFrame( control, control );
    CleanupStack::PushL( sbFrame );
    sbFrame->CreateDoubleSpanScrollBarsL( ETrue, EFalse );

    sbFrame->SetAdjustsHorizontalModel( ETrue );

    CleanupStack::PopAndDestroy( sbFrame );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKSbFrmSetAdjustsVModelL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKSbFrmSetAdjustsVModelL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKSbFrmSetAdjustsVModel, "in SbFrmSetAdjustsVModel" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKSbFrmSetAdjustsVModel );
    // Print to log file
    iLog->Log( KTestSDKSbFrmSetAdjustsVModel );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CEikScrollBarFrame* sbFrame = new ( ELeave ) CEikScrollBarFrame( control, control );
    CleanupStack::PushL( sbFrame );
    sbFrame->CreateDoubleSpanScrollBarsL( ETrue, EFalse );

    sbFrame->SetAdjustsVerticalModel( ETrue );

    CleanupStack::PopAndDestroy( sbFrame );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKSbFrmSetSbfrmFlagsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKSbFrmSetSbfrmFlagsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKSbFrmSetSbfrmFlags, "in SbFrmSetSbfrmFlags" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKSbFrmSetSbfrmFlags );
    // Print to log file
    iLog->Log( KTestSDKSbFrmSetSbfrmFlags );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CEikScrollBarFrame* sbFrame = new ( ELeave ) CEikScrollBarFrame( control, control );
    CleanupStack::PushL( sbFrame );
    sbFrame->CreateDoubleSpanScrollBarsL( ETrue, EFalse );

    TInt mask = 0;
    sbFrame->SetScrollBarFrameFlags( mask );

    CleanupStack::PopAndDestroy( sbFrame );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKSbFrmSbExistsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKSbFrmSbExistsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKSbFrmSbExists, "in SbFrmSbExists" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKSbFrmSbExists );
    // Print to log file
    iLog->Log( KTestSDKSbFrmSbExists );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CEikScrollBarFrame* sbFrame = new ( ELeave ) CEikScrollBarFrame( control, control );
    CleanupStack::PushL( sbFrame );
    sbFrame->CreateDoubleSpanScrollBarsL( ETrue, EFalse );

    CEikScrollBar::TOrientation orientation = CEikScrollBar::EHorizontal;
    TBool exist = sbFrame->ScrollBarExists( orientation );
    STIF_ASSERT_FALSE( exist );

    CleanupStack::PopAndDestroy( sbFrame );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKSbFrmCountComCtrlsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKSbFrmCountComCtrlsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKSbFrmCountComCtrls, "in SbFrmCountComCtrls" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKSbFrmCountComCtrls );
    // Print to log file
    iLog->Log( KTestSDKSbFrmCountComCtrls );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CEikScrollBarFrame* sbFrame = new ( ELeave ) CEikScrollBarFrame( control, control );
    CleanupStack::PushL( sbFrame );
    sbFrame->CreateDoubleSpanScrollBarsL( ETrue, EFalse );

    TInt count = sbFrame->CountComponentControls();
    STIF_ASSERT_EQUALS( 2, count );

    CleanupStack::PopAndDestroy( sbFrame );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKSbFrmComponentControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKSbFrmComponentControlL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKSbFrmComponentControl, "in SbFrmComponentControl" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKSbFrmComponentControl );
    // Print to log file
    iLog->Log( KTestSDKSbFrmComponentControl );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CEikScrollBarFrame* sbFrame = new ( ELeave ) CEikScrollBarFrame( control, control );
    CleanupStack::PushL( sbFrame );
    sbFrame->CreateDoubleSpanScrollBarsL( ETrue, EFalse );

    TInt index = 0;
    CCoeControl* sbFrameControl = sbFrame->ComponentControl( index );
    STIF_ASSERT_NOT_NULL( sbFrameControl );

    CleanupStack::PopAndDestroy( sbFrame );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKSbFrmGetSbHandleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKSbFrmGetSbHandleL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKSbFrmGetSbHandle, "in SbFrmGetSbHandle" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKSbFrmGetSbHandle );
    // Print to log file
    iLog->Log( KTestSDKSbFrmGetSbHandle );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CEikScrollBarFrame* sbFrame = new ( ELeave ) CEikScrollBarFrame( control, control );
    CleanupStack::PushL( sbFrame );
    sbFrame->CreateDoubleSpanScrollBarsL( ETrue, EFalse );

    CEikScrollBar::TOrientation orientation = CEikScrollBar::EHorizontal;
    CEikScrollBar* sbHandle = sbFrame->GetScrollBarHandle( orientation );
    STIF_ASSERT_NULL( sbHandle );

    CleanupStack::PopAndDestroy( sbFrame );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKSbFrmVScrollBarL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKSbFrmVScrollBarL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKSbFrmVScrollBar, "in SbFrmVScrollBar" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKSbFrmVScrollBar );
    // Print to log file
    iLog->Log( KTestSDKSbFrmVScrollBar );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CEikScrollBarFrame* sbFrame = new ( ELeave ) CEikScrollBarFrame( control, control );
    CleanupStack::PushL( sbFrame );
    sbFrame->CreateDoubleSpanScrollBarsL( ETrue, EFalse );

    CEikScrollBar* vScrollBar = sbFrame->VerticalScrollBar();
    STIF_ASSERT_NOT_NULL( vScrollBar );

    CleanupStack::PopAndDestroy( sbFrame );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKSbFrmSetTypeOfHSbL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKSbFrmSetTypeOfHSbL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKSbFrmSetTypeOfHSb, "in SbFrmSetTypeOfHSb" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKSbFrmSetTypeOfHSb );
    // Print to log file
    iLog->Log( KTestSDKSbFrmSetTypeOfHSb );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CEikScrollBarFrame* sbFrame = new ( ELeave ) CEikScrollBarFrame( control, control );
    CleanupStack::PushL( sbFrame );
    sbFrame->CreateDoubleSpanScrollBarsL( ETrue, EFalse );

    CEikScrollBarFrame::TScrollBarType sbType = CEikScrollBarFrame::EArrowHead;
    sbFrame->SetTypeOfHScrollBar( sbType );

    CleanupStack::PopAndDestroy( sbFrame );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKSbFrmSetTypeOfVSbL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKSbFrmSetTypeOfVSbL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKSbFrmSetTypeOfVSb, "in SbFrmSetTypeOfVSb" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKSbFrmSetTypeOfVSb );
    // Print to log file
    iLog->Log( KTestSDKSbFrmSetTypeOfVSb );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CEikScrollBarFrame* sbFrame = new ( ELeave ) CEikScrollBarFrame( control, control );
    CleanupStack::PushL( sbFrame );
    sbFrame->CreateDoubleSpanScrollBarsL( ETrue, EFalse );

    CEikScrollBarFrame::TScrollBarType sbType = CEikScrollBarFrame::EArrowHead;
    sbFrame->SetTypeOfVScrollBar( sbType );

    CleanupStack::PopAndDestroy( sbFrame );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKSbFrmTypeOfHSbL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKSbFrmTypeOfHSbL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKSbFrmTypeOfHSb, "in SbFrmTypeOfHSb" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKSbFrmTypeOfHSb );
    // Print to log file
    iLog->Log( KTestSDKSbFrmTypeOfHSb );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CEikScrollBarFrame* sbFrame = new ( ELeave ) CEikScrollBarFrame( control, control );
    CleanupStack::PushL( sbFrame );
    sbFrame->CreateDoubleSpanScrollBarsL( ETrue, EFalse );

    CEikScrollBarFrame::TScrollBarType sbType = CEikScrollBarFrame::EDoubleSpan;
    CEikScrollBarFrame::TScrollBarType type = sbFrame->TypeOfHScrollBar();
    STIF_ASSERT_EQUALS( sbType, type );

    CleanupStack::PopAndDestroy( sbFrame );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKSbFrmTypeOfVSbL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKSbFrmTypeOfVSbL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKSbFrmTypeOfVSb, "in SbFrmTypeOfVSb" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKSbFrmTypeOfVSb );
    // Print to log file
    iLog->Log( KTestSDKSbFrmTypeOfVSb );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CEikScrollBarFrame* sbFrame = new ( ELeave ) CEikScrollBarFrame( control, control );
    CleanupStack::PushL( sbFrame );
    sbFrame->CreateDoubleSpanScrollBarsL( ETrue, EFalse );

    CEikScrollBarFrame::TScrollBarType sbType = CEikScrollBarFrame::EDoubleSpan;
    CEikScrollBarFrame::TScrollBarType type = sbFrame->TypeOfVScrollBar();
    STIF_ASSERT_EQUALS( sbType, type );

    CleanupStack::PopAndDestroy( sbFrame );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKSbFrmIsArrowHeadSbL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKSbFrmIsArrowHeadSbL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKSbFrmIsArrowHeadSb, "in SbFrmIsArrowHeadSb" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKSbFrmIsArrowHeadSb );
    // Print to log file
    iLog->Log( KTestSDKSbFrmIsArrowHeadSb );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CEikScrollBarFrame* sbFrame = new ( ELeave ) CEikScrollBarFrame( control, control );
    CleanupStack::PushL( sbFrame );

    TInt flags = 0;
    TBool isArrowHead = sbFrame->IsArrowHeadScrollBar( flags );
    STIF_ASSERT_TRUE( isArrowHead );

    sbFrame->CreateDoubleSpanScrollBarsL( ETrue, EFalse );
    isArrowHead = sbFrame->IsArrowHeadScrollBar( flags );
    STIF_ASSERT_FALSE( isArrowHead );

    CleanupStack::PopAndDestroy( sbFrame );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKSbFrmCreDoubleSpanSbsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKSbFrmCreDoubleSpanSbsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKSbFrmCreDoubleSpanSbsL, "in SbFrmIsArrowHeadSb" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKSbFrmCreDoubleSpanSbsL );
    // Print to log file
    iLog->Log( KTestSDKSbFrmCreDoubleSpanSbsL );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CEikScrollBarFrame* sbFrame = new ( ELeave ) CEikScrollBarFrame( control, control );
    CleanupStack::PushL( sbFrame );

    sbFrame->CreateDoubleSpanScrollBarsL( ETrue, EFalse );

    CleanupStack::PopAndDestroy( sbFrame );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKSbFrmCreDoubleSpanSbsWithSbPaL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKSbFrmCreDoubleSpanSbsWithSbPaL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKSbFrmCreDoubleSpanSbsWithSbPaL, "in SbFrmIsArrowHeadSb" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKSbFrmCreDoubleSpanSbsWithSbPaL );
    // Print to log file
    iLog->Log( KTestSDKSbFrmCreDoubleSpanSbsWithSbPaL );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CEikScrollBarFrame* sbFrame = new ( ELeave ) CEikScrollBarFrame( control, control );
    CleanupStack::PushL( sbFrame );

    sbFrame->CreateDoubleSpanScrollBarsL( ETrue, EFalse, ETrue, ETrue );

    CleanupStack::PopAndDestroy( sbFrame );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKSbFrmTileWithRectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKSbFrmTileWithRectL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKSbFrmTileWithRect, "in SbFrmTileWithRect" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKSbFrmTileWithRect );
    // Print to log file
    iLog->Log( KTestSDKSbFrmTileWithRect );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CEikScrollBarFrame* sbFrame = new ( ELeave ) CEikScrollBarFrame( control, control );
    CleanupStack::PushL( sbFrame );
    sbFrame->CreateDoubleSpanScrollBarsL( ETrue, EFalse );

    TEikScrollBarModel* hModel = new ( ELeave ) TEikScrollBarModel;
    CleanupStack::PushL( hModel );
    TEikScrollBarModel* vModel = new ( ELeave ) TEikScrollBarModel;
    CleanupStack::PushL( vModel );
    sbFrame->Tile( hModel, vModel );

    CleanupStack::PopAndDestroy( vModel );
    CleanupStack::PopAndDestroy( hModel );
    CleanupStack::PopAndDestroy( sbFrame );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKSbFrmTileWithSbModelL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKSbFrmTileWithSbModelL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKSbFrmTileWithSbModel, "in SbFrmTileWithSbModel" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKSbFrmTileWithSbModel );
    // Print to log file
    iLog->Log( KTestSDKSbFrmTileWithSbModel );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CEikScrollBarFrame* sbFrame = new ( ELeave ) CEikScrollBarFrame( control, control );
    CleanupStack::PushL( sbFrame );
    sbFrame->CreateDoubleSpanScrollBarsL( ETrue, EFalse );

    TEikScrollBarModel* vModel = new ( ELeave ) TEikScrollBarModel;
    CleanupStack::PushL( vModel );
    TSize size( KWidth, KHeight );
    TRect vScrollBar( size );
    sbFrame->Tile( vModel, vScrollBar );

    CleanupStack::PopAndDestroy( vModel );
    CleanupStack::PopAndDestroy( sbFrame );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKSbFrmSbVisibilityL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKSbFrmSbVisibilityL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKSbFrmSbVisibility, "in SbFrmSbVisibility" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKSbFrmSbVisibility );
    // Print to log file
    iLog->Log( KTestSDKSbFrmSbVisibility );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CEikScrollBarFrame* sbFrame = new ( ELeave ) CEikScrollBarFrame( control, control );
    CleanupStack::PushL( sbFrame );
    sbFrame->CreateDoubleSpanScrollBarsL( ETrue, EFalse );

    CEikScrollBar::TOrientation orientation = CEikScrollBar::EHorizontal;
    CEikScrollBarFrame::TScrollBarVisibility sbVisibility = sbFrame->ScrollBarVisibility( orientation );
    STIF_ASSERT_EQUALS( CEikScrollBarFrame::EOff, sbVisibility );

    CleanupStack::PopAndDestroy( sbFrame );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKSbFrmDrawBgL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKSbFrmDrawBgL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKSbFrmDrawBg, "in SbFrmDrawBg" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKSbFrmDrawBg );
    // Print to log file
    iLog->Log( KTestSDKSbFrmDrawBg );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CEikScrollBarFrame* sbFrame = new ( ELeave ) CEikScrollBarFrame( control, control );
    CleanupStack::PushL( sbFrame );
    sbFrame->CreateDoubleSpanScrollBarsL( ETrue, EFalse );

    TInt err = sbFrame->DrawBackground( ETrue, ETrue );

    CleanupStack::PopAndDestroy( sbFrame );
    CleanupStack::PopAndDestroy( control );
    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKSbFrmDrawBgStateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKSbFrmDrawBgStateL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKSbFrmDrawBgState, "in SbFrmDrawBgState" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKSbFrmDrawBgState );
    // Print to log file
    iLog->Log( KTestSDKSbFrmDrawBgState );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CEikScrollBarFrame* sbFrame = new ( ELeave ) CEikScrollBarFrame( control, control );
    CleanupStack::PushL( sbFrame );
    sbFrame->CreateDoubleSpanScrollBarsL( ETrue, EFalse );

    TBool drawHorizontal = ETrue;
    TBool drawVertical = ETrue;
    TInt err = sbFrame->DrawBackgroundState( drawHorizontal, drawVertical );

    CleanupStack::PopAndDestroy( sbFrame );
    CleanupStack::PopAndDestroy( control );
    return err;

    }


