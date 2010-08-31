/*
* Copyright (c) 2002 - 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  App UI
*
*/

#include <eikbtgpc.h>
#include "aknappui.h"
#include <avkon.rsg>
#include <avkon.hrh>
#include <eikenv.h>
#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikenvinterface.h>
#endif
#include <AknDef.h>
#include "aknconsts.h"
#include <aknsoundsystem.h>
#include <AknSgcc.h>
#include <AknSettingCache.h>
#include <AknWsEventObserver.h>
#include <apgwgnam.h>
#include <babitflags.h>
#include <hlplch.h>

#include <centralrepository.h>
#include <AvkonInternalCRKeys.h>   // KAknQwertyInputModeActive (and others)
#include <AknFepInternalCRKeys.h>  // KAknFepHashKeySelection
#include <settingsinternalcrkeys.h> // KSettingsAutolockStatus
#include <cenrepnotifyhandler.h>
#include <e32property.h>
#include <ctsydomainpskeys.h>

#include <eikmenub.h>
#include <eikcolib.h>
#include <eikapp.h>
#include <eikon.hrh>
#include <AknsUtils.h>
#include <AknsConstants.h>

#include "aknshut.h"
#include "aknenv.h"
#include <aknsoundsystem.h>
#include "aknanimdllstd.h"
 
#include <textresolver.h>
#include <AknGlobalNote.h>
#include <apgcli.h>
#include <AknUtils.h>
#include <AknBidiTextUtils.h>
#include <aknconsts.h>

#include <AknCapServerClient.h>
#include "AknDebug.h"
#include <AknPanic.h>

#include <akntranseffect.h> // for Transition effect enumerations
#include <aknlayoutscalable_avkon.cdl.h>
#include <gfxtranseffect/gfxtranseffect.h>

#include <aknSDData.h>
#include <AknNotifyStd.h>
#include <SecondaryDisplay/AknSecondaryDisplayDefs.h>
#include <startupdomainpskeys.h>

#include "transitionmanager.h"
#include <PtiEngine.h>   
#include <PtiKeyMappings.h> 

#include <akntoolbar.h>
#include <eikdialg.h>

#ifdef RD_SCALABLE_UI_V2
#include <AknPriv.hrh>
#include <akntouchpane.h>
#endif

#include <touchfeedbackadaptation.h>
#include <touchfeedback.h>

#include <aknpointereventmodifier.h>

// UIDS for dialler view
const TUid KPhoneAppUid = { 0x100058B3 };
const TUid KAknDiallerViewUid = {0x10282D81};
const TUid KDiallerVievCommand = {0x1};
const TUid KVoiceUiUID = { 0x101F8543 };
_LIT( KVoiceDialApplication, "z:\\sys\\bin\\vuivoicerecognition.exe" ); //SIVC

#include "akncompaif.h" // touch compatibility mode

const TUid KActiveIdle2Uid = {0x102750F0};
const TUid KActiveIdleView = {0x1};

#ifndef APPLICATIONORIENTATION_H
const TUid KCRUidDefaultAppOrientation = {0x200159ED};
#endif

//const TInt KAknAppUiViewsGranularity = 1;

NONSHARABLE_CLASS(CAknAppUiExtension)
  : public CBase, 
    public MCenRepNotifyHandlerCallback,
    public MCoeViewActivationObserver
    {
public:
    static CAknAppUiExtension* NewL();
    ~CAknAppUiExtension();

    // From MCenRepNotifyHandlerCallback
    void HandleNotifyInt(TUint32 aId, TInt aNewValue); 
    
    // from MCoeViewActivationObserver
    void HandleViewActivation(const TVwsViewId& aNewlyActivatedViewId,const TVwsViewId& aViewIdToBeDeactivated);
    
private: 
    CAknAppUiExtension();
    void ConstructL();  

public:    
    MAknAliasKeyCodeResolver* iAknAliasKeyCodeResolver;

    // Handle to Central Repository.
    CRepository* iCenRep;    
    
    // For CenRep value change notifications. 
    CCenRepNotifyHandler* iCenRepNotifyHandler;        
    
    // PubSub property for qwerty mode status.
    RProperty iQwertyModeStatusProperty;

    // more app UI flags    
    enum TAknExtFlags
        {
        EHashKeyDown,       // Indicates whether hash key is down.    
        EHashKeyMarking,    // Caches the value of CenRep key KAknFepHashKeySelection.
        ESimulatingEvent,
        EAppIsHiddenInBackground,
        EFocusLost
        };
    TBitFlags iFlags;
    
    TInt iDisabledScanCode;
    
    TUid iLastActivatedViewId;
    };
    
    
CAknAppUiExtension* CAknAppUiExtension::NewL()
    {
    CAknAppUiExtension* self = new (ELeave) CAknAppUiExtension();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }    
    
CAknAppUiExtension::CAknAppUiExtension():
    iDisabledScanCode( -1 )
    {
    }
    
void CAknAppUiExtension::ConstructL()
    {
    // Start listening a CenRep key indicating whether hash key selection is active.
    TRAPD(err, iCenRep = CRepository::NewL(KCRUidAknFep));
    if (err == KErrNone)
        {
        iCenRepNotifyHandler = CCenRepNotifyHandler::NewL(*this,
            *iCenRep,
            CCenRepNotifyHandler::EIntKey,
            KAknFepHashKeySelection);

        iCenRepNotifyHandler->StartListeningL();
        TBool hashKeyMarking;
        if (iCenRep->Get(KAknFepHashKeySelection, hashKeyMarking) == KErrNone)
            iFlags.Assign(EHashKeyMarking, hashKeyMarking);
        } 
        
    // Attach to qwerty mode status property. Hash key marking is disabled when qwerty 
    // mode is active. Attach success also even if the value doesn't exist.
    User::LeaveIfError(iQwertyModeStatusProperty.Attach(KCRUidAvkon, KAknQwertyInputModeActive));
    }     
    
CAknAppUiExtension::~CAknAppUiExtension()
    {
    // Stop listening CenRep.
    if (iCenRepNotifyHandler)
        {
        iCenRepNotifyHandler->StopListening();
        }
    delete iCenRepNotifyHandler;
    delete iCenRep; 
    
    // Close PubSub handle.
    iQwertyModeStatusProperty.Close();
    }

// -----------------------------------------------------------------------------
// CAknAppUiExtension::HandleNotifyInt
// -----------------------------------------------------------------------------
//
void CAknAppUiExtension::HandleNotifyInt(TUint32 aId, TInt aNewValue)
    {
    if (aId == KAknFepHashKeySelection)
        {
        iFlags.Assign(EHashKeyMarking, aNewValue);
        }
    }
    
void CAknAppUiExtension::HandleViewActivation(const TVwsViewId& aNewlyActivatedViewId,const TVwsViewId& aViewIdToBeDeactivated)
    {
    CEikonEnv& eikEnv = *CEikonEnv::Static();
    TUid thisAppUid = eikEnv.EikAppUi()->Application()->AppDllUid();
    // if changing from another app to a new view in this app, clear the redraw stores
    if (aViewIdToBeDeactivated.iAppUid != thisAppUid &&
         ( (iLastActivatedViewId != TUid::Null() && 
         aNewlyActivatedViewId.iViewUid != iLastActivatedViewId) ||
         eikEnv.ScreenDevice()->CurrentScreenMode() != CAknSgcClient::ScreenMode().ModeNumber()))
        eikEnv.WsSession().ClearAllRedrawStores();
    if (aNewlyActivatedViewId.iAppUid == thisAppUid)
        iLastActivatedViewId = aNewlyActivatedViewId.iViewUid;
    }
    

enum TAknAppUiBaseFlags
    {
    EEmbedded,
    EFaded,
    EContainerWasForeground,
    EContainerWasPartialForeground,
    EFullScreen,
    EPartialForeground,
    ELayoutAwareApp, // Deprecated
    EOrientationSpecified,
    EOrientationLandscape,
    EOrientationAutomatic,
    EMSKEnabled,
    EForegroundOrPartialForeground,
    EAppClosing,
    ETouchCompatible,
    ESingleClickCompatible
    };


// CLASS DECLARATION

/** 
 * A class to launch the dialler or SIVC from non used send key press
 */ 
 
NONSHARABLE_CLASS ( CAknDiallerLauncher ) : public CCoeControl
    {
public:
    static CAknDiallerLauncher* NewL(CAknCompaIf*& aCompaIf);
    ~CAknDiallerLauncher();
    void SetFlags( const TInt aFlags );
private: // From CCoeControl
    TKeyResponse OfferKeyEventL(const TKeyEvent &aKeyEvent, TEventCode aType);
    
private:
    CAknDiallerLauncher(CAknCompaIf*& aCompaIf);
    void ConstructL();
    void StartKeyTimerL();
    void StopKeyTimer();
    void LaunchDiallerL();
    void LaunchVoiceCommandL();
    static TInt ReportLongPressL( TAny* aThis );
    
private:
    CPeriodic* iKeyTimer;
    CAknCompaIf*& iCompaIf; // touch compatibility mode
    TInt iKeyFlags;
    };

