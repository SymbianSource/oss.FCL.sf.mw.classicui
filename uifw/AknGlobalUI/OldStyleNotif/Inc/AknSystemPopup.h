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
* Description:  System soft notifications.
*
*/

#ifndef __AKNSYSTEMPOPUP_H__
#define __AKNSYSTEMPOPUP_H__

#include <e32std.h>
#include <e32base.h>
#include <eiknotapi.h>
#include <eikcmobs.h>
#include <aknnotedialog.h>
#include <aknstaticnotedialog.h>
#include <AknNotifyStd.h>
#include <AknEcs.h>
#include "AknNotifierControllerPlugin.h"
#include "AknPrivateImageLoader.h"
#include <aknSDData.h>
#include <akndialogcontroller.h>
#include <e32property.h>

class CAknMessageReaderLongPressDetector;
class MAknMessageNotifierObserver;

const TInt KGlobalNoteTextLength = 256;
const TInt KMinimumSoftNotePriority = 1000;

NONSHARABLE_CLASS( CGlobalNoteInfo ) : public CBase
    {
public: // Constructor and destructor.

    /**
     * Default constructor.
     */
    CGlobalNoteInfo();
        
    /**
     * Destructor.
     */
    ~CGlobalNoteInfo();
        
public:
    TInt iNoteId;
    TInt iResourceId;
    CAknNoteDialog::TTimeout iTimeOut;
    CAknNoteDialog::TTone iTone;
    TBuf<KGlobalNoteTextLength> iText;
    TInt iPriority;
    TInt iSoftkeys;
    TInt iGraphic;
    TInt iGraphicMask;
    TInt iAnimation;
    TInt iPlural;
    RMessagePtr2 iMessage;
    TBool iAsync;
    TBool iTextProcessing;
    TBool iIsFromAdapter; // Indicates that global note was shown by adapter.
                          // We need this information to return correct softkey
                          // enumeration in TRequestStatus.
    CAknSDData* iSDData;
    TInt iGlobalPopupPriority;	// used to set AknGlobalPopupPriorityController priority
    
    /// Raw image data for dialog.
    TPtrC8 iImage;
    /// Custom right softkey for dialog.
    TPtrC  iRightSK;
    /// Custom left softkey for dialog.
    TPtrC  iLeftSK;
    
    TInt iAlmFlag;
    };


struct SAknAlarmPSInfo;

class MGlobalNoteObserver
    {
public:
    virtual void GlobalNoteCompleted(TInt aCommandId) = 0;
    virtual TBool NoteWaiting() = 0;
    virtual SAknAlarmPSInfo* AlarmData() = 0;
	virtual TBool IsAppsKeyLocked() = 0;
    virtual void SetAppsKeyLocked( TBool aLocked ) = 0;
    };


NONSHARABLE_CLASS(CAknGlobalNoteDialog) : 
    public CAknStaticNoteDialog,
    public MAknPrivateImageLoaderObserver
    {
public:
    CAknGlobalNoteDialog(MGlobalNoteObserver* aObserver);
    ~CAknGlobalNoteDialog();
    void UpdateNoteAndDisplayL( CGlobalNoteInfo* aInfo );
    void ConstructL();
    void NextNoteOrExit(TBool aDirectExit = EFalse);
    void SetAutoLock(TBool aAutoLock);
    /**
     * Returns reference to current grouped note window
     *
     * @return RWindow of the dialog
     */  
    RWindow& GlobalNoteWindow();
        
    void RemoveCurrentNote();

private: // From MAknPrivateImageLoaderObserver
    void ImageLoadSuccess( CEikImage* aImage );
    void ImageLoadError( TInt aError );    
    
private:
    TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
    void PreLayoutDynInitL();
    void PostLayoutDynInitL();
    TBool OkToExitL(TInt aButtonId);
    static TBool CallNextNoteOrExit(TAny* aThis);
    void HandleResourceChange(TInt aType);
    virtual void CEikDialog_Reserved_1();
    virtual void CEikDialog_Reserved_2();
    virtual void CAknNoteDialog_Reserved();
    virtual void CAknStaticNoteDialog_Reserved();
    void HandlePointerEventL(const TPointerEvent& aPointerEvent);

private:
    MGlobalNoteObserver* iObserver;
    TInt iSoftkeys;
    TInt iCommand;
    TInt iControlType;
    TBool iIsSoftNotification;
    TBool iAutoLock;
    TBool iIsAlarm;
    TBool iIsAlarmWakeup;
    TInt iPreviousAnimation; // For optimizing animation usage.
    /// Flag whether dialog should be visible at the moment. Used for
    /// asynchronous image loading. 
    TBool iDialogActive;
    /// Own. Creates usable images from raw image data.
    CAknPrivateImageLoader* iImageLoader; 
    /// Previously active note. Used for optimizing image loading. 
    TInt  iPreviousNoteId; 
    /// Custom text for left softkey.
    TPtrC iSoftkeyLeft;
    /// Custom text for right softkey. 
    TPtrC iSoftkeyRight;
    TBool iCaptured;
    };


