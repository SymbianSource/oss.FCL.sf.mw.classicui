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

#include "t_textresourceutils.h"
#include <tultextresourceutils.h>
#include <tulstringresourcereader.h>
#include <t_textresourceutils.rsg>
#include <coeutils.h>
#include <eikenv.h>

#include <apacmdln.h>

const TText KLRMarker = 0x200E;
const TText KRLMarker = 0x200F;

_LIT(KTextResourceUtilsFilePath, "z:\\resource\\apps\\t_textresourceutils.rsc");

CT_TextResourceUtilsAppUi::CT_TextResourceUtilsAppUi(CT_TextResourceUtilsStep& aStep): 
CTestAppUi(&aStep, KTextResourceUtilsFilePath)
	{
	}

void CT_TextResourceUtilsAppUi::ConstructL()
	{
	CTestAppUi::ConstructL();
	AutoTestManager().StartAutoTest();
	}

CT_TextResourceUtilsAppUi::~CT_TextResourceUtilsAppUi()
	{
	Reset();
	}

void CT_TextResourceUtilsAppUi::Reset()
	{
	delete iStringHolder;
	iStringHolder = NULL;
	}

void CT_TextResourceUtilsAppUi::RunTestStepL(TInt aStep)
	{
	switch(aStep)
		{
	case 1:
		SetTestStepID(_L("UIF-ETUL-0015"));
		TextResourceUtilsCase1();
		RecordTestResultL();
		break;
	case 2:
		SetTestStepID(_L("UIF-ETUL-0016"));
		TextResourceUtilsCase2();
		RecordTestResultL();
		break;
	case 3:
		SetTestStepID(_L("UIF-ETUL-0017"));
		TextResourceUtilsCase3();
		RecordTestResultL();
		break;
	case 4:
		SetTestStepID(_L("UIF-ETUL-0018"));
		TextResourceUtilsCase4();
		RecordTestResultL();
		break;
	case 5:
		SetTestStepID(_L("UIF-ETUL-0019"));
		TRAPD(err, TextResourceUtilsCase5L());
		TEST(err == KErrNone);
		RecordTestResultL();
		break;
	case 6:
		SetTestStepID(_L("UIF-ETUL-0020"));
		TextResourceUtilsCase6();
		RecordTestResultL();
		break;
	case 7:
		SetTestStepID(_L("UIF-ETUL-0021"));
		TRAP(err, TextResourceUtilsCase7L());
		TEST(err == KErrNone);
		RecordTestResultL();
		break;
	case 8:
		SetTestStepID(_L("UIF-ETUL-0022"));
		TRAP(err, TextResourceUtilsCase8L());
		TEST(err == KErrNone);
		RecordTestResultL();
		break;
	case 9:
		SetTestStepID(_L("UIF-ETUL-0023"));
		TRAP(err, TestStringResourceReaderCaseL());
		TEST(err == KErrNone);
		RecordTestResultL();
		CloseTMSGraphicsStep();		// call after last RecordTestResultL()
		break;
	case 10:
		AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
		break;
	
	default:
		break;
		}
	}

/**
   @SYMTestCaseID UIF-ETUL-0015

   @SYMREQ 7736
 
   @SYMTestCaseDesc Tests variants of TulTextResourceUtils::LoadLC() and TulTextResourceUtils::LoadL() methods
   for normal and OOM conditions.
     
   @SYMTestPriority High 
 
   @SYMTestStatus Implemented
  
   @SYMTestActions Calls TulTextResourceUtils::LoadL() and LoadLC() to read resource string without any 
   format specifiers from the rss file.
   
   @SYMTestExpectedResults The test checks whether 
   1. TulTextResourceUtils::LoadL() loads the correct string from the resource file.
   2. TulTextResourceUtils::LoadL() loads the string with substring separator correctly.
   3. OOM test completes without any memory leaks.
 */
