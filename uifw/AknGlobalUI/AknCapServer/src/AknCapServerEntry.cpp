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

#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikdefconst.h>
#include <uikon/eikenvinterface.h>
#endif
#include <e32uid.h>
#include <eikstart.h>
#include <AknDef.h>
#include <barsread.h>
#include <bautils.h>
#include <e32std.h>
#include <e32property.h>
#include <UikonInternalPSKeys.h>     // KUikLayoutState, KPSUidUikon, KUikAppHiddenList
#include <AknFepInternalCRKeys.h>    // KAknFepHashKeySelection, KAknFepEditTextSubmenu
#ifdef RD_INTELLIGENT_TEXT_INPUT
#include <AknFepInternalPSKeys.h>    // KAknFepFnKeyState
#endif
#include "avkoninternalpskeys.h"     // KAknIdleAppWindowGroupId
#include <AknCapServerDefs.h>
#include <eikpriv.rsg>
#include <coedef.h>
#include <eiksvdef.h>
#include <aknconsts.h>
#include <AknsConstants.h>
#include <apgwgnam.h>

#include "AknCapServerDefs.h"
#include "AknCapServerEntry.h"
#include "AknCapServer.h"
#include "AknFastswapWindowControl.h"
#include "AknMemoryCardDialogImpl.h"
#include "oommonitor.h"
#include "AknKeyFilter.h"
#include <AknWsEventObserver.h>

#include <PtiEngine.h>
#include <PtiKeyMappings.h>
#include <PtiDefs.h>

// For Gs to initiate OFN status
#include <settingsinternalcrkeys.h>

#include <aknenv.h>
#include <AknSettingCache.h>
#include <eikspane.h>
#include "aknstatuspanedatapublisher.h"

#include <syslangutil.h> // SysLangUtil::GetInstalledLanguages
#include <featmgr.h>
#include <centralrepository.h>
#include "aknmessagereaderlongpressdetector.h" // MAknMessageReaderLongPressDetector

#include <akncapserveralternatefsplugin.h>
#include <akncapserveralternatefspluginconst.hrh>

#ifdef RD_UI_TRANSITION_EFFECTS_LAYOUT_SWITCH
    #include <gfxtranseffect/gfxtranseffect.h>
    #include <akntranseffect.h> // for Transition effect enumerations
#endif


#ifdef RD_INTELLIGENT_TEXT_INPUT
#include <AvkonInternalCRKeys.h>

#include "akncapserverdiscreetpopuphandler.h"

const TUid KPtiEnginePSUid = {0x101F8610}; // Same as PtiEngine dll
const TUid KPhoneUid = { 0x100058B3 };
enum TPtiEnginePSKeys
    {
    EKeyMapPropertyCount,
    EKeyMapPropertyData,
    EKeyMapPropertyCount2,
    EKeyMapPropertyData2,    
    EKeyMapPropertyCount3,
    EKeyMapPropertyData3        
    };

 // Read capability: AlwaysPass.
_LIT_SECURITY_POLICY_PASS( KCapServerPtiEngineAlwaysPass );    
_LIT_SECURITY_POLICY_S1( KCapServerPtiEngineWritePolicy, 0x10207218, ECapabilityWriteDeviceData);  
#endif

// External keyboard modifier
const TUint KModifierExternalKeyboard = 0x00200000;

const TInt KWgPriorityCoverEverything = 10000;
const TInt KKeyEventICodeThreshold = 0x001f;
const TInt KMaxLanguageCodeLength = 6; // 5 digits + separator

                

_LIT(KEikSrvUIResFileName, "z:\\resource\\eiksrvui.rsc");
_LIT_SECURITY_POLICY_PASS(KPassReadPolicy);
_LIT_SECURITY_POLICY_C1(KWriteDDPolicy, ECapabilityWriteDeviceData);
_LIT_SECURITY_POLICY_C1(KReadPolicy,    ECapability_None);
_LIT( KSeparator, " " );

CAknCapServerApplication::CAknCapServerApplication()
    {
    }

void CAknCapServerApplication::NewAppServerL(CApaAppServer*& aAppServer)
    {
    CAknCapServer* server = new (ELeave) CAknCapServer();
    
    CleanupStack::PushL(server);
    server->CreateDynamicSoftNoteEventManagerL();
    CleanupStack::Pop(server);    
    
    server->SetPriority(EActivePriorityIpcEventsHigh);
    aAppServer=&*server;
    iCapServer = server;
    }
    
CApaDocument* CAknCapServerApplication::CreateDocumentL()
    {
    return new (ELeave) CAknCapAppServerDocument(*this);
    }

CEikAppUi* CAknCapAppServerDocument::CreateAppUiL()
    {
    CAknCapServerApplication* app = static_cast<CAknCapServerApplication*>(iApp);
    CAknCapServer* server = app->CapServer();
    CAknCapAppServerAppUi* ret = new (ELeave) CAknCapAppServerAppUi( server );
    return ret;
    }

CAknCapAppServerAppUi::CAknCapAppServerAppUi( CAknCapServer* aCapServer ) : iCapServer( aCapServer )
    {
    iIdleActive = ETrue;
    }
    
CAknCapAppServerAppUi::~CAknCapAppServerAppUi()
    {
    delete iAlternateFS;
    delete iGlobalNotesAllowedSubscriber;
    
    if (iKeyCaptureControl)
        {
        RemoveFromStack(iKeyCaptureControl);   // ownership in stack 
        }
        
    delete iFSControl;
    
    if (iResourceFileOffset)
        {
        iCoeEnv->DeleteResourceFile(iResourceFileOffset);   
        }
    
    delete iHiddenList;
    delete iMMCUnlock;
    delete iIdler;
    iEikSrv.Close(); // this shouldn't be connected here anyway
    delete iPtiEngine;          
    }

_LIT(KProductSpecificHalFile, "z:\\system\\data\\ProductSpecificHalParams.txt");

void DoProductSpecificHalFunction()
    {
    RFs& fs = CCoeEnv::Static()->FsSession();
    RFile file;
    if (fs.Handle() && file.Open(fs,KProductSpecificHalFile, EFileRead)==KErrNone)
        {
        TBuf8<30> desc;
        file.Read(desc);
        TLex8 lex(desc);
        TInt i[4];
        TInt ii = 0;
        for (;ii < 4; ii++)
            {
            if (lex.Val(i[ii]))
                {
                ii = KErrArgument;
                break;
                }
            lex.SkipSpace();
            }
        if (ii != KErrArgument)
            {
            UserSvr::HalFunction(i[0], i[1], &i[2], &i[3]);         
            }
        file.Close();
        }
    }

