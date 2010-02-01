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

#include "ActiveTestStep.h"
#include <test/appfwk_test_appui.h>

_LIT(KTestDied, "Test step died with errno = %d");

void CActiveTestStepScheduler::Error(TInt aError) const
	{
	iStep->Stop(aError); // Generally this doesn't work, but it's a good place to break
	};

CActiveTestStepLauncher::CActiveTestStepLauncher() :
CActive(EPriorityNormal),
iVerdict(EAbort)
	{
	}
	
CActiveTestStepLauncher::~CActiveTestStepLauncher()
	{
	Cancel();
	}

void CActiveTestStepLauncher::RunL()
	{
	TRAPD(err, iVerdict = iStep->doActiveTestStepL());
	iStep->Stop(err);
	}

void CActiveTestStepLauncher::DoCancel()
	{
	iStep->Stop(KErrCancel);
	}

void CActiveTestStepLauncher::Launch(CActiveTestStep* aStep)
	{
	iStep = aStep;
	CActiveScheduler::Add(this);
	TRequestStatus * status = &iStatus;
	User::RequestComplete(status, KErrNone);
	SetActive();
	}

CActiveTestStep::CActiveTestStep()
	{
	}
	
CActiveTestStep::~CActiveTestStep()
	{
	if(iLauncher)
		iLauncher->Cancel();
	delete iLauncher;
	delete iScheduler;
	}
	
TVerdict CActiveTestStep::doTestStepPreambleL()
	{
	SetTestStepResult(EPass);
	return TestStepResult();
	}
	
TVerdict CActiveTestStep::doTestStepL()
	{
	if(TestStepResult() == EPass)
		{
		iScheduler = new (ELeave) CActiveTestStepScheduler;
		CActiveScheduler::Install(iScheduler);
		
		iLauncher = new CActiveTestStepLauncher;
		iLauncher->Launch(this);
		iScheduler->Start();
		
		SetTestStepResult(iLauncher->TestStepResult());
		}
	return TestStepResult();
	}
	
TVerdict CActiveTestStep::doTestStepPostambleL()
	{
	return TestStepResult();
	}

void CActiveTestStep::Stop(TInt aError)
	{
	if(aError != KErrNone)
		{
		ERR_PRINTF2(KTestDied, aError);
		iLauncher->SetTestStepResult(EFail);
		}
	iScheduler->Stop();
	}
