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
* Description:  AknCapServer Server and Session implementation 
*
*/

#include <AknNotifierWrapperDefs.h>
#include <aknconsts.h>
#include <aknanimdllstd.h>
#include <AknCapServerClient.h>
#include <baclipb.h>
#include "AknCapServerDefs.h"
#include "AknCapServerEntry.h"
#include "AknCapServer.h"
#include "AknMemoryCardDialogImpl.h"
#include "AknCapServerShutdown.h"
#include "akndynamicsoftnoteeventmanager.h"
#include <AknNotifierControllerPlugin.h>
#include <aknlongtapanimation.h>
#include <AknDef.h>
#include "akncapserverdiscreetpopuphandler.h"

NONSHARABLE_CLASS(CAknAlarmInterface): public CAknAppServiceBase, public MAknAlarmServiceStartup
    {
    };

const TInt KEikonServerSecureId = 0x10003A4A;
    
TBool  CAknCapServerSession::AllowClientL(const RMessage2& /*aMessage*/)
    {
    return ETrue;
    }

void  CAknCapServerSession::HandleMessageL(const RMessage2& aMessage)
    {   
    switch (aMessage.Function())
        {
        case EAknSLaunchView:
            {
            // completes the message
            iServer->CreateActivateViewL(aMessage);
            }
            break;
        case EAknSKillApp:
        case EAknSKillAllApps:
            iServer->KillAppL(aMessage);
            break;
        case EAknSUnlockMedia:
            iServer->HandleMMCRequestL(aMessage, REINTERPRET_CAST(TInt,this));          
            break;
        case EAknSEnableTaskList:
        case EAknsLaunchTaskList:
        case EAknSRefreshTaskList:
            iServer->DoTaskListCommandL(aMessage);
            break;
        case EAknSSuppressAppsKey:
            if (aMessage.SecureId() != KEikonServerSecureId)
                {
                // WriteDeviceData required if client is not eiksrv.                    
                aMessage.HasCapabilityL(ECapabilityWriteDeviceData); 
                }
            iServer->SuppressAppsKeyL(aMessage,this);
            break;
        case EAknSHideApplicationFromFWS:
            iServer->HideApplicationFromFWSL(aMessage);
            break;        
        case EAknSSetStatusPaneFlags:
            {
            iServer->SetStatusPaneFlags(aMessage.Int0());
            aMessage.Complete(KErrNone);
            }
            break;
        case EAknSSetStatusPaneLayout:
            {
            iServer->SetStatusPaneLayoutL(aMessage.Int0());
            aMessage.Complete(KErrNone);
            }
            break;
        case EAknSBlankScreen:
            {
            iBlankCount++;
            TRAPD(err, iServer->BlankScreenL());
            aMessage.Complete(err);
            }
            break;
        case EAknSUnblankScreen:
            {
            iBlankCount--;
            iServer->UnblankScreenL();
            aMessage.Complete(KErrNone);
            }
            break;
        case EAknEikAppUiSetSgcParams:
            {
            TPckgBuf<SAknCapServerSetSgcParams> paramsBuf;
            aMessage.ReadL(0, paramsBuf);
            const SAknCapServerSetSgcParams& params = paramsBuf();
            
            iServer->SetSgcParamsL(
                params.iWgId, 
                params.iAppFlags, 
                params.iSpLayout, 
                params.iSpFlags, 
                params.iAppScreenMode);
                
            aMessage.Complete(KErrNone);
            }
            break;
        case EAknEikAppUiBlockServerStatusPaneRedraws:
            {
            aMessage.Complete(KErrNone);
            }
            break;
        case EAknEikAppUiRedrawServerStatusPane:
            {
            CAknSgcClient::RedrawServerStatusPane();
            aMessage.Complete(KErrNone);
            }
            break;
        case EAknEikAppUiPrepareForAppExit:
            {
            iServer->PrepareForAppExitL(aMessage.Int0());
            aMessage.Complete(KErrNone);
            }
            break;
        case EAknEikAppUiSetSystemFaded:
            {
            TBool isFaded(aMessage.Int0());
            CCoeEnv *env = CCoeEnv::Static();
            CAknAppUi *appUi = static_cast<CAknAppUi*>(env->AppUi());
            
            if (!isFaded 
                && appUi->IsDisplayingMenuOrDialog() 
                && env->RootWin().OrdinalPriority() >= ECoeWinPriorityAlwaysAtFront
                && env->RootWin().Identifier() == env->WsSession().GetFocusWindowGroup())
                {
                // Don't unfaded the sytem, because in this case the requesting client application
                // already go back to the background just after staying in the foreground
                // for quite few moment, and the cap server return to the foreground again
                // when a sleeping dialog poped up in global note.
                }
            else
                {
                CAknSgcClient::SetSystemFaded(isFaded);
                }
            
            aMessage.Complete(KErrNone);
            }
            break;
        case EAknEikAppUiIsSystemFaded:
            {
            TBool fade = CAknSgcClient::IsSystemFaded();
            TPckg<TBool> pckg(fade);
            aMessage.WriteL(0, pckg);
            aMessage.Complete(KErrNone);
            }
            break;
        case EAknEikAppUiRelinquishPriorityToForegroundApp:
            {
            iServer->RelinquishPriorityToForegroundAppL(aMessage);
            }
            break;
        case EAknEikAppUiLayoutConfigSize:
            {
            TInt size = CAknSgcClient::LayoutConfigBuf().Size();
            TPckg<TInt> pckg(size);
            aMessage.WriteL(0, pckg);
            aMessage.Complete(KErrNone);
            }
            break;
        case EAknEikAppUiGetLayoutConfig:
            {
            const TDesC8& buf = CAknSgcClient::LayoutConfigBuf();
            aMessage.WriteL(0, buf);
            aMessage.Complete(KErrNone);
            }
            break;
        case EAknEikAppUiMoveAppInZOrder:
            {
            CAknSgcClient::MoveApp(aMessage.Int0(), (TSgcMoveAppToWhere)aMessage.Int1());
            aMessage.Complete(KErrNone);
            }
            break;
        case EAknSSetKeyboardRepeatRate:
            {
            CAknSgcClient::SetKeyboardRepeatRate((TAknDefaultKeyboardRepeatRate)aMessage.Int0());    
            aMessage.Complete(KErrNone);
            break;
            }
        case EAknSUpdateKeyBlockMode:
            {
            CAknSgcClient::SetKeyBlockMode((TAknKeySoundOpcode)aMessage.Int0());
            aMessage.Complete(KErrNone);
            break;
            }
        case EAknSShowLockedNote:
            {
            CEikonEnv* env = CEikonEnv::Static();
            RWsSession& wsSession = env->WsSession();
            TInt myWgId = env->RootWin().Identifier();
            // if keylock is active, we have special wg priority
            if (wsSession.GetWindowGroupOrdinalPriority(myWgId) == ECoeWinPriorityAlwaysAtFront+1)
                {
                TKeyEvent key;
                key.iCode=EKeyCBA2;
                key.iModifiers=0;
                key.iRepeats=0;
                env->SimulateKeyEventL(key, EEventKey);
                aMessage.Complete(ETrue);               
                }
             else
                {
                aMessage.Complete(EFalse);                  
                }   
            break;    
            }
        case EAknSShutdownApps:
            {
            if (aMessage.SecureId() != KEikonServerSecureId)
                {
                // PowerMgmt required if client is not eiksrv.                    
                aMessage.HasCapabilityL(ECapabilityPowerMgmt); 
                }
            //Empty clipboard here
            RFs& fs = CEikonEnv::Static()->FsSession();
            CClipboard* cb=0;
            TRAPD(err, 
                { 
                cb = CClipboard::NewForWritingLC(fs);
                CleanupStack::Pop();
                }); // end of trap
            
            if (!err)
                {
                cb->Clear(fs);
                }
            delete cb;

            iServer->ShutdownAppsL(aMessage);
            break;
            }
        case EAknSCancelShutdownApps:
            {
            if (aMessage.SecureId() != KEikonServerSecureId)
                {
                // PowerMgmt required if client is not eiksrv.                    
                aMessage.HasCapabilityL(ECapabilityPowerMgmt); 
                }
            iServer->CancelShutdownAppsL();
            aMessage.Complete(KErrNone);
            break;
            }
        case EAknSStatusPaneResourceId:
            {   
            TInt id = CAknSgcClient::CurrentStatuspaneResource();
            TPckg<TInt> pckg(id);
            aMessage.WriteL(0, pckg);
            aMessage.Complete(KErrNone);
            break;
            }
        case EAknSStatusPaneAppResourceId:
            {   
            TInt id = iServer->CurrentAppStatuspaneResourceIdL();
            TPckg<TInt> pckg(id);
            aMessage.WriteL(0, pckg);
            aMessage.Complete(KErrNone);
            break;
            }
        case EAknSSetStatusPaneAppResourceId:
            {   
            iServer->SetCurrentAppStatuspaneResourceIdL(aMessage.Int0());
            aMessage.Complete(KErrNone);
            break;
            }
        case EAknSetFgSpDataSubscriberId:
            {   
            iServer->SetFgSpDataSubscriberIdL(aMessage.Int0());
            aMessage.Complete(KErrNone);
            break;
            }
        case EAknSRotateScreen:
            {
            iServer->RotateScreenL();
            aMessage.Complete(KErrNone);
            break;
            }
        case EAknSAppsKeyBlocked:
            {
            iServer->DoAskAppsKeyStatusL(aMessage);
            break;
            }
        case EAknSShowLongTapAnimation:
            {
            iServer->ShowLongTapAnimationL(aMessage.Int0(), aMessage.Int1());
            aMessage.Complete(KErrNone);
            break;
            }
        case EAknSHideLongTapAnimation:
            {
            iServer->HideLongTapAnimation();
            aMessage.Complete(KErrNone);
            break;
            }
        case EAknGetAliasKeyCode:
            {
            TUint code = 0;
            TPckgBuf<TKeyEvent> keyEvent;
            aMessage.ReadL(1,keyEvent);
            iServer->GetAliasKeyCodeL(code, keyEvent(), (TEventCode)aMessage.Int2());
            aMessage.WriteL(0,TPckg<TUint>(code));
            aMessage.Complete(KErrNone);
            break;    
            }
        case EAknSGetPhoneIdleViewId:
            {
            TPckgBuf<TVwsViewId> id;
            aMessage.ReadL(0, id); 
            iServer->GetPhoneIdleViewId(id());
            aMessage.WriteL(0, id);
            aMessage.Complete(KErrNone);
            break;
            }
        case EAknSPreAllocateDynamicSoftNoteEvent:
            {
            iServer->DynamicSoftNoteEventManager()->RegisterEventL(this, aMessage);            
            break;
            }
        case EAknSNotifyDynamicSoftNoteEvent:
            {
            iServer->DynamicSoftNoteEventManager()->NotifyEvent(this, aMessage);
            break;
            }
        case EAknSCancelDynamicSoftNoteEventNotification:
            {
            iServer->DynamicSoftNoteEventManager()->CancelEvent(this, aMessage);
            break;
            }
        case EAknSDiscreetPopupAction:
            {
            CAknCapServerDiscreetPopupHandler::HandleDiscreetPopupMessageL( aMessage );
            break;
            }
        case KDoNotifierControllerCommand:
            {
            if (aMessage.SecureId() != KEikonServerSecureId)
                {
                User::Leave(KErrPermissionDenied);
                }
                
            CAknCapAppServerAppUi* appUi = (CAknCapAppServerAppUi*) CEikonEnv::Static()->AppUi();
            if (appUi && appUi->iGlobalNotesController)
                {
                switch(aMessage.Int0())
                    {
                case CAknNotifierControllerUtility::EDoAllow:
                    appUi->iGlobalNotesController->KeyLockStatusChange(EKeyLockAllowNotifications);
                    break;
                case CAknNotifierControllerUtility::EDoStop:
                    appUi->iGlobalNotesController->KeyLockStatusChange(EKeyLockStopNotifications);
                    break;
                case CAknNotifierControllerUtility::DoCancelAll:
                    appUi->iGlobalNotesController->KeyLockStatusChange(EKeyLockCancelNotification);
                    break;
                default:
                    break;
                    }
                }            
            } // fall through
        case ECancelNotifier:   // check if cancel (from TNotifierMessage)
            {
            RThread t;
            aMessage.ClientL(t);

            // store client information to appui
            CAknCapAppServerAppUi* appUi = (CAknCapAppServerAppUi*) CEikonEnv::Static()->AppUi();
            appUi->iClientId = t.Id();
            
            t.Close();
            } // fall through
        default:
            iServer->CheckAndLoadLibrariesL();
            // base call
            CAknNotifierServerAppService::HandleMessageL(aMessage);
            break;      
            }
    }

