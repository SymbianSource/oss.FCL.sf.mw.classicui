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
* Description:  Class header for CAknSoftNotificationSubject.
*
*/

#ifndef __AKNSOFTNOTIFICATIONPLUGIN_H__
#define __AKNSOFTNOTIFICATIONPLUGIN_H__

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <eiknotapi.h>
#include <eikcmobs.h>
#include <aknnotedialog.h>
#include <aknstaticnotedialog.h>
#include <AknNotifyStd.h>
#include <AknMediatorFacade.h> // Not the best for the purpose but will do just fine.
#include <SecondaryDisplay/AknSecondaryDisplayDefs.h>
#include <AknNotify.h>
#include "AknSystemPopup.h"
#include "AknGroupedNotifierNote.h"
#include "AknNotifierControllerPlugin.h"
#include "aknprivatesoftnotificationparameters.h"
#include "aknmessagereaderlongpressdetector.h" // MAknGroupedNoteObserver    

class CAknSmsViewerLauncher;
class RDesReadStream;
class CAknSoftNotificationSubject;
class CAknDynamicSoftNoteEventManager;

class TSoftNoteEntry
    {
public:
    TSoftNoteEntry() : iType(ENoSoftNotification), iId(0), iCount(0), iCustomId(0) {};
    TAknSoftNotificationType iType;
    TInt iId;
    TInt iCount;
    TInt iCustomId;
    };

// Stack entry for Custom Soft Notifications.
class CCustomNotifParams;

NONSHARABLE_CLASS(AknSoftNoteSDObserver) : public MAknDialogMediatorObserver
    {
public: 
    TAknDialogMediatorObserverCommand MediatorCommandL( TUid, TUid, TInt, const TDesC8& aData );
    void NotifyMediatorExit(){}
    void SetSoftNotificationSubject( CAknSoftNotificationSubject* aSubject );
private:
    CAknSoftNotificationSubject* iSubject;    
    };

/**
 * Soft notification plugin to EikSrv.
 */
