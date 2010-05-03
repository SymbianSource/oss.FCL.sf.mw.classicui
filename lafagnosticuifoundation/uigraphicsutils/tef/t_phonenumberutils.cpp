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


#include "t_phonenumberutils.h"
#include <eikenv.h>

/**
   Constructor
 */	
CT_PhoneNumberUtilsStep::CT_PhoneNumberUtilsStep()
	{
	// Call base class method to set up the human readable name for logging*/
	SetTestStepName(KT_PhoneNumberUtilsStep);
	}

/**
   Destructor
 */
CT_PhoneNumberUtilsStep::~CT_PhoneNumberUtilsStep()
	{
	}

TVerdict CT_PhoneNumberUtilsStep::doTestStepL()
	{
	INFO_PRINTF1(_L("Test Started"));
	__UHEAP_MARK;
	RunTestCases();
	__UHEAP_MARKEND;
	INFO_PRINTF1(_L("Test Finished"));
	return TestStepResult();
	}

void CT_PhoneNumberUtilsStep::RunTestCases()
	{
	SetTestStepID(_L("UIF-ETUL-0011"));
	ParsePhoneNumberForPPN();
	RecordTestResultL();
	SetTestStepID(_L("UIF-ETUL-0012"));
	ParsePhoneNumberForCCN();
	RecordTestResultL();
	SetTestStepID(_L("UIF-ETUL-0013"));
	ParsePhoneNumberForSMSNumber();
	RecordTestResultL();
	SetTestStepID(_L("UIF-ETUL-0014"));
	ParsePhoneNumberForPCN();
	RecordTestResultL();
	CloseTMSGraphicsStep();
	}

/**
   @SYMTestCaseID UIF-ETUL-0011

   @SYMREQ 7736
 
   @SYMTestCaseDesc Tests TulPhoneNumberUtils::Normalize() and  TulPhoneNumberUtils::IsValid() methods for 
   TulPhoneNumberUtils::EPlainPhoneNumber
  
   @SYMTestPriority High 
 
   @SYMTestStatus Implemented
  
   @SYMTestActions Calls TulPhoneNumberUtils::Normalize() and TulPhoneNumberUtils::IsValid() methods with 
   Valid and Invalid Plain Phone Number.
   
   @SYMTestExpectedResults The test checks whether
   1.  TulPhoneNumberUtils::Normalize() returns:
	   a. ETrue for Valid Plain Phone Number and normalizes the given Phone Number and
	   b. EFalse for Invalid Plain Phone Number. 
   2. TulPhoneNumberUtils::IsValid() returns:
   	   a. ETrue for Valid Plain Phone no.and 
   	   b. EFalse for Invalid Plain Phone no.
 */
