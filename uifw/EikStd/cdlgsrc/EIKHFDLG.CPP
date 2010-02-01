/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:
*
*/


#ifdef _DEBUG
// subvert private protection on CCoeEnv for border drawer
// use a name unlikely to be repeated in any included header
#define SetAppStartupInstrumentationEventIdBaseL SetAppStartupInstrumentationEventIdBaseL(TInt aAppStartupInstrumentationEventIdBase); friend class CCoeRedrawer; void FuncWhichDoesntReallyExist
#include <coemain.h>
#undef iExtra
#endif

#include <eikenv.h>
#include <eikdebug.h>
#include <eikon.hrh>
#include <eikhfdlg.h>
#include <eikappui.h>
#include <eikcdlg.rsg>
#include <aknsettingitemlist.h>
#include <AknDlgShut.h>
#include <AknDialog.h>
#include <aknnotewrappers.h>
#include <aknnotedialog.h>

NONSHARABLE_CLASS(CSchedulerShaker) : public CTimer
	{
public:
	CSchedulerShaker();
	~CSchedulerShaker();
	void ConstructL();
	void Go();
private:
	void RunL();
	void DoCancel();
private:
	TBool iStarted;
	};

CSchedulerShaker::CSchedulerShaker() : CTimer(CActive::EPriorityStandard)
	{
	CActiveScheduler::Add(this);
	}

CSchedulerShaker::~CSchedulerShaker()
	{
	Cancel();
	}

void CSchedulerShaker::ConstructL()
	{
	CTimer::ConstructL();
	}

void CSchedulerShaker::Go()
	{
	After(20000);
	}

void CSchedulerShaker::RunL()
	{
	Go();
	iStarted = !iStarted;
	if (iStarted)
		CActiveScheduler::Start();
	else
		CActiveScheduler::Stop();
	}

void CSchedulerShaker::DoCancel()
	{
	CTimer::DoCancel();
	if (iStarted)
		CActiveScheduler::Stop();
	iStarted = EFalse;
	}


NONSHARABLE_CLASS(CEikHeapFailSettingList) : public CAknSettingItemList
	{
public:
	CEikHeapFailSettingList(TEikHeapFailModel& aModel);
	CAknSettingItem* CreateSettingItemL( TInt identifier );

private:
	TEikHeapFailModel& iModel;
	};

CEikHeapFailSettingList::CEikHeapFailSettingList(TEikHeapFailModel& aModel)
: iModel(aModel)
	{}

CAknSettingItem* CEikHeapFailSettingList::CreateSettingItemL( TInt identifier )
	{
	CAknSettingItem* settingItem=0;

	switch (identifier)
		{
		case 1:
			settingItem = new (ELeave) CAknEnumeratedTextPopupSettingItem(identifier, iModel.iHeapFailType);
			break;
		case 2:
			settingItem = new (ELeave) CAknIntegerEdwinSettingItem(identifier, iModel.iHeapFailRate);
			break;
		case 3:
			settingItem = new (ELeave) CAknEnumeratedTextPopupSettingItem(identifier, iModel.iWservFailType);
			break;
		case 4:
			settingItem = new (ELeave) CAknIntegerEdwinSettingItem(identifier, iModel.iWservFailRate);
			break;
		case 5:
			settingItem = new (ELeave) CAknEnumeratedTextPopupSettingItem(identifier, iModel.iFileFailType);
			break;
		case 6:
			settingItem = new (ELeave) CAknIntegerEdwinSettingItem(identifier, iModel.iFileFailRate);
			break;
		}

	return settingItem;
	}

NONSHARABLE_CLASS(CEikHeapFailDialog) : public CEikDialog
	{
public:
	CEikHeapFailDialog(TEikHeapFailModel& aModel);
	SEikControlInfo CreateCustomControlL(TInt aControlType);
	TBool OkToExitL(TInt aButtonId);
private:
	TEikHeapFailModel& iModel;
	};

