/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Gesture recognition engine.
*
*/

#include <akntouchgesturefwobserver.h>

#include "akntouchgesturefwdefs.h"
#include "akntouchgesturefwbaserecognizer.h"
#include "akntouchgesturefwdragrecognizer.h"
#include "akntouchgesturefwevent.h"
#include "akntouchgesturefwflickrecognizer.h"
#include "akntouchgesturefwpinchrecognizer.h"
#include "akntouchgesturefwpointerstate.h"
#include "akntouchgesturefwrecognitionengine.h"
#include "akntouchgesturefwsettings.h"
#include "akntouchgesturefwtaprecognizer.h"

using namespace AknTouchGestureFw;

// Array of gesture groups
const TAknTouchGestureFwGroup KGestureGroup[] =
    {
    EAknTouchGestureFwGroupTap,
    EAknTouchGestureFwGroupDrag,
    EAknTouchGestureFwGroupFlick,
    EAknTouchGestureFwGroupPinch
    };

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwRecognitionEngine* CAknTouchGestureFwRecognitionEngine::NewL(
        MAknTouchGestureFwObserver& aObserver, CCoeControl* aControl )
    {
    CAknTouchGestureFwRecognitionEngine* self =
        CAknTouchGestureFwRecognitionEngine::NewLC( aObserver, aControl );
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwRecognitionEngine*
    CAknTouchGestureFwRecognitionEngine::NewLC(
            MAknTouchGestureFwObserver& aObserver, CCoeControl* aControl )
    {
    CAknTouchGestureFwRecognitionEngine* self
        = new ( ELeave ) CAknTouchGestureFwRecognitionEngine( aObserver,
            aControl );
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }


// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwRecognitionEngine::~CAknTouchGestureFwRecognitionEngine()
    {
    delete iPointerState;
    delete iSettings;
    iRecognizers.ResetAndDestroy();
    iRecognizers.Close();
    }


// ---------------------------------------------------------------------------
// Notifies the observer about a gesture event.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwRecognitionEngine::NotifyObserverL(
        MAknTouchGestureFwEvent& aEvent )
    {
#ifdef GFW_DEBUG_TRACE_INPUTOUTPUT
    AknTouchGestureFwUtils::DumpGestureEvent( aEvent );
#endif  // GFW_DEBUG_TRACE_INPUTOUTPUT

    iObserver.HandleTouchGestureL( aEvent );
    }


// ---------------------------------------------------------------------------
// Sets the gesture interest.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwRecognitionEngine::SetGestureInterestL(
    TUint aGestureGroups )
    {
    TUint newGestureInterest( aGestureGroups );

    // Create recognizers on demand.
    if ( newGestureInterest & EAknTouchGestureFwGroupPinch )
        {
        CreateRecognizerL( EAknTouchGestureFwGroupPinch );
        }

    if ( newGestureInterest & EAknTouchGestureFwGroupDrag )
        {
        CreateRecognizerL( EAknTouchGestureFwGroupDrag );
        }

    if ( newGestureInterest & EAknTouchGestureFwGroupFlick )
        {
        CreateRecognizerL( EAknTouchGestureFwGroupFlick );
        }

    if ( newGestureInterest & EAknTouchGestureFwGroupTap )
        {
        CreateRecognizerL( EAknTouchGestureFwGroupTap );
        }

    iGestureInterest = newGestureInterest;

    // Enable/disable recognizers.
    UpdateRecognizersForInterest( newGestureInterest );
    }


// ---------------------------------------------------------------------------
// Returns the current gesture interest.
// ---------------------------------------------------------------------------
//
TUint CAknTouchGestureFwRecognitionEngine::GestureInterest() const
    {
    return iGestureInterest;
    }


// ---------------------------------------------------------------------------
// Cancels the gesture recognition.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwRecognitionEngine::CancelRecognizing()
    {
    if ( iSingleRecognizing || iMultiRecognizing )
        {
        iSingleRecognizing = EFalse;
        iMultiRecognizing = EFalse;

        iPointerState->Reset();

        for ( TInt i = 0; i < iRecognizers.Count(); i++ )
            {
            iRecognizers[ i ]->CancelRecognizing();
            }
        }
    }


