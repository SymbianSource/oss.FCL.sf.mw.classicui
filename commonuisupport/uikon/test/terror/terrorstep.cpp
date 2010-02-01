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
// The TError test app tests the extended error resolver implemented in \uikon\coresrc\eikerror.cpp
// The app can only be built when Uikon source is present on the root of the same drive
// For the tests to run, TError_Test* must be moved to c:\resource\errors.  Note that the build 
// process does not do this automatically.
// The test app has no UI so all the tests are driven from the menu.  The tests should run in any
// order and be expected to succeed.
// 
//

/**
 @file
 @test
 @internalComponent - Internal Symbian test code
*/

#include <basched.h>
#include <eikenv.h>
#include <eikappui.h>
#include <eikapp.h>
#include <eikdoc.h>
#include <eikerror.h>
#include <ecom/ecom.h>
#include <bautils.h>
#include <hal.h>

#include <terrorstep.rsg>
#include "terrorstep.hrh"
#include "terrorStep.h"
#include <textresolver.h>
#include <errorres.rsg>

// Currently disabled as "No memory" dialogs from CCoeEnv::ReadResource prevent automation.
// #define TEST_OOM



//
//
// 	Global consts and definitions
//
//

const TInt KCDriveTest1Err	= 301;
const TInt KCDriveTest2Err	= 426;
const TInt KCDriveTest3Err	= 540;
const TInt KCDriveTest4Err	= 612;
const TInt KCDriveTest5Err	= 739;

_LIT(KCDriveTestErr1Text,"CDrv error #1");
_LIT(KCDriveTestErr2Text,"CDrv error #2");
_LIT(KCDriveTestErr3Text,"CDrv error #3");
_LIT(KCDriveTestErr4Text,"CDrv error #4");
_LIT(KCDriveTestErr5Text,"CDrv error #5");
_LIT(KErrTextOOM,"Not enough memory");
_LIT(KErrTextUnknown,"Unknown error");

_LIT(KTErrorResourceFilePath,"z:\\system\\test\\terror\\terrorstep.rsc");

// For error multiple language tests
_LIT(KTErrorLang1Src, "z:\\system\\test\\terror\\terror_lang1.r01");
_LIT(KTErrorLang1Tgt, "c:\\Resource\\Errors\\terror_lang1.r01");
_LIT(KTErrorLang2Src, "z:\\system\\test\\terror\\terror_lang2.r02");
_LIT(KTErrorLang2Tgt, "\\Resource\\Errors\\terror_lang2.r02");
_LIT(KTErrorLang3Src, "z:\\system\\test\\terror\\terror_lang3.rsc");
_LIT(KTErrorLang3Tgt, "c:\\Resource\\Errors\\terror_lang3.rsc");
_LIT(KTErrorLang4Src, "z:\\system\\test\\terror\\terror_lang4.r18");
_LIT(KTErrorLang4Tgt, "\\Resource\\Errors\\terror_lang4.r18");
_LIT(KTErrorLang5Src, "z:\\system\\test\\terror\\terror_lang5.r02");
_LIT(KTErrorLang5Tgt, "\\Resource\\Errors\\terror_lang5.r02");
_LIT(KTErrorLang6Src, "z:\\system\\test\\terror\\terror_lang6.r01");
_LIT(KTErrorLang6Tgt, "c:\\Resource\\Errors\\terror_lang6.r01");
_LIT(KTErrorLang7Src, "z:\\system\\test\\terror\\terror_lang7.r10");
_LIT(KTErrorLang7Tgt, "\\Resource\\Errors\\terror_lang5.r10");	// 5 on purpose so that NearestLanguageFile works

// Only V2 paths are supported now
_LIT(KSrcErrorResFileFmt,"Z:\\System\\Test\\TError\\TError_Test%dstep.rsc");
_LIT(KTrgErrorResFileFmt,"C:\\Resource\\Errors\\TError_Test%dstep.rsc");
_LIT(KResFileWild,"TError_Test?Step.r*");
_LIT(KErrorResFileFmt,"TError_Test%dStep.rsc");
_LIT(KLitV2ResFilePath, "C:\\Resource\\Errors\\");
_LIT(KLitV2ResFilePathInvalid, "C:\\Resource\\Errors_Invalid\\");


//
//
// 	Global functions
//
//

enum TTestErrorStepPanic
	{
	ETestUnknownResFile,
	ETestErrTextDontMatch,
	};


LOCAL_D void Panic(TTestErrorStepPanic aPanic)
	{
	User::Panic(_L("TERRORSTEP"), aPanic);
	}



// Full name of the test resource file when installed.
void ResFileFullName(TFileName& aFileName, TTErrorResFile aFile)
	{
	__ASSERT_ALWAYS(aFile >= EResFile1 && aFile <= EResFile5, Panic(ETestUnknownResFile));
	aFileName.Format(KErrorResFileFmt, aFile);
	aFileName.Insert(0, KLitV2ResFilePath());
	}



//
//
// 						class CWait
//
//


//
// class CKeyEater
//

CWait::CKeyEater* CWait::CKeyEater::NewL()
	{
	CKeyEater* self=new(ELeave) CKeyEater;
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}

CWait::CKeyEater::CKeyEater()
	{
	}

CWait::CKeyEater::~CKeyEater()
	{
	iEikonEnv->RemoveFromStack(this);
	}

TKeyResponse CWait::CKeyEater::OfferKeyEventL(const TKeyEvent& /*aKeyEvent*/,TEventCode /*aType*/)
	{
	return EKeyWasConsumed;
	}

void CWait::CKeyEater::ConstructL()
	{
	// highest stack priority so that Key Eater control get offered key events before other control.
   	iEikonEnv->EikAppUi()->AddToStackL(this,ECoeStackPriorityEnvironmentFilter);
	}

//
// class CWait
//

void CWait::WaitLD(TInt aIntervalMicroSeconds)
	{
	CWait* self=new(ELeave) CWait;
	CleanupStack::PushL(self);
	self->ConstructL(aIntervalMicroSeconds);
	CleanupStack::PopAndDestroy(self);
	}

