// Copyright (c) 2004-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#include "Animator.h"
#include "AnimationMixins.h"

#include <ecom/ecomresolverparams.h>
#include <ecom/ecom.h>

/** Locates and constructs an animator.

The MAnimationDrawer passed as an argument returns a string through the
function AnimatorDataType.  If a matching animator plugin can be found then
it will be loaded and constructed.

@param aRenderer The MAnimationDrawer implementation for the animator to use.
@return The new animator.*/
EXPORT_C CAnimator* CAnimator::NewL(MAnimationDrawer* aRenderer)
	{
	__ASSERT_ALWAYS(aRenderer != NULL, User::Leave(KErrArgument));
    TEComResolverParams resolverParams; 
    resolverParams.SetDataType(aRenderer->AnimatorDataType());
    TAny* ptr = REComSession::CreateImplementationL(KAnimatorInterfaceUid, _FOFF(CAnimator,iDtor_ID_Key), aRenderer, resolverParams);
    return reinterpret_cast<CAnimator*>(ptr);
	}

/** Destructor.*/
EXPORT_C CAnimator::~CAnimator()
	{
	REComSession::DestroyedImplementation(iDtor_ID_Key);
	}
