// Copyright (c) 2001-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
//

#if !defined(__GULGCMAP_H__)
#define __GULGCMAP_H__

#include <w32std.h>


class CWindowToBitmapMappingGc : public CWindowGc
/**
@publishedPartner
@released 
*/
	{
public:
	IMPORT_C static CWindowToBitmapMappingGc* NewL(CWsScreenDevice& aDevice,CFbsBitGc& aFbsBitGc);
	IMPORT_C virtual ~CWindowToBitmapMappingGc();
//====================FROM CGraphicsContext.H===============================
	IMPORT_C virtual CGraphicsDevice* Device() const;
	IMPORT_C virtual void Activate(RDrawableWindow &aWindow);
	IMPORT_C virtual void Deactivate();
	IMPORT_C virtual void SetOrigin(const TPoint &aPos=TPoint(0,0));
	IMPORT_C virtual void SetDrawMode(TDrawMode aDrawingMode);
	IMPORT_C virtual void SetClippingRect(const TRect& aRect);
	IMPORT_C virtual void CancelClippingRect();
	IMPORT_C virtual void Reset();

	IMPORT_C virtual void UseFont(const CFont *aFont);
	IMPORT_C virtual void DiscardFont();
	IMPORT_C virtual void SetUnderlineStyle(TFontUnderline aUnderlineStyle);
	IMPORT_C virtual void SetStrikethroughStyle(TFontStrikethrough aStrikethroughStyle);
// Used to do justified text properly
	IMPORT_C virtual void SetWordJustification(TInt aExcessWidth,TInt aNumGaps);
// Used primarily to get accurate WYSIWYG
	IMPORT_C virtual void SetCharJustification(TInt aExcessWidth,TInt aNumChars);

	IMPORT_C virtual void SetPenColor(const TRgb &aColor);
	IMPORT_C virtual void SetPenStyle(TPenStyle aPenStyle);
	IMPORT_C virtual void SetPenSize(const TSize& aSize);

	IMPORT_C virtual void SetBrushColor(const TRgb &aColor);
	IMPORT_C virtual void SetBrushStyle(TBrushStyle aBrushStyle);
	IMPORT_C virtual void SetBrushOrigin(const TPoint &aOrigin);
	IMPORT_C virtual void UseBrushPattern(const CFbsBitmap *aBitmap);
	IMPORT_C virtual void DiscardBrushPattern();
//
// Move the internal position, as used by DrawLineTo & DrawLineBy, and set by MoveTo,
// MoveBy, DrawLine, DrawLineTo, DrawLineBy and DrawPolyline
	IMPORT_C virtual void MoveTo(const TPoint &aPoint);
	IMPORT_C virtual void MoveBy(const TPoint &aVector);
	IMPORT_C virtual void Plot(const TPoint &aPoint);
//
//  Line drawing subject to pen color, width and style and draw mode
	IMPORT_C virtual void DrawArc(const TRect &aRect,const TPoint &aStart,const TPoint &aEnd);
	IMPORT_C virtual void DrawLine(const TPoint &aPoint1,const TPoint &aPoint2);
	IMPORT_C virtual void DrawLineTo(const TPoint &aPoint);
	IMPORT_C virtual void DrawLineBy(const TPoint &aVector);
	IMPORT_C virtual void DrawPolyLine(const CArrayFix<TPoint> *aPointList);
	IMPORT_C virtual void DrawPolyLine(const TPoint* aPointList,TInt aNumPoints);
//
// Filled outlines
// Outlines subject to pen color, width and style and draw mode
// (set pen to ENullPen for no outline)
// Fill subject to brush style (color, hash or pattern) and origin and
// drawing mode (set brush to ENullBrush for no fill)
	IMPORT_C virtual void DrawPie(const TRect &aRect,const TPoint &aStart,const TPoint &aEnd);
	IMPORT_C virtual void DrawEllipse(const TRect &aRect);
	IMPORT_C virtual void DrawRect(const TRect &aRect);
	IMPORT_C virtual void DrawRoundRect(const TRect &aRect,const TSize &aEllipse);
	IMPORT_C virtual TInt DrawPolygon(const CArrayFix<TPoint> *aPointList,TFillRule aFillRule=EAlternate);
	IMPORT_C virtual TInt DrawPolygon(const TPoint* aPointList,TInt aNumPoints,TFillRule aFillRule=EAlternate);
//
// Uses the bitmap's Twips size and does a "stretch" blit in general
	IMPORT_C virtual void DrawBitmap(const TPoint &aTopLeft, const CFbsBitmap *aSource);
	IMPORT_C virtual void DrawBitmap(const TRect &aDestRect, const CFbsBitmap *aSource);
	IMPORT_C virtual void DrawBitmap(const TRect &aDestRect, const CFbsBitmap *aSource, const TRect &aSourceRect);
	IMPORT_C virtual void DrawBitmapMasked(const TRect& aDestRect, const CFbsBitmap* aBitmap, const TRect& aSourceRect, const CFbsBitmap* aMaskBitmap, TBool aInvertMask);
	IMPORT_C virtual void DrawBitmapMasked(const TRect& aDestRect, const CWsBitmap* aBitmap, const TRect& aSourceRect, const CWsBitmap* aMaskBitmap, TBool aInvertMask);

//
// Text drawing subject to drawing mode
// Subject to used font, pen color, drawing mode, 
// word and char justification
	IMPORT_C virtual void DrawText(const TDesC &aString,const TPoint &aPosition);
//
// Subject to same as above plus brush for background
// (set brush to ENullBrush for no effect on background)
	IMPORT_C virtual void DrawText(const TDesC &aString,const TRect &aBox,TInt aBaselineOffset,TTextAlign aHoriz=ELeft,TInt aLeftMrg=0);
//================Extra functions from CBitmapContext==============
	IMPORT_C virtual void Clear();
	IMPORT_C virtual void Clear(const TRect &aRect);
	IMPORT_C virtual void CopyRect(const TPoint &aOffset,const TRect &aRect);
	IMPORT_C virtual void BitBlt(const TPoint &aPos, const CFbsBitmap *aDevice);
	IMPORT_C virtual void BitBlt(const TPoint &aPos, const CFbsBitmap *aDevice, const TRect &aRect);
	IMPORT_C virtual void BitBltMasked(const TPoint& aPoint,const CFbsBitmap* aBitmap,const TRect& aSourceRect,const CFbsBitmap* aMaskBitmap,TBool aInvertMask);
	IMPORT_C virtual void BitBlt(const TPoint &aPos, const CWsBitmap *aDevice);
	IMPORT_C virtual void BitBlt(const TPoint &aPos, const CWsBitmap *aDevice, const TRect &aRect);
	IMPORT_C virtual void BitBltMasked(const TPoint& aPoint,const CWsBitmap *aBitmap,const TRect& aSourceRect,const CWsBitmap *aMaskBitmap,TBool aInvertMask);
	IMPORT_C virtual void MapColors(const TRect& aRect,const TRgb* aColors,TInt aNumPairs=2,TBool aMapForwards=ETrue);

	IMPORT_C virtual void DrawTextVertical(const TDesC& aText,const TPoint& aPosition,TBool aUp);
	IMPORT_C virtual void DrawTextVertical(const TDesC& aText,const TRect& aBox,TInt aBaselineOffset,TBool aUp,TTextAlign aVert=ELeft,TInt aMargin=0);
//=================Extra functions specific to wserv GDI==============
	IMPORT_C virtual void SetDitherOrigin(const TPoint& aPoint);
	IMPORT_C virtual TInt SetClippingRegion(const TRegion &aClippingRegion);
	IMPORT_C virtual void CancelClippingRegion();
	IMPORT_C virtual void SetOpaque(TBool aDrawOpaque=ETrue);
//=================Functions also supplied by CFbsBitGc==============
	IMPORT_C void SetFaded(TBool aFaded);
	IMPORT_C void SetFadingParameters(TUint8 aBlackMap,TUint8 aWhiteMap);
	IMPORT_C TInt AlphaBlendBitmaps(const TPoint& aDestPt, const CFbsBitmap* aSrcBmp, const TRect& aSrcRect, const CFbsBitmap* aAlphaBmp, const TPoint& aAlphaPt);	
	IMPORT_C TInt AlphaBlendBitmaps(const TPoint& aDestPt, const CWsBitmap* aSrcBmp,	const TRect& aSrcRect, const CWsBitmap* aAlphaBmp, const TPoint& aAlphaPt);

//=============================================================
protected:
	IMPORT_C CWindowToBitmapMappingGc(CWsScreenDevice& aDevice,CFbsBitGc& aFbsBitGc);
	
private:
	CFbsBitGc& iFbsBitGc;	// not owned by this class
	};

#endif
