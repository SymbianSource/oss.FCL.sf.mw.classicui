/*
* Copyright (c) 2002-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implementation for tab navigation control.
*
*/


// SYSTEM INCLUDE FILES
#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikdefmacros.h>
#endif
#include <w32std.h>
#include <barsread.h>
#include <eikbctrl.h>
#include <eiklabel.h>
#include <eikimage.h>
#include <eikenv.h>
#include <AknLayoutDef.h>
#include <AknsUtils.h>
#include <AknIconUtils.h>
#include <AknDef.h>
#include <e32std.h>
#include <AknStatuspaneUtils.h>
#include <layoutmetadata.cdl.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <akniconconfig.h>

#include <AknTasHook.h>
#include <touchfeedback.h>

// USER INCLUDE FILES
#include "aknappui.h"
#include "avkon.hrh"
#include "AknNaviObserver.h"
#include "AknPanic.h"
#include "akntabgrp.h"
#include "AknTabObserver.h"
#include "aknenv.h"
#include "AknBitmapMirrorUtils.h"
#include "AknTabGrpGraphics.h"
#include "aknnavide.h"
#include "AknNaviDecoratorObserver.h"

// GLOBAL CONSTANTS

const TInt KTabArrayGranularity             = 4;
const TInt KAknTabGroupNoTabs               = KErrNotFound;
const TInt KTabColorBitmapQueueGranularity  = 2;
const TInt KTabColorBitmapActiveColorIndex  = 0;
const TInt KTabColorBitmapPassiveColorIndex = 1;

/** Maximum number of tabs that can be shown in the tab group at a time. */
const TInt KMaxNumberOfVisibleTabs          = 4;

/** Maximum number of frames in the tab group animations. */
const TInt KMaxAmountOfAnimationEvents      = 80;

/** Interval used between the frames in tab group animations. */
const TInt KAnimationEventInterval          = 25000; // 40 events/s

/** Speed value for the layout switch animation, smaller value is faster. */
const TInt KLayoutSwitchAnimationSpeed      = 25;

/** Minimum horizontal step size value for the tab cycle animation. */
const TInt KMinimumCycleAnimationStepSize   = 3;

/** Tolerance used for pointer event position's x-value in tab navigation. */
const TInt KDragNavigationTolerance         = 5;

//
// Extension to CAknTab
//

NONSHARABLE_CLASS( CAknTabExtension ) : public CBase
    {
public:
    static CAknTabExtension* NewL();
    ~CAknTabExtension();

private:
    CAknTabExtension();

public:

    /** Indicates whether or not the tab is shown in narrow tab group layout. */
    TBool iNarrowTabLayout;

    /** Total amount of tab in the tab group, needed to decide right layoutlines. */
    TInt  iNumberOfTabsInTabGroup;

    /** Indicates whether or not this tab is drawn using multi-color mode. */
    TBool iMultiColorMode;

    /** Indicates whether or not the tab is shown in long tab group layout. */
    TBool iLongTab;
    };

CAknTabExtension* CAknTabExtension::NewL()
    {
    CAknTabExtension* self = new ( ELeave ) CAknTabExtension();
    return self;
    }


CAknTabExtension::CAknTabExtension()
    {
    }

CAknTabExtension::~CAknTabExtension()
    {
    }

//
// CAknTab
//

CAknTab::~CAknTab()
    {
    AKNTASHOOK_REMOVE();
    delete iLabel;
    delete iBitmap;
    delete iBitmapMask;

    if ( iColorBitmaps )
        {
        iColorBitmaps->ResetAndDestroy();
        delete iColorBitmaps;
        iColorBitmaps = NULL;
        }

    delete iExtension;
    }

CAknTab* CAknTab::NewL( const CCoeControl& aParent, TResourceReader& aReader )
    {
    CAknTab* self = CAknTab::NewLC( aParent, aReader );
    CleanupStack::Pop( self );
    return self;
    }

CAknTab* CAknTab::NewLC( const CCoeControl& aParent, TResourceReader& aReader )
    {
    CAknTab* self = new (ELeave) CAknTab( 0 ); // default tab id
    CleanupStack::PushL( self );
    self->SetContainerWindowL( aParent );
    self->ConstructFromResourceL( aReader );
    AKNTASHOOK_ADDL( self, "CAknTab" );
    return self;
    }

CAknTab* CAknTab::NewL( TInt aId,
                        const CCoeControl& aParent,
                        const TDesC& aTabText )
    {
    CAknTab* self = CAknTab::NewLC( aId, aParent, aTabText );
    CleanupStack::Pop( self );
    return self;
    }

CAknTab* CAknTab::NewLC( TInt aId,
                         const CCoeControl& aParent,
                         const TDesC& aTabText )
    {
    CAknTab* self = new (ELeave) CAknTab( aId );
    CleanupStack::PushL( self );
    self->SetContainerWindowL( aParent );
    self->ConstructL( aTabText );
    AKNTASHOOK_ADDL( self, "CAknTab" );
    return self;
    }

CAknTab* CAknTab::NewL( TInt aId,
                        const CCoeControl& aParent,
                        const TDesC& aTabText,
                        const CFbsBitmap* aTabBitmap,
                        const CFbsBitmap* aMask )
    {
    CAknTab* self = CAknTab::NewLC( aId, aParent, aTabText, aTabBitmap, aMask );
    CleanupStack::Pop( self );
    return self;
    }

CAknTab* CAknTab::NewLC( TInt aId,
                         const CCoeControl& aParent,
                         const TDesC& aTabText,
                         const CFbsBitmap* aTabBitmap,
                         const CFbsBitmap* aMask )
    {
    CAknTab* self = new (ELeave) CAknTab( aId );
    CleanupStack::PushL( self );
    self->SetContainerWindowL( aParent );
    self->ConstructL( aTabText );
    self->ConstructL( aTabBitmap, aMask );
    AKNTASHOOK_ADDL( self, "CAknTab" );
    return self;
    }

CAknTab* CAknTab::NewL( TInt aId,
                        const CCoeControl& aParent,
                        const CFbsBitmap* aTabBitmap,
                        const CFbsBitmap* aMask )
    {
    CAknTab* self = CAknTab::NewLC( aId, aParent, aTabBitmap, aMask );
    CleanupStack::Pop( self );
    return self;
    }

CAknTab* CAknTab::NewLC( TInt aId,
                         const CCoeControl& aParent,
                         const CFbsBitmap* aTabBitmap,
                         const CFbsBitmap* aMask )
    {
    CAknTab* self = new (ELeave) CAknTab( aId );
    CleanupStack::PushL( self );
    self->SetContainerWindowL( aParent );
    self->ConstructL( aTabBitmap, aMask );
    AKNTASHOOK_ADDL( self, "CAknTab" );
    return self;
    }

CAknTab::CAknTab( TInt aId ) : iId( aId )
    {
    }

void CAknTab::ConstructFromResourceL( TResourceReader& aReader )
    {
    if ( !iExtension )
        {
        iExtension = CAknTabExtension::NewL();
        }

    iId = aReader.ReadInt16(); // tab id

    HBufC* txt = aReader.ReadHBufCL(); // tab text
    if ( txt )
        {
        CleanupStack::PushL( txt );
        ConstructL( *txt );
        CleanupStack::PopAndDestroy( txt );
        }

    HBufC* bitmapFile = aReader.ReadHBufCL(); // bmp filename
    TInt bitmapId     = aReader.ReadInt16();  // bmp id
    TInt maskId       = aReader.ReadInt16();  // bmp mask id

    if ( bitmapFile )
        {
        CleanupStack::PushL( bitmapFile );
        TFileName fileName( *bitmapFile );
        CompleteWithAppPath( fileName );
        if ( bitmapId != KErrNotFound )
            {
            CFbsBitmap* bitmap;
            if ( maskId != KErrNotFound )
                {
                CFbsBitmap* mask;
                AknIconUtils::CreateIconLC( bitmap,
                                            mask,
                                            fileName,
                                            bitmapId,
                                            maskId );
                CleanupStack::Pop( mask );
                CleanupStack::Pop( bitmap );
                // moves ownership of bitmap and mask at beginning =>
                // no need to have bitmap/mask in cleanupstack
                ConstructL( bitmap, mask );
                }
            else
                {
                bitmap = AknIconUtils::CreateIconL( fileName, bitmapId );
                // moves ownership of bitmap and mask at beginning =>
                // no need to have bitmap/mask in cleanupstack
                ConstructL( bitmap );
                }
            }
        CleanupStack::PopAndDestroy( bitmapFile );  // bitmapFile
        }

    LoadColorBitmapL();
    }

void CAknTab::ConstructL( const TDesC& aTabText )
    {
    if ( !iExtension )
        {
        iExtension = CAknTabExtension::NewL();
        }

    iLabel = new (ELeave) CEikLabel;
    iLabel->SetContainerWindowL( *this );
    iLabel->SetTextL( aTabText );
    iLabel->SetAlignment( EHCenterVCenter );
    iLabel->SetAllMarginsTo( KNaviTabMargins );

    if ( AknLayoutUtils::Variant() == EEuropeanVariant )
        {
        iLabel->SetFont( LatinBold12() );
        }
    else    // APAC
        {
        iLabel->SetFont( ApacPlain12() );
        }

    LoadColorBitmapL();
    }

void CAknTab::ConstructL( const CFbsBitmap* aTabBitmap,
                          const CFbsBitmap* aMask )
    {
    if ( !iExtension )
        {
        iExtension = CAknTabExtension::NewL();
        }

    iBitmap = aTabBitmap;
    iBitmapMask = aMask;
    LoadColorBitmapL();
    }

void CAknTab::ReplaceTextL( const TDesC& aTabText )
    {
    if ( iLabel )
        {
        iLabel->SetTextL( aTabText );
        }
    }

void CAknTab::SetActive( TBool aActive, TDrawNow aDrawNow )
    {
    iActive = aActive;

    if ( aDrawNow == EDrawNow )
        {
        DrawNow();
        }
    }

TBool CAknTab::Active() const
    {
    return iActive;
    }


TInt CAknTab::Id() const
    {
    return iId;
    }


enum CAknTab::TAknTabDataType CAknTab::TabType() const
    {
    TAknTabDataType tabType( EAknTabNone );

    if ( iLabel && iBitmap )
        {
        tabType = EAknTabTextAndIcon;
        }
    else if ( iBitmap )
        {
        tabType = EAknTabIcon;
        }
    else if ( iLabel )
        {
        tabType = EAknTabText;
        }

    return tabType;
    }


TSize CAknTab::MinimumSize()
    {
    TSize minSize;

    if ( iLabel )
        {
        minSize += iLabel->MinimumSize();
        }
    if ( iBitmap )
        {
        minSize += iBitmap->SizeInPixels();
        }

    return minSize;
    }


void CAknTab::SetDimmed( TBool aDimmed )
    {
    CCoeControl::SetDimmed( aDimmed );

    if ( iLabel )
        {
        iLabel->SetDimmed( aDimmed );
        }
    }


void CAknTab::GetColorUseListL( CArrayFix<TCoeColorUse>& aColorUseList ) const
    {
    TCoeColorUse colorUse;
    colorUse.SetLogicalColor( EColorDialogBackground );
    colorUse.SetUse( TCoeColorUse::EBack |
                     TCoeColorUse::ESurrounds |
                     TCoeColorUse::EActive |
                     TCoeColorUse::ENormal |
                     TCoeColorUse::ENeutral );
    aColorUseList.AppendL( colorUse );
    }


void CAknTab::SizeChanged()
    {
    if ( AknStatuspaneUtils::FlatLayoutActive() &&
         !iExtension->iNarrowTabLayout )
        {
        SizeChangedInFlatLayout();
        }
    else if ( iExtension->iNarrowTabLayout )
        {
        SizeChangedInNarrowLayout();
        }
    else
        {
        SizeChangedInNormalLayout();
        }
    }


void CAknTab::SizeChangedInNormalLayout()
    {
    if ( !iColorBitmaps )
        {
        TRAP_IGNORE( LoadColorBitmapL() );
        }

    TBool landscape( Layout_Meta_Data::IsLandscapeOrientation() );
    TBool staconPaneActive( AknStatuspaneUtils::StaconPaneActive() );
    TBool longTab( iExtension && iExtension->iLongTab );
    TRect rect( Rect() );

    if ( iLabel && iBitmap )
        {
        iBitmapRect.LayoutRect(
            rect,
            AknLayoutScalable_Avkon::navi_navi_icon_text_pane_g1() );
        AknIconUtils::SetSize( const_cast<CFbsBitmap*> ( iBitmap ),
                               iBitmapRect.Rect().Size() );

        AknLayoutUtils::LayoutLabel(
            iLabel,
            rect,
            AknLayoutScalable_Avkon::navi_navi_icon_text_pane_t1() );

        iLabel->CropText();
        }
    else
        {
        if ( iLabel )
            {
            TAknTextComponentLayout textLayout;

            switch ( iExtension->iNumberOfTabsInTabGroup )
                {
                case 1:
                    {
                    textLayout =
                        AknLayoutScalable_Avkon::tabs_2_long_active_pane_t1(
                            landscape );
                    break;
                    }

                case 2:
                    {
                    if ( longTab )
                        {
                        textLayout =
                            AknLayoutScalable_Avkon::tabs_2_long_active_pane_t1(
                                landscape );
                        }
                    else
                        {
                        if ( iActive )
                            {
                            textLayout =
                                AknLayoutScalable_Avkon::tabs_2_active_pane_t1(
                                    landscape );
                            }
                        else
                            {
                            textLayout =
                                AknLayoutScalable_Avkon::tabs_2_passive_pane_t1(
                                    landscape );
                            }
                        }
                    break;
                    }

                case 3:
                    {
                    if ( longTab )
                        {
                        textLayout =
                            AknLayoutScalable_Avkon::tabs_3_long_active_pane_t1(
                                landscape );
                        }
                    else
                        {
                        if ( iActive )
                            {
                            textLayout =
                                AknLayoutScalable_Avkon::tabs_3_active_pane_t1(
                                    landscape );
                            }
                        else
                            {
                            textLayout =
                                AknLayoutScalable_Avkon::tabs_3_passive_pane_t1(
                                    landscape );
                            }
                        }
                    break;
                    }

                case 4:
                default:
                    {
                    textLayout =
                        AknLayoutScalable_Avkon::tabs_4_active_pane_t1(
                            landscape );
                    break;
                    }
                }

            AknLayoutUtils::LayoutLabel( iLabel, rect, textLayout );

            iLabel->CropText();
            }

        if ( iBitmap )
            {
            TAknWindowComponentLayout l1( TAknWindowComponentLayout::Compose(
                AknLayoutScalable_Avkon::navi_tabs_2_pane(),
                TAknWindowComponentLayout::Compose(
                    AknLayoutScalable_Avkon::tabs_2_active_pane( 0 ),
                    AknLayoutScalable_Avkon::tabs_2_active_pane_g1() ) ) );

            TAknWindowComponentLayout l2( TAknWindowComponentLayout::Compose(
                AknLayoutScalable_Avkon::navi_tabs_3_pane(),
                TAknWindowComponentLayout::Compose(
                    AknLayoutScalable_Avkon::tabs_3_active_pane( 0 ),
                    AknLayoutScalable_Avkon::tabs_3_active_pane_g1() ) ) );

            TAknWindowComponentLayout l3( TAknWindowComponentLayout::Compose(
                AknLayoutScalable_Avkon::navi_tabs_4_pane(),
                TAknWindowComponentLayout::Compose(
                    AknLayoutScalable_Avkon::tabs_4_active_pane( 0 ),
                    AknLayoutScalable_Avkon::tabs_4_active_pane_g1() ) ) );

            TAknLayoutRect layoutRect;

            layoutRect.LayoutRect( rect, l1 );
            TRect r1( layoutRect.Rect() );
            layoutRect.LayoutRect( rect, l2 );
            TRect r2( layoutRect.Rect() );
            layoutRect.LayoutRect( rect, l3 );
            TRect r3( layoutRect.Rect() );

            TInt w = rect.Size().iWidth;
            TSize size;

            if ( w < r2.Width() ) // smaller than 3 icon layout - use 4 icon layout
                {
                size.iWidth = r3.Width();
                size.iHeight = r3.Height();
                }
            else if ( w >= r2.Width() && w < r1.Width() )  // use 3 icon layout
                {
                size.iWidth = r2.Width();
                size.iHeight = r2.Height();
                }
            else // same or larger than 2 icon layout - use 2 icon layout
                {
                size.iWidth = r1.Width();
                size.iHeight = r1.Height();
                }

            AknIconUtils::SetSize( const_cast<CFbsBitmap*> (iBitmap), size );

            TInt imageWidth  = iBitmap->SizeInPixels().iWidth;
            TInt imageXPos   = rect.Width() - imageWidth;
            TInt imageHeight = iBitmap->SizeInPixels().iHeight;
            TInt imageYPos   = rect.Height() - imageHeight;

            TRect nRect( 0,0, rect.Width(), rect.Height() );

            if ( imageXPos < 0 || imageYPos < 0 )
                {
                iBitmapRect.LayoutRect( nRect,
                                        ELayoutEmpty,
                                        rect.iTl.iX,
                                        rect.iTl.iY,
                                        ELayoutEmpty,
                                        ELayoutEmpty,
                                        rect.Width(),
                                        rect.Height());
                }
            else
                {
                // Center image.
                imageXPos  = imageXPos >> 1;
                imageXPos += rect.iTl.iX;
                imageYPos  = imageYPos >> 1;
                imageYPos += rect.iTl.iY;

                iBitmapRect.LayoutRect( nRect,
                                        ELayoutEmpty,
                                        imageXPos,
                                        imageYPos,
                                        ELayoutEmpty,
                                        ELayoutEmpty,
                                        imageWidth,
                                        imageHeight );
                }
            }
        }
    }


