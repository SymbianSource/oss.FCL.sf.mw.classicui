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
* Description:  Test akngrid.h
*
*/


/*
 * Include files
 */
#include <coedef.h>
#include <akngrid.h>
#include <akngridm.h>
#include <stifparser.h>
#include <barsread.h>
#include <akngrid.h>
#include <aknlists.h>
#include <w32std.h>
#include <testsdkgrids.rsg>

#include "testsdkgridscontainer.h"
#include "testsdkgridsext.h"
#include "testsdkgrids.h"
#include "scrolbarsbserver.h"
#include "testsdkgridsview.h"

const TInt KColumnWidthZero = 0;
const TInt KColumnWidthTwo = 2;
const TInt KPointX = 1;
const TInt KPointY = 1;
const TInt KZero = 0;
const TInt KOne = 1;
const TInt KTwo = 2;
const TInt KThree = 3;
const TInt KMinusone = -1;
const TInt KTen = 10;
const TInt KThousand = 1000;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsGridConstructionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridConstructionL( CStifItemParser& /*aItem*/)
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGridConstructionL, "In TestGridsGridConstructionL" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGridConstructionL );
    iLog->Log( KTestGridsGridConstructionL );

    iGrid = new( ELeave ) CAknGrid();
    STIF_ASSERT_NOT_NULL( iGrid );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsGridDelete
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridDelete( CStifItemParser& /*aItem*/)
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGridDelete, "In KTestGridsGridDelete" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGridDelete );
    iLog->Log( KTestGridsGridDelete );

    delete iGrid;
    iGrid = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsGridSetModelL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridSetModelL( CStifItemParser& /*aItem*/)
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGridSetModelL, "In TestGridsGridSetModelL" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGridSetModelL );
    iLog->Log( KTestGridsGridSetModelL );

    CAknGridM* model = new( ELeave ) CAknGridM();
    CleanupStack::PushL( model );
    iGrid->SetModel( model );
    CleanupStack::Pop( model );

    STIF_ASSERT_NOT_NULL( iGrid );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsGridConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridConstructL( CStifItemParser& /*aItem*/)
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGridConstructL, "In KTestGridsGridConstructL" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGridConstructL );
    iLog->Log( KTestGridsGridConstructL );

    iGrid->ConstructL( iContainer, 0 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsGridConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridConstructFromResourceL( CStifItemParser& /*aItem*/)
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGridConstructFromResourceL, "In KTestGridsGridConstructFromResourceL" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGridConstructFromResourceL );
    iLog->Log( KTestGridsGridConstructFromResourceL );

    TInt err = KErrNone;
    TResourceReader reader;
    iGrid->SetContainerWindowL( *iContainer );
    CEikonEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDKGRIDS_GRID );

    TRAP( err, iGrid->ConstructFromResourceL( reader ) );

    CleanupStack::Pop( );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsGridSetLayoutL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridSetLayoutL( CStifItemParser& /*aItem*/)
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGConstructionWithTBoolL, "In TestGridsGMSSGConstructionWithTBoolL" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGConstructionWithTBoolL );
    iLog->Log( KTestGridsGMSSGConstructionWithTBoolL );

    TSize size = iContainer->Rect().Size( );

    iGrid->SetLayoutL( ETrue, ETrue, ETrue, KOne, KOne, size, KZero, KZero );
    iGrid->SetLayoutL( EFalse, ETrue, ETrue, KOne, KOne, size, KZero, KZero );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsGridSetLayoutFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridSetLayoutFromResourceL( CStifItemParser& /*aItem*/)
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGConstructL, "In TestGridsGMSSGConstructL" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGConstructL );
    iLog->Log( KTestGridsGMSSGConstructL );

    TInt err = KErrNone;
    TResourceReader reader;
    CEikonEnv::Static()->CreateResourceReaderLC( reader, R_AVKON_GRID_STYLE_DEFAULT );
    TRAP( err, iGrid->SetLayoutFromResourceL( reader ) );

    CleanupStack::PopAndDestroy( );

    return err;
    }

// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsGridSetPrimaryScrollingType
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridSetPrimaryScrollingType( CStifItemParser& /*aItem*/)
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGDelete, "In TestGridsGMSSGDelete" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGDelete );
    iLog->Log( KTestGridsGMSSGDelete );

    iGrid->SetPrimaryScrollingType( CAknGridView::EScrollStops );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsGridSetSecondaryScrollingType
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridSetSecondaryScrollingType( CStifItemParser& /*aItem*/)
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGSetupLayout, "In TestGridsGMSSGSetupLayout" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGSetupLayout );
    iLog->Log( KTestGridsGMSSGSetupLayout );

    iGrid->SetSecondaryScrollingType( CAknGridView::EScrollStops );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsGridSetStartPositionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridSetStartPositionL( CStifItemParser& /*aItem*/)
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGHandlePointerEventL, "In TestGridsGMSSGHandlePointerEventL" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGHandlePointerEventL );
    iLog->Log( KTestGridsGMSSGHandlePointerEventL );

    TInt err = KErrNone;
    TPoint point( KPointX, KPointY);

    TRAP( err, iGrid->SetStartPositionL( point ) );

    return err;
    }

// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsGridCurrentDataIndex
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridCurrentDataIndex( CStifItemParser& /*aItem*/)
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGSizeChanged, "In TestGridsGMSSGSizeChanged" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGSizeChanged );
    iLog->Log( KTestGridsGMSSGSizeChanged );

    const TInt expected = 0;
    TInt dataIndex = iGrid->CurrentDataIndex( );
    STIF_ASSERT_EQUALS( expected, dataIndex );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsGridSetCurrentDataIndex
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridSetCurrentDataIndex( CStifItemParser& /*aItem*/)
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGMSSGMinimumSize" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );

    TInt dataIndex = iGrid->CurrentDataIndex( );
    iGrid->SetCurrentDataIndex( dataIndex );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsGridIndexOfPosition
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridIndexOfPosition( CStifItemParser& /*aItem*/)
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGMSSGMinimumSize" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );

    TInt expected = 0;
    TPoint point( KPointX, KPointY);
    TInt indexOfPosition = iGrid->IndexOfPosition( point );
    STIF_ASSERT_NOT_EQUALS( expected, indexOfPosition );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsGridPositionAtIndex
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridPositionAtIndex( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGMSSGMinimumSize" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );

    TPoint point( KPointX, KPointY);
    TInt indexOfPosition = iGrid->IndexOfPosition( point );
    TPoint positionAtIndex = iGrid->PositionAtIndex( indexOfPosition );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsGridItemDrawer
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridItemDrawer( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGMSSGMinimumSize" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );

    CFormattedCellListBoxItemDrawer* intemFrawer = iGrid->ItemDrawer();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsGridSetEmptyGridTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridSetEmptyGridTextL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGMSSGMinimumSize" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );

    TInt err = KErrNone;
    _LIT( text, "xxxxxxxxxxx" );
    TRAP( err, iGrid->SetEmptyGridTextL( text ) );

    return err;
    }

// -----------------------------------------------------------------------------
// Ctestsdkgrids::TestGridsGridEmptyGridText
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridEmptyGridText( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGMSSGMinimumSize" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );

    iGrid->EmptyGridText();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridMakeViewClassInstanceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridMakeViewClassInstanceL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGMSSGMinimumSize" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );

    CListBoxView* boxView = iGrid->MakeViewClassInstanceL();
    CleanupStack::PushL( boxView );
    STIF_ASSERT_NOT_NULL( iGrid );
    CleanupStack::PopAndDestroy( boxView );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridSetColumnWidth
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridSetColumnWidth( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGMSSGMinimumSize" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );

    iGrid->SetColumnWidth( KColumnWidthTwo );
    iGrid->SetColumnWidth( KColumnWidthZero );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridColumnWidth
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridColumnWidth( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGMSSGMinimumSize" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );

    TInt width = iGrid->ColumnWidth();
    STIF_ASSERT_EQUALS( KColumnWidthTwo, width );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridUpdateScrollBarsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridUpdateScrollBarsL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGMSSGMinimumSize" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );

    TInt err = KErrNone;
    TRAP( err, iGrid->UpdateScrollBarsL() );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridHandleItemAdditionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridHandleItemAdditionL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGMSSGMinimumSize" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );

    TInt err = KErrNone;
    TRAP( err, iGrid->HandleItemAdditionL() );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridHandleItemRemovalL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridHandleItemRemovalL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGMSSGMinimumSize" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );

    TInt err = KErrNone;
    TRAP( err, iGrid->HandleItemRemovalL() );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGMSSGMinimumSize" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );

    TKeyEvent keyEvent1 = { EKeyPause, EStdKeySpace, 0, 0  };
    TKeyResponse response = iGrid->OfferKeyEventL( keyEvent1, EEventNull );
    TKeyEvent keyEvent2 = { EKeyUpArrow, EStdKeySpace, 0, 0  };
    response = iGrid->OfferKeyEventL( keyEvent2, EEventNull );
    TKeyEvent keyEvent3 = { EKeyDownArrow, EStdKeySpace, 0, 0  };
    response = iGrid->OfferKeyEventL( keyEvent3, EEventNull );
    TKeyEvent keyEvent4 = { EKeyLeftArrow, EStdKeySpace, 0, 0  };
    response = iGrid->OfferKeyEventL( keyEvent4, EEventNull );
    TKeyEvent keyEvent5 = { EKeyRightArrow, EStdKeySpace, 0, 0  };
    response = iGrid->OfferKeyEventL( keyEvent5, EEventNull );
    TKeyEvent keyEvent6 = { EKeyPageUp, EStdKeySpace, 0, 0  };
    response = iGrid->OfferKeyEventL( keyEvent6, EEventNull );
    TKeyEvent keyEvent7 = { EKeyPageDown, EStdKeySpace, 0, 0  };
    response = iGrid->OfferKeyEventL( keyEvent7, EEventNull );
    TKeyEvent keyEvent8 = { EKeyHome, EStdKeySpace, 0, 0  };
    response = iGrid->OfferKeyEventL( keyEvent8, EEventNull );
    TKeyEvent keyEvent9 = { EKeyEnd, EStdKeySpace, 0, 0  };
    response = iGrid->OfferKeyEventL( keyEvent9, EEventNull );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridSetItemHeightL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridSetItemHeightL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGMSSGMinimumSize" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );

    iGrid->SetItemHeightL( KZero );
    iGrid->SetItemHeightL( KTwo );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridSizeChanged
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridSizeChanged( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGMSSGMinimumSize" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );

    iGrid->SizeChanged();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridModel
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridModel( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsdkgrid" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGMSSGMinimumSize" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );

    CTextListBoxModel* listBoxModel = iGrid->Model();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridSetRect
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridSetRectL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsetrect" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGridSetRect" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );
    
    CAknGrid* grid = new( ELeave ) CAknGrid();
    CleanupStack::PushL( grid );
    
    CAknGridM* model = new( ELeave ) CAknGridM();
    CleanupStack::PushL( model );
    grid->SetModel( model );
    CleanupStack::Pop( model );
    
    grid->SetContainerWindowL( *iContainer );
    
    TResourceReader reader;
    CEikonEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDKGRIDS_GRID );
    grid->ConstructFromResourceL( reader );
    
    TPoint topleftpoint( 0, 0 );
    TPoint bottomrightpoint( 10, 10 );
    TRect rect( topleftpoint, bottomrightpoint );
    grid->SetRect( rect );
    
    CleanupStack::PopAndDestroy( 2 );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridHandleViewRectSizeChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridHandleViewRectSizeChangeL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsetrect" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGridSetRect" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );
    
    CAknGrid* grid = new( ELeave ) CAknGrid();
    CleanupStack::PushL( grid );
    
    CAknGridM* model = new( ELeave ) CAknGridM();
    CleanupStack::PushL( model );
    grid->SetModel( model );
    CleanupStack::Pop( model );
    
    grid->SetContainerWindowL( *iContainer );
    
    TResourceReader reader;
    CEikonEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDKGRIDS_GRID );
    grid->ConstructFromResourceL( reader );
    
    TInt err;
    TRAP( err, grid->HandleViewRectSizeChangeL() );
    
    CleanupStack::PopAndDestroy( 2 );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridSetTopItemIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridSetTopItemIndexL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsetrect" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGridSetRect" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );
    
    CAknGrid* grid = new( ELeave ) CAknGrid();
    CleanupStack::PushL( grid );
    
    CAknGridM* model = new( ELeave ) CAknGridM();
    CleanupStack::PushL( model );
    grid->SetModel( model );
    CleanupStack::Pop( model );
    
    grid->SetContainerWindowL( *iContainer );
    
    TResourceReader reader;
    CEikonEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDKGRIDS_GRID );
    grid->ConstructFromResourceL( reader );
        
    grid->SetTopItemIndex( KOne );
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsetrect" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGridSetRect" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );
    
    CAknGrid* grid = new( ELeave ) CAknGrid();
    CleanupStack::PushL( grid );
    
    CAknGridM* model = new( ELeave ) CAknGridM();
    CleanupStack::PushL( model );
    grid->SetModel( model );
    CleanupStack::Pop( model );
    
    grid->SetContainerWindowL( *iContainer );
        
    TResourceReader reader;
    CEikonEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDKGRIDS_GRID );
    grid->ConstructFromResourceL( reader );
        
    grid->HandleResourceChange( KEikMessageFadeAllWindows );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridFocusChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridFocusChangedL( CStifItemParser& )
    {
    _LIT( Ktestsdkgrid, "testsetrect" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGridSetRect" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );
    
    CAknGrid* grid = new( ELeave ) CAknGrid();
    CleanupStack::PushL( grid );
    
    CAknGridM* model = new( ELeave ) CAknGridM();
    CleanupStack::PushL( model );
    grid->SetModel( model );
    CleanupStack::Pop( model );
    
    grid->SetContainerWindowL( *iContainer );
        
    TResourceReader reader;
    CEikonEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDKGRIDS_GRID );
    grid->ConstructFromResourceL( reader );
    
    grid->SetFocus( ETrue );
    grid->FocusChanged( EDrawNow );
    grid->FocusChanged( ENoDrawNow );
    
    grid->SetFocus( EFalse );
    grid->FocusChanged( EDrawNow );
    grid->FocusChanged( ENoDrawNow );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridHorizontalNudgeValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridHorizontalNudgeValueL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsetrect" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGridSetRect" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );
    
    CAknGridExt* grid = new( ELeave ) CAknGridExt();
    CleanupStack::PushL( grid );
    
    CAknGridM* model = new( ELeave ) CAknGridM();
    CleanupStack::PushL( model );
    grid->SetModel( model );
    CleanupStack::Pop( model );
    
    grid->SetContainerWindowL( *iContainer );
        
    TResourceReader reader;
    CEikonEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDKGRIDS_GRID );
    grid->ConstructFromResourceL( reader );
    
    TInt returnvalue = grid->HorizontalNudgeValue();
    STIF_ASSERT_EQUALS( KOne, returnvalue );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridHorizScrollGranularityInPixels
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridHorizScrollGranularityInPixelsL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsetrect" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGridSetRect" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );
    
    CAknGridExt* grid = new( ELeave ) CAknGridExt();
    CleanupStack::PushL( grid );
    
    CAknGridM* model = new( ELeave ) CAknGridM();
    CleanupStack::PushL( model );
    grid->SetModel( model );
    CleanupStack::Pop( model );
    
    grid->SetContainerWindowL( *iContainer );
        
    TResourceReader reader;
    CEikonEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDKGRIDS_GRID );
    grid->ConstructFromResourceL( reader );
    
    grid->SetColumnWidth( KThree );
    TInt returnvalue = grid->HorizScrollGranularityInPixels();
    STIF_ASSERT_EQUALS( KThree, returnvalue );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridAdjustTopItemIndex
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridAdjustTopItemIndexL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsetrect" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGridSetRect" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );
    
    CAknGridExt* grid = new( ELeave ) CAknGridExt();
    CleanupStack::PushL( grid );
    
    CAknGridM* model = new( ELeave ) CAknGridM();
    CleanupStack::PushL( model );
    grid->SetModel( model );
    CleanupStack::Pop( model );
    
    grid->SetContainerWindowL( *iContainer );
        
    TResourceReader reader;
    CEikonEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDKGRIDS_GRID );
    grid->ConstructFromResourceL( reader );
    
    grid->SetTopItemIndex( KThree );
    grid->AdjustTopItemIndex();
    CleanupStack::PopAndDestroy( KTwo );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridHandleDragEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridHandleDragEventL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsetrect" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGridSetRect" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );
    
    CAknGridExt* grid = new( ELeave ) CAknGridExt();
    CleanupStack::PushL( grid );
    
    
    CAknGridM* model = new( ELeave ) CAknGridM();
    CleanupStack::PushL( model );
    grid->SetModel( model );
    CleanupStack::Pop( model );
    
    grid->SetContainerWindowL( *iContainer );
        
    TResourceReader reader;
    CEikonEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDKGRIDS_GRID );
    grid->ConstructFromResourceL( reader );
    
    grid->ConstructL( iContainer, KOne );
    TInt err;
    TRAP( err, grid->HandleDragEventL( TPoint( KMinusone, KOne )));
    TRAP( err, grid->HandleDragEventL( TPoint( KMinusone, KMinusone )));
    TRAP( err, grid->HandleDragEventL( TPoint( KOne, KOne )));
    CleanupStack::PopAndDestroy( KTwo );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridRestoreClientRectFromViewRectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridRestoreClientRectFromViewRectL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsetrect" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGridSetRect" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );
    
    CAknGridExt* grid = new( ELeave ) CAknGridExt();
    CleanupStack::PushL( grid );
    
    CAknGridM* model = new( ELeave ) CAknGridM();
    CleanupStack::PushL( model );
    grid->SetModel( model );
    CleanupStack::Pop( model );
        
    grid->SetContainerWindowL( *iContainer );
        
    TResourceReader reader;
    CEikonEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDKGRIDS_GRID );
    grid->ConstructFromResourceL( reader );
    
    TPoint point( KZero, KZero );
    TRect rect( point, point );
    
    TInt err;
    TRAP( err, grid->RestoreClientRectFromViewRect( rect ));
    
    CleanupStack::PopAndDestroy( KTwo );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridAdjustRectHeightToWholeNumberOfItemsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridAdjustRectHeightToWholeNumberOfItemsL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsetrect" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGridSetRect" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );
    
    CAknGridExt* grid = new( ELeave ) CAknGridExt();
    CleanupStack::PushL( grid );
    
    CAknGridM* model = new( ELeave ) CAknGridM();
    CleanupStack::PushL( model );
    grid->SetModel( model );
    CleanupStack::Pop( model );
    
    grid->SetContainerWindowL( *iContainer );
    
    TResourceReader reader;
    CEikonEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDKGRIDS_GRID );
    grid->ConstructFromResourceL( reader );
    
    grid->SetRect( iContainer->Rect());
    TPoint topleftpoint( KZero, KZero );
    TPoint rightbottompoint( KTwo, KTwo );
    TRect rect( topleftpoint, rightbottompoint );
    TInt returnvalue = grid->AdjustRectHeightToWholeNumberOfItems( rect );
    STIF_ASSERT_NOT_EQUALS( KZero, returnvalue );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridUpdateScrollBarThumbsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridUpdateScrollBarThumbsL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsetrect" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGridSetRect" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );
    
    CAknGridExt* grid = new( ELeave ) CAknGridExt();
    CleanupStack::PushL( grid );
    
    CAknGridM* model = new( ELeave ) CAknGridM();
    CleanupStack::PushL( model );
    grid->SetModel( model );
    CleanupStack::Pop( model );
    
    grid->SetContainerWindowL( *iContainer );
    
    TResourceReader reader;
    CEikonEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDKGRIDS_GRID );
    grid->ConstructFromResourceL( reader );
    
    CStifScrollBarObserver* scrollbarobserver = new( ELeave ) CStifScrollBarObserver();
    CleanupStack::PushL( scrollbarobserver );
    CEikScrollBarFrame* scrollbarframe = new( ELeave ) CEikScrollBarFrame( iContainer,scrollbarobserver );
    CleanupStack::PushL( scrollbarframe );
    grid->SetScrollBarFrame( scrollbarframe, CEikListBox::ENotOwnedExternally );
    CleanupStack::Pop( scrollbarframe );
    CleanupStack::Pop( scrollbarobserver );
    
    grid->UpdateScrollBarThumbs();
    CleanupStack::PopAndDestroy( KTwo );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridCountComponentControlsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridCountComponentControlsL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsetrect" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGridSetRect" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );
    
    CAknGridExt* grid = new( ELeave ) CAknGridExt();
    CleanupStack::PushL( grid );
    
    CAknGridM* model = new( ELeave ) CAknGridM();
    CleanupStack::PushL( model );
    grid->SetModel( model );
    CleanupStack::Pop( model );
        
    grid->SetContainerWindowL( *iContainer );
    
    TResourceReader reader;
    CEikonEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDKGRIDS_GRID );
    grid->ConstructFromResourceL( reader );
    
    grid->CountComponentControls();
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridMoveToNextOrPreviousItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridMoveToNextOrPreviousItemL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsetrect" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGridSetRect" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );
    
    CAknGridExt* grid = new( ELeave ) CAknGridExt();
    CleanupStack::PushL( grid );
    
    CAknGridM* model = new( ELeave ) CAknGridM();
    CleanupStack::PushL( model );
    grid->SetModel( model );
    CleanupStack::Pop( model );
    
    grid->SetContainerWindowL( *iContainer );
        
    TResourceReader reader;
    CEikonEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDKGRIDS_GRID );
    grid->ConstructFromResourceL( reader );
    
    
    TInt err( KErrNone );
    TRAP( err, grid->MoveToNextOrPreviousItemL( TPoint( KMinusone, KMinusone )));
    TRAP( err, grid->MoveToNextOrPreviousItemL( TPoint( KOne, KTwo )));
    TRAP( err, grid->MoveToNextOrPreviousItemL( TPoint( KTen, KThousand )));
    
    CleanupStack::PopAndDestroy( KTwo );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridCalcGridSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridCalcGridSizeL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsetrect" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGridSetRect" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );
    
    CAknGridExt* grid = new( ELeave ) CAknGridExt();
    CleanupStack::PushL( grid );
    
    CAknGridM* model = new( ELeave ) CAknGridM();
    CleanupStack::PushL( model );
    grid->SetModel( model );
    CleanupStack::Pop( model );
        
    grid->SetContainerWindowL( *iContainer );
    
    TResourceReader reader;
    CEikonEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDKGRIDS_GRID );
    grid->ConstructFromResourceL( reader );
    
    TSize size = iContainer->Rect().Size( );
    grid->SetLayoutL( ETrue, ETrue, ETrue, KOne, KOne, size, KZero, KZero );
    TInt err( KErrNone );
    TRAP( err, grid->CalcGridSizeL());
    
    CleanupStack::PopAndDestroy( KTwo );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridCreateItemDrawerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridCreateItemDrawerL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsetrect" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGridSetRect" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );
    
    CAknGridExt* grid = new( ELeave ) CAknGridExt();
    CleanupStack::PushL( grid );
    
    CAknGridM* model = new( ELeave ) CAknGridM();
    CleanupStack::PushL( model );
    grid->SetModel( model );
    CleanupStack::Pop( model );
    
    grid->SetContainerWindowL( *iContainer );
        
    TResourceReader reader;
    CEikonEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDKGRIDS_GRID );
    grid->ConstructFromResourceL( reader );
    
    grid->SetContainerWindowL( *iContainer );
    grid->SetRect( iContainer->Rect() );
    
    TInt err( KErrNone );
    TRAP( err, grid->CreateItemDrawerL() );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridHandleScrollEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridHandleScrollEventL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsetrect" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGridSetRect" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );
    
    CAknGridExt* grid = new( ELeave ) CAknGridExt();
    CleanupStack::PushL( grid );
    
    CAknGridM* model = new( ELeave ) CAknGridM();
    CleanupStack::PushL( model );
    grid->SetModel( model );
    CleanupStack::Pop( model );
    
    grid->SetContainerWindowL( *iContainer );
        
    TResourceReader reader;
    CEikonEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDKGRIDS_GRID );
    grid->ConstructFromResourceL( reader );
    
    grid->SetRect( iContainer->Rect() );
    
    CEikScrollBar *scrollbar = new( ELeave ) CEikScrollBar();
    CleanupStack::PushL( scrollbar );
    
    grid->HandleScrollEventL( scrollbar, EEikScrollLeft );
    grid->HandleScrollEventL( scrollbar, EEikScrollUp );
    grid->HandleScrollEventL( scrollbar, EEikScrollRight );
    grid->HandleScrollEventL( scrollbar, EEikScrollDown );
    grid->HandleScrollEventL( scrollbar, EEikScrollPageLeft );
    grid->HandleScrollEventL( scrollbar, EEikScrollPageUp );
    grid->HandleScrollEventL( scrollbar, EEikScrollPageRight );
    grid->HandleScrollEventL( scrollbar, EEikScrollPageDown );
    grid->HandleScrollEventL( scrollbar, EEikScrollHome );
    grid->HandleScrollEventL( scrollbar, EEikScrollTop );
    grid->HandleScrollEventL( scrollbar, EEikScrollEnd );
    grid->HandleScrollEventL( scrollbar, EEikScrollBottom );
    grid->HandleScrollEventL( scrollbar, EEikScrollThumbDragHoriz );
    grid->HandleScrollEventL( scrollbar, EEikScrollThumbDragVert );
    grid->HandleScrollEventL( scrollbar, EEikScrollThumbReleaseHoriz );
    grid->HandleScrollEventL( scrollbar, EEikScrollThumbReleaseVert );
    
    CleanupStack::PopAndDestroy( scrollbar );
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridMopSupplyObjectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridMopSupplyObjectL( CStifItemParser& /*aItem*/ )
    {
    _LIT( Ktestsdkgrid, "testsetrect" );
    _LIT( KTestGridsGMSSGMinimumSize, "In TestGridsGridSetRect" );
    TestModuleIf().Printf( 0, Ktestsdkgrid, KTestGridsGMSSGMinimumSize );
    iLog->Log( KTestGridsGMSSGMinimumSize );
    
    CAknGridExt* grid = new( ELeave ) CAknGridExt;
    CleanupStack::PushL( grid );
    
    CAknGridM* model = new( ELeave ) CAknGridM();
    CleanupStack::PushL( model );
    grid->SetModel( model );
    CleanupStack::Pop( model );
        
    grid->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CEikonEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDKGRIDS_GRID );
    grid->ConstructFromResourceL( reader );
    
    const TTypeUid KTestUid = 0x1000008D;
    TTypeUid::Ptr returnptr = grid->MopSupplyObject( KTestUid );
    STIF_ASSERT_NOT_NULL( &returnptr );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

/*
 * End files
 */
