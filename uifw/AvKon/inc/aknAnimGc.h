/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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



// AknAnimGc.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Animation View Redirection GC


#if !defined(__AKNANIMGC_H__)
#define __AKNANIMGC_H__

#include <w32std.h>



NONSHARABLE_CLASS(CAknAnimatedGc) : public CWindowGc
	{
public:
	static CAknAnimatedGc* NewL(CWindowGc& aOldGc, CFbsBitGc& aReGc); 
	void SetRootWindow(const RWindowTreeNode& aRootWin);
	~CAknAnimatedGc();
	void SetScreenDevice(const CWsScreenDevice* aScreen);
protected:
	CAknAnimatedGc(CWsScreenDevice& aScreen, CFbsBitGc& aReGc, CWindowGc& aOldGc);
	// From CWindowGc
	IMPORT_C virtual void Activate(RDrawableWindow &aWindow);
	IMPORT_C virtual void Deactivate();

	IMPORT_C virtual CGraphicsDevice* Device() const;
	IMPORT_C virtual void SetOrigin(const TPoint &aPos=TPoint(0,0));
	IMPORT_C virtual void SetDrawMode(TDrawMode aDrawingMode);
	IMPORT_C virtual void SetClippingRect(const TRect& aRect);
	IMPORT_C virtual void CancelClippingRect();
	IMPORT_C virtual void Reset();

	IMPORT_C virtual void UseFont(const CFont *aFont);
	IMPORT_C virtual void DiscardFont();
	IMPORT_C virtual void SetUnderlineStyle(TFontUnderline aUnderlineStyle);
	IMPORT_C virtual void SetStrikethroughStyle(TFontStrikethrough aStrikethroughStyle);
	IMPORT_C virtual void SetWordJustification(TInt aExcessWidth,TInt aNumGaps);
	IMPORT_C virtual void SetCharJustification(TInt aExcessWidth,TInt aNumChars);

	IMPORT_C virtual void SetPenColor(const TRgb &aColor);
	IMPORT_C virtual void SetPenStyle(TPenStyle aPenStyle);
	IMPORT_C virtual void SetPenSize(const TSize& aSize);

	IMPORT_C virtual void SetBrushColor(const TRgb &aColor);
	IMPORT_C virtual void SetBrushStyle(TBrushStyle aBrushStyle);
	IMPORT_C virtual void SetBrushOrigin(const TPoint &aOrigin);
	IMPORT_C virtual void UseBrushPattern(const CFbsBitmap *aBitmap);
	IMPORT_C virtual void DiscardBrushPattern();

	IMPORT_C virtual void MoveTo(const TPoint &aPoint);
	IMPORT_C virtual void MoveBy(const TPoint &aVector);
	IMPORT_C virtual void Plot(const TPoint &aPoint);

	IMPORT_C virtual void DrawArc(const TRect &aRect,const TPoint &aStart,const TPoint &aEnd);
	IMPORT_C virtual void DrawLine(const TPoint &aPoint1,const TPoint &aPoint2);
	IMPORT_C virtual void DrawLineTo(const TPoint &aPoint);
	IMPORT_C virtual void DrawLineBy(const TPoint &aVector);
	IMPORT_C virtual void DrawPolyLine(const CArrayFix<TPoint> *aPointList);
	IMPORT_C virtual void DrawPolyLine(const TPoint* aPointList,TInt aNumPoints);

	IMPORT_C virtual void DrawPie(const TRect &aRect,const TPoint &aStart,const TPoint &aEnd);
	IMPORT_C virtual void DrawEllipse(const TRect &aRect);
	IMPORT_C virtual void DrawRect(const TRect &aRect);
	IMPORT_C virtual void DrawRoundRect(const TRect &aRect,const TSize &aEllipse);
	IMPORT_C virtual TInt DrawPolygon(const CArrayFix<TPoint> *aPointList,TFillRule aFillRule=EAlternate);
	IMPORT_C virtual TInt DrawPolygon(const TPoint* aPointList,TInt aNumPoints,TFillRule aFillRule=EAlternate);

	IMPORT_C virtual void DrawBitmap(const TPoint &aTopLeft, const CFbsBitmap *aSource);
	IMPORT_C virtual void DrawBitmap(const TRect &aDestRect, const CFbsBitmap *aSource);
	IMPORT_C virtual void DrawBitmap(const TRect &aDestRect, const CFbsBitmap *aSource, const TRect &aSourceRect);

	IMPORT_C virtual void DrawText(const TDesC &aString,const TPoint &aPosition);
	IMPORT_C virtual void DrawText(const TDesC &aString,const TRect &aBox,TInt aBaselineOffset,TTextAlign aHoriz=ELeft,TInt aLeftMrg=0);

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
	IMPORT_C virtual void SetDitherOrigin(const TPoint& aPoint);
	IMPORT_C virtual TInt SetClippingRegion(const TRegion &aClippingRegion);
	IMPORT_C virtual void CancelClippingRegion();
	IMPORT_C void SetFaded(TBool aFaded);
	IMPORT_C void SetFadingParameters(TUint8 aBlackMap,TUint8 aWhiteMap);

private:
	CFbsBitGc& iReGc;
	const RWindowTreeNode* iRootWin;
	TPoint iOrigin;
	CWindowGc& iOldGc;
	const CWsScreenDevice* iScreen;
	};


#endif
