/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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

// AKNSHUT.CPP
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

//
// CAknShutter
//

#include "aknshut.h"
#include <eikenv.h>
#include "aknViewAppUi.h"
#include <basched.h>
#include <coemain.h>
#include <uikon.hrh>
#include "aknview.h"
#include <oommonitorsession.h>

#include<aknenv.h>
#include<eikapp.h>
#include<akntranseffect.h>
#include"transitionmanager.h"
#include <akntoolbar.h>
#include <AknPriv.hrh>

#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikenvinterface.h>
#endif


class CKludgeScheduler : public CBaActiveScheduler
	{
public:
	inline TInt PublicLevel() const { return Level(); }
	};

const TInt KMaxNumEscKeysToSend=50;


CAknShutter::CAknShutter(CEikonEnv& aEikEnv, CAknAppUi* aBaseAppUi)
	:CActive(EActivePriorityWsEvents+1),
	 iEikEnv(aEikEnv),
	 iBaseAppUi(aBaseAppUi),
	 iStartLevel(StartLevel()),
	 iCount(0)
	{
	CActiveScheduler::Add(this);
	}

TInt CAknShutter::StartLevel()
	{
	return ((CKludgeScheduler*)CActiveScheduler::Current())->PublicLevel();
	}

CAknShutter::~CAknShutter()
	{
	Cancel();
	}

void CAknShutter::DoCancel()
	{
	}

void CAknShutter::Queue()
	{
	if (!IsActive())
		{
		TRequestStatus *pS=(&iStatus);
		User::RequestComplete(pS,0);
		SetActive();
		}
	}

void CAknShutter::RunL()
	{
	if (iCount++>KMaxNumEscKeysToSend)
		{
		Stop(); // give up
		return;
		}
	TInt startLevel=StartLevel();
	if (startLevel>iStartLevel)
		{
		Stop(); // give up: application has put up some query dialog
		return;
		}
	iStartLevel=startLevel;
	CEikAppUi* appUi=iEikEnv.EikAppUi();
	if (iBaseAppUi != appUi && appUi->ContainerAppUi())
		{
		// embedded app will not be going through a view transition, so send
		// events to the app UI.
		if (appUi->IsDisplayingMenuOrDialog())
			{
			Queue(); // before any call to CActiveScheduler::Start() from below
			TKeyEvent key;
			key.iRepeats=0;
			key.iCode=EKeyEscape;
			key.iModifiers=0;
			key.iScanCode = EStdKeyNull;
			iEikEnv.SimulateKeyEventL(key, EEventKey);
			}
		else
			{
			Queue(); // before any call to CActiveScheduler::Start() from below
			appUi->StopDisplayingMenuBar();
			appUi->HandleCommandL(EEikCmdExit);
			}
		}
	else if (IsDisplayingMenuOrDialog())
		{
		Queue(); // before any call to CActiveScheduler::Start() from below
		TKeyEvent key;
		key.iRepeats=0;
		key.iCode=EKeyEscape;
		key.iModifiers=0;
		key.iScanCode = EStdKeyNull;
		SimulateKeyEventL(key);
		}
	else if (iEikEnv.EikAppUi()->IsDisplayingMenuOrDialog())
		{ // app ui control stack check - only works in view shutter, already checked in app shutter
		Queue(); // before any call to CActiveScheduler::Start() from below
		TKeyEvent key;
		key.iRepeats=0;
		key.iCode=EKeyEscape;
		key.iModifiers=0;
		key.iScanCode = EStdKeyNull;
		iEikEnv.SimulateKeyEventL(key,EEventKey);
		}
	else
		{ // shut menus
		StopDisplayingMenuBar();
		ExitL();
		Stop(); // give up
		DeleteSelfIfSelfOwned();
		return;
		}
	}

void CAknShutter::DeleteSelfWhenReady()
	{
	if (!iSelfOwned)
		delete this;
	}

void CAknShutter::DeleteSelfIfSelfOwned()
	{
	if (iSelfOwned)
		delete this;
	}

TInt CAknShutter::RunError(TInt aError)
	{
	DeleteSelfIfSelfOwned();
	return aError;
	}
	
LOCAL_C CAknEnv& AknEnv(CEikonEnv& aEnv)
	{
	return static_cast<CAknEnv&>(*aEnv.Extension());
	}
		

CAknAppShutter* CAknAppShutter::NewL(CEikonEnv& aEikEnv, CAknAppUi* aBaseAppUi, CAknAppShutter** aSelfPtr)
	{
	return new(ELeave) CAknAppShutter(aEikEnv, aBaseAppUi, aSelfPtr);
	}

CAknAppShutter::CAknAppShutter(CEikonEnv& aEikEnv, CAknAppUi* aBaseAppUi, CAknAppShutter** aSelfPtr)
: CAknShutter(aEikEnv, aBaseAppUi), iSelfPtr(aSelfPtr)
	{
	}

