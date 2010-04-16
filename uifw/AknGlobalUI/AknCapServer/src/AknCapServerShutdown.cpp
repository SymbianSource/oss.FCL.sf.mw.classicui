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

#include "AknCapServerShutdown.h"
#include <apgwgnam.h>
#include <coemain.h>
#include <apgtask.h>
#include <coedef.h>
#include <eiksvdef.h>

#include <gfxtranseffect/gfxtranseffect.h>
#include "akntranseffect.h" // for Transition effect enumerations

// Delay after sending rogue apps a kill signal before completing the shutdown.
const TInt KEikServShutdownAppKillDelay = 1000000;  // 1 second 
const TUid KCapServerUid = { 0x10207218 };
const TUid KFepSwitchWGId = {0xfabbabba}; // hoping that value is to stay...

_LIT( KViewServerThreadName, "ViewServerThread" );
_LIT( KUikonWatchersThreadName, "UikonWatchers" );
_LIT( KAknCapServerThreadName, "akncapserver" ); 
_LIT( KEikAppUiServerThreadName, "EikAppUiServerThread" );	
_LIT( KEikAppClock2ThreadName, "adtupdater" );	
_LIT( KEikAppBsengineThreadName, "bsengine" );	

// shut critical thread may cause system to reset during shut up process.
TBool IsSystemCriticalThread( const RThread& aThread )
    {
    if ( ( User::Critical( aThread ) == User::ESystemCritical ) ||
         ( aThread.Name() == KViewServerThreadName ) ||
         ( aThread.Name() == KAknCapServerThreadName ) ||
         ( aThread.Name() == KUikonWatchersThreadName ) ||
         ( aThread.Name() == KEikAppClock2ThreadName ) ||
         ( aThread.Name() == KEikAppBsengineThreadName ) ||
		 ( aThread.Name() == KEikAppUiServerThreadName ) )
        {
        return ETrue;
        }

    return EFalse;
    }

CAknCapServerShutdown::CAknCapServerShutdown()
: iWs(CCoeEnv::Static()->WsSession())
    {
    }
    
CAknCapServerShutdown::~CAknCapServerShutdown()
    {
    if (iAppExitNotifiers)
        {
        iAppExitNotifiers->ResetAndDestroy();
        }
    delete iAppExitNotifiers;
    delete iShutdownTimeout;
    }
    
void CAknCapServerShutdown::ConstructL()
    {
#ifdef _DEBUG
    RDebug::Print(_L("Creating app exit notifiers"));
#endif
    iAppExitNotifiers = new (ELeave) CArrayPtrFlat<CAppExitNotifier>(4);
    }