// -----------------------------------------------------------------------------
// CAknDiallerLauncher::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CAknDiallerLauncher* CAknDiallerLauncher::NewL(CAknCompaIf*& aCompaIf)
    {
    CAknDiallerLauncher* self = new ( ELeave ) CAknDiallerLauncher(aCompaIf);
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CAknDiallerLauncher::CAknDiallerLauncher
// C++ default constructor.
// -----------------------------------------------------------------------------
//
CAknDiallerLauncher::CAknDiallerLauncher(CAknCompaIf*& aCompaIf):
    iCompaIf(aCompaIf)
    {
    }

// -----------------------------------------------------------------------------
// CAknDiallerLauncher::ConstructL
// Symbian 2nd phase constructor.
// -----------------------------------------------------------------------------
//
void CAknDiallerLauncher::ConstructL()
    {
    iKeyFlags = 0;
    }

// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------
//
CAknDiallerLauncher::~CAknDiallerLauncher()
    {
    delete iKeyTimer;
    }

// -----------------------------------------------------------------------------
// CAknDiallerLauncher::SetFlags
// -----------------------------------------------------------------------------
//
void CAknDiallerLauncher::SetFlags( const TInt aFlags )
    {
    iKeyFlags = aFlags;
    }
    
// -----------------------------------------------------------------------------
// CAknDiallerLauncher::OfferKeyEventL
// Returns always EKeyWasNotConsumed
// -----------------------------------------------------------------------------
//
TKeyResponse CAknDiallerLauncher::OfferKeyEventL( 
    const TKeyEvent &aKeyEvent, TEventCode aType )
    {    

    if ( aKeyEvent.iScanCode != EStdKeyYes ) 
        { 
        return EKeyWasNotConsumed;
        }

    if ( iKeyFlags & CAknAppUiBase::EDisableSendKeyLong && 
         iKeyFlags & CAknAppUiBase::EDisableSendKeyShort )
        {
        return EKeyWasNotConsumed;
        }
    
    // Check if autolock is on (if there is a an active call ongoing
    // and sendkey is pressed, keyevent ends up here and must be dismissed
    // to avoid opening dialler)
    CRepository* repository = CRepository::NewL(KCRUidSecuritySettings); 
    
    TInt lockStatus(0);
    TInt lockStatusErr = repository->Get(KSettingsAutolockStatus, lockStatus);
    
    delete repository;
    repository = NULL;
    
    // If lock is on, nothing should be done so we can just return.
    // Also return if status could't be fetched (just in case).
    if ( lockStatus == 1 || lockStatusErr != KErrNone )
        {
        return EKeyWasNotConsumed;
        }

    TInt curVal( 0 );
    TInt err = RProperty::Get( KPSUidStartup, KPSStartupUiPhase, curVal );
    if ( curVal != EStartupUiPhaseAllDone )
        {
        return EKeyWasNotConsumed;
        }

    // if it's alerting & Ringing status, ignore the send key event
    TInt callVal( 0 );
    TInt errCall = RProperty::Get( KPSUidCtsyCallInformation, KCTsyCallState, callVal );
    if ( err == KErrNone  && ( callVal == EPSCTsyCallStateDialling || EPSCTsyCallStateRinging == callVal ) )
        {
        return EKeyWasNotConsumed;
        }
    
    // if it's emerency calls status, ignore the send key event
    TInt emergVal( 0 );
    TInt errEmerg = RProperty::Get( KPSUidCtsyEmergencyCallInfo, KCTSYEmergencyCallInfo, emergVal );
    if ( errEmerg == KErrNone  && emergVal == 1 )
        {
        return EKeyWasNotConsumed;
        }
    
    if ( aType == EEventKeyDown )
        {
        StartKeyTimerL();                
        }

    if ( aType == EEventKeyUp && 
         iKeyTimer && iKeyTimer->IsActive() )
        {
        StopKeyTimer();
        if ( iKeyFlags & CAknAppUiBase::EDisableSendKeyShort )
            {
            return EKeyWasNotConsumed;
            }
                                              
        TBool launch = AknLayoutUtils::PenEnabled();
        // In touch compatibility mode current layout (QVGA) doesn't have
        // pen enabled. But dialler can be launched as it executes in
        // "native" layout where pen is enabled.
        launch = launch || ( iCompaIf && iCompaIf->IsForeground() );
        if ( launch )
            {
            LaunchDiallerL();
            }
        }
    return EKeyWasNotConsumed;
    }    

// -----------------------------------------------------------------------------
// CAknDiallerLauncher::StartKeyTimerL
// Starts the timer for the long press. Timer is constructed when used for the
// first time
// -----------------------------------------------------------------------------
//
void CAknDiallerLauncher::StartKeyTimerL()
    {
    if ( !iKeyTimer )
        {
        iKeyTimer = CPeriodic::NewL( CActive::EPriorityStandard );
        }
    else if ( iKeyTimer->IsActive() )
        {
        iKeyTimer->Cancel();
        }
    iKeyTimer->Start( KAknKeyboardRepeatInitialDelay,
                      KAknKeyboardRepeatInitialDelay, 
                      TCallBack ( ReportLongPressL, this ) );
    }

// -----------------------------------------------------------------------------
// CAknDiallerLauncher::StopKeyTimer
// -----------------------------------------------------------------------------
//
void CAknDiallerLauncher::StopKeyTimer()
    {
    if ( iKeyTimer && iKeyTimer->IsActive() )
        {
        iKeyTimer->Cancel();
        }
    }

// -----------------------------------------------------------------------------
// CAknDiallerLauncher::ReportLongPressL
// -----------------------------------------------------------------------------
//
TInt CAknDiallerLauncher::ReportLongPressL( TAny* aThis )
    {
    CAknDiallerLauncher* self = 
        reinterpret_cast <CAknDiallerLauncher* > ( aThis );
    self->StopKeyTimer();
    if ( iAvkonAppUi->IsForeground() )
        {
        self->LaunchVoiceCommandL();
        }
    return 1; // CPeriodic ignores return value
    }
    
// -----------------------------------------------------------------------------
// CAknDiallerLauncher::LaunchDiallerL
// -----------------------------------------------------------------------------
//
void CAknDiallerLauncher::LaunchDiallerL()
    {
    TVwsViewId diallerView( KPhoneAppUid, KAknDiallerViewUid );
    iAvkonAppUi->CreateActivateViewEventL( diallerView,
                KDiallerVievCommand, KNullDesC8() );
    }

// -----------------------------------------------------------------------------
// CAknDiallerLauncher::LaunchVoiceCommandL
// -----------------------------------------------------------------------------
//    
void CAknDiallerLauncher::LaunchVoiceCommandL()
    {
    if ( iKeyFlags & CAknAppUiBase::EDisableSendKeyLong )
        {
        return;
        }
            
    // Touch compatibility mode
    if (iCompaIf)
        {
        // Voice command launches itself in QHD layout on top of compa-mode
        // application. The screen gets messed up. Compa-mode application is
        // using wserv offset support to switch screen right (center the QVGA
        // application window). When it shows behind another non-offsetting
        // application, the shith is lost and screen is messed up.
        // A workaroundfor for this is to switch idle screen to foreground
        // before voice commander is launched.
        TVwsViewId idleView(KActiveIdle2Uid, KActiveIdleView);
        if (iCompaIf->IsForeground())
            {
            iAvkonAppUi->CreateActivateViewEventL(idleView, KNullUid,
                KNullDesC8());
            }
        }
    
    TApaTaskList apaTaskList( iCoeEnv->WsSession() );
    TApaTask apaTask = apaTaskList.FindApp( KVoiceUiUID );
    
    if ( apaTask.Exists() )
        {
        apaTask.BringToForeground();
        }
    else
        {
    RApaLsSession apa;
    User::LeaveIfError( apa.Connect() );
    CleanupClosePushL( apa );
    CApaCommandLine* cmdLine = CApaCommandLine::NewLC();
    cmdLine->SetExecutableNameL( KVoiceDialApplication );
    cmdLine->SetCommandL( EApaCommandRunWithoutViews );
    User::LeaveIfError( apa.StartApp( *cmdLine ) );
    CleanupStack::PopAndDestroy( 2 ); // cmdLine, apa
        }

    }
    
class CAknAppUiBaseExtension : public CBase
    {
public:
    CAknAppUiBaseExtension();
    TRect iApplicationRect; // Application rect stored inside appui so that we dont need to call wserv methods when someone asks for application rect.
    TInt iDefaultRotation;
    TAknUiZoom iLocalUiZoom;
    TInt iScreenMode;
    TInt iMSKEnabled; //CenRep value cached here
    CTouchFeedbackAdaptation* iFeedbackAdaptation;

    CAknDiallerLauncher* iDiallerLauncher;
    CAknCompaIf* iCompaIf; // touch compatibility mode
    CAknPointerEventModifier* iPointerEventModifier;
    };

CAknAppUiBaseExtension::CAknAppUiBaseExtension()
    : iLocalUiZoom(EAknUiZoomAutomatic), iScreenMode(KAknScreenModeUnset)
    {
    }

EXPORT_C CAknAppUiBase::~CAknAppUiBase()
    {
    if (iAppUiBaseExtension)
        {
        MTouchFeedback::DestroyInstance();
        iAppUiBaseExtension->iFeedbackAdaptation = NULL;
        RemoveFromStack( iAppUiBaseExtension->iDiallerLauncher );
        delete iAppUiBaseExtension->iDiallerLauncher;        
        iAppUiBaseExtension->iDiallerLauncher = NULL;
        delete iAppUiBaseExtension->iCompaIf;
        delete iAppUiBaseExtension->iPointerEventModifier;
        }
    delete iAppUiBaseExtension;
    iAppUiBaseExtension = NULL;
    delete iEventMonitor;
    delete iKeySounds;
    }

EXPORT_C CAknAppUiBase::CAknAppUiBase() : CEikAppUi()
    {
    SetFullScreenApp(ETrue);
    }

EXPORT_C void CAknAppUiBase::HandleForegroundEventL(TBool aForeground)
    {
    CAknSgcClient::SetKeyboardRepeatRate(EAknApplicationDefaulRepeatRate);
    iAknFlags.Clear(EContainerWasForeground);      // no longer need this flag
    iAknFlags.Clear(EContainerWasPartialForeground);       // no longer need this flag
    iAknFlags.Clear(EPartialForeground);           // now either foreground or background

    CEikAppUi::HandleForegroundEventL( aForeground );

    CAknSgcClient::HandleChangeL();
    }

EXPORT_C void CAknAppUiBase::ConstructL()
    {
    // Should Implement
    BaseConstructL(0);
    }

void CAknAppUiBase::SetAppUiAndLeaveIfErrorL( TInt aError )
    {
    if ( aError < KErrNone )
        {
        iContainerAppUi = static_cast<CEikAppUi*>(iEikonEnv->SetAppUi( this ));
        User::Leave( aError );       
        }   
    }

EXPORT_C void CAknAppUiBase::BaseConstructL( TInt aAppUiFlags )
    {
#ifdef AVKON_RDEBUG_INFO
    RDebug::Print(_L("CAknAppUiBase::BaseConstructL()"));
#endif

    // note that the extension may have already been created by some other API call
    // for example SetLocalUiZoomL
        
    if(!iAppUiBaseExtension)
        {
        // To avoid having to test on this extension everywhere, we need to Leave if the alloc fails.
        TRAPD( err,iAppUiBaseExtension = new(ELeave) CAknAppUiBaseExtension);   
        // ensure that CCoeEnv takes ownership before leaving
        SetAppUiAndLeaveIfErrorL( err );
        }

    // enable receipt of changes to screen state
    iEikonEnv->RootWin().EnableScreenChangeEvents();

    iAppUiBaseExtension->iApplicationRect = iCoeEnv->ScreenDevice()->SizeInPixels();
    
    if (!iAppUiBaseExtension->iFeedbackAdaptation )
        {
        iAppUiBaseExtension->iFeedbackAdaptation = CTouchFeedbackAdaptation::NewL();
        }
    
#ifdef AVKON_RDEBUG_INFO
    RDebug::Print(_L("CAknAppUiBase::BaseConstructL() application rect set"));
#endif
    CRepository* repository = NULL;
    TRAPD(ret, repository = CRepository::NewL(KCRUidAvkon));
    if (ret == KErrNone)
        {
        ret = repository->Get(KAknDefaultAppOrientation, iAppUiBaseExtension->iDefaultRotation);
        ret = repository->Get(KAknMiddleSoftkeyEnabled, iAppUiBaseExtension->iMSKEnabled);
        }
#ifdef AVKON_RDEBUG_INFO
    RDebug::Print(_L("CAknAppUiBase::BaseConstructL() orientation ok"));
#endif

    TInt orientationFlags = aAppUiFlags;
    CRepository* defaultOrientationCr = NULL;
    TRAPD( err, defaultOrientationCr = CRepository::NewL( KCRUidDefaultAppOrientation ) );
    if (err == KErrNone)
        {
        // Repository found, check if the orientation has been set
        TInt value = 0;
        err = defaultOrientationCr->Get( RProcess().SecureId().iId, value );
        if( err == KErrNone && value )
            {
            // Application key found and orientation has been set
            orientationFlags = value;
            }
        delete defaultOrientationCr;
        defaultOrientationCr = NULL;
        }
    iAknFlags.Assign(EOrientationSpecified, orientationFlags&EAppOrientationSpecifiedFlag);
    iAknFlags.Assign(EOrientationLandscape, orientationFlags&EAppOrientationLandscapeFlag);
    iAknFlags.Assign(EOrientationAutomatic, orientationFlags&EAppOrientationAutomaticFlag);
    iAknFlags.Assign(EMSKEnabled, aAppUiFlags&EAknEnableMSKflag);
    iAknFlags.Assign( ESingleClickCompatible,
            aAppUiFlags & EAknSingleClickCompatibleFlag );

    if ( aAppUiFlags & EAknTouchCompatibleFlag )
        {
        iAknFlags.Set( ETouchCompatible );
        }
    else
        {
        RProcess process;
        TFileName fileName = process.FileName();
        _LIT(KRomDrive,"z:");
        
        if ( fileName.FindF( KRomDrive ) == 0 )
            {
            iAknFlags.Set( ETouchCompatible );
            }
        }

#ifdef AVKON_RDEBUG_INFO
    RDebug::Print(_L("Entering CEikAppUi::BaseConstructL()"));    
#endif

    // Touch compatibility mode. Change application screen mode before
    // a call to CEikAppUi::BaseConstructL(). This way application
    // starts in a correct screen mode and there are no
    // HandleResourceChangeL() calls due to screen mode change.
    TInt compaScreenMode = KErrNotFound;
    TBool screenModeChanged = EFalse;
    // Check if the application doesn't need compa-mode or compa-mode is
    // disabled
    if (CAknCompaIf::IsNeeded(aAppUiFlags, repository))
        {
        // Compa-mode may be needed. Instantiate ecom plugin to check
        // further. Change application screen mode if compa-mode is needed.
        TBool isConsoleApp;
        TRAPD(compaModeErr,
            iAppUiBaseExtension->iCompaIf = CAknCompaIf::NewL();
            // SetCompaAppScreenModeL() returns KErrNotFound if compa-mode
            // is not needed
            compaScreenMode =
                iAppUiBaseExtension->iCompaIf->SetCompaAppScreenModeL(
                    screenModeChanged, isConsoleApp, aAppUiFlags, *this,
                    *iCoeEnv, *repository));
        delete repository; repository = NULL;
        // Ensure that CCoeEnv takes ownership before leaving
        SetAppUiAndLeaveIfErrorL(compaModeErr);
        if (compaScreenMode == KErrNotFound)
            {
            delete iAppUiBaseExtension->iCompaIf;
            iAppUiBaseExtension->iCompaIf = NULL;
            }
        else
            {
            if (isConsoleApp)
                {
                // If console application is run in compa-mode, allow status
                // bar to be created. Status bar is required to be able to set
                // application screen mode.
                aAppUiFlags &= ~CEikAppUi::ENoScreenFurniture;
                }
            }
        }
    delete repository; repository = NULL;

    CEikAppUi::BaseConstructL( aAppUiFlags );
    
    if ( !iAppUiBaseExtension->iDiallerLauncher )
        {
        iAppUiBaseExtension->iDiallerLauncher =
            CAknDiallerLauncher::NewL(iAppUiBaseExtension->iCompaIf);
        AddToStackL( iAppUiBaseExtension->iDiallerLauncher, -100, 
                     ECoeStackFlagRefusesFocus );
        }

    iAvkonEnv->TransitionEvent(KAknTransitionEventFlags); //look at fullsceen flags

    
#ifdef AVKON_RDEBUG_INFO
    RDebug::Print(_L("CEikAppUi::BaseConstructL() out "));
#endif

    if (iEikonEnv->StartedAsServerApp())
        EnableExternalViewSwitches(EFalse);

    // Note: iKeySounds is left uninitialized  //

    iEventMonitor = CAknWsEventMonitor::NewL();
    
    if(!(aAppUiFlags & EAknExplicitStartupEffectCompletion)) //does start idle time
        iAvkonEnv->TransitionEvent(AknTransEffect::EAppStartComplete);//normal case

    // Touch compatibility mode
    if (iAppUiBaseExtension->iCompaIf)
        {
        // Create compatibility mode keyboard and make it visible in the case
        // of a normal application. Compa-keyboard is also created for servers
        // that display global/notes notifications but left invisible.
        iAppUiBaseExtension->iCompaIf->CreateKbL(compaScreenMode,
            screenModeChanged);
        // Tactile feedback needs to be informed about layout change, because
        // otherwise it won't get correct information about pen support
        // (Tactile Feedback was instantiated earlier in this function, when
        // pen was still enabled).
        iAppUiBaseExtension->iFeedbackAdaptation->LayoutChanged();
        }
    else
        {
        // Pointer event modifier is not needed while in compatibility mode so
        // its creation is delayed until here.
        //
        // Leaves during construction are ignored since pointer event modifier
        // isn't mandatory i.e. the device should be usable also without it.
        TRAP_IGNORE( iAppUiBaseExtension->iPointerEventModifier = CAknPointerEventModifier::NewL() )
        }
    }

EXPORT_C TBool CAknAppUiBase::IsFaded() const
    {
    return CAknSgcClient::IsSystemFaded();
    }

/**
 * Returns the object which allows events to be spyed upon in addition to
 * normal event handling
 */
EXPORT_C CAknWsEventMonitor* CAknAppUiBase::EventMonitor() const
    {
    return iEventMonitor;
    }

EXPORT_C CAknKeySoundSystem* CAknAppUiBase::KeySounds() const
    {
    return iKeySounds;
    }

EXPORT_C void CAknAppUiBase::ReplaceKeySoundsL( TInt aUid )
    {
    delete iKeySounds;
    iKeySounds = NULL;
    iKeySounds = CAknKeySoundSystem::NewL(aUid);
    }

EXPORT_C TTypeUid::Ptr CAknAppUiBase::MopSupplyObject(TTypeUid aId)
    {
    // We give tactile feedback client as object provider for
    // MCoeControlStateObserver interface, so that feedback
    // areas of dimmed and invisible controls can be
    // disabled automatically.
    if ( aId.iUid == MCoeControlStateObserver::ETypeId &&  
         iAppUiBaseExtension && 
         iAppUiBaseExtension->iFeedbackAdaptation )
        {
        return aId.MakePtr( 
            static_cast<MCoeControlStateObserver*>(
                iAppUiBaseExtension->iFeedbackAdaptation ) );
        }
    else
        {
        // Touch compatibility mode. AknCapServer needs access to interface.
       if (aId.iUid == CAknCompaIf::ETypeId)
            {
            CAknCompaIf* compaIf = iAppUiBaseExtension ?
                iAppUiBaseExtension->iCompaIf : NULL;
            return aId.MakePtr(compaIf);
            }
        return CEikAppUi::MopSupplyObject(aId);
        }
    }

EXPORT_C void CAknAppUiBase::SetFullScreenApp(TBool aIsFullScreen)
    {
    iAknFlags.Assign(EFullScreen, aIsFullScreen);
    }

EXPORT_C TBool CAknAppUiBase::IsFullScreenApp() const
    {
    return iAknFlags[EFullScreen];
    }

TBool CAknAppUiBase::IsMSKEnabledApp() const
    {
    return iAknFlags[EMSKEnabled];
    }

EXPORT_C TBool CAknAppUiBase::IsLayoutAwareApp() const
    {
    return ETrue;
    }

EXPORT_C void CAknAppUiBase::SetLayoutAwareApp(TBool /*aLayoutAwareApp*/)
    {
    }

EXPORT_C TBool CAknAppUiBase::IsForeground() const
    {
    return static_cast<CAknAppUiBase*>(iEikonEnv->EikAppUi()) == this && ThreadIsForeground();
    }

EXPORT_C TBool CAknAppUiBase::IsPartialForeground() const
    {
    return iAknFlags[EPartialForeground];
    }

EXPORT_C void CAknAppUiBase::HandleApplicationSpecificEventL(TInt aType,const TWsEvent& aEvent)
/** Handles an application-specific event. 


@param aType The type of the event that occurred. This should be a unique 
identifier constant. 
@param aEvent The window server event that occurred. 
@see CCoeAppUi */
    {
    if (aType == KEikPartialForeground)
        {
        iAknFlags.Set(EPartialForeground);
        iAknFlags.Clear(EContainerWasPartialForeground);       // no longer need this flag
        HandleResourceChangeL(KEikPartialForeground);
        CAknSgcClient::HandleChangeL();
        }
    else if (aType == KEikClearPartialForegroundState)
        {
        iAknFlags.Clear(EPartialForeground);
        CAknSgcClient::HandleChangeL();
        }
    else if (aType == KEikDynamicLayoutVariantSwitch ||
        aType == KEikInputLanguageChange ||
        aType == KAknHardwareLayoutSwitch ||
        aType == KAknLocalZoomLayoutSwitch ||
        aType == KAknILDInstallationLayoutSwitch)
        {
        UpdateSettingCacheAndForwardEventL( aType );
        // Update application rect
        iAppUiBaseExtension->iApplicationRect = iCoeEnv->ScreenDevice()->SizeInPixels();       
        }
    else if ( aType == KEikHasBecomeCurrentAppUiWhileEmbeddedAppUiDeletes )
        {
        TBool thisWasForeground = IsForeground();
        TRAPD(ignore, CAknEnv::Static()->LoadAknLayoutL());
        TRAP(ignore,HandleResourceChangeL(KEikMessageEmbedLevelChange));
        HandleStackedControlsResourceChange(KEikMessageEmbedLevelChange);
        TRAP(ignore, SimulateWsEventL(
            EventForForegroundState(
            IsPartialForeground() || iAknFlags[EContainerWasPartialForeground], 
            thisWasForeground || (iAknFlags[EContainerWasForeground] ) 
            ) ) );
        }
    else if ( aType == KEikNotifyPreCreateEmbeddedL  )
        {
        iAknFlags.Assign(EContainerWasForeground, ThreadIsForeground());
        iAknFlags.Assign(EContainerWasPartialForeground, 
        static_cast<CAknAppUiBase*>(iContainerAppUi)->IsPartialForeground() );
        static_cast<CAknAppUiBase*>(iContainerAppUi)->SimulateWsEventL(EEventFocusLost); // TSOI-56GJ6M
        }
    else if ( aType == KEikNotifyPostCreateEmbeddedL  )
        {
        TWsEvent focusEvent;
        focusEvent.SetType(EventForForegroundState(iAknFlags[EContainerWasPartialForeground], iAknFlags[EContainerWasForeground]));
        iEikonEnv->WsSession().SendEventToWindowGroup(iEikonEnv->RootWin().Identifier(), focusEvent);
        }
    else if ( aType == KEikPostCoeAppUiConstructL  )
        {
        ApplyLayoutChangeL(EFalse);
        iAppUiBaseExtension->iApplicationRect = iCoeEnv->ScreenDevice()->SizeInPixels();
        }
    else if ( aType == KAknShutOrHideApp )
        {
        CAknEnv::ShutOrHideAppL();
        }
    else
        {
        CEikAppUi::HandleApplicationSpecificEventL( aType, aEvent);
        }
    }

EXPORT_C void CAknAppUiBase::HandleScreenDeviceChangedL()
    {
    // By-pass CEikAppUi's call (It would do too-early status pane reload)
    CCoeAppUi::HandleScreenDeviceChangedL();
    UpdateSettingCacheAndForwardEventL(KAknHardwareLayoutSwitch);
    iAppUiBaseExtension->iApplicationRect = iCoeEnv->ScreenDevice()->SizeInPixels();
    }

EXPORT_C void CAknAppUiBase::HandleResourceChangeL(TInt aType)
    {
    if (aType == KEikDynamicLayoutVariantSwitch)
        {
        // update application rect.
        iAppUiBaseExtension->iApplicationRect = iCoeEnv->ScreenDevice()->SizeInPixels();

        // Tactile feedback needs to be informed about new layout, 
        // because pen support may have been changed.   
        if ( iAppUiBaseExtension->iFeedbackAdaptation )
            {
            iAppUiBaseExtension->iFeedbackAdaptation->LayoutChanged();            
            }
        }
    CEikAppUi::HandleResourceChangeL( aType );
    }
    
EXPORT_C TRect CAknAppUiBase::ApplicationRect() const
    {
    TRect rect(iAppUiBaseExtension->iApplicationRect);
    return rect;        
    }
    
EXPORT_C void CAknAppUiBase::PrepareToExit()
/** Performs pre-exit processing to ensure the application will exit cleanly. */
    {
    iAknFlags.Assign(EAppClosing, ETrue);   
    CEikAppUi::PrepareToExit();

    // If this app is dying while in partial foreground, get app beneath to activate its view
/*  if (IsPartialForeground())
    {
        TInt nextWgId = KErrNotFound;
        TRAP_IGNORE(nextWgId = FindAppWgIdBelowMeL());
        if (nextWgId != KErrNotFound)
            {
            TWsEvent event;
            event.SetType(EEventUser);
            *(TApaSystemEvent*)(event.EventData())=EApaSystemEventBroughtToForeground;
            event.SetTimeNow();
            iEikonEnv->WsSession().SendEventToWindowGroup(nextWgId, event);
            }
        }
*/  }

TBool CAknAppUiBase::IsAppClosing() const
    {
    return iAknFlags[EAppClosing];
    }


void CAknAppUiBase::UpdateSettingCacheAndForwardEventL( TInt aEventId )
    {
    CAknEnv* env = iAvkonEnv;
    CAknSettingCache& cache = env->SettingCache();
    TBool changed = cache.Update( aEventId );

    if ( changed || AlwaysForwardEvent(aEventId) )
        {
        TBool reportEvent = ETrue;
        TInt originalEventId = aEventId;
        if (originalEventId == KAknHardwareLayoutSwitch || 
            originalEventId == KAknLocalZoomLayoutSwitch ||
            originalEventId == KAknILDInstallationLayoutSwitch)
            {
            aEventId = KEikDynamicLayoutVariantSwitch; // all layout changes are sent to apps as KEikDynamicLayoutVariantSwitch
            }
            
        if (aEventId == KEikDynamicLayoutVariantSwitch)
            {
            RelinquishPriorityToForegroundAppLC();
            if(originalEventId == KAknILDInstallationLayoutSwitch)
                {
                // always reload the current layout configuration, as we are expecting
                // a change in the actual layout pack instances that will be loaded, 
                // and always report the event to all app uis
                env->ReloadAknLayoutL();
                }
            else
                {
                reportEvent = env->LoadAknLayoutL();
                }
            }
        
        if (reportEvent)
            {
            // report resource changed to all app uis
            for ( CEikAppUi* appUi = iEikonEnv->EikAppUi();
                  appUi;
                  appUi = appUi->ContainerAppUi() )
                {
                appUi->ReportResourceChangedToAppL( aEventId );
                }
            }


        // Unblank screen if screen blanking is done at KEikDynamicLayoutVariantSwitch at aknglobaui side.
        if (IsForeground() && aEventId == KEikDynamicLayoutVariantSwitch)
             {
             RAknUiServer* client = CAknSgcClient::AknSrv();
             if (client && client->Handle())
                client->UnblankScreen();
             }

        if (aEventId == KEikDynamicLayoutVariantSwitch)
            {
            CleanupStack::PopAndDestroy(); // RelinquishPriorityToForegroundAppLC
            }
        }
    }

void CAknAppUiBase::RelinquishPriorityToForegroundAppLC()
    {
    CAknSgcClient::RelinquishPriorityToForegroundAppLC(iAknFlags[EForegroundOrPartialForeground] || IsForeground());
    }

TBool CAknAppUiBase::AlwaysForwardEvent( TInt aEventId )
    {
    switch(aEventId)
        {
        case KAknILDInstallationLayoutSwitch:
            // - If an ILD layout has been installed, then all application layouts 
            //  must be updated
            return ETrue;
        case KAknHardwareLayoutSwitch:
        case KEikDynamicLayoutVariantSwitch:
            // - For non-full screen apps, they need to follow the foreground
            //  application's orientation. 
            return !IsFullScreenApp(); 
        default:
            return EFalse;
        };
    }

EXPORT_C CAknAppUiBase::TAppUiOrientation CAknAppUiBase::Orientation() const
    {
    CAknAppUiBase::TAppUiOrientation orientation = EAppUiOrientationUnspecified;
    if (!iAknFlags[EOrientationSpecified])
        {
        if (iAppUiBaseExtension->iDefaultRotation >= 0 && iAppUiBaseExtension->iDefaultRotation <= 2)
            {
            // Product specific orientation configuration for applications that do not
            // set any orientation flag is done here.
            //
            // Return value:                 orientation
            // EAppUiOrientationUnspecified: Follows device orientation.
            // EAppUiOrientationPortrait:    Applications runs in portrait mode
            // EAppUiOrientationLandscape:   Applications runs in landscape mode
            orientation = (CAknAppUiBase::TAppUiOrientation)iAppUiBaseExtension->iDefaultRotation;
            }        
        }
    else if (iAknFlags[EOrientationAutomatic])
        orientation = EAppUiOrientationUnspecified;
    else if (iAknFlags[EOrientationLandscape])
        orientation = EAppUiOrientationLandscape;
    else
        orientation = EAppUiOrientationPortrait;

    return orientation;
    }

EXPORT_C TBool CAknAppUiBase::OrientationCanBeChanged() const
    {
    // parameters affecting ability to set mode
    TBool isFullScreen = IsFullScreenApp();
    TInt fixedMode = iAppUiBaseExtension ? iAppUiBaseExtension->iScreenMode : KAknScreenModeUnset;

    // Get portrait and landscape screen modes
    CAknLayoutConfig::TScreenMode portraitMode = 
        CAknSgcClient::CalculateScreenMode(isFullScreen, ETrue, EFalse, fixedMode);
            
    CAknLayoutConfig::TScreenMode landscapeMode = 
        CAknSgcClient::CalculateScreenMode(isFullScreen, ETrue, ETrue, fixedMode);
    
    // are the portrait and landscape modes different?
    return portraitMode.ModeNumber() != landscapeMode.ModeNumber();
    }

EXPORT_C void CAknAppUiBase::SetOrientationL(TAppUiOrientation aOrientation)
    {
    if (aOrientation != Orientation())
        {
        iAknFlags.Assign(EOrientationSpecified, aOrientation != EAppUiOrientationUnspecified);
        iAknFlags.Assign(EOrientationLandscape, aOrientation == EAppUiOrientationLandscape);
        iAknFlags.Assign(EOrientationAutomatic, aOrientation == EAppUiOrientationAutomatic);
        ApplyLayoutChangeL(ETrue);
        if(IsForeground())
            {
            RAknUiServer* client = CAknSgcClient::AknSrv();
            if (client && client->Handle())
                {
                client->UnblankScreen();
                }
            }
        }
    }

TBool CAknAppUiBase::ThreadIsForeground() const
    {
    RWsSession& ws = iEikonEnv->WsSession();
    TThreadId focusThreadId;
    ws.GetWindowGroupClientThreadId(ws.GetFocusWindowGroup(), focusThreadId);
    RThread myThread;
    return myThread.Id() == focusThreadId;
    }


// deprecated
TInt CAknAppUiBase::FindAppWgIdBelowMeL()
    {
/*    RWsSession& wsSession=iEikonEnv->WsSession();
    TInt count=wsSession.NumWindowGroups(0);
    CArrayFixFlat<TInt>* wgIds = new (ELeave) CArrayFixFlat<TInt>(count);
    CleanupStack::PushL(wgIds);
    User::LeaveIfError(wsSession.WindowGroupList(0,wgIds));
    count = wgIds->Count();
    TInt nextWgId = KErrNotFound;
    TThreadId nextThreadId;
    TInt myWgId = iEikonEnv->RootWin().Identifier();
    TThreadId myThreadId;
    wsSession.GetWindowGroupClientThreadId(myWgId, myThreadId);
    for (TInt ii=count-1; ii>=0; ii--)
        {
        TInt wgId = wgIds->At(ii);
        if (wgId == myWgId)
            break;
        // only record window groups if they belong to a different thread - prevents sending an event back to this thread
        wsSession.GetWindowGroupClientThreadId(wgId, nextThreadId);
        if (nextThreadId != myThreadId)
            {
            CApaWindowGroupName* wgName = CApaWindowGroupName::NewLC(wsSession, wgId);
            if (wgName->IsAppReady())
                nextWgId = wgId;
            CleanupStack::PopAndDestroy();
            }
        }
    CleanupStack::PopAndDestroy(wgIds);
*/
    return KErrNotSupported; //nextWgId;
    }

/**
 * Simulate a foreground event by passing it straight into HandleWsEventL. 
 * Used for telling embedding app to lose the foreground, part of fix for TSOI-56GJ6M 
 *
 * @param aForeground if EFalse, send to background, otherwise send to foreground
 *
 */
void CAknAppUiBase::SimulateWsEventL(TInt aEventId)
    {
    TWsEvent event;
    event.SetType(aEventId);
    event.SetHandle(0);
    HandleWsEventL(event, NULL);
    }

TInt CAknAppUiBase::EventForForegroundState(TBool aPartialFg, TBool aForeground)
    {
    if (aPartialFg)
        return KEikPartialForeground;
    else if (aForeground)
        return EEventFocusGained;
    else
        return EEventFocusLost;
    }

EXPORT_C void CAknAppUiBase::Exit()
/** Closes the app UI. */
    {
    // Exit() leaves. The app UI is deleted during exit, and processing must stop immediately.
    if (iContainerAppUi)
        {
        delete this;
        User::Leave(KLeaveWithoutAlert);    // stop this event here!
        }
    else
        {
        // default reason for exiting is EEikCmdExit. If server exists,
        // clients must be told. Other exit reasons should be notified
        // before they call Exit().
        CEikAppServer* server = iEikonEnv->AppServer();
        if (server)
            server->NotifyServerExit(EEikCmdExit);
        
        CBaActiveScheduler::Exit();
        }
    }

EXPORT_C void CAknAppUiBase::SetFadedL(TBool aFaded)
    {
    const TInt message=(aFaded? KEikMessageFadeAllWindows : KEikMessageUnfadeWindows);
    TRAPD(ignore, ReportResourceChangedToAppL(message));
    if (IsForeground())
       CAknSgcClient::SetSystemFaded(aFaded);
    TRAP(ignore, ReportResourceChangedToAppL(KEikMessageWindowsFadeChange));
    }

EXPORT_C TAknUiZoom CAknAppUiBase::LocalUiZoom() const
    {
    CAknEnv* env = iAvkonEnv;
    TInt value = EAknUiZoomAutomatic;
    CAknSettingCache& cache = env->SettingCache();
    // get the value from the top plugin
    TInt err = cache.PluginValue(KAknLocalZoomLayoutSwitch, value);
    // if there are no plugins, just use the real local value
    if(err != KErrNone && iAppUiBaseExtension)
        {
        value = iAppUiBaseExtension->iLocalUiZoom;
        }
    return static_cast<TAknUiZoom>(value);
    }

EXPORT_C void CAknAppUiBase::SetLocalUiZoom(TAknUiZoom aZoom)
    {
    TInt err = KErrNone;
    if(!iAppUiBaseExtension)
        {
        // we must have been called by application before their call to BaseConstructL
        // therefore we need to create the extension.
        // if it leaves, BaseConstructL will try to construct the extension again, 
        // and the side effect will be that normal zoom level is incorrectly used.
        TRAP(err, iAppUiBaseExtension = new(ELeave) CAknAppUiBaseExtension());
        }
    if(!err)
        {
        iAppUiBaseExtension->iLocalUiZoom = aZoom;
        }
    }

EXPORT_C void CAknAppUiBase::ApplyLayoutChangeL(TBool aReportChange)
    {
    CAknSgcClient::HandleChangeL();
    if (iAvkonEnv->LoadAknLayoutL())
        {
        if(aReportChange)
            {
            ReportResourceChangedToAppL(KEikDynamicLayoutVariantSwitch);
            }
        }
    }

TBool CAknAppUiBase::HasFullOrPartialForeground() const
    {
    return iAknFlags[EForegroundOrPartialForeground];
    }

void CAknAppUiBase::SetScreenModeL(TInt aModeNumber)
    {
    TInt err = KErrNone;
    if(!iAppUiBaseExtension)
        {
        // we must have been called by application before their call to BaseConstructL
        // therefore we need to create the extension.
        // if it leaves, BaseConstructL will try to construct the extension again, 
        // and the side effect will be that the natural screen mode is used.
        TRAP(err, iAppUiBaseExtension = new(ELeave) CAknAppUiBaseExtension());
        }
    if(!err)
        {
        iAppUiBaseExtension->iScreenMode = aModeNumber;
        // use iEventMonitor's existence to check if this is
        // fully constructed yet. If so, change the layout.
        if (iEventMonitor)
            ApplyLayoutChangeL(ETrue);
        }
    }

TInt CAknAppUiBase::ScreenMode() const
    {
    return iAppUiBaseExtension ?
        iAppUiBaseExtension->iScreenMode :
        KAknScreenModeUnset;
    }

EXPORT_C void CAknAppUiBase::SetKeyEventFlags( const TInt aFlags )
    {
    iAppUiBaseExtension->iDiallerLauncher->SetFlags( aFlags );
    }

EXPORT_C CAknPointerEventModifier* CAknAppUiBase::PointerEventModifier()
    {
    if ( iAppUiBaseExtension )
        {
        return iAppUiBaseExtension->iPointerEventModifier;
        }
        
    return NULL;
    }

EXPORT_C TBool CAknAppUiBase::IsTouchCompatible() const
    {
    return iAknFlags.IsSet( ETouchCompatible );
    }


EXPORT_C TBool CAknAppUiBase::IsSingleClickCompatible() const
    {
    return iAknFlags.IsSet( ESingleClickCompatible )
        && AknLayoutUtils::PenEnabled();
    }


//===============
// class CAknAppUi 
//===============

void CAknAppUi::DecideWsClientBufferSizesL()
    {
    RWsSession &ws = iEikonEnv->WsSession();
    ws.SetMaxBufferSizeL(KAknDefaultWsBufferSize);
    }

EXPORT_C void CAknAppUi::ConstructL()
    {
    // Should implement to catch those who do not implement MyApp::ConstructL()
    // Or ASSERT?
    CAknAppUi::BaseConstructL();
    }

EXPORT_C void CAknAppUi::BaseConstructL(TInt aAppUiFlags)
    {
    // Initialize AppUi-specific skin parameters and skin support
    // Trap errors and leave after BaseConstructL() if any.
    TInt skinParamErr = KErrNone;
    if( (aAppUiFlags&EAknEnableSkinFlag) != 0 )
        {
        TRAP( skinParamErr, AknsUtils::SetAvkonSkinEnabledL( ETrue ) );
        }
    TRAPD( skinErr, AknsUtils::InitSkinSupportL() );
    TRAPD( allocErr, DecideWsClientBufferSizesL() );
    // No leaving function calls before BaseConstructL().
    CAknAppUiBase::BaseConstructL(aAppUiFlags);

    User::LeaveIfError( allocErr );
    User::LeaveIfError( skinParamErr );
    User::LeaveIfError( skinErr );

    // Ensures that embedded applications get the right parameter
    if( (aAppUiFlags&EAknEnableSkinFlag) != 0 )
        {
        AknsUtils::SetAvkonSkinEnabledL( ETrue );
        }

    if( (aAppUiFlags & EAknDisableHighlightAnimationFlag) != 0 )
        {
        AknsUtils::SetAvkonHighlightAnimationEnabledL( EFalse );
        }

#ifdef RD_SCALABLE_UI_V2
    if ( CAknTouchPane* tp = TouchPane() )
        {
        tp->SetObserver( this );
        if ( EventMonitor() )
            {
            EventMonitor()->AddObserverL( tp );
            EventMonitor()->Enable();
            }
        }
#endif

    if (StatusPane())
        StatusPane()->SetObserver(this);

    TInt uid = KErrNotFound;
    if (Application())
        {
        // Only assign uid if an application is present
        // This is true for all Avkon apps, but not for Java MIDP
        uid = Application()->AppDllUid().iUid;
        }

    ReplaceKeySoundsL(uid);

    AddViewDeactivationObserverL(this);

    iAppShutter = CAknAppShutter::NewL(*iEikonEnv, this, &iAppShutter);
    if(!iExtension)
        {
        iExtension = CAknAppUiExtension::NewL();
        }
        
    AddViewActivationObserverL(iExtension);
        
    if (ExitHidesInBackground())
        {
        TBool isBackground = !IsForeground();
        HideApplicationFromFSW(isBackground);
        iExtension->iFlags.Assign(CAknAppUiExtension::EAppIsHiddenInBackground, isBackground);
        }
    }

EXPORT_C void CAknAppUi::HandleTouchPaneSizeChange()
    {    
    }

EXPORT_C void CAknAppUi::HandleStatusPaneSizeChange()
    {
    }

EXPORT_C CAknAppUi::~CAknAppUi()
    {
    if (iExtension)
        {
        RemoveViewActivationObserver(iExtension);
        }

    delete iExtension;
    // embedded apps need to let the shutter live till long enough to handle the app exit leave
    if (iAppShutter)
        iAppShutter->DeleteSelfWhenReady();

    RemoveViewDeactivationObserver(this);

    // Delete skin parameter singleton (if one exists)
    delete CCoeEnv::Static( KAknsAppUiParametersTls );
    }

EXPORT_C CEikStatusPane* CAknAppUi::StatusPane()
    {
    return iEikonEnv->AppUiFactory()->StatusPane();
    }

EXPORT_C void CAknAppUi::ProcessCommandL(TInt aCommand)
    {
    MEikAppUiFactory* appUiFactory = (iEikonEnv)->AppUiFactory();
    ASSERT(appUiFactory);
    if (appUiFactory->Popup())
        ClosePopup();
    else if (appUiFactory->MenuBar())
        StopDisplayingMenuBar();
    // Test for 'options' command
    if (aCommand == EAknSoftkeyOptions)
        {
        appUiFactory->MenuBar()->TryDisplayMenuBarL();
        return;
        }
    if (aCommand == EAknSoftkeyContextOptions)
        {
        appUiFactory->MenuBar()->TryDisplayContextMenuBarL();
        return;
        }
    if (aCommand == EAknCmdExit)
        {
        StopDisplayingPopupToolbar();
        CAknEnv::RunAppShutter();
        return;
        }
    if ( aCommand != EEikCmdCanceled )
        HandleCommandL(aCommand);
    }

EXPORT_C CEikButtonGroupContainer* CAknAppUi::Cba()
    {
    return iEikonEnv->AppUiFactory()->ToolBar();
    }

EXPORT_C void CAknAppUi::HandleErrorL(TInt aError, HBufC** aErrorDesc, TBool aShowNote )
    {
    // Lets Create TextResolver instance for error resolving
    CTextResolver* textresolver = CTextResolver::NewLC(); 

    TUint flags( 0 ); 
    TInt id( 0 );

    // Resolve the Error
//    TBuf<KErrorResolverMaxTextLength> errorstring = 
    if (!aErrorDesc)
        User::Leave(KErrNotSupported);
    
    // This is nasty, we alloc memory for error handling -> KErrNoMemory might fail
    // Anyway, it will be handled in eikon env, so we can allow this fail
    *aErrorDesc  = 
        textresolver->ResolveErrorString( aError, id, flags, CTextResolver::ECtxNoCtx ).AllocL();

    if ( flags & EErrorResOOMFlag || (*aErrorDesc)->Length() == 0 )
        {
        User::Leave(KErrNoMemory); // let EikEnv preallocated error handling take care of showing note.
        }

    if ( !(flags & ETextResolverBlankErrorFlag) )
        {
        // There is no need create Note before we know that error will displayed i.e. is not blank
        CAknGlobalNote* note = 0;        

        if (aShowNote)
            {
            note = CAknGlobalNote::NewL();
            CleanupStack::PushL( note );                                                         
            }

        TText contextChar = ((*aErrorDesc)->Des())[0]; // this is a colon

        // remove context character and line end character
        (*aErrorDesc)->Des().Delete( 0, 2 );

        // Solving the application name asing AppArc.lib
        RApaLsSession apparcSession;
        User::LeaveIfError( apparcSession.Connect() );
        CleanupClosePushL( apparcSession );
        TApaAppInfo appInfo;
        TInt err = apparcSession.GetAppInfo( appInfo, this->Application()->AppDllUid() );
        
        // +2 for colon and line end
        HBufC* captionBuffer = 
            HBufC::NewLC( KApaMaxAppCaption + KAknBidiExtraSpacePerLine + 2 ); 

//        CleanupStack::PushL( captionBuffer );
        TPtr caption = captionBuffer->Des();

        if ( err == KErrNone )
            {
            caption = appInfo.iCaption;
            }

        // Lets remove trailing spaces
        caption.TrimRight();
        
        // Insert the application name into the beginning of the error string
        if ( caption.Length() != 0 ) 
            {
            HBufC* result = HBufC::NewLC((*aErrorDesc)->Des().MaxLength() + 5 * (KAknBidiExtraSpacePerLine + 1)); // wasting more memory ...

            CArrayFix<TInt>* lineWidthArray =
                new( ELeave ) CArrayFixFlat<TInt>( 4 );

            CleanupStack::PushL( lineWidthArray );
            
            TRect mainPane;
            AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EPopupParent, mainPane );
            
            const TInt lineVariety( 2 ); // Equals 5 lines, which adapt. layer uses here.
            
            AknLayoutUtils::TAknCbaLocation cbaLocation( AknLayoutUtils::CbaLocation() );
            TInt softkeyVariety( lineVariety ); // Defaults to bottom cbalocation value
    
            // Modify the softkeyVariety in case cba is at either side
            if ( cbaLocation == AknLayoutUtils::EAknCbaLocationRight )
                {
                softkeyVariety += 3;
                }
            else if ( cbaLocation == AknLayoutUtils::EAknCbaLocationLeft )
                {
                softkeyVariety += 6;
                }           
            
            TAknLayoutRect popupLayoutRect;
            popupLayoutRect.LayoutRect( mainPane,
                AknLayoutScalable_Avkon::popup_note_window( softkeyVariety ) );
            
            TRect popupRect = popupLayoutRect.Rect();
            
            TAknLayoutText firstLineLayoutText;
            firstLineLayoutText.LayoutText( popupRect,
                AknLayoutScalable_Avkon::popup_note_window_t1( lineVariety ) );

            const CFont* font = firstLineLayoutText.Font();
            
            TAknLayoutText textRect;
            TAknTextComponentLayout textLayout;
            
            for ( TInt i = 1; i <= 4; ++i )
                {
                textLayout = AknLayoutScalable_Avkon::popup_note_window_t( i, lineVariety );
                textRect.LayoutText( popupRect, textLayout.LayoutLine() );
                lineWidthArray->AppendL( textRect.TextRect().Width() );
                }

            TPtr ptr = result->Des();

            // convert error string to visual order
            AknBidiTextUtils::ConvertToVisualAndWrapToStringL(
                (*aErrorDesc)->Des(),
                *lineWidthArray,
                *font,
                ptr,
                ETrue ); // insert truncation char if doesn't fit

            CleanupStack::PopAndDestroy(); // lineWidthArray

            // in visual order now
            CleanupStack::Pop(); // result
            delete *aErrorDesc;
            *aErrorDesc = result; // ownership to caller

            // add the caption

            TInt captionLength = firstLineLayoutText.TextRect().Width() - 
                font->CharWidthInPixels( contextChar );

            // Here we truncate the application name to fit in the first row of the note
            AknBidiTextUtils::ConvertToVisualAndClipL(
                caption,
                *font,
                captionLength,
                captionLength );

            TBuf<1> buf;
            buf.Append( contextChar );

            // in mirrored layout, ':' is the leftmost character
            if ( AknLayoutUtils::LayoutMirrored() )
                {
                caption.Insert( 0, buf );
                }
            // in non-mirrored layout, ':' is the rightmost character
            else
                {
                caption.Append( buf );
                }

            caption.Append( '\n' );

            // Insert caption row, in visual order.
            // The line end after it exists in string already.
            (*aErrorDesc)->Des().Insert( 0, caption );
            }
        if ( note )
            {
            if ( aError == KErrDiskFull ) 
                {
                note->SetSoftkeys(R_AVKON_SOFTKEYS_OK_EMPTY__OK);
                }

            // If there was a caption, we processed the text ourselves
            if ( caption.Length() )
                {
                note->SetTextProcessing( EFalse );
                }


            // secondary display needs to be informed about the error note
            SAknIntegerUpdate s = 
                {
                EAknTrappedError,
                aError 
                };
            TPckg<SAknIntegerUpdate> pck(s);
            CAknSDData* sdData = CAknSDData::NewL( KAknSecondaryDisplayCategory, EAknErrorNote, pck );
            note->SetSecondaryDisplayData( sdData );
                
            // Finally, let's show the global note
            note->ShowNoteL( EAknGlobalErrorNote, (*aErrorDesc)->Des() ); 

            CleanupStack::PopAndDestroy( 3 ); // note, apparcSession, captionBuffer
            }
        else
            {
            CleanupStack::PopAndDestroy( 2 ); // apparcSession, captionBuffer
            }
        }
    else 
        { 
        (*aErrorDesc)->Des().Zero(); // make text lenght 0 if error is blank
        }

    CleanupStack::PopAndDestroy(); // error resolver
    }

