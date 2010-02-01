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
// Tests message windows provided by CEIkonEnv.\n
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code
*/


#include <e32keys.h>
#include <basched.h>
#include <coecntrl.h>
#include <eikdef.h>
#include <eikenv.h>
#include <eikappui.h>
#include <techview/eikon.hrh>
#include <eikapp.h>
#include <eikdoc.h>
#include <tmsg.rsg>
#include "TMSG.HRH"
#include <techview/eiktbar.h>
#include <ecom/ecom.h>

_LIT(resourceFileName, "z:\\system\\test\\tmsg\\tmsg.rsc");

const TInt KStartDelay=3000000;

#include "Tmsg.h"


enum TTMsgPanic
	{
	ETMsgPanicBadCommand
	};

LOCAL_C void Panic(TTMsgPanic aPanic)
	{
	User::Panic(_L("TMsg"), aPanic);
	}

//
// CTstContainer
//
//!  A CTstContainer test control class. 
/**
 The class represents the test container control.
*/
class CTstContainer : public CCoeControl
	{
public:
	CTstContainer( CTmsTestStep* aStep );
	void ConstructL(const TRect& aRect);
	~CTstContainer();
	void HandleCommandL(TInt aCommand);
/*	//framework
	void CycleThroughEikonEnvInfoMsgs() const;
	void CycleThroughEikonEnvBusyMsgsL() const;*/
private:
	// framework
	virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
	virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	virtual void Draw(const TRect& aRect) const;
	void CycleThroughEikonEnvInfoMsgs() const;
	void CycleThroughEikonEnvBusyMsgsL() const;
	static TInt SimulateEnterKeyEvent(TAny* aAny);
private:
	enum
		{
		EBusyDuration=5*1000000
		};
private:
	CFont* iFont;
	TBuf<64> iText;
	TInt iCounter;
	CPeriodic* iKeyPressTimer;
	CTmsTestStep*	iStep;
	};

CTstContainer::CTstContainer( CTmsTestStep* aStep )
: iStep( aStep )
/**
   Constructor
 */
	{
	__DECLARE_NAME(_S("CTstContainer"));
	}
	
/**
   Auxiliary function for all Test Cases
  
   This method is the second phase constructor for CTstContainer.
   It is used to construct information message & busy message window.
   
 */
void CTstContainer::ConstructL(const TRect& aRect)
	{
	CreateWindowL();
	EnableDragEvents();
	Window().SetBackgroundColor(TRgb(170, 170, 170));
	CWsScreenDevice& screenDevice=*iCoeEnv->ScreenDevice();
	TFontSpec fontSpec(_L("Arial"), screenDevice.VerticalPixelsToTwips(20));
	User::LeaveIfError(screenDevice.GetNearestFontInTwips(iFont, fontSpec));
	iKeyPressTimer=CPeriodic::NewL(EPriorityLow);
	iText=_L("Type or drag pointer to show event-handling");
	SetRect(aRect);
	ActivateL();
	}

CTstContainer::~CTstContainer()
/**
   Destructor
 */
	{
	iCoeEnv->ScreenDevice()->ReleaseFont(iFont);
	delete iKeyPressTimer;
	}


/**
   @SYMTestCaseID UIF-TMSG-HandleCommandL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Tests information message window & busy message window.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method performs following:\n
   (1) Test displaying Information Message at\n
   (i) Bottom right corner of the screen.\n
   (ii)Top right corner of the screen.\n
   (2) Test Cancelling an Information Message Window.\n
   (3) Test Busy Message Window for the following:\n
   (i)  Display a Busy Message Window\n
   (ii) Display two Busy Message Window at the same corner of the screen.\n
   (iii)Display two Busy Message Window at the different corners of
   the screen.\n
   (iv) Display Busy Message Window by specifying initial delay.\n\n
   (4) Test Information Message & Busy Message Window provided by CEikonEnv.\n
   (5) Test Information window with a one or two-line message read from
   the passed resources.
   (6) Test Query Dialog window with a one or two-line message read from
   the passed resources.\n
  
   @SYMTestExpectedResults All the Information & Busy Messages should be displayed as expected.
   
 */