void CAknTab::SizeChangedInNarrowLayout()
    {
    if ( !iColorBitmaps )
        {
        TRAP_IGNORE( LoadColorBitmapL() );
        }

    TBool isStaconPaneActive( AknStatuspaneUtils::StaconPaneActive() );
    TBool longTab( iExtension && iExtension->iLongTab );

    TRect rect( Rect() );

    if ( iLabel && iBitmap )
        {
        iBitmapRect.LayoutRect(
            rect,
            AknLayoutScalable_Avkon::navi_navi_icon_text_pane_srt_g1() );
        AknIconUtils::SetSize( const_cast<CFbsBitmap*> ( iBitmap ),
                               iBitmapRect.Rect().Size() );
        AknLayoutUtils::LayoutLabel(
            iLabel,
            rect,
            AknLayoutScalable_Avkon::navi_navi_icon_text_pane_srt_t1( 0 ) );

        iLabel->CropText();
        }
    else
        {
        if ( iLabel )
            {
            TAknTextComponentLayout textLayout;

            switch ( iExtension->iNumberOfTabsInTabGroup )
                {
                case 1:
                    {
                    textLayout =
                        AknLayoutScalable_Avkon::tabs_2_long_active_pane_t1(
                            isStaconPaneActive );
                    break;
                    }

                case 2:
                    {
                    if ( longTab )
                        {
                        textLayout =
                            AknLayoutScalable_Avkon::tabs_2_long_active_pane_srt_t1(
                                isStaconPaneActive );
                        }
                    else
                        {
                        textLayout =
                            AknLayoutScalable_Avkon::tabs_2_active_pane_srt_t1(
                                isStaconPaneActive );
                        }
                    break;
                    }

                case 3:
                    {
                    if ( longTab )
                        {
                        textLayout =
                            AknLayoutScalable_Avkon::tabs_3_long_active_pane_srt_t1(
                                isStaconPaneActive );
                        }
                    else
                        {
                        textLayout =
                            AknLayoutScalable_Avkon::tabs_3_active_pane_srt_t1(
                                isStaconPaneActive );
                        }
                    break;
                    }

                case 4:
                default:
                    {
                    textLayout =
                        AknLayoutScalable_Avkon::tabs_4_active_pane_srt_t1(
                            isStaconPaneActive );
                    break;
                    }
                }

            AknLayoutUtils::LayoutLabel( iLabel, rect, textLayout );

            iLabel->CropText();
            }

        if ( iBitmap )
            {
            TAknWindowComponentLayout l1(
                AknLayoutScalable_Avkon::tabs_2_active_pane_srt_g1() );
            TAknWindowComponentLayout l2(
                AknLayoutScalable_Avkon::tabs_3_active_pane_srt_g1() );
            TAknWindowComponentLayout l3(
                AknLayoutScalable_Avkon::tabs_4_active_pane_srt_g1() );

            TAknLayoutRect layoutRect;

            layoutRect.LayoutRect( rect, l1 );
            TRect r1 = layoutRect.Rect();
            layoutRect.LayoutRect( rect, l2 );
            TRect r2 = layoutRect.Rect();
            layoutRect.LayoutRect( rect, l3 );
            TRect r3 = layoutRect.Rect();

            TInt w = rect.Size().iWidth;
            TSize size;

            if ( w < r2.Width() )  // smaller than 3 icon layout - use 4 icon layout
                {
                size.iWidth = r3.Width();
                size.iHeight = r3.Height();
                }
            else if ( w >= r2.Width() && w < r1.Width() )  // use 3 icon layout
                {
                size.iWidth = r2.Width();
                size.iHeight = r2.Height();
                }
            else // same or larger than 2 icon layout - use 2 icon layout
                {
                size.iWidth = r1.Width();
                size.iHeight = r1.Height();
                }

            AknIconUtils::SetSize( const_cast<CFbsBitmap*> (iBitmap), size );

            TInt imageWidth  = iBitmap->SizeInPixels().iWidth;
            TInt imageXPos   = rect.Width() - imageWidth;
            TInt imageHeight =  iBitmap->SizeInPixels().iHeight;
            TInt imageYPos   = rect.Height() - imageHeight;

            TRect nRect( 0,0, rect.Width(), rect.Height() );

            if ( imageXPos < 0 || imageYPos < 0 )
                {
                iBitmapRect.LayoutRect( nRect,
                                        ELayoutEmpty,
                                        rect.iTl.iX,
                                        rect.iTl.iY,
                                        ELayoutEmpty,
                                        ELayoutEmpty,
                                        rect.Width(),
                                        rect.Height() );
                }
            else
                {
                // Center image.
                imageXPos  = imageXPos >> 1;
                imageXPos += rect.iTl.iX;
                imageYPos  = imageYPos >> 1;
                imageYPos += rect.iTl.iY;
                iBitmapRect.LayoutRect( nRect,
                                        ELayoutEmpty,
                                        imageXPos,
                                        imageYPos,
                                        ELayoutEmpty,
                                        ELayoutEmpty,
                                        imageWidth,
                                        imageHeight );
                }
            }
        }

    }


// ---------------------------------------------------------------------------
// Handles size change events in flat status pane layouts.
// ---------------------------------------------------------------------------
//
void CAknTab::SizeChangedInFlatLayout()
    {
    if ( !iColorBitmaps )
        {
        TRAP_IGNORE( LoadColorBitmapL() );
        }

    TBool longTab( iExtension && iExtension->iLongTab );

    TRect rect( Rect() );

    if ( iLabel && iBitmap )
        {
        iBitmapRect.LayoutRect( rect, AknLayoutScalable_Avkon::navi_navi_icon_text_pane_g1() );

        AknIconUtils::SetSize( const_cast<CFbsBitmap*> ( iBitmap ),
                               iBitmapRect.Rect().Size() );

        AknLayoutUtils::LayoutLabel(
            iLabel,
            rect,
            AknLayoutScalable_Avkon::navi_navi_icon_text_pane_t1() );

        iLabel->CropText();
        }
    else
        {
        if ( iLabel )
            {
            TAknTextComponentLayout textLayout;

            switch ( iExtension->iNumberOfTabsInTabGroup )
                {
                case 1:
                    {
                    textLayout =
                        AknLayoutScalable_Avkon::tabs_2_long_active_pane_t1( 0 );
                    break;
                    }

                case 2:
                    {
                    if ( longTab )
                        {
                        textLayout =
                            AknLayoutScalable_Avkon::tabs_2_long_active_pane_t1( 0 );
                        }
                    else
                        {
                        if ( iActive )
                            {
                            textLayout =
                                AknLayoutScalable_Avkon::tabs_2_active_pane_t1( 0 );
                            }
                        else
                            {
                            textLayout =
                                AknLayoutScalable_Avkon::tabs_2_passive_pane_t1( 0 );
                            }
                        }
                    break;
                    }

                case 3:
                    {
                    if ( longTab )
                        {
                        textLayout =
                            AknLayoutScalable_Avkon::tabs_3_long_active_pane_t1( 0 );
                        }
                    else
                        {
                        if ( iActive )
                            {
                            textLayout =
                                AknLayoutScalable_Avkon::tabs_3_active_pane_t1( 0 );
                            }
                        else
                            {
                            textLayout =
                                AknLayoutScalable_Avkon::tabs_3_passive_pane_t1( 0 );
                            }
                        }
                    break;
                    }

                case 4:
                default:
                    {
                    textLayout =
                        AknLayoutScalable_Avkon::tabs_4_active_pane_t1( 0 );
                    break;
                    }
                }

            AknLayoutUtils::LayoutLabel( iLabel, rect, textLayout );

            iLabel->CropText();
            }

        if ( iBitmap )
            {
            TAknWindowComponentLayout l1(
                AknLayoutScalable_Avkon::tabs_2_active_pane_g1() );
            TAknWindowComponentLayout l2(
                AknLayoutScalable_Avkon::tabs_3_active_pane_g1() );
            TAknWindowComponentLayout l3(
                AknLayoutScalable_Avkon::tabs_4_active_pane_g1() );

            TAknLayoutRect layoutRect;

            layoutRect.LayoutRect( rect, l1 );
            TRect r1 = layoutRect.Rect();
            layoutRect.LayoutRect( rect, l2 );
            TRect r2 = layoutRect.Rect();
            layoutRect.LayoutRect( rect, l3 );
            TRect r3 = layoutRect.Rect();

            TInt w = rect.Size().iWidth;
            TSize size;

            if ( w < r2.Width() )  // smaller than 3 icon layout - use 4 icon layout
                {
                size.iWidth = r3.Width();
                size.iHeight = r3.Height();
                }
            else if ( w >= r2.Width() && w < r1.Width() )  // use 3 icon layout
                {
                size.iWidth = r2.Width();
                size.iHeight = r2.Height();
                }
            else // same or larger than 2 icon layout - use 2 icon layout
                {
                size.iWidth = r1.Width();
                size.iHeight = r1.Height();
                }

            AknIconUtils::SetSize( const_cast<CFbsBitmap*> (iBitmap), size );

            TInt imageWidth  = iBitmap->SizeInPixels().iWidth;
            TInt imageXPos   = rect.Width() - imageWidth;
            TInt imageHeight =  iBitmap->SizeInPixels().iHeight;
            TInt imageYPos   = rect.Height() - imageHeight;

            TRect nRect( 0,0, rect.Width(), rect.Height() );

            if ( imageXPos < 0 || imageYPos < 0 )
                {
                iBitmapRect.LayoutRect( nRect,
                                        ELayoutEmpty,
                                        rect.iTl.iX,
                                        rect.iTl.iY,
                                        ELayoutEmpty,
                                        ELayoutEmpty,
                                        rect.Width(),
                                        rect.Height() );
                }
            else
                {
                // Center image.
                imageXPos  = imageXPos >> 1;
                imageXPos += rect.iTl.iX;
                imageYPos  = imageYPos >> 1;
                imageYPos += rect.iTl.iY;
                iBitmapRect.LayoutRect( nRect,
                                        ELayoutEmpty,
                                        imageXPos,
                                        imageYPos,
                                        ELayoutEmpty,
                                        ELayoutEmpty,
                                        imageWidth,
                                        imageHeight );
                }
            }
        }
    }


// ---------------------------------------------------------------------------
// Returns the amount of component controls.
// ---------------------------------------------------------------------------
//
TInt CAknTab::CountComponentControls() const
    {
    TInt count( 0 );

    if ( iLabel )
        {
        count++;
        }

    return count;
    }


CCoeControl* CAknTab::ComponentControl( TInt /*aIndex*/ ) const
    {
    return iLabel;
    }

void CAknTab::Draw( const TRect& /*aRect*/ ) const
    {
    if ( iLabel )
        {
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        TRgb color;


        if ( iExtension->iNumberOfTabsInTabGroup == 1 ) // >= EAknTabWidthWithOneTab
            {
            TInt error = AknsUtils::GetCachedColor( skin, color,
                KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG2 );
            if ( !error )
                {
                // Ignore error
                TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL( *iLabel,
                    EColorLabelText, color ) );
                }
            }
        else
            {
            if ( iActive )
                {
                TInt error = AknsUtils::GetCachedColor( skin, color,
                    KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG3 );
                if ( !error )
                    {
                    // Ignore error
                    TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL( *iLabel,
                        EColorLabelText, color ) );
                    }
                }
            else
                {
                TInt error = AknsUtils::GetCachedColor( skin, color,
                    KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG4 );
                if ( !error )
                    {
                    // Ignore error
                    TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL( *iLabel,
                        EColorLabelText, color ) );
                    }
                }
            }

        }

    if ( iBitmap )
        {
        TBool legacyDraw = EFalse;
        CWindowGc& gc=SystemGc();
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        if ( skin && !iExtension->iMultiColorMode )
            {
            CFbsBitmap* colorBitmap = NULL;
            if (iColorBitmaps &&
                iColorBitmaps->At(KTabColorBitmapActiveColorIndex) &&
                iColorBitmaps->At(KTabColorBitmapPassiveColorIndex) )
                {
                if( iActive )
                    {
                    colorBitmap = iColorBitmaps->At(KTabColorBitmapActiveColorIndex);
                    }
                else
                    {
                    colorBitmap = iColorBitmaps->At(KTabColorBitmapPassiveColorIndex);
                    }
                }

            if ( colorBitmap && iBitmapMask )
                {
                iBitmapRect.DrawImage( gc,
                                       colorBitmap,
                                       const_cast<CFbsBitmap*> ( iBitmapMask ) );
                }
            else
                {
                legacyDraw = ETrue;
                }
            }
        else // No skin (legacy drawing) or multi-colored drawing.
            {
            legacyDraw = ETrue;
            }
        if ( legacyDraw )
            {
            iBitmapRect.DrawImage( gc,
                                   const_cast<CFbsBitmap*>( iBitmap ),
                                   const_cast<CFbsBitmap*>( iBitmapMask ) );
            }
        }
    }

void CAknTab::HandlePointerEventL( const TPointerEvent& aPointerEvent )
    {
    if ( aPointerEvent.iType==TPointerEvent::EButton1Down &&
         !iActive &&
         !IsDimmed() )
        {
        ReportEventL( MCoeControlObserver::EEventStateChanged );
        }
    }

EXPORT_C void* CAknTab::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

// ---------------------------------------------------------------------------
// Loads the bitmap used in drawing the tab icon with correct color.
// ---------------------------------------------------------------------------
//
void CAknTab::LoadColorBitmapL()
    {
    if ( iColorBitmaps )
        {
        iColorBitmaps->ResetAndDestroy();
        delete iColorBitmaps;
        iColorBitmaps = NULL;
        }

    TRect rect( Rect() );

    if ( rect.IsEmpty() )
        {
        // We cannot decide the right color.
        // This method will be called again when the rect is set.
        return;
        }

    if ( !iColorBitmaps )
        {
        iColorBitmaps = new (ELeave) CAknTabColorBitmapArray(
            KTabColorBitmapQueueGranularity );
        CFbsBitmap* activeColorBitmap = new (ELeave) CFbsBitmap();
        CleanupStack::PushL(activeColorBitmap);
        CFbsBitmap* passiveColorBitmap = new (ELeave) CFbsBitmap();
        CleanupStack::PushL( passiveColorBitmap );
        iColorBitmaps->AppendL( activeColorBitmap );
        iColorBitmaps->AppendL( passiveColorBitmap );
        CleanupStack::Pop( 2, activeColorBitmap );
        }

    TBool isStaconPaneActive( AknStatuspaneUtils::StaconPaneActive() );
    TBool isFlatLayoutActive(
        isStaconPaneActive ? EFalse : AknStatuspaneUtils::FlatLayoutActive() );

    TAknLayoutRect layoutRect;
    // LAF does not contain line for EAknTabWidthWithOneTab
    // so we use this instead.
    layoutRect.LayoutRect( rect, AknLayoutScalable_Avkon::navi_tabs_2_pane() );
    TRect tabRect = layoutRect.Rect();
    if ( tabRect.Width() < 0 || tabRect.Height() < 0 )
        {
        tabRect.SetRect( 0, 0, 0, 0 );
        }

    if ( !( iColorBitmaps &&
            iColorBitmaps->At( KTabColorBitmapActiveColorIndex ) &&
            iColorBitmaps->At( KTabColorBitmapPassiveColorIndex ) ) )
        {
        return;
        }

    // Note 64K or 16M mode seems to have some issues with some HW possibly
    // related to bitmap compression, so we use display's color mode
    // here instead for now instead of the AknIconConfig's preferred
    // display mode.
    TDisplayMode screenDisplayMode( iEikonEnv->ScreenDevice()->DisplayMode() );
    iColorBitmaps->At( KTabColorBitmapActiveColorIndex )->Create(
        Size(), screenDisplayMode );
    iColorBitmaps->At( KTabColorBitmapPassiveColorIndex )->Create(
        Size(), screenDisplayMode );

    TRgb color( KRgbGray );
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();

    // First active color...
    TAknsQsnIconColorsIndex colorIndex;
    if (iExtension->iNumberOfTabsInTabGroup == 1)
        {
        colorIndex = EAknsCIQsnIconColorsCG7;
        }
    else
        {
        colorIndex = EAknsCIQsnIconColorsCG8;
        }
    AknsUtils::GetCachedColor( skin,
                               color,
                               KAknsIIDQsnIconColors,
                               colorIndex );

    CFbsBitmapDevice* destinationDevice =
        CFbsBitmapDevice::NewL(
            iColorBitmaps->At( KTabColorBitmapActiveColorIndex ) );
    CleanupStack::PushL( destinationDevice );
    CFbsBitGc* destinationGc;
    User::LeaveIfError( destinationDevice->CreateContext( destinationGc ) );
    destinationGc->SetPenColor( color );
    destinationGc->SetPenStyle( CGraphicsContext::ESolidPen );
    destinationGc->SetBrushColor( color );
    destinationGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
    destinationGc->DrawRect(
        TRect( iColorBitmaps->At( KTabColorBitmapActiveColorIndex )->SizeInPixels() ) );

    delete destinationGc;
    CleanupStack::PopAndDestroy( destinationDevice );

    // ...then passive color.
    AknsUtils::GetCachedColor( skin,
                               color,
                               KAknsIIDQsnIconColors,
                               EAknsCIQsnIconColorsCG9 );

    destinationDevice =
        CFbsBitmapDevice::NewL(
            iColorBitmaps->At( KTabColorBitmapPassiveColorIndex ) );
    CleanupStack::PushL(destinationDevice);
    User::LeaveIfError( destinationDevice->CreateContext( destinationGc ) );
    destinationGc->SetPenColor( color );
    destinationGc->SetPenStyle( CGraphicsContext::ESolidPen );
    destinationGc->SetBrushColor( color );
    destinationGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
    destinationGc->DrawRect(
        TRect( iColorBitmaps->At( KTabColorBitmapPassiveColorIndex )->SizeInPixels() ) );

    delete destinationGc;
    CleanupStack::PopAndDestroy( destinationDevice );
    }


void CAknTab::HandleResourceChange( TInt aType )
    {
    CCoeControl::HandleResourceChange( aType );

    if ( aType == KEikDynamicLayoutVariantSwitch ||
         aType == KEikColorResourceChange ||
         aType == KAknsMessageSkinChange )
        {
        TRAP_IGNORE( LoadColorBitmapL() );
        DrawDeferred();
        }
    }

void CAknTab::SetTotalAmountOfTabs( TInt aAmount )
    {
    iExtension->iNumberOfTabsInTabGroup = aAmount;
    LoadColorBitmapL();
    }

