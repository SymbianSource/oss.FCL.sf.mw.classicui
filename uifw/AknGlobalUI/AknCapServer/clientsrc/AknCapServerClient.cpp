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

#include <eiknotapi.h>
#ifndef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon.hrh>
#else
#include <uikon.hrh>
#include <uiklaf/private/pluginuid.hrh>
#endif
#include "AknCapServerClient.h"
#include "AknCapServerDefs.h"
#include <eiksrvs.h>
#include <apgcli.h>
#include <apasvst.h>
#include <aknconsts.h>
#include <AknNotifierControllerUtilities.h>
#include <e32notif.h>

// For global note.
#include <AknGlobalNote.h>
#include <avkon.rsg>

#include "akndiscreetpopupdata.h"

_LIT(KAknCapServerExecutable, "z:\\sys\\bin\\akncapserver.exe");
_LIT(KAknNfySrvThreadName, "aknnfysrv");

TInt RAknUiServer::ConnectAknServer()
    {
#ifdef _DEBUG
    RThread me;
    TName name = me.Name();
    RDebug::Print( _L( "RAknUiServer::ConnectAknServer(), handle %d, %S" ), Handle(), &name );    
#endif
    TInt err = KErrNone;
    if (Handle() == NULL)
        {
        _LIT(KServerNameFormat, "%08x_%08x_AppServer");
        TFullName serverName;
        
        serverName.Format(
            KServerNameFormat, 
            KUikonUidPluginInterfaceNotifiers, 
            KAknCapServerUid.iUid);
            
        TRAP(err, ConnectExistingByNameL(serverName));
        if (err == KErrNotFound) // This should be never true when starter is in use!
            {
            TRAP_IGNORE(StartAknCapserverL());
            User::After(500000); // No problem to wait synchronously as pure RnD support.
            TRAP(err,ConnectExistingByNameL(serverName));
            }
        }
#ifdef _DEBUG
    RDebug::Print(_L("RAknUiServer::ConnectAknServer() end"));    
#endif
    return err;
    }
    
// This method must be able to connest eikon server always, used by notifiers running inside
// eikon server.
EXPORT_C TInt RAknUiServer::ConnectAndSendAppsKeySuppress(TBool aSuppress)
    {
    TInt ret = ConnectAknServer();
    if (ret == KErrNone)
        {
        TInt param = aSuppress ? EAknAppsKeyBlockAddCount : EAknAppsKeyBlockDecreaseCount;
        ret = SendReceive(EAknSSuppressAppsKey, TIpcArgs( param ));
        }
    return ret;
    }

EXPORT_C TInt RAknUiServer::HideApplicationFromFsw(TBool aHide, TInt aMyUid)
    {
    RThread thread;
    if (!Handle() && thread.Name() == EIKAPPUI_SERVER_THREAD_NAME)
        {
        return KErrNone;
        }

    TInt ret = ConnectAknServer();
    if (ret == KErrNone)
        {
        ret = SendReceive(EAknSHideApplicationFromFWS, TIpcArgs( aMyUid, aHide ));
        }
    return ret;
    }

EXPORT_C void RAknUiServer::UnlockMedia(TInt aDrive, TBool aStore, TRequestStatus& aStatus)
    {
    TInt ret = ConnectAknServer();
    if (ret == KErrNone)
        {
        SendReceive(EAknSUnlockMedia, TIpcArgs( EFalse, aDrive, aStore ), aStatus);
        }
    else
        {
        TRequestStatus* ptr = &aStatus;  
        User::RequestComplete(ptr, ret);        
        }       
    }
    
EXPORT_C void RAknUiServer::CancelUnlockMedia()
    {
    TInt ret = ConnectAknServer();
    if (ret == KErrNone)
        {
        ret = SendReceive(EAknSUnlockMedia, TIpcArgs( ETrue ));
        }
    }
    