CEikHeapFailDialog::CEikHeapFailDialog(TEikHeapFailModel& aModel)
: iModel(aModel)
	{}

SEikControlInfo CEikHeapFailDialog::CreateCustomControlL(TInt aControlType)
	{
	SEikControlInfo controlInfo;
	controlInfo.iControl = NULL;
	controlInfo.iTrailerTextId = 0;
	controlInfo.iFlags = 0;
    
	switch (aControlType)
        {
	case 10000:
	    controlInfo.iControl = new (ELeave) CEikHeapFailSettingList(iModel);
	    break;
	default:
		break;
		}

	return controlInfo;
	}

TBool CEikHeapFailDialog::OkToExitL(TInt /*aButtonId*/)
	{
	STATIC_CAST(CAknSettingItemList*, Control(EEikHeapFailSettingListId))->StoreSettingsL();

	TBuf<84> msg;
	RWsSession& wsSession=iEikonEnv->WsSession();
	switch (iModel.iHeapFailType)
		{
		case EEikCidHeapFailOff:
			{
			_LIT(KMsg,"Heap failure off ");
			msg.Append(KMsg);
			__UHEAP_SETFAIL(RHeap::ENone,iModel.iHeapFailRate);
			break;
			} 
		case EEikCidHeapFailTypeBackRandom:
			{
			_LIT(KMsg,"Setting random heap failure ");
			msg.Append(KMsg);
			__UHEAP_SETFAIL(RHeap::ERandom,iModel.iHeapFailRate);
			break;
			} 
		case EEikCidHeapFailTypeBackDeterministic:
			{
			_LIT(KMsg,"Setting deterministic heap failure ");
			msg.Append(KMsg);
			__UHEAP_SETFAIL(RHeap::EDeterministic,iModel.iHeapFailRate);
			break;
			}
		default: 
			return EFalse;
		}
	switch (iModel.iWservFailType)
		{
		case EEikCidWservHeapFailOff:
			{
			wsSession.HeapSetFail(RHeap::ENone,iModel.iWservFailRate);
			break;
			} 
		case EEikCidWservHeapFailTypeBackRandom:
			{
			wsSession.HeapSetFail(RHeap::ERandom,iModel.iWservFailRate);
			break;
			} 
		case EEikCidWservHeapFailTypeBackDeterministic:
			{
			wsSession.HeapSetFail(RHeap::EDeterministic,iModel.iWservFailRate);
			break;
			}
		default: 
			return EFalse;
		}
	if (iModel.iFileFailType)
		{
		_LIT(KMsg,"and file failure on");
		msg.Append(KMsg);
#if defined(_DEBUG)
		TInt KFileFailError=-9999;
		iCoeEnv->FsSession().SetErrorCondition(KFileFailError,iModel.iFileFailRate);
#endif
		}
	else
		{
		_LIT(KMsg,"and file failure off");
		msg.Append(KMsg);
#if defined(_DEBUG)
		TInt KFsNoErrRate=1000000;
		iCoeEnv->FsSession().SetErrorCondition(KErrNone,KFsNoErrRate);
#endif
		}
	iEikonEnv->InfoMsg(msg);
	return ETrue;
	}


//
//	class CEikDebugWin
//

void CEikDebugWin::Draw(const TRect& aRect) const
	{
	CGraphicsContext& gc=SystemGc();
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.SetPenStyle(CGraphicsContext::ENullPen);
	SystemGc().DrawRect(aRect);
	}
	
EXPORT_C void CEikDebugWin::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CCoeControl::HandlePointerEventL(aPointerEvent); 
    }	
	
void CEikDebugWin::ConstructL()
    {
    CreateWindowL();
    SetExtentToWholeScreen();
    Window().SetBackgroundColor(KRgbGray);
    ActivateL();
    DrawNow();
    iCoeEnv->Flush(300000);
    }


