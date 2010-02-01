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
//

#include "GRDPRINT.H"

EXPORT_C CGridPrinter::~CGridPrinter()
/** Destructor.

Frees resources before destruction of the object. */
	{
	delete iGridLay;
	delete iGridImg;
	delete iPrintLabelImg;
	delete iPrintCellImg;
	delete iZoomFactor;
	}

CGridPrinter::CGridPrinter(CGridLabelImg* aPrintLabelImg,CGridCellImg* aPrintCellImg,TZoomFactor* aZoomFactor)
	: iPrintLabelImg(aPrintLabelImg),
	iPrintCellImg(aPrintCellImg),
	iZoomFactor(aZoomFactor),
	iGraphicsDeviceMap(iZoomFactor->GraphicsDeviceMap())
	{
	}

EXPORT_C CGridPrinter* CGridPrinter::NewL(CGridLay* aGridLay,CGridLabelImg* aPrintLabelImg,
	CGridCellImg* aPrintCellImg,TZoomFactor* aZoomFactor)
/** Creates a new grid printer object.

@param aGridLay A pointer to an object that controls the layout of rows and 
columns.
@param aPrintLabelImg A pointer to an object that draws a grid cell's label.
@param aPrintCellImg A pointer to an object that draws the contents of a single 
cell.
@param aZoomFactor A pointer to the zoom factor object.
@see CGridLay::ConstructL() */
	{
	CGridPrinter* self=new(ELeave) CGridPrinter(aPrintLabelImg,aPrintCellImg,aZoomFactor);
	CleanupStack::PushL(self);
	self->ConstructL(aGridLay);
	CleanupStack::Pop();
	return self;
	}

void CGridPrinter::ConstructL(CGridLay* aGridLay)
	{
	iGridLay=new(ELeave) CGridLay(iZoomFactor);
	iGridImg=CGridImg::NewL(iPrintCellImg,iGridLay);
	iGridImg->SetGridLabelImg(iPrintLabelImg);
	iGridLay->ConstructL(aGridLay,iGridImg);
	}

LOCAL_C void CleanupGridLabelImg(TAny* aObject)
	{
	((CGridLabelImg*)aObject)->ReleaseFont();
	((CGridLabelImg*)aObject)->SetGraphicsDeviceMap(NULL);
	}

EXPORT_C void CGridPrinter::PrintBandL(CGraphicsDevice* aDevice,TInt aPageNo,const TBandAttributes& aBandInPixels)
/** Prints a band.

The function implements MPageRegionPrinter::PrintBandL().

@param aDevice Pointer to the graphics device representing the printer
@param aPageNo The number of the page containing the band to be printed.
@param aBandInPixels Attributes of the band to be printed. */
    {
	if (aBandInPixels.iFirstBandOnPage)
		{
		TSize pageSize=iGridLay->PageSizeInTwips();
		iPrintablePage.SetRect(iTlMarginInTwips,pageSize);
		iZoomFactor->SetGraphicsDeviceMap(iGraphicsDeviceMap);	// the real printing device
		iPrintLabelImg->SetGraphicsDeviceMap(iZoomFactor);
		iPrintLabelImg->NotifyGraphicsDeviceMapChangeL();
		TRect printGridRect=iZoomFactor->TwipsToPixels(iPrintablePage);
		printGridRect.iTl+=TPoint(1,1); //For border
		iGridImg->SetPrintGridRect(printGridRect);
		iPrintLabelImg->ReleaseFont();
		TRangeRef pageRange=iGridLay->PageToRange(aPageNo,CGridLay::ERightThenDown/*!!For Now*/);
		iGridLay->SetPrintRange(pageRange);
		}
	iZoomFactor->SetGraphicsDeviceMap(aDevice);
	iPrintLabelImg->SetGraphicsDeviceMap(iZoomFactor);
	iPrintLabelImg->NotifyGraphicsDeviceMapChangeL();
	TRect printablePageInPixels=iZoomFactor->TwipsToPixels(iPrintablePage);
	iScaleFactor=(iGridImg->GridRect().Height()*CGridImg::EScaleOneToOne-1)/printablePageInPixels.Height()+1;//Round up

	TRect printRect=aBandInPixels.iRect;
	if (!printRect.Intersects(printablePageInPixels))
		return;
	printRect.Intersection(printablePageInPixels);

	TRangeRef printRange=iGridLay->VisibleRange();
	printRange.iFrom.iRow=Max(printRange.iFrom.iRow,iGridLay->YValToRow(printRect.iTl.iY*iScaleFactor/CGridImg::EScaleOneToOne));
	printRange.iTo.iRow=Min(printRange.iTo.iRow,iGridLay->YValToRow(printRect.iBr.iY*iScaleFactor/CGridImg::EScaleOneToOne));
	CleanupStack::PushL(TCleanupItem(CleanupGridLabelImg,iPrintLabelImg));
	CGraphicsContext* printerGc;
	User::LeaveIfError(aDevice->CreateContext(printerGc));
	CleanupStack::PushL(printerGc);
	iGridImg->PrintGridLinesAndCellsInRangeL(printerGc,printRange,iScaleFactor);
	CleanupStack::PopAndDestroy(2);	// printerGc + CleanupGridLabelImg
    }

EXPORT_C void CGridPrinter::SetTopLeftMargin(const TPoint& aTlMarginInTwips)
/** Sets the top left margin.

@param aTlMarginInTwips The top left margin, in twips. */
	{
	iTlMarginInTwips=aTlMarginInTwips;
	}

EXPORT_C void CGridPrinter::SetPageSizeInTwipsL(const TSize& aSizeInTwips)
/** Sets the size of the page.

@param aSizeInTwips The size of the page, in twips. */
	{
	if (!iGridLay->IsAutoPagination())
		{
		iGridLay->SetPageSizeInTwipsL(aSizeInTwips);	// won't leave
		return;
		}
	SetGdMapAndPushLabelImgLC();
	iGridLay->SetPageSizeInTwipsL(aSizeInTwips);
	CleanupStack::PopAndDestroy();	// CleanupGridLabelImg
	}

EXPORT_C void CGridPrinter::PaginateL()
/** Paginates the grid. */
	{
	if (iGridLay->IsPaginated())
		return;
	SetGdMapAndPushLabelImgLC();
	iGridLay->PaginateL();
	CleanupStack::PopAndDestroy();	// CleanupGridLabelImg
	}

void CGridPrinter::SetGdMapAndPushLabelImgLC()
	{
	iZoomFactor->SetGraphicsDeviceMap(iGraphicsDeviceMap);	// re-paginate with the real printing device
	iPrintLabelImg->SetGraphicsDeviceMap(iZoomFactor);
	iPrintLabelImg->NotifyGraphicsDeviceMapChangeL();
	iGridLay->SetGraphicsDeviceMap(iZoomFactor);	// Pointer value is same but internal rep. may be different
	CleanupStack::PushL(TCleanupItem(CleanupGridLabelImg,iPrintLabelImg));
	}
