/*
* Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  CAknGridView handles the drawing, the mapping
*                of the grid data index to the underlying listbox index (and
*                vice versa) as well as the movement around the grid.
*
*/

#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikdefmacros.h>
#endif
#include <AknGridView.h>
#include <AknGridM.h>
#include <AknUtils.h>

#include <eikenv.h>
#include <gulutil.h>
#include <eiklbv.h>
#include <eiklbi.h>
#include <eiklbm.h>
#include <eiklbx.h>
#include <eiklbx.pan>
#include <eikpanic.h>
#include <eikfrlb.h>
#include <gulutil.h>
#include <eikfrlbd.h>

#include <AknsDrawUtils.h>
#include <AknsControlContext.h>
#include <aknphysics.h>

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
#include <aknlistloadertfx.h>
#include <aknlistboxtfxinternal.h>
#endif //RD_UI_TRANSITION_EFFECTS_LIST
#include "akntrace.h"

/**
 * Local Panic Function and Panic Codes
 */
enum TAknGridViewPanicCodes
    {
    EAknPanicGridViewGeneralPanic,
    EAknPanicGridViewInvalidRowIndex,
    EAknPanicGridViewInvalidColumnIndex,
    EAknPanicGridViewNoGraphicsContext,
    EAknPanicGridViewNoModel,
    EAknPanicGridViewInvalidNumberOfRows,
    EAknPanicGridViewInvalidNumberOfColumns,
    EAknPanicGridViewInvalidItemWidth,
    EAknPanicGridViewInvalidItemHeight
    };

GLDEF_C void Panic(TAknGridViewPanicCodes aPanic)
    {
    _LIT(KPanicCat,"AknGridView");
    User::Panic(KPanicCat, aPanic);
    }


/**
 * Constructor
 */
EXPORT_C CAknGridView::CAknGridView()
    {
    iScrollingType = EScrollFollowsItemsAndLoops;
    iScrollInSecondaryDimension = EScrollFollowsItemsAndLoops;
    iGridDetails.iGridDimensions = TSize(1,1);
    }

/**
 * Destructor
 */
EXPORT_C CAknGridView::~CAknGridView()
    {
    }

// data index <-> row/column calculation

/**
 * Converts a logical position on the grid, where the coordinates are with respect to
 * the top left hand corner of the grid, to an index for the cell with respect to the
 * ordering of the cells in the grid.
 */
EXPORT_C void CAknGridView::DataIndexFromLogicalPos(
    TInt& aItemIndex,
    TInt aRowIndex,
    TInt aColIndex) const
    {
    _AKNTRACE_FUNC_ENTER;
    // row and column orientated from  top left corner which is (0,0)

    // check minimums
    __ASSERT_ALWAYS((aRowIndex >= 0), Panic(EAknPanicGridViewInvalidRowIndex));
    __ASSERT_ALWAYS((aColIndex >= 0), Panic(EAknPanicGridViewInvalidColumnIndex));

    _AKNTRACE( "[%s] aItemIndex = %d aRowIndex = %d aColIndex = %d", 
    		   __FUNCTION__, aItemIndex, aRowIndex, aColIndex );
    // calculate number of cells from lowest index corner
    if (IsPrimaryVertical())
        {
        // work out how many complete columns from lowest index
        // to required position
        TInt numOfCols = aColIndex;
        if (!(iGridDetails.iGridFlags & ELeftToRight))
            numOfCols = (iGridDetails.iGridDimensions.iWidth - 1) - numOfCols;

        // process the row to calculate final index value depending
        // on orientation of lowest index with respect to the top to
        // bottom numbering of the rows.
        TInt adjustment = aRowIndex;
        if (!(iGridDetails.iGridFlags & ETopToBottom))
            {
            adjustment = -(adjustment + 1);
            numOfCols++;
            }

        aItemIndex = numOfCols * NumberOfRowsInView();
        aItemIndex += adjustment;
        }
    else
        {
        TInt numOfRows = aRowIndex;
        if (!(iGridDetails.iGridFlags & ETopToBottom))
            numOfRows = (iGridDetails.iGridDimensions.iHeight - 1) - numOfRows;

        TInt numOfCols  = aColIndex;
        if (!(iGridDetails.iGridFlags & ELeftToRight))
            {
            numOfCols = (NumberOfColsInView() - 1) - numOfCols;
            }

        aItemIndex = numOfRows * NumberOfColsInView();
        aItemIndex += numOfCols;
        }
    _AKNTRACE_FUNC_EXIT;
    }

/**
 * Converts an index for a cell in the grid, given with respect to the ordering
 * of the cells in the grid, to a logical position on the grid, where the coordinates
 * are with respect to the top left hand corner of the grid.
 */
EXPORT_C void CAknGridView::LogicalPosFromDataIndex(
    TInt aItemIndex,
    TInt& aRowIndex,
    TInt& aColIndex) const
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "[%s] aItemIndex = %d aRowIndex = %d aColIndex = %d", 
    		   __FUNCTION__, aItemIndex, aRowIndex, aColIndex );
    // refer to DataIndexFromLogicalPos above for explanation of mapping of data indexes
    if (aItemIndex > 0)
        {
        if (IsPrimaryVertical())
            {
            aColIndex = aItemIndex / NumberOfRowsInView();
            aRowIndex = aItemIndex % NumberOfRowsInView();
            }
        else
            {
            aRowIndex = aItemIndex / NumberOfColsInView();
            aColIndex = aItemIndex % NumberOfColsInView();
            }
        }
    else
        {
        aRowIndex = 0;
        aColIndex = 0;
        }

    if (!(iGridDetails.iGridFlags & ELeftToRight))
        aColIndex = (iGridDetails.iGridDimensions.iWidth - 1) - aColIndex;

    if (!(iGridDetails.iGridFlags & ETopToBottom))
        aRowIndex = (iGridDetails.iGridDimensions.iHeight - 1) - aRowIndex;

    if (aColIndex < 0)
        aColIndex = 0;
    if (aRowIndex < 0)
        aRowIndex = 0;
    _AKNTRACE_FUNC_EXIT;
    }

/**
 * Converts a CEikListBox index for a cell in the grid, given with respect to the
 * snaking listbox top down, left to right structure underlying the grid
 * structure, to a logical position on the grid, where the coordinates are with
 * respect to the top left hand corner of the grid.
 */
EXPORT_C void CAknGridView::ListBoxIndexFromLogicalPos(
    TInt& aItemIndex,
    TInt aRowIndex,
    TInt aColIndex) const
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "[%s] aItemIndex = %d aRowIndex = %d aColIndex = %d", 
    		   __FUNCTION__, aItemIndex, aRowIndex, aColIndex );
    // check minimums
    __ASSERT_DEBUG((aRowIndex >= 0), Panic(EAknPanicGridViewInvalidRowIndex));
    __ASSERT_DEBUG((aColIndex >= 0), Panic(EAknPanicGridViewInvalidColumnIndex));

    if(IsPrimaryVertical())
        {
        aItemIndex = aColIndex * NumberOfRowsInView();
        aItemIndex += aRowIndex;
        }
    else
        {
        aItemIndex = aRowIndex * NumberOfColsInView();
        aItemIndex += aColIndex;
        }
    _AKNTRACE_FUNC_EXIT;
    }

/**
 * Converts a logical position on the grid, where the coordinates are with respect to
 * the top left hand corner of the grid, to a CEikListBox index for the cell with
 * respect to the snaking listbox top down, left to right structure underlying the
 * grid structure.
 */
EXPORT_C void CAknGridView::LogicalPosFromListBoxIndex(TInt aItemIndex, TInt& aRowIndex, TInt& aColIndex) const
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "[%s] aItemIndex = %d aRowIndex = %d aColIndex = %d", 
    		   __FUNCTION__, aItemIndex, aRowIndex, aColIndex );
    aColIndex = 0;
    aRowIndex = 0;

    if (aItemIndex)
        {
        if(IsPrimaryVertical())
            {
            aColIndex = aItemIndex / NumberOfRowsInView();
            aRowIndex = aItemIndex % NumberOfRowsInView();
            }
        else
            {
            aColIndex = aItemIndex % NumberOfColsInView();
            aRowIndex = aItemIndex / NumberOfColsInView();
            }
        }
    _AKNTRACE_FUNC_EXIT;
    }

// data index <-> listbox index conversion routines

/**
 * Converts an underlying CEikListBox index into the equivalent grid
 * cell index given with respect to the ordering of the cells in the grid.
 */
