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

#ifndef _TRANSITIONPARTICIPANT_H_
#define _TRANSITIONPARTICIPANT_H_

#include <coecntrl.h>

#include "GfxTransDataType.h"
#include "TransitionControl.h"
#include <graphics/remotegc.h>


class CTransitionControl;

/**
A participant in a transition.
@internalTechnology
*/
NONSHARABLE_CLASS(CTransitionParticipant) : public CBase,
											public MCommandBufferObserver
	{
public:	
	enum TCaptureState 
		{
		ENoCapture = 0x0,
		EBeginCapture = 0x1,
		EEndCapture = 0x2
		};
	enum TCaptureType
		{
		EDeep,
		EShallow,
		ERect
		};
	enum TCoordinateRef
		{
		EWindowOwning,
		EScreen
		};
	static CTransitionParticipant* New(	const CCoeControl* aKey,
										CTransitionControl* aTransControl,
										TUint aFlags);
	~CTransitionParticipant();
	//Capture
	TInt CaptureBegin(const CCoeControl* aControl, TCaptureType aCaptureType, TInt aZDepth);
	TInt CaptureEnd(const CCoeControl* aControl, TCaptureType aCaptureType, TInt aZDepth);
	inline TCaptureState CaptureState();
	inline TBool HaveImageCapture();
	//demark
	void SetBeginDemarcation(TRect& aBeginRect, TCoordinateRef aCoordRef = CTransitionParticipant::EWindowOwning);
	void SetEndDemarcation(TRect& aBeginRect, TCoordinateRef aCoordRef = CTransitionParticipant::EWindowOwning);
	void ModifyCoordinates(TPoint& aBeginRef, TPoint& aEndRef);
	//hints
	inline void Invalidate();
	inline void SetFlags(TUint aFlags);
	inline void SetLayerType(TUid aLayerType);
	inline TUint Flags();
	//getters
	inline TBool Invalidated();
	inline const CCoeControl* Control();
	inline const CParticipantData* Data();
	//MCommandBufferObserver
	inline void SetListenForUpdates(TBool aListen);
	void CommandBufferUpdated(const TRect& aDrawRect, const TRect& aBoundingRect);
    inline CRemoteGc* RemoteGc();
private:
	//construct
	CTransitionParticipant(CTransitionControl* aTransControl);
	//data
	TCoordinateRef iCoordRefBegin;
	TCoordinateRef iCoordRefEnd;
	TCaptureState iCaptureState;
	CRemoteGc* iRemoteGc;
	CParticipantData* iData;
	CTransitionControl* iTransControl;
	//hints
	TBool iInvalidated;
	TBool iCaptureEndCalled;
	TBool iInCapture;
	TBool iCommandsReceived;
	TBool iCapturedGc;
	TBool iListensForUpdates;
	};

// inlines

CRemoteGc* CTransitionParticipant::RemoteGc()
    {
    return iRemoteGc;
    }

CTransitionParticipant::TCaptureState CTransitionParticipant::CaptureState()
	{
	return iCaptureState;
	}

void CTransitionParticipant::Invalidate()
	{
	iInvalidated = ETrue;
	}
	
TBool CTransitionParticipant::Invalidated()
	{
	return iInvalidated;
	}

void CTransitionParticipant::SetFlags(TUint aFlags)
	{
	iData->iFlags = aFlags;
	}

void CTransitionParticipant::SetLayerType(TUid aLayerType)
	{
	iData->iLayerType = aLayerType;
	}

TUint CTransitionParticipant::Flags()
	{
	return iData->iFlags;
	}

TBool CTransitionParticipant::HaveImageCapture()
	{
	return (iData->iBeginCapture || iData->iEndCapture);
	}

const CCoeControl* CTransitionParticipant::Control()
	{
	return iData->iKey;
	}
	
const CParticipantData* CTransitionParticipant::Data()
	{
	return iData;
	}

void CTransitionParticipant::SetListenForUpdates(TBool aListen)
	{
	iListensForUpdates = aListen;
	}
#endif //_TRANSITIONPARTICIPANT_H_