void CTstContainer::HandleCommandL(TInt aCommand)
	{
	TBuf<128> buffer;
	
	switch (aCommand)
		{
	case ETMsgCmdDisplayInfoMsgAtBottom:
		buffer.Format(_L("Info-msg, bottom-right, %d"), iCounter);
		iEikonEnv->InfoMsgWithAlignment(EHRightVBottom, buffer);
		break;
	case ETMsgCmdDisplayInfoMsgAtTop:
		buffer.Format(_L("Info-msg, top-right, %d"), iCounter);
		iEikonEnv->InfoMsgWithAlignment(EHRightVTop, buffer);
		break;
	case ETMsgCmdCancelInfoMsg:
		iEikonEnv->InfoMsgCancel();
		break;
	case ETMsgCmdDisplaySingleBusyMsg:
		buffer.Format(_L("Single busy-msg, bottom-left, %d"), iCounter);
		iEikonEnv->BusyMsgL(buffer, TGulAlignment(EHLeftVBottom));
		User::After(EBusyDuration);
		iEikonEnv->BusyMsgCancel();
		break;
	case ETMsgCmdDisplayTwoBusyMsgsInSameCorner:
		buffer.Format(_L("First of 2 busy-msgs, bottom-left, %d"), iCounter);
		iEikonEnv->BusyMsgL(buffer, TGulAlignment(EHLeftVBottom));
		User::After(EBusyDuration);
		buffer.Format(_L("Second of 2 busy-msgs, bottom-left, %d"), iCounter);
		iEikonEnv->BusyMsgL(buffer, TGulAlignment(EHLeftVBottom));
		User::After(EBusyDuration);
		iEikonEnv->BusyMsgCancel();
		break;
	case ETMsgCmdDisplayTwoBusyMsgsInDifferentCorners:
		buffer.Format(_L("First of 2 busy-msgs, bottom-left, %d"), iCounter);
		iEikonEnv->BusyMsgL(buffer, TGulAlignment(EHLeftVBottom));
		User::After(EBusyDuration);
		buffer.Format(_L("Second of 2 busy-msgs, top-left, %d"), iCounter);
		iEikonEnv->BusyMsgL(buffer, TGulAlignment(EHLeftVTop));
		User::After(EBusyDuration);
		iEikonEnv->BusyMsgCancel();
		break;
	case ETMsgCmdDisplaySingleBusyMsgWithInitialDelayOfTenSeconds:
		buffer.Format(_L("Single busy-msg (init delay = 10), bottom-left, %d"), iCounter);
		iEikonEnv->BusyMsgL(buffer, EHLeftVBottom, 10*1000000);
		User::After(EBusyDuration + 10*1000000);
		iEikonEnv->BusyMsgCancel();
		break;
	case ETMsgCmdDisplayInfoMsgAtTopWithDurationOfTenSeconds:
		buffer.Format(_L("Info-msg (duration = 10), top-right, %d"), iCounter);
		iEikonEnv->InfoMsgWithAlignmentAndDuration(EHRightVTop, buffer, 10*1000000);
		break;
	case ETMsgCmdCycleThroughEikonEnvInfoMsgs:
		CycleThroughEikonEnvInfoMsgs();
		break;
	case ETMsgCmdCycleThroughEikonEnvBusyMsgs:
		CycleThroughEikonEnvBusyMsgsL();
		break;
	case ETMsgCmdCancelBusyMsg:
		iEikonEnv->BusyMsgCancel();
		break;
	case ETMsgCmdInfoWin:
		{	
		TInt keyValue=EKeyEnter;
		TCallBack callBack(SimulateEnterKeyEvent,&keyValue);
		//
		iKeyPressTimer->Start(KStartDelay,KStartDelay,callBack);
		iEikonEnv->InfoWinL(R_TMSG_TBUF_INFOWINMSG_RESOURCEID);
		iKeyPressTimer->Cancel();
		//
		iKeyPressTimer->Start(KStartDelay,KStartDelay,callBack);
		iEikonEnv->InfoWinL(R_TMSG_TBUF_INFOWINMSG_RESOURCEID,R_TMSG_TBUF_INFOWINMSG_RESOURCEID);
		iKeyPressTimer->Cancel();
		}
		break;
	case ETMsgCmdQueryWin:
		{
		TInt keyValue=EKeyEscape;
		TCallBack callBack(SimulateEnterKeyEvent,&keyValue);
		//
		iKeyPressTimer->Start(KStartDelay,KStartDelay,callBack);
		iEikonEnv->QueryWinL(R_TMSG_TBUF_QUERYWINMSG_RESOURCEID);
		iKeyPressTimer->Cancel();
		//
		iKeyPressTimer->Start(KStartDelay,KStartDelay,callBack);
		iEikonEnv->QueryWinL(R_TMSG_TBUF_QUERYWINMSG_RESOURCEID,R_TMSG_TBUF_QUERYWINMSG_RESOURCEID);
		iKeyPressTimer->Cancel();
		}
		break;
	case EEikCmdExit:
		CBaActiveScheduler::Exit();
		break;
	default:
		Panic(ETMsgPanicBadCommand);
		break;
		}
	++iCounter;
	}