EXPORT_C TInt CAknGridView::ActualDataIndex(TInt aListBoxIndex) const
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "[%s] aListBoxIndex = %d", 
    		   __FUNCTION__, aListBoxIndex );
    TInt logicalRow = 0;
    TInt logicalCol = 0;
    LogicalPosFromListBoxIndex(aListBoxIndex, logicalRow, logicalCol);

    TInt dataIndex = 0;
    DataIndexFromLogicalPos(dataIndex, logicalRow, logicalCol);

    _AKNTRACE_FUNC_EXIT;
    return dataIndex;
    }

/**
 * Converts a grid cell index into the equivalent CEikListBox index for
 * the underlying snaking listbox top down, left to right structure.
 */
EXPORT_C TInt CAknGridView::ListBoxIndex(TInt aDataIndex) const
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "[%s] aDataIndex = %d", 
    		   __FUNCTION__, aDataIndex );
    TInt logicalRow = 0;
    TInt logicalCol = 0;
    LogicalPosFromDataIndex(aDataIndex, logicalRow, logicalCol);

    TInt listBoxIndex = 0;
    ListBoxIndexFromLogicalPos(listBoxIndex, logicalRow, logicalCol);

    _AKNTRACE_FUNC_EXIT;
    return listBoxIndex;
    }

// the current data item
/**
 * Returns the current data index with respect to the ordering of the cells in
 * the grid.
 */
EXPORT_C TInt CAknGridView::CurrentDataIndex() const
    {
    return ActualDataIndex(iCurrentItemIndex);
    }

/**
 * Sets the current data index with a value given with respect to the ordering of
 * the cells in the grid.
 */
EXPORT_C void CAknGridView::SetCurrentDataIndex(TInt aDataIndex)
    {
    _AKNTRACE( "[%s] aDataIndex = %d", 
    		   __FUNCTION__, aDataIndex );
    TRAP_IGNORE(MoveToItemIndexL(ListBoxIndex(aDataIndex),ENoSelection));
    }

// grid functions

/**
 * Checks that number of cells in the grid is always enough to fill the
 * current grid dimensions. This method should be called after any
 * method that may alter the amount of data within the grid.
 *
 */
EXPORT_C void CAknGridView::SetGridCellDimensions(TSize aGridDimensions)
    {
    // set the new grid size
    iGridDetails.iGridDimensions = aGridDimensions;
    }

/**
 * Returns the current grid dimensions.
 */
EXPORT_C TSize CAknGridView::GridCellDimensions() const
    {
    return iGridDetails.iGridDimensions;
    }

/**
 * Sets the size of the spaces between items.
 */
EXPORT_C void CAknGridView::SetSpacesBetweenItems(TSize aSizeOfSpaceBetweenItems)
    {
    iGridDetails.iSizeBetweenItems = TSize(0,0);
    if (aSizeOfSpaceBetweenItems.iWidth > 0)
        {
        iGridDetails.iSizeBetweenItems.iWidth=aSizeOfSpaceBetweenItems.iWidth;
        }
    if (aSizeOfSpaceBetweenItems.iHeight > 0)
        {
        iGridDetails.iSizeBetweenItems.iHeight=aSizeOfSpaceBetweenItems.iHeight;
        }
    }

/**
 * Sets the form of scroll to activate upon reaching the limit when moving in
 * the primary direction of grid, primary meaning whether the items are
 * organised vertically or horizontally.
 */
EXPORT_C void CAknGridView::SetPrimaryScrollingType(TScrollingType aScrollingType)
    {
    iScrollingType = aScrollingType;
    }

/**
 * Sets the form of scroll to activate upon reaching the limit when moving in
 * the secondary direction of grid.
 */
EXPORT_C void CAknGridView::SetSecondaryScrollingType(TScrollingType aSecondaryScrolling)
    {
    iScrollInSecondaryDimension = aSecondaryScrolling;
    }


/**
 * Returns true if the primary dimension of the grid is
 * vertical.
 */
EXPORT_C TBool CAknGridView::IsPrimaryVertical() const
    {
    return (iGridDetails.iGridFlags & EPrimaryIsVertical);
    }

/**
 * Returns ETrue if the CEikListBox index given exists.
 */
EXPORT_C TBool CAknGridView::ItemExists(TInt aListBoxIndex) const
    {
    TInt totalpossibleitems = iGridDetails.iGridDimensions.iHeight * iGridDetails.iGridDimensions.iWidth;

    return ((aListBoxIndex > -1) && (aListBoxIndex < totalpossibleitems));
    }


/**
 * This has been overloaded to ensure that only valid cells are drawn
 * and not the empty cells.
 */
EXPORT_C void CAknGridView::DrawItem( TInt aItemIndex ) const
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "[%s] aItemIndex = %d", 
    		   __FUNCTION__, aItemIndex );
    if ( RedrawDisabled() || !IsVisible() )
        {
        _AKNTRACE_FUNC_EXIT;
        return;
        }

    if ( ItemExists( aItemIndex ) )
        {
        TBool transparencyEnabled( CAknEnv::Static()->TransparencyEnabled() );
        TBool drawingInitiated = ETrue;
        TPoint itemPosition( ItemPos( aItemIndex ) );

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        MAknListBoxTfxInternal* transApi =
            CAknListLoader::TfxApiInternal( iGc );
#endif // RD_UI_TRANSITION_EFFECTS_LIST

        if ( transparencyEnabled )
            {
            if ( iWin && iWin->GetDrawRect() == TRect::EUninitialized )
                {
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
                drawingInitiated = transApi && !transApi->EffectsDisabled();
#else
                drawingInitiated = EFalse;
#endif
                }

            if ( !drawingInitiated )
                {
                TRect itemRect( itemPosition, ItemSize( aItemIndex ) );
                itemRect.Intersection( iViewRect );
                iWin->Invalidate( itemRect );
                iWin->BeginRedraw( itemRect );
                }
            }

        // convert to actual data index
        TInt dataIndex = ActualDataIndex( aItemIndex );

        __ASSERT_DEBUG( (iGc), Panic( EAknPanicGridViewNoGraphicsContext ) );

        if ( GridModel()->IndexContainsData( dataIndex ) )
            {
            // It must be ensured here that an item isn't drawn outside
            // the view rectangle.
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
            if ( transApi )
                {
                transApi->StartDrawing( MAknListBoxTfxInternal::EListNotSpecified );
                }
#endif // RD_UI_TRANSITION_EFFECTS_LIST

            iGc->SetClippingRect( iViewRect );
            
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
            if ( transApi )
                {
                transApi->StopDrawing();
                }
#endif // RD_UI_TRANSITION_EFFECTS_LIST

            iItemDrawer->DrawItem(
                dataIndex,
                itemPosition,
                ItemIsSelected( aItemIndex ),
                aItemIndex == iCurrentItemIndex,
                ( iFlags & EEmphasized ) == EEmphasized,
                ( iFlags & EDimmed ) == EDimmed );

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
            if ( transApi )
                {
                transApi->StartDrawing( MAknListBoxTfxInternal::EListNotSpecified );
                }
#endif // RD_UI_TRANSITION_EFFECTS_LIST

            iGc->CancelClippingRect();
            
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
            if ( transApi )
                {
                transApi->StopDrawing();
                }
#endif // RD_UI_TRANSITION_EFFECTS_LIST
            }
        else
            {
            static_cast<CFormattedCellListBoxItemDrawer*>( iItemDrawer )->
                DrawEmptyItem( dataIndex,
                               ItemPos( aItemIndex ),
                               ( iFlags & EDimmed ) == EDimmed );
            }

        if ( transparencyEnabled && !drawingInitiated )
            {
            iWin->EndRedraw();
            }
        }
    _AKNTRACE_FUNC_EXIT;
    }


/**
 * This has been overloaded to ensure that if no cells exist in the
 * grid then an empty grid is displayed. And also to correct drawing.
 */
