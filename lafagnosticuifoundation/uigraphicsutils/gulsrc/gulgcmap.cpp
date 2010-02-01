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

#include <gulgcmap.h>

// GC MAPPING CLASS

/**
 * Static factory construction method.  Creates (and returns a pointer to) 
 * the object which performs as an adaptor between this <code>CWindowGc</code> 
 * derived class and an internally held <code>CBitmapGc</code>.  
 * The internal CBitmapGc is provided as <code>aFbsBitGc</code>.  
 * Ownership of the arguments is not transferred.'
 *
 * @since     7.0
 * @param     "CWsScreenDevice& aDevice"
 * @param     "CFbsBitGc& aFbsBitGc" 
 *
 * @return   "CWindowToBitmapMappingGc*"
 *             Pointer to the new Window to Bitmap Mapping Graphical Context.
 *
 */
EXPORT_C CWindowToBitmapMappingGc* CWindowToBitmapMappingGc::NewL(CWsScreenDevice& aDevice,CFbsBitGc& aFbsBitGc)
	{
	CWindowToBitmapMappingGc* self = new(ELeave) CWindowToBitmapMappingGc(aDevice,aFbsBitGc);
	return self;
	}

EXPORT_C CWindowToBitmapMappingGc::~CWindowToBitmapMappingGc()
	{
	}
	
//====================Functions from GDI.H===============================

EXPORT_C CGraphicsDevice* CWindowToBitmapMappingGc::Device() const
	{
	return (iFbsBitGc.Device());
	}

EXPORT_C void CWindowToBitmapMappingGc::Activate(RDrawableWindow& /*aWindow*/)
	{
	}

EXPORT_C void CWindowToBitmapMappingGc::Deactivate()
	{
	}

EXPORT_C void CWindowToBitmapMappingGc::SetOrigin(const TPoint &aPoint)
	{
	iFbsBitGc.SetOrigin(aPoint);
	}

EXPORT_C void CWindowToBitmapMappingGc::SetClippingRect(const TRect& aRect)
	{
	iFbsBitGc.SetClippingRect(aRect);
	}

EXPORT_C void CWindowToBitmapMappingGc::CancelClippingRect()
	{
	iFbsBitGc.CancelClippingRect();
	}

EXPORT_C TInt CWindowToBitmapMappingGc::SetClippingRegion(const TRegion &aRegion)
	{
	iFbsBitGc.SetClippingRegion(&aRegion);
	return 0;
	}

EXPORT_C void CWindowToBitmapMappingGc::CancelClippingRegion()
	{
	iFbsBitGc.CancelClippingRegion();
	}
	
EXPORT_C void CWindowToBitmapMappingGc::SetOpaque(TBool /*aDrawOpaque*/)
	{
	}

EXPORT_C void CWindowToBitmapMappingGc::SetDrawMode(TDrawMode aDrawingMode)
	{
	iFbsBitGc.SetDrawMode(aDrawingMode);
	}

EXPORT_C void CWindowToBitmapMappingGc::UseFont(const CFont *aFont)
	{
	iFbsBitGc.UseFont(aFont);
	}

EXPORT_C void CWindowToBitmapMappingGc::DiscardFont()
	{
	iFbsBitGc.DiscardFont();
	}

EXPORT_C void CWindowToBitmapMappingGc::SetUnderlineStyle(TFontUnderline aUnderlineStyle)
	{
	iFbsBitGc.SetUnderlineStyle(aUnderlineStyle);
	}

EXPORT_C void CWindowToBitmapMappingGc::SetStrikethroughStyle(TFontStrikethrough aStrikethroughStyle)
	{
	iFbsBitGc.SetStrikethroughStyle(aStrikethroughStyle);
	}

EXPORT_C void CWindowToBitmapMappingGc::SetWordJustification(TInt aExcessWidth,TInt aNumGaps)
	{
	iFbsBitGc.SetWordJustification(aExcessWidth,aNumGaps);
	}

EXPORT_C void CWindowToBitmapMappingGc::SetCharJustification(TInt aExcessWidth,TInt aNumChars)
	{
	iFbsBitGc.SetCharJustification(aExcessWidth,aNumChars);
	}

