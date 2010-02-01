// Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
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
// The member variables of the class CGridImg are as follows:-
// iGridRect - the coordinates of the rectangle containing the grid.
// iTitlePoint - The point at the top left of the grid not including the labels
// iMainPoint - The point at which the visible range starts (usually == iTitlePoint)
// iCursorPos - the cell reference of the current cursor position.
// iNewCursorPos - the proposed cell reference of the position that
// the cursor would occupy after a keypress.
// iAnchorPos - the cell reference of the position that the cursor must
// return to after a series of selected movements have been made.
// iGcPtr - a pointer to the current graphics context.
// iGc - the internal grid image Gc
// *iWin - a pointer to the current active window.
// *iGridLay, *iGridCellImg, *iGridLabelImg - allow access to the data in these
// other classes.
// *iSelected - allows access to the class that stores the array of selected ranges
// *iCursorMoveCallBack - a pointer to call back to an app after a cursor move
// iDragLabel - store the index of the label currently being dragged
// iCurrentDragPos - Stores the position of the label prior to it being dragged
// iDragDiff - Stores the distance between the second drag label and the pointer while a label drag is in progress
// iDragDim - Simply stores the dimension in which a label drag is in (X,Y or none)
// iDragBmp - Stores the bitmap of the dragged labels during a drag.
// iXRefPoint,iYRefPoint - Remembers which part of the grid the last pointer event was in. This is used in the
// SetCursorWithPointer() function logic.
// 
//

#include "GRDSTD.H"
#include "GRDPANIC.H"

#if !defined(__WINC__)
#include <w32std.h>
#endif

const TInt KArrowLength = 11;
const TInt KArrowBreadth = 11;
const TInt KArrowSeparation = 11;

GLDEF_C void Panic(TGridPanic aPanic)
	{
	_LIT(KGridPanic,"GRIDIMG");
	User::Panic(KGridPanic,aPanic);
	}

EXPORT_C void TGridUtils::FillRect(CGraphicsContext* aGc,TRgb aColor,const TRect &aRect)
/** Fills the specified rectangle with the specified colour.

@param aGc The graphics context to be used.
@param aColor The colour which is to fill the rectangle.
@param aRect The rectangle to be filled.
@panic GRIDIMG 0 In debug mode only, if the pointer to the graphics context 
is Null. */
	{
	__ASSERT_DEBUG(aGc!=NULL,Panic(EGridImgInvalidGC));
	aGc->SetBrushStyle(CGraphicsContext::ESolidBrush);
	aGc->SetPenStyle(CGraphicsContext::ENullPen);
	aGc->SetBrushColor(aColor);
	aGc->DrawRect(aRect);
	aGc->SetPenStyle(CGraphicsContext::ESolidPen);
	aGc->SetBrushStyle(CGraphicsContext::ENullBrush);
	}

//

EXPORT_C CGridCellImg::CGridCellImg()
	: iBurstColOffset(0),
	iBurstLeft(0),
	iBurstRight(0),
	iGridLineFlags(EIsHorizontalGridLines|EIsVerticalGridLines)
/** Default constructor. */
	{
	}

EXPORT_C CGridCellImg::~CGridCellImg()
/** Destructor. */
	{
	}


EXPORT_C TInt CGridCellImg::DataWidthInPixelsL(const TCellRef& /*aCell*/) const
/**	Gets the width of the data contained in the specified cell.
@publishedAll 
@released
@param aCell The cell to be tested.
@return The width of the data, in pixels. The default implementation returns zero.*/
	{
	return 0;
	}

EXPORT_C TBool CGridCellImg::DoesCellContainDataL(const TCellRef& /*aCell*/) const
/**	Tests whether the specified cell contains data.
@publishedAll 
@released
@param aCell The cell to be tested.
@return True, if the cell contains data; false, otherwise. The default implementation returns true.*/
	{
	return ETrue;
	}

EXPORT_C void CGridCellImg::Reserved_1()
	{
// No implementation yet
	}

void CGridCellImg::SetBurstingData(TInt aBurstColOffset,TInt aBurstLeft,TInt aBurstRight)
	{
	iBurstColOffset=aBurstColOffset;
	iBurstLeft=aBurstLeft;
	iBurstRight=aBurstRight;
	}

//

EXPORT_C CGridLabelImg::CGridLabelImg(const TFontSpec& aFontSpec,MGraphicsDeviceMap* aGraphicsDeviceMap)
	: iFontSpec(aFontSpec),
	iGraphicsDeviceMap(aGraphicsDeviceMap)
/** Constructor taking specified parameters.

@param aFontSpec A font specification in device independent terms.
@param aGraphicsDeviceMap An interface for mapping between twips and device-specific 
units. */
	{
	}

EXPORT_C CGridLabelImg::~CGridLabelImg()
/** Destructor.

Releases resources before the object is destroyed. Specifically, it releases 
the font acquired when the object was constructed. */
	{
	if (iGraphicsDeviceMap && iFont)
		iGraphicsDeviceMap->ReleaseFont(iFont);
	}

EXPORT_C void CGridLabelImg::ConstructL()
/** Implements the second phase of two-phase construction.

Specifically, it gets the nearest font to that specified in the font specification 
passed to the constructor. */
	{
	NotifyGraphicsDeviceMapChangeL();
	}


EXPORT_C void CGridLabelImg::DrawTopLeftLabelL(CGraphicsContext* aGc,const TRect& aRect) const
/** Fills the specified rectangle with a colour.

The default implementation fills the specified rectangle with the background 
colour value as defined by the grid colour specification in iGridColors.
@publishedAll 
@released 
@param aGc The graphics context to be used.
@param aRect The rectangle to be filled.
@see TGridColors */
	{
//	TGridUtils::FillRect(aGc,KGridBackgroundColor,aRect);
//->
	TGridUtils::FillRect(aGc, iGridColors.iBackground, aRect);
	}

EXPORT_C void CGridLabelImg::DrawTopLeftLabelL(CGraphicsContext* aGc,const TRect& aRect, TRgb aColor) const
/** Fills the specified rectangle with the specified colour.

@param aGc The graphics context to be used.
@param aRect The rectangle to be filled.
@param aColor The colour which is to fill the rectangle. */
	{
	TGridUtils::FillRect(aGc, aColor, aRect);
	}
//->


EXPORT_C TInt CGridLabelImg::SideLabelWidthInPixels(TInt /*aStartRow*/,TInt /*aEndRow*/) const
/** Gets the width of the side labels.
@publishedAll 
@released 
@param aStartRow A start row. The default implementation does not use this value, 
but a derived class can use this to define the start of a range of rows, 
which may be useful if side labels have variable widths.
@param aEndRow An end row. The default implementation does not use this value, 
but a derived class can use this to define the end of a range of rows, 
which may be useful if side labels have variable widths.
@return The width value, in pixels. The default implementation returns the 
pixel value corresponding to the twips value EDefaultSideLabelWidthInTwips, 
as converted by the graphics device map function MGraphicsDeviceMap::HorizontalTwipsToPixels(). */
	{
	__ASSERT_DEBUG(iGraphicsDeviceMap!=NULL,Panic(EGridNullGraphicsDeviceMap));
	return iGraphicsDeviceMap->HorizontalTwipsToPixels(EDefaultSideLabelWidthInTwips);
	}

EXPORT_C TInt CGridLabelImg::TopLabelHeightInPixels() const
/** Gets the height of the top labels.
@publishedAll 
@released 
@return The height value, in pixels. The default implementation returns the 
pixel value corresponding to the twips value EDefaultTopLabelHeightInTwips, 
as converted by the graphics device map function MGraphicsDeviceMap::VerticalTwipsToPixels(). */
	{
	__ASSERT_DEBUG(iGraphicsDeviceMap!=NULL,Panic(EGridNullGraphicsDeviceMap));
	return iGraphicsDeviceMap->VerticalTwipsToPixels(EDefaultTopLabelHeightInTwips);
	}

EXPORT_C void CGridLabelImg::DrawRowCursorL(CGraphicsContext* /*aGc*/,const TRect& /*aRect*/) const
/** Draws a cursor to identify a row.

The default implementation is empty.
@publishedAll 
@released 
@param aGc The graphics context to be used.
@param aRect The rectangle in which the cursor is to be drawn. */
//
// To be overridden from if used
//
	{}

EXPORT_C void CGridLabelImg::ReleaseFont()
//
// Should be called before any change in the zoom factor device
/** Releases the font.

This is called by the destructor, and should be called before calling SetGraphicsDeviceMap().

@see ConstructL() */
	{
	__ASSERT_DEBUG(iGraphicsDeviceMap!=NULL,Panic(EGridNullGraphicsDeviceMap));
	iGraphicsDeviceMap->ReleaseFont(iFont);
	iFont=NULL;
	}

EXPORT_C void CGridLabelImg::NotifyGraphicsDeviceMapChangeL()
/** Deals with the result of changing the graphics device map, i.e. the interface 
for mapping between twips and device-specific units.

The function releases the existing font, and then tries to get the nearest 
font to that specified in the font specification.

@see ConstructL()
@see SetGraphicsDeviceMap() */
	{
	ReleaseFont();
	User::LeaveIfError(iGraphicsDeviceMap->GetNearestFontInTwips(iFont,iFontSpec));
	}

//

EXPORT_C CGridImg* CGridImg::NewL(CGridCellImg* aGridCellImg,CGridLay* aGridLay)
/** Creates a new grid image object suitable for printing.

@param aGridCellImg A pointer to an object that draws the contents of a 
single cell.
@param aGridLay A pointer to the object that controls the layout of rows and 
columns.
@return A pointer to the new grid image object. */
	{
//->
	CGridImg* self = new(ELeave) CGridImg(aGridCellImg,aGridLay);
	if (aGridLay && aGridCellImg)
		aGridCellImg->SetGridColors(aGridLay->GridColors());
	return self;
//->
//	return new(ELeave) CGridImg(aGridCellImg,aGridLay);
	}

CGridImg::CGridImg(CGridCellImg* aGridCellImg,CGridLay* aGridLay)
//
// Construct a partial gridImg object for printing with the same data as the passed gridImg
// and a handle to the passed gridLay
	: iGridCellImg(aGridCellImg),
	iGridLay(aGridLay)
	{
	}

EXPORT_C CGridImg* CGridImg::NewL(CGraphicsDevice* aGraphicsDevice,CGridCellImg* aGridCellImg,CGridLay* aGridLay)
/** Creates a new grid image object.

@param aGraphicsDevice The graphics device to be used for drawing.
@param aGridCellImg A pointer to an object that draws the contents of a single 
cell.
@param aGridLay A pointer to the object that controls the layout of rows and 
columns.
@return A pointer to the new grid image object. */
	{
	CGridImg* self=new(ELeave) CGridImg(aGraphicsDevice,aGridCellImg,aGridLay);
	CleanupStack::PushL(self);
//->
	if (aGridLay && aGridCellImg)
		aGridCellImg->SetGridColors(aGridLay->GridColors());
//->
	self->ConstructL();
	CleanupStack::Pop();
	return self;
	}

CGridImg::CGridImg(CGraphicsDevice *aGraphicsDevice,CGridCellImg *aGridCellImg,CGridLay* aGridLay)
	: iGraphicsDevice(aGraphicsDevice),
	iGridCellImg(aGridCellImg),
	iGridLay(aGridLay),
	iDragLabel(0),
	iCurrentDragPos(0),
	iDragDiff(0),
	iDragFlags(0),
	iDragDim(ENoDrag),
	iXRefPoint(EMainRef),
	iYRefPoint(EMainRef)
	{
	}

void CGridImg::ConstructL()
	{
#if !defined(__WINC__)
	if (iGraphicsDevice)
		User::LeaveIfError(iGraphicsDevice->CreateContext((CGraphicsContext*&)iGc));
#endif
	}

EXPORT_C CGridImg::~CGridImg()
/** Destructor.

Frees resources before destruction of the object. */
	{
#if !defined(__WINC__)
	delete iGc;
	delete iDragBmp;
#endif
	delete iSelected;
	}

void CGridImg::ConstructSelectedL(const TRangeRef& aGridRange)
	{
    delete iSelected;
    iSelected=NULL; // in case next line fails
	iSelected = CGridCellRegion::NewL(aGridRange);
	}

void CGridImg::CreateGc(CGraphicsContext* aGc)
	{
	__ASSERT_DEBUG(iGcPtr==NULL,Panic(EGridImgInvalidGC));
	iGcPtr=aGc;
#if !defined(__WINC__)
    if (iGcPtr==iGc)
    	iGc->Activate(*iWin);
#endif
	}

void CGridImg::DeleteGc()
	{
	__ASSERT_DEBUG(iGcPtr!=NULL,Panic(EGridImgInvalidGC));
#if !defined(__WINC__)
	if (iGcPtr==iGc)
    	iGc->Deactivate();
#endif
	iGcPtr=NULL;
	}

void CGridImg::DrawAllGridLabelsL() const
// Draw all the grid labels
	{
	__ASSERT_DEBUG(iGcPtr!=NULL,Panic(EGridImgInvalidGC));
	DrawTopLeftGridLabelL();
	TRangeRef titleRange=iGridLay->TitleRange();
	if (iGridLay->IsHorizontalTitleLine())
		DrawSideGridLabelsL(titleRange.iFrom.iRow,titleRange.iTo.iRow-1,ETitleRef);
	if (iGridLay->IsVerticalTitleLine())
		DrawTopGridLabelsL(titleRange.iFrom.iCol,titleRange.iTo.iCol-1,ETitleRef);
	TRangeRef visRange=iGridLay->VisibleRange();
	DrawTopGridLabelsL(visRange.iFrom.iCol,visRange.iTo.iCol);
	DrawSideGridLabelsL(visRange.iFrom.iRow,visRange.iTo.iRow);
	}

void CGridImg::DrawTopLeftGridLabelL() const
// Draw top left corner label
	{
	__ASSERT_DEBUG(iGcPtr!=NULL,Panic(EGridImgInvalidGC));
	if (iGridLay->IsTopLabels() && iGridLay->IsSideLabels())
		{
		TRect rect(iGridRect.iTl,iTitlePoint);
		if (iGridLay->IsGridLabelSeparators())
			{
		    rect.Resize(-1,-1);
//->
		    iGcPtr->SetPenColor(iGridLay->GridColors().iLabelSeparators);
//		    iGcPtr->SetPenColor(KRgbGridLabelSeparators);
//->
		    TPoint start(rect.iTl.iX,rect.iBr.iY);
		    TPoint finish(rect.iBr.iX+1,rect.iBr.iY);
		    iGcPtr->DrawLine(start,finish);
		    start.SetXY(rect.iBr.iX,rect.iTl.iY);
		    iGcPtr->DrawLine(start,rect.iBr);
            }
//->
//		iGridLabelImg->DrawTopLeftLabelL(iGcPtr,rect);
		iGridLabelImg->DrawTopLeftLabelL(iGcPtr, rect, iGridLay->GridColors().iBackground);
//->
		}
	}

