// Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
// Tests 100% of the public API of the Cone view architecture support.
// The tests performed are server start, coe env and app ui creation, addition of views,
// activation of views, activation message passing, queuing of view events,
// removal of views, view control stacking, key event simulation, control stack flag changing,
// addition of default view, activation of default view, addition of view deactivation observers
// removal of view deactivation observers.
// Also tests the ordering of key event passing for controls on the control stack of the appUi and
// the active view. Low priority controls in the appUi should get key events after higher priority
// controls in the active view. 
// 
//

/**
 @file
 @test
 @internalComponent - Internal Symbian test code
*/
 
#include <e32cons.h>
#include <vwsappst.h>
#include <coeaui.h>
#include <coemain.h>
#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <viewclipartner.h>
#endif //SYMBIAN_ENABLE_SPLIT_HEADERS

#include "coepriv.h"
#include "COEVWMAN.H"

#include <test/appfwk_test.h>
#include "TVWASTEP.H"


/*************************************************************
 **  
 **  Global constants
 **   
 *************************************************************/

_LIT(KCustomDes,"Custom Message");
_LIT(KNullDes,"");

#define KUidTViewAppOneValue 0xA
const TUid KUidTViewAppOne={KUidTViewAppOneValue};

#define KUidTViewOneValue 0x1
const TUid KUidTViewOne={KUidTViewOneValue};

#define KUidTViewTwoValue 0x2
const TUid KUidTViewTwo={KUidTViewTwoValue};

#define KUidTViewFiveValue 0x5
const TUid KUidTViewFive={KUidTViewFiveValue};

#define VIEW_ONE TVwsViewId(KUidTViewAppOne,KUidTViewOne)
#define VIEW_TWO TVwsViewId(KUidTViewAppOne,KUidTViewTwo)
#define VIEW_FIVE TVwsViewId(KUidTViewAppOne,KUidTViewFive)

#define KUidTViewAppTwoValue 0xB
const TUid KUidTViewAppTwo={KUidTViewAppTwoValue};

#define KUidTViewThreeValue 0x3
const TUid KUidTViewThree={KUidTViewThreeValue};

#define KUidTViewFourValue 0x4
const TUid KUidTViewFour={KUidTViewFourValue};

#define VIEW_THREE TVwsViewId(KUidTViewAppTwo,KUidTViewThree)
#define VIEW_FOUR TVwsViewId(KUidTViewAppTwo,KUidTViewFour)

const TUid KUidTws0CustomMesssageId={0x1};

const TInt KTopControlId=1;
const TInt KBottomControlId=2;

const TInt KViewDeactivationObserverOneId=1;
const TInt KViewDeactivationObserverTwoId=2;
const TInt KViewActivationObserverOneId=1;
const TInt KViewActivationObserverTwoId=2;
const TInt KViewActivationObserverThreeId=3;
 
// Global variables to check activations & deactivations notifications...
TInt gViewActivationObserverOne;
TInt gViewDeactivationObserverOne;
TInt gViewActivationObserverTwo;
TInt gViewDeactivationObserverTwo;
TInt gViewActivationObserverNotify;
TInt gViewDeactivationObserverNotify;

// Global variables to check controls event consumptions...
TInt gTopControl;
TInt gBottomControl;
TInt gAppUiControl;

enum TTestFrameworkPanic
    {
    ETestFailure = 1
    };

static void PanicWithCondAndInfo(TTestFrameworkPanic aPanic, const TDesC& aCondition, const TDesC& aFileName, const TDesC& aPanicName, TInt aLine)
    {
    TBuf<256> buf;
    _LIT(KPanicDesc1,"Testframework Panic %S, in file %S @ line %i");
    buf.Format(KPanicDesc1, &aPanicName, &aFileName, aLine);
    RDebug::Print(buf);
    _LIT(KPanicDesc2,"Assert condition = \"%S\"");
    buf.Format(KPanicDesc2, &aCondition);
    RDebug::Print(buf);
    _LIT(KPanicCategory,"CTestDriver");
    User::Panic(KPanicCategory,aPanic);
    }

#define _ASSERT_FILENAME(f)  _LIT(KPanicFileName, f);
#define _ASSERT_PANICNAME(p) _LIT(KPanicEnum ## p, # p);
#define _ASSERT_CONDITION(c) _LIT(KPanicCondition, c);

#define TEST_ASSERT(c, p) \
        do  { \
            if (!(c)) \
                { \
                _ASSERT_FILENAME(__FILE__); \
                _ASSERT_PANICNAME(p); \
                _ASSERT_CONDITION(#c); \
                PanicWithCondAndInfo(p, KPanicCondition, KPanicFileName, KPanicEnum ## p, __LINE__); \
                } \
            } while (0)

// Use this method as a way to test when usage of TEST macro is not possible
//inline void TEST_ASSERT(TBool aCondition){ TEST_ASSERT(aCondition, ETestFailure); }

/*************************************************************
 **  
 **  CViewActivationObserver  - implements the MCoeViewActivationObserver interface
 **  
 *************************************************************/

CViewActivationObserver* CViewActivationObserver::NewL(TInt aObserverId)
	{
	CViewActivationObserver* self=new(ELeave) CViewActivationObserver(aObserverId);
	return self;
	}

CViewActivationObserver::CViewActivationObserver(TInt aObserverId) : iObserverId(aObserverId)
	{
	}

CViewActivationObserver::~CViewActivationObserver()
	{
	}

void CViewActivationObserver::HandleViewActivation(const TVwsViewId& aNewlyActivatedViewId,const TVwsViewId& aViewIdToBeDeactivated)
	{
	RDebug::Print(_L("CViewActivationObserver::HandleViewActivation: Observer 0x%x - Newly Active View: 0x%x - Deactivate 0x%x"), iObserverId, aNewlyActivatedViewId.iViewUid.iUid, aViewIdToBeDeactivated.iViewUid.iUid);
	// for testing purposes
	if (iObserverId == KViewActivationObserverOneId)
		gViewActivationObserverOne++;
	else if (iObserverId == KViewActivationObserverTwoId)
		gViewActivationObserverTwo++;
	}



/*************************************************************
 **  
 **  CViewDeactivationObserver  - implements the MCoeViewDeactivationObserver interface
 **  
 *************************************************************/

CViewDeactivationObserver* CViewDeactivationObserver::NewL(TInt aObserverId)
	{
	CViewDeactivationObserver* self=new(ELeave) CViewDeactivationObserver(aObserverId);
	return self;
	}

CViewDeactivationObserver::CViewDeactivationObserver(TInt aObserverId) : iObserverId(aObserverId)
	{
	}

CViewDeactivationObserver::~CViewDeactivationObserver()
	{
	}

void CViewDeactivationObserver::HandleViewDeactivation(const TVwsViewId& aViewIdToBeDeactivated,const TVwsViewId& aNewlyActivatedViewId)
	{
	RDebug::Print(_L("CViewDeactivationObserver::HandleViewDeactivation: Observer 0x%x - Deactivate 0x%x - Newly Active View: 0x%x"), iObserverId, aViewIdToBeDeactivated.iViewUid.iUid, aNewlyActivatedViewId.iViewUid.iUid);
	// for testing purposes
	if (iObserverId == KViewDeactivationObserverOneId)
		gViewDeactivationObserverOne++;
	else if (iObserverId == KViewDeactivationObserverTwoId)
		gViewDeactivationObserverTwo++;
	}



/*************************************************************
 **  
 **  CViewActivationObserver_Notify  - implements the MCoeViewActivationObserver interface for notifications only
 **  
 *************************************************************/

CViewActivationObserver_Notify* CViewActivationObserver_Notify::NewL()
	{
	CViewActivationObserver_Notify* self=new(ELeave) CViewActivationObserver_Notify();
	return self;
	}

CViewActivationObserver_Notify::CViewActivationObserver_Notify() 
	{
	}

CViewActivationObserver_Notify::~CViewActivationObserver_Notify()
	{
	}

void CViewActivationObserver_Notify::HandleViewActivation(const TVwsViewId& aNewlyActivatedViewId,const TVwsViewId& aViewIdToBeDeactivated)
	{
	RDebug::Print(_L("Notified CViewActivationObserver_Notify::HandleViewActivation: Newly Active View: 0x%x - Deactivate 0x%x"), aNewlyActivatedViewId.iViewUid.iUid, aViewIdToBeDeactivated.iViewUid.iUid);
	// for testing purposes
	gViewActivationObserverNotify++;
	}



/*************************************************************
 **  
 **  CViewDeactivationObserver_Notify  - implements the MCoeViewDeactivationObserver interface for notifications only
 **  
 *************************************************************/

CViewDeactivationObserver_Notify* CViewDeactivationObserver_Notify::NewL()
	{
	CViewDeactivationObserver_Notify* self=new(ELeave) CViewDeactivationObserver_Notify();
	return self;
	}

CViewDeactivationObserver_Notify::CViewDeactivationObserver_Notify()
	{
	}

CViewDeactivationObserver_Notify::~CViewDeactivationObserver_Notify()
	{
	}

void CViewDeactivationObserver_Notify::HandleViewDeactivation(const TVwsViewId& aViewIdToBeDeactivated,const TVwsViewId& aNewlyActivatedViewId)
	{
	RDebug::Print(_L("Notified CViewDeactivationObserver_Notify::HandleViewDeactivation: Deactivate 0x%x - Newly Active View: 0x%x"), aViewIdToBeDeactivated.iViewUid.iUid, aNewlyActivatedViewId.iViewUid.iUid);
	// for testing purposes
	gViewDeactivationObserverNotify++;
	}




/*************************************************************
 **  
 **  CTVwaTestControl
 **  
 *************************************************************/

CTVwaTestControl::CTVwaTestControl(TVwsViewId& aViewId, TInt aControlId) : iViewId(aViewId), iControlId(aControlId)
    {
    }

void CTVwaTestControl::ConstructL()
    {
    CreateWindowL();
    SetExtent(TPoint(0,0),TSize(0,0));
    ActivateL();
    }

CTVwaTestControl::~CTVwaTestControl()
    {
    }

TKeyResponse CTVwaTestControl::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    if (aType!=EEventKey)
	    return(EKeyWasConsumed);
    
	RDebug::Print(_L("Key Event: View: 0x%x - Control: 0x%x - Key 0x%x"), iViewId.iViewUid.iUid, iControlId, aKeyEvent.iCode);

	// for testing purposes
	if (iControlId == KTopControlId)
		gTopControl++;
	else if (iControlId == KBottomControlId)
		gBottomControl++;
	
	// For testing purposes, if the control receives a 'C', let's consume it.
	if (aKeyEvent.iCode == 'C')
	    return(EKeyWasConsumed);
	else
		return(EKeyWasNotConsumed);

    }



/*************************************************************
 **  
 **  CAppUiTestControl
 **  
 *************************************************************/

CAppUiTestControl::CAppUiTestControl()
    {
    }

void CAppUiTestControl::ConstructL()
    {
    CreateWindowL();
    SetExtent(TPoint(0,0),TSize(0,0));
    ActivateL();
    }

CAppUiTestControl::~CAppUiTestControl()
    {
    }

TKeyResponse CAppUiTestControl::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    if (aType!=EEventKey)
	    return(EKeyWasConsumed);
    
	RDebug::Print(_L("AppUi Control Key Event: Key 0x%x"), aKeyEvent.iCode);

	// for testing purposes
	gAppUiControl++;

	// For testing purposes, if the control receives a 'U', let's consume it.
	if (aKeyEvent.iCode == 'C')
	    return(EKeyWasConsumed);
	else
		return(EKeyWasNotConsumed);
    }



