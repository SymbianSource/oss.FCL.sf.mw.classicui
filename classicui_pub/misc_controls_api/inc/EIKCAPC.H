/*
* Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
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


#if !defined(__EIKCAPC_H__)
#define __EIKCAPC_H__

#if !defined(__COECNTRL_H__)
#include <coecntrl.h>
#endif

#if !defined(__FEPBASE_H__)
#include <fepbase.h>
#endif

#if !defined(__EIKLABEL_H__)
#include <eiklabel.h>
#endif

#include <eikdialg.h>
#include <eikdpage.h>

#include <AknControl.h>
#include <aknsconstants.h>

class CEikImage ;
class CEikDialogPage;
// Forward declaration of types used in layout routines.
class CAknPopupField;
class CAknSlider;
class CEikEdwin;
class CEikMfne; 
class CEikSecretEditor;
class CEikCapCLabel ;
class CEikCapCExtension;
class MPointerEventObserver;
class MAknsControlContext;

/** CaptionedControl
 *
 * CaptionedControl is part of the dialogs. All dialogs and forms use captionedcontrol
 * as a control for one DLG_LINE. Each DLG_LINE has one captionedcontrol in it.
 * 
 * Rectangle of the captionedcontrol is single form field / form line or DLG_LINE's
 * rectangle dependent on the dialog type.
 */
