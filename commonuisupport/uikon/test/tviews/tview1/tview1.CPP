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
// TVIEW1
// Tests integration of view architecture throughout the ViewSrv, Cone, Apparc, Uikon and RefUI layers.
// Tests basic view switching and appUi embedding. Tests various exceptional view switch conditions
// including OOM during activation, attempts to start missing apps, tests panics while idle, while
// activating and while deactivating and very slow activations and deactivations.
// Includes test of a waiting activation - an abuse of the architecture
// Should be used with companion test app TVIEW2 which provides the target view for each test view switch.
// Regression test for EDNMMAT-4L3QZH 'Bad things happen if an application that has called NotifyNextActivation() dies'
// - TVIEW1 registers a view activation observer which keeps an outstanding request for view activation notification.
// Regression test for DOE-4SSJUR 'ViewSrv can miss notification of change of focused window group' - TVIEW1 creates an
// event to activate a view in TVIEW2, waits for 0.5s to allow this activation to be half processed, then brings itself
// back into foreground. The foreground task cross-check should then fail and a new activation event should be created for
// TVIEW1. 
// TVIEW1 can be used for stress testing the view arc by setting up queues of events while doing
// the longer tests and killing random apps etc.
// An endurance auto test runs a series of random activations of any of the views in TVIEW1,TVIEW2 and TVIEW3 timed at short
// varying intervals and continuing forever - TVIEW2 and TVIEW3 also generate similar activation requests
// The endurance test can also be run with TVIEW1 set to sporadically kill TVIEW2 and TVIEW3, and for TVIEW1 and TVIEW2 to
// occasionally exit, to test interactions between view activations and app starts and stops
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code
*/
#include <e32math.h>
#include <barsread.h>
#include <gulalign.h>
#include <txtrich.h>
#include <apgtask.h>
#include <apgcli.h>
#include <viewcli.h>

#include <techview/eiktxlbx.h>
#include <techview/eiktxlbm.h>
#include <techview/eiklabel.h>
#include <techview/eikcmbut.h>
#include <techview/eikbtpan.h>
#include <techview/eikmenub.h>
#include <techview/eikdialg.h>
#include <eikdll.h>
#include <eiksvdef.h>
#include <techview/eikrted.h>
#include <techview/eikwbtb.h>
#include <eikenv.h>
#include <eikstart.h>
#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <viewclipartner.h>
#endif //SYMBIAN_ENABLE_SPLIT_HEADERS

#include <techview/eikon.hrh>
#include <techview/eikon.rsg>

#include "tview1.rsg"

#include "tview1.H"
#include "tview1.HRH"
#include "tvwuids.H"

#define VIEW_ONE TVwsViewId(KUidViewAppOne,KUidViewOne)
#define VIEW_TWO TVwsViewId(KUidViewAppOne,KUidViewTwo)
#define APP_TEXT _L("TVIEW1")

//
// EXPORTed functions
//

	LOCAL_C CApaApplication* NewApplication()
		{
		return new CTestApplication;
		}

	GLDEF_C TInt E32Main()
		{
		return EikStart::RunApplication(NewApplication);
		}



//
// CTestApplication
//

TUid CTestApplication::AppDllUid() const
	{
	return KUidViewAppOne;
	}

CApaDocument* CTestApplication::CreateDocumentL()
	{
	return new (ELeave) CTestDocument(*this);
	}


//
// CTestDocument
//

CTestDocument::CTestDocument(CEikApplication& aApp)
		: CEikDocument(aApp)
	{
	}

CEikAppUi* CTestDocument::CreateAppUiL()
	{
	return new(ELeave) CTestAppUi;
	}


//
// CTestSwitchDialog.
//

CTestSwitchDialog::~CTestSwitchDialog()
	{
	}

CTestSwitchDialog::CTestSwitchDialog(CTestAppUi& aAppUi) : iAppUi(aAppUi)
	{
	}

