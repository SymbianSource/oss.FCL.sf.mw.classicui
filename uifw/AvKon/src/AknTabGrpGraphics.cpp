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


// SYSTEM INCLUDE FILES
#include <avkon.mbg>
#include <fbs.h>
#include <bitdev.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <AknIconUtils.h>
#include <AknsUtils.h>
#include <layoutmetadata.cdl.h>
#include <akniconconfig.h>

// USER INCLUDE FILES
#include "AknTabGrpGraphics.h"
#include "AknUtils.h"
#include "aknappui.h"
#include "AknStatuspaneUtils.h"
#include "AknDebug.h"

// CONSTANTS

/**
* These are the fading parameters used in drawing the "hidden" tabs.
* The hidden tabs are drawn with faded graphics context to make them
* appear slightly lighter in color than the actual visible tabs and thus to
* make them stand out from them. These values work for most of the themes
* but it would be better if these were defined in the skin content.
* 
* Currently the fading is not used as custom fading parameters are not
* supported by all display drivers (parameters are not used if
* SYMBIAN_USE_FAST_FADING is defined).
*/
//const TUint8 KHiddenFadeBlackMap( 20 );
//const TUint8 KHiddenFadeWhiteMap( 255 );

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknTabGroupGraphics::CAknTabGroupGraphics
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CAknTabGroupGraphics::CAknTabGroupGraphics()
    {
    iTabGroupBackgroundAvailable = ETrue;
    }

// -----------------------------------------------------------------------------
// CAknTabGroupGraphics::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CAknTabGroupGraphics::ConstructL()
    {
    TRAPD( err, LoadTabGraphicsL() );
    if ( err != KErrNone )
        {
        iTabGroupBackgroundAvailable = EFalse;
        }
    }

// -----------------------------------------------------------------------------
// CAknTabGroupGraphics::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CAknTabGroupGraphics* CAknTabGroupGraphics::NewL()
    {
    CAknTabGroupGraphics* self =
        new (ELeave) CAknTabGroupGraphics();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------
//
CAknTabGroupGraphics::~CAknTabGroupGraphics()
    {
    delete iActiveTabLeft;
    delete iActiveTabLeftMask;
    delete iActiveTabMiddle;
    delete iActiveTabMiddleMask;
    delete iActiveTabRight;
    delete iActiveTabRightMask;

    delete iPassiveTabLeft;
    delete iPassiveTabLeftMask;
    delete iPassiveTabMiddle;
    delete iPassiveTabMiddleMask;
    delete iPassiveTabRight;
    delete iPassiveTabRightMask;
    }

void CAknTabGroupGraphics::SetTabGroupBackgroundParent( TRect aParent )
    {
    iTabGroupBackgroundParent = aParent;
    }
    
#if 0

CAknTabGroupGraphics::SAknTabGroupBackground CAknTabGroupGraphics::CreateTabGroupBackgroundL( TInt aAvkonBitmapId)
    {
    CAknTabGroupGraphics::SAknTabGroupBackground emptyTabGroupBackGround;

    if ( !TabGroupBackgroundAvailable() )
        {
        return emptyTabGroupBackGround;
        }

    TBool longTabs    = EFalse;
    TInt numberOfTabs = 0;
    TInt activeTab    = 0;

    switch ( aAvkonBitmapId )
        {
        case EMbmAvkonQgn_graf_tab_21:
            {
            longTabs     = EFalse;
            numberOfTabs = 2;
            activeTab    = 1;
            break;
            }
        case EMbmAvkonQgn_graf_tab_22:
            {
            longTabs     = EFalse;
            numberOfTabs = 2;
            activeTab    = 2;
            break;
            }
        case EMbmAvkonQgn_graf_tab_31:
            {
            longTabs     = EFalse;
            numberOfTabs = 3;
            activeTab    = 1;
            break;
            }
        case EMbmAvkonQgn_graf_tab_32:
            {
            longTabs     = EFalse;
            numberOfTabs = 3;
            activeTab    = 2;
            break;
            }
        case EMbmAvkonQgn_graf_tab_33:
            {
            longTabs     = EFalse;
            numberOfTabs = 3;
            activeTab    = 3;
            break;
            }
        case EMbmAvkonQgn_graf_tab_41:
            {
            longTabs     = EFalse;
            numberOfTabs = 4;
            activeTab    = 1;
            break;
            }
        case EMbmAvkonQgn_graf_tab_42:
            {
            longTabs     = EFalse;
            numberOfTabs = 4;
            activeTab    = 2;
            break;
            }
        case EMbmAvkonQgn_graf_tab_43:
            {
            longTabs     = EFalse;
            numberOfTabs = 4;
            activeTab    = 3;
            break;
            }
        case EMbmAvkonQgn_graf_tab_44:
            {
            longTabs     = EFalse;
            numberOfTabs = 4;
            activeTab    = 4;
            break;
            }
        case EMbmAvkonQgn_graf_tab_long_21:
            {
            longTabs     = ETrue;
            numberOfTabs = 2;
            activeTab    = 1;
            break;
            }
        case EMbmAvkonQgn_graf_tab_long_22:
            {
            longTabs     = ETrue;
            numberOfTabs = 2;
            activeTab    = 2;
            break;
            }
        case EMbmAvkonQgn_graf_tab_long_31:
            {
            longTabs     = ETrue;
            numberOfTabs = 3;
            activeTab    = 1;
            break;
            }
        case EMbmAvkonQgn_graf_tab_long_32:
            {
            longTabs     = ETrue;
            numberOfTabs = 3;
            activeTab    = 2;
            break;
            }
        case EMbmAvkonQgn_graf_tab_long_33:
            {
            longTabs     = ETrue;
            numberOfTabs = 3;
            activeTab    = 3;
            break;
            }
        default:
            {
            break;
            }
        }
        
    return CreateTabGroupBackgroundL( longTabs, numberOfTabs, activeTab );
    }

CAknTabGroupGraphics::SAknTabGroupBackground CAknTabGroupGraphics::CreateTabGroupBackgroundL(
    TBool aLongTabs, TInt aNumberOfTabs, TInt aActiveTab )
    {
    CAknTabGroupGraphics::SAknTabGroupBackground       tabGroupBackGround;
    CAknTabGroupGraphics::SAknTabGroupBackgroundLayout tabGroupBackGroundLayout;

    AknIconConfig::TPreferredDisplayMode mode;
    AknIconConfig::PreferredDisplayMode( mode,
                                         AknIconConfig::EImageTypeOffscreen );

    TDisplayMode bitmapDisplayMode = mode.iBitmapMode;
    TDisplayMode maskDisplayMode   = EGray256;
    TSize size( iTabGroupBackgroundParent.Size() );

    // BITMAP
    tabGroupBackGround.iBitmap = new (ELeave) CFbsBitmap();
    CleanupStack::PushL( tabGroupBackGround.iBitmap );
    User::LeaveIfError( tabGroupBackGround.iBitmap->Create( size, bitmapDisplayMode ) );
    CFbsBitmapDevice* bitmapDevice = CFbsBitmapDevice::NewL( tabGroupBackGround.iBitmap );
    CleanupStack::PushL( bitmapDevice );
    CFbsBitGc* bitmapGc;
    User::LeaveIfError( bitmapDevice->CreateContext( bitmapGc ) );

    // Clear background first...
    bitmapGc->SetBrushColor( KRgbBlack );
    bitmapGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
    bitmapGc->DrawRect( iTabGroupBackgroundParent );

    bitmapGc->SetBrushStyle( CGraphicsContext::ENullBrush );
    DrawTabGroupBackgroundL( CAknTabGroupGraphics::ENormal,
                             aLongTabs,
                             aNumberOfTabs,
                             aActiveTab,
                             bitmapGc,
                             tabGroupBackGroundLayout,
                             ENone );
    delete bitmapGc;

    CleanupStack::Pop( 2, tabGroupBackGround.iBitmap );
    delete bitmapDevice;
    bitmapGc = NULL;
    bitmapDevice = NULL;

    // MASK
    tabGroupBackGround.iMask = new (ELeave) CFbsBitmap();
    CleanupStack::PushL( tabGroupBackGround.iMask );
    User::LeaveIfError( tabGroupBackGround.iMask->Create( size, maskDisplayMode ) );
    bitmapDevice = CFbsBitmapDevice::NewL( tabGroupBackGround.iMask );
    CleanupStack::PushL( bitmapDevice );
    User::LeaveIfError( bitmapDevice->CreateContext( bitmapGc ) );

    // Clear background first...
    bitmapGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
    if ( maskDisplayMode == EGray256 )
        {
        bitmapGc->SetBrushColor( KRgbBlack );
        }
    else
        {
        bitmapGc->SetBrushColor( KRgbWhite );
        }
    bitmapGc->DrawRect( iTabGroupBackgroundParent );

    bitmapGc->SetBrushStyle( CGraphicsContext::ENullBrush );
    DrawTabGroupBackgroundL( CAknTabGroupGraphics::EMaskOnly,
                             aLongTabs,
                             aNumberOfTabs,
                             aActiveTab,
                             bitmapGc,
                             tabGroupBackGroundLayout,
                             ENone);
    delete bitmapGc;

    CleanupStack::Pop( 2, tabGroupBackGround.iMask );
    delete bitmapDevice;

    return tabGroupBackGround;
    }
    
#endif


// ---------------------------------------------------------------------------
// Draws normal tab background from given parameters.
// ---------------------------------------------------------------------------
//
void CAknTabGroupGraphics::DrawTabGroupBackgroundL(
    TTabDrawMode aTabDrawMode,
    TBool aLongTabs,
    TInt aNumberOfTabs,
    TInt aActiveTab,
    CBitmapContext* aGc,
    SAknTabGroupBackgroundLayout& aLayout,
    TTabsHidden aTabsHidden,
    TTabAnimationType aAnimation ) const
    {
    switch ( aNumberOfTabs )
        {
        case 2:
            {
            if ( aLongTabs )
                {
                DrawTwoLongTabBackground( aTabDrawMode,
                                          aActiveTab,
                                          aGc,
                                          aLayout );
                }
            else
                {
                DrawTwoTabBackground( aTabDrawMode,
                                      aActiveTab,
                                      aGc,
                                      aLayout );
                }
            break;
            }
        case 3:
            {
            if ( aLongTabs )
                {
                DrawThreeLongTabBackground( aTabDrawMode,
                                            aActiveTab,
                                            aGc,
                                            aLayout );
                }
            else
                {
                DrawThreeTabBackground( aTabDrawMode,
                                        aActiveTab,
                                        aGc,
                                        aLayout,
                                        aTabsHidden,
                                        aAnimation );
                }
            break;
            }
        case 4:
            {
            DrawFourTabBackground( aTabDrawMode,
                                   aActiveTab,
                                   aGc,
                                   aLayout );
            break;
            }
        default:
            {
#ifdef AVKON_RDEBUG_ERROR
            RDebug::Print( _L("CAknTabGroupGraphics: Unknown tab layout !") );
#endif
            }
        }

    if ( !aLayout.iUse )
        {
        aLayout.iFirstTab.iActive  = EFalse;
        aLayout.iSecondTab.iActive = EFalse;
        aLayout.iThirdTab.iActive  = EFalse;
        aLayout.iFourthTab.iActive = EFalse;

        if ( aActiveTab == 1 )
            {
            aLayout.iFirstTab.iActive = ETrue;
            }
        else if ( aActiveTab == 2 )
            {
            aLayout.iSecondTab.iActive = ETrue;
            }
        else if ( aActiveTab == 3 )
            {
            aLayout.iThirdTab.iActive = ETrue;
            }
        else if ( aActiveTab == 4 )
            {
            aLayout.iFourthTab.iActive = ETrue;
            }
        }
    }

void CAknTabGroupGraphics::DrawTabGroupNarrowBackgroundL(
    TTabDrawMode aTabDrawMode,
    TBool aLongTabs,
    TInt aNumberOfTabs,
    TInt aActiveTab,
    CBitmapContext* aGc,
    SAknTabGroupBackgroundLayout& aLayout ) const
    {
    switch ( aNumberOfTabs )
        {
        case 2:
            {
            if ( aLongTabs )
                {
                if ( !aLayout.iUse )
                    {
                    aLayout = TwoLongTabNarrowBackground( aActiveTab );
                    }
                aLayout.iUse = ETrue;
                DrawTwoLongTabNarrowBackground( aTabDrawMode,
                                                aActiveTab,
                                                aGc,
                                                aLayout );
                }
            else
                {
                if ( !aLayout.iUse )
                    {
                    aLayout = TwoTabNarrowBackground( aActiveTab );
                    }
                aLayout.iUse = ETrue;
                DrawTwoTabNarrowBackground( aTabDrawMode,
                                            aActiveTab,
                                            aGc,
                                            aLayout );
                }
            break;
            }
        case 3:
            {
            if ( aLongTabs )
                {
                if ( !aLayout.iUse )
                    {
                    aLayout = ThreeLongTabNarrowBackground( aActiveTab );
                    }
                aLayout.iUse = ETrue;
                DrawThreeLongTabNarrowBackground( aTabDrawMode,
                                                  aActiveTab,
                                                  aGc,
                                                  aLayout );
                }
            else
                {
                if ( !aLayout.iUse )
                    {
                    aLayout = ThreeTabNarrowBackground( aActiveTab );
                    }
                aLayout.iUse = ETrue;
                DrawThreeTabNarrowBackground( aTabDrawMode,
                                              aActiveTab,
                                              aGc,
                                              aLayout );
                }
            break;
            }
        case 4:
            {
            if ( !aLayout.iUse )
                {
                aLayout = FourTabNarrowBackground( aActiveTab );
                }
            aLayout.iUse = ETrue;
            DrawFourTabNarrowBackground( aTabDrawMode,
                                         aActiveTab,
                                         aGc,
                                         aLayout );
            break;
            }
        default:
            {
#ifdef AVKON_RDEBUG_ERROR
            RDebug::Print( _L("CAknTabGroupGraphics: Unknown tab layout !") );
#endif
            }
        }

        if ( !aLayout.iUse )
            {
            aLayout.iFirstTab.iActive  = EFalse;
            aLayout.iSecondTab.iActive = EFalse;
            aLayout.iThirdTab.iActive  = EFalse;
            aLayout.iFourthTab.iActive = EFalse;

            if ( aActiveTab == 1 )
                {
                aLayout.iFirstTab.iActive = ETrue;
                }
            else if ( aActiveTab == 2 )
                {
                aLayout.iSecondTab.iActive = ETrue;
                }
            else if ( aActiveTab == 3 )
                {
                aLayout.iThirdTab.iActive = ETrue;
                }
            else if ( aActiveTab == 4 )
                {
                aLayout.iFourthTab.iActive = ETrue;
                }
            }
    }

TBool CAknTabGroupGraphics::TabClickedL( TInt aTabComponent,
                                         const TRect& aTabRect,
                                         const TPoint& aPoint,
                                         TBool aIsActiveTab )
    {
    CFbsBitmap* mask = NULL;

    switch ( aTabComponent )
        {
        case ELeft:
            if ( aIsActiveTab )
                {
                mask = iActiveTabLeftMask;
                }
            else
                {
                mask = iPassiveTabLeftMask;
                }
            break;

        case EMiddle:
            if ( aIsActiveTab )
                {
                mask = iActiveTabMiddleMask;
                }
            else
                {
                mask = iPassiveTabMiddleMask;
                }
            break;

        case ERight:
            if ( aIsActiveTab )
                {
                mask = iActiveTabRightMask;
                }
            else
                {
                mask = iPassiveTabRightMask;
                }
            break;

        default:
            User::Leave( KErrArgument );
            break;
        }

    // scale coordinates to bitmap origin
    TPoint point( aPoint.iX - aTabRect.iTl.iX, aPoint.iY - aTabRect.iTl.iY );

    if ( AknStatuspaneUtils::StaconPaneActive() )
        {
        point.iY = aTabRect.iBr.iY - aPoint.iY;
        }

    TBool retval = EFalse;
    TRgb pixel;
    // Note that mask must be in uncomressed state here.
    // That is taken care of in CAknTabGroupGraphics::LoadTabGraphicsL().
    mask->GetPixel( pixel, point );

    if ( pixel != KRgbBlack )
        {
        retval = ETrue;
        }

    return retval;
    }


// ---------------------------------------------------------------------------
// Gets the whole tab rectangle in relation to the tab group container.
// ---------------------------------------------------------------------------
//
TRect CAknTabGroupGraphics::TabRectFromLayout(
    const SAknTabLayout& aLayout )
    {
    TRect tabRect( aLayout.iLeft );
    tabRect.BoundingRect( aLayout.iMiddle );
    tabRect.BoundingRect( aLayout.iRight );
    return tabRect;
    }


// ---------------------------------------------------------------------------
// Adjusts the tab part rectangles by the specified x and y offsets.
// ---------------------------------------------------------------------------
//
void CAknTabGroupGraphics::AdjustTabLayoutRect(
    SAknTabLayout& aLayout, TInt aXOffset, TInt aYOffset ) const
    {
    aLayout.iLeft.Move( aXOffset, aYOffset );
    aLayout.iRight.Move( aXOffset, aYOffset );
    aLayout.iMiddle.iTl.iX = aLayout.iLeft.iBr.iX;    
    aLayout.iMiddle.iBr.iX = aLayout.iRight.iTl.iX;
    }

CAknTabGroupGraphics::SAknTabGroupBackgroundLayout CAknTabGroupGraphics::TwoTabBackground( TInt aActiveTab ) const
    {
    SAknTabGroupBackgroundLayout aLayout;

    TRect parentRect( iTabGroupBackgroundParent );

    // navi tabs 2 pane
    TRect naviTabsTwoPaneRect(
        RectFromLayout( parentRect,
                        AknLayoutScalable_Avkon::navi_tabs_2_pane() ) );

    TInt tabsActivePassivePaneOption = 0;
    if ( aActiveTab != 1 )
        {
        tabsActivePassivePaneOption = 1;
        }

    // Tabs two passive pane
    TRect tabsTwoPassivePaneRect(
        RectFromLayout( naviTabsTwoPaneRect,
                        AknLayoutScalable_Avkon::tabs_2_passive_pane(
                            tabsActivePassivePaneOption ) ) );

    // Tabs two active pane
    TRect tabsTwoActivePaneRect(
        RectFromLayout( naviTabsTwoPaneRect,
                        AknLayoutScalable_Avkon::tabs_2_active_pane(
                            tabsActivePassivePaneOption ) ) );

    // bg active tab pane
    TRect tabsBackgroundActivePaneRect(
        RectFromLayout( tabsTwoActivePaneRect,
                        AknLayoutScalable_Avkon::bg_active_tab_pane_cp1( 0 ) ) );

    // bg passive tab pane
    TRect tabsBackgroundFirstPassivePaneRect(
        RectFromLayout( tabsTwoPassivePaneRect,
                        AknLayoutScalable_Avkon::bg_passive_tab_pane_cp1( 0 ) ) );

    // Active tab left
    TRect activeTabLeftPaneRect(
        RectFromLayout( tabsBackgroundActivePaneRect,
                        AknLayoutScalable_Avkon::bg_active_tab_pane_g1_cp1() ) );

    // Active tab middle
    TRect activeTabMiddlePaneRect(
        RectFromLayout( tabsBackgroundActivePaneRect,
                        AknLayoutScalable_Avkon::bg_active_tab_pane_g2_cp1() ) );

    // Active tab right
    TRect activeTabRightPaneRect(
        RectFromLayout( tabsBackgroundActivePaneRect,
                        AknLayoutScalable_Avkon::bg_active_tab_pane_g3_cp1() ) );

    // First passive tab left
    TRect firstPassiveTabLeftPaneRect(
        RectFromLayout( tabsBackgroundFirstPassivePaneRect,
                        AknLayoutScalable_Avkon::bg_passive_tab_pane_g1_cp1() ) );

    // First passive tab middle
    TRect firstPassiveTabMiddlePaneRect(
        RectFromLayout( tabsBackgroundFirstPassivePaneRect,
                        AknLayoutScalable_Avkon::bg_passive_tab_pane_g2_cp1() ) );

    // First passive tab right
    TRect firstPassiveTabRightPaneRect(
        RectFromLayout( tabsBackgroundFirstPassivePaneRect,
                        AknLayoutScalable_Avkon::bg_passive_tab_pane_g3_cp1() ) );

    if ( aActiveTab == 1 )
        {
        aLayout.iFirstTab.iLeft   = activeTabLeftPaneRect;
        aLayout.iFirstTab.iMiddle = activeTabMiddlePaneRect;
        aLayout.iFirstTab.iRight  = activeTabRightPaneRect;

        aLayout.iSecondTab.iLeft   = firstPassiveTabLeftPaneRect;
        aLayout.iSecondTab.iMiddle = firstPassiveTabMiddlePaneRect;
        aLayout.iSecondTab.iRight  = firstPassiveTabRightPaneRect;
        }
    else
        {
        aLayout.iFirstTab.iLeft   = firstPassiveTabLeftPaneRect;
        aLayout.iFirstTab.iMiddle = firstPassiveTabMiddlePaneRect;
        aLayout.iFirstTab.iRight  = firstPassiveTabRightPaneRect;

        aLayout.iSecondTab.iLeft   = activeTabLeftPaneRect;
        aLayout.iSecondTab.iMiddle = activeTabMiddlePaneRect;
        aLayout.iSecondTab.iRight  = activeTabRightPaneRect;
        }

    TRect nullRect(0,0,0,0);

    aLayout.iThirdTab.iLeft   = nullRect;
    aLayout.iThirdTab.iMiddle = nullRect;
    aLayout.iThirdTab.iRight  = nullRect;

    aLayout.iFourthTab.iLeft   = nullRect;
    aLayout.iFourthTab.iMiddle = nullRect;
    aLayout.iFourthTab.iRight  = nullRect;

    return aLayout;
    }

CAknTabGroupGraphics::SAknTabGroupBackgroundLayout CAknTabGroupGraphics::TwoTabNarrowBackground(TInt aActiveTab) const
    {
    SAknTabGroupBackgroundLayout aLayout;

    // navi tabs pane
    TRect parentRect( NarrowParentRect() );

    // navi tabs 2 pane
    TRect naviTabsTwoPaneRect(
        RectFromLayout( parentRect,
                        AknLayoutScalable_Avkon::navi_tabs_2_pane_srt() ) );

    TInt tabsActivePassivePaneOption = 0;
    if ( aActiveTab == 1 )
        {
        tabsActivePassivePaneOption = 0;
        }
    else
        {
        tabsActivePassivePaneOption = 1;
        }

    // Tabs two passive pane
    TRect tabsTwoPassivePaneRect(
        RectFromLayout( naviTabsTwoPaneRect,
                        AknLayoutScalable_Avkon::tabs_2_passive_pane_srt(
                            tabsActivePassivePaneOption ) ) );

    // Tabs two active pane
    TRect tabsTwoActivePaneRect(
        RectFromLayout( naviTabsTwoPaneRect,
                        AknLayoutScalable_Avkon::tabs_2_active_pane_srt(
                            tabsActivePassivePaneOption ) ) );

    // bg active tab pane
    TRect tabsBackgroundActivePaneRect(
        RectFromLayout( tabsTwoActivePaneRect,
                        AknLayoutScalable_Avkon::bg_active_tab_pane_cp1_srt( 0 ) ) );

    // bg passive tab pane
    TRect tabsBackgroundFirstPassivePaneRect(
        RectFromLayout( tabsTwoPassivePaneRect,
                        AknLayoutScalable_Avkon::bg_passive_tab_pane_cp1_srt( 0 ) ) );


    // Active tab left
    TRect activeTabLeftPaneRect(
        RectFromLayout( tabsBackgroundActivePaneRect,
                        AknLayoutScalable_Avkon::bg_active_tab_pane_g1_cp1_srt() ) );

    // Active tab middle
    TRect activeTabMiddlePaneRect(
        RectFromLayout( tabsBackgroundActivePaneRect,
                        AknLayoutScalable_Avkon::bg_active_tab_pane_g2_cp1_srt() ) );

    // Active tab right
    TRect activeTabRightPaneRect(
        RectFromLayout( tabsBackgroundActivePaneRect,
                        AknLayoutScalable_Avkon::bg_active_tab_pane_g3_cp1_srt() ) );



    // First passive tab left
    TRect firstPassiveTabLeftPaneRect(
        RectFromLayout( tabsBackgroundFirstPassivePaneRect,
                        AknLayoutScalable_Avkon::bg_passive_tab_pane_g1_cp1_srt() ) );

    // First passive tab middle
    TRect firstPassiveTabMiddlePaneRect(
        RectFromLayout( tabsBackgroundFirstPassivePaneRect,
                        AknLayoutScalable_Avkon::bg_passive_tab_pane_g2_cp1_srt() ) );

    // First passive tab right
    TRect firstPassiveTabRightPaneRect(
        RectFromLayout( tabsBackgroundFirstPassivePaneRect,
                        AknLayoutScalable_Avkon::bg_passive_tab_pane_g3_cp1_srt() ) );

    if ( aActiveTab == 1 )
        {
        aLayout.iFirstTab.iLeft   = activeTabLeftPaneRect;
        aLayout.iFirstTab.iMiddle = activeTabMiddlePaneRect;
        aLayout.iFirstTab.iRight  = activeTabRightPaneRect;

        aLayout.iSecondTab.iLeft   = firstPassiveTabLeftPaneRect;
        aLayout.iSecondTab.iMiddle = firstPassiveTabMiddlePaneRect;
        aLayout.iSecondTab.iRight  = firstPassiveTabRightPaneRect;
        }
    else
        {
        aLayout.iFirstTab.iLeft   = firstPassiveTabLeftPaneRect;
        aLayout.iFirstTab.iMiddle = firstPassiveTabMiddlePaneRect;
        aLayout.iFirstTab.iRight  = firstPassiveTabRightPaneRect;

        aLayout.iSecondTab.iLeft   = activeTabLeftPaneRect;
        aLayout.iSecondTab.iMiddle = activeTabMiddlePaneRect;
        aLayout.iSecondTab.iRight  = activeTabRightPaneRect;
        }

    TRect nullRect( 0,0,0,0 );
    
    aLayout.iThirdTab.iLeft   = nullRect;
    aLayout.iThirdTab.iMiddle = nullRect;
    aLayout.iThirdTab.iRight  = nullRect;

    aLayout.iFourthTab.iLeft   = nullRect;
    aLayout.iFourthTab.iMiddle = nullRect;
    aLayout.iFourthTab.iRight  = nullRect;

    return aLayout;
    }

void CAknTabGroupGraphics::DrawTwoTabBackground(
    TTabDrawMode aTabDrawMode,
    TInt aActiveTab,
    CBitmapContext* aGc,
    SAknTabGroupBackgroundLayout& aLayout ) const
    {
    // If not given layout, then get the default layout
    if ( !aLayout.iUse )
        {
        aLayout = TwoTabBackground( aActiveTab );
        }

    if ( aActiveTab == 1 )
        {
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iSecondTab.iLeft,
                        aLayout.iSecondTab.iMiddle,
                        aLayout.iSecondTab.iRight,
                        aGc );
                        
        DrawActiveTab( aTabDrawMode,
                       aLayout.iFirstTab.iLeft,
                       aLayout.iFirstTab.iMiddle,
                       aLayout.iFirstTab.iRight,
                       aGc );
        }
    else
        {
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iFirstTab.iLeft,
                        aLayout.iFirstTab.iMiddle,
                        aLayout.iFirstTab.iRight,
                        aGc );

        DrawActiveTab( aTabDrawMode,
                       aLayout.iSecondTab.iLeft,
                       aLayout.iSecondTab.iMiddle,
                       aLayout.iSecondTab.iRight,
                       aGc );
        }
    }

