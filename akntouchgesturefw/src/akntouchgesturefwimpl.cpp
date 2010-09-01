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
* Description:  Touch gesture framework implementation.
*
*/

#include <aknappui.h>
#include <e32base.h>

#include "akntouchgesturefwimpl.h"
#include "akntouchgesturefwdefs.h"
#include "akntouchgesturefwevent.h"
#include "akntouchgesturefwrecognitionengine.h"

using namespace AknTouchGestureFw;

// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwImpl* CAknTouchGestureFwImpl::NewL(
    MAknTouchGestureFwObserver& aObserver,
    CCoeControl* aControl )
    {
    CAknTouchGestureFwImpl* self =
        CAknTouchGestureFwImpl::NewLC( aObserver, aControl );
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwImpl* CAknTouchGestureFwImpl::NewLC(
    MAknTouchGestureFwObserver& aObserver,
    CCoeControl* aControl )
    {
    CAknTouchGestureFwImpl* self =
        new ( ELeave ) CAknTouchGestureFwImpl( aControl );
    CleanupStack::PushL( self );
    self->ConstructL( aObserver );
    return self;
    }


// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwImpl::~CAknTouchGestureFwImpl()
    {
    if ( iCoeEnv )
        {
        iCoeEnv->RemoveForegroundObserver( *this );
        iCoeEnv->RemoveMessageMonitorObserver( *this );
        }

    delete iRecognitionEngine;
    }


// ---------------------------------------------------------------------------
// Handles simulated pointer events.
// Used only for testing purposes.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwImpl::HandleSimulatedPointerEventL(
    const TPointerEventData& pointerData )
    {
    HandlePointerEventL( pointerData );

    iSubscriberControl->HandlePointerEventL( pointerData.iPointerEvent );
    }


// ---------------------------------------------------------------------------
// Sets target control for window server events.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwImpl::SetSubscriberControlL( CCoeControl* aControl )
    {
    CCoeControl* subsControl = aControl;

    CCoeControl* windowControl( subsControl );

    while ( windowControl && !windowControl->OwnsWindow() )
        {
        windowControl = windowControl->Parent();
        }

    if ( windowControl )
        {
        iWindowControl = windowControl;
        }
    else
        {
        // The subscriber control or it's parents have no window,
        // so there's no point to continue.
        User::Leave( KErrNotFound );
        }

    iSubscriberControl = subsControl;

    EnableAdditionalEvents();
    }


// ---------------------------------------------------------------------------
// Sets the gesture interest.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwImpl::SetGestureInterestL( TUint aGestureGroups )
    {
    TUint gestureInterest( EAknTouchGestureFwNoGroup );
    if ( aGestureGroups )
        {
        gestureInterest = aGestureGroups;
        }

    if ( !iMonitoringWs &&
         gestureInterest != EAknTouchGestureFwNoGroup )
        {
        iCoeEnv->AddMessageMonitorObserverL( *this );
        iMonitoringWs = ETrue;
        }
    else if ( iMonitoringWs &&
              gestureInterest == EAknTouchGestureFwNoGroup )
        {
        iCoeEnv->RemoveMessageMonitorObserver( *this );
        iMonitoringWs = EFalse;
        }

    TRAPD( err,
           iRecognitionEngine->SetGestureInterestL( gestureInterest ) );

    // If setting the gesture interes fails then there's no need to
    // monitor the WS events.
    if ( err != KErrNone && iMonitoringWs )
        {
        iCoeEnv->RemoveMessageMonitorObserver( *this );
        iMonitoringWs = EFalse;

        User::Leave( err );
        }

    EnableAdditionalEvents();
    }


// ---------------------------------------------------------------------------
// Returns the gesture groups which should be recognized.
// ---------------------------------------------------------------------------
//
TUint CAknTouchGestureFwImpl::GestureInterest() const
    {
    TUint gestureInterest( EAknTouchGestureFwNoGroup );
    if ( iRecognitionEngine )
        {
        gestureInterest = iRecognitionEngine->GestureInterest();
        }
    return gestureInterest;
    }


