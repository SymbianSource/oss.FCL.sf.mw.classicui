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
*     Used to decorate an MDesCArray with an extra entry.
*     
*
*/

// AknDesCArrayDecorator.cpp
//
// 2001 Symbian Ltd.  All rights reserved.
//

#include "AknDesCArrayDecorator.h"
#include "AknPanic.h"

EXPORT_C TAknDesCArrayDecorator::TAknDesCArrayDecorator()
: iArray(0), iActive(EFalse)
	{
	// iText does not need to be initialised, as default ctor for TPtrC sets it to zero length.
	}

EXPORT_C void TAknDesCArrayDecorator::SetArray(const MDesCArray* aArray)
	{
	iArray = aArray;
	}

EXPORT_C void TAknDesCArrayDecorator::SetDecorationText(const TDesC& aText)
	{
	iText.Set(aText);
	}

EXPORT_C void TAknDesCArrayDecorator::SetActive(const TBool aActive)
	{
	iActive = aActive;
	}

EXPORT_C TBool TAknDesCArrayDecorator::DecoratedIndex(TInt& aIndex) const
	{
	__TEST_INVARIANT;

	aIndex = iArray->MdcaCount();

	return iActive;
	}

EXPORT_C TInt TAknDesCArrayDecorator::MdcaCount() const
	{
	__TEST_INVARIANT;

	TInt count = iArray->MdcaCount();

	if(iActive)
		count++;
	
	return count;
	}

EXPORT_C TPtrC TAknDesCArrayDecorator::MdcaPoint(TInt aIndex) const
	{
	__TEST_INVARIANT;
	__ASSERT_DEBUG(aIndex < MdcaCount(),Panic(EAknPanicDCADecoratorIndexOutOfRange));

	
	if(iActive && (aIndex == iArray->MdcaCount()))
		{// we need to return the "extra" entry off the end of the array
		return iText;
		}

	// otherwise just pass on the real value
	return iArray->MdcaPoint(aIndex);
	}

// debug only invariant function
EXPORT_C void TAknDesCArrayDecorator::__DbgTestInvariant() const          
	{    
#if defined(_DEBUG)
	TBool invalid = EFalse;
	if(iActive && iText.Length() == 0)
		invalid = ETrue;
	if(!iArray)
		invalid = ETrue;
	if(invalid)                
		User::Invariant();    
#endif          
	}