void CAknTab::SetNarrowTabLayout( TBool aNarrow )
    {
    iExtension->iNarrowTabLayout = aNarrow;
    }


// ---------------------------------------------------------------------------
// CAknTab::SetMultiColorMode
// ---------------------------------------------------------------------------
//
void CAknTab::SetMultiColorMode( TBool aMultiColor )
    {
    if ( iExtension )
        {
        iExtension->iMultiColorMode = aMultiColor;
        }
    }


// ---------------------------------------------------------------------------
// CAknTab::MultiColorMode
// ---------------------------------------------------------------------------
//
TBool CAknTab::MultiColorMode() const
    {
    if ( iExtension )
        {
        return iExtension->iMultiColorMode;
        }
    else
        {
        return EFalse;
        }
    }


// ---------------------------------------------------------------------------
// CAknTab::SetLongTabLayout
// Sets this tab to use long layout.
// ---------------------------------------------------------------------------
//
void CAknTab::SetLongTabLayout( TBool aLongTab )
    {
    if ( iExtension )
        {
        iExtension->iLongTab = aLongTab;
        }
    }


// ================= PRIVATE CLASS =======================

class CAknTabGroupExtension : public CBase
    {
public:

    /** Types of supported tab group animations. */
    enum TTabAnimationType
        {
        /**
        * No animation is currently used.
        */
        ENoAnimation = 0,
        /**
        * Animation type used when switching between
        * normal and flat tab group layout.
        */
        ELayoutSwitchAnimation,
        /**
        * Animation type used when cycling between tabs in three tab layout
        * when there are more than three tabs in the tab group.
        */
        ETabCycleAnimation
        };

    CAknTabGroupExtension();
    ~CAknTabGroupExtension(){};

public: // Member data.

    CFbsBitmap*           iStaconTabBitmaps[KTabNumberOfTabBitmaps];
    CFbsBitmap*           iStaconTabMaskBitmaps[KTabNumberOfTabBitmaps];
    CAknTabGroupGraphics* iTabSvgGraphics;

    /** Layout used for the tab background graphics. */
    CAknTabGroupGraphics::SAknTabGroupBackgroundLayout iTabBackgroundLayout;

    /** Layout used for the tab background graphics during tab animation. */
    CAknTabGroupGraphics::SAknTabGroupBackgroundLayout iNextTabBackgroundLayout;

    /** Timer used in tab animations. */
    CPeriodic* iTabAnimationTimer;

    /** Type of the current tab animation. */
    TTabAnimationType iTabAnimationType;

    /** Amount of completed tab animation steps. */
    TInt iAmountOfDoneAnimationEvents;

    /** Direction of the current tab cycle animation (left or right). */
    CAknTabGroup::TDirection iTabCycleAnimationDirection;

    /** Horizontal distance left in the tab cycle animation. */
    TInt iTabCycleAnimationDistanceLeft;

    /** Is the tab cycle animation in process. */
    TBool iTabCycleAnimationOngoing;

    /**
    * Specifies on which side of the tab group there are tabs
    * that don't fit in the set of currently displayed tabs.
    */
    CAknTabGroupGraphics::TTabsHidden iTabsHidden;

    TBool             iTabAnimationDoubleBufferNarrowTabLayout;
    TBool             iTabAnimationDoubleBufferLongTabs;
    TInt              iTabAnimationDoubleBufferNumberOfTabsShown;
    TInt              iTabAnimationDoubleBufferpositionActive;

    TBool  iNarrowTabLayout;
    TBool  iNarrowTabLayoutNext;

    /** Are navigation arrows shown in the current tab layout. */
    TBool  iNaviArrowsUsed;

    /** Index of the tab where pointer down event happened. */
    TInt   iPointerDownTab;

    /** X-value of the pointer down event position. */
    TInt   iPointerDownXPosition;

    /** This is the tab width that is set by the application. */
    TInt   iRequestedTabWidth;
    };


CAknTabGroupExtension::CAknTabGroupExtension()
    {
    iPointerDownTab       = -1;
    iPointerDownXPosition = -1;
    }


//
// CAknTabGroup
//

EXPORT_C CAknTabGroup::CAknTabGroup() : iActiveTab(KAknTabGroupNoTabs)
    {
    iTabFixedWidth     = -1;
    iFirstShownTab     = 0;
    iNumberOfTabsShown = 0;

    // Tab bitmaps and masks for every tab group layouts
    iBitmapNames[0]  = EMbmAvkonQgn_graf_tab_21;
    iBitmapNames[1]  = EMbmAvkonQgn_graf_tab_22;
    iBitmapNames[2]  = EMbmAvkonQgn_graf_tab_long_21;
    iBitmapNames[3]  = EMbmAvkonQgn_graf_tab_long_22;
    iBitmapNames[4]  = EMbmAvkonQgn_graf_tab_long_31;
    iBitmapNames[5]  = EMbmAvkonQgn_graf_tab_long_32;
    iBitmapNames[6]  = EMbmAvkonQgn_graf_tab_long_33;
    iBitmapNames[7]  = EMbmAvkonQgn_graf_tab_31;
    iBitmapNames[8]  = EMbmAvkonQgn_graf_tab_32;
    iBitmapNames[9]  = EMbmAvkonQgn_graf_tab_33;
    iBitmapNames[10] = EMbmAvkonQgn_graf_tab_41;
    iBitmapNames[11] = EMbmAvkonQgn_graf_tab_42;
    iBitmapNames[12] = EMbmAvkonQgn_graf_tab_43;
    iBitmapNames[13] = EMbmAvkonQgn_graf_tab_44;

    iBitmapMaskNames[0]  = EMbmAvkonQgn_graf_tab_21_mask;
    iBitmapMaskNames[1]  = EMbmAvkonQgn_graf_tab_22_mask;
    iBitmapMaskNames[2]  = EMbmAvkonQgn_graf_tab_long_21_mask;
    iBitmapMaskNames[3]  = EMbmAvkonQgn_graf_tab_long_22_mask;
    iBitmapMaskNames[4]  = EMbmAvkonQgn_graf_tab_long_31_mask;
    iBitmapMaskNames[5]  = EMbmAvkonQgn_graf_tab_long_32_mask;
    iBitmapMaskNames[6]  = EMbmAvkonQgn_graf_tab_long_33_mask;
    iBitmapMaskNames[7]  = EMbmAvkonQgn_graf_tab_31_mask;
    iBitmapMaskNames[8]  = EMbmAvkonQgn_graf_tab_32_mask;
    iBitmapMaskNames[9]  = EMbmAvkonQgn_graf_tab_33_mask;
    iBitmapMaskNames[10] = EMbmAvkonQgn_graf_tab_41_mask;
    iBitmapMaskNames[11] = EMbmAvkonQgn_graf_tab_42_mask;
    iBitmapMaskNames[12] = EMbmAvkonQgn_graf_tab_43_mask;
    iBitmapMaskNames[13] = EMbmAvkonQgn_graf_tab_44_mask;

    iMirrored = AknLayoutUtils::LayoutMirrored();
    }

EXPORT_C CAknTabGroup::~CAknTabGroup()
    {
    AKNTASHOOK_REMOVE();
    if ( iTabArray )
        {
        iTabArray->ResetAndDestroy();
        }
    delete iTabArray;

    for ( TInt i = 0; i < KTabNumberOfTabBitmaps; i++ )
        {
        delete( iTabBitmaps[i] );
        delete( iTabMaskBitmaps[i] );
        }

    if ( iExtension )
        {
        for ( TInt j = 0; j < KTabNumberOfTabBitmaps; j++ )
            {
            delete( iExtension->iStaconTabBitmaps[j] );
            delete( iExtension->iStaconTabMaskBitmaps[j] );
            }

        delete iExtension->iTabSvgGraphics;
        if ( iExtension->iTabAnimationTimer )
            {
            iExtension->iTabAnimationTimer->Cancel();
            delete iExtension->iTabAnimationTimer;
            }
        }

    delete iExtension;

    }

EXPORT_C CAknTabGroup* CAknTabGroup::NewL( const CCoeControl& aParent )
    {
    CAknTabGroup* self = CAknTabGroup::NewLC( aParent );
    CleanupStack::Pop( self );
    return self;
    }

EXPORT_C CAknTabGroup* CAknTabGroup::NewLC( const CCoeControl& aParent )
    {
    CAknTabGroup* self = new (ELeave) CAknTabGroup;
    CleanupStack::PushL( self );
    self->SetContainerWindowL( aParent );
    self->ConstructL();
    AKNTASHOOK_ADDL( self, "CAknTabGroup" );
    return self;
    }

EXPORT_C TInt CAknTabGroup::AddTabL( TResourceReader& aReader )
    {
    CAknTab* newTab = CAknTab::NewL( *this, aReader );
    CommonAddTabL( newTab ); // Takes ownership of newTab safely.
    return newTab->Id();
    }

EXPORT_C void CAknTabGroup::AddTabL( TInt aTabId, const TDesC& aTabText )
    {
    CAknTab* newTab = CAknTab::NewL( aTabId, *this, aTabText );
    CommonAddTabL( newTab );  // Takes ownership of newTab safely.
    }


EXPORT_C void CAknTabGroup::AddTabL( TInt aTabId,
                                     const TDesC& aTabText,
                                     const CFbsBitmap* aTabBitmap,
                                     const CFbsBitmap* aMask)
    {
    CAknTab* newTab = CAknTab::NewL( aTabId, *this, aTabText, aTabBitmap, aMask );
    CommonAddTabL( newTab );  // Takes ownership of newTab safely.
    }


EXPORT_C void CAknTabGroup::AddTabL( TInt aTabId,
                                     const CFbsBitmap* aTabBitmap,
                                     const CFbsBitmap* aMask)
    {
    CAknTab* newTab = CAknTab::NewL( aTabId, *this, aTabBitmap, aMask );
    CommonAddTabL( newTab );  // Takes ownership of newTab safely.
    }

void CAknTabGroup::CommonAddTabL( CAknTab* aTab )
    {
    CleanupStack::PushL( aTab );
    aTab->SetObserver( this );
    aTab->SetControlContext( this );

    if ( iMirrored && iTabObserver )
        {
        // If tab group is mirrored then tabs are inserted in
        // reverse order.
        iTabArray->InsertL( 0, aTab );
        }
    else
        {
        iTabArray->AppendL( aTab );
        }

    CleanupStack::Pop( aTab );

    if ( iTabFixedWidth < 0 && TabCount() > 1 )
        {
        SetTabFixedWidthL( KTabWidthWithTwoTabs );
        }
    }

EXPORT_C void CAknTabGroup::ReplaceTabL( TResourceReader& aReader )
    {
    CAknTab* newTab = CAknTab::NewL( *this, aReader );
    CommonReplaceTabL( newTab ); // Takes ownership of the newTab safely
    }

EXPORT_C void CAknTabGroup::ReplaceTabL( TInt aTabId,const TDesC& aTabText )
    {
    CAknTab* newTab=CAknTab::NewL( aTabId, *this, aTabText );
    CommonReplaceTabL( newTab ); // Takes ownership of the newTab safely
    }

EXPORT_C void CAknTabGroup::ReplaceTabL( TInt aTabId,
                                         const TDesC& aTabText,
                                         const CFbsBitmap* aTabBitmap,
                                         const CFbsBitmap* aMask )
    {
    CAknTab* newTab = CAknTab::NewL( aTabId, *this, aTabText, aTabBitmap, aMask );
    CommonReplaceTabL( newTab ); // Takes ownership of the newTab safely
    }

EXPORT_C void CAknTabGroup::ReplaceTabL( TInt aTabId,
                                         const CFbsBitmap* aTabBitmap,
                                         const CFbsBitmap* aMask )
    {
    CAknTab* newTab = CAknTab::NewL( aTabId, *this, aTabBitmap, aMask );
    CommonReplaceTabL( newTab ); // Takes ownership of the newTab safely
    }

void CAknTabGroup::CommonReplaceTabL( CAknTab* aTab )
    {
    CleanupStack::PushL( aTab );
    aTab->SetObserver( this );
    TInt tabIndex = ConvertTabIndex( TabIndexFromId( aTab->Id() ) );
    __ASSERT_ALWAYS( tabIndex >= 0, Panic( EAknPanicOutOfRange ) );

    // Is replaced tab active tab or not
    TBool isActiveTab =  iTabArray->At( tabIndex )->Active();
    TBool isMultiColor = iTabArray->At( tabIndex )->MultiColorMode();
    delete iTabArray->At( tabIndex );
    iTabArray->Delete( tabIndex );
    iTabArray->InsertL( tabIndex, aTab );
    CleanupStack::Pop( aTab );

    aTab->SetMultiColorMode( isMultiColor );
    aTab->SetControlContext( this );
    aTab->SetActive( isActiveTab, ENoDrawNow );
    SizeChanged();
    TInt event = MAknNavigationObserver::ENaviEventRedrawNeeded;
    ReportEventL( static_cast<MCoeControlObserver::TCoeEvent>( event ) );
    }

EXPORT_C void CAknTabGroup::ReplaceTabTextL( TInt aTabId, const TDesC& aTabText )
    {
    TInt tabIndex = ConvertTabIndex( TabIndexFromId( aTabId ) );
    __ASSERT_ALWAYS( tabIndex >= 0, Panic( EAknPanicOutOfRange ) );
    iTabArray->At( tabIndex )->ReplaceTextL( aTabText );
    SizeChanged();
    TInt event = MAknNavigationObserver::ENaviEventRedrawNeeded;
    ReportEventL( STATIC_CAST( MCoeControlObserver::TCoeEvent, event ) );
    }

EXPORT_C void CAknTabGroup::DeleteTabL( TInt aTabId )
    {
    TInt oldActiveTab = iActiveTab;
    TInt tabIndex = ConvertTabIndex( TabIndexFromId( aTabId ) );
    __ASSERT_ALWAYS( tabIndex >= 0, Panic( EAknPanicOutOfRange ) );
    delete iTabArray->At( tabIndex );
    iTabArray->Delete( tabIndex );
    TInt tabCount = TabCount();
    if ( tabCount == 0 )
        {
        iActiveTab = KAknTabGroupNoTabs;
        }
    if ( tabIndex < iActiveTab )
        {
        iActiveTab--;
        }
    else if ( tabIndex == iActiveTab && iActiveTab == tabCount )
        {
        iActiveTab--;
        if ( iFirstShownTab > 0 )
            {
            iFirstShownTab--;
            }
        }

    SizeChanged();

    TInt event = MAknNavigationObserver::ENaviEventRedrawNeeded;
    if ( tabCount <= 1 )
        {
        event = MAknNavigationObserver::ENaviEventOneItemExists;
        }
    else if ( iActiveTab == 0 && oldActiveTab != 0 )
        {
        event = MAknNavigationObserver::ENaviEventLeftMostItemReached;
        }
    else if ( iActiveTab == ( tabCount - 1 ) &&
              oldActiveTab != tabCount )
        {
        event = MAknNavigationObserver::ENaviEventRightMostItemReached;
        }

    ReportEventL( static_cast<MCoeControlObserver::TCoeEvent>( event ) );
    }

void CAknTabGroup::ConstructL()
    {
    iExtension = new (ELeave) CAknTabGroupExtension();
    iExtension->iTabSvgGraphics = CAknTabGroupGraphics::NewL();
    iExtension->iTabAnimationTimer = CPeriodic::NewL( CActive::EPriorityIdle );
    iTabArray = new (ELeave) CArrayPtrFlat<CAknTab>( KTabArrayGranularity );
    }

EXPORT_C void CAknTabGroup::SetActiveTabById( TInt aTabId )
    {
    TInt tabIndex = Index( aTabId );
    SetActiveTabByIndex( ConvertTabIndex( tabIndex ) );
    }


// ---------------------------------------------------------------------------
// Sets the active tab by tab index.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknTabGroup::SetActiveTabByIndex( TInt aTabIndex )
    {
    const TInt numTabs = TabCount();

    TInt realIndex = ConvertTabIndex( aTabIndex );

    // When iActiveTab doesn't change, nothing need to do.
    if ( realIndex == iActiveTab )
        {
        return;
        }

    if ( realIndex >= 0 && realIndex < numTabs )
        {
        CArrayPtr<CAknTab>& tabArray = *iTabArray;
        if ( iActiveTab >= 0 )
            {
            tabArray[iActiveTab]->SetFocus( EFalse, ENoDrawNow );
            tabArray[iActiveTab]->SetActive( EFalse, ENoDrawNow );
            }
        iActiveTab = realIndex;
        tabArray[iActiveTab]->SetFocus( ETrue, ENoDrawNow );
        tabArray[iActiveTab]->SetActive( ETrue, ENoDrawNow );

        if ( AknLayoutUtils::PenEnabled() &&
             iTabFixedWidth == KTabWidthWithThreeTabs )
            {
            if ( realIndex != RightMostTabIndex() &&
                 realIndex != LeftMostTabIndex() )
                {
                iFirstShownTab = realIndex - 1;
                }
            else if ( realIndex < iFirstShownTab )
                {
                iFirstShownTab = realIndex;
                }
            else if ( realIndex >= ( iFirstShownTab + iNumberOfTabsShown ) )
                {
                iFirstShownTab = realIndex - iNumberOfTabsShown + 1;
                }
            }
        else
            {
            if ( realIndex < iFirstShownTab )
                {
                iFirstShownTab = realIndex;
                }

            if ( realIndex >= ( iFirstShownTab + iNumberOfTabsShown ) )
                {
                iFirstShownTab = realIndex - iNumberOfTabsShown + 1;
                }
            }

        SizeChanged();

        if ( !AknStatuspaneUtils::FlatLayoutActive() &&
             iExtension->iTabAnimationType ==
                 CAknTabGroupExtension::ELayoutSwitchAnimation )
            {
            CancelTabAnimationEventTimer();
            }

        SetDecoratorLayout( EFalse );
        TRAP_IGNORE( InitTabAnimationL() );

        ReportNavigationEvent();
        }
    }

EXPORT_C TInt CAknTabGroup::ActiveTabId() const
    {
    if ( iActiveTab >= 0 )
        {
        return iTabArray->At( iActiveTab )->Id();
        }

    return KErrNotFound;
    }