CApaAppServiceBase* CAknCapServer::CreateServiceL(TUid aServiceType) const
    {
    // We provide place alarm library that can't run with eikon server capabilities.
    if (aServiceType == KAknAlarmServiceUid)
        { // There can't be more than one instance of this service running
        __ASSERT_DEBUG(iLibrary.Handle() == 0, User::Invariant());
        RLibrary& library = MUTABLE_CAST(RLibrary&, iLibrary);
        User::LeaveIfError(library.Load(KAknAlarmServiceLibrary));
        TLibraryFunction constructor = library.Lookup(1);
        MAknAlarmServiceStartup* alarm = (MAknAlarmServiceStartup*)((*constructor)());
        User::LeaveIfNull(alarm);
        alarm->StartupNewSessionL();
        return (CAknAlarmInterface*)alarm;
        }   
    else if ( aServiceType == KAknCapServiceUid || aServiceType == KAknNotifierServiceUid )
        {
        return new (ELeave) CAknCapServerSession(this);
        }
    else 
        {
        return CAknNotifierAppServer::CreateServiceL(aServiceType); 
        }   
    }

void CAknCapServer::KillAppL(const RMessage2& aMessage)
    {
    EnsureAppUiValidityL();
    iAppUi->KillAppL(aMessage);
    }