/*************************************************************
 **  
 **  CTestView
 **  
 *************************************************************/

CTestView::~CTestView()
	{
	RemoveFromStack(iTopControl);
	delete iTopControl;
	RemoveFromStack(iBottomControl);
	delete iBottomControl;
	}

CTestView::CTestView(const TVwsViewId& aViewId,CCoeAppUi& aAppUi)
	:iAppUi(aAppUi),iViewId(aViewId)
	{
	}

void CTestView::ConstructL()
	{
	iTopControl=new(ELeave) CTVwaTestControl(iViewId,KTopControlId);
    iTopControl->ConstructL();
	iBottomControl=new(ELeave) CTVwaTestControl(iViewId,KBottomControlId);
    iBottomControl->ConstructL();
	AddToStackL(iBottomControl);
	AddToStackL(iTopControl);
	}

/**
  Getter of view id.\n 
 */
TVwsViewId CTestView::ViewId() const
	{
	return iViewId;
	}

/**
  Activates the supplied view id.\n
 */
void CTestView::ViewActivatedL(const TVwsViewId& aPrevViewId,TUid aCustomMessageId,const TDesC8& aCustomMessage)
	{
	DoActivateNarrowL(aPrevViewId,aCustomMessageId,aCustomMessage);

	if (aPrevViewId.iAppUid.iUid == KUidTViewAppOneValue && iViewId.iAppUid.iUid == KUidTViewAppOneValue)
		{
		TSecureId processId = aPrevViewId.iAppUid;
		const TSecurityPolicy policy(processId);
		TInt previousAppInitiatedViewSwitch = 0;
		RDebug::Print(_L("Calling  CheckSourceOfViewSwitchL where appUid and processID are same ..."));
		TRAPD(err, previousAppInitiatedViewSwitch = iAppUi.CheckSourceOfViewSwitchL(policy, KSuppressPlatSecDiagnostic));
		TEST_ASSERT(err == KErrNone, ETestFailure);
		TEST_ASSERT(!previousAppInitiatedViewSwitch, ETestFailure);
		RDebug::Print(_L("Test for CheckSourceOfViewSwitchL complete ..."));
		}
	
	// CheckSourceOfViewSwitchL leaves with KErrUnknown if called outside of an implementation of MCoeView's ViewConstructL or ViewActivatedL
	// Do that if and only if we're switching between iAppUi (i.e. KTVwaStandardAppUiId, not KTVwaEmbeddedAppUiId)
	if (aPrevViewId.iAppUid.iUid == KUidTViewAppOneValue && iViewId.iAppUid.iUid == KUidTViewAppOneValue)
		{
		TInt r = 0;
		RDebug::Print(_L("Calling CheckSourceOfViewSwitchL with a valid TVendorId..."));
		TRAPD(err, r = iAppUi.CheckSourceOfViewSwitchL(TSecurityPolicy(TVendorId(0x70000001))));
		TEST_ASSERT(err == KErrNone, ETestFailure);
		TEST_ASSERT(r, ETestFailure);


		RDebug::Print(_L("Calling CheckSourceOfViewSwitchL with an invalid TVendorId..."));
		APPFWK_NEGATIVE_PLATSEC_START;
		TRAP(err, r = iAppUi.CheckSourceOfViewSwitchL(TSecurityPolicy(TVendorId(0x70000002)), __PLATSEC_DIAGNOSTIC_STRING("z:/conetest/menutest_t_vwa.script negative testing")));
		APPFWK_NEGATIVE_PLATSEC_FINISH;
		TEST_ASSERT(err == KErrNone, ETestFailure);
		TEST_ASSERT(!r, ETestFailure);
		}
	}


/**
  Activates the supplied view id but narrows down the supplied message from 16-bit unicode to 8 bit ASCII.
 */
void CTestView::DoActivateNarrowL(const TVwsViewId& aPrevViewId,TUid aCustomMessageId,const TDesC8& aCustomMessage)
	{
	HBufC16* wideCustomMessage=HBufC16::NewLC(aCustomMessage.Length()/2);
	TPtr16 ptr=wideCustomMessage->Des();
	ptr.Copy((TUint16*)aCustomMessage.Ptr(),aCustomMessage.Length()/2);
	DoActivateL(aPrevViewId,aCustomMessageId,ptr);
	CleanupStack::PopAndDestroy(wideCustomMessage);
	}

/**
  Activates the supplied view id.\n
 */
void CTestView::DoActivateL(const TVwsViewId& aPrevViewId,TUid aCustomMessageId,const TDesC16& aCustomMessage)
	{
	RDebug::Print(_L("CTestView::ViewActivatedL:: 0x%x - Previous View: 0x%x"), iViewId.iViewUid.iUid, aPrevViewId.iViewUid.iUid);
	RDebug::Print(_L("Message - Id: 0x%x - Text: %S"),aCustomMessageId.iUid, &aCustomMessage);
	}

/**
  Handles a change to the screen device returning the value of the TVwsViewIdAndMessage
  object that describes what the view architecture should do next.\n
 */
TVwsViewIdAndMessage CTestView::ViewScreenDeviceChangedL()
	{
	RDebug::Print(_L("CTestView::ViewScreenDeviceChangedL: 0x%x"), iViewId.iViewUid.iUid);
	return TVwsViewIdAndMessage();
	}

/**
  Prints a message which view has been deactivated.\n
 */
void CTestView::ViewDeactivated()
	{
	RDebug::Print(_L("CTestView::ViewDeactivated: 0x%x "), iViewId.iViewUid.iUid);
	}

/**
  Debug print of the uid of the top control.\n
 */
void CTestView::ViewConstructL()
	{
	if(!iTopControl && !iBottomControl)
		{
		ConstructL();
		}

	RDebug::Print(_L("CTestView::ViewConstructL: 0x%x "), iViewId.iViewUid.iUid);
	}

/**
  Activates view with id aViewId.\n
 */
void CTestView::ActivateViewL(const TVwsViewId& aViewId)
	{
	iAppUi.ActivateViewL(aViewId);
	}

/**
  Activates view with id aViewId and send a message.\n
 */
void CTestView::ActivateViewL(const TVwsViewId& aViewId,TUid aCustomMessageId,const TDesC16& aCustomMessage)
	{
	HBufC8* narrowMessage=HBufC8::NewLC(aCustomMessage.Size());
	TPtr8 ptr=narrowMessage->Des();
	ptr.Copy((TUint8*)aCustomMessage.Ptr(),aCustomMessage.Size());
	iAppUi.ActivateViewL(aViewId,aCustomMessageId,narrowMessage->Des());
	CleanupStack::PopAndDestroy(narrowMessage);
	}

/**
  Add aControl to Cone's control stack with priority aPriority and behaviour aStackingFlags.\n
 */
void CTestView::AddToStackL(CCoeControl* aControl,TInt aPriority,TInt aStackingFlags)
	{
	iAppUi.AddToStackL(*this, aControl,aPriority,aStackingFlags);
	}

/**
  Remove aControl from Cone's control stack.\n
 */
void CTestView::RemoveFromStack(CCoeControl* aControl)
	{
	iAppUi.RemoveFromStack(aControl);
	}

/**
  Updates the value of the flags for aControl on the control stack.
  The mask aMask defines which flags are modified, while aFlags defines the values they are set to.\n
 */
void CTestView::UpdateStackedControlFlags(CCoeControl* aControl,TInt aFlags,TInt aMask)
	{
	iAppUi.UpdateStackedControlFlags(aControl,aFlags,aMask);
	}

/**
  Set the top control to refuse all key events.\n
 */
void CTestView::UpdateControlStackingFlags()
	{
	UpdateStackedControlFlags(iTopControl,ECoeStackFlagRefusesAllKeys,0xffff);
	}

/**
  Lower the priority of the bottom control with 20.\n
 */
void CTestView::UpdateControlPriorityL()
	{
	RemoveFromStack(iBottomControl);
	AddToStackL(iBottomControl,ECoeStackPriorityDefault-20);
	}


/*************************************************************
 **  
 **  CTestDriver 
 **  
 *************************************************************/

CTestDriver::CTestDriver(CCoeAppUi& aAppUi, CTmsTestStep* aStep) : iAppUi(aAppUi) ,iStep(aStep)
	{
	}

void CTestDriver::ConstructL()
	{
	iUpdateTimer=CPeriodic::NewL(0);
	iUpdateTimer->Start(KUpdateInterval,KUpdateInterval,TCallBack(UpdateTimerCallBackL,this));

	iViewActivationObserverOne=CViewActivationObserver::NewL(KViewActivationObserverOneId);
	iViewDeactivationObserverOne=CViewDeactivationObserver::NewL(KViewDeactivationObserverOneId);

	iViewActivationObserverTwo=CViewActivationObserver::NewL(KViewActivationObserverTwoId);
	iViewDeactivationObserverTwo=CViewDeactivationObserver::NewL(KViewDeactivationObserverTwoId);

	iViewActivationObserver_Notify=CViewActivationObserver_Notify::NewL();
	iViewDeactivationObserver_Notify=CViewDeactivationObserver_Notify::NewL();
	}

CTestDriver::~CTestDriver()
	{
	delete iUpdateTimer;
	delete iViewActivationObserverOne;
	delete iViewDeactivationObserverOne;
	delete iViewActivationObserverTwo;
	delete iViewDeactivationObserverTwo;
	delete iViewActivationObserver_Notify;
	delete iViewDeactivationObserver_Notify;
	}

void CTestDriver::Exit()
	{
	CBaActiveScheduler::Exit();
	}

void CTestDriver::RunTestL()
	{
	TInt ret=EInvalid;
	TRAPD(err,ret=DoTestL());
	if (err!=KErrNone)
		{
		User::Leave(err);
		}
	else if (ret==EFinished)
		{
		iTestNum=KExitTestNum;
		}
	}


TInt CTestDriver::UpdateTimerCallBackL(TAny* aThis)
	{
	CTestDriver* driver=((CTestDriver*)aThis);
	driver->RunTestL();
	return 0;
	}


