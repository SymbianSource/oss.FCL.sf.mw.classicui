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
#include "AknExtendedFaderColorSchemeWatcher.h"

CAknExtendedFaderColorSchemeWatcher::CAknExtendedFaderColorSchemeWatcher(MAknExtendedFaderColorSchemeObserver& aObserver)
: CActive(EPriorityStandard), iObserver(aObserver)
	{
	}

CAknExtendedFaderColorSchemeWatcher::~CAknExtendedFaderColorSchemeWatcher()
	{
	// Cancel active object notifications
	Cancel();
	
	iColorSchemeProperty.Close();
	}
	
CAknExtendedFaderColorSchemeWatcher* CAknExtendedFaderColorSchemeWatcher::NewL(MAknExtendedFaderColorSchemeObserver& aObserver)
	{
	CAknExtendedFaderColorSchemeWatcher* self = new (ELeave) CAknExtendedFaderColorSchemeWatcher(aObserver);
	
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(); // self
	
	return self;
	}
	
void CAknExtendedFaderColorSchemeWatcher::ConstructL()
	{
	// Add AO to active scheduler
	CActiveScheduler::Add(this);
	
	// Attach & subscribe to startup property
	User::LeaveIfError(iColorSchemeProperty.Attach(KPSUidAvkonInternal, KAknFadeColorHandle));
		
	// Subscribe to property changes
	iColorSchemeProperty.Subscribe(iStatus);
	
	// Set AO active
	SetActive();
	
	// Get current value (if possible) and notify observer
	DoColorSchemeChanged();
	}
	
void CAknExtendedFaderColorSchemeWatcher::RunL()
	{
	DoColorSchemeChanged();
	
	// Resubscribe
	iColorSchemeProperty.Subscribe(iStatus);
	SetActive(); 
	}

void CAknExtendedFaderColorSchemeWatcher::DoColorSchemeChanged()
	{
	// Get color scheme from P&S and provide it to the observer
	TInt newColor, blackMap, whiteMap;
	
	// Try to get color data
	TInt err1 = iColorSchemeProperty.Get(newColor);
	TInt err2 = RProperty::Get(KPSUidAvkonInternal, KAknFadeBlackMapHandle, blackMap);
	TInt err3 = RProperty::Get(KPSUidAvkonInternal, KAknFadeWhiteMapHandle, whiteMap);
	
	if(err1==KErrNone && err2==KErrNone && err3==KErrNone)
		{
		iObserver.ColorSchemeChanged((TUint32)newColor, TUint8(blackMap), TUint8(whiteMap));
		}
	}

void CAknExtendedFaderColorSchemeWatcher::DoCancel()
	{
	iColorSchemeProperty.Cancel();
	}
