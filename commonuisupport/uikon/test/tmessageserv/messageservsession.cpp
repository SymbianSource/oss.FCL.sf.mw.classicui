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


#include "messageservsession.h"

const TInt STOP_SERVER_CODE	= 0xff;


/**
   Constructor - passes client to CSession.
 */
CMessageServSession::CMessageServSession(CMessageServServer * aServer)
	: CSession2()//aClient)
	{
	__DECLARE_NAME(_S("CMessageServSession"));
	iMsgSvr=aServer;
	}

/**
   Auxiliary function for TestCaseID TPACKAGESTARTER-doTestStepL
  
   This method creates a Server session for a client thread aClient.
  
 */
CMessageServSession* CMessageServSession::NewL(CMessageServServer * aServer)
	{
	return new(ELeave) CMessageServSession(aServer);
	}

/**
   Auxiliary function for TestCaseID TPACKAGESTARTER-doTestStepL
  
   This method handles the servicing of client requests to the message server.
   The message is serviced by calling CMessageServSession::DispatchMessageL()
   and signals completion of the client request by invoking RMessage::Complete().
  
 */
void CMessageServSession::ServiceL(const RMessage2& aMessage)
	{
	TRAPD(err,DispatchMessageL(aMessage));
	aMessage.Complete(err);
	}

/**
   Auxiliary function for TestCaseID TPACKAGESTARTER-doTestStepL
  
   This method services the client requests to the message server.
   The opcode is checked and does approprate servicing by invoking methods
   SetFromStringL() and SetErrorFromStringL().
  
 */
void CMessageServSession::DispatchMessageL(const RMessage2 &aMessage)
	{
	switch (aMessage.Function())
        {
	case EMessageServSetFromString:
		SetFromStringL(aMessage);
		return;
	case EMessageServSetErrorFromString:
		SetErrorFromStringL(aMessage);
		return;
	case EMessageServStop:
		{	
			CActiveScheduler::Stop();
			
			iMsgSvr->iMessageProvider->Message()->RequestForTheMessageOutput(STOP_SERVER_CODE);
			return;
		}
	// requests we don't understand at all are a different thing,
	// so panic the client here, this function also completes the message
	default:
		PanicClient(EBadRequest);
		return;
        }
	}

/**
   Auxiliary function for TestCaseID TPACKAGESTARTER-doTestStepL
  
   This method services Error message received from the client to the message
   server. It reads Error message, filename, line number and error code from
   the message
  
 */
void CMessageServSession::SetErrorFromStringL(const RMessage2 &aMessage)
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
		PanicClient(EBadDescriptor);
	
	iMsgSvr->iMessageProvider->Message()->iError = errorCode;
	iMsgSvr->iMessageProvider->Message()->iLineNumber = lineNumber;
	iMsgSvr->iMessageProvider->Message()->iMsg.Copy(initptr);
	iMsgSvr->iMessageProvider->Message()->iFileName.Copy(initptr1);

	delete writeBuf;
	delete writeBuf1;
	
	iMsgSvr->iMessageProvider->Message()->RequestForTheMessageOutput(errorCode);
	}

/**
   Auxiliary function for TestCaseID TPACKAGESTARTER-doTestStepL
  
   This method demonstrates reading message from the client address space to
   the server. It reads filename, line number and descriptor content from
   the message
  
 */
void CMessageServSession::SetFromStringL(const RMessage2 &aMessage)
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
		PanicClient(EBadDescriptor);
	
	iMsgSvr->iMessageProvider->Message()->iLineNumber = lineNumber;
	iMsgSvr->iMessageProvider->Message()->iMsg.Copy(initptr);
	iMsgSvr->iMessageProvider->Message()->iFileName.Copy(initptr1);

	delete writeBuf;
	delete writeBuf1;
	
	iMsgSvr->iMessageProvider->Message()->RequestForTheMessageOutput();
	}

/**
   Auxiliary function for TestCaseID TPACKAGESTARTER-doTestStepL
  
   This method is used to Panic the client thread
  
 */
void CMessageServSession::PanicClient(TInt aPanic) const
	{
	_LIT(KTxtServer,"CountServ server");
	User::Panic(KTxtServer,aPanic);
	}

