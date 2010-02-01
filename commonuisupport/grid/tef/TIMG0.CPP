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
// Implements the CSheetLableImg class which is used as a Grid Label
// for Grid0Step.\n
// Provides handlers to draw a row label,column label,to draw the text in the cell
// as well as calculate the side label width.\n
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code
*/

#include <e32std.h>
#include <gdi.h>
#include <grdstd.h>
#include "TIMG0.H"
#include <w32std.h>


#define KRgbGridLabelShadows	TRgb(85,85,85)
/**
  Constructor for CSheetLabelImg.\n
  Used as a Grid Label for GRID0Step.\n
*
*/
CSheetLabelImg::CSheetLabelImg(const TFontSpec& aFontSpec,MGraphicsDeviceMap* aGraphicsDeviceMap)
	: CGridLabelImg(aFontSpec,aGraphicsDeviceMap)
	{
	}
/**
  Auxiliary Function for T-Grid0Step-RunTestStepL.\n
  Function which draws the  Label for each row of the grid table.\n
*/	
void CSheetLabelImg::DrawRowLabelL(CGraphicsContext* aGc,TInt aRow,const TRect &aRect) const
	{
	TBuf<32> buf;
	buf.Num(aRow+1);
	DrawText(aGc,buf,aRect);
	}
/**
  Auxiliary Function for T-Grid0Step-RunTestStepL.\n
  Function which draws the  Label for each column of the grid table.\n
*/
void CSheetLabelImg::DrawColLabelL(CGraphicsContext* aGc,TInt aCol,const TRect &aRect) const
	{
	TBuf<32> buf;
	if (aCol>25)
		buf.Append(aCol/26+'A'-1);
	buf.Append(aCol%26+'A');
	DrawText(aGc,buf,aRect);
	}
/**
  Auxiliary Function for T-Grid0Step-RunTestStepL.\n
  Function to draw the text.\n
  Invokes the DrawText of CGraphicsContext to Draw the specified 
  text at a given position using the parameters supplied.\n
  The Pen and brush settings are configured before drawing the text.\n
*/
void CSheetLabelImg::DrawText(CGraphicsContext* aGc,const TDesC& aDes,const TRect& aRect) const
	{
//	aGc->SetPenColor(KRgbGridBackground);
	aGc->SetPenColor(iGridColors.iBackground);
	aGc->DrawLine(aRect.iTl,TPoint(aRect.iBr.iX,aRect.iTl.iY));
	aGc->DrawLine(aRect.iTl,TPoint(aRect.iTl.iX,aRect.iBr.iY));
	TRect rect=aRect;
	rect.iTl+=TPoint(1,1);
	TInt offset = rect.Height()-iFont->DescentInPixels();
//	aGc->SetPenColor(KRgbGridForeground);
	aGc->SetPenColor(iGridColors.iForeground);
	aGc->SetBrushStyle(CGraphicsContext::ESolidBrush);
	aGc->SetBrushColor(KRgbGridLabels);
	aGc->UseFont(iFont);
	aGc->DrawText(aDes,rect,offset,CGraphicsContext::ECenter);
	aGc->SetBrushStyle(CGraphicsContext::ENullBrush);
	}
/**
  Auxiliary Function for T-Grid0Step-RunTestStepL.\n
  Function that draws the top left label of the grid table.\n
  Sets the Pen colour using SetPenColor API of CGraphicsContext class.\n
  Set the x and y co-ordinates and  Invokes the DrawLine of CGraphicsContext to 
  draw a straight line between the points.\n
  Calls the static implementation of FillRect in TGridUtils to 
  fill the  rectangle with the specified colour(KRgbGridLabels).\n
*/
void CSheetLabelImg::DrawTopLeftLabelL(CGraphicsContext* aGc,const TRect& aRect) const
	{
	TRect rect=aRect;
	for (TInt ii=0;ii<2;ii++)
		{
//		aGc->SetPenColor(KRgbGridBackground);
		aGc->SetPenColor(iGridColors.iBackground);
		TPoint finish(rect.iBr.iX,rect.iTl.iY);
		aGc->DrawLine(rect.iTl,finish);
		finish.SetXY(rect.iTl.iX,rect.iBr.iY);
		aGc->DrawLine(rect.iTl,finish);
		aGc->SetPenColor(KRgbGridLabelShadows);
		TPoint start(rect.iTl.iX+1,rect.iBr.iY-1);
		finish.SetXY(rect.iBr.iX,rect.iBr.iY-1);
		aGc->DrawLine(start,finish);
		start.SetXY(rect.iBr.iX-1,rect.iBr.iY-2);
		finish.SetXY(rect.iBr.iX-1,rect.iTl.iY);
		aGc->DrawLine(start,finish);
		rect.Shrink(1,1);
		}
	TGridUtils::FillRect(aGc,KRgbGridLabels,rect);
	}
/**
  Auxiliary Function for T-Grid0Step-RunTestStepL.\n
  Draw function for the row cursor of the gridcell.\n
*/
void CSheetLabelImg::DrawRowCursorL(CGraphicsContext* aGc,const TRect& aRect) const
	{
	aGc->DrawText(_L(">"),aRect,(aRect.Height()+iFont->AscentInPixels())/2,CGraphicsContext::ERight);
	}
/**
  Auxiliary Function for T-Grid0Step-RunTestStepL.\n
  Gets the width of the side label.\n
  @return  The width of the side label in pixels.\n
*/
TInt CSheetLabelImg::SideLabelWidthInPixels(TInt aStartRow,TInt aEndRow) const
	{
	TInt maxLen=Max(Abs(aStartRow),Abs(aEndRow));
	if (maxLen<9)
		maxLen=9;	//Single digit labels must be same width as double digit labels
	TBuf<32> buf;
	buf.Num(maxLen+1);
	return (iFont->TextWidthInPixels(buf)
		+ iGraphicsDeviceMap->HorizontalTwipsToPixels(ESideLabelMarginWidthInTwips));
	}
/**
  Constructor for the SheetCellImg class.\n
*/
CSheetCellImg::CSheetCellImg()
	{
	}
/**
  Auxiliary Function for T-Grid0Step-RunTestStepL.\n
  Draw function for a particular cell in the Grid table.\n
  The function does nothing currently.\n
*/
void CSheetCellImg::DrawL(CGraphicsContext* /*aGc*/,const TCellRef& /*aCell*/,const TRect& /*aRect*/,
	const TRect& /*aClipRect*/) const
	{}
