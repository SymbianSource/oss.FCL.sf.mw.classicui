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

	
#if !defined(__EIKSBFRM_H__)
#define __EIKSBFRM_H__

#include <lafpublc.h>
#if !defined(__AKNSCRLB_H__)
#include <aknscrlb.h>
#endif
 
class CEikCba;

/**
 * Enables setting of the frame layout for a scroll bar.
 */
class TEikScrollBarFrameLayout
    {

public:

    /** 
     * Determines whether the client rectangle or the inclusive rectangle
     * remains constant.
     */
    enum TTilingMode
        {

        /** The client rectangle remains constant. */
        EClientRectConstant,

        /** The inclusive rectangle remains constant. */
        EInclusiveRectConstant
        };

public:

    /**
     * C++ default constructor.
     */
    IMPORT_C TEikScrollBarFrameLayout();

    /**
     * Sets all inclusive margins.
     *
     * @param aMargin The value to use for all inclusive margins.
     */
    IMPORT_C void SetInclusiveMargin(TInt aMargin);

    /**
     * Sets all client margins. These surround the client rectangle which is
     * the client area viewport onto the larger canvas to be scrolled.
     *
     * @param aMargin The value to use for all client margins.
     */
    IMPORT_C void SetClientMargin(TInt aMargin);

public:

    /** The inclusive margin (in twips or pixels). */
    TMargins iInclusiveMargin;

    /** 
     * The amount of screen movement performed when the nudge button is 
     * pressed.
     */
    TMargins iClientMargin;

    /** 
     * The amount of screen movement performed when the nudge button is
     * pressed.
     */
    TSize iClientAreaGranularity;

    /** 
     * Determines whether the client rectangle, or the inclusive rectangle,
     * remains constant.
     */
    TTilingMode iTilingMode;
    };


class CEikCornerWindow;
class CEikScrollBarFrameExtension;

/**
 * The scroll bar frame is a control assemblage manager that relates a control,
 * or control body, to two scroll bars and a corner window. A corner window is
 * that part of the screen that is common to both the horizontal, and the 
 * vertical elements of a scroll bar.
 *
 * This class helps with access to, and set up of, scroll bars and also with 
 * the layout of the scrolled control or control body. A scroll bar frame is 
 * not a control, but it does implement the standard control composite pattern
 * to manage the assemblage.
 */
