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


#if !defined(__EIKDPAGE_H__)
#define __EIKDPAGE_H__

#include <coeccntx.h>
#include <eiksbfrm.h>
#include <coecobs.h>
#include <eikedwob.h>
#include <AknPopupFieldText.h>
#include <AknControl.h>

//
// Forward declarations.
//

class CEikCapCArray;
class CEikCaptionedControl;
class CEikDialogPageContainer;
class CEikEdwin;
class CEikLabel;
class MEikDialogPageObserver;
struct SEikControlInfo;
class CAknLayoutData;
class CDialogPageExtension;

class CEikFormAnim;
class MEikFormAnimObserver;
class CAknPaneScroll;
class CAknFormPhysics;

/**
 * The CEikDialogPage class implements a scrollable dialog page control.
 *
 * @internal
 * @since ER5U
 */
NONSHARABLE_CLASS(CEikDialogPage) :
    public CAknControl,
    public MCoeControlObserver, 
    public MEikScrollBarObserver, 
    public MEikEdwinSizeObserver,
    public MAknPopupFieldObserver,
    public MEikEdwinObserver
    {
public:
    enum TFocusNavigationMode
        {
        ECyclic,
        ENonCyclic
        };
    enum TAScrollBarBreadthAllocationMode
        {
        ENone                                   =0x0000,
        EScrollBarBreadthPreAllocated           =0x1000
        };
    /**
    * Enumeration to express what layout is currently being used. Note that the use of 
    * bitmaps on the left is controlled by D
    *
    */
    enum TFormLayoutSelection
        {
        ESingle,
        EDouble
        };

    /** 
     * Used with iFormFlags to indicate where optimisations may or may not occur.  
     * Uses bits above 0x100 as those below are used as static form flags for configuration by resource file.
     */
    enum TDynamicFormFlags
        {
        EFormResizeOptimisationFlag = 0x100 ,
        EFormForceEdwinResizeFlag = 0x200
        } ;

public:
    ~CEikDialogPage();
    static CEikDialogPage* NewL(TInt aId,RWindow& aViewWin,CEikScrollBarFrame& aSBFrame,const CEikDialogPageContainer& aParent,MEikDialogPageObserver* aPageObserver);
    static CEikDialogPage* NewLC(TInt aId,RWindow& aViewWin,CEikScrollBarFrame& aSBFrame,const CEikDialogPageContainer& aParent,MEikDialogPageObserver* aPageObserver);
    static CEikDialogPage* NewL(TInt aId,RWindow& aViewWin,CEikScrollBarFrame& aSBFrame,const CEikDialogPageContainer& aParent,MEikDialogPageObserver* aPageObserver,TResourceReader& aReader);
    static CEikDialogPage* NewLC(TInt aId,RWindow& aViewWin,CEikScrollBarFrame& aSBFrame,const CEikDialogPageContainer& aParent,MEikDialogPageObserver* aPageObserver,TResourceReader& aReader);
    void SetDataPosition( TInt aTopY, TInt aBottomY, TBool aForceResize );
    TSize PreferredSize() const;
    void SetActiveL();
    void SetActiveAndFocusL();
    void SetInactiveL();
    TInt PageId() const;
    TInt LineId(const CCoeControl& aControl) const;
    TBool SetInitialFocus();
    CCoeControl* CreateLineByTypeL(const TDesC& aCaption,TInt aLineId,TInt aControlType,TAny* aReturnValue);
    CCoeControl* Control(TInt aLineId) const;
    CCoeControl* ControlOrNull(TInt aLineId) const;
    TInt ControlHeight(TInt aLineIndex) const;
    CEikCaptionedControl* Line(TInt aLineId) const;
    CEikCaptionedControl* LineOrNull(TInt aLineId) const;
    CEikCaptionedControl* CurrentLine() const;
    void SetDensePacking(TBool aDensePacking);
    void InsertLineL(TInt aPosition,TInt aResourceId);
    void DeleteLine(TInt aLineId,TBool aRedrawNow);
    void AdjustAllIds(TInt aControlIdDelta);
    TInt FocusLineL(TInt aLineId);
    TInt FocusedLineId() const;
    void GetAutoValues();
    TKeyResponse OfferUpDownKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType,TFocusNavigationMode aFocusNavigationMode);
    TBool OwnsLine(TInt aLineId) const;
    void ResetLineMinimumSizes();
    TInt FindLineIndex(const CCoeControl* aControl) const;
    TBool RotateFocusByL(TInt aDelta);
    TKeyResponse OfferHotKeysKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
    TBool TakesEnterKey();
    TInt LineIndex(TInt aLineId);
    void ReportPageChangedL();
    TInt GetFormFlags() const;
    void SetFormFlag( TInt16 aFlag, TBool aEnable ) ;  // used with TDynamicFormFlags
    void ConstructFormFromResourceL( TResourceReader& aReader ) ;
    void SetEditableL( TBool aEditable, TBool aActivePage ) ;
    TBool IsEditable() const;
    TBool IsForm() const;

	void SetDoubleQuery(TBool aIsDoubleQuery);

    CEikFormAnim* AcquireAnim( TBool aAcquire, MEikFormAnimObserver* aObserver ) const;

