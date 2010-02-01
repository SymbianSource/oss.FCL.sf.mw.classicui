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
* Description:  Dynamic soft notification observer.
*
*/

#include "AknDynamicSoftNoteObserver.h"
#include "AknDynamicSoftNotifier.h" 
#include "aknsoftnoteconsts.h"

//-----------------------------------------------------------------------------
// CAknDynamicSoftNoteObserver::CAknDynamicSoftNoteObserver
//-----------------------------------------------------------------------------
// 
CAknDynamicSoftNoteObserver::CAknDynamicSoftNoteObserver(
    CAknDynamicSoftNotifier& aDynamicSoftNotifier,
    MAknDynamicSoftNoteObserver* aClientApp, 
    TInt aNoteId ) :
    // members
    CActive(EPriorityStandard), 
    iClientApp(aClientApp), 
    iDynamicSoftNotifier(aDynamicSoftNotifier), 
    iNoteId(aNoteId)
    {
    CActiveScheduler::Add(this);
    }

//-----------------------------------------------------------------------------
// CAknDynamicSoftNoteObserver::ConstructL
//-----------------------------------------------------------------------------
//     
void CAknDynamicSoftNoteObserver::ConstructL()
    {
    User::LeaveIfError(iSession.Connect());        
    User::LeaveIfError(iSession.PreAllocateDynamicSoftNoteEvent(iNoteId));
    IssueRequest();
    }   
     
//-----------------------------------------------------------------------------
// CAknDynamicSoftNoteObserver::~CAknDynamicSoftNoteObserver
//-----------------------------------------------------------------------------
//    
CAknDynamicSoftNoteObserver::~CAknDynamicSoftNoteObserver()
    {
    Cancel();
    iSession.Close();
    }
    
//-----------------------------------------------------------------------------
// CAknDynamicSoftNoteObserver::NewL
//-----------------------------------------------------------------------------
//     
EXPORT_C CAknDynamicSoftNoteObserver* CAknDynamicSoftNoteObserver::NewL(
    CAknDynamicSoftNotifier& aDynamicSoftNotifier, 
    MAknDynamicSoftNoteObserver* aClientApp, 
    TInt aNoteId)
    {
    CAknDynamicSoftNoteObserver* self = 
        CAknDynamicSoftNoteObserver::NewLC(aDynamicSoftNotifier, aClientApp, aNoteId);
        
    CleanupStack::Pop(self);
    return self;
    }
   
//-----------------------------------------------------------------------------
// CAknDynamicSoftNoteObserver::NewLC
//-----------------------------------------------------------------------------
//         
EXPORT_C CAknDynamicSoftNoteObserver* CAknDynamicSoftNoteObserver::NewLC(
    CAknDynamicSoftNotifier& aDynamicSoftNotifier,
    MAknDynamicSoftNoteObserver* aClientApp, 
    TInt aNoteId)
    {
    CAknDynamicSoftNoteObserver* self = 
        new (ELeave) CAknDynamicSoftNoteObserver(aDynamicSoftNotifier, aClientApp, aNoteId);
        
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }     
   
//-----------------------------------------------------------------------------
// CAknDynamicSoftNoteObserver::NoteId
//-----------------------------------------------------------------------------
//     
TInt CAknDynamicSoftNoteObserver::NoteId() const
    {
    return iNoteId;            
    }
    
//-----------------------------------------------------------------------------
// CAknDynamicSoftNoteObserver::RunL
//-----------------------------------------------------------------------------
//     
void CAknDynamicSoftNoteObserver::RunL()
    {
    TInt err = iStatus.Int();
        
    if (err == KErrNone)
        {
        // Handle response.
        TInt actionId = iEventBuffer();
        
        // IssueRequest();
        switch (actionId)
            {
            case EAknDynamicSNoteEventAccepted:
                {
                iClientApp->NotificationAccepted(iNoteId);
                break;
                }
            case EAknDynamicSNoteEventCanceled:
                {
                iClientApp->NotificationCanceled(iNoteId);
                break;
                }
            default:
                {
                User::Panic(_L("DynamicSoftNote"), KErrArgument);
                break;
                }
            }
        }
#ifdef _DEBUG
    else
        {
        _LIT(KDmsg1, "AknDynamicSoftNoteObserver, RunL(): iStatus not equal to KErrNone, err:%d");
        RDebug::Print(KDmsg1, err);
        }        
#endif        
    
    iDynamicSoftNotifier.DeleteObserver(this);
    // This instance is deleted
    }

//-----------------------------------------------------------------------------
// CAknDynamicSoftNoteObserver::IssueRequest
//-----------------------------------------------------------------------------
//     
void CAknDynamicSoftNoteObserver::IssueRequest()
    {
    iSession.NotifyDynamicSoftNoteEvent(iStatus, iEventBuffer);
    SetActive();    
    }
    
//-----------------------------------------------------------------------------
// CAknDynamicSoftNoteObserver::DoCancel
//-----------------------------------------------------------------------------
//    
void CAknDynamicSoftNoteObserver::DoCancel()
    {
    iSession.CancelDynamicSoftNoteEventNotification();
    }    
   
// End of File
