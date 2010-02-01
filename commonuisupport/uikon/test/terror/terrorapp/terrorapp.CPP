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


#include "terrorapp.h"



_LIT(KTErrorAppErrorSrc, "z:\\system\\test\\terror\\terrorapp_errors.rsc");
_LIT(KTErrorAppErrorTgt, "c:\\resource\\apps_errors\\terrorapp_errors.rsc");
const TInt KTErrorAppFailure = -1199;	// random test failure


//
//
// CErrorAppUi
//
//

CErrorAppUi::CErrorAppUi() : CTestAppUi(NULL, KNullDesC)
  {
  }

void CErrorAppUi::ConstructL()
    {
   	CTestAppUi::ConstructL();
   	
   	// Connect to test utils server
	RSmlTestUtils utils;	
	User::LeaveIfError(utils.Connect());   	
	CleanupClosePushL(utils);

	// create resource error folder for apps
	TInt err = utils.CreateDirectoryL(KTErrorAppErrorTgt);
	if(err != KErrNone && err != KErrAlreadyExists)
		{
		RDebug::Print(_L("*** CErrorAppUi::ConstructL failed to create app error resource folder (%d)"), err);
		User::LeaveIfError(err);
		}
		
	// remove previous app error resource, if any
	err = utils.DeleteFileL(KTErrorAppErrorTgt);
	if((err != KErrNone) && (err != KErrNotFound) && (err != KErrPathNotFound))
		{
		RDebug::Print(_L("*** CErrorAppUi::ConstructL failed to delete old app error resource file (%d)"), err);
		User::LeaveIfError(err);
		}
	
	// copy the error resource across
	err = utils.CopyFileL(KTErrorAppErrorSrc, KTErrorAppErrorTgt);
	if(err != KErrNone)
		{
		RDebug::Print(_L("*** CErrorAppUi::ConstructL failed to copy app error resource file to ram (%d)"), err);
		User::LeaveIfError(err);
		}
	
	// clean-up
	CleanupStack::PopAndDestroy(&utils);

	// auto start for the tests
	AutoTestManager().StartAutoTest();
	}


void CErrorAppUi::AppCleanUpL()
	{
	// the application should clean after itself...remove copied resource files!
	RSmlTestUtils utils;	
	User::LeaveIfError(utils.Connect());   	
	CleanupClosePushL(utils);

	// remove read-only attributes (as it was kept from rom)
	TInt err = utils.SetReadOnly(KTErrorAppErrorTgt, 0);
	if(err != KErrNone)
		{
		RDebug::Print(_L("*** CErrorAppUi::TestErrorMessageL failed to set read-only attribute (%d)"), err);
		User::LeaveIfError(err);
		}
	
	// remove file
	err = utils.DeleteFileL(KTErrorAppErrorTgt);
	if(err != KErrNone)
		{
		RDebug::Print(_L("*** CErrorAppUi::TestErrorMessageL failed to delete file (%d)"), err);
		User::LeaveIfError(err);
		}

	// clean-up
	CleanupStack::PopAndDestroy(&utils);
	}



CErrorAppUi::~CErrorAppUi()
	{
	}

void CErrorAppUi::HandleCommandL(TInt /*aCommand*/)
	{
	}

void CErrorAppUi::TestErrorMessageL()
	{
	CEikonEnv* coeEnv = CEikonEnv::Static();
	CEikErrorResolver* errRes=CEikErrorResolver::NewL(*coeEnv);
	CleanupStack::PushL(errRes);

	// resolve the error...
	TBuf<40> appErrText;
	errRes->ResolveError(appErrText,KErrorAppId, KUidErrorApp);	
	CleanupStack::PopAndDestroy(errRes);
	
	// clean-up of copied files 
	AppCleanUpL();	
	
	// Kill this application with the appropiate error message	
	if(appErrText != KErrorAppSpecificText)
		{
		RProcess().Terminate(KTErrorAppFailure);
		}
	else
		{
		RProcess().Terminate(KErrNone);
		}
	}

void CErrorAppUi::RunTestStepL(TInt aNumStep)
	{
	switch(aNumStep)
		{
		case 1:	
			{
			TRAPD(err, TestErrorMessageL());
			User::LeaveIfError(err);
			break;
			}
		default:
			break;
		}
	
	}

//
//
// CErrorDocument
//
//
CErrorDocument::CErrorDocument(CEikApplication& aApp)
		: CEikDocument(aApp)
	{
	}

CEikAppUi* CErrorDocument::CreateAppUiL()
	{
	return new (ELeave) CErrorAppUi();
    }


//
//
// CErrorApplication
//
//
TUid CErrorApplication::AppDllUid() const
	{
	return KUidErrorApp;
	}

CApaDocument* CErrorApplication::CreateDocumentL()
	{
	return new (ELeave) CErrorDocument(*this);
	}

LOCAL_C CApaApplication* NewApplication()
	{
	return new CErrorApplication;
	}

GLDEF_C TInt E32Main()
	{
	return EikStart::RunApplication(NewApplication);
	}