void CAknTabGroupGraphics::DrawTwoTabNarrowBackground(
    TTabDrawMode aTabDrawMode,
    TInt aActiveTab,
    CBitmapContext* aGc,
    SAknTabGroupBackgroundLayout& aLayout ) const
    {
    // If not given layout, then get the default layout
    if ( !aLayout.iUse )
        {
        aLayout = TwoTabBackground( aActiveTab );
        }

    if ( aActiveTab == 1 )
        {
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iSecondTab.iLeft,
                        aLayout.iSecondTab.iMiddle,
                        aLayout.iSecondTab.iRight,
                        aGc );
                        
        DrawActiveTab( aTabDrawMode,
                       aLayout.iFirstTab.iLeft,
                       aLayout.iFirstTab.iMiddle,
                       aLayout.iFirstTab.iRight,
                       aGc );
        }
    else
        {
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iFirstTab.iLeft,
                        aLayout.iFirstTab.iMiddle,
                        aLayout.iFirstTab.iRight,
                        aGc );
                        
        DrawActiveTab( aTabDrawMode,
                       aLayout.iSecondTab.iLeft,
                       aLayout.iSecondTab.iMiddle,
                       aLayout.iSecondTab.iRight,
                       aGc );
        }
    }


// ---------------------------------------------------------------------------
// Extracts tab group background layout from layout data for three tab layout.
// ---------------------------------------------------------------------------
//
CAknTabGroupGraphics::SAknTabGroupBackgroundLayout CAknTabGroupGraphics::ThreeTabBackground(
    TInt aActiveTab ) const
    {
    SAknTabGroupBackgroundLayout layout;

    // parent
    TRect parentRect( iTabGroupBackgroundParent );

    // navi tabs 3 pane
    TRect naviTabsThreePaneRect(
        RectFromLayout( parentRect,
                        AknLayoutScalable_Avkon::navi_tabs_3_pane() ) );

    TRect tabsPassiveFirstPaneRect;
    TRect tabsPassiveSecondPaneRect;
    TRect tabsActivePaneRect;

    // We don't want to use options, just assume that active and passive tabs are same sizes.
    TRect parent( naviTabsThreePaneRect );
    TAknWindowComponentLayout firstTab(
        AknLayoutScalable_Avkon::tabs_3_active_pane( 0 ) );
    TAknWindowComponentLayout secondTab(
        AknLayoutScalable_Avkon::tabs_3_passive_pane( 0 ) );
    TAknWindowComponentLayout thirdTab(
        AknLayoutScalable_Avkon::tabs_3_passive_pane_cp( 0 ) );

	// Revise the invalid parameter.
    if (aActiveTab <= 0)
        aActiveTab = 1;
    
    if ( aActiveTab == 1 )
        {
        tabsActivePaneRect        = RectFromLayout( parent, firstTab );
        tabsPassiveFirstPaneRect  = RectFromLayout( parent, secondTab );
        tabsPassiveSecondPaneRect = RectFromLayout( parent, thirdTab );
        }
    else if ( aActiveTab == 2 )
        {
        tabsPassiveFirstPaneRect  = RectFromLayout( parent, firstTab );
        tabsActivePaneRect        = RectFromLayout( parent, secondTab );
        tabsPassiveSecondPaneRect = RectFromLayout( parent, thirdTab );
        }
    else if ( aActiveTab == 3 )
        {
        tabsPassiveFirstPaneRect  = RectFromLayout( parent, firstTab );
        tabsPassiveSecondPaneRect = RectFromLayout( parent, secondTab );
        tabsActivePaneRect        = RectFromLayout( parent, thirdTab );
        }

    // Tabs 3 first passive tab pane
    TRect tabsThreePassiveFirstPaneRect( tabsPassiveFirstPaneRect );

    // Tabs 3 second passive tab pane
    TRect tabsThreePassiveSecondPaneRect( tabsPassiveSecondPaneRect );

    // Tabs 3 active tab pane
    TRect tabsThreeActivePaneRect( tabsActivePaneRect );
    
    TAknWindowComponentLayout passivePaneLayout(
        AknLayoutScalable_Avkon::bg_passive_tab_pane_cp2( 0 ) );
    
    TAknWindowComponentLayout passiveTabLayout1(
        AknLayoutScalable_Avkon::bg_passive_tab_pane_g1_cp2() );
        
    TAknWindowComponentLayout passiveTabLayout2(
        AknLayoutScalable_Avkon::bg_passive_tab_pane_g2_cp2() );
        
    TAknWindowComponentLayout passiveTabLayout3(
        AknLayoutScalable_Avkon::bg_passive_tab_pane_g3_cp2() );
        
    // bg active tab pane
    TRect tabsBackgroundActivePaneRect(
    RectFromLayout( tabsThreeActivePaneRect,
                    AknLayoutScalable_Avkon::bg_active_tab_pane_cp2( 0 ) ) );

    // bg first passive tab pane
    TRect tabsBackgroundFirstPassivePaneRect(
        RectFromLayout( tabsThreePassiveFirstPaneRect,
                        passivePaneLayout ) );

    // bg second passive tab pane
    TRect tabsBackgroundSecondPassivePaneRect(
        RectFromLayout( tabsThreePassiveSecondPaneRect,
                        passivePaneLayout ) );


    // Active tab left
    TRect activeTabLeftPaneRect(
        RectFromLayout( tabsBackgroundActivePaneRect,
                        AknLayoutScalable_Avkon::bg_active_tab_pane_g1_cp2() ) );

    // Active tab middle
    TRect activeTabMiddlePaneRect(
        RectFromLayout( tabsBackgroundActivePaneRect,
                        AknLayoutScalable_Avkon::bg_active_tab_pane_g2_cp2() ) );

    // Active tab right
    TRect activeTabRightPaneRect(
        RectFromLayout( tabsBackgroundActivePaneRect,
                        AknLayoutScalable_Avkon::bg_active_tab_pane_g3_cp2() ) );


    // First passive tab left
    TRect firstPassiveTabLeftPaneRect(
        RectFromLayout( tabsBackgroundFirstPassivePaneRect,
                        passiveTabLayout1 ) );

    // First passive tab middle
    TRect firstPassiveTabMiddlePaneRect(
        RectFromLayout( tabsBackgroundFirstPassivePaneRect,
                        passiveTabLayout2 ) );

    // First passive tab right
    TRect firstPassiveTabRightPaneRect(
        RectFromLayout( tabsBackgroundFirstPassivePaneRect,
                        passiveTabLayout3 ) );


    // Second passive tab left
    TRect secondPassiveTabLeftPaneRect(
        RectFromLayout( tabsBackgroundSecondPassivePaneRect,
                        passiveTabLayout1 ) );

    // Second passive tab middle
    TRect secondPassiveTabMiddlePaneRect(
        RectFromLayout( tabsBackgroundSecondPassivePaneRect,
                        passiveTabLayout2 ) );

    // Second passive tab right
    TRect secondPassiveTabRightPaneRect(
        RectFromLayout( tabsBackgroundSecondPassivePaneRect,
                        passiveTabLayout3 ) );

    if ( aActiveTab == 1 )
        {
        layout.iFirstTab.iLeft   = activeTabLeftPaneRect;
        layout.iFirstTab.iMiddle = activeTabMiddlePaneRect;
        layout.iFirstTab.iRight  = activeTabRightPaneRect;

        layout.iSecondTab.iLeft   = firstPassiveTabLeftPaneRect;
        layout.iSecondTab.iMiddle = firstPassiveTabMiddlePaneRect;
        layout.iSecondTab.iRight  = firstPassiveTabRightPaneRect;

        layout.iThirdTab.iLeft   = secondPassiveTabLeftPaneRect;
        layout.iThirdTab.iMiddle = secondPassiveTabMiddlePaneRect;
        layout.iThirdTab.iRight  = secondPassiveTabRightPaneRect;
        }
    else if ( aActiveTab == 2 )
        {
        layout.iFirstTab.iLeft   = firstPassiveTabLeftPaneRect;
        layout.iFirstTab.iMiddle = firstPassiveTabMiddlePaneRect;
        layout.iFirstTab.iRight  = firstPassiveTabRightPaneRect;

        layout.iSecondTab.iLeft   = activeTabLeftPaneRect;
        layout.iSecondTab.iMiddle = activeTabMiddlePaneRect;
        layout.iSecondTab.iRight  = activeTabRightPaneRect;

        layout.iThirdTab.iLeft   = secondPassiveTabLeftPaneRect;
        layout.iThirdTab.iMiddle = secondPassiveTabMiddlePaneRect;
        layout.iThirdTab.iRight  = secondPassiveTabRightPaneRect;
        }
    else if ( aActiveTab == 3 )
        {
        layout.iFirstTab.iLeft   = firstPassiveTabLeftPaneRect;
        layout.iFirstTab.iMiddle = firstPassiveTabMiddlePaneRect;
        layout.iFirstTab.iRight  = firstPassiveTabRightPaneRect;

        layout.iSecondTab.iLeft   = secondPassiveTabLeftPaneRect;
        layout.iSecondTab.iMiddle = secondPassiveTabMiddlePaneRect;
        layout.iSecondTab.iRight  = secondPassiveTabRightPaneRect;

        layout.iThirdTab.iLeft   = activeTabLeftPaneRect;
        layout.iThirdTab.iMiddle = activeTabMiddlePaneRect;
        layout.iThirdTab.iRight  = activeTabRightPaneRect;
        }

    layout.iFourthTab.iLeft.SetRect( 0, 0, 0, 0 );
    layout.iFourthTab.iMiddle.SetRect( 0, 0, 0, 0 );
    layout.iFourthTab.iRight.SetRect( 0, 0, 0, 0 );
    
    // Calculate the amount of horizontal overlap in the tab backgrounds
    // since the hidden tab rectangles are not read from layout data
    // and must be adjusted to correspond with the "real" tabs.
    TInt xOverlap = layout.iFirstTab.iRight.iTl.iX -
                        layout.iSecondTab.iLeft.iTl.iX;
    
    layout.iHiddenTabLeft.iLeft = TRect( layout.iFirstTab.iLeft.iTl.iX -
                                             layout.iFirstTab.iMiddle.Width() -
                                             layout.iFirstTab.iLeft.Width(),
                                          layout.iFirstTab.iLeft.iTl.iY,
                                          layout.iFirstTab.iLeft.iTl.iX -
                                              layout.iFirstTab.iMiddle.Width(),
                                          layout.iFirstTab.iLeft.iBr.iY  );
    layout.iHiddenTabLeft.iLeft.Move( xOverlap, 0 );
    
    layout.iHiddenTabLeft.iMiddle = TRect( layout.iFirstTab.iLeft.iTl.iX -
                                               layout.iFirstTab.iMiddle.Width(),
                                           layout.iFirstTab.iLeft.iTl.iY,
                                           layout.iFirstTab.iLeft.iTl.iX,
                                           layout.iFirstTab.iLeft.iBr.iY );
    layout.iHiddenTabLeft.iMiddle.Move( xOverlap, 0 );
    
    layout.iHiddenTabLeft.iRight = layout.iFirstTab.iLeft;
    layout.iHiddenTabLeft.iRight.Move( xOverlap, 0 );
    
    layout.iHiddenTabRight.iLeft = layout.iThirdTab.iRight;
    layout.iHiddenTabRight.iLeft.Move( -xOverlap, 0 );
    layout.iHiddenTabRight.iMiddle = TRect( layout.iThirdTab.iRight.iBr.iX,
                                            layout.iThirdTab.iRight.iTl.iY,
                                            layout.iThirdTab.iRight.iBr.iX +
                                                layout.iThirdTab.iMiddle.Width(),
                                            layout.iThirdTab.iRight.iBr.iY );
    layout.iHiddenTabRight.iMiddle.Move( -xOverlap, 0 );
    
    layout.iHiddenTabRight.iRight = TRect( layout.iThirdTab.iRight.iBr.iX +
                                               layout.iThirdTab.iMiddle.Width(),
                                           layout.iThirdTab.iRight.iTl.iY,
                                           layout.iThirdTab.iRight.iBr.iX +
                                               layout.iThirdTab.iMiddle.Width() +
                                               layout.iThirdTab.iRight.Width(),
                                           layout.iThirdTab.iRight.iBr.iY );
    layout.iHiddenTabRight.iRight.Move( -xOverlap, 0 );

    return layout;
    }