EXPORT_C void CWindowToBitmapMappingGc::SetPenColor(const TRgb &aColor)
	{
	iFbsBitGc.SetPenColor(aColor);
	}

EXPORT_C void CWindowToBitmapMappingGc::SetPenStyle(TPenStyle aPenStyle)
	{
	iFbsBitGc.SetPenStyle(aPenStyle);
	}

EXPORT_C void CWindowToBitmapMappingGc::SetPenSize(const TSize& aSize)
	{
	iFbsBitGc.SetPenSize(aSize);
	}

EXPORT_C void CWindowToBitmapMappingGc::SetBrushColor(const TRgb &aColor)
	{
	iFbsBitGc.SetBrushColor(aColor);
	}

EXPORT_C void CWindowToBitmapMappingGc::SetBrushStyle(TBrushStyle aBrushStyle)
	{
	iFbsBitGc.SetBrushStyle(aBrushStyle);
	}

EXPORT_C void CWindowToBitmapMappingGc::SetBrushOrigin(const TPoint &aOrigin)
	{
	iFbsBitGc.SetBrushOrigin(aOrigin);
	}

EXPORT_C void CWindowToBitmapMappingGc::UseBrushPattern(const CFbsBitmap *aDevice)
	{
	iFbsBitGc.UseBrushPattern(aDevice);
	}

EXPORT_C void CWindowToBitmapMappingGc::DiscardBrushPattern()
	{
	iFbsBitGc.DiscardBrushPattern();
	}

EXPORT_C void CWindowToBitmapMappingGc::Plot(const TPoint &aPoint)
	{
	iFbsBitGc.Plot(aPoint);
	}

EXPORT_C void CWindowToBitmapMappingGc::DrawLine(const TPoint &aPoint1,const TPoint &aPoint2)
	{
	iFbsBitGc.DrawLine(aPoint1,aPoint2);
	}

EXPORT_C void CWindowToBitmapMappingGc::MoveTo(const TPoint &aPoint)
	{
	iFbsBitGc.MoveTo(aPoint);
	}

EXPORT_C void CWindowToBitmapMappingGc::MoveBy(const TPoint &aPoint)
	{
	iFbsBitGc.MoveBy(aPoint);
	}

EXPORT_C void CWindowToBitmapMappingGc::DrawLineTo(const TPoint &aPoint)
	{
	iFbsBitGc.DrawLineTo(aPoint);
	}

EXPORT_C void CWindowToBitmapMappingGc::DrawLineBy(const TPoint &aPoint)
	{
	iFbsBitGc.DrawLineBy(aPoint);
	}

EXPORT_C void CWindowToBitmapMappingGc::DrawPolyLine(const TPoint* aPointList,TInt aNumPoints)
	{
	iFbsBitGc.DrawPolyLine(aPointList,aNumPoints);
	}

EXPORT_C void CWindowToBitmapMappingGc::DrawPolyLine(const CArrayFix<TPoint> *aPointArray)
	{
	iFbsBitGc.DrawPolyLine(aPointArray);
	}

EXPORT_C TInt CWindowToBitmapMappingGc::DrawPolygon(const TPoint* aPointList,TInt aNumPoints,TFillRule aFillRule)
	{
	return (iFbsBitGc.DrawPolygon(aPointList,aNumPoints,aFillRule));
	}

EXPORT_C TInt CWindowToBitmapMappingGc::DrawPolygon(const CArrayFix<TPoint> *aPointArray,TFillRule aFillRule)
	{
	return (iFbsBitGc.DrawPolygon(aPointArray,aFillRule));
	}

EXPORT_C void CWindowToBitmapMappingGc::DrawArc(const TRect &aRect,const TPoint &aStart,const TPoint &aEnd)
	{
	iFbsBitGc.DrawArc(aRect,aStart,aEnd);
	}

EXPORT_C void CWindowToBitmapMappingGc::DrawPie(const TRect &aRect,const TPoint &aStart,const TPoint &aEnd)
	{
	iFbsBitGc.DrawPie(aRect,aStart,aEnd);
	}

