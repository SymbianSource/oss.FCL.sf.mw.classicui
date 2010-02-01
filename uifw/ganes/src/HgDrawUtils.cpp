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
* Description:     
*
*/


#include "HgDrawUtils.h"

#include "HgMarquee.h"

#include <gdi.h>
#include <gulicon.h>
#include <AknUtils.h>
#include <AknsUtils.h>
#include <AknsControlContext.h>
#include <AknsDrawUtils.h>
#include <AknsListBoxBackgroundControlContext.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <AknBidiTextUtils.h>

const TInt KHgDrawUtilsGranularity(10);
const TInt KHgDrawUtilsMaxNumberOfLines(4);

CHgDrawUtils* CHgDrawUtils::NewL( TCallBack& aMarqueeCallback )
    {
    CHgDrawUtils* self = new (ELeave) CHgDrawUtils();
    CleanupStack::PushL( self );
    self->ConstructL( aMarqueeCallback );
    CleanupStack::Pop(self);
    return self;
    }

CHgDrawUtils::~CHgDrawUtils()
    {
    delete iMarquee;
    }
    

void DrawEmptyListImpl_real_DrawUpToTwoLines( CGraphicsContext &aGc,
                                              TPtrC aText,
                                              TAknLayoutText &aLine1,
                                              TAknLayoutText &aLine2,
                                              TInt aLine1length,
                                              TInt aLine2length,
                                              const CFont* aFont,
                                              TRgb aColor,
                                              TDes& aBuffer )
    {
    TRAPD( error,
        {
        CArrayFix<TInt>* wrapWidthArray = new( ELeave ) CArrayFixFlat<TInt>(KHgDrawUtilsGranularity);
        CleanupStack::PushL( wrapWidthArray );

        wrapWidthArray->AppendL( aLine1length );
        wrapWidthArray->AppendL( aLine2length );
        
        AknBidiTextUtils::ConvertToVisualAndWrapToStringL( 
            aText, *wrapWidthArray, *aFont, aBuffer, ETrue );
        
        CleanupStack::PopAndDestroy( wrapWidthArray ); // wrapWidthArray
        } ); // TRAP end
    
    if ( error != KErrNone )
        {
        aBuffer = aText;
        }
    
    // Drawing text
    aGc.Reset();
    TBool oneline( EFalse );
    TPtrC ptr = aBuffer;
    TPtrC top = ptr;
    TInt off = ptr.Locate('\n');
    if ( off >= 0 )
        {
        top.Set(ptr.Left(off));
        ptr.Set(ptr.Mid(off+1));

        TInt off1 = ptr.Locate('\n');
        if ( off1 >= 0 )
            {
            ptr.Set(ptr.Left(off1));
            }
        else
            {
            oneline = ETrue;
            }
        }
    
    aGc.SetBrushStyle(CGraphicsContext::ENullBrush);

    // no layout exist for popup list - mainpane layout is ok for X
    // coords, center vertically.  Also need to calculate vertical
    // position for mainpane lists, since laf is broken as designed.
    // If you don't believe this, try using laf values in phonebook.
    aGc.UseFont( aFont );
    aGc.SetPenColor( aColor );
    
    aLine1.DrawText(aGc, top, EFalse, aColor );
    if ( !oneline )
        {
        aLine2.DrawText( aGc, ptr, EFalse, aColor );
        }
    aGc.DiscardFont();
    }    

