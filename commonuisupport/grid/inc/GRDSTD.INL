// Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
// CGridLay
// 
//

inline void CGridLay::SetGridTable(const MGridTable* aGridTable)
/** Sets the specified grid table object.

@param aGridTable The grid table object. */
	{ iGridTable = aGridTable; }

inline TRangeRef CGridLay::VisibleRange() const
/** Gets the range of cells that are currently visible.

@return The visible cell range. Note that the TRangeRef::iFrom member is the 
cell that is visible at the top of the window, and the TRangeRef::iTo member 
is the cell that is partially visible at the bottom right of the window. */
	{ return iVisibleRange; }

inline TRangeRef CGridLay::TitleRange() const
/** Gets the range of cells that form the grid titles.

@return The range of cells that form the grid titles. */
	{ return iTitleRange; }

inline TRangeRef CGridLay::GridRange() const
/** Gets the range of cells that defines the grid boundary.

@return The range of cells that defines the grid boundary. */
	{ return iGridRange; }

inline TBool CGridLay::IsSideLabels() const
/** Tests whether side grid labels are printed.

@return True, if the side labels are printed; false, otherwise. */
	{ return (iFlags&EIsSideLabels); }

inline TBool CGridLay::IsTopLabels() const
/** Tests whether top labels are printed.

@return True, if the top labels are printed; false, otherwise. */
	{ return (iFlags&EIsTopLabels); }

inline TBool CGridLay::IsVerticalGridLines() const
/** Tests whether vertical grid lines are to be drawn.

@return True, if vertical grid lines are to be drawn; false, otherwise. */
	{ return (iFlags&EIsVerticalGridLines); }

inline TBool CGridLay::IsHorizontalGridLines() const
/** Tests whether horizontal grid lines are to be drawn.

@return True, if horizontal grid lines are to be drawn; false, otherwise. */
	{ return (iFlags&EIsHorizontalGridLines); }

inline TBool CGridLay::IsGridLabelSeparators() const
/** Tests whether label separators are to be drawn.

@return True, if label separators are to be drawn; false, otherwise. */
	{ return (iFlags&EIsGridLabelSeparators); }

inline TBool CGridLay::IsColumnBursting() const
/** Tests whether column bursting is permitted.

Column bursting occurs when the contents of a cell are too wide; adjacent 
cells are then overwritten, provided they are empty.

@return True, if column bursting is permitted; false, otherwise. */
	{ return (iFlags&EIsColumnBursting); }

inline TBool CGridLay::IsCursorVisible() const
/** Tests whether the cursor is visible.

@return True, if the cursor is visible; false, otherwise. */
	{ return (iFlags&EIsCursorVisible); }

inline TBool CGridLay::IsHighlightVisible() const
/** Tests whether selected cells are highlighted.

@return True, if selected cells are highlighted; false, otherwise. */
	{ return (iFlags&EIsHighlightVisible); }

inline TBool CGridLay::IsRowPermanentlySelected() const
/** Tests whether rows are permanently selected.

@return True, if rows are permanently selected; false, otherwise. */
	{ return (iFlags&EIsRowPermanentlySelected); }

inline TBool CGridLay::IsTitleLines() const
/** Tests whether the grid has both horizontal and vertical title lines.

@return True, if the grid has both a horizontal and vertical title line; false, 
otherwise. */
	{ return (iFlags&(EIsHorizontalTitleLine|EIsVerticalTitleLine)); }

inline TBool CGridLay::IsHorizontalTitleLine() const
/** Tests whether the grid has a horizontal title line.

@return True, if the grid is to have a horizontal title line; false otherwise. */
	{ return (iFlags&EIsHorizontalTitleLine); }

inline TBool CGridLay::IsVerticalTitleLine() const
/** Tests whether the grid has a vertical title line.

@return True, if the grid is to have a vertical title line; false otherwise. */
	{ return (iFlags&EIsVerticalTitleLine); }

inline TBool CGridLay::IsIndefiniteRowBoundaries() const
/** Tests whether the grid has indefinite row boundaries.

@return True, if the grid has indefinite row boundaries; false, otherwise. */
	{ return (iFlags&EIsIndefiniteRowBoundaries); }

inline TBool CGridLay::IsUniformRowHeight() const
/** Tests whether all the rows have the same height.

@return True, if all rows have the same height; false, otherwise. */
	{ return (iFlags&EIsUniformRowHeight); }

inline TBool CGridLay::IsUniformColumnWidth() const
/** Tests whether all columns have the same width.

@return True, if all columns have the same width; false, otherwise. */
	{ return (iFlags&EIsUniformColumnWidth); }

inline TBool CGridLay::IsTopLabelDragDisabled() const
/** Tests whether a drag operation on the boundary between two columns is permitted.

@return True, if a drag operation on a column boundary is permitted; false otherwise. */
	{ return (iFlags&EIsTopLabelDragDisabled); }