EXPORT_C void CWindowToBitmapMappingGc::DrawEllipse(const TRect &aRect)
	{
	iFbsBitGc.DrawEllipse(aRect);
	}

EXPORT_C void CWindowToBitmapMappingGc::DrawRect(const TRect &aRect)
	{
	iFbsBitGc.DrawRect(aRect);
	}

EXPORT_C void CWindowToBitmapMappingGc::DrawRoundRect(const TRect &aRect,const TSize &aEllipse)
	{
	iFbsBitGc.DrawRoundRect(aRect,aEllipse);
	}

EXPORT_C void CWindowToBitmapMappingGc::DrawBitmap(const TPoint &aTopLeft, const CFbsBitmap *aDevice)
	{
	iFbsBitGc.DrawBitmap(aTopLeft,aDevice);
	}

EXPORT_C void CWindowToBitmapMappingGc::DrawBitmap(const TRect &aDestRect, const CFbsBitmap *aDevice)
	{
	iFbsBitGc.DrawBitmap(aDestRect,aDevice);
	}

EXPORT_C void CWindowToBitmapMappingGc::DrawBitmap(const TRect &aDestRect, const CFbsBitmap *aDevice, const TRect &aSourceRect)
	{
	iFbsBitGc.DrawBitmap(aDestRect,aDevice,aSourceRect);
	}

EXPORT_C void CWindowToBitmapMappingGc::DrawBitmapMasked(const TRect& aDestRect, const CFbsBitmap* aBitmap, const TRect& aSourceRect, const CFbsBitmap* aMaskBitmap, TBool aInvertMask)
	{
	iFbsBitGc.DrawBitmapMasked(aDestRect, aBitmap, aSourceRect, aMaskBitmap, aInvertMask);
	}
	
EXPORT_C void CWindowToBitmapMappingGc::DrawBitmapMasked(const TRect& aDestRect, const CWsBitmap* aBitmap, const TRect& aSourceRect, const CWsBitmap* aMaskBitmap, TBool aInvertMask)
	{
	iFbsBitGc.DrawBitmapMasked(aDestRect, aBitmap, aSourceRect, aMaskBitmap, aInvertMask);
	}

EXPORT_C void CWindowToBitmapMappingGc::DrawText(const TDesC &aBuf, const TPoint &aPos)
	{
	iFbsBitGc.DrawText(aBuf,aPos);
	}

EXPORT_C void CWindowToBitmapMappingGc::DrawText(const TDesC &aBuf,const TRect &aBox,TInt aBaselineOffset,TTextAlign aHoriz,TInt aLeftMrg)
	{
	iFbsBitGc.DrawText(aBuf,aBox,aBaselineOffset,aHoriz,aLeftMrg);
	}

EXPORT_C void CWindowToBitmapMappingGc::DrawTextVertical(const TDesC& aText,const TPoint& aPos,TBool aUp)
	{
	iFbsBitGc.DrawTextVertical(aText,aPos,aUp);
	}

EXPORT_C void CWindowToBitmapMappingGc::DrawTextVertical(const TDesC& aText,const TRect& aBox,TInt aBaselineOffset,TBool aUp,TTextAlign aVert,TInt aMargin)
	{
	iFbsBitGc.DrawTextVertical(aText,aBox,aBaselineOffset,aUp,aVert,aMargin);
	}

//========================Extra functions============================

EXPORT_C void CWindowToBitmapMappingGc::CopyRect(const TPoint &anOffset,const TRect &aRect)
	{
	iFbsBitGc.CopyRect(anOffset,aRect);
	}

EXPORT_C void CWindowToBitmapMappingGc::BitBlt(const TPoint &aPoint, const CFbsBitmap *aBitmap)
	{
	iFbsBitGc.BitBlt(aPoint,aBitmap);
	}

EXPORT_C void CWindowToBitmapMappingGc::BitBlt(const TPoint &aDestination,const CFbsBitmap *aBitmap,const TRect &aSource)
	{
	iFbsBitGc.BitBlt(aDestination,aBitmap,aSource);
	}

