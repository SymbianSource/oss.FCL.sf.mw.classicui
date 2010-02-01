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
// CoeLayoutManager.H
// 
//

#ifndef __COELAYOUTMANAGER_H__
#define __COELAYOUTMANAGER_H__

#include <e32base.h>

class CCoeControl;


/**
Base class for layout managers.

A layout manager can be attached to one, or many (depending on the concrete layout
manager), compound controls. The layout manager handles the layout of the components
of the attached compound controls, and calculates the attached compound controls' 
minimum size. 

@publishedAll
@released
*/
class MCoeLayoutManager
	{
protected:
	IMPORT_C MCoeLayoutManager();
	
public:

	/** Determines if it is possible to attach another control to the layout manager.
	@return <code>ETrue</code> if possible, otherwise <code>EFalse</code>
	*/
	virtual TBool CanAttach() const = 0;

	/** Attaches <code>aCompoundControl</code> to the layout manager.
	Is normally not called manually since <code>CCoeControl::SetLayoutManagerL()</code>
	calls this function.
	Once a compound control is attached to a layout manager, the layout manager owns itself.
	@see Detach()
	@see CCoeControl::SetLayoutManagerL()
	@param aCompoundControl The compound control.
	*/
	virtual void AttachL(CCoeControl& aCompoundControl) = 0;

	/** Detaches <code>aCompoundControl</code> from the layout manager.
	Is normally not called manually since <code>CCoeControl::SetLayoutManagerL()</code>
	calls this function when you switch layout managers on a control. It is also called
	from <code>CCoeControl::~CCoeControl</code>
	When the last attached compound control detaches, the layout manager deletes itself.
	@see CCoeControl::SetLayoutManagerL()
	@param aCompoundControl The compound control.
	*/
	virtual void Detach(CCoeControl& aCompoundControl) = 0;

	/** Calculates the minimum size of <code>aCompoundControl</code>
	Is normally not called manually since <code>CCoeControl::MinimumSize()</code>
	calls this function in the default implementation on controls with layout managers.

	To calculate the minimum size is almost as time consuming as performing an actual layout
	and should be used with caution. The minimum size depends on <code>aCompoundControl</code>'s
	maximum width.
	@see CCoeControl::MaximumWidth()
	@param aCompoundControl The compound control
	@return The minimum size
	*/
	virtual TSize CalcMinimumSize(const CCoeControl& aCompoundControl) const = 0;

	/** Performs the layout of the attached controls
	Is normally not called manually since <code>CCoeControl::SizeChanged()</code>
	calls this function in the default implementation on controls with layout managers.

	The layout is generally performed by calling the component controls'
	<code>SetMaximumWidth()</code>, followed by <code>MinimumSize()</code>, and then the
	layout manager tries to place the component controls according to their minimum
	sizes and the settings.

	@see CCoeControl::SetMaximumWidth()
	@see CCoeControl::MinimumSize()
	*/
	virtual void PerformLayout() = 0;

	/** Gets the offset to the first text baseline relative to the top of the control.
	
	@param aCompoundControl The control
	@param aSize The size of the control
	@return The baseline
	@see CCoeControl::TextBaselineOffset()
	*/
	virtual TInt CalcTextBaselineOffset(const CCoeControl& aCompoundControl, const TSize& aSize) const = 0;

	/** Sets the spacing between text baselines.

	@param aBaselineSpacing The new value for the baseline
	@see CCoeControl::SetTextBaseLineSpacing()
	*/
	virtual void SetTextBaselineSpacing(TInt aBaselineSpacing) = 0;
	
	/** Returns the baseline spacing.
	@return The baseline value.
	*/
	virtual TInt TextBaselineSpacing() const = 0;

	/** Handles when a component control is added to an attached compound control
	Is normally not called manually since <code>CCoeControlArray::InsertLC()</code>
	calls this function for controls with layout managers.
	Is used by layout managers to prepare to layout one more component control.
	@see CCoeControlArray::InsertLC()
	@param aCompoundControl The compound control.
	@param aAddedControl The added control
	*/
	virtual void HandleAddedControlL(const CCoeControl& aCompoundControl, const CCoeControl& aAddedControl) = 0;
	
	/** Handles when a component control is removed from an attached compound control
	Is normally not called manually since <code>CCoeControlArray::Remove()</code>
	calls this function for controls with layout managers.
	Is used by layout managers to remove all settings and similar that are specific for
	<code>aRemovedControl</code>.
	@see CCoeControlArray::Remove()
	@param aCompoundControl The compound control.
	@param aRemovedControl The removed control
	*/
	virtual void HandleRemovedControl(const CCoeControl& aCompoundControl, const CCoeControl& aRemovedControl) = 0;

	/** Handles when a component control is replaced by another component control
	in an attached compound control
	
	Is not called by <code>CCoeControl</code>.
	Is used by layout managers to move settings and similar that are specified for 
	<code>aOldControl</code> to <code>aNewControl</code>
	If this function is called, neither <code>HandleAddedControlL</code> nor 
	<code>HandleRemovedControl</code> is allowed to be called.
	@param aOldControl The old component control
	@param aNewControl The new component control
	@return <code>KErrNone</code> if no error. <code>KErrNotFound</code> if the
	layout manager cannot find <code>aOldControl</code>
	*/
	virtual TInt HandleControlReplaced(const CCoeControl& aOldControl, const CCoeControl& aNewControl) = 0;

	
private:
	IMPORT_C virtual void Reserved_MCoeLayoutManager_1();
	IMPORT_C virtual void Reserved_MCoeLayoutManager_2();
	IMPORT_C virtual void Reserved_MCoeLayoutManager_3();
	IMPORT_C virtual void Reserved_MCoeLayoutManager_4();
	IMPORT_C virtual void Reserved_MCoeLayoutManager_5();
	IMPORT_C virtual void Reserved_MCoeLayoutManager_6();
	IMPORT_C virtual void Reserved_MCoeLayoutManager_7();
	IMPORT_C virtual void Reserved_MCoeLayoutManager_8();
	IMPORT_C virtual void Reserved_MCoeLayoutManager_9();
	IMPORT_C virtual void Reserved_MCoeLayoutManager_10();
	IMPORT_C virtual void Reserved_MCoeLayoutManager_11();
private:
	TInt iMCoeLayoutManager_Reserved1;
	};


#endif	// __COELAYOUTMANAGER_H__
