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

// AknQueryValueNumber.cpp
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#include "eikenv.h"

#include <eikmfne.h>
#include <avkon.hrh>
#include <avkon.rsg>
#include "AknQueryValueNumber.h"
#include "AknQueryDialog.h"

#include "AknPanic.h"

//-------------------------------------------------
// class CAknQueryValueNumber
//-------------------------------------------------

/**
 * First stage of two stage construction.
 */
EXPORT_C CAknQueryValueNumber* CAknQueryValueNumber::NewL()
	{
	CAknQueryValueNumber* self = NewLC();
	CleanupStack::Pop();
	return self;
	}

/**
 * First stage of two stage construction.
 */
EXPORT_C CAknQueryValueNumber* CAknQueryValueNumber::NewLC()
	{
	CAknQueryValueNumber* self = new(ELeave) CAknQueryValueNumber;
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

/**
 * Destructor.
 */
EXPORT_C CAknQueryValueNumber::~CAknQueryValueNumber()
	{
	}

/**
 * Set the array.
 * 
 * @param aArray pointer to array, ownership is not passed
 */
EXPORT_C void CAknQueryValueNumber::SetArrayL(const CAknQueryValueNumberArray* aArray)
	{
	iArray = aArray;
	}

/**
 * Set the string used for the query caption to be a string other than the default.
 *
 * @param aResourceId		resource id of string to use for caption.
 *
 */
EXPORT_C void CAknQueryValueNumber::SetQueryCaption(TInt aResourceId)
	{
	iQueryCaptionId = aResourceId;
	}

/**
 * Return the current value, which may have been set by the user
 *
 * @return The current value
 *
 */
EXPORT_C TInt CAknQueryValueNumber::Value() const
	{
	return iNumber;
	}

/**
 * Returns the array as a descriptor array
 * 
 * @return descriptor array, ownership is not passed
 */
EXPORT_C const MDesCArray* CAknQueryValueNumber::MdcArray() const
	{
	return iArray;
	}

/**
 * Returns the current value as text
 * 
 * @return	descriptor representing current value, new 
 * descriptor is created and left on cleanup stack, ownership passed back to client
 */
EXPORT_C HBufC* CAknQueryValueNumber::CurrentValueTextLC()
	{
	HBufC* buf = HBufC::NewMaxLC(iArray->FormattedStringSize());
	TPtr ptr = buf->Des();
	ptr.Format(*(iArray->FormatString()), iNumber);
    AknTextUtils::DisplayTextLanguageSpecificNumberConversion( ptr );
	return buf;
	}

/**
 * Returns the index in the array of the current value. 
 * If there are duplicates, returns the index of the first match.
 * If there are no matches, returns zero;
 *
 * @return index in array of current value
 */
EXPORT_C TInt CAknQueryValueNumber::CurrentValueIndex() const
	{
	return iCurrentIndex;
	}

/**
 * Changes the current value to correspond to a value in the array.
 *
 * @param aIndex	index in array of value to set as current
 */
EXPORT_C void CAknQueryValueNumber::SetCurrentValueIndex(const TInt aIndex)
	{
	iCurrentIndex = aIndex;
	const CAknQueryValueNumberArray::NumberArray* numberArray = iArray->Array();
	if (IsValidIndex(iCurrentIndex))
	    iNumber = (*numberArray)[aIndex];
	}

/**
 * Creates a dialog containing a query control. If the value is edited and the Dialog
 * OK'd, the new value will be set as the current value. Otherwise the current value 
 * remains unchanged.
 *
 * @return	ETrue if current value was altered; EFalse otherwise
 */
EXPORT_C TBool CAknQueryValueNumber::CreateEditorL()
	{
	TBool result = EFalse;

	HBufC* queryString = CEikonEnv::Static()->AllocReadResourceLC(iQueryCaptionId);
	CAknNumberQueryDialog* dlg = CAknNumberQueryDialog::NewL(iNumber);
	TInt keyPressed = dlg->ExecuteLD(R_AVKON_DIALOG_QUERY_VALUE_NUMBER,*queryString);
	CleanupStack::PopAndDestroy(); // queryString
	
	switch(keyPressed)
		{
	case EAknSoftkeyOk:
		result = ETrue;
		if ( iFlags.IsSet( EAutoAppendBitIndex ) )
			{
			AppendValueIfNewL();
			}
		CalculateCurrentIndex();
		break;
	case EAknSoftkeyCancel:
		// fall through
	case EAknSoftkeyBack:
		// fall through
	default:
		result = EFalse;
		break;
		}

	return result;
	}

/**
 * Two stage construction
 *
 */
void CAknQueryValueNumber::ConstructL()
	{
	iQueryCaptionId = R_AVKON_TBUF_POPUP_FIELD_DEFAULT_NUMBER_QUERY_PROMPT;
	}

/**
 * Constructor.
 *
 */
CAknQueryValueNumber::CAknQueryValueNumber()
	{
	}

/**
 * Search for the current value in the list, and set the curent index 
 * to be the found index. If not found, set current index to 1 after the size of the array.
 *
 */
void CAknQueryValueNumber::CalculateCurrentIndex()
	{
	// ensure that if the new value is not in the list, the current index is set to the beginning
	TInt index = 0; 
	const CAknQueryValueNumberArray::NumberArray* numberArray = iArray->Array();
	TInt length = numberArray->Count();
	// search through array to find match for current value
	TBool match = EFalse;
	for(TInt i = 0; i < length; i++)
		{
		if((*numberArray)[i] == iNumber)
			{
			index = i;
			match = ETrue;
			break;
			}
		}
	if(!match)
		index = length;
	iCurrentIndex = index;
	}

/**
 * Append the current value if it is new
 *
 *
 */
void CAknQueryValueNumber::AppendValueIfNewL()
	{
	const CAknQueryValueNumberArray::NumberArray* array = iArray->Array();
	CalculateCurrentIndex();
	if ( iCurrentIndex == array->Count() ) 
		{
		CAknQueryValueNumberArray::NumberArray* array = iArray->Array();
		array->AppendL( iNumber );
		}
	}

EXPORT_C void CAknQueryValueNumber::Reserved_MAknQueryValue()
	{

	};


//-------------------------------------------------
// class CAknQueryValueNumberArray
//-------------------------------------------------

/**
 * NewL.
 *
 * @param aResourceId	Recource id of a TBUF containing a number format string. Client
 *							can use R_AVKON_TBUF_POPUP_FIELD_DEFAULT_NUMBER_FORMAT
 *							if desired, or provide its own resource. 
 */
EXPORT_C CAknQueryValueNumberArray* CAknQueryValueNumberArray::NewL(TInt aResourceId)
	{
	CAknQueryValueNumberArray* self = NewLC(aResourceId);
	CleanupStack::Pop();
	return self;
	}

/**
 * NewLC.
 *
 * @param aResourceId	Recource id of a TBUF containing a number format string. Client
 *							can use R_AVKON_TBUF_POPUP_FIELD_DEFAULT_NUMBER_FORMAT
 *							if desired, or provide its own resource. 
 */
EXPORT_C CAknQueryValueNumberArray* CAknQueryValueNumberArray::NewLC(TInt aResourceId)
	{
	CAknQueryValueNumberArray* self = new(ELeave) CAknQueryValueNumberArray;
	CleanupStack::PushL(self);
	self->ConstructL(aResourceId);
	return self;
	}

/**
 * Destructor.
 */
EXPORT_C CAknQueryValueNumberArray::~CAknQueryValueNumberArray()
	{
	delete iLastGeneratedTextValue;
	delete iFormatString;
	}

/**
 * Set the array of values. 
 * Note that client can use any implementation of array class, but must pass in a 
 * TArray generated from it (by calling the Array() method on the array class)
 *
 * @param array of values, ownership is not passed
 */
EXPORT_C void CAknQueryValueNumberArray::SetArray(NumberArray& aArray)
	{
	iArray = &aArray;
	}

/**
 * Get the array of values as a TArray. 
 * Note that client can use any implementation of array class, but the array is 
 * treated as a TArray.
 *
 * @return array of values, ownership is not passed
 */
EXPORT_C CAknQueryValueNumberArray::NumberArray* CAknQueryValueNumberArray::Array() const
	{
	return iArray;
	}

/**
 * Return the TTime format string that is used to generate MDesCArray values
 *
 * @return format string
 */
EXPORT_C const HBufC* CAknQueryValueNumberArray::FormatString() const
	{
	return iFormatString;
	}

/**
 * Return the size of a maximal time string formated using the format string 
 * that was supplied during construction of this instance.
 * Two versions to eliminate compiler warnings.
 *
 * @return length of formatted string.
 */
#ifdef __WINS__
EXPORT_C const TInt CAknQueryValueNumberArray::FormattedStringSize() const
	{
	return iFormattedStringSize;
	}
#else
EXPORT_C TInt CAknQueryValueNumberArray::FormattedStringSize() const
	{
	return iFormattedStringSize;
	}
#endif // __WINS__


/**
 * Reports count of contained array
 *
 * @return count of contained array
 */
EXPORT_C TInt CAknQueryValueNumberArray::MdcaCount() const
	{
	return iArray->Count();
	}

/**
 * Returns array element, converting value to text. 
 * <p> WARNING: the returned pointer is only valid until the next time this
 * method is invoked. 
 *
 * @param index of element to return
 * @return descriptor representing array element, ownership is not passed
 */
EXPORT_C TPtrC CAknQueryValueNumberArray::MdcaPoint(TInt aIndex) const
	{
	// only storing the last used string saves memory by avoiding keeping an array 
	// of descriptors in memory. 
	TInt number = (*iArray)[aIndex];
	TPtr textPtr = iLastGeneratedTextValue->Des();
	TPtr formatPtr = iFormatString->Des();
	textPtr.Format(formatPtr, number);
    AknTextUtils::DisplayTextLanguageSpecificNumberConversion( textPtr );
    return textPtr;
	}

/**
 * Constructor.
 */
CAknQueryValueNumberArray::CAknQueryValueNumberArray()
	{

	}

/**
 * ConstructL
 *
 * @param aResourceId	id of a resource containing a time format string
 */
void CAknQueryValueNumberArray::ConstructL(TInt aResourceId)
	{
	iFormatString = CEikonEnv::Static()->AllocReadResourceL(aResourceId);
	iFormattedStringSize = KSafeSizeOfDescriptorForNumberFormat;
	iLastGeneratedTextValue = HBufC::NewL(iFormattedStringSize);
	}

// End of File
