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

#include <coecontrolarray.h>	// class CCoeControlArray
#include <coecntrl.h>			// class CCoeControl
#include "coepanic.h"			// Cone panic codes
#include <e32std.h>				// class EUser

/**
Flags used internally.
*/
enum TFlags
	{
	/** Controls are owned externally. This means that the destructor
	shouldn't delete the individual controls. 
	*/
	EControlsOwnedExternally = 0x01,
	/** When the array is locked any attempt to add or remove elements will result in KErrLocked.
	*/
	EArrayLocked = 0x02
	};

LOCAL_C void CleanupComponentControl(TAny* aCleanupItem)	
	{
	CCoeControl* control = reinterpret_cast<CCoeControl*>(aCleanupItem);
	if (control)
		{
		control->RemoveFromParent();
		delete control;
		}
	}

LOCAL_C void CleanupExternallyOwnedComponentControl(TAny* aCleanupItem)	
	{
	CCoeControl* control = reinterpret_cast<CCoeControl*>(aCleanupItem);
	if (control)
		{
		control->RemoveFromParent();
		}
	}

//
// class CCoeControlArray::TCursor
//

/** Updates the cursor so that it points to the previous element in the array.
If the current element is the first one then this function does nothing and returns EFalse.

@return EFalse if the current element was the first one in the array, ETrue if it wasn't and the function
actually did something.
*/
EXPORT_C TBool CCoeControlArray::TCursor::Prev()
	{
	if(iIndex <= 0)
		return EFalse;
	
	iIndex--;
	UpdateMemento();
	return ETrue;
	}
	
/** Updates the cursor so that it points to the next element in the array.
If the current element is the last one then this function returns EFalse.

@return EFalse if the current element was the last one in the array, ETrue otherwise 
*/
EXPORT_C TBool CCoeControlArray::TCursor::Next()
	{
	const TInt count = iArray->Count();
	if(iIndex >= count-1) //If last element or beyond move to just off the end of the array
		{
		iIndex = count;
		iMemento = TCoeControlWithId(KCoeNoControlId);
		return EFalse;
		}	
	iIndex++;
	UpdateMemento();
	return ETrue;
	}

/** Checks if the cursor is valid. Use this to replace the comparison with NULL that you would
do with pointers. This function is typically used on the cursors returned by the find operations.
@return ETrue if the cursor points to a control, EFalse otherwise
*/
EXPORT_C TBool CCoeControlArray::TCursor::IsValid() const
	{
	UpdateIndex();
	return (iIndex != KErrNotFound);
	}

/** Checks if the cursors are equal. Cursors are equal if they point to the same control in the
same array else they are different.
@param aCursor The other cursor.
@return ETrue if the cursors point to the same position in the same array, EFalse 
otherwise.
*/
EXPORT_C TBool CCoeControlArray::TCursor::operator ==(const TCursor& aCursor) const
	{
	UpdateIndex();
	aCursor.UpdateIndex();
	
	ASSERT(IsValid());
	ASSERT(aCursor.IsValid());
	
	return (iIndex == aCursor.iIndex && iArray == aCursor.iArray);
	}

/** Checks if the cursors are different. Cursors are equal if they point to the same control in the
same array else they are different.
@param aCursor The other cursor.
@return EFalse if the cursors point to the same position in the same array, EFalse 
otherwise.
*/
EXPORT_C TBool CCoeControlArray::TCursor::operator !=(const TCursor& aCursor) const
	{
	UpdateIndex();	
	aCursor.UpdateIndex();
	
	ASSERT(IsValid());
	ASSERT(aCursor.IsValid());
	
	return !(iIndex == aCursor.iIndex && iArray == aCursor.iArray);
	}

/** Constructor.
@param aArray The array
@param aIndex The index into the array
*/
CCoeControlArray::TCursor::TCursor(const CCoeControlArray& aArray, TInt aIndex) : 
	iArray(&aArray), iIndex(aIndex), iMemento(KCoeNoControlId)
	{
	if(aIndex >= 0 && aIndex < aArray.Count())
		iMemento = TCoeControlWithId(aArray.At(aIndex));
	}

/** Gets the index of the cursor.
@return The index i.e. the position in the array
*/
TInt CCoeControlArray::TCursor::Index() const
	{
	UpdateIndex();
	return iIndex;
	}

