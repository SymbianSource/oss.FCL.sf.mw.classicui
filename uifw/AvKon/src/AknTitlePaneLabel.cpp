/*
* Copyright (c) 2005-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implementation of title pane's label.
*
*/


// SYSTEM INCLUDES
#include <e32def.h>
#include <AknPictographInterface.h>
#include <AknPictographDrawerInterface.h>
#include <bidivisual.h>
#include <biditext.h>
#include <akniconconfig.h>
#include <layoutmetadata.cdl.h>

#include <AknTasHook.h> // for testability hooks
// USER INCLUDES
#include "AknTitlePaneLabel.h"
#include "AknUtils.h"
#include "AknLayoutFont.h"
#include "aknappui.h"
#include "AknBidiTextUtils.h"
#include "AknStatuspaneUtils.h"

// General effects-related constants
const TInt KScrollTimerInterval                     = 50000; // 20 events/s
const TInt KScrollTimerDelay                        = KScrollTimerInterval;
const TInt KScrollTimerDelayBeforeDirectionReversal = 3000000; // 3s
const TInt KStartValue                              = 0;
const TInt KEndValue                                = 255;
const TInt KMinInterval                             = 50000;
const TInt KScaleMagicNumber                        = 208;

// ============================ MEMBER FUNCTIONS ===============================


CAknTitlePaneLabel::CAknTitlePaneLabel()
    {
    AKNTASHOOK_ADD( this, "CAknTitlePaneLabel" );
    }


CAknTitlePaneLabel::~CAknTitlePaneLabel()
    {
    AKNTASHOOK_REMOVE();
    delete iMask;
    delete iMaskDevice;
    delete iMaskGc;

    delete iBitmap;
    delete iBitmapDevice;
    delete iBitmapGc;

    if ( iEffectTimer )
        {
        iEffectTimer->Cancel();
        delete iEffectTimer;
        ControlEnv()->RemoveForegroundObserver( *this );
        }
    delete iEffectQueue;
    delete iScrollingText;
    }


void CAknTitlePaneLabel::Draw( const TRect& aRect ) const
    {
    if ( iEffect == EEffectNone )
        {
        CEikLabel::Draw( aRect );
        }

    // Text is paused before starting to scroll,
    // drawn without truncation character.
    else if ( iEffect == EEffectPause && iPreviousEffect == EEffectNone )
        {
        // const_cast is required to call the DrawWithoutTruncation() function.
        TRAPD( err,
               const_cast<CAknTitlePaneLabel*>( this )->DrawWithoutTruncationL( aRect ) );

        if ( err != KErrNone )
            {
            CEikLabel::Draw( aRect );
            }
        }
    else
        {
        DrawWithEffect( aRect );
        }
    }


void CAknTitlePaneLabel::DrawWithoutTruncationL( const TRect& aRect )
    {
    // Copy of the truncated text in CEikLabel is made first.
    HBufC* truncatedText = HBufC::NewL( Text()->Length() );
    CleanupStack::PushL( truncatedText );

    TPtr ptr( truncatedText->Des() );
    ptr.Copy( *Text() );

    // CEikLabel's text is set to the full text and is drawn.
    SetTextL( *iScrollingText );
    CEikLabel::Draw( aRect );

    // CEikLabel's text is set back to the truncated form.
    SetTextL( ptr );

    CleanupStack::PopAndDestroy( truncatedText );
    }


void CAknTitlePaneLabel::DrawWithEffect( const TRect& aRect ) const
    {
    if ( iEffect && iBitmap && iMask && iBitmapGc && iMaskGc )
        {
        // Bitblit using mask, this creates the fade effect
        CWindowGc& gc = SystemGc();
        gc.BitBltMasked(
            iTextLayout.TextRect().iTl,
            iBitmap,
            iTextLayout.TextRect(),
            iMask,
            ETrue );
        }
    else
        {
        CEikLabel::Draw( aRect );
        }
    }


void CAknTitlePaneLabel::DrawTextWithEffect() const
    {
    switch ( iEffect )
        {
        case EEffectFadeToLeft:
        case EEffectFadeToRight:
            {
            DrawTextWithFadeEffect();
            break;
            }
        case EEffectDefaultScroll:
            {
            DrawTextWithScrollEffect();
            break;
            }
        case EEffectDefaultScrollWithFade:
        case EEffectLoopScrollWithFade:
        case EEffectScrollOnceWithFade:
        case EEffectFadeOut:
        case EEffectFadeIn:
        case EEffectToggleScrolledTextTruncation:
            {
            DrawTextWithScrollAndFadeEffect();
            break;
            }
        case EEffectPause:
        case EEffectNone:
        default:
            {
            break;
            }
        }

    if ( DrawableWindow() )
        {
        DrawDeferred();
        }

    if ( iObserver && iObserver->DrawableWindow() )
        {
        iObserver->DrawDeferred();
        }
    }


