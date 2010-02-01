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

#ifndef __GFXTRANSEFFECT_IMPL_H__
#define __GFXTRANSEFFECT_IMPL_H__


#include <coemain.h> // CBase etc
#include <e32cmn.h> //RPointerArray

#include "GfxTransEffect.h"
#include "GfxTransAdapter.h"

#include "TransitionControl.h"
#include "RegisteredControl.h"
#include "PolicyHandler.h"

/**
Implementation of the GfxTransEffect API, one instance is createed per thread
using transitions.

@internalTechnology
*/	
NONSHARABLE_CLASS(CGfxTransEffect) : public CCoeStatic,
					  public MGfxTransClient,
					  MTransitionControlObserver
	{
public:
	// construction/destruction
	CGfxTransEffect();
	~CGfxTransEffect();
	TInt Construct();
	static CGfxTransEffect* Static(const CCoeControl* aControl);
	static CGfxTransEffect* StaticNoCreate(const CCoeControl * aControl);
	static CGfxTransEffect* Static();
	static CGfxTransEffect* StaticNoCreate();
	
	// registration
	void Register(const CCoeControl* aKey,const TVwsViewId &aView,TUid aType);
	void Register(const CCoeControl* aKey,TUid aType,TBool aNLayered);
	TBool IsRegistered(const CCoeControl* aKey);
	void Deregister(const CCoeControl* aKey);
	// stack
	void Begin(const CCoeControl* aKey,TUint aAction);
	void BeginLC(const CCoeControl* aKey,TUint aAction);
	void End(const CCoeControl* aKey);
	void NotifyExternalState(TInt aState, const TDesC8* aArg);
	inline TBool InTransition() const;
	void Abort(const CCoeControl* aKey);
	void AbortCleanup(const CCoeControl* aControl);
	void Abort();
	// hints
	void SetHints(const CCoeControl* aControl,TUint aFlags);
	TUint GetHints(const CCoeControl* aControl);
	void SetHints(const CCoeControl* aControl,TUid aLayerType);
	void Invalidate(const CCoeControl* aControl);
	// demarcation
	void SetDemarcation(const CCoeControl* aControl,TPoint const &aDemarcation);
	void SetDemarcation(TVwsViewId const &aView,TPoint const &aDemarcation);
	void SetDemarcation(const CCoeControl* aControl,TRect const &aDemarcation);
	void SetDemarcation(TVwsViewId const &aView,TRect const &aDemarcation);
	void SetDemarcation(const CCoeControl* aControl,const CCoeControl* aSrc,TRect const &aDemarcation);
	void SetDemarcation(TVwsViewId const &aView,const CCoeControl* aSrc,TRect const &aDemarcation);
	//Engine state
	void Enable();
	void Disable();
	inline TBool IsEnabled() const;
	//API additions
	void SetEndDemarcation(const CCoeControl* aControl, const TRect& aDemarcation);
	void SetBeginDemarcation(const CCoeControl* aControl, const TRect& aDemarcation);
	TInt BeginGroup(); //returns an id for the group.
	void EndGroup(TInt aGroupId);
	void SetTransitionData(TUint aType, const TDesC8& aData);
	void SetTransitionObserver(MGfxTransEffectObserver* aObserver);
	//Draw item controls
	void RegisterDrawItemControl(const CCoeControl* aControl, TUid aType);          
	void BeginDrawItem(const CCoeControl* aControl, TUint aId, TUid aType,TRect &aDrawRect,const TRect* aFromRect, const TRect* aToRect);
	void EndDrawItem(const CCoeControl*aControl);
	//full screen effects
	void BeginFullScreen(TUint aAction, const TRect &aEffectArea);
	void BeginFullScreen(TUint aAction, const TRect &aEffectArea, TUint aType, const TDesC8& aParams);
	void EndFullScreen();
	void AbortFullScreen();

	//MGfxTransClient
	void TransitionPolicyUpdate(TControlPolicy* aPolicy);
	void TransitionFinished(TInt aHandle);
	TInt GetTransitionData(TInt aHandle, const CTransitionData*& aTransData);
	void ClearAllPolicies();
	
	//MTransitionControlObserver
	void ParticipantUpdated(CTransitionControl* aTransControl, CTransitionParticipant* aParticipant, 
							RWsGraphicMsgBuf* aCommandBuffer, const TRect& aDrawRect, const TRect& aBoundingRect);
	
private:
	//UID
	static const TUid KTransEffectUid;
	// policies
	CPolicyHandler*iPolicyHandler;
	// registration
	RPointerArray<CRegisteredControl> iRegistered;
	TInt FindRegistration(const CCoeControl* aControl) const;
	TInt FindRegistration(TVwsViewId const &aViewId) const;
	// fallback
	void Fallback(const CCoeControl* aKey);
	//transition handle
	TInt CreateTransitionHandle();
	TInt iCreateHandle;
	// stack
	RActiveStack iActiveStack;
	// in transition
	RInTransitionList iInTransition;
	
	//Engine Adapter
	MGfxTransAdapter* iAdapter;
	
	// other
	TBool iEnabled;
	//observer
	MGfxTransEffectObserver* iObserver; //not owning
	};

/*** inlines ***/
	
TBool CGfxTransEffect::InTransition() const
	{
	//"InTransition" in API means between begin-end.
	return iActiveStack.Count();
	}

TBool CGfxTransEffect::IsEnabled() const
	{
	return iEnabled;
	}

#endif // __GFXTRANSEFFECT_IMPL_H__
