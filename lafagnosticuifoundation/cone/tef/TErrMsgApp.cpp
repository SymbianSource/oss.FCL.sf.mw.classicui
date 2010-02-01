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

#include "TErrMsgApp.h"
#include <e32std.h>

CApaCommandLine* iCmdLine;

void CErrMsgTestAppUi::ConstructL()
    {
    BaseConstructL(ENoAppResourceFile | ENoScreenFurniture);
	ExecuteCmdLineL();
	}

CErrMsgTestAppUi::~CErrMsgTestAppUi()
	{
	delete iCmdLine;
	}

void CErrMsgTestAppUi::HandleCommandL(TInt /*aCommand*/)
	{
	// app is designed to execute the cmdline and exit, so should not reach
	// this point
	User::Leave(KErrGeneral);
	}


void CErrMsgTestAppUi::HandleSystemEventL(const TWsEvent& /*aEvent*/)
	{
	// app is designed to execute the cmdline and exit, so should not reach
	// this point
	User::Leave(KErrGeneral);
	}

void CErrMsgTestAppUi::ExecuteCmdLineL()
	{
	TPtrC8 tailEnd = iCmdLine->TailEnd();
	_LIT8(KTestCaseErrMsg,"UIF-CONE-0015 ErrMsg");
	_LIT8(KTestCaseErrAndConMsg,"UIF-CONE-0014 ErrAndConMsg");
	
	TBuf<32> tailEndBuf;
	tailEndBuf.Copy(tailEnd);
	RDebug::Print(_L("tail:%S"),&tailEndBuf);
	
	_LIT(KTestErrMsg, "Test Error Message");
	TBuf<80> errText(KTestErrMsg);
	RBuf testMsg;
	testMsg.CreateL(errText);
	testMsg.CleanupClosePushL();
	
	if(tailEnd==KTestCaseErrAndConMsg)
		{
		_LIT(KTestErrConMsg, "Test Context Error Message");
		TBuf<40> errConText(KTestErrConMsg);
		RBuf testConMsg;
		testConMsg.CreateL(errConText);
		testConMsg.CleanupClosePushL();
		
		iCoeEnv->LeaveWithErrorText(testMsg, &testConMsg);
		CleanupStack::PopAndDestroy(&testConMsg);
		}
	else if (tailEnd==KTestCaseErrMsg)
		{
		iCoeEnv->LeaveWithErrorText(testMsg);
		}
		
	CleanupStack::PopAndDestroy(&testMsg);
	}

CErrMsgTestDocument::CErrMsgTestDocument(CEikApplication& aApp)
		: CEikDocument(aApp)
	{
	}

CEikAppUi* CErrMsgTestDocument::CreateAppUiL()
	{
    return new(ELeave) CErrMsgTestAppUi;
	}


const TUid KUidTErrMsgApp = { 0x102827C5 }; 

TUid CErrMsgTestApp::AppDllUid() const
	{
	return KUidTErrMsgApp;
	}


TFileName CErrMsgTestApp::ResourceFileName() const
{
	return TFileName(); // this app doesn't have a resource file
}

CApaDocument* CErrMsgTestApp::CreateDocumentL()
	{
	return new (ELeave) CErrMsgTestDocument(*this);
	}


LOCAL_C CApaApplication* NewApplication()
	{
	return new CErrMsgTestApp;
	}


GLDEF_C TInt E32Main()
	{
	CApaCommandLine::GetCommandLineFromProcessEnvironment(iCmdLine);

	return EikStart::RunApplication(NewApplication);
	}
	
