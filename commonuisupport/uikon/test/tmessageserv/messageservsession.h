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

#ifndef	__MESSAGESERVSESSION_H
#define	__MESSAGESERVSESSION_H

#include <e32base.h>
#include "messageservserver.h"


/** CMessageServSession
	This class represents a session in the server.
	CSession::Client() returns the client thread.
	Functions are provided to respond appropriately to client messages. */

class CMessageServSession : public CSession2
	{
public:
	// construct/destruct
	CMessageServSession(CMessageServServer * aServer);
	static CMessageServSession* NewL(CMessageServServer * aServer);
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
	CMessageServServer *iMsgSvr;
	};


#endif