CAknTabGroupGraphics::SAknTabGroupBackgroundLayout CAknTabGroupGraphics::ThreeTabNarrowBackground(TInt aActiveTab) const
    {
    SAknTabGroupBackgroundLayout aLayout;

    // navi tabs pane
    TRect parentRect( NarrowParentRect() );

    // navi tabs 3 pane
    TRect naviTabsThreePaneRect(
        RectFromLayout( parentRect,
                        AknLayoutScalable_Avkon::navi_tabs_3_pane_srt() ) );

    TRect tabsPassiveFirstPaneRect;
    TRect tabsPassiveSecondPaneRect;
    TRect tabsActivePaneRect;

    // We don't want to use options, just assume that active and passive tabs are same sizes.
    TRect parent = naviTabsThreePaneRect;
    TAknWindowComponentLayout aFirstTab(
        AknLayoutScalable_Avkon::tabs_3_active_pane_srt( 0 ) );
    TAknWindowComponentLayout aSecondTab(
        AknLayoutScalable_Avkon::tabs_3_passive_pane_srt( 0 ) );
    TAknWindowComponentLayout aThirdTab(
        AknLayoutScalable_Avkon::tabs_3_passive_pane_cp_srt( 0 ) );

    if ( aActiveTab == 1 )
        {
        tabsActivePaneRect        =  RectFromLayout( parent, aFirstTab );
        tabsPassiveFirstPaneRect  =  RectFromLayout( parent, aSecondTab );
        tabsPassiveSecondPaneRect =  RectFromLayout( parent, aThirdTab );
        }
    else if ( aActiveTab == 2 )
        {
        tabsPassiveFirstPaneRect  =  RectFromLayout( parent, aFirstTab );
        tabsActivePaneRect        =  RectFromLayout( parent, aSecondTab );
        tabsPassiveSecondPaneRect =  RectFromLayout( parent, aThirdTab );
        }
    else if ( aActiveTab == 3 )
        {
        tabsPassiveFirstPaneRect  =  RectFromLayout( parent, aFirstTab );
        tabsPassiveSecondPaneRect =  RectFromLayout( parent, aSecondTab );
        tabsActivePaneRect        =  RectFromLayout( parent, aThirdTab );
        }

    // Tabs 3 first passive tab pane
    TRect tabsThreePassiveFirstPaneRect( tabsPassiveFirstPaneRect );

    // Tabs 3 second passive tab pane
    TRect tabsThreePassiveSecondPaneRect( tabsPassiveSecondPaneRect );

    // Tabs 3 active tab pane
    TRect tabsThreeActivePaneRect( tabsActivePaneRect );
    
    TAknWindowComponentLayout passivePaneLayout(
        AknLayoutScalable_Avkon::bg_passive_tab_pane_cp2_srt( 0 ) );
    
    TAknWindowComponentLayout passiveTabLayout1(
        AknLayoutScalable_Avkon::bg_passive_tab_pane_g1_cp2_srt() );
        
    TAknWindowComponentLayout passiveTabLayout2(
        AknLayoutScalable_Avkon::bg_passive_tab_pane_g2_cp2_srt() );
        
    TAknWindowComponentLayout passiveTabLayout3(
        AknLayoutScalable_Avkon::bg_passive_tab_pane_g3_cp2_srt() );

    // bg active tab pane
    TRect tabsBackgroundActivePaneRect(
        RectFromLayout( tabsThreeActivePaneRect,
                        AknLayoutScalable_Avkon::bg_active_tab_pane_cp2_srt( 0 ) ) );

    // bg first passive tab pane
    TRect tabsBackgroundFirstPassivePaneRect(
        RectFromLayout( tabsThreePassiveFirstPaneRect,
                        passivePaneLayout ) );

    // bg second passive tab pane
    TRect tabsBackgroundSecondPassivePaneRect(
        RectFromLayout( tabsThreePassiveSecondPaneRect,
                        passivePaneLayout ) );

    // Active tab left
    TRect activeTabLeftPaneRect(
        RectFromLayout( tabsBackgroundActivePaneRect,
                        AknLayoutScalable_Avkon::bg_active_tab_pane_g1_cp2_srt() ) );

    // Active tab middle
    TRect activeTabMiddlePaneRect(
        RectFromLayout( tabsBackgroundActivePaneRect,
                        AknLayoutScalable_Avkon::bg_active_tab_pane_g2_cp2_srt() ) );

    // Active tab right
    TRect activeTabRightPaneRect(
        RectFromLayout( tabsBackgroundActivePaneRect,
                        AknLayoutScalable_Avkon::bg_active_tab_pane_g3_cp2_srt() ) );

    // First passive tab left
    TRect firstPassiveTabLeftPaneRect(
        RectFromLayout( tabsBackgroundFirstPassivePaneRect,
                        passiveTabLayout1 ) );

    // First passive tab middle
    TRect firstPassiveTabMiddlePaneRect(
        RectFromLayout( tabsBackgroundFirstPassivePaneRect,
                        passiveTabLayout2 ) );

    // First passive tab right
    TRect firstPassiveTabRightPaneRect(
        RectFromLayout( tabsBackgroundFirstPassivePaneRect,
                        passiveTabLayout3 ) );

    // Second passive tab left
    TRect secondPassiveTabLeftPaneRect(
        RectFromLayout( tabsBackgroundSecondPassivePaneRect,
                        passiveTabLayout1 ) );

    // Second passive tab middle
    TRect secondPassiveTabMiddlePaneRect(
        RectFromLayout( tabsBackgroundSecondPassivePaneRect,
                        passiveTabLayout2 ) );

    // Second passive tab right
    TRect secondPassiveTabRightPaneRect(
        RectFromLayout( tabsBackgroundSecondPassivePaneRect,
                        passiveTabLayout3 ) );

    if ( aActiveTab == 1 )
        {
        aLayout.iFirstTab.iLeft   = activeTabLeftPaneRect;
        aLayout.iFirstTab.iMiddle = activeTabMiddlePaneRect;
        aLayout.iFirstTab.iRight  = activeTabRightPaneRect;

        aLayout.iSecondTab.iLeft   = firstPassiveTabLeftPaneRect;
        aLayout.iSecondTab.iMiddle = firstPassiveTabMiddlePaneRect;
        aLayout.iSecondTab.iRight  = firstPassiveTabRightPaneRect;

        aLayout.iThirdTab.iLeft   = secondPassiveTabLeftPaneRect;
        aLayout.iThirdTab.iMiddle = secondPassiveTabMiddlePaneRect;
        aLayout.iThirdTab.iRight  = secondPassiveTabRightPaneRect;
        }
    else if ( aActiveTab == 2 )
        {
        aLayout.iFirstTab.iLeft   = firstPassiveTabLeftPaneRect;
        aLayout.iFirstTab.iMiddle = firstPassiveTabMiddlePaneRect;
        aLayout.iFirstTab.iRight  = firstPassiveTabRightPaneRect;

        aLayout.iSecondTab.iLeft   = activeTabLeftPaneRect;
        aLayout.iSecondTab.iMiddle = activeTabMiddlePaneRect;
        aLayout.iSecondTab.iRight  = activeTabRightPaneRect;

        aLayout.iThirdTab.iLeft   = secondPassiveTabLeftPaneRect;
        aLayout.iThirdTab.iMiddle = secondPassiveTabMiddlePaneRect;
        aLayout.iThirdTab.iRight  = secondPassiveTabRightPaneRect;
        }
    else if ( aActiveTab == 3 )
        {
        aLayout.iFirstTab.iLeft   = firstPassiveTabLeftPaneRect;
        aLayout.iFirstTab.iMiddle = firstPassiveTabMiddlePaneRect;
        aLayout.iFirstTab.iRight  = firstPassiveTabRightPaneRect;

        aLayout.iSecondTab.iLeft   = secondPassiveTabLeftPaneRect;
        aLayout.iSecondTab.iMiddle = secondPassiveTabMiddlePaneRect;
        aLayout.iSecondTab.iRight  = secondPassiveTabRightPaneRect;

        aLayout.iThirdTab.iLeft   = activeTabLeftPaneRect;
        aLayout.iThirdTab.iMiddle = activeTabMiddlePaneRect;
        aLayout.iThirdTab.iRight  = activeTabRightPaneRect;
        }

    aLayout.iFourthTab.iLeft = TRect(0,0,0,0);
    aLayout.iFourthTab.iMiddle = TRect(0,0,0,0);
    aLayout.iFourthTab.iRight = TRect(0,0,0,0);

    return aLayout;
    }


