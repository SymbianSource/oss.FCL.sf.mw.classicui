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
// The data members of the class CGridLay are as follows:-
// iGridRange - the range of cells that define the grid boundary.
// iVisibleRange - the range of cells within the grid that are visible
// in the active window. iVisibleRange.iFrom is the cell reference
// of the top left cell in the window with respect to iGridRange
// (i.e not necessarily (1, 1)). iVisibleRange.iTo is the cell that is
// partially visible at the bottom right of the window.
// *iGridTable, *iGridImg - allows access to the data in these classes.
// *iColumnWidthMap,*iRowHeightMap - pointers to an array of column/row heights/widths
// 
//

#include <s32strm.h>
#include "GRDSTD.H"
#include "GRDMAP.H"
#include "GRDPANIC.H"


#define KRgbGridForeground			TRgb(0,0,0)			// Black
#define KRgbGridBackground			TRgb(255,255,255)	// White
#define KRgbGridLines				TRgb(170,170,170)	// Light Gray
#define KRgbGridLabelSeparators		TRgb(0,0,0)


RWriteStream& operator<<(RWriteStream& aStream,const TInt& aInt)
	{
	aStream.WriteInt32L(aInt);
	return aStream;
	}

RReadStream& operator>>(RReadStream &aStream,TInt& aInt)
	{
	aInt = aStream.ReadInt32L();
	return aStream;
	}


//
// TGridColors class
//
EXPORT_C TGridColors::TGridColors() :
	iForeground(KRgbGridForeground),
	iBackground(KRgbGridBackground),
	iLines(KRgbGridLines),
	iLabelSeparators(KRgbGridLabelSeparators)
/** Default constructor.

Sets the colours to their default values: foreground colour to the RGB value 
TRgb(0,0,0), background colour to the RGB value TRgb(255,255,255), the colour 
of lines to the RGB value TRgb(170,170,170), and the colour of label separators 
to the RGB value TRgb(0,0,0). */
	{
	}

EXPORT_C TGridColors::TGridColors(TRgb aForeground, TRgb aBackground, TRgb aLines, TRgb aLabelSeparators) :
	iForeground(aForeground),
	iBackground(aBackground),
	iLines(aLines),
	iLabelSeparators(aLabelSeparators)
/** Constructor setting the colour values.

@param aForeground The foreground colour value.
@param aBackground The background colour value.
@param aLines The colour of lines.
@param aLabelSeparators The colour of label separators. */
	{
	}


// CGridLay stuff

EXPORT_C CGridLay::CGridLay(MGraphicsDeviceMap* aGraphicsDeviceMap)
	: iGraphicsDeviceMap(aGraphicsDeviceMap)
/** Constructor taking an object that implements mapping between twips and device-specific 
units.

@param aGraphicsDeviceMap An object that implements the interface for mapping 
between twips and device-specific units. Typically, this is a TZoomFactor 
object. */
	{
	}

LOCAL_C void CopyIntArrayL(const CArrayFix<TInt>* aSource,CArrayFix<TInt>*& aDest)
	{
	TInt count=aSource->Count();
	aDest = new(ELeave) CArrayFixFlat<TInt>(Max(count,1));
	for (TInt ii=0;ii<count;ii++)
		aDest->AppendL((*aSource)[ii]);
	}

EXPORT_C void CGridLay::ConstructL(CGridLay* aGridLay,CGridImg* aGridImg)
//
// Constructs a partial gridLay object for printing with the same data as the passed object.
// - Assumes the zoom factor has already been set
// - New Sparse maps are created
/** A second-phase constructor, taking an existing grid layout object, that constructs 
a partial layout object for printing.

The function assumes that the zoom factor has already been set.

@param aGridLay Pointer to an existing grid layout object.
@param aGridImg Pointer to an existing grid image object. */
	{
	iGridImg=aGridImg;
	iGridTable=aGridLay->iGridTable;
	iGridRange=aGridLay->iGridRange;
	iColumnWidthMap = CSparseMap::NewL(aGridLay->iColumnWidthMap);
	CopyIntArrayL(aGridLay->iHardRowPageBreaks,iHardRowPageBreaks);
	CopyIntArrayL(aGridLay->iHardColumnPageBreaks,iHardColumnPageBreaks);
	iPageSizeInTwips=aGridLay->iPageSizeInTwips;
	iRowHeightMap = CSparseMap::NewL(aGridLay->iRowHeightMap);
	RecalcPixelSparseMaps();
	iFlags=aGridLay->iFlags;
	if (IsPaginated())
		{
		ClearPagination();
		PaginateL();
		}
	}

EXPORT_C void CGridLay::ConstructL(const MGridTable *aGridTable,CGridImg *aGridImg,TInt aNoOfRows,TInt aNoOfCols)
/** A second-phase constructor for constructing the object with definite row boundaries.

@param aGridTable A pointer to the grid table.
@param aGridImg Pointer to a grid image object.
@param aNoOfRows The number of rows in the grid.
@param aNoOfCols The number of columns in the grid. */
	{
	TRangeRef gridRange(0,0,aNoOfRows-1,aNoOfCols-1);
	ConstructL(aGridTable,aGridImg,gridRange);
	}

EXPORT_C void CGridLay::ConstructL(const MGridTable *aGridTable,CGridImg *aGridImg,TInt aNoOfCols)
/** A second-phase constructor for constructing the object with indefinite row 
boundaries.

@param aGridTable A pointer to the grid table.
@param aGridImg Pointer to a grid image object.
@param aNoOfCols The number of columns in the grid. */
	{
	SetIndefiniteRowBoundaries(ETrue);
	TRangeRef gridRange(-KMaxTInt,0,KMaxTInt,aNoOfCols-1);
	ConstructL(aGridTable,aGridImg,gridRange);
	}

void CGridLay::ConstructL(const MGridTable *aGridTable,CGridImg *aGridImg,const TRangeRef& aGridRange)
// Initialization of member data in CGridLay
	{
	iGridTable = aGridTable;
	iGridImg = aGridImg;
	iGridRange = aGridRange;

	iColumnWidthMap = CSparseMap::NewL();
	iRowHeightMap = CSparseMap::NewL();
	iHardRowPageBreaks = new(ELeave) CArrayFixFlat<TInt>(1);
	iHardColumnPageBreaks = new(ELeave) CArrayFixFlat<TInt>(1);

	SetGridToDefault();
	if (iGridImg)
		iGridImg->ConstructSelectedL(iGridRange);
	iHasChanged=EFalse;
	}

EXPORT_C void CGridLay::SetGridImgL(CGridImg* aGridImg)
/** Sets the specified grid image object.

@param aGridImg The grid image object that draws the contents of the grid. */
	{
	__ASSERT_DEBUG(aGridImg!=NULL,Panic(EGridLayInvalidGridImg));
	iGridImg=aGridImg;
	iGridImg->ResetReferencePoints();
	ResetVisibleToCell();
	iGridImg->CheckSideLabelWidth();
	iGridImg->ConstructSelectedL(iGridRange);
	if (IsPaginated())	// Internalize will fail to paginate if NULL gridimg
		{
		ClearPagination();
		PaginateL();
		}
	}

EXPORT_C CGridLay::~CGridLay()
/** Destructor.

Frees resources prior to destruction of the object. */
	{
	delete iColumnWidthMap;
	delete iRowHeightMap;
	delete iColumnPageMap;
	delete iRowPageMap;
	delete iHardRowPageBreaks;
	delete iHardColumnPageBreaks;
	}

EXPORT_C void CGridLay::SetGraphicsDeviceMap(MGraphicsDeviceMap* aGraphicsDeviceMap)
/** Sets the graphics device map to be used.

@param aGraphicsDeviceMap The graphics device map: an interface for mapping 
between twips and device-specific units. */
	{
	__ASSERT_DEBUG(iGridImg!=NULL,Panic(EGridLayInvalidGridImg));
	iGraphicsDeviceMap=aGraphicsDeviceMap;
	RecalcPixelSparseMaps();
	iGridImg->ResetReferencePoints();
	ResetVisibleToCell();
	}

EXPORT_C void CGridLay::SetGridToDefault()
/** Resets the grid to its default layout. */
	{
	iRowHeightMap->ResetArray();
	iColumnWidthMap->ResetArray();
	iRowHeightMap->SetDefaultValueInTwips(EInitialDefaultRowHeightInTwips);
	iColumnWidthMap->SetDefaultValueInTwips(EInitialDefaultColumnWidthInTwips);
	RecalcPixelSparseMaps();
	ClearPagination();
	iHardRowPageBreaks->Reset();
	iHardColumnPageBreaks->Reset();
	iMinRowHeightInPixels=0;
	iMinColumnWidthInPixels=0;
	TBool isIndefiniteRowBoundaries=IsIndefiniteRowBoundaries();
	iFlags=EIsTopLabels|EIsSideLabels|EIsHorizontalGridLines|EIsVerticalGridLines|EIsGridLabelSeparators
		|EIsCursorVisible|EIsHighlightVisible|EIsPrintedGridLines|EIsAutoClearGridCells;
	if (iGridImg)
		{
		iGridImg->SetGridLay(this);
		iGridImg->ResetReferencePoints();
		}
	if (isIndefiniteRowBoundaries)
		{
		iFlags|=EIsIndefiniteRowBoundaries;
		iVisibleRange.iFrom.iRow=0;
		}
	else
		iVisibleRange.iFrom.iRow=iGridRange.iFrom.iRow;
	iVisibleRange.iFrom.iCol=iGridRange.iFrom.iCol;
	if (iGridImg)
		{
		ResetVisibleToCell();
		iGridImg->CheckSideLabelWidth();
		}
	}

EXPORT_C void CGridLay::SetVisibleRange(const TCellRef& aTopLeftCell)
/** Scrolls the grid so that the specified cell is visible in the top left corner 
of the grid.

@param aTopLeftCell The cell to be made visible in the top left corner of 
the visible grid. */
	{
	iVisibleRange.iFrom = aTopLeftCell;
	ResetVisibleToCell();
	}

EXPORT_C TPoint CGridLay::ExposeCell(const TCellRef &aCell)
/** Scrolls the grid by the minimum necessary to allow the specified cell to become 
visible.

@param aCell The cell to be made visible.
@return The number of pixels scrolled, in the x and y directions. */
	{
	TCellRef cell=aCell;
	LimitCellToVisible(cell);
	TCellRef newVisFromCell=iVisibleRange.iFrom;
	TInt visibilityCorr = (IsVisibleToRowFullyVisible()) ? 0 : 1;
	if (iVisibleRange.iTo.iRow>=iVisibleRange.iFrom.iRow)
		{
	    if (cell.iRow+visibilityCorr>iVisibleRange.iTo.iRow)
		    {
		    if (iVisibleRange.iFrom.iRow!=iVisibleRange.iTo.iRow)
			    CalcVisibleFromRow(cell.iRow+1,newVisFromCell.iRow);
		    else
			    newVisFromCell.iRow=cell.iRow;
		    }
	    else if (cell.iRow<iVisibleRange.iFrom.iRow)
		    newVisFromCell.iRow=cell.iRow;
        }
	visibilityCorr = (IsVisibleToColumnFullyVisible()) ? 0 : 1;
	if (iVisibleRange.iTo.iCol>=iVisibleRange.iFrom.iCol)
		{
	    if (cell.iCol+visibilityCorr>iVisibleRange.iTo.iCol)
		    {
		    if (iVisibleRange.iFrom.iCol!=iVisibleRange.iTo.iCol)
			    CalcVisibleFromColumn(cell.iCol+1,newVisFromCell.iCol);
		    else
			    newVisFromCell.iCol=cell.iCol;
		    }
	    else if (cell.iCol<iVisibleRange.iFrom.iCol)
		    newVisFromCell.iCol=cell.iCol;
        }
	TPoint offset=CalcOffsetBetweenCells(iVisibleRange.iFrom,newVisFromCell);
	SetVisibleRange(newVisFromCell);
	return (offset);
	}

EXPORT_C TPoint CGridLay::ExposeCellToTopLeft(const TCellRef &aCell)
/** Scrolls the grid by the minimum necessary so that the specified cell is in 
the top left corner of the visible grid.

@param aCell The cell to be made visible in the top left corner of the visible 
grid.
@return The number of pixels scrolled, in the x and y directions. */
	{
	TCellRef cell=aCell;
	LimitCellToVisible(cell);
	TPoint offset=CalcOffsetBetweenCells(iVisibleRange.iFrom,cell);
	SetVisibleRange(cell);
	return offset;
	}

