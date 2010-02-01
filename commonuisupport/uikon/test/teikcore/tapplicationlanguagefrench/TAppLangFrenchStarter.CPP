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

#include "TAppLangFrenchStarter.h"


#define FORCE_AUTO

#define STOP_SERVER_CODE		0xff

/**
   TODO XL
   Auxiliary function for TestCaseID TAppLangFrenchSTARTER-doTestStepL
  
   This method creates an active object of class CMessageActive and adds it to
   the active scheduler.
  
 */
CMessageActive3* CMessageActive3::NewL()
	{
	CMessageActive3*	theMessage = new CMessageActive3;
    CActiveScheduler::Add(theMessage);
	
	RThread	thread;
	theMessage->iID = thread.Id();
	return theMessage;
	}
/**
   Auxiliary function for TestCaseID TAppLAngFrenchSTARTER-doTestStepL
  
   This method is an override from CActive.It handles the client message request
   completion event. On completion of copying message from client to the server
   this method logs the information gathered from the message.
  
 */
void CMessageActive3::RunL()
	{
	if(iStatus.Int() == KErrNone)
		{
		CTestExecuteLogger& logger = iStep->Logger();
		logger.LogExtra(((TText8*)(iFileName.PtrZ())), iLineNumber, ESevrInfo, iMsg);
		}
	else if(iStatus.Int() == STOP_SERVER_CODE)
		{
		CActiveScheduler::Stop();
		}
	else
		{
		CTestExecuteLogger& logger = iStep->Logger();
		iStep->testBooleanTrueWithErrorCode(0, iError, ((TText8*)(iFileName.PtrZ())), iLineNumber );
		if(iError != 0)
			{
			logger.LogExtra(((TText8*)(iFileName.PtrZ())), iLineNumber, ESevrErr, iMsg, iError);
			}
		else
			{
			logger.LogExtra(((TText8*)(iFileName.PtrZ())), iLineNumber, ESevrErr, iMsg);
			}
		}
	}

/**
   Auxiliary function for TestCaseID TAppLangFrenchSTARTER-doTestStepL
  
   This method sets the request status to be complete and sets the request to be
   outstanding so that the active scheduler invokes the RunL() method of the
   active object CMessageActive.
  
 */
void CMessageActive3::Init()
	{
	TRequestStatus *pS=(&iStatus);
	User::RequestComplete(pS,0);
	*pS=KRequestPending;
	SetActive();
	}
/**
   Auxiliary function for TestCaseID TAppLangFrenchSTARTER-doTestStepL
  
   This method is an override from CActive. It is used for cancellation of an
   outstanding request.
  
 */
void CMessageActive3::DoCancel()
	{
	}
/**
   Auxiliary function for TestCaseID TAppLangFrenchSTARTER-doTestStepL
  
   This method is used to activate CMessageActive class to output the message
   to logs.
  
 */
void CMessageActive3::RequestForTheMessageOutput(TInt aCode)
{
	RThread	thread;
	TRequestStatus *pS=(&iStatus);

	*pS=KRequestPending;
	SetActive();

	thread.Open(iID);
	thread.RequestComplete(pS, aCode);
}


CTestApplicationLanguageFrenchStep::CTestApplicationLanguageFrenchStep()
/**
   Constructor
 */
	{
	SetTestStepName(KTestApplicationLanguageFrenchStep);
	}

CTestApplicationLanguageFrenchStep::~CTestApplicationLanguageFrenchStep()
/**
   Destructor
 */
	{
	}

/**
   @SYMTestCaseID UIF-TAppLangFrenchSTARTER-doTestStepL
  
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
   EMessageServStop and server stops active sheduler so that server's thread
   might be closed. 
  
   @SYMTestExpectedResults All messages send by the client should be processed by
   the server and outputted in the log file.
   
 */