void CAknCapServer::DoTaskListCommandL(const RMessage2& aMessage)
    {
    EnsureAppUiValidityL();
    iAppUi->DoTaskListCommandL(aMessage);   
    }

void CAknCapServer::SuppressAppsKeyL(const RMessage2& aMessage, CAknCapServerSession* aClient )
    {
    EnsureAppUiValidityL();
    iAppUi->SuppressAppSwitchingL(aMessage.Int0(),REINTERPRET_CAST(TInt,aClient));
    aMessage.Complete(KErrNone);
    }

void CAknCapServer::HandleClientExit(CAknCapServerSession* aClient)
    { // not allowed to leave 
    if (iAppUi)
        { // can't leave when aAddCount == 0
        TInt clientId = REINTERPRET_CAST(TInt,aClient);
        TRAP_IGNORE(iAppUi->SuppressAppSwitchingL(EAknAppsKeyBlockRemoveClient, clientId));
        iAppUi->MMCUnlock()->ClientExit( clientId );
        }
    if (iDynamicSoftNoteEventManager)
        {
        iDynamicSoftNoteEventManager->ClientExit(aClient);
        }
    }

void CAknCapServer::EnsureAppUiValidityL()
    {
    if (!iAppUi)
        {
        iAppUi = (CAknCapAppServerAppUi*) CEikonEnv::Static()->EikAppUi();
        }
    
    if (!iAppUi)
        {
        User::Leave(KErrNotReady);      
        }
    }

