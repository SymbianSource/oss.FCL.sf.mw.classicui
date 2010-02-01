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
//

/**
 @file 
 @internalComponent - Internal Symbian test code 
*/


#include <f32file.h>
#include <bautils.h>
#include <gdi.h>
#include <gulcolor.h>
#include <gulutil.h>
#include <eikenv.h>
#include "T_ColorStep.h"
#include <centralrepository.h>

// these constants are also defined in cone\src\CoeDataStorage.cpp
const TUint KUidSystemColorRepository=0x10272619;
const TUint KSystemColorRepositoryKey=0;

//
// CSimpleColorControl
//

void CSimpleColorControl::ConstructL()
	{
	CreateWindowL();
	Window().SetShadowDisabled(ETrue);
	SetExtentToWholeScreen();
	ActivateL();
	}

void CSimpleColorControl::Draw(const TRect&) const
	{
	CWindowGc& gc = SystemGc();
	gc.Clear(Rect());
	}


//
// CTestColorUi
//

CTestColorUi::CTestColorUi(CT_ColorStep& aStep)
: CTestAppUi(&aStep, KNullDesC), iColorStep(aStep)
	{
	}

void CTestColorUi::ConstructL()
	{
	CTestAppUi::ConstructL();
	iControl = new(ELeave) CSimpleColorControl;
	AddToStackL(iControl, ECoeStackPriorityDefault, ECoeStackFlagOwnershipTransfered);
	iControl->ConstructL();
	iTestResult = CAutoTestManager::EPass;

	AutoTestManager().StartAutoTest();
	}

CTestColorUi::~CTestColorUi()
	{
	delete iColorList;
	}


void CTestColorUi::RunTestStepL(TInt aStep)
	{
	TRAPD(err, DoRunTestStepL(aStep));
	if(err == KLeaveExit)
		{
		User::Leave(err);
		}
	else if(err != KErrNone)
		{
		// Don't propagate this error since leaving stops the test :O(
		INFO_PRINTF3(_L(" Test step %d failed: %d"), aStep, err);
		iTestResult = CAutoTestManager::EFailed;
		}
	}
	
void CTestColorUi::DoRunTestStepL(TInt aStep)
	{
	switch(aStep)
		{
		case CT_ColorStep::ETestColorArray:
		SetTestStepID(_L("UIF-egul-TestColorArray"));
		INFO_PRINTF1(_L("Test CColorArray"));
		iColorStep.TestColorArrayL();
		RecordTestResultL();
		break;
	case CT_ColorStep::ETestColorList:
		SetTestStepID(_L("UIF-egul-TestColorList"));
		INFO_PRINTF1(_L("Test CColorList"));
		iColorList = iColorStep.TestColorListLC();
		CleanupStack::Pop(iColorList);
		RecordTestResultL();
		break;
	case CT_ColorStep::ETestColorUtils:
		SetTestStepID(_L("UIF-egul-TestColorUtils"));
		INFO_PRINTF1(_L("Test ColorUtils"));
		iColorStep.TestColorUtilsL(*iColorList);
		RecordTestResultL();
		break;
	case CT_ColorStep::ETestColorOom:
		SetTestStepID(_L("UIF-egul-TestColorOom"));
		INFO_PRINTF1(_L("Repeat tests in low memory"));
		iColorStep.TestColorOomL();
		RecordTestResultL();
		break;
	case CT_ColorStep::ETestFileLength:
		SetTestStepID(_L("UIF-egul-FileLengthTestL"));
		INFO_PRINTF1(_L("Test access zero length file"));
		iColorStep.FileLengthTestL();
		RecordTestResultL();
		break;
	case CT_ColorStep::ETestFileCorrupt:
		SetTestStepID(_L("UIF-egul-CorruptFileTest"));
		INFO_PRINTF1(_L("Test access corrupt file"));
		iColorStep.CorruptFileTestL();
		RecordTestResultL();
		CloseTMSGraphicsStep();
		break;
	default:
		iColorStep.SetTestStepResult((iTestResult==CAutoTestManager::EPass) ? EPass : EFail);
		AutoTestManager().FinishAllTestCases(iTestResult);
		break;
		}
	}