class CEikScrollBarFrame : public CBase
    {
	
public:	// enums 

    DECLARE_TYPE_ID(0x101F8672)   

    /** Defines the scroll bar’s visibility.*/
    enum TScrollBarVisibility
        {
        /** Scroll bar not visible.*/
        EOff,

        /** Scroll bar visible.*/
        EOn,

        /** Scroll bar visible if required.*/
        EAuto
        };

    /** Defines the type of scroll bar.*/	
    enum TScrollBarType
        {
        /** Scroll bar complete with shaft. Not used.*/
        ENormalScrollBar =0x0,

        /** Floating arrow head scroll bar, without shaft. Legacy type. */
        EArrowHead =0x200,

        /** Spanned scroll bar. */
        EDoubleSpan =0x400
        };

    /** Defines where the scroll bar is located. */		
    enum TScrollBarSide
        {
        /** 
         * Scroll bar located at the bottom, or to the right of the scroll bar
         * frame.
         */
        EBottomOrRight =0x0,

        /** 
         * Scroll bar located at the top, or to the left of the scroll bar
         * frame.
         */
        ETopOrLeft =0x800
        };
		
    /** Determines how the scroll bar frame manages scroll bars.*/
    enum TScrollBarManagement 
        {
        /** 
         * The scroll bar frame creates, destroys and recreates, scroll bars
         * according to the visibility mode. The scroll bar frame also acts as
         * an intermediary with its owning control so that the scroll bars can
         * be treated as component controls.
         */
        EComponent                  ,//=SLafScrollBarFrame::EComponent,

        /** 
         * The scroll bar frame creates, destroys and recreates, scroll bars 
         * according to the visibility mode. In this case, the scroll bars are
         * not treated as component controls. Instead, the scroll bars are 
         * geometry managed in windows floating above the control window and
         * their position is determined in relation to the frame’s position on
         * the screen.
         */
        EFloating                   ,//=SLafScrollBarFrame::EFloating,

        /** 
         * The scroll bar frame uses the central application scroll bar as held
         * in the environment. This scroll bar is neither owned by the frame 
         * nor treated as a component control of the frame’s owner.
         */
        EApplicationScrollBar       //=SLafScrollBarFrame::EApplicationScrollBar
        };

    /**
     * Defines that is the horizontal or the vertical (spanned) scroll bar
     * visible. Applicaple  only for spanned scroll bars.
     */
    enum TScrollBarFrameFlags
        {
        /** Horizontal spanned scroll bar visible. */
        EHVisible           =0x01,

        /** Vertical spanned scroll bar visible. */
        EVVisible           =0x02,

        /** 
         * Enables nudge buttons in touch devices. This flag MUST
         * be set before the creation of the doublespan scrollbar.
         */
        EEnableNudgeButtons = 0x04,
        
        /** 
         * Disables expanded touch area, which is on by default
         * in touch devices. This flag MUST be set before the
         * creation of the doublespan scrollbar.
         */
        EDisableExpandedTouchArea = 0x08      
        };
private:
    enum TMarginsAdjustmentMode
        {
        EGrow,
        EShrink
        };

public:	// specific

    /**
     * C++ default constructor.
     */
    CEikScrollBarFrame(){}

    /**
     * Constructor. Constructs a scroll bar frame object.
     *
     * @param aParentWindow The scroll bar’s parent control.
     * @param aObserver The scroll bar observer.
     * @param aPreAlloc Not used.
     */  	
    IMPORT_C CEikScrollBarFrame(CCoeControl* aParentWindow, 
                                MEikScrollBarObserver* aObserver, 
                                TBool aPreAlloc=EFalse);

    /**
     * Destructor.
     */  
    IMPORT_C ~CEikScrollBarFrame();

    /**
     * Constructor. Internal only to Eikcoctl.lib use. Parameter @c aDoubleSpan
     * offers possibility to optimize scroll bar loading (if @c ETrue,
     * arrowhead scroll bar will never be loaded).
     *
     * @since S60 3.0
     * @param aParentWindow The scroll bar’s parent control.
     * @param aObserver The scroll bar observer.
     * @param aPreAlloc Not used.
     * @param aDoubleSpan If @c ETrue, spanned scroll bar is created.
     */     
    CEikScrollBarFrame(CCoeControl* aParentWindow, 
                       MEikScrollBarObserver* aObserver, 
                       TBool aPreAlloc, 
                       TBool aDoubleSpan);

    /**
     * Initializes a new @c CEikScrollBarFrameExtension object.
     *
     * @since S60 3.0
     * @param aParentWindow The scroll bar’s parent control.
     * @param aObserver The scroll bar observer.
     */
    void InitExtension(CCoeControl* aParentWindow, 
                       MEikScrollBarObserver* aObserver);

    /**
     * Forces any scroll bars and the corner window if it is visible to be 
     * redrawn.
     */     
    IMPORT_C void DrawScrollBarsNow() const;

	/**
     * Tell scroll bars and the corner window to redraw if it is visible
     */     
    void DrawScrollBarsDeferred() const;

    /**
     * Sets the visibility state for both the horizontal and the vertical scroll
     * bars. This is used when tiling.
     *
     * @param aHVisibility Horizontal scroll bar visibility.
     * @param aVVisibility Vertical scroll bar visibility.
     */     
    IMPORT_C void SetScrollBarVisibilityL(TScrollBarVisibility aHVisibility, 
                                          TScrollBarVisibility aVVisibility);

    /**
     * Determines the vertical scroll bar’s visibility. @c 
     * CEikScrollBarFrame::ScrollBarVisibility @c 
     * (CEikScrollBar::TOrientation aOrientation) can be used instead of this
     * method.
     * 
     * @return Visibility for vertical scroll bar.
     */     
    inline TScrollBarVisibility VScrollBarVisibility() const;

    /**
     * Sets scrollbar observers.
     *
     * @param aObserver The scroll bar observer. 
     */     
    IMPORT_C void SetScrollBarFrameObserver(MEikScrollBarObserver* aObserver);

    // Model setting. 

    /**
     * Sets the vertical scrollbar mode. Does not actually draw anything until 
     * the thumb or focus setting functions are called.
     *
     * @param aVModel Model for the vertical scrollbar.
     * @return @c EFalse.
     */     
    IMPORT_C TBool Tile(TEikScrollBarModel* aVModel);

    /**
     * Tiles the client area and the scroll bars managed by the frame. The 
     * scroll bars are set up according to the scroll bar models; @c aHModel and
     * @c aVModel. Ownership is not transferred as a result of passing these
     * parameters as pointers. The result of tiling geometry management is 
     * observable through the two rectangles @c aClientRect and @c 
     * aInclusiveRect. Depending on the tiling layout @c aLayout and the scroll 
     * bar visibility settings, either of these rectangles can be made constant
     * and the other rectangle adjusted accordingly.
     *
     * For @c EArrowhead type scrollbar the layout is always fixed, it cannot be
     * altered by using this method.
     *
     * For @c EDoublespan type scrollbar the layout can be set also with two 
     * helper methods from the @c AknLayoutUtils class:
     *
     * @code
     * AknLayoutUtils::LayoutVerticalScrollBar(
     *           CEikScrollBarFrame* aScrollBarFrame, 
     *           const TRect& aControlParent, 
     *           const TAknWindowLineLayout& aLayout);
     * AknLayoutUtils::LayoutHorizontalScrollBar(
     *           CEikScrollBarFrame* aScrollBarFrame, 
     *           const TRect& aControlParent, 
     *           const TAknWindowLineLayout& aLayout);
     * @endcode
     *   
     * @param aHModel Horizontal scroll bar model.
     * @param aVModel Vertical scroll bar model.
     * @param aClientRect Client rectangle.
     * @param aInclusiveRect A rectangle that includes the area to be scrolled 
     *        and the scroll bars themselves.
     * @param aLayout Tiling layout.
     * 
     * @return @c ETrue if the non-constant rectangle is adjusted, otherwise @c 
     *         EFalse.
     */     
    IMPORT_C TBool TileL(TEikScrollBarModel* aHModel, 
                         TEikScrollBarModel* aVModel,
                         TRect& aClientRect,
                         TRect& aInclusiveRect,
                         const TEikScrollBarFrameLayout& aLayout);

    /**
     * Moves the scroll bar thumbs by the specified amounts. This updates the 
     * scroll bars after an external scroll. The values of the parameters should
     * be supplied in terms of the horizontal and vertical scrolling models 
     * respectively. The scrolling models are presumed not to have changed 
     * spans.
     *
     * @param aDeltaX The amount to move the horizontal scroll bar.
     * @param aDeltaY The amount to move the vertical scroll bar.
     */     
    IMPORT_C void MoveThumbsBy(TInt aDeltaX, TInt aDeltaY);

    /**
     * Moves the horizontal scroll bar thumb to the position @c aHorizThumbPos.
     * This function is used to update the scroll bar after an external scroll.
     * The value of @c aThumbPos should be supplied in terms of the scrolling
     * model, which is presumed not to have changed spans.
     * 
     * @param aHorizThumbPos The required thumb position.
     */     
    IMPORT_C void MoveHorizThumbTo(TInt aHorizThumbPos);

    /**
     * Moves the vertical scroll bar thumb to the position @c aVertThumbPos. 
     * This function is used to update the scroll bar after an external scroll.
     * The value of aThumbPos should be supplied in terms of the scrolling 
     * model, which is presumed not to have changed spans.
     * 
     * @param aVertThumbPos The required thumb position.
     */     
    IMPORT_C void MoveVertThumbTo(TInt aVertThumbPos);

    /**
     * Moves the vertical scroll bar thumb to the position @c aFocusPosition. 
     * This function is used to update the scroll bar after an external scroll. 
     * The value of @c aFocusPosition should be supplied in terms of the 
     * scrolling model, which is presumed not to have changed spans.
     * 
     * @param aFocusPosition The required thumb position.
     */     
    IMPORT_C void SetVFocusPosToThumbPos(TInt aFocusPosition);

    /**
     * Returns the breadth of the scroll bar idenitified by @c aOrientation, or
     * zero if none exists.
     *
     * @param  aOrientation The orientation of the scroll bar for which you wish
     *         to obtain the breadth.
     *
     * @return The specified scroll bar's breadth. This is zero if none exists.
     */     
    IMPORT_C TInt ScrollBarBreadth(
        CEikScrollBar::TOrientation aOrientation) const;

    // scroll bar frame behavior functions

    /**
     * Not implemented.
     *
     * @param aAdjusts Not used. 
     */     
    IMPORT_C void SetAdjustsHorizontalModel(TBool aAdjusts); 

    /**
     * Not implemented.
     *
     * @param aAdjusts Not used. 
     */      
    IMPORT_C void SetAdjustsVerticalModel(TBool aAdjusts);

    /**
     * Sets scrollbar frame flags. 
     *
     * @param aMask Bitmask of the bits that are to be set.
     */     
    inline void SetScrollBarFrameFlags(TInt aMask);

    /**
     * Determines whether the scroll bar specified by aOrientation exists
     * 
     * @param aOrientation The scroll bar’s orientation.
     * @return @c ETrue if the specified scroll bar exists otherwise @c EFalse.
     */     
    IMPORT_C TBool ScrollBarExists(
        CEikScrollBar::TOrientation aOrientation) const;

    /**
     * From @c CCoeControl
     *
     * Gets the number of controls contained in a compound control.
     * 
     * @return The number of component controls contained in this control.
     */     
    IMPORT_C TInt CountComponentControls() const;

    /**
     * From @c CCoeControl
     *
     * Gets the component specified by index. Within a compound control, each
     * component control is identified by an index, where the index depends on
     * the order the controls were added: the first is given an index of 0, the
     * next an index of 1, and so on.
     * 
     * @return The component control with an index of aIndex
     */         
    IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;

    /**
     * Returns a pointer to the scroll bar identified by orientation @c 
     * aOrientation.
     * 
     * @param aOrientation The orientation of the scroll bar for which you wish
     *        to obtain a pointer.
     * @return A pointer to the scroll bar with orientation @c aOrientation if 
     *         the scrollbar is visible.
     */         
    IMPORT_C CEikScrollBar* GetScrollBarHandle(
        CEikScrollBar::TOrientation aOrientation) const;

    /**
     * Returns a pointer to the vertical scroll bar.
     * 
     * @return A pointer to the vertical scroll bar.
     */         
    IMPORT_C CEikScrollBar* VerticalScrollBar() const;

    /**
     * Sets the type of horizontal scroll bar. Possible values are @c EArrowHead
     * and @c EDoubleSpan.
     *
     * @param aType Type of the scrollbar. 
     */         
    IMPORT_C void SetTypeOfHScrollBar(TScrollBarType aType);

    /**
     * Sets the type of vertical scroll bar. Possible values are @c EArrowHead
     * and @c EDoubleSpan.
     *
     * @param aType Type of the scrollbar. 
     */         
    IMPORT_C void SetTypeOfVScrollBar(TScrollBarType aType);

    /**
     * Returns the control type of the horizontal scroll bar 
     * 
     * @return Type of the scrollbar.
     */         
    IMPORT_C TScrollBarType TypeOfHScrollBar() const;

    /**
     * Returns the control type of the vertical scroll bar 
     * 
     * @return Type of the scrollbar.
     */         
    IMPORT_C TScrollBarType TypeOfVScrollBar() const;

    /**
     * Checks if the vertical scrollbar type is @c EArrowHead.
     *
     * @param aFlag Not used.
     * @return @c ETrue if the type of the scrollbar is @c EArrowHead.
     */         
    IMPORT_C TBool IsArrowHeadScrollBar(TInt aFlag) const;

    // application scroll bar utilities

    /**
     * This method is used only internally by the @c CEikScrollBar. Disconnects
     * externally connected scrollbar.
     * 
     * @param aScrollBar Scrollbar to be disconnected.
     */     
    void DisconnectExternalScrollBar(CEikScrollBar* aScrollBar);

    /**
     * This method creates double span type scrollbars into this frame. Old
     * scrollbars are deleted or disconnected.
     *
     * @since S60 2.6
     * @param aWindowOwning Tells wheter created scrollbar should be 
     *        a window owning control or not. Selection for this is 
     *        relevant especially because skinned scrollbar draws            
     * @param aRemote @c True if this method should instead of creating own 
     *        scrollbar try to connect to a remote scrollbar frame and 
     *        start using its scrollbars. Connecting is done using 
     *        through object provider mechanism, so the object supply 
     *        chain must be valid. Also if true, then parameter @c 
     *        aWindowOwning will be ignored.
     *
     * Example of use:
     *
     * @code
     *    iSBFrame=new(ELeave) CEikScrollBarFrame(this, NULL, ETrue);
     *    iSBFrame->SetScrollBarVisibilityL(CEikScrollBarFrame::EOff,
     *                                      CEikScrollBarFrame::EAuto);
     *    iSBFrame->CreateDoubleSpanScrollBarsL(ETrue, EFalse);
     *
     *    Note that double span scrollbar types requires different model classes
     *    to be used in places of @c TEikScrollBarModel of this scrollbar frame 
     *    API:s other method calls.
     *    
     *    Scrollbar type        Required model (in places of TEikScrollBarModel)
     *    ---------------       ------------------------------------------------
     *    EDoubleSpan           TAknDoubleSpanScrollBarModel 
     *    EArrowHead            TEikScrollBarModel
     *
     *   // model for double span type scrollbar
     *   TAknDoubleSpanScrollBarModel vModel; 
     *   // model for double span type scrollbar
     *   TAknDoubleSpanScrollBarModel hModel; 
     *   
     *   iSBFrame->Tile(vModel, iVRect);
     * @endcode
     */ 
    IMPORT_C void CreateDoubleSpanScrollBarsL(TBool aWindowOwning, 
                                              TBool aRemote);

    /**
     * This method creates double span type scrollbars into this frame. Old 
     * scrollbars are deleted or disconnected.
     *
     * @since S60 2.8
     * @param aWindowOwning Tells wheter created scrollbar should be a window 
     *        owning control or not. Selection for this is relevant especially
     *        because skinned scrollbar draws its background using its parent 
     *        windows background context.                   
     * @param aRemote True if this method should instead of creating own
     *        scrollbar try to connect to a remote scrollbar frame and start
     *        using its scrollbars. Connecting is done using through object 
     *        provider mechanism, so the object supply chain must be valid. Also
     *        if true, then parameter @c aWindowOwning will be ignored.
     * @param aVertical If @c ETrue vertical scrollbar will be created to 
     *        scrollbar frame.
     * @param aHorizontal If @c ETrue horizontal scrollbar will be created to
     *        scrollbar frame.
     * @leave KErrNotFound Parent object doesn't have scrollbar frame.
     */ 
    IMPORT_C void CreateDoubleSpanScrollBarsL(TBool aWindowOwning, 
                                              TBool aRemote, 
                                              TBool aVertical, 
                                              TBool aHorizontal);

    /**
     * Tiles the vertical @c EDouble span type scroll bar managed by the frame.
     * The scroll bar is set up according to the scroll bar model and given 
     * rectangle which is relative to the parent window of the frame.
     *
     * @since S60 2.6
     * @param aVModel Vertical scrollbar model.         
     * @param aVScrollBar Vertical scrollbar rectangle.            
     *
     * For @c EDoublespan type scrollbar the layout can be set also with a 
     * helper method from the @c AknLayoutUtils class:
     *
     * @code
     * AknLayoutUtils::LayoutVerticalScrollBar(
     *                                   CEikScrollBarFrame* aScrollBarFrame, 
     *                                   const TRect& aControlParent, 
     *                                   const TAknWindowLineLayout& aLayout);
     * @endcode
     */     
    IMPORT_C void Tile(TEikScrollBarModel* aVModel, TRect& aVScrollBar);

    /**
     * Sets the models of the scrollbars. 
     * 
     * @since S60 2.6
     * @param aHModel The model of the horizontal scrollbar.
     * @param aVModel The model of the vertical scrollbar.
     *
     */     
    IMPORT_C void Tile(TEikScrollBarModel* aHModel,
                       TEikScrollBarModel* aVModel);

    /**
     * Gets the visibility of given scrollbar orientation. 
     * 
     * This method should be used instead of a deprecated method @c
     * CEikScrollBarFrame::HScrollBarVisibility() and
     * also can be used instead of @c CEikScrollBarFrame::VScrollBarVisibility()
     *
     * @since S60 2.6
     * @param aOrientation The orientation of a scrollbar in the frame.
     * @return The visibility of requested scrollbar.
     */     
    IMPORT_C TScrollBarVisibility ScrollBarVisibility(
            CEikScrollBar::TOrientation aOrientation) const;
	/**
    * Sets the background drawing for the double spanned scrollbars 
    * 
    * This method can be used to enable or disable the drawing of the scrollbar 
    * background via mop chain.
    *
    * @since    3.0
    * @param    aDrawHorizontal sets the state of the background drawing of 
    * 			the horizontal scrollbar.
    * @param    aDrawVertical sets the state of the background drawing of 
    * 			the vertical scrollbar.
    * @return   Success of the call, KErrNotSupported if the scrollbars 
    * 			are not doublespan scrollbars.
    *
    */
	IMPORT_C TInt DrawBackground(TBool aDrawHorizontal, TBool aDrawVertical);
	
	/**
    * Gets the state of the background drawing for the double spanned scrollbars.
    * 
    * This method can be used to get the state of drawing of the scrollbar 
    * background via mop chain.
    *
    * @since    3.0
    * @param    aDrawHorizontal gets the state of the background drawing of 
    * 			the horizontal scrollbar.
    * @param    aDrawVertical gets the state of the background drawing of 
    * 			the vertical scrollbar.
    * @return   Success of the call, KErrNotSupported if the scrollbars 
    * 			are not doublespan scrollbars.
    *
    */
	IMPORT_C TInt DrawBackgroundState(TBool& aDrawHorizontal, TBool& aDrawVertical);

public:

    /**
     * Gets a pointer to the horizontal scroll bar.
     * 
     * @return A pointer to the horizontal scroll bar.
     */         
    CEikScrollBar* HorizontalScrollBar() const;
    
    /**
     * Sets scrollbar observers.
     *
     * @param aObserver The scroll bar observer. 
     */
    MEikScrollBarObserver* ScrollBarFrameObserver();

protected:
    // Accessor methods

    /**
     * Sets parent window.
     * 
     * @param aParentWindow A pointer to the parent window.
     */ 
    void SetParentWindow(CCoeControl* aParentWindow);

    /**
     * Gets a pointer to the parent window.
     *  
     * @return A pointer to the parent window.
     */ 
    CCoeControl* ParentWindow() const;

protected:
   
    /** Struct */ 
    struct SBarData
        {

        /** Pointer to the @c CAknScrollBar class */
        CAknScrollBar* iBar;

        /** Enum @c TEikScrollBarModel */
        TEikScrollBarModel iModel;

        /** Enum @c TScrollBarVisibility. */
        TScrollBarVisibility iVisibility;

        /** Boolean value if external scroll bar is attached. */
        TBool iExternalScrollBarAttached;
        };

private:

    void CalcTheoreticalScrollBarVisibility(const TEikScrollBarModel* aVModel);
    void ApplyModel(SBarData& aSBar);
    void MakeSBarVisible(SBarData& aSBar, TBool aVisible);
    void GetScrollBars(TBool aDoubleSpan);
    CEikCba* GetCurrentCba();
    void DeleteScrollBars();
    void CreateArrowHeadScrollBarsL();

    void CalcTheoreticalScrollBarVisibility(const TEikScrollBarModel* aVModel,
                                            const TEikScrollBarModel* aHModel);

protected:

    /** Struct object.*/
    SBarData iV;

private:

    CEikScrollBarFrameExtension* iExtension; 
    TInt iScrollBarFrameFlags;

    friend class CEikScrollBarFrameExtension;
    };

inline CEikScrollBarFrame::TScrollBarVisibility CEikScrollBarFrame::VScrollBarVisibility() const
    { return iV.iVisibility; }
inline void CEikScrollBarFrame::SetScrollBarFrameFlags(TInt aMask)
    { iScrollBarFrameFlags|=aMask; }

// Cba scroll bar frame (with it's own scrollbar creation methods)
class CEikCbaScrollBarFrame : public CEikScrollBarFrame
    {
public:
    CEikCbaScrollBarFrame(CCoeControl* aParentWindow, MEikScrollBarObserver* aObserver, TBool aPreAlloc=EFalse);
    void ConstructL();
    void SwitchToArrowHeadScrollBarL();  // @since 3.0
    };

#endif
