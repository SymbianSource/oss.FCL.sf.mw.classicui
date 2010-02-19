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

 
#if !defined(__EIKEDWIN_H__)
#define __EIKEDWIN_H__

#include <s32std.h>
#include <gdi.h>
#include <txtetext.h>
#include <medobsrv.h>
#include <gulutil.h>
#include <fepbase.h>
#include <frmvis.h>
#include <frmtview.h>
#include <uikon.hrh>
#include <eikon.hrh>
#include <eikbctrl.h>
#include <eikedwob.h>
#include <eiksbfrm.h>
#include <eikccpu.h>
#include <eiklay.h>
#include <lafmain.h>
#include <AknPictographDrawerInterface.h>
#include <babitflags.h>
#include <centralrepository.h>          // class CCenRepNotifyHandler;
#include <cenrepnotifyhandler.h>        // class CRepository;

class CGlobalText;
class CParaFormatLayer;
class CCharFormatLayer;
class MLayDoc;
class CEikEdwinFepSupport;
class CLafEdwinCustomDrawBase;
class CClipboard;
class CAknEdwinFormAccessor;
class CAknEdwinState;
class CAknInputPolicyManager;
class CFormCursorModifier;
class CTextView;
class MAknsControlContext;
class CAknEdwinDrawingModifier;
class CAknEdwinFormExtendedInterfaceProvider;
class CAknPhoneNumberInlineTextSource;
class CAknNoMatchesIndicatorInlineTextSource;
class CAknInlineTextSource;
class CAknPictographInterface;
class CAknExtendedInputCapabilities;
class CAknPointerEventSuppressor;
class CSmileyManager;
class CSmileyCustomWrap;
class CAknEdwinPhysicsHandler;
class CEdwinAsyncFormat;

// Forward declaration of now removed (Series 60 2.0) custom drawer class for CEikEdwin
class CEikAvkonCustomDraw;

// Forward declaration of now removed (Series 60 2.0) custom drawer class for CEikEdwin
class CEikAvkonCustomDraw;

// For construction of Rich Text - based custom formatters
class CRichText;

enum TReplaceOption
	{
	ENoReplace,
	EReplaceOnce,
	EReplaceAll,
	EReplaceSkip
	};

/**
 * This describes the features of a
 * search-and-replace operation on a CEikEdwin.
 * 
 * See CEikEdwin::ReplaceL().
 */
struct SEdwinFindModel
	{
	/** Flags for the search (see CEikEdwin::TFindFlags) */
	TInt iFlags; // TEdwinFindFlags
	/** Text to search for. */
	TBuf<EEikEdwinFindStringMaxLen> iText;
	/** Text to replace it with. */
	TBuf<EEikEdwinFindStringMaxLen> iReplaceText;
	/** Replace options. */
	TReplaceOption iReplaceOption;
	};

/**
 * Styles for highlighting. See SetHighlightStyleL().
 */
enum TAknsHighlightStyle
    {
    /** Normal highlighting. */
    EEikEdwinHighlightNormal = 0,
    /** Link highlighting. */
    EEikEdwinHighlightLink
    };

// inline utility to handle RGB values (set / unset)      

class SAknRgb
    {
// data (private)    
    TRgb iValue;
    TBool iIsSet;
public: // utilities   
    SAknRgb():iIsSet(EFalse){}
    TRgb Value(){return iValue;}
    SAknRgb& operator=(TRgb aRgb)
        {
        iValue = aRgb;
        iIsSet = ETrue;
        return *this;
        }
    TBool IsSet(){return iIsSet;}
    };    

/** 
 * Base class for controls that display and allow manipulation of text.
 *
 * The properties of a particular Edwin object can be set using bitwise flags, 
 * which are defined in member enums (see @c TFlags for example).
 *
 * Edwins support Front End Processors, and so are a highly effective way of 
 * getting textual data from the user. The text currently being composed by the
 * user is called the composition text.
 */