// ---------------------------------------------------------------------------
// Handles pointer events.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwRecognitionEngine::HandlePointerEventL(
    const TPointerEventData& aPointerData )
    {
    // Note: term pointer means physical pointer, e.g. finger
    // in the following comments. So first pointer down
    // means that single finger has been pressed down and
    // second pointer down means that also another finger has
    // been pressed down

    // Update pointer state
    if ( !iPointerState->Update( aPointerData ) )
        {
        // Send unknown event if successive down events were received
        // to same pointer
        if ( iTestingEnabled && iPointerState->SuccessiveDownEventsReceived() )
            {
            TAknTouchGestureFwUnknownEvent unknown;
            NotifyObserverL( unknown );
            }
        return;
        }

    TBool multiTouchEvent( iMultiRecognizing );

    if ( aPointerData.iPointerEvent.iType == TPointerEvent::EButton1Down )
        {
        // Single recognizing with first button down
        if ( !iSingleRecognizing )
            {
            iMultiRecognizing = EFalse;
            iSingleRecognizing = ETrue;
            multiTouchEvent = EFalse;
            }
        else
            {
            // Second pointer down starts multi recognizing
            iSingleRecognizing = EFalse;
            iMultiRecognizing = ETrue;
            multiTouchEvent = ETrue;
            }
        }
    else if ( aPointerData.iPointerEvent.iType == TPointerEvent::EButton1Up )
        {
        if ( iMultiRecognizing && iPointerState->IsSingleTouch() )
            {
            iSingleRecognizing = ETrue;
            iMultiRecognizing = EFalse;
            multiTouchEvent = ETrue;
            }
        else if ( iSingleRecognizing && iPointerState->IsNoTouch() )
            {
            // Single recognizing ongoing, pointer goes up.
            iSingleRecognizing = EFalse;
            iMultiRecognizing = EFalse;
            multiTouchEvent = EFalse;
            }
        }

    SendPointerEventToRecognizersL( multiTouchEvent, aPointerData );
    }


// ---------------------------------------------------------------------------
// Returns the framework settings provider.
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwSettings& CAknTouchGestureFwRecognitionEngine::Settings() const
    {
    return *iSettings;
    }


// ---------------------------------------------------------------------------
// EnableTestingFeatures
// ---------------------------------------------------------------------------
//    
void CAknTouchGestureFwRecognitionEngine::EnableTestingFeatures()
    {
    iTestingEnabled = ETrue;
    }


// ---------------------------------------------------------------------------
// C++ constructor.
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwRecognitionEngine::CAknTouchGestureFwRecognitionEngine(
        MAknTouchGestureFwObserver& aObserver, CCoeControl* aControl )
    :
    iObserver( aObserver ),
    iPointerState( NULL ),
    iSettings( NULL ),
    iGestureInterest( EAknTouchGestureFwNoGroup ),
    iSingleRecognizing( EFalse ),
    iMultiRecognizing( EFalse ),
    iControl( aControl ),
    iFeedBack( MTouchFeedback::Instance() )
    {
    }


// ---------------------------------------------------------------------------
// Second-phase constructor.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwRecognitionEngine::ConstructL()
    {
    iPointerState = CAknTouchGestureFwPointerState::NewL();
    iSettings = CAknTouchGestureFwSettings::NewL();
    }


// ---------------------------------------------------------------------------
// Enables/disables the necessary recognizers based on the gesture interest.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwRecognitionEngine::UpdateRecognizersForInterest(
    TUint aGestureInterest )
    {
    for ( TInt i = 0; i < iRecognizers.Count(); i++ )
        {
        if ( iRecognizers[i]->GestureGroup() & aGestureInterest )
            {
            iRecognizers[i]->SetEnabled( ETrue );
            }
        else
            {
            iRecognizers[i]->SetEnabled( EFalse );
            }
        }
    }


// ---------------------------------------------------------------------------
// Creates the recognizer for the specified gesture group.
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwBaseRecognizer*
    CAknTouchGestureFwRecognitionEngine::CreateRecognizerL(
        TAknTouchGestureFwGroup aGroup )
    {
    // Check first that the recognizer doesn't already exist.
    CAknTouchGestureFwBaseRecognizer* newRecognizer( Recognizer( aGroup ) );
    if ( newRecognizer )
        {
        return newRecognizer;
        }
    
    switch ( aGroup )
        {
        case ( EAknTouchGestureFwGroupTap ):
            {
            newRecognizer = CAknTouchGestureFwTapRecognizer::NewLC( *this );
            break;
            }
        case ( EAknTouchGestureFwGroupFlick ):
            {
            newRecognizer = CAknTouchGestureFwFlickRecognizer::NewLC( *this );
            break;
            }
        case ( EAknTouchGestureFwGroupDrag ):
            {
            newRecognizer = CAknTouchGestureFwDragRecognizer::NewLC( *this );
            break;
            }
        case ( EAknTouchGestureFwGroupPinch ):
            {
            newRecognizer = CAknTouchGestureFwPinchRecognizer::NewLC( *this );
            break;
            }
            
        default:
            {
            break;
            }
        }

    if ( newRecognizer )
        {
        iRecognizers.AppendL( newRecognizer );
        CleanupStack::Pop( newRecognizer );
        }

    return newRecognizer;
    }


// ---------------------------------------------------------------------------
// Gets recognizer for the specified gesture group.
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwBaseRecognizer*
    CAknTouchGestureFwRecognitionEngine::Recognizer(
        TAknTouchGestureFwGroup aGroup )
    {
    for ( TInt i = 0; i < iRecognizers.Count(); i++ )
        {
        if ( iRecognizers[i]->GestureGroup() == aGroup )
            {
            return iRecognizers[i];
            }
        }
    return NULL;
    }


