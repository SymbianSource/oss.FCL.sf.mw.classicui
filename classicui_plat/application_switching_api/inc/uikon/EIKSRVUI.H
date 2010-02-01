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

#ifndef __EIKSRVUI_H__
#define __EIKSRVUI_H__

#include <eiksrv.h>
#include <eikenv.h>
#include <apgtask.h>
#include <uikon/eiksvfty.h>
#include <aknappui.h>
#include <eiksrvsp.h>
#include <eikcycledef.h>
#include <AknNotifierControllerPlugin.h>

#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eiknotifyalert.h>
#endif


GLREF_C TInt PanicNoteThreadFunction(TAny* aParameters);

class CEikServNotifyServer;
class CEikServBackupServer;
class CEikServAlarmAlertServer;
class CEikKeyWindow;
class CEikUndertaker;
class CAknFastSwapWindowControl;
class RAknAnimKeySound;
class CAknKeySoundSystem;
class MAknKeyLockController;
class CNotifierDialogController;
class CEikServKeyFilter;
class CEikServAppUiBase;
class CEikServBlankWin;
class CAknEikServAppUiSession;
class CEikServExtra;
class CEikServAppStarter;

// =================
// CEikServAppUiBase
// =================

class CEikServAppUiBase : 
    public CAknAppUiBase, 
    public MEikUndertakerObserver, 
    public MEikServAppUiSessionHandler
    {
public:
    enum TEikServServers { EAlwlSvr = 0x01, EApaSvr = 0x02, EBackupSvr = 0x04 };
    enum TEikSrvShutdownState { EShutdownWaitingForApps = 0, EShutdownKillingRogueApps };
public:
    IMPORT_C static CEikServAppUiBase* NewLC();
    IMPORT_C ~CEikServAppUiBase();

    // From MEikServAppUiSessionHandler
    IMPORT_C void NotifyAlarmServerOfTaskChangeL();
    IMPORT_C virtual void EnableTaskListL();
    IMPORT_C virtual void LaunchTaskListL();
    IMPORT_C void CycleTasksL(enum TTaskCycleDirection aDirection);
    IMPORT_C void SetStatusPaneFlags(TInt aFlags);
    IMPORT_C void SetStatusPaneLayoutL(TInt aLayoutResId);
    void Extension(TUid aExtensionUid,const TDesC8& aBuffer, RMessagePtr2 aMessage);

    IMPORT_C virtual void BlankScreenL();
    IMPORT_C virtual void UnblankScreen();

    IMPORT_C void ShutdownAppsL(
        const TUid aRequesterUID, 
        const RMessage2& aShutdownMessage, 
        const TInt aTimeoutInMicroseconds);
        
    IMPORT_C void HandleForegroundEventL(TBool aForeground);
    void SetSgcParamsL(TInt aWgId, TBitFlags aFullScreen, TInt aSpLayout, TInt aSpFlags);
    void PrepareForAppExitL(TInt aWgId);

public:
    inline RWindowGroup& AlertGroupWin() const;
    IMPORT_C void BringAlertGroupWinForwards(TBool aForwards);

protected:
    IMPORT_C void ConstructL();
    IMPORT_C void InitializeL(TEikServCtrlFactories& aCtrlFactories);
    IMPORT_C CEikServAppUiBase();
    IMPORT_C void HandleWsEventL(const TWsEvent& aEvent, CCoeControl* aDestination);
    
protected: // from MEikUndertakerObserver
    IMPORT_C void HandleThreadExitL(RThread& aThread);
    
private: // framework
    IMPORT_C void HandleSystemEventL(const TWsEvent& aEvent);
    IMPORT_C void HandleApplicationSpecificEventL(TInt aType, const TWsEvent& aEvent);
    IMPORT_C TKeyResponse HandleKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
    IMPORT_C void HandleSwitchOnEventL(CCoeControl* aDestination);
    
protected:
    IMPORT_C void HandleResourceChangeL(TInt aType);
    
private: // specific
    void SetSystemTime() const;
    static TInt RestartServerCallback(TAny* aObj);
    static TInt StartNotifierServerCallBackL(TAny* aPtr);
    void RestartServer();

protected:
    RWindowGroup iAlertGroupWin;
    TInt iAlertGroupForwardsCount;
    TInt iResourceFileOffset;
    CEikServNotifyServer* iNotifyServer;
    CEikServBackupServer* iBackupRestoreServer;
    CEikServAlarmAlertServer* iAlarmAlertServer;
    CEikUndertaker* iUndertaker;
    RWindowGroup iBackdropWindowGroup;
    CEikServStatusPane* iStatusPane;
    CEikServBlankWin* iBlankWin;
    TInt iBlankWinRefCount;
    RMessagePtr2 iReservedMessage; //ShutdownMessage;
    
private:
    CEikServExtra* iEikServExtra;
    TInt iServerToRestart;
    CEikServAppStarter* iAppStarter;
    CVwsSessionWrapper* iVwsSession;
    };

inline RWindowGroup& CEikServAppUiBase::AlertGroupWin() const
    { 
    return((RWindowGroup&)iAlertGroupWin); 
    }
      
// =============
// CEikServAppUi
// =============

