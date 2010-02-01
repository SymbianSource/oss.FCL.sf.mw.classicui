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
// Tests Memory leak in CEikShutter.\n
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code
*/
#include <coeaui.h>
#include <apgcli.h>
#include <apgtask.h>
#include <apacmdln.h>

#include "shutapp.h"
#include "tshutter.h"
#include <ecom/ecom.h>

const TInt KTestCleanupStack=0x40;

/**
   @SYMTestCaseID UIF-tshutter-TestShutterL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Regression test for defect DEF022650 - Memory leak in
   CEikShutter.
  
   @SYMTestPriority High
 
   @SYMTestStatus Implemented
  
   @SYMTestActions The test performs the following:\n
   1. Start the application shutapp\n
   2. Once the app has started, ask it to close itself.\n
   3. Wait till the app has terminated.\n
   
   @SYMTestExpectedResults The shutapp application should not panic on exit due to
   a CEikShutter object being orphaned on the heap. We check this by making
   sure the TExitType is EExitKill. We also check that logonRequestStatus is
   KErrNone.
   
 */
void CTShutter::TestShutterL()
	{
	// Create the semaphore first so that it is guaranteed to exist before the app thread gets scheduled.
	RSemaphore sem;
	CleanupClosePushL(sem);
	TInt error=sem.CreateGlobal(SHUTAPP_SEMAPHORE,0);
	if (error==KErrAlreadyExists)
		{
		error=sem.OpenGlobal(SHUTAPP_SEMAPHORE);
		}
	User::LeaveIfError(error);

	// start shutapp
	RApaLsSession ls;
	CleanupClosePushL(ls);
	User::LeaveIfError(ls.Connect());
	TApaAppInfo info;
	User::LeaveIfError(ls.GetAppInfo(info, KTestShutAppUid));

	CApaCommandLine* cmdLine=CApaCommandLine::NewLC();	
	cmdLine->SetExecutableNameL(info.iFullName);

	cmdLine->SetCommandL(EApaCommandViewActivate);
	
	TParsePtrC parse(info.iFullName);
	cmdLine->SetDocumentNameL(parse.Name());

	TThreadId appThreadId;
	User::LeaveIfError(ls.StartApp(*cmdLine, appThreadId));
	CleanupStack::PopAndDestroy(cmdLine);
	CleanupStack::PopAndDestroy(&ls);

	// logon to app thread so we can wait for it to terminate later
	RThread appThread;
	User::LeaveIfError(appThread.Open(appThreadId));
	CleanupClosePushL(appThread);
	TRequestStatus logonRequestStatus;
	appThread.Logon(logonRequestStatus);

	// wait for the app to tell us that it has started
	// (it does this by signalling the named semaphore SHUTAPP_SEMAPHORE)
	sem.Wait();

	// close the app we've just started
	RWsSession wsSession;
	User::LeaveIfError(wsSession.Connect());
	const TInt wgId = wsSession.FindWindowGroupIdentifier(0, appThreadId);
	TApaTask task(wsSession);
	task.SetWgId(wgId);
	task.SendSystemEvent(EApaSystemEventShutdown);
	wsSession.Close();

	// wait for SHUTAPP app to terminate
	User::WaitForRequest(logonRequestStatus);

	TEST(logonRequestStatus == KErrNone);

	// SHUTAPP application should exit with EExitKill for the test to pass
	TExitType exitType = appThread.ExitType();
	CleanupStack::PopAndDestroy(&appThread);
	TEST(exitType == EExitKill);
	CleanupStack::PopAndDestroy(&sem);
	}


/**
   Auxiliary function for TestCaseID tshutter-TestShutterL
  
   This method initialises the cleanup stack.
 */
void CTShutter::setupCleanup()
    {
	iTrapCleanup=CTrapCleanup::New();
	TRAPD(r,\
		{\
		for (TInt i=KTestCleanupStack;i>0;i--)\
			CleanupStack::PushL((TAny*)1);\
		CleanupStack::Pop(KTestCleanupStack);\
		});
	TEST(r==KErrNone);
	}


/*
#if defined (__WINS__)
IMPORT_C void RegisterWsExe(const TDesC &aName);
#endif
*/
 /**  Auxiliary function for all Test Cases
  
   This method is an override from CTestStep. It is used to launch the test step.
  
 */
TVerdict CTShutter::doTestStepL()
	{
	__UHEAP_MARK;
		
	INFO_PRINTF1(_L("Test Started"));
		
	// run the test
	INFO_PRINTF1(_L("Test CEikShutter"));
	SetTestStepID(_L("UIF-tshutter-TestShutterL"));
	TRAPD(err, TestShutterL());
	TEST(err == KErrNone);

	INFO_PRINTF1(_L("Test Finished"));
		
	REComSession::FinalClose();	
	RecordTestResultL();
	CloseTMSGraphicsStep();
	__UHEAP_MARKEND;

	return TestStepResult();
	}

