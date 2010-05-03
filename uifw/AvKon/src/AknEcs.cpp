/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:   Support for Emergency Calls. Class Implementations.
*   Pressed keys are tracked in a buffer and CEmergencyNumberUtils
*   is used to find out if the buffer matches to emergency number.
*   Observers, if registered are called to notify them.
*
*
*/



// INCLUDES
#include <e32std.h>
#include "aknenv.h"
#include "aknappui.h"
#include "AknEcs.h"
#include <featmgr.h>
#include "AknDebug.h"

#include <cphcltemergencycall.h>
#include <mphcltemergencycallobserver.h>
#include <phclttypes.h>
#include <AvkonInternalCRKeys.h>
#include <PtiDefs.h>
#include <e32property.h>


// CLASS DECLARATIONS

/** Class for getting emergency call events */
NONSHARABLE_CLASS(CPhCltEmergencyCallObserver) : public CBase,
                                                 public MPhCltEmergencyCallObserver
    {
    public:
        /** Constructor */
        CPhCltEmergencyCallObserver(CAknEcsDetector* aParent);
        
        /** Destructor */
        ~CPhCltEmergencyCallObserver( );
        
       /**
         * This method is called when client's dial request is completed.
         *
         * @param aStatus error code of the success of the operation.
         */       
        virtual void HandleEmergencyDialL( const TInt aStatus );
    private:
        /** Pointer to the parent object that really handles the events. */
        CAknEcsDetector* iParent;
    };
    
    
CPhCltEmergencyCallObserver::CPhCltEmergencyCallObserver(CAknEcsDetector* aParent)
    :iParent(aParent)
    {
    }
    
CPhCltEmergencyCallObserver::~CPhCltEmergencyCallObserver()
    {
    }
    
void CPhCltEmergencyCallObserver::HandleEmergencyDialL( const TInt /*aStatus*/ )
    {
#ifdef AVKON_RDEBUG_INFO
    _LIT(KDebugDialRequestCompleted, "Dial request is completed");
    RDebug::Print(KDebugDialRequestCompleted);
#endif
    iParent->CallAttemptedCallback( iParent );    
    }
       
/**
* Class to hold the queue of keys (TText characters) provided to the emergency call detector.
*
* Performs matching of an emergency number with the current queue.
*
* No memory is allocated after its complete construction
*
*/
NONSHARABLE_CLASS(CAknMatchingCharacterQueue) : public CBase
    {
    public:
        /**
        * These statuses are returned by MatchText
        */
        enum TStatus
            {
            ENoMatch,
            ECompleteMatch
            };
    public:
        /**
        * C++ constructor
        */
        CAknMatchingCharacterQueue( CPhCltEmergencyCall* aPhCltEmergencyCall );

        /**
        * C++ destructor
        */
        ~CAknMatchingCharacterQueue( );

        /**
        * 2nd phase constructor
        */
        void ConstructL();

        /**
        * Method to reset the buffer by resetting the pointers.
        *
        */
        void Reset();

        /**
        * Adds the passed character code to the queue. All codes append to the queue;
        * none are ignored.
        *
        * @param aNewChar New char to the queue.
        */
        void AddChar( TText aNewChar );


        /**
        * Set the entire contents of the queue. If the new buffer is longer than
        * the queue, rest are stripped.
        *
        * @param aNewBuffer New content to the queue.
        */
        void SetBuffer( const TDesC& aNewBuffer );

        /**
        * The number of characters in the queue.  Resets to 0. Increases as characters are added
        * up to and equal to KAknEcsMaxMatchingLength
        *
        * @return   the number of characters queued and available for match.
        *
        */
        TInt Count() const;

        /**
        * Returns the status of the queue (which is automatically updated when AddChar and other non-const
        * API is called)
        * @return The status of the match. Nothing matching returns ENoMatch; 
        *         The whole sequence matching returns ECompleteMatch.
        */
        TStatus Status() const;

        /**
        * Returns a pointer to the current matching number. 
        *
        * @return A ptr descriptor into the currently matching text
        */
        TPtrC CurrentMatch() const;

        /**
        * Returns an index to the current character buffer where the emergency number
        * match begins.  This value is between 0 and KAknEcsMaxMatchingLength, even if
        * there have been a large number characters input to the FIFO. Thus, it does not
        * take account of characters that have fallen out of the FIFO.
        *
        * @return the index in the current buffer where the match starts
        */
        TInt IndexOfCurrentMatch() const;

    private:
        /**
        * Update the status of the queue
        */
        void UpdateStatus( TBool aBufferMode );

    private:
        // Emergency number buffer is as long as maximum sequence
        TBuf<KAknEcsMaxMatchingLength> iCharBuffer;

        /** Pointer to phone client interface of emergency call. Not owned */
        CPhCltEmergencyCall* iPhCltEmergencyCall; 
        TStatus iStatus;      // Holds the status;
        TInt iMatchPosition;  // Position in iCharBuffer from where the match starts.

        TAny* iSpare;
    };