TInt StartOOM(TAny* aThis)
    {
    // By running idle priority active object twice, we allow idle priority objects
    // scheduled after AppUi::ConstructL() run at least once.
    CAknCapAppServerAppUi* me = (CAknCapAppServerAppUi*)aThis;
    if (!me->iHasRunOnce)
        {
        DoProductSpecificHalFunction();
        
        me->iHasRunOnce = ETrue;        
        me->iIdler->Start(TCallBack(StartOOM, aThis));
        return KErrNone;
        }
    
    // free resources of idler
    delete me->iIdler;
    me->iIdler = 0;
    
    // do the actual startup
    TRAPD( err, CreateOOMWatcherThreadL());
    // we panic here if something goes wrong as startup will fail anyway.
    __ASSERT_ALWAYS(err==KErrNone, User::Invariant());

    me->iEikSrv.AllowNotifierAppServersToLoad();
    me->iEikSrv.Close(); // currently there is no use to keep this session alive.

#ifdef SYMBIAN_BUILD_GCE
    const TInt KOOMWatcherDllUid = 0x10282DBF;
    _LIT(KOOMWatcherDll, "goommonitor.dll");

    RLibrary lib; // we don't need to push to stack because there is no leaving in following operations.
    TUidType uidType(KDynamicLibraryUid, KSharedLibraryUid, TUid::Uid(KOOMWatcherDllUid));

    err = lib.Load(KOOMWatcherDll, uidType);
    if (KErrNone == err)
        {
        TLibraryFunction func = lib.Lookup(2); /* CreateGOOMWatcherThreadL */
        if (func)
            {
            TRAP(err, (*func)());
            if (err != KErrNone)
                {
                RDebug::Print(_L("Creating out of graphics mem thread in capserver failed with err %d"), err);
                }
            }
        else
            {
            RDebug::Print(_L("Lookup function entry in goommonitor.dll return NULL, the entry number may be wrong!"));
            }
        }
    else
        {
        RDebug::Print(_L("Dynamically Loading goommonitor.dll failed with err %d, it's ok!"), err);
        }
#endif 

    return err;
    }

void CAknCapAppServerAppUi::LoadAlternateFsPlugin()
    {
    // List all plugins
    RImplInfoPtrArray implInfoArray;
    TRAPD( error, REComSession::ListImplementationsL(
        TUid::Uid( KAknCapServerAlternateFsPluginInterfaceUid ), implInfoArray ) );
    
    if ( error == KErrNone && implInfoArray.Count() )
        {
        TUid uid = implInfoArray[0]->ImplementationUid();
        TRAP_IGNORE( iAlternateFS = CAknCapAppServerAlternateFs::NewL( uid ) );
        }
    
    implInfoArray.ResetAndDestroy();
    }

void CAknCapAppServerAppUi::ShowOrDismissAlternateFs()
    {
    if ( !iAlternateFS )
        {
        return;
        }
    
    if ( iAlternateFS->IsVisible() )
        {
        iAlternateFS->HandleLongAppKeyPress();
        }
    else
        {
        iAlternateFS->Show();
        }
    }

