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
// Testing of GC behaviour overrides
// This class map a CWindowGc to a CFbsBitGc class. The majority of these functions are one to one mappings, 
// with the exception  of "application specific" implementations.
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code 
*/

#include "TTransGc.h"

#define KAlphaOpaque 255

EXPORT_C CTransGc* CTransGc::NewL(CWsScreenDevice& aDevice,CFbsBitGc& aFbsBitGc)
	{
	CTransGc* self = new(ELeave) CTransGc(aDevice,aFbsBitGc);
	return self;
	}

CTransGc::~CTransGc()
	{
	}

//====================Functions from GDI.H===============================

CGraphicsDevice* CTransGc::Device() const
	{
	return (iFbsBitGc.Device());
	}


void CTransGc::SetOrigin(const TPoint &aPoint)
	{
	iFbsBitGc.SetOrigin(aPoint);
	}

void CTransGc::SetClippingRect(const TRect& aRect)
	{
	iFbsBitGc.SetClippingRect(aRect);
	}

void CTransGc::CancelClippingRect()
	{
	iFbsBitGc.CancelClippingRect();
	}

TInt CTransGc::SetClippingRegion(const TRegion &aRegion)
	{
	iFbsBitGc.SetClippingRegion(&aRegion);
	return 0;
	}

void CTransGc::CancelClippingRegion()
	{
	iFbsBitGc.CancelClippingRegion();
	}

void CTransGc::SetDrawMode(TDrawMode aDrawingMode)
	{
	iFbsBitGc.SetDrawMode(aDrawingMode);
	}

void CTransGc::UseFont(const CFont *aFont)
	{
	iFbsBitGc.UseFont(aFont);
	}

void CTransGc::DiscardFont()
	{
	iFbsBitGc.DiscardFont();
	}

void CTransGc::SetUnderlineStyle(TFontUnderline aUnderlineStyle)
	{
	iFbsBitGc.SetUnderlineStyle(aUnderlineStyle);
	}

void CTransGc::SetStrikethroughStyle(TFontStrikethrough aStrikethroughStyle)
	{
	iFbsBitGc.SetStrikethroughStyle(aStrikethroughStyle);
	}

void CTransGc::SetWordJustification(TInt aExcessWidth,TInt aNumGaps)
	{
	iFbsBitGc.SetWordJustification(aExcessWidth,aNumGaps);
	}

void CTransGc::SetCharJustification(TInt aExcessWidth,TInt aNumChars)
	{
	iFbsBitGc.SetCharJustification(aExcessWidth,aNumChars);
	}


void CTransGc::SetPenStyle(TPenStyle aPenStyle)
	{
	iFbsBitGc.SetPenStyle(aPenStyle);
	}

void CTransGc::SetPenSize(const TSize& aSize)
	{
	iFbsBitGc.SetPenSize(aSize);
	}


void CTransGc::SetBrushStyle(TBrushStyle aBrushStyle)
	{
	iFbsBitGc.SetBrushStyle(aBrushStyle);
	}

void CTransGc::SetBrushOrigin(const TPoint &aOrigin)
	{
	iFbsBitGc.SetBrushOrigin(aOrigin);
	}

void CTransGc::UseBrushPattern(const CFbsBitmap *aDevice)
	{
	iFbsBitGc.UseBrushPattern(aDevice);
	}

void CTransGc::DiscardBrushPattern()
	{
	iFbsBitGc.DiscardBrushPattern();
	}

void CTransGc::Plot(const TPoint &aPoint)
	{
	iFbsBitGc.Plot(aPoint);
	}

void CTransGc::DrawLine(const TPoint &aPoint1,const TPoint &aPoint2)
	{
	iFbsBitGc.DrawLine(aPoint1,aPoint2);
	}

void CTransGc::MoveTo(const TPoint &aPoint)
	{
	iFbsBitGc.MoveTo(aPoint);
	}

void CTransGc::MoveBy(const TPoint &aPoint)
	{
	iFbsBitGc.MoveBy(aPoint);
	}

void CTransGc::DrawLineTo(const TPoint &aPoint)
	{
	iFbsBitGc.DrawLineTo(aPoint);
	}

void CTransGc::DrawLineBy(const TPoint &aPoint)
	{
	iFbsBitGc.DrawLineBy(aPoint);
	}

