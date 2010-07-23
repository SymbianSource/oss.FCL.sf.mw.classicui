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
* Description:  Structures and constant declarations for the AVKON Notifiers.
*
*/

#ifndef AKNNOTIFYSTD_H
#define AKNNOTIFYSTD_H

#include <e32std.h>
#include <e32base.h>
#include <eiknotapi.h>

/**
 * @deprecated
 */
const TUid KAknPopupNotifierUid={0x100059DC};

/**
 * UID for identifying AVKON signal notifier.
 * @internal
 */
const TUid KAknSignalNotifierUid={0x100059AB};

/**
 * UID for identifying AVKON battery notifier.
 * @internal
 */
const TUid KAknBatteryNotifierUid={0x100059AC};

/**
 * UID for identifying AVKON indicator notifier.
 * @internal
 */
const TUid KAknSmallIndicatorUid={0x100059AD};

/**
 * @deprecated
 */
const TUid KAknAsyncDemoNotifierUid={0x100059AE};

/**
 * @deprecated
 */
const TUid KAknTestNoteUid={0x100059AF};

/**
 * UID for identifying AVKON key lock notifier.
 * @internal
 */
const TUid KAknKeyLockNotifierUid={0x100059B0};

/**
 * UID for identifying AVKON global note notifier.
 * @internal
 */
const TUid KAknGlobalNoteUid={0x100059B1};

/**
 * UID for identifying AVKON soft notification notifier.
 * @internal
 */
const TUid KAknSoftNotificationUid={0x100059B2};

/**
 * UID for identifying AVKON incall bubble notifier.
 * @internal
 */
const TUid KAknIncallBubbleUid={0x100059B3};

/**
 * UID for identifying AVKON list query notifier.
 * @internal
 */
const TUid KAknGlobalListQueryUid={0x100059B4}; 

/**
 * UID for identifying AVKON list msg query notifier.
 * @internal
 */
const TUid KAknGlobalListMsgQueryUid={0x20011102};

/**
 * UID for identifying AVKON message query notifier.
 * @internal
 */
const TUid KAknGlobalMsgQueryUid={0x100059CB};

/**
 * UID for identifying AVKON confirmation query notifier.
 * @internal
 */
const TUid KAknGlobalConfirmationQueryUid={0x100059DB};

/**
 * UID for identifying AVKON progress dialog notifier.
 * @internal
 */
const TUid KAknGlobalProgressDialogUid={0x10005A04};

/**
 * @deprecated
 */
const TUid KAknMemoryCardDialogUid={0x101F467A};

/**
 * @deprecated
 */
const TUid KAknNotifierControllerUid={0x1020721C};  


/**
 * AVKON notifier channel UID for notes.
 * @internal
 */
const TUid EAknNotifierChannelNote = {1};
/**
 * AVKON notifier channel UID for lists.
 * @internal
 */
const TUid EAknNotifierChannelList = {2};
/**
 * AVKON notifier channel UID for message queries.
 * @internal
 */
const TUid EAknNotifierChannelMsgQuery = {3};
/**
 * AVKON notifier channel UID for confirmation queries.
 * @internal
 */
const TUid EAknNotifierChannelConfirmationQuery = {4};
/**
 * AVKON notifier channel UID for progress dialogs.
 * @internal
 */
const TUid EAknNotifierChannelProgressDialog = {5};
/**
 * AVKON notifier channel UID for list message queries.
 * @internal
 */
const TUid EAknNotifierChannelListMsgQuery = {6};

/**
 * Signal state notifier parameter structure.
 * @internal
 */
struct SAknSignalNotifyParams
    {
    TInt iGprsState;
    TInt iValue;
    };

/**
 * Battery state notifier parameter structure.
 * @internal
 */
struct SAknBatteryNotifyParams
    {
    enum { ERecharge, EStopRecharge, ENoRecharge, ESetValue, ESetState } iType;
    TInt iValue;
    TInt iBatteryState;
    };

/**
 * Small indicator notifier parameter structure.
 * @internal
 */
struct SAknSmallIndicatorParams
    {
    TUid iSmallIndicatorUid;
    TInt iValue;
    };

/**
 * Incall status bubble notifier parameter structure.
 * @internal
 */
struct SAknIncallBubbleParams
    {
    TInt iIncallBubbleFlags;
    };

/**
 * Key lock notifier reasons.
 * @internal
 */
enum TKeyLockNotifierReason
    {
    ELockEnabled,
    ELockDisabled,
    EAllowNotifications,
    EStopNotifications,
    EInquire,
    EOfferKeylock,
    ECancelAllNotifications,
    EEnableAutoLockEmulation,
    EDisableWithoutNote,
    EEnableWithoutNote,
    // add normal keylock operations before this
    ECommandFSWToHideApplication=99
    };

/**
 * Soft note notifier parameter structure.
 * @internal
 */
struct SAknSoftNoteNotifierParams
    {
    TInt iNoteResource;
    TInt iNoteCbaResource;
    TInt iResponse;
    };

