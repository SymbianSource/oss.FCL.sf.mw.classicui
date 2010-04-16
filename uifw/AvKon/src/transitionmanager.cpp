/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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



#include "transitionmanager.h"
#include <eikapp.h>
#include <aknappui.h>
#include <gfxtranseffect/gfxtranseffect.h>
#include <akntranseffect.h> // for Transition effect enumerations
#include <e32property.h>
#include <UikonInternalPSKeys.h> 
#include <featmgr.h>   
#include <pslninternalcrkeys.h>
#include <centralrepository.h>	
#include <apgwgnam.h>
#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <vwsdefpartner.h>
#endif

//this class fix a memory leak:
//there were cases when exit effect was not called in 
//preparetoexit (inproper parent class, thanks (mostly) to C++)
//this class ensures that exit is called when enviroment statics are still alive
//great integration point to keep in mind!
NONSHARABLE_CLASS(CExitWatch) : public CCoeStatic
	{
	public:
		CExitWatch(MExit& aExit);
		~CExitWatch();
	private:
		MExit& iExit;
	};


const TUid KExitWatchStatic = 
				{
				0x100056C6	//this is avkon uid.... propably a new uid should be allocated.
				};

CExitWatch::CExitWatch(MExit& aExit) : CCoeStatic(KExitWatchStatic, 0xFFFFFFF), //just any priority > 100 is enough as tfx uses that
	 iExit(aExit)
	{
	}
	
CExitWatch::~CExitWatch()
	{
	iExit.DoExit();
	}


NONSHARABLE_CLASS(CCenRepListen) : public CActive, public MKeyValue
	{
	public:
		static CCenRepListen* NewL(const TUid& aRep, const TUint32 aKey, MKeyListener& aListener);
		TInt Value() const;
		TUint32 Key() const;
		void Listen();
		~CCenRepListen();
	private:
		CCenRepListen(const TUint32 aKey, MKeyListener& aListener);
		void ConstructL(const TUid& aRep);
		void DoCancel();
		void RunL();
	private:
		const TUint32 iKey;
		MKeyListener& iListener;
		TInt iValue;
		CRepository* iRepository;
	};


CCenRepListen* CCenRepListen::NewL(const TUid& aRep, const TUint32 aKey, MKeyListener& aListener)
	{
	CCenRepListen* l = new (ELeave) CCenRepListen(aKey, aListener);
	CleanupStack::PushL(l);
	l->ConstructL(aRep);
	CleanupStack::Pop();
	return l;
	}
		
TInt CCenRepListen::Value() const
	{
	return iValue;
	}
	
TUint32 CCenRepListen::Key() const
	{
	return iKey;
	}
	
void CCenRepListen::Listen()
	{
	Cancel();
	SetActive();
	iRepository->NotifyRequest(iKey, iStatus);
	}
	
CCenRepListen::CCenRepListen(const TUint32 aKey, MKeyListener& aListener) :
CActive(CActive::EPriorityStandard), iKey(aKey), iListener(aListener)
	{
	CActiveScheduler::Add(this);
	}
	
void CCenRepListen::ConstructL(const TUid& aRep)
	{
	iRepository = CRepository::NewL(aRep);
	User::LeaveIfError(iRepository->Get(iKey, iValue));
	}
	
void CCenRepListen::DoCancel()
	{
	iRepository->NotifyCancelAll();
	}
	
void CCenRepListen::RunL()
	{
	User::LeaveIfError(iRepository->Get(iKey, iValue));
	iListener.KeyChangedL(*this);
	}	

CCenRepListen::~CCenRepListen()
	{
	Cancel();
	delete iRepository;
	}


//////////////////////////////////////////////////////////////////////////

	
_LIT(KTfxServerName,"TfxServer");	
const TInt KLimit(100);	

NONSHARABLE_CLASS(CServerWait) : public CTimer
	{
	public:
		static TBool WaitL();
	private:
		CServerWait();
		void RunL();
	private:
		TInt iCount;
	};	



CServerWait::CServerWait() : CTimer(CActive::EPriorityIdle) 
	{
	CActiveScheduler::Add(this);
	}

TBool CServerWait::WaitL()
	{
	CServerWait* wait = new (ELeave) CServerWait();
	CleanupStack::PushL(wait);
	wait->ConstructL();
	wait->After(1);
	CActiveScheduler::Start();
	const TBool ok = wait->iCount <= KLimit;
	CleanupStack::PopAndDestroy(); //wait
	return ok;
	}

