// Copyright (c) 2008-2009 Nokia Corporation and/or its subsidiary(-ies).
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


#include "AnimationTestServer.h"

#include <ecom/ecom.h>

#include "e32test.h"
#include "TFrames.h"
#include "TBasic.h"
#include "TSynch.h"
#include "TOomStep.h"
#include "TCustomStep.h"
#include "TMng.h"

_LIT(KServerName, "AnimationTestServer");

class CAnimationScheduler : public CActiveScheduler
	{
public:
	void Error(TInt aError) const;
	};
	
void CAnimationScheduler::Error(TInt /*aError*/) const
	{
	};

//
// TestServer implementation:
//
CAnimationTestServer* CAnimationTestServer::NewL()
	{
	CAnimationTestServer * self = new (ELeave) CAnimationTestServer();
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}
	
CTestStep* CAnimationTestServer::CreateTestStep(const TDesC& aStepName)
	{
	CTestStep* testStep = NULL;

	if (aStepName == KBasicStep)
		testStep = new CBasic;
	else if (aStepName == KFramesStep)
		testStep = new CFrames;
	else if (aStepName == KSynchStep)
		testStep = new CSynch;
	else if (aStepName == KOomStep)
		testStep = new COomStep;
	else if (aStepName == KCustomStep)
		testStep = new CCustomStep;
	else if (aStepName == KMngStep)
		testStep = new CMng;
	
	return testStep;
	}

CAnimationTestServer::CAnimationTestServer()
	{
	}
	
CAnimationTestServer::~CAnimationTestServer()
	{
	}
	
void CAnimationTestServer::ConstructL()
	{
	CTestServer::ConstructL(KServerName);
	}

//
// Entry functions:
//
LOCAL_C void MainL()
	{
	// Active scheduler:
	CAnimationScheduler* Scheduler = new (ELeave) CAnimationScheduler;
	CleanupStack::PushL(Scheduler);
	CActiveScheduler::Install(Scheduler);

	// Create test server:
	CAnimationTestServer* server = NULL;
	TRAPD(err,server = CAnimationTestServer::NewL());
	CleanupStack::PushL(server);
	// Run tests:
	if(!err)
		{
		RProcess::Rendezvous(KErrNone);
		CActiveScheduler::Start();
		}
	
	// Finish:
	CleanupStack::PopAndDestroy(2, Scheduler);
	}

GLDEF_C TInt E32Main()
	{
	CTrapCleanup* cleanup = CTrapCleanup::New();
	if (!cleanup)
		{
		return KErrNoMemory;
		}

	TInt err = KErrNone;
	TRAP_IGNORE(MainL());

	delete cleanup;
    return err;
	}
