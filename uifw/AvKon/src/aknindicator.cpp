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
* Description:  Implementation for status indicators.
*
*/


// INCLUDE FILES
#include <eikspane.h>
#include <AknsUtils.h>
#include <AknBidiTextUtils.h>
#include <AknPictographInterface.h>
#include <AknPictographDrawerInterface.h>
#include <AknIconUtils.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <akniconconfig.h>
#include <avkon.mbg>

#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikenvinterface.h>
#endif

#include <AknTasHook.h>
#include "AknPanic.h"
#include "aknconsts.h"
#include "AknIndicatorContainer.h"
#include "AknIndicator.h"
#include "AknUtils.h"
#include "aknenv.h"
#include "aknappui.h"
#include "AknDef.h"
#include "avkon.hrh"
#include "AknStatuspaneUtils.h"
#include "AknIndicatorFader.h"
#include "AknLayoutFont.h"
#include "layoutmetadata.cdl.h"
#include "AknIndicatorPlugin.h"
#include "AknIndicatorPluginImplUIDs.hrh"
#include "AknIndicatorObserver.h"
#include "aknstatuspanedatapublisher.h"
#include "aknnavide.h"

// Flags for indicators
enum TIndicatorsControlFlags
    {
    EAknIndicatorsButton1DownInIndicatorRect = 0x00000001
    };

// CONSTANTS
const TInt KAknBitmapQueueGranularity = 2;

// ================= Extension class ========================
NONSHARABLE_CLASS( CAknIndicatorExtension ) : CBase
    {
friend class CAknIndicator;

public:

    CAknIndicatorExtension();
    ~CAknIndicatorExtension();

public: // data

    CCoeControl*        iContainerControl;
    CAknIndicatorFader* iFader; // not owned

    TBool iIndicatorBitmapsCreated;

    typedef CArrayFixFlat<TInt> CAknIndicatorBitmapIndexQueue;
    CAknIndicatorBitmapIndexQueue* iIndicatorBitmapIndexes[2];

    TBool  iDynamicTextIndicator;
    HBufC* iDynamicIndicatorText;
    TBool  iMultiColorMode;
    TInt   iIndicatorPosition;

    TAknsItemID   iIndicatorColorGroup[2];
    TInt          iIndicatorColorIndex[2];

    TInt iFlags;
    };

CAknIndicatorExtension::CAknIndicatorExtension() :
    iFlags( 0 )
    {
    }


CAknIndicatorExtension::~CAknIndicatorExtension()
    {
    delete iDynamicIndicatorText;
    }



// ================= MEMBER FUNCTIONS =======================
CAknIndicator::CAknIndicator() :
                    iCountOfAnimStates(1),
                    iIndicatorTypeText(EFalse),
                    iIndicatorContext(CAknIndicatorContainer::EUniversalIndicators)
    {
    AKNTASHOOK_ADD( this, "CAknIndicator" );
    }

CAknIndicator::CAknIndicator(TInt aIndicatorContext) :
                    iCountOfAnimStates(1),
                    iIndicatorTypeText(EFalse),
                    iIndicatorContext(aIndicatorContext)
    {
    AKNTASHOOK_ADD( this, "CAknIndicator" );
    }

CAknIndicator::~CAknIndicator()
    {
    AKNTASHOOK_REMOVE();
    if(iExtension && iExtension->iIndicatorBitmapIndexes)
        {
        delete iExtension->iIndicatorBitmapIndexes[ELayoutModeUsual];
        delete iExtension->iIndicatorBitmapIndexes[ELayoutModeWide];
        }

    if ( iIndicatorBitmaps[ELayoutModeUsual] )
        {
        TInt count = iIndicatorBitmaps[ELayoutModeUsual]->Count();
        for(TInt ii = 0; ii < count; ii++)
            {
            delete iIndicatorBitmaps[ELayoutModeUsual]->At(ii);
            }
        delete iIndicatorBitmaps[ELayoutModeUsual];
        }

    if ( iIndicatorBitmaps[ELayoutModeWide] )
        {
        TInt count = iIndicatorBitmaps[ELayoutModeWide]->Count();
        for(TInt ii = 0; ii < count; ii++)
            {
            delete iIndicatorBitmaps[ELayoutModeWide]->At(ii);
            }
        delete iIndicatorBitmaps[ELayoutModeWide];
        }

    delete iBitmapFile;
    delete iIndicatorText;
    delete iExtension;

    }

void CAknIndicator::ConstructFromResourceL(TResourceReader& aReader, CAknIndicatorContainer* aParent)
    {
    if (!iExtension)
        {
        iExtension = new (ELeave) CAknIndicatorExtension;
        }

    if ( !iExtension->iIndicatorBitmapIndexes[ELayoutModeUsual] )
        {
        iExtension->iIndicatorBitmapIndexes[ELayoutModeUsual] = new(ELeave)
            CArrayFixFlat<TInt>(KAknBitmapQueueGranularity);
        }
    if ( !iExtension->iIndicatorBitmapIndexes[ELayoutModeWide] )
        {
        iExtension->iIndicatorBitmapIndexes[ELayoutModeWide] = new(ELeave)
            CArrayFixFlat<TInt>(KAknBitmapQueueGranularity);
        }

    if ( !iIndicatorBitmaps[ELayoutModeUsual] )
        {
        iIndicatorBitmaps[ELayoutModeUsual] = new(ELeave)
            CAknBitmapQueue(KAknBitmapQueueGranularity);
        }
    if ( !iIndicatorBitmaps[ELayoutModeWide] )
        {
        iIndicatorBitmaps[ELayoutModeWide] = new(ELeave)
            CAknBitmapQueue(KAknBitmapQueueGranularity);
        }
    iParent = aParent;

#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
    SetParent( aParent );
#endif

    iUid = aReader.ReadInt16();

    iNarrowPriority = aReader.ReadInt16();
    iWidePriority = aReader.ReadInt16();

    iBitmapFile = aReader.ReadHBufCL(); // bmp filename

    if ( !iBitmapFile )
        {
        iIndicatorTypeText = ETrue;
        }

    TInt count = aReader.ReadInt16();  // Number of states

    for (TInt ii = 0; ii < count; ii++)
        {
        TInt stateId = aReader.ReadInt16();
        switch ( stateId )
            {
            case EAknIndicatorStateOn:
                {

                TInt count = aReader.ReadInt16(); // Number of icons should be 1 in this state
                __ASSERT_ALWAYS( count == 1, Panic(EAknPanicOutOfRange));

                LoadIndicatorBitmapsL( aReader, count );
                break;
                }
            case EAknIndicatorStateAnimate:
                {
                iCountOfAnimStates = aReader.ReadInt16();
                __ASSERT_ALWAYS( iCountOfAnimStates >= 1, Panic(EAknPanicOutOfRange));

                LoadIndicatorBitmapsL( aReader, iCountOfAnimStates );
                break;
                }
            case EAknIndicatorStateOff: // No icons shown
                break;
            default:
                __ASSERT_ALWAYS( count == 1, Panic(EAknPanicOutOfRange));
                break;
            }
        }

    // If default icon file is used we delete filename to save some memory
   if ( iBitmapFile && !iBitmapFile->CompareC( KAvkonBitmapFile ) )
        {
        delete iBitmapFile;
        iBitmapFile = NULL;
        }


    // Decide here how indicators are positioned by default.
    switch (iUid)
        {
        case EAknNaviPaneEditorIndicatorMessageInfo:
        case EAknNaviPaneEditorIndicatorMessageLength:
        case EAknNaviPaneEditorIndicatorWmlWindowsText:
        case EAknNaviPaneEditorIndicatorWmlWindows:
        case EAknNaviPaneEditorIndicatorSecuredConnection:
        case EAknNaviPaneEditorIndicatorProgressBar:
        case EAknNaviPaneEditorIndicatorWaitBar:
        case EAknNaviPaneEditorIndicatorWlanAvailable:
        case EAknNaviPaneEditorIndicatorWlanActive:
        case EAknNaviPaneEditorIndicatorWlanActiveSecure:
            {
            iExtension->iIndicatorPosition = CAknIndicatorContainer::ELeftSide;
            break;
            }
        case EAknNaviPaneEditorIndicatorWmlWaitGlobe:
            {
            iExtension->iIndicatorPosition = CAknIndicatorContainer::EMiddle;
            break;
            }
        default:
            {
            iExtension->iIndicatorPosition = CAknIndicatorContainer::ERightSide;
            break;
            }
        }
    }


