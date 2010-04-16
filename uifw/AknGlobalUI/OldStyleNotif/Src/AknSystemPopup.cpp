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


#include <uikon/eiksrvui.h>
#include <AknNotiferAppServerApplication.h>
#include "AknSystemPopup.h"
#include <AknNotifyStd.h>
#include <AknNotifierControllerPlugin.h>

#include <avkon.rsg>
#include <avkon.mbg>
#include <eikbtgpc.h>
#include <eikenv.h>
#include <avkon.hrh>
#include <eikimage.h>
#include <barsread.h>

#include <aknnotpi.rsg>

#include "AknNotifyPlugin.hrh"
#include <aknnotedialog.h>
#include <aknnotecontrol.h>
#include <aknconsts.h>

#include <s32mem.h>
#include <viewcli.h>
#include <e32base.h>

#include <AknNotifySignature.h>
#include <aknnoteattributes.h> // for icon to skin conversion

#include <AknCapServer.h>
#include "AknCapServerEntry.h"
#include <AknMediatorFacade.h>
#include <aknSDData.h>

#include <SecondaryDisplay/AknSecondaryDisplayDefs.h>
#include <AknsUtils.h>
#include <aknglobalpopupprioritycontroller.h>
#include "GlobalWindowPriorities.h"
#include "aknmessagereaderlongpressdetector.h" // CAknMessageReaderLongPressDetector    

#include <coreapplicationuisdomainpskeys.h> // KCoreAppUIsAutolockStatus

#include "AknDynamicNotificationData.h"
#include "AknPrivateImageLoader.h"
#include <AknUtils.h>
#include <aknlayout.cdl.h>

#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS

    #include <gfxtranseffect/gfxtranseffect.h>
    #include <akntransitionutils.h>

#endif


const TInt KGlobalNoteGranularity = 4; // Initialize with space for 4 notes

const TInt KMaxSoftNotePriority = 3000;
const TInt KMaxAlarmNotePriority = 4000;
const TInt KMaxNotePriority = 5000;
const TInt KAlarmNotePriority = 3095;

// class CGlobalNoteInfo

CGlobalNoteInfo::CGlobalNoteInfo() :
    iSoftkeys( 0 ),
    iGraphic( -1 ),
    iAnimation( 0 ),
    iPlural( 0 ),
    iAsync( EFalse ),
    iTextProcessing( ETrue ),
    iSDData(NULL),
    iGlobalPopupPriority(0)
    {
    }

CGlobalNoteInfo::~CGlobalNoteInfo()
    {
    delete iSDData;
    }
    
// class CAknGlobalNoteDialog


CAknGlobalNoteDialog::CAknGlobalNoteDialog(MGlobalNoteObserver* aObserver)
:iObserver(aObserver), iPreviousNoteId( KErrNotFound )
    {
    iCommand = KErrCancel;
    }

void CAknGlobalNoteDialog::ConstructL()
    {
    ConstructSleepingDialogL(R_GLOBAL_NOTE);
    }

CAknGlobalNoteDialog::~CAknGlobalNoteDialog()
    {
    delete iImageLoader;
    }

TBool CAknGlobalNoteDialog::OkToExitL(TInt aButtonId)
    {
    
    ((CAknCapAppServerAppUi*) CEikonEnv::Static()->AppUi())->SetIsShortTimeGlobalNoteDisplaying(EFalse);
        
    if ( (iControlType == R_PERMANENT_CONTROL) ||
         (iControlType == R_WAIT_CONTROL && iSoftkeys == R_AVKON_SOFTKEYS_EMPTY) )
        {
        return EFalse;
        }

    else if ( iIsAlarm )
        {
        // Don't let an empty command through.
        if ( aButtonId == EAknSoftkeyEmpty )
            {
            return EFalse;
            }

        CEikButtonGroupContainer& bgc = ButtonGroupContainer();

        if ( aButtonId == EAlertSilence )
            {
            if ( iSoftkeys == R_ALERT_SOFTKEYS_STOP_SILENT__OPEN )
                {
                iSoftkeys = R_ALERT_SOFTKEYS_STOP_SNOOZE__OPEN;
                }
            else // R_ALERT_SOFTKEYS_STOP_SILENT
                {
                iSoftkeys = R_ALERT_SOFTKEYS_STOP_SNOOZE;
                }
            bgc.SetCommandSetL( iSoftkeys );
            bgc.ActivateL();
            bgc.MakeVisible( ETrue );            
            bgc.DrawNow();
            iObserver->GlobalNoteCompleted( EAlertSilence );
            return EFalse;
            }

        // make sure that rsk will be visible next time
        // (this is actually a CBA fault but anyway).
        else if ( iSoftkeys == R_ALERT_SOFTKEYS_STOP_SNOOZE &&
                  !bgc.IsCommandVisible( EAlertSnooze ) )
            {
            bgc.MakeCommandVisible( EAlertSnooze, ETrue );
            }
            
        if ( aButtonId == EAlertOpen )
            {
            if ( iSoftkeys == R_ALERT_SOFTKEYS_STOP_SILENT__OPEN ||
                 iSoftkeys == R_ALERT_SOFTKEYS_STOP_SNOOZE__OPEN ||
                 iSoftkeys == R_ALERT_SOFTKEYS_STOP_SNOOZE )
                {
                iSoftkeys = R_ALERT_SOFTKEYS_STOP_SNOOZE;
                }
            else if ( iSoftkeys == R_ALERT_SOFTKEYS_STOP_SILENT )
                {
                iSoftkeys = R_ALERT_SOFTKEYS_STOP_SILENT ;
                }
            else // R_ALERT_SOFTKEYS_STOP_EMPTY__OPEN
                {
                iSoftkeys = R_ALERT_SOFTKEYS_STOP_EMPTY__EMPTY;
                }

            bgc.SetCommandSetL( iSoftkeys );
            bgc.ActivateL();
            bgc.MakeVisible( ETrue );            
            bgc.DrawNow();
            iObserver->GlobalNoteCompleted( EAlertOpen );
            return EFalse;
            }
        }

    iCommand = aButtonId;
    NextNoteOrExit();
    return ETrue;
    }


void CAknGlobalNoteDialog::PreLayoutDynInitL()
    {
    delete iTimer;
    iTimer = NULL;
    if ( iTimeoutInMicroseconds != ENoTimeout )
        {
        iTimer = CPeriodic::NewL(0);
        iTimer->Start(iTimeoutInMicroseconds, iTimeoutInMicroseconds, 
            TCallBack(CallNextNoteOrExit,this));
        }

    TransferControlAttributes(); // Ensure that new layout will be done

    if (iIsSoftNotification && iObserver->IsAppsKeyLocked() )
        {
        iObserver->SetAppsKeyLocked( EFalse );
        }
    }

void CAknGlobalNoteDialog::HandleResourceChange(TInt aType)
    {
    if ( aType == KAknsMessageSkinChange )  
        {
        iPreviousAnimation = 0; // reload next animation always
        }
        
    CAknStaticNoteDialog::HandleResourceChange(aType);
    }


void CAknGlobalNoteDialog::PostLayoutDynInitL()
    {
    CEikButtonGroupContainer& bgc = ButtonGroupContainer();

    if ( iSoftkeys )
        {
        bgc.SetCommandSetL(iSoftkeys);
        MEikButtonGroup* buttonGrp = bgc.ButtonGroup();
        if( buttonGrp )
            {
            if( iSoftkeyLeft.Length() > 0 )
                {
                bgc.SetCommandL( buttonGrp->CommandId( 
                    CEikButtonGroupContainer::ELeftSoftkeyPosition ), 
                    iSoftkeyLeft );
                }
            if( iSoftkeyRight.Length() > 0 )
                {
                bgc.SetCommandL( buttonGrp->CommandId( 
                    CEikButtonGroupContainer::ERightSoftkeyPosition ),
                    iSoftkeyRight );
                }

            if (AknLayoutUtils::PenEnabled())
                {
                if (iIsSoftNotification && iAutoLock)
                    {
                    bgc.MakeCommandVisible(buttonGrp->CommandId(CEikButtonGroupContainer::ELeftSoftkeyPosition), EFalse);
                    bgc.MakeCommandVisible(buttonGrp->CommandId(CEikButtonGroupContainer::ERightSoftkeyPosition), EFalse);
                    }
                else
                    {
                    if (!bgc.IsCommandVisible(buttonGrp->CommandId(CEikButtonGroupContainer::ELeftSoftkeyPosition)))
                        bgc.MakeCommandVisible(buttonGrp->CommandId(CEikButtonGroupContainer::ELeftSoftkeyPosition), ETrue);
                    if (!bgc.IsCommandVisible(buttonGrp->CommandId(CEikButtonGroupContainer::ERightSoftkeyPosition)))
                        bgc.MakeCommandVisible(buttonGrp->CommandId(CEikButtonGroupContainer::ERightSoftkeyPosition), ETrue);
                    }
                }
            }
        }

    CAknStaticNoteDialog::PostLayoutDynInitL();

    if ( iIsSoftNotification && (iAutoLock > EAutolockOff) )
        { // members below exist always when dialog exists,
          // LockKeys can be called multiple w/o problems, but as a optimisation, lets not
        if (!((CAknGlobalNoteSubject*)iObserver)->iKeyLockController->IsKeyLockEnabled())
            {            
            ((CAknGlobalNoteSubject*)iObserver)->iKeyLockController->LockKeys(ETrue);
            }
        }

    // Play the note note here, since RunLD will not be called (which is where tones are normally played from)
    PlayTone();
    if (!iObserver->IsAppsKeyLocked() && !iIsSoftNotification)
        {
        if(iTimeoutInMicroseconds != EShortTimeout)
           {   
           iObserver->SetAppsKeyLocked( ETrue );
           }
        }
    }

