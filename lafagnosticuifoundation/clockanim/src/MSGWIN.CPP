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
// source code for the message-window class
// $Workfile:   MSGWIN.CPP  $
// $Revision:   1.7  $
// $Author:   DougF  $
// $Date:   07 Jul 1999 16:16:18  $
// 
//

#include "CL_STD.H"

// DMessageWindow

DMessageWindow::DMessageWindow()
	{
	__DECLARE_NAME(_S("DMessageWindow"));
	iPlinthTlColor=KRgbWhite;
	iPlinthBrColor=KRgbGray;
	}

DMessageWindow::~DMessageWindow()
	{
	CancelDisplay(); // copes with NULL pointers
	iFunctions->CloseFont(iFont);
	delete iTimer;
	}

void DMessageWindow::StartDisplay()
	{
	__ASSERT_DEBUG(~iFlags&EFlagVisible, Panic(EClockServerPanicAlreadyVisible));
	__ASSERT_DEBUG(!iTimer->IsActive(), Panic(EClockServerPanicTimerIsActive));
	if (~iFlags&EFlagFlash)
		iFunctions->SetSync(MAnimGeneralFunctions::ESyncNone);
	else
		{
		iFunctions->SetSync(MAnimGeneralFunctions::ESyncFlash);
		iFlags|=EFlagFlashStateOn;
		}
	iWindowFunctions->SetVisible(ETrue);
	iFlags|=EFlagVisible;
	if (iDuration.Int()!=SMessageWindowCommandStartDisplayArgs::EIndefiniteDuration)
		{
		iTimer->SetAction(DMessageWindowTimer::EActionCancelDisplay);
		iTimer->After(iDuration);
		}
	}

void DMessageWindow::CancelDisplay()
	{
	if (iTimer!=NULL)
		iTimer->Cancel();
	if (iFunctions!=NULL)
		{
		iFunctions->SetSync(MAnimGeneralFunctions::ESyncNone);
		iWindowFunctions->SetVisible(EFalse);
		iFlags&=~EFlagVisible;
		}
	}

void DMessageWindow::ConstructLP(const TUint8* aBytePtr, TBool)
	{
	SMessageWindowConstructorArgs* messageWindowArgs=(SMessageWindowConstructorArgs*)aBytePtr;
	aBytePtr+=sizeof(SMessageWindowConstructorArgs);
	iBaselineOffset=messageWindowArgs->iBaselineOffset;
	iFont=iFunctions->DuplicateFontL(messageWindowArgs->iFontHandle);
	iBackgroundColor=messageWindowArgs->iBackgroundColor;
	iTextColor=messageWindowArgs->iTextColor;
	iBorderColor=messageWindowArgs->iBorderColor;
	iTimer=DMessageWindowTimer::NewL(*this);
	CancelDisplay();
	}

TInt DMessageWindow::CommandReplyLP(TInt aOpcode, TAny* aArgs)
	{
	switch (aOpcode)
		{
	case EMessageWindowCommandStartDisplay:
		{
		SMessageWindowCommandStartDisplayArgs* messageWindowArgs=(SMessageWindowCommandStartDisplayArgs*)aArgs;
		TInt initialDelay=messageWindowArgs->iInitialDelay.Int();
		TInt duration=messageWindowArgs->iDuration.Int();
		__ASSERT_ALWAYS((initialDelay>=0) && ((duration==SMessageWindowCommandStartDisplayArgs::EIndefiniteDuration) || (duration>=0)),PanicClientFromServer());
		if (messageWindowArgs->iFlash)
			iFlags|=EFlagFlash;
		else
			iFlags&=~EFlagFlash;
		iDuration=messageWindowArgs->iDuration;
		iText=messageWindowArgs->iText;
		if ((iFlags&EFlagVisible) || (initialDelay==0))
			{
			CancelDisplay();
			StartDisplay();
			}
		else if (!iTimer->IsActive())
			{
			iTimer->SetAction(DMessageWindowTimer::EActionStartDisplay);
			iTimer->After(messageWindowArgs->iInitialDelay);
			}
		}
		return KErrNone;
	case EMessageWindowCommandCancelDisplay:
		CancelDisplay();
		return KErrNone;
	case EMessageWindowCommandGetBorders:
		{
		TMargins borders;
		borders.iLeft=EBorderWidthLeft;
		borders.iRight=EBorderWidthRight;
		borders.iTop=EBorderWidthTop;
		borders.iBottom=EBorderWidthBottom;
		const TInt error=iFunctions->Message()->Write(KIpcSlot, TPckgC<TMargins>(borders));
		__ASSERT_ALWAYS(error==KErrNone, PanicClientFromServer());
		}
		return KErrNone;
	case EMessageWindowCommandSetBackgroundColor:
		{
		SMessageWindowBackgroundColorArgs* messageWindowArgs=(SMessageWindowBackgroundColorArgs*)aArgs;
		iBackgroundColor = messageWindowArgs->iBackgroundColor;
		}
		return KErrNone;
	case EMessageWindowCommandSetTextColor:
		{
		SMessageWindowTextColorArgs* messageWindowArgs=(SMessageWindowTextColorArgs*)aArgs;
		iTextColor=messageWindowArgs->iTextColor;
		}
		return KErrNone;
	case EMessageWindowCommandSetBorderColor:
		{
		SMessageWindowBorderColorArgs* messageWindowArgs=(SMessageWindowBorderColorArgs*)aArgs;
		iBorderColor=messageWindowArgs->iBorderColor;
		}
		return KErrNone;
	case EMessageWindowCommandSetPlinthColor:
		{
		SMessageWindowPlinthColorArgs* messageWindowArgs=(SMessageWindowPlinthColorArgs*)aArgs;
		iPlinthTlColor=messageWindowArgs->iTlColor;
		iPlinthBrColor=messageWindowArgs->iBrColor;
		}
		return KErrNone;
	default:
		return DAnimWithUtils::CommandReplyLP(aOpcode, aArgs);
		}
	}