void CServerWait::RunL()
	{
	TFullName fullName;
	TFindServer find(KTfxServerName);
	if(iCount > KLimit || KErrNone == find.Next(fullName))
		{
		CActiveScheduler::Stop();
		}
	else
		{
		++iCount;
		After(10000);
		}
	}

	

///////////////////////////////////////////////////////////////////////////	
	
CTransitionManager* CTransitionManager::NewL(CEikonEnv& aEnv)
    {
    if(!FeatureManager::FeatureSupported(KFeatureIdUiTransitionEffects))
        return NULL; //this is only place where flag was used since calling it is slow, after that this ptr indicates its presense
    CTransitionManager* tm = new (ELeave) CTransitionManager(aEnv);
    CleanupStack::PushL(tm);
    tm->ConstructL();
    CleanupStack::Pop();
    return tm;
    }


CTransitionManager::CTransitionManager(CEikonEnv& aEnv) : iEikEnv(aEnv)
	{
	}
	

void CTransitionManager::AppStartupComplete()
	{
    TRAP_IGNORE( iEikEnv.EikAppUi()->AddViewObserverL( this ) );
	if(iFlags & EStarted)
		{
        iStartIdleState = ETransEffectWaitingForAppSwitch;
	    iFlags |= EStartupStarted;
		}
	else
		{
		iFlags |= (EStarted | EStartupStarted | EStartupComplete);
		GfxTransEffect::AbortFullScreen();
		}
	}
	

void CTransitionManager::ConstructL()
	{
	iAppStartupIdle = CIdle::NewL( CActive::EPriorityIdle );
	iCRListen = CCenRepListen::NewL(KCRUidThemes, KThemesTransitionEffects, *this);
	CheckEffectsL(EFalse);
	new (ELeave) CExitWatch(*this); //it is enviroment static, pointer to that is not needed 
	}
	

void CTransitionManager::DoExit()
	{
	if(iFlags & EStartupComplete && iAppUid != KNullUid)
		{
		RWsSession ses;
		if(KErrNone == ses.Connect())
			{
			TThreadId focusThreadId;
    		ses.GetWindowGroupClientThreadId(ses.GetFocusWindowGroup(), focusThreadId);
			RThread myThread;
    		if(myThread.Id() == focusThreadId)
    			{
				AppExit(AknTransEffect::EApplicationExit, iAppUid);
				}
			ses.Close();
			}
		}
	}
	
		
CTransitionManager::~CTransitionManager()
	{
	delete iCRListen;
    if(iAppStartupIdle != NULL)
    	{
    	iAppStartupIdle->Cancel();
    	}
    delete iAppStartupIdle;
	}
	

TBool CTransitionManager::AppStartupCb(TAny* aThis)
	{
	static_cast<CTransitionManager*>(aThis)->Startup();
	return EFalse;
	}

// Implementation of MCoeViewActivationObserver MCoeViewObserver
void CTransitionManager::HandleViewEventL( const TVwsViewEvent& aEvent )
    {
    switch( aEvent.iEventType )
        {
        case TVwsViewEvent::EVwsActivateView:
            // Appswitch has triggered flag so start idle callback
            if( iStartIdleState  == ETransEffectWaitingForViewSwitch)
                {
                if( !iAppStartupIdle->IsActive() )
                    {
                    iStartIdleState = ETransEffectWaitingForIdleCall;
                    iAppStartupIdle->Start( TCallBack( AppStartupCb, this ) );
                    }
                }
            else if( iStartIdleState == ETransEffectIdle && Ready() )
                // Wait for appswitch
                {
                iStartIdleState = ETransEffectWaitingForAppSwitch;
                }
            break;
        case TVwsViewEvent::EVwsDeactivateView:
            // Appswitch has triggered flag so start idle callback
            if( iStartIdleState  == ETransEffectWaitingForViewSwitch)
                {
                if( !iAppStartupIdle->IsActive() )
                    {
                    iStartIdleState = ETransEffectWaitingForIdleCall;
                    iAppStartupIdle->Start( TCallBack( AppStartupCb, this ) );
                    }
                }
            break;
        default:
            // Reset state if viewdeactivate to other app
            if( aEvent.iViewOneId.iAppUid != aEvent.iViewTwoId.iAppUid )
                {
                iStartIdleState = ETransEffectIdle;
                }
        break;
        }
    }

void CTransitionManager::SetEmbedded()
	{
	iFlags |= EEmbedded;
	}
	