void CAknCapAppServerAppUi::ConstructL()
    {
    User::SetCritical(User::ESystemCritical);

    InitiateOFNStatus();

    // install default FEP if none set before
    if (iEikonEnv->FepUid() == KNullUid)
        {
        iEikonEnv->InstallFepL(TUid::Uid(0x101FD65A));
        }
    
    // define and set the PS key listing installed languages
    PublishInstalledLanguagesL();

    TInt value = 1;
    if ( FeatureManager::FeatureSupported( KFeatureIdEditKey ) )
        {
        // The edit key exists in the device. Hash-key selection disabled and
        // edit text sub-menu removed from the options menu
        value = 0;
        }
    CRepository* repository = CRepository::NewL(KCRUidAknFep);
    // Return value of repository->Set() ignored.
    repository->Set(KAknFepHashKeySelection, value);
    repository->Set(KAknFepEditTextSubmenu, value);
    delete repository;
    repository = NULL;
    
    // kick eikon server in (in case it is not running yet)
    TInt error = iEikSrv.Connect();
    __ASSERT_ALWAYS(error == KErrNone, User::Invariant());
    
    // base call
    CAknNotifierAppServerAppUi::ConstructL();

    RWsSession& wsSession=iEikonEnv->WsSession();
    iBackdropWindowGroup=RWindowGroup(wsSession);
    User::LeaveIfError(iBackdropWindowGroup.Construct((TUint32)&iBackdropWindowGroup, EFalse));
    iBackdropWindowGroup.AutoForeground(EFalse);
    
    CApaWindowGroupName* apaName = 
        CApaWindowGroupName::NewLC(wsSession, (TUint32)&iBackdropWindowGroup);
        
    apaName->SetHidden(ETrue);
    apaName->SetSystem(ETrue); 

    apaName->SetCaptionL(EIKON_SERVER_BACKDROP_WINDOW_GROUP_NAME);
    User::LeaveIfError(apaName->SetWindowGroupName(iBackdropWindowGroup));
    CleanupStack::PopAndDestroy(); //apaName
    iBackdropWindowGroup.SetOrdinalPosition(1, ECoeWinPriorityNormal);

    // to make sure that wserv does not change our priority even we lose foreground
    wsSession.ComputeMode(RWsSession::EPriorityControlDisabled);

    wsSession.SetDoubleClick(KTimeBetweenClicks,KDoubleClickDistance);
    
    // AKNLAF
    wsSession.SetKeyboardRepeatRate(KAknKeyboardRepeatInitialDelay, KAknStandardKeyboardRepeatRate); 
 
    // Disable some of wserv hotkeys if not in RnD mode.
    if (!BaflUtils::FileExists( iEikonEnv->FsSession(), KRDSupport ))
        {
        User::LeaveIfError(wsSession.ClearHotKeys(EHotKeyOfDeath));
        // Symbian already protects this in urel mode, but just to play it safe  
        User::LeaveIfError(wsSession.ClearHotKeys(EHotKeyShutDown)); 
        User::LeaveIfError(wsSession.ClearHotKeys(EHotKeyOff));       
        }

    // Create statuspane & SGcs
    if (iEikonEnv->StatusPaneCoreResId())
        {
        iStatusPane = CEikServStatusPane::NewL(
            *iEikonEnv, 
            &iBackdropWindowGroup, 
            iEikonEnv->StatusPaneCoreResId());
        }

    iSgcs = CEikSgcServer::NewL();
    iSgcs->SetStatusPane(iStatusPane);
    iSgcs->SetAknCapAppServerAppUi(this);
    
    RWindowGroup& rootWin = iCoeEnv->RootWin();
    rootWin.EnableGroupListChangeEvents();
    rootWin.EnableScreenChangeEvents();
    rootWin.EnableFocusChangeEvents (); // For cover UI/status pane refresh problems

    iSgcs->HandleWindowGroupParamChangeL(rootWin.Identifier(), EFalse, 0, 0, KAknScreenModeUnset);

    // create a high priority key filter
    // i.e. capture Apps-Key
    iKeyCaptureControl=new(ELeave) CAknServKeyFilter();
    iKeyCaptureControl->ConstructL(*this);

    TFileName fileName(KEikSrvUIResFileName);
    BaflUtils::NearestLanguageFile(iEikonEnv->FsSession(),fileName);
    iResourceFileOffset=iCoeEnv->AddResourceFileL(fileName);

    // Create FSW
    iFSControl= new (ELeave) CAknFastSwapWindowControl(*this);
    iFSControl->ConstructL();
    
    // MMC unlocker
    iMMCUnlock = CAknMMCPasswordRequester::NewL();
    
    // Boost our priority similar to eikon server.
    RThread thread; 
#if defined(__EPOC32__)
    thread.SetProcessPriority(EPriorityHigh);
#else
    thread.SetPriority(EPriorityAbsoluteForeground);
#endif

    // Start OOM watcher thread when scheduler is running
    // effectively this frees eikon server thread also.
    iIdler = CIdle::NewL(CActive::EPriorityIdle);
    iIdler->Start(TCallBack(StartOOM, this));
    SetAliasKeyCodeResolverL(this);       
    
    // Define the property for Idle application window group id. This cannot be done in AknIcon,
    // because the property is internal in classicui domain.
    TInt err = RProperty::Define(
        KPSUidAvkonInternal, 
        KAknIdleAppWindowGroupId, 
        RProperty::EInt, 
        KPassReadPolicy,  // None
        KWriteDDPolicy);  // WriteDeviceData
        
    if (err != KErrAlreadyExists)
        {
        User::LeaveIfError(err);
        }
        
    // Define a PubSub key indicate menu option has the task swapper item or not
    err =  RProperty::Define(
    KPSUidAvkonInternal, 
    KAknMenuOptionNoTaskSwapper, 
    RProperty::EInt); 
               
    if ( err != KErrNone && err != KErrAlreadyExists )
         {
         User::LeaveIfError( err );
         } 
#ifdef RD_INTELLIGENT_TEXT_INPUT        
    // Define the property for Idle application window group id. This cannot be done in AknIcon,
    // because the property is internal in classicui domain.
    err = RProperty::Define(
        KPSUidAknFep, 
        KAknFepFnKeyState, 
        RProperty::EInt, 
        KPassReadPolicy,  // None
        KWriteDDPolicy);  // WriteDeviceData
        
    if (err != KErrAlreadyExists)
        {
        User::LeaveIfError(err);
        }
#endif
    
    // Start listening "global notes allowed" property. When global notes are allowed,
    // we know that the boot is finished and the Idle app window group id can be fetched.       
    User::LeaveIfError(iGlobalNotesAllowedProperty.Attach(
        KPSUidUikon, 
        KUikGlobalNotesAllowed));        

    iGlobalNotesAllowedSubscriber = new (ELeave) CPropertySubscriber(
        TCallBack(GlobalNotesAllowedCallBack, this), 
        iGlobalNotesAllowedProperty);

    iGlobalNotesAllowedSubscriber->Subscribe();
    
#ifdef RD_INTELLIGENT_TEXT_INPUT
         
    TInt err1 = 0;         
                                         
    err1 = RProperty::Define(KPtiEnginePSUid, EKeyMapPropertyCount, RProperty::EInt,
                            KCapServerPtiEngineAlwaysPass, KCapServerPtiEngineWritePolicy);
    err1 |= RProperty::Set(KPtiEnginePSUid, EKeyMapPropertyCount, 0);    
    err1 |= RProperty::Define(KPtiEnginePSUid, EKeyMapPropertyData, RProperty::EByteArray,    
                            KCapServerPtiEngineAlwaysPass, KCapServerPtiEngineWritePolicy);
                            
    err1 |= RProperty::Define(KPtiEnginePSUid, EKeyMapPropertyData2, RProperty::EByteArray,
                             KCapServerPtiEngineAlwaysPass, KCapServerPtiEngineWritePolicy);                                           
    err1 |= RProperty::Define(KPtiEnginePSUid, EKeyMapPropertyCount2, RProperty::EInt,
                            KCapServerPtiEngineAlwaysPass, KCapServerPtiEngineWritePolicy);
    err1 |= RProperty::Set(KPtiEnginePSUid, EKeyMapPropertyCount2, 0);      
    
    err1 |= RProperty::Define(KPtiEnginePSUid, EKeyMapPropertyData3, RProperty::EByteArray,
                             KCapServerPtiEngineAlwaysPass, KCapServerPtiEngineWritePolicy);                                           
    err1 |= RProperty::Define(KPtiEnginePSUid, EKeyMapPropertyCount3, RProperty::EInt,
                            KCapServerPtiEngineAlwaysPass, KCapServerPtiEngineWritePolicy);
    err1 |= RProperty::Set(KPtiEnginePSUid, EKeyMapPropertyCount3, 0);   
    
   // Create ptiengine instance for key code resolver.
	if (err1 == KErrNone && !iPtiEngine)
   		{   		
   		// create PtiEngine already here because only cap server process has write rights to
   		// above properties and several PtiEngine cores want to cache language
   		// bindings to those properties.
		TRAP_IGNORE(iPtiEngine = CPtiEngine::NewL(ETrue));
	 	}           
#endif

    // Create capserver discreetpopuphandler     
    CAknCapServerDiscreetPopupHandler::CreateDiscreetPopupHandlerL();     
	LoadAlternateFsPlugin();

	ProcessInitFlipStatus();
    }
    
