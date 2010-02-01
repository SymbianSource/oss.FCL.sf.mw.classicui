/*
* Copyright (c) 2004-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Class for drawing tab graphics.
*
*/


#ifndef C_AKNTABGRPGRAPHICS_H
#define C_AKNTABGRPGRAPHICS_H

// INCLUDES
#include <e32base.h>

// FORWARD DECLARATIONS
class CFbsBitmap;
class CFbsBitmapDevice;
class CFbsBitGc;
class CBitmapContext;
class TAknWindowComponentLayout;


/**
 * This class takes care of drawing tab graphics which are defined
 * in SVG format and are defined differently than old tab group graphics.
 * Basically this class can be used to draw a new ram bitmap which contains
 * old style tab group bitmap.
 *
 * @since 2.8
 * @lib avkon.lib
 * @internal
 */
NONSHARABLE_CLASS( CAknTabGroupGraphics ) : public CBase
    {
public:

    struct SAknTabGroupBackground
        {
        SAknTabGroupBackground() : iBitmap( NULL ), iMask( NULL ) {};
        CFbsBitmap* iBitmap;
        CFbsBitmap* iMask;
        };

    struct SAknTabLayout
        {
        SAknTabLayout()
        : iActive( EFalse ), iLeft(0,0,0,0), iMiddle(0,0,0,0), iRight(0,0,0,0)
        {};

        TBool iActive;
        TRect iLeft;
        TRect iMiddle;
        TRect iRight;
        };

    struct SAknTabGroupBackgroundLayout
        {
        SAknTabGroupBackgroundLayout()
        : iUse( EFalse ),
          iFirstTab(),
          iSecondTab(),
          iThirdTab(),
          iFourthTab()
        {};

        // This tells wheter rest of the data is valid to be used or not.
        TBool         iUse;

        SAknTabLayout iFirstTab;
        SAknTabLayout iSecondTab;
        SAknTabLayout iThirdTab;
        SAknTabLayout iFourthTab;
        SAknTabLayout iHiddenTabLeft;
        SAknTabLayout iHiddenTabRight;
        };

public: // Constructors and destructor

    /**
    * Two-phased constructor.
    *
    * @return  Newly constructed object.
    */
    static CAknTabGroupGraphics* NewL();

    /**
    * Destructor.
    */
    virtual ~CAknTabGroupGraphics();

public: // New functions

    /**
    * This method tells if this class is able to draw tab background or not.
    *
    * @return  @c ETrue if drawing is possible, otherwise @c EFalse.
    */
    TBool TabGroupBackgroundAvailable();

    /**
    * This method sets the parent rectangle which will be used in the layout
    * calculations when tab background is drawn.
    *
    * @param  aParent  Parent rectangle
    */
    void SetTabGroupBackgroundParent( TRect aParent );

#if 0 // not used
    /**
    * This method draws the tab background bitmap using SVG graphics.
    * The tab combination is given as bitmap id which refers to old style
    * tab bitmaps.
    *
    * @param  aAvkonBitmapId  Bitmap index (@see avkon.mbg).
    *
    * @return  Struct which contains both the bitmap and the mask.
    *          Ownership is transferred to the caller.
    */
    CAknTabGroupGraphics::SAknTabGroupBackground CreateTabGroupBackgroundL(
        TInt aAvkonBitmapId );
        
#endif
    /**
    * Draw modes of the tab background graphics.
    */ 
    enum TTabDrawMode
        {
        ENormal,     ///< Draws both bitmap and mask.
        EBitmapOnly, ///< Draws only the bitmaps without masks.
        EMaskOnly,   ///< Draws only the mask bitmaps.
        ENoDraw      ///< Only calculates the layouts.
        };
    
    /**
    * These values are used to specify whether "hidden" tabs are drawn to the
    * background, meaning tabs that are only partially visible on either
    * side of the tab group. Hidden tabs are drawn in touch layouts, in
    * which they are used instead of navigation arrows to indicate that there
    * are more tabs than currently visible in the tab group. They also need
    * to be drawn to the background in the tab cycle animation.
    */ 
    enum TTabsHidden
        {
        ENone,          ///< No hidden tabs.
        EOnLeftSide,    ///< Hidden tab drawn on the left side.
        EOnRightSide,   ///< Hidden tab drawn on the right side.
        EOnBothSides,   ///< Hidden tabs drawn on both sides.
        ETwoOnBothSides ///< Two hidden tabs drawn on both sides.
        };
    
    /**
    * Types of tab animations that need to be considered when drawing
    * the tab backgrounds.
    */
    enum TTabAnimationType
        {
        ENoAnimation, ///< No animation is used.
        ECycleToLeft, ///< Cycle left animation in use.
        ECycleToRight ///< Cycle right animation in use.
        };

    /**
    * Draws normal tab background from given parameters.
    * 
    * @param  aTabDrawMode     Mode with which the background is drawn.
    * @param  aLongTabs        Specifies whether or not long tabs are used.
    * @param  aNumberOfTabs    Number of tabs visible in the tab group (not
    *                          the total number of tabs in the tab group).
    * @param  aActiveTab       Active tab number in relation to the first tab
    *                          shown. This value can be from one to
    *                          @c aNumberOfTabs.
    * @param  aGc              Graphics context used in drawing the background.
    * @param  aLayout[in,out]  Tab group background layout used in drawing.
    *                          If the @c aLayout's @c iUse parameter is
    *                          @c EFalse, then the layout is calculated
    *                          to the @c aLayout. 
    * @param  aTabsHidden      Specifies where hidden tabs are drawn.
    * @param  aAnimation       Specifies the used animation.
    */
    void DrawTabGroupBackgroundL(
        TTabDrawMode aTabDrawMode,
        TBool aLongTabs,
        TInt aNumberOfTabs,
        TInt aActiveTab,
        CBitmapContext* aGc,
        SAknTabGroupBackgroundLayout& aLayout,
        TTabsHidden aTabsHidden,
        TTabAnimationType aAnimation = ENoAnimation ) const;

    /**
    * Draws narrow tab background from given parameters.
    * 
    * @param  aTabDrawMode     Mode with which the background is drawn.
    * @param  aLongTabs        Specifies whether or not long tabs are used.
    * @param  aNumberOfTabs    Number of tabs visible in the tab group (not
    *                          the total number of tabs in the tab group).
    * @param  aActiveTab       Active tab number in relation to the first tab
    *                          shown. This value can be from one to
    *                          @c aNumberOfTabs.
    * @param  aGc              Graphics context used in drawing the background.
    * @param  aLayout[in,out]  Tab group background layout used in drawing.
    *                          If the @c aLayout's @c iUse parameter is
    *                          @c EFalse, then the layout is calculated
    *                          to the @c aLayout. 
    */
    void DrawTabGroupNarrowBackgroundL(
        TTabDrawMode aTabDrawMode,
        TBool aLongTabs,
        TInt aNumberOfTabs,
        TInt aActiveTab,
        CBitmapContext* aGc,
        SAknTabGroupBackgroundLayout& aLayout ) const;

    /**
    * Background parts of a tab.
    */ 
    enum TTabPart
        {
        ELeft,
        EMiddle,
        ERight
        };

    /**
    * This function tests whether the given tab graphics was hit with a
    * pointer event or not. The result is determined using the mask graphics.
    *
    * @param  aTabComponent  Tab graphics component to test against,
    *                        this should be of type @c TTabPart.
    * @param  aTabGroupRect  Tab part's rectangle.
    * @param  aPoint         Pointer event's coordinates.
    * @param  aIsActiveTab   Whether the clicked tab is active or not.
    *
    * @return @c ETrue if the tab was hit, otherwise @c EFalse.
    */
    TBool TabClickedL( TInt aTabComponent,
                       const TRect& aTabGroupRect,
                       const TPoint& aPoint,
                       TBool aIsActiveTab );
    
    /**
    * Gets the whole tab rectangle in relation to the tab group container
    * by adding together the separate pieces of @c aLayout.
    */
    TRect TabRectFromLayout( const SAknTabLayout& aLayout );
    
    /**
    * Adjusts the tab part rectangles in the passed @c aLayout by the
    * specified x and y offsets. 
    * 
    * @param  aLayout[in,out]  Tab background layout to be adjusted.
    * @param  aXOffset         Horizontal value to move the rectangles for.
    * @param  aYOffset         Vertical value to move the rectangles for.
    */ 
    void AdjustTabLayoutRect( SAknTabLayout& aLayout, 
                              TInt aXOffset,
                              TInt aYOffset ) const;

private:

#if 0 //not used
    /**
    * This method draws tab group bitmap with given parameters.
    *
    * @param  aLongTabs      @c ETrue to draw long tabs.
    * @param  aNumberOfTabs  Number of tabs visible in the tab group.
    * @param  aActiveTab     Active tab index, allowed range from 1 to
    *                        @c aNumberOfTabs.
    *
    * @return  Struct which contains both the bitmap and the mask.
    *          Ownership is transferred to the caller.
    */
    CAknTabGroupGraphics::SAknTabGroupBackground CreateTabGroupBackgroundL(
        TBool aLongTabs,
        TInt aNumberOfTabs,
        TInt aActiveTab );
        
#endif
    /**
    * C++ default constructor.
    */
    CAknTabGroupGraphics();

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

    /**
    * Method to construct tab graphics from SVG.
    */
    void LoadTabGraphicsL();

    /**
    * Methods to extract normal layouts for tab group backgrounds
    */
    CAknTabGroupGraphics::SAknTabGroupBackgroundLayout TwoTabBackground(
        TInt aActiveTab ) const;

    CAknTabGroupGraphics::SAknTabGroupBackgroundLayout ThreeTabBackground(
        TInt aActiveTab ) const;

    CAknTabGroupGraphics::SAknTabGroupBackgroundLayout FourTabBackground(
        TInt aActiveTab ) const;

    CAknTabGroupGraphics::SAknTabGroupBackgroundLayout TwoLongTabBackground(
        TInt aActiveTab ) const;

    CAknTabGroupGraphics::SAknTabGroupBackgroundLayout ThreeLongTabBackground(
        TInt aActiveTab ) const;

    /**
    * Methods to extract narrow layouts for tab group backgrounds.
    */
    CAknTabGroupGraphics::SAknTabGroupBackgroundLayout
        TwoTabNarrowBackground( TInt aActiveTab ) const;

    CAknTabGroupGraphics::SAknTabGroupBackgroundLayout
        ThreeTabNarrowBackground( TInt aActiveTab ) const;

    CAknTabGroupGraphics::SAknTabGroupBackgroundLayout
        FourTabNarrowBackground( TInt aActiveTab ) const;

    CAknTabGroupGraphics::SAknTabGroupBackgroundLayout
        TwoLongTabNarrowBackground( TInt aActiveTab ) const;

    CAknTabGroupGraphics::SAknTabGroupBackgroundLayout
        ThreeLongTabNarrowBackground( TInt aActiveTab ) const;

    /**
    * Methods to draw normal tab backgrounds.
    */
    void DrawTwoTabBackground( TTabDrawMode aDrawMode,
                               TInt aActiveTab,
                               CBitmapContext* aGc,
                               SAknTabGroupBackgroundLayout& aLayout ) const;

    void DrawThreeTabBackground( TTabDrawMode aDrawMode,
                                 TInt aActiveTab,
                                 CBitmapContext* aGc,
                                 SAknTabGroupBackgroundLayout& aLayout,
                                 TTabsHidden aTabsHidden,
                                 TTabAnimationType aAnimation = ENoAnimation ) const;

    void DrawFourTabBackground( TTabDrawMode aDrawMode,
                                TInt aActiveTab,
                                CBitmapContext* aGc,
                                SAknTabGroupBackgroundLayout& aLayout ) const;

    void DrawTwoLongTabBackground(
        TTabDrawMode aDrawMode,
        TInt aActiveTab,
        CBitmapContext* aGc,
        SAknTabGroupBackgroundLayout& aLayout ) const;

    void DrawThreeLongTabBackground(
        TTabDrawMode aDrawMode,
        TInt aActiveTab,
        CBitmapContext* aGc,
        SAknTabGroupBackgroundLayout& aLayout ) const;

    /**
    * Methods to draw narrow tab backgrounds.
    */
    void DrawTwoTabNarrowBackground(
        TTabDrawMode aDrawMode,
        TInt aActiveTab,
        CBitmapContext* aGc,
        SAknTabGroupBackgroundLayout& aLayout ) const;

    void DrawThreeTabNarrowBackground(
        TTabDrawMode aDrawMode,
        TInt aActiveTab,
        CBitmapContext* aGc,
        SAknTabGroupBackgroundLayout& aLayout ) const;

    void DrawFourTabNarrowBackground(
        TTabDrawMode aDrawMode,
        TInt aActiveTab,
        CBitmapContext* aGc,
        SAknTabGroupBackgroundLayout& aLayout ) const;

    void DrawTwoLongTabNarrowBackground(
        TTabDrawMode aDrawMode,
        TInt aActiveTab,
        CBitmapContext* aGc,
        SAknTabGroupBackgroundLayout& aLayout ) const;

    void DrawThreeLongTabNarrowBackground(
        TTabDrawMode aDrawMode,
        TInt aActiveTab,
        CBitmapContext* aGc,
        SAknTabGroupBackgroundLayout& aLayout ) const;

    /**
    * Draws single tab graphics for an active tab.
    * 
    * @param  aDrawMode  Mode with which the background is drawn.
    * @param  aLeft      Rectangle of the left part of the tab.
    * @param  aMiddle    Rectangle of the middle part of the tab.
    * @param  aRight     Rectangle of the right part of the tab.
    * @param  aGc        Graphics context used in drawing.
    */
    void DrawActiveTab( TTabDrawMode aDrawMode,
                        TRect aLeft,
                        TRect aMiddle,
                        TRect aRight,
                        CBitmapContext* aGc ) const;
    
    /**
    * Draws single tab graphics for a passive tab.
    * 
    * @param  aDrawMode  Mode with which the background is drawn.
    * @param  aLeft      Rectangle of the left part of the tab.
    * @param  aMiddle    Rectangle of the middle part of the tab.
    * @param  aRight     Rectangle of the right part of the tab.
    * @param  aGc        Graphics context used in drawing.
    * @param  aFaded     Should the tab be drawn faded.
    */
    void DrawPassiveTab( TTabDrawMode aDrawMode,
                         TRect aLeft,
                         TRect aMiddle,
                         TRect aRight,
                         CBitmapContext* aGc,
                         TBool aFaded = EFalse ) const;
    
    /**
    * Draws single tab part graphics for a passive tab.
    * Used in drawing the hidden tab bits.
    * 
    * @param  aDrawMode  Mode with which the background is drawn.
    * @param  aTabPart   Part of the tab graphics to draw.
    * @param  aRect      Rectangle of the drawn part of the tab.
    * @param  aGc        Graphics context used in drawing.
    */
    void DrawPassiveTabBit( TTabDrawMode aDrawMode,
                            TTabPart aTabPart,
                            TRect aRect,
                            CBitmapContext* aGc ) const;

    /**
    * Helper methods to transform a layout line into a rectangle.
    */
    TRect RectFromLayout( TRect aParent,
                          TAknWindowComponentLayout aComponentLayout ) const;

    /**
    * Helper method to get the narrow tab container rect.
    */
    TRect NarrowParentRect() const;

private: // Member data.

    CFbsBitmap*   iActiveTabLeft;
    CFbsBitmap*   iActiveTabLeftMask;
    CFbsBitmap*   iActiveTabMiddle;
    CFbsBitmap*   iActiveTabMiddleMask;
    CFbsBitmap*   iActiveTabRight;
    CFbsBitmap*   iActiveTabRightMask;

    CFbsBitmap*   iPassiveTabLeft;
    CFbsBitmap*   iPassiveTabLeftMask;
    CFbsBitmap*   iPassiveTabMiddle;
    CFbsBitmap*   iPassiveTabMiddleMask;
    CFbsBitmap*   iPassiveTabRight;
    CFbsBitmap*   iPassiveTabRightMask;

    TRect         iTabGroupBackgroundParent;
    TBool         iTabGroupBackgroundAvailable;
    };

#endif // C_AKNTABGRPGRAPHICS_H

// End of File
