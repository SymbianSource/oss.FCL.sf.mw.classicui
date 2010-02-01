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

#ifndef __COEMOP_H__
#define __COEMOP_H__

#include <e32std.h>

/** Declares an object type, ETypeId, for a class, in order to allow the object 
provider mechanism to locate and provide objects from the class.

@publishedAll
@released
@see MObjectProvider */
#define DECLARE_TYPE_ID(id) enum { ETypeId = id };

//
// Used to wrap object type IDs in a standardised manner. Object type IDs must be asserted 
// in an ETypeId member data property by any types of object which 
// are capable of being retrieved by the MObjectProvider interface
//
class TTypeUid : public TUid
/** Part of the object provider mechanism, this class encapsulates the Uid that 
identifies the type of object that an object provider is to get.

The class is also used to encapsulate a pointer to the object that the object 
provider has found.

An object that is intended to be capable of being retrieved by the object 
provider mechanism must include enum {ETypeId = 0xabcdefgh}; in its class 
definition, where 0xabcdefgh is the Uid value. The macro DECLARE_TYPE_ID can 
be used to do this.

An instance of this class is passed to the MObjectProvider::MopSupplyObject() 
function implemented by an object provider. A TTypeUid::Ptr is also returned 
by this function.

@publishedAll
@released
@see MObjectProvider */
	{
public:
	class Ptr
	/** Encapsulates a pointer to an object fetched by an object provider.

	The class has no public constructor. TTypeUid::MakePtr() or TTypeUid::Null() 
	must be used to construct instances of this class. */
		{
		friend class TTypeUid;
	private:
		explicit inline Ptr(TAny* aPtr)
			: iPtr(aPtr)
			{}
	public:
		inline TAny* Pointer() const
		/** Retrieves the pointer to an object which is encapsulated by the Ptr.
	
		@return A pointer to an object. */
			{return iPtr;}
	private:
		TAny* iPtr;
		};
public:
	inline TTypeUid(TInt aUid)
	/** Constructor that takes a Uid value.
	
	@param aUid The Uid value that defines the type of object that an object provider 
	is to get. */
		{ iUid = aUid; }
	inline static Ptr Null()
	/** Constructs a Ptr which encapsulates a NULL pointer.
	
	@return The constructed Ptr object */
		{ return Ptr(NULL); }
	template <class T> inline Ptr MakePtr(T* aT) const
	/** Constructs a Ptr which encapsulates the specified object pointer.
	
	@param aT A pointer to the object which is to be encapsulated.
	@return The constructed Ptr object */
		{ __ASSERT_DEBUG(iUid == T::ETypeId,User::Invariant()); return Ptr(aT); }
	};


class MObjectProvider
/** An interface that allows an object to be part of a network of object providers.

The object provider mechanism can be used to find and access objects of a 
given type, where the type is defined by a TTypeUid object. Object providers 
may be arranged in a hierarchy, i.e. an object provider may have a parent-child 
relationship with another object provider.

An object provider must provide an implementation for the MopSupplyObject() 
function and can choose to provide an implementation for the MopNext() function. 
Typically, it will also have functionality to define who its parent is.

CCoeControl is an example of a class that implements this interface. Top level 
controls must have the view or app UI set as their object provider. This is 
done by calling CCoeControl::SetMopParent() on the view or the app UI. The 
view or app UI does this by calling the top level control's CCoeControl::SetMopParent() 
function. 

@publishedAll 
@released */
	{
public:
	template<class T>
	T* MopGetObject(T*& aPtr) 
	/** Gets an object of the type defined by the template parameter.
	
	The object may be supplied directly by this object provider, or by other object 
	providers higher up the hierarchy.
	
	@param aPtr A reference to a pointer to an object of a type that is to be 
	retrieved.
	@return A pointer to an object of the type required, or NULL if none can be 
	found. */
		{ return (aPtr=(T*)MopGetById(T::ETypeId)); }
		
	
	template<class T>	
	T*  MopGetObjectNoChaining(T*& aPtr)
	/** Gets an object of the type defined by the template parameter.
	
	The object will be supplied directly by this object provider, or NULL 
	will be returned, this function does not recurse through the object chain.
		
	@param aPtr A reference to a pointer to an object of a type that is to be 
	retrieved.
	@return A pointer to an object of the type required, or NULL if none can be 
	found. */
		{ return (aPtr=(T*)MopGetByIdNoChaining(T::ETypeId)); }
	
	/**
	@publishedAll 
	@released */
	MObjectProvider* FindParent(MObjectProvider* aMopToFind);
	
private: // must be overridden
	/** Gets an object whose type is encapsulated by the specified TTypeUid object.

	@param aId Encapsulates the Uid that identifies the type of object required.
	@return Encapsulates the pointer to the object provided. 
	Note that the encapsulated pointer may be NULL.

	@publishedAll 
	@released */
	virtual TTypeUid::Ptr MopSupplyObject(TTypeUid aId) = 0;

protected:
	IMPORT_C MObjectProvider();

private: // may be overridden to continue chain of responsibility
	/**
	@publishedAll 
	@released */
	IMPORT_C virtual MObjectProvider* MopNext();
	IMPORT_C virtual void MObjectProvider_Reserved1();
	IMPORT_C virtual void MObjectProvider_Reserved2();

private: 
	IMPORT_C TAny* MopGetById(TTypeUid aId);
	IMPORT_C TAny* MopGetByIdNoChaining(TTypeUid aId);
	
private:
	TInt iMObjectProvider_Reserved1;
	};

#endif	// __COEMOP_H__