/** Gets the control of the cursor.
@return The control.
*/
EXPORT_C CCoeControl* CCoeControlArray::TCursor::Ctrl() const
	{
	UpdateIndex();
	if(iIndex == KErrNotFound || iIndex >= iArray->Count())
		return NULL;
	else
		return iArray->At(iIndex).iControl;
	}

/** This function is used by any operation that requires an update of the memento.
*/
void CCoeControlArray::TCursor::UpdateMemento() const
	{
	if(iIndex >= 0 && iIndex < iArray->Count())
		iMemento = iArray->At(iIndex);
	else
		{
		iIndex = KErrNotFound;
		iMemento = TCoeControlWithId(KErrNotFound);
		}
	}

/** This function is used by any operation that requires an update of the index.
*/
void CCoeControlArray::TCursor::UpdateIndex() const
	{
	if(!iMemento.iControl)	// If we don't know what control this cursor should point to
		{
		// This is either an invalid cursor (if iIndex == -1) 
		// or one that points to the element just beyond the end of the array (iIndex == iArray->Count())
		
		// If the iIndex is pointing anywhere but at CCoeControlArray::End() it has gone bad
		if(iIndex != KErrNotFound && iIndex != iArray->Count())
			{
			iIndex = KErrNotFound;
			iMemento = TCoeControlWithId(KErrNotFound);
			}
	
		return;
		}
	
	if(iIndex >= 0 && iIndex < iArray->Count())	// If the index is within the valid range
		{
		// Check that the control at iIndex is the same as the memento
			
		const TCoeControlWithId controlWithId = iArray->At(iIndex);
		if(iMemento.iControl != controlWithId.iControl)	// If not, update the index to match the memento
			{
			const TInt newIndex = iArray->Find(iMemento.iControl).iIndex;
			if(newIndex != KErrNotFound)
				iIndex = newIndex;
			else
				{
				// If the memento control is no longer in the array, try update the memento instead
				UpdateMemento();
				}
			}
		}
	else
		{
		const TInt newIndex = iArray->Find(iMemento.iControl).iIndex;
		if(newIndex != KErrNotFound)
			iIndex = newIndex;
		else
			iMemento = TCoeControlWithId(KErrNotFound);	
		}
	}


//
// class CCoeControlArray
//

/** Creates a new CCoeControlArray.
@param aOwner The control that owns the new array
@return A new CCoeControlArray instance
*/
EXPORT_C CCoeControlArray* CCoeControlArray::NewL(CCoeControl& aOwner)
	{
	CCoeControlArray* self = new (ELeave) CCoeControlArray(aOwner);
	return self;
	}

/** Constructor.
*/
TCoeControlWithId::TCoeControlWithId(TInt aControlId, CCoeControl* aControl) : iControl(aControl), iId(aControlId)
	{
	}
	
/** The destructor will delete the controls in the array only if the EControlsOwnedExternally flag is not set.
*/
EXPORT_C CCoeControlArray::~CCoeControlArray()
	{
	if(!ControlsOwnedExternally())
		ResetAndDestroy();
	
	iControls.Close();
 	}

const TInt KControlArrayGranularity = 1;

/** Constructor 
@param aOwner The control that owns the new array
*/
EXPORT_C CCoeControlArray::CCoeControlArray(CCoeControl& aOwner)
 : iOwner(aOwner), iControls(KControlArrayGranularity, _FOFF(TCoeControlWithId, iId))
	{
	}

/** Gets the number of elements in the array.
@return The number of elements in the array
*/
EXPORT_C TInt CCoeControlArray::Count() const
	{
	return iControls.Count();
	}

/** Removes all the controls from the array but doesn't delete them.
*/
EXPORT_C void CCoeControlArray::Reset()
	{
	iControls.Reset();
	}

/** Removes all the controls from the array and deletes them.
*/
EXPORT_C void CCoeControlArray::ResetAndDestroy()
	{
	for(TInt i = iControls.Count()-1; i >= 0; i--)	// remove from the end, so we don't need to move any items
		{
		delete iControls[i].iControl;
		// The array must be shrunk immediately to avoid Kern-Exec 3 when calling CCoeControl::Components() 
		// or CCoeControl::ComponentControl(TInt aIndex) inside MCoeFocusObserver::HandleDestructionOfFocusedItem
 		iControls.Remove(i);
		}

	iControls.Reset();
	}

/** Sorts the controls using their index as the key.
*/
EXPORT_C void CCoeControlArray::SortById()
	{
	iControls.SortSigned();
	}