TVerdict CTestApplicationLanguageFrenchStep::doTestStepL() // main function called by E32
	{
	__UHEAP_MARK;
	SetTestStepID(_L("UIF-TAppLangFrenchSTARTER-doTestStepL"));
	CActiveScheduler*	theSheduler = new CActiveScheduler;
    CActiveScheduler::Install(theSheduler);

	iMessage = CMessageActive3::NewL();
	iMessage->iStep = this;

	_LIT(KPackageAppFileName,"z:\\sys\\bin\\TAPPLANGUAGEFRENCH.exe");

	CApaCommandLine* cmdLine=CApaCommandLine::NewLC();	
	cmdLine->SetCommandL(EApaCommandViewActivate);
	cmdLine->SetDocumentNameL(_L("jhghjg"));
	cmdLine->SetExecutableNameL(KPackageAppFileName);

	StartThread();

	RApaLsSession ls;
	User::LeaveIfError(ls.Connect());
	CleanupClosePushL(ls);
	User::LeaveIfError(ls.StartApp(*cmdLine));
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



//CMessageServServer

CMessageServServer3::CMessageServServer3(TInt aPriority)
	: CServer2(aPriority)
/**
   Constructor
 */
	{
	__DECLARE_NAME(_S("CMessageServServer"));
	}


/**
   Auxiliary function for TestCaseID TAppLangFrenchSTARTER-doTestStepL
  
   The method creates and start a the message server by invoking
   CServer::Start().
  
 */
void CMessageServServer3::New(CTestApplicationLanguageFrenchStep *aStep)
	{
	CMessageServServer3 *pS=new CMessageServServer3(EPriority);
	__ASSERT_ALWAYS(pS!=NULL,PanicServer3(ESvrCreateServer3));
	HBufC *pN=(&KMessageServerName3)->Alloc();
	__ASSERT_ALWAYS(pN!=NULL,PanicServer3(ESvrCreateServer3));
	
	pS->iStep = aStep;
	
	TInt r=pS->Start(*pN);
	__ASSERT_ALWAYS(r==KErrNone,PanicServer3(ESvrStartServer3));
	}


/**
   Auxiliary function for TestCaseID TAppLangFrenchSTARTER-doTestStepL.
  
   This method identifies the client thread. It then creates an returns a server
   session for the client. The new server session is created by calling 
   CMessageServSession::NewL().
  
 */
CSession2 *CMessageServServer3::NewSessionL(const TVersion &aVersion, const RMessage2& ) const
	{
	// check we're the right version
	TVersion v(KMessageServMajorVersionNumber3,KMessageServMinorVersionNumber3,KMessageServBuildVersionNumber3);
	if (!User::QueryVersionSupported(v,aVersion))
		User::Leave(KErrNotSupported);
	// make new session
	//RThread thread;// = Message().Client();
	//aMessage.Client(thread);

	return CMessageServSession3::NewL((CMessageServServer3*)this);
	}


//CMessageServSession

CMessageServSession3::CMessageServSession3(CMessageServServer3 * aServer)
	: CSession2()//aClient)
/**
   Constructor - passes client to CSession.
 */
	{
	__DECLARE_NAME(_S("CMessageServSession3"));
	iMsgSvr=aServer;
	}

/**
   Auxiliary function for TestCaseID TAppLangFrenchSTARTER-doTestStepL
  
   This method creates a Server session for a client thread aClient.
  
 */
CMessageServSession3* CMessageServSession3::NewL(CMessageServServer3 * aServer)
	{
	return new(ELeave) CMessageServSession3(aServer);
	}

/**
   Auxiliary function for TestCaseID TAppLangFrenchSTARTER-doTestStepL
  
   This method handles the servicing of client requests to the message server.
   The message is serviced by calling CMessageServSession::DispatchMessageL()
   and signals completion of the client request by invoking RMessage::Complete().
  
 */
void CMessageServSession3::ServiceL(const RMessage2& aMessage)
	{
	TRAPD(err,DispatchMessageL(aMessage));
	aMessage.Complete(err);
	}



/**
   Auxiliary function for TestCaseID TAppLangFrenchSTARTER-doTestStepL
  
   This method services the client requests to the message server.
   The opcode is checked and does approprate servicing by invoking methods
   SetFromStringL() and SetErrorFromStringL().
  
 */
void CMessageServSession3::DispatchMessageL(const RMessage2 &aMessage)
	{
	switch (aMessage.Function())
        {
	case EMessageServSetFromString3:
		SetFromStringL(aMessage);
		return;
	case EMessageServSetErrorFromString3:
		SetErrorFromStringL(aMessage);
		return;
	case EMessageServStop3:
		{	
			CActiveScheduler::Stop();
			
			iMsgSvr->iStep->iMessage->RequestForTheMessageOutput(STOP_SERVER_CODE);
			return;
		}
	// requests we don't understand at all are a different thing,
	// so panic the client here, this function also completes the message
	default:
		PanicClient(EBadRequest3);
		return;
        }
	}


/**
   Auxiliary function for TestCaseID TAppLangFrenchSTARTER-doTestStepL
  
   This method services Error message received from the client to the message
   server. It reads Error message, filename, line number and error code from
   the message
  
 */
void CMessageServSession3::SetErrorFromStringL(const RMessage2 &aMessage)
	{
	TInt res;
	//const TAny* pD=aMessage.Ptr0();
	TInt desLen=aMessage.GetDesLength(0);
	HBufC* writeBuf=HBufC::New(desLen);
	TPtr initptr = writeBuf->Des();
	TRAP(res,aMessage.ReadL(0,initptr));

	//const TAny* pD1=aMessage.Ptr1();
	TInt desLen1=aMessage.GetDesLength(1);//pD1);
	HBufC8* writeBuf1=HBufC8::New(desLen1);
	TPtr8 initptr1 = writeBuf1->Des();
	TRAP(res,aMessage.ReadL(1,initptr1));


	const TInt lineNumber = aMessage.Int2();
	const TInt errorCode = aMessage.Int3();

	// read the contents of the client pointer into a TPtr.

	if (res!=KErrNone)
		PanicClient(EBadDescriptor3);
	
	iMsgSvr->iStep->iMessage->iError = errorCode;
	iMsgSvr->iStep->iMessage->iLineNumber = lineNumber;
	iMsgSvr->iStep->iMessage->iMsg.Copy(initptr);
	iMsgSvr->iStep->iMessage->iFileName.Copy(initptr1);

	delete writeBuf;
	delete writeBuf1;
	
	iMsgSvr->iStep->iMessage->RequestForTheMessageOutput(errorCode);
	}


/**
   Auxiliary function for TestCaseID TAppLangFrenchSTARTER-doTestStepL
  
   This method demonstrates reading message from the client address space to
   the server. It reads filename, line number and descriptor content from
   the message
  
 */
void CMessageServSession3::SetFromStringL(const RMessage2 &aMessage)
	{
	TInt res;
	//const TAny* pD=aMessage().Ptr0();
	TInt desLen=aMessage.GetDesLength(0);
	HBufC* writeBuf=HBufC::New(desLen);
	TPtr initptr = writeBuf->Des();
	TRAP(res,aMessage.ReadL(0,initptr));

	//const TAny* pD1=Message().Ptr1();
	TInt desLen1=aMessage.GetDesLength(1);
	HBufC8* writeBuf1=HBufC8::New(desLen1);
	TPtr8 initptr1 = writeBuf1->Des();
	TRAP(res,aMessage.ReadL(1,initptr1));


	const TInt lineNumber = aMessage.Int2();

	// read the contents of the client pointer into a TPtr.

	if (res!=KErrNone)
		PanicClient(EBadDescriptor3);
	
	iMsgSvr->iStep->iMessage->iLineNumber = lineNumber;
	iMsgSvr->iStep->iMessage->iMsg.Copy(initptr);
	iMsgSvr->iStep->iMessage->iFileName.Copy(initptr1);

	delete writeBuf;
	delete writeBuf1;
	
	iMsgSvr->iStep->iMessage->RequestForTheMessageOutput();
	}



// write to the client thread; if unsuccessful, panic the client
//void CMessageServSession::Write(const TAny* aPtr,const TDesC8& aDes,TInt anOffset)
//	{
//	Write(aPtr,aDes,anOffset);
	//if (ret!=KErrNone)
	//	PanicClient(EBadDescriptor3);
//	}


/**
   Auxiliary function for TestCaseID TAppLangFrenchSTARTER-doTestStepL
  
   This method is used to Panic the client thread
  
 */
void CMessageServSession3::PanicClient(TInt aPanic) const
	{
	_LIT(KTxtServer,"CountServ server");
	User::Panic(KTxtServer,aPanic);
	}


/**
  
   Auxiliary function for TestCaseID TAppLangFrenchSTARTER-doTestStepL
  
   The method creates & installs an active scheduler for the server thread. It
   then creates & a message server instance by calling CMessageServServer::New().
   The message server is then set ready to run by invoking RSemaphore::Signal().
  
 */
GLDEF_C TInt CMessageServServer3::ThreadFunction(TAny* anArg)
	{
	
	CTestApplicationLanguageFrenchStep *theStep = (CTestApplicationLanguageFrenchStep*) anArg;

	// convert argument into semaphore reference
	RSemaphore& semaphore= theStep->semaphore;//(RSemaphore *)anArg;

	// start scheduler and server
	CActiveScheduler *pA=new CActiveScheduler;
	__ASSERT_ALWAYS(pA!=NULL,PanicServer3(EMainSchedulerError3));
	CActiveScheduler::Install(pA);
	CMessageServServer3::New(theStep);
	// signal that we've started
	semaphore.Signal();
	// start fielding requests from clients
	CActiveScheduler::Start();
	// finished
	
	//Adding a delay here seems to fix the crash on multicore SMP naviengine
	User::After(200000);
	
	return(KErrNone);
	}


/**
   Auxiliary function for TestCaseID TAppLangFrenchSTARTER-doTestStepL
  
   This method is used to panic the server thread.
 */

GLDEF_C void PanicServer3(TMessageServPanic3 aPanic)
	{
	_LIT(KTxtServerPanic,"server panic");
	User::Panic(KTxtServerPanic,aPanic);
	}


/**
   Auxiliary function for TestCaseID TAppLangFrenchSTARTER-doTestStepL
  
   This method creates the server thread by invoking RThread::Create() and calls
   CMessageServServer::ThreadFunction() to start the Message Server.
  
 */
TInt CTestApplicationLanguageFrenchStep::StartThread()
    {
	TInt res=KErrNone;
	// create server - if one of this name does not already exist
	TFindServer findCountServer(KMessageServerName3);
	TFullName name;
	if (findCountServer.Next(name)!=KErrNone) // we don't exist already
		{
		RThread thread;
		semaphore.CreateLocal(0); // create a semaphore so we know when thread finished
		res=thread.Create(KMessageServerName3,   // create new server thread
			CMessageServServer3::ThreadFunction, // thread's main function
			KDefaultStackSize,
			KDefaultHeapSize3,
			KDefaultHeapSize3,
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
    
