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
* Description:  Notifier server app wrapper implementation.
*
*/

#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uiklaf/private/pluginuid.hrh>
#include <uikon/eiknotifyalert.h>
#endif
#include <apgtask.h>
#include <apgcli.h>
#include <apacmdln.h>
#include <coemain.h>
#include <uikon/eiksrvui.h>
#include "AknNotifierWrapper.h"
#include "AknNotifierControllerUtilities.h"
#include <AknNotifierControllerPlugin.h>
#include <AknCapServerDefs.h>

const TInt KPreLoadEnabledButNotDoneYet(2);

//-------------------------------------------
// CAknNotifierMessageObserver
//-------------------------------------------    
 
CAknNotifierMessageObserver::CAknNotifierMessageObserver(TUid aNotifierUid, 
    MAknNotifierWrapper* aOwner, 
    const RMessagePtr2& aClientMessage, 
    TInt aReplySlot)
:CActive(CActive::EPriorityStandard), 
    iNotifierUid(aNotifierUid), 
    iReplySlot(aReplySlot), 
    iOwner(aOwner)
    {
    iMessage = aClientMessage;
    CActiveScheduler::Add(this);       
    }
 
 
EXPORT_C CAknNotifierMessageObserver* CAknNotifierMessageObserver::NewServerRequestL(
    TUid aNotifierUid, 
    MAknNotifierWrapper* aOwner, 
    const RMessagePtr2& aClientMessage, 
    TInt aReplySlot)
    {
    CAknNotifierMessageObserver* me = 
        new (ELeave) CAknNotifierMessageObserver(aNotifierUid,aOwner,aClientMessage,aReplySlot);
    
    // a bit awkward I admit...
    if (!aClientMessage.IsNull())
        {
        CleanupStack::PushL(me);
        me->iReplyBuf = HBufC8::NewL(aClientMessage.GetDesLength(aReplySlot));
        // we need ptr which keeps its address during async operation
        me->iReplyDesc = new (ELeave) TPtr8(me->iReplyBuf->Des());
        CleanupStack::Pop();

        // just in case: if notifier implementation wants to transmit data via replybuf for 
        // some reason
        aClientMessage.Read(aReplySlot,*(me->iReplyDesc));  
        }
        
    return me;    
    }
 
 
CAknNotifierMessageObserver::~CAknNotifierMessageObserver()
    {
    delete iReplyDesc;
    delete iReplyBuf;
    delete iInputBuf;
    __ASSERT_DEBUG(!IsActive(), User::Invariant() );
    }
  
void CAknNotifierMessageObserver::DoCancel()
    {
    if (iOwner)
        {
        iOwner->AsyncMessageCompleted( this );
        }

    if (!iMessage.IsNull())
        {
        iMessage.Complete(KErrCancel);
        }

    User::WaitForRequest(iStatus);
    delete this;
    }
 
void CAknNotifierMessageObserver::RunL()
    {
    if (iOwner)
        {// offer message from app-server for wrapper to clone
        iOwner->AsyncMessageCompleted( this );
        }

    // if Owner did not complete the message, do default reply 
    if (!iMessage.IsNull())
        {
        TInt err = iMessage.Write(iReplySlot,iReplyBuf->Des());
        iMessage.Complete(err?err:iStatus.Int());
        }
    delete this;
    }

//-------------------------------------------
// MAknNotifierWrapper
//-------------------------------------------  

// Default implementation to avoid SC break.
EXPORT_C void MAknNotifierWrapper::UpdateNotifierL( 
    TUid /*aNotifierUid*/,
    const TDesC8& /*aBuffer*/,
    TInt /*aReplySlot*/, 
    const RMessagePtr2& /*aMessage*/ )
    {
    User::Leave( KErrNotSupported );
    }
 
//-------------------------------------------
// CAknNotifierWrapperLight
//-------------------------------------------    
EXPORT_C CAknNotifierWrapperLight::~CAknNotifierWrapperLight()
    {
    }
 
