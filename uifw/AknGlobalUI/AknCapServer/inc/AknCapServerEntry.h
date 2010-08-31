/*
* Copyright (c) 2005-2008 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef __AKNCAPSERVERENTRY__
#define __AKNCAPSERVERENTRY__

#include <AknNotiferAppServerApplication.h> // link against AknNotifierWrapper.lib
#include <AknNotifierAppServer.h>
#include <AknSgcc.h>
#include <AknNotifierControllerPlugin.h>
#include <akneiksrvc.h>
#include <akndialogcontroller.h>
#include <e32property.h>
#ifdef RD_INTELLIGENT_TEXT_INPUT
#include <centralrepository.h>
#include <PtiDefs.h>
#endif

#include "AknEikSgcs.h"
#include "AknNotiferAppServerApplicationInterface.h"
#include "AknCapServerDefs.h"
#include "aknblankwin.h"
#include "AknFastswapWindowControl.h"
#include "aknphonekeyforwarder.h"
  
const TInt KAknInternalFSWClose(0);

class CPtiEngine;
class CAknCapServer;

struct SSuppressInfo
    {
    SSuppressInfo(TInt aUid):iUid(aUid),iReferenceCount(0){}
    TInt iUid;
    TInt iReferenceCount;       
    };

class CAknServKeyFilter;
class CAknFastSwapWindowControl;
class CAknMMCPasswordRequester;
class CWindowChangeMonitor;
class MAknMessageReaderLongPressDetector;
class CAknCapAppServerAlternateFs;

//----------------------------------
// PubSub key listener.
//----------------------------------
NONSHARABLE_CLASS(CPropertySubscriber) : public CActive
    {
public:
    CPropertySubscriber(TCallBack aCallBack, RProperty& aProperty);
    virtual ~CPropertySubscriber();

public: // New functions
    void Subscribe();
    void StopSubscribe();

private: // from CActive
    void RunL();
    void DoCancel();

private:
    TCallBack   iCallBack;
    RProperty&  iProperty;
    };

//----------------------------------
// Application
//----------------------------------
class CAknCapServerApplication : public CAknNotifierAppServerApplication
    {
public:
    CAknCapServerApplication();
    void NewAppServerL(CApaAppServer*& aAppServer);
    CApaDocument* CreateDocumentL();
    TUid AppDllUid() const 
        {
        return KAknCapServerUid;    
        }
    TFileName ResourceFileName() const
        {
        return KNullDesC();            
        }
    CAknCapServer* CapServer() const
        {
        return iCapServer;
        }
private:
    CAknCapServer* iCapServer;
    };

//----------------------------------
// Document
//----------------------------------
class CAknCapAppServerDocument : public CAknDocument
    {
public:
    CAknCapAppServerDocument(CEikApplication& aApp):CAknDocument(aApp), iApp(&aApp){};
private: // from CAknDocument
    CEikAppUi* CreateAppUiL();
    CEikApplication* iApp;
    };

//----------------------------------
// AppUi
//----------------------------------
class CAknCapAppServerAppUi : 
    public CAknNotifierAppServerAppUi, 
    public MAknCapServerInterface,
    MAknAliasKeyCodeResolver, 
    MAknPhoneKeyForwarder
    {
public:
    CAknCapAppServerAppUi( CAknCapServer* aCapServer );
    ~CAknCapAppServerAppUi();
    
public: //from CAknNotifierAppServerAppUi
    void ConstructL();
    TKeyResponse HandleKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
    
public: // from CCoeAppUi
    void HandleResourceChangeL(TInt aType);
    
private: // from CCoeAppUi
    void HandleWsEventL(const TWsEvent& aEvent,CCoeControl* aDestination);

public: // new methods  
#ifdef RD_INTELLIGENT_TEXT_INPUT
    TBool IsCharacterCategoryNumber(TUint aChar) const;
#endif
    void SuppressAppSwitchingL(TInt aAddCount, TInt aClientId);
    void KillAppL(const RMessage2& aMessage);
    void DoTaskListCommandL(const RMessage2& aMessage);
    void HideApplicationFromFswL(TInt aUid, TBool aHide);    
    TBool HiddenFromFSW( TInt aUid );
    TInt EnableTaskList(TBool aEnable);
    TBool HandleShortAppsKeyPressL(); // return true if event used
    TBool HandleLongAppsKeyPressL(); // "
    TBool IsAppsKeySuppressed();
    
    CAknMMCPasswordRequester* MMCUnlock()
        {
        return iMMCUnlock;
        } 
    
    CEikSgcServer* SgcServer()
        {
        return iSgcs; 
        }
        
    void SetStatusPaneFlags(TInt aFlags);   
    void SetStatusPaneLayoutL(TInt aLayoutResId);
    virtual void BlankScreenL(TBool aBlank, TBool aToForeground = EFalse);
    void SwapLayoutSwitchBlankScreenL();
    void SetCurrentAppStatuspaneResourceIdL(TInt aResourceId);
    TInt CurrentAppStatuspaneResourceIdL();
    virtual TBool IsDisplayingForegroundBlankScreen() const;
    void RotateScreenL();
    TInt UpdateTaskListL( TBool aTaskListRefreshNeeded );
    void SetFgSpDataSubscriberIdL(TInt aId);
    
    void CloseFSW();
    // set/get whether idle is active
    virtual void SetIdleActive( TBool bActive );
    virtual TBool IsIdelActive( );
    
    void SetIsShortTimeGlobalNoteDisplaying(TBool aShortTimeGlobalNoteDisplaying)
        {
        iShortTimeGlobalNoteDisplaying = aShortTimeGlobalNoteDisplaying;
        }
    
    TBool IsShortTimeGlobalNoteDisplaying()
        {
        return iShortTimeGlobalNoteDisplaying;
        }
    
private:
    void PublishHiddenList();
    void PublishInstalledLanguagesL();
    static TInt GlobalNotesAllowedCallBack(TAny* aPtr);
    void HandlePropertyChange(const TInt aProperty);
    void ProcessInitFlipStatus();
    void InitiateOFNStatus();
    void LoadAlternateFsPlugin();
    void ShowOrDismissAlternateFs();

public: 
    /**
     * From MAknAliasKeyCodeResolver.
     * Resolves keyboard layout dependent keycode for the given event.
     *
     * @since Series 60 3.1
     * @param aCode Reference to variable to contain new keycode. 
     * @param aKeyEvent Reference to original, complete, event.
     * @param aType Indicating original event type.
     * @return KErrNone on success, otherwise system wide error codes.
     */
    TInt GetAliasKeyCode(TUint& aCode, const TKeyEvent& aKeyEvent,TEventCode aType);        
    
