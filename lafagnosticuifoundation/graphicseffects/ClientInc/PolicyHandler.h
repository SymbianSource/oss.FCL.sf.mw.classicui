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

#ifndef _POLICYHANDLER_H_
#define _POLICYHANDLER_H_

#include "GfxTransDataType.h"

/**
Implementation of the policy handler

@internalTechnology
*/
NONSHARABLE_CLASS(CPolicyHandler) : public CBase
{
public:
	CPolicyHandler();
	~CPolicyHandler();
	TPolicy GetPolicy(TUid aUid, TUint aAction);
	void UpdatePolicy(TUid aUid, TUint aAction, TPolicy aPolicy);
	void SetTransitionPolicies(TControlPolicy* aPolicies, TInt aNum);
private: 
	class TActionPolicy
		{
		public:
		TUint iAction;
		TPolicy iPolicy;
		};
	class CControlPolicy
		{
		public:
		~CControlPolicy()
			{
			iActions.Reset();
			iActions.Close();
			}
		RArray<TActionPolicy> iActions;
		TUid iUid;
		};
	RPointerArray<CControlPolicy> iPolicies;
	TInt FindControlPolicy(TUid aUid);
	TInt FindActionPolicy(CControlPolicy* aControlPolicy, TUint aAction);
	
};

#endif //_POLICYHANDLER_H_