// ---------------------------------------------------------------------------
// Draws the tab group background in three tab layout.
// ---------------------------------------------------------------------------
//
void CAknTabGroupGraphics::DrawThreeTabBackground(
    TTabDrawMode aTabDrawMode,
    TInt aActiveTab,
    CBitmapContext* aGc,
    SAknTabGroupBackgroundLayout& aLayout,
    TTabsHidden aTabsHidden,
    TTabAnimationType aAnimation ) const
    {
    TInt animActiveTab( aActiveTab );
    if ( aAnimation && aActiveTab == 2 )
        {
        // Move the tab highlight already during the animation.
        animActiveTab = aAnimation == ECycleToLeft ? aActiveTab - 1 :
                                                     aActiveTab + 1;
        }

    // If not given layout, then get the default layout.
    if ( !aLayout.iUse )
        {
        aLayout = ThreeTabBackground( animActiveTab );
        }

    TInt xOffset( aLayout.iFirstTab.iRight.iBr.iX -
                      aLayout.iSecondTab.iLeft.iTl.iX );
    
    if ( aActiveTab == 1 )
        {
        if ( aTabsHidden == EOnRightSide )
            {
            DrawPassiveTab( aTabDrawMode,
                            aLayout.iHiddenTabRight.iLeft,
                            aLayout.iHiddenTabRight.iMiddle,
                            aLayout.iHiddenTabRight.iRight,
                            aGc,
                            ETrue );
            }

        DrawPassiveTab( aTabDrawMode,
                        aLayout.iThirdTab.iLeft,
                        aLayout.iThirdTab.iMiddle,
                        aLayout.iThirdTab.iRight,
                        aGc );

        DrawPassiveTab( aTabDrawMode,
                        aLayout.iSecondTab.iLeft,
                        aLayout.iSecondTab.iMiddle,
                        aLayout.iSecondTab.iRight,
                        aGc );

        DrawActiveTab( aTabDrawMode,
                       aLayout.iFirstTab.iLeft,
                       aLayout.iFirstTab.iMiddle,
                       aLayout.iFirstTab.iRight,
                       aGc );
        }
    else if ( aActiveTab == 2 )
        {
        switch ( aTabsHidden )
            {
            case EOnLeftSide:
                {
                TRect bitRect( aLayout.iHiddenTabLeft.iLeft );
                bitRect.Resize( xOffset, 0 );
                DrawPassiveTabBit( aTabDrawMode,
                                   ERight,
                                   bitRect,
                                   aGc );
                DrawPassiveTab( aTabDrawMode,
                                aLayout.iHiddenTabLeft.iLeft,
                                aLayout.iHiddenTabLeft.iMiddle,
                                aLayout.iHiddenTabLeft.iRight,
                                aGc,
                                aAnimation != ECycleToLeft ? ETrue : EFalse  );
                break;
                }
            case EOnRightSide:
                {
                TRect bitRect( aLayout.iHiddenTabRight.iRight );
                bitRect.Move( -xOffset, 0 );
                bitRect.Resize( xOffset, 0 );
                DrawPassiveTabBit( aTabDrawMode,
                                   ELeft,
                                   bitRect,
                                   aGc );
                DrawPassiveTab( aTabDrawMode,
                                aLayout.iHiddenTabRight.iLeft,
                                aLayout.iHiddenTabRight.iMiddle,
                                aLayout.iHiddenTabRight.iRight,
                                aGc,
                                aAnimation != ECycleToRight ? ETrue : EFalse  );
                break;
                }
            case EOnBothSides:
                {
                DrawPassiveTab( aTabDrawMode,
                                aLayout.iHiddenTabLeft.iLeft,
                                aLayout.iHiddenTabLeft.iMiddle,
                                aLayout.iHiddenTabLeft.iRight,
                                aGc,
                                aAnimation != ECycleToLeft ? ETrue : EFalse  );

                DrawPassiveTab( aTabDrawMode,
                                aLayout.iHiddenTabRight.iLeft,
                                aLayout.iHiddenTabRight.iMiddle,
                                aLayout.iHiddenTabRight.iRight,
                                aGc,
                                aAnimation != ECycleToRight ? ETrue : EFalse  );
                break;
                }
            case ETwoOnBothSides:
                {
                TRect bitRect( aLayout.iHiddenTabLeft.iLeft );
                bitRect.Resize( xOffset, 0 );
                DrawPassiveTabBit( aTabDrawMode,
                                   ERight,
                                   bitRect,
                                   aGc );
                DrawPassiveTab( aTabDrawMode,
                                aLayout.iHiddenTabLeft.iLeft,
                                aLayout.iHiddenTabLeft.iMiddle,
                                aLayout.iHiddenTabLeft.iRight,
                                aGc,
                                aAnimation != ECycleToLeft ? ETrue : EFalse );

                bitRect = aLayout.iHiddenTabRight.iRight;
                bitRect.Move( -xOffset, 0 );
                bitRect.Resize( xOffset, 0 );
                DrawPassiveTabBit( aTabDrawMode,
                                   ELeft,
                                   bitRect,
                                   aGc );
                DrawPassiveTab( aTabDrawMode,
                                aLayout.iHiddenTabRight.iLeft,
                                aLayout.iHiddenTabRight.iMiddle,
                                aLayout.iHiddenTabRight.iRight,
                                aGc,
                                aAnimation != ECycleToRight ? ETrue : EFalse);
                break;
                }
            case ENone:
            default:
                {
                break;
                }
            }

        if ( aAnimation == ECycleToLeft )
            {
            DrawPassiveTab( aTabDrawMode,
                            aLayout.iThirdTab.iLeft,
                            aLayout.iThirdTab.iMiddle,
                            aLayout.iThirdTab.iRight,
                            aGc,
                            ETrue );
            DrawPassiveTab( aTabDrawMode,
                            aLayout.iSecondTab.iLeft,
                            aLayout.iSecondTab.iMiddle,
                            aLayout.iSecondTab.iRight,
                            aGc );
             DrawActiveTab( aTabDrawMode,
                            aLayout.iFirstTab.iLeft,
                            aLayout.iFirstTab.iMiddle,
                            aLayout.iFirstTab.iRight,
                            aGc );
            }
        else if ( aAnimation == ECycleToRight )
            {
            DrawPassiveTab( aTabDrawMode,
                            aLayout.iFirstTab.iLeft,
                            aLayout.iFirstTab.iMiddle,
                            aLayout.iFirstTab.iRight,
                            aGc,
                            ETrue );
            DrawPassiveTab( aTabDrawMode,
                            aLayout.iSecondTab.iLeft,
                            aLayout.iSecondTab.iMiddle,
                            aLayout.iSecondTab.iRight,
                            aGc );
            DrawActiveTab( aTabDrawMode,
                           aLayout.iThirdTab.iLeft,
                           aLayout.iThirdTab.iMiddle,
                           aLayout.iThirdTab.iRight,
                           aGc );
            }
        else
            {
            DrawPassiveTab( aTabDrawMode,
                            aLayout.iFirstTab.iLeft,
                            aLayout.iFirstTab.iMiddle,
                            aLayout.iFirstTab.iRight,
                            aGc );
    
            DrawPassiveTab( aTabDrawMode,
                            aLayout.iThirdTab.iLeft,
                            aLayout.iThirdTab.iMiddle,
                            aLayout.iThirdTab.iRight,
                            aGc );
    
            if ( aAnimation )
                {
                DrawPassiveTab( aTabDrawMode,
                                aLayout.iSecondTab.iLeft,
                                aLayout.iSecondTab.iMiddle,
                                aLayout.iSecondTab.iRight,
                                aGc );
                }
            else
                {
                DrawActiveTab( aTabDrawMode,
                               aLayout.iSecondTab.iLeft,
                               aLayout.iSecondTab.iMiddle,
                               aLayout.iSecondTab.iRight,
                               aGc );
                }
            }
        }
    else if ( aActiveTab == 3 )
        {
        if ( aTabsHidden == EOnLeftSide )
            {
            DrawPassiveTab( aTabDrawMode,
                            aLayout.iHiddenTabLeft.iLeft,
                            aLayout.iHiddenTabLeft.iMiddle,
                            aLayout.iHiddenTabLeft.iRight,
                            aGc,
                            ETrue  );
            }
        
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iFirstTab.iLeft,
                        aLayout.iFirstTab.iMiddle,
                        aLayout.iFirstTab.iRight,
                        aGc );

        DrawPassiveTab( aTabDrawMode,
                        aLayout.iSecondTab.iLeft,
                        aLayout.iSecondTab.iMiddle,
                        aLayout.iSecondTab.iRight,
                        aGc );

        DrawActiveTab( aTabDrawMode,
                       aLayout.iThirdTab.iLeft,
                       aLayout.iThirdTab.iMiddle,
                       aLayout.iThirdTab.iRight,
                       aGc );
        }
    }


// ---------------------------------------------------------------------------
// Draws the tab group background in three tab narrow layout.
// ---------------------------------------------------------------------------
//
void CAknTabGroupGraphics::DrawThreeTabNarrowBackground(
    TTabDrawMode aTabDrawMode,
    TInt aActiveTab,
    CBitmapContext* aGc,
    SAknTabGroupBackgroundLayout& aLayout ) const
    {
    // If not given layout, then get the default layout
    if ( !aLayout.iUse )
        {
        aLayout = ThreeTabBackground( aActiveTab );
        }

    if ( aActiveTab == 1 )
        {
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iThirdTab.iLeft,
                        aLayout.iThirdTab.iMiddle,
                        aLayout.iThirdTab.iRight,
                        aGc );
        
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iSecondTab.iLeft,
                        aLayout.iSecondTab.iMiddle,
                        aLayout.iSecondTab.iRight,
                        aGc );
        
        DrawActiveTab( aTabDrawMode,
                       aLayout.iFirstTab.iLeft,
                       aLayout.iFirstTab.iMiddle,
                       aLayout.iFirstTab.iRight,
                       aGc );
        }
    else if ( aActiveTab == 2 )
        {
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iFirstTab.iLeft,
                        aLayout.iFirstTab.iMiddle,
                        aLayout.iFirstTab.iRight,
                        aGc );
        
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iThirdTab.iLeft,
                        aLayout.iThirdTab.iMiddle,
                        aLayout.iThirdTab.iRight,
                        aGc );
        
        DrawActiveTab( aTabDrawMode,
                       aLayout.iSecondTab.iLeft,
                       aLayout.iSecondTab.iMiddle,
                       aLayout.iSecondTab.iRight,
                       aGc );
        }
    else if ( aActiveTab == 3 )
        {
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iFirstTab.iLeft,
                        aLayout.iFirstTab.iMiddle,
                        aLayout.iFirstTab.iRight,
                        aGc );
        
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iSecondTab.iLeft,
                        aLayout.iSecondTab.iMiddle,
                        aLayout.iSecondTab.iRight,
                        aGc );
        
        DrawActiveTab( aTabDrawMode,
                       aLayout.iThirdTab.iLeft,
                       aLayout.iThirdTab.iMiddle,
                       aLayout.iThirdTab.iRight,
                       aGc );
        }
    }


CAknTabGroupGraphics::SAknTabGroupBackgroundLayout CAknTabGroupGraphics::FourTabBackground(
    TInt aActiveTab ) const
    {
    SAknTabGroupBackgroundLayout aLayout;

    TRect parentRect( iTabGroupBackgroundParent );

    // navi tabs 4 pane
    TRect naviTabsFourPaneRect(
        RectFromLayout( parentRect,
                        AknLayoutScalable_Avkon::navi_tabs_4_pane() ) );

    TRect tabsPassiveFirstPaneRect;
    TRect tabsPassiveSecondPaneRect;
    TRect tabsPassiveThirdPaneRect;
    TRect tabsActivePaneRect;

    // We don't want to use options, just assume that active and passive tabs are same sizes.
    TRect parent = naviTabsFourPaneRect;
    TAknWindowComponentLayout aFirstTab(  AknLayoutScalable_Avkon::tabs_4_active_pane(0) );
    TAknWindowComponentLayout aSecondTab( AknLayoutScalable_Avkon::tabs_4_passive_pane_cp(0) );
    TAknWindowComponentLayout aThirdTab(  AknLayoutScalable_Avkon::tabs_4_passive_pane(0) );
    TAknWindowComponentLayout aFourthTab( AknLayoutScalable_Avkon::tabs_4_passive_pane_cp2(0) );

    if ( aActiveTab == 1 )
        {
        tabsActivePaneRect        =  RectFromLayout( parent, aFirstTab );
        tabsPassiveFirstPaneRect  =  RectFromLayout( parent, aSecondTab );
        tabsPassiveSecondPaneRect =  RectFromLayout( parent, aThirdTab );
        tabsPassiveThirdPaneRect  =  RectFromLayout( parent, aFourthTab );
        }
    else if ( aActiveTab == 2 )
        {
        tabsActivePaneRect        =  RectFromLayout( parent, aSecondTab );
        tabsPassiveFirstPaneRect  =  RectFromLayout( parent, aFirstTab );
        tabsPassiveSecondPaneRect =  RectFromLayout( parent, aThirdTab );
        tabsPassiveThirdPaneRect  =  RectFromLayout( parent, aFourthTab );
        }
    else if ( aActiveTab == 3 )
        {
        tabsActivePaneRect        =  RectFromLayout( parent, aThirdTab );
        tabsPassiveFirstPaneRect  =  RectFromLayout( parent, aFirstTab );
        tabsPassiveSecondPaneRect =  RectFromLayout( parent, aSecondTab );
        tabsPassiveThirdPaneRect  =  RectFromLayout( parent, aFourthTab );
        }
    else if ( aActiveTab == 4 )
        {
        tabsActivePaneRect        =  RectFromLayout( parent, aFourthTab );
        tabsPassiveFirstPaneRect  =  RectFromLayout( parent, aFirstTab );
        tabsPassiveSecondPaneRect =  RectFromLayout( parent, aSecondTab );
        tabsPassiveThirdPaneRect  =  RectFromLayout( parent, aThirdTab );
        }
    
    TAknWindowComponentLayout passivePaneLayout(
        AknLayoutScalable_Avkon::bg_passive_tab_pane_cp3( 0 ) );

    TAknWindowComponentLayout passiveTabLayout1(
        AknLayoutScalable_Avkon::bg_passive_tab_pane_g1_cp3() );
        
    TAknWindowComponentLayout passiveTabLayout2(
        AknLayoutScalable_Avkon::bg_passive_tab_pane_g2_cp3() );
        
    TAknWindowComponentLayout passiveTabLayout3(
        AknLayoutScalable_Avkon::bg_passive_tab_pane_g3_cp3() );
        
        
    // Tabs 4 first passive tab pane
    TRect tabsFourPassiveFirstPaneRect( tabsPassiveFirstPaneRect );

    // Tabs 4 second passive tab pane
    TRect tabsFourPassiveSecondPaneRect( tabsPassiveSecondPaneRect );

    // Tabs 4 third passive tab pane
    TRect tabsFourPassiveThirdPaneRect( tabsPassiveThirdPaneRect );

    // Tabs 4 active tab pane
    TRect tabsFourActivePaneRect( tabsActivePaneRect );

    // bg active tab pane
    TRect tabsBackgroundActivePaneRect(
        RectFromLayout( tabsFourActivePaneRect,
                        AknLayoutScalable_Avkon::bg_active_tab_pane_cp3( 0 ) ) );

    // bg first passive tab pane
    TRect tabsBackgroundFirstPassivePaneRect(
        RectFromLayout( tabsFourPassiveFirstPaneRect, passivePaneLayout ) );

    // bg second passive tab pane
    TRect tabsBackgroundSecondPassivePaneRect(
        RectFromLayout( tabsFourPassiveSecondPaneRect, passivePaneLayout ) );

    // bg third passive tab pane
    TRect tabsBackgroundThirdPassivePaneRect(
        RectFromLayout( tabsFourPassiveThirdPaneRect, passivePaneLayout ) );

    // Active tab left
    TRect activeTabLeftPaneRect(
        RectFromLayout( tabsBackgroundActivePaneRect,
                        AknLayoutScalable_Avkon::bg_active_tab_pane_g1_cp3() ) );

    // Active tab middle
    TRect activeTabMiddlePaneRect(
        RectFromLayout( tabsBackgroundActivePaneRect,
                        AknLayoutScalable_Avkon::bg_active_tab_pane_g2_cp3() ) );

    // Active tab right
    TRect activeTabRightPaneRect(
        RectFromLayout( tabsBackgroundActivePaneRect,
                        AknLayoutScalable_Avkon::bg_active_tab_pane_g3_cp3() ) );

    // First passive tab left
    TRect firstPassiveTabLeftPaneRect(
        RectFromLayout( tabsBackgroundFirstPassivePaneRect,
                        passiveTabLayout1 ) );

    // First passive tab middle
    TRect firstPassiveTabMiddlePaneRect(
        RectFromLayout( tabsBackgroundFirstPassivePaneRect,
                        passiveTabLayout2 ) );

    // First passive tab right
    TRect firstPassiveTabRightPaneRect(
        RectFromLayout( tabsBackgroundFirstPassivePaneRect,
                        passiveTabLayout3 ) );

    // Second passive tab left
    TRect secondPassiveTabLeftPaneRect(
        RectFromLayout( tabsBackgroundSecondPassivePaneRect,
                        passiveTabLayout1 ) );

    // Second passive tab middle
    TRect secondPassiveTabMiddlePaneRect(
        RectFromLayout( tabsBackgroundSecondPassivePaneRect,
                        passiveTabLayout2 ) );

    // Second passive tab right
    TRect secondPassiveTabRightPaneRect(
        RectFromLayout( tabsBackgroundSecondPassivePaneRect,
                        passiveTabLayout3 ) );

    // Third passive tab left
    TRect thirdPassiveTabLeftPaneRect(
        RectFromLayout( tabsBackgroundThirdPassivePaneRect,
                        passiveTabLayout1 ) );

    // third passive tab middle
    TRect thirdPassiveTabMiddlePaneRect(
        RectFromLayout( tabsBackgroundThirdPassivePaneRect,
                        passiveTabLayout2 ) );

    // third passive tab right
    TRect thirdPassiveTabRightPaneRect(
        RectFromLayout( tabsBackgroundThirdPassivePaneRect,
                        passiveTabLayout3 ) );

    if ( aActiveTab == 1 )
        {
        aLayout.iFirstTab.iLeft   = activeTabLeftPaneRect;
        aLayout.iFirstTab.iMiddle = activeTabMiddlePaneRect;
        aLayout.iFirstTab.iRight  = activeTabRightPaneRect;

        aLayout.iSecondTab.iLeft   = firstPassiveTabLeftPaneRect;
        aLayout.iSecondTab.iMiddle = firstPassiveTabMiddlePaneRect;
        aLayout.iSecondTab.iRight  = firstPassiveTabRightPaneRect;

        aLayout.iThirdTab.iLeft   = secondPassiveTabLeftPaneRect;
        aLayout.iThirdTab.iMiddle = secondPassiveTabMiddlePaneRect;
        aLayout.iThirdTab.iRight  = secondPassiveTabRightPaneRect;

        aLayout.iFourthTab.iLeft   = thirdPassiveTabLeftPaneRect;
        aLayout.iFourthTab.iMiddle = thirdPassiveTabMiddlePaneRect;
        aLayout.iFourthTab.iRight  = thirdPassiveTabRightPaneRect;
        }
    else if ( aActiveTab == 2 )
        {
        aLayout.iFirstTab.iLeft   = firstPassiveTabLeftPaneRect;
        aLayout.iFirstTab.iMiddle = firstPassiveTabMiddlePaneRect;
        aLayout.iFirstTab.iRight  = firstPassiveTabRightPaneRect;

        aLayout.iSecondTab.iLeft   = activeTabLeftPaneRect;
        aLayout.iSecondTab.iMiddle = activeTabMiddlePaneRect;
        aLayout.iSecondTab.iRight  = activeTabRightPaneRect;

        aLayout.iThirdTab.iLeft   = secondPassiveTabLeftPaneRect;
        aLayout.iThirdTab.iMiddle = secondPassiveTabMiddlePaneRect;
        aLayout.iThirdTab.iRight  = secondPassiveTabRightPaneRect;

        aLayout.iFourthTab.iLeft   = thirdPassiveTabLeftPaneRect;
        aLayout.iFourthTab.iMiddle = thirdPassiveTabMiddlePaneRect;
        aLayout.iFourthTab.iRight  = thirdPassiveTabRightPaneRect;
        }
    else if ( aActiveTab == 3 )
        {
        aLayout.iFirstTab.iLeft   = firstPassiveTabLeftPaneRect;
        aLayout.iFirstTab.iMiddle = firstPassiveTabMiddlePaneRect;
        aLayout.iFirstTab.iRight  = firstPassiveTabRightPaneRect;

        aLayout.iSecondTab.iLeft   = secondPassiveTabLeftPaneRect;
        aLayout.iSecondTab.iMiddle = secondPassiveTabMiddlePaneRect;
        aLayout.iSecondTab.iRight  = secondPassiveTabRightPaneRect;

        aLayout.iThirdTab.iLeft   = activeTabLeftPaneRect;
        aLayout.iThirdTab.iMiddle = activeTabMiddlePaneRect;
        aLayout.iThirdTab.iRight  = activeTabRightPaneRect;

        aLayout.iFourthTab.iLeft   = thirdPassiveTabLeftPaneRect;
        aLayout.iFourthTab.iMiddle = thirdPassiveTabMiddlePaneRect;
        aLayout.iFourthTab.iRight  = thirdPassiveTabRightPaneRect;
        }
    else if ( aActiveTab == 4 )
        {
        aLayout.iFirstTab.iLeft   = firstPassiveTabLeftPaneRect;
        aLayout.iFirstTab.iMiddle = firstPassiveTabMiddlePaneRect;
        aLayout.iFirstTab.iRight  = firstPassiveTabRightPaneRect;

        aLayout.iSecondTab.iLeft   = secondPassiveTabLeftPaneRect;
        aLayout.iSecondTab.iMiddle = secondPassiveTabMiddlePaneRect;
        aLayout.iSecondTab.iRight  = secondPassiveTabRightPaneRect;

        aLayout.iThirdTab.iLeft   = thirdPassiveTabLeftPaneRect;
        aLayout.iThirdTab.iMiddle = thirdPassiveTabMiddlePaneRect;
        aLayout.iThirdTab.iRight  = thirdPassiveTabRightPaneRect;

        aLayout.iFourthTab.iLeft   = activeTabLeftPaneRect;
        aLayout.iFourthTab.iMiddle = activeTabMiddlePaneRect;
        aLayout.iFourthTab.iRight  = activeTabRightPaneRect;
        }

    return aLayout;
    }

