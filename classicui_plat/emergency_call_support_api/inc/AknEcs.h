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
* Description:   Support for Emergency Calls.
*   Pressed keys are tracked in a buffer and CEmergencyNumberUtils
*   is used to find out if the buffer matches to emergency number.
*   Observers, if registered are called to notify them.
*
*
*/


#if !defined(__AKNECS_H__)
#define __AKNECS_H__

// INCLUDES
#include <babitflags.h>
#include <eikapp.h>
#include <eikdef.h>
#include "AknWsEventObserver.h"

class CPhCltEmergencyCall;
class CPhCltEmergencyCallObserver;


// CONSTANTS

// Maximum length of an emergency number
const TInt KAknEcsMaxMatchingLength = 6;

// Separator character for the emergency number string
_LIT( KAknEcsSeparator, " ");

// Maximum time in Microseconds between keys in a valid emergency call entry:
const TInt KEcsInterKeyTimeout = 4000000;

// Deprecated
const TInt KAknMaxEmergencyNumberString = 200;

// FORWARD DECLARATIONS

// Forward declarations; Full declaration comes later
class MAknEcsObserver;
class CAknMatchingCharacterQueue;


// CLASS DECLARATIONS

/**
* Central coordinating object in the emergency call system
* Objects of this class own the number queue and own the interface object to the stored
* emergency numbers.
*
* A phone client session is also open while constructed
*
*/
class CAknEcsDetector : public CBase, public MAknWsEventObserver
    {

public:

    /**
    * Enumeration to carry the state of the Ecs detector
    */
    enum TState
        {
        ENotFullyConstructed,
        EEmpty,
        ENoMatch,
        EPartialMatch, // Not in use.
        ECompleteMatch,
        ECompleteMatchThenSendKey,
        ECallAttempted
        };

public:
    /**
    * C++ destructor
    */
    IMPORT_C virtual ~CAknEcsDetector();

    /**
    * Two phase constructor for Ecs detector
    * Static method.
    */
    IMPORT_C static CAknEcsDetector* NewL();

    // From MAknWsEventObserver
    /**
    * Handle and event coming from the AppUi. Default implementation handles all keys
    * and updates the Status(), CurrentMatch(), and IndexOfCurrentMatch()
    *
    */
    IMPORT_C virtual void HandleWsEventL(const TWsEvent& aEvent,CCoeControl* aDestination );

    /**
    * Add a character to the emergency call buffer. This should be fed with both numberic
    * key presses and the Send key.
    *
    * @param aNewChar New character to emergency call buffer.
    */
    IMPORT_C void AddChar( TText aNewChar );

    /**
    * Set the entire contents of the emergency call buffer.  A reset is performed first, and then
    * the characters in the passed descriptor are added to the buffer.
    * Emergency number is matched only if there is not other content in the string.
    *
    * @param aNewBuffer Emergency call buffer.
    */
    IMPORT_C void SetBuffer( const TDesC& aNewBuffer );

    /**
    * Reset the buffer to a just initialized state.
    */
    IMPORT_C void Reset();

    /**
    * Returns the current state of the Ecs Detector
    *
    * @return The state of the object
    */
    IMPORT_C TState State();

    /**
    * Returns a pointer to the current matching number.
    *
    * @return A ptr descriptor into the currently matching text
    */
    IMPORT_C TPtrC CurrentMatch() const;

    /**
    * Sets the obserever of the EcsDetector
    */
    IMPORT_C void SetObserver( MAknEcsObserver* aNewObserver );

    /**
    * This method attaches the Ecs Detector to the current appui and the registers itself for
    * receiving all key presses parasitically.
    * This method is called when there is no requirement for the ECS to keep synchronized with a
    * visual buffer
    *
    * @return Success of the connection
    */
    IMPORT_C TBool ConnectToEventSource();

    /**
    * Closes the connection to the appui object opened by a previous call to ConnectToEventSource
    */
    IMPORT_C void CloseEventSource();

    /**
     * It is called whenever status is retrieved (by the client).
     *
     * @param aStatus It is the status of the phone.
     */
    virtual void HandlePhoneStatusL( const TInt aStatus );

    /**
    * Returns an index to the current character buffer where the emergency number
    * match begins. This value is between 0 and KAknEcsMaxMatchingLength, even if
    * there have been a large number characters input to the FIFO. Thus, it does not
    * take account of characters that have fallen out of the FIFO.
    *
    * The main use case for this is to allow clients to tell if the number was matched
    * from the beginning of the buffer (value 0).  Note that for emergency numbers of
    * length KAknEcsMaxMatchingLength will ALWAYS return 0 if there is a complete match.
    *
    * @return the index in the current buffer where the match starts
    */
    TInt IndexOfCurrentMatch() const;

protected:

    /**
    * Enumeration for the bit indices of iFlags
    * Used for substates or state modifiers
    */
    enum TBitFlagIndices
        {
        EEventSourceConnected = 0,
        ETestMode
        };

    /**
    * C++ constructor
    */
    IMPORT_C CAknEcsDetector(); // Use NewL to construct

    /**
    * 2nd stage construction.  All memory allocation is performed in this routine
    */
    IMPORT_C void ConstructL(); // Use NewL to construct

    /**
    * Calls the observer
    */
    IMPORT_C virtual void ReportEvent( TState aNewState );

    /**
    * Internal routine to set the state
    */
    IMPORT_C void SetState( TState newState );

    /**
    * Framework method that may be re-implemented in order to perform some check or put up UI
    * before the phone call is made
    * Implementation must not leave;
    *
    * @return   Whether or not to continue with the emergency call
    */
    IMPORT_C virtual TBool OfferEmergencyCall();

    /**
    * Static method that can be used as a cancel callback to the detector
    *
    * @return   Integer return for CPeriodic callbacks; 1 to continue periodic callbacks
    */
    static TInt CancelMatch( TAny* aAny );

private:
    /**
    * Utility routine to determine the new state of the module.
    */
    void DetermineState();

    /**
    * Wraps up the code to capture whatever keys are necessary when the emergency number
    */
    void CaptureKeys();

    /**
    * Uncaptures Send key (if necessary)
    */
    void RelinquishCapturedKeys();

    /**
    * Wraps up the code that acutally sets off the emergency call
    */
    void AttemptEmergencyCall();

public:
    /**
    * This callback is called by a CIdle object to state that the call has been
    * attempted.  This is called outside the event loop in order allow self-deletion of the
    * client object.
    *
    * State is set to CallAttempted by this method.
    *
    * @param aSelf
    */
    static TInt CallAttemptedCallback(TAny* aSelf);

private:
    // Constituent object: the character queue
    CAknMatchingCharacterQueue* iQueue;

    // Internal state of the detector
    TState iState;

    TBuf<KAknEcsMaxMatchingLength> iSpare_3;

    // Timer for match timeout
    CPeriodic* iKeyTimeoutTimer;

    // The observer
    MAknEcsObserver* iObserver;

    // A reference to the control environment
    CCoeEnv* iCoeEnv;

    // Flags
    TBitFlags16 iFlags;

    // To hold a captured key handle
    TInt iCapturedKey;

    /** Phone client interface of emergency call. */
    CPhCltEmergencyCall* iPhCltEmergencyCall;

    // Idle object for causing a delayed call attempted state
    CIdle* iIdler;

    /** Pointer to emergency call observer object */
    CPhCltEmergencyCallObserver* iEmergencyCallObserver;
    
    TInt iSpare_2;
    };

//
// MAknEcsObserver
//
// This interface is used to handle changes in state of the Emergency call detector.
//
//
class MAknEcsObserver
    {
public:
    /**
    * This event handler method provides a pointer to the detector and gives its state.
    * It is called at least every changed of state.  It may be called repeatedly on the same state
    */
    virtual void HandleEcsEvent(CAknEcsDetector* aDetector, CAknEcsDetector::TState aUpdatedState) = 0;
    };

#endif  // __AKNECS_H__