EXPORT_C TInt RAknUiServer::EnableTaskList(TBool aEnable)
    {
    RThread thread;
    if (!Handle() && thread.Name() == EIKAPPUI_SERVER_THREAD_NAME)
        {
        return KErrNone;
        }

    TInt ret = ConnectAknServer();
    if (ret == KErrNone)
        {
        ret = SendReceive(EAknSEnableTaskList, TIpcArgs( aEnable ));
        }
    return ret;
    }
    
EXPORT_C TInt RAknUiServer::MakeTaskListVisible(TBool aShow)
    {
    RThread thread;
    if (!Handle() && thread.Name() == EIKAPPUI_SERVER_THREAD_NAME)
        {
        return KErrNone;        
        }

    TInt ret = ConnectAknServer();
    if (ret == KErrNone)
        {
        ret = SendReceive(EAknsLaunchTaskList, TIpcArgs( aShow));
        }
    return ret;
    }
    
EXPORT_C TInt RAknUiServer::UpdateTaskList()
    {
    RThread thread;
    if (!Handle() && thread.Name() == EIKAPPUI_SERVER_THREAD_NAME)
        {
        return KErrNone;
        }

    TInt ret = ConnectAknServer();
    if (ret == KErrNone)
        {
        Send(EAknSRefreshTaskList);
        }
    return ret; 
    }

EXPORT_C TInt RAknUiServer::SetSgcParams(TInt aWgId, TBitFlags aAppFlags, TInt aSpLayout, 
    TInt aSpFlags)
    {
    return SetSgcParams(aWgId, aAppFlags, aSpLayout, aSpFlags, KAknScreenModeUnset);
    }

EXPORT_C TInt RAknUiServer::SetSgcParams(TInt aWgId, TBitFlags aAppFlags, TInt aSpLayout, 
    TInt aSpFlags, TInt aAppScreenMode)
    {
    RThread thread;
    if (!Handle() && thread.Name() == EIKAPPUI_SERVER_THREAD_NAME)
        {
        return KErrNone;        
        }
    
    SAknCapServerSetSgcParams params;
    params.iWgId = aWgId;
    params.iAppFlags = aAppFlags;
    params.iSpLayout = aSpLayout;
    params.iSpFlags = aSpFlags;
    params.iAppScreenMode = aAppScreenMode;
    TPckg<SAknCapServerSetSgcParams> pack(params);

    TIpcArgs args(&pack);
    return SendReceive(EAknEikAppUiSetSgcParams, args);
    }

EXPORT_C TInt RAknUiServer::BlockServerStatusPaneRedraws()
    {
    RThread thread;
    if (!Handle() && thread.Name() == EIKAPPUI_SERVER_THREAD_NAME)
        {
        return KErrNone;        
        }
    
    return SendReceive(EAknEikAppUiBlockServerStatusPaneRedraws,TIpcArgs());
    }

EXPORT_C TInt RAknUiServer::RedrawServerStatusPane()
    {
    RThread thread;
    if (!Handle() && thread.Name() == EIKAPPUI_SERVER_THREAD_NAME)
        {
        return KErrNone;        
        }
    
    return SendReceive(EAknEikAppUiRedrawServerStatusPane,TIpcArgs());
    }

EXPORT_C TInt RAknUiServer::PrepareForAppExit(TInt aWgId)
    {
    RThread thread;
    if (!Handle() && thread.Name() == EIKAPPUI_SERVER_THREAD_NAME)
        {
        return KErrNone;        
        }
    
    TIpcArgs args( aWgId );
    return SendReceive(EAknEikAppUiPrepareForAppExit, args);
    }

EXPORT_C TInt RAknUiServer::SetSystemFaded(TBool aFade)
    {
    RThread thread;
    if (!Handle() && thread.Name() == EIKAPPUI_SERVER_THREAD_NAME)
        {
        return KErrNone;        
        }
    
    TIpcArgs args( aFade );
    return SendReceive(EAknEikAppUiSetSystemFaded, args);
    }

EXPORT_C TInt RAknUiServer::IsSystemFaded(TBool& aFade) const
    {
    RThread thread;
    if (!Handle() && thread.Name() == EIKAPPUI_SERVER_THREAD_NAME)
        {
        return KErrNone;        
        }
    
    TPckg<TBool> pckg(aFade);
    TIpcArgs args( &pckg );
    return SendReceive(EAknEikAppUiIsSystemFaded, args);
    }

