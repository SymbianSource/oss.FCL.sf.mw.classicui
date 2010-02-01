// Copyright (c) 2008-2009 Nokia Corporation and/or its subsidiary(-ies).
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
// Tests semi-transparent window owning control with background display properly when having a child window
// owning semi-transparent control.
// Creats a window application with two semi-transparent window owning parent controls both with background. 
// A semi-transparent child window owning control is created for each parent control. One of the child control
// enables transparent property properly, the other does not. 
// The child control which enables transparent property properly should not cause the background of parent control
// to redraw thus in all circumstance its parent control background drawing count should be less than the one doesn't
// enable transparent control with provided function.
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code 
  @SYMTestCaseID UIF-Cone-TConeTransparency
 @SYMPREQ 000
 @SYMTestCaseDesc
 @SYMTestPriority Medium
 @SYMTestStatus Implemented
 @SYMTestActions
 @SYMTestExpectedResults
*/


#include <coeaui.h>
#include <coemain.h>
#include <coedef.h>
#include <coesndpy.h>
#include <basched.h>
#include <bassnd.h>
#include <coeccntx.h>
#include <ecom/ecom.h>
#include "TConeTransparency.h"
#include "gdi.h"

//From MCoeControlBackground, has a mutable iBackgroundDrawnCount to measure how many times the background is drawn
void CTransparencyParentControl::Draw(CWindowGc &aGc, const CCoeControl &/*aControl*/, const TRect &aRect) const
	{
	
	aGc.SetClippingRect(aRect);
	aGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	aGc.SetBrushColor(TRgb(255,0,0,127));
	for(TInt i = 0; i < aRect.Width(); i+=10)
	{
	TRect stripe(aRect.iTl.iX + i, aRect.iTl.iY, aRect.iTl.iX + i+5, aRect.iBr.iY); 
	aGc.DrawRect(stripe);
	}
	aGc.CancelClippingRect();
	iBackgroundDrawnCount++;
	}

//Draw the control
void CTransparentControl::Draw(const TRect& aRect) const
    {
    
    CWindowGc& gc=SystemGc();

	TRect rc = Rect();

	gc.SetClippingRect(aRect);	
    
   	gc.SetPenColor(TRgb(0,0,0,127));
    gc.SetBrushColor(TRgb(255,0,0,127));
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.DrawEllipse(rc);  
	gc.CancelClippingRect();		    			
	
    }

	
//Construct the main background control. A parent control with a child control
void CTransparencyParentControl::ConstructL(TBool aEnableTransparencyProperly)
    {
    CreateWindowL();   
    TInt xPosOffset = 0;
    if(aEnableTransparencyProperly)
    	xPosOffset = 300;
    SetExtent(TPoint(20+xPosOffset  ,20),TSize(200,200));
    SetBackground(this);
        
    iControl = new (ELeave) CTransparentControl();
    iControl->CreateWindowL(this);
    iControl->SetExtent(TPoint(50,36),TSize(128,128));
    if(aEnableTransparencyProperly)
    	{
    	iControl->EnableWindowTransparency();
    	}
    else
    	{
    	iControl->Window().SetTransparencyAlphaChannel();
    	iControl->Window().SetBackgroundColor(~0);
    	}
        
    iControl->ActivateL();

    ActivateL();    
    }


//Destruction of the main control content
CTransparencyParentControl::~CTransparencyParentControl()
    {
	delete iControl;
    }

	
//Standard implementation	
CTConeTransparencyAppUi::CTConeTransparencyAppUi(CTmsTestStep* aStep) :
CTestCoeAppUi(aStep)
{}

//Destruction of the application
CTConeTransparencyAppUi::~CTConeTransparencyAppUi()
	{
	RemoveFromStack(iViewControl1);
	delete iViewControl1;
	RemoveFromStack(iViewControl2);
	delete iViewControl2;
	}


//Standard Implementation	
void CTConeTransparencyAppUi::ConstructL()
	{
	CTestCoeAppUi::ConstructL();
	
    iViewControl1=new(ELeave) CTransparencyParentControl();        
    iViewControl1->ConstructL(EFalse);   
    iViewControl2=new(ELeave) CTransparencyParentControl();        
    iViewControl2->ConstructL(ETrue); 
    AddToStackL(iViewControl1);
    AddToStackL(iViewControl2);
      
	AutoTestManager().StartAutoTest();	
	}

//Standard Implementation	
TKeyResponse CTConeTransparencyAppUi::HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
	TKeyResponse ret=EKeyWasNotConsumed;
    if (aType==EEventKey && aKeyEvent.iCode==CTRL('e'))
		{
		CBaActiveScheduler::Exit();
		ret=EKeyWasConsumed;
		}
	return ret;
    }

//The test case/steps, a proper semi-transparent window owning child control should not cause its parent 
//window owning control's background to redraw
void CTConeTransparencyAppUi::RunTestStepL(TInt /*aStepNum*/)
	{	
		SetTestStepID(_L("@SYMTestCaseID UIF-Cone-TConeTransparency"));			
		TInt firstViewBgDrawnCount = iViewControl1->BgDrawnCount();
		TInt secondViewBgDrawnCount = iViewControl2->BgDrawnCount();
		INFO_PRINTF2(_L("Background of left picture was drawn %i time(s)"), firstViewBgDrawnCount);
		INFO_PRINTF2(_L("Background of right picture was drawn %i time(s)"), secondViewBgDrawnCount);
		if(firstViewBgDrawnCount > secondViewBgDrawnCount)
			AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
		else
			{
			INFO_PRINTF1(_L("Background of left picture was drawn fewer times than that of right, but shouldn't be."));
			AutoTestManager().FinishAllTestCases(CAutoTestManager::EFailed);
			}
		RecordTestResultL();
		CloseTMSGraphicsStep();
	}



//Construct application
void CTConeTransparencyStep::ConstructAppL(CCoeEnv* aCoe)
	{ // runs inside a TRAP harness
	aCoe->ConstructL();
	CTConeTransparencyAppUi* appUi= new (ELeave) CTConeTransparencyAppUi(this);
	aCoe->SetAppUi(appUi);
	appUi->ConstructL();
	
	}

//Default implementation
CTConeTransparencyStep::CTConeTransparencyStep()
	{
	SetTestStepName(KTConeTransparencyStep);
	}

//Default implementation
CTConeTransparencyStep::~CTConeTransparencyStep()
	{}

//Default implementation
TVerdict CTConeTransparencyStep::doTestStepL() // main function called by E32
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

	REComSession::FinalClose();	

	__UHEAP_MARKEND;

	INFO_PRINTF1(_L("Test Finished"));
	return TestStepResult();
	}