EXPORT_C void CAknGridView::Draw( const TRect* aClipRect ) const
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "The rect of grid are ( %d, %d ) ( %d, %d )", 
    		   aClipRect->iTl.iX, aClipRect->iTl.iY, 
    		   aClipRect->iBr.iX, aClipRect->iBr.iY );
    if ( RedrawDisabled() || iItemHeight == 0 || ColumnWidth() == 0 )
        {
        _AKNTRACE_FUNC_EXIT;
        return;
        }

    if ( GridModel()->NumberOfData() == 0 )
        {
        DrawEmptyList();
        }
    else
        {
        if (RedrawDisabled())
        	{
        	_AKNTRACE_FUNC_EXIT;
            return;
        	}
        __ASSERT_DEBUG(iModel, Panic(EAknPanicGridViewNoModel));
        if (iItemHeight == 0)
        	{
        	_AKNTRACE_FUNC_EXIT;
            return;
        	}
        if ( !aClipRect )
            {
            aClipRect = &iViewRect;
            }
        
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        MAknListBoxTfxInternal* transApi = CAknListLoader::TfxApiInternal( iGc );
        if ( transApi )
            {
            aClipRect = &iViewRect;
            transApi->SetListType( MAknListBoxTfxInternal::EListBoxTypeGrid );    
            transApi->StartDrawing( MAknListBoxTfxInternal::EListNotSpecified );
            }
#endif //RD_UI_TRANSITION_EFFECTS_LIST

        iGc->SetClippingRect( *aClipRect );

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    if ( transApi )
        {
        transApi->StopDrawing();
        }
#endif

        TInt numberOfItems( iModel->NumberOfItems() );
        TInt numberOfCols( NumberOfColsInView() );
        TInt numberOfCells( numberOfItems );
        TInt emptyCellsAtEnd( numberOfItems % numberOfCols );
        if ( emptyCellsAtEnd )
            {
            // Add empty cells to the last row if it's not full so
            // that the whole row gets it's background drawn.
            numberOfCells += ( numberOfCols - emptyCellsAtEnd );
            }
        TInt numberOfRows( numberOfCells / numberOfCols );
        TInt firstPotentialItemIndex = iTopItemIndex >= numberOfCols ? iTopItemIndex - numberOfCols : iTopItemIndex;
        TInt lastPotentialItemIndex = iTopItemIndex + 
            ( NumberOfItemsThatFitInRect(iViewRect) * numberOfCols - 1 ) + numberOfCols;

        if ( lastPotentialItemIndex / numberOfCols > numberOfRows )
            {
            // Check that there isn't an empty row at the bottom.
            lastPotentialItemIndex -= numberOfCols;
            }

        // Clear the unused portion of the viewing area.
        DrawUnusedViewPortion();

        for ( TInt i = firstPotentialItemIndex; i <= lastPotentialItemIndex; i++ )
            {
            if ( ItemExists( i ) )
                {
                DrawItem( i );
                }
            else
                {
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
                if ( transApi )
                    {
                    transApi->StartDrawing( MAknListBoxTfxInternal::EListView );
                    }
#endif

                iGc->SetClippingRect( *aClipRect );
                ClearUnusedItemSpace( i, lastPotentialItemIndex );

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
                if ( transApi )
                    {
                    transApi->StopDrawing();
                    }
#endif
                break;
                }
            }

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        if ( transApi )
            {
            transApi->StartDrawing( MAknListBoxTfxInternal::EListView );
            }
#endif


        iGc->CancelClippingRect();
        
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
	    if ( transApi )
	        {
            transApi->StopDrawing();
            }
#endif //RD_UI_TRANSITION_EFFECTS_LIST
        }
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// This function has been overloaded to draw items correctly.
// ---------------------------------------------------------------------------
//
EXPORT_C TPoint CAknGridView::ItemPos( TInt aItemIndex ) const
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "[%s] aItemIndex = %d", 
    		   __FUNCTION__, aItemIndex );
    TInt rowIndex = 0;
    TInt colIndex = 0;
    CalcRowAndColIndexesFromItemIndex( aItemIndex, rowIndex, colIndex );
    
    TPoint itemPos(
        iViewRect.iTl.iX + colIndex *
            ( ColumnWidth() + iGridDetails.iSizeBetweenItems.iWidth ),
        iViewRect.iTl.iY + rowIndex *
            ( iItemHeight + iGridDetails.iSizeBetweenItems.iHeight ) + iVerticalOffset );
    
    _AKNTRACE_FUNC_EXIT;
    return itemPos;
    }


// ---------------------------------------------------------------------------
// This function has been overloaded to draw items correctly.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknGridView::CalcBottomItemIndex()
    {
    _AKNTRACE_FUNC_ENTER;
    TInt numberOfItems( iModel->NumberOfItems() );
    iBottomItemIndex =
        iTopItemIndex + iGridDetails.iPageSize - 1 + iGridDetails.iColsInView;
    if ( iBottomItemIndex - iGridDetails.iColsInView >= numberOfItems - 1 )
        {
        iBottomItemIndex -= iGridDetails.iColsInView;
        }
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// This function has been overloaded to draw items correctly.
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CAknGridView::CalcNewTopItemIndexSoItemIsVisible(
    TInt aItemIndex ) const
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "[%s] aItemIndex = %d", 
    		   __FUNCTION__, aItemIndex );
    TInt newTopItemIndex = iTopItemIndex;

    if ( aItemIndex != iTopItemIndex )
        {
        if ( IsPrimaryVertical() )
            {
            TInt numOfRowsInView = NumberOfRowsInView();
            TInt colIndexOfTargetItem = aItemIndex / numOfRowsInView;
            TInt numOfColsInView = NumberOfColsInView();
            if ( aItemIndex < iTopItemIndex )
                {
                newTopItemIndex = colIndexOfTargetItem * numOfRowsInView;
                }
            else if ( aItemIndex > iBottomItemIndex )
                {
                TInt colIndexOfNewBottomItem = colIndexOfTargetItem;
                TInt colIndexOfNewTopItem =
                    colIndexOfNewBottomItem - ( numOfColsInView - 1 );
                newTopItemIndex = colIndexOfNewTopItem * numOfRowsInView;
                }
            }
        else
            {
            TInt numOfColsInView = NumberOfColsInView();
            TInt rowIndexOfTargetItem = aItemIndex / numOfColsInView;
            TInt numOfRowsInView = NumberOfRowsInView();
            
			if ( aItemIndex < iTopItemIndex )
                {
                newTopItemIndex = rowIndexOfTargetItem * numOfColsInView;
                }
            else if ( aItemIndex > iBottomItemIndex - numOfColsInView )
                {
                TInt rowIndexOfNewBottomItem = rowIndexOfTargetItem;
                TInt rowIndexOfNewTopItem =
                    rowIndexOfNewBottomItem - ( numOfRowsInView - 1 );
                newTopItemIndex = rowIndexOfNewTopItem * numOfColsInView;
                }
            }
        }

    _AKNTRACE_FUNC_EXIT;
    return newTopItemIndex;
    }


/**
 * This function has been overloaded to draw items correctly.
 */
EXPORT_C void CAknGridView::DrawItemRange( TInt aStartItemIndex,
                                           TInt aEndItemIndex ) const
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "[%s] aStartItemIndex = %d aEndItemIndex = %d", 
    		   __FUNCTION__, aStartItemIndex, aEndItemIndex );
    if ( RedrawDisabled() || iItemHeight == 0 )
        {
        _AKNTRACE_FUNC_EXIT;
        return;
        }

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    MAknListBoxTfxInternal* transApi = CAknListLoader::TfxApiInternal( iGc );
#endif
    // Clear the unused portion of the viewing area.
    DrawUnusedViewPortion();

    for ( TInt i = aStartItemIndex; i <= aEndItemIndex; i++ )
        {
        if ( ItemExists( i ) )
            {
            DrawItem( i );
            }
        else
            {
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
            if ( transApi )
                {
                transApi->StartDrawing( MAknListBoxTfxInternal::EListView );
                }
#endif
            ClearUnusedItemSpace( i, aEndItemIndex );
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
            if ( transApi )
                {
                transApi->StopDrawing();
                }
#endif
            break;
            }
        }

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    if ( transApi )
        {
        transApi->StartDrawing( MAknListBoxTfxInternal::EListView );
        }
#endif


#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    if ( transApi )
        {
        transApi->StopDrawing();
        }
#endif
    _AKNTRACE_FUNC_EXIT;
	}

/**
 * This function may be overloaded to detail an empty grid as required.
 */
EXPORT_C void CAknGridView::DrawEmptyList() const
	{
	_AKNTRACE_FUNC_ENTER;
	iGc->SetClippingRect(iViewRect);
	iItemDrawer->ClearRect(iViewRect);

	if (EmptyListText())
		{
		// display empty grid message
		CFormattedCellListBoxItemDrawer *id = (CFormattedCellListBoxItemDrawer*)ItemDrawer();
		AknDrawWithSkins::DrawEmptyList(iViewRect, *iGc, *EmptyListText(), id->FormattedCellData()->Control());
		}
	iGc->CancelClippingRect();
	_AKNTRACE_FUNC_EXIT;
	}

/**
 * Grid initialisation function. Should only be called by SetLayoutL of
 * grid box.
 */
EXPORT_C void CAknGridView::SetGridDetails(SGrid aGridDetails)
	{
	SGrid details = aGridDetails;

	if (details.iSizeBetweenItems.iHeight < 0)
		{
		details.iSizeBetweenItems.iHeight = 0;
		}
	if (details.iSizeBetweenItems.iWidth < 0)
		{
		details.iSizeBetweenItems.iWidth = 0;
		}

	iGridDetails = details;
	}


