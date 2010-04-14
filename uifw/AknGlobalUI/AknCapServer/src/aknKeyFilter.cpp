/*
* Copyright (c) 2005-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Translates key events for different UI related situations.
*
*/


// INCLUDE FILES
#include <barsread.h>
#include <apgwgnam.h>
#include <e32property.h>
#include <UikonInternalPSKeys.h>    // KUikLayoutState, KUikFlipStatus
#include <AvkonInternalCRKeys.h>    // KAknQwertyInputModeActive
#include <eikpriv.rsg>
#include <AknDef.h>
#include <AknSgcc.h>
#include <aknenv.h>
#include <AknFepInternalPSKeys.h>
#include <AknFepGlobalEnums.h>
#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikenvinterface.h>
#endif


#include <AknSettingCache.h>
#include <AknLayoutConfig.h>

#include "AknKeyFilter.h"
#include <AknTaskList.h>
#include <aknconsts.h>

#include <gfxtranseffect/gfxtranseffect.h>
#include "akntranseffect.h" // for Transition effect enumerations
#include <hwrmdomainpskeys.h>

#include "AknCapServerEntry.h"

/** Phone application's AppUID. */
const TUid KPhoneAppUid  = { 0x100058B3 };

/** Phone application's view UID. */
const TUid KPhoneViewUid = { 0x10282D81 };



/** Video call application's AppUID */
const TUid KVideoCallAppUid     = { 0x101F8681 }; 

/** Layout */
const TInt KLayoutPortrait = 0;
const TInt KLayoutLandscape = 1;
/**
* Command used in activating the phone view.
* Null command allows the the phone app to decide whether
* to open dialer or call handling.
*/
const TUid KPhoneVievCommand = { 0x0 };
#ifdef RD_INTELLIGENT_TEXT_INPUT
#include <PtiDefs.h>
#include <AknFepInternalCRKeys.h>
#endif


// ================= MEMBER FUNCTIONS =======================


// ---------------------------------------------------------------------------
// CAknServKeyFilter::CAknServKeyFilter
// Default constructor.
// ---------------------------------------------------------------------------
//
CAknServKeyFilter::CAknServKeyFilter()
    : iHardwareStateKeyCaptures( 2 )
    {
    }


// ---------------------------------------------------------------------------
// CAknServKeyFilter::~CAknServKeyFilter
// Destructor.
// ---------------------------------------------------------------------------
//
CAknServKeyFilter::~CAknServKeyFilter()
    {
    FreeHardwareStateKeys();

    RWindowGroup& groupWin = iCoeEnv->RootWin();
    groupWin.CancelCaptureKeyUpAndDowns( iHomeKeyHandle );
#ifdef RD_INTELLIGENT_TEXT_INPUT
    delete iAvkonRepository;
#endif
    delete iHomeTimer;
    delete iSlideStatusObserver;
    }


