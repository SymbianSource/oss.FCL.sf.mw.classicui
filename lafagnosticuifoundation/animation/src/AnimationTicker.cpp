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

#include "AnimationTicker.h"

#include <e32std.h>

#include "AnimationMixins.h"

/**
Two stage constructor.

After construction, the ticker is already active.

Creates a new CAnimationTicker with the specified time period in microseconds.
The time period aTickLength must be greater than 0 otherwise the caller will be panicked. See CPeriodic for the panic code raised.

@see MAnimationTickee
@see CPeriodic
@param aTickLength The resolution of the timer.
@return The new object
*/
EXPORT_C CAnimationTicker* CAnimationTicker::NewL(TTimeIntervalMicroSeconds32 aTickLength)
	{
	CAnimationTicker* self = new (ELeave) CAnimationTicker;
	CleanupStack::PushL(self);
	self->ConstructL(aTickLength);
	CleanupStack::Pop(self);
	return self;
	}

/** Destructor.*/
EXPORT_C CAnimationTicker::~CAnimationTicker()
	{
	delete iPeriodic;
	iTickees.Reset();
	}
	
CAnimationTicker::CAnimationTicker()
	{
	}

static TInt OnTickCb(TAny* self)
	{
	TRAPD(err, static_cast<CAnimationTicker*>(self)->OnTick());
	return err;
	}

void CAnimationTicker::ConstructL(TTimeIntervalMicroSeconds32 aTickLength)
	{
	iTickLength = aTickLength;
	}
	
void CAnimationTicker::StartTickingL()
	{
	if(!iPeriodic)
		{
		iPeriodic = CPeriodic::NewL(EPriorityLess);
		TCallBack callback(OnTickCb, this);
		iPeriodic->Start(iTickLength, iTickLength, callback);
		}
	}
	
void CAnimationTicker::StopTicking()
	{
	delete iPeriodic;
	iPeriodic = 0;
	}
	
void CAnimationTicker::OnTick()
	{
	if (iFreeze == 0)
		{
		for (TInt tt = iTickees.Count() - 1; tt >= 0; --tt)
			{
			iTickees[tt]->Tick();
			}
		}
	}

/**
Adds a new tickee to the internal list.  All added tickees will be called
once every tick.
@param aTickee An object derived from MAnimationTickee
@return KErrNone or one of the other system wide error codes
*/
EXPORT_C TInt CAnimationTicker::Add(MAnimationTickee* aTickee)
	{
	TInt err = iTickees.Append(aTickee);
	if (err == KErrNone)
		{
		TRAP(err,StartTickingL())
		};
	return err;
	}

/**
Removes a tickee from the internal list.  Attempting to remove a tickee
that has not been added is not an error, and has no effect.
@param aTickee An object added using Add()
@return KErrNone or KErrNotFound
*/
EXPORT_C TInt CAnimationTicker::Remove(MAnimationTickee* aTickee)
	{
	TInt entry = iTickees.Find(aTickee);
	if (entry >= 0)
		{
		iTickees.Remove(entry);
		if (iTickees.Count() < 1)
			StopTicking();
		return KErrNone;
		}
	return KErrNotFound;
	}

/**
Freezes this ticker 

This allows asynchronous actions to be taken for more than one animation without the
animations getting out of synch with each other.

It is possible to freeze multiple times.  Doing so will increment a reference counter
and the ticker will not be unfrozen until every freeze has been matched by a call
to unfreeze.

You should not need to call this function unless you are writing a new animation type.
@see CAnimationTicker::Unfreeze()
*/
EXPORT_C void CAnimationTicker::Freeze()
	{
	++iFreeze;
	}

/**
Under some circumstances it may be necessary to handle unfreezing directly,
instead of through the item on the cleanupstack.  In this case the cleanup item
should be popped and then Unfreeze called when appropriate.

You should not need to call this function unless you are writing a new animation type.
@see CAnimationTicker::Freeze()
*/
EXPORT_C void CAnimationTicker::Unfreeze()
	{
	if(iFreeze > 0)
		--iFreeze;
	}

/** Reserved for future use */
EXPORT_C void CAnimationTicker::CAnimationTicker_Reserved1() {}

/** Reserved for future use */
EXPORT_C void CAnimationTicker::CAnimationTicker_Reserved2() {}
