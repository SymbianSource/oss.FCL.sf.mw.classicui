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
// test code for the clock DLL
// $Workfile:   TCLCK1.CPP  $
// $Revision:   1.7  $
// $Author:     DougF  $
// $Date:       07 Jul 1999 16:16:30  $
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code
*/
#include <e32keys.h>
#include <coemain.h>
#include <coedef.h>
#include <coeaui.h>
#include <coecntrl.h>
#include <clock.h>
#include <basched.h>

#include <mbs1.mbg>
#include "TCLCK1STEP.h"



#define TCLCK1_MBM _L("z:\\system\\data\\MBS1.MBM")
#define CLOCK EMbmMbs1Clock
#define CLOCKMSK EMbmMbs1Clockmsk

// classes
// main functions

CTestClck1Ui::CTestClck1Ui(CTmsTestStep* aStep) :
CTestCoeAppUi(aStep)
	{}


void CTestClck1Ui::ConstructL()
	{
	CTestCoeAppUi::ConstructL();
	iControl=new(ELeave) CClk1Control;
	AddToStackL(iControl,ECoeStackPriorityDefault,ECoeStackFlagOwnershipTransfered);
//	appUi->AddToStackL(control,ECoeStackPriorityDefault,ECoeStackFlagOwnershipTransfered);
	iControl->ConstructL();

	AutoTestManager().StartAutoTest();
	}

/**
   @SYMTestCaseID UIF-Clock-TClock1
 */

void CTestClck1Ui::RunTestStepL(TInt aNumStep)
	{
	TKeyEvent theKeyEvent;
	TEventCode theType = EEventKey;
	
	//only for debug
	User::After(TTimeIntervalMicroSeconds32(1000000));
	
	
	switch(aNumStep)
		{
		case 1:
		SetTestStepID(_L("UIF-Clock-TClock1"));
		theKeyEvent.iCode = EKeyEnter;
		theKeyEvent.iModifiers = 0;
		
		iControl->OfferKeyEventL(theKeyEvent, theType);
		INFO_PRINTF1(_L("Show analog & digital clocks"));
		break;
		
		case 2: case 3: case 4: case 5:
		theKeyEvent.iCode = EKeyLeftArrow;
		theKeyEvent.iModifiers = 0;
		
		iControl->OfferKeyEventL(theKeyEvent, theType);
		INFO_PRINTF1(_L("Change universal time backward"));
		break;

		case 6: case 7: case 8: case 9:
		theKeyEvent.iCode = EKeyRightArrow;
		theKeyEvent.iModifiers = 0;
		
		iControl->OfferKeyEventL(theKeyEvent, theType);
		INFO_PRINTF1(_L("Change universal time forward"));
		break;

		case 10:
		theKeyEvent.iCode = '*';
		theKeyEvent.iModifiers = 0;
		
		iControl->OfferKeyEventL(theKeyEvent, theType);
		INFO_PRINTF1(_L("Change clock separator"));
		break;

		case 11:  
		theKeyEvent.iCode = EKeySpace;
		theKeyEvent.iModifiers = EModifierShift;
		
		iControl->OfferKeyEventL(theKeyEvent, theType);
		INFO_PRINTF1(_L("Set a new background color"));
		break;

		case 12:  
		theKeyEvent.iCode = EKeySpace;
		theKeyEvent.iModifiers = 0;
		
		iControl->OfferKeyEventL(theKeyEvent, theType);
		INFO_PRINTF1(_L("Restore previos background color"));
		break;

		case 13:
		theKeyEvent.iCode = EKeyEnter;
		theKeyEvent.iModifiers = EModifierShift;
		
		iControl->OfferKeyEventL(theKeyEvent, theType);
		INFO_PRINTF1(_L("hide clocks"));
		RecordTestResultL();
		CloseTMSGraphicsStep();
		break;

		case 14:
			AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
		}
	}


void CTClck1Step::ConstructAppL(CCoeEnv* aCoeEnv)
	{
	aCoeEnv->ConstructL();
	CTestClck1Ui* appUi=new(ELeave) CTestClck1Ui(this);
	appUi->ConstructL();
	aCoeEnv->SetAppUi(appUi);
	}

CTClck1Step::~CTClck1Step()
/**
   Destructor
 */
	{
	}

CTClck1Step::CTClck1Step()
/**
   Constructor
 */
	{
	// Call base class method to set up the human readable name for logging
	SetTestStepName(KTClck1Step);
	}

TVerdict CTClck1Step::doTestStepL()
	{
	INFO_PRINTF1(_L("Test Started"));
	CCoeEnv* coeEnv=new CCoeEnv;
	if (coeEnv==NULL)
		{
		SetTestStepResult(EFail);
		return TestStepResult();
		}
	TRAPD(error, ConstructAppL(coeEnv));
	if (error!=KErrNone)
		{
		delete coeEnv;
		SetTestStepResult(EFail);
		return TestStepResult();
		}
	coeEnv->ExecuteD();
	INFO_PRINTF1(_L("Test Finished"));
	return TestStepResult();
	}