TestState CTestDriver::DoTestL()
	{
	switch(iTestNum++)
		{	 


//----------------------------------------------------------------------------------------------

/**
  @SYMTestCaseID 			UIF-CONE-VIEW-0014
  @SYMPREQ 					Codebase
  @SYMTestCaseDesc			Addition and activation of views using Cone view architecture support
  @SYMTestPriority 			High
  @SYMTestStatus 			Implemented
  @SYMTestActions 			The tests performed are addition of views to an application. Views 1, 2 & 5
  								are added, and activation of these views is tested (both with and without
  								a custom message associated to the activation). 
  								In addition, the getter and setter functionality of application default
  								view, and system default views are tested.
  @SYMTestType 				CIT
  @SYMTestExpectedResults 	Views are added and activated as expected with no error returned. Getter
  							& setter funtions get & set accordingly too.
*/

//----------------------------------------------------------------------------------------------

		case 0:
			{
			iStep->SetTestStepID(_L("UIF-CONE-VIEW-0014"));
			INFO_PRINTF1(_L("Add views 1, 5 and 2 for client 1"));
			TEST_ASSERT(AddView(VIEW_ONE) == KErrNone, ETestFailure);
			TEST_ASSERT(AddView(VIEW_FIVE) == KErrNone, ETestFailure);
			TEST_ASSERT(AddView(VIEW_TWO) == KErrNone, ETestFailure);
			}
			break;
			
		case 1:
			{
			INFO_PRINTF1(_L("Set default view for client 1 to view 5"));
			TEST_ASSERT(SetDefaultView(VIEW_FIVE) == KErrNone, ETestFailure);

			TVwsViewId viewId=KNullViewId;
			INFO_PRINTF1(_L("Set default view for client 1 to view 2 and check it changed"));
			TEST_ASSERT(GetDefaultView(viewId) == KErrNone, ETestFailure);			
			TEST_ASSERT(viewId == VIEW_FIVE, ETestFailure);

			TEST_ASSERT(SetDefaultView(VIEW_TWO) == KErrNone, ETestFailure);			
			TEST_ASSERT(GetDefaultView(viewId) == KErrNone, ETestFailure);			
			TEST_ASSERT(viewId == VIEW_TWO, ETestFailure);
			}
			break;
			
		case 2:
			{
			INFO_PRINTF1(_L("Set system default view for client 1 to view 1"));
			AppUi().SetSystemDefaultViewL(VIEW_ONE);

			TVwsViewId viewId=KNullViewId;
			INFO_PRINTF1(_L("Set system default view for client 1 to view 2 and check it changed"));
			AppUi().GetSystemDefaultViewL(viewId);			
			TEST_ASSERT(viewId == VIEW_ONE, ETestFailure);

			AppUi().SetSystemDefaultViewL(VIEW_TWO);
			AppUi().GetSystemDefaultViewL(viewId);			
			TEST_ASSERT(viewId == VIEW_TWO, ETestFailure);
			}
			break;
			
		case 3:
			{
			INFO_PRINTF1(_L("Set system default view for different modes"));
			AppUi().SetSystemDefaultViewL(VIEW_TWO);
			AppUi().SetSystemDefaultViewL(VIEW_ONE, 1);
			AppUi().SetSystemDefaultViewL(VIEW_FIVE, 2);

			TVwsViewId viewId=KNullViewId;
			AppUi().GetSystemDefaultViewL(viewId);			
			TEST_ASSERT(viewId == VIEW_TWO, ETestFailure);		// It's 2 for the current one (current = default)
			}
			break;

		case 5:
			{
			INFO_PRINTF1(_L("Activate view 2 with message"));
			TEST_ASSERT(ActivateView(VIEW_TWO,KUidTws0CustomMesssageId,KCustomDes) == KErrNone, ETestFailure);
			TVwsViewId activeViewId=KNullViewId;
			TEST_ASSERT(AppUi().GetActiveViewId(activeViewId) == KErrNone, ETestFailure);
			TEST_ASSERT(activeViewId.iViewUid.iUid == KUidTViewTwoValue, ETestFailure);
			}
			break;
			
		case 6:
			{
			INFO_PRINTF1(_L("Remove view 5"));
			TEST_ASSERT(RemoveView(VIEW_FIVE) == KErrNone, ETestFailure);			
			TVwsViewId activeViewId=KNullViewId;
			TEST_ASSERT(AppUi().GetActiveViewId(activeViewId) == KErrNone, ETestFailure);
			TEST_ASSERT(activeViewId.iViewUid.iUid == KUidTViewTwoValue, ETestFailure);
			}
			break;
			
		case 7:
			{
			INFO_PRINTF1(_L("Activate top view for client 1 (expected to be view 2)"));
			TEST_ASSERT(ActivateTopView() == KErrNone, ETestFailure);
			TVwsViewId activeViewId=KNullViewId;
			TEST_ASSERT(AppUi().GetActiveViewId(activeViewId) == KErrNone, ETestFailure);
			TEST_ASSERT(activeViewId.iViewUid.iUid == KUidTViewTwoValue, ETestFailure);
			}
			break;
			
		case 8:
			{
			INFO_PRINTF1(_L("Activate view 1 with message"));
			TEST_ASSERT(ActivateView(VIEW_ONE,KUidTws0CustomMesssageId,KCustomDes) == KErrNone, ETestFailure);
			TVwsViewId activeViewId=KNullViewId;
			TEST_ASSERT(AppUi().GetActiveViewId(activeViewId) == KErrNone, ETestFailure);
			TEST_ASSERT(activeViewId.iViewUid.iUid == KUidTViewOneValue, ETestFailure);
			iStep->RecordTestResultL();
			break;			
			}
			
			
//----------------------------------------------------------------------------------------------

/**
  @SYMTestCaseID 			UIF-CONE-VIEW-0015
  @SYMPREQ 					Codebase
  @SYMTestCaseDesc			Control notification in views using Cone view architecture support
  @SYMTestPriority 			High
  @SYMTestStatus 			Implemented
  @SYMTestActions 			The tests performs a simulation of EKeyEvents sent to the application to check
  								how both test controls (Top & Bottom) receive them, as well as the AppUi control.
  								A counter is increased everytime the key is processed, and usually the key
  								is never consumed, hence it goes to the next control in the loop. Just some specific
  								EKeyEvents are consumed to check that the next control do not receive it. 
  								In addition, priorities and flags are updated to test the notifications are
  								still correctly received.
  								Change of active view is also tested.
  @SYMTestType 				CIT
  @SYMTestExpectedResults 	Controls receive notifications as expected depending of their flags and / or
  							priorities.
*/

//----------------------------------------------------------------------------------------------

		case 20:
			{
			iStep->SetTestStepID(_L("UIF-CONE-VIEW-0015"));
			INFO_PRINTF1(_L("Simulate normal key event 'A'"));
			TEST_ASSERT(SimulateKeyEvent('A') == KErrNone, ETestFailure);			
			}
			break;
			
		case 21:
			{
			INFO_PRINTF1(_L("All controls must have received the notification, as none consumed it"));
			TEST_ASSERT(gTopControl == 1, ETestFailure);
			TEST_ASSERT(gBottomControl == 1, ETestFailure);
			TEST_ASSERT(gAppUiControl == 1, ETestFailure);
			}
			break;

		case 22:
			{
			INFO_PRINTF1(_L("Lower BottomControl priority for active view"));
			TEST_ASSERT(UpdateActiveViewPriorities() == KErrNone, ETestFailure);
			}
			break;
		
		case 23:
			{
			INFO_PRINTF1(_L("Simulate normal key event 'B'"));
			TEST_ASSERT(SimulateKeyEvent('B') == KErrNone, ETestFailure);			
			}
			break;
		
		case 24:
			{
			INFO_PRINTF1(_L("All controls must have received the notification, as none consumed it"));
			TEST_ASSERT(gTopControl == 2, ETestFailure);
			TEST_ASSERT(gBottomControl == 2, ETestFailure);
			TEST_ASSERT(gAppUiControl == 2, ETestFailure);
			}
			break;

		case 25:
			{
			INFO_PRINTF1(_L("Simulate normal key event 'C' (consumed by one of the controls!)"));
			TEST_ASSERT(SimulateKeyEvent('C') == KErrNone, ETestFailure);			
			}
			break;
		
		case 26:
			{
			INFO_PRINTF1(_L("BottomControl does not receive the key, as it's consumed by TopControl which has higher priority"));
			TEST_ASSERT(gTopControl == 3, ETestFailure);
			TEST_ASSERT(gBottomControl == 2, ETestFailure);
			TEST_ASSERT(gAppUiControl == 2, ETestFailure);
			}
			break;

		case 27:
			{
			INFO_PRINTF1(_L("Simulate normal key event 'U' (consumed by AppUi control!)"));
			TEST_ASSERT(SimulateKeyEvent('U') == KErrNone, ETestFailure);			
			}
			break;
		
		case 28:
			{
			INFO_PRINTF1(_L("AppUi consumes the key, but other Bottom and Top still receive it"));
			TEST_ASSERT(gTopControl == 4, ETestFailure);
			TEST_ASSERT(gBottomControl == 3, ETestFailure);
			TEST_ASSERT(gAppUiControl == 3, ETestFailure);
			}
			break;

		case 29:
			{
			INFO_PRINTF1(_L("Activate view 2"));
			TEST_ASSERT(ActivateView(VIEW_TWO,TUid::Null(),KNullDes) == KErrNone, ETestFailure);
			TVwsViewId activeViewId=KNullViewId;
			TEST_ASSERT(AppUi().GetActiveViewId(activeViewId) == KErrNone, ETestFailure);
			TEST_ASSERT(activeViewId.iViewUid.iUid == KUidTViewTwoValue, ETestFailure);
			}
			break;

		case 30:
			{
			INFO_PRINTF1(_L("Simulate normal key event 'D'"));
			TEST_ASSERT(SimulateKeyEvent('D') == KErrNone, ETestFailure);			
			}
			break;
		
		case 31:
			{
			INFO_PRINTF1(_L("All controls must have received the notification, as none consumed it"));
			TEST_ASSERT(gTopControl == 5, ETestFailure);
			TEST_ASSERT(gBottomControl == 4, ETestFailure);
			TEST_ASSERT(gAppUiControl == 4, ETestFailure);
			}
			break;

		case 32:
			{
			INFO_PRINTF1(_L("Update stacking flags for active view. TopControl refuses all key events"));
			TEST_ASSERT(UpdateActiveViewStackingFlags() == KErrNone, ETestFailure);
			}
			break;
		
		case 33:
			{
			INFO_PRINTF1(_L("Simulate normal key event 'E'"));
			TEST_ASSERT(SimulateKeyEvent('E') == KErrNone, ETestFailure);			
			}
			break;
		
		case 34:
			{
			INFO_PRINTF1(_L("TopControl refuses all key event, others receive it"));
			TEST_ASSERT(gTopControl == 5, ETestFailure);
			TEST_ASSERT(gBottomControl == 5, ETestFailure);
			TEST_ASSERT(gAppUiControl == 5, ETestFailure);
			}
			break;

		case 35:
			{
			INFO_PRINTF1(_L("Simulate normal key event 'C' (consumed by one of the controls!)"));
			TEST_ASSERT(SimulateKeyEvent('C') == KErrNone, ETestFailure);			
			}
			break;
		
		case 36:
			{
			INFO_PRINTF1(_L("BottomControl receives the key, as it's refused by TopControl although it has higher priority"));
			TEST_ASSERT(gTopControl == 5, ETestFailure);
			TEST_ASSERT(gBottomControl == 6, ETestFailure);
			TEST_ASSERT(gAppUiControl == 5, ETestFailure);
			iStep->RecordTestResultL();
			}
			break;


//----------------------------------------------------------------------------------------------

/**
  @SYMTestCaseID 			UIF-CONE-VIEW-0016
  @SYMPREQ 					Codebase
  @SYMTestCaseDesc			Negative testing using Cone view architecture support
  @SYMTestPriority 			High
  @SYMTestStatus 			Implemented
  @SYMTestActions 			Negative testing is implenented in this test case, with the following being done:
								- Activation of a non existing view, 
								- Activation of a non existing app
								- CheckSourceOfViewSwitchL leaves with KErrUnknown if called outside of 
									an implementation of MCoeView's ViewConstructL or ViewActivatedL
								- OOM testing.
  @SYMTestType 				CIT
  @SYMTestExpectedResults 	The framework behaves as expected returning the appropiate error return value.
*/

//----------------------------------------------------------------------------------------------

		case 40:
			{
			iStep->SetTestStepID(_L("UIF-CONE-VIEW-0016"));
			INFO_PRINTF1(_L("Activate view 5...ooops, it was removed (expecting to return KErrNotFound)"));
			TEST_ASSERT(ActivateView(VIEW_FIVE, TUid::Null(), KNullDes) == KErrNotFound, ETestFailure);	
			TVwsViewId activeViewId=KNullViewId;
			TEST_ASSERT(AppUi().GetActiveViewId(activeViewId) == KErrNone, ETestFailure);
			TEST_ASSERT(activeViewId.iViewUid.iUid == KUidTViewTwoValue, ETestFailure); 	// it doesn't change, so still view 2
			}
			break;
			
		case 41:
			{
			INFO_PRINTF1(_L("Activate missing app (expecting to return KErrNotFound)"));
			const TUid KUidPasswordMode={268435755}; 	// This UID defined in Uikon. Not an app.
			TEST_ASSERT(ActivateView(TVwsViewId(KUidPasswordMode, KUidTViewOne), TUid::Null(), KNullDes) == KErrNotFound, ETestFailure);
			TVwsViewId activeViewId=KNullViewId;
			TEST_ASSERT(AppUi().GetActiveViewId(activeViewId) == KErrNone, ETestFailure);
			TEST_ASSERT(activeViewId.iViewUid.iUid == KUidTViewTwoValue, ETestFailure); 	// it doesn't change, so still view 2
			}
			break;

		case 42:
			{
			INFO_PRINTF1(_L("Activate view 1"));
			TEST_ASSERT(ActivateView(VIEW_ONE, TUid::Null(), KNullDes) == KErrNone, ETestFailure);	

			TVwsViewId activeViewId=KNullViewId;
			TEST_ASSERT(AppUi().GetActiveViewId(activeViewId) == KErrNone, ETestFailure);
			TEST_ASSERT(activeViewId.iViewUid.iUid == KUidTViewOneValue, ETestFailure);

			TVwsViewId viewId=KNullViewId;
			AppUi().GetSystemDefaultViewL(viewId);
			TEST_ASSERT(viewId == VIEW_TWO, ETestFailure);
			}
			break;

		case 43:
			{
/*
PLEASE NOTE: 
This test case is related to DEF092434: Removing a view (which is active & system default) results in some confussion,
which was rejectes as "Not Going To Fix", as it was thought to be too complicated to solve without a Break Request

Include it whenever/if it is fixed later on
 
			INFO_PRINTF1(_L("Remove view 1 (normally it should panic, but it doesn't as it is the default system view too...(although for another mode!)"));
			TEST_ASSERT(RemoveView(VIEW_ONE) == KErrNone);

			TVwsViewId activeViewId=KNullViewId;
			TEST_ASSERT(AppUi().GetActiveViewId(activeViewId) == KErrNone);
			TEST_ASSERT(activeViewId.iViewUid.iUid != KUidTViewOneValue);
			INFO_PRINTF2(_L("activeViewId.iViewUid.iUid = %d"), activeViewId.iViewUid.iUid);

			TVwsViewId viewId=KNullViewId;
			AppUi().GetSystemDefaultViewL(viewId);			
			TEST_ASSERT(viewId == VIEW_TWO);								// view one was systemdefault view for aMode=1... */			
			}
			break;

		case 44:
			{
			INFO_PRINTF1(_L("Add view 2 for client 1 (which already has this view 2!)"));
			TEST_ASSERT(AddView(VIEW_TWO) == KErrNone, ETestFailure);
			}
			break;
			
		case 45:
			{
			INFO_PRINTF1(_L("Perform OOM testing over ActivateViewL"));
			TEST_ASSERT(TestActivateViewOOM(VIEW_TWO,KUidTws0CustomMesssageId,KCustomDes) == KErrNone, ETestFailure);
			}		
			break;
			
		case 46:
			{
			INFO_PRINTF1(_L("Perform OOM testing over AddViewL"));
			TEST_ASSERT(TestAddViewOOML(VIEW_FIVE) == KErrNone, ETestFailure);
			}
			break;

		case 47:
			{
			TInt r = 0;
			INFO_PRINTF1(_L("Calling CheckSourceOfViewSwitchL with a valid TVendorId..."));
			TRAPD(err, r = AppUi().CheckSourceOfViewSwitchL(TSecurityPolicy(TVendorId(0x70000001))));
			INFO_PRINTF3(_L("...leave error value ='%d', expected one ='%d'"), err, KErrUnknown);
			TEST_ASSERT(err == KErrUnknown, ETestFailure);
			INFO_PRINTF2(_L("...return value ='%d'"), r);
			TEST_ASSERT(!r, ETestFailure);

			INFO_PRINTF1(_L("Calling CheckSourceOfViewSwitchL with an invalid TVendorId..."));
			TRAP(err, r = AppUi().CheckSourceOfViewSwitchL(TSecurityPolicy(TVendorId(0x70000002))));
			INFO_PRINTF3(_L("...leave error value ='%d', expected one ='%d'"), err, KErrUnknown);
			TEST_ASSERT(err == KErrUnknown, ETestFailure);
			INFO_PRINTF2(_L("...return value ='%d'"), r);
			TEST_ASSERT(!r, ETestFailure);						
			iStep->RecordTestResultL();
			}
			break;
		

//----------------------------------------------------------------------------------------------

/**
  @SYMTestCaseID 			UIF-CONE-VIEW-0017
  @SYMPREQ 					Codebase
  @SYMTestCaseDesc			Add view activation and deactivation observers using Cone view architecture support
  @SYMTestPriority 			High
  @SYMTestStatus 			Implemented
  @SYMTestActions 			Observers are added to the application to check the correct observers are notified.
  								A counter is increased everytime the observer is notified, so the test performs
  								several view activations and deactivations to check that they are hit correctly.
								Also observers that call NotifyNextActivation are used, which should only be hit
								once.
								In addition, several consecutive activations (with and without message) are tested
								to test multiple activations
  @SYMTestType 				CIT
  @SYMTestExpectedResults 	For each view activation and deactivation the correct observers are notified and 
  							the counter associated to them corresponds with the expected value.
*/

//----------------------------------------------------------------------------------------------

		case 50:
			{
			iStep->SetTestStepID(_L("UIF-CONE-VIEW-0017"));
			INFO_PRINTF1(_L("Activate view 2"));
			TEST_ASSERT(ActivateView(VIEW_TWO, TUid::Null(), KNullDes) == KErrNone, ETestFailure);	
			TVwsViewId activeViewId=KNullViewId;
			TEST_ASSERT(AppUi().GetActiveViewId(activeViewId) == KErrNone, ETestFailure);
			TEST_ASSERT(activeViewId.iViewUid.iUid == KUidTViewTwoValue, ETestFailure);
			}
			break;
			
		case 51:
			{
			INFO_PRINTF1(_L("Add view activation / deactivation observers"));
			TEST_ASSERT(AddViewActivationObserverOne() == KErrNone, ETestFailure);
			TEST_ASSERT(AddViewActivationObserverTwo() == KErrNone, ETestFailure);
			TEST_ASSERT(AddViewDeactivationObserverOne() == KErrNone, ETestFailure);
			TEST_ASSERT(AddViewDeactivationObserverTwo() == KErrNone, ETestFailure);
			}
			break;
			
		case 52:
			{
			INFO_PRINTF1(_L("Add view 1 again for client 1 as it was previously removed"));
			TEST_ASSERT(AddView(VIEW_ONE) == KErrNone, ETestFailure);
			}
			break;
			
		case 53:
			{
			INFO_PRINTF1(_L("No activations / deactivations have been notified"));
			TEST_ASSERT(gViewActivationObserverOne == 0, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverOne == 0, ETestFailure);
			TEST_ASSERT(gViewActivationObserverTwo == 0, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverTwo == 0, ETestFailure);
			TEST_ASSERT(gViewActivationObserverNotify == 0, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverNotify == 0, ETestFailure);
			}
			break;

		case 54:
			{
			INFO_PRINTF1(_L("Activate view 1"));
			TEST_ASSERT(ActivateView(VIEW_ONE, TUid::Null(), KNullDes) == KErrNone, ETestFailure);	
			TVwsViewId activeViewId=KNullViewId;
			TEST_ASSERT(AppUi().GetActiveViewId(activeViewId) == KErrNone, ETestFailure);
			TEST_ASSERT(activeViewId.iViewUid.iUid == KUidTViewOneValue, ETestFailure);
			}
			break;
			
		case 55:
			{
			INFO_PRINTF1(_L("Both observer 1 & 2 have been notified of activation / deactivation"));
			TEST_ASSERT(gViewActivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewActivationObserverTwo == 1, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverTwo == 1, ETestFailure);
			TEST_ASSERT(gViewActivationObserverNotify == 0, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverNotify == 0, ETestFailure);
			}
			break;

		case 56:
			{
			INFO_PRINTF1(_L("Remove view activation / deactivation observer one"));
			TEST_ASSERT(RemoveViewDeactivationObserverOne() == KErrNone, ETestFailure);
			TEST_ASSERT(RemoveViewActivationObserverOne() == KErrNone, ETestFailure);
			}
			break;
		
		case 57:
			{
			INFO_PRINTF1(_L("Activate view 2"));
			TEST_ASSERT(ActivateView(VIEW_TWO, TUid::Null(), KNullDes) == KErrNone, ETestFailure);	
			TVwsViewId activeViewId=KNullViewId;
			TEST_ASSERT(AppUi().GetActiveViewId(activeViewId) == KErrNone, ETestFailure);
			TEST_ASSERT(activeViewId.iViewUid.iUid == KUidTViewTwoValue, ETestFailure);
			}
			break;
			
		case 58:
			{
			INFO_PRINTF1(_L("Check activations / deactivations have been notified for observer two"));
			TEST_ASSERT(gViewActivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewActivationObserverTwo == 2, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverTwo == 2, ETestFailure);
			TEST_ASSERT(gViewActivationObserverNotify == 0, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverNotify == 0, ETestFailure);
			}
			break;

		case 59:
			{
			INFO_PRINTF1(_L("Notify next activation"));
			TEST_ASSERT(NotifyActivation() == KErrNone, ETestFailure);
			}
			break;
		
		case 60:
			{
			INFO_PRINTF1(_L("Activate view 1"));
			TEST_ASSERT(ActivateView(VIEW_ONE, TUid::Null(), KNullDes) == KErrNone, ETestFailure);
			TVwsViewId activeViewId=KNullViewId;
			TEST_ASSERT(AppUi().GetActiveViewId(activeViewId) == KErrNone, ETestFailure);
			TEST_ASSERT(activeViewId.iViewUid.iUid == KUidTViewOneValue, ETestFailure);
			}
			break;
		
		case 61:
			{
			INFO_PRINTF1(_L("Check correct activations / deactivations have been notified"));
			TEST_ASSERT(gViewActivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewActivationObserverTwo == 3, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverTwo == 3, ETestFailure);
			TEST_ASSERT(gViewActivationObserverNotify == 1, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverNotify == 0, ETestFailure);
			}
			break;

		case 62:
			{
			INFO_PRINTF1(_L("Notify next deactivation"));
			TEST_ASSERT(NotifyDeactivation() == KErrNone, ETestFailure);
			}
			break;
		
		case 63:
			{
			INFO_PRINTF1(_L("Activate view 2"));
			TEST_ASSERT(ActivateView(VIEW_TWO, TUid::Null(), KNullDes) == KErrNone, ETestFailure);	
			TVwsViewId activeViewId=KNullViewId;
			TEST_ASSERT(AppUi().GetActiveViewId(activeViewId) == KErrNone, ETestFailure);
			TEST_ASSERT(activeViewId.iViewUid.iUid == KUidTViewTwoValue, ETestFailure);
			}
			break;

		case 64:
			{
			INFO_PRINTF1(_L("Check correct activations / deactivations have been notified"));
			TEST_ASSERT(gViewActivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewActivationObserverTwo == 4, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverTwo == 4, ETestFailure);
			TEST_ASSERT(gViewActivationObserverNotify == 1, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverNotify == 1, ETestFailure);
			}
			break;

		case 65:
			{
			INFO_PRINTF1(_L("Activate view 1, 2, 1, 2 ... test multiple activations"));
			TEST_ASSERT(ActivateView(VIEW_ONE,TUid::Null(),KNullDes) == KErrNone, ETestFailure);
			TEST_ASSERT(ActivateView(VIEW_TWO,TUid::Null(),KNullDes) == KErrNone, ETestFailure);
			TEST_ASSERT(ActivateView(VIEW_ONE,TUid::Null(),KNullDes) == KErrNone, ETestFailure);
			TEST_ASSERT(ActivateView(VIEW_TWO,TUid::Null(),KNullDes) == KErrNone, ETestFailure);
			TEST_ASSERT(ActivateView(VIEW_ONE,TUid::Null(),KNullDes) == KErrNone, ETestFailure);
			TEST_ASSERT(ActivateView(VIEW_TWO,TUid::Null(),KNullDes) == KErrNone, ETestFailure);
			TEST_ASSERT(ActivateView(VIEW_ONE,KUidTws0CustomMesssageId,KNullDes) == KErrNone, ETestFailure);
			TEST_ASSERT(ActivateView(VIEW_TWO,KUidTws0CustomMesssageId,KNullDes) == KErrNone, ETestFailure);
			TEST_ASSERT(ActivateView(VIEW_ONE,KUidTws0CustomMesssageId,KNullDes) == KErrNone, ETestFailure);
			TEST_ASSERT(ActivateView(VIEW_TWO,KUidTws0CustomMesssageId,KNullDes) == KErrNone, ETestFailure);
			TEST_ASSERT(ActivateView(VIEW_ONE,TUid::Null(),KNullDes) == KErrNone, ETestFailure);
			TEST_ASSERT(ActivateView(VIEW_TWO,TUid::Null(),KNullDes) == KErrNone, ETestFailure);
			TEST_ASSERT(ActivateView(VIEW_ONE,TUid::Null(),KNullDes) == KErrNone, ETestFailure);
			TEST_ASSERT(ActivateView(VIEW_TWO,TUid::Null(),KNullDes) == KErrNone, ETestFailure);
			}
			break;
		
		case 66:
			{
			INFO_PRINTF1(_L("Check activations / deactivations have been notified for observer two"));
			TEST_ASSERT(gViewActivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewActivationObserverTwo == 18, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverTwo == 18, ETestFailure);
			TEST_ASSERT(gViewActivationObserverNotify == 1, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverNotify == 1, ETestFailure);
			iStep->RecordTestResultL();
			}
			break;

			
//----------------------------------------------------------------------------------------------

/**
  @SYMTestCaseID 			UIF-CONE-VIEW-0018
  @SYMPREQ 					Codebase
  @SYMTestCaseDesc			Registers a pseudo-view for the application using Cone view architecture support
  @SYMTestPriority 			High
  @SYMTestStatus 			Implemented
  @SYMTestActions 			The test implements the registration of a pseudo-view after removing view 1. Once
  								this pseudo-view is in place, check that activating and deactivating it works as
  								expected. 
  								EKeyEvents are sent and controls are check to make sure the correct ones have been hit,
  								while the pseudo-view is active and while not.
  								In addition, the number of observers notifications is checked.  
  @SYMTestType 				CIT
  @SYMTestExpectedResults 	The pseudo-view is correctly added and activated. Also the correct observers and controls
  							are notified and the counter associated to them corresponds with the expected value.
*/

//----------------------------------------------------------------------------------------------

		case 80:
			{
			iStep->SetTestStepID(_L("UIF-CONE-VIEW-0018"));
			INFO_PRINTF1(_L("Remove view 1 (should be OK as it's not the active one)"));
			TEST_ASSERT(RemoveView(VIEW_ONE) == KErrNone, ETestFailure);

			TVwsViewId activeViewId=KNullViewId;
			TEST_ASSERT(AppUi().GetActiveViewId(activeViewId) == KErrNone, ETestFailure);
			TEST_ASSERT(activeViewId.iViewUid.iUid == KUidTViewTwoValue, ETestFailure);
			}
			break;

		case 81:
			{
			INFO_PRINTF1(_L("Check no activations / deactivations have been notified"));
			TEST_ASSERT(gViewActivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewActivationObserverTwo == 18, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverTwo == 18, ETestFailure);
			TEST_ASSERT(gViewActivationObserverNotify == 1, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverNotify == 1, ETestFailure);
			}
			break;

		case 82:
			{
			INFO_PRINTF1(_L("Simulate normal key event 'Z'"));
			TEST_ASSERT(SimulateKeyEvent('Z') == KErrNone, ETestFailure);			
			}
			break;
		
		case 83:
			{
			INFO_PRINTF1(_L("TopControl refuses all key event, others receive it"));
			TEST_ASSERT(gTopControl == 5, ETestFailure);
			TEST_ASSERT(gBottomControl == 7, ETestFailure);
			TEST_ASSERT(gAppUiControl == 6, ETestFailure);
			}
			break;

		case 84:
			{
			INFO_PRINTF1(_L("Add application view ('pseudo' view)"));
			TEST_ASSERT(AddApplicationView() == KErrNone, ETestFailure);
			}
			break;
		
		case 85:
			{
			INFO_PRINTF1(_L("Check no activations / deactivations have been notified"));
			TEST_ASSERT(gViewActivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewActivationObserverTwo == 18, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverTwo == 18, ETestFailure);
			TEST_ASSERT(gViewActivationObserverNotify == 1, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverNotify == 1, ETestFailure);
			}
			break;

		case 86:
			{
			INFO_PRINTF1(_L("Activate application view"));
			TEST_ASSERT(ActivateApplicationView() == KErrNone, ETestFailure);

			TVwsViewId activeViewId=KNullViewId;
			TEST_ASSERT(AppUi().GetActiveViewId(activeViewId) == KErrNone, ETestFailure);
			TEST_ASSERT(activeViewId.iViewUid.iUid == KUidTViewAppOneValue, ETestFailure);
			TEST_ASSERT(activeViewId.iAppUid.iUid == KUidTViewAppOneValue, ETestFailure);
			}
			break;
		
		case 87:
			{
			INFO_PRINTF1(_L("Check correct activations / deactivations have been notified"));
			TEST_ASSERT(gViewActivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewActivationObserverTwo == 19, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverTwo == 19, ETestFailure);
			TEST_ASSERT(gViewActivationObserverNotify == 1, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverNotify == 1, ETestFailure);
			}
			break;
			
		case 88:
			{
			INFO_PRINTF1(_L("Simulate normal key event 'Y'"));
			TEST_ASSERT(SimulateKeyEvent('Y') == KErrNone, ETestFailure);			
			}
			break;
		
		case 89:
			{
			INFO_PRINTF1(_L("Just AppUi receives the key event"));
			TEST_ASSERT(gTopControl == 5, ETestFailure);
			TEST_ASSERT(gBottomControl == 7, ETestFailure);
			TEST_ASSERT(gAppUiControl == 7, ETestFailure);
			}
			break;

		case 90:
			{
			INFO_PRINTF1(_L("Activate view 2"));
			TEST_ASSERT(ActivateView(VIEW_TWO,TUid::Null(),KNullDes) == KErrNone, ETestFailure);
			TVwsViewId activeViewId=KNullViewId;
			TEST_ASSERT(AppUi().GetActiveViewId(activeViewId) == KErrNone, ETestFailure);
			TEST_ASSERT(activeViewId.iViewUid.iUid == KUidTViewTwoValue, ETestFailure);
			}
			break;
		
		case 91:
			{
			INFO_PRINTF1(_L("Check correct activations / deactivations have been notified"));
			TEST_ASSERT(gViewActivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewActivationObserverTwo == 20, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverTwo == 20, ETestFailure);
			TEST_ASSERT(gViewActivationObserverNotify == 1, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverNotify == 1, ETestFailure);
			}
			break;

		case 92:
			{
			INFO_PRINTF1(_L("Remove application view"));
			TEST_ASSERT(RemoveApplicationView() == KErrNone, ETestFailure);
			TVwsViewId activeViewId=KNullViewId;
			TEST_ASSERT(AppUi().GetActiveViewId(activeViewId) == KErrNone, ETestFailure);
			TEST_ASSERT(activeViewId.iViewUid.iUid == KUidTViewTwoValue, ETestFailure);
			iStep->RecordTestResultL();
			}
			break;

		
//----------------------------------------------------------------------------------------------

/**
  @SYMTestCaseID 			UIF-CONE-VIEW-0019
  @SYMPREQ 					Codebase
  @SYMTestCaseDesc			Create an embedded appUi using Cone view architecture support
  @SYMTestPriority 			High
  @SYMTestStatus 			Implemented
  @SYMTestActions 			The test implements the creation of an embedded appUi. Once this app is in place
  								views 3 and 4 are added to it. Check the activation and deactivation of these
  								views works as expected.
  								In addition, the number of observers notifications is checked.
  								It has to be noted here that when activating embedded appUi views, the current 
  								active view for the normal appUi is not fully deactivated, hence no observers 
  								receive notifications.  
  								Note: The implementation of this test does not fully comform with the actual
  								concept of what a standard embedded appUi is. For a fully meaningful test, it
  								should be changed to be a complete embedded app. 
  								have any relationship with other windows or views.
  @SYMTestType 				CIT
  @SYMTestExpectedResults 	The embedded is correctly created and activated. Also the correct observers 
  							are notified and the counter associated to them corresponds with the expected value.
*/

//----------------------------------------------------------------------------------------------

		case 100:
			{
			iStep->SetTestStepID(_L("UIF-CONE-VIEW-0019"));
			INFO_PRINTF1(_L("Create 'embedded' appUi (not a proper embedded appUi though...)"));
			RDebug::Print(_L("CTestDriver case100: Create 'embedded' appUi (not a proper embedded appUi though...)"));
			TEST_ASSERT(ConstructEmbeddedAppUi() == KErrNone, ETestFailure);
			}
			break;
		
		case 101:
			{
			INFO_PRINTF1(_L("Check no activations / deactivations have been notified"));
			RDebug::Print(_L("CTestDriver case101: Check no activations / deactivations have been notified"));
			TEST_ASSERT(gViewActivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewActivationObserverTwo == 20, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverTwo == 20, ETestFailure);
			TEST_ASSERT(gViewActivationObserverNotify == 1, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverNotify == 1, ETestFailure);
			}
			break;

		case 102:
			{
			INFO_PRINTF1(_L("Add views 3 and 4 for embedded appUi"));
			RDebug::Print(_L("CTestDriver case102: Add views 3 and 4 for embedded appUi"));
			TEST_ASSERT(AddView(VIEW_THREE,KTVwaEmbeddedAppUiId) == KErrNone, ETestFailure);
			TEST_ASSERT(AddView(VIEW_FOUR,KTVwaEmbeddedAppUiId) == KErrNone, ETestFailure);
			}
			break;
		
		case 103:
			{
			INFO_PRINTF1(_L("Set default view for embedded appUi to view 3"));
			RDebug::Print(_L("CTestDriver case103: Set default view for embedded appUi to view 3"));
			TEST_ASSERT(SetDefaultView(VIEW_THREE,KTVwaEmbeddedAppUiId) == KErrNone, ETestFailure);			
			TVwsViewId viewId=KNullViewId;
			TEST_ASSERT(GetDefaultView(viewId,KTVwaEmbeddedAppUiId) == KErrNone, ETestFailure);			
			TEST_ASSERT(viewId == VIEW_THREE, ETestFailure);
			}
			break;
		
		case 104:
			{
			INFO_PRINTF1(_L("Check there's no activate view for embedded appUi until we activate top view (must be view 3)"));
			RDebug::Print(_L("CTestDriver case104: Check there's no activate view for embedded appUi until we activate top view (must be view 3)"));
			TVwsViewId activeViewId=KNullViewId;
			TEST_ASSERT(AppUi(KTVwaEmbeddedAppUiId).GetActiveViewId(activeViewId) == KErrNotFound, ETestFailure);
			TEST_ASSERT(activeViewId == KNullViewId, ETestFailure);

			TEST_ASSERT(ActivateTopView(KTVwaEmbeddedAppUiId) == KErrNone, ETestFailure);			
			TEST_ASSERT(AppUi(KTVwaEmbeddedAppUiId).GetActiveViewId(activeViewId) == KErrNone, ETestFailure);
			TEST_ASSERT(activeViewId.iViewUid.iUid == KUidTViewThreeValue, ETestFailure);

			INFO_PRINTF1(_L("view 2 still must be active for appUi (embedded view does not fully deactive view 2)"));
			RDebug::Print(_L("CTestDriver: view 2 still must be active for appUi (embedded view does not fully deactive view 2)"));
			activeViewId=KNullViewId;
			TEST_ASSERT(AppUi().GetActiveViewId(activeViewId) == KErrNone, ETestFailure);
			TEST_ASSERT(activeViewId.iViewUid.iUid == KUidTViewTwoValue, ETestFailure);
			}
			break;
		
		case 105:
			{
			INFO_PRINTF1(_L("Check no activations / deactivations have been notified"));
			RDebug::Print(_L("CTestDriver case105: Check no activations / deactivations have been notified"));
			TEST_ASSERT(gViewActivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewActivationObserverTwo == 20, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverTwo == 20, ETestFailure);
			TEST_ASSERT(gViewActivationObserverNotify == 1, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverNotify == 1, ETestFailure);
			}
			break;

		case 106:
			{
			INFO_PRINTF1(_L("Activate view 4"));
			RDebug::Print(_L("CTestDriver case106: Activate view 4"));
			TEST_ASSERT(ActivateView(VIEW_FOUR,TUid::Null(),KNullDes,KTVwaEmbeddedAppUiId) == KErrNone, ETestFailure);		
			TVwsViewId activeViewId=KNullViewId;
			TEST_ASSERT(AppUi(KTVwaEmbeddedAppUiId).GetActiveViewId(activeViewId) == KErrNone, ETestFailure);
			TEST_ASSERT(activeViewId.iViewUid.iUid == KUidTViewFourValue, ETestFailure);

			INFO_PRINTF1(_L("view 2 still must be active for appUi (embedded view does not fully deactive view 2)"));
			RDebug::Print(_L("CTestDriver: view 2 still must be active for appUi (embedded view does not fully deactive view 2)"));
			activeViewId=KNullViewId;
			TEST_ASSERT(AppUi().GetActiveViewId(activeViewId) == KErrNone, ETestFailure);
			TEST_ASSERT(activeViewId.iViewUid.iUid == KUidTViewTwoValue, ETestFailure);
			}
			break;
		
		case 107:
			{
			INFO_PRINTF1(_L("Check no activations / deactivations have been notified"));
			RDebug::Print(_L("CTestDriver case107: Check no activations / deactivations have been notified"));
			TEST_ASSERT(gViewActivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewActivationObserverTwo == 20, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverTwo == 20, ETestFailure);
			TEST_ASSERT(gViewActivationObserverNotify == 1, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverNotify == 1, ETestFailure);
			}
			break;

		case 108:
			{
			INFO_PRINTF1(_L("Add view 1 again for client 1 as it was previously removed"));
			RDebug::Print(_L("CTestDriver case108: Add view 1 again for client 1 as it was previously removed"));
			TEST_ASSERT(AddView(VIEW_ONE) == KErrNone, ETestFailure);
			}
			break;
			
		case 109:
			{
			INFO_PRINTF1(_L("Activate view 1"));
			RDebug::Print(_L("CTestDriver case109: Activate view 1"));
			TEST_ASSERT(ActivateView(VIEW_ONE, TUid::Null(), KNullDes) == KErrNone, ETestFailure);		
			TVwsViewId activeViewId=KNullViewId;
			TEST_ASSERT(AppUi().GetActiveViewId(activeViewId) == KErrNone, ETestFailure);
			TEST_ASSERT(activeViewId.iViewUid.iUid == KUidTViewOneValue, ETestFailure);

			INFO_PRINTF1(_L("embedded appUi views are not active"));
			RDebug::Print(_L("CTestDriver: embedded appUi views are not active"));
			activeViewId=KNullViewId;
			TEST_ASSERT(AppUi(KTVwaEmbeddedAppUiId).GetActiveViewId(activeViewId) == KErrNotFound, ETestFailure);
			TEST_ASSERT(activeViewId == KNullViewId, ETestFailure);
			}
			break;
		
		case 110:
			{
			INFO_PRINTF1(_L("Check correct activations / deactivations have been notified"));
			RDebug::Print(_L("CTestDriver case110: Check correct activations / deactivations have been notified"));
			TEST_ASSERT(gViewActivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewActivationObserverTwo == 21, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverTwo == 21, ETestFailure);
			TEST_ASSERT(gViewActivationObserverNotify == 1, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverNotify == 1, ETestFailure);
			}
			break;

		case 111:
			{
			INFO_PRINTF1(_L("Activate view 2"));
			RDebug::Print(_L("CTestDriver case111: Activate view 2"));
			TEST_ASSERT(ActivateView(VIEW_TWO, TUid::Null(), KNullDes) == KErrNone, ETestFailure);		
			TVwsViewId activeViewId=KNullViewId;
			TEST_ASSERT(AppUi().GetActiveViewId(activeViewId) == KErrNone, ETestFailure);
			TEST_ASSERT(activeViewId.iViewUid.iUid == KUidTViewTwoValue, ETestFailure);

			INFO_PRINTF1(_L("embedded appUi views are not active"));
			RDebug::Print(_L("CTestDriver: embedded appUi views are not active"));
			activeViewId=KNullViewId;
			TEST_ASSERT(AppUi(KTVwaEmbeddedAppUiId).GetActiveViewId(activeViewId) == KErrNotFound, ETestFailure);
			TEST_ASSERT(activeViewId == KNullViewId, ETestFailure);
			}
			break;
		
		case 112:
			{
			INFO_PRINTF1(_L("Check correct activations / deactivations have been notified"));
			RDebug::Print(_L("CTestDriver case112: Check correct activations / deactivations have been notified"));
			TEST_ASSERT(gViewActivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewActivationObserverTwo == 22, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverTwo == 22, ETestFailure);
			TEST_ASSERT(gViewActivationObserverNotify == 1, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverNotify == 1, ETestFailure);
			}
			break;

		case 113:
			{
			INFO_PRINTF1(_L("Activate view 1"));
			RDebug::Print(_L("CTestDriver case113: Activate view 1"));
			TEST_ASSERT(ActivateView(VIEW_ONE, TUid::Null(), KNullDes) == KErrNone, ETestFailure);		
			TVwsViewId activeViewId=KNullViewId;
			TEST_ASSERT(AppUi().GetActiveViewId(activeViewId) == KErrNone, ETestFailure);
			TEST_ASSERT(activeViewId.iViewUid.iUid == KUidTViewOneValue, ETestFailure);

			INFO_PRINTF1(_L("embedded appUi views are not active"));
			RDebug::Print(_L("CTestDriver: embedded appUi views are not active"));
			activeViewId=KNullViewId;
			TEST_ASSERT(AppUi(KTVwaEmbeddedAppUiId).GetActiveViewId(activeViewId) == KErrNotFound, ETestFailure);
			TEST_ASSERT(activeViewId == KNullViewId, ETestFailure);
			}
			break;
		
		case 114:
			{
			INFO_PRINTF1(_L("Check correct activations / deactivations have been notified"));
			RDebug::Print(_L("CTestDriver case114: Check correct activations / deactivations have been notified"));
			TEST_ASSERT(gViewActivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewActivationObserverTwo == 23, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverTwo == 23, ETestFailure);
			TEST_ASSERT(gViewActivationObserverNotify == 1, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverNotify == 1, ETestFailure);
			}
			break;

		case 115:
			{
			INFO_PRINTF1(_L("Activate view 3"));
			RDebug::Print(_L("CTestDriver case115: Activate view 3"));
			TEST_ASSERT(ActivateView(VIEW_THREE,TUid::Null(),KNullDes,KTVwaEmbeddedAppUiId) == KErrNone, ETestFailure);		
			TVwsViewId activeViewId=KNullViewId;
			TEST_ASSERT(AppUi(KTVwaEmbeddedAppUiId).GetActiveViewId(activeViewId) == KErrNone, ETestFailure);
			TEST_ASSERT(activeViewId.iViewUid.iUid == KUidTViewThreeValue, ETestFailure);

			INFO_PRINTF1(_L("view 1 still must be active for appUi (embedded view does not fully deactive view 2)"));
			RDebug::Print(_L("CTestDriver: view 1 still must be active for appUi (embedded view does not fully deactive view 2)"));
			activeViewId=KNullViewId;
			TEST_ASSERT(AppUi().GetActiveViewId(activeViewId) == KErrNone, ETestFailure);
			TEST_ASSERT(activeViewId.iViewUid.iUid == KUidTViewOneValue, ETestFailure);
			}
			break;
		
		case 116:
			{
			INFO_PRINTF1(_L("Check no activations / deactivations have been notified"));
			RDebug::Print(_L("CTestDriver case116: Check no activations / deactivations have been notified"));
			TEST_ASSERT(gViewActivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewActivationObserverTwo == 23, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverTwo == 23, ETestFailure);
			TEST_ASSERT(gViewActivationObserverNotify == 1, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverNotify == 1, ETestFailure);
			}
			break;

		case 117:
			{
			INFO_PRINTF1(_L("Destroy emdedded appUi"));
			RDebug::Print(_L("CTestDriver case117: Destroy emdedded appUi"));
			TEST_ASSERT(DestroyEmbeddedAppUi() == KErrNone, ETestFailure);
			}
			break;

		case 118:
			{
			INFO_PRINTF1(_L("Check no activations / deactivations have been notified"));
			RDebug::Print(_L("CTestDriver case118: Check no activations / deactivations have been notified"));
			TEST_ASSERT(gViewActivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewActivationObserverTwo == 23, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverTwo == 23, ETestFailure);
			TEST_ASSERT(gViewActivationObserverNotify == 1, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverNotify == 1, ETestFailure);
			iStep->RecordTestResultL();
			}
			break;


//----------------------------------------------------------------------------------------------

/**
  @SYMTestCaseID 			UIF-CONE-VIEW-0020
  @SYMPREQ 					Codebase
  @SYMTestCaseDesc			Notify next activation with viewId using Cone view architecture support
  @SYMTestPriority 			High
  @SYMTestStatus 			Implemented
  @SYMTestActions 			The test implements the activation and deactivation of a view while registering an observer
  								to be notified for the next activation and deactivation, but with the difference
  								that now we only want to be notified for a certain viewId, not any of them.
  @SYMTestType 				CIT
  @SYMTestExpectedResults 	The appropiate observer is notified and the counter associated to them corresponds with the expected value
  							after the view with viewId is activated and / or deactivated.
*/

//----------------------------------------------------------------------------------------------

		case 130:
			{
			iStep->SetTestStepID(_L("UIF-CONE-VIEW-0020"));
			INFO_PRINTF1(_L("Activate top view for client 1 (should be a no-op)"));
			RDebug::Print(_L("CTestDriver case130: Activate top view for client 1 (should be a no-op)"));
			TEST_ASSERT(ActivateTopView() == KErrNone, ETestFailure);
			TVwsViewId activeViewId=KNullViewId;
			TEST_ASSERT(AppUi().GetActiveViewId(activeViewId) == KErrNone, ETestFailure);
			TEST_ASSERT(activeViewId.iViewUid.iUid == KUidTViewOneValue, ETestFailure);
			}
			break;
		
		case 131:
			{
			INFO_PRINTF1(_L("Check no activations / deactivations have been notified"));
			RDebug::Print(_L("CTestDriver case131: Check no activations / deactivations have been notified"));
			TEST_ASSERT(gViewActivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewActivationObserverTwo == 23, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverTwo == 23, ETestFailure);
			TEST_ASSERT(gViewActivationObserverNotify == 1, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverNotify == 1, ETestFailure);
			}
			break;

		case 132:
			{
			INFO_PRINTF1(_L("Notify next activation & deactivation with view id (view 1)"));
			RDebug::Print(_L("CTestDriver case132: Notify next activation & deactivation with view id (view 1)"));
			TEST_ASSERT(NotifyActivationWithViewId(VIEW_ONE) == KErrNone, ETestFailure);
			TEST_ASSERT(NotifyDeactivationWithViewId(VIEW_ONE) == KErrNone, ETestFailure);
			}
			break;
		
		case 133:
			{
			INFO_PRINTF1(_L("Activate view 2"));
			RDebug::Print(_L("CTestDriver case133: Activate view 2"));
			TEST_ASSERT(ActivateView(VIEW_TWO, TUid::Null(), KNullDes) == KErrNone, ETestFailure);		
			TVwsViewId activeViewId=KNullViewId;
			TEST_ASSERT(AppUi().GetActiveViewId(activeViewId) == KErrNone, ETestFailure);
			TEST_ASSERT(activeViewId.iViewUid.iUid == KUidTViewTwoValue, ETestFailure);
			}
			break;
		
		case 134:
			{
			INFO_PRINTF1(_L("Check correct activations / deactivations have been notified (also deactivation notifier"));
			RDebug::Print(_L("CTestDriver case134: Check correct activations / deactivations have been notified (also deactivation notifier"));
			TEST_ASSERT(gViewActivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewActivationObserverTwo == 24, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverTwo == 24, ETestFailure);
			TEST_ASSERT(gViewActivationObserverNotify == 1, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverNotify == 2, ETestFailure);
			}
			break;

		case 135:
			{
			INFO_PRINTF1(_L("Activate view 1"));
			RDebug::Print(_L("CTestDriver case135: Activate view 1"));
			TEST_ASSERT(ActivateView(VIEW_ONE, TUid::Null(), KNullDes) == KErrNone, ETestFailure);		
			TVwsViewId activeViewId=KNullViewId;
			TEST_ASSERT(AppUi().GetActiveViewId(activeViewId) == KErrNone, ETestFailure);
			TEST_ASSERT(activeViewId.iViewUid.iUid == KUidTViewOneValue, ETestFailure);
			}
			break;
		
		case 137:
			{
			INFO_PRINTF1(_L("Check correct activations / deactivations have been notified (also activation notifier"));
			RDebug::Print(_L("CTestDriver case137: Check correct activations / deactivations have been notified (also activation notifier"));
			TEST_ASSERT(gViewActivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewActivationObserverTwo == 25, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverTwo == 25, ETestFailure);
			TEST_ASSERT(gViewActivationObserverNotify == 2, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverNotify == 2, ETestFailure);
			}
			break;

		case 138:
			{
			INFO_PRINTF1(_L("Deactivate active view (results in none being active)"));
			RDebug::Print(_L("CTestDriver case138: Deactivate active view (results in none being active)"));
			TEST_ASSERT(DeactivateActiveView() == KErrNone, ETestFailure);
			TVwsViewId activeViewId=KNullViewId;
			TEST_ASSERT(AppUi().GetActiveViewId(activeViewId) == KErrNotFound, ETestFailure);
			TEST_ASSERT(activeViewId == KNullViewId, ETestFailure);
			}
			break;
		
		case 139:
			{
			INFO_PRINTF1(_L("Check correct activations / deactivations have been notified"));
			RDebug::Print(_L("CTestDriver case139: Check correct activations / deactivations have been notified"));
			TEST_ASSERT(gViewActivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewActivationObserverTwo == 25, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverTwo == 26, ETestFailure);
			TEST_ASSERT(gViewActivationObserverNotify == 2, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverNotify == 2, ETestFailure);
			}
			break;

		case 140:
			{
			INFO_PRINTF1(_L("Remove view 1 & 2 (should be ok as none of them is active)"));
			RDebug::Print(_L("CTestDriver case140: Remove view 1 & 2 (should be ok as none of them is active)"));
			TEST_ASSERT(RemoveView(VIEW_ONE) == KErrNone, ETestFailure);
			TEST_ASSERT(RemoveView(VIEW_TWO) == KErrNone, ETestFailure);
			}
			break;

		case 141:
			{
			INFO_PRINTF1(_L("Register and Deregister view 1"));
			RDebug::Print(_L("CTestDriver case141: Register and Deregister view 1"));
			TEST_ASSERT(RegisterAndDeregisterView() == KErrNone, ETestFailure);
			}
  			break;
		
		case 142:
			{
			INFO_PRINTF1(_L("Check correct activations / deactivations have been notified"));
			RDebug::Print(_L("CTestDriver case142: Check correct activations / deactivations have been notified"));
			TEST_ASSERT(gViewActivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverOne == 1, ETestFailure);
			TEST_ASSERT(gViewActivationObserverTwo == 25, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverTwo == 26, ETestFailure);
			TEST_ASSERT(gViewActivationObserverNotify == 2, ETestFailure);
			TEST_ASSERT(gViewDeactivationObserverNotify == 2, ETestFailure);
			iStep->RecordTestResultL();
			}
			break;

//----------------------------------------------------------------------------------------------			

/**
@SYMTestCaseID 			UIF-CONE-VIEW-0032
@SYMTestCaseDesc		Check that calling RemoveViewActivationObserver with an invalid pointer does not panic
@SYMTestPriority 		High
@SYMTestStatus 			Implemented
@SYMTestActions 		Create a CViewActivationObserver object and then call
						AppUi().RemoveViewActivationObserver with the object.  Do not activate beforehand.
@SYMTestType 			CIT
@SYMTestExpectedResults In debug more there is a log put in the log output.
*/
		case 143:
			{
			iStep->SetTestStepID(_L("UIF-CONE-VIEW-0032"));
			INFO_PRINTF1(_L("Calling RemoveViewActivationObserver with invalid data"));
			RDebug::Print(_L("CTestDriver case143: Calling RemoveViewActivationObserver with invalid data"));
			TEST_ASSERT(TestRemoveViewActivationObserverL()==KErrNone, ETestFailure);
			iStep->RecordTestResultL();
			iStep->CloseTMSGraphicsStep();
			}
			break;		

//----------------------------------------------------------------------------------------------
//
//	FINISHING TEST CASES...
//
//----------------------------------------------------------------------------------------------

		case 150:
			INFO_PRINTF1(_L("End of valid tests cases..."));
			RDebug::Print(_L("CTestDriver case150: End of valid tests cases..."));
			return(EFinished);
  			//break;

		case KExitTestNum:
			Exit();
			break;
		
		default:
			break;
		}
	return(ENext);
	}


