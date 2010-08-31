/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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

#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eiknotifyalert.h>
#include <viewclipartner.h>
#include <uiklaf/private/pluginuid.hrh>
#endif
#include <hal.h>
#include <hal_data.h>
#include <s32file.h>
#include <basched.h>
#include <bautils.h>
#include <eikdll.h>
#include <eikenv.h>
#include <eikkeys.h>
#include "eikkwin.h"
#include <eikmover.h>
#include <eikon.rsg>

#include <uikon/eiksrvui.h>
#include <eiksvdef.h>
#include <Eikalmct.h>

#define __ASSHDBITFLAGS_H__

#include <uikon/eikalsup.h>
#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikenvinterface.h>
#endif
#include <eikunder.h>
#include <uikon/eikalsrv.h>
#include <uikon/eiknfysv.h>
#include "EIKNFYUI.H"
#include <eiksrvui.rsg>
#include <viewcli.h>

/*
* Following resources used from Symbian's eikpriv.rss file:
* 
* r_eik_system_default_view_id
* r_eik_system_view_server_event_time_out
* r_eik_system_view_server_client_request_time_out
*/
#include <eikpriv.rsg>
#include "EIKSRV.HRH"

#include <aknPopup.h>
#include <avkon.rsg>
#include <eiktxlbx.h>
#include <eiktxlbm.h>
#include "eikkeysoundserver.h"
#include <aknsoundsystem.h>
#include <eikapp.h>
#include <aknenv.h>

#include <AknLayout.lag>
#include <AknUtils.h>
#include <AknsUtils.h>
#include <featmgr.h>

#include <e32property.h>
#include <UikonInternalPSKeys.h>    // KUikLayoutState

#include <aknpriv.rsg>
#include <AknDef.h>

#include <AknIconUtils.h>
#include <avkon.mbg>
#include <aknlayout.cdl.h>

#include <asclisession.h>
#include <asclidefinitions.h>
#include <ascliclientutils.h>
#include <c32comm.h>

#include <apasvst.h>
#include <apgcli.h>
#include <apgwgnam.h>
#include <viewcli.h>
#include <vwsappst.h> 

#include "e32uid.h"

#include <eiksrvsp.h>
#include <eiksrvs.h>
#include <akneiksrvs.h>

#include <uiklaf/private/lafenv.h>
#include <uiklaf/private/lafsrv.h>

#include <eikrutil.h>
#include <AknSgcc.h>
#include <aknconsts.h>

#include "EikLafShutStarter.h"
#include "EikLafShutScheduler.h"

#include <AknWsEventObserver.h>
#include <aknappui.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <AknFontSpecification.h>
#include <AknTextDecorationMetrics.h>
#include <e32capability.h>

#include <AknCapServerDefs.h>
#include <akndialogcontroller.h>

#include "AknNotifierControllerPlugin.h"
#include <AknCustomCursorSupport.h>
#include "AknEikSrv.pan"

#include <hb/hbcore/hbsymbianvariant.h>
#include <hb/hbcore/hbdevicedialogsymbian.h>

#if defined(__WINS__)
const TInt KEikServSideBarWidth = 35;
const TInt KEikServAppbarHeight = 50;
#endif

#if defined (__WINS__)
_LIT(COMMS_PDD_NAME, "ECDRV");
_LIT(COMMS_LDD_NAME, "ECOMM");
#else
_LIT(COMMS_PDD_NAME, "EUART1");
_LIT(COMMS_LDD_NAME, "ECOMM");
#endif

const TInt KEikServServerRestartDelay = 500000; // .5 sec
const TInt KEikServServerRestartInterval = 3000000; // 3 sec

_LIT(KResFileName, "z:\\resource\\eiksrvui.rsc");
_LIT(KAnimDllFileName, "AknAnimDll.Dll");
_LIT(KWatcherThreadName, "UikonWatchers");

const TInt KEikServPanicTextBufferSize = 512;

GLDEF_C void Panic(TEikServPanic aPanic)
    {
    _LIT(KPanicCat,"EIKON-SERVER");
    User::Panic(KPanicCat,aPanic);
    }

#define iAknCapServerClient (*(CAknSgcClient::AknSrv()))

class CFbsBitmap;

// =====================
// RKeySoundServerCloser
// =====================

class RKeySoundServerCloser : public RSessionBase
    {
public:
    void CloseServer();
    };

void RKeySoundServerCloser::CloseServer()
    {
    if (CreateSession(__KEYSOUND_SERVER_NAME, TVersion(KKeySoundServMajorVN, KKeySoundServMinorVN, 
        KKeySoundServBuildVN), 0) == KErrNone)
        {
        SendReceive(EKeySoundServerCloseServer, TIpcArgs());
        Close();
        }
    }

// ==================
// CEikServAppStarter
// ==================

class CEikServAppStarter : public CBase, public MVwsAppStarter
    {
public:
    static CEikServAppStarter* NewL();
    ~CEikServAppStarter();
public: // From MVwsAppStarter.
    void StartAppL(TUid aAppUid, TThreadId& aThreadId);
private:
    CEikServAppStarter();
    void ConstructL();
private:
    };

CEikServAppStarter* CEikServAppStarter::NewL()
    {
    CEikServAppStarter* self=new(ELeave) CEikServAppStarter;
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }

CEikServAppStarter::~CEikServAppStarter()
    {
    }

CEikServAppStarter::CEikServAppStarter()
    {
    }

void CEikServAppStarter::ConstructL()
    {
    }

void CEikServAppStarter::StartAppL(TUid aAppUid, TThreadId& aThreadId)
    {
    RApaLsSession ls;
    CleanupClosePushL(ls);
    User::LeaveIfError(ls.Connect());
    TApaAppInfo info;
    TInt err = ls.GetAppInfo(info,aAppUid);

    User::LeaveIfError(err);
    
    // LeaveIfError does not trigger to positive values, but GetAppInfo does not return valid 
    // data unless server returns KErrNone.
    if ( err > 0 ) 
        {         
        User::Leave(KErrNotReady);
        }

    CApaCommandLine* cmdLine = CApaCommandLine::NewLC();  
    cmdLine->SetExecutableNameL(info.iFullName);
    cmdLine->SetCommandL(EApaCommandViewActivate);
    
    // Using apparc client-server to do this "internal" launch.
    ls.StartApp(*cmdLine, aThreadId); 
    CleanupStack::PopAndDestroy(); // cmdLine
    CleanupStack::PopAndDestroy(); // ls
    }

// Thread function for OOD watcher.
GLDEF_C TInt WatcherThreadFunction(TAny* /*aParameters*/)
    {
    TInt err(KErrNone);

    CTrapCleanup* cleanup = CTrapCleanup::New();
    CActiveScheduler* scheduler = new CEikLafShutScheduler();
    CEikLafShutStarter* lafShut = NULL;

    if (!cleanup || !scheduler)
        {
        err = KErrNoMemory;
        }

    else
        {
        CActiveScheduler::Install(scheduler);
        TRAP(err, 
            {
            RThread me;
            me.SetPriority(EPriorityLess);
            lafShut = CEikLafShutStarter::NewL();
            })

        if (err == KErrNone)
            {
            // start the watchers
            CActiveScheduler::Start();
            }
        }

    delete cleanup;
    delete scheduler;
    delete lafShut;
    
    return err;
    }

// Creates thread for OOM & OOD watchers.
GLDEF_C void CreateWatcherThreadL()
    {
    RThread thread;

    TInt ret = thread.Create( 
        KWatcherThreadName, 
        WatcherThreadFunction,
        0x2000,                 // stack size
        NULL,                   // uses caller thread's heap
        (TAny*)NULL );

    if (ret == KErrNone)
        {
        thread.Resume();
        thread.Close();
        }

    User::LeaveIfError(ret);
    }

// ==================
// CEikSrvAppShutdown
// ==================

NONSHARABLE_CLASS(CEikSrvAppShutdown) : public CActive
    {
public:
    static void StartL(
        const TUid aRequesterUID, 
        const RMessage2& aShutdownMessage, 
        const TInt aTimeoutInMicroseconds);
private:
    CEikSrvAppShutdown(const RMessage2& aShutdownMessage);
    ~CEikSrvAppShutdown();
    void DoCancel();
    void RunL();
private:
    RMessagePtr2 iMessage;
    };

