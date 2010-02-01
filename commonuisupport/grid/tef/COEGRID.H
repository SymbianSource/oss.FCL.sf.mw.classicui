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

#if !defined(__COEGRID_H__)
#define __COEGRID_H__

#if !defined(__E32STD_H_)
#include <e32std.h>
#endif
#if !defined(__GRDSTD_H_)
#include <grdstd.h>
#endif
#if !defined(__COECNTRL_H_)
#include <coecntrl.h>
#endif
#include <eikenv.h>

enum TCoeGridPanic
	{
	ECoeGridCellOutOfRange
	};

class CTGridQueryDialog;
//! A CCoeControl derived class.\n
/**
   The class is used to instantiate a Grid window.\n
   The Grid window is a control which receives the events and delegates the
   handling of events to GridLay and Grid Img classes.\n
*/
class CGridWin : public CCoeControl
	{
public:
	enum TResizeMode { EResizeOff, EResizeColumn, EResizeRow };
public:
	virtual ~CGridWin();
	static CGridWin* NewL(CCoeControl* aWin,CGridLay *aGridLay,CGridImg *aGridImg);
	void ConstructL(CCoeControl* aWin);
	CGridWin(CGridLay *aGridLay,CGridImg *aGridImg);
	CGridLay* GridLay() const;
	CGridImg* GridImg() const;
//replace
	virtual void Draw(const TRect& aRect) const;
    virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);
    virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	virtual void SizeChanged();
	void SetResizeMode(TResizeMode aMode);
	TInt ResizeMode();
	void DrawCellL(const TCellRef& aCell) const;
	void DrawRangeL(const TRangeRef& aRange) const;
	void DrawSelectedL() const;
	TCellRef CursorPos() const;
	void SetCursorPosL(const TCellRef& aCursorPos) const;
	void ExposeCellL(const TCellRef& aCell) const;
protected:
	CGridLay* const iGridLay;
	CGridImg* iGridImg;
private:
	CGridWin(); //not implemented
	TInt operator=(const CGridWin&); //not implemented TInt to stop warning
private:
	TInt iTestInt;
	TResizeMode iResizeMode;
	};
//! A CCoeControl derived class.\n
/**
   The class is used to instantiate a Grid window.\n
   The Grid window is a control which receives the events and delegates the
   handling of events to GridLay and Grid Img classes.\n
*/
class CGrid2Win : public CCoeControl
	{
public:
	enum TResizeMode { EResizeOff, EResizeColumn, EResizeRow };
public:
	virtual ~CGrid2Win();
	static CGrid2Win* NewL(CCoeControl* aWin,CGridLay *aGridLay,CGridImg *aGridImg);
	void ConstructL(CCoeControl* aWin);
	CGrid2Win(CGridLay *aGridLay,CGridImg *aGridImg);
	CGridLay* GridLay() const;
	CGridImg* GridImg() const;
//replace
	virtual void Draw(const TRect& aRect) const;
    virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);
    virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	virtual void SizeChanged();
	void SetResizeMode(TResizeMode aMode);
	TInt ResizeMode();
	void DrawCellL(const TCellRef& aCell) const;
	void DrawRangeL(const TRangeRef& aRange) const;
	void DrawSelectedL() const;
	TCellRef CursorPos() const;
	void SetCursorPosL(const TCellRef& aCursorPos) const;
	void ExposeCellL(const TCellRef& aCell) const;
protected:
	CGridLay* const iGridLay;
	CGridImg* iGridImg;
private:
	CGrid2Win(); //not implemented
	TInt operator=(const CGrid2Win&); //not implemented TInt to stop warning
private:
	TInt iTestInt;
	TResizeMode iResizeMode;
	};
//! A CCoeControl derived class.\n
/**
   A query dialog providing options for resizing a row or column.\n
*/
class CTGridQueryDialog : public CCoeControl
	{
public:
	CTGridQueryDialog(TBool& aIsColumn);
	~CTGridQueryDialog();
	//TBool ExecuteLD();
	void ConstructL();
    virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
private:
	virtual void Draw(const TRect& aRect) const;
private:
	TBool& iIsColumn;
	TBool iExitConfirmed;
	};

#endif