NONSHARABLE_CLASS(CAknSoftNotificationSubject) : 
    public CBase, 
    public MEikSrvNotifierBase2, 
    public MAknGroupedNotifierNoteObserver, 
    public MAknKeyLockObserver,
    public MSoftNotificationObserver,
    public MAknMessageNotifierObserver
    {
public:  // Constructors and destructor
    static CAknSoftNotificationSubject* NewL(
        MAknKeyLockController* aKeyLockObserver,
        CAknGlobalNoteSubject* aGlobalNoteController);
        
public: // Functions from base classes        
    /**
     * From MAknKeyLockController 
     * Called when the status of keylock changes.
     *
     * @param aStatus the new status of the keylock.
     */
    virtual void KeyLockStatusChange(TKeyLockStatus aStatus);
    
    /**
     * From MEikSrvNotifierBase.
     * Method to release the EikSrv plugin
     */
    void Release();

    /**
     * From MEikSrvNotifierBase. 
     * Method for registering the EikSrv plugin.
     *
     * @return TNotifierInfo Struct containing the plugin priorities etc.
     */
    TNotifierInfo RegisterL();

    /**
     * From MEikSrvNotifierBase. 
     * Method for getting the notifier info.
     * 
     * @return TNotifierInfo Struct containing the plugin priorities etc.
     */
    TNotifierInfo Info() const;

    /**
     * From MEikSrvNotifierBase. 
     * Method for starting the plugin. Synchronous version.
     *
     * @param aBuffer Buffer containing the parameters for the plugin, packaged in 
     *                TPckg<SAknSoftNotificationParams>.
     * @return This method will return KNullDesC.
     */
    TPtrC8 StartL(const TDesC8& aBuffer);

    /**
     * From MEikSrvNotifierBase.
     * Method for starting the plugin. Asynchronous version.
     *
     * @param aBuffer Buffer containing parameters for the plugin, packaged in 
     *                TPckg<SAknSoftNotificationParams>.
     * @param aReplySlot Return value of any type. Not used in this case.
     * @param aMessage RMessage to notify that the execution has ended.
     */
    void StartL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage);

    /**
     * From MEikSrvNotifierBase.
     * Method for cancelling the plugin execution.
     */
    void Cancel();

    /**
     * From MEikSrvNotifierBase. 
     * Method for updating the plugin while execution is in progress.
     *
     * @param aBuffer Buffer containing parameters for the plugin, packaged in 
     *                TPckg<SAknSoftNotificationParams>.
     * @return This method will return KNullDesC.
     */
    TPtrC8 UpdateL(const TDesC8& aBuffer);

    /**
     * From MEikSrvNotifierBase.
     * This method is not used but is required because of pure virtuality in base class.
     *
     * @param aBuffer Buffer containing parameters for this plugin.
     */
    void HandleMessageL(const TDesC8& aBuffer);
        
    /**
     * From MAknGroupedNotifierNoteObserver.
     * Called when user has pressed a key in the grouped soft notification dialog.
     *
     * @param aCommandId The id of the button the user pressed.
     * @param aSelectedItem The item that was selected when the user pressed a key.
     */
    void GroupedNoteCompletedL(TInt aCommandId, TAknGroupedNotifierItem aSelectedItem = EMaxItem);

    /**
     * From MAknGroupedNotifierNoteObserver.
     * Support for adding new items to grouped form.
     *
     * @since S60 3.0     
     * @param aText Array into which add new texts (item amount cannot be changed after this).
     * @param aOrder KeyArray for list to manage its entries, which must be uniqued (at a time) 
     *               and these must not collide with fixed values defined in 
     *               TAknGroupedNotifierItem. 
     */
    void AddItemsL(CDesCArray& aTexts, CArrayFix<TInt>& aOrder);
    
    /**
     * From MAknGroupedNotifierNoteObserver.
     * Custom soft notifications may have custom softkeys. This method returns the softkeys
     * and the accept softkey id for the given custom notification.
     *
     * @since S60 3.1
     * @param aCustomItem A custom notification for which to search softkeys.
     * @param aSoftkeyResourceId On return, the softkeys resource identifier.
     * @param aAcceptKeyId On return, the key that is used to accept the grouped notifier item, 
     *        i.e. to launch the handler application.
     * @param aLeftSoftkey Custom text for left softkey.
     * @param aRightSoftkey Custom text for right softkey.
     */      
    void SoftkeysForCustomItem(TAknGroupedNotifierItem aCustomItem, TInt& aSoftkeyResourceId, 
        TInt& aAcceptKeyId, TDes& aLeftSoftkey, TDes& aRightSoftkey);

    // From MSoftNotificationObserver
    void SoftNoteCompleted(TInt aId, TInt aCommand);
    TBool ShowSoftNoteL(TInt aPriority, const TDesC& aText);
    TBool CancelSoftNote(TInt aPriority);

public: // from MAknMessageNotifierObserver

    /**
     * From MAknMessageNotifierObserver. 
     * 
     * @return true if shown notifier is a message or a email 
     */
    TBool MessageNotifierShown();

    /**
     * From MAknMessageNotifierObserver. 
     * 
     * @return CEikButtonGroupContainer of the grouped note
     */
    CEikButtonGroupContainer* ButtonGroupContainer();
    
