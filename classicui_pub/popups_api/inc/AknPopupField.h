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
*     Represents a combo box type control, used to implement the Series 60 
*     pop-up field.
*     
*
*/


#ifndef AKNPOPUPFIELD_H
#define AKNPOPUPFIELD_H

#include <eikcmobs.h>
#include <eiklbx.h>
#include <eikbctrl.h>
#include <eikcmbut.h>
#include <bamdesca.h>

#include <AknDesCArrayDecorator.h>
#include <AknListBoxLayoutDecorator.h>
#include <aknnotedialog.h>

class TResourceReader;
class CEikLabel;
class CEikCommandButton;
class CAknFormGraphicStyleListBox;
class MAknQueryValue;

class CAknPopupField;
class CAknPopupFieldExtension;

/** 
 * this interface should be implemented by classes that need to know
 * about events occurring in the popup field control
 */
class MAknPopupFieldObserver
	{
public:
	enum TAknPopupFieldEvent
		{
		EAknPopupFieldEventModeChange,
		EAknPopupFieldEventValueChange
		};
public:
    /**
     * Handles events from the popup field control, such as changes between
     * selection list mode and label mode.
     *
     * @param aPopupField pointer to the popup field control that generated
     *        the event.
     * @param aEventType the type of event.
     * @param aHint for possible future use.
     */
    virtual void HandlePopupFieldEventL(CAknPopupField* aPopupField,
                                        TAknPopupFieldEvent aEventType,
                                        TInt aHint)=0;
	};

/**
 * Represents a combo box type control, used to implement the Series 60 
 * pop-up field.
 */