/**
	@SYMTestCaseID UIF-egul-TestColorArray
	
	@SYMPREQ
	
	@SYMTestCaseDesc
	Test basic functionality of the CColorArray class.

	@SYMTestPriority High

	@SYMTestStatus Implemented

	@SYMTestActions
	Create a new CColorList object.
	Add some logical colors to it.
	Check that the presence of the colors may be detected.
	Check that the values of the logical colors may be retrieved.

	@SYMTestExpectedResults
	Logical colors may be stored in, and retrieved from, a CColorArray object.

*/
void CT_ColorStep::TestColorArrayL()
	{
	CColorArray* array=CColorArray::NewL();
	TEST(array!=NULL);
	delete array;
	array=0;
	array=CColorArray::NewLC();
	TEST(array!=NULL);
	TEST(array->Contains(101)==EFalse);
	TEST(array->Count()==0);
	array->AddL(101,KRgbWhite);
	array->AddL(102,KRgbBlack);
	array->AddL(104,KRgbDarkBlue);
	array->AddL(103,KRgbGreen);
	TEST(array->Count()==4);
	TEST(array->Contains(101));
	TEST(!array->Contains(105));
	TEST(array->Color(102)==KRgbBlack);
	TEST(array->Color(103)==KRgbGreen);
	array->SetColor(104,KRgbYellow);
	TEST(array->Color(104)==KRgbYellow);
	TEST(array->Contains(104));
	array->Remove(102);
	array->Remove(104);
	TEST(array->Count()==2);
	TEST(array->Contains(101));
	TEST(array->Contains(103));
	TEST(!array->Contains(104));
	array->Reset();
	TEST(array->Count()==0);
	CleanupStack::PopAndDestroy(); // array
	}

/**
	@SYMTestCaseID UIF-egul-TestColorList

	@SYMPREQ

	@SYMTestCaseDesc
	Test basic functionality of the CColorList class.

	@SYMTestPriority High

	@SYMTestStatus Implemented

	@SYMTestActions
	Create a new CColorList object.
	Add some logical colors to it.
	Check that the presence of the colors may be detected.
	Check that the values of the logical colors may be retrieved.
	Add some CColorArray objects to it.
	Check that the presence of the color arrays may be detected.
	Check that the values of the colors in the color arrays may be retrieved.
	
	@SYMTestExpectedResults
	Logical colors and color arrays may be stored in, and retrieved from,
	a CColorList object.

*/
CColorList* CT_ColorStep::TestColorListLC()
	{
	CArrayFix<TRgb>* rgbs=new(ELeave) CArrayFixFlat<TRgb>(3);
	CleanupStack::PushL(rgbs);
	rgbs->AppendL(KRgbWhite);
	rgbs->AppendL(KRgbGray);
	rgbs->AppendL(KRgbCyan);
	rgbs->AppendL(KRgbDarkRed);
	CColorList* list=CColorList::NewL(rgbs);
	CleanupStack::Pop(); // rgbs
	CleanupStack::PushL(list);
	TEST(list->Color(TLogicalColor(0))==KRgbWhite);
	CColorArray* array=CColorArray::NewLC();
	array->AddL(200,KRgbDarkMagenta);
	array->AddL(201,KRgbDarkCyan);
	array->AddL(202,KRgbDarkMagenta);
	list->AddColorArrayL(TUid::Uid(KEikCustomColorsArrayValue),array);
	CleanupStack::Pop(); // array

	array=CColorArray::NewLC();
	array->AddL(300,KRgbDarkGray);
	array->AddL(301,KRgbRed);
	list->AddColorArrayL(TUid::Uid(1001),array);
	CleanupStack::Pop(); // array

	TEST(list->ContainsColorArray(TUid::Uid(KEikCustomColorsArrayValue)));
	TEST(!list->ContainsColorArray(TUid::Uid(1005)));
	TEST(list->ContainsColorArray(TUid::Uid(1001)));
	array=list->ColorArray(TUid::Uid(KEikCustomColorsArrayValue));
	TEST(array->Count()==3);
	TEST(list->Color(TUid::Uid(1001),300)==KRgbDarkGray);
	TEST(list->Color(TUid::Uid(KEikCustomColorsArrayValue),201)==KRgbDarkCyan);
	array=list->ColorArray(TUid::Uid(1001));
	TEST(array->Count()==2);

	list->DeleteColorArray(TUid::Uid(1001));
	TEST(list->ContainsColorArray(TUid::Uid(KEikCustomColorsArrayValue)));
	TEST(!list->ContainsColorArray(TUid::Uid(1005)));
	TEST(!list->ContainsColorArray(TUid::Uid(1001)));

	list->SetColor(TLogicalColor(1),KRgbBlack);
	TEST(list->Color(TLogicalColor(0))==KRgbWhite);
	TEST(list->Color(TLogicalColor(1))==KRgbBlack);

	return list;
	}