void CGridImg::DrawTopGridLabelsL(TInt aStartCol,TInt aEndCol,TRefPoint aXRef) const
// Draws all the top grid labels within the specified column range
	{
	__ASSERT_DEBUG(iGcPtr!=NULL,Panic(EGridImgInvalidGC));
	if (!iGridLay->IsTopLabels() || iGridLabelImg==NULL)
		return;
	TInt separatorCorr=(iGridLay->IsGridLabelSeparators()) ? 1 : 0;
	TRect rect;
	rect.iTl.iY=iGridRect.iTl.iY;
	rect.iBr.iY=iTitlePoint.iY-separatorCorr;
	rect.iTl.iX=((aXRef==ETitleRef) ? iGridLay->TitleColumnToXVal(aStartCol) :
		iGridLay->ColumnToXVal(aStartCol));
	rect.iBr.iX=rect.iTl.iX-separatorCorr;
	TBool doGrayFill=EFalse;
	TRangeRef visRange=iGridLay->VisibleRange();
	if (aEndCol>=visRange.iTo.iCol)
		{
		aEndCol=visRange.iTo.iCol;
		if (aEndCol>iGridLay->GridRange().iTo.iCol)
			{
			aEndCol--;
			doGrayFill=ETrue;
			}
		}
	iGcPtr->SetClippingRect(TRect(iTitlePoint.iX,iGridRect.iTl.iY,iGridRect.iBr.iX,iTitlePoint.iY));
	if (iGridLay->IsGridLabelSeparators())
		{
		for (TInt ii=aStartCol;ii<=aEndCol;ii++)
			{
			rect.iBr.iX+=iGridLay->ColumnWidthInPixels(ii);
			iGridLabelImg->DrawColLabelL(iGcPtr,ii,rect);
			rect.iTl.iX=rect.iBr.iX;
//->
		    iGcPtr->SetPenColor(iGridLay->GridColors().iLabelSeparators);
//			iGcPtr->SetPenColor(KRgbGridLabelSeparators);
//->
			iGcPtr->DrawLine(rect.iTl,rect.iBr);
			rect.iTl.iX++;
			}
		}
	else
		{
		for (TInt ii=aStartCol;ii<=aEndCol;ii++)
			{
			rect.iBr.iX+=iGridLay->ColumnWidthInPixels(ii);
			iGridLabelImg->DrawColLabelL(iGcPtr,ii,rect);
			rect.iTl.iX=rect.iBr.iX;
			}
		}
	if (doGrayFill)	
		{
		TGridUtils::FillRect(iGcPtr,iGridLay->iGridEdgeColor,
			TRect(rect.iTl.iX,rect.iTl.iY,iGridRect.iBr.iX,rect.iBr.iY+separatorCorr));
		}
	if (iGridLay->IsGridLabelSeparators())
		{
	    rect.iBr.iX++;
//->
	    iGcPtr->SetPenColor(iGridLay->GridColors().iLabelSeparators);
//	    iGcPtr->SetPenColor(KRgbGridLabelSeparators);
	    iGcPtr->DrawLine(TPoint(iTitlePoint.iX,rect.iBr.iY),rect.iBr);
//->
        }
	iGcPtr->CancelClippingRect();
	}

void CGridImg::DrawSideGridLabelsL(TInt aStartRow,TInt aEndRow,TRefPoint aYRef) const
	{
	//
	// Draw all the side grid labels within the specified row range
	//
	__ASSERT_DEBUG(iGcPtr!=NULL,Panic(EGridImgInvalidGC));
	if (!iGridLay->IsSideLabels() || iGridLabelImg==NULL)
		return;
	TInt separatorCorr=(iGridLay->IsGridLabelSeparators()) ? 1 : 0;
	TRect rect;
	rect.iTl.iX=iGridRect.iTl.iX;
	rect.iBr.iX=iTitlePoint.iX-separatorCorr;
	rect.iTl.iY=((aYRef==ETitleRef) ? iGridLay->TitleRowToYVal(aStartRow) :
		iGridLay->RowToYVal(aStartRow));
	TInt startY=rect.iTl.iY;
	rect.iBr.iY=rect.iTl.iY-separatorCorr;
	TBool doGrayFill=EFalse;
	TRangeRef visRange=iGridLay->VisibleRange();
	if (aEndRow>=visRange.iTo.iRow)
		{
		aEndRow=visRange.iTo.iRow;
		TInt reqRow;
		if (iGridLay->RequestRow(aEndRow,reqRow))
			{
			if (aEndRow!=reqRow)
				{
				aEndRow--;
				doGrayFill=ETrue;
				}
			}
		else
			{
			aEndRow=aStartRow-1;	// guarantees not to go into loop
			doGrayFill=ETrue;
			}
		}
	iGcPtr->SetClippingRect(TRect(iGridRect.iTl.iX,iTitlePoint.iY,iTitlePoint.iX,iGridRect.iBr.iY));
	if (iGridLay->IsGridLabelSeparators())
		{
		for (TInt ii=aStartRow;ii<=aEndRow;ii++)
			{
			rect.iBr.iY+=iGridLay->RowHeightInPixels(ii);
			iGridLabelImg->DrawRowLabelL(iGcPtr,ii,rect);
			if (ii==iCursorPos.iRow)
				iGridLabelImg->DrawRowCursorL(iGcPtr,rect);
			rect.iTl.iY=rect.iBr.iY;
//->
		    iGcPtr->SetPenColor(iGridLay->GridColors().iLabelSeparators);
//			iGcPtr->SetPenColor(KRgbGridLabelSeparators);
//->
			iGcPtr->DrawLine(rect.iTl,rect.iBr);
			rect.iTl.iY++;
			}
		}
	else
		{
		for (TInt ii=aStartRow;ii<=aEndRow;ii++)
			{
			rect.iBr.iY+=iGridLay->RowHeightInPixels(ii);
			iGridLabelImg->DrawRowLabelL(iGcPtr,ii,rect);
			if (ii==iCursorPos.iRow)
				iGridLabelImg->DrawRowCursorL(iGcPtr,rect);
			rect.iTl.iY=rect.iBr.iY;
			}
		}
	if (doGrayFill)
		{
		TGridUtils::FillRect(iGcPtr,iGridLay->iGridEdgeColor,
			TRect(rect.iTl.iX,rect.iTl.iY,rect.iBr.iX+separatorCorr,iGridRect.iBr.iY));
		}
	if (iGridLay->IsGridLabelSeparators())
		{
		rect.iBr.iY++;
//->
	    iGcPtr->SetPenColor(iGridLay->GridColors().iLabelSeparators);
//		iGcPtr->SetPenColor(KRgbGridLabelSeparators);
//->
		iGcPtr->DrawLine(TPoint(rect.iBr.iX,startY),rect.iBr);
		}
	iGcPtr->CancelClippingRect();
	}

void CGridImg::DrawSideGridLabelIfOnScreenL(TInt aRow) const
	{
	__ASSERT_DEBUG(iGcPtr!=NULL,Panic(EGridImgInvalidGC));
	TBool doDraw=EFalse;
	TRefPoint refPoint=EMainRef;
	TRangeRef visRange=iGridLay->VisibleRange();
	if (aRow>=visRange.iFrom.iRow && aRow<=visRange.iTo.iRow)
		doDraw=ETrue;
	else if (iGridLay->IsHorizontalTitleLine())
		{
		TRangeRef titleRange=iGridLay->TitleRange();
		if (aRow>=titleRange.iFrom.iRow && aRow<titleRange.iTo.iRow)
			{
			doDraw=ETrue;
			refPoint=ETitleRef;
			}
		}
	if (doDraw)
		DrawSideGridLabelsL(aRow,aRow,refPoint);
	}

EXPORT_C void CGridImg::DrawTitleLines() const
/** Draws the title lines. */
	{
#if !defined(__WINC__)
	((CGridImg*)this)->CreateGc(iGc);
	DrawVerticalTitleLine();
	DrawHorizontalTitleLine();
	((CGridImg*)this)->DeleteGc();
#endif
	}

EXPORT_C void CGridImg::ClearTitleLineRegionL(const TPoint& aCrossPoint) const
/** Clears the region where the the title lines are.

@param aCrossPoint Any point within the title region. */
	{
	TRect rect(Max(aCrossPoint.iX-1,iTitlePoint.iX),iTitlePoint.iY,
		aCrossPoint.iX,iGridRect.iBr.iY);
	BeginRedrawAndDrawL(rect);
	rect.SetRect(iTitlePoint.iX,Max(aCrossPoint.iY-1,iTitlePoint.iY),
		iGridRect.iBr.iX,aCrossPoint.iY);
	BeginRedrawAndDrawL(rect);
	}

void CGridImg::DrawVerticalTitleLine() const
	{
	__ASSERT_DEBUG(iGcPtr!=NULL,Panic(EGridImgInvalidGC));
	if (iMainPoint.iX>iTitlePoint.iX)
		{
//->
	    iGcPtr->SetPenColor(iGridLay->GridColors().iLabelSeparators);
//		iGcPtr->SetPenColor(KRgbGridLabelSeparators);
//->
		iGcPtr->DrawLine(TPoint(iMainPoint.iX-1,iTitlePoint.iY-1),
			TPoint(iMainPoint.iX-1,iGridRect.iBr.iY));
		}
	}

void CGridImg::DrawHorizontalTitleLine() const
	{
	__ASSERT_DEBUG(iGcPtr!=NULL,Panic(EGridImgInvalidGC));
	if (iMainPoint.iY>iTitlePoint.iY)
		{
//->
	    iGcPtr->SetPenColor(iGridLay->GridColors().iLabelSeparators);
//		iGcPtr->SetPenColor(KRgbGridLabelSeparators);
//->
		iGcPtr->DrawLine(TPoint(iTitlePoint.iX-1,iMainPoint.iY-1),
			TPoint(iGridRect.iBr.iX,iMainPoint.iY-1));
		}
	}

void CGridImg::DrawAllGridLinesAndCellsL() const
	// Draws all the grid lines and cells
	{
	__ASSERT_DEBUG(iGcPtr!=NULL,Panic(EGridImgInvalidGC));
	TRangeRef visRange=iGridLay->VisibleRange();
	if (iGridLay->IsEncroachingCellBorders())
		{
		if (iGridLay->IsVisibleToRowFullyVisible())
			visRange.iTo.iRow++;
		if (iGridLay->IsVisibleToColumnFullyVisible())
			visRange.iTo.iCol++;
		}
	TRect clippingRect;
	TRangeRef titleRange=iGridLay->TitleRange();
	TBool isHorizontalTitleLine=iGridLay->IsHorizontalTitleLine();
	TBool isVerticalTitleLine=iGridLay->IsVerticalTitleLine();
	TRangeRef range;
	if (isHorizontalTitleLine && isVerticalTitleLine)
		{
		clippingRect.SetRect(iTitlePoint,iMainPoint);
		DrawGridLinesAndCellsInRangeL(titleRange,clippingRect,ETitleRef,ETitleRef);
		}
	if (isHorizontalTitleLine)
		{
		clippingRect.SetRect(iMainPoint.iX,iTitlePoint.iY,iGridRect.iBr.iX,iMainPoint.iY);
		range.SetRange(titleRange.iFrom.iRow,visRange.iFrom.iCol,
			titleRange.iTo.iRow,visRange.iTo.iCol);
		DrawGridLinesAndCellsInRangeL(range,clippingRect,EMainRef,ETitleRef);
		}
	if (isVerticalTitleLine)
		{
		clippingRect.SetRect(iTitlePoint.iX,iMainPoint.iY,iMainPoint.iX,iGridRect.iBr.iY);
		range.SetRange(visRange.iFrom.iRow,titleRange.iFrom.iCol,
			visRange.iTo.iRow,titleRange.iTo.iCol);
		DrawGridLinesAndCellsInRangeL(range,clippingRect,ETitleRef,EMainRef);
		}
	clippingRect.SetRect(iMainPoint,iGridRect.iBr);
	DrawGridLinesAndCellsInRangeL(visRange,clippingRect);
	}

void CGridImg::DrawGridLinesAndCellsInRangeL(const TRangeRef& aRange,const TRect& aClipRect,
	TRefPoint aXRef,TRefPoint aYRef) const
// Draws the grid cells for the given cell range
	{
	__ASSERT_DEBUG(iGcPtr!=NULL,Panic(EGridImgInvalidGC));
	TRect rangeRect;
	if (aYRef==ETitleRef)
		{
		rangeRect.iTl.iY=iGridLay->TitleRowToYVal(aRange.iFrom.iRow);
		rangeRect.iBr.iY=iMainPoint.iY-1;
		}
	else
		{
		rangeRect.iTl.iY=iGridLay->RowToYVal(aRange.iFrom.iRow);
		rangeRect.iBr.iY=iGridRect.iBr.iY;
		}
	if (aXRef==ETitleRef)
		{
		rangeRect.iTl.iX=iGridLay->TitleColumnToXVal(aRange.iFrom.iCol);
		rangeRect.iBr.iX=iMainPoint.iX-1;
		}
	else
		{
		rangeRect.iTl.iX=iGridLay->ColumnToXVal(aRange.iFrom.iCol);
		rangeRect.iBr.iX=iGridRect.iBr.iX;
		}
	
	TInt endCol=aRange.iTo.iCol;
	TBool doRightFill=EFalse;
	TRangeRef visRange=iGridLay->VisibleRange();
	if (endCol>=visRange.iTo.iCol)
		{
		endCol=visRange.iTo.iCol;
		if (endCol>iGridLay->GridRange().iTo.iCol)
			{
			endCol--;
			doRightFill=ETrue;
			}
		}
	TInt endRow=aRange.iTo.iRow;
	TBool doBottomFill=EFalse;
	if (endRow>=visRange.iTo.iRow)
		{
		endRow=visRange.iTo.iRow;
		TInt reqRow;
		if (iGridLay->RequestRow(endRow,reqRow))
			{
			if (endRow!=reqRow)
				{
				endRow--;
				doBottomFill=ETrue;
				}
			}
		else
			{
			endRow=aRange.iFrom.iRow-1;
			doBottomFill=ETrue;
			}
		}
//->
	iGcPtr->SetPenColor((iGcPtr->Device()->DisplayMode()==EGray2) ? KRgbBlack : iGridLay->GridColors().iLines);		// To workaround a problem when printing gray lines
//	iGcPtr->SetPenColor((iGcPtr->Device()->DisplayMode()==EGray2) ? KRgbBlack : KRgbGridLines);		// To workaround a problem when printing gray lines
//->
	TRect rect;
	rect.iTl.iX=rect.iBr.iX=rangeRect.iTl.iX-1;
	if (iGridLay->IsVerticalGridLines())
		{
		rect.iTl.iY=rangeRect.iTl.iY;
		rect.iBr.iY=(doBottomFill) ? iGridLay->RowToYVal(endRow+1) : rangeRect.iBr.iY;
		}
	TInt startCol=aRange.iFrom.iCol;
	TInt pageCol=KMaxTInt;
	if (!iGridLay->IsPageBreakLinesHidden())
		iGridLay->FindNextColumnPageBreak(startCol,pageCol);
	iGcPtr->SetClippingRect(aClipRect);
	for (;startCol<=endCol;startCol++)
		{
		rect.Move(iGridLay->ColumnWidthInPixels(startCol),0);
		if (startCol==pageCol)
			{
			TPoint start(rect.iTl.iX,iTitlePoint.iY);
			TPoint end(rect.iBr.iX,rangeRect.iBr.iY);
//->
			iGcPtr->SetPenColor(iGridLay->GridColors().iBackground);
//			iGcPtr->SetPenColor(KRgbGridBackground);
//->
			iGcPtr->DrawLine(start,end);
//->
		    iGcPtr->SetPenColor(iGridLay->GridColors().iLabelSeparators);
//			iGcPtr->SetPenColor(KRgbGridLabelSeparators);
//->
			iGcPtr->SetPenStyle((iGridLay->IsHardColumnPageBreak(pageCol+1))
				? CGraphicsContext::EDotDashPen : CGraphicsContext::EDashedPen);
			iGcPtr->DrawLine(start,end);
			iGcPtr->SetPenStyle(CGraphicsContext::ESolidPen);
//->
			iGcPtr->SetPenColor((iGcPtr->Device()->DisplayMode()==EGray2) ? KRgbBlack : iGridLay->GridColors().iLines);
//			iGcPtr->SetPenColor((iGcPtr->Device()->DisplayMode()==EGray2) ? KRgbBlack : KRgbGridLines);
//->
			iGridLay->FindNextColumnPageBreak(startCol+1,pageCol);
			}
		else
			iGcPtr->DrawLine(rect.iTl,rect.iBr);
		}
	if (doRightFill)
		{
		TGridUtils::FillRect(iGcPtr,iGridLay->iGridEdgeColor,
			TRect(rect.iTl.iX+1,rangeRect.iTl.iY,iGridRect.iBr.iX,rangeRect.iBr.iY));
		}

	rect.iTl.iY=rect.iBr.iY=rangeRect.iTl.iY-1;
	if (iGridLay->IsHorizontalGridLines())
		{
		rect.iTl.iX=rangeRect.iTl.iX;
		rect.iBr.iX=(doRightFill) ? iGridLay->ColumnToXVal(endCol+1) : rangeRect.iBr.iX;
		}
	TInt startRow=aRange.iFrom.iRow;
	TInt pageRow=KMaxTInt;
	if (!iGridLay->IsPageBreakLinesHidden())
		iGridLay->FindNextRowPageBreak(startRow,pageRow);
	for (;startRow<=endRow;startRow++)
		{
		rect.Move(0,iGridLay->RowHeightInPixels(startRow));
		if (startRow==pageRow)
			{
			TPoint start(iTitlePoint.iX,rect.iTl.iY);
			TPoint end(rangeRect.iBr.iX,rect.iBr.iY);
//->
			iGcPtr->SetPenColor(iGridLay->GridColors().iBackground);
//			iGcPtr->SetPenColor(KRgbGridBackground);
//->
			iGcPtr->DrawLine(start,end);
//->
		    iGcPtr->SetPenColor(iGridLay->GridColors().iLabelSeparators);
//			iGcPtr->SetPenColor(KRgbGridLabelSeparators);
//->
			iGcPtr->SetPenStyle((iGridLay->IsHardRowPageBreak(pageRow+1))
				? CGraphicsContext::EDotDashPen : CGraphicsContext::EDashedPen);
			iGcPtr->DrawLine(start,end);
			iGcPtr->SetPenStyle(CGraphicsContext::ESolidPen);
//->
			iGcPtr->SetPenColor((iGcPtr->Device()->DisplayMode()==EGray2) ? KRgbBlack : iGridLay->GridColors().iLines);
//			iGcPtr->SetPenColor((iGcPtr->Device()->DisplayMode()==EGray2) ? KRgbBlack : KRgbGridLines);
//->
			iGridLay->FindNextRowPageBreak(startRow+1,pageRow);
			}
		else
			iGcPtr->DrawLine(rect.iTl,rect.iBr);
		}
	if (doBottomFill)
		{
		TGridUtils::FillRect(iGcPtr,iGridLay->iGridEdgeColor,
			TRect(rangeRect.iTl.iX,rect.iTl.iY+1,rangeRect.iBr.iX,iGridRect.iBr.iY));
		}
	iGcPtr->CancelClippingRect();
	DrawCellsToGcL(iGcPtr,aRange,aClipRect,rangeRect.iTl);
	}