void CAknTitlePaneLabel::DrawTextWithFadeEffect() const
    {
    if ( iEffect &&
         iBitmap &&
         iMask &&
         iBitmapGc &&
         iMaskGc &&
         iTitleText &&
         iScrollingText )
        {
        InitBitmaps();
        iMaskGc->SetPenStyle( CGraphicsContext::ESolidPen );
        iMaskGc->SetBrushStyle( CGraphicsContext::ENullBrush );
        iBitmapGc->SetPenStyle( CGraphicsContext::ESolidPen );
        iBitmapGc->SetBrushStyle( CGraphicsContext::ENullBrush );

        if ( IsStrikethrough() )
            {
            iMaskGc->SetStrikethroughStyle( EStrikethroughOn );
            iBitmapGc->SetStrikethroughStyle( EStrikethroughOn );
            }
        else
            {
            iMaskGc->SetStrikethroughStyle( EStrikethroughOff );
            iBitmapGc->SetStrikethroughStyle( EStrikethroughOff );
            }

        if ( IsUnderlined() )
            {
            iMaskGc->SetUnderlineStyle( EUnderlineOn );
            iBitmapGc->SetUnderlineStyle( EUnderlineOn );
            }
        else
            {
            iMaskGc->SetUnderlineStyle( EUnderlineOff );
            iBitmapGc->SetUnderlineStyle( EUnderlineOff );
            }

        const CFont* fontUsed =
            AknLayoutUtils::FontFromId( iTextLayoutLine.FontId() );
        iBitmapGc->UseFont( fontUsed );

        // First draw with white color for masking purpose
        const CAknLayoutFont* layoutFont =
            CAknLayoutFont::AsCAknLayoutFontOrNull( fontUsed );
        TInt textPaneAscent( 0 );
        if ( layoutFont )
            {
            textPaneAscent = layoutFont->TextPaneTopToBaseline();
            }
        else
            {
            textPaneAscent = fontUsed->AscentInPixels();
            }

        CGraphicsContext::TTextAlign textAlign( CGraphicsContext::ELeft );
        if( AknLayoutUtils::LayoutMirrored() )
            {
            textAlign = CGraphicsContext::ERight;
            }

        iBitmapGc->SetPenColor( KRgbWhite );
        iBitmapGc->DrawText( *iScrollingText,
                             iTextLayout.TextRect(),
                             textPaneAscent,
                             textAlign,
                             0 );

        // Draw pictographs
        if ( iPictographInterface )
            {
            iPictographInterface->Interface()->DrawPictographsInText(
                *iBitmapGc,
                *fontUsed,
                *iScrollingText,
                iTextLayout.TextRect(),
                textPaneAscent,
                textAlign,
                0 );
            }

        // Draw text to mask
        iMaskGc->BitBltMasked(
            Rect().iTl,
            iBitmap,
            TRect( iBitmap->SizeInPixels() ),
            iBitmap,
            ETrue );

        TRgb color( KRgbBlack );
        if ( IsDimmed() )
            {
            color = iEikonEnv->ControlColor( EColorLabelDimmedText, *this );
            }
        else
            {
            color = iEikonEnv->ControlColor( EColorLabelText, *this );
            }

        iBitmapGc->SetPenColor( color );
        iBitmapGc->DrawText( *iScrollingText,
                             iTextLayout.TextRect(),
                             textPaneAscent,
                             textAlign,
                             0 );

        // Draw pictographs
        if ( iPictographInterface )
            {
            iPictographInterface->Interface()->DrawPictographsInText(
                *iBitmapGc,
                *fontUsed,
                *iScrollingText,
                iTextLayout.TextRect(),
                textPaneAscent,
                textAlign,
                0 );
            }

        iBitmapGc->DiscardFont(); // Release the font cache
        }
    }

void CAknTitlePaneLabel::DrawTextWithScrollEffect() const
    {
    if ( iEffect &&
         iBitmap &&
         iMask &&
         iBitmapGc &&
         iMaskGc &&
         iTitleText &&
         iScrollingText )
        {
        InitBitmaps();
        iMaskGc->SetPenStyle( CGraphicsContext::ESolidPen );
        iMaskGc->SetBrushStyle( CGraphicsContext::ENullBrush );
        iBitmapGc->SetPenStyle( CGraphicsContext::ESolidPen );
        iBitmapGc->SetBrushStyle( CGraphicsContext::ENullBrush );

        TRect rect( iScrollRect );

        TRgb color( KRgbBlack );
        if ( IsDimmed() )
            {
            color = iEikonEnv->ControlColor( EColorLabelDimmedText, *this );
            }
        else
            {
            color = iEikonEnv->ControlColor( EColorLabelText, *this );
            }

        const CFont* fontUsed =
            AknLayoutUtils::FontFromId( iTextLayoutLine.FontId() );
        const CAknLayoutFont* layoutFont =
            CAknLayoutFont::AsCAknLayoutFontOrNull( fontUsed );
        TInt textPaneAscent( 0 );
        if ( layoutFont )
            {
            textPaneAscent = layoutFont->TextPaneTopToBaseline();
            }
        else
            {
            textPaneAscent = fontUsed->AscentInPixels();
            }

        CGraphicsContext::TTextAlign textAlign( CGraphicsContext::ELeft );

        if ( iWesternText )
            {
            rect.iTl.iX -= iScrollPosition;
            }
        else
            {
            rect.iBr.iX += iScrollPosition;
            textAlign = CGraphicsContext::ERight;
            }

        iBitmapGc->SetPenColor( KRgbWhite );
        iBitmapGc->UseFont( fontUsed );

        TBool truncated = Text()->Locate( KEllipsis ) != KErrNotFound;
        if ( !iScrollPosition && truncated )
            {
            // Draw truncated text
            iBitmapGc->DrawText( *Text(), rect, textPaneAscent, textAlign, 0 );
            // Draw pictographs
            if ( iPictographInterface )
                {
                iPictographInterface->Interface()->DrawPictographsInText(
                    *iBitmapGc,
                    *fontUsed,
                    *Text(),
                    rect,
                    textPaneAscent,
                    textAlign,
                    0 );
                }
            }
        else if ( iScrollingText )
            {
            // Draw non-truncated text
            iBitmapGc->DrawText( *iScrollingText,
                                 rect,
                                 textPaneAscent,
                                 textAlign,
                                 0 );
            // Draw pictographs
            if ( iPictographInterface )
                {
                iPictographInterface->Interface()->DrawPictographsInText(
                    *iBitmapGc,
                    *fontUsed,
                    *iScrollingText,
                    rect,
                    textPaneAscent,
                    textAlign,
                    0 );
                }
            }

        // Draw text to mask
        iMaskGc->BitBltMasked(
            Rect().iTl,
            iBitmap,
            TRect( iBitmap->SizeInPixels() ),
            iBitmap,
            ETrue );

        iBitmapGc->SetPenColor( color );

        if ( !iScrollPosition && truncated )
            {
            // Draw truncated text
            iBitmapGc->DrawText( *Text(), rect, textPaneAscent, textAlign, 0 );
            // Draw pictographs
            if ( iPictographInterface )
                {
                iPictographInterface->Interface()->DrawPictographsInText(
                    *iBitmapGc,
                    *fontUsed,
                    *Text(),
                    rect,
                    textPaneAscent,
                    textAlign,
                    0 );
                }
            }
        else if ( iScrollingText )
            {
            // Draw non-truncated text
            iBitmapGc->DrawText( *iScrollingText,
                                 rect,
                                 textPaneAscent,
                                 textAlign,
                                 0 );
            // Draw pictographs
            if ( iPictographInterface )
                {
                iPictographInterface->Interface()->DrawPictographsInText(
                    *iBitmapGc,
                    *fontUsed,
                    *iScrollingText,
                    rect,
                    textPaneAscent,
                    textAlign,
                    0 );
                }
            }

        iBitmapGc->DiscardFont(); // Release the font cache
        }
    }