TInt CTestDriver::SimulateKeyEvent(const TInt aCode)
	{
	TKeyEvent event;
	event.iCode=aCode;
	event.iScanCode=aCode;
	event.iModifiers=1;
	event.iRepeats=0;

	TRAPD(err,CCoeEnv::Static()->SimulateKeyEventL(event,EEventKey));
	return err;
	}

TInt CTestDriver::NotifyActivation()
	{
	AppUi().NotifyNextActivation(*iViewActivationObserver_Notify);
	return KErrNone;
	}

TInt CTestDriver::NotifyDeactivation()
	{
	AppUi().NotifyNextDeactivation(*iViewDeactivationObserver_Notify);
	return KErrNone;
	}

TInt CTestDriver::NotifyActivationWithViewId(const TVwsViewId& aViewId)
	{
	AppUi().NotifyNextActivation(aViewId, *iViewActivationObserver_Notify);
	return KErrNone;
	}

TInt CTestDriver::NotifyDeactivationWithViewId(const TVwsViewId& aViewId)
	{
	AppUi().NotifyNextDeactivation(aViewId, *iViewDeactivationObserver_Notify);
	return KErrNone;
	}
	
TInt CTestDriver::RegisterAndDeregisterView()
	{
	TRAPD(err,
		CTVwaTestAppUi& appUi=AppUi(KTVwaStandardAppUiId);
		CTestView* view=new(ELeave) CTestView(VIEW_ONE,appUi);
		CleanupStack::PushL(view);
		appUi.RegisterViewL(*view);
		appUi.DeregisterView(*view);
		CleanupStack::PopAndDestroy(view);
		);
	return err;
	}

