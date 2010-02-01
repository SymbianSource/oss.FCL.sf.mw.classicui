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
* Description:  Anim Gc
*
*/

// AknAnimGc.CPP
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Animation View Redirection GC


#include "aknAnimGc.h"


CAknAnimatedGc* CAknAnimatedGc::NewL(CWindowGc& aOldGc, CFbsBitGc& aReGc)
	{
	CWsScreenDevice* screen = new(ELeave)CWsScreenDevice();
	CleanupStack::PushL(screen);
	CAknAnimatedGc* self = new(ELeave)CAknAnimatedGc(*screen, aReGc, aOldGc);
	self->SetScreenDevice(screen);
	CleanupStack::Pop();
	return self;
	}

CAknAnimatedGc::CAknAnimatedGc(CWsScreenDevice& aScreen, CFbsBitGc& aReGc, CWindowGc& aOldGc)
:CWindowGc(&aScreen), iReGc(aReGc), iOldGc(aOldGc)
	{
	}


CAknAnimatedGc::~CAknAnimatedGc()
	{	
	// Delete the CWsScreenDevice used by this object
	delete iScreen;
	}

void CAknAnimatedGc::SetRootWindow(const RWindowTreeNode& aRootWin)
	{
	iRootWin = &aRootWin;
	}

EXPORT_C void CAknAnimatedGc::Activate(RDrawableWindow& aWindow)
	{
	TPoint pos = aWindow.InquireOffset(*iRootWin);
	iOrigin = pos;
	}

EXPORT_C void CAknAnimatedGc::Deactivate()
	{
	}

EXPORT_C void CAknAnimatedGc::Reset()
	{
	iReGc.Reset();
	}

EXPORT_C CGraphicsDevice* CAknAnimatedGc::Device() const
	{
	return iReGc.Device();
	}


EXPORT_C void CAknAnimatedGc::SetOrigin(const TPoint &aPos)
	{
	iReGc.SetOrigin(aPos);
	}

EXPORT_C void CAknAnimatedGc::SetDrawMode(TDrawMode aDrawingMode)
	{
	iReGc.SetDrawMode(aDrawingMode);
	}

EXPORT_C void CAknAnimatedGc::SetClippingRect(const TRect& aRect)
	{
	TRect rect(aRect);
	rect.Move(iOrigin);
	iReGc.SetClippingRect(rect);
	}

EXPORT_C void CAknAnimatedGc::CancelClippingRect()
	{
	iReGc.CancelClippingRect();
	}

EXPORT_C void CAknAnimatedGc::SetWordJustification(TInt aExcessWidth,TInt aNumGaps)
	{
	iReGc.SetWordJustification(aExcessWidth, aNumGaps);
	}

EXPORT_C void CAknAnimatedGc::SetCharJustification(TInt aExcessWidth,TInt aNumChars)
	{
	iReGc.SetCharJustification(aExcessWidth, aNumChars);
	}


EXPORT_C void CAknAnimatedGc::DrawText(const TDesC &aString,const TPoint &aPosition)
	{
	iReGc.DrawText(aString, aPosition+iOrigin);
	}

EXPORT_C void CAknAnimatedGc::DrawText(const TDesC &aString,const TRect &aBox,TInt aBaselineOffset,TTextAlign aHoriz,TInt aLeftMrg)
	{
	TRect box(aBox);
	box.Move(iOrigin);
	iReGc.DrawText(aString, box, aBaselineOffset, aHoriz, aLeftMrg);
	}


EXPORT_C void CAknAnimatedGc::Clear()
	{
	iReGc.Clear();
	}

EXPORT_C void CAknAnimatedGc::Clear(const TRect &aRect)
	{
	TRect rect(aRect);
	rect.Move(iOrigin);
	iReGc.Clear(rect);
	}

EXPORT_C void CAknAnimatedGc::SetBrushColor(const TRgb &aColor)
	{
	iReGc.SetBrushColor(aColor);
	}

EXPORT_C void CAknAnimatedGc::SetBrushStyle(TBrushStyle aBrushStyle)
	{
	iReGc.SetBrushStyle(aBrushStyle);
	}


EXPORT_C void CAknAnimatedGc::SetBrushOrigin(const TPoint &aOrigin)
	{
	iReGc.SetBrushOrigin(aOrigin);
	}

EXPORT_C void CAknAnimatedGc::UseBrushPattern(const CFbsBitmap *aBitmap)
	{
	iReGc.UseBrushPattern(aBitmap);
	}

EXPORT_C void CAknAnimatedGc::DiscardBrushPattern()
	{
	iReGc.DiscardBrushPattern();
	}


