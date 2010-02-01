/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Client interface to CompaKeySrv
*
*/


#include <coemain.h> // CCoeEnv

#include "akncompasrv.h"
#include "akncompasrvclient.h"

// --------------------------------------------------------------------------
// Start the server process
// --------------------------------------------------------------------------
static TInt StartServer()
    {
    // Simultaneous launching of two processes should be detected when
    // the second one attempts to create the server object, failing
    // with KErrAlreadyExists.
    const TUidType serverUid(KNullUid, KNullUid, KAknCompaSrvUid3);
    RProcess server;
    TInt r = server.Create(KAknCompaSrvName, KNullDesC, serverUid);
    if (r != KErrNone)
        {
        return r;        
        }
    TRequestStatus stat;
    server.Rendezvous(stat);
    if (stat!=KRequestPending)
        {
        server.Kill(0); // abort startup
        }
    else
        {
        server.Resume();// logon OK - start the server
        }
    User::WaitForRequest(stat); // wait for start or death
    // we can't use the 'exit reason' if the server panicked as this
    // is the panic 'reason' and may be '0' which cannot be distinguished
    // from KErrNone
    r=(server.ExitType()==EExitPanic) ? KErrGeneral : stat.Int();
    server.Close();
    return r;
    }

// --------------------------------------------------------------------------
// Connect to compa key-server
// --------------------------------------------------------------------------
TInt RAknCompaSrvSession::Connect()
    {
    TInt retry = KServerRetryCount;
    TInt r = KErrNone;
    while(ETrue)
        {
        r = CreateSession(KAknCompaSrvName, Version(),
            KAknCompaSrvMessageSlots);
        if( r != KErrNotFound && r != KErrServerTerminated)
            {
            return r;            
            }
        if(--retry == 0)
            {
            return r;            
            }
        r = StartServer();
        if( r!= KErrNone && r != KErrAlreadyExists)
            {
            return r;            
            }
        }
    }

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
TVersion RAknCompaSrvSession::Version(void) const
    {
    return TVersion(
        KAknCompaSrvMajorVersionNumber,
        KAknCompaSrvMinorVersionNumber,
        KAknCompaSrvBuildVersionNumber);
    }

// --------------------------------------------------------------------------
// Simulate key event to application
// --------------------------------------------------------------------------
void RAknCompaSrvSession::SimulateKeyEventL(TInt aScanCode, TBool aKeyDown)
    {
    TIpcArgs args(aScanCode, aKeyDown);
    User::LeaveIfError(SendReceive(ECompaSrvSimulateKeyEvent, args));
    }

// --------------------------------------------------------------------------
// Disable transition effects
// --------------------------------------------------------------------------
TInt RAknCompaSrvSession::DisaTransEffects()
    {
    return SendReceive(ECompaSrvDisaTransEffects);
    }

// --------------------------------------------------------------------------
// Restore transition effects to a state before DisaTransEffects()
// --------------------------------------------------------------------------
TInt RAknCompaSrvSession::RestoreTransEffects()
    {
    return SendReceive(ECompaSrvRestoreTransEffects);
    }