EXPORT_C TInt CAknTabGroup::ActiveTabIndex() const
    {
    return ConvertTabIndex( iActiveTab );
    }


// ---------------------------------------------------------------------------
// Sets the width (used layout) of the tabs.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknTabGroup::SetTabFixedWidthL( TInt aWidth )
    {
    if ( iExtension )
        {
        // Store the requested width in case it's mapped here to another
        // width but usable in some other layout.
        iExtension->iRequestedTabWidth = aWidth;
        }

    TInt  numberOfTabsShown = iNumberOfTabsShown;
    TInt  tabFixedWidth     = iTabFixedWidth;
    TBool longTabs          = iLongTabs;

    iLongTabs = EFalse;

    if ( aWidth <= KTabWidthWithTwoTabs && aWidth > KTabWidthWithThreeTabs )
        {
        iNumberOfTabsShown = 2;
        iTabFixedWidth = KTabWidthWithTwoTabs;
        }
    else if ( AknLayoutUtils::PenEnabled() )
        {
        if ( aWidth <= KTabWidthWithThreeTabs )
            {
            iNumberOfTabsShown = 3;
            iTabFixedWidth = KTabWidthWithThreeTabs;
            }
        else
            {
            iNumberOfTabsShown = 1;
            iTabFixedWidth = KTabWidthWithOneTab;
            }
        }
    else
        {
        if ( aWidth <= KTabWidthWithThreeTabs &&
             aWidth > KTabWidthWithFourTabs )
            {
            iNumberOfTabsShown = 3;
            iTabFixedWidth = KTabWidthWithThreeTabs;
            }
        else if ( aWidth <= KTabWidthWithFourTabs )
            {
            iNumberOfTabsShown = 4;
            iTabFixedWidth = KTabWidthWithFourTabs;
            }
        else if ( aWidth <= KTabWidthWithThreeLongTabs )
            {
            iNumberOfTabsShown = 3;
            iTabFixedWidth = KTabWidthWithThreeLongTabs;
            iLongTabs = ETrue;
            }
        else if ( aWidth <= KTabWidthWithTwoLongTabs )
            {
            iNumberOfTabsShown = 2;
            iTabFixedWidth = KTabWidthWithTwoLongTabs;
            iLongTabs = ETrue;
            }
        else
            {
            iNumberOfTabsShown = 1;
            iTabFixedWidth = KTabWidthWithOneTab;
            }
        }

    // When iNumberOfTabsShown, iTabFixedWidth, iLongTabs don't change,
    // there's no reason to do LoadTabBitmapsL(), etc.
    if ( numberOfTabsShown == iNumberOfTabsShown &&
         tabFixedWidth == iTabFixedWidth &&
         longTabs == iLongTabs )
        {
        return;
        }

    TInt tabCount = TabCount();

    for ( TInt ii = 0; ii < tabCount; ii++ )
        {
        // Tell the tabs about the long tab layout
        // for them to be able to layout their content
        // correctly.
        CAknTab* tab = iTabArray->At( ii );
        tab->SetLongTabLayout( iLongTabs );
        }

    SizeChanged();

    if ( iExtension &&
         iExtension->iTabSvgGraphics &&
         iExtension->iTabSvgGraphics->TabGroupBackgroundAvailable() )
        {
        iExtension->iTabBackgroundLayout.iUse = EFalse;

        iExtension->iTabSvgGraphics->DrawTabGroupBackgroundL(
            CAknTabGroupGraphics::ENoDraw,
            iLongTabs,
            iNumberOfTabsShown,
            1,
            NULL,
            iExtension->iTabBackgroundLayout,
            CAknTabGroupGraphics::ENone );

        iExtension->iTabBackgroundLayout.iUse = ETrue;
        SetDecoratorLayout( EFalse );
        }

    LoadTabBitmapsL( iNumberOfTabsShown, iLongTabs );
    }


EXPORT_C void CAknTabGroup::DimTab( TInt aTabId, TBool aDimmed )
    {
    TInt index = Index( aTabId );
    if ( index >= 0 )
        {
        CAknTab* tabToDim = iTabArray->At( index );
        tabToDim->SetDimmed( aDimmed );
        }
    }

EXPORT_C TBool CAknTabGroup::IsTabDimmed( TInt aTabId ) const
    {
    TInt index = Index( aTabId );
    if ( index < 0 )
        {
        return EFalse;
        }
    CAknTab* tabToCheck = iTabArray->At( index );
    return tabToCheck->IsDimmed();
    }

EXPORT_C TInt CAknTabGroup::TabIndexFromId( TInt aTabId ) const
    {
    const TInt numTabs = TabCount();

    for ( TInt ii = 0; ii < numTabs; ii++ )
        {
        if ( aTabId == iTabArray->At(ii)->Id() )
            {
            return ConvertTabIndex( ii );
            }
        }

    return KErrNotFound;
    }

EXPORT_C TInt CAknTabGroup::TabIdFromIndex( TInt aTabIndex ) const
    {
    TInt realIndex = ConvertTabIndex( aTabIndex );
    const TInt numTabs = TabCount();
    if( ( realIndex >= 0 ) && ( realIndex < numTabs ) )
        {
        return iTabArray->At( realIndex )->Id();
        }

    return KErrNotFound;
    }

EXPORT_C TInt CAknTabGroup::TabCount() const
    {
    return iTabArray->Count();
    }


EXPORT_C void CAknTabGroup::SetObserver( MAknTabObserver* aObserver )
    {
    if ( !iTabObserver && iTabArray && TabCount() > 0 && iMirrored )
        {
        //
        // If there isn't observer set but there is tabs already in array
        // then the order of tabs must be changed if layout is mirrored.
        //
        TRAP_IGNORE( ReverseTabOrderL() );
        iTabObserver = aObserver;
        iActiveTab = ConvertTabIndex( iActiveTab );
        SetActiveTabByIndex( ConvertTabIndex( iActiveTab ) );
        }
    else
        {
        iTabObserver = aObserver;
        }
    }

void CAknTabGroup::ReverseTabOrderL()
    {
    if ( !iTabArray )
        {
        return;
        }

    CArrayPtr<CAknTab>* oldArray = iTabArray;
    iTabArray = new(ELeave) CArrayPtrFlat<CAknTab>( KTabArrayGranularity );
    CleanupStack::PushL( oldArray );
    for ( TInt i = 0; i < oldArray->Count(); i++ )
        {
        iTabArray->InsertL( 0, oldArray->At(i) );
        }

    oldArray->Reset();
    CleanupStack::PopAndDestroy( oldArray );
    SizeChanged();
    }


EXPORT_C TSize CAknTabGroup::MinimumSize()
    {
    TAknWindowLineLayout layout;
    CurrentLayout( layout );
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect( ParentRect( iExtension->iNaviArrowsUsed ), layout );
    TRect rect( layoutRect.Rect() );

    return rect.Size();
    }


EXPORT_C TKeyResponse CAknTabGroup::OfferKeyEventL( const TKeyEvent& aKeyEvent,
                                                    TEventCode aType )
    {
    if ( aType != EEventKey )
        {
        return EKeyWasNotConsumed;
        }

    TKeyResponse keyResponse = EKeyWasNotConsumed;

    switch ( aKeyEvent.iCode )
        {
        case EKeyLeftArrow:
            if ( iActiveTab != LeftMostTabIndex() || aKeyEvent.iRepeats == 0 )
                {
                if ( CycleFocus( ELeft,EDrawNow ) )
                    {
                    keyResponse = EKeyWasConsumed;
                    }
                }
            break;

        case EKeyRightArrow:
            if ( iActiveTab != RightMostTabIndex() || aKeyEvent.iRepeats == 0 )
                {
                if ( CycleFocus( ERight,EDrawNow ) )
                    {
                    keyResponse = EKeyWasConsumed;
                    }
                }
            break;

        default:
            break;
        }

    if ( iTabObserver && keyResponse != EKeyWasNotConsumed )
        {
        iTabObserver->TabChangedL( ConvertTabIndex( iActiveTab ) );
        }

    return keyResponse;
    }


EXPORT_C void CAknTabGroup::GetColorUseListL(
    CArrayFix<TCoeColorUse>& aColorUseList ) const
    {
    TCoeColorUse colorUse;
    colorUse.SetLogicalColor( EColorDialogBackground );
    colorUse.SetUse( TCoeColorUse::EBack |
                     TCoeColorUse::ESurrounds |
                     TCoeColorUse::EActive |
                     TCoeColorUse::ENormal |
                     TCoeColorUse::ENeutral );
    aColorUseList.AppendL( colorUse );
    }


EXPORT_C void CAknTabGroup::HandleControlEventL( CCoeControl* aControl,
                                                 TCoeEvent aEventType )
    {
    switch ( aEventType )
        {
        case EEventStateChanged:
            HandleTabStateChanged( aControl );
            break;
        default:
            break;
        }
    }


EXPORT_C void CAknTabGroup::PrepareContext( CWindowGc& /*aGc*/ ) const
    {
    }


EXPORT_C void CAknTabGroup::SizeChanged()
    {
    // In flat statuspane we do things differently because the layout may vary.
    if ( AknStatuspaneUtils::FlatLayoutActive() && !NarrowTabLayout() )
        {
        SizeChangedInFlatLayout();
        }
    if ( NarrowTabLayout() )
        {
        SizeChangedInNarrowLayout();
        }
    else
        {
        SizeChangedInNormalLayout();
        }
    }


// ---------------------------------------------------------------------------
// Handles size change events in normal tab group layout.
// ---------------------------------------------------------------------------
//
void CAknTabGroup::SizeChangedInNormalLayout()
    {
    TRect rect( ParentRect( iExtension->iNaviArrowsUsed ) );

    TInt tabsDrawn = iNumberOfTabsShown;
    TInt numTabs   = TabCount();

    if ( tabsDrawn > numTabs )
        {
        tabsDrawn = numTabs;
        }

    if ( ( iFirstShownTab + iNumberOfTabsShown ) > numTabs )
        {
        iFirstShownTab = 0;
        }

    // set bitmap sizes
    TAknWindowLineLayout defaultLayout;
    CurrentLayout( defaultLayout );
    TAknLayoutRect r;
    r.LayoutRect( rect, defaultLayout );
    TRect tabPaneRect( r.Rect() );
    TSize size( tabPaneRect.Size() );

    for ( TInt i = 0; i < iNumberOfTabsShown; i++ )
        {
        AknIconUtils::SetSize( iTabBitmaps[i], size );
        }

    if ( iExtension->iTabCycleAnimationOngoing )
        {
        TRect emptyRect( 0, 0, 0, 0 );
        for ( TInt j = 0; j < numTabs; j++)
            {
            CAknTab* thisTab = iTabArray->At( j );
            thisTab->SetRect( emptyRect );
            }

        for ( TInt ii = 0; ii < tabsDrawn + 1; ii++ )
            {
            TInt tabIndex =
                iExtension->iTabCycleAnimationDirection == ELeft ? iActiveTab - 1 + ii :
                                                                   iActiveTab - 2 + ii;

            if ( tabIndex >= numTabs ||
                 tabIndex < 0 )
                {
                break;
                }

            CAknTab* thisTab = iTabArray->At( tabIndex );
            thisTab->SetNarrowTabLayout( EFalse ); // set to normal layout mode
            thisTab->SetTotalAmountOfTabs( iNumberOfTabsShown );

            switch ( ii )
                {
                case 0:
                    {
                    if ( iExtension->iTabCycleAnimationDirection == ELeft )
                        {
                        TRect tabRect( iExtension->iTabSvgGraphics->TabRectFromLayout(
                            iExtension->iNextTabBackgroundLayout.iHiddenTabLeft ) );
                        thisTab->SetRect( tabRect );
                        }
                    else
                        {
                        TRect tabRect( iExtension->iTabSvgGraphics->TabRectFromLayout(
                            iExtension->iNextTabBackgroundLayout.iFirstTab ) );
                        thisTab->SetRect( tabRect );
                        }
                    break;
                    }

                case 1:
                    {
                    if ( iExtension->iTabCycleAnimationDirection == ELeft )
                        {
                        TRect tabRect( iExtension->iTabSvgGraphics->TabRectFromLayout(
                            iExtension->iNextTabBackgroundLayout.iFirstTab ) );
                        thisTab->SetRect( tabRect );
                        }
                    else
                        {
                        TRect tabRect( iExtension->iTabSvgGraphics->TabRectFromLayout(
                            iExtension->iNextTabBackgroundLayout.iSecondTab ) );
                        thisTab->SetRect( tabRect );
                        }
                    break;
                    }

                case 2:
                    {
                    if ( iExtension->iTabCycleAnimationDirection == ELeft )
                        {
                        TRect tabRect( iExtension->iTabSvgGraphics->TabRectFromLayout(
                            iExtension->iNextTabBackgroundLayout.iSecondTab ) );
                        thisTab->SetRect( tabRect );
                        }
                    else
                        {
                        TRect tabRect( iExtension->iTabSvgGraphics->TabRectFromLayout(
                            iExtension->iNextTabBackgroundLayout.iThirdTab ) );
                        thisTab->SetRect( tabRect );
                        }
                    break;
                    }

                case 3:
                    {
                    if ( iExtension->iTabCycleAnimationDirection == ELeft )
                        {
                        TRect tabRect( iExtension->iTabSvgGraphics->TabRectFromLayout(
                            iExtension->iNextTabBackgroundLayout.iThirdTab ) );
                        thisTab->SetRect( tabRect );
                        }
                    else
                        {
                        TRect tabRect( iExtension->iTabSvgGraphics->TabRectFromLayout(
                            iExtension->iNextTabBackgroundLayout.iHiddenTabRight ) );
                        thisTab->SetRect( tabRect );
                        }
                    break;
                    }
                }
            }
        }
    else
        {
        for ( TInt ii=0; ii < tabsDrawn; ii++ )
            {
            CAknTab* thisTab = iTabArray->At( ii + iFirstShownTab );
            thisTab->SetNarrowTabLayout( EFalse ); // set to normal layout mode
            thisTab->SetTotalAmountOfTabs( iNumberOfTabsShown );

            TAknLayoutRect tabLayoutRect;

            switch ( iNumberOfTabsShown )
                {
                case 1:
                    {
                    thisTab->SetRect( tabPaneRect );
                    break;
                    }

                case 2:
                    {
                    if ( iLongTabs )
                        {
                        tabLayoutRect.LayoutRect(
                            tabPaneRect,
                            AknLayoutScalable_Avkon::tabs_2_long_active_pane( ii ) );
                        thisTab->SetRect( tabLayoutRect.Rect() );
                        }
                    else
                        {
                        tabLayoutRect.LayoutRect(
                            tabPaneRect,
                            AknLayoutScalable_Avkon::tabs_2_active_pane( ii ) );
                        thisTab->SetRect( tabLayoutRect.Rect() );
                        }

                    break;
                    }

                case 3:
                    {
                    if ( iLongTabs )
                        {
                        tabLayoutRect.LayoutRect(
                            tabPaneRect,
                            AknLayoutScalable_Avkon::tabs_3_long_active_pane( ii ) );
                        thisTab->SetRect( tabLayoutRect.Rect() );
                        }
                    else
                        {
                        tabLayoutRect.LayoutRect(
                            tabPaneRect,
                            AknLayoutScalable_Avkon::tabs_3_active_pane( ii ) );
                        thisTab->SetRect( tabLayoutRect.Rect() );
                        }

                    break;
                    }

                case 4:
                    {
                    tabLayoutRect.LayoutRect(
                        tabPaneRect,
                        AknLayoutScalable_Avkon::tabs_4_active_pane( ii ) );
                    thisTab->SetRect( tabLayoutRect.Rect() );
                    break;
                    }
                }
            }
        }
    }


// ---------------------------------------------------------------------------
// Handles size change events in narrow tab group layout.
// ---------------------------------------------------------------------------
//
void CAknTabGroup::SizeChangedInNarrowLayout()
    {
    TRect rect( ParentRect( iExtension->iNaviArrowsUsed ) );

    TRect containerNarrowRect(
        CAknNavigationDecorator::DecoratedControlNarrowRect(
            CAknNavigationDecorator::ETabGroup ) );

    TInt tabsDrawn = iNumberOfTabsShown;
    TInt numTabs   = TabCount();

    if ( tabsDrawn > numTabs )
        {
        tabsDrawn = numTabs;
        }

    if ( ( iFirstShownTab + iNumberOfTabsShown ) > numTabs )
        {
        iFirstShownTab = 0;
        }

    // set bitmap sizes
    TAknWindowLineLayout defaultLayout;
    CurrentLayout( defaultLayout );
    TAknLayoutRect r;
    r.LayoutRect( rect, defaultLayout );
    TRect tabPaneRect( r.Rect() );
    TSize size( tabPaneRect.Size() );

    for ( TInt i = 0; i < iNumberOfTabsShown; i++ )
        {
        AknIconUtils::SetSize( iTabBitmaps[i], size );
        }

    for ( TInt ii = 0; ii < tabsDrawn; ii++ )
        {
        CAknTab* thisTab = iTabArray->At( ii + iFirstShownTab );
        CAknTab::TAknTabDataType type = thisTab->TabType();
        thisTab->SetNarrowTabLayout( ETrue ); // set to narrow layout mode
        thisTab->SetTotalAmountOfTabs( iNumberOfTabsShown );

        // In flat statuspane we do things differently because the layout may vary.
        if ( AknStatuspaneUtils::FlatLayoutActive() && NarrowTabLayout() )
            {
            // only active tab shows content in narrow layout
            if ( thisTab->Active() || iNumberOfTabsShown == 1 )
                {
                CAknTabGroupGraphics::SAknTabLayout activeTabLayout;
                TInt positionActive = iActiveTab - iFirstShownTab;

                if ( positionActive == 0 )
                    {
                    activeTabLayout = iExtension->iTabBackgroundLayout.iFirstTab;
                    }
                else if ( positionActive == 1 )
                    {
                    activeTabLayout = iExtension->iTabBackgroundLayout.iSecondTab;
                    }
                else if ( positionActive == 2 )
                    {
                    activeTabLayout = iExtension->iTabBackgroundLayout.iThirdTab;
                    }
                else if ( positionActive == 3 )
                    {
                    activeTabLayout = iExtension->iTabBackgroundLayout.iFourthTab;
                    }

                TRect parentRect( activeTabLayout.iLeft );
                parentRect.BoundingRect( activeTabLayout.iMiddle );
                parentRect.BoundingRect( activeTabLayout.iRight );

                if ( iNumberOfTabsShown == 1 )
                    {
                    thisTab->SetRect( containerNarrowRect );
                    }
                else
                    {
                    thisTab->SetRect( parentRect );
                    }
                }
            else
                {
                thisTab->SetSize( TSize( 0, 0 ) );
                }

            continue;
            }
        }
    }


