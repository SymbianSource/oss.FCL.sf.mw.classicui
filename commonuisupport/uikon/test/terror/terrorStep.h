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
// The TError test app tests the extended error resolver.
// 
//

/**
 @file
 @test
 @internalComponent - Internal Symbian test code
*/

#if (!defined __TERROR_STEP_H__)
#define __TERROR_STEP_H__

#include <coecntrl.h>
#include <babackup.h>
#include "eikerror.h"

#include <test/testexecutestepbase.h>
#include "appfwk_test_AppUi.h"
#include "appfwk_test_utils.h"
#include "terrorapp.h"

/**
Resource files.
*/
enum TTErrorResFile
	{
	EResFile1 = 1,
	EResFile2,
	EResFile3,
	EResFile4,
	EResFile5
	};


//
//
// 						class CWait
//
//

/**
An Active Object class used to implement a delay for backing up the terror
 resource files.
*/
class CWait : public CActive
	{
public:
	static void WaitLD(TInt aIntervalMicroSeconds);
private:
	class CKeyEater : public CCoeControl
		{
	public:
		static CKeyEater* NewL();
		~CKeyEater();
	public: // from CCoeControl
		TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	private:
		CKeyEater();
		void ConstructL();
		};
private:
	CWait();
	void ConstructL(TInt aIntervalMicroSeconds);
	~CWait();
private: // from CActive
	void DoCancel();
	void RunL();
private:
	RTimer		iTimer;
	CKeyEater*	iKeyControl;
	};



//
//
// 						class CAppBackup
//
//

/**
Class initiates the backup operation.
*/
class CAppBackup : public CBase
	{
public:
	static CAppBackup* NewLC();
	~CAppBackup();
private:
	CAppBackup();
	void ConstructL();
	void CloseFileL(TTErrorResFile);
	void RestartFile(TTErrorResFile);
private:
	CBaBackupSessionWrapper* iBackupSession;
	};



class CTErrorAppUi;

//
//
// 						class CAppTest
//
//

/**
Class that performs all the test on extended error resolver.
*/
class CAppTest : public CBase
	{
public:
	CAppTest(CEikonEnv& aEnv, CTErrorAppUi* aAppUi);
	void TestResolveErrsL();
	void TimeResolveErrsL();
	void TestResolveAllL();
	void TestOOML();
	void RunStandardAPIL();
	void TestMultipleLanguagesAcrossDrivesL();
	void TestErrorAppL();
	void TestErrorWithTitleAppL();
	void TestErrorWithTitleManuallyL();
private:
	void TestErrTxtL(const TDesC& aErrText,const TDesC& aExpected) const;
	void TestResolveErrsL(CEikErrorResolver& aErrRes);
	void TimeResolveSingleErrL(TInt aErrCode, const TDesC& aTargetErrText, TUid uid);
	void TestResolveSingleErrL(TInt aErrCode, const TDesC& aTargetErrText, TUid uid);
	void InitTimerL();
	void StartTimer();
	void StopTimer();	
private:
	CEikonEnv& iEikEnv;
	CTErrorAppUi* iAppUi;
	TBool iOOMTesting;
	TUint32 iStartTime;
	TUint32 iEndTime;
	TInt iFreq;
	TInt64 iTotalTime;
	};



//
//
// 						class CTErrorAppUi
//
//

/**
 UI class for test class CTErrorStep.
*/
class CTErrorAppUi : public CTestAppUi
	{
public:
	CTErrorAppUi(CTmsTestStep* aStep);
	~CTErrorAppUi();
	void ConstructL();
private:
	void TestResolveErrorsL();
	void TestMultipleLangL();
	void ProfileL();
	void TestAllL();
	void OOMTestsL();
	void TestStandardAPIL();
	void CheckConfigL();
	void DoCheckConfigL(TTErrorResFile aFile);
	void RunTestStepL(TInt aNumStep);
	void DoRunTestStepL(TInt aNumStep);
	void TestErrorApplicationL();
	void TestErrorWithTitleL();
private:
	CAppTest* iTest;	
	};



//
//
// 						class CTErrorStep
//
//

/**
 Class tests the extended error resolver.
*/
class CTErrorStep : public CTmsTestStep
	{
public:
	CTErrorStep();
	~CTErrorStep();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CEikonEnv* aCoe);
private:
	void FindRemovableMediaL(TDriveUnit& aDriveUnit);
	void SetupErrorResFilesL();
	void SetupMultipleLangResFilesL();
	void CleanUpResFilesL();
private:
	RSmlTestUtils iUtils;

	};


_LIT(KTErrorStep,"TError");
#endif