/**
   Auxiliary function for TestCaseID CTstContainer::HandleCommandL()
  
   This method prepares a key press event and sends a simulated raw key
   event to the window server. The method is used by HandleCommandL()
   to simulate ENTER key event.
   
 */
TInt CTstContainer::SimulateEnterKeyEvent(TAny* aAny)
	{
	TWsEvent theEvent;
	TKeyEvent *theKey = theEvent.Key();
	theKey->iScanCode = *(TInt*)aAny;
	theKey->iModifiers= 0;
	theKey->iRepeats=0;
	theKey->iCode = EKeyEscape;

	RWsSession	ws;
	TInt theRes = ws.Connect();
	
	if(theRes == KErrNone)
		{
		CCoeEnv* env = CCoeEnv::Static();
		RWindowGroup& winGroup = env->RootWin();
		theEvent.SetTimeNow();
		TInt theId = winGroup.Identifier();
		
		theEvent.SetType(EEventKeyDown);
		theEvent.SetTimeNow();
		ws.SendEventToWindowGroup(theId, theEvent);
		
		theEvent.SetType(EEventKey);
		theEvent.SetTimeNow();
		ws.SendEventToWindowGroup(theId, theEvent);

		theEvent.SetType(EEventKeyUp);
		theEvent.SetTimeNow();
		ws.SendEventToWindowGroup(theId, theEvent);

		ws.Close();
		}
	return KErrNone;
	}

/**
   @SYMTestCaseID UIF-TMSG-CycleThroughEikonEnvInfoMsgs
  
   @SYMPREQ
 
   @SYMTestCaseDesc Tests information message window provided by CEikonEnv.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method tests displaying Information Messages provided
   by CEikonEnv.The API's tested are as listed.\n
   void CEikonEnv::InfoMsg(const TDesC& aDes)\n
   void CEikonEnv::InfoMsg(TInt aResourceId,...)\n
   void CEikonEnv::InfoMsg(TInt aResourceId,VA_LIST aList)\n
   void CEikonEnv::InfoMsgWithAlignment(TGulAlignment aCorner,const TDesC& aDes)\n
   void CEikonEnv::InfoMsgWithAlignment(TGulAlignment aCorner,TInt aResourceId,...)\n
   void CEikonEnv::InfoMsgWithAlignment(TGulAlignment aCorner,TInt aResourceId,VA_LIST aList)\n
   void CEikonEnv::InfoMsgWithDuration(const TDesC& aDes, TTimeIntervalMicroSeconds32 aDuration)\n
   void CEikonEnv::InfoMsgWithDuration(TInt aResourceId, TTimeIntervalMicroSeconds32 aDuration,...)\n
   void CEikonEnv::InfoMsgWithDuration(TInt aResourceId, TTimeIntervalMicroSeconds32 aDuration, VA_LIST aList)\n
   void CEikonEnv::InfoMsgWithAlignmentAndDuration(TGulAlignment aCorner,const TDesC& aDes, TTimeIntervalMicroSeconds32 aDuration)\n
   void CEikonEnv::InfoMsgWithAlignmentAndDuration(TGulAlignment aCorner,TInt aResourceId, TTimeIntervalMicroSeconds32 aDuration,...)\n
   void CEikonEnv::InfoMsgWithAlignmentAndDuration(TGulAlignment aCorner,TInt aResourceId, TTimeIntervalMicroSeconds32 aDuration,VA_LIST aList)\n
  
   @SYMTestExpectedResults All the Information Message Window should be displayed as expected.
   
 */
