/*
* Copyright (c) 2004 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:  Server applications framework.
 *
 *
*/


#include "AknServerApp.h"

#include <avkon.hrh>
#include <aknenv.h>
#include "AknOpenFileServiceImpl.h"
#include "AknNullServiceImpl.h"
#include "AknLaunchAppServiceImpl.h"
#include "AknDebug.h"


// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
EXPORT_C void RAknAppServiceBase::ConnectChainedAppL(TUid aAppUid)
    {
#ifdef AVKON_RDEBUG_INFO
    RDebug::Print(_L("RAknAppServiceBase::ConnectChainedAppL"));
#endif
	CEikonEnv* eikEnv = CEikonEnv::Static();
	RWindowGroup& wg = eikEnv->RootWin();
    ConnectNewChildAppL(aAppUid, wg);
    }

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
EXPORT_C void RAknAppServiceBase::Close()
    {
#ifdef AVKON_RDEBUG_INFO
    RDebug::Print(_L("RAknAppServiceBase::Close"));
#endif
    REikAppServiceBase::Close();
    }




// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
EXPORT_C void MAknServerAppExitObserver::HandleServerAppExit(TInt aReason)
    {
#ifdef AVKON_RDEBUG_INFO
    RDebug::Print(_L("MAknServerAppExitObserver::HandleServerAppExit"));
#endif
    if (aReason == EAknCmdExit)
        {
        // ShutOrHideAppL is very unlikely to leave, app is supposed to be
        // exiting, so ignore errors anyway.
        TRAP_IGNORE(CAknEnv::ShutOrHideAppL());
        }
    }



// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
EXPORT_C CAknAppServiceBase::CAknAppServiceBase()
    {
    }

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
EXPORT_C CAknAppServiceBase::~CAknAppServiceBase()
    {
    if ( Server() )
        {
        static_cast<CAknAppServer*>(const_cast<CServer2*>(Server()))->HandleSessionClose();
        }
    }

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
EXPORT_C void CAknAppServiceBase::CreateL()
    {
#ifdef AVKON_RDEBUG_INFO
    RDebug::Print(_L("CAknAppServiceBase::CreateL"));
#endif
    static_cast<CAknAppServer*>(const_cast<CServer2*>(Server()))->HandleSessionOpen();
    CApaAppServiceBase::CreateL();
    }

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
EXPORT_C void CAknAppServiceBase::ServiceL(const RMessage2& aMessage)
    {
#ifdef AVKON_RDEBUG_INFO
    RDebug::Print(_L("CAknAppServiceBase::ServiceL"));
#endif
    CApaAppServiceBase::ServiceL(aMessage);
    }

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
EXPORT_C void CAknAppServiceBase::ServiceError(const RMessage2& aMessage,TInt aError)
    {
#ifdef AVKON_RDEBUG_INFO
    RDebug::Print(_L("CAknAppServiceBase::ServiceError"));
#endif
    CApaAppServiceBase::ServiceError(aMessage, aError);
    }


// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
EXPORT_C CAknAppServer::~CAknAppServer()
	{
	// CApaAppServiceBase destructors call back to this class,
	// so ensure that they are deleted before this class is
	// deleted, and ensure that a derived HandleAllClientsClosed()
	// is not called by artificially raising the session count.
	++iSessionCount;
	iSessionIter.SetToFirst();
	CSession2* s;
	while ((s=iSessionIter++)!=NULL)
		{
		delete s;
		}
	}

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
EXPORT_C void CAknAppServer::ConstructL(const TDesC& aFixedServerName)
    {
#ifdef AVKON_RDEBUG_INFO
    RDebug::Print(_L("CAknAppServer::ConstructL"));
#endif
    CEikAppServer::ConstructL(aFixedServerName);
    }

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
EXPORT_C CApaAppServiceBase* CAknAppServer::CreateServiceL(TUid aServiceType) const
    {
#ifdef AVKON_RDEBUG_INFO
    RDebug::Print(_L("CAknAppServer::CreateServiceL"));
#endif
    // two built-in services: Open File and Null service.
    if (aServiceType == KAknOpenFileServiceUid)
    {
        return new(ELeave) CAknOpenFileServiceSession;
    }
    else if (aServiceType == KAknNullServiceUid)
    {
        return new(ELeave) CAknAppServiceBase;
    }
    else if (aServiceType == KAknLaunchAppServiceUid)
    {
        return new(ELeave) CAknLaunchAppServiceSession;
    }
    return CEikAppServer::CreateServiceL(aServiceType);
    }

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
EXPORT_C void CAknAppServer::HandleAllClientsClosed()
    {
#ifdef AVKON_RDEBUG_INFO
    RDebug::Print(_L("CAknAppServer::HandleAllClientsClosed"));
#endif
    CAknEnv::Static()->RunAppShutter();
    }

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
void CAknAppServer::HandleSessionClose()
    {
#ifdef AVKON_RDEBUG_INFO
    RDebug::Print(_L("CAknAppServer::HandleSessionClose"));
#endif
    if (--iSessionCount<=0)
        {
        //CAknEnv::Static()->RunAppShutter();
        HandleAllClientsClosed();
        }
    }

// ---------------------------------------------------------
//
// ---------------------------------------------------------
//
void CAknAppServer::HandleSessionOpen()
    {
#ifdef AVKON_RDEBUG_INFO
    RDebug::Print(_L("CAknAppServer::HandleSessionOpen"));
#endif
    iSessionCount++;
    }

// End of file.