NONSHARABLE_CLASS(CAknGlobalNoteSubject) :
    public CBase,
    public MAknUINotifierBase,
    public MGlobalNoteObserver,
    public MAknKeyLockObserver,
    public MAknGlobalNoteController
    {
public:
    static CAknGlobalNoteSubject* NewL(MAknKeyLockController* aKeyLockController);
    ~CAknGlobalNoteSubject();
    void ConstructL();
    
public: // From MAknGlobalNoteController
    TInt AddSoftNotificationL(
        const TDesC& aText, 
        TInt aResource, 
        TInt aCount, 
        TInt aPriority, 
        TInt aSoftkeys, 
        TInt aTone = 0);

    TInt AddNoteToQueueL(
        TInt aResourceId, 
        const TDesC& aText, 
        TInt aPriority, 
        CAknNoteDialog::TTimeout aTimeout, 
        CAknNoteDialog::TTone aDefaultTone, 
        TInt aUserTone, 
        TInt aGraphic, 
        TInt aGraphicMask, 
        TInt aAnimation, 
        TInt aSoftkeys = 0);
        
    void CancelNote(TInt aNoteId, TBool aShowNext = ETrue);

    void TryDisplayNextNoteL(TBool aShowAsynch = EFalse);

    // The variable aTime is deprecated, the alarm note content should be 
    // described in the descriptor aDescription.
    TInt DisplayAlarmL(TInt aType,const TDesC& aDescription, const TDesC& aTime);

    // The variable aTime is deprecated, the alarm note content should be 
    // described in the descriptor aDescription.
    void AddAlarmAdditionalInfo( 
        TInt aType,
        const TDesC& aTime,
        const TDesC& aDate,
        const TDesC& aSubject,
        const TDesC& aLocation);

public: // New methods
    /**
     * Adds new soft notification to queue.
     * 
     * @param aText Text of the soft notification.
     * @param aCount Count of items in the soft notification.
     * @param aPriority Visibility priority of the soft notification.
     * @param aTone Tone played when soft notification is shown.
     * @param aLeftSk Custom left softkey. 
     * @param aRightSk Custom right softkey.
     * @param aImage Raw image data for soft notification dialog. 
     */
    TInt AddSoftNotificationL( 
        const TDesC& aText, 
        TInt aCount,
        TInt aPriority, 
        TInt aTone,
        const TDesC& aLeftSK,
        const TDesC& aRightSK,
        const TDesC8& aImage );
    
    void DisplayNextNoteL();

    void SetSoftNoteObserver(MSoftNotificationObserver* aObserver);
    void SetNotificationDialogObserver(MSoftNotificationObserver* aObserver);
    TInt NotePlural(TInt aNoteId);
    const TDesC& NoteText(TInt aNoteId);
    void SetMaxDisplayPriorityL(TInt aPriority, TInt aDelay = 0);
    TInt StackCount();
    static TInt CallDisplayNextNote(TAny* aThis);
    
    void SetMessageNotifierObserver( MAknMessageNotifierObserver* aMessageNotifierObserver );
    TBool SetSDData(TInt aNoteId, CAknSDData* aData);                                      

private:
    // RProperty listener for autolock status.
    NONSHARABLE_CLASS(CSubscriber) : public CActive
        {
    public: // New functions.
        CSubscriber(TCallBack aCallBack, RProperty& aProperty);
        ~CSubscriber();
        void Subscribe();
        void StopSubscribe();
    private: // From CActive.
        void RunL();
        void DoCancel();
    private:
        TCallBack iCallBack;
        RProperty& iProperty;
        };    

private:
    CAknGlobalNoteSubject(MAknKeyLockController* aKeyLockController);

    //From MEikSrvNotifierBase
    virtual void Release();
    virtual TNotifierInfo RegisterL();
    virtual TNotifierInfo Info() const;
    virtual TPtrC8 StartL(const TDesC8& aBuffer);
    virtual void StartL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage);
    virtual void Cancel();
    virtual TPtrC8 UpdateL(const TDesC8& aBuffer);

    virtual void KeyPressed(const TKeyEvent& aKeyEvent, TEventCode aType);

    TInt AddNoteToQueueL(TInt aResourceId, TInt aPriority, TInt aTone, TInt aPreallocatedNoteId = 0);
    void CancelOustandingRequests();
    
    // From MGlobalNoteObserver
    virtual void GlobalNoteCompleted(TInt aCommandId);
    virtual TBool NoteWaiting();
	virtual TBool IsAppsKeyLocked();
    virtual void SetAppsKeyLocked( TBool aLocked );

    void HighestPriorityNote(TInt& aIndex, TInt& aPriority);
    CGlobalNoteInfo* Note( TInt aNoteId );
    TInt NoteIndex(TInt aNoteId);
    TInt PermanentNotesCount() const;

    // From MAknKeyLockObserver
    void KeyLockStatusChange(TKeyLockStatus aStatus);
	void CancelNote( TInt aNoteId, TBool aShowNext, TBool aDeleteNoteInfo );
    // Handles changes in autolock status.
    static TInt AutolockStatusNotificationL(TAny* aObj);  
    void HandleAutolockStatusNotificationL(); 
    
    TInt AddNoteToQueueL(
        TInt aResourceId, 
        const TDesC& aText, 
        TInt aPriority, 
        CAknNoteDialog::TTimeout aTimeout, 
        CAknNoteDialog::TTone aDefaultTone, 
        TInt aUserTone, 
        TInt aGraphic, 
        TInt aGraphicMask, 
        TInt aAnimation, 
        TInt aSoftkeys,
        TInt aPreallocatedNoteId);

    TBool IsPreallocatedNoteIdValid(const TInt aPreallocatedNoteId);

