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

#if !defined(__TDISABLEEXITCHECKS_STEP_H__)
#define __TDISABLEEXITCHECKS_STEP_H__

#include <coecntrl.h>
#include <test/testexecutestepbase.h>
#include "appfwk_test_AppUi.h"

_LIT(KTDisableExitChecksStep,"TDisableExitChecks");
_LIT(KExeName,"z:\\sys\\bin\\disableexitchecksapp.exe");

class CTDisableExitChecksStep : public CTmsTestStep
	{
public:
	CTDisableExitChecksStep();
	~CTDisableExitChecksStep();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CEikonEnv* aCoe);
	};

class CTDisableExitChecksAppUi : public CTestAppUi
    {
public:
	CTDisableExitChecksAppUi(CTmsTestStep* aStep);
	~CTDisableExitChecksAppUi();
	void StartProcessL(const TDesC8& aTailEnd);
	void TestDisableShutDownChecks();
public:
	void ConstructL();
private:
	void RunTestStepL(TInt aStepNum);
    };

#endif