void CAknCapServerShutdown::ShutdownAppsL(
    const TUid aRequesterUID, 
    const RMessage2& aShutdownMessage, 
    const TInt aTimeoutInMicroseconds)
    {
    GfxTransEffect::BeginFullScreen(
        AknTransEffect::EApplicationExit,
        TRect(0,0,0,0),
        AknTransEffect::EParameterType,
        AknTransEffect::GfxTransParam(KCapServerUid, AknTransEffect::TParameter::EAvkonCheck));
      
    // Exit all apps currently running, with the exception of the one whose UID is passed in.
    iShutdownMessage = aShutdownMessage;

    CArrayFixFlat<TInt>* wgIds = new(ELeave) CArrayFixFlat<TInt>(4);
    CleanupStack::PushL(wgIds);
    User::LeaveIfError(iWs.WindowGroupList(0, wgIds));
    TInt lastEntry = wgIds->Count() - 1;

    iTotalAppExitNotifiers = 0;
    iAppExitNotifiers->ResetAndDestroy();

    for ( TInt ii = lastEntry; ii >= 0; ii-- )
      {
      CApaWindowGroupName* doomed = CApaWindowGroupName::NewLC(iWs, wgIds->At(ii));
      RThread thd;
      TThreadId threadId;

#ifdef _DEBUG
      TBool isSystem = doomed->IsSystem();
      TBool isHidden = doomed->Hidden();
#endif // _DEBUG
      // This UID comes from the app, not the mmp!
      TUid uid = doomed->AppUid(); 
      iWs.GetWindowGroupClientThreadId(wgIds->At(ii), threadId);
      thd.Open(threadId);  
	  CleanupClosePushL( thd );

      // Is this app OK to kill? We don't kill the this app, EikSrv backdrop or the app that 
      // instigated the shutdown.
      if ((uid != aRequesterUID) && ( uid != KCapServerUid ) && ( uid != KFepSwitchWGId ) && 
             ( doomed->Caption() != EIKON_SERVER_BACKDROP_WINDOW_GROUP_NAME ) &&
			  !IsSystemCriticalThread( thd ) )  
         {
         TApaTask* harbingerOfDoom = new (ELeave) TApaTask(iWs);
         CleanupDeletePushL(harbingerOfDoom);
         harbingerOfDoom->SetWgId(wgIds->At(ii));
                
#ifdef _DEBUG   // Silliness to prevent "using lvalue as rvalue" warnings.
         TPtrC caption(doomed->Caption()); // doomed->Caption());
         TPtrC docname(doomed->DocName()); // doomed->DocName());
         TPtrC wgname(doomed->WindowGroupName());  // doomed->WindowGroupName());
             
         _LIT(KDebugShutdownMsg1, "SHUTDOWN: Exiting App (ThreadId %d, WgId %d, ");
         RDebug::Print(KDebugShutdownMsg1, TUint(harbingerOfDoom->ThreadId()), wgIds->At(ii));
         _LIT(KDebugShutdownMsg2, "UID 0x%X); Caption: %S, ");
         RDebug::Print(KDebugShutdownMsg2, uid.iUid, &caption);
             
         _LIT(KDebugShutdownMsg3, "Docname: %S, system %d, ");
         RDebug::Print(KDebugShutdownMsg3, &docname, isSystem);
             
         _LIT(KDebugShutdownMsg4, "hidden %d, WGName : %S");
         RDebug::Print(KDebugShutdownMsg4, isHidden, &wgname);
         TPtrC threadName(thd.Name());
         RDebug::Print(_L("thread:%S)"), &threadName );
#endif // _DEBUG
         CAppExitNotifier* exiter = CAppExitNotifier::NewL(harbingerOfDoom, this);
         CleanupStack::Pop(); // harbingerOfDoom
         CleanupStack::PushL(exiter);
         iAppExitNotifiers->AppendL(exiter);
         iTotalAppExitNotifiers++;
         CleanupStack::Pop(); //exiter
         exiter->ExitTask();
         } 
#ifdef _DEBUG           
      else 
         {
         TPtrC caption = doomed->Caption();
         TPtrC threadName(thd.Name());
         RDebug::Print(_L("SHUTDOWN: privileged App %S(thread:%S) is not being closed"), &caption, &threadName );
         }
#endif

      CleanupStack::PopAndDestroy( &thd ); //thd
      CleanupStack::PopAndDestroy();  //doomed
      }

    // If no apps were running, complete straight away.
    if (iTotalAppExitNotifiers == 0)
        {
        iShutdownMessage.Complete(KErrNone);
        }
    else
        {
        // Start the timeout timer.
        iShutdownTimeout = CPeriodic::NewL(CActive::EPriorityHigh); 
        
        iShutdownTimeout->Start(
            aTimeoutInMicroseconds, 
            aTimeoutInMicroseconds, 
            TCallBack(ShutdownTimeoutL, this));
            
        iShutdownState=EShutdownWaitingForApps;
        }

    CleanupStack::PopAndDestroy(); // wgIds
    }
    
void CAknCapServerShutdown::CancelShutdownAppsL()
    {
    if ( !iShutdownMessage.IsNull() )
        {
        iShutdownMessage.Complete(KErrCancel);
        }
    }

// Static callback from Shutdown timeout.
TInt CAknCapServerShutdown::ShutdownTimeoutL(TAny* aPtr)
    {
    return (STATIC_CAST(CAknCapServerShutdown*,aPtr))->DoShutdownTimeoutL();
    }

