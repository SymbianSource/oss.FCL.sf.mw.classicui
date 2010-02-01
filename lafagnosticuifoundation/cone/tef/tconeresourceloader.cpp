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

#include "tconeresourceloader.h"
#include <eikenv.h>

_LIT(KConeResourceLoaderPath,"z:\\resource\\apps\\tconeresourceloader.rsc");

CTConeResourceLoaderAppUi::CTConeResourceLoaderAppUi(CTConeResourceLoaderStep& aStep) 
: CTestAppUi(&aStep, KConeResourceLoaderPath)
	{
	}

void CTConeResourceLoaderAppUi::ConstructL()
	{
	CTestAppUi::ConstructL();
	AutoTestManager().StartAutoTest();
	}

CTConeResourceLoaderAppUi::~CTConeResourceLoaderAppUi()
	{
	}

void CTConeResourceLoaderAppUi::RunTestStepL(TInt aStep)
	{
	switch (aStep)
		{
		case 1:
			SetTestStepID(_L("UIF-CONE-0026"));			
			INFO_PRINTF1(_L("Test Cone resource loader"));
			TestConeResourceLoader();
			INFO_PRINTF1(_L("Test Cone resource loader Completed"));
			RecordTestResultL();			
			break;
		case 2:
			SetTestStepID(_L("UIF-CONE-0027"));			
	  		INFO_PRINTF1(_L("Start OOM test for Cone Resource Loader"));
	  		TestOOMConeResourceLoader();
			INFO_PRINTF1(_L("OOM test for Cone Resource Loader Completed"));
			RecordTestResultL();
			CloseTMSGraphicsStep();
			break;	
		case 3:
			AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
			break;
		default:
			break;
		}
	}

/**
   @SYMTestCaseID UIF-CONE-0026
  
   @SYMREQ 7736
  
   @SYMTestCaseDesc Tests the RCoeResourceLoader::OpenL(), RCoeResourceLoader::Open() and RCoeResourceLoader::Close() methods.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The OpenL() and Open() methods opens the given resource file. 
   					Close() method closes the resource file if it is open.
   
   @SYMTestExpectedResults  1. OpenL() and Open() methods open the given resource file and leaves and returns 
   							   with KErrNone respectively.  
   							2. The OpenL() leaves with KErrNotSupported if the given resource file is already open.
   							3. Close() method closes the given resource file.
   							4. The OpenL() leaves with KErrNotFound if the given resource file is not found.
   							5. Close() method returns correctly if it called on resource file which not opened using resource loader.
   							
 */
void CTConeResourceLoaderAppUi::TestConeResourceLoader()
	{
	TInt ret(KErrNone);
    TFileName fileName(KConeResourceLoaderPath);
    
    RCoeResourceLoader resourceLoader(*iCoeEnv);
        	
	TRAP(ret, resourceLoader.OpenL(fileName));
	TEST(ret == KErrNone);
	
	// Try to open an already open file.
	INFO_PRINTF1(_L("Try to open a file which is already open, using Cone resource loader"));
	TRAP(ret, resourceLoader.OpenL(fileName));
	TEST(ret == KErrNotSupported);
	resourceLoader.Close();

	ret = resourceLoader.Open(fileName);
	TEST(ret == KErrNone);
	resourceLoader.Close();
	
	// Try to open an non-existing file.
	INFO_PRINTF1(_L("Try to open a file which is not present, using Cone resource loader"));
	fileName = _L("c:\\system\\data\\trial.rsc");
	TRAP(ret, resourceLoader.OpenL(fileName));
	TEST(ret==KErrNotFound || ret==KErrPathNotFound);
	if (ret!=KErrNotFound)
		{
		if (ret==KErrPathNotFound)
			{
			_LIT(KLog,"WARNING!! Opening non existent resouce file %S gave error KErrPathNotFound (%d) expecting KErrNotFound");
			INFO_PRINTF3(KLog,&fileName,ret);
			}
		else
			{
			_LIT(KLog,"Opening non existent resouce file %S gave unexpected error %d (should have been KErrNotFound: %d)");
			INFO_PRINTF4(KLog,&fileName,ret,KErrNotFound);
			}
		}
	INFO_PRINTF1(_L("Try to close a file which is not open using Cone resource loader"));
	resourceLoader.Close();
	}

/**
   @SYMTestCaseID UIF-CONE-0027
  
   @SYMREQ 7736
  
   @SYMTestCaseDesc Tests RCoeResourceLoader::OpenL() method when device goes Out of Memory.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions Calls OpenL() under OOM condition
   
   @SYMTestExpectedResults Tests should complete without any memory leaks.
 */
void CTConeResourceLoaderAppUi::TestOOMConeResourceLoader()
	{
    TFileName fileName(KConeResourceLoaderPath);
    
    RCoeResourceLoader resourceLoader(*iCoeEnv);
	//OOM test for RCoeResourceLoader::OpenL() method.
	for (TInt fail = 1;; fail++)
		{
		__UHEAP_SETFAIL(RHeap::EDeterministic, fail);
		__UHEAP_MARK;
		TRAPD(ret, resourceLoader.OpenL(fileName));
		TEST((ret == KErrNone) || (ret == KErrNoMemory));
		if (ret == KErrNone)
			{
			resourceLoader.Close();
			__UHEAP_MARKEND;
			break;
			}
		__UHEAP_MARKEND;
		}
	__UHEAP_RESET;	
	}

/**
   Destructor
 */
CTConeResourceLoaderStep::~CTConeResourceLoaderStep()
	{
	}

/**
   Constructor
 */	
CTConeResourceLoaderStep::CTConeResourceLoaderStep()
	{
	// Call base class method to set up the human readable name for logging
	SetTestStepName(KTConeResourceLoader);
	}
	
void CTConeResourceLoaderStep::ConstructAppL(CEikonEnv* aEikEnv)
	{
	aEikEnv->ConstructL();
	CTConeResourceLoaderAppUi* appUi=new(ELeave) CTConeResourceLoaderAppUi(*this);
	appUi->ConstructL();
	aEikEnv->SetAppUi(appUi);
	}

TVerdict CTConeResourceLoaderStep::doTestStepL()
	{
	INFO_PRINTF1(_L("Cone Resource Loader Test"));
	__UHEAP_MARK;

	CEikonEnv* coe = new(ELeave) CEikonEnv;
	TRAPD(err, ConstructAppL(coe));
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
