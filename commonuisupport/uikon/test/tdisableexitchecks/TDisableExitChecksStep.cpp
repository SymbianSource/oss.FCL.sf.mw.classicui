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

#include <eikenv.h>
#include <eikappui.h>
#include <eikapp.h>
#include <eikdoc.h>
#include <ecom/ecom.h>
#include <hal.h>

#include "TDisableExitChecksStep.h"
#include <apacmdln.h>


_LIT(KTDisableExitChecksResourceFilePath,"");
_LIT8(KETrue,"ETrue");
_LIT8(KEFalse,"EFalse");

/*AppUI*/
CTDisableExitChecksAppUi::CTDisableExitChecksAppUi(CTmsTestStep* aStep) :
	CTestAppUi(aStep, KTDisableExitChecksResourceFilePath)
	{
	}

void CTDisableExitChecksAppUi::ConstructL()
	{
	CTestAppUi::ConstructL();
	AutoTestManager().StartAutoTest();
	}

CTDisableExitChecksAppUi::~CTDisableExitChecksAppUi()
	{
	}

/**
   @SYMTestCaseID UIF-TDisableExitChecksStep-TestDisableShutDownChecks
  
   @SYMDEF PDEF109432: Device does not shutdown properly  
  
   @SYMTestCaseDesc Test triggers the launch of an app that leaks memory once with disabled and once
   with enabled shutdown checks.
   
   @SYMTestPriority High 
  
   @SYMTestStatus Implemented
   
   @SYMTestActions Call StartProcessL with ETrue in order to disable the shutdown checks.
   Call StartProcessL with EFalse in order to disable the shutdown checks.
   Close the panic windows that have emerged.
   
   @SYMTestExpectedResults A panic window emerges, when the shutdown checks are enabled, since
   the app used (disableexitchecksapp) leaks memory. The panic window is followingly closed.
 */

void CTDisableExitChecksAppUi::TestDisableShutDownChecks()
	{
	INFO_PRINTF1(_L("Start Test TestDisableShutDownChecks..."));
	INFO_PRINTF1(_L("Disable shutdown checks..."));	
	StartProcessL(KETrue);
	INFO_PRINTF1(_L("Enable shutdown checks..."));	
	StartProcessL(KEFalse);
	CloseAllPanicWindowsL();	//closes the panic window that emerges, when the shutdown checks are enabled.
	}

/**
 *	This function creates a process to run disableexitchecksapp and launches this application.
 *
 *	The trailing data in the launch information is set to the aTailEnd parameter (expected to
 *	be ETrue or EFalse).
 *
 *	Since disableexitchecksapp leaks memory, it panics, when shutdown checks are enabled.
 *	However, it is expected to exit normally,when shutdown checks are disabled.
 *	
 */
void CTDisableExitChecksAppUi::StartProcessL(const TDesC8& aTailEnd)
	{
 	CApaCommandLine* cmdLine=CApaCommandLine::NewLC();
	RProcess process; 
	INFO_PRINTF1(_L("Create process..."));	
	User::LeaveIfError(process.Create(KExeName, KNullDesC));
	INFO_PRINTF1(_L("Process created!"));	
	CleanupClosePushL(process);
	INFO_PRINTF1(_L("Set commandline parameters..."));	
	TRAPD(ret,
		{ 
		cmdLine->SetExecutableNameL(KExeName);
		cmdLine->SetTailEndL(aTailEnd);
		cmdLine->SetProcessEnvironmentL(process);
		})
	TEST(ret==KErrNone);	
	TRequestStatus status = KRequestPending;
	process.Logon(status);

	//Prevent emulator closing when a panic occurs
	User::SetJustInTime(EFalse);

	process.Resume();
	User::WaitForRequest(status);
	INFO_PRINTF1(_L("Check process exit type..."));	
	if (aTailEnd==KETrue) 
		TEST(process.ExitType()==EExitKill);  //disableexitchecksapp exits normally,when shutdown checks are disabled
	else if (aTailEnd==KEFalse)
		TEST(process.ExitType()==EExitPanic); //disableexitchecksapp panics at exit,when shutdown checks are enabled
	INFO_PRINTF1(_L("Check process exit reason..."));	
	TEST(process.ExitReason()==KErrNone);

	User::SetJustInTime(ETrue);
	CleanupStack::PopAndDestroy(2, cmdLine);
	}
	
void CTDisableExitChecksAppUi::RunTestStepL(TInt aStepNum)
	{
	switch(aStepNum)
		{	
		case 1:
			SetTestStepID(_L("UIF-TDisableExitChecksStep-TestDisableShutDownChecks"));
			TRAPD(err,TestDisableShutDownChecks());
			TEST(err==KErrNone);
			RecordTestResultL();
			CloseTMSGraphicsStep();
			break;
		case 2:
			INFO_PRINTF1(_L("All tests completed.\n"));
			AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);	
			break;
		default:
			INFO_PRINTF1(_L("CTDisableExitChecksAppUi::RunTestStepL default case\n"));
			break;	
		}
	}

/*Test step*/
CTDisableExitChecksStep::CTDisableExitChecksStep()
	{
	SetTestStepName(KTDisableExitChecksStep);
	}

CTDisableExitChecksStep::~CTDisableExitChecksStep()
	{
	}

void CTDisableExitChecksStep::ConstructAppL(CEikonEnv* aCoe)
	{
	aCoe->ConstructL();
	CTDisableExitChecksAppUi* appUi=new(ELeave) CTDisableExitChecksAppUi(this);
	aCoe->SetAppUi(appUi);
	appUi->ConstructL();	
	}

TVerdict CTDisableExitChecksStep::doTestStepL() // main function called by E32
	{
	INFO_PRINTF1(_L("TDisableExitChecks Test Started"));
	PreallocateHALBuffer();
	__UHEAP_MARK; // 
	CEikonEnv* coe=new CEikonEnv;
	TRAPD(err,ConstructAppL(coe));
	if (!err)
		{
		coe->ExecuteD();
		}
	else
		{
		SetTestStepResult(EFail);
		delete coe;
		}
		
	REComSession::FinalClose();	
	__UHEAP_MARKEND;
	INFO_PRINTF1(_L("Test Finished"));
	return TestStepResult();
	}
