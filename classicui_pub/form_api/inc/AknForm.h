/*
* Copyright (c) 2002-2004 Nokia Corporation and/or its subsidiary(-ies).
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
* 	  Support for Form component. Also has CAknDialog which specialized 
*     CEikDialog (adds menu capability) Note that most support for Avkon
*     Forms is contained within CEikDialog.
*
*
*/


#ifndef __AKNFORM_H__
#define __AKNFORM_H__

// INCLUDES
#include <AknDialog.h>

// CLASS DECLARATION
class CEikMenuBar ;

/**
* Forms are special types of dialogs. The item layout and functionality can
* differ between the two states. In the view state, the fields are not 
* editable. It looks and acts like a listbox. The listbox focus can be moved
* and items can be selected.
*
*  @since Series 60 0.9
*/
class CAknForm : public CAknDialog
	{
public:
	
	/**
	* Base class default constructor.
	*/
	IMPORT_C CAknForm();
	
	/**
    * Perform the second phase construction of a object. If a leave occurs
    * the framework generates a Symbian Leave code.
    * @param aMenuResource The menu resource to be used for the form.
    */
	IMPORT_C void ConstructL( TInt aMenuBarId=0 );
	
	/**
	* Destructor.
	*/
	IMPORT_C ~CAknForm();

    /**
    * Function from @c MEikMenuObserver. The framework 
    * calls this function. It removes the unused default form options. If a 
    * leave occurs the framework generates a Symbian Leave code. 
    * @param aResourceId The ID of the menu pane.
    * @param aMenuPane The menu pane itself.
    */
	IMPORT_C virtual void DynInitMenuPaneL( TInt aResourceId, CEikMenuPane* aMenuPane );

    /**
    * Function from @c MEikCommandObserver. Handle user menu commands. If a
    * leave occurs the framework generates a Symbian Leave code.
    * @param aCommandId The command identifier to process.
    */ 
	IMPORT_C virtual void ProcessCommandL( TInt aCommandId );

protected:
	/**
	* Function from @c CEikDialog. Called by framework when the softkey is 
	* pressed. Use this to pop up the options menu or close the dialog. Will
	* call c@ SaveFormDataL() before closing if data has been edited. Will 
	* NOT permit exit if attempt to save data fails. If a leave occurs the 
	* framework generates a Symbian Leave code.
 	* @param aButtonId Translates the button presses into commands ID.
 	* @return @c ETrue if the dialog should exit, and @c EFalse if it should
 	* not. 
	*/ 
	IMPORT_C virtual TBool OkToExitL( TInt aButtonId );

	/**
	* Function from @c CEikDialog and thence from c@ MEikDialogPageObserver.
	* This funtion should be implemented to prepare for focus transition from
	* the current line. If deleting then this routine must not do anything (the
	* default tries to access the control which has just been deleted). If a
	* leave occurs the framework generates a Symbian Leave code.
	*/
	IMPORT_C virtual void PrepareForFocusTransitionL();

public:

	/**
	* Function from @c CCoeControl handles a change to the control's resources
	* of type aType which are shared across the environment, e.g. colors or 
	* fonts.
	* @param aType. A message UID value.
	* @since Series 60 2.0
	*/
	IMPORT_C void HandleResourceChange(TInt aType);

        /**
         * From CCoeControl.     
         * Handles pointer events
         * @param aPointerEvent     The pointer event.
         */
    	IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

protected:

	/**
	* This routine should be re-implemented by the client to save the contents
	* of the form. The re-implementation can call this function to display the 
	* 'Saved' dialog @c CAknForm::SaveFormDataL().
	* @return @c ETrue if the editable state can be left. The return value should
	* reflect whether or not the form is to leave the editable state. A real 
	* system problem saving should generate a Symbian Leave code.
	*/
	IMPORT_C virtual TBool SaveFormDataL(); 
	
	/**
	* This routine should be implemented by the client for dealing with the 
	* occasion of a change from edit->view mode but the user does not wish to 
	* save the changes. A typical implementation would set the controls back 
	* to their old values. If a leave occurs the framework generates a 
	* Symbian Leave code.
	*/
	IMPORT_C virtual void DoNotSaveFormDataL(); 

	/**
	* This routine may be overridden. Default displays 'Save Changes Dialog 
	* Yes/No'. Data validation may occur here as an alternative to overriding
	* @c OkToExit(). Re-implementation may put data validation here (as an 
	* alternative to over-riding @c OkToExit() - which is a more complicated 
	* method). Note that this routine does not perform the changes itself. If 
	* the leave occurs the framework generates a Symbian Leave code.
	* @return @c ETrue if changes are requested to be saved and then are 
	* successfully saved. Save of data is not performed here but in 
	* @c SaveFormDataL().
    */
	IMPORT_C virtual TBool QuerySaveChangesL();
	
	/**
 	* This routine may be overridden. Default displays old label as caption and
 	* editor for new one. Uses customised dialog.If a leave occurs the 
 	* framework generates a Symbian Leave code.
 	*/
	IMPORT_C virtual void EditCurrentLabelL();
		
	/**
 	* This routine may be overridden. Default displays "Delete item? Yes/No"
 	* Deletes item on return from the dialog before returning. If a leave occurs
 	* the framework generates a Symbian Leave code.
 	*/	
	IMPORT_C virtual void DeleteCurrentItemL();
	
	/**
 	* This routine may be overridden. Implementation is missing in this class.
 	*/	
	IMPORT_C virtual void AddItemL();
	
	/**
	* Sets changes pending.
	* @param aChangesPending @c ETrue if changes are pending. Else @cEFalse. 
	*/	
	IMPORT_C void SetChangesPending(TBool aChangesPending);
	
	/**
	* Function from @c CEikdialog. This function is called by the EIKON 
	* dialog framework just before the dialog is activated, after it has 
	* called @c PreLayoutDynInitL() and the dialog has been sized. If a  
	* leave occurs the framework generates a Symbian Leave code.
	*/	
	IMPORT_C void PostLayoutDynInitL();
	
	/**
	* Overridden, so that the form can tell if a line's state has changed.
	* This is used to decide when to save changes. If a leave occurs the
	* framework generates a Symbian Leave code.
	* @param aControlId. Control id. 
	*/	
	IMPORT_C void HandleControlStateChangeL(TInt aControlId);
	
	/** 
	* This is added, so that anyone adding lines either in @c PreLayoutDynInit()
	* or @c SetInitialCurrentLine() should have the lines in a consistent state.
	*/	
	IMPORT_C void SetInitialCurrentLine();

	/** 
	* Required by @c OkToExit().
	* @return @c ETrue if unsave editing, and @c EFalse if it 
	* should not.
	*/
	IMPORT_C TBool UnsavedEdit() const;
	
	/** 
	* Required by @c PrepareForFocusTransitionL().
	* @return @c ETrue if deleting, and @c EFalse if it 
	* should not.
	*/	
	IMPORT_C TBool Deleting() const;

enum TFlags
	{
	/** Flag for deleting item. */
	EDeleting = 0x1, // Form flag enum
	
	/** Flag for unsave editing item. */
	EUnsavedEdit = 0x2 // Form flag enum
	};

	/**
	* Set the form flag indicated.
	* @param aFlagPattern Pattern of bits to set or clear.
	* @param aSetTheFlag If @c ETrue, sets the pattern; if @c EFalse, clear the 
	* pattern.
	*/
	IMPORT_C void SetFormFlag( TFlags aFlagPattern, TBool aSetTheFlag );

private: 
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );

private: 
	IMPORT_C virtual void CEikDialog_Reserved_1();
	IMPORT_C virtual void CEikDialog_Reserved_2();	
private: 
	IMPORT_C virtual void CAknDialog_Reserved();
private:// new function  
	IMPORT_C virtual void CAknForm_Reserved();
private: // helpers
	void DoLayout();
private :
	TInt iMenuBarId ;  // resource ID
	TInt iFlags ;
	TInt iWsBufferRequestID;
	} ;

#endif	// __AKNFORM_H__