void CT_TextResourceUtilsAppUi::TextResourceUtilsCase1()
	{
	CEikonEnv* eikonEnv = CEikonEnv::Static();
	
	INFO_PRINTF1(_L("Test to read resource string from the rss file"));
	
	HBufC* buf  = NULL;
	TRAPD(ret, buf = TulTextResourceUtils::LoadLC(R_TEXT_EXAMPLE_1); CleanupStack::Pop(buf));
	TEST(ret == KErrNone && buf->Compare(_L("Humblemumble")) == 0);
	delete buf;

	TRAP(ret, iStringHolder = TulTextResourceUtils::LoadL(R_TEXT_EXAMPLE_B));
	TEST(ret == KErrNone && iStringHolder->Compare(_L("Humble mumble")) == 0);
	Reset();

	TRAP(ret, iStringHolder = TulTextResourceUtils::LoadL(R_TEXT_EXAMPLE_B, eikonEnv));
	TEST(ret == KErrNone && iStringHolder->Compare(_L("Humble mumble")) == 0);
	Reset();
	
	TRAP(ret, iStringHolder = TulTextResourceUtils::LoadL(R_TEXT_EXAMPLE_B));
	TEST(ret == KErrNone && iStringHolder->Compare(_L("Humble mumble")) == 0);
	Reset();

    TRAP(ret, iStringHolder = TulTextResourceUtils::LoadL(R_TEXT_EXAMPLE_NEW_1));
	TEST(ret == KErrNone && iStringHolder->Compare(_L("Substrings\001no param\neters\001at all")) == 0);
	Reset();
	
    TRAP(ret, iStringHolder = TulTextResourceUtils::LoadL(R_TEXT_EXAMPLE_NEW_2));
    TEST(ret == KErrNone && iStringHolder->Compare( _L("\001")) == 0);
    Reset();

    TRAP(ret, iStringHolder = TulTextResourceUtils::LoadL(R_TEXT_EXAMPLE_NEW_3));
    TEST(ret == KErrNone && iStringHolder->Compare( _L("\001\001")) == 0);
    Reset();
    
    TRAP(ret, iStringHolder = TulTextResourceUtils::LoadL(R_TEXT_EXAMPLE_NEW_4));
    TEST(ret == KErrNone && iStringHolder->Compare( _L("\001Substring inside\001")) ==0);
    Reset();
	
	// Test LoadL(TInt aResourceId, CCoeEnv* aLoaderEnv); for out of memory conditions.
    for (TInt fail = 1;; fail++)
    	{
		__UHEAP_SETFAIL(RHeap::EDeterministic, fail);
        __UHEAP_MARK;          	
    	
		TRAP(ret, iStringHolder = TulTextResourceUtils::LoadL(R_TEXT_EXAMPLE_B, eikonEnv));
		TEST((ret==KErrNone || ret==KErrNoMemory));
		if (ret == KErrNone)
			{
			TEST(iStringHolder->Compare(_L("Humble mumble")) == 0);
			Reset();
			__UHEAP_MARKEND;
			break;
			}
     	__UHEAP_MARKEND;
        }
	__UHEAP_RESET;
	}

/**
   @SYMTestCaseID UIF-ETUL-0016

   @SYMREQ 7736
 
   @SYMTestCaseDesc Tests variants of TulTextResourceUtils::LoadL() and LoadLC() methods for normal and OOM conditions.
  
   @SYMTestPriority High 
 	
   @SYMTestStatus Implemented
  
   @SYMTestActions Calls TulTextResourceUtils::LoadL() and LoadLC() to read a resource string from rss file, 
   and replace the first %U-string in it with replacement string.
   
   @SYMTestExpectedResults The test checks whether 
   1. TulTextResourceUtils::LoadL() and LoadLC() loads the correct string from the resource file and replaces
   	  the first %U with specified string.
   2. OOM completes without any memory leaks.
 */
void CT_TextResourceUtilsAppUi::TextResourceUtilsCase2()
	{
	INFO_PRINTF1(_L("Test to read a resource string from rss file, and replace the first %%U-string in it with replacement string"));
	
	CEikonEnv* eikonEnv = CEikonEnv::Static();
	TRAPD(ret, iStringHolder = TulTextResourceUtils::LoadL(R_TEXT_EXAMPLE_2, _L("and")));	
	TEST(ret == KErrNone && iStringHolder->Compare(_L("Humble %and mumble")) == 0);
	Reset();
	
	HBufC* buf = NULL;
	TRAP(ret, buf = TulTextResourceUtils::LoadLC(R_TEXT_EXAMPLE_A2, _L("and"), eikonEnv); CleanupStack::Pop(buf));
	TEST(ret == KErrNone && buf->Compare(_L("and Humble mumble")) == 0);
	delete buf;

	TRAP(ret, iStringHolder = TulTextResourceUtils::LoadL(R_TEXT_EXAMPLE_A2, _L("I will"), eikonEnv));
	TEST(ret == KErrNone && iStringHolder->Compare(_L("I will Humble mumble")) == 0);
	Reset();

	TRAP(ret, iStringHolder = TulTextResourceUtils::LoadL(R_TEXT_EXAMPLE_A1, _L(" is nice."), eikonEnv));
	TEST(ret == KErrNone && iStringHolder->Compare(_L("Humble mumble is nice.")) == 0);
	Reset();

	TRAP(ret, iStringHolder = TulTextResourceUtils::LoadL(R_TEXT_EXAMPLE_2, _L("hilipatipilipatipippampaajarallatirallatirallallaatervemoroheipäheimulonmunatsullaei")));	
	TEST(ret == KErrNone && iStringHolder->Compare(_L("Humble %hilipatipilipatipippampaajarallatirallatirallallaatervemoroheipäheimulonmunatsullaei mumble")) == 0);
	Reset();
	
	TRAP(ret, iStringHolder = iStringHolder = TulTextResourceUtils::LoadL(R_TEXT_EXAMPLE_2, _L("")));	
	TEST(ret == KErrNone && iStringHolder->Compare(_L("Humble % mumble")) == 0);
	Reset();

	TRAP(ret, iStringHolder = TulTextResourceUtils::LoadL(R_TEXT_EXAMPLE_10, _L("string"), eikonEnv));
	TEST(ret == KErrNone && iStringHolder->Compare(_L("Testing substring separator at end of the string ")) == 0);
	Reset();
	
	TRAP(ret, iStringHolder = TulTextResourceUtils::LoadL(R_TEXT_EXAMPLE_11, _L("string"), eikonEnv));
	TEST(ret == KErrNone && iStringHolder->Compare(_L("Testing substring separator at end of the string \001 ")) == 0);
	Reset();

    for (TInt fail = 1;; fail++)
    	{
		__UHEAP_SETFAIL(RHeap::EDeterministic, fail);
        __UHEAP_MARK;          	
    	
		TRAP(ret, iStringHolder = TulTextResourceUtils::LoadL(R_TEXT_EXAMPLE_2, _L("a")));
		TEST((ret==KErrNone || ret==KErrNoMemory));
		if (ret == KErrNone)
			{
			TEST(iStringHolder->Compare(_L("Humble %a mumble")) == 0);
			Reset();
			__UHEAP_MARKEND;
			break;
			}
     	__UHEAP_MARKEND;
        }
	__UHEAP_RESET;
	}

