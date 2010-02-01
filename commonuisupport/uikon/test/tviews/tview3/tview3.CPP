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
// TVIEW3
// Tests integration of view architecture throughout the ViewSrv, Cone, Apparc, Uikon and RefUI layers.
// Largely redundant given TVIEW1 and TVIEW2 but used by auto tests.
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
#include <eikstart.h>

#include <techview/eikwbtb.h> 

#include <techview/eikon.hrh>
#include <techview/eikon.rsg>

#include <tview3.rsg>

#include "tview3.H"
#include "tview3.HRH"
#include "tvwuids.H"

#define VIEW_ONE TVwsViewId(KUidViewAppThree,KUidViewOne)
#define VIEW_TWO TVwsViewId(KUidViewAppThree,KUidViewTwo)
#define APP_TEXT _L("TVIEW3")

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
	return KUidViewAppThree;
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
	delete iAutoTestTimer;
	}

const TInt KRandSeed=67890;

CTestAppUi::CTestAppUi()
	: iRandSeed(KRandSeed)
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
	iAutoTestTimer=CPeriodic::NewL(0);
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
	case EPanicApp:
		TestPanic();
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
	RDebug::Print(_L("TVIEW3 : Test Succesive Alloc Failure During Activation Until Success"));	
	TInt error=KErrUnknown;
	for(TInt fail=1;error!=KErrNone;fail++)
		{
		RDebug::Print(_L("TVIEW3 : Next Failure Test"));
		__UHEAP_FAILNEXT(fail);// fail on succesive allocations
		__UHEAP_MARK;
		TRAP(error,CCoeAppUi::ActivateViewL(TVwsViewId(KUidViewAppTwo,KUidViewOne)));
		__UHEAP_MARKEND; // Check nothing has alloc'd due to fail
		}
	__UHEAP_SETFAIL(RHeap::ENone,0);// turn failure off
	}

void CTestAppUi::TestActivationOOML()
	{
	RDebug::Print(_L("TVIEW3 : Test Activation OOM"));
	ActivateViewL(TVwsViewId(KUidViewAppTwo,KUidViewOne),KUidActivationOOM,KNullDesC16);
	}

void CTestAppUi::TestWaitingActivationL()
	{
	RDebug::Print(_L("TVIEW3 : Test Waiting Activation"));
	ActivateViewL(TVwsViewId(KUidViewAppTwo,KUidViewOne),KUidStartScheduler,KNullDesC16);
	}

void CTestAppUi::TestPanicedActivationL()
	{
	RDebug::Print(_L("TVIEW3 : Test Paniced Activation"));
	ActivateViewL(TVwsViewId(KUidViewAppTwo,KUidViewOne),KUidActivationPanic,KNullDesC16);
	}

void CTestAppUi::TestPanicedDeactivationL()
	{
	RDebug::Print(_L("TVIEW3 : Test Paniced Deactivation"));
	STATIC_CAST(CTestView*,View(VIEW_ONE))->iDeactivationPanic=ETrue;
	STATIC_CAST(CTestView*,View(VIEW_TWO))->iDeactivationPanic=ETrue;
	CCoeAppUi::ActivateViewL(TVwsViewId(KUidViewAppTwo,KUidViewOne));
	}

void CTestAppUi::TestSlowActivationL()
	{
	RDebug::Print(_L("TVIEW3 : Test Slow Activation"));
	ActivateViewL(TVwsViewId(KUidViewAppTwo,KUidViewOne),KUidSlowActivation,KNullDesC16);
	}

void CTestAppUi::TestSlowDeactivationL()
	{
	RDebug::Print(_L("TVIEW3 : Test Slow Deactivation"));
	STATIC_CAST(CTestView*,View(VIEW_ONE))->iSlowDeactivation=ETrue;
	STATIC_CAST(CTestView*,View(VIEW_TWO))->iSlowDeactivation=ETrue;
	CCoeAppUi::ActivateViewL(TVwsViewId(KUidViewAppTwo,KUidViewOne));
	}

const TInt KMinimumDelay=50000;

