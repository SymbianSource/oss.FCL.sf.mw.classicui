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
// $Workfile:   TCLCK0.CPP  $
// $Revision:   1.6  $
// $Author:   DougF  $
// $Date:   07 Jul 1999 16:16:28  $
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

#include <mbs0.mbg>
#define TCLCK0_MBM _L("z:\\system\\data\\MBS0.MBM")
#define CLOCK EMbmMbs0Clock
#define CLOCKMSK EMbmMbs0Clockmsk

#include "TCLCK0STEP.h"


//_LIT(KTestString1,"Show analog & digital clocks");
_LIT(KTestString2,"Change universal time backward");
_LIT(KTestString3,"Change universal time forward");
_LIT(KTestString4,"Change clock separator");
_LIT(KTestString5,"Moving clock to right");
_LIT(KTestString6,"Set a new background color");
_LIT(KTestString7,"Restore previos background color");
_LIT(KTestString8,"hide clocks");
_LIT(KTestStarted,"Test Started");
_LIT(KTestFinished,"Test Finished");

// enums, structs and classes


// local functions

LOCAL_C TInt PanickingFunction(TAny* aPtr)
	{
	SPanickingFunctionData* data=(SPanickingFunctionData*)aPtr;
	RWsSession wsSession;
	wsSession.Connect();
	RAnimDll animDll(wsSession);
	animDll.Load(_L("CLOCKA.DLL"));
	RWindowGroup windowGroup(wsSession);
	windowGroup.Construct(NULL);
	windowGroup.SetOwningWindowGroup(data->iMainWindowGroup);
	RWindow window(wsSession);
	window.Construct(windowGroup, NULL);
	CWsScreenDevice* wsScreenDevice=new CWsScreenDevice(wsSession);
	wsScreenDevice->Construct();
	CDestructableFont* font=new CDestructableFont(wsScreenDevice);
	font->ConstructL(TFontSpec(_L("arial"), wsScreenDevice->VerticalPixelsToTwips(60)));
	TInt fontHandle=font->Handle();
	STimeDeviceShadow shadow;
	shadow.iIsOn=EFalse;
	TRgb color(255, 255, 255);
	TPoint position(10, 0);
	TSize size(0, 10);
	TInt seconds(20*60);
	TMargins margins;
	margins.iLeft=0;
	margins.iRight=0;
	margins.iTop=0;
	margins.iBottom=0;
	TBuf<64> digitalClockFormat=_L("any old thing");
	TDigitalDisplayTextSection digitalDisplayTextSection(fontHandle, color, EDigitalDisplayHorizontalTextAlignmentCenter,
																	EDigitalDisplayVerticalTextAlignmentBottomInclDescent,
																	0, 0, digitalClockFormat);
	RDigitalClock digitalClock(animDll, window);
	CFbsBitmap* analogClockFace0=new(ELeave) CFbsBitmap;
	analogClockFace0->Load(TCLCK0_MBM, CLOCK);
	CFbsBitmap* analogClockFace1=new(ELeave) CFbsBitmap;
	analogClockFace1->Load(TCLCK0_MBM, CLOCK);
	TInt analogClockFaceHandle0=analogClockFace0->Handle();
	TInt analogClockFaceHandle1=analogClockFace1->Handle();
	TAnalogDisplayHand analogClockHandWithNoFeatures(EAnalogDisplayHandOneRevPerMinute);
	TAnalogDisplayHand analogClockHand(EAnalogDisplayHandOneRevPerMinute);
	analogClockHand.AddCircle(CGraphicsContext::EDashedPen, color, size, CGraphicsContext::ESolidBrush, color, position, 8);
	RAnalogClock analogClock(animDll, window);

	// the last line of each of these cases should panic
	switch (data->iFunction)
		{
	case ECreateDigitalClockWithNoConstructCall:
		digitalClock.AddTextSectionL(digitalDisplayTextSection);
		break;
	case ECreateDigitalClockWithTooManyConstructCalls:
		digitalClock.ConstructL(seconds, position, size, margins, shadow, color, 1);
		digitalClock.ConstructL(seconds, position, size, margins, shadow, color, 1);
		break;
	case ECreateDigitalClockWithNoTextSections:
		digitalClock.ConstructL(seconds, position, size, margins, shadow, color, 0);
		break;
	case ECreateDigitalClockWithTooManyTextSections:
		digitalClock.ConstructL(seconds, position, size, margins, shadow, color, 2);
		digitalClock.AddTextSectionL(digitalDisplayTextSection);
		digitalClock.AddTextSectionL(digitalDisplayTextSection);
		digitalClock.AddTextSectionL(digitalDisplayTextSection);
		break;
	case ECreateDigitalClockWithNonNormalizedRect:
		digitalClock.ConstructL(seconds, position, TSize(-1, 0), margins, shadow, color, 1);
		break;
	case ECreateAnalogClockWithNoConstructCall:
		analogClock.AddHandL(analogClockHand);
		break;
	case ECreateAnalogClockWithTooManyConstructCalls:
		analogClock.ConstructL(seconds, position, size, margins, shadow, analogClockFaceHandle0, 0, 2);
		analogClock.ConstructL(seconds, position, size, margins, shadow, analogClockFaceHandle1, 0, 2);
		break;
	case ECreateAnalogClockWithNoHands:
		analogClock.ConstructL(seconds, position, size, margins, shadow, analogClockFaceHandle0, 0, 0);
		break;
	case ECreateAnalogClockWithTooManyHands:
		analogClock.ConstructL(seconds, position, size, margins, shadow, analogClockFaceHandle0, 0, 2);
		analogClock.AddHandL(analogClockHand);
		analogClock.AddHandL(analogClockHand);
		analogClock.AddHandL(analogClockHand);
		break;
	case ECreateAnalogClockWithHandWithNoFeatures:
		analogClock.ConstructL(seconds, position, size, margins, shadow, analogClockFaceHandle0, 0, 1);
		analogClock.AddHandL(analogClockHandWithNoFeatures);
		break;
		}

	return 0;
	}