TKeyResponse CAknGlobalNoteDialog::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    if (iIsSoftNotification && aType == EEventKey)
        {
        // Send numbers keys to phone app, and bring it for foreground
        if ((aKeyEvent.iCode >= '0' && aKeyEvent.iCode <= '9') 
            || aKeyEvent.iCode == '#' 
            || aKeyEvent.iCode == '*')
            {
            if( aKeyEvent.iRepeats == 0 )
                {
                MAknPhoneKeyForwarder* keyf = STATIC_CAST(
                    CAknCapAppServerAppUi*, 
                    CEikonEnv::Static()->AppUi())->AsKeyForwarder();
                
                keyf->ForwardKeyToPhoneAppL(aKeyEvent);
            
                ((CAknGlobalNoteSubject*)iObserver)->SetMaxDisplayPriorityL(KMinimumSoftNotePriority);
                }
            return EKeyWasConsumed;
            }
        else if ( aKeyEvent.iCode == EKeyEnter )
            {
            TKeyEvent ccpuStart = { EKeyOK, EStdKeyDevice3, 0, 0 };
            CCoeEnv::Static()->SimulateKeyEventL( ccpuStart, EEventKey );	
            return EKeyWasConsumed;
            }    
        else if ( aKeyEvent.iCode != EKeyOK ) //Other keys don't remove soft notification.
            {
            if ( aKeyEvent.iCode == EKeyNo )
                {
                iCommand = EAknSoftkeyExit;
                NextNoteOrExit();
                }

            return EKeyWasConsumed;
            }
        }

    if (aKeyEvent.iCode == EKeyEscape)
        {
        return EKeyWasNotConsumed;
        }

    // Don't consume send key for displaying the dialer view,
    // only for soft notification.
    if (aKeyEvent.iScanCode == EStdKeyYes && iIsSoftNotification)
        {
        return EKeyWasNotConsumed;
        }

    if (iControlType == R_PERMANENT_CONTROL || 
        iControlType == R_WAIT_CONTROL      || 
        iTimeoutInMicroseconds == ENoTimeout)
        {
        return EKeyWasConsumed;
        }

    // Any keypress dismissed other types of notes
    if (aType == EEventKey)
        {
        NextNoteOrExit();
        }
    return EKeyWasConsumed;
    }

TBool CAknGlobalNoteDialog::CallNextNoteOrExit(TAny* aThis)
    {
    STATIC_CAST(CAknGlobalNoteDialog*, aThis)->NextNoteOrExit();
    return ETrue;
    }

void CAknGlobalNoteDialog::NextNoteOrExit(TBool aDirectExit)
    {
    // If there is another global note waiting, show the next note,
    // otherwise put the global note back to sleep
    delete iTimer;
    iTimer = NULL;
    
    // if there are more notes on queue, don't release the apps key
    if (iObserver->IsAppsKeyLocked() && !iObserver->NoteWaiting())
        {
        iObserver->SetAppsKeyLocked( EFalse );
        }
        
    // Set borders back to zero
    SetNumberOfBorders(0);

    // to make sure that we don't leave RSK hidden even if OkToExitL is not called
    if (aDirectExit)
        {
        CEikButtonGroupContainer& bgc = ButtonGroupContainer();
        if ( iSoftkeys == R_ALERT_SOFTKEYS_STOP_SNOOZE &&
             !bgc.IsCommandVisible( EAlertSnooze ) )
            {
            bgc.MakeCommandVisible( EAlertSnooze, ETrue );
            }
        }

#ifdef RD_SCALABLE_UI_V2
    if ( AknLayoutUtils::PenEnabled() )
        {
        SetGloballyCapturing( EFalse );
        SetPointerCapture( EFalse );
        }
#endif // RD_SCALABLE_UI_V2

    ExitSleepingDialog();
    iDialogActive = EFalse;
    
    TRAP_IGNORE( PublishDialogL( 0 ) ); // to reset 
    iObserver->GlobalNoteCompleted(iCommand);
    }

void CAknGlobalNoteDialog::RemoveCurrentNote()
    {
    // Removes the current global note, so that a non-note dialog can be
    // shown
    delete iTimer;
    iTimer = NULL;
#ifdef RD_SCALABLE_UI_V2
    if ( AknLayoutUtils::PenEnabled() )
        {
        SetGloballyCapturing( EFalse );
        SetPointerCapture( EFalse );
        }
#endif // RD_SCALABLE_UI_V2

    ExitSleepingDialog();
    iDialogActive = EFalse;
    }

void CAknGlobalNoteDialog::UpdateNoteAndDisplayL( CGlobalNoteInfo* aInfo )
    {
    TInt                     notePriority  = aInfo->iPriority;
    TInt                     noteResource  = aInfo->iResourceId;
    TInt                     noteSoftkeys  = aInfo->iSoftkeys;
    TInt                     notePlural    = aInfo->iPlural;
    TInt                     noteGraphic   = aInfo->iGraphic;
    TInt                     noteGraphicM  = aInfo->iGraphicMask;
    TInt                     noteAnimation = aInfo->iAnimation;
    CAknNoteDialog::TTimeout noteTimeout   = aInfo->iTimeOut;
    CAknNoteDialog::TTone    noteTone      = aInfo->iTone;
    CAknSDData*              noteSDData    = aInfo->iSDData;
    
    iCommand = KErrCancel;
    iTimeoutInMicroseconds = noteTimeout;
    iControlType = noteResource;
    
    iIsSoftNotification = (
        notePriority >= KMinimumSoftNotePriority && 
        notePriority <= KMaxSoftNotePriority );
    
    //close the blank screen when global note display
    if (noteTimeout == EShortTimeout)
        {
        CAknCapAppServerAppUi* pAppui =
                (CAknCapAppServerAppUi*) CEikonEnv::Static()->AppUi();
        pAppui->SetIsShortTimeGlobalNoteDisplaying(ETrue);
        }
    
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
    
    // use soft notify context
    if( iIsSoftNotification )
        {
        GfxTransEffect::Register( this, KGfxSystemNotificationControlUid );
        }
    else // must register other possible contexts (global notes)    
        {
        class TResIdToContext
            {
            public:
            TInt iResId;
            TUid iContextId;
            };
        
        TResIdToContext mapArray[] = 
        { 
        R_INFORMATION_CONTROL, KGfxInformationNoteControlUid,
        R_WARNING_CONTROL, KGfxWarningNoteControlUid,
        R_CONFIRMATION_CONTROL, KGfxConfirmationNoteControlUid,
        R_ERROR_CONTROL, KGfxErrorNoteControlUid,
        R_WAIT_CONTROL, KGfxWaitNoteControlUid, 
        R_BATTERY_CHARGING_CONTROL,KGfxSystemNotifBatteryControlUid,
        R_BATTERY_NOT_CHARGING_CONTROL,KGfxSystemNotifBatteryControlUid,
        R_BATTERY_FULL_CONTROL,KGfxSystemNotifBatteryControlUid,
        R_BATTERY_LOW_CONTROL,KGfxSystemNotifBatteryControlUid,
        R_RECHARGE_BATTERY_CONTROL,KGfxSystemNotifBatteryControlUid
        };
        
        TUid contextId = TUid::Uid(0);
        for( TInt i = 0; i<sizeof(mapArray)/sizeof(TResIdToContext); i++ )
            {
            if( mapArray[i].iResId == noteResource )
                {
                contextId = mapArray[i].iContextId;
                break;
                }
            }
        
        if( contextId.iUid == 0 )        
            {
            contextId = KGfxPopupDefaultControlUid;
            }
            
        GfxTransEffect::Register( this, contextId );
        }
    
#endif // RD_UI_TRANSITION_EFFECTS_POPUPS
        
    iIsAlarm = ( notePriority == KAlarmNotePriority );
    iIsAlarmWakeup = (iIsAlarm && aInfo->iAlmFlag == EAskWakeUp);
    iSoftkeys = noteSoftkeys;

#ifdef RD_SCALABLE_UI_V2
    if ( AknLayoutUtils::PenEnabled() )
        {
        SetGloballyCapturing( ETrue ); 
        SetPointerCapture( ETrue ); 
        }
#endif

    if ( !iSoftkeys )
        {
        if (iControlType == R_WAIT_CONTROL)
            {
            iSoftkeys = R_AVKON_SOFTKEYS_CANCEL;
            }
        else if ( notePriority != KAlarmNotePriority )
            {
            iSoftkeys = R_AVKON_SOFTKEYS_EMPTY;
            }
        }
    
    iSoftkeyLeft.Set( aInfo->iLeftSK );
    iSoftkeyRight.Set( aInfo->iRightSK );

    if (aInfo->iImage.Length() <= 0)
        {
        // Exit sleeping dialog firstly for preventing from ui flicker.
        ExitSleepingDialog();
        }

    if( iPreviousNoteId != aInfo->iNoteId && 
        aInfo->iImage.Length() > 0 &&
        !noteResource )
        {
        // this is dynamic soft notification with new image.
        // Set dialogs layout with resource.
        noteResource = R_NEW_DYNAMIC_NOTIFIER_NOTE;
        }    
    
    CAknNoteControl* note = STATIC_CAST( CAknNoteControl*, Control(ENPIGlobalNote) );
    if ( noteResource )
        {
        TResourceReader reader;
        iEikonEnv->CreateResourceReaderLC( reader, noteResource );
        note->ConstructFromResourceL( reader );
        CleanupStack::PopAndDestroy();  // reader
        }

    SetTextProcessing( aInfo->iTextProcessing );

    if ( aInfo->iText.Length() )
        {
        SetTextL( aInfo->iText );
        }
    if ( notePlural > 0 )
        {
        SetTextNumberL( notePlural );
        }

    // check whether this is the same note we showed last time
    TBool noteChanged = ( iPreviousNoteId != aInfo->iNoteId );
    iPreviousNoteId = aInfo->iNoteId;
    TBool asyncImageLoading = EFalse; // delay dialog until image is loaded
    
    if( aInfo->iImage.Length() > 0 )
        {
        // Only load image if the notification has changed
        if( noteChanged )
            {
            // Get icon size from LAF
            TRect mainpane;
            AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, mainpane );
            TAknLayoutRect noterect;
            noterect.LayoutRect( mainpane, AknLayout::popup_note_image_window() );
            TAknLayoutRect gfxrect;
            gfxrect.LayoutRect( noterect.Rect(), 
                AknLayout::Note_with_an_image_pop_up_window_elements_Line_12() );

            // Create image loader
            if( !iImageLoader )
                {
                iImageLoader = CAknPrivateImageLoader::NewL( 
                    CEikonEnv::Static()->FsSession(), *this );
                }
            
            // load icon
            TRAPD( err, 
                iImageLoader->LoadIconL( aInfo->iImage, gfxrect.Rect().Size() ) );
            
            if( !err )
                {
                // we're loading image -> delay dialog until loading is done
                asyncImageLoading = ETrue;
                }
            else
                {
                // when image loading fails, we reset the dialog's image
                SetImageL( NULL );
                }
            }
        }
    if ( noteGraphic != -1 )
        {
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();

        CEikImage* image = new (ELeave) CEikImage;
        CleanupStack::PushL( image );

        //Check For Skin Icon 
        TAknsItemID id = CAknNoteAttributes::GetSkinnedBitmapID( noteGraphic );

        CFbsBitmap* bitmap = NULL;
        CFbsBitmap* mask = NULL;
       
        AknsUtils::CreateIconL(
            skin, 
            id,
            bitmap, 
            mask,
            KAvkonBitmapFile,
            noteGraphic,
            noteGraphicM);

        image->SetPicture( bitmap, mask );
        SetImageL( image );
        CleanupStack::Pop( image );
        }

    if ( noteAnimation != 0 )
        {
        // don't reset animation if it is already loaded            
        if ( noteResource || iPreviousAnimation != noteAnimation )
            {
            note->SetAnimationL( noteAnimation );
            iPreviousAnimation = noteAnimation; 
            }
        }
    else
        iPreviousAnimation = 0;

    iTone = noteTone;

    // We don't want play tone twice (In case some other note appears on top of this note).    
    noteTone = CAknNoteDialog::ENoTone; 
    
    ReportUserActivity();

    if ( noteSDData )
        {
        // secondary display data has been published
        PublishDialogL( noteSDData->iDialogIdx, noteSDData->iCategory );
        }
    else 
        {
        // or the global note is unidentified
        PublishDialogL( EAknUnidentifiedNote, KAknSecondaryDisplayCategory );
        }
        
    CAknMediatorFacade* cover_info = AknMediatorFacade(this);
    if (cover_info) // cover ui defined
        {
        if ( noteSDData && noteSDData->iAdditionalData )
            {// information from client
            cover_info->BufStream() << *(noteSDData->iAdditionalData);        
            }
        else if (iIsAlarm && iObserver->AlarmData())
            { // share detailled alarm info 
            TBuf8<sizeof(SAknAlarmPSInfo)> buf;
            
            // copy constructor should do just fine, but just to make sure               
            buf.Append((const TUint8*)iObserver->AlarmData(),sizeof(SAknAlarmPSInfo)); 
            
            cover_info->BufStream() << buf;
            }
        else
            { // default information about global note
            SAknGlobalNoteData params;    
            params.iResourceId = noteResource;
            params.iTimeOut = noteTimeout;
            params.iTone = noteTone;
            params.iTextLength = aInfo->iText.Length();
            params.iSoftkeys = noteSoftkeys;
            params.iImage.iImageId = noteGraphic;
            params.iImage.iImageMaskId = noteGraphicM;
            params.iAnimation = noteAnimation;
            params.iPlural = notePlural;
            TPckgBuf<SAknGlobalNoteData> buf(params);
            cover_info->BufStream() << buf;
            cover_info->BufStream() << aInfo->iText;                
            }
         cover_info->BufStream().CommitL();    
         }
        
    AknGlobalPopupPriorityController::SetPopupPriorityL(*this, aInfo->iGlobalPopupPriority);
    
    iDialogActive = ETrue;
    
    // invalidate whole dialog area
    if( !asyncImageLoading )
        {
     // DrawDeferred();
        RouseSleepingDialog();
        }
    }

