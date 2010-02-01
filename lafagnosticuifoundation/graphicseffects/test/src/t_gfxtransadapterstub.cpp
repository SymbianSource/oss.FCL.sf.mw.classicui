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

#include <gfxtranseffect/gfxtranseffect.h>
#include <gfxtranseffect/gfxtransdatatype.h>

#include "t_gfxtransadapterstub.h"

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
	return KErrNone;
	}
	
TBool CGfxTransAdapterStub::IsActive()
	{
	return ETrue;
	}
	
TControlPolicy* CGfxTransAdapterStub::GetTransitionPolicies(TInt&  aCount)
	{
	//Create a policy
    aCount = 1; // we need only one policy
    
    TControlPolicy* policies = new TControlPolicy[aCount];
    policies[0].iId.iUid = 0; // control UID
    policies[0].iAction = GfxTransEffect::ELoseFocus; // action identifier
    policies[0].iPolicy = ESupported;
    
    return policies;
	}
	
void CGfxTransAdapterStub::StartTransition(TInt /* aHandle */)
	{
    // Empty implementation
    // We don't inform client about finishing transition so we 
    // could test deregistering while being in transition
    }

void CGfxTransAdapterStub::NotifyExternalState(TInt /*aState*/, const TDesC8* /* aArg */)
	{
	
	}
	
void CGfxTransAdapterStub::HandleParticpantUpdate(TInt /*aHandle*/, const CParticipantData* /*aParticipant*/, RWsGraphicMsgBuf* /*aCommandBuffer*/, const TRect& /*aDrawRect*/, const TRect& /*aBoundingRect*/)
	{

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