// CDestructableFont

CDestructableFont::CDestructableFont(CWsScreenDevice* aScreenDevice)
	:iScreenDevice(aScreenDevice)
	{
	}

void CDestructableFont::ConstructL(const TFontSpec& aFontSpec)
	{
	User::LeaveIfError(iScreenDevice->GetNearestFontInTwips((CFont*&)iFont, aFontSpec));
	}

CDestructableFont::~CDestructableFont()
	{
	iScreenDevice->ReleaseFont(iFont); // N.B. do not need to do "delete iFont"
	}

TInt CDestructableFont::Handle() const
	{
	return iFont->Handle();
	}

// CClkControl

CClkControl::CClkControl()
	:iBackgroundColor(85, 85, 85),
	 iAnimDll(iCoeEnv->WsSession()),
	 iDigitalClock0Position(250, 125),
	 iDigitalClock0Size(180, 70),
	 iAnalogClock0Position(10, 5),
	 iAnalogClock0Size(200, 200),
	 iUniversalTimeOffset(0)
	{
	__DECLARE_NAME(_S("CClkControl"));

	__ASSERT_DEBUG(iDigitalClock0==NULL, User::Panic(_L("Clock test-code"), 1));
	__ASSERT_DEBUG(iAnalogClock0==NULL, User::Panic(_L("Clock test-code"), 2));
	}

void CClkControl::ConstructL()
	{
	// CONE construction stuff
	CreateWindowL();
	Window().SetBackgroundColor(iBackgroundColor);
	SetExtent(TPoint(10, 10), TSize(620, 220));
	ActivateL();
	User::LeaveIfError(iAnimDll.Load(_L("CLOCKA.DLL")));

#if (0)
	TTime time;
	time.HomeTime();
	TDateTime dateTime=time.DateTime();
	User::SetHomeTime(TTime(TDateTime(dateTime.Year(), dateTime.Month(), dateTime.Day(), 10, 11, 0, 0)));
	time=time.DateTime();
#endif

	// clock construction stuff
	TestForDegenerateClockCreationL();
	CreateDigitalClocksL();
	CreateAnalogClocksL();
	}

CClkControl::~CClkControl()
	{
	if (iDigitalClock0!=NULL)
		iDigitalClock0->Destroy();
	if (iAnalogClock0!=NULL)
		iAnalogClock0->Destroy();
	iAnimDll.Close();
	
	}