EXPORT_C TErrorHandlerResponse CAknAppUi::HandleError(TInt aError, 
                                                      const SExtendedError& /*aExtErr*/,  
                                                      TDes& /*aErrorText*/, 
                                                      TDes& /*aContextText*/ )
    {
    HBufC* buf = 0;
    TRAPD(err, HandleErrorL(aError, &buf));
    delete buf;
    
    if ( !err )
        {
        return(ENoDisplay); // Error handled proper way.
        }
    
    return(EErrorNotHandled); // Error not handled, let EIKENV handle the error.
    }

EXPORT_C void CAknAppUi::HandleSystemEventL(const TWsEvent& aEvent)
    {
    switch (*(TApaSystemEvent*)(aEvent.EventData()))
        {
    case EApaSystemEventShutdown:
        if((static_cast<CEikonEnv*>(iCoeEnv)->IsSystem()))
            {
            break;
            }
        // else fall-through
    case EApaSystemEventSecureShutdown:
        StopDisplayingPopupToolbar();
        CAknEnv::RunAppShutter();
        break;
    default:
        CEikAppUi::HandleSystemEventL(aEvent);
        break;
        }
    }

EXPORT_C void CAknAppUi::Reserved_MtsmPosition()
    {
    }

EXPORT_C void CAknAppUi::Reserved_MtsmObject()
    {
    }

