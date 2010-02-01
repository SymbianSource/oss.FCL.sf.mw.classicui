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
// framework visibility event receipt and dispatch to registered message monitor observers.
// Creates a three control(window) application (main control(window) and two children).
// The two children are flagged to windows server as generators of visibility events.
// The application is registered to the framework as a message monitor observer and handles the relevant TWsVisibilityChangedEvent messages.
// One window is moved on and off the other window and the visibility status is compared to that expected.
// The visibility status returned should match the status of the control as visible or not visible, which is handled
// specifically in each test step.
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code 
  @SYMTestCaseID UIF-Cone-TConeVisibility
 @SYMPREQ 915
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
#include "TConeVisibility.h"
#include "gdi.h"


//Draw the control, different colours are used depending on status although this is for cosmetic purposes and is not required
//by the test.
void CVisibleControl::Draw(const TRect& aRect) const
    {
    
    CWindowGc& gc=SystemGc();

	TRect rc = Rect();

	gc.SetClippingRect(aRect);	
    
  	gc.SetPenColor(KRgbBlack);
  	
    	switch (iStatus)
    	{
    		case EPartial:			gc.SetBrushColor(KRgbBlue);		break;
    		case EHidden:			gc.SetBrushColor(KRgbRed);		break;
    		case EPartiallyVisible:	gc.SetBrushColor(KRgbGreen);	break;    		
    		case ENone:				gc.SetBrushColor(KRgbYellow);	break;
    		case EFullyVisible:		gc.SetBrushColor(KRgbMagenta);	break; 
			default:				gc.SetBrushColor(KRgbBlack);	break; 
    	}
    	
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.DrawRect(rc);  
	gc.CancelClippingRect();		    			
	
    }

	
//Construct the main background control. A parent control with two child controls that receive visibility events.
void CVisibilityBackground::ConstructL()
    {
    CreateWindowL();   
    SetExtent(TPoint(20,20),TSize(600,200));
    	
    iControl1 = new (ELeave) CVisibleControl();
    iControl1->CreateWindowL(this);
    iControl1->SetExtent(TPoint(200,36),TSize(128,128));
    iControl1->ActivateL();

    iControl2 = new (ELeave) CVisibleControl();
    iControl2->CreateWindowL(this);
    iControl2->SetExtent(TPoint(200,36),TSize(128,128));
    iControl2->ActivateL();

	//Enable visibility events for both these windows.
	iControl1->DrawableWindow()->EnableVisibilityChangeEvents();
	iControl2->DrawableWindow()->EnableVisibilityChangeEvents();

    ActivateL();    
    }


//Destruction of the main control content
CVisibilityBackground::~CVisibilityBackground()
    {
	delete iControl1;
    delete iControl2;
    }

	
//Standard implementation	
CTConeVisibilityAppUi::CTConeVisibilityAppUi(CTmsTestStep* aStep) :
CTestCoeAppUi(aStep)
{}

//Destruction of the application
CTConeVisibilityAppUi::~CTConeVisibilityAppUi()
	{
	RemoveFromStack(iViewControl);
	delete iViewControl;
	}


//Standard Implementation	
void CTConeVisibilityAppUi::ConstructL()
	{
	CTestCoeAppUi::ConstructL();
	
    iViewControl=new(ELeave) CVisibilityBackground();        
    iViewControl->ConstructL();        
    AddToStackL(iViewControl);
    
    //Register this MCoeVisibilityChangeObserver class as a cone visibility observer. 
	CCoeEnv::Static()->AddMessageMonitorObserverL(*this);
	    
	AutoTestManager().StartAutoTest();	
	}

//Standard Implementation	
TKeyResponse CTConeVisibilityAppUi::HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
	TKeyResponse ret=EKeyWasNotConsumed;
    if (aType==EEventKey && aKeyEvent.iCode==CTRL('e'))
		{
		CBaActiveScheduler::Exit();
		ret=EKeyWasConsumed;
		}
	return ret;
    }