TInt CTestDriver::AddView(const TVwsViewId& aViewId,TInt aAppUiId)
	{
	TRAPD(err,
		CTVwaTestAppUi& appUi=AppUi(aAppUiId);
		CTestView* view=new(ELeave) CTestView(aViewId,appUi);
		appUi.AddViewL(view);	// transfers ownership at start
		);
	return err;
	}

TInt CTestDriver::AddApplicationView()
	{
	TRAPD(err,AppUi().RegisterApplicationViewL(KUidTViewAppOne));
	return err;
	}

TInt CTestDriver::ActivateApplicationView()
	{
	TRAPD(err,iAppUi.ActivateViewL(TVwsViewId(KUidTViewAppOne,KUidTViewAppOne)));
	return err;
	}

TInt CTestDriver::RemoveApplicationView()
	{
	TRAPD(err,AppUi().DeregisterApplicationView());
	return err;
	}

TInt CTestDriver::DeactivateActiveView()
	{
	TRAPD(err,iAppUi.iViewManager->iVwsSession->DeactivateActiveView());
	return err;
	}

TInt CTestDriver::ActivateView(const TVwsViewId& aViewId,TUid aCustomMessageId,const TDesC16& aCustomMessage,TInt aAppUiId)
	{
	TRAPD(err,AppUi(aAppUiId).ActivateViewL(aViewId,aCustomMessageId,aCustomMessage));
	return err;
	}

