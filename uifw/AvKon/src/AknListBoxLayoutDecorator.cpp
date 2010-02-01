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
*     Decorates a descriptor array to include tabs suitable for list box formatting
*     
*
*/

// AknListBoxLayoutDecorator.cpp
//
// 2001 Symbian Ltd.  All rights reserved.
//

#include <eikenv.h>

#include "AknListBoxLayoutDecorator.h"
#include "AknPanic.h"

EXPORT_C CAknListBoxLayoutDecorator* CAknListBoxLayoutDecorator::NewL()
	{
	CAknListBoxLayoutDecorator* self = NewLC();
	CleanupStack::Pop();
	return self;
	}

EXPORT_C CAknListBoxLayoutDecorator* CAknListBoxLayoutDecorator::NewLC()
	{
	CAknListBoxLayoutDecorator* self = new(ELeave) CAknListBoxLayoutDecorator;
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

EXPORT_C CAknListBoxLayoutDecorator::~CAknListBoxLayoutDecorator()
	{
	delete iLastGeneratedTextValue;
	}

EXPORT_C const MDesCArray* CAknListBoxLayoutDecorator::Array() const
	{
	return iArray;
	}

EXPORT_C void CAknListBoxLayoutDecorator::SetArray(const MDesCArray* aArray)
	{
	iArray = aArray;
	}

EXPORT_C void CAknListBoxLayoutDecorator::SetLeadingDecorationTextL(const TDesC& aText)
	{
	TInt delta = aText.Length() - iLeadingDecorationText.Length();
	if(delta > 0)
		{
		TInt newLength = iLastGeneratedTextValue->Des().MaxLength() + delta;
		iLastGeneratedTextValue = iLastGeneratedTextValue->ReAllocL(newLength); // does not get changed if ReAllocL leaves
		}

	iLeadingDecorationText.Set(aText);
	}

EXPORT_C void CAknListBoxLayoutDecorator::SetTrailingDecorationTextL(const TDesC& aText)
	{
	TInt delta = aText.Length() - iTrailingDecorationText.Length();
	if(delta > 0)
		{
		TInt newLength = iLastGeneratedTextValue->Des().MaxLength() + delta;
		iLastGeneratedTextValue = iLastGeneratedTextValue->ReAllocL(newLength);
		}

	iTrailingDecorationText.Set(aText);
	}

EXPORT_C void CAknListBoxLayoutDecorator::SetActive(const TBool aActive)
	{
	iActive = aActive;
	}


EXPORT_C TInt CAknListBoxLayoutDecorator::MdcaCount() const
	{
	return iArray->MdcaCount();
	}

EXPORT_C TPtrC CAknListBoxLayoutDecorator::MdcaPoint(TInt aIndex) const
	{
	if(iActive)
		{
		// we have pre-allocated enough memory for the leading and trailing strings
		// so all we need to do is decide how much room we need and can get for the string
		TInt err1=KErrNone;
		TPtr ptr = iLastGeneratedTextValue->Des();

		TInt decorationLength = iLeadingDecorationText.Length() + 
			iTrailingDecorationText.Length();

		TInt totalSize = iArray->MdcaPoint(aIndex).Length() + decorationLength;
		if(totalSize > ptr.MaxLength())
			{
			TRAP(err1, iLastGeneratedTextValue = iLastGeneratedTextValue->ReAllocL(totalSize))

			// ensure that our TPtr is up to date after the reallocation
			ptr.Set(iLastGeneratedTextValue->Des());
			}

		// we need the leading decoration whatever happens
		ptr.Copy(iLeadingDecorationText);

		if(err1==KErrNone)
			{
			// to get here, we must have enough space for all three strings
			__ASSERT_DEBUG(totalSize <= ptr.MaxLength(), Panic(EAknPanicListBoxLayoutDecoratorMemoryAllocation));
			ptr.Append(iArray->MdcaPoint(aIndex));
			}
		else
			{
			// we couldn't allocate enough for the string plus the decoration
			// so chop the string until it all fits into the existing space - 
			// that way our performance degrades gracefully
			TInt availableSize = ptr.MaxLength() - decorationLength;
			if(availableSize > 0)
				{
				ptr.Append((iArray->MdcaPoint(aIndex)).Left(availableSize)); // copy only availableSize characters from the string
				}
			}

		// we need the trailing decoration whatever happens
		ptr.Append(iTrailingDecorationText);

		return *iLastGeneratedTextValue;
		}
	else
		{
		// leave contents alone
		return iArray->MdcaPoint(aIndex);
		}
	}

CAknListBoxLayoutDecorator::CAknListBoxLayoutDecorator()
	{
	}

void CAknListBoxLayoutDecorator::ConstructL()
	{
	iLastGeneratedTextValue = HBufC::NewL(KSafeSizeOfDescriptor);
	}

EXPORT_C void CAknListBoxLayoutDecorator::CAknListBoxLayoutDecorator_Reserved1()
	{
	}

EXPORT_C void CAknListBoxLayoutDecorator::CAknListBoxLayoutDecorator_Reserved1() const 
	{
	}


// debug only invariant function
EXPORT_C void CAknListBoxLayoutDecorator::__DbgTestInvariant() const          
	{    
	}
