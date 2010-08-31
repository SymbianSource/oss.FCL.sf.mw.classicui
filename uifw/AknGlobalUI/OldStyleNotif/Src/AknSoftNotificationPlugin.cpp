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
* Description: 
*
*/

// INCLUDE FILES

#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <vwsdefpartner.h>
#endif
#include <avkon.rsg>
#include <eikbtgpc.h>
#include <eikenv.h>
#include <avkon.hrh>
#include <aknnotpi.rsg>
#include <aknnotedialog.h>
#include <AknPanic.h>
#include <aknappui.h>
#include <StringLoader.h>
#include "AknSoftNotificationPlugin.h"
#include <AknNotifyStd.h>
#include <msvstd.hrh>   // for Messaging centre constants
#include "AknNotifyPlugin.hrh"
#include <centralrepository.h>
#include <AvkonInternalCRKeys.h>
#include <viewcli.h>
#include <s32file.h>
#include <s32mem.h>
#include <e32cmn.h>
#include "AknNotifierController.h"
#include <eikfrlb.h>
#include <eiklbi.h>
#include <bautils.h>
#include <AknNotifySignature.h>
#include <apgcli.h>
#include <aknsoundsystem.h>
#include "AknCapServerEntry.h"
#include "AknDynamicNotificationData.h"
#include "aknsoftnoteconsts.h"
#include "akndynamicsoftnoteeventmanager.h"

// Messaging UIDs
// Traditional messaging UIDs.
#define KMessagingCentreMainViewUid TVwsViewId(TUid::Uid(0x100058C5),TUid::Uid(0x01))
#define KMessagingCentreInboxView TVwsViewId(TUid::Uid(0x100058C5),TUid::Uid(0x02))

// Conversational messaging UIDs.
#define KConversationApplicationViewUid TVwsViewId(TUid::Uid(0x2002A540),TUid::Uid(0x01))
const TInt KConversationListViewUid  = 0x01 ;

// Messaging central repository. Used to read default view settings.
const TUid KCRUidMessageSettings = {0x101F87EB};
const TUint32 KMessagingAppDefaultViewCRKey = 0x0000001C;  

// Cbs topic list view Uid. This view is shown when there are several cbs messages
#define KCbsApplicationUidTopicListView TVwsViewId(TUid::Uid(0x101F4CD3),TUid::Uid(0x02))
// Cbs message view Uid. This view is shown when there is only one new cbs message
#define KCbsApplicationUidMessageView TVwsViewId(TUid::Uid(0x101F4CD3),TUid::Uid(0x04))

// Voice messages are handleb by speed dial application.
#define KSpeeddialVmbxDialUidView TVwsViewId( TUid::Uid( 0x1000590A ),TUid::Uid( 0x02 ) )

// Logs application UID
#define KUidLogs TUid(TUid::Uid(0x101F4CD5))
_LIT8(KLogsActivationMsg ,"missed");

_LIT8( KExternalLaunch, "outside" );

#define KUidGS TUid(TUid::Uid(0x100058EC))
#define KSettListNetViewId TUid(TUid::Uid(0x102824A8)) // Implementation UID for GSNetworkPlugin in GS.
#define KSelectNetworkAppUidView TVwsViewId(KUidGS, KSettListNetViewId)

#define KChatSpecificView TVwsViewId(TUid::Uid(0x101F4673),TUid::Uid(7))
const TInt KGSCustomActivateNetView = 9000;

const TInt KSoftNoteGranularity = 4;

const TInt KNetworkInfoPriority     = 2500;
const TInt KSelectNetworkPriority   = 2400;
const TInt KUSSDPriority            = 2300;
const TInt KVoiceMailPriority       = 2200;
const TInt KVoiceMailOnLinePriority = 2100;
const TInt KCBSPriority             = 2000;
const TInt KGroupedNotification     = 1500;
const TInt KMissedCallsPriority     = 1300;
const TInt KNewMessagesPriority     = 1200;
const TInt KChatMessagePriority     = 1150;
const TInt KNewEmailPriority        = 1100;

/// Lowest value for unique id. Id range: KMinimumUniqueId...KMaxTInt.
const TInt KMinimumUniqueId         = 0x00ff;

#define KDeliveryTextMaxLength 64

_LIT( KAknSNFilename, "c:\\private\\10207218\\softnote.dat" );
/// File where to store unique identification counter.
_LIT( KAknDynamicIdFilename, "c:\\private\\10207218\\dynamic.dat" );

NONSHARABLE_CLASS(CCustomNotifParams) : public CBase
    {
public:
    ~CCustomNotifParams()
        {
        delete iParamData;
        delete iDynamicData;
        if ( iCoeResourceHandle )
            {
            CCoeEnv::Static()->DeleteResourceFile(iCoeResourceHandle);
            }
        };
        
    /**
     * Internalize content of CCustomNotifParams from stream.
     * @param aStream Source stream.
     */
    void InternalizeL( RReadStream& aStream );
    /**
     * Externalize content of CCustomNotifParams to stream.
     * @param aStream Destination stream.
     */
    void ExternalizeL( RWriteStream& aStream ) const;
    /**
     * Return text for custom notification.
     * 
     * @param aCount Count of items to be displayed in notification.
     * @param aGroupText ETrue  : Text is shown in grouped list.
     *                   EFalse : Text is shown in single dialog.
     * @return Custom text.
     */
    const TDesC& CustomText( TInt aCount, TBool aGroupText ) const;
    /**
     * @return View activation message or KNullDesC8 if not defined.
     */
    const TDesC8& ViewActivationMessage() const;
    /**
     * @return Flag whether user events are wanted by the event manager.
     */
    TBool EnableObserver() const;
    
    TInt iId;
    TInt iNoteId;
    TBool iSupportsGroupedform;
    TBool iHasViewInfo;
    TInt iCount;
    /// Data for custom soft notification.
    CAknPrivateSoftNoteParameters* iParamData;
    /// Data for dynamic soft notification.
    CAknDynamicNotificationData* iDynamicData;
    /// Parameter type to distinguish dynamic note from custom note. 
    /// Use KAknSoftNotificationCustom or KAknSoftNotificationDynamic. 
    TInt iParamType;
    CCustomNotifParams* iNext;
    TInt iCoeResourceHandle;
    };

TBool CCustomNotifParams::EnableObserver() const
    {
    if (iDynamicData)
        {
        return iDynamicData->EnableObserver();
        }
    else
        {
        return EFalse;
        }        
    }

// ---------------------------------------------------------
// CCustomNotifParams::InternalizeL
// ---------------------------------------------------------
//
void CCustomNotifParams::InternalizeL( RReadStream& aStream )
    {
    iParamType = aStream.ReadInt16L();
    switch( iParamType )
        {
        case KAknSoftNotificationCustom:
            {
            CAknPrivateSoftNoteParameters* param = 
                CAknPrivateSoftNoteParameters::NewL(); 
            aStream >> *param;
            delete iParamData;
            iParamData = param;
            break;
            }
        case KAknSoftNotificationDynamic:
            {
            CAknDynamicNotificationData* data = 
                CAknDynamicNotificationData::NewLC( aStream );
            
            // Duplicate values to ease the changes required
            //
            CAknPrivateSoftNoteParameters* param = 
                CAknPrivateSoftNoteParameters::NewL();
            CleanupStack::PushL( param );
            
            // copy some values
            param->iCustomMessageId = data->CustomMsgUid();
            param->iPluralViewId = data->PluralViewId();
            param->iViewId = data->ViewId();
            param->iPriority = data->Priority();
            param->iTone = data->Tone();
            param->iNoteResourceId = data->Id();
            param->iAcceptSoftKey = EAknSoftkeyShow;
            
            // secondary display data
            if( aStream.ReadInt8L() ) 
                {
                // item has secondary display data
                CAknSDData* sddata = new (ELeave) CAknSDData();
                CleanupStack::PushL( sddata );
                aStream >> *sddata;
                delete param->iSecondaryDisplayData;
                param->iSecondaryDisplayData = sddata;
                CleanupStack::Pop( sddata );
                }

            // Assign values when we can't leave anymore. 
            CleanupStack::Pop( 2, data ); // param
            delete iParamData;
            iParamData = param;
            delete iDynamicData;
            iDynamicData = data;

            break;
            }
        default:
            {
            User::Leave( KErrCorrupt );
            break;
            }
        }
    }

// ---------------------------------------------------------
// CCustomNotifParams::ExternalizeL
// ---------------------------------------------------------
//
void CCustomNotifParams::ExternalizeL( RWriteStream& aStream ) const
    {
    if( iParamType <= KAknSoftNotificationCustom && iParamData ) // default
        {
        aStream.WriteInt16L( KAknSoftNotificationCustom );
        aStream << *iParamData;
        }
    else if( iParamType == KAknSoftNotificationDynamic && iDynamicData )
        {
        aStream.WriteInt16L( KAknSoftNotificationDynamic );
        aStream << *iDynamicData;
        
        // secondary display data
        if( iParamData && iParamData->iSecondaryDisplayData )
            {
            aStream.WriteInt8L( ETrue );
            aStream << iParamData->iSecondaryDisplayData;
            }
        else
            {
            aStream.WriteInt8L( EFalse );
            }
        }
    else
        {
        User::Leave( KErrCorrupt );
        }
    }

// ---------------------------------------------------------
// CCustomNotifParams::CustomText
// ---------------------------------------------------------
//
const TDesC& CCustomNotifParams::CustomText( 
    TInt count, TBool aGroupText ) const
    {
    if( iParamType == KAknSoftNotificationDynamic && iDynamicData )
        {
        if( count > 1 )
            {
            // use plural text
            return aGroupText ? iDynamicData->PluralLabelGroup() :
                iDynamicData->PluralLabel();
            }
        else
            {
            // use singular text
            return aGroupText ? iDynamicData->SingularLabelGroup() : 
                iDynamicData->SingularLabel();
            }
        }
    return KNullDesC();
    }

// ---------------------------------------------------------
// CCustomNotifParams::ViewActivationMessage
// ---------------------------------------------------------
//
const TDesC8& CCustomNotifParams::ViewActivationMessage() const
    {
    if( iParamType == KAknSoftNotificationDynamic && iDynamicData )
        {
        return iDynamicData->CustomMsg();
        }
    else if( iParamData && iParamData->iViewActivationMsg )
        {
        return *iParamData->iViewActivationMsg;
        }
    return KNullDesC8();
    }

void AknSoftNoteSDObserver::SetSoftNotificationSubject( CAknSoftNotificationSubject* aSubject )
    {
    iSubject = aSubject;
    }
    
