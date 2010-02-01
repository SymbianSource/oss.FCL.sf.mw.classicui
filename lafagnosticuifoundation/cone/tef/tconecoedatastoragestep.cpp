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
// The test step corrupts the system colorlist and colorlist is populated 
// again using PopulateColorArrayL API and OOM tests are performed.
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code.
*/


#include "tconecoedatastoragestep.h"
#include "coedatastorage.h"
#include <centralrepository.h>
#include <gulcolor.h>


/**
Constant Value KUidSystemColorRepository obtained from CoeDataStorage.cpp
*/
const TUint KUidSystemColorRepository = 0x10272619;
const TUint KSystemColorRepositoryKey = 0;

CTConeCoeDataStorageStep::CTConeCoeDataStorageStep()
/**
Constructor
*/
	{
	SetTestStepName(KTConeCoeDataStorageStep);
	}

CTConeCoeDataStorageStep::~CTConeCoeDataStorageStep()
/**
Destructor
*/
	{
	}
	
/**
  @SYMTestCaseID UIF-TConeCoeDataStorageStep-TestPopulateColorArrayOOML
 
  @SYMPREQ
 
  @SYMTestCaseDesc Tests PopulateColorArrayL API with forced memory allocation failure.\n
 
  @SYMTestPriority High
 
  @SYMTestStatus Implemented
  
  @SYMTestActions : Creating the colorlist using PopulateColorArrayL API  .\n
  The system colorlist is corrupted and PopulateColorArrayL API is invoked to populate the colorlist.\n
      
  @SYMTestExpectedResults : PopulateColorArrayL method should report KErrNoMemory if it cannot allocate sufficient \n 
	memory and recover gracefully from low memory situations and subsequently succeed in creating the colorlist when \n
	sufficient memory is available.\n
 
  @SYMTestType : CIT
*/
void CTConeCoeDataStorageStep::TestPopulateColorArrayOOML()
	{
	TInt err = KErrNoMemory;
	TInt ii;
	//The ideal loop condition is err==KErrNoMemory, it is changed
	//because PopulateColorArrayL API invokes GetSystemColorListL() which has TRAP function,
	//which captures the KErrNoMemory condition and the PopulateColorArrayL API doesn't leave
	//with any memory allocation failure. In order to make sure that PopulateColorArrayL API 
	//leaves with memory allocation failure and also to create successfully the colorlist 
	//the loop has to run for 70 times. 
	INFO_PRINTF1(_L("Tests After Corrupting the System Colorlist"));
	for (ii=1; ii<70; ii++)
		{
		INFO_PRINTF2(_L("The value of the iteration number is %d"), ii);
		__UHEAP_FAILNEXT(ii);
		__UHEAP_MARK;
		TRAP(err, DoOomTestsAfterCorruptingColorListL());
		INFO_PRINTF2(_L("The value of the err is %d"), err);
		__UHEAP_MARKEND;
		}
	__UHEAP_SETFAIL(RHeap::ENone,0); 
	User::LeaveIfError(err);
	}
	
/**
This functions performs the OOM Tests.
*/	
void CTConeCoeDataStorageStep::DoOomTestsAfterCorruptingColorListL()
	{
	SetSystemColorSchemeL(_L8("Some rubbish binary data\xab\xcd\xef"));
	CColorList* colorlist = NULL;
	CCoeDataStorage* dataStorage = CCoeDataStorage::NewL();
	CleanupStack::PushL(dataStorage);
	colorlist = dataStorage->PopulateColorArrayL();
	TEST(colorlist != NULL);
	delete colorlist;
    CleanupStack::PopAndDestroy(dataStorage);
	}
	
/**
This function corrupts the System Colorlist by corrupting the color scheme file. 
*/	
void CTConeCoeDataStorageStep::SetSystemColorSchemeL(const TDesC8& aBuffer)
	{ 
	CRepository* const repository = CRepository::NewL(TUid::Uid(KUidSystemColorRepository));
	CleanupStack::PushL(repository);
	User::LeaveIfError(repository->Set(KSystemColorRepositoryKey, aBuffer));
	CleanupStack::PopAndDestroy(repository);
	}
/**
  Entry function for CTConeCoeDataStorageStep Test Step.\n
  Invokes the TestPopulateColorArrayOOML function. \n
*/
TVerdict CTConeCoeDataStorageStep::doTestStepL() // main function called by E32
	{
	SetTestStepID(_L("UIF-TConeCoeDataStorageStep-TestPopulateColorArrayOOML"));
	INFO_PRINTF1(_L("Test Started"));
	TestPopulateColorArrayOOML();
	INFO_PRINTF1(_L("Test Finished"));
	RecordTestResultL();
	return TestStepResult();
	}
