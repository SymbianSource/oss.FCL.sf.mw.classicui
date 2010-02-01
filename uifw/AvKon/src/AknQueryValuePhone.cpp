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

// AknQueryValuePhone.cpp
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#include "eikenv.h"

#include <eikmfne.h>
#include <avkon.hrh>
#include <avkon.rsg>
#include "AknQueryValuePhone.h"
#include "AknQueryDialog.h"
#include "akntextsettingpage.h"

#include "AknPanic.h"

//-------------------------------------------------
// class CAknQueryValuePhone
//-------------------------------------------------

/**
 * First stage of two stage construction.
 */
EXPORT_C CAknQueryValuePhone* CAknQueryValuePhone::NewL()
	{
	CAknQueryValuePhone* self = NewLC();
	CleanupStack::Pop();
	return self;
	}

/**
 * First stage of two stage construction.
 */
EXPORT_C CAknQueryValuePhone* CAknQueryValuePhone::NewLC()
	{
	CAknQueryValuePhone* self = new(ELeave) CAknQueryValuePhone;
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

/**
 * Destructor.
 */
EXPORT_C CAknQueryValuePhone::~CAknQueryValuePhone()
	{
	delete iText;
	}

/**
 * Set the array.
 * 
 * @param aArray pointer to array, ownership is not passed
 */
EXPORT_C void CAknQueryValuePhone::SetArrayL(const CAknQueryValuePhoneArray* aArray)
	{
	iArray = aArray;
	}

/**
 * Set the string used for the query caption to be a string other than the default.
 *
 * @param aResourceId		resource id of string to use for caption.
 *
 */
EXPORT_C void CAknQueryValuePhone::SetQueryCaption(TInt aResourceId)
	{
	iQueryCaptionId = aResourceId;
	}

/**
 * Return the current value, which may have been set by the user
 *
 * @return The current value, ownership is not passed
 *
 */
EXPORT_C HBufC* CAknQueryValuePhone::Value() const
	{
	return iText;
	}

/**
 * Returns the array as a descriptor array
 * 
 * @return descriptor array, ownership is not passed
 */
EXPORT_C const MDesCArray* CAknQueryValuePhone::MdcArray() const
	{
	return iArray;
	}

/**
 * Returns the current value as text
 * 
 * @return	descriptor representing current value, new 
 * descriptor is created and left on cleanup stack, ownership passed back to client
 */
EXPORT_C HBufC* CAknQueryValuePhone::CurrentValueTextLC()
	{
	HBufC* buf = HBufC::NewMaxLC(iText->Length());
	TPtr ptr = buf->Des();
	ptr = *iText;
	return buf;
	}

/**
 * Returns the index in the array of the current value. 
 * If there are duplicates, returns the index of the first match.
 * If there are no matches, returns zero;
 *
 * @return index in array of current value
 */
EXPORT_C TInt CAknQueryValuePhone::CurrentValueIndex() const
	{
	return iCurrentIndex;
	}

/**
 * Changes the current value to correspond to a value in the array.
 *
 * @param aIndex	index in array of value to set as current
 */
EXPORT_C void CAknQueryValuePhone::SetCurrentValueIndex(const TInt aIndex)
	{
	iCurrentIndex = aIndex;
	const CAknQueryValuePhoneArray::TextArray* textArray = iArray->Array();
	if (IsValidIndex(aIndex))
	    {
	    TPtrC newPtr = textArray->MdcaPoint(aIndex); 
	    TPtr currentPtr = iText->Des();
	    currentPtr = newPtr;
	    }
	}

/**
 * Creates a dialog containing a query control. If the value is edited and the Dialog
 * OK'd, the new value will be set as the current value. Otherwise the current value 
 * remains unchanged.
 *
 * @return	ETrue if current value was altered; EFalse otherwise
 */
EXPORT_C TBool CAknQueryValuePhone::CreateEditorL()
	{
	TBool result = EFalse;
	TInt keyPressed;

	HBufC* queryString = CEikonEnv::Static()->AllocReadResourceLC(iQueryCaptionId);
	TPtr textPtr = iText->Des();

	if ( iFlags.IsSet( ESettingPageModeBitIndex ) )
		{
		CAknTextSettingPage* dlg =  new ( ELeave ) CAknTextSettingPage ( queryString, 
			EAknSettingPageNoOrdinalDisplayed, EEikCtEdwin,
			R_AVKON_DEFAULT_SETTING_PAGE_TEXT_EDITOR, 0, textPtr );
		result =  dlg->ExecuteLD( );

		if ( result )
			keyPressed = EAknSoftkeyOk;
		else
			keyPressed = EAknSoftkeyCancel;
		}
	else
		{
		CAknTextQueryDialog* dlg = CAknTextQueryDialog::NewL(textPtr);
		keyPressed = dlg->ExecuteLD(R_AVKON_DIALOG_QUERY_VALUE_PHONE,*queryString);
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
void CAknQueryValuePhone::ConstructL()
	{
	iQueryCaptionId = R_AVKON_TBUF_POPUP_FIELD_DEFAULT_PHONE_QUERY_PROMPT;
	iText = HBufC::NewL(CAknQueryValuePhoneArray::KSafeSizeOfDescriptorForPhoneFormat);
	}

/**
 * Constructor. Does nothing.
 *
 */
CAknQueryValuePhone::CAknQueryValuePhone()
	{
	}

/**
 * Search for the current value in the list, and set the curent index 
 * to be the found index. If not found, set current index to 1 after the size of the array.
 *
 */
void CAknQueryValuePhone::CalculateCurrentIndex()
	{
	// ensure that if the new value is not in the list, the current index is set to the beginning
	TInt index = 0; 
	const CAknQueryValuePhoneArray::TextArray* textArray = iArray->Array();
	TInt length = textArray->MdcaCount();
	// search through array to find match for current value
	TBool match = EFalse;
	for(TInt i = 0; i < length; i++)
		{
		TInt res = textArray->MdcaPoint(i).Compare(*iText);
		if(res == 0)
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
void CAknQueryValuePhone::AppendValueIfNewL()
	{
	const CAknQueryValuePhoneArray::TextArray* array = iArray->Array();
	CalculateCurrentIndex();
	if ( iCurrentIndex == array->MdcaCount() )
		{
		CAknQueryValuePhoneArray::TextArray* array = iArray->Array();
		array->AppendL(*iText);
		}
	}

EXPORT_C void CAknQueryValuePhone::Reserved_MAknQueryValue()
	{

	};


//-------------------------------------------------
// class CAknQueryValuePhoneArray
//-------------------------------------------------

/**
 * NewL.
 *
 */
EXPORT_C CAknQueryValuePhoneArray* CAknQueryValuePhoneArray::NewL()
	{
	CAknQueryValuePhoneArray* self = NewLC();
	CleanupStack::Pop();
	return self;
	}

/**
 * NewLC.
 *
 */
EXPORT_C CAknQueryValuePhoneArray* CAknQueryValuePhoneArray::NewLC()
	{
	CAknQueryValuePhoneArray* self = new(ELeave) CAknQueryValuePhoneArray;
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

/**
 * Destructor.
 */
EXPORT_C CAknQueryValuePhoneArray::~CAknQueryValuePhoneArray()
	{
	}

/**
 * Set the array of values. 
 * Note that client can use any implementation of array class, but must pass in a 
 * TArray generated from it (by calling the Array() method on the array class)
 *
 * @param array of values, ownership is passed
 */
EXPORT_C void CAknQueryValuePhoneArray::SetArray(TextArray& aArray)
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
EXPORT_C CAknQueryValuePhoneArray::TextArray* CAknQueryValuePhoneArray::Array() const
	{
	return iArray;
	}

/**
 * Return the size of a maximal time string formated using the format string 
 * that was supplied during construction of this instance.
 * Two versions to eliminate compiler warnings.
 *
 * @return length of formatted string.
 */
#ifdef __WINS__
EXPORT_C const TInt CAknQueryValuePhoneArray::FormattedStringSize() const
	{
	return iFormattedStringSize;
	}
#else
EXPORT_C TInt CAknQueryValuePhoneArray::FormattedStringSize() const
	{
	return iFormattedStringSize;
	}
#endif // __WINS__


/**
 * Reports count of contained array
 *
 * @return count of contained array
 */
EXPORT_C TInt CAknQueryValuePhoneArray::MdcaCount() const
	{
	return iArray->MdcaCount();
	}

/**
 * Returns array element, pass through to contained descriptor array
 *
 * @param index of element to return
 * @return descriptor representing array element, ownership is not passed
 */
EXPORT_C TPtrC CAknQueryValuePhoneArray::MdcaPoint(TInt aIndex) const
	{
	return iArray->MdcaPoint(aIndex);
	}

/**
 * Constructor.
 */
CAknQueryValuePhoneArray::CAknQueryValuePhoneArray()
	{

	}

/**
 * ConstructL
 *
 * @param aResourceId	id of a resource containing a time format string
 */
void CAknQueryValuePhoneArray::ConstructL()
	{
	iFormattedStringSize = KSafeSizeOfDescriptorForPhoneFormat;
	}

// End of File