TAknDialogMediatorObserverCommand AknSoftNoteSDObserver::MediatorCommandL( TUid, TUid, TInt, 
    const TDesC8& aData)
    {
    RDesReadStream* readStreamSDData = new(ELeave) RDesReadStream();
    CleanupStack::PushL( readStreamSDData );
    readStreamSDData->Open( aData ); // aData = data received from Mediator    
    TPckgBuf<SAknSoftNotificationFeedbackData> paramsBuf;
    *readStreamSDData >> paramsBuf;
    
    if ( paramsBuf().iType == EShowGroupedNotification ) 
        {
        CAknGroupedNotifierNote* groupedNote = iSubject->iGroupedNote;
        iSubject->GroupedNoteCompletedL(EAknSoftkeyExit, EMaxItem); // saves as well
        // iSubject->iGroupedNote equals to NULL now
        delete groupedNote;
        }
        
    else if (paramsBuf().iType != ECustomSoftNotification )
        {
        TAknSoftNotificationType type = paramsBuf().iType;
        iSubject->iSoftNotificationAmounts[ type ] = 0;
        iSubject->RemoveByType( type );

        if ( type == EMissedCallsNotification ||
             type == ENewMessagesNotification ||
             type == ENewMailNotification ||
             type == EChatMessageNotification)
            {
            iSubject->RemoveByType(EShowGroupedNotification);
            iSubject->ScheduleGroupedNotifierL();
            }
        else
            {
            iSubject->iGlobalNoteController->TryDisplayNextNoteL();
            }
        
        iSubject->iNotificationsSaved = EFalse;
        iSubject->SaveSoftNotificationsL();
        }
        
    else
        {
        CCustomNotifParams* params = iSubject->iCustomNoteParamsStack;
        for (;params;params = params->iNext)
            {
            if (params->iParamData->iSecondaryDisplayData)
                {
                if ( params->iParamData->iSecondaryDisplayData->iCategory.iUid == paramsBuf().iCategory 
                     && params->iParamData->iSecondaryDisplayData->iDialogIdx == paramsBuf().iDialogID )
                    {
                    TInt noteId = params->iNoteId;
                    if ( noteId == 0 )
                        {
                        iSubject->RemoveCustomNoteForId( params->iId );
                        iSubject->ScheduleGroupedNotifierL();
                        }
                    else
                        {
                        iSubject->RemoveCustomNoteForId( noteId, ETrue );
                        if ( noteId != KErrNotFound ) // was added to global notes queue
                            {
                            iSubject->iGlobalNoteController->TryDisplayNextNoteL();
                            }
                        }

                    iSubject->iNotificationsSaved = EFalse;
                    iSubject->SaveSoftNotificationsL();
                    break;
                    }
                }
            }
        }
        
    readStreamSDData->Close(); 
    CleanupStack::PopAndDestroy(); // read stream
    return EDoNothingWithThisCommand;
    }
    
    
// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknSoftNotificationSubject::CAknSoftNotificationSubject(
    MAknKeyLockController* aKeyLockController,
    CAknGlobalNoteSubject* aGlobalNoteController)
:iKeyLockController(aKeyLockController), 
    iGlobalNoteController(aGlobalNoteController), 
    iNotificationsSaved(ETrue), // We'll have to assume there are saved notifications on startup
    iUniqueIdCounter(KMinimumUniqueId)
    {
    iMessagingRepository = NULL;
    iDynamicSoftNoteManager = CAknDynamicSoftNoteEventManager::UniqueInstance();
    __ASSERT_ALWAYS(iDynamicSoftNoteManager != NULL, User::Invariant());
    }

// EPOC default constructor can leave.
void CAknSoftNotificationSubject::ConstructL()
    {
    iKeyLockController->AddObserverL(this);

    iSoftNoteEntryList = new(ELeave)CArrayFixFlat<TSoftNoteEntry>(KSoftNoteGranularity);
    iGlobalNoteController->SetSoftNoteObserver(this);
    // Set initial state to 'non-idle'
    iGlobalNoteController->SetMaxDisplayPriorityL(KMinimumSoftNotePriority);

    iGlobalNoteController->SetMessageNotifierObserver(this);

    // Messaging settings repository
    TRAP_IGNORE( iMessagingRepository = CRepository::NewL(KCRUidMessageSettings) );
    
#ifdef __COVER_DISPLAY  
    // Just to give something, not used.
    iCoverClient = CAknMediatorFacade::NewL((CEikDialog*)CEikonEnv::Static()->Alert()->AsEikDialog()); 
    
    iCoverClient->SetObserver(&iObsStub);
    iObsStub.SetSoftNotificationSubject( this );
    iCoverClient->CatUid() = KAknSecondaryDisplayCategory;
    iCoverClient->DialogIndex() = EAknSoftNotificationSDInfo;
#endif
    
    // If the loading fails, then we'll start using unique id's 
    // from KMinimumUniqueId.
    TRAPD( err, LoadUniqueIdL() );
    if( err )
        {
#ifdef _DEBUG
        _LIT( KDmsg, "AknSoftNotificationPlugin, Unique Id restore err: %d" );
        RDebug::Print( KDmsg, err );
#endif //_DEBUG
        }
    }

CAknSoftNotificationSubject::~CAknSoftNotificationSubject()
    {
    delete iSoftNoteEntryList;

    while(iCustomNoteParamsStack)
        {
        CCustomNotifParams* params = iCustomNoteParamsStack->iNext;
        delete iCustomNoteParamsStack;
        iCustomNoteParamsStack = params;
        }

    delete iIdle;
    delete iCoverClient;
    
    if(iKeyLockController)
        {
        iKeyLockController->RemoveObserver(this);
        }    

    if ( iMessagingRepository )
        {
        delete iMessagingRepository;
        iMessagingRepository = NULL;
        }
    }

// Two-phased constructor.
CAknSoftNotificationSubject* CAknSoftNotificationSubject::NewL(
    MAknKeyLockController* aKeyLockController,
    CAknGlobalNoteSubject* aGlobalNoteController )
    {
    CAknSoftNotificationSubject* self = new (ELeave) CAknSoftNotificationSubject(
        aKeyLockController, 
        aGlobalNoteController);
        
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self);
    return self;
    }

// ---------------------------------------------------------
// CAknSoftNotificationSubject::KeyLockStatusChange
// ---------------------------------------------------------
//
void CAknSoftNotificationSubject::KeyLockStatusChange(TKeyLockStatus aStatus)
    {
    if ( aStatus == EKeyLockEnabled )
        {
        iKeysLocked = ETrue;
        }
    else if ( aStatus == EKeyLockDisabled )
        {
        iKeysLocked = EFalse;
        }
        
    if ( iGroupedNote && iGroupedNote->ListBox())
        {
        if ( aStatus == EKeyLockEnabled )
            {
            iGroupedNote->ListBox()->View()->ItemDrawer()->SetFlags(
                CListItemDrawer::EDisableHighlight);
                
            iGroupedNote->DrawDeferred();
            }
        else if ( aStatus == EKeyLockDisabled )
            {
            iGroupedNote->ListBox()->View()->ItemDrawer()->ClearFlags(
                CListItemDrawer::EDisableHighlight);
                
            iGroupedNote->DrawDeferred();
            }
        }
    }    

// ---------------------------------------------------------
// CAknSoftNotificationSubject::Release()
//
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknSoftNotificationSubject::Release()
    {
    delete this;
    }

// ---------------------------------------------------------
// CAknSoftNotificationSubject::RegisterL()
// (other items were commented in a header).
// ---------------------------------------------------------
//
CAknSoftNotificationSubject::TNotifierInfo CAknSoftNotificationSubject::RegisterL()
    {
    iInfo.iUid=KAknSoftNotificationUid;
    iInfo.iChannel=EAknNotifierChannelNote;
    iInfo.iPriority=ENotifierPriorityHigh;
    return iInfo;
    }

// ---------------------------------------------------------
// CAknSoftNotificationSubject::Info()
// (other items were commented in a header).
// ---------------------------------------------------------
//
CAknSoftNotificationSubject::TNotifierInfo CAknSoftNotificationSubject::Info() const
    {
    return iInfo;
    }

// ---------------------------------------------------------
// CAknSoftNotificationSubject::StartL(const TDesC8& aBuffer)
//
// (other items were commented in a header).
// ---------------------------------------------------------
//
TPtrC8 CAknSoftNotificationSubject::StartL(const TDesC8& aBuffer)
    {
    TInt id = KErrNotFound;
    HandleNotifierMessageL( aBuffer, id );

    if( id > 0 )
        {
        // Custom note id generated, report it back to client
        WriteResponse( iResponseMsg, id );
        return iResponseMsg;
        }
    return KNullDesC8();
    }

// ---------------------------------------------------------
// CAknSoftNotificationSubject::StartL()
// This is the asynchronous version that should not be used
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknSoftNotificationSubject::StartL(const TDesC8& aBuffer, TInt aReplySlot, 
    const RMessagePtr2& aMessage)
    {
    TInt id = KErrNotFound;
    HandleNotifierMessageL( aBuffer, id );    
    if( id > 0 )
        {
        // Custom note id generated, report it back to client
        WriteResponse( iResponseMsg, id );
        aMessage.WriteL( aReplySlot, iResponseMsg );
        }
    aMessage.Complete( KErrNone );
    }

// ---------------------------------------------------------
// CAknSoftNotificationSubject::Cancel()
// Not much happening here. If a certain type of of soft
// notification should be canceled, please use the wrapper's
// method
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknSoftNotificationSubject::Cancel()
    {
    }

// ---------------------------------------------------------
// CAknSoftNotificationSubject::UpdateL(const TDesC8& aBuffer)
//
// (other items were commented in a header).
// ---------------------------------------------------------
//
TPtrC8 CAknSoftNotificationSubject::UpdateL(const TDesC8& aBuffer)
    {
    return StartL( aBuffer );
    }

// ---------------------------------------------------------
// HandleMessageL(const TDesC8& aBuffer)
// Required because of framework
// (other items were commented in a header).
// ---------------------------------------------------------
//
void HandleMessageL( const TDesC8& /*aBuffer*/ )
    {
    }