void CTestAppUi::StartEnduranceTest()
	{
	if (iAutoTestTimer->IsActive())
		iAutoTestTimer->Cancel();
	
	// Start the auto test timer
	TTimeIntervalMicroSeconds32 delay(KMinimumDelay+KMinimumDelay*Math::Rand(iRandSeed)/KMaxTInt);
	iAutoTestTimer->Start(delay,delay,TCallBack(EnduranceTestCallBack,this));
	}

void CTestAppUi::DoNextEnduranceTestActivation()
	{
	if (iAutoTestTimer->IsActive())
		iAutoTestTimer->Cancel();

	// Find a new view to activate
	TUid viewUid = (Math::Rand(iRandSeed)<KMaxTInt/2) ? KUidViewOne : KUidViewTwo;
	TUid appUid = KNullUid;
	TInt rand=Math::Rand(iRandSeed);
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
	// or the activation will leave
	TUid messageUid=KNullUid;
	rand=Math::Rand(iRandSeed);
	if (rand<=KMaxTInt/10)	// 1 in 10 chance
		{
		messageUid=KUidActivationOOM;
		}
	else if (rand/2<=KMaxTInt/10)
		{
		messageUid=KUidSluggishActivation;
		}
	else if (rand/3<=KMaxTInt/10)
		{
		STATIC_CAST(CTestView*,View(VIEW_ONE))->iSluggishDeactivation=ETrue;
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
	RDebug::Print(_L("TVIEW3 : Test Start Missing App"));
	CCoeAppUi::ActivateViewL(TVwsViewId(KUidPasswordMode,KUidViewOne));
	}

void CTestAppUi::TestPanic()
	{
	RDebug::Print(_L("TVIEW3 : Test Panic"));
	User::Panic(APP_TEXT,1);
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
	:CTestVwAppView(aViewId,aAppUi), iDeactivationPanic(EFalse), iSlowDeactivation(EFalse), iSluggishDeactivation(EFalse)
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

LOCAL_C void CleanupDoActivate(TAny* aPtr)
	{
	((CTestView*)aPtr)->UnrollDoActivate();
	}

void CTestView::UnrollDoActivate()
	{
	delete iControl;
	iControl=NULL;
	}

void CTestView::DoActivateL(const TVwsViewId& /*aPrevViewUid*/,TUid aCustomMessageId,const TDesC16& /*aCustomMessage*/)
	{
	CleanupStack::PushL(TCleanupItem(CleanupDoActivate,this));
	
	if (!iControl)
		ConstructL();

	if(aCustomMessageId==KUidStartScheduler)
		{
		STATIC_CAST(CTestAppUi&,AppUi()).DisplayRichTextDialogL();
		}
	else if(aCustomMessageId==KUidActivationOOM)
		{
		User::Leave(KErrNoMemory);
		}
	else if(aCustomMessageId==KUidActivationPanic)
		{
		User::Panic(APP_TEXT,1);
		}
	else if(aCustomMessageId==KUidSlowActivation)
		{
		User::After(5000000);
		}
	else if(aCustomMessageId==KUidEndurance)
		{
		STATIC_CAST(CTestAppUi&,AppUi()).StartEnduranceTest();
		}
	else if(aCustomMessageId==KUidSluggishActivation)
		{
		User::After(1000000);	// 1.0 sec
		}

	CleanupStack::Pop();	// TCleanupItem

	iControl->DrawableWindow()->SetOrdinalPosition(0);
	iActivated=ETrue;
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
		RDebug::Print(_L("TVIEW3 : Deactivation Panic"));
		User::Panic(APP_TEXT,1);
		}
	else if (iSlowDeactivation)
		{
		RDebug::Print(_L("TVIEW3 : Slow Deactivation"));
		User::After(5000000);	// 5 sec
		iSlowDeactivation=EFalse;
		}
	else if (iSluggishDeactivation)
		{
		RDebug::Print(_L("TVIEW3 : Sluggish Deactivation"));
		User::After(500000);	// 0.5 sec
		iSluggishDeactivation=EFalse;
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

void CTestView::Reset()
	{
	delete iControl;
	iControl=NULL;
	}


