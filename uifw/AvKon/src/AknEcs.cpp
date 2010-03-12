/*
* Copyright (c) 2002-2010 Nokia Corporation and/or its subsidiary(-ies).
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

#include <CPhCltEmergencyCall.h>
#include <MPhCltEmergencyCallObserver.h>
#include <PhCltTypes.h>
#include <AvkonInternalCRKeys.h>
#include <PtiDefs.h>
#include <e32property.h>
#include <AiwCommon.hrh>
#include <aiwdialdata.h>
#include <AiwServiceHandler.h>
#include <centralrepository.h>

#include "akntrace.h"

const TInt KAknKeyScanCodeBegin = 33;
const TInt KAknKeyScanCodeEnd   = 126;

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
            ECompleteMatch,
            EServiceNumMatch
            };
    public:
        /**
        * C++ constructor
        *
        * @param aPhCltEmergencyCall  Emergency call client
        * @param aServiceCallEnabled  Is service call feature enabled during device or key lock.
        */
        CAknMatchingCharacterQueue( CPhCltEmergencyCall* aPhCltEmergencyCall, TBool aServiceCallEnabled );

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

        /**
        * Validates the service number.
        *
        * @param aNumber Service number to be validated from CenRep.
        *
        * @return Returns ETrue if aNumber is a service number, EFalse if not.
        */
        TBool ValidateServiceNumberL( const TDesC& aNumber );

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
        TBool iServiceCallFeature;  // True if service call feature is enabled.

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


CAknMatchingCharacterQueue::CAknMatchingCharacterQueue( CPhCltEmergencyCall* aPhCltEmergencyCall, TBool aServiceCallEnabled )
        : iPhCltEmergencyCall( aPhCltEmergencyCall ), iServiceCallFeature( aServiceCallEnabled )
    {
    _AKNTRACE_FUNC_ENTER;
    Reset();
    _AKNTRACE_FUNC_EXIT;
    }

CAknMatchingCharacterQueue::~CAknMatchingCharacterQueue( )
    {
    }

void CAknMatchingCharacterQueue::ConstructL()
    {
    }

void CAknMatchingCharacterQueue::Reset()
    {
    _AKNTRACE_FUNC_ENTER;
    iMatchPosition = 0;
    iCharBuffer.Zero();
    _AKNTRACE_FUNC_EXIT;
    }

void CAknMatchingCharacterQueue::AddChar( TText aNewChar )
    {    
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "[%s][%s] aNewChar: %s", "CAknMatchingCharacterQueue", 
        		__FUNCTION__,&aNewChar);
    
    TInt length = iCharBuffer.Length();
    TInt maxLenght = iCharBuffer.MaxLength();
    if (length >= maxLenght)
        {
        iCharBuffer = iCharBuffer.Right(length - 1);
        }
    iCharBuffer.Append( aNewChar );
    UpdateStatus( EFalse );
    _AKNTRACE_FUNC_EXIT;
    }

void CAknMatchingCharacterQueue::SetBuffer( const TDesC& aNewBuffer )
    {    
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "[%s][%s] aNewBuffer: %s", "CAknMatchingCharacterQueue", 
            		__FUNCTION__,&aNewBuffer);
    
    TInt maxLenght = iCharBuffer.MaxLength();
    TInt length = aNewBuffer.Length();
    if ( length > maxLenght )
        {
        length = maxLenght;
        }
    iCharBuffer = aNewBuffer.Left( length );
    UpdateStatus( ETrue );
    _AKNTRACE_FUNC_EXIT;
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
    _AKNTRACE_FUNC_ENTER;
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
    else if ( iServiceCallFeature && cbLength >= KAknServiceCallMinLength )
        {
        // Check if this is a service call
        TBool isServiceNum = EFalse;
        TRAP_IGNORE( isServiceNum = ValidateServiceNumberL( iCharBuffer ) );

        if ( isServiceNum )
            {
            iMatchPosition = 0;
            iStatus = EServiceNumMatch;
            }
        else
            {
            iMatchPosition = cbLength;
            iStatus = ENoMatch;
            }
        }
    else
        {
        iMatchPosition = cbLength;
        iStatus = ENoMatch;
        }
    _AKNTRACE( "[%s][%s] iStatus: %d", "CAknMatchingCharacterQueue", 
                		__FUNCTION__,iStatus );
    _AKNTRACE_FUNC_EXIT;
    }

