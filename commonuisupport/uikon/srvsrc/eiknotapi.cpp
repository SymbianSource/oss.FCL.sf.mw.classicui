// Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#include "eiknotapi.h"
#include "EIKNFYSV.H"
#include <uiklaf/private/lafnotcap.h>

/** Constructor for MEikSrvNotifierManager */
EXPORT_C MEikSrvNotifierManager::MEikSrvNotifierManager()
	{
	}

/** Reserved for future use */	
EXPORT_C void MEikSrvNotifierManager::MEikSrvNotifierManager_Reserved1()
	{
	}

/** Reserved for future use */	
EXPORT_C void MEikSrvNotifierManager::MEikSrvNotifierManager_Reserved2()
	{
	}


//
// MEikSrvNotifierBase2
//

void MEikSrvNotifierBase2::SetManager(MEikSrvNotifierManager* aManager)
	{
	iManager = aManager;
	}

EXPORT_C MEikSrvNotifierBase2::MEikSrvNotifierBase2()
	{}

EXPORT_C MEikSrvNotifierBase2::~MEikSrvNotifierBase2()
	{}

/** Reserved for future use */	
EXPORT_C void MEikSrvNotifierBase2::MEikSrvNotifierBase2_Reserved_2()
	{}

EXPORT_C void MEikSrvNotifierBase2::UpdateL(const TDesC8& /*aBuffer*/, TInt /*aReplySlot*/, const RMessagePtr2& /*aMessage*/)
	{}

/** Handles a screen change event.

This function is called by the notifier manager, but only if the notifier 
can handle a change to the screen device, i.e. if a call to NotifierCapabilites() 
reports that the EScreenDeviceChangeSupported flag is set.

The default implementation is empty.

@param aEvent The Uid representing the event. */
EXPORT_C void MEikSrvNotifierBase2::HandleSystemEventL(TUid /*aEvent*/)
	{
	}

/** Gets notifier capabilities.

Calls the LAF implemented function.
   
@see LafNotifierCapabilities::NotifierCapabilities() */
EXPORT_C TInt MEikSrvNotifierBase2::NotifierCapabilites()
   	{
 	//Calling the LAF implemented NotifierCapabilities function to get the capability.
 	TInt capabilities = LafNotifierCapabilities::NotifierCapabilities();
   	return capabilities;
   	}