/**This function provides a pluggable implementation to sort the array of controls.
@param aOrder The user defined static method which implements the algorithm for sorting.
*/
EXPORT_C void CCoeControlArray::Sort(TLinearOrder< TCoeControlWithId > aOrder)
	{
	iControls.Sort(aOrder);
	}
/** This function checks if the controls are owned by the array or not. If the controls are owned by the array they
will be deleted when the array is destroyed else they will not.

@return ETrue if the array does NOT own the controls, EFalse if the array owns the controls.
*/
EXPORT_C TBool CCoeControlArray::ControlsOwnedExternally() const
	{
	return (iFlags&EControlsOwnedExternally);
	}

/** Is used to set whether the array owns the controls or not. If the controls are owned by the array they
will be deleted when the array is destroyed else they will not.

@param aOwnedExternally ETrue if the controls are owned externally, EFalse if
they are owned by the array.
*/
EXPORT_C void CCoeControlArray::SetControlsOwnedExternally(TBool aOwnedExternally)
	{
	if(aOwnedExternally)
		{
		iFlags |= EControlsOwnedExternally;
		}
	else 
		{
		iFlags &= ~EControlsOwnedExternally;
		}
	}

/** Checks whether the array is locked or not. If an array is locked any attempt to add or remove controls
will fail with KErrLocked.

@return ETrue if the array is locked, EFalse otherwise
*/
EXPORT_C TBool CCoeControlArray::IsArrayLocked() const
	{
	return (iFlags&EArrayLocked);
	}

/** Locks the array. If an array is locked any attempt to add or remove controls
will fail with KErrLocked.
*/
EXPORT_C void CCoeControlArray::SetArrayLocked()
	{
	iFlags |= EArrayLocked;
	}
	
/** Gets a cursor that points to the first element of the array. Note that if the array is empty
this is actually equivalent to a call to End().

@return A cursor that points to the first control in the array.
*/
EXPORT_C CCoeControlArray::TCursor CCoeControlArray::Begin() const
	{
	return TCursor(*this, 0);
	}

/** Gets a cursor to the position right after the last element in the array. To get the last element
use Prev(). This cursor is useful as argument to the insertion function to add the new control at the end of the array.

@return A cursor that points right after the last element
*/
EXPORT_C CCoeControlArray::TCursor CCoeControlArray::End() const
	{
	return TCursor(*this, Count());
	}

/** Gets a cursor to the control, if the control is found in the array. Use
the TCursor::IsValid function to check that the search found something or not.

@param aControl The control to find.
@return A cursor to the control. This may be an invalid cursor if we didn't 
find the requested control. Use TCursor::IsValid() to check if the cursor is valid.
*/
EXPORT_C CCoeControlArray::TCursor CCoeControlArray::Find(const CCoeControl* aControl) const
	{
	const TInt numControls = iControls.Count();
	for(TInt index = 0; index < numControls; index++)
		{
		if(iControls[index].iControl == aControl)
			return TCursor(*this, index);
		}
	
	return TCursor(*this, KCoeNoControlId);
	}
	
/** Gets a cursor to the control, if the control with the given id is found in the array.
Use the TCusror::IsValid function to check that the search found something or not.

@param aControlId The id of the control to find.
@return A cursor to the control. This may be an invalid cursor if we didn't 
find the requested control. Use TCursor::IsValid() to check if the cursor is valid.
*/
EXPORT_C CCoeControlArray::TCursor CCoeControlArray::Find(TInt aControlId) const
	{
	const TInt index = iControls.Find(TCoeControlWithId(aControlId));
	return TCursor(*this, index);
	}

/** Appends a control at the end of the array.

@param aControl The control to add
@param aControlId The id for the new control
@return A cursor to the added control
*/
EXPORT_C CCoeControlArray::TCursor CCoeControlArray::AppendLC(CCoeControl* aControl, TInt aControlId)
	{
	TCursor cursor = End();
	InsertLC(cursor, aControl, aControlId);
	return cursor;
	}
	
