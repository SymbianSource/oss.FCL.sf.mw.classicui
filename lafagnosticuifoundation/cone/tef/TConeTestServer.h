// Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
 @test
 @internalComponent - Internal Symbian test code   
*/

#if (!defined __TCONETEST_SERVER_H__)
#define __TCONETEST_SERVER_H__

#include <test/testexecuteserverbase.h>

enum TConeTestPanic
	{
	EConeTestPanicWrongTest,
	EConeTestWrongLeave,			//The Active Scheduler left with an unexpected code
	EConePanicNoDigitiser          //Pointer event when the configuration has no digitiser
	};


class CTConeTestServer : public CTestServer
	{
public:
	static CTConeTestServer* NewL();
	virtual CTestStep* CreateTestStep(const TDesC& aStepName);
	};


#endif	//__TCONETEST_SERVER_H__