class CAknPopupField :
	public CEikBorderedControl, 
	public MCoeControlObserver, 
	public MEikCommandObserver, 
	public MEikListBoxObserver
	{
protected:
	/**
	 * Specialises bitmap button to make the layout correct for popup field
	 */
	class CAknPopupFieldBitmapButton : public CEikBitmapButton
		{
	public:
		/**
		 * Constructor
		 */
		CAknPopupFieldBitmapButton();
		};
public:
    /**
     * Selection mode of the popup field.
     */
    enum EAknPopupFieldSelectionMode
        {
        /** 
         * Label mode. In Label mode popup field is minimized and popup field
         * looks identical to a list item. When it receives the selection key 
         * press it is changed to @c EAknPopupFieldSelectionListMode and the 
         * pre-defined list is displayed. 
         */
        EAknPopupFieldLabelMode,
		
        /** 
         * Selection list mode. In this selection mode pre-defined popup 
         * selection list is displayed.
         */    
		EAknPopupFieldSelectionListMode
		};

    /**
     * Form mode for the popup field.
     */
	enum EAknFormMode
        {
        /** View mode. */
        EAknFormModeView,

        /** Editable mode. */    
        EAknFormModeEdit,

        /** View mode with graphic. */
        EAknFormModeViewWideWithGraphic,

        /** View mode without graphic. */
        EAknFormModeViewWideWithoutGraphic,

        /** Edit mode with graphic. */
        EAknFormModeEditWideWithGraphic,

        /** Edit mode without graphic. */
		EAknFormModeEditWideWithoutGraphic
		};
public: 
	EAknPopupFieldSelectionMode SelectionMode() const { return iSelectionMode; }
	EAknFormMode FormMode() const { return iFormMode; }
    /**
     * C++ default constructor.
     */
	IMPORT_C CAknPopupField();

	/**
	 * Destructor
	 */
	IMPORT_C ~CAknPopupField();

    /** 
     * Handles 2nd phase construction.
     */
	IMPORT_C void ConstructL();

    /**
     * Sets a flag that enables user defined entry. Note that flag can also be 
     * set from resources, but this method allows behaviour to be changed at 
     * runtime.
     *
     * @param aAllows if @c ETrue sets a flag.
     */
	IMPORT_C void SetAllowsUserDefinedEntry(TBool aAllows);

    /**
     * Causes a list of pre-defined values to appear. 
     * Use this method to activate the pop-up field from a menu option command.
     * Note that the desired control must be focused on before it can be 
     * activated.
     */
	IMPORT_C void ActivateSelectionListL();

    /**
     * Used by the client to set the query value. It is used to represent the 
     * user defined query value in this popup field control.
     *
     * @param aValue Pointer to query value, ownership is not passed.
     */
	IMPORT_C void SetQueryValueL(MAknQueryValue* aValue);

    /**
     * Sets the font of the contained label.
     *
     * @param aFont Font definition used to set the font of the contained 
     *        label.
     */
	IMPORT_C void SetFont(const CFont* aFont);

    /**
     * Sets a flag that determines whether the indicators are shown.
     * In practice the indicators have the appearance of radio buttons.
     *
     * @param aShowIndicators If @c ETrue, indicators are displayed.
     */
	IMPORT_C void SetShowIndicatorsL(TBool aShowIndicators);

    /**
     * Number of lines used.
     *
     * @return Number of entries on the selection list. If selection list 
     *         is not active, 1 is returned.
     *	       NOTE that the number is limited by @c KAknMaxEditorLines.
     */
	IMPORT_C TInt NumLines() const;

    /**
     * Sets an observer of this class to receive events from popup field.
     * 
     * @param aObserver Pointer to the class that implements the observer 
     *        interface.
     */
	IMPORT_C void SetPopupFieldObserver(MAknPopupFieldObserver* aObserver);

    /**
     * Sets the note to be displayed when the selection list has no items 
     * available.
     * 
     * @param aResourceId Resource id for the note.
     * @param aTimeout = CAknNoteDialog::EShortTimeout Timeout for the note. 
     * @param aTone = CAknNoteDialog::ENoTone Tone for the note.
     */
	IMPORT_C void SetEmptyListNoteL(TInt aResourceId,
									CAknNoteDialog::TTimeout aTimeout = CAknNoteDialog::EShortTimeout,
									CAknNoteDialog::TTone aTone = CAknNoteDialog::ENoTone);

    /**
     * Sets the empty list note text. This note is displayed when the 
     * selection list has no items available.
     * 
     * @param aEmptyText The empty list note text.
     */
    IMPORT_C void SetEmptyTextL(const TDesC& aEmptyText);

    /**
     * Sets the text to be added to the bottom of the array to enter user 
     * defined data.
     * 
     * @param aOtherText Text to the bottom of the selection array.
     */
	IMPORT_C void SetOtherTextL(const TDesC& aOtherText);

    /**
     * Sets the text for view state when none of the elements in the
     * list are available. 
     *
     * @param aInvalidText The invalid text.
     */
	IMPORT_C void SetInvalidTextL(const TDesC &aInvalidText);

    /**
     * Closes the selection list 
     *
     *  @since v5.2 
     */
    IMPORT_C void CloseSelectionListL();

public: // from CCoeControl

    /** 
     * From @c CCoeControl.
     *
     * Handles key events.
     *
     * @param aKeyEvent The key event. 
     * @param aType The type of key event.
     * @return Indicates whether or not the key event was used by this control.
     */
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

    /** 
     * From @c CCoeControl.
     * 
     * Constructs the control from a resource file.
     *
     * @param aReader The resource reader pointing to the popup field resource.
     */
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

    /** 
     * From @c CCoeControl.
     *
     * Determines the minimum size of the control.
     * 
     * @return The minimum size required by the control.
     */
	IMPORT_C TSize MinimumSize();

    /**
     * From @c CCoeControl.
     *
     * Handles a change to the control's resources.
     *
     * @param aType The type of the resource change. 
	 */
	IMPORT_C void HandleResourceChange(TInt aType);

    /**
     * From @c CCoeControl.
     *
     * Handles pointer events of popup field list.
     *
     * @param aPointerEvent The pointer event to be handled.
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
public:
	/**
    /**
     * Sets the maximium number of lines that can be displayed.
     *
     * @param aMaxNoLines The maximum number of lines.
     */
	IMPORT_C void SetMaxNumberOfLinesPermitted(TInt aMaxNoLines);
public:

    /**
     * Sets a form field rectangle so that a popup field can correctly position
     * the label.
     *
     * @param aFormFieldRect The form field rectangle.
     */
	IMPORT_C void SetFormFieldRect(TRect aFormFieldRect);

protected: // from MCoeControlObserver
	
    /** 
     * From @c MCoeControlObserver.
     *
     * Handles an event from an observed control.
     *
     * @param aControl The control that sent the event.
     * @param aEvent The event type. 
     */
	IMPORT_C void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEvent);