EXPORT_C TPoint CGridLay::PageScroll(TMoveDirectionAndAmount aPageScroll)
// Same as CalcScroll but updates iVisibleRange to the new value.
/** Scrolls the grid by one page.

@param aPageScroll The direction and amount by which to scroll.
@return The number of pixels scrolled, in the x and y directions. This represents 
the amount of scrolling required to move from the start of the old visible 
range to the start of the new visible range. */
	{
	TRangeRef newVisRange;
	newVisRange.iFrom=CalcVisibleFromCellAfterPageScroll(aPageScroll);
	TPoint offset=CalcOffsetBetweenCells(iVisibleRange.iFrom,newVisRange.iFrom);
	SetVisibleRange(newVisRange.iFrom);
	return offset;
	}

TInt CGridLay::ColumnWidthInPixels(TInt aCol) const
	{
	return iColumnWidthMap->ValueInPixels(aCol);
	}

EXPORT_C TInt CGridLay::ColumnWidthInTwips(TInt aCol) const
/** Gets the width of the specified column.

@param aCol The column number.
@return The width of the column, in twips. */
	{
	return iColumnWidthMap->ValueInTwips(aCol);
	}

void CGridLay::SetColumnWidthInPixelsL(TInt aCol,TInt aWidthInPixels)
//
// Set the given column to the given width. Ensures that the visible range is
// left with sensible values
//	
	{
	__ASSERT_DEBUG(iGraphicsDeviceMap!=NULL,Panic(EGridNullGraphicsDeviceMap));
	aWidthInPixels=Max(aWidthInPixels,iMinColumnWidthInPixels);
	PreCheckColumnWidthChange(aCol,aWidthInPixels);
	iColumnWidthMap->SetL(aCol,iGraphicsDeviceMap->HorizontalPixelsToTwips(aWidthInPixels),aWidthInPixels);
	PostCheckColumnWidthChange(aCol,aWidthInPixels);
	}

void CGridLay::PreCheckColumnWidthChange(TInt aCol,TBool aNonZeroWidth)
	{
	if (aNonZeroWidth)
		{
		TInt col=aCol;
		StepColumnForward(col);
		if (IsVerticalTitleLine() && col==iTitleRange.iFrom.iCol)
			iTitleRange.iFrom.iCol=aCol;
		else if ((!IsVerticalTitleLine() || col>iTitleRange.iTo.iCol) && col==iVisibleRange.iFrom.iCol)
			iVisibleRange.iFrom.iCol=aCol;
		}
	}

void CGridLay::PostCheckColumnWidthChange(TInt aCol,TBool aNonZeroWidth)
	{
	if (!aNonZeroWidth)
		{
		if (IsVerticalTitleLine() && aCol==iTitleRange.iFrom.iCol)
			StepColumnForward(iTitleRange.iFrom.iCol);
		if (aCol==iVisibleRange.iFrom.iCol)
			StepColumnForward(iVisibleRange.iFrom.iCol);
		}
	if (iGridImg)
		iGridImg->ResetReferencePoints();
	ResetVisibleToColumn();
	iHasChanged=ETrue;
	}

EXPORT_C void CGridLay::SetColumnWidthInTwipsL(TInt aCol,TInt aWidthInTwips)
//
// Set the given column to the given width. Ensures that the visible range is
// left with sensible values
//	
/** Sets the width of the specified column.

Note that the width cannot be set smaller than the minimum defined column 
width.

@param aCol The number of the column whose width is to be set.
@param aWidthInTwips The width of the column, in twips.
@panic GRIDIMG 9 In debug mode, if no MGraphicsDeviceMap object has been set.
@see MinColumnWidthInPixels() */
	{
	TInt widthInPixels=0;
	if (iGraphicsDeviceMap)
		{
		widthInPixels=iGraphicsDeviceMap->HorizontalTwipsToPixels(aWidthInTwips);
		if (widthInPixels<iMinColumnWidthInPixels)
			{
			widthInPixels=iMinColumnWidthInPixels;
			aWidthInTwips=iGraphicsDeviceMap->HorizontalPixelsToTwips(widthInPixels);
			}
		}
	PreCheckColumnWidthChange(aCol,aWidthInTwips);
	iColumnWidthMap->SetL(aCol,aWidthInTwips,widthInPixels);
	PostCheckColumnWidthChange(aCol,aWidthInTwips);
	}

EXPORT_C TInt CGridLay::SetColumnWidthInTwipsL(TInt aStartCol,TInt aEndCol,TInt aWidthInTwips)
/** Sets the widths of all specified columns to the specified value.

@param aStartCol The first column whose width is to be set.
@param aEndCol The last column whose width is to be set.
@param aWidthInTwips The width of the columns, in twips. Note that if the specified 
columns span the whole grid, then the function sets this value as the default 
width of all columns through a call to SetDefaultColumnWidthInTwips().
@return KErrNone if successful; KErrTooBig if the difference between the two 
column numbers is greater than EMaxArrayChanges. */
	{
	if (aStartCol==iGridRange.iFrom.iCol && aEndCol==iGridRange.iTo.iCol)
		{
		SetColumnWidthsToDefault();
		SetDefaultColumnWidthInTwips(aWidthInTwips);
		}
	else if (aEndCol-aStartCol>EMaxArrayChanges)
		return KErrTooBig;
	else
		{
		for (;aStartCol<=aEndCol;aStartCol++)
			SetColumnWidthInTwipsL(aStartCol,aWidthInTwips);
		}
	iHasChanged=ETrue;
	return KErrNone;
	}

TInt CGridLay::DefaultColumnWidthInPixels() const
	{
	return iColumnWidthMap->DefaultValueInPixels();
	}

EXPORT_C TInt CGridLay::DefaultColumnWidthInTwips() const
/** Gets the default width of columns.

@return The default width of columns, in twips. */
	{
	return iColumnWidthMap->DefaultValueInTwips();
	}

void CGridLay::SetDefaultColumnWidthInPixels(TInt aWidthInPixels)
	{
	if (aWidthInPixels==0)
		return;
	__ASSERT_DEBUG(iGraphicsDeviceMap!=NULL,Panic(EGridNullGraphicsDeviceMap));
	aWidthInPixels=Max(aWidthInPixels,iMinColumnWidthInPixels);
	iColumnWidthMap->SetDefaultValueInPixels(aWidthInPixels);
	iColumnWidthMap->SetDefaultValueInTwips(iGraphicsDeviceMap->HorizontalPixelsToTwips(aWidthInPixels));
	if (iGridImg)
		iGridImg->ResetReferencePoints();
	ResetVisibleToColumn();
	iHasChanged=ETrue;
	}

EXPORT_C void CGridLay::SetDefaultColumnWidthInTwips(TInt aWidthInTwips)
/** Sets the column width default value.

Note that the width cannot be set smaller than the minimum defined column 
width.

@param aWidthInTwips The width of columns, in twips.
@see SetMinColumnWidthInPixels()
@see MinColumnWidthInPixels() */
	{
	if (aWidthInTwips==0)
		return;
	if (iGraphicsDeviceMap)
		{
		TInt widthInPixels=iGraphicsDeviceMap->HorizontalTwipsToPixels(aWidthInTwips);
		if (widthInPixels<iMinColumnWidthInPixels)
			{
			widthInPixels=iMinColumnWidthInPixels;
			aWidthInTwips=iGraphicsDeviceMap->HorizontalPixelsToTwips(widthInPixels);
			}
		iColumnWidthMap->SetDefaultValueInPixels(widthInPixels);
		}
	iColumnWidthMap->SetDefaultValueInTwips(aWidthInTwips);
	if (iGridImg)
		iGridImg->ResetReferencePoints();
	ResetVisibleToColumn();
	iHasChanged=ETrue;
	}

EXPORT_C void CGridLay::SetColumnWidthsToDefault()
/** Sets the widths of all columns to the default value.

@see SetDefaultColumnWidthInTwips() */
	{
	iColumnWidthMap->ResetArray();
	if (iGridImg)
		iGridImg->ResetReferencePoints();
	ResetVisibleToColumn();
	iHasChanged=ETrue;
	}

EXPORT_C TInt CGridLay::MinColumnWidthInPixels() const
/** Gets the minimum width of columns.

@return The minimum width of columns, in pixels. */
	{
	return iMinColumnWidthInPixels;
	}

EXPORT_C void CGridLay::SetMinColumnWidthInPixels(TInt aWidthInPixels)
/** Sets the minimum width of columns.

@param aWidthInPixels The minimum width of columns, in pixels. */
	{
	iMinColumnWidthInPixels=aWidthInPixels;
	iHasChanged=ETrue;
	}

EXPORT_C TInt CGridLay::ColumnWidthOfSelectedInTwips() const
/** Gets the width of columns in the selected region.

@return The column width, in twips, if all columns in the selected region 
have the same width; -1, otherwise.
@panic GRIDIMG 3 If this grid layout object has no grid image object. */
	{
	__ASSERT_DEBUG(iGridImg!=NULL,Panic(EGridLayInvalidGridImg));
	if (IsUniformColumnWidth())
		return DefaultColumnWidthInTwips();
	const CGridCellRegion* selected=iGridImg->Selected();
	TInt count=selected->Count();
	if (!count)
		return ColumnWidthInTwips(iGridImg->CursorPos().iCol);
	if (selected->IsAnyRowSelected())
		return iColumnWidthMap->Count() ? -1 : DefaultColumnWidthInTwips();

	TInt width=ColumnWidthInTwips((*selected)[count-1].iFrom.iCol);
	for (TInt ii=0;ii<count;ii++)
		{
		TRangeRef range=(*selected)[ii];
		for (;range.iFrom.iCol<=range.iTo.iCol;range.iFrom.iCol++)
			{
			if (ColumnWidthInTwips(range.iFrom.iCol)!=width)
				return -1; //Inconsistent widths
			}
		}
	return width;
	}

EXPORT_C void CGridLay::SetColumnWidthOfSelectedInTwipsL(TInt aWidthInTwips)
/** Sets the widths of all columns in the selected region to the specified value.

@param aWidthInTwips The column width, in twips.
@panic GRIDIMG 3 If this grid layout object has no grid image object. */
	{
	__ASSERT_DEBUG(iGridImg!=NULL,Panic(EGridLayInvalidGridImg));
	const CGridCellRegion* selected=iGridImg->Selected();
	if (selected->IsAnyRowSelected() || IsUniformColumnWidth())
		{
		iColumnWidthMap->ResetArray();
		SetDefaultColumnWidthInTwips(aWidthInTwips);
		}
	else
		{
		TInt count=selected->Count();
		if (!count)
			SetColumnWidthInTwipsL(iGridImg->CursorPos().iCol,aWidthInTwips);
		for (TInt ii=0;ii<count;ii++)
			{
			TRangeRef range=(*selected)[ii];
			if ((range.iTo.iCol-range.iFrom.iCol)>EMaxArrayChanges)
				continue;
			for (;range.iFrom.iCol<=range.iTo.iCol;range.iFrom.iCol++)
				SetColumnWidthInTwipsL(range.iFrom.iCol,aWidthInTwips);
			}
		}
	NotifyPaginationOutOfDateL();
	}

TInt CGridLay::RowHeightInPixels(TInt aRow) const
	{
	return iRowHeightMap->ValueInPixels(aRow);
	}

EXPORT_C TInt CGridLay::RowHeightInTwips(TInt aRow) const
/** Gets the height of the specified row.

@param aRow The row number.
@return The height of the row, in twips. */
	{
	return iRowHeightMap->ValueInTwips(aRow);
	}

void CGridLay::SetRowHeightInPixelsL(TInt aRow,TInt aHeightInPixels)
//
// Similar to SetColumnWidthInPixelsL (remember this may be limited to the min row height)
//
	{
	__ASSERT_DEBUG(iGraphicsDeviceMap!=NULL,Panic(EGridNullGraphicsDeviceMap));
	aHeightInPixels=Max(aHeightInPixels,iMinRowHeightInPixels);
	PreCheckRowHeightChange(aRow,aHeightInPixels);
	iRowHeightMap->SetL(aRow,iGraphicsDeviceMap->VerticalPixelsToTwips(aHeightInPixels),aHeightInPixels);
	PostCheckRowHeightChange(aRow,aHeightInPixels);
	}

