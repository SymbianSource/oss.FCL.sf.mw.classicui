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
// Non-secure versions will be xxxServer.Dll and require a thread to be started
// in the process of the client. The client initialises the server by calling the
// one and only ordinal.
// 
//

/**
 @file 
 @internalComponent - Internal Symbian test code
*/

#include "TEgulTestServer.h"
#include "T_ColorStep.h"
#include "TBorderstep.h"
#include "T_DigitWidth.h"
#include "TEgulAlignmentStep.h"



_LIT(KServerName,"TEgulTestServer");
CTEgulTestServer* CTEgulTestServer::NewL()
/**
   @return - Instance of the test server
   Same code for Secure and non-secure variants
   Called inside the MainL() function to create and start the
   CTestServer derived server.
 */
	{
	CTEgulTestServer * server = new (ELeave) CTEgulTestServer();
	CleanupStack::PushL(server);
	// CServer base class call
	server->StartL(KServerName);
	CleanupStack::Pop(server);
	return server;
	}


LOCAL_C void MainL()

/** Secure variant
    Much simpler, uses the new Rendezvous() call to sync with the client
*/
	{
#if (defined __DATA_CAGING__)
	RProcess().DataCaging(RProcess::EDataCagingOn);
	RProcess().SecureApi(RProcess::ESecureApiOn);
#endif
	CActiveScheduler* sched=NULL;
	sched=new(ELeave) CActiveScheduler;
	CActiveScheduler::Install(sched);
	CTEgulTestServer* server = NULL;
	// Create the CTestServer derived server
	TRAPD(err,server = CTEgulTestServer::NewL());
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
/*
   @return - Standard Epoc error code on process exit
   Secure variant only
   Process entry point. Called by client using RProcess API
*/
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




CTestStep* CTEgulTestServer::CreateTestStep(const TDesC& aStepName)
/**
   @return - A CTestStep derived instance
   Secure and non-secure variants
   Implementation of CTestServer pure virtual
 */
	{
	CTestStep* testStep = NULL;
	// This server creates just one step but create as many as you want
	// They are created "just in time" when the worker thread is created
	if(aStepName == KT_ColorStep)
		testStep = new CT_ColorStep();
	else if(aStepName == KTBorderStep)
		testStep = new CTBorderStep();
	else if(aStepName == KT_DigitWidth)
		testStep= new CT_DigitWidth();
	else if(aStepName == KTAlignmentStep)
		testStep= new CTAlignmentStep();
	
	return testStep;
	}
