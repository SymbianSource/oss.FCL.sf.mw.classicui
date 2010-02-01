/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:
*
*/
// AKNEIKSRVC.CPP
//

#include <e32std.h>
#include <e32math.h>
#include <eiksrvc.h>
#include <eiksvdef.h>
#include <s32mem.h>
#include "akneiksrvc.h"
#include <akneiksrvs.h>

GLDEF_C void PanicServer(TEikAppUiServPanic aPanic)
	{
	_LIT(KPanicCat,"EIKON-SERVER");
	User::Panic(KPanicCat,aPanic);
	}




EXPORT_C RAknEikAppUiSession::RAknEikAppUiSession()
	{
	}

EXPORT_C TInt RAknEikAppUiSession::ShutdownApps(const TUid aRequesterUID, const TInt aTimeoutInMicroseconds) const
	{
    TIpcArgs args( aRequesterUID.iUid, aTimeoutInMicroseconds );
	return SendReceive(EAknEikAppUiShutdownApps, args);
	}

EXPORT_C TInt RAknEikAppUiSession::SetSgcParams(TInt /*aWgId*/, TBitFlags /*aAppFlags*/, TInt /*aSpLayout*/, TInt /*aSpFlags*/)
	{
    return KErrNotSupported;
	}

EXPORT_C TInt RAknEikAppUiSession::BlockServerStatusPaneRedraws()
	{
    return KErrNone;
	}

EXPORT_C TInt RAknEikAppUiSession::RedrawServerStatusPane()
	{
    return KErrNotSupported;
	}

EXPORT_C TInt RAknEikAppUiSession::PrepareForAppExit(TInt /*aWgId*/)
	{
    return KErrNotSupported;
	}

EXPORT_C TInt RAknEikAppUiSession::SetSystemFaded(TBool /*aFade*/)
	{
    return KErrNotSupported;
	}

EXPORT_C TInt RAknEikAppUiSession::IsSystemFaded(TBool& /*aFade*/) const
	{
    return KErrNotSupported;
	}

TInt RAknEikAppUiSession::DoNotifierControllerCommand(TInt aCommand)
	{
    TPckgC<TInt> arg(aCommand);
    SendReceive(EEikAppUiExtension, TIpcArgs(EAknNotifierControllerCmd, &arg));
	return 0;
	}

EXPORT_C TInt RAknEikAppUiSession::AllowNotifierAppServersToLoad()
	{
	return SendReceive(EEikAppUiExtension, TIpcArgs(EAknCapServerStartupComplete, &KNullDesC8));	
	}

EXPORT_C TInt  RAknEikAppUiSession::DoSynchWaitForAknCapServer()
	{
	TInt err(KErrNone);
	TBool connectedLocally(EFalse);
	if (Handle() == 0)
		{
		err = Connect();
		connectedLocally = ETrue;
		}
	
	__ASSERT_ALWAYS(err == KErrNone, User::Invariant());
	
	TRequestStatus status;
    SendReceive(EEikAppUiExtension,TIpcArgs(EAknSignalAknCapServerReady, &KNullDesC8), status);
	User::WaitForRequest(status);
	if (connectedLocally)
		{
		Close();
		}
	
	return status.Int();
	}