// ---------------------------------------------------------------------------
// This set the current item index and moves the highlight to the specified
// item index and and scrolls the grid if necessary.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknGridView::MoveToItemIndexL( TInt aItemIndex,
                                              TSelectionMode aSelectionMode )
	{
	_AKNTRACE_FUNC_ENTER;
	if ( !ItemExists( aItemIndex ) )
	    {
	    _AKNTRACE_FUNC_EXIT;
		return; // nothing to do
	    }
	_AKNTRACE( "[%s] aItemIndex = %d TSelectionMode = %d", 
			   __FUNCTION__, aItemIndex, aSelectionMode );
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    MAknListBoxTfxInternal* transApi = CAknListLoader::TfxApiInternal( iGc );
    if ( transApi )
        {
        transApi->SetMoveType( MAknListBoxTfxInternal::EListStartUnknownMove );
        }
#endif // RD_UI_TRANSITION_EFFECTS_LIST
    
    TInt oldItemIndex = iCurrentItemIndex;
    
    if ( !ScrollToMakeItemVisible( aItemIndex ) )
        {
        if ( ItemIsPartiallyVisible( aItemIndex ) )
            {
            // ScrollToMakeItemVisible doesn't scroll the view for
            // partial items, so for key events the scrolling is done here.
            
            TInt amountToScroll =
                CalculateHScrollOffsetSoItemIsVisible( aItemIndex );
        
            iHScrollOffset += amountToScroll;        
            iCurrentItemIndex = aItemIndex;
            
            if ( iExtension && !iExtension->iScrollingDisabled )
                {
                CFormattedCellListBoxItemDrawer* itemDrawer =
                    static_cast<CFormattedCellListBoxItemDrawer*>( iItemDrawer );
                CEikListBox* listBox =
                    static_cast<CEikListBox*>(
                        itemDrawer->FormattedCellData()->Control() );
                listBox->HandlePhysicsScrollEventL(
                    amountToScroll * iItemHeight + ItemOffsetInPixels() );
                }
            else
                {
                // Do normal scrolling if physics are not enabled.
                VScrollTo( CalcNewTopItemIndexSoItemIsVisible( aItemIndex ) );
                }
            }
        else
            {
            // View was not scrolled, so item is already visible.
            iCurrentItemIndex = aItemIndex;
            DrawItem( oldItemIndex );
            }
        }

	UpdateSelectionL( aSelectionMode ); // this draws iCurrentItemIndex

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    if ( transApi )
        {
        transApi->SetMoveType( MAknListBoxTfxInternal::EListStopUnknownMove );
        }
#endif // RD_UI_TRANSITION_EFFECTS_LIST
    _AKNTRACE_FUNC_EXIT;
	}


// ---------------------------------------------------------------------------
// Returns the number of visible columns.
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CAknGridView::NumberOfColsInView() const
	{
	__ASSERT_ALWAYS( ( iGridDetails.iColsInView > 0 ),
	                 Panic( EAknPanicGridViewInvalidNumberOfColumns ) );
	return iGridDetails.iColsInView;
	}


// ---------------------------------------------------------------------------
// Returns the number of visible rows.
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CAknGridView::NumberOfRowsInView() const
	{
	__ASSERT_ALWAYS( ( iGridDetails.iRowsInView > 0 ),
	                 Panic( EAknPanicGridViewInvalidNumberOfRows ) );
	TInt rows = iGridDetails.iRowsInView;

	return rows;
	}


void CAknGridView::MoveCursorWithRepeatsL( 
        TBool aNextOrPrev, TSelectionMode aSelectionMode, TInt aAmount )
    {  
    _AKNTRACE_FUNC_ENTER;
    TBool singleColumn = EFalse;
    if ( IsPrimaryVertical() )
        {
        singleColumn = iGridDetails.iGridDimensions.iHeight < 2;
        }
    else
        {
        singleColumn = iGridDetails.iGridDimensions.iWidth < 2;
        }
    
    TCursorMovement cursorMovement;
    if ( aNextOrPrev )
        {
        cursorMovement = CListBoxView::ECursorNextColumn;
        if ( singleColumn )
            {
            cursorMovement = CListBoxView::ECursorNextItem;
            }
        }
    else
        {
        cursorMovement = CListBoxView::ECursorPreviousColumn;
        if ( singleColumn )
            {
            cursorMovement = CListBoxView::ECursorPreviousItem;
            }
        }
        
    TInt step = aAmount;   
    if ( !singleColumn )
        {
        // Stop looping in grids. Looping is still allowed in list like grid.
        TInt maxIndex = GridModel()->NumberOfData() - 1;
        TInt dataIndex = CurrentDataIndex();        
        TBool isToTail = iGridDetails.iGridFlags & ELeftToRight ?
            aNextOrPrev : !aNextOrPrev;

        if ( dataIndex + step > maxIndex && isToTail )
            {
            step = maxIndex - dataIndex;
            }

        if ( dataIndex < step && !isToTail )
            {
            step = dataIndex;
            }
        }
    
    for ( TInt ii = 0; ii < step; ii++ )
        {
        MoveCursorL( cursorMovement, aSelectionMode );
        }  
    _AKNTRACE_FUNC_EXIT;
    }

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
// -----------------------------------------------------------------------------
// LISTBOX EFFECTS IMPLEMENTATION
// 
// Sets movement type in the transition controller
//
// This function is called from DoMoveL before MoveToItemIndexL is called.
// -----------------------------------------------------------------------------
//
void SetMoveType( CWindowGc* aGc,
                  CAknGridView::TCursorMovement aCursorMovement )
    {
    MAknListBoxTfxInternal* api = CAknListLoader::TfxApiInternal( aGc );
    if ( api )
	    {
	    if ( aCursorMovement == CAknGridView::ECursorNextColumn)
	        {
            api->SetMoveType( MAknListBoxTfxInternal::EListMoveRight );
	        }
	    else if ( aCursorMovement == CAknGridView::ECursorNextItem )
	        {
            api->SetMoveType( MAknListBoxTfxInternal::EListMoveDown );
	        }
	    else if ( aCursorMovement == CAknGridView::ECursorPreviousItem )
	        {
            api->SetMoveType( MAknListBoxTfxInternal::EListMoveUp );
	        }
	    else if ( aCursorMovement == CAknGridView::ECursorPreviousColumn )
	        {
            api->SetMoveType( MAknListBoxTfxInternal::EListMoveLeft );
	            }
	        else
	            {
            api->SetMoveType( MAknListBoxTfxInternal::EListNoMovement );
	            }
	        }
    }
#endif //RD_UI_TRANSITION_EFFECTS_LIST