inline TBool CGridLay::IsSideLabelDragDisabled() const
/** Tests whether a drag operation on the boundary between two rows is permitted.

@return True, if a drag operation on a row boundary is permitted; false otherwise. */
	{ return (iFlags&EIsSideLabelDragDisabled); }

inline TBool CGridLay::IsPrintedLabels() const
/** Tests whether labels are printed.

@return True, if labels are printed; false, otherwise. */
	{ return (iFlags&EIsPrintedLabels); }

inline TBool CGridLay::IsPrintedGridLines() const
/** Tests whether grid lines are printed.

@return True, if grid lines are printed; false, otherwise. */
	{ return (iFlags&EIsPrintedGridLines); }

inline TBool CGridLay::IsVisibleToRowFullyVisible() const
	{ return (iFlags&EIsVisibleToRowFullyVisible); }

inline TBool CGridLay::IsVisibleToColumnFullyVisible() const
	{ return (iFlags&EIsVisibleToColumnFullyVisible); }

inline TBool CGridLay::IsEncroachingCellBorders() const
/** Tests whether encroaching cell borders are permitted.

Encroaching cell borders are where cell borders wider than one pixel are drawn 
inside the cell, as opposed to outside.

@return True, if encroaching cells borders are permitted; false, otherwise. */
	{ return (iFlags&EIsEncroachingCellBorders); }

inline TBool CGridLay::IsRowSelectionDisabled() const
/** Tests whether row selection is disabled.

@return True, if row selection is disabled; false, otherwise. */
	{ return (iFlags&EIsRowSelectionDisabled); }

inline TBool CGridLay::IsColumnSelectionDisabled() const
/** Tests whether column selection is disabled.

@return True, if column selection is disabled; false, otherwise. */
	{ return (iFlags&EIsColumnSelectionDisabled); }

inline TBool CGridLay::IsAutoClearGridCells() const
/** Tests whether automatic clearing of grid cells is done.

Automatic clearing of grid cells is where all cells are cleared on redraw, 
in case drawing the contents doesn't guarantee to write to every pixel (the 
usual way of doing flicker-free redraws).

@return True, if automatic clearing of grid cells is done; false, otherwise. */
	{ return (iFlags&EIsAutoClearGridCells); }

inline TBool CGridLay::IsPageBreakLinesHidden() const
/** Tests whether lines marking page breaks are hidden.

@return True, if lines marking page breaks are hidden; false, otherwise. */
	{ return (iFlags&EIsPageBreakLinesHidden); }

inline TBool CGridLay::HasChanged() const
/** Tests whether any change has occurred to the grid layout.

Such changes include alterations to the height of a row or the 
width of a column, additions or deletions of rows or columns, 
and changes to the visibility of grid lines.
Note that this list is not exhaustive.

@return True, if the grid layout has changed; false, otherwise. */
	{ return iHasChanged; }

inline void CGridLay::SetHasChanged(TBool aHasChanged)
/** Sets whether any change has occurred to the grid layout.

@param aHasChanged ETrue, if any change has occurred to the grid layout; EFalse, 
otherwise. */
	{ iHasChanged=aHasChanged; }

inline void CGridLay::SetGridEdgeColor(TRgb aColor)
/** Defines the colour that the edges of the grid beyond the grid range are to 
have.

If not changed by this function, the default colour is white.

@param aColor The colour value. */
	{ iGridEdgeColor=aColor; }

inline TBool CGridLay::IsPaginated() const
/** Tests whether the grid has been paginated.

@return True, if the grid has been paginated; false, otherwise. */
	{ return (iFlags&EIsPaginated); }

inline void CGridLay::SetPrintRange(const TRangeRef& aPrintRange) 
/** Sets the range of cells that are visible for printing.

@param aPrintRange The cell range. */
	{ iVisibleRange=aPrintRange; }

inline TSize CGridLay::PageSizeInTwips() const
/** Gets the size of a page.

@return The size of a page, in twips. */
	{ return iPageSizeInTwips; }

inline TBool CGridLay::IsAutoPagination() const
/** Tests whether automatic pagination is in effect.

@return True, if automatic pagination is in effect, false, otherwise. */
	{ return (iFlags&EIsAutoPagination); }

// CGridLabelImg

inline void CGridLabelImg::SetGraphicsDeviceMap(MGraphicsDeviceMap* aGraphicsDeviceMap)
/** Supplies a new interface object for mapping between twips and device-specific 
units.

Note that the caller must call ReleaseFont() before calling this function, 
and must call NotifyGraphicsDeviceMapChangeL() afterwards.

@param aGraphicsDeviceMap A new interface object for mapping between twips 
and device-specific units. */
	{
	iGraphicsDeviceMap=aGraphicsDeviceMap;
	}

