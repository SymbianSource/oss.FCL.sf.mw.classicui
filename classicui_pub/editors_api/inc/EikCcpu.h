/*
* Copyright (c) 2002-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Provides support for cut, copy, paste and
*                undo functionality in editors.
*
*/


#ifndef EIKCCPU_H
#define EIKCCPU_H

#include <coecntrl.h>
#include <eikdef.h>
#include <eikmobs.h>
#include <babitflags.h>
#include <AknControl.h>

class CEikButtonGroupContainer;
class CEikMenuBar;


/**
 * Interface for cut, copy, paste and undo functionality.
 */
class MEikCcpuEditor
	{
public:
    /**
     * Derived classes must provide the implementation for
     * following:
     *
     * Tests whether the editor is focused.
     * 
     * @return If editor is focused, @c ETrue is returned.
     */
	virtual TBool CcpuIsFocused() const = 0;
	
    /**
     * Derived classes must provide the implementation for
     * following:
     *
     * Tests whether the selected text can be cut.
     * 
     * @return @c ETrue if it is possible to cut the selected text.
     */
	virtual TBool CcpuCanCut() const = 0;
	
    /**
     * Derived classes must provide the implementation for
     * following:
     *
     * Cuts selected text.
     */
	virtual void CcpuCutL() = 0;
	
    /**
     * Derived classes must provide the implementation for
     * following:
     *
     * Tests whether the selected text can be copied.
     * 
     * @return @c ETrue if it is possible to copy the selected text.
     */	
	virtual TBool CcpuCanCopy() const = 0;

    /**
     * Derived classes must provide the implementation for
     * following:
     *
     * Copies selected text.
     */	
	virtual void CcpuCopyL() = 0;
	
    /**
     * Derived classes must provide the implementation for
     * following:
     *
     * Tests whether text can be pasted from the clipboard.
     * 
     * @return @c ETrue if it is possible to paste the clipboard text.
     */	
	virtual TBool CcpuCanPaste() const = 0;

    /**
     * Derived classes must provide the implementation for
     * following:
     *
     * Pastes text from the clipboard to the editor.
     */	
	virtual void CcpuPasteL() = 0;
	
	/**
     * Derived classes must provide the implementation for
     * following:
     *
     * Tests is it possible to undo previous operation.
     * 
     * @return @c ETrue if it is possible to undo previous operation.
     */	
	virtual TBool CcpuCanUndo() const = 0;
	
    /**
     * Derived classes must provide the implementation for
     * following:
     *
     * Undoes the most recent text operation when the editor supports this
     * feature and when the undo store is not empty
     */	
	virtual void CcpuUndoL() = 0;
	};

/**
 * Cut, copy, paste and undo support class. Takes care
 * of CBA handling and menu command processing when FEP
 * instructs this control to activate the commands
 * for ccpu operations.
 */
class CAknCcpuSupport : public CAknControl, public MEikMenuObserver
	{
public:
    /**
     * Constructor. ConstructL() must be called after a call
     * to this function.
     *
     * @param aEditor A pointer to the editor implementing the
     * MEikCcpuEditor interface.
     */
	IMPORT_C CAknCcpuSupport(MEikCcpuEditor* aEditor);
	
	/**
	 * Destructor.
	 */
	IMPORT_C ~CAknCcpuSupport();
	
	/**
	 * 2nd phase constructor.
	 *
	 * Adds this control to the control stack.
	 */
	IMPORT_C void ConstructL();

    /**
     * Updates the CBA labels according to selection and
     * clipboard contents.
     */
	IMPORT_C void HandleSelectionChangeL();
	
	/**
	 * Updates the CBA labels according to editor focus
	 * state.
	 */
	IMPORT_C void HandleFocusChangeL();

	// from CCoeControl
    
    /**
     * Responds to key presses.
     * 
     * Overrides CCoeControl::OfferKeyEventL().
     * 
     * @param aKeyEvent The key event.
     * @param aType Not used.
     * @return Indicates whether or not the key event was consumed.
     */	
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

    /**
     * From @c CCoeControl.
     * 
     * Handles pointer events.
     *
     * @param aPointerEvent The pointer event.
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

	// from MEikMenuObserver
	
	/**
	 * From MEikMenuObserver.
	 * 
	 * Dynamically initialises a menu pane.
	 *
	 * @param aResourceId Resource ID of the menu.
	 * @param aMenuPane The in-memory representation of the menu pane.
	 */
	IMPORT_C void DynInitMenuPaneL(TInt aResourceId,CEikMenuPane* aMenuPane);

    /**
     * From MEikCommandObserver.
     *
     * Processes user commands.
     *
     * @param aCommandId ID of the command to respond to.
     */
	IMPORT_C void ProcessCommandL(TInt aCommandId);

private:
    void UpdateCBALabelsL();
    TBool UpdateCBALabelL(TInt aPosition, TInt aCommandId, TInt aTextResId);
    void SetEmphasis(CCoeControl* aMenuControl,TBool aEmphasis);
    void DeleteCBAL();

private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
private:
    TBitFlags iFlags;
    TBool isCbaEmded;
    // Owned
    CEikButtonGroupContainer* iCba;
    

	// Not owned
	CEikMenuBar* iMenu;
	MEikCcpuEditor* iEditor;
	CEikButtonGroupContainer* iDialogCba;
	};

#endif // EIKCCPU_H