class CEikEdwin : public CEikBorderedControl, 
                  public MEikScrollBarObserver, 
                  public CTextView::MObserver, 
                  public MEditObserver, 
                  public MEikCcpuEditor
	{

private:

    class CUndoBuffer;
    NONSHARABLE_CLASS(CEikEdwinExtension) : public CBase, MCenRepNotifyHandlerCallback
        {
    public:
        /**
         * Allocates and constructs a CEikEdwinExtension.
         *
         * @param aEdwin Pointer to the CEikEdwin creating the extension.
         * @return A newly constructed edwin extension.
         */
		static CEikEdwinExtension* NewL(CEikEdwin* aEdwin);
		
		/**
		 * Destructor.
		 */
		~CEikEdwinExtension();
		
		/**
		 * Gets the form accessor.
		 *
		 * @return The form accessor.
		 */
		IMPORT_C CAknEdwinFormAccessor* FormAccessor() const;
		
		/**
		 * Sets the form accessor.
		 *
		 * @param aFormAccessor The form accessor.
		 */
		IMPORT_C void SetFormAccessor(CAknEdwinFormAccessor* aFormAccessor);
		
		/**
		 * Sets the CIdle object to update scroll bar.
		 *
		 * @param The CIdle object to perform scroll bar updating.
		 */
		IMPORT_C void SetScrollBarSetter(CIdle* aScrollBarSetter);
		
		/**
		 * Gets the CIdle object which updates scroll bar.
		 *
		 * @return The CIdle object used to perform scroll bar updating.
		 */
		IMPORT_C CIdle* ScrollBarSetter();
		
		/**
		 * Gets the custom wrapper.
		 *
		 * @return The custom wrapper.
		 */
		IMPORT_C const TAvkonEditorCustomWrap& TextWrapper();

		// the following two methods are deprecated
        IMPORT_C CFormCursorModifier* FormCursorModifier() const;
        
        /**
        * Store a locally stored (but externally set) Skins background control context.
        *
        * @param aBackgroundControlContext   Control context to store. Not owned. Can be NULL.
        */
        void SetSkinBackgroundControlContext( MAknsControlContext* aBackgroundControlContext );
        
        /**
        * Access to locally stored Skins background control context.
        * 
        * @return Pointer to locally stored control context
        */
        
        MAknsControlContext* SkinBackgroundControlContext() const;
        
        /**
        * This returns a flag that records whether the background context has ever been 
        * set by API.
        *
        * @return   EFalse iff control context has never been set.
        */
        TBool SkinBackgroundControlContextHasBeenSet() const;

        /**
        * Stores the alignment value.
        *
        * @param aAlignment   Editor alignment to be stored.
        */
        void SetAlignment(TInt aAlignment);

        /**
        * Returns the stored alignment value.
        *
        * @return Value of the current editor alignment.
        */
        TInt CurrentAlignment() const;

        /**
        * Sets pictograph animation callback.
        */
        void SetPictoCallBack( TCallBack& aCallBack );

        /**
        * Sets pictograph animation callback.
        */
        const TCallBack& PictoCallBack() const;

        /**
        * Creates the CAknFormExtendedInterfaceProvider object if it does not exist.
        */
        void CreateFormExtendedInterfaceProviderIfNeededL();

        /**
        * Access to Form's extended interface provider.
        */
        CAknEdwinFormExtendedInterfaceProvider* FormExtendedInferfaceProvider() const;

        /**
        * Create a custom formatter for pure phone number content.
        *
        * Calls CreateFormExtendedInterfaceProviderIfNeededL to ensure that there is an
        * ExtendedInterfaceProvider object built.
        *
        * @param    aTextLayout     Reference to the CTextLayout object used for this editor.
        *           aText           CPlainText object reference for the text used in the editor.
        */
        void CreatePurePhoneNumberFormatterL( CTextLayout& aTextLayout, const CPlainText& aText);

        /**
        * Create a custom formatter for pure phone number content.
        *
        * Calls CreateFormExtendedInterfaceProviderIfNeededL to ensure that there is an
        * ExtendedInterfaceProvider object built.
        *
        * @param    aTextLayout     Reference to the CTextLayout object used for this editor
        */
        void CreateNoMatchesIndicatorFormatterL( CTextLayout& aTextLayout );

        /**
        * Create a custom formatter for rich text editor with general content. Phone numbers are
        * recognized using an internal parser and formatted with the number grouping engine
        *
        * Calls CreateFormExtendedInterfaceProviderIfNeededL to ensure that there is an
        * ExtendedInterfaceProvider object built.
        *
        * @param    aTextLayout     Reference to the CTextLayout object used for this editor
        */
        void CreateRichTextPhoneNumberFormatterL( CTextLayout& aTextLayout, const CRichText& aText );

        /**
        * This allows the caller to access the single inline text interface that will be seen
        * by Tagma.  All installed inline text source classes are held behind this single interface
        * 
        * @return   pointer to the inline text source object that will be provided to Tagma
        *           Null is returned if none is installed.
        */
        CAknInlineTextSource* InlineTextSource() const;

        /**
        * Returns pointer to pictograph interface.
        *
        * @return Pointer to pictograph interface. The value can be NULL if pictographs are not supported.
        */
        CAknPictographInterface* PictographInterface() const;
        
        /**
        * Used for suppressing all editor's background drawing.
        */
        void SetSuppressBackgroundDrawing( TBool aSuppress );
        
        /**
        * Tests if the background drawing is suppressed.
        */
        TBool IsBackgroundDrawingSuppressed() const;

        /**
        * Returns the value of ClearDirection
        *
        * @return value of current ClearDirection
        */
        TInt ClearDirection() const;
        
        /**
         * Enables kinetic scrolling.
         */
        void EnableKineticScrollingL();

        /**
         * Enables physics.
         */
        void EnablePhysicsL();

        /**
         * Initializes physics.
         */
        void InitPhysicsL();
        
    public: // from MCenRepNotifyHandlerCallback
        void HandleNotifyInt(TUint32 aId, TInt aNewValue);

    private:

        CEikEdwinExtension();
        void ConstructL(CEikEdwin* aEdwin);

    private:

        enum TFlagIndices
            {
            ESkinBackgroundControlContextHasBeenSetIndex = 0,
            ESuppressBackgroundDrawing,
            EKineticScrollingEnabled
            };
        class TAknEdwinPictographDrawer : public MAknPictographAnimatorCallBack
            {
            private: // From MAknPictographAnimatorCallBack
                void DrawPictographArea();
            };        
        
	private:

		CIdle* iSetScrollBar;
		TAvkonEditorCustomWrap iTextWrapper;
		CAknEdwinFormAccessor* iFormAccessor;
        CFormCursorModifier* iFormCursorModifier;
        MAknsControlContext* iSkinBackgroundControlContext;
        TBitFlags iFlags;
        TInt iAlignment;
        TCallBack iPictoCallBack;       
        CAknEdwinFormExtendedInterfaceProvider* iFormExtendedInterfaceProvider; // Owned
        CAknInlineTextSource* iPhoneNumberFormatter;                 // Not owned
        CAknNoMatchesIndicatorInlineTextSource* iNoMatchesIndicatorFormatter;   // Not owned
        TAknEdwinPictographDrawer iPictographDrawer;
        CAknPictographInterface* iPictographInterface;
        // For clear direction.
        CRepository* iCenRep;                           // Owned
        CCenRepNotifyHandler* iCenRepNotifyHandler;     // Owned
        TInt iClearDirection;                           // Value of ClearDirection
     public:

        TInt iSkinIdForText;
        TAknsHighlightStyle iSkinHighlightStyle;
        SAknRgb iEditorBackgroundColor;
        TInt iUpperFullFormattingLength;
        CAknExtendedInputCapabilities* iExtendedInputCapabilities;
        TRect iTextLinesRect;
        TRect iScrollRect;
        TInt iTempCursorPos;
        TInt iTempAnchorPos;
        TInt iTempSelect;
        CAknPointerEventSuppressor* iPtSuppressor;
        TBool iDragging;
        TInt iRecordCursor;
        TBool iRecordScroll;
        /**
        * @c iDestroyedPtr is used for the object destruction check.
        * If it has non-null value, the destruction check is turned on, and
        * the value points to a local boolean variable that keeps the destroyed state.
        */
        TBool* iDestroyedPtr;
        enum TDrawState
            {
            ENotDraw = 0,
            EDrawn,
            EDrawing
            };
        TInt iDrawInvoked;
        TInt iThumbPos;
        // own
        CSmileyManager* iSmiley;        
        CSmileyCustomWrap* iSmileyWrap;
        TBool iInlineEditing;
        TBool iDisableConvertInFormat;
        TCursorSelection iVisibleRange;
        CEdwinAsyncFormat* iAsyncFormat;
        
        /**
         * Pointer to CEikEdwin.
         * Not own.
         */
        CEikEdwin* iEdwin;
        
        /**
         * Scrolled offset if using rate scroll way.
         */
        TInt iScrolledDelta;

        /**
         * If ETrue, uses rate scroll. Otherwise uses original way.
    	 */
        TBool iUseRateScroll;

        /**
         * Used with each step of dragging scrollbar to record
         * the thumb position before dragging action
         */
        TInt iScrollbarPosition;

       /**
         * Physics handler. Used only when physics feature is enabled.
         * Own.
         */
        CAknEdwinPhysicsHandler* iPhysicsHandler;
        
        /**
         * Content has moved down so that empty space
         * above the editor content is visible.
         */
        TBool iStartBorderExceeded;
        
        /**
         * Content has moved up so that empty space
         * below the editor content is visible.
         */
        TBool iEndBorderExceeded;
        
        /**
         * Amount of pixels out of border. In practice width
         * of empty space above or below editor content.
         */
        TInt iPixelsOutOfBorder;

        /**
         * If ETrue, text cursor was visible before drag or flick started.
         * Used to store cursor state so that it is possible to enable cursor
         * again when dragging, flicking or bounce stops.
         */
        TBool iCursorWasVisible;
        
        /**
         * If ETrue, ongoing scrolling is caused by moving scrollbar thumb.
         */
        TBool iScrolledByScrollBar;
        };

public:

    /**
     * The following flags may be combined with a bitwise OR to form the 
     * @c aEdwinFlags argument to @c ConstructL(TInt, ...) or the flags field 
     * of an EDWIN resource structure run through @c ConstructFromResourceL().
     *
     * These flags are duplicated in @c uikon.hrh (see @c EEikEdwinKeepDocument
     * etc.)
     */
    enum TFlags
        { // user flags
        /**  */
    	EZeroEnumValue			=0x00000000, 

        /** 
         * If set, @c CEikEdwin does not destroy its content on destruction. 
         */
    	EKeepDocument			=0x00000001,

        /** 
         * If set, the content buffer uses segmented storage (see 
         * @c CEditableText::ESegmentedStorage).
         */
    	ESegmentedStorage		=0x00000002,

        /**
         * The size specified in the resource used to construct the object is 
         * given in pixels, not character widths.
         */
    	EWidthInPixels			=0x00000004,

        /**
         * No automatic selection takes place. Normally the entire text is 
         * selected whenever the Edwin is created, resized or has its text 
         * set as one operation.
         */
    	ENoAutoSelection		=0x00000008,

        /**
         * If set, then whenever the control is activated the cursor is 
         * moved to the end of the text.
         */
    	EJustAutoCurEnd			=0x00000010,

        /**
         * Does not wrap the text being edited.
         */
    	ENoWrap					=0x00000020,

        /**
         * Uses a line cursor instead of a block cursor.
         */
    	ELineCursor				=0x00000040, 

        /**
         * Does not perform horizontal scrolling.
         */
    	ENoHorizScrolling		=0x00000080, 

        /**
         * If set, scroll bars required to edit long documents appear inside 
         * the Edwin. This reduces the area used to display the Edwin.
         * 
         * If not set, scroll bars appear outside the Edwin.
         */
    	EInclusiveSizeFixed		=0x00000100, 

        /**
         * Sets the Edwin’s height according to the number of lines of text 
         * supplied by the user.
         */
    	EUserSuppliedText		=0x00000200,

        /**
         * The Edwin is a window-owning control.
         */
    	EOwnsWindow				=0x00000400,

        /**
         * The Edwin does not respond to input at all.
         */
    	EDisplayOnly			=0x00000800,

        /**
         * Does not hide the selection if the Edwin loses focus.
         */
    	EAlwaysShowSelection	=0x00001000,

        /**
         * The Edwin is read-only so users cannot add text to any document it 
         * displays.
         */
    	EReadOnly				=0x00002000,

        /**
         * If set, no special attempt will be made to delete the embedded pictures cleanly.
         * 
         * This flag does not apply to Edwins which do not edit rich text.
         */
    	EAllowPictures			=0x00004000,

        /**
         * The Edwin supports undo operations.
         */
    	EAllowUndo				=0x00008000,

        /**
         * Does not allow line or paragraph breaks in the text being edited.
         */
    	ENoLineOrParaBreaks		=0x00010000,

        /**
         * Allows only ASCII characters.
         */
    	EOnlyASCIIChars			=0x00020000,

        /**
         * The Edwin is resizable.
         */
    	EResizable				=0x00040000,

        /**
         * The Edwin ignores the virtual cursor.
         */
    	EIgnoreVirtualCursor	=0x00080000,

        /**
         * No custom draw is done.
         */
    	ENoCustomDraw			=0x01000000,

        /**
         * Changes layout to Avkon style.
         */
    	EAvkonEditor			=0x02000000,

        /**
         * Hides cursor.
         */
    	EAvkonDisableCursor		=0x04000000,

        /**
         * Changes text editor to non-editable mode.
         */
    	EAvkonNotEditable		=0x08000000, 

        /**
         * Sets the @c Avkon wrapping rules ON.
         */
    	EEdwinAlternativeWrapping = 0x10000000,
    	
    	/**
    	 * Enables tab key handling
    	 */
    	EAvkonTabsEnabled = 0x20000000,
    	
    	/**
    	 * Disable VKB input
    	 */ 
    	EAvkonDisableVKB = 0x40000000,
    	
    	/**
    	 * Enable Smiley Support
    	 */ 
    	EAvkonEnableSmileySupport = 0x80000000
    	};

    /**
     * Defines the possible commands for @c ClipboardL().
     */
    enum TClipboardFunc
		{
        /** Do nothing. */
		ENoClipboard,

        /** Cut. */
		ECut,

        /** Copy. */
		ECopy,

        /** Paste. */
		EPaste
		};

    /**
     * The following flags may be ORed together for text searches (see 
     * @c FindL() for example).
     */
	enum TFindFlags
		{
        /** Search progresses up the screen. */
		EFindDirectionUp	=0x01,

        /** Only whole-word matches count. */
		EFindWholeWord		=0x02,

        /** Search is case-sensitive. */
		EFindCaseSensitive	=0x04,

        /** Finds again. */
		EFindAgain			=0x08,

        /** Does not display a busy message. */
		ENoBusyMessage		=0x10,

        /**  */
		EReadOnlyFile		=0x20 // New for CKon
		};

    /**
     * When content is supplied to an Edwin using @c SetDocumentContentL(), 
     * this defines whether the new content is added to or has replaced the 
     * existing content.
     */
	enum TSetContent
		{
        /** Replaces the Edwin’s existing content. */
		EUseText,

        /** Copies the supplied content into the existing content. */
		ECopyText
		};

    /**
     * Specifies whether the Edwin owns the document it is being used to edit.
     *
     * If the Edwin owns the document, the document object is destroyed on 
     * destruction.
     */
	enum TOwnershipType
		{
        /** Document is owned by the Edwin. */
		EOwnsText,

        /** Document is owned by some other object. */
		EDoesNotOwnText
		};

    // order of hotkeys defined in resource file.  Not all applicable to plain 
    // text editors
    /**
     * Enumerates the hotkeys that are defined an @c r_eik_edwin_ctrl_hotkeys 
     * or @c r_eik_edwin_shift_ctrl_hotkeys resource.
     *
     * Not all are applicable to plain text editors.
     */
	enum TEdwinHotKeys 
		{
        /** Cut. */
		EHotKeyCut,

        /** Copy. */
		EHotKeyCopy,

        /** Paste. */
		EHotKeyPaste,

        /** Undo. */
		EHotKeyUndo,

        /** Find. */
        EHotKeyFind,

        /** Insert a character. */
		EHotKeyInsertChar,

        /** Bold. */
		EHotKeyBold,

        /** Italic. */
		EHotKeyItalic,

        /** Underline. */
		EHotKeyUnderline,

        /** Font. */
		EHotKeyFont,

        /** Insert an object. */
		EHotKeyInsertObject,

        /** Edit an object. */
		EHotKeyEditObject,

        /** Format an object. */
		EHotKeyFormatObject
		};

public: // construction and destruction

    /**
     * Destructor.
     *
     * Deletes objects and frees resources owned by this object. The Edwin’s 
     * editable text is freed if the @c EKeepDocument flag is not set.
     */
    IMPORT_C ~CEikEdwin();

    /**
     * C++ default constructor.
     *
     * Creates a new @c Edwin, FEP support for the new editor will not be 
     * present if there is insufficient memory.
     */
	IMPORT_C CEikEdwin();

    /**
     * Constructor. 
     *
     * Creates a new @c Edwin, specifying the border to use. As with the default
     * constructor, FEP support for the new editor will not be present if there
     * is insufficient memory. S60 Edwin does not support / draw any borders.
     *
     * @param aBorder The Edwin border.
     */
	IMPORT_C CEikEdwin(const TGulBorder& aBorder);
    
    /**
     * Handles Symbian 2nd phase construction.
     * Completes construction of a new @c Edwin, initialising its heap-stored 
     * members from the supplied arguments.
     *
     * @param aEdwinFlags Bitwise ORed combination of flags from @c TFlags. 
              Default value is 0.
     * @param aWidthInChars Specifies the width for the Edwin, in characters or
              pixels: see the @c EWidthInPixels flag. Default value is 0.
     * @param aTextLimit Maximum length for the text to present as editable. 
              Default value is 0.
     * @param aNumberOfLines Height for the Edwin, in lines. Default value 
              is 0.
     */
	IMPORT_C void ConstructL(TInt aEdwinFlags=0,
                             TInt aWidthInChars=0,
                             TInt aTextLimit=0,
                             TInt aNumberOfLines=0);
	
    /**
     * Sets the Edwin observer. The Edwin’s observer will be called back with 
     * control events associated with the Edwin.
     *
     * @param aEdwinObserver New observer.
     */
    IMPORT_C void SetEdwinObserver(MEikEdwinObserver* aEdwinObserver);
	
    /**
     * Adds an observer of standard Edwin events to the list of observers, 
     * creating the list if necessary. May be called any number of times and is
     * independent of calls to @c SetEdwinObserver.
     *
     * @param aEdwinObserver The observer to add to the list of observers.
     */
    IMPORT_C void AddEdwinObserverL(MEikEdwinObserver* aEdwinObserver);
	
    /**
     * Removes the specified observer from the list of observers. Does nothing 
     * if aEdwinObserver is not an observer.
     * 
     * @param aEdwinObserver The observer to remove from the list of observers.
     */
    IMPORT_C void RemoveEdwinObserver(MEikEdwinObserver* aEdwinObserver);
	
    /**
     * Creates the containing window for the Edwin if it does not already have one. 
     */
    IMPORT_C void SetContainerWindowL();
	
    /**
     * Sets the Edwin’s editable content. Before calling this function you must
     * get the @c iText pointer as @c iText is replaced by @c aText. You must 
     * also free the memory by deleting the previous @c iText contents.
     *
     * @param aText New value for the content.
     * @param aContent Specifies whether to use @c aText itself, or to copy its
     *        content. Default value is @c CEikEdwin::ECopyText.
     */
    IMPORT_C void SetDocumentContentL(CGlobalText& aText,
                        TSetContent aContent=CEikEdwin::ECopyText);

public: // from CCoeControl
    
    /**
     * From @c CCoeControl.
     *
     * Handles key events. 
     * 
     * @param aKeyEvent The key event.
     * @param aType The type of the event: @c EEventKeyDown, @c EEventKeyUp 
     *        or @c EEventKey.
     * @return A suitable response code.
     */
    IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,
                                         TEventCode aType);
	
    /**
     * From @c CCoeControl.
     *
     * Responds to focus-changed events.
     *
     * @param aDrawNow Not used.
     */
    IMPORT_C void FocusChanged(TDrawNow aDrawNow);
	
    /**
     * From @c CCoeControl.
     *
     * Sets the Edwin as ready for drawing.
     *
     * @leave KErrNoMemory.
     */
    IMPORT_C void ActivateL();
	
    /**
     * From @c CCoeControl.
     *
     * Completes the construction of a new @c Edwin. This function initialises
     * the heap-stored members from an @c EDWIN resource.
     *
     * @param aReader A reader positioned for reading from an @c EDWIN resource.
     */
    IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	
    /**
     * From @c CCoeControl.
     *
     * Handles pointer events.
     *
     * @param aPointerEvent Pointer event to respond to.
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	
    /**
     * From @c CCoeControl.
     *
     * Gets the minimum size of this Edwin for automatic-layout control 
     * contexts such as dialogs.
     *
     * @return Minimum size for the control.
     */
    IMPORT_C TSize MinimumSize();
	
    /**
     * From @c CCoeControl.
     *
     * Draws the control on request. 
     *
     * @param aRect If supplied, the rectangle in which to draw the Edwin.
     */
    IMPORT_C void Draw(const TRect& aRect) const;
	
    /**
     * From @c CCoeControl.
     *
     * Dims or undims the Edwin.
     *
     * @param aDimmed @c ETrue to dim the Edwin. @c EFalse to undim the Edwin.
     */
    IMPORT_C void SetDimmed(TBool aDimmed);
	
    /**
     * From @c CCoeControl. 
     *
     * Sets the containing window for the Edwin by copying it from the specified
     * parent. Also copies a control context from @c aParent if one has not been
     * previously set.
     *
     *@param aParent The control to set as this Edwin’s parent.
     */
    IMPORT_C void SetContainerWindowL(const CCoeControl& aParent);
	
    /**
     * From @c CCoeControl.
     * 
     * Gets the list of logical colours employed in the drawing of the control,
     * paired with an explanation of how they are used. Appends the list to 
     * @c aColorUseList.
     *
     * @param[out] aColorUseList The list of logical colours.
     */
    IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& 
                     aColorUseList) const; // not available before Release 005u
	
    // not available before Release 005u    
    /**
     * From @c CCoeControl.
     *
     * Handles a change to Edwin’s resources which are shared across the 
     * environment. Colours or fonts for example.
     *
     * @param aType The type of resource that was changed.
     */
    IMPORT_C virtual void HandleResourceChange(TInt aType);
    
    /**
     * From @c CCoeControl.
     *
     * Access to the input capabilities of the edwin.
     *
     * If this function is overrided in a subclass, the subclass should
     * obtain this class' InputCapabilities' object provider through
     * TCoeInputCapabilities::ObjectProvider() and set that as a part of
     * the subclass' InputCapabilities object provider chain to ensure
     * maximum functionality.
     *
     * @return The Edwin input capabilities.
     */
    IMPORT_C TCoeInputCapabilities InputCapabilities() const;
    
    /**
     * From @c CCoeControl.
     *
     * This method sets the input capabilities of the edwin. Ownership of the 
     * T-class is not transferred.
     *
     * @param aInputCapabilities	Reference to an input capabilities object 
     *        on the heap.
     * @leave KErrNoMemory Edwin FEB support object is not created.
     */
    IMPORT_C void SetInputCapabilitiesL(const TCoeInputCapabilities& 
                                        aInputCapabilities); 

    /**
     * From @c CCoeControl.
     *
     * In debug mode writes the internal state to the given stream. Does
     * nothing in release mode.
     *
     * @param[out] aWriteStream A stream for writing the internal state.
     */
    IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;

