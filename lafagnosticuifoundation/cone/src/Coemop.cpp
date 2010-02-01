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

#include <coemop.h>

/** Safety check to avoid loops in the Mop chain.
*/
MObjectProvider* MObjectProvider::FindParent(MObjectProvider* aMopToFind)
	{
	MObjectProvider* mop = this;
	while (mop && mop!= aMopToFind)
		{
		mop = mop->MopNext();
		}
	return mop;
	}

/** Gets the parent object provider.

This is called by the private function MopGetById() when a call to 
MopGetObject() returns NULL.

The default implementation returns NULL. Note that care must be taken 
to avoid infinite loops. For example, returning a pointer, either 
directly or indirectly, to this same object provider.

@return	A pointer to the parent object provider, or NULL if there is none.
@publishedAll 
@released */
EXPORT_C MObjectProvider* MObjectProvider::MopNext()
	{
	return NULL;
	}


/** Gets an object of a type identified by the specified TTypeUid object.

Although private, the implementation tries to find a suitable object through 
a call to MopSupplyObject(). If this returns NULL, it calls MopNext() to find 
a parent object provider, and then recursively calls MopGetById(), until an object 
is found, or no further parents can be found.

Note that we should preserve Binary Compatibility for this function because it 
is called by the publishedAll inline function MObjectProvider::MopGetObject().

@param aId A unique identifier which identifies the type of object required.
@return The owned object of the given type ID. If no owned object of the given 
type ID exists, NULL is returned.
@internalComponent */
EXPORT_C TAny* MObjectProvider::MopGetById(TTypeUid aId)
	{
	TAny* obj = MopSupplyObject(aId).Pointer();

	if (obj)
		return obj;
	
	MObjectProvider* next = MopNext();
	if (next)
		return next->MopGetById(aId);

	return NULL;
	}
	
	
/** Gets an object of a type identified by the specified TTypeUid object. It does not
recurse through the object provider chain to find the object required. If this object
cannot provide it then it returns NULL.

Although private, the implementation tries to find a suitable object through 
a call to MopSupplyObject(), and if this returns NULL, this function returns NULL.

Note that we should preserve Binary Compatibility for this function because it 
is called by the publishedAll inline function MObjectProvider::MopGetObjectNoChaining().

@param aId A unique identifier which identifies the type of object required.
@return The owned object of the given type ID. If no owned object of the given 
type ID exists, NULL is returned.
@internalComponent */
EXPORT_C TAny* MObjectProvider::MopGetByIdNoChaining(TTypeUid aId)
	{
	TAny* obj = MopSupplyObject(aId).Pointer();
	return obj;
	}


EXPORT_C MObjectProvider::MObjectProvider()
	{
	}

EXPORT_C void MObjectProvider::MObjectProvider_Reserved1()
	{
	}
	
EXPORT_C void MObjectProvider::MObjectProvider_Reserved2()
	{
	}
	