// -----------------------------------------------------------------------------
// CAknMatchingCharacterQueue::ValidateServiceNumber
// 
// Validates the service phone number.
// -----------------------------------------------------------------------------
//
TBool CAknMatchingCharacterQueue::ValidateServiceNumberL( const TDesC& aNumber )
    {
    _AKNTRACE_FUNC_ENTER;
	TBool isServiceNum = EFalse;
    HBufC* serviceNum = HBufC::NewLC( KAknEcsMaxMatchingLength );
    CRepository* cenRep = CRepository::NewLC( KCRUidAvkon );
    TPtr bufPtr = serviceNum->Des();

    if( cenRep->Get( KAknServiceCallNumber, bufPtr ) != KErrNone )
        {
        CleanupStack::PopAndDestroy( cenRep );
        CleanupStack::PopAndDestroy( serviceNum );
        return EFalse;
        }

    // Check if aNumber matches serviceNum
    if ( aNumber.Compare( *serviceNum ) == 0 )
        {
        isServiceNum = ETrue;
		}

    CleanupStack::PopAndDestroy( cenRep );
    CleanupStack::PopAndDestroy( serviceNum );
    _AKNTRACE_FUNC_EXIT;
    return isServiceNum;
    }

//
//
// Implementation of CAknEcsDetector
//  (Emergency Call Support Detector)
//
//

