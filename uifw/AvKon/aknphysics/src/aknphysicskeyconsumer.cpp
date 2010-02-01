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
* Description:  AknPhysics key consuming control
*
*/

#include <aknappui.h>

#include "aknphysicsconeobserver.h"
#include "aknphysicskeyconsumer.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CAknPhysicsKeyConsumer::NewL
// ---------------------------------------------------------------------------
//
CAknPhysicsKeyConsumer* CAknPhysicsKeyConsumer::NewL(
    CAknPhysicsConeObserver* aConeObserver )
    {
    CAknPhysicsKeyConsumer* self = 
        CAknPhysicsKeyConsumer::NewLC( aConeObserver );
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsKeyConsumer::NewLC
// ---------------------------------------------------------------------------
//
CAknPhysicsKeyConsumer* CAknPhysicsKeyConsumer::NewLC( 
    CAknPhysicsConeObserver* aConeObserver )
    {
    CAknPhysicsKeyConsumer* self 
        = new ( ELeave ) CAknPhysicsKeyConsumer( aConeObserver );
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsKeyConsumer::~CAknPhysicsKeyConsumer
// ---------------------------------------------------------------------------
//
CAknPhysicsKeyConsumer::~CAknPhysicsKeyConsumer()
    {
    }


// ---------------------------------------------------------------------------
// CAknPhysicsKeyConsumer::CAknPhysicsKeyConsumer
// ---------------------------------------------------------------------------
//
CAknPhysicsKeyConsumer::CAknPhysicsKeyConsumer( 
    CAknPhysicsConeObserver* aConeObserver )
    :
    iConeObserver( aConeObserver )
    {
    }


// ---------------------------------------------------------------------------
// CAknPhysicsKeyConsumer::ConstructL
// ---------------------------------------------------------------------------
//
void CAknPhysicsKeyConsumer::ConstructL()
    {
    }


// ---------------------------------------------------------------------------
// CAknPhysicsKeyConsumer::OfferKeyEventL
// ---------------------------------------------------------------------------
//
TKeyResponse CAknPhysicsKeyConsumer::OfferKeyEventL( 
    const TKeyEvent& aKeyEvent, TEventCode aType )
    {
    TKeyResponse response( EKeyWasNotConsumed );
    
    // EKeyEscape can't be blocked otherwise dialog or menu will not be
    // closed correctly when user pressed end key or application key
    TBool dialogShutEvent(
            aType == EEventKey
            && aKeyEvent.iCode == EKeyEscape
            && iCoeEnv->AppUi()->IsDisplayingMenuOrDialog() );
    
    if ( !dialogShutEvent && iConeObserver 
        && !iConeObserver->EventHandlingAllowed() )
        {
        response = EKeyWasConsumed;
        }

    return response;
    }