private:

    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );

public: // from MEikScrollBarObserver

    /**
     * From @c MEikScrollBarObserver.
     *
     * Handles scrollbar key events.
     *
     * @param aScrollBar The scrollbar.
     * @param aEventType The type of key event.
     */
	IMPORT_C void HandleScrollEventL(CEikScrollBar* aScrollBar, 
                                     TEikScrollEvent aEventType); 

public: // from CTextView::MObserver
	
    /**
     * From @c CTextView::MObserver.
     *
     * Called after reformatting but before redisplay so that edit windows 
     * etc. can be resized. 
     *
     * @param aTextView Not used.
     */
    IMPORT_C void OnReformatL(const CTextView* aTextView);

public:
    
    /**
     * Gets the number of characters in the document.
     *
     * @return The number of characters in the document.
     */
	IMPORT_C TInt TextLength() const;

    /**
     * Gets the cursor’s position within the document.
     *
     * @return The cursor’s position within the document.
     */
	IMPORT_C TInt CursorPos() const;

    /**
     * Gets the number of characters including non-printing characters within
     * the selection.
     *
     * @return The number of characters within the selection.
     */
	IMPORT_C TInt SelectionLength() const;

    /**
     * Gets the cursor selection. If no text view is associated to the Edwin 
     * this returns @c TCursorSelection(0,0).
     *
     * @return The current selection.
     */
	IMPORT_C TCursorSelection Selection() const;

    /**
     * Removes the selection and any composition text. The cursor position is 
     * unaffected. If there is no selected region, this function has no effect.
     */
	IMPORT_C void ClearSelectionL();

    /**
     * Sets the text selection. Highlights the selected area and makes the new 
     * cursor position visible. Any previous selection is cancelled. This 
     * function also updates the scroll bar thumbs if present.
     *
     * @param aCursorPos The cursor’s position.
     * @param aAnchorPos The anchor’s position.
     */
	IMPORT_C void SetSelectionL(TInt aCursorPos,TInt aAnchorPos);

    /**
     * Sets the cursor’s position within the document. If the new position is 
     * not visible the text is scrolled so that the line containing the 
     * cursor is visible. This function also updates the scroll bar thumbs 
     * if present. 
     *
     * @param aCursorPos New cursor position. 
     * @param aSelect @c ETrue to extend the cursor’s selection to the new 
     *        position. @c EFalse otherwise.
     */
	IMPORT_C void SetCursorPosL(TInt aCursorPos,TBool aSelect);

    /**
     * Selects the entire document.
     */
	IMPORT_C void SelectAllL();

    /**
     * Recalculates the screen width of an Edwin from the specified number 
     * of character widths. This is called during construction. If the 
     * Edwin only allows editing of numbers, the width of the zero 
     * character (0) is used; otherwise 
     * @c CFont::MaxNormalCharWidthInPixels() is used.
     * 
     * If the @c EWidthInPixels flag has been set, the @c aWidthInChars 
     * argument is measured in pixels, not characters.
     * 
     * @param aWidthInChars Width in either pixels or characters.
     */
	IMPORT_C void CalculateWidth(TInt aWidthInChars);

    /**
     * Copies the entire document’s content into a descriptor. It is the 
     * caller's responsibility to provide a large enough buffer.
     * 
     * @param[out] aDes An initialised descriptor which on return contains a 
     *        copy of the content of this Edwin.
     */
	IMPORT_C void GetText(TDes& aDes) const;
	
    /**
     * Gets a new buffer containing a copy of the whole text document.
     * 
     * @return A new copy of the document text.
     */
    IMPORT_C HBufC* GetTextInHBufL() const;

    /**
     * Sets the document text of this Edwin from the contents of a descriptor. 
     * This function removes any pictures, any invalid characters and cancels 
     * any previous selection.
     *
     * @param aDes Descriptor from which to copy.
     */
	IMPORT_C void SetTextL(const TDesC* aDes);

    /**
     * Handles cut, copy and paste commands. This function also reports a 
     * change of state of the control to the observer when necessary.
     *
     * @param aClipboardFunc Clipboard operation.
     */
	IMPORT_C void ClipboardL(TClipboardFunc aClipboardFunc);

    /**
     * Inserts a field at the current cursor position. If a selection was made
     * the field replaces that selection.
     *
     * @param aField Text field to insert.
     * @param aFieldType Type of the field. 
     */
	IMPORT_C void InsertFieldL(CTextField* aField, TUid aFieldType);

    /**
     * Updates all the fields in the document. 
     */
	IMPORT_C void UpdateAllFieldsL();
	
    /**
     * Updates any text field at the current cursor position. Updating involves
     * calculating the new value for the field, and replacing the field’s 
     * existing text content with the new text.
     *
     * This function does nothing if the cursor is not within a text field.
     */
    IMPORT_C void UpdateCurrentFieldL();
	
    /**
     * Counts and returns the number of words in the document.
     *
     * @return The number of words in the document.
     */
    IMPORT_C TInt CountWords();

    /**
     * Inserts the contents of a text file into the text being edited at the 
     * current cursor position.
     *
     * @param aFileName The file to open and read.
     * @param aTextOrganisation How to handle line breaks. Default value is 
     *        @c CPlainText::EOrganiseByLine.
     */
    IMPORT_C void InsertFromTextFileL(const TFileName &aFileName,
                    const CPlainText::TTextOrganisation 
                    aTextOrganisation=CPlainText::EOrganiseByLine);

    /**
     * Uses @c SetScrollBarsL() to set the scrollbars.
     * 
     * @param aPtr Pointer to @c CEikEdwin instance.
     * @return Integer value of @c EFalse.
     */
    IMPORT_C static TInt IdleL(TAny *aPtr);

    /**
     * Gets a pointer to the Edwin’s document contents.
     * 
     * @return A @c CPlainText pointer which contains the 
     *         document.
     */
    IMPORT_C CPlainText* Text() const;

    // this is particularly important for when the front-end processor is 
    // inline-editing a CEikEdwin
    /**
     * Cancels any current transaction with the Edwin’s front-end processor. 
     * Any front-end input windows are removed, and any highlighted text being
     * edited in the Edwin is removed. The Edwin is rolled back to the state 
     * it was in before the FEP transaction started. This function is called 
     * by @c CEikEdwin itself when the document content, the cursor position 
     * or the current selection is changed.
     *
     * Cancelling outstanding FEP transactions before performing operations 
     * on the text programmatically is particularly important when the 
     * front-end processor is inline-editing an Edwin.
     *
     */
    IMPORT_C void CancelFepTransaction(); 
    
    /**
     * Handles all modifications made by reformatting the entire document. 
     * Calls @c CEikEdwin::FormatText() and redraws Edwin contents and 
     * scroll bars if they are ready to be redrawn.
     */
    IMPORT_C void HandleTextChangedL();
	
    /**
     * Gets the width used for laying out the text inside the Edwin in pixels. 
     * This may be larger or smaller than the width of the Edwin itself. 
     * See @c SetWysiwygModeOn() for example.
     *
     * @return Width of the text layout area in pixels.
     */
    IMPORT_C TInt LayoutWidth() const;

    /**
     * Formats and draws a new document, updates scrollbars if necessary.
     */
	IMPORT_C void NotifyNewDocumentL();

    /**
     * Reformats and redraws the document, updates scrollbars if necessary.
     */
	IMPORT_C void NotifyNewFormatL();
	
    /**
     * Gets true if a substring is present in the text being edited before or 
     * after the cursor position. If @c aFindText is NULL, then the current 
     * word or selection will be searched for again. 
     * 
     * @param aFindText The substring to search for.
     * @param aFindFlags See @c TFindFlags. Default value is 0. 
     * @return @c ETrue if aFindText is found.
     */
    IMPORT_C TBool FindL(const TDesC* aFindText,TInt aFindFlags=0);
	
    /**
     * Gets the cursor position of the matching text in the document. The 
     * search starts from @c aPos. If @c aFindText is NULL, then the 
     * current word or selection will be searched for. If the substring 
     * cannot be found, this function returns @c KErrNotFound.
     * 
     * @param aFindText The substring to search for.
     * @param aPos Starting position for the find.
     * @param aFindFlags See @c TFindFlags. 
     * @return KErrNotFound if the text was not found, otherwise the 
     *         position of the matched substring.
     */
    IMPORT_C TInt FindTextL(const TDesC* aFindText,TInt aPos,TInt aFindFlags);
	
    /**
     * Replaces the highlighted text. See @c SEdwinFindModel struct.
     *
     * @param[in,out] aFindModel Pointer to the replacement text.
     */
    IMPORT_C void ReplaceL(SEdwinFindModel* aFindModel);

    /**
     * Replaces all occurrences of a string with new text. Both old and new 
     * text are held in @c aFindModel.
     *
     * @param[in,out] aFindModel Pointer to the replacement text.
     * @leave This function will leave if the replace operation fails
     *        unexpectedly.
     */
	IMPORT_C void ReplaceAllL(SEdwinFindModel* aFindModel);

    /**
     * Gets the current word or selection and searches for it. This function 
     * is called by @c FindL() and @c FindTextL() when no text to search for 
     * is given.
     *
     * @param aFindText An empty descriptor.
     */
	IMPORT_C void GetFindText(TDes* aFindText);

    /**
     * Updates scrollbars.
     */
	IMPORT_C void UpdateScrollBarsL();

    /**
     * Creates the Edwin scroll bar frame with no pre-allocation of memory 
     * for scroll bars.
     *
     * @return The scroll bar frame.
     */
	IMPORT_C CEikScrollBarFrame* CreateScrollBarFrameL();

    /**
     * Creates a pre-allocated scroll bar frame.
     *
     * @return Pre-allocated scroll bar frame.
     */
	inline CEikScrollBarFrame* CreatePreAllocatedScrollBarFrameL();
    
    /**
     * Gets the scroll bar frame surrounding this Edwin.
     *
     * @return Pointer to this Edwin’s scroll bar frame.
     */
	inline CEikScrollBarFrame* ScrollBarFrame();
    
    /**
     * Sets word wrapping on or off.
     *
     * @param aWrapIsOn @c ETrue enables word wrapping, @c EFalse disables 
     *        word wrapping.
     */
	IMPORT_C void SetWordWrapL(TBool aWrapIsOn);
	
    /**
     * Gets the width of a line cursor in pixels.
     *
     * @return Always 0.
     */
    IMPORT_C virtual TInt LineCursorWidth() const;
	
    /**
     * Sets the zoom factor of the document and reformats the document.
     *
     * @param aZoomFactor New value for the zooming factor.
     */
    IMPORT_C void SetZoomFactorL(TZoomFactor* aZoomFactor);
	
    /**
     * Sets the Edwin’s background colour.
     *
     * @param aBackground New value for the background colour. 
     */
    IMPORT_C void SetBackgroundColorL(TRgb aBackground);
	
    /**
     * Sets the format mode to be WYSIWYG.
     *
     * @param aLayoutWidth Formatting width in twips. 
     * @param aDevice Mapping between twips and pixels on the target device.
     */    
    IMPORT_C void SetWysiwygModeOn(TInt aLayoutWidth,
                                   MGraphicsDeviceMap* aDevice);
	
    /**
     * Switches off the WYSIWYG mode. This function sets the new format mode 
     * to be @c EFScreenMode.
     */
    IMPORT_C void SetWysiwygModeOff();
	
    /**
     * Updates the text wrap width. This function is for use in WYSIWYG mode
     * only.
     *
     * @param aLayoutWidth New width to wrap text at in WYSIWYG mode in twips.
     */
    IMPORT_C void UpdateLayoutWidth(TInt aLayoutWidth); 
    	
    /**
     * Sends the Edwin’s document using an infra red beamer.
     */
    IMPORT_C void SendDataOverIrL();
	
    /**
     * Receives an Edwin document using an infra red beamer.
     * This function will leave if the data received is not a suitable type 
     * to be pasted into the Edwin.
     */
    IMPORT_C void ReceiveDataOverIrL();
	
	/**
	* Controls the formatting mode of the editor.
	*
	* The length of the text is compared against current formatting mode thresholds.
	* (See method SetUpperFullFormattingLength). If the length is greater than the 
	* upper limit of full formatting, then the editor is set to "band" formatting,
	* where the editor attempts to format as little as is needed, e.g. the visible part
	* of the editor. If the text length is less than the lower limit of band formatting, 
	* then the formatting mode is switched to full document formatting.
    *	
    * This method performs an immediate re-formatting of all or part of the text with the new formatting mode.
	* 
	* @param aIsNewDoc  If EFalse, attempts to perform re-formatting based upon current formatting
	*                   If not EFalse, whole document it formatted from scratch
	*                   Note: This parameter is ignored if aReFormat is EFalse
	*/
	IMPORT_C void SetAmountToFormatL(TBool aIsNewDoc=EFalse);

    /**
    * Controls the formatting mode of the editor.
    *
    * The length of the text is compared against the current formatting mode thresholds.
    * (See method SetUpperFullFormattingLength). If the length is greater than the 
    * upper limit of full formatting, then the editor is set to "band" formatting,
    * where the editor attempts to format as little as is needed, e.g. the visible part
    * of the editor. If the text length is less than the lower limit of band formatting, 
    * then the formatting mode is switched to full document formatting.
    *	
    * This method has a flag to allow any immediate re-formatting to be suppressed. 
    * Formatting text can be a time-consuming operation. If the client is able to 
    * ensure that no reformatting is needed, (for instance if a further re-formatting 
    * API is going to be called later) then the reformatting flag can be called
    * with EFalse. Otherwise, a re-format will take place within this method.
    * 
    * @since 3.1
    * @param aIsNewDoc  If EFalse, attempts to perform re-formatting based upon current formatting
    *                   If not EFalse, whole document it formatted from scratch
    *                   Note: This parameter is ignored if aReFormat is EFalse
    * @param aReFormat  If EFalse, do not perform any re-formatting 
    */
    IMPORT_C void SetAmountToFormatL( TBool aIsNewDoc, TBool aReFormat );

    /**
     * Sets the @c EPasteFromIrStore flag.
     *
     * @param aPasteFromIrStore @c ETrue to set the @c EPasteFromIrStore flag. 
     *        @c EFalse to remove the @c EPasteFromIrStore flag.
     */
    IMPORT_C void SetPasteFromIrStore(TBool aPasteFromIrStore);
	
    /**
     * Copies the contents of a stream store to the current cursor position, 
     * replacing any selected text. This function is used to paste data from 
     * the clipboard.
     *
     * @param[out] aStore Store from which to read.
     * @param[in] aDict Stream dictionary. 
     */
    IMPORT_C void PasteFromStoreL(CStreamStore& aStore, 
                                  CStreamDictionary& aDict);
	
    /**
     * Copies the highlighted text into a stream store.
     *
     * @param[out] aStore Store to write to. 
     * @param[in] aDict Stream dictionary.
     */
    IMPORT_C void CopyToStoreL(CStreamStore& aStore, CStreamDictionary& aDict);
	
    /**
     * Sets the text view margins. 
     *
     * @param aMargins New value for the view’s margins. 
     */
    IMPORT_C void SetBorderViewMargins(TMargins8 aMargins);
	
    /**
     * Forces the scrollbars to update now; this is a synchronous function.
     */
    IMPORT_C void ForceScrollBarUpdateL();
	
    /**
     * Sets whether the Edwin owns a document. Edwins can either be used as a 
     * standalone text editor control, or as an editor for text owned by 
     * another object. The document ownership setting determines whether the 
     * Edwin or another object owns the document.
     *
     * @param aOwner Whether Edwin or another object owns the document. 
     *        See @c TOwnershipType.
     */
    IMPORT_C void SetDocumentOwnership(TOwnershipType aOwner);
	
    /**
     * Sets the maximum number of characters that can be inserted.
     *
     * @param aLimit New maximum for the number of characters that can be
     *        inserted.
     */
    IMPORT_C void SetTextLimit(TInt aLimit);
	
    /**
     * Displays a dialog allowing the user to choose a character from the 
     * character map. The selected character is inserted into the Edwin 
     * at the current cursor position.
     */
    IMPORT_C void RunCharMapDialogL();
	
    /**
     * Gets the text view margins. 
     *
     * @return The text view margins.
     */
    IMPORT_C TMargins8 Margins() const;
	
    /**
     * Gets the upper limit for formatting. This returns the value of 
     * @c KFullFormattingUpperThreshold which determines the maximum number of 
     * characters that can be formatted, if it is exceeded then only visible 
     * text is formatted. This is used with @c KPartialFormattingLowerThreshold 
     * to control the extent of text formatting.
     *
     * @return The value of @c KFullFormattingUpperThreshold.
     */
    IMPORT_C TInt UpperFullFormattingLength() const;
	
    /**
     * Gets the lower limit for formatting. This returns the value of 
     * @c KPartialFormattingLowerThreshold which determines when a switch is 
     * made from formatting only visible text to formatting all text. When the 
     * text length exceeds the @c KFullFormattingUpperThreshold only visible 
     * text is formatted. If some characters are deleted so that the text 
     * length is less than @c KFullFormattingUpperThreshold the entire text 
     * is still not formatted. Instead, reformatting occurs only when the 
     * number of characters is less than the value of 
     * @c KPartialFormattingLowerThreshold.
     *
     * @return The value of @c KPartialFormattingLowerThreshold.
     */
    IMPORT_C TInt LowerPartialFormattingLength() const;
	
    /**
     * Sets the Edwin’s read-only flag so that documents displayed by Edwin 
     * cannot be edited by users.
     *
     * @param aReadOnly @c ETrue to set Edwin to display documents as 
     *        read-only. @c EFalse otherwise.
     */
    IMPORT_C void SetReadOnly(TBool aReadOnly);
	
    /**
     * Determines whether the document being edited with Edwin is read-only.
     *
     * @return @c ETrue if the document being edited is read-only. 
     *         @c EFalse otherwise. 
     */
    IMPORT_C TBool IsReadOnly() const;
    
    /**
         * Gets editor flags from the editor.
         * @return editor flags if existed
         * @or return KErrNotFound
         */
    IMPORT_C TInt CEikEdwin::AknEditorFlags();
    

	
    /**
     * Determines whether the document being edited is read only. Displays 
     * a message with @c CEikonEnv::InfoMsg() if the document is set as 
     * read-only.
     */
    IMPORT_C void CheckNotReadOnlyL();
	
    /**
     * Sets whether the document accepts pictures.
     *
     * @param aAllow @c ETrue sets the document to accept pictures, @c EFalse 
     *        sets the document to not accept pictures.
     */
    IMPORT_C void SetAllowPictures(TBool aAllow);
	
    /**
     * Removes unwanted pictures. If @c EAllowPictures has been set, returns 
     * immediately. Otherwise, this function checks the document text between 
     * two bounds and removes all pictures in that range.
     *
     * @param aStartPos Where to start looking for unwanted pictures.
     * @param aLength Where to stop. 
     */
    IMPORT_C void CheckRemovePictures(TInt aStartPos,TInt aLength);
	
    /**
     * Sets the minimum gap between text and the right hand edge of the Edwin 
     * when text is wrapped. This value is used to calculate the layout area 
     * for text.
     *
     * @param aGap Size of the gutter in pixels.
     */
    IMPORT_C void SetRightWrapGutter(TInt aGap);
	
    /**
     * Undoes the most recent text operation when the Edwin supports this 
     * feature and when the undo store is not empty.
     */
    IMPORT_C void UndoL();
	
    /**
     * Deletes the undo store.
     */
    IMPORT_C void ClearUndo();
	
    /**
     * Sets whether the undo operation is permitted.
     *
     * @param aAllow ETrue to permit undo operations. EFalse to not permit undo
     *        operations.
     */
    IMPORT_C void SetAllowUndo(TBool aAllow);
	
    /**
     * Gets whether Edwin is set to support the undo command.
     *
     * @return @c ETrue if edits can be undone. @c EFalse if edits cannot
     *         be undone.
     */
    IMPORT_C TBool SupportsUndo() const;
	
    /**
     * Tests whether an undo is possible. Returns @c ETrue only if the undo 
     * store is available to Edwin.
     *
     * @return @c ETrue if the undo store is available. @c EFalse if the 
     *         undo store is not available.
     */
    IMPORT_C TBool CanUndo() const;
	
    /**
     * Sets whether picture characters and/or punctuation should be treated as 
     * word delimiters in addition to whitespace. 
     *
     * @param aPicture @c ETrue if picture characters should be treated as 
     *        delimiters for words.
     * @param aPunctuation @c ETrue if punctuation should be treated as 
     *        delimiters for words. 
     */
    IMPORT_C void SetWordDelimiters(TBool aPicture,TBool aPunctuation);
	
    /**
     * Gets the start position and the length of the word in which the 
     * specified document position is located.
     *
     * @param[in] aCurrentPos A position within a word in the text. 
     * @param[out] aStartPos Returns the start position of the word.
     * @param[out] aLength Returns the word’s length. 
     */
    IMPORT_C void GetWordInfo(TInt aCurrentPos,
                              TInt& aStartPos,
                              TInt& aLength) const;
	
    /**
     * Sets the new cursor position. If the cursor is no longer visible the 
     * document is scrolled to display the line containing the new cursor 
     * position. Scrollbars are also updated if present.
     *
     * @param aMovement The cursor movement. 
     * @param aSelect If @c ETrue, the selection is extended. This corresponds 
     *        to holding down the Shift key on a machine keyboard.
     */
    IMPORT_C void MoveCursorL(TCursorPosition::TMovementType aMovement,
                              TBool aSelect);
	
    /**
     * Scrolls the text either horizontally or vertically without affecting 
     * the cursor’s position.
     *
     * @param aMovement The cursor's movement.
     */
    IMPORT_C void MoveDisplayL(TCursorPosition::TMovementType aMovement);
	
    /**
     * Removes all non-ASCII characters from the specified text. This can be 
     * used to remove Unicode characters where they are not valid characters 
     * for example.
     *
     * @param aStartPos The start position in the text. 
     * @param aLength The number of characters, beginning with aStartPos to 
     *        check.
     */
    IMPORT_C void CheckValidityOfChars(TInt aStartPos,TInt aLength);
	
    /**
     * Sets the @c EOnlyASCIIChars flag. 
     *
     * @param aASCIIOnly If @c ETrue the EOnlyASCIIChars flag will be set. If 
     *        @c EFalse the EOnlyASCIIChars flag will be removed.
     */
    IMPORT_C void SetOnlyASCIIChars(TBool aASCIIOnly);
	
    /**
     * Tests whether the @c EOnlyASCIIChars flag is set. 
     *
     * @return @c ETrue if the @c EOnlyASCIIChars flag is set.
     */
    IMPORT_C TBool OnlyASCIIChars() const;
	
    /**
     * Gets the average number of lines shown in Edwin’s view.
     *
     * @return The average number of lines.
     */
    inline TInt AvgLinesInViewRect() const;
	
    /**
     * Gets the average number of characters on a line.
     *
     * @return The average number of characters on a line.
     */
    inline TInt AvgCharsPerLine() const;
	
    /**
     * Sets the average number of lines displayed in Edwin’s view.
     *
     * @param aAvgLines The average number of lines to display.
     */
    inline void SetAvgLinesInViewRect(TInt aAvgLines);
	
    /**
     * Sets the average number of characters per line.
     *
     * @param aAvgChars The average number of characters per line.
     */
    inline void SetAvgCharsPerLine(TInt aAvgChars);
	
    /**
     * Sets the Edwin size observer. Does not imply transfer of ownership.
     *
     * @param aEdwinSizeObserver The Edwin size observer.
     */
    IMPORT_C void SetEdwinSizeObserver(MEikEdwinSizeObserver* 
                                            aEdwinSizeObserver);
	
    /**
     * Gets the minimum Edwin height.
     *
     * @return The minimum Edwin height.
     */
    IMPORT_C TInt MinimumHeight() const;

    /**	
     * Gets the maximum Edwin height.
     *
     * Please do not use the following method for deciding heights if you are 
     * using edwins with Maximum Heights in forms. Use @c MaximumHeightInLines 
     * instead.
     *
     * @return The maximum Edwin height.
    */
	IMPORT_C TInt MaximumHeight() const;
    
    /**
     * Sets the minimum Edwin height. This function also increases the maximum 
     * Edwin height if its value is less than @c aHeight.
     */
	IMPORT_C void SetMinimumHeight(TInt aHeight);

    /**
     * Sets the maximum Edwin height. This function also decreases the minimum 
     * Edwin height if its value is greater than @c aHeight.
     * 
     * Please do not use the following method for setting maximum heights if 
     * you are using edwins with maximum heights in forms. Use 
     * @c MaximumHeightInLines instead.
     *
     * @param aHeight The maximum Edwin height.
    */
	IMPORT_C void SetMaximumHeight(TInt aHeight);
	
	void OnEditorStateFlagChange( TInt aOldFlag, TInt aNewFlag );
	void ReportChinesePopupEventL( TBool aChinesePopupOpen );