void CAknAppShutter::Start()
	{
	if(iBaseAppUi->IsForeground() && iBaseAppUi->Document() )
		{
		//only if focused, otherwise next app HandleForeground may never come.
		AknEnv(iEikEnv).TransitionEvent(AknTransEffect::EApplicationExit, iBaseAppUi->Application()->AppDllUid());
		}
			
	iStartLevel = StartLevel();
	iCount = 0;
	Queue();
	}

TBool CAknAppShutter::IsDisplayingMenuOrDialog() const
	{
	return iEikEnv.EikAppUi()->IsDisplayingMenuOrDialog();
	}

void CAknAppShutter::SimulateKeyEventL(const TKeyEvent& aKeyEvent)
	{
	iEikEnv.SimulateKeyEventL(aKeyEvent,EEventKey);
	}

void CAknAppShutter::StopDisplayingMenuBar()
	{
	iEikEnv.EikAppUi()->StopDisplayingMenuBar();
	}

void CAknAppShutter::ExitL()
	{
	StopDisplayingToolbar();
	// app ui can't delete this object in destructor if it's running
	iSelfOwned = ETrue;
	CAknAppShutter** appUiSelfPtr = iSelfPtr;
	if (iSelfPtr)
		{
		ASSERT(*iSelfPtr == this);
		*iSelfPtr = NULL;
		iSelfPtr = NULL;
		}
	iEikEnv.EikAppUi()->HandleCommandL(EEikCmdExit);
	
	// If we got here, app has not closed as requested. Tell the OOM monitor
	ROomMonitorSession oomMonitor;
	if (oomMonitor.Connect() == KErrNone)
		{
		oomMonitor.ThisAppIsNotExiting(iEikEnv.RootWin().Identifier());
		oomMonitor.Close();
		}
		
	// also check that the app has not started another app shutter
	if (appUiSelfPtr && *appUiSelfPtr && (*appUiSelfPtr)->IsActive())
		{
		(*appUiSelfPtr)->DeleteSelfWhenReady();
		*appUiSelfPtr = NULL;
		}
	}

void CAknAppShutter::Stop()
	{
	AknEnv(iEikEnv).TransitionEvent(KAknTransitionExitCancel);
	
	Cancel();
	}

void CAknAppShutter::StopDisplayingToolbar()
	{
	CAknAppUi* appUi = static_cast<CAknAppUi*>( iEikEnv.EikAppUi() );
	CAknToolbar* appToolbar = 0;
	
	if ( appUi && appUi->CurrentPopupToolbar() ) 
	    {
	    appToolbar = appUi->CurrentPopupToolbar();
	    }
	else if ( appUi && appUi->PopupToolbar() )
	    {
	    appToolbar = appUi->PopupToolbar();
	    }
	    
    if ( appToolbar )
        {
        appToolbar->HandleResourceChange( KAknToolbarSetHidden );
        }
	}

CAknViewShutter::~CAknViewShutter()
	{
	iViews.Reset();
	}

CAknViewShutter* CAknViewShutter::NewL(CEikonEnv& aEikEnv, CAknAppUi* aBaseAppUi)
	{
	return new(ELeave) CAknViewShutter(aEikEnv, aBaseAppUi);
	}

void CAknViewShutter::Start( const RPointerArray<CAknView>& aViews )
	{
    iViews.Reset();
    
    for ( TInt i = 0; i < aViews.Count(); i++ )
        {
        TRAP_IGNORE( iViews.AppendL( aViews[i] ) );
        }

	iStartLevel = StartLevel();
	iCount = 0;
	Queue();
	}

CAknViewShutter::CAknViewShutter(CEikonEnv& aEikEnv, CAknAppUi* aBaseAppUi)
: CAknShutter(aEikEnv, aBaseAppUi)
	{
	}

TBool CAknViewShutter::IsDisplayingMenuOrDialog() const
	{
	return iEikEnv.EikAppUi()->IsDisplayingMenuOrDialog();
	}

void CAknViewShutter::SimulateKeyEventL(const TKeyEvent& aKeyEvent)
	{
	iEikEnv.SimulateKeyEventL(aKeyEvent,EEventKey);
	}

void CAknViewShutter::StopDisplayingMenuBar()
	{
	for ( TInt i = 0; i < iViews.Count(); i++ )
	    {
		iViews[i]->StopDisplayingMenuBar();
	    }
	}

void CAknViewShutter::ExitL()
	{
	for ( TInt i = 0; i < iViews.Count(); i++ )
	    {
		iViews[i]->AknViewDeactivated();
	    }
	}

void CAknViewShutter::Stop()
	{
	Cancel();
	}

// End of File
