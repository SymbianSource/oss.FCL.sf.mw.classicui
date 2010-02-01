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
#ifndef AKNEXTENDEDFADERCOLORSCHEMEWATCHER_H__
#define AKNEXTENDEDFADERCOLORSCHEMEWATCHER_H__

#include <e32property.h>
#include "avkoninternalpskeys.h"

class MAknExtendedFaderColorSchemeObserver
	{
public:
	virtual void ColorSchemeChanged(const TUint32& aNewColor, const TUint8& aNewBlackMap, const TUint8& aNewWhiteMap) = 0;
	};

class CAknExtendedFaderColorSchemeWatcher : public CActive
	{
public:
	~CAknExtendedFaderColorSchemeWatcher();
	
	static CAknExtendedFaderColorSchemeWatcher* NewL(MAknExtendedFaderColorSchemeObserver& aObserver);

protected: // Overrides	

	void RunL();
	void DoCancel();
	
private:
	CAknExtendedFaderColorSchemeWatcher(MAknExtendedFaderColorSchemeObserver& aObserver);
	void ConstructL();
	
	void DoColorSchemeChanged();
	
private:
	RProperty iColorSchemeProperty;
	
	MAknExtendedFaderColorSchemeObserver &iObserver;
	};

#endif