TKeyResponse CClkControl::OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType)
	{
	if (aType==EEventKey)
		{
		if (aKeyEvent.iModifiers&EModifierFunc)
			{
			TPoint increment(0, 0);
			TInt incrementMagnitude=(aKeyEvent.iModifiers&EModifierCtrl)? 5: 1;
			switch(aKeyEvent.iCode)
				{
			case EKeyLeftArrow:
				increment.iX=-incrementMagnitude;
				goto setDigitalClockSize;
			case EKeyRightArrow:
				increment.iX=incrementMagnitude;
				goto setDigitalClockSize;
			case EKeyUpArrow:
				increment.iY=-incrementMagnitude;
				goto setDigitalClockSize;
			case EKeyDownArrow:
				increment.iY=incrementMagnitude;
				goto setDigitalClockSize;
			setDigitalClockSize:
				iDigitalClock0Size+=increment;
				iAnalogClock0Size+=increment;
				iDigitalClock0->SetPositionAndSize(iDigitalClock0Position, iDigitalClock0Size);
				iAnalogClock0->SetPositionAndSize(iAnalogClock0Position, iAnalogClock0Size);
				break;
				}
			}
		else
			{
			TInt adjust=0;
			switch(aKeyEvent.iCode)
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
		}

	return EKeyWasConsumed;
	}

void CClkControl::HandlePointerEventL(const TPointerEvent& aPointerEvent)
	{
//	CCoeEnv* coeEnv = CCoeEnv::Static();
//	CTestClckUi* theApplication = (CTestClckUi*) (coeEnv->AppUi());

	switch (aPointerEvent.iType)
		{
	case TPointerEvent::EButton1Down:
		if (aPointerEvent.iModifiers&EModifierShift)
			{
			iDigitalClock0Position=aPointerEvent.iPosition;
			iDigitalClock0->SetPositionAndSize(iDigitalClock0Position, iDigitalClock0Size);
			}
		else
			{
			iAnalogClock0Position=aPointerEvent.iPosition;
			iAnalogClock0->SetPositionAndSize(iAnalogClock0Position, iAnalogClock0Size);
			}
		break;
	default: // dummy default to prevent gcc compiler warning
		break;
		}
	}

void CClkControl::Draw(const TRect&) const
	{
	CGraphicsContext& systemGc=SystemGc();
	systemGc.SetPenStyle(CGraphicsContext::ENullPen);
	systemGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	systemGc.SetBrushColor(iBackgroundColor);
	systemGc.DrawRect(Rect());
	}

void CClkControl::TestForDegenerateClockCreationL()
	{
	// test deleting partially created clocks
	TestClosingPartiallyCreatedDigitalClocksL();
	TestClosingPartiallyCreatedAnalogClocksL();

	// test for panics
	/**
	TBool oldJustInTimeDebugging=User::JustInTime();
	User::SetJustInTime(EFalse);
	SPanickingFunctionData data;
	data.iMainWindowGroup=iCoeEnv->RootWin().Identifier();
	data.iFunction=ECreateDigitalClockWithNoConstructCall;
	FireOffNewThreadAndTestForPanicL(&data);
	data.iFunction=ECreateDigitalClockWithTooManyConstructCalls;
	FireOffNewThreadAndTestForPanicL(&data);
	data.iFunction=ECreateDigitalClockWithNoTextSections;
	FireOffNewThreadAndTestForPanicL(&data);
	data.iFunction=ECreateDigitalClockWithTooManyTextSections;
	FireOffNewThreadAndTestForPanicL(&data);
	data.iFunction=ECreateDigitalClockWithNonNormalizedRect;
	FireOffNewThreadAndTestForPanicL(&data);
	data.iFunction=ECreateAnalogClockWithNoConstructCall;
	FireOffNewThreadAndTestForPanicL(&data);
	data.iFunction=ECreateAnalogClockWithTooManyConstructCalls;
	FireOffNewThreadAndTestForPanicL(&data);
	data.iFunction=ECreateAnalogClockWithNoHands;
	FireOffNewThreadAndTestForPanicL(&data);
	data.iFunction=ECreateAnalogClockWithTooManyHands;
	FireOffNewThreadAndTestForPanicL(&data);
	data.iFunction=ECreateAnalogClockWithHandWithNoFeatures;
	FireOffNewThreadAndTestForPanicL(&data);
	User::SetJustInTime(oldJustInTimeDebugging);*/
	}

void CClkControl::TestClosingPartiallyCreatedDigitalClocksL()
	{
	CWsScreenDevice* screenDevice=iCoeEnv->ScreenDevice();
	TRgb color(97, 97, 97);
	TPoint position(35, -35);
	TSize size(100, 50);
	TMargins margins;
	margins.iLeft=0;
	margins.iRight=0;
	margins.iTop=0;
	margins.iBottom=0;

	RDigitalClock tempDigitalClock0(iAnimDll, Window());
	tempDigitalClock0.Close();
	RDigitalClock tempDigitalClock1(iAnimDll, Window());
	RDigitalClock tempDigitalClock2(iAnimDll, Window());
	STimeDeviceShadow tempDigitalClock2Shadow;
	tempDigitalClock2Shadow.iIsOn=EFalse;
	tempDigitalClock2.ConstructL(TTimeIntervalSeconds(20*60), position, size, margins, tempDigitalClock2Shadow,
																color, 3);
	RDigitalClock tempDigitalClock3(iAnimDll, Window());
	STimeDeviceShadow tempDigitalClock3Shadow;
	tempDigitalClock3Shadow.iIsOn=EFalse;
	tempDigitalClock3.ConstructL(TTimeIntervalSeconds(20*60), position, size, margins, tempDigitalClock2Shadow,
																color, 3);
	TBuf<64> tempDigitalClock3Format0=_L("");
	tempDigitalClock3Format0.Append(_L("%*J"));
	tempDigitalClock3Format0.Append(TChar(EDigitalDisplayLayoutCharFlashingBlockDelimiter));
	tempDigitalClock3Format0.Append(_L("%:1"));
	tempDigitalClock3Format0.Append(TChar(EDigitalDisplayLayoutCharFlashingBlockDelimiter));
	tempDigitalClock3Format0.Append(_L("%T"));
	tempDigitalClock3Format0.Append(TChar(EDigitalDisplayLayoutCharFlashingBlockDelimiter));
	tempDigitalClock3Format0.Append(_L("%:2"));
	tempDigitalClock3Format0.Append(TChar(EDigitalDisplayLayoutCharFlashingBlockDelimiter));
	tempDigitalClock3Format0.Append(_L("%S %B"));
	CDestructableFont* tempDigitalClock3Font0=new(ELeave) CDestructableFont(screenDevice);
	tempDigitalClock3Font0->ConstructL(TFontSpec(_L("arial"), screenDevice->VerticalPixelsToTwips(60)));
	tempDigitalClock3.AddTextSectionL(TDigitalDisplayTextSection(tempDigitalClock3Font0->Handle(), TRgb(0, 0, 0),
																EDigitalDisplayHorizontalTextAlignmentCenter,
																EDigitalDisplayVerticalTextAlignmentCenterExclDescent,
																0, 0, tempDigitalClock3Format0));
	RDigitalClock tempDigitalClock4(iAnimDll, Window());
	STimeDeviceShadow tempDigitalClock4Shadow;
	tempDigitalClock4Shadow.iIsOn=EFalse;
	tempDigitalClock4.ConstructL(TTimeIntervalSeconds(20*60), position, size, margins, tempDigitalClock4Shadow,
																color, 3);
	RDigitalClock tempDigitalClock5(iAnimDll, Window());
	STimeDeviceShadow tempDigitalClock5Shadow;
	tempDigitalClock5Shadow.iIsOn=EFalse;
	tempDigitalClock5.ConstructL(TTimeIntervalSeconds(20*60), position, size, margins, tempDigitalClock2Shadow,
																color, 3);
	TBuf<64> tempDigitalClock5Format0=_L("");
	tempDigitalClock5Format0.Append(_L("%*J"));
	tempDigitalClock5Format0.Append(TChar(EDigitalDisplayLayoutCharFlashingBlockDelimiter));
	tempDigitalClock5Format0.Append(_L("%:1"));
	tempDigitalClock5Format0.Append(TChar(EDigitalDisplayLayoutCharFlashingBlockDelimiter));
	tempDigitalClock5Format0.Append(_L("%T"));
	tempDigitalClock5Format0.Append(TChar(EDigitalDisplayLayoutCharFlashingBlockDelimiter));
	tempDigitalClock5Format0.Append(_L("%:2"));
	tempDigitalClock5Format0.Append(TChar(EDigitalDisplayLayoutCharFlashingBlockDelimiter));
	tempDigitalClock5Format0.Append(_L("%S %B"));
	CDestructableFont* tempDigitalClock5Font0=new(ELeave) CDestructableFont(screenDevice);
	tempDigitalClock5Font0->ConstructL(TFontSpec(_L("arial"), screenDevice->VerticalPixelsToTwips(60)));
	tempDigitalClock5.AddTextSectionL(TDigitalDisplayTextSection(tempDigitalClock5Font0->Handle(), TRgb(0, 0, 0),
																EDigitalDisplayHorizontalTextAlignmentCenter,
																EDigitalDisplayVerticalTextAlignmentCenterExclDescent,
																0, 0, tempDigitalClock5Format0));
	tempDigitalClock2.Close();
	tempDigitalClock1.Close();
	tempDigitalClock3.Close();
	tempDigitalClock4.Close();
	tempDigitalClock5.Close();
	delete tempDigitalClock3Font0;
	delete tempDigitalClock5Font0;
	}

void CClkControl::TestClosingPartiallyCreatedAnalogClocksL()
	{
	TRgb color(234, 234, 234);
	TPoint position(0, 0);
	TSize size(2, 0);
	RWindow& window=Window();
	TMargins margins;
	margins.iLeft=0;
	margins.iRight=0;
	margins.iTop=0;
	margins.iBottom=0;

	RAnalogClock tempAnalogClock0(iAnimDll, window);
	tempAnalogClock0.Close();
	RAnalogClock tempAnalogClock1(iAnimDll, window);
	RAnalogClock tempAnalogClock2(iAnimDll, window);
	STimeDeviceShadow tempAnalogClock2Shadow;
	tempAnalogClock2Shadow.iIsOn=EFalse;
	CFbsBitmap* tempAnalogClock2Face=new(ELeave) CFbsBitmap;
	User::LeaveIfError(tempAnalogClock2Face->Load(TCLCK0_MBM, CLOCK));
	tempAnalogClock2.ConstructL(TTimeIntervalSeconds(20*60), position, size, margins, tempAnalogClock2Shadow,
																tempAnalogClock2Face->Handle(), 0, 3);
	RAnalogClock tempAnalogClock3(iAnimDll, window);
	STimeDeviceShadow tempAnalogClock3Shadow;
	tempAnalogClock3Shadow.iIsOn=EFalse;
	CFbsBitmap* tempAnalogClock3Face=new(ELeave) CFbsBitmap;
	User::LeaveIfError(tempAnalogClock3Face->Load(TCLCK0_MBM, CLOCK));
	tempAnalogClock3.ConstructL(TTimeIntervalSeconds(20*60), position, size, margins, tempAnalogClock3Shadow,
																tempAnalogClock3Face->Handle(), 0, 3);
	TAnalogDisplayHand tempAnalogClock3Hand(EAnalogDisplayHandOneRevPerMinute);
	CArrayFix<TPoint>* tempAnalogClock3HandPointList=new(ELeave) CArrayFixFlat<TPoint>(2);
	tempAnalogClock3HandPointList->AppendL(TPoint(-10000, -10000));
	tempAnalogClock3HandPointList->AppendL(TPoint(10000, 10000));
	tempAnalogClock3Hand.AddPolyLine(CGraphicsContext::EDottedPen, color, TSize(50, 50),
																CGraphicsContext::ESolidBrush, TRgb(12, 12, 12),
																ETrue, tempAnalogClock3HandPointList);
	tempAnalogClock3Hand.AddCircle(CGraphicsContext::EDashedPen, TRgb(77, 77, 77), TSize(0, 0), CGraphicsContext::ESolidBrush,
																TRgb(77, 77, 77), TPoint(-20, 20), 9000);
	tempAnalogClock3.AddHandL(tempAnalogClock3Hand);
	tempAnalogClock3.AddHandL(tempAnalogClock3Hand); // try adding the same hand more than once
	RAnalogClock tempAnalogClock4(iAnimDll, window);
	STimeDeviceShadow tempAnalogClock4Shadow;
	tempAnalogClock4Shadow.iIsOn=ETrue;
	tempAnalogClock4Shadow.iColor=TRgb(123, 123, 123);
	tempAnalogClock4Shadow.iOffset.SetXY(1000, 1000);
	CFbsBitmap* tempAnalogClock4Face=new(ELeave) CFbsBitmap;
	User::LeaveIfError(tempAnalogClock4Face->Load(TCLCK0_MBM, CLOCK));
	tempAnalogClock4.ConstructL(TTimeIntervalSeconds(20*60), position, size, margins, tempAnalogClock4Shadow,
																tempAnalogClock4Face->Handle(), 0, /* this parameter is aNumHands: */3);
	RAnalogClock tempAnalogClock5(iAnimDll, window);
	STimeDeviceShadow tempAnalogClock5Shadow;
	tempAnalogClock5Shadow.iIsOn=ETrue;
	tempAnalogClock5Shadow.iColor=TRgb(123, 123, 123);
	tempAnalogClock5Shadow.iOffset.SetXY(1000, 1000);
	CFbsBitmap* tempAnalogClock5Face=new(ELeave) CFbsBitmap;
	User::LeaveIfError(tempAnalogClock5Face->Load(TCLCK0_MBM, CLOCK));
	tempAnalogClock5.ConstructL(TTimeIntervalSeconds(20*60), position, size, margins, tempAnalogClock5Shadow,
																tempAnalogClock5Face->Handle(), 0, /* this parameter is aNumHands: */3);
	TAnalogDisplayHand tempAnalogClock5Hand(EAnalogDisplayHandOneRevPerMinute);
	CArrayFix<TPoint>* tempAnalogClock5HandPointList=new(ELeave) CArrayFixFlat<TPoint>(2);
	tempAnalogClock5HandPointList->AppendL(TPoint(-10000, -10000));
	tempAnalogClock5HandPointList->AppendL(TPoint(10000, 10000));
	tempAnalogClock5Hand.AddPolyLine(CGraphicsContext::EDottedPen, color, TSize(50, 0),
																CGraphicsContext::ESolidBrush, TRgb(12, 12, 12),
																ETrue, tempAnalogClock5HandPointList);
	tempAnalogClock5Hand.AddCircle(CGraphicsContext::EDashedPen, TRgb(77, 77, 77), TSize(0, 0), CGraphicsContext::ESolidBrush,
																TRgb(77, 77, 77), TPoint(-20, 20), 9000);
	tempAnalogClock5.AddHandL(tempAnalogClock5Hand);
	tempAnalogClock5.AddHandL(tempAnalogClock5Hand); // try adding the same hand more than once
	tempAnalogClock2.Close();
	tempAnalogClock1.Close();
	tempAnalogClock3.Close();
	tempAnalogClock4.Close();
	tempAnalogClock5.Close();
	delete tempAnalogClock2Face;
	delete tempAnalogClock3Face;
	delete tempAnalogClock3HandPointList;
	delete tempAnalogClock4Face;
	delete tempAnalogClock5Face;
	delete tempAnalogClock5HandPointList;
	}

void CClkControl::FireOffNewThreadAndTestForPanicL(TAny* aData)
	{
	RThread thread;
	TRequestStatus status;
	User::LeaveIfError(thread.Create(_L("test-thread"), PanickingFunction, 0x2000, 0x2000, 0x2000, aData));
	thread.Logon(status);
	thread.Resume();
	User::WaitForRequest(status);
	if (thread.ExitType()!=EExitPanic)
		User::Leave(KErrGeneral);
	thread.Close();
	}

void CClkControl::CreateDigitalClocksL()
	{
	CWsScreenDevice* screenDevice=iCoeEnv->ScreenDevice();
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
	iDigitalClock0=new(ELeave) RDigitalClock(iAnimDll, Window());
	iDigitalClock0->ConstructL(TTimeIntervalSeconds(30*60), iDigitalClock0Position, iDigitalClock0Size, margins, digitalClock0Shadow, TRgb(170, 170, 170), 2);
	//
	TBuf<64> digitalClock0Format0=_L(""); // N.B. this string will contain 22 characters i.e. *not* a multiple of 4-bytes
	digitalClock0Format0.Append(_L("%-B%J"));
	digitalClock0Format0.Append(TChar(EDigitalDisplayLayoutCharFlashingBlockDelimiter));
	digitalClock0Format0.Append(_L("%:1"));
	digitalClock0Format0.Append(TChar(EDigitalDisplayLayoutCharFlashingBlockDelimiter));
	digitalClock0Format0.Append(_L("%T"));
	digitalClock0Format0.Append(TChar(EDigitalDisplayLayoutCharFlashingBlockDelimiter));
	digitalClock0Format0.Append(_L("%:2"));
	digitalClock0Format0.Append(TChar(EDigitalDisplayLayoutCharFlashingBlockDelimiter));
	digitalClock0Format0.Append(_L("%S%+B"));
	CDestructableFont* digitalClock0Font0=new(ELeave) CDestructableFont(screenDevice);
	CleanupStack::PushL(digitalClock0Font0);
	TFontSpec digitalClock0FontSpec0(_L("arial"), screenDevice->VerticalPixelsToTwips(25));
	digitalClock0FontSpec0.iFontStyle.SetPosture(EPostureItalic);
	digitalClock0FontSpec0.iFontStyle.SetStrokeWeight(EStrokeWeightBold);
	digitalClock0Font0->ConstructL(digitalClock0FontSpec0);
	iDigitalClock0->AddTextSectionL(TDigitalDisplayTextSection(digitalClock0Font0->Handle(), TRgb(0, 0, 0),
																EDigitalDisplayHorizontalTextAlignmentCenter,
																EDigitalDisplayVerticalTextAlignmentCenterExclDescent,
																0, 0, digitalClock0Format0));
	//
	TBuf<64> digitalClock0Format1=_L("");
	digitalClock0Format1.Append(_L("date -- %1%/1%2%/2%3")); // N.B. this string contains 20 characters i.e. a multiple of 4-bytes
	CDestructableFont* digitalClock0Font1=new(ELeave) CDestructableFont(screenDevice);
	CleanupStack::PushL(digitalClock0Font1);
	TFontSpec digitalClock0FontSpec1(_L("arial"), screenDevice->VerticalPixelsToTwips(15));
	digitalClock0FontSpec1.iFontStyle.SetStrokeWeight(EStrokeWeightBold);
	digitalClock0Font1->ConstructL(digitalClock0FontSpec1);
	iDigitalClock0->AddTextSectionL(TDigitalDisplayTextSection(digitalClock0Font1->Handle(), TRgb(255, 255, 255),
																EDigitalDisplayHorizontalTextAlignmentCenter,
																EDigitalDisplayVerticalTextAlignmentBottomInclDescent,
																0, 0, digitalClock0Format1));
	//
	CleanupStack::PopAndDestroy(); // pop and destroy digitalClock0Font1
	CleanupStack::PopAndDestroy(); // pop and destroy digitalClock0Font0
	//
	//
	//
	STimeDeviceShadow digitalClock1Shadow;
	digitalClock1Shadow.iIsOn=ETrue;
	digitalClock1Shadow.iColor=TRgb(85, 85, 85);
	digitalClock1Shadow.iOffset.SetXY(2, 2);
	//
	RDigitalClock digitalClock1(iAnimDll, Window());
	digitalClock1.ConstructL(TTimeIntervalSeconds(30*60), TPoint(0, 0), TSize(20, 20), margins, digitalClock1Shadow, TRgb(170, 170, 170), 1);
	TDigitalDisplayTextSection* textSection=NULL;
	TInt error=KErrNone;
	//
	textSection=new(ELeave) TDigitalDisplayTextSection(0, TRgb(0, 0, 0),
																EDigitalDisplayHorizontalTextAlignmentCenter,
																EDigitalDisplayVerticalTextAlignmentCenterExclDescent,
																0, 0, _L("%+"));
	TRAP(error,digitalClock1.AddTextSectionL(*textSection));
	__ASSERT_ALWAYS(error!=KErrNone, User::Panic(_L("Clock test-code"), 3));
	delete textSection;
	//
	textSection=new(ELeave) TDigitalDisplayTextSection(0, TRgb(0, 0, 0),
																EDigitalDisplayHorizontalTextAlignmentCenter,
																EDigitalDisplayVerticalTextAlignmentCenterExclDescent,
																0, 0, _L("%-"));
	TRAP(error,digitalClock1.AddTextSectionL(*textSection));
	__ASSERT_ALWAYS(error!=KErrNone, User::Panic(_L("Clock test-code"), 4));
	delete textSection;
	//
	textSection=new(ELeave) TDigitalDisplayTextSection(0, TRgb(0, 0, 0),
																EDigitalDisplayHorizontalTextAlignmentCenter,
																EDigitalDisplayVerticalTextAlignmentCenterExclDescent,
																0, 0, _L("%:_"));
	TRAP(error,digitalClock1.AddTextSectionL(*textSection));
	__ASSERT_ALWAYS(error!=KErrNone, User::Panic(_L("Clock test-code"), 6));
	delete textSection;
	//
	textSection=new(ELeave) TDigitalDisplayTextSection(0, TRgb(0, 0, 0),
																EDigitalDisplayHorizontalTextAlignmentCenter,
																EDigitalDisplayVerticalTextAlignmentCenterExclDescent,
																0, 0, _L("%/5"));
	TRAP(error,digitalClock1.AddTextSectionL(*textSection));
	__ASSERT_ALWAYS(error!=KErrNone, User::Panic(_L("Clock test-code"), 7));
	delete textSection;
	digitalClock1.Close();
	}

void CClkControl::CreateAnalogClocksL()
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
	CDestructableFont* analogClock0AmPmFont=new(ELeave) CDestructableFont(screenDevice);
	CleanupStack::PushL(analogClock0AmPmFont);
	TFontSpec analogClock0AmPmFontSpec(_L("arial"), screenDevice->VerticalPixelsToTwips(12));
	analogClock0AmPmFontSpec.iFontStyle.SetStrokeWeight(EStrokeWeightBold);
	analogClock0AmPmFont->ConstructL(analogClock0AmPmFontSpec);
	//
	SAnalogDisplayAmPm analogClock0AmPm;
	analogClock0AmPm.iPositionRelativeToFace=TPoint(174, 103);
	analogClock0AmPm.iShadow.iIsOn=EFalse;
	analogClock0AmPm.iShadow.iColor=TRgb(85, 85, 85);
	analogClock0AmPm.iShadow.iOffset.SetXY(2, 2);
	analogClock0AmPm.iSize.SetSize(18, 13);
	analogClock0AmPm.iBackgroundColor=TRgb(255, 255, 255);
	analogClock0AmPm.iFontHandle=analogClock0AmPmFont->Handle();
	analogClock0AmPm.iTextColor=TRgb(0, 0, 0);
	//
	CFbsBitmap* analogClock0Face=new(ELeave) CFbsBitmap;
	CleanupStack::PushL(analogClock0Face);
	User::LeaveIfError(analogClock0Face->Load(TCLCK0_MBM, CLOCK));
	analogClock0Face->SetSizeInTwips(screenDevice);
	CFbsBitmap* analogClock0FaceMask=new(ELeave) CFbsBitmap;
	CleanupStack::PushL(analogClock0FaceMask);
	User::LeaveIfError(analogClock0FaceMask->Load(TCLCK0_MBM, CLOCKMSK));
	analogClock0FaceMask->SetSizeInTwips(screenDevice);
	//
	iAnalogClock0=new(ELeave) RAnalogClock(iAnimDll, Window());
	iAnalogClock0->ConstructL(TTimeIntervalSeconds(30*60), iAnalogClock0Position, iAnalogClock0Size, margins, analogClock0Shadow,
								analogClock0Face->Handle(), analogClock0FaceMask->Handle(), 3, &analogClock0AmPm);
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
	analogClock0SecondHand.AddLine(CGraphicsContext::ESolidPen, black, TSize(1, 1), TPoint(0, 40), TPoint(0, -60));
	analogClock0SecondHand.AddCircle(CGraphicsContext::ESolidPen, black, TSize(2, 2), CGraphicsContext::ENullBrush, black, TPoint(0, -65), 5);
	analogClock0SecondHand.AddLine(CGraphicsContext::ESolidPen, black, TSize(1, 1), TPoint(0, -70), TPoint(0, -80));
	pointList->AppendL(TPoint(-16, 33));
	pointList->AppendL(TPoint(0, 7));
	pointList->AppendL(TPoint(16, 33));
	pointList->AppendL(TPoint(0, 14));
	analogClock0SecondHand.AddPolyLine(CGraphicsContext::ESolidPen, black, TSize(1, 1), CGraphicsContext::ESolidBrush, TRgb(170, 170, 170), ETrue, pointList);
	pointList->Reset();
	pointList->AppendL(TPoint(-16, 39));
	pointList->AppendL(TPoint(0, 21));
	pointList->AppendL(TPoint(16, 39));
	pointList->AppendL(TPoint(0, 28));
	analogClock0SecondHand.AddPolyLine(CGraphicsContext::ESolidPen, black, TSize(1, 1), CGraphicsContext::ENullBrush, black, ETrue, pointList);
	pointList->Reset();
	pointList->AppendL(TPoint(-16, 45));
	pointList->AppendL(TPoint(0, 35));
	pointList->AppendL(TPoint(16, 45));
	analogClock0SecondHand.AddPolyLine(CGraphicsContext::ESolidPen, black, TSize(1, 1), CGraphicsContext::ENullBrush, black, EFalse, pointList);
	pointList->Reset();
	iAnalogClock0->AddHandL(analogClock0SecondHand);
	//
	CleanupStack::PopAndDestroy(); // pop and destroy pointList
	CleanupStack::PopAndDestroy(); // pop and destroy analogClock0FaceMask
	CleanupStack::PopAndDestroy(); // pop and destroy analogClock0Face
	CleanupStack::PopAndDestroy(); // pop and destroy analogClock0AmPmFont
	}