EXPORT_C void CAknGridView::DoMoveL(TCursorMovement aCursorMovement, TSelectionMode aSelectionMode)
	{
	_AKNTRACE_FUNC_ENTER;
	TInt rowIndex = 0;
	TInt colIndex = 0;
	LogicalPosFromListBoxIndex(iCurrentItemIndex, rowIndex, colIndex);

	TBool moveDown = IsMoveDown(aCursorMovement);
	TBool moveRight = IsMoveRight(aCursorMovement);

	TInt newIndex = 0;
	TScrollingType scrollingType = EScrollStops;
	TBool moveIsVert = (aCursorMovement==ECursorNextItem)||(aCursorMovement==ECursorPreviousItem);
	TBool moveInPrim = COMPARE_BOOLS(IsPrimaryVertical(),(moveIsVert));
	if (moveInPrim)
		scrollingType = iScrollingType;
	else
		scrollingType = iScrollInSecondaryDimension;

	switch(scrollingType)
		{
		case EScrollStops: // drop through
		case EScrollFollowsGrid: // drop through
		case EScrollFollowsItemsAndStops: // drop through
		case EScrollFollowsItemsAndLoops:
			newIndex = SearchByLines(colIndex, rowIndex, aCursorMovement);
			break;
		case EScrollIncrementLineAndStops: // drop through
		case EScrollIncrementLineAndLoops:
			{
			TBool edgePassed = IsEdgePassed(iCurrentItemIndex, moveDown, moveRight, !moveIsVert, EFalse, newIndex);
			if (!moveInPrim && edgePassed && (newIndex >=0))
				{// special scroll
				TBool specialMoveNeeded = EFalse;
				LogicalPosFromListBoxIndex(newIndex, rowIndex, colIndex);
				if (moveIsVert)
					if ((rowIndex != 0) && (rowIndex != iGridDetails.iGridDimensions.iHeight - 1))
						specialMoveNeeded = ETrue;
				else
					if ((colIndex != 0) && (colIndex != iGridDetails.iGridDimensions.iWidth - 1))
						specialMoveNeeded = ETrue;
				if (specialMoveNeeded)
					{// fake being at the far edge of the grid
					if (moveRight)
						colIndex = 0;
					else
						colIndex = iGridDetails.iGridDimensions.iWidth - 1;

					if (moveDown)
						rowIndex = 0;
					else
						rowIndex = iGridDetails.iGridDimensions.iHeight - 1;

					TInt newIndex2 = 0; // fake index
					ListBoxIndexFromLogicalPos(newIndex2, rowIndex, colIndex);
					iTopItemIndex = CalcNewTopItemIndexSoItemIsVisible(newIndex2);
					CalcBottomItemIndex();
					iCurrentItemIndex = newIndex; // set current to actual index we want to move to
					iHScrollOffset += CalculateHScrollOffsetSoItemIsVisible(newIndex);
					DrawItemRange(iTopItemIndex, iBottomItemIndex); // draw range for fake index
					if (ItemIsVisible(newIndex))
						return; // moved and drawn
					// need to scroll some more to make the newIndex visable
					}
				}
			}
			break;
		default:
			break;
		}
	
	if (newIndex >=0)
		{ // found next item to move to
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
            SetMoveType( iGc, aCursorMovement );
#endif //RD_UI_TRANSITION_EFFECTS_LIST
		MoveToItemIndexL(newIndex, aSelectionMode);
		_AKNTRACE_FUNC_EXIT;
		return;
		}

	TInt oldRowIndex = rowIndex;
	TInt oldColIndex = colIndex;
	if (moveRight)
		colIndex = 0;
	else
		colIndex = iGridDetails.iGridDimensions.iWidth - 1;

	if (moveDown)
		rowIndex = 0;
	else
		rowIndex = iGridDetails.iGridDimensions.iHeight - 1;

	switch(scrollingType)
		{// we are at an edge
		case EScrollStops:
			{
			_AKNTRACE_FUNC_EXIT;
			return; // easy
			}
		case EScrollFollowsGrid:
			newIndex = SearchByLines((moveIsVert ? oldColIndex : colIndex),(moveIsVert ? rowIndex : oldRowIndex), aCursorMovement, ETrue);
			break;
		case EScrollFollowsItemsAndStops:
		case EScrollFollowsItemsAndLoops:
			newIndex = FindNextItem(iCurrentItemIndex, moveDown, moveRight, !IsPrimaryVertical());
			if (moveInPrim)
				{// move in the primary direction of the grid
				if (newIndex >=0)
					{ // found next item to move to
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
                        SetMoveType( iGc, aCursorMovement );
#endif //RD_UI_TRANSITION_EFFECTS_LIST
					MoveToItemIndexL(newIndex, aSelectionMode);
					_AKNTRACE_FUNC_EXIT;
					return;
					}
				// did not find anything
				if (iScrollingType == EScrollFollowsItemsAndStops)
					{
					_AKNTRACE_FUNC_EXIT;
					return; // do nothing
					}

				// then must be EScrollFollowsItemsAndLoops
				ListBoxIndexFromLogicalPos(newIndex, rowIndex, colIndex);
				newIndex = FindNextItem(newIndex, moveDown, moveRight, !moveIsVert, ETrue);
				}
			else
				{// move in scondary
				if (newIndex < 0)
					{ // no more items
					if (iScrollInSecondaryDimension == EScrollFollowsItemsAndStops)
						{
						_AKNTRACE_FUNC_EXIT;
						return;
						}
					//must be EScrollFollowsItemsAndLoops
					}
				else
					{ // some more items before the end
					if (moveIsVert)
						{
						if (moveRight)
							colIndex = oldColIndex + 1;
						else
							colIndex = oldColIndex - 1;
						}
					else
						{
						if (moveDown)
							rowIndex = oldRowIndex + 1;
						else
							rowIndex = oldRowIndex - 1;
						}
					}
				newIndex = SearchByLines(colIndex, rowIndex, aCursorMovement, ETrue);
				}
			break;
		case EScrollIncrementLineAndStops:
			_AKNTRACE_FUNC_EXIT;
			return; // do nothing
		case EScrollIncrementLineAndLoops:
			{
			ListBoxIndexFromLogicalPos(newIndex, rowIndex, colIndex);
			newIndex = FindNextItem(newIndex, moveDown, moveRight, !moveIsVert, ETrue);
			if (!moveInPrim && newIndex >=0)
				{// may need to have a special scroll
				TBool specialMoveNeeded = EFalse;
				LogicalPosFromListBoxIndex(newIndex, rowIndex, colIndex);
				if (moveIsVert)
					if ((rowIndex != 0) && (rowIndex != iGridDetails.iGridDimensions.iHeight - 1))
						specialMoveNeeded = ETrue;
				else
					if ((colIndex != 0) && (colIndex != iGridDetails.iGridDimensions.iWidth - 1))
						specialMoveNeeded = ETrue;
				if (specialMoveNeeded)
					{// first fake being at the far edge of the grid
					if (moveRight)
						colIndex = 0;
					else
						colIndex = iGridDetails.iGridDimensions.iWidth - 1;

					if (moveDown)
						rowIndex = 0;
					else
						rowIndex = iGridDetails.iGridDimensions.iHeight - 1;

					TInt newIndex2 = 0; // fake index
					ListBoxIndexFromLogicalPos(newIndex2, rowIndex, colIndex);
					iTopItemIndex = CalcNewTopItemIndexSoItemIsVisible(newIndex2);
					CalcBottomItemIndex();
					iCurrentItemIndex = newIndex; // set current to actual index we want to move to
					iHScrollOffset += CalculateHScrollOffsetSoItemIsVisible(newIndex);
					DrawItemRange(iTopItemIndex, iBottomItemIndex); // draw range for fake index
					if (ItemIsVisible(newIndex))
						{
						_AKNTRACE_FUNC_EXIT;
						return; // moved and drawn
						}
					// need to scroll some more to make the newIndex visable
					}
				}
			}
			break;
		default:
			break; // should never get here
		}

	if (newIndex >=0)
		{ // found next item to move to
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
            SetMoveType( iGc, aCursorMovement );
#endif //RD_UI_TRANSITION_EFFECTS_LIST
		MoveToItemIndexL(newIndex, aSelectionMode);
		}
	_AKNTRACE_FUNC_EXIT;
	}

/**
 * Used with grids which contain empty items
 * returns the new listbox index of the next item
 * returns -1 if there is nothing to move to.
 */
EXPORT_C TInt CAknGridView::SearchByLines(TInt aX, TInt aY, TCursorMovement aCursorMovement, TBool aBeginSearchOnIndex)
	{
	_AKNTRACE_FUNC_ENTER;
	TInt xMax = iGridDetails.iGridDimensions.iWidth;
	TInt yMax = iGridDetails.iGridDimensions.iHeight;

	TInt xIteration = 0;
	TInt yIteration = 0;
	switch(aCursorMovement)
		{
		case ECursorNextColumn:
				xIteration = 1;
			break;
		case ECursorPreviousColumn:
				xIteration = -1;
			break;
		case ECursorNextItem:
				yIteration = 1;
			break;
		case ECursorPreviousItem:
				yIteration = -1;
			break;
		default:
			break;
		}
	// set up first for a Horizontal grid
	TInt primaryIteration = xIteration;
	TInt secondaryIteration = yIteration;
	TInt primaryMax = xMax;
	TInt secondaryMax = yMax;
	TInt p = aX;
	TInt s = aY;
	// now change variables if it is a Vertical grid
	if (IsPrimaryVertical())
		{
		primaryIteration = yIteration;
		secondaryIteration = xIteration;
		primaryMax = yMax;
		secondaryMax = xMax;
		p = aY;
		s = aX;
		}

	if (!aBeginSearchOnIndex)
		s += secondaryIteration;

	TInt index = 0;
	for ( ; (s < secondaryMax) && (s >= 0) ; s += secondaryIteration)
		{
		for (TInt primaryOffset = 0;(p - primaryOffset >= 0) || (p + primaryOffset < primaryMax) ; primaryOffset++)
			{
			TInt x = 0;
			TInt y = 0;
			if (secondaryIteration == 0)
				{// then we are moving in the primary orientation of the grid 
				 // so just find the next item in this direction.
				TInt offSet = (aBeginSearchOnIndex ? primaryOffset : primaryOffset+1);
				x = p + (primaryIteration * (offSet));
				if (x < 0 || x >= primaryMax)
					break;
				y = s;
				if (IsPrimaryVertical())
					{//swap them
					y = x;
					x = s;
					}
				DataIndexFromLogicalPos(index,y,x);
				if (GridModel()->IndexContainsData(index))
					{
					_AKNTRACE_FUNC_EXIT;
					return ListBoxIndex(index);
					}
				}
			else
				{
				TInt newOffset = p+(primaryOffset);
				if ((newOffset >= 0) && (newOffset < primaryMax))
					{
					x = newOffset;
					y = s;
					if (IsPrimaryVertical())
						{
						x = s;
						y = newOffset;
						}
					DataIndexFromLogicalPos(index,y,x);
					if (GridModel()->IndexContainsData(index))
						{
						_AKNTRACE_FUNC_EXIT;
						return ListBoxIndex(index);
						}
					}
				newOffset = p-(primaryOffset);
				if ((newOffset >= 0) && (newOffset < primaryMax))
					{
					x = newOffset;
					y = s;
					if (IsPrimaryVertical())
						{
						x = s;
						y = newOffset;
						}
					DataIndexFromLogicalPos(index,y,x);
					if (GridModel()->IndexContainsData(index))
						{
						_AKNTRACE_FUNC_EXIT;
						return ListBoxIndex(index);
						}
					}
				}
			}
		if (secondaryIteration == 0)
			{// no more items
			_AKNTRACE_FUNC_EXIT;
			return -1;
			}
		}
	_AKNTRACE_FUNC_EXIT;
	// no more items
	return -1;
	}

