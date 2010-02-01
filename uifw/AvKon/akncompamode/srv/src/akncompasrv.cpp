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
* Description:   Main process execution
*
*/


#include <e32base.h>
#include <e32std.h>

#include "akncompasrv.h"
#include "akncompaserver.h"

// --------------------------------------------------------------------------
// Run compa key-server
// --------------------------------------------------------------------------
static void RunServerL()
    {
    // Perform all server initialisation, in particular creation of the
    // scheduler and server and then run the scheduler

    // Naming the server thread after the server helps to debug panics
    User::LeaveIfError(RThread::RenameMe(KAknCompaSrvName));

    // Create and install the active scheduler
    CActiveScheduler* s = new(ELeave) CActiveScheduler;
    CleanupStack::PushL(s);
    CActiveScheduler::Install(s);

    // Create the server (leave it on the cleanup stack)
    CAknCompaServer::NewLC();

    // Initialisation complete, now signal the client
    RProcess::Rendezvous(KErrNone);

    // Set to high priority
    RThread thread;
    thread.SetProcessPriority(EPriorityHigh);

    // Ready to run
    CActiveScheduler::Start();

    // Cleanup the server and scheduler
    CleanupStack::PopAndDestroy(2);
    }

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
GLDEF_C TInt E32Main()
    {
    __UHEAP_MARK;

    CTrapCleanup* cleanup=CTrapCleanup::New();
    TInt r=KErrNoMemory;
    if (cleanup)
      {
      TRAP(r,RunServerL());
      delete cleanup;
      }

    __UHEAP_MARKEND;
    return r;
    }