// ---------------------------------------------------------------------------
// Sends a pointer event to all enabled recognizers.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwRecognitionEngine::SendPointerEventToRecognizersL(
    TBool aMultiPointer,
    const TPointerEventData& aPointerData )
    {    
    // Inform recognizers of pointer event
    for ( TInt i = 0; i < iRecognizers.Count(); i++ )
        {
        if ( iRecognizers[ i ]->Enabled() )
            {
            // Multi pointer event
            if ( aMultiPointer )
                {
                // Both pointers in use
                if ( iPointerState->IsDoubleTouch() )
                    {
                    iRecognizers[ i ]->HandleMultiPointerEventL(
                            aPointerData,
                            *iPointerState->FirstPointerPosition(),
                            *iPointerState->SecondPointerPosition() );
                    }
                // One pointer up
                else
                    {
                    iRecognizers[ i ]->HandleMultiPointerEventL(
                            aPointerData,
                            *iPointerState->FirstPointerPosition(),
                            TPoint() );
                    }
                }
            // Single pointer event
            else
                {
                iRecognizers[ i ]->HandleSinglePointerEventL( 
                        aPointerData );
                }
            }
        }
    }


// -----------------------------------------------------------------------------
// CAknTouchGestureFwRecognitionEngine::ImmediateFeedback
// -----------------------------------------------------------------------------
//
void CAknTouchGestureFwRecognitionEngine::ImmediateFeedback(
    TTouchLogicalFeedback aLogicalFeedback,
    TTouchFeedbackType aFeedbackType )
    {
    if ( iFeedBack )
        {
        // dummy pointer event is needed
        TPointerEvent pointerEvent;
        iFeedBack->InstantFeedback( iControl, aLogicalFeedback, aFeedbackType,
            pointerEvent );
        }
    }


// -----------------------------------------------------------------------------
// CAknTouchGestureFwRecognitionEngine::StartContinuousFeedback
// -----------------------------------------------------------------------------
//
void CAknTouchGestureFwRecognitionEngine::StartContinuousFeedback(
    TTouchContinuousFeedback aType,
    TInt aIntensity,
    TTimeIntervalMicroSeconds32 aTimeout )
    {
    if ( iFeedBack )
        {
        iFeedBack->StartFeedback( iControl, aType, NULL,
            aIntensity, aTimeout );
        }
    }


// -----------------------------------------------------------------------------
// CAknTouchGestureFwRecognitionEngine::ModifyContinuousFeedback
// -----------------------------------------------------------------------------
//
void CAknTouchGestureFwRecognitionEngine::ModifyContinuousFeedback(
    TInt aIntensity )
    {
    iFeedBack->ModifyFeedback( iControl, aIntensity );
    }


// -----------------------------------------------------------------------------
// CAknTouchGestureFwRecognitionEngine::StopContinuousFeedback
// -----------------------------------------------------------------------------
//
void CAknTouchGestureFwRecognitionEngine::StopContinuousFeedback()
    {
    if ( iFeedBack )
        {
        iFeedBack->StopFeedback( iControl );
        }
    }


// ---------------------------------------------------------------------------
// Defines gesture groups, which trigger tactile feedback automatically.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwRecognitionEngine::SetFeedbackForGroupsL( TUint aGestureGroups )
    {
    CAknTouchGestureFwBaseRecognizer* recognizer;
    
    TInt count = sizeof( KGestureGroup )/sizeof( TAknTouchGestureFwGroup );
    for ( TInt i = 0; i < count; i++ )
        {
        if ( aGestureGroups & KGestureGroup[ i ] )
            {
            recognizer = Recognizer( KGestureGroup[ i ] );
            if ( recognizer )
                {
                recognizer->SetFeedbackForTypesL(
                    KAknTouchGestureFwAllGestureTypes,
                    KAknTouchGestureFwAllGestureTypes );
                }
            }
        }
    }


// ---------------------------------------------------------------------------
// Defines gesture types, which trigger tactile feedback automatically.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwRecognitionEngine::SetFeedbackForTypesL(
    TAknTouchGestureFwGroup aGestureGroup,
    TUint aGestureTypesForTactile,
    TUint aGestureTypesForAudio )
    {
    if ( aGestureGroup == EAknTouchGestureFwNoGroup )
        {
        return;
        }
    if ( aGestureGroup == EAknTouchGestureFwAll )
        {
        for ( TInt i = 0; i < iRecognizers.Count(); i++ )
            {
            iRecognizers[ i ]->SetFeedbackForTypesL( aGestureTypesForTactile,
                aGestureTypesForAudio );        
            }
        return;
        }
    
    CAknTouchGestureFwBaseRecognizer* recognizer =
        Recognizer( aGestureGroup );
           
    if ( recognizer )
        {
        recognizer->SetFeedbackForTypesL( aGestureTypesForTactile,
            aGestureTypesForAudio );
        }
    }

// End of File