CWait::CWait()
	: CActive(EPriorityStandard)
	{
	CActiveScheduler::Add(this);
	iStatus=KRequestPending;
	SetActive();
	}

void CWait::ConstructL(TInt aIntervalMicroSeconds)
	{
	User::LeaveIfError(iTimer.CreateLocal());
	iTimer.After(iStatus,aIntervalMicroSeconds);
	iKeyControl=CKeyEater::NewL();
	CActiveScheduler::Start();
	}

CWait::~CWait()
	{
	Cancel();
	iTimer.Close();
	delete iKeyControl;
	}

void CWait::DoCancel()
	{
	iTimer.Cancel();
	}

void CWait::RunL()
	{
	CActiveScheduler::Stop();
	}



//
//
// 						class CAppBackup
//
//

CAppBackup* CAppBackup::NewLC()
	{
	CAppBackup* self=new(ELeave) CAppBackup;
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CAppBackup::~CAppBackup()
	{
	if (iBackupSession)
		{
		RestartFile(EResFile1);
		RestartFile(EResFile2);
		RestartFile(EResFile3);
		RestartFile(EResFile4);
		RestartFile(EResFile5);
		CWait::WaitLD(1000000); // wait 1s to allow for all resource files to be reopened
		delete iBackupSession;
		}
	}

CAppBackup::CAppBackup()
	{
	}

void CAppBackup::ConstructL()
	{
	iBackupSession=CBaBackupSessionWrapper::NewL();
	CloseFileL(EResFile1);
	CloseFileL(EResFile2);
	CloseFileL(EResFile3);
	CloseFileL(EResFile4);
	CloseFileL(EResFile5);
	CWait::WaitLD(100000); // wait 0.1s to allow the files to be closed
	}

// Releases resource files to enable backup.
void CAppBackup::CloseFileL(TTErrorResFile aFile)
	{
	TFileName fileName;
	ResFileFullName(fileName, aFile);
	iBackupSession->CloseFileL(fileName, MBackupObserver::EReleaseLockNoAccess);
	}


// Called by the destructor to release file locks imposed during backup.
void CAppBackup::RestartFile(TTErrorResFile aFile)
	{
	TFileName fileName;
	ResFileFullName(fileName, aFile);
	iBackupSession->RestartFile(fileName);
	}



//
//
// 						class CAppTest
//
//

CAppTest::CAppTest(CEikonEnv& aEnv, CTErrorAppUi* aAppUi)
	: iEikEnv(aEnv), iAppUi(aAppUi)
	{
	}

void CAppTest::InitTimerL()
	{
	User::LeaveIfError(HAL::Get(HALData::EFastCounterFrequency, iFreq));
	}

void CAppTest::StartTimer()
	{
	iStartTime = User::FastCounter();	
	}

void CAppTest::StopTimer()
	{
	iEndTime = User::FastCounter();
	iTotalTime = (1000000*(TInt64)(iEndTime - iStartTime)) / (TInt64)iFreq;
	}

void CAppTest::TestErrTxtL(const TDesC& aErrText,const TDesC& aExpected) const
	{
	if (aErrText!=aExpected)
		{
		if (iOOMTesting && (aErrText==KNullDesC || aErrText==KErrTextOOM || aErrText==KErrTextUnknown))
			{
			User::LeaveNoMemory();
			}
		iAppUi->ERR_PRINTF3(_L("Errors texts don't match: Expected='%S', Actual='%S'"), &aExpected, &aErrText);
		iAppUi->TEST(EFalse);
		}
	}

/**
   @SYMTestCaseID UIF-errorstep-TestResolveErrsL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test CEikErrorResolver::ResolveError() API.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method invokes CEikErrorResolver::ResolveError() method by
   passing the errors defined. It then checks if the error message for the error
   is read from its corresponding resource file and returned.
  
   @SYMTestExpectedResults All tests check the error message returned for the error
   against the error message defined in corresponding resource file.
   
 */
void CAppTest::TestResolveErrsL()
	{
	CEikErrorResolver* errRes=CEikErrorResolver::NewL(iEikEnv);
	CleanupStack::PushL(errRes);
	TestResolveErrsL(*errRes);
	CleanupStack::PopAndDestroy(errRes);
	}

void CAppTest::TestResolveErrsL(CEikErrorResolver& aErrRes)
	{
	TBuf<256> errText;

	aErrRes.ResolveError(errText,KCDriveTest1Err,KNullUid); 
	TestErrTxtL(errText, KCDriveTestErr1Text);

	errText.Zero();
	aErrRes.ResolveError(errText,KCDriveTest2Err,KNullUid); 
	TestErrTxtL(errText, KCDriveTestErr2Text);

	errText.Zero();
	aErrRes.ResolveError(errText,KCDriveTest3Err,KNullUid); 
	TestErrTxtL(errText, KCDriveTestErr3Text);

	errText.Zero();
	aErrRes.ResolveError(errText,KCDriveTest4Err,KNullUid); 
	TestErrTxtL(errText, KCDriveTestErr4Text);

	errText.Zero();
	aErrRes.ResolveError(errText,KCDriveTest5Err,KNullUid); 
	TestErrTxtL(errText, KCDriveTestErr5Text);
	}


/**
   @SYMTestCaseID UIF-errorstep-TestMultipleLanguagesAcrossDrivesL
  
   @SYMDEF PDEF096768
  
   @SYMTestCaseDesc Test CEikErrorResolver::ResolveError() API.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The test case is to scan the various drives present 
   with the given error id and checking whether it resolves to the exact or nearest 
   error message of the chosen language. The language is changed and scanning of 
   various drives to resolve the error message is carried out.
  
   @SYMTestExpectedResults All tests check the error message returned for the error
   against the error message defined in corresponding resource file.
 */
void CAppTest::TestMultipleLanguagesAcrossDrivesL()
	{
	CEikErrorResolver* eikResolver=CEikErrorResolver::NewL(iEikEnv);
	CleanupStack::PushL(eikResolver);

	// test it gives an "english error" with the specified id, ignoring others with same id
	TBuf<256> errText;
	const TInt errorId1 = 25000;
	eikResolver->ResolveError(errText,errorId1,KNullUid); 
	_LIT(KRefString1, "An english error");
	TestErrTxtL(errText, KRefString1);
	errText.Zero();
	
	// test it gives an "default error" with the specified id, ignoring others with same id
	const TInt errorId2 = 30000;
	eikResolver->ResolveError(errText,errorId2,KNullUid); 
	_LIT(KRefString2, "A default error");
	TestErrTxtL(errText, KRefString2);
	errText.Zero();
	
	// test it gives an "american error" if language is changed to american
	BaflUtils::SetIdealLanguage(ELangAmerican);
	const TInt errorId3 = 31000;
	eikResolver->ResolveError(errText,errorId3,KNullUid); 
	_LIT(KRefString3, "Another american error");
	TestErrTxtL(errText, KRefString3);
	errText.Zero();
	
	// test it gives an "unknown error" if no language is specified
	BaflUtils::SetIdealLanguage(ELangNone);	
	const TInt errorId4 = 35604;
	eikResolver->ResolveError(errText,errorId4,KNullUid); 
	_LIT(KRefString4, "Unknown error");
	TestErrTxtL(errText, KRefString4);
	errText.Zero();

	CleanupStack::PopAndDestroy(eikResolver);
	}

	
/**
   @SYMTestCaseID UIF-errorstep-TimeResolveErrsL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test turnaround time of extended error resolver.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method invokes CAppTest::TimeResolveSingleErrL() which 
   records the the turn around time for CEikErrorResolver::ResolveError() to
   resolve each of the defined errors & return the error message read from the
   resource file. It also tests the turn around time for resolving all the error
   defined.
  
   @SYMTestExpectedResults In all cases the turnaround time for the defined errors
   to be resolved is recorded.
 */
void CAppTest::TimeResolveErrsL()
	{
	TBuf<256> errText;

	// init the timer to get the value for the frequency of the counter
	InitTimerL();

	// resolve each error using a newly constructed resolver - gives worst case response times
	errText=KCDriveTestErr1Text();
	TimeResolveSingleErrL(KCDriveTest1Err,errText, KNullUid);
	errText=KCDriveTestErr2Text();
	TimeResolveSingleErrL(KCDriveTest2Err,errText, KNullUid);
	errText=KCDriveTestErr3Text();
	TimeResolveSingleErrL(KCDriveTest3Err,errText, KNullUid);
	errText=KCDriveTestErr4Text();
	TimeResolveSingleErrL(KCDriveTest4Err,errText, KNullUid);
	errText=KCDriveTestErr5Text();
	TimeResolveSingleErrL(KCDriveTest5Err,errText, KNullUid);

	// resolve each error using the same (newly constructed resolver)
	CEikErrorResolver* errRes=CEikErrorResolver::NewL(iEikEnv);
	StartTimer();
	TestResolveErrsL(*errRes);
	StopTimer();
	iAppUi->INFO_PRINTF2(_L("time taken to resolve each error using the same (newly constructed resolver) is '%d'"), iTotalTime);

	// resolve each error using a resolver that has already scanned all resource files
	StartTimer();
	TestResolveErrsL(*errRes);
	StopTimer();
	iAppUi->INFO_PRINTF2(_L("time taken to resolve each error using a resolver that has already scanned all resource files is '%d'"), iTotalTime);

	// clean-up
	delete errRes;
	}


void CAppTest::TimeResolveSingleErrL(TInt aErrCode,const TDesC& aTargetErrText, TUid uid)
	{
	CEikErrorResolver* errRes=CEikErrorResolver::NewL(iEikEnv);
	CleanupStack::PushL(errRes);
	TBuf<256> errText;

	StartTimer();
	errRes->ResolveError(errText,aErrCode,uid);
	StopTimer();
	TestErrTxtL(errText, aTargetErrText);
	iAppUi->INFO_PRINTF2(_L("time taken to resolve each error using a newly constructed resolver is '%d'"), iTotalTime);

	// Clean-up and return	
	CleanupStack::PopAndDestroy(errRes);
	}


/**
   @SYMTestCaseID UIF-errorstep-TestResolveAllL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test behaviour when error files are added or removed.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method backs up the resource files and renames them.Then
   invokes CEikErrorResolver::ResolveError() by passing error codes. It tests
   the error message returned by ResolveError(). The method then adds the
   resource files back and tests CEikErrorResolver::ResolveError() API.
  
   @SYMTestExpectedResults The error message should be unknown error on renaming of
   the resource files. On restoration of the resource files the error message
   should be as read from the resource file.
*/
void CAppTest::TestResolveAllL()
	{
	CEikErrorResolver* errRes=CEikErrorResolver::NewL(iEikEnv);
	CleanupStack::PushL(errRes);
	TBuf<40> unknownErrText;
	errRes->ResolveError(unknownErrText,KErrUnknown,KNullUid);
	
	// resolve resource files (all should be ok now)
	TestResolveErrsL(*errRes);

	// Connect to the utils server
	RSmlTestUtils utils;
	User::LeaveIfError(utils.Connect());
	CleanupClosePushL(utils);

	// remove res files
	CAppBackup* backup=CAppBackup::NewLC();
	TInt err = utils.RenameDirectoryL(KLitV2ResFilePath(), KLitV2ResFilePathInvalid());
	iAppUi->TEST(err == KErrNone);

	// resolve resource files (now things are not resolved...)
	TBuf<256> errText;

	errRes->ResolveError(errText,KCDriveTest1Err,KNullUid);
	TestErrTxtL(errText, unknownErrText);
	errRes->ResolveError(errText,KCDriveTest3Err,KNullUid);
	TestErrTxtL(errText, unknownErrText);
	errRes->ResolveError(errText,KCDriveTest5Err,KNullUid);
	TestErrTxtL(errText, unknownErrText);

	// add res files again
	err = utils.RenameDirectoryL(KLitV2ResFilePathInvalid(), KLitV2ResFilePath());
	CleanupStack::PopAndDestroy(backup);
	
	// resolve works again...
	TestResolveErrsL(*errRes);

	// clean-up
	CleanupStack::PopAndDestroy(2, errRes);
	}


/**
   @SYMTestCaseID UIF-errorstep-TestOOML
  
   @SYMPREQ
  
   @SYMTestCaseDesc Performs OOM tests.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method tests CEikErrorResolver::ResolveError() unnder OOM
   condition. The method finds the number of handles open for the thread &
   process before performimg tests. Then checks the threads heap while running
   tests on CEikErrorResolver::ResolveError() for all the defined errors. On
   completion of these tests the number of handles open for the thread & process
   are checked.
  
   @SYMTestExpectedResults The number of handles open for the thread & process at
   start and end should be same.
 */
void CAppTest::TestOOML()
	{
	iOOMTesting = ETrue;
	TInt error=KErrNoMemory;
	iAppUi->INFO_PRINTF1(_L("starting the OOM testing loop..."));
	TInt fail(0);
	for(fail=1;error!=KErrNone;fail++)
		{
		TInt pHCountStart=0;
		TInt tHCountStart=0;
		RThread().HandleCount(pHCountStart,tHCountStart);
		__UHEAP_SETFAIL(RHeap::EDeterministic, fail);
		__UHEAP_MARK;

		// for OOM purposes, we test one of the errors texts only
		TRAP(error, TestResolveSingleErrL(KCDriveTest1Err, KCDriveTestErr1Text, KNullUid));
		iAppUi->TEST(error == KErrNoMemory || error == KErrNone);
		
		__UHEAP_MARKEND;
		TInt pHCountEnd=0;
		TInt tHCountEnd=0;
		RThread().HandleCount(pHCountEnd,tHCountEnd);
		iAppUi->TEST(pHCountStart == pHCountEnd && tHCountStart == tHCountEnd);
		__UHEAP_RESET;
		}
	iAppUi->INFO_PRINTF2(_L("OOM loop finished after '%d' attempts"), fail-1);
	iOOMTesting = EFalse;
	}

void CAppTest::TestResolveSingleErrL(TInt aErrCode, const TDesC& aTargetErrText, TUid uid)
	{
	CEikErrorResolver* errRes=CEikErrorResolver::NewL(iEikEnv);
	CleanupStack::PushL(errRes);
	TBuf<256> errText;

	errRes->ResolveError(errText,aErrCode,uid);
	TestErrTxtL(errText, aTargetErrText);

	// Clean-up and return	
	CleanupStack::PopAndDestroy(errRes);
	}


/**
   @SYMTestCaseID UIF-errorstep-RunStandardAPIL
  
   @SYMPREQ
   
   @SYMTestCaseDesc Tests CEikonEnv::GetErrorText() with defined errors.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method invokes CEikonEnv::GetErrorText() method by
   passing the errors defined. It then checks if the error message for the error
   is same as the error messages defined in the terror resource files..
  
   @SYMTestExpectedResults The method tests all error messages returned by
   CEikonEnv::GetErrorText() against expected results.
   
 */
void CAppTest::RunStandardAPIL()
	{
	TBuf<256> errText;

	iEikEnv.GetErrorText(errText,KCDriveTest1Err,KNullUid);
	TestErrTxtL(errText, KCDriveTestErr1Text);

	iEikEnv.GetErrorText(errText,KCDriveTest2Err,KNullUid);
	TestErrTxtL(errText, KCDriveTestErr2Text);

	iEikEnv.GetErrorText(errText,KCDriveTest3Err,KNullUid);
	TestErrTxtL(errText, KCDriveTestErr3Text);

	iEikEnv.GetErrorText(errText,KCDriveTest4Err,KNullUid);
	TestErrTxtL(errText, KCDriveTestErr4Text);

	iEikEnv.GetErrorText(errText,KCDriveTest5Err,KNullUid);
	TestErrTxtL(errText, KCDriveTestErr5Text);
	}
	
	
/**
   @SYMTestCaseID UIF-UIKON-0006
  
   @SYMDEF DEF097643
  
   @SYMTestCaseDesc Test 
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions This Method invokes terrorapp.exe.
     
   @SYMTestExpectedResults The Method should run terrorapp.exe successfully 
   and terrorapp.exe tests CEikErrorResolver::ResolveError() API by testing the error message resolved.
   Terrorapp.exe should terminate with KErrNone.
 */
void CAppTest::TestErrorAppL()
	{
	_LIT(KErrorAppFileName,"z:\\sys\\bin\\terrorapp.exe");
	RProcess errorAppProc;
	TRequestStatus appState;
	TBool jit = User::JustInTime();
	User::SetJustInTime(EFalse);
	TInt ret = errorAppProc.Create(KErrorAppFileName,KNullDesC);
	User::LeaveIfError(ret);
	CleanupClosePushL(errorAppProc);
	
	//Launching the application
	errorAppProc.Logon(appState);
	errorAppProc.Resume();
	User::WaitForRequest(appState);
	
	ret = errorAppProc.ExitReason();
	iAppUi->TEST(ret == KErrNone);

	CleanupStack::PopAndDestroy(&errorAppProc);
	User::SetJustInTime(jit);
	
	User::LeaveIfError(ret);	
	}

/**
   @SYMTestCaseID UIF-UIKON-0008
  
   @SYMREQ 7736

   @SYMTestCaseDependencies	Following steps should be done before running this test: 
   		1. Uncomment the call to this manual test
   		2. Error codes must be updated. Following files need replacing with those in uikon/test/terror/terrortextwithtitleapp/data.
   			a) //EPOC/master/common/generic/tools/s60_header_compat/commonengineresources/data/errorres.rss
			b) //EPOC/master/common/generic/tools/s60_header_compat/commonengineresources/inc/errorres.loc
		3. Reallyclean and re-compile the following folders:
			a) //EPOC/master/common/generic/tools/s60_header_compat/group95/bld.inf (or later)
			b) Uiktest code (\uikon\test\group\bld.inf), so the test code links against the new rsc files.
  
   @SYMTestCaseDesc Test
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions This Method invokes terrortextwithtitleapp.exe, which tests the newly added error codes.
     
   @SYMTestExpectedResults terrortextwithtitleapp.exe should terminate with KErrNone, meaning that all its internal
   						   checks inside the app were ok, and hence error message correctly resolved.
 */
void CAppTest::TestErrorWithTitleManuallyL()
	{
	iAppUi->INFO_PRINTF1(_L("Manual Testing for new test error codes added to errorres.rss file"));
	_LIT(KErrorTextWithTitleAppFileName,"z:\\sys\\bin\\terrortextwithtitleapp.exe");
	RProcess errorContextProc;
	TRequestStatus appState;
	TBool jit = User::JustInTime();
	User::SetJustInTime(EFalse);
	TInt ret = errorContextProc.Create(KErrorTextWithTitleAppFileName,KNullDesC);
	iAppUi->TEST(ret == KErrNone);
	User::LeaveIfError(ret);
	CleanupClosePushL(errorContextProc);

	//Launching the application
	iAppUi->INFO_PRINTF1(_L("Start terrortextwithtitleapp.exe to test the new test error codes"));
	errorContextProc.Logon(appState);
	errorContextProc.Resume();
	User::WaitForRequest(appState);
	iAppUi->TEST(errorContextProc.ExitReason() == KErrNone);
	iAppUi->TEST(errorContextProc.ExitType() == EExitKill);

	CleanupStack::PopAndDestroy(&errorContextProc);
	User::SetJustInTime(jit);
	iAppUi->INFO_PRINTF1(_L("Manual test completed"));
    }

/**
   @SYMTestCaseID UIF-UIKON-0009
  
   @SYMREQ 7736
  
   @SYMTestCaseDependencies	This test should be run only from v9.6 onwards

   @SYMTestCaseDesc Tests CTextResolver::ResolveErrorString() API
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions This method tests the standard error codes present in the error resource file (resource/apps/errorres.rsc)
     
   @SYMTestExpectedResults CTextResolver::ResolveErrorString() method should resolve the standard error defined in error
   resource file with error text and title text.
 */
void CAppTest::TestErrorWithTitleAppL()
	{
    TInt textId = 0;
    TUint flags = 0;
	CEikonEnv* eikonEnv = CEikonEnv::Static();

    CTextResolver* textResolver = CTextResolver::NewLC(*eikonEnv);
	iAppUi->INFO_PRINTF1(_L("Test for error with empty string description"));
  	TPtrC buf(textResolver->ResolveErrorString(-12004, textId, flags));
    iAppUi->TEST(buf.Compare(_L("")) == 0 && flags == 10);
    CleanupStack::PopAndDestroy();

    textResolver = CTextResolver::NewL();
    CleanupStack::PushL(textResolver);
  	buf.Set(textResolver->ResolveErrorString(-12004, textId, flags));
    iAppUi->TEST(buf.Compare(_L("")) == 0 && flags == 10);
    CleanupStack::PopAndDestroy();

	iAppUi->INFO_PRINTF1(_L("Test for error which is not present in the error resource file"));
    textResolver = CTextResolver::NewL();
    CleanupStack::PushL(textResolver);
  	buf.Set(textResolver->ResolveErrorString(-10020, textId, flags));
    iAppUi->TEST(buf.Compare(_L("System:\nSystem error.")) == 0 && flags == 6);
    CleanupStack::PopAndDestroy();

    textResolver = CTextResolver::NewL(*eikonEnv);
    CleanupStack::PushL(textResolver);
  	buf.Set(textResolver->ResolveErrorString(-10020, textId, flags));
    iAppUi->TEST(buf.Compare(_L("System:\nSystem error.")) == 0 && flags == 6);
    CleanupStack::PopAndDestroy();

	iAppUi->INFO_PRINTF1(_L("Test out of memory error"));
    textResolver = CTextResolver::NewLC(*eikonEnv); 
    buf.Set(textResolver->ResolveErrorString(KErrNoMemory, textId, flags, CTextResolver::ECtxNoCtx));
    iAppUi->TEST(textId == R_ERROR_RES_NO_MEMORY && (flags == 0));
    CleanupStack::PopAndDestroy();

    textResolver = CTextResolver::NewLC();	// TextResolver doesn't use uikon's error resolver for resolving the error
    buf.Set(textResolver->ResolveErrorString(KErrNoMemory, textId, flags, CTextResolver::ECtxNoCtx));
    iAppUi->TEST(textId == R_ERROR_RES_NO_MEMORY && (flags == 0));
    CleanupStack::PopAndDestroy();

   	iAppUi->INFO_PRINTF1(_L("Test the error In Use"));
    textResolver = CTextResolver::NewLC(*eikonEnv); 	// TextResolver uses uikon's error resolver for resolving the error
    buf.Set(textResolver->ResolveErrorString(KErrInUse, textId, flags, CTextResolver::ECtxNoCtx));
    iAppUi->TEST(buf.Compare(_L(":\nRequested object is used by another application")) == 0 && (textId == R_ERROR_RES_IN_USE) && (flags == 0));
    CleanupStack::PopAndDestroy();

    textResolver = CTextResolver::NewLC();
    buf.Set(textResolver->ResolveErrorString(KErrInUse, textId, flags, CTextResolver::ECtxNoCtx));
    iAppUi->TEST(buf.Compare(_L(":\nRequested object is used by another application")) == 0 && (textId == R_ERROR_RES_IN_USE) && (flags == 0));
    CleanupStack::PopAndDestroy();

   	iAppUi->INFO_PRINTF1(_L("Test the permission denied error"));
    textResolver = CTextResolver::NewLC(*eikonEnv); 	// TextResolver uses uikon's error resolver for resolving the error
    buf.Set(textResolver->ResolveErrorString(-12007));
    iAppUi->TEST(buf.Compare(_L("System:\nExecution not allowed for security reasons")) == 0);
    CleanupStack::PopAndDestroy();

    textResolver = CTextResolver::NewLC();
    buf.Set(textResolver->ResolveErrorString(-12007));
    iAppUi->TEST(buf.Compare(_L("System:\nExecution not allowed for security reasons")) == 0);
    CleanupStack::PopAndDestroy();

    iAppUi->INFO_PRINTF1(_L("Test Unknown error"));
    textResolver = CTextResolver::NewLC(*eikonEnv); 
    buf.Set(textResolver->ResolveErrorString(-34, textId, flags));
    iAppUi->TEST(buf.Compare(_L("System:\nSystem error.")) == 0 && (textId == R_ERROR_RES_GENERAL) && (flags == 6));
    CleanupStack::PopAndDestroy();

    iAppUi->INFO_PRINTF1(_L("Test Unknown error without the error title and context separator"));
    textResolver = CTextResolver::NewLC(); 
    buf.Set(textResolver->ResolveErrorString(-34, textId, flags, CTextResolver::ECtxNoCtxNoSeparator));
    iAppUi->TEST(buf.Compare(_L("System error.")) == 0 && (textId == R_ERROR_RES_GENERAL) && (flags == 6));
    CleanupStack::PopAndDestroy();

    iAppUi->INFO_PRINTF1(_L("Test System error"));
    textResolver = CTextResolver::NewLC(*eikonEnv);
  	buf.Set(textResolver->ResolveErrorString(-12008, textId, flags));
    iAppUi->TEST(buf.Compare(_L("System:\nSystem error.")) == 0 && (flags == 6));
    CleanupStack::PopAndDestroy();

    textResolver = CTextResolver::NewLC();
  	buf.Set(textResolver->ResolveErrorString(-12008, textId, flags));
    iAppUi->TEST(buf.Compare(_L("System:\nSystem error.")) == 0 && (flags == 6));
    CleanupStack::PopAndDestroy();

	TBuf<256> errText;
	TBuf<256> titleText;
	eikonEnv->GetErrorTextAndTitle(errText, -12007, titleText);
    iAppUi->TEST(titleText.Compare(_L("System")) == 0 && errText.Compare(_L("Execution not allowed for security reasons")) == 0);

    // Test error resolving with memory allocation failure in 1 to n allocations
    iAppUi->INFO_PRINTF1(_L("OOM test for Text Resolver"));
	textResolver = NULL;
	TBool loop = ETrue;
    for (TInt fail = 1; loop; fail++)
    	{
		__UHEAP_SETFAIL(RHeap::EDeterministic, fail);
        __UHEAP_MARK;          	

    	TRAPD(error, textResolver = CTextResolver::NewL(*eikonEnv));
     	__UHEAP_RESET;
    	if (error != KErrNone)
    		{
    		__UHEAP_MARKEND;
    		iAppUi->TEST(textResolver == NULL);
			continue;
    		}
    	buf.Set(textResolver->ResolveErrorString(-12007, textId, flags));
		iAppUi->TEST((flags == 0) && buf.Compare(_L("System:\nExecution not allowed for security reasons")) == 0);
		delete textResolver;
		loop=EFalse;
     	__UHEAP_MARKEND;
        }
	}

//
//
// 						class CTErrorAppUi
//
//

CTErrorAppUi::CTErrorAppUi(CTmsTestStep* aStep) :
	CTestAppUi(aStep, KTErrorResourceFilePath)
	{
	}

CTErrorAppUi::~CTErrorAppUi()
	{
	delete iTest;
	}

void CTErrorAppUi::ConstructL()
	{
	CTestAppUi::ConstructL();
	iTest=new(ELeave) CAppTest(*iEikonEnv, this);
   	AutoTestManager().StartAutoTest();
	}

void CTErrorAppUi::TestResolveErrorsL()
	{
	CheckConfigL();
	iTest->TestResolveErrsL();
	}

void CTErrorAppUi::TestMultipleLangL()
	{
	CheckConfigL();
	iTest->TestMultipleLanguagesAcrossDrivesL();
	}

void CTErrorAppUi::TestErrorApplicationL()
	{
	iTest->TestErrorAppL();
	}

void CTErrorAppUi::TestErrorWithTitleL()
	{
	iTest->TestErrorWithTitleAppL();
	// The following test is a manual one (should be run manually if updates happen in the area)
	// iTest->TestErrorWithTitleManuallyL();
	}

void CTErrorAppUi::ProfileL()
	{
	CheckConfigL();
	iTest->TimeResolveErrsL();
	}

void CTErrorAppUi::TestAllL()
	{
	CheckConfigL();
	iTest->TestResolveAllL();
	}

void CTErrorAppUi::OOMTestsL()
	{
	CheckConfigL();
	iTest->TestOOML();
	}

void CTErrorAppUi::TestStandardAPIL()
	{
	CheckConfigL();
	iTest->RunStandardAPIL();
	}

void CTErrorAppUi::CheckConfigL()
	{
	// checks whether TError_Test* resource have been moved to RAM...
	DoCheckConfigL(EResFile1);
	DoCheckConfigL(EResFile2);
	DoCheckConfigL(EResFile3);
	DoCheckConfigL(EResFile4);
	DoCheckConfigL(EResFile5);
	}

void CTErrorAppUi::DoCheckConfigL(TTErrorResFile aFile)
	{
   // Check entry for resource filename is available to ensure that res file has been copied to RAM.
	TFileName fileName;
	ResFileFullName(fileName, aFile);

	TEntry entry;
	if(iEikonEnv->FsSession().Entry(fileName, entry) != KErrNone)
		{
		ERR_PRINTF2(_L("test resource files ('%S') missing from C: - test(s) cannot be run!"), &fileName);
		TEST(EFalse);
		}
	}

void CTErrorAppUi::RunTestStepL(TInt aNumStep)
	{
	TRAPD(err, DoRunTestStepL(aNumStep));
	if(err==KLeaveExit)
		{
		User::Leave(err);	// Complete - success.
		}
	if(err != KErrNone)
		{
		ERR_PRINTF3(_L("test step '%d' failed with error '%d'!"), aNumStep, err);
		TEST(EFalse);
		}
	}

	
void CTErrorAppUi::DoRunTestStepL(TInt aNumStep)
	{
	switch(aNumStep)
		{
		case 1:
		SetTestStepID(_L("UIF-errorstep-TestResolveErrsL"));
		INFO_PRINTF1(_L("test case 1: Test resolve error..."));
		TestResolveErrorsL();
		INFO_PRINTF1(_L("...completed!\n"));
		RecordTestResultL();
		break;
		
		case 2:
		SetTestStepID(_L("UIF-errorstep-TimeResolveErrsL"));
		INFO_PRINTF1(_L("test case 2: Time resolve error..."));
		ProfileL();
		INFO_PRINTF1(_L("...completed!\n"));
		RecordTestResultL();
		break;
		
		case 3:
		SetTestStepID(_L("UIF-errorstep-TestResolveAllL"));
		INFO_PRINTF1(_L("test case 3: Test backup error files..."));
		TestAllL();
		INFO_PRINTF1(_L("...completed!\n"));
		RecordTestResultL();
		break;
		
		case 4:
#ifdef TEST_OOM
		SetTestStepID(_L("UIF-errorstep-TestOOML"));
		INFO_PRINTF1(_L("test case 4: Test OOM failures..."));
		OOMTestsL();
		INFO_PRINTF1(_L("...completed!\n"));
		RecordTestResultL();
#endif
		break;
		
		case 5:
		SetTestStepID(_L("UIF-errorstep-RunStandardAPIL"));
		INFO_PRINTF1(_L("test case 5: Test standard API..."));
		TestStandardAPIL();
		INFO_PRINTF1(_L("...completed!\n"));
		RecordTestResultL();
		break;
		
		case 6:
		SetTestStepID(_L("UIF-errorstep-TestMultipleLanguagesAcrossDrivesL"));
		INFO_PRINTF1(_L("test case 6: Test resolve error multiple language..."));
		TestMultipleLangL();
		INFO_PRINTF1(_L("...completed!\n"));
		RecordTestResultL();
		break;

		case 7:
		SetTestStepID(_L("UIF-UIKON-0006"));
		INFO_PRINTF1(_L("test case 7: Test Error Application..."));
		TestErrorApplicationL();
		INFO_PRINTF1(_L("...completed!\n"));
		RecordTestResultL();
		break;
		
		case 8:
		SetTestStepID(_L("UIF-UIKON-0009"));
		INFO_PRINTF1(_L("test case 8: Test Error text with title..."));
		TestErrorWithTitleL();
		INFO_PRINTF1(_L("...completed!\n"));
		RecordTestResultL();
		CloseTMSGraphicsStep();
		break;

		case 9:
		AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
		break;
		
		default:
		break;
		}
	}

 
//
//
// 						class CTErrorStep
//
//

void CTErrorStep::FindRemovableMediaL(TDriveUnit& aDriveUnit)
	{
#ifdef __WINS__
 	aDriveUnit = EDriveX;
#else
	// The removable media is expected at D: on NAND ROM and at E: on normal ROMs.
	// The following code works on techview but not guaranteed to work on all platforms. 
	RFs fs;
	User::LeaveIfError(fs.Connect());

	TDriveInfo driveInfo;
	TInt error = fs.Drive(driveInfo, EDriveD);
	if(error == KErrNone && ((driveInfo.iDriveAtt & KDriveAttRemovable) != 0))
		{
	 	aDriveUnit = EDriveD; 	 	// Use drive D
	 	}
	 else
	 	{
		error = fs.Drive(driveInfo, EDriveE);
		if(error == KErrNone && ((driveInfo.iDriveAtt & KDriveAttRemovable) != 0))
			{
		 	aDriveUnit = EDriveE;	// Use drive E
		 	}
		}
	fs.Close();		
#endif
	}
		
void CTErrorStep::SetupErrorResFilesL()
	{
	// Create target path for resource files
	TInt err = iUtils.CreateDirectoryL(KLitV2ResFilePath);
	if(err != KErrNone && err != KErrAlreadyExists)
		{
		ERR_PRINTF2(_L("Create directory '%S' failed"), KLitV2ResFilePath);
		User::LeaveIfError(err);
		}
		
	// Delete any previous file from the test if any
	TParse parse;
	TBuf<128> path = KLitV2ResFilePath();
	User::LeaveIfError(parse.Set(KResFileWild, &path, NULL));
	err = iUtils.DeleteFileUsingWildcardL(parse.FullName());
	if((err != KErrNone) && (err != KErrNotFound) && (err != KErrPathNotFound))
		{
		ERR_PRINTF2(_L("DeleteFileUsingWildcardL for '%S' failed"), &parse.FullName());
		User::LeaveIfError(err);
		}
	
	// Copy error resource files to target path previously created.
	TFileName src;
	TFileName trg;
	for(TInt index=EResFile1; index<=EResFile5; ++index)
		{
		src.Format(KSrcErrorResFileFmt, TTErrorResFile(index));
		trg.Format(KTrgErrorResFileFmt, TTErrorResFile(index));
		err = iUtils.CopyFileL(src,trg);
		if(err != KErrNone)
			{
			ERR_PRINTF2(_L("Copying resource file '%S' failed"), &src);
			User::LeaveIfError(err);
			}
		}
	}


void CTErrorStep::SetupMultipleLangResFilesL()
	{
	// Copy files to target path in C: drive
	User::LeaveIfError(iUtils.CopyFileL(KTErrorLang1Src, KTErrorLang1Tgt));
	User::LeaveIfError(iUtils.CopyFileL(KTErrorLang3Src, KTErrorLang3Tgt));
	User::LeaveIfError(iUtils.CopyFileL(KTErrorLang6Src, KTErrorLang6Tgt));

	// Find where the removable media is (can vary on hardware builds)
	TDriveUnit drive;
	FindRemovableMediaL(drive);

	// Create target directory in removable drive
	TBuf<128> bufName;
	bufName = drive.Name();
	bufName.Append(KTErrorLang2Tgt);
	TInt err = iUtils.CreateDirectoryL(bufName);
	if(err != KErrNone && err != KErrAlreadyExists)
		{
		ERR_PRINTF2(_L("Create directory '%S' in removable media failed"), &bufName);
		User::LeaveIfError(err);
		}

	// Copy files to removable drive
	User::LeaveIfError(iUtils.CopyFileL(KTErrorLang2Src, bufName));
	bufName.Zero();
	bufName = drive.Name();
	bufName.Append(KTErrorLang4Tgt);
	User::LeaveIfError(iUtils.CopyFileL(KTErrorLang4Src, bufName));
	bufName.Zero();
	bufName = drive.Name();
	bufName.Append(KTErrorLang5Tgt);
	User::LeaveIfError(iUtils.CopyFileL(KTErrorLang5Src, bufName));
	bufName.Zero();
	bufName = drive.Name();
	bufName.Append(KTErrorLang7Tgt);
	User::LeaveIfError(iUtils.CopyFileL(KTErrorLang7Src, bufName));
	}

void CTErrorStep::CleanUpResFilesL()
	{
	// Delete error rsc files in C: drive (accordingly, we remove the read-only attr kept from rom)
	// They need to be unlocked first
	CBaBackupSessionWrapper* backupSession = CBaBackupSessionWrapper::NewL();
	CleanupStack::PushL(backupSession);
	TFileName fileName;
	for(TInt index=EResFile1; index<=EResFile5; ++index)
		{
		ResFileFullName(fileName, TTErrorResFile(index));
		backupSession->CloseFileL(fileName, MBackupObserver::EReleaseLockNoAccess);
		User::After(100000); // wait 0.1s to allow the files to be closed
		User::LeaveIfError(iUtils.SetReadOnly(fileName, 0));	
		User::LeaveIfError(iUtils.DeleteFileL(fileName));
		}
	CleanupStack::PopAndDestroy(backupSession);

	// Delete error lang rsc files in C: drive (accordingly, we remove the read-only attr kept from rom)
	User::LeaveIfError(iUtils.SetReadOnly(KTErrorLang1Tgt, 0));	
	User::LeaveIfError(iUtils.DeleteFileL(KTErrorLang1Tgt));

	User::LeaveIfError(iUtils.SetReadOnly(KTErrorLang3Tgt, 0));	
	User::LeaveIfError(iUtils.DeleteFileL(KTErrorLang3Tgt));
	
	User::LeaveIfError(iUtils.SetReadOnly(KTErrorLang6Tgt, 0));	
	User::LeaveIfError(iUtils.DeleteFileL(KTErrorLang6Tgt));

	// Find where the removable media is (can vary on hardware builds)
	TDriveUnit drive;
	FindRemovableMediaL(drive);

	// Delete files in removable drive (accordingly, we remove the read-only attr kept from rom)
	TBuf<128> bufName;
	bufName = drive.Name();
	bufName.Append(KTErrorLang2Tgt);
	User::LeaveIfError(iUtils.SetReadOnly(bufName, 0));	
	User::LeaveIfError(iUtils.DeleteFileL(bufName));

	bufName.Zero();
	bufName = drive.Name();
	bufName.Append(KTErrorLang4Tgt);
	User::LeaveIfError(iUtils.SetReadOnly(bufName, 0));	
	User::LeaveIfError(iUtils.DeleteFileL(bufName));

	bufName.Zero();
	bufName = drive.Name();
	bufName.Append(KTErrorLang5Tgt);
	User::LeaveIfError(iUtils.SetReadOnly(bufName, 0));	
	User::LeaveIfError(iUtils.DeleteFileL(bufName));

	bufName.Zero();
	bufName = drive.Name();
	bufName.Append(KTErrorLang7Tgt);
	User::LeaveIfError(iUtils.SetReadOnly(bufName, 0));	
	User::LeaveIfError(iUtils.DeleteFileL(bufName));
	}
	
void CTErrorStep::ConstructAppL(CEikonEnv* aCoe)
	{ // runs inside a TRAP harness
	aCoe->ConstructL();
	CTErrorAppUi* appUi= new (ELeave) CTErrorAppUi(this);
	aCoe->SetAppUi(appUi);
	appUi->ConstructL();
	}

CTErrorStep::~CTErrorStep()
	{
	}

CTErrorStep::CTErrorStep()
	{
	SetTestStepName(KTErrorStep);
	}

TVerdict CTErrorStep::doTestStepL()
	{
	INFO_PRINTF1(_L("Test ErrorStep started...."));
	PreallocateHALBuffer();

	__UHEAP_MARK;

	// Connect to the utils server (contains Tcb capabilities for copy/delete ops in \resource\...)
	User::LeaveIfError(iUtils.Connect());

	// Setup of error resource files
	TRAPD(ret, SetupErrorResFilesL());
	INFO_PRINTF2(_L("Setup of error resource files completed with return '%d'"), ret);
	TEST(ret == KErrNone);
	
	// Setup of MultilpeLanguage resource files
	TRAP(ret, SetupMultipleLangResFilesL());
	INFO_PRINTF2(_L("Setup of MultilpeLanguage resource files completed with return '%d'\n"), ret);
	TEST(ret == KErrNone);
	

	CEikonEnv* coeEnv=new CEikonEnv;
	TEST(coeEnv!=NULL);
	if (coeEnv==NULL)
		{
		SetTestStepResult(EFail);
		return TestStepResult();
		}
		
	TRAPD(error, ConstructAppL(coeEnv));
	TEST(error==KErrNone);
	if (error!=KErrNone)
		{
		SetTestStepResult(EFail);
		return TestStepResult();
		}

	// Perform the tests...
	coeEnv->ExecuteD();

	// Clean-up all resource files copied around
	TRAP(ret, CleanUpResFilesL());
	INFO_PRINTF2(_L("Clean-up of resource files completed with return '%d'"), ret);
	TEST(ret == KErrNone);

	iUtils.Close();
	REComSession::FinalClose();	
	__UHEAP_MARKEND;

	INFO_PRINTF1(_L("....test ErrorStep finished!"));
	return TestStepResult();
	}