EXPORT_C void CAknAnimatedGc::SetPenColor(const TRgb &aColor)
	{
	iReGc.SetPenColor(aColor);
	}

EXPORT_C void CAknAnimatedGc::SetPenStyle(TPenStyle aPenStyle)
	{
	iReGc.SetPenStyle(aPenStyle);
	}

EXPORT_C void CAknAnimatedGc::SetPenSize(const TSize& aSize)
	{
	iReGc.SetPenSize(aSize);
	}


EXPORT_C void CAknAnimatedGc::SetStrikethroughStyle(TFontStrikethrough aStrikethroughStyle)
	{
	iReGc.SetStrikethroughStyle(aStrikethroughStyle);
	}

EXPORT_C void CAknAnimatedGc::SetUnderlineStyle(TFontUnderline aUnderlineStyle)
	{
	iReGc.SetUnderlineStyle(aUnderlineStyle);
	}

EXPORT_C void CAknAnimatedGc::UseFont(const CFont *aFont)
	{
	iReGc.UseFont(aFont);
	}

EXPORT_C void CAknAnimatedGc::DiscardFont()
	{
	iReGc.DiscardFont();
	}



EXPORT_C void CAknAnimatedGc::MoveTo(const TPoint &aPoint)
	{
	TPoint point = iOrigin + aPoint;
	iReGc.MoveTo(point);
	}

EXPORT_C void CAknAnimatedGc::MoveBy(const TPoint &aVector)
	{
	iReGc.MoveBy(aVector);
	}

EXPORT_C void CAknAnimatedGc::Plot(const TPoint &aPoint)
	{
	TPoint point = iOrigin + aPoint;
	iReGc.Plot(point);
	}

EXPORT_C void CAknAnimatedGc::DrawArc(const TRect &aRect,const TPoint &aStart,const TPoint &aEnd)
	{
	TRect rect = aRect;
	rect.Move(iOrigin);
	iReGc.DrawArc(rect, aStart+iOrigin, aEnd+iOrigin);
	}

EXPORT_C void CAknAnimatedGc::DrawLine(const TPoint &aPoint1,const TPoint &aPoint2)
	{
	iReGc.DrawLine(aPoint1+iOrigin, aPoint2+iOrigin);
	}


EXPORT_C void CAknAnimatedGc::DrawLineTo(const TPoint &aPoint)
	{
	iReGc.DrawLineTo(aPoint+iOrigin);
	}

EXPORT_C void CAknAnimatedGc::DrawLineBy(const TPoint &aVector)
	{
	iReGc.DrawLineBy(aVector);
	}

EXPORT_C void CAknAnimatedGc::DrawPolyLine(const CArrayFix<TPoint> *aPointList)
	{
	iReGc.DrawPolyLine(aPointList);
	}

EXPORT_C void CAknAnimatedGc::DrawPolyLine(const TPoint* aPointList,TInt aNumPoints)
	{
	iReGc.DrawPolyLine(aPointList, aNumPoints);
	}


EXPORT_C void CAknAnimatedGc::DrawPie(const TRect &aRect,const TPoint &aStart,const TPoint &aEnd)
	{
	TRect rect = aRect;
	rect.Move(iOrigin);
	iReGc.DrawPie(rect, aStart+iOrigin, aEnd+iOrigin);
	}

EXPORT_C void CAknAnimatedGc::DrawEllipse(const TRect &aRect)
	{
	TRect rect = aRect;
	rect.Move(iOrigin);
	iReGc.DrawEllipse(rect);
	}

EXPORT_C void CAknAnimatedGc::DrawRect(const TRect &aRect)
	{
	TRect rect(aRect);
	rect.Move(iOrigin);
	iReGc.DrawRect(rect);
	}
	
EXPORT_C void CAknAnimatedGc::DrawRoundRect(const TRect &aRect,const TSize &aEllipse)
	{
	TRect rect(aRect);
	rect.Move(iOrigin);
	iReGc.DrawRoundRect(rect, aEllipse);
	}

EXPORT_C TInt CAknAnimatedGc::DrawPolygon(const CArrayFix<TPoint> *aPointList,TFillRule aFillRule)
	{
	return iReGc.DrawPolygon(aPointList,aFillRule);
	}

EXPORT_C TInt CAknAnimatedGc::DrawPolygon(const TPoint* aPointList,TInt aNumPoints,TFillRule aFillRule)
	{
	return iReGc.DrawPolygon(aPointList, aNumPoints, aFillRule);
	}



EXPORT_C void CAknAnimatedGc::DrawBitmap(const TPoint &aTopLeft, const CFbsBitmap *aSource)
	{
	iReGc.DrawBitmap(iOrigin + aTopLeft, aSource);
	}