void CEikSrvAppShutdown::StartL(const TUid aRequesterUID, const RMessage2& aShutdownMessage,
    const TInt aTimeoutInMicroseconds)
    {
    if (iAknCapServerClient.Handle())
        {
        CEikSrvAppShutdown* self = new(ELeave) CEikSrvAppShutdown(aShutdownMessage);
        iAknCapServerClient.ShutdownApps(aRequesterUID, aTimeoutInMicroseconds, self->iStatus);
        self->SetActive();
        }
    else
        aShutdownMessage.Complete(KErrNone);
    }

CEikSrvAppShutdown::CEikSrvAppShutdown(const RMessage2& aShutdownMessage)
: CActive(CActive::EPriorityStandard), iMessage(aShutdownMessage)
    {
    CActiveScheduler::Add(this);
    }

CEikSrvAppShutdown::~CEikSrvAppShutdown()
    {
    Cancel();
    }

void CEikSrvAppShutdown::DoCancel()
    {
    }

void CEikSrvAppShutdown::RunL()
    {
    iMessage.Complete(KErrNone);
    delete this;
    }

// =============
// CEikServExtra
// =============

class CEikServExtra : public CBase
    {
public:
    CPeriodic* iServerRestarter;
    CArrayPtr<RWsPointerCursor>* iPointerCursors;
    CIdle* iNotifierServerStarter;
    };

const TInt KEiksrvUiDllValue = 0x100053D0;


EXPORT_C CEikServAppUiBase* CEikServAppUiBase::NewLC()
    {
    if (CEikonEnv::Static()->WsSession().FindWindowGroupIdentifier(
        0, __EIKON_SERVER_NAME, 0) > KErrNotFound)
        {
        return NULL; // Already an Eikon server running.
        }

    // This code duplicates what is in EikSrv.cpp in CEikServAppUiServer::CreateAppUiL().
    _LIT(KRomPath, "\\System\\Libs\\");
    _LIT(KEiksrvUiDllName, "EiksrvUi.dll");
    TFileName path;
    Dll::FileName(path);
    const TUint16& drv = path[0];
    if (drv == 'z' || drv == 'Z')
        {
        path.Append(KRomPath);
        }
    else
        {
        TParse parse;
        User::LeaveIfError(parse.Set(path, NULL, NULL));
        path = parse.DriveAndPath();
        }
    TUidType uidType(KDynamicLibraryUid, KSharedLibraryUid, TUid::Uid(KEiksrvUiDllValue));
    RLibrary lib;
    User::LeaveIfError(lib.Load(KEiksrvUiDllName, path, uidType));
    CleanupClosePushL(lib);
    TLibraryFunction appui = lib.Lookup(1);
    CEikServAppUiBase* self = REINTERPRET_CAST(CEikServAppUiBase*, (*appui)());
    User::LeaveIfNull(self);
    STATIC_CAST(CEikServEnv*, CEikonEnv::Static())->SetUiDll(lib);
    CleanupStack::Pop(); // lib
    CleanupStack::PushL(self);
    STATIC_CAST(CEikAppUi*, self)->ConstructL();

    return self;
    }

EXPORT_C void CEikServAppUiBase::NotifyAlarmServerOfTaskChangeL()
    {
    if (iAlarmAlertServer)
        {
        iAlarmAlertServer->TaskKeyPressedL();
        }
    }

EXPORT_C void CEikServAppUiBase::EnableTaskListL()
    {
    User::Leave(KErrNotSupported);
    }

EXPORT_C void CEikServAppUiBase::LaunchTaskListL()
    {
    User::Leave(KErrNotSupported);
    }

EXPORT_C void CEikServAppUiBase::CycleTasksL(enum TTaskCycleDirection aDirection) 
    {
    TApaTaskList taskList(iCoeEnv->WsSession());
    if (aDirection == EBackwards)
        {
        TApaTask task = taskList.FindByPos(-1);
        task.BringToForeground();
        }
    else
        {
        TApaTask task = taskList.FindByPos(0);
        task.SendToBackground();
        }
    
    // Will also task away from alarm when only 1 task!! Correct?        
    NotifyAlarmServerOfTaskChangeL(); 
    }

EXPORT_C CEikServAppUiBase::CEikServAppUiBase()
    {
    SetFullScreenApp(EFalse);
    }

LOCAL_C void ReleaseFactories(TAny* aPtr)
    {
    TEikServCtrlFactories& factory = *(TEikServCtrlFactories*)aPtr;
    if (factory.iAlert)
        {
        factory.iAlert->Release();
        }
    }

LOCAL_C void PointerCleanup(TAny* aPtr)
    {
    RWsPointerCursor* ptr = REINTERPRET_CAST(RWsPointerCursor*, aPtr);
    ptr->Close();
    delete ptr;
    }

EXPORT_C void CEikServAppUiBase::ConstructL() 
    {
    RWindowGroup& groupWin = iCoeEnv->RootWin();
    RWsSession& wsSession = iCoeEnv->WsSession();
    iEikonEnv->SetAutoForwarding(ETrue);
    iEikonEnv->SetSystem(ETrue);
    iEikonEnv->FsSession().SetNotifyUser(EFalse);

    // Must call BaseConstructL to get Avkon classes called.
#ifdef _DEBUG
    RDebug::Print(_L("CAknAppUiBase::BaseConstructL() in "));
#endif
    CAknAppUiBase::BaseConstructL(ENonStandardResourceFile|ENoScreenFurniture|
        EAknEnableMSK|EAknSingleClickCompatible);
#ifdef _DEBUG
    RDebug::Print(_L("CAknAppUiBase::BaseConstructL() out"));
#endif

    groupWin.SetName(__EIKON_SERVER_NAME);
    groupWin.EnableErrorMessages(EEventControlAlways);
    groupWin.EnableOnEvents(EEventControlAlways);
    wsSession.ComputeMode(RWsSession::EPriorityControlDisabled);
    iCoeEnv->RootWin().EnableScreenChangeEvents();
    RThread thread;
    
#if defined(__EPOC32__)
    thread.SetProcessPriority(EPriorityHigh);
#else
    thread.SetPriority(EPriorityAbsoluteForeground);
#endif

    // Create a window group for the password and alarm screens.
    iAlertGroupWin = RWindowGroup(wsSession);
    
    // EFalse disables key events - they will be enabled again as soon as the ordinal position is 
    // set such that iAlertGroupWin is not the foreground window-group.
    User::LeaveIfError(iAlertGroupWin.Construct((TUint32)this, EFalse)); 
    
    iAlertGroupWin.SetOrdinalPosition(0, ECoeWinPriorityNeverAtFront);
    
    // Enable key events, now that iAlertGroupWin is not in the foreground.
    iAlertGroupWin.EnableReceiptOfFocus(ETrue); 

    iEikServExtra = new(ELeave) CEikServExtra();
    
    TInt numCursors = LafServAppUiBase::NumberOfCursorsInSystemCursorList();
    if(numCursors != 0 && LafServAppUiBase::ClaimPointerCursorListIfNeeded(*iEikonEnv) == KErrNone)
        {
        iEikServExtra->iPointerCursors = new(ELeave) CArrayPtrFlat<RWsPointerCursor>(4);
        TSpriteMember member;
        for(TInt ii = 0; ii < numCursors; ii++)
            {
            RWsPointerCursor* cursor = LafServAppUiBase::ConstructPointerCursorL(ii, member, 
                *iEikonEnv);
                
            CleanupStack::PushL(TCleanupItem(PointerCleanup, cursor));
            iEikServExtra->iPointerCursors->AppendL(cursor);
            CleanupStack::Pop(); // cursor - handle & ptr
            }
        }
    }