// ---------------------------------------------------------------------------
// CAknServKeyFilter::ConstructL
// Second-phase constructor.
// ---------------------------------------------------------------------------
//
void CAknServKeyFilter::ConstructL( CAknCapAppServerAppUi& aAppUi )
    {
    RWindowGroup& groupWin = iCoeEnv->RootWin();
    iHomeKeyHandle      = groupWin.CaptureKeyUpAndDowns(EStdKeyApplication0, 0, 0);

    // Get the default view id
    TResourceReader reader;
    // AppUi loads this resource
    iEikonEnv->CreateResourceReaderLC( reader, R_EIK_SYSTEM_DEFAULT_VIEW_ID );
    iHomeViewId.iAppUid.iUid  = reader.ReadInt32();
    iHomeViewId.iViewUid.iUid = reader.ReadInt32();
    CleanupStack::PopAndDestroy(); // reader

    aAppUi.AddToStackL(
        this,
        ECoeStackPriorityEnvironmentFilter,
        ECoeStackFlagRefusesFocus|ECoeStackFlagOwnershipTransfered|ECoeStackFlagSharable);

    iAppUi = &aAppUi;

    CaptureHardwareStateKeysL();
    InitHardwareStateL();

    RProperty::Define( KPSUidUikon, KUikFlipStatus, RProperty::EInt );
    // Set default value for the KUikFlipStatus Pub&Sub key.
    RProperty::Set( KPSUidUikon, KUikFlipStatus, 0 );

    RProperty::Define( KCRUidAvkon, KAknQwertyInputModeActive, RProperty::EInt );
    
    // Set default value for the KAknQwertyInputModeActive Pub&Sub key.
    RProperty::Set(KCRUidAvkon, KAknQwertyInputModeActive, 0);
    iAppUi->iQwertyStatus = EFalse;


#ifdef RD_INTELLIGENT_TEXT_INPUT        
#if defined(__WINS__)    

    TInt layoutState = 0;
    TInt hwKeyCode = 0;
    RProperty::Get(KPSUidUikon, KUikLayoutState, layoutState);
    CAknLayoutConfig::THardwareStateArray hwStates = CAknSgcClient::LayoutConfig().HardwareStates();
    TInt count = hwStates.Count();
    for (TInt ii=0; ii<count; ii++)
        {
        const CAknLayoutConfig::THardwareState& hwState = hwStates.At(ii);
        if (hwState.StateNumber() == layoutState)
            {
            hwKeyCode = hwState.KeyCode();
            break;
            }
        }
        
    RProperty::Define( KCRUidAvkon, KAknKeyBoardLayout, RProperty::EInt );
    iAvkonRepository = CRepository::NewL(KCRUidAvkon);
    TInt keyboardLayout = HwKeyToKeyBoardType(hwKeyCode);
    
    // Set default value for the KAknKeyBoardLayout Pub&Sub key.
    RProperty::Set(KCRUidAvkon, KAknKeyBoardLayout, keyboardLayout);
    
    #ifdef RD_SCALABLE_UI_V2 
    // Define KAknFepVirtualKeyboardType Pub&sub key.
	RProperty::Define( KPSUidAknFep, KAknFepVirtualKeyboardType, RProperty::EInt );
	// Set default value for KAknFepVirtualKeyboardType Pub&sub key.
	RProperty::Set( KPSUidAknFep, KAknFepVirtualKeyboardType, EPtiKeyboard12Key );	
	
	// Define KAknFepTouchInputActive Pub&sub key
	RProperty::Define( KPSUidAknFep, KAknFepTouchInputActive, RProperty::EInt );
	// Set default value for KAknFepTouchInputActive Pub&sub key.
	RProperty::Set( KPSUidAknFep, KAknFepTouchInputActive, 0 );
    #endif // RD_SCALABLE_UI_V2
#else
    
    RProperty::Define( KCRUidAvkon, KAknKeyBoardLayout, RProperty::EInt );
    iAvkonRepository = CRepository::NewL(KCRUidAvkon);
    TInt keyboardLayout = EPtiKeyboard12Key;
    iAvkonRepository->Get(KAknKeyBoardLayout, keyboardLayout); 
    RProperty::Set(KCRUidAvkon, KAknKeyBoardLayout, keyboardLayout);

	#ifdef RD_SCALABLE_UI_V2 
	// Define KAknFepVirtualKeyboardType Pub&sub key.
	RProperty::Define( KPSUidAknFep, KAknFepVirtualKeyboardType, RProperty::EInt );
	// Set default value for KAknFepVirtualKeyboardType Pub&sub key.
	RProperty::Set( KPSUidAknFep, KAknFepVirtualKeyboardType, EPtiKeyboard12Key );
	
	// Define KAknFepTouchInputActive Pub&sub key
	RProperty::Define( KPSUidAknFep, KAknFepTouchInputActive, RProperty::EInt );
	// Set default value for KAknFepTouchInputActive Pub&sub key.
	RProperty::Set( KPSUidAknFep, KAknFepTouchInputActive, 0 );
	
	#endif // RD_SCALABLE_UI_V2   
#endif // !__WINS__   
    TBool isQwertyOn = EFalse;
    switch(keyboardLayout)
        {
        case EPtiKeyboardQwerty4x12:
        case EPtiKeyboardQwerty4x10:
        case EPtiKeyboardQwerty3x11:
        case EPtiKeyboardHalfQwerty:
        case EPtiKeyboardCustomQwerty:
            {
            isQwertyOn = ETrue;
            break;
            }
        default:
            break;
        }
    if(isQwertyOn)
        {
        RProperty::Set(KCRUidAvkon, KAknQwertyInputModeActive, 1);
        iAppUi->iQwertyStatus = ETrue;
        }
    else
        {
        RProperty::Set(KCRUidAvkon, KAknQwertyInputModeActive, 0);
        iAppUi->iQwertyStatus = EFalse;
        }
#endif // RD_INTELLIGENT_TEXT_INPUT
    iSlideOpen = EFalse;
    TRAP_IGNORE( iSlideStatusObserver = CAknSlideStatusNotifier::NewL( this ) );
    iSensorOrientation = KLayoutPortrait;
    }