void CTransitionManager::Startup()
	{
	if(!(iFlags & EStartupComplete))
		{
		const TInt group = iEikEnv.RootWin().Identifier();
		if(group != 0)
			{
	    	TWsEvent event;
	    	event.SetType(EEventNull);
	    	event.SetTimeNow();
	    	iEikEnv.WsSession().SendEventToWindowGroup(group, event);
			}
		}
	if( ( iEikEnv.AppUi() != NULL ) && ( static_cast<CAknAppUi*>(iEikEnv.AppUi())->IsForeground() ) )
		{
		iEikEnv.WsSession().Flush(); //ensure that all drawing commands will be in server
		GfxTransEffect::EndFullScreen();	 	
		}
	iFlags |= EStartupComplete;
    iStartIdleState = ETransEffectIdle;
	}
	
	
TBool CTransitionManager::IsFullScreen() const
	{
	return (iEikEnv.AppUi() != NULL && static_cast<CAknAppUi*>(iEikEnv.AppUi())->IsFullScreenApp());
	}	
	
void CTransitionManager::AppSwitch(TInt aContext/*, const TUid& aUid*/)	
    {
    // Set the parent again as it might be cleared by another embedded instance 
    // (with the same uid) on exit
    if ( iFlags & EEmbedded )
        {
        const TInt focusWGroupId = iEikEnv.WsSession().GetFocusWindowGroup();
        const TInt thisApplicationWgId = iEikEnv.RootWin().Identifier();
        if ( focusWGroupId == thisApplicationWgId )
            {
            SendAvkonInfo();
            }
        }

    if(Ready())
    	{
    	iEikEnv.WsSession().Flush(); 
    

    	if(aContext == AknTransEffect::EApplicationActivate && (iFlags & EStartupStarted)) 
        	{
            // If this is a plain switch without a previous appstart then just wait for view activate
            if( iStartIdleState == ETransEffectIdle )
                {
                iStartIdleState = ETransEffectWaitingForViewSwitch;
                }
            else if( iStartIdleState == ETransEffectWaitingForAppSwitch )
                {
                if( !iAppStartupIdle->IsActive() )
                    {
                    iStartIdleState = ETransEffectWaitingForIdleCall;
                    iAppStartupIdle->Start( TCallBack( AppStartupCb, this ) );
                    }
                }
            }
        }
    }

void CTransitionManager::AppStartup(TInt aContext, const TUid& aUid)
	{  
	ASSERT(!(iFlags & EStarted));
	ASSERT(aUid != KNullUid);
	
	iAppUid = aUid;
	
	//reset instance data e.g. emedded and fullscreen as those params
	//may vary per instance
	TInt flags = AknTransEffect::TParameter::EResetServerStats; 
			         
	if(Ready())
	    {
	    
	    if( aContext == AknTransEffect::EAppStartupBackground )
	        {
	        flags |= AknTransEffect::TParameter::ENoEffects;
	        GfxTransEffect::BeginFullScreen(aContext, TRect(0,0,0,0),
    	    AknTransEffect::EParameterAvkonInternal, AknTransEffect::GfxTransParam(aUid, flags)); 
	        }
	    else
    	    {
    		GfxTransEffect::BeginFullScreen(aContext, TRect(0,0,0,0),
    	        AknTransEffect::EParameterType, AknTransEffect::GfxTransParam(aUid, flags)); 
    	  	}
    		
        iFlags |= EStarted;
	    }
	}


void CTransitionManager::KeyChangedL(const MKeyValue& aValue)
	{
	ASSERT(aValue.Key() == KThemesTransitionEffects);
	ASSERT(!(iFlags & EffectsEnabled));
	CheckEffectsL(ETrue);

	SendAvkonInfo();
	CheckFlags();
	}

void CTransitionManager::CheckEffectsL(TBool aWait)
	{
	if(!(iFlags & EffectsEnabled))
		{
		if(iCRListen->Value() & AknTransEffect::EFullScreenTransitionsOff)
			{
			iFlags &= ~EffectsEnabled;	
			iCRListen->Listen();
			}
		else if(!aWait || CServerWait::WaitL())
			{
			iFlags |= EffectsEnabled;	
			}
		}
	}
	
		
void CTransitionManager::SetAvkon()
	{	
	if(iAppUid != KNullUid && !(iFlags & EAvkonApp))
		{
		iFlags |= EAvkonApp;
		SendAvkonInfo();
		}
	}
	