CAknTabGroupGraphics::SAknTabGroupBackgroundLayout CAknTabGroupGraphics::FourTabNarrowBackground(TInt aActiveTab) const
    {
    SAknTabGroupBackgroundLayout aLayout;

    // navi tabs pane
    TRect parentRect( NarrowParentRect() );

    // navi tabs 4 pane
    TRect naviTabsFourPaneRect(
        RectFromLayout( parentRect,
                        AknLayoutScalable_Avkon::navi_tabs_4_pane_srt() ) );

    TRect tabsPassiveFirstPaneRect;
    TRect tabsPassiveSecondPaneRect;
    TRect tabsPassiveThirdPaneRect;
    TRect tabsActivePaneRect;
    
    TRect parent = naviTabsFourPaneRect;
    
    // We don't want to use options, just assume that active and passive tabs are same sizes.
    TAknWindowComponentLayout aFirstTab( 
        AknLayoutScalable_Avkon::tabs_4_active_pane_srt(0) );
        
    TAknWindowComponentLayout aSecondTab(
        AknLayoutScalable_Avkon::tabs_4_passive_pane_cp_srt(0) );
        
    TAknWindowComponentLayout aThirdTab(
        AknLayoutScalable_Avkon::tabs_4_passive_pane_srt(0) );
        
    TAknWindowComponentLayout aFourthTab(
        AknLayoutScalable_Avkon::tabs_4_passive_pane_cp2_srt(0) );

    if ( aActiveTab == 1 )
        {
        tabsActivePaneRect        =  RectFromLayout( parent, aFirstTab );
        tabsPassiveFirstPaneRect  =  RectFromLayout( parent, aSecondTab );
        tabsPassiveSecondPaneRect =  RectFromLayout( parent, aThirdTab );
        tabsPassiveThirdPaneRect  =  RectFromLayout( parent, aFourthTab );
        }
    else if ( aActiveTab == 2 )
        {
        tabsActivePaneRect        =  RectFromLayout( parent, aSecondTab );
        tabsPassiveFirstPaneRect  =  RectFromLayout( parent, aFirstTab );
        tabsPassiveSecondPaneRect =  RectFromLayout( parent, aThirdTab );
        tabsPassiveThirdPaneRect  =  RectFromLayout( parent, aFourthTab );
        }
    else if ( aActiveTab == 3 )
        {
        tabsActivePaneRect        =  RectFromLayout( parent, aThirdTab );
        tabsPassiveFirstPaneRect  =  RectFromLayout( parent, aFirstTab );
        tabsPassiveSecondPaneRect =  RectFromLayout( parent, aSecondTab );
        tabsPassiveThirdPaneRect  =  RectFromLayout( parent, aFourthTab );
        }
    else if ( aActiveTab == 4 )
        {
        tabsActivePaneRect        =  RectFromLayout( parent, aFourthTab );
        tabsPassiveFirstPaneRect  =  RectFromLayout( parent, aFirstTab );
        tabsPassiveSecondPaneRect =  RectFromLayout( parent, aSecondTab );
        tabsPassiveThirdPaneRect  =  RectFromLayout( parent, aThirdTab );
        }

    // Tabs 4 first passive tab pane
    TRect tabsFourPassiveFirstPaneRect( tabsPassiveFirstPaneRect );

    // Tabs 4 second passive tab pane
    TRect tabsFourPassiveSecondPaneRect( tabsPassiveSecondPaneRect );

    // Tabs 4 third passive tab pane
    TRect tabsFourPassiveThirdPaneRect( tabsPassiveThirdPaneRect );

    // Tabs 4 active tab pane
    TRect tabsFourActivePaneRect( tabsActivePaneRect );

    TAknWindowComponentLayout passivePaneLayout(
        AknLayoutScalable_Avkon::bg_passive_tab_pane_cp3_srt( 0 ) );

    TAknWindowComponentLayout passiveTabLayout1(
        AknLayoutScalable_Avkon::bg_passive_tab_pane_g1_cp3_srt() );
        
    TAknWindowComponentLayout passiveTabLayout2(
        AknLayoutScalable_Avkon::bg_passive_tab_pane_g2_cp3_srt() );
        
    TAknWindowComponentLayout passiveTabLayout3(
        AknLayoutScalable_Avkon::bg_passive_tab_pane_g3_cp3_srt() );

    // bg active tab pane
    TRect tabsBackgroundActivePaneRect(
        RectFromLayout( tabsFourActivePaneRect,
                        AknLayoutScalable_Avkon::bg_active_tab_pane_cp3_srt( 0 ) ) );

    // bg first passive tab pane
    TRect tabsBackgroundFirstPassivePaneRect(
        RectFromLayout( tabsFourPassiveFirstPaneRect, passivePaneLayout ) );

    // bg second passive tab pane
    TRect tabsBackgroundSecondPassivePaneRect(
        RectFromLayout( tabsFourPassiveSecondPaneRect, passivePaneLayout ) );

    // bg third passive tab pane
    TRect tabsBackgroundThirdPassivePaneRect(
        RectFromLayout( tabsFourPassiveThirdPaneRect, passivePaneLayout ) );


    // Active tab left
    TRect activeTabLeftPaneRect(
        RectFromLayout( tabsBackgroundActivePaneRect,
                        AknLayoutScalable_Avkon::bg_active_tab_pane_g1_cp3_copy1() ) );

    // Active tab middle
    TRect activeTabMiddlePaneRect(
        RectFromLayout( tabsBackgroundActivePaneRect,
                        AknLayoutScalable_Avkon::bg_active_tab_pane_g2_cp3_copy1() ) );

    // Active tab right
    TRect activeTabRightPaneRect(
        RectFromLayout( tabsBackgroundActivePaneRect,
                        AknLayoutScalable_Avkon::bg_active_tab_pane_g3_cp3_copy1() ) );


    // First passive tab left
    TRect firstPassiveTabLeftPaneRect(
        RectFromLayout( tabsBackgroundFirstPassivePaneRect,
                        passiveTabLayout1 ) );

    // First passive tab middle
    TRect firstPassiveTabMiddlePaneRect(
        RectFromLayout( tabsBackgroundFirstPassivePaneRect,
                        passiveTabLayout2 ) );

    // First passive tab right
    TRect firstPassiveTabRightPaneRect(
        RectFromLayout( tabsBackgroundFirstPassivePaneRect,
                        passiveTabLayout3 ) );


    // Second passive tab left
    TRect secondPassiveTabLeftPaneRect(
        RectFromLayout( tabsBackgroundSecondPassivePaneRect,
                        passiveTabLayout1 ) );

    // Second passive tab middle
    TRect secondPassiveTabMiddlePaneRect(
        RectFromLayout( tabsBackgroundSecondPassivePaneRect,
                        passiveTabLayout2 ) );

    // Second passive tab right
    TRect secondPassiveTabRightPaneRect(
        RectFromLayout( tabsBackgroundSecondPassivePaneRect,
                        passiveTabLayout3 ) );


    // Third passive tab left
    TRect thirdPassiveTabLeftPaneRect(
        RectFromLayout( tabsBackgroundThirdPassivePaneRect,
                        passiveTabLayout1 ) );

    // third passive tab middle
    TRect thirdPassiveTabMiddlePaneRect(
        RectFromLayout( tabsBackgroundThirdPassivePaneRect,
                        passiveTabLayout2 ) );

    // third passive tab right
    TRect thirdPassiveTabRightPaneRect(
        RectFromLayout( tabsBackgroundThirdPassivePaneRect,
                        passiveTabLayout3 ) );


    if ( aActiveTab == 1 )
        {
        aLayout.iFirstTab.iLeft   = activeTabLeftPaneRect;
        aLayout.iFirstTab.iMiddle = activeTabMiddlePaneRect;
        aLayout.iFirstTab.iRight  = activeTabRightPaneRect;

        aLayout.iSecondTab.iLeft   = firstPassiveTabLeftPaneRect;
        aLayout.iSecondTab.iMiddle = firstPassiveTabMiddlePaneRect;
        aLayout.iSecondTab.iRight  = firstPassiveTabRightPaneRect;

        aLayout.iThirdTab.iLeft   = secondPassiveTabLeftPaneRect;
        aLayout.iThirdTab.iMiddle = secondPassiveTabMiddlePaneRect;
        aLayout.iThirdTab.iRight  = secondPassiveTabRightPaneRect;

        aLayout.iFourthTab.iLeft   = thirdPassiveTabLeftPaneRect;
        aLayout.iFourthTab.iMiddle = thirdPassiveTabMiddlePaneRect;
        aLayout.iFourthTab.iRight  = thirdPassiveTabRightPaneRect;
        }
    else if ( aActiveTab == 2 )
        {
        aLayout.iFirstTab.iLeft   = firstPassiveTabLeftPaneRect;
        aLayout.iFirstTab.iMiddle = firstPassiveTabMiddlePaneRect;
        aLayout.iFirstTab.iRight  = firstPassiveTabRightPaneRect;

        aLayout.iSecondTab.iLeft   = activeTabLeftPaneRect;
        aLayout.iSecondTab.iMiddle = activeTabMiddlePaneRect;
        aLayout.iSecondTab.iRight  = activeTabRightPaneRect;

        aLayout.iThirdTab.iLeft   = secondPassiveTabLeftPaneRect;
        aLayout.iThirdTab.iMiddle = secondPassiveTabMiddlePaneRect;
        aLayout.iThirdTab.iRight  = secondPassiveTabRightPaneRect;

        aLayout.iFourthTab.iLeft   = thirdPassiveTabLeftPaneRect;
        aLayout.iFourthTab.iMiddle = thirdPassiveTabMiddlePaneRect;
        aLayout.iFourthTab.iRight  = thirdPassiveTabRightPaneRect;
        }
    else if ( aActiveTab == 3 )
        {
        aLayout.iFirstTab.iLeft   = firstPassiveTabLeftPaneRect;
        aLayout.iFirstTab.iMiddle = firstPassiveTabMiddlePaneRect;
        aLayout.iFirstTab.iRight  = firstPassiveTabRightPaneRect;

        aLayout.iSecondTab.iLeft   = secondPassiveTabLeftPaneRect;
        aLayout.iSecondTab.iMiddle = secondPassiveTabMiddlePaneRect;
        aLayout.iSecondTab.iRight  = secondPassiveTabRightPaneRect;

        aLayout.iThirdTab.iLeft   = activeTabLeftPaneRect;
        aLayout.iThirdTab.iMiddle = activeTabMiddlePaneRect;
        aLayout.iThirdTab.iRight  = activeTabRightPaneRect;

        aLayout.iFourthTab.iLeft   = thirdPassiveTabLeftPaneRect;
        aLayout.iFourthTab.iMiddle = thirdPassiveTabMiddlePaneRect;
        aLayout.iFourthTab.iRight  = thirdPassiveTabRightPaneRect;
        }
    else if ( aActiveTab == 4 )
        {
        aLayout.iFirstTab.iLeft   = firstPassiveTabLeftPaneRect;
        aLayout.iFirstTab.iMiddle = firstPassiveTabMiddlePaneRect;
        aLayout.iFirstTab.iRight  = firstPassiveTabRightPaneRect;

        aLayout.iSecondTab.iLeft   = secondPassiveTabLeftPaneRect;
        aLayout.iSecondTab.iMiddle = secondPassiveTabMiddlePaneRect;
        aLayout.iSecondTab.iRight  = secondPassiveTabRightPaneRect;

        aLayout.iThirdTab.iLeft   = thirdPassiveTabLeftPaneRect;
        aLayout.iThirdTab.iMiddle = thirdPassiveTabMiddlePaneRect;
        aLayout.iThirdTab.iRight  = thirdPassiveTabRightPaneRect;

        aLayout.iFourthTab.iLeft   = activeTabLeftPaneRect;
        aLayout.iFourthTab.iMiddle = activeTabMiddlePaneRect;
        aLayout.iFourthTab.iRight  = activeTabRightPaneRect;
        }

    return aLayout;
    }

void CAknTabGroupGraphics::DrawFourTabBackground( TTabDrawMode aTabDrawMode,
                                                  TInt aActiveTab,
                                                  CBitmapContext* aGc,
                                                  SAknTabGroupBackgroundLayout& aLayout ) const
    {
    // If not given layout, then get the default layout
    if ( !aLayout.iUse )
        {
        aLayout = FourTabBackground( aActiveTab );
        }

    if ( aActiveTab == 1 )
        {
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iFourthTab.iLeft,
                        aLayout.iFourthTab.iMiddle,
                        aLayout.iFourthTab.iRight,
                        aGc );
        
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iThirdTab.iLeft,
                        aLayout.iThirdTab.iMiddle,
                        aLayout.iThirdTab.iRight,
                        aGc );
        
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iSecondTab.iLeft,
                        aLayout.iSecondTab.iMiddle,
                        aLayout.iSecondTab.iRight,
                        aGc );
        
        DrawActiveTab( aTabDrawMode,
                       aLayout.iFirstTab.iLeft,
                       aLayout.iFirstTab.iMiddle,
                       aLayout.iFirstTab.iRight,
                       aGc );
        }
    else if ( aActiveTab == 2 )
        {
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iFourthTab.iLeft,
                        aLayout.iFourthTab.iMiddle,
                        aLayout.iFourthTab.iRight,
                        aGc );
        
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iThirdTab.iLeft,
                        aLayout.iThirdTab.iMiddle,
                        aLayout.iThirdTab.iRight,
                        aGc );
        
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iFirstTab.iLeft,
                        aLayout.iFirstTab.iMiddle,
                        aLayout.iFirstTab.iRight,
                        aGc );
        
        DrawActiveTab( aTabDrawMode,
                       aLayout.iSecondTab.iLeft,
                       aLayout.iSecondTab.iMiddle,
                       aLayout.iSecondTab.iRight,
                       aGc );
        }
    else if ( aActiveTab == 3 )
        {
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iFirstTab.iLeft,
                        aLayout.iFirstTab.iMiddle,
                        aLayout.iFirstTab.iRight,
                        aGc );
        
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iSecondTab.iLeft,
                        aLayout.iSecondTab.iMiddle,
                        aLayout.iSecondTab.iRight,
                        aGc );
        
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iFourthTab.iLeft,
                        aLayout.iFourthTab.iMiddle,
                        aLayout.iFourthTab.iRight,
                        aGc );
        
        DrawActiveTab( aTabDrawMode,
                       aLayout.iThirdTab.iLeft,
                       aLayout.iThirdTab.iMiddle,
                       aLayout.iThirdTab.iRight,
                       aGc );
        }
    else if ( aActiveTab == 4 )
        {
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iFirstTab.iLeft,
                        aLayout.iFirstTab.iMiddle,
                        aLayout.iFirstTab.iRight,
                        aGc );
        
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iSecondTab.iLeft,
                        aLayout.iSecondTab.iMiddle,
                        aLayout.iSecondTab.iRight,
                        aGc );
        
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iThirdTab.iLeft,
                        aLayout.iThirdTab.iMiddle,
                        aLayout.iThirdTab.iRight,
                        aGc );
        
        DrawActiveTab( aTabDrawMode,
                       aLayout.iFourthTab.iLeft,
                       aLayout.iFourthTab.iMiddle,
                       aLayout.iFourthTab.iRight,
                       aGc );
        }
    }