EXPORT_C void CEikServAppUiBase::InitializeL(TEikServCtrlFactories& aCtrlFactories)
    {
    RWindowGroup& rootWin = iCoeEnv->RootWin();

    CleanupStack::PushL(TCleanupItem(&ReleaseFactories,&aCtrlFactories));
    RFs& fsSession = iCoeEnv->FsSession();
    _LIT(KAppDirName, "C:\\System\\Apps\\");
    fsSession.MkDirAll(KAppDirName); // !! prevent app arch crash

    // Initialize some system settings.
    SetSystemTime();
    rootWin.EnableOnEvents(EEventControlAlways);

    TPasswordMode mode = EPasswordNone;

    TRAP_IGNORE(
        CEikPasswordModeCategory* pcategory = CEikPasswordModeCategory::NewLC(fsSession);
        if( pcategory )
            {
            pcategory->GetPasswordModeL(mode);
            if (mode == EPasswordNone) // prevent overwriting once per day
                {
                mode = EPasswordAlways;    
                }
            // Initialise (write to system.ini) here so that it won't fail in the future due to OOM.
            pcategory->SetPasswordModeL(mode);
            CleanupStack::PopAndDestroy(); // pcategory
            }
        );

    // Create separate thread for OOD watchers.
    CreateWatcherThreadL();

    // Start View Server.
    iAppStarter = CEikServAppStarter::NewL();
    User::LeaveIfError(CVwsSessionWrapper::StartViewServer(*iAppStarter));
    iVwsSession = CVwsSessionWrapper::NewL();
    
    TResourceReader reader;
    iEikonEnv->CreateResourceReaderLC(reader, R_EIK_SYSTEM_DEFAULT_VIEW_ID);
    TVwsViewId viewId;
    viewId.iAppUid.iUid = reader.ReadInt32();
    viewId.iViewUid.iUid = reader.ReadInt32();
    CleanupStack::PopAndDestroy(); // reader
    iVwsSession->SetSystemDefaultView(viewId);

    TInt serverEventTimeOutDuration = EikResourceUtils::ReadTInt32L(    
        R_EIK_SYSTEM_VIEW_SERVER_EVENT_TIME_OUT, iEikonEnv);
        
    iVwsSession->SetServerEventTimeOut( TTimeIntervalMicroSeconds32(serverEventTimeOutDuration) );
    
    TInt clientRequestTimeOutDuration = EikResourceUtils::ReadTInt32L(
        R_EIK_SYSTEM_VIEW_SERVER_CLIENT_REQUEST_TIME_OUT, iEikonEnv);
        
    iVwsSession->SetClientRequestTimeOut( TTimeIntervalMicroSeconds32(clientRequestTimeOutDuration) );

    iVwsSession->EnableServerBlankScreen(EFalse);
    iVwsSession->EnableServerEventTimeOut(EFalse);
    
    // Start Comms
    TInt err = StartC32();
    if (err != KErrNone && err != KErrAlreadyExists)
        {
        User::Leave(err);
        }
    
    err = User::LoadPhysicalDevice(COMMS_PDD_NAME);
    if (err != KErrNone && err != KErrAlreadyExists && err != KErrNotFound)
        {
        User::Leave(err);
        }
        
    err = User::LoadLogicalDevice(COMMS_LDD_NAME);
    if (err != KErrNone && err != KErrAlreadyExists && err != KErrNotFound)
        {
        User::Leave(err);
        }

    // Start notifier server last as these may have plug-ins that rely on the other servers 
    // started here being up and running.
    iNotifyServer = CEikServNotifyServer::NewL(aCtrlFactories.iAlert);

    CleanupStack::Pop(); // aCtrlFactories

    iEikServExtra->iNotifierServerStarter = CIdle::NewL(CActive::EPriorityLow);
    iEikServExtra->iNotifierServerStarter->Start(TCallBack(StartNotifierServerCallBackL, this));

    rootWin.EnableGroupListChangeEvents();

    // Create undertaker active object.
    iUndertaker = CEikUndertaker::NewL(*this);

    // Create an active object to restart servers. 
    iEikServExtra->iServerRestarter = CPeriodic::NewL(CActive::EPriorityStandard);
    }

EXPORT_C void CEikServAppUiBase::HandleThreadExitL(RThread& aThread)
    {
    _LIT(KAppArcServerThread, "AppArcServerThread");
    if (aThread.Name() == ASCliDefinitions::ServerAndThreadName()) // alarm server died
        {
        aThread.Close(); // need to Close() before restarting with same name
        iServerToRestart |= EAlwlSvr; // restarted under active object
        }
    else if (aThread.Name() == KAppArcServerThread) // AppArc server died
        {
        aThread.Close();
        iServerToRestart|=EApaSvr;
        }
        
    if (iServerToRestart && !iEikServExtra->iServerRestarter->IsActive())
        {
        iEikServExtra->iServerRestarter->Start(
            KEikServServerRestartDelay, 
            KEikServServerRestartInterval, 
            TCallBack(RestartServerCallback, this));
        }
    }

EXPORT_C void CEikServAppUiBase::HandleForegroundEventL(TBool aForeground)
    {
    CAknAppUiBase::HandleForegroundEventL(aForeground);
    }

TInt CEikServAppUiBase::RestartServerCallback(TAny* aObj)
    {
    STATIC_CAST(CEikServAppUiBase*, aObj)->RestartServer();
    return KErrNone;
    }

TInt CEikServAppUiBase::StartNotifierServerCallBackL(TAny* aPtr)
    { // static
    CEikServAppUiBase* self = static_cast<CEikServAppUiBase*>(aPtr);
    self->iNotifyServer->StartL();
    delete self->iEikServExtra->iNotifierServerStarter;
    self->iEikServExtra->iNotifierServerStarter=NULL;
    return KErrNone;
    }

// Kick dead servers back to life, if we can connect then stop kicking.
void CEikServAppUiBase::RestartServer()
    {
    if (iServerToRestart & EAlwlSvr)
        {
        // Start AlarmServer
        TInt err = AlarmClientUtils::StartAlarmServer();
        if (err == KErrNone)
            {
            iServerToRestart&=(~EAlwlSvr);
            }
        }
        
    if (iServerToRestart&EApaSvr)
        {
        AknStartupApaServerProcess();

        // try to connect to the server
        RApaLsSession ls;
        TInt err = ls.Connect();
        if (err == KErrNone)
            {
            ls.Close();
            iServerToRestart&=(~EApaSvr);
            }
        }
        
    if (!iServerToRestart)
        {
        iEikServExtra->iServerRestarter->Cancel();
        }
    }

EXPORT_C TKeyResponse CEikServAppUiBase::HandleKeyEventL(const TKeyEvent& aKeyEvent, 
    TEventCode /*aType*/)
    {
    if (aKeyEvent.iCode == CTRL('e'))
        {
        CBaActiveScheduler::Exit();
        }
    return EKeyWasConsumed;
    }

// Check the battery states and update any alarm snooze time.
EXPORT_C void CEikServAppUiBase::HandleSwitchOnEventL(CCoeControl* /*aDestination*/)
    {
    // Could just expose alarm alert server to UI dll!!
    if (iAlarmAlertServer)
        {
        iAlarmAlertServer->HandleSwitchOnEvent();
        }
    }

EXPORT_C void CEikServAppUiBase::HandleSystemEventL(const TWsEvent& aEvent)
    {
    TInt event = *((TInt*)aEvent.EventData());
    switch (event)
        {
#ifdef _DEBUG
        case EEikServExit:
            CBaActiveScheduler::Exit();
            break;
#endif
        default:
            break;
        }
    }

EXPORT_C void CEikServAppUiBase::HandleApplicationSpecificEventL(TInt aType, const TWsEvent& aEvent)
    {
    // Check command/number or whatever first!!
    CAknAppUiBase::HandleApplicationSpecificEventL(aType, aEvent);
    }


