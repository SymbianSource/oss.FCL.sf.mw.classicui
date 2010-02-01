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
#ifndef AKNEXTENDEDFADERSTARTUPWATCHER_H__
#define AKNEXTENDEDFADERSTARTUPWATCHER_H__

#include <e32property.h>
#include <startupdomainpskeys.h>

class MAknExtendedFaderStartupObserver
	{
public:
	virtual void GlobalSystemStateChangedL(TPSGlobalSystemState aState) = 0;
	};

class CAknExtendedFaderStartupWatcher : public CActive
	{
public:
	~CAknExtendedFaderStartupWatcher();
	
	static CAknExtendedFaderStartupWatcher* NewL(MAknExtendedFaderStartupObserver& aObserver);

protected: // Overrides	

	void RunL();
	void DoCancel();
	
private:
	CAknExtendedFaderStartupWatcher(MAknExtendedFaderStartupObserver& aObserver);
	void ConstructL();
	
private:
	RProperty iProperty;
	
	MAknExtendedFaderStartupObserver &iObserver;
	};

#endif