/**
   @SYMTestCaseID UIF-ETUL-0017

   @SYMREQ 7736
 
   @SYMTestCaseDesc Tests variants of TulTextResourceUtils::Load() and TulTextResourceUtils::Format() methods under
   normal and OOM conditions.
  
   @SYMTestPriority High 
 
   @SYMTestStatus Implemented
  
   @SYMTestActions Calls TulTextResourceUtils::LoadL() to read a resource string from rss file, and 
   calls TulTextResourceUtils::Format() method to format the same string.
      
   @SYMTestExpectedResults The test checks whether 
   1. TulTextResourceUtils::LoadL() loads the correct string from the resource file.
   2. TulTextResourceUtils::Format() replaces all %U specifiers with specified string if position given is -1
   3. TulTextResourceUtils::Format() replaces all %N specifiers with specified number if position given is -1.
   4. TulTextResourceUtils::Format() replaces corresponding %U specifiers with specified string if position given is other than -1
   5. TulTextResourceUtils::Format() replaces corresponding %N specifiers with specified number if position given is other than -1
   6. OOM test completes without any memory leak.
 */
void CT_TextResourceUtilsAppUi::TextResourceUtilsCase3()
	{
	INFO_PRINTF1(_L("Test to read a resource string from rss file, and to format the string"));

	TBuf<50> buffer1;
    TBuf<50> buffer2;

	CEikonEnv* eikonEnv = CEikonEnv::Static();
	TulTextResourceUtils::Load(buffer1, R_TEXT_EXAMPLE_8, eikonEnv);
	TulTextResourceUtils::Format(buffer2, buffer1, -1, _L("either"));
	TEST(buffer2.Compare(_L("Here either")) == 0);
	
	TulTextResourceUtils::Load(buffer1, R_TEXT_EXAMPLE_9);
	TulTextResourceUtils::Format(buffer2, buffer1, -1, 10);
	TEST(buffer2.Compare(_L("Humble 10 times...%")) == 0);
	
	TulTextResourceUtils::Load(buffer1, R_TEXT_EXAMPLE_D);
	TEST(buffer1.Compare(_L("No memory allocated")) == 0);
	
    TulTextResourceUtils::Load(buffer2, R_TEXT_EXAMPLE_E);
    TulTextResourceUtils::Format(buffer1, buffer2, 2, _L("Really? "));
    buffer2.Zero();
    TulTextResourceUtils::Format(buffer2, buffer1, 1, _L("allocated "));
    buffer1.Zero();
    TulTextResourceUtils::Format(buffer1, buffer2, 0, _L("nothing"));
    TEST(buffer1.Compare(_L("Really? Here allocated nothing ")) == 0);

    TulTextResourceUtils::Load(buffer1, R_TEXT_EXAMPLE_G);
    TulTextResourceUtils::Format(buffer2, buffer1, 3, 6);
    buffer1.Zero();
    TulTextResourceUtils::Format(buffer1, buffer2, 2, 567);
    buffer2.Zero();
    TulTextResourceUtils::Format(buffer2, buffer1, 1, 9);
    buffer1.Zero();
    TulTextResourceUtils::Format(buffer1, buffer2, 0, 7);
    TEST(buffer1.Compare(_L("6I 9allocated 7 bytes567")) == 0);
    
    buffer1.Zero();
	buffer2.Zero();
	TulTextResourceUtils::Load(buffer1, R_TEXT_EXAMPLE_8, eikonEnv);
	TInt fail = 0;
	for (fail = 1; ; fail++)
    	{
		__UHEAP_SETFAIL(RHeap::EDeterministic, fail);
        __UHEAP_MARK;          	
		TulTextResourceUtils::Format(buffer2, buffer1, -1, _L("either"));
		if (buffer2.Length())
			{
			__UHEAP_RESET;	// TEST result will not be displayed correctly if the memory allocation is not reset.
			TEST(buffer2.Compare(_L("Here either")) == 0);
			__UHEAP_MARKEND;
			break;
			}
     	__UHEAP_MARKEND;
    	}

	__UHEAP_RESET;
    buffer1.Zero();
	buffer2.Zero();
    TulTextResourceUtils::Load(buffer1, R_TEXT_EXAMPLE_F);
    for (fail = 1; ; fail++)
    	{
		__UHEAP_SETFAIL(RHeap::EDeterministic, fail);
        __UHEAP_MARK;          	
		TulTextResourceUtils::Format(buffer2, buffer1, -1, 7);
		if (buffer2.Length())
			{
			__UHEAP_RESET;	// TEST result will not be displayed correctly if the memory allocation is not reset.
			TEST(buffer2.Compare(_L("I allocated 7 bytes")) == 0);
			__UHEAP_MARKEND;
			break;
			}
     	__UHEAP_MARKEND;
    	}
    __UHEAP_RESET;	
    }