void CAknIndicator::SetIndicatorState(TInt aState)
    {
    iState = aState;
    if ( iState == EAknIndicatorStateOn )
        {
        iAnimState = iCountOfAnimStates - 1;
        }
    else if ( iState == EAknIndicatorStateOff )
        {
        DeleteBitmaps();
        }
    SizeChanged();
    }


void CAknIndicator::SetIndicatorValueL(const TDesC& aString)
    {
    __ASSERT_ALWAYS( iIndicatorTypeText, Panic(EAknPanicOutOfRange));

    iExtension->iDynamicTextIndicator = ETrue; // Set to dynamic type by default
    delete iIndicatorText;
    iIndicatorText = NULL;

    // If dynamic text indicator, then do not convert to visual here...we do it later.
    if (iExtension->iDynamicTextIndicator)
        {
        HBufC* copiedString = HBufC::NewLC( aString.Length() + KAknBidiExtraSpacePerLine );
        *copiedString = aString;
        iIndicatorText = copiedString;
        CleanupStack::Pop(); // copiedString
        SizeChanged();
        }
    else
        {
        // screen
        TRect screenRect;
        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, screenRect );

        TInt  KDefaultMaxIndicatorWidth = 67; // Non-APAC layouts use this value (not in LAF yet)
        TInt  KApacMaxIndicatorWidth = 62;    // APAC layouts use this value (not in LAF yet)

        TInt maxIndicatorWidth = (KDefaultMaxIndicatorWidth * screenRect.Width())/176; // scale magic number

        TAknLayoutId layout;
        iAvkonEnv->GetCurrentLayoutId( layout );

        if ( layout == EAknLayoutIdAPAC )
            {
            maxIndicatorWidth = (KApacMaxIndicatorWidth * screenRect.Width())/176; // scale magic number
            }

        TInt statusPaneCurrentResourceId = 0;
        CEikStatusPaneBase* statusPane = CEikStatusPaneBase::Current();

        if ( statusPane )
            statusPaneCurrentResourceId = statusPane->CurrentLayoutResId();

        // If this indicator is in small statuspane we have more space
        if (AknStatuspaneUtils::SmallLayoutActive())
            {
            // app window
            TAknWindowComponentLayout applicationWindowLayout( AknLayoutScalable_Avkon::application_window(0) );
            TAknLayoutRect applicationWindowLayoutRect;
            applicationWindowLayoutRect.LayoutRect( screenRect, applicationWindowLayout );
            TRect applicationWindowRect( applicationWindowLayoutRect.Rect() );

            // top area
            TAknWindowComponentLayout topAreaLayout( AknLayoutScalable_Avkon::area_top_pane(1) );
            TAknLayoutRect topAreaLayoutRect;
            topAreaLayoutRect.LayoutRect( applicationWindowRect, topAreaLayout );
            TRect topAreaRect( topAreaLayoutRect.Rect() );

            // small statuspane
            TAknWindowComponentLayout smallStatusPaneLayout( AknLayoutScalable_Avkon::status_small_pane() );
            TAknLayoutRect smallStatusPaneLayoutRect;
            smallStatusPaneLayoutRect.LayoutRect( topAreaRect, smallStatusPaneLayout );
            TRect smallStatusPaneRect( smallStatusPaneLayoutRect.Rect() );

            // small statuspane, icons
            TAknWindowComponentLayout iconPaneLayout( AknLayoutScalable_Avkon::status_small_icon_pane() );
            TAknLayoutRect iconPaneLayoutRect;
            iconPaneLayoutRect.LayoutRect( smallStatusPaneRect, iconPaneLayout );
            TRect iconPaneRect( iconPaneLayoutRect.Rect() );

            // small statuspane, gprs
            TAknWindowComponentLayout gprsIndicatorLayout( AknLayoutScalable_Avkon::signal_pane_g2(0) );
            TAknLayoutRect gprsIndicatorLayoutRect;
            gprsIndicatorLayoutRect.LayoutRect( smallStatusPaneRect, gprsIndicatorLayout );
            TRect gprsIndicatorRect( gprsIndicatorLayoutRect.Rect() );

            // Finally calculate the available length
            maxIndicatorWidth = iconPaneRect.Width() - KMinSpaceBetweenIconsInPixels;

            // if gprs is visible, reduce available lenght a bit
            if ( statusPaneCurrentResourceId == AVKONENV->StatusPaneResIdForCurrentLayout(R_AVKON_STATUS_PANE_LAYOUT_SMALL_WITH_SIGNAL_PANE) )
                maxIndicatorWidth -= gprsIndicatorRect.Width();
            }
        // if this indicator is in staconapane we have more space
        if (AknStatuspaneUtils::StaconPaneActive())
            {
            TRect navirect = CAknNavigationDecorator::DecoratedControlRect(CAknNavigationDecorator::EEditorIndicator);
            maxIndicatorWidth = navirect.Size().iWidth;
            }

        TAknTextComponentLayout line;
        if (AknStatuspaneUtils::SmallLayoutActive() || AknStatuspaneUtils::StaconPaneActive())
            {
            line = AknLayoutScalable_Avkon::status_small_pane_t1(0);
            }
        else
            {
            TAknWindowComponentLayout layout( AknLayoutScalable_Avkon::navi_text_pane(0) );
            TAknTextComponentLayout l2( AknLayoutScalable_Avkon::navi_text_pane_t1() );
            line = TAknWindowComponentLayout::ComposeText( layout, l2 );
            }

        const CFont* fontUsed = AknLayoutUtils::FontFromId(line.LayoutLine().FontId());

        HBufC* clippedString = HBufC::NewLC( aString.Length() + KAknBidiExtraSpacePerLine );
        *clippedString = aString;
        TPtr clippedStringPtr = clippedString->Des();
        AknBidiTextUtils::ConvertToVisualAndClipL(
            clippedStringPtr,
            *fontUsed,
            maxIndicatorWidth,
            maxIndicatorWidth);

        iIndicatorText = clippedString;
        CleanupStack::Pop(); // clippedString
        SizeChanged();
        }
    }

TInt CAknIndicator::IndicatorState()
    {
    return iState;
    }

TBool CAknIndicator::TextIndicator()
    {
    return iIndicatorTypeText;
    }

