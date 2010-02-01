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
//

#include "GRDCELLS.H"
#include "GRDPANIC.H"


EXPORT_C CGridCellRegion* CGridCellRegion::NewL(const TRangeRef& aBounds)
/** Creates a new selected region.

@param aBounds The boundary of the region, defined as cell range.
@return A pointer to the new selected region object. */
	{
	CGridCellRegion* self = new(ELeave) CGridCellRegion(aBounds);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();
	return self;
	}

CGridCellRegion::CGridCellRegion(const TRangeRef &aBounds)
	: iBounds(aBounds)
	{
	}

EXPORT_C CGridCellRegion::~CGridCellRegion()
/** Destructor.

Frees all resources owned by the object prior to its destruction. */
	{
	delete iRangeList;
	}

void CGridCellRegion::ConstructL()
	{
	iRangeList = new(ELeave) CArrayFixFlat<TRangeRef>(1);
	}

EXPORT_C void CGridCellRegion::AddColL(TInt aCol)
/** Defines a new cell range one column in width, and adds it to the region.

The row number of the start cell of the new range is the row number defining 
the start of the region boundary.

The row number of the end cell of the new range is the row number defining 
the end of the region boundary.

@param aCol The new column. This must lie on or within the region boundary, 
otherwise no new range is added to the region. */
	{
	if (aCol<iBounds.iFrom.iCol || aCol>iBounds.iTo.iCol)
		return;
	TRangeRef cellRange;
	cellRange.iFrom.iCol = cellRange.iTo.iCol = aCol;
	cellRange.iFrom.iRow = iBounds.iFrom.iRow;
	cellRange.iTo.iRow = iBounds.iTo.iRow;
	iRangeList->AppendL(cellRange);
	}

EXPORT_C void CGridCellRegion::AddRowL(TInt aRow)
/** Defines a new cell range one row in height, and adds it to the region.

The column number of the start cell of the new range is the column number 
defining the start of the region boundary.

The column number of the end cell of the new range is the column number defining 
the end of the region boundary.

@param aRow The new row. This must lie on or within the region boundary, otherwise 
no new range is added to the region. */
	{
	if (aRow<iBounds.iFrom.iRow || aRow>iBounds.iTo.iRow)
		return;
	TRangeRef cellRange;
	cellRange.iFrom.iRow = cellRange.iTo.iRow = aRow;
	cellRange.iFrom.iCol = iBounds.iFrom.iCol;
	cellRange.iTo.iCol = iBounds.iTo.iCol;
	iRangeList->AppendL(cellRange);
	}

LOCAL_C void NormalizeRange(TRangeRef& aRange)
	{
	if (aRange.iFrom.iCol>aRange.iTo.iCol)
		{
		TInt temp=aRange.iFrom.iCol;
		aRange.iFrom.iCol=aRange.iTo.iCol;
		aRange.iTo.iCol=temp;
		}
	if (aRange.iFrom.iRow>aRange.iTo.iRow)
		{
		TInt temp=aRange.iFrom.iRow;
		aRange.iFrom.iRow=aRange.iTo.iRow;
		aRange.iTo.iRow=temp;
		}
	}	

EXPORT_C void CGridCellRegion::AddCellRangeL(const TRangeRef& aCellRange)
/** Adds the specified range to the region.

@param aCellRange The new range. This must lie on or within the region boundary, 
otherwise it is not added to the region. */
	{
	TRangeRef range=aCellRange;
	NormalizeRange(range);
	if (range.iTo.iRow<iBounds.iFrom.iRow || range.iFrom.iRow>iBounds.iTo.iRow
		|| range.iTo.iCol<iBounds.iFrom.iCol || range.iFrom.iCol>iBounds.iTo.iCol)
		{
		return;
		}
	iRangeList->AppendL(range);
	}

EXPORT_C void CGridCellRegion::SetLastCellRange(const TRangeRef& aCellRange)
/** Replaces the last range in the region with the specified range.

Note that a region is implemented as an array of ranges, and the last range 
is the last one in the array.

@param aCellRange The range to replace the last range in the region. Note 
that it is the caller's responsibility to ensure that this region lies within 
the region boundary, as no checks are made by the function.
@panic GRIDIMG 1 If the region is empty. */
	{
	__ASSERT_DEBUG(iRangeList->Count()>0,Panic(ECellRegionNothingSelected));
	TRangeRef range=aCellRange;
	NormalizeRange(range);
	(*iRangeList)[iRangeList->Count()-1]=range;
	}

