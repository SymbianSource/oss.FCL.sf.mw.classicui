// Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
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

/**
 @file
 @internalComponent - Internal Symbian test code 
*/



#ifndef __ACTIVEWAIT_H__
#define __ACTIVEWAIT_H__

#include "e32std.h"
#include "e32base.h"

class CActiveWait : public CActive
	{
public:
	static CActiveWait* NewL();
	~CActiveWait();
	void Wait(TInt aDelay);
	// From CActive:
	void RunL();
	void DoCancel();
	TInt RunError(TInt aError);
protected:
	CActiveWait();
	void ConstructL();
protected:
	RTimer iTimer;
	TTime iFromTime;
	};
	
#endif //__ACTIVEWAIT_H__
