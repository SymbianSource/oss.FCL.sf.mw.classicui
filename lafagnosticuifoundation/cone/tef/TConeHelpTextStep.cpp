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
//

/**
 @file
 @test
 @internalComponent - Internal Symbian test code 
*/

//#include <coemain.h>
//#include <bautils.h>
//#include <apacmdln.h> 
//#include <fbs.h>
//#include <imageconversion.h>
//#include <bitmaptransforms.h>
#include <coehelp.h>
#include "TConeHelpTextStep.h"



/**
  Single Argument Constructor for CConeHelpTextTestAppUi class.\n
*/
CConeHelpTextTestAppUi::CConeHelpTextTestAppUi(CTmsTestStep* aStep) :
CTestCoeAppUi(aStep)
{}
/**
  Destructor for CConeHelpTextTestAppUi class.\n
*/
CConeHelpTextTestAppUi::~CConeHelpTextTestAppUi()
{}

/**
  Second phase Constructor for CConeHelpTextTestAppUi class.\n
  Invokes the base class CTestCoeAppUi second phase constructor.\n
  Executes the testcases asynchronously using Autotest Manager.\n
*/
void CConeHelpTextTestAppUi::ConstructL()
	{
	CTestCoeAppUi::ConstructL();
	
	AutoTestManager().StartAutoTest();
	}

/**
   @SYMTestCaseID		    UIF-CONE-0016

   @SYMTestCaseDesc 	    Test TCoeHelpContext::IsNull() returns ETrue when TCoeHelpContext
   							has Null values, and false otherwise.
  
   @SYMTestPriority   	    Critical
   
   @SYMTestType				Unit Test
  
   @SYMTestStatus 	  	    Implemented
    
   @SYMTestActions  	    Create null TCoeHelpContext (using default constructor)
   							Test IsNull() returns true
   							Set iMajor to non null value
   							Test IsNull() returns false
   							Set iMajor back to null
   							Set iContext to null
   							Test IsNull() returns false
   
   @SYMTestExpectedResults  IsNull returns false when either iMajor or iContext is non
   							null, and true if both are null.
 */
void CConeHelpTextTestAppUi::TestCase01()
	{
	INFO_PRINTF1(_L("UIF-CONE-0016 - test case start"));
	TCoeHelpContext help;

	INFO_PRINTF1(_L("Test IsNull() returns ETrue when default constructor is used."));
	TBool ret = help.IsNull();
	TEST(ret!=EFalse);

	INFO_PRINTF1(_L("Test IsNull() returns EFalse when uid has been set."));
	TUid testUid(TUid::Uid(0x12345678));
	help.iMajor = testUid;
	ret = help.IsNull();
	TEST(ret==EFalse);

	INFO_PRINTF1(_L("Test IsNull() returns EFalse when context has been set."));
	help.iMajor = KNullUid;
	_LIT(KTestContext,"Test Context");
	TBuf<12> testContext(KTestContext);
	help.iContext = testContext;
	ret = help.IsNull();
	TEST(ret==EFalse);
	INFO_PRINTF1(_L("UIF-CONE-0016 - test case end"));
	}

/**
   @SYMTestCaseID		    UIF-CONE-0017

   @SYMTestCaseDesc 	    Test TCoeHelpContext(TUid aMajor,const TDesC& aContext) constructor
   							sets the member variables correctly.
  
   @SYMTestPriority   	    Critical
   
   @SYMTestType				Unit Test
  
   @SYMTestStatus 	  	    Implemented
    
   @SYMTestActions  	    Call the constructor with aMajor set to a uid of 0x12345678 and
   							aContext to "Test Context"
   
   @SYMTestExpectedResults  Check iMajor has been set to 0x12345678 and iContext has been
   							set to "Test Context"
 */
void CConeHelpTextTestAppUi::TestCase02()
	{
	INFO_PRINTF1(_L("UIF-CONE-0017 - test case start"));
	TUid testUid(TUid::Uid(0x12345678));
	_LIT(KTestContext,"Test Context");
	TBuf<12> testContext(KTestContext);
	TCoeHelpContext help(testUid, testContext);
	INFO_PRINTF1(_L("Test the constructor set the member variables"));
	TEST(help.iMajor==testUid);
	TEST(help.iContext==testContext);
	INFO_PRINTF1(_L("UIF-CONE-0017 - test case end"));
	}

/**
   @SYMTestCaseID		    UIF-CONE-0018

   @SYMTestCaseDesc 	    Test TCoeHelpContext operator== reports true when two
   							TCoeHelpContexts are identical, and false otherwise.
  
   @SYMTestPriority   	    Critical
   
   @SYMTestType				Unit Test
  
   @SYMTestStatus 	  	    Implemented
    
   @SYMTestActions  	    Create two identical TCoeHelpContext with Major set to
   							0x12345678, and Contest set to "Test Context"
   							Compare using ==
   							Set iMajor to KNullUid
   							Compare
   							Set iMajor back to 0x12345678
   							Set iContext to KNullDesC
   							Compare
   							Set iMajor and iContext to null
   							Compare
   
   @SYMTestExpectedResults  Operator== returns true when both Contexts are identical, and
   							false otherwise
 */
