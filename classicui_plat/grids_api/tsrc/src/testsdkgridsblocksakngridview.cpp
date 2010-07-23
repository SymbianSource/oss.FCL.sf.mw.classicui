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
* Description:  Test akngridview.h
*
*/


/*
 * Include files
 */
#include <akngridview.h>
#include <akngrid.h>
#include <barsread.h>
#include <eikenv.h>
#include <testsdkgrids.rsg>
#include <eiktxlbm.h> 
#include <eikdialg.h> 
#include <eiklbv.h> 
#include <akngridm.h>

#include "testsdkgridscontainer.h"
#include "stifgridview.h"
#include "testsdkgrids.h"

const TInt KOne = 1;
const TInt KTwo = 2;
const TInt KThree = 3;
const TInt KZero = 0;
const TInt KTen = 10;
const TInt KWidth = 240;
const TInt KHeight = 320;
const TInt KMinusone = -1;
const TInt KNine = 9;
const TInt KTwoHundredThirtyeight = 238;
const TInt KTwoHundredThirtynine = 239;
const TInt KThreeHundredeightten = 318;
const TInt KThreeHundredninetten = 319;
const TInt KTestIfExist = 100000000;
const TInt KTwenty = 20;

_LIT( KListText, "It is a list text!");

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewDestructorAndDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewDestructorAndDestructorL( CStifItemParser& /*aItem*/ )
    {
    CAknGridView* view = new( ELeave ) CAknGridView;
    CleanupStack::PushL( view );
    STIF_ASSERT_NOT_NULL( view );
    CleanupStack::PopAndDestroy( view );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewActualDataIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewActualDataIndexL( CStifItemParser& /*aItem*/ )
    {
    CAknGridView* view = new( ELeave ) CAknGridView;
    CleanupStack::PushL( view );
    
    CAknGridView::SGrid gridnumber;
    gridnumber.iColsInView = KNine;
    gridnumber.iRowsInView = KNine;
    gridnumber.iSizeBetweenItems = TSize( KZero, KZero );
    gridnumber.iSizeOfItems = TSize( KTen, KTen );
    gridnumber.iPageSize = KOne;
    gridnumber.iGridDimensions = TSize( KWidth, KHeight );
    gridnumber.iGridFlags = KOne;
    
    view->SetGridDetails( gridnumber );
    TInt actualdataindex = view->ActualDataIndex( KOne );
    STIF_ASSERT_NOT_EQUALS( KZero, actualdataindex );
    
    CleanupStack::PopAndDestroy( view );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewListBoxIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewListBoxIndexL( CStifItemParser& /*aItem*/ )
    {
    CAknGridView* view = new( ELeave ) CAknGridView;
    CleanupStack::PushL( view );
    
    CAknGridView::SGrid gridnumber;
    gridnumber.iColsInView = KNine;
    gridnumber.iRowsInView = KNine;
    gridnumber.iSizeBetweenItems = TSize( KZero, KZero );
    gridnumber.iSizeOfItems = TSize( KTen, KTen );
    gridnumber.iPageSize = KOne;
    gridnumber.iGridDimensions = TSize( KWidth, KHeight );
    gridnumber.iGridFlags = KOne;
    
    view->SetGridDetails( gridnumber );
    TInt listboxindex = view->ListBoxIndex( KOne );
    STIF_ASSERT_NOT_EQUALS( KZero, listboxindex );
    
    CleanupStack::PopAndDestroy( view );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewCurrentDataIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewCurrentDataIndexL( CStifItemParser& aItem )
    {
    TInt err = TestGridsGridviewSetCurrentDataIndexL( aItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewSetCurrentDataIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewSetCurrentDataIndexL( CStifItemParser& /*aItem*/ )
    {
    CAknGridView* view = new( ELeave ) CAknGridView;
    CleanupStack::PushL( view );
    
    CAknGridView::SGrid gridnumber;
    gridnumber.iColsInView = KNine;
    gridnumber.iRowsInView = KNine;
    gridnumber.iSizeBetweenItems = TSize( KZero, KZero );
    gridnumber.iSizeOfItems = TSize( KTen, KTen );
    gridnumber.iPageSize = KOne;
    gridnumber.iGridDimensions = TSize( KWidth, KHeight );
    gridnumber.iGridFlags = KOne;
    
    view->SetGridDetails( gridnumber );
    
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
    const TRect rect = iContainer->Rect();
    view->ConstructL( modeltwo, drawer, screendevice, &parent, window, rect, KTen );
        
    view->SetCurrentDataIndex( KZero );
    TInt dataindex = view->CurrentDataIndex();
    STIF_ASSERT_NOT_EQUALS( KZero, dataindex );
    
    view->SetCurrentDataIndex( KThree );
    dataindex = view->CurrentDataIndex();
    STIF_ASSERT_NOT_EQUALS( KThree, dataindex );
    
    CleanupStack::PopAndDestroy( mydialog );
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( grid );
    CleanupStack::Pop( view );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewSetPrimaryScrollingTypeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewSetPrimaryScrollingTypeL( CStifItemParser& /*aItem*/ )
    {
    CAknGridView* view = new( ELeave ) CAknGridView;
    CleanupStack::PushL( view );
    
    CAknGridView::SGrid gridnumber;
    gridnumber.iColsInView = KNine;
    gridnumber.iRowsInView = KNine;
    gridnumber.iSizeBetweenItems = TSize( KZero, KZero );
    gridnumber.iSizeOfItems = TSize( KTen, KTen );
    gridnumber.iPageSize = KOne;
    gridnumber.iGridDimensions = TSize( KWidth, KHeight );
    gridnumber.iGridFlags = KOne;
    
    view->SetGridDetails( gridnumber );
    
    CAknGridView::TScrollingType scrollingtype = CAknGridView::EScrollFollowsItemsAndStops;
    
    view->SetPrimaryScrollingType( scrollingtype );
    
    scrollingtype = CAknGridView::EScrollFollowsGrid;
    
    view->SetPrimaryScrollingType( scrollingtype );
    
    CleanupStack::PopAndDestroy( view );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewSetSecondaryScrollingTypeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewSetSecondaryScrollingTypeL( CStifItemParser& /*aItem*/ )
    {
    CAknGridView* view = new( ELeave ) CAknGridView;
    CleanupStack::PushL( view );
    
    CAknGridView::SGrid gridnumber;
    gridnumber.iColsInView = KNine;
    gridnumber.iRowsInView = KNine;
    gridnumber.iSizeBetweenItems = TSize( KZero, KZero );
    gridnumber.iSizeOfItems = TSize( KTen, KTen );
    gridnumber.iPageSize = KOne;
    gridnumber.iGridDimensions = TSize( KWidth, KHeight );
    gridnumber.iGridFlags = KOne;
    
    view->SetGridDetails( gridnumber );
    
    CAknGridView::TScrollingType scrollingtype = CAknGridView::EScrollFollowsItemsAndStops;
        
    view->SetSecondaryScrollingType( scrollingtype );
    
    scrollingtype = CAknGridView::EScrollFollowsGrid;
    
    view->SetSecondaryScrollingType( scrollingtype );
    
    CleanupStack::PopAndDestroy( view );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewSetGridCellDimensionsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewSetGridCellDimensionsL( CStifItemParser& /*aItem*/ )
    {
    CAknGridView* view = new( ELeave ) CAknGridView;
    CleanupStack::PushL( view );
    
    CAknGridView::SGrid gridnumber;
    gridnumber.iColsInView = KNine;
    gridnumber.iRowsInView = KNine;
    gridnumber.iSizeBetweenItems = TSize( KZero, KZero );
    gridnumber.iSizeOfItems = TSize( KTen, KTen );
    gridnumber.iPageSize = KOne;
    gridnumber.iGridDimensions = TSize( KWidth, KHeight );
    gridnumber.iGridFlags = KOne;
    
    view->SetGridDetails( gridnumber );
    
    TSize size( KThree, KThree );
    view->SetGridCellDimensions( size );
    
    TSize returnsize = view->GridCellDimensions();
    
    STIF_ASSERT_EQUALS( size, returnsize );
    
    CleanupStack::PopAndDestroy( view );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewGridCellDimensions
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewGridCellDimensionsL( CStifItemParser& aItem )
    {
    TInt err = TestGridsGridviewSetGridCellDimensionsL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewSetSpacesBetweenItemsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewSetSpacesBetweenItemsL( CStifItemParser& /*aItem*/ )
    {
    CAknGridView* view = new( ELeave ) CAknGridView;
    CleanupStack::PushL( view );
    
    CAknGridView::SGrid gridnumber;
    gridnumber.iColsInView = KNine;
    gridnumber.iRowsInView = KNine;
    gridnumber.iSizeBetweenItems = TSize( KZero, KZero );
    gridnumber.iSizeOfItems = TSize( KTen, KTen );
    gridnumber.iPageSize = KOne;
    gridnumber.iGridDimensions = TSize( KWidth, KHeight );
    gridnumber.iGridFlags = KOne;
    
    view->SetGridDetails( gridnumber );
    
    view->SetSpacesBetweenItems( TSize( KZero ,KZero ));
    view->SetSpacesBetweenItems( TSize( KThree, KThree ));
    
    CleanupStack::PopAndDestroy( view );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewIsPrimaryVerticalL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewIsPrimaryVerticalL( CStifItemParser& /*aItem*/ )
    {
    CAknGridView* view = new( ELeave ) CAknGridView;
    CleanupStack::PushL( view );
    
    CAknGridView::SGrid gridnumber;
    gridnumber.iColsInView = KNine;
    gridnumber.iRowsInView = KNine;
    gridnumber.iSizeBetweenItems = TSize( KZero, KZero );
    gridnumber.iSizeOfItems = TSize( KTen, KTen );
    gridnumber.iPageSize = KOne;
    gridnumber.iGridDimensions = TSize( KWidth, KHeight );
    gridnumber.iGridFlags = KOne;
    
    view->SetGridDetails( gridnumber );
    
    TBool flag = view->IsPrimaryVertical();
    STIF_ASSERT_TRUE( flag );
    
    gridnumber.iGridFlags = KZero;
    view->SetGridDetails( gridnumber );
    
    flag = view->IsPrimaryVertical();
    STIF_ASSERT_FALSE( flag );
    
    CleanupStack::PopAndDestroy( view );    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewDataIndexFromLogicalPosL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewDataIndexFromLogicalPosL( CStifItemParser& /*aItem*/ )
    {
    CAknGridView* view = new( ELeave ) CAknGridView;
    CleanupStack::PushL( view );
    
    CAknGridView::SGrid gridnumber;
    gridnumber.iColsInView = KNine;
    gridnumber.iRowsInView = KNine;
    gridnumber.iSizeBetweenItems = TSize( KZero, KZero );
    gridnumber.iSizeOfItems = TSize( KTen, KTen );
    gridnumber.iPageSize = KOne;
    gridnumber.iGridDimensions = TSize( KWidth, KHeight );
    gridnumber.iGridFlags = KOne;
    
    view->SetGridDetails( gridnumber );
    
    TInt dataindex( KZero );
    view->DataIndexFromLogicalPos( dataindex, KOne, KOne );
    STIF_ASSERT_NOT_EQUALS( KZero, dataindex );
    
    dataindex = KZero;
    gridnumber.iGridFlags = KZero;
    
    view->DataIndexFromLogicalPos( dataindex, KOne, KOne );
    STIF_ASSERT_NOT_EQUALS( KZero, dataindex );
    
    CleanupStack::PopAndDestroy( view );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewLogicalPosFromDataIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewLogicalPosFromDataIndexL( CStifItemParser& /*aItem*/ )
    {
    CAknGridView* view = new( ELeave ) CAknGridView;
    CleanupStack::PushL( view );
    
    CAknGridView::SGrid gridnumber;
    gridnumber.iColsInView = KNine;
    gridnumber.iRowsInView = KNine;
    gridnumber.iSizeBetweenItems = TSize( KZero, KZero );
    gridnumber.iSizeOfItems = TSize( KTen, KTen );
    gridnumber.iPageSize = KOne;
    gridnumber.iGridDimensions = TSize( KWidth, KHeight );
    gridnumber.iGridFlags = KOne;
    
    view->SetGridDetails( gridnumber );
    
    TInt rowindex( KZero );
    TInt colindex( KZero );
    
    view->LogicalPosFromDataIndex( KNine, rowindex, colindex );
    STIF_ASSERT_EQUALS( KThreeHundredninetten, rowindex );
    STIF_ASSERT_EQUALS( KTwoHundredThirtyeight, colindex );
    
    gridnumber.iGridFlags = KZero;
    view->SetGridDetails( gridnumber );
    
    view->LogicalPosFromDataIndex( KNine, rowindex, colindex );
    STIF_ASSERT_EQUALS( KThreeHundredeightten, rowindex );
    STIF_ASSERT_EQUALS( KTwoHundredThirtynine, colindex );
    
    view->LogicalPosFromDataIndex( KMinusone, rowindex, colindex );
    STIF_ASSERT_EQUALS( KThreeHundredninetten, rowindex );
    STIF_ASSERT_EQUALS( KTwoHundredThirtynine, colindex );
    
    CleanupStack::PopAndDestroy( view );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewListBoxIndexFromLogicalPosL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewListBoxIndexFromLogicalPosL( CStifItemParser& /*aItem*/ )
    {
    CAknGridView* view = new( ELeave ) CAknGridView;
    CleanupStack::PushL( view );
    
    CAknGridView::SGrid gridnumber;
    gridnumber.iColsInView = KNine;
    gridnumber.iRowsInView = KNine;
    gridnumber.iSizeBetweenItems = TSize( KZero, KZero );
    gridnumber.iSizeOfItems = TSize( KTen, KTen );
    gridnumber.iPageSize = KOne;
    gridnumber.iGridDimensions = TSize( KWidth, KHeight );
    gridnumber.iGridFlags = KOne;
    
    view->SetGridDetails( gridnumber );
    
    TInt mitemindex( KZero );
    view->ListBoxIndexFromLogicalPos( mitemindex, KOne, KOne );
    STIF_ASSERT_EQUALS( KTen, mitemindex );
    
    gridnumber.iGridFlags = KZero;
    view->SetGridDetails( gridnumber );
    
    view->ListBoxIndexFromLogicalPos( mitemindex, KZero, KOne );
    STIF_ASSERT_EQUALS( KOne, mitemindex );
    
    CleanupStack::PopAndDestroy( view );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewLogicalPosFromListBoxIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewLogicalPosFromListBoxIndexL( CStifItemParser& /*aItem*/ )
    {
    CAknGridView* view = new( ELeave ) CAknGridView;
    CleanupStack::PushL( view );
    
    CAknGridView::SGrid gridnumber;
    gridnumber.iColsInView = KNine;
    gridnumber.iRowsInView = KNine;
    gridnumber.iSizeBetweenItems = TSize( KZero, KZero );
    gridnumber.iSizeOfItems = TSize( KTen, KTen );
    gridnumber.iPageSize = KOne;
    gridnumber.iGridDimensions = TSize( KWidth, KHeight );
    gridnumber.iGridFlags = KOne;
    
    view->SetGridDetails( gridnumber );
    
    TInt rolindex( KZero );
    TInt colindex( KZero );
    
    view->LogicalPosFromListBoxIndex( KZero, rolindex, colindex );
    STIF_ASSERT_EQUALS( KZero, rolindex );
    STIF_ASSERT_EQUALS( KZero, colindex );
    
    view->LogicalPosFromListBoxIndex( KNine, rolindex, colindex );
    STIF_ASSERT_EQUALS( KZero, rolindex );
    STIF_ASSERT_EQUALS( KOne, colindex );
    
    gridnumber.iGridFlags = KZero;
    view->SetGridDetails( gridnumber );
    
    view->LogicalPosFromListBoxIndex( KNine, rolindex, colindex );
    STIF_ASSERT_EQUALS( KOne, rolindex );
    STIF_ASSERT_EQUALS( KZero, colindex );
    
    CleanupStack::PopAndDestroy( view );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewDrawEmptyListL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewDrawEmptyListL( CStifItemParser& /*aItem*/ )
    {
    CAknGridView* view = new( ELeave ) CAknGridView;
    CleanupStack::PushL( view );
    
    CAknGridView::SGrid gridnumber;
    gridnumber.iColsInView = KNine;
    gridnumber.iRowsInView = KNine;
    gridnumber.iSizeBetweenItems = TSize( KZero, KZero );
    gridnumber.iSizeOfItems = TSize( KTen, KTen );
    gridnumber.iPageSize = KOne;
    gridnumber.iGridDimensions = TSize( KWidth, KHeight );
    gridnumber.iGridFlags = KOne;
    
    view->SetGridDetails( gridnumber );
    
    TBuf<32> buf( KListText );
    view->SetListEmptyTextL( buf );
    
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
    const TRect rect = iContainer->Rect();
    view->ConstructL( modeltwo, drawer, screendevice, &parent, window, rect, KTen );
    
    view->DrawEmptyList();
    
    CleanupStack::PopAndDestroy( mydialog );
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( grid );
    CleanupStack::Pop( view );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewSetGridDetailsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewSetGridDetailsL( CStifItemParser& aItem )
    {
    TInt err = TestGridsGridviewIsPrimaryVerticalL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewMoveToItemIndexLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewMoveToItemIndexLL( CStifItemParser& /*aItem*/ )
    {
    CAknGridView* view = new( ELeave ) CAknGridView;
    CleanupStack::PushL( view );
    
    CAknGridView::SGrid gridnumber;
    gridnumber.iColsInView = KNine;
    gridnumber.iRowsInView = KNine;
    gridnumber.iSizeBetweenItems = TSize( KZero, KZero );
    gridnumber.iSizeOfItems = TSize( KTen, KTen );
    gridnumber.iPageSize = KOne;
    gridnumber.iGridDimensions = TSize( KWidth, KHeight );
    gridnumber.iGridFlags = KOne;
    
    view->SetGridDetails( gridnumber );
    
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
    const TRect rect = iContainer->Rect();
    view->ConstructL( modeltwo, drawer, screendevice, &parent, window, rect, KTen );
    
    view->SetCurrentItemIndex( KOne );
    
    view->MoveToItemIndexL( 200, CListBoxView::ENoSelection );
    view->MoveToItemIndexL( KThree, CListBoxView::ESingleSelection );
    view->MoveToItemIndexL( KZero, CListBoxView::EDisjointSelection );
    view->MoveToItemIndexL( KZero, CListBoxView::EDisjointMarkSelection );
    
    CleanupStack::PopAndDestroy( mydialog );
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( grid );
    CleanupStack::Pop( view );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewNumberOfColsInViewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewNumberOfColsInViewL( CStifItemParser& /*aItem*/ )
    {
    CAknGridView* view = new( ELeave ) CAknGridView;
    CleanupStack::PushL( view );
    
    CAknGridView::SGrid gridnumber;
    gridnumber.iColsInView = KNine;
    gridnumber.iRowsInView = KNine;
    gridnumber.iSizeBetweenItems = TSize( KZero, KZero );
    gridnumber.iSizeOfItems = TSize( KTen, KTen );
    gridnumber.iPageSize = KOne;
    gridnumber.iGridDimensions = TSize( KWidth, KHeight );
    gridnumber.iGridFlags = KOne;
    
    view->SetGridDetails( gridnumber );
    
    TInt numberofcols = view->NumberOfColsInView();
    STIF_ASSERT_EQUALS( KNine, numberofcols );
    
    CleanupStack::PopAndDestroy( view );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewNumberOfRowsInViewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewNumberOfRowsInViewL( CStifItemParser& /*aIetm*/ )
    {
    CAknGridView* view = new( ELeave ) CAknGridView;
    CleanupStack::PushL( view );
    
    CAknGridView::SGrid gridnumber;
    gridnumber.iColsInView = KNine;
    gridnumber.iRowsInView = KNine;
    gridnumber.iSizeBetweenItems = TSize( KZero, KZero );
    gridnumber.iSizeOfItems = TSize( KTen, KTen );
    gridnumber.iPageSize = KOne;
    gridnumber.iGridDimensions = TSize( KWidth, KHeight );
    gridnumber.iGridFlags = KOne;
    
    view->SetGridDetails( gridnumber );
    
    TInt numberofcols = view->NumberOfRowsInView();
    STIF_ASSERT_EQUALS( KNine, numberofcols );
    
    CleanupStack::PopAndDestroy( view );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewDrawMatcherCursorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewDrawMatcherCursorL( CStifItemParser& /*aItem*/ )
    {
    CAknGridView* view = new( ELeave ) CAknGridView;
    CleanupStack::PushL( view );
    
    view->DrawMatcherCursor();
    
    CleanupStack::PopAndDestroy( view );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewCurrentItemIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewCurrentItemIndexL( CStifItemParser& /*aItem*/ )
    {
    CAknGridView* view = new( ELeave ) CAknGridView;
    CleanupStack::PushL( view );
    
    CAknGridView::SGrid gridnumber;
    gridnumber.iColsInView = KNine;
    gridnumber.iRowsInView = KNine;
    gridnumber.iSizeBetweenItems = TSize( KZero, KZero );
    gridnumber.iSizeOfItems = TSize( KTen, KTen );
    gridnumber.iPageSize = KOne;
    gridnumber.iGridDimensions = TSize( KWidth, KHeight );
    gridnumber.iGridFlags = KOne;
    
    view->SetGridDetails( gridnumber );
    
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
    const TRect rect = iContainer->Rect();
    view->ConstructL( modeltwo, drawer, screendevice, &parent, window, rect, KTen );
    
    TInt currentindex = view->CurrentItemIndex();
    STIF_ASSERT_EQUALS( KZero, currentindex );
    
    CStifGridView* stifgridview = static_cast<CStifGridView*>( view );
    CAknGridM* gridm = stifgridview->DoGridModel();
    
    view->SetCurrentItemIndex( KOne );
    currentindex = view->CurrentItemIndex();
    STIF_ASSERT_EQUALS( KOne, currentindex );
    
    CleanupStack::PopAndDestroy( mydialog );
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( grid );
    CleanupStack::Pop( view );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewItemExistsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewItemExistsL( CStifItemParser& /*aItem*/ )
    {
    CStifGridView* view = new( ELeave ) CStifGridView;
    CleanupStack::PushL( view );
    
    CAknGridView::SGrid gridnumber;
    gridnumber.iColsInView = KNine;
    gridnumber.iRowsInView = KNine;
    gridnumber.iSizeBetweenItems = TSize( KZero, KZero );
    gridnumber.iSizeOfItems = TSize( KTen, KTen );
    gridnumber.iPageSize = KOne;
    gridnumber.iGridDimensions = TSize( KWidth, KHeight );
    gridnumber.iGridFlags = KOne;
    
    view->SetGridDetails( gridnumber );
    
    TBool justiceifexist = view->DoItemExists( KOne );
    STIF_ASSERT_TRUE( justiceifexist );
    justiceifexist = view->DoItemExists( KMinusone );
    STIF_ASSERT_FALSE( justiceifexist );
    justiceifexist = view->DoItemExists( KTestIfExist );
    STIF_ASSERT_FALSE( justiceifexist );
    
    CleanupStack::PopAndDestroy( view );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewSetColumnWidthL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewSetColumnWidthL( CStifItemParser& /*aItem*/ )
    {
    CAknGridView* view = new( ELeave ) CAknGridView;
    CleanupStack::PushL( view );
    
    CAknGridView::SGrid gridnumber;
    gridnumber.iColsInView = KNine;
    gridnumber.iRowsInView = KNine;
    gridnumber.iSizeBetweenItems = TSize( KZero, KZero );
    gridnumber.iSizeOfItems = TSize( KTen, KTen );
    gridnumber.iPageSize = KOne;
    gridnumber.iGridDimensions = TSize( KWidth, KHeight );
    gridnumber.iGridFlags = KOne;
    
    view->SetGridDetails( gridnumber );
    
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
    const TRect rect = iContainer->Rect();
    view->ConstructL( modeltwo, drawer, screendevice, &parent, window, rect, KTen );
    
    view->SetColumnWidth( KTen );
    TInt columnwidth = view->ColumnWidth();
    STIF_ASSERT_EQUALS( KTen, columnwidth );
    
    view->SetColumnWidth( KWidth );
    columnwidth = view->ColumnWidth();
    STIF_ASSERT_EQUALS( KWidth, columnwidth );
    
    CleanupStack::PopAndDestroy( mydialog );
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( grid );
    CleanupStack::Pop( view );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewMoveCursorLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewMoveCursorLL( CStifItemParser& /*aItem*/ )
    {
    CAknGrid* grid = new( ELeave ) CAknGrid();
    CleanupStack::PushL( grid );
    
    CAknGridM* model = new( ELeave ) CAknGridM();
    CleanupStack::PushL( model );
    grid->SetModel( model );
    CleanupStack::Pop( model );
    TResourceReader reader;
    grid->SetContainerWindowL( *iContainer );
    CEikonEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDKGRIDS_GRID );
    grid->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    grid->GridView()->MoveCursorL( CListBoxView::ECursorFirstItem, CListBoxView::ENoSelection );
    
    CleanupStack::PopAndDestroy( grid );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewDrawL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewDrawL( CStifItemParser& /*aItem*/ )
    {
    CAknGridView* view = new( ELeave ) CAknGridView;
    CleanupStack::PushL( view );
    
    CAknGridView::SGrid gridnumber;
    gridnumber.iColsInView = KNine;
    gridnumber.iRowsInView = KNine;
    gridnumber.iSizeBetweenItems = TSize( KZero, KZero );
    gridnumber.iSizeOfItems = TSize( KTen, KTen );
    gridnumber.iPageSize = KOne;
    gridnumber.iGridDimensions = TSize( KWidth, KHeight );
    gridnumber.iGridFlags = KOne;
    
    view->SetGridDetails( gridnumber );
    
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
    const TRect rect = iContainer->Rect();
    view->ConstructL( modeltwo, drawer, screendevice, &parent, window, rect, KTen );
    
    view->Draw();
    TRect drawrect = iContainer->Rect();
    TRect* drawrectptr = &drawrect;
    view->Draw( drawrectptr );
    
    CleanupStack::PopAndDestroy( mydialog );
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( grid );
    CleanupStack::Pop( view );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewDrawItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewDrawItemL( CStifItemParser& /*aItem*/ )
    {
    CAknGrid* grid = new( ELeave ) CAknGrid();
    CleanupStack::PushL( grid );
    
    CAknGridM* model = new( ELeave ) CAknGridM();
    CleanupStack::PushL( model );
    grid->SetModel( model );
    CleanupStack::Pop( model );
    TResourceReader reader;
    grid->SetContainerWindowL( *iContainer );
    CEikonEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDKGRIDS_GRID );
    grid->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    grid->GridView()->DrawItem( 0 );
    
    CleanupStack::PopAndDestroy( grid );
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewItemPosL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewItemPosL( CStifItemParser& /*aItem*/ )
    {
    CAknGridView* view = new( ELeave ) CAknGridView;
    CleanupStack::PushL( view );
    
    CAknGridView::SGrid gridnumber;
    gridnumber.iColsInView = KNine;
    gridnumber.iRowsInView = KNine;
    gridnumber.iSizeBetweenItems = TSize( KZero, KZero );
    gridnumber.iSizeOfItems = TSize( KTen, KTen );
    gridnumber.iPageSize = KOne;
    gridnumber.iGridDimensions = TSize( KWidth, KHeight );
    gridnumber.iGridFlags = KOne;
    
    view->SetGridDetails( gridnumber );
    
    TPoint topleftpoint = view->ItemPos( KZero );
    STIF_ASSERT_EQUALS( TPoint( KZero, KZero ), topleftpoint );
    
    topleftpoint = view->ItemPos( KOne );
    STIF_ASSERT_NOT_EQUALS( TPoint( KZero, KZero ), topleftpoint );
    
    gridnumber.iGridFlags = KZero;
    view->SetGridDetails( gridnumber );
    
    topleftpoint = view->ItemPos( KZero );
    STIF_ASSERT_EQUALS( TPoint( KZero, KZero ), topleftpoint );
    
    topleftpoint = view->ItemPos( KOne );
    STIF_ASSERT_NOT_EQUALS( TPoint( KZero, KZero ), topleftpoint );
    
    CleanupStack::PopAndDestroy( view );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewCalcBottomItemIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewCalcBottomItemIndexL( CStifItemParser& /*aItem*/ )
    {
    CAknGridView* view = new( ELeave ) CAknGridView;
    CleanupStack::PushL( view );
    
    CAknGridView::SGrid gridnumber;
    gridnumber.iColsInView = KNine;
    gridnumber.iRowsInView = KNine;
    gridnumber.iSizeBetweenItems = TSize( KZero, KZero );
    gridnumber.iSizeOfItems = TSize( KTen, KTen );
    gridnumber.iPageSize = KOne;
    gridnumber.iGridDimensions = TSize( KWidth, KHeight );
    gridnumber.iGridFlags = KOne;
    
    view->SetGridDetails( gridnumber );
    
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
    const TRect rect = iContainer->Rect();
    view->ConstructL( modeltwo, drawer, screendevice, &parent, window, rect, KTen );
        
    view->CalcBottomItemIndex();
    
    CleanupStack::PopAndDestroy( mydialog );
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( grid );
    CleanupStack::Pop( view );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewCalcNewTopItemIndexSoItemIsVisibleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewCalcNewTopItemIndexSoItemIsVisibleL( CStifItemParser& /*aItem*/ )
    {
    CAknGridView* view = new( ELeave ) CAknGridView;
    CleanupStack::PushL( view );
    
    CAknGridView::SGrid gridnumber;
    gridnumber.iColsInView = KNine;
    gridnumber.iRowsInView = KNine;
    gridnumber.iSizeBetweenItems = TSize( KZero, KZero );
    gridnumber.iSizeOfItems = TSize( KTen, KTen );
    gridnumber.iPageSize = KOne;
    gridnumber.iGridDimensions = TSize( KWidth, KHeight );
    gridnumber.iGridFlags = KOne;
    
    view->SetGridDetails( gridnumber );
    
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
    const TRect rect = iContainer->Rect();
    view->ConstructL( modeltwo, drawer, screendevice, &parent, window, rect, KTen );
    
    TInt topitemindex = view->CalcNewTopItemIndexSoItemIsVisible( KZero );
    STIF_ASSERT_EQUALS( KZero, topitemindex );
    
    topitemindex = view->CalcNewTopItemIndexSoItemIsVisible( KOne );
    STIF_ASSERT_NOT_EQUALS( KZero, topitemindex );
    
    view->SetTopItemIndex( KTwo );
    topitemindex = view->CalcNewTopItemIndexSoItemIsVisible( KOne );
    STIF_ASSERT_EQUALS( KZero, topitemindex );
    
    gridnumber.iGridFlags = KZero;
    view->SetGridDetails( gridnumber );
    
    topitemindex = view->CalcNewTopItemIndexSoItemIsVisible( KOne );
    STIF_ASSERT_EQUALS( KZero, topitemindex );
    
    view->SetTopItemIndex( KZero );
    topitemindex = view->CalcNewTopItemIndexSoItemIsVisible( KOne );
    STIF_ASSERT_NOT_EQUALS( KZero, topitemindex );
    
    CleanupStack::PopAndDestroy( mydialog );
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( grid );
    CleanupStack::Pop( view );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewDrawItemRangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewDrawItemRangeL( CStifItemParser& /*aItem*/ )
    {
    CAknGridView* view = new( ELeave ) CAknGridView;
    CleanupStack::PushL( view );
    
    CAknGridView::SGrid gridnumber;
    gridnumber.iColsInView = KNine;
    gridnumber.iRowsInView = KNine;
    gridnumber.iSizeBetweenItems = TSize( KZero, KZero );
    gridnumber.iSizeOfItems = TSize( KTen, KTen );
    gridnumber.iPageSize = KOne;
    gridnumber.iGridDimensions = TSize( KWidth, KHeight );
    gridnumber.iGridFlags = KOne;
    
    view->SetGridDetails( gridnumber );
    
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
    const TRect rect = iContainer->Rect();
    view->ConstructL( modeltwo, drawer, screendevice, &parent, window, rect, KTen );
    
    view->DrawItemRange( KZero, KTen );
    
    CleanupStack::PopAndDestroy( mydialog );
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( grid );
    CleanupStack::Pop( view );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewColumnWidthL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewColumnWidthL( CStifItemParser& aItem )
    {
    TInt err = TestGridsGridviewSetColumnWidthL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewSetTopItemIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewSetTopItemIndexL( CStifItemParser& aItem )
    {
    TInt err = TestGridsGridviewCalcNewTopItemIndexSoItemIsVisibleL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewSetItemHeightL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewSetItemHeightL( CStifItemParser& /*aItem*/ )
    {
    CAknGridView* view = new( ELeave ) CAknGridView;
    CleanupStack::PushL( view );
    
    CAknGridView::SGrid gridnumber;
    gridnumber.iColsInView = KNine;
    gridnumber.iRowsInView = KNine;
    gridnumber.iSizeBetweenItems = TSize( KZero, KZero );
    gridnumber.iSizeOfItems = TSize( KTen, KTen );
    gridnumber.iPageSize = KOne;
    gridnumber.iGridDimensions = TSize( KWidth, KHeight );
    gridnumber.iGridFlags = KOne;
    
    view->SetGridDetails( gridnumber );
    
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
    const TRect rect = iContainer->Rect();
    view->ConstructL( modeltwo, drawer, screendevice, &parent, window, rect, KTen );
    
    CStifGridView* stifgridview = static_cast<CStifGridView*>( view );
    
    TInt griditemheight = stifgridview->GetItemHeight();
    STIF_ASSERT_EQUALS( KTen, griditemheight );
    
    view->SetItemHeight( KOne );
    griditemheight = stifgridview->GetItemHeight();
    STIF_ASSERT_EQUALS( KOne, griditemheight );
    
    CleanupStack::PopAndDestroy( mydialog );
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( grid );
    CleanupStack::Pop( view );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewXYPosToItemIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewXYPosToItemIndexL( CStifItemParser& /*aItem*/ )
    {
    CAknGridView* view = new( ELeave ) CAknGridView;
    CleanupStack::PushL( view );
    
    CAknGridView::SGrid gridnumber;
    gridnumber.iColsInView = KNine;
    gridnumber.iRowsInView = KNine;
    gridnumber.iSizeBetweenItems = TSize( KZero, KZero );
    gridnumber.iSizeOfItems = TSize( KTen, KTen );
    gridnumber.iPageSize = KOne;
    gridnumber.iGridDimensions = TSize( KWidth, KHeight );
    gridnumber.iGridFlags = KOne;
    
    view->SetGridDetails( gridnumber );
    
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
    const TRect rect = iContainer->Rect();
    view->ConstructL( modeltwo, drawer, screendevice, &parent, window, rect, KTen );
    
    TInt returnitem( KZero );
    TBool flag = view->XYPosToItemIndex( TPoint( KOne, KTen ), returnitem );
    STIF_ASSERT_FALSE( flag );
    STIF_ASSERT_EQUALS( KZero, returnitem );
    
    
    CleanupStack::PopAndDestroy( mydialog );
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( grid );
    CleanupStack::Pop( view );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewCalcDataWidthL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewCalcDataWidthL( CStifItemParser& /*aItem*/ )
    {
    CAknGridView* view = new( ELeave ) CAknGridView;
    CleanupStack::PushL( view );
    
    CAknGridView::SGrid gridnumber;
    gridnumber.iColsInView = KNine;
    gridnumber.iRowsInView = KNine;
    gridnumber.iSizeBetweenItems = TSize( KZero, KZero );
    gridnumber.iSizeOfItems = TSize( KTen, KTen );
    gridnumber.iPageSize = KOne;
    gridnumber.iGridDimensions = TSize( KWidth, KHeight );
    gridnumber.iGridFlags = KOne;
    
    view->SetGridDetails( gridnumber );
    
    CStifGridView* stifgridview = static_cast<CStifGridView*>( view );
    view->CalcDataWidth();
    TInt datawidth = stifgridview->GetDataWidth();
    STIF_ASSERT_EQUALS( KWidth, datawidth );
    
    gridnumber.iGridDimensions = TSize( KTen, KHeight );
    view->SetGridDetails( gridnumber );
    
    view->CalcDataWidth();
    datawidth = stifgridview->GetDataWidth();
    STIF_ASSERT_EQUALS( KTen, datawidth );
    
    CleanupStack::PopAndDestroy( view );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewVisibleWidthL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewVisibleWidthL( CStifItemParser& /*aItem*/ )
    {
    CAknGridView* view = new( ELeave ) CAknGridView;
    CleanupStack::PushL( view );
    
    CAknGridView::SGrid gridnumber;
    gridnumber.iColsInView = KNine;
    gridnumber.iRowsInView = KNine;
    gridnumber.iSizeBetweenItems = TSize( KZero, KZero );
    gridnumber.iSizeOfItems = TSize( KTen, KTen );
    gridnumber.iPageSize = KOne;
    gridnumber.iGridDimensions = TSize( KWidth, KHeight );
    gridnumber.iGridFlags = KOne;
    
    view->SetGridDetails( gridnumber );
    
    TInt colwidth = view->ColumnWidth();
    TPoint topleftpoint( KZero, KZero );
    TPoint bottomrightpoint( KTen, KTen );
    TRect rect( topleftpoint, bottomrightpoint );
    
    TInt visiblewidth = view->VisibleWidth( rect );
    STIF_ASSERT_EQUALS( KOne, visiblewidth );
    
    CleanupStack::PopAndDestroy( view );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewScrollToMakeItemVisibleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewScrollToMakeItemVisibleL( CStifItemParser& /*aItem*/ )
    {
    CAknGrid* grid = new( ELeave ) CAknGrid();
    CleanupStack::PushL( grid );
    
    CAknGridM* model = new( ELeave ) CAknGridM();
    CleanupStack::PushL( model );
    grid->SetModel( model );
    CleanupStack::Pop( model );
    TResourceReader reader;
    grid->SetContainerWindowL( *iContainer );
    CEikonEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDKGRIDS_GRID );
    grid->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    grid->GridView()->ScrollToMakeItemVisible( 0 );
    
    CleanupStack::PopAndDestroy( grid );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewCalculateHScrollOffsetSoItemIsVisibleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewCalculateHScrollOffsetSoItemIsVisibleL( CStifItemParser& /*aItem*/ )
    {
    CAknGridView* view = new( ELeave ) CAknGridView;
    CleanupStack::PushL( view );
    
    CAknGridView::SGrid gridnumber;
    gridnumber.iColsInView = KNine;
    gridnumber.iRowsInView = KNine;
    gridnumber.iSizeBetweenItems = TSize( KZero, KZero );
    gridnumber.iSizeOfItems = TSize( KTen, KTen );
    gridnumber.iPageSize = KOne;
    gridnumber.iGridDimensions = TSize( KWidth, KHeight );
    gridnumber.iGridFlags = KOne;
    
    view->SetGridDetails( gridnumber );
    
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
    const TRect rect = iContainer->Rect();
    view->ConstructL( modeltwo, drawer, screendevice, &parent, window, rect, KTen );
    
    TInt needredraw = view->CalculateHScrollOffsetSoItemIsVisible( KZero );
    STIF_ASSERT_EQUALS( KZero, needredraw );
    
    needredraw = view->CalculateHScrollOffsetSoItemIsVisible( 50 );
    STIF_ASSERT_NOT_EQUALS( KZero, needredraw );
    
    gridnumber.iGridFlags = KZero;
    view->SetGridDetails( gridnumber );
    
    needredraw = view->CalculateHScrollOffsetSoItemIsVisible( KZero );
    STIF_ASSERT_EQUALS( KZero, needredraw );
    
    needredraw = view->CalculateHScrollOffsetSoItemIsVisible( 50 );
    STIF_ASSERT_NOT_EQUALS( KZero, needredraw );
    
    CleanupStack::PopAndDestroy( mydialog );
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( grid );
    CleanupStack::Pop( view );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewItemSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewItemSizeL( CStifItemParser& /*aItem*/ )
    {
    CAknGridView* view = new( ELeave ) CAknGridView;
    CleanupStack::PushL( view );
    
    CAknGridView::SGrid gridnumber;
    gridnumber.iColsInView = KNine;
    gridnumber.iRowsInView = KNine;
    gridnumber.iSizeBetweenItems = TSize( KZero, KZero );
    gridnumber.iSizeOfItems = TSize( KTen, KTen );
    gridnumber.iPageSize = KOne;
    gridnumber.iGridDimensions = TSize( KWidth, KHeight );
    gridnumber.iGridFlags = KOne;
    
    view->SetGridDetails( gridnumber );
    
    TSize returnitemsize = view->ItemSize( KZero );
    STIF_ASSERT_EQUALS( TSize( KTen, KTwenty), returnitemsize );
    
    gridnumber.iSizeOfItems = TSize( KThree, KThree );
    view->SetGridDetails( gridnumber );
    
    returnitemsize = view->ItemSize( KZero );
    STIF_ASSERT_EQUALS( TSize( KThree, KTwenty), returnitemsize );
    
    returnitemsize = view->ItemSize( KThree );
    STIF_ASSERT_EQUALS( TSize( KThree, KTwenty), returnitemsize );
    
    CleanupStack::PopAndDestroy( view );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewCalcRowAndColIndexesFromItemIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewCalcRowAndColIndexesFromItemIndexL( CStifItemParser& aItem )
    {
    TInt err = TestGridsGridviewItemPosL( aItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewCalcItemIndexFromRowAndColIndexesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewCalcItemIndexFromRowAndColIndexesL( CStifItemParser& /*aItem*/ )
    {
    CAknGridView* view = new( ELeave ) CAknGridView;
    CleanupStack::PushL( view );
    
    CAknGridView::SGrid gridnumber;
    gridnumber.iColsInView = KNine;
    gridnumber.iRowsInView = KNine;
    gridnumber.iSizeBetweenItems = TSize( KZero, KZero );
    gridnumber.iSizeOfItems = TSize( KTen, KTen );
    gridnumber.iPageSize = KOne;
    gridnumber.iGridDimensions = TSize( KWidth, KHeight );
    gridnumber.iGridFlags = KOne;
    
    view->SetGridDetails( gridnumber );
    
    TInt resultitemindex( KZero );
    view->CalcItemIndexFromRowAndColIndexes( resultitemindex, KOne, KTen );
    STIF_ASSERT_NOT_EQUALS( KZero, resultitemindex );
    
    view->CalcItemIndexFromRowAndColIndexes( resultitemindex, KZero, KZero );
    STIF_ASSERT_EQUALS( KZero, resultitemindex );
    
    gridnumber.iGridFlags = KZero;
    view->SetGridDetails( gridnumber );
    
    view->CalcItemIndexFromRowAndColIndexes( resultitemindex, KOne, KTen );
    STIF_ASSERT_NOT_EQUALS( KZero, resultitemindex );
    
    view->CalcItemIndexFromRowAndColIndexes( resultitemindex, KZero, KZero );
    STIF_ASSERT_EQUALS( KZero, resultitemindex );
    
    CleanupStack::PopAndDestroy( view );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewDrawColumnRangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewDrawColumnRangeL( CStifItemParser& /*aItem*/ )
    {
    CAknGridView* view = new( ELeave ) CAknGridView;
    CleanupStack::PushL( view );
    
    CAknGridView::SGrid gridnumber;
    gridnumber.iColsInView = KNine;
    gridnumber.iRowsInView = KNine;
    gridnumber.iSizeBetweenItems = TSize( KZero, KZero );
    gridnumber.iSizeOfItems = TSize( KTen, KTen );
    gridnumber.iPageSize = KOne;
    gridnumber.iGridDimensions = TSize( KWidth, KHeight );
    gridnumber.iGridFlags = KOne;
    
    view->SetGridDetails( gridnumber );
    
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
    const TRect rect = iContainer->Rect();
    view->ConstructL( modeltwo, drawer, screendevice, &parent, window, rect, KTen );
    CStifGridView* stifgridview = static_cast<CStifGridView*>( view );
    
    stifgridview->DoDrawColumnRange( KZero, KTen );
    view->SetItemHeight( KZero );
    stifgridview->DoDrawColumnRange( KZero, KTen );
    
    CleanupStack::PopAndDestroy( mydialog );
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( grid );
    CleanupStack::Pop( view );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewClearUnusedItemSpaceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewClearUnusedItemSpaceL( CStifItemParser& /*aItem*/ )
    {
    CAknGridView* view = new( ELeave ) CAknGridView;
    CleanupStack::PushL( view );
    
    CAknGridView::SGrid gridnumber;
    gridnumber.iColsInView = KNine;
    gridnumber.iRowsInView = KNine;
    gridnumber.iSizeBetweenItems = TSize( KZero, KZero );
    gridnumber.iSizeOfItems = TSize( KTen, KTen );
    gridnumber.iPageSize = KOne;
    gridnumber.iGridDimensions = TSize( KWidth, KHeight );
    gridnumber.iGridFlags = KOne;
    
    view->SetGridDetails( gridnumber );
    
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
    const TRect rect = iContainer->Rect();
    view->ConstructL( modeltwo, drawer, screendevice, &parent, window, rect, KTen );
    CStifGridView* stifgridview = static_cast<CStifGridView*>( view );
    
    stifgridview->DoClearUnusedItemSpace( KZero, KTen );
    
    CleanupStack::PopAndDestroy( mydialog );
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( grid );
    CleanupStack::Pop( view );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewUpdateHScrollOffsetBasedOnTopItemIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewUpdateHScrollOffsetBasedOnTopItemIndexL( CStifItemParser& /*aItem*/ )
    {
    CAknGridView* view = new( ELeave ) CAknGridView;
    CleanupStack::PushL( view );
    
    CAknGridView::SGrid gridnumber;
    gridnumber.iColsInView = KTwo;
    gridnumber.iRowsInView = KTwo;
    gridnumber.iSizeBetweenItems = TSize( KZero, KZero );
    gridnumber.iSizeOfItems = TSize( KTen, KTen );
    gridnumber.iPageSize = KOne;
    gridnumber.iGridDimensions = TSize( KWidth, KHeight );
    gridnumber.iGridFlags = KOne;
    
    view->SetGridDetails( gridnumber );
    
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
    const TRect rect = iContainer->Rect();
    view->ConstructL( modeltwo, drawer, screendevice, &parent, window, rect, KTen );
        
    view->SetTopItemIndex( KTwo );
    CStifGridView* stifgridview = static_cast<CStifGridView*>( view );
    
    stifgridview->DoUpdateHScrollOffsetBasedOnTopItemIndex();
    TInt offset = stifgridview->GetiHScrollOffset();
    STIF_ASSERT_EQUALS( KOne, offset );
    
    gridnumber.iRowsInView = KOne;
    view->SetGridDetails( gridnumber );
    stifgridview->DoUpdateHScrollOffsetBasedOnTopItemIndex();
    offset = stifgridview->GetiHScrollOffset();
    STIF_ASSERT_EQUALS( KTwo, offset );
    
    CleanupStack::PopAndDestroy( mydialog );
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( grid );
    CleanupStack::Pop( view );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridviewDoMoveLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridviewDoMoveLL( CStifItemParser& /*aItem*/ )
    {
    CAknGridView* view = new( ELeave ) CAknGridView;
    CleanupStack::PushL( view );
    
    CAknGridView::SGrid gridnumber;
    gridnumber.iColsInView = KNine;
    gridnumber.iRowsInView = KNine;
    gridnumber.iSizeBetweenItems = TSize( KZero, KZero );
    gridnumber.iSizeOfItems = TSize( KTen, KTen );
    gridnumber.iPageSize = KOne;
    gridnumber.iGridDimensions = TSize( KWidth, KHeight );
    gridnumber.iGridFlags = KOne;
    
    view->SetGridDetails( gridnumber );
    
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
    const TRect rect = iContainer->Rect();
    view->ConstructL( modeltwo, drawer, screendevice, &parent, window, rect, KTen );
        
    CStifGridView* stifgridview = static_cast<CStifGridView*>( view );
    
    stifgridview->DoDoMoveL( CListBoxView::ECursorNextItem, CListBoxView::ESingleSelection );
    stifgridview->DoDoMoveL( CListBoxView::ECursorNextScreen, CListBoxView::ESingleSelection );
    
    gridnumber.iGridFlags = KZero;
    view->SetGridDetails( gridnumber );
    
    stifgridview->DoDoMoveL( CListBoxView::ECursorNextItem, CListBoxView::ESingleSelection );
    stifgridview->DoDoMoveL( CListBoxView::ECursorNextScreen, CListBoxView::ESingleSelection );
    
    CleanupStack::PopAndDestroy( mydialog );
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( grid );
    CleanupStack::Pop( view );
    return KErrNone;
    }

/*
 * End files
 */