void CGridImg::DrawCellsToGcL(CGraphicsContext* aGc,const TRangeRef& aRange,const TRect& aClipRect,
	const TPoint& aStartPoint,TInt aScaleFactor) const
	{
	TCellRef startCell=aRange.iFrom;
	if (!iGridLay->LimitCell(startCell))
		return;	// Nothing to draw
	TCellRef endCell = aRange.iTo;
	iGridLay->LimitCell(endCell);
	TRect rect;
	TInt yPos=aStartPoint.iY;
	rect.iTl.iY = yPos*EScaleOneToOne/aScaleFactor;
	TCellRef cell = aRange.iFrom;
	TInt horzLineCorr=(iGridLay->IsHorizontalGridLines()) ? 1 : 0;
	TInt vertLineCorr=(iGridLay->IsVerticalGridLines()) ? 1 : 0;
	iGridCellImg->iGridLineFlags=0;
	if (horzLineCorr)
		iGridCellImg->iGridLineFlags|=CGridCellImg::EIsHorizontalGridLines;
	if (vertLineCorr)
		iGridCellImg->iGridLineFlags|=CGridCellImg::EIsVerticalGridLines;
	for (;cell.iRow<=endCell.iRow;cell.iRow++)
		{
		TInt xPos=aStartPoint.iX;
		rect.iTl.iX=xPos*EScaleOneToOne/aScaleFactor;
		yPos+=iGridLay->RowHeightInPixels(cell.iRow);
		rect.iBr.iY = yPos*EScaleOneToOne/aScaleFactor-vertLineCorr;
		cell.iCol=aRange.iFrom.iCol;
		if (iGridLay->IsColumnBursting())
			{
			if (cell.iCol<=endCell.iCol)
				{
				xPos+=iGridLay->ColumnWidthInPixels(cell.iCol);
				rect.iBr.iX = xPos*EScaleOneToOne/aScaleFactor-horzLineCorr;
				TCellRef burstCell=cell;
				TInt burstLeft=CalcBurstLeftL(burstCell,aScaleFactor);
				DrawBurstingCellL(aGc,cell,rect,aClipRect,aScaleFactor,burstLeft,burstCell);
				burstLeft+=rect.Width()+horzLineCorr;
				rect.iTl.iX=rect.iBr.iX+horzLineCorr;
				for (cell.iCol++;cell.iCol<=endCell.iCol;cell.iCol++)
					{
					xPos+=iGridLay->ColumnWidthInPixels(cell.iCol);
					rect.iBr.iX = xPos*EScaleOneToOne/aScaleFactor-horzLineCorr;
					if (iGridCellImg->DoesCellContainDataL(cell))
						{
						burstLeft=0;
						burstCell.iCol=cell.iCol;
						}
					DrawBurstingCellL(aGc,cell,rect,aClipRect,aScaleFactor,burstLeft,burstCell);
					burstLeft+=rect.Width()+horzLineCorr;
					rect.iTl.iX=rect.iBr.iX+horzLineCorr;
					}
				}
			}
		else
			{
			for (;cell.iCol<=endCell.iCol;cell.iCol++)
				{
				xPos+=iGridLay->ColumnWidthInPixels(cell.iCol);
				rect.iBr.iX = xPos*EScaleOneToOne/aScaleFactor-horzLineCorr;
				iGridCellImg->DrawL(aGc,cell,rect,aClipRect);
				rect.iTl.iX=rect.iBr.iX+horzLineCorr;
				}
			}
		rect.iTl.iY=rect.iBr.iY+vertLineCorr;
		}
	ResetGcToDefault(aGc);
	}

void CGridImg::DrawBurstingCellL(CGraphicsContext* aGc,const TCellRef& aCell,const TRect& aRect,const TRect& aClipRect,
	TInt aScaleFactor,TInt aBurstLeft,const TCellRef& aBurstCell) const
	{
	TInt burstDataWidth=iGridCellImg->DataWidthInPixelsL(aBurstCell);
	if (burstDataWidth<=aBurstLeft)
		iGridCellImg->DrawL(aGc,aCell,aRect,aClipRect);
	else
		{
		TInt excessRight=burstDataWidth-aBurstLeft-aRect.Width();
		iGridCellImg->SetBurstingData(aCell.iCol-aBurstCell.iCol,aBurstLeft,
			CalcBurstRightL(aCell,excessRight,aScaleFactor));
		iGridCellImg->DrawL(aGc,aCell,aRect,aClipRect);
		iGridCellImg->SetBurstingData();
		}
	}

TInt CGridImg::CalcBurstLeftL(TCellRef& aBurstCell,TInt aScaleFactor) const
	{
	enum { EMaxNumberChecked = 20 };
	const TInt limit=Max(aBurstCell.iCol-EMaxNumberChecked,iGridLay->GridRange().iFrom.iCol);
	TInt burstLeft=0;
	while (aBurstCell.iCol>limit && !iGridCellImg->DoesCellContainDataL(aBurstCell))
		{
		burstLeft+=iGridLay->ColumnWidthInPixels(--aBurstCell.iCol);
		}
	return burstLeft*EScaleOneToOne/aScaleFactor;
	}

TInt CGridImg::CalcBurstRightL(const TCellRef& aCell,TInt aExcessRight,TInt aScaleFactor) const
	{
	TInt limit=iGridLay->GridRange().iTo.iCol;
	TInt burstRight=0;
	TInt scaledBurstRight=0;
	for (TCellRef forwardCell(aCell.iRow,aCell.iCol+1);forwardCell.iCol<=limit;forwardCell.iCol++)
		{
		TInt width=iGridLay->ColumnWidthInPixels(forwardCell.iCol);
		if (iGridCellImg->DoesCellContainDataL(forwardCell) || scaledBurstRight>aExcessRight)
			{
			break;
			}
		burstRight+=width;
		scaledBurstRight=burstRight*EScaleOneToOne/aScaleFactor;
		}
	return scaledBurstRight;
	}

EXPORT_C void CGridImg::DrawCellL(const TCellRef &aCell) const
/** Draws the content of the specified cell.

@param aCell The cell to be drawn. */
	{
	TRect rect=PartialCellRectL(aCell,MainRect());
	TRect clipRect;
	TBool isHorizontalTitleLine=iGridLay->IsHorizontalTitleLine();
	TBool isVerticalTitleLine=iGridLay->IsVerticalTitleLine();
	if (isHorizontalTitleLine && isVerticalTitleLine)
		{
		clipRect.SetRect(iTitlePoint,iMainPoint);
		rect.BoundingRect(PartialCellRectL(aCell,clipRect,ETitleRef,ETitleRef));
		}
	if (isHorizontalTitleLine)
		{
		clipRect.SetRect(iMainPoint.iX,iTitlePoint.iY,iGridRect.iBr.iX,iMainPoint.iY);
		rect.BoundingRect(PartialCellRectL(aCell,clipRect,EMainRef,ETitleRef));
		}
	if (isVerticalTitleLine)
		{
		clipRect.SetRect(iTitlePoint.iX,iMainPoint.iY,iMainPoint.iX,iGridRect.iBr.iY);
		rect.BoundingRect(PartialCellRectL(aCell,clipRect,ETitleRef,EMainRef));
		}
	BeginRedrawAndDrawL(rect);
	}

TRect CGridImg::PartialCellRectL(const TCellRef& aCell,const TRect& aClipRect,
	TRefPoint aXRef,TRefPoint aYRef) const
	{
	TRect rect;
	rect.iTl=RelativeCellToPoint(aCell,aXRef,aYRef);
	rect.iBr=rect.iTl+iGridLay->CellToPoint(aCell,aCell+TCellRef(1,1));
	if (iGridLay->IsColumnBursting())
		{
		TInt limit=iGridLay->GridRange().iTo.iCol;
		for (TCellRef forwardCell(aCell.iRow,aCell.iCol+1);rect.iBr.iX<iGridRect.iBr.iX && forwardCell.iCol<=limit;forwardCell.iCol++)
			{
			if (iGridCellImg->DoesCellContainDataL(forwardCell))
				break;
			rect.iBr.iX+=iGridLay->ColumnWidthInPixels(forwardCell.iCol);
			}
		}
	rect.iTl-=TPoint(2,2);	//For cell borders
	rect.Intersection(aClipRect);
	return rect;
	}

EXPORT_C void CGridImg::DrawRangeL(const TRangeRef& aRange) const
/** Draws the rectangle corresponding to the specified range.

@param aRange The range to be drawn. */
	{
	TRect rect=PartialRangeRect(aRange,MainRect());
	TRect clipRect;
	TBool isHorizontalTitleLine=iGridLay->IsHorizontalTitleLine();
	TBool isVerticalTitleLine=iGridLay->IsVerticalTitleLine();
	if (isHorizontalTitleLine && isVerticalTitleLine)
		{
		clipRect.SetRect(iTitlePoint,iMainPoint);
		rect.BoundingRect(PartialRangeRect(aRange,clipRect,ETitleRef,ETitleRef));
		}
	if (isHorizontalTitleLine)
		{
		clipRect.SetRect(iMainPoint.iX,iTitlePoint.iY,iGridRect.iBr.iX,iMainPoint.iY);
		rect.BoundingRect(PartialRangeRect(aRange,clipRect,EMainRef,ETitleRef));
		}
	if (isVerticalTitleLine)
		{
		clipRect.SetRect(iTitlePoint.iX,iMainPoint.iY,iMainPoint.iX,iGridRect.iBr.iY);
		rect.BoundingRect(PartialRangeRect(aRange,clipRect,ETitleRef,EMainRef));
		}
	BeginRedrawAndDrawL(rect);
	}

TRect CGridImg::PartialRangeRect(const TRangeRef& aRange,const TRect& aClipRect,
	TRefPoint aXRef,TRefPoint aYRef) const
	{
	TRect rect;
	rect.iTl=RelativeCellToPoint(aRange.iFrom,aXRef,aYRef);
	rect.iBr=rect.iTl+iGridLay->CellToPoint(aRange.iFrom,aRange.iTo+TCellRef(1,1));
	if (iGridLay->IsColumnBursting())
		rect.iBr.iX=iGridRect.iBr.iX;
	rect.iTl-=TPoint(2,2);	//For cell borders
	rect.Intersection(aClipRect);
	return rect;
	}

EXPORT_C void CGridImg::DrawSelectedL() const
/** Draws the currently selected region. */
	{
	TInt count=iSelected->Count();
	if (count==0)
		DrawCellL(iCursorPos);
	else if (count==1)
		DrawRangeL((*iSelected)[0]);
	else
		BeginRedrawAndDrawL();
	}
	
#if defined(__WINC__)
void CGridImg::HighlightMinRegionL(const TRegion& /*aOldRegion*/,const TRegion& /*aNewRegion*/)
	{}
#else

void CGridImg::HighlightMinRegionL(const TRegion& aOldRegion,const TRegion& aNewRegion)
// 
// Highlights the minimum necessary region to get from the old to the new region
//
	{
	RRegion unionRegion;
	unionRegion.Copy(aOldRegion);
	unionRegion.Union(aNewRegion);
	RRegion tempRegion;
	tempRegion.Copy(aOldRegion);
	tempRegion.Intersect(aNewRegion);
	unionRegion.SubRegion(tempRegion);
	tempRegion.Close();
	unionRegion.Tidy();
	if (unionRegion.CheckError())
		{
		unionRegion.Close();
		User::Leave(KErrNoMemory);
		}
	CreateGc(iGc);
	HighlightRegion(unionRegion);
	DeleteGc();
	unionRegion.Close();
	}
#endif

void CGridImg::HighlightRegion(const TRegion &aRegion) const
	{
	//
	// Fills each of the rectangles in the passed region one by one
	//
	__ASSERT_DEBUG(iGcPtr!=NULL,Panic(EGridImgInvalidGC));
	TInt count=aRegion.Count();
	if (count)
		{
		iGcPtr->SetDrawMode(CGraphicsContext::EDrawModeNOTSCREEN);
		iGcPtr->SetBrushStyle(CGraphicsContext::ESolidBrush);
		for (TInt ii=0;ii<count;ii++)
			iGcPtr->DrawRect(aRegion[ii]);
		iGcPtr->SetBrushStyle(CGraphicsContext::ENullBrush);
		iGcPtr->SetDrawMode(CGraphicsContext::EDrawModePEN);
		}
	}

TPoint CGridImg::RelativeCellToPoint(const TCellRef& aCell,
	TRefPoint aXRef,TRefPoint aYRef) const
	{
	TPoint ret;
	ret.iX=(aXRef==ETitleRef) ? iGridLay->TitleColumnToXVal(aCell.iCol) :
		iGridLay->ColumnToXVal(aCell.iCol);
	ret.iY=(aYRef==ETitleRef) ? iGridLay->TitleRowToYVal(aCell.iRow) :
		iGridLay->RowToYVal(aCell.iRow);
	return ret;
	}