// CLASS IMPLEMENTATIONS

/**
 * Local Panic Function and Panic Codes
 */

enum TAknEcsPanicCodes
    {
    EAknEcsPanicDialLLeft = 1,
    EAknEcsPanicBadState
    };

GLDEF_C void Panic(TAknEcsPanicCodes aPanic)
    {
    _LIT(KPanicCat,"AknEcs");
    User::Panic(KPanicCat, aPanic);
    }

//
// Queue used for storing and matching the keys used in emergency number detection
//
//


CAknMatchingCharacterQueue::CAknMatchingCharacterQueue( CPhCltEmergencyCall* aPhCltEmergencyCall ) 
        : iPhCltEmergencyCall( aPhCltEmergencyCall )
    {
    Reset();
    }

CAknMatchingCharacterQueue::~CAknMatchingCharacterQueue( )
    {
    }

void CAknMatchingCharacterQueue::ConstructL()
    {
    }

void CAknMatchingCharacterQueue::Reset()
    {
    iMatchPosition = 0;
    iCharBuffer.Zero();
    }

void CAknMatchingCharacterQueue::AddChar( TText aNewChar )
    {    
    TInt length = iCharBuffer.Length();
    TInt maxLenght = iCharBuffer.MaxLength();
    if (length >= maxLenght)
        {
        iCharBuffer = iCharBuffer.Right(length - 1);
        }
    iCharBuffer.Append( aNewChar );
    UpdateStatus( EFalse );
    }

void CAknMatchingCharacterQueue::SetBuffer( const TDesC& aNewBuffer )
    {    
    TInt maxLenght = iCharBuffer.MaxLength();
    TInt length = aNewBuffer.Length();
    if ( length > maxLenght )
        {
        length = maxLenght;
        }
    iCharBuffer = aNewBuffer.Left( length );
    UpdateStatus( ETrue );
    }

TInt CAknMatchingCharacterQueue::Count() const
    {
    return iCharBuffer.Length();
    }

CAknMatchingCharacterQueue::TStatus CAknMatchingCharacterQueue::Status() const
    {
    return iStatus;
    }

TPtrC CAknMatchingCharacterQueue::CurrentMatch() const
    {
    return TPtrC(iCharBuffer.Right(iCharBuffer.Length() - iMatchPosition));
    }

TInt CAknMatchingCharacterQueue::IndexOfCurrentMatch() const
    {
    return iMatchPosition;
    }

void CAknMatchingCharacterQueue::UpdateStatus( TBool aBufferMode )
    {
    TBool isEmergency = EFalse;
    TInt err = KErrNone;
    TPhCltTelephoneNumber buffer = iCharBuffer;
    if (iPhCltEmergencyCall)
        {
        err = iPhCltEmergencyCall->FindEmergencyPhoneNumber(buffer, isEmergency);        
        }
    if ( err != KErrNone )
        {
        isEmergency = EFalse;
        }

    TInt cbLength = iCharBuffer.Length();
    TInt bLength = buffer.Length();

    if ( aBufferMode && isEmergency && ( cbLength != bLength ) )
        {
        isEmergency = EFalse;
        }

    if ( isEmergency )
        {
        iMatchPosition = cbLength - bLength;
        iStatus = ECompleteMatch;
        }
    else
        {
        iMatchPosition = cbLength;
        iStatus = ENoMatch;
        }
    }


