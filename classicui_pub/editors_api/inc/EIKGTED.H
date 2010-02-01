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


#if !defined(__EIKGTED_H__)
#define __EIKGTED_H__

#if !defined(__EIKEDWIN_H__)
#include <eikedwin.h>
#endif


#if !defined(__BADESCA_H__)
#include <badesca.h>
#endif

#if !defined(__EIKON_HRH__)
#include <eikon.hrh>
#endif

class CGlobalText;
class CControlEnv;
class CEikDialogToolBar;
class CPrintSetup;
class CTextPageRegionPrinter;
class CEikDialogToolBar;

/**
 * Global text editor.
 *
 * This is an edit window which supports globally formatted text. Supports
 * a line cursor and provides functions which make it easy to launch various
 * dialogs, for instance search, replace, set font etc. 
 * 
 * @since Symbian 5.0
 */ 
class CEikGlobalTextEditor : public CEikEdwin
	{

public:

    /**
     * Font style
     */
	enum TFontStyleFlags
		{
        /** Normal font */
        EStandard	=0x00,

        /** Bolded font */
		EBold		=0x01,

        /** Italic font */
		EItalic		=0x02,

        /** Underlined font */
		EUnderline	=0x04
		};

public: // construction and destruction

    /** 
     * C++ default constructor.
     */
    IMPORT_C CEikGlobalTextEditor();
	
    /** 
     * C++ default constructor.
     *
     * @param aBorder The editor's border.
     */ 
    IMPORT_C CEikGlobalTextEditor(const TGulBorder& aBorder);
	
    /**
     * Destructor.
     */
    IMPORT_C ~CEikGlobalTextEditor();
	
    /** 
     * By Default symbian 2nd phase constructor is private.
     *
     * Completes construction of the global text editor.
     *
     * The editor's paragraph and character formatting is set to 
     * default values.
     *
     * @param aParent The editor's parent control. Omit if the 
     *        editor has no parent.
     * @param aNumberOfLines The editor's number of lines.
     * @param aTextLimit The maximum length of the editor in characters.
     * @param aEdwinFlags The editor's flags. See @c CEikEdwin::TFlags.
     * @param aFontControlFlags A set of flags that specify which font 
     *        controls should appear, e.g. specifying @c EGulFontControlBold
     *        removes the bold checkbox control. The default shows all. 
     *        For possible values, see @c gulftflg.hrh.
     * @param aFontNameFlags The editor's font name flags. For possible 
     *        values, see @c gulftflg.hrh.
     */ 
    IMPORT_C void ConstructL(const CCoeControl* aParent,
                             TInt aNumberOfLines,
                             TInt aTextLimit,
                             TInt aEdwinFlags,
                             TInt aFontControlFlags,
                             TInt aFontNameFlags);
	
    // This feature is not supported in Avkon; type made more general for 
    // source compatibility

    /**
     * Not implemented.
     *
     * @param aButtonGroup Not used
     */ 
	IMPORT_C void SetButtonGroup(CCoeControl* aButtonGroup);
	
    // This feature is not supported in Avkon
    /**
     * Not implemented.
     *
     * @param aBitmap Not used
     */
	IMPORT_C void SetLineCursorBitmapL(CFbsBitmap* aBitmap);

public: // formatting dialogs

    /**
     * Runs a dialog enabling a user to set the font.
     *
     * Updates the button group to reflect any text formatting applied.
     *
     * @param aFontFlags = EGulNoSymbolFonts Specifies which font types should
     *        appear in the list. For possible values see @c gulftflg.hrh.
     * @param aGraphicsDevice = NULL The graphics device. This is used to get 
     *        the list of available fonts. If NULL the default screen device 
     *        is used.
     * @param aFontControlFlags = EGulFontControlAll A set of flags that specify 
     *        which font controls should appear in the dialog e.g. specifying 
     *        @c EGulFontControlBold removes the bold checkbox control. 
     *        The default shows all. For possible values see @c gulftflg.hrh.
     * @return @c ETrue if user made a change and pressed @c OK. 
     *         @c EFalse if user pressed cancel or made no changes.
     */
    IMPORT_C TBool RunFontDialogL(TInt aFontFlags=EGulNoSymbolFonts,
                                  CGraphicsDevice* aGraphicsDevice=NULL,
                                  TInt aFontControlFlags=EGulFontControlAll);
	
    /**
     * Runs a dialog enabling an user to set tab position.
     *
     * @param aPageWidth Width of the page in twips.
     */
    IMPORT_C void RunTabsDialogL(TInt aPageWidth);
	
    /** 
     * Runs indents dialog.
     *
     * Changes the paragraph format to indent all text.
     *
     * @param aPageWidth Width of page in twips.
     */
    IMPORT_C void RunIndentsDialogL(TInt aPageWidth);
	
    /**
     * Sets the Graphics device to be used.
     *
     * @param aGraphicsDevice Wanted graphics device.
     */
    IMPORT_C void SetGraphicsDevice(CGraphicsDevice* aGraphicsDevice);
	
    /**
     * Runs the find dialog.
     * Enables an user to specify the text for which to search for. 
     */ 
    IMPORT_C void RunFindDialogL();
	
    /**
     * Runs the find dialog again. 
     */ 
    IMPORT_C void RunFindAgainDialogL();
	
    /** 
     * Runs the replace dialog.
     *
     * Enables the user to specify the text to be searched for and the
     * replacement for that text. Can replace single or multiple occurances.
     */ 
    IMPORT_C void RunReplaceDialogL();
	
    /**
     * Sets up the find model, the find list and the replace list ready
     * for find or replace operations.
     * 
     * @param aModel The find model to be used.
     * @param aFindList The find list to be used.
     * @param aReplaceList The replace list to be used.
     */
    IMPORT_C void InitFindL(SEdwinFindModel*& aModel,
                            CDesCArray*& aFindList,
                            CDesCArray*& aReplaceList);
	
    /**
     * Searches for text.
     * 
     * Returns @c ETrue if text is found.
     *
     * Used by @c RunFindDialogL(), @c RunFindAgainDialogL() and 
     * @c RunReplaceDialogL() methods.
     *
     * @return @c ETrue if the text is found @c EFalse otherwise.
     */ 
    IMPORT_C TBool DoFindL();
	
    /**
     * Runs a dialog enabling a user to set one of text alignment, spacing or
     * borders.
     *
     * Depending on the user's choice another dialog is run enabling them to 
     * set their requirements.
     *
     * @param aCommand User selected command. One of @c EEikCmdParaAlign, 
     *        @c EEikCmdParaSpacing or @c EEikCmdParaBorder. 
     */
    IMPORT_C void RunParaDialogsL(TInt aCommand);	
	
    /**
     * Runs a dialog enabling a user to do pagination.
     * 
     * @param aPrintSetup The printer setup.
     * @param aCharsPerPage Page table (array of characters per page).
     * @return @c ETrue if pagination is succesfull @c EFalse otherwise.
     */ 
    IMPORT_C TBool RunPaginateDialogL(CPrintSetup* aPrintSetup,
                                      CArrayFix<TInt>* aCharsPerPage);

public: // other functions

    /**
     * Gets the global text that is being edited.
     * 
     * @return The global text being edited.
     */
    IMPORT_C CGlobalText* GlobalText() const;
	
    /** 
     * Applies the paragraph formatting and updates the screen layout.
     *
     * The attributes which are set in the mask are read from @c aParaMask. 
     * The attributes which are not set in the mask are not changed. 
     * 
     * @param aParaFormat Contains the new paragraph formatting values 
     *        to apply.
     * @param aParaMask Bitmask specifying the paragraph format attributes 
     *        to change.
     */
    IMPORT_C void ApplyParaFormatL(CParaFormat* aParaFormat,
                                   TParaFormatMask& aParaMask);
	
    /**
     * Applies the character formatting and updates the screen layout. 
     * 
     * The attributes which are set in the mask are read from @c aCharFormat.
     * The attributes which are not set in the mask are not changed. 
     *
     * @param aCharFormat Contain the new character formatting values 
     *        to apply.
     * @param aCharMask Bitmask specifying the character format attributes 
     *        to change.
     */
    IMPORT_C void ApplyCharFormatL(TCharFormat& aCharFormat,
                                   TCharFormatMask& aCharMask);
	
    /** 
     * Toggles format in the current selection. 
     * 
     * For a global text editor the format change is applied globally.
     * For a rich text editor where there is no selection the format 
     * change is applied to the word at the current cursor position.
     *
     * @param aFontFlag The format attribute toggle. See the 
     *        @c TFontStyleFlags enum.
     */
    IMPORT_C void BoldItalicUnderlineEventL(TInt aFontFlag);
	
    /**
     * Update the buttons in the button group so that they reflect the 
     * formatting of the global text object.
     */ 
    IMPORT_C void UpdateButtonGroup();

public: // from CCoeControl

    /**
     * From @c CCoeControl.
     *
     * Completes construction of the global text editor from a resource file.
     * 
     * The editor's paragraph and character formatting is set to default 
     * values.
     *
     * See the @c GTXTED resource struct
     *
     * @param aReader A reader positioned for reading from a @c GTXTED 
     *        resource.
     */
    IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	
    /**
     * From @c CCoeControl.
     *
     * Handles key events.
     *
     * @param aKeyEvent The key code and modifier 
     * @param aType The type of the event: e.g. Key up.
     * @return @c EKeyWasConsumed if the event was handled.
     *         @c EKeyWasNotConsumed if the event was not handled.
     */
    IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,
                                         TEventCode aType);
    /**
     * From @c CCoeControl.
     *
     * Sets the editor ready for drawing.
     */ 
    IMPORT_C void ActivateL();
    
    /**
     * From @c CCoeControl.
     *
     * Handles pointer events.
     *
     * @param aPointerEvent Pointer to an event that is to be handled. 
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

public: // from CEikEdwin

    /**
     * From @c CEikEdwin.
     *
     * Gets the width of a line cursor in pixels.
     *
     * @return The width of the line cursor in pixels.  
     */ 
    IMPORT_C TInt LineCursorWidth() const;