// ---------------------------------------------------------------------------
// CAknServKeyFilter::ToggleShellL
// This method handles the short press of the applications key.
// ---------------------------------------------------------------------------
//
void CAknServKeyFilter::ToggleShellL()
    {
    RWsSession& ws = iCoeEnv->WsSession();
    TInt fgWgId    = ws.GetFocusWindowGroup();

    // Foreground application might be embedded into another application,
    // find root.
    CAknTaskList* taskList = CAknTaskList::NewL( ws );
    const RArray<RWsSession::TWindowGroupChainInfo>& chain = taskList->WgArray();
    const TInt chainCount = chain.Count();

    TBool found = ETrue;
    TInt wgId = fgWgId;
    while ( found )
        {
        found = EFalse;

        for ( TInt ii = 0; ii < chainCount; ii++ )
            {
            const RWsSession::TWindowGroupChainInfo& info = chain[ ii ];
            if ( info.iId == wgId && info.iParentId > 0 )
                {
                wgId = info.iParentId;
                found = ETrue;
                ii = chainCount; // break from for loop.
                }
            }
        }
    delete taskList;

    // Get application UID of root window group.
    CApaWindowGroupName* wgName = CApaWindowGroupName::NewL( ws, wgId );
    CleanupStack::PushL( wgName );
    TUid appUid = wgName->AppUid();
    CleanupStack::PopAndDestroy( wgName );

    TVwsViewId idleView = TVwsViewId();
    TInt err = AknDef::GetPhoneIdleViewId( idleView );
    if ( err )
        {
        return;
        }
    
    if ( appUid == iHomeViewId.iAppUid )
        {
        // We are in AppShell, so try to activate the idle app
        // or phone app if there's a call ongoing.
        TInt value = 0;
        err = RProperty::Get( KPSUidUikon, KUikVideoCallTopApp, value );
      	if ( value == KPhoneAppUid.iUid )
      	    {
            ActivateViewL( TVwsViewId( TUid::Uid( value ), KPhoneViewUid ), KPhoneVievCommand );
            }
      	else if ( value == KVideoCallAppUid.iUid )
            {
            ActivateViewL( TVwsViewId( TUid::Uid( value ), KVideoCallAppUid ), TUid::Null() );
      	    }
        else
            {
            ActivateViewL( idleView, TUid::Uid( 1 ) );
            }
          }
    else if ( appUid == idleView.iAppUid || iAppUi->IsIdelActive( ))
        {
        ActivateViewL( iHomeViewId, TUid::Uid(1) );
        }
    else
        {
        GfxTransEffect::AbortFullScreen();
        ActivateViewL( idleView, TUid::Uid(1) );
        }
    }