// ---------------------------------------------------------------------------
// Defines gesture groups, which trigger tactile feedback automatically.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwImpl::SetFeedbackForGroupsL( TUint aGestureGroups )
    {
    iRecognitionEngine->SetFeedbackForGroupsL( aGestureGroups );
    }


// ---------------------------------------------------------------------------
// Defines gesture types, which trigger tactile feedback automatically.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwImpl::SetFeedbackForTypesL(
    TAknTouchGestureFwGroup aGestureGroup,
    TUint aGestureTypesForTactile,
    TUint aGestureTypesForAudio )
    {
    iRecognitionEngine->SetFeedbackForTypesL( aGestureGroup,
        aGestureTypesForTactile, aGestureTypesForAudio );
    }


// ---------------------------------------------------------------------------
// EnableTestingFeatures
// ---------------------------------------------------------------------------
//    
void CAknTouchGestureFwImpl::EnableTestingFeatures()
    {
    iRecognitionEngine->EnableTestingFeatures();
    }


// ----------------------------------------------------------------------------
// C++ Constructor
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwImpl::CAknTouchGestureFwImpl( CCoeControl* aControl )
    :
    iMonitoringWs( EFalse ),
    iCoeEnv( CCoeEnv::Static() ),
    iSubscriberControl( aControl ),
    iWindowControl( NULL ),
    iRecognitionEngine( NULL )
    {
    }


// ---------------------------------------------------------------------------
// Symbian second-phase constructor.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwImpl::ConstructL(
    MAknTouchGestureFwObserver& aObserver )
    {
    SetSubscriberControlL( iSubscriberControl );

    iRecognitionEngine =
        CAknTouchGestureFwRecognitionEngine::NewL( aObserver,
            iSubscriberControl );

    iCoeEnv->AddForegroundObserverL( *this );
    }


// ---------------------------------------------------------------------------
// Handles pointer events.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwImpl::HandlePointerEventL(
    const TPointerEventData& aPointerData )
    {
#ifdef GFW_DEBUG_TRACE_INPUTOUTPUT
    AknTouchGestureFwUtils::DumpPointerEvent( aEvent, aPointerData.iSimulated );
#endif // GFW_DEBUG_TRACE_INPUTOUTPUT
    
    const TPointerEvent event = aPointerData.iPointerEvent;
    TInt pointerNumber = 0;
    if ( event.IsAdvancedPointerEvent() )
        {
        pointerNumber = event.AdvancedPointerEvent()->PointerNumber();
        }

    __ASSERT_ALWAYS( pointerNumber >= 0, User::Invariant() );
    __ASSERT_ALWAYS( pointerNumber <= 1, User::Invariant() );

    iRecognitionEngine->HandlePointerEventL( aPointerData );
   }


// ---------------------------------------------------------------------------
// Cancels ongoing recognition.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwImpl::CancelRecognition()
    {
    iRecognitionEngine->CancelRecognizing();
    }


// ---------------------------------------------------------------------------
// Enables the necessary events for the subscriber control's window.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwImpl::EnableAdditionalEvents()
    {
    // Additional pointer events are needed for the following gesture groups
    TUint gestureInterest( GestureInterest() );
    TBool multiEventsNeeded = gestureInterest & EAknTouchGestureFwGroupPinch;
    TBool dragEventsNeeded =
        gestureInterest & ( EAknTouchGestureFwGroupFlick |
                            EAknTouchGestureFwGroupDrag |
                            EAknTouchGestureFwGroupPinch );

    // Enables drag events and advanced pointer events for window if needed
    if ( iWindowControl )
        {
        RDrawableWindow* window = iWindowControl->DrawableWindow();
        if ( window )
            {
            if ( dragEventsNeeded )
                {
                window->PointerFilter( EPointerFilterDrag, 0 );
                }
            if ( multiEventsNeeded )
                {
                window->EnableAdvancedPointers();
                }
            if ( dragEventsNeeded || multiEventsNeeded )
			    {
                // Set pointer grab when drag or multi pointer events are
                // needed to enable gesture recognition outside gesture control.
                window->SetPointerGrab( ETrue );
				}
            }
        }
    }


