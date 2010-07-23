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

// AknQueryValueDuration.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#if !defined(__AKNQUERYVALUEDURATION_H__)
#define __AKNQUERYVALUEDURATION_H__

#include <bamdesca.h>
#include <eikdialg.h>
#include "AknQueryValue.h"

class CAknQueryValueDurationArray;

/**
 * Encapsulates a TTimeIntervalSeconds. Provides an interface to create a dialog
 * containing a duration query control, which will edit the value. Optionally 
 * allows the value to be changed by selecting from a list of values. 
 *
 */
NONSHARABLE_CLASS(CAknQueryValueDuration) : public CAknQueryValue
    {
public:
    /**
     * Two-phased constructor.
     *
    */
	IMPORT_C static CAknQueryValueDuration* NewL();
	
    /**
     * Two-phased constructor.
     *
    */
	IMPORT_C static CAknQueryValueDuration* NewLC();
    IMPORT_C virtual ~CAknQueryValueDuration();
    
    /**
     * Set the array.
     * 
     * @param aArray pointer to array, ownership is not passed
    */
	IMPORT_C void SetArrayL(const CAknQueryValueDurationArray* aArray);
	
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
	IMPORT_C TTimeIntervalSeconds Value() const;
	
public: // from MAknQueryValue
    IMPORT_C virtual const MDesCArray* MdcArray() const;
    IMPORT_C virtual HBufC* CurrentValueTextLC();
    IMPORT_C virtual TInt CurrentValueIndex() const;
    IMPORT_C virtual void SetCurrentValueIndex(const TInt aIndex);
    IMPORT_C virtual TBool CreateEditorL();
protected:
	CAknQueryValueDuration();
	
    /**
     * 2nd stage construction.
     *
    */
	void ConstructL();
	
	/**
     * Search for the current value in the list, and set the curent index 
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
	TTimeIntervalSeconds iDuration;
	TInt iCurrentIndex;
	// the following are not owned
	const CAknQueryValueDurationArray* iArray;
    };


/**
 * Wraps an array of numeric values, adapts it into a descriptor array.
 *
 */
NONSHARABLE_CLASS(CAknQueryValueDurationArray) : public CBase, public MDesCArray
	{
public:
    /**
     * Typedef for array containing TTimeIntervalSeconds items
     *
    */
	typedef CArrayFix<TTimeIntervalSeconds> DurationArray;
	
	enum {KSafeSizeOfDescriptorForDurationFormat = 32};
	
public:
    /**
     * Two-phased constructor..
     *
     * @param aResourceId	Recource id of a TBUF containing a duration format string. Client
     *							can use R_AVKON_TBUF_POPUP_FIELD_DEFAULT_DURATION_FORMAT
     *							if desired, or provide its own resource. (must be at least "%d%d%d")
    */
	IMPORT_C static CAknQueryValueDurationArray* NewL(TInt aResourceId);
	
    /**
     * See NewL
     *
    */
	IMPORT_C static CAknQueryValueDurationArray* NewLC(TInt aResourceId);
	
	IMPORT_C ~CAknQueryValueDurationArray();
	
    /**
     * Set the array of values. 
     * Note that client can use any implementation of array class, but must pass in a 
     * TArray generated from it (by calling the Array() method on the array class)
     *
     * @param aArray   array of values, ownership is not passed
    */
	IMPORT_C void SetArray(DurationArray& aArray);
	
    /**
     * Get the array of values as a TArray. 
     * Note that client can use any implementation of array class, but the array is 
     * treated as a TArray.
     *
     * @return array of values, ownership is not passed
    */
	IMPORT_C DurationArray* Array() const;
	
    /**
     * Return the TTime format string that is used to generate MDesCArray values
     *
     * @return format string
    */
	IMPORT_C const HBufC* FormatString() const;
	
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

   /**
    * Format a descriptor with the textual version of a duration, formated according to the format string. 
     * Number of hours is not bounded.
     *
     * @param aText descriptor to be filled, must be of sufficient size
     * @param aDuration the interval to be formatted
     *
    */
	IMPORT_C void FormatDuration(TPtr& aText, TTimeIntervalSeconds aDuration) const;
	
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
     * @param aIndex   index of element to return
     * @return descriptor representing array element, ownership is not passed
    */
    IMPORT_C virtual TPtrC MdcaPoint(TInt aIndex) const;
    
protected:
	CAknQueryValueDurationArray();
	
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
	DurationArray* iArray;
	TInt iFormattedStringSize;
	};


#endif // __AKNQUERYVALUEDURATION_H__

