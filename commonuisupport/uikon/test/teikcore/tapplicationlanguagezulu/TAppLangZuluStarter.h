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

#ifndef		__APPLANGZULUSTARTER_H
#define		__APPLANGZULUSTARTER_H


#include "appfwk_test_AppUi.h"

_LIT(KTestApplicationLanguageZuluStep, "TApplicationLanguageZulu");

class CTestApplicationLanguageZuluStep;

//! CMessageActive
/**
Class is used to log message from client.
*/
class CMessageActive4	: public CActive
{
public:
	CMessageActive4() :
	  CActive(EPriorityLow){}

	static CMessageActive4* NewL();  
	void RunL();
	void DoCancel();
	void Init();
	void RequestForTheMessageOutput(TInt aCode = KErrNone);
	TThreadId iID;
	CTestApplicationLanguageZuluStep*	iStep;
	
	TInt	iLineNumber;
	TInt	iError;
	TBuf<512>	iMsg;
	TBuf8<256>	iFileName;

};

//! A CTestPackageStep test step class
/**
Class tests embedding feature of the application.
*/
class CTestApplicationLanguageZuluStep : public CTmsTestStep
	{
public:
	CTestApplicationLanguageZuluStep();
	~CTestApplicationLanguageZuluStep();
	//virtual TVerdict doTestStepPreambleL();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CEikonEnv* aCoe);

	RSemaphore semaphore;
	TInt StartThread();
	CMessageActive4	*iMessage;
private:
	};
	


class CTestPackageStep;


//CMessageServServer

class CMessageServServer4 : public CServer2
	{
public:
	enum {EPriority=950}; // mpt - need to explain the magic here!
public:
	static void New(CTestApplicationLanguageZuluStep *aStep);
	~CMessageServServer4() {}
	virtual CSession2 *NewSessionL(const TVersion& aVersion,const RMessage2& aMessage) const;
static TInt ThreadFunction(TAny* aStarted);
	CTestApplicationLanguageZuluStep*	iStep;
protected:
	CMessageServServer4(TInt aPriority);
private:
	TInt				iActive;
	};


/** CMessageServSession
	This class represents a session in the server.
	CSession::Client() returns the client thread.
	Functions are provided to respond appropriately to client messages.
*/
class CMessageServSession4 : public CSession2
	{
public:
	// construct/destruct
	CMessageServSession4(CMessageServServer4 * aServer);
	static CMessageServSession4* NewL(CMessageServServer4 * aServer);
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
	CMessageServServer4 *iMsgSvr;
	};



_LIT(KMessageServerName4,"MessageServer4");


// reasons for server panic
enum TMessageServPanic4
	{
	EBadRequest4,
	EBadDescriptor4,
	EMainSchedulerError4,
	ESvrCreateServer4,
	ESvrStartServer4,
	ECreateTrapCleanup4,
	ENotImplementedYet4,
	};
// opcodes used in message passing between client and server
enum TMessageServRqst4
	{
	EMessageServSetFromString4,
	EMessageServSetErrorFromString4,
	EMessageServStop4
	};


const TUint KMessageServMajorVersionNumber4=0;
const TUint KMessageServMinorVersionNumber4=1;
const TUint KMessageServBuildVersionNumber4=1;


GLDEF_C void PanicServer4(TMessageServPanic4 aPanic);

const TUint KDefaultHeapSize4=0x10000;

#endif