CTestClckUi::CTestClckUi(CTmsTestStep* aStep) :
	CTestCoeAppUi(aStep)
	{}


void CTestClckUi::ConstructL()
	{
	CTestCoeAppUi::ConstructL();
	iControl=new(ELeave) CClkControl;
	AddToStackL(iControl,ECoeStackPriorityDefault,ECoeStackFlagOwnershipTransfered);
	iControl->ConstructL();
	AutoTestManager().StartAutoTest();
	}

/**
   @SYMTestCaseID UIF-Clock-TClock0
 */

void CTestClckUi::RunTestStepL(TInt aNumStep)
	{
	TKeyEvent theKeyEvent;
	TEventCode theType = EEventKey;
	
	//only for debug
	User::After(TTimeIntervalMicroSeconds32(1000000));
	_LIT(KTestString1,"Show analog & digital clocks");
	
	switch(aNumStep)
		{
		case 1:
		SetTestStepID(_L("UIF-Clock-TClock0"));	// for TMS
		theKeyEvent.iCode = EKeyEnter;
		theKeyEvent.iModifiers = 0;
		
		iControl->OfferKeyEventL(theKeyEvent, theType);
		
		INFO_PRINTF1(KTestString1);
		break;
		
		case 2: case 3: case 4: case 5:
		theKeyEvent.iCode = EKeyLeftArrow;
		theKeyEvent.iModifiers = 0;
		
		iControl->OfferKeyEventL(theKeyEvent, theType);
		INFO_PRINTF1(KTestString2);
		break;

		case 6: case 7: case 8: case 9:
		theKeyEvent.iCode = EKeyRightArrow;
		theKeyEvent.iModifiers = 0;
		
		iControl->OfferKeyEventL(theKeyEvent, theType);
		INFO_PRINTF1(KTestString3);
		break;

		case 10:
		theKeyEvent.iCode = '*';
		theKeyEvent.iModifiers = 0;
		
		iControl->OfferKeyEventL(theKeyEvent, theType);
		INFO_PRINTF1(KTestString4);
		break;

		case 11: case 12: case 13: case 14: 
		theKeyEvent.iCode = EKeyRightArrow;
		theKeyEvent.iModifiers = EModifierFunc | EModifierCtrl;
		
		iControl->OfferKeyEventL(theKeyEvent, theType);
		INFO_PRINTF1(KTestString5);
		break;
		case 15:  
		theKeyEvent.iCode = EKeySpace;
		theKeyEvent.iModifiers = EModifierShift;
		
		iControl->OfferKeyEventL(theKeyEvent, theType);
		INFO_PRINTF1(KTestString6);
		break;

		case 16:  
		theKeyEvent.iCode = EKeySpace;
		theKeyEvent.iModifiers = 0;
		
		iControl->OfferKeyEventL(theKeyEvent, theType);
		INFO_PRINTF1(KTestString7);
		break;

		case 17:
		theKeyEvent.iCode = EKeyEnter;
		theKeyEvent.iModifiers = EModifierShift;
		
		iControl->OfferKeyEventL(theKeyEvent, theType);
		INFO_PRINTF1(KTestString8);
		RecordTestResultL();	// for TMS
		CloseTMSGraphicsStep();
		break;

		case 18:
			AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
		}
	}
// main functions

void CTClck0Step::ConstructAppL(CCoeEnv* aCoeEnv)
	{
	aCoeEnv->ConstructL();
	CTestClckUi* appUi=new(ELeave) CTestClckUi(this);
	appUi->ConstructL();
	aCoeEnv->SetAppUi(appUi);
	}


CTClck0Step::~CTClck0Step()
/**
   Destructor
 */
	{
	}

CTClck0Step::CTClck0Step()
/**
   Constructor
 */
	{
	// Call base class method to set up the human readable name for logging
	SetTestStepName(KTClck0Step);
	}

TVerdict CTClck0Step::doTestStepL()
	{
	INFO_PRINTF1(KTestStarted);
	
	PreallocateHALBuffer();

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
	
	INFO_PRINTF1(KTestFinished);
	return TestStepResult();
	}



