/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
*     This class is an extension of the text list
*     model class. It is designed specifically to be used with
*     the grid class and the grid view class.
*
*/


// AknGridM.cpp
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

#include <AknGridM.h>
#include "akntrace.h"

/**
 * Constructor
 */
EXPORT_C CAknGridM::CAknGridM()
    {
    }

/**
 * Destructor
 */
EXPORT_C CAknGridM::~CAknGridM()
	{
	}

/**
 * @return Number of the non empty cells in the grid.
 */
EXPORT_C TInt CAknGridM::NumberOfData() const
	{
	return iItemTextArray->MdcaCount();
	}

/**
 * Altered version of the CTextListBoxModel::NumberOfItems method.
 * This ensures that the functionality of the parental list
 * box code will work correctly with the layout of a
 * grid.
 * @return Number of cells within the grid (including
 * empty cells).
 */
EXPORT_C TInt CAknGridM::NumberOfItems() const
	{
	// number of items now data + empty cells - therefore
	// will always be a mapping between list box index and
	// actual data index

	TInt numberOfCells = NumberOfData();

	// add on empty cells
	numberOfCells += iEmptyCellsAtStart;
	_AKNTRACE( "[%s] number of items are %d", 
			   __FUNCTION__, numberOfCells );
	return numberOfCells;
	}

/**
 * @return ETrue if the data index given is a data cell within the
 * grid otherwise EFalse.
 */
EXPORT_C TBool CAknGridM::IndexContainsData(TInt aDataIndex) const
	{
	TInt numOfData = NumberOfData();

	// check data in array
	if (numOfData == 0)
		{
		return EFalse;
		}

	// check index is in range
	if (aDataIndex >= (numOfData + iEmptyCellsAtStart))
		{
		return EFalse;
		}

	// check index is not an empty start cell
	return (aDataIndex >= iEmptyCellsAtStart);
	}

/**
 * @return TPtr to the associated item text for a cell. Note
 * it assumes that the item index is a valid grid index. A
 * check should be made using IndexContainsData before the
 * function is called.
 * 
 * <p>Beware that if you have empty cells at the start that the
 * index given should take these in account.
 */
EXPORT_C TPtrC CAknGridM::ItemText(TInt aItemIndex) const
	{
	TInt realIndex = aItemIndex - iEmptyCellsAtStart;
	return iItemTextArray->MdcaPoint(realIndex);
	}

/**
 * Sets the number of empty cells at the start of the grid.
 */
EXPORT_C void CAknGridM::SetStartCells(TInt aNumEmpty)
	{
	iEmptyCellsAtStart = aNumEmpty;
	}

/**
 * @return Index of the first data item if data exists in
 * model or -1 if no data exists.
 */
EXPORT_C TInt CAknGridM::IndexOfFirstDataItem() const
	{
	if (NumberOfData())
		{
		return iEmptyCellsAtStart;
		}
	else
		{
		return -1;
		}
	}

/**
 * @return Index of the last data item if data exists in
 * model or -1 if no data exists.
 */
EXPORT_C TInt CAknGridM::IndexOfLastDataItem() const
	{
	TInt gridCheck = NumberOfData();
	if (gridCheck > 0)
		{
		return (gridCheck + iEmptyCellsAtStart - 1);
		}
	else
		{
		return -1;
		}
	}

// End of File
