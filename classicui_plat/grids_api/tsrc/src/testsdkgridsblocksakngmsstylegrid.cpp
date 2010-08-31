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
* Description:  Test akngmsstylegrid.h
*
*/


/*
 *  [INCLUDE FILES]
 */
#include <akngmsstylegrid.h>
#include <stifparser.h>
#include <eiklbo.h>
#include <aknview.h> 
#include <coeaui.h>
#include <coecobs.h>
#include <akngrid.h>
#include <w32std.h>
#include <testsdkgrids.rsg>
#include <barsread.h>
#include <eikdialg.h>

#include "testsdkgridscontainer.h"
#include "testsdkgrids.h"

const TInt KRectWidth = 50;
const TInt KRectHeight = 50;
const TInt KZero = 0;

// ============================ MEMBER FUNCTIONS ===============================

//==========================class CAknGMSStyleGridView==========================
// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsGMSSGVConstuctionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGMSSGVConstuctionL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGVConstuctionL, "In TestGridsGMSSGVConstuctionL" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGVConstuctionL );

    CAknGMSStyleGridView* gridView = new( ELeave ) CAknGMSStyleGridView();
    CleanupStack::PushL( gridView );
    STIF_ASSERT_NOT_NULL( gridView );
    CleanupStack::PopAndDestroy( gridView );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsGMSSGVDrawL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGMSSGVDrawL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGVDrawL, "In TestGridsGMSSGVDrawL" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGVDrawL );
    iLog->Log( KTestGridsGMSSGVDrawL );
    
    CAknGMSStyleGridView* gridView = new( ELeave ) CAknGMSStyleGridView();
    CleanupStack::PushL( gridView );
    CAknGrid* grid = new( ELeave ) CAknGrid();
    CleanupStack::PushL( grid );
    
    CAknGridM* model = new( ELeave ) CAknGridM();
    CleanupStack::PushL( model );
    grid->SetModel( model );
    CleanupStack::Pop( model );
    
    TResourceReader reader;
    CEikonEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDKGRIDS_GRID );
    grid->SetContainerWindowL( *iContainer );
    grid->ConstructFromResourceL( reader );
    
    CTextListBoxModel* modeltwo = grid->Model();
    CListItemDrawer* drawer = grid->ItemDrawer();
    CWsScreenDevice * screendevice = CEikonEnv::Static()->ScreenDevice();
    RWindowGroup& parent = CCoeEnv::Static()->RootWin();
    CEikDialog* mydialog= new(ELeave) CEikDialog; 
    mydialog->PrepareLC(R_TEST_DIALOG); 
    RWindow* window = (RWindow*)mydialog->DrawableWindow(); 
    TRect rect( TPoint( KRectWidth, KRectHeight ), TPoint( KRectWidth, KRectHeight ));
    
    gridView->ConstructL( modeltwo, drawer, screendevice, &parent, window, rect, KZero );
    gridView->SetupLayout( rect, ETrue, KZero );
    gridView->Draw();
    
    CleanupStack::PopAndDestroy( mydialog );
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( grid );
    CleanupStack::Pop( gridView );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsGMSSGVSetupLayoutL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGMSSGVSetupLayoutL( CStifItemParser& aItem )
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGVSetupLayoutL, "In TestGridsGMSSGVSetupLayoutL" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGVSetupLayoutL );
    iLog->Log( KTestGridsGMSSGVSetupLayoutL );

    CAknGMSStyleGridView* gridView = new( ELeave ) CAknGMSStyleGridView();
    CleanupStack::PushL( gridView );

    TRect rect = iContainer->Rect();
    
    TInt flag;
    TInt err = aItem.GetNextInt( flag );
    if( err != KErrNone)
        return err;
    switch ( flag )
        {
        case 1:
            gridView->SetupLayout( rect, EFalse, -1 );
            break;
        case 2:
            gridView->SetupLayout( rect, ETrue, 1 );
            break;
        default:
            break;
        }

    CleanupStack::PopAndDestroy( gridView );

    return KErrNone;
    }

