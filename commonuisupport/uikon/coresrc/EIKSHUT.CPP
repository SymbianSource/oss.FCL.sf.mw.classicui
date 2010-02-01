// Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
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
// CEikShutter
// 
//

#include "EIKSHUT.H"
#include <eikenv.h>
#include <eikappui.h>
#include <basched.h>
#include <coemain.h>
#include <uikon.hrh>

const TUid KEikShutterSingletonUid = {0x1028306A};

NONSHARABLE_CLASS(CLocalScheduler) : public CBaActiveScheduler
	{
public:
	inline TInt PublicLevel() const { return Level(); }
	};

const TInt KMaxNumEscKeysToSend=50;

void CEikShutter::DeferredExecuteL(CEikonEnv& aEikEnv)
	{
	if(aEikEnv.FindStatic(KEikShutterSingletonUid))
		return;	// a shutter is already invoked with the intention of closing this app
			
	new(ELeave) CEikShutter(aEikEnv, KNullUid, NULL);
	}

void CEikShutter::DeferredExecuteL(CEikonEnv& aEikEnv, TUid aMessageUid, const TDesC8& aMessageParameters)
	{
	if(aEikEnv.FindStatic(KEikShutterSingletonUid))
		return;	// a shutter is already invoked with the intention of closing this app
		
	new(ELeave) CEikShutter(aEikEnv, aMessageUid, aMessageParameters.AllocLC());
	CleanupStack::Pop(); // aMessageParameters.AllocLC()
	}

CEikShutter::CEikShutter(CEikonEnv& aEikEnv, TUid aMessageUid, HBufC8* aMessageParameters)
	:CActive(EActivePriorityWsEvents+1), CCoeStatic(KEikShutterSingletonUid, CCoeStatic::EThread),
	 iEikEnv(aEikEnv),
	 iMessageUid(aMessageUid),
	 iMessageParameters(aMessageParameters),
	 iFlags(0),
	 iCount(0),
	 iStartLevel(StartLevel())
	{
	CActiveScheduler::Add(this);
	Queue();
	}

TInt CEikShutter::StartLevel()
	{
	return ((CLocalScheduler*)CActiveScheduler::Current())->PublicLevel();
	}

CEikShutter::~CEikShutter()
	{
	Cancel();
	delete iMessageParameters;
	}

void CEikShutter::DoCancel()
	{
	}

void CEikShutter::Queue()
	{
	TRequestStatus *pS=(&iStatus);
	User::RequestComplete(pS,0);
	SetActive();
	}

void CEikShutter::Terminate()
	{
	if (iFlags&ETryingToTerminateApp)
		{
		Cancel();
		iFlags|=EDestroySelfPending;
		}
	else
		delete this;
	}

void CEikShutter::RunL()
	{
	if (iCount++>KMaxNumEscKeysToSend)
		{
		Terminate();
		return;
		}
	TInt startLevel=StartLevel();
	if (startLevel>iStartLevel)
		{
		Terminate();
		return;
		}
	iStartLevel=startLevel;
	CEikAppUi* appUi=iEikEnv.EikAppUi();
	const TBool displayingDialog=appUi->IsDisplayingDialog();
	if (appUi->IsDisplayingMenuOrDialog() && (displayingDialog || !(iFlags&ETriedDismissMenu)))
		{
		if (!displayingDialog)
			{
			iFlags|=ETriedDismissMenu;
			}
		Queue(); // before any call to CActiveScheduler::Start() from below
		TKeyEvent key;
		key.iCode=EKeyEscape;
		key.iScanCode=0;
		key.iModifiers=0;
		key.iRepeats=0;
		iEikEnv.SimulateKeyEventL(key,EEventKey);
		}
	else if (appUi->ContainerAppUi() || (iMessageParameters==NULL))
		{
		iFlags&=~ETriedDismissMenu;
		Queue(); // before any call to CActiveScheduler::Start() from below
		iFlags |= ETryingToTerminateApp;
		TRAPD(error, appUi->HandleCommandL(EEikCmdExit)); // will leave when really exits
				
		iFlags &= ~ETryingToTerminateApp;
		User::LeaveIfError(error);
		if (iFlags&EDestroySelfPending)
			{
			iFlags&=~EDestroySelfPending;
			delete this;
			return;
			}
		}
	else
		{ // don't call Queue() in this case, else crash if switch files throws up dialog with wait
		appUi->ProcessMessageL(iMessageUid, *iMessageParameters);
		Terminate();
		return;
		}
	}

TInt CEikShutter::RunError(TInt aError)
	{
	Terminate();
	return aError;
	}