public: // new utility methods

    /**
     * Replaces the cursor selection with the identified text.
     * 
     * @param aInsertPos The position at which text will be inserted. 
     * @param aText The text to insert. 
     * @param aDelete The cursor-selected text that will be replaced by @c 
     *        aText.
     */
	IMPORT_C void InsertDeleteCharsL(TInt aInsertPos,
                                     const TDesC& aText,
                                     const TCursorSelection& aDelete);
	
    /**
     * Sets non-printing characters?visibility.
     *
     * @param aVisibility Non-printing characters?visibility.
     */
    IMPORT_C void SetNonPrintingCharsVisibility(TNonPrintingCharVisibility 
                                                aVisibility);
	
    /**
     * Sets non-printing characters?visibility.
     *
     * @return Non-printing characters?visibility.
     */
    IMPORT_C TNonPrintingCharVisibility NonPrintingCharsVisibility() const;

public: // new Avkon wrap interface

    /**
     * Sets the @c EAvkonEditor flag.
     *
     * @param aAvkonWrapIsOn If @c ETrue @c EAvkonEditor flag is set.
     */
	IMPORT_C void SetAvkonWrap(TBool aAvkonWrapIsOn);

public:	// Avkon editor extensions

    /**
     * Sets default case for the editor. The case is used when the editor
     * is focused first time. Available case flags from @c uikon.hrh
     * are @c EAknEditorUpperCase, @c EAknEditorLowerCase and 
     * @c EAknEditorTextCase. @c EAknEditorTextCase is used if the initial 
     * case is not set from EDWIN resource default_case or with this API.
     *
     * @param aCase Initial case to be used in the editor.
     */
    IMPORT_C void SetAknEditorCase(TInt aCase);

    /**
     * Sets permitted cases for the editor.
     * Possible flags from @c uikon.hrh are @c EAknEditorAllCaseModes, 
     * @c EAknEditorUpperCase, @c EAknEditorLowerCase and 
     * @c EAknEditorTextCase. @c EAknEditorAllCaseModes is used if the value 
     * is not set from EDWIN resource allowed_case_modes or with this API.
     *
     * @param aPermittedCaseModes Case modes that are available in the editor.
     */
    IMPORT_C void SetAknEditorPermittedCaseModes(TInt aPermittedCaseModes);

    /**
     * Sets number mode key mapping for '*' and '#' keys. The key mapping is 
     * used in editors when numeric input mode is used. Key mapping characters
     * for '*' key are shown on special character table if also text input 
     * modes are allowed in the editor but the current input mode is numeric 
     * mode. @c EAknEditorStandardNumberModeKeymap is used in editors that 
     * allow only numeric input if the mapping is not set from EDWIN resource 
     * @c numeric_keymap or with this API. 
     * @c EAknEditorAlphanumericNumberModeKeymap is used as default if the 
     * editor allows also text input mode.
     *
     * @param aNumericKeymap Key mapping used in an editor with number input 
     *        mode.
     */
    IMPORT_C void SetAknEditorNumericKeymap(TAknEditorNumericKeymap 
                                            aNumericKeymap);

    /**
     * Sets default input mode for the editor. The input mode is used when 
     * the editor is focused first time. 
     * @c EAknEditorTextInputMode is used if the initial input mode is not set 
     * from EDWIN resource default_input_mode or with this API.
     *
     * @param aInputMode Initial input mode to be used in the editor.
     */
    IMPORT_C void SetAknEditorInputMode(TInt aInputMode);

    /**
     * Sets allowed input modes for the editor. 
     * All input modes are allowed (@c EAknEditorAllInputModes) if the value 
     * is not set from EDWIN resource @c allowed_input_modes or with this API.
     *
     * @param aInputModes Input modes that are allowed in the editor.
     */
    IMPORT_C void SetAknEditorAllowedInputModes(TInt aInputModes);

    /**
     * Sets editor specific special character table. 
     *
     * @param aSCTResId Special character table dialog resource.
     */
    IMPORT_C void SetAknEditorSpecialCharacterTable(TInt aSCTResId);

    /**
     * Sets initial editor flags for the editor.
     * This method can be used also to update editor flags after the editor is 
     * focused. FEP is automatically notified of the updated editor flags.
     *
     * @param aFlags Avkon editor flags for the editor.
     */
    IMPORT_C void SetAknEditorFlags(TInt aFlags);

    /**
     * Enables or disables CCPU interface provided functionalities 
     * (cut, copy, paste and undo).
     * 
     * @param aSupport CCPU support enabled if @c ETrue.
     */
    IMPORT_C void EnableCcpuSupportL(TBool aSupport);

    /**
     * Updates editor input mode. FEP is automatically notified of the
     * new input mode in editor state and FEP takes new input mode to use 
     * immediatelly. Current inline editing is reset.
     * This method should not be used for setting initial input mode for the 
     * editor. Use @c SetAknEditorInputMode() method instead for setting 
     * initial input mode.
     *
     * @param aInputMode New input mode for the editor.
     */
    IMPORT_C void SetAknEditorCurrentInputMode(TInt aInputMode);

    /**
     * Returns the input mode that has been saved to editor state.
     *
     * @since S60 2.6
     * @return Input Mode that is saved to editor state.
     */
    IMPORT_C TInt AknEditorCurrentInputMode();

    /**
     * Updates editor case. FEP is automatically notified of the
     * case change in editor state and FEP takes new case to use immediately.
     * Available case flags from @c uikon.hrh are @c EAknEditorUpperCase, 
     * @c EAknEditorLowerCase and @c EAknEditorTextCase.
     * This method should not be used to set initial case for the editor.
     * Use @c SetAknEditorCase() method instead for setting initial case.
     *
     * @param aCase New case for the editor.
     */
    IMPORT_C void SetAknEditorCurrentCase(TInt aCase);

    /**
     * Sets new local input language for the editor. Global input language
     * changes have not effect for the input language but the user can still
     * change the input language from the edit menu.
     *
     * @param aLanguage Editor local input language.
     */
    IMPORT_C void SetAknEditorLocalLanguage(TLanguage aLanguage);

    /** 
     * This call causes FEP to reset current editing state and
     * new editing state is fetched from @c CAknEdwinState object.
     */
    IMPORT_C void NotifyEditorStateObserverOfStateChangeL();

    /**
     * Used for suppressing all editor's background drawing. This is
     * intended for internal use.
     *
     * Note that when this is set, the background is not drawn with skin
     * nor cleared, so the background MUST be drawn by the parent control
     * every time the editor changes.
     *
     * @param aSuppress If ETrue, suppress background drawing
     */
    IMPORT_C void SetSuppressBackgroundDrawing( TBool aSuppress );
    
    /**
     * Tests if the background drawing is suppressed.
     *
     * @return ETrue if the background drawing is suppressed
     */
    IMPORT_C TBool IsBackgroundDrawingSuppressed() const;
    
    /**
     * Used to prevent partial text lines from being drawn.
     * The client is responsible for giving a sane value. An empty
     * rect disables this feature. This is intended for internal use.
     *
     * @param aRect The rect which contains text lines to be drawn
     */
    IMPORT_C void SetTextLinesRect( const TRect& aRect );
    
	/**
	 * Used to determine which area is used for scrolling
	 */
	IMPORT_C void SetScrollRect( const TRect & aRect );

    /**
     * Gets the rectangle set for drawing only full lines. In case
     * the feature is disabled, this returns an empty rect.
     * This is intended for internal use.
     *
     * @return The rect which contains text lines to be drawn
     */
    IMPORT_C TRect GetTextLinesRect() const;
    
    /**
	 * Used to control cursor visibility
	 */
    IMPORT_C void SetCursorVisible(TBool aVisible);
