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
* Description:  AknPhysics control environment observer
*
*/


#include <aknphysics.h>
#include <aknappui.h>
#include <aknpointereventmodifier.h>

#include "aknphysicsconeobserver.h"
#include "aknphysicskeyconsumer.h"
#include "aknphysicsrestrictor.h"
#include "aknphysicsdragobserver.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CAknPhysicsConeObserver::NewL
// ---------------------------------------------------------------------------
//
CAknPhysicsConeObserver* CAknPhysicsConeObserver::NewL( 
    CAknPhysics* aPhysics, CAknPhysicsRestrictor* aRestrictor )
    {
    CAknPhysicsConeObserver* self = 
        CAknPhysicsConeObserver::NewLC( aPhysics, aRestrictor );
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsConeObserver::NewLC
// ---------------------------------------------------------------------------
//
CAknPhysicsConeObserver* CAknPhysicsConeObserver::NewLC( 
    CAknPhysics* aPhysics, CAknPhysicsRestrictor* aRestrictor )
    {
    CAknPhysicsConeObserver* self 
        = new ( ELeave ) CAknPhysicsConeObserver( aPhysics, aRestrictor );
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsConeObserver::~CAknPhysicsConeObserver
// ---------------------------------------------------------------------------
//
CAknPhysicsConeObserver::~CAknPhysicsConeObserver()
    {
    if ( iCoeEnv )
        {
        iCoeEnv->RemoveForegroundObserver( *this );
        iCoeEnv->RemoveMessageMonitorObserver( *this );

        if ( iCoeEnv->AppUi() )
            {
            iCoeEnv->AppUi()->RemoveFromStack( iKeyConsumer );
            }
        }
    delete iDragObserver;
    delete iKeyConsumer;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsConeObserver::EventHandlingAllowed
// ---------------------------------------------------------------------------
//
TBool CAknPhysicsConeObserver::EventHandlingAllowed() const
    {
    if ( !iEventsAllowed 
        || OngoingAction() == CAknPhysics::EAknPhysicsActionBouncing )
        {
        return EFalse;
        }
    return ETrue;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsConeObserver::SetViewWindowControl
// ---------------------------------------------------------------------------
//
void CAknPhysicsConeObserver::SetViewWindowControl( CCoeControl* aControl )
    {
    if ( aControl )
        {
        CCoeControl* windowControl( aControl );
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
            iWindowControl = aControl;
            }
        iViewControl = aControl;
        }
    }


// ---------------------------------------------------------------------------
// CAknPhysicsConeObserver::PhysicsStateChanged
// ---------------------------------------------------------------------------
//
void CAknPhysicsConeObserver::PhysicsStateChanged()
    {
    // Make sure that if we are foreground, we are monitoring ws events.
    if ( !iMonitoringWs && iCoeEnv )
        {
        CAknAppUi* appUi( AppUi() );
        if ( appUi && appUi->IsForeground() )
            {
            HandleGainingForeground();            
            }
        }
    }


// ---------------------------------------------------------------------------
// CAknPhysicsConeObserver::DragChanged
// ---------------------------------------------------------------------------
//
TBool CAknPhysicsConeObserver::DragChanged( const TBool& aLandscape,
                                            TPoint& aDragDistance, 
                                            TInt& aMoveTime ) const
    {
    if ( iDragObserver && iDragObserver->DragChanged() )
        {
        TPoint changedDrag( iDragObserver->ChangedDragDistance() );
        if ( aLandscape && changedDrag.iX != aDragDistance.iX )
            {
            aDragDistance.iX = changedDrag.iX;
            aMoveTime = iDragObserver->ChangedHorizontalDragMoveTime();
            return ETrue;
            }
        else if ( !aLandscape && changedDrag.iY != aDragDistance.iY )
            {
            aDragDistance.iY = changedDrag.iY;
            aMoveTime = iDragObserver->ChangedVerticalDragMoveTime();
            return ETrue;
            }
        }
    return EFalse;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsConeObserver::UpdateViewWindowControl
// ---------------------------------------------------------------------------
//
void CAknPhysicsConeObserver::UpdateViewWindowControl( CCoeControl* aControl )
    {
    if ( !aControl )
        {
        aControl = iViewControl;
        }
    SetViewWindowControl( aControl );
    }


// ---------------------------------------------------------------------------
// CAknPhysicsConeObserver::CAknPhysicsConeObserver
// ---------------------------------------------------------------------------
//
CAknPhysicsConeObserver::CAknPhysicsConeObserver( 
    CAknPhysics* aPhysics, CAknPhysicsRestrictor* aRestrictor )
    :
    iPhysics( aPhysics ),
    iKeyConsumer( NULL ),
    iCoeEnv( CCoeEnv::Static() ),
    iEventsAllowed( ETrue ),
    iMonitoringWs( EFalse ),
    iWindowControl( NULL ),
    iViewControl( NULL ),
    iRestrictor( aRestrictor ),
    iDragObserver( NULL )
    {
    }


// ---------------------------------------------------------------------------
// CAknPhysicsConeObserver::ConstructL
// ---------------------------------------------------------------------------
//
void CAknPhysicsConeObserver::ConstructL()
    {
    iKeyConsumer = CAknPhysicsKeyConsumer::NewL( this );
    iDragObserver = CAknPhysicsDragObserver::NewL( 
        iRestrictor->ParameterProvider() );
    if ( iCoeEnv )
        {
        iCoeEnv->AppUi()->AddToStackL( iKeyConsumer, 
                                       ECoeStackPriorityEnvironmentFilter,
                                       ECoeStackFlagRefusesFocus );
        iCoeEnv->AddForegroundObserverL( *this );
        }
    }


// ---------------------------------------------------------------------------
// CAknPhysicsConeObserver::OngoingAction
// ---------------------------------------------------------------------------
//
TInt CAknPhysicsConeObserver::OngoingAction() const
    {
    if ( iPhysics )
        {
        return iPhysics->OngoingPhysicsAction();
        }
    return 0;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsConeObserver::EventTargetedToView
// ---------------------------------------------------------------------------
//
TInt CAknPhysicsConeObserver::EventTargetedToView( 
    const TPointerEvent* aEvent, const CCoeControl* aTargetControl )
    {
    TInt target( ETargetUnresolvedControl );
    
    if ( aTargetControl && iWindowControl )
        {
        // target window different from view window
        if ( aTargetControl != iWindowControl )
            {
            // figure out if target window is iWindowControl's child window
            CCoeControl* parent = const_cast<CCoeControl*>( aTargetControl );
            
            while ( parent )
                {
                if ( parent == iWindowControl )
                    {
                    return ETargetChildControl;
                    }
                
                parent = parent->Parent();
                }
            
            target = ETargetOtherControl;
            }

        // target window same as view window
        else if ( iViewControl )
            {
            TRect viewRect( iViewControl->Rect() );
            
            // pointerevent position not in control area - view control
            // not target control
            if ( viewRect != TRect() 
                && !viewRect.Contains( aEvent->iPosition ) )
                {
                target = ETargetOtherControl;
                }
            else
                {
                target = ETargetViewControl;
                }

            if ( target != ETargetOtherControl )
                {
                // check if there is a child control to receive the event
                for ( TInt i = 0; i < iViewControl->CountComponentControls();
                      i++ )
                    {
                    CCoeControl* child = iViewControl->ComponentControl( i );
                    if ( child && child->IsVisible() && !child->OwnsWindow() )
                        {
                        if ( child->Rect().Contains( aEvent->iPosition ) )
                            {
                            target = ETargetOtherControl;
                            }
                        }
                    }
                }
            }
        }
    return target;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsConeObserver::MonitorPointerEvent
// ---------------------------------------------------------------------------
//
TBool CAknPhysicsConeObserver::MonitorPointerEvent( 
    TPointerEvent* aEvent, CCoeControl* aTargetControl )
    {
    // Check where event is targeted
    TInt eventTarget( EventTargetedToView( aEvent, aTargetControl ) );
    
    // Register event to drag observer
    if ( iDragObserver 
        && ( eventTarget == ETargetViewControl 
            || aEvent->iType == TPointerEvent::EButton1Up ) )
        {
        iDragObserver->RegisterEventPosition( aEvent );
        }

    if ( aEvent->iType == TPointerEvent::EButton1Up && 
         iPhysics->IsPanningDrawOmitted() )
        {
        // Ensure that the last panning position gets drawn if the last
        // view redraw was omitted due to too high CPU use.
        iPhysics->DrawViewInCurrentPosition();
        }
    
    // Stop physics only with pointer down event
    if ( aEvent->iType != TPointerEvent::EButton1Down )
        {
        return EFalse;
        }

    iEventsAllowed = ETrue;
    TBool stopPhysics( EFalse );
    TInt ongoingAction = OngoingAction();
    
    if ( ongoingAction != CAknPhysics::EAknPhysicsActionNone
        && ongoingAction != CAknPhysics::EAknPhysicsActionDragging )
        {
        PointerEventModified( aEvent, aTargetControl );
        }
    
    // Check if flick should be stopped
    if ( ongoingAction == CAknPhysics::EAknPhysicsActionFlicking )
        {
        // Event not targeted to view - stop flick
        if ( ( eventTarget == ETargetOtherControl || 
                eventTarget == ETargetChildControl ) && aTargetControl )
            {
            stopPhysics = ETrue;
            aTargetControl->IgnoreEventsUntilNextPointerUp();
            }
        }

    // No pointer events to view control while bounce is ongoing
    else if ( ongoingAction == CAknPhysics::EAknPhysicsActionBouncing
        && eventTarget == ETargetViewControl )
        {
        iWindowControl->IgnoreEventsUntilNextPointerUp();
        }
    else if ( ongoingAction == CAknPhysics::EAknPhysicsActionBouncing
        && eventTarget == ETargetChildControl )
        {
        aTargetControl->IgnoreEventsUntilNextPointerUp();
        }

    return stopPhysics;
    }


// --------------------------------------------------------------------------
// CAknPhysicsConeObserver::MonitorKeyEvent
// --------------------------------------------------------------------------
//
TBool CAknPhysicsConeObserver::MonitorKeyEvent( TKeyEvent* /*aEvent*/ )
    {
    iEventsAllowed = ETrue;
    if ( OngoingAction() == CAknPhysics::EAknPhysicsActionFlicking )
        {
        return ETrue;
        }
    return EFalse;
    }


// --------------------------------------------------------------------------
// CAknPhysicsConeObserver::PointerEventModified
// --------------------------------------------------------------------------
//
TBool CAknPhysicsConeObserver::PointerEventModified( 
    TPointerEvent* aEvent, CCoeControl* aTargetControl )
    {
    TPoint originalPosition( aEvent->iPosition );
    CAknAppUi* appUi = AppUi();
    if ( appUi )
        {
        appUi->PointerEventModifier()->HandlePointerEvent( 
            *aEvent, aTargetControl );
        }
    if ( originalPosition != aEvent->iPosition )
        {
        return ETrue;
        }
    return EFalse;
    }


// --------------------------------------------------------------------------
// CAknPhysicsConeObserver::AppUi
// --------------------------------------------------------------------------
//
CAknAppUi* CAknPhysicsConeObserver::AppUi()
    {
    if ( iCoeEnv )
        {
        return static_cast<CAknAppUi*>( iCoeEnv->AppUi() );        
        }
    return NULL;
    }


// --------------------------------------------------------------------------
// CAknPhysicsConeObserver::HandleGainingForeground
// --------------------------------------------------------------------------
//
void CAknPhysicsConeObserver::HandleGainingForeground()
    {
    iEventsAllowed = ETrue;
    if ( iCoeEnv && !iMonitoringWs )
        {
        TRAP_IGNORE( iCoeEnv->AddMessageMonitorObserverL( *this ) );
        iMonitoringWs = ETrue;
        }
    if ( iPhysics )
        {
        iPhysics->SetBounceTactileFeedback( ETrue );
        }
    }


// --------------------------------------------------------------------------
// CAknPhysicsConeObserver::HandleLosingForeground
// --------------------------------------------------------------------------
//
void CAknPhysicsConeObserver::HandleLosingForeground()
    {
    if ( iPhysics )
        {
        iPhysics->SetBounceTactileFeedback( EFalse );
        }
    if ( iPhysics 
        && OngoingAction() == CAknPhysics::EAknPhysicsActionFlicking )
        {
        iPhysics->StopPhysics();
        iPhysics->ResetFriction();
        }
    else if ( OngoingAction() == CAknPhysics::EAknPhysicsActionNone
        || OngoingAction() == CAknPhysics::EAknPhysicsActionDragging
        && iPhysics )
        {
        iPhysics->UpdateViewPosition();
        }
    if ( iCoeEnv && iMonitoringWs )
        {
        iCoeEnv->RemoveMessageMonitorObserver( *this );
        iMonitoringWs = EFalse;
        }
    }


// --------------------------------------------------------------------------
// CAknPhysicsConeObserver::MonitorWsMessage
// --------------------------------------------------------------------------
//
void CAknPhysicsConeObserver::MonitorWsMessage( const TWsEvent &aEvent )
    {
    TBool stopPhysics( EFalse );

    // Check if physics should be stopped with pointer event
    if ( aEvent.Type() == EEventPointer )
        {
        CCoeControl* targetControl = 
            reinterpret_cast<CCoeControl*>( aEvent.Handle() );
        if ( targetControl )
            {
            stopPhysics = MonitorPointerEvent( 
                aEvent.Pointer(), targetControl );
            }
        }

    // Check if physics should be stopped with key event
    else if ( aEvent.Type() == EEventKeyDown )
        {
        stopPhysics = MonitorKeyEvent( aEvent.Key() );
        }

    // Stop physics with layout change if flicking        
    else if ( aEvent.Type() == EEventScreenDeviceChanged
        && OngoingAction() == CAknPhysics::EAknPhysicsActionFlicking )
        {
        stopPhysics = ETrue;
        }

    if ( stopPhysics && iPhysics )
        {
        iPhysics->StopPhysics();
        iPhysics->ResetFriction();
        iEventsAllowed = EFalse;
        }
    }
