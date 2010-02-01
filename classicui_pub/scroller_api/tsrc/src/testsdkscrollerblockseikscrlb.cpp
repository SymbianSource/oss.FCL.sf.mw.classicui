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
* Description:  test eikscrlb.h
*
*/


// [INCLUDE FILES]
#include <eikscrlb.h>

#include "testsdkscroller.h"
#include "testsdkscrollercontrol.h"
#include "testsdkscrollereikscrlb.h"

// CONSTANTS
const TInt KPointX = 5;
const TInt KPointY = 5;
const TInt KWidth = 100;
const TInt KHeight = 100;
const TInt KLength = 9;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKEikSbmDefConsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKEikSbmDefConsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKEikSbmDefCons, "in EikSbmDefCons" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKEikSbmDefCons );
    // Print to log file
    iLog->Log( KTestSDKEikSbmDefCons );

    TEikScrollBarModel* sbModel = new ( ELeave ) TEikScrollBarModel;
    CleanupStack::PushL( sbModel );
    STIF_ASSERT_NOT_NULL( sbModel );

    CleanupStack::PopAndDestroy( sbModel );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKEikSbmDefConsWithPaL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKEikSbmDefConsWithPaL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKEikSbmDefConsWithPa, "in EikSbmDefConsWithPa" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKEikSbmDefConsWithPa );
    // Print to log file
    iLog->Log( KTestSDKEikSbmDefConsWithPa );

    TInt scSpan = 0;
    TEikScrollBarModel* sbModel = new ( ELeave ) TEikScrollBarModel( scSpan );
    CleanupStack::PushL( sbModel );
    STIF_ASSERT_NOT_NULL( sbModel );

    CleanupStack::PopAndDestroy( sbModel );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKEikSbmEquOpaL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKEikSbmEquOpaL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKEikSbmEquOpa, "in EikSbmEquOpa" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKEikSbmEquOpa );
    // Print to log file
    iLog->Log( KTestSDKEikSbmEquOpa );

    TInt scSpan = 0;
    TEikScrollBarModel* sbModel = new ( ELeave ) TEikScrollBarModel( scSpan );
    CleanupStack::PushL( sbModel );
    TEikScrollBarModel* model = new ( ELeave ) TEikScrollBarModel( scSpan );
    CleanupStack::PushL( model );
    STIF_ASSERT_TRUE( *sbModel == *model );

    CleanupStack::PopAndDestroy( model );
    CleanupStack::PopAndDestroy( sbModel );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKEikSbmNotEquOpaL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKEikSbmNotEquOpaL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKEikSbmNotEquOpa, "in EikSbmNotEquOpa" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKEikSbmNotEquOpa );
    // Print to log file
    iLog->Log( KTestSDKEikSbmNotEquOpa );

    TInt scSpan = 0;
    TEikScrollBarModel* sbModel = new ( ELeave ) TEikScrollBarModel( scSpan );
    CleanupStack::PushL( sbModel );
    TEikScrollBarModel* model = new ( ELeave ) TEikScrollBarModel( scSpan );
    CleanupStack::PushL( model );
    STIF_ASSERT_FALSE( *sbModel != *model );

    CleanupStack::PopAndDestroy( model );
    CleanupStack::PopAndDestroy( sbModel );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKEikSbmSbUsefulL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKEikSbmSbUsefulL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKEikSbmSbUseful, "in EikSbmSbUseful" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKEikSbmSbUseful );
    // Print to log file
    iLog->Log( KTestSDKEikSbmSbUseful );

    TInt scSpan = 1;
    TEikScrollBarModel* sbModel = new ( ELeave ) TEikScrollBarModel( scSpan );
    CleanupStack::PushL( sbModel );

    TBool sbUseful = sbModel->ScrollBarUseful();
    STIF_ASSERT_TRUE( sbUseful );

    CleanupStack::PopAndDestroy( sbModel );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKEikSbmMaxThumbPosL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKEikSbmMaxThumbPosL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKEikSbmMaxThumbPos, "in EikSbmMaxThumbPos" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKEikSbmMaxThumbPos );
    // Print to log file
    iLog->Log( KTestSDKEikSbmMaxThumbPos );

    TInt scSpan = 1;
    TEikScrollBarModel* sbModel = new ( ELeave ) TEikScrollBarModel( scSpan );
    CleanupStack::PushL( sbModel );

    TInt maxThumbPos = sbModel->MaxThumbPos();
    STIF_ASSERT_EQUALS( scSpan, maxThumbPos );

    CleanupStack::PopAndDestroy( sbModel );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKEikSbmCheckBoundsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKEikSbmCheckBoundsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKEikSbmCheckBounds, "in EikSbmCheckBounds" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKEikSbmCheckBounds );
    // Print to log file
    iLog->Log( KTestSDKEikSbmCheckBounds );

    TInt scSpan = 1;
    TEikScrollBarModel* sbModel = new ( ELeave ) TEikScrollBarModel( scSpan );
    CleanupStack::PushL( sbModel );

    sbModel->CheckBounds();

    CleanupStack::PopAndDestroy( sbModel );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKDsModelDefConsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKDsModelDefConsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKDsModelDefCons, "in DsModelDefCons" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKDsModelDefCons );
    // Print to log file
    iLog->Log( KTestSDKDsModelDefCons );

    TAknDoubleSpanScrollBarModel* dsModel = new ( ELeave ) TAknDoubleSpanScrollBarModel;
    CleanupStack::PushL( dsModel );
    STIF_ASSERT_NOT_NULL( dsModel );

    CleanupStack::PopAndDestroy( dsModel );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKDsModelDefConsWithPaL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKDsModelDefConsWithPaL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKDsModelDefConsWithPa, "in DsModelDefConsWithPa" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKDsModelDefConsWithPa );
    // Print to log file
    iLog->Log( KTestSDKDsModelDefConsWithPa );

    TEikScrollBarModel* sbModel = new ( ELeave ) TEikScrollBarModel;
    CleanupStack::PushL( sbModel );
    TAknDoubleSpanScrollBarModel* dsModel = new ( ELeave )
            TAknDoubleSpanScrollBarModel( *sbModel );
    CleanupStack::PushL( dsModel );
    STIF_ASSERT_NOT_NULL( dsModel );

    CleanupStack::PopAndDestroy( dsModel );
    CleanupStack::PopAndDestroy( sbModel );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKDsModelSetScrollSpanL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKDsModelSetScrollSpanL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKDsModelSetScrollSpan, "in DsModelSetScrollSpan" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKDsModelSetScrollSpan );
    // Print to log file
    iLog->Log( KTestSDKDsModelSetScrollSpan );

    TAknDoubleSpanScrollBarModel* dsModel = new ( ELeave ) TAknDoubleSpanScrollBarModel;
    CleanupStack::PushL( dsModel );

    TInt value = 1;
    dsModel->SetScrollSpan( value );

    CleanupStack::PopAndDestroy( dsModel );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKDsModelSetFocusPosL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKDsModelSetFocusPosL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKDsModelSetFocusPos, "in DsModelSetFocusPos" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKDsModelSetFocusPos );
    // Print to log file
    iLog->Log( KTestSDKDsModelSetFocusPos );

    TAknDoubleSpanScrollBarModel* dsModel = new ( ELeave ) TAknDoubleSpanScrollBarModel;
    CleanupStack::PushL( dsModel );

    TInt value = 1;
    dsModel->SetFocusPosition( value );

    CleanupStack::PopAndDestroy( dsModel );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKDsModelSetWinSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKDsModelSetWinSizeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKDsModelSetWinSize, "in DsModelSetWinSize" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKDsModelSetWinSize );
    // Print to log file
    iLog->Log( KTestSDKDsModelSetWinSize );

    TAknDoubleSpanScrollBarModel* dsModel = new ( ELeave ) TAknDoubleSpanScrollBarModel;
    CleanupStack::PushL( dsModel );

    TInt value = 1;
    dsModel->SetWindowSize( value );

    CleanupStack::PopAndDestroy( dsModel );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKDsModelSetFieldSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKDsModelSetFieldSizeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKDsModelSetFieldSize, "in DsModelSetFieldSize" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKDsModelSetFieldSize );
    // Print to log file
    iLog->Log( KTestSDKDsModelSetFieldSize );

    TAknDoubleSpanScrollBarModel* dsModel = new ( ELeave ) TAknDoubleSpanScrollBarModel;
    CleanupStack::PushL( dsModel );

    TInt value = 1;
    dsModel->SetFieldSize( value );

    CleanupStack::PopAndDestroy( dsModel );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKDsModelSetFieldPosL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKDsModelSetFieldPosL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKDsModelSetFieldPos, "in DsModelSetFieldPos" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKDsModelSetFieldPos );
    // Print to log file
    iLog->Log( KTestSDKDsModelSetFieldPos );

    TAknDoubleSpanScrollBarModel* dsModel = new ( ELeave ) TAknDoubleSpanScrollBarModel;
    CleanupStack::PushL( dsModel );

    TInt value = 1;
    dsModel->SetFieldPosition( value );

    CleanupStack::PopAndDestroy( dsModel );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKDsModelScrollSpanL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKDsModelScrollSpanL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKDsModelScrollSpan, "in DsModelScrollSpan" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKDsModelScrollSpan );
    // Print to log file
    iLog->Log( KTestSDKDsModelScrollSpan );

    TAknDoubleSpanScrollBarModel* dsModel = new ( ELeave ) TAknDoubleSpanScrollBarModel;
    CleanupStack::PushL( dsModel );

    TInt value = dsModel->ScrollSpan();
    STIF_ASSERT_EQUALS( 0, value );

    CleanupStack::PopAndDestroy( dsModel );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKDsModelFocusPosL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKDsModelFocusPosL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKDsModelFocusPos, "in DsModelFocusPos" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKDsModelFocusPos );
    // Print to log file
    iLog->Log( KTestSDKDsModelFocusPos );

    TAknDoubleSpanScrollBarModel* dsModel = new ( ELeave ) TAknDoubleSpanScrollBarModel;
    CleanupStack::PushL( dsModel );

    TInt value = dsModel->FocusPosition();
    STIF_ASSERT_EQUALS( 0, value );

    CleanupStack::PopAndDestroy( dsModel );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKDsModelWinSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKDsModelWinSizeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKDsModelWinSize, "in DsModelWinSize" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKDsModelWinSize );
    // Print to log file
    iLog->Log( KTestSDKDsModelWinSize );

    TAknDoubleSpanScrollBarModel* dsModel = new ( ELeave ) TAknDoubleSpanScrollBarModel;
    CleanupStack::PushL( dsModel );

    TInt value = dsModel->WindowSize();
    STIF_ASSERT_EQUALS( 0, value );

    CleanupStack::PopAndDestroy( dsModel );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKDsModelFieldSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKDsModelFieldSizeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKDsModelFieldSize, "in DsModelFieldSize" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKDsModelFieldSize );
    // Print to log file
    iLog->Log( KTestSDKDsModelFieldSize );

    TAknDoubleSpanScrollBarModel* dsModel = new ( ELeave ) TAknDoubleSpanScrollBarModel;
    CleanupStack::PushL( dsModel );

    TInt value = dsModel->FieldSize();
    STIF_ASSERT_EQUALS( 0, value );

    CleanupStack::PopAndDestroy( dsModel );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKDsModelFieldPosL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKDsModelFieldPosL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKDsModelFieldPos, "in DsModelFieldPos" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKDsModelFieldPos );
    // Print to log file
    iLog->Log( KTestSDKDsModelFieldPos );

    TAknDoubleSpanScrollBarModel* dsModel = new ( ELeave ) TAknDoubleSpanScrollBarModel;
    CleanupStack::PushL( dsModel );

    TInt value = dsModel->FieldPosition();
    STIF_ASSERT_EQUALS( 0, value );

    CleanupStack::PopAndDestroy( dsModel );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKEikSbDefConsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKEikSbDefConsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKEikSbDefCons, "in EikSbDefCons" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKEikSbDefCons );
    // Print to log file
    iLog->Log( KTestSDKEikSbDefCons );

    CEikScrollBar* scBar = new ( ELeave ) CEikScrollBar;
    CleanupStack::PushL( scBar );
    STIF_ASSERT_NOT_NULL( scBar );

    CleanupStack::PopAndDestroy( scBar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKEikSbConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKEikSbConstructL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKEikSbConstructL, "in EikSbConstructL" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKEikSbConstructL );
    // Print to log file
    iLog->Log( KTestSDKEikSbConstructL );

    CEikScrollBar* scBar = new ( ELeave ) CEikScrollBar;
    CleanupStack::PushL( scBar );
    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CEikScrollBar::TOrientation orientation = CEikScrollBar::EVertical;

    scBar->ConstructL( control, control, orientation, KLength );

    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( scBar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKEikSbSetLengthL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKEikSbSetLengthL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKEikSbSetLengthL, "in EikSbSetLengthL" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKEikSbSetLengthL );
    // Print to log file
    iLog->Log( KTestSDKEikSbSetLengthL );

    CEikScrollBar* scBar = new ( ELeave ) CEikScrollBar;
    CleanupStack::PushL( scBar );
    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CEikScrollBar::TOrientation orientation = CEikScrollBar::EVertical;
    scBar->ConstructL( control, control, orientation, KLength );

    scBar->SetLengthL( KLength );

    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( scBar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKEikSbSetModelL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKEikSbSetModelL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKEikSbSetModelL, "in EikSbSetModelL" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKEikSbSetModelL );
    // Print to log file
    iLog->Log( KTestSDKEikSbSetModelL );

    CEikScrollBar* scBar = new ( ELeave ) CEikScrollBar;
    CleanupStack::PushL( scBar );
    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CEikScrollBar::TOrientation orientation = CEikScrollBar::EVertical;
    scBar->ConstructL( control, control, orientation, KLength );

    TEikScrollBarModel* sbModel = new ( ELeave ) TEikScrollBarModel;
    CleanupStack::PushL( sbModel );
    scBar->SetModelL( sbModel );

    CleanupStack::PopAndDestroy( sbModel );
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( scBar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKEikSbSetModeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKEikSbSetModeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKEikSbSetModel, "in EikSbSetModel" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKEikSbSetModel );
    // Print to log file
    iLog->Log( KTestSDKEikSbSetModel );

    CEikScrollBar* scBar = new ( ELeave ) CEikScrollBar;
    CleanupStack::PushL( scBar );
    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CEikScrollBar::TOrientation orientation = CEikScrollBar::EVertical;
    scBar->ConstructL( control, control, orientation, KLength );

    TEikScrollBarModel* sbModel = new ( ELeave ) TEikScrollBarModel;
    CleanupStack::PushL( sbModel );
    scBar->SetModel( sbModel );

    CleanupStack::PopAndDestroy( sbModel );
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( scBar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKEikSbSetLenAndModL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKEikSbSetLenAndModL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKEikSbSetLenAndModL, "in EikSbSetLenAndModL" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKEikSbSetLenAndModL );
    // Print to log file
    iLog->Log( KTestSDKEikSbSetLenAndModL );

    CEikScrollBar* scBar = new ( ELeave ) CEikScrollBar;
    CleanupStack::PushL( scBar );
    TEikScrollBarModel* sbModel = new ( ELeave ) TEikScrollBarModel;
    CleanupStack::PushL( sbModel );

    scBar->SetLengthAndModelL( KLength, sbModel );

    CleanupStack::PopAndDestroy( sbModel );
    CleanupStack::PopAndDestroy( scBar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKEikSbSetModThuPosL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKEikSbSetModThuPosL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKEikSbSetModThuPos, "in EikSbSetModThuPos" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKEikSbSetModThuPos );
    // Print to log file
    iLog->Log( KTestSDKEikSbSetModThuPos );

    CEikScrollBar* scBar = new ( ELeave ) CEikScrollBar;
    CleanupStack::PushL( scBar );
    TInt thumbPos = 0;

    scBar->SetModelThumbPosition( thumbPos );

    CleanupStack::PopAndDestroy( scBar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKEikSbSetFoPosToThPosL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKEikSbSetFoPosToThPosL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKEikSbSetFoPosToThPos, "in EikSbSetFoPosToThPos" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKEikSbSetFoPosToThPos );
    // Print to log file
    iLog->Log( KTestSDKEikSbSetFoPosToThPos );

    CEikScrollBar* scBar = new ( ELeave ) CEikScrollBar;
    CleanupStack::PushL( scBar );
    TInt focusPos = 0;

    scBar->SetFocusPosToThumbPos( focusPos );

    CleanupStack::PopAndDestroy( scBar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKEikSbDefSbBreadth
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKEikSbDefSbBreadth( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKEikSbDefSbBreadth, "in EikSbDefSbBreadth" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKEikSbDefSbBreadth );
    // Print to log file
    iLog->Log( KTestSDKEikSbDefSbBreadth );

    TInt breadth = CEikScrollBar::DefaultScrollBarBreadth();
    STIF_ASSERT_EQUALS( KLength, breadth );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKEikSbPoModelL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKEikSbPoModelL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKEikSbPoModel, "in EikSbPoModel" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKEikSbPoModel );
    // Print to log file
    iLog->Log( KTestSDKEikSbPoModel );

    CEikScrollBar* scBar = new ( ELeave ) CEikScrollBar;
    CleanupStack::PushL( scBar );

    const TEikScrollBarModel* sbModel = scBar->Model();
    STIF_ASSERT_NOT_NULL( sbModel );

    CleanupStack::PopAndDestroy( scBar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKEikSbThumbPosL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKEikSbThumbPosL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKEikSbThumbPos, "in EikSbThumbPos" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKEikSbThumbPos );
    // Print to log file
    iLog->Log( KTestSDKEikSbThumbPos );

    CEikScrollBar* scBar = new ( ELeave ) CEikScrollBar;
    CleanupStack::PushL( scBar );

    TInt thumbPos = scBar->ThumbPosition();
    STIF_ASSERT_EQUALS( 0, thumbPos );

    CleanupStack::PopAndDestroy( scBar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKEikSbScBarBreaL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKEikSbScBarBreaL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKEikSbScBarBrea, "in EikSbScBarBrea" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKEikSbScBarBrea );
    // Print to log file
    iLog->Log( KTestSDKEikSbScBarBrea );

    CEikScrollBar* scBar = new ( ELeave ) CEikScrollBar;
    CleanupStack::PushL( scBar );

    TInt sbBreadth = scBar->ScrollBarBreadth();
    STIF_ASSERT_EQUALS( 0, sbBreadth );

    CleanupStack::PopAndDestroy( scBar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKEikSbMinVisLen
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKEikSbMinVisLen( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKEikSbMinVisLen, "in EikSbMinVisLen" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKEikSbMinVisLen );
    // Print to log file
    iLog->Log( KTestSDKEikSbMinVisLen );

    TInt sbFlags = 0;
    TInt minLength = CEikScrollBar::MinVisibleLength( sbFlags );
    STIF_ASSERT_EQUALS( 0, minLength );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKEikSbSetDecButDimmedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKEikSbSetDecButDimmedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKEikSbSetDecButDimmed, "in EikSbSetDecButDimmed" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKEikSbSetDecButDimmed );
    // Print to log file
    iLog->Log( KTestSDKEikSbSetDecButDimmed );

    CEikScrollBar* scBar = new ( ELeave ) CEikScrollBar;
    CleanupStack::PushL( scBar );

    scBar->SetDecreaseButtonsDimmed( ETrue );

    CleanupStack::PopAndDestroy( scBar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKEikSbSetIncButDimmedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKEikSbSetIncButDimmedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKEikSbSetIncButDimmed, "in EikSbSetIncButDimmed" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKEikSbSetIncButDimmed );
    // Print to log file
    iLog->Log( KTestSDKEikSbSetIncButDimmed );

    CEikScrollBar* scBar = new ( ELeave ) CEikScrollBar;
    CleanupStack::PushL( scBar );

    scBar->SetIncreaseButtonsDimmed( ETrue );

    CleanupStack::PopAndDestroy( scBar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKEikSbSetAllButDimmedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKEikSbSetAllButDimmedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKEikSbSetAllButDimmed, "in EikSbSetAllButDimmed" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKEikSbSetAllButDimmed );
    // Print to log file
    iLog->Log( KTestSDKEikSbSetAllButDimmed );

    CEikScrollBar* scBar = new ( ELeave ) CEikScrollBar;
    CleanupStack::PushL( scBar );

    scBar->SetAllButtonsDimmed( ETrue );

    CleanupStack::PopAndDestroy( scBar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKEikSbIncNudgeButL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKEikSbIncNudgeButL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKEikSbIncNudgeBut, "in EikSbIncNudgeBut" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKEikSbIncNudgeBut );
    // Print to log file
    iLog->Log( KTestSDKEikSbIncNudgeBut );

    CEikScrollBar* scBar = new ( ELeave ) CEikScrollBar;
    CleanupStack::PushL( scBar );

    CAknScrollButton* scBut = scBar->IncreaseNudgeButton();
    STIF_ASSERT_NULL( scBut );

    CleanupStack::PopAndDestroy( scBar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKEikSbDecNudgeButL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKEikSbDecNudgeButL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKEikSbDecNudgeBut, "in EikSbDecNudgeBut" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKEikSbDecNudgeBut );
    // Print to log file
    iLog->Log( KTestSDKEikSbDecNudgeBut );

    CEikScrollBar* scBar = new ( ELeave ) CEikScrollBar;
    CleanupStack::PushL( scBar );

    CAknScrollButton* scBut = scBar->DecreaseNudgeButton();
    STIF_ASSERT_NULL( scBut );

    CleanupStack::PopAndDestroy( scBar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKEikSbSetContCbaL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKEikSbSetContCbaL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKEikSbSetContCba, "in EikSbSetContCba" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKEikSbSetContCba );
    // Print to log file
    iLog->Log( KTestSDKEikSbSetContCba );

    CEikScrollBar* scBar = new ( ELeave ) CEikScrollBar;
    CleanupStack::PushL( scBar );
    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CEikScrollBar::TOrientation orientation = CEikScrollBar::EVertical;
    scBar->ConstructL( control, control, orientation, KLength );
    CEikCba* cba = NULL;

    scBar->SetContainingCba( cba );

    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( scBar );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKEikSbMakeVisibleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKEikSbMakeVisibleL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKEikSbMakeVisible, "in EikSbMakeVisible" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKEikSbMakeVisible );
    // Print to log file
    iLog->Log( KTestSDKEikSbMakeVisible );

    CEikScrollBar* scBar = new ( ELeave ) CEikScrollBar;
    CleanupStack::PushL( scBar );

    scBar->MakeVisible( ETrue );

    CleanupStack::PopAndDestroy( scBar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKEikSbHanPointEveL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKEikSbHanPointEveL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKEikSbHanPointEveL, "in EikSbHanPointEveL" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKEikSbHanPointEveL );
    // Print to log file
    iLog->Log( KTestSDKEikSbHanPointEveL );

    CEikScrollBar* scBar = new ( ELeave ) CEikScrollBar;
    CleanupStack::PushL( scBar );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( KPointX, KPointY );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;

    scBar->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( scBar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKEikSbCompCtrlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKEikSbCompCtrlL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKEikSbCompCtrl, "in EikSbCompCtrl" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKEikSbCompCtrl );
    // Print to log file
    iLog->Log( KTestSDKEikSbCompCtrl );

    CEikScrollBarExt* scBarExt = new ( ELeave ) CEikScrollBarExt;
    CleanupStack::PushL( scBarExt );

    TInt index = 0;
    CCoeControl* control = scBarExt->DoComponentControl( index );
    STIF_ASSERT_NULL( control );

    CleanupStack::PopAndDestroy( scBarExt );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKEikSbCountCompCtrlsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKEikSbCountCompCtrlsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKEikSbCountCompCtrls, "in EikSbCountCompCtrls" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKEikSbCountCompCtrls );
    // Print to log file
    iLog->Log( KTestSDKEikSbCountCompCtrls );

    CEikScrollBarExt* scBarExt = new ( ELeave ) CEikScrollBarExt;
    CleanupStack::PushL( scBarExt );

    TInt count = scBarExt->DoCountComponentControls();
    STIF_ASSERT_EQUALS( 0, count );

    CleanupStack::PopAndDestroy( scBarExt );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKEikSbSetButPosL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKEikSbSetButPosL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKEikSbSetButPosL, "in EikSbSetButPosL" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKEikSbSetButPosL );
    // Print to log file
    iLog->Log( KTestSDKEikSbSetButPosL );

    CEikScrollBarExt* scBarExt = new ( ELeave ) CEikScrollBarExt;
    CleanupStack::PushL( scBarExt );
    CAknScrollButton::TType type = CAknScrollButton::ENudgeUp;
    CAknScrollButton* scBut = CAknScrollButton::NewL( type );
    CleanupStack::PushL( scBut );

    scBarExt->DoSetButtonPositionL( scBut );

    CleanupStack::PopAndDestroy( scBut );
    CleanupStack::PopAndDestroy( scBarExt );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKArrHeSbDefConsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKArrHeSbDefConsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKArrHeSbDefCons, "in ArrHeSbDefCons" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKArrHeSbDefCons );
    // Print to log file
    iLog->Log( KTestSDKArrHeSbDefCons );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );

    CEikArrowHeadScrollBar* ahScBar = new ( ELeave ) CEikArrowHeadScrollBar( control );
    CleanupStack::PushL( ahScBar );
    STIF_ASSERT_NOT_NULL( ahScBar );

    CleanupStack::PopAndDestroy( ahScBar );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKArrHeSbConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKArrHeSbConstructL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKArrHeSbConstructL, "in ArrHeSbConstructL" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKArrHeSbConstructL );
    // Print to log file
    iLog->Log( KTestSDKArrHeSbConstructL );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CEikArrowHeadScrollBar* ahScBar = new ( ELeave ) CEikArrowHeadScrollBar( control );
    CleanupStack::PushL( ahScBar );
    CEikScrollBar::TOrientation orientation = CEikScrollBar::EVertical;

    ahScBar->ConstructL( control, control, orientation, KLength );

    CleanupStack::PopAndDestroy( ahScBar );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKArrHeSbHanPointEveL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKArrHeSbHanPointEveL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKArrHeSbHanPointEveL, "in ArrHeSbHanPointEveL" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKArrHeSbHanPointEveL );
    // Print to log file
    iLog->Log( KTestSDKArrHeSbHanPointEveL );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CEikArrowHeadScrollBar* ahScBar = new ( ELeave ) CEikArrowHeadScrollBar( control );
    CleanupStack::PushL( ahScBar );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( KPointX, KPointY );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;

    ahScBar->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( ahScBar );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKDbSpaSbDefConsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKDbSpaSbDefConsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKDbSpaSbDefCons, "in DbSpaSbDefCons" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKDbSpaSbDefCons );
    // Print to log file
    iLog->Log( KTestSDKDbSpaSbDefCons );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );

    CAknDoubleSpanScrollBar* dbSpanSb = new ( ELeave ) CAknDoubleSpanScrollBar( control );
    CleanupStack::PushL( dbSpanSb );
    STIF_ASSERT_NOT_NULL( dbSpanSb );

    CleanupStack::PopAndDestroy( dbSpanSb );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKDbSpaSbSetFlRectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKDbSpaSbSetFlRectL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKDbSpaSbSetFlRect, "in DbSpaSbSetFlRect" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKDbSpaSbSetFlRect );
    // Print to log file
    iLog->Log( KTestSDKDbSpaSbSetFlRect );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CAknDoubleSpanScrollBar* dbSpanSb = new ( ELeave ) CAknDoubleSpanScrollBar( control );
    CleanupStack::PushL( dbSpanSb );

    TSize size( KWidth, KHeight );
    TRect rect( size );
    dbSpanSb->SetFixedLayoutRect( rect );

    CleanupStack::PopAndDestroy( dbSpanSb );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKDbSpaSbConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKDbSpaSbConstructL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKDbSpaSbConstructL, "in DbSpaSbConstructL" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKDbSpaSbConstructL );
    // Print to log file
    iLog->Log( KTestSDKDbSpaSbConstructL );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CAknDoubleSpanScrollBar* dbSpanSb = new ( ELeave ) CAknDoubleSpanScrollBar( control );
    CleanupStack::PushL( dbSpanSb );
    CEikScrollBar::TOrientation orientation = CEikScrollBar::EVertical;

    dbSpanSb->ConstructL( EFalse, control, control, orientation, KLength );

    CleanupStack::PopAndDestroy( dbSpanSb );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKDbSpaSbSetSpInfoTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKDbSpaSbSetSpInfoTextL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKDbSpaSbSetSpInfoTextL, "in DbSpaSbSetSpInfoTextL" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKDbSpaSbSetSpInfoTextL );
    // Print to log file
    iLog->Log( KTestSDKDbSpaSbSetSpInfoTextL );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CAknDoubleSpanScrollBar* dbSpanSb = new ( ELeave ) CAknDoubleSpanScrollBar( control );
    CleanupStack::PushL( dbSpanSb );

    _LIT( KText, "ScrollPopupInfoText" );
    dbSpanSb->SetScrollPopupInfoTextL( KText );

    CleanupStack::PopAndDestroy( dbSpanSb );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKDbSpaSbConstructExtL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKDbSpaSbConstructExtL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKDbSpaSbConstructExtL, "in DbSpaSbConstructExtL" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKDbSpaSbConstructExtL );
    // Print to log file
    iLog->Log( KTestSDKDbSpaSbConstructExtL );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CAknDoubleSpanScrollBar* dbSpanSb = new ( ELeave ) CAknDoubleSpanScrollBar( control );
    CleanupStack::PushL( dbSpanSb );
    CEikScrollBar::TOrientation orientation = CEikScrollBar::EVertical;

    dbSpanSb->ConstructL( control, control, orientation, KLength );

    CleanupStack::PopAndDestroy( dbSpanSb );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKDbSpaSbMakeVisibleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKDbSpaSbMakeVisibleL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKDbSpaSbMakeVisible, "in DbSpaSbMakeVisible" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKDbSpaSbMakeVisible );
    // Print to log file
    iLog->Log( KTestSDKDbSpaSbMakeVisible );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CAknDoubleSpanScrollBar* dbSpanSb = new ( ELeave ) CAknDoubleSpanScrollBar( control );
    CleanupStack::PushL( dbSpanSb );
    CEikScrollBar::TOrientation orientation = CEikScrollBar::EVertical;
    dbSpanSb->ConstructL( EFalse, control, control, orientation, KLength );

    dbSpanSb->MakeVisible( ETrue );

    CleanupStack::PopAndDestroy( dbSpanSb );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKDbSpaSbHanPointEveL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKDbSpaSbHanPointEveL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKDbSpaSbHanPointEveL, "in DbSpaSbHanPointEveL" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKDbSpaSbHanPointEveL );
    // Print to log file
    iLog->Log( KTestSDKDbSpaSbHanPointEveL );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CAknDoubleSpanScrollBar* dbSpanSb = new ( ELeave ) CAknDoubleSpanScrollBar( control );
    CleanupStack::PushL( dbSpanSb );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( KPointX, KPointY );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;

    dbSpanSb->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( dbSpanSb );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKDbSpaSbCompCtrlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKDbSpaSbCompCtrlL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKDbSpaSbCompCtrl, "in DbSpaSbCompCtrl" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKDbSpaSbCompCtrl );
    // Print to log file
    iLog->Log( KTestSDKDbSpaSbCompCtrl );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CAknDouSpanScBarExt* dbSpaSbExt = new ( ELeave ) CAknDouSpanScBarExt( control );
    CleanupStack::PushL( dbSpaSbExt );

    TInt index = 0;
    CCoeControl* dbControl = dbSpaSbExt->DoComponentControl( index );
    STIF_ASSERT_NULL( dbControl );

    CleanupStack::PopAndDestroy( dbSpaSbExt );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKDbSpaSbCountCompCtrlsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKDbSpaSbCountCompCtrlsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKDbSpaSbCountCompCtrls, "in DbSpaSbCountCompCtrls" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKDbSpaSbCountCompCtrls );
    // Print to log file
    iLog->Log( KTestSDKDbSpaSbCountCompCtrls );

    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CAknDouSpanScBarExt* dbSpaSbExt = new ( ELeave ) CAknDouSpanScBarExt( control );
    CleanupStack::PushL( dbSpaSbExt );

    TInt count = dbSpaSbExt->DoCountComponentControls();
    STIF_ASSERT_EQUALS( 0, count );

    CleanupStack::PopAndDestroy( dbSpaSbExt );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKScroller::TestSDKEikSbSetExtensionAreaTypeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKScroller::TestSDKEikSbSetExtensionAreaTypeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKScroller, "testsdkscroller" );
    _LIT( KTestSDKEikSbSetExtensionAreaTypeL, "in EikSbSetExtensionAreaTypeL" );
    TestModuleIf().Printf( 0, KTestSDKScroller, KTestSDKEikSbSetExtensionAreaTypeL );
    // Print to log file
    iLog->Log( KTestSDKEikSbSetExtensionAreaTypeL );

    CEikScrollBar* scBar = new ( ELeave ) CEikScrollBar;
    CleanupStack::PushL( scBar );
    CTestScrollerControl* control = CTestScrollerControl::NewL();
    CleanupStack::PushL( control );
    CEikScrollBar::TOrientation orientation = CEikScrollBar::EVertical;
    scBar->ConstructL( control, control, orientation, KLength );

    scBar->SetExtensionAreaType( CEikScrollBar::ENormalExpandedTouchArea );

    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( scBar );
    return KErrNone;

    }


// [End of file]
