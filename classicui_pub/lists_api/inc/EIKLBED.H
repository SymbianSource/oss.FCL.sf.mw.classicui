/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
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

   
#if !defined(__EIKLBED_H__)
#define __EIKLBED_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__EIKLBM_H__)
#include <eiklbm.h>
#endif

#if !defined(__W32STD_H__)
#include <w32std.h>
#endif

#if !defined(__COEDEF_H__)
#include <coedef.h>
#endif

#if !defined(__COECNTRL_H__)
#include <coecntrl.h>
#endif

#include <AknControl.h>

class CEikEdwin;
class CParaFormatLayer;
class CCharFormatLayer;

/**
 * The MEikListBoxEditor class specifies an interface to a text editor which can be used inside
 * a list box.
 *
 * @since ER5U
 */
class MEikListBoxEditor
	{
public:
    /**
     * Returns a pointer to the current editable item text.
     */
	virtual TPtrC ItemText() = 0;

    /**
     * Creates the editor inside the list box aContainer. The editor occupies the rectangle aRect
     * and is used to editor the contents of the item at index aItemIndex up to a maximum length of
     * aMaxLength characters..
     */
	virtual void StartEditingL(const CCoeControl& aContainer,const TRect& aRect,TInt aItemIndex,TInt aMaxLength) = 0;

    /**
     * Stops editing and deletes the item editor. 
     */
	virtual void StopEditingL() = 0;

    /**
	 * Updates the list box model with the new item contents.
	 */
	virtual TBool UpdateModelL() = 0;

	/**
	 * Deletes the editor.
	 */
	virtual void Release() = 0;
private:
	IMPORT_C virtual void MEikListBoxEditor_Reserved_1();
	};

class MListBoxEditorObserver
	{
public:
	virtual TKeyResponse HandleListBoxEditorEventL(MEikListBoxEditor* aListBoxEditor, const TKeyEvent& aKeyEvent)=0;
	};

/**
* The @c CEikListBoxTextEditor implements a text list box item editor. This 
* editor is used inside of listbox items for editing the list box item text.  
*
* @since ER5U
*/
class CEikListBoxTextEditor : public CAknControl, public MEikListBoxEditor
	{
public:

    /**
     * C++ default constructor.
     *
     * @param aModel Model class of the list box.
     */
	IMPORT_C CEikListBoxTextEditor(MListBoxModel* aModel);
	
    /**
     * Destructor
     */
	IMPORT_C ~CEikListBoxTextEditor();

    /**
     * Sets font to the text editor
     *
     * @param aFont New font for the text editor.
     */
	IMPORT_C void SetFont(const CFont* aFont);

    /**
     * Gets text editor instance as @c CEikEdwin.
     *
     * @return CEikEdwin* Pointer to the text editor base class instance. 
     */
	IMPORT_C CEikEdwin* Editor();

    /**
     * Sets observer to the text editor. 
     *
     * @param aObserver The list box editor observer interface.
     */
	IMPORT_C void SetListBoxEditorObserver(MListBoxEditorObserver* aObserver);

public: // from MEikListBoxEditor

    /**
     * From @c MEikListBoxEditor. 
     * This function returns the text of the list box item.
     *
     * @return TPtrC Pointer descriptor to the list box item text.
     */
	IMPORT_C TPtrC ItemText();

	/**
     * From @c MEikListBoxEditor. 
     * This function creates text editor inside the 
     * list box item and starts editing of the item text. The list box item can 
     * contain partly editable text. This text is between '\\n' chars and this
     * control does not modify it. 
     *
     * @param aContainer Container class of the list box.
     * @param aRect Retangle of the list box item.
     * @param aItemIndex Index of the list box item where text editor will be
     *					created.
     * @param aMaxLength Maximum length of editor in characters.
     */
	IMPORT_C void StartEditingL(const CCoeControl& aContainer, 
								const TRect& aRect, 
								TInt aItemIndex, 
								TInt aMaxLength);
	
    /**
     * From @c MEikListBoxEditor. 
     * Stops editing the current item and deletes the text editor. 
     */
	IMPORT_C void StopEditingL();

    /**
     * From @c MEikListBoxEditor. 
     * Updates the list box model with new text from text editor. If text is 
     * partly editable, string between '\n' chars is not updated.
     *
     * @return TBool @c EFalse if editing is not currently on otherwise @c ETrue
     */
	IMPORT_C TBool UpdateModelL();

	/**
     * From @c CCoeControl. 
     * Handles key press events. Called by the control framework.
     *
     * @param aKeyEvent The key event 
     * @param aType The type of key event: @c EEventKey, @c EEventKeyUp or 
     *              @c EEventKeyDown.
     * @return TKeyResponse Indicates whether or not the key event was used by 
     *                      this control.
     */
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, 
										 TEventCode aType);

public: // From CCoeControl

    /**
     * From @c CCoeControl. 
     * Handles pointer events.
     *
     * @param aPointerEvent The pointer event.
     */	
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
    	
protected: // from MEikListBoxEditor

    /**
     * From @c MEikListBoxEditor. 
     * Deletes the editor. 
     */
	IMPORT_C void Release();

protected:

    /**
     * Gets the list box model.
     *
     * @return MListBoxModel* Pointer to the list box model instance.
     */
	IMPORT_C MListBoxModel* ListBoxModel();

    /**
     * Function for getting the list box item index that holds the text editor.
     *
     * @return TInt Index of the list box item that holds the text editor.
     */
	IMPORT_C TInt ItemIndex() const;

private: // from MEikListBoxEditor

	IMPORT_C void MEikListBoxEditor_Reserved_1();

protected:

    /**
     * This function writes the internal state of the control and its components
     * to @c aStream in debug mode. Does nothing in release mode. 
     *
     * @param aWriteStream Stream where control and its components internal 
     *                     state will be written.
     */
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;

private:

	void UseFontL(CEikEdwin& editor, const CFont& aFont);

	TPtrC EditableItemText(TRect* aRect=NULL);

private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface(TUid aInterface);

private:
	MListBoxEditorObserver* iEditorObserver;
	MListBoxModel*  iModel;
	CEikEdwin*		iEditor;
	TInt            iItemIndex;
	CFont*          iFont;
	TInt			iItemPos;
	TInt			iItemLen;
	CParaFormatLayer* iParaFormatLayer;
	CCharFormatLayer* iCharFormatLayer;
    TInt iSpare[2];
	};

#endif


//  End of File