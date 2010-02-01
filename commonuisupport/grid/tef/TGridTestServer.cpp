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
// Example file/test code to demonstrate how to develop a TestExecute Server
// Developers should take this project as a template and substitute their own
// code at the __EDIT_ME__ tags.\n
// Secure and non-secure variants.\n
// Secure EKA2 versions will be a simpler xxxServer.exe running in its own process.\n
// Non-secure versions will be xxxServer.Dll and require a thread to be started
// in the process of the client. The client initialises the server by calling the
// one and only ordinal.\n
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code
*/
#include "TGridTestServer.h"
#include "TGlayStep.h"
#include "TGrid0Step.h"
#include "TCoGridStep.h"


_LIT(KServerName,"TGridTestServer");
CTGridTestServer* CTGridTestServer::NewL()
/**
   @return - Instance of the test server
   Same code for Secure and non-secure variants
   Called inside the MainL() function to create and start the
   CTestServer derived server.
 */
	{
	CTGridTestServer * server = new (ELeave) CTGridTestServer();
	CleanupStack::PushL(server);
	// CServer base class call
	server->StartL(KServerName);
	CleanupStack::Pop(server);
	return server;
	}


LOCAL_C void MainL()
/**
    Secure variant.\n
    Much simpler, uses the new Rendezvous() call to sync with the client.\n
*/
	{
#if (defined __DATA_CAGING__)
	RProcess().DataCaging(RProcess::EDataCagingOn);
	RProcess().SecureApi(RProcess::ESecureApiOn);
#endif
	CActiveScheduler* sched=NULL;
	sched=new(ELeave) CActiveScheduler;
	CActiveScheduler::Install(sched);
	CTGridTestServer* server = NULL;
	// Create the CTestServer derived server
	TRAPD(err,server = CTGridTestServer::NewL());
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
/**
    @return - Standard Epoc error code on process exit.\n
 
    Secure variant only.\n
    Process entry point. Called by client using RProcess API.\n
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



CTestStep* CTGridTestServer::CreateTestStep(const TDesC& aStepName)
/**
    @return - A CTestStep derived instance
    Secure and non-secure variants
    Implementation of CTestServer pure virtual
 */
	{
	CTestStep* testStep = NULL;
	// This server creates just one step but create as many as you want
	// They are created "just in time" when the worker thread is created
	if(aStepName == KTGlayStep)
		testStep = new CTGlayStep();
	if(aStepName == KTGrid0Step)
		testStep = new CTGrid0Step();
	if(aStepName == KTCoGridStep)
		testStep = new CTCoGridStep();
	return testStep;
	}