void CAknSoftNotificationSubject::HandleNotifierMessageL( 
    const TDesC8& aBuffer, TInt& aNoteId )
    {
    RDesReadStream readStream( aBuffer );

    if ( aBuffer.Length() < 4 // TInt takes four char
        || readStream.ReadInt32L() != KAKNNOTIFIERSIGNATURE )
        {
        User::Leave( KErrArgument );
        }

    TAknSoftNotificationType type = STATIC_CAST(TAknSoftNotificationType,readStream.ReadUint8L());
    TInt16 count = readStream.ReadInt16L();
    
    //set current idle status to appui
    if ( type == ESetIdleState )
        {
        ((CAknCapAppServerAppUi*)(CEikonEnv::Static())->EikAppUi())
            ->SetIdleActive( count ? ETrue : EFalse );
        }
        
    switch ( type )
        {
        case ENetworkInformationNotification:
        case ESelectNetworkNotification:
        case EUnstructuredSSDataNotification:
        case EVoiceMailNotification:
        case ESeparateVoiceMailOnLine1Notification:
        case ESeparateVoiceMailOnLine2Notification:
        case ECellBroadcastNotification:
        case EDeliveryReportNotification:
        case EClass0SmsNotification:
        case EMissedCallsNotification:
        case ENewMessagesNotification:
        case ENewMailNotification:
        case EShowActiveNotifications:
        case EShowGroupedNotification:
        case ECustomSoftNotification:
        case EChatMessageNotification:
        case ESetIdleState:
            break;
        case ENoSoftNotification:
        case EMaxSoftNotification:
        default:
            // Simply return with no error code.
            return;
        }

    // Stores value for future use.
    TBool notificationsSavedTmp = iNotificationsSaved;

    TInt err = KErrNone;
    if ( !iIdleStateActive )
        {
        TRAP( err, LoadAndQueueSoftNotesL() ); // leaves if file does not exist.
        }
    else if ( type != ESetIdleState && type != EShowActiveNotifications ) 
        {
        // To make sure that changes will be saved even we didn't load them.
        iNotificationsSaved = EFalse; 
        }

    if ( err && err != KErrNotFound && err != KErrNoMemory ) 
        {
        // There was an error, check allowed error codes, others mean corruption of data.
        CEikonEnv::Static()->FsSession().Delete( KAknSNFilename );
        iNotificationsSaved = EFalse;
        }

#ifdef _DEBUG
    _LIT(KDmsg, "AknSoftNotificationPlugin, HandleNotifierMessageL:type %d,count %d, Load returned %d");
    RDebug::Print(KDmsg,type,count,err);
#endif

    if ( type == EShowActiveNotifications )
        {
        return;
        }

    if ( type == ESetIdleState )
        {
        if ( count )
            {
            iGlobalNoteController->SetMaxDisplayPriorityL( KMaxTInt );
            iIdleStateActive = ETrue;
            }
        else
            {
            iGlobalNoteController->SetMaxDisplayPriorityL( KMinimumSoftNotePriority );
            iIdleStateActive = EFalse;
            }
        return;
        }

    TChar isCancel = readStream.ReadUint8L();
    TChar addCount = readStream.ReadUint8L();

    // using hbuf allows us to use dynamic sized buffers, client should send the info...
    HBufC* noteTextH = HBufC::NewLC( KGlobalNoteTextLength );
    TPtr noteText = noteTextH->Des();
    
    readStream >> noteText;

    if ( count == 0 && !addCount )
        {
        isCancel = 1; // true
        }
    else if ( count < 0 )
        {
        count = 1;
        }

    if ( type == ECustomSoftNotification )
        {
        TInt customNoteID = readStream.ReadInt32L();

        CCustomNotifParams* params = SeekCustomNoteForId( customNoteID );
        TInt noteId = ( params==0 ) ? KErrNotFound : params->iNoteId;

        if ( isCancel )
            {
            if ( !params ) 
                {
                // No note for id, no need to do anything but restore the iNotificationsSaved value.
                CleanupStack::PopAndDestroy( noteTextH );
                iNotificationsSaved = notificationsSavedTmp;
                return;
                }

            if ( noteId == 0 ) // was displayed in grouped form
                {
                RemoveCustomNoteForId( customNoteID );
                
                if (!IsGroupedFormed())
                    {
                    // ScheduleGroupedNotifierL does not remove EShowGroupedNotification item
                    // so let's do it here.
                    RemoveByType(EShowGroupedNotification);
                    }                
                
                ScheduleGroupedNotifierL();
                SaveSoftNotificationsL();
                
                // If grouped note was visible and only one groupable soft note was left,
                // then iSoftNoteEntryList and iCustomNoteParamsStack states are not exactly 
                // correct. Load restores this state.
                TRAP_IGNORE(LoadAndQueueSoftNotesL());
                }
            else
                {
                RemoveCustomNoteForId( noteId, ETrue );
                if ( noteId != KErrNotFound ) // was added to global notes queue
                    {
                    iGlobalNoteController->TryDisplayNextNoteL();
                    }
                    
                SaveSoftNotificationsL();           
                }
            
            CleanupStack::PopAndDestroy( noteTextH );
            return;
            }

        if ( params ) // Remove old
            {
            count += ( addCount ? params->iCount : 0 );
            TBool isNotGrouped = noteId != 0;
            RemoveCustomNoteForId( isNotGrouped ? noteId : customNoteID, isNotGrouped );
            }

        TBool newNote = ( params == NULL );
        AddNewCustomNoteL( readStream, count, newNote );

        if( iCustomNoteParamsStack && 
            iCustomNoteParamsStack->iParamType == KAknSoftNotificationDynamic )
            {
            aNoteId = iCustomNoteParamsStack->iId; // generated id
            TPtrC customTxt( iCustomNoteParamsStack->CustomText( count, EFalse ) );
            if( customTxt.Length() > 0 )
                {
                noteText.Copy( customTxt.Left( KGlobalNoteTextLength ) );
                }
            }
        }

    if ( !isCancel )
        {
#ifdef __COVER_DISPLAY
        // Play tone for select network notification immediately if device has cover display.
        if ((type == ESelectNetworkNotification) && count && !iSoftNotificationAmounts[type])
            {
            ((CAknCapAppServerAppUi*)(CEikonEnv::Static())->EikAppUi())->KeySounds()->
                PlaySound(CAknNoteDialog::EErrorTone);
            }
#endif // __COVER_DISPLAY            

        TBool countChanged = ETrue;
        
        if ( addCount )
            {
            iSoftNotificationAmounts[type] += count;
            }
        else
            {
            if ( iSoftNotificationAmounts[type] == count )
                {
                // If the amount is not changed, set up a flag for
                // not updating the note.
                countChanged = EFalse;
                }
            iSoftNotificationAmounts[type] = count;
            }
            
        UpdateNoteL(type, noteText, iSoftNotificationAmounts[type], countChanged);
        CleanupStack::PopAndDestroy( noteTextH );

        User::ResetInactivityTime();
        }
    else // Cancel note by type
        {
        CleanupStack::PopAndDestroy( noteTextH );

        if (iSoftNotificationAmounts[type] == 0)
            {
            // There is not this type of soft notifications on queue
            // Just restore the iNotificationsSaved value and return.
            iNotificationsSaved = notificationsSavedTmp;
            return;
            }
            
        iSoftNotificationAmounts[type] = 0;
        RemoveByType(type);
        
        if (type == EMissedCallsNotification ||
            type == ENewMessagesNotification ||
            type == ENewMailNotification ||
            type == EChatMessageNotification)
            {
            RemoveByType(EShowGroupedNotification);
            ScheduleGroupedNotifierL();
            }
        else
            {
            iGlobalNoteController->TryDisplayNextNoteL();
            }
        }

    SaveSoftNotificationsL();
    }

// ---------------------------------------------------------
// CAknSoftNotificationSubject::GroupedNoteCompletedL(TInt aCommandId,TAknGroupedNotifierItem aSelectedItem)
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknSoftNotificationSubject::GroupedNoteCompletedL(TInt aCommandId,TAknGroupedNotifierItem aSelectedItem)
    {
    if ( iGroupedNote )
        {
        //No delete is necessary as the dialog will take care of deleting itself
        iGroupedNote->RemoveEditorIndicator();
        iGroupedNote = NULL;
        }

    if ( aCommandId == EEikBidTab ) // Apps or end-key pressed
        {
        SaveSoftNotificationsL();
        ClearAllNotes();
        return;
        }

    if ( aCommandId == EAknSoftkeyExit )
        {
        SetNcnFlag(EFalse);
        }

    // Make sure goruped notification is removed from queue
    RemoveByType(EShowGroupedNotification);

    if (aSelectedItem > EMaxItem || aSelectedItem < 0 ) // out of "static" range
        {
        CCustomNotifParams* params = SeekCustomNoteForId(aSelectedItem);
        if (params)
            {
            HandleCustomNoteCompletedL(params, aCommandId);
            }
        RemoveCustomNoteForId(aSelectedItem);
        
        // To allow this to fall through next clause (saving, rescheduling etc.).
        aCommandId = EAknSoftkeyOk; 
        }

    if (aCommandId == EAknSoftkeyShow  || aCommandId == EAknSoftkeyOk)
        {
        if (aSelectedItem == EMissedCalls)
            {
            iSoftNotificationAmounts[EMissedCallsNotification] = 0;
            LaunchMissedCallsAppL();
            }
        else if (aSelectedItem == ENewMessages)
            {
            iSoftNotificationAmounts[ENewMessagesNotification] = 0;
            LaunchNewMessagesAppL();
            }
        else if (aSelectedItem == ENewChatMsgs)
            {
            iSoftNotificationAmounts[EChatMessageNotification] = 0;
            LaunchNewIMAppL();
            }
        else if (aSelectedItem == ENewMails)
            {
            iSoftNotificationAmounts[ENewMailNotification] = 0;
            LaunchNewMailAppL();
            }

        ScheduleGroupedNotifierL();
        iNotificationsSaved = EFalse;

    }
    else if (aCommandId == EAknSoftkeyExit || aCommandId == KErrCancel)
        {
        if ( aCommandId == EAknSoftkeyExit )
            {
            iSoftNotificationAmounts[EMissedCallsNotification] = 0;
            iSoftNotificationAmounts[ENewMessagesNotification] = 0;
            iSoftNotificationAmounts[EChatMessageNotification] = 0;
            iSoftNotificationAmounts[ENewMailNotification] = 0;

            // Null Customs
            CCustomNotifParams* params = iCustomNoteParamsStack;
            while(params)
                {
                CCustomNotifParams* tmp = params->iNext;
                if (params->iSupportsGroupedform)
                    {
                    if( params->iParamType == KAknSoftNotificationDynamic )
                        {
                        if (params->EnableObserver())
                            {
                            // notify user event
                            iDynamicSoftNoteManager->IssueEvent(
                                params->iId, EAknDynamicSNoteEventCanceled, ETrue);    
                            }
                        }
                    RemoveCustomNoteForId(params->iId);
                    }
                params = tmp;
                }

            RemoveByType(EShowGroupedNotification); // Remove also from global notes queue
            iNotificationsSaved = EFalse;
            }
        iGlobalNoteController->TryDisplayNextNoteL();
        }
    SaveSoftNotificationsL();
    }