private:
    TPckgBuf<SAknGlobalNoteReturnParams> iRetPckg;
    TNotifierInfo iInfo;
    MAknKeyLockController* iKeyLockController;
    CArrayFixFlat<CGlobalNoteInfo*>* iGlobalNoteList;
    TInt iDisplayingNoteId;
    TInt iNoteId;
    CAknGlobalNoteDialog* iGlobalNote;
    MSoftNotificationObserver* iSoftNoteObserver;
    MSoftNotificationObserver* iNotificationDialogObserver;
    TInt iMaxDisplayPriority;
    TInt iMaxDisplayPriorityLimit;
    CAknEcsDetector* iEcsDetector;
    TBool iNotesDisabled;
    TInt iPreviousDisplayPriority;
    CAsyncCallBack* iDisplayCallback;
    CNotifierDialogController* iDialogController;

    TInt iAutoLock;
    TInt iCurrentPriority;

    friend class CAknGlobalNoteDialog;

    CIdle* iIdle;
    static TInt EnableAutolockEmulation(TAny* aThis);

    virtual SAknAlarmPSInfo* AlarmData() {return iAlarmData;}
    SAknAlarmPSInfo* iAlarmData;
    
    TBool iAppsKeyLocked;

    CAknMessageReaderLongPressDetector* iMessageReaderLongPressDetector;

    CSubscriber*            iAutolockStatusSubscriber;
    RProperty               iAutolockStatusProperty;
    };

#endif // __AKNSYSTEMPOPUP_H__

// End of File