void CAknTitlePaneLabel::DrawTextWithScrollAndFadeEffect() const
    {
    DrawTextWithScrollEffect();
    }


void CAknTitlePaneLabel::SetTextEffect( TInt aEffect,
                                        TRect aEffectRect,
                                        TInt aEffectDuration,
                                        TRect aLabelRect,
                                        TAknLayoutText aTextLayout,
                                        TAknTextLineLayout aTextLayoutLine,
                                        HBufC* aTitleText,
                                        CCoeControl* aObserver)
    {
    iPreviousEffect = iEffect;

    iObserver = aObserver;
    iTextLayout = aTextLayout;
    iTextLayoutLine = aTextLayoutLine;

    if ( ( iTitleText != aTitleText && iScrollingText ) ||
         ( !iScrollingText && aEffect ) )
        {
        TRAP_IGNORE( CreateScrollingTextL( aTitleText ) );
        }

    iTitleText = aTitleText;
    iEffectDuration = aEffectDuration;

    iWesternText =
        TBidiText::TextDirectionality( *Text() ) == TBidiText::ELeftToRight;

    if ( aEffect == EEffectScrollOnceWithFade ||
         aEffect == EEffectLoopScrollWithFade ||
         aEffect == EEffectLoopScroll ||
         aEffect == EEffectDefaultScrollWithFade ||
         aEffect == EEffectDefaultScroll )
        {
        iScrollPosition = 0;
        }

    iScrollRect = iTextLayout.TextRect();
    if ( iScrollRect.iTl.iX < aEffectRect.iTl.iX )
        {
        iScrollRect.iTl.iX = aEffectRect.iTl.iX;
        }
    if ( iScrollRect.iBr.iX > aEffectRect.iBr.iX )
        {
        iScrollRect.iBr.iX = aEffectRect.iBr.iX;
        }

    const CFont* fontUsed =
        AknLayoutUtils::FontFromId( aTextLayoutLine.FontId() );
    CFont::TMeasureTextInput input;
    input.iFlags = CFont::TMeasureTextInput::EFVisualOrder;
    iTextLength = fontUsed->MeasureText( *aTitleText, &input );

    iOperatorNamePhase = 0;

    if ( !aEffect ||
         iEffect != aEffect ||
         iEffectRect != aEffectRect ||
         Rect() != aLabelRect )
        {
        iEffect = aEffect;
        iEffectRect = aEffectRect;
        if ( !iEffect )
            {
            TRgb color( iEikonEnv->ControlColor( EColorLabelText, *this ) );
            // We cast here a bit dangerously, this might be changed someday.
            TAknMultiLineTextLayout* multilinePtr = NULL;
            multilinePtr =
                static_cast<TAknMultiLineTextLayout*> ( &aTextLayoutLine );
            AknLayoutUtils::LayoutLabel(this, aLabelRect, *multilinePtr);
            // Layoutlabel loses the color, set it back to right one
            TRAP_IGNORE(
                AknLayoutUtils::OverrideControlColorL(
                    *this, EColorLabelText, color ) );
            }
        else
            {
            if ( aEffect != EEffectPause )
                {
                SetRect( aLabelRect );
                }
            }

        iEffectLabelSize = Size();

        TInt error = KErrNone;
        TRAP( error, InitEffectL() );
        if ( error != KErrNone )
            {
            iEffect = EEffectNone;
            }
        }

    // Do effect event at least once
    DoEffectEvent();

    // Setup timer for furter effect events if needed
    if ( iEffect != EEffectPause )
        {
        TRAP_IGNORE( InitTimerL( KScrollTimerDelay, KScrollTimerInterval ) );
        }
    }


