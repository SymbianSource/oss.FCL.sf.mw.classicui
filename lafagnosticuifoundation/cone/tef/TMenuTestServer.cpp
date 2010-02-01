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
 

#include "TMenuTestServer.h"
#include "TMenu0Step.h"
#include "TMenu1Step.h"
#include "TVWASTEP.H"


_LIT(KServerName,"TMenuTestServer");


CTMenuTestServer* CTMenuTestServer::NewL()
	{
	CTMenuTestServer * server = new (ELeave) CTMenuTestServer();
	CleanupStack::PushL(server);
	server->StartL(KServerName);
	CleanupStack::Pop(server);
	return server;
	}


LOCAL_C void MainL()
	{
	RProcess().DataCaging(RProcess::EDataCagingOn);
	RProcess().SecureApi(RProcess::ESecureApiOn);
	CActiveScheduler* sched=NULL;
	sched=new(ELeave) CActiveScheduler;
	CActiveScheduler::Install(sched);
	CTMenuTestServer* server = NULL;
	// Create the CTestServer derived server
	TRAPD(err,server = CTMenuTestServer::NewL());
	if(!err)
		{
		// Sync with the client and enter the active scheduler
		RProcess::Rendezvous(KErrNone);
		sched->Start();
		}
	delete server;
	delete sched;
	}

GLDEF_C TInt E32Main()
	{
	__UHEAP_MARK;
	CTrapCleanup* cleanup = CTrapCleanup::New();
	if(cleanup == NULL)
		{
		return KErrNoMemory;
		}
	TRAP_IGNORE(MainL());
	delete cleanup;
	__UHEAP_MARKEND;
	return KErrNone;
    }



CTestStep* CTMenuTestServer::CreateTestStep(const TDesC& aStepName)
	{
	CTestStep* testStep = NULL;

	if(aStepName == KTMenu0Step)
		{
		testStep = new CTMenu0Step();
		}
	if(aStepName == KTMenu1Step)
		{
		testStep = new CTMenu1Step();
		}
	if(aStepName == KTVwaStep)
		{
		testStep = new CTVwaStep();
		}
	return testStep;
	}