EXPORT_C void CGridCellRegion::ResizeBounds(const TCellRef& aNewToBounds)
/** Defines a new region boundary by replacing the end cell with the specified 
cell.

Any existing ranges that are now wholly outside the new region boundary are 
deleted.

Any existing ranges whose boundaries were the same as the old region boundary, 
are stretched or shrunk so that their boundaries are now on the new region 
boundary.

Any existing ranges that now intersect the new region boundary are truncated 
back to the new region boundary.

Any existing ranges that remain wholly within the new region boundary remain 
unchanged.

@param aNewToBounds The new end cell for the region boundary. */
	{
	TRangeRef newBounds(iBounds.iFrom,aNewToBounds);
	TInt end=iRangeList->Count();
	for (TInt ii=0;ii<end;ii++)
		{
		TRangeRef& range=(*iRangeList)[ii];
		if (range.iFrom.iRow>newBounds.iTo.iRow || range.iFrom.iCol>newBounds.iTo.iCol)
			{
			iRangeList->Delete(ii--);
			end--;
			continue;
			}
		if (IsColSelected(range.iFrom.iCol,ii))
			range.iTo.iRow=newBounds.iTo.iRow;
		else
			range.iTo.iRow = Min(range.iTo.iRow,newBounds.iTo.iRow);
		if (IsRowSelected(range.iFrom.iRow,ii))
			range.iTo.iCol=newBounds.iTo.iCol;
		else
			range.iTo.iCol = Min(range.iTo.iCol,newBounds.iTo.iCol);
		}
	iBounds=newBounds;
	}

EXPORT_C void CGridCellRegion::Reset()
/** Deletes all ranges from the region. */
	{
	iRangeList->Reset();
	}

EXPORT_C TInt CGridCellRegion::Count() const
/** Gets the number of ranges in the region.

@return The number of ranges in the region. */
	{
	return(iRangeList->CArrayFixBase::Count());
	}

EXPORT_C TBool CGridCellRegion::IsCellSelected(const TCellRef &aCell) const
/** Tests whether the specified cell is selected.

A cell is selected if it is in the region.

@param aCell The cell to be tested.
@return True, if the cell is selected; false, otherwise. Note that this is 
also false if the region is empty. */
	{
	TInt end=iRangeList->Count();
	for (TInt ii=0;ii<end;ii++)
		{
		if (IsCellSelected(aCell,ii))
			return ETrue;
		}
	return EFalse;
	}

EXPORT_C TBool CGridCellRegion::IsCellSelected(const TCellRef &aCell,TInt aIndex) const
/** Tests whether the specified cell is selected in the range identified by the 
specified index.

A cell is selected if it lies in the range.

Note that a region is implemented as an array of ranges, and the index identifies 
a specific range within that array.

@param aCell The cell to be tested.
@param aIndex An index value identifying a specific range within the region.
@return True, if the specified cell is in the range identified by the index; 
false, otherwise.
@panic GRIDIMG 2 In debug mode only, if the index value is illegal. */
	{
	__ASSERT_DEBUG(aIndex>=0&&aIndex<iRangeList->Count(),Panic(ECellRegionInvalidIndex));
	TRangeRef temp=(*iRangeList)[aIndex];
	return (TBool)(temp.iFrom.iRow<=aCell.iRow && temp.iTo.iRow>=aCell.iRow &&
		temp.iFrom.iCol<=aCell.iCol && temp.iTo.iCol>=aCell.iCol);
	}

EXPORT_C TBool CGridCellRegion::IsCellSelectedLastIndex(const TCellRef &aCell) const
/** Tests whether the specified cell is selected in the last range of the region.

A cell is selected if it lies in the range.

Note that a region is implemented as an array of ranges, and the last range 
is the last one in the array.

@param aCell The cell to be tested.
@return True, if the specified cell is in the last range of the region; false, 
otherwise. Note that this is also false if the region is empty. */
	{
	TInt index=iRangeList->Count();
	return (index) ? IsCellSelected(aCell,index-1) : EFalse;
	}