private:
    RArray<SSuppressInfo> iAppsKeyArray;
    CArrayFixFlat<TInt>* iHiddenList; 
    CAknServKeyFilter* iKeyCaptureControl;
    TBool iTaskListEnabled;
    CAknFastSwapWindowControl* iFSControl;
    TInt iResourceFileOffset; // for eiksrvui.rsc
    CAknMMCPasswordRequester* iMMCUnlock;
    CEikSgcServer* iSgcs;
    TInt iBlankWinRefCount;
    CAknServBlankWin* iBlankWin;
    RWindowGroup iBackdropWindowGroup;
    CEikServStatusPane* iStatusPane;
    TBool iForegroundBlankScreen;
    CAknCapServer* iCapServer;
    
    TBool iShortTimeGlobalNoteDisplaying;
    CAknCapAppServerAlternateFs* iAlternateFS;

public: // startup scheduling  
    CIdle* iIdler;
    TBool iHasRunOnce;
    CPtiEngine* iPtiEngine;
    TBool iQwertyStatus;

public:
    MAknKeyLockObserver* iGlobalNotesController;
    RAknEikAppUiSession iEikSrv;

public:
    MAknMessageReaderLongPressDetector* iMessageReaderLongPressDetector;
    
public: // phone key event forwarding 
    MAknPhoneKeyForwarder* AsKeyForwarder()
        {
        return this;
        }
   
    void ForwardKeyToPhoneAppL(const TKeyEvent& aKeyEvent);    
    void PhoneKeyUpReceived();
               
    TKeyEvent iPhoneKey;
    TInt iScanCodeCaptureHandle;
    TBool iUpReceived;

    /** Id of the client thread for global note cancelling. */
    TThreadId iClientId;

private:
    RProperty iGlobalNotesAllowedProperty;
    CPropertySubscriber* iGlobalNotesAllowedSubscriber;
    
    TBool iIdleActive;
    };

#endif // __AKNCAPSERVERENTRY__

// End of file