EXPORT_C CAknNotifierWrapperLight::CAknNotifierWrapperLight(
    MAknNotifierWrapper& aSessionOwningNotifier, 
    TUid aNotifierUid, 
    TUid aChannel, 
    TInt aPriority )
:iOwner(aSessionOwningNotifier)
    {
    iInfo.iUid = aNotifierUid;
    iInfo.iChannel = aChannel;
    iInfo.iPriority = aPriority;   
    }
    

EXPORT_C TPtrC8 CAknNotifierWrapperLight::UpdateL(const TDesC8& aBuffer)
    {
    return iOwner.UpdateNotifierL( iInfo.iUid, aBuffer );
    }
    
EXPORT_C void CAknNotifierWrapperLight::UpdateL(const TDesC8& aBuffer, TInt aReplySlot, 
    const RMessagePtr2& aMessage)
    {
    iOwner.UpdateNotifierL( iInfo.iUid, aBuffer, aReplySlot, aMessage );
    }

EXPORT_C void CAknNotifierWrapperLight::Cancel()
    {
    iOwner.CancelNotifier(iInfo.iUid);
    }
        
EXPORT_C void CAknNotifierWrapperLight::StartL(const TDesC8& aBuffer, TInt aReplySlot, 
    const RMessagePtr2& aMessage)
    {
    iOwner.StartNotifierL(iInfo.iUid, aBuffer, aReplySlot, aMessage);
    }
    
EXPORT_C TPtrC8 CAknNotifierWrapperLight::StartL(const TDesC8& aBuffer)
    {
    return iOwner.StartNotifierL(iInfo.iUid, aBuffer);
    }
        
EXPORT_C MEikSrvNotifierBase2::TNotifierInfo CAknNotifierWrapperLight::Info() const
    {
    return iInfo;    
    }
        
EXPORT_C MEikSrvNotifierBase2::TNotifierInfo CAknNotifierWrapperLight::RegisterL()
    {
    return iInfo;    
    }
  
EXPORT_C void CAknNotifierWrapperLight::Release()
    {
    Cancel();
    delete this;
    }

EXPORT_C TInt CAknNotifierWrapperLight::NotifierCapabilites()
    {
    return MEikSrvNotifierBase2::NotifierCapabilites();
    }
    
//-------------------------------------------
// CAknNotifierWrapper
//-------------------------------------------    

EXPORT_C CAknNotifierWrapper::CAknNotifierWrapper(TUid aNotifierUid, TUid aChannel, TInt aPriority)
    :CAknNotifierWrapperLight(*this, aNotifierUid, aChannel, aPriority)
    {
    iClient.SetServerAppUid(AppServerUid());
    }
    
CAknNotifierWrapper::CAknNotifierWrapper(TUid aNotifierUid, TUid aChannel, TInt aPriority, 
    TUid aAppServerUid)
:CAknNotifierWrapperLight(*this, aNotifierUid, aChannel, aPriority), iAppServerUid(aAppServerUid)
    {
    iClient.SetServerAppUid(iAppServerUid);
    }
     

EXPORT_C CAknNotifierWrapper::~CAknNotifierWrapper()
    {
    CEikServAppUi* appUi = (CEikServAppUi*)CCoeEnv::Static()->AppUi();
    if (appUi && appUi->NotifierController())
        {
        appUi->NotifierController()->RegisterNotifierControllerPlugin(this, ETrue);
        }
    
    delete iReplyBuffer;
    
    // Make sure that there are no pending messages
    __ASSERT_DEBUG(iMessageQueue.Count()==0, User::Invariant());
    
    iClient.Close();
    }

// We use CEikServAppUi idle queue to launch application servers (applications will be started after 
// eiksrv-construction has been completed )
EXPORT_C MEikSrvNotifierBase2::TNotifierInfo CAknNotifierWrapper::RegisterL()
    {
    CEikServAppUi* appUi = (CEikServAppUi*)CCoeEnv::Static()->AppUi();
    if (appUi)
        {
        if (AppServerUid()!=KAknCapServerUid) // aknCapServer is handled elsewhere
            {
            appUi->StartNewServerApplicationL(AppServerUid());
            }
        
        appUi->NotifierController()->RegisterNotifierControllerPlugin(this, EFalse);
        }
    return CAknNotifierWrapperLight::RegisterL();    
    }

 