//The test case/steps, not that the TEST statement compares the result for the PREVIOUS test step.
void CTConeVisibilityAppUi::RunTestStepL(TInt aStepNum)
	{	
		switch (aStepNum)
			{
			case 1:		
				SetTestStepID( _L("UIF-cone-TConeVisibility"));
				//Overlap control1 (expect visible)
		    	iViewControl->iControl2->SetExtent(TPoint(300,36),TSize(128,128));
                iViewControl->iControl2->ControlEnv()->WsSession().Flush();
				User::After(TTimeIntervalMicroSeconds32(1000000));
		    	break;
		
			case 2:
				//Test result 1 
		    	TEST(iViewControl->iControl1->iStatus == CVisibleControl::EPartiallyVisible);			

				//Occlude control1 (expect hidden)
		    	iViewControl->iControl2->SetExtent(TPoint(200,36),TSize(128,128));
		    	iViewControl->iControl2->ControlEnv()->WsSession().Flush();
				User::After(TTimeIntervalMicroSeconds32(1000000));
				break;
				
			case 3:			
				//Test result 2
    			TEST(iViewControl->iControl1->iStatus == CVisibleControl::EHidden);			

				//Set next to control1 the window, not-overlapped (expect visible)
		    	iViewControl->iControl2->SetExtent(TPoint(450,36),TSize(128,128));
		    	iViewControl->iControl2->ControlEnv()->WsSession().Flush();
				User::After(TTimeIntervalMicroSeconds32(1000000));
				break;
				
			case 4:			
				//Test result 3
    			TEST( iViewControl->iControl1->iStatus == CVisibleControl::EPartiallyVisible | CVisibleControl::EFullyVisible);			

				//Occlude control1 (expect hidden)
		    	iViewControl->iControl2->SetExtent(TPoint(200,36),TSize(128,128));
	            iViewControl->iControl2->ControlEnv()->WsSession().Flush();
				User::After(TTimeIntervalMicroSeconds32(1000000));
				break;
				
			case 5:			
				//Test result 4
    			TEST(iViewControl->iControl1->iStatus == CVisibleControl::EHidden);		
				break;
				
			case 6:
			   	//Unregister this MCoeVisibilityChangeObserver. 
				CCoeEnv::Static()->RemoveMessageMonitorObserver(*this);
				RecordTestResultL();
				CloseTMSGraphicsStep();
				break;
				
			default:	    			
	    		AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
		}		
	}

//Overidden visibility message monitor/

void CTConeVisibilityAppUi::MonitorWsMessage(const TWsEvent& aEvent)
{		
	//Check for visibility events, the only event we are interested in
	if (aEvent.Type() == EEventWindowVisibilityChanged) 
		{
			const TWsVisibilityChangedEvent *pVC = aEvent.VisibilityChanged();
			
		//The window handle for cone controls is the CCoeControl pointer. We know we only receive
		//events on specific windows so it is safe to cast them.
		CVisibleControl *pControl = REINTERPRET_CAST(CVisibleControl *, aEvent.Handle());
		
		if (pControl)
			{
			//Set the received visibility status of this control
			pControl->iStatus = pVC->iFlags;
			//Call a redraw event.
			pControl->DrawDeferred();
			}
		}
}

//Construct application
void CTConeVisibilityStep::ConstructAppL(CCoeEnv* aCoe)
	{ // runs inside a TRAP harness
	aCoe->ConstructL();
	CTConeVisibilityAppUi* appUi= new (ELeave) CTConeVisibilityAppUi(this);
	aCoe->SetAppUi(appUi);
	appUi->ConstructL();
	
	}

//Default implementation
CTConeVisibilityStep::CTConeVisibilityStep()
	{
	SetTestStepName(KTConeVisibilityStep);
	}

//Default implementation
CTConeVisibilityStep::~CTConeVisibilityStep()
	{}

//Default implementation
TVerdict CTConeVisibilityStep::doTestStepL() // main function called by E32
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