// ---------------------------------------------------------
// CAknSoftNotificationSubject::UpdateNoteL(TSoftNotifierType aType)
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknSoftNotificationSubject::UpdateNoteL(
    TAknSoftNotificationType aType,const TDesC& aText, TInt aCount, TBool aCountChanged)
    {
    iLatestType = aType;

    if ((aType > ENoSoftNotification && aType < EMissedCallsNotification)
        || aType == ECustomSoftNotification)
        {
        // Received an ungrouped soft notification
        DisplayUngroupedNotifierL(aType, aText, aCount);
        }
    else if ((aType >= EMissedCallsNotification && aType <= ENewMailNotification)
        || aType == EChatMessageNotification)
        {
        // Set shared data flag if this is missed calls notification.
        // This is needed for synchronizing notes with screensaver
        // indicator view.
        if (aType == EMissedCallsNotification && aCount > 0)
            {
            SetNcnFlag( ETrue );
            }
            
        // Update grouped notifier only if the count has actually changed.
        // This removes flicker in some cases.
        if ( aCountChanged )
            {
            ScheduleGroupedNotifierL();
            }
        }
    }


void CAknSoftNotificationSubject::ScheduleGroupedNotifierL()
    {
    // Possible grouped notification
    TBool grouped = IsGroupedFormed();
    if (grouped)
        {
        if (iGroupedNote)
            {
            // grouped note already exists, so just update it
            ShowGroupedNotificationL();
            }
        else
            {
            // Schedule grouped note
            RemoveByType(EShowGroupedNotification);
            RemoveByType(EMissedCallsNotification);
            RemoveByType(ENewMessagesNotification);
            RemoveByType(EChatMessageNotification);
            RemoveByType(ENewMailNotification);

            CCustomNotifParams* params = iCustomNoteParamsStack;
            for (;params;params = params->iNext)
                {
                if( params->iSupportsGroupedform )
                    {
                    if ( params->iNoteId != KErrNotFound && params->iNoteId != 0)
                        {
                        iGlobalNoteController->CancelNote(params->iNoteId, EFalse);
                        for (TInt ii = 0; ii < iSoftNoteEntryList->Count(); ii++)
                            {
                            if (params->iNoteId == iSoftNoteEntryList->At(ii).iId )
                                {
                                iSoftNoteEntryList->At(ii).iId = 0;
                                iSoftNoteEntryList->At(ii).iCustomId = params->iId;
                                break;
                                }
                            }
                        }

                    params->iNoteId = 0;
                    }
                }

            // Create grouped notification
            TSoftNoteEntry softNote;
            softNote.iType = EShowGroupedNotification;
            softNote.iId = iGlobalNoteController->AddSoftNotificationL(KNullDesC, 0, 0,
                KGroupedNotification, 0);
            iGlobalNoteController->TryDisplayNextNoteL();
            iSoftNoteEntryList->AppendL(softNote);
            }
        }
    else
        {
        if (iGroupedNote)
            {
            delete iGroupedNote;
            iGroupedNote = NULL;
            }
        // Display using ungrouped layout
        if (iSoftNotificationAmounts[EMissedCallsNotification])
            {
            DisplayUngroupedNotifierL(EMissedCallsNotification, KNullDesC, 
                iSoftNotificationAmounts[EMissedCallsNotification]);
            }
        if (iSoftNotificationAmounts[ENewMessagesNotification])
            {
            DisplayUngroupedNotifierL(ENewMessagesNotification, KNullDesC, 
                iSoftNotificationAmounts[ENewMessagesNotification]);
            }
        if (iSoftNotificationAmounts[EChatMessageNotification])
            {
            DisplayUngroupedNotifierL(EChatMessageNotification, KNullDesC, 
                iSoftNotificationAmounts[EChatMessageNotification]);
            }
        if (iSoftNotificationAmounts[ENewMailNotification])
            {
            DisplayUngroupedNotifierL(ENewMailNotification, KNullDesC, 
                iSoftNotificationAmounts[ENewMailNotification]);
            }
        }
    }



void CAknSoftNotificationSubject::DisplayUngroupedNotifierL(TAknSoftNotificationType aType, 
    const TDesC& aText, TInt aCount)
    {
    TInt resource = 0;
    TInt priority = 0;
    TBool cancel = EFalse;
    TInt count = 0;
    TInt softkeys = 0;
    TInt tone = 0; // ENoTone;
    switch (aType)
        {
        case ENetworkInformationNotification:
            resource = R_NETWORK_INFORMATION_NOTE;
            softkeys = R_AVKON_SOFTKEYS_OK_EMPTY__OK;
            priority = KNetworkInfoPriority;
            break;
        case ESelectNetworkNotification:
            resource = R_SELECT_NETWORK_NOTE;
            softkeys = R_AVKON_SOFTKEYS_OK_CANCEL__OK;
            priority = KSelectNetworkPriority;
#ifndef __COVER_DISPLAY            
            tone = CAknNoteDialog::EErrorTone;
#endif // __COVER_DISPLAY            
            if ( CheckIfAlreadyExists(ESelectNetworkNotification) )
                {
                return;
                }
            break;
        case EUnstructuredSSDataNotification:
            resource = R_UNSTRUCTURED_SS_DATA_NOTE;
            softkeys = R_AVKON_SOFTKEYS_READ_EXIT__READ;
            priority = KUSSDPriority;
            break;
        case EVoiceMailNotification:
            resource = R_VOICE_MAIL_NOTE;
            softkeys = R_AVKON_SOFTKEYS_LISTEN_EXIT__LISTEN;
            priority = KVoiceMailPriority;
            cancel = ETrue;
            break;
        case ESeparateVoiceMailOnLine2Notification:
            resource = R_VOICE_MAIL_ON_LINE2_NOTE;
            softkeys = R_AVKON_SOFTKEYS_LISTEN_EXIT__LISTEN;
            priority = KVoiceMailOnLinePriority;
            cancel = ETrue;
            break;
        case ESeparateVoiceMailOnLine1Notification:
            resource = R_VOICE_MAIL_ON_LINE1_NOTE;
            softkeys = R_AVKON_SOFTKEYS_LISTEN_EXIT__LISTEN;
            priority = KVoiceMailOnLinePriority;
            cancel = ETrue;
            break;
        case ECellBroadcastNotification:
            resource = R_CELL_BROADCAST_NOTE;
            softkeys = R_AVKON_SOFTKEYS_READ_EXIT__READ;
            priority = KCBSPriority;
            cancel = ETrue;
            break;
        case EMissedCallsNotification:
            resource = R_MISSED_CALLS_NOTE;
            softkeys = R_AVKON_SOFTKEYS_SHOW_EXIT__SHOW;
            priority = KMissedCallsPriority;
            cancel = ETrue;
            SetNcnFlag(ETrue);
            break;
        case ENewMessagesNotification:
            resource = R_NEW_MESSAGES_NOTE;
            softkeys = R_AVKON_SOFTKEYS_SHOW_EXIT__SHOW;
            priority = KNewMessagesPriority;
            cancel = ETrue;
            break;
        case ENewMailNotification:
            resource = R_NEW_MAIL_NOTE;
            softkeys = R_AVKON_SOFTKEYS_SHOW_EXIT__SHOW;
            priority = KNewEmailPriority;
            cancel = ETrue;
            break;
        case EChatMessageNotification:
            resource = R_NEW_CHAT_MESSAGES_NOTE;
            softkeys = R_AVKON_SOFTKEYS_SHOW_EXIT__SHOW;
            priority = KChatMessagePriority;
            cancel = ETrue;
            break;
        case ECustomSoftNotification:
            {
            resource = iCustomNoteParamsStack->iId;
            softkeys = iCustomNoteParamsStack->iParamData->iSoftkeys;
            priority = iCustomNoteParamsStack->iParamData->iPriority;
            tone = iCustomNoteParamsStack->iParamData->iTone;
            cancel = EFalse;
            count = iCustomNoteParamsStack->iCount;
            break;
            }
        default:
            break;
        };

    if (cancel)
        {
        // Remove duplicate notes
        RemoveByType(aType);
        count = aCount;
        }

    TSoftNoteEntry softNote;
    softNote.iType = aType;
    softNote.iCount = count;

#ifdef _DEBUG
    _LIT(KDmsg, "AknSoftNotificationPlugin, Adding ungrouped:type %d,count %d ");
    RDebug::Print(KDmsg,aType, count);
#endif

    if ( aType == ECustomSoftNotification )
        {
        if( iCustomNoteParamsStack->iParamType == KAknSoftNotificationCustom )
            {
            TFileName resourceFile;
            CEikonEnv* environment = CEikonEnv::Static();
            resourceFile.Append(iCustomNoteParamsStack->iParamData->iResourceFile->Des());
            BaflUtils::NearestLanguageFile(environment->FsSession(),resourceFile);
    
            TRAPD( err, iCustomNoteParamsStack->iCoeResourceHandle =
                environment->AddResourceFileL(resourceFile));
    
            if ( err )
                { // couldn't load note resource, remove note from queue
#ifdef _DEBUG
                _LIT(KDmsg2,"AknSoftNotificationPlugin,Resource loading failed: %s");
                RDebug::Print(KDmsg2,&resourceFile);
#endif
                RemoveCustomNoteForId(resource);
                return;
                }
            }

        if (iCustomNoteParamsStack->iSupportsGroupedform && IsGroupedFormed())
            { // don't add to global notes queue
            softNote.iId = 0; // grouped, not in global notes queue
            softNote.iCustomId = iCustomNoteParamsStack->iId;
            iSoftNoteEntryList->AppendL(softNote);
            ScheduleGroupedNotifierL();
            return;
            }
        }

    if( aType == ECustomSoftNotification &&
        iCustomNoteParamsStack->iParamType == KAknSoftNotificationDynamic )
        {
        if( iCustomNoteParamsStack->iDynamicData )
            {
            CAknDynamicNotificationData* data = 
                iCustomNoteParamsStack->iDynamicData;
            softNote.iId = iGlobalNoteController->AddSoftNotificationL(
                aText,
                count,
                data->Priority(),
                data->Tone(),
                data->LeftSoftkey(),
                data->RightSoftkey(),
                data->ImageData() );
            }
        }
    else
        {
        softNote.iId = iGlobalNoteController->AddSoftNotificationL(aText, resource, count, priority, 
            softkeys, tone );
        }
        
    if ( aType == ECustomSoftNotification )
        {
        CAknSDData* sdData = iCustomNoteParamsStack->iParamData->iSecondaryDisplayData;
        
        if ( sdData )
            {
            CAknSDData* cloneSDData = NULL;
            cloneSDData = CAknSDData::NewL( sdData->iCategory, sdData->iDialogIdx, *(sdData->iAdditionalData) );
            CleanupStack::PushL( cloneSDData );
            
            TBool sdDataSet = iGlobalNoteController->SetSDData( softNote.iId, cloneSDData );
            
            if ( sdDataSet )
                {
                CleanupStack::Pop( cloneSDData );
                }          
            else // cloneSDData ownership not transferred
            	{
            	CleanupStack::PopAndDestroy( cloneSDData );
            	}
            }
            
        iCustomNoteParamsStack->iNoteId = softNote.iId;
        }

    iGlobalNoteController->TryDisplayNextNoteL();
    iSoftNoteEntryList->AppendL(softNote);

#ifdef _DEBUG
    _LIT(KDmsg3,"AknSoftNotificationPlugin, Added SoftNote:type %d,NoteId %d ");
    RDebug::Print(KDmsg3,aType, softNote.iId);
#endif
    }