#ifdef _DEBUG
//
// classs CCoeRedrawer and CCoeEnvExtra
// subversively replaces cones redrawer active object to add borders to everything
// DEBUG ONLY
//
class CCoeRedrawer;

// maintain against src\common\generic\app-framework\cone\inc\coeenvextra.h
NONSHARABLE_CLASS(CCoeEnvExtra) : public CBase
	{
public:
	CCoeRedrawer* iRedrawer;
	};

NONSHARABLE_CLASS(CCoeRedrawer) : public CActive
	{
public:
	CCoeRedrawer(CCoeEnv* aCoeEnv);
	~CCoeRedrawer();
private:
	void Queue();
	// from CActive
	virtual void RunL();
	virtual void DoCancel();
	void DrawBorders(CCoeControl* aControl, TRgb& aCol);
private:
	RWsSession& iWsSession;
	CCoeEnv* iCoeEnv;
	CCoeRedrawer* iRedrawer;
	};

CCoeRedrawer::CCoeRedrawer(CCoeEnv* aCoeEnv)
	:CActive(EActivePriorityRedrawEvents), iWsSession(aCoeEnv->WsSession()), iCoeEnv(aCoeEnv)
	{
	CActiveScheduler::Add(this);

	iRedrawer = iCoeEnv->iExtra->iRedrawer;
	iRedrawer->Cancel();

	Queue();
	}

CCoeRedrawer::~CCoeRedrawer()
	{
	Cancel();
	iRedrawer->Queue();
	}

void CCoeRedrawer::Queue()
	{
	iWsSession.RedrawReady(&iStatus);
	SetActive();
	}

void CCoeRedrawer::RunL()
	{
	TWsRedrawEvent redraw;
	iWsSession.GetRedraw(redraw);
	CCoeControl* window=(CCoeControl*)redraw.Handle();
	if (window)
		{
		window->HandleRedrawEvent(redraw.Rect());

		TRgb col(KRgbGray);
		DrawBorders(window, col);
		}

	Queue(); // do this at the end to flush the window-server client-side buffer *after* HandleRedrawEvent has done any drawing
	}

void CCoeRedrawer::DoCancel()
	{
	iWsSession.RedrawReadyCancel();
	}

void CCoeRedrawer::DrawBorders(CCoeControl* aControl, TRgb& aCol)
	{
	RDrawableWindow* window = aControl->DrawableWindow();
	if (window)
		{
		TRect rect = aControl->Rect();
		CWindowGc& gc = iCoeEnv->SystemGc();
		gc.Activate(*window);
		gc.SetBrushStyle(CGraphicsContext::ENullBrush);
		gc.SetPenStyle(CGraphicsContext::ESolidPen);
		aCol.SetRed((aCol.Red() + 17) % 256);
		aCol.SetGreen((aCol.Green() + 199) % 256);
		aCol.SetBlue((aCol.Blue() + 111) % 256);
		gc.SetPenColor(aCol);
		gc.DrawRect(rect);
		gc.Deactivate();
		}

	TInt count = aControl->CountComponentControls();
	for (TInt ii=0; ii<count; ii++)
		{
		DrawBorders(aControl->ComponentControl(ii), aCol);
		}
	}

#endif


// 
// CAknMovableDialog 
//
//

NONSHARABLE_CLASS(CAknMovableDialog) : public CAknDialog
	{
public:
	CAknMovableDialog();
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
private:
	void AttemptMoveBy( TPoint aMoveBy );
	

	};

/**
 * Constructor 
 */
CAknMovableDialog::CAknMovableDialog() 
	{
	}

/**
 * Traps the arrow keys and moves the dialog
 */
