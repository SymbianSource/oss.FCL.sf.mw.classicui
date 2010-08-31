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
* Description:  Keyguard functionality is provided by a notifier.
*
*/

#ifndef __AKNKEYLOCKNOTIFIER_H__
#define __AKNKEYLOCKNOTIFIER_H__

#include <eiknotapi.h>
#include <eikbtgpc.h>
#include <AknNotifyStd.h>
#include <aknnotedialog.h>
#include <AknEcs.h>
#include <AknNotifierControllerPlugin.h>
#include <AknQueryDialog.h>                    // phone query
#include <e32property.h>
#include <LockDomainCRKeys.h>

class CAknKeyLockControl;
class CAknEcsNote;
class CAknKeyLockNotifierSubject;
class CKeyLockPolicyApi; 

NONSHARABLE_CLASS(CAknSleepingNote) : public CAknNoteDialog
    {
public:
    CAknSleepingNote(MEikCommandObserver* aCommandObserver = NULL);
    void ConstructSleepingNoteL(TInt aResourceId);
    TInt ShowNote(const TInt aTimeout,const TTone aTone);
    TBool OkToExitL(TInt aCommand);
private: 
    virtual void CEikDialog_Reserved_1();
    virtual void CEikDialog_Reserved_2();   
private: 
    virtual void CAknNoteDialog_Reserved();
private: //new virtual function
    virtual void CAknSleepingNote_Reserved();
protected:
    MEikCommandObserver* iCommandObserver;
    TInt iResourceId;
    void HandleResourceChange(TInt aType);
    };

NONSHARABLE_CLASS(CAknLockedNote) : public CAknSleepingNote
    {
public:
    CAknLockedNote(TInt& aLocked, MEikCommandObserver* aCommandObserver = NULL);
    TBool OkToExitL(TInt aButtonId);
    ~CAknLockedNote();
    void CancelNote();
    void FocusChanged(TDrawNow aDrawNow);
private: 
    virtual void CEikDialog_Reserved_1();
    virtual void CEikDialog_Reserved_2();   
private: 
    virtual void CAknNoteDialog_Reserved();
private: 
    virtual void CAknSleepingNote_Reserved();
private:
    TInt& iLocked;
    };

NONSHARABLE_CLASS(CAknLockedPhoneQuery) : public CAknTextQueryDialog
    {
public:
    static CAknLockedPhoneQuery* NewL(TDes& aDataText);
    virtual ~CAknLockedPhoneQuery();
private:
    CAknLockedPhoneQuery(TDes& aDataText);
    void ConstructL();
    TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
    void ResetInactivityTimer();
    static TInt InactivityExitL(TAny *aThis);
    void DoInactivityExitL();
protected:
    CPeriodic* iInactivityTimer;
    };

