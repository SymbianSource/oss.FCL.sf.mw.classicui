/*
* Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Avkon keysound animation dll.
*
*/

// INCLUDES
#include "AknAnimKeySound.h"
#include <eikkeysound.h>
#include "aknanimdllstd.h"
#include <AknKeyRotator.h>
#include <keffactory.h>
#include <centralrepository.h>

// End key - power key related headers
#include <featmgr.h>
#include <e32property.h>
#include <UikonInternalPSKeys.h>
#include "avkoninternalpskeys.h"    // KAknIdleAppWindowGroupId
#include <avkondomainpskeys.h>      // KAknPowerMenuStatus & KAknEndKeyEvent

// This is currently nasty set dependencies, API should be moved to middleware layer asap 
#include <ctsydomainpskeys.h> 

#include <networkhandlingdomainpskeys.h>
#include <PSVariables.h>

#include <hwrmlight.h> 
#include <tactilefeedbackserver.h>

// CONSTANTS
const TInt KShortPress(600000);
const TInt KLongPress(1800000); // Extreme long press 2,4s - 0,6s

enum TKeyEmulationAction
    {
    EDoNothing = 0,
    EEmulateNow,
    EEmulateNowPhoneCallActive,
    EEmulateNowNotificationOnTop, 
    ESetEventPending
    };

// Scan codes in this table are blocked by the animdll if another key is currently being pressed
// This prevents two keys from being pressed, but allows power key, headset and grip to still be 
// operated.
const TInt KBlockedKeyCodes[] =
    {
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    '0',
    EStdKeyHash,
    EStdKeyNkpAsterisk,
    EStdKeyYes,
    EStdKeyNo,
    EStdKeyApplication0,    // Apps key
    EStdKeyDevice6          // Side key
    };

const TInt KBlockedKeyCodeTableSize = sizeof(KBlockedKeyCodes) / sizeof(TInt);

NONSHARABLE_CLASS(CAknPendingKeyEvent): public CTimer
    {
public:
    static CAknPendingKeyEvent* NewL(MAnimGeneralFunctions* aFucntions, TInt& aEmulatedKey);
    ~CAknPendingKeyEvent();
    TBool HandleKeyReleased(const TRawEvent &aRawEvent);
    void SetShortTimerForEvent(const TRawEvent &aRawEvent);
    void SetLongTimerForEvent(const TRawEvent &aRawEvent);
    void JustEmulateUpEvent(const TRawEvent &aRawEvent);
    TBool IsMadeUpEvent()
        {
        return iIsMadeUpEvent;
        }
    
private:    
    CAknPendingKeyEvent(MAnimGeneralFunctions* aFucntions, TInt& aEmulatedKey);
    void RunL();
    void DoCancel();
    
    enum
        {
        EBreathe,
        EShort,
        ELong,
        EWaitingUpEvent
        };
    
    TInt iState;
    TRawEvent iPendingEvent;
    TInt& iEmulatedKey; 
    MAnimGeneralFunctions* iFunctions; 
    TBool iIsMadeUpEvent; // Indicates whether the event is self generated.
    };

// REikSrvSoundServerSession implementation:

// -----------------------------------------------------------------------------
// REikSrvSoundServerSession::Connect
// -----------------------------------------------------------------------------
//
TInt REikSrvSoundServerSession::Connect()
    {
    // Create a session with zero message slots 
    // (since we have no asycronous calls).
    TInt ret=CreateSession
        (
        __KEYSOUND_SERVER_NAME,
        TVersion( 
            KKeySoundServMajorVN, 
            KKeySoundServMinorVN, 
            KKeySoundServBuildVN ),
        1
        );
    return ret;  
    }

// -----------------------------------------------------------------------------
// REikSrvSoundServerSession::KeyPressed
//
// NB. as this is asynchronous, the cancel should be provided also, anyway we rely on that 
// keysound server will complete all requests relatively fast so we never stall on 
// ~CAknAnimKeySound more than tens of milliseconds.
// -----------------------------------------------------------------------------
//
void REikSrvSoundServerSession::KeyPressed( TInt aKey, TRequestStatus& aStatus, TBool aRepeat )
    {
    TIpcArgs args( aKey, aRepeat);    
    SendReceive( EKeySoundServerPlayKey, args, aStatus ); 
    }