// ---------------------------------------------------------------------------
// Handles size change events in flat status pane layout.
// ---------------------------------------------------------------------------
//
void CAknTabGroup::SizeChangedInFlatLayout()
    {
    TRect rect( ParentRect( iExtension->iNaviArrowsUsed ) );

    TRect containerNarrowRect(
        CAknNavigationDecorator::DecoratedControlRect(
            CAknNavigationDecorator::ETabGroup,
            iExtension->iNaviArrowsUsed ) );

    TInt tabsDrawn = iNumberOfTabsShown;
    TInt numTabs   = TabCount();

    if ( tabsDrawn > numTabs )
        {
        tabsDrawn = numTabs;
        }

    if ( ( iFirstShownTab + iNumberOfTabsShown ) > numTabs )
        {
        iFirstShownTab = 0;
        }

    // set bitmap sizes
    TAknWindowLineLayout defaultLayout;
    CurrentLayout( defaultLayout );
    TAknLayoutRect r;
    r.LayoutRect( containerNarrowRect, defaultLayout );
    TRect tabPaneRect( r.Rect() );
    TSize size( tabPaneRect.Size() );

    for ( TInt i = 0; i < iNumberOfTabsShown; i++ )
        {
        AknIconUtils::SetSize( iTabBitmaps[i], size );
        }

    for ( TInt ii = 0; ii < tabsDrawn; ii++ )
        {
        CAknTab* thisTab = iTabArray->At( ii + iFirstShownTab );
        CAknTab::TAknTabDataType type = thisTab->TabType();
        thisTab->SetNarrowTabLayout( ETrue ); // set to narrow layout mode
        thisTab->SetTotalAmountOfTabs( iNumberOfTabsShown );

        if ( AknStatuspaneUtils::FlatLayoutActive() )
            {
            CAknTabGroupGraphics::SAknTabLayout activeTabLayout;
            TInt positionActive = iActiveTab - iFirstShownTab;

            if ( positionActive == 0 )
                {
                activeTabLayout = iExtension->iTabBackgroundLayout.iFirstTab;
                }
            else if ( positionActive == 1 )
                {
                activeTabLayout = iExtension->iTabBackgroundLayout.iSecondTab;
                }
            else if ( positionActive == 2 )
                {
                activeTabLayout = iExtension->iTabBackgroundLayout.iThirdTab;
                }
            else if ( positionActive == 3 )
                {
                activeTabLayout = iExtension->iTabBackgroundLayout.iFourthTab;
                }

            TRect parentRect( activeTabLayout.iLeft );
            parentRect.BoundingRect( activeTabLayout.iMiddle );
            parentRect.BoundingRect( activeTabLayout.iRight );

            if ( iNumberOfTabsShown == 1 )
                {
                thisTab->SetRect( containerNarrowRect );
                }
            else
                {
                thisTab->SetRect( parentRect );
                }
            }
        }
    }


// ---------------------------------------------------------------------------
// Returns the amount of component controls.
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CAknTabGroup::CountComponentControls() const
    {
    TInt count( 0 );

    // Check if tabs are supposed to be visible in current layout.
    if ( !TabsVisibleInCurrentLayout() ||
         iActiveTab < 0 )
        {
        count = 0;
        }
    else
        {
        TInt numTabs = TabCount();
        if ( iLongTabs && iActiveTab >= 0 )
            {
            // In long tab layout only one tab is drawn at a time.
            count = 1;
            }
        else if ( numTabs < iNumberOfTabsShown ||
                  iExtension->iTabCycleAnimationOngoing )
            {
            // It's required that all tabs can be drawn during
            // the tab cycle animation, so return the
            // entire amount of tabs.
            count = numTabs;
            }
        else
            {
            // Else return amount of the displayed tabs.
            count = iNumberOfTabsShown;
            }
        }

    return count;
    }


// ---------------------------------------------------------------------------
// Gets a component control (tab control) by the control index.
// ---------------------------------------------------------------------------
//
EXPORT_C CCoeControl* CAknTabGroup::ComponentControl( TInt aIndex ) const
    {
    CCoeControl* control = NULL;

    if ( iLongTabs )
        {
        control = iTabArray->At( iActiveTab );
        }
    else
        {
        TInt index( aIndex );
        if ( !iExtension->iTabCycleAnimationOngoing )
            {
            index += iFirstShownTab;
            }
        control = iTabArray->At( index );
        }

    return control;
    }

EXPORT_C void CAknTabGroup::FocusChanged( TDrawNow aDrawNow )
    {
    if ( iActiveTab >= 0 )
        {
        iTabArray->At( iActiveTab )->SetFocus( IsFocused(), aDrawNow );
        }
    }


// ---------------------------------------------------------------------------
// Converts a mirrored tab index to it's non-mirrored index.
// ---------------------------------------------------------------------------
//
TInt CAknTabGroup::ConvertTabIndex( TInt aIndex ) const
    {
    if ( iMirrored && iTabObserver && aIndex >= 0 )
        {
        return TabCount() - 1 - aIndex;
        }

    return aIndex;
    }


// ---------------------------------------------------------------------------
// Draws the tab group background graphics.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknTabGroup::Draw( const TRect& /*aRect*/ ) const
    {
    TRect rect( ParentRect( iExtension->iNaviArrowsUsed ) );

    // Are tabs supposed to be visible in current layout.
    if ( !TabsVisibleInCurrentLayout() )
        {
        return;  // No tabs shown
        }

    if ( iActiveTab < 0 || iNumberOfTabsShown == 1 )
        {
        return;
        }

    TInt bitmapNo = 0;
    TInt positionActive = iActiveTab - iFirstShownTab;

    // Find out a correct background bitmap for tabs
    if ( iNumberOfTabsShown == 2 )
        if ( iLongTabs )
            {
            bitmapNo = positionActive + KTabIndexOfFirstTabBitmapInTwoLongTabsSet;
            }
        else
            {
            bitmapNo = positionActive + KTabIndexOfFirstTabBitmapInTwoTabsSet;
            }
    if ( iNumberOfTabsShown == 3 )
        if ( iLongTabs )
            {
            bitmapNo = positionActive + KTabIndexOfFirstTabBitmapInThreeLongTabsSet;
            }
        else
            {
            bitmapNo = positionActive + KTabIndexOfFirstTabBitmapInThreeTabsSet;
            }
    if ( iNumberOfTabsShown == 4 )
        {
        bitmapNo = positionActive + KTabIndexOfFirstTabBitmapInFourTabsSet;
        }

    CWindowGc& gc = SystemGc();

    if (iExtension && iExtension->iTabSvgGraphics
            && iExtension->iTabSvgGraphics->TabGroupBackgroundAvailable())
        {

        if (iExtension->iNarrowTabLayout)
            {
            iExtension->iTabSvgGraphics->DrawTabGroupNarrowBackgroundL(
                    CAknTabGroupGraphics::ENormal, iLongTabs,
                    iNumberOfTabsShown, positionActive + 1, &gc,
                    iExtension->iTabBackgroundLayout);

            iExtension->iTabSvgGraphics->DrawTabGroupNarrowBackgroundL(
                    CAknTabGroupGraphics::EMaskOnly, iLongTabs,
                    iNumberOfTabsShown, positionActive + 1, &gc,
                    iExtension->iTabBackgroundLayout);
            }
        else
            {
            CAknTabGroupGraphics::TTabAnimationType animation(
                    CAknTabGroupGraphics::ENoAnimation);
            TBool animationOngoing( iExtension->iTabCycleAnimationOngoing );
            
            if ( animationOngoing )
                {
                animation
                        = iExtension->iTabCycleAnimationDirection == ELeft
                                                                           ? CAknTabGroupGraphics::ECycleToLeft
                                                                              : CAknTabGroupGraphics::ECycleToRight;
                }
            iExtension->iTabSvgGraphics->DrawTabGroupBackgroundL(
                    CAknTabGroupGraphics::ENormal, iLongTabs,
                    iNumberOfTabsShown, positionActive + 1, &gc,
                    animationOngoing ? iExtension->iNextTabBackgroundLayout
                                       : iExtension->iTabBackgroundLayout,
                    iExtension->iTabsHidden, animation);

            iExtension->iTabSvgGraphics->DrawTabGroupBackgroundL(
                    CAknTabGroupGraphics::EMaskOnly,
                    iLongTabs,
                    iNumberOfTabsShown,
                    positionActive + 1,
                    &gc,
                    animationOngoing ? iExtension->iNextTabBackgroundLayout
                                       : iExtension->iTabBackgroundLayout,
                    iExtension->iTabsHidden, animation);
            }
        }
    else
        {
        // Old legacy draw code
        if (iTabBitmaps[bitmapNo] && iTabMaskBitmaps[bitmapNo])
            {
            gc.BitBltMasked(rect.iTl, iTabBitmaps[bitmapNo], rect,
                    iTabMaskBitmaps[bitmapNo], ETrue);
            }
        }
    }


// ---------------------------------------------------------------------------
// Handles the pointer events that happen inside tab group control.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknTabGroup::HandlePointerEventL(
    const TPointerEvent& aPointerEvent )
    {
    if ( AknLayoutUtils::PenEnabled() && iNumberOfTabsShown > 0 )
        {
        TInt newTab = -1;

        // If the tab background graphics are not drawn, then we can't
        // use it to calculate tab rects and use only the x-value of
        // the pointer event position.
        TBool tabBackgroundUsed( iTabFixedWidth != KTabWidthWithOneTab );

        if ( tabBackgroundUsed )
            {
            CAknTabGroupGraphics::SAknTabGroupBackgroundLayout* layout =
                &iExtension->iTabBackgroundLayout;

            CAknTabGroupGraphics::SAknTabLayout* tabLayout[KMaxNumberOfVisibleTabs];
            Mem::FillZ( tabLayout, sizeof( TUint ) * KMaxNumberOfVisibleTabs );

            // Sort the layout array into right order. Tabs need to be tested
            // according to their "z-order" so that the currently active tab
            // is tested last.

            TInt currentTab = iActiveTab - iFirstShownTab;

            switch ( iNumberOfTabsShown )
                {
                case 1:
                    {
                    tabLayout[0] = &layout->iFirstTab;
                    break;
                    }

                case 2:
                    {
                    if ( currentTab == 0 )
                        {
                        tabLayout[0] = &layout->iSecondTab;
                        tabLayout[1] = &layout->iFirstTab;
                        }
                    else
                        {
                        tabLayout[0] = &layout->iFirstTab;
                        tabLayout[1] = &layout->iSecondTab;
                        }
                    break;
                    }

                case 3:
                    {
                    switch ( currentTab )
                        {
                        case 0:
                            tabLayout[0] = &layout->iThirdTab;
                            tabLayout[1] = &layout->iSecondTab;
                            tabLayout[2] = &layout->iFirstTab;
                            break;

                        case 1:
                            tabLayout[0] = &layout->iThirdTab;
                            tabLayout[1] = &layout->iFirstTab;
                            tabLayout[2] = &layout->iSecondTab;
                            break;

                        default:
                            tabLayout[0] = &layout->iFirstTab;
                            tabLayout[1] = &layout->iSecondTab;
                            tabLayout[2] = &layout->iThirdTab;
                        }
                    break;
                    }

                case 4:
                    {
                    if ( NarrowTabLayout() )
                        {
                        switch ( currentTab )
                            {
                            case 0:
                                tabLayout[0] = &layout->iFourthTab;
                                tabLayout[1] = &layout->iThirdTab;
                                tabLayout[2] = &layout->iSecondTab;
                                tabLayout[3] = &layout->iFirstTab;
                                break;

                            case 1:
                                tabLayout[0] = &layout->iFourthTab;
                                tabLayout[1] = &layout->iThirdTab;
                                tabLayout[2] = &layout->iFirstTab;
                                tabLayout[3] = &layout->iSecondTab;
                                break;

                            case 2:
                                tabLayout[0] = &layout->iFourthTab;
                                tabLayout[1] = &layout->iFirstTab;
                                tabLayout[2] = &layout->iSecondTab;
                                tabLayout[3] = &layout->iThirdTab;
                                break;

                            default:
                                tabLayout[0] = &layout->iFirstTab;
                                tabLayout[1] = &layout->iSecondTab;
                                tabLayout[2] = &layout->iThirdTab;
                                tabLayout[3] = &layout->iFourthTab;
                            }
                        }
                    else
                        {
                        switch ( currentTab )
                            {
                            case 0:
                                tabLayout[0] = &layout->iFourthTab;
                                tabLayout[1] = &layout->iThirdTab;
                                tabLayout[2] = &layout->iSecondTab;
                                tabLayout[3] = &layout->iFirstTab;
                                break;

                            case 1:
                                tabLayout[0] = &layout->iFourthTab;
                                tabLayout[1] = &layout->iThirdTab;
                                tabLayout[2] = &layout->iFirstTab;
                                tabLayout[3] = &layout->iSecondTab;
                                break;

                            case 2:
                                tabLayout[0] = &layout->iFourthTab;
                                tabLayout[1] = &layout->iSecondTab;
                                tabLayout[2] = &layout->iFirstTab;
                                tabLayout[3] = &layout->iThirdTab;
                                break;

                            default:
                                tabLayout[0] = &layout->iThirdTab;
                                tabLayout[1] = &layout->iSecondTab;
                                tabLayout[2] = &layout->iFirstTab;
                                tabLayout[3] = &layout->iFourthTab;
                            }
                        }
                    break;
                    }

                default:
                    {
                    User::Leave( KErrArgument );
                    }
                }

            // Loop through the layout array & pick the last suitable tab.
            TRect* rect;

            for ( TInt tab = 0; tab < iNumberOfTabsShown; ++tab )
                {
                rect = &tabLayout[tab]->iLeft;

                for ( TInt part = CAknTabGroupGraphics::ELeft;
                      part <= CAknTabGroupGraphics::ERight;
                      ++part )
                    {
                    if ( rect->Contains( aPointerEvent.iPosition ) )
                        {
                        if ( iExtension->iTabSvgGraphics->TabClickedL( 
                                part, *rect, aPointerEvent.iPosition,
                                tab == KMaxNumberOfVisibleTabs - 1 ) )
                            {
                            if ( tabLayout[tab] == &layout->iFirstTab )
                                {
                                newTab = iFirstShownTab;
                                }
                            else if ( tabLayout[tab] == &layout->iSecondTab )
                                {
                                newTab = iFirstShownTab + 1;
                                }
                            else if ( tabLayout[tab] == &layout->iThirdTab )
                                {
                                newTab = iFirstShownTab + 2;
                                }
                            else
                                {
                                newTab = iFirstShownTab + 3;
                                }
                            break;
                            }
                        }

                    // advance pointer to the next tab component
                    if ( part < CAknTabGroupGraphics::ERight )
                        {
                        rect++;
                        }
                    }
                }
            }

        if ( aPointerEvent.iType == TPointerEvent::EButton1Down )
            {
            if( newTab> -1 )
                {
                MTouchFeedback* feedback = MTouchFeedback::Instance();

                // Feedback is given only if new tab wasn't already active
                // Use two convertTabIndex to cancel the mirror effects, because the newTab is always the phsical index.
                TBool isActiveTab = iTabArray->At( ConvertTabIndex( ConvertTabIndex( newTab ) ) )->Active();
                TTouchFeedbackType type = static_cast<TTouchFeedbackType>(ETouchFeedbackAudio | ETouchFeedbackVibra);
                if ( feedback && !isActiveTab )
                    {
                    feedback->InstantFeedback( this,
                        ETouchFeedbackBasic, 
                        type,
                        aPointerEvent );
                    }
                }
            if ( !tabBackgroundUsed )
                {
                // In one tab layout handle the navigation always by
                // pointer position.
                newTab = iActiveTab;
                }
            iExtension->iPointerDownTab       = newTab;
            iExtension->iPointerDownXPosition = aPointerEvent.iPosition.iX;
            return;
            }
        else if ( aPointerEvent.iType == TPointerEvent::EButton1Up )
            {
            if( newTab> -1 )
                {
                MTouchFeedback* feedback = MTouchFeedback::Instance();

                // Feedback is given only if new tab wasn't already active
                // Use two convertTabIndex to cancel the mirror effects, because the newTab is always the phsical index.
                TBool isActiveTab = iTabArray->At( ConvertTabIndex( ConvertTabIndex( newTab ) ) )->Active();
                if ( feedback && !isActiveTab )
                    {
                    feedback->InstantFeedback( this,
                        ETouchFeedbackBasic, 
                        ETouchFeedbackVibra,
                        aPointerEvent );
                    }
                }
            if ( !tabBackgroundUsed )
                {
                // In one tab layout handle the navigation always by
                // pointer position.
                newTab = -1;
                }

            // if the button up event occurs ouside tabgroup, ignore it.
            if ( !Rect().Contains( aPointerEvent.iPosition ) )
                {
                iExtension->iPointerDownTab       = -1;
                iExtension->iPointerDownXPosition = -1;
                return ;
                }

            if ( newTab != iActiveTab &&
                 newTab > -1 &&
                 newTab == iExtension->iPointerDownTab &&
                 iNumberOfTabsShown > 1 )
                {
                if ( iTabObserver )
                    {
                    TDirection direction = newTab > iActiveTab ? ERight : ELeft;

                    CancelTabAnimationEventTimer();

                    StartCycleAnimationL( direction, newTab );

                    SetActiveTabByIndex( ConvertTabIndex( newTab ) );

                    iTabObserver->TabChangedL( ConvertTabIndex( newTab ) );
                    }

                else
                    {
                    // Kludge: if there is no tab observer, we need to
                    // generate a keyevent to the application so it knows
                    // to activate the correct view.
                    //
                    // The real fix would be to update applications to
                    // implement MAknTabObserver::TabChangedL and to
                    // activate the correct view there.
                    TInt tabsToSkip = newTab - iActiveTab;
                    TKeyEvent code;
                    code.iCode = EKeyRightArrow;
                    code.iModifiers = iEikonEnv->WsSession().GetModifierState();
                    code.iRepeats = 0; // some applications are ignoring repeated events
                    if ( tabsToSkip < 0 )
                        {
                        code.iCode = EKeyLeftArrow;
                        tabsToSkip = -tabsToSkip;
                        }

                    for ( TInt i = 0; i < tabsToSkip; i++ )
                        {
                        iEikonEnv->SimulateKeyEventL( code, EEventKey );
                        }
                    }
                }
            else
                {
                if ( newTab != iExtension->iPointerDownTab && iExtension->iPointerDownTab > -1 )
                    {
                    if ( newTab == -1 )
                        {
                        if ( iExtension->iPointerDownXPosition + KDragNavigationTolerance <
                                 aPointerEvent.iPosition.iX )
                            {
                            newTab = iExtension->iPointerDownTab + 1;
                            }
                        else if ( iExtension->iPointerDownXPosition - KDragNavigationTolerance >
                                      aPointerEvent.iPosition.iX )
                            {
                            newTab = iExtension->iPointerDownTab - 1;
                            }
                        else
                            {
                            newTab = iExtension->iPointerDownTab;
                            }
                        }

                    if ( iExtension->iPointerDownTab < newTab &&
                         iActiveTab > LeftMostTabIndex() )
                        {
                        if ( iTabObserver )
                            {
                            CycleFocus( ELeft, EDrawNow );
                            iTabObserver->TabChangedL( ConvertTabIndex( iActiveTab ) );
                            }
                        else
                            {
                            // Kludge: if there is no tab observer generate a keyevent to
                            // instruct the application to change the view.
                            TKeyEvent code;
                            code.iCode = EKeyLeftArrow;
                            iEikonEnv->SimulateKeyEventL( code, EEventKey );
                            }
                        }
                    else if ( iExtension->iPointerDownTab > newTab &&
                              iActiveTab < RightMostTabIndex() )
                        {
                        if ( iTabObserver )
                            {
                            CycleFocus( ERight, EDrawNow );
                            iTabObserver->TabChangedL( ConvertTabIndex( iActiveTab ) );
                            }
                        else
                            {
                            // Kludge: if there is no tab observer generate a keyevent to
                            // instruct the application to change the view.
                            TKeyEvent code;
                            code.iCode = EKeyRightArrow;
                            iEikonEnv->SimulateKeyEventL( code, EEventKey );
                            }
                        }
                    }
                }

            iExtension->iPointerDownTab       = -1;
            iExtension->iPointerDownXPosition = -1;
            }
        }
    }


