// Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
 @test
*/

#include <e32std.h>
#include "COEAUI.H"
#include "tconeevents.h"

const TInt KUserEvent=60850;		//0xEDB2 - a random number that is unlikely to be used by other applicaions for user event sending

/**
 Low priority active object to unnest the Active Scheduler
*/
class CStopTheScheduler : public CAsyncOneShot
	{
public:
	inline CStopTheScheduler(TInt aPriority) : CAsyncOneShot(aPriority) {}
	//Virtual function from CActive
	void RunL();
	};

void CStopTheScheduler::RunL()
	{
	CActiveScheduler::Stop();
	}


/**
 A control to test the recieving of redraw events.
 */
class CDrawControl : public CCoeControl
	{
public:
	static CDrawControl* NewLC(TInt aPos);
	TBool HasDrawn();
protected:
	//Virtual function from CCoeControl
	void Draw(const TRect& aRect) const;
private:
	void ConstructL(TInt aPos);
	void inline Flush() {iCoeEnv->WsSession().Flush();}
private:
	__MUTABLE TBool iDrawn;
	};

/**
 Create an object and leave it on the cleanup stack
 */
CDrawControl* CDrawControl::NewLC(TInt aPos)
	{
	CDrawControl* self=new(ELeave) CDrawControl();
	CleanupStack::PushL(self);
	self->ConstructL(aPos);
	return self;
	}

/**
 Set up the control
 */
void CDrawControl::ConstructL(TInt aPos)
	{
	TSize scrSize(iCoeEnv->ScreenDevice()->SizeInPixels());
	TPoint topLeft(scrSize.iWidth/6,scrSize.iHeight/6);
	if (aPos==2)
		topLeft.SetXY(scrSize.iWidth/2-10,scrSize.iHeight/6+10);
	SetExtent(topLeft,TSize(scrSize.iWidth/3+10,scrSize.iHeight*2/3-10));
	CreateWindowL();
	Window().SetBackgroundColor(aPos==1 ? TRgb(255,85,85):TRgb(85,255,85));	//Bright Red or Green
	ActivateL();
	//iCoeEnv->WsSession().LogCommand(RWsSession::ELoggingStatusDump);		//Useful for debugging window creation problems
	DrawNow();
	Flush();
	}

/**
 Draw the controls window
 */
void CDrawControl::Draw(const TRect& aRect) const
	{
	TRect rect(aRect);
	const TSize size(aRect.Size());
	rect.Shrink(size.iWidth/5,size.iHeight/5);
	CWindowGc& gc=SystemGc();
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.SetBrushColor(TRgb(85,85,255));	//Bright Blue
	gc.DrawRect(rect);
	MUTABLE_CAST(TBool&,iDrawn)=ETrue;
	}

/**
 Return if the control has be drawn and reset the flag
 */
TBool CDrawControl::HasDrawn()
	{
	TBool drawn=iDrawn;
	iDrawn=EFalse;
	return drawn;
	}


/**
 Constructor for the APP UI for this test
 */
CConeEventsAppUi::CConeEventsAppUi(CTmsTestStep* aStep,CCoeEnv* aCoe)
	: CTestCoeAppUi(aStep), iCoe(aCoe)
	{}

/**
 Creates control for this test
 */
void CConeEventsAppUi::ConstructL()
	{
	CTestCoeAppUi::ConstructL();
	AutoTestManager().StartAutoTest();
	}

/**
 Creates control for this test
 */
void CConeEventsAppUi::HandleWsEventL(const TWsEvent& aEvent,CCoeControl* aDestination)
	{
	if (aEvent.Type()!=KUserEvent)
		CTestCoeAppUi::HandleWsEventL(aEvent,aDestination);
	else
		{
		++iEventCount;
		iCoe->WsSession().Finish();
		}
	}

/**
 @SYMTestCaseID UIF-APPFWK-CONE-0033

 @SYMDEF PDEF131541

 @SYMTestCaseDesc Tests that all events are recieved before a AO of lower priority runs.

 @SYMTestPriority High

 @SYMTestStatus Implemented

 @SYMTestActions Sends lots of events and recieves them back while low priority AO is active.

 @SYMTestExpectedResults All events are recieved before a AO of lower priority runs

 @SYMTestType Unit Test
 */