void CTransGc::DrawPolyLine(const TPoint* aPointList,TInt aNumPoints)
	{
	iFbsBitGc.DrawPolyLine(aPointList,aNumPoints);
	}

void CTransGc::DrawPolyLine(const CArrayFix<TPoint> *aPointArray)
	{
	iFbsBitGc.DrawPolyLine(aPointArray);
	}

TInt CTransGc::DrawPolygon(const TPoint* aPointList,TInt aNumPoints,TFillRule aFillRule)
	{
	return (iFbsBitGc.DrawPolygon(aPointList,aNumPoints,aFillRule));
	}

TInt CTransGc::DrawPolygon(const CArrayFix<TPoint> *aPointArray,TFillRule aFillRule)
	{
	return (iFbsBitGc.DrawPolygon(aPointArray,aFillRule));
	}

void CTransGc::DrawArc(const TRect &aRect,const TPoint &aStart,const TPoint &aEnd)
	{
	iFbsBitGc.DrawArc(aRect,aStart,aEnd);
	}

void CTransGc::DrawPie(const TRect &aRect,const TPoint &aStart,const TPoint &aEnd)
	{
	iFbsBitGc.DrawPie(aRect,aStart,aEnd);
	}

void CTransGc::DrawEllipse(const TRect &aRect)
	{
	iFbsBitGc.DrawEllipse(aRect);
	}

void CTransGc::DrawRect(const TRect &aRect)
	{
	iFbsBitGc.DrawRect(aRect);
	}

void CTransGc::DrawRoundRect(const TRect &aRect,const TSize &aEllipse)
	{
	iFbsBitGc.DrawRoundRect(aRect,aEllipse);
	}

void CTransGc::DrawBitmap(const TPoint &aTopLeft, const CFbsBitmap *aDevice)
	{
	iFbsBitGc.DrawBitmap(aTopLeft,aDevice);
	}

void CTransGc::DrawBitmap(const TRect &aDestRect, const CFbsBitmap *aDevice)
	{
	iFbsBitGc.DrawBitmap(aDestRect,aDevice);
	}

void CTransGc::DrawBitmap(const TRect &aDestRect, const CFbsBitmap *aDevice, const TRect &aSourceRect)
	{
	iFbsBitGc.DrawBitmap(aDestRect,aDevice,aSourceRect);
	}

void CTransGc::DrawText(const TDesC &aBuf, const TPoint &aPos)
	{
	iFbsBitGc.DrawText(aBuf,aPos);
	}

void CTransGc::DrawText(const TDesC &aBuf,const TRect &aBox,TInt aBaselineOffset,TTextAlign aHoriz,TInt aLeftMrg)
	{
	iFbsBitGc.DrawText(aBuf,aBox,aBaselineOffset,aHoriz,aLeftMrg);
	}

void CTransGc::DrawTextVertical(const TDesC& aText,const TPoint& aPos,TBool aUp)
	{
	iFbsBitGc.DrawTextVertical(aText,aPos,aUp);
	}

void CTransGc::DrawTextVertical(const TDesC& aText,const TRect& aBox,TInt aBaselineOffset,TBool aUp,TTextAlign aVert,TInt aMargin)
	{
	iFbsBitGc.DrawTextVertical(aText,aBox,aBaselineOffset,aUp,aVert,aMargin);
	}

//========================Extra functions============================

void CTransGc::CopyRect(const TPoint &anOffset,const TRect &aRect)
	{
	iFbsBitGc.CopyRect(anOffset,aRect);
	}

void CTransGc::BitBlt(const TPoint &aPoint, const CFbsBitmap *aBitmap)
	{
	iFbsBitGc.BitBlt(aPoint,aBitmap);
	}

void CTransGc::BitBlt(const TPoint &aDestination,const CFbsBitmap *aBitmap,const TRect &aSource)
	{
	iFbsBitGc.BitBlt(aDestination,aBitmap,aSource);
	}

void CTransGc::BitBltMasked(const TPoint& aPoint,const CFbsBitmap* aBitmap,const TRect& aSourceRect,const CFbsBitmap* aMaskBitmap,TBool aInvertMask)
	{
	iFbsBitGc.BitBltMasked(aPoint,aBitmap,aSourceRect,aMaskBitmap,aInvertMask);
	}