public:

    // These methods have been added for use with Avkon to set maximum 
    // editor heights.
    /**
     * Sets editor's maximum height in lines.
     *
     * @param aLines Maximum height in lines.
     */
	IMPORT_C void SetMaximumHeightInLines(TInt aLines);

    /**
     * Gets editor maximum height in lines.
     *
     * @return Maximum height in lines.
     */
	IMPORT_C TInt MaximumHeightInLines() const;

public: // From MEikCcpuEditor

    /**
     * Tests whether the editor is focused.
     * 
     * @return If editor is focused, @c ETrue is returned.
     */
	IMPORT_C TBool CcpuIsFocused() const;

    /**
     * Tests whether the selected text can be cut.
     * 
     * @return @c ETrue if it is possible to cut the selected text.
     */
	IMPORT_C TBool CcpuCanCut() const;

    /**
     * Cuts selected text.
     */
	IMPORT_C void CcpuCutL();
	
    /**
     * Tests whether the selected text can be copied.
     * 
     * @return @c ETrue if it is possible to copy the selected text.
     */
    IMPORT_C TBool CcpuCanCopy() const;

    /**
     * Copies selected text.
     */
	IMPORT_C void CcpuCopyL();
	
    /**
     * Tests whether text can be pasted from the clipboard.
     * 
     * @return @c ETrue if it is possible to paste the clipboard text.
     */
    IMPORT_C TBool CcpuCanPaste() const;

    /**
     * Pastes text from the clipboard to the editor.
     */
	IMPORT_C void CcpuPasteL();
	
    /**
     * Tests is it possible to undo previous operation.
     * 
     * @return @c ETrue if it is possible to undo previous operation.
     */
    IMPORT_C TBool CcpuCanUndo() const;

    /**
     * Undoes the most recent text operation when the Edwin supports this
     * feature and when the undo store is not empty
     */
	IMPORT_C void CcpuUndoL();
	
    /**
     * Gets edwin's flags from @c CAknEdwinState.
     * 
     * @return The control's flags.
     */
    IMPORT_C TInt AknEdwinFlags() const;
 