void CAknTabGroupGraphics::DrawFourTabNarrowBackground( TTabDrawMode aTabDrawMode,
                                                        TInt aActiveTab,
                                                        CBitmapContext* aGc,
                                                        SAknTabGroupBackgroundLayout& aLayout ) const
    {
    // If not given layout, then get the default layout
    if ( !aLayout.iUse )
        {
        aLayout = FourTabBackground( aActiveTab );
        }

    if ( aActiveTab == 1 )
        {
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iFourthTab.iLeft,
                        aLayout.iFourthTab.iMiddle,
                        aLayout.iFourthTab.iRight,
                        aGc );
        
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iThirdTab.iLeft,
                        aLayout.iThirdTab.iMiddle,
                        aLayout.iThirdTab.iRight,
                        aGc );
        
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iSecondTab.iLeft,
                        aLayout.iSecondTab.iMiddle,
                        aLayout.iSecondTab.iRight,
                        aGc );
        
        DrawActiveTab( aTabDrawMode,
                       aLayout.iFirstTab.iLeft,
                       aLayout.iFirstTab.iMiddle,
                       aLayout.iFirstTab.iRight,
                       aGc );
        }
    else if ( aActiveTab == 2 )
        {
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iFourthTab.iLeft,
                        aLayout.iFourthTab.iMiddle,
                        aLayout.iFourthTab.iRight,
                        aGc );
        
        DrawPassiveTab( aTabDrawMode, 
                        aLayout.iThirdTab.iLeft,
                        aLayout.iThirdTab.iMiddle,
                        aLayout.iThirdTab.iRight,
                        aGc );
        
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iFirstTab.iLeft,
                        aLayout.iFirstTab.iMiddle,
                        aLayout.iFirstTab.iRight,
                        aGc );
        
        DrawActiveTab( aTabDrawMode,
                       aLayout.iSecondTab.iLeft,
                       aLayout.iSecondTab.iMiddle,
                       aLayout.iSecondTab.iRight,
                       aGc );
        }
    else if ( aActiveTab == 3 )
        {
        // Note the drawing order of passive tabs
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iFirstTab.iLeft,
                        aLayout.iFirstTab.iMiddle,
                        aLayout.iFirstTab.iRight,
                        aGc );
        
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iSecondTab.iLeft,
                        aLayout.iSecondTab.iMiddle,
                        aLayout.iSecondTab.iRight,
                        aGc );
        
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iFourthTab.iLeft,
                        aLayout.iFourthTab.iMiddle,
                        aLayout.iFourthTab.iRight,
                        aGc );
        
        DrawActiveTab( aTabDrawMode,
                       aLayout.iThirdTab.iLeft,
                       aLayout.iThirdTab.iMiddle,
                       aLayout.iThirdTab.iRight,
                       aGc );
        }
    else if ( aActiveTab == 4 )
        {
        // Note the drawing order of passive tabs
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iFirstTab.iLeft,
                        aLayout.iFirstTab.iMiddle,
                        aLayout.iFirstTab.iRight,
                        aGc );
        
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iSecondTab.iLeft,
                        aLayout.iSecondTab.iMiddle,
                        aLayout.iSecondTab.iRight,
                        aGc );
        
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iThirdTab.iLeft,
                        aLayout.iThirdTab.iMiddle,
                        aLayout.iThirdTab.iRight,
                        aGc );
        
        DrawActiveTab( aTabDrawMode,
                       aLayout.iFourthTab.iLeft,
                       aLayout.iFourthTab.iMiddle,
                       aLayout.iFourthTab.iRight,
                       aGc );
        }
    }

CAknTabGroupGraphics::SAknTabGroupBackgroundLayout CAknTabGroupGraphics::TwoLongTabBackground(TInt aActiveTab) const
    {
    SAknTabGroupBackgroundLayout aLayout;

    // screen
    TRect screenRect;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, screenRect );
    
    TBool landscape( Layout_Meta_Data::IsLandscapeOrientation() );

    TRect parentRect( iTabGroupBackgroundParent );

    // two tabs pane
    TRect naviTabsTwoPaneRect(
        RectFromLayout( parentRect,
                        AknLayoutScalable_Avkon::navi_tabs_2_long_pane() ) );

    TInt tabsActivePassivePaneOption = ( aActiveTab == 1 ) ? 0 : 1;

    // Tabs two passive pane
    TRect tabsTwoPassivePaneRect(
        RectFromLayout( naviTabsTwoPaneRect,
                        AknLayoutScalable_Avkon::tabs_2_long_passive_pane(
                            tabsActivePassivePaneOption ) ) );

    // Tabs two active pane
    TRect tabsTwoActivePaneRect(
        RectFromLayout( naviTabsTwoPaneRect,
                        AknLayoutScalable_Avkon::tabs_2_long_active_pane(
                            tabsActivePassivePaneOption ) ) );

    // bg active tab pane
    TRect tabsBackgroundActivePaneRect(
        RectFromLayout( tabsTwoActivePaneRect,
                        AknLayoutScalable_Avkon::bg_active_tab_pane_cp4(
                            landscape ) ) );

    // bg passive tab pane
    TRect tabsBackgroundFirstPassivePaneRect(
        RectFromLayout( tabsTwoPassivePaneRect,
                        AknLayoutScalable_Avkon::bg_passive_tab_pane_cp4(
                            landscape ) ) );

    // Active tab left
    TRect activeTabLeftPaneRect(
        RectFromLayout( tabsBackgroundActivePaneRect,
                        AknLayoutScalable_Avkon::bg_active_tab_pane_g1_cp4() ) );

    // Active tab middle
    TRect activeTabMiddlePaneRect(
        RectFromLayout( tabsBackgroundActivePaneRect,
                        AknLayoutScalable_Avkon::bg_active_tab_pane_g2_cp4() ) );

    // Active tab right
    TRect activeTabRightPaneRect(
        RectFromLayout( tabsBackgroundActivePaneRect,
                        AknLayoutScalable_Avkon::bg_active_tab_pane_g3_cp4() ) );

    // First passive tab left
    TRect firstPassiveTabLeftPaneRect(
        RectFromLayout( tabsBackgroundFirstPassivePaneRect,
                        AknLayoutScalable_Avkon::bg_passive_tab_pane_g1_cp4() ) );

    // First passive tab middle
    TRect firstPassiveTabMiddlePaneRect(
        RectFromLayout( tabsBackgroundFirstPassivePaneRect,
                        AknLayoutScalable_Avkon::bg_passive_tab_pane_g2_cp4() ) );

    // First passive tab right
    TRect firstPassiveTabRightPaneRect(
        RectFromLayout( tabsBackgroundFirstPassivePaneRect,
                        AknLayoutScalable_Avkon::bg_passive_tab_pane_g3_cp4() ) );

    if ( aActiveTab == 1 )
        {
        aLayout.iFirstTab.iLeft   = activeTabLeftPaneRect;
        aLayout.iFirstTab.iMiddle = activeTabMiddlePaneRect;
        aLayout.iFirstTab.iRight  = activeTabRightPaneRect;

        aLayout.iSecondTab.iLeft   = firstPassiveTabLeftPaneRect;
        aLayout.iSecondTab.iMiddle = firstPassiveTabMiddlePaneRect;
        aLayout.iSecondTab.iRight  = firstPassiveTabRightPaneRect;
        }
    else
        {
        aLayout.iFirstTab.iLeft   = firstPassiveTabLeftPaneRect;
        aLayout.iFirstTab.iMiddle = firstPassiveTabMiddlePaneRect;
        aLayout.iFirstTab.iRight  = firstPassiveTabRightPaneRect;

        aLayout.iSecondTab.iLeft   = activeTabLeftPaneRect;
        aLayout.iSecondTab.iMiddle = activeTabMiddlePaneRect;
        aLayout.iSecondTab.iRight  = activeTabRightPaneRect;
        }

    TRect nullRect( 0,0,0,0 );

    aLayout.iThirdTab.iLeft   = nullRect;
    aLayout.iThirdTab.iMiddle = nullRect;
    aLayout.iThirdTab.iRight  = nullRect;

    aLayout.iFourthTab.iLeft   = nullRect;
    aLayout.iFourthTab.iMiddle = nullRect;
    aLayout.iFourthTab.iRight  = nullRect;

    return aLayout;
    }

CAknTabGroupGraphics::SAknTabGroupBackgroundLayout CAknTabGroupGraphics::TwoLongTabNarrowBackground(TInt aActiveTab) const
    {
    SAknTabGroupBackgroundLayout aLayout;

    TBool landscape( Layout_Meta_Data::IsLandscapeOrientation() );

    // navi tabs pane
    TRect parentRect( NarrowParentRect() );

    // two tabs pane
    TRect naviTabsTwoPaneRect(
        RectFromLayout( parentRect,
                        AknLayoutScalable_Avkon::navi_tabs_2_long_pane_srt() ) );

    TInt tabsActivePassivePaneOption = ( aActiveTab == 1 ) ? 0 : 1;

    // Tabs two passive pane
    TRect tabsTwoPassivePaneRect(
        RectFromLayout( naviTabsTwoPaneRect,
                        AknLayoutScalable_Avkon::tabs_2_long_passive_pane_srt(
                            tabsActivePassivePaneOption ) ) );

    // Tabs two active pane
    TRect tabsTwoActivePaneRect(
        RectFromLayout( naviTabsTwoPaneRect,
                        AknLayoutScalable_Avkon::tabs_2_long_active_pane_srt(
                            tabsActivePassivePaneOption ) ) );

    // bg active tab pane
    TRect tabsBackgroundActivePaneRect(
        RectFromLayout( tabsTwoActivePaneRect,
                        AknLayoutScalable_Avkon::bg_active_tab_pane_cp4_srt(
                            landscape ) ) );

    // bg passive tab pane
    TRect tabsBackgroundFirstPassivePaneRect(
        RectFromLayout( tabsTwoPassivePaneRect,
                        AknLayoutScalable_Avkon::bg_passive_tab_pane_cp4_srt(
                            landscape ) ) );

    // Active tab left
    TRect activeTabLeftPaneRect(
        RectFromLayout( tabsBackgroundActivePaneRect,
                        AknLayoutScalable_Avkon::bg_active_tab_pane_g1_cp4_srt() ) );

    // Active tab middle
    TRect activeTabMiddlePaneRect(
        RectFromLayout( tabsBackgroundActivePaneRect,
                        AknLayoutScalable_Avkon::bg_active_tab_pane_g2_cp4_srt() ) );

    // Active tab right
    TRect activeTabRightPaneRect(
        RectFromLayout( tabsBackgroundActivePaneRect,
                        AknLayoutScalable_Avkon::bg_active_tab_pane_g3_cp4_srt() ) );

    // First passive tab left
    TRect firstPassiveTabLeftPaneRect(
        RectFromLayout( tabsBackgroundFirstPassivePaneRect,
                        AknLayoutScalable_Avkon::bg_passive_tab_pane_g1_cp4_srt() ) );

    // First passive tab middle
    TRect firstPassiveTabMiddlePaneRect(
        RectFromLayout( tabsBackgroundFirstPassivePaneRect,
                        AknLayoutScalable_Avkon::bg_passive_tab_pane_g2_cp4_srt() ) );

    // First passive tab right
    TRect firstPassiveTabRightPaneRect(
        RectFromLayout( tabsBackgroundFirstPassivePaneRect,
                        AknLayoutScalable_Avkon::bg_passive_tab_pane_g3_cp4_srt() ) );


    if ( aActiveTab == 1 )
        {
        aLayout.iFirstTab.iLeft   = activeTabLeftPaneRect;
        aLayout.iFirstTab.iMiddle = activeTabMiddlePaneRect;
        aLayout.iFirstTab.iRight  = activeTabRightPaneRect;

        aLayout.iSecondTab.iLeft   = firstPassiveTabLeftPaneRect;
        aLayout.iSecondTab.iMiddle = firstPassiveTabMiddlePaneRect;
        aLayout.iSecondTab.iRight  = firstPassiveTabRightPaneRect;
        }
    else
        {
        aLayout.iFirstTab.iLeft   = firstPassiveTabLeftPaneRect;
        aLayout.iFirstTab.iMiddle = firstPassiveTabMiddlePaneRect;
        aLayout.iFirstTab.iRight  = firstPassiveTabRightPaneRect;

        aLayout.iSecondTab.iLeft   = activeTabLeftPaneRect;
        aLayout.iSecondTab.iMiddle = activeTabMiddlePaneRect;
        aLayout.iSecondTab.iRight  = activeTabRightPaneRect;
        }

    TRect nullRect( 0,0,0,0 );

    aLayout.iThirdTab.iLeft   = nullRect;
    aLayout.iThirdTab.iMiddle = nullRect;
    aLayout.iThirdTab.iRight  = nullRect;

    aLayout.iFourthTab.iLeft   = nullRect;
    aLayout.iFourthTab.iMiddle = nullRect;
    aLayout.iFourthTab.iRight  = nullRect;

    return aLayout;
    }

void CAknTabGroupGraphics::DrawTwoLongTabBackground(
    TTabDrawMode aTabDrawMode,
    TInt aActiveTab,
    CBitmapContext* aGc,
    SAknTabGroupBackgroundLayout& aLayout ) const
    {
    // If not given layout, then get the default layout
    if ( !aLayout.iUse )
        {
        aLayout = TwoLongTabBackground( aActiveTab );
        }

    if ( aActiveTab == 1 )
        {
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iSecondTab.iLeft,
                        aLayout.iSecondTab.iMiddle,
                        aLayout.iSecondTab.iRight,
                        aGc );
                        
        DrawActiveTab( aTabDrawMode,
                       aLayout.iFirstTab.iLeft,
                       aLayout.iFirstTab.iMiddle,
                       aLayout.iFirstTab.iRight,
                       aGc );
        }
    else
        {
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iFirstTab.iLeft,
                        aLayout.iFirstTab.iMiddle,
                        aLayout.iFirstTab.iRight,
                        aGc );
                        
        DrawActiveTab( aTabDrawMode,
                       aLayout.iSecondTab.iLeft,
                       aLayout.iSecondTab.iMiddle,
                       aLayout.iSecondTab.iRight,
                       aGc );
        }
    }

void CAknTabGroupGraphics::DrawTwoLongTabNarrowBackground(
    TTabDrawMode aTabDrawMode,
    TInt aActiveTab,
    CBitmapContext* aGc,
    SAknTabGroupBackgroundLayout& aLayout ) const
    {
    // If not given layout, then get the default layout
    if ( !aLayout.iUse )
        {
        aLayout = TwoLongTabBackground( aActiveTab );
        }

    if ( aActiveTab == 1 )
        {
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iSecondTab.iLeft,
                        aLayout.iSecondTab.iMiddle,
                        aLayout.iSecondTab.iRight,
                        aGc );
                        
        DrawActiveTab( aTabDrawMode,
                       aLayout.iFirstTab.iLeft,
                       aLayout.iFirstTab.iMiddle,
                       aLayout.iFirstTab.iRight,
                       aGc );
        }
    else
        {
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iFirstTab.iLeft,
                        aLayout.iFirstTab.iMiddle,
                        aLayout.iFirstTab.iRight,
                        aGc );
                        
        DrawActiveTab( aTabDrawMode,
                       aLayout.iSecondTab.iLeft, 
                       aLayout.iSecondTab.iMiddle,
                       aLayout.iSecondTab.iRight,
                       aGc );
        }
    }

