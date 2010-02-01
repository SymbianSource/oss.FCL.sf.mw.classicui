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
// @file 
// @internalComponent - Internal Symbian test code
// test code for the message-window class
// $Workfile:   TMSGWIN0.CPP  $
// $Revision:   1.6  $
// $Author:	 DougF  $
// $Date:		 07 Jul 1999 16:16:30  $
// 
//

#include <e32keys.h>
#include <coemain.h>
#include <coedef.h>
#include <coeaui.h>
#include <coecntrl.h>
#include <clock.h>
#include <basched.h>


#include "TMsgWin0Step.h"

// enums

// CClkMsgWinControl

CClkMsgWinControl::CClkMsgWinControl()
	:iBackgroundColor(85, 85, 85),
	 iAnimDll(iCoeEnv->WsSession()),
	 iCounter(0)
	{
	__DECLARE_NAME(_S("CClkMsgWinControl"));

	__ASSERT_DEBUG(iMessageWindow==NULL, User::Panic(_L("Clock test-code"), 1));
	}

void CClkMsgWinControl::ConstructL()
	{
	CreateWindowL();
	EnableDragEvents();
	RWindow& window=Window();
	window.SetPointerGrab(ETrue);
	window.SetBackgroundColor(iBackgroundColor);
	window.SetShadowHeight(8);
	User::LeaveIfError(iAnimDll.Load(_L("CLOCKA.DLL")));
	TFontSpec fontSpec(_L("arial"), iCoeEnv->ScreenDevice()->VerticalPixelsToTwips(25));
	User::LeaveIfError(iCoeEnv->ScreenDevice()->GetNearestFontInTwips((CFont*&)iFont, fontSpec));
	iDummy=new(ELeave) CCoeControl;
	iDummy->SetNonFocusing();
	iBlankWindow=new(ELeave) RBlankWindow(iCoeEnv->WsSession());
	User::LeaveIfError(iBlankWindow->Construct(iCoeEnv->RootWin(), (TUint32)iDummy));
	iMessageWindow=new(ELeave) RMessageWindow(iAnimDll, *iBlankWindow);
	iMessageWindow->ConstructL(EGapAboveMessageWindowText+iFont->AscentInPixels(), iFont->Handle(), TRgb(0, 0, 0), TRgb(255, 255, 255));
	SetExtent(TPoint(10, 10), TSize(100, 100));
	iBlankWindow->Activate();
	ActivateL();
	}

CClkMsgWinControl::~CClkMsgWinControl()
	{
	iCoeEnv->ScreenDevice()->ReleaseFont(iFont); // N.B. do not need to do "delete iFont"
	if (iMessageWindow!=NULL)
		iMessageWindow->Destroy();
	if (iBlankWindow!=NULL)
		iBlankWindow->Destroy();
	delete iDummy;
	iAnimDll.Close();
	}

TKeyResponse CClkMsgWinControl::OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType)
	{
	if (aType==EEventKey)
		{
		switch (aKeyEvent.iCode)
			{
		case CTRL('e'):
			iCoeEnv->Flush();
			CBaActiveScheduler::Exit();
			break;
		case EKeyBackspace:
		case EKeyDelete:
			iMessageWindow->CancelDisplay();
			break;
		case EKeyLineFeed:
		case EKeyEnter:
			{
			TBuf<64> text;
			TInt initialDelay=(aKeyEvent.iModifiers&EModifierRightShift)? 1*1000000: 0;
			TBool flash=(aKeyEvent.iModifiers&EModifierLeftShift);
			if (aKeyEvent.iModifiers&EModifierCtrl)
				{
				text.Format(_L("Counter=%d"), iCounter++);
				iBlankWindow->SetExtent(TPoint(50, 50), WindowSize(*iFont, text));
				iMessageWindow->StartDisplay(flash, initialDelay, text);
				}
			else
				{
				text.Format(_L("Counter=%d, duration=5"), iCounter++);
				iBlankWindow->SetExtent(TPoint(50, 50), WindowSize(*iFont, text));
				iMessageWindow->StartDisplay(flash, initialDelay, 5*1000000, text);
				}
			}
			break;
			}
		}

	return EKeyWasNotConsumed;
	}

void CClkMsgWinControl::HandlePointerEventL(const TPointerEvent& aPointerEvent)
	{
	RWindow& window=Window();
	switch (aPointerEvent.iType)
		{
	case TPointerEvent::EButton1Down:
		iCoeEnv->RootWin().SetOrdinalPosition(0);
		window.SetOrdinalPosition(0);
		iPointerOffset=aPointerEvent.iPosition;
		break;
	case TPointerEvent::EDrag:
		SetPosition(aPointerEvent.iParentPosition-iPointerOffset);
		break;
	case TPointerEvent::EButton1Up:
		window.SetOrdinalPosition(1000);
		iPointerOffset.SetXY(0, 0);
		break;
	default:
		break;
		}
	}

void CClkMsgWinControl::Draw(const TRect&) const
	{
	CGraphicsContext& systemGc=SystemGc();
	systemGc.SetPenStyle(CGraphicsContext::ENullPen);
	systemGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	systemGc.SetBrushColor(iBackgroundColor);
	systemGc.DrawRect(Rect());
	}

