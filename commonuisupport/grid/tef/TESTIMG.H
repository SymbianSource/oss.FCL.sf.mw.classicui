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

#if !defined(__TESTIMG_H__)
#define __TESTIMG_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif
#if !defined(__GRDSTD_H__)
#include <grdstd.h>
#endif

//! A derived class from CBase and MGridTable interface.\n
/**
 Grid Table class for TCoGridStep application.\n
*/

class CTestGridTable : public CBase,public MGridTable
	{
public:
	CTestGridTable();
	virtual TBool RequestRow(TInt aRow,TInt& aReturnRow) const;
public:
	TBool iZeroRows;	// !! OK for test code
	};
//! A CGridCellImg derived class.\n
/**
 Grid Label class for TCoGridStep application.\n
*/
class CTestLabelImg : public CGridLabelImg
	{
public:
	enum {
		ESideLabelMarginWidthInTwips=120,
		ERowCursorDiameterInPixels=10
		};
public:
	CTestLabelImg(const TFontSpec& aFontSpec,MGraphicsDeviceMap* aGraphicsDeviceMap);
	virtual void DrawRowLabelL(CGraphicsContext *aGc,TInt aRow,const TRect &aRect) const;
	virtual void DrawColLabelL(CGraphicsContext *aGc,TInt aCol,const TRect &aRect) const;
	virtual TInt SideLabelWidthInPixels(TInt aStartRow,TInt aEndRow) const;
	virtual void DrawRowCursorL(CGraphicsContext* aGc,const TRect& aRect) const;
	virtual void DrawTopLeftLabelL(CGraphicsContext* aGc,const TRect& aRect) const;
	};

class CFont;
//! A CGridCellImg derived class.\n
/**
 Grid cell class for TCoGridStep application.\n
*/
class CTestCellImg : public CGridCellImg
	{
public:
	CTestCellImg(const CFont *aFont);
	virtual void DrawL(CGraphicsContext *aGc,const TCellRef &aCell,const TRect &aRect,
		const TRect& aClipRect) const;
	virtual TInt DataWidthInPixelsL(const TCellRef& aCell) const;
	virtual TBool DoesCellContainDataL(const TCellRef& aCell) const;
private:
	const TDesC* GetL(TInt aRow,TInt aCol) const;
	CTestCellImg& operator=(const CTestCellImg&);//not implemented
private:
	enum { ENumberOfItems=5 };
private:
	const CFont* iFont;
	struct STestData
		{
		TCellRef iPos;
		TBuf<32> iBuf;
		};
	STestData iData[ENumberOfItems];	//!!! Very crude but only for testing purposes
	};


#endif