EXPORT_C void CAknAnimatedGc::DrawBitmap(const TRect &aDestRect, const CFbsBitmap *aSource)
	{
	TRect rect(aDestRect);
	rect.Move(iOrigin);
	iReGc.DrawBitmap(rect, aSource);
	}

EXPORT_C void CAknAnimatedGc::DrawBitmap(const TRect &aDestRect, const CFbsBitmap *aSource, const TRect &aSourceRect)
	{
	TRect rect(aDestRect);
	rect.Move(iOrigin);
	iReGc.DrawBitmap(rect, aSource, aSourceRect);
	}



EXPORT_C void CAknAnimatedGc::CopyRect(const TPoint &aOffset,const TRect &aRect)
	{
	TRect rect(aRect);
	rect.Move(iOrigin);
	iReGc.CopyRect(aOffset + iOrigin, rect);
	}

EXPORT_C void CAknAnimatedGc::MapColors(const TRect& aRect,const TRgb* aColors,TInt aNumPairs,TBool aMapForwards)
	{
	TRect rect(aRect);
	rect.Move(iOrigin);
	iReGc.MapColors(rect, aColors, aNumPairs, aMapForwards);
	}





EXPORT_C void CAknAnimatedGc::BitBlt(const TPoint &aPos, const CFbsBitmap *aDevice)
	{
	iReGc.BitBlt(aPos+iOrigin, aDevice);
	}

EXPORT_C void CAknAnimatedGc::BitBlt(const TPoint &aPos, const CFbsBitmap *aDevice, const TRect &aRect)
	{
	iReGc.BitBlt(aPos+iOrigin, aDevice, aRect);
	}

EXPORT_C void CAknAnimatedGc::BitBltMasked(const TPoint& aPoint,const CFbsBitmap* aBitmap,const TRect& aSourceRect,const CFbsBitmap* aMaskBitmap,TBool aInvertMask)
	{
	iReGc.BitBltMasked(aPoint+iOrigin, aBitmap, aSourceRect, aMaskBitmap, aInvertMask);
	}

EXPORT_C void CAknAnimatedGc::BitBlt(const TPoint &aPos, const CWsBitmap *aDevice)
	{
	iReGc.BitBlt(aPos+iOrigin, aDevice);
	}

EXPORT_C void CAknAnimatedGc::BitBlt(const TPoint &aPos, const CWsBitmap *aDevice, const TRect &aRect)
	{
	iReGc.BitBlt(aPos+iOrigin, aDevice, aRect);
	}

EXPORT_C void CAknAnimatedGc::BitBltMasked(const TPoint& aPoint,const CWsBitmap *aBitmap,const TRect& aSourceRect,const CWsBitmap *aMaskBitmap,TBool aInvertMask)
	{
	iReGc.BitBltMasked(aPoint+iOrigin, aBitmap, aSourceRect, aMaskBitmap, aInvertMask);
	}


EXPORT_C void CAknAnimatedGc::DrawTextVertical(const TDesC& aText,const TPoint& aPosition,TBool aUp)
	{
	iReGc.DrawTextVertical(aText, aPosition + iOrigin, aUp);
	}

EXPORT_C void CAknAnimatedGc::DrawTextVertical(const TDesC& aText,const TRect& aBox,TInt aBaselineOffset,TBool aUp,TTextAlign aVert,TInt aMargin)
	{
	TRect box(aBox);
	box.Move(iOrigin);
	iReGc.DrawTextVertical(aText, box, aBaselineOffset, aUp, aVert, aMargin);
	}

EXPORT_C void CAknAnimatedGc::SetDitherOrigin(const TPoint& aPoint)
	{
	iReGc.SetDitherOrigin(aPoint + iOrigin);
	}

EXPORT_C TInt CAknAnimatedGc::SetClippingRegion(const TRegion &aClippingRegion)
	{
	RRegion region;
	region.Copy(aClippingRegion);
	region.Offset(iOrigin);
	iReGc.SetClippingRegion(&region);
	return KErrNone;
	}

EXPORT_C void CAknAnimatedGc::CancelClippingRegion()
	{
	iReGc.CancelClippingRegion();
	}

EXPORT_C void CAknAnimatedGc::SetFaded(TBool /*aFaded*/)
	{
	}

EXPORT_C void CAknAnimatedGc::SetFadingParameters(TUint8 aBlackMap,TUint8 aWhiteMap)
	{
	iReGc.SetFadingParameters(aBlackMap, aWhiteMap);
	}

void CAknAnimatedGc::SetScreenDevice(const CWsScreenDevice* aScreen)
	{
	iScreen = aScreen;
	}

// End of File