EXPORT_C CAknEcsDetector::CAknEcsDetector()
    {
    _AKNTRACE_FUNC_ENTER;
    iCoeEnv = CCoeEnv::Static();
    iState = ENotFullyConstructed;
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C CAknEcsDetector::~CAknEcsDetector()
    {
    _AKNTRACE_FUNC_ENTER;
    // Must close this in order to remove any observers from the AppUi's monitor
    CloseEventSource();
    delete iPhCltEmergencyCall;
    delete iEmergencyCallObserver;
    delete iQueue;
    delete iIdler;
    delete iKeyTimeoutTimer;
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CAknEcsDetector::ConstructL()
    {
    _AKNTRACE_FUNC_ENTER;
    iEmergencyCallObserver = new (ELeave) CPhCltEmergencyCallObserver( this );
    // Phone client interface
    iPhCltEmergencyCall = CPhCltEmergencyCall::NewL( iEmergencyCallObserver );

    // Check if service call is allowed during device and key lock
    iServiceCallEnabled = 
        FeatureManager::FeatureSupported( KFeatureIdFfServiceCallWhilePhoneLocked );

    iQueue = new (ELeave) CAknMatchingCharacterQueue( iPhCltEmergencyCall, iServiceCallEnabled );
    iQueue->ConstructL();

    DetermineState();

    // Idler for delaying the change of state to Call Attempted
    iIdler = CIdle::NewL( CActive::EPriorityLow );

    // Timer for timing the timeout between keys
    iKeyTimeoutTimer = CPeriodic::NewL( CActive::EPriorityLow);
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C CAknEcsDetector* CAknEcsDetector::NewL()
    { // static
    _AKNTRACE_FUNC_ENTER;
    CAknEcsDetector* self = new (ELeave) CAknEcsDetector();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop(); //self
    _AKNTRACE_FUNC_EXIT;
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
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "[%s][%s] aEvent.type(): %d, aEvent.Key()->iScanCode :%d", "CAknEcsDetector", 
                            		__FUNCTION__,aEvent.Type(),aEvent.Key()->iScanCode );
    if ( aEvent.Type() == EEventKeyDown || 
        // EKeyPhoneEnd/EKeyNo doesn't send EEVentKeyDown events, so EEventKey is used instead
       ( ( aEvent.Key()->iScanCode == EStdKeyNo ) && ( aEvent.Type() == EEventKey ) ) )
        {
        AddChar( (TText)(aEvent.Key()->iScanCode ) ); // top 16 ( in Unicode build) bits removed
        }

    if ( iServiceCallEnabled )
        {
        // When Cancel is pressed we need to clear the queue
        if ( iState == EServiceNumMatch && aEvent.Type() == EEventPointer && 
        	   aEvent.Pointer()->iType == TPointerEvent::EButton1Down )
            {
            // Clear the queue, set state to EEmpty, and cancel any pending timeout
            Reset();
            iKeyTimeoutTimer->Cancel();
            }
        }
    _AKNTRACE_FUNC_EXIT;
    }


EXPORT_C void CAknEcsDetector::AddChar( TText aNewChar )
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "[%s][%s] aNewChar: %s", "CAknEcsDetector", 
                                		__FUNCTION__, &aNewChar );

    if (aNewChar == EKeyQwertyOn || aNewChar == EKeyQwertyOff)
        { 
        _AKNTRACE_FUNC_EXIT;
        return;   // return directly if the aNewChar is slide open/closed.
        }
	
    iKeyTimeoutTimer->Cancel(); // there might be pending timeout; clear it
    if ( aNewChar == EStdKeyYes || aNewChar == EKeyPhoneSend )
        {
        if ( iServiceCallEnabled )
            {
            if ( iState == ECompleteMatch || iState == EServiceNumMatch )
                {
                _AKNTRACE( "[%s][%s] SetState( ECompleteMatchThenSendKey )", "CAknEcsDetector", 
                                            		    __FUNCTION__ );
                SetState( ECompleteMatchThenSendKey );
                }
            }
        else
            {
            if ( iState == ECompleteMatch )
                {
                _AKNTRACE( "[%s][%s] SetState( ECompleteMatchThenSendKey )", "CAknEcsDetector", 
                                                        __FUNCTION__ );
                SetState( ECompleteMatchThenSendKey );
                }
            }
        // else do nothing with it...
        }
    else
        {
        TText scanCode = aNewChar;

        if ( scanCode < KAknKeyScanCodeBegin || scanCode > KAknKeyScanCodeEnd )
            {
            // Just return since it is an invalid character
            return;
            }

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
    _AKNTRACE_FUNC_EXIT;
    }


void CAknEcsDetector::DetermineState()
    {
    _AKNTRACE_FUNC_ENTER;
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
            case CAknMatchingCharacterQueue::EServiceNumMatch:
                if ( iServiceCallEnabled )
                    {
                    bestState = EServiceNumMatch;
                    break;
                    }
                // Fall through to default case if service call feature is off
            default:
                __ASSERT_DEBUG( 0, Panic(EAknEcsPanicBadState) );
                break;
            }
        SetState(bestState);
        }
    _AKNTRACE( "[%s][%s] bestState: %d", "CAknEcsDetector", 
                                    		__FUNCTION__, bestState );
    _AKNTRACE_FUNC_EXIT;
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
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "[%s][%s] aNewBuffer: %s", "CAknEcsDetector", 
                                        		__FUNCTION__, &aNewBuffer );
        
    iKeyTimeoutTimer->Cancel(); // there might be pending timeout; clear it
    iQueue->Reset();
    iQueue->SetBuffer(aNewBuffer);
    DetermineState();

    if ( iServiceCallEnabled )
        {
        if ( iState == ECompleteMatch || iState == EServiceNumMatch )
            {
            iKeyTimeoutTimer->Start( KEcsInterKeyTimeout,
                KEcsInterKeyTimeout, TCallBack( CancelMatch, this ) );
            }
        }
    else
        {
        if ( iState == ECompleteMatch )
            {
            _AKNTRACE( "[%s][%s] State() == ECompleteMatch ", "CAknEcsDetector", 
                                                		    __FUNCTION__ );
            iKeyTimeoutTimer->Start( KEcsInterKeyTimeout,
                KEcsInterKeyTimeout, TCallBack( CancelMatch, this ) );
            }
        }
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CAknEcsDetector::SetState( TState aNewState )
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "[%s][%s] aNewState: %d", "CAknEcsDetector", 
                                            		__FUNCTION__, aNewState );
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
                    _AKNTRACE( "[%s][%s] Attempt Emergency Call", "CAknEcsDetector", 
                                                                		__FUNCTION__);
                    AttemptEmergencyCall();
                    }
                else
                    {  // Pass through this state immediately
                    _AKNTRACE( "[%s][%s] Reset", "CAknEcsDetector", __FUNCTION__);
                    iQueue->Reset();
                    SetState( EEmpty );
                    }
                }
            break;

        case EServiceNumMatch:
            if ( iServiceCallEnabled )
                {
                if ( aNewState == ECompleteMatchThenSendKey )
                    {
                    RelinquishCapturedKeys();
                    _AKNTRACE( "[%s][%s] Make Service Call", "CAknEcsDetector", 
                                                                		__FUNCTION__);
                    TRAP_IGNORE( MakeServiceCallL() );
                    }
                }
            break;

        default:
            break;

        }
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CAknEcsDetector::Reset()
    {
    _AKNTRACE_FUNC_ENTER;
    iQueue->Reset();
    SetState( EEmpty );
    _AKNTRACE_FUNC_EXIT;
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
    _AKNTRACE_FUNC_ENTER;
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
    _AKNTRACE_FUNC_EXIT;
    }