TBool CTestSwitchDialog::OkToExitL(TInt aButtonId)
	{
	if (aButtonId!=EEikBidOk)
		return EFalse;

	switch (ChoiceListCurrentItem(ESwitchDlg_ViewChoice))
		{
		case 0:
			iAppUi.iViewToActivate.iViewUid=KUidViewOne;
			break;
		case 1:
			iAppUi.iViewToActivate.iViewUid=KUidViewTwo;
			break;
		default:
			break;
		}

	if (ChoiceListCurrentItem(ESwitchDlg_AppChoice)==0)
		{
		iAppUi.iViewToActivate.iAppUid=KUidViewAppOne;
		}
	else if (ChoiceListCurrentItem(ESwitchDlg_AppChoice)==1)
		{
		iAppUi.iViewToActivate.iAppUid=KUidViewAppTwo;
		}

	delete iAppUi.iCustomMsg;
	iAppUi.iCustomMsg=HBufC::NewL(STATIC_CAST(CEikEdwin*,Control(ESwitchDlg_CustomMsg))->TextLength());
	TPtr des=iAppUi.iCustomMsg->Des();
	GetEdwinText(des,ESwitchDlg_CustomMsg);
	return ETrue;
	}

//
// CTestRichTextDialog
//

class CTestRichTextDialog : public CEikDialog
	{
public:
	CTestRichTextDialog(CRichText*& aRichText,CParaFormatLayer*& aRichParaFormatLayer,CCharFormatLayer*& aRichCharFormatLayer);
private: // framework
	void PreLayoutDynInitL();
    TBool OkToExitL(TInt aKeycode);
private:
	CRichText*& iRichText;
	CParaFormatLayer*& iRichParaFormatLayer;
	CCharFormatLayer*& iRichCharFormatLayer;
	};


CTestRichTextDialog::CTestRichTextDialog(CRichText*& aRichText,CParaFormatLayer*& aRichParaFormatLayer,
						 CCharFormatLayer*& aRichCharFormatLayer)
	: iRichText(aRichText),iRichParaFormatLayer(aRichParaFormatLayer),iRichCharFormatLayer(aRichCharFormatLayer)
	{}
	

void CTestRichTextDialog::PreLayoutDynInitL()
	{
	CEikRichTextEditor* ed=(CEikRichTextEditor*)Control(ERtextedDlg_Editor);
	ed->SetDocumentContentL(*iRichText);
	}

TBool CTestRichTextDialog::OkToExitL(TInt /*aKeycode*/)
    {
	delete iRichText;
	delete iRichParaFormatLayer;
	delete iRichCharFormatLayer;
	CEikRichTextEditor* edwin=STATIC_CAST(CEikRichTextEditor*,Control(ERtextedDlg_Editor));
	edwin->SetDocumentOwnership(CEikEdwin::EDoesNotOwnText);
	iRichText=edwin->RichText();
	iRichText->SetPictureFactory(iRichText->PictureFactory(),NULL);
	iRichParaFormatLayer=((CParaFormatLayer*)iRichText->GlobalParaFormatLayer());
	iRichCharFormatLayer=((CCharFormatLayer*)iRichText->GlobalCharFormatLayer());
    return(ETrue);
    }


//
// CTestAppUi
//

CTestAppUi::~CTestAppUi()
	{
	delete iCustomMsg;
	delete iRichText;
	delete iRichParaFormatLayer;
	delete iRichCharFormatLayer;
	delete iViewActivationObserver;
	delete iAutoTestTimer;
	}

const TInt KRandSeed=12345;

CTestAppUi::CTestAppUi()
	: iRandSeed(KRandSeed),
	  iDoKills(EFalse),
	  iIsServerEventTimeOutEnabled(ETrue)
	{
	TTime time;
	time.HomeTime();
	iRandSeed=time.Int64();
	}

void CTestAppUi::ConstructL()
	{
	CTestVwAppUi::ConstructL();
	iRichParaFormatLayer=CEikonEnv::NewDefaultParaFormatLayerL();
    iRichCharFormatLayer=CEikonEnv::NewDefaultCharFormatLayerL();
	iRichText=CRichText::NewL(iRichParaFormatLayer,iRichCharFormatLayer);
	CreateViewsL();
	iViewActivationObserver=new(ELeave) CTestViewActivationObserver(*this);
	iViewActivationObserver->ConstructL();
	iAutoTestTimer=CPeriodic::NewL(0);
	}

void CTestAppUi::DynInitMenuPaneL(TInt aMenuId,CEikMenuPane* aMenuPane)
	{
	if (aMenuId==R_VW_BASIC_MENU && iIsServerEventTimeOutEnabled)
		{
		aMenuPane->SetItemButtonState(EToggleTimeOutEnabled, EEikMenuItemSymbolOn);
		}
	}

