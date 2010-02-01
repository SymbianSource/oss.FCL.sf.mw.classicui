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
//

#include "GfxTransImpl.h"
#include "GfxTransUtils.h"
#include "TransitionControl.h"
#include "RegisteredControl.h"
#include "GfxTransEffectPanic.h"
#include <coecntrl.h>

//
//

const TUid CGfxTransEffect::KTransEffectUid = {0x102822A6};

//
// Construction/Destruction
//

CGfxTransEffect::CGfxTransEffect() :
	CCoeStatic(KTransEffectUid,-1,CCoeStatic::EApp),
	iEnabled(ETrue)
	{
	iCreateHandle = 0;
	}
	
CGfxTransEffect::~CGfxTransEffect()
	{
	delete iPolicyHandler;
	
	iInTransition.ResetAndDestroy();
	iInTransition.Close();

	iRegistered.ResetAndDestroy();
	iRegistered.Close();

	iActiveStack.ResetAndDestroy();
	iActiveStack.Close();

	MGfxTransAdapter::Destroy(iAdapter);
	}
	
TInt CGfxTransEffect::Construct()
	{
	TRAPD(err,iAdapter = MGfxTransAdapter::CreateL(this));
	if(err != KErrNone) 
		{
		return err;
		}
	iPolicyHandler = new CPolicyHandler();
	if(!iPolicyHandler)
		{
		return KErrNoMemory;
		}
	// Get policies from engine
	TInt count;
	TControlPolicy *policies = iAdapter->GetTransitionPolicies(count);
	if(count > 0 && policies != NULL)
		{
		// the policyhandler handles the memory cleanup
		iPolicyHandler->SetTransitionPolicies(policies, count);
		}
	return KErrNone;
	}
	
CGfxTransEffect* CGfxTransEffect::Static(const CCoeControl * aControl)
	{
	CGfxTransEffect *singleton = StaticNoCreate(aControl);
	if(!singleton)
		{
		singleton = new CGfxTransEffect;
		if(NULL == singleton)
			{
			return NULL;
			}
		if(KErrNone != singleton->Construct())
			{
			delete singleton;
			singleton=NULL;
			return NULL;
			}
		__ASSERT_ALWAYS(aControl->ControlEnv()->FindStatic(KTransEffectUid) == singleton,Panic(EGfxTransEffectFindStatic));
		}
	__ASSERT_ALWAYS(singleton,Panic(EGfxTransEffectNotSingleton));
	return singleton;
	}

CGfxTransEffect* CGfxTransEffect::StaticNoCreate(const CCoeControl * aControl)
	{
	__ASSERT_DEBUG(aControl,Panic(KErrArgument));
	if (!aControl->ControlEnv())
		{
		return NULL;
		}
	return reinterpret_cast<CGfxTransEffect*>(aControl->ControlEnv()->FindStatic(KTransEffectUid));
	}
CGfxTransEffect* CGfxTransEffect::Static()
	{
	if (!CCoeEnv::Static())
		{
		return NULL;
		}
	CGfxTransEffect *singleton = reinterpret_cast<CGfxTransEffect*>(CCoeEnv::Static(KTransEffectUid));
	if(!singleton)
		{
		singleton = new CGfxTransEffect;
		if(NULL == singleton)
			{
			return NULL;
			}
		if(KErrNone != singleton->Construct())
			{
			delete singleton;
			singleton=NULL;
			return NULL;
			}
		__ASSERT_ALWAYS(CCoeEnv::Static(KTransEffectUid) == singleton,Panic(EGfxTransEffectNotSingleton));
		}
	__ASSERT_ALWAYS(singleton,Panic(EGfxTransEffectNotSingleton));
	return singleton;
	}

CGfxTransEffect* CGfxTransEffect::StaticNoCreate()
	{
	if (!CCoeEnv::Static())
		{
		return NULL;
		}
	return reinterpret_cast<CGfxTransEffect*>(CCoeEnv::Static(KTransEffectUid));
	}

//
// API implementation
//
//---------------------------------
// registration
//---------------------------------
void CGfxTransEffect::Register(const CCoeControl * aKey,const TVwsViewId &aView,TUid aType)
	{
	const TInt idx = FindRegistration(aKey);
	if(IsValidIndex(idx)) // previously registered! update. 
		{
		iRegistered[idx]->SetUid(aType);
		iRegistered[idx]->SetViewId(aView);
		iRegistered[idx]->SetType(CRegisteredControl::EView);
		iRegistered[idx]->SetRegistered(ETrue);
		}
	else 
		{
		if(CRegisteredControl* regctrl = new CRegisteredControl(aKey,aView,aType))
			{
			if(KErrNone != iRegistered.Append(regctrl)) 
				{
				//Failed to add, probably due to memory constraints. Fail silently without registering.
				delete regctrl;
				}
			}
		}		
	}
