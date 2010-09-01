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



// INCLUDES
#if !defined(__AKNGRIDM_H__)
#define __AKNGRIDM_H__  

#include <eiktxlbm.h>
#include <AknUtils.h>
// CLASS DECLARATION
	/**
	* Model class to @c CAknGrid. 
	* Usually this class object is instantiated automatically during the 
	* construction phase of @c CAknGrid object.If programmer wants to provide
	* their own model they must instantiate grid model class object of their
	* own and give it to the @c CAknGrid object using the @c SetModel function
	* before calling the @c ConstructL/ConstructFromResourceL function of
	* @c CAknGrid.
 	*
 	* @since Series60 0.9
 	*/
class CAknGridM : public CTextListBoxModel
	{
public:

	/**
 	* Default C++ constructor.
 	*/
	IMPORT_C CAknGridM();
	
	/**
 	* Destructor.
 	*/
	IMPORT_C virtual ~CAknGridM();
	
	/**
	* Access to the number of items in the arrays.
	* @return Number of cells within the grid (including empty cells).
	*/
	IMPORT_C virtual TInt NumberOfItems() const;
	
	/**
 	* Tests if the given cell index has data.
 	* @param aDataIndex Index to the item to be checked.
 	* @return @c ETrue if the data index given is a data cell within the grid
 	* otherwise returns @c EFalse.
 	*/
	IMPORT_C virtual TBool IndexContainsData(TInt aDataIndex) const;
	
	/**
	* Gives the number of data cells in the grid.
 	* @return Number of the non empty cells in the grid.
 	*/
	IMPORT_C virtual TInt NumberOfData() const;
	
	/**
 	* This function sets the number of empty data cells at the start of the
 	* grid.
 	* @param aNumEmpty Number of empty cells.
 	*/
	IMPORT_C void SetStartCells(TInt aNumEmpty);
	
	/**
	* Gets the index of the first data item in the model.
 	* @return Index of the first data item if data exists in model. Returns -1 
 	* if no data exists.
 	*/
	IMPORT_C TInt IndexOfFirstDataItem() const;
	
	/**
	* Gets the index of the last data item in the model.
 	* @return Index of the last data item if data exists in model. Returns -1
 	* if no data exists.
 	*/
	IMPORT_C TInt IndexOfLastDataItem() const;
	
	/**
	* Gets the text of given index. No check is made that the item index given
	* is a valid grid index. A check should be made using @c IndexContainsData
	* before the function is called. Empty cells at the start should be taken
	* in account of the index given.
 	* @param aItemIndex Index of the grid.
 	* @return a Pointer descriptor to the associated item text for a cell. 
 	*/
	IMPORT_C virtual TPtrC ItemText(TInt aItemIndex) const;
private:
	TInt iEmptyCellsAtStart;
	TInt iEmptyCellsAtEnd;

    TInt iSpare[2];
	}; 


#endif
