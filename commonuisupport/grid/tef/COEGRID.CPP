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
// Implements the query dialog box used for asking users input on row 
// and column resize. Also implements the Grid Window which handles the user 
// inputs on the Grid Table.\n
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code
*/

#include <gdi.h>
#include <coemain.h>
#include "COEGRID.H"
#include <grdstd.h>

#define KGridPointerRepeatDelayInMicroSeconds	10000

#define KGridRectForPointerRepeats		(TRect(-1000,-1000,1000,1000))
/**
  Function invoked in case of PANIC.\n
*/
GLDEF_C void Panic(TCoeGridPanic aPanic)
	{
	User::Panic(_L("COEGRID"),aPanic);
	}

//
// class CTGridQueryDialog
//

CTGridQueryDialog::~CTGridQueryDialog()
	{
	//iEikonEnv->RemoveFromStack(this);	
	}

/*
TBool CTGridQueryDialog::ExecuteLD()
	{
	ConstructL();
    CActiveScheduler::Start();
	TBool exitConfirmed=iExitConfirmed;
	delete this;
	return exitConfirmed;
	}
*/

/**   Single argument Constructor for CTGridQueryDialog  */

CTGridQueryDialog::CTGridQueryDialog(TBool& aIsColumn)
	: iIsColumn(aIsColumn)
	{}
/**
  Second phase constructor for the query dialog.\n
  Creates a control window , 
  Set the control's extent and draws the control after activating the dialog.\n
*/
void CTGridQueryDialog::ConstructL()
	{
	CreateWindowL();
	SetExtent(TPoint(0,0),TSize(600,100));
	//iEikonEnv->AddDialogLikeControlToStackL(this);
	ActivateL();
	DrawNow();
	}
/**
  Draw function related to CTGridQueryDialog box.\n
  Draws the dialog box with three options for resize column,row and to skip.\n
*/
void CTGridQueryDialog::Draw(const TRect& /*aRect*/) const
	{
	CWindowGc& gc=iCoeEnv->SystemGc();
	gc.SetPenColor(KRgbBlack);
	gc.SetBrushColor(KRgbGray);
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	TRect border=Rect();
	gc.DrawRect(border);
	border.Shrink(5,5);
	gc.DrawRect(border);
	border.Shrink(5,5);
	gc.SetBrushColor(KRgbBlack);
	gc.UseFont(iCoeEnv->NormalFont());
	TPoint pos=border.iTl;
	pos.iY+=20;
	gc.DrawText(_L("Press [C] to resize column, [R] to resize row, [Esc] to cancel"),pos);
	pos.iY+=30;
	gc.DrawText(_L("Resize with arrow keys, then [Enter] to resize or [Esc] to cancel"),pos);
	}
 /**
    Auxilliary Fn for T-Grid0Step-RunTestStepL
    The query dialog box is used to handle user inputs regarding resizing.\n
    Handles the following key events.\n
    Esc Key Event - Skips the Resize.\n
    'r' Key Event - Invoked for resizing the row.\n
    'c' Key Event - Invoked for resizing the row.\n
 */   
TKeyResponse CTGridQueryDialog::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
	{
	if(aType==EEventKey)
		{
		switch(User::LowerCase(aKeyEvent.iCode))
			{
		case EKeyEscape:
			iExitConfirmed=EFalse;						
		//	CActiveScheduler::Stop();
			break;
		case 'c': //C
			iExitConfirmed=ETrue;
			iIsColumn=ETrue;
		//	CActiveScheduler::Stop();
			break;
		case 'r':  //R
			iExitConfirmed=ETrue;
			iIsColumn=EFalse;
		//	CActiveScheduler::Stop();
			break;
		default:
			break;
			}
		}
	return EKeyWasConsumed;
	}

/**
  Static function to construct the Grid Window.\n
  Grid Window is a control on which the Grid table is displayed .\n
  Invokes the second phase constructor.\n
*/
CGridWin* CGridWin::NewL(CCoeControl* aWin,CGridLay *aGridLay,CGridImg *aGridImg)
	{
	CGridWin *self=new(ELeave) CGridWin(aGridLay,aGridImg);
	CleanupStack::PushL(self);
	self->ConstructL(aWin);
	CleanupStack::Pop();
	return self;
	}
/**
  Sets the resize mode for the Grid Window.\n
  The typical values of the mode will be to resize column or row .\n
  The function is invoked when the user chooses to resize row or column.\n
*/
void CGridWin::SetResizeMode(TResizeMode aMode)
	{
	iResizeMode=aMode;
	}
/**
  Returns the current resize mode for the Grid Window.\n
  The typical values of the mode will be to resize column or row .\n
*/
TInt CGridWin::ResizeMode()
	{
	return iResizeMode;
	}
