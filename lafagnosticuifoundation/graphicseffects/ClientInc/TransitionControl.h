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

#ifndef _TRANSITIONCONTROL_H
#define _TRANSITIONCONTROL_H

#include <e32base.h>
#include <w32std.h>
#include <vwsdef.h>

#include "TransitionParticipant.h"
#include "GfxTransDataType.h"


class CRegisteredControl;
class CTransitionControl;
class CCoeControl;
class CTransitionParticipant;

/**
stack for controls that has got a begin, but not yet an end.

@internalTechnology
*/
class RActiveStack : public RPointerArray<CTransitionControl>
	{
public:
	TInt Push(CTransitionControl* aTransControl);
	TInt PushLC(CTransitionControl* aTransControl);
	CTransitionControl* Pop();
	CTransitionControl* Top();

	TInt ClearAbove(TInt aIndex);
	TInt Find(const CCoeControl* aControl) const;
	TInt Find(const CRegisteredControl* aRegControl) const;
	TInt FindView(TVwsViewId const &aView) const;
	TInt Find(TInt aHandle) const;
private:
	static void CleanupOperation(TAny* aAny);
	};

/**
list of controls currently transitioning/animating.
*/
class RInTransitionList : public RPointerArray<CTransitionControl>
	{
public:
	TInt Append(CTransitionControl* aTransControl);
	void Remove(TInt aIndex);

	TInt Find(const CRegisteredControl* aRegControl) const;
	TInt Find(TInt aHandle) const;
	};

class MTransitionControlObserver
	{
public:
	virtual void ParticipantUpdated(CTransitionControl* aTransControl, CTransitionParticipant* aParticipant, 
									RWsGraphicMsgBuf* aCommandBuffer, const TRect& aDrawRect, const TRect& aBoundingRect) = 0;
	};

/**
keeps the data defining a specific transition instance.
*/
NONSHARABLE_CLASS(CTransitionControl) : public CBase
	{
public:
	friend class RActiveStack;

	static CTransitionControl* New(	CRegisteredControl* aRegControl, MTransitionControlObserver* aObserver,
									TUint aAction, TPolicy aPolicy, TInt aHandle);
	~CTransitionControl();
	void Reset();									
	//getters
	inline CRegisteredControl* RegControl() const;
	inline TUint Action() const;
	inline TInt Handle() const;
	inline TBool Failed() const;
	inline TPolicy Policy() const;
	inline CWsScreenDevice* ScreenDevice();
	
	//capture
	void CaptureBegin();
	void CaptureEnd();
	//demarcation
	void DoSetDemarcation(const CCoeControl* aKey, TRect aDemarcation);
	void DoSetDemarcation(const CCoeControl* aKey, const CCoeControl* aSrc, TRect aDemarcation);
	void DoSetBeginDemarcation(const CCoeControl* aKey, TRect aDemarcation);
	void DoSetEndDemarcation(const CCoeControl* aKey, TRect aDemarcation);
	// hints
	void Invalidate(const CCoeControl* aKey);
	void SetHints(const CCoeControl* aKey, TUid aLayerType);
	void SetHints(const CCoeControl* aKey, TUint aFlags);
	TUint GetHints(const CCoeControl* aKey);
	//
	void SetTransitionData(TUint aType, const TDesC8& aData);
	void GetTransitionData(const CTransitionData*& aTransData);
	TInt GetUpdatedRegion(RRegion& aRegion);
	
	//participant callback
	void ParticipantUpdated(CTransitionParticipant* aParticipant, RWsGraphicMsgBuf* aCommandBuffer,
							const TRect& aDrawRect, const TRect& aBoundingRect);
	void SetListenForUpdates(TBool aListen);
private:
	MTransitionControlObserver* iObserver;
	//private functions
	CTransitionControl(CRegisteredControl* aRegControl, MTransitionControlObserver* aObserver, TInt aHandle);
	void Fallback();
	TInt FindParticipant(const CCoeControl* aKey);
	CTransitionParticipant* CreateSubControl(const CCoeControl* aKey, TUint aFlags);
	//data
	CTransitionData* iData;
	CRegisteredControl* iRegControl; //not owning
	CTransitionParticipant* iBaseControl;
	RPointerArray<CTransitionParticipant> iSubControls;
	
	//transition info
	TInt iHandle;
	
	CWsScreenDevice* iScreenDevice; //not owning
	friend class RActiveStack;
	friend class RInTransitionList;
	//helpers
	TBool iHasBeginWOPos;
	TBool iOnCleanupStack;
};

//getters/setters.
CRegisteredControl* CTransitionControl::RegControl() const 
	{
	return iRegControl;
	}
TUint CTransitionControl::Action() const
	{
	return iData->iAction;
	}

TInt CTransitionControl::Handle() const
	{
	return iHandle;
	}
	
TBool CTransitionControl::Failed() const
	{
	return iData->iFailed;
	}

TPolicy CTransitionControl::Policy() const
	{
	return iData->iPolicy;
	}

CWsScreenDevice* CTransitionControl::ScreenDevice()
	{
	return iScreenDevice;
	}

#endif