void CAknSoftNotificationSubject::RemoveByType(TAknSoftNotificationType aType, TInt aId)
    {
    TInt count = iSoftNoteEntryList->Count();
    for (TInt ii=count-1; ii>=0; ii--)
        {
        TSoftNoteEntry& entry = (*iSoftNoteEntryList)[ii];

        if ( ( aType != ECustomSoftNotification && entry.iType == aType)
            || ( aId != 0 && entry.iType == ECustomSoftNotification && entry.iId == aId) )
            {
            iGlobalNoteController->CancelNote(entry.iId, EFalse);
            iSoftNoteEntryList->Delete(ii);
            }
        }
    }

void CAknSoftNotificationSubject::ClearAllNotes()
    {
#ifdef _DEBUG
    _LIT(KDmsg, "AknSoftNotificationPlugin,ClearAllNotes");
    RDebug::Print(KDmsg);
#endif

    while ( iSoftNoteEntryList->Count())
        {
        TSoftNoteEntry& entry = (*iSoftNoteEntryList)[0];
        if (entry.iId != 0)
            {
            iGlobalNoteController->CancelNote(entry.iId, EFalse);
            }
        iSoftNotificationAmounts[entry.iType] = 0;
        iSoftNoteEntryList->Delete(0);
        }

    CCustomNotifParams* params = iCustomNoteParamsStack;
    while ( params )
        {
        CCustomNotifParams* tmp = params;
        params = params->iNext;
        delete tmp;
        }
    iCustomNoteParamsStack = 0;
    }

// Used only with ungrouped notes
TAknSoftNotificationType CAknSoftNotificationSubject::TypeFromId(TInt aId)
    {
    TInt count = iSoftNoteEntryList->Count();
    for (TInt ii = count - 1; ii >= 0; ii--)
        {
        TSoftNoteEntry& entry = (*iSoftNoteEntryList)[ii];
        if (entry.iId == aId)
            {
            return entry.iType;
            }
        }
    return ENoSoftNotification;
    }

// Used only with ungrouped notes
void CAknSoftNotificationSubject::CompleteId(TInt aId)
    {
    TInt count = iSoftNoteEntryList->Count();
    for (TInt ii=count-1; ii>=0; ii--)
        {
        TSoftNoteEntry& entry = (*iSoftNoteEntryList)[ii];
        if (entry.iId == aId)
            {
            // Set notification count to zero
            iSoftNotificationAmounts[entry.iType] = 0;
            iSoftNoteEntryList->Delete(ii);
            RemoveCustomNoteForId(aId,ETrue);
            iNotificationsSaved = EFalse;
            return;
            }
        }
    return;
    }

void CAknSoftNotificationSubject::SoftNoteCompleted(TInt aId, TInt aCommand)
    {
    TRAPD(err, DoSoftNoteCompletedL(aId, aCommand));
    if (err)
        {
        CEikonEnv::Static()->HandleError(err);
        }
    }

void CAknSoftNotificationSubject::DoSoftNoteCompletedL(TInt aId, TInt aCommand)
    {
    TAknSoftNotificationType type = TypeFromId( aId );

#ifdef _DEBUG
    _LIT(KDmsg, "AknSoftNotificationPlugin,DoSoftNoteCompletedL:type %d,NoteId %d, command %d ");
    RDebug::Print(KDmsg,type, aId, aCommand);
#endif

    if ( aCommand == EAknSoftkeyExit )
        {
        if ( type == EMissedCallsNotification )
            {
            SetNcnFlag(EFalse);
            }
        if( type == ECustomSoftNotification )
            {
            CCustomNotifParams* params = SeekCustomNoteForId( aId, ETrue );
            if( params )
                {
                HandleCustomNoteCanceledL( params, aCommand );
                }            
            }
        CompleteId(aId);
        SaveSoftNotificationsL();
        return;
        }

    switch (type)
        {
        case ESelectNetworkNotification:
            if (aCommand == EAknSoftkeyOk)
                {
                LaunchSelectNetworkAppL();
                CompleteId(aId);
                }
            break;
        case EUnstructuredSSDataNotification:
            if (aCommand == EAknSoftkeyRead || aCommand == EAknSoftkeyOk)
                {
                LaunchUSSDAppL();
                CompleteId(aId);
                }
            break;
        case EVoiceMailNotification:
        case ESeparateVoiceMailOnLine1Notification:
        case ESeparateVoiceMailOnLine2Notification:
            if (aCommand == EAknSoftkeyListen || aCommand == EAknSoftkeyOk)
                {
                LaunchNewVoiceMailAppL(type);
                CompleteId(aId);
                }
            break;
        case ECellBroadcastNotification:
            if (aCommand == EAknSoftkeyRead || aCommand == EAknSoftkeyOk)
                {
                LaunchNewCbsAppL();
                CompleteId(aId);
                }
            break;
        case EMissedCallsNotification:
            if (aCommand == EAknSoftkeyShow || aCommand == EAknSoftkeyOk)
                {
                LaunchMissedCallsAppL();
                CompleteId(aId);
                }
            break;
        case ENewMessagesNotification:
            if (aCommand == EAknSoftkeyShow || aCommand == EAknSoftkeyOk)
                {
                LaunchNewMessagesAppL();
                CompleteId(aId);
                }
            break;
        case ENewMailNotification:
            if (aCommand == EAknSoftkeyShow || aCommand == EAknSoftkeyOk)
                {
                LaunchNewMailAppL();
                CompleteId(aId);
                }
            break;
        case EChatMessageNotification:
            if (aCommand == EAknSoftkeyShow || aCommand == EAknSoftkeyOk)
                {
                LaunchNewIMAppL();
                CompleteId(aId);
                }
            break;
        case ECustomSoftNotification:
            {
            CCustomNotifParams* params = SeekCustomNoteForId(aId, ETrue);
            if (params)
                {
                HandleCustomNoteCompletedL(params, aCommand);
                CompleteId(aId);
                }
            }
            break;
        default:
            // Note type something else, this should not be the case.
            // Remove note from queue anyway.
            CompleteId( aId );
            break;
        }
    SaveSoftNotificationsL();
    }


void CAknSoftNotificationSubject::HandleCustomNoteCompletedL(CCustomNotifParams* aParams, 
    TInt aCommand)
    {
    if (aParams->iHasViewInfo)
        {
        if ( aCommand == EAknSoftkeyOk ||
             aParams->iParamData->iAcceptSoftKey == aCommand )
            {
            LaunchViewL( 
                ((aParams->iParamData->iPluralViewId != KNullViewId && aParams->iCount > 1)?
                    aParams->iParamData->iPluralViewId:
                    aParams->iParamData->iViewId),

                aParams->iParamData->iCustomMessageId,
                aParams->ViewActivationMessage() );
            }
        }
    
    // notify user event
    if( aParams->iParamType == KAknSoftNotificationDynamic )
        {
        if( aParams->EnableObserver() )
            {
            iDynamicSoftNoteManager->IssueEvent( 
                aParams->iId, EAknDynamicSNoteEventAccepted, ETrue );
            }        
        }
    }

void CAknSoftNotificationSubject::HandleCustomNoteCanceledL( 
    CCustomNotifParams* aParams, TInt /*aCommand*/ )
    {
    // notify user event
    if( aParams->iParamType == KAknSoftNotificationDynamic )
        {
        if( aParams->EnableObserver() )
            {
            iDynamicSoftNoteManager->IssueEvent( 
                aParams->iId, EAknDynamicSNoteEventCanceled, ETrue );
            }         
        }
    }

//
// Sets shared data flag to indicate that NCN is active.
// This implementation sets this only for missed calls note.
//
void CAknSoftNotificationSubject::SetNcnFlag(TBool aValue)
    {
    CRepository* repository = NULL;
    TRAPD(ret, repository = CRepository::NewL(KCRUidAvkon));
    if (ret == KErrNone)
        {
        ret = repository->Set(KAknNewContactsNoteActive, aValue);
        }
    delete repository;
    }


// Handler function for ncn flag shared data state change.
TInt CAknSoftNotificationSubject::HandleNcnFlagStateChange(TAny* /* aPtr */)
    {
    return KErrNone;
    }

TBool CAknSoftNotificationSubject::ShowSoftNoteL(TInt aPriority, const TDesC& /*aText*/)
    {
    if (aPriority == KGroupedNotification)
        {
        ShowGroupedNotificationL();
        return ETrue;
        }
    return EFalse;
    }

TBool CAknSoftNotificationSubject::CancelSoftNote(TInt aPriority)
    {
    if (aPriority == KGroupedNotification)
        {
        if (iGroupedNote)
            {
            iGroupedNote->RemoveEditorIndicator();
            delete iGroupedNote;
            iGroupedNote = NULL;
            }
        return ETrue;
        }
    return EFalse;
    }

// ---------------------------------------------------------
// CAknSoftNotificationSubject::ShowGroupedNotificationL()
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknSoftNotificationSubject::ShowGroupedNotificationL()
    {
    if ( iGroupedNote )
        {
        iGroupedNote->RemoveEditorIndicator();
        }

    CAknGroupedNotifierNote* note = new (ELeave) CAknGroupedNotifierNote();
    CleanupStack::PushL( note );
    note->ConstructL( this );

    note->SetItemAmountL(
        EMissedCalls, 
        iSoftNotificationAmounts[EMissedCallsNotification], 
        iLatestType == EMissedCallsNotification);
        
    note->SetItemAmountL(
        ENewMessages, 
        iSoftNotificationAmounts[ENewMessagesNotification], 
        iLatestType == ENewMessagesNotification);
        
    note->SetItemAmountL(
        ENewChatMsgs, 
        iSoftNotificationAmounts[EChatMessageNotification], 
        iLatestType == EChatMessageNotification);
        
    note->SetItemAmountL(
        ENewMails, 
        iSoftNotificationAmounts[ENewMailNotification], 
        iLatestType == ENewMailNotification);
        
    CleanupStack::Pop( note );

    note->ExecuteLD( R_GROUPED_SOFT_NOTIFICATION );

    delete iGroupedNote;
    iGroupedNote = note;
    if ( iKeysLocked && note )
        {
        iGroupedNote->ListBox()->View()->ItemDrawer()->SetFlags(
            CListItemDrawer::EDisableHighlight );
        }
    }

