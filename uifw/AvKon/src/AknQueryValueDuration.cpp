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

// AknQueryValueDuration.cpp
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#include "eikenv.h"

#include <eikmfne.h>
#include <avkon.hrh>
#include <avkon.rsg>
#include "AknQueryValueDuration.h"
#include "AknQueryDialog.h"
#include "aknmfnesettingpage.h"

#include "AknPanic.h"

//-------------------------------------------------
// class CAknQueryValueDuration
//-------------------------------------------------

/**
 * First stage of two stage construction.
 */
EXPORT_C CAknQueryValueDuration* CAknQueryValueDuration::NewL()
	{
	CAknQueryValueDuration* self = NewLC();
	CleanupStack::Pop();
	return self;
	}

/**
 * First stage of two stage construction.
 */
EXPORT_C CAknQueryValueDuration* CAknQueryValueDuration::NewLC()
	{
	CAknQueryValueDuration* self = new(ELeave) CAknQueryValueDuration;
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

/**
 * Destructor.
 */
EXPORT_C CAknQueryValueDuration::~CAknQueryValueDuration()
	{
	}

/**
 * Set the array.
 * 
 * @param aArray pointer to array, ownership is not passed
 */
EXPORT_C void CAknQueryValueDuration::SetArrayL(const CAknQueryValueDurationArray* aArray)
	{
	iArray = aArray;
	}

/**
 * Set the string used for the query caption to be a string other than the default.
 *
 * @param aResourceId		resource id of string to use for caption.
 *
 */
EXPORT_C void CAknQueryValueDuration::SetQueryCaption(TInt aResourceId)
	{
	iQueryCaptionId = aResourceId;
	}

/**
 * Return the current value, which may have been set by the user
 *
 * @return The current value
 *
 */
EXPORT_C TTimeIntervalSeconds CAknQueryValueDuration::Value() const
	{
	return iDuration;
	}

/**
 * Returns the array as a descriptor array
 * 
 * @return descriptor array, ownership is not passed
 */
EXPORT_C const MDesCArray* CAknQueryValueDuration::MdcArray() const
	{
	return iArray;
	}

/**
 * Returns the current value as text
 * 
 * @return	descriptor representing current value, new 
 * descriptor is created and left on cleanup stack, ownership passed back to client
 */
EXPORT_C HBufC* CAknQueryValueDuration::CurrentValueTextLC()
	{
	HBufC* buf = HBufC::NewMaxLC(iArray->FormattedStringSize());
	TPtr ptr = buf->Des();
	ptr.Format(*(iArray->FormatString()), iDuration.Int());
		iArray->FormatDuration(ptr, iDuration);
    AknTextUtils::DisplayTextLanguageSpecificNumberConversion(ptr);
	return buf;
	}

/**
 * Returns the index in the array of the current value. 
 * If there are duplicates, returns the index of the first match.
 * If there are no matches, returns zero;
 *
 * @return index in array of current value
 */
EXPORT_C TInt CAknQueryValueDuration::CurrentValueIndex() const
	{
	return iCurrentIndex;
	}

/**
 * Changes the current value to correspond to a value in the array.
 *
 * @param aIndex	index in array of value to set as current
 */
EXPORT_C void CAknQueryValueDuration::SetCurrentValueIndex(const TInt aIndex)
	{
	iCurrentIndex = aIndex;
	const CAknQueryValueDurationArray::DurationArray* durationArray = iArray->Array();
	if (IsValidIndex(aIndex))
	    iDuration = (*durationArray)[aIndex];
	}

/**
 * Creates a dialog containing a query control. If the value is edited and the Dialog
 * OK'd, the new value will be set as the current value. Otherwise the current value 
 * remains unchanged.
 *
 * @return	ETrue if current value was altered; EFalse otherwise
 */
EXPORT_C TBool CAknQueryValueDuration::CreateEditorL()
	{
	TBool result = EFalse;
	TInt keyPressed;

	HBufC* queryString = CEikonEnv::Static()->AllocReadResourceLC(iQueryCaptionId);

	if ( iFlags.IsSet( ESettingPageModeBitIndex ) )
		{
		CAknDurationSettingPage* dlg =  new ( ELeave ) CAknDurationSettingPage ( queryString, 
			EAknSettingPageNoOrdinalDisplayed, EEikCtDurationEditor,
			R_AVKON_DEFAULT_SETTING_PAGE_DURATION_EDITOR, 0, iDuration );
		result =  dlg->ExecuteLD( );

		if ( result )
			keyPressed = EAknSoftkeyOk;
		else
			keyPressed = EAknSoftkeyCancel;
		}
	else
		{
		CAknDurationQueryDialog* dlg = CAknDurationQueryDialog::NewL(iDuration);
		keyPressed = dlg->ExecuteLD(R_AVKON_DIALOG_QUERY_VALUE_DURATION,*queryString);
		}
	
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
void CAknQueryValueDuration::ConstructL()
	{
	iQueryCaptionId = R_AVKON_TBUF_POPUP_FIELD_DEFAULT_DURATION_QUERY_PROMPT;
	}

/**
 * Constructor. Does nothing.
 *
 */
CAknQueryValueDuration::CAknQueryValueDuration()
	{
	}

/**
 * Search for the current value in the list, and set the curent index 
 * to be the found index. If not found, set current index to 1 after the size of the array.
 *
 */
void CAknQueryValueDuration::CalculateCurrentIndex()
	{
	// ensure that if the new value is not in the list, the current index is set to the beginning
	TInt index = 0; 
	const CAknQueryValueDurationArray::DurationArray* durationArray = iArray->Array();
	TInt length = durationArray->Count();
	// search through array to find match for current value
	TBool match = EFalse;
	for(TInt i = 0; i < length; i++)
		{
		if((*durationArray)[i] == iDuration)
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
 */
void CAknQueryValueDuration::AppendValueIfNewL()
	{
	const CAknQueryValueDurationArray::DurationArray* array = iArray->Array();
	CalculateCurrentIndex();
	if ( iCurrentIndex == array->Count() )
		{
		CAknQueryValueDurationArray::DurationArray* array = iArray->Array();
		array->AppendL( iDuration );
		}
	}

EXPORT_C void CAknQueryValueDuration::Reserved_MAknQueryValue()
	{

	};


//-------------------------------------------------
// class CAknQueryValueDurationArray
//-------------------------------------------------

/**
 * NewL.
 *
 * @param aResourceId	Recource id of a TBUF containing a duration format string. Client
 *							can use R_AVKON_TBUF_POPUP_FIELD_DEFAULT_DURATION_FORMAT
 *							if desired, or provide its own resource. (must be at least "%d%d%d")
 */
EXPORT_C CAknQueryValueDurationArray* CAknQueryValueDurationArray::NewL(TInt aResourceId)
	{
	CAknQueryValueDurationArray* self = NewLC(aResourceId);
	CleanupStack::Pop();
	return self;
	}

/**
 * NewLC.
 *
 * @param aResourceId	Recource id of a TBUF containing a duration format string. Client
 *							can use R_AVKON_TBUF_POPUP_FIELD_DEFAULT_DURATION_FORMAT
 *							if desired, or provide its own resource. (must be at least "%d%d%d")
 */
EXPORT_C CAknQueryValueDurationArray* CAknQueryValueDurationArray::NewLC(TInt aResourceId)
	{
	CAknQueryValueDurationArray* self = new(ELeave) CAknQueryValueDurationArray;
	CleanupStack::PushL(self);
	self->ConstructL(aResourceId);
	return self;
	}

/**
 * Destructor.
 */
EXPORT_C CAknQueryValueDurationArray::~CAknQueryValueDurationArray()
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
EXPORT_C void CAknQueryValueDurationArray::SetArray(DurationArray& aArray)
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
EXPORT_C CAknQueryValueDurationArray::DurationArray* CAknQueryValueDurationArray::Array() const
	{
	return iArray;
	}

/**
 * Return the TTime format string that is used to generate MDesCArray values
 *
 * @return format string
 */
EXPORT_C const HBufC* CAknQueryValueDurationArray::FormatString() const
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
EXPORT_C const TInt CAknQueryValueDurationArray::FormattedStringSize() const
	{
	return iFormattedStringSize;
	}
#else
EXPORT_C TInt CAknQueryValueDurationArray::FormattedStringSize() const
	{
	return iFormattedStringSize;
	}
#endif // __WINS__

/**
 * Format a descriptor with the textual version of a duration, formated according to the format string. 
 * Number of hours is not bounded.
 *
 * @param aText descriptor to be filled, must be of sufficient size
 * @param aDuration the interval to be formatted
 *
 */
EXPORT_C void CAknQueryValueDurationArray::FormatDuration(TPtr& aText, TTimeIntervalSeconds aDuration) const
	{
	TInt timeIntervalSeconds=aDuration.Int();
	TInt second=timeIntervalSeconds%60;
	timeIntervalSeconds/=60;
	TInt minute=timeIntervalSeconds%60;
	timeIntervalSeconds/=60;
	TInt hour=timeIntervalSeconds%24;

	aText.Format(iFormatString->Des(), hour, minute, second);
    AknTextUtils::DisplayTextLanguageSpecificNumberConversion( aText );
	}

/**
 * Reports count of contained array
 *
 * @return count of contained array
 */
EXPORT_C TInt CAknQueryValueDurationArray::MdcaCount() const
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
EXPORT_C TPtrC CAknQueryValueDurationArray::MdcaPoint(TInt aIndex) const
	{
	// only storing the last used string saves memory by avoiding keeping an array 
	// of descriptors in memory. 
	TTimeIntervalSeconds duration = (*iArray)[aIndex];

	TPtr textPtr = iLastGeneratedTextValue->Des();
	FormatDuration(textPtr, duration);
	return textPtr;
	}

/**
 * Constructor.
 */
CAknQueryValueDurationArray::CAknQueryValueDurationArray()
	{

	}

/**
 * ConstructL
 *
 * @param aResourceId	id of a resource containing a time format string
 */
void CAknQueryValueDurationArray::ConstructL(TInt aResourceId)
	{
	iFormatString = CEikonEnv::Static()->AllocReadResourceL(aResourceId);
	iFormattedStringSize = KSafeSizeOfDescriptorForDurationFormat;
	iLastGeneratedTextValue = HBufC::NewL(iFormattedStringSize);
	}

// End of File