NONSHARABLE_CLASS(CAknKeyLockControl) : 
    public CCoeControl, 
    public MEikCommandObserver, 
    public MAknEcsObserver
    {
public:
    CAknKeyLockControl();
    ~CAknKeyLockControl();
    void ConstructL();
    void EnableKeylock(TBool aShowNote = ETrue);
    void DisableKeylock();
    void OfferKeylock();

    void DisplayLockedNote();
    void DisplayKeyActiveNote();
    void ShowKeylockCba();

    void OfferTimerExpired();

    void HandleResourceChange(TInt aType);
    
private:
    void ShowLockedNote();
    void DoShowLockedNote();
    void DoUnlock();

    void CaptureSystemKeys();
    void UnCaptureSystemKeys();

    void DoExitOfferKeylock();

    void SendMessageToSysAp(TInt aMessage);

    void LeftSoftKeyPressed();
    
    // From MEikCommandObserver
    void ProcessCommandL(TInt aCommandId);
    // From CCoeControl
    TInt CountComponentControls() const;
    CCoeControl* ComponentControl(TInt aIndex) const;
    TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
    // From MAknEcsObserver
    void HandleEcsEvent( CAknEcsDetector* aEcsDetector, CAknEcsDetector::TState aState );
    
    // For screen lock
    void CapturePointerEvents();
    void UnCapturePointerEvents();

private:
    CEikButtonGroupContainer* iKeyLockCba;
    TInt iUnlockConfirmation;
    CAknLockedNote* iConfirmationNote;
    CAknLockedNote* iLockedNote;
    TBool iLockedNoteDisplayed;
    TInt iPowerKey;
	TInt iEndKey;
    TInt iAppKey;
    TInt iVoiceKey;
    TInt iPowerKey2;
    TInt iAppKey2;
    TInt iVoiceKey2;
    TInt iAppKeyA;        // For BT keyboard 'Message' key.
    TInt iPoCKey;
    TInt iPoCKey2;
    TInt iHoldSwitch;
    TBool iKeysCaptured;
    CAknEcsDetector* iEcsDetector;
    CAknSleepingNote* iKeypadLockedNote;
    CAknSleepingNote* iKeypadUnlockedNote;
    CAknLockedNote* iOfferLockNote;
public:
    // Position of these publics member data should not be changed; new things to be added after
    TBool iKeyLockEnabled;
    TBool iOfferLockEnabled;
private:
    // Emergency number display note
    CAknEcsNote* iEcsNote;
    //Show note "Now press *". 
    //Note is shown when user has pressed "Unlock" when keypad is in locked state
    CAknLockedNote* iConfirmationNoteAsterisk;
    TBool iFeatureKeypadNoSlider;
    TBool iSoundsMuted;
    CAknKeyLockNotifierSubject* iNotif; // Not owned
    TInt iLeftSoftKey;
    TInt iEditKeyL;
    TInt iEditKeyR;
    TInt iCameraKey;
    TInt iVolumeUpKey;
    TInt iVolumeDownKey;
    TInt iCameraKey2;
    TInt iVolumeUpKey2;
    TInt iVolumeDownKey2;
    RProperty iStatusProperty;
    TBool iFeatureNoPowerkey;
    TLockHardware iHardwareSupport;
    CKeyLockPolicyApi* iKeylockApi; 
    TBool iConsumeNextEventKey;
public:
    TBool iAutolockEnabled;
    CAknKeyLockControl(CAknKeyLockNotifierSubject* aNotif);
    void AutolockEnabled(TBool aAutoLockOn);
    TBool iPhoneQueryOnScreen;
    void CallNumberL(TDesC& aNumber);
    void ShowLockPhoneQueryL();
    };

// CAknKeyLockNotifierSubject

NONSHARABLE_CLASS(CAknKeyLockNotifierSubject) : 
    public CBase, 
    public MEikSrvNotifierBase2, 
    public MAknKeyLockController
    {
public:
    static CAknKeyLockNotifierSubject* NewL();
    ~CAknKeyLockNotifierSubject();
    // From MAknKeyLockObserver
    TBool IsKeyLockEnabled();
    TBool AllowNotifications();
    void UnlockKeys();
    void LockKeys(TBool aAutoLockOn = EFalse);
    void AddObserverL(MAknKeyLockObserver* aObserver);
    void RemoveObserver(MAknKeyLockObserver* aObserver);
private:
    CAknKeyLockNotifierSubject();
    void ConstructL();

    void DoEnableKeyLock();
    void DoDisableKeyLock();
    void DoAllowNotifications();
    void DoStopNotifications();
    void DoOfferKeyLock();
    void DoCancelAllNotificatons();

    void ShowKeylockCba();

    void NotifyStatusChange(TKeyLockStatus aStatus);
    // From MEikSrvNotifierBase
    void Release();
    TNotifierInfo RegisterL();
    TNotifierInfo Info() const;
    TPtrC8 StartL(const TDesC8& aBuffer);
    void StartL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage);
    void Cancel();
    TPtrC8 UpdateL(const TDesC8& aBuffer);

private:
    TNotifierInfo iInfo;
    RMessagePtr2 iMessage;
    TBool iCompleted;
    CArrayPtrFlat<MAknKeyLockObserver>* iObserverList;
    CAknKeyLockControl* iKeyLockControl;
    TBool iAllowNotifications;
    TPckgBuf<SAknKeyLockNotifierParams> iRetPckg;
    TInt iResourceFileOffset;
    friend class CAknKeyLockControl; // needed for NotifyStatusChange
    };

#endif // __AKNKEYLOCKNOTIFIER_H__

// End of File