TKeyResponse CAknCapAppServerAppUi::HandleKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType)
    {
    return CAknNotifierAppServerAppUi::HandleKeyEventL(aKeyEvent, aType);
    }

// This must not leave if aAddCount == 0.
void CAknCapAppServerAppUi::SuppressAppSwitchingL(TInt aAddCount, TInt aClientId)
    {
    TInt index = KErrNotFound;
    for (TInt ii=0;ii<iAppsKeyArray.Count();ii++)
        {
        if (iAppsKeyArray[ii].iUid == aClientId)
            {
            index = ii;
            }
        }
    
    if (aAddCount == EAknAppsKeyBlockRemoveClient && aClientId) // client is exiting
        {
        if (index != KErrNotFound)
            {
            iAppsKeyArray.Remove(index);
            }
        return;
        }
        
    // create client entry (did not previosly exist)
    if (index == KErrNotFound)
        {
        __ASSERT_DEBUG(aAddCount == EAknAppsKeyBlockAddCount, User::Invariant());
        SSuppressInfo info = SSuppressInfo(aClientId);
        User::LeaveIfError(iAppsKeyArray.Insert(info,0));
        index = 0;
        }
    // Add aAddcount to client data
    iAppsKeyArray[index].iReferenceCount += aAddCount;
    if ( IsAppsKeySuppressed() )
        {
        TInt err = RProperty::Set(
        KPSUidAvkonInternal, 
        KAknMenuOptionNoTaskSwapper, ENoTaskSwapper );
        if ( err!=KErrNone )
            {
            User::LeaveIfError( err );
            }    
        }
    else
        {
        TInt err = RProperty::Set(
        KPSUidAvkonInternal, 
        KAknMenuOptionNoTaskSwapper, ETaskSwapper );
        if ( err!=KErrNone )
            {
            User::LeaveIfError( err );
            }
        }    
    }
    
void CAknCapAppServerAppUi::KillAppL(const RMessage2& aMessage)
    {
    aMessage.Complete(KErrNotSupported);
    }
    
void CAknCapAppServerAppUi::DoTaskListCommandL(const RMessage2& aMessage)        
    {
    switch (aMessage.Function())
        {
        case EAknSEnableTaskList:
            {
            TInt err = EnableTaskList(aMessage.Int0());
            aMessage.Complete(err);
            break;
            }
        case EAknsLaunchTaskList:
            {
            if (iTaskListEnabled)
                {
                if ( iAlternateFS && iAlternateFS->IsReady() )
                    {
                    if ( aMessage.Int0() )
                        {
                        iAlternateFS->Show();
                        }
                    else
                        {
                        iAlternateFS->Dismiss();
                        }                         
                    }
                else
                    {
                    if ( aMessage.Int0() )
                        {
                        TInt err = KErrNone;
                        TRAP( err, iFSControl->InitializeWindowGroupListL( EFalse ));
                        if ( !err )
                            {   
                            iFSControl->RunFastSwapL();             
                            }
                        }
                    else
                        {
                        iFSControl->CloseFastSwap();
                        }                        
                    }
                }
            aMessage.Complete(KErrNone);
            break;
            }
        case EAknSRefreshTaskList:
            {
            TInt err = UpdateTaskListL( ETrue );
            if ( err != KErrNone )
                {
                iFSControl->CloseFastSwap();
                }
            aMessage.Complete(err);
            break;
            }
        default:
            {
            aMessage.Complete(KErrNotSupported);
            break;          
            }
        }
    }

TBool CAknCapAppServerAppUi::IsAppsKeySuppressed()
    {
    if (!iTaskListEnabled)
        {
        return ETrue;
        }
    
    for(TInt ii = 0; ii < iAppsKeyArray.Count(); ii++)
        {
        if (iAppsKeyArray[ii].iReferenceCount)
            {
            return ETrue;
            }
        }
    return EFalse;
    }
    
void CAknCapAppServerAppUi::HideApplicationFromFswL(TInt aUid,TBool aDisable)
    {
    if (!iHiddenList)
        {
        iHiddenList = new (ELeave) CArrayFixFlat<TInt>(1); // This won't grow very big I hope
        // the appui server reserves a property where it stores the hidden list.
        RProperty::Define(KPSUidUikon, KUikAppHiddenList, RProperty::ELargeByteArray);
        }
    TBool foundUid( EFalse );
    
    for (TInt i = 0; i < iHiddenList->Count(); i++)
        {
        if (aUid == iHiddenList->At(i))
            {
            iHiddenList->Delete(i);
            foundUid = ETrue;
            break;
            }
        }

    if (aDisable)
        {
        iHiddenList->AppendL(aUid);
        // visible uid hidden -> refresh tasklist
        if ( !foundUid )
            {
            UpdateTaskListL( ETrue );
            }
        }
    else 
        {
        // hidden uid set to visible -> refresh tasklist
        if ( foundUid )
            {
            UpdateTaskListL( ETrue );
            }
        }
        
    // when the hidden list is ready it get's published to P&S service 
    PublishHiddenList();    
    }

void CAknCapAppServerAppUi::ProcessInitFlipStatus()
    {
    // we remove the definition from hal_switch.h
    enum
        {
        ECoverSwitch,
        EHalGroupSwitch = 29
        };

		const TInt KFeatureIdFfSliderLandscapeStartsApp_LocalDefinition = 5126; //we have to define it here because of some header exporting problem
    if (FeatureManager::FeatureSupported(KFeatureIdFfSliderLandscapeStartsApp_LocalDefinition))
        {
        // check the state of phone slide, if it is open during startup, 
        // we enable the landscape orientation
        TBool flipStatus(EFalse); // flipStatus true : flip open / false : flip close
        TInt err = UserSvr::HalFunction(EHalGroupSwitch, ECoverSwitch, &flipStatus, reinterpret_cast<TAny*>(EFalse));
        if (KErrNone == err && flipStatus)
            {
            TRAP_IGNORE(RotateScreenL());
            }
        }
    }

