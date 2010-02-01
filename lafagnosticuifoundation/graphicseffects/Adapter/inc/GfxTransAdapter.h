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

#ifndef _GFXTRANSADAPTERADAPTER_H_
#define _GFXTRANSADAPTERADAPTER_H_

#include <gfxtranseffect/gfxtransclient.h>

//class CTransitionControl;

/**
This is the abstract interface of a transition adapter.
The transition engine vendor implements this interface to serve transitions.
The implementation is a static interface dll with two exports,
at ordinal 1, MGfxTransAdapter::CreateL() to create an adapter adapter and
at ordinal 2, MGfxTransAdapter::Destroy() to destroy it.
 
@publishedPartner
@released
*/
class MGfxTransAdapter 
	{
public: //DLL Interface
	IMPORT_C static MGfxTransAdapter* CreateL(MGfxTransClient* aProvider);
	IMPORT_C static void Destroy(MGfxTransAdapter* aAdapter);
public: //Adapter Interface.
	enum TClientState 
		{
		EPreBeginCapture,
		EPostBeginCapture,
		EPreEndCapture,
		EPostEndCapture,
		EAbort,
		EGlobalAbort, 
		EBeginGroup,
		EEndGroup,
		EFallback,
		};
	/**
	 Handles a specific client state.
	 @param aState a client state to handle
	 @param aKey the registered control, NULL if not valid
	 @param aHandle handle to the transition in progress, 0 if not valid.
	 */
	virtual TInt HandleClientState(TClientState aState, const CCoeControl* aKey, TInt aHandle) = 0; 

	/**
	Handles an update to a transition participant during transition animation.
	Is called by the client if new draw commands arrive after End, but before MGfxTransClient::TransitionFinished() 
	has been called.	
	@param aHandle handle to the transition.
	@param aParticipantId the id of the participant that was updated.
	@param aDrawRect
	@param aBoundingRect
	*/
	virtual void HandleParticpantUpdate(TInt aHandle, const CParticipantData* aParticipant, RWsGraphicMsgBuf* aCommandBuffer, const TRect& aDrawRect, const TRect& aBoundingRect) = 0;

	/**
	
	 @return ETrue if the adapter is ready to serve transitions.
	 */
	virtual TBool IsActive() = 0;

	/**
	 Returns the current set of transition policies.
	 The engine might choose to return NULL and push all policies through MGfxTransClient::TransitionPolicyUpdate()
	 @param aCount on return, contains the number of policies returned.
	 @return an array of TControlPolicy pointers. caller takes responsibility for cleanup.
	 */
	virtual TControlPolicy* GetTransitionPolicies(TInt &aCount) = 0;
	
	/**
	A notify of external state change.
	Same as the API function, is passed straight from the client.
	@param aState the user supplied state
	@param aArg optional arguments or NULL if not used.
	*/
	virtual void NotifyExternalState(TInt aState, const TDesC8* aArg) = 0;
	
	/**
	 Requests a transition finished event. 
	 This MUST result in a later call to MGfxTransClient::TransitionFinished(). 
	 It can be called immediatly if adapter does not need to handle this.
	 */
	virtual void StartTransition(TInt aHandle) = 0;
	
	/**
	 Tells the engine to start a full screen effect.
	 @param aAction Effect identifier
	 @param aEffectArea the part of the framebuffer to be affected
	 */
	virtual void BeginFullScreen(TUint aAction, const TRect &aEffectArea) = 0;
	/**
	 Tells the engine to start a full screen effect.
	 @param aAction Effect identifier
	 @param aEffectArea the part of the framebuffer to be affected
	 @param aType the type of the parameters.
	 @param aParam the parameters.
	*/
	virtual void BeginFullScreen(TUint aAction, const TRect &aEffectArea, TUint aType, const TDesC8& aParams) = 0;
	
	/**
	Informs the engine of the endpoint of a fullscreen effect.
	*/
	virtual void EndFullScreen() = 0;
	
	/**
	Tells the engine to abort a fullscreen effect.
	*/
	virtual void AbortFullScreen() = 0;
	};
	

#endif