TSize CClkMsgWinControl::WindowSize(const CFbsFont& aFont, const TDesC& aText) const
	{
	TMargins borders;
	iMessageWindow->GetBorders(borders);
	__ASSERT_ALWAYS(borders.iLeft==3 &&
					borders.iRight==4 &&
					borders.iTop==3 &&
					borders.iBottom==4, User::Panic(_L("Clock test-code"), 2));
	return TSize(borders.iLeft+borders.iRight+EGapLeftOfMessageWindowText+EGapRightOfMessageWindowText+aFont.TextWidthInPixels(aText),
				 borders.iTop+borders.iBottom+EGapAboveMessageWindowText+EGapBelowMessageWindowText+aFont.HeightInPixels());
	}

// 

CTMsgWinTestAppUi::CTMsgWinTestAppUi(CTmsTestStep* aStep) :
	CTestCoeAppUi(aStep)
	{}


void CTMsgWinTestAppUi::ConstructL()
	{
	CTestCoeAppUi::ConstructL();
	iControl=new(ELeave) CClkMsgWinControl;
	AddToStackL(iControl,ECoeStackPriorityDefault,ECoeStackFlagOwnershipTransfered);
	iControl->ConstructL();
	
	AutoTestManager().StartAutoTest();

	}

/**
   @SYMTestCaseID UIF-Clock-TMsgWin
 */

void CTMsgWinTestAppUi::RunTestStepL(TInt aStep)
	{
	TKeyEvent	theKeyEvent;
	User::After(TTimeIntervalMicroSeconds32(1000000));
	
	switch(aStep)
		{
		case 1:
		SetTestStepID(_L("UIF-Clock-TMsgWin"));
		case 2: case 3: case 4:
		theKeyEvent.iCode = EKeyEnter;
		theKeyEvent.iModifiers = 0;
		INFO_PRINTF1(_L("Start display counter window with duration"));
		iControl->OfferKeyEventL(theKeyEvent, EEventKey);
		break;
		case 5: 
		theKeyEvent.iCode = EKeyDelete;
		INFO_PRINTF1(_L("Close counter window"));
		iControl->OfferKeyEventL(theKeyEvent, EEventKey);
		break;
		case 6: case 7: case 8: case 9: //flashing
		theKeyEvent.iCode = EKeyEnter;
		theKeyEvent.iModifiers = EModifierLeftShift;
		INFO_PRINTF1(_L("Flashing display counter window with duration"));
		iControl->OfferKeyEventL(theKeyEvent, EEventKey);
		break;
		case 10: 
		theKeyEvent.iCode = EKeyDelete;
		INFO_PRINTF1(_L("Close counter window"));
		iControl->OfferKeyEventL(theKeyEvent, EEventKey);
		break;

		case 11: case 12: 
		theKeyEvent.iCode = EKeyEnter;
		theKeyEvent.iModifiers = EModifierCtrl;
		INFO_PRINTF1(_L("Start display counter window"));
		iControl->OfferKeyEventL(theKeyEvent, EEventKey);
		break;
		case 13: 
		theKeyEvent.iCode = EKeyDelete;
		INFO_PRINTF1(_L("Close counter window"));
		iControl->OfferKeyEventL(theKeyEvent, EEventKey);
		break;
		case 14: case 15:  //flashing
		theKeyEvent.iCode = EKeyEnter;
		INFO_PRINTF1(_L("Flashing display counter window"));
		theKeyEvent.iModifiers = EModifierLeftShift | EModifierCtrl;
		iControl->OfferKeyEventL(theKeyEvent, EEventKey);
		break;
		case 16: 
		theKeyEvent.iCode = EKeyDelete;
		INFO_PRINTF1(_L("Close counter window"));
		iControl->OfferKeyEventL(theKeyEvent, EEventKey);
		break;
		case 17: 
		theKeyEvent.iCode = CTRL('e');
		iControl->OfferKeyEventL(theKeyEvent, EEventKey);
		RecordTestResultL();
		CloseTMSGraphicsStep();
		break;
		}
	}

//---------
void CTMsgWin0Step::ConstructAppL(CCoeEnv* aCoe)
	{ // runs inside a TRAP harness
	aCoe->ConstructL();
	CTMsgWinTestAppUi* appUi= new (ELeave) CTMsgWinTestAppUi(this);
	aCoe->SetAppUi(appUi);
	appUi->ConstructL();
	}

CTMsgWin0Step::~CTMsgWin0Step()
/**
   Destructor
 */
	{
	}

CTMsgWin0Step::CTMsgWin0Step()
/**
   Constructor
 */
	{
	// Call base class method to set up the human readable name for logging
	SetTestStepName(KTMsgWin0Step);
	}


TVerdict CTMsgWin0Step::doTestStepL() // main function called by E32
	{
	PreallocateHALBuffer();

	__UHEAP_MARK;

	INFO_PRINTF1(_L("Test Started"));
	CCoeEnv* coe=new CCoeEnv;
	TRAPD(err,ConstructAppL(coe));

	if (!err)
		coe->ExecuteD();

	__UHEAP_MARKEND;
	
	INFO_PRINTF1(_L("Test Finished"));

    return TestStepResult();
	}