void CTestAppUi::CreateViewsL()
	{
	if (iViewsCreated)
		{
		RDebug::Print(_L("Views already created"));
		return;
		}

	AddViewL(VIEW_ONE);
	AddViewL(VIEW_TWO);
	STATIC_CAST(CTestView*,View(VIEW_TWO))->InitializeAsDefaultL();
	RDebug::Print(_L("All views created"));
	iViewsCreated=ETrue;
	}

void CTestAppUi::AddViewL(const TVwsViewId& aViewId)
	{
	RDebug::Print(_L("Creating %x..."),aViewId.iViewUid.iUid);
	CTestView* view=new(ELeave) CTestView(aViewId,*this);
	CleanupStack::PushL(view);
	view->ConstructL();
	CTestVwAppUi::AddViewL(view);
	CleanupStack::Pop();
	}

void CTestAppUi::DisplaySwitchViewDialogL()
	{
	CEikDialog* dlg=new(ELeave) CTestSwitchDialog(*this);
	if (dlg->ExecuteLD(R_VW_VIEW_SWITCH_DIALOG))
		{
		DoActivationL();
		}
	}

void CTestAppUi::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
	case ESwitchView:
		DisplaySwitchViewDialogL();
		break;
	case EDisplayRichText:
		DisplayRichTextDialogL();
		break;
	case EEikCmdExit:
		Exit();
		break;
	case EDisplayTaskList:
		CEikonEnv::Static()->DisplayTaskList();
		break;
	case EActivationOOM:
		TestActivationOOML();
		break;
	case ESuccesiveAllocFail:
		TestSuccesiveAllocFailL();
		break;
	case EWaitingActivation:
		TestWaitingActivationL();
		break;
	case EStartMissingApp:
		TestStartMissingAppL();
		break;
	case EPanicedActivation:
		TestPanicedActivationL();
		break;
	case EPanicedDeactivation:
		TestPanicedDeactivationL();
		break;
	case ESlowActivation:
		TestSlowActivationL();
		break;
	case ESlowDeactivation:
		TestSlowDeactivationL();
		break;
	case EEnduranceTest	:
		TestServerEnduranceL();
		break;
	case EEnduranceWithKillsTest	:
		TestServerEnduranceWithKillsL();
		break;
	case EExitAndDoubleActivaiton :
		TestExitAndDoubleActivationL();
		break;
	case EActivateInsideViewActivated :
		TestActivateInsideViewActivatedL();
		break;
	case EWaitOnAppStart :
		TestWaitOnAppStartL();
		break;
	case EForegroundChange :
		TestForegroundChangeWhileEventsOnQueueL();
		break;
	case ECheckForegroundChange :
		CheckForegroundChangeWhileEventsOnQueue();
		break;
	case EToggleTimeOutEnabled :
		TestToggleTimeOutEnabledL();
		break;
	default:
		if (ActiveView())
			ActiveView()->HandleCommandL(aCommand);
		else
			RDebug::Print(_L("No active view"));
		break;
		}
	}

void CTestAppUi::DisplayRichTextDialogL()
	{
	CEikDialog* dialog=new(ELeave) CTestRichTextDialog(iRichText,iRichParaFormatLayer,iRichCharFormatLayer);
	dialog->ExecuteLD(R_VW_RTEXTED_DIALOG);
	}

void CTestAppUi::DoActivationL()
	{
	if (iCustomMsg->Length())
		{
		ActivateViewL(iViewToActivate,KUidTestCustomMesssageId,*iCustomMsg);
		}
	else
		{
		CCoeAppUi::ActivateViewL(iViewToActivate);
		}
	}

void CTestAppUi::TestSuccesiveAllocFailL()
	{
	RDebug::Print(_L("TVIEW1 : Test Succesive Alloc Failure During Activation Until Success"));	
	TInt error=KErrUnknown;
	for(TInt fail=1;error!=KErrNone;fail++)
		{
		RDebug::Print(_L("TVIEW2 : Next Failure Test"));
		__UHEAP_FAILNEXT(fail);// fail on succesive allocations
		__UHEAP_MARK;
		TRAP(error,CCoeAppUi::ActivateViewL(TVwsViewId(KUidViewAppTwo,KUidViewOne)));
		__UHEAP_MARKEND; // Check nothing has alloc'd due to fail
		}
	__UHEAP_SETFAIL(RHeap::ENone,0);// turn failure off
	}