/**
  Two argument Constructor.\n
  Constructs a Grid Window taking GridLay and Grid Image as arguments.\n
*/
CGridWin::CGridWin(CGridLay *aGridLay,CGridImg *aGridImg)
	: iGridLay(aGridLay),
	iGridImg(aGridImg),
	iResizeMode(EResizeOff)
	{}
/**
  Second phase constructor for the Grid Window.\n
  Creates a control's window which is the child of the application's window group.\n
  Allows pointer grabs in a window in order to receive pointer events.\n
  Sets the window as the default window.\n
*/
void CGridWin::ConstructL(CCoeControl* aWin)
	{
	CreateWindowL(aWin);
	Window().PointerFilter(EPointerFilterDrag,0);
	Window().SetPointerGrab(ETrue);
	iGridImg->SetWindow(&Window());
	if (iGridLay->IsIndefiniteRowBoundaries())
		iGridLay->SetUniformRowHeight(ETrue);
	}
/**
  Destructor for the  Grid Window class.\n
*/
CGridWin::~CGridWin()
	{
	}
/**
  
  @return Pointer to the GridLay object owned by the Grid Window.\n
 
  The function is invoked in case modifications 
  need to be made to the layout of the grid.\n
*/
CGridLay* CGridWin::GridLay() const
	{
	return iGridLay;
	}
/**
  @return Pointer to the GridImg object owned by the Grid Window.\n
 
  The function is invoked whenever there is a need to redraw the contents of the grid.\n
*/
CGridImg* CGridWin::GridImg() const
	{
	return iGridImg;
	}
/**
  Draws the Grid Window.\n
  The function is invoked by the window server.\n
  This function is used for window server-initiated redrawing of controls,
  and for some application-initiated drawing.\n
  It should be implemented by each control.\n
 
*/
void CGridWin::Draw(const TRect& aRect) const
	{
	CWindowGc& gc=SystemGc();
	gc.DrawRect(Rect());
	TRAPD(err,iGridImg->DrawL(&gc,aRect));
	__ASSERT_ALWAYS(!err,User::Panic(_L("DrawL(&gc,aRect)"),err));
	}

TKeyResponse CGridWin::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode /*aType*/)
// Tells GridImg to do the appropriate action on a keypress.
	{
	if(iResizeMode!=EResizeOff)
		{
		TKeyResponse response=EKeyWasNotConsumed;
		if(iResizeMode==EResizeColumn)
			{
			switch(aKeyEvent.iCode)
				{
			case EKeyLeftArrow:
				iGridImg->UpdateLabelResize(-4);
				response=EKeyWasConsumed;
				break;
			case EKeyRightArrow:
				iGridImg->UpdateLabelResize(4);
				response=EKeyWasConsumed;
				break;
				}
			}
		else if(iResizeMode==EResizeRow)
			{
			switch(aKeyEvent.iCode)
				{
			case EKeyUpArrow:
				iGridImg->UpdateLabelResize(-4);
				response=EKeyWasConsumed;
				break;
			case EKeyDownArrow:
				iGridImg->UpdateLabelResize(4);
				response=EKeyWasConsumed;
				break;
				}
			}
		switch(aKeyEvent.iCode)
			{
		case EKeyEnter:
			iGridImg->FinishLabelResizeL(ETrue);
			iResizeMode=EResizeOff;
			response=EKeyWasConsumed;
			break;
		case EKeyEscape:
			iGridImg->FinishLabelResizeL(EFalse);
			iResizeMode=EResizeOff;
			response=EKeyWasConsumed;
			break;
			}
		return response;
		}
	else
		{
		TUint selectState=0;
		if (aKeyEvent.iModifiers&EModifierShift)
			selectState=CGridImg::EIsWithSelect;
		if (aKeyEvent.iModifiers&EModifierCtrl)
			{
			switch (aKeyEvent.iCode)
				{
			case EKeyUpArrow:
				iGridImg->MoveCursorL(EMovePageUp,selectState);
				break;
			case EKeyDownArrow:
				iGridImg->MoveCursorL(EMovePageDown,selectState);
				break;
			case EKeyLeftArrow:
				iGridImg->MoveCursorL(EMovePageLeft,selectState);
				break;
			case EKeyRightArrow:
				iGridImg->MoveCursorL(EMovePageRight,selectState);
				break;
			case EKeyHome:
				iGridImg->MoveCursorL(EMoveHome,selectState);
				break;
			case EKeyEnd:
				iGridImg->MoveCursorL(EMoveEnd,selectState);
				break;
			case EKeyPageUp:
				iGridImg->MoveCursorL(EMoveColumnStart,selectState);
				break;
			case EKeyPageDown:
				iGridImg->MoveCursorL(EMoveColumnEnd,selectState);
				break;
			default:
				return EKeyWasNotConsumed;
				}
			}
		else
			{
			switch (aKeyEvent.iCode)
				{
			case EKeyUpArrow:
				iGridImg->MoveCursorL(EMoveRowUp,selectState);
				break;
			case EKeyDownArrow:
				iGridImg->MoveCursorL(EMoveRowDown,selectState);
				break;
			case EKeyLeftArrow:
				iGridImg->MoveCursorL(EMoveColumnLeft,selectState);
				break;
			case EKeyRightArrow:
				iGridImg->MoveCursorL(EMoveColumnRight,selectState);
				break;
			case EKeyPageUp:
				iGridImg->MoveCursorL(EMovePageUp,selectState);
				break;
			case EKeyPageDown:
				iGridImg->MoveCursorL(EMovePageDown,selectState);
				break;
			case EKeyHome:
				iGridImg->MoveCursorL(EMoveRowStart,selectState);
				break;
			case EKeyEnd:
				iGridImg->MoveCursorL(EMoveRowEnd,selectState);
				break;
			default:
				return EKeyWasNotConsumed;
				}
			}
		}
	return EKeyWasConsumed;
	}