EXPORT_C CEikServAppUiBase::~CEikServAppUiBase()
    {
    delete iUndertaker;
    
    if (iEikServExtra)
        {
        delete iEikServExtra->iServerRestarter;
        
        if (iEikServExtra->iPointerCursors)
            {
            const TInt count = iEikServExtra->iPointerCursors->Count();
            
            for (TInt ii = 0; ii < count; ii++)
                {
                (*(iEikServExtra->iPointerCursors))[ii]->Close();
                }
                
            iEikServExtra->iPointerCursors->ResetAndDestroy();
            delete iEikServExtra->iPointerCursors;
            }
            
        delete iEikServExtra->iNotifierServerStarter;
        delete iEikServExtra;
        }
        
    LafServAppUiBase::FreePointerCursorListIfNeeded(*iEikonEnv);
    RWindowGroup& groupWin = iEikonEnv->RootWin();
    groupWin.DisableErrorMessages();
    groupWin.DisableOnEvents();
    iAlertGroupWin.Close();
    delete iNotifyServer;
    delete iAlarmAlertServer;
    delete iAppStarter;
    
    if (iVwsSession)
        {
        iVwsSession->ShutdownViewServer();
        delete iVwsSession;
        }
    }

void CEikServAppUiBase::SetSystemTime() const
    {
    // Deprecated, we don't have capability to set system time.
    }

// Bring to foreground or send to background appropriately.
EXPORT_C void CEikServAppUiBase::BringAlertGroupWinForwards(TBool aForwards)
    {
    if (aForwards)
        {
        if (!iAlertGroupForwardsCount++)
            {
            iAlertGroupWin.SetOrdinalPosition(0, KMaxTInt); 
            }
        }
    else if (--iAlertGroupForwardsCount == 0)
        {
        iAlertGroupWin.SetOrdinalPosition(0, ECoeWinPriorityNeverAtFront); 
        }
    }

EXPORT_C void CEikServAppUiBase::SetStatusPaneFlags(TInt /*aFlags*/)
    {
    User::Leave(KErrNotSupported);
    }

EXPORT_C void CEikServAppUiBase::SetStatusPaneLayoutL(TInt /*aLayoutResId*/)
    {
    User::Leave(KErrNotSupported);
    }

EXPORT_C void CEikServAppUiBase::BlankScreenL()
    {
    User::Leave(KErrNotSupported);
    }

EXPORT_C void CEikServAppUiBase::UnblankScreen()
    {
    User::Leave(KErrNotSupported);
    }

EXPORT_C void CEikServAppUiBase::ShutdownAppsL(const TUid aRequesterUID, 
    const RMessage2& aShutdownMessage, const TInt aTimeoutInMicroseconds)
    {
    CEikSrvAppShutdown::StartL(aRequesterUID, aShutdownMessage, aTimeoutInMicroseconds);
    }

EXPORT_C void CEikServAppUiBase::HandleResourceChangeL(TInt aType)
    {
    CAknAppUiBase::HandleResourceChangeL(aType);
    }

void CEikServAppUiBase::Extension(TUid /*aExtensionUid*/, const TDesC8& /*aBuffer*/, 
    RMessagePtr2 /*aMessage*/)
    {
    // Not implemented
    }

EXPORT_C void CEikServAppUiBase::HandleWsEventL(const TWsEvent& aEvent,CCoeControl* aDestination)
    {
    CAknAppUiBase::HandleWsEventL(aEvent, aDestination);
    }

void CEikServAppUiBase::SetSgcParamsL(TInt /*aWgId*/, TBitFlags /*aAppFlags*/, TInt /*aSpLayout*/, 
    TInt /*aSpFlags*/)
    {
    }

void CEikServAppUiBase::PrepareForAppExitL(TInt /*aWgId*/)
    {
    }


// =============
// CEikServAppUi
// =============

void CEikServAppUi::SetStatusPaneFlags(TInt aFlags)
    {
    if (iAknCapServerClient.Handle())
        {
        iAknCapServerClient.SetStatusPaneFlags(aFlags);
        }
    }

void CEikServAppUi::SetStatusPaneLayoutL(TInt aLayoutResId)
    {
    if (iAknCapServerClient.Handle())
        {
        iAknCapServerClient.SetStatusPaneLayout(aLayoutResId);
        }
    }

void CEikServAppUi::BlankScreenL()
    {
    if (iAknCapServerClient.Handle())
        {
        iAknCapServerClient.BlankScreen();
        }
    }

void CEikServAppUi::UnblankScreen()
    {
    if (iAknCapServerClient.Handle())
        {
        iAknCapServerClient.UnblankScreen();
        }
    }

void CEikServAppUi::EnableTaskListL()
    {
    User::LeaveIfError(iAknCapServerClient.EnableTaskList(ETrue));
    }

void CEikServAppUi::LaunchTaskListL() //const
    {
    User::LeaveIfError(iAknCapServerClient.MakeTaskListVisible(ETrue));
    }

void CEikServAppUi::CloseTaskList() //const
    {
    // Ignore possible error.
    iAknCapServerClient.MakeTaskListVisible(EFalse);
    }

CEikServAppUi::CEikServAppUi()
    {
    }

void CEikServAppUi::ConstructL()
    {
    // Create stub to allow device boot up with old notifier controller dependencies.
    iNotifierDialogController = CNotifierDialogController::NewL(0);

#ifdef _DEBUG
    RDebug::Print(_L("CEikServAppUi::ConstructL() in"));
#endif

    AknsUtils::InitSkinSupportL();
#ifdef _DEBUG
    RDebug::Print(_L("CEikServAppUi::ConstructL() init skins ok"));
#endif

    CEikServAppUiBase::ConstructL();
#ifdef _DEBUG
    RDebug::Print(_L("CEikServAppUi::ConstructL() CEikServAppUiBase constructed"));
#endif

    AknsUtils::SetAvkonSkinEnabledL( ETrue );
#ifdef _DEBUG
    RDebug::Print(_L("CEikServAppUi::ConstructL(), CEikServAppUiBase::ConstructL() succeed"));
#endif

    AknsUtils::SetAvkonSkinEnabledL( ETrue );
#ifdef _DEBUG
    RDebug::Print(_L("CEikServAppUiBase::ConstructL(), Skins enabled"));
#endif

    TFileName fileName(KResFileName);
    BaflUtils::NearestLanguageFile(iEikonEnv->FsSession(), fileName);
    iResourceFileOffset = iCoeEnv->AddResourceFileL(fileName);

    // Create notifier controller before Notfier server is started.
    iNotifierController = CAknNotifierController::NewL();

#ifdef _DEBUG
    RDebug::Print(_L("CEikServAppUi::ConstructL(), initializing Alert"));
#endif

    CEikServNotifyAlert* alert=new(ELeave) CEikServNotifyAlert;
    CleanupStack::PushL(alert);
    alert->ConstructL();
    TEikServCtrlFactories fctry;
    fctry.iAlert = alert;
    fctry.iAlarmAlert = this;
    CleanupStack::Pop();

#ifdef _DEBUG
    RDebug::Print(_L("CEikServAppUi::ConstructL(), Alert created"));
#endif

    CEikServAppUiBase::InitializeL(fctry);

#ifdef _DEBUG
    RDebug::Print(_L("CEikServAppUiBase::InitializeL(fctry) succeed"));
#endif

    RWsSession& wsSession = iCoeEnv->WsSession();

    // Initialize some system settings.
    TRAP_IGNORE(EnsureExternalKeyHandlerAppStreamExistsL());

#ifdef _DEBUG
    RDebug::Print(_L("CEikServAppUi::ConstructL(), Creating WG for status pane"));
#endif

    // Create high priority windows for app bar and side bar.
    iOffScreenGroupWin = RWindowGroup(wsSession);
    User::LeaveIfError(iOffScreenGroupWin.Construct((TUint32)&iOffScreenGroupWin, 
        EFalse)); // EFalse disables key events
    iOffScreenGroupWin.SetOrdinalPosition(0,ECoeWinPriorityHigh);

#ifdef _DEBUG
    RDebug::Print(_L("CEikServAppUi::ConstructL(), Starting sound server"));
#endif

    // Launch the Avkon KeySound Server
    User::LeaveIfError(CEikKeySoundServer::LaunchServer(iKeySoundThreadId));
    
    // Start the Avkon Anim Dll - required for keysounds
    iAknAnimDll = new(ELeave)RAnimDll(wsSession);
    iAknAnimDll->Load(KAnimDllFileName);
    iAknAnimKeySound = new(ELeave)RAknAnimKeySound(*iAknAnimDll);
    iAknAnimKeySound->ConstructL(&iOffScreenGroupWin);

#ifdef _DEBUG
    RDebug::Print(_L("CEikServAppUi::ConstructL(), Keysounds and plugin initialized"));
#endif

    // Create default keysounds - pass in UID.
    ReplaceKeySoundsL(0x100053D0);

#ifdef _DEBUG
    RDebug::Print(_L("CEikServAppUi::ConstructL(), Default client and context for keysound created "));
#endif

    // Window server buffer size.
    RWsSession &ws = iEikonEnv->WsSession();
    TInt bufSize = 6400;
    ws.SetMaxBufferSizeL(bufSize);

    // Load bitmap cursors.
    LoadBitmapCursorsL();

    STATIC_CAST(CEikServEnv*,CEikonEnv::Static())->SetEikServAppUiSessionFactory( this );

#ifdef _DEBUG
    RDebug::Print(_L("CEikServAppUi::ConstructL(), over and out"));
#endif
    }