EXPORT_C void* CAknTabGroup::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }


// ---------------------------------------------------------------------------
// CAknTabGroup::SetTabMultiColorMode
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknTabGroup::SetTabMultiColorMode( TInt aTabId,
                                                  TBool aMultiColor )
    {
    TInt tabIndex = ConvertTabIndex( TabIndexFromId( aTabId ) );
    if ( tabIndex >= 0 && tabIndex < TabCount() )
        {
        iTabArray->At( tabIndex )->SetMultiColorMode( aMultiColor );
        }
    }


TBool CAknTabGroup::CycleFocus( TDirection aDirection, TDrawNow /*aDrawNow*/ )
    {
    if ( iActiveTab < 0 )
        {
        return EFalse;
        }

    if ( AknStatuspaneUtils::FlatLayoutActive() )
        {
        SetDecoratorLayout( EFalse );
        }
     else
        {
        CancelTabAnimationEventTimer();
        }

    TInt numTabs = TabCount();

    if ( ( iActiveTab <= 0 ) && ( aDirection==ELeft ) )
        {
        TInt event = MAknNavigationObserver::ENaviEventAlreadyLeftmostItem;
        TRAP_IGNORE( ReportEventL(
                static_cast<MCoeControlObserver::TCoeEvent>( event ) ) );
        return EFalse;
        }
    else if ( ( iActiveTab >= ( numTabs - 1 ) ) && ( aDirection==ERight ) )
        {
        TInt event = MAknNavigationObserver::ENaviEventAlreadyRightmostItem;
        TRAP_IGNORE( ReportEventL(
                static_cast<MCoeControlObserver::TCoeEvent>( event ) ) );
        return EFalse;
        }

    TInt tabIndex = ( aDirection == ERight ) ? iActiveTab + 1 : iActiveTab - 1;

    CAknTab* thisTab = (*iTabArray)[tabIndex];

    // This starts the animation only if required.
    TRAP_IGNORE( StartCycleAnimationL( aDirection, tabIndex ) );

    (*iTabArray)[iActiveTab]->SetFocus( EFalse, ENoDrawNow );
    thisTab->SetFocus( ETrue, ENoDrawNow );

    SetActiveTabByIndex( ConvertTabIndex( tabIndex ) );

    return ETrue;
    }


void CAknTabGroup::HandleTabStateChanged( CCoeControl* aControl )
    {
    const TInt numTabs = TabCount();

    if ( numTabs > 1 )
        {
        CAknTab* newTab = static_cast<CAknTab*>( aControl );
        CArrayPtr<CAknTab>& tabArray = *iTabArray;

        TInt ii = 0;
        for( ; ii < numTabs; ii++ )
            {
            if( tabArray[ii] == newTab )
                {
                break;
                }
            }

        tabArray[iActiveTab]->SetFocus( EFalse, EDrawNow );
        SetActiveTabByIndex( ConvertTabIndex( ii ) );
        }
    else
        {
        ReportNavigationEvent();
        }
    }


TInt CAknTabGroup::Index( TInt aTabId ) const
    {
    const TInt numTabs = iTabArray->Count();

    for (TInt ii = 0; ii < numTabs; ii++ )
        {
        CAknTab* thisTab=iTabArray->At(ii);
        if ( thisTab->Id() == aTabId )
            {
            return ii;
            }
        }
    return KErrNotFound;
    }


// --------------------------------------------------------------------------
// Returns the index of the leftmost tab in the tab group.
// --------------------------------------------------------------------------
//
TInt CAknTabGroup::LeftMostTabIndex() const
    {
    TInt index = 0;
    const TInt numTabs = TabCount();

    while ( iTabArray->At( index )->IsDimmed() )
        {
        if ( ++index >= numTabs )
            {
            return KErrNotFound;
            }
        }

    return index;
    }


// --------------------------------------------------------------------------
// Returns the index of the rightmost tab in the tab group.
// --------------------------------------------------------------------------
//
TInt CAknTabGroup::RightMostTabIndex() const
    {
    TInt index = TabCount() - 1;

    if ( index >= 0 )
        {
        while ( iTabArray->At( index )->IsDimmed() )
            {
            if ( --index < 0 )
                {
                return KErrNotFound;
                }
            }
        return index;
        }
    else
        {
        return KErrNotFound;
        }
    }


// ---------------------------------------------------------------------------
// Reports a navigation event to the navi pane decorator.
// ---------------------------------------------------------------------------
//
void CAknTabGroup::ReportNavigationEvent()
    {
    TInt active   = ConvertTabIndex( ActiveTabIndex() );
    TInt tabCount = TabCount();

    TInt event = MAknNavigationObserver::ENaviEventHandleNavigation;

    if ( tabCount <= 1 )
        {
        event = MAknNavigationObserver::ENaviEventOneItemExists;
        }
    else if ( active == 0 )
        {
        event = MAknNavigationObserver::ENaviEventLeftMostItemReached;
        }
    else if ( active >= ( tabCount - 1 ) )
        {
        event = MAknNavigationObserver::ENaviEventRightMostItemReached;
        }

    TRAP_IGNORE( ReportEventL(
        static_cast<MCoeControlObserver::TCoeEvent>( event ) ) );
    }


void CAknTabGroup::LoadTabBitmapsL( TInt aNumberOfTabsShown, TBool aLongTabs )
    {
    TInt i = 0;
    for ( i = 0; i < KTabNumberOfTabBitmaps; i++ )
        {
        delete( iTabBitmaps[i] );
        iTabBitmaps[i] = NULL;
        delete( iTabMaskBitmaps[i] );
        iTabMaskBitmaps[i] = NULL;
        }

    TInt first = KErrNotFound;  // Bitmap indexes to bitmap name array
    TInt last  = KErrNotFound;

    // Figures out what tab background bitmaps are needed.
    if ( aNumberOfTabsShown == 1 )
        {
        return;
        }
    else if ( aNumberOfTabsShown == 2 )
        {
        if ( aLongTabs )
            {
            first = KTabIndexOfFirstTabBitmapInTwoLongTabsSet;
            last = KTabIndexOfLastTabBitmapInTwoLongTabsSet;
            }
        else
            {
            first = KTabIndexOfFirstTabBitmapInTwoTabsSet;
            last = KTabIndexOfLastTabBitmapInTwoTabsSet;
            }
        }
    else if ( aNumberOfTabsShown == 3 )
        {
        if ( aLongTabs )
            {
            first = KTabIndexOfFirstTabBitmapInThreeLongTabsSet;
            last = KTabIndexOfLastTabBitmapInThreeLongTabsSet;
            }
        else
            {
            first = KTabIndexOfFirstTabBitmapInThreeTabsSet;
            last = KTabIndexOfLastTabBitmapInThreeTabsSet;
            }
        }
    else if ( aNumberOfTabsShown == 4 )
        {
        first = KTabIndexOfFirstTabBitmapInFourTabsSet;
        last = KTabIndexOfLastTabBitmapInFourTabsSet;
        }

    if ( first < 0 )
        {
        return;
        }

    TRect rect( ParentRect( iExtension->iNaviArrowsUsed ) );

    if ( iExtension &&
         iExtension->iTabSvgGraphics &&
         iExtension->iTabSvgGraphics->TabGroupBackgroundAvailable() )
        {
        // The background graphics are no more created in this case, instead
        // backgrounds are drawn to a single double buffer
        // (and other double buffer for stacon).
        CAknTabGroupGraphics* tabgraphics = iExtension->iTabSvgGraphics;

        tabgraphics->SetTabGroupBackgroundParent(
            ParentRect( iExtension->iNaviArrowsUsed ) );
        }
    else
        {
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();

        TAknWindowLineLayout layout;
        CurrentLayout( layout );
        TAknLayoutRect layoutRect;
        layoutRect.LayoutRect( rect, layout );
        TSize size ( layoutRect.Rect().Size() );

        // This code is for legacy bitmaps, we should newer go here anymore.
        if ( skin )
            {
            for ( i = first; i <= last; i++ )
                {
                TAknsItemID iid;
                iid.Set( EAknsMajorAvkon, iBitmapNames[i] );
                AknsUtils::CreateIconL( skin,
                                        iid,
                                        iTabBitmaps[i],
                                        iTabMaskBitmaps[i],
                                        KAvkonBitmapFile,
                                        iBitmapNames[i],
                                        iBitmapMaskNames[i] );

                AknIconUtils::SetSize( iTabBitmaps[i],
                                       size,
                                       EAspectRatioNotPreserved );
                }
            }
        else
            {
            TAknLayoutRect layoutRect;
            layoutRect.LayoutRect( rect,
                AknLayoutScalable_Avkon::navi_tabs_2_pane() );

            // Loads only those tab background bitmaps that are needed.
            for ( i = first; i <= last; i++ )
                {
                // Delete (in case skin loading created some bitmaps)
                delete iTabBitmaps[i];
                iTabBitmaps[i] = NULL;
                delete iTabMaskBitmaps[i];
                iTabMaskBitmaps[i] = NULL;

                AknIconUtils::CreateIconL( iTabBitmaps[i],
                                           iTabMaskBitmaps[i],
                                           KAvkonBitmapFile,
                                           iBitmapNames[i],
                                           iBitmapMaskNames[i] );

                // Validate all loaded bitmaps by setting their sizes.
                AknIconUtils::SetSize( iTabBitmaps[i],
                                       layoutRect.Rect().Size(),
                                       EAspectRatioNotPreserved );
                }
            }
        }

    InitTabAnimationL();
    }


void CAknTabGroup::HandleResourceChange( TInt aType )
    {
    // First forward event to child controls,
    // skin change must be forwarded to ALL tabs...
    if( aType == KAknsMessageSkinChange || aType == KEikColorResourceChange )
        {
        TInt numTabs = TabCount();
        for ( TInt i = 0; i < numTabs; i++ )
            {
            iTabArray->At(i)->HandleResourceChange( aType );
            }
        }
    else
        {
        CCoeControl::HandleResourceChange( aType );
        }

    // ...now handle events
    if ( aType == KAknsMessageSkinChange )
        {
        // If this fails, svg tab graphics are not available.
        // Then defaults to bitmaps if possible.
        TRAP_IGNORE( InitTabGroupGraphicsL() );
        TRAP_IGNORE( LoadTabBitmapsL( iNumberOfTabsShown, iLongTabs ) );
        }

    if ( aType == KEikDynamicLayoutVariantSwitch )
        {
        // If double buffers are used in this layout,
        // then initialize its layouts at this point.
        if ( iExtension &&
             iExtension->iTabSvgGraphics &&
             iExtension->iTabSvgGraphics->TabGroupBackgroundAvailable() )
                {
                TRAP_IGNORE( SwitchTabLayoutL() );

                iExtension->iTabSvgGraphics->SetTabGroupBackgroundParent(
                    ParentRect( iExtension->iNaviArrowsUsed ) );

                iExtension->iTabBackgroundLayout.iUse = EFalse;
                TRAP_IGNORE( iExtension->iTabSvgGraphics->DrawTabGroupBackgroundL(
                                CAknTabGroupGraphics::ENoDraw,
                                iLongTabs,
                                iNumberOfTabsShown,
                                1,
                                NULL,
                                iExtension->iTabBackgroundLayout,
                                CAknTabGroupGraphics::ENone ) );
                iExtension->iTabBackgroundLayout.iUse = ETrue;
                SetDecoratorLayout( EFalse );
                }

        if ( iExtension )
            {
            iExtension->iNarrowTabLayout = EFalse;
            }

        if ( !COMPARE_BOOLS( iMirrored, AknLayoutUtils::LayoutMirrored() ) )
            {
            TInt active = ActiveTabIndex();
            TRAPD( err, ReverseTabOrderL() );
            if ( err == KErrNone )
                {
                iMirrored = AknLayoutUtils::LayoutMirrored();
                SetActiveTabByIndex( active );
                }
            }

        SizeChanged();
        TRAP_IGNORE( LoadTabBitmapsL( iNumberOfTabsShown, iLongTabs ) );
        }
    }


TBool CAknTabGroup::TabsVisibleInCurrentLayout() const
    {
    TBool tabsVisible = ETrue;

    // Tabs are not shown in idle layouts and in portrait flat
    // status pane layout because there's not enough space.
    if ( AknStatuspaneUtils::IdleLayoutActive() ||
         ( AknStatuspaneUtils::FlatLayoutActive() &&
           !Layout_Meta_Data::IsLandscapeOrientation() ) )
        {
        tabsVisible = EFalse;  // No tabs shown
        }

    return tabsVisible;
    }


void CAknTabGroup::CurrentLayout( TAknWindowLineLayout& aLayout ) const
    {
    TAknWindowLineLayout layout( AknLayoutScalable_Avkon::navi_tabs_2_pane() );

    if ( iLongTabs )
        {
        switch ( iNumberOfTabsShown )
            {
            case 3:
                {
                layout = AknLayoutScalable_Avkon::navi_tabs_3_long_pane();
                break;
                }
            default:
                {
                layout = AknLayoutScalable_Avkon::navi_tabs_2_long_pane();
                break;
                }
            }
        }
    else
        {
        switch ( iNumberOfTabsShown )
            {
            case 4:
                {
                layout = AknLayoutScalable_Avkon::navi_tabs_4_pane();
                break;
                }
            case 3:
                {
                layout = AknLayoutScalable_Avkon::navi_tabs_3_pane();
                break;
                }
            default:
                {
                break;
                }
            }
        }

    aLayout = layout;
    }


// ---------------------------------------------------------------------------
// Handles navication decorator events scrolling tabs to left/right
// Depending on event
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknTabGroup::HandleNaviDecoratorEventL( TInt aEventID )
    {
    if ( AknLayoutUtils::PenEnabled() )
        {
        switch ( aEventID )
            {
            case MAknNaviDecoratorObserver::EAknNaviDecoratorEventLeftTabArrow:
                {
                if ( iTabObserver )
                    {
                    if ( iActiveTab != LeftMostTabIndex() )
                        {
                        CycleFocus( ELeft, EDrawNow );
                        }
                    iTabObserver->TabChangedL( ConvertTabIndex( iActiveTab ) );
                    }
                else
                    {
                    // Kludge: if there is no tab observer generate a keyevent to
                    // instruct the application to change the view.
                    TKeyEvent code;
                    code.iCode = EKeyLeftArrow;
                    iEikonEnv->SimulateKeyEventL( code, EEventKey );
                    }
                }
                break;

            case MAknNaviDecoratorObserver::EAknNaviDecoratorEventRightTabArrow:
                {
                if ( iTabObserver )
                    {
                    if ( iActiveTab != RightMostTabIndex() )
                        {
                        CycleFocus( ERight, EDrawNow );
                        }
                    iTabObserver->TabChangedL( ConvertTabIndex( iActiveTab ) );
                    }
                else
                    {
                    // Kludge: if there is no tab observer generate a keyevent to
                    // instruct the application to change the view.
                    TKeyEvent code;
                    code.iCode = EKeyRightArrow;
                    iEikonEnv->SimulateKeyEventL( code, EEventKey );
                    }
                }
                break;

            default:
                break;
            }
        }
    }

EXPORT_C void CAknTabGroup::Reserved1()
    {
    }

EXPORT_C void CAknTabGroup::Reserved2()
    {
    }