// CClck1DestructableFont

CClck1DestructableFont::CClck1DestructableFont(CWsScreenDevice* aScreenDevice)
	:iScreenDevice(aScreenDevice)
	{
	}

void CClck1DestructableFont::ConstructL(const TFontSpec& aFontSpec)
	{
	User::LeaveIfError(iScreenDevice->GetNearestFontInTwips((CFont*&)iFont, aFontSpec));
	}

CClck1DestructableFont::~CClck1DestructableFont()
	{
	iScreenDevice->ReleaseFont(iFont); // N.B. do not need to do "delete iFont"
	}

TInt CClck1DestructableFont::Handle() const
	{
	return iFont->Handle();
	}

// CClk1Control

CClk1Control::CClk1Control()
	:iBackgroundColor(85, 85, 85),
	 iAnimDll(iCoeEnv->WsSession()),
	 iDigitalClock0Position(350, 125),
	 iDigitalClock0Size(180, 70),
	 iAnalogClock0Position(10, 0),
	 iAnalogClock0Size(300, 222),
	 iUniversalTimeOffset(0)
	{
	__DECLARE_NAME(_S("CClk1Control"));

	__ASSERT_DEBUG(iDigitalClock0==NULL, User::Panic(_L("Clock test-code"), 1));
	__ASSERT_DEBUG(iAnalogClock0==NULL, User::Panic(_L("Clock test-code"), 2));
	}

void CClk1Control::ConstructL()
	{
	// CONE construction stuff
	CreateBackedUpWindowL(iCoeEnv->RootWin());
	SetExtent(TPoint(10, 10), TSize(620, 220));
	ActivateL();
	iCoeEnv->WsSession().Flush();

	User::LeaveIfError(iAnimDll.Load(_L("CLOCKA.DLL")));

	// clock construction stuff
	CreateDigitalClocksL();
	CreateAnalogClocksL();
	}

CClk1Control::~CClk1Control()
	{
	if (iDigitalClock0!=NULL)
		iDigitalClock0->Destroy();
	if (iAnalogClock0!=NULL)
		iAnalogClock0->Destroy();
	iAnimDll.Close();
	}

TKeyResponse CClk1Control::OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType)
	{
	if (aType==EEventKey)
		{
		TInt adjust=0;
		switch (aKeyEvent.iCode)
			{
		case CTRL('e'):
			iCoeEnv->Flush();
			CBaActiveScheduler::Exit();
			break;
		case EKeySpace:
			if (aKeyEvent.iModifiers&EModifierShift)
				iDigitalClock0->SetBackgroundColor(TRgb(85, 85, 85), TRgb(0, 0, 0));
			else
				iDigitalClock0->SetBackgroundColor(TRgb(170, 170, 170), TRgb(85, 85, 85));
			break;
		case EKeyEnter:
			if (aKeyEvent.iModifiers&EModifierShift)
				{
				iDigitalClock0->SetVisible(EFalse);
				iAnalogClock0->SetVisible(EFalse);
				}
			else
				{
				iDigitalClock0->SetVisible(ETrue);
				iAnalogClock0->SetVisible(ETrue);
				}
			break;
		case '$':
		case '%':
		case '^':
		case '&':
		case '+':
		case '-':
		case '*':
		case '/':
		case 'S':
		case 's':
		case '\\':
		case ':':
			{
			TLocale locale;
			locale.Refresh();
#pragma warning (disable: 4710)
			locale.SetTimeSeparator(aKeyEvent.iCode, 1);
			locale.SetTimeSeparator(aKeyEvent.iCode, 2);
#pragma warning (default: 4710)
			locale.Set();
			}
			break;
		case EKeyLeftArrow:
		case EKeyUpArrow:
			adjust=-3600;
			goto adjustClock;
		case EKeyRightArrow:
		case EKeyDownArrow:
			adjust=3600;
			goto adjustClock;
		adjustClock:
			iUniversalTimeOffset+=adjust;
			iDigitalClock0->SetUniversalTimeOffset(iUniversalTimeOffset);
			iAnalogClock0->SetUniversalTimeOffset(iUniversalTimeOffset);
			break;
		case 'U':
		case 'u':
			iDigitalClock0->UpdateDisplay();
			iAnalogClock0->UpdateDisplay();
			break;
		case 'D':
		case 'd':
			iDigitalClock0->Draw();
			iAnalogClock0->Draw();
			break;
			}
		}

	return EKeyWasConsumed;
	}

void CClk1Control::Draw(const TRect&) const
	{
	CGraphicsContext& systemGc=SystemGc();
	systemGc.SetPenStyle(CGraphicsContext::ENullPen);
	systemGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	systemGc.SetBrushColor(iBackgroundColor);
	systemGc.DrawRect(Rect());
	}

