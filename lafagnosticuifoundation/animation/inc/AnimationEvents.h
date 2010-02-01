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

#ifndef __ANIMATIONEVENTS_H__
#define __ANIMATIONEVENTS_H__

/** Generic events which all animation data providers can pass to animators.

An implementation of CAnimation may intercept these and perform additional
processing if necessary.  

Events specific to a particular data type should take values greater than
EAnimationReservedEvents.  Implementations of CAnimation should not intercept
or attempt to act on data type specific events.
@publishedAll
@released */
enum TAnimationEvent
	{
	/** Sent when the data itself has changed and the animator needs to be
	ready to	receive the new values */
	EAnimationDataChanged,
	/** Sent when an error occurs within the data provider and it is unable
	to complete the sending of the animation data */
	EAnimationDataProviderError,
	/** Specifies an upper limit for generic events.  Events larger than this
	are free to use for data type specific information */
	EAnimationReservedEvents = 0xFF
	};

/** Events specific to the "bitmap" data type.  These events are only sent
by data providers dealing with bitmap frame animations, and are only understood
by bitmap animators.
@publishedAll
@released */
enum TBitmapAnimationEvent
	{
	/** This event contains data specifying the bitmaps for a new frame of
	animation */
	EBitmapAnimationNewFrame = EAnimationReservedEvents + 1,
	/** This event indicates that there are no more frames to send */
	EBitmapAnimationComplete,
	};

#endif //__ANIMATIONEVENTS_H__