TSize CAknIndicator::IconSize()
    {
    TInt layoutMode = iLayoutMode; // Universal indicators

    if ( iIndicatorContext == CAknIndicatorContainer::ENaviPaneEditorIndicators )
        {
        layoutMode = ELayoutModeWide;
        }
    else if ( iIndicatorContext == CAknIndicatorContainer::EQueryEditorIndicators )
        {
        layoutMode = ELayoutModeUsual;
        }

    if ( !iIndicatorTypeText && (iIndicatorBitmaps[layoutMode]->Count() > 0))
        {
        if ( iIndicatorBitmaps[layoutMode]->At( 0 ) )
            {
            // If bitmap is not yet rendered, do it before measuring it.
            if (iIndicatorBitmaps[layoutMode]->At( 0 )->SizeInPixels() == TSize(0,0))
                SetSvgIconSize(iIndicatorBitmaps[layoutMode]->At( 0 ), iLayoutMode);
            return iIndicatorBitmaps[layoutMode]->At( 0 )->SizeInPixels();
            }
        else
            {
            return TSize(0,0);
            }
        }
    else if (iIndicatorText)
        {
        TAknTextComponentLayout line;
        if (AknStatuspaneUtils::SmallLayoutActive() || AknStatuspaneUtils::StaconPaneActive())
            {
            line = AknLayoutScalable_Avkon::status_small_pane_t1(0);
            }
        else
            {
            TAknWindowComponentLayout layout( AknLayoutScalable_Avkon::navi_text_pane(0) );
            TAknTextComponentLayout l2( AknLayoutScalable_Avkon::navi_text_pane_t1() );
            line = TAknWindowComponentLayout::ComposeText( layout, l2 );
            }

        const CFont* fontUsed = AknLayoutUtils::FontFromId( line.LayoutLine().FontId() );

        // The iIndicatorText is in logical order.
        CFont::TMeasureTextInput input;
        TInt textLength = fontUsed->MeasureText( *iIndicatorText, &input );

        const CAknLayoutFont* layoutFont = CAknLayoutFont::AsCAknLayoutFontOrNull( fontUsed );
        TInt textPaneHeight(0);
        if ( layoutFont )
            {
            textPaneHeight = layoutFont->TextPaneHeight();
            }
        else
            {
            textPaneHeight = fontUsed->HeightInPixels();
            }


        // +1 is to leave some empty space between text and the next indicator
        return TSize( textLength + 1, textPaneHeight );
        }
    else
        {
        return TSize(0,0);
        }
    }

TInt CAknIndicator::Priority()
    {
    TInt layoutMode = iLayoutMode;

    if ( iIndicatorContext == CAknIndicatorContainer::ENaviPaneEditorIndicators )
        {
        layoutMode = ELayoutModeWide;
        }
    else if ( iIndicatorContext == CAknIndicatorContainer::EQueryEditorIndicators )
        {
        layoutMode = ELayoutModeUsual;
        }

    return (layoutMode == ELayoutModeUsual ? iNarrowPriority : iWidePriority);
    }


void CAknIndicator::SetLayoutMode(TLayoutMode aMode)
    {
    iLayoutMode = aMode;
    if (iState != EAknIndicatorStateOff) // Do SizeChanged only if really needed to avoid performance problems with SVG graphics
        SizeChanged();
    }

TUid CAknIndicator::Uid() const
    {
    return TUid::Uid(iUid);
    }

EXPORT_C void CAknIndicator::PositionChanged()
    {
    CCoeControl::PositionChanged();
    }


// ---------------------------------------------------------------------------
// CAknIndicator::Draw
// Draws the indicator.
// ---------------------------------------------------------------------------
//
void CAknIndicator::Draw( const TRect& /*aRect*/ ) const
    {
    CWindowGc& gc = SystemGc();

    TRect rect( Rect() );

    if ( iIndicatorTypeText )
        {
        // Draw text indicator
        if ( !iIndicatorText )
            {
            return;
            }

        TAknTextComponentLayout line;
        if ( AknStatuspaneUtils::SmallLayoutActive() ||
             AknStatuspaneUtils::StaconPaneActive() )
            {
            line = AknLayoutScalable_Avkon::status_small_pane_t1( 0 );
            }
        else
            {
            line = TAknWindowComponentLayout::ComposeText(
                AknLayoutScalable_Avkon::navi_text_pane( 0 ),
                AknLayoutScalable_Avkon::navi_text_pane_t1() );
            }

        const CFont* fontUsed = AknLayoutUtils::FontFromId( line.LayoutLine().FontId() );


        const CAknLayoutFont* layoutFont = CAknLayoutFont::AsCAknLayoutFontOrNull( fontUsed );
        TInt textPaneAscent( 0 );
        if ( layoutFont )
            {
            textPaneAscent = layoutFont->TextPaneTopToBaseline();
            }
        else
            {
            textPaneAscent = fontUsed->AscentInPixels();
            }


        TRgb color( SelectColor( iLayoutMode ) );
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();

        CGraphicsContext::TTextAlign textAlign =
            AknLayoutUtils::LayoutMirrored() ? CGraphicsContext::ERight :
                                               CGraphicsContext::ELeft;

        gc.SetPenColor( color );
        gc.SetPenStyle( CGraphicsContext::ESolidPen );
        gc.SetBrushStyle( CGraphicsContext::ENullBrush );
        gc.UseFont( fontUsed );
        gc.DrawText( *Text(), rect, textPaneAscent, textAlign, 0 );

        // Draw pictographs if required.
        CAknPictographInterface* pictoInterface = iParent->PictographInterface();
        if ( pictoInterface )
            {
            pictoInterface->Interface()->DrawPictographsInText(
                gc,
                *fontUsed,
                *Text(),
                rect,
                textPaneAscent,
                textAlign,
                0 );
            }
        gc.DiscardFont();
        }
    else // indicator icon
        {
        TInt layoutMode = iLayoutMode;

        if ( iIndicatorContext == CAknIndicatorContainer::ENaviPaneEditorIndicators )
            {
            layoutMode = ELayoutModeWide;
            }
        else if ( iIndicatorContext == CAknIndicatorContainer::EQueryEditorIndicators )
            {
            layoutMode = ELayoutModeUsual;
            }

        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        TSize iconSize( iIndicatorBitmaps[layoutMode]->At( 0 )->SizeInPixels() );
        TInt iconWidth  = iconSize.iWidth;
        TInt iconHeight = iconSize.iHeight;

        if ( iState != EAknIndicatorStateOff )
            {
            // GPRS indicator is actually never drawn here, it is drawn
            // by the system to the signal pane.
            if ( iUid == EAknNaviPaneEditorIndicatorGprs )
                {
                return;
                }

            if ( iUid == EAknNaviPaneEditorIndicatorProgressBar ||
                 iUid == EAknNaviPaneEditorIndicatorWaitBar )
                {
                TRgb color( SelectColor( iLayoutMode ) );

                // Draw rect outside the bar.
                gc.SetPenColor( color );
                gc.SetPenStyle( CGraphicsContext::ESolidPen );
                gc.DrawRect( rect );

                TAknWindowComponentLayout waitPaneComponentLayout(
                    AknLayoutScalable_Avkon::status_small_wait_pane_g2() );

                TAknLayoutRect waitPaneComponentLayoutRect;
                waitPaneComponentLayoutRect.LayoutRect( rect, waitPaneComponentLayout );
                TRect waitPaneComponentRect( waitPaneComponentLayoutRect.Rect() );
                rect = waitPaneComponentRect;

                if ( iUid == EAknNaviPaneEditorIndicatorProgressBar )
                    {
                    // Calculate the progress amount.
                    TInt progressInPixels = 0;
                    if ( iProgressBarMaxValue > 0 )
                        {
                        progressInPixels =
                            ( iconSize.iWidth * iProgressBarValue ) / iProgressBarMaxValue;
                        }
                    iconWidth = progressInPixels;
                    }
                }

            if ( iIndicatorBitmaps[layoutMode]->At( iAnimState * 2 ) &&
                 iIndicatorBitmaps[layoutMode]->At( iAnimState * 2 + 1 ) )
                {
                CFbsBitmap* mask = iIndicatorBitmaps[layoutMode]->At( iAnimState * 2 + 1 );
                if ( iExtension && iExtension->iFader )
                    {
                    mask = iExtension->iFader->FadeMask(
                        iIndicatorBitmaps[layoutMode]->At( iAnimState * 2 + 1 ) );
                    }

                gc.SetBrushStyle( CGraphicsContext::ENullBrush );

                // Draw editor indicator bitmap with mask if it exists
                gc.BitBltMasked( TPoint( rect.iTl.iX, rect.iTl.iY ),
                                 iIndicatorBitmaps[layoutMode]->At( iAnimState * 2 ),
                                 TRect( 0, 0, iconWidth, iconHeight),
                                 mask,
                                 ETrue );
                }
        else if ( iIndicatorBitmaps[layoutMode]->At( iAnimState * 2 ) )
                {
                // Draw editor indicator bitmap without mask
                CFbsBitmap* mask = iIndicatorBitmaps[layoutMode]->At( iAnimState * 2 );
                if ( iExtension && iExtension->iFader )
                    {
                    mask = iExtension->iFader->FadeMask(
                        iIndicatorBitmaps[layoutMode]->At( iAnimState * 2 ) );
                    }
                gc.BitBlt( TPoint( rect.iTl.iX,rect.iTl.iY ),
                           mask,
                           TRect( 0, 0, iconWidth, iconHeight ) );
                }
            }
        }
    }


