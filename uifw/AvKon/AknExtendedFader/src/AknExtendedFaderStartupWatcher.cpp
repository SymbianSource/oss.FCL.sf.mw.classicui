/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:
*
*/
#include <e32base.h>
#include "AknExtendedFaderStartupWatcher.h"

CAknExtendedFaderStartupWatcher::CAknExtendedFaderStartupWatcher(MAknExtendedFaderStartupObserver& aObserver)
: CActive(EPriorityStandard), iObserver(aObserver)
	{
	}

CAknExtendedFaderStartupWatcher::~CAknExtendedFaderStartupWatcher()
	{
	// Cancel active object notifications
	Cancel();
	}
	
CAknExtendedFaderStartupWatcher* CAknExtendedFaderStartupWatcher::NewL(MAknExtendedFaderStartupObserver& aObserver)
	{
	CAknExtendedFaderStartupWatcher* self = new (ELeave) CAknExtendedFaderStartupWatcher(aObserver);
	
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(); // self
	
	return self;
	}
	
void CAknExtendedFaderStartupWatcher::ConstructL()
	{
	// Add AO to active scheduler
	CActiveScheduler::Add(this);
	
	// Attach & subscribe to startup property
	User::LeaveIfError(iProperty.Attach(KPSUidStartup, KPSGlobalSystemState));
	iProperty.Subscribe(iStatus);

	// Set AO active
	SetActive();
	
	// Get current value (if possible) and notify observer
	TInt value;
	if(iProperty.Get(value)==KErrNone)
		{
		iObserver.GlobalSystemStateChangedL(static_cast<TPSGlobalSystemState>(value));
		}
			
	
	}
	
void CAknExtendedFaderStartupWatcher::RunL()
	{
	if(iStatus==KErrNone)
		{
		TInt value;
		if(iProperty.Get(value)==KErrNone)
			{
			iObserver.GlobalSystemStateChangedL(static_cast<TPSGlobalSystemState>(value));
			}
		}
	
	// Resubscribe
	iProperty.Subscribe(iStatus);
	SetActive(); 
	}
	
void CAknExtendedFaderStartupWatcher::DoCancel()
	{
	iProperty.Cancel();
	}
