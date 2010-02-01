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
// GFXTRANSEFFECT.CPP
// 
//

#include "PolicyHandler.h"
#include "GfxTransUtils.h"

//---------------------------------
// construct/destruct  
//---------------------------------

CPolicyHandler::CPolicyHandler() 
	{
	
	}
	 
CPolicyHandler::~CPolicyHandler() 
	{
	iPolicies.ResetAndDestroy();
	iPolicies.Close();
	}


//---------------------------------
// get/set policies 
//---------------------------------
 
TPolicy CPolicyHandler::GetPolicy(TUid aUid, TUint aAction) 
	{
	TInt cpIdx = FindControlPolicy(aUid);
	if(IsValidIndex(cpIdx))
		{
		TInt apIdx = FindActionPolicy(iPolicies[cpIdx], aAction);
		if(IsValidIndex(apIdx))
			{
			return iPolicies[cpIdx]->iActions[apIdx].iPolicy;
			}
		}
	return ENotSupported;
	}
	 
void CPolicyHandler::UpdatePolicy(TUid aUid, TUint aAction, TPolicy aPolicy) 
	{
	TInt const cpIdx = FindControlPolicy(aUid);
	if(IsValidIndex(cpIdx))
		{
		CControlPolicy *policy = iPolicies[cpIdx];
		
		TInt apIdx = FindActionPolicy(policy, aAction);
		if(IsValidIndex(apIdx))
			{
			if(aPolicy == ENotSupported)
				{ //remove current existing policy
				policy->iActions.Remove(apIdx);
				if(policy->iActions.Count() == 0)
					{
					iPolicies.Remove(cpIdx);
					delete policy;
					}
				}
			else 
				{
				//change the policy
				policy->iActions[apIdx].iPolicy = aPolicy;
				}
			return;
			}
		if(aPolicy == ENotSupported)
			{
			//already not existing so do nothing
			return;
			}
		else 
			{
			//create the action policy
			TActionPolicy actionPolicy;
			actionPolicy.iAction = aAction;
			actionPolicy.iPolicy = aPolicy;
			policy->iActions.Append(actionPolicy); //nothing to do if we fail
			return;
			}
		}
	if(aPolicy == ENotSupported)
		{
		//already not existing so do nothing
		return;
		}
	else 
		{
		//Create the policy
		CControlPolicy* policy = new CControlPolicy();
		if(!policy)
			return; //nothing to do if we fail
		policy->iUid = aUid;
		TActionPolicy actionPolicy;
		actionPolicy.iAction = aAction;
		actionPolicy.iPolicy = aPolicy;
		if(KErrNone != policy->iActions.Append(actionPolicy))
			{
			delete policy;
			return;
			}
		if(KErrNone != iPolicies.Append(policy))
			{
			delete policy;
			return; //nothing to do if we fail
			}
		}
	}
		
void CPolicyHandler::SetTransitionPolicies(TControlPolicy* aPolicies, TInt aNum)
	{
	iPolicies.ResetAndDestroy();
	for(TInt i = 0;i < aNum; i++)
		{
		UpdatePolicy(aPolicies[i].iId, aPolicies[i].iAction, aPolicies[i].iPolicy);
		}
	delete aPolicies;
	}



//---------------------------------
// find functions  
//---------------------------------
TInt CPolicyHandler::FindControlPolicy(TUid aUid)
	{
	TInt count = iPolicies.Count();
	for(TInt i = 0; i < count; i++)
		{
		if(iPolicies[i]->iUid == aUid)
			{
			return i;
			}
		}
	return KErrNotFound;
	}
	
TInt CPolicyHandler::FindActionPolicy(CControlPolicy* aControlPolicy, TUint aAction)
	{
	TInt count = aControlPolicy->iActions.Count();
	for(TInt i = 0; i < count; i++)
		{
		if(aControlPolicy->iActions[i].iAction == aAction)
			{
			return i;
			}
		}
	return KErrNotFound;
	}
	