TCellRef CGridImg::RelativePointToCell(const TPoint& aPoint,
	TRefPoint aXRef,TRefPoint aYRef) const
	{
	TCellRef ret;
	ret.iCol=(aXRef==ETitleRef) ? iGridLay->XValToTitleColumn(aPoint.iX) :
		iGridLay->XValToColumn(aPoint.iX);
	ret.iRow=(aYRef==ETitleRef) ? iGridLay->YValToTitleRow(aPoint.iY) :
		iGridLay->YValToRow(aPoint.iY);
	return ret;
	}

void CGridImg::AppendPartialHighlightRegionL(TRegion& aRegion,const TRect& aClipRect,
	TRefPoint aXRef,TRefPoint aYRef) const
//
// returns ETrue if there's an error in the region manipulation
	{
	TInt count=iSelected->Count();
	if (!count)
		{
		if (iGridLay->IsCursorVisible())
			{
            if (iGridLay->IsCellOutOfGridRange(iCursorPos))
                return;
			TRect cursor(RelativeCellToPoint(iCursorPos,aXRef,aYRef),TSize(0,0));
			cursor.iBr.iX+=iGridLay->ColumnWidthInPixels(iCursorPos.iCol);
			cursor.iBr.iY+=iGridLay->RowHeightInPixels(iCursorPos.iRow);
		
			TRegionFix<4> region;
			region.AddRect(TRect(cursor.iTl.iX-2,cursor.iTl.iY-2,cursor.iBr.iX+1,cursor.iTl.iY+1));
			region.AddRect(TRect(cursor.iTl.iX-2,cursor.iBr.iY-2,cursor.iBr.iX+1,cursor.iBr.iY+1));
			region.AddRect(TRect(cursor.iTl.iX-2,cursor.iTl.iY+1,cursor.iTl.iX+1,cursor.iBr.iY-2));
			region.AddRect(TRect(cursor.iBr.iX-2,cursor.iTl.iY+1,cursor.iBr.iX+1,cursor.iBr.iY-2));
			region.ClipRect(aClipRect);
			aRegion.Union(region);
			}
		}
    else if (iGridLay->IsHighlightVisible())
		{
		for (TInt ii=0;ii<count;ii++)
			{
			TRangeRef range=(*iSelected)[ii];
			if (!iGridLay->LimitCell(range.iFrom))
				continue;
			iGridLay->LimitCell(range.iTo);
			TRect rect;
			rect.iTl=RelativeCellToPoint(range.iFrom,aXRef,aYRef);
			rect.iBr=RelativeCellToPoint(range.iTo+TCellRef(1,1),aXRef,aYRef);
			rect.Resize(-1,-1);
			rect.Shrink(1,1);
			rect.Intersection(aClipRect);
			if (iSelected->IsColSelected(range.iFrom.iCol,ii) && 
				(iTitlePoint.iY==iMainPoint.iY || aYRef==ETitleRef) &&
				!iGridLay->IsColumnSelectionDisabled())
				{
				rect.iTl.iY=Min(rect.iTl.iY,iGridRect.iTl.iY+1);
				}
			if (iSelected->IsRowSelected(range.iFrom.iRow,ii) &&
				(iTitlePoint.iX==iMainPoint.iX || aXRef==ETitleRef) &&
				!iGridLay->IsRowSelectionDisabled())
				{
				rect.iTl.iX=Min(rect.iTl.iX,iGridRect.iTl.iX+1);
				}
			aRegion.AddRect(rect);
			}
		if (iGridLay->IsCursorVisible())
			{
			if (!iGridLay->IsCellOutOfGridRange(iAnchorPos))
				{
				TRect anchorRect=(TRect(RelativeCellToPoint(iAnchorPos,aXRef,aYRef),TSize(0,0)));
				anchorRect.iBr.iX+=iGridLay->ColumnWidthInPixels(iAnchorPos.iCol);
				anchorRect.iBr.iY+=iGridLay->RowHeightInPixels(iAnchorPos.iRow);
				anchorRect.Resize(-1,-1);
				anchorRect.Shrink(2,2);
				anchorRect.Intersection(aClipRect);
				aRegion.SubRect(anchorRect);
				}
			}
		}
	if (aRegion.CheckError())
		User::Leave(KErrNoMemory);
	}

void CGridImg::AppendTotalHighlightRegionL(TRegion &aRegion) const
	{
	//
	// Creates the total selected region by summing all the rectangles
	// of the cursor or the highlighted regions (including the anchor)
	//
	TRect clipRect=MainRect();
	AppendPartialHighlightRegionL(aRegion,clipRect);
	TBool isHorizontalTitleLine=iGridLay->IsHorizontalTitleLine();
	TBool isVerticalTitleLine=iGridLay->IsVerticalTitleLine();
	if (isHorizontalTitleLine && isVerticalTitleLine)
		{
		clipRect.SetRect(iTitlePoint,iMainPoint-TPoint(1,1));
		if (clipRect.IsNormalized())
			AppendPartialHighlightRegionL(aRegion,clipRect,ETitleRef,ETitleRef);
		}
	if (isHorizontalTitleLine)
		{
		clipRect.SetRect(iMainPoint.iX,iTitlePoint.iY,iGridRect.iBr.iX,iMainPoint.iY-1);
		if (clipRect.IsNormalized())
			AppendPartialHighlightRegionL(aRegion,clipRect,EMainRef,ETitleRef);
		}
	if (isVerticalTitleLine)
		{
		clipRect.SetRect(iTitlePoint.iX,iMainPoint.iY,iMainPoint.iX-1,iGridRect.iBr.iY);
		if (clipRect.IsNormalized())
			AppendPartialHighlightRegionL(aRegion,clipRect,ETitleRef,EMainRef);
		}
	}

void CGridImg::RemoveRowLabelFromRegionL(TInt aRow,TRegion& aRegion) const
//
// Returns ETrue if error
	{
	TInt tlY=iGridLay->VisibleRowToYVal(aRow);
	if (tlY<0)
		return;	// Not on screen
	TRect rect(iGridRect.iTl.iX,tlY,iTitlePoint.iX,tlY+iGridLay->RowHeightInPixels(aRow));
	aRegion.SubRect(rect);
	if (aRegion.CheckError())
		User::Leave(KErrNoMemory);
	}

void CGridImg::CleanupGc(TAny* aObject)
	{
	((CGridImg*)aObject)->DeleteGc();
	}

EXPORT_C void CGridImg::DrawL(CGraphicsContext* aGc) const
/** Draws the entire grid and its contents.

@param aGc The graphics context to be used for drawing. */
	{
	((CGridImg*)this)->CreateGc(aGc);
	iGcPtr->SetClippingRect(iGridRect);	//Needed because of border round grid
	ResetGcToDefault(iGcPtr);
	CleanupStack::PushL(TCleanupItem(CleanupGc,(CGridImg*)this));
	DrawAllGridLabelsL();
	iGcPtr->Reset();
	if (iGridLay->IsAutoClearGridCells())
//->
		TGridUtils::FillRect(iGcPtr, iGridLay->GridColors().iBackground, TRect(iTitlePoint,iGridRect.iBr));
//		TGridUtils::FillRect(iGcPtr,KRgbGridBackground,TRect(iTitlePoint,iGridRect.iBr));
//->
	DrawAllGridLinesAndCellsL();	//Handles its own clipping
	RRegion region;
	CleanupClose<RRegion>::PushL(region);
	AppendTotalHighlightRegionL(region);
	CleanupStack::Pop(2);	// region + gc cleanup
	HighlightRegion(region);
	region.Close();
	DrawVerticalTitleLine();
	DrawHorizontalTitleLine();
	((CGridImg*)this)->DeleteGc();
	CONST_CAST(CGridImg*,this)->DrawResizingDragHiglights(iGridRect);
	}

#if !defined(__WINC__)
LOCAL_C void EndRedraw(TAny* aObject)
	{
	((RWindow*)aObject)->EndRedraw();
	}
#endif

void CGridImg::BeginRedrawAndDrawL() const
	{
#if !defined(__WINC__)
	iWin->Invalidate();
	iWin->BeginRedraw();
	CleanupStack::PushL(TCleanupItem(EndRedraw,iWin));
	DrawL(iGc);
	CleanupStack::PopAndDestroy();
#endif
	}

EXPORT_C void CGridImg::DrawL(CGraphicsContext* aGc,const TRect& aRect) const
/** Draws the grid and its contents that are visible within the specified 
rectangle.

@param aGc The graphics context to be used for drawing.
@param aRect Drawing of the grid is restricted to this rectangle. */
	{
	if (aRect.Contains(iGridRect.iTl) && aRect.Contains(iGridRect.iBr))
		{
		DrawL(aGc);
		return;
		}
	((CGridImg*)this)->CreateGc(aGc);
	ResetGcToDefault(iGcPtr);

	TRangeRef titleRange=iGridLay->TitleRange();
	TBool isHorizontalTitleLine=iGridLay->IsHorizontalTitleLine();
	TBool isVerticalTitleLine=iGridLay->IsVerticalTitleLine();
	TRect clippingRect(iGridRect.iTl,iMainPoint);	//Top left quarter of grid
	CleanupStack::PushL(TCleanupItem(CleanupGc,(CGridImg*)this));
	if (aRect.Intersects(clippingRect))
		{
		clippingRect.Intersection(aRect);
		iGcPtr->SetClippingRect(clippingRect);
		DrawTopLeftGridLabelL();
		if (isVerticalTitleLine)
			DrawTopGridLabelsL(titleRange.iFrom.iCol,titleRange.iTo.iCol-1,ETitleRef);
		if (isHorizontalTitleLine)
			{
			DrawSideGridLabelsL(titleRange.iFrom.iRow,titleRange.iTo.iRow,ETitleRef);
			}
		iGcPtr->Reset();
		if (isVerticalTitleLine && isHorizontalTitleLine)
			{
			clippingRect.SetRect(iTitlePoint,iMainPoint);
			clippingRect.Intersection(aRect);
			if (iGridLay->IsAutoClearGridCells())
//->
				TGridUtils::FillRect(iGcPtr, iGridLay->GridColors().iBackground, clippingRect);
//				TGridUtils::FillRect(iGcPtr,KRgbGridBackground,clippingRect);
//->
			DrawGridLinesAndCellsInRangeL(titleRange,clippingRect,ETitleRef,ETitleRef);
			}
		}

	TInt borderCorr=(iGridLay->IsEncroachingCellBorders()) ? 1 : 0;
	TRangeRef range;
	clippingRect.SetRect(iMainPoint.iX,iGridRect.iTl.iY,iGridRect.iBr.iX,iMainPoint.iY);//Top right quarter
	if (aRect.Intersects(clippingRect))
		{
		clippingRect.Intersection(aRect);
		iGcPtr->SetClippingRect(clippingRect);
		range.iFrom.iCol=iGridLay->XValToColumn(clippingRect.iTl.iX);
		range.iTo.iCol=iGridLay->XValToColumn(clippingRect.iBr.iX+borderCorr);
		DrawTopGridLabelsL(range.iFrom.iCol,range.iTo.iCol);
		iGcPtr->Reset();
		if (isHorizontalTitleLine)
			{
			range.iFrom.iRow=titleRange.iFrom.iRow;
			range.iTo.iRow=titleRange.iTo.iRow;
			clippingRect.SetRect(iMainPoint.iX,iTitlePoint.iY,iGridRect.iBr.iX,iMainPoint.iY);
			clippingRect.Intersection(aRect);
			if (iGridLay->IsAutoClearGridCells())
//->
				TGridUtils::FillRect(iGcPtr,iGridLay->GridColors().iBackground,clippingRect);
//				TGridUtils::FillRect(iGcPtr,KRgbGridBackground,clippingRect);
//->
			DrawGridLinesAndCellsInRangeL(range,clippingRect,EMainRef,ETitleRef);
			}
		}

	clippingRect.SetRect(iGridRect.iTl.iX,iMainPoint.iY,iMainPoint.iX,iGridRect.iBr.iY);//Bottom left quarter
	if (aRect.Intersects(clippingRect))
		{
		clippingRect.Intersection(aRect);
		iGcPtr->SetClippingRect(clippingRect);
		range.iFrom.iRow=iGridLay->YValToRow(clippingRect.iTl.iY);
		range.iTo.iRow=iGridLay->YValToRow(clippingRect.iBr.iY+borderCorr);
		DrawSideGridLabelsL(range.iFrom.iRow,range.iTo.iRow);
		iGcPtr->Reset();
		if (isVerticalTitleLine)
			{
			range.iFrom.iCol=titleRange.iFrom.iCol;
			range.iTo.iCol=titleRange.iTo.iCol;
			clippingRect.SetRect(iTitlePoint.iX,iMainPoint.iY,iMainPoint.iX,iGridRect.iBr.iY);
			clippingRect.Intersection(aRect);
			if (iGridLay->IsAutoClearGridCells())
//->
				TGridUtils::FillRect(iGcPtr,iGridLay->GridColors().iBackground,clippingRect);
//				TGridUtils::FillRect(iGcPtr,KRgbGridBackground,clippingRect);
//->
			DrawGridLinesAndCellsInRangeL(range,clippingRect,ETitleRef,EMainRef);
			}
		}

	clippingRect.SetRect(iMainPoint,iGridRect.iBr);	//Bottom right(main) quarter of grid
	if (aRect.Intersects(clippingRect))
		{
		clippingRect.Intersection(aRect);
		range.iFrom = iGridLay->PointToCell(clippingRect.iTl);
		range.iTo = iGridLay->PointToCell(clippingRect.iBr+TPoint(borderCorr,borderCorr));
		if (iGridLay->IsAutoClearGridCells())
//->
			TGridUtils::FillRect(iGcPtr,iGridLay->GridColors().iBackground,clippingRect);
//			TGridUtils::FillRect(iGcPtr,KRgbGridBackground,clippingRect);
//->
		DrawGridLinesAndCellsInRangeL(range,clippingRect);
		}
	clippingRect=iGridRect;
	clippingRect.Intersection(aRect);
	iGcPtr->SetClippingRect(clippingRect);
	RRegion region;
	CleanupClose<RRegion>::PushL(region);
	AppendTotalHighlightRegionL(region);
	CleanupStack::Pop(2);	// region + gc cleanup
	HighlightRegion(region);
	region.Close();
	DrawVerticalTitleLine();
	DrawHorizontalTitleLine();
	iGcPtr->CancelClippingRect();
	((CGridImg*)this)->DeleteGc();
	CONST_CAST(CGridImg*,this)->DrawResizingDragHiglights(aRect);
	}

#if defined(__WINC__)
void CGridImg::BeginRedrawAndDrawL(const TRect& /*aRect*/) const
	{}	// shouldn't be called under WINC
#else

void CGridImg::BeginRedrawAndDrawL(const TRect& aRect) const
	{
	iWin->Invalidate(aRect);
	iWin->BeginRedraw(aRect);
	CleanupStack::PushL(TCleanupItem(EndRedraw,iWin));
	DrawL(iGc,aRect);
	CleanupStack::PopAndDestroy();
	}
#endif

EXPORT_C void CGridImg::PrintGridLinesAndCellsInRangeL(CGraphicsContext* aPrinterGc,const TRangeRef& aRange,
	TInt aScaleFactor) const