EXPORT_C void CAknTabGroup::Reserved3()
    {
    }

void CAknTabGroup::InitTabGroupGraphicsL()
    {
    if ( iExtension && iExtension->iTabSvgGraphics )
        {
        delete iExtension->iTabSvgGraphics;
        iExtension->iTabSvgGraphics = NULL;
        iExtension->iTabSvgGraphics = CAknTabGroupGraphics::NewL();
        }
    }


// ---------------------------------------------------------------------------
// Starts the animation timer.
// ---------------------------------------------------------------------------
//
void CAknTabGroup::InitTabAnimationEventTimer()
    {
    TInt delay = 1;
    iExtension->iTabAnimationTimer->Cancel();
    iExtension->iTabAnimationTimer->Start(
        TTimeIntervalMicroSeconds32( delay ),
        TTimeIntervalMicroSeconds32( KAnimationEventInterval ),
        TCallBack( CAknTabGroup::TabAnimationEvent, this ) );
    }


// ---------------------------------------------------------------------------
// Cancels the animation timer.
// ---------------------------------------------------------------------------
//
void CAknTabGroup::CancelTabAnimationEventTimer()
    {
    if ( iExtension &&
         iExtension->iTabAnimationTimer &&
         iExtension->iTabAnimationTimer->IsActive() )
        {
        iExtension->iTabAnimationTimer->Cancel();
        iExtension->iAmountOfDoneAnimationEvents = 0;

        if ( iExtension->iTabAnimationType ==
                 CAknTabGroupExtension::ETabCycleAnimation )
            {
            iExtension->iTabCycleAnimationOngoing = EFalse;

            iExtension->iTabsHidden = CAknTabGroupGraphics::EOnBothSides;
            if ( iFirstShownTab == 0 )
                {
                iExtension->iTabsHidden = CAknTabGroupGraphics::EOnRightSide;
                }
            else if ( iFirstShownTab == TabCount() - iNumberOfTabsShown )
                {
                iExtension->iTabsHidden = CAknTabGroupGraphics::EOnLeftSide;
                }
            }

        iExtension->iTabAnimationType =
            CAknTabGroupExtension::ENoAnimation;
        }
    }

TInt CAknTabGroup::TabAnimationEvent( TAny* aPtr )
    {
    static_cast<CAknTabGroup*>( aPtr )->DoTabAnimationEvent();
    return ETrue;
    }


// ---------------------------------------------------------------------------
// Animation timer callback.
// ---------------------------------------------------------------------------
//
void CAknTabGroup::DoTabAnimationEvent()
    {
    // In this method we calculate the new positions of tabs during
    // the animation cycle.

    // We do this safety check because of possible problems with layout data.
    iExtension->iAmountOfDoneAnimationEvents++;
    if ( iExtension->iAmountOfDoneAnimationEvents > KMaxAmountOfAnimationEvents )
        {
        CancelTabAnimationEventTimer();
        SizeChanged();
        TRAP_IGNORE( InitTabAnimationL() );
        DrawDeferred();
        return;
        }

    TBool firstDone  = EFalse;
    TBool secondDone = EFalse;
    TBool thirdDone  = EFalse;
    TBool fourthDone = EFalse;

    if ( iExtension->iTabAnimationType ==
             CAknTabGroupExtension::ETabCycleAnimation )
        {
        if ( iExtension->iAmountOfDoneAnimationEvents == 1 )
            {
            // Calculate the initial distance to go on the first event.
            iExtension->iTabCycleAnimationDistanceLeft =
                iExtension->iTabBackgroundLayout.iSecondTab.iLeft.iTl.iX -
                iExtension->iTabBackgroundLayout.iFirstTab.iLeft.iTl.iX;
            }

        // Calculate the step size used in this frame, currently
        // using ease-out.
        TInt stepSize = iExtension->iTabCycleAnimationDistanceLeft /
                            KMinimumCycleAnimationStepSize;

        // Sanity check, ensure that animation doesn't move too slow.
        if ( stepSize < KMinimumCycleAnimationStepSize )
            {
            stepSize = KMinimumCycleAnimationStepSize;
            }

        if ( iExtension->iTabCycleAnimationDirection ==
                 CAknTabGroup::ERight )
            {
            // Adjust the step size sign according to the direction
            // we're moving to.
            stepSize = -stepSize;
            }

        // Decrease the distance left by the step size.
        iExtension->iTabCycleAnimationDistanceLeft -= Abs( stepSize );

        // Move the tabs.
        iExtension->iTabSvgGraphics->AdjustTabLayoutRect(
            iExtension->iNextTabBackgroundLayout.iHiddenTabLeft, stepSize, 0 );
        iExtension->iTabSvgGraphics->AdjustTabLayoutRect(
            iExtension->iNextTabBackgroundLayout.iFirstTab, stepSize, 0 );
        iExtension->iTabSvgGraphics->AdjustTabLayoutRect(
            iExtension->iNextTabBackgroundLayout.iSecondTab, stepSize, 0 );
        iExtension->iTabSvgGraphics->AdjustTabLayoutRect(
            iExtension->iNextTabBackgroundLayout.iThirdTab, stepSize, 0 );
        iExtension->iTabSvgGraphics->AdjustTabLayoutRect(
            iExtension->iNextTabBackgroundLayout.iHiddenTabRight, stepSize, 0 );
        }
    else
        {
        // This seems to be quite ok speed for the animation.
        TInt defaultStepSize = Rect().Width() / KLayoutSwitchAnimationSpeed;

        // Sanity check
        if ( defaultStepSize == 0 )
            {
            defaultStepSize = 1;
            }

        // First find out where we are moving, how far is the destination.
        TInt firstTabHorizontalDistanceLeft  =
        iExtension->iNextTabBackgroundLayout.iFirstTab.iLeft.iTl.iX -
                iExtension->iTabBackgroundLayout.iFirstTab.iLeft.iTl.iX;

        TInt secondTabHorizontalDistanceLeft =
        iExtension->iNextTabBackgroundLayout.iSecondTab.iLeft.iTl.iX -
                iExtension->iTabBackgroundLayout.iSecondTab.iLeft.iTl.iX;

        TInt thirdTabHorizontalDistanceLeft  =
        iExtension->iNextTabBackgroundLayout.iThirdTab.iLeft.iTl.iX -
                iExtension->iTabBackgroundLayout.iThirdTab.iLeft.iTl.iX;

        TInt fourthTabHorizontalDistanceLeft =
        iExtension->iNextTabBackgroundLayout.iFourthTab.iLeft.iTl.iX -
                iExtension->iTabBackgroundLayout.iFourthTab.iLeft.iTl.iX;

        TInt firstTabHorizontalDistanceMiddle  =
        iExtension->iNextTabBackgroundLayout.iFirstTab.iMiddle.iTl.iX -
                iExtension->iTabBackgroundLayout.iFirstTab.iMiddle.iTl.iX;

        TInt secondTabHorizontalDistanceMiddle =
        iExtension->iNextTabBackgroundLayout.iSecondTab.iMiddle.iTl.iX -
                iExtension->iTabBackgroundLayout.iSecondTab.iMiddle.iTl.iX;

        TInt thirdTabHorizontalDistanceMiddle  =
        iExtension->iNextTabBackgroundLayout.iThirdTab.iMiddle.iTl.iX -
                iExtension->iTabBackgroundLayout.iThirdTab.iMiddle.iTl.iX;

        TInt fourthTabHorizontalDistanceMiddle =
        iExtension->iNextTabBackgroundLayout.iFourthTab.iMiddle.iTl.iX -
                iExtension->iTabBackgroundLayout.iFourthTab.iMiddle.iTl.iX;

        TInt firstTabHorizontalDistanceRight  =
        iExtension->iNextTabBackgroundLayout.iFirstTab.iRight.iTl.iX -
                iExtension->iTabBackgroundLayout.iFirstTab.iRight.iTl.iX;

        TInt secondTabHorizontalDistanceRight =
        iExtension->iNextTabBackgroundLayout.iSecondTab.iRight.iTl.iX -
                iExtension->iTabBackgroundLayout.iSecondTab.iRight.iTl.iX;

        TInt thirdTabHorizontalDistanceRight  =
        iExtension->iNextTabBackgroundLayout.iThirdTab.iRight.iTl.iX -
                iExtension->iTabBackgroundLayout.iThirdTab.iRight.iTl.iX;

        TInt fourthTabHorizontalDistanceRight =
        iExtension->iNextTabBackgroundLayout.iFourthTab.iRight.iTl.iX -
                iExtension->iTabBackgroundLayout.iFourthTab.iRight.iTl.iX;

        TInt usedStepSizeForFirstTabLeft  = defaultStepSize;
        TInt usedStepSizeForSecondTabLeft = defaultStepSize;
        TInt usedStepSizeForThirdTabLeft  = defaultStepSize;
        TInt usedStepSizeForFourthTabLeft = defaultStepSize;

        TInt usedStepSizeForFirstTabMiddle  = defaultStepSize;
        TInt usedStepSizeForSecondTabMiddle = defaultStepSize;
        TInt usedStepSizeForThirdTabMiddle  = defaultStepSize;
        TInt usedStepSizeForFourthTabMiddle = defaultStepSize;

        TInt usedStepSizeForFirstTabRight  = defaultStepSize;
        TInt usedStepSizeForSecondTabRight = defaultStepSize;
        TInt usedStepSizeForThirdTabRight  = defaultStepSize;
        TInt usedStepSizeForFourthTabRight = defaultStepSize;


        // If we are close to end, then adjust the step size. Also if we are moving to normal layout
        // from narrow, do it with one big step.
        if ( Abs( firstTabHorizontalDistanceLeft ) < Abs( usedStepSizeForFirstTabLeft ) ||
             !NarrowTabLayoutNext() )
            {
            usedStepSizeForFirstTabLeft = Abs( firstTabHorizontalDistanceLeft );
            }
        if ( Abs( firstTabHorizontalDistanceMiddle ) < Abs( usedStepSizeForFirstTabMiddle ) ||
             !NarrowTabLayoutNext() )
            {
            usedStepSizeForFirstTabMiddle = Abs( firstTabHorizontalDistanceMiddle );
            }
        if ( Abs( firstTabHorizontalDistanceRight ) < Abs( usedStepSizeForFirstTabRight ) ||
             !NarrowTabLayoutNext() )
            {
            usedStepSizeForFirstTabRight = Abs( firstTabHorizontalDistanceRight );
            }

        if ( Abs( secondTabHorizontalDistanceLeft ) < Abs( usedStepSizeForSecondTabLeft ) ||
             !NarrowTabLayoutNext() )
            {
            usedStepSizeForSecondTabLeft = Abs( secondTabHorizontalDistanceLeft );
            }
        if ( Abs( secondTabHorizontalDistanceMiddle ) < Abs( usedStepSizeForSecondTabMiddle ) ||
             !NarrowTabLayoutNext() )
            {
            usedStepSizeForSecondTabMiddle = Abs( secondTabHorizontalDistanceMiddle );
            }
        if ( Abs( secondTabHorizontalDistanceRight ) < Abs( usedStepSizeForSecondTabRight ) ||
             !NarrowTabLayoutNext() )
            {
            usedStepSizeForSecondTabRight = Abs( secondTabHorizontalDistanceRight );
            }

        if ( Abs( thirdTabHorizontalDistanceLeft ) < Abs( usedStepSizeForThirdTabLeft ) ||
             !NarrowTabLayoutNext() )
            {
            usedStepSizeForThirdTabLeft = Abs(thirdTabHorizontalDistanceLeft);
            }
        if ( Abs( thirdTabHorizontalDistanceMiddle ) < Abs( usedStepSizeForThirdTabMiddle ) ||
             !NarrowTabLayoutNext() )
            {
            usedStepSizeForThirdTabMiddle = Abs(thirdTabHorizontalDistanceMiddle);
            }
        if ( Abs( thirdTabHorizontalDistanceRight ) < Abs( usedStepSizeForThirdTabRight) ||
             !NarrowTabLayoutNext() )
            {
            usedStepSizeForThirdTabRight = Abs(thirdTabHorizontalDistanceRight);
            }

        if ( Abs( fourthTabHorizontalDistanceLeft ) < Abs( usedStepSizeForFourthTabLeft ) ||
             !NarrowTabLayoutNext() )
            {
            usedStepSizeForFourthTabLeft = Abs(fourthTabHorizontalDistanceLeft);
            }
        if ( Abs( fourthTabHorizontalDistanceMiddle ) < Abs( usedStepSizeForFourthTabMiddle ) ||
             !NarrowTabLayoutNext() )
            {
            usedStepSizeForFourthTabMiddle = Abs(fourthTabHorizontalDistanceMiddle);
            }
        if ( Abs( fourthTabHorizontalDistanceRight ) < Abs( usedStepSizeForFourthTabRight ) ||
             !NarrowTabLayoutNext() )
            {
            usedStepSizeForFourthTabRight = Abs(fourthTabHorizontalDistanceRight);
            }


        // First tab
        if ( firstTabHorizontalDistanceLeft < 0 )
            {
            usedStepSizeForFirstTabLeft = -usedStepSizeForFirstTabLeft;
            }

        if ( firstTabHorizontalDistanceMiddle < 0 )
            {
            usedStepSizeForFirstTabMiddle = -usedStepSizeForFirstTabMiddle;
            }

        if ( firstTabHorizontalDistanceRight < 0 )
            {
            usedStepSizeForFirstTabRight = -usedStepSizeForFirstTabRight;
            }

    iExtension->iTabBackgroundLayout.iFirstTab.iLeft.Move( usedStepSizeForFirstTabLeft, 0 );
    iExtension->iTabBackgroundLayout.iFirstTab.iRight.Move( usedStepSizeForFirstTabRight, 0 );

    iExtension->iTabBackgroundLayout.iFirstTab.iMiddle.iTl.iX =
        iExtension->iTabBackgroundLayout.iFirstTab.iLeft.iBr.iX;

    iExtension->iTabBackgroundLayout.iFirstTab.iMiddle.iBr.iX =
        iExtension->iTabBackgroundLayout.iFirstTab.iRight.iTl.iX;

        if ( ( iExtension->iNextTabBackgroundLayout.iFirstTab.iLeft.iTl.iX -
                   iExtension->iTabBackgroundLayout.iFirstTab.iLeft.iTl.iX == 0 ) &&
             ( iExtension->iNextTabBackgroundLayout.iFirstTab.iMiddle.iTl.iX -
                   iExtension->iTabBackgroundLayout.iFirstTab.iMiddle.iTl.iX == 0 ) &&
             ( iExtension->iNextTabBackgroundLayout.iFirstTab.iRight.iTl.iX -
                   iExtension->iTabBackgroundLayout.iFirstTab.iRight.iTl.iX == 0 ) )
            {
            firstDone = ETrue;
            }

        // Second tab
        if ( secondTabHorizontalDistanceLeft < 0 )
            {
            usedStepSizeForSecondTabLeft = -usedStepSizeForSecondTabLeft;
            }
        if ( secondTabHorizontalDistanceMiddle < 0 )
            {
            usedStepSizeForSecondTabMiddle = -usedStepSizeForSecondTabMiddle;
            }
        if ( secondTabHorizontalDistanceRight < 0 )
            {
            usedStepSizeForSecondTabRight = -usedStepSizeForSecondTabRight;
            }

    iExtension->iTabBackgroundLayout.iSecondTab.iLeft.Move(usedStepSizeForSecondTabLeft,0);
    iExtension->iTabBackgroundLayout.iSecondTab.iRight.Move(usedStepSizeForSecondTabRight,0);

    iExtension->iTabBackgroundLayout.iSecondTab.iMiddle.iTl.iX =
        iExtension->iTabBackgroundLayout.iSecondTab.iLeft.iBr.iX;

    iExtension->iTabBackgroundLayout.iSecondTab.iMiddle.iBr.iX =
        iExtension->iTabBackgroundLayout.iSecondTab.iRight.iTl.iX;

        if ( ( iExtension->iNextTabBackgroundLayout.iSecondTab.iLeft.iTl.iX -
                   iExtension->iTabBackgroundLayout.iSecondTab.iLeft.iTl.iX == 0 ) &&
             ( iExtension->iNextTabBackgroundLayout.iSecondTab.iMiddle.iTl.iX -
                   iExtension->iTabBackgroundLayout.iSecondTab.iMiddle.iTl.iX == 0 ) &&
             ( iExtension->iNextTabBackgroundLayout.iSecondTab.iRight.iTl.iX -
                   iExtension->iTabBackgroundLayout.iSecondTab.iRight.iTl.iX == 0 ) )
            {
            secondDone = ETrue;
            }

        // Third tab
        if ( thirdTabHorizontalDistanceLeft < 0 )
            {
            usedStepSizeForThirdTabLeft = -usedStepSizeForThirdTabLeft;
            }
        if ( thirdTabHorizontalDistanceMiddle < 0 )
            {
            usedStepSizeForThirdTabMiddle = -usedStepSizeForThirdTabMiddle;
            }
        if ( thirdTabHorizontalDistanceRight < 0 )
            {
            usedStepSizeForThirdTabRight = -usedStepSizeForThirdTabRight;
            }

    iExtension->iTabBackgroundLayout.iThirdTab.iLeft.Move(usedStepSizeForThirdTabLeft,0);
    iExtension->iTabBackgroundLayout.iThirdTab.iRight.Move(usedStepSizeForThirdTabRight,0);

    iExtension->iTabBackgroundLayout.iThirdTab.iMiddle.iTl.iX =
        iExtension->iTabBackgroundLayout.iThirdTab.iLeft.iBr.iX;

    iExtension->iTabBackgroundLayout.iThirdTab.iMiddle.iBr.iX =
        iExtension->iTabBackgroundLayout.iThirdTab.iRight.iTl.iX;

        if ( ( iExtension->iNextTabBackgroundLayout.iThirdTab.iLeft.iTl.iX -
                   iExtension->iTabBackgroundLayout.iThirdTab.iLeft.iTl.iX == 0 ) &&
             ( iExtension->iNextTabBackgroundLayout.iThirdTab.iMiddle.iTl.iX -
                   iExtension->iTabBackgroundLayout.iThirdTab.iMiddle.iTl.iX == 0 ) &&
             ( iExtension->iNextTabBackgroundLayout.iThirdTab.iRight.iTl.iX -
                   iExtension->iTabBackgroundLayout.iThirdTab.iRight.iTl.iX == 0 ) )
            {
            thirdDone = ETrue;
            }

        // Fourth tab
        if ( fourthTabHorizontalDistanceLeft < 0 )
            {
            usedStepSizeForFourthTabLeft = -usedStepSizeForFourthTabLeft;
            }
        if ( fourthTabHorizontalDistanceMiddle < 0 )
            {
            usedStepSizeForFourthTabMiddle = -usedStepSizeForFourthTabMiddle;
            }
        if ( fourthTabHorizontalDistanceRight < 0 )
            {
            usedStepSizeForFourthTabRight = -usedStepSizeForFourthTabRight;
            }

    iExtension->iTabBackgroundLayout.iFourthTab.iLeft.Move(
        usedStepSizeForFourthTabLeft, 0 );
    iExtension->iTabBackgroundLayout.iFourthTab.iRight.Move(
        usedStepSizeForFourthTabRight, 0 );
    iExtension->iTabBackgroundLayout.iFourthTab.iMiddle.iTl.iX =
        iExtension->iTabBackgroundLayout.iFourthTab.iLeft.iBr.iX;
    iExtension->iTabBackgroundLayout.iFourthTab.iMiddle.iBr.iX =
        iExtension->iTabBackgroundLayout.iFourthTab.iRight.iTl.iX;

        if ( ( iExtension->iNextTabBackgroundLayout.iFourthTab.iLeft.iTl.iX -
                iExtension->iTabBackgroundLayout.iFourthTab.iLeft.iTl.iX == 0 ) &&
             ( iExtension->iNextTabBackgroundLayout.iFourthTab.iMiddle.iTl.iX -
                iExtension->iTabBackgroundLayout.iFourthTab.iMiddle.iTl.iX == 0 ) &&
             ( iExtension->iNextTabBackgroundLayout.iFourthTab.iRight.iTl.iX -
                iExtension->iTabBackgroundLayout.iFourthTab.iRight.iTl.iX == 0 ) )
            {
            fourthDone = ETrue;
            }
        }

   // Then lets adjust the tab content to right places.
   if ( NarrowTabLayoutNext() )
       {
       TBool refreshTabs = iExtension->iNarrowTabLayout;
       iExtension->iNarrowTabLayout = ETrue;
       if ( refreshTabs )
           {
           SizeChanged();
           }
       }
   else
       {
       TBool refreshTabs = !iExtension->iNarrowTabLayout;
       iExtension->iNarrowTabLayout = EFalse;
       if ( refreshTabs )
           {
           SizeChanged();
           }
       }

    // Check if we are done with the animation
    if ( firstDone && secondDone && thirdDone && fourthDone ||
         ( iExtension->iTabAnimationType == CAknTabGroupExtension::ETabCycleAnimation &&
           iExtension->iTabCycleAnimationDistanceLeft <= 0 ) )
        {
        CancelTabAnimationEventTimer(); // done
        SizeChanged();
        }

    // Finally draw the tabs to their new places. Note that drawing must draw
    // tabs little differently in this animated case. See Draw() method.
    TRAP_IGNORE( InitTabAnimationL() );
        
    DrawDeferred();
    }