void CAknIndicator::LoadIndicatorBitmapsL(TResourceReader& aReader, TInt aCount)
    {
    LoadIndicatorBitmapsL(aReader, aCount, EFalse);
    }

void CAknIndicator::LoadIndicatorBitmapsL(TResourceReader& aReader, TInt aCount, TBool aCreateBitmaps)
    {
    TInt bitmapId;
    TInt maskId;

    for (TInt ii = 0; ii < aCount; ii++)
        {
        for (TInt jj = ELayoutModeUsual; jj <= ELayoutModeWide; jj++)
            {
            if ( ( (jj == ELayoutModeWide) &&
                (iIndicatorContext == CAknIndicatorContainer::EQueryEditorIndicators) )
                ||
                ( (jj == ELayoutModeUsual) &&
                (iIndicatorContext == CAknIndicatorContainer::ENaviPaneEditorIndicators) ) )
                {
                // Do not load query editor bitmaps if navi pane editor indicators is needed
                // and vice versa
                aReader.ReadInt16(); // bitmaps
                aReader.ReadInt16(); // mask
                iExtension->iIndicatorBitmapIndexes[jj]->AppendL(0); // bitmap
                iExtension->iIndicatorBitmapIndexes[jj]->AppendL(0); // mask
                continue;
                }
                bitmapId = aReader.ReadInt16();
                maskId = aReader.ReadInt16();

                if (bitmapId == 16446)
                    {
                    TInt tmp =     bitmapId+1;
                    bitmapId = tmp-1;
                    }

                if ( bitmapId == -1 ) // no bitmap
                    {
                    iExtension->iIndicatorBitmapIndexes[jj]->AppendL(0); // bitmap
                    iExtension->iIndicatorBitmapIndexes[jj]->AppendL(0); // mask
                    continue;
                    }
                if ( maskId == -1 ) // no mask, just bitmap
                    {
                    iExtension->iIndicatorBitmapIndexes[jj]->AppendL(bitmapId); // bitmap
                    iExtension->iIndicatorBitmapIndexes[jj]->AppendL(bitmapId); // mask
                    }
                else // both bitmap and mask
                    {
                    iExtension->iIndicatorBitmapIndexes[jj]->AppendL(bitmapId); // bitmap
                    iExtension->iIndicatorBitmapIndexes[jj]->AppendL(maskId); // mask
                    }
            }
        }

    if (aCreateBitmaps)
        CreateLoadedIndicatorBitmapsL();
    }


void CAknIndicator::CreateLoadedIndicatorBitmapsL()
    {
    if (!iExtension->iIndicatorBitmapsCreated)
        {
        TInt count = 0;
        TInt bitmapId = 0;
        TInt maskId = 0;
        CFbsBitmap* bitmap = NULL;
        CFbsBitmap* mask = NULL;

        for (TInt jj = ELayoutModeUsual; jj <= ELayoutModeWide; jj++)
            {
            count = iExtension->iIndicatorBitmapIndexes[jj]->Count();
            for(TInt ii = 0; ii < count; ii+=2)
                {
                bitmapId = iExtension->iIndicatorBitmapIndexes[jj]->At(ii);
                maskId = iExtension->iIndicatorBitmapIndexes[jj]->At(ii+1);

                if (bitmapId && maskId)
                    {
                    TAknsItemID dummyId;
                    dummyId.Set( 0,0 );

                    TAknsItemID colorGroup;
                    colorGroup.Set(0,0);

                    TInt colorIndex = 0;

                    SelectColorSkin(jj, colorGroup, colorIndex);

                    MAknsSkinInstance* skin = AknsUtils::SkinInstance();

                    if (MultiColorMode())
                        {
                        if (iBitmapFile)
                            AknIconUtils::CreateIconLC( bitmap, mask, *iBitmapFile, bitmapId, maskId );
                        else
                            AknIconUtils::CreateIconLC( bitmap, mask, KAvkonBitmapFile, bitmapId, maskId );
                        }
                    else
                        {
                        if (iBitmapFile)
                            AknsUtils::CreateColorIconLC( skin, dummyId, colorGroup, colorIndex,
                                bitmap, mask, *iBitmapFile, bitmapId, maskId, KRgbGray );
                        else
                            AknsUtils::CreateColorIconLC( skin, dummyId, colorGroup, colorIndex,
                                bitmap, mask, AknIconUtils::AvkonIconFileName(), bitmapId, maskId, KRgbGray );

                        iExtension->iIndicatorColorGroup[jj] = colorGroup;
                        iExtension->iIndicatorColorIndex[jj] = colorIndex;
                        }

                    iIndicatorBitmaps[jj]->AppendL(bitmap);
                    iIndicatorBitmaps[jj]->AppendL(mask);
                    CleanupStack::Pop(2); // bitmap, mask
                    }
                }
            }
        }
    iExtension->iIndicatorBitmapsCreated = ETrue;
    }


void CAknIndicator::Animate()
    {
    iAnimState += 1;
    if (iAnimState >= iCountOfAnimStates)
        {
        iAnimState = 0;
        }
    }

void CAknIndicator::SetAnimateState(TInt aAnimState)
    {
    iAnimState = aAnimState % iCountOfAnimStates;
    }

void CAknIndicator::SetIndicatorValue( TInt aValue, TInt aMaxValue )
    {
    // check that values are not insane
    if ( aValue >= 0    &&
         aMaxValue >= 0 &&
         aMaxValue >= aValue )
        {
        iProgressBarValue    = aValue;
        iProgressBarMaxValue = aMaxValue;
        }
    SizeChanged();
    }


