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

#include "akndynamicsoftnoteeventmanager.h"

/// Observer array granularity
const TInt KAknEventManagerGranularity = 3;

/// Non-delivered event array reserved extra space.
const TInt KAknEventManagerExtraSpace = 5;

// ---------------------------------------------------------------------------
// CAknDynamicSoftNoteEventManager::CreateUniqueInstanceL
// ---------------------------------------------------------------------------
//
EXPORT_C CAknDynamicSoftNoteEventManager* CAknDynamicSoftNoteEventManager::CreateUniqueInstanceL()
    {
    if (Dll::Tls())
        {
        User::Panic(KAknPanicCategory, EAknEventMgrPanicEventManagerAlreadyExists);                
        }        
        
    CAknDynamicSoftNoteEventManager* self = new(ELeave) CAknDynamicSoftNoteEventManager;
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    
    Dll::SetTls(self);
    
    return self;
    }

//-----------------------------------------------------------------------------
// CAknDynamicSoftNoteEventManager::CAknDynamicSoftNoteEventManager
//-----------------------------------------------------------------------------
//
CAknDynamicSoftNoteEventManager::CAknDynamicSoftNoteEventManager()
    : iObservers(KAknEventManagerGranularity),
      iNonDeliveredEvents(KAknEventManagerGranularity)
    {
    }

//-----------------------------------------------------------------------------
// CAknDynamicSoftNoteEventManager::ConstructL
//-----------------------------------------------------------------------------
//
void CAknDynamicSoftNoteEventManager::ConstructL()
    {
    iNonDeliveredEvents.ReserveL(KAknEventManagerExtraSpace);
    }
  
//-----------------------------------------------------------------------------
// CAknDynamicSoftNoteEventManager::~CAknDynamicSoftNoteEventManager
//-----------------------------------------------------------------------------
//    
CAknDynamicSoftNoteEventManager::~CAknDynamicSoftNoteEventManager()
    {
    for (TInt i = iObservers.Count() - 1; i >= 0; i--)
        {
        if (!iObservers[i].iMessage.IsNull())
            {
            iObservers[i].iMessage.Complete(KErrCancel);
            }
        }
    iObservers.Close();
    iNonDeliveredEvents.Close();
    
    Dll::SetTls(NULL);
    }
    
//-----------------------------------------------------------------------------
// CAknDynamicSoftNoteEventManager::UniqueInstance
//-----------------------------------------------------------------------------
//    
EXPORT_C CAknDynamicSoftNoteEventManager* CAknDynamicSoftNoteEventManager::UniqueInstance()
    {
    if (Dll::Tls())
        {        
        CAknDynamicSoftNoteEventManager* eventManager = 
            static_cast<CAknDynamicSoftNoteEventManager*>(Dll::Tls());
            
        return eventManager;
        }
    else
        {
        return NULL;
        }        
    }    
  
//-----------------------------------------------------------------------------
// CAknDynamicSoftNoteEventManager::ClientExit
//-----------------------------------------------------------------------------
//    
EXPORT_C void CAknDynamicSoftNoteEventManager::ClientExit(TAny* aClient)
    {
    const TInt count = iObservers.Count();       
    for (TInt i = 0; i < count; i++)
        {
        if (iObservers[i].iClient == aClient)
            {
            if (!iObservers[i].iMessage.IsNull())
                {
                iObservers[i].iMessage.Complete(KErrCancel);                    
                }
            iObservers.Remove(i);
            break;       
            }
        }
    }

//-----------------------------------------------------------------------------
// CAknDynamicSoftNoteEventManager::RegisterEventL
//-----------------------------------------------------------------------------
//    
EXPORT_C void CAknDynamicSoftNoteEventManager::RegisterEventL(TAny* aClient, 
    const RMessage2& aMessage)
    {
    TInt pos = FindByClientFromObservers(aClient);
    if (pos != KErrNotFound)
        {
        aMessage.Panic(KAknPanicCategory, EAknEventMgrPanicAlreadyRegistered);
        return;        
        }
    
    TInt reserveCount = Max(
        iNonDeliveredEvents.Count(), 
        iObservers.Count() + KAknEventManagerExtraSpace);
    
    iNonDeliveredEvents.ReserveL(reserveCount);
    
    TObserverItem item;
    item.iClient = aClient;
    item.iNoteId = aMessage.Int0();
    
    iObservers.AppendL(item);
    aMessage.Complete(KErrNone);
    }
  
