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

#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <animationmixins.h>

class TAnimationConfig;

/** Pure virtual base class for animations.

This defines an abstracted interface between a client application and an
animation.  Most of the implementation details are handled by an animator
plugin.  The source of the animation data and its interpretation are usually
handled by a data provider.

@see CAnimationDataProvider
@see CAnimator
@see MAnimationObserver
@publishedAll
@released*/
class CAnimation : public CBase
	{
public:
	/** Causes the animation to start, at the first time step or logical
	equivalent.  If the animation is already running, it rewinds.
	@see TAnimationConfig
	@param aConfig Specifies run time attributes of the animation.*/
	virtual void Start(const TAnimationConfig& aConfig) = 0;
	/** Causes the animation to stop, and rewinds to the first frame.*/
	virtual void Stop() = 0;
	/** Causes the animation to stop, but without rewinding.*/
	virtual void Pause() = 0;
	/** Causes a paused animation to continue from where it left off.*/
	virtual void Resume() = 0;
	/** Puts an animation on hold, which is similar to pause, but keeps
	track of the time steps passing and catches up when resumed.  This
	can be used to temporarily cease processing an animation without it
	getting out of step with others.*/
	virtual void Hold() = 0;
	/** Resumes a held animation.*/
	virtual void Unhold() = 0;
	/** Sets the coordinates of the animation.  This generally refers
	to the top left corner of the total area the animation covers.
	@param aPoint The new coordinates of the animation (usually the top left
	corner)*/
	virtual void SetPosition(const TPoint& aPoint) = 0;
	/** Causes whatever ticker this animation provides to its animator to
	be frozen untill a corresponding call to unfreeze.
	
	You should not normally need to call this function.
	@see Unfreeze()*/
	virtual void Freeze() = 0;
	/** Causes whatever ticker this animation provides to its animator to
	be unfrozen.
	
	You should not normally need to call this function.
	@see Freeze()*/	
	virtual void Unfreeze() = 0;
	};

#endif //__ANIMATION_H__
