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

// AknQueryValueText.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#if !defined(__AKNQUERYVALUETEXT_H__)
#define __AKNQUERYVALUETEXT_H__

#include <bamdesca.h>
#include <eikdialg.h>
#include "AknQueryValue.h"

class CAknQueryValueTextArray;

/**
 * Encapsulates a string. Provides an interface to create a dialog
 * containing a text query control, which will edit the value. Optionally 
 * allows the value to be changed by selecting from a list of values. 
 *
 */
NONSHARABLE_CLASS(CAknQueryValueText) : public CAknQueryValue
    {
public:
    /**
     * First stage of two stage construction.
    */
	IMPORT_C static CAknQueryValueText* NewL();
	
	/**
     * First stage of two stage construction.
    */
	IMPORT_C static CAknQueryValueText* NewLC();
	
    IMPORT_C virtual ~CAknQueryValueText();
    
    /**
     * Set the array.
     * 
     * @param aArray pointer to array, ownership is not passed
    */
	IMPORT_C void SetArrayL(const CAknQueryValueTextArray* aArray);
	
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
     * @return The current value, ownership is not passed
     *    
    */
	IMPORT_C HBufC* Value() const;
	
public: // from MAknQueryValue
    IMPORT_C virtual const MDesCArray* MdcArray() const;
    IMPORT_C virtual HBufC* CurrentValueTextLC();
    IMPORT_C virtual TInt CurrentValueIndex() const;
    IMPORT_C virtual void SetCurrentValueIndex(const TInt aIndex);
    IMPORT_C virtual TBool CreateEditorL();
    
protected:
	CAknQueryValueText();
	
	/**
     * Two stage construction
     *
    */
	void ConstructL();
	
	/**
     * Search for the current value in the list, and set the current index 
     * to  be the found index. If not found, set current index to 1 after the size of the array.
     *
    */
	void CalculateCurrentIndex();
	
	/**
     * Append the current value if it is new
     *
     *
    */
	virtual void AppendValueIfNewL();
	
private: // from MAknQueryValue
	IMPORT_C void Reserved_MAknQueryValue();

private:
	// the following are member variables
	TInt iQueryCaptionId;
	HBufC* iText;
	TInt iCurrentIndex;
	// the following are not owned
	const CAknQueryValueTextArray* iArray;
    };


/**
 * Wraps a descriptor array.
 *
 */
NONSHARABLE_CLASS(CAknQueryValueTextArray) : public CBase, public MDesCArray
	{
public:
    /**
     * Typedef for array
     *
    */
	typedef CDesCArray TextArray;
	
	enum {KSafeSizeOfDescriptorForTextFormat = 32};
	
public:
    /**
     * Two-phased constructor.
     *
    */
	IMPORT_C static CAknQueryValueTextArray* NewL();
	
	/**
     * Two-phased constructor.
     *
    */
	IMPORT_C static CAknQueryValueTextArray* NewLC();
	
	IMPORT_C ~CAknQueryValueTextArray();
	
	/**
     * Set the array of values. 
     * Note that client can use any implementation of array class, but must pass in a 
     * TArray generated from it (by calling the Array() method on the array class)
     *
     * @param aArray   array of values, ownership is passed
    */
	IMPORT_C void SetArray(TextArray& aArray);
	
	/**
     * Get the array of values as a TArray. 
     * Note that client can use any implementation of array class, but the array is 
     * treated as a TArray.
     *
     * @return array of values, ownership is not passed
    */
	IMPORT_C TextArray* Array() const;

    /**
     * Return the size of a maximal time string formated using the format string 
     * that was supplied during construction of this instance.
     * Two versions to eliminate compiler warnings.
     *
     * @return length of formatted string.
    */	
#ifdef __WINS__
	IMPORT_C const TInt FormattedStringSize() const;
#else
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
     * Returns array element, pass through to contained descriptor array
     *
     * @param aIndex  index of element to return
     * @return descriptor representing array element, ownership is not passed
    */
    IMPORT_C virtual TPtrC MdcaPoint(TInt aIndex) const;
    
protected:
	CAknQueryValueTextArray();
	
	/**
     * 2nd stage construction.
     *
    */
	void ConstructL();
	
private:
	// the following members are not owned
	TextArray* iArray;
	TInt iFormattedStringSize;
	};

#endif // __AKNQUERYVALUETEXT_H__