//
//
// Implementation of CAknEcsDetector
//  (Emergency Call Support Detector)
//
//

EXPORT_C CAknEcsDetector::CAknEcsDetector()
    {
    iCoeEnv = CCoeEnv::Static();
    iState = ENotFullyConstructed;
    }

EXPORT_C CAknEcsDetector::~CAknEcsDetector()
    {
    // Must close this in order to remove any observers from the AppUi's monitor
    CloseEventSource();
    delete iPhCltEmergencyCall;
    delete iEmergencyCallObserver;
    delete iQueue;
    delete iIdler;
    delete iKeyTimeoutTimer;
    }

EXPORT_C void CAknEcsDetector::ConstructL()
    {
    iEmergencyCallObserver = new (ELeave) CPhCltEmergencyCallObserver( this );
    // Phone client interface
    iPhCltEmergencyCall = CPhCltEmergencyCall::NewL( iEmergencyCallObserver );
    iQueue = new (ELeave) CAknMatchingCharacterQueue(iPhCltEmergencyCall);
    iQueue->ConstructL();

    DetermineState();

    // Idler for delaying the change of state to Call Attempted
    iIdler = CIdle::NewL( CActive::EPriorityLow );

    // Timer for timing the timeout between keys
    iKeyTimeoutTimer = CPeriodic::NewL( CActive::EPriorityLow);
    }

EXPORT_C CAknEcsDetector* CAknEcsDetector::NewL()
    { // static
    CAknEcsDetector* self = new (ELeave) CAknEcsDetector();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop(); //self
    return self;
    }

EXPORT_C TBool CAknEcsDetector::ConnectToEventSource()
    {
    if ( iFlags.IsClear( EEventSourceConnected ) )
        {
        TRAPD( err, iAvkonAppUi->EventMonitor()->AddObserverL(this) );
        iFlags.Assign( EEventSourceConnected, ( err == KErrNone ) );
        return ( err == KErrNone );
        }
    else
        {
        return ETrue;
        }
    }

EXPORT_C void CAknEcsDetector::CloseEventSource()
    {
    if (iFlags.IsSet( EEventSourceConnected ) )
        {
        CAknWsEventMonitor* eventMonitor = iAvkonAppUi->EventMonitor();
        eventMonitor->RemoveObserver(this);
        iFlags.Clear( EEventSourceConnected );
        }
    }

EXPORT_C void CAknEcsDetector::HandleWsEventL(const TWsEvent& aEvent, CCoeControl* /* aDestination  */)
    {
    if ( aEvent.Type() == EEventKeyDown || 
    // EKeyPhoneEnd/EKeyNo doesn't send EEVentKeyDown events, so EEventKey is used instead
    ( ( aEvent.Key()->iScanCode == EStdKeyNo ) && ( aEvent.Type() == EEventKey ) ) 
        )
        {
        AddChar( (TText)(aEvent.Key()->iScanCode ) ); // top 16 ( in Unicode build) bits removed
        }    
    }