void CT_PhoneNumberUtilsStep::ParsePhoneNumberForPPN()
    {
	INFO_PRINTF1(_L("Test to Parse PhoneNumber With Valid PlainPhoneNumber"));
    TBuf<KMaxTestBufferSize> number = _L("+46 345 34(34347) 42443 42"); // This should be a parseable Plain Phone Number
	TEST(TulPhoneNumberUtils::Normalize(number, TulPhoneNumberUtils::EPlainPhoneNumber));
	INFO_PRINTF2(_L("Normalized Phone No. is %S"), &number);
	
	number = _L("0500 -4990		00"); // This should be a parseable Plain Phone Number
	TEST(TulPhoneNumberUtils::Normalize(number, TulPhoneNumberUtils::EPlainPhoneNumber));
 	INFO_PRINTF2(_L("Normalized Phone No. is %S"), &number);

 	INFO_PRINTF1(_L("Test to Validate Plain PhoneNumber"));
  	number = _L("+46 40 45656546"); // This should be Valid Plain Phone Number
    TEST(TulPhoneNumberUtils::IsValid(number, TulPhoneNumberUtils::EPlainPhoneNumber));

    number = _L("46-40 45656546"); // This should be a Valid Plain Phone Number
    TEST((TulPhoneNumberUtils::IsValid(number, TulPhoneNumberUtils::EPlainPhoneNumber)));

  	INFO_PRINTF1(_L("Test to Parse PhoneNumber With Invalid PlainPhoneNumber"));
  	number = _L("p050-4872485"); // This should NOT be a parseable Plain Phone Number
	TEST(!(TulPhoneNumberUtils::Normalize(number, TulPhoneNumberUtils::EPlainPhoneNumber)));

  	number = _L("+0?50-4872485"); // This should NOT be a parseable Plain Phone Number
	TEST(!(TulPhoneNumberUtils::Normalize(number, TulPhoneNumberUtils::EPlainPhoneNumber)));

  	INFO_PRINTF1(_L("Parse phone no. with closing paranthesis at the first position of phone number"));
  	number = _L(")050-4872485"); // This should NOT be a parseable Plain Phone Number
	TEST(!(TulPhoneNumberUtils::Normalize(number, TulPhoneNumberUtils::EPlainPhoneNumber)));

	INFO_PRINTF1(_L("Parse phone no. with opening paranthesis at the last position of phone number"));
  	number = _L("050-4872485("); // This should NOT be a parseable Plain Phone Number
	TEST(!(TulPhoneNumberUtils::Normalize(number, TulPhoneNumberUtils::EPlainPhoneNumber)));

  	number = _L("/050-4872485"); // This should NOT be a parseable Plain Phone Number
	TEST(!(TulPhoneNumberUtils::Normalize(number, TulPhoneNumberUtils::EPlainPhoneNumber)));
    }

 /**
   @SYMTestCaseID UIF-ETUL-0012

   @SYMREQ 7736
 
   @SYMTestCaseDesc Tests TulPhoneNumberUtils::Normalize() and TulPhoneNumberUtils::IsValid() methods
   for TulPhoneNumberUtils::EContactCardNumber
  
   @SYMTestPriority High 
 
   @SYMTestStatus Implemented
  
   @SYMTestActions Calls TulPhoneNumberUtils::Normalize() method with Valid and Invalid Contact Card Number.
   Calls TulPhoneNumberUtils::IsValid() method with Valid and Invalid Contact Card Number.
   
   @SYMTestExpectedResults The test checks whether
   1. TulPhoneNumberUtils::Normalize() returns:
		a. ETrue for Valid Contact Card Number and normalizes the given Contact Card Number.
		b. EFalse for Invalid Contact Card Number.
   2. TulPhoneNumberUtils::IsValid() returns:
	   a. ETrue for Valid Contact Card Number and 
	   b. EFalse for Invalid Contact Card Number.
 */
 void CT_PhoneNumberUtilsStep::ParsePhoneNumberForCCN()
    {
  	INFO_PRINTF1(_L("Test to Parse PhoneNumber With Valid ContactCardNumber"));
  	TBuf<KMaxTestBufferSize> number = _L("*31*6(0)35/6546"); // This should be a parseable Contact Card Number
	TEST(TulPhoneNumberUtils::Normalize(number, TulPhoneNumberUtils::EContactCardNumber));
	INFO_PRINTF2(_L("Normalized Contact Card No. is %S"), &number);

   	INFO_PRINTF1(_L("Test to Validate ContactCardNumber"));
    number = _L("*31#0w(08)3111113"); // This should  be a Valid Contact Card Number
	TEST(TulPhoneNumberUtils::IsValid(number, TulPhoneNumberUtils::EContactCardNumber));

    number = _L("**3112213"); // This should be a Valid Contact Card Number
	TEST((TulPhoneNumberUtils::IsValid(number, TulPhoneNumberUtils::EContactCardNumber)));
	TEST((TulPhoneNumberUtils::Normalize(number, TulPhoneNumberUtils::EContactCardNumber)));
	INFO_PRINTF2(_L("Normalized Contact Card No. is %S"), &number);

    number = _L("##3113113"); // This should be a Valid Contact Card Number
	TEST((TulPhoneNumberUtils::IsValid(number, TulPhoneNumberUtils::EContactCardNumber)));
	TEST((TulPhoneNumberUtils::Normalize(number, TulPhoneNumberUtils::EContactCardNumber)));
	INFO_PRINTF2(_L("Normalized Contact Card No. is %S"), &number);

    number = _L("a(08)3111113"); // This should NOT be a Valid Contact Card Number
	TEST(!(TulPhoneNumberUtils::IsValid(number, TulPhoneNumberUtils::EContactCardNumber)));

	INFO_PRINTF1(_L("Test to Parse PhoneNumber With Invalid ContactCardNumber"));
    number = _L("*31*p#+46a35656546"); // This should NOT be a parseable Contact Card Number
	TEST(!(TulPhoneNumberUtils::Normalize(number, TulPhoneNumberUtils::EContactCardNumber)));
    }
    
/**
   @SYMTestCaseID UIF-ETUL-0013

   @SYMREQ 7736
 
   @SYMTestCaseDesc Tests TulPhoneNumberUtils::Normalize() and  TulPhoneNumberUtils::IsValid() methods for
   TulPhoneNumberUtils::ESMSNumber
  
   @SYMTestPriority High 
 
   @SYMTestStatus Implemented
  
   @SYMTestActions Calls TulPhoneNumberUtils::Normalize() and TulPhoneNumberUtils::IsValid() 
   methods with Valid and Invalid SMS number.
      
   @SYMTestExpectedResults The test checks whether 
   1. TulPhoneNumberUtils::Normalize() returns:
		a. ETrue for Valid SMS number and normalizes the given SMS number.
		b. EFalse for Invalid SMS number.
   2. TulPhoneNumberUtils::IsValid() returns:
	   a. ETrue for Valid SMS number and 
	   b. EFalse for Invalid SMS number.
 */
