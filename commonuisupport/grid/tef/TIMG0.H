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


#if !defined(__TIMG0_H__)
#define __TIMG0_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif
#if !defined(__GRDSTD_H__)
#include <grdstd.h>
#endif


#define KRgbGridLabels	TRgb(170,170,170)

//! A CGridLabelImg derived class.\n
/**
  Class used to draw grid cell's label for the grid in TGrid0 Step.\n
*/

class CSheetLabelImg : public CGridLabelImg
	{
public:
	enum {ESideLabelMarginWidthInTwips=120};
public:
	CSheetLabelImg(const TFontSpec& aFontSpec,MGraphicsDeviceMap* aGraphicsDeviceMap);
private:
	virtual void DrawRowLabelL(CGraphicsContext* aGc,TInt aRow,const TRect &aRect) const;
	virtual void DrawColLabelL(CGraphicsContext* aGc,TInt aCol,const TRect &aRect) const;
	virtual TInt SideLabelWidthInPixels(TInt aStartRow,TInt aEndRow) const;
	virtual void DrawTopLeftLabelL(CGraphicsContext* aGc,const TRect& aRect) const;
	virtual void DrawRowCursorL(CGraphicsContext* aGc,const TRect& aRect) const;
	void DrawText(CGraphicsContext* aGc,const TDesC& aDes,const TRect& aRect) const;
private:
	};

class CGlobalTextImg;
class CFont;

//! A CGridCellImg derived class.\n
/**
  Class used to draw the grid cell used for the grid in TGrid0 Step.\n
*/

class CSheetCellImg : public CGridCellImg
	{
public:
	enum {ELeftMarginWidth = 2};
public:
	CSheetCellImg();
	virtual void DrawL(CGraphicsContext* aGc,const TCellRef &aCell,const TRect &aRect,
		const TRect& aClipRect) const;
private:
	CSheetCellImg& operator=(const CSheetCellImg&);//not implemented
	};


#endif