void DrawEmptyListImpl_real_DrawMoreThanTwoLines( const TRect &aParentRect,
                                                  CGraphicsContext &aGc,
                                                  TPtrC aText,
                                                  TRgb aColor,
                                                  TDes& buffer )

    {
    // fetch layouts
    TAknLayoutText line[KHgDrawUtilsMaxNumberOfLines];
    
    line[0].LayoutText( aParentRect, AknLayoutScalable_Avkon::main_pane_empty_t1(2) );
    line[1].LayoutText( aParentRect, AknLayoutScalable_Avkon::main_pane_empty_t3(0) );
    line[2].LayoutText( aParentRect, AknLayoutScalable_Avkon::main_pane_empty_t4(0) );
    line[3].LayoutText( aParentRect, AknLayoutScalable_Avkon::main_pane_empty_t5(0) );

    TInt lineLength[KHgDrawUtilsMaxNumberOfLines];
    TInt i;
    for ( i = 0; i < KHgDrawUtilsMaxNumberOfLines; i++ )
        {
        lineLength[i] = line[i].TextRect().Width();
        }
    
    const CFont *bigFont = line[0].Font();
    const CFont *smallFont = line[1].Font(); 

    // wrap text
    TInt off = aText.Locate('\n');
    TPtrC rest( aText );
    rest.Set( aText.Right(aText.Length() - off - 1 ));

    HBufC* firstLine = NULL;
    
    TRAPD( error1, 
            {
            firstLine = HBufC::NewL(
                aText.Left(off).Length() + KAknBidiExtraSpacePerLine );
            });

    if (error1 == KErrNone)
        {
        TPtr firstLinePtr = firstLine->Des();
        AknBidiTextUtils::ConvertToVisualAndClip(
                                aText.Left(off),
                                firstLinePtr,
                                *bigFont,
                                lineLength[0],
                                lineLength[0] );
        }
    
    TRAPD( error2,
        {
        CArrayFix<TInt>* wrapWidthArray = new( ELeave ) CArrayFixFlat<TInt>(KHgDrawUtilsGranularity);
        CleanupStack::PushL( wrapWidthArray );
        
        // wrap small font lines
        wrapWidthArray->Reset();
        for ( i = 1; i < KHgDrawUtilsMaxNumberOfLines; i++ )
            {
            wrapWidthArray->AppendL( lineLength[i] );
            }
        
        AknBidiTextUtils::ConvertToVisualAndWrapToStringL( 
            rest, *wrapWidthArray, *smallFont, buffer, ETrue );
        
        CleanupStack::PopAndDestroy( wrapWidthArray ); // wrapWidthArray
        } ); // TRAP end
    
    
    TPtrC ptr[KHgDrawUtilsMaxNumberOfLines];
    TInt n = 0;
    
    if (error1 == KErrNone)
        {
        ptr[0].Set( firstLine->Des() );
        }
    if ( error1 != KErrNone || error2 != KErrNone )
        {
        ptr[0].Set(aText.Left(off));
        }
    else
        {
        TInt newlines[3];
        n = 0;
        for ( i = 0; i < buffer.Length(); i++ )
            {
            if ( buffer[i] != '\n' )
                {
                continue;
                }
            newlines[n] = i;
            
            n++;
            if ( n >= 3 )
                {
                break;
                }
            }
        
        if ( n >= 1 )
            {
            ptr[1].Set( buffer.Left( newlines[0] ) );
            }
        if ( n >= 2 )
            {
            ptr[2].Set( buffer.Mid( newlines[0] + 1, newlines[1] - newlines[0] - 1 ) );
            }
        if ( n >= 3 )
            {
            ptr[3].Set( buffer.Mid( newlines[1] + 1, newlines[2] - newlines[1] - 1 ) );
            }
        }
    
    // draw texts
    aGc.SetBrushStyle(CGraphicsContext::ENullBrush);
    
    for ( i = 0; i < KHgDrawUtilsMaxNumberOfLines; i++ )
        {
        line[i].DrawText( aGc, ptr[i], EFalse, aColor );
        }

    delete firstLine;
    }