/**
   @SYMTestCaseID UIF-ETUL-0018

   @SYMREQ 7736
 
   @SYMTestCaseDesc Tests variants of TulTextResourceUtils::LoadL() and LoadLC() methods for normal and OOM conditions.
  
   @SYMTestPriority High 
 
   @SYMTestStatus Implemented
  
   @SYMTestActions Calls TulTextResourceUtils::LoadL() and LoadLC() to read resource string from the rss file
   and to replace the first %%(index)N-string with replacement TInt.
   
   @SYMTestExpectedResults The test checks whether 
   1. TulTextResourceUtils::LoadL() and LoadLC() loads the correct string from the resource file and replaces 
   	  the first %%(index)N-string in it with replacement TInt.
   2. OOM test completes without any memory leaks.
 */
void CT_TextResourceUtilsAppUi::TextResourceUtilsCase4()
	{
	TInt number(324);
	CEikonEnv* eikonEnv = CEikonEnv::Static();

	INFO_PRINTF1(_L("Test to read resource string from the rss file and to replace the first %%(index)N-string in it with replacement TInt"));
	HBufC* buf = NULL;
	TRAPD(ret, buf = TulTextResourceUtils::LoadLC(R_TEXT_EXAMPLE_3, number, eikonEnv); CleanupStack::Pop(buf));
	TEST(ret == KErrNone && buf->Compare(_L("You have %R324 undone tasks.")) == 0);
	delete buf;
	
	TRAP(ret, iStringHolder = TulTextResourceUtils::LoadL(R_TEXT_EXAMPLE_9, 123456789, eikonEnv));
	TEST(ret == KErrNone && iStringHolder->Compare(_L("Humble 123456789 times...%")) == 0);
	Reset();

	// Test LoadL(TInt aResourceId, TInt aNumber, CCoeEnv* aLoaderEnv = NULL); for out of memory conditions.
	TRAP(ret, iStringHolder = TulTextResourceUtils::LoadL(R_TEXT_EXAMPLE_9, -12345, eikonEnv));
	TEST(ret == KErrNone && iStringHolder->Compare(_L("Humble -12345 times...%")) == 0);
	Reset();

    for (TInt fail = 1;; fail++)
    	{
		__UHEAP_SETFAIL(RHeap::EDeterministic, fail);
        __UHEAP_MARK;          	
    	
		TRAP(ret, iStringHolder = TulTextResourceUtils::LoadL(R_TEXT_EXAMPLE_3, number));
		TEST((ret==KErrNone || ret==KErrNoMemory));
		if (ret == KErrNone)
			{
			TEST(iStringHolder->Compare(_L("You have %R324 undone tasks.")) == 0);
			Reset();
			__UHEAP_MARKEND;
			break;
			}
     	__UHEAP_MARKEND;
        }
	__UHEAP_RESET;
	}

/**
   @SYMTestCaseID UIF-ETUL-0019

   @SYMREQ 7736
 
   @SYMTestCaseDesc Tests variants of TulTextResourceUtils::LoadL() and  LoadLC() methods for normal and OOM conditions.
  
   @SYMTestPriority High 
 
   @SYMTestStatus Implemented
  
   @SYMTestActions Calls TulTextResourceUtils::LoadL() and LoadLC() methods to read resource string from the rss file and 
	to replace the %%(index)U-strings with replacement strings from an array
   
   @SYMTestExpectedResults The test checks whether 
   1. TulTextResourceUtils::LoadL() and LoadLC() loads the correct string from the resource file
      and replaces the %%(index)U-strings in it with replacement strings from the array.
   2. TulTextResourceUtils::LoadL() loads the string which has strictly right-to-left directional characters in substring
   3. TulTextResourceUtils::LoadL() loads the string with KDirNotFound and substring separator
   4. OOM test completes without any memory leaks.
 */