//-----------------------------------------------------------------------------
// CAknDynamicSoftNoteEventManager::NotifyEvent
//-----------------------------------------------------------------------------
//    
EXPORT_C void CAknDynamicSoftNoteEventManager::NotifyEvent(TAny* aClient, 
    const RMessage2& aMessage)
    {
    TInt pos = FindByClientFromObservers(aClient);
    if (pos == KErrNotFound)
        {
        aMessage.Panic(KAknPanicCategory, EAknEventMgrPanicNotRegistered);
        return;
        }

    const TObserverItem& item = iObservers[pos];      
    if (!iObservers[pos].iMessage.IsNull())
        {
        aMessage.Panic(KAknPanicCategory, EAknEventMgrPanicDuplicateNotify);
        return;
        }
    
    TInt nonDeliveredPos = FindByNoteIdFromNonDeliveredEvents(item.iNoteId);
    
    if (nonDeliveredPos != KErrNotFound)
        {
        TPckgBuf<TInt> actionId(iNonDeliveredEvents[nonDeliveredPos].iActionId);
        if (aMessage.Write(0, actionId) != KErrNone)
            {
            aMessage.Panic(KAknPanicCategory, EAknEventMgrPanicBadMessage);
            return;
            }
        aMessage.Complete(KErrNone);
        iNonDeliveredEvents.Remove(nonDeliveredPos);
        }
    
    if (!aMessage.IsNull())
        {
        iObservers[pos].iMessage = aMessage;
        }
    }
  
//-----------------------------------------------------------------------------
// CAknDynamicSoftNoteEventManager::CancelEvent
//-----------------------------------------------------------------------------
//    
EXPORT_C void CAknDynamicSoftNoteEventManager::CancelEvent(TAny* aClient, 
    const RMessage2& aMessage)
    {
    TInt pos = FindByClientFromObservers(aClient);
   
    if (pos != KErrNotFound)
        {
        if (!iObservers[pos].iMessage.IsNull())
            {
            iObservers[pos].iMessage.Complete(KErrCancel);
            }
        }
        
    aMessage.Complete(KErrNone);
    }
  
//-----------------------------------------------------------------------------
// CAknDynamicSoftNoteEventManager::IssueEvent
//-----------------------------------------------------------------------------
//    
EXPORT_C void CAknDynamicSoftNoteEventManager::IssueEvent(TInt aNoteId, 
    TInt aActionId, TBool aMustDeliver)
    {
    TInt pos = FindByNoteIdFromObservers(aNoteId);    
    TBool completed = EFalse;
    
    if (pos != KErrNotFound)
        {
        if (!iObservers[pos].iMessage.IsNull())
            {
            completed = ETrue;
            TPckgBuf<TInt> actionId(aActionId);
            if (iObservers[pos].iMessage.Write(0, actionId) != KErrNone)
                {
                iObservers[pos].iMessage.Panic(
                    KAknPanicCategory, EAknEventMgrPanicBadMessage);
                return;
                }
            iObservers[pos].iMessage.Complete(KErrNone);            
            }
        }
   
    if (!completed)
        {
        TInt nonDeliveredPos = FindByNoteIdFromNonDeliveredEvents(aNoteId);
        
        if (nonDeliveredPos != KErrNotFound)
            {
            iNonDeliveredEvents[nonDeliveredPos].iActionId = aActionId;
            }
        else if (aMustDeliver)
            {
            TNonDeliveredEvent event;
            event.iNoteId = aNoteId;
            event.iActionId = aActionId;
            iNonDeliveredEvents.Append(event);
            }
        }
    }
  
//-----------------------------------------------------------------------------
// CAknDynamicSoftNoteEventManager::FindByNoteIdFromObservers
//-----------------------------------------------------------------------------
//    
TInt CAknDynamicSoftNoteEventManager::FindByNoteIdFromObservers(TInt aNoteId) const
    {
    TInt result = KErrNotFound;
    
    const TInt count = iObservers.Count();
    for (TInt i = 0; i < count; i++)
        {
        if (iObservers[i].iNoteId == aNoteId)
            {
            result = i;
            break;
            }
        }

    return result;        
    }
  
//-----------------------------------------------------------------------------
// CAknDynamicSoftNoteEventManager::FindByClientFromObservers
//-----------------------------------------------------------------------------
//    
TInt CAknDynamicSoftNoteEventManager::FindByClientFromObservers(TAny* aClient) const
    {
    TInt result = KErrNotFound;
    
    const TInt count = iObservers.Count();
    for (TInt i = 0; i < count; i++)
        {
        if (iObservers[i].iClient == aClient)
            {
            result = i;
            break;
            }
        }

    return result;        
    }    

//-----------------------------------------------------------------------------
// CAknDynamicSoftNoteEventManager::FindByNoteIdFromNonDeliveredEvents
//-----------------------------------------------------------------------------
//
TInt CAknDynamicSoftNoteEventManager::FindByNoteIdFromNonDeliveredEvents(TInt aNoteId) const
    {
    TInt result = KErrNotFound;
    
    const TInt count = iNonDeliveredEvents.Count();
    for (TInt i = 0; i < count; i++)
        {
        if (iNonDeliveredEvents[i].iNoteId == aNoteId)
            {
            result = i;
            break;
            }
        }

    return result;    
    }

// End of file