void DMessageWindow::AnimateP(TDateTime*)
	{
	__ASSERT_DEBUG(iFlags&EFlagFlash,Panic(EClockServerPanicAnimatingNonFlashingMessageWindow));
	if (iFunctions->FlashStateOn())
		iFlags|=EFlagFlashStateOn;
	else
		iFlags&=~EFlagFlashStateOn;
	iWindowFunctions->ActivateGc();
	TRect rect=Rect();
	rect.iTl+=TPoint(EBorderWidthLeft, EBorderWidthTop);
	rect.iBr-=TPoint(EBorderWidthRight, EBorderWidthBottom);
	DrawTextPortionOfDisplay(rect);
	}

void DMessageWindow::RedrawP()
	{
	TRect rect=Rect();
	iGc->SetBrushStyle(CGraphicsContext::ENullBrush);
	iGc->SetPenStyle(CGraphicsContext::ESolidPen);
//	iGc->SetPenColor(KRgbBlack);
	iGc->SetPenColor(iBorderColor);
	iGc->SetPenSize(TSize(1, 1));
	iGc->DrawRect(rect);
	rect.Shrink(1, 1);
	iGc->DrawRect(rect);
	rect.Shrink(1, 1);
	iGc->SetPenColor(iPlinthTlColor);
	iGc->DrawLine(rect.iTl, TPoint(rect.iTl.iX, rect.iBr.iY-1));
	iGc->DrawLine(rect.iTl, TPoint(rect.iBr.iX-1, rect.iTl.iY));
	iGc->SetPenColor(iPlinthBrColor);
	iGc->DrawLine(TPoint(rect.iBr.iX-1, rect.iTl.iY), TPoint(rect.iBr.iX-1, rect.iBr.iY));
	iGc->DrawLine(TPoint(rect.iTl.iX, rect.iBr.iY-1), TPoint(rect.iBr.iX, rect.iBr.iY-1));
	rect.Shrink(1, 1);
	iGc->DrawLine(TPoint(rect.iBr.iX-1, rect.iTl.iY), TPoint(rect.iBr.iX-1, rect.iBr.iY));
	iGc->DrawLine(TPoint(rect.iTl.iX, rect.iBr.iY-1), TPoint(rect.iBr.iX, rect.iBr.iY-1));
	rect.iBr-=TPoint(1, 1);
	DrawTextPortionOfDisplay(rect);
	}

TRect DMessageWindow::Rect() const
	{
	return TRect(TPoint(0, 0), iWindowFunctions->WindowSize());
	}

void DMessageWindow::DrawTextPortionOfDisplay(const TRect& aRect) const
	{
	__ASSERT_DEBUG(TRect(aRect.iTl-TPoint(EBorderWidthLeft, EBorderWidthTop),
						aRect.iBr+TPoint(EBorderWidthRight, EBorderWidthBottom))==Rect(),Panic(EClockServerPanicBadRect));
	iGc->SetBrushStyle(CGraphicsContext::ESolidBrush);
	iGc->SetBrushColor(iBackgroundColor);
	if ((iFlags&EFlagFlash) && (~iFlags&EFlagFlashStateOn))
		iGc->Clear(aRect);
	else
		{
		iGc->SetPenStyle(CGraphicsContext::ESolidPen);
		iGc->SetPenColor(iTextColor);
		iGc->UseFont(iFont);
		iGc->DrawText(iText, aRect, iBaselineOffset, CGraphicsContext::ECenter);
		}
	}

// DMessageWindow::DMessageWindowTimer

DMessageWindow::DMessageWindowTimer::DMessageWindowTimer(DMessageWindow& aOwner)
	:CTimer(EPriorityStandard),
	 iOwner(aOwner)
	{
	__DECLARE_NAME(_S("DMessageWindowTimer"));
	CActiveScheduler::Add(this);
	}

DMessageWindow::DMessageWindowTimer* DMessageWindow::DMessageWindowTimer::NewL(DMessageWindow& aOwner)
	{
	DMessageWindowTimer* timer=new(ELeave) DMessageWindowTimer(aOwner);
	CleanupStack::PushL(timer);
	timer->ConstructL();
	CleanupStack::Pop();
	return timer;
	}

void DMessageWindow::DMessageWindowTimer::SetAction(TAction aAction)
	{
	iAction=aAction;
	}

void DMessageWindow::DMessageWindowTimer::RunL()
	{
	switch (iAction)
		{
	case EActionStartDisplay:
		iOwner.StartDisplay();
		break;
	case EActionCancelDisplay:
		iOwner.CancelDisplay();
		break;
#if defined(_DEBUG)
	default:
		Panic(EClockServerPanicBadMessageWindowTimerAction);
		break;
#endif
		}
	}

