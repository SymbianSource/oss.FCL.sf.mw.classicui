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
// uiktetestserver.CPP
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code 
*/

#include <basched.h>
#include <eikenv.h>
#include <eikappui.h>
#include <techview/eikon.hrh>
#include <eikapp.h>
#include <eikdoc.h>
#include <techview/eiklabel.h>
#include <eikfctry.h>
#include <coecntrl.h>
#include <barsread.h>
#include <techview/eiktbar.h>
#include <techview/eikmenub.h>
#include <eikspane.h>

#include "appfwk_test_AppUi.h"
#include "uiktestserver.h"
#include "Taddlib.h"
#include "tspane.h"
#include "Tmsg.h"
#include "thlsprite.h"
#include "tbrdrcol.h"
#include "tbackup.h"
#include "tnotdial.h"
#include "Tcolscm.h"
#include "TCOLOVRStep.h"
#include "terrorStep.h"
#include "TpackageStarter.h"
#include "tshutter.h"
#include "Tautolib.h"
#include "tfileutils.h"
#include "teikenv.h"
#include "T_FocusStep.h"
#include "T_NonFocusStep.h"
#include "T_ParentStep.h"
#include "TCapability1.h"
#include "TCapability2.h"
#include "TSysColor.h"
#include "TDisableExitChecksStep.h"


#include "TAppLangStarter.h"
#include "TAppLangFrenchStarter.h"
#include "TAppLangZuluStarter.h"
#include "TAppLangNotSetStarter.h"
#include "TAppLangScStarter.h"


CUiktestServer* CUiktestServer::NewL()
	{
	CUiktestServer * server = new (ELeave) CUiktestServer();
	CleanupStack::PushL(server);
	// CServer base class call
	TParsePtrC serverName(RProcess().FileName());	
	server->StartL(serverName.Name());
	CleanupStack::Pop(server);
	return server;
	}


CTestStep* CUiktestServer::CreateTestStep(const TDesC& aStepName)
	{
	CTestStep* testStep = NULL;

	// This server creates just one step but create as many as you want
	// They are created "just in time" when the worker thread is created
	if(aStepName == KTestAddLibraryStep)
		{
		testStep = new CTestAddLibraryStep();
		}
	else if(aStepName == KTestAutoLibStep)
		{
		testStep = new CTestAutoLibStep();
		}
	else if(aStepName == KTestSpaneStep)
		{
		testStep = new CTestSpaneStep();
		}
	else if(aStepName == KTestMsgStep)
		{
		testStep = new CTestMsgStep();
		}
	else if(aStepName == KHlSpriteStep)
		{
		testStep = new CTestThlspriteStep();
		}
	else if(aStepName == KTestBrdrColStep)
		{
		testStep = new CTestBrdrColStep();
		}
	else if(aStepName == KTestBackupStep)
		{
		testStep = new CTestBackupStep();
		}
	else if(aStepName == KTestColscmStep)
		{
		testStep = new CTestColscmStep();
		}
	else if(aStepName == KTestPackageStep)
		{
		testStep = new CTestPackageStep();
		}
	else if(aStepName == KTColOvrStep)
		{
		testStep = new CTColOvrStep();
		}
	else if(aStepName == KTErrorStep)
		{
		testStep = new CTErrorStep();
		}
	else if(aStepName == KTShutter)
		{
		testStep = new CTShutter();
		}
	else if(aStepName == KTNotdialStep)
		{
		testStep = new CTNotdialStep();
		}
	else if(aStepName == KFileUtilsStep)
		{
		testStep = new CFileUtilsStep();
		}
	else if(aStepName == KEikEnvStep)
		{
		testStep = new CEikEnvStep();
		}
	else if (aStepName == KTestApplicationLanguageStep)
		{
		testStep = new CTestApplicationLanguageStep();
		}
	else if (aStepName == KTestApplicationLanguageFrenchStep)
		{
		testStep = new CTestApplicationLanguageFrenchStep();
		}
	else if (aStepName == KTestApplicationLanguageZuluStep)
		{
		testStep = new CTestApplicationLanguageZuluStep();
		}
	else if (aStepName == KTestApplicationLanguageNotSetStep)
		{
		testStep = new CTestApplicationLanguageNotSetStep();
		}
	else if (aStepName == KTestApplicationLanguageSCStep)
		{
		testStep = new CTestApplicationLanguageSCStep();
		}
	else if (aStepName == KTestFocusStep)
		{
		testStep = new CTestFocusStep();
		}
	else if (aStepName == KTestNonFocusStep)
		{
		testStep = new CTestNonFocusStep();
		}
	else if (aStepName == KTestParentStep)
		{
		testStep = new CTestParentStep();
		}
	else if	(aStepName == KTCapability1Step)
		{
		testStep = new CTCapability1Step();
		}
	else if	(aStepName == KTCapability2Step)
		{
		testStep = new CTCapability2Step();
		}
	else if	(aStepName == KTSysColorStep)
		{
		testStep = new CTSysColorStep();
		}
	else if	(aStepName == KTDisableExitChecksStep)
		{
		testStep = new CTDisableExitChecksStep();
		}
	return testStep;
	}


LOCAL_C void MainL()
	{
	// Leave the hooks in for platform security
	CActiveScheduler* sched=NULL;
	sched=new(ELeave) CActiveScheduler;
	CActiveScheduler::Install(sched);

	CUiktestServer* server = NULL;
	// Create the CTestServer derived server
	TRAPD(err,server = CUiktestServer::NewL());
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