void CAknServKeyFilter::ActivateViewL( const TVwsViewId& aViewId, TUid aCustomMessageId )
    {
    RWsSession& ws = iCoeEnv->WsSession();
    TApaTaskList appList( ws );
    TApaTask task = appList.FindApp( aViewId.iAppUid );
    
    if ( task.Exists() )
        {
        TVwsViewId idleView = TVwsViewId();
        AknDef::GetPhoneIdleViewId( idleView );
        // If the task already exists, bring it to foreground.
        if ( aViewId.iAppUid == iHomeViewId.iAppUid )
            {
            // special process for appshell
            RThread thread;
            TInt error = thread.Open(task.ThreadId());
            if ( error == KErrNone )
               {
               thread.SetProcessPriority(EPriorityForeground);  
               }
               
            // start different fullscreen effect when launching app by KUidApaMessageSwitchOpenFile
            GfxTransEffect::BeginFullScreen(
                AknTransEffect::EApplicationActivate,
                TRect(),
                AknTransEffect::EParameterType,
                AknTransEffect::GfxTransParam( aViewId.iAppUid ) );   
            
            // matrix menu will bring itself foreground when getting the message below
            task.SendMessage( KUidApaMessageSwitchOpenFile , KNullDesC8 );
            }
        else if ( aViewId.iAppUid == idleView.iAppUid )
            {
            // special process for idle
            RThread thread;
            TInt error = thread.Open( task.ThreadId() );
            if ( error == KErrNone )
               {
               thread.SetProcessPriority( EPriorityForeground );  
               }
                           
            // idle will bring itself foreground when getting the message below
            task.SendMessage( KUidApaMessageSwitchOpenFile , KNullDesC8 );
            
            }
        else
            {
            CAknSgcClient::MoveApp(task.WgId(), ESgcMoveAppToForeground);
            }
        }
    else
        {
        // Shell app wants reactivation, so send a non-zero message ID.
        // Note that in high CPU load situations this might
        // cause the view server to panic an application,
        // that's why we try to bring an existing task
        // to foreground first.
        iAppUi->CreateActivateViewEventL( aViewId, aCustomMessageId, KNullDesC8() );
        }
    }



// ---------------------------------------------------------------------------
// CAknServKeyFilter::OfferKeyEventL
// Handles key events.
// ---------------------------------------------------------------------------
//
TKeyResponse CAknServKeyFilter::OfferKeyEventL( const TKeyEvent& aKeyEvent,
                                                TEventCode aType )
    {
    // Forward up event to app ui because of soft notification
    // key forwaring to phone app.
    if ( aType == EEventKeyUp &&
         iAppUi->iScanCodeCaptureHandle &&
         iAppUi->iPhoneKey.iScanCode == aKeyEvent.iScanCode )
        {
        iAppUi->PhoneKeyUpReceived();
        return EKeyWasConsumed;
        }

    if ( aKeyEvent.iScanCode == EStdKeyApplication0 )
        {
        return HandleHomeKeyEventL( aType );
        }
    else if ( aType==EEventKey && HandleHardwareStateKeyL( aKeyEvent.iCode ) )
        {
        return EKeyWasConsumed;
        }

    return EKeyWasNotConsumed;
    }


// ---------------------------------------------------------------------------
// CAknServKeyFilter::HandleHomeKeyEventL
// Handles the pressing of applications key.
// ---------------------------------------------------------------------------
//
TKeyResponse CAknServKeyFilter::HandleHomeKeyEventL( TEventCode aType )
    {
    if ( iAppUi->IsAppsKeySuppressed() )
        {
        return EKeyWasNotConsumed;
        }

    if ( aType == EEventKeyDown )
        {
        delete iHomeTimer;
        iHomeTimer = NULL;
        iHomeTimer = CPeriodic::NewL( CActive::EPriorityHigh );

        iHomeTimer->Start( KHomeHoldDelay, 1, TCallBack( HomeTickL, this ) );
        return EKeyWasConsumed;
        }
    else if ( aType == EEventKeyUp )
        {
        if ( iHomeTimer && iHomeTimer->IsActive() )
            {
            iHomeTimer->Cancel();
            delete iHomeTimer;
            iHomeTimer = NULL;
            if ( !iAppUi->HandleShortAppsKeyPressL() )
                {
                RWsSession& ws = iEikonEnv->WsSession();
                TApaTaskList apList( ws );
                TApaTask task = apList.FindApp( iHomeViewId.iAppUid );
                if( task.Exists() && task.WgId() == ws.GetFocusWindowGroup() )
                    {
                    GfxTransEffect::BeginFullScreen(
                        AknTransEffect::EApplicationExit,
                        TRect(),
                        AknTransEffect::EParameterType,
                        AknTransEffect::GfxTransParam( iHomeViewId.iAppUid ) );
                    }
                ToggleShellL();
                }

            return EKeyWasConsumed;
            }
        }

    return EKeyWasNotConsumed;
    }

