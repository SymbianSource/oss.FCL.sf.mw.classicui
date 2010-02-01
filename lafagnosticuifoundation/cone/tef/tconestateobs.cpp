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
 @internalComponent - Internal Symbian test code
 @test
*/

#include <e32std.h>
#include "COEAUI.H"
#include "tconestateobs.h"
#include "statecon.h"

/**
   Handles calls from the Mop interface on the control enviroment
 */
TInt CStepStateObsEnv::HandleControlStateChange(CCoeControl* aControl,MCoeControlStateObserver::TCoeState aState)
	{
	if (iPassOn)
		return iPassOn->ControlStateChangePassOn(aControl,aState);
	return KErrNone;
	}

/**
   Returns the Mop interface provided by this control enviroment
 */
TTypeUid::Ptr CStepStateObsEnv::MopSupplyObject(TTypeUid aId)
	{
	if (aId.iUid==MCoeControlStateObserver::ETypeId && iRetObserver)
		return aId.MakePtr(static_cast<MCoeControlStateObserver*>(this));
	return CCoeEnv::MopSupplyObject(aId);
	}

/**
   Constructor for the APP UI for this test
 */
CConeStateObsAppUi::CConeStateObsAppUi(CTmsTestStep* aStep,CStepStateObsEnv* aCoe)
	: CTestCoeAppUi(aStep), iCoe(aCoe)
	{}

/** 
   Destructor for the APP UI for this test
 */
CConeStateObsAppUi::~CConeStateObsAppUi()
	{
	delete iStateObCnt;
	}

/**
   Creates font and control for this test and sets state need by all sub-tests
 */
void CConeStateObsAppUi::ConstructL()
	{
	CTestCoeAppUi::ConstructL();
	AutoTestManager().StartAutoTest();
	//Creating the first font allocates memory that is never deleted so must do this outside heap checks
	CFbsFont* font=iCoe->CreateScreenFontL(CStateObserverControl::iFontSpec);
	iCoe->ReleaseScreenFont(font);
	iStateObCnt=new(ELeave) CStateObserverControl();
	iStateObCnt->ConstructL();
	iStateObCnt->SetEnv(iCoe);
	iCoe->SetPassOn(iStateObCnt);
	iCoe->SetReturnObserver(ETrue);
	}

/**
   Do a sub test
 */
void CConeStateObsAppUi::DoStateObserverTest()
	{
	__UHEAP_MARK;
	TInt failAt=iStateObCnt->DoTest();
	if (failAt>0)
		{
		TEST(EFalse);
		_LIT(KLog,"StateObserverTest failed on subtest: %d");
		INFO_PRINTF2(KLog,failAt);
		}
	__UHEAP_MARKEND;
	}

/**
   @SYMTestCaseID UIF-CONE-0029

   @SYMCR CR1251

   @SYMTestCaseDesc Tests calling MakeVisible or SetDimmed calls the new Mop interface
   when only the control enviroment provides the relevant Mop interface

   @SYMTestPriority High

   @SYMTestStatus Implemented

   @SYMTestActions Makes many calls to MakeVisible or SetDimmed in different situations 
   and checks if the new Mop interface is called or not on each time.

   @SYMTestExpectedResults The new interface is called if there is a change in the controls state

   @SYMTestType : Unit Test
 */
void CConeStateObsAppUi::StateObserverTestEnvOnly()
	{
	iStateObCnt->SetReturnObserver(CStateObserverControl::ENoObserver);
	iStateObCnt->SetRecievers(EFalse,ETrue);
	DoStateObserverTest();
	}

/**
   @SYMTestCaseID UIF-CONE-0030

   @SYMCR CR1251

   @SYMTestCaseDesc Tests calling MakeVisible or SetDimmed calls the new Mop interface
   when both the control the control enviroment provides the relevant Mop interface

   @SYMTestPriority High

   @SYMTestStatus Implemented

   @SYMTestActions Makes many calls to MakeVisible or SetDimmed in different situations 
   and checks if the new Mop interface is called or not on each time.

   @SYMTestExpectedResults The new interface is called if there is a change in the controls state

   @SYMTestType : Unit Test
 */
void CConeStateObsAppUi::StateObserverTestBoth()
	{
	iStateObCnt->ResetCount();
	iStateObCnt->SetReturnObserver(CStateObserverControl::EObserver);
	iStateObCnt->SetRecievers(ETrue,ETrue);
	DoStateObserverTest();
	}

/**
   @SYMTestCaseID UIF-CONE-0031

   @SYMCR CR1251

   @SYMTestCaseDesc Tests calling MakeVisible or SetDimmed calls the new Mop interface
   when both the control the control enviroment provides the relevant Mop interface but
   do so using the same object

   @SYMTestPriority High

   @SYMTestStatus Implemented

   @SYMTestActions Makes many calls to MakeVisible or SetDimmed in different situations 
   and checks if the new Mop interface is called or not on each time.

   @SYMTestExpectedResults The new interface is called if there is a change in the controls state

   @SYMTestType : Unit Test
 */
void CConeStateObsAppUi::StateObserverTestBothAtEnv()
	{
	iStateObCnt->ResetCount();
	iStateObCnt->SetReturnObserver(CStateObserverControl::ECoeEnvObserver);
	iStateObCnt->SetRecievers(EFalse,ETrue);
	DoStateObserverTest();
	}

/**
   Function to call each of the tests in turn
 */
void CConeStateObsAppUi::RunTestStepL(TInt aStepNum)
	{
	_LIT(KTest1,"Test 1: MCoeControlStateObserver event recieved through control enviroment only");
	_LIT(KTest2,"Test 2: MCoeControlStateObserver event recieved through both control enviroment and control");
	_LIT(KTest3,"Test 3: MCoeControlStateObserver event recieved through both control enviroment and control but by the same object");
	switch(aStepNum)
		{
	case 1:
		SetTestStepID(_L("UIF-CONE-0029"));		
		INFO_PRINTF1(KTest1);
		StateObserverTestEnvOnly();
		RecordTestResultL();		
		break;
	case 2:
		SetTestStepID(_L("UIF-CONE-0030"));		
		INFO_PRINTF1(KTest2);
		StateObserverTestBoth();
		RecordTestResultL();		
		break;
	case 3:
		SetTestStepID(_L("UIF-CONE-0031"));		
		INFO_PRINTF1(KTest3);
		StateObserverTestBothAtEnv();
		RecordTestResultL();
		CloseTMSGraphicsStep();
		break;
	default:
		AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
		break;
		}
	}

/**
   Constructor for the main test class
 */
CTConeStateObs::CTConeStateObs()
	{
	SetTestStepName(KTConeStateObs);
	}

/**
   Finish creating the Control Enviroment and create the App UI.
 */
void CTConeStateObs::ConstructL()
	{
	//Would like to do this line here but this gives a panic in the cleanup stack code.
	//iCoe=new(ELeave) CStepStateObsEnv();
	iCoe->ConstructL();
	CConeStateObsAppUi* appUi=new(ELeave) CConeStateObsAppUi(this,iCoe);
	iCoe->SetAppUi(appUi);
	appUi->ConstructL();
	}

/**
   Entry function for CTConeStateObs Test Step.
 */
TVerdict CTConeStateObs::doTestStepL()
	{
	INFO_PRINTF1(_L("Test Started"));
	iCoe=new(ELeave) CStepStateObsEnv();
	TRAPD(err,ConstructL());
	if (!err)
		iCoe->ExecuteD();
	else
		{
		SetTestStepResult(EFail);
		delete iCoe;
		}
	INFO_PRINTF1(_L("Test Finished"));
	return TestStepResult();
	}