void CAknEcsDetector::MakeServiceCallL()
    {
    _AKNTRACE_FUNC_ENTER;
    if ( iServiceCallEnabled )
        {
        CAiwServiceHandler* aiwServiceHandler = CAiwServiceHandler::NewLC();
        RCriteriaArray interest;
        CleanupClosePushL( interest );

        CAiwCriteriaItem* criteria = CAiwCriteriaItem::NewLC( KAiwCmdCall,
                                         KAiwCmdCall, _L8( "*" ) );
        TUid base;
        base.iUid = KAiwClassBase;
        criteria->SetServiceClass( base );
        User::LeaveIfError( interest.Append( criteria ) );
        aiwServiceHandler->AttachL( interest );

        CAiwDialData* dialData = CAiwDialData::NewLC();
        dialData->SetCallType( CAiwDialData::EAIWForcedCS );
        dialData->SetPhoneNumberL( CurrentMatch() );
        dialData->SetWindowGroup( AIWDialData::KAiwGoToIdle );

        CAiwGenericParamList& paramList = aiwServiceHandler->InParamListL();
        dialData->FillInParamListL( paramList );

        TRAPD( err, aiwServiceHandler->ExecuteServiceCmdL( KAiwCmdCall, paramList,
                    aiwServiceHandler->OutParamListL(), 0, NULL ) );
        __ASSERT_DEBUG( err == KErrNone, Panic( EAknEcsPanicDialLLeft ) );

        //reset the queue
        iQueue->Reset();

        CleanupStack::PopAndDestroy( dialData );
        CleanupStack::PopAndDestroy( criteria );
        CleanupStack::PopAndDestroy( &interest );
        CleanupStack::PopAndDestroy( aiwServiceHandler );

        if( err != KErrNone )
            {
            User::Leave( err );
            }
        }
    _AKNTRACE_FUNC_EXIT;
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
    _AKNTRACE_FUNC_ENTER;
    REINTERPRET_CAST(CAknEcsDetector*,aSelf)->SetState( ECallAttempted );
#ifdef AVKON_RDEBUG_INFO
    _LIT(KDebugCallAttemptedCallback, "CallAttemptedCallback");
    RDebug::Print(KDebugCallAttemptedCallback);
#endif
    _AKNTRACE_FUNC_EXIT;
    return 0;
    }

TInt CAknEcsDetector::CancelMatch(TAny* aThis)
    {
    _AKNTRACE_FUNC_ENTER;
    static_cast<CAknEcsDetector*>(aThis)->Reset();
    static_cast<CAknEcsDetector*>(aThis)->iKeyTimeoutTimer->Cancel();
    _AKNTRACE_FUNC_EXIT;
    return 0; // Do not repeat the operation
    }

// End of File