// For Gs to initiate OFN status
void CAknCapAppServerAppUi::InitiateOFNStatus()
    {
    // For Gs to initiate OFN status
    enum TFidOFNFunctionForGs
        {
        EOFNSetPowerON,     // OFN Powering (ON/OFF)
        EHalGroupOFN = 28
        };

    const TInt KFeatureId_Ff_Ofn_Feature = 193;
    const TInt KSettingsOptical_Joystick_Status = 0x00000019;
    
    // For Gs to initiate OFN status
    if( FeatureManager::FeatureSupported( KFeatureId_Ff_Ofn_Feature ) )
        {
        CRepository* personalizationRepository = NULL;
        TRAPD( errCode, personalizationRepository = CRepository::NewL( KCRUidPersonalizationSettings ) );
        if (errCode == KErrNone)
            {
            TInt ofnStatus = 0;
            personalizationRepository->Get( KSettingsOptical_Joystick_Status, ofnStatus );
            delete personalizationRepository;
            
            UserSvr::HalFunction( EHalGroupOFN, EOFNSetPowerON, reinterpret_cast<TAny*>( ofnStatus ), 
                                reinterpret_cast<TAny*>( ofnStatus ) );
            }
	    }
    }

void CAknCapAppServerAppUi::PublishHiddenList()
    {
    // 1. the creation of hidden list array
    TBuf16 <2*KMaxHiddenApps> hiddenList;
    TInt i;
    TUint16 upperBits;
    // the limit of hidden application uids
    TInt hiddenCount = ( iHiddenList->Count() > KMaxHiddenApps ) ? 
        KMaxHiddenApps : iHiddenList->Count();
    
    for ( i = 0; i < hiddenCount; i++)                
        {
        // 32-bit integer is appended in two parst to 16-bit buffer 
        upperBits = iHiddenList->At(i) >> 16;
        hiddenList.Append( upperBits );
        // upper values are automatically truncated
        hiddenList.Append( iHiddenList->At(i) );
        }
        
    // the end of hidden list is marked null (0x00000000)
    if ( i < KMaxHiddenApps )
        {
        hiddenList.Append( 0x0000 );
        hiddenList.Append( 0x0000 );
        }
        
    // 2. setting the property value 
    RProperty::Set(KPSUidUikon, KUikAppHiddenList, hiddenList);
    }

TBool CAknCapAppServerAppUi::HiddenFromFSW( TInt aUid )
    {
    if ( iHiddenList )
        {
        for ( TInt i = 0; i < iHiddenList->Count(); i++)
            {
            if (aUid == iHiddenList->At(i))
                {
                return ETrue;
                }
            }
        }

    return EFalse;
    }

TInt CAknCapAppServerAppUi::EnableTaskList(TBool aEnable)
    {
    TInt err = KErrNone;
    
    iTaskListEnabled = aEnable;
       
    if ( IsAppsKeySuppressed() )
        {
        err = RProperty::Set(KPSUidAvkonInternal, KAknMenuOptionNoTaskSwapper, ENoTaskSwapper);    
        }
    else
        {
        err = RProperty::Set(KPSUidAvkonInternal, KAknMenuOptionNoTaskSwapper, ETaskSwapper);
        }
    return err;
    }

TBool CAknCapAppServerAppUi::HandleShortAppsKeyPressL()
    {
    if(iAlternateFS && iAlternateFS->IsReady() && iAlternateFS->IsVisible())
        {
        iAlternateFS->HandleShortAppKeyPress();
        return ETrue;
        }
    if (iFSControl->IsVisible())
        {
        iFSControl->HandleShortAppsKeyPressL();
        return ETrue;
        }
        
    return EFalse;
    }

TBool CAknCapAppServerAppUi::HandleLongAppsKeyPressL()
    {
    if (iTaskListEnabled)
        {
        if ( iAlternateFS && iAlternateFS->IsReady() )
            {        
            ShowOrDismissAlternateFs();
            }
        else
            {
            if (iFSControl->IsVisible())
                {
                iFSControl->HandleLongAppsKeyPressL();
                }
            else
                {
                if (iFSControl->VisibleWindowGroupsCountL()<1)
                    {
                    return EFalse;
                    }
                else
                    {
                    iFSControl->RunFastSwapL();
                    }
                }            
            }
        }
    return ETrue;
    }

void CAknCapAppServerAppUi::SetStatusPaneFlags(TInt aFlags)
    {
    if (iStatusPane)
        {
        iStatusPane->SetFlags(aFlags);
        }
    }

void CAknCapAppServerAppUi::SetStatusPaneLayoutL(TInt aLayoutResId)
    {
    if (iStatusPane)
        {
        iStatusPane->SwitchLayoutL(aLayoutResId);
        }
    }

void CAknCapAppServerAppUi::BlankScreenL(TBool aBlank, TBool aToForeground)
    {
    if (aBlank)
        {
        if (++iBlankWinRefCount == 1)
            {
            ASSERT(!iBlankWin);
            if (aToForeground)
                {
                iBackdropWindowGroup.SetOrdinalPosition(0, KWgPriorityCoverEverything);
                }
            else
                {
                iBackdropWindowGroup.SetOrdinalPosition(1, ECoeWinPriorityNormal); 
                }
            iBlankWin = CAknServBlankWin::NewL(iBackdropWindowGroup, iStatusPane);
            iForegroundBlankScreen = aToForeground;
            }
        }
    else if (--iBlankWinRefCount <= 0)
        {
        iBlankWinRefCount = 0;
        if (iForegroundBlankScreen)
            {
#ifdef RD_UI_TRANSITION_EFFECTS_LAYOUT_SWITCH
            CWsScreenDevice* screen = iEikonEnv->ScreenDevice();
            /*
            RWsSession& ws = iEikonEnv->WsSession();
            TInt wgId = ws.GetFocusWindowGroup();
            CApaWindowGroupName* wgName = CApaWindowGroupName::NewL(ws, wgId);
            CleanupStack::PushL( wgName );
            TUid appUid = wgName->AppUid();
            CleanupStack::PopAndDestroy( wgName );
            */
            //GfxTransEffect::BeginFullScreen( AknTransEffect::ELayoutSwitch,
            //        TRect( screen->SizeInPixels() ),
            //        AknTransEffect::EParameterType,
            //        AknTransEffect::GfxTransParam( KTfxServerUid )
            //        );

            GfxTransEffect::EndFullScreen();
#endif
            iBackdropWindowGroup.SetOrdinalPosition(1, ECoeWinPriorityNormal);
            }
        delete iBlankWin;
        iBlankWin = 0;
        iForegroundBlankScreen = EFalse;
        } 
    }

