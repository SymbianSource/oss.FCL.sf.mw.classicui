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
// Implements the CTestLableImg class which is used as a Grid Label
// for Grid0Step. Provides handlers to draw labels.\n
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code
*/

#include <coedef.h>
#include "TESTIMG.H"


#define KRgbGridLabels	KRgbDitheredLightGray
/**
  Two argument Constructor with font specification and an Interface class for mapping between twips 
  and device-specific units (pixels) as arguments.\n 
*/
CTestLabelImg::CTestLabelImg(const TFontSpec& aFontSpec,MGraphicsDeviceMap* aGraphicsDeviceMap)
	: CGridLabelImg(aFontSpec,aGraphicsDeviceMap)
	{
	}
/**
  Auxiliary Function for T-CoGridStep-RunTestStepL.\n
  Function which draws the  Label for each row of the grid table.\n
*/	
void CTestLabelImg::DrawRowLabelL(CGraphicsContext *aGc,TInt aRow,const TRect &aRect) const
	{
	TRect rect=aRect;
	aGc->SetPenColor(iGridColors.iLines);
	--rect.iBr.iY;
	aGc->DrawLine(TPoint(rect.iTl.iX,rect.iBr.iY),rect.iBr);
	rect.iBr.iX-=ERowCursorDiameterInPixels;
	TInt offset = rect.Height()-iFont->DescentInPixels();
	TBuf<32> buf;
	buf.Num(aRow+1);
	aGc->UseFont(iFont);
	aGc->SetPenColor(iGridColors.iForeground);
	aGc->SetBrushStyle(CGraphicsContext::ESolidBrush);
	aGc->SetBrushColor(iGridColors.iBackground);
	aGc->DrawText(buf,rect,offset,CGraphicsContext::ECenter);
	rect.iTl.iX=rect.iBr.iX;
	rect.iBr.iX+=ERowCursorDiameterInPixels;
	TGridUtils::FillRect(aGc, iGridColors.iBackground, rect);
	}
/**
  Auxiliary Function for T-CoGridStep-RunTestStepL.\n
  Function which draws the  Label for each column of the grid table.\n
*/	
void CTestLabelImg::DrawColLabelL(CGraphicsContext *aGc,TInt aCol,const TRect &aRect) const
	{
	TRect rect=aRect;
	aGc->SetPenColor(KRgbDarkGray);
	--rect.iBr.iY;
	TPoint point(rect.iTl.iX,rect.iBr.iY);
	aGc->DrawLine(point,rect.iBr);
	--rect.iBr.iY;
	--point.iY;
	aGc->DrawLine(point,rect.iBr);
	TBuf<32> buf;
	if (aCol>25)
		buf.Append(aCol/26+'A'-1);
	buf.Append(aCol%26+'A');
	aGc->UseFont(iFont);
	aGc->SetPenColor(iGridColors.iForeground);
	aGc->SetBrushStyle(CGraphicsContext::ESolidBrush);
	aGc->SetBrushColor(iGridColors.iBackground);
	aGc->DrawText(buf,rect,rect.Height()-iFont->DescentInPixels(),CGraphicsContext::ELeft);
	aGc->SetBrushStyle(CGraphicsContext::ENullBrush);
	}
/**
  Auxiliary Function for T-CoGridStep-RunTestStepL.\n
  Gets the width of the side label.\n
  @return  The width of the side label in pixels.\n
  
*/
TInt CTestLabelImg::SideLabelWidthInPixels(TInt aStartRow,TInt aEndRow) const
	{
	TInt maxLen=Max(Abs(aStartRow),Abs(aEndRow));
	if (maxLen<9)
		maxLen=9;	//Single digit labels must be same width as double digit labels
	TBuf<32> buf;
	buf.Num(maxLen+1);
	return (iFont->TextWidthInPixels(buf) + ERowCursorDiameterInPixels
		+ iGraphicsDeviceMap->HorizontalTwipsToPixels(ESideLabelMarginWidthInTwips));
	}
/**
  Auxiliary Function for T-CoGridStep-RunTestStepL.\n
  Draw function for the row cursor of the gridcell.\n
*/
void CTestLabelImg::DrawRowCursorL(CGraphicsContext* aGc,const TRect& aRect) const
	{
	TRect rect=aRect;
	rect.iTl.iX=rect.iBr.iX-ERowCursorDiameterInPixels-1;
	TInt midY=rect.iTl.iY+rect.Height()/2;
	rect.iTl.iY=midY-ERowCursorDiameterInPixels/2;
	rect.iBr.iY=midY+ERowCursorDiameterInPixels/2;
	aGc->SetBrushStyle(CGraphicsContext::ESolidBrush);
	aGc->SetBrushColor(iGridColors.iForeground);
	aGc->DrawEllipse(rect);
	aGc->SetBrushStyle(CGraphicsContext::ENullBrush);
	aGc->SetBrushColor(iGridColors.iBackground);
	}
