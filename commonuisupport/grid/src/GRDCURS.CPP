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

// This module contains all the main logic connected with movement and selection in CGridImg.
//
#include "GRDSTD.H"
#include "GRDPANIC.H"

#if !defined(__WINC__)
#include <w32std.h>
#endif


GLREF_C void CleanupGc(TAny* aObject);

void CGridImg::DrawCursorOrRegionL(TUint aMoveFlags)
	{
	//
	// Does the appropriate operation on the cursor given the conditions in the parameters
	//
	if (iGridLay->IsRowPermanentlySelected())
		aMoveFlags|=EIsRowSelected;
	RRegion oldRegion;
	CleanupClose<RRegion>::PushL(oldRegion);
	AppendTotalHighlightRegionL(oldRegion);
	TInt oldCursorRow=iCursorPos.iRow;
	TInt selectCount=iSelected->Count();
	if (selectCount)
		{
		if (aMoveFlags&EIsWithSelect)
			{
			if (aMoveFlags&EIsAtBoundary)
				iNewCursorPos = iCursorPos;
			else 
				UpdateSelectedRegion(selectCount,aMoveFlags);
			}
		else
			{
			if (aMoveFlags&EIsWithControl)
				{
				if (aMoveFlags&(EIsRowSelected|EIsColumnSelected))
					AddLabelToRegionL(aMoveFlags);
				else
					{
					iAnchorPos=iCursorPos=iNewCursorPos;
					StartSelectedRegionL(aMoveFlags);
					}
				}
			else
				{
 				iSelected->Reset();
				if ((aMoveFlags&(EIsRowSelected|EIsColumnSelected)) && (!(aMoveFlags&EIsAtBoundary)
					|| iGridLay->IsRowPermanentlySelected()))
					{
					AddLabelToRegionL(aMoveFlags);
					}
				else
					{
					if (aMoveFlags&EIsAtBoundary)
						iNewCursorPos=iCursorPos=iAnchorPos;
					else
						iCursorPos=iNewCursorPos;
					}
				}
			}
		}
	else
		{
		if (aMoveFlags&EIsAtBoundary)
			iNewCursorPos = iCursorPos;
		else
			{
			if (aMoveFlags&(EIsWithSelect|EIsWithControl))
				{
				if (aMoveFlags&EIsWithSelect)
					StartSelectedRegionL(aMoveFlags);
				else
					{
					if (aMoveFlags&(EIsRowSelected|EIsColumnSelected))
						AddLabelToRegionL(aMoveFlags);
					else
						{
						iAnchorPos=iCursorPos=iNewCursorPos;
						StartSelectedRegionL(aMoveFlags);
						}
					}
				}
			else
				{
				if (aMoveFlags&(EIsRowSelected|EIsColumnSelected))
					AddLabelToRegionL(aMoveFlags);
				else
					iCursorPos = iNewCursorPos;
				}
			}
		}
	if (iCursorPos.iRow!=oldCursorRow || aMoveFlags&EIsColumnSelected)
		{
		RemoveRowLabelFromRegionL(oldCursorRow,oldRegion);
		RemoveRowLabelFromRegionL(iCursorPos.iRow,oldRegion);
#if !defined(__WINC__)
		CreateGc(iGc);
		CleanupStack::PushL(TCleanupItem(CleanupGc,this));
		DrawSideGridLabelIfOnScreenL(oldCursorRow);
		DrawSideGridLabelIfOnScreenL(iCursorPos.iRow);
		CleanupStack::PopAndDestroy();	// gc cleanup
#endif
		}
	HighlightNewRegionFromOldL(oldRegion);
	CleanupStack::PopAndDestroy();	// oldRegion
	}

