/*
* Copyright (c) 2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  An implementation of a configurable key translation map.
*
*/


// INCLUDES
#include "AknKeyEventMap.h"
#include <e32std.h>
#include <e32math.h>
#include <barsc.h>
#include <barsread.h>
#include <bautils.h>
#include "AknKeyResource.h"
#include <aknkeyeventmap.rsg>
#include "AknAnimLogger.h"
#include "aknanimdllstd.h"

// CONSTANTS
#define STRIP_MODS  &0x0000FFFF
#define GET_MODS    &0xFFFF0000

// Key event map resource file.
_LIT( KAknKeyTableRsc, "z:\\resource\\AknKeyEventMap.rsc" );

// Publish & Subscribe device mode category.
const TInt32 KUidWinservCategoryValue = 0x10003B20;

// Publish & Subscribe device mode category as TUid.
const TUid KUidWinservCategory = { KUidWinservCategoryValue };

// Always pass policy.
_LIT_SECURITY_POLICY_PASS(KAlwaysPassPolicy);

// Only system application can access.
_LIT_SECURITY_POLICY_S0(KSysapOnlyPolicy, 0x100058F3);

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknKeyEventMap::CAknKeyEventMap
// -----------------------------------------------------------------------------
//
CAknKeyEventMap::CAknKeyEventMap(CAknAsynchTonePlayer& aSoundSession)
    : iDownEvents( KAknMaxComboKeys ), iUpEvents( KAknMaxComboKeys ), iSoundSession(aSoundSession)
    {    
    }