protected:

    /**
     * Completes the second-phase construction of a @c CEikEdwin object. 
     * This protected function is called by @c ConstructL() and 
     * @c ConstructFromResourceL() after the @c Edwin’s size, flags and 
     * text limit have been set. Derived classes should call either this 
     * function or @c CEikEdwin’s @c ConstructL() or 
     * @c ConstructFromResourceL() functions during their construction 
     * before initialising their own members.
     */ 
    IMPORT_C void BaseConstructL();

protected: //from CCoeControl

    /**
     * From @c CCoeControl.
     *
     * Writes the internal state to the specified stream. Does nothing
     * in release mode. 
     * 
     * @param aWriteStream The stream to write to.
     */
    IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;

private: // from CoeControl

    IMPORT_C void Reserved_2();

private:

    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );

private: // from CEikEdwin

    IMPORT_C void Reserved_3();

private:

    void CheckDocumentNotEmptyL();
	
    void CreateFindModelL();
	
    void GetTextForFindL();

protected:

    /** 
     * Stores the object's global character formatting. 
     */
    CCharFormatLayer* iCharFormatLayer;
	
    /** 
     * Stores the object's global paragraph formatting. 
     */
    CParaFormatLayer* iParaFormatLayer;

private:

    CDesCArray* iFindList; 
	
    CDesCArray* iReplaceList;
	
    SEdwinFindModel* iFindModel;
	
    CEikDialogToolBar* iButGroup;
	
    TInt iLineCursorWidth;
	
    CFbsBitmap* iLineCursor;
	
    TInt iFontControlFlags;
	
    TInt iFontNameFlags;
	
    CGraphicsDevice* iGraphicsDevice;
    
    TInt iSpare[4];
	};


#endif  // __EIKGTED_H__

// enf of file