void CGfxTransEffect::Register(const CCoeControl * aKey,TUid aType,TBool aNLayered)
	{
	const TInt idx = FindRegistration(aKey);
	if(IsValidIndex(idx)) // previously registered! update. 
		{
		iRegistered[idx]->SetUid(aType);
		iRegistered[idx]->SetNLayered(aNLayered);
		iRegistered[idx]->SetType(CRegisteredControl::ECoeControl);
		iRegistered[idx]->SetRegistered(ETrue);
		}
	else 
		{
		if(CRegisteredControl* regctrl = new CRegisteredControl(aKey,aType,aNLayered))
			{
			if(KErrNone != iRegistered.Append(regctrl)) 
				{
				//Failed to add, probably due to memory constraints. Fail silently without registering.
				delete regctrl;
				}
			}
		}		
	}

TBool CGfxTransEffect::IsRegistered(const CCoeControl * aKey)
	{
	const TInt idx = FindRegistration(aKey);
	return (IsValidIndex(idx) && iRegistered[idx]->Registered());
	}
	
void CGfxTransEffect::Deregister(const CCoeControl * aKey)
	{
	const TInt idx = FindRegistration(aKey);
	if(IsValidIndex(idx))
		{
		CRegisteredControl* regctrl = iRegistered[idx];
		TInt activeidx  = iActiveStack.Find(regctrl);
		if(IsValidIndex(activeidx))
			{
			//deregisters between begin and end aborts transition.
			Abort(aKey);
			}
		if(regctrl->InTransitionCount() > 0)
			{
			//If in transition, set registered flag to EFalse
			regctrl->SetRegistered(EFalse);
			//and reset all transition data (such as remotegc)
			regctrl->ResetTransitions();
			//and draw now
			regctrl->Control()->DrawNow();
			}
		else 
			{
			//no ongoing transitions - so remove
			iRegistered.Remove(idx);
			#ifdef _DEBUG
			iRegistered.Compress(); //for __UHEAP_MARK tests.
			#endif
			delete regctrl;
			}
		}
	}

//---------------------------------
// Begin/End   
//---------------------------------
void CGfxTransEffect::Begin(const CCoeControl * aKey,TUint aAction)
	{
	const TInt regidx = FindRegistration(aKey);
	if(!IsValidIndex(regidx) || !(iRegistered[regidx]->Registered()))
		{
		return; //Unregistered controls are silently ignored.
		}
	CRegisteredControl* regctrl = iRegistered[regidx];
	
	//get policy
	TPolicy policy;
	if(!IsEnabled() || !iAdapter->IsActive())
		{
		policy = ENotSupported;
		}
	else
		{
		policy = iPolicyHandler->GetPolicy(regctrl->Uid(), aAction);
		}
		
	//reset active and ongoing transitions for this registered control
	if(policy == ESupported)
		{
		regctrl->ResetTransitions();
		}
		
	//Create a new transition control
	CTransitionControl *transctrl;
	if(NULL == (transctrl = CTransitionControl::New(regctrl, this, aAction, policy, CreateTransitionHandle())))
		{
		return; 
		}
		
	//add transition to the registered control
	if(KErrNone != regctrl->AddTransition(transctrl))
		{
		delete transctrl;
		return;
		}
	
	//add to stack
	if(KErrNone != iActiveStack.Push(transctrl))
		{
		delete transctrl;
		return;
		}
	
	
	// if supported: Capture Begin state
	iAdapter->HandleClientState(MGfxTransAdapter::EPreBeginCapture, aKey, transctrl->Handle());
	
	transctrl->CaptureBegin();
		
	iAdapter->HandleClientState(MGfxTransAdapter::EPostBeginCapture, aKey, transctrl->Handle());
	}