void CAknIndicator::SetSvgIconSize( CFbsBitmap*& aBitmap, TInt aLayoutMode )
    {
    TRect rect( Rect() );

    TInt indicatorUid = iUid;
    if (indicatorUid >= EAknNaviPaneEditorIndicatorDynamicUidRangeFirst &&
        indicatorUid <= EAknNaviPaneEditorIndicatorDynamicUidRangeLast)
        {
        indicatorUid = EAknNaviPaneEditorIndicatorDynamicUidRangeFirst;
        }

    TSize size(10,10); // default size (every SVG icon needs to be initialized)
    TScaleMode aspectRatio = EAspectRatioPreservedAndUnusedSpaceRemoved;

    TRect navipaneRect(0,0,0,0);
    CEikStatusPaneBase* statusPane = CEikStatusPaneBase::Current();
    if (statusPane)
        {
        CCoeControl* control = NULL;
        TRAP_IGNORE(control = statusPane->ControlL(TUid::Uid( EEikStatusPaneUidNavi )));
        if (control)
            {
            navipaneRect.SetSize( control->Size() );
            }
        }

    // If navipane is not found, we get portrait normal navipanerect frop laf data which is usually right enough.
    if (navipaneRect.Size() == TSize(0,0))
        {
        TInt battery = 0;
        TRect statusPaneRect;
        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EStatusPane, statusPaneRect );

        if ( AknStatuspaneUtils::IdleLayoutActive() )
            {
            if ( ( iIndicatorContext == CAknIndicatorContainer::EQueryEditorIndicators )
                && ( statusPaneRect.Size() == TSize(0,0) ) )
                {
                battery = 0;
                }
            else
                {
                battery = 1;
                }
            }


        // Navi pane
        TAknWindowComponentLayout naviPaneLayout( AknLayoutScalable_Avkon::navi_pane(battery) );
        TAknLayoutRect naviPaneLayoutRect;
        naviPaneLayoutRect.LayoutRect(statusPaneRect, naviPaneLayout);
        navipaneRect.SetSize( naviPaneLayoutRect.Rect().Size() );
        }

    // Screen
    TRect screenRect;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, screenRect );

    switch (indicatorUid)
        {
        // Status pane's indicators
        case EAknIndicatorIrActive:
        case EAknIndicatorEnvelope:
        case EAknIndicatorEmailMessage:
        case EAknIndicatorDataMessage:
        case EAknIndicatorFaxMessage:
        case EAknIndicatorOtherMessage:
        case EAknIndicatorSecuredConnection:
        case EAknIndicatorVoiceMailWaiting:
        case EAknIndicatorVoiceMailWaitingOnLine1:
        case EAknIndicatorVoiceMailWaitingOnLine2:
        case EAknIndicatorVoiceMailWaitingOnBothLines:
        case EAknIndicatorHomeZone:
        case EAknIndicatorBluetooth:
        case EAknIndicatorBluetoothVisible:
        case EAknIndicatorBluetoothModuleOn:
        case EAknIndicatorBluetoothModuleOnVisible:
        case EAknIndicatorOutbox:
        case EAknIndicatorKeyguard:
        case EAknIndicatorAllCallsForwarded:
        case EAknIndicatorCallsForwardedOnLine1:
        case EAknIndicatorCallsForwardedOnLine2:
        case EAknIndicatorCallsForwardedOnBothLines:
        case EAknIndicatorCallsForwardedToVoiceMailbox:
        case EAknIndicatorSelectedLine:
        case EAknIndicatorAlarmClock:
        case EAknIndicatorHeadset:
        case EAknIndicatorLoopset:
        case EAknIndicatorIHFActive:
        case EAknIndicatorInstantMessage:
        case EAknIndicatorTTY:
        case EAknIndicatorUSBConnection:
        case EAknIndicatorMissedCalls:
        case EAknIndicatorRemoteMailboxEmailMessage:
        case EAknIndicatorLocation:
        case EAknIndicatorHeadsetUnavailable:
        case EAknIndicatorRoaming:
        case EAknIndicatorLocationOn:
        case EAknIndicatorLocationOff:
        case EAknIndicatorPoC:
        case EAknIndicatorPoCMissed:
        case EAknIndicatorPoCDnD:
        case EAknIndicatorVoIP:
        case EAknIndicatorWlanAvailable:
        case EAknIndicatorWlanActive:
        case EAknIndicatorWlanActiveSecure:
        case EAknIndicatorCarkit:
        case EAknIndicatorTvOut:
        case EAknIndicatorHDMI:
        case EAknIndicatorMobileTV:
        case EAknIndicatorMobileTVRec:
        case EAknIndicatorHAC:
        case EAknIndicatorMemoryCard:
        case EAknIndicatorTARM:
        case EAknIndicatorTARMModuleOn:
        case EAknIndicatorVideoSharing:
        case EAknIndicatorSynchronization:
        case EAknIndicatorGPS:
        case EAknIndicatorFMTxSending:
        case EAknIndicatorFMTxEnabled:
        case EAknIndicatorMissedCalendarAlarm:
        case EAknIndicatorUSBMemConnected:
        case EAknIndicatorUSBMemActive:
        case EAknIndicatorStopWatch:
        case EAknIndicatorMecoServiceTab:
            {
            // Main pane
            TRect mainPaneRect;
            AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane,
                                               mainPaneRect );

            // statuspane, usual
            TRect usualStatusPaneRect;
            AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EStatusPane,
                                               usualStatusPaneRect );

            // status indicator pane elements
            TRect statusIndicatorPaneElementsRect;
            AknLayoutUtils::LayoutMetricsRect(
                AknLayoutUtils::EIndicatorPane,
                statusIndicatorPaneElementsRect );

            // universal indicator pane (note statuspane as parent)
            TAknLayoutRect universalIndicatorPaneLayoutRect;
            universalIndicatorPaneLayoutRect.LayoutRect(
                usualStatusPaneRect,
                AknLayoutScalable_Avkon::uni_indicator_pane( 0 ) );
            TRect universalIndicatorPaneRect(
                universalIndicatorPaneLayoutRect.Rect() );

            // universal indicator pane elements
            TAknLayoutRect universalIndicatorPaneElementsLayoutRect;
            universalIndicatorPaneElementsLayoutRect.LayoutRect(
                universalIndicatorPaneRect,
                AknLayoutScalable_Avkon::uni_indicator_pane_g1() );
            TRect universalIndicatorPaneElementsRect(
                universalIndicatorPaneElementsLayoutRect.Rect() );

            if ( aLayoutMode == ELayoutModeUsual )
                {
                size = universalIndicatorPaneElementsRect.Size();
                }

            if ( aLayoutMode == ELayoutModeWide )
                {
                size = statusIndicatorPaneElementsRect.Size();
                }

            // Stacon special cases
            if ( AknStatuspaneUtils::StaconPaneActive() &&
                 !AknStatuspaneUtils::IdleLayoutActive() &&
                 !AknStatuspaneUtils::ExtendedStaconPaneActive())
                {
                size = Size();
                }
            else if ( AknStatuspaneUtils::ExtendedStaconPaneActive() )
                {
                size = Size();
                }

            // Flat special cases
            if ( AknStatuspaneUtils::FlatLayoutActive() )
                {
                size = Size();
                }

            // Portrait extended cases
            if ( AknStatuspaneUtils::ExtendedLayoutActive() )
                {
                size = Size();
                if ( AknStatuspaneUtils::IdleLayoutActive() &&
                     !AknStatuspaneUtils::HDLayoutActive() )
                    {
                    aspectRatio = EAspectRatioPreserved;
                    }
                }

            // In landscape idle we use vertical indicators if parent
            // is in vertical mode, otherwise horizontal.
            if ( AknStatuspaneUtils::IdleLayoutActive() &&
                 Layout_Meta_Data::IsLandscapeOrientation() &&
                 iParent->Size().iWidth < iParent->Size().iHeight )
                {
                size = Size();
                }

            break;
            }

        // Navi pane editor indicators
        case EAknNaviPaneEditorIndicatorT9:
        case EAknNaviPaneEditorIndicatorUpperCase:
        case EAknNaviPaneEditorIndicatorLowerCase:
        case EAknNaviPaneEditorIndicatorTextCase:
        case EAknNaviPaneEditorIndicatorNumberCase:
        case EAknNaviPaneEditorIndicatorQuery:
        case EAknNaviPaneEditorIndicatorQwertyShift:
#ifndef RD_INTELLIGENT_TEXT_INPUT
        case EAknNaviPaneEditorIndicatorAutoComplete:
#endif //RD_INTELLIGENT_TEXT_INPUT

        // select mode variants
        case EAknNaviPaneEditorIndicatorUpperCaseSelect:
        case EAknNaviPaneEditorIndicatorLowerCaseSelect:
        case EAknNaviPaneEditorIndicatorTextCaseSelect:
        case EAknNaviPaneEditorIndicatorNumberCaseSelect:

        case EAknNaviPaneEditorIndicatorArabicCase:
        case EAknNaviPaneEditorIndicatorHebrewCase:
        case EAknNaviPaneEditorIndicatorArabicIndicNumberCase:

        // FARSI AND URDU
        case EAknNaviPaneEditorIndicatorFarsiAndUrduCase:

        // APAC
        case EAknNaviPaneEditorIndicatorPinyin:
        case EAknNaviPaneEditorIndicatorZhuyin:
        case EAknNaviPaneEditorIndicatorStroke: // Stroke editor indicator for simplified Chinese.
        case EAknNaviPaneEditorIndicatorCangJie:

        case EAknNaviPaneEditorIndicatorZhuyinFind:
        case EAknNaviPaneEditorIndicatorStrokeFind:
        case EAknNaviPaneEditorIndicatorPinyinPhrase:
        case EAknNaviPaneEditorIndicatorZhuyinPhrase:
        case EAknNaviPaneEditorIndicatorStrokePhrase:
        case EAknNaviPaneEditorIndicatorStrokeTradPhrase:

        // THAI
        case EAknNaviPaneEditorIndicatorThai:
        // HINDI
//        #ifdef RD_HINDI
        case EAknNaviPaneEditorIndicatorDevanagariCase:
        case EAknNaviPaneEditorIndicatorDevanagariIndicNumberCase:
//        #endif //RD_HINDI
#ifdef RD_HINDI_PHONETIC_INPUT
        case EAknNaviPaneEditorIndicatorDevanagariPhoneticUpperCase:
        case EAknNaviPaneEditorIndicatorDevanagariPhoneticLowerCase:
#endif
        case EAknNaviPaneEditorIndicatorStrokeTrad:  // Stroke editor indicator for traditional Chinese.

        // Vietnamese
        case EAknNaviPaneEditorIndicatorVietnameseUpperCase:
        case EAknNaviPaneEditorIndicatorVietnameseLowerCase:
        case EAknNaviPaneEditorIndicatorVietnameseTextCase:
        
        // Greek   
        case EAknNaviPaneEditorIndicatorGreekUpperCase:
        case EAknNaviPaneEditorIndicatorGreekLowerCase:
        case EAknNaviPaneEditorIndicatorGreekTextCase:
        
        // Cyrillic   
        case EAknNaviPaneEditorIndicatorCyrillicUpperCase:
        case EAknNaviPaneEditorIndicatorCyrillicLowerCase:
        case EAknNaviPaneEditorIndicatorCyrillicTextCase:
        
        // Navi pane editor indicators for Japanese
        case EAknNaviPaneEditorIndicatorJapaneseHiraganaKanji:      // Hiragana/Kanji
        case EAknNaviPaneEditorIndicatorJapaneseHiragana:           // Hiragana
        case EAknNaviPaneEditorIndicatorJapaneseFullKatakana:       // Full-width Katakana
        case EAknNaviPaneEditorIndicatorJapaneseHalfKatakana:       // Half-width Katakana
        case EAknNaviPaneEditorIndicatorJapaneseFullUpperAlphabet:  // Full-width Upper Case alphabet
        case EAknNaviPaneEditorIndicatorJapaneseFullLowerAlphabet:  // Full-width Lower Case alphabet
        case EAknNaviPaneEditorIndicatorJapaneseFullTextAlphabet:   // Full-width Text Case alphabet
        case EAknNaviPaneEditorIndicatorJapaneseFullNumeric:        // Full-width numeric

		// Navi pane editor indicators for Korean
        case EAknNaviPaneEditorIndicatorKoreanHangul:
        case EAknNaviPaneEditorIndicatorKoreanHangulSelect:

        // Application indicators to editor indicator pane
        case EAknNaviPaneEditorIndicatorAudioAttached:
        case EAknNaviPaneEditorIndicatorImageAttached:
        case EAknNaviPaneEditorIndicatorObjects:
        case EAknNaviPaneEditorIndicatorAttachment:
        case EAknNaviPaneEditorIndicatorMcePriorityHigh:
        case EAknNaviPaneEditorIndicatorMcePriorityLow:
        case EAknNaviPaneEditorIndicatorMessageLength:
        case EAknNaviPaneEditorIndicatorMessageInfo:
        case EAknNaviPaneEditorIndicatorDynamicUidRangeFirst: // all custom indicators use this
#ifdef RD_INTELLIGENT_TEXT_INPUT
        case EAknNaviPaneEditorIndicatorFnKeyPressed:
        case EAknNaviPaneEditorIndicatorFnKeyLocked:
#endif
            {
            TAknWindowComponentLayout l1 = AknLayoutScalable_Avkon::navi_icon_pane(0);
            TAknWindowComponentLayout l2 = AknLayoutScalable_Avkon::navi_icon_pane_g1();
            TAknWindowComponentLayout layout = TAknWindowComponentLayout::Compose( l1, l2 );

            TAknLayoutRect layoutRect;
            layoutRect.LayoutRect( navipaneRect, layout );
            TRect rect( layoutRect.Rect() );
            size = rect.Size();
            break;
            }

        // Extra application indicators to editor indicator pane
        // in small or nHD status pane layout.
        case EAknNaviPaneEditorIndicatorWaitBar:
        case EAknNaviPaneEditorIndicatorProgressBar:
            {
            TAknLayoutRect waitPaneComponentLayoutRect;
            waitPaneComponentLayoutRect.LayoutRect(
                rect,
                AknLayoutScalable_Avkon::status_small_wait_pane_g2() );
            TRect waitPaneComponentRect( waitPaneComponentLayoutRect.Rect() );

            size        = waitPaneComponentRect.Size();
            aspectRatio = EAspectRatioNotPreserved;
            break;
            }

        case EAknNaviPaneEditorIndicatorWmlWindows:
        case EAknNaviPaneEditorIndicatorWmlWaitGlobe:
        case EAknNaviPaneEditorIndicatorSecuredConnection:
        case EAknNaviPaneEditorIndicatorGprs:
        case EAknNaviPaneEditorIndicatorFileSize:
        case EAknNaviPaneEditorIndicatorWlanAvailable:
        case EAknNaviPaneEditorIndicatorWlanActive:
        case EAknNaviPaneEditorIndicatorWlanActiveSecure:
            {
            // app window
            TAknWindowComponentLayout applicationWindowLayout( AknLayoutScalable_Avkon::application_window(0) );
            TAknLayoutRect applicationWindowLayoutRect;
            applicationWindowLayoutRect.LayoutRect( screenRect, applicationWindowLayout );
            TRect applicationWindowRect( applicationWindowLayoutRect.Rect() );

            // top area
            TAknWindowComponentLayout topAreaLayout( AknLayoutScalable_Avkon::area_top_pane(1) );
            TAknLayoutRect topAreaLayoutRect;
            topAreaLayoutRect.LayoutRect( applicationWindowRect, topAreaLayout );
            TRect topAreaRect( topAreaLayoutRect.Rect() );

            // small statuspane
            TAknWindowComponentLayout smallStatusPaneLayout( AknLayoutScalable_Avkon::status_small_pane() );
            TAknLayoutRect smallStatusPaneLayoutRect;
            smallStatusPaneLayoutRect.LayoutRect( topAreaRect, smallStatusPaneLayout );
            TRect smallStatusPaneRect( smallStatusPaneLayoutRect.Rect() );

            // icon pane
            TAknWindowComponentLayout iconPaneLayout( AknLayoutScalable_Avkon::status_small_icon_pane() );
            TAknLayoutRect iconPaneLayoutRect;
            iconPaneLayoutRect.LayoutRect( smallStatusPaneRect, iconPaneLayout );
            TRect iconPaneRect( iconPaneLayoutRect.Rect() );

            size = iconPaneRect.Size();
            break;
            }

        default:
            {
            break; // default size (10,10) used - no indicator should get this
            }
        }

    AknIconUtils::SetSize( aBitmap, size, aspectRatio );
    }