void DrawEmptyListImpl_real( const TRect &aClientRect,
                             CGraphicsContext &aGc,
                             TPtrC aText,
                             const TRgb& aColor  )
    {
    if ( !aText.Length() )
        {
        return;
        }

    HBufC* hbuf = HBufC::New( aText.Size() + 3 * ( KAknBidiExtraSpacePerLine  +1 )
                              + 10 );  // reserve space for newlines
    if ( !hbuf )
        { // can't really do anything
        return;
        }

    TPtr buffer(hbuf->Des());
    
    /*
    * input text can be either
    * - "line1"
    * - "line1 which will be wrapped to 2 lines and truncated with..."
    * - "line1\nline2"
    * - "line1\nMany other lines which will be wrapped to several lines"
    *
    * there are 3 layouts
    * - 1 line with big font,
    * - 2 lines with big font
    * - 1 line with big font + 1..3 lines with small font (not for popup lists)
    *
    *  so first we need to check if given text has a newline,
    *  if so, then we need to check if given text fits to 2 lines or
    *  should it be split to several small font lines
    */

    TInt i, n;
    n = 0;
    for (i = 0; i < aText.Length(); i ++)
        {
        if ( aText[i] == '\n' )
            {
            n++;
            }
        }

    
    TAknTextComponentLayout layout1( AknLayoutScalable_Avkon::main_pane_empty_t1( 0 ) );
    TAknTextComponentLayout layout2( AknLayoutScalable_Avkon::main_pane_empty_t2( 0 ) );
    TAknLayoutText line1;
    TAknLayoutText line2;

    line1.LayoutText( aClientRect, layout1 );
    TInt line1length = line1.TextRect().Size().iWidth;

    line2.LayoutText( aClientRect, layout2 ); 
    TInt line2length = line2.TextRect().Size().iWidth;

    const CFont *font = line1.Font();

    if ( n == 0 )
        { // one line, or one line which will be wrapped to two
        DrawEmptyListImpl_real_DrawUpToTwoLines( aGc, aText, line1, line2,
                                                 line1length, line2length,
                                                 font, aColor, buffer );
        delete hbuf;
        return;
        }
    
    TRAPD( error,
        {
        CArrayFix<TInt>* wrapWidthArray = new( ELeave ) CArrayFixFlat<TInt>(KHgDrawUtilsGranularity);
        CleanupStack::PushL( wrapWidthArray );

        wrapWidthArray->AppendL( line1length );
        wrapWidthArray->AppendL( line2length );
        wrapWidthArray->AppendL( line2length ); // allow wrap to 3 lines
        
        AknBidiTextUtils::ConvertToVisualAndWrapToStringL(
            aText, *wrapWidthArray, *font, buffer, ETrue );

        CleanupStack::PopAndDestroy( wrapWidthArray ); // wrapWidthArray
        } ); // TRAP end


    n = 0;
    for ( i = 0; i < buffer.Length(); i ++)
        {
        if (buffer[i] == '\n')
            {
            n++;
            }
        }

    // wrapping adds a \n to end of each line --> n < 3
    // there is no layout for empty popuplist
    if ( error != KErrNone || n < 3 )
        { // 2 lines which fit to 2 line space
        DrawEmptyListImpl_real_DrawUpToTwoLines( aGc, aText, line1, line2,
                                                 line1length, line2length,
                                                 font, aColor, buffer );
        }
    else
        { // 1 line with big font + 1..3 lines with small font
        DrawEmptyListImpl_real_DrawMoreThanTwoLines( aClientRect, aGc, aText, aColor, buffer );
        }

    delete hbuf;
    }

void CHgDrawUtils::DrawEmptyText(
        CWindowGc& aGc, 
        const TRect& aRect,
        const TDesC& aText,
        const TRgb& aColor 
        ) const
    {
    DrawEmptyListImpl_real(aRect, aGc, aText, aColor);
    }

