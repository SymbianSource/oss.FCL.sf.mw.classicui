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

#ifndef		__APPLANGFRENCHSTARTER_H
#define		__APPLANGFRENCHSTARTER_H


#include "appfwk_test_AppUi.h"

_LIT(KTestApplicationLanguageFrenchStep, "TApplicationLanguageFrench");

class CTestApplicationLanguageFrenchStep;

//! CMessageActive
/**
Class is used to log message from client.
*/
class CMessageActive3	: public CActive
{
public:
	CMessageActive3() :
	  CActive(EPriorityLow){}

	static CMessageActive3* NewL();  
	void RunL();
	void DoCancel();
	void Init();
	void RequestForTheMessageOutput(TInt aCode = KErrNone);
	TThreadId iID;
	CTestApplicationLanguageFrenchStep*	iStep;
	
	TInt	iLineNumber;
	TInt	iError;
	TBuf<512>	iMsg;
	TBuf8<256>	iFileName;

};

//! A CTestPackageStep test step class
/**
Class tests embedding feature of the application.
*/
class CTestApplicationLanguageFrenchStep : public CTmsTestStep
	{
public:
	CTestApplicationLanguageFrenchStep();
	~CTestApplicationLanguageFrenchStep();
	//virtual TVerdict doTestStepPreambleL();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CEikonEnv* aCoe);

	RSemaphore semaphore;
	TInt StartThread();
	CMessageActive3	*iMessage;
private:
	};
	


class CTestPackageStep;



//CMessageServServer

class CMessageServServer3 : public CServer2
	{
public:
	enum {EPriority=950}; // mpt - need to explain the magic here!
public:
	static void New(CTestApplicationLanguageFrenchStep *aStep);
	~CMessageServServer3() {}
	virtual CSession2 *NewSessionL(const TVersion& aVersion,const RMessage2& aMessage) const;
static TInt ThreadFunction(TAny* aStarted);
	CTestApplicationLanguageFrenchStep*	iStep;
protected:
	CMessageServServer3(TInt aPriority);
private:
	TInt				iActive;
	};


/** CMessageServSession
	This class represents a session in the server.
	CSession::Client() returns the client thread.
	Functions are provided to respond appropriately to client messages.
*/
class CMessageServSession3 : public CSession2
	{
public:
	// construct/destruct
	CMessageServSession3(CMessageServServer3 * aServer);
	static CMessageServSession3* NewL(CMessageServServer3 * aServer);
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
	CMessageServServer3 *iMsgSvr;
	};



_LIT(KMessageServerName3,"MessageServer3");


// reasons for server panic
enum TMessageServPanic3
	{
	EBadRequest3,
	EBadDescriptor3,
	EMainSchedulerError3,
	ESvrCreateServer3,
	ESvrStartServer3,
	ECreateTrapCleanup3,
	ENotImplementedYet3,
	};
// opcodes used in message passing between client and server
enum TMessageServRqst3
	{
	EMessageServSetFromString3,
	EMessageServSetErrorFromString3,
	EMessageServStop3
	};


const TUint KMessageServMajorVersionNumber3=0;
const TUint KMessageServMinorVersionNumber3=1;
const TUint KMessageServBuildVersionNumber3=1;


GLDEF_C void PanicServer3(TMessageServPanic3 aPanic);

const TUint KDefaultHeapSize3=0x10000;

#endif