TInt CAknTitlePaneLabel::TextEffect()
    {
    return iEffect;
    }


void CAknTitlePaneLabel::InitEffectL()
    {
    if ( EffectBitmapsNeeded( iEffect ) )
        {
        delete iMask;
        iMask = NULL;
        delete iMaskDevice;
        iMaskDevice = NULL;
        delete iMaskGc;
        iMaskGc = NULL;

        delete iBitmap;
        iBitmap = NULL;
        delete iBitmapDevice;
        iBitmapDevice = NULL;
        delete iBitmapGc;
        iBitmapGc = NULL;

        iMask = new (ELeave) CFbsBitmap();
        iMask->Create( Size(), EGray256 );
        iMaskDevice = CFbsBitmapDevice::NewL( iMask );
        iMaskDevice->CreateContext( iMaskGc );

        AknIconConfig::TPreferredDisplayMode mode;
        AknIconConfig::PreferredDisplayMode(
            mode,
            AknIconConfig::EImageTypeOffscreen );

        iBitmap = new (ELeave) CFbsBitmap();
        iBitmap->Create( Size(), mode.iBitmapMode );
        iBitmapDevice = CFbsBitmapDevice::NewL( iBitmap );
        iBitmapDevice->CreateContext( iBitmapGc );

        InitBitmaps();
        }
    }


void CAknTitlePaneLabel::InitTimerL( TInt aDelay, TInt aInterval )
    {
    CancelTimer();

    if ( EffectEventsNeeded( iEffect ) )
        {
        if ( !iEffectTimer )
            {
            iEffectTimer = CPeriodic::NewL( CActive::EPriorityIdle );
            ControlEnv()->AddForegroundObserverL( *this );
            }

        if ( !iEffectTimer->IsActive() )  // start timer if not already started
            {
            iEffectTimer->Start(
                TTimeIntervalMicroSeconds32( aDelay ),
                TTimeIntervalMicroSeconds32( aInterval ),
                TCallBack( CAknTitlePaneLabel::EffectEvent, this ) );
            }
        }
    else
        {
        iScrollPosition = 0;
        }
    }


void CAknTitlePaneLabel::CancelTimer()
    {
    if ( iEffectTimer && iEffectTimer->IsActive() )
        {
        iEffectTimer->Cancel();
        }
    }