void CAknCapAppServerAppUi::SwapLayoutSwitchBlankScreenL()
    {
    if (iBlankWin)
        {
        if (!iForegroundBlankScreen)
            {
            iBackdropWindowGroup.SetOrdinalPosition(0, KWgPriorityCoverEverything);
            }
        iForegroundBlankScreen = ETrue;
        CAknServBlankWin* newBlankWin = CAknServBlankWin::NewL(iBackdropWindowGroup, iStatusPane);
        newBlankWin->SetLayoutBlank(ETrue);
        delete iBlankWin;
        iBlankWin = newBlankWin;
        }
    }

TBool CAknCapAppServerAppUi::IsDisplayingForegroundBlankScreen() const
    {
    return iForegroundBlankScreen;
    }

void CAknCapAppServerAppUi::HandleResourceChangeL(TInt aType)
    {
    if (aType == KAknInternalFSWClose) // for notifiers running inside this thread
        {
        if (iFSControl)
            {
            iFSControl->CloseFastSwap();
            
            // This cancels power menu when keys are locked / soft note accepted.
            Manager()->CancelNotifier(KAknGlobalListQueryUid); 
            }
        return; // don't pass this outside this class
        }
    if ( aType == KEikDynamicLayoutVariantSwitch )
        {
        iCapServer->RefreshLongTapAnimation();
        }
    
    CAknNotifierAppServerAppUi::HandleResourceChangeL(aType);
    if (iFSControl)
        {
        if ( aType == KAknsMessageSkinChange )
            {
            UpdateTaskListL( ETrue );
            }
        iFSControl->HandleResourceChange(aType);
        }
    if (iStatusPane)
        {
        iStatusPane->HandleResourceChange(aType);
        }
	if (aType == KAknsMessageSkinChange )
		{
		iSgcs->FadeBitmapGenerationL();
		iSgcs->FadeColorGenerationL();
		}
    }
    
void CAknCapAppServerAppUi::HandleWsEventL(const TWsEvent& aEvent,CCoeControl* aDestination)
    {
    if ( iMessageReaderLongPressDetector && !IsAppsKeySuppressed() && !iFSControl->IsDisplayed() )
        {
        // Message Reader can be launched by long pressing left soft key 
        // events need to be intercepted/consumed before they are forwarded to cba
        if ( iMessageReaderLongPressDetector->HandleWsEventL( aEvent, aDestination ) )
            {
            return;
            }
        }
    switch( aEvent.Type() )
        {
        case EEventFocusGroupChanged: // For cover UI/status pane refresh problems
        case EEventWindowGroupListChanged:
            {
            // only updated if application has informed about it's intentions to exit
            UpdateTaskListL( EFalse );
            iSgcs->HandleWindowGroupListChangeL();
            break;
            }
        case KUidValueAknsSkinChangeEvent:
            {
            HandleResourceChangeL(KAknsMessageSkinChange);
            HandleStackedControlsResourceChange(KAknsMessageSkinChange);
            break;
            }
        default:
            { 
            CAknNotifierAppServerAppUi::HandleWsEventL(aEvent, aDestination);
            if (EventMonitor())
                {
                EventMonitor()->HandleWsEventL(aEvent, aDestination); // for ecs
                }
            }
        }
    }

void CAknCapAppServerAppUi::SetCurrentAppStatuspaneResourceIdL(TInt aResourceId)
    {
    iStatusPane->SetCurrentAppStatuspaneResourceId(aResourceId);
    }

TInt CAknCapAppServerAppUi::CurrentAppStatuspaneResourceIdL()
    {
    return iStatusPane->CurrentAppStatuspaneResourceId();
    }

void CAknCapAppServerAppUi::RotateScreenL()
    {
    iSgcs->RotateScreenL();
    }

// ---------------------------------------------------------
// CAknCapAppServerAppUi::UpdateTaskListL
// Tasklist will be updated when its visible and when 
// when the old tasklist is no longer valid
// ---------------------------------------------------------
//  
TInt CAknCapAppServerAppUi::UpdateTaskListL( TBool aTaskListRefreshNeeded )
    {
    TInt err = KErrNone;
    if ( iFSControl->IsDisplayed() )
        {
        // update window group list (task list)
        TInt windowGroupListChanged = ETrue;
        
        TRAP( err, windowGroupListChanged = iFSControl->InitializeWindowGroupListL( 
            !aTaskListRefreshNeeded ) );
            
        if ( windowGroupListChanged || aTaskListRefreshNeeded ) 
            {
            TRAP( err, iFSControl->HandleChangeInWindowGroupListL() ); 
            }
        }
    return err;
    }

LOCAL_C TBool IsQwertyKey(TPtiKey aKey) 
    {
    if ((aKey >= EPtiKeyQwertyA && aKey <= EPtiKeyQwertyZ) ||
        (aKey >= EPtiKeyQwerty0 && aKey <= EPtiKeyQwerty9) ||
        aKey == EPtiKeyQwertyPlus || 
        aKey == EPtiKeyQwertyMinus ||
        aKey == EPtiKeyQwertyComma ||
        aKey == EPtiKeyQwertySemicolon ||       
        aKey == EPtiKeyQwertyFullstop ||
        aKey == EPtiKeyQwertyHash ||       
        aKey == EPtiKeyQwertySlash ||
        aKey == EPtiKeyQwertyApostrophe
#ifdef RD_INTELLIGENT_TEXT_INPUT
        || aKey == EPtiKeyQwertySpace       
        || aKey == EPtiKeyQwertyAtCharacter   
#endif
       )
            {    
            return ETrue;
            }   

    return EFalse;  
    } 
#ifdef RD_INTELLIGENT_TEXT_INPUT
TBool CAknCapAppServerAppUi::IsCharacterCategoryNumber(TUint aChar) const
{
    TChar::TBdCategory numCategory;
    TBool isNumber = EFalse;
    numCategory = (TChar(aChar)).GetBdCategory();
    isNumber = ((numCategory == TChar::EEuropeanNumber) || (numCategory == TChar::EArabicNumber) ||
               (numCategory == TChar::EEuropeanNumberTerminator) || (aChar == 0x2E) || 
               (aChar == 0x2A) || (aChar == 0x3D) || (aChar == 0x2F));
    return isNumber;
}
#endif