TInt CAknCapServerShutdown::DoShutdownTimeoutL()
    {
    if (iShutdownState == EShutdownWaitingForApps)
        { //The timer has completed because not all apps have closed cleanly in the allotted time.
#ifdef _DEBUG
        RDebug::Print(_L("SHUTDOWN: Timeout! Killing remaining apps"));
#endif
        delete iShutdownTimeout;
        iShutdownTimeout = NULL;
        
        // Kill any remaining apps forcibly.
        for (TInt ii = 0; ii < iAppExitNotifiers->Count(); ii++)
            {
            if (!iAppExitNotifiers->At(ii)->IsDead())
                {
                iAppExitNotifiers->At(ii)->KillTask();
                }
            }
        
        // Now the remaining apps have been killed, there is no need to wait any longer.
        // We can allow the machine to turn off after a short delay.
        iShutdownTimeout = CPeriodic::NewL(CActive::EPriorityHigh); 
        
        iShutdownTimeout->Start(
            KEikServShutdownAppKillDelay, 
            KEikServShutdownAppKillDelay,
            TCallBack(ShutdownTimeoutL, this));
            
        iShutdownState = EShutdownKillingRogueApps;
        }
    else
        { 
        // The timer has completed because not all apps have responded to a kill request in the 
        // allotted time (this is bad).
#ifdef _DEBUG
        RDebug::Print(_L("SHUTDOWN: Error! At least one app failed to respond to kill request. Shutting down..."));
#endif
        ProceedWithShutdown();
        }

    return EFalse;
    }

// Callback from CAppExitNotifier.
void CAknCapServerShutdown::AppExitNotifierL(
    const CAppExitNotifier* aNotifier, 
    CAppExitNotifier::TAppExitMethod aHowClosed)
    {
    if (aHowClosed == CAppExitNotifier::EAppExitNormal)
        {
#ifdef _DEBUG
        RDebug::Print(_L("SHUTDOWN: App with ThreadId %d has exited"), TUint(aNotifier->ThreadId()));
#endif
        }
    else if (aHowClosed == CAppExitNotifier::EAppExitForced)
        {
#ifdef _DEBUG
        RDebug::Print(_L("SHUTDOWN: App with ThreadId %d was killed"), TUint(aNotifier->ThreadId()));
#endif
        }
    iTotalAppExitNotifiers--;
    
    // If all the apps have exited then complete the request.
    if (iTotalAppExitNotifiers == 0)
        {
        ProceedWithShutdown();
        }
    }
    
// Cleanup of objects used in shutdown, and signal to client that apps are all closed.
void CAknCapServerShutdown::ProceedWithShutdown()
    {
    // Complete the client message.
    iShutdownMessage.Complete(KErrNone);
    // Delete all the notifiers
    iAppExitNotifiers->ResetAndDestroy();
    // and stop the timeout timer.
    delete iShutdownTimeout;
    iShutdownTimeout=NULL;
    }

//
// class CAppExitNotifier
// 
CAknCapServerShutdown::CAppExitNotifier* CAknCapServerShutdown::CAppExitNotifier::NewL(
    TApaTask* aTask, 
    CAknCapServerShutdown* aObserver)
    {
    CAppExitNotifier* self = new (ELeave) CAppExitNotifier(aTask,aObserver);
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(); //self
    return self;
    }

CAknCapServerShutdown::CAppExitNotifier::~CAppExitNotifier()
    {
    Cancel();
    delete iTask;
    }

void CAknCapServerShutdown::CAppExitNotifier::ExitTask()
    {
    iExitMethod = EAppExitNormal;
    iTask->EndTask();
    }

void CAknCapServerShutdown::CAppExitNotifier::KillTask()
    {
    iExitMethod = EAppExitForced;
    iTask->KillTask();
    }

TBool CAknCapServerShutdown::CAppExitNotifier::IsDead()
    {
    return iIsDead;
    }

const TApaTask& CAknCapServerShutdown::CAppExitNotifier::Task() const
    {
    return *iTask;
    }

const TThreadId CAknCapServerShutdown::CAppExitNotifier::ThreadId() const
    {
    return iThreadId;
    }

void CAknCapServerShutdown::CAppExitNotifier::ConstructL()
    {
    iThreadId = iTask->ThreadId();
    User::LeaveIfError(iThread.Open(iThreadId));
    iThread.Logon(iStatus);
    SetActive();
    }

void CAknCapServerShutdown::CAppExitNotifier::RunL()
    {
    iIsDead = ETrue;
    iObserver->AppExitNotifierL(this,iExitMethod);
    }

void CAknCapServerShutdown::CAppExitNotifier::DoCancel()
    {
    iThread.LogonCancel(iStatus);
    }

CAknCapServerShutdown::CAppExitNotifier::CAppExitNotifier(TApaTask* aTask, 
    CAknCapServerShutdown* aObserver) 
: CActive(EPriorityStandard),
    iObserver(aObserver),
    iTask(aTask)
    {
    CActiveScheduler::Add(this);
    }

// End of file