//================================CAknGMSStyleGrid=============================//
// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsGMSSGNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGMSSGNewL( CStifItemParser& aItem )
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGNewL, "In TestGridsGMSSGNewL" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGNewL );
    iLog->Log( KTestGridsGMSSGNewL );

    TInt flag;
    TInt err = aItem.GetNextInt( flag );
    if( err != KErrNone)
        return err;
    switch ( flag )
        {
        case 1:
            iStyleGrid = CAknGMSStyleGrid::NewL( iContainer , EFalse );
            STIF_ASSERT_NOT_NULL( iStyleGrid );
            break;
        case 2:
            iStyleGrid = CAknGMSStyleGrid::NewL( iContainer , ETrue );
            STIF_ASSERT_NOT_NULL( iStyleGrid );
            break;
        default:
            break;
        }

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsGMSSGConstructionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGMSSGConstructionL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGConstructionL, "In TestGridsGMSSGConstructionL" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGConstructionL );
    iLog->Log( KTestGridsGMSSGConstructionL );

    iStyleGrid = new( ELeave ) CAknGMSStyleGrid();
    STIF_ASSERT_NOT_NULL( iStyleGrid );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsGMSSGConstructionWithTBoolL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGMSSGConstructionWithTBoolL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGConstructionWithTBoolL, "In TestGridsGMSSGConstructionWithTBoolL" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGConstructionWithTBoolL );
    iLog->Log( KTestGridsGMSSGConstructionWithTBoolL );

    iStyleGrid = new( ELeave ) CAknGMSStyleGrid( EFalse );
    STIF_ASSERT_NOT_NULL( iStyleGrid );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsGMSSGConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGMSSGConstructL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGConstructL, "In TestGridsGMSSGConstructL" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGConstructL );
    iLog->Log( KTestGridsGMSSGConstructL );

    TInt err;
    TRAP( err, iStyleGrid->ConstructL( iContainer, 1, 1 ) );

    return err;
    }

// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsGMSSGDelete
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGMSSGDelete( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGDelete, "In TestGridsGMSSGDelete" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGDelete );
    iLog->Log( KTestGridsGMSSGDelete );

    delete iStyleGrid;
    iStyleGrid = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsGMSSGSetupLayout
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGMSSGSetupLayout( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGSetupLayout, "In TestGridsGMSSGSetupLayout" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGSetupLayout );
    iLog->Log( KTestGridsGMSSGSetupLayout );

    iStyleGrid->SetupLayout();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsGMSSGHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGMSSGHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGHandlePointerEventL, "In TestGridsGMSSGHandlePointerEventL" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGHandlePointerEventL );
    iLog->Log( KTestGridsGMSSGHandlePointerEventL );

    TInt err;
    TPointerEvent pointerEvent( TPointerEvent::EButton1Up,
            EModifierAutorepeatable, TPoint( 20, 20 ), TPoint( 0, 0 ) );
    TRAP( err, iStyleGrid->HandlePointerEventL( pointerEvent ) ); 

    return err;
    }

// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsGMSSGSizeChanged
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGMSSGSizeChanged( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGSizeChanged, "In TestGridsGMSSGSizeChanged" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGSizeChanged );
    iLog->Log( KTestGridsGMSSGSizeChanged );

    iStyleGrid->SizeChanged();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsGMSSGMinimumSize
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGMSSGMinimumSize( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGMSSGMinimumSize" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );

    TSize minimumSize = iStyleGrid->MinimumSize();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsGMSSGOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGMSSGOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGMSSGMinimumSize" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );

    TInt err;
    TKeyEvent keyEvent = { EKeyPause, EStdKeySpace, 0, 0  };

    TRAP( err, iStyleGrid->OfferKeyEventL( keyEvent, EEventNull ) );

    return err;
    }

// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsGMSSGDraw
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGMSSGDraw( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGMSSGMinimumSize" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );

    TRect rect = iContainer->Rect();
    iStyleGrid->Draw( rect );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsGMSSGMakeViewClassInstanceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGMSSGMakeViewClassInstanceL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGMSSGMinimumSize" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );

    CListBoxView* listBoxView = iStyleGrid->MakeViewClassInstanceL();
    CleanupStack::PushL( listBoxView );

    STIF_ASSERT_NOT_NULL( listBoxView );
    
    CleanupStack::PopAndDestroy( listBoxView );
    
    return KErrNone;
    }