EXPORT_C TInt RAknUiServer::Connect()
    {
    RThread thread;
    if (!Handle() && thread.Name() == EIKAPPUI_SERVER_THREAD_NAME)
        {
        return KErrNone;        
        }

    return ConnectAknServer();
    }

EXPORT_C TInt RAknUiServer::RelinquishPriorityToForegroundApp()
    {
    if (!Handle())
        {
        return KErrNone;        
        }
    
    return SendReceive(EAknEikAppUiRelinquishPriorityToForegroundApp);
    }
    
EXPORT_C TInt RAknUiServer::SetStatusPaneFlags(TInt aFlags) const
    {
    RThread thread;
    if (!Handle() && thread.Name() == EIKAPPUI_SERVER_THREAD_NAME)
        {
        return KErrNone;        
        }
        
    return SendReceive(EAknSSetStatusPaneFlags,TIpcArgs(aFlags));
    }

EXPORT_C TInt RAknUiServer::SetStatusPaneLayout(TInt aLayoutResId) const
    {
    RThread thread;
    if (!Handle() && thread.Name() == EIKAPPUI_SERVER_THREAD_NAME)
        {
        return KErrNone;        
        }
        
    return SendReceive(EAknSSetStatusPaneLayout,TIpcArgs(aLayoutResId));
    }

EXPORT_C TInt RAknUiServer::BlankScreen() const
    {
    RThread thread;
    if (!Handle() && thread.Name() == EIKAPPUI_SERVER_THREAD_NAME)
        {
        return KErrNone;        
        }
    
    if ( thread.Name() == KAknNfySrvThreadName )
    //Notifier Server should not blank the screen, if not, flickers show
        {
        return KErrNone;
        }
        
    return SendReceive(EAknSBlankScreen,TIpcArgs());
    }

EXPORT_C TInt RAknUiServer::UnblankScreen() const
    {
    RThread thread;
    if (!Handle() && thread.Name() == EIKAPPUI_SERVER_THREAD_NAME)
        {
        return KErrNone;        
        }
    
    if ( thread.Name() == KAknNfySrvThreadName )
        {
        return KErrNone;        
        }
        
    return SendReceive(EAknSUnblankScreen,TIpcArgs());
    }

EXPORT_C TUid RAknUiServer::ServiceUid() const 
    {
    return KAknCapServiceUid;
    }   

EXPORT_C TInt RAknUiServer::SetKeyboardRepeatRate(TAknDefaultKeyboardRepeatRate aRate)
    {
    RThread thread;
    if (!Handle() && thread.Name() == EIKAPPUI_SERVER_THREAD_NAME)
        {
        return KErrNone;        
        }
        
    return SendReceive(EAknSSetKeyboardRepeatRate,TIpcArgs(aRate));
    }

EXPORT_C TInt RAknUiServer::SetKeyblockMode(TAknKeySoundOpcode aMode)
    {
    RThread thread;
    if (!Handle() && thread.Name() == EIKAPPUI_SERVER_THREAD_NAME)
        {
        return KErrNone;        
        }
        
    return SendReceive(EAknSUpdateKeyBlockMode,TIpcArgs(aMode));
    }

EXPORT_C TInt RAknUiServer::DoEikonServerConnect()
    {
    return ConnectAknServer();
    }

EXPORT_C TInt RAknUiServer::ShowKeysLockedNote(TBool& aIsKeyPadLocked)
    {
    TInt ret = SendReceive(EAknSShowLockedNote);
    if (ret >= 0) // no error 
        {
        aIsKeyPadLocked = ret;    
        ret = KErrNone;
        } 
    return ret;
    }

EXPORT_C void RAknUiServer::ShutdownApps(const TUid aRequesterUID, 
    const TInt aTimeoutInMicroseconds, TRequestStatus& aStatus) const
    {
    TIpcArgs args( aRequesterUID.iUid, aTimeoutInMicroseconds );
    SendReceive(EAknSShutdownApps, args, aStatus);
    }
    
