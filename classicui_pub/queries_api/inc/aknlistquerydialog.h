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
*   Implementation of CAknListQueryDialog
*
*/


#ifndef AKNLISTQUERYDIALOG_H
#define AKNLISTQUERYDIALOG_H

#include <AknQueryDialog.h>

class CAknMessageQueryControl;
class CAknListQueryMediatorObserver;

/**
 * List query class.
 *
 * This class is be used for list or multiselection list queries. 
 */
class CAknListQueryDialog : public CAknQueryDialog,
                            public MEikListBoxObserver, 
                            public MAknIntermediateState
	{
    public:
        /**
         * C++ default constructor.
         *
         * @param aIndex After the query is dismissed, the index will 
         *        hold the value of selected item.
         */
	    IMPORT_C CAknListQueryDialog(TInt* aIndex);

        /**
         * C++ default constructor.
         *
         * @param aSelectionIndexArray Will hold the values of selected
         *        items (in multiselection list).
         */
        IMPORT_C CAknListQueryDialog(
                  CListBoxView::CSelectionIndexArray* aSelectionIndexArray);

        /**
        * Destructor
        */
	    IMPORT_C virtual ~CAknListQueryDialog();

        /**
         * From @c CEikDialog.   
         *
         * Sets the type and position of the list box.
         *
         * @param aSize Not used.
         */
        IMPORT_C void SetSizeAndPosition(const TSize &aSize);

        /**
         * From @c CCoeControl.  
         *
         * Handles key events. When a key event occurs, @c CONE calls this 
         * function for each control on the control stack, until one of them
         * returns @c EKeyWasConsumed to indicate that it processed the key
         * event.  
         *
         * @param aKeyEvent The key event.
         * @param aType The type of the event: @c EEventKey, @c EEventKeyUp or 
         *        @c EEventKeyDown.
         * @return Indicates whether or not the key event was 
         *         used by this control.
         */
        IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, 
                                             TEventCode aType);
	    
        /**
         * From @c MEikListBoxObserver. 
         *
         * Handles events from listbox.
         * 
         * @param aListBox The listbox which caused the event.
         * @param aEventType Type of the event.
         */
        IMPORT_C void HandleListBoxEventL(CEikListBox* aListBox, 
                                          TListBoxEvent aEventType);

        /**
         * Sets item text array to the listbox.
         *
         * @param aItemTextArray Item text array to be added.
         */
        IMPORT_C void SetItemTextArray(MDesCArray* aItemTextArray);

        /**
         * Sets ownership type of the item array.
         *
         * @param aOwnershipType Type of ownership.
         */
        IMPORT_C void SetOwnershipType(
                        TListBoxModelItemArrayOwnership aOwnershipType);

        /**
         * Destroys a possible old icon array in the listbox and installs a new
         * one and takes ownership of the new icon array.
         *
         * @param aIcons Icon pointer which will be installed.
         */
        IMPORT_C void SetIconArrayL(CArrayPtr<CGulIcon>* aIcons);

        /**
         * Gets list query's listbox.
         *
         * @return The requested list box. 
         */
        IMPORT_C CEikListBox* ListBox() const;

        /**
         * Gets pointer to list query control or @c NULL.
         *
         * @return Pointer to list query control or in case that there is 
         *         no such element a @c NULL pointer. 
         */
        IMPORT_C CAknListQueryControl* ListControl() const;

        /**
         * Gets pointer to message query control or @c NULL.
         *
         * @return Pointer to message query control or in case that there 
         *         is no such element a @c NULL pointer. 
         */
        IMPORT_C CAknMessageQueryControl* MessageBox() const;

        /**
         * Gets pointer to query heading or @c NULL.
         *
         * @return Pointer to query heading or in case there is no such
         *         element a @c NULL pointer. 
         */
        IMPORT_C CAknPopupHeadingPane* QueryHeading() const;

        /**
         * From @c CCoeControl.
         *
         * Sets the control to be ready for drawing.
         */
        IMPORT_C void ActivateL();

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
         * If overriding @c HandlePointerEventL(), the implementation must 
         * include a base call to @c CCoeControl's @c HandlePointerEventL().
         *
         * @param &aPointerEvent The pointer event.
         */
        IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

    protected:
        /**
         * From @c CEikDialog.   
         *
         * This function is called by the @c EIKON dialog framework just
         * before the dialog is activated, but before it is sized,
         * and before @c PostLayoutDynInitL() is called.
         */
        IMPORT_C void PreLayoutDynInitL(void);

        /**
         * From @c CEikDialog.   
         *
         * This function is called by the @c EIKON dialog framework 
         * just before the dialog is activated, after it has called
         * @c PreLayoutDynInitL() and the dialog has been sized.
         */
        IMPORT_C void PostLayoutDynInitL();

        /**
         * From @c CEikDialog.   
         *
         * This function is called by the @c EIKON framework if the user 
         * activates a button in the button panel. It is not called if 
         * the @c Cancel button is activated, unless the 
         * @c EEikDialogFlagNotifyEsc flag is set.
         *
         * @param aButtonId The ID of the button that was activated
         * @return @c ETrue if the dialog should exit, 
         *         and @c EFalse if it should not.
         */
        IMPORT_C TBool OkToExitL(TInt aButtonId);

        /**
         * Gets border style of the list query.
         *
         * @return Border style (@c AknBorderId type)
         */
        IMPORT_C TInt BorderStyle();

    protected:
        /**
         * From @c MAknIntermediateState.
         * 
         * Tries to close the query with non-leaving way.
         */
        IMPORT_C void CloseState();

    private:
        /**
         * Closes the dialog.
         *
         * Gets called by iIdle.
         *
         * @param aObj Target dialog to be closed.
         * @return @c EFalse always. 
         */
        static TInt ClosePopup(TAny *aObj);

        /**
         * Closes the dialog and accepts selected item.
         *
         * Gets called by iIdle.
         *
         * @param aObj Target dialog to be closed. 
         * @return @c EFalse always.
         */
        static TInt ClosePopupAcceptingChanges(TAny *aObj);

    private:
        /**
        * From @c CAknControl
        */
        IMPORT_C void* ExtensionInterface( TUid aInterface );
	private: 
		IMPORT_C virtual void CEikDialog_Reserved_1();
		IMPORT_C virtual void CEikDialog_Reserved_2();	
	private: 
		IMPORT_C virtual void CAknDialog_Reserved();
	private:
		IMPORT_C virtual void CAknQueryDialog_Reserved();
    private:
        // Will hold the index of the selected item
        TInt *iIndex;
        // Will hold the selected items' indexes
        CListBoxView::CSelectionIndexArray *iSelectionIndexArray;
        // Was the enter key pressed
	    TBool iEnterKeyPressed;
        // Idle object to close the query if it there's no items to show
	    CIdle *iIdle;
        // Layout for List query control
	    TAknPopupWindowLayoutDef iLayout;

        CAknListQueryMediatorObserver* iMediatorObs;

        TInt iDragActioned;

    protected:
        /**
         * Gets search field if it has been set.
         *
         * @return Pointer to search field. If no search field is used 
         *         returns @c NULL.
         */
        IMPORT_C CAknSearchField* FindBox() const;
        
    public:
        /** 
         * Sets the tone for the dialog.
         *
         * @param aTone Tone to be used by the dialog.
         */
	    IMPORT_C void SetTone(TInt aTone);
	    
	    IMPORT_C void HandleResourceChange(TInt aType);
	    
	    
    	/**
    	* @since 3.1
	    * Override to CEikDialog default functionality
	    * Instantiates mediator support and send a command with given parameters when a 
	    * dialog is brought to display
	    * @param aDialogIndex Unique index to identify a dialog within the category
	    *                     0 has special meaning, it causes implementation to omit all communication
	    *                     with secondary display. (use with sleeping dialogs only)
	    * @param aCatUid  gategory uid, if default paramter is passed, application uid is used
	    *                 as a category
	    * @return void 
	    */
	    IMPORT_C void PublishDialogL(TInt aDialogIndex, TUid aCatUid = KNullUid,  CArrayFixFlat<TInt>* aItemIds = 0);
 
	
       /* @since 3.1
	    * Instantiates mediator support and passes possible feedback to given intance.
	    * If no observer is set, dialog tries to handle feedback by it self.
	    *
	    * Please note that no commands will be instantiated unless command identifiers are 
	    * are set using PublishDialogL
	    *
	    * @param  aObserver pointer to instance implementing MAknDialogMediatorObserver API
	    *         Can be NULL
	    * @return void 
	    */
	    IMPORT_C void SetMediatorObserver(MAknDialogMediatorObserver* aObserver);	    
	};

#endif //  AKNLISTQUERYDIALOG_H


// End of File