//
// Assumes aPrinterGc is active for drawing to
/** Prints the grid lines and cells in the specified range.

@param aPrinterGc The printer graphics context.
@param aRange The cell range.
@param aScaleFactor The scale factor. A value of: 2, scales down by a half; 
4, scales down by a quarter, etc. */
	{
	__ASSERT_DEBUG(aPrinterGc!=NULL,Panic(EGridImgInvalidGC));

	TRangeRef visRange=iGridLay->VisibleRange();
	TPoint endPoint=iGridLay->CellToPoint(visRange.iTo+TCellRef(1,1));
	TRect borderRect(iGridRect.iTl,endPoint);
	TPoint titlePoint=iTitlePoint;
	if (aScaleFactor!=EScaleOneToOne)
		{
		ScaleDown(borderRect.iTl,aScaleFactor);
		ScaleDown(borderRect.iBr,aScaleFactor);
		ScaleDown(titlePoint,aScaleFactor);
		}
	borderRect.iTl-=TPoint(1,1);
	TPoint realTlPoint=iGridLay->CellToPoint(aRange.iFrom);
	TBool doColumns=aRange.iTo.iCol>=aRange.iFrom.iCol;
	TBool doRows=aRange.iTo.iRow>=aRange.iFrom.iRow;
	TBool printBorderRect=EFalse;
	if (iGridLay->IsPrintedLabels())
		{
		TBool isSideLabels=iGridLay->IsSideLabels();
		TBool isTopLabels=iGridLay->IsTopLabels();
		if (isSideLabels && isTopLabels && aRange.iFrom==visRange.iFrom)	// i.e. is top band
			{
			TRect rect(iGridRect.iTl,iTitlePoint);
			ScaleDown(rect.iTl,aScaleFactor);
			ScaleDown(rect.iBr,aScaleFactor);
			rect.Resize(-1,-1);
//->
//			iGridLabelImg->DrawTopLeftLabelL(aPrinterGc,rect);
			iGridLabelImg->DrawTopLeftLabelL(aPrinterGc, rect, iGridLay->GridColors().iBackground);
//->
			printBorderRect=ETrue;
			}
		if (isTopLabels && doColumns)
			{
			TInt realPos=realTlPoint.iX;
			TRect line(realPos*EScaleOneToOne/aScaleFactor,borderRect.iTl.iY+1,0,titlePoint.iY-1);
			for (TInt ii=aRange.iFrom.iCol;ii<aRange.iTo.iCol;ii++)
				{
				realPos+=iGridLay->ColumnWidthInPixels(ii);
				line.iBr.iX=realPos*EScaleOneToOne/aScaleFactor-1;
				iGridLabelImg->DrawColLabelL(aPrinterGc,ii,line);
				line.iTl.iX=line.iBr.iX;
//->
			    aPrinterGc->SetPenColor(iGridLay->GridColors().iLabelSeparators);
//				aPrinterGc->SetPenColor(KRgbGridLabelSeparators);
//->
				aPrinterGc->DrawLine(line.iTl,line.iBr);
				line.iTl.iX++;
				}
			realPos+=iGridLay->ColumnWidthInPixels(aRange.iTo.iCol);
			line.iBr.iX=realPos*EScaleOneToOne/aScaleFactor-1;
			iGridLabelImg->DrawColLabelL(aPrinterGc,aRange.iTo.iCol,line);
//->
		    aPrinterGc->SetPenColor(iGridLay->GridColors().iLabelSeparators);
//			aPrinterGc->SetPenColor(KRgbGridLabelSeparators);
//->
			aPrinterGc->DrawLine(TPoint(borderRect.iTl.iX,titlePoint.iY-1),
				TPoint(borderRect.iBr.iX,titlePoint.iY-1));
			printBorderRect=ETrue;
			}
		if (isSideLabels && doRows)
			{
			TInt realPos=realTlPoint.iY;
			TRect line(borderRect.iTl.iX+1,realPos*EScaleOneToOne/aScaleFactor,titlePoint.iX-1,0);
			for (TInt ii=aRange.iFrom.iRow;ii<aRange.iTo.iRow;ii++)
				{
				realPos+=iGridLay->RowHeightInPixels(ii);
				line.iBr.iY=realPos*EScaleOneToOne/aScaleFactor-1;
				iGridLabelImg->DrawRowLabelL(aPrinterGc,ii,line);
				line.iTl.iY=line.iBr.iY;
//->
			    aPrinterGc->SetPenColor(iGridLay->GridColors().iLabelSeparators);
//				aPrinterGc->SetPenColor(KRgbGridLabelSeparators);
//->
				aPrinterGc->DrawLine(line.iTl,line.iBr);
				line.iTl.iY++;
				}
			realPos+=iGridLay->RowHeightInPixels(aRange.iTo.iRow);
			line.iBr.iY=realPos*EScaleOneToOne/aScaleFactor-1;
			iGridLabelImg->DrawRowLabelL(aPrinterGc,aRange.iTo.iRow,line);
//->
		    aPrinterGc->SetPenColor(iGridLay->GridColors().iLabelSeparators);
//			aPrinterGc->SetPenColor(KRgbGridLabelSeparators);
//->
			aPrinterGc->DrawLine(TPoint(titlePoint.iX-1,borderRect.iTl.iY),
				TPoint(titlePoint.iX-1,borderRect.iBr.iY));
			printBorderRect=ETrue;
			}
		}

	if (iGridLay->IsPrintedGridLines())
		{	
//->
//		aPrinterGc->SetPenColor(KRgbGridForeground);	// prints black not gray as on screen
		aPrinterGc->SetPenColor(iGridLay->GridColors().iForeground);	// prints black not gray as on screen
//->
		if (iGridLay->IsVerticalGridLines() && doColumns)
			{
			TInt realPos=realTlPoint.iX;
			TRect line(0,titlePoint.iY,0,borderRect.iBr.iY-1);
			for (TInt ii=aRange.iFrom.iCol;ii<aRange.iTo.iCol;ii++)
				{
				realPos+=iGridLay->ColumnWidthInPixels(ii);
				line.iTl.iX=line.iBr.iX=realPos*EScaleOneToOne/aScaleFactor-1;
				aPrinterGc->DrawLine(line.iTl,line.iBr);
				}
			printBorderRect=ETrue;
			}
		if (iGridLay->IsHorizontalGridLines() && doRows)
			{
			TInt realPos=realTlPoint.iY;
			TRect line(titlePoint.iX,0,borderRect.iBr.iX-1,0);
			for (TInt ii=aRange.iFrom.iRow;ii<aRange.iTo.iRow;ii++)
				{
				realPos+=iGridLay->RowHeightInPixels(ii);
				line.iTl.iY=line.iBr.iY=realPos*EScaleOneToOne/aScaleFactor-1;
				aPrinterGc->DrawLine(line.iTl,line.iBr);
				}
			printBorderRect=ETrue;
			}
		}
	if (printBorderRect)
		{
//->
//		aPrinterGc->SetPenColor(KRgbGridForeground);
		aPrinterGc->SetPenColor(iGridLay->GridColors().iForeground);
//->
		
		aPrinterGc->DrawRect(borderRect);
		}
	if (doRows && doColumns)
		DrawCellsToGcL(aPrinterGc,aRange,TRect(titlePoint,borderRect.iBr),realTlPoint,aScaleFactor);
	}

void CGridImg::ScaleDown(TPoint& aPoint,TInt aScaleFactor) const
	{
	aPoint.iX=aPoint.iX*EScaleOneToOne/aScaleFactor;
	aPoint.iY=aPoint.iY*EScaleOneToOne/aScaleFactor;
	}

void CGridImg::ResetGcToDefault(CGraphicsContext* aGc) const
//
// Should be called if the gc may have changed outside CGridImg since the private
// functions assume these settings.
	{
	aGc->SetPenStyle(CGraphicsContext::ESolidPen);
	aGc->SetPenSize(TSize(1,1));
	aGc->SetBrushStyle(CGraphicsContext::ENullBrush);
	}

EXPORT_C void CGridImg::SetCursorPosL(const TCellRef& aCursorPos)	
/** Sets the new position of the cursor.

This is the proposed position that the cursor would occupy after a keypress.

@param aCursorPos The cell reference of the new cursor position. */
	{
	iNewCursorPos=aCursorPos;
	if (!iGridLay->LimitCell(iNewCursorPos))
		{
		iNewCursorPos=iCursorPos;
		return;
		}
	DrawCursorOrRegionL(EIsAbsoluteMove);
	if (iCursorMoveCallBack)
		iCursorMoveCallBack->HandleCursorMoveL();
	}

EXPORT_C void CGridImg::SetAnchorPosL(const TCellRef& aAnchorPos)
/** Sets the cursor's anchor position.

Note that the cursor's anchor position is unchanged if the specified position 
lies outside the currently selected region.

@param aAnchorPos The cell reference of the cursor's anchor position. */
	{
	if (!iSelected->IsCellSelected(iAnchorPos))
		return;	//Can't have the anchor outside the selection region
	RRegion oldRegion;
	CleanupClose<RRegion>::PushL(oldRegion);
	AppendTotalHighlightRegionL(oldRegion);
	iAnchorPos=aAnchorPos;
	if (!iGridLay->LimitCell(iAnchorPos))
		{
		oldRegion.Close();
		CleanupStack::Pop();
		return;
		}
	iNewCursorPos=iCursorPos=iAnchorPos;
	HighlightNewRegionFromOldL(oldRegion);
	oldRegion.Close();
	CleanupStack::Pop();
	if (iCursorMoveCallBack)
		iCursorMoveCallBack->HandleCursorMoveL();
	}

EXPORT_C void CGridImg::MoveCursorL(TMoveDirectionAndAmount aCursorMove,TUint aSelectState)
/** Moves the cursor to the specified position.

The screen is scrolled as necessary.

@param aCursorMove Defines the direction and the amount by which the cursor 
is to be moved.
@param aSelectState Flag. If set to EIsWithSelect, then the cursor may become 
part of the selected region. */
	{
	TUint flagList=aSelectState&EIsWithSelect;	//Filters out any other components
	if (!flagList && iSelected->Count())
		iNewCursorPos = iAnchorPos;
	TCellRef oldPos=iNewCursorPos;
	TMoveDirectionAndAmount pageScroll=EMoveNone;
	TRangeRef visRange=iGridLay->VisibleRange();
	TCellRef cellToExpose=visRange.iFrom;
	TBool doExposeCol=EFalse;
	TInt relCursorPos;
	TInt amount;
	switch (aCursorMove)
		{
	case EMoveRowUp:
		iGridLay->StepRowBackward(--iNewCursorPos.iRow);
		break;
	case EMoveRowDown:
		iGridLay->StepRowForward(++iNewCursorPos.iRow);
		break;
	case EMoveColumnLeft:
		if (iGridLay->IsRowPermanentlySelected())
			{
			--cellToExpose.iCol;
			doExposeCol=ETrue;
			}
		else
			iGridLay->StepColumnBackward(--iNewCursorPos.iCol);
		break;
	case EMoveColumnRight:
		if (iGridLay->IsRowPermanentlySelected())
			{
			cellToExpose.iCol=visRange.iTo.iCol;
			if (iGridLay->IsVisibleToColumnFullyVisible() || visRange.iFrom.iCol==visRange.iTo.iCol)
				cellToExpose.iCol++;
			doExposeCol=ETrue;
			}
		else
			iGridLay->StepColumnForward(++iNewCursorPos.iCol);
		break;
	case EMovePageUp:
		relCursorPos=iGridLay->RowToYVal(visRange.iFrom.iRow,iNewCursorPos.iRow);
		pageScroll=EMovePageDown;
		amount=iGridLay->CalcVisibleFromRowAfterPageScroll(pageScroll);
		if (amount!=visRange.iFrom.iRow)
			{
			TInt newCursorRow=iGridLay->YValToNearestRow(amount,relCursorPos);
			if (newCursorRow>=iNewCursorPos.iRow)
				iGridLay->StepRowBackward(--iNewCursorPos.iRow);
			else
				iNewCursorPos.iRow=newCursorRow;
			}
		else
			iNewCursorPos.iRow=Min(visRange.iFrom.iRow,iNewCursorPos.iRow-1);
		iGridLay->LimitRowToVisible(iNewCursorPos.iRow);
		break;
	case EMovePageDown:
		relCursorPos=iGridLay->RowToYVal(visRange.iFrom.iRow,iNewCursorPos.iRow);
		pageScroll=EMovePageUp;
		amount=iGridLay->CalcVisibleFromRowAfterPageScroll(pageScroll);
		if (amount!=visRange.iFrom.iRow)
			{
			TInt newCursorRow=iGridLay->YValToNearestRow(amount,relCursorPos);
			if (newCursorRow<=iNewCursorPos.iRow)
				iGridLay->StepRowForward(++iNewCursorPos.iRow);
			else
				iNewCursorPos.iRow=newCursorRow;
			}
		else
			{
			TInt corr=iGridLay->IsVisibleToRowFullyVisible() ? 0 : 1;
			iNewCursorPos.iRow=Max(visRange.iTo.iRow-corr,iNewCursorPos.iRow+1);
			}
		break;
	case EMovePageLeft:
		relCursorPos=iGridLay->ColumnToXVal(visRange.iFrom.iCol,iNewCursorPos.iCol);
		pageScroll=EMovePageRight;
		amount=iGridLay->CalcVisibleFromColumnAfterPageScroll(pageScroll);
		if (amount!=visRange.iFrom.iCol)
			{
			TInt newCursorColumn=iGridLay->XValToNearestColumn(amount,relCursorPos);
			if (newCursorColumn>=iNewCursorPos.iCol)
				iGridLay->StepColumnBackward(--iNewCursorPos.iCol);
			else
				iNewCursorPos.iCol=newCursorColumn;
			}
		else
			iNewCursorPos.iCol=Min(visRange.iFrom.iCol,iNewCursorPos.iCol-1);
		iGridLay->LimitColumnToVisible(iNewCursorPos.iCol);
		break;
	case EMovePageRight:
		relCursorPos=iGridLay->ColumnToXVal(visRange.iFrom.iCol,iNewCursorPos.iCol);
		pageScroll=EMovePageLeft;
		amount=iGridLay->CalcVisibleFromColumnAfterPageScroll(pageScroll);
		if (amount!=visRange.iFrom.iCol)
			{
			TInt newCursorColumn=iGridLay->XValToNearestColumn(amount,relCursorPos);
			if (newCursorColumn<=iNewCursorPos.iCol)
				iGridLay->StepColumnForward(++iNewCursorPos.iCol);
			else
				iNewCursorPos.iCol=newCursorColumn;
			}
		else
			{
			TInt corr=iGridLay->IsVisibleToColumnFullyVisible() ? 0 : 1;
			iNewCursorPos.iCol=Max(visRange.iTo.iCol-corr,iNewCursorPos.iCol+1);
			}
		break;
	case EMoveRowStart:
	case EMoveColumnStart:
	case EMoveHome:
		if (aCursorMove!=EMoveColumnStart)
			{
			if (iGridLay->IsRowPermanentlySelected())
				{
				cellToExpose.iCol=iGridLay->MinVisibleFromColumn();
				doExposeCol=ETrue;
				}
			else
				{
				iNewCursorPos.iCol=iGridLay->MinVisibleFromColumn();
				iGridLay->StepColumnForward(iNewCursorPos.iCol);
				}
			}
		if (aCursorMove!=EMoveRowStart)
			{
			iNewCursorPos.iRow=(iGridLay->IsIndefiniteRowBoundaries())
				? -KMaxTInt : iGridLay->MinVisibleFromRow();
			iGridLay->StepRowForward(iNewCursorPos.iRow);
			}
		break;
	case EMoveRowEnd:
	case EMoveColumnEnd:
	case EMoveEnd:
		{
		TCellRef fromCell=iGridLay->GridRange().iFrom;
		if (aCursorMove!=EMoveColumnEnd)
			{
			TInt lastCol=fromCell.iCol+iGridLay->ColumnExtent()-1;
			if (iGridLay->IsRowPermanentlySelected())
				{
				cellToExpose.iCol=lastCol;
				doExposeCol=ETrue;
				}
			else
				{
				iNewCursorPos.iCol=lastCol;
				iGridLay->StepColumnBackward(iNewCursorPos.iCol);
				}
			}
		if (aCursorMove!=EMoveRowEnd)
			{
			iNewCursorPos.iRow=(iGridLay->IsIndefiniteRowBoundaries())
				? KMaxTInt : fromCell.iRow+iGridLay->RowExtent()-1;
			iGridLay->StepRowBackward(iNewCursorPos.iRow);
			}
		}
		break;
	default:
		break;
		}
	iGridLay->LimitCell(iNewCursorPos);
	if (oldPos==iNewCursorPos)
		flagList|=EIsAtBoundary;
	oldPos=iNewCursorPos;
	DrawCursorOrRegionL(flagList);
	TPoint offset;
	if (pageScroll!=EMoveNone)
		offset=iGridLay->PageScroll(pageScroll);
	cellToExpose.iRow=iCursorPos.iRow;
	if (!doExposeCol)
		cellToExpose.iCol=iCursorPos.iCol;
	if (iGridLay->IsCellOutOfVisibleRange(cellToExpose))
		{
		visRange=iGridLay->VisibleRange();
		visRange.iTo.Offset(-1,-1);
		iGridLay->StepRowBackward(visRange.iTo.iRow);
		iGridLay->StepColumnBackward(visRange.iTo.iCol);
		if (iSelected->IsColSelectedLastIndex(cellToExpose.iCol) && 
			!iGridLay->IsColumnSelectionDisabled())
			{
			cellToExpose.iRow=visRange.iFrom.iRow;
			}
		if ((iSelected->IsRowSelectedLastIndex(cellToExpose.iRow) || iGridLay->IsRowPermanentlySelected())
			&& !doExposeCol && !iGridLay->IsRowSelectionDisabled())
			{
			cellToExpose.iCol=visRange.iFrom.iCol;
			}
		offset+=iGridLay->ExposeCell(cellToExpose);
		}
	ScrollL(offset);
	if (iCursorMoveCallBack)
		iCursorMoveCallBack->HandleCursorMoveL();
	}

