// Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef __EIKSHTSV_H__
#define __EIKSHTSV_H__

#include <e32base.h>
#include <w32std.h>
#include <savenotf.h>
#include <shutdownsrv.h>
#include <uiklaf/private/lafshut.h> // okay to include this in a private header
#include <shutdownsess.h>

class CLafShutdownManagerBase;

NONSHARABLE_CLASS(CEikServShutdownServer) : public CServShutdownServer
	{
public:
	IMPORT_C static CEikServShutdownServer* NewL();
public:
	~CEikServShutdownServer();
public: // from CServShutdownServer
	void ConstructL();
private:
	CEikServShutdownServer(TInt aPriority);
private: // from CServer2
	CSession2* NewSessionL(const TVersion& aVersion,const RMessage2& aMessage) const;
private:
	CLafShutdownManagerBase* iLafShutdown;
	};

NONSHARABLE_CLASS(CEikServShutdownSession) : public CServShutdownSession
	{
public:
	static CEikServShutdownSession* NewL();
private:
	inline CEikServShutdownSession() :CServShutdownSession() {}
	};

#endif	// __EIKSHTSV_H__
