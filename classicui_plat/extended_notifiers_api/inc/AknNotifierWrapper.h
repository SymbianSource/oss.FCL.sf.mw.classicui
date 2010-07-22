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
* Description:  Notifier server app wrapper definition.
*
*/

#ifndef __AKNNOTIFIERSERVERAPPWRAPPER_H__
#define __AKNNOTIFIERSERVERAPPWRAPPER_H__

#include <eiknotapi.h>
#include <eikserverapp.h>
#include <AknNotifierWrapperDefs.h>
#include <e32notif.h>

// FORWARD DECLARATIONS
class CAknNotifierMessageObserver;

/**
 * Avkon notifier wrapper interface.
 *
 * Abstract class for accessing an object implementing actual client-session to Notifier 
 * App Server.
 *
 * @lib aknnotifierwrapper.lib
 * @since S60 v3.0
 */   
class MAknNotifierWrapper
    {
public:
    /**
     * Command session owning object to update a notifier with given uid
     * Method is synchronous. On error leaves with standard Symbian OS error code.
     * @since 3.0
     * @param aNotifierUid Notifier to be updated
     * @param aBuffer Buffer from RNotifier client
     * @return Return package from app server. Implementation specific.
     */
    virtual TPtrC8 UpdateNotifierL( TUid aNotifierUid, const TDesC8& aBuffer) = 0;
    
    /**
     * Command session owning object to cancel a notifier with given uid
     * Method is synchronous
     * @since 3.0
     * @param aNotifierUid Notifier to be cancelled
     */
    virtual void CancelNotifier( TUid aNotifierUid ) = 0;

    /**
     * Command session owning object to start a notifier with given uid
     * Method is asynchronous. On error leaves with standard Symbian OS error code.
     * @since 3.0
     * @param aNotifierUid Notifier to be started
     * @param aBuffer Buffer from RNotifier client
     * @param aReplySlot to which slot plugin will write its reply 
     * @param aMessage Message into which reply is written when async request is completed
     */
    virtual void StartNotifierL( 
        TUid aNotifierUid, 
        const TDesC8& aBuffer, 
        TInt aReplySlot, 
        const RMessagePtr2& aMessage) = 0;

    /**
     * Command session owning object to start a notifier with given uid
     * Method is synchronous. On error leaves with standard Symbian OS error code.
     * @since 3.0
     * @param aNotifierUid Notifier to be started
     * @param aBuffer Buffer from RNotifier client
     * @return Return package from app server. Implementation specific.
     */
    virtual TPtrC8 StartNotifierL( TUid aNotifierUid, const TDesC8& aBuffer) = 0;
    
    /**
     * Return unique identifier of server application implmenting the service
     * @since 3.0
     * @return refrence to Uid
     */
    virtual const TUid& AppServerUid() const = 0;
    
    /**
     * Return reference to buffer used in syncronous commands to store reply before sending 
     * it to client.
     * @since 3.0
     * @return refrence to synch reply buffer
     */
    virtual TPtr8 SynchronousReplyBuf() = 0;          

    /**
     * Callback method, called when async request from app server completes. 
     * @since 3.0
     * @param aEntry queue object which was completed by app server. Called before FW
     * completes request from client using RNotifier.
     * Instance implementing this API, may complete the message during this method if default 
     * implementation is not suitable (just writes the reply from client to replyslot given) 
     */
    virtual void AsyncMessageCompleted( CAknNotifierMessageObserver* aEntry ) = 0;
    
    /**
     * Command session owning object to update a notifier with given uid
     * Method is asynchronous. On error leaves with standard Symbian OS error code.
     * 
     * This method was added to 3.2 and in order to preserve SC it has a default
     * implementation which leaves with @c KErrNotSupported. 
     *
     * @since 3.2
     * @param aNotifierUid Notifier to be updated
     * @param aBuffer      Buffer from RNotifier client
     * @param aReplySlot   To which slot plugin will write its reply 
     * @param aMessage     Message into which reply is written when async request is completed
     */
    IMPORT_C virtual void UpdateNotifierL( 
        TUid aNotifierUid, 
        const TDesC8& aBuffer, 
        TInt aReplySlot, 
        const RMessagePtr2& aMessage);
    };

class CAknCommonNotifierWrapper;

