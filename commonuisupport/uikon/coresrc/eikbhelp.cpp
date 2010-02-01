// Copyright (c) 2000-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#include <eikbhelp.h>
#include "eikmischelp.h"

//
// MEikTriggeredHelp
//

EXPORT_C void MEikTriggeredHelp::MEikTriggeredHelp_Reserved_1()
	{}

EXPORT_C void MEikTriggeredHelp::MEikTriggeredHelp_Reserved_2()
	{}


//
// EikBubbleHelp
//

EXPORT_C void EikBubbleHelp::Trigger(const TDesC& aDes,const TRect& aRect,TInt aHandle)
	// static
/** Starts bubble help displaying the help message text descriptor after a fixed 
time delay.

The bubble help is not displayed if it is cancelled during the waiting period.

Replaces any outstanding request to show a help message. The screen rectangle 
aRect is used to anchor the bubble help. An optional handle aHandle can be 
supplied to identify the trigger request. This allows a client to later enquire 
if the bubble help is being displayed due to this request.

@param aDes The help message text descriptor.
@param aRect The rectangle used to anchor the bubble help.
@param aHandle The handle used to identify this trigger request. */
	{
	CEikBubbleHelp::Trigger(aDes,aRect,aHandle);
	}

EXPORT_C void EikBubbleHelp::Cancel()
	// static
/** Cancels any outstanding help message whether being displayed or waiting to be 
displayed. */
	{
	CEikBubbleHelp::Cancel();
	}

EXPORT_C void EikBubbleHelp::CancelTrigger()
	// static
/** Cancels any outstanding help message that is waiting to be displayed. */
	{
	CEikBubbleHelp::CancelTrigger();
	}

EXPORT_C TBool EikBubbleHelp::IsDisplaying(TInt aHandle)
	// static
/** Tests if bubble help is currently being displayed.

@param aHandle ETrue if bubble help is currently being displayed due to the 
trigger request identified by the handle aHandle. An optional handle aHandle 
can be supplied to identify the trigger request. */
	{
	return CEikBubbleHelp::IsDisplaying(aHandle);
	}


//
// CEikBubbleHelp
//

void CEikBubbleHelp::Trigger(const TDesC& aDes,const TRect& aRect,TInt aHandle)
	// static
	{
	CEikBubbleHelp* self=CEikBubbleHelp::Self();
	if (self && self->iHelp)
		{
		self->iHelp->TriggerHelp(aDes,aRect,aHandle);
		}
	}

void CEikBubbleHelp::Cancel()
	// static
	{
	CEikBubbleHelp* self=CEikBubbleHelp::Self();
	if (self && self->iHelp)
		{
		self->iHelp->CancelHelp();
		}
	}

void CEikBubbleHelp::CancelTrigger()
	// static
	{
	CEikBubbleHelp* self=CEikBubbleHelp::Self();
	if (self && self->iHelp)
		{
		self->iHelp->CancelHelpTrigger();
		}
	}

TBool CEikBubbleHelp::IsDisplaying(TInt aHandle)
	// static
	{
	CEikBubbleHelp* self=CEikBubbleHelp::Self();
	if (self && self->iHelp)
		{
		return self->iHelp->IsDisplayingHelp(aHandle);
		}
	else
		{
		return EFalse;
		}
	}

//
// Sets the bubble help implementation for this application to aTriggeredHelp. Should be called
// when initializing the environment for the application.
//
EXPORT_C void CEikBubbleHelp::SetTriggeredHelpL(MEikTriggeredHelp* aTriggeredHelp)
	// static
	{
	CEikBubbleHelp* self=CEikBubbleHelp::Self();
	if (!self)
		{
		self=new(ELeave) CEikBubbleHelp(); // CCoeEnv takes ownership immediately
		}
	self->iHelp=aTriggeredHelp;
	}

CEikBubbleHelp::~CEikBubbleHelp()
	{
	if(iHelp)
		iHelp->Release();
	}