void CAknGlobalNoteDialog::ImageLoadSuccess( CEikImage* aImage )
    {
    // set image    
    TRAP_IGNORE(SetImageL(aImage));

    if( iDialogActive )
        {
        // Draw dialog
        DrawDeferred();
        RouseSleepingDialog();
        }

    delete iImageLoader;
    iImageLoader = NULL;
    }

void CAknGlobalNoteDialog::ImageLoadError( TInt /*aError*/ )
    {
    // clear previous image
    TRAP_IGNORE(SetImageL(NULL));
    
    if( iDialogActive )
        {
        // Draw dialog without image
        DrawDeferred();
        RouseSleepingDialog();
        }
    
    delete iImageLoader;
    iImageLoader = NULL;
    }

void CAknGlobalNoteDialog::SetAutoLock(TBool aAutoLock)
    {
    iAutoLock = aAutoLock;
    }

RWindow& CAknGlobalNoteDialog::GlobalNoteWindow()
    {
    return Window();
    }
    
void CAknGlobalNoteDialog::CEikDialog_Reserved_1()
    {
    }

void CAknGlobalNoteDialog::CEikDialog_Reserved_2()
    {
    }

void CAknGlobalNoteDialog::CAknNoteDialog_Reserved()
    {
    }

void CAknGlobalNoteDialog::CAknStaticNoteDialog_Reserved()
    {
    }

void CAknGlobalNoteDialog::HandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
    if(aPointerEvent.iType == TPointerEvent::EButton1Down)
        {
        iCaptured = ETrue;
        }
    if (Rect().Contains(aPointerEvent.iPosition) && (aPointerEvent.iType == TPointerEvent::EButton1Up)
        && iIsAlarm)
        {
        if (!iIsAlarmWakeup)
            {
            CEikDialog::TryExitL(EAlertOpen);
            }
		}
    else if ((iSoftkeys == R_AVKON_SOFTKEYS_EMPTY) && 
            (iTimeoutInMicroseconds != ENoTimeout) && 
            (aPointerEvent.iType == TPointerEvent::EButton1Up)&& iCaptured)
        {
        CEikDialog::TryExitL(EAknSoftkeyExit);
        }
    else
        {
        CAknStaticNoteDialog::HandlePointerEventL(aPointerEvent);
        }
    
    if(aPointerEvent.iType == TPointerEvent::EButton1Up)
        {
        iCaptured = EFalse;
        }
    
    }

// class CAknGlobalNoteSubject

