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
* Description:  
*
*/


#include <e32svr.h>
#include <e32uid.h>
#include <coemain.h> // CCoeEnv
#include <apgtask.h>  // TApaTaskList and friends
#include <centralrepository.h>
#include <AvkonInternalCRKeys.h>
#include <pslninternalcrkeys.h>
#include <AknCapServerDefs.h>
#include <AknNotifierWrapperDefs.h>

#include "akncompasrv.h"
#include "akncompaserver.h"

// Flags for KAknCompaModeEffects
const TInt KAknCompaModeEffectsSaved = (1 << 31);
const TInt KAknCompaModeEffectsDisabled = 0x7fffffff;

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
CAknCompaSrvWsEventHandler::CAknCompaSrvWsEventHandler(RWsSession& aWsSession)
    : CActive(CActive::EPriorityStandard), iWsSession(aWsSession)
    {
    CActiveScheduler::Add(this);
    IssueRequest();
    }

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
CAknCompaSrvWsEventHandler::~CAknCompaSrvWsEventHandler()
    {
    Cancel();
    }

// --------------------------------------------------------------------------
// Issue request to read from wsrv event queue
// --------------------------------------------------------------------------
void CAknCompaSrvWsEventHandler::IssueRequest()
    {
    iWsSession.EventReady(&iStatus);
    SetActive();
    }