/**
  Function handles the pointer events received by the control Window.\n
  Handles the following events.\n
  1. Pointer Drag.\n
  2. Double click.\n
  3. Ctrl+ ButtonDown.\n
  4. Shift+ Select.\n
*/
void CGridWin::HandlePointerEventL(const TPointerEvent& aPointerEvent)
	{
	//
	// Tells GridImg to do the appropriate action on a pointer event
	//
    if (aPointerEvent.iType==TPointerEvent::EDrag || aPointerEvent.iType==TPointerEvent::EButtonRepeat
		&& !iGridImg->MainRect().Contains(aPointerEvent.iPosition))
		{
        Window().RequestPointerRepeatEvent(KGridPointerRepeatDelayInMicroSeconds,KGridRectForPointerRepeats);
		}
	TPointerEvent event=aPointerEvent;
	if (event.iType==TPointerEvent::EButtonRepeat)
		event.iType=TPointerEvent::EDrag;
	else if (event.iModifiers&EModifierDoubleClick)
		event.iType=TPointerEvent::EButton1Down;

	TUint flagList=0;
	if (event.iModifiers&EModifierCtrl)
		flagList=CGridImg::EIsWithControl;
	if (event.iType == TPointerEvent::EButton1Up)
		iGridImg->FinishLabelDragL();
	else if (event.iType == TPointerEvent::EButton1Down)
		{
		if (!iGridImg->StartLabelDrag(event.iPosition))
			{
			if (event.iModifiers&EModifierShift)
				flagList|=CGridImg::EIsWithSelect;
			iGridImg->SetCursorWithPointerL(event.iPosition,flagList);
			}
		}
	else if (event.iType == TPointerEvent::EDrag)
		{
		if (!iGridImg->UpdateLabelDrag(event.iPosition))
			{
			flagList|=CGridImg::EIsWithSelect|CGridImg::EIsWithDrag;
			iGridImg->SetCursorWithPointerL(event.iPosition,flagList);
			}
		}
	}
/**
  Shrinks the Grid. 
  The shrinking is achieved by adding value of (1,1) to the top left corner.\n
  and subtracting the same coordinates from the bottom right corner of the grid.\n
*/
void CGridWin::SizeChanged()
	{
	TRect rect(Size());
	rect.Shrink(1,1);
	iGridImg->SetGridRect(rect);
	iGridLay->ResetVisibleToCell();
	}
/**
  Draw the cell corresponding to the reference.\n
  Calls the DrawCellL function of the CGridImg class.\n
*/
void CGridWin::DrawCellL(const TCellRef& aCell) const
	{
	iGridImg->DrawCellL(aCell);
	}
/**
  Draws the rectangle corresponding to the range.\n
  Invokes the DrawRangeL function of the CGridImg class.\n
*/
void CGridWin::DrawRangeL(const TRangeRef& aRange) const
	{
	iGridImg->DrawRangeL(aRange);
	}
/**
  Draws the currently selected region.\n
  Invokes the corresponding function of the CGridImg class.\n
*/
void CGridWin::DrawSelectedL() const
	{
	iGridImg->DrawSelectedL();
	}
/**
  @return the cell reference where the cursor is located.\n
 
  Delegates the task to the corresponding function of CGridImg function.\n
*/
TCellRef CGridWin::CursorPos() const
	{
	return iGridImg->CursorPos();
	}
/**
  Sets the cursor position to the cell reference sent as an argument.\n
*/
void CGridWin::SetCursorPosL(const TCellRef& aCursorPos) const
	{
	iGridImg->SetCursorPosL(aCursorPos);
	}
/**
  Scrolls the grid by the minimum necessary to 
  allow the specified cell to become visible.\n
  The offset to the cell required to be visible is calculated and 
  a scroll operation is performed.\n
*/
void CGridWin::ExposeCellL(const TCellRef& aCell) const
	{
	TPoint offset=iGridLay->ExposeCell(aCell);
	iGridImg->ScrollL(offset);
	}