void CT_TextResourceUtilsAppUi::TextResourceUtilsCase5L()
	{
	CDesCArrayFlat* strings = new (ELeave)CDesCArrayFlat(4);
	CleanupStack::PushL(strings);
	
	INFO_PRINTF1(_L("Test to read a resource string from the rss file and to replace the %%(index)U-strings in it with replacement strings from an array"));
	
	strings->AppendL(_L("orking")); //First string
	strings->AppendL(_L("ll")); 	//Second string
	strings->AppendL(_L("sti")); 	//Third string
	strings->AppendL(_L("w")); 		//Fourth string

	CEikonEnv* eikonEnv = CEikonEnv::Static();
	HBufC* buf = NULL;
	TRAPD(ret, buf = TulTextResourceUtils::LoadLC(R_TEXT_EXAMPLE_4, *strings, eikonEnv); CleanupStack::Pop(buf));
	TEST(ret == KErrNone && buf->Compare(_L("I'm %11 still working fine.")) == 0);
	delete buf;
	
    // Test LoadL(TInt aResourceId, const MDesCArray& aStrings, CCoeEnv* aLoaderEnv = NULL); for out of memory conditions.
    for (TInt fail = 1;; fail++)
    	{
		__UHEAP_SETFAIL(RHeap::EDeterministic, fail);
        __UHEAP_MARK;          	
    	
		TRAP(ret, iStringHolder = TulTextResourceUtils::LoadL(R_TEXT_EXAMPLE_4, *strings));
		TEST((ret==KErrNone || ret==KErrNoMemory));
		if (ret == KErrNone)
			{
			__UHEAP_RESET;	// TEST result will not be displayed correctly if the memory allocation is not reset.
			TEST(iStringHolder->Compare(_L("I'm %11 still working fine.")) == 0);
			Reset();
			__UHEAP_MARKEND;
			break;
			}
     	__UHEAP_MARKEND;
        }

	__UHEAP_RESET;
  // strongly right-to-left directional characters in substring
    TBuf<10> substring;
    substring.Append(TChar(0x062C));
    substring.Append(TChar(0x0639));
    substring.Append(TChar(0x0644));

    TRAP(ret, iStringHolder = TulTextResourceUtils::LoadL(R_TEXT_EXAMPLE_NEW_5, substring));
	TEST(ret == KErrNone);
 
    TBuf<100> compareBuffer;
    compareBuffer.Append(KLRMarker);
    compareBuffer.Append(_L("Strongly right-to-left("));
    compareBuffer.Append(KRLMarker);
    compareBuffer.Append(substring);
    compareBuffer.Append(KRLMarker);
    compareBuffer.Append(_L(") directional\001"));
    compareBuffer.Append(KLRMarker);
    compareBuffer.Append(_L(" characters ("));
    compareBuffer.Append(KRLMarker);
    compareBuffer.Append(substring);
    compareBuffer.Append(KRLMarker);
    compareBuffer.Append(_L(") in \001"));
    compareBuffer.Append(KLRMarker);
    compareBuffer.Append(_L("substring"));
    TEST(iStringHolder->Compare(compareBuffer) == 0);
    Reset();

    compareBuffer.Insert(1, _L(" "));
    compareBuffer.Append(_L("\x0001"));
	TRAP(ret, iStringHolder = TulTextResourceUtils::LoadL(R_TEXT_EXAMPLE_NEW_8, substring, eikonEnv));
	TEST(ret == KErrNone && iStringHolder->Compare(compareBuffer) == 0);
	Reset();

	compareBuffer.Delete(0, 2);
	compareBuffer.Insert(0, _L("\x0002 "));
	compareBuffer.Delete(compareBuffer.Length()-1, 6);
	TRAP(ret, iStringHolder = TulTextResourceUtils::LoadL(R_TEXT_EXAMPLE_NEW_9, substring, eikonEnv));
	TEST(ret == KErrNone && iStringHolder->Compare(compareBuffer) == 0);
	Reset();

    strings->Reset();
    strings->AppendL(_L("1234567890"));
    strings->AppendL(_L("ABCDEFGHIJ"));
    strings->AppendL(_L("?/*"));
    TRAP(ret, iStringHolder = TulTextResourceUtils::LoadL(R_TEXT_EXAMPLE_NEW_7, *strings));
    TEST(ret == KErrNone);
    // "Testing string length limiting Five:%0U[05] Three:%1U[03]\001Seven:%0U[07] Nine:%1U[09] Three:%2U[03]"
    compareBuffer.Zero(); 
    compareBuffer.Append(_L("Testing string length limiting Five:1234"));
    compareBuffer.Append(KEllipsis);
    compareBuffer.Append(_L(" Three:AB"));
    compareBuffer.Append(KEllipsis);
    compareBuffer.Append(_L("\001Seven:123456"));
    compareBuffer.Append(KEllipsis);
    compareBuffer.Append(_L(" Nine:ABCDEFGH"));
    compareBuffer.Append(KEllipsis);
    compareBuffer.Append(_L(" Three:?/*"));
    TEST(iStringHolder->Compare(compareBuffer) == 0);
    Reset();

	CleanupStack::PopAndDestroy();
	}

/**
   @SYMTestCaseID UIF-ETUL-0020

   @SYMREQ 7736
 
   @SYMTestCaseDesc Tests variants of TulTextResourceUtils::LoadL() and LoadLC() methods for normal and OOM conditions.
  
   @SYMTestPriority High 
 
   @SYMTestStatus Implemented
  
   @SYMTestActions Calls TulTextResourceUtils::LoadL() and LoadLC() to read resource string from the rss file and to
   replace the first %%(index)N-string with replacement TInt and the first %%(index)U-string with replacement string
   
   @SYMTestExpectedResults The test checks whether 
   1. TulTextResourceUtils::LoadL() and LoadLC() loads the correct string from the resource file and replaces
      a. The first %%(index)N-string with replacement TInt 
      b. The first %%(index)U-string with replacement string.
   2. OOM tests completes without any memory leaks.
 */