// ---------------------------------------------------------------------------
// CAknServKeyFilter::HandleFlipKeyEvent
// Handles the flip events.
// ---------------------------------------------------------------------------
//
void CAknServKeyFilter::HandleFlipKeyEvent( TInt aCode )
    {
    if ( aCode == EKeyFlipOpen )
        {
        RProperty::Set( KPSUidUikon, KUikFlipStatus, 1 ); // flip opened
        // hack solution for mcl only, need refactory after summer vacation by SysAp
        //RProperty::Set( KPSUidHWRM, KHWRMFlipStatus, EPSHWRMFlipOpen ); // valid API
        }
    else
        {
        RProperty::Set( KPSUidUikon, KUikFlipStatus, 0 ); // flip closed
        // hack solution for mcl only, need refactory after summer vacation by SysAp
        //RProperty::Set( KPSUidHWRM, KHWRMFlipStatus, EPSHWRMFlipClosed ); // valid API
        }
    }


// ---------------------------------------------------------------------------
// CAknServKeyFilter::HomeTickL
// Static callback method of the long keypress detector of applications key.
// ---------------------------------------------------------------------------
//
TInt CAknServKeyFilter::HomeTickL( TAny* aThis )
    {
    static_cast<CAknServKeyFilter*>( aThis )->DoHomeTickL();
    return 0;   // do not continue
    }


// ---------------------------------------------------------------------------
// CAknServKeyFilter::HomeTickL
// Callback method of the long keypress detector of applications key.
// ---------------------------------------------------------------------------
//
void CAknServKeyFilter::DoHomeTickL()
    {
    iHomeTimer->Cancel();
    delete iHomeTimer;
    iHomeTimer = NULL;
    // method return value ignored (not needed)
    // leave should not happen in this level
    TRAP_IGNORE( iAppUi->HandleLongAppsKeyPressL() );
    }


// ---------------------------------------------------------------------------
// CAknServKeyFilter::CaptureHardwareStateKeysL
// Reads the hardware state keys of supported layouts and appends them
// to the captured keys.
// ---------------------------------------------------------------------------
//
void CAknServKeyFilter::CaptureHardwareStateKeysL()
    {
    RWindowGroup& groupWin = iCoeEnv->RootWin();

    CAknLayoutConfig::THardwareStateArray hwStates =
        CAknSgcClient::LayoutConfig().HardwareStates();
    TInt count = hwStates.Count();
    iHardwareStateKeyCaptures.ReserveL( count );
    for ( TInt ii = 0; ii < count; ii++ )
        {
        const CAknLayoutConfig::THardwareState& hwState = hwStates.At( ii );
        TInt key = hwState.KeyCode();
        // EKeyFlipOpen and EKeyFlipClose are already captured
        // (iFlipOpenKeyHandle and iFlipCloseKeyHandle).
        if ( key && !( key == EKeyFlipOpen || key == EKeyFlipClose ) )
            {
            iHardwareStateKeyCaptures.AppendL(groupWin.CaptureKey(key, 0, 0));
            }
        }
    }


// ---------------------------------------------------------------------------
// CAknServKeyFilter::InitHardwareStateL
// Initializes the hardware state P&S key.
// ---------------------------------------------------------------------------
//
void CAknServKeyFilter::InitHardwareStateL()
    {
    // Initialise the hardware state shared data key, so that a value exists,
    // use a state that results in screen mode zero for normal apps.
    CAknLayoutConfig::THardwareStateArray hwStates =
        CAknSgcClient::LayoutConfig().HardwareStates();

    TBool changed;
    TInt count = hwStates.Count();
    for ( TInt ii = 0; ii < count; ii++ )
        {
        const CAknLayoutConfig::THardwareState& hwState = hwStates.At( ii );
        if ( hwState.ScreenMode() == 0 )
            {
            SetHardwareStateL( hwState.StateNumber(), changed );
            return;
            }
        }

    // Fall back to state 0.
    SetHardwareStateL( 0, changed);
    }