CAknGlobalNoteSubject* CAknGlobalNoteSubject::NewL(
    MAknKeyLockController* aKeyLockController )
    {
    CAknGlobalNoteSubject* self =
        new (ELeave) CAknGlobalNoteSubject(aKeyLockController);
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

CAknGlobalNoteSubject::CAknGlobalNoteSubject(MAknKeyLockController* aKeyLockController)
:iKeyLockController(aKeyLockController),iNoteId(1), iMaxDisplayPriority(KMaxTInt), 
    iMaxDisplayPriorityLimit(KMaxSoftNotePriority)
    {
    }

void CAknGlobalNoteSubject::ConstructL()
    {
    iGlobalNoteList = new(ELeave) CArrayFixFlat<CGlobalNoteInfo*>(KGlobalNoteGranularity);
    iGlobalNoteList->SetReserveL(KGlobalNoteGranularity);
    iDisplayingNoteId = KErrNotFound;
    
    // Construct the emergency call support here, but it is not activated until a
    // permanent note is started
    iEcsDetector = CAknEcsDetector::NewL();
    iKeyLockController->AddObserverL(this);

    // Setup a async callback for displaying the next note in the queue
    // This allows the next note to be displayed from the destructor of
    // a previous note, but the callback will execute only when the
    // destructor has finished
    TCallBack callback(CallDisplayNextNote, this);
    iDisplayCallback = new(ELeave)CAsyncCallBack(callback, CActive::EPriorityHigh);

    iGlobalNote = new(ELeave)CAknGlobalNoteDialog(this);
    iGlobalNote->ConstructL();

    iDialogController = CNotifierDialogController::NewL(this);
    SetNotificationDialogObserver(iDialogController);

    // Make sure that server has a pointer to the dialog stack
    STATIC_CAST(CAknCapServer*,CEikonEnv::Static()->AppServer())->
        SetGlobalNoteController(iDialogController);
        
    STATIC_CAST(CAknCapAppServerAppUi*,CEikonEnv::Static()->AppUi())->
        iGlobalNotesController = this;
    
    // Only initialize message reader long press detector 
    // if message reader has been installed
    if ( CAknMessageReaderLongPressDetector::MessageReaderInstalled() )
        {
        iMessageReaderLongPressDetector = CAknMessageReaderLongPressDetector::NewL( &iGlobalNote->ButtonGroupContainer(), iGlobalNote->GlobalNoteWindow() );
        STATIC_CAST(CAknCapAppServerAppUi*,CEikonEnv::Static()->AppUi())->
            iMessageReaderLongPressDetector = iMessageReaderLongPressDetector;
        }
        
    // Set-up autolock status change notification.
    User::LeaveIfError(iAutolockStatusProperty.Attach(
        KPSUidCoreApplicationUIs, 
        KCoreAppUIsAutolockStatus));

    iAutolockStatusSubscriber = new (ELeave) CSubscriber(
        TCallBack(AutolockStatusNotificationL, this), 
        iAutolockStatusProperty);

    iAutolockStatusSubscriber->Subscribe();       
    
    // Get the initial value.
    iAutolockStatusProperty.Get(iAutoLock);
    
    iGlobalNote->SetAutoLock(iAutoLock > EAutolockOff);

    iAlarmData = new SAknAlarmPSInfo;
    User::LeaveIfNull(iAlarmData);
    }


TPtrC8 CAknGlobalNoteSubject::StartL(const TDesC8& aBuffer)
    {
    RDesReadStream readStream(aBuffer);
    
    // TInt32 takes four chars.
    if ( aBuffer.Length() < 4 )
        {
        User::Leave(KErrArgument);
        }
    else
        {
        TInt signature = readStream.ReadInt32L();
        
        if ( signature == KAKNNOTIFIERSIGNATURE_GETNOTEID )
            {
            iRetPckg().iNoteId = iNoteId++;
            return iRetPckg;            
            }

        if ( signature != KAKNNOTIFIERSIGNATURE )
            {
            User::Leave(KErrArgument);            
            }
        }        

    TBuf<KGlobalNoteTextLength> text; // We mustn't use heap...

    TInt type = readStream.ReadInt16L();
    readStream >> text;

    TInt priority = readStream.ReadInt16L();
    TInt softkeys = readStream.ReadInt32L();
    TInt graphic = readStream.ReadInt16L();
    TInt graphicMask = readStream.ReadInt16L();
    TInt animation = readStream.ReadInt32L();
    TInt tone = readStream.ReadInt16L();
    TChar adapterTypesUsed = readStream.ReadInt8L();
    TChar textProcessing = readStream.ReadInt8L();
    TInt preallocatedNoteId = readStream.ReadInt32L();
    CAknSDData* secondaryDisplayInfo = new (ELeave) CAknSDData();
    CleanupStack::PushL(secondaryDisplayInfo);
    if (readStream.ReadInt8L())
        {
        readStream >> *secondaryDisplayInfo;        
        }
    
    TInt noteId = KErrNotFound;

    if ( type == EAknGlobalRechargeBatteryNote ||
         type == EAknGlobalBatteryLowNote||
         type == EAknGlobalBatteryFullNote||
         type == EAknGlobalChargingNote ||
         type == EAknGlobalNotChargingNote ||
         type == EAknGlobalBatteryFullUnplugNote ||
         type == EAknGlobalUnplugChargerNote )
        {
        if (iNotesDisabled)
            {
            priority = KMaxAlarmNotePriority;
            tone = CAknNoteDialog::ENoTone;
            }
        secondaryDisplayInfo->iDialogIdx = type;
        // fw will set correct category uid automatically    
        secondaryDisplayInfo->iCategory = KNullUid;
        }

    // make sure that error notes w/o timeout do not get hidden behinds soft notifications
    if (type == EAknGlobalErrorNote || type == EAknGlobalWarningNote )
        {
        // We alter only default priority, and do it only if note does not have timeout.
        if (priority == 0 && softkeys != 0 ) 
            {
            priority = KMaxSoftNotePriority+1;
            }
        }

    switch ( type )
        {
        case EAknGlobalInformationNote:
            noteId = AddNoteToQueueL( R_INFORMATION_CONTROL,
                                      text,
                                      priority, 
                                      CAknNoteDialog::ELongTimeout,
                                      CAknNoteDialog::EConfirmationTone,
                                      tone,
                                      graphic, 
                                      graphicMask,
                                      animation,
                                      softkeys,
                                      preallocatedNoteId );
            break;

        case EAknGlobalWarningNote:
            noteId = AddNoteToQueueL( R_WARNING_CONTROL,
                                      text,
                                      priority,
                                      CAknNoteDialog::ELongTimeout, 
                                      CAknNoteDialog::EWarningTone,
                                      tone,
                                      graphic,
                                      graphicMask,
                                      animation,
                                      softkeys,
                                      preallocatedNoteId );
            break;
            
        case EAknGlobalConfirmationNote:
            noteId = AddNoteToQueueL( R_CONFIRMATION_CONTROL,
                                      text,
                                      priority, 
                                      CAknNoteDialog::EShortTimeout,
                                      CAknNoteDialog::EConfirmationTone,
                                      tone,
                                      graphic, 
                                      graphicMask,
                                      animation,
                                      softkeys,
                                      preallocatedNoteId );
            break;
            
        case EAknGlobalErrorNote:
            noteId = AddNoteToQueueL( R_ERROR_CONTROL,
                                      text,
                                      priority,
                                      CAknNoteDialog::ELongTimeout, 
                                      CAknNoteDialog::EErrorTone,
                                      tone,
                                      graphic,
                                      graphicMask,
                                      animation,
                                      softkeys,
                                      preallocatedNoteId );
            break;
            
        case EAknGlobalWaitNote:
            noteId = AddNoteToQueueL( R_WAIT_CONTROL,
                                      text,
                                      priority,
                                      CAknNoteDialog::ENoTimeout, 
                                      CAknNoteDialog::ENoTone,
                                      tone,
                                      graphic,
                                      graphicMask,
                                      animation,
                                      softkeys,
                                      preallocatedNoteId );
            break;
            
        case EAknGlobalPermanentNote:
            noteId = AddNoteToQueueL( R_PERMANENT_CONTROL,
                                      text,
                                      priority, 
                                      CAknNoteDialog::ENoTimeout,
                                      CAknNoteDialog::ENoTone,
                                      tone,
                                      graphic,
                                      graphicMask, 
                                      animation,
                                      0,                    // softkeys
                                      preallocatedNoteId );
            break;
            
        case EAknGlobalChargingNote:
            noteId = AddNoteToQueueL( R_BATTERY_CHARGING_CONTROL,
                                      priority,
                                      tone,
                                      preallocatedNoteId );
            break;
            
        case EAknGlobalNotChargingNote:
            noteId = AddNoteToQueueL( R_BATTERY_NOT_CHARGING_CONTROL,
                                      priority,
                                      tone,
                                      preallocatedNoteId );
            break;
            
        case EAknGlobalBatteryFullNote:
            noteId = AddNoteToQueueL( R_BATTERY_FULL_CONTROL,
                                      priority,
                                      tone,
                                      preallocatedNoteId );
            break;
            
        case EAknGlobalBatteryLowNote:
            noteId = AddNoteToQueueL( R_BATTERY_LOW_CONTROL,
                                      priority,
                                      tone,
                                      preallocatedNoteId );
            break;
            
        case EAknGlobalRechargeBatteryNote:
            noteId = AddNoteToQueueL( R_RECHARGE_BATTERY_CONTROL,
                                      priority,
                                      tone,
                                      preallocatedNoteId );
            break;
            
        case EAknCancelGlobalNote:
            CancelNote( priority );
            break;
            
        case EAknGlobalTextNote:
            noteId = AddNoteToQueueL( R_NOTE_PLAIN_TEXT_CONTROL,
                                      text,
                                      priority, 
                                      CAknNoteDialog::ELongTimeout,
                                      CAknNoteDialog::EConfirmationTone,
                                      tone,
                                      graphic, 
                                      graphicMask,
                                      animation,
                                      softkeys,
                                      preallocatedNoteId );
            break;
            
        case EAknGlobalBatteryFullUnplugNote:
            noteId = AddNoteToQueueL( R_BATTERY_FULL_UNPLUG_CONTROL,
                                      priority,
                                      tone,
                                      preallocatedNoteId );
            break;
            
        case EAknGlobalUnplugChargerNote:
            noteId = AddNoteToQueueL( R_UNPLUG_CHARGER_CONTROL,
                                      priority,
                                      tone,
                                      preallocatedNoteId );
            break;
            
        default:
            break;
        }
        
    if( type == EAknGlobalChargingNote ||
        type == EAknGlobalNotChargingNote ||
        type == EAknGlobalBatteryFullNote ||
        type == EAknGlobalBatteryLowNote ||
        type == EAknGlobalRechargeBatteryNote ||
        type == EAknGlobalBatteryFullUnplugNote ||
        type == EAknGlobalUnplugChargerNote )
        {
        Note(noteId)->iGlobalPopupPriority = 1;
        }

    TBool sdDataSet( EFalse );

    if ( noteId != KErrNotFound && iGlobalNoteList ) // we are not in cancel state
        {
        TInt index = NoteIndex(noteId);
        if ( index != KErrNotFound && iGlobalNoteList->Count() > index )
            {
            // Is global note adapter used.                
            (*iGlobalNoteList)[index]->iIsFromAdapter = adapterTypesUsed; 
            (*iGlobalNoteList)[index]->iTextProcessing = textProcessing;
            }
        if ( index != KErrNotFound && secondaryDisplayInfo->iDialogIdx != 0 )
            {
            sdDataSet = SetSDData( noteId, secondaryDisplayInfo );
            }
        }
    
    if ( sdDataSet )
        {
        CleanupStack::Pop( secondaryDisplayInfo );
        }          
    else // secondaryDisplayInfo ownership not transferred
        {
        CleanupStack::PopAndDestroy( secondaryDisplayInfo );
        }

#ifdef _DEBUG
    _LIT(KDmsg, "AknGlobalNote, StartL:id %d,type %d,prior %d");
    RDebug::Print(KDmsg,noteId,type,priority);
#endif

    TryDisplayNextNoteL(ETrue);

    iRetPckg().iNoteId = noteId;
    return iRetPckg;
    }

CAknGlobalNoteSubject::~CAknGlobalNoteSubject()
    {
    // Stop subscribe for autolock status changes in PubSub.
    if (iAutolockStatusSubscriber)
        {
        iAutolockStatusSubscriber->StopSubscribe();
        }
    iAutolockStatusProperty.Close();
    delete iAutolockStatusSubscriber;
    
    delete iDialogController;
    delete iGlobalNote;
    delete iDisplayCallback;
    iKeyLockController->RemoveObserver(this);
    delete iEcsDetector;
    
    if ( iGlobalNoteList )
        {
        TInt count = iGlobalNoteList->Count();
        for ( TInt i = count - 1; i > KErrNotFound; i-- )
            {
            delete (*iGlobalNoteList)[i];
            }
        delete iGlobalNoteList;
        }
        
    delete iIdle;
    delete iAlarmData;

    if ( iMessageReaderLongPressDetector ) 
        {
        delete iMessageReaderLongPressDetector;
        }    
    }

void CAknGlobalNoteSubject::Release()
    {
    delete this;
    }

CAknGlobalNoteSubject::TNotifierInfo CAknGlobalNoteSubject::RegisterL()
    {
    iInfo.iUid = KAknGlobalNoteUid;
    iInfo.iChannel=EAknNotifierChannelNote;
    iInfo.iPriority = ENotifierPriorityVHigh;
    return iInfo;
    }

CAknGlobalNoteSubject::TNotifierInfo CAknGlobalNoteSubject::Info() const
    {
    return iInfo;
    }

void CAknGlobalNoteSubject::StartL(const TDesC8& aBuffer, TInt /*aReplySlot*/,
    const RMessagePtr2& aMessage)
    {
    RDesReadStream readStream(aBuffer);        
        
    // TInt32 takes four chars.
    if (aBuffer.Length() >= 4 && readStream.ReadInt32L() == KAKNNOTIFIERSIGNATURE_GETNOTEID)
        {
        aMessage.Complete(KErrNotSupported);
        return;
        }

    StartL(aBuffer);
    TInt noteId = iRetPckg().iNoteId;
    
    if (noteId == KErrNotFound)
        {
        aMessage.Complete(KErrNone);
        return;
        }
    
    // returns correct info or panics, no need to error handling here
    CGlobalNoteInfo* info = Note(noteId); 
    
    info->iAsync = ETrue;
    info->iMessage = aMessage;
#ifdef _DEBUG
    _LIT(KDmsg, "AknGlobalNote, async StartL:id %d,prior %d");
    RDebug::Print(KDmsg,noteId,info->iPriority);
#endif
    }

void CAknGlobalNoteSubject::Cancel()
    {
    CancelOustandingRequests();
    }

TPtrC8 CAknGlobalNoteSubject::UpdateL(const TDesC8& aBuffer)
    {
#ifdef _DEBUG
    _LIT(KDmsg,"AknGlobalNote, UpdateL");
    RDebug::Print(KDmsg);
#endif
    return StartL(aBuffer);
    }

void CAknGlobalNoteSubject::KeyPressed(const TKeyEvent& /*aKeyEvent*/,TEventCode /*aType*/)
    {
    }

TInt CAknGlobalNoteSubject::AddNoteToQueueL(
    TInt aResourceId, 
    const TDesC& aText, 
    TInt aPriority, 
    CAknNoteDialog::TTimeout aTimeout, 
    CAknNoteDialog::TTone aDefaultTone, 
    TInt aUserTone, 
    TInt aGraphic, 
    TInt aGraphicMask, 
    TInt aAnimation, 
    TInt aSoftkeys)
    {
    return AddNoteToQueueL(
        aResourceId, 
        aText, 
        aPriority, 
        aTimeout, 
        aDefaultTone, 
        aUserTone, 
        aGraphic, 
        aGraphicMask, 
        aAnimation, 
        aSoftkeys,
        0);
    }

TInt CAknGlobalNoteSubject::AddNoteToQueueL(
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
    TInt aPreAllocatedNoteId)
    {
    if (!IsPreallocatedNoteIdValid(aPreAllocatedNoteId))
        {
        return KErrNotFound;
        }
        
    // Check that note doesn't already exist
    TInt count = iGlobalNoteList->Count();
    for (TInt ii=0; ii<count; ii++)
        {
        CGlobalNoteInfo* info = (*iGlobalNoteList)[ii];
        if (info->iResourceId == aResourceId)
            {
            if (info->iText.Compare(aText) == 0)
                {
                return KErrNotFound;
                }
            }
        }
            
    CGlobalNoteInfo* info = new (ELeave) CGlobalNoteInfo();
    
    if (aPreAllocatedNoteId)
        {
        info->iNoteId = aPreAllocatedNoteId;
        }
    else
        {
        info->iNoteId = iNoteId++;    
        }        
    
    info->iResourceId = aResourceId;
    info->iTimeOut = aTimeout;
    if (aSoftkeys)
        {
        info->iTimeOut = CAknNoteDialog::ENoTimeout;
        }
    CAknNoteDialog::TTone tone = aDefaultTone;
    if (aUserTone != -1)
        {
        tone = (CAknNoteDialog::TTone)aUserTone;
        }
    info->iTone = tone;
    info->iText.Copy(aText);
    info->iPriority = aPriority;
    info->iSoftkeys = aSoftkeys;
    info->iGraphic = aGraphic;
    info->iGraphicMask = aGraphicMask;
    info->iAnimation = aAnimation;
    iGlobalNoteList->AppendL( info );

    iGlobalNote->SetNumberOfBorders( StackCount() );

    return info->iNoteId;
    }

TInt CAknGlobalNoteSubject::AddNoteToQueueL(TInt aResourceId, TInt aPriority, TInt aTone, 
    TInt aPreAllocatedNoteId)
    {
    if (!IsPreallocatedNoteIdValid(aPreAllocatedNoteId))
        {
        return KErrNotFound;
        }

    // Check that note doesn't already exist    
    TInt count = iGlobalNoteList->Count();
    for (TInt ii=0; ii<count; ii++)
        {
        CGlobalNoteInfo* info = (*iGlobalNoteList)[ii];
        if (info->iResourceId == aResourceId)
            {
            return KErrNotFound;
            }
        }
    
    CGlobalNoteInfo* info = new (ELeave) CGlobalNoteInfo();
    
    if (aPreAllocatedNoteId)
        {
        info->iNoteId = aPreAllocatedNoteId;
        }
    else
        {
        info->iNoteId = iNoteId++;
        }        
    
    info->iResourceId = aResourceId;
    info->iTimeOut = CAknNoteDialog::EShortTimeout;
    CAknNoteDialog::TTone tone = CAknNoteDialog::ENoTone;
    if (aTone != -1)
        {
        tone = (CAknNoteDialog::TTone)aTone;
        }
    info->iTone = tone;
    info->iPriority = aPriority;
    iGlobalNoteList->AppendL( info );

    iGlobalNote->SetNumberOfBorders( StackCount() );

    return info->iNoteId;
    }


TInt CAknGlobalNoteSubject::AddSoftNotificationL(const TDesC& aText, TInt aResource, TInt aCount, 
    TInt aPriority, TInt aSoftkeys, TInt aTone)
    {
    CGlobalNoteInfo* info = new (ELeave) CGlobalNoteInfo();
    info->iNoteId = iNoteId++;
    info->iText.Copy(aText);
    info->iResourceId = aResource;
    info->iTimeOut = CAknNoteDialog::ENoTimeout;
    info->iTone = CAknNoteDialog::TTone(aTone);
    info->iPriority = aPriority;
    info->iSoftkeys = aSoftkeys;
    info->iPlural = aCount;
    iGlobalNoteList->AppendL( info );

    iGlobalNote->SetNumberOfBorders( StackCount() );

    return info->iNoteId;
    }

TInt CAknGlobalNoteSubject::AddSoftNotificationL( 
    const TDesC& aText, 
    TInt aCount,
    TInt aPriority, 
    TInt aTone,
    const TDesC& aLeftSK,
    const TDesC& aRightSK,
    const TDesC8& aImage )
    {
    CGlobalNoteInfo* info = new (ELeave) CGlobalNoteInfo();
    CleanupStack::PushL( info );
    info->iNoteId = iNoteId++;
    // use resource if no image is defined to clear the previous image
    info->iResourceId = 
        aImage.Length() > 0 ? 0 : R_NEW_DYNAMIC_NOTIFIER_NOTE;
    info->iText.Copy( aText.Left( KGlobalNoteTextLength ) );
    info->iSoftkeys = R_AVKON_SOFTKEYS_SHOW_EXIT__SHOW;
    info->iTimeOut = CAknNoteDialog::ENoTimeout;
    info->iTone = CAknNoteDialog::TTone(aTone);
    info->iPriority = aPriority;
    info->iPlural = aCount;
    
    // extended custom parameters
    info->iImage.Set( aImage );
    info->iRightSK.Set( aRightSK );
    info->iLeftSK.Set( aLeftSK );

    iGlobalNoteList->AppendL( info );
    CleanupStack::Pop( info );
    iGlobalNote->SetNumberOfBorders( StackCount() );
    return info->iNoteId;
    }

void CAknGlobalNoteSubject::TryDisplayNextNoteL(TBool aShowAsynch)
    {
    if ( iGlobalNoteList && iGlobalNoteList->Count() == 0 )
        {
        return;
        }

#ifdef _DEBUG
    _LIT(KDmsg, "AknGlobalNote, TryDisplayNextNoteL:displaying %d");
    RDebug::Print(KDmsg,iDisplayingNoteId);
#endif

    if (iDisplayingNoteId == KErrNotFound)
        {
        // Note current note, so display as normal
        if (!aShowAsynch)
            {                
            DisplayNextNoteL();            
            }
        else if (!iDisplayCallback->IsActive())
            {
            iDisplayCallback->CallBack();
            }
        }
    else
        {
        TInt highIndex;
        TInt highPriority;
        CGlobalNoteInfo* info = Note( iDisplayingNoteId );
        // we don't want add any note on top of alarm note ( at least currently )
        if (info->iPriority == KAlarmNotePriority )
            {
            return;
            }

        HighestPriorityNote(highIndex, highPriority);
        if (highPriority > iCurrentPriority)
            {
            if (iSoftNoteObserver)
                {
                iSoftNoteObserver->CancelSoftNote(info->iPriority);
                }
            if (iNotificationDialogObserver )
                {
                iNotificationDialogObserver->CancelSoftNote(info->iPriority);
                }
            iDisplayingNoteId = KErrNotFound;
            if (!aShowAsynch)
                {
                DisplayNextNoteL();
                iCurrentPriority = highPriority;
                }
            else if (!iDisplayCallback->IsActive())
                {
                iDisplayCallback->CallBack();   
                }   
            }
        }
    }


void CAknGlobalNoteSubject::HighestPriorityNote(TInt& aIndex, TInt& aPriority)
    {
    // Priority of notes:
    // First added non-waiting note in queue has priority
    // If no non-waiting notes added, first added waiting note
    // Notes with a prioriy higher than iMaxDisplayPriority are ignored
    TInt priority = KMinTInt;
    TInt index = KErrNotFound;
    TInt count = iGlobalNoteList->Count();
    for (TInt ii=0; ii<count; ii++)
        {
        CGlobalNoteInfo* info = (*iGlobalNoteList)[ii];
        if (info->iPriority < iMaxDisplayPriority || info->iPriority > iMaxDisplayPriorityLimit)
            {
            TInt actualPriority = info->iPriority;
            if (info->iTimeOut != CAknNoteDialog::ENoTimeout)
                {
                // Boost priority of non-waiting notes, so that
                // they interrupt soft notifications
                actualPriority += KMaxNotePriority;
                }
            if (actualPriority > priority)
                {
                priority = actualPriority;
                index = ii;
                }
            }
        }
    aIndex = index;
    aPriority = priority;
    }


void CAknGlobalNoteSubject::DisplayNextNoteL()
    {
    if (iDisplayCallback->IsActive())
        {
        iDisplayCallback->Cancel();                    
        }

    if ( iMessageReaderLongPressDetector ) 
        {
        iMessageReaderLongPressDetector->SoftNotifierVisible( EFalse );
        } 

    // Count permanent notes and see if ECS should be turned on/off
    TInt permanentNoteCount = PermanentNotesCount();
    if ( permanentNoteCount > 0 )
        {
        iEcsDetector->ConnectToEventSource();
        }
    else
        {
        iEcsDetector->CloseEventSource();
        iEcsDetector->Reset(); // Ecs queue is cleared; keys up til here are forgotten
        }

    TInt count = iGlobalNoteList->Count();
    if (iDisplayingNoteId != KErrNotFound || count == 0)
        {
        return;
        }

    // Find next highest priority note

    TInt priority = KMinTInt;
    TInt index = 0;
    HighestPriorityNote(index, priority);
    if (index == KErrNotFound)
        {
        return;
        }

    CGlobalNoteInfo* info = (*iGlobalNoteList)[index];

    if (iSoftNoteObserver)
        {
        
        // activate long press detector if soft notification is shown
        if ( iMessageReaderLongPressDetector ) 
            {
            TBool isSoftNotification = ( info->iPriority >= KMinimumSoftNotePriority && 
                                         info->iPriority <= KMaxSoftNotePriority );
            if ( isSoftNotification )
                {
                iMessageReaderLongPressDetector->SoftNotifierVisible( ETrue );
                }
            }          
        if (iSoftNoteObserver->ShowSoftNoteL( info->iPriority, info->iText ) )
            {
            // Soft note is being displayed instead
            iDisplayingNoteId = info->iNoteId;
#ifdef _DEBUG
    _LIT(KDmsg, "AknGlobalNote, DisplayNextNoteL:SoftNote %d");
    RDebug::Print( KDmsg, info->iPriority );
#endif
            return;
            }
        }
    if (iNotificationDialogObserver)
        {
        if (iNotificationDialogObserver->ShowSoftNoteL(info->iPriority, info->iText))
            {
            // Get rid of any current global note
            iGlobalNote->RemoveCurrentNote();
            // Notifier note is being displayed instead
            iDisplayingNoteId = info->iNoteId;
#ifdef _DEBUG
    _LIT(KDmsg2, "AknGlobalNote, DisplayNextNoteL:Other type %d");
    RDebug::Print(KDmsg2,info->iPriority);
#endif
            return;
            }
        }

    iGlobalNote->UpdateNoteAndDisplayL(info);
    
    // display stack indicator, if more than 1 note pending
    iGlobalNote->SetNumberOfBorders(StackCount());   

    iDisplayingNoteId = info->iNoteId;
    iCurrentPriority = priority;
#ifdef _DEBUG
    _LIT(KDmsg3, "AknGlobalNote, DisplayNextNoteL:Normal: %d");
    RDebug::Print(KDmsg3,info->iPriority);
#endif
    }


void CAknGlobalNoteSubject::GlobalNoteCompleted(TInt aCommand)
    {
    iCurrentPriority = KMinTInt;
    if (iDisplayingNoteId == KErrNotFound)
        {
        return;
        }
    CGlobalNoteInfo* info = Note( iDisplayingNoteId );

#ifdef _DEBUG
    _LIT(KDmsg, "AknGlobalNote, NoteCompleted:Command %d, id %d");
    RDebug::Print(KDmsg,aCommand, info->iNoteId);
#endif

    if ( iSoftNoteObserver && info->iPriority >= KMinimumSoftNotePriority)
        {
        iSoftNoteObserver->SoftNoteCompleted(info->iNoteId, aCommand);
        }
    if (iNotificationDialogObserver)
        {
        iNotificationDialogObserver->SoftNoteCompleted(info->iNoteId, aCommand);
        if ( aCommand == EAlertSilence )
            {
            CAknMediatorFacade* coverData = AknMediatorFacade( iGlobalNote );
            if ( coverData )
                {
                SAknIntegerUpdate s = 
                    {
                    EAknGlobalNotifierUpdateSoftkeys,
                    R_ALERT_SOFTKEYS_STOP_SNOOZE
                    };
            
                TPckg<SAknIntegerUpdate> pck(s);
                coverData->ResetBuffer();
                coverData->BufStream() << pck;
                TRAP_IGNORE(
                    coverData->BufStream().CommitL();
                    coverData->PostUpdatedDataL();
                    );
                }
            return;
            }
        else if ( aCommand == EAlertOpen )
            {
            // Works the same way as the "silence" key...don't complete/close the note.
            return;
            }
        }
    if (info->iAsync)
        {
        if (info->iIsFromAdapter) // if adapter is in use, we need to change softkey
            {                    // enumeration according to GlobalNote.h
            if ( aCommand == EAknSoftkeyOk )
                {
                info->iMessage.Complete( 1 ); //    EGlobalNoteResultOk      = 1,
                }
            else if ( aCommand == EAknSoftkeyExit )
                {
                info->iMessage.Complete( 2 ); //    EGlobalNoteResultExit    = 2,
                }
            else if ( aCommand == EAknSoftkeyCancel )
                {
                info->iMessage.Complete( 3 ); //    EGlobalNoteResultCancel  = 3,
                }
            else if ( aCommand == EAknSoftkeyBack )
                {
                info->iMessage.Complete( 4 ); //    EGlobalNoteResultBack    = 4,
                }
            else if ( aCommand == EAknSoftkeyClose )
                {
                info->iMessage.Complete( 5 ); //    EGlobalNoteResultClose   = 5,
                }
            else if ( aCommand == EAknSoftkeyQuit )
                {
                info->iMessage.Complete( 6 ); //    EGlobalNoteResultQuit    = 6,
                }
            else if ( aCommand == EAknSoftkeyYes )
                {
                info->iMessage.Complete( 7 ); //    EGlobalNoteResultYes     = 7,
                }
            else if ( aCommand == EAknSoftkeyNo )
                {
                info->iMessage.Complete( 8 ); //    EGlobalNoteResultNo      = 8,
                }
            else if ( aCommand == EAknSoftkeyShow )
                {
                info->iMessage.Complete( 9 ); //    EGlobalNoteResultAnswer  = 9
                }
            else // Default:
                {
                info->iMessage.Complete(KErrCancel);
                }
            }
        else  // return S60 softkeyId
            {
            info->iMessage.Complete(aCommand);
            }
        info->iAsync = EFalse;
        }
    
    iGlobalNoteList->Delete( NoteIndex( iDisplayingNoteId ) );
    delete info;
    info = NULL;
    
    iDisplayingNoteId = KErrNotFound;

    // Call DisplayNextNoteL via a async callback.
    iDisplayCallback->CallBack();
    }

TInt CAknGlobalNoteSubject::CallDisplayNextNote( TAny* aThis )
    {
    // Need to trap this, since this may be called from destructor of
    // prevous global note.
    // Worst situation is that global note will not be displayed immediately,
    // and sit in queue until another global note is displayed.
    TRAP_IGNORE( STATIC_CAST( CAknGlobalNoteSubject*, aThis )->DisplayNextNoteL() );
    return 0;
    }

void CAknGlobalNoteSubject::SetMessageNotifierObserver( MAknMessageNotifierObserver* aMessageNotifierObserver )
    {
    if ( iMessageReaderLongPressDetector )
        {
        iMessageReaderLongPressDetector->SetMessageNotifierObserver( aMessageNotifierObserver );
        }
    }

// -----------------------------------------------------------------------------
// CAknGlobalNoteSubject::CancelNote
// -----------------------------------------------------------------------------
//
void CAknGlobalNoteSubject::CancelNote( TInt aNoteId, TBool aShowNext )
    {
    CancelNote( aNoteId, aShowNext, ETrue );
    }


// -----------------------------------------------------------------------------
// CAknGlobalNoteSubject::CancelNote
// -----------------------------------------------------------------------------
//
void CAknGlobalNoteSubject::CancelNote( TInt aNoteId,
                                        TBool aShowNext,
                                        TBool aDeleteNoteInfo )
    {
    
#ifdef _DEBUG
    _LIT( KDmsg, "AknGlobalNote, NoteCompleted:Command %d, id %d" );
    RDebug::Print( KDmsg, aNoteId );
#endif

    TInt noteIndex = NoteIndex( aNoteId );
    if ( noteIndex == KErrNotFound )
        {
        return;
        }

    CGlobalNoteInfo* info = Note( aNoteId );
    const TInt priority = info->iPriority;    
    
    if ( iNotificationDialogObserver )
        {
        iNotificationDialogObserver->CancelSoftNote( priority );
        }

    if ( iDisplayingNoteId == aNoteId )
        {
        // Deleting will also remove note from stack.
        if ( !aShowNext )
            {
            if ( info->iAsync )
                {
                info->iMessage.Complete( KErrCancel );
                info->iAsync = EFalse;
                }
                
            iGlobalNoteList->Delete( noteIndex );
            
            if ( aDeleteNoteInfo )
                {
                // aDeleteNoteInfo specifies whether or not the note
                // is really discarded.
            	delete info;
            	info = NULL;
            	// info should not be accessed any more.
                }
                
            iDisplayingNoteId = KErrNotFound;
            }

        if ( iSoftNoteObserver )
            {
            // disable long press detector when notification is closed from the screen
            if ( iMessageReaderLongPressDetector ) 
                {
                iMessageReaderLongPressDetector->SoftNotifierVisible( EFalse );
                }            
            TBool noteDeleted = iSoftNoteObserver->CancelSoftNote( priority );
            if ( noteDeleted && aShowNext ) // grouped note was deleted so remove it from queue
                {
                iGlobalNoteList->Delete( noteIndex );

                if ( aDeleteNoteInfo )
                    {
                    // aDeleteNoteInfo specifies whether or not the note
                    // is really discarded.
		        	delete info;
            	    info = NULL;
            	    // info should not be accessed any more.
                    }
                
                iDisplayingNoteId = KErrNotFound;
                }
            }

        iGlobalNote->NextNoteOrExit( ETrue );
        iDisplayingNoteId = KErrNotFound;
        }
    else
        {
        // If not displayed, remove note from stack.
        if ( info->iAsync )
            {
            info->iMessage.Complete( KErrCancel );
            info->iAsync = EFalse;
            }

        iGlobalNoteList->Delete( noteIndex );

        if ( aDeleteNoteInfo )
            {
            // aDeleteNoteInfo specifies whether or not the note
            // is really discarded.
        	delete info;
            info = NULL;
            // info should not be accessed any more.            	
            }
        
        // Change stack indicator. Display stack indicator, if more than 1 note pending.
        iGlobalNote->SetNumberOfBorders( StackCount() );   
        }
    }


void CAknGlobalNoteSubject::CancelOustandingRequests()
    {
    TInt count = iGlobalNoteList->Count();
    for (TInt ii = count - 1; ii >= 0; ii--)
        {
        CGlobalNoteInfo* info = (*iGlobalNoteList)[ii];
        if ( info->iAsync )
            {
            // Only cancelled if the cancelling thread is where the
            // global note originated from.
            RThread t;
            TInt err = info->iMessage.Client(t);
            CAknCapAppServerAppUi* appUi = (CAknCapAppServerAppUi*) CEikonEnv::Static()->AppUi();
            if ( !err && ( appUi->iClientId == t.Id() ) )
                {
                CancelNote( info->iNoteId );
                }
            t.Close();
            }
        }
    }


void CAknGlobalNoteSubject::SetSoftNoteObserver(MSoftNotificationObserver* aObserver)
    {
    iSoftNoteObserver = aObserver;
    }

void CAknGlobalNoteSubject::SetNotificationDialogObserver(MSoftNotificationObserver* aObserver)
    {
    iNotificationDialogObserver = aObserver;
    }

TInt CAknGlobalNoteSubject::NotePlural(TInt aNoteId)
    {
    TInt count = iGlobalNoteList->Count();
    for (TInt ii = 0; ii < count; ii++)
        {
        CGlobalNoteInfo* info = (*iGlobalNoteList)[ii];
        if (info->iNoteId == aNoteId)
            {
            return info->iPlural;
            }
        }
    return -1;
    }

const TDesC& CAknGlobalNoteSubject::NoteText(TInt aNoteId)
    {
    TInt count = iGlobalNoteList->Count();
    for (TInt ii = 0; ii < count; ii++)
        {
        CGlobalNoteInfo* info = (*iGlobalNoteList)[ii];
        if (info->iNoteId == aNoteId)
            {
            return info->iText;
            }
        }
    return KNullDesC;
    }

void CAknGlobalNoteSubject::SetMaxDisplayPriorityL(TInt aPriority, TInt aDelay)
    {
#ifdef _DEBUG
    _LIT(KDmsg, "AknGlobalNote, SetMaxDisplayPriorityL: %d");
    RDebug::Print(KDmsg,aPriority);
#endif

    if (iNotesDisabled)
        {
        iPreviousDisplayPriority = aPriority;
        return;
        }

    iMaxDisplayPriority = aPriority;
    if (iDisplayingNoteId == KErrNotFound)
        {
        if (aDelay > 0 && iGlobalNoteList->Count() > 0)
            {
            if (!iDisplayCallback->IsActive())
                {
                iDisplayCallback->CallBack();           
                }
            return;
            }
        
        TryDisplayNextNoteL();
        return;
        }

    CGlobalNoteInfo* info = Note( iDisplayingNoteId );

    if (info->iPriority >= iMaxDisplayPriority)
        {
        TBool async = info->iAsync;
        // Displaying note is higher than max priority, so cancel it.
        if ( async )
            {
            // Leave note to queue, but remove it from display.
            iDisplayingNoteId = KErrNotFound;
            iGlobalNote->NextNoteOrExit();
            }
        else
            {
            if ( info->iPriority == KAlarmNotePriority )
                {
                // Idle states does not have any effect to alarm.
                if  ( iMaxDisplayPriority != KMinimumSoftNotePriority ) 
                    {
                    CancelNote( info->iNoteId, EFalse );
                    }
                }
            else
                {
                // All the others but alarm note are rescheduled.                    
                CancelNote( info->iNoteId, EFalse, EFalse ); // remove from display, but
                                                             // don't delete info object,
                                                             // as it's appended back.
                iGlobalNoteList->AppendL( info );   // add to queue
                }
            }
        }
        
    else if ( iGlobalNoteList->Count() > 1 ) // there are other notifications on queue
        {
        TryDisplayNextNoteL();
        }
    }

TInt CAknGlobalNoteSubject::StackCount()
    {
    TInt total = 0;
    TInt count = iGlobalNoteList->Count();
    for (TInt ii = 0; ii < count; ii++)
        {
        CGlobalNoteInfo* info = (*iGlobalNoteList)[ii];
        if (info->iPriority < iMaxDisplayPriority)
            {
            total++;
            }
        }
    return total;
    }


CGlobalNoteInfo* CAknGlobalNoteSubject::Note(TInt aNoteId)
    {
    TInt count = iGlobalNoteList->Count();
    for (TInt ii = 0; ii < count; ii++)
        {
        CGlobalNoteInfo* info = (*iGlobalNoteList)[ii];
        if (info->iNoteId == aNoteId)
            {
            return info;
            }
        }
    return (*iGlobalNoteList)[0];
    }


TInt CAknGlobalNoteSubject::NoteIndex(TInt aNoteId)
    {
    TInt count = iGlobalNoteList->Count();
    for (TInt ii = 0; ii < count; ii++)
        {
        CGlobalNoteInfo* info = (*iGlobalNoteList)[ii];
        if ( info->iNoteId == aNoteId )
            {
            return ii;
            }
        }
    return KErrNotFound;
    }

TInt CAknGlobalNoteSubject::PermanentNotesCount() const
    {
    TInt permanentCount = 0;
    TInt count = iGlobalNoteList->Count();
    for (TInt ii = 0; ii < count; ii++)
        {
        const CGlobalNoteInfo* info = (*iGlobalNoteList)[ii];
        if (info->iPriority < iMaxDisplayPriority)
            if ( info->iResourceId == R_PERMANENT_CONTROL )
            {
            permanentCount++;
            }
        }
    return permanentCount;
    }

void CAknGlobalNoteSubject::KeyLockStatusChange(TKeyLockStatus aStatus)
    {
#ifdef _DEBUG
    RDebug::Print(_L("--KeyLockStatusChange aStatus [%d], NoteDisabled [%d], Previous [%d], Limit [%d], Max [%d]"),
            aStatus, iNotesDisabled, iPreviousDisplayPriority, iMaxDisplayPriorityLimit, iMaxDisplayPriority);
#endif
    
    // Handle EKeyLockStopNotifications.
    if (aStatus == EKeyLockStopNotifications)
        {
        if (!iNotesDisabled)
            {
            iPreviousDisplayPriority = iMaxDisplayPriority;
            iMaxDisplayPriorityLimit = KMaxAlarmNotePriority;
            // Ignore errors, just means next note may not display at present.
            TRAP_IGNORE(SetMaxDisplayPriorityL(KMinTInt));
            iNotesDisabled = ETrue;
#ifdef _DEBUG
            _LIT(KDmsg, "--DisableGlobalNotes");
            RDebug::Print(KDmsg);
#endif
            }
        }
    // Handle EKeyLockAllowNotifications.
    else if (aStatus == EKeyLockAllowNotifications)
        {
        if (iNotesDisabled)
            {
            iNotesDisabled = EFalse;
            iMaxDisplayPriorityLimit = KMaxSoftNotePriority;
            // Ignore errors, just means next note may not display at present.
            TRAP_IGNORE( SetMaxDisplayPriorityL(iPreviousDisplayPriority));
#ifdef _DEBUG
            _LIT(KDmsg2, "--AllowGlobalNotes");
            RDebug::Print(KDmsg2);
#endif
            }
        }
    // Handle EKeyLockCancelNotification.
    else if (aStatus == EKeyLockCancelNotification)
        {
#ifdef _DEBUG
        _LIT(KDmsg3, "--CancelAllGlobalNotes");
        RDebug::Print(KDmsg3);
#endif
        // First check to make sure.
        if (iDisplayingNoteId >= 0)
            {
            CGlobalNoteInfo* info = Note(iDisplayingNoteId);
            if (info->iResourceId == R_PERMANENT_CONTROL)
                {
                return;
                }
            }

        CancelNote(iDisplayingNoteId, EFalse);
        
        // Cancel all other queued notifications.
        TInt count = iGlobalNoteList->Count();
        for (TInt ii = count - 1; ii >= 0; ii--)
            {
            CGlobalNoteInfo* info = (*iGlobalNoteList)[ii];
            if (info->iPriority < iMaxDisplayPriority && info->iResourceId != R_PERMANENT_CONTROL)
                {
                CancelNote(info->iNoteId, EFalse);
                }
            }
        SetAppsKeyLocked( EFalse );
        }
    // Handle EHideSoftNotifications.
    else if ( aStatus == EHideSoftNotifications )
        {
#ifdef _DEBUG
        _LIT(KDmsg4, "--HideSoftNotifications");
        RDebug::Print(KDmsg4);
#endif
        TRAP_IGNORE(SetMaxDisplayPriorityL(KMinimumSoftNotePriority));
        }
    // Handle EShowSoftNotifications.
    else if ( aStatus == EShowSoftNotifications )
        {
#ifdef _DEBUG
        _LIT(KDmsg5, "--AllowSoftNotifications");
        RDebug::Print(KDmsg5);
#endif
        if (iNotesDisabled)
            {
            // After the max priority is set, we need to restore iNoteDisabled back to ETrue,
            // otherwise, it will break EKeyLockAllowNotifications.
            iNotesDisabled = EFalse;
            TRAP_IGNORE(SetMaxDisplayPriorityL(KMaxTInt, 50000));
            iNotesDisabled = ETrue;
            iPreviousDisplayPriority = KMaxTInt;
            }
        else
            {
            TRAP_IGNORE(SetMaxDisplayPriorityL(KMaxTInt, 50000));    
            }
        }
    }

TBool CAknGlobalNoteSubject::NoteWaiting()
    {
    TInt count = StackCount();
    if (count > 1 && iDisplayingNoteId != KErrNotFound)
        {
        return ETrue;
        }
    return EFalse;
    }

TBool CAknGlobalNoteSubject::IsAppsKeyLocked()
    {
    return iAppsKeyLocked;
    }

void CAknGlobalNoteSubject::SetAppsKeyLocked( TBool aLocked )
    {
    if ( ( iAppsKeyLocked && aLocked ) || ( !iAppsKeyLocked && !aLocked ) )
        {
        return;
        }

    TInt err = ((CAknNotifierAppServerAppUi*)(CEikonEnv::Static())->EikAppUi())->
        SuppressAppSwitching( aLocked );

    if ( !err )
        {
        iAppsKeyLocked = aLocked;
        }
    }

TInt CAknGlobalNoteSubject::EnableAutolockEmulation( TAny* aThis )
    {
    CAknGlobalNoteSubject& me = *static_cast<CAknGlobalNoteSubject*>(aThis);
    me.iKeyLockController->LockKeys(ETrue);
    delete me.iIdle;
    me.iIdle = 0;
    return KErrNone;
    }


TInt CAknGlobalNoteSubject::DisplayAlarmL( TInt aType,
                                           const TDesC& aDescription,
                                           const TDesC& /*aTime*/ )
    {
    
#ifdef _DEBUG
    RDebug::Print(_L("CAknGlobalNoteSubject::DisplayAlarmL type [%d], noteId [%d], priority [%d]"), 
            aType, iDisplayingNoteId, iCurrentPriority);
#endif
    
    TBuf<KGlobalNoteTextLength> buf;
    
    // Make sure that buffer will not overflow.
    if ( aDescription.Length() > KGlobalNoteTextLength )
        {
        buf.Append( aDescription.Left( KGlobalNoteTextLength ) );
        }
    else
        {
        buf.Append( aDescription );
        }

    TInt rid( R_ALARM_CONTROL );
    TInt animation( 0 );
    TInt softkeys( 0 );
    TInt imageId( -1 );
    TInt maskId( -1 );
    
    if ( aType & EMskOpen ) // msk
        {
        if ( aType & EHideSnooze ) // no snooze (+ no silence)
            {
            // stop_open_empty
            softkeys = R_ALERT_SOFTKEYS_STOP_EMPTY__OPEN;
            iAlarmData->iAlarmSoftkeys = EAknAlarmStopNone;
            }
        else if ( aType & ENoSilence ) // no silence
            {
            // stop_open_snooze
            softkeys = R_ALERT_SOFTKEYS_STOP_SNOOZE__OPEN;
            iAlarmData->iAlarmSoftkeys = EAknAlarmStopSnooze;
            }
        else // silence
            {
            // stop_open_silence
            softkeys = R_ALERT_SOFTKEYS_STOP_SILENT__OPEN;
            iAlarmData->iAlarmSoftkeys = EAknAlarmStopSilent;
            }
        }
    else // no msk
        {
        if ( aType & EHideSnooze ) // no snooze (+ no silence)
            {
            // stop_empty_empty
            softkeys = R_ALERT_SOFTKEYS_STOP_EMPTY__EMPTY;
            iAlarmData->iAlarmSoftkeys = EAknAlarmStopNone;
            }
        else if ( aType & ENoSilence ) // no snooze
            {
            // stop_empty_snooze
            softkeys = R_ALERT_SOFTKEYS_STOP_SNOOZE;
            iAlarmData->iAlarmSoftkeys = EAknAlarmStopSnooze;
            }
        else // silence
            {
            // stop_empty_silence
            softkeys = R_ALERT_SOFTKEYS_STOP_SILENT;
            iAlarmData->iAlarmSoftkeys = EAknAlarmStopSilent;
            }
        }

    if ( aType & EClockAlarm )
        {
        // animation = R_ANIM_CLOCK_ALARM;
        imageId = EMbmAvkonQgn_note_alarm_clock;
        maskId  = EMbmAvkonQgn_note_alarm_clock_mask;
        }

    else if ( aType & ECalendarAlarm )
        {
        // animation = R_ANIM_CALENDAR_ALARM;
        imageId = EMbmAvkonQgn_note_alarm_calendar;
        maskId  = EMbmAvkonQgn_note_alarm_calendar_mask;
        }
    else if ( aType == EAskWakeUp )
        {
        animation = R_QGN_NOTE_QUERY_ANIM;
        softkeys = R_AVKON_SOFTKEYS_YES_NO__YES;
        }

    TInt noteId =
        AddNoteToQueueL( rid,
                         buf,
                         KAlarmNotePriority,
                         CAknNoteDialog::ENoTimeout,
                         CAknNoteDialog::ENoTone,
                         -1,
                         imageId,
                         maskId,
                         animation,
                         softkeys );

    CGlobalNoteInfo* alarmNoteInfo = (*iGlobalNoteList)[iGlobalNoteList->Count()-1];
    if ( alarmNoteInfo )
        {
        alarmNoteInfo->iGlobalPopupPriority = KGlobalWindowPriority_Alarm;
        alarmNoteInfo->iAlmFlag = aType;
        }

    // We will not specify alarm otherwise here. Alarm implementation provides more precise 
    // information using AddAlarmAdditionalData.
    CAknSDData* data = CAknSDData::NewL(
        KAknSecondaryDisplayCategory, 
        aType == EAskWakeUp ? EAknSwitchOnAfterAlarmNote : EAknAlarmNote,
        KNullDesC8 );
       
    TBool sdDataSet = SetSDData( noteId, data );
    
    if ( !sdDataSet ) // data ownership not transferred
        {
        delete data;
        }
        
    TryDisplayNextNoteL();
    
#ifdef _DEBUG
    RDebug::Print(_L("DisplayAlarmL noteId [%d], Display [%d], Prio [%d], AutoLock [%d], Limit [%d], Disabled [%d]"),
            noteId, iDisplayingNoteId, iCurrentPriority, iAutoLock, iMaxDisplayPriorityLimit, iNotesDisabled);
#endif
    
    return noteId;
    }


void CAknGlobalNoteSubject::AddAlarmAdditionalInfo( 
    TInt aType,
    const TDesC& aTime,
    const TDesC& aDate,
    const TDesC& aSubject,
    const TDesC& aLocation )
    {
    if ( iAlarmData )
        {
        iAlarmData->iType = aType > 0 ? 
            (SAknAlarmPSInfo::TAlarmType)aType : SAknAlarmPSInfo::EAknClock;
            
        iAlarmData->iTime.Zero();
        iAlarmData->iTime.Append(
            aTime.Ptr(), 
            Min(iAlarmData->iTime.MaxLength(), 
            aTime.Length()));
            
        iAlarmData->iDate.Zero();
        iAlarmData->iDate.Append(
            aDate.Ptr(), 
            Min(iAlarmData->iDate.MaxLength(), 
            aDate.Length()));
        
        iAlarmData->iSubject.Zero();
        iAlarmData->iSubject.Append(
            aSubject.Ptr(), 
            Min(iAlarmData->iSubject.MaxLength(), 
            aSubject.Length()));
        
        iAlarmData->iLocation.Zero();
        iAlarmData->iLocation.Append(
            aLocation.Ptr(),
            Min(iAlarmData->iLocation.MaxLength(), 
            aLocation.Length()));
        }
    }

TBool CAknGlobalNoteSubject::SetSDData( TInt aNoteId, CAknSDData* aData )
    {
    TInt index = NoteIndex( aNoteId );
    
    if ( index != KErrNotFound )
        {
        delete (*iGlobalNoteList)[index]->iSDData;
        (*iGlobalNoteList)[index]->iSDData = aData;
        return ETrue;
        }
        
    return EFalse;
    }
    
TBool CAknGlobalNoteSubject::IsPreallocatedNoteIdValid(const TInt aPreAllocatedNoteId)
    {
    if (aPreAllocatedNoteId)
        {
        // Pre-allocated note id is given. Check that it is from valid range and that there is no 
        // note with that id already existing.
        if (aPreAllocatedNoteId >= iNoteId || NoteIndex(aPreAllocatedNoteId) != KErrNotFound)
            {
            return EFalse;
            }
        }
    
    return ETrue;
    }
    
// -----------------------------------------------------------------------------
// CAknGlobalNoteSubject::AutolockStatusNotificationL
// -----------------------------------------------------------------------------
//    
TInt CAknGlobalNoteSubject::AutolockStatusNotificationL(TAny* aObj)
    {
    if (aObj != NULL)
        {
        static_cast<CAknGlobalNoteSubject*>(aObj)->HandleAutolockStatusNotificationL();
        return KErrNone;
        }
    else
        {
        return KErrArgument;
        }
    }
    
// -----------------------------------------------------------------------------
// CAknGlobalNoteSubject::HandleAutolockStatusNotificationL
// -----------------------------------------------------------------------------
//      
void CAknGlobalNoteSubject::HandleAutolockStatusNotificationL()
    {
    iAutolockStatusProperty.Get(iAutoLock);

    iGlobalNote->SetAutoLock(iAutoLock > EAutolockOff);
    if (iAutoLock > EAutolockOff)
        {
        if (iIdle)
            {
            return; // Notify already activated.
            }
        else
            {
            iIdle = CIdle::NewL(CActive::EPriorityIdle);
            iIdle->Start(TCallBack(EnableAutolockEmulation, this));
            }
        }
    else
        {
        if (iIdle) // Cancel enabling autolock.
            {
            delete iIdle;
            iIdle = 0;
            }
        }

#ifdef _DEBUG
    _LIT(KDmsg,"AknGlobalNote (HandleAutolockStatusNotificationL), AutolockStatus: %d");
    RDebug::Print(KDmsg, iAutoLock);
#endif
    }   
    
// -----------------------------------------------------------------------------
// CAknGlobalNoteSubject::CSubscriber::CSubscriber
// -----------------------------------------------------------------------------
//        
CAknGlobalNoteSubject::CSubscriber::CSubscriber(TCallBack aCallBack, RProperty& aProperty)
    : CActive(EPriorityNormal), iCallBack(aCallBack), iProperty(aProperty)
    {
    CActiveScheduler::Add(this);
    }

// -----------------------------------------------------------------------------
// CAknGlobalNoteSubject::CSubscriber::~CSubscriber
// -----------------------------------------------------------------------------
//  
CAknGlobalNoteSubject::CSubscriber::~CSubscriber()
    {
    Cancel();
    }

// -----------------------------------------------------------------------------
// CAknGlobalNoteSubject::CSubscriber::Subscribe
// -----------------------------------------------------------------------------
//  
void CAknGlobalNoteSubject::CSubscriber::Subscribe()
    {
    if (!IsActive())
        {
        iProperty.Subscribe(iStatus);
        SetActive();
        }
    }

// -----------------------------------------------------------------------------
// CAknGlobalNoteSubject::CSubscriber::StopSubscribe
// -----------------------------------------------------------------------------
//  
void CAknGlobalNoteSubject::CSubscriber::StopSubscribe()
    {
    Cancel();
    }

// -----------------------------------------------------------------------------
// CAknGlobalNoteSubject::CSubscriber::RunL
// -----------------------------------------------------------------------------
//  
void CAknGlobalNoteSubject::CSubscriber::RunL()
    {
    if (iStatus.Int() == KErrNone)
        {
        iCallBack.CallBack();
        Subscribe();
        }
    }

// -----------------------------------------------------------------------------
// CAknGlobalNoteSubject::CSubscriber::DoCancel
// -----------------------------------------------------------------------------
//  
void CAknGlobalNoteSubject::CSubscriber::DoCancel()
    {
    iProperty.Cancel();
    }    

// End of File