/**
 * Key lock notifier parameter structure.
 * @internal
 */
struct SAknKeyLockNotifierParams
    {
    TKeyLockNotifierReason iReason;
    TBool iEnabled;
    };

/**
 * Global note types.
 */
enum TAknGlobalNoteType
    {
    EAknGlobalInformationNote = 1,
    EAknGlobalWarningNote,
    EAknGlobalConfirmationNote,
    EAknGlobalErrorNote,
    EAknGlobalChargingNote,
    EAknGlobalWaitNote,
    EAknGlobalPermanentNote,
    EAknGlobalNotChargingNote,
    EAknGlobalBatteryFullNote,
    EAknGlobalBatteryLowNote,
    EAknGlobalRechargeBatteryNote,
    EAknCancelGlobalNote,
    EAknGlobalTextNote,
    EAknGlobalBatteryFullUnplugNote = 105,
    EAknGlobalUnplugChargerNote
    };

/**
 * Global note parameters.
 * @internal
 */
struct SAknGlobalNoteParams
    {
    TAknGlobalNoteType iType;
    TPtrC iText;
    TInt iPriority;
    TInt iSoftkeys;
    TInt iGraphic;
    TInt iGraphicMask;
    TInt iAnimation;
    };

/**
 * Global note return parameter structure.
 * @internal
 */
struct SAknGlobalNoteReturnParams
    {
    TInt iNoteId;
    };

/**
 * Global query commands.
 * @internal
 */
enum TAknGlobalQueryCmd
    {
    EAknShowGlobalQuery=1,
    EAknCancelGlobalQuery,
    EAknUpdateGlobalQuery,
    // list query cmds,
    EAknMoveDownGlobalListQuery,
    EAknMoveUpGlobalListQuery,
    EAknSelectGlobalListQuery,
    // Progess dialog cmds
    EAknFinishGlobalProgressDialog
    };

/**
 * Global list query parameter structure.
 * @internal
 */
struct SAknGlobalListQueryParams
    {
    TAknGlobalQueryCmd iCmd;
    TInt iIndex;
    };

/**
 * Global message query parameter structure.
 * @internal
 */
struct SAknGlobalMsgQueryParams
    {
    TAknGlobalQueryCmd iCmd;
    TInt iSoftkeys;
    };

/**
 * Global progress note parameter structure.
 * @internal
 */
struct SAknGlobalProgressDialogParams
    {
    TAknGlobalQueryCmd iCmd;
    TInt iValue;
    TInt iFinalValue;
    };

/**
 * Soft notification types.
 * @internal
 */
enum TAknSoftNotificationType
    {
    ENoSoftNotification = -1,
    ENetworkInformationNotification=0,
    ESelectNetworkNotification,
    EUnstructuredSSDataNotification,
    EVoiceMailNotification,
    ESeparateVoiceMailOnLine1Notification,
    ESeparateVoiceMailOnLine2Notification,
    ECellBroadcastNotification,

    EDeliveryReportNotification,
    EClass0SmsNotification,

    EMissedCallsNotification,
    ENewMessagesNotification,
    ENewMailNotification,

    EShowActiveNotifications,

    EShowGroupedNotification,
    ECustomSoftNotification,
    EChatMessageNotification,
    EMaxSoftNotification,
    ESetIdleState = 100
    };

/**
 * Soft notification parameters.
 * @internal
 */
struct SAknSoftNotificationParams
    {
    /** The type of the soft notification, @see @c TAknSoftNotificationType
    */
    TAknSoftNotificationType iType; 
    
    /**
     * @c iIsCancel is used to decide whether to spawn a new
     * (or add the number on an existing) soft notification or
     * to cancel a type of soft notification. Please note that
     * calling a cancel on a certain type of soft notification
     * cancels all soft notifications of that type.
     */
    TBool iIsCancel;

    /**
     * This parameter is intended only to be used when setting
     * the number of new messages. Stay clear otherwise!
     */
    TInt iCount;
    };


/**
 * @deprecated
 */
enum TAknSignalStates
    {
    EAknSignalGprsStateOff = 0,
    EAknSignalGprsStateOn = 1,
    EAknSignalGprsStateNotChanged = -1,
    EAknSignalStateNotChanged = -2,
    // Constants below are used for syncronizing signalpane and navipane background types.
    EAknSignalGprsIndicatorBgTypeNotDefined = -3,
    EAknSignalGprsIndicatorBgTypeWipe       = -4,
    EAknSignalGprsIndicatorBgTypeSolid      = -5                
    };

/**
 * @deprecated
 */
const TInt KAknSignalNumberOfGprsStates = 6;

/**
 * @deprecated
 */
struct SAknMemoryCardUIParams
    {
    TBool iStore;
    };

/**
 * @deprecated
 */
class MAknUINotifierBase: public MEikSrvNotifierBase2
    {
public:
    /**
     * @deprecated
     */
    TInt NotifierCapabilites(){return EScreenDeviceChangeSupported;}
    };

#endif // AKNNOTIFYSTD_H