EXPORT_C void CAknAppUi::HandleForegroundEventL(TBool aForeground)
    {
#ifdef RD_SCALABLE_UI_V2
    TVwsViewId viewId;
    TInt err = GetActiveViewId( viewId );
    if ( ( err == KErrNotFound || viewId.iAppUid == viewId.iViewUid ) && CurrentFixedToolbar() )
        {
        CurrentFixedToolbar()->HandleResourceChange( KAknToolbarSetVisible ); 
        }
#endif 
    if ( KeySounds() && IsForeground() ) // IsForeground() used because aForeground may already be out of date
        {
        KeySounds()->BringToForeground();
        }

#ifdef RD_SCALABLE_UI_V2
    if ( TouchPane() && aForeground )
        {
        TouchPane()->RefreshL();
        }

    if ( !aForeground )
        {  
        HandleStackedControlsResourceChange(KAknMessageFocusLost);            
        }
#endif

    if (aForeground && iExtension->iFlags[CAknAppUiExtension::EAppIsHiddenInBackground])
        {
        HideApplicationFromFSW(EFalse);
        iExtension->iFlags.Clear(CAknAppUiExtension::EAppIsHiddenInBackground);
        }
        
    CEikAppUi::HandleForegroundEventL(aForeground);
    }

EXPORT_C void CAknAppUi::HandleViewDeactivation(const TVwsViewId& /*aViewIdToBeDeactivated*/, const TVwsViewId &/*aNewlyActivatedViewId*/)
    {
    iAvkonEnv->CloseAllIntermediateStates();
    }

