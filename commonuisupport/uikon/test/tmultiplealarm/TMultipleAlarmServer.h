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

#ifndef __TMULTIPLEALARMSERVER_H
#define __TMULTIPLEALARMSERVER_H

#include <test/testexecuteserverbase.h>

/**
Standard TEF server implementation.
*/

class CTMultipleAlarmServer : public CTestServer
	{
public:
	static CTMultipleAlarmServer* NewL();
	virtual CTestStep* CreateTestStep(const TDesC& aStepName);
	};

#endif // __TMULTIPLEALARMSERVER_H