CAknTabGroupGraphics::SAknTabGroupBackgroundLayout CAknTabGroupGraphics::ThreeLongTabBackground(TInt aActiveTab) const
    {
    SAknTabGroupBackgroundLayout aLayout;
    
    // screen
    TRect screenRect;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, screenRect );
    
    TBool landscape( Layout_Meta_Data::IsLandscapeOrientation() );

    TRect parentRect( iTabGroupBackgroundParent );

    // navi tabs 3 pane
    TRect naviTabsThreePaneRect(
        RectFromLayout( parentRect,
                        AknLayoutScalable_Avkon::navi_tabs_3_long_pane() ) );

    TRect tabsPassiveFirstPaneRect;
    TRect tabsPassiveSecondPaneRect;
    TRect tabsActivePaneRect;

    // We don't want to use options, just assume that active and passive tabs are same sizes.
    TRect parent( naviTabsThreePaneRect );
    
    TAknWindowComponentLayout aFirstTab(
        AknLayoutScalable_Avkon::tabs_3_long_active_pane( 0 ) );
    
    TAknWindowComponentLayout aSecondTab(
        AknLayoutScalable_Avkon::tabs_3_long_passive_pane( 0 ) );
    
    TAknWindowComponentLayout aThirdTab(
        AknLayoutScalable_Avkon::tabs_3_long_passive_pane_cp( 0 ) );
        
    if ( aActiveTab == 1 )
        {
        tabsActivePaneRect        = RectFromLayout( parent, aFirstTab );
        tabsPassiveFirstPaneRect  = RectFromLayout( parent, aSecondTab );
        tabsPassiveSecondPaneRect = RectFromLayout( parent, aThirdTab );
        }
    else if ( aActiveTab == 2 )
        {
        tabsPassiveFirstPaneRect  = RectFromLayout( parent, aFirstTab );
        tabsActivePaneRect        = RectFromLayout( parent, aSecondTab );
        tabsPassiveSecondPaneRect = RectFromLayout( parent, aThirdTab );
        }
    else if ( aActiveTab == 3 )
        {
        tabsPassiveFirstPaneRect  = RectFromLayout( parent, aFirstTab );
        tabsPassiveSecondPaneRect = RectFromLayout( parent, aSecondTab );
        tabsActivePaneRect        = RectFromLayout( parent, aThirdTab );
        }

    // Tabs 3 first passive tab pane
    TRect tabsThreePassiveFirstPaneRect( tabsPassiveFirstPaneRect );

    // Tabs 3 second passive tab pane
    TRect tabsThreePassiveSecondPaneRect( tabsPassiveSecondPaneRect );

    // Tabs 3 active tab pane
    TRect tabsThreeActivePaneRect( tabsActivePaneRect );
    
    TAknWindowComponentLayout passivePaneLayout(
        AknLayoutScalable_Avkon::bg_passive_tab_pane_cp5( landscape ) );
        
    TAknWindowComponentLayout passiveTabLayout1(
        AknLayoutScalable_Avkon::bg_passive_tab_pane_g1_cp5() );
        
    TAknWindowComponentLayout passiveTabLayout2(
        AknLayoutScalable_Avkon::bg_passive_tab_pane_g2_cp5() );
    
    TAknWindowComponentLayout passiveTabLayout3(
        AknLayoutScalable_Avkon::bg_passive_tab_pane_g3_cp5() );

    // bg active tab pane
    TRect tabsBackgroundActivePaneRect(
        RectFromLayout( tabsThreeActivePaneRect,
                        AknLayoutScalable_Avkon::bg_active_tab_pane_cp5( landscape ) ) );

    // bg first passive tab pane
    TRect tabsBackgroundFirstPassivePaneRect(
        RectFromLayout( tabsThreePassiveFirstPaneRect,
                        passivePaneLayout ) );

    // bg second passive tab pane
    TRect tabsBackgroundSecondPassivePaneRect(
        RectFromLayout( tabsThreePassiveSecondPaneRect,
                        passivePaneLayout ) );


    // Active tab left
    TRect activeTabLeftPaneRect(
        RectFromLayout( tabsBackgroundActivePaneRect,
                        AknLayoutScalable_Avkon::bg_active_tab_pane_g1_cp5() ) );

    // Active tab middle
    TRect activeTabMiddlePaneRect(
        RectFromLayout( tabsBackgroundActivePaneRect,
                        AknLayoutScalable_Avkon::bg_active_tab_pane_g2_cp5() ) );

    // Active tab right
    TRect activeTabRightPaneRect(
        RectFromLayout( tabsBackgroundActivePaneRect,
                        AknLayoutScalable_Avkon::bg_active_tab_pane_g3_cp5() ) );


    // First passive tab left
    TRect firstPassiveTabLeftPaneRect(
        RectFromLayout( tabsBackgroundFirstPassivePaneRect,
                        passiveTabLayout1 ) );

    // First passive tab middle
    TRect firstPassiveTabMiddlePaneRect(
        RectFromLayout( tabsBackgroundFirstPassivePaneRect,
                        passiveTabLayout2 ) );

    // First passive tab right
    TRect firstPassiveTabRightPaneRect(
        RectFromLayout( tabsBackgroundFirstPassivePaneRect,
                        passiveTabLayout3 ) );


    // Second passive tab left
    TRect secondPassiveTabLeftPaneRect(
        RectFromLayout( tabsBackgroundSecondPassivePaneRect,
                        passiveTabLayout1 ) );

    // Second passive tab middle
    TRect secondPassiveTabMiddlePaneRect(
        RectFromLayout( tabsBackgroundSecondPassivePaneRect,
                        passiveTabLayout2 ) );

    // Second passive tab right
    TRect secondPassiveTabRightPaneRect(
        RectFromLayout( tabsBackgroundSecondPassivePaneRect,
                        passiveTabLayout3 ) );

    if ( aActiveTab == 1 )
        {
        aLayout.iFirstTab.iLeft   = activeTabLeftPaneRect;
        aLayout.iFirstTab.iMiddle = activeTabMiddlePaneRect;
        aLayout.iFirstTab.iRight  = activeTabRightPaneRect;

        aLayout.iSecondTab.iLeft   = firstPassiveTabLeftPaneRect;
        aLayout.iSecondTab.iMiddle = firstPassiveTabMiddlePaneRect;
        aLayout.iSecondTab.iRight  = firstPassiveTabRightPaneRect;

        aLayout.iThirdTab.iLeft   = secondPassiveTabLeftPaneRect;
        aLayout.iThirdTab.iMiddle = secondPassiveTabMiddlePaneRect;
        aLayout.iThirdTab.iRight  = secondPassiveTabRightPaneRect;
        }
    else if ( aActiveTab == 2 )
        {
        aLayout.iFirstTab.iLeft   = firstPassiveTabLeftPaneRect;
        aLayout.iFirstTab.iMiddle = firstPassiveTabMiddlePaneRect;
        aLayout.iFirstTab.iRight  = firstPassiveTabRightPaneRect;

        aLayout.iSecondTab.iLeft   = activeTabLeftPaneRect;
        aLayout.iSecondTab.iMiddle = activeTabMiddlePaneRect;
        aLayout.iSecondTab.iRight  = activeTabRightPaneRect;

        aLayout.iThirdTab.iLeft   = secondPassiveTabLeftPaneRect;
        aLayout.iThirdTab.iMiddle = secondPassiveTabMiddlePaneRect;
        aLayout.iThirdTab.iRight  = secondPassiveTabRightPaneRect;
        }
    else if ( aActiveTab == 3 )
        {
        aLayout.iFirstTab.iLeft   = firstPassiveTabLeftPaneRect;
        aLayout.iFirstTab.iMiddle = firstPassiveTabMiddlePaneRect;
        aLayout.iFirstTab.iRight  = firstPassiveTabRightPaneRect;

        aLayout.iSecondTab.iLeft   = secondPassiveTabLeftPaneRect;
        aLayout.iSecondTab.iMiddle = secondPassiveTabMiddlePaneRect;
        aLayout.iSecondTab.iRight  = secondPassiveTabRightPaneRect;

        aLayout.iThirdTab.iLeft   = activeTabLeftPaneRect;
        aLayout.iThirdTab.iMiddle = activeTabMiddlePaneRect;
        aLayout.iThirdTab.iRight  = activeTabRightPaneRect;
        }

    aLayout.iFourthTab.iLeft   = TRect(0,0,0,0);
    aLayout.iFourthTab.iMiddle = TRect(0,0,0,0);
    aLayout.iFourthTab.iRight  = TRect(0,0,0,0);

    return aLayout;
    }

CAknTabGroupGraphics::SAknTabGroupBackgroundLayout CAknTabGroupGraphics::ThreeLongTabNarrowBackground(
    TInt aActiveTab ) const
    {
    SAknTabGroupBackgroundLayout aLayout;
    
    TBool landscape( Layout_Meta_Data::IsLandscapeOrientation() );
    
    // navi tabs pane
    TRect parentRect( NarrowParentRect() );

    // navi tabs 3 pane
    TRect naviTabsThreePaneRect(
        RectFromLayout( parentRect,
                        AknLayoutScalable_Avkon::navi_tabs_3_long_pane_srt() ) );

    TRect tabsPassiveFirstPaneRect;
    TRect tabsPassiveSecondPaneRect;
    TRect tabsActivePaneRect;

    // We don't want to use options, just assume that active and passive tabs are same sizes.
    TRect parent( naviTabsThreePaneRect );
    
    TAknWindowComponentLayout aFirstTab(
        AknLayoutScalable_Avkon::tabs_3_long_active_pane_srt( 0 ) );
        
    TAknWindowComponentLayout aSecondTab(
        AknLayoutScalable_Avkon::tabs_3_long_passive_pane_srt( 0 ) );
        
    TAknWindowComponentLayout aThirdTab(
        AknLayoutScalable_Avkon::tabs_3_long_passive_pane_cp_srt( 0 ) );

    if ( aActiveTab == 1 )
        {
        tabsActivePaneRect        = RectFromLayout( parent, aFirstTab );
        tabsPassiveFirstPaneRect  = RectFromLayout( parent, aSecondTab );
        tabsPassiveSecondPaneRect = RectFromLayout( parent, aThirdTab );
        }
    else if ( aActiveTab == 2)
        {
        tabsPassiveFirstPaneRect  = RectFromLayout( parent, aFirstTab );
        tabsActivePaneRect        = RectFromLayout( parent, aSecondTab );
        tabsPassiveSecondPaneRect = RectFromLayout( parent, aThirdTab );
        }
    else if ( aActiveTab == 3)
        {
        tabsPassiveFirstPaneRect  = RectFromLayout( parent, aFirstTab );
        tabsPassiveSecondPaneRect = RectFromLayout( parent, aSecondTab );
        tabsActivePaneRect        = RectFromLayout( parent, aThirdTab );
        }

    // Tabs 3 first passive tab pane
    TRect tabsThreePassiveFirstPaneRect( tabsPassiveFirstPaneRect );

    // Tabs 3 second passive tab pane
    TRect tabsThreePassiveSecondPaneRect( tabsPassiveSecondPaneRect );

    // Tabs 3 active tab pane
    TRect tabsThreeActivePaneRect( tabsActivePaneRect );
    
    TAknWindowComponentLayout passivePaneLayout(
        AknLayoutScalable_Avkon::bg_passive_tab_pane_cp5_srt( landscape ) );
    TAknWindowComponentLayout passiveLayout1(
        AknLayoutScalable_Avkon::bg_passive_tab_pane_g1_cp5_srt() );
    TAknWindowComponentLayout passiveLayout2(
        AknLayoutScalable_Avkon::bg_passive_tab_pane_g2_cp5_srt() );
    TAknWindowComponentLayout passiveLayout3(
        AknLayoutScalable_Avkon::bg_passive_tab_pane_g3_cp5_srt() );

    // bg active tab pane
    TRect tabsBackgroundActivePaneRect(
        RectFromLayout( tabsThreeActivePaneRect,
                        AknLayoutScalable_Avkon::bg_active_tab_pane_cp5_srt( landscape ) ) );

    // bg first passive tab pane
    TRect tabsBackgroundFirstPassivePaneRect(
        RectFromLayout( tabsThreePassiveFirstPaneRect,
                        passivePaneLayout ) );

    // bg second passive tab pane
    TRect tabsBackgroundSecondPassivePaneRect(
        RectFromLayout( tabsThreePassiveSecondPaneRect,
                        passivePaneLayout ) );


    // Active tab left
    TRect activeTabLeftPaneRect(
        RectFromLayout( tabsBackgroundActivePaneRect,
                        AknLayoutScalable_Avkon::bg_active_tab_pane_g1_cp5_srt() ) );

    // Active tab middle
    TRect activeTabMiddlePaneRect(
        RectFromLayout( tabsBackgroundActivePaneRect,
                        AknLayoutScalable_Avkon::bg_active_tab_pane_g2_cp5_srt() ) );

    // Active tab right
    TRect activeTabRightPaneRect(
        RectFromLayout( tabsBackgroundActivePaneRect,
                        AknLayoutScalable_Avkon::bg_active_tab_pane_g3_cp5_srt() ) );


    // First passive tab left
    TRect firstPassiveTabLeftPaneRect(
        RectFromLayout( tabsBackgroundFirstPassivePaneRect,
                        passiveLayout1 ) );

    // First passive tab middle
    TRect firstPassiveTabMiddlePaneRect(
        RectFromLayout( tabsBackgroundFirstPassivePaneRect,
                        passiveLayout2 ) );

    // First passive tab right
    TRect firstPassiveTabRightPaneRect(
        RectFromLayout( tabsBackgroundFirstPassivePaneRect,
                        passiveLayout3 ) );


    // Second passive tab left
    TRect secondPassiveTabLeftPaneRect(
        RectFromLayout( tabsBackgroundSecondPassivePaneRect,
                        passiveLayout1 ) );

    // Second passive tab middle
    TRect secondPassiveTabMiddlePaneRect(
        RectFromLayout( tabsBackgroundSecondPassivePaneRect,
                        passiveLayout2 ) );

    // Second passive tab right
    TRect secondPassiveTabRightPaneRect(
        RectFromLayout( tabsBackgroundSecondPassivePaneRect,
                        passiveLayout3 ) );


    if ( aActiveTab == 1 )
        {
        aLayout.iFirstTab.iLeft   = activeTabLeftPaneRect;
        aLayout.iFirstTab.iMiddle = activeTabMiddlePaneRect;
        aLayout.iFirstTab.iRight  = activeTabRightPaneRect;

        aLayout.iSecondTab.iLeft   = firstPassiveTabLeftPaneRect;
        aLayout.iSecondTab.iMiddle = firstPassiveTabMiddlePaneRect;
        aLayout.iSecondTab.iRight  = firstPassiveTabRightPaneRect;

        aLayout.iThirdTab.iLeft   = secondPassiveTabLeftPaneRect;
        aLayout.iThirdTab.iMiddle = secondPassiveTabMiddlePaneRect;
        aLayout.iThirdTab.iRight  = secondPassiveTabRightPaneRect;
        }
    else if ( aActiveTab == 2)
        {
        aLayout.iFirstTab.iLeft   = firstPassiveTabLeftPaneRect;
        aLayout.iFirstTab.iMiddle = firstPassiveTabMiddlePaneRect;
        aLayout.iFirstTab.iRight  = firstPassiveTabRightPaneRect;

        aLayout.iSecondTab.iLeft   = activeTabLeftPaneRect;
        aLayout.iSecondTab.iMiddle = activeTabMiddlePaneRect;
        aLayout.iSecondTab.iRight  = activeTabRightPaneRect;

        aLayout.iThirdTab.iLeft   = secondPassiveTabLeftPaneRect;
        aLayout.iThirdTab.iMiddle = secondPassiveTabMiddlePaneRect;
        aLayout.iThirdTab.iRight  = secondPassiveTabRightPaneRect;
        }
    else if ( aActiveTab == 3)
        {
        aLayout.iFirstTab.iLeft   = firstPassiveTabLeftPaneRect;
        aLayout.iFirstTab.iMiddle = firstPassiveTabMiddlePaneRect;
        aLayout.iFirstTab.iRight  = firstPassiveTabRightPaneRect;

        aLayout.iSecondTab.iLeft   = secondPassiveTabLeftPaneRect;
        aLayout.iSecondTab.iMiddle = secondPassiveTabMiddlePaneRect;
        aLayout.iSecondTab.iRight  = secondPassiveTabRightPaneRect;

        aLayout.iThirdTab.iLeft   = activeTabLeftPaneRect;
        aLayout.iThirdTab.iMiddle = activeTabMiddlePaneRect;
        aLayout.iThirdTab.iRight  = activeTabRightPaneRect;
        }

    aLayout.iFourthTab.iLeft   = TRect(0,0,0,0);
    aLayout.iFourthTab.iMiddle = TRect(0,0,0,0);
    aLayout.iFourthTab.iRight  = TRect(0,0,0,0);

    return aLayout;
    }

void CAknTabGroupGraphics::DrawThreeLongTabBackground( TTabDrawMode aTabDrawMode,
                                                       TInt aActiveTab, CBitmapContext* aGc,
                                                       SAknTabGroupBackgroundLayout& aLayout ) const
    {
    // If not given layout, then get the default layout
    if ( !aLayout.iUse )
        {
        aLayout = ThreeLongTabBackground( aActiveTab );
        }

    if ( aActiveTab == 1 )
        {
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iThirdTab.iLeft,
                        aLayout.iThirdTab.iMiddle,
                        aLayout.iThirdTab.iRight,
                        aGc );
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iSecondTab.iLeft,
                        aLayout.iSecondTab.iMiddle,
                        aLayout.iSecondTab.iRight,
                        aGc );
        DrawActiveTab( aTabDrawMode,
                       aLayout.iFirstTab.iLeft,
                       aLayout.iFirstTab.iMiddle,
                       aLayout.iFirstTab.iRight,
                       aGc );
        }
    else if ( aActiveTab == 2)
        {
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iFirstTab.iLeft,
                        aLayout.iFirstTab.iMiddle,
                        aLayout.iFirstTab.iRight,
                        aGc );
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iThirdTab.iLeft,
                        aLayout.iThirdTab.iMiddle,
                        aLayout.iThirdTab.iRight,
                        aGc );
        DrawActiveTab( aTabDrawMode,
                        aLayout.iSecondTab.iLeft,
                        aLayout.iSecondTab.iMiddle,
                        aLayout.iSecondTab.iRight,
                        aGc );
        }
    else if ( aActiveTab == 3)
        {
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iFirstTab.iLeft,
                        aLayout.iFirstTab.iMiddle,
                        aLayout.iFirstTab.iRight,
                        aGc );
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iSecondTab.iLeft,
                        aLayout.iSecondTab.iMiddle,
                        aLayout.iSecondTab.iRight,
                        aGc );
        DrawActiveTab( aTabDrawMode,
                       aLayout.iThirdTab.iLeft,
                       aLayout.iThirdTab.iMiddle,
                       aLayout.iThirdTab.iRight,
                       aGc );
        }
    }

