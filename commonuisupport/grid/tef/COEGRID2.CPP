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
// and column resize.\n
// Also implements the Grid Window which handles the user 
// inputs on the Grid Table.\n
// Copy of COEGRID.CPP except for OfferKeyEvent and HandlePointerEvent\n
// Copy of COEGRID.CPP except for OfferKeyEvent and HandlePointerEvent
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code
*/

#include <coemain.h>
#include "COEGRID.H"

#define KGridPointerRepeatDelayInMicroSeconds	10000

#define KGridRectForPointerRepeats		(TRect(-1000,-1000,1000,1000))

/**
  Static function to construct the Grid Window.\n
  Grid Window is a control on which the Grid table is displayed .\n
  Invokes the second phase constructor.\n
 
  @return : Pointer to the newly constructed Grid window.\n
 
*/
CGrid2Win* CGrid2Win::NewL(CCoeControl* aWin,CGridLay *aGridLay,CGridImg *aGridImg)
	{
	CGrid2Win *self=new(ELeave) CGrid2Win(aGridLay,aGridImg);
	CleanupStack::PushL(self);
	self->ConstructL(aWin);
	CleanupStack::Pop();
	return self;
	}
/**
  Two argument Constructor.\n
  Constructs a Grid Window taking GridLay and Grid Img as arguments.\n
*/
CGrid2Win::CGrid2Win(CGridLay *aGridLay,CGridImg *aGridImg)
	: iGridLay(aGridLay),
	iGridImg(aGridImg)
	{}
/**
  Second phase constructor for the Grid Window.\n
  Creates a control's window which is the child of the application's window group.\n
  Allows pointer grabs in a window in order to receive pointer events.\n
  Sets the window as the default window.\n
*/
void CGrid2Win::ConstructL(CCoeControl* aWin)
	{
	CreateWindowL(aWin);
	Window().PointerFilter(EPointerFilterDrag,0);
	Window().SetPointerGrab(ETrue);
	iGridImg->SetWindow(&Window());
	if (iGridLay->IsIndefiniteRowBoundaries())
		iGridLay->SetUniformRowHeight(ETrue);
	}
/**
  Destructor for Grid Window.\n
*/
CGrid2Win::~CGrid2Win()
	{
	}
/**
  
  @return Pointer to the GridLay object owned by the Grid Window.\n
 
  The function is invoked in case modifications 
  need to be made to the layout of the grid.\n
*/
CGridLay* CGrid2Win::GridLay() const
	{
	return iGridLay;
	}
/**
  @return Pointer to the GridImg object owned by the Grid Window.\n
 
  The function is invoked whenever there is a need to redraw the contents of the grid.\n
*/
CGridImg* CGrid2Win::GridImg() const
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
void CGrid2Win::Draw(const TRect& aRect) const
	{
	CWindowGc& gc=SystemGc();
	gc.DrawRect(Rect());
	TRAPD(err,iGridImg->DrawL(&gc,aRect));
	__ASSERT_ALWAYS(!err,User::Panic(_L("DrawL(&gc,aRect) 2"),err));
	}
/**
  The function provides handlers for various key events such as \n
  Ctrl+ KeyUpArrow.\n
  Ctrl+ KeyDownArrow.\n
  Ctrl+ KeyRightArrow.\n
  Ctrl+ KeyLeftArrow.\n
  Ctrl+ KeyHome.\n
  Ctrl+ KeyEnd.\n
  Ctrl+ KeyPageup.\n
  Ctrl+ KeyPageDown.\n
  KeyUpArrow.\n
  KeyDownArrow.\n 
  KeyRightArrow.\n
  KeyLeftArrow.\n
  KeyHome.\n
  KeyEnd.\n
  KeyPageup.\n
  KeyPageDown.\n
  The function differs from the corresponding function in CGridWin as the
  Resize mode is not taken into consideration while handling the key events.\n
 
  @return : TKeyResponse indicating whether the key event has been handled or not.\n
 
*/
TKeyResponse CGrid2Win::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode /*aType*/)
// Tells GridImg to do the appropriate action on a keypress.
	{
	TUint selectState=0;
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
	return EKeyWasConsumed;
	}
/**
  The function provides handlers for Pointer events.\n
  Handles the following pointer events \n
  1. Pointer Drag.\n
  2. Double click event.\n
  3. Pointer Button Down.\n
*/
void CGrid2Win::HandlePointerEventL(const TPointerEvent& aPointerEvent)
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

	if (event.iType == TPointerEvent::EButton1Up)
		iGridImg->FinishLabelDragL();
	else if (event.iType == TPointerEvent::EButton1Down)
		{
		if (!iGridImg->StartLabelDrag(event.iPosition))
			iGridImg->SetCursorWithPointerL(event.iPosition,0);
		}
	else if (event.iType == TPointerEvent::EDrag)
		{
		if (!iGridImg->UpdateLabelDrag(event.iPosition))
			iGridImg->SetCursorWithPointerL(event.iPosition,CGridImg::EIsWithDrag);
		}
	}
/**
  Shrinks the Grid. 
  The shrinking is achieved by adding value of (1,1) to the top left corner.\n
  and subtracting the same coordinates from the bottom right corner of the grid.\n
*/
void CGrid2Win::SizeChanged()
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
void CGrid2Win::DrawCellL(const TCellRef& aCell) const
	{
	iGridImg->DrawCellL(aCell);
	}
/**
  Draws the rectangle corresponding to the range.\n
  Invokes the DrawRangeL function of the CGridImg class.\n
*/
void CGrid2Win::DrawRangeL(const TRangeRef& aRange) const
	{
	iGridImg->DrawRangeL(aRange);
	}
/**
  Draws the currently selected region.\n
  Invokes the corresponding function of the CGridImg class.\n
*/
void CGrid2Win::DrawSelectedL() const
	{
	iGridImg->DrawSelectedL();
	}
/**
  @return the cell reference where the cursor is located.\n
 
  Delegates the task to the corresponding function of CGridImg function.\n
*/
TCellRef CGrid2Win::CursorPos() const
	{
	return iGridImg->CursorPos();
	}
/**
  Sets the cursor position to the cell reference sent as an argument.\n
*/
void CGrid2Win::SetCursorPosL(const TCellRef& aCursorPos) const
	{
	iGridImg->SetCursorPosL(aCursorPos);
	}
/**
  Scrolls the grid by the minimum necessary to 
  allow the specified cell to become visible.\n
  The offset to the cell required to be visible is calculated and 
  a scroll operation is performed.\n
*/
void CGrid2Win::ExposeCellL(const TCellRef& aCell) const
	{
	TPoint offset=iGridLay->ExposeCell(aCell);
	iGridImg->ScrollL(offset);
	}
