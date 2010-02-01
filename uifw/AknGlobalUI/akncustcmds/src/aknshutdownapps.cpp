/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description : Implementation of CAknShutdownApps class.
*
*/

#include "aknshutdownapps.h"

// 7 seconds time for applications to close themself
const TInt KTimeToKillAppsNicely = 7000000;

// UID of this DLL for the shutdown operation
const TUid KAknStartupExtPluginUID = { 0x1020506D };

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CAknShutdownApps::NewL
//
// ---------------------------------------------------------------------------
//
CAknShutdownApps* CAknShutdownApps::NewL()
	{
	CAknShutdownApps* self = new ( ELeave ) CAknShutdownApps;
	return self;
	}


// ---------------------------------------------------------------------------
// Destructor
//
// ---------------------------------------------------------------------------
//
CAknShutdownApps::~CAknShutdownApps()
    {
    }


// ---------------------------------------------------------------------------
// CAknShutdownApps::Initialize
//
// ---------------------------------------------------------------------------
//
TInt CAknShutdownApps::Initialize( CSsmCustomCommandEnv* /*aCmdEnv*/ )
    {
    return KErrNone;
    }


// ---------------------------------------------------------------------------
// CAknShutdownApps::Execute
//
// ---------------------------------------------------------------------------
//
void CAknShutdownApps::Execute(
    const TDesC8& /*aParams*/,
    TRequestStatus& aRequest )
    {
    aRequest = KRequestPending;

    TInt errorCode = iAknUiServer.Connect();
    if ( errorCode == KErrNone )
        {
        iAknUiServer.ShutdownApps(
            KAknStartupExtPluginUID, KTimeToKillAppsNicely, aRequest );

        iActive = ETrue;
        }
    else
        {
        TRequestStatus* request = &aRequest;
        User::RequestComplete( request, errorCode );
        }
    }


// ---------------------------------------------------------------------------
// CAknShutdownApps::ExecuteCancel
//
// ---------------------------------------------------------------------------
//
void CAknShutdownApps::ExecuteCancel()
    {
    // Nothing to do.
    if ( iActive )
        {
        iAknUiServer.CancelShutdownApps();
        iActive = EFalse;
        }
    }


// ---------------------------------------------------------------------------
// CAknShutdownApps::Release
//
// ---------------------------------------------------------------------------
//
void CAknShutdownApps::Release()
    {
	delete this;
    }


// ---------------------------------------------------------------------------
// CAknShutdownApps::Close
//
// ---------------------------------------------------------------------------
//
void CAknShutdownApps::Close()
    {
    // Nothing to do.
    }


// ---------------------------------------------------------------------------
// First phase constructor
//
// ---------------------------------------------------------------------------
//
CAknShutdownApps::CAknShutdownApps()
    {
    }