void CAknTitlePaneLabel::InitBitmaps() const
    {
    iBitmapGc->SetPenColor( KRgbBlack );
    iBitmapGc->SetPenStyle( CGraphicsContext::ENullPen );
    iBitmapGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
    iBitmapGc->SetBrushColor( KRgbBlack );
    iBitmapGc->DrawRect( TRect( Size() ) );

    iMaskGc->SetPenColor( KRgbBlack );
    iMaskGc->SetPenStyle( CGraphicsContext::ENullPen );
    iMaskGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
    iMaskGc->SetBrushColor( KRgbWhite );
    iMaskGc->DrawRect( TRect( Size() ) );

    iMaskGc->SetPenStyle( CGraphicsContext::ESolidPen );
    iMaskGc->SetBrushStyle( CGraphicsContext::ENullBrush );

    TInt width = iEffectRect.Width();

    TRect parentRect( Rect() );

    TBool isLandscape( Layout_Meta_Data::IsLandscapeOrientation() );
    TBool flatSp( AknStatuspaneUtils::FlatLayoutActive() );

    switch ( iEffect )
        {
        case EEffectFadeToLeft:
            {
            TInt KMaxFadeSteps = KEndValue - KStartValue;
            TInt usedFadeStep = 0;
            TInt usedDrawStep = 1;

            if ( width < KMaxFadeSteps &&
                 width != 0)
                {
                usedFadeStep = KMaxFadeSteps / width;
                }
            else
                {
                usedFadeStep = 1;
                usedDrawStep = width / KMaxFadeSteps;
                }

            TInt startValue( KStartValue );

            // In portrait mode flat status pane layout
            // we fade the text fully, because the navi
            // pane content and title pane can't be displayed
            // at the same time.

            TRgb rgb;
            rgb.SetRed( startValue );
            rgb.SetGreen( startValue );
            rgb.SetBlue( startValue );

            TRect rect;
            for ( TInt x = 0; x < width; x += usedDrawStep )
                {
                iMaskGc->SetPenColor( rgb );
                iMaskGc->SetBrushColor( rgb );
                rect.iTl.iX = iEffectRect.iTl.iX + x;
                rect.iTl.iY = 0;
                rect.iBr.iX = rect.iTl.iX + usedDrawStep;
                rect.iBr.iY = rect.iTl.iY + parentRect.Height();

                iMaskGc->DrawRect( rect );
                rgb.SetRed( rgb.Red() + usedFadeStep );
                rgb.SetGreen( rgb.Green() + usedFadeStep );
                rgb.SetBlue( rgb.Blue() + usedFadeStep );
                }

            iMaskGc->SetPenStyle( CGraphicsContext::ENullPen );
            iMaskGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
            iMaskGc->SetPenColor( KRgbBlack );
            iMaskGc->SetBrushColor( KRgbBlack );
            iMaskGc->DrawRect( TRect( parentRect.iTl.iX,
                                      parentRect.iTl.iY,
                                      iEffectRect.iTl.iX,
                                      parentRect.iBr.iY ) );
            break;
            }
        case EEffectFadeToRight:
            {
            TInt KMaxFadeSteps = KEndValue - KStartValue;
            TInt usedFadeStep = 0;
            TInt usedDrawStep = 1;


            if ( width < KMaxFadeSteps &&
                 width != 0 )
                {
                usedFadeStep = KMaxFadeSteps / width;
                }
            else
                {
                usedFadeStep = 1;
                usedDrawStep = width / KMaxFadeSteps;
                }

            TInt startValue( KStartValue );

            // In portrait mode flat status pane layout
            // we fade the text fully, because the navi
            // pane content and title pane can't be displayed
            // at the same time.

            TRgb rgb;
            rgb.SetRed( startValue );
            rgb.SetGreen( startValue );
            rgb.SetBlue( startValue );

            TRect rect;
            for ( TInt x = width - 1; x >= 0; x -= usedDrawStep )
                {
                iMaskGc->SetPenColor( rgb );
                iMaskGc->SetBrushColor( rgb );
                rect.iTl.iX = iEffectRect.iTl.iX + x;
                rect.iTl.iY = 0;
                rect.iBr.iX = rect.iTl.iX + usedDrawStep;
                rect.iBr.iY = rect.iTl.iY + parentRect.Height();
                iMaskGc->DrawRect( rect );
                rgb.SetRed( rgb.Red() + usedFadeStep );
                rgb.SetGreen( rgb.Green() + usedFadeStep );
                rgb.SetBlue( rgb.Blue() + usedFadeStep );
                }

            iMaskGc->SetPenStyle( CGraphicsContext::ENullPen );
            iMaskGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
            iMaskGc->SetPenColor( KRgbBlack );
            iMaskGc->SetBrushColor( KRgbBlack );
            iMaskGc->DrawRect( TRect( iEffectRect.iBr.iX,
                                      parentRect.iTl.iY,
                                      parentRect.iBr.iX,
                                      parentRect.iBr.iY ) );
            break;
            }
        case EEffectDefaultScrollWithFade:
        case EEffectLoopScrollWithFade:
        case EEffectScrollOnceWithFade:
            {
            if ( !TextNeedsTruncation() || iScrollPosition == 0 )
                {
                return; // No need to fade if not even scrolled.
                }

            // We fade about 5-10% of the text area end/start to make
            // scrolling text appear/disappear smoother.
            width = iEffectRect.Width() / 30;
            TRect leftFadeEffectRect( iEffectRect );
            leftFadeEffectRect.iBr.iX = leftFadeEffectRect.iTl.iX + width;

            TRect rightFadeEffectRect = iEffectRect;
            rightFadeEffectRect.iTl.iX = rightFadeEffectRect.iBr.iX - width;

            TInt KMaxFadeSteps = KEndValue - KStartValue;
            TInt usedFadeStep  = 0;
            TInt usedDrawStep  = 1;

            if ( width < KMaxFadeSteps &&
                 width != 0 )
                {
                usedFadeStep = KMaxFadeSteps / width;
                }
            else
                {
                usedFadeStep = 1;
                usedDrawStep = width / KMaxFadeSteps;
                }

            TRgb rgb;
            rgb.SetRed( KStartValue );
            rgb.SetGreen( KStartValue );
            rgb.SetBlue( KStartValue );

            TRect rect;
            for ( TInt x = 0; x < width; x += usedDrawStep )
                {
                iMaskGc->SetPenColor( rgb );
                iMaskGc->SetBrushColor( rgb );
                rect.iTl.iX = leftFadeEffectRect.iTl.iX + x;
                rect.iTl.iY = 0;
                rect.iBr.iX = rect.iTl.iX + usedDrawStep;
                rect.iBr.iY = rect.iTl.iY + parentRect.Height();

                iMaskGc->DrawRect( rect );
                rgb.SetRed( rgb.Red() + usedFadeStep );
                rgb.SetGreen( rgb.Green() + usedFadeStep );
                rgb.SetBlue( rgb.Blue() + usedFadeStep );
                }

            iMaskGc->SetPenStyle( CGraphicsContext::ENullPen );
            iMaskGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
            iMaskGc->SetPenColor( KRgbBlack );
            iMaskGc->SetBrushColor( KRgbBlack );
            iMaskGc->DrawRect( TRect( parentRect.iTl.iX,
                                      parentRect.iTl.iY,
                                      leftFadeEffectRect.iTl.iX,
                                      parentRect.iBr.iY ) );


            iMaskGc->SetPenStyle( CGraphicsContext::ESolidPen );
            iMaskGc->SetBrushStyle( CGraphicsContext::ENullBrush );

            KMaxFadeSteps = KEndValue - KStartValue;
            usedFadeStep  = 0;
            usedDrawStep  = 1;

            if ( width < KMaxFadeSteps &&
                 width != 0 )
                {
                usedFadeStep = KMaxFadeSteps / width;
                }
            else
                {
                usedFadeStep = 1;
                usedDrawStep = width / KMaxFadeSteps;
                }

            rgb.SetRed( KStartValue );
            rgb.SetGreen( KStartValue );
            rgb.SetBlue( KStartValue );

            for ( TInt x = width - 1; x >= 0; x -= usedDrawStep )
                {
                iMaskGc->SetPenColor( rgb );
                iMaskGc->SetBrushColor( rgb );
                rect.iTl.iX = rightFadeEffectRect.iTl.iX + x;
                rect.iTl.iY = 0;
                rect.iBr.iX = rect.iTl.iX + usedDrawStep;
                rect.iBr.iY = rect.iTl.iY + parentRect.Height();

                iMaskGc->DrawRect( rect );
                rgb.SetRed( rgb.Red() + usedFadeStep );
                rgb.SetGreen( rgb.Green() + usedFadeStep );
                rgb.SetBlue( rgb.Blue() + usedFadeStep );
                }

            iMaskGc->SetPenStyle( CGraphicsContext::ENullPen );
            iMaskGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
            iMaskGc->SetBrushColor( KRgbBlack );
            iMaskGc->DrawRect( TRect( rightFadeEffectRect.iBr.iX,
                                      parentRect.iTl.iY,
                                      parentRect.iBr.iX,
                                      parentRect.iBr.iY ) );
            break;
            }
        case EEffectFadeOut:
        case EEffectFadeIn:
            {
            TRgb fadeRgb;
            fadeRgb.SetRed( iFadeInOutValue );
            fadeRgb.SetGreen( iFadeInOutValue );
            fadeRgb.SetBlue( iFadeInOutValue );
            iMaskGc->SetPenStyle( CGraphicsContext::ENullPen );
            iMaskGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
            iMaskGc->SetPenColor( fadeRgb );
            iMaskGc->SetBrushColor( fadeRgb );
            iMaskGc->DrawRect( iEffectRect );

            iMaskGc->SetPenStyle( CGraphicsContext::ENullPen );
            iMaskGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
            iMaskGc->SetPenColor( KRgbBlack );
            iMaskGc->SetBrushColor( KRgbBlack );
            iMaskGc->DrawRect( TRect( parentRect.iTl.iX,
                                      parentRect.iTl.iY,
                                      iEffectRect.iTl.iX,
                                      parentRect.iBr.iY ) );
            break;
            }
        case EEffectPause:
        case EEffectNone:
        case EEffectToggleScrolledTextTruncation:
        case EEffectDefaultScroll:
        default:
            {
            break;
            }
        }
    }


