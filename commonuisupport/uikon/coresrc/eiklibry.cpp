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

#include <eiklibry.h>
#include <ecom/ecom.h>

EXPORT_C void CEikLibrary::PostAppUiInitializeL()
	{}

EXPORT_C CEikLibrary2* CEikLibrary2::LoadLibraryL(TUid aImplementationUid) 
/** Instantiates an interface implementation to satisfy the specified ECom plugin interface.

@publishedAll
@released
@param aImplementationUid A UID specifying the required ECom plugin interface implementation.
@return A pointer to the instantiated ECom plugin interface implementation.*/
	{
	TAny* ptr= REComSession::CreateImplementationL(aImplementationUid, _FOFF(CEikLibrary2, iDtrkey));
	return REINTERPRET_CAST(CEikLibrary2*, ptr);
	}

EXPORT_C CEikLibrary2::~CEikLibrary2()
/** Destructor. 

Signals the destruction of an interface implementation to ECom. */
	{
	REComSession::DestroyedImplementation(iDtrkey);
	}
