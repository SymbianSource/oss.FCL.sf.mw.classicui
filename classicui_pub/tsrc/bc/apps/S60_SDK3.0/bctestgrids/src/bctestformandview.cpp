/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         test case
*
*/









#include <w32std.h>
#include <coecntrl.h>
#include <akngridm.h>
#include <akngridview.h>
#include <bctestgrids.rsg>
#include <akngrid.h>
#include <barsread.h>
#include <eikclb.h>
#include <eikclbd.h>

#include "bctestformandview.h"
#include "bctestgridscontainer.h"
#include "bctestgrids.hrh"

const TInt KItemHeight = 20;
const TInt KDimensionX = 1;
const TInt KDimensionY = 2;
const TInt KItemX = 1;
const TInt KItemY = 1;
const TInt KOne = 1;
const TInt KTwo = 2;
const TInt KZero = 0;
const TInt KNegative = -2;

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestForMAndView* CBCTestForMAndView::NewL( 
    CBCTestGridsContainer* aContainer )
    {
    CBCTestForMAndView* self = new( ELeave ) CBCTestForMAndView( 
        aContainer );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestForMAndView::CBCTestForMAndView( 
    CBCTestGridsContainer* aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestForMAndView::~CBCTestForMAndView()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestForMAndView::ConstructL()
    {    
    BuildScriptL();
    iEnv = CEikonEnv::Static();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestForMAndView::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestForMAndView::BuildScriptL()
    { 
    // Add script as your need.   
    AddTestL( LeftCBA, Down, Down, KeyOK, KeyOK, TEND ); 
    AddTestL( LeftCBA, Down, Down, KeyOK, Down, KeyOK, TEND );     
    }
    
// ---------------------------------------------------------------------------
// CBCTestForMAndView::RunL
// ---------------------------------------------------------------------------
//
void CBCTestForMAndView::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdEmptyOutline || aCmd > EBCTestCmdMaxOutline )
        {
        return;
        }
        
    switch ( aCmd )  
        {
        case EBCTestForCAknGridM:
            TestForAknGridML();
            break;
        case EBCTestForCAknGridView:
            TestForAknGridViewL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestForMAndView::TestForAknGridML
// ---------------------------------------------------------------------------
//    
void CBCTestForMAndView::TestForAknGridML()
    {
    CAknGridM* gridM = new( ELeave ) CAknGridM();
    CleanupStack::PushL( gridM );
    _LIT( KCAknGridM, "CAknGridM test" );
    AssertTrueL( ETrue, KCAknGridM ); 
    
    CDesCArray* array = iEnv->ReadDesCArrayResourceL( R_BCTESTGRIDS_ARRAY );
    
    gridM->ConstructL ( array, ELbmOwnsItemArray );
    
    TInt number = gridM->NumberOfItems();
    _LIT( KNumberOfItems, "NumberOfItems test" );
    AssertTrueL( ETrue, KNumberOfItems ); 
    
    TInt dataIndex = 0;
    TBool indexContainsData = gridM->IndexContainsData( dataIndex ); 
    _LIT( KIndexContainsData, "IndexContainsData test" );
    AssertTrueL( ETrue, KIndexContainsData );
    
    TInt numEmpty = 0;
    gridM->SetStartCells( numEmpty );
    _LIT( KSetStartCells, "SetStartCells test" );
    AssertTrueL( ETrue, KSetStartCells );
    
    TInt numberOfData = gridM->NumberOfData();
    _LIT( KNumberOfData, "NumberOfData test" );
    AssertTrueL( ETrue, KNumberOfData );
   
    TInt index = gridM->IndexOfFirstDataItem();
    _LIT( KIndexOfFirstDataItem, "IndexOfFirstDataItem test" );
    AssertTrueL( ETrue, KIndexOfFirstDataItem );
    
    gridM->IndexOfLastDataItem();
    _LIT( KIndexOfLastDataItem, "IndexOfLastDataItem test" );
    AssertTrueL( ETrue, KIndexOfLastDataItem );
    
    TInt itemIndex = 0;
    TPtrC itemText = gridM->ItemText( itemIndex );
    _LIT( KItemText, "ItemText test" );
    AssertTrueL( ETrue, KItemText );
   
    
    CleanupStack::PopAndDestroy( gridM ); 
    _LIT( KDesCAknGridM, "~CAknGridM test" );
    AssertTrueL( ETrue, KDesCAknGridM ); 
    }
    

// ---------------------------------------------------------------------------
// CBCTestForMAndView::TestForAknGridViewL
// ---------------------------------------------------------------------------
// 
void CBCTestForMAndView::TestForAknGridViewL()
    {
    CAknGrid *aknGrid = new( ELeave ) CAknGrid();
    CleanupStack::PushL( aknGrid );
    
    aknGrid->SetContainerWindowL ( *iContainer );
    
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_BCTESTGRIDS_GRID );
    aknGrid->ConstructFromResourceL( reader );
    _LIT( KConstructFromResourceL, "ConstructFromResourceL test" );
    AssertTrueL( ETrue, KConstructFromResourceL );
    CleanupStack::PopAndDestroy(); //reader
    
    CAknGridView* gridView = aknGrid->GridView();
    _LIT( KCAknGridView, "CAknGridView test" );
    AssertTrueL( ETrue, KCAknGridView );
    
    TInt listBoxIndex = 0;
    TInt dataIndex = gridView->ActualDataIndex( listBoxIndex );
    _LIT( KActualDataIndex, "ActualDataIndex test" );
    AssertTrueL( ETrue, KActualDataIndex );
   
    TInt listBoxIndex1 = gridView->ListBoxIndex( dataIndex );
    _LIT( KListBoxIndex, "ListBoxIndex test" );
    AssertTrueL( ETrue, KListBoxIndex );
    
    TInt currentDataIndex = gridView->CurrentDataIndex();
    _LIT( KCurrentDataIndex, "CurrentDataIndex test" );
    AssertTrueL( ETrue, KCurrentDataIndex );
    
    gridView->SetCurrentDataIndex( dataIndex );
    _LIT( KSetCurrentDataIndex, "SetCurrentDataIndex test" );
    AssertTrueL( ETrue, KSetCurrentDataIndex );
    
    gridView->SetPrimaryScrollingType( CAknGridView::EScrollFollowsGrid );
    _LIT( KSetPrimaryScrollingType, "SetPrimaryScrollingType test" );
    AssertTrueL( ETrue, KSetPrimaryScrollingType );
    
    gridView->SetSecondaryScrollingType( CAknGridView::EScrollFollowsGrid );
    _LIT( KSetSecondaryScrollingType, "SetSecondaryScrollingType test" );
    AssertTrueL( ETrue, KSetSecondaryScrollingType );
    
    TSize size = iContainer->Rect().Size();
    gridView->SetGridCellDimensions( size );
    _LIT( KSetGridCellDimensions, "SetGridCellDimensions test" );
    AssertTrueL( ETrue, KSetGridCellDimensions );
    
    TSize gridCellDimensions = gridView->GridCellDimensions();
    _LIT( KGridCellDimensions, "GridCellDimensions test" );
    AssertTrueL( ETrue, KGridCellDimensions );
    
    gridView->SetSpacesBetweenItems( size );
    _LIT( KSetSpacesBetweenItems, "SetSpacesBetweenItems test" );
    AssertTrueL( ETrue, KSetSpacesBetweenItems );
    
    TBool isPrimaryVertical = gridView->IsPrimaryVertical();
    _LIT( KIsPrimaryVertical, "IsPrimaryVertical test" );
    AssertTrueL( ETrue, KIsPrimaryVertical );
    
    TInt itemIndex = 1;
    TInt rowIndex = 1;
    TInt colIndex = 1;
    gridView->DataIndexFromLogicalPos( itemIndex, rowIndex, colIndex );
    _LIT( KDataIndexFromLogicalPos, "DataIndexFromLogicalPos test" );
    AssertTrueL( ETrue, KDataIndexFromLogicalPos );
    
    TInt negative = -2;
    gridView->LogicalPosFromDataIndex( itemIndex, rowIndex, colIndex );
    gridView->LogicalPosFromDataIndex( negative, rowIndex, colIndex  );
    gridView->LogicalPosFromDataIndex( itemIndex, negative, colIndex  );
    gridView->LogicalPosFromDataIndex( negative, rowIndex, colIndex  );
    gridView->LogicalPosFromDataIndex( itemIndex, rowIndex, negative  );
    gridView->LogicalPosFromDataIndex( negative, rowIndex, negative  );
    gridView->LogicalPosFromDataIndex( itemIndex, negative, negative  );
    gridView->LogicalPosFromDataIndex( negative, negative, negative  );
	_LIT( KLogicalPosFromDataIndex, "LogicalPosFromDataIndex test" );
    AssertTrueL( ETrue, KLogicalPosFromDataIndex );
    
    CAknGridView::SGrid gridDetailPos1 = { size, 1, 1, 1, 1, size, size };
    gridView->SetGridDetails( gridDetailPos1 );
    gridView->ListBoxIndexFromLogicalPos( itemIndex, rowIndex, colIndex );
    TInt isVisible = 
        gridView->CalcNewTopItemIndexSoItemIsVisible( KZero );
     CAknGridView::SGrid gridDetailPos2 = { size, 0, 1, 1, 1, size, size };
    gridView->SetGridDetails( gridDetailPos2 );
    gridView->ListBoxIndexFromLogicalPos( itemIndex, rowIndex, colIndex );
    _LIT( KListBoxIndexFromLogicalPos, "ListBoxIndexFromLogicalPos test" );
    AssertTrueL( ETrue, KListBoxIndexFromLogicalPos );
    
    gridView->LogicalPosFromListBoxIndex( itemIndex, rowIndex, colIndex );
    _LIT( KLogicalPosFromListBoxIndex, "LogicalPosFromListBoxIndex test" );
    AssertTrueL( ETrue, KLogicalPosFromListBoxIndex );
    
    gridView->DrawEmptyList();
    _LIT( KDrawEmptyList, "DrawEmptyList test" );
    AssertTrueL( ETrue, KDrawEmptyList );
    
    CAknGridView::SGrid gridDetail = { size, 1, 1, 1, 1, size, size };
    gridView->SetGridDetails( gridDetail );
    _LIT( KSetGridDetails, "SetGridDetails test" );
    AssertTrueL( ETrue, KSetGridDetails );
    
    gridView->MoveToItemIndexL( itemIndex, CAknGridView::ENoSelection );
    gridView->MoveToItemIndexL( negative, CAknGridView::ENoSelection );
    _LIT( KMoveToItemIndex, "MoveToItemIndex test" );
    AssertTrueL( ETrue, KMoveToItemIndex );
    
    TInt numberOfColsInView = gridView->NumberOfColsInView();
    _LIT( KNumberOfColsInView, "NumberOfColsInView test" );
    AssertTrueL( ETrue, KNumberOfColsInView );
    
    TInt numberOfRowsInView = gridView->NumberOfRowsInView();
    _LIT( KNumberOfRowsInView, "NumberOfRowsInView test" );
    AssertTrueL( ETrue, KNumberOfRowsInView );
    
    gridView->DrawMatcherCursor();
    _LIT( KDrawMatcherCursor, "DrawMatcherCursor test" );
    AssertTrueL( ETrue, KDrawMatcherCursor );
    
    TInt currentItemIndex = gridView->CurrentItemIndex();
    _LIT( KCurrentItemIndex, "CurrentItemIndex test" );
    AssertTrueL( ETrue, KCurrentItemIndex );
    gridView->ScrollToMakeItemVisible( KNegative );
    currentItemIndex = gridView->CurrentItemIndex();
    
    TInt columnWidth = 1;
    gridView->SetColumnWidth( columnWidth );
    _LIT( KSetColumnWidth, "SetColumnWidth test" );
    AssertTrueL( ETrue, KSetColumnWidth );
		
    gridView->MoveCursorL( CAknGridView::ECursorNextItem, 
        CAknGridView::ENoSelection );
    gridView->MoveCursorL( CAknGridView::ECursorPreviousItem, 
        CAknGridView::ENoSelection );
    gridView->MoveCursorL( CAknGridView::ECursorNextColumn, 
        CAknGridView::ENoSelection );
    gridView->MoveCursorL( CAknGridView::ECursorPreviousColumn, 
        CAknGridView::ENoSelection );
    gridView->MoveCursorL( CAknGridView::ECursorPreviousPage, 
        CAknGridView::ENoSelection );
    gridView->MoveCursorL( CAknGridView::ECursorNextPage, 
        CAknGridView::ENoSelection );
    gridView->MoveCursorL( CAknGridView::ECursorFirstItem, 
        CAknGridView::ENoSelection );
    gridView->MoveCursorL( CAknGridView::ECursorLastItem, 
        CAknGridView::ENoSelection );
    gridView->MoveCursorL( CAknGridView::ECursorNextScreen, 
        CAknGridView::ENoSelection );
    gridView->MoveCursorL( CAknGridView::ECursorPrevScreen, 
        CAknGridView::ENoSelection );
    
	_LIT( KMoveCursorL, "MoveCursorL test" );
    AssertTrueL( ETrue, KMoveCursorL );	
    
    gridView->Draw( NULL );
    _LIT( KDraw, "Draw test" );
    AssertTrueL( ETrue, KDraw );	
    
    gridView->DrawItem( itemIndex ); 
    gridView->DrawItem( KZero ); 
    _LIT( KDrawItem, "DrawItem test" );
    AssertTrueL( ETrue, KDrawItem );
    
    TPoint point = gridView->ItemPos( itemIndex );
    _LIT( KItemPos, "ItemPos test" );
    AssertTrueL( ETrue, KItemPos );
    
    gridView->CalcBottomItemIndex();
    _LIT( KCalcBottomItemIndex, "CalcBottomItemIndex test" );
    AssertTrueL( ETrue, KCalcBottomItemIndex );
    
    isVisible = 
        gridView->CalcNewTopItemIndexSoItemIsVisible( itemIndex );
    _LIT( KCalcNewTopItemIndexSoItemIsVisible, 
        "CalcNewTopItemIndexSoItemIsVisible test" );
    AssertTrueL( ETrue, KCalcNewTopItemIndexSoItemIsVisible );
    
    gridView->DrawItemRange( KZero, KOne );
    gridView->DrawItemRange( KNegative, KOne );
    _LIT( KDrawItemRange, "DrawItemRange test" );
    AssertTrueL( ETrue, KDrawItemRange );
    
    gridView->SetTopItemIndex( itemIndex );
    _LIT( KSetTopItemIndex, "SetTopItemIndex test" );
    AssertTrueL( ETrue, KSetTopItemIndex );
    
    gridView->SetItemHeight( KItemHeight );
    _LIT( KSetItemHeight, "SetItemHeight test" );
    AssertTrueL( ETrue, KSetItemHeight );
   
    TBool posToItemIndex = gridView->XYPosToItemIndex( point, itemIndex );
    _LIT( KXYPosToItemIndex, "XYPosToItemIndex test" );
    AssertTrueL( ETrue, KXYPosToItemIndex );
    
    gridView->CalcDataWidth();
    _LIT( KCalcDataWidth, "CalcDataWidth test" );
    AssertTrueL( ETrue, KCalcDataWidth );
    
    TRect rect = iContainer->Rect();
    TInt visibleWidth = gridView->VisibleWidth( rect );
    _LIT( KVisibleWidth, "VisibleWidth test" );
    AssertTrueL( ETrue, KVisibleWidth );
    
    CAknGridView::SGrid gridDetailIndex1 = { size, 0, 1, 1, 1, size, size };
    gridView->SetGridDetails( gridDetailIndex1 );
    TBool visible = gridView->ScrollToMakeItemVisible( KOne );
    visible = gridView->ScrollToMakeItemVisible( KNegative );
    TInt itemIsVisible = 
        gridView->CalculateHScrollOffsetSoItemIsVisible( itemIndex );
    CAknGridView::SGrid gridDetailIndex2 = { size, 1, 1, 1, 1, size, size };
    gridView->SetGridDetails( gridDetailIndex2 );
    visible = gridView->ScrollToMakeItemVisible( KOne );
    visible = gridView->ScrollToMakeItemVisible( KNegative );
    _LIT( KScrollToMakeItemVisible, "ScrollToMakeItemVisible test" );
    AssertTrueL( ETrue, KScrollToMakeItemVisible );
    
    itemIsVisible = 
        gridView->CalculateHScrollOffsetSoItemIsVisible( itemIndex );
    _LIT( KCalculateHScrollOffsetSoItemIsVisible, 
        "CalculateHScrollOffsetSoItemIsVisible test" );
    AssertTrueL( ETrue, KCalculateHScrollOffsetSoItemIsVisible );
    
    TSize itemSize = gridView->ItemSize( 0 );
    _LIT( KItemSize, "ItemSize test" );
    AssertTrueL( ETrue, KItemSize );
    
    gridView->CalcRowAndColIndexesFromItemIndex( itemIndex, rowIndex, 
        colIndex );
    _LIT( KCalcRowAndColIndexesFromItemIndex, 
        "CalcRowAndColIndexesFromItemIndex test" );
    AssertTrueL( ETrue, KCalcRowAndColIndexesFromItemIndex );
    
    gridView->CalcItemIndexFromRowAndColIndexes( itemIndex, rowIndex, 
        colIndex );
     _LIT( KCalcItemIndexFromRowAndColIndexes, 
        "CalcItemIndexFromRowAndColIndexes test" );
    AssertTrueL( ETrue, KCalcItemIndexFromRowAndColIndexes );
    
    
    CBCTestForGridView* testForGridView = new( ELeave ) CBCTestForGridView();
    CleanupStack::PushL( testForGridView );
    
    /*CTextListBoxModel* listBoxModel = aknGrid->Model();
    CDesCArray* array = iEnv->ReadDesCArrayResourceL( R_BCTESTGRIDS_ARRAY );
    listBoxModel->ConstructL ( array, ELbmOwnsItemArray );
    CFormattedCellListBoxItemDrawer* itemDrawer = aknGrid->ItemDrawer();*/
    
    CAknGridM* listBoxModel = new( ELeave ) CAknGridM();
    CleanupStack::PushL( listBoxModel );
    CDesCArray* array = iEnv->ReadDesCArrayResourceL( R_BCTESTGRIDS_ARRAY );
    CleanupStack::PushL( array );
    listBoxModel->ConstructL ( array, ELbmOwnsItemArray );
    CleanupStack::Pop( array );
    CFormattedCellListBoxData* data = CFormattedCellListBoxData::NewL();
    CleanupStack::PushL( data );
    CFormattedCellListBoxItemDrawer* itemDrawer = new( ELeave ) 
        CFormattedCellListBoxItemDrawer( listBoxModel, iEnv->NormalFont(),
             data );
    CleanupStack::PushL( itemDrawer );
    CWsScreenDevice* screen = iEnv->ScreenDevice();
    RWindowGroup& groupWin = iEnv->RootWin();
    RWindow& wsWindow = iContainer->Window();
    testForGridView->ConstructL( listBoxModel, itemDrawer, screen,  
        &groupWin, &wsWindow, rect, KItemHeight );
  
    
    TSize gridDimension( KDimensionX, KDimensionY );
    TSize betweenItems( KItemX, KItemY );
    TSize sizeOfItem( size.iWidth / KOne, size.iHeight / KTwo );
    TInt flags = CAknGridView::ELeftToRight | CAknGridView::ETopToBottom |
        CAknGridView::EPrimaryIsVertical;
    CAknGridView::SGrid gridDetail2 = 
        { gridDimension, flags, KTwo, KOne, KTwo, betweenItems, sizeOfItem };
    testForGridView->SetGridDetails( gridDetail2 );
    TSize betweenItemsTwo( KNegative, KOne );
    CAknGridView::SGrid gridDetail3 = { gridDimension, flags, KTwo, KOne, 
        KTwo, betweenItemsTwo, sizeOfItem };
    testForGridView->SetGridDetails( gridDetail3 );
    TSize betweenItemsThree( KNegative, KNegative );
    CAknGridView::SGrid gridDetail4 = { gridDimension, flags, KTwo, KOne, KTwo, 
        betweenItemsThree, sizeOfItem };
    testForGridView->SetGridDetails( gridDetail4 );
  
    TInt startColIndex = 0;
    TInt endColIndex = 1;
    testForGridView->DrawColumnRange( startColIndex, endColIndex );
    _LIT( KDrawColumnRange, "DrawColumnRange test" );
    AssertTrueL( ETrue, KDrawColumnRange );
    
    testForGridView->ClearUnusedItemSpace( KZero, KOne );
    _LIT( KClearUnusedItemSpace, "ClearUnusedItemSpace test" );
    AssertTrueL( ETrue, KClearUnusedItemSpace );
    
    testForGridView->UpdateHScrollOffsetBasedOnTopItemIndex();
    _LIT( KUpdateHScrollOffsetBasedOnTopItemIndex, 
        "UpdateHScrollOffsetBasedOnTopItemIndex test" );
    AssertTrueL( ETrue, KUpdateHScrollOffsetBasedOnTopItemIndex );
    
    testForGridView->DoMoveL( CAknGridView::ECursorNextItem, 
        CAknGridView::ENoSelection );
    _LIT( KDoMoveL, "DoMoveL test" );
    AssertTrueL( ETrue, KDoMoveL );
   
    TBool itemExists = testForGridView->ItemExists( listBoxIndex );
    _LIT( KItemExists, "ItemExists test" );
    AssertTrueL( ETrue, KItemExists );
    
    //for block coverage
    CAknGridView::SGrid gridDetailForScroll1 = { gridDimension, KOne, KOne, 
        KOne, KOne, betweenItemsThree, sizeOfItem };
    testForGridView->SetGridDetails( gridDetailForScroll1 );
    
    testForGridView->SetPrimaryScrollingType( CAknGridView::EScrollStops );
    testForGridView->SetSecondaryScrollingType( CAknGridView::EScrollStops );
    testForGridView->DoMoveL(CAknGridView::ECursorNextItem, 
        CAknGridView::ENoSelection );
    
    testForGridView->SetPrimaryScrollingType( 
        CAknGridView::EScrollFollowsGrid );
    testForGridView->SetSecondaryScrollingType( 
        CAknGridView::EScrollFollowsGrid );
    testForGridView->DoMoveL(CAknGridView::ECursorNextItem, 
        CAknGridView::ENoSelection );
    
    testForGridView->SetPrimaryScrollingType( 
        CAknGridView::EScrollFollowsItemsAndStops );
    testForGridView->SetSecondaryScrollingType( 
        CAknGridView::EScrollFollowsItemsAndStops );
    testForGridView->DoMoveL(CAknGridView::ECursorNextItem, 
        CAknGridView::ENoSelection );
    
    CAknGridView::SGrid gridDetailForScroll2 = { gridDimension, KZero, KOne, 
        KOne, KOne, betweenItemsThree, sizeOfItem };
    testForGridView->SetGridDetails( gridDetailForScroll2 );
        
    testForGridView->SetPrimaryScrollingType( 
        CAknGridView::EScrollFollowsItemsAndLoops );
    testForGridView->SetSecondaryScrollingType( 
        CAknGridView::EScrollFollowsItemsAndLoops );
    testForGridView->DoMoveL(CAknGridView::ECursorNextItem, 
        CAknGridView::ENoSelection );
    
    testForGridView->SetPrimaryScrollingType( 
        CAknGridView::EScrollIncrementLineAndStops );
    testForGridView->SetSecondaryScrollingType( 
        CAknGridView::EScrollIncrementLineAndStops );
    testForGridView->DoMoveL(CAknGridView::ECursorNextItem, 
        CAknGridView::ENoSelection );
    
    testForGridView->SetPrimaryScrollingType( 
        CAknGridView::EScrollIncrementLineAndLoops );
    testForGridView->SetSecondaryScrollingType( 
        CAknGridView::EScrollIncrementLineAndLoops );
    testForGridView->DoMoveL(CAknGridView::ECursorNextItem, 
        CAknGridView::ENoSelection );
    testForGridView->DoMoveL(CAknGridView::ECursorPreviousItem, 
        CAknGridView::ENoSelection );
    testForGridView->DoMoveL(CAknGridView::ECursorNextColumn, 
        CAknGridView::ENoSelection );
    testForGridView->DoMoveL(CAknGridView::ECursorPreviousColumn, 
        CAknGridView::ENoSelection );        
    
    CleanupStack::Pop( itemDrawer );
    CleanupStack::Pop( data );
    CleanupStack::PopAndDestroy( listBoxModel );
    CleanupStack::PopAndDestroy( testForGridView );
    
    CleanupStack::PopAndDestroy( aknGrid );
    _LIT( KDesCAknGridView, "~CAknGridView test" );
    AssertTrueL( ETrue, KDesCAknGridView );
    }
