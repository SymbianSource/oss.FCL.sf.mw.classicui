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

#include "AnimationGroup.h"

#include "AnimationTls.h"
#include "AnimationTicker.h"

/**
Two stage constructor.

Creates an empty animation group.

@return The new object
*/
EXPORT_C CAnimationGroup* CAnimationGroup::NewL()
	{
	CAnimationGroup * self = new (ELeave) CAnimationGroup;
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}

/** Destructor.*/
EXPORT_C CAnimationGroup::~CAnimationGroup()
	{
	while(iFreezeCount > 0)
		CAnimationGroup::Unfreeze();
	iAnimations.Reset();
	if(iTls)
		{
		iTls->Close();
		iTls = NULL;
		}
	}

CAnimationGroup::CAnimationGroup()
	{
	}

void CAnimationGroup::ConstructL()
	{
	iTls = CAnimationTls::NewL();
	}

/**
Returns a reference to the array of animations being grouped.

It is intended for animations to be added to and removed from this array directly.
@return the array of animations currently held in the group.
*/
EXPORT_C const RPointerArray<CAnimation>& CAnimationGroup::Animations() const
	{
	return iAnimations;
	}
	
/**
Returns a reference to the array of animations being grouped.

It is intended for animations to be added to and removed from this array directly.
@return the array of animations currently held in the group.
*/
EXPORT_C RPointerArray<CAnimation>& CAnimationGroup::Animations()
	{
	return iAnimations;
	}

/** Starts all of the animations.

@param aConfig Specifies run time attributes of the animation */
void CAnimationGroup::Start(const TAnimationConfig& aConfig)
	{
	Freeze();
	for (TInt ii = iAnimations.Count() - 1; ii >= 0; --ii)
		{
		iAnimations[ii]->Start(aConfig);
		}
	Unfreeze();
	}
	
/** Stops all of the animations.*/
void CAnimationGroup::Stop()
	{
	Freeze();
	for (TInt ii = iAnimations.Count() - 1; ii >= 0; --ii)
		{
		iAnimations[ii]->Stop();
		}
	Unfreeze();
	}
	
/** Pauses all of the animations.*/
void CAnimationGroup::Pause()
	{
	Freeze();
	for (TInt ii = iAnimations.Count() - 1; ii >= 0; --ii)
		{
		iAnimations[ii]->Pause();
		}
	Unfreeze();
	}
	
/** Resumes all of the animations.*/
void CAnimationGroup::Resume()
	{
	Freeze();
	for (TInt ii = iAnimations.Count() - 1; ii >= 0; --ii)
		{
		iAnimations[ii]->Resume();
		}
	Unfreeze();
	}
	
/** Hold all of the animations.*/
void CAnimationGroup::Hold()
	{
	Freeze();
	for (TInt ii = iAnimations.Count() - 1; ii >= 0; --ii)
		{
		iAnimations[ii]->Hold();
		}
	Unfreeze();
	}
	
/** Unhold all of the animations.*/
void CAnimationGroup::Unhold()
	{
	Freeze();
	for (TInt ii = iAnimations.Count() - 1; ii >= 0; --ii)
		{
		iAnimations[ii]->Unhold();
		}
	Unfreeze();
	}
	
/**
Set the position of all the animations.

Note that this will cause all the animations to be in the same place, which is
unlikely to be a desired effect. It is implemented here for completeness.

@param aPoint The new location of the top left corner of the animation, 
relative to the window in which it is to be drawn */
void CAnimationGroup::SetPosition(const TPoint& aPoint)
	{
	Freeze();
	for (TInt ii = iAnimations.Count() - 1; ii >= 0; --ii)
		{
		iAnimations[ii]->SetPosition(aPoint);
		}
	Unfreeze();
	}
	
/** Freeze all of the animations.*/
void CAnimationGroup::Freeze()
	{
	for (TInt ii = iAnimations.Count() - 1; ii >= 0; --ii)
		{
		iAnimations[ii]->Freeze();
		}
	++iFreezeCount;
	}
	
/** Unfreeze all of the animations.*/
void CAnimationGroup::Unfreeze()
	{
	for (TInt ii = iAnimations.Count() - 1; ii >= 0; --ii)
		{
		iAnimations[ii]->Unfreeze();
		}
	--iFreezeCount;
	}
	
/** Reserved for future use */
EXPORT_C void CAnimationGroup::CAnimationGroup_Reserved1() 
	{
	}

/** Reserved for future use */
EXPORT_C void CAnimationGroup::CAnimationGroup_Reserved2()
	{
	}