EXPORT_C TPtrC8 CAknNotifierWrapper::UpdateNotifierL( TUid aNotifierUid, const TDesC8& aBuffer)
    {
    User::LeaveIfError(iClient.SendSync(EUpdateNotifier, aNotifierUid, aBuffer, 
        SynchronousReplyBuf(), KNullDesC));
        
    return TPtrC8(SynchronousReplyBuf()); 
    }

EXPORT_C void CAknNotifierWrapper::UpdateNotifierL( TUid aNotifierUid, const TDesC8& aBuffer, 
    TInt aReplySlot, const RMessagePtr2& aMessage)
    {    
    CAknNotifierMessageObserver* entry = 
        CreateNewQueueEntryL(aNotifierUid, aBuffer, aReplySlot, aMessage);
        
    if (entry)
        {
        iClient.SendAsync(EUpdateNotifierAndGetResponse, aNotifierUid,*entry->iInputBuf, entry, 
            KNullDesC);
        }        
    }
    
void CAknNotifierWrapper::CompleteOutstandingRequests( TUid aNotifierUid, TInt aReason )
    {
    for ( TInt i = 0; i < iMessageQueue.Count(); i++ )
        {
        if (iMessageQueue[i]->iNotifierUid == aNotifierUid)
            {
            // This leaves listener to active state, it will be destroyed when a message in
            // Notifier server application is completed. 
            // Effectively this means that plugin can't send any data inside message which is 
            // being cancelled.
            if (!iMessageQueue[i]->iMessage.IsNull())
                {
                iMessageQueue[i]->iMessage.Complete(aReason);               
                }
            }
        }
    }
    
EXPORT_C void CAknNotifierWrapper::CancelNotifier( TUid aNotifierUid )
    {
    iClient.SendSync(ECancelNotifier, aNotifierUid, KNullDesC8, SynchronousReplyBuf(), KNullDesC);
    CompleteOutstandingRequests( aNotifierUid, KErrCancel);
    }


CAknNotifierMessageObserver* CAknNotifierWrapper::CreateNewQueueEntryL(TUid aNotifierUid, 
    const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage)
    {
    CAknNotifierMessageObserver* entry = 0;
    if (!aMessage.IsNull())
        {
        entry = CAknNotifierMessageObserver::NewServerRequestL(aNotifierUid, this, aMessage, 
            aReplySlot);
            
        CleanupStack::PushL(entry);
        entry->iInputBuf = aBuffer.AllocL();
        CleanupStack::Pop();
        TInt err = iMessageQueue.Append(entry);  
        if (err)
            { // completes client message with err;
            TRequestStatus* ptr = &entry->iStatus;
            User::RequestComplete(ptr, err);
            entry = 0;
            }
        }
    return entry;
    }

EXPORT_C void CAknNotifierWrapper::StartNotifierL( TUid aNotifierUid, const TDesC8& aBuffer, 
    TInt aReplySlot, const RMessagePtr2& aMessage)
    {    
    CAknNotifierMessageObserver* entry = 
        CreateNewQueueEntryL(aNotifierUid, aBuffer, aReplySlot, aMessage);
        
    if (entry)
        {
        iClient.SendAsync(
            EStartNotifierAndGetResponse, 
            aNotifierUid, 
            *entry->iInputBuf, 
            entry, 
            KNullDesC);        
        }        
    }

EXPORT_C TPtrC8 CAknNotifierWrapper::StartNotifierL( TUid aNotifierUid, const TDesC8& aBuffer)
    {
    User::LeaveIfError(iClient.SendSync(EStartNotifier, aNotifierUid, aBuffer, 
        SynchronousReplyBuf(), KNullDesC));      
        
    return TPtrC8(SynchronousReplyBuf());     
    }

