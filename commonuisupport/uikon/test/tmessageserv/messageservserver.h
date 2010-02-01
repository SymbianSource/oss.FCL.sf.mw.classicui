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

#ifndef	__MESSAGESERVSERVER_H
#define	__MESSAGESERVSERVER_H

#include <e32base.h>
#include "messageprovider.h"


class CMessageServServer : public CServer2
	{
public:
	enum {EPriority=950}; // mpt - need to explain the magic here!
	
public:
	static void New(MMessageProvider *aMessageProvider);
	~CMessageServServer() {}
	virtual CSession2 *NewSessionL(const TVersion& aVersion,const RMessage2& aMessage) const;
	IMPORT_C static TInt ThreadFunction(TAny* aStarted);
	MMessageProvider*	iMessageProvider;
	
protected:
	CMessageServServer(TInt aPriority);
	
private:
	TInt				iActive;
	};



_LIT(KMessageServerName,"MessageServer");
// reasons for server panic
enum TMessageServPanic
	{
	EBadRequest,
	EBadDescriptor,
	EMainSchedulerError,
	ESvrCreateServer,
	ESvrStartServer,
	ECreateTrapCleanup,
	ENotImplementedYet,
	};
	
// opcodes used in message passing between client and server
enum TMessageServRqst
	{
	EMessageServSetFromString,
	EMessageServSetErrorFromString,
	EMessageServStop
	};


const TUint KMessageServMajorVersionNumber=0;
const TUint KMessageServMinorVersionNumber=1;
const TUint KMessageServBuildVersionNumber=1;


GLDEF_C void PanicServer(TMessageServPanic aPanic);

const TUint KDefaultHeapSize=0x10000;

#endif