void CEikServAppUi::RestartKeySoundThreadL()
    {
    // Restart keysound server.
    TInt err = CEikKeySoundServer::LaunchServer(iKeySoundThreadId);
    if (err != KErrNone)
        {
        // Server cannot be restarted, so leave existing animation dll.
        // No sounds will be played, but machine will still operate.
        return;
        }
        
    // Restart the animation dll
    if (iAknAnimKeySound)
        {
        iAknAnimKeySound->Close();
        delete iAknAnimKeySound;
        iAknAnimKeySound = NULL;
        }
        
    if (iAknAnimDll)
        {
        iAknAnimDll->Close();
        delete iAknAnimDll;
        iAknAnimDll = NULL;
        }

    // Restart the animation dll.
    iAknAnimDll = new(ELeave)RAnimDll(iCoeEnv->WsSession());
    iAknAnimDll->Load(KAnimDllFileName);
    iAknAnimKeySound = new(ELeave)RAknAnimKeySound(*iAknAnimDll);
    iAknAnimKeySound->ConstructL(&iOffScreenGroupWin);

    // Invented new API.
    ReplaceKeySoundsL(0x100053D0);
    KeySounds()->BringToForeground();
    }

LOCAL_C void ShowNotificationDialog(const TDesC& aNoteText)
    {
    _LIT(KNotificationDialogPlugin, "com.nokia.hb.devicenotificationdialog/1.0");
    _LIT(KTimeout, "timeout");
    _LIT(KTitle,   "title");

    //@TODO replace the hardcoded parameter after enum EASyncServerStartup
    // is defined(after MCL wk26).
    //CHbDeviceDialogSymbian* dlg = CHbDeviceDialogSymbian::NewL(
    //                    CHbDeviceDialogSymbian::EASyncServerStartup);
    CHbDeviceDialogSymbian* dlg = CHbDeviceDialogSymbian::NewL(2);
    CleanupStack::PushL(dlg);

    TInt  timeout = 0;
        
    CHbSymbianVariantMap* map = CHbSymbianVariantMap::NewL();
    CleanupStack::PushL(map);
    
    map->Add(KTimeout, CHbSymbianVariant::NewL(&timeout,    CHbSymbianVariant::EInt));
    map->Add(KTitle,   CHbSymbianVariant::NewL(&aNoteText,  CHbSymbianVariant::EDes));
    
    dlg->Show(KNotificationDialogPlugin, *map);

    CleanupStack::PopAndDestroy(2);
    }

void CEikServAppUi::HandleThreadExitL(RThread& aThread)
    {
    if(aThread.Name().CompareF(_L("aknnfysrv")) == 0)
        {
        StartNewServerApplicationL(KCommonNotifierAppSrvUid);
        return;
        }

    TThreadId id = aThread.Id();
    TExitType exitType = aThread.ExitType();
    if (id == iExternalKeyHandlerThreadId)
        {
        iExternalKeyHandlerRunning = EFalse;
        }
    else if (id == iHelpAppThreadId)
        {
        iHelpAppRunning = EFalse;
        }
    else if (id == iKeySoundThreadId)
        {
        RestartKeySoundThreadL();
        // Don't tell the user about it.
        return;
        }

    TBool rdSupport = BaflUtils::FileExists( iEikonEnv->FsSession(), KRDSupport );

    // Show panic notes only if that feature is enabled.
    if ( exitType == EExitPanic && ( rdSupport || FeatureManager::FeatureSupported( 
        KFeatureIdShowPanics )) )
        {
        // Construct text for a panic note.
        HBufC* panicText = ConstructPanicTextLC( aThread, rdSupport );
        
        /* iAknCapServerClient.ShowGlobalNoteL(panicText->Des(), EAknGlobalErrorNote); */

        ShowNotificationDialog( panicText->Des() );

        CleanupStack::PopAndDestroy(); // panicText
        }
        
    CEikServAppUiBase::HandleThreadExitL(aThread);
    }

void CEikServAppUi::UpdateTaskListL()
    {
    iAknCapServerClient.UpdateTaskList();
    }

TKeyResponse CEikServAppUi::HandleKeyEventL(const TKeyEvent& aKeyEvent, TEventCode /*aType*/)
    {
    if (aKeyEvent.iCode == CTRL('e')) // Exit
        {
        CBaActiveScheduler::Exit();
        }
    return EKeyWasConsumed;
    }

void CEikServAppUi::HandleWsEventL(const TWsEvent& aEvent, CCoeControl* aDestination)
    {
    switch (aEvent.Type())
        {
        case EEventPassword:
            {
            // No action in Avkon.
            break;
            }
        case EEventErrorMessage:
            HandleErrorMessageEvent(*(aEvent.ErrorMessage()));
            break;
        case KUidValueAknsSkinChangeEvent:
            {
            HandleResourceChangeL(KAknsMessageSkinChange);
            HandleStackedControlsResourceChange(KAknsMessageSkinChange);
            break;
            }
        default:
            CEikServAppUiBase::HandleWsEventL(aEvent, aDestination);
            break;
        }
    }

// Handle an error message from the window server.
void CEikServAppUi::HandleErrorMessageEvent(const TWsErrorMessage& aErrorMessage)
    {
    TUint err = aErrorMessage.iError;
    
    switch (aErrorMessage.iErrorCategory)
        {
        case TWsErrorMessage::EDrawingRegion:
            HandleOomEvent();
            break;
        case TWsErrorMessage::EBackLight:
            HandleBacklightError(err);
            break;
        case TWsErrorMessage::ELogging:
            HandleWservLoggingError(err);
            break;
        default:
            break; // intentionally ignored
        }
    }

void CEikServAppUi::HandleResourceChangeL(TInt aType)
    {
    CEikServAppUiBase::HandleResourceChangeL(aType);
    if ( aType == KEikDynamicLayoutVariantSwitch )
        {
        UpdateCursorsL();
        }
    }

// Check the battery states and update any alarm snooze time.
void CEikServAppUi::HandleSwitchOnEventL(CCoeControl* /*aDestination*/)
    {
    if (iAlarmAlertServer)
        {
        iAlarmAlertServer->HandleSwitchOnEvent();
        }
    }

void CEikServAppUi::HandleSystemEventL(const TWsEvent& aEvent)
    {
    TInt event = *((TInt*)aEvent.EventData());
    switch (event)
        {
#ifdef _DEBUG
        case EEikServExit:
            CBaActiveScheduler::Exit();
            break;
#endif
        case EEikServChangePasswordMode:
            // No action in Avkon
            break;
        case EEikServShowTaskList:
            LaunchTaskListL();
            break;
        case EEikServHideTaskList:
            CloseTaskList();
            break;
        default:
            break;
        }
    }

CEikServAppUi::~CEikServAppUi()
    {
    if (iAknAnimKeySound)
        {
        iAknAnimKeySound->Close();
        }
    delete iAknAnimKeySound;
    
    if (iAknAnimDll)
        {
        iAknAnimDll->Close();
        }
    delete iAknAnimDll;

    // Shut down the key sound server.
    RKeySoundServerCloser ksCloserSession;
    ksCloserSession.CloseServer();

    iOffScreenGroupWin.Close();
    delete iAppbarWindow;
    delete iSidebarWindow;
    
    if (iCoeEnv)
        {
        iCoeEnv->DeleteResourceFile(iResourceFileOffset);
        }

    delete iIdler;
    iNotifServerAppQueue.Close();

    delete iNotifierController;
    delete iNotifierDialogController;
    }

