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
* Description:  Touch gesture fw simulation class.
*
*/


#include "akntouchgesturefwimpl.h"
#include "akntouchgesturefwsimulation.h"

using namespace AknTouchGestureFw;

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Sets the pointer number of an advanced pointer event.
// ---------------------------------------------------------------------------
//
void TAdvancedPointerEventHelper::SetPointerNumberToEvent(
    TAdvancedPointerEvent* aEvent,
    TInt aPointerNumber )
    {
    // Just to hack to set the pointer number: these members may not be
    // supported in the future...
    aEvent->iModifiers |= EModifierAdvancedPointerEvent;
    aEvent->iData.multiPos3D.iPointerNumber = aPointerNumber;
    }


// ---------------------------------------------------------------------------
// CAknTouchGestureFwSimulation::~CAknTouchGestureFwSimulation
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwSimulation::~CAknTouchGestureFwSimulation()
    {
    iDataArray.Reset();
    iDataArray.Close();
    }


// ---------------------------------------------------------------------------
// CAknTouchGestureFwSimulation::InitSimulationL
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwSimulation::InitSimulationL(
        CAknTouchGestureFw* aGestureFw,
        CAknTouchGestureFwImpl* aGestureEngine )
    {
    CAknTouchGestureFwSimulation* instance =
        static_cast< CAknTouchGestureFwSimulation* >(
                CCoeEnv::Static( KAknTouchGestureFwSimulation ) );
    if ( !instance )
        {
        instance =
            new ( ELeave ) CAknTouchGestureFwSimulation();
        }
    // Check if already in array
    TBool gestureFwFound( EFalse );
    for ( TInt i = 0; i < instance->iDataArray.Count(); i++ )
        {
        if ( instance->iDataArray[ i ].iGestureFw == aGestureFw )
            {
            gestureFwFound = ETrue;
            break;
            }
        }
    // Add only if fw was not found from array
    if ( !gestureFwFound )
        {
        TAknTouchGestureFwSimulationData newData;
        newData.iGestureFw = aGestureFw;
        newData.iGestureEngine = aGestureEngine;
        instance->iDataArray.AppendL( newData );
        }
    }


// ---------------------------------------------------------------------------
// CAknTouchGestureFwSimulation::EndSimulation
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwSimulation::EndSimulation(
        CAknTouchGestureFw* aGestureFw )
    {
    CAknTouchGestureFwSimulation* instance =
        static_cast< CAknTouchGestureFwSimulation* >(
                CCoeEnv::Static( KAknTouchGestureFwSimulation ) );
    if ( !instance )
        {
        return;
        }
    for ( TInt i = 0; i < instance->iDataArray.Count(); i++ )
        {
        if ( instance->iDataArray[ i ].iGestureFw == aGestureFw )
            {
            instance->iDataArray.Remove( i );
            break;
            }
        }
    }


// ---------------------------------------------------------------------------
// Simulates a single pointer event.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwSimulation::SimulateL( CAknTouchGestureFw* aGestureFw,
                                              TPointerEvent& aEvent,
                                              TInt aPointerNumber,
                                              TTime aTimeStamp )
    {
    CAknTouchGestureFwImpl* engine( NULL );
    for ( TInt i = 0; i < iDataArray.Count(); i++ )
        {
        if ( iDataArray[ i ].iGestureFw == aGestureFw )
            {
            engine = iDataArray[ i ].iGestureEngine;
            break;
            }
        }
    if ( engine )
        {
        TAdvancedPointerEvent* ctrlEvent =
            static_cast<TAdvancedPointerEvent*>( &aEvent );
        TAdvancedPointerEventHelper::SetPointerNumberToEvent(
                ctrlEvent, aPointerNumber );
        
        TPointerEventData pointerData( 
                *ctrlEvent, aPointerNumber, aTimeStamp, ETrue, ETrue );
        engine->HandleSimulatedPointerEventL( pointerData );
        }
    }


// ---------------------------------------------------------------------------
// Default C++ constructor.
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwSimulation::CAknTouchGestureFwSimulation()
    : CCoeStatic( KAknTouchGestureFwSimulation )
    {
    }

// End of File
