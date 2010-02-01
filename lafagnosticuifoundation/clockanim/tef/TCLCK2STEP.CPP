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
#include "TCLCK2STEP.h"



#define TCLCK1_MBM _L("z:\\system\\data\\MBS1.MBM")
#define CLOCK EMbmMbs1Clock
#define CLOCKMSK EMbmMbs1Clockmsk

// classes
// main functions

CTestClck2Ui::CTestClck2Ui(CTmsTestStep* aStep) :
CTestCoeAppUi(aStep)
	{}


void CTestClck2Ui::ConstructL()
	{
	CTestCoeAppUi::ConstructL();
	iControl=new(ELeave) CClk2Control;
	AddToStackL(iControl,ECoeStackPriorityDefault,ECoeStackFlagOwnershipTransfered);
//	appUi->AddToStackL(control,ECoeStackPriorityDefault,ECoeStackFlagOwnershipTransfered);
	iControl->ConstructL();

	AutoTestManager().StartAutoTest();
	}

/**
   @SYMTestCaseID UIF-Clock-TClock2
 */

void CTestClck2Ui::RunTestStepL(TInt aNumStep)
	{
	TKeyEvent theKeyEvent;
	TEventCode theType = EEventKey;
	
	//only for debug
	User::After(TTimeIntervalMicroSeconds32(1000000));
	
	
	switch(aNumStep)
		{
		case 1:
		SetTestStepID(_L("UIF-Clock-TClock2"));
		theKeyEvent.iCode = EKeyEnter;
		theKeyEvent.iModifiers = 0;
		
		iControl->OfferKeyEventL(theKeyEvent, theType);
		INFO_PRINTF1(_L("Show analog & digital clocks"));
		break;
		
		case 2: case 6:
		//Animate for 5 seconds
		User::After(5000000);
		INFO_PRINTF1(_L("Animate for 5 seconds"));
		break;

		case 3:
		theKeyEvent.iCode = 'I';
		theKeyEvent.iModifiers = 0;
		
		iControl->OfferKeyEventL(theKeyEvent, theType);
		INFO_PRINTF1(_L("Stop wserv heartbeat timer"));
		break;

		case 4:
		User::After(5000000);
		INFO_PRINTF1(_L("Wait 5 seconds"));
		break;

		case 5:  
		theKeyEvent.iCode = 'A';
		theKeyEvent.iModifiers = 0;
		
		iControl->OfferKeyEventL(theKeyEvent, theType);
		INFO_PRINTF1(_L("Start wserv heartbeat timer"));
		RecordTestResultL();
		CloseTMSGraphicsStep();
		break;
		
		case 7:
			AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
		}
	}


void CTClck2Step::ConstructAppL(CCoeEnv* aCoeEnv)
	{
	aCoeEnv->ConstructL();
	CTestClck2Ui* appUi=new(ELeave) CTestClck2Ui(this);
	appUi->ConstructL();
	aCoeEnv->SetAppUi(appUi);
	}

CTClck2Step::~CTClck2Step()
/**
 * Destructor
 */
	{
	}

CTClck2Step::CTClck2Step()
/**
 * Constructor
 */
	{
	// Call base class method to set up the human readable name for logging
	SetTestStepName(KTClck2Step);
	}

TVerdict CTClck2Step::doTestStepL()
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


// CClck2DestructableFont

CClck2DestructableFont::CClck2DestructableFont(CWsScreenDevice* aScreenDevice)
	:iScreenDevice(aScreenDevice)
	{
	}

void CClck2DestructableFont::ConstructL(const TFontSpec& aFontSpec)
	{
	User::LeaveIfError(iScreenDevice->GetNearestFontInTwips((CFont*&)iFont, aFontSpec));
	}

CClck2DestructableFont::~CClck2DestructableFont()
	{
	iScreenDevice->ReleaseFont(iFont); // N.B. do not need to do "delete iFont"
	}

TInt CClck2DestructableFont::Handle() const
	{
	return iFont->Handle();
	}

// CClk2Control

CClk2Control::CClk2Control()
	:iBackgroundColor(85, 85, 85),
	 iAnimDll(iCoeEnv->WsSession()),
	 iDigitalClock0Position(350, 125),
	 iDigitalClock0Size(180, 70),
	 iAnalogClock0Position(10, 0),
	 iAnalogClock0Size(300, 222),
	 iUniversalTimeOffset(0)
	{
	__ASSERT_DEBUG(iDigitalClock0==NULL, User::Panic(_L("Clock test-code"), 1));
	__ASSERT_DEBUG(iAnalogClock0==NULL, User::Panic(_L("Clock test-code"), 2));
	}

void CClk2Control::ConstructL()
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

CClk2Control::~CClk2Control()
	{
	if (iDigitalClock0!=NULL)
		iDigitalClock0->Destroy();
	if (iAnalogClock0!=NULL)
		iAnalogClock0->Destroy();
	iAnimDll.Close();
	}

TKeyResponse CClk2Control::OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType)
	{
	if (aType==EEventKey)
		{
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
		case 'A':
		case 'a':
			{
			TRawEvent	event;
			event.Set(TRawEvent::EActive);
			UserSvr::AddEvent(event);
			}
			break;
		case 'I':
		case 'i':
			{
			TRawEvent	event;
			event.Set(TRawEvent::EInactive);
			UserSvr::AddEvent(event);
			}
			break;
			}
		}

	return EKeyWasConsumed;
	}

void CClk2Control::Draw(const TRect&) const
	{
	CGraphicsContext& systemGc=SystemGc();
	systemGc.SetPenStyle(CGraphicsContext::ENullPen);
	systemGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	systemGc.SetBrushColor(iBackgroundColor);
	systemGc.DrawRect(Rect());
	}

void CClk2Control::CreateDigitalClocksL()
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
	CClck2DestructableFont* digitalClock0Font0=new(ELeave) CClck2DestructableFont(iCoeEnv->ScreenDevice());
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

void CClk2Control::CreateAnalogClocksL()
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
								analogClock0Face->Handle(), analogClock0FaceMask->Handle(), 3);
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
	TAnalogDisplayHand analogClock0SecondHand(EAnalogDisplayHandOneRevPerMinute);
	analogClock0SecondHand.AddLine(CGraphicsContext::ESolidPen, black, TSize(2, 2), TPoint(0, 10), TPoint(0, -70));
	iAnalogClock0->AddHandL(analogClock0SecondHand);
	//
	CleanupStack::PopAndDestroy(); // pop and destroy pointList
	CleanupStack::PopAndDestroy(); // pop and destroy analogClock0FaceMask
	CleanupStack::PopAndDestroy(); // pop and destroy analogClock0Face
	}