TKeyResponse CAknMovableDialog::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {

	const TInt KMoveByHorizontal =  6;
	const TInt KMoveByVertical = 8;

	if ( aType == EEventKey )
		{
		TPoint aMoveBy(0,0);
		switch (aKeyEvent.iCode)
			{
			case EKeyUpArrow:
				aMoveBy.SetXY( 0, -KMoveByVertical );
				break;
			case EKeyDownArrow:
				aMoveBy.SetXY( 0, KMoveByVertical );
				break;
			case EKeyLeftArrow:
				aMoveBy.SetXY( -KMoveByHorizontal, 0 );
				break;
			case EKeyRightArrow:
				aMoveBy.SetXY( KMoveByHorizontal, 0 );
				break;
			default:
				// No action
				break;
			}

			if (aMoveBy.iX != 0  || aMoveBy.iY != 0 ) // Key is not consumed any other key
				{
				AttemptMoveBy( aMoveBy );
				return EKeyWasConsumed;
				}
		}
	
	return CAknDialog::OfferKeyEventL( aKeyEvent, aType );
    }

/**
*  This method is called "Attempt" because it will not move the dialog too far away 
* from the screen - to avoid it getting lost.  It does not leave.
*
*/
void CAknMovableDialog::AttemptMoveBy( TPoint aMoveBy )
	{
	// The dialog is a window-owning control, so we have to be aware of the coordinate system used at all times.
	TPoint pos = Position(); // Relative to screen
	TRect rect = Rect();
	pos += aMoveBy;		// New top left corner
	rect.Move( pos );
	// This test prevents the dialog from escaping off into the distance
	TRect screenRect = iCoeEnv->ScreenDevice()->SizeInPixels();
	if ( rect.Intersects(  screenRect ) )
		{
		SetRect( rect );
		}
	}




//
// class CEikDebugKeys
//

void CEikDebugKeys::ConstructL()
    {
    CCoeAppUi* appUi=iEikonEnv->EikAppUi();
    appUi->AddToStackL(this,ECoeStackPriorityEnvironmentFilter,ECoeStackFlagRefusesFocus|ECoeStackFlagSharable);
	iModel.iHeapFailRate=500;
	iModel.iHeapFailType=EEikCidHeapFailOff;
	iModel.iWservFailRate=500;
	iModel.iWservFailType=EEikCidWservHeapFailOff;
	iModel.iFileFailRate=5;
	iModel.iFileFailType=EFalse;
	iSchedulerShaker = new(ELeave) CSchedulerShaker;
	iSchedulerShaker->ConstructL();
    }

void CEikDebugKeys::Release()
	{
	CCoeAppUi* appUi=iEikonEnv->EikAppUi();
	if (appUi)
        appUi->RemoveFromStack(this);
#ifdef _DEBUG
	delete iPhantomBorderDrawer;
#endif
	delete iSchedulerShaker;
	delete this;
    }

