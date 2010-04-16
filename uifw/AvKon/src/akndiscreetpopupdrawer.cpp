/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Discreet popup drawer
*
*/

#include <AknBidiTextUtils.h>
#include "akndiscreetpopupcontrol.h"
#include <AknIconUtils.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <AknsDrawUtils.h>
#include <AknUtils.h>
#include <gulicon.h>


#include "akndiscreetpopupdrawer.h"

const TInt KTextBufSize( 255 );
const TInt KMaxNumOfLines( 2 );

// Help structure for layout data
class TPopupLayoutData
    {
public:
    TUint16 iWindowVariety;
    TUint16 iIconVariety;
    TUint16 i1stRowVariety;
    TUint16 i2ndRowVariety;
    };
    
// Layout data indexes in layout data array
const TInt KLayoutUnresolved( -1 );
const TInt KLayout2RowsIcon( 0 );
const TInt KLayout2Rows( 1 );
const TInt KLayout1RowIcon( 2 );
const TInt KLayout1Row( 3 );
const TInt KLayout2RowsWrappedIcon( 4 );
const TInt KLayout2RowsWrapped( 5 );

// Layout data array
static const TPopupLayoutData KPopupLayoutData[] =
    {
    { 0, 0, 0, 0 },
    { 0, 0, 1, 1 },
    { 0, 1, 2, 0 },
    { 0, 1, 3, 0 },
    { 0, 4, 4, 4 },
    { 0, 0, 5, 5 }
    };

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CAknDiscreetPopupDrawer::NewL
// ---------------------------------------------------------------------------
//
CAknDiscreetPopupDrawer* CAknDiscreetPopupDrawer::NewL( 
    CAknDiscreetPopupControl* aControl,
    const TDesC& aTitleText, 
    const TDesC& aBodyText, 
    CGulIcon* aIcon,
    const TAknsItemID& aSkinId,
    const TDesC& aBitmapFile,
    const TInt& aBitmapId,
    const TInt& aMaskId,
    const TBool& aAction )
    {
    CAknDiscreetPopupDrawer* self = 
        CAknDiscreetPopupDrawer::NewLC( aControl, 
                                        aTitleText, 
                                        aBodyText, 
                                        aIcon, 
                                        aSkinId, 
                                        aBitmapFile, 
                                        aBitmapId,
                                        aMaskId,
                                        aAction );
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupDrawer::NewLC
// ---------------------------------------------------------------------------
//
CAknDiscreetPopupDrawer* CAknDiscreetPopupDrawer::NewLC(
    CAknDiscreetPopupControl* aControl,
    const TDesC& aTitleText, 
    const TDesC& aBodyText, 
    CGulIcon* aIcon,
    const TAknsItemID& aSkinId,
    const TDesC& aBitmapFile,
    const TInt& aBitmapId,
    const TInt& aMaskId,
    const TBool& aAction )
    {
    CAknDiscreetPopupDrawer* self 
        = new ( ELeave ) CAknDiscreetPopupDrawer( aControl, aIcon, aAction );
    CleanupStack::PushL( self );
    self->ConstructL( aTitleText, 
                      aBodyText, 
                      aSkinId, 
                      aBitmapFile, 
                      aBitmapId,
                      aMaskId );
    return self;
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupDrawer::~CAknDiscreetPopupDrawer
// ---------------------------------------------------------------------------
//
CAknDiscreetPopupDrawer::~CAknDiscreetPopupDrawer()
    {
    delete iPopupBitmap;
    delete iTransparentMask;
    delete iIcon;
    delete iBodyText;
    delete iTitleText;
    }

// ---------------------------------------------------------------------------
// CAknDiscreetPopupDrawer::LayoutPopup
// Sets popup and its components size and position.
// ---------------------------------------------------------------------------
//
TRect CAknDiscreetPopupDrawer::LayoutPopup()
    {
    ResolvePopupLayout();

    TPopupLayoutData data( KPopupLayoutData[ iPopupLayoutType ] );
    
    TRect popupRect;
    TRect popupBitmapRect;
    
    GetPopupRect( data.iWindowVariety, popupRect );

    // Calculate sub rects according to popup bitmap rect
    popupBitmapRect = TRect( 0, 0, popupRect.Width(), popupRect.Height() );

    // Possible icon rect
    if ( iPopupLayoutType == KLayout2RowsIcon 
        || iPopupLayoutType == KLayout1RowIcon
        || iPopupLayoutType == KLayout2RowsWrappedIcon )
        {
        iIconRect = RectFromLayout( popupBitmapRect, 
            AknLayoutScalable_Avkon::popup_discreet_window_g1( 
            data.iIconVariety ) );
        if( iIcon && iIcon->Bitmap() )
            {
            AknIconUtils::SetSize( iIcon->Bitmap(), iIconRect.Size() );
            }
        if( iIcon && iIcon->Mask() )
            {
            AknIconUtils::SetSize( iIcon->Mask(), iIconRect.Size() );
            }
        }

    // Title text font
    TextDataFromLayout(
            iTitleTextData,
            popupBitmapRect,
            AknLayoutScalable_Avkon::popup_discreet_window_t1(
                    data.i1stRowVariety ) );

    // Two rows - no wrapping
    if ( iPopupLayoutType == KLayout2RowsIcon 
        || iPopupLayoutType == KLayout2Rows )
        {
        // Body text font
        TextDataFromLayout(
                iBodyTextData,
                popupBitmapRect,
                AknLayoutScalable_Avkon::popup_discreet_window_t2(
                        data.i2ndRowVariety ) );
        }
    // Two wrapped rows
    else if ( iPopupLayoutType == KLayout2RowsWrappedIcon
            || iPopupLayoutType == KLayout2RowsWrapped )
        {
        // Body text
        TextDataFromLayout(
                iBodyTextData,
                popupBitmapRect,
                AknLayoutScalable_Avkon::popup_discreet_window_t3(
                        data.i2ndRowVariety ) );
        // Text should be wrapped if in two-row layout and no bodytext
        if ( iBodyText->Des() == KNullDesC )
            {
            TRAP_IGNORE( WrapTitleTextL() );
            }
        }

    return popupRect;
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupDrawer::PopupBitmap
// Provides popup bitmap.
// ---------------------------------------------------------------------------
//
CFbsBitmap* CAknDiscreetPopupDrawer::PopupBitmap( const TSize& aSize )
    {
    if ( !iPopupBitmap || aSize != iPopupBitmap->SizeInPixels() )
        {
        TRAP_IGNORE( CreatePopupBitmapL( TRect( TPoint(), aSize ) ) );
        }
    return iPopupBitmap;
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupDrawer::TransparentMask
// Provides transparent mask for a bitmap.
// ---------------------------------------------------------------------------
//
CFbsBitmap* CAknDiscreetPopupDrawer::TransparentMask( 
    const TSize& aSize, const TInt& aAlpha )
    {
    if ( !iTransparentMask || aSize != iTransparentMask->SizeInPixels() )
        {
        TRAP_IGNORE( CreateTransparentMaskL( TRect( TPoint(), aSize ) ) );
        }

    TInt width( iTransparentMask->SizeInPixels().iWidth );
    TInt height( iTransparentMask->SizeInPixels().iHeight ); 
    TUint8* address( ( TUint8* ) iTransparentMask->DataAddress() );
    TInt dataStride( iTransparentMask->DataStride() - width );
    
    for ( TInt i = 0; i < height; ++i )
        {
        for ( TInt j = 0; j < width; j++ )
            {
            *address = aAlpha;
            ++address;
            }
        address += dataStride; 
        }
    
    return iTransparentMask;
    }  


// ---------------------------------------------------------------------------
// CAknDiscreetPopupDrawer::CAknDiscreetPopupDrawer
// ---------------------------------------------------------------------------
//
CAknDiscreetPopupDrawer::CAknDiscreetPopupDrawer( 
    CAknDiscreetPopupControl* aControl, 
    CGulIcon* aIcon, 
    const TBool& aAction )
    :
    iControl( aControl ),
    iTitleText( NULL ),
    iBodyText( NULL ),
    iIcon( aIcon ),
    iPopupBitmap( NULL ),
    iTransparentMask( NULL ),
    iPopupLayoutType( KLayoutUnresolved ),
    iAction( aAction )
    {
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupDrawer::ConstructL
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopupDrawer::ConstructL( const TDesC& aTitleText, 
                                          const TDesC& aBodyText,
                                          const TAknsItemID& aSkinId,
                                          const TDesC& aBitmapFile,
                                          const TInt& aBitmapId,
                                          const TInt& aMaskId )
    {
    // Body text to title text if title text is empty
    if ( aTitleText == KNullDesC && aBodyText != KNullDesC )
        {
        iTitleText = aBodyText.AllocL();
        }
    else
        {
        iTitleText = aTitleText.AllocL();
        iBodyText = aBodyText.AllocL();
        }

    if ( !iIcon )
        {
        iIcon = CreatePopupIconL( aSkinId, 
                                  aBitmapFile, 
                                  aBitmapId, 
                                  aMaskId );
        }
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupDrawer::CreatePopupBitmap
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopupDrawer::CreatePopupBitmapL( const TRect& aRect )
    {
    delete iPopupBitmap;
    iPopupBitmap = NULL;
    
    // create a bitmap to draw to
    CFbsBitmap* bitmap = new ( ELeave ) CFbsBitmap;
    CleanupStack::PushL( bitmap );

    bitmap->Create( 
        aRect.Size(), CCoeEnv::Static()->ScreenDevice()->DisplayMode() );
    CFbsBitGc* fbsBitGc = CFbsBitGc::NewL();
    CleanupStack::PushL( fbsBitGc );
    CFbsBitmapDevice* bmpDevice = CFbsBitmapDevice::NewL( bitmap );
    CleanupStack::PushL( bmpDevice );
    fbsBitGc->Activate( bmpDevice );

    // draw background of the popup	
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    AknsDrawUtils::DrawFrame( skin, *fbsBitGc, aRect, aRect, 
        KAknsIIDQsnFrPopupPreview, KAknsIIDDefault, KAknsDrawParamDefault );
    
    // Draw the texts
    TRgb textColor( EikonEnv()->ControlColor( EColorControlText, *iControl ) );
    if ( iAction )
        {
        fbsBitGc->SetUnderlineStyle( EUnderlineOn );
        AknsUtils::GetCachedColor( skin,
                                   textColor,
                                   KAknsIIDQsnHighlightColors,
                                   EAknsCIQsnHighlightColorsCG3 );
        }
    else
        {
        AknsUtils::GetCachedColor( skin,
                                   textColor,
                                   KAknsIIDQsnTextColors,
                                   EAknsCIQsnTextColorsCG55 );
        }
    fbsBitGc->SetPenColor( textColor );
    DrawTexts( fbsBitGc );
    fbsBitGc->SetUnderlineStyle( EUnderlineOff );

    // draw the icon
    if ( iIcon && iIcon->Bitmap() && iIcon->Mask() )
        {
        fbsBitGc->BitBltMasked( iIconRect.iTl,
                                iIcon->Bitmap(), 
                                iIcon->Bitmap()->SizeInPixels(), 
                                iIcon->Mask(), 
                                EFalse );

        }
    else if( iIcon && iIcon->Bitmap() )
        {
        fbsBitGc->BitBlt( iIconRect.iTl, iIcon->Bitmap() );
        }

    CleanupStack::PopAndDestroy( bmpDevice );
    CleanupStack::PopAndDestroy( fbsBitGc );
    CleanupStack::Pop( bitmap );
    
    iPopupBitmap = bitmap;
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupDrawer::CreateTransparentMaskL
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopupDrawer::CreateTransparentMaskL( const TRect& aRect )
    {
    delete iTransparentMask;
    iTransparentMask = NULL;
    iTransparentMask = new ( ELeave ) CFbsBitmap;
    iTransparentMask->Create( aRect.Size(), EGray256 );
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupDrawer::DrawTexts
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopupDrawer::DrawTexts( CFbsBitGc* aGc )
    {
    aGc->SetBrushStyle( CGraphicsContext::ENullBrush );

    DrawBidiEnabledText( aGc, iTitleTextData, *iTitleText );
    
    if ( iBodyTextData.iTextRect != TRect() )
        {
        DrawBidiEnabledText( aGc, iBodyTextData, *iBodyText );
        }
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupDrawer::ResolvePopupLayout
// Resolves popup layout type.
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopupDrawer::ResolvePopupLayout()
    {
    // Layout already resolved, do nothing
    if ( iPopupLayoutType != KLayoutUnresolved )
        {
        return;
        }
    
    TBool withIcon( iIcon && iIcon->Bitmap() );
    TBool twoRowsText( 
        iTitleText->Des() != KNullDesC 
        && iBodyText->Des() != KNullDesC );

    // Two rows of text
    if ( twoRowsText )
        {
        if ( withIcon )
            {
            iPopupLayoutType = KLayout2RowsIcon;
            }
        else
            {
            iPopupLayoutType = KLayout2Rows;
            }
        }
    // One row of text
    else
        {
        if ( withIcon )
            {
            iPopupLayoutType = KLayout1RowIcon;
            }
        else
            {
            iPopupLayoutType = KLayout1Row;
            }

        // Check if text should be wrapped to two lines
        if ( TitleTextNeedsWrapping( iPopupLayoutType ) )
            {
            if ( withIcon )
                {
                iPopupLayoutType = KLayout2RowsWrappedIcon;
                }
            else
                {
                iPopupLayoutType = KLayout2RowsWrapped;
                }
            }
        }
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupDrawer::EikonEnv
// Provides control eikon env.
// ---------------------------------------------------------------------------
//
CEikonEnv* CAknDiscreetPopupDrawer::EikonEnv()
    {
    if ( iControl )
        {
        return static_cast<CEikonEnv*>( iControl->ControlEnv() );
        }
    return NULL;
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupDrawer::TitleTextNeedsWrapping
// Returns ETrue if title text needs wrapping.
// ---------------------------------------------------------------------------
//
TBool CAknDiscreetPopupDrawer::TitleTextNeedsWrapping( 
        const TInt& aLayoutType )
    {
    const CFont* textFont( NULL );
    TRect textRect;
    TRect popupRect;
    TPopupLayoutData data( KPopupLayoutData[ aLayoutType ] );
    GetPopupRect( data.iWindowVariety, popupRect );
    popupRect.Move( 0, 0 );

    textFont = FontFromLayout( 
        popupRect, 
        AknLayoutScalable_Avkon::popup_discreet_window_t1( 
        data.i1stRowVariety ), textRect );
    if ( textFont->TextCount( *iTitleText, textRect.Width() ) 
            < iTitleText->Length() )
        {
        return ETrue;
        }
    return EFalse;
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupDrawer::WrapTitleTextL
// Wraps long text to two lines.
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopupDrawer::WrapTitleTextL()
    {
    CArrayFixFlat<TInt>* lineWidths 
        = new ( ELeave ) CArrayFixFlat<TInt>( KMaxNumOfLines );
    CleanupStack::PushL( lineWidths );
    CArrayFixFlat<TPtrC>* wrappedArray
        = new ( ELeave ) CArrayFixFlat<TPtrC>( KMaxNumOfLines );
    CleanupStack::PushL( wrappedArray );

    for ( TInt i = 0; i < KMaxNumOfLines; i++ )
        {
        lineWidths->AppendL( iTitleTextData.iTextRect.Width() );
        }

    HBufC* visualBuffer = HBufC::NewLC( 
            iTitleText->Length() + KMaxNumOfLines * KAknBidiExtraSpacePerLine );
    *visualBuffer = *iTitleText;
    TPtr ptr( visualBuffer->Des() );

    AknBidiTextUtils::ConvertToVisualAndWrapToArrayL(
            ptr, *lineWidths, *iTitleTextData.iTextFont, *wrappedArray, ETrue );

    if ( wrappedArray->Count() && wrappedArray->At( 1 ) != KNullDesC )
        {
        delete iTitleText;
        iTitleText = NULL;
        delete iBodyText;
        iBodyText = NULL;
        iTitleText = wrappedArray->At( 0 ).AllocL();
        iBodyText = wrappedArray->At( 1 ).AllocL();
        }

    CleanupStack::PopAndDestroy( visualBuffer );
    CleanupStack::PopAndDestroy( wrappedArray );
    CleanupStack::PopAndDestroy( lineWidths );
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupDrawer::DrawBidiEnabledText
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopupDrawer::DrawBidiEnabledText(
        CFbsBitGc* aGc,
        TAknDiscreetPopupTextData& aTextData,
        const TDesC& aText )
    {
    // Buffer for visually ordered text
    TBuf<KTextBufSize + KAknBidiExtraSpacePerLine> visualText; 
    TInt clipWidth( aTextData.iTextRect.Width() );

    // Bidi processing - using AknBidiTextUtils.
    AknBidiTextUtils::ConvertToVisualAndClip(
        aText, visualText, *aTextData.iTextFont, clipWidth, clipWidth );

    TInt baselineOffset(
            aTextData.iTextFont->AscentInPixels()
            + ( aTextData.iTextRect.Height()
                    - aTextData.iTextFont->AscentInPixels() ) / 2 );

    aGc->UseFont( aTextData.iTextFont );
    aGc->DrawText(
            visualText,
            aTextData.iTextRect,
            baselineOffset,
            aTextData.iTextAlignment );
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupDrawer::CreatePopupIconL
// Creates icon of given parameters.
// ---------------------------------------------------------------------------
//
CGulIcon* CAknDiscreetPopupDrawer::CreatePopupIconL( const TAknsItemID& aSkinId,
                                                     const TDesC& aBitmapFile,
                                                     const TInt& aBitmapId,
                                                     const TInt& aMaskId )
    {
    if ( !ImageInfoAvailable( aSkinId, aBitmapFile, aBitmapId ) )
        {
        return NULL;
        }
    
    CGulIcon* icon = NULL;
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();

    // Only skin id defined
    if ( aBitmapFile == KNullDesC || aBitmapId == -1 )
        {
        if ( aSkinId != KAknsIIDNone && skin )
            {
            icon = AknsUtils::CreateGulIconL( skin, aSkinId, EFalse );
            }
        }
    else
        {
        // Skin id and bitmap file info defined
        if ( aSkinId != KAknsIIDNone && skin )
            {
            icon = AknsUtils::CreateGulIconL( skin, 
                                              aSkinId, 
                                              aBitmapFile, 
                                              aBitmapId,
                                              aMaskId);
            }

        // Only bitmap file info defined
        else
            {
            CFbsBitmap* bmp;
            CFbsBitmap* mask;
            AknIconUtils::CreateIconLC( bmp, 
                                        mask, 
                                        aBitmapFile, 
                                        aBitmapId, 
                                        aMaskId );
            icon = CGulIcon::NewL( bmp, mask ); // ownership passed
            CleanupStack::Pop( mask );
            CleanupStack::Pop( bmp );
            }
        }
    return icon;
    }  


// ---------------------------------------------------------------------------
// CAknDiscreetPopupDrawer::ImageInfoAvailable
// ---------------------------------------------------------------------------
//
TBool CAknDiscreetPopupDrawer::ImageInfoAvailable( const TAknsItemID& aSkinId,
                                                   const TDesC& aBitmapFile,
                                                   const TInt& aBitmapId )
    {
    if ( aSkinId != KAknsIIDNone && aSkinId != KAknsIIDDefault )
        {
        return ETrue;
        }
    if ( aBitmapFile != KNullDesC && aBitmapId > 0 )
        {
        return ETrue;
        }
    return EFalse;
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupDrawer::RectFromLayout
// Returns the specified layout rectangle.
// ---------------------------------------------------------------------------
//
TRect CAknDiscreetPopupDrawer::RectFromLayout( const TRect& aParent,
    const TAknWindowComponentLayout& aComponentLayout )
    {
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect( aParent, aComponentLayout.LayoutLine() );
    return layoutRect.Rect();
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupDrawer::TextDataFromLayout
// Fills text data according to text layout.
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopupDrawer::TextDataFromLayout( 
        TAknDiscreetPopupTextData& aTextData,
        const TRect& aParent, 
        const TAknTextComponentLayout& aComponentLayout )
    {
    aTextData.iTextFont =
        FontFromLayout( aParent, aComponentLayout, aTextData.iTextRect );
    switch ( aComponentLayout.J() )
        {
        case ELayoutAlignRight:
            {
            aTextData.iTextAlignment = CGraphicsContext::ERight;
            break;
            }
        case ELayoutAlignLeft:
            {
            aTextData.iTextAlignment = CGraphicsContext::ELeft;
            break;
            }
        case ELayoutAlignCenter:
            {
            aTextData.iTextAlignment = CGraphicsContext::ECenter;
            break;
            }
        default:
            {
            aTextData.iTextAlignment = CGraphicsContext::ECenter;
            break;
            }
        }
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupDrawer::FontFromLayout
// Returns the specified text layout font.
// ---------------------------------------------------------------------------
//
const CFont* CAknDiscreetPopupDrawer::FontFromLayout( 
    const TRect& aParent,
    const TAknTextComponentLayout& aComponentLayout,
    TRect& aTextRect )
    {
    TAknLayoutText layoutRect;
    layoutRect.LayoutText( aParent, aComponentLayout.LayoutLine() );
    aTextRect = layoutRect.TextRect();
    return layoutRect.Font();
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopupDrawer::GetPopupRect
// Provides popup rect.
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopupDrawer::GetPopupRect(
        const TInt& aWindowVariety, TRect& aRect )
    {
    TRect appRect;
    AknLayoutUtils::LayoutMetricsRect( 
        AknLayoutUtils::EApplicationWindow, appRect);

    // Popup rect
    aRect = RectFromLayout( 
            appRect, 
            AknLayoutScalable_Avkon::popup_discreet_window( 
            aWindowVariety ) );
        
    }