/**
	@SYMTestCaseID UIF-egul-TestColorUtils

	@SYMPREQ
	
	@SYMTestCaseDesc
	Test basic functionality of the ColorUtils class.

	@SYMTestPriority High

	@SYMTestStatus Implemented

	@SYMTestActions
	Remove the current color scheme file.
	Check that an attempt to read the color scheme returns a NULL CColorList object.
	Create a new color scheme file from a supplied CColorList.
	Check that an attempt to read the new color scheme returns a CColorList object
	containing the expected colors and color arrays.
	Restore the original color scheme file.
	
	@SYMTestExpectedResults
	The system color scheme may be changed.

*/
void CT_ColorStep::TestColorUtilsL(CColorList& aColorList)
	{
	RFs& fs = iFs;
//	if (BaflUtils::FileExists(fs,????KColorSchemeFile))
//		{
//		if (BaflUtils::FileExists(fs,KColorSchemeFileOriginalRenamed))
//			{
//			User::LeaveIfError(fs.Delete(KColorSchemeFileOriginalRenamed));
//			}
//		User::LeaveIfError(fs.Rename(KColorSchemeFile,KColorSchemeFileOriginalRenamed));
//		}
	CColorList* list=ColorUtils::CreateSystemColorListL(fs);
	delete list;
	ColorUtils::UpdateSystemColorListL(fs,aColorList);
	list=ColorUtils::CreateSystemColorListL(fs);
	CleanupStack::PushL(list);
	TEST(list->Color(TLogicalColor(0))==KRgbWhite);
	TEST(list->ContainsColorArray(TUid::Uid(KEikCustomColorsArrayValue)));
	TEST(!list->ContainsColorArray(TUid::Uid(1005)));
	TEST(!list->ContainsColorArray(TUid::Uid(1001)));
	CColorArray* array=list->ColorArray(TUid::Uid(KEikCustomColorsArrayValue));
	TEST(array->Count()==3);
	TEST(list->Color(TUid::Uid(KEikCustomColorsArrayValue),201)==KRgbDarkCyan);
	CleanupStack::PopAndDestroy(list);
	//restore original file
//	User::LeaveIfError(fs.Delete(KColorSchemeFile));
//	if (BaflUtils::FileExists(fs,KColorSchemeFileOriginalRenamed))
//		{
//		User::LeaveIfError(fs.Rename(KColorSchemeFileOriginalRenamed,KColorSchemeFile));
//		}
	}

void CT_ColorStep::DoOomTestsL()
	{
	TestColorArrayL();
	CColorList* list=TestColorListLC();
	TestColorUtilsL(*list);
	CleanupStack::PopAndDestroy(list);
	}

/**
	@SYMTestCaseID UIF-egul-TestColorOom

	@SYMPREQ

	@SYMTestCaseDesc
	Test basic functionality of the CColorArray, CColorList and ColorUtils classes under low memory conditions.

	@SYMTestPriority High

	@SYMTestStatus Implemented

	@SYMTestActions
	Perform the CT_ColScm_TestColorArray, CT_ColScm_TestColorList, and CT_ColScm_TestColorUtils test cases
	under low memory conditions, where each memory allocation is made to fail once.

	@SYMTestExpectedResults
	All methods should report KErrNoMemory if they cannot allocate sufficient memory to complete.
	All methods should recover gracefully from low memory situations and subsequently succeed when sufficient
	memory is available.

*/
void CT_ColorStep::TestColorOomL()
	{
	TInt err=KErrNoMemory;
	for (TInt ii=0;err==KErrNoMemory;ii++)
		{
		__UHEAP_FAILNEXT(ii);
		__UHEAP_MARK;
		TRAP(err,DoOomTestsL());
		__UHEAP_MARKEND;
		}
	__UHEAP_SETFAIL(RHeap::ENone,0);
	User::LeaveIfError(err);
	}