void CTransGc::BitBlt(const TPoint &aPoint, const CWsBitmap *aBitmap)
	{
	iFbsBitGc.BitBlt(aPoint,aBitmap);
	}

void CTransGc::BitBlt(const TPoint &aDestination,const CWsBitmap  *aBitmap,const TRect &aSource)
	{
	iFbsBitGc.BitBlt(aDestination,aBitmap,aSource);
	}

void CTransGc::BitBltMasked(const TPoint& aPoint,const CWsBitmap * aBitmap,const TRect& aSourceRect,const CWsBitmap * aMaskBitmap,TBool aInvertMask)
	{
	iFbsBitGc.BitBltMasked(aPoint,aBitmap,aSourceRect,aMaskBitmap,aInvertMask);
	}

void CTransGc::MapColors(const TRect &aRect,const TRgb *aColors,TInt aNumPairs,TBool aMapForwards)
	{
	iFbsBitGc.MapColors(aRect,aColors,aNumPairs,aMapForwards);
	}

void CTransGc::Clear(const TRect &aRect)
	{
	iFbsBitGc.Clear(aRect);
	}

void CTransGc::Clear()
	{
	iFbsBitGc.Clear();
	}

void CTransGc::SetDitherOrigin(const TPoint& aPoint)
	{
	iFbsBitGc.SetDitherOrigin(aPoint);
	}


void CTransGc::SetFaded(TBool aFaded)
	{
	iFbsBitGc.SetFaded(aFaded);
	}

void CTransGc::SetFadingParameters(TUint8 aBlackMap,TUint8 aWhiteMap)
	{
	iFbsBitGc.SetFadingParameters(aBlackMap,aWhiteMap);
	}


/** Application specific */

CTransGc::CTransGc(CWsScreenDevice& aDevice, CFbsBitGc& aFbsBitGc)
		: CWindowGc(&aDevice), iFbsBitGc(aFbsBitGc)
	{
		//Default alpha value is opaque
		iAlpha = KAlphaOpaque; 
	}

void CTransGc::SetWindowOrigin(TPoint aOrigin)
{
	//The window origin is reference offset so that multiple windows can composite into an offscreen Gc 
	iWindowOrigin = aOrigin;
}

//The Gc activate function ensures the correct window refreshing (clearing) and relative placement of origin for offscreen
//bitmap images.
void CTransGc::Activate(RDrawableWindow& aWindow)
	{				
		CancelClippingRect();
								
		//Alpha clear the redraw rect;
		iFbsBitGc.SetBrushColor(TRgb(0,0,0,0)); //Alpha transparent 			
		SetDrawMode(CGraphicsContext::EDrawModeWriteAlpha);	
		
		//The new Gc Origin is the current window position relative to our main iWindowOrigin
		TPoint p = aWindow.AbsPosition();	
		p -= iWindowOrigin;
		iGcOrigin = p;
		
		//ensure the drawing functions to draw to the correct origin
		iFbsBitGc.SetOrigin(p);

		//Only clear this Gc if a new window (and hence different rect) is applied 
		if (iWin!=&aWindow)		
			{
			//Save the window 
			iWin = &aWindow;
			TRect rect;
			//Get the redraw rectangle
			rect = aWindow.GetDrawRect();		
			//Clear the drawing region
			Clear(rect); 

			}			
		
		SetDrawMode(CGraphicsContext::EDrawModePEN);		
	}

void CTransGc::Reset()
	{	
		iFbsBitGc.Reset();
		
		//Make sure the current origin is maintained.
		iFbsBitGc.SetOrigin(iGcOrigin);
	}

void CTransGc::Deactivate()
	{	
		CancelClippingRect();
	}

//Set the current alpha level component
void CTransGc::SetAlphaLevel(TInt aAlpha)
	{
	iAlpha = aAlpha;
	}

//Ensure the pen colour is set in the bitmap with the correct alpha blending level
void CTransGc::SetPenColor(const TRgb &aColor)
	{
	TRgb Color = aColor;
	Color.SetAlpha(iAlpha);
	iFbsBitGc.SetPenColor(Color);
	
	}
//Ensure the brush colour is set in the bitmap with the correct alpha blending level
void CTransGc::SetBrushColor(const TRgb &aColor)
	{
	TRgb Color = aColor;
	Color.SetAlpha(iAlpha);
	iFbsBitGc.SetBrushColor(Color);
	}
