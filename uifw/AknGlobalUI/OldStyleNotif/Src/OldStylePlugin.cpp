/*
* Copyright (c) 2002-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Creates Avkon old style notifiers.
*
*/

#include <eiknotapi.h>
#include <AknNotifyStd.h>
#include <MediatorEventProvider.h>
#include "AknKeyLockNotifier.h"
#include "AknNotifyPlugin.h"
#include "AknSystemPopup.h"
#include "AknSoftNotificationPlugin.h"
#include "AknSystemListPopup.h"
#include "aknsystemmsgpopup.h"
#include "AknSystemListMsgPopup.h"
#include "aknsystemconfirmationpopup.h"
#include "aknsystemprogresspopup.h"

const TInt KArrayGranularity = 3;

GLDEF_C void Panic(TAknPanic aPanic)
    {
    _LIT(KPanicCat, "AknNotifyPlugin");
    User::Panic(KPanicCat, aPanic);
    }

void CleanupArray(TAny* aArray)
    {
    CArrayPtrFlat<MEikSrvNotifierBase2>* subjects = 
        static_cast<CArrayPtrFlat<MEikSrvNotifierBase2>*>(aArray);
        
    subjects->ResetAndDestroy();
    delete subjects;
    }

CArrayPtr<MEikSrvNotifierBase2>* DoCreateNotifierArrayL()
    {
    CArrayPtrFlat<MEikSrvNotifierBase2>* subjects = 
        new (ELeave)CArrayPtrFlat<MEikSrvNotifierBase2>(KArrayGranularity);
        
    CleanupStack::PushL(TCleanupItem(CleanupArray, subjects));

    // ----------------------------
    // Key lock notifier.
    // ----------------------------
    CAknKeyLockNotifierSubject* keyLockNotifier = CAknKeyLockNotifierSubject::NewL();
    
    CleanupStack::PushL(keyLockNotifier);
    subjects->AppendL(keyLockNotifier);
    CleanupStack::Pop(keyLockNotifier);

    // ----------------------------
    // Global note notifier.
    // ----------------------------
    CAknGlobalNoteSubject* globalNoteSubject = CAknGlobalNoteSubject::NewL(keyLockNotifier);
    
    CleanupStack::PushL(globalNoteSubject);
    subjects->AppendL(globalNoteSubject);
    CleanupStack::Pop(globalNoteSubject);
    
    // ----------------------------
    // Soft note notifier.
    // ----------------------------
    CAknSoftNotificationSubject* softNotificationSubject = CAknSoftNotificationSubject::NewL(
        keyLockNotifier, 
        globalNoteSubject);
        
    CleanupStack::PushL(softNotificationSubject);
    subjects->AppendL(softNotificationSubject);
    CleanupStack::Pop(softNotificationSubject);

    // ----------------------------
    // Popup notifier.
    // ----------------------------
    CAknPopupNotifierSubject* popupNotifierSubject = CAknPopupNotifierSubject::NewL();
    
    CleanupStack::PushL(popupNotifierSubject);
    subjects->AppendL(popupNotifierSubject);
    CleanupStack::Pop(popupNotifierSubject);
    
    // =========================================================================
    // Notifiers using CAknMediatorEvent.
    // =========================================================================
    CAknMediatorEvent* aknEvent = new (ELeave) CAknMediatorEvent();
    CleanupStack::PushL(aknEvent);
    
#ifdef __COVER_DISPLAY  
    aknEvent->iImpl = CMediatorEventProvider::NewL();
#endif  

    // ----------------------------
    // Signal notifier.
    // ----------------------------
    CAknSignalNotifierSubject* signalNotifierSubject = CAknSignalNotifierSubject::NewL(aknEvent);
    
    CleanupStack::PushL(signalNotifierSubject);
    subjects->AppendL(signalNotifierSubject);
    CleanupStack::Pop(signalNotifierSubject);
    
    // ----------------------------
    // Battery notifier.
    // ----------------------------
    CAknBatteryNotifierSubject* batteryNotifierSubject = CAknBatteryNotifierSubject::NewL(aknEvent);
    
    CleanupStack::PushL(batteryNotifierSubject);
    subjects->AppendL(batteryNotifierSubject);
    CleanupStack::Pop(batteryNotifierSubject);
    
    // ----------------------------
    // Small indicator notifier.
    // ----------------------------
    CAknSmallIndicatorSubject* smallIndicatorSubject = CAknSmallIndicatorSubject::NewL(aknEvent);

    CleanupStack::PushL(smallIndicatorSubject);
    subjects->AppendL(smallIndicatorSubject);
    CleanupStack::Pop(smallIndicatorSubject);
    
    // Mediator event not needed anymore.
    CleanupStack::Pop(aknEvent); 
    
    // ----------------------------
    // Incall bubble notifier.
    // ----------------------------
    CAknIncallBubbleSubject* incallBubbleSubject = CAknIncallBubbleSubject::NewL();
    
    CleanupStack::PushL(incallBubbleSubject);
    subjects->AppendL(incallBubbleSubject);
    CleanupStack::Pop(incallBubbleSubject);

    // =========================================================================
    // Traditional notifiers, moved here because of higher wg-priority (wouldn't
    // require any capabilities otherwise).
    // =========================================================================
    
    // ----------------------------
    // Global list query.
    // ----------------------------
    CAknGlobalListQuerySubject* listQuerySubject = CAknGlobalListQuerySubject::NewL();
    
    CleanupStack::PushL(listQuerySubject);
    subjects->AppendL(listQuerySubject);
    CleanupStack::Pop(listQuerySubject);    
    
    // ----------------------------
    // Global msg query.
    // ----------------------------
    CAknGlobalMsgQuerySubject* msgQuerySubject = CAknGlobalMsgQuerySubject::NewL();
    
    CleanupStack::PushL(msgQuerySubject);
    subjects->AppendL(msgQuerySubject);
    CleanupStack::Pop(msgQuerySubject);
    
    // ----------------------------
    // Global confirmation query.
    // ----------------------------
    CAknGlobalConfirmationQuerySubject* confirmationQuerySubject = 
        CAknGlobalConfirmationQuerySubject::NewL();
    
    CleanupStack::PushL(confirmationQuerySubject);
    subjects->AppendL(confirmationQuerySubject);
    CleanupStack::Pop(confirmationQuerySubject);
    
    // ----------------------------
    // Global progress dialog.
    // ----------------------------
    CAknGlobalProgressDialogSubject* progressDialogSubject = 
        CAknGlobalProgressDialogSubject::NewL();
    
    CleanupStack::PushL(progressDialogSubject);
    subjects->AppendL(progressDialogSubject);
    CleanupStack::Pop(progressDialogSubject);
    
    // ----------------------------
    // Global list msg query.
    // ----------------------------
    CAknGlobalListMsgQuerySubject* listMsgQuerySubject = CAknGlobalListMsgQuerySubject::NewL();
    
    CleanupStack::PushL(listMsgQuerySubject);
    subjects->AppendL(listMsgQuerySubject);
    CleanupStack::Pop(listMsgQuerySubject);

    CleanupStack::Pop(subjects);
    return subjects;
    }

// Lib main entry point
EXPORT_C CArrayPtr<MEikSrvNotifierBase2>* NotifierArray()
    {
    CArrayPtr<MEikSrvNotifierBase2>* subjects = NULL;
    TRAP_IGNORE(subjects = DoCreateNotifierArrayL());
    return subjects;
    }

// End of file
