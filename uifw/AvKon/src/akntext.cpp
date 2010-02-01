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
*     Stores and handles text labels for note dialogs. Each note dialog
*     can have two different labels, one singular and one plural labels.
*     For example:-
*        "You have 1 new message" is the singular label and
*        "You have 2 new messages" is the plural label.
*     This class supports the ability to change number inside the label, e.g.:-
*        "You have 100 new messages" is also supported.
*
*/


#include <StringLoader.h>
#include "AknPanic.h"
#include "akntext.h"
#include "AknUtils.h"


_LIT(KNumberId, "%N");
_LIT(KDigitId,  "%d");
_LIT(KUnsignedId, "%U");

CAknText::CAknText()
	{
	iPlurality = ENotSpecified;
	iType      = ENotFormatted;
	}

CAknText::CAknText(const TType& aType) : iType(aType)
	{
	iPlurality = ENotSpecified;
	}

CAknText::~CAknText()
	{
	delete iUnformattedSingularText;
	delete iUnformattedPluralText;
	delete iText;
	delete iTextCopy;
	}
	

void CAknText::ConstructFromResourceL(TResourceReader& aRes)
	{
	if (iType == ENotFormatted)
		{
	    iUnformattedSingularText = aRes.ReadHBufCL();
	    iUnformattedPluralText   = aRes.ReadHBufCL();

	    if (iUnformattedSingularText)
			iPlurality = ESingular;

		if (iUnformattedPluralText && !iUnformattedSingularText)
			iPlurality = EPlural;

		FormatL();
		}
	else if (iType == EFormatted)
		{
		iText = aRes.ReadHBufCL();
		if (iText)
			iTextCopy = iText->Des().AllocL();
		}
	}

CAknText& CAknText::operator=(CAknText& aNoteText)
	{
	if (&aNoteText == this)
		return *this;

	iType = aNoteText.iType;

	if (aNoteText.iPlurality != ENotSpecified)
		iPlurality = aNoteText.iPlurality;

	if (aNoteText.iNumberHasBeenSet)
		{
		iNumber           = aNoteText.iNumber;
		iNumberHasBeenSet = aNoteText.iNumberHasBeenSet;
		}

#define __TRANSFER_PTR_(P1,P2)  if (P1) { delete P2; P2 = P1; P1 = NULL; } 
	
	__TRANSFER_PTR_(aNoteText.iUnformattedSingularText,iUnformattedSingularText);
	__TRANSFER_PTR_(aNoteText.iUnformattedPluralText,iUnformattedPluralText);
	__TRANSFER_PTR_(aNoteText.iText,iText);
	__TRANSFER_PTR_(aNoteText.iTextCopy,iTextCopy);
	    
#undef  __TRASFER_PTR_

	TRAP_IGNORE(FormatL());
	return *this;
	}


void CAknText::SetPluralityL(TBool aIsPlural)
	{
	iType = ENotFormatted;
	if (aIsPlural)
		iPlurality = EPlural;
	else
		iPlurality = ESingular;
	FormatL();
	}

void CAknText::SetNumberL(TInt aNumber)
	{
	iType = ENotFormatted;
	iNumberHasBeenSet = ETrue;
	iNumber = aNumber;
	SetPluralityL(iNumber > 1); 
	}

void CAknText::DoSetTextL(HBufC*& aBuffer, const TDesC& aText)
	{
	if (!aBuffer || aBuffer->Des().MaxLength() < aText.Length() )
		{
		delete aBuffer;
		aBuffer = NULL;
		aBuffer = aText.AllocL();
		}
	else 
		{
		*aBuffer = aText;
		}
	}

void CAknText::SetL(const TDesC& aText)
	{
	if (TextIsNotFormatted(aText))
		{
		if (iPlurality == ESingular)
			{
			DoSetTextL(iUnformattedSingularText,aText);
			}
		else
			{
			DoSetTextL(iUnformattedPluralText,aText);
			}
		FormatL();
		}
	else
		{
		DoSetTextL(iText,aText);
		DoSetTextL(iTextCopy,aText);
		iType = EFormatted;
		}
	}

/**
 * Return a copy of the text, that the client can modify
 */
TPtr CAknText::Get() const
	{
	if (iText && iTextCopy)
		{
		if (iTextCopy->Des().MaxLength() >= iText->Des().Length())
			{
			*iTextCopy = *iText;
			return iTextCopy->Des(); 
			}
		}
	return TPtr(0,0);
	}

void CAknText::FormatL()
	{
	if (iType == EFormatted)
		return;

	if (iPlurality == ENotSpecified)
		return;

	if (iPlurality == ESingular && iUnformattedSingularText)
		DoFormatTextL(iUnformattedSingularText);
	
	else if (iPlurality == EPlural && iUnformattedPluralText)
		DoFormatTextL(iUnformattedPluralText);
	}

void CAknText::DoFormatTextL(HBufC* aUnformattedText)
	{
	__ASSERT_DEBUG(aUnformattedText,Panic(EAknPanicNullPointer));

	TPtr unformattedText = TranslateDintoN(aUnformattedText);

	TInt len = aUnformattedText->Length() + 10; //10 is because biggest int32 has 10 digits at most
	if (!iText || iText->Des().MaxLength() < len)
		{
		delete iText;
		iText = NULL;
		iText = HBufC::NewL(len); 
		}

	TPtr formattedText = iText->Des();
    

    if ( unformattedText.Find(KNumberId) != KErrNotFound) // threre is a number key
        {    
        StringLoader::Format( formattedText, unformattedText, -1, iNumber);
        }
    else
    	{
        formattedText.Zero();
        formattedText.Append(unformattedText);
	    }	


	if (iText && (!iTextCopy || iTextCopy->Des().MaxLength() < iText->Des().Length()))
		{
		delete iTextCopy;
		iTextCopy = NULL;
		iTextCopy = iText->Des().AllocL();
		}
	}

// Translate %d and %U into %N
TPtr CAknText::TranslateDintoN(HBufC* aUnformattedText)
	{
	TPtr text = aUnformattedText->Des();
	
	TInt pos = text.Find(KDigitId);
    if ( pos == KErrNotFound )
        {
        pos = text.Find(KUnsignedId);
        }
	if (pos != KErrNotFound)
		{
		text[pos+1] = 'N';
		}
	
	return text;
	}
	
TBool CAknText::TextIsNotFormatted(const TDesC& aText)
	{
	return ( ( (aText.Find(KNumberId) != KErrNotFound) ||
				(aText.Find(KDigitId) != KErrNotFound) ) && iType == ENotFormatted);

	}

// End of File