// ---------------------------------------------------------------------------
// CAknServKeyFilter::HandleHardwareStateKeyL
// Handles hardware state key events.
// ---------------------------------------------------------------------------
//
TBool CAknServKeyFilter::HandleHardwareStateKeyL( TInt aCode )
    {
    if ( aCode == EKeyFlipOpen || aCode == EKeyFlipClose )
        {
        HandleFlipKeyEvent(aCode);
        }

    CAknLayoutConfig::THardwareStateArray hwStates =
        CAknSgcClient::LayoutConfig().HardwareStates();
    TInt count = hwStates.Count();
    for ( TInt ii = 0; ii < count; ii++ )
        {
        const CAknLayoutConfig::THardwareState& hwState = hwStates.At( ii );
        if ( hwState.KeyCode() == aCode )
        	{
            // Found the state
        	iSensorOrientation = hwState.StateNumber();
            if( !iSlideOpen )
				{
                UpdateStateAndNotifyL( hwState.StateNumber() );
#ifdef RD_INTELLIGENT_TEXT_INPUT
#if defined(__WINS__)
            
            TInt keyboardLayout = HwKeyToKeyBoardType(aCode);
            TInt curkeyLayout = 0;
            TBool qwertyOn = EFalse;
            RProperty::Get(KCRUidAvkon, KAknKeyBoardLayout, curkeyLayout);
            
		        switch(keyboardLayout)
                {
                case EPtiKeyboardQwerty4x12:
                case EPtiKeyboardQwerty4x10:
                case EPtiKeyboardQwerty3x11:
                case EPtiKeyboardHalfQwerty:
                case EPtiKeyboardCustomQwerty:
                    {
                    qwertyOn = ETrue;
                    break;
                    }
                default:
                    break;
                }					  
        
            if(curkeyLayout != keyboardLayout)
                {
                RProperty::Set(KCRUidAvkon, KAknKeyBoardLayout, keyboardLayout);
                }
            if(qwertyOn)
                {
                iAppUi->iQwertyStatus = ETrue;
                TInt err = RProperty::Set(KCRUidAvkon, KAknQwertyInputModeActive, 1); 
                iAvkonRepository->Set(KAknQwertyInputModeActive,1);
                } 
            else
                {
                iAppUi->iQwertyStatus = EFalse;
                TInt err = RProperty::Set(KCRUidAvkon, KAknQwertyInputModeActive, 0); 
                iAvkonRepository->Set(KAknQwertyInputModeActive,0); 
                }
#endif // __WINS__            
#else
#if defined(__WINS__)
            // On emulator environment, Qwerty input mode is set active when
            // the emulator facia bitmap has Qwerty keyboard. Otherwise the
            // Qwerty input mode is set off.
            // Key code EKeyDeviceF is used when the Qwerty emulator is activated.
            TInt err;
            if ( aCode == EKeyDeviceF )
                {
                err = RProperty::Set( KCRUidAvkon, KAknQwertyInputModeActive, 1 );
                iAppUi->iQwertyStatus = 1;
                }
            else
                {
                err = RProperty::Set( KCRUidAvkon, KAknQwertyInputModeActive, 0 );
                iAppUi->iQwertyStatus = 0;
                }

#ifdef _DEBUG
            _LIT( KDMsg, "xxxx KAknQwertyInputModeActive err=%d" );
            RDebug::Print( KDMsg, err );
#endif

#endif // __WINS__
#endif //RD_INTELLIGENT_TEXT_INPUT
            return ETrue;
				}
            }
        }

    return EFalse;
    }


