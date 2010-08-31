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
* Description:  Recording graphics context used to cache drawing commands.
*
*/


#include <w32std.h>

class CFbsBitmap;
class CFbsBitGc;
class CFbsBitmapDevice;

NONSHARABLE_CLASS( CAknRecordingGc ) : public CWindowGc
    {
public:
//	CWindowGc(CWsScreenDevice *aDevice);
	CAknRecordingGc(CWindowGc *aRealGc);
	virtual ~CAknRecordingGc();
	void ConstructL(  const TSize& aSize );
	virtual void Activate(RDrawableWindow &aDevice);
	virtual void Deactivate();
//====================FROM CGraphicsContext.H===============================
	virtual CGraphicsDevice* Device() const;
	virtual void SetOrigin(const TPoint &aPoint=TPoint(0,0));
	virtual void SetDrawMode(TDrawMode aDrawingMode);
	virtual void SetClippingRect(const TRect& aRect);
	virtual void CancelClippingRect();
	virtual void Reset();

	virtual void UseFont(const CFont *aFont);
	virtual void DiscardFont();
	virtual void SetUnderlineStyle(TFontUnderline aUnderlineStyle);
	virtual void SetStrikethroughStyle(TFontStrikethrough aStrikethroughStyle);
// Used to do justified text properly
	virtual void SetWordJustification(TInt aExcessWidth,TInt aNumGaps);
// Used primarily to get accurate WYSIWYG
	virtual void SetCharJustification(TInt aExcessWidth,TInt aNumChars);

	virtual void SetPenColor(const TRgb &aColor);
	virtual void SetPenStyle(TPenStyle aPenStyle);
	virtual void SetPenSize(const TSize& aSize);

	virtual void SetBrushColor(const TRgb &aColor);
	virtual void SetBrushStyle(TBrushStyle aBrushStyle);
	virtual void SetBrushOrigin(const TPoint &aOrigin);
	virtual void UseBrushPattern(const CFbsBitmap *aDevice);
	virtual void DiscardBrushPattern();
//
// Move the internal position, as used by DrawLineTo & DrawLineBy, and set by MoveTo,
// MoveBy, DrawLine, DrawLineTo, DrawLineBy and DrawPolyline
	virtual void MoveTo(const TPoint &aPoint);
	virtual void MoveBy(const TPoint &aPoint);
	virtual void Plot(const TPoint &aPoint);
//
//  Line drawing subject to pen color, width and style and draw mode
	virtual void DrawArc(const TRect &aRect,const TPoint &aStart,const TPoint &aEnd);
	virtual void DrawLine(const TPoint &aPoint1,const TPoint &aPoint2);
	virtual void DrawLineTo(const TPoint &aPoint);
	virtual void DrawLineBy(const TPoint &aPoint);
	virtual void DrawPolyLine(const CArrayFix<TPoint> *aPointList);
	virtual void DrawPolyLine(const TPoint* aPointList,TInt aNumPoints);
//
// Filled outlines
// Outlines subject to pen color, width and style and draw mode
// (set pen to ENullPen for no outline)
// Fill subject to brush style (color, hash or pattern) and origin and
// drawing mode (set brush to ENullBrush for no fill)
	virtual void DrawPie(const TRect &aRect,const TPoint &aStart,const TPoint &aEnd);
	virtual void DrawEllipse(const TRect &aRect);
	virtual void DrawRect(const TRect &aRect);
	virtual void DrawRoundRect(const TRect &aRect,const TSize &aEllipse);
	virtual TInt DrawPolygon(const CArrayFix<TPoint> *aPointList,TFillRule aFillRule=EAlternate);
	virtual TInt DrawPolygon(const TPoint* aPointList,TInt aNumPoints,TFillRule aFillRule=EAlternate);
//
// Uses the bitmap's Twips size and does a "stretch" blit in general
	virtual void DrawBitmap(const TPoint &aTopLeft, const CFbsBitmap *aDevice);
	virtual void DrawBitmap(const TRect &aDestRect, const CFbsBitmap *aDevice);
	virtual void DrawBitmap(const TRect &aDestRect, const CFbsBitmap *aDevice, const TRect &aSourceRect);
	virtual void DrawBitmapMasked(const TRect& aDestRect, const CFbsBitmap* aBitmap, const TRect& aSourceRect, const CFbsBitmap* aMaskBitmap, TBool aInvertMask);
	virtual void DrawBitmapMasked(const TRect& aDestRect, const CWsBitmap* aBitmap, const TRect& aSourceRect, const CWsBitmap* aMaskBitmap, TBool aInvertMask);
//
// Text drawing subject to drawing mode
// Subject to used font, pen color, drawing mode,
// word and char justification
	virtual void DrawText(const TDesC &aBuf,const TPoint &aPos);
//
// Subject to same as above plus brush for background
// (set brush to ENullBrush for no effect on background)
	virtual void DrawText(const TDesC &aBuf,const TRect &aBox,TInt aBaselineOffset,TTextAlign aHoriz=ELeft,TInt aLeftMrg=0);
//================Extra functions from CBitmapContext==============
	virtual void Clear();
	virtual void Clear(const TRect &aRect);
	virtual void CopyRect(const TPoint &anOffset,const TRect &aRect);
	virtual void BitBlt(const TPoint &aPos, const CFbsBitmap *aBitmap);
	virtual void BitBlt(const TPoint &aDestination, const CFbsBitmap *aBitmap, const TRect &aSource);
	virtual void BitBltMasked(const TPoint& aPoint,const CFbsBitmap* aBitmap,const TRect& aSourceRect,const CFbsBitmap* aMaskBitmap,TBool aInvertMask);
	virtual void BitBlt(const TPoint &aPoint, const CWsBitmap *aBitmap);
	virtual void BitBlt(const TPoint &aDestination, const CWsBitmap *aBitmap, const TRect &aSource);
	virtual void BitBltMasked(const TPoint& aPoint,const CWsBitmap *aBitmap,const TRect& aSourceRect,const CWsBitmap *aMaskBitmap,TBool aInvertMask);
	virtual void MapColors(const TRect& aRect,const TRgb* aColors,TInt aNumPairs=2,TBool aMapForwards=ETrue);

	virtual void DrawTextVertical(const TDesC& aText,const TPoint& aPos,TBool aUp);
	virtual void DrawTextVertical(const TDesC& aText,const TRect& aBox,TInt aBaselineOffset,TBool aUp,TTextAlign aVert=ELeft,TInt aMargin=0);
//=================Extra functions specific to wserv GDI==============
	virtual void SetDitherOrigin(const TPoint& aPoint);
	virtual TInt SetClippingRegion(const TRegion &aRegion);
	virtual void CancelClippingRegion();
	virtual void SetOpaque(TBool aDrawOpaque=ETrue);
//=================Functions also supplied by CFbsBitGc==============
	virtual void SetFaded(TBool aFaded);
	virtual void SetFadingParameters(TUint8 aBlackMap,TUint8 aWhiteMap);
	virtual TInt AlphaBlendBitmaps(const TPoint& aDestPt, const CFbsBitmap* aSrcBmp, const TRect& aSrcRect, const CFbsBitmap* aAlphaBmp, const TPoint& aAlphaPt);
	virtual TInt AlphaBlendBitmaps(const TPoint& aDestPt, const CWsBitmap* aSrcBmp, const TRect& aSrcRect, const CWsBitmap* aAlphaBmp, const TPoint& aAlphaPt);
	
	virtual TAny* Interface( TUid aInterfaceId );
    virtual const TAny* Interface( TUid aInterfaceId ) const;
    
protected:  
    virtual TInt APIExtension( TUid aUid, TAny*& aOutput, TAny* aInput );
    
public:
	void FlushBuffer( const TRect& aRect, TInt aLineToSkip );
	void PurgeBuffer();
	void PrepareForNewLineL( const TRect& aRect );
	void ReplaceLineL( TInt aLine );
	void InsertLineL( TInt aLine, const TRect& aRect );
	void InsertLineL( TInt aLine );
	void AppendLineL();
	void PurgeLine( TInt aLine );
	void SetLineRect( TInt aLine, const TRect& aRect );
	void DeleteLine( TInt aLine );
	
	void UseBitGc( TBool aUseBitGc );
	
private:
    NONSHARABLE_CLASS( CBufferItem ) : public CBase
        {
        public:
        enum TCommandType
            {
            EShortText,
            ELongText,
            ESetPenColor,
            EBitBlt1,
            EBitBlt2,
            EBitBltMasked1,
            EUseFont,
            EDiscardFont,
            ESetDrawMode,
            ESetClippingRect,
            ECancelClippingRect,
            ESetBrushColor,
            ESetBrushStyle,
            EDrawRect,
            EClear
            };
        
        public:
            ~CBufferItem();
            
            TInt iType;
            HBufC* iText;
            TPoint iPosition;
            TRect iBox;
            TInt iBaseLineOffset;
            TTextAlign iHorizontal;
            TInt iLeftMargin;
            TRgb iColor;
            const CFbsBitmap* iBitmap;
            const CFbsBitmap* iMask;
            TRect iSource;
            TBool iInvertMask;
            const CFont* iFont;
            TDrawMode iDrawMode;
            TBrushStyle iBrushStyle;
            TRect iRect;
        };
        
    NONSHARABLE_CLASS( CLineData ) : public CBase
        {
        public:
            ~CLineData();
            TRect iRect;
            RPointerArray<CBufferItem> iItems;
            
        };
    
    CBufferItem* BufferItem();
        
    CWindowGc* iRealGc;
    RPointerArray<CLineData> iLines;
    CFont* iFont;
    CFbsBitmap* iOffScreenBmp;
    CFbsBitGc* iBitGc;
    CFbsBitmapDevice* iBitmapDevice;
    TInt iCurrentLine;
    TBool iUseBitGc;
    };

