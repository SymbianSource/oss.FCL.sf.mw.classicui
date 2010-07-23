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


#if !defined(__EIKRTED_H__)
#define __EIKRTED_H__

#if !defined(__EIKGTED_H__)
#include <eikgted.h>
#endif

#if !defined(__APPARC_H__)
#include <apparc.h>
#endif

#if !defined(__TXTMRTSR_H__)
#include <txtmrtsr.h>
#endif

#if !defined(__GDI_H__)
#include <gdi.h>
#endif

class CRichText;
class TResourceReader;
class TPictureHeader;
class CEikRubberBand;
class CBufStore;
class CStreamStore;
class CApaDoor;
class CEikParserManager;
class MEikRichTextEditorParserObserver;
class MParser;

/**
 * Rich text editor.
 * 
 * This is an edit window that supports rich text, including embedded objects
 * represented either by icons or glass doors. 
 *
 * @since Symbian 5.0
 */
class CEikRichTextEditor : public CEikGlobalTextEditor, 
                           public MApaEmbeddedDocObserver, 
                           public MRichTextStoreResolver, 
                           public MPictureFactory
	{

public:
    
    /** 
     * Identifies how an embedded object should be represented.
     *
     * One of these values is specified when the object is inserted.
     */ 
	enum TObjectFormat
		{
        /** The object is always represented by an icon */
		EAlwaysIconic,

        /** 
         * The object is represented by a glass door, if possible, or by icon,
         * if not.
         */
		EGlassIfPossible
		};

    /** 
     * Edit window attribute flags specific to the rich text editor.
     *
     * These may be specified during construction in addition to the values 
     * contained in the @c TFlags enum in class @c CEikEdwin.
     */
	enum // user flag
		{
        /** 
         * All embedded objects are represented by icon rather than 
         * glass doors. 
         */
        EShowAllPicturesAsIconic	=0x00100000,
		
        /**
         * The editor has no text parsers.
         *
         * Text parsers are used to recognise and tag special text strings,
         * e.g. URLs.
         */
        ENoTextParsers				=0x00200000,
        
        /**
         * When pasting text into the editor, the text is
         * stripped of all formatting.
         *
         * @since 3.2
         */
        EPasteAsPlainText           =0x00400000
		};

public:

    /**
     * C++ default constructor.
     */
    IMPORT_C CEikRichTextEditor();

    /**
     * C++ constructor.
     * 
     * @param aBorder Border for the rich text editor. 
     */ 
	IMPORT_C CEikRichTextEditor(const TGulBorder& aBorder);

    /**
     * Destructor.
     */ 
    IMPORT_C ~CEikRichTextEditor();

    /** 
     * By default Symbian 2nd phase constructor is private.
     *
     * Completes construction of the rich text editor.
     *
     * The editor's paragraph and character formatting are set to default
     * values, unless the @c CEikEdwin::EUserSuppliedText flag is specified 
     * in @c aEdwinFlags.
     *
     * @param aParent If not NULL, the editor's parent control. 
     *        If NULL, the editor has no parent.
     * @param aNumberOfLines The number of lines visible in the editor. 
     *        This controls the editor's height.
     * @param aTextLimit The maximum number of characters that can be entered
     *        into the editor.
     * @param aEdwinFlags Edit window attribute flags. 
     *        See @c CEikEdwin::TFlags().
     * @param aFontControlFlags = EGulFontControlAll Flags that specify which 
     *        font-related controls should not appear in font dialogs launched 
     *        from the edit window. For instance @c EGulFontControlBold removes 
     *        the bold checkbox control. The default shows all. For possible 
     *        values, see @c gulftflg.hrh.
     * @param aFontNameFlags = EGulNoSymbolFonts The font flags. These control 
     *        whether symbol and monospace fonts should be displayed in font
     *        dialogs launched from the edit window. For possible values, see 
     *        @c gulftflg.hrh.
     */
    IMPORT_C void ConstructL(const CCoeControl* aParent,
                             TInt aNumberOfLines,
                             TInt aTextLimit,
                             TInt aEdwinFlags,
                             TInt aFontControlFlags=EGulFontControlAll,
                             TInt aFontNameFlags=EGulNoSymbolFonts);
	
    /** 
     * Gets a pointer to the rich text object owned by the editor.
     *
     * @return Pointer to the rich text object.
     */
    IMPORT_C CRichText* RichText() const;
	
    /** 
     * Launches an insert object dialog (@c CEikInsertObjectDialog),
     * and inserts a default document of the application type selected 
     * by the user.
     * 
     * The object can be displayed either as a glass door, if supported, 
     * or as an icon, and the inserted object is opened for editing.
     *
     * Displays an info message and leaves if the editor's text limit 
     * has been reached.
     * 
     * @param aFormat Specifies whether the embedded document should be 
     *        displayed as an icon or as a glass door.
     */ 
    IMPORT_C void InsertObjectL(TObjectFormat aFormat);
	
    /** 
     * Launches an insert object dialog (@c CEikInsertObjectDialog),
     * and inserts a default document of the application type selected 
     * by the user.
     * 
     * The object is displayed as a glass door rather than as an icon, 
     * if supported and the inserted object is opened for editing.
     *
     * Displays an info message and leaves if the editor's text limit 
     * has been reached.
     *
     * Default is @c EGlassIfPossible.
     */
    IMPORT_C void InsertObjectL(); // defaults to EGlassIfPossible
	
    /** 
     * Creates and inserts a default document of the specified 
     * application type.
     * 
     * @c CApaProcess::AddNewDocumentL() is used to create the document.
     * 
     * The object can be displayed either as a glass door, if supported, 
     * or as an icon, and the inserted object is opened for editing.
     *
     * Displays an info message and leaves if no suitable application DLL 
     * can be found, or if the editor's text limit has been reached.
     *
     * @since Symbian 7.0
     * @param aAppDllName Filename of the application DLL.
     * @param aAppDllUid UID of the application. The default is @c KNullUid.
     * @param aFormat Specifies whether the embedded document should be 
     *        displayed as an icon or as a glass door.
     */
    IMPORT_C void InsertObjectL(const TDesC& aAppDllName,
                                TUid aAppDllUid,
                                TObjectFormat aFormat);
	
    /** 
     * Creates and inserts a new embedded object of the specified type.
     *
     * First, an attempt is made to find an extended picture factory that
     * supports the insertion of pictures of the specified type. If one is
     * not found, the function leaves; if one is found, the picture is inserted
     * at the cursor position.
     *
     * Displays an info message and leaves if the editor's text limit has
     * been reached.
     * 
     * @since Symbian 6.1
     * @param aPictureType The picture type.
     * @param aData The base address of the data. 
     * @leave KErrNotSupported No picture factory which supports the specified 
     *                         type is available in the control's @c Uikon 
     *                         environment.
     */
    IMPORT_C void InsertObjectL(TUid aPictureType,
                                CBase* aData);
	
    /** 
     * Re-edits the embedded object at the cursor position.
     *
     * If there is no embedded object at the cursor position, or if there is a 
     * selection, an info message is displayed.
     *
     * If there is a valid object at the cursor position, it is opened for 
     * editing (or for viewing if the editor is read-only).
     */
    IMPORT_C void ReEditObjectL();
	
    /** 
     * Gets the document position and checks whether there is an embedded 
     * object at the cursor position.
     *
     * If there is no embedded object at the cursor position, or if there 
     * is a selection, an info message is displayed.
     *
     * @return The document position of the embedded object, or 
     *         @c KErrNotFound if there is no embedded object at the cursor 
     *         position, or if there is a selection
     */
    IMPORT_C TInt ObjectCursorPos() const;
	
    /**
     * Tests whether there is an embedded object at the cursor position.
     *
     * If there is one, it is opened for editing (or for viewing if the editor
     * is read-only).
     *
     * @return @c ETrue if there is an embedded object at the cursor 
     *         position and it could be opened. @c EFalse if there is no 
     *         embedded object at the cursor position, or if the object has
     *         a NULL UID.
     */ 
    IMPORT_C TBool CheckForObjectL();
	
    /**
     * Launches a format object dialog (@c CEikFormatObjectDialog) if there 
     * is an embedded object at the cursor position, and the object supports 
     * being displayed as a glass door.
     *
     * If the object does not support being displayed as a glass door, an 
     * object information dialog (@c CEikObjectInfoDialog) is launched instead.
     *
     * If the embedded object's associated application cannot be found, an 
     * info message is displayed and the function leaves.
     *
     * The function has no effect if there is no embedded object at the cursor
     * position.
     */ 
    IMPORT_C void EditPictureFormatL();
	
    /**
     * Handles a change to the format of an embedded object, by updating the 
     * view, the scroll bars and reporting the event to its observers.
     *
     * There is no need to call this function after calling 
     * @c EditPictureFormatL().
     */
    IMPORT_C void PictureFormatChangedL();
	
    /**
     * Gets a pointer to the embedded object located at the specified position. 
     *
     * If the object is not in memory, the function loads it.  
     *
     * If the object's associated application cannot be found, an info message
     * is displayed and the function leaves.
     *
     * @param aDoor On return, the embedded document's wrapper object (icon or 
     *        glass door).
     * @param aDoc On return, the embedded document.
     * @param aDocPos The document position in the editor at which the embedded 
     *        object is located.
     */
    IMPORT_C void GetEmbeddedAppL(CApaDoor*& aDoor,
                                  CApaDocument*& aDoc,
                                  TInt aDocPos);
	
    /** 
     * Changes all embedded objects displayed as glass doors into temporarily 
     * iconic.
     * 
     * The function operates throughout the editor.
     *
     * Only needed when pictures are temporarily iconic. 
     *
     * Has no effect if there are no embedded objects in the editor or if the 
     * @c EShowAllPicturesAsIconic attribute flag was set during construction.
     */
    IMPORT_C void UpdatePictureFormatL(); 
	
    /**
     * Changes all embedded objects displayed as glass doors into temporarily 
     * iconic.
     * 
     * The function operates over a specified range of characters.
     *
     * Has no effect if there are no embedded objects in the editor or if the 
     * @c EShowAllPicturesAsIconic attribute flag was set during construction.
     *
     * Only needed when pictures are temporarily iconic.
     *
     * @param aStartPos The start position.
     * @param aLength The number of characters, beginning at @c aStartPos over 
     *        which the function operates.
     */
    IMPORT_C void UpdatePictureFormatL(TInt aStartPos,TInt aLength); 
	
    /** 
     * Changes the size of the icons used to represent embedded objects.
     *
     * Any existing iconic doors can be updated to the new size by calling 
     * @c UpdatePictureSizeL().
     *
     * @param aSize The new iconic door size in twips.
     */ 
    IMPORT_C void SetDefaultIconicDoorSize(const TSize& aSize); 
	
    /** 
     * Gets the size of iconic doors.
     * 
     * @return The size of iconic doors. 
     */ 
    IMPORT_C const TSize& DefaultIconicDoorSize() const;
	
    /** 
     * Changes the size of all icons representing embedded objects to the 
     * default iconic door size.
     *
     * Also updates any objects currently displayed as glass doors, so that
     * if displayed as icons, they will use the correct size. 
     *
     * The function operates throughout the editor.
     */
    IMPORT_C void UpdatePictureSizeL();
	
    /**
     * Changes the size of all icons representing embedded objects to the 
     * default iconic door size.
     *
     * Also updates any objects currently displayed as glass doors, so that 
     * if displayed as icons, they will use the correct size. 
     *
     * The function operates over a specified range of characters.
     *
     * @param aStartPos The start position.
     * @param aLength The number of characters, beginning at @c aStartPos over
     *        which the function operates.
     */
    IMPORT_C void UpdatePictureSizeL(TInt aStartPos,TInt aLength);
	
    /** 
     * Sets a parser observer.
     *
     * If the @c CEikEdwin::ENoTextParsers attribute flag was specified on 
     * construction, this function has no effect.
     *
     * Its @c HandleCursorOverParserL() function is called when the cursor is 
     * positioned over text that has been tagged by the parser, for instance 
     * a URL.
     *
     * @param aObserver The parser observer.
     */ 
    IMPORT_C void SetParserObserver(
                    MEikRichTextEditorParserObserver* aObserver);
    
    /**
     * Activate/Disable phone number grouping.
     *
     * @param aEnable @c ETrue if phone number grouping is to be activated,
     *        @c EFalse otherwise.
     */ 
    IMPORT_C void SetPhoneNumberGrouping( TBool aEnable );

public: // from CCoeControl

    /** 
     * From @c CCoeControl.
     * 
     * Handles key events.
     *
     * Has no effect (apart from returning @c EKeyWasConsumed) if the 
     * @c CEikEdwin::EDisplayOnly attribute flag was specified on construction.
     *
     * Handles rich text-specific hot keys, for instance to insert an object; 
     * otherwise calls @c CEikGlobalTextEditor::OfferKeyEventL(). 
     *
     * @param aKeyEvent The key event.
     * @param aType The type of the event. The editor only consumes events of 
     *        type @c EEventKey.
     * @return Indicates whether or not the editor consumed the 
     *         key event.
     */
    IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	
    /**
     * From @c CCoeControl.
     * 
     * Handles pointer events inside the editor.
     *
     * Has no effect if the @c CEikEdwin::EDisplayOnly attribute flag was 
     * specified on construction.
     * 
     * @param aPointerEvent The pointer event to be handled.
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	
    /** 
     * From @c CCoeControl.
     *
     * Completes the construction of the rich text editor from a resource file.
     *
     * The editor's paragraph and character formatting are set to default 
     * values, unless the @c CEikEdwin::EUserSuppliedText flag is specified in 
     * the resource.
     *
     * @param aReader A resource reader positioned for reading from an 
     *        RTXTED resource.
     */
    IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	
    /** 
     * From @c CCoeControl. 
     * 
     * Activates the editor so that it is ready for use.
     *
     * For instance, the text view is created, the editor is set to observe its
     * rich text object, the editor's parser manager is set up, which handles
     * the changes that occur when the cursor is moved over tagged text
     * (for instance a URL), and all embedded objects are set to be displayed
     * as icons, of the default size.
     */ 
    IMPORT_C void ActivateL();

private:

    /**
    * From CAknControl.
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );

public: // from CEikEdwin

    /** 
     * From @c CEikEdwin.
     * 
     * Copies the contents of one text object into another.
     *
     * @param[in] aInText The rich text object to copy.
     * @param[out] aOutText On return, contains a copy of @c aInText.
     * @panic 26 In debug mode, if either @c aInText or @c aOutText is @c NULL.
     */ 
    IMPORT_C void CopyDocumentContentL(CGlobalText& aInText,CGlobalText& aOutText);

protected:

    /** 
     * Internal flags used for indicating operations. 
     */
    enum // internal flags
		{
        /** Crop from left. */ 
        ECropFromLeft			=0x00010000,
		
        /** Crop from right. */
        ECropFromRight			=0x00020000,
      
        /** Crop from top. */
        ECropFromTop			=0x00040000,

        /** Crop from bottom. */ 
        ECropFromBottom			=0x00080000,

        /** Object is being re-edited. */
        EReEditingObject		=0x00100000
		};

protected: // from CCoeControl

    /** 
     * From @c CCoeControl.
     *
     * Writes the internal state to the specified stream.
     * 
     * @param aWriteStream Target stream.
     */
    IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;

protected: // from MEditObserver

    /** 
     * From @c MEditObserver. 
     * 
     * This member is internal an not meant to be used. 
     *
     * @param aStartEdit Start position for editing.
     * @param aEditLength The length of the edited object.
     */
    IMPORT_C void EditObserver(TInt aStartEdit,TInt aEditLength);

private: // from CoeControl

    IMPORT_C void Draw(const TRect& aRect) const;

    IMPORT_C void Reserved_2();

private: // from CEikEdwin

    IMPORT_C void HandleTextPastedL(TInt aStartPos,TInt& aLength);
    IMPORT_C void Reserved_3();

private: // from MApaEmbeddedDocObserver

    IMPORT_C void NotifyExit(TExitMode aMode);

private: // from MRichTextStoreResolver

    IMPORT_C const CStreamStore& StreamStoreL(TInt aPos) const;

private: // from MPictureFactory

    IMPORT_C void NewPictureL(TPictureHeader& aHdr,const CStreamStore& aDeferredPictureStore) const;

private:

    void CommonConstructL();
	
    static TInt InsertEmbeddedDocL(TAny *aThis);
	
    static TInt DeleteEmbeddedDoc(TAny *aThis);
	
    static TInt UpdateEmbeddedDocL(TAny* aThis);

    static TInt TryDeleteEmbeddedDocL(TAny *aThis);
	
    void InsertPictureL(const TPictureHeader& aPictureHeader);
	
    void DoInsertPictureL(TBool& aFormatHasChanged,const TPictureHeader& aPictureHeader);
	
    void DoReEditObjectL(TInt aDocPos);
	
    void RoomForObjectL();
	
    void InsertObjectL(CApaDocument* aDoc,TObjectFormat aFormat);
	
    void SetTextObserver(CRichText& aText);
	
    inline void DoReportEdwinEventL(MEikEdwinObserver::TEdwinEvent aEventType);

protected:

    /** 
     * Default size of iconic door.
     */
    TSize iDefaultIconicDoorSize;

private:

    TPictureHeader iEmbeddedDoc;

    CIdle* iEmbeddedDocUpdate;
	
    CBufStore* iBufStore;
	
    CEikParserManager* iParserManager;

private:

    friend class CEikParserManager;

public: // new methods

    /**
     * Force everything to be parsed.
     */ 
    IMPORT_C void RefreshParsersL();
	
    };

class MEikRichTextEditorParserObserver
	{
public:
	virtual void HandleCursorOverParserL(const TDesC& aDoItText)=0;
	};

inline void CEikRichTextEditor::DoReportEdwinEventL(MEikEdwinObserver::TEdwinEvent aEventType)
	{ReportEdwinEventL(aEventType);}

#endif  // __EIKRTED_H__

// End of file