// -----------------------------------------------------------------------------
// CAknKeyEventMap::ConstructL
//
// Initializes member variables, reads the default keytables from a resource 
// file, instantiates P&S subscriber and opens the door for raw events.
// -----------------------------------------------------------------------------
//
void CAknKeyEventMap::ConstructL( MAnimGeneralFunctions* aFunctions )
    {
    iFunctions = aFunctions;

    if ( KAknMaxDeviceMode < 1 || KAknMaxDeviceMode > 15)
        {
        __AKNANIMLOGSTRING("CAknKeyEventMap::ConstructL ERROR: must have at least 1 and at most 15 device modes");
        User::Leave(KErrGeneral);
        }

    iCurrentDeviceMode = KAknModeDefault;
    iKeyBeacon.iKeyCode = EKeyNull;
    iKeyBeacon.iEventType = 0;
    iDownTimer = CPeriodic::New( CActive::EPriorityLow );
    iCombos = new (ELeave) RArray<RArray<TUint32>*>( KAknMaxComboKeys );
    
    iRepeatRate = KAknRepeatRate;
    iKeyPollInterval = static_cast<TTimeIntervalMicroSeconds32>(1000000./iRepeatRate);
    
    iConsume = EFalse;
    iIsCanceled = EFalse;
    
    iScanCodeIJustGenerated = -1;
    
    // Initialize keymap.
    const TAknKeyEvent nullEvent = { EKeyNull, EKeyNull, 0 };
    for ( TUint j = 0; j < KAknKeyMapRows; j++ )
        {
        for ( TUint i = 0; i < KAknKeyMapColumns; i++ )
            {
            iKeyMap[i][j] = nullEvent;
            }
        }
    
    // Load the default configuration.
    TRAPD( ierr, InitializeKeyTableFromResourceL( KAknKeyTableRsc ) );
    if ( ierr != KErrNone )
        {
        __AKNANIMLOGSTRING1( "Error initializing the key tables, %d", ierr );
        }

    if ( !IsKeyEventMapEnabled() )
        {
        return;
        }
    
    // Define Publish & Subscribe key
    TInt err = RProperty::Define( KUidWinservCategory, KAknPSDeviceMode, 
        RProperty::EInt, KAlwaysPassPolicy, KSysapOnlyPolicy );
    if ( err != KErrNone )
        {
        __AKNANIMLOGSTRING1("CAknKeyEventMap::ConstrucL() Problem defining The Key %d", err);
        }

    // Subscribe to Publish & Subscribe keys
    err = KErrNone;
    CAknKefSubscriber *sub = NULL;
    
    sub = CAknKefSubscriber::NewL( *this, KUidWinservCategory , KAknPSDeviceMode  );
    if ( sub )
        {        
        err = iKefSubscribers.Append( sub );
        if ( err != KErrNone )
            {
            delete sub;
            __AKNANIMLOGSTRING( "CAknKeyEventMap::ConstructL ERROR: device mode subscription failed." );
            // We could stop the boot here, but we can also continue, just without 
            // the device modes.
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknKeyEventMap::~CAknKeyEventMap
// -----------------------------------------------------------------------------
//
CAknKeyEventMap::~CAknKeyEventMap()
    {
    __AKNANIMLOGSTRING("CAknKeyEventMap::Destructor entered.");
    
    if ( iCombos )
        {
        const TInt count = iCombos->Count();
        for ( TInt i = count - 1; i >= 0; i-- ) 
            {
            (*iCombos)[i]->Close();
            delete (*iCombos)[i];
            iCombos->Remove(i);
            }
        iCombos->Close();
        delete iCombos;
        }
    
    delete iDownTimer;

    iUpEvents.Close();   
    iDownEvents.Close();
    iRepeatRates.Close();
    
    iKefSubscribers.ResetAndDestroy();
    iKefSubscribers.Close();
    }

// -----------------------------------------------------------------------------
// CAknKeyEventMap::IsKeyEventMapEnabled
// -----------------------------------------------------------------------------
//
TBool CAknKeyEventMap::IsKeyEventMapEnabled() const
    {
    return iKeyEventMapEnabled;
    }
    
// -----------------------------------------------------------------------------
// CAknKeyEventMap::OfferRawEvent
// 
// -----------------------------------------------------------------------------
//
TBool CAknKeyEventMap::OfferRawEvent( const TRawEvent& aRawEvent )
    {
    return OfferRawEvent(aRawEvent, EFalse);
    }    
    
// -----------------------------------------------------------------------------
// CAknKeyEventMap::OfferRawEvent
// 
// This is where the raw events end up in, and
// where we have to decide what to do with them.
// -----------------------------------------------------------------------------
//
TBool CAknKeyEventMap::OfferRawEvent( const TRawEvent& aRawEvent, TBool aSilentEvent )    
    {
    const TBool downEvent = ( aRawEvent.Type() == TRawEvent::EKeyDown );
    const TBool upEvent = ( aRawEvent.Type() == TRawEvent::EKeyUp );
    
    //
    // Raw events created by this CAknKeyEventMap itself: pass them on.
    //
    if ( ( downEvent || upEvent ) && 
         ( aRawEvent.ScanCode() == iScanCodeIJustGenerated ) )
        {
        if ( downEvent )
            {
            // Add this scan code to iUpEvents so we can generate
            // the appropriate raw UPs when the key press is finished.
            __AKNANIMLOGSTRING1("CAknKeyEventMap::OfferRawEvent adding %x to iUpEvents", iScanCodeIJustGenerated);
            TInt err = iUpEvents.Append( iScanCodeIJustGenerated );
            if ( err != KErrNone )  // never happened
                {
                __AKNANIMLOGSTRING("CAknKeyEventMap::OfferRawEvent ERROR appending up event!");
                }        
            }
    
        if ( upEvent )
            {
            // would be nice to .Remove() elements from iUpEvents here,
            // but that'd require another call to ResolveMapping(),
            //  -- .Remove() in CancelProcessingKeyPress() instead.
            }
            
        iScanCodeIJustGenerated = -1;
        return EFalse;  // not further processing for scan codes iJustGenerated.
        }       
        
    TInt err = KErrNone;
    iConsume = EFalse;  // very important to set this here.
    
    // log arrays
    for ( TInt i = 0 ; i < iDownEvents.Count() ; i++ )
        {
        __AKNANIMLOGSTRING2("CAknKeyEventMap::OfferRawEvent iDownEvents[%d] = %x", i, iDownEvents[i] );
        }
    for ( TInt i = 0 ; i < iUpEvents.Count() ; i++ )
        {
        __AKNANIMLOGSTRING2("CAknKeyEventMap::OfferRawEvent iUpEvents[%d] = %x", i, iUpEvents[i] );
        }
    
    // Down events
    if ( downEvent && aRawEvent.ScanCode() >= 0 )
        {
        iCurrentScanCode = aRawEvent.ScanCode(); 
        iPostMeOnUp.iKeyCode = EKeyNull;
        iPostMeOnUp.iEventType = 0;
        __AKNANIMLOGSTRING3( "CAknKeyEventMap::OfferRawEvent KeyDown scancode=%x mods=%x, we're in devicemode=%d", 
            iCurrentScanCode STRIP_MODS, iCurrentScanCode GET_MODS, iCurrentDeviceMode);
        
        // Combo support
        if ( iDownEvents.Count() < KAknMaxComboKeys )
            {
            err = iDownEvents.Append( aRawEvent.ScanCode() STRIP_MODS );
            if ( err != KErrNone )  // never happened
                {
                __AKNANIMLOGSTRING("CAknKeyEventMap::OfferRawEvent ERROR appending down event!");
                }                
            }
        else 
            {
            // User is trying to press more simultaneous keys than supported.
            // We have no problem with that, just ignore it.
            }
        
        // Resolve mapping for this event and set is as the beacon.
        iKeyBeacon = ResolveMapping();

        // Launch a CPeriodic so the duration of the keypress can be known.  
        // There's only one timer; for combos, it measures the time starting
        // from the first DOWN event of the combo.  If usability troubles appear,
        // try re-starting the timer for each participating key in a combo
        // (by removing the test against iDownEvents.Count())
        if ( iDownEvents.Count() < 2 )
            {            
            iKeyPressDuration = 0.0;
            iDownTimer->Cancel();
            iIsCanceled = EFalse; // set this before Start()
            iDownTimer->Start( iKeyPollInterval, iKeyPollInterval, 
                TCallBack( &KeyPressDuration, (TAny*) this ) );
            }

        if ( iKeyBeacon.iKeyCode > KAknKeyDisabled )
            {
            if ( ( iKeyBeacon.iEventType & KAknIsLongOnly ) )
                {
                // delayed posting of the short event when KAknIsLongOnly
                iPostMeOnUp = iKeyBeacon;  
                return iConsume;      // notice!  we're finished with this event.
                }
            else
                {
                if ( ( iKeyBeacon.iEventType & KAknIsShortKey ) == EFalse )
                    {
                    PostEvent( EAknPostRaw );
                    }
                else 
                    {
                    PostEvent( EAknPostKey );
                    }
                }
            }       
        
        // Emit a keyclick.
        if ( !aSilentEvent && iKeyBeacon.iKeyCode != KAknKeyDisabled )
            {
            if ( iKeyBeacon.iKeyCode > KAknKeyDisabled )
                {
                iSoundSession.KeyPressed( iKeyBeacon.iKeyCode STRIP_MODS );
                }
            else
                {
                iSoundSession.KeyPressed( aRawEvent.ScanCode() STRIP_MODS );
                }
            }
        
        return iConsume; // this was set by ResolveMapping
        }
    
    //  Up events    
    if ( upEvent )
        {
        iCurrentScanCode = aRawEvent.ScanCode(); 
        __AKNANIMLOGSTRING1("CAknKeyEventMap::OfferRawEvent KeyUp scancode=%x",aRawEvent.ScanCode());
        
        // Check whether this up event finishes a keypress we've been handling.
        TInt finishesKeyPress = 
            iDownEvents.Find( aRawEvent.ScanCode() STRIP_MODS );
        __AKNANIMLOGSTRING1("CAknKeyEventMap::OfferRawEvent finishesKeypress index %d", finishesKeyPress);
        __AKNANIMLOGSTRING1("CAknKeyEventMap::OfferRawEvent Duration =%f",iKeyPressDuration);

        // We got an UP for a known DOWN
        if ( finishesKeyPress != KErrNotFound ) 
            {
            
            if ( iPostMeOnUp.iKeyCode > KAknKeyDisabled && !iIsLongKeyPress  )
                {
                iKeyBeacon = iPostMeOnUp;
                if ( ( iKeyBeacon.iEventType & KAknIsShortKey ) == EFalse )
                    {
                    PostEvent( EAknPostRaw );
                    }
                else 
                    {
                    PostEvent( EAknPostKey );
                    }
                iPostMeOnUp.iKeyCode = EKeyNull;
                iPostMeOnUp.iEventType = 0;
                }

            iKeyBeacon = ResolveMapping();

            
            // Remove key from the down array
            iDownEvents.Remove( finishesKeyPress );
            
            // if it is mapped on the up array -> generate the up event
            TInt upKeyPressIndex = KErrNotFound;
            for ( TInt i = 0 ; i < iUpEvents.Count() ; i++ )
                {
                if ( (iUpEvents[i] STRIP_MODS) == ( iKeyBeacon.iKeyCode STRIP_MODS ) )
                    {
                    upKeyPressIndex = i;
                    break;
                    }
                }
            
            if ( upKeyPressIndex != KErrNotFound )
                {
                iScanCodeIJustGenerated = iUpEvents[upKeyPressIndex];
                TRawEvent rawEvent;
                rawEvent.Set( TRawEvent::EKeyUp, iScanCodeIJustGenerated );
                __AKNANIMLOGSTRING1("CAknKeyEventMap::OfferRawEvent POST RAW UP-EVENT for %x",iScanCodeIJustGenerated);
                iFunctions->PostRawEvent( rawEvent ) ;
                iUpEvents.Remove(upKeyPressIndex);
                iConsume = ETrue;
                }
                
            if ( !iDownEvents.Count() )
                {
                CancelProcessingKeyPress();
                }

            }
         else // finishesKeyPress == KErrNotFound
            {
            // probably a hardware/driver bug, in any case we're
            // confused now.
            __AKNANIMLOGSTRING("CAknKeyEventMap::OfferRawEvent INPUT IS CONFUSED: cancel key processing");            
            CancelProcessingKeyPress();
            }
        }
    
    return iConsume;
    }

// -----------------------------------------------------------------------------
// CAknKeyEventMap::CancelProcessingKeyPress
// -----------------------------------------------------------------------------

void CAknKeyEventMap::CancelProcessingKeyPress()
    {
    iDownTimer->Cancel();
    iIsCanceled = ETrue;
    iDownEvents.Reset();
    
    // be sure to send out all raw upevents or CKeyTranslator
    // will think the key is still being pressed.
    TRawEvent rawEvent;    
    while ( iUpEvents.Count() > 0 )
        {
        iScanCodeIJustGenerated = iUpEvents[0];
        rawEvent.Set( TRawEvent::EKeyUp, iScanCodeIJustGenerated );
        __AKNANIMLOGSTRING1("CAknKeyEventMap::CancelProcessingKeyPress POST RAW UP-EVENT for %x",iScanCodeIJustGenerated);
        iFunctions->PostRawEvent( rawEvent ) ;
        iUpEvents.Remove(0);
        }
        
    iUpEvents.Reset();
    iRepeats = 0;
    iKeyPressDuration = 0.0;
    iIsLongKeyPress = EFalse;                
    __AKNANIMLOGSTRING1("CAknKeyEventMap::CancelProcessingKeyPress Last beacon sent: %x", iKeyBeacon.iKeyCode);
    iKeyBeacon.iKeyCode = EKeyNull;
    iKeyBeacon.iEventType = 0;
    }
    

// -----------------------------------------------------------------------------
// CAknKeyEventMap::HandlePropertyChangedL
//
// Callback for Publish & Subscribe key events, it tracks
// the device mode changes for internal use.
// -----------------------------------------------------------------------------
//
void CAknKeyEventMap::HandlePropertyChangedL( 
        const TUid& aCategory, 
        const TUint aKey )
    {
    TInt keyValue( 0 );
    TInt err = KErrNone;
    err = RProperty::Get( aCategory, aKey, keyValue );
    if ( err == KErrNone )
        {
        switch( aKey )
            {
            case KAknPSDeviceMode:
                {
                __AKNANIMLOGSTRING1("CAknKeyEventMap::HandlePropertyChanged VALUE: %d",aKey);
                iCurrentDeviceMode = keyValue;
                
                const TInt count = iRepeatRates.Count();
                TUint16 currentMode = iCurrentDeviceMode; 
                for ( TInt ii = 0; ii < count; ii++ )
                    {
                    const TAknKeyRepeatRate& repeatRate = iRepeatRates[ ii ];
                    
                    if ( ( currentMode & repeatRate.iModeMask ) == 
                         repeatRate.iMode )
                        {
                        SetRepeatRate( repeatRate.iRate );
                        ii = count; // exit the loop.
                        }
                    }
                }
                break;
            default:
                {
                __AKNANIMLOGSTRING1("CAknKeyEventMap::HandlePropertyChanged GOT A P&S VALUE: %d",aKey);
                }
                break;
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknKeyEventMap::InitializeKeyTableFromResourceL
// -----------------------------------------------------------------------------
//
void CAknKeyEventMap::InitializeKeyTableFromResourceL(
        const TDesC& aConfigFile ) 
    {
    // Get a handle for the resource file.
    RFs fsSession;
    CleanupClosePushL( fsSession );
    TInt err = fsSession.Connect();
    if ( err != KErrNone )
        {
        User::Leave( err );
        }
    RResourceFile resourceFile;
    CleanupClosePushL( resourceFile );
    
    // Make sure we have the resource file.
    if ( BaflUtils::FileExists( fsSession, aConfigFile ) )
        {
        resourceFile.OpenL( fsSession, aConfigFile );
        }
    else
        {
        __AKNANIMLOGSTRING( "CAknKeyEventMap::InitializeKeyTableFromResourceL: no configuration file!");
        CleanupStack::PopAndDestroy(); // CleanupClosePushL.
        CleanupStack::PopAndDestroy(); // CleanupClosePushL.
        return;
        }
    
    // Confirm signature of the resource file.
    resourceFile.ConfirmSignatureL( 0 );
    
    // Now just get the resource chunk into a heap buffer and give it to a 
    // TResourceReader.
    HBufC8* res;
    res = resourceFile.AllocReadLC( R_AVKON_KEY_EVENT_MAP );
    
    TResourceReader theReader;
    theReader.SetBuffer( res );
    
    // Check version field.
    const TUint16 version = theReader.ReadUint16();
    if ( version != KAknKeyEventVersion1 )
        {
        __AKNANIMLOGSTRING( "CAknKeyEventMap::InitializeKeyTableFromResourceL: key event map disabled!");
        CleanupStack::PopAndDestroy( res );
        CleanupStack::PopAndDestroy(); // CleanupClosePushL.
        CleanupStack::PopAndDestroy(); // CleanupClosePushL.
        return;
        }
    
    iKeyEventMapEnabled = ETrue;
    theReader.ReadUint16(); // read flags, not in use yet.

    // Read repeat rates.
    const TUint count = theReader.ReadUint16();
    for ( TInt idx = 0; idx < count; idx++ )
        {
        TUint16 mode = theReader.ReadUint16();
        TUint16 modeMask = theReader.ReadUint16();
        TUint8 rate = theReader.ReadUint8();
        
        const TAknKeyRepeatRate repeatRate = 
            {
            mode,
            modeMask,
            rate
            };
        
        User::LeaveIfError( iRepeatRates.Append( repeatRate ) );
        }

    // Parses the resource data
    CAknKeyResourceArray* keyResourceArray = CAknKeyResourceArray::NewLC();
    CArrayPtrFlat<CAknKeyResource>* keyEvents = NULL;
    keyEvents = keyResourceArray->GetKeyEventsL( theReader );
    
    // At this point we have all the key event info; just put it in its place
    // in iKeyMap and iCombos.
    for ( TUint i = 0; i < (TUint)keyEvents->Count(); i++ )
        {
        CAknKeyResource* keyEvent = keyEvents->At(i);
        
        if ( keyEvent->GetScanCodes().Count() > 0 )
            {
            if ( (keyEvent->GetKeyCodes().Count() == keyEvent->GetDeviceModes().Count())
                 && (keyEvent->GetKeyCodes().Count() == keyEvent->GetEventTypes().Count()))
                {
                for ( TUint j = 0; 
                      j < (TUint)keyEvent->GetKeyCodes().Count(); 
                      j++ )
                    {            
                    TUint16 thisMode = keyEvent->GetDeviceModes().At(j);
                    RArray<TUint> theseModes;
                    CleanupClosePushL( theseModes );
                    
                    ResolveDeviceModeL( 
                        theseModes, 
                        keyEvent->GetDeviceModes().At(j) );
                    
                    TUint16 thisType = keyEvent->GetEventTypes().At(j);
                    for ( TUint k = 0; k < (TUint)theseModes.Count(); k++ )
                        {
                        TAknKeyDefinition thisKey;
                        thisKey.iScanCodes = &(keyEvent->GetScanCodes());
                        thisKey.iDeviceMode = theseModes[k];
                        thisKey.iKeyCode = keyEvent->GetKeyCodes().At(j);
                        thisKey.iEventType = thisType;
                        
                        TRAPD( error, SetKeyMappingL( thisKey ) );
                        if (error != KErrNone)
                            {
                            __AKNANIMLOGSTRING( "CAknKeyEventMap::InitializeKeyTableFromResourceL ERROR setting a mapping");
                            }
                        }
                    
                    CleanupStack::PopAndDestroy( &theseModes );
                    }
                }
            else
                {
                // Keyboard configuration is erroneous!
                // When multiple keycodes have been defined, they must have
                // an associated device mode, etc.
                __AKNANIMLOGSTRING( "CAknKeyEventMap::InitializeKeyTableFromResourceL ERROR: inconsistent data in KEY_EVENT" );
                User::Leave( KErrGeneral );
                }
            }
        else 
            {
            // Error. No scancodes for the key event.
            User::Leave( KErrGeneral );
            }    
        }
    
    // All done! The maps are now ready for use!
    CleanupStack::PopAndDestroy( 4 ); // keyResourceArray, res, 
                                      // &resourceFile, &fsSession
    }
    
// -----------------------------------------------------------------------------
// CAknKeyEventMap::SetRepeatRate
// -----------------------------------------------------------------------------
//
void CAknKeyEventMap::SetRepeatRate( TUint8 aRepeatRate )
    {
    if ( iRepeatRate > 0 && iRepeatRate < 32 )
        {        
        iRepeatRate = aRepeatRate;
        }
    }

// -----------------------------------------------------------------------------
// CAknKeyEventMap::SetKeyMappingL
//
// Sets the keycodes in iKeyMap and iCombos for one device mode.
// -----------------------------------------------------------------------------
//
void CAknKeyEventMap::SetKeyMappingL( const TAknKeyDefinition& aKey )
    {
    if ( aKey.iScanCodes->Count() == 1 )
        {        
        // Normal (=single key) mapping
        if ( (aKey.iEventType & KAknTypeShort) == KAknTypeShort )
            {
            // handle anykey definition for single presses.
            if ( aKey.iScanCodes->At(0) == KAknAnyKey)
                {
                for (TUint j = 0; j < KAknMaxScanCode; j++) 
                    {
                    iKeyMap[j][aKey.iDeviceMode].iShortPress = 
                        aKey.iKeyCode;
                    iKeyMap[j][aKey.iDeviceMode].iLongPress = 
                        aKey.iKeyCode;
                    iKeyMap[j][aKey.iDeviceMode].iEventType |=
                        ResolveEventType ( aKey.iEventType );
                    }
                }
            else 
                {                                
                // default is to set iLongPress to same as iShortPress, which in 
                // practice means that the default behavior for long keypresses is
                // to repeat.
                iKeyMap[aKey.iScanCodes->At(0)][aKey.iDeviceMode].iShortPress = 
                    aKey.iKeyCode;
                iKeyMap[aKey.iScanCodes->At(0)][aKey.iDeviceMode].iLongPress = 
                    aKey.iKeyCode;
                iKeyMap[aKey.iScanCodes->At(0)][aKey.iDeviceMode].iEventType |= 
                    ResolveEventType( aKey.iEventType );
                }
            }
        else if ( ((aKey.iEventType & KAknTypeLong) == KAknTypeLong) ||
                  ((aKey.iEventType & KAknTypeLongOnly) == KAknTypeLongOnly))
            {
            iKeyMap[aKey.iScanCodes->At(0)][aKey.iDeviceMode].iLongPress  = 
                aKey.iKeyCode;
            iKeyMap[aKey.iScanCodes->At(0)][aKey.iDeviceMode].iEventType |= 
                ResolveEventType( aKey.iEventType );
            }
        else
            {
            // Ignored.
            }
        }
    else
        {
        // Combo mapping
        RArray<TUint32>* newCombo = 
            new (ELeave) RArray<TUint32>( KAknMaxComboKeys );
        TUint i;
        TInt err = KErrNone;
        for ( i = 0; i < aKey.iScanCodes->Count(); i++ ) 
            {           
            err = newCombo->Append( aKey.iScanCodes->At(i) );
            if ( err != KErrNone ) 
                {
                User::Leave( err );  // we're trapped, just bail out.
                }
            }
        
        // For combos, the device mode information is encoded in to the
        // upper 16 bits of the Key Code value.    
        TUint32 keyMode = aKey.iKeyCode + ( aKey.iDeviceMode << 16 );
        newCombo->Insert( keyMode, 0 );
       
        TUint32 eventType = ResolveEventType( aKey.iEventType );
        newCombo->Insert( eventType, 1 );

        err = iCombos->Append( newCombo );
        if ( err != KErrNone )
            {
            User::Leave( KErrNone );
            }  
        }
    }

// -----------------------------------------------------------------------------
// CAknKeyEventMap::ResolveEventType
//
// A conversion between the eventtype representation in the resource file
// and iKeyMap.
// -----------------------------------------------------------------------------

TUint8 CAknKeyEventMap::ResolveEventType( TUint8 aEventType )
    {
    TUint8 result = 0;
    
    if ( (aEventType & (KAknTypeLongOnly)) == KAknTypeLongOnly )
        {
        result |= KAknIsLongOnly;
        result |= KAknIsLongPress;
        if ( (aEventType & KAknTypeKey) )
            {
            result |= KAknIsLongKey;
            }
        }
    else if ( (aEventType & KAknTypeLong) == KAknTypeLong )
        {
        result |= KAknIsLongPress;
        if ( (aEventType & KAknTypeKey) == KAknTypeKey )
            {
            result |= KAknIsLongKey;
            }
        }
    else if ( (aEventType & KAknTypeShort) == KAknTypeShort )
        {
        result = 0; // to be 101% sure
        if ( (aEventType & KAknTypeKey) == KAknTypeKey )
            {
            result |= KAknIsShortKey;
            }
        }

    return result;
    }
    
// -----------------------------------------------------------------------------
// CAknKeyEventMap::ResolveDeviceModeLC
//
// Given a TUint specifying a device mode, this function figures out 
// which rows of the iKeyMap are affected by a mapping. Only used in 
// setting up the key tables, not when querying data from them (just use 
// iCurrentDeviceMode then).
// -----------------------------------------------------------------------------
//
void CAknKeyEventMap::ResolveDeviceModeL( 
        RArray<TUint>& aModes, 
        TUint16 aMode )
    {
    TInt err;   
    TUint16 myMode = aMode;
    
    for ( TUint k = 0; k < KAknKeyMapRows; k++ )
        {
        // The loop index is now tested against aMode to see whether
        // there should be a non-null value in iKeyMap.
        
        if ( k == myMode )
            {            
            err = aModes.InsertInOrder( k );
            if ( err != KErrNone && err != KErrAlreadyExists )
                {
                User::Leave( err );  // we can't initialize the table.  fail.
                }
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknKeyEventMap::GetKeyMapping
//
// Returns mappings from iKeyMap.
// -----------------------------------------------------------------------------
//
TAknKeyBeacon CAknKeyEventMap::GetKeyMapping( 
        TUint16 aScanCode, 
        TUint16 aDeviceMode )
    {
    TAknKeyBeacon mapValue = { EKeyNull, 0 };      
    
    if ( aScanCode < KAknKeyMapColumns && aDeviceMode < KAknKeyMapRows )
        {
        // Look up the mode specific value, if any
        if ( iIsLongKeyPress == EFalse )
            {
            mapValue.iKeyCode = iKeyMap[aScanCode][aDeviceMode].iShortPress;
            }
        else
            {
            mapValue.iKeyCode = iKeyMap[aScanCode][aDeviceMode].iLongPress;
            }

        mapValue.iEventType = iKeyMap[aScanCode][aDeviceMode].iEventType;        
            
        // With this, we always return the default mapping (if any)
        // unless a mode-specific mapping was found.  
        if ( !mapValue.iKeyCode )
            {
            if ( iIsLongKeyPress == EFalse )
                {
                mapValue.iKeyCode = iKeyMap[aScanCode][ KAknModeDefault ].iShortPress; 
                }
            else
                {
                mapValue.iKeyCode = iKeyMap[aScanCode][ KAknModeDefault ].iLongPress;
                }
            mapValue.iEventType = iKeyMap[aScanCode][ KAknModeDefault ].iEventType;        
            }
        }
    return mapValue;
    }

// -----------------------------------------------------------------------------
// CAknKeyEventMap::GetComboMapping
//
// Returns mappings from iCombos.
// -----------------------------------------------------------------------------
//
TAknKeyBeacon CAknKeyEventMap::GetComboMapping( 
        RArray<TUint32>& aComboCandidate )
    {
    TAknKeyBeacon mapValue = { EKeyNull, 0 };        
    
    TUint i;
    TUint j;
    
    // First we check the first index of aComboCandidate
    // against the second index (= first scancode) of all combo
    // arrays in iCombos. If they match, then the i'th combo
    // array in iCombos could match aComboCandidate.
    //
    // iCombos[i][0] contains the key code that is to be returned for a 
    // succesful mapping, which introduces the offset-by-one in the following 
    // loops/lookups.also included in [i][0] are the device mode info and the 
    // event type info, both encoded into the upper 16 bits of iCombos[i][0].
    
    RArray<TUint> possibleMatch;  //  iCombos indices that might match
    for (i = 0; i < iCombos->Count(); i++) 
        {
        if ( (*(*iCombos)[i])[2] == aComboCandidate[0] && 
             ((*iCombos)[i])->Count()-2 == aComboCandidate.Count() ) 
            {
            possibleMatch.Append(i);
            __AKNANIMLOGSTRING1("CAknKeyEventMap::GetComboMapping ComboCandidate might hit iCombos[%d]",i);
            }                    
        }
    
    // If we have possibleMatches, then we just check whether any of
    // them matches aComboCandidate precisely. For the first match,
    // we return the keyvalue from the first element of the matching
    // combo array.
    if ( possibleMatch.Count() )
        {
        TInt8 isAMatch = -1;
        for ( i = 0; i < possibleMatch.Count() && isAMatch < 0; i++ ) 
            {
            // If isAMatch doesn't go to -1 within this loop, 
            // then we got a match.
            isAMatch = possibleMatch[i]; 
            for ( j = 2; j < (*(*iCombos)[possibleMatch[i]]).Count(); j++ ) 
                {
                // Try to find all scan codes of the current event 
                // in a combo definition.
                // NOTE: the order of the remaining scancodes is not matched,
                // as long as the first scancode is OK, the others can come in 
                // any order.
                TInt err = KErrNotFound;
                for ( TInt f = (*(*iCombos)[possibleMatch[i]]).Count()-1; f >= 0 ; f-- )
                    {
                    if ( (*(*iCombos)[possibleMatch[i]])[f] == aComboCandidate[j-2] )
                        {
                        err = f;
                        break;
                        }
                    }
                
                
                // err < 2 must be discarded, because the first two elements are
                // used for device mode & event type data.
                if ( err == KErrNotFound || err < 2)
                    {
                    // If a scan code cannot be found, this possibleMatch is 
                    // not a real match.
                    isAMatch = -1;
                    }
                }
            
            // If we get this far, a matching combination of keys has been 
            // found. Still need to check that the combo type (long/short) and 
            // the active device mode for this combo match those of the current
            // event.
            
            TUint16 comboMode = ((*(*iCombos)[possibleMatch[i]])[0] GET_MODS) >> 16;
            TUint16 comboType = ((*(*iCombos)[possibleMatch[i]])[1]);
            
            // If ..
            //    a matching set of scan codes was found,
            //    but it fails the long/short test,
            //    or it's defined for another device mode
            if ( isAMatch > -1 && 
                 ( iIsLongKeyPress && (!(comboType & KAknIsLongPress)  ) || 
                   ( ( iCurrentDeviceMode != comboMode ) && ( comboMode != KAknModeDefault ) ) ) )
                {
                isAMatch = -1;
                }
            }
        
        if ( isAMatch > -1  && isAMatch < iCombos->Count() )
            {
            // The correct return value can be found from the isAMatch'th 
            // combo-mapping's first element.
            mapValue.iKeyCode = (*(*iCombos)[isAMatch])[0] STRIP_MODS;
            mapValue.iEventType = (*(*iCombos)[isAMatch])[1];
            __AKNANIMLOGSTRING1("CAknKeyEventMap::GetComboMapping ComboCandidate DID hit iCombos[%d]", isAMatch);
            __AKNANIMLOGSTRING1("CAknKeyEventMap::GetComboMapping mapValue = %d", mapValue.iKeyCode);
            }
        }
    else 
        {
        mapValue.iKeyCode = EKeyNull;
        mapValue.iEventType = 0 ;
        }
    possibleMatch.Close();
    return mapValue;
    }

// -----------------------------------------------------------------------------
// CAknKeyEventMap::ResolveMapping
// 
// A little macro for figuring out how to map the current scan code.  
// -----------------------------------------------------------------------------
//
TAknKeyBeacon CAknKeyEventMap::ResolveMapping()
    {
    TAknKeyBeacon keyBeacon = 
    {
        EKeyNull, 0 
    };
    
    if ( iDownEvents.Count() > 1 && iDownEvents.Count() <= KAknMaxComboKeys ) 
        {
        // check that the current key is not disabled in this mode
        // if it is, then any combo containing this key must be 
        // blocked.
        TAknKeyBeacon tmp = GetKeyMapping( 
            iCurrentScanCode STRIP_MODS, iCurrentDeviceMode);
        
        if (tmp.iKeyCode != KAknKeyDisabled)
            {            
            keyBeacon = GetComboMapping( iDownEvents );

            // If we do not find combo, then try to map a single key.
            if ( keyBeacon.iKeyCode == EKeyNull )
                {
                __AKNANIMLOGSTRING( "CAknKeyEventMap::ResolveMapping Combo not found. Trying to get single." );
                keyBeacon = GetKeyMapping( 
                    iCurrentScanCode STRIP_MODS, iCurrentDeviceMode );
                }
            }
        else
            {
            __AKNANIMLOGSTRING("CAknKeyEventMap::ResolveMapping Ignoring combo because component is disabled");
            keyBeacon.iKeyCode = KAknKeyDisabled;
            keyBeacon.iEventType = 0;
            }
        }
    else if ( iDownEvents.Count() == 1 )
        {
        keyBeacon = GetKeyMapping( 
            iCurrentScanCode STRIP_MODS, iCurrentDeviceMode );
        }
    
    // Always consume succesful mappings, including EKeyDisabled
    if ( keyBeacon.iKeyCode != EKeyNull )
        {
        iConsume = ETrue;
        __AKNANIMLOGSTRING1( "CAknKeyEventMap::ResolveMapping mapping found: %x", keyBeacon.iKeyCode );
        }
    else
        {
        __AKNANIMLOGSTRING( "CAknKeyEventMap::ResolveMapping mapping not found" );
        }
    
    return keyBeacon;
    }

// -----------------------------------------------------------------------------
// CAknKeyEventMap::KeyPressDuration
//
// Callback for iDownTimer, used to distinguish between short and 
// long key presses and to handle repeats.
// -----------------------------------------------------------------------------
//
TInt CAknKeyEventMap::KeyPressDuration( TAny* aSelf )
    {
    if (aSelf != NULL)
        {
        CAknKeyEventMap* self = reinterpret_cast<CAknKeyEventMap*>(aSelf);
        
        self->iKeyPressDuration += ((TReal32)self->iKeyPollInterval.Int())/1e6;
        
        // Distinguish between short and long key presses.
        if ( self->iKeyPressDuration < KAknKeyLongThreshold )
            {
            // nothing to do.  if combo duration measurement is changed
            // so that each participating key resets the timer, then
            // un-comment the following lines:
            // self->iIsLongKeyPress = EFalse;
            // self->iKeyBeacon = self->ResolveMapping();
            }
        else 
            {            
            // Keypress turned out to be a long one
            if ( ! self->iIsLongKeyPress && ! self->iIsCanceled ) 
                {
                self->iIsLongKeyPress = ETrue;
                self->iKeyBeacon = self->ResolveMapping();
    
                // post the KAknTypeLongOnly event
                if ( self->iKeyBeacon.iKeyCode > KAknKeyDisabled
                    && (self->iKeyBeacon.iEventType & KAknIsLongPress))
                    {
                    if ( (self->iKeyBeacon.iEventType & KAknIsLongKey ) ) 
                        {
                        self->PostEvent( EAknPostKey );
                        }
                    else  
                        {
                        self->PostEvent( EAknPostRaw );
                        }
                    }
                }
            }
        
        // Handle repeats.
        if ( self->iKeyPressDuration >= KAknKeyLongThreshold && 
             self->iKeyBeacon.iKeyCode > KAknKeyDisabled ) 
            {
            if ( ( self->iKeyBeacon.iEventType & KAknIsLongKey ) )
                {
                self->iRepeats++;  // perhaps don't do this?
                self->PostEvent( EAknPostKey );
                }
            else
                {
                __AKNANIMLOGSTRING("CAknKeyEventMap::KeyPressDuration RAW repeat not sent (CKeyTranslator handles that)");   
                }
            }
        
        if ( self->iIsCanceled )
            {
            self->iDownTimer->Cancel();
            }
        }
    return KErrNone;
    } 

// -----------------------------------------------------------------------------
// CAknKeyEventMap::PostEvent
// -----------------------------------------------------------------------------

void CAknKeyEventMap::PostEvent(TUint aType) 
    {
    switch ( aType )
        {
        case EAknPostKey:
            TKeyEvent keyEvent;
            keyEvent.iCode = iKeyBeacon.iKeyCode;
            keyEvent.iScanCode = iCurrentScanCode STRIP_MODS;
            keyEvent.iRepeats = iRepeats;
            keyEvent.iModifiers = iCurrentScanCode GET_MODS; 
            iFunctions->PostKeyEvent(keyEvent);
            __AKNANIMLOGSTRING1( "CAknKeyEventMap::PostEvent() POST KEY code=%x", keyEvent.iCode);
            
            break;        
        
        case EAknPostRaw:
        default:
            TRawEvent rawEvent;
            rawEvent.Set(TRawEvent::EKeyDown, (iCurrentScanCode GET_MODS) + iKeyBeacon.iKeyCode );
            iScanCodeIJustGenerated = rawEvent.ScanCode();
            __AKNANIMLOGSTRING1( "CAknKeyEventMap::PostEvent() POST RAW scancode=%x", rawEvent.ScanCode());
            iFunctions->PostRawEvent( rawEvent );
            break;
        }
    iConsume = ETrue;
    }
    


// End of File