void CGfxTransEffect::BeginLC(const CCoeControl * aKey,TUint aAction)
	{
	const TInt regidx = FindRegistration(aKey);
	if(!IsValidIndex(regidx) || !(iRegistered[regidx]->Registered())) 
		{
		return; //Unregistered controls are silently ignored.
		}
	CRegisteredControl* regctrl = iRegistered[regidx];
	
	TPolicy policy;
	if(!IsEnabled() || !iAdapter->IsActive())
		{
		policy = ENotSupported;
		}
	else
		{
		policy = iPolicyHandler->GetPolicy(regctrl->Uid(), aAction);
		}
		
	//reset active and ongoing transitions for this registered control
	if(policy == ESupported)
		{
		regctrl->ResetTransitions();
		}
	
	//Create a new transition control
	CTransitionControl *transctrl = NULL;
	if(NULL == (transctrl = CTransitionControl::New(regctrl, this, aAction, policy, CreateTransitionHandle())))
		{
		return; 
		}
	
	//add transition to the registered control
	if(KErrNone != regctrl->AddTransition(transctrl))
		{
		delete transctrl;
		return;
		}
	
	//add to stack
	if(KErrNone != iActiveStack.PushLC(transctrl))
		{
		delete transctrl;
		return;
		}
	
	iAdapter->HandleClientState(MGfxTransAdapter::EPreBeginCapture, aKey, transctrl->Handle());

	//capture begin
	transctrl->CaptureBegin();

	iAdapter->HandleClientState(MGfxTransAdapter::EPostBeginCapture, aKey, transctrl->Handle());
	}

void CGfxTransEffect::End(const CCoeControl * aKey)
	{
	CTransitionControl* transctrl = NULL;
	
	TInt idx = iActiveStack.Find(aKey);
	
	//Fallback if the control isn't in the iActiveStack
	if(!IsValidIndex(idx))
		{
		Fallback(aKey);
		return;
		}
	
	iActiveStack.ClearAbove(idx);
		
	transctrl = iActiveStack.Top();
	if(!transctrl) 
		{
		Fallback(aKey); 
		return;
		}
	
	iAdapter->HandleClientState(MGfxTransAdapter::EPreEndCapture, transctrl->RegControl()->Control(), transctrl->Handle());
	
	//capture end	
	transctrl->CaptureEnd();

	iAdapter->HandleClientState(MGfxTransAdapter::EPostEndCapture, transctrl->RegControl()->Control(), transctrl->Handle());
	
	//pop control from stack 
	iActiveStack.Pop();
	

	if(!transctrl->Failed())
		{
		// start the transition
		if(	(transctrl->Policy() == ESupported))
			{
			//add control to InTranstionList
			if(KErrNone != iInTransition.Append(transctrl))
				{
				delete transctrl;
				Fallback(aKey);
				return;
				}
			iAdapter->StartTransition(transctrl->Handle());
			if((0 < iInTransition.Count()) && (transctrl == iInTransition[iInTransition.Count() - 1]))
			    {
			    transctrl->SetListenForUpdates(ETrue);
			    }
			}
		// if not supported: draw the updated parts of the control
		else 
			{
			RRegion region;
			if(KErrNone != transctrl->GetUpdatedRegion(region))
				{
				delete transctrl;
				Fallback(aKey);
				return;
				}
			TInt count = region.Count();
			for(TInt i = 0; i < count; i++)
				{
				aKey->DrawNow(region[i]);
				}
			region.Close();
			delete transctrl;
			}
		}
	else 
		{
		delete transctrl;
		Fallback(aKey);
		return;
		}		
	}

//---------------------------------
// NotifyExternalState
//---------------------------------

void CGfxTransEffect::NotifyExternalState(TInt aState, const TDesC8* aArg)
	{
	iAdapter->NotifyExternalState(aState,aArg);	
	}

//---------------------------------
// Abort
//---------------------------------

void CGfxTransEffect::Abort(const CCoeControl * aKey)
	{
	//abort current begin-end pair
	CTransitionControl *current = iActiveStack.Top();
	if(current && current->RegControl()->Control() == aKey)
		{
		iActiveStack.Pop();
		iAdapter->HandleClientState(MGfxTransAdapter::EAbort, aKey, current->Handle());
		delete current;
		}
	}
	