EXPORT_C void CAknAppUi::PrepareToExit()
    {
    if( IsForeground() && Document() )
        {
        //only if focused, otherwise next app HandleForeground may never come.
        iAvkonEnv->TransitionEvent(AknTransEffect::EApplicationExit, Application()->AppDllUid());
        }
    else
        {
        iAvkonEnv->TransitionEvent(AknTransEffect::EApplicationExit);
        }
        
    if ( StatusPane() )
        {
        StatusPane()->PrepareForAppExit();
        }
    CAknAppUiBase::PrepareToExit();
    }

EXPORT_C void CAknAppUi::RunAppShutter()
    {
    if (!iAppShutter)
        {
        // the app shutter may not exist if a previous shut attempt failed,
        // eg because KLeaveExit was trapped, or the app did not call Exit() in response to EEikCmdExit.
        TRAP_IGNORE(iAppShutter = CAknAppShutter::NewL(*iEikonEnv, this, &iAppShutter));
        }
        
    if (iAppShutter)
        iAppShutter->Start();
    }

EXPORT_C TBool CAknAppUi::IsAppShutterRunning() const
    {
    return iAppShutter ? iAppShutter->IsActive() : EFalse;
    }

TBool CAknAppUi::IsAppHiddenInBackground() const
    {
    return iExtension && iExtension->iFlags[CAknAppUiExtension::EAppIsHiddenInBackground];
    }