EXPORT_C void CAknEcsDetector::AddChar( TText aNewChar )
    {
    iKeyTimeoutTimer->Cancel(); // there might be pending timeout; clear it
    if ( aNewChar == EStdKeyYes || aNewChar ==EKeyPhoneSend )
        {
        if ( State() == ECompleteMatch )
            {
            SetState( ECompleteMatchThenSendKey );
            }
        // else do nothing with it...
        }
    else
        {
        TText scanCode = aNewChar;
#ifdef RD_INTELLIGENT_TEXT_INPUT 
        // Convert scan code to number value here 
        // for 4*10, 3*11, half-qwerty key pad
        // The convert value is referenced from KeymapBuilder.pl in ptienginev2
        // Note: if the product change the scancode defintion,pls change the following 
        // map rules.
        TInt keyboardLayout = EPtiKeyboardNone;
        TInt errCode = RProperty::Get( KCRUidAvkon, KAknKeyBoardLayout, keyboardLayout );
        if ( errCode == KErrNone &&  ( keyboardLayout == EPtiKeyboardQwerty4x10 
            || keyboardLayout == EPtiKeyboardQwerty3x11 ) )
            {
            // using same conventor rule for 3x11 & 4x10
            if ( scanCode == EPtiKeyQwertyQ )
                {
                scanCode = EPtiKeyQwerty1;
                }
            else if ( scanCode == EPtiKeyQwertyW )
                {
                scanCode = EPtiKeyQwerty2;
                }
            else if ( scanCode == EPtiKeyQwertyE )
                {
                scanCode = EPtiKeyQwerty3;
                }        
            else if ( scanCode == EPtiKeyQwertyR )
                {
                scanCode = EPtiKeyQwerty4;
                }
            else if ( scanCode == EPtiKeyQwertyT )
                {
                scanCode = EPtiKeyQwerty5;
                }
            else if ( scanCode == EPtiKeyQwertyY )
                {
                scanCode = EPtiKeyQwerty6;
                }
            else if ( scanCode == EPtiKeyQwertyU )
                {
                scanCode = EPtiKeyQwerty7;
                }
            else if ( scanCode == EPtiKeyQwertyI )
                {
                scanCode = EPtiKeyQwerty8;
                }
            else if ( scanCode == EPtiKeyQwertyO )
                {
                scanCode = EPtiKeyQwerty9;
                }
            else if ( scanCode == EPtiKeyQwertyP )
                {
                scanCode = EPtiKeyQwerty0;
                }    
            }
        else if ( errCode == KErrNone && keyboardLayout == EPtiKeyboardHalfQwerty )
            {
            if ( scanCode == EPtiKeyQwertyE )
                {
                scanCode = EPtiKeyQwerty1;
                }
            else if ( scanCode == EPtiKeyQwertyT )
                {
                scanCode = EPtiKeyQwerty2;
                }
            else if ( scanCode == EPtiKeyQwertyU )
                {
                scanCode = EPtiKeyQwerty3;
                }        
            else if ( scanCode == EPtiKeyQwertyD )
                {
                scanCode = EPtiKeyQwerty4;
                }
            else if ( scanCode == EPtiKeyQwertyG )
                {
                scanCode = EPtiKeyQwerty5;
                }
            else if ( scanCode == EPtiKeyQwertyJ )
                {
                scanCode = EPtiKeyQwerty6;
                }
            else if ( scanCode == EPtiKeyQwertyU )
                {
                scanCode = EPtiKeyQwertyC;
                }
            else if ( scanCode == EPtiKeyQwertyB )
                {
                scanCode = EPtiKeyQwerty8;
                }
            else if ( scanCode == EPtiKeyQwertyM )
                {
                scanCode = EPtiKeyQwerty9;
                }
            else if ( scanCode == EPtiKeyQwertySpace )
                {
                scanCode = EPtiKeyQwerty0;
                }    
            }
#endif   //RD_INTELLIGENT_TEXT_INPUT    
        
        iQueue->AddChar( scanCode );
        DetermineState();
        iKeyTimeoutTimer->Start( KEcsInterKeyTimeout, KEcsInterKeyTimeout, TCallBack( CancelMatch, this ) );
        }
    }


void CAknEcsDetector::DetermineState()
    {
    TState bestState = ENoMatch;

    if ( iQueue->Count() == 0 )
        {
        bestState = EEmpty;
        }
    else
        {
        CAknMatchingCharacterQueue::TStatus matchStatus = iQueue->Status();

        switch ( matchStatus )
            {
            case CAknMatchingCharacterQueue::ENoMatch:
                bestState = ENoMatch;
                break;
            case CAknMatchingCharacterQueue::ECompleteMatch:
                bestState = ECompleteMatch;
                break;
            default:
                __ASSERT_DEBUG( 0, Panic(EAknEcsPanicBadState) );
                break;
            }
        SetState(bestState);
        }
    }

EXPORT_C void CAknEcsDetector::ReportEvent(TState aNewState )
    {
    if (iObserver)
        {
        iObserver->HandleEcsEvent( this, aNewState );
        }
    }


EXPORT_C TPtrC CAknEcsDetector::CurrentMatch() const
    {
    return iQueue->CurrentMatch();
    }

TInt CAknEcsDetector::IndexOfCurrentMatch() const
    {
    return iQueue->IndexOfCurrentMatch();
    }