void CGridLay::PreCheckRowHeightChange(TInt aRow,TBool aNonZeroHeight)
	{
	if (aNonZeroHeight)
		{
		TInt row=aRow;
		StepRowForward(row);
		if (IsHorizontalTitleLine() && row==iTitleRange.iFrom.iRow)
			iTitleRange.iFrom.iRow=aRow;
		else if ((!IsHorizontalTitleLine() || row>iTitleRange.iTo.iRow) && row==iVisibleRange.iFrom.iRow)
			iVisibleRange.iFrom.iRow=aRow;
		}
	}

void CGridLay::PostCheckRowHeightChange(TInt aRow,TBool aNonZeroHeight)
	{
	if (!aNonZeroHeight)
		{
		if (IsHorizontalTitleLine() && aRow==iTitleRange.iFrom.iRow)
			StepRowForward(iTitleRange.iFrom.iRow);
		if (aRow==iVisibleRange.iFrom.iRow)
			StepRowForward(iVisibleRange.iFrom.iRow);
		}
	if (iGridImg)
		iGridImg->ResetReferencePoints();
	ResetVisibleToRow();
	iHasChanged=ETrue;
	}

EXPORT_C void CGridLay::SetRowHeightInTwipsL(TInt aRow,TInt aHeightInTwips)
//
// Similar to SetColumnWidthInTwipsL (remember this may be limited to the min row height)
//
/** Sets the height of the specified row.

Note that the height cannot be set smaller than the minimum defined row height.

@param aRow The number of row whose height is to be set.
@param aHeightInTwips The height of the row, in twips.
@see MinRowHeightInPixels() */
	{
	TInt heightInPixels=0;
	if (iGraphicsDeviceMap)
		{
		heightInPixels=iGraphicsDeviceMap->VerticalTwipsToPixels(aHeightInTwips);
		if (heightInPixels<iMinRowHeightInPixels)
			{
			heightInPixels=iMinRowHeightInPixels;
			aHeightInTwips=iGraphicsDeviceMap->VerticalPixelsToTwips(heightInPixels);
			}
		}
	PreCheckRowHeightChange(aRow,aHeightInTwips);
	iRowHeightMap->SetL(aRow,aHeightInTwips,heightInPixels);
	PostCheckRowHeightChange(aRow,aHeightInTwips);
	}

EXPORT_C TInt CGridLay::SetRowHeightInTwipsL(TInt aStartRow,TInt aEndRow,TInt aHeightInTwips)
/** Sets the heights of all specified rows to the specified value.

@param aStartRow The first row whose height is to be set.
@param aEndRow The last row whose height is to be set.
@param aHeightInTwips The height of the rows, in twips. Note that if the specified 
rows span the whole grid, then the function sets this value as the default 
height of all rows through a call to SetDefaultRowHeightInTwips().
@return KErrNone if successful; KErrTooBig if the difference between the two 
row numbers is greater than EMaxArrayChanges. */
	{
	if (aStartRow==iGridRange.iFrom.iRow && aEndRow==iGridRange.iTo.iRow)
		{
		SetRowHeightsToDefault();
		SetDefaultRowHeightInTwips(aHeightInTwips);
		}
	else if (aEndRow-aStartRow>EMaxArrayChanges)
		return KErrTooBig;
	else
		{
		for (;aStartRow<=aEndRow;aStartRow++)
			SetRowHeightInTwipsL(aStartRow,aHeightInTwips);
		}
	iHasChanged=ETrue;
	return KErrNone;
	}

EXPORT_C TInt CGridLay::MinRowHeightInPixels() const
/** Gets the minimum height of rows.

@return The minimum height of rows, in pixels. */
	{
	return iMinRowHeightInPixels;
	}

EXPORT_C void CGridLay::SetMinRowHeightInPixels(TInt aHeightInPixels)
/** Sets the minimum height of rows.

@param aHeightInPixels The minimum height of rows, in pixels. */
	{
	iMinRowHeightInPixels=aHeightInPixels;
	iHasChanged=ETrue;
	}

TInt CGridLay::DefaultRowHeightInPixels() const
	{
	return iRowHeightMap->DefaultValueInPixels();
	}

EXPORT_C TInt CGridLay::DefaultRowHeightInTwips() const
/** Gets the default height of rows.

@return The default height of rows, in twips, */
	{
	return iRowHeightMap->DefaultValueInTwips();
	}

void CGridLay::SetDefaultRowHeightInPixels(TInt aHeightInPixels)
//
// Remember this may be limited to the min row height
	{
	if (aHeightInPixels==0)
		return;
	__ASSERT_DEBUG(iGraphicsDeviceMap!=NULL,Panic(EGridNullGraphicsDeviceMap));
	aHeightInPixels=Max(aHeightInPixels,iMinRowHeightInPixels);
	iRowHeightMap->SetDefaultValueInPixels(aHeightInPixels);
	iRowHeightMap->SetDefaultValueInTwips(iGraphicsDeviceMap->VerticalPixelsToTwips(aHeightInPixels));
	if (iGridImg)
		iGridImg->ResetReferencePoints();
	ResetVisibleToRow();
	iHasChanged=ETrue;
	}

EXPORT_C void CGridLay::SetDefaultRowHeightInTwips(TInt aHeightInTwips)
/** Sets the default height of rows.

Note that the height cannot be set smaller than the minimum defined row height.

@param aHeightInTwips The height of rows, in twips.
@see SetMinRowHeightInPixels()
@see MinRowHeightInPixels() */
	{
	if (aHeightInTwips==0)
		return;
	if (iGraphicsDeviceMap)
		{
		TInt heightInPixels=iGraphicsDeviceMap->VerticalTwipsToPixels(aHeightInTwips);
		if (heightInPixels<iMinRowHeightInPixels)
			{
			heightInPixels=iMinRowHeightInPixels;
			aHeightInTwips=iGraphicsDeviceMap->VerticalPixelsToTwips(heightInPixels);
			}
		iRowHeightMap->SetDefaultValueInPixels(heightInPixels);
		}
	iRowHeightMap->SetDefaultValueInTwips(aHeightInTwips);
	if (iGridImg)
		iGridImg->ResetReferencePoints();
	ResetVisibleToRow();
	iHasChanged=ETrue;
	}

EXPORT_C void CGridLay::SetRowHeightsToDefault()
/** Sets the heights of all rows to the default value.

@see SetDefaultRowHeightInTwips() */
	{
	iRowHeightMap->ResetArray();
	if (iGridImg)
		iGridImg->ResetReferencePoints();
	ResetVisibleToRow();
	iHasChanged=ETrue;
	}

EXPORT_C TInt CGridLay::RowHeightOfSelectedInTwips() const
/** Gets the height of rows in the selected region.

@return The row height, in twips, if all rows in the selected region have 
the same width; -1, otherwise.
@panic GRIDIMG 3 If this grid layout object has no grid image object. */
	{
	__ASSERT_DEBUG(iGridImg!=NULL,Panic(EGridLayInvalidGridImg));
	if (IsUniformRowHeight())
		return DefaultRowHeightInTwips();
	const CGridCellRegion* selected=iGridImg->Selected();
	TInt count=selected->Count();
	if (!count)
		return RowHeightInTwips(iGridImg->CursorPos().iRow);
	if (selected->IsAnyColSelected())
		return iRowHeightMap->Count() ? -1 : DefaultRowHeightInTwips();

	TInt height=RowHeightInTwips((*selected)[count-1].iFrom.iRow);
	for (TInt ii=0;ii<count;ii++)
		{
		TRangeRef range=(*selected)[ii];
		for (;range.iFrom.iRow<=range.iTo.iRow;range.iFrom.iRow++)
			{
			if (RowHeightInTwips(range.iFrom.iRow)!=height)
				return -1; //Inconsistent heights
			}
		}
	return height;
	}

EXPORT_C void CGridLay::SetRowHeightOfSelectedInTwipsL(TInt aHeightInTwips)
/** Sets the heights of all rows in the selected region to the specified value.

@param aHeightInTwips The row height, in twips.
@panic GRIDIMG 3 If this grid layout object has no grid image object. */
	{
	__ASSERT_DEBUG(iGridImg!=NULL,Panic(EGridLayInvalidGridImg));
	const CGridCellRegion* selected=iGridImg->Selected();
	if (selected->IsAnyColSelected() || IsUniformRowHeight())
		{
		iRowHeightMap->ResetArray();
		SetDefaultRowHeightInTwips(aHeightInTwips);
		}
	else
		{
		TInt count=selected->Count();
		if (!count)
			SetRowHeightInTwipsL(iGridImg->CursorPos().iRow,aHeightInTwips);
		for (TInt ii=0;ii<count;ii++)
			{
			TRangeRef range=(*selected)[ii];
			if ((range.iTo.iRow-range.iFrom.iRow)>EMaxArrayChanges)
				continue;
			for (;range.iFrom.iRow<=range.iTo.iRow;range.iFrom.iRow++)
				SetRowHeightInTwipsL(range.iFrom.iRow,aHeightInTwips);
			}
		}
	iHasChanged=ETrue;
	NotifyPaginationOutOfDateL();
	}

EXPORT_C void CGridLay::RecalcPixelSparseMaps()
/** Recalculates the internal maps that map row and column numbers to heights and 
widths respectively.

Heights and widths are held as both pixel and twip values. */
	{
	if (!iGraphicsDeviceMap)
		{
		const TInt KArbitraryNonZeroValue = 100;
		iColumnWidthMap->SetDefaultValueInPixels(KArbitraryNonZeroValue);	// Must be non-zero else get divide by zero errors
		iRowHeightMap->SetDefaultValueInPixels(KArbitraryNonZeroValue);
		return;
		}
	TInt defValueInTwips=iColumnWidthMap->DefaultValueInTwips();
	TInt defValueInPixels=iGraphicsDeviceMap->HorizontalTwipsToPixels(defValueInTwips);
	if (defValueInPixels==0)
		defValueInPixels=1;		// cannot be zero
	iColumnWidthMap->SetDefaultValueInPixels(defValueInPixels);
	TInt end=iColumnWidthMap->Count();
	{for (TInt ii=0;ii<end;ii++)
		{
		TSizeElement& element=(*iColumnWidthMap)[ii];
		element.iValueInPixels=iGraphicsDeviceMap->HorizontalTwipsToPixels(element.iValueInTwips);
		}}

	defValueInTwips=iRowHeightMap->DefaultValueInTwips();
	defValueInPixels=iGraphicsDeviceMap->VerticalTwipsToPixels(defValueInTwips);
	if (defValueInPixels==0)
		defValueInPixels=1;
	iRowHeightMap->SetDefaultValueInPixels(defValueInPixels);
	end=iRowHeightMap->Count();
	for (TInt ii=0;ii<end;ii++)
		{
		TSizeElement& element=(*iRowHeightMap)[ii];
		element.iValueInPixels=iGraphicsDeviceMap->VerticalTwipsToPixels(element.iValueInTwips);
		}
	}

EXPORT_C void CGridLay::InsertDeleteColumns(TInt aStartCol,TInt aNoOfCols,TFixGridRange aFixGridRange)
/** Inserts or deletes columns.

Insertion causes columns to be inserted in front of the specified start column. 
Deletion causes columns in front of the specified columns to be deleted.

@param aStartCol The start column.
@param aNoOfCols The number of columns to be inserted or deleted. A positive 
number means that columns are to be inserted; a negative number means that 
columns are to be deleted.
@param aFixGridRange Indicates whether the grid boundary is to be adjusted 
by the number of columns (increased or decreased). */
	{
	if (aNoOfCols==0)
		return;
	if (aFixGridRange==EAdjustGridRange)
		iGridRange.iTo.iCol+=aNoOfCols;
	iColumnWidthMap->OpenCloseGap(aStartCol,aNoOfCols,iGridRange.iTo.iCol);
	if (iGridImg)
		{
		iGridImg->ResetReferencePoints();
		ResetVisibleToColumn();
		if (aFixGridRange==EAdjustGridRange)
			iGridImg->NotifyGridRangeResize();
		}
	iHasChanged=ETrue;
	}