// ---------------------------------------------------------------------------
// Checks if pointer event is targeted to the gesture control.
// ---------------------------------------------------------------------------
//
TBool CAknTouchGestureFwImpl::PointerEventTargetedToControl(
    CCoeControl* aTargetControl,
    TPointerEvent& aEvent ) const
    {
    if ( !aTargetControl )
        {
        return EFalse;
        }

    TBool targetedToControl( EFalse );
    TBool eventInControl(
            iSubscriberControl->Rect().Contains( aEvent.iPosition ) );

    // Check if target control is gesture control's window control.
    targetedToControl = aTargetControl == iWindowControl;

    // Check that pointer is in gesture control area.
    if ( targetedToControl &&
         aEvent.iType == TPointerEvent::EButton1Down )
        {
        targetedToControl = eventInControl;
        }

    // Check if pointer is targeted to child window that is on gesture
    // control area.
    else if ( !targetedToControl && eventInControl )
        {
        CCoeControl* windowControl( aTargetControl );
        while ( windowControl )
            {
            windowControl = windowControl->Parent();
            if ( windowControl == iWindowControl )
                {
                targetedToControl = ETrue;
                ConvertPositionToControlWindow(
                        aTargetControl->DrawableWindow(),
                        aEvent.iPosition );
                break;
                }
            }
        }

    return targetedToControl;
    }


// ---------------------------------------------------------------------------
// Converts position in window area according to control window coordinates.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwImpl::ConvertPositionToControlWindow(
    RDrawableWindow* aWindow,
    TPoint& aPosition ) const
    {
    if ( aWindow )
        {
        TPoint targetPosition( aWindow->AbsPosition() );
        TPoint windowPosition(
                iWindowControl->DrawableWindow()->AbsPosition() );
        aPosition.iX = aPosition.iX + targetPosition.iX - windowPosition.iX;
        aPosition.iY = aPosition.iY + targetPosition.iY - windowPosition.iY;
        }
    }


// ---------------------------------------------------------------------------
// Called when the application gains foreground.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwImpl::HandleGainingForeground()
    {
#ifdef GFW_DEBUG_TRACE_INPUTOUTPUT
    _LIT( KAknTouchGainForeground, "[GFW] IN GAIN FOREGROUND" );
    RDebug::Print( KAknTouchGainForeground );
#endif

    if ( !iMonitoringWs && GestureInterest() != EAknTouchGestureFwNoGroup )
        {
        TRAP_IGNORE( iCoeEnv->AddMessageMonitorObserverL( *this ) );
        iMonitoringWs = ETrue;
        }
    }


// ---------------------------------------------------------------------------
// Called when the application loses foreground.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwImpl::HandleLosingForeground()
    {
#ifdef GFW_DEBUG_TRACE_INPUTOUTPUT
    _LIT( KAknTouchLostForeground, "[GFW] IN LOST FOREGROUND" );
    RDebug::Print( KAknTouchLostForeground );
#endif

    // Reset framework state because it might be possible that
    // pointer is down when framework loses background.
    // In this situation corresponding up-event is never received
    // and framework stays to wrong state (assuming pointer is still down)
    // without resetting it.
    CancelRecognition();

    if ( iMonitoringWs )
        {
        iCoeEnv->RemoveMessageMonitorObserver( *this );
        iMonitoringWs = EFalse;
        }
    }


// ---------------------------------------------------------------------------
// Handles window server messages.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwImpl::MonitorWsMessage( const TWsEvent& aEvent )
    {
    if ( aEvent.Type() == EEventPointer )
        {
        CCoeControl* targetControl =
            reinterpret_cast<CCoeControl*>( aEvent.Handle() );
        TAdvancedPointerEvent event( *aEvent.Pointer() );
        TBool targetedToControl( PointerEventTargetedToControl(
                targetControl, event ) );
        
        TPointerEventData pointerData( event, 
                                       event.PointerNumber(), 
                                       aEvent.Time(), 
                                       EFalse, 
                                       targetedToControl );
        
        TRAP_IGNORE( HandlePointerEventL( pointerData ) );
        }
    else if ( aEvent.Type() == EEventScreenDeviceChanged )
        {
        // Cancel recognition if layout changes
        CancelRecognition();
        }
    }

// End of File