void CTestAppUi::TestActivationOOML()
	{
	RDebug::Print(_L("TVIEW1 : Test Activation OOM"));
	ActivateViewL(TVwsViewId(KUidViewAppTwo,KUidViewOne),KUidActivationOOM,KNullDesC16);
	}

void CTestAppUi::TestWaitingActivationL()
	{
	RDebug::Print(_L("TVIEW1 : Test Waiting Activation"));
	ActivateViewL(TVwsViewId(KUidViewAppTwo,KUidViewOne),KUidStartScheduler,KNullDesC16);
	}

void CTestAppUi::TestPanicedActivationL()
	{
	RDebug::Print(_L("TVIEW1 : Test Paniced Activation"));
	ActivateViewL(TVwsViewId(KUidViewAppTwo,KUidViewOne),KUidActivationPanic,KNullDesC16);
	}

void CTestAppUi::TestPanicedDeactivationL()
	{
	RDebug::Print(_L("TVIEW1 : Test Paniced Deactivation"));
	STATIC_CAST(CTestView*,View(VIEW_ONE))->iDeactivationPanic=ETrue;
	STATIC_CAST(CTestView*,View(VIEW_TWO))->iDeactivationPanic=ETrue;
	CCoeAppUi::ActivateViewL(TVwsViewId(KUidViewAppTwo,KUidViewOne));
	}

void CTestAppUi::TestSlowActivationL()
	{
	RDebug::Print(_L("TVIEW1 : Test Slow Activation"));
	ActivateViewL(TVwsViewId(KUidViewAppTwo,KUidViewOne),KUidSlowActivation,KNullDesC16);
	}

void CTestAppUi::TestSlowDeactivationL()
	{
	RDebug::Print(_L("TVIEW1 : Test Slow Deactivation"));
	STATIC_CAST(CTestView*,View(VIEW_ONE))->iSlowDeactivation=ETrue;
	STATIC_CAST(CTestView*,View(VIEW_TWO))->iSlowDeactivation=ETrue;
	CCoeAppUi::ActivateViewL(TVwsViewId(KUidViewAppTwo,KUidViewOne));
	}

void CTestAppUi::TestServerEnduranceL()
	{
	RDebug::Print(_L("TVIEW1 : Test Server Endurance"));
	iDoKills=EFalse;
	DoNextEnduranceTestActivation();
	ActivateViewL(TVwsViewId(KUidViewAppTwo,KUidViewOne),KUidEndurance,KNullDesC16);
	ActivateViewL(TVwsViewId(KUidViewAppThree,KUidViewOne),KUidEndurance,KNullDesC16);
	}

void CTestAppUi::TestServerEnduranceWithKillsL()
	{
	RDebug::Print(_L("TVIEW1 : Test Server Endurance With Client Kills"));
	iDoKills=ETrue;
	DoNextEnduranceTestActivation();
	ActivateViewL(TVwsViewId(KUidViewAppTwo,KUidViewOne),KUidEndurance,KNullDesC16);
	ActivateViewL(TVwsViewId(KUidViewAppThree,KUidViewOne),KUidEndurance,KNullDesC16);
	}

void CTestAppUi::TestExitAndDoubleActivationL()
	{
	RDebug::Print(_L("TVIEW1 : Test Exit And Double Activation"));
	CreateActivateViewEventL(TVwsViewId(KUidViewAppTwo,KUidViewOne),KNullUid,KNullDesC8);
	CreateActivateViewEventL(TVwsViewId(KUidViewAppTwo,KUidViewTwo),KUidActivationExit,KNullDesC8);
	CreateActivateViewEventL(TVwsViewId(KUidViewAppTwo,KUidViewTwo),KNullUid,KNullDesC8);
	}

void CTestAppUi::TestActivateInsideViewActivatedL()
	{
	RDebug::Print(_L("TVIEW1 : Test Activate Inside ViewActivated"));
	ActivateViewL(TVwsViewId(KUidViewAppTwo,KUidViewOne),KUidActivateAgain,KNullDesC16);
	}

