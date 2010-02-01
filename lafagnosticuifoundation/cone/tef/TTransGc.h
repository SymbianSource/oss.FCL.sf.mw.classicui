// Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
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

/**
 @file 
 @internalComponent - Internal Symbian test code 
*/



#if !defined(__TTRANSGC_H__)
#define __TTRANSGC_H__

#include <w32std.h>

/** Maps a CWindowGc to a CFbsBitGc class. The majority of these function are one to one mappings, 
	with the exception of "application specific" 
	@test
*/

class CTransGc : public CWindowGc
	{
public:
	IMPORT_C static CTransGc* NewL(CWsScreenDevice& aDevice,CFbsBitGc& aFbsBitGc);
	virtual ~CTransGc();
	virtual CGraphicsDevice* Device() const;
	virtual void Activate(RDrawableWindow &aWindow);
	virtual void Deactivate();
	virtual void SetOrigin(const TPoint &aPos=TPoint(0,0));
	virtual void SetDrawMode(TDrawMode aDrawingMode);
	virtual void SetClippingRect(const TRect& aRect);
	virtual void CancelClippingRect();
	virtual void Reset();
	virtual void UseFont(const CFont *aFont);
	virtual void DiscardFont();
	virtual void SetUnderlineStyle(TFontUnderline aUnderlineStyle);
	virtual void SetStrikethroughStyle(TFontStrikethrough aStrikethroughStyle);
	virtual void SetWordJustification(TInt aExcessWidth,TInt aNumGaps);
	virtual void SetCharJustification(TInt aExcessWidth,TInt aNumChars);
	virtual void SetPenColor(const TRgb &aColor);
	virtual void SetPenStyle(TPenStyle aPenStyle);
	virtual void SetPenSize(const TSize& aSize);
	virtual void SetBrushColor(const TRgb &aColor);
	virtual void SetBrushStyle(TBrushStyle aBrushStyle);
	virtual void SetBrushOrigin(const TPoint &aOrigin);
	virtual void UseBrushPattern(const CFbsBitmap *aBitmap);
	virtual void DiscardBrushPattern();
	virtual void MoveTo(const TPoint &aPoint);
	virtual void MoveBy(const TPoint &aVector);
	virtual void Plot(const TPoint &aPoint);
	virtual void DrawArc(const TRect &aRect,const TPoint &aStart,const TPoint &aEnd);
	virtual void DrawLine(const TPoint &aPoint1,const TPoint &aPoint2);
	virtual void DrawLineTo(const TPoint &aPoint);
	virtual void DrawLineBy(const TPoint &aVector);
	virtual void DrawPolyLine(const CArrayFix<TPoint> *aPointList);
	virtual void DrawPolyLine(const TPoint* aPointList,TInt aNumPoints);
	virtual void DrawPie(const TRect &aRect,const TPoint &aStart,const TPoint &aEnd);
	virtual void DrawEllipse(const TRect &aRect);
	virtual void DrawRect(const TRect &aRect);
	virtual void DrawRoundRect(const TRect &aRect,const TSize &aEllipse);
	virtual TInt DrawPolygon(const CArrayFix<TPoint> *aPointList,TFillRule aFillRule=EAlternate);
	virtual TInt DrawPolygon(const TPoint* aPointList,TInt aNumPoints,TFillRule aFillRule=EAlternate);
	virtual void DrawBitmap(const TPoint &aTopLeft, const CFbsBitmap *aSource);
	virtual void DrawBitmap(const TRect &aDestRect, const CFbsBitmap *aSource);
	virtual void DrawBitmap(const TRect &aDestRect, const CFbsBitmap *aSource, const TRect &aSourceRect);
	virtual void DrawText(const TDesC &aString,const TPoint &aPosition);
	virtual void DrawText(const TDesC &aString,const TRect &aBox,TInt aBaselineOffset,TTextAlign aHoriz=ELeft,TInt aLeftMrg=0);
	virtual void Clear();
	virtual void Clear(const TRect &aRect);
	virtual void CopyRect(const TPoint &aOffset,const TRect &aRect);
	virtual void BitBlt(const TPoint &aPos, const CFbsBitmap *aDevice);
	virtual void BitBlt(const TPoint &aPos, const CFbsBitmap *aDevice, const TRect &aRect);
	virtual void BitBltMasked(const TPoint& aPoint,const CFbsBitmap* aBitmap,const TRect& aSourceRect,const CFbsBitmap* aMaskBitmap,TBool aInvertMask);
	virtual void BitBlt(const TPoint &aPos, const CWsBitmap *aDevice);
	virtual void BitBlt(const TPoint &aPos, const CWsBitmap *aDevice, const TRect &aRect);
	virtual void BitBltMasked(const TPoint& aPoint,const CWsBitmap *aBitmap,const TRect& aSourceRect,const CWsBitmap *aMaskBitmap,TBool aInvertMask);
	virtual void MapColors(const TRect& aRect,const TRgb* aColors,TInt aNumPairs=2,TBool aMapForwards=ETrue);

	virtual void DrawTextVertical(const TDesC& aText,const TPoint& aPosition,TBool aUp);
	virtual void DrawTextVertical(const TDesC& aText,const TRect& aBox,TInt aBaselineOffset,TBool aUp,TTextAlign aVert=ELeft,TInt aMargin=0);
	virtual void SetDitherOrigin(const TPoint& aPoint);
	virtual TInt SetClippingRegion(const TRegion &aClippingRegion);
	virtual void CancelClippingRegion();
	virtual void SetFaded(TBool aFaded);
	virtual void SetFadingParameters(TUint8 aBlackMap,TUint8 aWhiteMap);
	CTransGc(CWsScreenDevice& aDevice,CFbsBitGc& aFbsBitGc);

//Application specific functions and variables
	void SetAlphaLevel(TInt aAlpha);
	void SetWindowOrigin(TPoint aOrigin);
private:
	CFbsBitGc& iFbsBitGc;	// not owned by this class
	TInt iAlpha;			// Current alpha level
	TPoint iGcOrigin;		// The relative origin of the current window
	TPoint iWindowOrigin;	// The relative window origin of the Gc	

public:
	RDrawableWindow *iWin;	// The current window being drawn
	};

#endif