void CClk1Control::CreateDigitalClocksL()
	{
	TMargins margins;
	margins.iLeft=0;
	margins.iRight=0;
	margins.iTop=0;
	margins.iBottom=0;
	// construct digital clock
	STimeDeviceShadow digitalClock0Shadow;
	digitalClock0Shadow.iIsOn=ETrue;
	digitalClock0Shadow.iColor=TRgb(85, 85, 85);
	digitalClock0Shadow.iOffset.SetXY(2, 2);
	//
	iDigitalClock0=new(ELeave) RDigitalClock(iAnimDll, BackedUpWindow());
	iDigitalClock0->ConstructL(TTimeIntervalSeconds(30*60), iDigitalClock0Position, iDigitalClock0Size, margins, digitalClock0Shadow, TRgb(170, 170, 170), 1);
	//
	TBuf<64> digitalClock0Format0=_L("%-B%J%:1%T%+B");
	CClck1DestructableFont* digitalClock0Font0=new(ELeave) CClck1DestructableFont(iCoeEnv->ScreenDevice());
	CleanupStack::PushL(digitalClock0Font0);
	TFontSpec digitalClock0FontSpec0(_L("arial"), iCoeEnv->ScreenDevice()->VerticalPixelsToTwips(25));
	digitalClock0FontSpec0.iFontStyle.SetPosture(EPostureItalic);
	digitalClock0FontSpec0.iFontStyle.SetStrokeWeight(EStrokeWeightBold);
	digitalClock0Font0->ConstructL(digitalClock0FontSpec0);
	iDigitalClock0->AddTextSectionL(TDigitalDisplayTextSection(digitalClock0Font0->Handle(), TRgb(0, 0, 0),
																EDigitalDisplayHorizontalTextAlignmentCenter,
																EDigitalDisplayVerticalTextAlignmentCenterExclDescent,
																0, 0, digitalClock0Format0));
	//
	CleanupStack::PopAndDestroy(); // pop and destroy digitalClock0Font0
	}

void CClk1Control::CreateAnalogClocksL()
	{
	CWsScreenDevice* screenDevice=iCoeEnv->ScreenDevice();
	TMargins margins;
	margins.iLeft=0;
	margins.iRight=0;
	margins.iTop=0;
	margins.iBottom=0;
	// construct analog clock
	//
	STimeDeviceShadow  analogClock0Shadow;
	analogClock0Shadow.iIsOn=ETrue;
	analogClock0Shadow.iColor=TRgb(85, 85, 85);
	analogClock0Shadow.iOffset.SetXY(4, 4);
	//
	CFbsBitmap* analogClock0Face=new(ELeave) CFbsBitmap;
	CleanupStack::PushL(analogClock0Face);
	User::LeaveIfError(analogClock0Face->Load(TCLCK1_MBM, CLOCK));
	analogClock0Face->SetSizeInTwips(screenDevice);
	CFbsBitmap* analogClock0FaceMask=new(ELeave) CFbsBitmap;
	CleanupStack::PushL(analogClock0FaceMask);
	User::LeaveIfError(analogClock0FaceMask->Load(TCLCK1_MBM, CLOCKMSK));
	analogClock0Face->SetSizeInTwips(screenDevice);
	//
	iAnalogClock0=new(ELeave) RAnalogClock(iAnimDll, BackedUpWindow());
	iAnalogClock0->ConstructL(TTimeIntervalSeconds(30*60), iAnalogClock0Position, iAnalogClock0Size, margins, analogClock0Shadow,
								analogClock0Face->Handle(), analogClock0FaceMask->Handle(), 2);
	//
	TRgb black(0, 0, 0);
	CArrayFix<TPoint>* pointList=new(ELeave) CArrayFixFlat<TPoint>(4);
	CleanupStack::PushL(pointList);
	//
	// N.B. the dimensions/positions of the hand features (i.e. lines and circles) are specified with the hand assumed to be in the
	// 12 o'clock position, with TPoint(0, 0) being the center of the clock
	TAnalogDisplayHand analogClock0HourHand(EAnalogDisplayHandOneRevPer12Hours);
	analogClock0HourHand.AddLine(CGraphicsContext::ESolidPen, black, TSize(4, 4), TPoint(0, 10), TPoint(0, -55));
	iAnalogClock0->AddHandL(analogClock0HourHand);
	//
	TAnalogDisplayHand analogClock0MinuteHand(EAnalogDisplayHandOneRevPerHour);
	analogClock0MinuteHand.AddLine(CGraphicsContext::ESolidPen, black, TSize(4, 4), TPoint(0, 10), TPoint(0, -70));
	iAnalogClock0->AddHandL(analogClock0MinuteHand);
	//
	CleanupStack::PopAndDestroy(); // pop and destroy pointList
	CleanupStack::PopAndDestroy(); // pop and destroy analogClock0FaceMask
	CleanupStack::PopAndDestroy(); // pop and destroy analogClock0Face
	}