public:
    void UpdateScrollBarL();
    TBool LineHandlerCalled() const;

public: // from CCoeControl
    TSize MinimumSize();
    virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
    virtual void HandleResourceChange(TInt aType);
    virtual void PrepareForFocusLossL();
    virtual void SetDimmed(TBool aDimmed);
    virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
public: // from MCoeControlObserver
    virtual void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
public: // from MEikEdwinSizeObserver
    virtual TBool HandleEdwinSizeEventL(CEikEdwin* aEdwin, TEdwinSizeEvent aEventType, TSize aDesirableEdwinSize);
public: // from MEikEdwinObserver
    virtual void HandleEdwinEventL(CEikEdwin* aEdwin,TEdwinEvent aEventType);

public: // from MAknPopupFieldObserver
    virtual void HandlePopupFieldEventL(CAknPopupField* aPopupField, TAknPopupFieldEvent aEventType, TInt aHint);
public: 
    void SetPageContainer(const CEikDialogPageContainer* aPageContainer);
    const CEikDialogPageContainer* PageContainer() const;
protected: // from CCoeControl
    void WriteInternalStateL(RWriteStream& aWriteStream) const;
    void SizeChanged();
    TInt CountComponentControls() const;
    CCoeControl* ComponentControl(TInt aIndex) const;
    void FocusChanged(TDrawNow aDrawNow);
    void Draw(const TRect& aRect) const;
public:
    // added to allow Form format to be set by API
    IMPORT_C void SetFormLayout(TFormLayoutSelection aLayout);
    IMPORT_C TFormLayoutSelection FormLayout() const;
public:
public:
    TBool IsAtOrOffTopOfPage(const CCoeControl* aControl) const;
    TBool IsAtOrOffBottomOfPage(const CCoeControl* aControl) const ;
public:
    TBool VisibleSizeOnPage(TInt& aHeightOfControlVisibleOnPage, const CCoeControl* aControl) const;
    
    /**
     * Scrolls cached drawing commands by @c aDelta pixels in y direction.
     * 
     * @param  aDelta     A y-asix base on the sliding control's coordinate.
     * @param  aDebugMsg  Not used.
     * @param  aDrawNow   Whether or not the view should be drawn.  
     */
    void ScrollCacheByPixels( TInt aDelta,
                              const TDesC& aDebugMsg,
                              TBool aDrawNow = ETrue );
    
    /**
     * Updates line's cached drawing commands.
     */
    void UpdateLineInCache( CEikCaptionedControl* aLine );
    
    /**
     * Physics simulation ended.
     */
    void Synchronize();

    /**
     * Can be used to query whether highlight graphics should be drawn.
     *
     * @since S60 5.2
     * 
     * @return ETrue if highlight should be drawn.
     */
    TBool HighlightVisible() const;
    
protected: // from MEikScrollBarObserver
    virtual void HandleScrollEventL(CEikScrollBar* aScrollBar,TEikScrollEvent aEventType);

