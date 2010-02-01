// Copyright (c) 2004-2009 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef __COECONTROLARRAY_H__
#define __COECONTROLARRAY_H__

#include <e32base.h>	// class CBase

class CCoeControl;

/** Default id for controls that have no associated id. This is equal
to KErrNotFound
@publishedAll 
@released 
*/
const TInt KCoeNoControlId = KErrNotFound;

/** Class that encapsulates a control and the identifier for that control.

Controls in a CCoeControlArray can be associated with an id. This class encapsulates the control and its id.

@publishedAll 
@released */
class TCoeControlWithId
	{
public:
	TCoeControlWithId(TInt aControlId, CCoeControl* aControl = NULL);
public:
	/** The control */
	CCoeControl* iControl;
	/** The id of the control */
	TInt iId;
	};

/** Class that represents an array of controls.

The CCoeControlArray class is used to store the child controls of a container control.
The method CCoeControl::InitComponentArrayL() must be used to create the array and the method
CCoeControlArray& CCoeControl::Components() can be used to get this array.

@publishedAll 
@released */
class CCoeControlArray : public CBase
	{
public:
	/** This class is an iterator for the CCoeControlArray class.
	@publishedAll 
	@released 
	*/
	class TCursor	// robust iterator
		{
	public:	
		template<typename T> T* Control();
		template<typename T> const T* Control() const;
		IMPORT_C TBool Prev();
		IMPORT_C TBool Next();
		IMPORT_C TBool IsValid() const;
		
		IMPORT_C TBool operator==(const TCursor& aCursor) const;
		IMPORT_C TBool operator!=(const TCursor& aCursor) const;
	public:
		TCursor(const CCoeControlArray& aArray, TInt aIndex);
		TInt Index() const;
	private:
		IMPORT_C CCoeControl* Ctrl() const;	
		void UpdateMemento() const;
		void UpdateIndex() const;
	private:
		const CCoeControlArray* iArray;
		mutable TInt iIndex;
		mutable TCoeControlWithId iMemento;
		};
public:
	IMPORT_C static CCoeControlArray* NewL(CCoeControl& aOwner);
	IMPORT_C ~CCoeControlArray();
	IMPORT_C TInt Count() const;
	IMPORT_C void Reset();
	IMPORT_C void ResetAndDestroy();
	IMPORT_C void SortById();
	
	IMPORT_C TBool ControlsOwnedExternally() const;
	IMPORT_C void SetControlsOwnedExternally(TBool aOwnedExternally);
			
	IMPORT_C TBool IsArrayLocked() const;
	IMPORT_C void SetArrayLocked();
	
	template<typename T> T* ControlById(TInt aControlId);
	template<typename T> const T* ControlById(TInt aControlId) const;
		
	IMPORT_C TCursor Begin() const;
	IMPORT_C TCursor End() const;
	IMPORT_C TCursor Find(const CCoeControl* aControl) const;
	IMPORT_C TCursor Find(TInt aControlId) const;

	IMPORT_C TCursor AppendLC(CCoeControl* aControl, TInt aControlId = KCoeNoControlId);
	IMPORT_C TCursor InsertAfterLC(TInt aInsertAfterId, CCoeControl* aControl, TInt aControlId = KCoeNoControlId);
	IMPORT_C TCursor InsertLC(TCursor& aInsertAt, CCoeControl* aControl, TInt aControlId = KCoeNoControlId);
	
	IMPORT_C TInt Remove(const CCoeControl* aControl);
	IMPORT_C CCoeControl* Remove(TCursor aRemoveAt);
	IMPORT_C CCoeControl* RemoveById(TInt aControlId);
public:	
	IMPORT_C TInt Replace(CCoeControl* aOriginalControl, CCoeControl* aNewControl);
	
public:	// internal use only
	IMPORT_C TCoeControlWithId At(TInt aIndex);
	IMPORT_C const TCoeControlWithId At(TInt aIndex) const;
	IMPORT_C TInt Id(const CCoeControl& aControl) const;
	IMPORT_C void Sort(TLinearOrder< TCoeControlWithId > aOrder);
public:
	/** Defines the possible events related to a change to the contents
	of the array. */
	enum TEvent
		{
		/** A control has been added to the array */
		EControlAdded,	
		/** A control has been removed from the array */
		EControlRemoved
		};

private:
	IMPORT_C CCoeControlArray(CCoeControl& aOwner);
	TInt IndexById(TInt aControlId) const;
	IMPORT_C CCoeControl* CtrlById(TInt aControlId) const;

private:
	CCoeControl& iOwner;
	TInt iFlags;
	RArray<TCoeControlWithId> iControls;
	};

/**	Gets the control.
@return The control at the current cursor position. 
*/
template<typename T>
T* CCoeControlArray::TCursor::Control()
	{
	return static_cast<T*>(Ctrl());
	}

/**	Gets the control.
@return The control at the current cursor position. 
*/
template<typename T>
const T* CCoeControlArray::TCursor::Control() const
	{
	return static_cast<T*>(Ctrl());
	}

/** Gets the control with the given id.
@param aControlId The id of the desired control.
@return The control with the given id.
*/
template<typename T>
T* CCoeControlArray::ControlById(TInt aControlId)
	{
	return static_cast<T*>(CtrlById(aControlId));
	}

/** Gets the control with the given id.
@param aControlId The id of the desired control.
@return The control with the given id.
*/
template<typename T>
const T* CCoeControlArray::ControlById(TInt aControlId) const
	{
	return static_cast<T*>(CtrlById(aControlId));
	}

#endif //__COECONTROLARRAY_H__