EXPORT_C void RAknUiServer::CancelShutdownApps()
    {
    SendReceive(EAknSCancelShutdownApps);
    }

EXPORT_C TInt RAknUiServer::ShowGlobalNoteL(const TDesC& aNoteText, TInt aGlobalNoteType)
    {
    if (!Handle())
        {
        return KErrNotReady;
        }

    CBufFlat* buffer = CBufFlat::NewL(128);
    CleanupStack::PushL(buffer);
    
    CAknGlobalNote::DoGlobaNoteBufferL(
        aGlobalNoteType,
        0,
        R_AVKON_SOFTKEYS_OK_EMPTY,
        -1,
        -1,
        -1,
        -1,
        EFalse,
        ETrue,
        aNoteText,
        buffer
        );
        
    TPtrC8 bufferPtr;
    bufferPtr.Set(buffer->Ptr(0));
    TPckgBuf<SAknGlobalNoteReturnParams> retPckg;
    TInt ret = SendReceive(EStartNotifier, TIpcArgs(KAknGlobalNoteUid.iUid, &bufferPtr, &retPckg));
    CleanupStack::PopAndDestroy(); // buffer
    return ret;
    }
    
EXPORT_C TInt RAknUiServer::StatusPaneResourceId()
    { 
    if (!Handle()) // either eikon server has not yet connected to aknserver or we are in aknserver   
        {
        return 0; // zero is invalid resource id -> indicates problem accessing sp
        }

    TInt ret = 0;
    TPckg<TInt> pckg(ret);
    TInt err = SendReceive(EAknSStatusPaneResourceId, TIpcArgs(&pckg));
    return ((err == KErrNone)?ret:0);   
    }

EXPORT_C TInt RAknUiServer::CreateActivateViewEventL(const TVwsViewId& aViewId, 
    TUid aCustomMessageId, const TDesC8& aCustomMessage)
    {
    return SendReceive(EAknSLaunchView, TIpcArgs(
        aViewId.iAppUid.iUid,
        aViewId.iViewUid.iUid,
        aCustomMessageId.iUid,
        &aCustomMessage));
    }

EXPORT_C HBufC8* RAknUiServer::GetPackedConfigL() const
    {
    TInt size = 0;
    TPckg<TInt> pckg(size);
    User::LeaveIfError(SendReceive(EAknEikAppUiLayoutConfigSize, TIpcArgs(&pckg)));
    
    HBufC8* buf = HBufC8::NewMaxLC(size);
    TPtr8 ptr = buf->Des();
    User::LeaveIfError(SendReceive(EAknEikAppUiGetLayoutConfig, TIpcArgs(&ptr)));
    
    CleanupStack::Pop(buf);
    return buf;
    }

EXPORT_C TInt RAknUiServer::CurrentAppStatuspaneResource()
    {
    if (!Handle()) // either eikon server has not yet connected to aknserver or we are in aknserver   
        {
        return 0; // zero is invalid resource id -> indicates problem accessing sp
        }

    TInt ret = 0;
    TPckg<TInt> pckg(ret);
    TInt err = SendReceive(EAknSStatusPaneAppResourceId, TIpcArgs(&pckg));
    return ((err == KErrNone)?ret:0);   
    }
    
EXPORT_C TInt RAknUiServer::SetCurrentAppStatuspaneResource(TInt aResourceId)
    {
    RThread thread;
    if (!Handle() && thread.Name() == EIKAPPUI_SERVER_THREAD_NAME)
        {
        return KErrNone;        
        }
        
    return SendReceive(EAknSSetStatusPaneAppResourceId,TIpcArgs(aResourceId));      
    }

EXPORT_C TInt RAknUiServer::RotateScreen()
    {
    return SendReceive(EAknSRotateScreen, TIpcArgs());
    }