private: // new functions
    void AfterAddingNewLinesL(TInt aNewLineAdded);

    CEikDialogPage(TInt aId,RWindow& aViewWin,CEikScrollBarFrame& aSBFrame,MEikDialogPageObserver* aPageObserver);
    void ConstructL();
    void ConstructFromResourceL(TResourceReader& aReader, TBool aFormControl = EFalse );
    void ConstructByTypeL(TInt aControlType,CEikCaptionedControl* aLine,CCoeControl* aContainer);
    void ShowFocus(TBool aFocus, TBool aRedraw=ETrue);
    SEikControlInfo CreateCustomControlL(TInt aControlType);
    void ChangeFocusTo(TInt aLineIndex);
    void PrepareForFocusTransitionL();
    void ChangeFocusToAndExposeL(TInt aLine,TBool aShowWholeControl=EFalse);
    TInt TopFocusableLine() const;
    TInt BottomFocusableLine() const;
    TBool LineIsFocusable(TInt aLine) const;
    TBool ResizeEdwinToFitTextL(CEikEdwin* aEdwin, TDrawNow aDrawNow, TSize aDesirableEdwinSize);
    TInt YPosToLine2(TInt aYPos) const;
    TInt LineToYPos(TInt& aLine) const;
    void ExposeLine(TInt aLine, TBool aForceResize, TBool aShowWholeLine = EFalse );
    void PassOnEventL(CCoeControl* aControl,MCoeControlObserver::TCoeEvent aEvent);
    CEikCaptionedControl* ConstructLineL(TInt aResourceId);
    CEikCaptionedControl* ConstructLineL(TResourceReader& aReader);
    TKeyResponse HandleCyclicFocusNavigationKeyL(const TKeyEvent& aKeyEvent);
    TKeyResponse HandleNonCyclicFocusNavigationKeyL(const TKeyEvent& aKeyEvent);
    void MakeEdwinScrollbarsVisibleL(TBool aVisible);
    void LineChangedL(TInt aControlId);
    void UpdateScrollBarThumb();
    void ReconsiderPageSize();
	void PrepareToDrawVerticalLine() const;
	
	/**
	* Specialized pointer event handling for forms.
	*/
	void HandleFormPointerEventL( const TPointerEvent& aPointerEvent );
	
	/**
	* Updates physics data.
	*/
	void UpdatePhysics();

    /**
    * Callback for highlight timer.
    */
    static TInt HighlightTimerCallBack( TAny* aPtr );
    
    /**
    * Handles highlight timer's expiration.
    */
    void HandleHighlightTimer();
    
    /**
    * Performs forced redraw of aControl and its component controls.
    */
    void DrawControl( CCoeControl* aControl ) const;
    
    /**
    * Record all lines drawing commands to the cache. Existing cache is purged.
    */
    void RecordLinesL();
    
    /**
    * Records one line's drawing commands to the cache replacing existing commands for that line.
    */
    void RecordLineL( TInt aLine );
    
    /**
    * Scrolls all lines by aPixels in y direction.
    */
    void ScrollByPixels( TInt aDelta );
    
    /**
    * Removes pressed down highlight.
    */
    void RemovePressedDownHighlight();
    
    /**
     * Sets highlight's visibility.
     *
     * @since S60 5.2
     * 
     * @param aVisible ETrue to set highlight visible.
     */
    void HighlightVisible( TBool aVisible );

    enum TScrollDirection
        {
        ESingleLineScrollUp ,
        ESingleLineScrollDown
        } ;
    void RegisterComponentL(TInt aControlType, CCoeControl* aControl, CEikCaptionedControl* aLine);
    static void CommonConstructCodeBetweenNewL(CEikDialogPage& aDialogPage, const CEikDialogPageContainer& aParent);

public: 
    TBool AnythingToDisplay() const;
    void DrawVerticalLine() const;
    CEikCaptionedControl* LineOnPageOrNull(TInt aLine) const;
    TSize RealDataSize() const;
    TInt NumberOfLines() const;
    CEikCaptionedControl* LineByIndex(TInt aIndex) const;

private:
    CEikCapCArray* iLines;
    MEikDialogPageObserver* iPageObserver;
    TInt iPageId;
    TInt iCurrentLine;
    TInt16 iFormFlags ;
    TBool iIsEditable;
    TBool iFormControl ;
    TInt iLastExposedLine;
    TInt iLastExposedLineViewWinYPosition;
    const CEikDialogPageContainer* iPageContainer;
    TFormLayoutSelection iFormLayout;
	CAknPaneScroll *iScroll;
public:
mutable CEikEdwin* iIgnoreFurtherEdwinResizeEvents;
private:
    CDialogPageExtension* iExtension;
    void DrawEmptyListL( CWindowGc& aGc );
    CAknFormPhysics* iPhysics;

    /**
     * Stores highlight's visibility.
     */
    TBool iHighlightVisible;

public:
/**
 * HandlePointerEventL
 * Function notifys the pages observer that the page has been tapped. (stylus down&up)
 * @param aPointerEvent the pointer event.
 */
	virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	
	void SetScbState(TBool aExternal);
    TBool ScbState() const;

private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
	};


/**
 * The CEikDialogPageContainer class contains one or more dialog pages and provides an interface to the active
 * page.
 *
 * @internal
 * @since ER5U
 */
