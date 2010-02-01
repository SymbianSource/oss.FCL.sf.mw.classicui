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
*     Represents a generic text combo box type control, used to implement the
*     Symbian OS text pop-up field.
*     This control can be constructed directly from resource.
*
*/

// AknPopupFieldText.cpp
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

#include "AknPopupFieldText.h"
#include "AknPanic.h"
#include <barsread.h>

EXPORT_C CAknPopupFieldText::CAknPopupFieldText()
	{}

EXPORT_C CAknPopupFieldText::~CAknPopupFieldText()
	{
	delete iArray;
	delete iTextArray;
	delete iTextValue;
	}


EXPORT_C void CAknPopupFieldText::ConstructFromResourceL(TResourceReader& aReader)
	{
	CAknPopupField::ConstructFromResourceL(aReader);
	TInt textArrayResourceId = aReader.ReadInt32();
	TInt initialIndex = aReader.ReadInt16();

	CommonConstructL(textArrayResourceId, initialIndex);
	}

void CAknPopupFieldText::CommonConstructL(TInt aTextArrayResourceId, TInt aInitialIndex)
	{
 	if (aTextArrayResourceId)
		{
		iArray=iCoeEnv->ReadDesCArrayResourceL(aTextArrayResourceId);
		}
	__ASSERT_DEBUG(iArray, Panic(EAknPanicPopupFieldArrayIsEmpty));
	__ASSERT_DEBUG(iArray->Count()>0, Panic(EAknPanicPopupFieldArrayIsEmpty));


	iTextArray = CAknQueryValueTextArray::NewL();
	iTextArray->SetArray(*iArray);
	
	iTextValue = CAknQueryValueText::NewL();
	iTextValue->SetArrayL(iTextArray);
	SetCurrentValueIndex(aInitialIndex);
	CAknPopupField::SetQueryValueL(iTextValue);
	}

EXPORT_C HBufC* CAknPopupFieldText::CurrentValueTextLC()
	{
	return iTextValue->CurrentValueTextLC();
	}

EXPORT_C TInt CAknPopupFieldText::CurrentValueIndex() const
	{
	return iTextValue->CurrentValueIndex();
	}

EXPORT_C void CAknPopupFieldText::SetCurrentValueIndex(const TInt aIndex)
	{
	iTextValue->SetCurrentValueIndex(aIndex);
	}

EXPORT_C const MDesCArray* CAknPopupFieldText::MdcArray() const
	{
	return iTextValue->MdcArray();
	}

EXPORT_C void CAknPopupFieldText::SetAutoAppend(TBool aAppend)
	{
	iTextValue->SetAutoAppend(aAppend);
	}

void CAknPopupFieldText::ConstructL()
	{
	CAknPopupField::ConstructL();
	}

void CAknPopupFieldText::SetQueryValueL(MAknQueryValue* /*aValue*/) 
	{
	__ASSERT_DEBUG(ETrue, Panic(EAknPanicNotSupported));
	}

EXPORT_C void CAknPopupFieldText::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknPopupField::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CAknPopupFieldText::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

EXPORT_C void CAknPopupFieldText::Reserved_1()
	{}

EXPORT_C void CAknPopupFieldText::Reserved_2()
	{}

// End of File
