/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Default label control for the status pane's navigation pane.
*
*/


// SYSTEM INCLUDE FILES
#include <gdi.h>
#include <eikspane.h>
#include <AknsDrawUtils.h>
#include <bidivisual.h>
#include <biditext.h>
#include <aknlayoutscalable_avkon.cdl.h>

#include <AknTasHook.h>
// USER INCLUDE FILES
#include "aknnavilabel.h"
#include "AknPanic.h"
#include "AknUtils.h"
#include "aknconsts.h"
#include "AknBidiTextUtils.h"
#include "AknStatuspaneUtils.h"
#include "aknenv.h"
#include "aknnavide.h"
#include <aknnavide.h>

NONSHARABLE_CLASS( CAknNaviLabelExtension ) : public CBase
    {
public:
    static CAknNaviLabelExtension* NewL();
    ~CAknNaviLabelExtension();
    void SetVisualBufferSizeL( TInt aSize );
private:
    CAknNaviLabelExtension();
    void ConstructL();
public: //data
    HBufC* iVisualTextBuffer;
    };

CAknNaviLabelExtension* CAknNaviLabelExtension::NewL()
    {
    CAknNaviLabelExtension* self = new (ELeave) CAknNaviLabelExtension;
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

CAknNaviLabelExtension::CAknNaviLabelExtension()
    {
    }

CAknNaviLabelExtension::~CAknNaviLabelExtension()
    {
    delete iVisualTextBuffer;
    }

void CAknNaviLabelExtension::ConstructL()
    {
    iVisualTextBuffer = HBufC::NewL(0);
    }

void CAknNaviLabelExtension::SetVisualBufferSizeL( TInt aSize )
    {
    if ( aSize <= iVisualTextBuffer->Des().MaxLength() )
        {
        return;
        }

    HBufC* tempBuf = HBufC::NewL( aSize );
    delete iVisualTextBuffer;
    iVisualTextBuffer = tempBuf;
    }

EXPORT_C CAknNaviLabel::~CAknNaviLabel()
    {
    AKNTASHOOK_REMOVE();
    delete iText;
    delete iExtension;
    }

EXPORT_C CAknNaviLabel::CAknNaviLabel()
    {
    AKNTASHOOK_ADD( this, "CAknNaviLabel" );
    }

EXPORT_C void CAknNaviLabel::SetTextL( const TDesC& aText )
    {
    __ASSERT_DEBUG( &aText, Panic( EAknPanicNullPointer ) );

    if ( !iExtension )
        {
        iExtension = CAknNaviLabelExtension::NewL();
        }

    User::LeaveIfError( AknBidiTextUtils::PrepareRunInfoArray( aText ) );
    HBufC* newText = aText.AllocLC();
    iExtension->SetVisualBufferSizeL(
        aText.Length() + KAknBidiExtraSpacePerLine );
    CleanupStack::Pop( newText );

    delete iText; // after all allocations succeed
    iText = newText;

    SizeChanged();
    }

EXPORT_C void CAknNaviLabel::SetNaviLabelType( TNaviLabelType aLabelType )
    {
    iLabelType = aLabelType;
    }

EXPORT_C CAknNaviLabel::TNaviLabelType CAknNaviLabel::NaviLabelType()
    {
    return iLabelType;
    }

EXPORT_C void CAknNaviLabel::SizeChanged()
    {
    if ( !iExtension )
        {
        return;
        }

    TRect parentRect( Rect() );

    CGraphicsContext::TTextAlign alignment = CGraphicsContext::ELeft;
    iRightOffset = 0;

    TAknLayoutText textLayout( LayoutText() );

    switch ( iLabelType )
        {
        case ENavigationLabel:
            {
            TRect textRect( textLayout.TextRect() );
            TRect rect( Rect() );

            // because this components rect is not same as navipane
            // in LAF some calculations are needed.

            // The left margin amount of navipane that this labels
            // rect does not cover.
            TInt leftOutsideMargin = 0;

            // The right margin amount of navipane that this labels
            // rect does not cover.
            TInt rightOutsideMargin = 0;

            leftOutsideMargin = rect.iTl.iX;
            rightOutsideMargin = parentRect.iBr.iX - rect.iBr.iX;

            if ( leftOutsideMargin < 0 )
                {
                leftOutsideMargin = 0;
                }

            if ( rightOutsideMargin < 0 )
                {
                rightOutsideMargin = 0;
                }

            iLeftMargin  = textRect.iTl.iX - leftOutsideMargin;
            iRightMargin = rect.iBr.iX - textRect.iBr.iX;
            iFont        = textLayout.Font();
            iColor       = textLayout.Color();
            alignment    = textLayout.Align();
            }
            break;

        case EAdditionalInfoLabel: // fallthrough, these use same properties.
        case EHintText:
            {
            TRect textRect( textLayout.TextRect() );
            iLeftMargin  = textRect.iTl.iX;
            iRightMargin = parentRect.iBr.iX - textRect.iBr.iX;
            iFont        = textLayout.Font();
            iColor       = textLayout.Color();
            alignment    = textLayout.Align();
            }
            break;

        default:
            break;
        }

    TInt width = WidthInsideMargins();
    if ( width < 0 )
        {
        width = 0;
        }

    TPtr truncated = iExtension->iVisualTextBuffer->Des();

    AknBidiTextUtils::ConvertToVisualAndClip(
        *iText,
        truncated,
        *iFont,
        width,
        width );

    if ( alignment == CGraphicsContext::ECenter )
        {
        // Center the text. Must inform the text measurement algorithm that
        // the text is in visual, not logical order.

        CFont::TMeasureTextInput input;
        input.iFlags = CFont::TMeasureTextInput::EFVisualOrder;

        TInt textLength = iFont->MeasureText( truncated, &input );

        iRightOffset = ( width - textLength ) / 2;
        }
    }

EXPORT_C void CAknNaviLabel::Draw( const TRect& /*aRect*/ ) const
    {
    if ( !iExtension )
        {
        return;
        }

    CWindowGc& gc = SystemGc();

    TRect rect( Rect() );
    gc.UseFont( iFont );

    TRgb color = iColor;

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    TAknLayoutText layoutText( LayoutText() );
    if ( AknStatuspaneUtils::StaconPaneActive() ||
         AknStatuspaneUtils::FlatLayoutActive() )
        {
        AknsUtils::GetCachedColor( skin,
                                   color,
                                   KAknsIIDQsnTextColors,
                                   EAknsCIQsnTextColorsCG43 );
        }
    else
        {
        AknsUtils::GetCachedColor( skin,
                                   color,
                                   KAknsIIDQsnTextColors,
                                   EAknsCIQsnTextColorsCG2 );
        }

    layoutText.DrawText( gc, *iText, ETrue, color );
    }

EXPORT_C void CAknNaviLabel::HandlePointerEventL(
    const TPointerEvent& aPointerEvent )
    {
    CAknControl::HandlePointerEventL( aPointerEvent );
    }

EXPORT_C void* CAknNaviLabel::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

TInt CAknNaviLabel::WidthInsideMargins() const
    {
    TInt width = Rect().Width() - iLeftMargin - iRightMargin;
    return width;
    }

TAknLayoutText CAknNaviLabel::LayoutText() const
    {
    TRect parentRect( CAknNavigationDecorator::DecoratedControlRect(
        CAknNavigationDecorator::ENaviLabel ) );

    TAknWindowLineLayout naviPaneLayout;
    TAknWindowLineLayout naviTextPaneLayout;
    TAknTextLineLayout layout;

    // In flat status pane with narrow layout we have another layout
    TBool flatNarrow = AknStatuspaneUtils::FlatLayoutActive() &&
                       parentRect.Width() > Rect().Width();

    if ( flatNarrow )
        {
        parentRect = Rect();
        }

    if ( AknStatuspaneUtils::SmallLayoutActive() )
        {
        layout = AknLayoutScalable_Avkon::status_small_pane_t1( 0 );
        }
    else
        {
        switch ( iLabelType )
            {
            case ENavigationLabel:
                {
                if ( flatNarrow )
                    {
                    naviPaneLayout = AknLayoutScalable_Avkon::navi_navi_pane_srt().LayoutLine();
                    naviTextPaneLayout = AknLayoutScalable_Avkon::navi_navi_text_pane_srt().LayoutLine();
                    layout = TAknWindowComponentLayout::ComposeText( naviPaneLayout,
                                TAknWindowComponentLayout::ComposeText( naviTextPaneLayout,
                                    AknLayoutScalable_Avkon::navi_navi_text_pane_srt_t1().LayoutLine() ) );
                    }
                else
                    {
                    naviPaneLayout = AknLayoutScalable_Avkon::navi_navi_pane().LayoutLine();
                    naviTextPaneLayout = AknLayoutScalable_Avkon::navi_navi_text_pane().LayoutLine();
                    layout = TAknWindowComponentLayout::ComposeText( naviPaneLayout,
                                TAknWindowComponentLayout::ComposeText( naviTextPaneLayout,
                                    AknLayoutScalable_Avkon::navi_navi_text_pane_t1().LayoutLine() ) );
                    }
                }
                break;

            case EAdditionalInfoLabel:
                {
                if ( flatNarrow )
                    {
                    naviTextPaneLayout = AknLayoutScalable_Avkon::navi_text_pane_srt(1).LayoutLine();
                    layout = TAknWindowComponentLayout::ComposeText( naviTextPaneLayout,
                                AknLayoutScalable_Avkon::navi_text_pane_srt_t1().LayoutLine() );
                    }
                else
                    {
                    naviTextPaneLayout = AknLayoutScalable_Avkon::navi_text_pane(1).LayoutLine();
                    layout = TAknWindowComponentLayout::ComposeText( naviTextPaneLayout,
                                AknLayoutScalable_Avkon::navi_text_pane_t1().LayoutLine() );
                    }
                }
                break;

            case EHintText:
                {
                if ( flatNarrow )
                    {
                    naviTextPaneLayout = AknLayoutScalable_Avkon::navi_text_pane_srt(0).LayoutLine();
                    layout = TAknWindowComponentLayout::ComposeText( naviTextPaneLayout,
                                AknLayoutScalable_Avkon::navi_text_pane_srt_t1().LayoutLine() );
                    }
                else
                    {
                    naviTextPaneLayout = AknLayoutScalable_Avkon::navi_text_pane(0).LayoutLine();
                    layout = TAknWindowComponentLayout::ComposeText( naviTextPaneLayout,
                                AknLayoutScalable_Avkon::navi_text_pane_t1().LayoutLine() );
                    }
                }
                break;

            default:
                break;
            }
        }

    // In stacon pane text justification depends on which side the
    // soft keys are. We change justification here manually because
    // the LAF data does not support this yet. So this code overides also
    // A & H mirroring which is supposed to be not used in stacon pane anyway.
    if ( AknStatuspaneUtils::StaconPaneActive() &&
         layout.iJ != ELayoutAlignCenter )
        {
        if ( AknStatuspaneUtils::StaconSoftKeysLeft() )
            {
            layout.iJ = ELayoutAlignRight;
            }
        else
            {
            layout.iJ = ELayoutAlignLeft;
            }
        }
    // In flat status pane we change justification here manually because
    // the LAF data does not support this yet. This way we avoid odd looking
    // situation where navitexts are in the middle of the status pane area.
    // Right side is more sensible place (left in A&H).
    else if ( AknStatuspaneUtils::FlatLayoutActive() &&
              layout.iJ != ELayoutAlignCenter )
        {
        if ( AknLayoutUtils::LayoutMirrored() )
            {
            layout.iJ = ELayoutAlignLeft;
            }
        else
            {
            layout.iJ = ELayoutAlignRight;
            }
        }



    TAknLayoutText textLayout;
    textLayout.LayoutText( parentRect, layout );
    return textLayout;
    }

//  End of File