// Just remove completed entry from queue, default completion (ie. just copying message from 
// app server) is currently enough for us. 
EXPORT_C void CAknNotifierWrapper::AsyncMessageCompleted( CAknNotifierMessageObserver* aEntry )
    {
    TInt status = aEntry->iStatus.Int();

    TInt index = iMessageQueue.Find(aEntry);
    if (index != KErrNotFound)
        {
        iMessageQueue.Remove(index);    
        }     

    if ( status == KErrServerTerminated && AppServerUid() != KCommonNotifierAppSrvUid)
        { // Just try to restart (connect on next request), not interested if success or fail
          //
          // We could clone the original message here and resend it to server
          // if information was really vital for system
        Client().Close();    
        Client().SetHandle(0);
        
        TRAP_IGNORE(((CEikServAppUi*)CCoeEnv::Static()->AppUi())->StartNewServerApplicationL(
            AppServerUid()));    
        }
    }

EXPORT_C CAknNotifierWrapper* CAknNotifierWrapper::NewL( 
    TUid aNotifierUid, 
    TUid aChannel, 
    TInt aPriority, 
    TUid aAppServerUid, 
    TUint aReplyBufSize)
    {
    CAknNotifierWrapper* me = 
        new (ELeave) CAknNotifierWrapper(aNotifierUid, aChannel, aPriority, aAppServerUid);
        
    CleanupStack::PushL(me);
    me->ConstructL(aReplyBufSize);
    CleanupStack::Pop();
    return me;
    }
    
EXPORT_C void CAknNotifierWrapper::DoNotifierControllerCommand(TInt aCommand)
    {
    iClient.SendAsync(aCommand);
    }
                                    
void CAknNotifierWrapper::ConstructL(TUint aReplyBufSize)
    {
    iReplyBuffer = HBufC8::NewL(aReplyBufSize);
    }

RAknNotifierAppServClient::RAknNotifierAppServClient()
    :iAppServerUid(KNullUid), iOwnerUsingMonitor(0)
    {       
    }   
 
void RAknNotifierAppServClient::SetServerAppUid(TUid aAppServerUid)
    {
    iAppServerUid = aAppServerUid;   
    }
 
TInt RAknNotifierAppServClient::StartServer()
    {
    TRAPD(ret, StartServerL())        
    return ret;
    }
 
void RAknNotifierAppServClient::StartServerL()
    {
    if (Handle() != 0)
        {
        return;
        }
            
    if (iAppServerUid == KNullUid)
        {
        User::Leave(KErrGeneral);
        }

    _LIT(KServerNameFormat, "%08x_%08x_AppServer");
    TFullName serverName;
    serverName.Format(KServerNameFormat, KUikonUidPluginInterfaceNotifiers, iAppServerUid);
    TFindServer find(serverName);
    TFullName fullName;
    if (find.Next(fullName) == KErrNone)
        {
        ConnectExistingByNameL(serverName); 
        if (iOwnerUsingMonitor)
            {
            iOwnerUsingMonitor->AppServerConnectedL();
            }
        return;
        }

    User::Leave(KErrNotReady);
    }
    
TUid RAknNotifierAppServClient::ServiceUid() const
    {
    return KAknNotifierServiceUid;
    }
    
TInt RAknNotifierAppServClient::SendSync(TNotifierMessage aFunction, TUid aNotifierUid, 
    const TDesC8& aBuffer, TPtr8 aReply, const TDesC& aLibraryName)
    {
    // just an optimisation
    if (aFunction == ECancelNotifier && !Handle())
        {
        return KErrNone;
        }
    
    TInt err = StartServer();
    return err ? err : SendReceive(aFunction, TIpcArgs((TInt)aNotifierUid.iUid, &aBuffer, &aReply, 
        &aLibraryName));
    }
 
