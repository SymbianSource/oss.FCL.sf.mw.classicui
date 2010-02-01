/*
* Copyright (c) 2005-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Handles shutdown situation.
*
*/

#ifndef AKNCAPSERVERSHUTDOWN_H
#define AKNCAPSERVERSHUTDOWN_H

#include <e32base.h>

class TApaTask;
class RWsSession;

class CAknCapServerShutdown : public CBase
    {
public:
    CAknCapServerShutdown();
    ~CAknCapServerShutdown();
    void ConstructL();
    
    void ShutdownAppsL(const TUid aRequesterUID, const RMessage2& aShutdownMessage, 
        const TInt aTimeoutInMicroseconds);
        
    void CancelShutdownAppsL();
    
private:
    enum TAknCapServerShutdownState 
        {
        EShutdownWaitingForApps = 0, 
        EShutdownKillingRogueApps
        };
    
    // Exits / kills a running task & notifies when complete.
    class CAppExitNotifier : public CActive
        {
    public:
        enum TAppExitMethod
            {
            EAppExitNormal,
            EAppExitForced
            };
            
    public: // Constructors and destructor
        static CAppExitNotifier* NewL(TApaTask* aTask,  CAknCapServerShutdown* aObserver);
        ~CAppExitNotifier();
        void ExitTask();        // The nice way, exits a task cleanly.
        void KillTask();        // The nasty way, kills a task. For use when ExitTask doesn't work.
        TBool IsDead();
        const TApaTask& Task() const;
        const TThreadId ThreadId() const;
        
    private:
        void ConstructL();
        void RunL();
        void DoCancel();
        CAppExitNotifier(TApaTask* aTask, CAknCapServerShutdown* aObserver);

    private:  // Data
        CAknCapServerShutdown* iObserver;   // Pointer to CAknCapServerShutdown for callbacks.
        TBool iIsDead;                      // Flag indicating the status of the thread.
        TApaTask* iTask;                    // Task being exited.
        RThread iThread;                    // iTask's thread.
        TThreadId iThreadId;                // iTask's threadID.
        TAppExitMethod iExitMethod;         // How the app is closed.
        };
public:
    void AppExitNotifierL(const CAppExitNotifier* aNotifier,
        CAppExitNotifier::TAppExitMethod aHowClosed);

private:
    static TInt ShutdownTimeoutL(TAny* aPtr);
    TInt DoShutdownTimeoutL();
    void ProceedWithShutdown();
    
private:
    RMessagePtr2 iShutdownMessage;
    CArrayPtrFlat<CAppExitNotifier>* iAppExitNotifiers;
    TInt iTotalAppExitNotifiers;
    CPeriodic* iShutdownTimeout;
    TAknCapServerShutdownState iShutdownState;
    RWsSession& iWs;
    };

#endif // AKNCAPSERVERSHUTDOWN_H