/** Inserts a control after the control with the given id.

Each array has an owner (an instance of the CCoeControl class) which is the container of all the child controls. 
Each control has a parent and for the child controls this parent must be the container. This function will automatically 
update the parent of aControl.

The function will also result in the CCoeControl::HandleControlArrayEventL method being called
on the owner of the array. The event being generated is EControlAdded.

@param aInsertAfterId The id of the control after which we want to insert the new control. If a control with this 
id can't be found in the array the function will leave with KErrNotFound.
@param aControl The new control we want to add.
@param aControlId The id of the new control.
@return A cursor to the added control
@leave KErrLocked if the array has been locked using the CCoeControlArray::SetArrayLocked() function.
@leave KErrNotFound if the array doesn't contain a control identified by aInsertAfterId. 
*/
EXPORT_C CCoeControlArray::TCursor CCoeControlArray::InsertAfterLC(TInt aInsertAfterId, CCoeControl* aControl, TInt aControlId)
	{
	const TInt index = IndexById(aInsertAfterId);
	if(index == KErrNotFound)
		{
		if(!(iFlags & EControlsOwnedExternally))
			delete aControl;
		User::Leave(KErrNotFound);
		}
	TCursor cursor(*this, index);
	cursor.Next();	// insert before the next item
	return(InsertLC(cursor, aControl, aControlId));
	}

/** Inserts a control at the given position. 

Each array has an owner (an instance of the CCoeControl class) which is the container of all the child controls. 
Each control has a parent and for the child controls this parent must be the container. This function will automatically 
update the parent of aControl.

The function will also result in the CCoeControl::HandleControlArrayEventL method being called
on the owner of the array. The event being generated is EControlAdded.

@param aInsertAt The position at which we want to insert the new control.
@param aControl The new control we want to add.
@param aControlId The id of the new control.
@return A cursor to the added control
@leave KErrLocked if the array has been locked using the CCoeControlArray::SetArrayLocked() function.
*/
EXPORT_C CCoeControlArray::TCursor CCoeControlArray::InsertLC(TCursor& aInsertAt, CCoeControl* aControl, TInt aControlId)
	{
 	__ASSERT_DEBUG(this, Panic(ECoePanicNonExistentArray));	
	
	const TBool externallyOwned = iFlags & EControlsOwnedExternally;
	
	// Set parent before pushing the CleanupComponenetControl, so that we can 
	// look for external ownership on parent if something leaves
	const TInt err = aControl->SetParent(&iOwner);
	if(err != KErrNone)
		{
		if(!externallyOwned)
			delete aControl;
		User::Leave(err);
		}
	
	CleanupStack::PushL(TCleanupItem((externallyOwned ? 
										CleanupExternallyOwnedComponentControl : 
										CleanupComponentControl),
									 aControl));

	if(IsArrayLocked())
		User::Leave(KErrLocked);

#ifdef _DEBUG	
	__ASSERT_DEBUG(aControlId == KCoeNoControlId || 
			iControls.Find(TCoeControlWithId(aControlId)) == KErrNotFound, Panic(ECoePanicDuplicateControlId));
#endif	

	// To preserve the insertion order of controls without assigned ID
	if(aControlId == KCoeNoControlId)	// If the control has not been given an ID...
		{
		// ...loop through all controls and find the largest negative ID (i.e. the one closest to zero)
		TInt autoId = KMinTInt32;
		const TInt count = iControls.Count();
		for(TInt i = 0; i < count; i++)
			{
			const TInt controlId = iControls[i].iId;
			if(controlId < 0 && autoId <= controlId)
				{
				autoId = controlId+1;
				}
			}
			
		aControlId = autoId;	// Give the new control the next larger negative ID
		}
		
	iControls.InsertL(TCoeControlWithId(aControlId, aControl), aInsertAt.Index());
	iOwner.HandleControlArrayEventL(EControlAdded, this, aControl, aControlId);	
	
	const TCursor newItemCursor = aInsertAt; 
	aInsertAt.Next();	// Move the cursor forward to presserve its position in the array
	
	return newItemCursor;
	}
	
/** Removes a control but does NOT delete the control itself. The ownership of the control is 
transferred to the caller.

The function will also result in the CCoeControl::HandleControlArrayEventL method being called
on the owner of the array. The event being generated is EControlRemoved.

@param aControl The control to remove
@return KErrNone if the control was removed successfully, KErrNotFound if the control could not be found.
*/
EXPORT_C TInt CCoeControlArray::Remove(const CCoeControl* aControl)
	{
	for(TInt i = 0; i < iControls.Count(); i++)
		{
		const TCoeControlWithId controlWithId = iControls[i];
		if(controlWithId.iControl == aControl)
			{
			iControls.Remove(i);
			// EControlRemoved event must never cause leave
			TRAP_IGNORE(iOwner.HandleControlArrayEventL(EControlRemoved, this, controlWithId.iControl, controlWithId.iId));	
			return KErrNone;	
			}
		}
		
	return KErrNotFound;
	}

