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

// AknQueryValueDate.cpp
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#include "eikenv.h"

#include <eikmfne.h>
#include <avkon.hrh>
#include <avkon.rsg>
#include "AknQueryValueDate.h"
#include "AknQueryDialog.h"
#include "aknmfnesettingpage.h"

#include "AknPanic.h"

//-------------------------------------------------
// class CAknQueryValueDate
//-------------------------------------------------

/**
 * First stage of two stage construction.
 */
EXPORT_C CAknQueryValueDate* CAknQueryValueDate::NewL()
	{
	CAknQueryValueDate* self = NewLC();
	CleanupStack::Pop();
	return self;
	}

/**
 * First stage of two stage construction
 */
EXPORT_C CAknQueryValueDate* CAknQueryValueDate::NewLC()
	{
	CAknQueryValueDate* self = new(ELeave) CAknQueryValueDate;
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

/**
 * Destructor.
 */
EXPORT_C CAknQueryValueDate::~CAknQueryValueDate()
	{
	}

/**
 * Set the array.
 * 
 * @param aArray pointer to array, ownership is not passed
 */
EXPORT_C void CAknQueryValueDate::SetArrayL(const CAknQueryValueDateArray* aArray)
	{
	iArray = aArray;
	}

/**
 * Set the string used for the query caption to be a string other than the default.
 *
 * @param aResourceId		resource id of string to use for caption.
 *
 */
EXPORT_C void CAknQueryValueDate::SetQueryCaption(TInt aResourceId)
	{
	iQueryCaptionId = aResourceId;
	}

/**
 * Return the current value, which may have been set by the user
 *
 * @return The current value
 *
 */
EXPORT_C TTime CAknQueryValueDate::Value() const
	{
	return iTime;
	}

/**
 * Returns the array as a descriptor array
 * 
 * @return descriptor array, ownership is not passed
 */
EXPORT_C const MDesCArray* CAknQueryValueDate::MdcArray() const
	{
	return iArray;
	}

/**
 * Returns the current value as text
 * 
 * @return	descriptor representing current value, new 
 * descriptor is created and left on cleanup stack, ownership passed back to client
 */
EXPORT_C HBufC* CAknQueryValueDate::CurrentValueTextLC()
	{
	HBufC* buf = HBufC::NewMaxLC(iArray->FormattedStringSize());
	TPtr ptr = buf->Des();
#ifndef _DEBUG
	iTime.FormatL(ptr, *(iArray->FormatString()));
#else
	TRAPD(err, iTime.FormatL(ptr, *(iArray->FormatString())));
	if(err != KErrNone)
		Panic(EAknPanicQueryDateArrayTimeFormatLeave);
#endif
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
EXPORT_C TInt CAknQueryValueDate::CurrentValueIndex() const
	{
	return iCurrentIndex;
	}

/**
 * Changes the current value to correspond to a value in the array.
 *
 * @param aIndex	index in array of value to set as current
 */
EXPORT_C void CAknQueryValueDate::SetCurrentValueIndex(const TInt aIndex)
	{
	iCurrentIndex = aIndex;
	const CAknQueryValueDateArray::TimeArray* timeArray = iArray->Array();
	if (IsValidIndex(aIndex))
	    iTime = (*timeArray)[aIndex];
	}

/**
 * Creates a dialog containing a query control. If the value is edited and the Dialog
 * OK'd, the new value will be set as the current value. Otherwise the current value 
 * remains unchanged.
 *
 * @return	ETrue if current value was altered; EFalse otherwise
 */
EXPORT_C TBool CAknQueryValueDate::CreateEditorL()
	{
	TBool result = EFalse;

	HBufC* queryString = CEikonEnv::Static()->AllocReadResourceLC(iQueryCaptionId);
	TInt keyPressed;

	if ( iFlags.IsSet( ESettingPageModeBitIndex ) )
		{
		CAknDateSettingPage* dlg =  new ( ELeave ) CAknDateSettingPage ( queryString, 
			EAknSettingPageNoOrdinalDisplayed, EEikCtDateEditor,
			R_AVKON_DEFAULT_SETTING_PAGE_DATE_EDITOR, 0, iTime );
		result =  dlg->ExecuteLD( );

		if ( result )
			keyPressed = EAknSoftkeyOk;
		else
			keyPressed = EAknSoftkeyCancel;
		}
	else
		{
		CAknTimeQueryDialog* dlg = CAknTimeQueryDialog::NewL(iTime);
		dlg->PrepareLC(R_AVKON_DIALOG_QUERY_VALUE_DATE);
		dlg->SetPromptL(*queryString);
		keyPressed = dlg->RunLD();
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
void CAknQueryValueDate::ConstructL()
	{
	iQueryCaptionId = R_AVKON_TBUF_POPUP_FIELD_DEFAULT_DATE_QUERY_PROMPT;
	}

/**
 * Constructor. Does nothing.
 *
 */
CAknQueryValueDate::CAknQueryValueDate()
	{
	}

/**
 * Search for the current time in the list, and set the curent index 
 * to be the found index. If not found, set current index to 1 after the size of the array.
 *
 */
void CAknQueryValueDate::CalculateCurrentIndex()
	{
	// ensure that if the new value is not in the list, the current index is set to the beginning
	TInt index = 0; 
	const CAknQueryValueDateArray::TimeArray* timeArray = iArray->Array();
	TInt length = timeArray->Count();
	// search through array to find match for current value
	TBool match = EFalse;
	for(TInt i = 0; i < length; i++)
		{
		if((*timeArray)[i] == iTime)
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
void CAknQueryValueDate::AppendValueIfNewL()
	{
	const CAknQueryValueDateArray::TimeArray* array = iArray->Array();
	CalculateCurrentIndex();
	if ( iCurrentIndex == array->Count() ) 
		{
		CAknQueryValueDateArray::TimeArray* array = iArray->Array();
		array->AppendL( iTime );
		}
	}

EXPORT_C void CAknQueryValueDate::Reserved_MAknQueryValue()
	{

	};


//-------------------------------------------------
// class CAknQueryValueDateArray
//-------------------------------------------------

/**
 * NewL.
 *
 * @param aResourceId	Recource id of a TBUF containing a TTime format string. Client
 *							can use R_AVKON_TBUF_POPUP_FIELD_DEFAULT_DATE_FORMAT
 *							if desired, or provide its own resource.
 */
EXPORT_C CAknQueryValueDateArray* CAknQueryValueDateArray::NewL(TInt aResourceId)
	{
	CAknQueryValueDateArray* self = NewLC(aResourceId);
	CleanupStack::Pop();
	return self;
	}

/**
 * NewLC.
 *
 * @param aResourceId	Recource id of a TBUF containing a TTime format string. Client
 *							can use R_AVKON_TBUF_POPUP_FIELD_DEFAULT_DATE_FORMAT
 *							if desired, or provide its own resource.
 */
EXPORT_C CAknQueryValueDateArray* CAknQueryValueDateArray::NewLC(TInt aResourceId)
	{
	CAknQueryValueDateArray* self = new(ELeave) CAknQueryValueDateArray;
	CleanupStack::PushL(self);
	self->ConstructL(aResourceId);
	return self;
	}

/**
 * Destructor.
 */
EXPORT_C CAknQueryValueDateArray::~CAknQueryValueDateArray()
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
EXPORT_C void CAknQueryValueDateArray::SetArray(TimeArray& aArray)
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
EXPORT_C CAknQueryValueDateArray::TimeArray* CAknQueryValueDateArray::Array() const
	{
	return iArray;
	}

/**
 * Return the TTime format string that is used to generate MDesCArray values
 *
 * @return format string
 */
EXPORT_C const HBufC* CAknQueryValueDateArray::FormatString() const
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
EXPORT_C const TInt CAknQueryValueDateArray::FormattedStringSize() const
	{
	return iFormattedStringSize;
	}
#else
EXPORT_C TInt CAknQueryValueDateArray::FormattedStringSize() const
	{
	return iFormattedStringSize;
	}
#endif // __WINS__

/**
 * Reports count of contained array
 *
 * @return count of contained array
 */
EXPORT_C TInt CAknQueryValueDateArray::MdcaCount() const
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
EXPORT_C TPtrC CAknQueryValueDateArray::MdcaPoint(TInt aIndex) const
	{
	// only storing the last used string saves memory by avoiding keeping an array 
	// of descriptors in memory. 
	TTime time = (*iArray)[aIndex];
	TPtr textPtr = iLastGeneratedTextValue->Des();

	// clear the last value in case of formatting failure
	textPtr.Zero();

	// we have set the size so that it should have enough room
	TRAPD(err, time.FormatL(textPtr, *iFormatString));
	if(err != KErrNone)
		{
#ifdef _DEBUG
		// only other cause for leave is bad formatting, that must be 
		// caught during debugging of application code
		Panic(EAknPanicQueryDateArrayTimeFormatLeave);
#endif
		}
    AknTextUtils::DisplayTextLanguageSpecificNumberConversion( textPtr );
	return textPtr;
	}

/**
 * Constructor.
 */
CAknQueryValueDateArray::CAknQueryValueDateArray()
	{

	}

/**
 * ConstructL
 *
 * @param aResourceId	id of a resource containing a time format string
 */
void CAknQueryValueDateArray::ConstructL(TInt aResourceId)
	{
	iFormatString = CEikonEnv::Static()->AllocReadResourceL(aResourceId);

	// work out size of a formatted time string, and use this for time string size
	_LIT(KTime, "20030829:"); // should use max characters, "Wednesday 30th September 2003"
	TTime tempTime(KTime);
	HBufC* tempString = HBufC::NewLC(KSafeSizeOfDescriptorForTTimeFormat);
	TPtr ptr = tempString->Des();
	tempTime.FormatL(ptr, *iFormatString);
	iFormattedStringSize = tempString->Length();
	iFormattedStringSize++;
	CleanupStack::PopAndDestroy(); // tempString

	iLastGeneratedTextValue = HBufC::NewL(iFormattedStringSize);
	}

// End of File