// global abort
void CGfxTransEffect::Abort()
	{
	CTransitionControl *current = iActiveStack.Top();
	
	// inform the engine
	if(current)
		{
		iAdapter->HandleClientState(MGfxTransAdapter::EGlobalAbort, current->RegControl()->Control(), 0);
		}
		
	// delete all transitions in active stack
	while(current)
		{
		iActiveStack.Pop();
		iAdapter->HandleClientState(MGfxTransAdapter::EAbort, current->RegControl()->Control(), current->Handle());
		delete current;
		current = iActiveStack.Top();
		}
		
	// abort all transitions in InTransition list
	TInt const count = iInTransition.Count();
	for(TInt i = 0; i < count; i++)
		{
		iAdapter->HandleClientState(MGfxTransAdapter::EAbort, iInTransition[i]->RegControl()->Control(), iInTransition[i]->Handle());
		//no removal, wait for TransitionFinished from the server
		}		
	}
	
//---------------------------------
// Hints
//---------------------------------
void CGfxTransEffect::SetHints(const CCoeControl * aControl,TUint aFlags)
	{
	//first check the active stack for registered controls
	TInt idx = iActiveStack.Find(aControl);	
	if(IsValidIndex(idx))
		{
		iActiveStack[idx]->SetHints(aControl, aFlags);
		return;
		}
	// if not a registered control is active stack
	// check if it is a registered control	
	idx = FindRegistration(aControl);
	if(IsValidIndex(idx))
		{
		iRegistered[idx]->SetFlags(aFlags);
		}
	// Also test if aControl is a layer in a transition
	idx = iActiveStack.Find(aControl->Parent());
	if(IsValidIndex(idx))
		{
		iActiveStack[idx]->SetHints(aControl, aFlags);
		return;
		}
	}

TUint CGfxTransEffect::GetHints(const CCoeControl * aControl)
	{
	// first check if it is a registered control
	TInt idx = FindRegistration(aControl);
	if(IsValidIndex(idx))
		{
		return iRegistered[idx]->Flags();
		}
	// check if it is a subcontrol in an active transition
	idx = iActiveStack.Find(aControl->Parent());
	if(IsValidIndex(idx))
		{
		return iActiveStack[idx]->GetHints(aControl);
		}
	return GfxTransEffect::ENone;
	}

void CGfxTransEffect::SetHints(const CCoeControl * aControl,TUid aLayerType)
	{
	TInt idx = iActiveStack.Find(aControl);
	if(!IsValidIndex(idx))
		{
		idx = iActiveStack.Find(aControl->Parent());
		if(!IsValidIndex(idx))
			{
			return;
			}
		}
	iActiveStack[idx]->SetHints(aControl, aLayerType);
	}

void CGfxTransEffect::Invalidate(const CCoeControl * aControl)
	{
	TInt idx = iActiveStack.Find(aControl);
	if(!IsValidIndex(idx))
		{
		idx = iActiveStack.Find(aControl->Parent());
		if(!IsValidIndex(idx))
			{
			return;
			}
		}
	iActiveStack[idx]->Invalidate(aControl);
	}
	
//---------------------------------
// Demarcation
//---------------------------------
void CGfxTransEffect::SetDemarcation(const CCoeControl * aControl,TPoint const &aDemarcation)
	{
	TInt idx = iActiveStack.Find(aControl);
	if(!IsValidIndex(idx))
		{
		idx = iActiveStack.Find(aControl->Parent());
		if(!IsValidIndex(idx))
			{
			return;
			}
		}
	iActiveStack[idx]->DoSetDemarcation(aControl, TRect(aDemarcation, TSize(0,0)));
	}

void CGfxTransEffect::SetDemarcation(TVwsViewId const &aView,TPoint const &aDemarcation)
	{
	TInt idx = iActiveStack.FindView(aView);
	if(!IsValidIndex(idx))
		{
		return;
		}
	iActiveStack[idx]->DoSetDemarcation(iActiveStack[idx]->RegControl()->Control(), 
										TRect(aDemarcation, TSize(0,0)));
	}

void CGfxTransEffect::SetDemarcation(const CCoeControl * aControl,TRect const &aDemarcation)
	{
	TInt idx = iActiveStack.Find(aControl);
	if(!IsValidIndex(idx))
		{
		idx = iActiveStack.Find(aControl->Parent());
		if(!IsValidIndex(idx))
			{
			return;
			}
		}
	iActiveStack[idx]->DoSetDemarcation(aControl, aDemarcation);
	}

void CGfxTransEffect::SetDemarcation(TVwsViewId const &aView,TRect const &aDemarcation)
	{
	TInt idx = iActiveStack.FindView(aView);
	if(!IsValidIndex(idx))
		{
		return;
		}
	iActiveStack[idx]->DoSetDemarcation(iActiveStack[idx]->RegControl()->Control(), aDemarcation);
	}