MEikServAlarm* CEikServAppUi::NewAlarmL(CEikAlmControlSupervisor& aSupervisor)
    {
    CEikAlarmControl* alarm = new(ELeave) CEikAlarmControl(&aSupervisor,this);
    CleanupStack::PushL(alarm);
    alarm->ConstructL();
    CleanupStack::Pop(); // alarm
    return alarm;
    }

void CEikServAppUi::EnsureExternalKeyHandlerAppStreamExistsL()
    {
    }

// Respond to an out of memory event from the window server.
void CEikServAppUi::HandleOomEvent()
    {
    TBuf<80> msg1;
    TBuf<80> msg2;
    iEikonEnv->ReadResource(msg1, R_EIKSRV_OOM_EVENT_TOP);
    iEikonEnv->ReadResource(msg2, R_EIKSRV_OOM_EVENT_BOT);
    MEikAlertWin* mAlert = CONST_CAST(MEikAlertWin*, iEikonEnv->Alert());
    CEikDialog* alert = mAlert->AsEikDialog();
    
    CEikMover* title = NULL;
    if ( alert )
        {
        title = &( alert->Title() );
        alert->SetGloballyCapturing(ETrue);
        title->SetActive(EFalse);
        }
    iEikonEnv->AlertWin(msg1, msg2);
    if ( alert )
        {
        title->SetActive(ETrue);
        alert->SetGloballyCapturing(EFalse);
        }
    }

// Respond to an error from the backlight (battery too low).
void CEikServAppUi::HandleBacklightError(TInt /*aError*/)
    {
    }

// Respond to a logging error from wserv (for use by developers)
void CEikServAppUi::HandleWservLoggingError(TInt aError)
    {
    TBuf<80> temp;
    iEikonEnv->ReadResource(temp, R_EIKSRV_WSERV_LOGGING_ERROR);
    TBuf<80> msg;
    msg.Format(temp, aError);
    iEikonEnv->AlertWin(msg);
    }

EXPORT_C void CEikServAppUi::SuppressAppSwitching(TBool aSuppress)
    {
    // Ignore error as there is nothing to do if failing.
    iAknCapServerClient.ConnectAndSendAppsKeySuppress(aSuppress);
    }

HBufC* CEikServAppUi::ConstructPanicTextLC( RThread& aThread, TBool aRDSupport ) const
    {
    HBufC* panicText = HBufC::NewLC( KEikServPanicTextBufferSize );
    TPtr ptr = panicText->Des();

    iEikonEnv->ReadResource( ptr, R_PROGRAM_CLOSED );

    ptr.Append( '\n' );

    HBufC* buffer = aThread.Name().AllocL();
    TPtr name = buffer->Des();

    // Here we truncate the thread name to fit in the second and third lines of the note.

    TRect mainPane;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EPopupParent, mainPane );
    TAknLayoutRect popupNoteWindow;
    
    AknLayoutUtils::TAknCbaLocation cbaLocation( AknLayoutUtils::CbaLocation() );
    TInt variety( 0 );
    if ( cbaLocation == AknLayoutUtils::EAknCbaLocationRight )
        {
        variety = 3;
        }
    else if ( cbaLocation == AknLayoutUtils::EAknCbaLocationLeft )
        {
        variety = 6;
        }
    else
        {
        variety = 0;
        }
        
    popupNoteWindow.LayoutRect(mainPane, AknLayoutScalable_Avkon::popup_note_window( variety ) );
        
    TAknLayoutText textRectTwoLines;
    
    textRectTwoLines.LayoutText(
        popupNoteWindow.Rect(), 
        AKN_LAYOUT_TEXT_Note_pop_up_window_texts_Line_1(1));

    // First determine how much fits in the 2. line of the note this can't return NULL.
    const CFont* font = textRectTwoLines.Font();

    TInt characters( font->TextCount( name, textRectTwoLines.TextRect().Width() ) );

    // 'characters' is now the amount of characters that fit in the second line.

    ptr.Append( name.Left( characters ) );
    ptr.Append( '\n' );

    // If the name was cut, clip the rest in the third line.
    TInt charactersLeft( name.Length() - characters );

    if ( charactersLeft > 0 )
        {
        TPtr line3( 
            (TText*)&name[characters],
            charactersLeft,
            charactersLeft );

        popupNoteWindow.LayoutRect(
            mainPane, 
            AknLayoutScalable_Avkon::popup_note_window( variety + 1) );
            
        TAknLayoutText textRectThreeLines;
        
        textRectThreeLines.LayoutText(
            popupNoteWindow.Rect(), 
            AKN_LAYOUT_TEXT_Note_pop_up_window_texts_Line_1(2));
            
        // No bidirectional text support for rendering the thread name. This is intentional.

        AknTextUtils::ClipToFit(
            line3,
            *font,
            textRectThreeLines.TextRect().Width() );

        ptr.Append( line3 );
        ptr.Append( '\n' );
        }

    delete buffer;

    // Append panic category and reason only if RD-support file exists.

    if ( aRDSupport )
        {
        ptr.Append( aThread.ExitCategory() );
        ptr.Append( ' ' );
        ptr.AppendNum( aThread.ExitReason() );
        }

    return panicText;
    }

void CEikServAppUi::LoadBitmapCursorsL()
    {
    RWsSession& ws = iEikonEnv->WsSession();

    // Create the array containing one sprite member.
    TFixedArray<TSpriteMember, 1> spriteMemberArray;
    TSpriteMember& spriteMember = spriteMemberArray[0];
    spriteMember.iInterval = TTimeIntervalMicroSeconds32(0);

    // This resource is of type AVKON_CUSTOM_TEXT_CURSORS defined in eiksrvui.rss.
    TResourceReader reader;
    iEikonEnv->CreateResourceReaderLC(reader, R_AKN_CUSTOM_TEXT_CURSORS);

    HBufC* bmpFile = reader.ReadHBufCL();
    CleanupStack::PushL(bmpFile);


    TInt count = reader.ReadInt16();
    for (TInt ii = 0; ii < count; ii++)
        {
        // id
        TInt id = reader.ReadInt32();

        // bmpId and maskId
        TInt bmpId = reader.ReadInt32();
        TInt maskId = reader.ReadInt32();
        spriteMember.iBitmap = NULL;
        spriteMember.iMaskBitmap = NULL;

        if (maskId != -1)
            {
            AknIconUtils::CreateIconLC( 
                spriteMember.iBitmap,
                spriteMember.iMaskBitmap,
                *bmpFile,
                bmpId,
                maskId );
            }
        else
            {
            spriteMember.iBitmap = AknIconUtils::CreateIconL( *bmpFile, bmpId );
            CleanupStack::PushL( spriteMember.iBitmap );
            }
         
        TAknWindowLineLayout l;

        switch( id )
            {
            case KAknCustomTextCursorIdLeftToRight:
            case KAknCustomTextCursorIdRightToLeft:
                l = AknLayoutScalable_Avkon::cursor_primary_pane().LayoutLine();
                break;
            case KAknCustomTextCursorIdLeftToRightThin:
            case KAknCustomTextCursorIdRightToLeftThin:
            default:
                l = AknLayoutScalable_Avkon::cursor_primary_small_pane().LayoutLine();                   
                break;
            }

        TRect rectParent = ApplicationRect();
        TAknLayoutRect layoutRect;
        layoutRect.LayoutRect( rectParent, l );
        TRect rectCursorBitmap( layoutRect.Rect() );
        TSize scaledSize(rectCursorBitmap.Width(),  rectCursorBitmap.Height() );
        
        // Perform the scaling
        AknIconUtils::SetSize( 
            spriteMember.iBitmap, 
            scaledSize, 
            EAspectRatioPreservedAndUnusedSpaceRemoved);
            
        if ( spriteMember.iMaskBitmap )
            {
            AknIconUtils::SetSize( 
                spriteMember.iMaskBitmap, 
                scaledSize, 
                EAspectRatioPreservedAndUnusedSpaceRemoved);
            }
        
        // Flags.
        TUint flags = reader.ReadUint16();
        spriteMember.iInvertMask = flags|EAknCustomTextCursorFlagInvertMask;

        // Draw mode.
        spriteMember.iDrawMode = (CGraphicsContext::TDrawMode)reader.ReadInt16();

        // Offset. Use actual scalings used. Do not read inside TPoint constructor for compiler 
        // independence.
        TInt offsetX = reader.ReadInt16(); 
        TInt offsetY = reader.ReadInt16(); 
        spriteMember.iOffset = TPoint(offsetX, offsetY);

        // Alignment.
        TInt align = reader.ReadInt16();

        // Decode the "vehicle ids" into features:
        TAknFontCategory category(EAknFontCategoryPrimary);
        TBool isRightToLeft(EFalse);

        switch( id )
            {
            case KAknCustomTextCursorIdLeftToRight:
                break;
            case KAknCustomTextCursorIdRightToLeft:
                isRightToLeft = ETrue;
                break;
            case KAknCustomTextCursorIdLeftToRightThin:
                category = EAknFontCategoryPrimarySmall;
                break;
            case KAknCustomTextCursorIdRightToLeftThin:
                category = EAknFontCategoryPrimarySmall;
                isRightToLeft = ETrue;
                break;
            default:
                // Should not get here if the resource is correct. Already initialized defaults 
                // get used.
                break;
            }

        id = AknCustomCursorSupport::CustomBidiTextCursorId( 
            category, 
            rectCursorBitmap, 
            isRightToLeft );

        // Return code is ignored since we will regularly be setting a bitmap twice
        (void)ws.SetCustomTextCursor(
            id, 
            spriteMemberArray.Array(), 
            ESpriteFlash, 
            (RWsSession::TCustomTextCursorAlignment)align);

        if (maskId != -1)
            {
            CleanupStack::PopAndDestroy(spriteMember.iMaskBitmap);
            }
        CleanupStack::PopAndDestroy(spriteMember.iBitmap);
        }

    CleanupStack::PopAndDestroy(bmpFile);
    CleanupStack::PopAndDestroy();        // reader
    }

