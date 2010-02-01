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
* Description:  System soft notifications.
*
*/

#include "akndialogcontroller.h"

// CNotifierDialogController
// For use by notifiers external to Aknnotifyplugin2.DLL.
CNotifierDialogController::CNotifierDialogController(MAknGlobalNoteController* aGlobalNoteNotifier)
:iGlobalNoteNotifier(aGlobalNoteNotifier)
    {
    }

EXPORT_C TInt CNotifierDialogController::LaunchNoteL(TInt aNoteResource, TInt aSoftkeys, 
    TInt aPriority)
    {
    TInt note = 0;
    
    if (iGlobalNoteNotifier)
        {
        note = iGlobalNoteNotifier->AddSoftNotificationL(
            KNullDesC, 
            aNoteResource, 
            0, 
            aPriority, 
            aSoftkeys);
            
        iGlobalNoteNotifier->TryDisplayNextNoteL();
        }

    return note;
    }

EXPORT_C TInt CNotifierDialogController::LaunchNoteL(TInt aResourceId, TInt aSoftkeys, 
    TInt aPriority, CAknNoteDialog::TTimeout aTimeout, CAknNoteDialog::TTone aTone)
    {
    TInt note = 0;
    if (iGlobalNoteNotifier)
        {
        note = iGlobalNoteNotifier->AddNoteToQueueL(
            aResourceId, 
            KNullDesC,  
            aPriority, 
            aTimeout, 
            aTone, 
            -1, 
            -1, 
            0, 
            aSoftkeys);
            
        iGlobalNoteNotifier->TryDisplayNextNoteL();
        }

    return note;
    }

EXPORT_C void CNotifierDialogController::SetNoteObserver(MNotifierDialogObserver* aObserver)
    {
    iObserver = aObserver;
    }

void CNotifierDialogController::SoftNoteCompleted(TInt aId, TInt aCommand)
    {
    if (iObserver)
        {
        iObserver->NoteCompleted(aId, aCommand);
        }
    }

TBool CNotifierDialogController::ShowSoftNoteL(TInt aPriority, const TDesC& /*aText*/)
    {
    if (iObserver)
        {
        return iObserver->DisplayDialogL(aPriority);
        }
    return EFalse;
    }

TBool CNotifierDialogController::CancelSoftNote(TInt aPriority)
    {
    if (iObserver)
        {
        return iObserver->CancelDialog(aPriority);
        }
    return EFalse;
    }

EXPORT_C void CNotifierDialogController::CancelNote(TInt aNoteId)
    {
    if (iGlobalNoteNotifier)
        {
        iGlobalNoteNotifier->CancelNote(aNoteId);
        }
    }

EXPORT_C TInt CNotifierDialogController::DisplayNonNoteDialogL(TInt aPriority)
    {
    TInt note = 0;
    if (iGlobalNoteNotifier)
        {
        note = iGlobalNoteNotifier->AddSoftNotificationL(KNullDesC, 0, 0, aPriority, 0);
        iGlobalNoteNotifier->TryDisplayNextNoteL();
        }

    return note;
    }

EXPORT_C TInt CNotifierDialogController::DisplayAlarmL(TInt aType, const TDesC& aDescription,
    const TDesC& aTime)
    {
    TInt noteId = 0;
    
    if (iGlobalNoteNotifier)
        {
        noteId = iGlobalNoteNotifier->DisplayAlarmL(aType,aDescription,aTime);
        }

    return noteId;
    }

EXPORT_C CNotifierDialogController* CNotifierDialogController::NewL(
    MAknGlobalNoteController* aGlobalNoteNotifier)
    {
    CNotifierDialogController* me = new (ELeave) CNotifierDialogController(aGlobalNoteNotifier);
    return me;
    }

EXPORT_C void CNotifierDialogController::AddAlarmAdditionalInfo(
    TInt aType,
    const TDesC& aTime,
    const TDesC& aDate,
    const TDesC& aSubject,
    const TDesC& aLocation)
    {
    if (iGlobalNoteNotifier)
        {
        iGlobalNoteNotifier->AddAlarmAdditionalInfo(aType,aTime,aDate,aSubject,aLocation);
        }
    }
    