// --------------------------------------------------------------------------
// Event ready in window server event queue
// --------------------------------------------------------------------------
void CAknCompaSrvWsEventHandler::RunL()
    {
    // Window server event queue read to purge it in case wsrv sends
    // something. As we dont have window group created this is probably
    // unneccesary as there seem to be no events.
    TWsEvent wsEvent;
    iWsSession.GetEvent(wsEvent);
    IssueRequest();
    }

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
void CAknCompaSrvWsEventHandler::DoCancel()
    {
    iWsSession.EventReadyCancel();
    }

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
CAknCompaServer::CAknCompaServer()
    :CServer2(CActive::EPriorityStandard)
    {
    }

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
CAknCompaServer::~CAknCompaServer()
    {
    delete iThemesCenRep;
    delete iAvkonCenRep;

    delete iWsEventHandler;
    iWsSession.Close();
    }

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
CServer2* CAknCompaServer::NewLC()
    {
    CAknCompaServer* self = new (ELeave) CAknCompaServer;
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
void CAknCompaServer::ConstructL()
    {
    User::LeaveIfError(iWsSession.Connect());
    iThemesCenRep = CRepository::NewL(KCRUidThemes);
    iAvkonCenRep = CRepository::NewL(KCRUidAvkon);

    // Check if compa-mode has disabled effects in repository
    TInt savedEffects = KAknCompaModeEffectsDisabled;
    iAvkonCenRep->Get(KAknCompaModeEffects, savedEffects);
    iEffectsDisabled = (savedEffects & KAknCompaModeEffectsSaved) != 0;

    iWsEventHandler = new (ELeave) CAknCompaSrvWsEventHandler(iWsSession);
    StartL(KAknCompaSrvName);
    }

// --------------------------------------------------------------------------
// New session added to server
// --------------------------------------------------------------------------
void CAknCompaServer::AddSession()
    {
    iSessionCount++;
    }


// --------------------------------------------------------------------------
// Session is closing
// --------------------------------------------------------------------------
void CAknCompaServer::DropSession()
    {
    if (--iSessionCount == 0)
        {
        // Stops the active scheduler. As this server runs in its 
        // own process this stop effectively kills the process
        CActiveScheduler::Stop();
        }
    }

// --------------------------------------------------------------------------
// Get window server session
// --------------------------------------------------------------------------
RWsSession& CAknCompaServer::WsSession()
    {
    return iWsSession;
    }

// --------------------------------------------------------------------------
// Create a new session
// --------------------------------------------------------------------------
CSession2* CAknCompaServer::NewSessionL(const TVersion& aVersion,
    const RMessage2& /*aMessage*/) const
    {
    // Check that the version is OK
    TVersion v(KAknCompaSrvMajorVersionNumber,
        KAknCompaSrvMinorVersionNumber, KAknCompaSrvBuildVersionNumber);
    if (!User::QueryVersionSupported(v,aVersion))
        {
        User::Leave(KErrNotSupported);          
        }

    return new (ELeave) CAknCompaSrvSession;
    }

// --------------------------------------------------------------------------
// Panic server
// --------------------------------------------------------------------------
void CAknCompaServer::PanicServer(TAknCompaServerPanic aPanic)
    {
    User::Panic(KAknCompaSrvName, aPanic);
    }

// --------------------------------------------------------------------------
// Panic client
// --------------------------------------------------------------------------
void CAknCompaServer::PanicClient(const RMessage2& aMessage, 
    TInt aPanic)
    {
    aMessage.Panic(KAknCompaSrvName, aPanic);
    }

// --------------------------------------------------------------------------
// Check if process is a server that displays global
// notes/notifications (Eikon server, Avkon notify and cap servers)
// --------------------------------------------------------------------------
TBool CAknCompaServer::IsGlobalUiSrv(const RMessage2& aMessage)
    {
    const TUint32 KEikSrvUid = 0x10003a4a;
    return aMessage.SecureId().iId == KAknCapServerUid.iUid ||
        aMessage.SecureId().iId == KCommonNotifierAppSrvUid.iUid ||
        aMessage.SecureId().iId == KEikSrvUid;
    }

// --------------------------------------------------------------------------
// Set thread priority to normal
// --------------------------------------------------------------------------
void CAknCompaServer::SetThreadPriorityNormal(TAny* /*aUnused*/)
    {
    RThread thread;
    thread.SetPriority(EPriorityNormal);
    }

// --------------------------------------------------------------------------
// Set thread priority higher than any non-signed application threads
// --------------------------------------------------------------------------
void CAknCompaServer::SetThreadPriorityHigh()
    {
    RThread thread;
    thread.SetPriority(EPriorityAbsoluteRealTime1);
    }

// --------------------------------------------------------------------------
// Disable transition effects
// --------------------------------------------------------------------------
void CAknCompaServer::DisaTransEffectsL(const RMessage2& aMessage)
    {
    if (!iEffectsDisabled)
        {
        // Allow effects control only from global ui servers
        if (!IsGlobalUiSrv(aMessage))
            {
            User::Leave(KErrPermissionDenied);
            }
        iEffectsDisabled = ETrue;
        // The only way to disable transition effects is through CenRep. The
        // same variable is also controlled by "Control Panel". If the device
        // is turned off while we have disabled effects, we need to enable
        // them when device is restarted.
        TInt savedEffects = KAknCompaModeEffectsDisabled;
        iAvkonCenRep->Get(KAknCompaModeEffects, savedEffects);

        if ((savedEffects & KAknCompaModeEffectsSaved) == 0)
            {
            TInt effects = 0;
            iThemesCenRep->Get(KThemesTransitionEffects, effects);
            if (effects != KAknCompaModeEffectsDisabled)
                {
                iAvkonCenRep->Set(KAknCompaModeEffects,
                    effects | KAknCompaModeEffectsSaved);
                iThemesCenRep->Set(KThemesTransitionEffects,
                    KAknCompaModeEffectsDisabled);
                }
            }
        }
    }

// --------------------------------------------------------------------------
// Restore transition effects to a state before they were disabled
// --------------------------------------------------------------------------
void CAknCompaServer::RestoreTransEffectsL(const RMessage2& aMessage)
    {
    if (iEffectsDisabled)
        {
        // Allow effects control only from global ui servers
        if (!IsGlobalUiSrv(aMessage))
            {
            User::Leave(KErrPermissionDenied);
            }
        iEffectsDisabled = EFalse;

        // Read saved effects state from our CenRep
        TInt savedEffects = 0;
        iAvkonCenRep->Get(KAknCompaModeEffects, savedEffects);

        if (savedEffects & KAknCompaModeEffectsSaved)
            {
            savedEffects &= ~KAknCompaModeEffectsSaved;
            iThemesCenRep->Set(KThemesTransitionEffects, savedEffects);
            iAvkonCenRep->Set(KAknCompaModeEffects, savedEffects);
            }
        }
    }

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
CAknCompaServer& CAknCompaSrvSession::Server()
    {
    return *static_cast<CAknCompaServer*>
        (const_cast<CServer2*>(CSession2::Server()));
    }

// --------------------------------------------------------------------------
// Create session
// --------------------------------------------------------------------------
void CAknCompaSrvSession::CreateL()
    {
    // Allocate memory for keystate array to hold all possible keys.
    // This avoid possibility of memory allocation error when key is
    // added to key state array due to key press while application is
    // executing.
    iKeyState.Reserve(EKeyStateGranularity);
    
    Server().AddSession();
    }

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
CAknCompaSrvSession::CAknCompaSrvSession():
    iKeyState(EKeyStateGranularity)
    {
    // We allow only rocker keys, softkeys and numeric keypad keys to be
    // simulated.
    static const TUint8 ValidScanCodes[] =
        {
        EStdKeyDevice0, EStdKeyUpArrow, EStdKeyDevice1, EStdKeyLeftArrow,
        EStdKeyDevice3, EStdKeyRightArrow, EStdKeyRightShift,
        EStdKeyDownArrow, EStdKeyBackspace, EStdKeyNkpAsterisk, EStdKeyHash,
        0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39
        };
    iValidScanCodes.Set(ValidScanCodes, sizeof(ValidScanCodes));
    }

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
CAknCompaSrvSession::~CAknCompaSrvSession()
    {
    TInt num = iKeyState.Count();

    // When session closes, send key up events for all keys being in down
    // state. This ensures even if application crashes that no keys are left
    // down.
    for( TInt i=0; i < num; i++)
        {
        SimulateKeyEvent(iKeyState[i], EFalse);
        }
    Server().DropSession();
    iKeyState.Close();
    }


// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
void CAknCompaSrvSession::ServiceL(const RMessage2& aMessage)
    {
    TRAPD(err, DispatchMessageL(aMessage));
    aMessage.Complete(err);
    }

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
void CAknCompaSrvSession::DispatchMessageL(const RMessage2& aMessage)
    {
    switch(aMessage.Function())
        {
    case ECompaSrvSimulateKeyEvent:
        SimulateKeyEventServiceL(aMessage);
        break;
    case ECompaSrvDisaTransEffects:
        Server().DisaTransEffectsL(aMessage);
        break;
    case ECompaSrvRestoreTransEffects:
        Server().RestoreTransEffectsL(aMessage);
        break;
    // Requests that we don't understand at all are a different matter.
    // This is considered a client programming error, so we panic the 
    // client - this also completes the message.
    default:
        CAknCompaServer::PanicClient(aMessage, EBadRequest);
        }
    }

// --------------------------------------------------------------------------
// Simulate key event for client application
// --------------------------------------------------------------------------
void CAknCompaSrvSession::SimulateKeyEventServiceL(const RMessage2& aMessage)
    {
    TInt scancode = aMessage.Int0();
    TBool keyDown = aMessage.Int1();

    // Check that scan code is valid. Client request will fail with error
    // code KErrNotFound if the check fails.
    TChar ch(scancode);
    User::LeaveIfError(iValidScanCodes.Locate(ch));

    if (keyDown)
        {
        // Set thread priority to very high. The purpose is to prevent
        // other threads to change foreground application in between
        // client foreground status check and SimulateRawEvent().
        CAknCompaServer::SetThreadPriorityHigh();
        CleanupStack::PushL(
            TCleanupItem(CAknCompaServer::SetThreadPriorityNormal, NULL));
        // Check that client task is foreground
        CheckKeyDownPermissionL(aMessage);
        }

    // Keeps tracks which scancodes are in down state
    if (keyDown)
        {
        // There can be only one of each scancode in the list
        if (iKeyState.Find(scancode) == KErrNotFound)
            {
            iKeyState.AppendL(scancode);
            SimulateKeyEvent(scancode, keyDown);
            }
        CleanupStack::PopAndDestroy();
        }
    else
        {
        TInt pos = iKeyState.Find(scancode);
        if (pos != KErrNotFound)
            {
            iKeyState.Remove(pos);
            iKeyState.GranularCompress();
            SimulateKeyEvent(scancode, keyDown);
            }
        }
    }

// --------------------------------------------------------------------------
// Simulate key event to window server
// --------------------------------------------------------------------------
void CAknCompaSrvSession::SimulateKeyEvent(TInt aScancode, TBool aKeyDown)
    {
    TRawEvent event;
    event.Set(
        aKeyDown ? TRawEvent::EKeyDown : TRawEvent::EKeyUp,
        aScancode);

    RWsSession& wsSession = Server().WsSession();
    // Simulate key event as it came from a keypad
    wsSession.SimulateRawEvent(event);
    wsSession.Flush();
    }

// --------------------------------------------------------------------------
// Check whether client key event request can be executed
// --------------------------------------------------------------------------
void CAknCompaSrvSession::CheckKeyDownPermissionL(const RMessage2& aMessage)
    {
    // We try to increase security by allowing only foreground application
    // to set key down. As the simulated key events are sent to the
    // foreground application by window server, the application is
    // sending a key event to itself.

    // Granted if client has ECapabilitySwEvent or request is coming from
    // EikSrv. TApaTaskList won't report EikSrv in foreground though
    // it's displaying a note.
    if (!aMessage.HasCapability(ECapabilitySwEvent) &&
        !CAknCompaServer::IsGlobalUiSrv(aMessage))
        {
        // Allow key down only from a foreground task
        TApaTaskList tasklist(Server().WsSession());
        TApaTask foregroundTask = tasklist.FindByPos(0);

        RThread thread;
        User::LeaveIfError(thread.Open(foregroundTask.ThreadId()));
        TSecurityPolicy securityPolicy(thread.SecureId());
        thread.Close();

        if (!securityPolicy.CheckPolicy(aMessage))
            {
            User::Leave(KErrPermissionDenied);
            }
        }
    }