// ---------------------------------------------------------
// CAknSoftNotificationSubject::MessageNotifierShown()
// ---------------------------------------------------------
//
TBool CAknSoftNotificationSubject::MessageNotifierShown()
    {
    TBool messageNotifierActive( EFalse );

    for ( TInt ii = 0; ii <= ECustomSoftNotification; ii++)
        {
        // Check that one of the message notifiers is first in the 
        // priority order (visible). 
        if (iSoftNotificationAmounts[ii] > 0)
            {
            if (ii == EMissedCallsNotification && IsGroupedFormed())
                {
                continue;
                }
            if ( ii == ENewMessagesNotification ||
                 ii == ENewMailNotification ||
                 ii == ECustomSoftNotification ) // Email uses custom soft note.
                {
                messageNotifierActive = ETrue;
                }
            break;                
            }
        }

    return messageNotifierActive;
    }

// ---------------------------------------------------------
// CAknSoftNotificationSubject::ButtonGroupContainer()
// ---------------------------------------------------------
//
CEikButtonGroupContainer* CAknSoftNotificationSubject::ButtonGroupContainer()
    {
    CEikButtonGroupContainer* container = NULL;
    if ( iGroupedNote ) 
        {
        container = &iGroupedNote->ButtonGroupContainer();
        }
    return container;
    }
        
// ---------------------------------------------------------
// CAknSoftNotificationSubject::IsGroupedFormed()
// (other items were commented in a header).
// ---------------------------------------------------------
//
TBool CAknSoftNotificationSubject::IsGroupedFormed()
    {
    TInt foundTypes = 0;
    if (iSoftNotificationAmounts[EMissedCallsNotification])
        {
        foundTypes++;
        }
    if (iSoftNotificationAmounts[ENewMessagesNotification])
        {
        foundTypes++;
        }
    if (iSoftNotificationAmounts[EChatMessageNotification])
        {
        foundTypes++;
        }
    if (iSoftNotificationAmounts[ENewMailNotification])
        {
        foundTypes++;
        }
        
    // check custom notes which support grouped form
    CCustomNotifParams* params = iCustomNoteParamsStack;
    for (;params;params = params->iNext)
        {
        if(params->iSupportsGroupedform)
            {
            foundTypes++;
            }
        }

    if (foundTypes > 1)
        {
        return ETrue;
        }
    else
        {
        return EFalse;
        }
    }

// ------------------------------------
// From MAknGroupedNotifierNoteObserver
// Add items to grouped form
// ------------------------------------
void CAknSoftNotificationSubject::AddItemsL( CDesCArray& aTexts, CArrayFix<TInt>& aOrder )
    {
    // check custom notes which support grouped form
    CCustomNotifParams* params = iCustomNoteParamsStack;
    for (;params;params = params->iNext)
        {
        if(params->iSupportsGroupedform)
            {
            if( params->iParamType == KAknSoftNotificationDynamic )
                {
                if( params->iCount > 1 )
                    {
                    // plural text needs to be formatted
                    TPtrC text( params->CustomText( params->iCount, ETrue ) );
                    const TInt formatSpace = 11; // space needed for 'count'
                    HBufC* buf = HBufC::NewLC( text.Length() + formatSpace );
                    buf->Des().Format( text, params->iCount );
                    
                    aTexts.AppendL( *buf );
                    aOrder.AppendL( params->iId );
                    
                    CleanupStack::PopAndDestroy( buf );
                    }
                else
                    {
                    // append singular text
                    aTexts.AppendL( params->CustomText( params->iCount, ETrue ) );
                    aOrder.AppendL( params->iId );
                    }
                }
            else
                {
                // Load text
                CCoeEnv* coe = CCoeEnv::Static();
                TResourceReader reader;
                HBufC* buf = 0;
    
                // Resources are loaded in DisplayUngroupedNotifierL()
                coe->CreateResourceReaderLC(reader, params->iParamData->iGroupedTextResourceId);
                TInt stringResource = reader.ReadInt32();
    
                // Handle Singular / plural + possible plural string w/o number tag
                if (params->iCount == 1)
                    {
                    buf = coe->AllocReadResourceLC(stringResource);
                    }
                else 
                    {
                    stringResource = reader.ReadInt32();
                    buf = coe->AllocReadResourceLC(stringResource);
                    _LIT(KNumberId, "%N");
                    if (buf->Find(KNumberId) != KErrNotFound)
                        {
                        CleanupStack::PopAndDestroy();
                        buf = 0;
                        buf = StringLoader::LoadLC(stringResource,params->iCount);
                        }
                    }
 
                // Add Text
                aTexts.AppendL(buf->Des());
                // add order
                aOrder.AppendL(params->iId);
                
                CleanupStack::PopAndDestroy( 2 ); // buf and reader
                }
            

            }
        }
    }
    
// --------------------------------------------------
// CAknSoftNotificationSubject::SoftkeysForCustomItem
// (other items were commented in a header).
// --------------------------------------------------
void CAknSoftNotificationSubject::SoftkeysForCustomItem(TAknGroupedNotifierItem aCustomItem,
    TInt& aSoftkeyResourceId, TInt& aAcceptKeyId,
    TDes& aLeftSoftkey,
    TDes& aRightSoftkey )
    {
    CCustomNotifParams* params = SeekCustomNoteForId(aCustomItem, EFalse);
    if( params )
        {
        if( params->iParamType == KAknSoftNotificationCustom && 
            params->iParamData )
            {
            aSoftkeyResourceId = params->iParamData->iSoftkeys;
            aAcceptKeyId       = params->iParamData->iAcceptSoftKey;
            }
        
        if( params->iParamType == KAknSoftNotificationDynamic && 
            params->iDynamicData )
            {
            TPtrC sk( params->iDynamicData->LeftSoftkey() );
            if( sk.Length() > 0 )
                {
                aLeftSoftkey.Copy( sk.Left( aLeftSoftkey.MaxLength() ) );
                }
            
            sk.Set( params->iDynamicData->RightSoftkey() );
            if( sk.Length() > 0 )
                {
                aRightSoftkey.Copy( sk.Left( aRightSoftkey.MaxLength() ) );
                }
            
            }
        }
    }

// ---------------------------------------------------------
// CAknSoftNotificationSubject::LaunchMissedCallsAppL()
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknSoftNotificationSubject::LaunchMissedCallsAppL()
    {
    TPtrC8 msg(KLogsActivationMsg);                
    
    TApaTaskList taskList( CCoeEnv::Static()->WsSession() );
    TApaTask task = taskList.FindApp( KUidLogs );

    // close fsw in case it is active.
    // this is needed because LaunchMissedCallsAppL doesn't call 
    // method LaunchViewL, which does the same
    ((CAknCapAppServerAppUi*)(CEikonEnv::Static())->EikAppUi())->
        HandleResourceChangeL(KAknInternalFSWClose); // won't leave
    
    TInt err = KErrNone;
    
    if( task.Exists() ) //Logs already open. Request it to
        {               //activate the correct view
        task.SendMessage( KUidLogs, msg ); // the uid has no meaning so just re-use existing 

     // preventing from the flicker of log view, the view will activte ieself when receiving a message.   
     // task.BringToForeground();
        }
    else                //Start Logs and request it to activate
        {               //the correct view
        TApaAppInfo appInfo;
        RApaLsSession lsSession;
        err = lsSession.Connect();
        
        if ( err == KErrNone )
            {
            CleanupClosePushL( lsSession );
            
            if( lsSession.GetAppInfo( appInfo, KUidLogs ) == KErrNone )
                {
                CApaCommandLine* cmdLine = CApaCommandLine::NewLC();
                cmdLine->SetExecutableNameL( appInfo.iFullName );
                cmdLine->SetCommandL( EApaCommandRun );
                cmdLine->SetTailEndL( msg );

                lsSession.StartApp( *cmdLine );
                CleanupStack::PopAndDestroy( cmdLine );
                }

            CleanupStack::PopAndDestroy();  // lsSession
            }
        else
            {
            User::LeaveIfError( err );
            }
        }
    
    if ( err == KErrNone )
        {
        // We'll assume that application was launched/activated succesfully
        SetNcnFlag(EFalse);
        }
    }

// ---------------------------------------------------------
// CAknSoftNotificationSubject::LaunchNewMessagesAppL()
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknSoftNotificationSubject::LaunchNewMessagesAppL()
    {        
    TInt viewtype = 0; // Default is traditional Inbox

    if ( iMessagingRepository )
        {
	// Read the messaging settings
        iMessagingRepository->Get(KMessagingAppDefaultViewCRKey,viewtype);
        }

    if ( viewtype == 1 ) // Launch conversations 
        {
        LaunchViewL( 
                KConversationApplicationViewUid,           
                TUid::Uid(KConversationListViewUid),         
                KNullDesC8() );
        }    
    else  // Launch traditional Inbox
        {
        LaunchViewL( 
            KMessagingCentreInboxView, 
            TUid::Uid(KMsvGlobalInBoxIndexEntryIdValue), 
            KNullDesC8() );
        }    
    }

// ---------------------------------------------------------
// CAknSoftNotificationSubject::LaunchNewMailAppL()
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknSoftNotificationSubject::LaunchNewMailAppL()
    {
    // reactivate MCE main view with arbitrary UID
    LaunchViewL( KMessagingCentreMainViewUid, TUid::Uid(1),KNullDesC8() );
    }

void CAknSoftNotificationSubject::LaunchNewCbsAppL()
    {
    if ( iSoftNotificationAmounts[ECellBroadcastNotification] == 1)
        {
        LaunchViewL( KCbsApplicationUidMessageView, TUid::Uid(1), KNullDesC8() );
        }
    else
        {
        LaunchViewL( KCbsApplicationUidTopicListView, TUid::Uid(1), KNullDesC8() );
        }
    }

void CAknSoftNotificationSubject::LaunchNewVoiceMailAppL(TInt aType)
    {
    TUid uid = {1}; // als line 1 or no als (TVmbxNumberEntry::EAlsLine1Entry)
    if ( aType == ESeparateVoiceMailOnLine2Notification )
        {
        uid.iUid = 2; // (TVmbxNumberEntry::EAlsLine2Entry)
        }

    LaunchViewL( KSpeeddialVmbxDialUidView, uid, KExternalLaunch );
    }

void CAknSoftNotificationSubject::LaunchSelectNetworkAppL()
    {
    LaunchViewL( KSelectNetworkAppUidView, TUid::Uid( KGSCustomActivateNetView ), KNullDesC8() );
    }

void CAknSoftNotificationSubject::LaunchUSSDAppL()
    {
    }

