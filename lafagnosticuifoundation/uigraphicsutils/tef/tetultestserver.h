// Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies).
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


#if (!defined __TETULTEST_SERVER_H__)
#define __TETULTEST_SERVER_H__

#include <test/testexecuteserverbase.h>
#include <test/testexecutelog.h>

class CTEtulTestServer : public CTestServer
	{
public:
	static CTEtulTestServer* NewL();
	virtual CTestStep* CreateTestStep(const TDesC& aStepName);
	};

#endif


