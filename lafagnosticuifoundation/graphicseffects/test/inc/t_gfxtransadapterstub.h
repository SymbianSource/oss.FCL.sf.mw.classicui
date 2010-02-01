// Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies).
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

/**
 @file
 @test
 @internalComponent - Internal Symbian test code
*/

#ifndef _T_GFXTRANSADAPTERSTUB_H_
#define _T_GFXTRANSADAPTERSTUB_H_

#include <e32base.h>

#include <gfxtranseffect/gfxtransadapter.h>

class CCoeControl;

/** 
A class containing the basic, stub methods for an engine adapter.  The
adapter sits between the client and the engine, and will need to be customised
for each engine.

This is a fake implementation of transition engine for testing purposes.
It's goal is to create a correct TControlPolicy so that transition could be started.
This code was created to test the fix for defect INC109405: Problem with sequential Gfxtranseffect registrations 
*/
NONSHARABLE_CLASS(CGfxTransAdapterStub) : public CBase, public MGfxTransAdapter
	{
private:
	CGfxTransAdapterStub(MGfxTransClient* aClient);
	~CGfxTransAdapterStub();
public:
	void ConstructL();
public: //MGfxTransAdapter
	TInt HandleClientState(TClientState aState, const CCoeControl *aKey, TInt aHandle); 
	TBool IsActive();
	TControlPolicy* GetTransitionPolicies(TInt &aCount);
	void StartTransition(TInt aHandle);
	void HandleParticpantUpdate(TInt aHandle, const CParticipantData* aParticipant, RWsGraphicMsgBuf* aCommandBuffer, const TRect& aDrawRect, const TRect& aBoundingRect);
	void BeginFullScreen(TUint aAction, const TRect &aEffectArea);
	void BeginFullScreen(TUint aAction, const TRect &aEffectArea, TUint aType, const TDesC8& aParams);
	void EndFullScreen();
	void AbortFullScreen();
	void NotifyExternalState(TInt aState, const TDesC8* aArg);
private:
	friend class MGfxTransAdapter;
	MGfxTransClient* iClient;
	};

#endif //_T_GFXTRANSADAPTERSTUB_H_