void CT_PhoneNumberUtilsStep::ParsePhoneNumberForSMSNumber()
   {
   INFO_PRINTF1(_L("Test to Validate SMS number"));
   TBuf<KMaxTestBufferSize> number = _L("12*3-45/345-24.3"); // This should be a Valid SMS number
   TEST(TulPhoneNumberUtils::IsValid(number, TulPhoneNumberUtils::ESMSNumber));
   
   TEST(TulPhoneNumberUtils::Normalize(number, TulPhoneNumberUtils::ESMSNumber));
   INFO_PRINTF2(_L("Normalized SMS No. is %S"), &number);

   if (KPhoneNoUtilsMaxNumbers < KMaxTestBufferSize)
        {
        // form number more than max number
        number.Zero();
        for (TInt i = 0; i <= KPhoneNoUtilsMaxNumbers; ++i)
            {
            number.Append('0' + i % 10);
            }
        // This should be a NOT Valid SMS number
        TEST(!(TulPhoneNumberUtils::IsValid(number, TulPhoneNumberUtils::ESMSNumber)));
        }
   
   number = _L(" "); // This should NOT be a Valid SMS numbernumber
   TEST(!(TulPhoneNumberUtils::IsValid(number, TulPhoneNumberUtils::ESMSNumber)));
   
   number = _L("(345345243"); // This should NOT be a Valid SMS numbernumber as there is no closing braces.
   TEST(!(TulPhoneNumberUtils::IsValid(number, TulPhoneNumberUtils::ESMSNumber)));

   TEST(!(TulPhoneNumberUtils::IsValid(number, TulPhoneNumberUtils::ESMSNumber)));
   TEST(!(TulPhoneNumberUtils::Normalize(number, TulPhoneNumberUtils::ESMSNumber)));
   }

/**
   @SYMTestCaseID UIF-ETUL-0014

   @SYMREQ 7736
 
   @SYMTestCaseDesc Tests TulPhoneNumberUtils::Normalize() and  TulPhoneNumberUtils::IsValid() methods for 
   TulPhoneNumberUtils::EPhoneClientNumber
  
   @SYMTestPriority High 
 
   @SYMTestStatus Implemented
  
   @SYMTestActions Calls TulPhoneNumberUtils::Normalize() and TulPhoneNumberUtils::IsValid() methods
   with Valid and Invalid Contact Phone Client number.
   
   @SYMTestExpectedResults The test checks whether 
   1. TulPhoneNumberUtils::Normalize() returns:
		a. ETrue for Valid Phone Client number and normalizes the given Phone Client number.
		b. EFalse for Invalid Phone Client number.
   2. TulPhoneNumberUtils::IsValid() returns:
	   a. ETrue for Valid Phone Client number and 
	   b. EFalse for Invalid Phone Client number.
 */
void CT_PhoneNumberUtilsStep::ParsePhoneNumberForPCN()
	{
   	INFO_PRINTF1(_L("Test to Validate PhoneClientNumber"));

   	TBuf<KMaxTestBufferSize> number = _L("1p23-4534w5-2*43#34"); // This should be a Valid Phone Client Number
	TEST(TulPhoneNumberUtils::IsValid(number, TulPhoneNumberUtils::EPhoneClientNumber));
    
    TEST(TulPhoneNumberUtils::Normalize(number, TulPhoneNumberUtils::EPhoneClientNumber));
    INFO_PRINTF2(_L("Normalized Phone Client Number is %S"), &number);

    number = _L("*5p6405656546"); // This should be a Valid Phone Client Number
    TEST((TulPhoneNumberUtils::IsValid(number, TulPhoneNumberUtils::EPhoneClientNumber)));

    number = _L("+*6405656546"); // This should be a Valid Phone Client Number
    TEST((TulPhoneNumberUtils::IsValid(number, TulPhoneNumberUtils::EPhoneClientNumber)));

    number = _L("+#64046"); // This should be a Valid Phone Client Number
    TEST((TulPhoneNumberUtils::IsValid(number, TulPhoneNumberUtils::EPhoneClientNumber)));

    number = _L("+p640 45656546"); // This should be a NOT Valid Phone Client Number
    TEST(!(TulPhoneNumberUtils::IsValid(number, TulPhoneNumberUtils::EPhoneClientNumber)));

    number = _L("#12a3-45345-243"); // This should NOT be a Valid Phone Client Number
	TEST(!(TulPhoneNumberUtils::IsValid(number, TulPhoneNumberUtils::EPhoneClientNumber)));
    TEST(!(TulPhoneNumberUtils::Normalize(number, TulPhoneNumberUtils::EPhoneClientNumber)));
	}