// ---------------------------------------------------------------------------
// CAknServKeyFilter::FreeHardwareStateKeys
// Frees the captured hardware state keys.
// ---------------------------------------------------------------------------
//
void CAknServKeyFilter::FreeHardwareStateKeys()
    {
    RWindowGroup& groupWin = iCoeEnv->RootWin();
    TInt count = iHardwareStateKeyCaptures.Count();
    for ( TInt ii = 0; ii < count; ii++ )
        {
        groupWin.CancelCaptureKey( iHardwareStateKeyCaptures[ii] );
        }
    iHardwareStateKeyCaptures.Close();
    }


// ---------------------------------------------------------------------------
// CAknServKeyFilter::SetHardwareStateL
// Updates the hardware state P&S key.
// ---------------------------------------------------------------------------
//
void CAknServKeyFilter::SetHardwareStateL( TInt aState, TBool& aChanged )
    {
    TInt currentState(-1);
    RProperty::Get( KPSUidUikon, KUikLayoutState, currentState );
    aChanged = currentState != aState;
    if ( aChanged )
        {
        TInt err = RProperty::Set( KPSUidUikon, KUikLayoutState, aState );

#ifdef _DEBUG
    _LIT( KDMsg1, "xxxx KUikLayoutState err=%d" );
    RDebug::Print( KDMsg1, err );
#endif

#ifdef _DEBUG // should we omit error as we used to
    User::LeaveIfError( err );
#endif

    // Reset preferred orientation
    err = RProperty::Set( KPSUidUikon,
                          KUikPreferredOrientation,
                          EPreferredOrientationNormal );

#ifdef _DEBUG
    _LIT( KDMsg2, "xxxx KUikPreferredOrientation err=%d" );
    RDebug::Print( KDMsg2, err );
#endif

#ifdef _DEBUG
    User::LeaveIfError( err );
#endif
        }
    }

#ifdef RD_INTELLIGENT_TEXT_INPUT
TInt CAknServKeyFilter::HwKeyToKeyBoardType(TInt aKeyCode)
    {
    TInt ret = EPtiKeyboardNone;
    switch(aKeyCode)
        {
        case EKeyApplicationE:
            {
            ret = EPtiKeyboardQwerty4x10;
            break;
            }
        case EKeyApplication10:
            {
            ret = EPtiKeyboardQwerty3x11; //mini Qwerty
            break;
            }
        case EKeyApplication11:
            {
            ret = EPtiKeyboardHalfQwerty; // half Qwerty
            break;
            }
//The EKeyDeviceF is done only for emulator. Borrowed from the old code.
#if defined(__WINS__)
        case EKeyDeviceF:
            {
            ret = EPtiKeyboardQwerty4x12;
            break;
            }
#endif
		// ITU-T screen event
        case EKeyApplication12:
        case EKeyApplication15:
        case EKeyApplication16:
        case EKeyFlipClose:
            {
            ret = EPtiKeyboard12Key;
            break;
            }
        default:
            {
            iAvkonRepository->Get(KAknKeyBoardLayout, ret);
            break;
            }
        }
    return ret;
    }
#endif //RD_INTELLIGENT_TEXT_INPUT

// ---------------------------------------------------------------------------
// CAknServKeyFilter::SlideStatusChangedL
// ---------------------------------------------------------------------------
//
void CAknServKeyFilter::SlideStatusChangedL( const TInt& aValue )
    {
	CAknLayoutConfig::THardwareStateArray hwStates =
		CAknSgcClient::LayoutConfig().HardwareStates();
    TInt keyboardLayout(0);
    TInt state(0);
    
    RWsSession wsSession = iEikonEnv->WsSession();
    
    TKeyEvent eventQwertyOn = { EKeyQwertyOn, 0 };
    
    TKeyEvent eventQwertyOff = { EKeyQwertyOff, 0 };

	switch( aValue )
		{
		case EPSHWRMGripOpen:
			iSlideOpen = ETrue;
			wsSession.SimulateKeyEvent( eventQwertyOn );
			//to be read from cenrep
			iAvkonRepository->Get( KAknKeyboardSlideOpen, keyboardLayout );
			if( keyboardLayout > EPtiKeyboard12Key )
				{
				//if the keyboard is a qwerty the layout is landscape
				state = KLayoutLandscape;
				}
			else
				{
				//if the keyboard is not a qwerty the layout is portrait
				state = KLayoutPortrait;
				}
			break;
		case EPSHWRMGripClosed:
			iSlideOpen = EFalse;
			wsSession.SimulateKeyEvent( eventQwertyOff );
			state = iSensorOrientation;
			iAvkonRepository->Get( KAknKeyboardSlideClose, keyboardLayout );
			break;
		}
	
	UpdateKeyboardLayout( keyboardLayout );
	RotateScreenL( state );
    }