NONSHARABLE_CLASS(CEikServAppUi) : 
    public CEikServAppUiBase, 
    public MEikServAlarmFactory, 
    public MEikServAppUiSessionFactory
    {
public:
    enum TTaskCycleDirection { EBackwards, EForwards };
    enum TEikServServers { EAlwlSvr = 0x01, EApaSvr = 0x02 };
    
public:
    CEikServAppUi();
    ~CEikServAppUi();
    void ConstructL();
    void HandleThreadExitL(RThread& aThread);
    void HandleTaskListExitL();
    
public: // from CEikServAppUiBase
    void EnableTaskListL();
    void LaunchTaskListL();
    void CloseTaskList();
    TInt VisibleWindowGroupsCountL();
    IMPORT_C void SuppressAppSwitching(TBool aSuppress);
    IMPORT_C void ActivateDisplayIfNeeded();
    void SetStatusPaneFlags(TInt aFlags);
    void SetStatusPaneLayoutL(TInt aLayoutResId);
    void BlankScreenL();
    void UnblankScreen();

private: // from CCoeAppUiBase
    void HandleWsEventL(const TWsEvent& aEvent, CCoeControl* aDestination);
    
private: // from CCoeAppUi
    void HandleSystemEventL(const TWsEvent& aEvent);
    TKeyResponse HandleKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
    void HandleSwitchOnEventL(CCoeControl* aDestination);
    void HandleResourceChangeL(TInt aType);
    
private: // from MEikServAlarmFactory
    MEikServAlarm* NewAlarmL(CEikAlmControlSupervisor& aSupervisor);
    
private: // specific
    void EnsureExternalKeyHandlerAppStreamExistsL();
    void UpdateTaskListL();
    void HandleErrorMessageEvent(const TWsErrorMessage& aErrorMessage);
    void HandleOomEvent();
    void HandleBacklightError(TInt aError);
    void HandleWservLoggingError(TInt aError);
    HBufC* ConstructPanicTextLC(RThread& aThread, TBool aRDSupport) const;
    void RestartKeySoundThreadL();
    void LoadBitmapCursorsL();
    void UpdateCursorsL();
    
private:
    friend class CEikServKeyFilter;
    
private:
    TInt32 iExternalKeys[3];
    TInt32 iScreenCaptureKey;
    TInt32 iHelpKey;
    TInt32 spare; // was iHomekey, remove

    RWindowGroup iOffScreenGroupWin;
    CEikKeyWindow* iSidebarWindow;
    CEikKeyWindow* iAppbarWindow;
    TInt iResourceFileOffset;

    CEikServKeyFilter* iFilter;

    TBool iExternalKeyHandlerRunning;
    TThreadId iExternalKeyHandlerThreadId;

    TBool iHelpAppRunning;
    TThreadId iHelpAppThreadId;
    TThreadId iKeySoundThreadId;

    RAnimDll* iAknAnimDll;
    RAknAnimKeySound* iAknAnimKeySound;
    
public:
    // Accessed from notifiers
    MAknKeyLockController* iKeyLockController; // obsolete, to be removed. Fix Me !!
    CNotifierDialogController* iNotifierDialogController;

public:
    // From MEikServAppUiSessionFactory
    IMPORT_C CEikServAppUiSession* CreateSessionL();

private:
    // eiksrv session handler
    CAknEikServAppUiSession* iSession;
    
public:
    // check and remove if obsolete
    IMPORT_C void HideApplicationFromFswL(TInt aUid, TBool aDisable);

public: // new notifier fw
    IMPORT_C void StartNewServerApplicationL(TUid aAppServerUid);
    
    CAknNotifierController* NotifierController()
        {
        return iNotifierController;
        }
        
    TUid NextNotifierServerUid();    

    void DoAknCapServerStartupCompleteL();
    void DoSignalWhenAknServerReady(const RMessagePtr2& aMessage);
    void AknCapServerStartupComplete(TBool aComplete);

private: // from MEikServAppUiSessionHandler
    void Extension(TUid aExtensionUid, const TDesC8& aBuffer, RMessagePtr2 aMessage);

private:
    RArray<TInt> iNotifServerAppQueue;
    CIdle* iIdler;
    CAknNotifierController* iNotifierController;

    RMessagePtr2 iAknCapServerMessage;
    void DoAlarmServerStartupL();
    };

// =======================
// CAknEikServAppUiSession
// =======================

class CAknEikServAppUiSession : public CEikServAppUiSession
    {
public:
    static CAknEikServAppUiSession* NewL(
        MEikServAppUiSessionHandler* aHandler, 
        CEikServAppUi& iAppUi);
        
    ~CAknEikServAppUiSession();

private:
    void ConstructL();
    CAknEikServAppUiSession(MEikServAppUiSessionHandler* aHandler, CEikServAppUi& iAppUi );
    void ServiceL(const RMessage2 &aMessage);
    void Write(const RMessage2& aMessage, const TAny* aPtr, const TDesC8& aDes, TInt anOffset);
    
private:
    CEikServAppUi& iAppUi; // Non-const. Many non-const methods will be called on this.
    };

#endif // __EIKSRVUI_H__