void CAknIndicator::SizeChanged()
    {
    // Optimization, we do not set sizes etc. if state is off.
    if (iState == EAknIndicatorStateOff)
        return;

    // Check for skin color change (because of layout might have changed)
    TAknsItemID selectedColorGroup;
    selectedColorGroup.Set(0,0);
    TInt selectedColorIndex = 0;
    SelectColorSkin(iLayoutMode, selectedColorGroup, selectedColorIndex);

    TAknsItemID activeColorGroup;
    activeColorGroup.Set(0,0);
    TInt activeColorIndex   = 0;
    ActiveColorSkin(iLayoutMode, activeColorGroup, activeColorIndex);

    TBool colorMode = MultiColorMode();
    if ( !colorMode && ( activeColorGroup != selectedColorGroup
            || activeColorIndex != selectedColorIndex ))
        DeleteBitmaps();

    // This method creates actual bitmaps if not yet created.
    TRAP_IGNORE(CreateLoadedIndicatorBitmapsL());

    if ( iIndicatorBitmaps[iLayoutMode] && Size() != TSize(0,0))
        {
        TInt count = iIndicatorBitmaps[iLayoutMode]->Count();
        for(TInt ii = 0; ii < count; ii++)
            {
            SetSvgIconSize(iIndicatorBitmaps[iLayoutMode]->At(ii),iLayoutMode);
            }
        }

    if (DynamicTextIndicator())
        {
        TRAP_IGNORE(SetupDynamicIndicatorTextL(Size().iWidth));
        }
    }

void CAknIndicator::SetIndicatorFader(CAknIndicatorFader* aFader)
    {
    if (iExtension)
        {
        iExtension->iFader = aFader;
        }
    }
/**
 *
 */
void CAknIndicator::HandleResourceChange( TInt aType )
    {
    CCoeControl::HandleResourceChange( aType );
    if ( aType == KEikDynamicLayoutVariantSwitch || aType == KEikColorResourceChange ||
        aType == KAknsMessageSkinChange )
        {
        DeleteBitmaps();
        SizeChanged(); // reloads bitmaps if needed.
        DrawDeferred();
        }
    }

TRgb CAknIndicator::SelectColor(TInt aLayoutMode) const
    {
    TRgb color( KRgbGray );
    TAknsItemID colorGroup;
    colorGroup.Set(0,0);
    TInt colorIndex = 0;
    SelectColorSkin(aLayoutMode, colorGroup, colorIndex);
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    AknsUtils::GetCachedColor( skin, color, colorGroup, colorIndex );
    return color;
    }

TRgb CAknIndicator::ActiveColor(TInt aLayoutMode)
    {
    TRgb color( KRgbGray );
    TAknsItemID colorGroup;
    colorGroup.Set(0,0);
    TInt colorIndex = 0;
    ActiveColorSkin(aLayoutMode, colorGroup, colorIndex);
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    AknsUtils::GetCachedColor( skin, color, colorGroup, colorIndex );
    return color;
    }

EXPORT_C void CAknIndicator::HandlePointerEventL(
    const TPointerEvent& aPointerEvent )
    {
    CCoeControl::HandlePointerEventL( aPointerEvent );
    }

EXPORT_C void CAknIndicator::SetIndicatorObserver(
    MAknIndicatorObserver* /*aIndicatorObserver*/ )
    {
    // Use of this method is deprecated.
    // Empty implementation is left here just for preserving binary compatibility
    }

void CAknIndicator::SetupDynamicIndicatorTextL(TInt aWidth)
    {
    __ASSERT_ALWAYS( iIndicatorTypeText, Panic(EAknPanicOutOfRange));

    if (DynamicTextIndicator())
        {
        delete iExtension->iDynamicIndicatorText;
        iExtension->iDynamicIndicatorText = NULL;

        if (iIndicatorText)
            {
            TAknTextComponentLayout line;
            if (AknStatuspaneUtils::SmallLayoutActive() || AknStatuspaneUtils::StaconPaneActive())
                {
                line = AknLayoutScalable_Avkon::status_small_pane_t1(0);
                }
            else
                {
                TAknWindowComponentLayout layout( AknLayoutScalable_Avkon::navi_text_pane(0) );
                TAknTextComponentLayout l2( AknLayoutScalable_Avkon::navi_text_pane_t1() );
                line = TAknWindowComponentLayout::ComposeText( layout, l2 );
                }

            const CFont* fontUsed = AknLayoutUtils::FontFromId( line.LayoutLine().FontId() );

            HBufC* clippedString = HBufC::NewLC( iIndicatorText->Length() + KAknBidiExtraSpacePerLine );
            *clippedString = *iIndicatorText;
            TPtr clippedStringPtr = clippedString->Des();
            AknBidiTextUtils::ConvertToVisualAndClipL(
                clippedStringPtr,
                *fontUsed,
                aWidth,
                aWidth);

            iExtension->iDynamicIndicatorText = clippedString;
            CleanupStack::Pop(); // clippedString
            }
        }
    }

TBool CAknIndicator::DynamicTextIndicator() const
    {
    return (iIndicatorTypeText && iExtension->iDynamicTextIndicator);
    }

HBufC* CAknIndicator::Text() const
    {
    if (DynamicTextIndicator() && iExtension->iDynamicIndicatorText)
        {
        return iExtension->iDynamicIndicatorText;
        }
    else
        {
        return iIndicatorText;
        }
    }

void CAknIndicator::SetMultiColorMode(TBool aMultiColor)
    {
    iExtension->iMultiColorMode = aMultiColor;
    }

TBool CAknIndicator::MultiColorMode() const
    {
    return iExtension->iMultiColorMode;
    }

void CAknIndicator::SetIndicatorPosition(TInt aPosition)
    {
    iExtension->iIndicatorPosition = aPosition;
    }

TInt CAknIndicator::IndicatorPosition() const
    {
    return iExtension->iIndicatorPosition;
    }