EXPORT_C TInt CAknGridView::FindNextItem(TInt aItemIndex, TBool aLookDown, TBool aLookRight, TBool aFirstLookHorizontal, TBool aBeginSearchOnIndex)
	{
	TInt newIndex = 0;
	IsEdgePassed(aItemIndex, aLookDown, aLookRight, aFirstLookHorizontal, aBeginSearchOnIndex, newIndex);
	return newIndex;
	}

TBool CAknGridView::IsEdgePassed(TInt aItemIndex, TBool aLookDown, TBool aLookRight, TBool aFirstLookHorizontal, TBool aBeginSearchOnIndex, TInt& aNewIndex)
	{
	_AKNTRACE_FUNC_ENTER;
	TInt rowIndex = 0;
	TInt colIndex = 0;

	LogicalPosFromListBoxIndex(aItemIndex, rowIndex, colIndex);

	TInt x = 0;
	TInt y = 0;
	TBool edgePassed = EFalse;

	CAknGridM* gridModel = GridModel();
	TInt newDataIndex = -1;
	if (aFirstLookHorizontal)
		{
		x = (aBeginSearchOnIndex ? colIndex : (aLookRight ? colIndex + 1 : colIndex - 1));
		for (y = rowIndex; (y>=0) && (y < iGridDetails.iGridDimensions.iHeight); y = (aLookDown ? y+1 : y-1))
			{
			for ( ; (x>=0) && (x<iGridDetails.iGridDimensions.iWidth); x = (aLookRight ? x+1 : x-1))
				{
				DataIndexFromLogicalPos(newDataIndex,y,x);
				if (gridModel->IndexContainsData(newDataIndex))
					{
					aNewIndex = ListBoxIndex(newDataIndex);
					_AKNTRACE_FUNC_EXIT;
					return edgePassed;
					}
				}
			edgePassed = ETrue;
			if (aLookRight)
				x = 0;
			else
				x = iGridDetails.iGridDimensions.iWidth - 1;
			}
		}
	else
		{
		y = (aBeginSearchOnIndex ? rowIndex : (aLookDown ? rowIndex + 1 : rowIndex - 1));
		for (x = colIndex; (x>=0) && (x < iGridDetails.iGridDimensions.iWidth); x = (aLookRight ? x+1 : x-1))
			{
			for ( ; (y>=0) && (y<iGridDetails.iGridDimensions.iHeight); y = (aLookDown ? y+1 : y-1))
				{
				DataIndexFromLogicalPos(newDataIndex,y,x);
				if (gridModel->IndexContainsData(newDataIndex))
					{
					aNewIndex = ListBoxIndex(newDataIndex);
					_AKNTRACE_FUNC_EXIT;
					return edgePassed;
					}
				}
			edgePassed = ETrue;
			if (aLookDown)
				y = 0;
			else
				y = iGridDetails.iGridDimensions.iHeight - 1;
			}
		}

	aNewIndex = -1;
	_AKNTRACE_FUNC_EXIT;
	return edgePassed;
	}


TBool CAknGridView::IsMoveRight(TCursorMovement aCursorMovement)
	{
	_AKNTRACE_FUNC_ENTER;
	TBool moveRight = EFalse;
	switch(aCursorMovement)
		{
		case ECursorNextItem:
			moveRight = COMPARE_BOOLS((iGridDetails.iGridFlags & ETopToBottom),(iGridDetails.iGridFlags & ELeftToRight));
			break;
		case ECursorPreviousItem:
			moveRight = !COMPARE_BOOLS((iGridDetails.iGridFlags & ETopToBottom),(iGridDetails.iGridFlags & ELeftToRight));
			break;
		case ECursorNextColumn:
			moveRight = ETrue;
			break;
		case ECursorPreviousColumn:
			moveRight = EFalse;
			break;
		default:
			break;
		}
	_AKNTRACE_FUNC_EXIT;
	return moveRight;
	}

TBool CAknGridView::IsMoveDown(TCursorMovement aCursorMovement)
	{
	_AKNTRACE_FUNC_ENTER;
	TBool moveDown = EFalse;
	switch(aCursorMovement)
		{
		case ECursorNextItem:
			moveDown = ETrue;
			break;
		case ECursorPreviousItem:
			moveDown = EFalse;
			break;
		case ECursorNextColumn:
			moveDown = COMPARE_BOOLS((iGridDetails.iGridFlags & ETopToBottom),(iGridDetails.iGridFlags & ELeftToRight));
			break;
		case ECursorPreviousColumn:
			moveDown = !COMPARE_BOOLS((iGridDetails.iGridFlags & ETopToBottom),(iGridDetails.iGridFlags & ELeftToRight));
			break;
		default:
			break;
		}
	_AKNTRACE_FUNC_EXIT;
	return moveDown;
	}


/**
 * Overloaded MoveCursorL method to process cursor movement according to
 * orientation of the grid.
 */
EXPORT_C void CAknGridView::MoveCursorL(TCursorMovement aCursorMovement, TSelectionMode aSelectionMode)
	{ 
	_AKNTRACE_FUNC_ENTER;
	// This is driving method for all movement around the grid

	// check that actually some data in the grid
	if (GridModel()->NumberOfData() == 0)
		{
		_AKNTRACE_FUNC_EXIT;
		return;
		}

#if defined(_DEBUG)
	switch (aCursorMovement)
		{
		// page movements
		case ECursorFirstItem: // go back first index
			MoveToItemIndexL(0, aSelectionMode);
			_AKNTRACE_FUNC_EXIT;
			return;
		case ECursorLastItem: // go to last index
			MoveToItemIndexL(GridModel()->IndexOfLastDataItem(), aSelectionMode);
			_AKNTRACE_FUNC_EXIT;
			return;
		case ECursorNextPage: 
			MoveToItemIndexL((iCurrentItemIndex+iGridDetails.iPageSize < GridModel()->NumberOfData() ? iCurrentItemIndex+iGridDetails.iPageSize : GridModel()->NumberOfData() - 1), aSelectionMode);
			_AKNTRACE_FUNC_EXIT;
			return;
		case ECursorPreviousPage: 
			MoveToItemIndexL((iCurrentItemIndex-iGridDetails.iPageSize >= 0 ? iCurrentItemIndex-iGridDetails.iPageSize : 0 ), aSelectionMode);
			_AKNTRACE_FUNC_EXIT;
			return;
		default: 
			break;
		}
#endif
	// perform movement required
	DoMoveL(aCursorMovement, aSelectionMode);
	_AKNTRACE_FUNC_EXIT;
	}

/**
 * Sets the width of the grid column. This should only be called via
 * the selection box class's SetColumnWidth method.
 */
EXPORT_C void CAknGridView::SetColumnWidth(TInt aColumnWidth)
	{
	__ASSERT_ALWAYS((aColumnWidth > 0), Panic(EAknPanicGridViewInvalidItemWidth));

	_AKNTRACE( " [%s] aColumnWidth = %d", 
			   __FUNCTION__, aColumnWidth );
	iGridDetails.iSizeOfItems.iWidth = aColumnWidth;

	iItemDrawer->SetItemCellSize(ItemSize());
	}

/////////////////////////////////////////////////
//////////////////////////////////////////////////

