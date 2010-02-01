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

#include "eikshtsv.h"
#include <coemain.h>
#include <savenotf.h>
#include <savepriv.h>
#include <hal.h>

//
// class CEikServShutdownServer
//

/**
Static factory function to create new CEikServShutdownServer
@return Instantiated and constructed server with priority EActivePriorityIpcEventsHigh
@publishedAll
@released
*/
EXPORT_C CEikServShutdownServer* CEikServShutdownServer::NewL()
	{ // static
	CEikServShutdownServer* self=new(ELeave) CEikServShutdownServer(EActivePriorityIpcEventsHigh);
	return self;
	}

/**
Destructor
*/
CEikServShutdownServer::~CEikServShutdownServer()
	{
	delete iLafShutdown;
	}

/**
Private constructor
@internalComponent
*/
CEikServShutdownServer::CEikServShutdownServer(TInt aPriority)
	: CServShutdownServer(aPriority)
	{}

/**
Second phase construction
Framework function.  Calls base class.
@see CServShutdownServer::ConstructL()
*/
void CEikServShutdownServer::ConstructL()
	{
	CServShutdownServer::ConstructL();
	iLafShutdown=LafShutdown::CreateShutdownManager(*this);
	}

/**
Framwork function
@return A newly instantiated CEikServShutdownSession
@see CServer2::NewSessionL(const TVersion& aVersion, const RMessage2&) 
*/
CSession2* CEikServShutdownServer::NewSessionL(const TVersion& aVersion, const RMessage2&) const
	{
	TVersion version(KShutdownMajorVN,KShutdownMinorVN,KShutdownBuildVN);
	if (!User::QueryVersionSupported(version,aVersion))
		{
		User::Leave(KErrNotSupported);
		}
	return CEikServShutdownSession::NewL();
	}


//
// class CEikServShutdownSession
//

/**
Static factory function.
@internalTechnology
*/
CEikServShutdownSession* CEikServShutdownSession::NewL()
	{
	return new (ELeave) CEikServShutdownSession;
	}

//
// Main
//