void CTestAppUi::TestWaitOnAppStartL()
	{
	RDebug::Print(_L("TVIEW1 : Test Wait On App Start"));

	RThread appThread;
	TRequestStatus status;
	TThreadId threadId;

	RApaLsSession ls;
	CleanupClosePushL(ls);
	User::LeaveIfError(ls.Connect());
	TApaAppInfo info;
	User::LeaveIfError(ls.GetAppInfo(info,KUidViewAppTwo));
	CleanupStack::PopAndDestroy();	// ls 

	CApaCommandLine* cmdLine=CApaCommandLine::NewLC();	
	cmdLine->SetExecutableNameL(info.iFullName);
	cmdLine->SetCommandL(EApaCommandViewActivate);
	TFileName fName=_L("c:\\Documents\\");
	TParsePtrC parse(info.iFullName);
	fName.Append(parse.Name());
	cmdLine->SetDocumentNameL(fName);

	RApaLsSession lsSession;
  	User::LeaveIfError(lsSession.Connect());
  	CleanupClosePushL(lsSession);
  	threadId=User::LeaveIfError(lsSession.StartApp(*cmdLine, threadId));
  	CleanupStack::PopAndDestroy(&lsSession);
	CleanupStack::PopAndDestroy(); // cmdLine
	User::LeaveIfError(appThread.Open(threadId));
	appThread.Logon(status);
	User::WaitForRequest(status);
	}

void CTestAppUi::TestForegroundChangeWhileEventsOnQueueL()
	{
	RDebug::Print(_L("TVIEW1 : Test Foreground Change While Events On Queue"));
	// Activate a view in TView2 first to make sure that the app is available
	CCoeAppUi::ActivateViewL(TVwsViewId(KUidViewAppTwo,KUidViewOne));
	// Activate a view in TView1 to get into a known state so that we can do a check of the outcome of the real test
	CCoeAppUi::ActivateViewL(TVwsViewId(KUidViewAppOne,KUidViewOne));

	// Create an activation event for TView2 and stall long enough so that the event will be waiting for the deactivation
	// in this app. Then immediately bring this app into the foreground.
	CreateActivateViewEventL(TVwsViewId(KUidViewAppTwo,KUidViewOne),KNullUid,KNullDesC8);
	User::After(50000);	// 0.5 sec
	TApaTaskList taskList(CEikonEnv::Static()->WsSession());
	TApaTask task=taskList.FindApp(KUidViewAppOne);
	task.BringToForeground();
	}

void CTestAppUi::CheckForegroundChangeWhileEventsOnQueue()
	{
	TVwsViewId activeView;
	if (GetActiveViewId(activeView)!=KErrNotFound && activeView==TVwsViewId(KUidViewAppOne,KUidViewOne))
		{
		iEikonEnv->InfoMsg(_L("Test passed"));
		}
	else
		{
		iEikonEnv->InfoMsg(_L("Test failed"));
		}
	}

void CTestAppUi::TestToggleTimeOutEnabledL()
	{
	CVwsSessionWrapper* vwsSession=CVwsSessionWrapper::NewLC();
	User::LeaveIfError(vwsSession->EnableServerEventTimeOut(!iIsServerEventTimeOutEnabled));
	iIsServerEventTimeOutEnabled=(!iIsServerEventTimeOutEnabled);
	CleanupStack::PopAndDestroy();
	}

const TInt KMinimumDelay=50000;