// -----------------------------------------------------------------------------
// CHgScroller::DrawImage()
// -----------------------------------------------------------------------------
//
void CHgDrawUtils::DrawImage(
        CWindowGc& aGc, 
        const TRect& aRect,
        const TAknWindowComponentLayout& aLayout,
        const CGulIcon& aIcon
        ) const
    {
    TAknLayoutRect image;
    image.LayoutRect(aRect, aLayout);
//    image.DrawImage(aGc, aIcon.Bitmap(), aIcon.Mask());
    TSize slotSize(image.Rect().Size());
    TPoint cropPoint(0,0);
    TPoint toTl(image.Rect().iTl);
    if( aIcon.Bitmap() && aIcon.Bitmap()->SizeInPixels() != slotSize )
        {
        TSize bitmapSize( aIcon.Bitmap()->SizeInPixels() );
        if( bitmapSize.iWidth != slotSize.iWidth )
            {
            if( bitmapSize.iWidth < slotSize.iWidth )
                {
                // Bitmap smaller than slot -> move draw position
                toTl.iX += ( slotSize.iWidth - bitmapSize.iWidth )/2;
                }
            else
                {
                // Slot smaller than bitmap -> move crop rect position
                cropPoint.iX += ( bitmapSize.iWidth - slotSize.iWidth )/2;
                }
            }
        
        if( bitmapSize.iHeight != slotSize.iHeight )
            {
            if( bitmapSize.iHeight < slotSize.iHeight )
                {
                // Bitmap smaller than slot -> move draw position
                toTl.iY += ( slotSize.iHeight - bitmapSize.iHeight )/2;
                }
            else
                {
                // Slot smaller than bitmap -> move crop rect position
                cropPoint.iY += ( bitmapSize.iHeight - slotSize.iHeight )/2;
                }
            }
        }

    TRect cropRect(cropPoint, slotSize);
    
    if (aIcon.Mask()) 
        { 
        aGc.BitBltMasked(toTl, aIcon.Bitmap(), cropRect, aIcon.Mask(), ETrue); 
        }
     else
        {
        aGc.BitBlt(toTl, aIcon.Bitmap(), cropRect);
        }
    }

// -----------------------------------------------------------------------------
// CHgScroller::DrawText()
// -----------------------------------------------------------------------------
//
void CHgDrawUtils::DrawText(
        CWindowGc& aGc, 
        const TRect& aRect,
        const TAknTextComponentLayout& aLayout,
        const TDesC& aText,
        const TRgb& aColor
        ) const
    {
    TAknLayoutText textLayout;
    textLayout.LayoutText(aRect, aLayout.LayoutLine());
    textLayout.DrawText(aGc, aText, ETrue, aColor );
    }

// -----------------------------------------------------------------------------
// CHgScroller::DrawTextMarquee()
// -----------------------------------------------------------------------------
//
void CHgDrawUtils::DrawTextMarquee(
        CWindowGc& aGc, 
        const TRect& aRect,
        const TAknTextComponentLayout& aLayout,
        const TDesC& aText,
        const TRgb& aColor,
        const TInt& aMarqueeLine
        )
    {
    TBool drawn = EFalse;
    
    if( iMarqueeLine == aMarqueeLine)
        
        {
        if( iMarquee->DrawText(
                aGc, 
                aRect, 
                aLayout.LayoutLine(), 
                aText,
                aColor))
            {
            iMarquee->Reset();
            iMarqueeLine++;
            }
        else
            {
            drawn = ETrue;
            }
        }

    if(!drawn)
        {
        DrawText(aGc, aRect, aLayout, aText, aColor);
        }
    }


CHgDrawUtils::CHgDrawUtils()
    {
    
    }

void CHgDrawUtils::ConstructL( TCallBack& aMarqueeCallback )
    {
    iMarquee = CHgMarquee::NewL();
    iMarquee->SetRedrawCallBack( aMarqueeCallback );
    }

void CHgDrawUtils::ResetMarquee()
    {
    if(iMarquee)
        {
        iMarquee->Reset();
        iMarqueeLine = 0;
        }
    }

void CHgDrawUtils::EnableMarquee( TBool aEnable )
    {
    iMarquee->EnableMarquee(aEnable);
    }
