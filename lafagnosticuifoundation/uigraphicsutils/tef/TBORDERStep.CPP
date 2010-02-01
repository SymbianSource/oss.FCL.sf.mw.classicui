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


#include <e32keys.h>
#include <basched.h>
#include <coemain.h>
#include <coeaui.h>
#include <gulutil.h>

#include "TBorderstep.h"

//
// class CSimpleControl
//


void CSimpleControl::ConstructL()
    {
    CreateWindowL();
    Window().SetShadowDisabled(ETrue);
	iAlign=CGraphicsContext::ECenter;
    SetExtentToWholeScreen();
    ActivateL();
	iBuf1 = _L("This &line has 0 margin...");
	iBuf2 = _L("and this one has a &margin of 20!");
	iRect = TRect(TPoint(40,40),TSize(560,160));
    }

TKeyResponse CSimpleControl::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    if (aType!=EEventKey)
        return(EKeyWasNotConsumed);
    TInt code=aKeyEvent.iCode;
    if (code==CTRL('e'))
        CBaActiveScheduler::Exit();
	if (code==CTRL('l'))
		iAlign=CGraphicsContext::ELeft;
	else if (code==CTRL('r'))
		iAlign=CGraphicsContext::ERight;
	else if (code==CTRL('c'))
		iAlign=CGraphicsContext::ECenter;
	else
		return(EKeyWasConsumed);
	ActivateGc();
	DrawText();
	DeactivateGc();
    return(EKeyWasConsumed);
    }

void CSimpleControl::DrawBorder(CWindowGc& aGC, TRgb aColor, TGulBorder::TBorderType aBorderType, TInt aYPos, TInt aYTextPos, const TDesC &aBorderName) const
	{
	TGulBorder border(aBorderType);
	aGC.SetClippingRect(TRect(TPoint(30,aYPos),TSize(100,20)));
	border.Draw(aGC,TRect(TPoint(30,aYPos),TSize(100,20)));
	aGC.CancelClippingRect();
	border.Draw(aGC,TRect(TPoint(140,aYPos),TSize(100,20)));
	aGC.SetPenColor(aColor);
	aGC.DrawText(aBorderName,TPoint(250,aYTextPos));
	}

void CSimpleControl::Draw(const TRect& /*aRect*/) const
	{
	CWindowGc& gc = SystemGc();
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.DrawRect(Rect());
	gc.UseFont(iCoeEnv->NormalFont());

	TInt yPos = 30;
	TInt yTextPos = 42;
	const TInt yInc = 25;

	DrawBorder(gc,KRgbBlack,TGulBorder::ENone, yPos, yTextPos,_L("ENone"));
	yTextPos+=yInc;
	yPos+=yInc;

	DrawBorder(gc,KRgbBlack,TGulBorder::ESingleBlack, yPos, yTextPos,_L("ESingleBlack"));
	yTextPos+=yInc;
	yPos+=yInc;
	
	DrawBorder(gc,KRgbBlack,TGulBorder::EShallowRaised, yPos, yTextPos,_L("EShallowRaised"));	
	yTextPos+=yInc;
	yPos+=yInc;
	
	DrawBorder(gc,KRgbBlack,TGulBorder::EDeepRaised, yPos, yTextPos,_L("EDeepRaised"));	
	yTextPos+=yInc;
	yPos+=yInc;
	
	DrawBorder(gc,KRgbBlack,TGulBorder::EShallowSunken, yPos, yTextPos,_L("EShallowSunken"));	
	yTextPos+=yInc;
	yPos+=yInc;
	
	DrawBorder(gc,KRgbBlack,TGulBorder::EDeepSunken, yPos, yTextPos,_L("EDeepSunken"));	
	yTextPos+=yInc;
	yPos+=yInc;
	
	DrawBorder(gc,KRgbBlack,TGulBorder::EThickDeepRaisedWithOutline, yPos, yTextPos,_L("EThickDeepRaisedWithOutline"));	
	yTextPos+=yInc;
	yPos+=yInc;
	}

void CSimpleControl::DrawText() const
	{ // assumes brush style is NULL on entry to routine; trashed at exit
	CWindowGc& gc = SystemGc();
	TRect rect = iRect;
	rect.Shrink(TSize(80,60));
	rect.Move(0,-30);
	const CFont* font = iCoeEnv->NormalFont();
	gc.UseFont(font);
	TRect tmp=rect;
	gc.DrawRect(tmp);
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	tmp.Shrink(1,1);
	DrawUtils::DrawText(gc,iBuf1,tmp,font->AscentInPixels()*2,iAlign,0,font);
	rect.Move(0,60);
	gc.SetBrushStyle(CGraphicsContext::ENullBrush);
	gc.DrawRect(rect);
	rect.Shrink(1,1);
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	DrawUtils::DrawText(gc,iBuf2,rect,font->AscentInPixels()*2,iAlign,20,font);
	}


CTestBorderUi::CTestBorderUi(CTmsTestStep* aStep) :
	CTestCoeAppUi(aStep)
	{}

CTestBorderUi::~CTestBorderUi()
	{
	if(iControl)
		{
//		RemoveFromStack(iControl);
//		delete iControl;
		}
	}

void CTestBorderUi::ConstructL()
	{
	CTestCoeAppUi::ConstructL();
	iControl=new(ELeave) CSimpleControl;
	AddToStackL(iControl,ECoeStackPriorityDefault,ECoeStackFlagOwnershipTransfered);
	iControl->ConstructL();

	AutoTestManager().StartAutoTest();
	}


void CTestBorderUi::RunTestStepL(TInt aStep)
	{
	TKeyEvent	theKeyEvent;


	User::After(TTimeIntervalMicroSeconds32(1000000));
	
	switch(aStep)
		{
		case 1:
		theKeyEvent.iCode = CTRL('l');
		INFO_PRINTF1(_L("Left alignment"));
		iCoeEnv->SimulateKeyEventL(theKeyEvent, EEventKey);
		break;
		case 2:
		theKeyEvent.iCode = CTRL('r');
		INFO_PRINTF1(_L("Right alignment"));
		iCoeEnv->SimulateKeyEventL(theKeyEvent, EEventKey);
		break;
		case 3:
		theKeyEvent.iCode = CTRL('c');
		INFO_PRINTF1(_L("Center alignment"));
		iCoeEnv->SimulateKeyEventL(theKeyEvent, EEventKey);
		break;
		case 4:
		AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
		break;
		}

	}

//
// Main
//

void CTBorderStep::ConstructAppL(CCoeEnv* aCoeEnv)
    { // runs inside a TRAP harness
	aCoeEnv->ConstructL();
	CTestBorderUi* appUi=new(ELeave) CTestBorderUi(this);
	appUi->ConstructL();
	aCoeEnv->SetAppUi(appUi);
    }


CTBorderStep::~CTBorderStep()
/**
   Destructor
 */
	{
	}

CTBorderStep::CTBorderStep()
/**
   Constructor
 */
	{
	// Call base class method to set up the human readable name for logging
	SetTestStepName(KTBorderStep);
	}


TVerdict CTBorderStep::doTestStepL()
	{
	INFO_PRINTF1(_L("Test Started"));

	PreallocateHALBuffer();

	__UHEAP_MARK;

    CCoeEnv* coe=new(ELeave) CCoeEnv;
    TRAPD(err,ConstructAppL(coe));
    if (!err)
        coe->ExecuteD();
		else
			{
			SetTestStepResult(EFail);
			delete coe;
			}

 	INFO_PRINTF1(_L("Test Finished"));

	__UHEAP_MARKEND;
	return TestStepResult();
	}
