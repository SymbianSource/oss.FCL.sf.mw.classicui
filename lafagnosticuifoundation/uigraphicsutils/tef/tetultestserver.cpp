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

#include "tetultestserver.h"
#include "t_textresourceutils.h"
#include "t_addressstringtokenizer.h"
#include "t_phonenumberutils.h"

/**
   @return - Instance of the test server
   Called inside the MainL() function to create and start the
   CTestServer derived server.
 */
CTEtulTestServer* CTEtulTestServer::NewL()
	{
	CTEtulTestServer * server = new (ELeave) CTEtulTestServer();
	CleanupStack::PushL(server);
	// CServer base class call
	TParsePtrC serverName(RProcess().FileName());	
	server->StartL(serverName.Name());
	CleanupStack::Pop(server);
	return server;
	}

/** Secure variant
    Much simpler, uses the new Rendezvous() call to sync with the client
*/
LOCAL_C void MainL()
	{
	CActiveScheduler* sched=NULL;
	sched=new(ELeave) CActiveScheduler;
	CActiveScheduler::Install(sched);
	CTEtulTestServer* server = NULL;
	// Create the CTestServer derived server
	TRAPD(err,server = CTEtulTestServer::NewL());
	if(!err)
		{
		// Sync with the client and enter the active scheduler
		RProcess::Rendezvous(KErrNone);
		sched->Start();
		}
	delete server;
	delete sched;
	}

/*
   @return - Standard Epoc error code on process exit
   Secure variant only
   Process entry point. Called by client using RProcess API
*/
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

/**
   @return - A CTestStep derived instance
   Implementation of CTestServer pure virtual
 */
CTestStep* CTEtulTestServer::CreateTestStep(const TDesC& aStepName)
	{
	CTestStep* testStep = NULL;
	if(aStepName == KT_TextResourceUtilsStep)
		testStep = new CT_TextResourceUtilsStep();
	else if(aStepName == KT_AddressStringTokenizerStep)
		testStep = new CT_AddressStringTokenizerStep();
	else if(aStepName == KT_PhoneNumberUtilsStep)
		testStep = new CT_PhoneNumberUtilsStep();
	return testStep;
	}