EXPORT_C void CGridLay::InsertDeleteRows(TInt aStartRow,TInt aNoOfRows,TFixGridRange aFixGridRange)
/** Inserts or deletes rows.

Insertion causes rows to be inserted below the specified start row. Deletion 
causes rows below the specified row to be deleted.

@param aStartRow The start row.
@param aNoOfRows The number of rows to be inserted or deleted. A positive number 
means that rows are to be inserted; a negative number means that rows are 
to be deleted.
@param aFixGridRange Indicates whether the grid boundary is to be adjusted 
by the number of rows (increased or decreased). */
	{
	if (aNoOfRows==0)
		return;
	if (aFixGridRange==EAdjustGridRange)
		iGridRange.iTo.iRow+=aNoOfRows;
	iRowHeightMap->OpenCloseGap(aStartRow,aNoOfRows,iGridRange.iTo.iRow);
	if (iGridImg)
		{
		iGridImg->ResetReferencePoints();
		ResetVisibleToRow();
		if (aFixGridRange==EAdjustGridRange)
			iGridImg->NotifyGridRangeResize();
		}
	iHasChanged=ETrue;
	}

EXPORT_C void CGridLay::SetHorizontalGridLines(TBool aState)
/** Sets whether horizontal grid lines are to be drawn.

@param aState ETrue, if horizontal grid lines are to be drawn; EFalse, otherwise. */
	{
	if (aState)
		iFlags|=EIsHorizontalGridLines;
	else
		iFlags&=~EIsHorizontalGridLines;
	iHasChanged=ETrue;
	}

EXPORT_C void CGridLay::SetVerticalGridLines(TBool aState)
/** Sets whether vertical grid lines are to be drawn.

@param aState ETrue, if vertical grid lines are to be drawn; EFalse, otherwise. */
	{
	if (aState)
		iFlags|=EIsVerticalGridLines;
	else
		iFlags&=~EIsVerticalGridLines;
	iHasChanged=ETrue;
	}

EXPORT_C void CGridLay::SetSideLabels(TBool aState)
/** Sets whether side labels are printed.

@param aState ETrue, if side labels are printed; EFalse, otherwise. */
	{
	if (aState)
		iFlags|=EIsSideLabels;
	else
		iFlags&=~EIsSideLabels;
	if (iGridImg)
		{
		iGridImg->ResetReferencePoints();
		ResetVisibleToColumn();
		}
	iHasChanged=ETrue;
	}

EXPORT_C void CGridLay::SetTopLabels(TBool aState)
/** Sets whether top labels are printed.

@param aState ETrue, if top labels are printed; EFalse, otherwise. */
	{
	if (aState)
		iFlags|=EIsTopLabels;
	else
		iFlags&=~EIsTopLabels;
	if (iGridImg)
		{
		iGridImg->ResetReferencePoints();
		ResetVisibleToRow();
		}
	iHasChanged=ETrue;
	}

EXPORT_C void CGridLay::SetGridLabelSeparators(TBool aState)
/** Sets whether label separators are to be drawn.

@param aState ETrue, if label separators are to be drawn; EFalse, otherwise. */
	{
	if (aState)
		iFlags|=EIsGridLabelSeparators;
	else
		iFlags&=~EIsGridLabelSeparators;
	iHasChanged=ETrue;
	}

EXPORT_C void CGridLay::SetColumnBursting(TBool aState)
/** Sets whether column bursting is to be permitted.

Column bursting occurs when the contents of a cell are too wide; adjacent 
cells are then overwritten, provided they are empty.

@param aState ETrue, if column bursting is to be permitted; EFalse, otherwise. */
	{
	if (aState)
		iFlags|=EIsColumnBursting;
	else
		iFlags&=~EIsColumnBursting;
	iHasChanged=ETrue;
	}

EXPORT_C void CGridLay::SetCursorVisible(TBool aVisible)
/** Sets whether the cursor is to be visible.

@param aVisible ETrue, if the cursor is to be visible; EFalse, otherwise. */
	{
	if (aVisible)
		iFlags|=EIsCursorVisible;
	else
		iFlags&=~EIsCursorVisible;
	iHasChanged=ETrue;
	}

EXPORT_C void CGridLay::SetHighlightVisible(TBool aVisible)
/** Sets whether selected cells are to be highlighted.

@param aVisible ETrue, if selected cells are to be highlighted; EFalse, otherwise. */
	{
	if (aVisible)
		iFlags|=EIsHighlightVisible;
	else
		iFlags&=~EIsHighlightVisible;
	iHasChanged=ETrue;
	}

EXPORT_C void CGridLay::SetRowPermanentlySelectedL(TBool aState)
/** Sets whether rows are to be permanently selected.

@param aState ETrue, if rows are to be permanently selected; EFalse, otherwise. */
	{
	if (aState)
		iFlags|=EIsRowPermanentlySelected;
	else
		iFlags&=~EIsRowPermanentlySelected;
	if (aState && iGridImg)
		{
		CGridCellRegion* selected = (CGridCellRegion*)iGridImg->Selected(); //!! Bit naughty
		selected->Reset();
		selected->AddRowL(iGridImg->CursorPos().iRow);
		}
	iHasChanged=ETrue;
	}

EXPORT_C void CGridLay::SetTitleLinesL(TBool aState)
/** Sets whether the grid is to have both horizontal and vertical title lines.

@param aState ETrue, if the grid is to have both a horizontal and vertical 
title line; EFalse, otherwise. */
	{
	if (!(aState || IsTitleLines()))
		return;	//No change
	__ASSERT_DEBUG(iGridImg!=NULL,Panic(EGridLayInvalidGridImg));
	TCellRef cursorPos=(iGridImg->Selected()->Count()) ? iGridImg->AnchorPos() :
		iGridImg->CursorPos();
	if (aState)
		{
		SetTitleLinesL(cursorPos);
		}
	else
		{
		TCellRef cell=iVisibleRange.iFrom;
		if (IsHorizontalTitleLine())
			cell.iRow=iTitleRange.iTo.iRow;
		if (IsVerticalTitleLine())
			cell.iCol=iTitleRange.iTo.iCol;
		TPoint offset=ExposeCellToTopLeft(cell);
		iGridImg->ScrollL(offset);
		if (IsHorizontalTitleLine())
			iVisibleRange.iFrom.iRow=iTitleRange.iFrom.iRow;
		if (IsVerticalTitleLine())
			iVisibleRange.iFrom.iCol=iTitleRange.iFrom.iCol;
		iFlags&=~(EIsHorizontalTitleLine|EIsVerticalTitleLine);
		offset=iGridImg->MainPoint();	//Just using offset instead of creating a new TPoint
		iGridImg->ResetReferencePoints();
		iGridImg->ClearTitleLineRegionL(offset);
		}
	iHasChanged=ETrue;
	}

EXPORT_C void CGridLay::SetTitleLinesL(const TCellRef& aCellRef)
/** Sets horizontal and vertical title lines at the specified cell.

@param aCellRef The cell reference at which title lines are set.
@panic GRIDIMG 3 If this grid layout object has no grid image object. */
	{
	__ASSERT_DEBUG(iGridImg!=NULL,Panic(EGridLayInvalidGridImg));
	SetTitleLinesL(EFalse);		// must be cleared first
	if (aCellRef.iRow>iVisibleRange.iFrom.iRow && aCellRef.iRow<=iVisibleRange.iTo.iRow
		&& !IsIndefiniteRowBoundaries())
		{
		iFlags|=EIsHorizontalTitleLine;
		iTitleRange.iFrom.iRow=iVisibleRange.iFrom.iRow;
		iTitleRange.iTo.iRow=iVisibleRange.iFrom.iRow=aCellRef.iRow;
		}
	if (aCellRef.iCol>iVisibleRange.iFrom.iCol && aCellRef.iCol<=iVisibleRange.iTo.iCol)
		{
		iFlags|=EIsVerticalTitleLine;
		iTitleRange.iFrom.iCol=iVisibleRange.iFrom.iCol;
		iTitleRange.iTo.iCol=iVisibleRange.iFrom.iCol=aCellRef.iCol;
		}
	if (IsTitleLines())
		{
		iGridImg->ResetReferencePoints();
		iGridImg->DrawTitleLines();
		}
	iHasChanged=ETrue;
	}

EXPORT_C void CGridLay::ToggleTitleLinesL()
/** Sets title lines on, if they are off; sets title lines off, if they are on. */
	{
	SetTitleLinesL(!IsTitleLines());
	}

void CGridLay::SetIndefiniteRowBoundaries(TBool aState)
	{
	if (aState)
		iFlags|=EIsIndefiniteRowBoundaries;
	else
		iFlags&=~EIsIndefiniteRowBoundaries;
	iHasChanged=ETrue;
	}

EXPORT_C void CGridLay::SetUniformRowHeight(TBool aState)
/** Sets whether all rows are to have the same height.

@param aState ETrue, if all rows are to have the same height; EFalse, otherwise. */
	{
	if (aState)
		{
		iFlags|=EIsUniformRowHeight;
		SetRowHeightsToDefault();
		}
	else
		iFlags&=~EIsUniformRowHeight;
	iHasChanged=ETrue;
	}

EXPORT_C void CGridLay::SetUniformColumnWidth(TBool aState)
/** Sets whether all columns are to have the same width.

@param aState ETrue, if all columns are to have the same width; EFalse, otherwise. */
	{
	if (aState)
		{
		iFlags|=EIsUniformColumnWidth;
		SetColumnWidthsToDefault();
		}
	else
		iFlags&=~EIsUniformColumnWidth;
	iHasChanged=ETrue;
	}

EXPORT_C void CGridLay::SetTopLabelDragDisabled(TBool aState)
/** Sets whether a drag operation on the boundary between two columns is to be 
permitted.

@param aState ETrue, if the drag operation is to be permitted; EFalse, otherwise. */
	{
	if (aState)
		iFlags|=EIsTopLabelDragDisabled;
	else
		iFlags&=~EIsTopLabelDragDisabled;
	iHasChanged=ETrue;
	}

EXPORT_C void CGridLay::SetSideLabelDragDisabled(TBool aState)
/** Sets whether a drag operation on the boundary between two rows is to be permitted.

@param aState ETrue, if the drag operation is to be permitted; EFalse, otherwise. */
	{
	if (aState)
		iFlags|=EIsSideLabelDragDisabled;
	else
		iFlags&=~EIsSideLabelDragDisabled;
	iHasChanged=ETrue;
	}

EXPORT_C void CGridLay::SetPrintedLabels(TBool aState)
/** Sets whether labels are printed.

@param aState ETrue if labels are printed; EFalse, otherwise. */
	{
	if (aState)
		iFlags|=EIsPrintedLabels;
	else
		iFlags&=~EIsPrintedLabels;
	iHasChanged=ETrue;
	}

EXPORT_C void CGridLay::SetPrintedGridLines(TBool aState)
/** Sets whether grid lines are printed.

@param aState ETrue if grid lines are printed; EFalse, otherwise. */
	{
	if (aState)
		iFlags|=EIsPrintedGridLines;
	else
		iFlags&=~EIsPrintedGridLines;
	iHasChanged=ETrue;
	}

void CGridLay::SetVisibleToRowFullyVisible(TBool aState)
	{
	if (aState)
		iFlags|=EIsVisibleToRowFullyVisible;
	else
		iFlags&=~EIsVisibleToRowFullyVisible;
	}

void CGridLay::SetVisibleToColumnFullyVisible(TBool aState)
	{
	if (aState)
		iFlags|=EIsVisibleToColumnFullyVisible;
	else
		iFlags&=~EIsVisibleToColumnFullyVisible;
	}

EXPORT_C void CGridLay::SetEncroachingCellBorders(TBool aState)
/** Sets whether encroaching cell borders are permitted.

Encroaching cell borders are where cell borders wider than one pixel are drawn 
inside the cell, as opposed to outside.

@param aState ETrue, if encroaching cells borders are to be permitted; EFalse, 
otherwise. */
	{
	if (aState)
		iFlags|=EIsEncroachingCellBorders;
	else 
		iFlags&=~EIsEncroachingCellBorders;
	iHasChanged=ETrue;
	}

EXPORT_C void CGridLay::SetRowSelectionDisabled(TBool aState)
/** Sets whether row selection is disabled.

@param aState ETrue, if row selection is disabled; EFalse, otherwise. */
	{
	if (aState)
		iFlags|=EIsRowSelectionDisabled;
	else
		iFlags&=~EIsRowSelectionDisabled;
	iHasChanged=ETrue;
	}

EXPORT_C void CGridLay::SetColumnSelectionDisabled(TBool aState)
/** Sets whether column selection is disabled.

@param aState ETrue, if column selection is disabled; EFalse, otherwise. */
	{
	if (aState)
		iFlags|=EIsColumnSelectionDisabled;
	else
		iFlags&=~EIsColumnSelectionDisabled;
	iHasChanged=ETrue;
	}

