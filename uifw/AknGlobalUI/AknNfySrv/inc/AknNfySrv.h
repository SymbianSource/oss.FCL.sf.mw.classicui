/*
* Copyright (c) 2004-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  AknNfySrv session and server declaration.
*
*/

#ifndef __AKNNFYSRV_H__
#define __AKNNFYSRV_H__

#include <AknNotifierAppServerSession.h>
#include <AknNotifierAppServer.h>
#include <akndialogcontroller.h>

class CAknNfySrvSession;
class CAknNotifierEntry;
class CAknNotifLibraryEntry;

class CAknNfySrv: public CAknNotifierAppServer, public MNotifLibraryOwningServer
    {   
    public:  // from CEikAppServer
        CApaAppServiceBase* CreateServiceL(TUid aServiceType) const;
    
    public: 
        ~CAknNfySrv();
        void LoadLibraryL(HBufC* aLibName);
        void AddNotifiersFromLibL(CAknNotifLibraryEntry* aNewLib);
        void HandleClientExit(CAknNfySrvSession* aSession);
        CAknNotifierEntry* FindEntry(TUid aUid) const;
        TBool CheckReferenceCount(const TDesC& aLibName, TBool aIncrease);
        void UnloadLibrary(TUid aNotifierUid);
    
        // from MNotifLibraryOwningServer
        MEikSrvNotifierBase2* FindImplementation(TUid aUid) const;
        
        void StartNotifierL(TUid aNotifierUid,const TDesC8& aBuffer,TDes8& aResponse);
        void CancelNotifier(TUid aNotifierUid);
        
        void StartNotifierAndGetResponseL(
            TUid aNotifierUid, 
            TDesC8& aBuffer, 
            const RMessagePtr2& aMsg, 
            TInt aReplySlot);
            
        void DoUnload(const TDesC& aLibName);
        void CheckPendingRemovalsL();
    
        RPointerArray<CAknNotifierEntry> iNotifierArray;
        RPointerArray<CAknNotifLibraryEntry> iLibraryArray;
        CIdle* iLibraryRemover;
    
    private: // from MNotifLibraryOwningServer
        void UnbalanceReferenceCount(TUid aUid, TBool aAddCount);
        void NotifierExtension(TUid aExtensionUid, TAny*& aGenParam);
    };
    

class CAknNfySrvSession: public CAknNotifierServerAppService
    {
    public: 
        CAknNfySrvSession(const CAknNfySrv* aAppServer)
            :CAknNotifierServerAppService((const CAknNotifierAppServer&) *aAppServer), 
            iServer((CAknNfySrv*)aAppServer)
            {
            }
            
        ~CAknNfySrvSession()
            {
            iServer->HandleClientExit(this);            
            }
    
    public: // From base classes.    
        /**
         * From CAknNotifierServerAppService.
         * Actual message handling, this method commands server to do notifier operations based on
         * received message. ServiceL calls this method if client has passed AllowClientL checking
         * 
         * @since 3.0 
         * @param aMessage Message from client.
         */      
        void HandleMessageL(const RMessage2& aMessage);
                
    private:    
        CAknNfySrv* iServer; 
    };


#endif // __AKNCAPSERVER_H__
 
// End of file
 