void CAknTabGroupGraphics::DrawThreeLongTabNarrowBackground( TTabDrawMode aTabDrawMode,
                                                             TInt aActiveTab,
                                                             CBitmapContext* aGc,
                                                             SAknTabGroupBackgroundLayout& aLayout ) const
    {
    // If not given layout, then get the default layout
    if ( !aLayout.iUse )
        {
        aLayout = ThreeLongTabBackground( aActiveTab );
        }

    if ( aActiveTab == 1 )
        {
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iThirdTab.iLeft,
                        aLayout.iThirdTab.iMiddle,
                        aLayout.iThirdTab.iRight,
                        aGc );
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iSecondTab.iLeft,
                        aLayout.iSecondTab.iMiddle,
                        aLayout.iSecondTab.iRight,
                        aGc );
        DrawActiveTab( aTabDrawMode,
                       aLayout.iFirstTab.iLeft,
                       aLayout.iFirstTab.iMiddle,
                       aLayout.iFirstTab.iRight,
                       aGc );
        }
    else if ( aActiveTab == 2)
        {
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iFirstTab.iLeft,
                        aLayout.iFirstTab.iMiddle,
                        aLayout.iFirstTab.iRight,
                        aGc );
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iThirdTab.iLeft,
                        aLayout.iThirdTab.iMiddle,
                        aLayout.iThirdTab.iRight,
                        aGc );
        DrawActiveTab( aTabDrawMode,
                        aLayout.iSecondTab.iLeft,
                        aLayout.iSecondTab.iMiddle,
                        aLayout.iSecondTab.iRight,
                        aGc );
        }
    else if ( aActiveTab == 3)
        {
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iFirstTab.iLeft,
                        aLayout.iFirstTab.iMiddle,
                        aLayout.iFirstTab.iRight,
                        aGc );
        DrawPassiveTab( aTabDrawMode,
                        aLayout.iSecondTab.iLeft,
                        aLayout.iSecondTab.iMiddle,
                        aLayout.iSecondTab.iRight,
                        aGc );
        DrawActiveTab( aTabDrawMode,
                       aLayout.iThirdTab.iLeft,
                       aLayout.iThirdTab.iMiddle,
                       aLayout.iThirdTab.iRight,
                       aGc );
        }
    }


// ---------------------------------------------------------------------------
// Draws single tab graphics for an active tab.
// ---------------------------------------------------------------------------
//
void CAknTabGroupGraphics::DrawActiveTab( TTabDrawMode aTabDrawMode,
                                          TRect aLeft,
                                          TRect aMiddle,
                                          TRect aRight,
                                          CBitmapContext* aGc ) const
    {
    AknIconUtils::SetSize( iActiveTabLeft,
                           aLeft.Size(),
                           EAspectRatioNotPreserved );

    AknIconUtils::SetSize( iActiveTabMiddle,
                           aMiddle.Size(),
                           EAspectRatioNotPreserved );

    AknIconUtils::SetSize( iActiveTabRight,
                           aRight.Size(),
                           EAspectRatioNotPreserved );

    TRect rect( aLeft );

    if ( aTabDrawMode == CAknTabGroupGraphics::ENoDraw )
        {
        return;
        }
    else if ( aTabDrawMode == CAknTabGroupGraphics::ENormal )
        {
        aGc->BitBltMasked( rect.iTl,
                           iActiveTabLeft,
                           TRect( 0, 0, rect.Width(), rect.Height() ),
                           iActiveTabLeftMask,
                           ETrue );

        rect = aMiddle;
        aGc->BitBltMasked( rect.iTl,
                           iActiveTabMiddle,
                           TRect( 0, 0, rect.Width(), rect.Height() ),
                           iActiveTabMiddleMask,
                           ETrue );

        rect = aRight;
        aGc->BitBltMasked( rect.iTl,
                           iActiveTabRight,
                           TRect( 0, 0, rect.Width(), rect.Height() ),
                           iActiveTabRightMask,
                           ETrue );
        }
    else if ( aTabDrawMode == CAknTabGroupGraphics::EBitmapOnly )
        {
        aGc->BitBlt( rect.iTl,
                     iActiveTabLeft,
                     TRect( 0, 0, rect.Width(), rect.Height() ) );
        rect = aMiddle;

        aGc->BitBlt( rect.iTl,
                     iActiveTabMiddle,
                     TRect( 0, 0, rect.Width(), rect.Height() ) );

        rect = aRight;
        aGc->BitBlt( rect.iTl,
                     iActiveTabRight,
                     TRect( 0, 0, rect.Width(), rect.Height() ) );

        }
    else if ( aTabDrawMode == CAknTabGroupGraphics::EMaskOnly )
        {
        aGc->BitBltMasked( rect.iTl,
                           iActiveTabLeftMask,
                           TRect( 0, 0, rect.Width(), rect.Height() ),
                           iActiveTabLeftMask,
                           ETrue );

        rect = aMiddle;
        aGc->BitBltMasked( rect.iTl,
                           iActiveTabMiddleMask,
                           TRect( 0, 0, rect.Width(), rect.Height() ),
                           iActiveTabMiddleMask,
                           ETrue );

        rect = aRight;
        aGc->BitBltMasked( rect.iTl,
                           iActiveTabRightMask,
                           TRect( 0, 0, rect.Width(), rect.Height() ),
                           iActiveTabRightMask,
                           ETrue );
        }
    }


// ---------------------------------------------------------------------------
// Draws single tab graphics for a passive tab.
// ---------------------------------------------------------------------------
//
void CAknTabGroupGraphics::DrawPassiveTab( TTabDrawMode aDrawMode,
                                           TRect aLeft,
                                           TRect aMiddle,
                                           TRect aRight,
                                           CBitmapContext* aGc,
                                           TBool aFaded ) const
    {
    AknIconUtils::SetSize( iPassiveTabLeft,
                           aLeft.Size(),
                           EAspectRatioNotPreserved );

    AknIconUtils::SetSize( iPassiveTabMiddle,
                           aMiddle.Size(),
                           EAspectRatioNotPreserved );

    AknIconUtils::SetSize( iPassiveTabRight,
                           aRight.Size(),
                           EAspectRatioNotPreserved );

    TRect rect( aLeft );
    
    if ( aDrawMode != CAknTabGroupGraphics::ENoDraw )
        {
        if ( aFaded )
            {
            // Fading not currently supported.
            /*aGc->SetFadingParameters( KHiddenFadeBlackMap,
                                      KHiddenFadeWhiteMap );
            aGc->SetFaded( ETrue );*/
            }
        }
    else
        {
        return;
        }
    
    if ( aDrawMode == CAknTabGroupGraphics::ENormal )
        {
        aGc->BitBltMasked( rect.iTl,
                           iPassiveTabLeft,
                           TRect( rect.Size() ),
                           iPassiveTabLeftMask,
                           ETrue );
        rect = aMiddle;
        aGc->BitBltMasked( rect.iTl,
                           iPassiveTabMiddle,
                           TRect( rect.Size() ),
                           iPassiveTabMiddleMask,
                           ETrue );

        rect = aRight;
        aGc->BitBltMasked( rect.iTl,
                           iPassiveTabRight,
                           TRect( rect.Size() ),
                           iPassiveTabRightMask,
                           ETrue);
        }
    else if ( aDrawMode == CAknTabGroupGraphics::EBitmapOnly )
        {
        aGc->BitBlt( rect.iTl, iPassiveTabLeft, TRect( rect.Size() ) );

        rect = aMiddle;
        aGc->BitBlt( rect.iTl, iPassiveTabMiddle, TRect( rect.Size() ) );

        rect = aRight;
        aGc->BitBlt( rect.iTl, iPassiveTabRight, TRect( rect.Size() ) );
        }
    else if ( aDrawMode == CAknTabGroupGraphics::EMaskOnly )
        {
        aGc->BitBltMasked( rect.iTl,
                           iPassiveTabLeftMask,
                           TRect( rect.Size() ),
                           iPassiveTabLeftMask,
                           ETrue );

        rect = aMiddle;
        aGc->BitBltMasked( rect.iTl,
                           iPassiveTabMiddleMask,
                           TRect( rect.Size() ),
                           iPassiveTabMiddleMask,
                           ETrue );

        rect = aRight;
        aGc->BitBltMasked( rect.iTl,
                           iPassiveTabRightMask,
                           TRect( rect.Size() ),
                           iPassiveTabRightMask,
                           ETrue );
        }

    if ( aFaded )
        {
        // Fading not currently supported.
        //aGc->SetFaded( EFalse );
        }
    }


// ---------------------------------------------------------------------------
// Draws single tab part graphics for a passive tab.
// ---------------------------------------------------------------------------
//
void CAknTabGroupGraphics::DrawPassiveTabBit( TTabDrawMode aDrawMode,
                                              TTabPart aTabPart,
                                              TRect aRect,
                                              CBitmapContext* aGc ) const
    {
    if ( aDrawMode == CAknTabGroupGraphics::ENoDraw )
        {
        return;
        }
    
    // The passive tab bits are always parts of the hidden tabs and
    // as such always drawn faded.
    // Fading not currently supported.
    //aGc->SetFadingParameters( KHiddenFadeBlackMap, KHiddenFadeWhiteMap );
    //aGc->SetFaded( ETrue );

    CFbsBitmap* passiveTabBit     = NULL;
    CFbsBitmap* passiveTabBitMask = NULL;
    
    TSize rectSize( aRect.Size() );
    
    switch ( aTabPart )
        {
        case ERight:
            {
            AknIconUtils::SetSize( iPassiveTabRight,
                                   rectSize,
                                   EAspectRatioNotPreserved );
            passiveTabBit     = iPassiveTabRight;
            passiveTabBitMask = iPassiveTabRightMask;
            break;
            }

        case ELeft:
            {
            AknIconUtils::SetSize( iPassiveTabLeft,
                                   rectSize,
                                   EAspectRatioNotPreserved );
            passiveTabBit     = iPassiveTabLeft;
            passiveTabBitMask = iPassiveTabLeftMask;
            break;
            }

        default:
            {
            return;
            }
        }

    if ( aDrawMode == CAknTabGroupGraphics::ENormal )
        {
        aGc->BitBltMasked( aRect.iTl,
                           passiveTabBit,
                           TRect( rectSize ),
                           passiveTabBitMask,
                           ETrue );
        }
    else if ( aDrawMode == CAknTabGroupGraphics::EBitmapOnly )
        {
        aGc->BitBlt( aRect.iTl, passiveTabBit, TRect( rectSize ) );
        }
    else if ( aDrawMode == CAknTabGroupGraphics::EMaskOnly )
        {
        aGc->BitBltMasked( aRect.iTl,
                           passiveTabBitMask,
                           TRect( rectSize ),
                           passiveTabBitMask,
                           ETrue );
        }

    // Fading not currently supported.
    //aGc->SetFaded( EFalse );
    }


void CAknTabGroupGraphics::LoadTabGraphicsL()
    {
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    TAknsItemID iid;

    // active tabs
    iid = KAknsIIDQgnGrafTabActiveL;
    AknsUtils::CreateIconL( skin,
                            iid,
                            iActiveTabLeft,
                            iActiveTabLeftMask,
                            AknIconUtils::AvkonIconFileName(),
                            EMbmAvkonQgn_graf_tab_active_l,
                            EMbmAvkonQgn_graf_tab_active_l_mask );

    iid = KAknsIIDQgnGrafTabActiveM;
    AknsUtils::CreateIconL( skin,
                            iid,
                            iActiveTabMiddle,
                            iActiveTabMiddleMask,
                            AknIconUtils::AvkonIconFileName(),
                            EMbmAvkonQgn_graf_tab_active_m,
                            EMbmAvkonQgn_graf_tab_active_m_mask );

    iid = KAknsIIDQgnGrafTabActiveR;
    AknsUtils::CreateIconL( skin,
                            iid,
                            iActiveTabRight,
                            iActiveTabRightMask,
                            AknIconUtils::AvkonIconFileName(),
                            EMbmAvkonQgn_graf_tab_active_r,
                            EMbmAvkonQgn_graf_tab_active_r_mask );

    // passive tabs
    iid = KAknsIIDQgnGrafTabPassiveL;
    AknsUtils::CreateIconL( skin,
                            iid,
                            iPassiveTabLeft,
                            iPassiveTabLeftMask,
                            AknIconUtils::AvkonIconFileName(),
                            EMbmAvkonQgn_graf_tab_passive_l,
                            EMbmAvkonQgn_graf_tab_passive_l_mask );

    iid = KAknsIIDQgnGrafTabPassiveM;
    AknsUtils::CreateIconL( skin,
                            iid,
                            iPassiveTabMiddle,
                            iPassiveTabMiddleMask,
                            AknIconUtils::AvkonIconFileName(),
                            EMbmAvkonQgn_graf_tab_passive_m,
                            EMbmAvkonQgn_graf_tab_passive_m_mask );

    iid = KAknsIIDQgnGrafTabPassiveR;
    AknsUtils::CreateIconL( skin,
                            iid,
                            iPassiveTabRight,
                            iPassiveTabRightMask,
                            AknIconUtils::AvkonIconFileName(),
                            EMbmAvkonQgn_graf_tab_passive_r,
                            EMbmAvkonQgn_graf_tab_passive_r_mask );

    // Disable compression of the masks because the pointer event
    // hit-test needs to use CFbsBitmap::GetPixel()-method.
    AknIconUtils::DisableCompression( iActiveTabLeftMask );
    AknIconUtils::DisableCompression( iActiveTabMiddleMask );
    AknIconUtils::DisableCompression( iActiveTabRightMask );
    AknIconUtils::DisableCompression( iPassiveTabLeftMask );
    AknIconUtils::DisableCompression( iPassiveTabMiddleMask );
    AknIconUtils::DisableCompression( iPassiveTabRightMask );
    }

TRect CAknTabGroupGraphics::RectFromLayout( TRect aParent,
                                            TAknWindowComponentLayout aComponentLayout ) const
    {
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect( aParent, aComponentLayout );
    return layoutRect.Rect();
    }


TRect CAknTabGroupGraphics::NarrowParentRect() const
    {
    // screen
    TRect screenRect;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, screenRect );
    
    TBool landscape( Layout_Meta_Data::IsLandscapeOrientation() );

    // top area
    TAknWindowComponentLayout areaLayout;
    if ( landscape )
        {
        areaLayout = AknLayoutScalable_Avkon::area_top_pane( 8 );
        }
    else
        {
        areaLayout = AknLayoutScalable_Avkon::area_top_pane( 6 );
        }
    TRect areaRect( RectFromLayout( screenRect, areaLayout ) );

    // navi pane
    TRect naviRect(
        RectFromLayout( areaRect, AknLayoutScalable_Avkon::navi_pane( 2 ) ) );

    // short navi pane
    TAknWindowComponentLayout naviSrtLayout;
    if ( landscape )
        {
        naviSrtLayout = AknLayoutScalable_Avkon::navi_pane_srt( 0 );
        }
    else
        {
        naviSrtLayout = AknLayoutScalable_Avkon::navi_pane_srt( 3 );
        }
    TRect naviSrtRect( RectFromLayout( areaRect, naviSrtLayout ) );

    TRect parentRect( naviSrtRect );
    
    // Set relative to navipane coordinates
    parentRect.Move( -naviRect.iTl.iX, 0 );
    parentRect.iTl.iY = 0;
    parentRect.SetHeight( iTabGroupBackgroundParent.Height() );

    // navi navi pane
    TRect naviNaviPaneRect(
        RectFromLayout( parentRect,
                        AknLayoutScalable_Avkon::navi_navi_pane_srt() ) );

    // navi tabs pane
    TRect naviNaviTabsPaneRect(
        RectFromLayout( naviNaviPaneRect,
                        AknLayoutScalable_Avkon::navi_navi_tabs_pane_srt() ) );

    if ( !landscape )
        {
        // In portrait mode the indicator pane width must be 
        // taken into account separately.
        TAknWindowLineLayout indicatorPaneLayout(
            AknLayoutScalable_Avkon::uni_indicator_pane( 1 ).LayoutLine() );
        naviNaviTabsPaneRect.Move(
            AknLayoutUtils::LayoutMirrored() ? indicatorPaneLayout.iW :
                                               -indicatorPaneLayout.iW,
            0 );
        }

    return naviNaviTabsPaneRect;
    }


TBool CAknTabGroupGraphics::TabGroupBackgroundAvailable()
    {
    // 1. If SVG icons are not available, return false. We don't
    //    want to use bitmap versions because those would look ugly in
    //    this case (we prefer to default then to old style bitmaps).
    //
    // 2. If currently acive skin provides old bitmap tabs we
    //    don't want to override those for skin backwards
    //    compatibility reasons. But not in stacon pane because
    //    many old skins do not look good in that layout.
    //
    // 3. Finally check if scalable UI data is not available
    //    we cannot draw tabs from SVG because we don't have
    //    access to layout data.

#ifndef __SCALABLE_ICONS
    return EFalse; // 1
#endif

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    TAknsItemID iid;
    iid.Set( EAknsMajorAvkon, EMbmAvkonQgn_graf_tab_21 );

    if ( AknsUtils::GetCachedBitmap( skin, iid ) &&
         !AknStatuspaneUtils::StaconPaneActive() )
        {
        return EFalse; // 2.
        }

    return iTabGroupBackgroundAvailable; // 3
    }

// End of file