public: // Internal to Symbian
	
    // the following methods are deprecated and will be removed in a future 
    // release
    /**
     * Allocates memory for the Edwin text view.
     */
	IMPORT_C void CreateTextViewL();

    /**
     * Gets Edwin text view.
     *
     * @return Pointer to the Edwin text view.
     */
	IMPORT_C CTextView* TextView() const;

    /**
     * Gets Edwins text layout.
     *
     * @return Pointer to the text layout.
     */
	IMPORT_C CTextLayout* TextLayout() const;

    /**
     * Sets undo buffer for the Edwin.
     *
     * @param aSelection The current selection.
     * @return @c ETrue if buffer was set.
     */
	IMPORT_C TBool SetUndoBufferL(const TCursorSelection& aSelection);

    /**
     * Sets new undoable text to the undo buffer.
     * 
     * @param aSelection The current selection.
     */
    IMPORT_C void SetUndoableText(const TCursorSelection& aSelection);

    /**
     * Gets the editor state.
     *
     * @return Pointer to editor state object.
     */
	CAknEdwinState* EditorState() const;

    /**
     * Sets maximum length for the editor.
     *
     * @param aLength Maximum length for the editor.
     */
	inline void SetMaxLength(TInt aLength);

    /**
     * Gets the editor maximum length.
     *
     * @return The editor maximum length
     */
	inline TInt MaxLength() const;

public:

	// added to get access to user flags without a get/set for every different
    // flag.
    /**
     * Adds user flags.
     * See @c TFlags.
     *
     * @param aFlag Flags to add.
     */
	IMPORT_C void AddFlagToUserFlags(TUint32 aFlag);
	
    /**
     * Removes user flags.
     * See @c TFlags.
     *
     * @param aFlag Flags to remove.
     */
    IMPORT_C void RemoveFlagFromUserFlags(TUint32 aFlag);

    /**
     * Gets user flags.
     * See @c TFlags.
     *
     * @return The user flags.
     */
	IMPORT_C TUint32 UserFlags() const ;

public:

    /**
     * Sets the character format layer for the editor. Ownership of the 
     * CCharFormatLayer is transferred.
     *
     * @param aCharFormatLayer Pointer to the character format layer object.
     */
	IMPORT_C void SetCharFormatLayer(CCharFormatLayer* aCharFormatLayer);
	
    /**
     * Sets the paragraph format layer for the editor. Ownership of the 
     * CParaFormatLayer is transferred.
     *
     * @param aParaFormatLayer Pointer to the paragraph format layer object.
     */
    IMPORT_C void SetParaFormatLayer(CParaFormatLayer* aParaFormatLayer);


public: // Skins support

    /**
     * Sets within in the editor an externally owned Skins background control 
     * context. This background control context will then be used by the editor
     * to draw background.
     *
     * If this API is not called, then the editor IS skin enabled, (that is 
     * @c CEikEdwins are skin enabled by default) but it will try to find a 
     * control context with which to perform background drawing from the 
     * Control Environment, via the Object Provider.
     *
     * Setting this control context to NULL will have the effect of turning off
     * background skinning. 
     *
     * @param aContext Control context to store. Not owned. Can be NULL.
     */
    IMPORT_C void SetSkinBackgroundControlContextL( MAknsControlContext* 
                                                    aContext );

    /**
     * Access to Skins background control context that is potentially being 
     * used by the Editor.
     *
     * This API will first check to see if an control context has been set by 
     * API, and if so, return that. If the background control context has been 
     * set to NULL by API, then it will return NULL. If the background control 
     * context has never been set by API, then this returns the control context 
     * (if one exists) that the object obtains from Object Provider.
     * 
     * @return Pointer to control context potentially in 
     *         use, or NULL.
     */
    MAknsControlContext* SkinBackgroundControlContext() const;

    /**
     * Access to disposition of the editor to perform Skinning. This does not 
     * take into account whether the application is skin enabled or whether the 
     * environment is providing a background control context. It is only a 
     * function of whether editor's (default) disposition to skin has been 
     * countered by calls on the editor API.
     * 
     * @return @c EFalse if SetSkinBackgroundControlContextL has been 
     *         called with NULL in its most recent call.
     */
    TBool SkinEnabled() const;

	/**
	 * Stores the alignment value for an editor.
	 *
	 * @param aAlignment Editor alignment to be stored - must be supplied as
	 *	      one of the values in Avkon editor alignment enum i.e.:
	 *           EAknEditorAlignCenter,
	 *           EAknEditorAlignLeft,
	 *           EAknEditorAlignRight, 
	 *           EAknEditorAlignBidi
	 */
	IMPORT_C void SetAlignment(TInt aAlignment);

public: // Pictograph support

    /**
     * Redraws text view. Used for pictograph animations.
     */
    void DrawTextView() const;

    /**
     * Sets the callback, which the editor calls after having redrawn itself 
     * for animated pictographs. @c CEikCaptionedControl uses it to draw the 
     * highlight frame on top of the editor.
     *
     * @since S60 2.6
     * @param aCallBack The callback.
     */
    IMPORT_C void SetPictographAnimationCallBack( TCallBack& aCallBack );

    /**
     * Returns pictograph animation callback. If it is not set, the function
     * pointer is NULL.
     *
     * @return Pictograph animation callback
     */
    const TCallBack& PictographAnimationCallBack() const;

    /**
     * This method sets the upper limit of full document formatting.  
     *
     * At construction, the mode is full document formatting, where the text 
     * formatter processes the whole document to determine its layout.
     * 
     * When the text content is set, or when user input causes the length of 
     * text to exceed this value, the formatting mode switches to "Band" 
     * formatting, where the text formatter attempts to format as little as 
     * possible - optimally just the visible screen.
     * 
     * A lower limit is calculated from the passed-in value, by the subtraction
     * of a constant. When the text becomes smaller than this lower limit, the
     * formatting switches to full document formatting.
     * 
     * Internally-imposed limits prevent the client setting too small a value 
     * for proper operation of the text formatting.
     *
     * If this method is not called, the upper and lower limts are set to a 
     * large default values.
     *
     * Access to the actual limits is available via the methods 
     * @c UpperFullFormattingLength() and @c LowerPartialFormattingLength().
     *
     * @since 3.0
     * @param aUpperFullFormattingLimit The upper limit of full document 
     *        formatting.
     */
    IMPORT_C void SetUpperFullFormattingLength( TInt aUpperFullFormattingLimit );
    
    /**
     * Can be called to inhibit redrawing of the editor when NotifyNewFormatL()
     * is called.
     *
     * @param aEnabled If ETrue, inhibit redrawing when notified of
     * new format from now on.
     */
	IMPORT_C void SetSuppressNotifyDraw( TBool aEnabled );    

    /**
     * Can be called to inhibit formatting of the editor. Care is required to ensure that
     * the necessary reformatting is carried out later on if this API is used. 
     * 
     * Note: When called with EFalse, it does not automatically trigger reformatting.
     *
     * @since 3.1
     * @param aSuppressed If ETrue, inhibit formatting from now on, if EFalse,
     * re-enable formatting from now on. 
     */
    IMPORT_C void SetSuppressFormatting( TBool aSuppressed );

    /**
     * Enables kinetic scrolling in editor.
     * 
     * Note that when kinetic scrolling is enabled, it is
     * no longer possible to disable it with this function.
     * 
     * @since S60 v5.2
     * @param aEnable ETrue if kinetic scrolling should be enabled.
     */
    IMPORT_C void EnableKineticScrollingL( TBool aEnable );

public: 
    void EnableSmileySupportL( TBool aEnableSmiley );
    TBool IsSmileyEnabled() const;
    void DrawSmileyInTextL( CBitmapContext& aGc, CFont& aFont, 
        const TDesC& aText, const TPoint& aPt );
    void ConvertVisibleTextForSmileyL( TBool aTextToCode );    
    void HandleScrollForSmileyL();
    TBool AdjustCursorForSmileyL( TInt aOldCursor, TCursorSelection& aSelect );
    TRect AdjustDrawRectForSmiley( const TRect& aRect ) const;
    void GetClipRegionForSmiley( RRegion& rgn, CFont& aFont, const TDesC& aText, 
        const TPoint& aPt, const TRect& aRect ) const;
    HBufC* ExtractTextLC( TCursorSelection aSelect );
    void ConvertSmileyIconToTextL( TInt aStartPos, TDes& aText );

private:
    void ConvertTextForSmileyL( TCursorSelection aSelect, 
        TBool aTextToCode, TBool aRedraw = ETrue );
    void TrimText( TDes& aText );
    TCursorSelection GetVisibleTextRangeL();
    void ExtendedRangeForSmiley( TCursorSelection& aSelect );
    TBool ConvertSmileyForDeleteL( TInt aDocPos, TBool aBackSpace ); 
    void ConvertSmileyForDeleteL( const TCursorSelection &aSelect );
    TBool AdjustCursorPosByMovementL( TCursorPosition::TMovementType aMovement, 
        TBool aSelect );
    void HandleSelectionForSmiley( TCursorSelection aSelect );
	    
protected:

    /**
     * Specifies the end points of the editable area.
     */
	enum TEnd
		{
        /** The start of the editable area. */
		EStart,

        /** The end of the editable area. */
		EEnd   
		};

    /**
     * Specifies the chunk size as either a word, or a paragraph.
     */
	enum TChunkSize
		{
        /** A word. */
		EChunkWord,

        /** A paragraph. */
		EChunkPara
		};

    /**
     * Specifies the chunk size as either a word, or a paragraph.
     */
	enum TEikEdwinFlags // Internal flags
		{ 
        /** Rich text editor used. */
		ERichText           =0x00000001,
		
        /** For double item dragging. */
        EDragDouble			=0x00000002,
		
        /**
         * If set, indicates the pointer being pressed inside the 
         * editor rectangle.
         */
        ELeftDownInViewRect =0x00000004,
		
        /** Used to calculate initial width. */
        ENumericCharacters	=0x00000008, 
		
        /** Edwin has one line and is not resizable. */
        EHasOneLineOnly     =0x00000010,  
        
        /** 
         * Custom formatter is installed to find and format phone numbers 
         * (@c CEikRichTextEditor only).
         */
        EPhoneNumberGrouping = 0x00000020,
		ESuppressNotifyDraw  = 0x00000040,
		ESuppressFormatting  = 0x00000080, // Suppresses calls to formatting
		ESkipBackgroundDrawer = 0x00000100
        };

protected: // from MEditObserver
    
    /**
     * From @c MEditObserver.
     *
     * Observer function called by the @c CRichText object when the object is 
     * edited to give notification of changes to its text buffer. In this way,
     * the control knows how the text object has changed and can reformat and 
     * redraw the text object appropriately.
     * 
     * @param aStartEdit The start position of the edit. 
     * @param aEditLength The number of characters added or, if negative, 
     *        deleted after this position.
     */
	IMPORT_C void EditObserver(TInt aStartEdit,TInt aEditLength);

