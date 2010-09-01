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
* Description: 
*     CAknGridView handles the drawing, the mapping
*     of the grid data index to the underlying listbox index (and
*     visa versa) as well as the movement around the grid.
*
*/

#ifndef __AKNGRIDVIEW_H__
#define __AKNGRIDVIEW_H__

// INCLUDES
#include <eiklbv.h>
#include <AknGridM.h>
#include <eiklabel.h>

// CLASS DECLARATION

/**
* @c CAknGridView handles the drawing, the mapping of the grid data index
* to the underlying listbox index (and vice versa) as well as the movement
* around the grid. Differentiation is needed between a data index and the
* list box index since the inherited list box code handles the top, bottom
* and current indexes as though everything is order topdown and left to
* right. This is no good for grid that maybe order in 8 different
* ways so need conversion between list box index and actual data
* index.
* List box index is the index for the data item according to the
* snaking list box format of numbering data items.
* Data index is the actual index in the grid according to the
* ordering applied to the data by the user.
* Note: the logical position is the intermediate form used to map
* from a list box index to a data index or vi sa versa. It is
* essentialy the position of the item in relation to the top left
* corner of the grid. I.e. the top left position has logical
* position 0,0.
* 
* @since 0.9
* @lib avkon.lib
*/
class CAknGridView : public CListBoxView 
	{
public:
	/** Enumeration flags for grid.*/
	enum TGridFlags
		{
		/** Vertical is primary direction.*/
		EPrimaryIsVertical	= 0x0001,
		/** From top to bottom.*/
		ETopToBottom		= 0x0002,
		/** From left to right.*/
		ELeftToRight		= 0x0004
		};
	/** Enumeration for different scrolling types.*/
	enum TScrollingType
		{
		/** Scrolling follows items and stops.*/
		EScrollFollowsItemsAndStops,
		/** Scrolling follows items and loops.*/
		EScrollFollowsItemsAndLoops,
		/** Scrolling follows grid. */
		EScrollFollowsGrid,
		/** Scrolling stops. */
		EScrollStops,
		/** Scrolls one line and stops.*/
		EScrollIncrementLineAndStops,
		/** Scrolls one line and loops.*/
		EScrollIncrementLineAndLoops
		};
	/** Enumeration flags for different layouts.*/
	struct SGrid
		{
		/** Current size of entire grid. */
		TSize iGridDimensions;
		/** Flags. */
		TInt iGridFlags;
		/** Size of the viewable area ( iColsInView * iRowsInView ). */
		TInt iPageSize;
		/** The number of columns in the viewable area. */
		TInt iColsInView;
		/** The number of rows in the viewable area. */
		TInt iRowsInView;
		/** The size of gap between items (height and width). */
		TSize iSizeBetweenItems;
		/** The size of an item. */
		TSize iSizeOfItems;
		};

protected:
	/** Enumeration flags for pages.*/
	enum TPageIndex 
		{
		/** Previous page.*/
		EPreviousPage,
		/** Next page.*/
		ENextPage,
		/** First page. */
		EHome,
		/** Last page.*/
		EEnd
		};
	/* Enumeration of position of current index.*/
	enum TPositionCurrentIndex
		{
		/** Page. */
		EPage,
		/** Column.*/
		EColumn,
		/** Opposite corner.*/
		EOppositeCorner
		};

public:
	/**
	* Default C++ constructor.
	*/
	IMPORT_C CAknGridView();
	
	/**
	* Destructor.
	*/
	IMPORT_C virtual ~CAknGridView();

	// actual <-> listbox index conversion routines
	/**
	* Returns the actual index of given listbox index.
	* @param aListBoxIndex The index of the listbox.
	* @return The actual data index.
	*/
	IMPORT_C TInt ActualDataIndex(TInt aListBoxIndex) const;
	
	/**
	* Returns the listbox index of given data index.
	* @param aDataIndex The index of the actual data.
	* @return The index in listbox.
	*/
	IMPORT_C TInt ListBoxIndex(TInt aDataIndex) const;

	/**
	* Returns the current data index with respect to the ordering of the cells
	* in the grid.
	* @return Current data index.
	*/
	IMPORT_C TInt CurrentDataIndex() const;
	
	/**
 	* Sets the current data index with a value given with respect to the
 	* ordering of the cells in the grid.
 	* @param aDataIndex The index to be set.
 	*/
	IMPORT_C void SetCurrentDataIndex(TInt aDataIndex);

	/**
 	* Sets the form of scroll to activate upon reaching the limit when moving
 	* in the primary direction of grid, primary meaning whether the items are
 	* organised vertically or horizontally.
 	* @param aScrollingType The primary scrolling type.
 	*/
	IMPORT_C void SetPrimaryScrollingType(TScrollingType aScrollingType);
	/**
 	* Sets the form of scroll to activate upon reaching the limit when moving
 	* in the secondary direction of grid.
 	* @param aSecondaryScrolling The secondary scrolling type.
 	*/
	IMPORT_C void SetSecondaryScrollingType(TScrollingType aSecondaryScrolling);

	/**
 	* Checks that number of cells in the grid is always enough to fill the
 	* current grid dimensions. This method should be called after any method
 	* that may alter the amount of data within the grid.
 	* @param aGridDimensions Grid diemnsions.
 	*/
	IMPORT_C void SetGridCellDimensions(TSize aGridDimensions);
	
	/**
 	* Returns the current grid dimensions.
 	* @return The size of the current grid.
 	*/
	IMPORT_C TSize GridCellDimensions() const;
	/**
	* Sets the size of the spaces between items.
	* @param aSizeOfSpaceBetweenItems The size of the spaces between items.
 	*/
	IMPORT_C void SetSpacesBetweenItems(TSize aSizeOfSpaceBetweenItems);
	
	/**
 	* Returns @c ETrue if the primary dimension of the grid is vertical.
 	* @return @ETrue if vertical is set as primary, otherwise @c EFalse.
 	*/
	IMPORT_C TBool IsPrimaryVertical() const;

	/**
 	* Converts a logical position on the grid, where the co-ordinates are with
 	* respect to the top left hand corner of the grid, to an index for the cell
 	* with respect to the ordering of the cells in the grid.
 	* @param aItemIndex Reference to the index for the cell in the grid. 
 	* @param aRowIndex The row in the grid.
 	* @param aColIndex The column in the grid.
 	*/
	IMPORT_C void DataIndexFromLogicalPos(
		TInt& aItemIndex,
		TInt aRowIndex,
		TInt aColIndex) const;
	
	/**
 	* Converts an index for a cell in the grid, given with respect to the
 	* ordering of the cells in the grid, to a logical position on the grid,
 	* where the co-ordinates are with respect to the top left hand corner of
 	* the grid.
 	* @param aItemIndex The index for the cell in the grid. 
 	* @param aRowIndex Reference to the row in the grid.
 	* @param aColIndex Reference to the column in the grid.
 	*/
	IMPORT_C void LogicalPosFromDataIndex(
		TInt aItemIndex,
		TInt& aRowIndex,
		TInt& aColIndex) const;
	
	/**
 	* Converts a CEikListBox index for a cell in the grid, given with respect
 	* to the snaking listbox top down, left to right structure underlying the
 	* grid structure, to a logical position on the grid, where the co-ordinates
 	* are with respect to the top left hand corner of the grid.
 	* @param aItemIndex Reference to the index for the cell in the grid. 
 	* @param aRowIndex The row in the grid.
 	* @param aColIndex The column in the grid.
 	*/	
	IMPORT_C void ListBoxIndexFromLogicalPos(
		TInt& aItemIndex,
		TInt aRowIndex,
		TInt aColIndex) const;
	/**
 	* Converts a logical position on the grid, where the co-ordinates are with
 	* respect to the top left hand corner of the grid, to a CEikListBox index
 	* for the cell with respect to the snaking listbox top down, left to right
 	* structure underlying the grid structure.
 	* @param aItemIndex The index for the cell in the grid. 
 	* @param aRowIndex Reference to the row in the grid.
 	* @param aColIndex Reference to the column in the grid.
 	*/
	IMPORT_C void LogicalPosFromListBoxIndex(
		TInt aItemIndex,
		TInt& aRowIndex,
		TInt& aColIndex) const;

	/**
	* Draws empty grid list.
	*/
	IMPORT_C virtual void DrawEmptyList() const;

	/**
 	* Grid initialisation function.
 	* @param aGridDetails Struct of grid details.
 	*/
	IMPORT_C void SetGridDetails(SGrid aGridDetails);

	/**
 	* This moves to the item and draws the grid in the right place.
 	* @param aItemIndex The wanted item index.
 	* @param aSelectionMode Mode for modifying the selection.
 	*/
	IMPORT_C void MoveToItemIndexL(TInt aItemIndex, TSelectionMode aSelectionMode);

	/**
	* This function returns the number of visible columns.
	* @return The number of visible columns in view.
	*/
	IMPORT_C TInt NumberOfColsInView() const;

	/**
 	* This function returns the number of visible rows.
 	* @return The number of visible rows in view.
 	*/
	IMPORT_C TInt NumberOfRowsInView() const;

    /**
    * Moves cursor with repeats.
    * @param aNext ETrue if next, EFalse if previous.
    * @param aSelectionMode selection mode.
    * @param aAmount Amount of steps to move.
    * @since S60 3.2
    */
    void MoveCursorWithRepeatsL( 
        TBool aNextOrPrev, 
        TSelectionMode aSelectionMode, 
        TInt aAmount );
    
public: // from CListBoxView 
	/**
	* From @c CListBoxView. Basically empty implementation of 
	* @c CListBoxView::DrawMatcherCursor.
	*/
	IMPORT_C virtual void DrawMatcherCursor();

	/** 
	* From @c CListBoxView. This function returns the current item in the grid
	* and -1 if there is no current item,
	* @return The current item.
	*/
	IMPORT_C TInt CurrentItemIndex() const;

protected:
	/**
	* This function tests whether an item exists.
	* @param aListBoxIndex Index to test.
	* @return @c ETrue if the specified item exists, @c EFalse otherwise.
	*/
	IMPORT_C TBool ItemExists(TInt aListBoxIndex) const;

public: // code moved from CSnakingListBoxView
	/**
 	* This function sets the width of the grid column. This should only be 
 	* called via the selection box class's @c SetColumnWidth method.
 	* @param aColumnWidth The required width of all columns in the view, 
 	* in pixels.
 	*/
	IMPORT_C void SetColumnWidth(TInt aColumnWidth);
	
	/**
	* Overloaded @c MoveCursorL method to process cursor movement according to
 	* orientation of the grid.
 	* @param aCursorMovement The cursor movement to apply 
 	* etc. @c ECursorNextItem and @c ECursorPreviousItem.
 	* @param aSelectionMode The selection mode of the calling list box. 	
 	*/	
	IMPORT_C virtual void MoveCursorL(
		TCursorMovement aCursorMovement,
		TSelectionMode aSelectionMode);

	/**
	* This function draws every visible item into the specified rectangle. 
	* As implemented in @c CListBoxView, this function's argument is ignored
	* and the internal viewing rectangle is used. See @c SetViewRect().
	* @param @c TRect* @c aClipRect = @c NULL The rectangle to draw into.
	*/
	IMPORT_C virtual void Draw(const TRect* aClipRect = NULL) const;

	/**
 	* This has been overloaded to ensure that only valid cells are drawn and 
 	* not the empty cells.
 	* @param aItemIndex Index number of the item to draw.
	*/ 	
	IMPORT_C virtual void DrawItem(TInt aItemIndex) const;

	/**
	* This function gets the position of the top left corner of the specified 
	* item, in pixels. 
	* @param aItemIndex An item in the model. 
	* @return @c TPoint position of the top left corner of the item, in pixels.
	*/ 
	IMPORT_C virtual TPoint ItemPos(TInt aItemIndex) const;
	
	/**
	* This function has been overloaded to draw items correctly. Recalculates 
	* the bottom item’s index. This is called by the list box control when 
	* either the size or the number of items in its model changes. 
	*/ 	
	IMPORT_C virtual void CalcBottomItemIndex();
	
	/**
	* This function gets the item the view would need to be moved to in order 
	* to make the specified item visible.
	* @param aItemIndex The item to make visible.
	* @return The item to scroll to to make @c aItemIndex visible.
	*/	
	IMPORT_C virtual TInt CalcNewTopItemIndexSoItemIsVisible(TInt aItemIndex) const;
	
	/**
	* This function draws every item between the start and end indices
	* inclusively.
	* @param aStartItemIndex The first item to draw.
	* @param aEndItemIndex The final item to draw.
	*/
	IMPORT_C virtual void DrawItemRange(TInt aStartItemIndex, TInt aEndItemIndex) const;

	/**
	* This function gets the width of all columns in the view.
	* @return The width of all columns in the view, in pixels.
	*/
	inline TInt ColumnWidth() const;
	
	/**
	* Sets which item appears at the top left corner of the view. The function
	* changes items displayed in the view appropriately.
	* @param aItemIndex Index of the item to set at the top left.
	*/
	IMPORT_C virtual void SetTopItemIndex(TInt aItemIndex);
	
	/**
	* This function sets item height in pixels.
	* @param aItemHeight New height in pixels for this view’s items.
	*/	
	IMPORT_C virtual void SetItemHeight(TInt aItemHeight);
	
	/*
	* This function converts an (x, y) pixel position to an item index.
	* @param aPosition Pixel position in the viewing rectangle.
	* @param aItemIndex Reference to the item index.
	* @return Whether there was an item at aPosition.
	*/	
	IMPORT_C virtual TBool XYPosToItemIndex(TPoint aPosition, TInt& aItemIndex) const;

	/**
	* Calculates the data width in columns. @c iDataWidth is calculated based on
	* model and drawer information.
	*/	
	IMPORT_C virtual void CalcDataWidth();
	
	/**
	* Gets the visible width of the specified rectangle in pixels.
	* @param aRect Reference to the rectangle for which to get the visible 
	* width.
	* @return Visible width of aRect in pixels.
	*/	
	IMPORT_C virtual TInt VisibleWidth(const TRect& aRect) const;
	
	/**
	* Makes the specified item visible by moving the view location and 
	* redrawing the control. Index of the item to make visible. 
	* @param aItemIndex Index of the item to make visible. 
	* @return @c ETrue if the control was redrawn, @c EFalse if no redraw 
	* happened (i.e. the item was already visible, or redraw was disabled).
	*/
	IMPORT_C virtual TBool ScrollToMakeItemVisible(TInt aItemIndex);
	
	/**
	* Gets the number of columns that this view would need to be scrolled by 
	* to make the specified item visible. The function returns 0 if no 
	* scrolling is needed. @c ScrollToMakeItemVisible() uses this function.
	* @param aItemIndex Item to make visible.
	* @return The number of columns to scroll, or zero if no scrolling is
	* needed.
	*/
	IMPORT_C virtual TInt CalculateHScrollOffsetSoItemIsVisible(TInt aItemIndex);
	
	/**
	* Gets the size of the specified item.
	* @param aItemIndex=0 The index of the item whose size this call is to get.
	* @return @c TSize The size of the item in pixels.
	*/
	IMPORT_C virtual TSize ItemSize(TInt aItemIndex=0) const;
	
	/**
	* Converts an item index into the (row, column) pair describing that item.
	* @param aItemIndex The item index.
	* @param aRowIndex Reference to the row index.
	* @param aColIndex Reference the column index.
	*/	
	IMPORT_C void CalcRowAndColIndexesFromItemIndex(TInt aItemIndex, TInt& aRowIndex, TInt& aColIndex) const;
	
	/**
	* This function converts a row/column pair into the item index for that 
	* item.
	* @param aItemIndex Reference to the item index. 
	* @param aRowIndex Row index of the item.
	* @param aColIndex Column index of the item.
	*/
	IMPORT_C void CalcItemIndexFromRowAndColIndexes(TInt& aItemIndex, TInt aRowIndex, TInt aColIndex) const;

protected: // code moved from CSnakingListBoxView
	/**
	* This function draws every item in every column between the start and end
	* columns inclusively.
	* @param aStartColIndex The first column to draw. 
	* @param aEndColIndex The last column to draw. 
	*/
	IMPORT_C void DrawColumnRange(TInt aStartColIndex, TInt aEndColIndex) const;

	/**
	* This function clears each item’s rectangle between the specified start
	* and finish item’s indexes.
	* @param aStartItemIndex The first item to clear.
	* @param aEndItemIndex The last item to clear.
	*/	
	IMPORT_C void ClearUnusedItemSpace(TInt aStartItemIndex, TInt aEndItemIndex) const;

	/**
	* This function updates the horizontal scroll offset (iHScrollOffset) 
	* based on the top item’s index. This function is called internally by
	* @c CEikSnakingListBoxes when needed.
	*/	
	IMPORT_C void UpdateHScrollOffsetBasedOnTopItemIndex();

protected:
	/**
	* This inline function is grid model helper.
	* @return A pointer to @c CAknGridM object.
	*/	
	inline CAknGridM* GridModel() const;

	/** 
	* This function handles movement routines.
	* @param aCursorMovement Handles cursor movements etc. @c ECursorNextItem
	* and @c ECursorPreviousItem.
	* @param aSelectionMode Modes for modifying the selection.
	*/
	IMPORT_C void DoMoveL(TCursorMovement aCursorMovement, TSelectionMode aSelectionMode);

private:
	// movement handling routines
	IMPORT_C TInt SearchByLines(TInt aX, TInt aY, TCursorMovement aCursorMovement, TBool aBeginSearchOnIndex = EFalse);
	IMPORT_C TInt FindNextItem(TInt aItemIndex, TBool aLookDown, TBool aLookRight, TBool aFirstLookHorizontal, TBool aBeginSearchOnIndex = EFalse);
	TBool IsEdgePassed(TInt aItemIndex, TBool aLookDown, TBool aLookRight, TBool aFirstLookHorizontal, TBool aBeginSearchOnIndex, TInt& aNewIndex);

	TBool IsMoveRight(TCursorMovement aCursorMovement);
	TBool IsMoveDown(TCursorMovement aCursorMovement);
private: // overridden from CListBoxView
	IMPORT_C virtual TAny* Reserved_1();

private:
    
    /**
    * Draws the portion of the grid view rectangle that contains no items.
    */
    void DrawUnusedViewPortion() const;
    
private:
	TScrollingType iScrollingType;
	TScrollingType iScrollInSecondaryDimension;

	SGrid iGridDetails;
    TInt iSpare[2];
	};

inline CAknGridM* CAknGridView::GridModel() const
	{
	return STATIC_CAST(CAknGridM*,iModel);
	}

inline TInt CAknGridView::ColumnWidth() const
	{ return iGridDetails.iSizeOfItems.iWidth; }

#endif // __AKNGRIDVIEW_H__