void CAknCapServer::HideApplicationFromFWSL(const RMessage2& aMessage )
    {
    EnsureAppUiValidityL();
    iAppUi->HideApplicationFromFswL(aMessage.Int0(),aMessage.Int1());
    aMessage.Complete(KErrNone);
    }

void CAknCapServer::HandleMMCRequestL(const RMessage2& aMessage, TInt aClientId )
    {
    if (aMessage.Int0() == 0) // not cancel
        { // owner ship of message to dialog
        EnsureAppUiValidityL();
        iAppUi->MMCUnlock()->StartL(aMessage.Int1(), aMessage.Int2(), aMessage, aClientId);
        }
    else
        {
        TRAPD(err,  EnsureAppUiValidityL())
        if (!err)
            {
            iAppUi->MMCUnlock()->Cancel(aClientId);
            }
        aMessage.Complete(KErrNone);
        }
    }

void CAknCapServer::SetSgcParamsL(TInt aWgId, TBitFlags aAppFlags, TInt aSpLayout, TInt aSpFlags, 
    TInt aAppScreenMode)
    {
    EnsureAppUiValidityL();
    
    iAppUi->SgcServer()->HandleWindowGroupParamChangeL(
        aWgId, 
        aAppFlags, 
        aSpLayout, 
        aSpFlags, 
        aAppScreenMode);
    }

void CAknCapServer::PrepareForAppExitL(TInt aWgId)
    {
    EnsureAppUiValidityL();
    iAppUi->SgcServer()->PrepareForAppExitL(aWgId);
    }

void CAknCapServer::RelinquishPriorityToForegroundAppL(const RMessage2& aMessage)
    {
    EnsureAppUiValidityL();
    iAppUi->SgcServer()->RelinquishPriorityToForegroundAppL(aMessage);
    }

void CAknCapServer::SetStatusPaneFlags(TInt aFlags)
    {
    if (iAppUi && iAppUi->StatusPane())
        {
        iAppUi->StatusPane()->SetFlags(aFlags);
        }
    }

void CAknCapServer::SetStatusPaneLayoutL(TInt aResourceId)
    {
    EnsureAppUiValidityL(); 
    if (iAppUi->StatusPane())
        {
        iAppUi->StatusPane()->SwitchLayoutL(aResourceId);
        }
    }
    
void CAknCapServer::BlankScreenL()
    {
    EnsureAppUiValidityL(); 
    iAppUi->BlankScreenL(ETrue);
    }
    
