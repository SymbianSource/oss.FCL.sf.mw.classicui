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
* Description:  AknCapServer session and server declaration.
*
*/

#ifndef __AKNCAPSERVER_H__
#define __AKNCAPSERVER_H__

#include <AknNotifierAppServerSession.h>
#include <AknNotifierAppServer.h>
#include <akndialogcontroller.h>

class CAknCapAppServerAppUi;
class CAknCapServerSession;
class CAknCapServerShutdown;
class CAknLongTapAnimation;
class TVwsViewId;
class CAknDynamicSoftNoteEventManager;

class CAknCapServer : public CAknNotifierAppServer
    {   
    public:  // from CEikAppServer
        CApaAppServiceBase* CreateServiceL(TUid aServiceType) const;
    
    public: 
        ~CAknCapServer();
        void KillAppL(const RMessage2& aMessage);
        void DoTaskListCommandL(const RMessage2& aMessage);
        void SuppressAppsKeyL(const RMessage2& aMessage, CAknCapServerSession* aClient);
        void HandleClientExit(CAknCapServerSession* aClient);
        inline void CheckAndLoadLibrariesL();
        void HideApplicationFromFWSL(const RMessage2& aMessage);
        void HandleMMCRequestL(const RMessage2& aMessage, TInt aClientId );
        void SetStatusPaneFlags(TInt aFlags);
        void SetStatusPaneLayoutL(TInt aResourceId);
        void BlankScreenL();
        void UnblankScreenL();
        
        void SetSgcParamsL(
            TInt aWgId, 
            TBitFlags aAppFlags, 
            TInt aSpLayout, 
            TInt aSpFlags, 
            TInt aAppScreenMode);
            
        void PrepareForAppExitL(TInt aWgId);
        // awkward but true
        CNotifierDialogController* GlobalNoteControllerL()
            {
            CheckAndLoadLibrariesL(); // ensures that global notes queue is instantiated
            return iGlobalNoteController;
            }
        void SetGlobalNoteController(CNotifierDialogController* aCont)
            {
            iGlobalNoteController = aCont;
            }
        void ShutdownAppsL(const RMessage2& aMessage);
        void CancelShutdownAppsL();
        void CreateActivateViewL(const RMessage2& aMessage);
        void RelinquishPriorityToForegroundAppL(const RMessage2& aMessage);
        void SetCurrentAppStatuspaneResourceIdL(TInt aResourceId);
        TInt CurrentAppStatuspaneResourceIdL(); 
        void RotateScreenL();
        void DoAskAppsKeyStatusL(const RMessage2& aMessage);
        void ShowLongTapAnimationL(const TInt aX, const TInt aY);
        void HideLongTapAnimation();
        void GetAliasKeyCodeL(TUint& aCode, const TKeyEvent& aKeyEvent, TEventCode aType);
        void SetFgSpDataSubscriberIdL(TInt aId);
        void GetPhoneIdleViewId( TVwsViewId& aViewId );
        void RefreshLongTapAnimation();
        void CreateDynamicSoftNoteEventManagerL();
        CAknDynamicSoftNoteEventManager* DynamicSoftNoteEventManager();
        
    private:
        void EnsureAppUiValidityL();
        
    private:
        CNotifierDialogController* iGlobalNoteController; // not owned
        CAknCapAppServerAppUi* iAppUi; // not owned
        TBool iLibrariesLoaded;
        __MUTABLE RLibrary iLibrary;
        CAknCapServerShutdown* iShutdown;
        CAknLongTapAnimation* iLongTapAnimation;
        CAknDynamicSoftNoteEventManager* iDynamicSoftNoteEventManager;
    };
   

class CAknCapServerSession : public CAknNotifierServerAppService
   {
   public: 
       CAknCapServerSession(const CAknCapServer* aAppServer)
       :CAknNotifierServerAppService((const CAknNotifierAppServer&) *aAppServer), 
       iServer((CAknCapServer*)aAppServer)
           {
           }
       ~CAknCapServerSession()
           {
           for (TInt ii=0; ii<iBlankCount; ii++)
               {
               TRAP_IGNORE(iServer->UnblankScreenL());
               }
           iServer->HandleClientExit(this);            
           }
   
   public: // From CAknNotifierServerAppService    
       /**
       * ServiceL calls this method to decide whether the message will be served or not.
       * Default implementation just checks that client is eikon server thread, other 
       * clients are not served.
       * @since 3.0 
       * @param aMessage Message from client.
       * @return Boolean, is a client allowed to access our services.
       */      
       TBool AllowClientL(const RMessage2& aMessage);

       /**
       * Actual message handling, this method commands server to do notifier operations based on
       * received message. ServiceL calls this method if client has passed AllowClientL checking.
       * 
       * @since 3.0 
       * @param aMessage Message from client.
       */      
       void HandleMessageL(const RMessage2& aMessage);
               
   private:    
       CAknCapServer* iServer; 
       TInt iBlankCount;
   };

inline void CAknCapServer::CheckAndLoadLibrariesL()
    {
    if (!iLibrariesLoaded)
        {
        AppendNotifierLibNameL(_L("AknOldStyleNotif.DLL"));
        LoadNotifiersL();   
        iLibrariesLoaded = ETrue;
        }
    }

#endif // __AKNCAPSERVER_H__
 
// End of file
 