//==============================class CAknGMSPopupGrid==========================
// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsGMSPGNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGMSPGNewL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGMSSGMinimumSize" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );

    CAknGMSStyleGrid* styleGrid = CAknGMSStyleGrid::NewL( iContainer, EFalse );
    CleanupStack::PushL( styleGrid );
    CAknGMSPopupGrid* popupGrid = CAknGMSPopupGrid::NewL( styleGrid, R_GRIDS_CBA_OK_BACK, AknPopupLayouts::EMenuWindow );
    CleanupStack::PushL( popupGrid );

    STIF_ASSERT_NOT_NULL( popupGrid );
    CleanupStack::PopAndDestroy( popupGrid );
    CleanupStack::PopAndDestroy( styleGrid );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsGMSPGSetupWindowLayoutL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGMSPGSetupWindowLayoutL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGMSSGMinimumSize" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );

    CAknGMSStyleGrid* styleGrid = CAknGMSStyleGrid::NewL( iContainer, EFalse );
    CleanupStack::PushL( styleGrid );
    CAknGMSPopupGrid* popupGrid = CAknGMSPopupGrid::NewL( styleGrid, R_GRIDS_CBA_OK_BACK, AknPopupLayouts::EMenuWindow );
    CleanupStack::PushL( popupGrid );

    popupGrid->SetupWindowLayout( AknPopupLayouts::EMenuWindow );
    popupGrid->SetupWindowLayout( AknPopupLayouts::EMenuGraphicWindow );
    popupGrid->SetupWindowLayout( AknPopupLayouts::EMenuGraphicHeadingWindow );
    popupGrid->SetupWindowLayout( AknPopupLayouts::EMenuDoubleWindow );
    popupGrid->SetupWindowLayout( 
        AknPopupLayouts::EMenuDoubleLargeGraphicWindow );
    popupGrid->SetupWindowLayout( AknPopupLayouts::EPopupSNotePopupWindow );
    popupGrid->SetupWindowLayout( 
        AknPopupLayouts::EMenuUnknownColumnWindow );
    popupGrid->SetupWindowLayout( 
        AknPopupLayouts::EMenuUnknownFormattedCellWindow );
    popupGrid->SetupWindowLayout( AknPopupLayouts::EDynMenuWindow );
    popupGrid->SetupWindowLayout( AknPopupLayouts::EDynMenuGraphicWindow );
    popupGrid->SetupWindowLayout( AknPopupLayouts::EDynMenuGraphicHeadingWindow );
    popupGrid->SetupWindowLayout( AknPopupLayouts::EDynMenuDoubleWindow );
    popupGrid->SetupWindowLayout( AknPopupLayouts::EDynMenuDoubleLargeGraphicWindow );

    CleanupStack::PopAndDestroy( popupGrid );
    CleanupStack::PopAndDestroy( styleGrid );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsGMSPGCalcPopupGridLargeGraphicWindowL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGMSPGCalcPopupGridLargeGraphicWindowL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGMSSGMinimumSize" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );

    CAknGMSStyleGrid* styleGrid = CAknGMSStyleGrid::NewL( iContainer, EFalse );
    CleanupStack::PushL( styleGrid );
    CAknGMSPopupGrid* popupGrid = CAknGMSPopupGrid::NewL( styleGrid, R_GRIDS_CBA_OK_BACK, AknPopupLayouts::EMenuWindow );
    CleanupStack::PushL( popupGrid );

    TAknPopupWindowLayoutDef def;
    TRect rect = iContainer->Rect();
    TInt lines = 1;

    popupGrid->CalcPopupGridLargeGraphicWindow( def, rect, lines );

    CleanupStack::PopAndDestroy( popupGrid );
    CleanupStack::PopAndDestroy( styleGrid );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsGMSPGSetupPopupGridLargeGraphicWindowL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGMSPGSetupPopupGridLargeGraphicWindowL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGMSSGMinimumSize" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );

    CAknGMSStyleGrid* styleGrid = CAknGMSStyleGrid::NewL( iContainer, EFalse );
    CleanupStack::PushL( styleGrid );
    CAknGMSPopupGrid* popupGrid = CAknGMSPopupGrid::NewL( styleGrid, R_GRIDS_CBA_OK_BACK, AknPopupLayouts::EMenuWindow );
    CleanupStack::PushL( popupGrid );

    popupGrid->SetupWindowLayout( AknPopupLayouts::EMenuDoubleWindow );
    TAknPopupWindowLayoutDef def;
    TInt lines = 1;

    popupGrid->SetupPopupGridLargeGraphicWindow( def, lines, ETrue );

    CleanupStack::PopAndDestroy( popupGrid );
    CleanupStack::PopAndDestroy( styleGrid );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsGMSPGPopupGridLargeGraphicGraphicsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGMSPGPopupGridLargeGraphicGraphicsL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGMSSGMinimumSize" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );

    CAknGMSStyleGrid* styleGrid = CAknGMSStyleGrid::NewL( iContainer, EFalse );
    CleanupStack::PushL( styleGrid );
    CAknGMSPopupGrid* popupGrid = CAknGMSPopupGrid::NewL( styleGrid, R_GRIDS_CBA_OK_BACK, AknPopupLayouts::EMenuWindow );
    CleanupStack::PushL( popupGrid );

    TAknPopupWindowLayoutDef def;

    popupGrid->PopupGridLargeGraphicGraphics( def );

    CleanupStack::PopAndDestroy( popupGrid );
    CleanupStack::PopAndDestroy( styleGrid );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsGMSPGHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGMSPGHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGMSSGMinimumSize" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );

    CAknGMSStyleGrid* styleGrid = CAknGMSStyleGrid::NewL( iContainer, EFalse );
    CleanupStack::PushL( styleGrid );
    CAknGMSPopupGrid* popupGrid = CAknGMSPopupGrid::NewL( styleGrid, R_GRIDS_CBA_OK_BACK, AknPopupLayouts::EMenuWindow );
    CleanupStack::PushL( popupGrid );

    TPointerEvent pointerEvent( TPointerEvent::EButton1Up,
            EModifierAutorepeatable, TPoint( 20, 20 ), TPoint( 0, 0 ) );
    popupGrid->HandlePointerEventL( pointerEvent );

    CleanupStack::PopAndDestroy( popupGrid );
    CleanupStack::PopAndDestroy( styleGrid );

    return KErrNone;
    }

/*
 * End files
 */