EXPORT_C TBool RAknUiServer::TaskSwitchingSupressed()
    {
    if (ConnectAknServer() == KErrNone)
        {
        // Mimics also boolean EFalse, in any error or posivite value we assume that appswitch is 
        // forbidden.
        return !(SendReceive(EAknSAppsKeyBlocked) == KErrNone); 
        }                                                      
    else 
        {
        return ETrue; // Capserver not available -> no app switching allowed either    
        }
    }

EXPORT_C TInt RAknUiServer::ShowLongTapAnimation( const TPointerEvent& aEvent)
    {
    if ( !Handle() )
        {
        return KErrCouldNotConnect;
        }
    
    return SendReceive(
        EAknSShowLongTapAnimation, 
        TIpcArgs(aEvent.iParentPosition.iX, aEvent.iParentPosition.iY));
    }
    
EXPORT_C TInt RAknUiServer::HideLongTapAnimation()
    {
    if ( !Handle() )
        {
        return KErrCouldNotConnect;
        }

    return SendReceive(EAknSHideLongTapAnimation, TIpcArgs());
    }

EXPORT_C TInt RAknUiServer::GetAliasKeyCode(TUint& aCode, const TKeyEvent& aKeyEvent, 
    TEventCode aType)
    {
    TPckgC<TKeyEvent> buf(aKeyEvent);
    TPckg<TUint> pckg(aCode);

    return SendReceive(EAknGetAliasKeyCode, TIpcArgs(&pckg, &buf, aType));
    }

EXPORT_C TInt RAknUiServer::GetPhoneIdleViewId( TVwsViewId& aViewId )
    {
    TPckg<TVwsViewId> pckg(aViewId);
    return SendReceive(EAknSGetPhoneIdleViewId, TIpcArgs(&pckg));
    }

EXPORT_C void RAknUiServer::StartAknCapserverL()
    {
    AknStartupApaServerProcess();
    
    RApaLsSession apa;
    User::LeaveIfError(apa.Connect());
    CleanupClosePushL(apa);

    CApaCommandLine* cmdLine = CApaCommandLine::NewLC();
    cmdLine->SetExecutableNameL( KAknCapServerExecutable );
    cmdLine->SetServerRequiredL(KUikonUidPluginInterfaceNotifiers);
    cmdLine->SetCommandL(EApaCommandBackground);
    TThreadId dummy;
    
    TRequestStatus requestStatusForRendezvous;
    User::LeaveIfError(apa.StartApp(*cmdLine, dummy, &requestStatusForRendezvous));
    User::WaitForRequest(requestStatusForRendezvous);
    User::LeaveIfError(requestStatusForRendezvous.Int());
    CleanupStack::PopAndDestroy(2, &apa);   // cmdLine and apa    
    }


/* Copied from \common\generic\app-framework\apparc\apgrfx\apscli.cpp
 * so that a command line can be passed to apparc.
 */ 
EXPORT_C TInt AknStartupApaServerProcess()
    {
    _LIT(KNameApaImage,"APSEXE");
    const TUid KServerUid3 = { 0x10003A3F };
    const TUidType uidType(KNullUid, KNullUid, KServerUid3);
    
    _LIT(KApaCommandLine, "-IDLE_TIMEOUT_PERIODIC_DELAY_5000");
    RProcess server;
    TInt r = server.Create(KNameApaImage, KApaCommandLine, uidType);
    
    if (r != KErrNone)
        {
        return r;   
        }
    TRequestStatus stat;
    server.Rendezvous(stat);
    if (stat != KRequestPending)
        {
        server.Kill(0);     // abort startup
        }
    else
        {
        server.Resume();    // logon OK - start the server
        }
    User::WaitForRequest(stat); // wait for start or death
    server.Close();
    return stat.Int();
    }

EXPORT_C TInt RAknUiServer::DoNotifierControllerCommand(TInt aNotifierControllerCommand)
    {
    return Send(KDoNotifierControllerCommand, TIpcArgs(aNotifierControllerCommand));
    }

EXPORT_C TInt RAknUiServer::SetFgSpDataSubscriberId(TInt aId)
    {
    RThread thread;
    if (!Handle() && thread.Name() == EIKAPPUI_SERVER_THREAD_NAME)
        {
        return KErrNone;        
        }
    return SendReceive(EAknSetFgSpDataSubscriberId, TIpcArgs(aId));      
    }