void CGfxTransEffect::SetDemarcation(const CCoeControl * aControl,const CCoeControl * aSrc,TRect const &aDemarcation)
	{
	TInt idx = iActiveStack.Find(aControl);
	if(!IsValidIndex(idx))
		{
		idx = iActiveStack.Find(aControl->Parent());
		if(!IsValidIndex(idx))
			{
			return;
			}
		}
	iActiveStack[idx]->DoSetDemarcation(aControl, aSrc, aDemarcation);
	}

void CGfxTransEffect::SetDemarcation(TVwsViewId const &aView,const CCoeControl * aSrc,TRect const &aDemarcation)
	{
	TInt idx = iActiveStack.FindView(aView);
	if(!IsValidIndex(idx))
		{
		return;
		}
	iActiveStack[idx]->DoSetDemarcation(iActiveStack[idx]->RegControl()->Control(),
										aSrc, aDemarcation);
	}
	
//---------------------------------
// Adapter state
//---------------------------------
void CGfxTransEffect::Enable()
	{
	iAdapter->IsActive();
	iEnabled = ETrue; //enable regardless if engine IsActive or not.
	}

void CGfxTransEffect::Disable()
	{
	Abort();
	iEnabled = EFalse;
	}

//---------------------------------
// API additions
//---------------------------------
void CGfxTransEffect::SetEndDemarcation(const CCoeControl* aControl, const TRect& aDemarcation)
	{
	TInt idx = iActiveStack.Find(aControl);
	if(!IsValidIndex(idx))
		{
		idx = iActiveStack.Find(aControl->Parent());
		if(!IsValidIndex(idx))
			{
			return;
			}
		}
	iActiveStack[idx]->DoSetEndDemarcation(aControl, aDemarcation);
	}
	
void CGfxTransEffect::SetBeginDemarcation(const CCoeControl* aControl, const TRect& aDemarcation)
	{
	TInt idx = iActiveStack.Find(aControl);
	if(!IsValidIndex(idx))
		{
		idx = iActiveStack.Find(aControl->Parent());
		if(!IsValidIndex(idx))
			{
			return;
			}
		}
	iActiveStack[idx]->DoSetBeginDemarcation(aControl, aDemarcation);
	}
	
TInt CGfxTransEffect::BeginGroup()
	{
	TInt groupId = CreateTransitionHandle();
	iAdapter->HandleClientState(MGfxTransAdapter::EBeginGroup, NULL, groupId);
	return groupId;
	}
	 
void CGfxTransEffect::EndGroup(TInt aGroupId)
	{
	iAdapter->HandleClientState(MGfxTransAdapter::EEndGroup, NULL, aGroupId);
	}
	
void CGfxTransEffect::SetTransitionData(TUint aType, const TDesC8& aData)
	{
	CTransitionControl *aTransControl = iActiveStack.Top();
	if(aTransControl)
		{
		aTransControl->SetTransitionData(aType, aData);
		}
	}

void CGfxTransEffect::SetTransitionObserver(MGfxTransEffectObserver *aObserver)
	{
	iObserver = aObserver;
	}
	
//---------------------------------
// Draw item controls
//---------------------------------
void CGfxTransEffect::RegisterDrawItemControl(const CCoeControl *aControl, TUid aType)
	{
	const TInt idx = FindRegistration(aControl);
	if(IsValidIndex(idx)) // previously registered! update. 
		{
		iRegistered[idx]->SetUid(aType);
		iRegistered[idx]->SetType(CRegisteredControl::EDrawItemControl);
		}
	else 
		{
		if(CRegisteredControl* regctrl = new CRegisteredControl(aControl,aType))
			{
			if(KErrNone != iRegistered.Append(regctrl)) 
				{
				//Failed to add, probably due to memory constraints. Fail silently without registring.
				delete regctrl;
				}
			}
		}	
	} 
	         
void CGfxTransEffect::BeginDrawItem(const CCoeControl */*aControl*/, TUint /*aId*/, TUid /*aType*/,TRect &/*aDrawRect*/, const TRect */*aFromRect*/, const TRect */*aToRect*/)
	{
	// Will be implemented later
	}
	
void CGfxTransEffect::EndDrawItem(const CCoeControl */*aControl*/)
	{
	// Will be implemented later
	}
//---------------------------------
// Full screen effects
//---------------------------------
void CGfxTransEffect::BeginFullScreen(TUint aAction, const TRect &aEffectArea)
	{
	iAdapter->BeginFullScreen(aAction, aEffectArea);
	}
	