TInt CTestDriver::ActivateTopView(TInt aAppUiId)
	{
	TRAPD(err,AppUi(aAppUiId).ActivateTopViewL());
	return err;
	}

TInt CTestDriver::SetDefaultView(const TVwsViewId& aViewId,TInt aAppUiId)
	{
	TRAPD(err,AppUi(aAppUiId).SetDefaultViewL(*(AppUi(aAppUiId).ViewById(aViewId))));
	return err;
	}

TInt CTestDriver::GetDefaultView(TVwsViewId& aViewId,TInt aAppUiId)
	{
	return AppUi(aAppUiId).GetDefaultViewId(aViewId);
	}

TInt CTestDriver::RemoveView(const TVwsViewId& aViewId,TInt aAppUiId)
	{
	TRAPD(err,
		CTVwaTestAppUi& appUi=AppUi(aAppUiId);
		CTestView* view=appUi.ViewById(aViewId);
		AppUi().RemoveView(*view)
		);
	return err;
	}

TInt CTestDriver::UpdateActiveViewStackingFlags()
	{
	TRAPD(err,AppUi().ActiveView()->UpdateControlStackingFlags());
	return err;
	}

TInt CTestDriver::UpdateActiveViewPriorities()
	{
	TRAPD(err,AppUi().ActiveView()->UpdateControlPriorityL());
	return err;
	}