protected: // from MEikCommandObserver
	
    /**
     * From @c MEikCommandObserver.
     *
     * Processes events from the softkeys. Responds to @c EAknSoftkeyOk and 
     * @c EAknSoftkeyCancel to accept or cancel the pop-up.
     * 
     * @param aCommandId Event Id from the soft-key.
     */
	IMPORT_C void ProcessCommandL(TInt aCommandId);	
protected: // From MEikListBoxObserver

    /**
     * From @c MEikListBoxObserver.
     *
     * Processes key events from the listbox. Responds to 
     * @c EEventEnterKeyPressed to accept the pop-up.
     * 
     * @param aListBox Listbox being observed.
     * @param aEventType Event observed.
     */
    IMPORT_C void HandleListBoxEventL(CEikListBox* aListBox, 
                                      TListBoxEvent aEventType);
protected: // from CCoeControl

    /** 
     * From @c CCoeControl.
     *
     * Gets the number of controls contained in a compound control.
     *
     * @return The number of component controls contained by this control.
     */
	IMPORT_C TInt CountComponentControls() const;

    /** 
     * From @c CCoeControl.
     *
     * Gets an indexed component of a compound control.
     * 
     * @param aIndex Control index.
     * @return The component control with an index of @c aIndex. 
     */
	IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;

    /** 
     * From @c CCoeControl.
     *
     * Responds to changes to the size and position of the contents of this 
     * control.
     */
	IMPORT_C void SizeChanged();

    /**
     * From @c CCoeControl.
     *
     * Responds to a change in focus.
     *
     * @param aDrawNow Contains the value that was passed to it by 
     *        @c SetFocus(). 
     */
    IMPORT_C void FocusChanged( TDrawNow aDrawNow );

    /**
     * From @c CEikBorderedControl.
     *
     * Called by the framework to draw the control.
     *
     * @param aRect Rectangle in which the Cone framework believes drawing is 
     *        needed.
     */
	IMPORT_C void Draw(const TRect& aRect) const;

private: // from CCoeControl
	IMPORT_C void Reserved_1();
	IMPORT_C void Reserved_2();

private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );

protected: // personal

    /**
     * Construction tasks common to both a normal construction and a construction 
     * from a resource. Used from @c ConstructL() and 
     * @c ConstructFromResourceL().
     */
	void CommonConstructL();
protected: // from MObjectProvider

    /**
     * From @c CCoeControl.
     *
     * Retrieves an object of the same type as that encapsulated in @c aId.
     *
     * @param aId An encapsulated object type ID.
     * @return Encapsulates the pointer to the object provided. 
     *         Note that the encapsulated pointer may be NULL.
     */
	IMPORT_C TTypeUid::Ptr MopSupplyObject(TTypeUid aId);
private: // personal

    /** 
     * Create the label that will show the currently selected value.
     *
     */
	void ConstructLabelL();

	/** 
	 * Create the command button that will be used to show the other choices indicator.
	 *
	 */
	void ConstructCommandButtonL();

	/** 
	 * Create the selection list box that will fill the expanded popup field
	 *
	 */
	void ConstructSelectionListL();

	/** 
	 * setup the scroll bar within the selection list box
	 *
	 */
	void SetUpScrollBarL();

	/** 
	 * set the scroll bar selection
	 *
	 */
	void SetScrollBarSelectionL();

	/** 
	 * Set up the bitmap array for the "not pushed" and "pushed in" states
	 *
	 */
	void InitialiseRadioButtonBitmapsL();

	/**
	 * Handles the case where the selection list is closed. If necessary, 
	 * update the value of the text label that is displayed.
	 * 
	 * @return TBool ETrue always
	 */
	TBool HandleInteractionConfirmedL();

	/**
	 * Create the popup list. Warn the user if there are no entries in the list.
	 *
	 */
	void CreatePopoutL();

	/**
	 * Destroy the popup list and remove it from the stack
	 *
	 */
	void DestroyPopout();

	/**
	 * Checks to see if the popupfield is empty
	 *
	 */
	TBool IsEmpty() const;
	/**
	 * Checks to see if the popupfield is invalid
	 *
	 */
	TBool IsInvalid() const;
	/**
	 * Handles a horizontal key event
	 *
	 * @return TKeyResponse returns either EKeyWasConsumed
	 *                       or EKeyWasNotConsumed
	 */
	TKeyResponse HandleHorizontalKeyEventL(TUint aKeyEventCode);