EXPORT_C void CGridImg::SetCursorWithPointerL(const TPoint &aPoint,TUint aFlagList)
/** Moves the cursor to an absolute position.

@param aPoint The absolute position.
@param aFlagList Flag. Can be set to EIsWithDrag. */
	{
	TRangeRef visRange(iGridLay->VisibleRange());
	TCellRef cellToExpose = visRange.iFrom;
	if (iGridLay->IsVerticalTitleLine())
		{
		if (aPoint.iX<iMainPoint.iX)
			{
			if (!(aFlagList&EIsWithDrag))
		 		iXRefPoint=ETitleRef;
			}
		else
			{
			if (iXRefPoint==ETitleRef && !iSelected->IsRowSelectedLastIndex(iCursorPos.iRow)
				&& (aFlagList&EIsWithDrag))
				{
				cellToExpose.iCol=iGridLay->TitleRange().iTo.iCol;
				}
			iXRefPoint=EMainRef;
			}
		}
	else
		iXRefPoint=EMainRef;
	if (iGridLay->IsHorizontalTitleLine())
		{
		if (aPoint.iY<iMainPoint.iY)
			{
			if (!(aFlagList&EIsWithDrag))
				iYRefPoint=ETitleRef;
			}
		else
			{
			if (iYRefPoint==ETitleRef && !iSelected->IsColSelectedLastIndex(iCursorPos.iCol)
				&& (aFlagList&EIsWithDrag))
				{
				cellToExpose.iRow=iGridLay->TitleRange().iTo.iRow;
				}
			iYRefPoint=EMainRef;
			}
		}
	else
		iYRefPoint=EMainRef;
	TPoint offset=iGridLay->ExposeCellToTopLeft(cellToExpose);
	ScrollL(offset);

	if (aPoint.iY<iTitlePoint.iY)
		{
		if (iDragFlags&EIsLabelDraggingIgnored && aFlagList&EIsWithDrag)
			return;
		if (!(aFlagList&EIsWithDrag) || iSelected->IsColSelectedLastIndex(iCursorPos.iCol))
			{
			if (iGridLay->IsColumnSelectionDisabled())
				{
				iDragFlags|=EIsLabelDraggingIgnored;
				return;
				}
			aFlagList|=EIsColumnSelected;
			iDragFlags=iDragFlags&~EIsLabelDraggingIgnored;
			}
		}
	if (aPoint.iX<iTitlePoint.iX)
		{
		if (iDragFlags&EIsLabelDraggingIgnored && aFlagList&EIsWithDrag)
			return;
		if (!(aFlagList&EIsWithDrag) ||	iSelected->IsRowSelectedLastIndex(iCursorPos.iRow))
			{
			if (iGridLay->IsRowPermanentlySelected() && !(aFlagList&EIsWithDrag))
				iDragFlags|=EIsSidewaysScrollIgnored;
			else if (iGridLay->IsRowSelectionDisabled())
				{
				iDragFlags|=EIsLabelDraggingIgnored;
				return;
				}
			else
				aFlagList|=EIsRowSelected;
			iDragFlags=iDragFlags&~EIsLabelDraggingIgnored;
			}
		}
	else
		{
		iDragFlags=iDragFlags&~EIsSidewaysScrollIgnored;
		if (aPoint.iY>=iTitlePoint.iY)		//ie not on the labels
			iDragFlags=iDragFlags&~EIsLabelDraggingIgnored;
		}
	iNewCursorPos=RelativePointToCell(aPoint,iXRefPoint,iYRefPoint);	
	iGridLay->LimitCell(iNewCursorPos);
	if (iCursorPos==iNewCursorPos && !iSelected->Count() && 
		!(aFlagList&(EIsRowSelected|EIsColumnSelected|EIsWithControl)))
		{
		return;	// Don't need to do anything in this case
		}

	cellToExpose = iNewCursorPos;
	if (iSelected->IsColSelectedLastIndex(iCursorPos.iCol) && (aFlagList&EIsWithDrag))
		cellToExpose.iRow = visRange.iFrom.iRow;
	if ((iSelected->IsRowSelectedLastIndex(iCursorPos.iRow) && (aFlagList&EIsWithDrag)
		&& !iGridLay->IsRowPermanentlySelected()) || iDragFlags&EIsSidewaysScrollIgnored)
		{
		cellToExpose.iCol = visRange.iFrom.iCol;
		}
	TBool expose = EFalse;
	if (aFlagList&EIsWithDrag)
		{
		if ((aPoint.iX<iMainPoint.iX && iXRefPoint==EMainRef) || aPoint.iX>iGridRect.iBr.iX)
			expose=ETrue;
		else
			cellToExpose.iCol=visRange.iFrom.iCol;
		if ((aPoint.iY<iMainPoint.iY && iYRefPoint==EMainRef) || aPoint.iY>iGridRect.iBr.iY)
			expose=ETrue;
		else
			cellToExpose.iRow=visRange.iFrom.iRow;
		}

	aFlagList|=EIsAbsoluteMove;
	DrawCursorOrRegionL(aFlagList);
	if (expose)
		{
		offset=iGridLay->ExposeCell(cellToExpose);
		ScrollL(offset);
		}
	if (iCursorMoveCallBack)
		iCursorMoveCallBack->HandleCursorMoveL();
	}

EXPORT_C void CGridImg::ResetSelectedL()
/** Clears the selected region. */
	{
	if (!iSelected->Count())
		return;
	RRegion oldRegion;
	CleanupClose<RRegion>::PushL(oldRegion);
	AppendTotalHighlightRegionL(oldRegion);
	iNewCursorPos=iCursorPos=iAnchorPos;
	iSelected->Reset();
	HighlightNewRegionFromOldL(oldRegion);
	oldRegion.Close();
	CleanupStack::Pop();
	if (iCursorMoveCallBack)
		iCursorMoveCallBack->HandleCursorMoveL();
	}

EXPORT_C void CGridImg::AddRangeToSelectedL(const TRangeRef& aRange,TSelectType aType)
/** Adds the specified range to, or replaces, the currently selected region.

The range can be added to the existing selected region or it can replace the 
existing selected region.

@param aRange The range to be added.
@param aType Indicates whether the existing selected region is to be reset 
(i.e. emptied) before adding the new range. */
	{
	RRegion oldRegion;
	CleanupClose<RRegion>::PushL(oldRegion);
	AppendTotalHighlightRegionL(oldRegion);
	if (aType==ESelectOverwrite)
		iSelected->Reset();
	iNewCursorPos=iCursorPos=aRange.iTo;
	iAnchorPos=aRange.iFrom;
	iSelected->AddCellRangeL(aRange);
	HighlightNewRegionFromOldL(oldRegion);
	oldRegion.Close();
	CleanupStack::Pop();
	if (iCursorMoveCallBack)
		iCursorMoveCallBack->HandleCursorMoveL();
	}

EXPORT_C void CGridImg::AddRegionToSelectedL(const CArrayFix<TRangeRef>* aCellRegion,TSelectType aType)
/** Adds the specified region to, or replaces, the currently selected region.

The region can be added to the existing selected region, or it can replace 
the existing selected region.

@param aCellRegion A set of ranges that form the region to be added.
@param aType Indicates whether the existing selected region is to be reset 
(i.e. emptied) before adding the new region. */
	{
	RRegion oldRegion;
	CleanupClose<RRegion>::PushL(oldRegion);
	AppendTotalHighlightRegionL(oldRegion);
	if (aType==ESelectOverwrite)
		iSelected->Reset();
	TInt count=aCellRegion->Count();
	if (!count)
		iNewCursorPos=iCursorPos=iAnchorPos=iGridLay->GridRange().iFrom;
	else
		{
		TRangeRef lastRange=(*aCellRegion)[count-1];
		iNewCursorPos=iCursorPos=lastRange.iTo;
		iAnchorPos=lastRange.iFrom;
		for (TInt ii=0;ii<count;ii++)
			iSelected->AddCellRangeL((*aCellRegion)[ii]);
		}
	HighlightNewRegionFromOldL(oldRegion);
	oldRegion.Close();
	CleanupStack::Pop();
	if (iCursorMoveCallBack)
		iCursorMoveCallBack->HandleCursorMoveL();
	}

EXPORT_C void CGridImg::AddRowToSelectedL(TInt aRow,TSelectType aType)
/** Adds a row to, or replaces, the currently selected region.

The row can be added to the existing selected region, or it can replace the 
existing selected region.

@param aRow The row to be added.
@param aType Indicates whether the existing selected region is to be reset 
(i.e. emptied) before adding the new region. */
	{
	RRegion oldRegion;
	CleanupClose<RRegion>::PushL(oldRegion);
	AppendTotalHighlightRegionL(oldRegion);
	if (aType==ESelectOverwrite)
		iSelected->Reset();
	iAnchorPos.iRow=iCursorPos.iRow=iNewCursorPos.iRow=aRow;
	iAnchorPos.iCol=iGridLay->VisibleRange().iFrom.iCol;
	iNewCursorPos.iCol=iCursorPos.iCol=iGridLay->GridRange().iTo.iCol;
	iSelected->AddRowL(aRow);
	HighlightNewRegionFromOldL(oldRegion);
	oldRegion.Close();
	CleanupStack::Pop();
	if (iCursorMoveCallBack)
		iCursorMoveCallBack->HandleCursorMoveL();
	}

EXPORT_C void CGridImg::AddColToSelectedL(TInt aCol,TSelectType aType)
/** Adds a column to, or replaces, the currently selected region.

The column can be added to the existing selected region, or it can replace 
the existing selected region.

@param aCol The column to be added.
@param aType Indicates whether the existing selected region is to be reset 
(i.e. emptied) before adding the new region. */
	{
	RRegion oldRegion;
	CleanupClose<RRegion>::PushL(oldRegion);
	AppendTotalHighlightRegionL(oldRegion);
	if (aType==ESelectOverwrite)
		iSelected->Reset();
	iAnchorPos.iCol=iCursorPos.iCol=iNewCursorPos.iCol=aCol;
	iAnchorPos.iRow=iGridLay->VisibleRange().iFrom.iRow;
	iNewCursorPos.iRow=iCursorPos.iRow=iGridLay->GridRange().iTo.iRow;
	iSelected->AddColL(aCol);
	HighlightNewRegionFromOldL(oldRegion);
	oldRegion.Close();
	CleanupStack::Pop();
	if (iCursorMoveCallBack)
		iCursorMoveCallBack->HandleCursorMoveL();
	}

void CGridImg::HighlightNewRegionFromOldL(const TRegion& aOldRegion)
//
// returns ETrue if there's an error
	{
	RRegion newRegion;
	CleanupClose<RRegion>::PushL(newRegion);
	AppendTotalHighlightRegionL(newRegion);
	HighlightMinRegionL(aOldRegion,newRegion);
	CleanupStack::Pop();
	newRegion.Close();
	}

EXPORT_C void CGridImg::CheckSideLabelWidthAndScrollL()
/** Checks the side label width and, if changed, scrolls the screen. */
	{
	TInt offset=CheckSideLabelWidth();
#if !defined(__WINC__)
	if (offset)
		{
		TRect rect(iGridRect.iTl.iX,iGridRect.iTl.iY,iTitlePoint.iX-1,iGridRect.iBr.iY);
		iWin->Scroll(iGridRect,TPoint(offset,0));
		BeginRedrawAndDrawL(rect);
		if (offset<0)
			{
			rect.SetRect(iGridRect.iBr.iX+offset,iGridRect.iTl.iY,iGridRect.iBr.iX,iGridRect.iBr.iY);
			BeginRedrawAndDrawL(rect);
			}
		}
#endif
	}

EXPORT_C TInt CGridImg::CheckSideLabelWidth()
/** Checks whether there has been a change in the width of the side label.

@return The difference between the new width and the old width (new width 
- old width). */
	{
	if (iGridLay->IsSideLabels())
		{
		TInt oldWidth=iTitlePoint.iX-iGridRect.iTl.iX;
		TInt newWidth=SideLabelWidthInPixels();
		if (oldWidth!=newWidth)
			{
			ResetReferencePoints();
			iGridLay->ResetVisibleToCell();
			return (newWidth-oldWidth);
			}
		}
	return 0;
	}

EXPORT_C TInt CGridImg::SideLabelWidthInPixels() const
/** Gets the width of the side label.

@return The width of the side label, in pixels. */
	{
	if (iGridLabelImg==NULL)
		return 0;
	TRangeRef visRange=iGridLay->VisibleRange();
	if (!iGridLay->LimitRow(visRange.iFrom.iRow))
		return 0;
	return iGridLabelImg->SideLabelWidthInPixels(visRange.iFrom.iRow,visRange.iTo.iRow);
	}

EXPORT_C TInt CGridImg::MaxSideLabelWidthInPixels() const
/** Gets the maximum width of the side label.

@return The maximum width of the side label, in pixels. */
	{
	if (iGridLabelImg==NULL)
		return 0;
	TInt firstRow;
	if (!iGridLay->RequestRow(-KMaxTInt,firstRow))
		return 0;
	return iGridLabelImg->SideLabelWidthInPixels(firstRow,firstRow+iGridLay->RowExtent()-1);
	}

EXPORT_C TInt CGridImg::TopLabelHeightInPixels() const
/** Gets the height of the top labels.

@return The height of the top labels, in pixels. */
	{
	if (iGridLabelImg==NULL)
		return 0;
	return iGridLabelImg->TopLabelHeightInPixels();
	}

#if defined(__WINC__)

// All these functions are inappropriate under WINC
EXPORT_C void CGridImg::FinishLabelDragL()
	{}

EXPORT_C TBool CGridImg::StartLabelDrag(const TPoint& /*aPoint*/)
	{ return EFalse; }