TInt CTestDriver::AddViewActivationObserverOne()
	{
	TRAPD(err,AppUi().AddViewActivationObserverL(iViewActivationObserverOne));
	return err;
	}

TInt CTestDriver::RemoveViewActivationObserverOne()
	{
	TRAPD(err,AppUi().RemoveViewActivationObserver(iViewActivationObserverOne));
	return err;
	}

TInt CTestDriver::AddViewDeactivationObserverOne()
	{
	TRAPD(err,AppUi().AddViewDeactivationObserverL(iViewDeactivationObserverOne));
	return err;
	}

TInt CTestDriver::RemoveViewDeactivationObserverOne()
	{
	TRAPD(err,AppUi().RemoveViewDeactivationObserver(iViewDeactivationObserverOne));
	return err;
	}

TInt CTestDriver::AddViewActivationObserverTwo()
	{
	TRAPD(err,AppUi().AddViewActivationObserverL(iViewActivationObserverTwo));
	return err;
	}

TInt CTestDriver::AddViewDeactivationObserverTwo()
	{
	TRAPD(err,AppUi().AddViewDeactivationObserverL(iViewDeactivationObserverTwo));
	return err;
	}

/* 
The term embedded appUi here is a missuse of the concept of embedded app. This is not a fully
embedded app, which means that the resulting app will not have the same behaviour as a proper
embedded one (for exaple, appUi and embedded appUi are sharing hte same CCoeEnv, ....).
*/
TInt CTestDriver::ConstructEmbeddedAppUi()
	{
	TRAPD(err,
		iAppUiEmbedded=new(ELeave) CTVwaTestAppUi();
		CCoeEnv::Static()->SetAppUi(iAppUiEmbedded);
		iAppUiEmbedded->ConstructL(&iAppUi);
		);
	return err;
	}

