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




#include "messageservserver.h"
#include "messageservsession.h"


/**
   Constructor
 */
CMessageServServer::CMessageServServer(TInt aPriority)
	: CServer2(aPriority)
	{
	__DECLARE_NAME(_S("CMessageServServer"));
	}


/**
   Auxiliary function for TestCaseID TPACKAGESTARTER-doTestStepL
  
   The method creates and start a the message server by invoking
   CServer::Start().
  
 */
void CMessageServServer::New(MMessageProvider *aMessageProvider)
	{
	CMessageServServer *pS=new CMessageServServer(EPriority);
	__ASSERT_ALWAYS(pS!=NULL,PanicServer(ESvrCreateServer));
	HBufC *pN=(&KMessageServerName)->Alloc();
	__ASSERT_ALWAYS(pN!=NULL,PanicServer(ESvrCreateServer));
	
	pS->iMessageProvider = aMessageProvider;
	
	TInt r=pS->Start(*pN);
	__ASSERT_ALWAYS(r==KErrNone,PanicServer(ESvrStartServer));
	}


/**
   Auxiliary function for TestCaseID TPACKAGESTARTER-doTestStepL.
 
   This method identifies the client thread. It then creates an returns a server
   session for the client. The new server session is created by calling 
   CMessageServSession::NewL().
 
*/
CSession2 *CMessageServServer::NewSessionL(const TVersion &aVersion, const RMessage2& ) const
	{
	// check we're the right version
	TVersion v(KMessageServMajorVersionNumber,KMessageServMinorVersionNumber,KMessageServBuildVersionNumber);
	if (!User::QueryVersionSupported(v,aVersion))
		User::Leave(KErrNotSupported);
	// make new session
	//RThread thread;// = Message().Client();
	//aMessage.Client(thread);

	return CMessageServSession::NewL((CMessageServServer*)this);
	}
	
/**
  
   Auxiliary function for TestCaseID TPACKAGESTARTER-doTestStepL
  
   The method creates & installs an active scheduler for the server thread. It
   then creates & a message server instance by calling CMessageServServer::New().
   The message server is then set ready to run by invoking RSemaphore::Signal().
  
 */
EXPORT_C TInt CMessageServServer::ThreadFunction(TAny* anArg)
	{
	MMessageProvider *theProvider = (MMessageProvider*) anArg;

	// convert argument into semaphore reference
	RSemaphore& semaphore= theProvider->Semaphore();

	// start scheduler and server
	CActiveScheduler *pA=new CActiveScheduler;
	__ASSERT_ALWAYS(pA!=NULL,PanicServer(EMainSchedulerError));
	CActiveScheduler::Install(pA);
	CMessageServServer::New(theProvider);
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
   Auxiliary function for TestCaseID TPACKAGESTARTER-doTestStepL
  
   This method is used to panic the server thread.
  
 */
GLDEF_C void PanicServer(TMessageServPanic aPanic)
	{
	_LIT(KTxtServerPanic,"server panic");
	User::Panic(KTxtServerPanic,aPanic);
	}