void CAknSoftNotificationSubject::LaunchViewL(const TVwsViewId& aViewId, TUid aCustomMessageId, 
    const TDesC8& aCustomMessage)
    {
    CCoeEnv::Static()->AppUi()->CreateActivateViewEventL(aViewId, aCustomMessageId, aCustomMessage);

    SaveSoftNotificationsL();
    
    // close fsw in case it is active.
    ((CAknCapAppServerAppUi*)(CEikonEnv::Static())->EikAppUi())->HandleResourceChangeL(
        KAknInternalFSWClose); // won't leave
   
    // We assume that view switching was successful, change idle state to false:
    delete iIdle;
    iIdle = 0;
    iIdle = CIdle::NewL(EPriorityLow);
    iIdle->Start(TCallBack(SetIdleStateFalse, this));
    }

TInt CAknSoftNotificationSubject::SetIdleStateFalse(TAny* aThis)
    {
    TRAPD( err, ((CAknSoftNotificationSubject*)aThis)->iGlobalNoteController->
        SetMaxDisplayPriorityL(KMinimumSoftNotePriority))
    if (!err)
        {
        ((CAknSoftNotificationSubject*)aThis)->iIdleStateActive = EFalse;
        ((CAknCapAppServerAppUi*)(CEikonEnv::Static())->EikAppUi())->SetIdleActive( EFalse );
        }
    return err;
    }

void CAknSoftNotificationSubject::SaveSoftNotificationsL()
    {
    // Save all soft notifications in case of power failure
    if ( iNotificationsSaved ) // notifications haven't been loaded since saved i.e. no changes
        {
        return;
        }

    TInt count = iSoftNoteEntryList->Count();
    RFs& fs = CEikonEnv::Static()->FsSession();
#ifdef __COVER_DISPLAY  
    iCoverClient->CancelCommand();
    iCoverClient->ResetBuffer();
#endif
    if (count == 0)
        {
        // Nothing to save, delete any existing file
        TInt err = fs.Delete(KAknSNFilename);
        iNotificationsSaved = EFalse;
#ifdef __COVER_DISPLAY  
        // if deleted for the first time, inform the cover ui,
        // otherwise the deletion returns KErrNotFound
        if ( err == KErrNone ) 
            {
            // inform the cover ui that there are no soft notifications
            iCoverClient->BufStream().WriteInt32L(count);
            iCoverClient->BufStream().CommitL();
            iCoverClient->IssueCommand();
            }
#endif        
        }
    else
        {
        // Create new file and save soft notifications
        RFileWriteStream file;
        TInt err = file.Replace(fs, KAknSNFilename, EFileWrite);
        // path may not yet exist in 3.0 (private directory).
        if (err == KErrPathNotFound)
            {
            User::LeaveIfError(fs.MkDirAll(KAknSNFilename));
            User::LeaveIfError(file.Create(fs, KAknSNFilename, EFileWrite));
            }

        CleanupClosePushL(file);
        file.WriteInt32L(count);

#ifdef __COVER_DISPLAY  
        TBool groupedExists = EFalse;
        iCoverClient->BufStream().WriteInt32L(count);
#endif

        // Save in reverse order so order of notifications with identical priority remains
        for (TInt ii = count - 1; ii >= 0; ii--)
            {
            TSoftNoteEntry& entry = (*iSoftNoteEntryList)[ii];
            SaveNoteL(file, entry);

#ifdef __COVER_DISPLAY
            if (entry.iType == EShowGroupedNotification)
                {
                groupedExists = ETrue;
                }
            
            iCoverClient->BufStream().WriteInt32L(entry.iType);
            iCoverClient->BufStream().WriteInt32L(entry.iCount);
#endif
            };

#ifdef __COVER_DISPLAY

        TUint8 customsWCoverDataCount( 0 );
        // we don't have actual count of custom params (nor ones with secondary display data..)
        for (CCustomNotifParams* params = iCustomNoteParamsStack; params; params = params->iNext)
            {
            if (params->iParamData->iSecondaryDisplayData)
                {
                customsWCoverDataCount++;
                }
            }                
            
        iCoverClient->BufStream().WriteInt8L(customsWCoverDataCount);
        if (customsWCoverDataCount)
            {
            for (CCustomNotifParams* params = iCustomNoteParamsStack; params; params = params->iNext)
                {
                if (params->iParamData->iSecondaryDisplayData)
                    {
                    iCoverClient->BufStream() << *params->iParamData->iSecondaryDisplayData;
                    }
                }
            }

        if (groupedExists)
            {
            iCoverClient->BufStream().WriteInt32L(EMissedCallsNotification);
            iCoverClient->BufStream().WriteInt32L(iSoftNotificationAmounts[EMissedCallsNotification]);
            iCoverClient->BufStream().WriteInt32L(ENewMessagesNotification);
            iCoverClient->BufStream().WriteInt32L(iSoftNotificationAmounts[ENewMessagesNotification]);
            iCoverClient->BufStream().WriteInt32L(EChatMessageNotification);
            iCoverClient->BufStream().WriteInt32L(iSoftNotificationAmounts[EChatMessageNotification]);
            iCoverClient->BufStream().WriteInt32L(ENewMailNotification);
            iCoverClient->BufStream().WriteInt32L(iSoftNotificationAmounts[ENewMailNotification]);
            }

        iCoverClient->BufStream().CommitL();
        iCoverClient->IssueCommand();
#endif
        CleanupStack::PopAndDestroy();  // close file
        iNotificationsSaved = ETrue;
        }
    }


void CAknSoftNotificationSubject::SaveNoteL(RWriteStream& aFile, TSoftNoteEntry& aEntry)
    {
    TInt plural = aEntry.iCount;
    const TDesC& text = iGlobalNoteController->NoteText(aEntry.iId);

#ifdef _DEBUG
    _LIT(KDmsg, "AknSoftNotificationPlugin,SaveNoteL:type %d,NoteId %d, count %d ");
    RDebug::Print(KDmsg, aEntry.iType, aEntry.iId, plural);
#endif

    switch (aEntry.iType)
        {
        case ENetworkInformationNotification:
        case EUnstructuredSSDataNotification:
            aFile.WriteUint8L(aEntry.iType);
            aFile << text;
            break;
        case ESelectNetworkNotification:
            aFile.WriteUint8L(aEntry.iType);
            break;
        case ESeparateVoiceMailOnLine1Notification:
        case ESeparateVoiceMailOnLine2Notification:
        case ECellBroadcastNotification:
        case EVoiceMailNotification:
        case EMissedCallsNotification:
        case ENewMessagesNotification:
        case ENewMailNotification:
        case EChatMessageNotification:
            aFile.WriteUint8L(aEntry.iType);
            aFile.WriteInt32L(plural);
            break;
        case EShowGroupedNotification:
            aFile.WriteUint8L(aEntry.iType);
            aFile.WriteInt32L(iSoftNotificationAmounts[EMissedCallsNotification]);
            aFile.WriteInt32L(iSoftNotificationAmounts[ENewMessagesNotification]);
            aFile.WriteInt32L(iSoftNotificationAmounts[EChatMessageNotification]);
            aFile.WriteInt32L(iSoftNotificationAmounts[ENewMailNotification]);
            break;
        case ECustomSoftNotification:
            {
            CCustomNotifParams* params = 0;
            if (aEntry.iId != 0 )
                {
                params = SeekCustomNoteForId(aEntry.iId,ETrue);
                }
            else
                {
                params = SeekCustomNoteForId(aEntry.iCustomId);
                }

            if ( params )
                {
                aFile.WriteUint8L(aEntry.iType);
                aFile.WriteInt16L(params->iCount);
                aFile << *params;
                }
            }
            break;
        default:
            break;
        }
    }

void CAknSoftNotificationSubject::LoadAndQueueSoftNotesL()
    {
    if ( !iNotificationsSaved )
        {
        return;
        }

    RFs& fs = CEikonEnv::Static()->FsSession();
    RFileReadStream file;

    TInt err = file.Open(fs, KAknSNFilename, EFileRead);
    if ( err != KErrNone )
        {
        iNotificationsSaved =EFalse;
        User::Leave(err);
        }

    CleanupClosePushL(file);

    TInt count = file.ReadInt32L();

    if ( count > 0 )
        {
        ClearAllNotes();
        }

    for (TInt ii=0; ii<count; ii++)
        {
        LoadAndQueueNoteL(file);
        }

    iNotificationsSaved = EFalse;

    if ( iSoftNotificationAmounts[EMissedCallsNotification] )
        {
        SetNcnFlag(ETrue);
        }

    CleanupStack::PopAndDestroy();  // close file
    }

void CAknSoftNotificationSubject::LoadAndQueueNoteL(RReadStream& aStream)
    {
    TAknSoftNotificationType type = STATIC_CAST(TAknSoftNotificationType, aStream.ReadUint8L());
    TInt count = 1;
    TBuf<200> text;
    switch (type)
        {
        case ENetworkInformationNotification:
        case EUnstructuredSSDataNotification:
            aStream >> text;
            break;
        case ESeparateVoiceMailOnLine1Notification:
        case ESeparateVoiceMailOnLine2Notification:
        case ECellBroadcastNotification:
        case EVoiceMailNotification:
        case EMissedCallsNotification:
        case ENewMessagesNotification:
        case ENewMailNotification:
        case EChatMessageNotification:
            count = aStream.ReadInt32L();
            break;
        case EShowGroupedNotification:
            iSoftNotificationAmounts[EMissedCallsNotification] = aStream.ReadInt32L();
            iSoftNotificationAmounts[ENewMessagesNotification] = aStream.ReadInt32L();
            iSoftNotificationAmounts[EChatMessageNotification] = aStream.ReadInt32L();
            iSoftNotificationAmounts[ENewMailNotification]     = aStream.ReadInt32L();
            break;
        case ECustomSoftNotification:
            {
            count = aStream.ReadInt16L();
            AddNewCustomNoteL(aStream, count);
            if( iCustomNoteParamsStack )
                {
                TPtrC customTxt( iCustomNoteParamsStack->CustomText( count, EFalse ) );
                if( customTxt.Length() > 0 )
                    {
                    text.Copy( customTxt.Left( text.MaxLength() ) );
                    }
                }            
            }
        default:
            break;
        }

#ifdef _DEBUG
    _LIT(KDmsg, "AknSoftNotificationPlugin,LoadNoteL:type %d, count %d ");
    RDebug::Print(KDmsg,type, count);
#endif

    if (type != EShowGroupedNotification)
        {
        TBool countChanged = ( iSoftNotificationAmounts[type] != count );
        iSoftNotificationAmounts[type] = count;
        UpdateNoteL(type, text, count, countChanged);
        }
    else
        {
        ScheduleGroupedNotifierL();
        }
    }


TBool CAknSoftNotificationSubject::CheckIfAlreadyExists(TAknSoftNotificationType aType)
    {
    TInt count = iSoftNoteEntryList->Count();
    for (TInt ii=count-1; ii>=0; ii--)
        {
        TSoftNoteEntry& entry = (*iSoftNoteEntryList)[ii];
        if (entry.iType == aType)
            {
            return ETrue;
            }
        }
    return EFalse;
    }