EXPORT_C void CWindowToBitmapMappingGc::BitBltMasked(const TPoint& aPoint,const CFbsBitmap* aBitmap,const TRect& aSourceRect,const CFbsBitmap* aMaskBitmap,TBool aInvertMask)
	{
	iFbsBitGc.BitBltMasked(aPoint,aBitmap,aSourceRect,aMaskBitmap,aInvertMask);
	}

EXPORT_C void CWindowToBitmapMappingGc::BitBlt(const TPoint &aPoint, const CWsBitmap *aBitmap)
	{
	iFbsBitGc.BitBlt(aPoint,aBitmap);
	}

EXPORT_C void CWindowToBitmapMappingGc::BitBlt(const TPoint &aDestination,const CWsBitmap  *aBitmap,const TRect &aSource)
	{
	iFbsBitGc.BitBlt(aDestination,aBitmap,aSource);
	}

EXPORT_C void CWindowToBitmapMappingGc::BitBltMasked(const TPoint& aPoint,const CWsBitmap * aBitmap,const TRect& aSourceRect,const CWsBitmap * aMaskBitmap,TBool aInvertMask)
	{
	iFbsBitGc.BitBltMasked(aPoint,aBitmap,aSourceRect,aMaskBitmap,aInvertMask);
	}

EXPORT_C void CWindowToBitmapMappingGc::MapColors(const TRect &aRect,const TRgb *aColors,TInt aNumPairs,TBool aMapForwards)
	{
	iFbsBitGc.MapColors(aRect,aColors,aNumPairs,aMapForwards);
	}

EXPORT_C void CWindowToBitmapMappingGc::Clear(const TRect &aRect)
	{
	iFbsBitGc.Clear(aRect);
	}

EXPORT_C void CWindowToBitmapMappingGc::Clear()
	{
	iFbsBitGc.Clear();
	}

EXPORT_C void CWindowToBitmapMappingGc::Reset()
	{
	iFbsBitGc.Reset();
	}

EXPORT_C void CWindowToBitmapMappingGc::SetDitherOrigin(const TPoint& aPoint)
	{
	iFbsBitGc.SetDitherOrigin(aPoint);
	}

/**
 *
 * Sets whether the graphics context is faded.
 *
 * @since     7.0
 * @param     "TBool aFaded"
 *            if <code>ETrue</code>  to fade GC
 *			  if <code>EFalse</code> not to fade GC
 */
EXPORT_C void CWindowToBitmapMappingGc::SetFaded(TBool aFaded)
	{
	iFbsBitGc.SetFaded(aFaded);
	}

/**
 *
 * Sets fading parameters.
 *
 * @since     7.0
 * @param     "TUint8 aBlackMap"
 *             Black map fading parameter. 
 * @param	  "TUint8 aWhiteMap"
 *			   White map fading parameter. 			  
 */
EXPORT_C void CWindowToBitmapMappingGc::SetFadingParameters(TUint8 aBlackMap,TUint8 aWhiteMap)
	{
	iFbsBitGc.SetFadingParameters(aBlackMap,aWhiteMap);
	}
	
EXPORT_C TInt CWindowToBitmapMappingGc::AlphaBlendBitmaps(const TPoint& aDestPt, const CFbsBitmap* aSrcBmp, const TRect& aSrcRect, const CFbsBitmap* aAlphaBmp, const TPoint& aAlphaPt)
	{
	return iFbsBitGc.AlphaBlendBitmaps(aDestPt,aSrcBmp,aSrcRect,aAlphaBmp,aAlphaPt);
	}
	
EXPORT_C TInt CWindowToBitmapMappingGc::AlphaBlendBitmaps(const TPoint& aDestPt, const CWsBitmap* aSrcBmp,	const TRect& aSrcRect, const CWsBitmap* aAlphaBmp, const TPoint& aAlphaPt)
	{
	return iFbsBitGc.AlphaBlendBitmaps(aDestPt,aSrcBmp,aSrcRect,aAlphaBmp,aAlphaPt);
	}

EXPORT_C CWindowToBitmapMappingGc::CWindowToBitmapMappingGc(CWsScreenDevice& aDevice, CFbsBitGc& aFbsBitGc)
		: CWindowGc(&aDevice), iFbsBitGc(aFbsBitGc)
	{
	}
