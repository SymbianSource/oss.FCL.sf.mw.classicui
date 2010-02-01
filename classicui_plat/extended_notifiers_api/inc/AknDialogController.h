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
* Description:  Notification dialog controller.
*
*/


#ifndef __AKNDIALOGCONTROLLER_H__
#define __AKNDIALOGCONTROLLER_H__

#include <e32std.h>
#include <e32base.h>
#include <aknnotedialog.h>

class CAknGlobalNoteSubject;

class MAknGlobalNoteController
    {
public:
    virtual TInt AddSoftNotificationL(
        const TDesC& aText, 
        TInt aResource, 
        TInt aCount, 
        TInt aPriority, 
        TInt aSoftkeys, 
        TInt aTone = 0) = 0;
        
    virtual TInt AddNoteToQueueL(
        TInt aResourceId, 
        const TDesC& aText, 
        TInt aPriority, 
        CAknNoteDialog::TTimeout aTimeout, 
        CAknNoteDialog::TTone aDefaultTone, 
        TInt aUserTone, 
        TInt aGraphic, 
        TInt aGraphicMask, 
        TInt aAnimation, 
        TInt aSoftkeys = 0) = 0;
        
    virtual void TryDisplayNextNoteL(
        TBool aShowAsynch = EFalse) = 0;
        
    virtual void CancelNote(
        TInt aNoteId,
        TBool aShowNext = ETrue) = 0;
        
    virtual TInt DisplayAlarmL(
        TInt aType,
        const TDesC& aDescription,
        const TDesC& aTime) = 0;
        
    virtual void AddAlarmAdditionalInfo(  
        TInt aType,
        const TDesC& aTime,
        const TDesC& aDate,
        const TDesC& aSubject,
        const TDesC& aLocation) = 0;
    };

class MSoftNotificationObserver
    {
public:
    virtual void SoftNoteCompleted(TInt aId, TInt aCommand) = 0;
    virtual TBool ShowSoftNoteL(TInt aPriority, const TDesC& aText) = 0;
    virtual TBool CancelSoftNote(TInt aPriority) = 0;
    };

class MNotifierDialogObserver
    {
public:
    virtual void NoteCompleted(TInt aNoteId, TInt aCommand) = 0;
    virtual TBool DisplayDialogL(TInt aPriority) = 0;
    virtual TBool CancelDialog(TInt aPriority) = 0;
    };

// For use by notifiers outside of Aknnotifyplugin2.DLL
NONSHARABLE_CLASS(CNotifierDialogController) : public CBase, public MSoftNotificationObserver
    {
public:
    CNotifierDialogController(MAknGlobalNoteController* aGlobalNoteNotifier); // not exported
    IMPORT_C void SetNoteObserver(MNotifierDialogObserver* aObserver);
    IMPORT_C TInt LaunchNoteL(TInt aNoteResource, TInt aSoftkeys, TInt aPriority);
    
    IMPORT_C TInt LaunchNoteL(
        TInt aResourceId, 
        TInt aSoftkeys, 
        TInt aPriority, 
        CAknNoteDialog::TTimeout aTimeout, 
        CAknNoteDialog::TTone aTone);
    
    IMPORT_C void CancelNote(TInt aNoteId);
    IMPORT_C TInt DisplayNonNoteDialogL(TInt aPriority);
    IMPORT_C TInt DisplayAlarmL(TInt aType, const TDesC& aDescription, const TDesC& aTime);
    
    IMPORT_C void AddAlarmAdditionalInfo( 
        TInt aType, // same as CAgnEntry::TType, use -1 for clock alarm
        const TDesC& aTime,
        const TDesC& aDate,
        const TDesC& aSubject,
        const TDesC& aLocation);

private: // for now, will be public when system fully implemented
    // @Since 2.8 
    // Modules using this class should create own instance instead using Instance on EiksrvAppUI
    IMPORT_C static CNotifierDialogController* NewL(MAknGlobalNoteController* aGlobalNoteNotifier);

private:
    // From MSoftNotificationObserver
    virtual void SoftNoteCompleted(TInt aId, TInt aCommand);
    virtual TBool ShowSoftNoteL(TInt aPriority, const TDesC& aText);
    virtual TBool CancelSoftNote(TInt aPriority);

private:
    MAknGlobalNoteController* iGlobalNoteNotifier;
    MNotifierDialogObserver* iObserver;
    friend class CAknGlobalNoteSubject;
    friend class CEikServAppUi;
    };

 
enum 
    {
    EClockAlarm        = 1,
    ECalendarAlarm     = 2,
    EHideSnooze        = 4,
    EClockAlarmStop    = 5, // binary EClockAlarm+EHideSnooze
    ECalendarAlarmStop = 6, // binary ECalendarAlarm+EHideSnooze
    EAskWakeUp         = 8,
    ENoSilence         = 16,
    EMskOpen           = 32
    };

class MAknPhoneKeyForwarder
    {
public:
    virtual void ForwardKeyToPhoneAppL(const TKeyEvent& aKeyEvent) = 0;
    };

#endif // __AKNDIALOGCONTROLLER_H__