EXPORT_C void CGridLay::SetAutoClearGridCells(TBool aState)
/** Sets whether automatic clearing of grid cells is to be done.

@param aState ETrue, if automatic clearing of grid cells is to be done; EFalse, 
otherwise. */
	{
	if (aState)
		iFlags|=EIsAutoClearGridCells;
	else
		iFlags&=~EIsAutoClearGridCells;
	iHasChanged=ETrue;
	}

EXPORT_C void CGridLay::SetPageBreakLinesHidden(TBool aState)
/** Sets whether lines marking page breaks are hidden.

@param aState ETrue, if lines marking page breaks are hidden; EFalse, otherwise. */
	{
	if (aState)
		iFlags|=EIsPageBreakLinesHidden;
	else
		iFlags&=~EIsPageBreakLinesHidden;
	iHasChanged=ETrue;
	}

EXPORT_C TInt CGridLay::RowToYVal(TInt aRow) const
/** Converts the specified row number to a screen y-coordinate value.

Note that the resulting value may be outside the current grid window.

@param aRow The row number.
@return The y-coordinate value. */
	{
	__ASSERT_DEBUG(iGridImg!=NULL,Panic(EGridLayInvalidGridImg));
	TInt disp;
	iRowHeightMap->IdToDisplacement(iVisibleRange.iFrom.iRow,aRow,disp);
	return (iGridImg->MainPoint().iY+disp);
	}

EXPORT_C TInt CGridLay::RowToYVal(TInt aStartRow,TInt aEndRow) const
/** Calculates the relative pixel distance between the two specified rows.

@param aStartRow The row number of the first row.
@param aEndRow The row number of the second row.
@return The relative pixel distance. */
	{
	TInt disp;
	iRowHeightMap->IdToDisplacement(aStartRow,aEndRow,disp);
	return disp;
	}

EXPORT_C TInt CGridLay::VisibleRowToYVal(TInt aRow) const
/** Converts the specified visible row number to a screen y-coordinate value.

Note that the resulting value may be outside the current grid window.

@param aRow The row number of the visible row.
@return The y-coordinate value. Note that this is -1, if the row is not visible. */
	{
	if (aRow>iVisibleRange.iTo.iRow)
		return -1;
	if (aRow<iVisibleRange.iFrom.iRow)
		{
		if (IsHorizontalTitleLine())
			{
			if (aRow<iTitleRange.iFrom.iRow || aRow>=iTitleRange.iTo.iRow)
				return -1;
			return TitleRowToYVal(aRow);
			}
		return -1;
		}
	return RowToYVal(aRow);
	}

EXPORT_C TInt CGridLay::TitleRowToYVal(TInt aTitleRow) const
/** Calculates the relative pixel distance between the specified row and the first 
title row.

@param aTitleRow The row number.
@return The relative pixel distance. */
	{
	__ASSERT_DEBUG(IsHorizontalTitleLine(),Panic(EGridLayNoTitles));
	__ASSERT_DEBUG(iGridImg!=NULL,Panic(EGridLayInvalidGridImg));
	TInt disp;
	iRowHeightMap->IdToDisplacement(iTitleRange.iFrom.iRow,aTitleRow,disp);
	return (iGridImg->TitlePoint().iY+disp);
	}

EXPORT_C TInt CGridLay::ColumnToXVal(TInt aCol) const
/** Converts the specified column number to a screen x-coordinate value.

Note that the resulting value may be outside the current grid window.

@param aCol The column number.
@return The column's x-coordinate value.
@panic GRIDIMG 3 In debug mode, if this grid layout object has no grid image. */
	{
	//
	// Converts the passed column to a relative screen 'X' coordinate.
	//
	__ASSERT_DEBUG(iGridImg!=NULL,Panic(EGridLayInvalidGridImg));
	TInt disp;
	iColumnWidthMap->IdToDisplacement(iVisibleRange.iFrom.iCol,aCol,disp);
	return (iGridImg->MainPoint().iX+disp);
	}

EXPORT_C TInt CGridLay::ColumnToXVal(TInt aStartCol,TInt aEndCol) const
/** Gets the distance, in pixels, between the two specified columns.

@param aStartCol The first (start) column number.
@param aEndCol The second (end) column number.
@return The distance, in pixels. */
	{
	TInt disp;
	iColumnWidthMap->IdToDisplacement(aStartCol,aEndCol,disp);
	return disp;
	}

EXPORT_C TInt CGridLay::VisibleColumnToXVal(TInt aCol) const
/** Converts the specified visible column number to a screen x-coordinate value.

Note that the resulting value may be outside the current grid window.

@param aCol The column number of the visible column.
@return The x-coordinate value. Note that this is -1, if the column is not 
visible. */
	{
	if (aCol>iVisibleRange.iTo.iCol)
		return -1;
	if (aCol<iVisibleRange.iFrom.iCol)
		{
		if (IsVerticalTitleLine())
			{
			if (aCol<iTitleRange.iFrom.iCol || aCol>=iTitleRange.iTo.iCol)
				return -1;
			return TitleColumnToXVal(aCol);
			}
		return -1;
		}
	return ColumnToXVal(aCol);
	}

EXPORT_C TInt CGridLay::TitleColumnToXVal(TInt aTitleCol) const
/** Calculates the relative pixel distance between the specified column and the 
first title column.

@param aTitleCol The column number.
@return The relative pixel distance. */
	{
	__ASSERT_DEBUG(IsVerticalTitleLine(),Panic(EGridLayNoTitles));
	__ASSERT_DEBUG(iGridImg!=NULL,Panic(EGridLayInvalidGridImg));
	TInt disp;
	iColumnWidthMap->IdToDisplacement(iTitleRange.iFrom.iCol,aTitleCol,disp);
	return (iGridImg->TitlePoint().iX+disp);
	}

EXPORT_C TPoint CGridLay::CellToPoint(const TCellRef &aCell) const
/** Gets the relative screen coordinates of the top left corner of the specified 
cell.

@param aCell The cell.
@return The relative screen co-ordinates. */
	{
	return TPoint(ColumnToXVal(aCell.iCol),RowToYVal(aCell.iRow));
	}

EXPORT_C TPoint CGridLay::CellToPoint(const TCellRef &aStartCell,const TCellRef &aEndCell) const
/** Gets the co-ordinate distance, in pixels, between the specified cells.

@param aStartCell The start cell of the range.
@param aEndCell The end cell of the range.
@return The x and y values representing the distance, in pixels, between the 
two columns and the two rows, respectively, that are defined by the two cells. */
	{
	return TPoint(ColumnToXVal(aStartCell.iCol,aEndCell.iCol),RowToYVal(aStartCell.iRow,aEndCell.iRow));
	}

EXPORT_C TPoint CGridLay::TitleCellToPoint(const TCellRef& aTitleCell) const
/** Gets the relative screen coordinates of the top left corner of the specified 
cell, when title lines are displayed.

@param aTitleCell The cell.
@return The relative screen co-ordinates.
@panic GRIDIMG 3 In debug mode, if this grid layout object has no grid image.
@panic GRIDIMG 4 In debug mode, if there is no horizontal title line and/or 
there is no vertical title line. */
	{
	__ASSERT_DEBUG(IsHorizontalTitleLine(),Panic(EGridLayNoTitles));
	__ASSERT_DEBUG(IsVerticalTitleLine(),Panic(EGridLayNoTitles));
	__ASSERT_DEBUG(iGridImg!=NULL,Panic(EGridLayInvalidGridImg));
	TPoint point;
	iColumnWidthMap->IdToDisplacement(iTitleRange.iFrom.iCol,aTitleCell.iCol,point.iX);
	iRowHeightMap->IdToDisplacement(iTitleRange.iFrom.iRow,aTitleCell.iRow,point.iY);
	return point+iGridImg->TitlePoint();
	}

EXPORT_C TRect CGridLay::CellToRect(const TCellRef& aCell) const
/** Gets the rectangle that is occupied by the specified cell.

@param aCell The cell.
@return The occupied rectangle. Note that this excludes the cell's bottom and 
right grid lines. */
	{
	TRect rect(CellToPoint(aCell),TSize(0,0));
	rect.iBr.iX+=ColumnWidthInPixels(aCell.iCol)-1;
	rect.iBr.iY+=RowHeightInPixels(aCell.iRow)-1;
	return rect;
	}

EXPORT_C TInt CGridLay::YValToRow(TInt aYVal) const
/** Gets the number of the row, limited to the grid boundary, that is on or above 
the specified y-coordinate value.

@param aYVal The y-coordinate value. Note that this may represent a point 
off the visible screen.
@return The row number, limited to the grid boundary. */
	{
	__ASSERT_DEBUG(iGridImg!=NULL,Panic(EGridLayInvalidGridImg));
	TInt tempYVal = iGridImg->MainPoint().iY;
	return YValToRow(iVisibleRange.iFrom.iRow,aYVal-tempYVal);
	}

EXPORT_C TInt CGridLay::YValToRow(TInt aStartRow,TInt aDisp) const
/** Gets the number of the row that is on or above the specified displacement from 
the specified row.

@param aStartRow The row from which displacement is calculated.
@param aDisp The displacement, in pixels.
@return The row number at the specified displacement. */
	{
	TInt row;
	iRowHeightMap->DisplacementToId(aStartRow,aDisp,row);
	StepRowBackward(row);
	return(row);
	}

EXPORT_C TInt CGridLay::YValToTitleRow(TInt aYVal) const
/** Gets the number of the row that is on or above the specified y-coordinate value

@param aYVal The y-coordinate value. Note that this may represent a point 
off the visible screen.
@return The row number. Note that this may include the title row. */
	{
	__ASSERT_DEBUG(IsHorizontalTitleLine(),Panic(EGridLayNoTitles));
	__ASSERT_DEBUG(iGridImg!=NULL,Panic(EGridLayInvalidGridImg));
	TInt tempYVal = iGridImg->TitlePoint().iY;
	return YValToRow(iTitleRange.iFrom.iRow,aYVal-tempYVal);
	}

EXPORT_C TInt CGridLay::XValToColumn(TInt aXVal) const
/** Gets the number of the column, limited to the grid boundary, that is on or 
to the left of the specified x-coordinate value.

@param aXVal The x-coordinate value. Note that this may represent a point 
off the visible screen.
@return The column number, limited to the grid boundary. */
	{
	__ASSERT_DEBUG(iGridImg!=NULL,Panic(EGridLayInvalidGridImg));
	TInt tempXVal=iGridImg->MainPoint().iX;
	return XValToColumn(iVisibleRange.iFrom.iCol,aXVal-tempXVal);
	}

EXPORT_C TInt CGridLay::XValToColumn(TInt aStartCol,TInt aDisp) const
/** Gets the number of the column that is on or to the left of the specified displacement 
from the specified column.

@param aStartCol The column from which displacement is calculated.
@param aDisp The displacement, in pixels.
@return The column number at the specified displacement. */
	{
	TInt column;
	iColumnWidthMap->DisplacementToId(aStartCol,aDisp,column);
	StepColumnBackward(column);
	return(column);
	}

EXPORT_C TInt CGridLay::XValToTitleColumn(TInt aXVal) const
/** Gets the number of the column that is on or to the left of the specified x-coordinate 
value

@param aXVal The x-coordinate value. Note that this may represent a point 
off the visible screen.
@return The column number. Note that this may include the title column. */
	{
	__ASSERT_DEBUG(IsVerticalTitleLine(),Panic(EGridLayNoTitles));
	__ASSERT_DEBUG(iGridImg!=NULL,Panic(EGridLayInvalidGridImg));
	TInt tempXVal=iGridImg->TitlePoint().iX;
	return XValToColumn(iTitleRange.iFrom.iCol,aXVal-tempXVal);
	}

EXPORT_C TCellRef CGridLay::PointToCell(const TPoint &aPoint) const
/** Gets the cell reference of the cell that contains the specified screen co-ordinates.

@param aPoint The screen co-ordinates.
@return The cell reference. */
	{
	return TCellRef(YValToRow(aPoint.iY),XValToColumn(aPoint.iX));
	}

EXPORT_C TCellRef CGridLay::PointToCell(const TCellRef &aStartCell,const TPoint &aPointDisp) const
/** Gets the cell reference of the cell that is displaced from the specified cell 
by the specified pixel co-ordinates.

@param aStartCell The cell reference from which the displacement is based.
@param aPointDisp The displacement.
@return The cell at the specified displacement. */
	{
	return TCellRef(YValToRow(aStartCell.iRow,aPointDisp.iY),XValToColumn(aStartCell.iCol,aPointDisp.iX));
	}