TInt CTestDriver::DestroyEmbeddedAppUi()
	{
	TRAPD(err,
		CCoeEnv::Static()->SetAppUi(&iAppUi);
		delete iAppUiEmbedded;
		);
	return err;
	}

TInt CTestDriver::TestActivateViewOOM(const TVwsViewId& aViewId,TUid aCustomMessageId,const TDesC16& aCustomMessage,TInt aAppUiId)
	{
	TInt err=KErrNoMemory;
	TInt failRate=0;
	for(failRate=1; err==KErrNoMemory; failRate++)
		{
		__UHEAP_SETFAIL(RHeap::EDeterministic, failRate);
		__UHEAP_MARK;
		TRAP(err, AppUi(aAppUiId).ActivateViewL(aViewId,aCustomMessageId,aCustomMessage));
		__UHEAP_MARKEND;
		__UHEAP_RESET;
		TEST_ASSERT(err==KErrNoMemory || err==KErrNone, ETestFailure);
		}
	INFO_PRINTF2(_L("ActivateViewL succeded after %d attempts."), failRate - 1);
	return err;	
	}

TInt CTestDriver::TestAddViewOOML(const TVwsViewId& aViewId,TInt aAppUiId)
	{
	CTVwaTestAppUi& appUi=AppUi(aAppUiId);
	CTestView* view=new(ELeave) CTestView(aViewId,appUi);
	CleanupStack::PushL(view);

	TInt err=KErrNoMemory;
	TInt failRate=1;
	for(failRate=1; err==KErrNoMemory; failRate++)
		{
		__UHEAP_SETFAIL(RHeap::EDeterministic, failRate);
		__UHEAP_MARK;
		TRAP(err, appUi.RegisterViewL(*view));
		TEST_ASSERT(err==KErrNoMemory || err==KErrNone, ETestFailure);
		if (err == KErrNone)
			{
			appUi.DeregisterView(*view);
			}
		__UHEAP_MARKEND;
		__UHEAP_RESET;
		}

	CleanupStack::PopAndDestroy(view);

	INFO_PRINTF2(_L("AddViewL succeded after %d attempts."), failRate - 1);
	return err;	
	}

TInt CTestDriver::TestRemoveViewActivationObserverL()
	{
	CViewActivationObserver* observer;
	observer=CViewActivationObserver::NewL(KViewActivationObserverThreeId);
	AppUi().RemoveViewActivationObserver(observer);
	delete observer;
	return KErrNone;
	}

/*************************************************************
 **  
 **  CTVwaTestAppUi
 **  
 *************************************************************/

const TInt KAppViewArrayGranularity=5;

CTVwaTestAppUi::CTVwaTestAppUi()
	:iAppViewArray(KAppViewArrayGranularity)
	{
	}


TKeyResponse CTVwaTestAppUi::HandleKeyEventL(const TKeyEvent& /*aKeyEvent*/,TEventCode /*aType*/)
    {
	return EKeyWasConsumed;
    }


void CTVwaTestAppUi::ConstructL(CTmsTestStep* aStep, CCoeAppUi* aPrevious)
	{
	CCoeAppUi::ConstructL(aPrevious);

	iDriver=new (ELeave) CTestDriver(*this, aStep); 
	iDriver->ConstructL();

	iControl=new (ELeave) CAppUiTestControl();
	iControl->ConstructL();
	AddToStackL(iControl,ECoeStackPriorityDefault-10);
	}


void CTVwaTestAppUi::AddViewL(CTestView* aView)
	{
	iAppViewArray.AppendL(aView);
	TRAPD(err,RegisterViewL(*aView));
	if (err)
		{
		iAppViewArray.Delete(TestAppUiViewIndex(*aView));
		User::Leave(err);
		}
	}


CTestView* CTVwaTestAppUi::ViewById(const TVwsViewId& aViewId) const
	{
	return iAppViewArray[TestAppUiViewIndex(aViewId)];
	}


TInt CTVwaTestAppUi::TestAppUiViewIndex(CTestView& aView) const
	{
	TInt pos;
	TKeyArrayFix key(0,ECmpTInt);
	if (iAppViewArray.Find(&aView,key,pos)==KErrNone)
		{
		return pos;
		}
	return KErrNotFound;
	}


void CTVwaTestAppUi::ActivateViewL(const TVwsViewId& aViewId,TUid aCustomMessageId,const TDesC16& aCustomMessage)
	{
	HBufC8* narrowMessage=HBufC8::NewLC(aCustomMessage.Size());
	TPtr8 ptr=narrowMessage->Des();
	ptr.Copy((TUint8*)aCustomMessage.Ptr(),aCustomMessage.Size());
	CCoeAppUi::ActivateViewL(aViewId,aCustomMessageId,narrowMessage->Des());
	CleanupStack::PopAndDestroy(narrowMessage);
	}


CTVwaTestAppUi::~CTVwaTestAppUi()
	{
	delete iDriver;
	const TInt numViews=iAppViewArray.Count();
	for (TInt ii=numViews-1;ii>=0;--ii)
		{
		CTestView* thisView=iAppViewArray[ii];
		DeregisterView(*thisView);
		iAppViewArray.Delete(ii);
		delete thisView;
		}
	RemoveFromStack(iControl);
	delete iControl;
	}
	
	
TInt CTVwaTestAppUi::TestAppUiViewIndex(const TVwsViewId& aViewId) const
	{
	const TInt numAppViews=iAppViewArray.Count();
	for (TInt ii=0;ii<numAppViews;ii++)
		{
		if (iAppViewArray[ii]->ViewId()==aViewId)
			return ii;
		}
	return KErrNotFound;
	}


void CTVwaTestAppUi::RemoveView(CTestView& aView)
	{
	const TInt viewIndex=TestAppUiViewIndex(aView);
	TEST_ASSERT(viewIndex!=KErrNotFound, ETestFailure);
	DeregisterView(aView);
	delete iAppViewArray[viewIndex];
	iAppViewArray.Delete(viewIndex);
	}


CTestView* CTVwaTestAppUi::ActiveView() const
	{
	TVwsViewId activeViewId=KNullViewId;
	if (GetActiveViewId(activeViewId)==KErrNone)
		{
		return iAppViewArray[TestAppUiViewIndex(activeViewId)];
		}
	return NULL;
	}


/*************************************************************
 **  
 **  CTVwaStep
 **  
 *************************************************************/

void CTVwaStep::ConstructAppL(CCoeEnv* aCoe)
	{ // runs inside a TRAP harness
	aCoe->ConstructL();
	CTVwaTestAppUi* appUi=new(ELeave) CTVwaTestAppUi();
	aCoe->SetAppUi(appUi);
	appUi->ConstructL(this);
	}

CTVwaStep::~CTVwaStep()
	{
	}

CTVwaStep::CTVwaStep()
	{
	SetTestStepName(KTVwaStep);
	}

TVerdict CTVwaStep::doTestStepL()
	{
	INFO_PRINTF1(_L("Test Started"));
	PreallocateHALBuffer();

	// initialise notification checkers
	gViewActivationObserverOne = 0;
	gViewDeactivationObserverOne = 0;
	gViewActivationObserverTwo = 0;
	gViewDeactivationObserverTwo = 0;
	gViewActivationObserverNotify = 0;
	gViewDeactivationObserverNotify = 0;
	// initialise control checkers
	gTopControl = 0;
	gBottomControl = 0;
	gAppUiControl = 0;

	__UHEAP_MARK;

	CCoeEnv* coe=new CCoeEnv;
	TRAPD(err,ConstructAppL(coe));
	TEST(err==KErrNone);
	if (!err)
		coe->ExecuteD();
	
	__UHEAP_MARKEND;
	
	INFO_PRINTF1(_L("Test Finished"));
	return TestStepResult();
	}