// Class implementing queue entry for asynchronous requests. 
// Deletion of an entry is possible only by completing the request status of entry. 
class CAknNotifierMessageObserver : public CActive
    {
public:
    /**
     * Creates new queue entry which combines message from client using RNotifier
     * to an asynchronous app server requests. When app server completes TRequestStatus of this 
     * entry callback AsyncMessageCompleted() will be called.
     * On error leaves with standard Symbian OS error code.
     * @since 3.0
     * @param aNotifierUid Notifier to be started
     * @param aOwner Object which will be notified when request is complete
     * @param aClientMessage Message into which reply is written when async request is completed
     * @param aReplySlot Index to which reply will be copied.
     * @return New queue entry ready for use.
     */
    IMPORT_C static CAknNotifierMessageObserver* NewServerRequestL(
        TUid aNotifierUid, 
        MAknNotifierWrapper* aOwner, 
        const RMessagePtr2& aClientMessage, 
        TInt aReplySlot);    
    
    void Start(){ CActive::SetActive(); };

private:
    ~CAknNotifierMessageObserver();   
         
    CAknNotifierMessageObserver( 
        TUid aNotifierUid, 
        MAknNotifierWrapper* aOwner, 
        const RMessagePtr2& aClientMessage, 
        TInt aReplySlot);

private: // from CActive     
    void RunL();
    void Cancel();  
    void DoCancel();

    // Offer access for owning class, it may complete the message if default implementation 
    // is not suitable for its purposes.
public: 
    TUid iNotifierUid;
    HBufC8* iReplyBuf;
    TPtr8* iReplyDesc; // cannot be constructed otherwise
    HBufC8* iInputBuf;        
    RMessagePtr2 iMessage;
    TInt iReplySlot;
    
private: // data    
    MAknNotifierWrapper* iOwner; // not owned
    }; 

// Simple client to App Server. Internal to Avkon.
class RAknNotifierAppServClient : public REikAppServiceBase
    {
public:
    RAknNotifierAppServClient();
    void SetServerAppUid(TUid aAppServerUid);
    TUid ServiceUid() const;
    
    TInt SendSync(
        TNotifierMessage aFunction, 
        TUid aNotifierUid, 
        const TDesC8& aBuffer, 
        TPtr8 aReply, 
        const TDesC& aLibraryName);
        
    void SendAsync(TNotifierMessage aFunction, 
        TUid aNotifierUid, 
        const TDesC8& aBuffer, 
        CAknNotifierMessageObserver* aQueueEntry, 
        const TDesC& aLibraryName);
        
    TInt StartServer(); // or rather connect
    TInt SendAsync(TInt aNotifierControllerFunction);
    void SetOwnerUsingMonitor(CAknCommonNotifierWrapper* aOwner)
        {
        iOwnerUsingMonitor = aOwner;
        }
        
private:
    void StartServerL();
    TUid iAppServerUid;
    CAknCommonNotifierWrapper* iOwnerUsingMonitor;
    };    


// Ligthweight implementation of MEikSrvNotifierBase2.
// Instances cannot access app server directly but only via session owning instace which 
// implemets MAknNotifierWrapper API.
class CAknNotifierWrapperLight : public CBase, public MEikSrvNotifierBase2
    {
public:    
    IMPORT_C ~CAknNotifierWrapperLight();
    /**
     * Constructor. Requires reference to a session owning instance (MAknNotifierWapper 
     * derived). 
     * 
     * @since 3.0 
     * @param aSessionOwningNotifier Object which provides the actual client server session
     *                               to app server.
     * @param aNotifierUid Uid of this notifier, returned in Info()
     * @param aChannel Channel uid of this notifier, returned in Info()
     * @param aPriority Priority of this notifier, see declaration of MEikSrvNotifierBase2, 
     *                  returned in Info()
     */
    IMPORT_C CAknNotifierWrapperLight(
        MAknNotifierWrapper& aSessionOwningNotifier, 
        TUid aNotifierUid, 
        TUid aChannel, 
        TInt aPriority );
   
public:
    // from MEikSrvNotifierBase2
    IMPORT_C TPtrC8 UpdateL(const TDesC8& aBuffer);
    IMPORT_C void Cancel();
    IMPORT_C void StartL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage);
    IMPORT_C TPtrC8 StartL(const TDesC8& aBuffer);                              
    IMPORT_C TNotifierInfo Info() const;        
    IMPORT_C TNotifierInfo RegisterL();  
    IMPORT_C TInt NotifierCapabilites(); // just base calls currently

   /**
    * Cancels asynchronous requests and deletes instance.
    */ 
   IMPORT_C void Release();
   
   /**
    * Updates a currently active notifier with new data.
    *
    * @since S60 3.2
    *
    * @param   aBuffer    Data from the client side.
    * @param   aReplySlot Identifies which message argument to use for the reply.
    * @param   aMessage   Encapsulates the client request.
    */
    IMPORT_C void UpdateL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage);