private:
    void ConstructL();

    ~CAknSoftNotificationSubject();

    /**
     * The constructor is private. 
     */
    CAknSoftNotificationSubject(
        MAknKeyLockController* aKeyLockObserver,
        CAknGlobalNoteSubject* aGlobalNoteController);

    void HandleNotifierMessageL(const TDesC8& aBuffer, TInt& aNoteId );

    /**
     * The following method is called after the notifier has been started to reflect the changes
     * to the UI mechanism. The parameter aType is the most recently requested soft notification 
     * type.
     */
    void UpdateNoteL(TAknSoftNotificationType aType, const TDesC& aText, TInt aCount, TInt aCountChanged);

    void DisplayUngroupedNotifierL(
        TAknSoftNotificationType aType, 
        const TDesC& aText, 
        TInt aCount = 0);

    void RemoveByType(TAknSoftNotificationType aType, TInt aId = 0);

    TAknSoftNotificationType TypeFromId(TInt aId);
    void CompleteId(TInt aId);
    void ScheduleGroupedNotifierL();
    void DoSoftNoteCompletedL(TInt aId, TInt aCommand);

    /**
     * A helper method to show the grouped soft notification dialog.
     */
    void ShowGroupedNotificationL();
    
    /**
     * Helper method to find out if a grouped soft notification should be formed.
     */
    TBool IsGroupedFormed();

    void LaunchSelectNetworkAppL();
    void LaunchUSSDAppL();
    void LaunchMissedCallsAppL();
    void LaunchNewMessagesAppL();
    void LaunchNewMailAppL();
    void LaunchNewCbsAppL();
    void LaunchNewVoiceMailAppL(TInt aType);
    
    void LaunchViewL(
        const TVwsViewId& aViewId, 
        TUid aCustomMessageId, 
        const TDesC8& aCustomMessage);

    void SaveSoftNotificationsL();
    void SaveNoteL(RWriteStream& aFile, TSoftNoteEntry& aEntry);

    void LoadAndQueueSoftNotesL();
    void LoadAndQueueNoteL(RReadStream& aStream);

    void ClearAllNotes();

    /**
     * Method for resetting user inactivity timers (e.g. screen saver timer).
     */
    void ReportUserActivity();

    TBool CheckIfAlreadyExists(TAknSoftNotificationType aType);

    TBool AutoLockEnabled();

    void SetNcnFlag(TBool aValue);
    static TInt HandleNcnFlagStateChange(TAny *aPtr);

    void HandleCustomNoteCompletedL(CCustomNotifParams* aParams, TInt aCommand);
    
    /**
     * Called when custom note has been canceled by the user.
     * 
     * @param aParams Custom notification data.
     * @param aCommand Command that canceled the notification.
     */
    void HandleCustomNoteCanceledL( CCustomNotifParams* aParams, TInt aCommand );
    
private: // Data
    TNotifierInfo iInfo;
    MAknKeyLockController* iKeyLockController;
    CAknGlobalNoteSubject* iGlobalNoteController;
    
    // The array keeps track of unselected soft notifications in priority order.
    TInt iSoftNotificationAmounts[EMaxSoftNotification];

    CArrayFixFlat<TSoftNoteEntry>* iSoftNoteEntryList;    
    TAknSoftNotificationType iLatestType;
    
    CAknGroupedNotifierNote* iGroupedNote;
    CAknSmsViewerLauncher* iSmsViewer;

    /// Some of the data of CCustomNotifParams is referred from 
    /// CAknGlobalNoteSubject. Make sure the source is not deleted before
    /// referrer is removed.
    CCustomNotifParams* iCustomNoteParamsStack;

    friend class AknSoftNoteSDObserver;
    
private: // New member functions.
    CCustomNotifParams* SeekCustomNoteForId(TInt aID, TBool aSeekByGNoteId = EFalse);
    void AddNewCustomNoteL(RDesReadStream& readStream, TInt aCount, TBool aNewNote = EFalse );
    void AddNewCustomNoteL(RReadStream& readStream, TInt aCount, TBool aNewNote = EFalse );
    void RemoveCustomNoteForId(TInt aID, TBool aSeekByGNoteId = EFalse);
    void LaunchNewIMAppL();
    
    /**
     * Load unique identifier from persistent store.
     */
    void LoadUniqueIdL();
    /**
     * Save unique identifier to persistent store.
     */
    void StoreUniqueIdL();
    /**
     * Increases unique identifier counter and finds next free identifier.
     * @return Next free unique identifier.
     */
    TInt GenerateUniqueId();
    /**
     * Write response from given parameters.
     * @param aResponse Response buffer to write into.
     * @param aNoteId Notification id to write. 
     */
    void WriteResponse( TDes8& aResponse, TInt aNoteId ) const;

private: // New member data.
    TBool iNotificationsSaved;
    CIdle* iIdle;
    static TInt SetIdleStateFalse(TAny* aThis);
    TBool iKeysLocked;
    
public: // To allow static method above access this.
    TBool iIdleStateActive;
    
private:
    CAknMediatorFacade* iCoverClient;
    AknSoftNoteSDObserver iObsStub;
    /// Unique dynamic soft notification counter.
    TInt iUniqueIdCounter;
    /// Dynamic soft notification response buffer. Space for TInt (32bit).
    TBuf8<4> iResponseMsg;
    /// Not own. Dynamic soft notification event manager.
    CAknDynamicSoftNoteEventManager* iDynamicSoftNoteManager;
    /// Own. Central Repository to read messaging settings. 
    CRepository* iMessagingRepository;
    };

#endif // __AKNSOFTNOTIFICATIONPLUGIN_H__

// End of File