void CT_TextResourceUtilsAppUi::TextResourceUtilsCase6()
	{
	TInt number2(12);
	_LIT(name, "John Doe");

	INFO_PRINTF1(_L("Test to read resource string from the rss file and replace the first %%(index)N-string in it with replacement TInt and the first %%(index)U-string in it with replacement string"));

	CEikonEnv* eikonEnv = CEikonEnv::Static();
	HBufC* buf = NULL;
	TRAPD(ret, buf = TulTextResourceUtils::LoadLC(R_TEXT_EXAMPLE_5, name, number2, eikonEnv); CleanupStack::Pop(buf));
	TEST(ret == KErrNone && buf->Compare(_L("You have missed 12 messages from John Doe.\001Missed 12 msgs from John Doe.\001Missed 12 msgs.")) == 0);
	delete buf;

	TRAP(ret, iStringHolder = TulTextResourceUtils::LoadL(R_TEXT_EXAMPLE_C, _L("and"), 68365));
	TEST(ret == KErrNone && iStringHolder->Compare(_L("and mumble 68365 times.")) == 0);
	Reset();

	// Test LoadL(TInt aResourceId, const TDesC& aString, TInt aInt, CCoeEnv* aLoaderEnv = NULL); for out of memory conditions.
    for (TInt fail = 1;; fail++)
    	{
		__UHEAP_SETFAIL(RHeap::EDeterministic, fail);
        __UHEAP_MARK;          	
    	
		TRAP(ret, iStringHolder = TulTextResourceUtils::LoadL(R_TEXT_EXAMPLE_5, name, number2));
		TEST((ret==KErrNone || ret==KErrNoMemory));
		if (ret == KErrNone)
			{
			TEST(iStringHolder->Compare(_L("You have missed 12 messages from John Doe.\001Missed 12 msgs from John Doe.\001Missed 12 msgs.")) == 0);
			Reset();
			__UHEAP_MARKEND;
			break;
			}
     	__UHEAP_MARKEND;
        }
	__UHEAP_RESET;
	}

/**
   @SYMTestCaseID UIF-ETUL-0021

   @SYMREQ 7736
 
   @SYMTestCaseDesc Tests variants of TulTextResourceUtils::LoadL() and LoadLC() methods for normal and OOM conditions.
  
   @SYMTestPriority High 
 
   @SYMTestStatus Implemented
  
   @SYMTestActions Calls TulTextResourceUtils::LoadL() and LoadLC() to read resource string from the rss file and to
   replace the %%(index)N-strings with replacement TInts from the given array.
   
   @SYMTestExpectedResults The test checks whether 
   1. TulTextResourceUtils::LoadL() and LoadLC() loads the correct string from the resource file and
   	  replaces the %%(index)N-strings with replacement TInts from the given array.
   2. OOM tests completes without any memory leaks.
 */	
void CT_TextResourceUtilsAppUi::TextResourceUtilsCase7L()
	{
	CArrayFix<TInt>* numberArray = new(ELeave)CArrayFixFlat<TInt>(3);
	CleanupStack::PushL(numberArray);
	
	numberArray->AppendL(1);	// First Integer
	numberArray->AppendL(2);	// Second Integer
	
	INFO_PRINTF1(_L("Test to read resource string from the rss file and replaces the %%(index)N-strings in it with replacement TInts from an array"));

	CEikonEnv* eikonEnv = CEikonEnv::Static();
	HBufC* buf = NULL;
	TRAPD(ret, buf = TulTextResourceUtils::LoadLC(R_TEXT_EXAMPLE_6, *numberArray, eikonEnv); CleanupStack::Pop(buf));
	TEST(ret == KErrNone && buf->Compare(_L("Multiple numeric 1:%2N indexes 1:1\x0001\x0032:2 in separate\x0001substrings")) == 0);
	delete buf;

	numberArray->AppendL(3);	// Third Integer
	TRAP(ret, iStringHolder = TulTextResourceUtils::LoadL(R_TEXT_EXAMPLE_6, *numberArray, eikonEnv));
	TEST(ret == KErrNone && iStringHolder->Compare(_L("Multiple numeric 1:3 indexes 1:1\x0001\x0032:2 in separate\x0001substrings")) == 0);
	Reset();
	
	// Test LoadL(TInt aResourceId, const CArrayFix<TInt>& aInts, CCoeEnv* aLoaderEnv = NULL); for out of memory conditions.
    for (TInt fail = 1;; fail++)
    	{
		__UHEAP_SETFAIL(RHeap::EDeterministic, fail);
        __UHEAP_MARK;          	
    	
		TRAP(ret, iStringHolder = TulTextResourceUtils::LoadL(R_TEXT_EXAMPLE_6, *numberArray));
		TEST((ret==KErrNone || ret==KErrNoMemory));
		if (ret == KErrNone)
			{
			TEST(iStringHolder->Compare(_L("Multiple numeric 1:3 indexes 1:1\x0001\x0032:2 in separate\x0001substrings")) == 0);
			Reset();
			__UHEAP_MARKEND;
			break;
			}
     	__UHEAP_MARKEND;
        }
	__UHEAP_RESET;
	CleanupStack::PopAndDestroy();
	}	

/**
   @SYMTestCaseID UIF-ETUL-0022

   @SYMREQ 7736
 
   @SYMTestCaseDesc Tests variants of TulTextResourceUtils::LoadL() and TulTextResourceUtils::LoadLC() 
   methods for normal and OOM conditions.
  
   @SYMTestPriority High 
 
   @SYMTestStatus Implemented
  
   @SYMTestActions Calls TulTextResourceUtils::LoadL() to read resource string without any format specifiers from the rss file 
   and to replace the %%(index)U-strings with replacement strings from the give array and
   the %%(index)N-strings with replacement TInts from an array
   
   @SYMTestExpectedResults The test checks whether 
   1. TulTextResourceUtils::LoadL() loads the correct string from the resource file and replaces the 
      a. %%(index)U-strings with replacement strings from the given array of strings
      b. %%(index)N-strings with replacement strings from the given TInt array
   2. TulTextResourceUtils::LoadL() loads the string which has multiple strictly right-to-left directional characters 
   	  in substring   
   3. OOM tests completes without any memory leaks.
 */	