private: // Avkon

    /**
     * Creates the CBA for use when the selection list is active
     */
	void CreateCbaL();

	/**
	 * Configures the decoration according to the currently set flags.
	 * Should be called whenever the flags are changed. 
	 *
	 */
	void ConfigureDecorator();

	/**
	 * Configures the layout decoration according to the radio button flag
	 * Should be called whenever the flags are changed. 
	 *
	 */
	void ConstructLayoutDecoratorL();

	/**
	 * display a note when the selection list has no items available
	 *
	 */
	void ShowEmptyListNoteL();

	/**
	 * Re-defined method of the base class. Gets called when the 
	 * user tries to select a value. If required, an editor is created to 
	 * allow the user to input the user defined value. Otherwise, the
	 * normal selection behaviour of popup list is activated.
	 *
	 * @param aAccept	If ETrue, popup list was accepted; 
	 *								if EFalse, popup list was cancelled
	 *
	 */
	void AttemptExitL(TBool aAccept);

	/**
	 * Changes the mode of the popupfield to one of
	 * the EAknPopupFieldSelectionMode's
	 */
	void ChangeMode(EAknPopupFieldSelectionMode aNewMode);

private: // async 
	static TInt AttemptExitCallbackL(TAny* aThis);
	void DoAttemptExitL();
	void DoSizeChangedL();
protected:
	// the following members are owned
    /**
     * Label of the popup field.
     * Own.
     */
	CEikLabel* iLabel;

    /**
     * Bitmap button for the popup field.
     * Own.
     */
	CAknPopupFieldBitmapButton* iButton;

    /**
     * List box for the popup field usage.
     * Own.
     */
	CAknFormGraphicStyleListBox* iSelectionList;

    /**
     * Contains a popup field selection array and a leading text that will be 
     * inserted before the text from the descriptor array entry.
     * Own.
     */
	CAknListBoxLayoutDecorator* iLayoutDecorator;

    /**
     * Button group container for the popup field.
     * Own.
     */
	CEikButtonGroupContainer* iCba;

    /**
     * Active object for calling @c AttemptExitCallbackL asynchronously.
     * Own.
     */
	CAsyncCallBack* iAttemptExitAsync;

	// the following fields are reflected in the POPUP_FIELD resource structure
    /**
     * Flags for the popup field.
     */
    TInt iFlags;

    /**
     * Maximum line width.
     */
    TInt iWidth;

    /**
     * Text to the bottom of the selection array.
     * Own.
     */
    HBufC* iOtherText;

    /**
     * The empty list note text.
     * Own.
     */
    HBufC* iEmptyText;

    /**
     * The invalid text. Used in the view state when none of the elements in the
     * list are available. 
     * Own.
     */
    HBufC* iInvalidText;

    /**
     * Resource id for the empty note.
     */
	TInt iEmptyNoteResourceId;
	
	// the following members are not owned
    /**
     * Query value for the popup field.
     * Not own.
     */
	MAknQueryValue* iValue;

    /**
     * Observer for receiving events from the popup field.
     * Not own.
     */
	MAknPopupFieldObserver* iObserver;

	// the following values are member variables
    /**
     * Enumeration representing form mode values.
     */
    EAknFormMode iFormMode;

    /**
     * Timeout for the empty tone.
     */
    CAknNoteDialog::TTimeout iEmptyNoteTimeout;

    /**
     * Tone for the empty note.
     */
    CAknNoteDialog::TTone iEmptyNoteTone;

    /**
     * Selection array for the popup field.
     */
    TAknDesCArrayDecorator iDecorator;

    /**
     * Enumeration representing selection mode values.
     */
    EAknPopupFieldSelectionMode iSelectionMode; 

    /**
     * Maximum number of items in selection array.
     */
	TInt iMaxNoLines;
	// NOTE: use Extension() to extend this class.
private:
	CAknPopupFieldExtension* iExtension;
    TInt iSpare[3];
	};

#endif // AKNPOPUPFIELD_H