CFbsBitmap* CAknTitlePaneLabel::TextAsBitmap()
    {
    if ( iEffect != EEffectNone )
        {
        return iBitmap;
        }
    else
        {
        return NULL;
        }
    }


CFbsBitmap* CAknTitlePaneLabel::TextAsMask()
    {
    if ( iEffect != EEffectNone )
        {
        return iMask;
        }
    else
        {
        return NULL;
        }
    }


void CAknTitlePaneLabel::HandleGainingForeground()
    {
    TRAP_IGNORE( InitTimerL( KScrollTimerDelay, KScrollTimerInterval ) );
    }

void CAknTitlePaneLabel::HandleLosingForeground()
    {
    CancelTimer();
    }


TInt CAknTitlePaneLabel::EffectEvent( TAny* aPtr )
    {
    static_cast<CAknTitlePaneLabel*> ( aPtr )->DoEffectEvent();
    return ETrue;
    }


TBool CAknTitlePaneLabel::DoDefaultScrollEffectEvent()
    {
    TBool done( EFalse );
    if ( !TextNeedsTruncation() )
        {
        iScrollStep = 0;
        done        = ETrue;
        }

    if ( iScrollDirectionBackwards )
        {
        iScrollStep = -ScrollStepInPixels();
        if ( iScrollPosition == 0 )
            {
            // If text is at the other end, switch
            // scrolling direction and continue.
            iScrollDirectionBackwards = EFalse;
            TRAP_IGNORE(
                InitTimerL(
                    KScrollTimerDelayBeforeDirectionReversal,
                    KScrollTimerInterval ) ); // Make a littler longer delay at the ends
            }
        }
    else
        {
        iScrollStep = ScrollStepInPixels();
        if ( iScrollPosition + iScrollRect.Width() > iTextLength + iScrollRect.Width() / 10 )
            {
            // If text is at the other end, switch scrolling direction and continue
            iScrollDirectionBackwards = ETrue;
            TRAP_IGNORE(
                InitTimerL(
                    KScrollTimerDelayBeforeDirectionReversal,
                    KScrollTimerInterval ) ); // Make a littler longer delay at the ends
            }
        }
    iScrollPosition += iScrollStep;
    return done;
    }


TBool CAknTitlePaneLabel::DoLoopScrollEffectEvent()
    {
    TBool done( EFalse );
    if ( !TextNeedsTruncation() )
        {
        iScrollStep = 0;
        done        = ETrue;
        }

    iScrollStep = ScrollStepInPixels();
    if ( iScrollPosition > iTextLength + iScrollRect.Width() / 10 )
        {
        // If text has scrolled away from screen, start again from the other end
        iScrollPosition = -iScrollRect.Width();
        }
    iScrollPosition += iScrollStep;
    return done;
    }


TBool CAknTitlePaneLabel::DoScrollOnceEffectEvent()
    {
    TBool done( EFalse );
    if ( !TextNeedsTruncation() )
        {
        iScrollStep = 0;
        done        = ETrue;
        }
    else
        {
        iScrollStep = ScrollStepInPixels();
        if ( iScrollPosition + iScrollRect.Width() > iTextLength + iScrollRect.Width() / 10 )
            {
            // If text is at the other end, continue with fade after timout
            iScrollStep = 0;
            done        = ETrue;
            }
        }
    iScrollPosition += iScrollStep;
    return done;
    }