EXPORT_C TSize CGridLay::TopLeftTitleRangeSize() const
/** Gets the size of the top left range, if title lines are on.

The top left range is the range of cells formed by the intersection of the 
rows and columns that form the titles.

@return The size of the top left range. */
	{
	TSize ret;
	if (IsHorizontalTitleLine())
		iRowHeightMap->IdToDisplacement(iTitleRange.iFrom.iRow,iTitleRange.iTo.iRow,ret.iHeight);
	if (IsVerticalTitleLine())
		iColumnWidthMap->IdToDisplacement(iTitleRange.iFrom.iCol,iTitleRange.iTo.iCol,ret.iWidth);
	return ret;
	}

EXPORT_C TInt CGridLay::YValToNearestRow(TInt aStartRow,TInt aDisp) const
/** Gets the row that is nearest to the specified displacement from the specified 
row.

@param aStartRow The row on which the displacement is based.
@param aDisp The displacement value, in pixels.
@return The nearest row. */
	{
	TInt topRow;
	iRowHeightMap->DisplacementToId(aStartRow,aDisp,topRow);
	StepRowForward(topRow);
	TInt topYVal;
	iRowHeightMap->IdToDisplacement(aStartRow,topRow,topYVal);
	TInt bottomYVal = topYVal+RowHeightInPixels(topRow);
	if ((aDisp-topYVal)>=(bottomYVal-aDisp))
		StepRowForward(++topRow);
	return (topRow);
	}

EXPORT_C TInt CGridLay::XValToNearestColumn(TInt aStartCol,TInt aDisp) const
/** Gets the column that is nearest to the specified displacement from the specified 
column.

@param aStartCol The column on which the displacement is based.
@param aDisp The displacement value, in pixels.
@return The nearest column. */
	{
	TInt leftCol;
	iColumnWidthMap->DisplacementToId(aStartCol,aDisp,leftCol);
	StepColumnForward(leftCol);
	TInt leftXVal;
	iColumnWidthMap->IdToDisplacement(aStartCol,leftCol,leftXVal);
	TInt rightXVal = leftXVal+ColumnWidthInPixels(leftCol);
	if ((aDisp-leftXVal)>=(rightXVal-aDisp))
		StepColumnForward(++leftCol);
	return (leftCol);
	}

TPoint CGridLay::CalcOffsetBetweenCells(const TCellRef& aCell1,
	const TCellRef& aCell2) const
//
// Returns the scrolling offset required to get from aCell1 to aCell2
	{
	TPoint offset;
	iColumnWidthMap->IdToDisplacement(aCell2.iCol,aCell1.iCol,offset.iX);
	iRowHeightMap->IdToDisplacement(aCell2.iRow,aCell1.iRow,offset.iY);
	return offset;
	}

TInt CGridLay::CalcVisibleFromRowAfterPageScroll(TMoveDirectionAndAmount aPageScroll) const
//
// Calculates what iVisibleRange.iFrom.iRow would be after aPageScroll but doesn't actually set it
	{
	TInt newFromRow;
	switch (aPageScroll)
		{
	case EMovePageDown:
		CalcVisibleFromRow(iVisibleRange.iFrom.iRow+1,newFromRow);
		if (newFromRow>iVisibleRange.iFrom.iRow)
			newFromRow=iVisibleRange.iFrom.iRow;
		break;
	case EMovePageUp:
		{
		TInt corr=IsVisibleToRowFullyVisible() ? 0 : 1;
		corr=(CalcVisibleToRow(iVisibleRange.iTo.iRow-corr,newFromRow))	? 1 : 0;	// correct if fully visible
		if (newFromRow == iVisibleRange.iTo.iRow)
			newFromRow = iVisibleRange.iTo.iRow - 1;
		else
			CalcVisibleFromRow(newFromRow+corr,newFromRow);
		if (newFromRow<iVisibleRange.iFrom.iRow)
			newFromRow=iVisibleRange.iFrom.iRow;
		}
		break;
	default:
		newFromRow=iVisibleRange.iFrom.iRow;
		break;
		}
	return newFromRow;
	}

TInt CGridLay::CalcVisibleFromColumnAfterPageScroll(TMoveDirectionAndAmount aPageScroll) const
	{
	TInt newFromColumn;
	switch (aPageScroll)
		{
	case EMovePageRight:
		CalcVisibleFromColumn(iVisibleRange.iFrom.iCol+1,newFromColumn);
		if (newFromColumn>iVisibleRange.iFrom.iCol)
			newFromColumn=iVisibleRange.iFrom.iCol;
		break;
	case EMovePageLeft:
		{
		TInt corr=IsVisibleToColumnFullyVisible() ? 0 : 1;
		corr=(CalcVisibleToColumn(iVisibleRange.iTo.iCol-corr,newFromColumn)) ? 1 : 0;
		if (newFromColumn == iVisibleRange.iTo.iCol)
			newFromColumn = iVisibleRange.iTo.iCol - 1;
		else
			CalcVisibleFromColumn(newFromColumn+corr,newFromColumn);
		if (newFromColumn<iVisibleRange.iFrom.iCol)
			newFromColumn=iVisibleRange.iFrom.iCol;
		}
		break;
	default:
		newFromColumn=iVisibleRange.iFrom.iCol;
		break;
		}
	return newFromColumn;
	}

TCellRef CGridLay::CalcVisibleFromCellAfterPageScroll(TMoveDirectionAndAmount aPageScroll) const
	{
	return TCellRef(CalcVisibleFromRowAfterPageScroll(aPageScroll),
		CalcVisibleFromColumnAfterPageScroll(aPageScroll));
	}

void CGridLay::CalcVisibleFromRow(TInt aVisibleToRow,TInt& aNewVisibleFromRow) const
	{
	//
	// Calculates what the VisibleRange.iFrom.iRow would be for a given
	// VisibleRange.iTo.iRow.
	//
	__ASSERT_DEBUG(iGridImg!=NULL,Panic(EGridLayInvalidGridImg));
	TInt disp=-iGridImg->MainRect().Height()-1;
	iRowHeightMap->DisplacementToId(aVisibleToRow,disp,aNewVisibleFromRow);
	aNewVisibleFromRow++;
	if (IsIndefiniteRowBoundaries())
		{
		if (!RequestRow(aNewVisibleFromRow,aNewVisibleFromRow))
			aNewVisibleFromRow=aVisibleToRow;
		}
	else
		aNewVisibleFromRow=Max(aNewVisibleFromRow,MinVisibleFromRow());
	StepRowForward(aNewVisibleFromRow);
	}

TBool CGridLay::CalcVisibleToRow(TInt aVisibleFromRow,TInt& aNewVisibleToRow) const
	{
	__ASSERT_DEBUG(iGridImg!=NULL,Panic(EGridLayInvalidGridImg));
	TInt disp=iGridImg->MainRect().Height()+1;
	TBool isExactDisp=iRowHeightMap->DisplacementToId(aVisibleFromRow,disp,aNewVisibleToRow);
	if (isExactDisp)
		aNewVisibleToRow--;
	if (IsIndefiniteRowBoundaries())
		{
		if (RequestRow(TInt(aNewVisibleToRow-1),aNewVisibleToRow))
			aNewVisibleToRow++;
		else
			aNewVisibleToRow=aVisibleFromRow;
		}
	else
		aNewVisibleToRow=Min(aNewVisibleToRow,iGridRange.iTo.iRow+1);
	return isExactDisp;
	}

void CGridLay::CalcVisibleFromColumn(TInt aVisibleToCol,TInt& aNewVisibleFromCol) const
	{
	//
	// Calculates what the VisibleRange.iFrom.iCol would be for a given
	// VisibleRange.iTo.iCol.
	//
	__ASSERT_DEBUG(iGridImg!=NULL,Panic(EGridLayInvalidGridImg));
	TInt disp=-iGridImg->MainRect().Width()-1;
	iColumnWidthMap->DisplacementToId(aVisibleToCol,disp,aNewVisibleFromCol);
	aNewVisibleFromCol++;
	aNewVisibleFromCol=Max(aNewVisibleFromCol,MinVisibleFromColumn());
	StepColumnForward(aNewVisibleFromCol);	//Guarantees to be on a non-zero width column
	}

TBool CGridLay::CalcVisibleToColumn(TInt aVisibleFromCol,TInt& aNewVisibleToCol) const
	{
	__ASSERT_DEBUG(iGridImg!=NULL,Panic(EGridLayInvalidGridImg));
	TInt disp=iGridImg->MainRect().Width()+1;
	TBool isExactDisp=iColumnWidthMap->DisplacementToId(aVisibleFromCol,disp,aNewVisibleToCol);
	if (isExactDisp)
		aNewVisibleToCol--;
	aNewVisibleToCol=Min(aNewVisibleToCol,iGridRange.iTo.iCol+1);
	return isExactDisp;
	}

EXPORT_C void CGridLay::ResetVisibleToRow()
//
// Resets iVisibleRange.iTo.iRow given iVisibleRange.iFrom.iRow.
/** Resets the row number of the row that should be visible at the bottom of the 
visible area of the grid. */
	{
	if (!iGridImg)
		return;
	TBool isExactDisp=CalcVisibleToRow(iVisibleRange.iFrom.iRow,iVisibleRange.iTo.iRow);
	SetVisibleToRowFullyVisible(isExactDisp);
	}

EXPORT_C void CGridLay::ResetVisibleToColumn()
/** Resets the column number of the column visible at the right of the visible 
area of the grid. */
	{
	if (!iGridImg)
		return;
	TBool isExactDisp=CalcVisibleToColumn(iVisibleRange.iFrom.iCol,iVisibleRange.iTo.iCol);
	SetVisibleToColumnFullyVisible(isExactDisp);
	}

EXPORT_C void CGridLay::ResetVisibleToCell()
/** Resets the row and column numbers visible at the bottom, and to the right, 
of the visible area of the grid. */
	{
	ResetVisibleToRow();
	ResetVisibleToColumn();
	}

TBool CGridLay::IsCellOutOfVisibleRange(const TCellRef &aCell) const
//
// Return ETrue if aCell is outside the visible grid (including title range)
	{
	if (aCell.iRow>=iVisibleRange.iTo.iRow || aCell.iCol>=iVisibleRange.iTo.iCol)
		return ETrue;
	if (aCell.iRow<iVisibleRange.iFrom.iRow)
		{
		TBool inRange=EFalse;
		if (IsHorizontalTitleLine())
			{
			if (aCell.iRow<iTitleRange.iTo.iRow && aCell.iRow>=iTitleRange.iFrom.iRow)
				inRange=ETrue;
			}
		if (!inRange)
			return ETrue;
		}
	if (aCell.iCol<iVisibleRange.iFrom.iCol)
		{
		TBool inRange=EFalse;
		if (IsVerticalTitleLine())
			{
			if (aCell.iCol<iTitleRange.iTo.iCol && aCell.iCol>=iTitleRange.iFrom.iCol)
				inRange=ETrue;
			}
		if (!inRange)
			return ETrue;
		}
	return EFalse;
	}

TBool CGridLay::IsCellOutOfGridRange(const TCellRef& aCell) const
// Similar to LimitCell but Doesn't alter aCell
	{
	TCellRef cell=aCell;
	return !LimitCell(cell);
	}

TBool CGridLay::LimitRow(TInt &aRow) const
	{
	TInt newRow;
	TBool ret=RequestRow(aRow,newRow);
	if (ret)
		{
		if (newRow<aRow)
			StepRowBackward(newRow);
		else if (newRow>aRow)
			StepRowForward(newRow);
		}
	aRow=newRow;
	return ret;
	}

TBool CGridLay::LimitColumn(TInt &aCol) const
	{
	if (iGridRange.iFrom.iCol>iGridRange.iTo.iCol)
		return EFalse;
	LimitColumn(aCol,iGridRange.iFrom.iCol,iGridRange.iTo.iCol);
	return ETrue;
 	}

void CGridLay::LimitRow(TInt& aRow,TInt aLowerLimit,TInt aUpperLimit) const
	{
	if (aRow>aUpperLimit)
		{
		aRow=aUpperLimit;
		StepRowBackward(aRow);
		}
	else if (aRow<aLowerLimit)
		{
		aRow=aLowerLimit;
		StepRowForward(aRow);
		}
	}

