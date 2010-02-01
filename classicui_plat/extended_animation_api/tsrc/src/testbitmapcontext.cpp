/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  function implement of CTestBitmapContext
*
*/



// [INCLUDE FILES]
#include "testbitmapcontext.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestBitmapContext::Clear
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::Clear()
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::Clear
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::Clear( const TRect& /*aRect*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::CopyRect
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::CopyRect( const TPoint& /*aOffset*/, const TRect& /*aRect*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::BitBlt
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::BitBlt( const TPoint& /*aPoint*/, const CFbsBitmap* /*aBitmap*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::BitBlt
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::BitBlt( const TPoint& /*aPoint*/,
        const CFbsBitmap* /*aBitmap*/, const TRect& /*aRect*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::BitBltMasked
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::BitBltMasked( const TPoint& /*aPoint*/,
        const CFbsBitmap* /*aBitmap*/, const TRect& /*aSourceRect*/,
        const CFbsBitmap* /*aMaskBitmap*/, TBool /*aInvertMask*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::SetFaded
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::SetFaded( TBool /*aFaded*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::SetFadingParameters
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::SetFadingParameters( TUint8 /*aBlackMap*/, TUint8 /*aWhiteMap*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::AlphaBlendBitmaps
// -----------------------------------------------------------------------------
//
TInt CTestBitmapContext::AlphaBlendBitmaps( const TPoint& /*aDestPt*/,
        const CFbsBitmap* /*aSrcBmp*/, const TRect& /*aSrcRect*/,
        const CFbsBitmap* /*aAlphaBmp*/, const TPoint& /*aAlphaPt*/ )
    {
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::AlphaBlendBitmaps
// -----------------------------------------------------------------------------
//
TInt CTestBitmapContext::AlphaBlendBitmaps( const TPoint& /*aDestPt*/,
        const CWsBitmap* /*aSrcBmp*/, const TRect& /*aSrcRect*/,
        const CWsBitmap* /*aAlphaBmp*/, const TPoint& /*aAlphaPt*/ )
    {
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::AlphaBlendBitmaps
// -----------------------------------------------------------------------------
//
CGraphicsDevice* CTestBitmapContext::Device() const
    {
    return NULL;
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::SetOrigin
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::SetOrigin( const TPoint& /*aPos*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::SetDrawMode
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::SetDrawMode( TDrawMode /*aDrawingMode*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::SetClippingRect
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::SetClippingRect( const TRect& /*aRect*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::SetClippingRect
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::CancelClippingRect()
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::Reset
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::Reset()
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::UseFont
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::UseFont( const CFont* /*aFont*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::DiscardFont
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::DiscardFont()
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::SetUnderlineStyle
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::SetUnderlineStyle( TFontUnderline /*aUnderlineStyle*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::SetStrikethroughStyle
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::SetStrikethroughStyle( TFontStrikethrough /*aStrikethroughStyle*/ )
    {
    }
    
// -----------------------------------------------------------------------------
// CTestBitmapContext::SetWordJustification
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::SetWordJustification( TInt /*aExcessWidth*/, TInt /*aNumGaps*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::SetCharJustification
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::SetCharJustification( TInt /*aExcessWidth*/, TInt /*aNumChars*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::SetPenColor
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::SetPenColor( const TRgb& /*aColor*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::SetPenStyle
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::SetPenStyle( TPenStyle /*aPenStyle*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::SetPenSize
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::SetPenSize( const TSize& /*aSize*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::SetBrushColor
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::SetBrushColor( const TRgb& /*aColor*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::SetBrushStyle
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::SetBrushStyle( TBrushStyle /*aBrushStyle*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::SetBrushOrigin
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::SetBrushOrigin( const TPoint& /*aOrigin*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::UseBrushPattern
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::UseBrushPattern( const CFbsBitmap* /*aBitmap*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::DiscardBrushPattern
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::DiscardBrushPattern()
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::MoveTo
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::MoveTo( const TPoint& /*aPoint*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::MoveBy
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::MoveBy( const TPoint& /*aVector*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::Plot
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::Plot( const TPoint& /*aPoint*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::DrawArc
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::DrawArc( const TRect& /*aRect*/,
        const TPoint& /*aStart*/, const TPoint& /*aEnd*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::DrawLine
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::DrawLine( const TPoint& /*aPoint1*/, const TPoint& /*aPoint2*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::DrawLineTo
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::DrawLineTo( const TPoint& /*aPoint*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::DrawLineBy
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::DrawLineBy( const TPoint& /*aVector*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::DrawPolyLine
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::DrawPolyLine( const CArrayFix<TPoint>* /*aPointList*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::DrawPolyLine
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::DrawPolyLine( const TPoint* /*aPointList*/, TInt /*aNumPoints*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::DrawPie
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::DrawPie( const TRect& /*aRect*/,
        const TPoint& /*aStart*/, const TPoint& /*aEnd*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::DrawEllipse
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::DrawEllipse( const TRect& /*aRect*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::DrawRect
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::DrawRect( const TRect& /*aRect*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::DrawRoundRect
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::DrawRoundRect( const TRect& /*aRect*/, const TSize& /*aCornerSize*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::DrawPolygon
// -----------------------------------------------------------------------------
//
TInt CTestBitmapContext::DrawPolygon( const CArrayFix<TPoint>* /*aPointList*/,
                    TFillRule /*aFillRule*/ )
    {
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::DrawPolygon
// -----------------------------------------------------------------------------
//
TInt CTestBitmapContext::DrawPolygon( const TPoint* /*aPointList*/,
        TInt /*aNumPoints*/, TFillRule /*aFillRule*/ )
    {
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::DrawBitmap
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::DrawBitmap( const TPoint& /*aTopLeft*/, const CFbsBitmap* /*aSource*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::DrawBitmap
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::DrawBitmap( const TRect& /*aDestRect*/, const CFbsBitmap* /*aSource*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::DrawBitmap
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::DrawBitmap( const TRect& /*aDestRect*/,
        const CFbsBitmap* /*aSource*/, const TRect& /*aSourceRect*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::DrawBitmapMasked
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::DrawBitmapMasked( const TRect& /*aDestRect*/,
        const CFbsBitmap* /*aBitmap*/, const TRect& /*aSourceRect*/,
        const CFbsBitmap* /*aMaskBitmap*/, TBool /*aInvertMask*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::DrawBitmapMasked
// -----------------------------------------------------------------------------
//
 void CTestBitmapContext::DrawBitmapMasked( const TRect& /*aDestRect*/,
         const CWsBitmap* /*aBitmap*/, const TRect& /*aSourceRect*/,
         const CWsBitmap* /*aMaskBitmap*/, TBool /*aInvertMask*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::DrawText
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::DrawText( const TDesC& /*aText*/, const TPoint& /*aPosition*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::DrawText
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::DrawText( const TDesC& /*aText*/,
        const TRect& /*aBox*/, TInt /*aBaselineOffset*/,
        TTextAlign /*aAlignment*/, TInt /*aLeftMargin*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::MapColors
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::MapColors( const TRect& /*aRect*/, const TRgb* /*aColors*/,
                         TInt /*aNumPairs*/, TBool /*aMapForwards*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::SetClippingRegion
// -----------------------------------------------------------------------------
//
TInt CTestBitmapContext::SetClippingRegion( const TRegion& /*aRegion*/ )
    {
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::CancelClippingRegion
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::CancelClippingRegion()
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::DrawTextVertical
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::DrawTextVertical( const TDesC& /*aText*/,
        const TPoint& /*aPos*/, TBool /*aUp*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestBitmapContext::DrawTextVertical
// -----------------------------------------------------------------------------
//
void CTestBitmapContext::DrawTextVertical( const TDesC& /*aText*/,
        const TRect& /*aBox*/, TInt /*aBaselineOffset*/,
        TBool /*aUp*/, TTextAlign /*aVert*/, TInt /*aMargin*/ )
    {
    }

// [End of File]

