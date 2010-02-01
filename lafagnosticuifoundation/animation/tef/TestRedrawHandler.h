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

#ifndef __TESTREDRAWHANDLER_H__
#define __TESTREDRAWHANDLER_H__

#include <e32base.h>

class RWsSession;

class CTestRedrawHandler : public CActive
	{
public:
	CTestRedrawHandler(RWsSession& aWs);
	virtual ~CTestRedrawHandler();
	void Start();
protected:
	void RunL();
	void DoCancel();
	TInt RunError(TInt aError);
protected:
	RWsSession& iWs;
	};
	
#endif //__TESTREDRAWHANDLER_H__
