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

#include "gfxtransadapterstub.h"

//
// DLL interface.
//
EXPORT_C MGfxTransAdapter* MGfxTransAdapter::CreateL(MGfxTransClient* aClient)
	{
		CGfxTransAdapterStub* adapter = new (ELeave) CGfxTransAdapterStub(aClient);
		CleanupStack::PushL(adapter);
		adapter->ConstructL();
		CleanupStack::Pop(adapter);
		return adapter;
	}

EXPORT_C void MGfxTransAdapter::Destroy(MGfxTransAdapter* aAdapter)
	{
	delete static_cast<CGfxTransAdapterStub*>(aAdapter);
	}

//
// Construction/Destruction
//
CGfxTransAdapterStub::CGfxTransAdapterStub(MGfxTransClient* aClient) :
	iClient(aClient)
	{
	}
	
CGfxTransAdapterStub::~CGfxTransAdapterStub()
	{
	}
	
void CGfxTransAdapterStub::ConstructL()
	{
	}

//
// MGfxTransAdapter implementation
//
TInt CGfxTransAdapterStub::HandleClientState(TClientState /*aState*/, const CCoeControl* /* aKey*/, TInt /*aHandle*/)
	{
	//Adapter should respond to the state here if it needs to.
	//Most adapters will probably not be interested in most states.
	
	//aKey can be NULL if no control is available for that state and aHandle can be 0 if its not valid.
	//(like global abort)
	
	//You can also request the CTransitionData here, if you got a valid handle. 
	//Be aware though that it might not yet be complete. 
	//(For example, in EPostBeginCapture, the begin state has just been captured, but 
	// the endstate has not yet been.)
	
	return KErrNone;
	}
	
TBool CGfxTransAdapterStub::IsActive()
	{
	return ETrue;
	}
	
TControlPolicy* CGfxTransAdapterStub::GetTransitionPolicies(TInt& /* aCount*/)
	{
	return NULL;
	}
	
void CGfxTransAdapterStub::StartTransition(TInt aHandle)
	{
	//Get information about the transition collected by the client like this:
	const CTransitionData* transition;
	iClient->GetTransitionData(aHandle,transition);
	
	//Check gfxtransdatatype.h to see what information is available through CTransitionData.
	
	
	// A start transition call from the client MUST always be followed by a transitionfinished callback to it.
	// If not getting it, the client can't know when to clean up the transition information.
	iClient->TransitionFinished(aHandle); 
	}

void CGfxTransAdapterStub::NotifyExternalState(TInt /*aState*/, const TDesC8* /* aArg */)
	{
	//This one is called if the new NotifyExternalState API function is called.
	// anything passed in from the API gets through to here unmodified.
	}
	
void CGfxTransAdapterStub::HandleParticpantUpdate(TInt /*aHandle*/, const CParticipantData* /*aParticipant*/, RWsGraphicMsgBuf* /*aCommandBuffer*/, const TRect& /*aDrawRect*/, const TRect& /*aBoundingRect*/)
	{
	//This function will be called if the client finds a participant has been updated (called drawnow on) 
	//while the transition is animating. 
	//(That is, after End has return, but before the client has got TransitionFinished from the adapter)
	
	//For this stubadapter, this can never happen since all transitions are finished immediatly.
	//A real adapter would though do this in an async way, returning from StartTransition without calling
	//TransitionFinished, and then call this at a later point when the animation has finished.
	}

void CGfxTransAdapterStub::BeginFullScreen(TUint /*aAction*/, const TRect& /*aEffectArea*/)
	{
	}

void CGfxTransAdapterStub::BeginFullScreen(TUint /*aAction*/, const TRect& /*aEffectArea*/, TUint /*aType*/, const TDesC8& /*aParams*/)
	{
	}

void CGfxTransAdapterStub::EndFullScreen()
	{
	}

void CGfxTransAdapterStub::AbortFullScreen()
	{
	}