//
// First export
//

EXPORT_C CEikServAppUi* CreateAppUi()
    {
    return new CEikServAppUi;
    }

EXPORT_C void CEikServAppUi::ActivateDisplayIfNeeded()
    {
#ifndef __WINS__

    // Check if screen saver active.
    TApaTaskList list(iCoeEnv->WsSession());
    TApaTask task = list.FindByPos(0); // topmost application
    CApaWindowGroupName* name = 0;
    TRAPD( err, name = CApaWindowGroupName::NewL(iCoeEnv->WsSession(), task.WgId()));
    if ( !err && name->AppUid() == TUid::Uid(0x100056CF) ) // Screen saver Uid
        {
        User::ResetInactivityTime();
        }
    delete name;
#endif
    }

EXPORT_C CEikServAppUiSession* CEikServAppUi::CreateSessionL( /*RThread aClient*/ )
    {
    return CAknEikServAppUiSession::NewL( /*aClient,*/ this, *this);
    }

void CEikServAppUi::Extension(TUid aExtensionUid, const TDesC8& aBuffer, RMessagePtr2 aMessage)
    {
    TBool hasCap = aMessage.HasCapability(ECapabilityWriteDeviceData); // Write Dev D required here

    if (!hasCap)
        {
        aMessage.Complete(KErrPermissionDenied);
        return;
        }

    switch(aExtensionUid.iUid)
        {
        case EAknCommonNotifierServerRunning:
            {
            aMessage.Complete(KErrNone);
            TRAP_IGNORE(
                // Do not clear the list, it can be used when common notifier server is being
                // restarted due crash.
                for (TInt i = iNotifierController->iPreloadList.Count() - 1; i >= 0; i--)
                    {
                    iNotifierController->iPreloadList[i]->PreLoadLibraryL();
                    }
                );
            break;   
            }
        case EAknNotifierControllerCmd: 
            {
            TInt cmd = static_cast<TInt>(*(aBuffer.Ptr()));
#ifdef _DEBUG
            RThread thread;
            aMessage.ClientL(thread); // ok to leave in debug mode
            TName threadName( thread.Name() );
#endif        
            if(cmd == CAknNotifierControllerUtility::EDoAllow)
                {
#ifdef _DEBUG
                
                RDebug::Print(_L("Allow all notifications: thread %S"), &threadName);      
#endif
                NotifierController()->DoAllowNotifications();
                }
            else if(cmd == CAknNotifierControllerUtility::EDoStop)
                {
#ifdef _DEBUG
                RDebug::Print(_L("Stop all notifications: thread %S"), &threadName);
#endif
                NotifierController()->DoStopNotifications();
                }
            else if(cmd == CAknNotifierControllerUtility::DoCancelAll)
                {
#ifdef _DEBUG
                RDebug::Print(_L("Cancel all notifications: thread %S"), &threadName);      
#endif
                CloseTaskList();
                NotifierController()->DoCancelAllNotificatons();
                }
            else    
                {
                if (!aMessage.IsNull())
                    {
                    aMessage.Complete(KErrNotSupported);
                    }
                return; 
                } 
    
            if (!aMessage.IsNull())
                { 
                // Release caller before forwarding to app servers.                    
                aMessage.Complete(KErrNone); 
                }
            
            NotifierController()->NotifyAppServers(cmd);
            break;
            }
        case EAknCapServerStartupComplete:
            {
            aMessage.Complete(KErrNone); // No one is listening this return value.
            TRAP_IGNORE(DoAknCapServerStartupCompleteL());
            break;  
            }
        case EAknSignalAknCapServerReady:
            {
            DoSignalWhenAknServerReady(aMessage); // Completes message when akncapserver is ready.
            break;
            }
        default:
            aMessage.Complete(KErrNotSupported);
        }
    }

/// Session within avkon code:

CAknEikServAppUiSession::CAknEikServAppUiSession(
    /* RThread aClient, */
    MEikServAppUiSessionHandler* aHandler, 
    CEikServAppUi& aAppUi )
: CEikServAppUiSession( aHandler), iAppUi(aAppUi)
    {
    }

CAknEikServAppUiSession* CAknEikServAppUiSession::NewL(
    /*RThread aClient, */
    MEikServAppUiSessionHandler* aHandler, 
    CEikServAppUi& aAppUi )
    {
    CAknEikServAppUiSession* session = new(ELeave) CAknEikServAppUiSession( 
        /*aClient,*/ 
        aHandler, 
        aAppUi);
        
    CleanupStack::PushL(session);
    session->ConstructL();
    CleanupStack::Pop();
    return session;
    }

CAknEikServAppUiSession::~CAknEikServAppUiSession()
    {
    }

void CAknEikServAppUiSession::ConstructL()
    {
    }

void CAknEikServAppUiSession::ServiceL(const RMessage2 &aMessage)
    {
    switch (aMessage.Function())
        {
        case EEikAppUiNotifyAlarmServerOfTaskChange:
            SessionHandler()->NotifyAlarmServerOfTaskChangeL();
            aMessage.Complete(KErrNone); 
            break;
        case EEikAppUiEnableTaskList:
            SessionHandler()->EnableTaskListL();
            aMessage.Complete(KErrNone);
            break;
        case EEikAppUiLaunchTaskList:
            SessionHandler()->LaunchTaskListL();
            aMessage.Complete(KErrNone);
            break;
        case EEikAppUiCycleTasks:
            {
            aMessage.Complete(KErrNone); 
            }
            break;
        case EAknEikAppUiAddToStack:
            {
            CCoeControl*temp = REINTERPRET_CAST(CCoeControl*, CONST_CAST(TAny*, aMessage.Ptr0()) );
            iAppUi.AddToStackL(temp, aMessage.Int1(), aMessage.Int2());
            aMessage.Complete(KErrNone);
            }
            break;
        case EAknEikAppUiRemoveFromStack:
            {
            CCoeControl*temp = REINTERPRET_CAST(CCoeControl*, CONST_CAST(TAny*, aMessage.Ptr0()) );
            iAppUi.RemoveFromStack(temp);
            aMessage.Complete(KErrNone);
            }
            break;
        case EAknEikAppUiShutdownApps:
            {
            aMessage.HasCapabilityL(ECapabilityPowerMgmt); // PowerMgmt required here
            TUid uid;
            uid.iUid = (REINTERPRET_CAST(TInt, CONST_CAST(TAny*, aMessage.Ptr0()) ));
            TInt timeout = REINTERPRET_CAST(TInt, CONST_CAST(TAny*, aMessage.Ptr1()) );
            
            //ShutdownAppsL must complete message.
            TRAPD(err, iAppUi.ShutdownAppsL(uid, aMessage, timeout)); 
            if (err != KErrNone)
                { 
                // Message wasn't completed.
                aMessage.Complete(err);
                }
            }
            break;
         
        default:
            {
            // It is the base class' responsibility to complete.
            // This will pick up any new opcodes added by Symbian that are
            // not yet handled here.
            CEikServAppUiSession::ServiceL(aMessage);
            break;    
            }
        }
    }