void CGridLay::LimitColumn(TInt& aCol,TInt aLowerLimit,TInt aUpperLimit) const
	{
 	if (aCol>aUpperLimit)
		{
		aCol=aUpperLimit;
		StepColumnBackward(aCol);
        if (aCol<aLowerLimit)
            aCol=aLowerLimit;
		}
	else if (aCol<aLowerLimit)
		{
		aCol=aLowerLimit;
		StepColumnForward(aCol);
        if (aCol>aUpperLimit)
            aCol=aUpperLimit;
		}
	}

TBool CGridLay::LimitCell(TCellRef &aCell) const
// Keeps the cell within the grid boundary. Returns EFalse if unable to do so
	{
	TBool canLimitRow=LimitRow(aCell.iRow);
	return (LimitColumn(aCell.iCol) && canLimitRow);
	}

/*EXPORT_C void CGridLay::LimitCell(TCellRef &aCell,const TRangeRef &aLimitRange) const
	{
	LimitRow(aCell.iRow,aLimitRange.iFrom.iRow,aLimitRange.iTo.iRow);
	LimitColumn(aCell.iCol,aLimitRange.iFrom.iCol,aLimitRange.iTo.iCol);
	}*/

void CGridLay::LimitRowToVisible(TInt& aRow) const
	{
	if (IsIndefiniteRowBoundaries())
		LimitRow(aRow);
	else
		{
		TInt minRow=MinVisibleFromRow();
		if (minRow>iGridRange.iTo.iRow)
			{
			aRow=minRow;
			return;
			}
		LimitRow(aRow,minRow,iGridRange.iTo.iRow);
		}
	}

void CGridLay::LimitColumnToVisible(TInt& aCol) const
	{
	TInt minCol=MinVisibleFromColumn();
	if (minCol>iGridRange.iTo.iCol)
		{
		aCol=minCol;
		return;
		}
	LimitColumn(aCol,minCol,iGridRange.iTo.iCol);
	}

void CGridLay::LimitCellToVisible(TCellRef& aCell) const
	{
	LimitRowToVisible(aCell.iRow);
	LimitColumnToVisible(aCell.iCol);
	}

void CGridLay::StepRowForward(TInt& aRow) const
// Steps row forward to the nearest non zero row
	{
	for (;!RowHeightInPixels(aRow);aRow++)
		;
	}

void CGridLay::StepRowBackward(TInt& aRow) const
	{
	for (;!RowHeightInPixels(aRow);aRow--)
		;
	}

void CGridLay::StepColumnForward(TInt& aCol) const
	{
	for (;!ColumnWidthInPixels(aCol);aCol++)
		;
	}

void CGridLay::StepColumnBackward(TInt& aCol) const
	{
	for (;!ColumnWidthInPixels(aCol);aCol--)
		;
	}

EXPORT_C TInt CGridLay::MinVisibleFromRow() const
/** Gets the number of the topmost row visible in the grid.

@return The row number if successful else KErrUnknown. */
	{
	TInt minRow;
	if (IsIndefiniteRowBoundaries())
		{
		if(!RequestRow(-KMaxTInt,minRow))	// Result is undefined if request row is false
			{
			return KErrUnknown;
			}
		}
	else
		minRow=(IsHorizontalTitleLine())?iTitleRange.iTo.iRow:iGridRange.iFrom.iRow;
	StepRowForward(minRow);
	return minRow;
	}

EXPORT_C TInt CGridLay::MinVisibleFromColumn() const
/** Gets the number of the leftmost column visible in the grid.

@return The column number. */
	{
	TInt minCol=(IsVerticalTitleLine())?iTitleRange.iTo.iCol:iGridRange.iFrom.iCol;
	StepColumnForward(minCol);
	return minCol;
	}

EXPORT_C void CGridLay::PaginateL()
/** Paginates the grid.

Note that when preparing the grid for printing using a CGridPrinter object, 
then use that object's CGridPrinter::PaginateL() function instead. */
	{
	if (IsPaginated() || !iGraphicsDeviceMap)
		return;
	__ASSERT_DEBUG(iRowPageMap==NULL && iColumnPageMap==NULL,Panic(EGridLayPageMapAlreadyExists));
	iRowPageMap = CSparseMap::NewL();
	iColumnPageMap = CSparseMap::NewL();

	__ASSERT_DEBUG(iPageSizeInTwips.iWidth!=0 && iPageSizeInTwips.iHeight!=0,
 		Panic(EGridLayNoPageSizeSet));
	TPoint pageSizeInPixels=iGraphicsDeviceMap->TwipsToPixels(iPageSizeInTwips.AsPoint());
	if (IsPrintedLabels())
		{
		__ASSERT_DEBUG(iGridImg!=NULL,Panic(EGridLayInvalidGridImg));
		if (IsSideLabels())
			pageSizeInPixels.iX-=iGridImg->MaxSideLabelWidthInPixels();
		if (IsTopLabels())
			pageSizeInPixels.iY-=iGridImg->TopLabelHeightInPixels();
		}
	DoMainPaginationLoopL(pageSizeInPixels.iX,iColumnWidthMap,iColumnPageMap,
		iHardColumnPageBreaks,iGridRange.iFrom.iCol);
	TInt startRow;
	if (RequestRow(-KMaxTInt,startRow))
		{
		DoMainPaginationLoopL(pageSizeInPixels.iY,iRowHeightMap,iRowPageMap,
			iHardRowPageBreaks,startRow);
		}
	iFlags|=EIsPaginated;
	iHasChanged=ETrue;
	}

void CGridLay::DoMainPaginationLoopL(TInt aPageSpan,CSparseMap* aCellSpanMap,CSparseMap* aPageMap,
	CArrayFix<TInt>* aHardPageBreaks,TInt aStartId)
	{
	__ASSERT_DEBUG(aCellSpanMap->DefaultValueInPixels(),Panic(EGridMapDefaultValueIsZero));
	TInt defIdsPerPage = aPageSpan/aCellSpanMap->DefaultValueInPixels();
	if (defIdsPerPage==0)
		defIdsPerPage=1;	// Should always print at least 1 row/column per page
	aPageMap->SetDefaultValueInPixels(defIdsPerPage);//!!!Misleading Units
	TInt softCount=aCellSpanMap->Count();
	TInt hardCount=aHardPageBreaks->Count();
	TInt currPage=0;
	TInt softPos=0;
	TInt hardPos=0;
	while (softPos<softCount || hardPos<hardCount)
		{
		TInt nextSoftId=(softPos<softCount) ? (*aCellSpanMap)[softPos].iId : KMaxTInt;
		if (aStartId>nextSoftId)
			{
			softPos++;
			continue;
			}
		TInt nextHardPb=(hardPos<hardCount) ? (*aHardPageBreaks)[hardPos] : KMaxTInt;
		TInt nextId=Min(nextSoftId,nextHardPb);
		TInt pageSteps=(nextId-aStartId)/defIdsPerPage;
		currPage+=pageSteps;
		aStartId+=(pageSteps*defIdsPerPage);
		TInt currIdsPerPage;
		if (nextId==nextHardPb)
			{
			if (nextId==aStartId)
				{
				hardPos++;
				continue;
				}
			currIdsPerPage=nextId-aStartId;
			hardPos++;
			if (nextId==nextSoftId)
				softPos++;
			}
		else
			{
			aCellSpanMap->DisplacementToId(aStartId,aPageSpan,currIdsPerPage);
			currIdsPerPage-=aStartId;
			if ((aStartId+currIdsPerPage)>nextHardPb)
				{
				currIdsPerPage=nextHardPb-aStartId;
				hardPos++;
				}
			if (currIdsPerPage==0)
				currIdsPerPage=1;
//			softPos++;
			}
		if (currIdsPerPage)
			{
			aPageMap->SetL(currPage,0/*NotUsed*/,currIdsPerPage);
			aStartId+=currIdsPerPage;
			currPage++;
			}
		}
	}

EXPORT_C void CGridLay::ClearPagination()
/** Marks the grid as unpaginated. */
	{
	delete iRowPageMap;
	iRowPageMap=NULL;
	delete iColumnPageMap;
	iColumnPageMap=NULL;
	iFlags&=~EIsPaginated;
	iHasChanged=ETrue;
	}

EXPORT_C void CGridLay::NotifyPaginationOutOfDateL()
/** Notifies this object that repagination must take place.

This function is called as a response to changes in the grid, such as a change 
in the page size, a change to the width of selected columns, the setting or 
removal of hard page breaks etc. */
	{
	if (IsPaginated())
		{
		ClearPagination();
		if (IsAutoPagination())
			PaginateL();
		}
	}

EXPORT_C TRangeRef CGridLay::PageToRange(TInt aPageNo,TPageOrder aPageOrder) const
/** Gets the range of cells that are on the specified page

@param aPageNo The page number. The first page is assumed to be page zero.
@param aPageOrder The page order.
@return The range of cells.
@panic GRIDIMG 5 In debug mode, if the grid has not been paginated. */
	{
	__ASSERT_DEBUG(IsPaginated(),Panic(EGridLayNotPaginated));
	TCellRef pageRef;
	TInt startRow;
	if (!RequestRow(-KMaxTInt,startRow))
		return TRangeRef();
	TInt rowExtent=RowExtent();
	TInt colExtent=ColumnExtent();
	if (aPageOrder==ERightThenDown)
		{
		TInt noOfHorzPages;
		iColumnPageMap->DisplacementToId(0,colExtent-1,noOfHorzPages);
		noOfHorzPages++;
		pageRef.iRow=aPageNo/noOfHorzPages;
		pageRef.iCol=aPageNo-(pageRef.iRow*noOfHorzPages);
		}
	else
		{
		TInt noOfVertPages;
		iRowPageMap->DisplacementToId(0,rowExtent-1,noOfVertPages);
		noOfVertPages++;
		pageRef.iCol=aPageNo/noOfVertPages;
		pageRef.iRow=aPageNo-(pageRef.iCol*noOfVertPages);
		}
	TRangeRef pageRange;
	iColumnPageMap->IdToDisplacement(0,pageRef.iCol,pageRange.iFrom.iCol);
	pageRange.iFrom.iCol+=iGridRange.iFrom.iCol;
	iRowPageMap->IdToDisplacement(0,pageRef.iRow,pageRange.iFrom.iRow);
	pageRange.iFrom.iRow+=startRow;
	pageRange.iTo.iCol=Min(pageRange.iFrom.iCol+iColumnPageMap->ValueInPixels(pageRef.iCol)-1,
		iGridRange.iFrom.iCol+colExtent-1);
	pageRange.iTo.iRow=Min(pageRange.iFrom.iRow+iRowPageMap->ValueInPixels(pageRef.iRow)-1,
		startRow+rowExtent-1);
	return pageRange;
	}

EXPORT_C TInt CGridLay::NoOfPages() const
/** Gets the number of pages that the grid would print to.

@return The number of pages.
@panic GRIDIMG 5 In debug mode, if the grid has not been paginated. */
	{
	__ASSERT_DEBUG(IsPaginated(),Panic(EGridLayNotPaginated));
	TInt noOfHorzPages;
	iColumnPageMap->DisplacementToId(0,ColumnExtent()-1,noOfHorzPages);
	noOfHorzPages++;
	TInt noOfVertPages;
	iRowPageMap->DisplacementToId(0,RowExtent()-1,noOfVertPages);
	noOfVertPages++;
	return noOfHorzPages*noOfVertPages;
	}

TBool CGridLay::FindNextRowPageBreak(TInt aSearchStart,TInt& aFoundRow) const
//
// Searches from aSearchStart and finds the next row page break (hard or soft). If one is found,
// aFoundRow is amended and ETrue returned. Note that returned value is 1 less than the value
// stored because the physical line break belongs to the row above the stored page break.
	{
	if (IsPaginated())
		{
		TInt startRow;
		if (!RequestRow(-KMaxTInt,startRow))
			return EFalse;
		TInt rowPage;
		iRowPageMap->DisplacementToId(0,aSearchStart-startRow,rowPage);
		iRowPageMap->IdToDisplacement(0,rowPage+1,aFoundRow);
		aFoundRow+=startRow-1;
		return ETrue;
		}
	else
		{
		TKeyArrayFix key(0,ECmpTInt);
		TInt pos;
		aSearchStart++;
		if (iHardRowPageBreaks->FindIsq(aSearchStart,key,pos)==0)
			{
			aFoundRow=aSearchStart-1;
			return ETrue;
			}
		else if (pos<iHardRowPageBreaks->Count())
			{
			aFoundRow=(*iHardRowPageBreaks)[pos]-1;
			return ETrue;
			}
		}
	return EFalse;
	}