private:
    MAknNotifierWrapper& iOwner;
    TNotifierInfo iInfo;
    TAny* iSpare;
    };
   
// Class implementing both session to AppServer and MEikSrvNotifierBase (CAknNotifierWrapperLight). 
class CAknNotifierWrapper : public CAknNotifierWrapperLight,  public MAknNotifierWrapper
    {
public:   // for convenience, no need to derive if default implementation is enough
    /**
     * Static constructor. This does not connect (nor create) app server, but the server is created 
     * when RegisterL is being called by Symbian FW. Real connection to app server is formed during
     * first actual notifier request
     * 
     * @since 3.0 
     * @param aNotifierUid Uid of this notifier, returned in Info()
     * @param aChannel Channel uid of this notifier, returned in Info()
     * @param aPriority Priority of this notifier, see declaration of MEikSrvNotifierBase2, returned
     *                  in Info()
     * @param aAppServerUid Uid of App Server to connect (implementation specific)
     * @param aReplyBufSize Size of a reply buffer used in synchrouns notifier requests
     */
    IMPORT_C static CAknNotifierWrapper* NewL(  
        TUid aNotifierUid, 
        TUid aChannel, 
        TInt aPriority, 
        TUid aAppServerUid, 
        TUint aReplyBufSize);
                
    const TUid& AppServerUid() const {return iAppServerUid;}
    TPtr8 SynchronousReplyBuf(){return iReplyBuffer->Des();}
    
protected: // c'tor  
    /**
     * Constructor. Intended only for derivation. Uses AppServerUid() to initialize iAppServerUid. 
     * 
     * @since 3.0 
     * @param aNotifierUid Uid of this notifier, returned in Info()
     * @param aChannel Channel uid of this notifier, returned in Info()
     * @param aPriority Priority of this notifier, see declaration of MEikSrvNotifierBase2, 
     *                  returned in Info().
     */
    IMPORT_C CAknNotifierWrapper(TUid aNotifierUid, TUid aChannel, TInt aPriority);   
    
public: //  d'tor  
    IMPORT_C ~CAknNotifierWrapper();

public: // from CAknNotifierWrapperLight  
    // This effectively starts server immediately after eiksrv construction has been completed.
    IMPORT_C TNotifierInfo RegisterL(); 

public: // from MAknNotifierWrapper
    IMPORT_C TPtrC8 UpdateNotifierL(TUid aNotifierUid, const TDesC8& aBuffer);
    IMPORT_C void CancelNotifier(TUid aNotifierUid);
    
    IMPORT_C void StartNotifierL( 
        TUid aNotifierUid, 
        const TDesC8& aBuffer, 
        TInt aReplySlot, 
        const RMessagePtr2& aMessage);
        
    IMPORT_C TPtrC8 StartNotifierL(TUid aNotifierUid, const TDesC8& aBuffer);          
    IMPORT_C void AsyncMessageCompleted(CAknNotifierMessageObserver* aEntry);
    
    IMPORT_C void UpdateNotifierL( 
        TUid aNotifierUid, 
        const TDesC8& aBuffer, 
        TInt aReplySlot, 
        const RMessagePtr2& aMessage);
    
public: // for generic notifier window controller
    IMPORT_C void DoNotifierControllerCommand(TInt aCommand);

protected:
    void SetSynchReplybuf(HBufC8* aReplyBuffer)
        {
        delete iReplyBuffer;
        iReplyBuffer = aReplyBuffer;
        }
       
    RAknNotifierAppServClient& Client()
        {
        return iClient;
        }
       
    CAknNotifierMessageObserver* CreateNewQueueEntryL( 
        TUid aNotifierUid, 
        const TDesC8& aBuffer, 
        TInt aReplySlot, 
        const RMessagePtr2& aMessage);   
  
private: // internal utilities 
    // Completes all requests with matching uid with given reason.
    void CompleteOutstandingRequests( TUid aNotifierUid, TInt aReason );    
    void ConstructL(TUint aReplyBufSize);    

private: // for convenience methods needs 
    CAknNotifierWrapper( 
        TUid aNotifierUid, 
        TUid aChannel, 
        TInt aPriority, 
        TUid aAppServerUid); 

private: // data
    RAknNotifierAppServClient iClient;
    //CApaServerAppExitMonitor* iServerExitMonitor;
    RPointerArray<CAknNotifierMessageObserver> iMessageQueue;
    HBufC8* iReplyBuffer;
    TUid iAppServerUid;        
    }; 
 
 