class CEikCaptionedControl : public CAknControl, public MCoeCaptionRetrieverForFep, public MCoeControlObserver
    {
    friend class CEikCapCExtension;
public:
    enum TSpaceSharingFlags
        {
        EIfTooSmallCtlGetsWidthLast         =0x0,
        EIfTooSmallCtlGetsWidthFirst        =0x1,
        EIfTooSmallCtlGetsEqualShareOfWidth =0x2,
        EIfTooBigCtlStaysMinHeight          =0x4,
        EIfTooBigCtlStaysMinWidth           =0x8,
        EIfTooBigCtlStaysMinSize            =0xc,
        EIfTooSmallDontStrech               =0x10
        };
    enum TCaptionExpandingState
        {
        EInitial = 0,
        EExtended =1,
        ERetracted =2
        };

public:
 	/** Constructor
 	 */	
    IMPORT_C CEikCaptionedControl();
    /** Destructor
     */
    IMPORT_C ~CEikCaptionedControl();
public: // new functions
	/** SetUsesEars() sets a flag Uses Ears.
	 */
    IMPORT_C void SetUsesEars();
    /** SetSpaceSharingFlags() sets flags for space sharing
     */
    IMPORT_C void SetSpaceSharingFlags(TInt aFlags);
    /** SetExtraAscent() modifies layout to include extra ascent for fonts
     */
    IMPORT_C void SetExtraAscent();
    /** SetCaptionL() Sets label of the DLG_LINE
     * @param aText Descriptor
     */
    IMPORT_C void SetCaptionL(const TDesC& aText);
    /** SetTrailerL() Sets trailer
     * Should not be used
     * @param aText Descriptor
     */
    IMPORT_C void SetTrailerL(const TDesC& aText);
	/** Sets the captionedcontrol to be currently focused or not
     * @param aSelected whether captionedcontrol is focused
	 */
    IMPORT_C void SetCurrent(TBool aSelected);
	/** Updates captionedcontrol's dimmed state
	 */
    IMPORT_C void CheckDimmedDisplayState();
	/** Sets minimumsizes to zero
	 */
    IMPORT_C void ResetMinimumSizes();
	/** Whether captionedcontrol is latent
	 *
	 * @return true if is latent
	 */
    IMPORT_C TBool IsLatent() const;
	/** Sets captionedcontrol latent status
	 */
    IMPORT_C void SetLatent(TBool aLatent);
	/** Whether captionedcontrol has latent group following it
     * @returns true if has latent group following
	 */
    IMPORT_C TBool LatentGroupLineFollows() const;
	/** Sets latent group following flag
     * @param aLglf true if latent group following
	 */
    IMPORT_C void SetLatentGroupLineFollows(TBool aLglf);
	/** Whether there is a divider after the captionedcontrol
	 */
    IMPORT_C TBool DividerAfter() const;
    /** Sets divider after the captionedcontrol
     */
    IMPORT_C void SetDividerAfter(TBool aDividerAfter);
    /** Whether captionedcontrol consumes enter key
     */
    IMPORT_C TBool TakesEnterKey() const;
    /** Sets captionedcontrol to take enter key
     * @param aTakesEnter true if takes enter key, false if not
     */
    IMPORT_C void SetTakesEnterKey(TBool aTakesEnter);
    /** Whether offers hot keys
     * @return boolean true if offers hotkeys
     */
    IMPORT_C TBool OfferHotKeys() const;
    /** Sets captionedcontrol to offer hotkeys
     */
    IMPORT_C void SetOfferHotKeys(TBool aOffer);
    

    /**
     * From MCoeControlObserver:
     * Acts upon changes in the hosted control's state. 
     * 
     * This class's implementation handles events from MFNE editor editing
     * buttons in touch enabled builds
     *
     * @param	aControl	The control changing its state (not used)
     * @param	aEventType	The type of control event 
     */
	IMPORT_C virtual void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
	
public:
    TInt MaximumNumberOfControlLinesOnVisiblePage() const;
	TInt NumberOfLines() const;
	TInt NumberOfLinesForScrollBar() const;
public:
    TBool ControlIsAnEdwin(TInt aControlType) const;
    TBool ControlIsAMfne(TInt aControlType) const;
    TBool ControlIsAPopfield(TInt aControlType) const;
    TBool ControlIsASecretEditor(TInt aControlType) const;
    TBool ControlIsASlider(TInt aControlType) const;
    TBool ControlIsAColourSelGrid(TInt aControlType) const;
	TInt ControlType() const;

public: // from CCoeControl
    /** MinimumSize() returns minimum size of the control
     */
    IMPORT_C TSize MinimumSize();
    /** ConstructFromResourceL() constructs the captionedcontrol from DLG_LINE resource
     *
     * usually called with the following code:
     * TResourceReader reader;
     * iCoeEnv->CreateResourceReaderLC(reader, resId);
     * control->ConstructFromResourceL(reader);
     * CleanupStack::PopAndDestroy();
     */
    IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
    /** OfferKeyEventL() handles key events
     */
    IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
    /** GetColorUseListL() gets color use list
     */
    IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
    /** HandleResourceChange handles several kinds of resource change event
     */
    IMPORT_C virtual void HandleResourceChange(TInt aType);         // not available before Release 005u
    /** Provides ability to get input capabilities needed for fep
     */
    IMPORT_C TCoeInputCapabilities InputCapabilities() const;
    /** SetDimmed sets captionedcontrol to dimmed state
     */
    IMPORT_C void SetDimmed(TBool aDimmed);
    /** HandlePointerEventL handles touch pointer events
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
public:
    void RegisterPageWithCaptionControl(CEikDialogPage* aPage);

public: // internal layout properties
	//void SetProperties(const TRegion &aRegion, const RArray<TCapCProperty> &aProperties);
	//TRect Line(TInt aLineIndex); // text line rectangles
	//TInt LineIndex(TPoint aPoint);
	//TPoint LineControlPoint(TInt aLineIndex);
	//RArray<TInt> LineIndexesIntersecting(TRect aRect);
	//void SetProperty(TInt aLine, TCapCProperty &aProperty);
	//void ClearProperty(TInt aLine, TCapCProperty &aProperty);
	//TCapCProperty Properties(TInt aLine);
	//void LineRegions(TRegion &aRegion);
	//void SetVisibleArea(TRect aRect);
	//void RemoveVisibleArea();
private: // from CCoeControl
    IMPORT_C TInt CountComponentControls() const;
    IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
    IMPORT_C void SizeChanged();
    IMPORT_C void FocusChanged(TDrawNow aDrawNow);
protected: // from CCoeControl
    IMPORT_C void Draw(const TRect& aRect) const;
    IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
    IMPORT_C void Reserved_2();
    // from MCoeCaptionRetrieverForFep
    IMPORT_C virtual void GetCaptionForFep(TDes& aCaption) const;
    IMPORT_C virtual void MCoeCaptionRetrieverForFep_Reserved_1();
    IMPORT_C virtual void MCoeCaptionRetrieverForFep_Reserved_2();
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );

protected: // from MObjectProvider
    IMPORT_C TTypeUid::Ptr MopSupplyObject(TTypeUid aId);

public:
    /** SetToolTipTextL() sets tooltip text
     * @param aText descriptor for tooltip text
     */
      
    IMPORT_C void SetToolTipTextL( const TDesC& aText ) ;
    /** Ability to query tooltip text string
     */
    IMPORT_C const TDesC* ToolTipText() const ;
    /** SetBitmapFromFileL() sets icon contents for the captionedcontrol
     */
    IMPORT_C void SetBitmapFromFileL( const TDesC& aFilename,TInt aMainId,TInt aMaskId =-1 ) ;
    /** SetEditable sets captionedcontrol to editable state
     */
    IMPORT_C void SetEditableL( TBool aEditable, TBool aShowEmptyFields = ETrue ) ;
    
    IMPORT_C void SetFormFlags( TInt aFlags ) ;
    void GetAknLayoutValuesL() ;  // Visible within DLL only.
    TBool HasSeparator() const;
    /** GetFullCaptionText() gets caption descriptor
     *
     */
    IMPORT_C const TPtrC GetFullCaptionText() const;
    TBool   IsDisplayable() const;
    /** 
     * Allows clients of CEikCaptionedControl to turn off drawing 
     * of white background of captionedcontrol.
     *
     * @since 2.1
     */
    IMPORT_C void SetDrawNoWhiteBackground(TBool aEnabled); // for list queries with find.

    /**
    * In case of an editor control residing in a form,
    * sets up a pictograph animation callback to redraw the form highlight
    * control when pictograph animations are updated.
    */
    void SetPictographCallBack();
    
    /**
    * Sets icon and sets its size.
    * @param aBitmap a bitmap which has already been loaded. Must not be NULL.
    * @param aMask a mask bitmap which has already been loaded. Can be NULL.
    * Takes ownership of the bitmap objects.
    * @since 2.8
    */
    IMPORT_C void SetIconL( CFbsBitmap* aBitmap, CFbsBitmap* aMask ); 

    /**
     * Sets one of the two small indicator icons
     * @param aIcon a index 0 or 1 depending on which icon to set
     * @param aBitmap a bitmap pointer or NULL
     * @param aMask a mask pointer or NULL
     */
	IMPORT_C void SetIndicatorIconL( TInt aIcon, CFbsBitmap *aBitmap, CFbsBitmap *aMask );

    /** SetPointerEventObserver
     * Low level observer for touch related pointer events.
     * This can be used to receive low level pointer events.
     */
	IMPORT_C void SetPointerEventObserver(MPointerEventObserver *aObserver);
	MPointerEventObserver *PointerEventObserver() const;
	
    /** Sets the captionedcontrol to be currently focused or not.
     * @param aSelected whether captionedcontrol is focused
     * @param aRedraw whether redraw is needed or not
     */    
    void SetCurrent(TBool aSelected, TBool aRedraw );
    
protected:
    TRect ViewRect() const;
    TRect EditRect() const;

private:
    enum TWhichEars
        {
        ENoEar=0x00,
        ELeftEar=0x01,
        ERightEar=0x02,
        EBothEars=0x03
        };
private: // new functions
    TInt WidthForEars(TInt aWidthRemaining) const;
    void DrawEarsNow(TWhichEars aEar) const;
    void DrawEars(TWhichEars aEar) const;
    void DrawSingleEar(TWhichEars aEar,TBool aPressed) const;
    TRect EarRect(TWhichEars aEar) const;
    void FireEarL(TWhichEars aEar,TInt aEarRepeat);
    TInt SquashComponentWidth(TInt& aTotalWidth,const TInt aComponentWidthHint);
    void StretchComponents();
    void SetVertEdgeSpacing( TInt aVertEdgeSpacing );
    void SetHorzEdgeSpacing( TInt aHorzEdgeSpacing );
    void SquashComponents();
    void CalculateNumberOfLinesForControl( TInt aLines ) ;
    void SizeDialogComponents() ;
    void PositionDialogComponents() ;
    static TInt PictographAnimationCallBack( TAny* aPtr );
    /**
    * Sets a size for a bitmap that has already been loaded.
    * @since 2.8
    */    
    void SetIconSizeL(CFbsBitmap* aBitmap);
    /**
    * Gets control context for the given control
    * @param aDialog a dialog to get context for
    * If aDialog provided does not exist, TODO
    */
    MAknsControlContext* GetDialogControlContext(const CCoeControl* aDialog) const;

    /**
     * Searches recursively for control's parents until it finds a window owning control
     */
    const CCoeControl* WindowOwningParent() const;

public:
    /**
     * Positions form components in accordance with dialog page flags. 
     * If the dialog instance is not registered, them flags set with SetFormFlags() are used. 
     */	
    void PositionFormComponents();
    void ScrollBackEditor();
    
public:
    void DrawClosingLine() const;
	const CEikDialogPage* DialogPage() const { return iDialogPage; }
	void SetPartiallyVisible( TBool aPVisible );
    TBool PressedDownState() const;
	void SetPressedDownState( TBool aPressed );
private:
    TSize EditorControlSize() const ;
    void SetElementBrushColorsL( TRgb aColor ) ;
    void SetElementTextColorsL( TRgb aColor ) ;

    TBool ShowBitmap() const;
    void  LayoutBitmap(const TRect& aRect);
    void  LayoutCaption(const TRect& aRect);
    void DoFormCaptionSettingsL(const TDesC& aText);
private:
    static void FormLayoutControlBitmap(CEikImage* aBitmap, const TRect& aParent, TBool aIsEditable, TBool aSingleLayout, TInt aNumberOfLines);
    void FormLayoutControlEdwin(CEikEdwin* aEdwin, const TRect& aParent, TBool aIsEditable, TBool aSingleLayout, TInt aNumberOfLines, TBool aBitmapPresent, TBool aIsFocused);
    void FormLayoutControlLabel(CEikLabel* aSlider, const TRect& aParent, TBool aIsEditable, TBool aSingleLayout, TInt aNumberOfLines, TBool aLayoutWithBitmap, TBool aIsFocused, TInt aIconCount);
    void FormLayoutControlMfne(CEikMfne* aMfne,  const TRect& aParent, TBool aIsEditable, TBool aSingleLayout, TInt aNumberOfLines, TBool aBitmapPresent, TBool aIsFocused );
    void FormLayoutControlPopfield(CAknPopupField* aPopfield, const TRect& aParent, TBool aIsEditable, TBool aSingleLayout, TInt aNumberOfLines, TBool aBitmapPresent, TBool aIsFocused);
    void FormLayoutControlSecretEditor(CEikSecretEditor* aSecretEd, const TRect& aParent, TBool aIsEditable, TBool aSingleLayout, TInt aNumberOfLines, TBool aBitmapPresent, TBool aIsFocused );
    static void FormLayoutControlSlider(CAknSlider* aSlider, const TRect& aParent, TBool aIsEditable, TBool aSingleLayout, TInt aNumberOfLines, TBool aBitmapPresent);
    static void ConvertViewRectToEditRect(TRect& aRect);
    static void ConvertEditRectToViewRect(TRect& aRect);

    /*	
    *
    * Access method for use in a CAknForm context. 
    *
    * @return   Enumeration for layout for the CAknForm
    *           Layout value is received from owning CEikDialogPage, if it is not defined then EEikFormUseDoubleSpacedFormat flag is checked.
    *           Default value is CEikDialogPage::ESingle
    */
    CEikDialogPage::TFormLayoutSelection FormLayout() const;

    /**
    * Draws the separator between (at the top of current ) caption control(s)
    *
    * @param    gc  Current graphics contect
    */
    void DrawFormSeparator( CWindowGc& gc ) const;

    /**
    * Constructs the extension object.
    * There is no base constructL, so it is necessary to call this in several places
    */
    void ConstructExtensionL() ;

    void DrawAsSkinnedForm( CWindowGc& aGc, const TRect& aRect ) const;
    void LayoutSkinControlContexts();
    TBool DrawingSkins() const;
    void DrawAsForm( const TRect& aRect ) const;
    void DrawAsEikonDialog( const TRect& aRect ) const;
    void DrawAsFormInEditMode( const TRect& aRect ) const;
    void DrawAsFormInViewMode( const TRect& aRect ) const;
    void DrawAsFormUnFocusedLine( const TRect& aRect ) const;
    
    /**
     * Returns correct text color index.
     *
     * @since S60 5.2
     * @return Text color index.
     */
    TAknsQsnTextColorsIndex TextColorIndex() const;

public:
    CCoeControl* iControl;
    CEikCapCLabel* iCaption;
    HBufC* iCaptionText;

    CEikLabel* iTrailer;
    TInt iId;
    TInt iControlType;
    TAny* iReturnValue;
    TBool iIsFormControl ;
    CEikImage* iBitmap ;
    TBool iIsEditable ;

private:
    TBool iHasAppendedEditIndicator;
    TSize iMinSize;
    TInt  iCapCFlags;
    TInt  iCaptionWidth;
    TInt  iFullWidth;
    TSize iNormalSize ;
    HBufC*iToolTipText ;
    TBool iDoNotDisplay ;

    TInt iVertEdgeSpacing ;
    TInt iHorzEdgeSpacing ;
    TInt iOriginalHeight ;

    TSize iEditorControlSize ;
    TInt iNumberOfLines ;

    friend class CEikCapCArray;

    enum { ENotSupplied = -1 } ;
    TInt iFlags ;

    TBool iRefresh ;

    TInt iCaptionFontId ;
    TInt iEditorFontId ;
    TInt iVerticalLineXPosition; //iAknTopSpacing ;         
    CCoeControl* iHighlightControl;
    CEikCapCExtension* iExtension ;  // BC extension for additional Data members.
    TInt iAknFormControlHeight ;
    TInt iAknFormControlWidth ;
    TInt iPenColor ;
    TInt iShadowColor ;
    TBool iIsCurrentLine;
    CEikDialogPage* iDialogPage;


    };


/*
 * Special Label Class which appends colon to label text
 */

NONSHARABLE_CLASS(CEikCapCLabel) : public CEikLabel
    {
public :
    CEikCapCLabel() ;
    ~CEikCapCLabel() ;

    TBool ColonEnabled() const ;
    void EnableColon( TBool aEnable ) ;

protected :
    void Draw(const TRect& aRect) const ;
    void DrawL(const TRect& aRect) ;

private:
    TBool iIsColonEnabled ;
    } ;

class MPointerEventObserver
	{
public:
	virtual bool PointerEvent(CEikCaptionedControl *aControl, const TPointerEvent& aPointerEvent)=0;
	};

#endif
