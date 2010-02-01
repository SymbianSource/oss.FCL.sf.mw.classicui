/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Handles dynamic soft notification events.
*
*/

#ifndef AKNDYNAMICSOFTNOTEEVENTMANAGER_H
#define AKNDYNAMICSOFTNOTEEVENTMANAGER_H

#include <e32base.h>

/// Panic category
_LIT(KAknPanicCategory, "AknSNoteEventMgr");

/// Panic values
enum TAknEventMgrPanics
    {
    /// Event manager instance already exists.
    EAknEventMgrPanicEventManagerAlreadyExists,        
    /// Client already registered.
    EAknEventMgrPanicAlreadyRegistered,
    /// Client not registred and trying to get notifications.
    EAknEventMgrPanicNotRegistered,
    /// Bad message received.
    EAknEventMgrPanicBadMessage,
    /// Client sent a duplicate notify message
    EAknEventMgrPanicDuplicateNotify,
    };

/**
 * Event manager for dynamic soft notifications.
 *
 * @lib AknDynamicSoftNoteEventManager.lib
 * @since S60 3.2
 * @internal
 */
NONSHARABLE_CLASS(CAknDynamicSoftNoteEventManager) : public CBase
    {
public:
    /**
     * Creates a unique dynamic soft note event manager instance. 
     *
     * This method must be called only once, subsequent calls result 
     * EAknEventMgrPanicEventManagerAlreadyExists panic.
     *
     * @return New event manager instance.
     */    
    IMPORT_C static CAknDynamicSoftNoteEventManager* CreateUniqueInstanceL();
    
    /**
     * Returns unique dynamic soft note event manager instance.
     *
     * @return Dynamic soft note event manager instance, if it exists. NULL otherwise.
     */ 
    IMPORT_C static CAknDynamicSoftNoteEventManager* UniqueInstance();
    
    /**
     * Destructor.
     */
    virtual ~CAknDynamicSoftNoteEventManager();    

    /**
     * Allocates memory for an observer. Must be called before calling NotifyEvent().
     *
     * @param aClient Client identification.
     * @param aMessage Request message.
     */
    IMPORT_C void RegisterEventL(TAny* aClient, const RMessage2& aMessage);

    /**
     * Registers a client as an observer for dynamic soft note events.
     *
     * @param aClient Client identification.
     * @param aMessage Request message.
     */
    IMPORT_C void NotifyEvent(TAny* aClient, const RMessage2& aMessage);

    /**
     * Cancels a reqistration for dynamic soft note events.
     *
     * @param aClient Client identification.
     * @param aMessage Request message.
     */
    IMPORT_C void CancelEvent(TAny* aClient, const RMessage2& aMessage);

    /**
     * Handles the actual soft note events, e.g. when soft note has been accepted or canceled.
     *
     * @param aNoteId Soft notification id.
     * @param aActionId Event id.
     * @param aMustDeliver Force the delivery of this event.
     */
    IMPORT_C void IssueEvent(TInt aNoteId, TInt aActionId, TBool aMustDeliver);

    /**
     * Handles client exit.
     *
     * @param aClient Client identification.
     */
    IMPORT_C void ClientExit(TAny* aClient);    

private:
    CAknDynamicSoftNoteEventManager();
    void ConstructL();
    
    TInt FindByNoteIdFromObservers(TInt aNoteId) const;
    TInt FindByClientFromObservers(TAny* aClient) const;
    TInt FindByNoteIdFromNonDeliveredEvents(TInt aNoteId) const;

private: // data
    /// Observer container.
    struct TObserverItem
        {
        /// Client identification.
        TAny* iClient;
        /// Soft notification id.
        TInt iNoteId;
        /// Request message.
        RMessagePtr2 iMessage;
        };

    /// Non-delivered event container.
    struct TNonDeliveredEvent
        {
        /// Soft notification id.
        TInt iNoteId;
        /// Event id.
        TInt iActionId;
        };

    /// Own. Array of observers.
    RArray<TObserverItem> iObservers;
    /// Own. Array of non-delivered events.
    RArray<TNonDeliveredEvent> iNonDeliveredEvents;
    };

#endif // AKNDYNAMICSOFTNOTEEVENTMANAGER_H