TBool CGridLay::FindNextColumnPageBreak(TInt aSearchStart,TInt& aFoundCol) const
//
// Searches from aSearchStart and finds the next column page break (hard or soft). If one is found,
// aFoundCol is amended and ETrue returned.
	{
	if (IsPaginated())
		{
		TInt colPage;
		iColumnPageMap->DisplacementToId(0,aSearchStart-iGridRange.iFrom.iCol,colPage);
		iColumnPageMap->IdToDisplacement(0,colPage+1,aFoundCol);
		aFoundCol+=iGridRange.iFrom.iCol-1;
		return ETrue;
		}
	else
		{
		TKeyArrayFix key(0,ECmpTInt);
		TInt pos;
		aSearchStart++;
		if (iHardColumnPageBreaks->FindIsq(aSearchStart,key,pos)==0)
			{
			aFoundCol=aSearchStart-1;
			return ETrue;
			}
		else if (pos<iHardColumnPageBreaks->Count())
			{
			aFoundCol=(*iHardColumnPageBreaks)[pos]-1;
			return ETrue;
			}
		}
	return EFalse;
	}

EXPORT_C void CGridLay::SetPageSizeInTwipsL(const TSize& aPageSize)
/** Sets the size of a page.

@param aPageSize The size of a page, in twips. */
	{
	iPageSizeInTwips=aPageSize;
	NotifyPaginationOutOfDateL();
	iHasChanged=ETrue;
	}

EXPORT_C void CGridLay::SetAutoPagination(TBool aState)
/** Sets whether automatic pagination is to be in effect.

@param aState ETrue, if automatic pagination is to be in effect; EFalse, otherwise. */
	{
	if (aState)
		iFlags|=EIsAutoPagination;
	else
		iFlags&=~EIsAutoPagination;
	iHasChanged=ETrue;
	}

EXPORT_C void CGridLay::SetHardRowPageBreakL(TInt aRow)
/** Sets a hard page break at the specified row.

Note that pagination will be flagged as being out of date.

@param aRow The row, immediately above which the hard page break is to occur. */
	{
	if (IsHardRowPageBreak(aRow))
		return;
	TInt startRow;
	if (!RequestRow(-KMaxTInt,startRow) || aRow==startRow)
		return;
	TKeyArrayFix key(0,ECmpTInt);
	iHardRowPageBreaks->InsertIsqL(aRow,key);
	NotifyPaginationOutOfDateL();
	iHasChanged=ETrue;
	}

EXPORT_C void CGridLay::ClearHardRowPageBreakL(TInt aRow)
/** Removes the hard page break at the specified row.

Note that pagination will be flagged as being out of date.

Note also that there is no harm in calling this function if there is no hard 
page break at the specified row.

@param aRow The row, immediately above which there is a hard page break. */
	{
	TKeyArrayFix key(0,ECmpTInt);
	TInt pos;
	if (iHardRowPageBreaks->FindIsq(aRow,key,pos)==0)
		{
		iHardRowPageBreaks->Delete(pos);
		NotifyPaginationOutOfDateL();
		iHasChanged=ETrue;
		}
	}

EXPORT_C TBool CGridLay::IsHardRowPageBreak(TInt aRow) const
/** Tests whether there is a hard page break at the specified row.

@param aRow The row.
@return True, if there is a hard page break at (i.e. immediately above) the 
specified row; false, otherwise. */
	{
	TKeyArrayFix key(0,ECmpTInt);
	TInt pos;
	if (iHardRowPageBreaks->FindIsq(aRow,key,pos)==0)
		return ETrue;
	return EFalse;
	}

EXPORT_C void CGridLay::SetHardColumnPageBreakL(TInt aCol)
/** Sets a hard page break at the specified column.

Note that pagination will be flagged as being out of date.

@param aCol The column, immediately to the left of which the hard page break 
is to occur. */
	{
	if (IsHardColumnPageBreak(aCol) || aCol==iGridRange.iFrom.iCol)
		return;
	TKeyArrayFix key(0,ECmpTInt);
	iHardColumnPageBreaks->InsertIsqL(aCol,key);
	NotifyPaginationOutOfDateL();
	iHasChanged=ETrue;
	}

EXPORT_C void CGridLay::ClearHardColumnPageBreakL(TInt aCol)
/** Removes the hard page break at the specified column.

Note that pagination will be flagged as being out of date.

Note also that there is no harm in calling this function if there is no hard 
page break at the specified column.

@param aCol The column, immediately to the left of which there is a hard page 
break. */
	{
	TKeyArrayFix key(0,ECmpTInt);
	TInt pos;
	if (iHardColumnPageBreaks->FindIsq(aCol,key,pos)==0)
		{
		iHardColumnPageBreaks->Delete(pos);
		NotifyPaginationOutOfDateL();
		iHasChanged=ETrue;
		}
	}

EXPORT_C TBool CGridLay::IsHardColumnPageBreak(TInt aCol) const
/** Tests whether there is a hard page break at the specified column.

@param aCol The column.
@return True, if there is a hard page break at (i.e. immediately to the left 
of) the specified column; false, otherwise. */
	{
	TKeyArrayFix key(0,ECmpTInt);
	TInt pos;
	if (iHardColumnPageBreaks->FindIsq(aCol,key,pos)==0)
		return ETrue;
	return EFalse;
	}

EXPORT_C void CGridLay::ClearAllHardPageBreaksL()
/** Removes all hard page breaks; this includes all row and column page breaks.

Note that pagination will be flagged as being out of date. */
	{
	iHardRowPageBreaks->Reset();
	iHardColumnPageBreaks->Reset();
	NotifyPaginationOutOfDateL();
	iHasChanged=ETrue;
	}

EXPORT_C void CGridLay::ExternalizeL(RWriteStream &aStream) const
/** Externalises an object of this class to a write stream.

The presence of this function means that the standard templated operator<<() 
can be used to externalise objects of this class. 

@param aStream Stream to which the object should be externalised. */
	{
	aStream.WriteUint32L(iFlags);
	aStream << iGridRange;
	aStream << *iRowHeightMap;
	aStream << *iColumnWidthMap;
	aStream << *iHardRowPageBreaks;
	aStream << *iHardColumnPageBreaks;
	aStream.WriteInt32L(iMinRowHeightInPixels);
	aStream.WriteInt32L(iMinColumnWidthInPixels);
	aStream.WriteInt32L(iPageSizeInTwips.iWidth);
	aStream.WriteInt32L(iPageSizeInTwips.iHeight);
	if (IsTitleLines())
		{
		aStream << iTitleRange;
		}
	aStream << iVisibleRange.iFrom;
	aStream << iGridEdgeColor;
	((CGridLay*)this)->iHasChanged=EFalse;
	}

EXPORT_C void CGridLay::InternalizeL(RReadStream &aStream)
/** Internalises an object of this class from a read stream.

The presence of this function means that the standard templated operator>>() 
can be used to internalise objects of this class.

Note that the function has assignment semantics. It replaces the old value 
of the object with a new value read from the read stream. 

@param aStream Stream from which the object is to be internalised. */
	{
	iFlags = aStream.ReadUint32L();
	aStream >> iGridRange;
	if (iGridImg)
		iGridImg->NotifyGridRangeResize();
	aStream >> *iRowHeightMap;
	aStream >> *iColumnWidthMap;
	aStream >> *iHardRowPageBreaks;
	aStream >> *iHardColumnPageBreaks;
	RecalcPixelSparseMaps();
	iMinRowHeightInPixels=aStream.ReadInt32L();
	iMinColumnWidthInPixels=aStream.ReadInt32L();
	iPageSizeInTwips.iWidth=aStream.ReadInt32L();
	iPageSizeInTwips.iHeight=aStream.ReadInt32L();
	if (IsPaginated() && iGridImg)
		{
		ClearPagination();
		PaginateL();
		}
	if (IsTitleLines())
		{
		aStream >> iTitleRange;
		}
	if (IsRowPermanentlySelected())
		SetRowPermanentlySelectedL(ETrue);	//To add row to selection region
	if (iGridImg)
		iGridImg->ResetReferencePoints();
	aStream >> iVisibleRange.iFrom;
	if (iGridImg)
		{
		ResetVisibleToCell();
		iGridImg->CheckSideLabelWidth();
		}
	aStream >> iGridEdgeColor;
	iHasChanged=EFalse;
	}

EXPORT_C TStreamId CGridLay::StoreL(CStreamStore& aStore) const
/** Externalises this object to a stream in the specified store.

@param aStore The store in which the stream is to be created and stored.
@return The Id of the created stream. */
	{
	RStoreWriteStream stream;
	TStreamId streamId = stream.CreateLC(aStore);
	ExternalizeL(stream);
	stream.CommitL();
	CleanupStack::PopAndDestroy();
	return streamId;
	}

EXPORT_C void CGridLay::RestoreL(const CStreamStore& aStore,TStreamId aStreamId)
/** Internalises this object from the specified stream in the specified store.

Note that the function has assignment semantics. It replaces the old value 
of this object with a new value read from the specified stream.

@param aStore The store containing the stream.
@param aStreamId The Id of the stream from which this object is to be internalised. */
	{
	RStoreReadStream stream;
	stream.OpenLC(aStore,aStreamId);
	InternalizeL(stream);
	CleanupStack::PopAndDestroy();
	}

TBool CGridLay::RequestRow(TInt aRow,TInt& aReturnRow) const
	{
	if (IsIndefiniteRowBoundaries())
		return iGridTable->RequestRow(aRow,aReturnRow);
	if (aRow<iGridRange.iFrom.iRow)
		aReturnRow=iGridRange.iFrom.iRow;
	else if (aRow>iGridRange.iTo.iRow)
		aReturnRow=iGridRange.iTo.iRow;
	else
		aReturnRow=aRow;
	return iGridRange.iFrom.iRow<=iGridRange.iTo.iRow;
	}

EXPORT_C TInt CGridLay::RowExtent() const
/** Gets the number of rows in the range.

@return The number of rows. */
	{
	TInt gridRowExtent=iGridRange.iTo.iRow-iGridRange.iFrom.iRow+1;
	if (gridRowExtent<0)
		gridRowExtent=KMaxTInt;	// In case gridrange is v. large (i.e. indefinite row boundaries)
	return Min(iGridTable->RowExtent(),gridRowExtent);
	}

EXPORT_C TInt CGridLay::ColumnExtent() const
/** Gets the number of columns in the range.

@return The number of columns. */
	{
	return Min(iGridTable->ColumnExtent(),iGridRange.iTo.iCol-iGridRange.iFrom.iCol+1);
	}

//

EXPORT_C TBool MGridTable::RequestRow(TInt /*aRow*/,TInt& /*aReturnRow*/) const
/** Translates a requested row.

Typically, the function is called by grid before it attempts a redraw in order 
to determine how many rows can be drawn. For example, if a request for row 16 
were to be translated as row 11, then it would imply that there are only 11 
rows in this rowset, and cause grid to draw accordingly.

An implementation must be provided for grids that have indefinite row boundaries.

The default implementation raises a panic.

@param aRow The row to be translated.
@param aReturnRow On return, the row that corresponds to the requested row.
@return True, if a row is returned; false, if no rows can be returned.
@panic GRIDIMG 8 Always raised by the default implementation.*/
	{
	Panic(EGridTableInvalidRequestRow);
	return EFalse;
	}

EXPORT_C TInt MGridTable::RowExtent() const
/** Gets the number of rows in the grid.

@return The number of rows in the grid. The default implementation returns 
the value EDefaultRowExtent. */
	{
	return EDefaultRowExtent;
	}

EXPORT_C TInt MGridTable::ColumnExtent() const
/** Gets the number of columns in the grid.

@return The number of columns in the grid. The default implementation returns 
the value EDefaultColumnExtent. */
	{
	return EDefaultColumnExtent;
	}

//	Setting the grid colors

EXPORT_C void CGridLay::SetGridColors(TGridColors aColors)
/** Sets the collection of colours to be used to draw the grid.

@param aColors The grid colour definitions. */
	{
	iColors = aColors;
	iGridImg->SetGridColors(aColors);
	}

//	Getting the grid colors

EXPORT_C const TGridColors& CGridLay::GridColors() const
/** Gets the collection of colours used to draw the grid.

@return The grid colour definitions. */
	{
	return iColors;
	}