EXPORT_C void CAknAppUi::HandleWsEventL(const TWsEvent& aEvent,CCoeControl* aDestination)
    {
    iAvkonEnv->TransitionEvent(KAknTransitionEventAvkon); 
    if (EventMonitor() && EventMonitor()->IsEnabled())
        {
        EventMonitor()->HandleWsEventL(aEvent,aDestination);
        }
    
    TInt eventType = aEvent.Type();
    // block these two here to avoid any extra execution beneath avkon level
    if (eventType == KAknFullOrPartialForegroundLost ||
        eventType == KAknFullOrPartialForegroundGained )
        {
        iAknFlags.Assign(EForegroundOrPartialForeground, eventType == KAknFullOrPartialForegroundGained);
        return;
        }

    // This method call practically adds a shift modifier to hash key + joystick events.
    // This is because of marking in lists and editors when edit there is no edit key in device.
    if (SimulateHashKeyMarkingEvent(aEvent))
        {
        return;
        }

    // ---- To turn on key code conversion by default -----            
    // must be done before passing to base classes
    if (eventType == EEventKey && iExtension && !iExtension->iFlags[CAknAppUiExtension::ESimulatingEvent])
        {
        TKeyEvent key = *(aEvent.Key());
        TUint code = key.iCode;
        
        GetAliasKeyCodeL(key.iCode, key, EEventKey);
            
        // if key conversion returned something different from original                  
        if (code != key.iCode)
           {
           iExtension->iFlags.Set(CAknAppUiExtension::ESimulatingEvent);
           TRAPD(err, iCoeEnv->SimulateKeyEventL(key, EEventKey));
           iExtension->iFlags.Clear(CAknAppUiExtension::ESimulatingEvent);
           User::LeaveIfError(err);
                
           return; // block handling of this event.         
           }
        }
        
#ifdef RD_SCALABLE_UI_V2
    if ( eventType == EEventPointer )        
        {
        if ( PointerEventModifier() )
            {
            PointerEventModifier()->HandlePointerEvent( *aEvent.Pointer(), aDestination );
            }

        if ( aEvent.Pointer()->iType == TPointerEvent::EButton1Down )
            {                       
            if ( iExtension )
                {
                iExtension->iFlags.Clear(CAknAppUiExtension::EFocusLost);
                }
            
            CAknToolbar* toolbar = CurrentPopupToolbar();
            
            // Non-focusing toolbar takes focus away from its embedded editor
            // or other component control if a control other than toolbar is 
            // tapped. Focus is not removed if the tapped control is CBA, 
            // touchpane or a non-fullscreen dialog.
            if ( toolbar && toolbar->IsShown() && toolbar != aDestination )
                {
                if ( TouchPane() != aDestination )
                    {
                    CEikDialog* dlg = aDestination->MopGetObject( dlg );
                    
                    TBool focusLost = ETrue;
                    
                    if ( dlg )
                        {
                        TInt flags = dlg->DialogFlags();
                        
                        if ( flags != EEikDialogFlagFillScreen &&
                             flags != EEikDialogFlagFillAppClientRect )
                            {
                            focusLost = EFalse;
                            }
                        }
                    else
                        {
                        CEikCba* cba = aDestination->MopGetObject( cba );
                        
                        if ( cba == aDestination )
                            {
                            focusLost = EFalse;
                            }
                        }
                    
                    if ( focusLost )
                        {
                        toolbar->PrepareForFocusLossL(); 
                        }
                    }
                }
            }     
        else if ( iExtension && iExtension->iFlags[CAknAppUiExtension::EFocusLost] )
            {
            aDestination->IgnoreEventsUntilNextPointerUp();
            iExtension->iFlags.Clear(CAknAppUiExtension::EFocusLost);
            }                
        }
#endif // RD_SCALABLE_UI_V2        




    if ( eventType == EEventPointer && iExtension &&
        aEvent.Pointer()->iType == TPointerEvent::EButton1Up )
        {
        iExtension->iDisabledScanCode = -1; 
        }
        



    if (!iDumpNextControl)
        {
        CAknAppUiBase::HandleWsEventL(aEvent, aDestination);    
        }
    switch (eventType)
        {
        case EEventFocusGained:
            UpdateKeyBlockMode();
            GfxTransEffect::Enable();
            iAvkonEnv->TransitionEvent(AknTransEffect::EApplicationActivate);
            if (iExtension)
                {
#ifdef RD_SCALABLE_UI_V2
                iExtension->iFlags.Clear(CAknAppUiExtension::EFocusLost);
#endif                         
                }
            break;
        case EEventFocusLost:
            if (iExtension)
                {
                iExtension->iFlags.Clear(CAknAppUiExtension::EHashKeyDown);
                    
#ifdef RD_SCALABLE_UI_V2
                iExtension->iFlags.Set(CAknAppUiExtension::EFocusLost);
#endif                         
                }
                
            break;          
        case EEventKey:
            {
            TKeyEvent* key = aEvent.Key();
            
            TInt disabledScanCode = iExtension ? iExtension->iDisabledScanCode : -1;
            
            if ( key->iRepeats && KeySounds() && key->iScanCode != disabledScanCode )
                {
                KeySounds()->PlaySound(*key);
                }
            
                
#ifdef _DEBUG
            if (key->iCode == CTRL('i') && (key->iModifiers&EAllStdModifiers)==EAllStdModifiers)
                {
                iDumpNextControl = ETrue;
                }
#endif
            // Launch help application.
            if (key->iCode == EKeyHelp && !key->iRepeats)
                {
                // Some applications do not handle EAknCmdHelp, but define their own command.
                // So first check if help context is available.
                CArrayFix<TCoeHelpContext> *helpContext = iEikonEnv->EikAppUi()->AppHelpContextL();
                if ( helpContext && helpContext->Count())
                    {
                    // Help context is available, launch help directly from here.
                    // Still need to check if stuff from ProcessCommandL's beginning is needed
                    // (eg. close menu & pop-up's) or are they handled by focus lost/gain.
                    HlpLauncher::LaunchHelpApplicationL(iEikonEnv->WsSession(), helpContext);   
                    return;
                    }
                else
                    {
                    // Help context was not available. App either does not support help
                    // or creates the context manually. Send EAknCmdHelp to the application.
                    // This will work if the application handles EAknCmdHelp instead of defining
                    // its own command for help. If the app didn't return help context and does
                    // not handle EAknCmdHelp, we can not launch help.
                    ProcessCommandL(EAknCmdHelp);
                    return;
                    }
                }
            break;
            }
#ifdef _DEBUG
        case EEventPointer:
            {
            if (iDumpNextControl)
                {
                iDumpNextControl = EFalse;
                RDebug debug;
                DumpControl(aDestination, 0, debug);
                }
            break;
            }
#endif
        case KUidValueAknsSkinChangeEvent:
            {
            RelinquishPriorityToForegroundAppLC();
            
            HandleResourceChangeL(KAknsMessageSkinChange);
            HandleStackedControlsResourceChange(KAknsMessageSkinChange);

            // Pass the event to container AppUi in case we are embedded
            CEikAppUi* container = ContainerAppUi();
            if (container)
                {
                container->HandleResourceChangeL(KAknsMessageSkinChange);
                container->HandleStackedControlsResourceChange(KAknsMessageSkinChange);
                }
            
            CleanupStack::PopAndDestroy();  // RelinquishPriorityToForegroundAppLC
            break;
            }

        case KAknUidValueEndKeyCloseEvent:
            {
            CEikonEnv* env = iEikonEnv;
            if ( env && !env->IsSystem() ) // System apps are not closed
                {
                // Close or hide the application.
                TWsEvent event;
                event.SetType( KAknShutOrHideApp );
                event.SetTimeNow();
                CAknAppUiBase::HandleWsEventL( event, aDestination );
                }
            break;
            }


        default:
            break;
        }
        
    }
    
