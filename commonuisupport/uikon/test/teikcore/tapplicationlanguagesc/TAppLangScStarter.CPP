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
// This test aims to test embedding feature of the application. The dll 
// launches tpackage application, all messages go via client-server
// architecture. Server leaves on the Testpackage step side and is started
// in the doTestStepL() function, client places on the tpackage application
// side. Server's thread creates and run active scheduler in order to maintain
// the active objects.\n
// It is relevant that logger uses the same thread in which it was created, 
// therefore when server receives  EMessageServSetFromString message from the 
// client it activates active object (CMessageActive) in order to output 
// log buffer into the file in the same thread as lives logger.  
// The CMessageActive class is activated by calling function 
// CMessageActive::RequestForTheMessageOutput(TInt aCode), 
// iStatus sets to aCode value.\n
// When client completes its work, it sends message  EMessageServStop and 
// server stops active sheduler so server's thread might be closed.\n
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code
*/



#include <coecntrl.h>
#include <coeccntx.h>
#include <eikdoc.h>
#include <apgcli.h>
#include <apacmdln.h>
#include <ecom/ecom.h>

#include "TAppLangScStarter.h"
#include "messageservserver.h"
#include "messageservclient.h"

#define FORCE_AUTO

CTestApplicationLanguageSCStep::CTestApplicationLanguageSCStep()
/**
   Constructor
 */
	{
	SetTestStepName(KTestApplicationLanguageSCStep);
	}

CTestApplicationLanguageSCStep::~CTestApplicationLanguageSCStep()
/**
   Destructor
 */
	{
	}

 /**
   @SYMTestCaseID UIF-TAppLangSCSTARTER-oTestStepL
  
   @SYMPREQ
  
   @SYMTestCaseDesc This test aims to test embedding feature of the application.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The dll creates a thread and starts a Message server. Once the
   message server is up and ready it launches the test client application,
   tpackage. The server installs and starts an active scheduler to service
   request messages received from the client and to log the information gathered
   from the request messages.When the server receives  EMessageServSetFromString
   message from the client, it activates CMessageActive active object in order
   to output the log buffer. When client completes its work, it sends message
   MessageServStop and server stops active sheduler so that server's thread
   might be closed. 
  
   @SYMTestExpectedResults All messages send by the client should be processed by
   the server and outputted in the log file.
   
 */
TVerdict CTestApplicationLanguageSCStep::doTestStepL() // main function called by E32
	{
	__UHEAP_MARK;
	SetTestStepID(_L("UIF-TAppLangSCSTARTER-oTestStepL"));
	CActiveScheduler*	theSheduler = new CActiveScheduler;
    CActiveScheduler::Install(theSheduler);

	iMessage = CMessageActive::NewL();
	iMessage->iStep = this;

	_LIT(KPackageAppFileName,"z:\\sys\\bin\\TAPPLANGUAGESC.exe");

	CApaCommandLine* cmdLine=CApaCommandLine::NewLC();	
	cmdLine->SetCommandL(EApaCommandViewActivate);
	cmdLine->SetDocumentNameL(_L("jhghjg"));
	cmdLine->SetExecutableNameL(KPackageAppFileName);

	StartThread();

	RApaLsSession ls;
	User::LeaveIfError(ls.Connect());
	CleanupClosePushL(ls);
	TInt err = ls.StartApp(*cmdLine);
	if (err != KErrNone)
		{
		TEST(EFalse);
		INFO_PRINTF1(_L("Failed to start application"));
		// If there is a problem starting the app we have to stop the 
		// message server
		RMessageServ serv;
		TInt theRes = serv.Connect();
		if(theRes == KErrNone)
			{
			serv.Stop();	
			serv.Close();
			// Now make sure we wait until the server has stopped
			// Not sure this is necessary but safer
			while (ETrue)
				{
				TFindServer findCountServer(KMessageServerName);
				TFullName name;
				if (findCountServer.Next(name)!=KErrNone)
					{
					break;			
					}
				}
			}
		}
	CleanupStack::PopAndDestroy(&ls);
	
	CleanupStack::PopAndDestroy(cmdLine);
	
	CActiveScheduler::Start();

	
	delete theSheduler;
	delete iMessage;
	iMessage = NULL;
	REComSession::FinalClose();	
	RecordTestResultL();
	CloseTMSGraphicsStep();
	__UHEAP_MARKEND;

	return TestStepResult();
	}


/**
   Auxiliary function for TestCaseID TAppLangSCSTARTER-doTestStepL
  
   This method creates the server thread by invoking RThread::Create() and calls
   CMessageServServer::ThreadFunction() to start the Message Server.
  
 */
TInt CTestApplicationLanguageSCStep::StartThread()
    {
	TInt res=KErrNone;
	// create server - if one of this name does not already exist
	TFindServer findCountServer(KMessageServerName);
	TFullName name;
	if (findCountServer.Next(name)!=KErrNone) // we don't exist already
		{
		RThread thread;
		semaphore.CreateLocal(0); // create a semaphore so we know when thread finished
		res=thread.Create(KMessageServerName,   // create new server thread
			CMessageServServer::ThreadFunction, // thread's main function
			KDefaultStackSize,
			KDefaultHeapSize,
			KDefaultHeapSize,
			this // passed as TAny* argument to thread function
			);

		if (res==KErrNone) // thread created ok - now start it going
			{
			thread.SetPriority(EPriorityNormal);
			thread.Resume(); // start it going
			semaphore.Wait(); // wait until it's initialized
			thread.Close(); // we're no longer interested in the other thread
			}
		else // thread not created ok
			{
			thread.Close(); // therefore we've no further interest in it
			}

		semaphore.Close();
		}

    return res;
    }


