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
// The test step creates a sample application and uses AutoTest Manager
// to create KeyUp and KeyDown Events asynchronously. These events are then handled
// by the appropriate handlers.\n
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code 
*/
#include <coeaui.h>
#include <coemain.h>
#include <coedef.h>
#include <coesndpy.h>
#include <basched.h>
#include <bassnd.h>
#include <ecom/ecom.h>
#include "TCone0Step.h"

/**
  Single Argument Constructor for CCone0TestAppUi class.\n
*/
CCone0TestAppUi::CCone0TestAppUi(CTmsTestStep* aStep) :
CTestCoeAppUi(aStep)
{}
/**
  Destructor for CCone0TestAppUi class.\n
*/
CCone0TestAppUi::~CCone0TestAppUi()
{}

/**
  Second phase Constructor for CCone0TestAppUi class.\n
  Invokes the base class CTestCoeAppUi second phase constructor.\n
  Executes the testcases asynchronously using Autotest Manager.\n
*/
void CCone0TestAppUi::ConstructL()
	{
	CTestCoeAppUi::ConstructL();
	
	AutoTestManager().StartAutoTest();
	}

/**
   Auxiliary Function for all Test Cases.\n
  
   The method is an override from CTestCoeAppUi.\n 
   
 */
 
void CCone0TestAppUi::Beep(TInt /*aFrequency*/)
	{
	CoeSoundPlayer::PlaySound(TBaSystemSoundType(KUidSystemSoundEvent));
	}
	

/**
   Auxiliary Function for all Test Cases
  
   The method is an override from CTestCoeAppUi. 
   The function handles the following key events.\n
   Key Up Event and Key down Event.\n
 */
 	
TKeyResponse CCone0TestAppUi::HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
	TKeyResponse ret=EKeyWasNotConsumed;
    Beep(1760+(aType-EEventKey)*220);
    if (aType==EEventKey && aKeyEvent.iCode==CTRL('e'))
		{
		CBaActiveScheduler::Exit();
		ret=EKeyWasConsumed;
		}
	return ret;
    }
/**
  Handles the foreground events by generating a Beep.\n
*/
void CCone0TestAppUi::HandleForegroundEventL(TBool aForeground)
    {
    Beep(aForeground? 1500: 1200);
    }


/**
   @SYMTestCaseID UIF-TCCone0TestAppUi-TestStepKeyDownL
  
   @SYMPREQ
 
   @SYMTestPriority High
 
   @SYMTestStatus Implemented
  
   @SYMTestActions The method calls CCone0TestAppUi::HandleKeyEventL() to test KeyDown Event
  
   @SYMTestExpectedResults. This test is manually verified, the system will play a beep.
  
   @SYMTestType: CIT
 */
 
void CCone0TestAppUi::TestStepKeyDownL(TKeyEvent aKeyEvent)
	{
	INFO_PRINTF1(_L("Emulation the event KeyDown"));
	HandleKeyEventL(aKeyEvent,EEventKeyDown);
	}


/**
   @SYMTestCaseID UIF-TCCone0TestAppUi-TestStepKeyUpL
  
   @SYMPREQ
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method calls CCone0TestAppUi::HandleKeyEventL() to handle the KeyUp Event
   
   @SYMTestExpectedResults. This test is manually verified, the system will play a beep.
  
   @SYMTestType : CIT
 */
 
void CCone0TestAppUi::TestStepKeyUpL(TKeyEvent aKeyEvent)
	{
	INFO_PRINTF1(_L("Emulation the event KeyUp"));
	HandleKeyEventL(aKeyEvent,EEventKeyUp);
	}

/**
   Auxiliary Function for all Test Cases.\n
  
   The method is an override from CTestCoeAppUi.\n
   This function is called asynchronously by RunL function of the
   AutotestManager after previous test case is executed.\n
   Generates the KeyDown event and KeyUp Events alternatively.\n
 */
 
void CCone0TestAppUi::RunTestStepL(TInt aStepNum)
	{

	User::After(TTimeIntervalMicroSeconds32(1000000));
	
	TKeyEvent theKeyEvent = {0,0,0,0};
	switch(aStepNum)
		{
		case 1: 
		SetTestStepID(_L("UIF-TCCone0TestAppUi-TestStepKeyDownL"));	
		// follow on...
		case 3: case 5:
		TestStepKeyDownL(theKeyEvent);
		if( aStepNum == 5 )
			{
			RecordTestResultL();
			}
		break;
		
		case 2: 
		SetTestStepID(_L("UIF-TCCone0TestAppUi-TestStepKeyUpL"));
		// follow on...		
		case 4: case 6:
		TestStepKeyUpL(theKeyEvent);
		if( aStepNum == 6 )
			{		
			RecordTestResultL();
			CloseTMSGraphicsStep();
			}
		break;
		case 7:
			AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
		break;

		}
	}

/**
  Completes the construction of the Control Environment(CCoeEnv object).\n
  Instantiates the CCone0TestAppUi class which serves as a AppUi class.\n
  Sets the CCone0TestAppUi object as the application's user interface object.\n
  Invokes the second phase constructor of the application's UI.\n
*/
void CTCone0Step::ConstructAppL(CCoeEnv* aCoe)
	{ // runs inside a TRAP harness
	aCoe->ConstructL();
	CCone0TestAppUi* appUi= new (ELeave) CCone0TestAppUi(this);
	aCoe->SetAppUi(appUi);
	appUi->ConstructL();
	}
/**
  Constructor for CTCone0Step class.\n
  Sets the test step name.\n
*/
CTCone0Step::CTCone0Step()
	{
	SetTestStepName(KTCone0Step);
	}
/**
  Destructor for CTCone0Step class.\n
*/
CTCone0Step::~CTCone0Step()
{}

/**
  Entry function for CTCone0 Test Step.\n
  Sets up the control environment.\n
  Constructs and Launches the CTCone0 Test application.\n
 
*/
TVerdict CTCone0Step::doTestStepL() // main function called by E32
	{
	INFO_PRINTF1(_L("Test Started"));
	
	PreallocateHALBuffer();

	__UHEAP_MARK;

	CCoeEnv* coe=new(ELeave) CCoeEnv;
	TRAPD(err,ConstructAppL(coe));

	if (!err)
		coe->ExecuteD();
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