TKeyResponse CEikDebugKeys::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    if (aType!=EEventKey || ((aKeyEvent.iModifiers&EAllStdModifiers)!=EAllStdModifiers))
        return(EKeyWasNotConsumed);
	TInt code=aKeyEvent.iCode;
    if (code<CTRL('a') || code>CTRL('z'))
        return(EKeyWasNotConsumed);
    switch (code)
        {
    case CTRL('a'):
        iEikonEnv->AllocInfoMsg();
        break;
	case CTRL('b'):
        iEikonEnv->FservAllocInfoMsg();
		break;
	case CTRL('c'):
        iEikonEnv->WservAllocInfoMsg();
		break;
	case CTRL('f'):
		{
		_LIT(KMsg,"Enabling Wserv auto-flush");
		InfoNote(KMsg);
		iEikonEnv->WsSession().SetAutoFlush(ETrue);
		break;
		}
	case CTRL('g'):
		{
		iEikonEnv->WsSession().SetAutoFlush(EFalse);
		_LIT(KMsg,"Wserv auto-flush disabled");
		InfoNote(KMsg);
		break;
		}
	case CTRL('j'):
		{
#ifdef _DEBUG
		if (iPhantomBorderDrawer)
			{
			delete iPhantomBorderDrawer;
			iPhantomBorderDrawer = 0;
			}
		else
			{
			iPhantomBorderDrawer = new(ELeave)CCoeRedrawer(iCoeEnv);
			}
		CEikDebugWin* win=new(ELeave) CEikDebugWin;
		CleanupStack::PushL(win);
		win->ConstructL();
		CleanupStack::PopAndDestroy();
#endif
		break;
		}
	case CTRL('l'):
		{
		AknDialogShutter::ShutDialogsL(*iEikonEnv);
		break;
		}
	case CTRL('m'):
		{
		// Put up Avkon "Move Me" dialog
		CEikDialog* dialog=new(ELeave) CAknMovableDialog;
		dialog->ExecuteLD(R_EIK_DIALOG_MOVEME);
		break;
		}
	case CTRL('n'):
		{
		if (iSchedulerShaker->IsActive())
			{
			_LIT(KMsg,"Scheduler shaker stopped");
			InfoNote(KMsg);
			iSchedulerShaker->Cancel();
			}
		else
			{
			_LIT(KMsg,"Scheduler shaker started");
			InfoNote(KMsg);
			iSchedulerShaker->Go();
			}
		break;
		}
	case CTRL('p'):
		__UHEAP_RESET;
		(new(ELeave) CEikHeapFailDialog(iModel))->ExecuteLD(R_EIK_HEAP_FAIL_DIALOG);
		break;
	case CTRL('q'):
		{
		__UHEAP_RESET;
		_LIT(KMsg,"Heap failure mode reset");
		InfoNote(KMsg);
		break;
		}
	case CTRL('r'):
		{
		CEikDebugWin* win=new(ELeave) CEikDebugWin;
		CleanupStack::PushL(win);
		win->ConstructL();
		CleanupStack::PopAndDestroy();
		break;
		}
	case CTRL('t'):
		iEikonEnv->DisplayTaskList();
		break;
	case CTRL('v'):
		if (iVerbose)
			{
			iVerbose=EFalse;
			_LIT(KMsg,"Verbose info messages disabled");
			InfoNote(KMsg);
			}
		else
			{
			iVerbose=ETrue;
			_LIT(KMsg,"Verbose info messages enabled");
			InfoNote(KMsg);
			}
		iEikonEnv->SetVerboseInfoReporting(iVerbose);
		break;
	case CTRL('y'):
		{
		_LIT(KMsg,"Mounting system as X:");
		InfoNote(KMsg);
		RFs& fs=iEikonEnv->FsSession();
		User::LeaveIfError(fs.AddFileSystem(_L("EFAT")));
		fs.MountFileSystem(_L("Fat"),EDriveX);
		RFormat format;
		TInt count;
		User::LeaveIfError(format.Open(fs,_L("X:"),EHighDensity,count));
		while (count)
			format.Next(count);
		format.Close();
		}
		break;
	case CTRL('z'):
		{
		RWsSession& wS=iEikonEnv->WsSession();
		TInt wgId=wS.GetFocusWindowGroup();
		TWsEvent wsEvent;
        TKeyEvent event={0,0,0,0};
		_LIT(KMsg,"Sending ASCII chars A-J as repeated keypresses to app");
		InfoNote(KMsg);
		for (TInt i=65; i<75; i++)
			{
			event.iCode=i;
			*(wsEvent.Key())=event;
			wsEvent.SetType(EEventKey);
			wsEvent.SetTimeNow();
			wS.SendEventToWindowGroup(wgId, wsEvent);
			}
		}
		break;
      	}
    return(EKeyWasConsumed);
    }

void CEikDebugKeys::InfoNote(const TDesC& aDes)
	{
	TRAP_IGNORE(
	  CAknInformationNote* note = new (ELeave) CAknInformationNote;
	  note->ExecuteLD(aDes);
	 );
	}
	
EXPORT_C void CEikDebugKeys::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CCoeControl::HandlePointerEventL(aPointerEvent); 
    }	