/** Removes a control but does NOT delete the control itself. The ownership of the control is 
transferred to the caller.

The function will also result in the CCoeControl::HandleControlArrayEventL method being called
on the owner of the array. The event being generated is EControlRemoved.

@param aRemoveAt The position of the control to remove
@return A pointer to the control that has been removed. This can be used by the caller to delete the control.
*/
EXPORT_C CCoeControl* CCoeControlArray::Remove(TCursor aRemoveAt)
	{
	const TCoeControlWithId controlWithId = iControls[aRemoveAt.Index()];
	iControls.Remove(aRemoveAt.Index());
	// EControlRemoved event must never cause leave
	TRAP_IGNORE(iOwner.HandleControlArrayEventL(EControlRemoved, this, controlWithId.iControl, controlWithId.iId));	

	return controlWithId.iControl;	
	}

/** Removes a control but does NOT delete the control itself. The ownership of the control is 
transferred to the caller.

The function will also result in the CCoeControl::HandleControlArrayEventL method being called
on the owner of the array. The event being generated is EControlRemoved.

@param aControlId The id of the control to remove
@return A pointer to the control that has been removed. This can be used by the caller to delete the control. The function
returns NULL if no control with the given aControlId has been found.
*/	
EXPORT_C CCoeControl* CCoeControlArray::RemoveById(TInt aControlId)
	{
	const TInt index = IndexById(aControlId);
	if(index != KErrNotFound)
		{
		const TCoeControlWithId controlWithId = iControls[index];
		iControls.Remove(index);
		// EControlRemoved event must never cause leave
		TRAP_IGNORE(iOwner.HandleControlArrayEventL(EControlRemoved, this, controlWithId.iControl, controlWithId.iId));	
		return controlWithId.iControl;
		}
		
	return NULL;	
	}
	
/** Gets the element at the given index.
@param aIndex The index of the control
@return The control and its id
*/
EXPORT_C TCoeControlWithId CCoeControlArray::At(TInt aIndex)
	{
	return iControls[aIndex];	
	}

/** Gets the element at the given index.
@param aIndex The index of the control
@return The control and its id
*/
EXPORT_C const TCoeControlWithId CCoeControlArray::At(TInt aIndex) const
	{
	return iControls[aIndex];	
	}
	
/** Gets the id of the control.
@param aControl The control
@return The id of the control or KErrNotFound if the control can't be found.
*/
EXPORT_C TInt CCoeControlArray::Id(const CCoeControl& aControl) const
	{
	for(TInt i = 0; i < iControls.Count(); i++)
		{
		if(iControls[i].iControl == &aControl)
			return iControls[i].iId;
		}
		
	return KErrNotFound;
	}

/** Replaces a control in the array with another control.

@param aOriginalControl The control that must be replaced
@param aNewControl The new control
@return A standard error code
*/
EXPORT_C TInt CCoeControlArray::Replace(CCoeControl* aOriginalControl, CCoeControl* aNewControl)
	{
 	__ASSERT_DEBUG(this, Panic(ECoePanicNonExistentArray));		
	for(TInt i = 0; i < iControls.Count(); i++)
		{
		if(iControls[i].iControl == aOriginalControl)
			{
			iControls[i].iControl = aNewControl;
			return KErrNone;
			}
		}
		
	return KErrNotFound;
	}

/** Gets the control with the given id or NULL if there is no control with the given id.
@param aControlId The id of the control
@return The control with the given id or null.
*/
EXPORT_C CCoeControl* CCoeControlArray::CtrlById(TInt aControlId) const
	{
	const TInt index = IndexById(aControlId);
	return (index != KErrNotFound ? iControls[index].iControl : NULL);
	}

/** Gets the index of the control with the given id or KErrNotFound if there is no control that has
that id.
@param aControlId The id of the control
@return The index of the control with the given id or KErrNotFound.
*/
TInt CCoeControlArray::IndexById(TInt aControlId) const
	{
	if(aControlId == KErrNotFound)
		return KErrNotFound;
	
	const TInt index = iControls.Find(TCoeControlWithId(aControlId));
	return index;
	}