void CAknCapServer::UnblankScreenL()
    {
    EnsureAppUiValidityL(); 
    iAppUi->BlankScreenL(EFalse);
    }

CAknCapServer::~CAknCapServer()
    {
    delete iDynamicSoftNoteEventManager;
    delete iShutdown;
    iLibrary.Close();
    delete iLongTapAnimation;
    }

void CAknCapServer::ShutdownAppsL(const RMessage2& aMessage)
    {
    delete iShutdown;
    iShutdown = 0;
    iShutdown = new(ELeave) CAknCapServerShutdown;
    iShutdown->ConstructL();

    TUid uid = { aMessage.Int0() };
    TInt timeout = aMessage.Int1();
    iShutdown->ShutdownAppsL(uid, aMessage, timeout);
    }
    
void CAknCapServer::CancelShutdownAppsL()
    {
    if (iShutdown)
        {
        iShutdown->CancelShutdownAppsL();
        }
    }

// For applications that do not have CCoeAppUI ready or available.
void CAknCapServer::CreateActivateViewL(const RMessage2& aMessage)
    {
    EnsureAppUiValidityL(); 
    TInt messageLength = aMessage.GetDesLengthL(3);
    TInt appUid = aMessage.Int0();
    TInt viewUid = aMessage.Int1();
    TInt customUid = aMessage.Int2(); 
    if (messageLength > 0)
        {
        HBufC8* buf = HBufC8::NewLC(messageLength);        
        TPtr8 ptr = buf->Des();
        aMessage.ReadL(3, ptr);
        
        iAppUi->CreateActivateViewEventL(
            TVwsViewId(TUid::Uid(appUid), TUid::Uid(viewUid)),
            TUid::Uid(customUid),
            *buf);
            
        CleanupStack::PopAndDestroy();
        }
    else
        {
        iAppUi->CreateActivateViewEventL(
            TVwsViewId(TUid::Uid(appUid),TUid::Uid(viewUid)),
            TUid::Uid(customUid),
            KNullDesC8());        
        }
    aMessage.Complete(KErrNone);
    }

void CAknCapServer::SetCurrentAppStatuspaneResourceIdL(TInt aResourceId)
    {
    EnsureAppUiValidityL(); 
    iAppUi->SetCurrentAppStatuspaneResourceIdL(aResourceId);
    }

TInt CAknCapServer::CurrentAppStatuspaneResourceIdL()
    {
    EnsureAppUiValidityL(); 
    return iAppUi->CurrentAppStatuspaneResourceIdL();
    }

void CAknCapServer::SetFgSpDataSubscriberIdL(TInt aId)
    {
    EnsureAppUiValidityL(); 
    iAppUi->SetFgSpDataSubscriberIdL(aId);
    }

void CAknCapServer::RotateScreenL()
    {
    iAppUi->RotateScreenL();
    }

void CAknCapServer::DoAskAppsKeyStatusL(const RMessage2& aMessage)
    {
    EnsureAppUiValidityL();
    aMessage.Complete(iAppUi->IsAppsKeySuppressed());    
    }           

void CAknCapServer::ShowLongTapAnimationL( const TInt aX, const TInt aY )
    {    
    if ( !iLongTapAnimation )
        {
        iLongTapAnimation = CAknLongTapAnimation::NewL();
        }
    iLongTapAnimation->ShowAnimationL( aX, aY );
    }

void CAknCapServer::HideLongTapAnimation()
    {
    if ( iLongTapAnimation )
        {
        iLongTapAnimation->HideAnimation();
        }
    }
void CAknCapServer::GetAliasKeyCodeL(TUint& aCode, const TKeyEvent& aKeyEvent, TEventCode aType)
    {
    EnsureAppUiValidityL();
    iAppUi->GetAliasKeyCodeL(aCode,aKeyEvent,aType);
    }

void CAknCapServer::GetPhoneIdleViewId( TVwsViewId& aViewId )
    {
    AknDef::GetPhoneIdleViewId( aViewId );
    }

void CAknCapServer::RefreshLongTapAnimation()
    {
    delete iLongTapAnimation;
    iLongTapAnimation = NULL;
    }
    
void CAknCapServer::CreateDynamicSoftNoteEventManagerL()
    {
    if(!iDynamicSoftNoteEventManager)
        {
        iDynamicSoftNoteEventManager = CAknDynamicSoftNoteEventManager::CreateUniqueInstanceL();
        }
    }
    
CAknDynamicSoftNoteEventManager* CAknCapServer::DynamicSoftNoteEventManager()
    {
    return iDynamicSoftNoteEventManager;
    }

// End of file