// ---------------------------------------------------------------------------
// CAknServKeyFilter::UpdateKeyboardLayout
// ---------------------------------------------------------------------------
//
void CAknServKeyFilter::UpdateKeyboardLayout( TInt aKeyboardLayout )
    {
    RProperty::Set(KCRUidAvkon, KAknKeyBoardLayout, aKeyboardLayout);
	if( aKeyboardLayout > EPtiKeyboard12Key )
		{
		iAppUi->iQwertyStatus = ETrue;
		TInt err = RProperty::Set(KCRUidAvkon, KAknQwertyInputModeActive, 1); 
		iAvkonRepository->Set(KAknQwertyInputModeActive,1);
		}
	else
		{
		iAppUi->iQwertyStatus = EFalse;
		TInt err = RProperty::Set(KCRUidAvkon, KAknQwertyInputModeActive, 0); 
		iAvkonRepository->Set(KAknQwertyInputModeActive, 0);
		}
    }

// ---------------------------------------------------------------------------
// CAknServKeyFilter::RotateScreenL
// ---------------------------------------------------------------------------
//
void CAknServKeyFilter::RotateScreenL( TInt aState )
	{
	CWsScreenDevice* screen = iEikonEnv->ScreenDevice();
	TInt screenMode = screen->CurrentScreenMode();
	TBool changed;
	SetHardwareStateL( aState, changed);
	
    // Update the setting cache and get SGCS to process the screen
    // mode change. This may broadcast a screen device change to
    // the apps, to inform them of the update.
    iAvkonEnv->SettingCache().Update( KAknHardwareLayoutSwitch );
    iAppUi->SgcServer()->HandleWindowGroupParamChangeL(
        iEikonEnv->RootWin().Identifier(),
        0,
        0,
        0,
        KAknScreenModeUnset );

	if ( screenMode == screen->CurrentScreenMode() )
		{
		// Apps will not have received a screen device changed event
		// so send a KAknHardwareLayoutSwitch to the apps to ensure
		// they get to know about the key.
		TWsEvent event;
		event.SetType( KAknHardwareLayoutSwitch );
		event.SetHandle( 0 );
		iEikonEnv->WsSession().SendEventToAllWindowGroups( 0, event );
		}
    }
	
// ---------------------------------------------------------------------------
// CAknServKeyFilter::UpdateStateAndNotifyL
// ---------------------------------------------------------------------------
//
void CAknServKeyFilter::UpdateStateAndNotifyL( TInt aState )
    {
    CWsScreenDevice* screen = iEikonEnv->ScreenDevice();
    TInt screenMode = screen->CurrentScreenMode();
    TBool changed;
    SetHardwareStateL( aState, changed);
    
    //Do something only if anything changed
    if (changed)
        {
        // Update the setting cache and get SGCS to process the screen
        // mode change. This may broadcast a screen device change to
        // the apps, to inform them of the update.
        iAvkonEnv->SettingCache().Update( KAknHardwareLayoutSwitch );
        iAppUi->SgcServer()->HandleWindowGroupParamChangeL(
            iEikonEnv->RootWin().Identifier(),
            0,
            0,
            0,
            KAknScreenModeUnset );
        
        }
    
    if (screenMode == screen->CurrentScreenMode() )
        {
        // Remember that there was at least one inhibited screen mode
        iAppUi->SgcServer()->SetBackgroundAppsStateChangeDeferred( ETrue );
        }
    }

// End of file
