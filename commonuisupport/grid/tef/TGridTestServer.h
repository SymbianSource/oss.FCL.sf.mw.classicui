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


#if (!defined __TGRIDTEST_SERVER_H__)
#define __TGRIDTEST_SERVER_H__

#include <test/testexecuteserverbase.h>


//! A CTestServer derived class.\n

/** 
  The test server executes all the Grid related tests on grids 
  with definite and indefinite row boundaries, tests appearance 
  of rows,columns and their selections.\n
*/

class CTGridTestServer : public CTestServer
	{
public:
	static CTGridTestServer* NewL();
	virtual CTestStep* CreateTestStep(const TDesC& aStepName);
	};

#endif



