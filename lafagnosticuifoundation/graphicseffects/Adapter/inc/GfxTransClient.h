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

#ifndef _GFXTRANSCLIENT_H_
#define _GFXTRANSCLIENT_H_

#include <gfxtranseffect/gfxtransdatatype.h>

/**
this interface is given to the transition engine on contruction.
It is then to be used to retrieve information about transitions the client has gathered.
It is also used to signal the client.
 
@publishedPartner
@released
*/
class MGfxTransClient
	{
public:
	/**
	 Callback called by adapter when a new policy arrives.
	 @param aPolicy the newly arrived policy. The client takes ownership of the pointer passed.
	 */
	virtual void TransitionPolicyUpdate(TControlPolicy* aPolicy) = 0;

	/**
	 resets policies all to its default, ENotSupported.
	 */
	virtual void ClearAllPolicies() = 0;

	/**
	 Callback, called by adapter when a transition has stopped animating.
	 @param aHandle handle for the transition that finished.
	 */
	virtual void TransitionFinished(TInt aHandle) = 0;

	/**
	 Used by adapter to get transition data from the client.
	 @param aHandle handle for the transition to get the data for.
	 @param aTransData on return contains a pointer to the transition data. Does not transfer ownership.
	 */
	virtual TInt GetTransitionData(TInt aHandle, const CTransitionData*& aTransData) = 0;
	};
	
#endif