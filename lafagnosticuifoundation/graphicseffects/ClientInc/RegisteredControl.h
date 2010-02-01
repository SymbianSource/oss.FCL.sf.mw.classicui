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

#ifndef _REGISTEREDCONTROL_H_
#define _REGISTEREDCONTROL_H_

#include <vwsdef.h> // TVwsViewId
#include <e32base.h>
#include "TransitionControl.h"

class CCoeControl;

/**
Implementation of the registered control class

@internalTechnology
*/
NONSHARABLE_CLASS(CRegisteredControl) : public CBase
	{
public:
	enum TType 
		{
		ECoeControl,
		EView,
		EDrawItemControl
		};
	CRegisteredControl( const CCoeControl* aCoeControl, TUid const & aUid, TBool aNLayered);
	CRegisteredControl( const CCoeControl* aCoeControl, TVwsViewId const & aViewId, TUid aUid );
	CRegisteredControl( const CCoeControl* aCoeControl, TUid aUid );
	
	~CRegisteredControl();
	//transitions
	void ResetTransitions();
	TInt AddTransition(CTransitionControl* aTransControl);
	void RemoveTransition(CTransitionControl* aTransControl);
	inline TInt InTransitionCount();
	//inline setters/getters
	inline TUid Uid() const;
	inline TVwsViewId const &ViewId() const;
	inline TType Type() const;
	inline const CCoeControl* Control() const;
	inline TBool IsNLayered() const;
	inline TUint Flags() const;
	inline TBool Registered() const;
	
	inline void SetRegistered(TBool aRegistered);
	inline void SetUid(TUid const & aUid);
	inline void SetViewId(TVwsViewId const & aViewId);
	inline void SetType(TType aType);
	inline void SetControl(const CCoeControl* aControl);
	inline void SetNLayered(TBool aIsNLayered);
	inline void SetFlags(TUint aFlags);
	
private:
	RPointerArray<CTransitionControl> iTransitions; //does not own the ctranscontrols
	TType iType;
	TUid iUid;
	const CCoeControl* iKey;
	TVwsViewId iViewId;		
	TBool iNLayered;
	TBool iRegistered;
	TUint iFlags;
	};

//Inline definitions.

//Getters
TInt CRegisteredControl::InTransitionCount()
	{
	return iTransitions.Count();
	}

TUid CRegisteredControl::Uid() const
	{
	return iUid;
	}
TVwsViewId const & CRegisteredControl::ViewId() const
	{
	return iViewId;
	}
CRegisteredControl::TType CRegisteredControl::Type() const
	{
	return iType;
	}
const CCoeControl* CRegisteredControl::Control() const
	{
	return iKey;
	}
TBool CRegisteredControl::IsNLayered() const
	{
	return iNLayered;
	}
	
TUint CRegisteredControl::Flags() const
	{
	return iFlags;
	}	

TBool CRegisteredControl::Registered() const
	{
	return iRegistered;
	}
		
//Setters

void CRegisteredControl::SetRegistered(TBool aRegistered)
	{
	iRegistered = aRegistered;
	}

void CRegisteredControl::SetUid(TUid const & aUid)
	{
	iUid = aUid;
	}
void CRegisteredControl::SetViewId(TVwsViewId const & aViewId)
	{
	iViewId = aViewId;
	}
void CRegisteredControl::SetType(TType aType)
	{
	iType = aType;
	}
void CRegisteredControl::SetControl(const CCoeControl* aControl)
	{
	iKey = aControl;
	}
void CRegisteredControl::SetNLayered(TBool aIsNLayered)
	{
	iNLayered = aIsNLayered;
	}

void CRegisteredControl::SetFlags(TUint aFlags)
	{
	iFlags = aFlags;
	}

#endif