TInt CAknCapAppServerAppUi::GetAliasKeyCode(TUint& aCode, const TKeyEvent& aKeyEvent,TEventCode /*aType*/)
    {   
    aCode = aKeyEvent.iCode;
#ifdef RD_INTELLIGENT_TEXT_INPUT                               
    TKeyEvent keyEventLocal = aKeyEvent;
    
    #if defined(__WINS__)
        if ( keyEventLocal.iScanCode == EStdKeyNkpPlus )
            {
            // Workaround solution for the qwerty '+' key in emulator environment.
            // I did not find a way how to to configure epoc_352x416_Qwerty.ini to send '+' keyevent.
            keyEventLocal.iScanCode = 0x2b;  // '+' key.
            }
	#endif 
        
#endif 
    if (!iQwertyStatus || (aKeyEvent.iModifiers & EModifierSpecial) != 0)
        {
        // Only qwerty events are converted. Coversion is also rejected if EModifierSpecial
        // bit is set. That can be used for disabling conversion for simulated
        // key events.
        return KErrNone;
        }
            
#ifdef RD_INTELLIGENT_TEXT_INPUT                               
    if (IsQwertyKey((TPtiKey)keyEventLocal.iScanCode))       
#else
    if (IsQwertyKey((TPtiKey)aKeyEvent.iScanCode))       
#endif 
        {           
        // We know in advance that iCode values below this threshold are not
        // going to be converted, so just return.    
        if (aCode <= KKeyEventICodeThreshold)
            {
            return KErrNone;
            }
            
        if (aKeyEvent.iModifiers & KModifierExternalKeyboard)            
            {
            // The event is coming from external keyboard, do not convert.
            return KErrNone;
            }
                
        TInt err = KErrNone;                
        
        if (!iPtiEngine)
            {
            TRAP(err, iPtiEngine = CPtiEngine::NewL(ETrue));
            if (err != KErrNone)
                {
                return err;
                }
            }
                                           
        CAknSettingCache& settingsCache =   CAknEnv::Static()->SettingCache();
                                
        const TInt KMaxNumCharsPerCase = 50;
        TBuf<KMaxNumCharsPerCase> keys; 
   
        const TBool shifted = (aKeyEvent.iModifiers & EModifierLeftShift) ||
            (aKeyEvent.iModifiers & EModifierRightShift); 
#ifdef RD_INTELLIGENT_TEXT_INPUT

		TInt fnState;
    	RProperty::Get(KPSUidAknFep,KAknFepFnKeyState, fnState);
		const TBool functionized = (keyEventLocal.iModifiers & EModifierRightFunc) ;
									//||	(fnState == 6); 

        const TBool isCtrl = (aKeyEvent.iModifiers & EModifierLeftCtrl) ||
            (aKeyEvent.iModifiers & EModifierRightCtrl);
        if(isCtrl)
            return KErrNone;
#endif
        CPtiCoreLanguage* lang = static_cast<CPtiCoreLanguage*>(iPtiEngine->GetLanguage(
            settingsCache.InputLanguage()));                 
#ifdef RD_INTELLIGENT_TEXT_INPUT
            // Qwerty Keyboard layout
        TInt keyboardLayout = 0;       
        RProperty::Get(KCRUidAvkon, KAknKeyBoardLayout, keyboardLayout);

        TPtiKeyboardType keyboardType = (TPtiKeyboardType) keyboardLayout ;
#endif
            
        if (lang)
            {                   
#ifdef RD_INTELLIGENT_TEXT_INPUT                               
            CPtiQwertyKeyMappings* maps;
            if(keyboardType != EPtiKeyboardHalfQwerty)
                maps = static_cast<CPtiQwertyKeyMappings*>(lang->GetQwertyKeymappings());
            else
                maps = static_cast<CPtiQwertyKeyMappings*>(lang->GetHalfQwertyKeymappings());
            
#else
            CPtiQwertyKeyMappings* maps = 
                static_cast<CPtiQwertyKeyMappings*>(lang->GetQwertyKeymappings());
#endif                    
                
            if (maps)
                {
#ifdef RD_INTELLIGENT_TEXT_INPUT
                maps->SetKeyboardType(keyboardType);
                if(functionized)
                    {
                    maps->GetDataForKey((TPtiKey)keyEventLocal.iScanCode, keys, EPtiCaseFnLower);
					if( !(keys.Length() && IsCharacterCategoryNumber(keys[0])))
                        maps->GetDataForKey((TPtiKey)keyEventLocal.iScanCode, keys, EPtiCaseFnUpper);					
					if(!keys.Length())
                        {
                        maps->GetDataForKey((TPtiKey)keyEventLocal.iScanCode, keys, EPtiCaseFnLower);
                        }
                    }
				else if(shifted)
					{
					maps->GetDataForKey((TPtiKey)keyEventLocal.iScanCode, keys, EPtiCaseUpper);
					}
				else
					{               
                maps->GetDataForKey((TPtiKey)keyEventLocal.iScanCode, keys, EPtiCaseFnLower);
                if( !(keys.Length() && IsCharacterCategoryNumber(keys[0])))
                    maps->GetDataForKey((TPtiKey)keyEventLocal.iScanCode, keys, EPtiCaseFnUpper);
                if( !(keys.Length() && IsCharacterCategoryNumber(keys[0])))
                    maps->GetDataForKey((TPtiKey)keyEventLocal.iScanCode, keys, EPtiCaseLower);
                if( !(keys.Length() && IsCharacterCategoryNumber(keys[0])))
                    maps->GetDataForKey((TPtiKey)keyEventLocal.iScanCode, keys, EPtiCaseUpper);                
                    if( !(keys.Length() && IsCharacterCategoryNumber(keys[0])))
                        keys.SetLength(0);
					}
                
#else
                if (shifted)
                    {
                    maps->GetDataForKey((TPtiKey)aKeyEvent.iScanCode, keys, EPtiCaseUpper);             
                    }
                else
                    {
                    maps->GetDataForKey((TPtiKey)aKeyEvent.iScanCode, keys, EPtiCaseLower);             
                    }                       
#endif
                }
            }
        
        if ( keys.Length() > 0 )
            {
            switch (keys[0])        
                {
                case KPtiPinyinMarker:
                case KPtiStrokeMarker:
                case KPtiZhuyinMarker:
                case KPtiCangjieMarker:
                case KPtiGetAllMarker:                  
                    if (keys.Length() > 1)
                        {
                        aCode = keys[1];
                        }
                    break;
                default:                 
                    aCode = keys[0];                 
                }
            } 
        } 
        
    return KErrNone;
    }