TBool CAknTitlePaneLabel::DoFadeInEffectEvent()
    {
    TBool done( EFalse );
    if ( iEffectDuration )
        {
        TInt interval = iEffectDuration / KEndValue;

        if ( interval < KMinInterval )
            {
            interval = KMinInterval;
            iFadeInOutStep = iEffectDuration / KMinInterval;
            }
        else
            {
            iFadeInOutStep = 1;
            }

        if ( iFadeInOutStep < 1 )
            {
            iFadeInOutStep = 1;
            }
        if ( iFadeInOutStep > KEndValue )
            {
            iFadeInOutStep = KEndValue;
            }

        TRAP_IGNORE( InitTimerL( interval, interval ) );

        iEffectDuration = 0;
        iFadeInOutValue = 0; // start from fully invisible
        }

    if ( iFadeInOutValue + iFadeInOutStep > KEndValue )
        {
        iFadeInOutValue = KEndValue;
        done = ETrue;
        }
    else
        {
        iFadeInOutValue += iFadeInOutStep;
        }

    return done;
    }

TBool CAknTitlePaneLabel::DoFadeOutEffectEvent()
    {
    TBool done( EFalse );
    if ( iEffectDuration )
        {
        TInt interval = iEffectDuration / KEndValue;

        if ( interval < KMinInterval )
            {
            interval = KMinInterval;
            iFadeInOutStep = iEffectDuration / KMinInterval;
            }
        else
            {
            iFadeInOutStep = 1;
            }

        if ( iFadeInOutStep < 1 )
            {
            iFadeInOutStep = 1;
            }
        if ( iFadeInOutStep > KEndValue )
            {
            iFadeInOutStep = KEndValue;
            }

        TRAP_IGNORE( InitTimerL( interval, interval ) );

        iEffectDuration = 0;
        iFadeInOutValue = KEndValue; // start from fully visible
        }

    if ( iFadeInOutValue - iFadeInOutStep < 0 )
        {
        iFadeInOutValue = 0;
        done = ETrue;
        }
    else
        {
        iFadeInOutValue -= iFadeInOutStep;
        }

    return done;
    }


TBool CAknTitlePaneLabel::DoPauseEffectEvent()
    {
    TBool done( EFalse );
    if ( iEffectDuration )
        {
        TRAP_IGNORE( InitTimerL( iEffectDuration, iEffectDuration ) );
        iEffectDuration = 0;
        }
    else
        {
        done = ETrue;
        }
    return done;
    }


TBool CAknTitlePaneLabel::DoToggleScrolledTextTruncationEffectEvent()
    {
    iScrollPosition = 0;
    return ETrue;
    }


void CAknTitlePaneLabel::DoEffectEvent()
    {
    TBool done( EFalse );

    switch ( iEffect )
        {
        case EEffectDefaultScroll:
        case EEffectDefaultScrollWithFade:
            done = DoDefaultScrollEffectEvent();
            break;
        case EEffectLoopScroll:
        case EEffectLoopScrollWithFade:
            done = DoLoopScrollEffectEvent();
            break;
        case EEffectFadeIn:
            done = DoFadeInEffectEvent();
            break;
        case EEffectFadeOut:
            done = DoFadeOutEffectEvent();
            break;
        case EEffectPause:
            done = DoPauseEffectEvent();
            break;
        case EEffectScrollOnceWithFade:
            done = DoScrollOnceEffectEvent();
            break;
        case EEffectToggleScrolledTextTruncation:
            done = DoToggleScrolledTextTruncationEffectEvent();
            break;
        default:
            iScrollStep = 0;
            done = ETrue;
            break;
        }

    // Draw text
    DrawTextWithEffect();

    // If done then process next effect
    if ( done )
        {
        NextEffect();
        }
    }

TBool CAknTitlePaneLabel::TextNeedsTruncation() const
    {
    if ( iTextLength > iScrollRect.Width() )
        {
        return ETrue;
        }
    else
        {
        return EFalse;
        }
    }


TBool CAknTitlePaneLabel::EffectEventsNeeded( TInt aEffect ) const
    {
    if ( aEffect == EEffectDefaultScroll ||
         aEffect == EEffectDefaultScrollWithFade ||
         aEffect == EEffectLoopScroll ||
         aEffect == EEffectLoopScrollWithFade ||
         aEffect == EEffectFadeOut ||
         aEffect == EEffectFadeIn ||
         aEffect == EEffectScrollOnceWithFade ||
         aEffect == EEffectPause )
        {
        return ETrue;
        }
    else
        {
        return EFalse;
        }
    }


TBool CAknTitlePaneLabel::EffectBitmapsNeeded( TInt aEffect ) const
    {
    if ( aEffect == EEffectDefaultScroll ||
         aEffect == EEffectDefaultScrollWithFade ||
         aEffect == EEffectLoopScroll ||
         aEffect == EEffectLoopScrollWithFade ||
         aEffect == EEffectFadeOut ||
         aEffect == EEffectFadeIn ||
         aEffect == EEffectScrollOnceWithFade ||
         aEffect == EEffectFadeToLeft ||
         aEffect == EEffectFadeToRight )
        {
        return ETrue;
        }
    else
        {
        return EFalse;
        }
    }


TInt CAknTitlePaneLabel::ScrollStepInPixels() const
    {
    TInt stepInPixels = 2;

    // Adjust scrolling speed according to screen size
    TRect screenRect( iAvkonAppUi->ApplicationRect() );

    TInt scale = KScaleMagicNumber;
    if ( screenRect.Height() > screenRect.Width() )
        {
        scale = screenRect.Height();
        }
    else
        {
        scale = screenRect.Width();
        }

    stepInPixels = ( stepInPixels * scale ) / KScaleMagicNumber;

    if ( stepInPixels < 1 )
        {
        stepInPixels = 1;
        }

    return stepInPixels;
    }