NONSHARABLE_CLASS(CEikDialogPageContainer) : public CAknControl, public MCoeControlContext, public MCoeControlHitTest
    {
public:
    ~CEikDialogPageContainer();
    static CEikDialogPageContainer* NewL(const CCoeControl& aParent,MEikDialogPageObserver* aPageObserver);
    static CEikDialogPageContainer* NewLC(const CCoeControl& aParent,MEikDialogPageObserver* aPageObserver);
    TSize PreferredSize(const TSize& aMaxSize) const;
    void SetActivePageByIdL(TInt aPageId);
    void SetActivePageByIndexL(TInt aPageIndex);
    TInt ActivateFirstPageL();
    void AddPageL(TInt aPageId);
    void AddPageL(TInt aPageId,TResourceReader& aReader);
    TBool SetInitialFocus();
    CEikCaptionedControl* Line(TInt aLineId) const;
    CEikCaptionedControl* LineOrNull(TInt aLineId) const;
    CEikCaptionedControl* CurrentLine() const;
    void SetPageDensePacked(TInt aPageId,TBool aDensePacked);
    void SetAllPagesDensePacked(TBool aDensePacked);
    void SetPageDimmed(TInt aPageId,TBool aDimmed,TDrawNow aDrawNow);
    TBool IsActivePageDimmed() const;
    TInt LineId(const CCoeControl& aControl) const;
    void InsertLineL(TInt aPosition,TInt aPageId,TInt aResourceId);
    void DeleteLine(TInt aLineId, TBool aRedrawNow);
    void AdjustAllIds(TInt aPageId,TInt aControlIdDelta);
    CCoeControl* CreateLineByTypeL(const TDesC& aCaption,TInt aLineId,TInt aControlType,TAny* aReturnValue);
    CCoeControl* CreateLineByTypeL(const TDesC& aCaption,TInt aPageId,TInt aLineId,TInt aControlType,TAny* aReturnValue);
    TInt FocusLineL(TInt aLineId);
    TInt FocusedLineId() const;
    void GetAutoValues();
    TKeyResponse OfferUpDownKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType,CEikDialogPage::TFocusNavigationMode aFocusNavigationMode);
    TInt ActivePageId() const;
    TInt ActivePageIndex() const;
    void ResetLineMinimumSizes();
    TInt FindLineIndex(const CCoeControl& aControl) const;
    TBool RotateFocusByL(TInt aDelta);
    TInt NumPages() const;
    TKeyResponse OfferHotKeysKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
    TBool TakesEnterKey();
    TInt FindPageIndexForLineId(TInt aLineId);
    CEikDialogPage* Page( TInt aPageID ) ;
    void SetEditableL( TBool aEditable ) ;

    CEikFormAnim* AcquireAnim( TBool aAcquire, MEikFormAnimObserver* aObserver ) const;

public: // from CCoeControl
    virtual void Draw(const TRect& aRect) const;
    virtual TSize MinimumSize();
    virtual void PrepareForFocusLossL();
    virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
    virtual void HandleResourceChange(TInt aType);
public: // from MCoeControlContext
    virtual void PrepareContext(CWindowGc& aGc) const;
public:
    TBool HitRegionContains( const TPoint& aPoint, const CCoeControl& aControl ) const;
public:
    void SetPageFormSized();
protected:  // from CCoeControl
    virtual void SizeChanged();
    virtual TInt CountComponentControls() const;
    virtual CCoeControl* ComponentControl(TInt aIndex) const;
    virtual void ActivateL();
    virtual void FocusChanged(TDrawNow aDrawNow);
    virtual void WriteInternalStateL(RWriteStream& aWriteStream) const;
public: 
    void SetPageSelector(const CEikDialogPageSelector* aPageSelector);
    const CEikDialogPageSelector* PageSelector() const; 
private:
    CEikDialogPageContainer(MEikDialogPageObserver* aPageObserver);
    void ConstructL(const CCoeControl& aParent);
    void ConstructFromResourceL(TResourceReader& aReader,const CCoeControl& aParent);
    void CommonConstructL(const CCoeControl& aParent);
    void CreatePageArrayL();
    TInt PageIndex(TInt aPageId) const;
    TInt PageId(TInt aIndex) const;
    TInt PageIdFromLineId(TInt aLineId) const;
public:
    void CreateScrollBarL(const CCoeControl& aParent);
    CEikScrollBarFrame* ScrollBar() const;
    
private:
    CEikScrollBarFrame* iSBFrame;
    CArrayPtr<CEikDialogPage>* iPageArray;
    MEikDialogPageObserver* iPageObserver;
    TInt iActivePage;
    const CEikDialogPageSelector* iPageSelector;
    TBool iForm;
    TBool iIsEditable;

    /**
    * A singleton animation object for interfacing AknsEffectAnimation. All
    * captioned controls (in all dialog pages) share the same animation.
    * Only animation creation and memory management is vested here. Actual
    * animation usage is implemented in CaptionedControl.
    */
    CEikFormAnim* iAnimation;
    };

#endif