// ---------------------------------------------------------------------------
// Sets the narrow/normal layout state of the tab group.
// ---------------------------------------------------------------------------
//
void CAknTabGroup::SetNarrowTabLayoutL( TBool aNarrow, TBool aUseAnimation )
    {
    if ( iExtension->iTabCycleAnimationOngoing )
        {
        // Narrow tab layout is not currently supported in touch layouts
        // and this may should not be called during tab cycle animation.
        return;
        }

    if ( !aUseAnimation )
        {
        // Switch the layout directly without using the animation.
        iExtension->iNarrowTabLayout = aNarrow;
        iExtension->iTabAnimationType =
            CAknTabGroupExtension::ENoAnimation;
        }
    else
        {
        iExtension->iTabAnimationType =
            CAknTabGroupExtension::ELayoutSwitchAnimation;
        }

    iExtension->iNarrowTabLayoutNext = aNarrow;

    iExtension->iTabSvgGraphics->SetTabGroupBackgroundParent(
        ParentRect( iExtension->iNaviArrowsUsed ) );

    // Calculate new destination positions for animated tabs.
    TInt positionActive = iActiveTab - iFirstShownTab;
    if ( aNarrow )
        {
        iExtension->iNextTabBackgroundLayout.iUse = EFalse;
        iExtension->iTabSvgGraphics->DrawTabGroupNarrowBackgroundL(
            CAknTabGroupGraphics::ENoDraw,
            iLongTabs,
            iNumberOfTabsShown,
            positionActive + 1,
            NULL,
            iExtension->iNextTabBackgroundLayout );
        iExtension->iNextTabBackgroundLayout.iUse = ETrue;

        if ( !aUseAnimation )
            {
            iExtension->iTabBackgroundLayout.iUse = EFalse;
            iExtension->iTabSvgGraphics->DrawTabGroupNarrowBackgroundL(
                CAknTabGroupGraphics::ENoDraw,
                iLongTabs,
                iNumberOfTabsShown,
                positionActive + 1,
                NULL,
                iExtension->iTabBackgroundLayout );
            iExtension->iTabBackgroundLayout.iUse = ETrue;
            }
        }
    else
        {
        iExtension->iNextTabBackgroundLayout.iUse = EFalse;
        iExtension->iTabSvgGraphics->DrawTabGroupBackgroundL(
            CAknTabGroupGraphics::ENoDraw,
            iLongTabs,
            iNumberOfTabsShown,
            positionActive + 1,
            NULL,
            iExtension->iNextTabBackgroundLayout,
            CAknTabGroupGraphics::ENone );
        iExtension->iNextTabBackgroundLayout.iUse = ETrue;

        iExtension->iTabBackgroundLayout.iUse = EFalse;
        iExtension->iTabSvgGraphics->DrawTabGroupBackgroundL(
            CAknTabGroupGraphics::ENoDraw,
            iLongTabs,
            iNumberOfTabsShown,
            positionActive + 1,
            NULL,
            iExtension->iTabBackgroundLayout,
            CAknTabGroupGraphics::ENone );
        iExtension->iTabBackgroundLayout.iUse = ETrue;
        }

    InitTabAnimationL();

    if ( AknStatuspaneUtils::FlatLayoutActive() )
        {
        InitTabAnimationEventTimer();
        }
    else
        {
        CancelTabAnimationEventTimer();
        }
    }


// ---------------------------------------------------------------------------
// Sets the tab group internal state of the navi arrow visibility.
// ---------------------------------------------------------------------------
//
void CAknTabGroup::SetNaviArrowsVisible( TBool aVisible )
    {
    if ( iExtension )
        {
        iExtension->iNaviArrowsUsed = aVisible;
        }
    }


TBool CAknTabGroup::NarrowTabLayoutNext()
    {
    return iExtension && iExtension->iNarrowTabLayoutNext;
    }

TBool CAknTabGroup::NarrowTabLayout()
    {
    return iExtension && iExtension->iNarrowTabLayout;
    }


// ---------------------------------------------------------------------------
// Sets the layout of the navi decorator to match the current
// tab group layout.
// ---------------------------------------------------------------------------
//
void CAknTabGroup::SetDecoratorLayout( TBool aNarrow )
    {
    CEikStatusPaneBase* statusPane           = CEikStatusPaneBase::Current();
    CAknNavigationControlContainer* naviPane = NULL;
    CAknNavigationDecorator* decorator       = NULL;

    if ( statusPane )
        {
        CCoeControl* control = NULL;
        TRAPD( err, control = statusPane->ControlL(
            TUid::Uid( EEikStatusPaneUidNavi ) ) );

        if ( !err && control )
            {
            // Control cannot be casted directly because someone may have
            // swapped the control. Use this workaround instead.
            control->MopGetObject( naviPane );
            if ( naviPane )
                {
                decorator = naviPane->Top();
                if ( decorator && decorator->DecoratedControl() != this )
                    {
                    decorator = NULL;
                    }
                }
            }
        }

    // Check first that application has not forced any layout mode.
    if ( aNarrow )
        {
        if ( decorator &&
             decorator->NaviControlLayoutMode() ==
                CAknNavigationDecorator::ENaviControlLayoutModeAutomatic )
           {
           decorator->SetNaviControlLayoutStyle(
               CAknNavigationDecorator::ENaviControlLayoutNarrow );
           }
        }
    else
        {
        if ( decorator &&
             decorator->NaviControlLayoutMode() ==
                CAknNavigationDecorator::ENaviControlLayoutModeAutomatic )
           {
           decorator->SetNaviControlLayoutStyle(
            CAknNavigationDecorator::ENaviControlLayoutNormal );
           }
        }

    // Only use tab arrows in non-touch layouts and in the one tab layout.
    TBool naviArrowsShouldBeVisible( iTabFixedWidth == KTabWidthWithOneTab ||
                                     !AknLayoutUtils::PenEnabled() );
    if ( decorator &&
         !COMPARE_BOOLS( decorator->ScrollButtonVisible(), naviArrowsShouldBeVisible ) )
        {
        decorator->MakeScrollButtonVisible( naviArrowsShouldBeVisible );
        }
    else
        {
        if ( iExtension )
            {
            // Ensure that the value here is correct if navi decorator
            // already has it correct.
            iExtension->iNaviArrowsUsed = naviArrowsShouldBeVisible;
            }
        }

    // After this method call decorator will set this class size right by
    // calling us back at CAknTabGroup::SetNarrowTabLayoutL().
    // If decorator does not exist we call ourself SetNarrowTabLayout.
    if ( !decorator )
        {
        TRAP_IGNORE( SetNarrowTabLayoutL( aNarrow ) );
        }
    }


// ---------------------------------------------------------------------------
// Creates if necessary and draws the tab group background double buffer.
// ---------------------------------------------------------------------------
//
void CAknTabGroup::InitTabAnimationL()
    {
    TRect rect( ParentRect( iExtension->iNaviArrowsUsed ) );

    TSize size( rect.iBr.iX, rect.iBr.iY );

    if ( size.iHeight <= 0 || size.iWidth <= 0 )
        {
        size = rect.Size();
        }

    TInt positionActive = iActiveTab - iFirstShownTab;

    TBool penEnabled( AknLayoutUtils::PenEnabled() );

    if ( penEnabled && iTabFixedWidth == KTabWidthWithThreeTabs )
        {
        // It's ensured here that the focused tab background graphic is drawn
        // behind the middle tab in touch layouts when using three tab
        // layout, if the currently active tab is not the leftmost or
        // rightmost tab.
        if ( iActiveTab != RightMostTabIndex() &&
             iActiveTab != LeftMostTabIndex() )
            {
            positionActive = 1;
            }
        }

    if ( !iExtension->iNarrowTabLayout )
        {
        TInt tabCount = TabCount();
        iExtension->iTabsHidden = CAknTabGroupGraphics::ENone;
        TBool animationOngoing( iExtension->iTabCycleAnimationOngoing );
        TBool firstAnimationUpdate( animationOngoing
                && iExtension->iAmountOfDoneAnimationEvents == 0 );

                if ( tabCount > iNumberOfTabsShown && penEnabled )
                    {
                    iExtension->iTabsHidden = CAknTabGroupGraphics::ETwoOnBothSides;
                    if ( animationOngoing &&
                         ( ( iFirstShownTab == 0 &&
                             iExtension->iTabCycleAnimationDirection == ELeft ) ||
                           ( iFirstShownTab == tabCount - ( iNumberOfTabsShown ) &&
                             iExtension->iTabCycleAnimationDirection == ERight ) ) )
                        {
                        iExtension->iTabsHidden = CAknTabGroupGraphics::EOnBothSides;
                        }
                    else if ( iActiveTab < iNumberOfTabsShown &&
                         ( ( iFirstShownTab == 0 &&
                             !animationOngoing ) ||
                           firstAnimationUpdate &&
                           iExtension->iTabCycleAnimationDirection == ERight ) )
                        {
                        iExtension->iTabsHidden = CAknTabGroupGraphics::EOnRightSide;
                        }
                    else if ( iActiveTab >= tabCount - ( iNumberOfTabsShown ) &&
                              ( ( !animationOngoing &&
                                  iFirstShownTab == tabCount - ( iNumberOfTabsShown ) ) ||
                                firstAnimationUpdate &&
                                iExtension->iTabCycleAnimationDirection == ELeft ) )
                        {
                        iExtension->iTabsHidden = CAknTabGroupGraphics::EOnLeftSide;
                        }
                    }

        if (firstAnimationUpdate)
            {
            iExtension->iNextTabBackgroundLayout.iUse = EFalse;
            }
        else
            {
            iExtension->iNextTabBackgroundLayout.iUse = ETrue;
            }

        }

    iExtension->iTabAnimationDoubleBufferNarrowTabLayout
            = iExtension->iNarrowTabLayout;
    iExtension->iTabAnimationDoubleBufferNumberOfTabsShown
            = iNumberOfTabsShown;
    iExtension->iTabAnimationDoubleBufferpositionActive = positionActive;
    iExtension->iTabAnimationDoubleBufferLongTabs = iLongTabs;

    iExtension->iTabBackgroundLayout.iUse = ETrue;
    }


// ---------------------------------------------------------------------------
// Gets the tab group's parent rectangle.
// ---------------------------------------------------------------------------
//
TRect CAknTabGroup::ParentRect( TBool aArrowsUsed )
    {
    TBool scaled( ETrue );

    if ( !AknLayoutUtils::PenEnabled() )
        {
        CEikStatusPaneBase* statusPane = CEikStatusPaneBase::Current();

        if ( statusPane )
            {
            // In portrait mode the tab group needs to be adjacent
            // the bottom of the navi pane.
            TInt layoutResId = statusPane->CurrentLayoutResId();
            if ( layoutResId == R_AVKON_STATUS_PANE_LAYOUT_USUAL_EXT ||
                 layoutResId == R_AVKON_STATUS_PANE_LAYOUT_EMPTY )
                {
                scaled = EFalse;
                }
            }
        }

    TRect parentRect(
        CAknNavigationDecorator::DecoratedTabControlRect( scaled,
                                                          aArrowsUsed ) );

    return parentRect;
    }


// ---------------------------------------------------------------------------
// Starts the tab group cycle animation.
// ---------------------------------------------------------------------------
//
void CAknTabGroup::StartCycleAnimationL( TDirection aDirection,
                                         TInt aNewTab )
    {
    TInt tabCount( TabCount() );

    // First check if the animation should be used.
    // The cycle animation is currently used only in following situation:
    //  1) The three tab layout is active.
    //  2) Touch layout is used.
    //  3) Cycling the focus changes the first shown tab of the tab group.
    //
    if ( iTabFixedWidth == KTabWidthWithThreeTabs &&          // 1
         AknLayoutUtils::PenEnabled() &&                      // 2
         tabCount > iNumberOfTabsShown &&
         ( ( iActiveTab > 0 && iActiveTab < tabCount - 2 &&   // 3
             aDirection == ERight ) ||
           ( iActiveTab > 1 && iActiveTab < tabCount - 1 &&   // 3
             aDirection == ELeft ) ||
           ( iActiveTab == 0 &&                               // 3
             aNewTab == ( iNumberOfTabsShown - 1 ) ) ||
           ( iActiveTab == tabCount - 1 &&                    // 3
             aNewTab == tabCount - iNumberOfTabsShown ) ) )
        {
        iExtension->iTabAnimationType =
            CAknTabGroupExtension::ETabCycleAnimation;

        iExtension->iTabCycleAnimationOngoing = ETrue;
        iExtension->iTabCycleAnimationDirection = aDirection;

        iExtension->iTabSvgGraphics->SetTabGroupBackgroundParent(
            ParentRect( iExtension->iNaviArrowsUsed ) );

        iExtension->iNextTabBackgroundLayout.iUse = EFalse;

        InitTabAnimationEventTimer();
        }
    }


// ---------------------------------------------------------------------------
// Switches the current tab layout to one that is usable in the current
// layout.
// ---------------------------------------------------------------------------
//
void CAknTabGroup::SwitchTabLayoutL()
    {
    TBool penEnabled( AknLayoutUtils::PenEnabled() );

    if ( penEnabled && ( iTabFixedWidth == KTabWidthWithTwoLongTabs ||
                         iTabFixedWidth == KTabWidthWithThreeLongTabs ||
                         iTabFixedWidth == KTabWidthWithFourTabs ) )
        {
        // If the current tab width is not supported in touch
        // layout then switch it to a corresponding one.
        SetTabFixedWidthL( iTabFixedWidth );
        }
    else if ( iExtension && iTabFixedWidth != iExtension->iRequestedTabWidth )
        {
        // Else try to set the requested width if it's supported in
        // the new layout.
        SetTabFixedWidthL( iExtension->iRequestedTabWidth );
        }
    else
        {
        // Nothing to do.
        return;
        }

    // Set the correct focus if tab width is changed in layout
    // switch.
    if ( iActiveTab >= 0 )
        {
        if ( penEnabled && iTabFixedWidth == KTabWidthWithThreeTabs )
            {
            if ( iActiveTab != RightMostTabIndex() &&
                    iActiveTab != LeftMostTabIndex() )
                {
                iFirstShownTab = iActiveTab - 1;
                }
            else if ( iActiveTab < iFirstShownTab )
                {
                iFirstShownTab = iActiveTab;
                }
            else if ( iActiveTab >= ( iFirstShownTab + iNumberOfTabsShown ) )
                {
                iFirstShownTab = iActiveTab - iNumberOfTabsShown + 1;
                }
            }
        else
            {
            if ( iActiveTab < iFirstShownTab )
                {
                iFirstShownTab = iActiveTab;
                }

            if ( iActiveTab >= ( iFirstShownTab + iNumberOfTabsShown ) )
                {
                iFirstShownTab = iActiveTab - iNumberOfTabsShown + 1;
                }
            }
        SizeChanged();
        }

    CancelTabAnimationEventTimer();
    }

 //  End of File
