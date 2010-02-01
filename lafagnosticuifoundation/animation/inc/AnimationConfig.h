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

#ifndef __ANIMATIONCONFIG_H__
#define __ANIMATIONCONFIG_H__

struct TAnimationConfig
/** These are passed to animator objects when an animation is started and
provide some control over the manner in which the animation runs.
@publishedAll
@released*/
	{
	enum TFlags
	/** Flag values used by animator objects when an animation is started that
	provide some control over the manner in which the animation runs. 

	@publishedAll
	@released */
 		{
		/** If set, interpret the iData member as the number of times the
		animation should run before automatically stopping itself.*/
		ELoop				= 0x0001,
		/** If set, the animation will start as soon as it can.  By default,
		animations wait for the data to be completely loaded before starting.*/
		EStartImmediately	= 0x0010,
		/** If set, and ELoop is set, interpret the iData member as a number
		of frames to run through, instead of complete cycles.*/
		ECountFrames		= 0x0020,
		/** By default animations which stop after a number of loops return
		to the first frame.  If this flag is set they stop on the last frame.*/
		EEndOnLastFrame 	= 0x0040,
		};
	/** Set this to a combination of the values in TFlags.*/
	TInt iFlags;
	/** The meaning of this item depends on the value of the iFlags member.*/
	TInt iData;
	};

#endif //__ANIMATIONCONFIG_H__