class MAknNotifierCustomSecurityCheck
    {
public:
    // releases resources allocated (usually: delete this)
    virtual void Release()=0;
    // Called from asynch StartL() other places we don't have access to actual message.
    virtual void CustomSecurityCheckL(const RMessagePtr2& aMessage) = 0;
    }; 
 
 
class CAknCommonNotifierWrapper : public CAknNotifierWrapper, public MApaServerAppExitObserver
    {
public:
    /**
     * Static constructor. This does not connect (nor create) app server, but the server is created 
     * when RegisterL is being called by Symbian FW. Real connection to app server is formed during 
     * first actual notifier request.
     * 
     * @since 3.1 
     * @param aNotifierUid Uid of this notifier, returned in Info().
     * @param aChannel Channel uid of this notifier, returned in Info().
     * @param aPriority Priority of this notifier, see declaration of MEikSrvNotifierBase2, 
     *                  returned in Info().
     * @param aReplyBufSize Size of a reply buffer used in synchrouns notifier requests.
     */
    IMPORT_C static CAknCommonNotifierWrapper* NewL( 
        TUid aNotifierUid, 
        TUid aChannel, 
        TInt aPriority, 
        const TDesC& aLibraryName, 
        TUint aReplyBufSize,
        TBool aPreload = EFalse ); 

    /**
     * Sets custom security checking object, ownership taken. When ever notifier wrapper receives a 
     * command with actual message message is first passed to given object.
     * 
     * If callback (CustomSecurityCheckL()) does not leave, it is assumed that security checking 
     * was successfully passed.
     * 
     * @since 3.1 
     * @param aNotifierUid Uid of this notifier, returned in Info().
     */
    IMPORT_C void SetCustomSecurityHandler(MAknNotifierCustomSecurityCheck* aHandler);

    
    /**
     * Loads the notifier plugin once app server is available. Keeps this plugin (aLibraryName 
     * in constructor).
     * always loaded
     * 
     * @since 3.1 
     * @param aNotifierUid Uid of this notifier, returned in Info().
     */    
    IMPORT_C void PreLoadLibraryL();
    
    // callback 
    TBool PreLoadLibrary();
    
    ~CAknCommonNotifierWrapper();

public: // from base class
    const TUid& AppServerUid() const {return KCommonNotifierAppSrvUid;}
    
    void StartNotifierL( 
        TUid aNotifierUid, 
        const TDesC8& aBuffer, 
        TInt aReplySlot, 
        const RMessagePtr2& aMessage );
        
    TPtrC8 StartNotifierL( TUid aNotifierUid, const TDesC8& aBuffer );          
    void CancelNotifier( TUid aNotifierUid );
    TNotifierInfo RegisterL();
    
public: // callback from client once server is connected 
    void AppServerConnectedL();    

    // Introduce to this namespace to avoid possible conflicts
    struct TPendingMsg
        {
        TPendingMsg(TUid uid, const RMessagePtr2& msg): iUid(uid.iUid),iMessage(msg){}
        TInt iUid;
        RMessagePtr2 iMessage;
        };

private:
    // from MApaServerAppExitObserver
    void HandleServerAppExit(TInt aReason);    

    void ConstructL(const TDesC& aLibraryName, TUint aReplyBufSize);
    
    CAknCommonNotifierWrapper( 
        TUid aNotifierUid, 
        TUid aChannel, 
        TInt aPriority,
        TBool aPreLoad);
                    
    HBufC* iLibraryName;
    MAknNotifierCustomSecurityCheck* iCustomSecurityCheck;
    CIdle* iIdle;
    TBool iPreLoad;
    CApaServerAppExitMonitor* iMonitor;
    RArray<TPendingMsg> iPendingArray;
    }; 
 
#endif // __AKNNOTIFIERSERVERAPPWRAPPER_H__
 
// End of file
 