void CT_ColorStep::SetSystemColorSchemeL(const TDesC8& aBuffer)
	{ // static
	CRepository* const repository=CRepository::NewL(TUid::Uid(KUidSystemColorRepository));
	CleanupStack::PushL(repository);
	User::LeaveIfError(repository->Set(KSystemColorRepositoryKey, aBuffer));
	CleanupStack::PopAndDestroy(repository);
	}

/**
   @SYMTestCaseID UIF-egul-FileLengthTestL
  
   @SYMPREQ DEF043427
  
   @SYMTestCaseDesc
   Color scheme file should be checked for zero length.\n
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
  
   @SYMTestActions
   Open the color scheme file in write mode and set its length as zero.\n
   API Calls:
   static CColorList* ColorUtils::CreateSystemColorListL(RFs& aFs);\n
  
   @SYMTestExpectedResults
   If the file length is zero then it should be deleted and the \n
   CreateSystemColorListL should return NULL.\n
  
 */
void CT_ColorStep::FileLengthTestL()
	{
	SetSystemColorSchemeL(KNullDesC8);

	CColorList* colorlist=NULL;
	TRAPD(err,colorlist=ColorUtils::CreateSystemColorListL(iFs));

	TEST(err == KErrNone);
	TEST(colorlist == NULL);
	}

/**
   @SYMTestCaseID UIF-egul-CorruptFileTest
  
   @SYMPREQ DEF043427
  
   @SYMTestCaseDesc
   Color scheme file length should be set to abnormal value.\n
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
  
   @SYMTestActions
   Open the color scheme file in write mode and set its length as half.\n
   the actual file length.
  
   API Calls:
   static CColorList* ColorUtils::CreateSystemColorListL(RFs& aFs);\n
  
   @SYMTestExpectedResults
   CreateSystemColorListL should return NULL and delete the file.
  
 */
void CT_ColorStep::CorruptFileTestL()
	{
	SetSystemColorSchemeL(_L8("blah blah some rubbish binary data\xab\xcd\xef"));

	CColorList* colorlist=NULL;
	TRAPD(err,colorlist=ColorUtils::CreateSystemColorListL(iFs));

	TEST(err == KErrNone);
	TEST(colorlist == NULL);
	}


CT_ColorStep::~CT_ColorStep()
/**
   Destructor
 */
	{
	iFs.Close();
	}

CT_ColorStep::CT_ColorStep()
/**
   Constructor
 */
	{
	// Call base class method to set up the human readable name for logging
	SetTestStepName(KT_ColorStep);
	}


void CT_ColorStep::ConstructAppL(CEikonEnv* aCoeEnv)
	{
	/** CEikonEnv will install a CEikEnvDataStorage object instance to access the EikSrv data cage.
	    Using the system colour scheme from EikSrv for these tests causes problems in the rest of the system,
	    (e.g. Shell app panics with EEgulPanicLogicalColorNotFound) because these tests set up a non-standard
	    colour scheme.
	
	    So, here we remove the CEikEnvDataStorage object and install a test data storage object
	    that stores the colour scheme file in c:\\EGulTest\\, keeping it out of the way of everything else.
	*/
	aCoeEnv->ConstructL();
	CTestColorUi* appUi=new(ELeave) CTestColorUi(*this);
	appUi->ConstructL();
	aCoeEnv->SetAppUi(appUi);
	}

TVerdict CT_ColorStep::doTestStepL()
	{
	INFO_PRINTF1(_L("Test Started"));

	PreallocateHALBuffer();

	__UHEAP_MARK;

	User::LeaveIfError(iFs.Connect());
	CEikonEnv* coe=new(ELeave) CEikonEnv;
	TRAPD(err,ConstructAppL(coe));
	if (!err)
		coe->ExecuteD();
	else
		{
		SetTestStepResult(EFail);
		delete coe;
		}

	INFO_PRINTF1(_L("Test Finished"));

	__UHEAP_MARKEND;
	return TestStepResult();
	}


