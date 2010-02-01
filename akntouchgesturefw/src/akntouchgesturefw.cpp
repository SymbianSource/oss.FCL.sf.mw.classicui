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
* Description: Touch gesture framework public API methods.
*
*/

#include <akntouchgesturefw.h>
#include <AknTasHook.h>

#include "akntouchgesturefwdefs.h"
#include "akntouchgesturefwimpl.h"
#include "akntouchgesturefwsimulation.h"

using namespace AknTouchGestureFw;

// ---------------------------------------------------------------------------
// Two-phase constructor
// ---------------------------------------------------------------------------
//
EXPORT_C CAknTouchGestureFw* CAknTouchGestureFw::NewL(
        MAknTouchGestureFwObserver& aObserver,
        CCoeControl& aControl )
    {
    CAknTouchGestureFw* self = new ( ELeave ) CAknTouchGestureFw;
    CleanupStack::PushL( self );
    self->ConstructL( aObserver, aControl );
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CAknTouchGestureFw::~CAknTouchGestureFw()
    {
    AKNTASHOOK_REMOVE();
    CAknTouchGestureFwSimulation::EndSimulation( this );
    delete iImpl;
    }


// ---------------------------------------------------------------------------
// Sets the gesture interest.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknTouchGestureFw::SetGestureInterestL( TUint aGestureGroups,
                                                       TUint /*aFlags*/ )
    {
    iImpl->SetGestureInterestL( aGestureGroups );
    }


// ---------------------------------------------------------------------------
// Defines gesture groups, which trigger tactile feedback automatically.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknTouchGestureFw::SetFeedbackForGroupsL( TUint aGestureGroups )
    {
    iImpl->SetFeedbackForGroupsL( aGestureGroups );
    }


// ---------------------------------------------------------------------------
// Defines gesture types, which trigger tactile feedback automatically.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknTouchGestureFw::SetFeedbackForTypesL(
    TAknTouchGestureFwGroup aGestureGroup,
    TUint aGestureTypesForTactile,
    TUint aGestureTypesForAudio )
    {
    iImpl->SetFeedbackForTypesL(
        aGestureGroup,
        aGestureTypesForTactile,
        aGestureTypesForAudio );
    }


// ----------------------------------------------------------------------------
// Extension_
// ----------------------------------------------------------------------------
//
TInt CAknTouchGestureFw::Extension_( TUint aExtensionId, TAny*& a0, TAny* a1 )
    {
    if ( aExtensionId == KAknTouchGestureFwTestingFeature )
        {
        TRAP_IGNORE(
                CAknTouchGestureFwSimulation::InitSimulationL( this, iImpl ) );
        iImpl->EnableTestingFeatures();
        return KErrNone;
        }
    return CBase::Extension_( aExtensionId, a0, a1 );
    }


// ---------------------------------------------------------------------------
// Default C++ constructor.
// ---------------------------------------------------------------------------
//
CAknTouchGestureFw::CAknTouchGestureFw()
    {
    AKNTASHOOK_ADD( this, "CAknTouchGestureFw" );
    }


// ---------------------------------------------------------------------------
// Second-phase constructor.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFw::ConstructL( MAknTouchGestureFwObserver& aObserver,
                                     CCoeControl& aControl )
    {
    iImpl = CAknTouchGestureFwImpl::NewL( aObserver, &aControl );
    }

// End of File