void CTstContainer::CycleThroughEikonEnvInfoMsgs() const
	{
	iEikonEnv->InfoMsgWithAlignment(EHLeftVBottom,_L("(aAlignment,aText) botLeft"));
	User::After(45*100000);	// info message defaults to 2.5 seconds, so allow another second
	iEikonEnv->InfoMsg(_L("(aText)"));
	User::After(45*100000);
	iEikonEnv->InfoMsg(R_TMSG_TBUF_RESOURCEID);
	User::After(45*100000);
	iEikonEnv->InfoMsg(R_TMSG_TBUF_RESOURCEID_VLIST,12,23);
	User::After(45*100000);
	iEikonEnv->InfoMsgWithAlignment(EHLeftVBottom,R_TMSG_TBUF_CORNER_RESOURCEID);
	User::After(45*100000);
	iEikonEnv->InfoMsgWithAlignment(EHLeftVBottom,R_TMSG_TBUF_CORNER_RESOURCEID_VLIST,34,45);
	User::After(45*100000);
	iEikonEnv->InfoMsgWithDuration(_L("(aText,aDuration) d = 8"),8*1000000);
	User::After(100*100000);
	iEikonEnv->InfoMsgWithDuration(R_TMSG_TBUF_RESOURCEID_DURATION,8*1000000);
	User::After(100*100000);
	iEikonEnv->InfoMsgWithDuration(R_TMSG_TBUF_RESOURCEID_DURATION_VLIST,8*1000000,56,67);
	User::After(100*100000);
	iEikonEnv->InfoMsgWithAlignmentAndDuration(EHLeftVBottom,_L("(aAlignment,aText,aDuration) botLeft,d = 8"), 8*1000000);
	User::After(100*100000);
	iEikonEnv->InfoMsgWithAlignmentAndDuration(EHLeftVBottom,R_TMSG_TBUF_CORNER_RESOURCEID_DURATION, 8*1000000);
	User::After(100*100000);
	iEikonEnv->InfoMsgWithAlignmentAndDuration(EHLeftVBottom,R_TMSG_TBUF_CORNER_RESOURCEID_DURATION_VLIST, 8*1000000,78,89);
	User::After(100*100000);
	}


/**
   @SYMTestCaseID UIF-TMSG-CycleThroughEikonEnvBusyMsgsL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Tests Busy Message Window provided by CEikonEnv.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method tests displaying Busy Messages provided
   by CEikonEnv.The API's tested are as listed.\n
   void CEikonEnv::BusyMsgL(const TDesC& aDes)\n
   void CEikonEnv::BusyMsgL(const TDesC& aDes,TGulAlignment aCorner)\n
   void CEikonEnv::BusyMsgL(TInt aResourceId)\n
   void CEikonEnv::BusyMsgL(const TDesC& aDes,TTimeIntervalMicroSeconds32 aInitialDelay)\n
   void CEikonEnv::BusyMsgL(const TDesC& aDes,TGulAlignment aCorner,TTimeIntervalMicroSeconds32 aInitialDelay)\n
   void CEikonEnv::BusyMsgL(TInt aResourceId,TTimeIntervalMicroSeconds32 aInitialDelay)\n
   void CEikonEnv::BusyMsgCancel()\n
  
   @SYMTestExpectedResults All the Busy Message Window should be displayed as expected.
   
 */
