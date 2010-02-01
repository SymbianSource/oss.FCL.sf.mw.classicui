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
// The shutapp application is intended only for use with the test tshutter.
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code 
*/

#include <coecntrl.h>
#include <eikappui.h>
#include <e32base.h>

#include <basched.h>
#include <eikenv.h>
#include <eikapp.h>
#include <eikdoc.h>
#include <eikstart.h>

#include "shutapp.h"

class CSignalAppRunning : public CTimer
	{
public:
	static CSignalAppRunning* NewL();
	~CSignalAppRunning();
private:
	CSignalAppRunning();
	void ConstructL();
private: // from CActive
	void RunL();
	void DoCancel();
	};

class CEscapeKeyPresser : public CActive
	{
public:
	~CEscapeKeyPresser();
	CEscapeKeyPresser(CEikonEnv& aEikEnv);
	void RequestDeferredEscapeKeyPress();
private: // from CActive
	void RunL();
	void DoCancel();
	CEikonEnv& iEikEnv;
	};

class CSimpleAppUi;

class CDeferredAppExit : public CActive
	{
public:
	~CDeferredAppExit();
	CDeferredAppExit();
	void RequestDeferredAppExit();
private: // from CActive
	void RunL();
	void DoCancel();
	};

class CEmptyControl : public CCoeControl
	{
public:
	void ConstructL(const TRect& aRect);
	};

class CSimpleAppUi : public CEikAppUi
	{
public:
	void ConstructL();
	~CSimpleAppUi();
private: // from CCoeAppUi
	void HandleCommandL(TInt aCommand);
private:
	CEmptyControl* iEmptyControl;
	CSignalAppRunning* iAppRunning;
	CEscapeKeyPresser* iEscapeKeyPresser;
	CDeferredAppExit* iDeferredAppExit;
	};

const TInt KWaitBeforeSignalingSemaphore = 1000000;

LOCAL_C void SignalSemaphore()
	{
	RSemaphore semaphore;
	const TInt error=semaphore.OpenGlobal(SHUTAPP_SEMAPHORE);
//#ifndef __SECURE_API__
	if (error==KErrNone)
		{
			semaphore.Signal();
		}
	else
		{
		User::Panic(KShutAppPanic, EPanicErrorOpeningSemaphore);
		}
//#endif
	semaphore.Close();
	}

//
// CEscapeKeyPresser
//

CEscapeKeyPresser::CEscapeKeyPresser(CEikonEnv& aEikEnv)
: CActive(EActivePriorityWsEvents), // priority must be lower than CEikShutter's priority to ensure that CEikShutter::RunL is called inside the nested active scheduler loop which is started by displaying the alert win
	 iEikEnv(aEikEnv)
	{
	CActiveScheduler::Add(this);
	}

CEscapeKeyPresser::~CEscapeKeyPresser()
	{
	Cancel();
	}

void CEscapeKeyPresser::RequestDeferredEscapeKeyPress()
	{
	TRequestStatus* pS=(&iStatus);
	User::RequestComplete(pS, KErrNone);
	SetActive();
	}

void CEscapeKeyPresser::RunL()
	{
	TKeyEvent key;
	key.iCode=EKeyEscape;
	key.iModifiers=0;
	iEikEnv.SimulateKeyEventL(key,EEventKey);
	}

void CEscapeKeyPresser::DoCancel()
	{
	}


//
// CDeferredAppExit
//

CDeferredAppExit::CDeferredAppExit()
: CActive(EActivePriorityWsEvents-1)
	{
	CActiveScheduler::Add(this);
	}

CDeferredAppExit::~CDeferredAppExit()
	{
	Cancel();
	}

void CDeferredAppExit::RequestDeferredAppExit()
	{
	TRequestStatus* pS=(&iStatus);
	User::RequestComplete(pS, KErrNone);
	SetActive();
	}

void CDeferredAppExit::RunL()
	{
	CBaActiveScheduler::Exit();
	}

void CDeferredAppExit::DoCancel()
	{
	}

//
// CSignalAppRunning
//

CSignalAppRunning* CSignalAppRunning::NewL()
	{
	CSignalAppRunning* self=new (ELeave) CSignalAppRunning();
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}

CSignalAppRunning::~CSignalAppRunning()
	{
	Cancel();
	}

CSignalAppRunning::CSignalAppRunning()
: CTimer(EPriorityLow)
	{
	}

void CSignalAppRunning::ConstructL()
	{
	CTimer::ConstructL();
	CActiveScheduler::Add(this);
	After(TTimeIntervalMicroSeconds32(KWaitBeforeSignalingSemaphore));
	}

void CSignalAppRunning::RunL()
	{
	SignalSemaphore();
	}

void CSignalAppRunning::DoCancel()
	{
	SignalSemaphore();
	}


//
// Models
//

void CEmptyControl::ConstructL(const TRect& aRect)
	{
	CreateWindowL();
	SetRect(aRect);
	SetBlank();
	ActivateL();
	}

//
// class CSimpleAppUi
//

void CSimpleAppUi::ConstructL()
	{
	BaseConstructL(ENoAppResourceFile);
	iEmptyControl=new(ELeave) CEmptyControl;
	iEmptyControl->ConstructL(ClientRect());
	iAppRunning=CSignalAppRunning::NewL();
	iEscapeKeyPresser=new(ELeave) CEscapeKeyPresser(*iEikonEnv);
	iDeferredAppExit=new(ELeave) CDeferredAppExit();
	}

CSimpleAppUi::~CSimpleAppUi()
	{
	delete iEmptyControl;
	delete iAppRunning;
	delete iEscapeKeyPresser;
	delete iDeferredAppExit;
	}

void CSimpleAppUi::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
		case EEikCmdExit:
			{
			iEscapeKeyPresser->RequestDeferredEscapeKeyPress(); // to dismiss the dialog we're about to display after CEikShutter has had a chance to run again
			iEikonEnv->AlertWin(_L("message from shutapp"));

			// defer app exit till after CEikShutter::RunL has finished
			iDeferredAppExit->RequestDeferredAppExit();
			break;
			}
		default:
			{
			User::Panic(KShutAppPanic, EPanicReceivedUnexpectedCommand);
			break;
			}
		}
	}

//
// CSimpleDocument
//

class CSimpleDocument : public CEikDocument
	{
public:
	CSimpleDocument(CEikApplication& aApp): CEikDocument(aApp) { }
private: // from CApaDocument
	CEikAppUi* CreateAppUiL();
	};

CEikAppUi* CSimpleDocument::CreateAppUiL()
	{
	return(new(ELeave) CSimpleAppUi);
	}

//
// CSimpleApplication
//

class CSimpleApplication : public CEikApplication
	{
private: // from CApaApplication
	CApaDocument* CreateDocumentL();
	TUid AppDllUid() const;
private:
	CApaDocument* CreateDocumentL(CApaProcess* a) { return CEikApplication::CreateDocumentL(a); }
public:
	TFileName ResourceFileName() const;
	};

TUid CSimpleApplication::AppDllUid() const
	{
	return(KTestShutAppUid);
	}

CApaDocument* CSimpleApplication::CreateDocumentL()
	{
	return(new(ELeave) CSimpleDocument(*this));
	}

TFileName CSimpleApplication::ResourceFileName() const
	{
	return TFileName();
	}

//
// EXPORTed functions
//


	LOCAL_C CApaApplication* NewApplication()
		{
		return (new CSimpleApplication);
		}

	GLDEF_C TInt E32Main()
		{
		return EikStart::RunApplication(NewApplication);
		}