EXPORT_C CAknEcsDetector::TState CAknEcsDetector::State()
    {
    return iState;
    }
EXPORT_C void CAknEcsDetector::SetBuffer( const TDesC& aNewBuffer )
    {
    iKeyTimeoutTimer->Cancel(); // there might be pending timeout; clear it
    iQueue->Reset();
    iQueue->SetBuffer(aNewBuffer);
    DetermineState();
    if ( State() == ECompleteMatch )
        {
        iKeyTimeoutTimer->Start( KEcsInterKeyTimeout,
            KEcsInterKeyTimeout, TCallBack( CancelMatch, this ) );
        }
    }

EXPORT_C void CAknEcsDetector::SetState( TState aNewState )
    {
    ReportEvent( aNewState );

    TInt oldState = iState;
    iState = aNewState;

    switch ( oldState )
        {
        // All these are OK to go to the next state without transition action:
        case ENotFullyConstructed:
        case EEmpty:
        case ECallAttempted:
        case ENoMatch:
        case ECompleteMatchThenSendKey:
            break;

        case ECompleteMatch:
            if ( aNewState == ECompleteMatchThenSendKey )
                {
                RelinquishCapturedKeys();

                TBool proceedWithCall = ETrue;
                proceedWithCall = OfferEmergencyCall();
                if ( proceedWithCall )
                    {
                    AttemptEmergencyCall();
                    }
                else
                    {  // Pass through this state immediately
                    iQueue->Reset();
                    SetState( EEmpty );
                    }
                }
            break;

        default:
            break;

        }
    }

EXPORT_C void CAknEcsDetector::Reset()
    {
    iQueue->Reset();
    SetState( EEmpty );
    }

/**
* This may be re-implemented to add a confirm query. Re-implementation must not leave
*
*/
EXPORT_C TBool CAknEcsDetector::OfferEmergencyCall()
    {
    return ETrue;
    }

void CAknEcsDetector::CaptureKeys()
    {
    // Capture Send Key
    RWindowGroup& groupWin=iCoeEnv->RootWin();
    iCapturedKey=groupWin.CaptureKey( EStdKeyYes, 0, 0);
    }

void CAknEcsDetector::RelinquishCapturedKeys()
    {
    RWindowGroup& groupWin=iCoeEnv->RootWin();
    groupWin.CancelCaptureKey( iCapturedKey );
    }

void CAknEcsDetector::AttemptEmergencyCall()
    {
#ifdef AVKON_RDEBUG_INFO
    _LIT(KDebugAttemptEmergencyCall, "Attempt Emergency Call From Detector");
    RDebug::Print(KDebugAttemptEmergencyCall);
#endif

    TRAPD( err, iPhCltEmergencyCall->DialEmergencyCallL( CurrentMatch() ) );
    __ASSERT_DEBUG( err==KErrNone, Panic( EAknEcsPanicDialLLeft ) );
    if(err != KErrNone)
        {
        err = KErrNone;
        }
    }

EXPORT_C void CAknEcsDetector::SetObserver( MAknEcsObserver* aObserver )
    {
    iObserver = aObserver;
    }

    /**
     * It is called whenever status is retrieved (by the client).
     *
     * @param aStatus It is the status of the phone.
     */
void CAknEcsDetector::HandlePhoneStatusL( const TInt /* aStatus */ )
    {
    }

    /**
    * This is meant to be called asynchronously in order for the Observer to destroy itself
    *
    */
TInt CAknEcsDetector::CallAttemptedCallback(TAny* aSelf)
    { // static
    REINTERPRET_CAST(CAknEcsDetector*,aSelf)->SetState( ECallAttempted );
#ifdef AVKON_RDEBUG_INFO
    _LIT(KDebugCallAttemptedCallback, "CallAttemptedCallback");
    RDebug::Print(KDebugCallAttemptedCallback);
#endif
    return 0;
    }

TInt CAknEcsDetector::CancelMatch(TAny* aThis)
    {
    static_cast<CAknEcsDetector*>(aThis)->Reset();
    static_cast<CAknEcsDetector*>(aThis)->iKeyTimeoutTimer->Cancel();
    return 0; // Do not repeat the operation
    }

// End of File