void CTstContainer::CycleThroughEikonEnvBusyMsgsL() const
	{
	iEikonEnv->BusyMsgL(_L("(aText)"));
	User::After(70*100000);
	iEikonEnv->BusyMsgCancel();
	iEikonEnv->BusyMsgL(_L("(aAlignment,aText) botLeft"),TGulAlignment(EHLeftVBottom));
	User::After(70*100000);
	iEikonEnv->BusyMsgCancel();
	iEikonEnv->BusyMsgL(R_TMSG_TBUF_BUSYMSG_RESOURCEID);
	User::After(70*100000);
	iEikonEnv->BusyMsgCancel();
	iEikonEnv->BusyMsgL(_L("(aText,aInitialDelay) d = 3"),3*1000000);
	User::After(100*100000);
	iEikonEnv->BusyMsgCancel();
	iEikonEnv->BusyMsgL(_L("(aText,aAlignment,aInitialDelay) botLeft,d = 3"),EHLeftVBottom,3*1000000);
	User::After(100*100000);
	iEikonEnv->BusyMsgCancel();
	iEikonEnv->BusyMsgL(R_TMSG_TBUF_BUSYMSG_RESOURCEID_INITIALDELAY,3*1000000);
	User::After(100*100000);
	iEikonEnv->BusyMsgCancel();
	}


/**
   Auxiliary function for all Test Cases.
  
   This method is an override from CCoeControl.When a key event occurs, the
   control framework calls this function for each control on the control stack,
   until one of them can process the key event (and returns EKeyWasConsumed).
   
 */
TKeyResponse CTstContainer::OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType)
	{
	iText.Format(_L("Key event: type %d, code %d"), aType, aKeyEvent.iCode);
	DrawNow();
	return EKeyWasConsumed;
	}


/**
   Auxiliary function for all Test Cases.
  
   This method is an override from CCoeControl.This function gets called
   whenever a pointer event occurs in the Container control.
   
 */
void CTstContainer::HandlePointerEventL(const TPointerEvent& aPointerEvent)
	{
	iText.Format(_L("Pointer event: type %d, position (%d, %d)"), aPointerEvent.iType, aPointerEvent.iPosition.iX, aPointerEvent.iPosition.iY);
	DrawNow();
	}


/**
   Auxiliary function for all Test Cases.
  
   This method is an override from CCoeControl. It draws the container control.
   
 */
void CTstContainer::Draw(const TRect&) const
	{
	CWindowGc& gc=SystemGc();
	TRect rect=Rect();
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.SetBrushColor(KRgbYellow);
	gc.DrawRect(rect);
	gc.SetBrushStyle(CGraphicsContext::ENullBrush);
	gc.UseFont(iFont);
	gc.DrawText(iText, rect, iSize.iHeight/2, CGraphicsContext::ECenter);
	}

//
// CTstAppUi
//

//!  A CTstAppUi test class. 
/**
 The class handles work with resources.
*/
class CTstAppUi : public CTestAppUi
	{
public:
	CTstAppUi(CTmsTestStep *aStep) :
	  CTestAppUi(aStep,  
		  resourceFileName)//, R_TMSG_HOTKEYS, 0, R_TMSG_TOOLBAR)
/**
   Constructor
 */
	  {}
	
	void ConstructL();
	virtual ~CTstAppUi();
//private: // framework
	void RunTestStepL(TInt aNumStep);
	virtual void HandleCommandL(TInt aCommand);
private:

	CTstContainer* iContainer;

	TInt		iMsgState;
	};


/**
   Auxiliary function for all Test Cases
  
   The method creates a container and sets active object with lowest
   priority for running test in auto mode.
  
 */
void CTstAppUi::ConstructL()
	{
	//BaseConstructL();
	CTestAppUi::ConstructL();
	
	TRect boundingRect=ClientRect(); // 

	ReduceRect(boundingRect);
	iContainer=new(ELeave) CTstContainer( iStep );
	iContainer->ConstructL(boundingRect);
	AddToStackL(iContainer);

	AutoTestManager().StartAutoTest();

	}


CTstAppUi::~CTstAppUi()
/**
   Destructor
 */
	{
	RemoveFromStack(iContainer);
	delete iContainer;
	}


/**
   Auxiliary function for all Test Cases
  
   This method is called by CTstAppUi::RunTestStepL() to initiate the tests.
   
 */
void CTstAppUi::HandleCommandL(TInt aCommand)
	{
	iContainer->HandleCommandL(aCommand);
	}


/**
   Auxiliary function for all Test Cases
  
   The method is an override from CTestAppUi. The method initiates all tests
   to be performed by calling CTstAppUi::HandleCommandL().
   
 */