protected:
    
    /**
     * Draws the visible text and the cursor for DrawL(), but does not draw 
     * the border. The @c DrawL() function is trapped to handle problems due
     * to insufficient resources being available.
     *
     * @param aRect Rectangle in which to draw.
     */
	IMPORT_C void TrappedDraw(const TRect& aRect) const;
    
    /**
     * Draws the visible text and the cursor.
     */
	IMPORT_C void DrawContents();
	
    /**
     * Completes the second-phase construction of a @c CEikEdwin object. This 
     * protected function is called by @c ConstructL() and 
     * @c ConstructFromResourceL() after the Edwin’s size, flags and text 
     * limit have been set. Derived classes should call either this function 
     * or @c CEikEdwin’s @c ConstructL() or @c ConstructFromResourceL() 
     * functions during their construction before initialising their own 
     * members.
     */
    IMPORT_C void BaseConstructL();
	
    /**
     * Formats all the text in the text view. Called by several functions, for 
     * example by @c CEikEdwin::HandleTextChangedL() and 
     * @c CEikEdwin::SetTextL().
     */
    IMPORT_C void FormatTextL();
	
    /**
     * Deletes the text under the cursor selection, also cancelling the
     * selection. This function asks the user to confirm this action if
     * aPromptConfirmation is ETrue.
     *
     * @param[out] aChanged On return, @c ETrue if the text was changed. 
     * @param[in] aIsBackSpace ETrue if this is in response to backspace being 
     *        pressed. Determines whether character formatting is preserved 
     *        or not. Default value is @c EFalse.
     * @param[in] aPromptConfirmation Optional. @c ETrue to ask the user to
     *            confirm this action. Default value is @c ETrue.
     * @return The cursor position in the text after deletion.
     */
    IMPORT_C TInt DeleteHighlightL(TBool& aChanged, 
                                   TBool aIsBackSpace=EFalse,
                                   TBool aPromptConfirmation=ETrue);
	
    /**
     * Confirms whether the deletion of the user’s selection is required.
     *
     * If the user’s selection is less than @c KBlockDeleteWarningSize and does
     * not contain a picture, this function returns @c ETrue.
     *
     * If the user’s selection is greater than @c KBlockDeleteWarningSize or 
     * contains a picture, this function asks the user to confirm deletion of 
     * their selection and then returns the user’s response.
     *
     * @return @c ETrue.
     */
    IMPORT_C TBool OkToDeleteSelectionL();
	
    /**
     * Deletes the cursor’s selection. If no selection is made, this function 
     * deletes only one character. The argument @c aIsBackSpace determines 
     * whether to preserve the character formatting or not.
     *
     * @param[out] aChanged On return, @c ETrue if the text was changed.
     * @param[in] aSelection The cursor selection describing the position to be
     *            deleted. 
     * @param[in] aIsBackSpace @c ETrue if this in response to backspace being 
     *            pressed. Determines whether character formatting is preserved
     *            or not.
     * @param[in] aAllowUndo @c ETrue if the user is permitted to undo this
     *            change.
     */
    IMPORT_C void DeleteL(TBool& aChanged,
                          const TCursorSelection& aSelection,
                          TBool aIsBackSpace=EFalse,
                          TBool aAllowUndo=ETrue);
	
    /**
     * Handles errors that occur when handling a change in Edwin’s size. Calls 
     * @c CEikonEnv::NotifyIdleErrorWhileRedrawing().
     */
    IMPORT_C void TrappedSizeChanged();
	
    /**
     * Handles a change in Edwin’s size. This function accounts for text wrap 
     * settings and whether the Edwin is ready to be redrawn and also calls 
     * functions to reformat text and to update the Edwin’s scroll bars.
     */
    IMPORT_C void HandleSizeChangedL();
	
    /**
     * Cancels the selection and any FEP composition text. This function then 
     * repositions the cursor at the specified end of the currently selected 
     * text.
     *
     * @param aEndOfSelectionToLeaveCursor The end of the current selection at 
     *        which the cursor is repositioned.
     */
    IMPORT_C void CancelSelectionL(TEnd aEndOfSelectionToLeaveCursor);
	
    /**
     * Moves the cursor to the beginning of the next word or paragraph. This 
     * function cancels any front end processing transaction currently in 
     * progress for the Edwin.
     *
     * @param aSelect If @c ETrue the chunk is selected, otherwise @c EFalse. 
     * @param aChunkSize The chunk size, this can be either a word or a 
     *        paragraph. See @c TChunkSize enum.
     * @param aEndScanningTowards Which direction to scan towards, the start 
     *        or the end of the document.  
     */
    IMPORT_C void MoveCursorToChunkStartL(TBool aSelect,
                                          TChunkSize aChunkSize,
                                          TEnd aEndScanningTowards);
	
    /**
     * Cancels the insertion of a character format. This can be used for rich 
     * text only.
     */
    IMPORT_C void CancelInsertCharFormat();
	
    /**
     * Copies the contents of the cursor selection onto the clipboard. 
     */
    IMPORT_C void PlaceDataOnClipboardL();
	
    /**
     * Reports an Edwin event of the specified type. The Edwin event is passed 
     * first to the Edwin observer and then to the list of observers, even if 
     * the first Edwin observer is not set. If the Edwin has a custom drawer, 
     * and the event is of type @c EEventFormatChanged, the event is passed to 
     * the custom drawer. If the Edwin has an observer the event is passed to 
     * that observer. If no observer is set for the Edwin, this function passes
     * the event to each observer in the observer list.
     *
     * @param aEventType The type of event to report.
     */
    IMPORT_C void ReportEdwinEventL(MEikEdwinObserver::TEdwinEvent aEventType);
	
    /**
     * Sets margin widths and line cursor width.
     */
    IMPORT_C void SetLineCursorDetailsL();
	
    /**
     * Replaces the current Edwin text.
     *
     * @param aInText Text with which the current text is replaced.
     * @param aOutText On return, the replaced text. 
     */
    IMPORT_C virtual void CopyDocumentContentL(CGlobalText& aInText,
                                               CGlobalText& aOutText);
	
    /**
     * Displays an information message to indicate that the specified text 
     * could not be found. The information message is constructed from 
     * @c R_EIK_TBUF_CANNOT_FIND_TEXT.
     *
     * @param aFindText The text that could not be found.
     */
    IMPORT_C void DisplayFindTextNotFound(TDes& aFindText);
	
    /**
     * Not implemented.
     *
     * @param aStartPos Not used.
     * @param aLength Not used.
     */
    IMPORT_C virtual void HandleTextPastedL(TInt aStartPos,TInt& aLength);
	
    /**
     * Creates a new @c CLafEdwinCustomDrawBase instance.
     *
     * @return Pointer to new custom @c CLafEdwinCustomDrawBase object.
     */
    IMPORT_C virtual CLafEdwinCustomDrawBase* CreateCustomDrawL();
	
    // Avkon editor extensions
    /**
     * Used in @c ConstructFromResourceL(). Sets Avkon editor properties.
     *
     * @param aReader A reader positioned for reading from an EDWIN resource.
     */
    IMPORT_C void ReadAknResourceL(TResourceReader& aReader);

protected: // Internal to Symbian

    /**
     * Creates new text layout.
     *
     * @param aLayDoc Pointer to the @c MLayDoc implementation that is the 
     *        source of the text and formatting information.
     */
	IMPORT_C void CreateLayoutL(MLayDoc* aLayDoc);
	
    /**
     * Creates new instance of @c CGlobalText and text layout based on it. 
     * 
     * @param aParaFormatLayer Paragraph format layer pointer for 
     *        @c CGlobalText constructor.
     * @param aCharFormatLayer Character format layer pointer for 
     *        @c CGlobalText constructor.
     */
    IMPORT_C void CreateTextAndLayoutL(CParaFormatLayer* aParaFormatLayer,
                                       CCharFormatLayer* aCharFormatLayer);
	
    /**
     * Checks that is Edwin's extension created. If not, it will be created.
     *
     * @leave KErrNoMemory If the Edwin FEP support pointer is NULL.
     */
    IMPORT_C void CheckEdwinExtensionL();
	
    /**
     * Gets Edwin's extension.
     *
     * @return Pointer to Edwin's extension. 
     */
    IMPORT_C CEikEdwinExtension* EdwinExtension();

private:

	enum
		{ // internal flags
		EWysiwygOn						=0x00000010,
		EUnderOneScreenFormattedText	=0x00000020,
		EPictureDelimits				=0x00000040,
		EPunctuationDelimits			=0x00000080,
		EPasteFromIrStore				=0x00000100,
		ELockScrollBarState				=0x00000200,
		EOnReformatting					=0x00000400
		};

private: // from CCoeControl

	IMPORT_C void SizeChanged();
	IMPORT_C TInt CountComponentControls() const;
	IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
	IMPORT_C void Reserved_2();

private:

	IMPORT_C virtual void Reserved_3();
	IMPORT_C virtual void NotifyInvalidOperationOnReadOnlyL();
	IMPORT_C CEikScrollBarFrame* CreateScrollBarFrameL(TBool aPreAlloc);
	void SetVirtualCursorStateL(TBool aIsFocused) const;
	void SetHeightForNumOfLinesL();
	void ApplyAutoSelectionL();
	void SetScrollBarsL();
	void SetVertScrollBarModelByCharactersL(TEikScrollBarModel& aVertModel) const;
	void RetrieveDataFromClipboardL();
	void SetCursorVisibilityL(TBool aEmphasis);
	TBool OwnsScrollBars() const;
	void CreateScrollBarFrameLayout(TEikScrollBarFrameLayout& aLayout) const;
	void UpdateHorizScrollBarThumb();
	void UpdateVertScrollBarThumbL();
	void DoSetUndoBufferL(const TCursorSelection& aSelection);
	void DoPasteFromStoreL(const CStreamStore& aStore,const CStreamDictionary& aDict);
	void DoReplaceAllL(SEdwinFindModel* aModel,TBool& aTextFound,TBool& aReplaced);
	void DeleteExtraParasL(TInt aStartPos,TInt aLength);
	TInt LocateChar(TChar aChar,TInt aStartPos,TInt aLength);
	TBool IsValidChar(TInt aChar) const;
	TInt CalcMinimumHeightFromNumOfLinesL() const;
	void CheckEdwinHeight();
	TBool IsNewHeightWithinMinimumAndMaximum(TInt aNewHeight) const;
	void SetEdwinHeight(TInt aHeight);
	void DoCreateCustomDrawL();
	void SetCursorSizeAndType();
	TKeyResponse DoOfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	void DoCcpuCanPasteL() const;
	void DoReportEventL(MCoeControlObserver::TCoeEvent aEvent);
	void CheckIfEdwinIsResizable();
	void SetKeyboardRepeatRate(TTimeIntervalMicroSeconds32 aKeyRepeatRate) const;
	HBufC* GetAllowedCharsLC() const;
	TInt CheckAllowedCharsL(const TDesC& aChars, CClipboard& aClipboard, TBool aRichText) const;

	TInt CursorWidth() const;
	TFontSpec CursorFontSpec() const;

	void BuildEdwinFepSupport();
	void MakeCharFormatLayerMatchL(CCharFormatLayer* aCharFormatLayer);
	void MakeParaFormatLayerMatchL(CParaFormatLayer* aParaFormatLayer);
    void UpdateCache(TInt aId);
	void DrawBackgroundAroundTextView( 
		CWindowGc& gc, 
		const TRect& aOuterRect, 
		const TRect& aInnerRect, 
		const TRgb& aBackgroundColor  ) const;
	TInt CurrentAlignment() const;
	void DoAlignment();
	void NewParagraphL();
    TKeyResponse ScrollReadOnlyNoCursorDisplayL(TUint aKeyCode);
    void ReplaceParaDelimitersL( TInt aStartPos, TInt aLength );
    TRect AdjustedViewRect() const;
    void SetVKBStatus();
    void ScrollViewToCursorLineL();
    void PerformRecordedOperationL();
    void ScrollIfAtTopOrBottomL();
    void SetSelectionVisibilityL(TBool isVisable);
    
    /**
     * Sets scrollbars with kinetic scrolling.
     */
    void SetKineticScrollingScrollBarsL();
    
    /**
     * Sets vertical scrollbar model with kinetic scrolling.
     * 
     * @param aVertModel Vertical scrollbar model 
     */
    void SetKineticScrollingScrollBarModel(
            TEikScrollBarModel& aVertModel ) const;
    
    /**
     * Enables rate scrolling in editor.
     * 
     * @param aEnable ETrue if rate scrolling should be enabled.
     */
    void EnableRateScrolling( TBool aEnable );