// This method watches for hash key presses, and adds a shift modifier to all arrow key 
// and ok key events, if hash key is simultaneously down. This is done because of making the 
// edit key optional in the device. Therefore, hash key with joystick (or single hash press, 
// see eiklbx.cpp) can be used for marking in lists and editors.    
TBool CAknAppUi::SimulateHashKeyMarkingEvent(const TWsEvent& aEvent)
    {
    TInt eventType = aEvent.Type();        
        
    if (iExtension && 
        iExtension->iFlags[CAknAppUiExtension::EHashKeyMarking] &&
        (eventType == EEventKeyDown || eventType == EEventKeyUp || eventType == EEventKey) &&
        !iExtension->iFlags[CAknAppUiExtension::ESimulatingEvent])
        {
        TKeyEvent key = *(aEvent.Key());
        
        if (eventType == EEventKeyDown && key.iScanCode == EStdKeyHash)
            {
            iExtension->iFlags.Set(CAknAppUiExtension::EHashKeyDown);
            }
        else if (eventType == EEventKeyUp && key.iScanCode == EStdKeyHash)
            {
            iExtension->iFlags.Clear(CAknAppUiExtension::EHashKeyDown);
            }
        else if (iExtension->iFlags[CAknAppUiExtension::EHashKeyDown] && eventType == EEventKey && 
            (key.iCode == EKeyUpArrow    || 
             key.iCode == EKeyDownArrow  || 
             key.iCode == EKeyLeftArrow  || 
             key.iCode == EKeyRightArrow ||
             key.iCode == EKeyOK))
            {
            // Fetch the qwerty mode status from pubsub. No error handling needed.
            TBool qwertyMode = EFalse;    
            iExtension->iQwertyModeStatusProperty.Get(qwertyMode);                        
                
            if (!qwertyMode)
                {
                TKeyEvent keyEvent;
                keyEvent.iCode = key.iCode;
                keyEvent.iScanCode = key.iScanCode;
                keyEvent.iRepeats = key.iRepeats;
                keyEvent.iModifiers = key.iModifiers|EModifierShift;  // Adds shift.
                 
                iExtension->iFlags.Set(CAknAppUiExtension::ESimulatingEvent);
                TRAPD(err, iCoeEnv->SimulateKeyEventL(keyEvent, EEventKey));          
                iExtension->iFlags.Clear(CAknAppUiExtension::ESimulatingEvent);
                User::LeaveIfError(err);
                
                return ETrue; // block handling of this event.   
                }
            }            
        }
        
    return EFalse;          
    }