void CTestAppUi::DoNextEnduranceTestActivation()
	{
	if (iAutoTestTimer->IsActive())
		iAutoTestTimer->Cancel();
	
	TInt rand=0;
	if (iDoKills)
		{
		// Occasionally we kill another TVIEW
		TUid killAppUid=KNullUid;
		rand=Math::Rand(iRandSeed);
		if (rand<=KMaxTInt/8)	// 1 in 8 chance
			{
			killAppUid=KUidViewAppTwo;
			}
		else if (rand/2<=KMaxTInt/8)
			{
			killAppUid=KUidViewAppThree;
			}
			
		if (killAppUid!=KNullUid)
			{
			TApaTaskList taskList(CEikonEnv::Static()->WsSession());
			TApaTask task=taskList.FindApp(killAppUid);
			if (task.Exists())
				{
				RDebug::Print(_L("TVIEW1 : ********************* KILLING %x ********************* "),killAppUid.iUid);
				task.KillTask();
				User::After(10000);	// 0.1 sec
				}

			// Start the timer again with a new time delay
			TTimeIntervalMicroSeconds32 delay(KMinimumDelay+KMinimumDelay*Math::Rand(iRandSeed)/KMaxTInt);
			iAutoTestTimer->Start(delay,delay,TCallBack(EnduranceTestCallBack,this));
			
			TRAPD(err,ActivateViewL(TVwsViewId(killAppUid,KUidViewOne),KUidEndurance,KNullDesC16));
			__ASSERT_ALWAYS(!err,User::Panic(_L("ActivateViewL(TVwsViewId(killAppUid,KUidViewOne),KUidEndurance,KNullDesC16)"),err));
			return;
			}
		}	
	// Otherwise we do another random activation

	// Find a new view to activate
	TUid viewUid = (Math::Rand(iRandSeed)>KMaxTInt/2) ? KUidViewOne : KUidViewTwo;
	TUid appUid = KNullUid;
	rand=Math::Rand(iRandSeed);
	if (rand<=KMaxTInt/3)	// 1 in 3 chance
		{
		appUid=KUidViewAppOne;
		}
	else if (rand/2<=KMaxTInt/3)	
		{
		appUid=KUidViewAppTwo;
		}
	else	
		{
		appUid=KUidViewAppThree;
		}

	// Decide whether any special condition should be used with activation.
	// This can mean the activation will be sluggish, a deactivation will be sluggish
	// or the activation will leave or exit
	TUid messageUid=KNullUid;
	rand=Math::Rand(iRandSeed);
	if (rand<KMaxTInt/10)	// 1 in 10 chance
		{
		messageUid=KUidActivationOOM;
		}
	else if (rand/2<KMaxTInt/10)
		{
		messageUid=KUidSluggishActivation;
		}
	else if (rand/3<KMaxTInt/10)
		{
		STATIC_CAST(CTestView*,View(VIEW_ONE))->iSluggishDeactivation=ETrue;
		}
	else if (rand/4<=KMaxTInt/10 && iDoKills)
		{
		STATIC_CAST(CTestView*,View(VIEW_ONE))->iExitDeactivation=ETrue;
		}
	else if (rand<=KMaxTInt && iDoKills && appUid==KUidViewAppTwo)
		{
		messageUid=KUidActivationExit;
		}

	// Start the timer again with a new time delay
	TTimeIntervalMicroSeconds32 delay(KMinimumDelay+KMinimumDelay*Math::Rand(iRandSeed)/KMaxTInt);
	iAutoTestTimer->Start(delay,delay,TCallBack(EnduranceTestCallBack,this));

	TRAPD(err,ActivateViewL(TVwsViewId(appUid,viewUid),messageUid,KNullDesC));
	__ASSERT_ALWAYS(!err,User::Panic(_L("ActivateViewL(TVwsViewId(appUid,viewUid),messageUid,KNullDesC)"),err));
	}

TInt CTestAppUi::EnduranceTestCallBack(TAny* aSelf)
	{ // static
	REINTERPRET_CAST(CTestAppUi*,aSelf)->DoNextEnduranceTestActivation();
	return 0;
	}

//
// This UID defined in Uikon. Not an app.
//
const TUid KUidPasswordMode={268435755};

void CTestAppUi::TestStartMissingAppL()
	{
	RDebug::Print(_L("TVIEW1 : Test Start Missing App"));
	CCoeAppUi::ActivateViewL(TVwsViewId(KUidPasswordMode,KUidViewOne));
	}


CTestViewControl::~CTestViewControl()
	{
	}

void CTestViewControl::ConstructL(const TVwsViewId& aViewId)
    {
	iViewId=aViewId;
    CreateWindowL();
    Window().SetShadowDisabled(ETrue);
	Window().SetBackgroundColor(KRgbRed);
    ActivateL();
    }

const TInt KXStart = 50;
const TInt KYStart = 50;

void CTestViewControl::Draw(const TRect& /*aRect*/) const
	{
	CWindowGc& gc = SystemGc();
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.SetBrushColor(KRgbDitheredLightGray);
	gc.DrawRect(Rect());

	gc.UseFont(iEikonEnv->TitleFont());

	TInt yPos = KYStart;
	TInt xPos = KXStart;

	gc.DrawText(APP_TEXT,TPoint(xPos,yPos));

	yPos+=30;

	TBuf<256> viewNameBuf;
	viewNameBuf.Append(_L("View "));
	TBuf<16> numBuf;
	numBuf.Num((TInt)iViewId.iViewUid.iUid);
	viewNameBuf.Append(numBuf);


	gc.DrawText(viewNameBuf,TPoint(xPos,yPos));

	}