void CAknEikServAppUiSession::Write(const RMessage2& aMessage, const TAny* aPtr, const TDesC8& aDes,
    TInt anOffset)
    {
    TRAPD(ret, aMessage.WriteL( (TInt)aPtr, aDes, anOffset);)
    if (ret != KErrNone)
        {
        RThread clientThread;
        (void)aMessage.Client( clientThread); 
        clientThread.Panic(_L("CEikServAppUi server"), KErrGeneral);
        }
    }

//
// Main
//

GLDEF_C TInt PanicNoteThreadFunction( TAny* /*aParameters*/ )
    {
    return KErrNone;
    }
    
// Probably obsolete, but just in case, Fix Me !!
EXPORT_C void CEikServAppUi::HideApplicationFromFswL(TInt aUid,TBool aDisable)
    {
    iAknCapServerClient.HideApplicationFromFsw(aDisable, aUid);
    }

// Start new notifier server plugin using fixed server differentiator.
void StartNotifierAppServerL(TUid aAppServerUid)
    {
    RApaLsSession apa;
    User::LeaveIfError(apa.Connect());
    CleanupClosePushL(apa);

    TApaAppInfo info;
    
    TInt err(0);
    for(TInt i = 20;
        ((err = apa.GetAppInfo(info, aAppServerUid)) == RApaLsSession::EAppListInvalid) && i > 0;
        i--)
        {
        User::After(500000);    
        }

    User::LeaveIfError(err);

    CApaCommandLine* cmdLine = CApaCommandLine::NewLC();
    cmdLine->SetExecutableNameL(info.iFullName);
    cmdLine->SetServerRequiredL(KUikonUidPluginInterfaceNotifiers);
    cmdLine->SetCommandL(EApaCommandBackground);
    TThreadId dummy;
    User::LeaveIfError(apa.StartApp(*cmdLine, dummy));

    CleanupStack::PopAndDestroy(2, &apa);   // cmdLine and apa
    }

TBool StartNotifierAppServer(TAny* aAny)
    {
    // Resolve uid.
    CEikServAppUi* appUI = (CEikServAppUi*)aAny;
    TUid serverUid = appUI->NextNotifierServerUid();  

    // Check if the aknnfysrv.exe is running, perventing for dropping into
    // an infinite loop of launching aknnfysrv.exe
    if (serverUid == KCommonNotifierAppSrvUid)
        {
        TFullName serverName;
        serverName.Format(_L("%08x_%08x_AppServer"), KUikonUidPluginInterfaceNotifiers, KCommonNotifierAppSrvUid);
        TFindServer find(serverName);
        TFullName fullName;
        if (find.Next(fullName) == KErrNone)
            {
            // Aknnfysrv.exe is already running, so just return.
            return EFalse;
            }    
        }

    if (serverUid != KNullUid)
        {
        TRAP_IGNORE(StartNotifierAppServerL(serverUid))
        }

    return EFalse; // do not call back again 
    }

EXPORT_C void CEikServAppUi::StartNewServerApplicationL(TUid aAppServerUid)
    {
    // Add to queue.   
    if (iNotifServerAppQueue.Find(aAppServerUid.iUid) == KErrNotFound)
        {
        iNotifServerAppQueue.AppendL(aAppServerUid.iUid);    
        }

    // Start idler if does not exist (if only akncapserver is already running).
    if (!iIdler && iAknCapServerClient.Handle() != 0)
        {
        iIdler = CIdle::NewL(CActive::EPriorityHigh);
        iIdler->Start(TCallBack(StartNotifierAppServer, this));
        }
    }
    
TUid CEikServAppUi::NextNotifierServerUid()
    {
    TInt uid = 0;

    delete iIdler;
    iIdler = 0;

    if (iNotifServerAppQueue.Count()) 
        {
        uid = iNotifServerAppQueue[0];
        iNotifServerAppQueue.Remove(0);
        }    

    // Activate idler for next uid.
    if (iNotifServerAppQueue.Count()) 
        {
        // We must trap this call, if creating a new CIdle fails, no applications will be started 
        // from queue until new request comes.
        TRAPD(err, iIdler = CIdle::NewL(CActive::EPriorityHigh))
        if (!err)
            {
            iIdler->Start(TCallBack(StartNotifierAppServer, this));
            }
        }
     else
        { 
        // Last notifier app server is being launched, free starter.
        if (!iAknCapServerMessage.IsNull())
            {
            iAknCapServerMessage.Complete(KErrNone);
            }
        }
        
    // Return uid of topmost.
    return TUid::Uid(uid);  
    }
    
void CEikServAppUi::UpdateCursorsL() 
    {
    LoadBitmapCursorsL();
    }

TInt DoPollCapServer(TAny* appui)
    {
    _LIT(KServerNameFormat, "%08x_%08x_AppServer");
    TFullName serverName;
    serverName.Format(KServerNameFormat, KUikonUidPluginInterfaceNotifiers, KAknCapServerUid.iUid);
    TFindServer find(serverName);
    TFullName fullName;
    ((CEikServAppUi*)appui)->AknCapServerStartupComplete(find.Next(fullName) == KErrNone);
    return KErrNone;
    }

// We are doing this on startup when there is always enough memory, so methods with L really 
// can't leave.
void CEikServAppUi::AknCapServerStartupComplete(TBool aComplete)
    {
    delete iIdler;
    iIdler = 0;

    if (aComplete)
        {
        // In this phase of boot, create real connection to akncapserver.
        iAknCapServerClient.DoEikonServerConnect();           
        
        // Create alarm server as we have capserver running.
        TRAPD(err, DoAlarmServerStartupL());
        
        // No use to startup phone if this fails.
        __ASSERT_ALWAYS(!err, User::Invariant()); 
        
        iIdler = CIdle::NewL(CActive::EPriorityHigh);
        iIdler->Start(TCallBack(StartNotifierAppServer, this));
        }
    else
        {
        const TInt waitDelay = 200000;  // 0.2 seconds
        User::After(waitDelay);
        DoAknCapServerStartupCompleteL();
        }
    }

void CEikServAppUi::DoAknCapServerStartupCompleteL()
    {
    __ASSERT_DEBUG(iIdler == 0, User::Invariant());

    iIdler = CIdle::NewL(CActive::EPriorityIdle);
    iIdler->Start(TCallBack(DoPollCapServer, this));
    }
    
void CEikServAppUi::DoSignalWhenAknServerReady(const RMessagePtr2& aMessage)
    {
    if (iAknCapServerClient.Handle() != 0)
        {
        aMessage.Complete(KErrNone);
        }
        
    // This should be used as single shot.
    __ASSERT_DEBUG(iAknCapServerMessage.IsNull(), User::Invariant());   
    iAknCapServerMessage = aMessage;
    }

void CEikServAppUi::DoAlarmServerStartupL()
    {
    // Stupid naming, perhaps.
    iAlarmAlertServer = CEikServAlarmAlertServer::NewL(this);

    // Start AlarmServer.
    TInt err = AlarmClientUtils::StartAlarmServer();
    if (err != KErrNone && err != KErrAlreadyExists)
        {
        User::Leave(err);
        }

    HandleSwitchOnEventL( NULL );    
    }

// End of file