void CT_TextResourceUtilsAppUi::TextResourceUtilsCase8L()
	{
	INFO_PRINTF1(_L("Test to read a resource string from the rss file and to replace the %%(index)U-strings in it with replacement strings from an array & the %%(index)N-strings in it with replacement TInts from an array"));

	CEikonEnv* eikonEnv = CEikonEnv::Static();
	CArrayFix<TInt>* numberArray = new(ELeave)CArrayFixFlat<TInt>(2);
	CleanupStack::PushL(numberArray);
	
	numberArray->AppendL(5);	// First Integer
	numberArray->AppendL(2);	// Second Integer
		
	CDesCArrayFlat* strings = new (ELeave)CDesCArrayFlat(5);
	CleanupStack::PushL(strings);
	
	strings->AppendL(_L("for")); 	//First string
	strings->AppendL(_L("Test")); 	//Second string
	strings->AppendL(_L("strings")); //Third string
	strings->AppendL(_L("numerics")); //Fourth string
	strings->AppendL(_L("and")); 	//Fifth string

	HBufC* buf = NULL;
	TRAPD(ret, buf = TulTextResourceUtils::LoadLC(R_TEXT_EXAMPLE_7, *strings, *numberArray, eikonEnv); CleanupStack::Pop(buf));
	TEST(ret == KErrNone);
	TEST(buf->Compare(_L("Multiple numeric and strings mixed One: Test for reading 5 strings and 2 numerics %4")) == 0);
	delete buf;
	
	// Test LoadL(TInt aResourceId, const MDesCArray& aStrings, const CArrayFix<TInt>& aInts, CCoeEnv* aLoaderEnv = NULL); for out of memory conditions.
    for (TInt fail = 1;; fail++)
    	{
		__UHEAP_SETFAIL(RHeap::EDeterministic, fail);
        __UHEAP_MARK;          	
    	
		TRAP(ret, iStringHolder = TulTextResourceUtils::LoadL(R_TEXT_EXAMPLE_7, *strings, *numberArray));
		TEST((ret==KErrNone || ret==KErrNoMemory));
		if (ret == KErrNone)
			{
			__UHEAP_RESET;	// TEST result will not be displayed correctly if the memory allocation is not reset.
			TEST(iStringHolder->Compare(_L("Multiple numeric and strings mixed One: Test for reading 5 strings and 2 numerics %4")) == 0);
			Reset();
			__UHEAP_MARKEND;
			break;
			}
     	__UHEAP_MARKEND;
        }
	
	__UHEAP_RESET;
	strings->Reset();
	numberArray->Reset();
    // strongly right-to-left directional characters in substring
    TBuf<10> substring;
    TBuf<10> substring2;

    substring.Append(TChar(0x062C));
    substring.Append(TChar(0x0639));
    substring.Append(TChar(0x0644));

    substring2.Append(TChar(0x0644));
    substring2.Append(TChar(0x0639));
    substring2.Append(TChar(0x062C));

    strings->AppendL(substring); 
    strings->AppendL(substring2); 
    numberArray->AppendL(2);

    TRAP(ret, iStringHolder = TulTextResourceUtils::LoadL(R_TEXT_EXAMPLE_NEW_6, *strings, *numberArray));
	TEST(ret == KErrNone);
 
    TBuf<150> compareBuffer; 
    //"Multiple (%2N) Strongly right-to-left(%0U,%1U) directional\001 characters (%1U)(%0U) in \001substring"
    compareBuffer.Append(KLRMarker);
    compareBuffer.Append(_L("Multiple (2) Strongly right-to-left("));
    compareBuffer.Append(KRLMarker);
    compareBuffer.Append(substring);
    compareBuffer.Append(KRLMarker);
    compareBuffer.Append(_L(","));
    compareBuffer.Append(KRLMarker);
    compareBuffer.Append(substring2);
    compareBuffer.Append(KRLMarker);
    compareBuffer.Append(_L(") directional\001"));
    compareBuffer.Append(KLRMarker);
    compareBuffer.Append(_L(" characters ("));
    compareBuffer.Append(KRLMarker);
    compareBuffer.Append(substring2);
    compareBuffer.Append(KRLMarker);
    compareBuffer.Append(_L(")("));
    compareBuffer.Append(KRLMarker);
    compareBuffer.Append(substring);
    compareBuffer.Append(KRLMarker);
    compareBuffer.Append(_L(") in \001"));
    compareBuffer.Append(KLRMarker);
    compareBuffer.Append(_L("substring"));
    TEST(iStringHolder->Compare(compareBuffer) == 0);
    Reset();

    CleanupStack::PopAndDestroy(2);
	}

/**
   @SYMTestCaseID UIF-ETUL-0023

   @SYMREQ 7736
 
   @SYMTestCaseDesc Tests variants of CTulStringResourceReader::NewLC() and NewL() methods and 
   CTulStringResourceReader::ReadResourceString() method for normal and OOM conditions.
  
   @SYMTestPriority High 
 
   @SYMTestStatus Implemented
  
   @SYMTestActions Calls CTulStringResourceReader::ReadResourceString() to read resource string from the given resource file.
   
   @SYMTestExpectedResults The test checks whether 
   1. CTulStringResourceReader::ReadResourceString() loads the correct string from the resource file.
   2. CTulStringResourceReader::ReadResourceString() loads the string with very long text(~1000 characters) from the resource file.
   3. OOM tests completes without any memory leaks.
 */	