void CAknTitlePaneLabel::InitEffectQueueL()
    {
    if ( !iEffectQueue )
        {
        iEffectQueue = new (ELeave) CArrayFixFlat<SAknTitleLableEffect>( 2 );
        }
    iEffectQueue->Reset();
    iNextEffectInEffectQueue = 0;
    }


void CAknTitlePaneLabel::AddToEffectQueueL( SAknTitleLableEffect aEffect )
    {
    if ( iEffectQueue )
        {
        iEffectQueue->AppendL( aEffect );
        }
    }


void CAknTitlePaneLabel::ActivateEffectQueue()
    {
    if ( iEffectQueue && iEffectQueue->Count() > iNextEffectInEffectQueue )
        {
        iNextEffectInEffectQueue++;
        SetTextEffect(
            iEffectQueue->At( iNextEffectInEffectQueue - 1 ).iEffect,
            iEffectQueue->At( iNextEffectInEffectQueue - 1 ).iEffectRect,
            iEffectQueue->At( iNextEffectInEffectQueue - 1 ).iEffectDuration,
            iEffectQueue->At( iNextEffectInEffectQueue - 1 ).iLabelRect,
            iEffectQueue->At( iNextEffectInEffectQueue - 1 ).iTextLayout,
            iEffectQueue->At( iNextEffectInEffectQueue - 1 ).iTextLayoutLine,
            iEffectQueue->At( iNextEffectInEffectQueue - 1 ).iTitleText,
            iEffectQueue->At( iNextEffectInEffectQueue - 1 ).iObserver);
        }
    }


void CAknTitlePaneLabel::NextEffect()
    {
    CancelTimer();
    ActivateEffectQueue();
    }


TInt CAknTitlePaneLabel::TextLength()
    {
    return iTextLength;
    }


void CAknTitlePaneLabel::HandleResourceChange( TInt aType )
    {
    CEikLabel::HandleResourceChange( aType );

    if ( aType == KEikDynamicLayoutVariantSwitch )
        {
        CancelTimer();
        TRAP_IGNORE( InitEffectQueueL() );
        iEffect = 0;
        }
    }


void CAknTitlePaneLabel::SetPictographInterface(
    CAknPictographInterface& aInterface )
    {
    TRAP_IGNORE( EnablePictographsL( aInterface ) );
    iPictographInterface = &aInterface;
    }


void CAknTitlePaneLabel::InvalidateText()
    {
    iTitleText = NULL;
    }


TBool CAknTitlePaneLabel::EffectQueueIsEmpty()
    {
    if ( iEffectQueue && iEffectQueue->Count() > 0 )
        {
        return EFalse;
        }
    else
        {
        return ETrue;
        }
    }


void CAknTitlePaneLabel::CreateScrollingTextL( const HBufC* aOriginalText )
    {
    delete iScrollingText;
    iScrollingText = NULL;

    if ( aOriginalText )
        {
        const CFont* fontUsed =
            AknLayoutUtils::FontFromId( iTextLayoutLine.FontId() );
        CFont::TMeasureTextInput input;
        TInt textLength = fontUsed->MeasureText( *aOriginalText, &input );
        // Add some safety margin ( must be at least this )
        textLength = textLength + textLength / 2;
        if ( textLength < Size().iWidth )
            {
            textLength = Size().iWidth;
            }

        iScrollingText = HBufC::NewL(
            aOriginalText->Length() + KAknBidiExtraSpacePerLine );
        TPtr ptr( iScrollingText->Des() );
        ptr.Fill(' ');
        AknBidiTextUtils::ConvertToVisualAndClip(
            *aOriginalText,
            ptr,
            *iFont,
            textLength,
            textLength );

        // Linefeed chars are always removed since this
        // text should never be used with 2-line text.
        ReplaceControlCharacters( iScrollingText, ETrue );
        }
    }


void CAknTitlePaneLabel::ReplaceControlCharacters( HBufC* aText,
                                                   TBool aReplaceLinefeeds )
    {
    // Remove chars 0x00 to 0x1F and 0x2029 (Paragraph separator).
    _LIT(KAknTitleLableStripListControlChars, "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F\x2029");
    // 0x0A (Newline) and 0x2029 (Paragraph separator) excluded.
    _LIT(KAknTitleLableStripListControlCharsWithoutLinefeed, "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0B\x0C\x0D\x0E\x0F\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F");

    // Replace with space (0x20)
    TChar replacementChar( 0x20 );

    const TDesC& aChars = KAknTitleLableStripListControlChars;
    const TDesC& aCharsWithoutLinefeed =
        KAknTitleLableStripListControlCharsWithoutLinefeed;

    TUint16* ptr = const_cast<TUint16*> ( aText->Ptr() );

    TInt src = 0;
    TInt srclength = aText->Length();
    while( src < srclength )
        {
        TChar c( ptr[src] );
        if ( aReplaceLinefeeds )
            {
            if ( aChars.LocateF( c ) != KErrNotFound )
                {
                ptr[src] = TUint16( replacementChar );
                }
            }
        else
            {
            if ( aCharsWithoutLinefeed.LocateF( c ) != KErrNotFound )
                {
                ptr[src] = TUint16( replacementChar );
                }
            }
        ++src;
        }
    }