void CAknCapAppServerAppUi::ForwardKeyToPhoneAppL(const TKeyEvent& aKeyEvent)
    {
    if (iScanCodeCaptureHandle)
        {
        return;
        }
    iPhoneKey = aKeyEvent; // reset
    
    iScanCodeCaptureHandle = CCoeEnv::Static()->RootWin().CaptureKeyUpAndDowns(
        aKeyEvent.iScanCode,0,0 );
        
    if (!iIdler)
        {
        iIdler = CIdle::NewL(CActive::EPriorityStandard);        
        }
    iIdler->Start(TCallBack(AknPhoneKeyForwarder::ForwardKeyToPhoneApp, &iPhoneKey));
    iUpReceived = EFalse;
    }



void CAknCapAppServerAppUi::PhoneKeyUpReceived()
    {              
    if (iScanCodeCaptureHandle)
        {
        CCoeEnv::Static()->RootWin().CancelCaptureKeyUpAndDowns(iScanCodeCaptureHandle);
        }
    iScanCodeCaptureHandle = 0;
    iUpReceived = ETrue;
    if (!iIdler->IsActive()) // callback already triggered
        { // direct call
        AknPhoneKeyForwarder::ForwardUpEventToPhoneApp(&iPhoneKey);
        }
    }

void CAknCapAppServerAppUi::SetFgSpDataSubscriberIdL(TInt aId)
    {   
    CEikStatusPaneBase* statusPane = CEikStatusPaneBase::Current();
    if (statusPane)
        {
        CEikServStatusPane* ssp = static_cast<CEikServStatusPane*>(statusPane);
        CAknStatusPaneDataPublisher* publisher = ssp->iDataPublisher;
        if (publisher)
            {
            publisher->SetForegroundSubscriberId(aId);
            publisher->PublishDataL();
            }            
        }
    }

void CAknCapAppServerAppUi::CloseFSW()
    {
    if (iFSControl)
        {
        iFSControl->CloseFastSwap();
        }
    }
	
void CAknCapAppServerAppUi::SetIdleActive( TBool bActive )
    {
    iIdleActive = bActive;
    }

TBool CAknCapAppServerAppUi::IsIdelActive( )
    {
    return iIdleActive;
    }

void CAknCapAppServerAppUi::PublishInstalledLanguagesL()
    {
    User::LeaveIfError( RProperty::Define( 
        KPSUidUikon,
        KUikInstalledLanguages,
        RProperty::EText,
        KReadPolicy,        // None
        KWriteDDPolicy ) ); // WriteDeviceData
    
    CArrayFixFlat<TInt>* installedLanguages = 0;
    
    User::LeaveIfError( SysLangUtil::GetInstalledLanguages( installedLanguages ) );
    
    CleanupStack::PushL( installedLanguages );
    
    TInt nbrOfLanguages = installedLanguages->Count();
    
    // This is a bit more than enough buffer in most cases
    // Add one just for the space at the beginning of the data.
    TInt bufferLength = nbrOfLanguages * KMaxLanguageCodeLength + 1;
            
    HBufC8* languages = HBufC8::NewLC( bufferLength );
    TPtr8 ptr( languages->Des() );
    
    if ( nbrOfLanguages > 0 )
        {
        ptr.Append( KSeparator ); // Add space at the beginning of the data
        }
    
    for ( TInt i = 0; i < nbrOfLanguages; i++ )
        {
        ptr.AppendNum( installedLanguages->At(i) ); // Add language ID to data
        ptr.Append( KSeparator );// Space is also added as the last character
        }    
          
    RProperty::Set( KPSUidUikon, KUikInstalledLanguages, ptr );
    
    CleanupStack::PopAndDestroy( 2, installedLanguages );
    }

TInt CAknCapAppServerAppUi::GlobalNotesAllowedCallBack(TAny* aPtr)
    {
    CAknCapAppServerAppUi* self = static_cast<CAknCapAppServerAppUi*>(aPtr);
    if (self)
        {
        self->HandlePropertyChange(KUikGlobalNotesAllowed);
        }
    return KErrNone;
    }

    
void CAknCapAppServerAppUi::HandlePropertyChange(const TInt aProperty)
    {
    switch(aProperty)
        {
        case KUikGlobalNotesAllowed:
            {
            TUid uid = KPhoneUid;
            TApaTaskList taskList ( CEikonEnv::Static ()->WsSession () );
            TApaTask task = taskList.FindApp ( uid );
            if ( task.Exists() )
                {
                TInt wgId = task.WgId ();
                // Save the window group id to PubSub. 
                RProperty::Set ( KPSUidAvkonInternal, KAknIdleAppWindowGroupId,
                        wgId );
                }
            }
            break;
        default:
            break;
        };
    }
    
// -----------------------------------------------------------------------------
// C++ constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CPropertySubscriber::CPropertySubscriber(TCallBack aCallBack, RProperty& aProperty)
    : CActive(EPriorityNormal), iCallBack(aCallBack), iProperty(aProperty)
    {
    CActiveScheduler::Add(this);
    }

// -----------------------------------------------------------------------------
// Destructor.
// -----------------------------------------------------------------------------
//
CPropertySubscriber::~CPropertySubscriber()
    {
    Cancel();
    }

// -----------------------------------------------------------------------------
// Starts to listen for changes.
// -----------------------------------------------------------------------------
//
void CPropertySubscriber::Subscribe()
    {
    if (!IsActive())
        {
        iProperty.Subscribe(iStatus);
        SetActive();
        }
    }

// -----------------------------------------------------------------------------
// Stops listening for changes.
// -----------------------------------------------------------------------------
//
void CPropertySubscriber::StopSubscribe()
    {
    Cancel();
    }

// -----------------------------------------------------------------------------
// When active object fires, call callback and continue listening.
// -----------------------------------------------------------------------------
//
void CPropertySubscriber::RunL()
    {
    if (iStatus.Int() == KErrNone)
        {
        iCallBack.CallBack();
        Subscribe();
        }
    }

// -----------------------------------------------------------------------------
// Cancel.
// -----------------------------------------------------------------------------
//
void CPropertySubscriber::DoCancel()
    {
    iProperty.Cancel();
    }
    
// Actual entry point.  
LOCAL_C CApaApplication* NewApplication()
    {
    return new CAknCapServerApplication();
    }   
    
GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }

// End of file
