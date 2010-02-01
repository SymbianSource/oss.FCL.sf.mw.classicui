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
* Description:  Server and Session for AknCompaSrv
*
*/


#ifndef __AKNCOMPASERVER_H__
#define __AKNCOMPASERVER_H__

#include <e32base.h>
#include <w32std.h>

class CRepository;

// Needed for creating server thread.
const TUint KDefaultHeapSize=0x10000;

// Reasons for server panic
enum TAknCompaServerPanic
    {
    EBadRequest = 1,
    EBadDescriptor,
    EMainSchedulerError,
    ESvrCreateServer,
    ESvrStartServer,
    ECreateTrapCleanup
    };

// Reasons for client panic
enum TAknCompaServerClientPanic
    {
    EPanicClientNotAuthorized  = 1,
    };

/**
 * Window server event handler
 *
 * Reads events from window server event queue to keep it empty
 *
 * @since S60 v5.0
 */
class CAknCompaSrvWsEventHandler : public CActive
    {
public:
    CAknCompaSrvWsEventHandler(RWsSession& aWsSession);
    ~CAknCompaSrvWsEventHandler();

private: // New functions
    // Issue request to window server for events
    void IssueRequest();

private: // from CActive
    // Active object protocol
    void RunL();
    void DoCancel();

private:
    RWsSession& iWsSession;
    };

/**
 * CAknCompaServer server 
 *
 * @since S60 v5.0
 */
class CAknCompaServer : public CServer2
    {
public:
    static CServer2* NewLC();

    void AddSession();
    void DropSession();

    RWsSession& WsSession();

    // Function to panic the server
    static void PanicServer(TAknCompaServerPanic aPanic);
    static void PanicClient(const RMessage2& aMessage, TInt aPanic);

    static TBool IsGlobalUiSrv(const RMessage2& aMessage);

    static void SetThreadPriorityNormal(TAny* aUnused);
    static void SetThreadPriorityHigh();

    void DisaTransEffectsL(const RMessage2& aMessage);
    void RestoreTransEffectsL(const RMessage2& aMessage);
protected:
    CSession2* NewSessionL(const TVersion& aVersion,
        const RMessage2& aMessage) const;
    CAknCompaServer();
    ~CAknCompaServer();
    void ConstructL();

private:
    TInt iSessionCount;
    TBool iEffectsDisabled;
    RWsSession iWsSession;
    CRepository* iThemesCenRep; // repository to control transition effects
    CRepository* iAvkonCenRep;
    CAknCompaSrvWsEventHandler* iWsEventHandler;
    };

/**
 * Session to CAknCompaServer
 *
 * Provides a service to simulate key events for compa mode applications
 * that don't have swEvent capability.
 *
 * @since S60 v5.0
 */
class CAknCompaSrvSession : public CSession2
    {
public: // constructors and destructors
    CAknCompaSrvSession();
    void CreateL();

public: // services
    void SimulateKeyEventServiceL(const RMessage2& aMessage);

private:
    enum
        {
        // Allocate enough memory to hold all possible keys in the
        // key state array
        EKeyStateGranularity = 32
        };

    ~CAknCompaSrvSession();

    CAknCompaServer& Server();

    void SimulateKeyEvent(TInt aScancode, TBool aKeyDown);

    void CheckKeyDownPermissionL(const RMessage2& aMessage);

    // Service request
    void ServiceL(const RMessage2& aMessage);
    void DispatchMessageL(const RMessage2& aMessage);

private:
    RArray<TInt> iKeyState;
    TPtrC8 iValidScanCodes;
    };

#endif // __AKNCOMPASERVER_H__