EXPORT_C TInt RAknUiServer::PreAllocateDynamicSoftNoteEvent(TInt aNoteId)
    {
    return SendReceive(EAknSPreAllocateDynamicSoftNoteEvent, TIpcArgs(aNoteId));
    }
    
EXPORT_C void RAknUiServer::NotifyDynamicSoftNoteEvent(TRequestStatus& aStatus, TDes8& aActionId)
    {
    TIpcArgs args(&aActionId);
    SendReceive(EAknSNotifyDynamicSoftNoteEvent, args, aStatus);
    }
    
EXPORT_C void RAknUiServer::CancelDynamicSoftNoteEventNotification()
    {
    SendReceive(EAknSCancelDynamicSoftNoteEventNotification, TIpcArgs());
    }
    
EXPORT_C TInt RAknUiServer::MoveAppInZOrder(TInt aAppWindowGroupId, TBool aBackgroundOrForeground)
	{
    return Send(EAknEikAppUiMoveAppInZOrder, TIpcArgs(aAppWindowGroupId, aBackgroundOrForeground));
	}
    

EXPORT_C void RAknUiServer::DoDiscreetPopupAction( 
        TAknDiscreetPopupData* aData, TRequestStatus* aStatus )
    {
    if ( !aData || !Handle() )
        {
        return;
        }

    switch ( aData->Type() )
        {
        // Launch global popup with params
        case ( TAknDiscreetPopupData::EAknPopupTypeParam ):
            {
            TPckg<TAknDiscreetPopupParamData> pkg( 
                    *( static_cast<TAknDiscreetPopupParamData*>( aData ) ) );
            SendReceive( EAknSDiscreetPopupAction, TIpcArgs( &pkg ), *aStatus );
            break;
            }
        // Launch global popup from resources
        case ( TAknDiscreetPopupData::EAknPopupTypeResource ):
            {
            TPckg<TAknDiscreetPopupResourceData> pkg( 
                    *( static_cast<TAknDiscreetPopupResourceData*>( aData ) ) );
            SendReceive( EAknSDiscreetPopupAction, TIpcArgs( &pkg ), *aStatus );
            break;
            }
        // All request cancellation
        case ( TAknDiscreetPopupData::EAknPopupTypeCancelRequest ):
            {
            TPckg<TAknDiscreetPopupCancelRequestData> pkg( 
                    *( static_cast<TAknDiscreetPopupCancelRequestData*>( aData ) ) );
            SendReceive( EAknSDiscreetPopupAction, TIpcArgs( &pkg ) );
            break;
            }
         // Id request
        case ( TAknDiscreetPopupData::EAknPopupTypeUndefined ):
            {
            TPckg<TAknDiscreetPopupData> pkg( 
                    *( static_cast<TAknDiscreetPopupData*>( aData ) ) );
            SendReceive( EAknSDiscreetPopupAction, TIpcArgs( &pkg ) );
            break;    
            }
        // Query the rect of global discreet popup in use
        case ( TAknDiscreetPopupData::EAknPopupTypeQueryInUseRect ):
            {
            TPckg<TAknDiscreetPopupRectData> pkg(
                    *( static_cast<TAknDiscreetPopupRectData*>( aData ) ) );
            SendReceive( EAknSDiscreetPopupAction, TIpcArgs( &pkg ) );
            break;
            }        
        default:
            {
            break;
            }
        }
    }

// ---------------------------------------------------------------------------
// RAknUiServer::GetInUseGlobalDiscreetPopupRect
// ---------------------------------------------------------------------------
//
EXPORT_C const TRect RAknUiServer::GetInUseGlobalDiscreetPopupRect()
    {
    TAknDiscreetPopupRectData rectData(TRect::EUninitialized);
    DoDiscreetPopupAction( static_cast<TAknDiscreetPopupData*>(&rectData),NULL);
    return rectData.Rect();            
    }

// End of file