void RAknNotifierAppServClient::SendAsync(TNotifierMessage aFunction, TUid aNotifierUid, 
    const TDesC8& aBuffer, CAknNotifierMessageObserver* aQueueEntry, const TDesC& aLibraryName)
    {
    TInt err = StartServer();

    aQueueEntry->Start();  
    if (err)
        {
        TRequestStatus* sptr= &aQueueEntry->iStatus;
        User::RequestComplete(sptr, err);
        return;
        }
    // we implicitely trust that aLibraryName will exist when data is extracted at other end...    
    SendReceive(
        aFunction, 
        TIpcArgs((TInt)aNotifierUid.iUid, &aBuffer, aQueueEntry->iReplyDesc, &aLibraryName), 
        aQueueEntry->iStatus);
    }

TInt RAknNotifierAppServClient::SendAsync(TInt aNotifierControllerCommand)
    {
    if (Handle()!=0)
        {
        return Send(KDoNotifierControllerCommand, TIpcArgs(aNotifierControllerCommand));
        }
        
    // omit error as there is no need to forward commands to server apps which are not running yet.
    return KErrNone; 
    }

EXPORT_C CAknCommonNotifierWrapper* CAknCommonNotifierWrapper::NewL( 
    TUid aNotifierUid, 
    TUid aChannel, 
    TInt aPriority, 
    const TDesC& aLibraryName, 
    TUint aReplyBufSize,
    TBool aPreLoad)
    {
    CAknCommonNotifierWrapper* me = 
        new (ELeave) CAknCommonNotifierWrapper(aNotifierUid, aChannel, aPriority, aPreLoad);
        
    CleanupStack::PushL(me);
    me->ConstructL(aLibraryName, aReplyBufSize);
    CleanupStack::Pop();   
    return me;
    }

void CAknCommonNotifierWrapper::ConstructL(const TDesC& aLibraryName, TUint aReplyBufSize)
    {
    SetSynchReplybuf(HBufC8::NewL(aReplyBufSize));
    iLibraryName = aLibraryName.AllocL();
    Client().SetOwnerUsingMonitor(this);
    }

CAknCommonNotifierWrapper::CAknCommonNotifierWrapper( 
    TUid aNotifierUid, 
    TUid aChannel, 
    TInt aPriority,
    TBool aPreLoad)
:CAknNotifierWrapper(aNotifierUid, aChannel, aPriority), iPreLoad(aPreLoad)
    {
    Client().SetServerAppUid(AppServerUid());
    if (aPreLoad)
        {
        iPreLoad = KPreLoadEnabledButNotDoneYet;
        }
    }

EXPORT_C void CAknCommonNotifierWrapper::SetCustomSecurityHandler(
    MAknNotifierCustomSecurityCheck* aHandler)
    {
    iCustomSecurityCheck = aHandler;
    }

CAknCommonNotifierWrapper::~CAknCommonNotifierWrapper()
    {
    delete iMonitor;
    delete iIdle;
    if (iCustomSecurityCheck)
        {
        iCustomSecurityCheck->Release();
        }
    delete iLibraryName;
    iPendingArray.Close();
    }

void CAknCommonNotifierWrapper::StartNotifierL( TUid aNotifierUid, const TDesC8& aBuffer, 
    TInt aReplySlot, const RMessagePtr2& aMessage)
    {
    if (iPreLoad == KPreLoadEnabledButNotDoneYet) // only preload libs to support message queue
        {
        iPendingArray.AppendL(TPendingMsg(aNotifierUid, aMessage));
        return;
        }

    if (iCustomSecurityCheck)
        {
        iCustomSecurityCheck->CustomSecurityCheckL(aMessage);
        }
    
    CAknNotifierMessageObserver* entry = 
        CreateNewQueueEntryL(aNotifierUid, aBuffer, aReplySlot, aMessage);
        
    if (entry)
        {
        Client().SendAsync(
            EStartNotifierAndGetResponse, 
            aNotifierUid,
            *entry->iInputBuf,
            entry, 
            *iLibraryName);        
        }        
    }