//
// CTestView
//

CTestView::~CTestView()
	{
	delete iControl;
	}

CTestView::CTestView(const TVwsViewId& aViewId,CTestAppUi& aAppUi)
	:CTestVwAppView(aViewId,aAppUi), iDeactivationPanic(EFalse), iSlowDeactivation(EFalse), iSluggishDeactivation(EFalse),
	iExitDeactivation(EFalse)
	{
	}

void CTestView::ConstructL() 
	{
	iControl=new(ELeave) CTestViewControl;
    iControl->ConstructL(ViewId());
	iControl->SetRect(ClientRect());
	}

void CTestView::InitializeAsDefaultL()
	{
	AppUi().SetDefaultViewL(*this);

	if (!iControl)
		ConstructL();

	iControl->ActivateL();
	iControl->DrawNow();
	}

void CTestView::DoActivateL(const TVwsViewId& /*aPrevViewUid*/,TUid aCustomMessageId,const TDesC16& /*aCustomMessage*/)
	{
	iActivated=ETrue;
	if(aCustomMessageId==KUidActivationOOM)
		{
		User::Leave(KErrNoMemory);
		}
	else if(aCustomMessageId==KUidSluggishActivation)
		{
		User::After(1000000);	// 1.0 sec
		}
	iControl->DrawableWindow()->SetOrdinalPosition(0);
	}

void CTestView::DoDeactivate()
	{
	if (!iActivated)
		{
		RDebug::Print(_L("%x,%x deactivated when not active"),ViewId().iAppUid.iUid,ViewId().iViewUid.iUid);
		ASSERT(iActivated);
		}
	if (iDeactivationPanic)
		{
		RDebug::Print(_L("TVIEW1 : Deactivation Panic"));
		User::Panic(APP_TEXT,1);
		}
	else if (iSlowDeactivation)
		{
		RDebug::Print(_L("TVIEW1 : Slow Deactivation"));
		User::After(5000000);	// 5 sec
		iSlowDeactivation=EFalse;
		}
	else if (iSluggishDeactivation)
		{
		RDebug::Print(_L("TVIEW1 : Sluggish Deactivation"));
		User::After(500000);	// 0.5 sec
		iSluggishDeactivation=EFalse;
		}
	else if (iExitDeactivation)
		{
		RDebug::Print(_L("TVIEW1 : Exit During Deactivation"));
		TApaTaskList taskList(CEikonEnv::Static()->WsSession());
		TApaTask task=taskList.FindApp(KUidViewAppTwo);
		if (task.Exists())
			{
			RDebug::Print(_L("TVIEW1 : ********************* KILLING TVIEW2 ********************* "));
			task.KillTask();
			User::After(10000);	// 0.1 sec
			}
		iExitDeactivation=EFalse;
		}
	iActivated=EFalse;
	}

void CTestView::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
	case ETaskToAppAViewOne:
		ActivateViewL(TVwsViewId(KUidViewAppOne,KUidViewOne));
		break;
	case ETaskToAppAViewTwo:
		ActivateViewL(TVwsViewId(KUidViewAppOne,KUidViewTwo));
		break;
	case EDNLViewAppC:
		//ActivateViewL(TVwsViewId(KUidViewAppCApp,KUidViewAppCOne));
		break;
	default:
		break;
		}
	}

void CTestView::SetEmphasis(CCoeControl* /*aMenuControl*/,TBool /*aEmphasis*/)
	{
	}


//
// Class CTestViewDeactivationObserver
//

CTestViewActivationObserver::CTestViewActivationObserver(CCoeAppUi& aAppUi)
	: iAppUi(aAppUi), iActivationCount(0)
	{}

void CTestViewActivationObserver::ConstructL()
	{
	iAppUi.NotifyNextActivation(*this);
	}

const TInt KLargeInt=KMaxTInt/2;

void CTestViewActivationObserver::HandleViewActivation(const TVwsViewId& /*aNewlyActivatedViewId*/,const TVwsViewId& /*aViewIdToBeDeactivated*/)
	{
	// reset count if it gets big
	if (iActivationCount>KLargeInt)
		{
		iActivationCount=0;
		}
	iActivationCount++;
	iAppUi.NotifyNextActivation(*this);
	}