void CTransitionManager::GetRootAppL(TUid& aRootAppUid)
	{
	RWsSession& ws = iEikEnv.WsSession();
	RWsSession::TWindowGroupChainInfo wgInfo = {0,0};
	wgInfo.iId = iEikEnv.RootWin().Identifier();
	TInt foundWgId = wgInfo.iId;
	
	RArray<RWsSession::TWindowGroupChainInfo> wgInfoArray;
	ws.WindowGroupList(&wgInfoArray);
	TInt index = wgInfoArray.Find(wgInfo);
	
	// Find the root window group
	while( index >= 0 )
		{
		foundWgId = wgInfo.iId;
		wgInfo.iId = wgInfoArray[index].iParentId;
		index = wgInfoArray.Find(wgInfo);
		} 	
	wgInfoArray.Close();

	CApaWindowGroupName* windowName = CApaWindowGroupName::NewLC(ws, foundWgId);
    aRootAppUid = windowName->AppUid();
	CleanupStack::PopAndDestroy();  //windowName
	}	

void CTransitionManager::SendAvkonInfo()
	{
	if((iFlags & EffectsEnabled) && (iAppUid != KNullUid) && (iFlags & EAvkonApp))
		{
#ifdef TFX_USE_WCHANGE_EVENT		
		TUid parentUid = KNullUid; 
		
		if(iFlags & EEmbedded)
			{ //set this app parent if emdded, thus server can go parent chain
			//and not to do switch effects between chain apps
			TRAP_IGNORE(GetRootAppL(parentUid));
			}	
		
		const TUint data[3] = {iAppUid.iUid, parentUid.iUid, iEikEnv.RootWin().Identifier()};
		
		const TPckgC<TUint[3]> buffer(data);
			
		GfxTransEffect::BeginFullScreen(AknTransEffect::ENone, 
	  		TRect(0,0,0,0),
	    	AknTransEffect::EParameterAvkonInternal,
	     	buffer);
	     	
#else
		TInt flags = AknTransEffect::TParameter::EAvkonCheck;
		
		TUid parentUid = KNullUid; 
		
		if(iFlags & EEmbedded)
			{ //set this app parent if emdded, thus server can go parent chain
			//and not to do switch effects between chain apps
			flags |= AknTransEffect::TParameter::EParentUid;
			TRAP_IGNORE(GetRootAppL(parentUid));
			}
			
		GfxTransEffect::BeginFullScreen(AknTransEffect::ENone, 
	  		TRect(0,0,0,0),
	    	AknTransEffect::EParameterType,
	     	AknTransEffect::GfxTransParam(iAppUid, parentUid, flags)); 
#endif	
			
		}
	}		
	

void CTransitionManager::SetDisableEffects(TBool aDisable)
	{
	if(iAppUid == KNullUid)
		return;
	const TInt flags = aDisable ? 
		AknTransEffect::TParameter::ENoEffects : 
		AknTransEffect::TParameter::EEnableEffects ;
	GfxTransEffect::BeginFullScreen(AknTransEffect::ENone, //not important
	  		TRect(0,0,0,0),
	    	AknTransEffect::EParameterType,
	     	AknTransEffect::GfxTransParam(iAppUid, flags));
	}

void CTransitionManager::CheckFlags()
	{
	if((iFlags & EffectsEnabled) && //some one hearing us
	 ( !IsFullScreen())) //they were disabled (flag not equal with state) or not fullscreen
		{
	    SetDisableEffects(ETrue);
		}		
	}		

void CTransitionManager::AppExit(TInt /*aContext*/, const TUid& aUid)
	{
	if(aUid != KNullUid && Ready())
		{
		const TInt flags = AknTransEffect::TParameter::EAvkonCheck;//EAvkonExit;
		const TInt context = 
				(iFlags & EEmbedded)           //if embedded
			?  
			AknTransEffect::EEmbeddedApplicationExit // just for no effect
			: AknTransEffect::EApplicationExit;       // do a exit effect
		
		GfxTransEffect::BeginFullScreen(context, TRect(0,0,0,0),
			AknTransEffect::EParameterType, AknTransEffect::GfxTransParam(aUid, flags));
			
		}
	iFlags |= EExitCompleted;
	}
	
void CTransitionManager::CancelExit()
	{
	if(iFlags & EExitCompleted)
		{
		GfxTransEffect::AbortFullScreen();
		iFlags &= ~EExitCompleted;
		}
	}
	
TBool CTransitionManager::Ready()
	{
	if(iFlags & EExitCompleted)
		return EFalse;
	if(!(iFlags & EffectsEnabled))
		return EFalse;
	if(!(iFlags & EEnviromentReady))
		{
		TBool allowed;
		if(KErrNone == RProperty::Get(KPSUidUikon, KUikGlobalNotesAllowed, allowed) && allowed)
			{
			iFlags |= EEnviromentReady;
			}
		}
	return (iFlags & EEnviromentReady) != 0;
	}
	