private:

	void DrawFirstLineTextL() const;
    CAknEdwinDrawingModifier* AknEdwinDrawingModifier();
    TBool EditorSupportsNeutralProtection() const;

    /**
    * Main routine for neutral protection.  This routine returns a boolean stating if there is a
    * requirement for protection, but also returns the text that should replace the to-be-deleted text.
    * 
    * @param aPosOfLosEndOfDelete   index of the first character deleted
    * @param aLengthToDelete        length the text to be deleted
    * @param aNewText               neutral protection characters to replace the delete 
    * @param aForwardProtectionNeeded EFalse if only reverse protection needed; data valid only if 
    *                               method does not return EFalse.
    * @return                       EFalse iff no deletion is to be performed
    */
    TBool NeedsNeutralProtection( TInt aPosOfLowEndOfDelete, TInt aLengthToDelete, TDes& aNewText, TBool& aForwardProtectionNeeded );

    /**
    * Returns whether the character is strongly directional
    *
    * @param    aChar   character to be examined
    * @param    aRightToLeft    This is valid upon return only if EFalse is not returned. 
    *                           Value is EFalse if the strong directionality is Left-to-right
    * @return   EFalse if the character is not strongly directional.  
    */
    TBool GetStrongDirectionality(TChar aChar, TBool& aRightToLeft ) const;

    /**
    * Returns ETrue if the character at aPos is neutral
    *
    * @param    aPos    index in editor; must be a valid index
    * @return           EFalse iff the character is not neutral
    */
    TBool CharIsNeutral( TInt aPos ) const;

    /**
    * Looks through the passed descriptor, looking for a strongly directional character.  
    * Direction of search can be set. Search starts at the begining if searching forward; 
    * starts at the end if searching backwards.
    * 
    * Search is carried out until a strong character is found or the end (or beginning) 
    * of the descriptor has been reached.
    * 
    * @param aText      Descriptor to search.
    * @param aForward   If EFalse, then search is backward (decreasing index) in logical buffer
    * @param aIsRightToLeft     Set to ETrue on return if first strong character found is RTL
    *
    * @return           EFalse if no strong character was found.
    */
    TBool GetExposedDirectionOfTextInDescriptor( const TDesC& aText, TBool aForward, TBool& aIsRightToLeft ) const;

    /**
    * Looks through the editor's text starting at character aPos, looking for a
    * strongly directional character.  Direction of search can be set.
    * Search is carried out until a strong character is found or the end (or beginning) 
    * of the editor text has been reached.
    * 
    * @param aPos       First character to look at
    * @param aForward   If EFalse, then search is backward (decreasing index) in logical buffer
    * @param aIsRightToLeft     Set to ETrue on return if first strong character found is RTL
    *
    * @return           EFalse if no strong character was found.
    */
    TBool GetExposedDirectionOfText( TInt aPos, TBool aForward, TBool& aIsRightToLeft ) const;

    /**
    * Routine to perform the operation of replacing a selection with new text. 
    * This is intended for internal use.
    * 
    * The current selection, if non-zero length is deleted, and replace with aNewText if non-zero length
    * iTextView must be set.
    * 
    * @param aNewText               Replacement text. May be zero length.
    * @param aCursorPosInNewText    This is the position, relative to the beginning of the newtext,
    *                               that you want the cursor to be at when the operation is complete
    * @param aFormatHasChanged  Set this to ETrue if you want the reformatting to start at
    *                           the beginning of the paragraph. EFalse if just to reformat the line.
    *                           This variable may also be set by the call to DeleteHighlight that this
    *                           code executes, so it may be set to ETrue upon return, even if EFalse was
    *                           passed.
    */
    void ReplaceSelectionWithTextL( const TDesC& aNewText, 
                                    TInt aCursorPosInNewText,
                                    TBool& aFormatHasChanged );

    /**
    * Returns EFalse iff ( phone number had only numeric input modes AND the keymap is a phone number
    * type keymap ). 
    * Phone number type keymaps are:
    *   EAknEditorStandardNumberModeKeymap
    *   EAknEditorFixedDiallingNumberModeKeymap
    *
    * @return       EFalse if the phone number will only contain a pure phone number
    */
    TBool IsPurePhoneNumberEditor() const;

    /**
    * Standard check on upper and lower formatting thresholds versus current textview formatting mode.
    *
    * @return       EFalse iff the formatting mode does not need changing
    */ 
    TBool NeedToChangeFormattingModeL() const;         	
    
    /**
    * When Band formatting is started, this should be called to update the cached
    * metrics used for the scroll bar calculations.
    */
    void CalculateLineMetricsForBandFormattingL();
    
    /**
     * check the selection content is visible character or not 
     */
    TBool IsSelectionVisible();


protected:	// from MObjectProvider

    /**
     * From @c MObjectProvider.
     *
     * Retrieves an object of the same type as that encapsulated in @c aId.
     *
     * This function is used to allow controls to ask their owners for access 
     * to other objects that they own.
     *
     * Other than in the case where NULL is returned, the object returned must 
     * be of the same object type - that is, the @c ETypeId member of the 
     * object pointed to by the pointer returned by this function must be equal
     * to the @c iUid member of @c aId.
     *
     * @param aId An encapsulated object type ID.
     * @return Encapsulates the pointer to the object provided. Note that the
     *         encapsulated pointer may be NULL.
     */
	IMPORT_C TTypeUid::Ptr MopSupplyObject(TTypeUid aId);
	
public: // new since 3.0

    /**
     * Sets skin id for text.
     * 
     * @param aAknSkinIdForTextColor The skin id.
     */
    IMPORT_C void SetTextSkinColorIdL(TInt aAknSkinIdForTextColor);

    /**
     * Sets highlight style.
     *
     * @param aStyle The highlight style.
     */
    IMPORT_C void SetHighlightStyleL(TAknsHighlightStyle aStyle);
    
    // for custom drawer, not exported
    /**
     * Gets skin id.
     * 
     * @return The skin id.
     */
    TInt SkinColorId() const;

    /**
     * Gets highlight style.
     * 
     * @return The highlight style.
     */
    TAknsHighlightStyle HighlightStyle() const;
    
    /**
    * Called to determine the background color to draw. It is not to be used if skinning is
    * being used to draw the background.
    * 
    * This API can be used two ways: 
    * 
    * i) If the caller has a default color to offer (to be used as 
    * a fallback if SetBackgroundColorL has not been called), then he should use the 
    * Input/Output parameter aConditionalColor, and ignore the return value. The output
    * parameter will only be over-written by the set background color if SetBackgroundColorL
    * has been called.
    * 
    * ii) If the caller does not have a default color to offer, then he should pass in a dummy
    * input parameter and use the return value. 
    * 
    * @param    aConditionalColor   Output parameter. Returns a color set by 
    *                               SetBackgroundColorL. It is unchanged if 
    *                               background color has not been set by SetBackgroundColorL
    * @return   TRgb for the color to be used for background.
    */
    TRgb EditorBackgroundColor(TRgb& aConditionalColor) const;

public:
    /**
     * Can be used by custom drawers to check if background drawing should be
     * performed. This is meant to be used only if editor has
     * MCoeControlBackground object attached.
     *
     * @return ETrue if custom drawer shouldn't draw background.
     */
    TBool SkipBackgroundDrawer() const;
    
    /**
     * Scrolls view by amount of pixels.
     * Stops scrolling when beginning or end of content exceeded.
     * This function should be used when scrolling starts from inside content
     * (in other words in normal situation when begin- or end-border has not
     * yet exceeded) 
     *
     * @param   aPixelsToScroll Amount of pixels to scroll
     * @param   aBorderExceeded returns ETrue if border was exceeded
     * @param   aRestOfPixels   Amount of pixels not scrolled because border
     *                          was exceeded  
     *
     * @return Amount of scrolled pixels.
     */
    TInt ScrollView( TInt aPixelsToScroll, TBool& aBorderExceeded,
            TInt& aRestOfPixels );
    
    /**
     * Scrolls view by amount of pixels.
     *
     * This function should be used to scroll when we have already
     * exceeded begin- or end-border (we are out of borders).
     * This function supports scrolling so that there can be empty space
     * above or below the editor content (used in bounce effect).
     * Stops scrolling when we return back to inside borders.
     *
     * @param   aPixelsToScroll Amount of pixels to scroll
     * @param   aEndOfBounce    returns ETrue if content scrolled back
     *                          to inside of borders
     * @param   aRestOfPixels   Amount of pixels not scrolled
     *
     * @return Amount of scrolled pixels.
     */
    TInt ScrollViewWithBounce( TInt aPixelsToScroll, TBool& aEndOfBounce,
            TInt& aRestOfPixels );
    
    /**
     * Returns amount of pixels how much we are out of borders.
     *
     * @return Amount of pixels scrolled out of borders.
     */
    TInt PixelsOutOfBorder() const;
    
    /**
     * Handles scrollbar events with kinetic scrolling.
     *
     * @param aScrollBar The scrollbar.
     */
    void HandleScrollEventWithPhysics( CEikScrollBar* aScrollBar );
	
	 /**
     * If cursor is visible, disables it and stores cursor visibility info.
     */
    void StoreCursorState();
    
    /**
     * Show cursor again if needed (based on stored cursor visibility info).
     */
    void RestoreCursorState();
    
    /**
     * Returns ETrue if kinetic scrolling is enabled.
     *
     * @return ETrue if kinetic scrolling is enabled.
     */
    TBool KineticScrollingEnabled() const;

	
protected:

    /**
     * Edwin user flags.
     */
	TUint32 iEdwinUserFlags;

    /**
     * Internal Edwin flags.
     */
	TUint32 iEdwinInternalFlags;

    /**
     * Edwin's text content.
     */
	CPlainText* iText;

protected: // Internal to Symbian

    /**
     * Edwin's text view.
     */
	CTextView* iTextView;

    /**
     * Edwin's text layout.
     */
	CTextLayout* iLayout;

protected:

    /**
     * Maximum length ot the edwin.
     */
	TInt iTextLimit;
    
    /**
     * Number of lines in Edwin.
     */
	TInt iNumberOfLines;
	
    /**
     * Current zoom factor.
     */
    MGraphicsDeviceMap* iZoomFactor;
	
    /**
     * Cursor position.
     */
    TInt iLastPointerDocPos;
	
    /**
     * Edwin's margins.
     */
    TMargins8 iMargins;

private:

	friend class CEikEdwinFepSupport;
	friend class CEikEdwinExtension;
	// added this class to allow additional data members without breaking BC
	CEikEdwinExtension* iEdwinExtension; // replaced iSetScrollBar
	CEikScrollBarFrame* iSBFrame;
	MEikEdwinObserver* iEdwinObserver;
	CArrayPtr<MEikEdwinObserver>* iObserverArray;
	CEikEdwinFepSupport* iEdwinFepSupport;
	CUndoBuffer* iUndoStore;
	TInt iAvgLinesInViewRect;
	TInt iAvgCharsPerLine;
	TInt iRightWrapGutter;
	TInt iLayoutWidth;
	MEikEdwinSizeObserver* iEdwinSizeObserver;
	TInt iMinimumHeight;
	TInt iMaximumHeight;
/* 
iMaximumHeightInLines
---------------------
This is simply a holder for the number, used to simplify some Avkon LAF requirements.
The viewable region of an edwin is actually measured in pixels, However, if certain LAF
requirements are enforced (that the view region has to be smaller than the number of 
lines viewable * the baseline separation (in pixels)) some undesired scrolling effects
occur.


That is to say, by simply setting iMaximumHeightInLines, this will not affect
the actual maximum height of the edwin.  To do this, you must set the iMaximumHeight

One of the use cases of this member variable is for AknLayoutUtils::LayoutEdwin. 
That method uses iMaximumHeightInLines along with the baseline separation, to set 
the iMaximumHeight.

The general formula is very simple, to remove unneeded scrolling.
iMaximumHeight=baselineSeparation*iMaximumNumberOfLines

If you cannot allocate sufficient space to the edwin, to permit so much viewable region
then the method AlterViewRect can be called on the TextView() component.  This will introduce
a clipping rectangle, which allows blank space required by the edwin layout component
to not be shown.
*/
	TInt iMaximumHeightInLines; 
	CLafEdwinCustomDrawBase* iCustomDrawer;
	TInt iLastPointerAnchorPos;
	CAknCcpuSupport* iCcpuSupport;
	CCharFormatLayer* iCharFormatLayer;
	CParaFormatLayer* iParaFormatLayer;
	TInt iSpare_1;
	TInt iSpare_2;
	};


inline CEikScrollBarFrame* CEikEdwin::CreatePreAllocatedScrollBarFrameL()
	{ return CreateScrollBarFrameL(ETrue);}
inline CEikScrollBarFrame* CEikEdwin::ScrollBarFrame()
	{ return ((CEikScrollBarFrame* const)iSBFrame); }
inline TInt CEikEdwin::AvgLinesInViewRect() const
	{ return iAvgLinesInViewRect; }
inline TInt CEikEdwin::AvgCharsPerLine() const
	{ return iAvgCharsPerLine;}
inline void CEikEdwin::SetAvgLinesInViewRect(TInt aAvgLines)
	{ iAvgLinesInViewRect=aAvgLines; }
inline void CEikEdwin::SetAvgCharsPerLine(TInt aAvgChars)
	{ iAvgCharsPerLine=aAvgChars; }

inline void CEikEdwin::SetMaxLength(TInt aLength ) 
	{ SetTextLimit(aLength); }
inline TInt CEikEdwin::MaxLength() const 
	{ return iTextLimit; }

#endif