void CGridImg::UpdateSelectedRegion(TInt aSelectCount,TUint aMoveFlags)
	{
	//
	// Updates the latest selected region in accordance with the passed parameters.
	//
	__ASSERT_DEBUG(aSelectCount>0,Panic(ECellRegionNothingSelected));

	TRangeRef range = (*iSelected)[aSelectCount-1];
	TRangeRef bounds(iGridLay->GridRange());
	if (aMoveFlags&EIsAbsoluteMove)
		{
		if (((aMoveFlags&(EIsColumnSelected|EIsRowSelected|EIsWithDrag))==EIsColumnSelected)
			|| (iSelected->IsColSelectedLastIndex(iCursorPos.iCol) && (aMoveFlags&EIsWithDrag)
			&& !iSelected->IsRowSelectedLastIndex(iCursorPos.iRow)))
			{
			iGridLay->LimitCell(iNewCursorPos);
			range.iFrom.iCol = Min(iAnchorPos.iCol, iNewCursorPos.iCol);
			range.iTo.iCol = Max(iAnchorPos.iCol, iNewCursorPos.iCol);
			range.iFrom.iRow = bounds.iFrom.iRow;
			range.iTo.iRow = bounds.iTo.iRow;
			iCursorPos.iCol = iNewCursorPos.iCol;
			iNewCursorPos.iRow = iCursorPos.iRow;
			}
		else if (((aMoveFlags&(EIsRowSelected|EIsColumnSelected|EIsWithDrag))==EIsRowSelected)
			|| (iSelected->IsRowSelectedLastIndex(iCursorPos.iRow) && (aMoveFlags&EIsWithDrag)
			&& !iSelected->IsColSelectedLastIndex(iCursorPos.iCol)))
			{
			iGridLay->LimitCell(iNewCursorPos);
			range.iFrom.iRow = Min(iAnchorPos.iRow, iNewCursorPos.iRow);
			range.iTo.iRow = Max(iAnchorPos.iRow, iNewCursorPos.iRow);
			range.iFrom.iCol = bounds.iFrom.iCol;
			range.iTo.iCol = bounds.iTo.iCol;
			iCursorPos.iRow = iNewCursorPos.iRow;
			iNewCursorPos.iCol = iCursorPos.iCol;
			}
		else if ((aMoveFlags&(EIsRowSelected|EIsColumnSelected|EIsWithDrag))==
			(EIsRowSelected|EIsColumnSelected))
			{
			range = bounds;
			iNewCursorPos = iCursorPos = bounds.iTo;
			}
		else if (!(iSelected->IsRangeSelectedLastIndex(iGridLay->GridRange()) &&
			(aMoveFlags&EIsWithDrag)))
			{
			iGridLay->LimitCell(iNewCursorPos);
 			range.iFrom.iCol = Min(iAnchorPos.iCol, iNewCursorPos.iCol);
			range.iTo.iCol = Max(iAnchorPos.iCol, iNewCursorPos.iCol);
   			range.iFrom.iRow = Min(iAnchorPos.iRow, iNewCursorPos.iRow);
			range.iTo.iRow = Max(iAnchorPos.iRow, iNewCursorPos.iRow);
			iCursorPos = iNewCursorPos;
			}
		}
	else
		{
		if (iNewCursorPos.iRow != iCursorPos.iRow)
			{
 			range.iFrom.iRow = Min(iAnchorPos.iRow, iNewCursorPos.iRow);
			range.iTo.iRow = Max(iAnchorPos.iRow, iNewCursorPos.iRow);
			iCursorPos.iRow = iNewCursorPos.iRow;
			}
		if (iNewCursorPos.iCol != iCursorPos.iCol && !iGridLay->IsRowPermanentlySelected())
			{
 			range.iFrom.iCol = Min(iAnchorPos.iCol, iNewCursorPos.iCol);
			range.iTo.iCol = Max(iAnchorPos.iCol, iNewCursorPos.iCol);
			iCursorPos.iCol = iNewCursorPos.iCol;
			}
		}
	iSelected->SetLastCellRange(range);
	}

void CGridImg::AddLabelToRegionL(TUint aMoveFlags)
	{
	//
	// Adds an entire row/column/grid to the selected region 
	// depending on iNewCursorPos
	//
	if ((aMoveFlags&(EIsRowSelected|EIsColumnSelected))==(EIsRowSelected|EIsColumnSelected))
		{
		TRangeRef gridRange=iGridLay->GridRange();
		iSelected->AddCellRangeL(gridRange);
		iAnchorPos.iRow=(iGridLay->IsHorizontalTitleLine()) ? iGridLay->TitleRange().iFrom.iRow
			: iGridLay->VisibleRange().iFrom.iRow;
		iAnchorPos.iCol=(iGridLay->IsVerticalTitleLine()) ? iGridLay->TitleRange().iFrom.iCol
			: iGridLay->VisibleRange().iFrom.iCol;
		iCursorPos=iNewCursorPos=iGridLay->GridRange().iTo;
		}
	else if (aMoveFlags&EIsColumnSelected)
		{
		iSelected->AddColL(iNewCursorPos.iCol);
		iAnchorPos.iCol = iCursorPos.iCol = iNewCursorPos.iCol;
		iAnchorPos.iRow=(iGridLay->IsHorizontalTitleLine()) ? iGridLay->TitleRange().iFrom.iRow
			: iGridLay->VisibleRange().iFrom.iRow;
		iCursorPos.iRow = iNewCursorPos.iRow = iGridLay->GridRange().iTo.iRow;
		}
	else if (aMoveFlags&EIsRowSelected)
		{
		iSelected->AddRowL(iNewCursorPos.iRow);
		iAnchorPos.iRow = iCursorPos.iRow = iNewCursorPos.iRow;
		iAnchorPos.iCol=(iGridLay->IsVerticalTitleLine()) ? iGridLay->TitleRange().iFrom.iCol
			: iGridLay->VisibleRange().iFrom.iCol;
		iCursorPos.iCol = iNewCursorPos.iCol = iGridLay->GridRange().iTo.iCol;
		}
	}

void CGridImg::StartSelectedRegionL(TUint aMoveFlags)
	{
	//
	// Sets the anchor to the current cursor position and selects the region between
	// the anchor and the new cursor position
	//
	if (aMoveFlags&(EIsRowSelected|EIsColumnSelected) && (aMoveFlags&EIsWithDrag))
		return;
	iAnchorPos = iCursorPos;
	iCursorPos = iNewCursorPos;
	TRangeRef range;
	if ((aMoveFlags&EIsColumnSelected) && (aMoveFlags&EIsRowSelected))
		range = iGridLay->GridRange();
	else
		{
		range.iFrom.iRow = Min(iAnchorPos.iRow, iNewCursorPos.iRow);
		range.iTo.iRow = Max(iAnchorPos.iRow, iNewCursorPos.iRow);
		range.iFrom.iCol = Min(iAnchorPos.iCol, iNewCursorPos.iCol);
		range.iTo.iCol = Max(iAnchorPos.iCol, iNewCursorPos.iCol);
		if (aMoveFlags&EIsRowSelected)
			{
			TRangeRef gridRange=iGridLay->GridRange();
			range.iFrom.iCol = gridRange.iFrom.iCol;
			range.iTo.iCol = gridRange.iTo.iCol;
			}
		if (aMoveFlags&EIsColumnSelected)
			{
			TRangeRef gridRange=iGridLay->GridRange();
	   		range.iFrom.iRow = gridRange.iFrom.iRow;
			range.iTo.iRow = gridRange.iTo.iRow;
			}
		}
	iSelected->AddCellRangeL(range);
	}