void CConeEventsAppUi::ManyEvents()
	{
	CStopTheScheduler* stop=new CStopTheScheduler(EActivePriorityWsEvents-10);
	if (!stop)
		{
		TEST(EFalse);
		_LIT(KLog,"Not enough memory to run test");
		INFO_PRINTF1(KLog);
		}
	RWsSession& ws=iCoe->WsSession();
	const TInt id=iCoe->RootWin().Identifier();
	TWsEvent event;
	event.SetType(KUserEvent);
	TInt events;
	TInt ii;
	for (events=0;events<10;++events)
		{
		for (ii=events;ii>0;--ii)
			ws.SendEventToWindowGroup(id,event);
		iEventCount=0;
		stop->Call();
		CActiveScheduler::Start();
		TEST(iEventCount==events);
		if (iEventCount!=events)
			{
			_LIT(KLog,"Recieved %d events when %d expected");
			INFO_PRINTF3(KLog,iEventCount,events);
			}
		}
	delete stop;
	}

/**
 @SYMTestCaseID UIF-APPFWK-CONE-0034

 @SYMDEF PDEF131541

 @SYMTestCaseDesc Tests that all redraw events are recieved before a AO of lower priority runs.

 @SYMTestPriority High

 @SYMTestStatus Implemented

 @SYMTestActions Creates two redraws and receives them while low priority AO is active.

 @SYMTestExpectedResults Both redraws occure before the AO runs

 @SYMTestType Unit Test
 */
void CConeEventsAppUi::ManyRedrawsL()
	{
	CStopTheScheduler* stop=new(ELeave) CStopTheScheduler(EActivePriorityRedrawEvents-10);
	CleanupStack::PushL(stop);
	CDrawControl* stateObCnt1=CDrawControl::NewLC(1);
	CDrawControl* stateObCnt2=CDrawControl::NewLC(2);
	stateObCnt1->DrawDeferred();
	stateObCnt2->DrawDeferred();
	stop->Call();
	CActiveScheduler::Start();
	TBool cnt1Drawn=stateObCnt1->HasDrawn();
	TBool cnt2Drawn=stateObCnt2->HasDrawn();
	TEST(cnt1Drawn && cnt2Drawn);
	if (!cnt1Drawn || !cnt2Drawn)
		{
		_LIT(KLog,"Error!!  Control1 Drawn: %d  Control2 Drawn: %d  Both controls should have been drawn");
		INFO_PRINTF3(KLog,cnt1Drawn,cnt2Drawn);
		}
	CleanupStack::PopAndDestroy(3,stop);
	}

/**
 Function to call each of the tests in turn
 */
void CConeEventsAppUi::RunTestStepL(TInt aStepNum)
	{
	_LIT(KTest1,"Test 1: Many Events");
	_LIT(KTest2,"Test 2: Many Redraws");
	switch(aStepNum)
		{
	case 1:
		SetTestStepID(_L("UIF-APPFWK-CONE-0033"));
		INFO_PRINTF1(KTest1);
		ManyEvents();
		RecordTestResultL();
		break;
	case 2:
		SetTestStepID(_L("UIF-APPFWK-CONE-0034"));
		INFO_PRINTF1(KTest2);
		ManyRedrawsL();
		RecordTestResultL();
		CloseTMSGraphicsStep();
		break;
	default:
		AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
		break;
		}
	}

/**
 Constructor for the main test class
 */
CTConeEvents::CTConeEvents(TInt aMode) :iMode(aMode)
	{
	SetTestStepName(aMode==1?KTConeEvents():KTConeEvents2());
	}

/**
 Finish creating the Control Enviroment and create the App UI.
 */
void CTConeEvents::ConstructL(CCoeEnv* aCoe)
	{
	aCoe->ConstructL();
	CConeEventsAppUi* appUi=new(ELeave) CConeEventsAppUi(this,aCoe);
	aCoe->SetAppUi(appUi);
	appUi->ConstructL();
	}

/**
 Entry function for CTConeEvents Test Step.
 */
TVerdict CTConeEvents::doTestStepL()
	{
	INFO_PRINTF1(_L("Test Started"));
	CCoeEnv* coe=new(ELeave) CCoeEnv();		//Need to create the CoeEnv here because it creates a new clean-up stack
	TRAPD(err,ConstructL(coe));
	if (!err)
		{
		if (iMode==1)
			coe->ExecuteD();
		else
			{
			TRAPD(ret,CActiveScheduler::Start());
			_LIT(KTest,"CONE-Test");
			__ASSERT_ALWAYS(ret==KLeaveExit || ret==KErrNone,User::Panic(KTest,EConeTestWrongLeave));
			coe->DisableExitChecks(ETrue);
			delete coe;		//Need to delete the CoeEnv as otherwise there is a CleanupStack panic in TestExecute
			}
		}
	else
		{
		SetTestStepResult(EFail);
		delete coe;
		}
	INFO_PRINTF1(_L("Test Finished"));
	return TestStepResult();
	}