void CTstAppUi::RunTestStepL(TInt aNumStep)
	{
	TInt theMessageState = EEikCmdExit;
	switch(aNumStep)
		{
		case 1:
		INFO_PRINTF1(_L("Display info message at bottom"));
		theMessageState = ETMsgCmdDisplayInfoMsgAtBottom;
		break;
		case 2:
		INFO_PRINTF1(_L("Display info message at top"));
		theMessageState = ETMsgCmdDisplayInfoMsgAtTop;
		break;
		case 3:
		INFO_PRINTF1(_L("Cancel info message"));
		theMessageState = ETMsgCmdCancelInfoMsg;
		break;
		case 4:
		INFO_PRINTF1(_L("Display single busy message"));
		theMessageState = ETMsgCmdDisplaySingleBusyMsg;
		break;
		case 5:
		INFO_PRINTF1(_L("Display two busy messages in the same corner"));
		theMessageState = ETMsgCmdDisplayTwoBusyMsgsInSameCorner;
		break;
		case 6:
		INFO_PRINTF1(_L("Display two busy messages in different corners"));
		theMessageState = ETMsgCmdDisplayTwoBusyMsgsInDifferentCorners;
		break;
		case 7:
		INFO_PRINTF1(_L("Display single message with initial delay of ten seconds"));
		theMessageState = ETMsgCmdDisplaySingleBusyMsgWithInitialDelayOfTenSeconds;
		break;
		case 8:
		INFO_PRINTF1(_L("Display message at top with duration of ten seconds"));
		theMessageState = ETMsgCmdDisplayInfoMsgAtTopWithDurationOfTenSeconds;
		break;
		case 9:
		INFO_PRINTF1(_L("Cycle through EikonEnv info  messages"));
		iStep->SetTestStepID(_L("UIF-TMSG-CycleThroughEikonEnvInfoMsgs"));
		theMessageState = ETMsgCmdCycleThroughEikonEnvInfoMsgs;
		iStep->RecordTestResultL();
		break;
		case 10:
		INFO_PRINTF1(_L("Cycle through EikonEnv busy messages"));
		iStep->SetTestStepID(_L("UIF-TMSG-CycleThroughEikonEnvBusyMsgsL"));
		theMessageState = ETMsgCmdCycleThroughEikonEnvBusyMsgs;
		iStep->RecordTestResultL();
		iStep->CloseTMSGraphicsStep();
		break;
		case 11:
		INFO_PRINTF1(_L("Cancel busy message"));
		theMessageState = ETMsgCmdCancelBusyMsg;
		break;
		case 12:
		INFO_PRINTF1(_L("InfoWin messages"));
		theMessageState = ETMsgCmdInfoWin;
		INFO_PRINTF1(_L("InfoWin messages completed!"));
		break;
		case 13:
		INFO_PRINTF1(_L("QueryWin messages"));
		theMessageState = ETMsgCmdQueryWin;
		INFO_PRINTF1(_L("QueryWin messages completed!"));
		break;
		case 14:
			AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
			return;
		}
		
				
		HandleCommandL(theMessageState);
	}

//----------
CTestMsgStep::CTestMsgStep()
/**
   Constructor
 */
	{
	SetTestStepName(KTestMsgStep);
	}

CTestMsgStep::~CTestMsgStep()
/**
   Destructor
 */
	{
	}
	
/**
   Auxiliary function for all Test Cases
  
   The method creates & sets the application's user interface object.
   
 */
void CTestMsgStep::ConstructAppL(CEikonEnv* aCoe)
    { // runs inside a TRAP harness
	aCoe->ConstructL();
	CTstAppUi* appUi=new(ELeave) CTstAppUi(this);
    aCoe->SetAppUi(appUi);
    appUi->ConstructL();
    }

/**
   Auxiliary function for all Test Cases
  
   The method creates & sets the application's user interface object to 
   launch the application which will initiate the tests.
   
 */
TVerdict CTestMsgStep::doTestStepL() // main function called by E32
	{
	PreallocateHALBuffer();
	__UHEAP_MARK;

	CEikonEnv* coe=new CEikonEnv;
	TRAPD(err,ConstructAppL(coe));

	if (!err)
		coe->ExecuteD();

	REComSession::FinalClose();	
	__UHEAP_MARKEND;

	return TestStepResult();
	}