TBool CGridImg::ScanColumnsForDrag(TInt /*aFromColumn*/,TInt /*aToColumn*/,TInt /*aPointerPos*/,TInt& /*aPrevious*/,TInt& /*aCurrent*/)
	{ return EFalse; }

TBool CGridImg::ScanRowsForDrag(TInt /*aFromRow*/,TInt /*aToRow*/,TInt /*aPointerPos*/,TInt& /*aPrevious*/,TInt& /*aCurrent*/)
	{ return EFalse; }

EXPORT_C TBool CGridImg::UpdateLabelDrag(const TPoint& /*aPoint*/)
	{ return EFalse; }

void CGridImg::DrawArrowsToInMemoryBitmap(TArrows /*aArrows*/)
	{}

void CGridImg::DrawDraggingHighlight(const TRect /*aLine*/,TDragDraw /*aDragDraw*/)
	{}

EXPORT_C void CGridImg::ScrollL(const TPoint& /*aOffset*/)
	{}
#else

EXPORT_C void CGridImg::FinishLabelDragL()
/** Deals with the end of a drag operation.

Typically, the function is called whan handling a pointer event in a control.

The function removes the dotted drag line indicating a drag operation, and, 
if necessary, updates the column width/row height, and then scrolls and redraws 
the necessary regions.

@see StartLabelDrag() */
	{	   
	//
	// Erases the two dotted drag lines if necessary, updates the column/row width/height then scrolls
	// and redraws the necessary regions. The relevant member variables are also set to zero.
	//
	if (iDragDim == ENoDrag)
		return;
	TRect line1 = iGridRect;
	TRect line2 = iGridRect;
	TInt oldValue;
	TInt prevDragPos;
	TRangeRef titleRange=iGridLay->TitleRange();
	if (iDragDim == EXDrag)
		{
		prevDragPos = ((iGridLay->IsVerticalTitleLine() && iDragLabel<=titleRange.iTo.iCol)
			? iGridLay->TitleColumnToXVal(iDragLabel) : iGridLay->ColumnToXVal(iDragLabel))-1;
		line1.iTl.iX = line1.iBr.iX = prevDragPos;
		line2.iTl.iX = line2.iBr.iX = iCurrentDragPos;
		oldValue = iGridLay->ColumnWidthInPixels(iDragLabel);
		}
	else
		{
		prevDragPos = ((iGridLay->IsHorizontalTitleLine() && iDragLabel<=titleRange.iTo.iRow)
			? iGridLay->TitleRowToYVal(iDragLabel) : iGridLay->RowToYVal(iDragLabel))-1;
		line1.iTl.iY = line1.iBr.iY = prevDragPos;
		line2.iTl.iY = line2.iBr.iY = iCurrentDragPos;
		oldValue = iGridLay->RowHeightInPixels(iDragLabel);
		}
	CreateGc(iGc);
	iGc->SetClippingRect(iGridRect);
	DrawDraggingHighlight(line1,EDragDrawWithoutBitmap);
	DrawDraggingHighlight(line2,EDragDrawWithBitmap);
	delete iDragBmp;
	iDragBmp=NULL;
	DeleteGc();
	iCurrentDragPos = Max(iCurrentDragPos,prevDragPos);
	TInt newValue = iCurrentDragPos-prevDragPos;
	TInt minValue=(iDragDim==EXDrag) ? iGridLay->MinColumnWidthInPixels() : iGridLay->MinRowHeightInPixels();
	newValue=Max(newValue,minValue);
	if (oldValue!=newValue)
		{
		TRect validRect=iGridRect;
		TRect scrollRect=iGridRect;
		TPoint offset;
		TBool doScroll=EFalse;
		TBool newPagination=EFalse;
		TBool clearPagination=EFalse;
		if (iGridLay->IsPaginated())
			{
			if (!iGridLay->IsAutoPagination())
				clearPagination=ETrue;
			newPagination=ETrue;
			}
		if (iDragDim==EXDrag)
			{
			if (iGridLay->IsUniformColumnWidth() || (iSelected->IsRangeSelected(iGridLay->GridRange())
				&& !iGridLay->IsColumnSelectionDisabled()))
				{
				if (newValue==0)
					goto DragEnd;
				validRect.iTl.iX=iTitlePoint.iX;
				iGridLay->SetDefaultColumnWidthInPixels(newValue);
				iGridLay->SetColumnWidthsToDefault();
				}
			else if (iSelected->IsColSelected(iDragLabel) && !iGridLay->IsColumnSelectionDisabled())
				{
				validRect.iTl.iX=iTitlePoint.iX;
				TInt count=iSelected->Count();
				for (TInt ii=0;ii<count;ii++)
					{
					TRangeRef range=(*iSelected)[ii];
					if (iSelected->IsColSelected(range.iFrom.iCol,ii))
						{
						if ((range.iTo.iCol-range.iFrom.iCol)>CGridLay::EMaxArrayChanges)
							continue;
						for (;range.iFrom.iCol<=range.iTo.iCol;range.iFrom.iCol++)
							iGridLay->SetColumnWidthInPixelsL(range.iFrom.iCol,newValue);
						}
					}
				}
			else
				{
				validRect.iTl.iX = (clearPagination) ? iTitlePoint.iX :
					Max(prevDragPos-1,iTitlePoint.iX);
				if (!iGridLay->IsColumnBursting() && !newPagination)
					{
					doScroll=ETrue;
					validRect.iBr.iX = iCurrentDragPos+2;
					scrollRect.iTl.iX=Max(Min(prevDragPos+oldValue+2,iCurrentDragPos+1),iTitlePoint.iX);
					offset.iX = newValue-oldValue;
					}
				iGridLay->SetColumnWidthInPixelsL(iDragLabel,newValue);
				}
			}
		else
			{
			if (iGridLay->IsUniformRowHeight() || (iSelected->IsRangeSelected(iGridLay->GridRange())
				&& !iGridLay->IsRowSelectionDisabled()))
				{
				if (newValue==0)
					goto DragEnd;
				validRect.iTl.iY=iTitlePoint.iY;
				iGridLay->SetDefaultRowHeightInPixels(newValue);
				iGridLay->SetRowHeightsToDefault();
				}
			else if (iSelected->IsRowSelected(iDragLabel) && !iGridLay->IsRowSelectionDisabled())
				{
				validRect.iTl.iY=iTitlePoint.iY;
				TInt count=iSelected->Count();
				for (TInt ii=0;ii<count;ii++)
					{
					TRangeRef range=(*iSelected)[ii];
					if (iSelected->IsRowSelected(range.iFrom.iRow,ii))
						{
						if ((range.iTo.iRow-range.iFrom.iRow)>CGridLay::EMaxArrayChanges)
							continue;
						for (;range.iFrom.iRow<=range.iTo.iRow;range.iFrom.iRow++)
							iGridLay->SetRowHeightInPixelsL(range.iFrom.iRow,newValue);
						}
					}
				}
			else
				{
				validRect.iTl.iY = (clearPagination) ? iTitlePoint.iY :
					Max(prevDragPos-1,iTitlePoint.iY);
				if (!newPagination)
					{
					doScroll=ETrue;
					validRect.iBr.iY = iCurrentDragPos+2;
					scrollRect.iTl.iY=Max(Min(prevDragPos+oldValue+2,iCurrentDragPos+1),iTitlePoint.iY);
					offset.iY = newValue-oldValue;
					}
				iGridLay->SetRowHeightInPixelsL(iDragLabel,newValue);
				}
			}
		iGridLay->NotifyPaginationOutOfDateL();
		if (doScroll)
	   		iWin->Scroll(scrollRect,offset);
		validRect.Intersection(iGridRect);
		BeginRedrawAndDrawL(validRect);
		if ((offset.iX<0 && !iGridLay->IsColumnBursting()) || offset.iY<0)
			{
			if (offset.iX<0)
				{
				validRect.iBr.iX = iGridRect.iBr.iX;
				validRect.iTl.iX = validRect.iBr.iX+offset.iX;
				}
			else
				{
				validRect.iBr.iY = iGridRect.iBr.iY;
				validRect.iTl.iY = validRect.iBr.iY+offset.iY;
				}
			BeginRedrawAndDrawL(validRect);
			}
		CheckSideLabelWidthAndScrollL();
		if (!newValue && !iSelected->Count())
			{
			if (iDragDim==EXDrag)
				{
				if (iDragLabel==iCursorPos.iCol)
					MoveCursorL(EMoveColumnRight,!EIsWithSelect);	//2nd param=0
				}
			else
				{
				if (iDragLabel==iCursorPos.iRow)
					MoveCursorL(EMoveRowDown,!EIsWithSelect);
				}
			}
		}
DragEnd:
	iCurrentDragPos = iDragLabel = iDragDiff = 0;
	iDragDim = ENoDrag;
	}

EXPORT_C TBool CGridImg::StartLabelResize(TBool aIsColumnLabel, TInt aIndex)
/** Begins the resizing of a column or a row.

@param aIsColumnLabel Indicates whether a column or row is to be resized: 
specify ETrue for a column; specify EFalse for a row.
@param aIndex Identifes the row or column to be resized. This value increases 
from left to right for a column, and from top to bottom for a row.
@return True, if resizing has begun; false otherwise. */
	{
	TInt widthOrHeight=0;
	TRect line1 = iGridRect;
	TRect line2 = iGridRect;
	TRangeRef visibleRange=iGridLay->VisibleRange();
	iDragDim=ENoDrag;
	if(aIsColumnLabel && aIndex>=visibleRange.iFrom.iCol && aIndex<visibleRange.iTo.iCol 
		&& !iGridLay->IsTopLabelDragDisabled())
		{
		iDragLabel=aIndex;
		iDragDim = EXDrag;
		line1.iTl.iX=line1.iBr.iX=iGridLay->ColumnToXVal(aIndex)-1;
		widthOrHeight=iGridLay->ColumnWidthInPixels(aIndex);
		iCurrentDragPos=line2.iTl.iX=line2.iBr.iX=line1.iTl.iX+widthOrHeight;
		}
	else if(!aIsColumnLabel && aIndex>=visibleRange.iFrom.iRow && 
		aIndex<visibleRange.iTo.iRow && !iGridLay->IsSideLabelDragDisabled())
		{
		iDragLabel=aIndex;
		iDragDim = EYDrag;
		line1.iTl.iY=line1.iBr.iY=iGridLay->RowToYVal(aIndex)-1;
		widthOrHeight=iGridLay->RowHeightInPixels(aIndex);
		iCurrentDragPos=line2.iTl.iY=line2.iBr.iY=line1.iTl.iY+widthOrHeight;
		}
	if(iDragDim!=ENoDrag)
		{
		TArrows arrows=(widthOrHeight==0? ESecondArrowOnly : EBothArrows);
		DrawArrowsToInMemoryBitmap(arrows);
		TRect invalid = TRect(line1.iTl,line2.iBr);
		if(iDragDim==EXDrag)
			{
			invalid.iTl.iX-=2;
			invalid.iBr.iX+=KArrowLength+KArrowSeparation;
			}
		else
			{
			invalid.iTl.iY-=2;
			invalid.iBr.iY+=KArrowLength+KArrowSeparation;
			}
		iWin->Invalidate(invalid);
		iDrawResizeLines=ETrue;
		return ETrue;
		}
	else
		return EFalse;
	}

void CGridImg::DrawResizingDragHiglights(const TRect& aRect)
	{
	if(iDrawResizeLines)
		{
		TRect line1 = iGridRect;
		TRect line2 = iGridRect;
		if(iDragDim==EXDrag)
			{
			line1.iTl.iX=line1.iBr.iX=iGridLay->ColumnToXVal(iDragLabel)-1;
			line2.iTl.iX=line2.iBr.iX=iCurrentDragPos;
			}
		else if(iDragDim==EYDrag)
			{
			line1.iTl.iY=line1.iBr.iY=iGridLay->RowToYVal(iDragLabel)-1;
			line2.iTl.iY=line2.iBr.iY=iCurrentDragPos;
			}
		CreateGc(iGc);
		TRect clip=aRect;
		clip.Intersection(iGridRect);
		iGc->SetClippingRect(clip);
		DrawDraggingHighlight(line1,EDragDrawWithoutBitmap);
		DrawDraggingHighlight(line2,EDragDrawWithBitmap);
		DeleteGc();
		}
	}

EXPORT_C TBool CGridImg::UpdateLabelResize(TInt aDelta)
/** Changes the size of the row or column currently being resized.

@param aDelta The amount, in pixels, by which the size of the row or column 
is being changed.
@return True, if a row or column is being resized; false, otherwise. */
	{
	if(iDragDim==ENoDrag)
		return EFalse;
	TRect line1 = iGridRect;
	TRect line2 = iGridRect;
	if (iDragDim == EXDrag)
		{
		TInt left=iGridLay->ColumnToXVal(iDragLabel);
		line1.iTl.iX = line1.iBr.iX = iCurrentDragPos;
		line2.iTl.iX = line2.iBr.iX = iCurrentDragPos =
			Max(left,Min(iCurrentDragPos+aDelta,iGridRect.iBr.iX));
		}
	else
		{
		TInt top=iGridLay->RowToYVal(iDragLabel);
		line1.iTl.iY = line1.iBr.iY = iCurrentDragPos;
		line2.iTl.iY = line2.iBr.iY = iCurrentDragPos =
			Max(top,Min(iCurrentDragPos+aDelta,iGridRect.iBr.iY));
		}
	if (line1!=line2)
		{
		CreateGc(iGc);
		iGc->SetClippingRect(iGridRect);
		DrawDraggingHighlight(line1,EDragDrawWithBitmap);
		DrawDraggingHighlight(line2,EDragDrawWithBitmap);
		DeleteGc();
		}
	return ETrue;
	}

EXPORT_C void CGridImg::FinishLabelResizeL(TBool aResize)
/** Completes the resizing of a row or column.

@param aResize ETrue, to complete the resizing of the row or column; EFalse, 
if the row or column is to retain its original size. */
	{
	iDrawResizeLines=EFalse;
	if(iDragDim!=ENoDrag && aResize)
		{
		FinishLabelDragL();
		}
	else if (iDragDim!=ENoDrag && !aResize)
		{
		TRect line1 = iGridRect;
		TRect line2 = iGridRect;
		if (iDragDim == EXDrag)
			{
			line1.iTl.iX = line1.iBr.iX = iCurrentDragPos;
			line2.iTl.iX = line2.iBr.iX = iGridLay->ColumnToXVal(iDragLabel)-1;
			}
		else
			{
			line1.iTl.iY = line1.iBr.iY = iCurrentDragPos;
			line2.iTl.iY = line2.iBr.iY = iGridLay->RowToYVal(iDragLabel)-1;
			}
		CreateGc(iGc);
		iGc->SetClippingRect(iGridRect);
		DrawDraggingHighlight(line1,EDragDrawWithBitmap);
		DrawDraggingHighlight(line2,EDragDrawWithoutBitmap);
		DeleteGc();
		}
	}