void CGfxTransEffect::BeginFullScreen(TUint aAction, const TRect &aEffectArea, TUint aType, const TDesC8& aParams)
	{
	iAdapter->BeginFullScreen(aAction, aEffectArea, aType, aParams);
	}
	
void CGfxTransEffect::EndFullScreen()
	{
	iAdapter->EndFullScreen();
	}
	
void CGfxTransEffect::AbortFullScreen()
	{
	iAdapter->AbortFullScreen();
	}
	
	
	
//
// Internal functions
//
//---------------------------------
// Registration handling
//---------------------------------
TInt CGfxTransEffect::FindRegistration(const CCoeControl * aControl) const
	{
	const TInt count = iRegistered.Count();
	for(TInt i=0; i<count; i++)
		{
		if(aControl == iRegistered[i]->Control())
			{
			return i;
			}
		}
	return KErrNotFound;
	}
	
TInt CGfxTransEffect::FindRegistration(TVwsViewId const &aViewId) const
	{
	const TInt count = iRegistered.Count();
	for(TInt i=0; i<count; i++)
		{
		if(aViewId == iRegistered[i]->ViewId())
			{
			return i;
			}
		}
	return KErrNotFound;
	}

//---------------------------------
// Fallback
//---------------------------------
void CGfxTransEffect::Fallback(const CCoeControl * aKey)
	{
	iAdapter->HandleClientState(MGfxTransAdapter::EFallback, aKey, 0);
	aKey->DrawNow();
	}

//---------------------------------
// Transition Handle
//---------------------------------
TInt CGfxTransEffect::CreateTransitionHandle()
	{
	if(iCreateHandle == 0)
		iCreateHandle = 1;
	iCreateHandle++;
	return iCreateHandle;
	}

//---------------------------------
// MGfxTransDataProvider 
//---------------------------------
void CGfxTransEffect::TransitionPolicyUpdate(TControlPolicy* aPolicy)
	{
	iPolicyHandler->UpdatePolicy(aPolicy->iId, aPolicy->iAction, aPolicy->iPolicy);
	delete aPolicy;
	}
	
void CGfxTransEffect::TransitionFinished(TInt aHandle)
	{
	TInt idx = iInTransition.Find(aHandle);
	if(IsValidIndex(idx))
		{
		//remove from intransition list
		CTransitionControl *transcontrol = iInTransition[idx];
		iInTransition.Remove(idx);
		CRegisteredControl *regcontrol = transcontrol->RegControl();
		// save callback data
		TUint action = transcontrol->Action();
		const CCoeControl *control = regcontrol->Control();
		// delete data and reset remotegc
		delete transcontrol;
		if(regcontrol->InTransitionCount() == 0)
			{
			if(!(regcontrol->Registered()))
				{
				TInt regidx = iRegistered.Find(regcontrol);
				if(IsValidIndex(regidx))
					{
					iRegistered.Remove(regidx);
					}
				delete regcontrol;
				}
			else 
				{
				control->DrawNow();
				}
			}
		if(iObserver)
			{
			iObserver->TransitionFinished(control, action);
			}
		}	
	}
	
TInt CGfxTransEffect::GetTransitionData(TInt aHandle, const CTransitionData*& aTransData)
	{
	//try to find in active stack
	TInt idx = iActiveStack.Find(aHandle);
	if(IsValidIndex(idx))
		{
		iActiveStack[idx]->GetTransitionData(aTransData);
		return KErrNone;
		}
	//try to find in InTransition stack
	idx = iInTransition.Find(aHandle);
	if(IsValidIndex(idx))
		{
		iInTransition[idx]->GetTransitionData(aTransData);
		return KErrNone;
		}
	// not found
	return KErrNotFound;
	}
	
void CGfxTransEffect::ClearAllPolicies()
	{
	iPolicyHandler->SetTransitionPolicies(NULL, 0);
	}

//---------------------------------
// MTransitionControlObserver
//---------------------------------
void CGfxTransEffect::ParticipantUpdated(CTransitionControl *aTransControl, CTransitionParticipant *aParticipant, 
										RWsGraphicMsgBuf* aCommandBuffer, const TRect& aDrawRect, const TRect& aBoundingRect)
	{
	
	iAdapter->HandleParticpantUpdate(aTransControl->Handle(), aParticipant->Data(), aCommandBuffer, aDrawRect, aBoundingRect);
	}
	
