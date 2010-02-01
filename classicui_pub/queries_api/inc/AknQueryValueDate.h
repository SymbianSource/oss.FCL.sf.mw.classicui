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
*
*/

// AknQueryValueDate.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#if !defined(__AKNQUERYVALUEDATE_H__)
#define __AKNQUERYVALUEDATE_H__

#include <bamdesca.h>
#include <eikdialg.h>
#include "AknQueryValue.h"

class CAknQueryValueDateArray;

/**
 * Encapsulates a date value. Provides an interface to create a dialog
 * containing a time query control, which will edit the value. Optionally 
 * Allows the value to be changed by selecting from a list of values. 
 *
 */
NONSHARABLE_CLASS(CAknQueryValueDate) : public CAknQueryValue
    {
public:
    /**
     * Two-phased constructor.
     *
    */
	IMPORT_C static CAknQueryValueDate* NewL();
	
    /**
     * Two-phased constructor.
     *
    */	
	IMPORT_C static CAknQueryValueDate* NewLC();

    /**
     * destructor
     *
    */
	IMPORT_C virtual ~CAknQueryValueDate();
	
    /**
     * Set the array.
     * 
     * @param aArray pointer to array, ownership is not passed
    */	
	IMPORT_C void SetArrayL(const CAknQueryValueDateArray* aArray);
	
    /**
     * Set the string used for the query caption to be a string other than the default.
     *
     * @param aResourceId		resource id of string to use for caption.
     *
    */	
	IMPORT_C void SetQueryCaption(TInt aResourceId);
	
    /**
     * Return the current value, which may have been set by the user
     *
    */	
	IMPORT_C TTime Value() const;

public: // from MAknQueryValue
    IMPORT_C virtual const MDesCArray* MdcArray() const;
    IMPORT_C virtual HBufC* CurrentValueTextLC();
    IMPORT_C virtual TInt CurrentValueIndex() const;
    IMPORT_C virtual void SetCurrentValueIndex(const TInt aIndex);
    IMPORT_C virtual TBool CreateEditorL();
    
protected:
	CAknQueryValueDate();
	
	/**
     * 2nd stage construction.
     *
    */
	void ConstructL();
	
    /**
     * Search for the current time in the list, and set the current index 
     * to be the found index. If not found, set current index to 1 after the size of the array.
     *
    */	
	void CalculateCurrentIndex();
	
	virtual void AppendValueIfNewL();
	
private: // from MAknQueryValue
	IMPORT_C void Reserved_MAknQueryValue();

private:
	// the following are member variables
	TInt iQueryCaptionId;
	TTime iTime;
	TInt iCurrentIndex;
	// the following are not owned
	const CAknQueryValueDateArray* iArray;
    };


/**
 * Wraps an array of dates, adapts it into a descriptor array.
 *
 */
NONSHARABLE_CLASS(CAknQueryValueDateArray) : public CBase, public MDesCArray
	{
public:
    /**
     * Typedef for array containing TTime items
     *
    */
	typedef CArrayFix<TTime> TimeArray;
	

	enum {KSafeSizeOfDescriptorForTTimeFormat = 128};
	
public:
    /**
     * Two-phased constructor.
     *
    */
	IMPORT_C static CAknQueryValueDateArray* NewL(TInt aResourceId);
	
    /**
     * Two-phased constructor.
     *
    */	
	IMPORT_C static CAknQueryValueDateArray* NewLC(TInt aResourceId);
	
	IMPORT_C ~CAknQueryValueDateArray();
	
    /**
     * Set the array of values. 
     * Note that client can use any implementation of array class, but must pass in a 
     * TArray generated from it (by calling the Array() method on the array class)
     *
     * @param aArray  array of values, ownership is not passed
    */
	IMPORT_C void SetArray(TimeArray& aArray);
	
	/**
     * Get the array of values as a TArray. 
     * Note that client can use any implementation of array class, but the array is 
     * treated as a TArray.
     *
     * @return array of values, ownership is not passed
    */
	IMPORT_C TimeArray* Array() const;
	
    /**
     * Return the TTime format string that is used to generate MDesCArray values
     *
     * @return format string
    */	
	IMPORT_C const HBufC* FormatString() const;
	
#ifdef __WINS__
    /**
     * Return the size of a maximal time string formated using the format string 
     * that was supplied during construction of this instance.
     * Two versions to eliminate compiler warnings.
     *	
     * @return length of formatted string.
    */
	IMPORT_C const TInt FormattedStringSize() const;
#else
    /**
     * See const TInt FormattedStringSize() const;
     *
    */
	IMPORT_C TInt FormattedStringSize() const;
#endif // __WINS__

public:
	// from MDesCArray
    /**
	 * @return count of contained array
     *
    */
    IMPORT_C virtual TInt MdcaCount() const;
    
    /**
     * Returns array element, converting value to text. 
     * <p> WARNING: the returned pointer is only valid until the next time this
     * method is invoked. 
     *
     * @param aIndex of element to return
     * @return descriptor representing array element, ownership is not passed
    */
    IMPORT_C virtual TPtrC MdcaPoint(TInt aIndex) const;
    
protected:
	CAknQueryValueDateArray();
	
    /**
     * 2nd stage construction.
     *
    */
	void ConstructL(TInt aResourceId);
	
private:
	// the following members are owned
	HBufC* iLastGeneratedTextValue;
	HBufC* iFormatString;
	// the following members are not owned
	TimeArray* iArray;
	TInt iFormattedStringSize;
	};

#endif // __AKNQUERYVALUEDATE_H__

