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

#if !defined(__GRDCELLS_H__)
#define __GRDCELLS_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif
#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif
#if !defined(__BACELL_H__)
#include <bacell.h>
#endif



class CGridCellRegion : public CBase
/** Defines a selected region.

A selected region consists of one or more cell ranges, represented by TRangeRef 
objects, that exist within a defined boundary. The boundary is itself defined 
as a cell range.

Cell ranges map cell selections, and the class provides the behaviour to manage 
these selections. 

@publishedAll 
@released */
	{
public:
	IMPORT_C static CGridCellRegion* NewL(const TRangeRef& aBounds);
	IMPORT_C virtual ~CGridCellRegion();
	IMPORT_C void AddColL(TInt aCol);
	IMPORT_C void AddRowL(TInt aRow);
	IMPORT_C void AddCellRangeL(const TRangeRef& aCellRange);
	IMPORT_C void SetLastCellRange(const TRangeRef& aCellRange);
	IMPORT_C void ResizeBounds(const TCellRef& aNewToBounds);
	IMPORT_C void Reset();
	IMPORT_C TInt Count() const;
	IMPORT_C TBool IsCellSelected(const TCellRef &aCell) const;
	IMPORT_C TBool IsCellSelected(const TCellRef &aCell,TInt aIndex) const;
	IMPORT_C TBool IsCellSelectedLastIndex(const TCellRef &aCell) const;
	IMPORT_C TBool IsRowSelected(TInt aRow) const;
	IMPORT_C TBool IsRowSelected(TInt aRow,TInt aIndex) const;
	IMPORT_C TBool IsRowSelectedLastIndex(TInt aRow) const;
	IMPORT_C TBool IsAnyRowSelected() const;
	IMPORT_C TBool IsColSelected(TInt aCol) const;
	IMPORT_C TBool IsColSelected(TInt aCol,TInt aIndex) const;
	IMPORT_C TBool IsColSelectedLastIndex(TInt aCol) const;
	IMPORT_C TBool IsAnyColSelected() const;
	IMPORT_C TBool IsRangeSelected(const TRangeRef &aRange) const;
	IMPORT_C TBool IsRangeSelected(const TRangeRef &aRange,TInt aIndex) const;
	IMPORT_C TBool IsRangeSelectedLastIndex(const TRangeRef &aRange) const;
	IMPORT_C TRangeRef operator[](TInt aIndex) const;
	IMPORT_C const CArrayFix<TRangeRef>* RangeList() const;
private:
	CGridCellRegion(const TRangeRef& aBounds);
	void ConstructL();
private:
	TRangeRef iBounds;
	CArrayFix<TRangeRef>* iRangeList;
	};
#endif