TBool CAknSoftNotificationSubject::AutoLockEnabled()
    {
    return EFalse;
    }

void CAknSoftNotificationSubject::AddNewCustomNoteL(
    RReadStream& readStream, TInt aCount, TBool aNewNote )
    {
    AddNewCustomNoteL((RDesReadStream&)readStream, aCount, aNewNote );
    }


void CAknSoftNotificationSubject::AddNewCustomNoteL(
    RDesReadStream& readStream, TInt aCount, TBool aNewNote )
    {
    // Before adding, check if there is a note of this type
    CCustomNotifParams* next = new (ELeave) CCustomNotifParams;
    CleanupStack::PushL( next );
    readStream >> *next;
    CCustomNotifParams* existing = SeekCustomNoteForId(next->iParamData->iNoteResourceId,EFalse);
    if ( existing )
        {
        existing->iCount = aCount;
        CleanupStack::PopAndDestroy( next );
        return;
        }

    // do the switch (append new entry to stack)    
    next->iNext = iCustomNoteParamsStack;
    iCustomNoteParamsStack = next;
    CleanupStack::Pop();

    if( next->iParamType == KAknSoftNotificationDynamic )
        {
        if( aNewNote )
            {
            // if new note, then generate new id
            next->iDynamicData->SetId( GenerateUniqueId() );
            }
        next->iId = next->iDynamicData->Id();
        next->iHasViewInfo = ( KNullViewId != next->iDynamicData->ViewId() );
        next->iCount = aCount;
        next->iNoteId = KErrNotFound;
        next->iSupportsGroupedform = ( 
            next->iDynamicData->SingularLabelGroup().Length() > 0 ||
            next->iDynamicData->PluralLabelGroup().Length() > 0 );
        }
    else // default
        {
        iCustomNoteParamsStack->iId = iCustomNoteParamsStack->iParamData->iNoteResourceId;
        
        iCustomNoteParamsStack->iHasViewInfo = ( 
            KNullViewId != iCustomNoteParamsStack->iParamData->iViewId);
            
        iCustomNoteParamsStack->iCount = aCount;
        iCustomNoteParamsStack->iNoteId = KErrNotFound;
        
        iCustomNoteParamsStack->iSupportsGroupedform = 
            (iCustomNoteParamsStack->iParamData->iGroupedTextResourceId != 0);
        }
    }

CCustomNotifParams* CAknSoftNotificationSubject::SeekCustomNoteForId(TInt aID, TBool aSeekByGNoteId)
    {
    CCustomNotifParams* params = iCustomNoteParamsStack;

    for (;params && (aID != (aSeekByGNoteId?params->iNoteId:params->iId));)
        {
        params = params->iNext;
        }

    return params;
    }


void CAknSoftNotificationSubject::RemoveCustomNoteForId(TInt aID, TBool aSeekByGNoteId)
    {
    CCustomNotifParams* params = iCustomNoteParamsStack;

    if ( !params )
        {
        return;
        }

    if ( aSeekByGNoteId )
        {
        RemoveByType(ECustomSoftNotification, aID);
        }
    else
        { // just remove entry from list
        TInt count = iSoftNoteEntryList->Count();
        for (TInt ii=0; ii<count; ii++)
            {
            if ( iSoftNoteEntryList->At(ii).iCustomId == aID )
                {
                iSoftNoteEntryList->Delete(ii);
                break;
                }
            }
        }

    if ( aID == (aSeekByGNoteId?params->iNoteId:params->iId)) // Remove first note on stack
        {
        iCustomNoteParamsStack = params->iNext;
        delete params;

        if (!iCustomNoteParamsStack)
            {
            iSoftNotificationAmounts[ECustomSoftNotification] = 0;
            }

        return;
        }


    for (;params->iNext && (aID != (aSeekByGNoteId?params->iNext->iNoteId:params->iNext->iId));)
        {
        params = params->iNext;
        }

    if ( params->iNext ) // Found previous item
        {
        CCustomNotifParams* tmp = params->iNext;
        params->iNext = tmp->iNext;
        delete tmp;
        }

    if (!iCustomNoteParamsStack)
        {
        iSoftNotificationAmounts[ECustomSoftNotification] = 0;
        }
    }

void CAknPrivateSoftNoteParameters::InternalizeL( RReadStream& aStream )
    {
    delete iResourceFile;
    iResourceFile = 0;
    TInt length = aStream.ReadInt32L();
    if ( length )
        {
        iResourceFile = HBufC::NewL(length);
        TPtr resptr( iResourceFile->Des() );
        aStream >> resptr;
        }

    iNoteResourceId = aStream.ReadInt32L();
    iPriority = aStream.ReadInt32L();
    iSoftkeys = aStream.ReadInt32L();
    iTone = (CAknNoteDialog::TTone)aStream.ReadInt32L();

    iViewId.iAppUid = TUid::Uid(aStream.ReadUint32L());
    iViewId.iViewUid = TUid::Uid(aStream.ReadUint32L());
    iCustomMessageId = TUid::Uid(aStream.ReadUint32L());
    iAcceptSoftKey = aStream.ReadInt32L();

    iPluralViewId.iAppUid = TUid::Uid(aStream.ReadUint32L());
    iPluralViewId.iViewUid = TUid::Uid(aStream.ReadUint32L());
    iGroupedTextResourceId = aStream.ReadInt32L();

    delete iViewActivationMsg;
    iViewActivationMsg = 0;
    length = aStream.ReadInt32L();
    if ( length != KErrNotFound )
        {
        iViewActivationMsg = HBufC8::NewL(length);
        TPtr8 ptr( iViewActivationMsg->Des() );
        aStream >> ptr;
        }
    
    delete iSecondaryDisplayData;
    iSecondaryDisplayData = 0;
        
    if (aStream.ReadInt8L()) // item has secondary display data
        {
        iSecondaryDisplayData = new (ELeave) CAknSDData();
        aStream >> *iSecondaryDisplayData;
        }
    }

void CAknPrivateSoftNoteParameters::ExternalizeL( RWriteStream& aStream ) const
    {
    aStream.WriteInt32L(iResourceFile->Length());
    aStream << (*iResourceFile);
    aStream.WriteInt32L(iNoteResourceId);
    aStream.WriteInt32L(iPriority);
    aStream.WriteInt32L(iSoftkeys);
    aStream.WriteInt32L(iTone);
    aStream.WriteUint32L(iViewId.iAppUid.iUid);
    aStream.WriteUint32L(iViewId.iViewUid.iUid);
    aStream.WriteUint32L(iCustomMessageId.iUid);
    aStream.WriteInt32L(iAcceptSoftKey);

    aStream.WriteUint32L(iPluralViewId.iAppUid.iUid);
    aStream.WriteUint32L(iPluralViewId.iViewUid.iUid);
    aStream.WriteUint32L(iGroupedTextResourceId);

    if ( iViewActivationMsg ) // optional
        {
        aStream.WriteInt32L(iViewActivationMsg->Length());
        aStream << (*iViewActivationMsg);
        }
    else
        {
        aStream.WriteInt32L(KErrNotFound);
        }
    
    if (iSecondaryDisplayData)
        {
        aStream.WriteInt8L(ETrue);
        aStream << *iSecondaryDisplayData;
        }
    else
        {
        aStream.WriteInt8L(EFalse);            
        }
    }

void CAknSoftNotificationSubject::LaunchNewIMAppL()
    {
    LaunchViewL( KChatSpecificView, TUid::Uid(42), KNullDesC8() );
    }

// ---------------------------------------------------------
// CAknSoftNotificationSubject::LoadUniqueIdL
// ---------------------------------------------------------
//
void CAknSoftNotificationSubject::LoadUniqueIdL()
    {
    RFs& fs( CEikonEnv::Static()->FsSession() );

    RFileReadStream file;
    User::LeaveIfError( file.Open( fs, KAknDynamicIdFilename, EFileRead ) );

    file.PushL();
    iUniqueIdCounter = file.ReadInt32L();
    CleanupStack::PopAndDestroy( &file );
    }

// ---------------------------------------------------------
// CAknSoftNotificationSubject::StoreUniqueIdL
// ---------------------------------------------------------
//
void CAknSoftNotificationSubject::StoreUniqueIdL()
    {
    RFs& fs( CEikonEnv::Static()->FsSession() );

    RFileWriteStream file;
    TInt err = file.Replace( fs, KAknDynamicIdFilename, EFileWrite );

    if( err == KErrPathNotFound )
        {
        // folder not found -> create it
        User::LeaveIfError( fs.MkDirAll( KAknDynamicIdFilename ) );
        User::LeaveIfError( file.Create( fs, KAknDynamicIdFilename, EFileWrite ) );
        }
    else
        {
#ifdef _DEBUG
        if( err )
            {
            _LIT(KDmsg, "AknSoftNotificationPlugin,StoreUniqueIdL: error %d");
            RDebug::Print( KDmsg, err);
            }
#endif        
        User::LeaveIfError( err );
        }

    file.PushL();
    file.WriteInt32L( iUniqueIdCounter );
    file.CommitL();
    CleanupStack::PopAndDestroy( &file );
    }


// ---------------------------------------------------------
// CAknSoftNotificationSubject::GenerateUniqueId
// ---------------------------------------------------------
//
TInt CAknSoftNotificationSubject::GenerateUniqueId()
    {
    TInt failsafe = KMaxTInt; // prevent infinite loop
    while( failsafe ) // loop until found or failsafe expires
        {
        // try next id. Disallow values below KMinimumUniqueId.
        iUniqueIdCounter = Max( KMinimumUniqueId, iUniqueIdCounter + 1 );
        
        // go through existing notes and verify that the id is not used
        CCustomNotifParams* params = iCustomNoteParamsStack;
        while( params && params->iId != iUniqueIdCounter )
            {
            params = params->iNext;
            }
        
        if( !params )
            {
            // Unique id found
            break;
            }
        
        --failsafe;
        }
    
    // Store new id always when it has changed. We can't do anything if the
    // saving fails, so we just ignore the error. 
    TRAPD( err, StoreUniqueIdL() );
    if( err )
        {
#ifdef _DEBUG
        _LIT(KDmsg, "AknSoftNotificationPlugin,GenerateUniqueId: save error %d");
        RDebug::Print( KDmsg, err );
#endif //_DEBUG    
        }
    
    return iUniqueIdCounter;
    }

// ---------------------------------------------------------
// CAknSoftNotificationSubject::WriteResponse
// ---------------------------------------------------------
//
void CAknSoftNotificationSubject::WriteResponse( 
    TDes8& aResponse, TInt aNoteId ) const
    {
    TPckg<TInt> response( aNoteId );
    aResponse.Copy( response.Left( aResponse.MaxLength() ) );
    }

//  End of File
