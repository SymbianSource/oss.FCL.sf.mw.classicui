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
*
*/


#ifndef __AKNDIALOG_H__
#define __AKNDIALOG_H__


#include <eikdialg.h>
#include <eikmobs.h>


class CAknDialogAttributes;

/**
 * Base class for different types of @c AknDialogs
 *
 * Instances of the @c CAikDialog class may be created, and it is possible to
 * add controls directly to them. However it is more normal to create a 
 * subclass, and to handle the controls appearing on the dialog dynamically.
 */
class CAknDialog : public CEikDialog, public MEikMenuObserver
    {
    public :

        /** 
         * C++ default constructor. 
         */ 
        IMPORT_C CAknDialog() ;

        /** 
         * Handles Symbian 2nd phase construction.
         *
         * A menu resource MUST be specified - this function will Panic 
         * otherwise. If a menu is not required use @c CEikDialog!
         * 
         * @param aMenuTitleResourceId Title of the menu.
         */
        IMPORT_C void ConstructL( TInt aMenuTitleResourceId ) ;
		
        /**
         * Destructor. 
         */ 
        IMPORT_C ~CAknDialog() ;

        /**
         * From @c CEikDialog.
         *
         * Loads, displays, and destroys the dialog.
         * 
         * This function loads the specified dialog from a resource and 
         * displays it. The method then destroys the dialog when it exits,
         * therefore there is no need for the application program to 
         * destroy the dialog.
         *
         * @param aResourceId The resource ID of the dialog to load.
         * @return Zero, unless it is a waiting dialog. For a waiting dialog,
         *         the return value is the ID of the button that closed the
         *         dialog, or zero if it was the cancel button 
         *         (@c EEikBidCancel).
         */
		IMPORT_C TInt ExecuteLD( TInt aResourceId ) ;

        /**
         * From @c CEikDialog.
         *
         * Prepares the dialog, by constructing it from the specified resource.
         *
         * @param aResourceId The resource ID of the dialog.
         */
        IMPORT_C  void PrepareLC(TInt aResourceId);

        /**
         * From @c CEikDialog.
         *
         * Runs the dialog and returns the ID of the button used to dismiss it.
         *
         * The dialog is destroyed on exit.
         * 
         * This function is called by the dialog framework (@c ExecuteLD()) to
         * perform dynamic construction (layout) and to display/destroy the 
         * dialog. Static construction of the dialog must already be complete 
         * before this function is called, e.g. using @c PrepareLC().
         *
         * The function returns immediately unless @c EEikDialogFlagWait has 
         * been specified in the @c DIALOG resource. If @c EEikDialogFlagWait 
         * is specified, it returns when the dialog exits.
         *
         * @return The ID of the button used to dismiss the dialog.
         */
        IMPORT_C TInt RunLD();

		// From MEikMenuObserver
        /**
         * From @c MEikMenuObserver.
         *
         * Called by the Uikon framework to handle the emphasising or 
         * de-emphasising of a menu window.
         *
         * @c CEikMenuBar objects call this on their observer to emphasise
         * themselves when they are displayed, and de-emphasise themselves when
         * they stop displaying.
         *
         * @param aMenuControl The menu control. 
         * @param aEmphasis @c ETrue to emphasize the menu, 
         *        @c EFalse otherwise. 
         */ 
        IMPORT_C virtual void SetEmphasis( CCoeControl* aMenuControl,
                                           TBool aEmphasis ) ;
        /**
         * Not implemented.
         *
         * @param aResourceId Not used.
         * @param aMenuPane Not used.
         */ 
        IMPORT_C virtual void DynInitMenuPaneL( TInt aResourceId, 
                                                CEikMenuPane* aMenuPane ) ;

        /**
         * From @c MEikMenuObserver.
         *
         * Hides the menu.
         *
         * @param aCommandId Not used.
         */ 
		IMPORT_C virtual void ProcessCommandL( TInt aCommandId ) ;

		// From CCoeControl

        /** 
         * From @c CCoeControl.
         *
         * Handles key events.
         *
         * If a control wishes to process key events, it should implement this
         * function. The implementation must ensure that the function returns
         * @c EKeyWasNotConsumed if it does not do anything in response to a
         * key event, otherwise, other controls or dialogs may be prevented 
         * from receiving the key event. If it is able to process the event
         * it should return @c EKeyWasConsumed.
         *
         * When a key event occurs, the control framework calls this function 
         * for each control on the control stack, until one of them can process 
         * the key event (and returns @c EKeyWasConsumed).
         *
         * Each keyboard key press results in three separate events: 
         * @c EEventKeyDown, @c EEventKey, and @c EEventKeyUp, in that order.
         *
         * To receive key events, which can be processed by this function, 
         * the application should call @c CCoeAppUi::AddToStackL() to add the 
         * control to the stack. This only applies, however, to controls which 
         * are not components of a compound control. Compound controls should 
         * pass key events to their components as necessary: the components 
         * themselves do not go on the stack.
         *
         * @param aKeyEvent The key event. 
         * @param aType The type of key event: @c EEventKey, @c EEventKeyUp or 
         *        @c EEventKeyDown. 
         * @return Indicates whether or not the key event was used by 
         *         this control. 
         */ 
		IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,
                                             TEventCode aType) ;

        /** 
         * From @c CCoeControl.
         *
         * Responds to a change in focus.
         *
         * This is called whenever the control gains or loses focus, as a 
         * result of a call to @c SetFocus(). A typical use of 
         * @c FocusChanged() is to change the appearance of the control, 
         * for example by drawing a focus rectangle around it.
         *
         * @param aDrawNow Contains the value that was passed to it by 
         *        @c SetFocus(). 
         */ 
        IMPORT_C void FocusChanged(TDrawNow aDrawNow); 

        /** 
         * From @c CCoeControl.
         *
         * Handles pointer events.
         *
         * This function gets called whenever a pointer event occurs in the
         * control, i.e. when the pointer is within the control's extent, 
         * or when the control has grabbed the pointer. The control should 
         * implement this function to handle pointer events.
         *
         * Note: events of type @c EButton1Down are processed before 
         * @c HandlePointerEventL() is called, in order to transfer keyboard
         * focus to the control in which the @c EButton1Down event occurred.
         *
         * @param aPointerEvent The pointer event
         */ 
        IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

	private: // formerly from MTopSetMember<CEikMenuBar>, now reserved
		
        IMPORT_C virtual void Reserved_MtsmPosition();

        IMPORT_C virtual void Reserved_MtsmObject();

    private:
    
        /**
        * From CAknControl
        */
        IMPORT_C void* ExtensionInterface( TUid aInterface );

    protected:

        /**
         * From @c CEikDialog.
         *
         * Handles a dialog button press for the specified button. 
         *
         * This function is invoked when the user presses a button in the
         * button panel. It is not called if the Cancel button is activated 
         * unless the @c EEikDialogFlagNotifyEsc flag has been set.
         *
         * If there is an Options key then pops up menu, otherwise exits.
         *
         * The function should be overridden by the derived class, and is 
         * usually used to validate the values of the dialog's controls. 
         * The function should return @c ETrue if it is OK to exit, and 
         * @c EFalse to keep the dialog active. It should always return
         * @c ETrue if the button with ID @c EEikBidOK was activated.
         *
         * @param aButtonId The ID of the button that was activated.
         * @return @c ETrue to validate and exit the dialog, 
         *         @c EFalse to keep the dialog active. If @c ETrue, the 
         *         dialog will be destroyed automatically by @c ExecuteLD(). 
         *         The default implementation returns @c ETrue no matter which
         *         button is pressed.
         */
		IMPORT_C virtual TBool OkToExitL( TInt aButtonId ) ;

        /**
         * From @c CEikDialog.
         *
         * Displays menu bar.
         */
		IMPORT_C void DisplayMenuL() ;

        /**
         * From @c CEikDialog.
         *
         * Hides menu bar.
         */
        IMPORT_C void HideMenu() ;
		
        /**
         * From @c CEikDialog.
         *
         * Checks if menu is displayed.
         * 
         * @return @c ETrue if menu is displayed,
         *         @c EFalse otherwise.
         */
        IMPORT_C TBool MenuShowing() const ;
		
        /**
         * From @c CEikDialog.
         *
         * Lays out the dialog's components when the size of the dialog 
         * is changed.
         */
		IMPORT_C virtual void SizeChanged();
	
        /**
         * From @c CEikDialog.
         *
         * Draws the control.
         * 
         * @param aRect Area to be drawn.
         */
        IMPORT_C virtual void Draw(const TRect &aRect) const;

	protected: // from MObjectProvider
		
        /** 
         * From @c MObjectProvider. 
         *
         * Gets Mop supply object of the given type.  
         *
         * @param aId Identifier for the supply object.
         * @return Pointer to the supply object type ID.
         */
        IMPORT_C TTypeUid::Ptr MopSupplyObject(TTypeUid aId);

    private: 

		IMPORT_C virtual void CEikDialog_Reserved_1();
		
        IMPORT_C virtual void CEikDialog_Reserved_2();	

    private: // new function 

		IMPORT_C virtual void CAknDialog_Reserved();
	
    protected: // new function 

        /** 
         * Creates or replaces dialog's menu bar.
         *
         * @param aMenuTitleResourceId Title of the menu bar. 
         */ 
        void CreateMenuBarL(TInt aMenuTitleResourceId);

    protected:
		        
        /**
         * Dialog's menu bar. 
         * Not owned.
         */
		CEikMenuBar* iMenuBar;

private:

	enum TAknDialogFlag
	    {
	    EAknDialogFlagDialogDeleted = 1,
        EAknDialogFlagDefaultSounds = 2,
		EAknDialogFlagNotConstructed = 4
	    };

    CAknDialogAttributes* iAttributes;  // Was TInt iSpare;

	CAknDialogAttributes* AttributesL();

	} ;

#endif // __AKNDIALOG_H__

 
// End of file