inline TFontSpec CGridLabelImg::FontSpec() const
/** Gets the font specification.

@return The font specification. */
	{
	return iFontSpec;
	}

inline void CGridLabelImg::SetGridColors(const TGridColors& aGridColors)
/** Sets the colours to be used when drawing the label.

@param aGridColors The object containing the grid colours specification. */
	{
	iGridColors = aGridColors;
	}

// CGridCellImg

inline TInt CGridCellImg::BurstColOffset() const
/** Gets the bursting column offset.

@return The burst column offset */
	{ return iBurstColOffset; }

inline TInt CGridCellImg::BurstLeft() const
/** Gets the left hand bursting value.

@return The burst value. */
	{ return iBurstLeft; }

inline TInt CGridCellImg::BurstRight() const
/** Gets the right hand bursting value.

@return The burst value */
	{ return iBurstRight; }

inline TBool CGridCellImg::IsHorizontalGridLines() const
/** Tests whether horizontal grid lines are drawn.

This function is set by the CGridImg object and allows classes derived from 
CGridCellImg to modify or restrict the area into which they draw.

@return True, if horizontal grid lines are drawn; false, otherwise. */
	{ return iGridLineFlags&EIsHorizontalGridLines; }

inline TBool CGridCellImg::IsVerticalGridLines() const
/** Tests whether vertical grid lines are drawn.

This function is set by the CGridImg object and allows classes derived from 
CGridCellImg to modify or restrict the area into which they draw.

@return True, if vertical grid lines are drawn; false, otherwise. */
	{ return iGridLineFlags&EIsVerticalGridLines; }

inline void CGridCellImg::SetGridColors(const TGridColors& aGridColors)
/** Sets the colours to be used when drawing.

@param aGridColors The object containing the grid colours specification. */
	{
	iGridColors = aGridColors;
	}

// CGridImg

inline void CGridImg::SetGridLay(CGridLay* aGridLay)
/** Sets the specified grid layout object.

@param aGridLay A pointer to the object that controls the layout of rows and 
columns. */
	{ iGridLay = aGridLay; }

inline void CGridImg::SetWindow(RWindow *aWin)
/** Sets the specified window.

@param aWin A pointer to the currently active window. */
	{ iWin = aWin; }

//->
//inline void CGridImg::SetGridLabelImg(CGridLabelImg *aGridLabelImg)
//	{ iGridLabelImg =  aGridLabelImg; }
//->

inline void CGridImg::SetCursorMoveCallBack(MGridCursorMoveCallBack *aCursorMoveCallBack)
/** Sets the cursor moved call-back object.

The call-back object encapsulates the implementation of a call-back function 
that is called whenever there is a change to the cursor position.

@param aCursorMoveCallBack A pointer to the callback object. */
	{ iCursorMoveCallBack = aCursorMoveCallBack; }

inline const CGridCellRegion* CGridImg::Selected() const
/** Gets the currently selected region.

@return A pointer to the selected region object. */
	{ return iSelected; }

inline const CGridLabelImg* CGridImg::GridLabelImg() const
/** Gets the the object that is used to draw a cell label.

@return A pointer to the object that is used to draw a cell label. */
	{ return iGridLabelImg; }

inline TCellRef CGridImg::CursorPos() const
/** Gets the current position of the cursor.

@return The cell reference of the current cursor position. */
	{ return iCursorPos; }

inline TCellRef CGridImg::AnchorPos() const
/** Gets the cursor's anchor position. 

This is the cell reference of the position that the cursor must return to 
after a series of selected movements have been made.

@return The cell reference of the cursor's anchor position. */
	{ return iAnchorPos; }

inline TCellRef CGridImg::NewCursorPos() const
/** Gets the new position of the cursor.

@return The cell reference of the new cursor position.
@see SetCursorPosL() */
	{ return iNewCursorPos; }

inline TRect CGridImg::GridRect() const
/** Gets the rectangle containing the grid.

@return The rectangle containing the grid. */
	{ return iGridRect; }

inline TPoint CGridImg::TitlePoint() const
/** Gets the position of the title.

This is the point at the top left of the grid excluding the labels.

@return The position of the title. */
	{ return iTitlePoint; }

inline TPoint CGridImg::MainPoint() const
// Returns the most commonly used point in the grid (usually same as TitlePoint()).
/** Gets the position at which the visible range starts.

@return The position at which the visible range starts. */
	{ return iMainPoint; }

inline TRect CGridImg::MainRect() const
/** Gets the rectangle that corresponds to the visible range.

@return The rectangle that corresponds to the visible range. */
	{ return TRect(iMainPoint,iGridRect.iBr); }


