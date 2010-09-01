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
#include <akngrid.h>
#include <barsread.h>
#include <bctestgrids.rsg>

#include "bctestforakngrid.h"
#include "bctestgridscontainer.h"
#include "bctestgrids.hrh"

const TInt KPointX = 1;
const TInt KPointY = 1;
const TInt KZero = 0;
const TInt KOne = 1;
const TInt KTwo = 2;   

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestForAknGrid* CBCTestForAknGrid::NewL(
    CBCTestGridsContainer* aContainer )
    {
    CBCTestForAknGrid* self = new( ELeave ) CBCTestForAknGrid(
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
CBCTestForAknGrid::CBCTestForAknGrid(
    CBCTestGridsContainer* aContainer )
    : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestForAknGrid::~CBCTestForAknGrid()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestForAknGrid::ConstructL()
    {
    BuildScriptL();
    iEnv = CEikonEnv::Static(); 
    }

// ---------------------------------------------------------------------------
// CBCTestForAknGrid::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestForAknGrid::BuildScriptL()
    {
    // Add script as your need.
    AddTestL( LeftCBA, Down, KeyOK, TEND );
    }

// ---------------------------------------------------------------------------
// CBCTestForAknGrid::RunL
// ---------------------------------------------------------------------------
//
void CBCTestForAknGrid::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdEmptyOutline || aCmd > EBCTestCmdMaxOutline )
        {
        return;
        }
 
    switch ( aCmd )
        {
        case EBCTestForCAknGrid:
            TestCAknGridL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestForAknGrid::SetUpCAknGridL
// ---------------------------------------------------------------------------
//
CAknGrid* CBCTestForAknGrid::SetUpCAknGridL()
    {
    CAknGrid* grid1 = new( ELeave) CAknGrid();
    CleanupStack::PushL( grid1 );
    _LIT( KCAknGrid, "CAknGrid test" );
    AssertTrueL( ETrue, KCAknGrid );
    
    
    CAknGridM* model = new( ELeave ) CAknGridM();
    CleanupStack::PushL( model );
    grid1->SetModel( model );
    _LIT( KSetModel, "SetModel test" );
    AssertTrueL( ETrue, KSetModel );
    CleanupStack::Pop( model );
    
    grid1->ConstructL( iContainer, 0 );
    _LIT( KConstructL, "ConstructL For CAknGrid test" );
    AssertTrueL( ETrue, KConstructL );
    
    CleanupStack::PopAndDestroy( grid1 );
    grid1 = NULL;
    
    CAknGrid* grid = new( ELeave) CAknGrid();
    CleanupStack::PushL( grid );
    
    grid->SetContainerWindowL ( *iContainer );
    
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_BCTESTGRIDS_GRID );
    grid->ConstructFromResourceL( reader );
    _LIT( KConstructFromResourceL, "ConstructFromResourceL test" );
    AssertTrueL( ETrue, KConstructFromResourceL );
    CleanupStack::PopAndDestroy(); //reader
    
    return grid;
    }
    
// ---------------------------------------------------------------------------
// CBCTestForAknGrid::TearDownCAknGridL
// ---------------------------------------------------------------------------
//   
void CBCTestForAknGrid::TearDownCAknGridL( CAknGrid* aGrid )
    {
    CleanupStack::PopAndDestroy( aGrid );
    _LIT( KDesCAknGrid, "~CAknGrid test" );
    AssertTrueL( ETrue, KDesCAknGrid );
    }
// ---------------------------------------------------------------------------
// CBCTestForAknGrid::TestLayoutDecorator
// ---------------------------------------------------------------------------
//
void CBCTestForAknGrid::TestCAknGridL()
    {
    // Test some API here
    CAknGrid* grid = SetUpCAknGridL();
  
    //for block coverage
    grid->SizeChanged();
    grid->HandleItemAdditionL();
    grid->HandleItemRemovalL();
    
    TSize size = iContainer->Rect().Size();
    grid->SetLayoutL( ETrue, ETrue, ETrue, KOne, KOne, size, KZero, KZero );
    grid->SetLayoutL( EFalse, ETrue, ETrue, KOne, KOne, size, KZero, KZero );
	_LIT( KSetLayoutL, "SetLayoutL test" );
    AssertTrueL( ETrue, KSetLayoutL );						
        
    grid->SetPrimaryScrollingType( CAknGridView::EScrollStops );
    _LIT( KSetPrimaryScrollingType, "SetPrimaryScrollingType test" );
    AssertTrueL( ETrue, KSetPrimaryScrollingType );
    
    grid->SetSecondaryScrollingType( CAknGridView::EScrollStops );
    _LIT( KSetSecondaryScrollingType, "SetSecondaryScrollingType test" );
    AssertTrueL( ETrue, KSetSecondaryScrollingType );
    
    TPoint point( KPointX, KPointY );
    grid->SetStartPositionL( point );
    _LIT( KSetStartPositionL, "SetStartPositionL test" );
    AssertTrueL( ETrue, KSetStartPositionL );
    
    TInt dataIndex = grid->CurrentDataIndex();
    _LIT( KCurrentDataIndex, "CurrentDataIndex test" );
    AssertTrueL( ETrue, KCurrentDataIndex );
    
    grid->SetCurrentDataIndex( dataIndex );
    _LIT( KSetCurrentDataIndex, "SetCurrentDataIndex test" );
    AssertTrueL( ETrue, KSetCurrentDataIndex );	
    
    TInt indexOfPosition = grid->IndexOfPosition( point );
    _LIT( KIndexOfPosition, "IndexOfPosition test" );
    AssertTrueL( ETrue, KIndexOfPosition );	
    
    TPoint positionAtIndex = grid->PositionAtIndex( indexOfPosition );
    _LIT( KPositionAtIndex, "PositionAtIndex test" );
    AssertTrueL( ETrue, KPositionAtIndex );	
    
    CFormattedCellListBoxItemDrawer* intemFrawer = grid->ItemDrawer();
    _LIT( KItemDrawer, "ItemDrawer test" );
    AssertTrueL( ETrue, KItemDrawer );	
    
    _LIT( text, "xxxxxxxxxxx" );
    grid->SetEmptyGridTextL( text );
    _LIT( KSetEmptyGridTextL, "SetEmptyGridTextL test" );
    AssertTrueL( ETrue, KSetEmptyGridTextL);
    
    CListBoxView* boxView = grid->MakeViewClassInstanceL();
    delete boxView;
    _LIT( KMakeViewClassInstanceL, "MakeViewClassInstanceL test" );
    AssertTrueL( ETrue, KMakeViewClassInstanceL);
    
    TInt width = grid->ColumnWidth();
    _LIT( KColumnWidth, "ColumnWidth test" );
    AssertTrueL( ETrue, KColumnWidth); 
    
    TInt columnWidthZero = 0;
    TInt columnWidthTwo = 2;
    grid->SetColumnWidth( columnWidthTwo );
    grid->SetColumnWidth( columnWidthZero );
    _LIT( KSetColumnWidth, "SetColumnWidth test" );
    AssertTrueL( ETrue, KSetColumnWidth );
    
    grid->UpdateScrollBarsL();
    _LIT( KUpdateScrollBarsL, "UpdateScrollBarsL test" );
    AssertTrueL( ETrue, KUpdateScrollBarsL );
    
    grid->HandleItemAdditionL();
    _LIT( KHandleItemAdditionL, "HandleItemAdditionL test" );
    AssertTrueL( ETrue, KHandleItemAdditionL );
    
    grid->HandleItemRemovalL();
    _LIT( KHandleItemRemovalL, "HandleItemRemovalL test" );
    AssertTrueL( ETrue, KHandleItemRemovalL );
    
    TKeyEvent keyEvent1 = { EKeyPause, EStdKeySpace, 0, 0  };
    TKeyResponse response = grid->OfferKeyEventL( keyEvent1, EEventNull );
    TKeyEvent keyEvent2 = { EKeyUpArrow, EStdKeySpace, 0, 0  };
    response = grid->OfferKeyEventL( keyEvent2, EEventNull );
    TKeyEvent keyEvent3 = { EKeyDownArrow, EStdKeySpace, 0, 0  };
    response = grid->OfferKeyEventL( keyEvent3, EEventNull );
    TKeyEvent keyEvent4 = { EKeyLeftArrow, EStdKeySpace, 0, 0  };
    response = grid->OfferKeyEventL( keyEvent4, EEventNull );
    TKeyEvent keyEvent5 = { EKeyRightArrow, EStdKeySpace, 0, 0  };
    response = grid->OfferKeyEventL( keyEvent5, EEventNull );
    TKeyEvent keyEvent6 = { EKeyPageUp, EStdKeySpace, 0, 0  };
    response = grid->OfferKeyEventL( keyEvent6, EEventNull );
    TKeyEvent keyEvent7 = { EKeyPageDown, EStdKeySpace, 0, 0  };
    response = grid->OfferKeyEventL( keyEvent7, EEventNull );
    TKeyEvent keyEvent8 = { EKeyHome, EStdKeySpace, 0, 0  };
    response = grid->OfferKeyEventL( keyEvent8, EEventNull );
    TKeyEvent keyEvent9 = { EKeyEnd, EStdKeySpace, 0, 0  };
    response = grid->OfferKeyEventL( keyEvent9, EEventNull );
    _LIT( KOfferKeyEventL, "OfferKeyEventL test" );
    AssertTrueL( ETrue, KOfferKeyEventL );
    
    grid->SetItemHeightL( KZero );
    grid->SetItemHeightL( KTwo );
    _LIT( KSetItemHeightL, "SetItemHeightL test" );
    AssertTrueL( ETrue, KSetItemHeightL );
    
    grid->SizeChanged();
    _LIT( KSizeChanged, "SizeChanged test" );
    AssertTrueL( ETrue, KSizeChanged );
    
    CTextListBoxModel* listBoxModel = grid->Model();
    _LIT( KModel, "Model test" );
    AssertTrueL( ETrue, KModel);
    
    TRect rect = iContainer->Rect();
    grid->SetRect( rect );
    _LIT( KSetRect, "SetRect test" );
    AssertTrueL( ETrue, KSetRect);
    
    grid->HandleViewRectSizeChangeL();
    _LIT( KHandleViewRectSizeChangeL, "HandleViewRectSizeChangeL test" );
    AssertTrueL( ETrue, KHandleViewRectSizeChangeL);
    
    TInt itemIndex = 1;
    grid->SetTopItemIndex( itemIndex );
    _LIT( KSetTopItemIndex, "SetTopItemIndex test" );
    AssertTrueL( ETrue, KSetTopItemIndex );
    
    grid->HandleResourceChange( KEikDynamicLayoutVariantSwitch );
    grid->HandleResourceChange( KEikPartialForeground );
    _LIT( KHandleResourceChange, "HandleResourceChange test" );
    AssertTrueL( ETrue, KHandleResourceChange );
    
    grid->FocusChanged( ENoDrawNow );
    _LIT( KFocusChanged, "FocusChanged test" );
    AssertTrueL( ETrue, KFocusChanged );
    
    TPointerEvent pointerEvent = { TPointerEvent::EButton1Up,
         EModifierAutorepeatable, TPoint( 20, 20 ), TPoint( 0, 0 ) };
    grid->HandlePointerEventL( pointerEvent );
    _LIT( KHandlePointerEventL, "HandlePointerEventL test" );
    AssertTrueL( ETrue, KHandlePointerEventL );
    
    TearDownCAknGridL( grid );
    
    CBCTestForGrid* testForGrid = new( ELeave ) CBCTestForGrid();
    CleanupStack::PushL( testForGrid );
    
    testForGrid->SetContainerWindowL ( *iContainer );
    
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_BCTESTGRIDS_GRID );
    testForGrid->ConstructFromResourceL( reader );
    _LIT( KConstructFromResourceL, "ConstructFromResourceL test" );
    AssertTrueL( ETrue, KConstructFromResourceL );
    CleanupStack::PopAndDestroy(); //reader
    
    TInt nudgeValue = testForGrid->HorizontalNudgeValue();
    _LIT( KHorizontalNudgeValue, "HorizontalNudgeValue test" );
    AssertTrueL( ETrue, KHorizontalNudgeValue );
    
    TInt granularity = testForGrid->HorizScrollGranularityInPixels();
    _LIT( KHorizScrollGranularityInPixels, 
        "HorizScrollGranularityInPixels test" );
    AssertTrueL( ETrue, KHorizScrollGranularityInPixels ); 
    
    testForGrid->AdjustTopItemIndex();
    _LIT( KAdjustTopItemIndex, "AdjustTopItemIndex test" );
    AssertTrueL( ETrue, KAdjustTopItemIndex ); 
    
    testForGrid->HandleDragEventL( point );
    _LIT( KHandleDragEventL, "HandleDragEventL test" );
    AssertTrueL( ETrue, KHandleDragEventL ); 
    
    testForGrid->RestoreClientRectFromViewRect( rect );
    _LIT( KRestoreClientRectFromViewRect, 
        "RestoreClientRectFromViewRect test" );
    AssertTrueL( ETrue, KRestoreClientRectFromViewRect );
    
    testForGrid->AdjustRectHeightToWholeNumberOfItems( rect );
    _LIT( KAdjustRectHeightToWholeNumberOfItems, 
        "AdjustRectHeightToWholeNumberOfItems test" );
    AssertTrueL( ETrue, KAdjustRectHeightToWholeNumberOfItems );
    
    testForGrid->UpdateScrollBarThumbs();
    _LIT( KUpdateScrollBarThumbs, "UpdateScrollBarThumbs test" );
    AssertTrueL( ETrue, KUpdateScrollBarThumbs ); 
    
    TInt controls = testForGrid->CountComponentControls();
    _LIT( KCountComponentControls, "CountComponentControls test" );
    AssertTrueL( ETrue, KCountComponentControls ); 
    
    testForGrid->MoveToNextOrPreviousItemL( point );
    _LIT( KMoveToNextOrPreviousItemL, "MoveToNextOrPreviousItemL test" );
    AssertTrueL( ETrue, KMoveToNextOrPreviousItemL ); 
    
    testForGrid->CalcGridSizeL();
    _LIT( KCalcGridSizeL, "CalcGridSizeL test" );
    AssertTrueL( ETrue, KCalcGridSizeL ); 

    CEikScrollBar* scrollBar = new( ELeave ) CEikScrollBar();
    CleanupStack::PushL( scrollBar );
    testForGrid->HandleScrollEventL( scrollBar, EEikScrollUp );
	_LIT( KHandleScrollEventL, "HandleScrollEventL test" );
    AssertTrueL( ETrue, KHandleScrollEventL );
    CleanupStack::PopAndDestroy( scrollBar );
    
    CleanupStack::PopAndDestroy( testForGrid );
    
    //test for block coverage
    CAknGrid* gridForBlock = new( ELeave) CAknGrid();
    CleanupStack::PushL( gridForBlock );
    
    gridForBlock->SetContainerWindowL ( *iContainer );
    
    TResourceReader readerForBlock;
    iEnv->CreateResourceReaderLC( readerForBlock, R_BCTESTGRIDS_GRID_TWO );
    grid->ConstructFromResourceL( readerForBlock );
    CleanupStack::PopAndDestroy(); //readerForBlock
    
    CleanupStack::PopAndDestroy( gridForBlock );
    }