EXPORT_C void CAknGridView::SetTopItemIndex(TInt aNewTopItemIndex)
	{
	_AKNTRACE( "[%s] aNewTopItemIndex = %d", 
			   __FUNCTION__, aNewTopItemIndex );
	if (iViewRect.Height() == 0)
		return;
	CListBoxView::SetTopItemIndex(aNewTopItemIndex);
	UpdateHScrollOffsetBasedOnTopItemIndex();
	}

EXPORT_C void CAknGridView::SetItemHeight(TInt aItemHeight)
	{
	_AKNTRACE( "[%s] aItemHeight = %d", 
			   __FUNCTION__, aItemHeight );
	CListBoxView::SetItemHeight(aItemHeight);
	iGridDetails.iSizeOfItems.iHeight = aItemHeight;
	CalcBottomItemIndex();
	UpdateHScrollOffsetBasedOnTopItemIndex();
	}


// ---------------------------------------------------------------------------
// Returns ETrue and sets aItemIndex to the index of the item whose
// bounding box contains aPosition, or EFalse if no such item exists. 
// ---------------------------------------------------------------------------
//
EXPORT_C TBool CAknGridView::XYPosToItemIndex( TPoint aPosition,
                                               TInt& aItemIndex ) const
	{
	_AKNTRACE_FUNC_ENTER;
	TBool itemFound = EFalse;

	if ( ColumnWidth() == 0 || iItemHeight == 0 )
	    {
		return EFalse;
	    }

	if ( iViewRect.Contains( aPosition ) )
		{
		// aPosition is inside the display area
		TInt yOffsetFromViewRectOrigin = aPosition.iY - iViewRect.iTl.iY - iVerticalOffset;
		TInt xOffsetFromViewRectOrigin = aPosition.iX - iViewRect.iTl.iX;
		TInt xItemPlusGap = ColumnWidth() + iGridDetails.iSizeBetweenItems.iWidth;
		TInt yItemPlusGap = iItemHeight + iGridDetails.iSizeBetweenItems.iHeight;
		TInt colIndex = xOffsetFromViewRectOrigin / xItemPlusGap;
		TInt rowIndex = yOffsetFromViewRectOrigin / yItemPlusGap;
		TInt numberOfRowsInView = NumberOfRowsInView();
		
		if ( yOffsetFromViewRectOrigin < 0 )
		    {
		    rowIndex = -1;
		    }
		else if ( yOffsetFromViewRectOrigin > iViewRect.Height() )
		    {
            // Ensure it will not go out of boundary...
		    rowIndex = Min( rowIndex, numberOfRowsInView);
		    }
		
        // If column or row is bigger than there are in view,
        // then item is not found.
        if ( colIndex >= NumberOfColsInView() ||
             rowIndex > numberOfRowsInView ||
             colIndex < 0 ||
             rowIndex < -1 )
            {
            itemFound = EFalse;
            }
        else
            {
            // Need to take into account the gaps.
            TInt yItemOffset = yOffsetFromViewRectOrigin % yItemPlusGap;
            TInt xItemOffset = xOffsetFromViewRectOrigin % xItemPlusGap;
            if ( yItemOffset > iItemHeight || xItemOffset > ColumnWidth() )
                {
                _AKNTRACE_FUNC_EXIT;
                return EFalse;
                }

            // Now work out the item index given that we know which
            // row and column it is in.
            TInt itemIndex;
            CalcItemIndexFromRowAndColIndexes( itemIndex,
                                               rowIndex,
                                               colIndex );

            // Error correction that becomes tapping partially
            // filled colour selection grid.
            if ( ItemExists( itemIndex ) &&
                 GridModel()->IndexContainsData( ActualDataIndex( itemIndex ) ) )
                {
                aItemIndex = itemIndex;
                itemFound = ETrue;
                }
            }
        }

	_AKNTRACE_FUNC_EXIT;
    return itemFound;
    }


EXPORT_C void CAknGridView::CalcDataWidth() 
	{
	iDataWidth = iGridDetails.iGridDimensions.iWidth;
	}

EXPORT_C TInt CAknGridView::VisibleWidth(const TRect& aRect) const
	{
	return aRect.Width() / ColumnWidth();
	}


// ---------------------------------------------------------------------------
// Scrolls the view so that the item with the given index becomes visible
// if it's currently outside of the view rectangle.
// ---------------------------------------------------------------------------
//
EXPORT_C TBool CAknGridView::ScrollToMakeItemVisible( TInt aItemIndex )
	{
	_AKNTRACE_FUNC_ENTER;
	_AKNTRACE( "[%s] aItemIndex = %d", 
			   __FUNCTION__, aItemIndex );
	if ( iViewRect.Height() == 0 || iItemHeight == 0 )
	    {
	    _AKNTRACE_FUNC_EXIT;
	    return EFalse;
	    }
	
    const TBool redrawDisabled = RedrawDisabled();
    TPoint itemPosition( ItemPos( aItemIndex ) );
    TBool itemPartiallyVisible = ItemIsPartiallyVisible( aItemIndex );

    if ( itemPartiallyVisible || ItemIsVisible( aItemIndex ) )
        {
        _AKNTRACE_FUNC_EXIT;
        // Item is already visible, so no scrolling required.
        return EFalse;
        }
    
    // Item is partially visible or not visible.

	HideMatcherCursor();
	TInt amountToScroll = CalculateHScrollOffsetSoItemIsVisible( aItemIndex );

	if ( amountToScroll == 0 && !itemPartiallyVisible )
	    {
	    _AKNTRACE_FUNC_EXIT;
		return EFalse;
	    }

	iHScrollOffset += amountToScroll;
	TBool gridVertical = IsPrimaryVertical();

	// assume horizontal
	TInt numOfLinesInViewOrientated = gridVertical ? NumberOfColsInView() :
                                                     NumberOfRowsInView();
	TInt numOfLinesInViewOrthogonal = gridVertical ? NumberOfRowsInView() :
                                                     NumberOfColsInView();

	if ( Abs( amountToScroll ) >= numOfLinesInViewOrientated )
		{ // Entire view content is changed, so don't bother scrolling.
		iTopItemIndex += numOfLinesInViewOrthogonal * amountToScroll;
		CalcBottomItemIndex();
		iCurrentItemIndex = aItemIndex;
		iVerticalOffset = 0;
		
		if ( !redrawDisabled )
		    {
		    Draw();
		    DrawMatcherCursor();
		    }

		_AKNTRACE_FUNC_EXIT;
		return ETrue;
		}

	iCurrentItemIndex = aItemIndex;
	
	if ( iExtension && !iExtension->iScrollingDisabled )
	    {
        CFormattedCellListBoxItemDrawer* itemDrawer =
            static_cast<CFormattedCellListBoxItemDrawer*>( iItemDrawer );
        CEikListBox* listBox =
            static_cast<CEikListBox*>(
                itemDrawer->FormattedCellData()->Control() );
        TRAP_IGNORE( listBox->HandlePhysicsScrollEventL(
                         amountToScroll * iItemHeight + ItemOffsetInPixels() ) );
	    }
    else
        {
        // Do normal scrolling if physics are not enabled.
        VScrollTo( CalcNewTopItemIndexSoItemIsVisible( aItemIndex ) );
        }
	
	_AKNTRACE_FUNC_EXIT;
	return ETrue;
	}


//////////////////////////////////////////////////
EXPORT_C TInt CAknGridView::CalculateHScrollOffsetSoItemIsVisible(TInt aItemIndex) 
	{
	_AKNTRACE_FUNC_ENTER;
	_AKNTRACE( "[%s] aItemIndex = %d", 
			   __FUNCTION__, aItemIndex );
	// returns the number of cols or rows that we need to scroll, 0 if no scrolling is needed
	TInt newTopItemIndex = CalcNewTopItemIndexSoItemIsVisible(aItemIndex);
	TInt numToScroll = 0;
	if (IsPrimaryVertical())
		{
		TInt numOfRowsInView = NumberOfRowsInView();
		TInt oldHScrollOffset = iHScrollOffset;
		TInt newHScrollOffset = newTopItemIndex / numOfRowsInView;
		numToScroll = newHScrollOffset - oldHScrollOffset;
		}
	else
		{
		TInt logicalRow = 0;
		TInt logicalCol = 0;
		LogicalPosFromListBoxIndex(iTopItemIndex, logicalRow, logicalCol);
		TInt oldHScrollOffset = logicalRow;
		LogicalPosFromListBoxIndex(newTopItemIndex, logicalRow, logicalCol);
		TInt newHScrollOffset = logicalRow;
		numToScroll = newHScrollOffset - oldHScrollOffset;
		}
	_AKNTRACE_FUNC_EXIT;
	return numToScroll;
	}