/**
  Auxiliary Function for T-CoGridStep-RunTestStepL.\n
  Function that draws the top left label of the grid table.\n
*/
void CTestLabelImg::DrawTopLeftLabelL(CGraphicsContext* aGc,const TRect& aRect) const
	{
	TRect rect=aRect;
	aGc->SetPenColor(KRgbDarkGray);
	--rect.iBr.iY;
	TPoint point(rect.iTl.iX,rect.iBr.iY);
	aGc->DrawLine(point,rect.iBr);
	--rect.iBr.iY;
	--point.iY;
	aGc->DrawLine(point,rect.iBr);
	TGridUtils::FillRect(aGc,iGridColors.iBackground,rect);
	}


/**
  Constructor for the grid cell.\n
  Initializes the font for a grid cell.\n
  Initializes the iData array with some test data.\n
  The data will be returned by invoking GetL function.
  The GetL function is used to get the data in a grid cell.\n
*/
CTestCellImg::CTestCellImg(const CFont *aFont)
	: iFont(aFont)
	{
	iData[0].iPos=TCellRef(2,2);
	iData[0].iBuf=_L("Some");
	iData[1].iPos=TCellRef(2,4);
	iData[1].iBuf=_L("Hard");
	iData[2].iPos=TCellRef(3,3);
	iData[2].iBuf=_L("Coded");
	iData[3].iPos=TCellRef(4,2);
	iData[3].iBuf=_L("Test");
	iData[4].iPos=TCellRef(4,4);
	iData[4].iBuf=_L("Data");
	}
/**
  Auxiliary Function for T-CoGridStep-RunTestStepL.\n
  Draw function for the grid cell and the data contained in the cell.\n
  Calculates the effective rectange and sets the brush style and colour.\n
  Redraws the text in the grid cell .\n
*/
void CTestCellImg::DrawL(CGraphicsContext* aGc,const TCellRef& aCell,const TRect& aRect,const TRect& aClipRect) const
	{
	TInt offset = aRect.Height()-iFont->DescentInPixels();
	TRect effectiveRect=aRect;
	effectiveRect.iTl.iX-=BurstLeft();
	effectiveRect.iBr.iX+=BurstRight();
	aGc->UseFont(iFont);
	aGc->SetPenColor(iGridColors.iForeground);
	TRect realClipRect=aRect;
	realClipRect.Grow(1,1);
	realClipRect.Intersection(effectiveRect);
	realClipRect.Intersection(aClipRect);
	aGc->SetClippingRect(realClipRect);
	aGc->SetBrushStyle(CGraphicsContext::ESolidBrush);
	aGc->SetBrushColor(iGridColors.iBackground);
	const TDesC* des=GetL(aCell.iRow,aCell.iCol-BurstColOffset());
	if (des)
		aGc->DrawText(*des,effectiveRect,offset,CGraphicsContext::ELeft);
	else
		{
		aGc->SetPenStyle(CGraphicsContext::ENullPen);
		aGc->DrawRect(effectiveRect);
		}
	aGc->CancelClippingRect();
	aGc->Reset();
	}
/**
  Auxiliary Function for T-CoGridStep-RunTestStepL.\n
  @return Width of the text in pixels contained in the grid cell.\n
*/
TInt CTestCellImg::DataWidthInPixelsL(const TCellRef& aCell) const
	{
	const TDesC* des=GetL(aCell.iRow,aCell.iCol);
	if (des!=NULL)
		return iFont->TextWidthInPixels(*des);
	return 0;
	}
/**
  Auxiliary Function for T-CoGridStep-RunTestStepL.\n
  @return Boolean,True if the grid cell contains data else False.\n

*/
TBool CTestCellImg::DoesCellContainDataL(const TCellRef& aCell) const
	{
	const TDesC* des=GetL(aCell.iRow,aCell.iCol);
	return des!=NULL;
	}
/**
  Auxiliary Function for T-CoGridStep-RunTestStepL.\n
  @return Returns the data contained in the grid cell identified by the row and column arguments.\n
*/
const TDesC* CTestCellImg::GetL(TInt aRow,TInt aCol) const
//
// Horrible array access function but OK for low ENumberOfItems
	{
	for (TInt ii=0;ii<ENumberOfItems;ii++)
		{
		if (iData[ii].iPos.iRow==aRow && iData[ii].iPos.iCol==aCol)
			return &iData[ii].iBuf;
		}
	return NULL;
	}


/**
  Constructor for a Test Grid Table.\n
  Initializes the member variable indicating zero rows as False.\n
*/
CTestGridTable::CTestGridTable()
	: iZeroRows(EFalse)
	{
	}
/**
  Auxiliary Function for T-CoGridStep-RunTestStepL.\n
  @return Boolean,True if rows are non Zero.\n
*/

TBool CTestGridTable::RequestRow(TInt aRow,TInt& aReturnRow) const
// Test function for grids with indefinite row boundaries
	{
	if (aRow>49)
		aReturnRow=49;
	else if (aRow<-21)
		aReturnRow=-21;
	else
		aReturnRow=aRow;
	return !iZeroRows;
	}