void CConeHelpTextTestAppUi::TestCase03()
	{
	INFO_PRINTF1(_L("UIF-CONE-0018 - test case start"));
	TUid testUid(TUid::Uid(0x12345678));
	_LIT(KTestContext,"Test Context");
	TBuf<12> testContext(KTestContext);
	TCoeHelpContext help1(testUid, testContext);
	TCoeHelpContext help2(testUid, testContext);
	INFO_PRINTF1(_L("Test operator== returns true when both help contexts are the same"));
	TEST(help1==help2);
	help1.iMajor=KNullUid;
	INFO_PRINTF1(_L("Test operator== returns false when iMajor is different"));
	TEST((help1==help2)==EFalse);
	help1.iMajor=testUid;
	TEST(help1==help2);
	help1.iContext=KNullDesC;
	INFO_PRINTF1(_L("Test operator== returns false when iContext is different"));
	TEST((help1==help2)==EFalse);
	help1.iMajor=KNullUid;
	INFO_PRINTF1(_L("Test operator== returns false when both iMajor and iContext is different"));
	TEST((help1==help2)==EFalse);
	INFO_PRINTF1(_L("UIF-CONE-0018 - test case end"));
	}

/**
   @SYMTestCaseID		    UIF-CONE-0019

   @SYMTestCaseDesc 	    Test TCoeHelpContext operator!= reports false when two
   							TCoeHelpContexts are identical, and true otherwise.
  
   @SYMTestPriority   	    Critical
   
   @SYMTestType				Unit Test
  
   @SYMTestStatus 	  	    Implemented
    
   @SYMTestActions  	    Create two identical TCoeHelpContext with Major set to
   							0x12345678, and Contest set to "Test Context"
   							Compare using !=
   							Set iMajor to KNullUid
   							Compare
   							Set iMajor back to 0x12345678
   							Set iContext to KNullDesC
   							Compare
   							Set iMajor and iContext to null
   							Compare
   
   @SYMTestExpectedResults  Operator!= returns false when both Contexts are identical, and
   							true otherwise
 */
void CConeHelpTextTestAppUi::TestCase04()
	{
	INFO_PRINTF1(_L("UIF-CONE-0019 - test case start"));
	TUid testUid(TUid::Uid(0x12345678));
	_LIT(KTestContext,"Test Context");
	TBuf<12> testContext(KTestContext);
	TCoeHelpContext help1(testUid, testContext);
	TCoeHelpContext help2(testUid, testContext);
	INFO_PRINTF1(_L("Test operator!= returns false when both help contexts are the same"));
	TEST((help1!=help2)==EFalse);
	help1.iMajor=KNullUid;
	INFO_PRINTF1(_L("Test operator!= returns true when iMajor is different"));
	TEST(help1!=help2);
	help1.iMajor=testUid;
	TEST(help1==help2);
	help1.iContext=KNullDesC;
	INFO_PRINTF1(_L("Test operator!= returns true when iContext is different"));
	TEST(help1!=help2);
	help1.iMajor=KNullUid;
	INFO_PRINTF1(_L("Test operator!= returns true when both iMajor and iContext is different"));
	TEST(help1!=help2);
	INFO_PRINTF1(_L("UIF-CONE-0019 - test case end"));
	}


/**
   Auxiliary Function for all Test Cases.\n
  
   The method is an override from CTestCoeAppUi.\n
   This function is called asynchronously by RunL function of the
   AutotestManager after previous test case is executed.\n
   Generates the KeyDown event and KeyUp Events alternatively.\n
 */
 
void CConeHelpTextTestAppUi::RunTestStepL(TInt aStepNum)
	{
	switch(aStepNum)
		{
		case 1:
			SetTestStepID(_L("UIF-CONE-0016"));
			TestCase01();	
			RecordTestResultL();
			break;
		case 2:
			SetTestStepID(_L("UIF-CONE-0017"));
			TestCase02();	
			RecordTestResultL();
			break;
		case 3:
			SetTestStepID(_L("UIF-CONE-0018"));
			TestCase03();
			RecordTestResultL();
			break;
		case 4:
			SetTestStepID(_L("UIF-CONE-0019"));
			TestCase04();
			RecordTestResultL();
			CloseTMSGraphicsStep();
			break;
		default:
			AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
			break;
		}
	}

/**
  Completes the construction of the Control Environment(CCoeEnv object).\n
  Instantiates the CConeHelpTextTestAppUi class which serves as a AppUi class.\n
  Sets the CConeHelpTextTestAppUi object as the application's user interface object.\n
  Invokes the second phase constructor of the application's UI.\n
*/
void CTConeHelpTextStep::ConstructAppL(CCoeEnv* aCoe)
	{ // runs inside a TRAP harness
	aCoe->ConstructL();
	CConeHelpTextTestAppUi* appUi= new (ELeave) CConeHelpTextTestAppUi(this);
	aCoe->SetAppUi(appUi);
	appUi->ConstructL();
	}
/**
  Constructor for CTConeHelpTextStep class.\n
  Sets the test step name.\n
*/
CTConeHelpTextStep::CTConeHelpTextStep()
	{
	SetTestStepName(KTConeHelpTextStep);
	}
/**
  Destructor for CTConeHelpTextStep class.\n
*/
CTConeHelpTextStep::~CTConeHelpTextStep()
{}

/**
  Entry function for CTCone0 Test Step.\n
  Sets up the control environment.\n
  Constructs and Launches the CTCone0 Test application.\n
 
*/
TVerdict CTConeHelpTextStep::doTestStepL() // main function called by E32
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