EXPORT_C TSize CAknGridView::ItemSize(TInt /*aItemIndex*/) const
	{
	return TSize(ColumnWidth(), iItemHeight);
	}


EXPORT_C void CAknGridView::CalcRowAndColIndexesFromItemIndex( TInt aItemIndex,
                                                               TInt& aRowIndex,
                                                               TInt& aColIndex ) const
	{
	_AKNTRACE_FUNC_ENTER;
	_AKNTRACE( "[%s] aItemIndex = %d aRowIndex = %d aColIndex = %d", 
			   __FUNCTION__, aItemIndex, aRowIndex, aColIndex );
	// Should panic if iItemHeight or iViewRect.Height() is 0.
	// Assumes specified item is currently visible.
	TInt numOfItemsFromFirstVisibleItem = (aItemIndex - iTopItemIndex);

	if ( IsPrimaryVertical() )
		{
		TInt numOfRowsInView = NumberOfRowsInView();
		aColIndex = numOfItemsFromFirstVisibleItem / numOfRowsInView;
		aRowIndex = numOfItemsFromFirstVisibleItem % numOfRowsInView;
		}
	else
		{
		TInt numOfColsInView = NumberOfColsInView();

		if ( numOfItemsFromFirstVisibleItem < 0 )
            {
            // This is possible the visible topmost row is partially drawn
            // and iTopItemIndex has already moved to the next row.
            // So this handling is required for the top row to be drawn
            // correctly.
            aColIndex = ( numOfItemsFromFirstVisibleItem + numOfColsInView ) % numOfColsInView;
            aRowIndex = -1;
            }
		else
		    {
            aColIndex = numOfItemsFromFirstVisibleItem % numOfColsInView;
            aRowIndex = numOfItemsFromFirstVisibleItem / numOfColsInView;
		    }
		}
	_AKNTRACE_FUNC_EXIT;
	}


// ---------------------------------------------------------------------------
// Calculates the item index that is on the given row and column indices.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknGridView::CalcItemIndexFromRowAndColIndexes( TInt& aItemIndex,
                                                               TInt aRowIndex,
                                                               TInt aColIndex ) const
	{
	_AKNTRACE_FUNC_ENTER;
	_AKNTRACE( "[%s] aItemIndex = %d aRowIndex = %d aColIndex = %d", 
			   __FUNCTION__, aItemIndex, aRowIndex, aColIndex );
	// Row index can be -1 if the row above top item index is partially
	// visible.
	__ASSERT_DEBUG( aRowIndex >= -1, Panic( EAknPanicGridViewInvalidRowIndex ) );
	__ASSERT_DEBUG( aColIndex >= 0, Panic( EAknPanicGridViewInvalidColumnIndex ) );

	// Should panic if iItemHeight is 0.
	if ( IsPrimaryVertical() )
		{
		TInt numOfRowsInView = NumberOfRowsInView();
		aItemIndex = iTopItemIndex + ((aColIndex * numOfRowsInView) + aRowIndex); 
		}
	else
		{
		TInt numOfColsInView = NumberOfColsInView();
		aItemIndex = iTopItemIndex + ((aRowIndex * numOfColsInView) + aColIndex); 
		}
	_AKNTRACE_FUNC_EXIT;
	}


EXPORT_C void CAknGridView::DrawMatcherCursor()
	{
	}

// ---------------------------------------------------------------------------
// Returns the item index of the currently highlighted item.
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CAknGridView::CurrentItemIndex() const
	{
	if ( ItemExists( iCurrentItemIndex ) )
	    {
		return iCurrentItemIndex;
	    }
	else
	    {
	    // Means there is no current item.
		return KErrNotFound;
	    }
	}
	
////////////////////////////////// protect

// ---------------------------------------------------------------------------
// Draws a range of columns.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknGridView::DrawColumnRange( TInt aStartColIndex,
                                             TInt aEndColIndex ) const
	{
	_AKNTRACE_FUNC_ENTER;
	if ( !RedrawDisabled() && iItemHeight > 0 )
	    {
        TInt numOfRowsInView = NumberOfRowsInView();
        TInt startItemIndex = aStartColIndex * numOfRowsInView;
        TInt endItemIndex = aEndColIndex * numOfRowsInView + numOfRowsInView - 1;
        DrawItemRange( startItemIndex, endItemIndex );
	    }
	_AKNTRACE_FUNC_EXIT;
	}


EXPORT_C void CAknGridView::ClearUnusedItemSpace(TInt aStartItemIndex, TInt aEndItemIndex) const
	{
	_AKNTRACE_FUNC_ENTER;
	TRect blankRect;
	for (TInt i = aStartItemIndex; i <= aEndItemIndex; i++)
		{
		blankRect.SetRect(ItemPos(i), ItemSize());
		blankRect.Intersection(iViewRect);

		MAknsSkinInstance *skin = AknsUtils::SkinInstance();
		CFormattedCellListBoxItemDrawer *id = (CFormattedCellListBoxItemDrawer*)ItemDrawer();
		if (id->FormattedCellData()->Control())
			{
			MAknsControlContext *cc = AknsDrawUtils::ControlContext( id->FormattedCellData()->Control() );
			if ( !cc )
			    {
			    cc = id->FormattedCellData()->SkinBackgroundContext();
			    }
			AknsDrawUtils::Background( skin, cc, id->FormattedCellData()->Control(), *iGc, blankRect );
			}
		else
			{
			iGc->Clear(blankRect);
			}
		}
	_AKNTRACE_FUNC_EXIT;
	}

EXPORT_C void CAknGridView::UpdateHScrollOffsetBasedOnTopItemIndex()
	{
	TInt numOfRowsInView = iGridDetails.iRowsInView;
	if (numOfRowsInView > 0)
		iHScrollOffset = iTopItemIndex / numOfRowsInView;
	}


EXPORT_C TAny* CAknGridView::Reserved_1()
	{
	return NULL;
	}


// ---------------------------------------------------------------------------
// Draws the part of the view rectangle in which no items are drawn.  
// ---------------------------------------------------------------------------
//
void CAknGridView::DrawUnusedViewPortion() const
    {
    _AKNTRACE_FUNC_ENTER;
    TInt gapWidth = iGridDetails.iSizeBetweenItems.iWidth;
    TInt numberOfCols  = iGridDetails.iColsInView;
    TInt usedViewRectPortionWidth = 
                numberOfCols * ( ColumnWidth() + gapWidth ) - gapWidth;
    TRect itemUsedRect;
    //if the gapWidth > 0, the entire background should be drawn.
    //So use default value of itemUsedRect (0,0,0,0).
    //And vice versa the view rect except items used should 
    //draw background 
    if ( gapWidth <= 0 )
        {
        TPoint endPos( CAknGridView::ItemPos( iBottomItemIndex ).iX + ColumnWidth(),
        		       CAknGridView::ItemPos( iBottomItemIndex ).iY + iItemHeight );
        itemUsedRect.SetRect( CAknGridView::ItemPos(iTopItemIndex), endPos );
        if ( iViewRect.Intersects( itemUsedRect ) )
            {
            TRect viewRect( iViewRect );
            viewRect.Intersection( itemUsedRect );
            }
        }
    iGc->SetBrushColor( BackColor() );
    CFormattedCellListBoxItemDrawer* itemDrawer =
        static_cast<CFormattedCellListBoxItemDrawer*>( iItemDrawer );
    MAknsSkinInstance *skin = AknsUtils::SkinInstance();

    CWindowGc* gc = itemDrawer->Gc();
    if ( !gc )
        {
        gc = iGc;
        }

    CCoeControl* listBoxControl = itemDrawer->FormattedCellData()->Control();

    if ( listBoxControl )
        {
        MAknsControlContext *cc = AknsDrawUtils::ControlContext(
            listBoxControl );
        if ( !cc )
            {
            cc = itemDrawer->FormattedCellData()->SkinBackgroundContext();
            }

        if ( CAknEnv::Static()->TransparencyEnabled() )
            {
            AknsDrawUtils::BackgroundBetweenRects( 
                skin,
                cc,
                listBoxControl, 
                *iGc,
                iViewRect,
                itemUsedRect, 
                KAknsDrawParamNoClearUnderImage );
            }
        else
            {
            AknsDrawUtils::BackgroundBetweenRects(
                skin,
                cc,
                listBoxControl,
                *iGc,
                iViewRect,
                itemUsedRect ); 
            }        
        }
    else
        {
        DrawUtils::ClearBetweenRects( *gc, iViewRect, itemUsedRect );
        }
    _AKNTRACE_FUNC_EXIT;
    }

// End of File
