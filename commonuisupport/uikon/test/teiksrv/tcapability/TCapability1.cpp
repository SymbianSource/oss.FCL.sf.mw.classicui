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
// The following test case is used to test whether uiktestserver has the capability
// to access writable apis
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code
*/

#include "TCapability1.h"
#include <e32def.h>
#include "eiksrvc.h"
#include <e32test.h>
#include <test/appfwk_test.h>




/**
   @SYMTestCaseID		UIF-UIKON-0001
  
   @SYMPREQ				Policing server apis		
  
   @SYMTestCaseDesc 	Testing whether uiktestserver has the capability to access writable apis
  
   @SYMTestPriority 	High
  
   @SYMTestStatus 		Implemented
   
   @SYMTestActions  
   To connect to REikAppUiSession and to check whether uiktestserver process
   has the permission to access the mentioned apis
   API Calls:\n		
   REikAppUiSession::Connect();
   REikAppUiSession::OpenFepAttributes();
   REikAppUiSession::SetInstalledFepName(const TDesC& aName, TBool aRaiseFileError) const;
   REikAppUiSession::SetFepAttribute(TUid aAttribUid, const TDesC8& aAttribData) const;
   REikAppUiSession::CommitFepAttributes() const ;
   @SYMTestExpectedResults Test should complete without any panic.
   
 */
void CTCapability1Step::ExecuteL()
	{
	TInt ret;
	REikAppUiSession uiSession;

	TEST(uiSession.Connect()==KErrNone);
	CleanupClosePushL(uiSession);

	TSecurityInfo info;
	info.Set(RProcess());
	
	APPFWK_NEGATIVE_PLATSEC_START;
	ret=uiSession.SetInstalledFepName(KNullDesC,FALSE);
	APPFWK_NEGATIVE_PLATSEC_FINISH;
	INFO_PRINTF1(_L("Capability check of SetInstalledFepName"));
	INFO_PRINTF3(_L("Expected return code: %d, Actual return code: %d"), KErrPermissionDenied, ret);
	TEST(ret==KErrPermissionDenied);

	uiSession.OpenFepAttributes();

	APPFWK_NEGATIVE_PLATSEC_START;
	ret=uiSession.SetFepAttribute(KNullUid,KNullDesC8);
	APPFWK_NEGATIVE_PLATSEC_FINISH;
	INFO_PRINTF1(_L("Capability check of SetInstalledFepName"));
	INFO_PRINTF3(_L("Expected return code: %d, Actual return code: %d"), KErrPermissionDenied, ret);
	TEST(ret==KErrPermissionDenied);

	CleanupStack::PopAndDestroy(&uiSession);
	}

CTCapability1Step::CTCapability1Step()
/**
   Constructor
 */
	{
	// Call base class method to set up the human readable name for logging
	SetTestStepName(KTCapability1Step);
	}

CTCapability1Step::~CTCapability1Step()
	{
	}

TVerdict CTCapability1Step::doTestStepL()
    {
	INFO_PRINTF1(_L("UIF-UIKON-0001: Capability1 - Started"));
	
	__UHEAP_MARK; // mark heap state
	SetTestStepID(_L("UIF-UIKON-0001"));

	TRAPD(error,ExecuteL()); // do most stuff under cleanup stack
	__ASSERT_ALWAYS(!error,User::Panic(_L("TestParse"),error));

	RecordTestResultL();
	CloseTMSGraphicsStep();
	__UHEAP_MARKEND; // check no memory leak

	INFO_PRINTF1(_L("UIF-UIKON-0001: Capability1 - Finished"));

	return TestStepResult();
	}
