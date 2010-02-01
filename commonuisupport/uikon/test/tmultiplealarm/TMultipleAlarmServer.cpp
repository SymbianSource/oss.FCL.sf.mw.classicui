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

#include "TMultipleAlarmServer.h"
#include "TMultipleAlarmStep.h"

_LIT(KServerName, "TMultipleAlarmServer");

CTMultipleAlarmServer* CTMultipleAlarmServer::NewL()
	{
	CTMultipleAlarmServer* server = new (ELeave) CTMultipleAlarmServer;
	CleanupStack::PushL(server);
	server->StartL(KServerName);
	CleanupStack::Pop(server);
	
	return server;
	}
	
CTestStep* CTMultipleAlarmServer::CreateTestStep(const TDesC& aStepName)
	{

	if (aStepName == KTMultipleAlarm)
		{
		return new CTMultipleAlarmStep;
		}
	return 0;
	}

static void MainL()
	{
	CActiveScheduler* sched = new(ELeave) CActiveScheduler;
	CActiveScheduler::Install(sched);
	
	CTMultipleAlarmServer* server = 0;
	TRAPD(err,server = CTMultipleAlarmServer::NewL());
	
	if(!err)
		{
		RProcess::Rendezvous(KErrNone);
		CActiveScheduler::Start();
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