EXPORT_C TBool CGridCellRegion::IsRowSelected(TInt aRow) const
/** Tests whether the specified row is selected.

A row is selected if the row lies within one of the region's ranges, and the 
range spans all of the columns defined by the region boundary (i.e. extends 
from one side of the region boundary to the other).

@param aRow The row to be tested.
@return True, if the row is selected; false otherwise. */
	{
	TInt end=iRangeList->Count();
	for (TInt ii=0;ii<end;ii++)
		{
		if (IsRowSelected(aRow,ii))
			return ETrue;
		}
	return EFalse;
	}

EXPORT_C TBool CGridCellRegion::IsRowSelected(TInt aRow,TInt aIndex) const
/** Tests whether the specified row is selected in the range identified by the 
specified index.

A row is selected in a range only if it lies in the range, and the range spans 
all of the columns defined by region boundary (i.e. extends from one side 
of the region boundary to the other).

Note that a region is implemented as an array of ranges, and the index identifies 
a specific range within that array.

@param aRow The row to be tested.
@param aIndex An index value identifying a specific range within the region.
@return True, if the row is selected; false otherwise.
@panic GRIDIMG 2 In debug mode only, if the index value is illegal. */
	{
	__ASSERT_DEBUG(aIndex>=0&&aIndex<iRangeList->Count(),Panic(ECellRegionInvalidIndex));
	TRangeRef range=(*iRangeList)[aIndex];
	return (TBool)(range.iFrom.iRow<=aRow && range.iTo.iRow>=aRow
		&& range.iFrom.iCol==iBounds.iFrom.iCol && range.iTo.iCol==iBounds.iTo.iCol);
	}

EXPORT_C TBool CGridCellRegion::IsRowSelectedLastIndex(TInt aRow) const
/** Tests whether the specified row is selected in the last range in the region.

A row is selected in a range only if it lies in the range, and the range spans 
all of the columns defined by region boundary (i.e. extends from one side 
of the region boundary to the other).

Note that a region is implemented as an array of ranges, and the last range 
is the last one in the array.

@param aRow The row to be tested.
@return True, if the row is selected; false otherwise. Note that this is also 
false if the region is empty. */
	{
	TInt index=iRangeList->Count();
	return (index) ? IsRowSelected(aRow,index-1) : EFalse;
	}

EXPORT_C TBool CGridCellRegion::IsAnyRowSelected() const
/** Tests whether any row is selected.

A row is selected if any range spans all of the columns defined by region 
boundary (i.e. extends from one side of the region boundary to the other).

@return True, if any row is selected; false, otherwise. */
	{
	TInt end=iRangeList->Count();
	for (TInt ii=0;ii<end;ii++)
		{
		TRangeRef range=(*iRangeList)[ii];
		if (range.iFrom.iCol==iBounds.iFrom.iCol && range.iTo.iCol==iBounds.iTo.iCol)
			return ETrue;
		}
	return EFalse;
	}

EXPORT_C TBool CGridCellRegion::IsColSelected(TInt aCol) const
/** Tests whether the specified column is selected.

A column is selected if the column lies within one of the region's ranges, 
and the range spans all of the rows defined by the region boundary (i.e. extends 
from the top of the region boundary to the bottom).

@param aCol The column to be tested.
@return True, if the column is selected; false, otherwise. */
	{
	TInt end=iRangeList->Count();
	for (TInt ii=0;ii<end;ii++)
		{
		if (IsColSelected(aCol,ii))
			return ETrue;
		}
	return EFalse;
	}