EXPORT_C TBool CGridImg::StartLabelDrag(const TPoint& aPoint)
/** Deals with the start of a drag operation.

Typically, the function is called whan handling a pointer event in a control.

The function checks that the pointer event is within 10 pixels of the boundary 
between label cells, and draws a dotted line along the row or column boundary 
together with pairs of arrows on either side of that line, and prepares for 
the continuation or end of a drag operation on the boundary separating a row 
or a column (to expand or contract that row or column).

The dotted line is a visual indication that a drag operation is in progress.

@param aPoint The position of the pointer event.
@return True, if the pointer event marks the start of a drag operation, and 
dragging is permitted; false otherwise. */
	{
	TBool action = EFalse;
	TRect line1 = iGridRect;
	TRect line2 = iGridRect;
	TRangeRef titleRange=iGridLay->TitleRange();
	TRangeRef visibleRange=iGridLay->VisibleRange();
	TArrows arrows = EBothArrows;
	if (aPoint.iY<iTitlePoint.iY-1 && !iGridLay->IsTopLabelDragDisabled())
		{
		TInt previous = iTitlePoint.iX-1;
        TInt current=0;
		if (iGridLay->IsVerticalTitleLine())
			action = ScanColumnsForDrag(titleRange.iFrom.iCol,titleRange.iTo.iCol,aPoint.iX,previous,current);
		if (!action)
			action = ScanColumnsForDrag(visibleRange.iFrom.iCol,visibleRange.iTo.iCol,aPoint.iX,previous,current);
		if (action)
			{
			line1.iTl.iX = line1.iBr.iX = previous;
			line2.iTl.iX = line2.iBr.iX = iCurrentDragPos = current;
			if (previous==current)
				arrows=ESecondArrowOnly;
			iDragDiff = aPoint.iX - current;
			iDragDim = EXDrag;
			}
		}
	else if (aPoint.iX<iTitlePoint.iX-1 && !iGridLay->IsSideLabelDragDisabled())
		{
		TInt previous = iTitlePoint.iY-1;
		TInt current=0;
		if (iGridLay->IsHorizontalTitleLine())
			action = ScanRowsForDrag(titleRange.iFrom.iRow,titleRange.iTo.iRow,aPoint.iY,previous,current);
		if (!action)
			action = ScanRowsForDrag(visibleRange.iFrom.iRow,visibleRange.iTo.iRow,aPoint.iY,previous,current);
		if (action)
			{
			line1.iTl.iY = line1.iBr.iY = previous;
			line2.iTl.iY = line2.iBr.iY = iCurrentDragPos = current;
			if (previous==current)
				arrows=ESecondArrowOnly;
			iDragDiff = aPoint.iY - current;
			iDragDim = EYDrag;
			}
		}
	if (action)
		{
		DrawArrowsToInMemoryBitmap(arrows);
		CreateGc(iGc);
		iGc->SetClippingRect(iGridRect);
		DrawDraggingHighlight(line1,EDragDrawWithoutBitmap);
		DrawDraggingHighlight(line2,EDragDrawWithBitmap);
		DeleteGc();
		}
	return action;
	}

const TInt KDragFactor = 5;
const TInt KMaxPenToLabel = 10;
const TInt KMinDraggingLength = 10;

TBool CGridImg::ScanColumnsForDrag(TInt aFromColumn,TInt aToColumn,TInt aPointerPos,TInt& aPrevious,TInt& aCurrent)
	{
	TInt ii=aFromColumn;
	if (!iGridLay->ColumnWidthInPixels(ii-1))
		--ii;
	TInt width=iGridLay->ColumnWidthInPixels(ii++);
	aCurrent=aPrevious+width;
	TInt currentPenToLabel=(width>=KMinDraggingLength) ? Min(width/KDragFactor,(TInt)KMaxPenToLabel) : 0;
	for (;ii<=aToColumn && aCurrent<iGridRect.iBr.iX;ii++)
		{
		iGridLay->StepColumnForward(ii);
		width=iGridLay->ColumnWidthInPixels(ii);
		TInt next=aCurrent+width;
		TInt nextPenToLabel=(width>=KMinDraggingLength) ? Min(width/KDragFactor,(TInt)KMaxPenToLabel) : 0;
		if (aPointerPos>aCurrent-currentPenToLabel && aPointerPos>Min(aPrevious+currentPenToLabel,aCurrent-1)
			&& aPointerPos<aCurrent+nextPenToLabel && aPointerPos<Max(next-nextPenToLabel,aCurrent))
			{
			iDragLabel=ii-1;
			if (aPointerPos<aCurrent)
				iGridLay->StepColumnBackward(iDragLabel);
			else if (iGridLay->ColumnWidthInPixels(iDragLabel)==0)
				aPrevious=aCurrent;	// reopen zero width column
			return ETrue;
			}
		aPrevious=aCurrent;
		aCurrent=next;
		currentPenToLabel=nextPenToLabel;
		}
	return EFalse;
	}

TBool CGridImg::ScanRowsForDrag(TInt aFromRow,TInt aToRow,TInt aPointerPos,TInt& aPrevious,TInt& aCurrent)
	{
	TInt ii=aFromRow;
	if (!iGridLay->RowHeightInPixels(ii-1))
		--ii;
	TInt height=iGridLay->RowHeightInPixels(ii++);
	aCurrent=aPrevious+height;
	TInt currentPenToLabel=(height>=KMinDraggingLength) ? Min(height/KDragFactor,(TInt)KMaxPenToLabel) : 0;
	for (;ii<=aToRow && aCurrent<iGridRect.iBr.iY;ii++)
		{
		iGridLay->StepRowForward(ii);
		height=iGridLay->RowHeightInPixels(ii);
		TInt next=aCurrent+height;
		TInt nextPenToLabel=(height>=KMinDraggingLength) ? Min(height/KDragFactor,(TInt)KMaxPenToLabel) : 0;
		if (aPointerPos>aCurrent-currentPenToLabel && aPointerPos>Min(aPrevious+currentPenToLabel,aCurrent-1)
			&& aPointerPos<aCurrent+nextPenToLabel && aPointerPos<Max(next-nextPenToLabel,aCurrent))
			{
			iDragLabel=ii-1;
			if (aPointerPos<aCurrent)
				iGridLay->StepRowBackward(iDragLabel);
			else if (iGridLay->RowHeightInPixels(iDragLabel)==0)
				aPrevious=aCurrent;	// reopen zero height row
			return ETrue;
			}
		aPrevious=aCurrent;
		aCurrent=next;
		currentPenToLabel=nextPenToLabel;
		}
	return EFalse;
	}

EXPORT_C TBool CGridImg::UpdateLabelDrag(const TPoint& aPoint)
/** Deletes the dotted drag line and and redraws it at the new pointer position.

Typically, the function is called whan handling a pointer event in a control.

@param aPoint The position of the pointer event.
@return True, if a drag operation was in progress; false, otherwise. */
	{
	if (iDragDim == ENoDrag)
		return EFalse;
	TRect line1 = iGridRect;
	TRect line2 = iGridRect;
	if (iDragDim == EXDrag)
		{
		line1.iTl.iX = line1.iBr.iX = iCurrentDragPos;
		line2.iTl.iX = line2.iBr.iX = iCurrentDragPos = Min(aPoint.iX-iDragDiff,iGridRect.iBr.iX-1);
		}
	else
		{
		line1.iTl.iY = line1.iBr.iY = iCurrentDragPos;
		line2.iTl.iY = line2.iBr.iY = iCurrentDragPos = Min(aPoint.iY-iDragDiff,iGridRect.iBr.iY-1);
		}
	if (line1!=line2)
		{
		CreateGc(iGc);
		iGc->SetClippingRect(iGridRect);
		DrawDraggingHighlight(line1,EDragDrawWithBitmap);
		DrawDraggingHighlight(line2,EDragDrawWithBitmap);
		DeleteGc();
		}
	return ETrue;
	}

void CGridImg::DrawArrowsToInMemoryBitmap(TArrows aArrows)
	{
	const TInt KNoOfPoints = 3;
	CFbsBitmapDevice* bmpDevice=NULL;
	CGraphicsContext* bmpGc=NULL;
	delete iDragBmp;
	iDragBmp=NULL;
	TRAPD(err,
		iDragBmp = new(ELeave) CFbsBitmap;
		TSize bmpSize;
		if (iDragDim==EXDrag)
			bmpSize.SetSize(2*KArrowLength+KArrowSeparation,KArrowBreadth);
		else
			bmpSize.SetSize(KArrowBreadth,2*KArrowLength+KArrowSeparation);
		iDragBmp->Create(bmpSize,EGray2);
		bmpDevice = CFbsBitmapDevice::NewL(iDragBmp);
		CleanupStack::PushL(bmpDevice);
		User::LeaveIfError(bmpDevice->CreateContext(bmpGc));
		CleanupStack::Pop();	// bmpDevice
		);
	if (err!=KErrNone)
		{
		delete iDragBmp;
		iDragBmp=NULL;
		return;		// No big deal - we just don't draw the arrows in low memory conditions
		}
	bmpGc->SetBrushStyle(CGraphicsContext::ESolidBrush);
	bmpGc->SetBrushColor(KRgbBlack);
	TPoint arrow[KNoOfPoints];
	if (iDragDim==EXDrag)
		{
		if (aArrows==EBothArrows)
			{
			arrow[0].SetXY(KArrowLength-1,0);
			arrow[1].SetXY(KArrowLength-1,KArrowBreadth-1);
			arrow[2].SetXY(0,KArrowBreadth/2);
			bmpGc->DrawPolygon(arrow,KNoOfPoints);
			}
		arrow[0].SetXY(KArrowLength+KArrowSeparation,0);
		arrow[1].SetXY(arrow[0].iX,KArrowBreadth-1);
		arrow[2].SetXY(arrow[1].iX+KArrowLength,KArrowBreadth/2);
		bmpGc->DrawPolygon(arrow,KNoOfPoints);
		}
	else
		{
		if (aArrows==EBothArrows)
			{
			arrow[0].SetXY(KArrowBreadth/2,0);
			arrow[1].SetXY(0,KArrowLength-1);
			arrow[2].SetXY(KArrowBreadth-1,KArrowLength-1);
			bmpGc->DrawPolygon(arrow,KNoOfPoints);
			}
		arrow[0].SetXY(0,KArrowLength+KArrowSeparation);
		arrow[1].SetXY(KArrowBreadth-1,arrow[0].iY);
		arrow[2].SetXY(KArrowBreadth/2,arrow[1].iY+KArrowLength);
		bmpGc->DrawPolygon(arrow,KNoOfPoints);
		}
	delete bmpGc;
	delete bmpDevice;
	}

void CGridImg::DrawDraggingHighlight(const TRect aLine,TDragDraw aDragDraw)
	{
	__ASSERT_DEBUG(iGcPtr==iGc,Panic(EGridImgInvalidGC));	// Can only call this using internal GC
	iGc->SetDrawMode(CGraphicsContext::EDrawModeNOTXOR);
	iGc->SetPenStyle(CGraphicsContext::EDottedPen);
	iGc->DrawLine(aLine.iTl,aLine.iBr);
	if (aDragDraw==EDragDrawWithoutBitmap || !iDragBmp)
		return;
	
	const TInt KNoOfArrowsToDisplay = 4;
	const TInt KMinArrowSeparation = 25;
	TSize bmpSize=iDragBmp->SizeInPixels();
	if (iDragDim==EXDrag)
		{
		TInt separation=Max((aLine.iBr.iY-iTitlePoint.iY)/KNoOfArrowsToDisplay,KMinArrowSeparation);
		TPoint point(aLine.iTl.iX-bmpSize.iWidth/2,iTitlePoint.iY+(separation-bmpSize.iHeight)/2);
		while (point.iY<aLine.iBr.iY-separation/2)
			{
			iGc->BitBlt(point,iDragBmp);
			point.iY+=separation;
			}
		}
	else
		{
		TInt separation=Max((aLine.iBr.iX-iTitlePoint.iX)/KNoOfArrowsToDisplay,KMinArrowSeparation);
		TPoint point(iTitlePoint.iX+(separation-bmpSize.iWidth)/2,aLine.iTl.iY-bmpSize.iHeight/2);
		while (point.iX<aLine.iBr.iX-separation/2)
			{
			iGc->BitBlt(point,iDragBmp);
			point.iX+=separation;
			}
		}
	}

EXPORT_C void CGridImg::ScrollL(const TPoint &aOffset)
/** Scrolls the grid by the specified number of pixels.

Draws the minimum necessary, i.e. grid labels, grid lines, grid cells, selected 
regions and the cursor.

@param aOffset Scroll offset, in pixels. */
	{
	if (!aOffset.iY && !aOffset.iX)
		return;
	TRect scrollRect;
	TRect validRect;
	TRegionFix<4> region;
	if (aOffset.iX)
		{
		scrollRect=iGridRect;
		scrollRect.iTl.iX=iMainPoint.iX;
		validRect=scrollRect;
		if (aOffset.iX>0)
			validRect.iBr.iX = Min(validRect.iBr.iX,validRect.iTl.iX+aOffset.iX);
		else
			validRect.iTl.iX = Max(validRect.iTl.iX,validRect.iBr.iX+aOffset.iX);
		iWin->Scroll(scrollRect, TPoint(aOffset.iX,0));
		region.AddRect(validRect);
		}
	if (aOffset.iY)
		{
		scrollRect=iGridRect;
		scrollRect.iTl.iY=iMainPoint.iY;
		validRect=scrollRect;
		if (aOffset.iY>0)
			validRect.iBr.iY = Min(validRect.iBr.iY,validRect.iTl.iY+aOffset.iY);
		else
			validRect.iTl.iY = Max(validRect.iTl.iY,validRect.iBr.iY+aOffset.iY);
		iWin->Scroll(scrollRect, TPoint(0,aOffset.iY));
		region.AddRect(validRect);
		}
	region.Tidy();
	TInt end=region.Count();
	for (TInt ii=0;ii<end;ii++)
		{
		TRect rect=region[ii];
		BeginRedrawAndDrawL(rect);
		}
	CheckSideLabelWidthAndScrollL();
	}
#endif

EXPORT_C void CGridImg::SetGridRect(const TRect& aNewRect)
/** Sets the rectangle that is to contain the grid.

@param aNewRect The rectangle that is to contain the grid. */
	{
	iGridRect = aNewRect;
	ResetReferencePoints();
	}

EXPORT_C void CGridImg::SetPrintGridRect(const TRect& aPrintGridRect)
/** Sets the rectangle that is to contain the grid for the purpose of printing.

@param aPrintRect The rectangle that is to contain the grid. */
	{
	iGridRect=aPrintGridRect;
	iTitlePoint=iGridRect.iTl;
	if (iGridLay->IsPrintedLabels())
		{
		if (iGridLay->IsSideLabels())
			iTitlePoint.iX+=MaxSideLabelWidthInPixels();
		if (iGridLay->IsTopLabels())
			iTitlePoint.iY+=TopLabelHeightInPixels();
		}
	iMainPoint=iTitlePoint;
	}

EXPORT_C void CGridImg::ResetReferencePoints()
/** Resets the reference points.

The reference points are the mainpoint and the titlepoint, i.e the point at 
which the visible range starts, and the point at the top left of the grid 
not including the labels. */
	{
	iTitlePoint=iGridRect.iTl;
	if (iGridLay->IsSideLabels())
		iTitlePoint.iX+=SideLabelWidthInPixels();
	if (iGridLay->IsTopLabels())
		iTitlePoint.iY+=TopLabelHeightInPixels();
	iMainPoint=iTitlePoint+iGridLay->TopLeftTitleRangeSize();
	}

EXPORT_C void CGridImg::NotifyGridRangeResize()
/** Resets the region boundary to the grid boundary. */
	{
	iGridLay->LimitCell(iCursorPos);
	iGridLay->LimitCell(iAnchorPos);
	iSelected->ResizeBounds(iGridLay->iGridRange.iTo);
	}

//->
EXPORT_C void CGridImg::SetGridLabelImg(CGridLabelImg* aGridLabelImg)
/** Sets an object that draws a cell label.

@param aGridLabelImg A pointer to an object that draws a cell label. */
	{
	iGridLabelImg =  aGridLabelImg;
	if (aGridLabelImg && iGridLay)
		aGridLabelImg->SetGridColors(iGridLay->GridColors());
	}

void CGridImg::SetGridColors(const TGridColors& aGridColors)
	{
	iGridLabelImg->SetGridColors(aGridColors);
	iGridCellImg->SetGridColors(aGridColors);
	}
//->
