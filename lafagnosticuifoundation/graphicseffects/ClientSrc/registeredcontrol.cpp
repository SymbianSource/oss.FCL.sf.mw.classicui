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

#include "RegisteredControl.h"

CRegisteredControl::CRegisteredControl( const CCoeControl* aCoeControl, TUid const & aUid, TBool aNLayered) :
	iType(ECoeControl),
	iUid(aUid),
	iKey(aCoeControl),
	iNLayered(aNLayered),
	iRegistered(ETrue)
	{
	}

CRegisteredControl::CRegisteredControl( const CCoeControl* aCoeControl, TVwsViewId const & aViewId, TUid aUid ) :
	iType(EView),
	iUid(aUid),
	iKey(aCoeControl),
	iViewId(aViewId),
	iRegistered(ETrue)
	{
	}

CRegisteredControl::CRegisteredControl( const CCoeControl* aCoeControl, TUid aUid ) :
	iType(EDrawItemControl),
	iUid(aUid),
	iKey(aCoeControl),
	iRegistered(ETrue)
	{
	}
	
CRegisteredControl::~CRegisteredControl()
	{
	iTransitions.Reset();
	iTransitions.Close();
	}

void CRegisteredControl::ResetTransitions()
	{
	const TInt count = iTransitions.Count();
	for(TInt i = 0; i < count; i++)
		{
		iTransitions[i]->Reset();
		}
	#ifdef _DEBUG
	iTransitions.Compress(); // so that __UHEAP_MARK can be used
	#endif
	}

TInt CRegisteredControl::AddTransition(CTransitionControl *aTransControl)
	{
	return iTransitions.Append(aTransControl);
	}
	
void CRegisteredControl::RemoveTransition(CTransitionControl *aTransControl)
	{
	const TInt count = iTransitions.Count();
	for(TInt i = 0; i < count; i++)
		{
		if(iTransitions[i] == aTransControl)
			{
			iTransitions.Remove(i); //not owning
			#ifdef _DEBUG
			iTransitions.Compress(); // so that __UHEAP_MARK can be used
			#endif
			return;
			}
		}
	}