EXPORT_C TBool CGridCellRegion::IsColSelected(TInt aCol,TInt aIndex) const
/** Tests whether the specified column is selected in the range identified by the 
specified index.

A column is selected in a range only if it lies in the range, and the range 
spans all of the rows defined by the region boundary (i.e. extends from the 
top of the region boundary to the bottom).

Note that a region is implemented as an array of ranges, and the index identifies 
a specific range within that array.

@param aCol The column to be tested.
@param aIndex An index value identifying a specific range within the region.
@return True, if the column is selected; false, otherwise.
@panic GRIDIMG 2 In debug mode only, if the index value is illegal. */
	{
	__ASSERT_DEBUG(aIndex>=0&&aIndex<iRangeList->Count(),Panic(ECellRegionInvalidIndex));
	TRangeRef range=(*iRangeList)[aIndex];
	return (TBool)(range.iFrom.iCol<=aCol && range.iTo.iCol>=aCol
		&& range.iFrom.iRow==iBounds.iFrom.iRow && range.iTo.iRow==iBounds.iTo.iRow);
	}

EXPORT_C TBool CGridCellRegion::IsColSelectedLastIndex(TInt aCol) const
/** Tests whether the specified column is selected in the last range in the region.

A column is selected in a range only if it lies in the range, and the range 
spans all of the rows defined by the region boundary (i.e. extends from the 
top of the region boundary to the bottom).

Note that a region is implemented as an array of ranges, and the last range 
is the last one in the array.

@param aCol The column to be tested.
@return True, if the column is selected; false otherwise. Note that this is 
also false if the region is empty. */
	{
	TInt index=iRangeList->Count();
	return (index) ? IsColSelected(aCol,index-1) : EFalse;
	}


EXPORT_C TBool CGridCellRegion::IsAnyColSelected() const
/** Tests whether any column is selected.

A column is selected if any range spans all of the rows defined by region 
boundary (i.e. extends from the top of the region boundary to the bottom).

@return True, if any column is selected; false, otherwise. */
	{
	TInt end=iRangeList->Count();
	for (TInt ii=0;ii<end;ii++)
		{
		TRangeRef range=(*iRangeList)[ii];
		if (range.iFrom.iRow==iBounds.iFrom.iRow && range.iTo.iRow==iBounds.iTo.iRow)
			return ETrue;
		}
	return EFalse;
	}

EXPORT_C TBool CGridCellRegion::IsRangeSelected(const TRangeRef &aRange) const
/** Tests whether the specified range is selected.

A range is selected if it is one of the ranges making up the region.

@param aRange The range to be tested.
@return True, if the range is one of the ranges making up the region; false, 
otherwise. */
	{
	TInt end=iRangeList->Count();
	for (TInt ii=0;ii<end;ii++)
		{
		if (IsRangeSelected(aRange,ii))
			return ETrue;
		}
	return EFalse;
	}

EXPORT_C TBool CGridCellRegion::IsRangeSelected(const TRangeRef &aRange,TInt aIndex) const
/** Tests whether the specified range is the same as the range identified by the 
specified index.

Note that a region is implemented as an array of ranges, and the index identifies 
a specific range within that array.

@param aRange The range to be tested.
@param aIndex An index value identifying a specific range within the region.
@return True, if the specified range is the same as the range identified by 
the index; false, otherwise.
@panic GRIDIMG 2 In debug mode only, if the index value is illegal. */
	{
	__ASSERT_DEBUG(aIndex>=0&&aIndex<iRangeList->Count(),Panic(ECellRegionInvalidIndex));
	return (TBool)((*iRangeList)[aIndex]==aRange);
	}

EXPORT_C TBool CGridCellRegion::IsRangeSelectedLastIndex(const TRangeRef &aRange) const
/** Tests whether the specified range is the same as the last range in the region.

Note that a region is implemented as an array of ranges, and the last range 
is the last one in the array.

@param aRange The range to be tested.
@return True, if the specified range is the same as the last range in the region; 
false, otherwise. Note that this is also false if the region is empty. */
	{
	TInt index=iRangeList->Count();
	return (index) ? IsRangeSelected(aRange,index-1) : EFalse;
	}

EXPORT_C TRangeRef CGridCellRegion::operator[](TInt aIndex) const
/** Gets the range within the region that is identified by the specified index.

Note that a region is implemented as an array of ranges.

@param aIndex The index value.
@return The cell range. */
	{
	return (*iRangeList)[aIndex];
	}

EXPORT_C const CArrayFix<TRangeRef>* CGridCellRegion::RangeList() const
/** Gets a pointer to the internal array of ranges that constitutes the region.

@return A pointer to the array of ranges that constitutes the region. */
	{
	return iRangeList;
	}