TPtrC8 CAknCommonNotifierWrapper::StartNotifierL( TUid aNotifierUid, const TDesC8& aBuffer)          
    {
    if (iPreLoad == KPreLoadEnabledButNotDoneYet) 
        {              
        // In case of synchronous commands (start / update) we cannot delay sending messages,
        // only way to recover is to return error. Update cannot occur before one successfull 
        // start so it does need changes.
        User::Leave(KErrNotReady); 
        }

    User::LeaveIfError(Client().SendSync(EStartNotifier, aNotifierUid, aBuffer, 
        SynchronousReplyBuf(), *iLibraryName));      
    
    return TPtrC8(SynchronousReplyBuf());     
    }

TBool CallBackLoad(TAny* aThis)
    {
    return ((CAknCommonNotifierWrapper*)aThis)->PreLoadLibrary();
    }
 
EXPORT_C void CAknCommonNotifierWrapper::PreLoadLibraryL()
    {
    iPreLoad = ETrue; // restore original, real boolean value once callback from server arrives
    if (!iIdle)
        {
        iIdle = CIdle::NewL(CActive::EPriorityIdle);
        iIdle->Start(TCallBack(CallBackLoad, this));
        }
    }

// On succes this method will cause unbalanced reference count in app server -> library will not be 
// unloaded unless server terminates.
TBool CAknCommonNotifierWrapper::PreLoadLibrary()
    {
    TInt err = Client().SendSync(
        (TNotifierMessage)EAknNfySrvLoadLibrary, 
        KNullUid, 
        KNullDesC8, 
        SynchronousReplyBuf(), 
        *iLibraryName);
        
    if (err == KErrNotReady)
        {
        return ETrue;
        }
    else
        {
        delete iIdle;
        iIdle = 0;  
        return EFalse;  
        }
    }
    
MEikSrvNotifierBase2::TNotifierInfo CAknCommonNotifierWrapper::RegisterL()
    {
    if (iPreLoad)
        {
        CEikServAppUi* appUi = (CEikServAppUi*)CCoeEnv::Static()->AppUi();
        if (appUi)
            {
            appUi->NotifierController()->RegisterPreloadPluginL(this);
            }
        }
    return CAknNotifierWrapper::RegisterL();
    }


void CAknCommonNotifierWrapper::HandleServerAppExit(TInt)
    {
    delete iMonitor;
    iMonitor = 0;
    Client().Close();    
    Client().SetHandle(0);
    if (iPreLoad)
        {
        iPreLoad = KPreLoadEnabledButNotDoneYet;
        }
    }

void CAknCommonNotifierWrapper::CancelNotifier( TUid aNotifierUid )
    {
    // if there are pending requests, there cannot be actual connection to server yet
    if (iPendingArray.Count())
        {
        for (TInt i = iPendingArray.Count()-1; i >= 0; i--)
            {
            if (iPendingArray[i].iUid == aNotifierUid.iUid)
                {
                iPendingArray.Remove(i);
                }
            }
        }
    else
        {
        CAknNotifierWrapper::CancelNotifier( aNotifierUid );
        }        
    }

void TryProcessPendingEntryL(CAknCommonNotifierWrapper::TPendingMsg& aPendingEntry, 
    CAknCommonNotifierWrapper* aThis)
    {
    HBufC8* buf = HBufC8::NewLC(aPendingEntry.iMessage.GetDesLengthL(1));
    TPtr8 ptr = buf->Des();
    aPendingEntry.iMessage.ReadL(1, ptr );
    aThis->StartNotifierL(TUid::Uid(aPendingEntry.iUid), *buf, 2, aPendingEntry.iMessage );
    CleanupStack::PopAndDestroy();            
    }

void CAknCommonNotifierWrapper::AppServerConnectedL()
    {
    if (!iMonitor)
        {
        iMonitor = CApaServerAppExitMonitor::NewL(Client(), *this, CActive::EPriorityStandard);   
        }
        
    for (TInt i = 0; i < iPendingArray.Count(); i++)
        { // common app servers have no problem with asynch message slots
        // anyway, we don't allow pending messages to abort StartServerL so trap needed 
        TRAP_IGNORE(TryProcessPendingEntryL(iPendingArray[i], this));
        }
        
    iPendingArray.Reset();    
    }

// End of file
