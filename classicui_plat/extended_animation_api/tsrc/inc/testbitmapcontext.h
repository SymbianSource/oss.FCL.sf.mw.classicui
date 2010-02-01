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
* Description:  For Testing extended_animation_api
*
*/



#ifndef C_TESTBITMAPCONTEXT_H
#define C_TESTBITMAPCONTEXT_H

//  INCLUDES
#include <gdi.h>

// CTestBitmapContext for testing DrawNextAnimationStep of CAknAnimationData
class CTestBitmapContext: public CBitmapContext
    {
public:
    
    /**
    * From CBitmapContext
    */
    void Clear();

    /**
     * From CBitmapContext
     * @param aRect is not used.
     */
    void Clear( const TRect& aRect );

    /**
     * From CBitmapContext
     * @param aOffset is not used.
     * @param aRect is not used
     */
    void CopyRect( const TPoint& aOffset, const TRect& aRect );

    /**
     * From CBitmapContext
     * @param aPoint is not used.
     * @param aBitmap is not used.
     */
    void BitBlt( const TPoint& aPoint, const CFbsBitmap* aBitmap );

    /**
     * From CBitmapContext
     * @param aPoint is not used.
     * @param aBitmap is not used.
     * @param aRect is not used.
     */
    void BitBlt( const TPoint& aPoint, const CFbsBitmap* aBitmap, const TRect& aRect );

    /**
     * From CBitmapContext
     * @param aPoint is not used.
     * @param aBitmap is not used.
     * @param aSourceRect is not used.
     * @param aMaskBitmap is not used.
     * @param aInvertMask is not used.
     */
    void BitBltMasked( const TPoint& aPoint,
            const CFbsBitmap* aBitmap, const TRect& aSourceRect,
            const CFbsBitmap* aMaskBitmap, TBool aInvertMask );

    /**
     * From CBitmapContext
     * @param aFaded is not used.
     */
    void SetFaded( TBool aFaded );

    /**
     * From CBitmapContext
     * @param aBlackMap is not used.
     * @param aWhiteMap is not used.
     */
    void SetFadingParameters( TUint8 aBlackMap, TUint8 aWhiteMap );

    /**
     * From CBitmapContext
     * @param aDestPt is not used.
     * @param aSrcBmp is not used.
     * @param aSrcRect is not used.
     * @param aAlphaBmp is not used.
     * @param aAlphaPt is not used.
     */
    TInt AlphaBlendBitmaps( const TPoint& aDestPt,
            const CFbsBitmap* aSrcBmp, const TRect& aSrcRect,
            const CFbsBitmap* aAlphaBmp, const TPoint& aAlphaPt );

    /**
     * From CBitmapContext
     * @param aDestPt is not used.
     * @param aSrcBmp is not used.
     * @param aSrcRect is not used.
     * @param aAlphaBmp is not used.
     * @param aAlphaPt is not used.
     */
    TInt AlphaBlendBitmaps( const TPoint& aDestPt,
            const CWsBitmap* aSrcBmp, const TRect& aSrcRect,
            const CWsBitmap* aAlphaBmp, const TPoint& aAlphaPt );
    
    /**
     * From CGraphicsContext
     */
    CGraphicsDevice* Device() const;

    /**
     * From CGraphicsContext
     * @param aPos is not used.
     */
    void SetOrigin( const TPoint& aPos=TPoint( 0, 0 ) );

    /**
     * From CGraphicsContext
     * @param aDrawingMode is not used.
     */
    void SetDrawMode( TDrawMode aDrawingMode );

    /**
     * From CGraphicsContext
     * @param aRect is not used.
     */
    void SetClippingRect( const TRect& aRect );

    /**
     * From CGraphicsContext
     */
    void CancelClippingRect();

    /**
     * From CGraphicsContext
     */
    void Reset();

    /**
     * From CGraphicsContext
     * @param aFont is not used.
     */
    void UseFont( const CFont* aFont );

    /**
     * From CGraphicsContext
     */
    void DiscardFont();

    /**
     * From CGraphicsContext
     * @param aUnderlineStyle is not used.
     */
    void SetUnderlineStyle( TFontUnderline aUnderlineStyle );

    /**
     * From CGraphicsContext
     * @param aStrikethroughStyle is not used.
     */
   void SetStrikethroughStyle( TFontStrikethrough aStrikethroughStyle );
    
   /**
    * From CGraphicsContext
    * @param aExcessWidth is not used.
    * @param aNumGaps is not used.
    */
    void SetWordJustification( TInt aExcessWidth, TInt aNumGaps );

    /**
     * From CGraphicsContext
     * @param aExcessWidth is not used.
     * @param aNumChars is not used.
     */
    void SetCharJustification( TInt aExcessWidth, TInt aNumChars );

    /**
     * From CGraphicsContext
     * @param aColor is not used.
     */
    void SetPenColor( const TRgb& aColor );

    /**
     * From CGraphicsContext
     * @param aPenStyle is not used.
     */
    void SetPenStyle( TPenStyle aPenStyle );

    /**
     * From CGraphicsContext
     * @param aSize is not used.
     */
    void SetPenSize( const TSize& aSize );

    /**
     * From CGraphicsContext
     * @param aColor is not used.
     */
    void SetBrushColor( const TRgb& aColor );

    /**
     * From CGraphicsContext
     * @param aBrushStyle is not used.
     */
    void SetBrushStyle( TBrushStyle aBrushStyle );

    /**
     * From CGraphicsContext
     * @param aOrigin is not used.
     */
    void SetBrushOrigin( const TPoint& aOrigin );

    /**
     * From CGraphicsContext
     * @param aBitmap is not used.
     */
    void UseBrushPattern( const CFbsBitmap* aBitmap );

    /**
     * From CGraphicsContext
     */
    void DiscardBrushPattern();


    /**
     * From CGraphicsContext
     * @param aPoint is not used.
     */
    void MoveTo( const TPoint& aPoint );

    /**
     * From CGraphicsContext
     * @param aVector is not used.
     */
    void MoveBy( const TPoint& aVector );

    /**
     * From CGraphicsContext
     * @param aPoint is not used.
     */
    void Plot( const TPoint& aPoint );

    /**
     * From CGraphicsContext
     * @param aRect is not used.
     * @param aStart is not used.
     * @param aEnd is not used.
     */
    void DrawArc( const TRect& aRect, const TPoint& aStart, const TPoint& aEnd );

    /**
     * From CGraphicsContext
     * @param aPoint1 is not used.
     * @param aPoint2 is not used.
     */
    void DrawLine( const TPoint& aPoint1, const TPoint& aPoint2 );

    /**
     * From CGraphicsContext
     * @param aPoint is not used.
     */
    void DrawLineTo( const TPoint& aPoint );

    /**
     * From CGraphicsContext
     * @param aVector is not used.
     */
    void DrawLineBy( const TPoint& aVector );

    /**
     * From CGraphicsContext
     * @param aPointList is not used.
     */
    void DrawPolyLine( const CArrayFix<TPoint>* aPointList );

    /**
     * From CGraphicsContext
     * @param aPointList is not used.
     * @param aNumPoints is not used.
     */
    void DrawPolyLine( const TPoint* aPointList, TInt aNumPoints );

    /**
     * From CGraphicsContext
     * @param aRect is not used.
     * @param aStart is not used.
     * @param aEnd is not used.
     */
    void DrawPie( const TRect& aRect, const TPoint& aStart, const TPoint& aEnd );

    /**
     * From CGraphicsContext
     * @param aRect is not used.
     */
    void DrawEllipse( const TRect& aRect );

    /**
     * From CGraphicsContext
     * @param aRect is not used.
     */
    void DrawRect( const TRect& aRect );

    /**
     * From CGraphicsContext
     * @param aRect is not used.
     * @param aCornerSize is not used.
     */
    void DrawRoundRect( const TRect& aRect, const TSize& aCornerSize );

    /**
     * From CGraphicsContext
     * @param aPointList is not used.
     * @param aFillRule is not used.
     */
    TInt DrawPolygon( const CArrayFix<TPoint>* aPointList,
                        TFillRule aFillRule=EAlternate );

    /**
     * From CGraphicsContext
     * @param aPointList is not used.
     * @param aNumPoints is not used.
     * @param aFillRule is not used.
     */
    TInt DrawPolygon( const TPoint* aPointList,
            TInt aNumPoints, TFillRule aFillRule=EAlternate );

    /**
     * From CGraphicsContext
     * @param aTopLeft is not used.
     * @param aSource is not used.
     */
    void DrawBitmap( const TPoint& aTopLeft, const CFbsBitmap* aSource );

    /**
     * From CGraphicsContext
     * @param aDestRect is not used.
     * @param aSource is not used.
     */
    void DrawBitmap( const TRect& aDestRect, const CFbsBitmap* aSource );

    /**
     * From CGraphicsContext
     * @param aDestRect is not used.
     * @param aSource is not used.
     * @param aSourceRect is not used.
     */
    void DrawBitmap( const TRect& aDestRect,
            const CFbsBitmap* aSource, const TRect& aSourceRect );

    /**
     * From CGraphicsContext
     * @param aDestRect is not used.
     * @param aBitmap is not used.
     * @param aSourceRect is not used.
     * @param aMaskBitmap is not used.
     * @param aInvertMask is not used.
     */
    void DrawBitmapMasked( const TRect& aDestRect,
            const CFbsBitmap* aBitmap, const TRect& aSourceRect,
            const CFbsBitmap* aMaskBitmap, TBool aInvertMask );

    /**
     * From CGraphicsContext
     * @param aDestRect is not used.
     * @param aBitmap is not used.
     * @param aSourceRect is not used.
     * @param aMaskBitmap is not used.
     * @param aInvertMask is not used.
     */
     void DrawBitmapMasked( const TRect& aDestRect,
             const CWsBitmap* aBitmap, const TRect& aSourceRect,
             const CWsBitmap* aMaskBitmap, TBool aInvertMask );

     /**
      * From CGraphicsContext
      * @param aText is not used.
      * @param aPosition is not used.
      */
    void DrawText( const TDesC& aText, const TPoint& aPosition );

    /**
     * From CGraphicsContext
     * @param aText is not used.
     * @param aBox is not used.
     * @param aBaselineOffset is not used.
     * @param aAlignment is not used.
     * @param aLeftMargin is not used.
     */
    void DrawText( const TDesC& aText,
            const TRect& aBox, TInt aBaselineOffset,
            TTextAlign aAlignment = ELeft, TInt aLeftMargin = 0 );
    
    /**
     * From CGraphicsContext
     * @param aRect is not used.
     * @param aColors is not used.
     * @param aNumPairs is not used.
     * @param aMapForwards is not used.
     */
    void MapColors( const TRect& aRect, const TRgb* aColors,
                             TInt aNumPairs, TBool aMapForwards );
    
    /**
     * From CGraphicsContext
     * @param aRegion is not used.
     */
    TInt SetClippingRegion( const TRegion& aRegion );
    
    /**
     * From CGraphicsContext
     */
    void CancelClippingRegion();
    
    /**
     * From CGraphicsContext
     * @param aText is not used.
     * @param aPos is not used.
     * @param aUp is not used.
     */
    void DrawTextVertical( const TDesC& aText, const TPoint& aPos, TBool aUp );
    
    /**
     * From CGraphicsContext
     * @param aText is not used.
     * @param aBox is not used.
     * @param aBaselineOffset is not used.
     * @param aUp is not used.
     * @param ELeft is not used.
     * @param aMargin is not used.
     */
    void DrawTextVertical( const TDesC& aText,
            const TRect& aBox, TInt aBaselineOffset,
            TBool aUp, TTextAlign aVert=ELeft, TInt aMargin=0 );
    
    };


#endif //C_TESTBITMAPCONTEXT_H

// End of File
