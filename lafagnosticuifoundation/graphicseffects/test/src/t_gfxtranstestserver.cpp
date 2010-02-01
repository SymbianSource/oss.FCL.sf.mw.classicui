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

#include <coecntrl.h>

#include "appfwk_test_AppUi.h"
#include "t_gfxtranstestServer.h"
#include "t_gfxtranseffect.h"


CGfxTransTestServer* CGfxTransTestServer::NewL()
/**
   @return - Instance of the test server
   Called inside the MainL() function to create and start the
   CTestServer derived server.
 */
	{
	CGfxTransTestServer * server = new (ELeave) CGfxTransTestServer();
	CleanupStack::PushL(server);
	// CServer base class call
	TParsePtrC serverName(RProcess().FileName());	
	server->StartL(serverName.Name());
	CleanupStack::Pop(server);
	return server;
	}


CTestStep* CGfxTransTestServer::CreateTestStep(const TDesC& aStepName)
/**
   @return - A CTestStep derived instance
   Secure and non-secure variants
   Implementation of CTestServer pure virtual
 */
	{
	CTestStep* testStep = NULL;

	// This server creates just one step but create as many as you want
	// They are created "just in time" when the worker thread is created
	if (aStepName == KTestGfxTransEffect)
        {
        testStep = new CTestGfxTransEffect();
        }
	return testStep;
	}


LOCAL_C void MainL()
/**
   Much simpler, uses the new Rendezvous() call to sync with the client
 */
	{
	CActiveScheduler* sched=NULL;
	sched=new(ELeave) CActiveScheduler;
	CActiveScheduler::Install(sched);

	CGfxTransTestServer* server = NULL;
	// Create the CTestServer derived server
	TRAPD(err,server = CGfxTransTestServer::NewL());
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
   @return - Standard Epoc error code on exit
 */
	{
	CTrapCleanup* cleanup = CTrapCleanup::New();
	if(cleanup == NULL)
		{
		return KErrNoMemory;
		}
	TRAP_IGNORE(MainL());
	delete cleanup;
	return KErrNone;
    }