// CAknAnimKeySound implementation:

// -----------------------------------------------------------------------------
// CAknAnimKeySound::CAknAnimKeySound
// -----------------------------------------------------------------------------
//
CAknAnimKeySound::CAknAnimKeySound()
    :iEnableKeyBlock(ETrue), 
     iBlockedPointerDown(EFalse),
     iBlockKeyEvents( EFalse ),
     iBlockPointerEvents( EFalse )
    {
    iFeedback = MTactileFeedbackServer::Instance();
    }

// -----------------------------------------------------------------------------
// CAknAnimKeySound::~CAknAnimKeySound
// -----------------------------------------------------------------------------
//
CAknAnimKeySound::~CAknAnimKeySound()
    {
    if ( iFunctions )
        {
        iFunctions->GetRawEvents( EFalse );
        }
    delete iKeyRotator;
    iRotateLibrary.Close();

    delete iKeyEventMap;
    iKefLibrary.Close();
    
    
    delete iSoundSession;
    delete iPendingEvent;
    delete iLight;
    }

// -----------------------------------------------------------------------------
// CAknAnimKeySound::CommandReplyL
// -----------------------------------------------------------------------------
//
TInt CAknAnimKeySound::CommandReplyL( TInt /*aOpcode*/, TAny* /*aArgs*/ )
    {
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CAknAnimKeySound::Command
// -----------------------------------------------------------------------------
//
void CAknAnimKeySound::Command( TInt /*aOpcode*/, TAny* /*aArgs*/ )
    {
    }

// -----------------------------------------------------------------------------
// CAknAnimKeySound::Animate
// -----------------------------------------------------------------------------
//
void CAknAnimKeySound::Animate( TDateTime* /*aDateTime*/ )
    {
    }

// -----------------------------------------------------------------------------
// CAknAnimKeySound::ConstructL
// -----------------------------------------------------------------------------
//
void CAknAnimKeySound::ConstructL( TAny* /*aArgs*/, TBool /*aHasFocus*/ )
    {
    iFunctions->GetRawEvents( ETrue );
    
    iSoundSession = new (ELeave) CAknAsynchTonePlayer();
    
    if ( iKefLibrary.Load( KKefLibraryName ) == KErrNone )
        {
        // The function in the lookup table may leave (CreateKefMapL)
        TInt res = iKefLibrary.Lookup( KKefMapFactoryFunctionOrdinal )();
        iKeyEventMap = (CKefMap*)res;
        
        if ( !iKeyEventMap->IsKeyEventMapEnabled() )
            {
            // Key event map is disabled. Use default approach.
            delete iKeyEventMap;
            iKeyEventMap = NULL;
            iKefLibrary.Close();
            }
        else
            {
            iKeyEventMap->SetProvider( *this );
            }
        }

    if ( !iKeyEventMap )
        {
        if ( iRotateLibrary.Load( KAknKeyRotatorLibraryName ) == KErrNone )
            {
            // The function in the lookup table may leave (CreateAknKeyRotatorL)
            TInt res = iRotateLibrary.Lookup( KAknKeyRotatorFactoryFunctionOrdinal )();
            iKeyRotator = (CAknKeyRotator*)res;
            }
        iConnected = iSoundSession->iSoundSession.Handle() != 0;
        }
    
    FeatureManager::InitializeLibL();
    iFeatureNoPowerKey = 
        FeatureManager::FeatureSupported( KFeatureIdNoPowerkey );    

    if (iFeatureNoPowerKey)
        {
        iPendingEvent = CAknPendingKeyEvent::NewL(iFunctions, iNoPowerKeyScanCode);
        }

    FeatureManager::UnInitializeLib();
    
    // Get extension for querying and manipulating the window and screen attributes.
    iExt = reinterpret_cast<MAnimGeneralFunctionsWindowExtension*>(iFunctions->ExtendedInterface(
        MAnimGeneralFunctions::EWindowExtensionInterface)); 
            
    iLight = CHWRMLight::NewL();
    }

// -----------------------------------------------------------------------------
// CAknAnimKeySound::Redraw
// -----------------------------------------------------------------------------
//
void CAknAnimKeySound::Redraw()
    {
    }

// -----------------------------------------------------------------------------
// CAknAnimKeySound::FocusChanged
// -----------------------------------------------------------------------------
//
void CAknAnimKeySound::FocusChanged( TBool /*aState*/ )
    {
    }

// -----------------------------------------------------------------------------
// CAknAnimKeySound::IsBlockedKeyCode
// -----------------------------------------------------------------------------
//
TBool CAknAnimKeySound::IsBlockedKeyCode( TInt aScanCode )
    {
    for ( TInt ii=0; ii < KBlockedKeyCodeTableSize; ii++ )
        {
        if ( aScanCode == KBlockedKeyCodes[ii] )
            {
            return ETrue;
            }
        }
    return EFalse;
    }

// -----------------------------------------------------------------------------
// CAknAnimKeySound::NonBlockedKeyCode
// -----------------------------------------------------------------------------
//
TBool CAknAnimKeySound::NonBlockedKeyCode( TInt aScanCode )
    {
    // Return ETrue if this key is never blocked - typically just modifiers
    if ( aScanCode == EStdKeyLeftShift || aScanCode == EStdKeyRightShift ||
         aScanCode == EStdKeyLeftCtrl || aScanCode == EStdKeyRightCtrl ||
         aScanCode == EStdKeyLeftAlt || aScanCode == EStdKeyRightAlt ||
         aScanCode == EStdKeyLeftFunc || aScanCode == EStdKeyRightFunc )
        {
        return ETrue;
        }
    return EFalse;
    }

// -----------------------------------------------------------------------------
// CAknAnimKeySound::IsBlockedEvent
// HW keys and touch event interaction 
// -----------------------------------------------------------------------------
//
TBool CAknAnimKeySound::IsBlockedEvent( const TRawEvent &aRawEvent )
    {
    // Check key event exceptions
    if ( iBlockKeyEvents )
        {
        if ( aRawEvent.Type() == TRawEvent::EKeyDown || 
             aRawEvent.Type() == TRawEvent::EKeyRepeat ||
             aRawEvent.Type() == TRawEvent::EKeyUp )
            {
            // Vkb generated key event
            if ( aRawEvent.IsTip () )
                {
                return EFalse;
                }
            TInt scan = aRawEvent.ScanCode() & 0xFFFF;
            if ( IsAlwaysAcceptedKey( scan ) )
                {
                return EFalse;
                }
            }
        }
        
    // if key down, block pointer events and vice versa   
    switch ( aRawEvent.Type() )
        {
        case TRawEvent::EKeyDown:
            {
            if ( iBlockKeyEvents )
                {
                return ETrue;
                }
            else
                {
                // If exception key, don't block pointer events
                TInt scan = aRawEvent.ScanCode() & 0xFFFF;
                if ( IsAlwaysAcceptedKey( scan ) )
                    {
                    iBlockPointerEvents = EFalse;
                    }
                else
                    {
                    iBlockPointerEvents = ETrue;    
                    }
                }
            break;
            }
        
        case TRawEvent::EKeyRepeat:
            {
            if ( iBlockKeyEvents )
                {
                return ETrue;
                }
            break;                    
            }
        
        case TRawEvent::EKeyUp:
            {
            if ( iBlockKeyEvents )
                {
                return ETrue;
                }
             else
                {
                iBlockPointerEvents = EFalse;
                }
            break;                
            }
            
        case TRawEvent::EButton1Down:
            {
            if ( iBlockPointerEvents )
                {
                return ETrue;
                }
            else
                {
                iBlockKeyEvents = ETrue;
                }
            break;    
            }            
            
        case TRawEvent::EPointerMove:
            {
            if ( iBlockPointerEvents )
                {
                return ETrue;
                }
            break;
            }
        
        case TRawEvent::EButton1Up:
            {
            if ( iBlockPointerEvents )
                {
                return ETrue;
                }
            else
                {
                iBlockKeyEvents = EFalse;
                }
            break;
            }
            
        default:
            break;
        }
    return EFalse;
    }

// -----------------------------------------------------------------------------
// CAknAnimKeySound::IsAlwaysAcceptedKey
// HW keys and touch event interaction - keys that work even if touch is active
// -----------------------------------------------------------------------------
//
TBool CAknAnimKeySound::IsAlwaysAcceptedKey( TInt aScanCode )
    {
    if ( aScanCode == EStdKeyLeftShift || aScanCode == EStdKeyRightShift ||
         aScanCode == EStdKeyLeftCtrl || aScanCode == EStdKeyRightCtrl ||
         aScanCode == EStdKeyLeftAlt || aScanCode == EStdKeyRightAlt ||
         aScanCode == EStdKeyApplication10 || // Layout switch to landscape
         aScanCode == EStdKeyApplication14 || // Layout switch to portrait
         aScanCode == EStdKeyDevice2 || // Power button
// Device & application keys 
         ( aScanCode >= EStdKeyDevice4 && aScanCode <= EStdKeyDeviceF )||
         ( aScanCode >= EStdKeyApplication6 && aScanCode <= EStdKeyApplicationF ) ||
         ( aScanCode >= EStdKeyDevice10 && aScanCode <= EStdKeyApplication27 ) )
        {
        return ETrue;
        }
    return EFalse;   
    }


// -----------------------------------------------------------------------------
// IsIdleAppOnTop
//
// Returns ETrue, if the window group of Idle application is topmost.
// -----------------------------------------------------------------------------
//
TBool IsIdleAppOnTop(MAnimGeneralFunctionsWindowExtension* aExt)
    {
    TBool retval = ETrue;        
    TInt idleWgId = 0;
    MAnimGeneralFunctionsWindowExtension::TWindowGroupInfo wgInfo;
    
    // Check screen having focus and the number of existing window groups.
    TInt focused = aExt->FocusScreens();
    TInt groups  = aExt->WindowGroups(focused);
    
    // Get the idle application window group id.
    TInt err = RProperty::Get(KPSUidAvkonInternal, KAknIdleAppWindowGroupId, idleWgId);
    
    // If there is an error fetching the window group id, it is safer to assume that
    // Idle application is on top. The power menu will be shown then.    
    if(!err && idleWgId != -1)
        {
        // Got valid window group id. Go through the window group list and find if there is a 
        // focusable group on top of Idle.
        for (TInt i = 0; i < groups; i++)
            {
            const TBool exist = aExt->WindowGroupInfo(wgInfo, focused, i);
            
            if(exist)
                {
                if (wgInfo.iId == idleWgId)
                    {
                    // Idle app is on top.
                    break;
                    }
                else if (wgInfo.IsFocusable())
                    {
                    // We have some notification on top of the idle app.
                    retval = EFalse;
                    break;
                    }
                }
            } 
        }      
    else
        {
#ifdef _DEBUG
        RDebug::Print(_L("AknAnimKeySound:IsIdleAppOnTop() - Error fetching idleWgId, id=%d"), err);         
#endif                 
        }
    return retval;
    }

// -----------------------------------------------------------------------------
// EmulateEndKeyL
//
// Emulates end key. Used if the device has combined power and end key.
// -----------------------------------------------------------------------------
//
void EmulateEndKeyL(TKeyEmulationAction& aResult, const TRawEvent &aRawEvent, 
    /*TInt& aEmulatedScanCode,*/ MAnimGeneralFunctionsWindowExtension* aExt)
    {
    aResult = EDoNothing;
    if (aRawEvent.Type() == TRawEvent::EKeyDown)
        {
        TInt ps(0), startupOk(0), idle(0);

        // If system is not in idle or there are calls ongoing, then end key ought to be generated.
        User::LeaveIfError( RProperty::Get( KPSUidCtsyCallInformation, KCTsyCallState, ps ) );
        User::LeaveIfError( RProperty::Get( KPSUidUikon, KUikGlobalNotesAllowed, startupOk ) );

        RDebug::Print(_L("call: %d, idle %d, notes %d"), ps, idle, startupOk);

        // Call state not yet initialized or startup not yet complete but no emergency call ongoing.
        if (ps == EPSCTsyCallStateUninitialized || 
           (ps == EPSCTsyCallStateNone && !startupOk) )
            {
            return;
            }
        if ( ps != EPSCTsyCallStateNone )
            {
            // A phone call is active.
            aResult = EEmulateNowPhoneCallActive;
            }
        else
            {
            // We are in idle view with no active phone calls. 
            TInt powerMenuActive(0);
                        
            // If power menu is active, do not check windows on top of the Idle app, short power
            // key presses must change the item in the power menu, not to close the power menu.
            User::LeaveIfError(RProperty::Get(KPSUidAvkonDomain, KAknPowerMenuStatus, powerMenuActive));
            if(!powerMenuActive)
                {
                // If there is a notification (window) on top of idle, the event is changed to 
                // end key for closing it. Otherwise we continue normally.
                if(!IsIdleAppOnTop(aExt))
                    {
                    aResult = EEmulateNowNotificationOnTop;
                    return;
                    }
                }
            
            // Make bearer resolution.
            User::LeaveIfError(RProperty::Get(KPSUidNetworkInfo, KNWTelephonyNetworkMode, ps)); 
            if (ps == ENWNetworkModeWcdma)
                {
                User::LeaveIfError(RProperty::Get(KUidSystemCategory, KPSUidWcdmaStatusValue, ps));
                if (ps != EPSWcdmaStatusUninitialized && ps != EPSWcdmaUnattached && ps != KErrUnknown)
                    {
                    // Wcdma is active (or attached).
                    aResult = ESetEventPending;
                    }        
                else
                    {
                    // Wcdma is not active, do nothing.
                    }
                } 
            else // gsm et als
                {
                User::LeaveIfError(RProperty::Get(KUidSystemCategory, KPSUidGprsStatusValue, ps));
                if (ps != EPSGprsUnattached && ps != EPSGprsStatusUninitialized && ps != KErrUnknown)
                    {
                    // Gprs is active (or attached).                    
                    aResult = ESetEventPending;
                    }
                else
                    {
                    // Gprs is not active, do nothing.
                    }
                }
            } 
        }
    }

// -----------------------------------------------------------------------------
// EmulateEndKey
//
// Emulates end key. Used if the device has combined power and end key.
// -----------------------------------------------------------------------------
//
TKeyEmulationAction EmulateEndKey(const TRawEvent &aRawEvent, /*TInt& aEmulatedScanCode,*/
    MAnimGeneralFunctionsWindowExtension* aExt)
    {
    TKeyEmulationAction result(EDoNothing);
        {
        TRAP_IGNORE(EmulateEndKeyL(result, aRawEvent/*, aEmulatedScanCode*/, aExt));
        }
    return result;    
    }

// -----------------------------------------------------------------------------
// CAknAnimKeySound::OfferRawEvent
// -----------------------------------------------------------------------------
//
TBool CAknAnimKeySound::OfferRawEvent(const TRawEvent &aRawEvent)
    {
    // Check HW and touch interaction
    if ( IsBlockedEvent ( aRawEvent ) )
        {
        return ETrue;
        }
 
    // Check key blocking enable / disable codes:
    if ( (TAknKeySoundOpcode)( aRawEvent.Type() ) == EEnableKeyBlock )
        {
        iEnableKeyBlock = ETrue;
        return ETrue;
        }
    if ( (TAknKeySoundOpcode)( aRawEvent.Type() ) == EDisableKeyBlock )
        {
        iEnableKeyBlock = EFalse;
        return ETrue;
        }

    if (iFeatureNoPowerKey && !iPendingEvent->IsMadeUpEvent() 
        && (aRawEvent.Type () == TRawEvent::EKeyDown || aRawEvent.Type () == TRawEvent::EKeyUp ))
        {
        if (aRawEvent.ScanCode() != EStdKeyDevice2)
            {
            if (aRawEvent.ScanCode() != iNoPowerKeyScanCode) // handle here so it won't fall through
                {
                iPendingEvent->Cancel();    
                }
            }
        else if (iPendingEvent->IsActive())
            {
            if (iPendingEvent->HandleKeyReleased(aRawEvent))
                {
                return ETrue;
                }
            // else let it just fall trough of KEF also            
            }
        else
            {
            // evaluate now
            TInt action = EmulateEndKey(aRawEvent, iExt);
            
            switch(action)
                {
                case EEmulateNow:
                case EEmulateNowPhoneCallActive:
                case EEmulateNowNotificationOnTop:
                    {
                    TRawEvent newEvent(aRawEvent);
                    newEvent.Set( aRawEvent.Type(), EStdKeyNo );
                    iFunctions->PostRawEvent(newEvent);
                        
                    if (action == EEmulateNow)
                        {
                        // Start timer for extra long key press (both keys generated).
                        iPendingEvent->SetLongTimerForEvent(newEvent);
                        }
                    else
                        {
                        // No timers are set. A long power key press must not switch the phone off
                        // if there is an active phone call or a notification is on top of the Idle app. 
                        // Only the call needs to be disconnected or notification closed.
                        iPendingEvent->JustEmulateUpEvent(newEvent); 
                        }
                    return ETrue;            
                    }            
                case ESetEventPending:
                    {
                    // set short timer for down event
                    iPendingEvent->SetShortTimerForEvent(aRawEvent);
                    return ETrue; 
                    }
                default:
                    break;            
                }
            }
        }

    // If key event map is in use, then forward events.
    if ( iKeyEventMap )
        {
        if ( iKeyEventMap->OfferRawEvent( aRawEvent, EFalse ) )
            {
            return ETrue;
            }
        }
    else
        {
        // If key rotator is in use, then forward key events.
        // Note that key event map and key rotator cannot be in use at
        // the same time.
        if( iKeyRotator )
            {
            if ( iKeyRotator->CheckRotation( aRawEvent, *iFunctions ) )
                {
                return ETrue;
                }
            }
        }

    // If key event map is disabled, then use default approach.
    // Also, if key event map did not consume event, handle blocking here.
    // However, key sounds are handled in key event map.
   
    // Then, check the key blocking
    TBool blockEvent = EFalse;
    
    switch ( aRawEvent.Type() )
        {
        case TRawEvent::EKeyDown:
            {
            TInt scan = aRawEvent.ScanCode() & 0xFFFF;
            if ( !NonBlockedKeyCode( scan ) 
                && iKeyPressed && iEnableKeyBlock && IsBlockedKeyCode( scan ) )
                {
                blockEvent = ETrue;
                }
            else
                {
                if ( iConnected ) // to avoid playing tones twice with KEF
                    {
                    iSoundSession->KeyPressed( scan );
                    }
                if ( !NonBlockedKeyCode( scan ) )
                    {
                    iKeyPressed = scan;
                    }
                else
                    {
                    iKeyPressed = 0;
                    }
                }
            }
            break;

        case TRawEvent::EKeyRepeat:
            {
            TInt scan = aRawEvent.ScanCode() & 0xFFFF;
            if ( !NonBlockedKeyCode( scan ) && iKeyPressed != scan && 
                 iEnableKeyBlock && IsBlockedKeyCode( scan ) )
                {
                // If down event is not passed forward, then 
                // repeat events are not passed either.
                blockEvent = ETrue;
                }
            }
            break;
            
        case TRawEvent::EKeyUp:
            {
            TInt scan = aRawEvent.ScanCode() & 0xFFFF;
            if ( !NonBlockedKeyCode( scan ) && iKeyPressed != scan && 
                 iEnableKeyBlock && IsBlockedKeyCode( scan ) )
                {
                // Do not need to block key-up events - there's not a problem 
                // if there's an unexpected key-up events delivery to an app
                }
            else
                {
                iKeyPressed = 0;
                }
            }
            break;
        
        // If pointer down is received when the lights are out,
        // all pointer events are blocked until next pointer down.    
                case TRawEvent::EButton1Down:
            {
            if( iBlockedPointerDown )
                {
                iBlockedPointerDown = EFalse;
                }

            if( iLight && iLight->LightStatus( CHWRMLight::EPrimaryDisplay ) == CHWRMLight::ELightOff )
                {
                blockEvent = ETrue;
                iBlockedPointerDown = ETrue;
                }
            }
            break;
        case TRawEvent::EButton1Up:
        case TRawEvent::EPointerMove:
            {
            if( iBlockedPointerDown )
                {
                blockEvent = ETrue;
                }
            }
            break;

        default:
            break;
        }

    return blockEvent;
    }

// -----------------------------------------------------------------------------
// CAknAnimKeySound::KefPostRawEvent
// -----------------------------------------------------------------------------
//
void CAknAnimKeySound::KefPostRawEvent(const TRawEvent& aRawEvent) const
    {
    iFunctions->PostRawEvent( aRawEvent );
    }

// -----------------------------------------------------------------------------
// CAknAnimKeySound::KefPostKeyEvent
// -----------------------------------------------------------------------------
//
void CAknAnimKeySound::KefPostKeyEvent(const TKeyEvent& aKeyEvent) const
    {
    iFunctions->PostKeyEvent( aKeyEvent );
    }

// -----------------------------------------------------------------------------
// CAknAnimKeySound::KefGenerateKeySound
// -----------------------------------------------------------------------------
//
void CAknAnimKeySound::KefGenerateKeySound( TInt aKey )
    {
    iSoundSession->KeyPressed( aKey, EFalse );
    }

// -----------------------------------------------------------------------------
// CAknAnimKeySound::KefGenerateFeedback
// -----------------------------------------------------------------------------
//
void CAknAnimKeySound::KefGenerateFeedback( TUint16 aFeedback )
    {
    if ( iFeedback )
        {
        iFeedback->InstantFeedback( (TTouchLogicalFeedback)aFeedback );
        }
    }

// -----------------------------------------------------------------------------
// CAknPendingKeyEvent::NewL
// -----------------------------------------------------------------------------
//
CAknPendingKeyEvent* CAknPendingKeyEvent::NewL(MAnimGeneralFunctions* aFunctions, TInt& aEmulatedKey)
    {
    CAknPendingKeyEvent* me = new (ELeave) CAknPendingKeyEvent(aFunctions, aEmulatedKey);
    CleanupStack::PushL(me);
    me->ConstructL();
    CleanupStack::Pop();
    return me;
    }

// -----------------------------------------------------------------------------
// CAknPendingKeyEvent::CAknPendingKeyEvent
// -----------------------------------------------------------------------------
//
CAknPendingKeyEvent::CAknPendingKeyEvent(MAnimGeneralFunctions* aFunctions, TInt& aEmulatedKey)
    :CTimer(CActive::EPriorityHigh),iEmulatedKey(aEmulatedKey),iFunctions(aFunctions)
    {
    CActiveScheduler::Add(this);
    }

// -----------------------------------------------------------------------------
// CAknPendingKeyEvent::~CAknPendingKeyEvent
// -----------------------------------------------------------------------------
//
CAknPendingKeyEvent::~CAknPendingKeyEvent()
    {
    }

// -----------------------------------------------------------------------------
// CAknPendingKeyEvent::HandleKeyReleased
// -----------------------------------------------------------------------------
//
TBool CAknPendingKeyEvent::HandleKeyReleased(const TRawEvent& /*aRawEvent*/)
    {
    TBool result(EFalse);
    TInt state = iState;
    Cancel();
    if (state == EShort)
        {
        // generate short powerkey
        iIsMadeUpEvent = ETrue;
        iFunctions->PostRawEvent(iPendingEvent); // contains powerkey down
        iIsMadeUpEvent = EFalse;

        result = EFalse; // let the up event go through
        }
    else if (state == ELong)
        {
        result = ETrue; // just block the original
        }
        
    else if (state == EWaitingUpEvent)
        {
        result = ETrue; // just block the original
        }
    
    return result;
    }

// -----------------------------------------------------------------------------
// CAknPendingKeyEvent::SetShortTimerForEvent
// -----------------------------------------------------------------------------
//
void CAknPendingKeyEvent::SetShortTimerForEvent(const TRawEvent &aRawEvent)
    {
    iPendingEvent = aRawEvent;
    After(KShortPress);
    iState = EShort;
    }

// -----------------------------------------------------------------------------
// CAknPendingKeyEvent::SetLongTimerForEvent
// -----------------------------------------------------------------------------
//
void CAknPendingKeyEvent::SetLongTimerForEvent(const TRawEvent &aRawEvent)
    {
    iEmulatedKey = aRawEvent.ScanCode();
    iPendingEvent = aRawEvent;
    After(KLongPress); 
    iState = ELong;    
    }

// -----------------------------------------------------------------------------
// CAknPendingKeyEvent::JustEmulateUpEvent
// -----------------------------------------------------------------------------
//
void CAknPendingKeyEvent::JustEmulateUpEvent(const TRawEvent &aRawEvent)
    {
    if (!IsActive())
        {
        iEmulatedKey = aRawEvent.ScanCode();
        iPendingEvent = aRawEvent;
        iStatus = KRequestPending;
        SetActive();
        iState = EWaitingUpEvent;
        }
    }

// -----------------------------------------------------------------------------
// CAknPendingKeyEvent::RunL
// -----------------------------------------------------------------------------
//
void CAknPendingKeyEvent::RunL()
    {
    switch(iState)
        {
        case EShort: // Generate end-key and start waiting again
            {
            iEmulatedKey = EStdKeyEnd; // please note that this is not standard end-key !!
            
            iIsMadeUpEvent = ETrue;
            iPendingEvent.Set(TRawEvent::EKeyDown,iEmulatedKey);
            iFunctions->PostRawEvent(iPendingEvent);
            iIsMadeUpEvent = EFalse;
            
            After(KLongPress); 
            iState = ELong;    
            break;
            }  
         
        case ELong:
            {
            iIsMadeUpEvent = ETrue;
            if (iEmulatedKey != EKeyNull)
                {
                iPendingEvent.Set(TRawEvent::EKeyUp,iEmulatedKey);
                iFunctions->PostRawEvent(iPendingEvent);
                iEmulatedKey = EKeyNull;
                }

            iPendingEvent.Set(TRawEvent::EKeyDown,EStdKeyDevice2);
            iFunctions->PostRawEvent(iPendingEvent);
            iIsMadeUpEvent = EFalse;
            
            iState = EBreathe;    
            break;
            }  
         
        default:
            break;
        }
    }
    
// -----------------------------------------------------------------------------
// CAknPendingKeyEvent::DoCancel
// -----------------------------------------------------------------------------
//    
void CAknPendingKeyEvent::DoCancel()
    {
    if (iEmulatedKey != EKeyNull)
        {
        iIsMadeUpEvent = ETrue;
        iPendingEvent.Set(TRawEvent::EKeyUp,iEmulatedKey);
        iFunctions->PostRawEvent(iPendingEvent);
        iEmulatedKey = EKeyNull;
        iIsMadeUpEvent = EFalse;
        }
  
    if (iState == EWaitingUpEvent)
        {
        TRequestStatus* sptr = &iStatus;
        User::RequestComplete(sptr, KErrNone);
        }
    else
        {
        CTimer::DoCancel();
        }
        
    iState = EBreathe;  
    }

// End of File
