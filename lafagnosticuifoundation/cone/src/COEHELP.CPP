// Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
//

#include <coehelp.h>

/** Default constructor. 

Constructs a default TCoeHelpContext object, identifying a null CS Help file 
UID and context. */
EXPORT_C TCoeHelpContext::TCoeHelpContext()
	: iMajor(KNullUid), iContext(KNullDesC)
	{}

/** Constructor specifying a Help file and a topic context descriptor.

@param aMajor The UID of a Help file containing a set of related help topics.
@param aContext The literal descriptor for a particular Help topic. This is 
generated from a context string by the CS Help compiler */
EXPORT_C TCoeHelpContext::TCoeHelpContext(TUid aMajor,const TDesC& aContext)
	: iMajor(aMajor), iContext(aContext)
	{}

/** Tests if the TCoeHelpContext is NULL.

@return ETrue if the object is NULL, EFalse if either the context or Help 
file UID have been set. */
EXPORT_C TBool TCoeHelpContext::IsNull() const
	{
	return (iMajor==KNullUid && iContext.Length()==0);
	}

/** Tests for equality.

@param aContext The Help context to compare to this object.
@return ETrue if aContext has the same data member values as this object, otherwise 
EFalse. */
EXPORT_C TBool TCoeHelpContext::operator==(const TCoeHelpContext& aContext) const
	{
	return (iMajor==aContext.iMajor && iContext==aContext.iContext);
	}

/** Tests for inequality.

@param aContext The Help context to compare to this object.
@return ETrue if aContext has any different data member values as this object, 
otherwise EFalse. */
EXPORT_C TBool TCoeHelpContext::operator!=(const TCoeHelpContext& aContext) const
	{
	return (iMajor!=aContext.iMajor || iContext!=aContext.iContext);
	}
