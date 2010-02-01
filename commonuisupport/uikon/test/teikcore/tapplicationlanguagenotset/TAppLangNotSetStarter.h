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
// Tests embedding feature of the application.
// 
//

/**
 @file 
 @internalComponent - Internal Symbian test code
*/

#ifndef		__APPLANGNotSetSTARTER_H
#define		__APPLANGNotSetSTARTER_H


#include "appfwk_test_AppUi.h"

_LIT(KTestApplicationLanguageNotSetStep, "TApplicationLanguageNotSet");

class CTestApplicationLanguageNotSetStep;

//! CMessageActive
/**
Class is used to log message from client.
*/
class CMessageActive5	: public CActive
{
public:
	CMessageActive5() :
	  CActive(EPriorityLow){}

	static CMessageActive5* NewL();  
	void RunL();
	void DoCancel();
	void Init();
	void RequestForTheMessageOutput(TInt aCode = KErrNone);
	TThreadId iID;
	CTestApplicationLanguageNotSetStep*	iStep;
	
	TInt	iLineNumber;
	TInt	iError;
	TBuf<512>	iMsg;
	TBuf8<256>	iFileName;

};

//! A CTestPackageStep test step class
/**
Class tests embedding feature of the application.
*/
class CTestApplicationLanguageNotSetStep : public CTmsTestStep
	{
public:
	CTestApplicationLanguageNotSetStep();
	~CTestApplicationLanguageNotSetStep();
	//virtual TVerdict doTestStepPreambleL();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CEikonEnv* aCoe);

	RSemaphore semaphore;
	TInt StartThread();
	CMessageActive5	*iMessage;
private:
	};
	


class CTestPackageStep;



//CMessageServServer

class CMessageServServer5 : public CServer2
	{
public:
	enum {EPriority=950}; // mpt - need to explain the magic here!
public:
	static void New(CTestApplicationLanguageNotSetStep *aStep);
	~CMessageServServer5() {}
	virtual CSession2 *NewSessionL(const TVersion& aVersion,const RMessage2& aMessage) const;
static TInt ThreadFunction(TAny* aStarted);
	CTestApplicationLanguageNotSetStep*	iStep;
protected:
	CMessageServServer5(TInt aPriority);
private:
	TInt				iActive;
	};


/** CMessageServSession
    This class represents a session in the server.
    CSession::Client() returns the client thread.
    Functions are provided to respond appropriately to client messages. */

class CMessageServSession5 : public CSession2
	{
public:
	// construct/destruct
	CMessageServSession5(CMessageServServer5 * aServer);
	static CMessageServSession5* NewL(CMessageServServer5 * aServer);
	//service request
	virtual void ServiceL(const RMessage2 &aMessage);
	void DispatchMessageL(const RMessage2 &aMessage);

	//services available to initialize/increase/decrease/reset and return the counter value.
	void SetFromStringL(const RMessage2 &aMessage);
// The function read Error message, filename, line number and error code from
// the message
	void SetErrorFromStringL(const RMessage2 &aMessage);
protected:
	// panic the client
	void PanicClient(TInt aPanic) const;
	// safewrite between client and server
	//void Write(const TAny* aPtr,const TDesC8& aDes,TInt anOffset=0);
private:
	CMessageServServer5 *iMsgSvr;
	};



_LIT(KMessageServerName5,"MessageServer5");


// reasons for server panic
enum TMessageServPanic5
	{
	EBadRequest5,
	EBadDescriptor5,
	EMainSchedulerError5,
	ESvrCreateServer5,
	ESvrStartServer5,
	ECreateTrapCleanup5,
	ENotImplementedYet5,
	};
// opcodes used in message passing between client and server
enum TMessageServRqst5
	{
	EMessageServSetFromString5,
	EMessageServSetErrorFromString5,
	EMessageServStop5
	};


const TUint KMessageServMajorVersionNumber5=0;
const TUint KMessageServMinorVersionNumber5=1;
const TUint KMessageServBuildVersionNumber5=1;


GLDEF_C void PanicServer5(TMessageServPanic5 aPanic);

const TUint KDefaultHeapSize5=0x10000;

#endif