// ---------------------------------------------------------------------------
// static CAknIndicator::GetBitmapIndex
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknIndicator::GetBitmapIndexL( TInt  aIndicatorContext,
                                              TInt aIndicatorID,
                                              TInt& aBitmapIndex,
                                              TInt& aMaskIndex )
    {
    TResourceReader reader;

    TInt resourceID = 0;
    switch ( aIndicatorContext )
        {
        case CAknIndicatorContainer::EUniversalIndicators:
            {
            resourceID = R_AVKON_STATUS_PANE_INDICATOR_DEFAULT;
            break;
            }
        case CAknIndicatorContainer::ENaviPaneEditorIndicators:
        case CAknIndicatorContainer::EQueryEditorIndicators: // fallthrough
            {
            resourceID = R_AVKON_NAVI_PANE_EDITOR_INDICATORS;
            break;
            }
        default:
            {
            resourceID = KErrNotFound;
            break;
            }
        }

    TInt indicatorCount = 0;
    if ( resourceID != KErrNotFound )
        {
        CCoeEnv::Static()->CreateResourceReaderLC(
            reader,
            resourceID );
        indicatorCount = reader.ReadInt16();
        }
    else
        {
        aBitmapIndex = KErrNotFound;
        aMaskIndex = KErrNotFound;
        }

    for ( TInt ii = 0; ii < indicatorCount; ii++ )
        {
        TInt foundUid = reader.ReadInt16();
        if ( foundUid == aIndicatorID )
            {
            reader.ReadInt16(); // narrow priority
            reader.ReadInt16(); // wide priority
            HBufC* bitmapFile = reader.ReadHBufCL();
            CleanupStack::PushL( bitmapFile );

            TInt stateCount = reader.ReadInt16();
            TInt state      = reader.ReadInt16();
            TInt iconCount  = reader.ReadInt16();

            if ( state == EAknIndicatorStateAnimate )
                {
                for ( TInt j = 0; j < iconCount - 1; j++ )
                    {
                    // Use the last animation frame
                    // in case of animated indicator.
                    reader.ReadInt16();
                    reader.ReadInt16();
                    reader.ReadInt16();
                    reader.ReadInt16();
                    }
                }

            aBitmapIndex = reader.ReadInt16();
            aMaskIndex   = reader.ReadInt16();


            if ( aBitmapIndex == KErrNotFound )
                {
                aBitmapIndex = reader.ReadInt16();
                aMaskIndex   = reader.ReadInt16();
                }

            CleanupStack::PopAndDestroy( bitmapFile );
            break;
            }
        else
		 	{
	    	reader.ReadInt16();
	    	reader.ReadInt16();
	    	HBufC* bitmapFile = reader.ReadHBufCL(); // bmp filename
	    	delete bitmapFile;
	    	bitmapFile = NULL;
		    TInt numberOfStates = reader.ReadInt16();  // Number of states
	    	for ( TInt j = 0; j < numberOfStates; j++ )
	        	{
	        	reader.ReadInt16(); // State id
				TInt numberOfIcons = reader.ReadInt16();
			    for ( TInt jj = 0; jj < numberOfIcons; jj++ )
			        {
			        for ( TInt jjj = CAknIndicator::ELayoutModeUsual; jjj <= CAknIndicator::ELayoutModeWide; jjj++ )
			            {
		                reader.ReadInt16(); // bitmaps
		                reader.ReadInt16(); // mask
			            }
	                }
	            }
	        }
        }

    if ( resourceID != KErrNotFound )
        {
        CleanupStack::PopAndDestroy(); // reader
        }
    }

void CAknIndicator::SelectColorSkin( TInt aLayoutMode,
                                     TAknsItemID& aColorGroup,
                                     TInt& aColorIndex ) const
    {
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();

    switch( iIndicatorContext )
        {
        case CAknIndicatorContainer::ENaviPaneEditorIndicators:
            if ( AknStatuspaneUtils::StaconPaneActive() ||
                 ( AknStatuspaneUtils::SmallLayoutActive() &&
                   Layout_Meta_Data::IsLandscapeOrientation() ) )
                {
                if (iIndicatorTypeText)
                    {
                    aColorGroup = KAknsIIDQsnTextColors;
                    aColorIndex = EAknsCIQsnTextColorsCG43;
                    }
                else
                    {
                    aColorGroup = KAknsIIDQsnIconColors;
                    aColorIndex = EAknsCIQsnIconColorsCG22;
                    }
                }
            else
                {
                if (iIndicatorTypeText)
                    {
                    aColorGroup = KAknsIIDQsnTextColors;
                    aColorIndex = EAknsCIQsnTextColorsCG2;
                    }
                else
                    {
                    aColorGroup = KAknsIIDQsnIconColors;
                    aColorIndex = EAknsCIQsnIconColorsCG4;
                    }
                }
            break;

        case CAknIndicatorContainer::EUniversalIndicators:
            if (AknStatuspaneUtils::StaconPaneActive())
                {
                // Status indicators in stacon pane
                if (AknStatuspaneUtils::IdleLayoutActive() && !AknStatuspaneUtils::ExtendedStaconPaneActive())
                    {
                    // Idle is similar to portraid, but it is not used if extended stacon is active.
                    aColorGroup = KAknsIIDQsnIconColors;
                    aColorIndex = EAknsCIQsnIconColorsCG1;
                    }
                else
                    {
                    // usual has own color group
                    aColorGroup = KAknsIIDQsnIconColors;
                    aColorIndex = EAknsCIQsnIconColorsCG20;
                    }
                }
            else if (AknStatuspaneUtils::FlatLayoutActive())
                {
                if (AknStatuspaneUtils::ExtendedFlatLayoutActive())
                    {
                    // TODO: NO colors specified yet, use left cba colors
                    if (AknStatuspaneUtils::IdleLayoutActive())
                        {
                        aColorGroup = KAknsIIDQsnTextColors;
                        aColorIndex = EAknsCIQsnTextColorsCG15;
                        }
                    else
                        {
                        aColorGroup = KAknsIIDQsnTextColors;
                        aColorIndex = EAknsCIQsnTextColorsCG13;
                        }

                    }
                else
                    {
                    if (AknStatuspaneUtils::IdleLayoutActive())
                        {
                        // Idle is similar to portraid
                        aColorGroup = KAknsIIDQsnIconColors;
                        aColorIndex = EAknsCIQsnIconColorsCG1;
                        }
                    else
                        {
                        // Flat usual uses stacon pane color group
                        aColorGroup = KAknsIIDQsnIconColors;
                        aColorIndex = EAknsCIQsnIconColorsCG20;
                        }
                    }
                }
            else if ( AknStatuspaneUtils::HDLayoutActive() )
                {
                aColorGroup = KAknsIIDQsnIconColors;
                aColorIndex = EAknsCIQsnIconColorsCG20;
                }
            else
                {
                if( aLayoutMode == ELayoutModeWide )
                    {
                    // Status indicators (in idle)
                    aColorGroup = KAknsIIDQsnIconColors;
                    aColorIndex = EAknsCIQsnIconColorsCG1;
                    }
                else
                    {
                    // Universal indicators
                    aColorGroup = KAknsIIDQsnIconColors;
                    aColorIndex = EAknsCIQsnIconColorsCG2;
                    }
                }
            break;

        case CAknIndicatorContainer::EQueryEditorIndicators:
        case CAknIndicatorContainer::EFindIndicators:
            {
            aColorGroup = KAknsIIDQsnIconColors;
            aColorIndex = EAknsCIQsnIconColorsCG10;
            }
            break;

        default:
            return;
        }
    }


void CAknIndicator::ActiveColorSkin( TInt aLayoutMode,
                                     TAknsItemID& aColorGroup,
                                     TInt& aColorIndex ) const
    {
    aColorGroup = iExtension->iIndicatorColorGroup[aLayoutMode];
    aColorIndex = iExtension->iIndicatorColorIndex[aLayoutMode];
    }


void CAknIndicator::DeleteBitmaps()
    {
    if ( iIndicatorBitmaps[ELayoutModeUsual] )
        {
        TInt count = iIndicatorBitmaps[ELayoutModeUsual]->Count();
        for ( TInt ii = 0; ii < count; ii++ )
            {
            delete iIndicatorBitmaps[ELayoutModeUsual]->At( ii );
            }
        iIndicatorBitmaps[ELayoutModeUsual]->Reset();
        }

    if ( iIndicatorBitmaps[ELayoutModeWide] )
        {
        TInt count = iIndicatorBitmaps[ELayoutModeWide]->Count();
        for ( TInt ii = 0; ii < count; ii++ )
            {
            delete iIndicatorBitmaps[ELayoutModeWide]->At( ii );
            }
        iIndicatorBitmaps[ELayoutModeWide]->Reset();
        }
    iExtension->iIndicatorBitmapsCreated = EFalse;
    }

//  End of File
