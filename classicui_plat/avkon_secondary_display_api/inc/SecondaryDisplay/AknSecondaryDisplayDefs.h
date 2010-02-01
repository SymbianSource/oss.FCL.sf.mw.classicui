/*
* Copyright (c) 2005-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Secondary display constant definitions.
*
*/

#ifndef __AKNSECONDARYDISPLAYDEF_H__
#define __AKNSECONDARYDISPLAYDEF_H__

#include <e32std.h>
#include <w32std.h>
#include <AknCapServerDefs.h>
#include <AknNotifyStd.h>

#define KAknSecondaryDisplayCategory KAknCapServerUid 

enum TAvkonGlobalSDInfo
    {
    EAknChargingNote = EAknGlobalChargingNote,
    EAknNotChargingNote = EAknGlobalNotChargingNote,
    EAknBatteryFullNote = EAknGlobalBatteryFullNote,
    EAknBatteryLowNote = EAknGlobalBatteryLowNote,
    EAknRechargeNote = EAknGlobalRechargeBatteryNote,
    EAknMemoryCardQuery,
    EAknKeysLockedNote,
    EAknKeysReleasedNote,
    EAknAlarmNote, //SAknAlarmPSInfo
    EAknSwitchOnAfterAlarmNote,
    EAknDiskWarnignNote,
    EAknDiskFullNote,
    EAknMMCWarningNote,
    EAknMMCFullNote,
    EAknListQueryItemsInfo,
    EAknListQueryUpdateSelection, // SAknIntegerUpdate
    EAknGlobalNotifierUpdateSoftkeys, // SAknIntegerUpdate
    
    // Data agreement: [cmd id(TInt32), value(TInt32) and final value(TInt32)]
    EAknGlobalPDialogValuesUpdate, 
    
    // Unidentified global note.
    EAknUnidentifiedNote, 
    
    // SAknIntegerUpdate (iCmd TAknIntegerUpdateCommands::EAknTrappedError, iId the error id). 
    EAknErrorNote, 
    
    EAknUnidentifiedListQuery,
    EAknUnidentifiedMsgQuery,
    EAknUnidentifiedConfirmationNote,
    EAknUnidentifiedProgressNote,  
    
    EAknNonDialogTypes = 100,
    
    // Related struct SAknSmallIndicatorData.
    EAknSmallIndicatorSDInfo = EAknNonDialogTypes, 
    
    // SAknSoftNotificationData + custom soft notification information + in case of grouped 
    // notification, counts of fixed types, ie: entry count (int32) + entry count * 
    // SAknSoftNotificationData + count of custom soft notifications (CCSN) uint8 + CAknSDData
    // * CCSN + 4 * SAknSoftNotificationData.
    EAknSoftNotificationSDInfo, 
   
    // SAknSignalNotifyParams, aknnotifystd.h
    EAknSignalIndicatorSDInfo, 
    
    // SAknBatteryNotifyParams, aknnotifystd.h
    EAknBatteryIndicatorSDInfo,
    
    EAknBatteryFullUnplugNote = EAknGlobalBatteryFullUnplugNote,
    EAknUnplugChargerNote,
    
    // IDs for mass storage out-of-disk notes.
    EAknMassStorageWarningNote,
    EAknMassStorageFullNote
    };

enum TAknSecondaryDisplayFeedback
    { // leave first one hundred to app specific range
    EAknDialogFeedback = 100 // SAknDialogFeedBack
    };
    
struct SAknSoftNotificationFeedbackData
    {
    TAknSoftNotificationType iType; // notification to be cancelled
    TInt iCategory; // only used with custom notification
    TInt iDialogID; // only used with custom notification
    };
    
// Defines the softkeys used by the alarm note.
enum TAknAlarmSoftkeys 
    {
    EAknAlarmStopSnooze,
    EAknAlarmStopSilent,
    EAknAlarmStopNone
    };
     
/**
 * Data agreement: - First 16 bits of buffer, count of elements as unsigned
 *                 - Table of SAknSmallIndicatorData
 */
struct SAknSmallIndicatorData
    {
    TInt iIndicator;      // values defined in avkon.hrh (enum does not have name)
    TInt iIndicatorState; // "
    };

/**
 * Data agreement: - First 16 bits of buffer, count of elements as unsigned
 *                 - Table of SAknSoftNotificationData which have count different from 0
 */
struct SAknSoftNotificationData
    {
    TAknSoftNotificationType iType;
    TInt iCount;    
    };    


// KAvkonBitmapFile is used when iFileName is left empty
struct SAknGlobalNotificationImageInfo
   {
   TInt iImageId;
   TInt iImageMaskId;
   TInt iSkinsMajor;
   TInt iSkinsMinor;
   TFileName iFileName;
   };


// This structure is sent to coveui if client chooses to publish a dialog, but does not 
// define any data for cover ui.
struct SAknGlobalNoteData // items from class TGlobalNoteInfo
    {    
    TInt iResourceId;
    TInt  iTimeOut;
    TInt  iTone;
    TInt  iTextLength;
    TInt iSoftkeys;    
    SAknGlobalNotificationImageInfo iImage;    
    TInt iAnimation;
    TInt iPlural;    
    };    

// Alarm information. Comes directly from alarm ui implementation.
struct SAknAlarmPSInfo
    {   
    // declare inside class to avoid name clash
    enum TAlarmType
        { 
        /** Appointment. */
        EAknAppt,
        /** To-do. */
        EAknTodo,
        /** Event. */
        EAknEvent,
        /** Anniversary. */
        EAknAnniv,
        /** Clock */
        EAknClock
        };
        
    TAlarmType iType; 
    TBuf<24> iTime;
    TBuf<24> iDate;
    TBuf<64> iSubject;
    TBuf<64> iLocation;
    TAknAlarmSoftkeys iAlarmSoftkeys;
    };

// Feedback

struct SAknDialogFeedback
    {
    SAknDialogFeedback(const TKeyEvent& aKey):iCommandId(EAknDialogFeedback), iKey(aKey){}
    TInt iCommandId;
    TKeyEvent iKey;
    };

struct SAknIntegerUpdate
    {
    TInt iCmd;
    TInt iId;
    };

// Spesific integer update (SAknIntegerUpdate) command ids (iCmd). 
enum TAknIntegerUpdateCommands
    {
    EAknTrappedError = 100 // for EAknErrorNote integer update
    };

const TInt KAknMediatorUpdateChannelOffset(1000);

#endif // __AKNSECONDARYDISPLAYDEF_H__