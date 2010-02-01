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


#if (!defined __UIKTESTSERVER_H__)
#define __UIKTESTSERVER_H__

#include <test/testexecutestepbase.h>
#include <test/testexecuteserverbase.h>
#include <test/testexecutelog.h>

class CUiktestServer : public CTestServer
	{
public:
	static CUiktestServer* NewL();
	virtual CTestStep* CreateTestStep(const TDesC& aStepName);
	};
	
#endif