EXPORT_C void CAknAppUi::SetKeyBlockMode(TAknKeyBlockMode aMode)
    {
    iBlockMode = aMode;
    UpdateKeyBlockMode();
    }


void CAknAppUi::UpdateKeyBlockMode()
    {
    CAknSgcClient::SetKeyBlockMode((TAknKeySoundOpcode)iBlockMode);
    }

#ifdef _DEBUG
const TInt KDumpIndentWidth = 2;

class CPublicCCoeControl : public CCoeControl
    {
public:
    TInt CountComponentControls() const { return 0; }
    CCoeControl* ComponentControl(TInt /*aIndex*/) const { return 0; }
    };

void CAknAppUi::DumpControl(CCoeControl* aControl, TInt aLevel, RDebug& aDebug)
    {
    TInt indent = KDumpIndentWidth * aLevel;
    aDebug.Print(_L("%*cAddress = (CCoeControl*)0x%08x"), indent, ' ', aControl);

    _LIT(KDumpIs, "is");
    _LIT(KDumpHas, "has");
    _LIT(KDumpNo, "no");
    _LIT(KDumpNot, "not");
    aDebug.Print(_L("%*c%S visible, %S dimmed, %S focused, %S border, %S focusable, %S window owning"), indent, ' ', 
        aControl->IsVisible() ? &KDumpIs : &KDumpNot,
        aControl->IsDimmed() ? &KDumpIs : &KDumpNot,
        aControl->IsFocused() ? &KDumpIs : &KDumpNot,
        aControl->HasBorder() ? &KDumpHas : &KDumpNo,
        aControl->IsNonFocusing() ? &KDumpNot : &KDumpIs,
        aControl->OwnsWindow() ? &KDumpIs : &KDumpNot
        );

    TPoint pos = aControl->PositionRelativeToScreen();
    TRect rect = aControl->Rect();
    aDebug.Print(_L("%*cscreen pos = (%d,%d)   top left = (%d,%d)   bottom right = (%d,%d)   size = (%d,%d)"),
        indent, ' ', pos.iX, pos.iY, rect.iTl.iX, rect.iTl.iY,
        rect.iBr.iX, rect.iBr.iY, rect.Width(), rect.Height());

    CPublicCCoeControl* pub = reinterpret_cast<CPublicCCoeControl*>(aControl);
    TInt count = pub->CountComponentControls();
    aDebug.Print(_L("%*c%d sub control(s)"), indent, ' ', count);
    for (TInt ii=0; ii<count; ii++)
        {
        aDebug.Print(_L("%*csub control %d:"), indent, ' ', ii);
        DumpControl(pub->ComponentControl(ii), aLevel+1, aDebug);
        }
    }

#endif

EXPORT_C void CAknAppUi::HideApplicationFromFSW(TBool aHide)
    {
    RAknUiServer* client = CAknSgcClient::AknSrv();
    if ( client && client->Handle())
        {
        client->HideApplicationFromFsw(aHide, Application()->AppDllUid().iUid);
        }
    else 
        {
        // if CAknSgcClient connection to capserver client
        // is not available, make a new connection
        RAknUiServer cap;
        cap.HideApplicationFromFsw(aHide, Application()->AppDllUid().iUid);
        cap.Close();
        }
    }

EXPORT_C CAknTouchPane* CAknAppUi::TouchPane()
    {
#ifdef RD_SCALABLE_UI_V2  
    return static_cast<CEikAppUiFactory*>(iEikonEnv->AppUiFactory())->TouchPane();
#else
    return NULL;
#endif
    }

EXPORT_C CAknToolbar* CAknAppUi::PopupToolbar() const
    {
    return static_cast<CEikAppUiFactory*>(iEikonEnv->AppUiFactory())->PopupToolbar();
    }
    
EXPORT_C CAknToolbar* CAknAppUi::CurrentPopupToolbar() const
    {
    return static_cast<CEikAppUiFactory*>(iEikonEnv->AppUiFactory())->CurrentPopupToolbar();
    }

EXPORT_C CAknToolbar* CAknAppUi::CurrentFixedToolbar() const
    {
    return static_cast<CEikAppUiFactory*>(iEikonEnv->AppUiFactory())->CurrentFixedToolbar();
    }

    
EXPORT_C void CAknAppUi::StopDisplayingPopupToolbar()
    {
    if (CurrentPopupToolbar())
        {
        CurrentPopupToolbar()->SetToolbarVisibility( EFalse );
        }
    if (PopupToolbar())
        {
        PopupToolbar()->SetToolbarVisibility( EFalse );
        }
    }

EXPORT_C void CAknAppUi::GetAliasKeyCodeL(TUint& aCode, const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    if (iExtension && iExtension->iAknAliasKeyCodeResolver)
        {
        User::LeaveIfError(iExtension->iAknAliasKeyCodeResolver->GetAliasKeyCode(aCode,aKeyEvent,aType));
        return;
        }
        
    aCode = aKeyEvent.iCode;
    RAknUiServer* cap = CAknSgcClient::AknSrv();
    if (cap && cap->Handle())
        {
        User::LeaveIfError(cap->GetAliasKeyCode(aCode, aKeyEvent, aType));        
        }
    }

EXPORT_C void CAknAppUi::SetAliasKeyCodeResolverL(MAknAliasKeyCodeResolver* aResolver)
    {
    if(!iExtension)
        {
        iExtension = CAknAppUiExtension::NewL();
        }
    iExtension->iAknAliasKeyCodeResolver = aResolver;
    }
    
    

EXPORT_C TInt32 CAknAppUi::CaptureKey(TUint aKeycode, TUint aModifierMask, TUint aModifier)
    {
    TInt err = KErrNone;
    TInt32 handle = 0;
    TRAP(err, CaptureKeyL(aKeycode, aModifierMask, aModifier, handle));
    
    if (err != KErrNone)
        {
        return err;
        }
        
    return handle;  
    }
    
    
EXPORT_C void CAknAppUi::CaptureKeyL(TUint aKeycode, TUint aModifierMask, TUint aModifier, TInt32& aHandle)
    {   
    TBool qwertyOn = EFalse;    
    User::LeaveIfError(RProperty::Get(KCRUidAvkon, KAknQwertyInputModeActive, qwertyOn));
    
    RWindowGroup& group = iCoeEnv->RootWin();       
    
    if (qwertyOn)   
        {           
        RArray<TPtiNumericKeyBinding> numMaps;
        CPtiEngine* pti = NULL;     
                
        CAknSettingCache& settingsCache = CAknEnv::Static()->SettingCache();
    
        pti = CPtiEngine::NewL();
        CleanupStack::PushL(pti);
                
        pti->GetNumericModeKeysForQwertyL(settingsCache.InputLanguage(), numMaps);
        
        TPtiKey starScanCode = (TPtiKey)0;  
        TInt i = 0;     
        for (; i < numMaps.Count(); i++)
            {
            if (numMaps[i].iChar == '*')     
                {
                starScanCode = numMaps[i].iKey;
                break;
                }                               
            }
                
        if (starScanCode)
            {
            CPtiCoreLanguage* lang = static_cast<CPtiCoreLanguage*>(pti->GetLanguage(ELangEnglish));
            if (lang)
                {
                CPtiQwertyKeyMappings* qmap = static_cast<CPtiQwertyKeyMappings*>(lang->GetQwertyKeymappings());
                if (qmap)
                    {   
                    TBuf<50> keyData;
                    qmap->GetDataForKey(starScanCode, keyData, numMaps[i].iCase);
                    if (keyData.Length())                       
                        {
                        aKeycode = keyData[0];
                        }
                    else
                        {
                        User::Leave(KErrNotFound);
                        }                           
                    }                                                       
                }                                                               
            }
                    
        CleanupStack::PopAndDestroy(); // pti
        numMaps.Close();            
        }
                    
    aHandle = group.CaptureKey( aKeycode, aModifierMask, aModifier );           
    User::LeaveIfError(aHandle);
    }
     
EXPORT_C TBool CAknAppUi::ExitHidesInBackground() const
    {
    TBool hide = EFalse;
    if (!iEikonEnv->StartedAsServerApp())
        TRAP_IGNORE(hide = ExitHidesInBackgroundL());
    return hide;
    }
    
TBool CAknAppUi::ExitHidesInBackgroundL() const
    {
    // Detect whether or not the application should attempt a fake exit. 
    // Configuration is through a cenrep keyspace listing the application UIDs which should fake exit.
    CEikApplication* app = Application();
    if (!app)
        return EFalse;
    TInt uid = app->AppDllUid().iUid;
    CRepository* repository = CRepository::NewLC(KCRUidLeaveAppsInMemory);
    RArray<TUint32> keys;
    repository->FindEqL(KLeaveAppsInMemoryAppListKeyRange,
                        KLeaveAppsInMemoryAppListKeyMask,
                        uid,
                        keys);
    TBool hide = keys.Count() != 0;
    keys.Close();
    CleanupStack::PopAndDestroy(repository);
    return hide;
    }
    
EXPORT_C void CAknAppUi::HideInBackground()
    {
  /*
  Call EApplicationExit effect start here since for the user hiding app in background
  is still exiting an app. So this call changes the application switch effect to an application 
  exit effect.
  */
  CEikApplication* app = Application();

    const TInt focusWGroupId = iEikonEnv->WsSession().GetFocusWindowGroup();
    const TInt thisApplicationWgId = iEikonEnv->RootWin().Identifier();

    if ( focusWGroupId == thisApplicationWgId )
        {
        GfxTransEffect::BeginFullScreen( AknTransEffect::EApplicationExit, TRect(),
        AknTransEffect::EParameterType, AknTransEffect::GfxTransParam( app->AppDllUid() ) );
        }

    // Hide the application in the background. 
    // This performs the push-to-background and hide-from-FSW operations necessary to make the application look as if it has exited.
    HideApplicationFromFSW(ETrue);
    iExtension->iFlags.Set(CAknAppUiExtension::EAppIsHiddenInBackground);
    CAknSgcClient::MoveApp(iEikonEnv->RootWin().Identifier(), ESgcMoveAppToBackground);
    }
    
    
EXPORT_C void CAknAppUi::DisableNextKeySound( TInt aScanCode )
    {
    if ( iExtension )
        {
        iExtension->iDisabledScanCode = aScanCode;
        }
    if ( KeySounds() )
        {
        KeySounds()->DisableNextKeySound( aScanCode );
        }
    }

// End of File

