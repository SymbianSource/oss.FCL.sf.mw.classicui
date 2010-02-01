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
// The test server drives tests related to Cone APIs featuring
// Creating controls, Component-control interface, Background drawing, object
// provider mechanism, Screen Drawing- Offscreen drawing erc.\n
// 
//

/**
 @file
 @test
 @internalComponent - Internal Symbian test code 
*/


#include "TConeTestServer.h"
#include "TCone0Step.h"
#include "TCone1Step.h"
#include "TCone2Step.h"
#include "TCone3Step.h"
#include "TCone4StepExe.h"
#include "TConeErrorMsgStep.h"
#include "TConeHelpTextStep.h"
#include "TConeBackground.h"
#include "TCone5Step.h"
#include "TCone6Step.h"
#include "TCone7Step.h"
#include "TConeInvalidate.h"
#include "TConeTransition.h"
#include "TConeTransparency.h"
#include "TConeZoomFont.h"
#include "TConeVisibility.h"
#include "tconecoedatastoragestep.h"
#include "tconecoecntssstep.h"
#include "tconeresourceloader.h"
#include "tconestateobs.h"
#include "TConeMultiPtrStep.h"
#include "tconemultiptrcompoundstep.h"
#include "TMultipleScreensStep.h"
#include "tconeevents.h"


_LIT(KServerName,"TConeTestServer");


CTConeTestServer* CTConeTestServer::NewL()
	{
	CTConeTestServer * server = new (ELeave) CTConeTestServer();
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

	CTConeTestServer* server = NULL;
	TRAPD(err,server = CTConeTestServer::NewL());
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
	CTrapCleanup* cleanup = CTrapCleanup::New();
	if(cleanup == NULL)
		{
		return KErrNoMemory;
		}
	TRAP_IGNORE(MainL());

	delete cleanup;
	return KErrNone;
    }


CTestStep* CTConeTestServer::CreateTestStep(const TDesC& aStepName)
	{
	CTestStep* testStep = NULL;
	if (aStepName==KTConeErrorMsgStep)
		{
		testStep = new CTConeErrorMsgStep();
		}
	else if (aStepName==KTConeHelpTextStep)
		{
		testStep = new CTConeHelpTextStep();
		}
	else if (aStepName==KTCone0Step)
		{
		testStep = new CTCone0Step();
		}
	else if (aStepName==KTCone1Step)
		{
		testStep = new CTCone1Step();
		}
	else if (aStepName==KTCone2Step)
		{
		testStep = new CTCone2Step();
		}
	else if (aStepName==KTCone3Step)
		{
		testStep = new CTCone3Step();
		}
	else if (aStepName==KTCone4StepExe)
		{
		testStep = new CTCone4StepExe();
		}
	else if (aStepName==KTBackgroundStep)
		{
		testStep = new CTConeBackgroundStep();
		}
	else if (aStepName==KTCone5Step)
		{
		testStep = new CTCone5Step();
		}
	else if (aStepName==KTConeInvalidateStep)
		{
		testStep = new CTConeInvalidateStep();
		}
	else if (aStepName==KTCone6Step)
		{
		testStep = new CTCone6Step();
		}
	else if (aStepName==KTCone7Step)
		{
		testStep = new CTCone7Step();
		}
	else if (aStepName==KTConeTransitionStep)
		{
		testStep = new CTConeTransitionStep();
		}
	else if (aStepName==KTConeZoomFontStep)
		{
		testStep = new CTConeZoomFontStep();
		}
	else if (aStepName==KTConeVisibilityStep)
		{
		testStep = new CTConeVisibilityStep();
		}
	else if (aStepName==KTConeCoeDataStorageStep)
		{
		testStep = new CTConeCoeDataStorageStep();
		}
	else if (aStepName==KTConeCoeCntSSStep)
		{
		testStep = new CTConeCoeCntSSStep();
		}
	else if (aStepName==KTConeResourceLoader)
		{
		testStep = new CTConeResourceLoaderStep();
		}
	else if (aStepName==KTConeStateObs)
		{
		testStep = new CTConeStateObs();
		}
	else if(aStepName == KTConeTransparencyStep)
		{
		testStep = new CTConeTransparencyStep();
		}
	else if (aStepName==KTConeMultiPtrStep)
		{
		testStep = new CTConeMultiPtrStep();
		}
	else if (aStepName==KTConeMultiPtrCompoundStep)
		{
		testStep = new CTConeMultiPtrCompoundStep();
		}
	else if(aStepName == KTMultipleScreensStep)
		{
		testStep = new CTMultipleScreensStep();
		}
	else if (aStepName==KTConeEvents)
		{
		testStep=new CTConeEvents(1);
		}
	else if (aStepName==KTConeEvents2)
		{
		testStep=new CTConeEvents(2);
		}
	return testStep;
	}