void CT_TextResourceUtilsAppUi::TestStringResourceReaderCaseL()
	{
	INFO_PRINTF1(_L("Test to read a resource string from the resource file using CTulStringResourceReader"));
	TFileName fileName(KTextResourceUtilsFilePath);
    
	RFs rFs;
	User::LeaveIfError(rFs.Connect());
	CleanupClosePushL(rFs);
    TPtrC buf;

    CTulStringResourceReader* stringResourceLoader = CTulStringResourceReader::NewLC(fileName);
    buf.Set(stringResourceLoader->ReadResourceString(R_TEXT_STRINGRESOURCEREADER_1));
    TEST(buf.Compare(_L("Some string to be read")) == 0);
    CleanupStack::PopAndDestroy(stringResourceLoader);

    stringResourceLoader = CTulStringResourceReader::NewL(fileName);
    CleanupStack::PushL(stringResourceLoader);
    buf.Set(stringResourceLoader->ReadResourceString(R_TEXT_STRINGRESOURCEREADER_2));
    TEST(buf.Compare(_L("Some other string to be read")) == 0);
    CleanupStack::PopAndDestroy(stringResourceLoader);

    stringResourceLoader = CTulStringResourceReader::NewLC(fileName, rFs);
    buf.Set(stringResourceLoader->ReadResourceString(R_TEXT_STRINGRESOURCEREADER_3));
    TEST(buf.Compare(_L("Very long text. ~1000 characters. 123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012")));
    CleanupStack::PopAndDestroy(stringResourceLoader);

    stringResourceLoader = CTulStringResourceReader::NewL(fileName, rFs);
    CleanupStack::PushL(stringResourceLoader);
    buf.Set(stringResourceLoader->ReadResourceString(R_TEXT_STRINGRESOURCEREADER_4));
    TEST(buf.Compare(_L("Short string to be read")) == 0);
    CleanupStack::PopAndDestroy(stringResourceLoader);
    CleanupStack::PopAndDestroy(&rFs);

	// OOM test for CTulStringReaderReader.
	INFO_PRINTF1(_L("OOM Test for CTulStringReaderReader"));
    for (int fail = 1;; fail++)
        {
        __UHEAP_SETFAIL(RHeap::EDeterministic, fail);
        __UHEAP_MARK;

        CTulStringResourceReader* stringResourceLoader = NULL;
        TRAPD(err, stringResourceLoader = CTulStringResourceReader::NewL(fileName));
        TEST(err == KErrNone || err == KErrNoMemory);
        if (err == KErrNone)
            {
            buf.Set(stringResourceLoader->ReadResourceString(R_TEXT_STRINGRESOURCEREADER_1));
            if (buf != KNullDesC)
            	{
            	TEST(buf.Compare(_L("Some string to be read")) == 0);
             	delete stringResourceLoader;
             	__UHEAP_MARKEND;
      	    	break;
            	}
            delete stringResourceLoader;
        	}
        __UHEAP_MARKEND;
	   	}
    __UHEAP_RESET;
	}

/**
   Destructor
 */
CT_TextResourceUtilsStep::~CT_TextResourceUtilsStep()
	{
	}

/**
   Constructor
 */	
CT_TextResourceUtilsStep::CT_TextResourceUtilsStep()
	{
	// Call base class method to set up the human readable name for logging
	SetTestStepName(KT_TextResourceUtilsStep);
	}
	
void CT_TextResourceUtilsStep::ConstructAppL(CEikonEnv* aCoeEnv)
	{
	aCoeEnv->ConstructL();
	CT_TextResourceUtilsAppUi* appUi=new(ELeave) CT_TextResourceUtilsAppUi(*this);
	appUi->ConstructL();
	aCoeEnv->SetAppUi(appUi);
	}

void CT_TextResourceUtilsStep::TestTextResourceUtilsWithoutCoeEnv()
	{
	INFO_PRINTF1(_L("Test TulTextResourceUtils Load methods before CoeEnv is created"));
	TRAPD(err, TulTextResourceUtils::LoadL(R_TEXT_EXAMPLE_B));
	TEST(err == KErrNotSupported);
	
	HBufC* buf  = NULL;
	TRAP(err, buf = TulTextResourceUtils::LoadLC(R_TEXT_EXAMPLE_B); CleanupStack::Pop(buf));
	TEST(!buf);
	delete buf;
	TEST(err == KErrNotSupported);
	}

TVerdict CT_TextResourceUtilsStep::doTestStepL()
	{
	INFO_PRINTF1(_L("Test Started"));
	__UHEAP_MARK;

	TestTextResourceUtilsWithoutCoeEnv();
	CEikonEnv* coe = new(ELeave) CEikonEnv;
	TRAPD(err, ConstructAppL(coe));
	if (!err)
		coe->ExecuteD();
	else
		{
		SetTestStepResult(EFail);
		delete coe;
		}
	__UHEAP_MARKEND;
	INFO_PRINTF1(_L("Test Finished"));
	return TestStepResult();
	}
