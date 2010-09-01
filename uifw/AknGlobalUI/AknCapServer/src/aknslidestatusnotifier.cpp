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
* Description:
*
*/

#include <e32base.h>
#include <UikonInternalPSKeys.h>

#include "aknslidestatusnotifier.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CAknSlideStatusNotifier::ConstructL()
// Second phase of two-phase construction
// ---------------------------------------------------------------------------
//
void CAknSlideStatusNotifier::ConstructL( MAknSlideStatusObserver* aObserver )
    {
    TInt err = iProperty.Attach( KPSUidHWRM, KHWRMGripStatus/*KPSUidUikon, KUikFlipStatus*/);
    User::LeaveIfError( err );

    iProperty.Subscribe(iStatus);
    iObserver = aObserver;
    CActiveScheduler::Add( this );
    SetActive();
    }


// ---------------------------------------------------------------------------
// CAknSlideStatusNotifier::NewL()
// Two-phase constructor
// ---------------------------------------------------------------------------
//
CAknSlideStatusNotifier* CAknSlideStatusNotifier::NewL( MAknSlideStatusObserver* aObserver )
    {
    CAknSlideStatusNotifier* self = CAknSlideStatusNotifier::NewLC( aObserver );
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// CAknSlideStatusNotifier::NewLC()
// Two-phase constructor, leaves pointer on the cleanup stack
// ---------------------------------------------------------------------------
//
CAknSlideStatusNotifier* CAknSlideStatusNotifier::NewLC( MAknSlideStatusObserver* aObserver )
    {
    CAknSlideStatusNotifier* self = new( ELeave ) CAknSlideStatusNotifier;
    CleanupStack::PushL( self );
    self->ConstructL( aObserver );
    return self;
    }


// ---------------------------------------------------------------------------
// CAknSlideStatusNotifier::CAknSlideStatusNotifier()
// Default C++ constructor
// ---------------------------------------------------------------------------
//
CAknSlideStatusNotifier::CAknSlideStatusNotifier() : CActive( EPriorityNormal )
    {
    // No implementation needed
    }

// ---------------------------------------------------------------------------
// CAknSlideStatusNotifier::~CAknSlideStatusNotifier()
// ---------------------------------------------------------------------------
//
CAknSlideStatusNotifier::~CAknSlideStatusNotifier()
    {
    Cancel();
    iProperty.Close();
    }


// ---------------------------------------------------------------------------
// CAknSlideStatusNotifier::RunL
// From class CActive
// Handles an active object's request completion event.
// ---------------------------------------------------------------------------
//
void CAknSlideStatusNotifier::RunL()
    {
    TInt status( 0 );
    TInt runStatus( iStatus.Int() );
    //resubscribe so that no events are lost    
    iProperty.Subscribe( iStatus );
    SetActive();

    switch( runStatus )
        {
        case KErrNone:
            if ( KErrNone == iProperty.Get( status ) )
                {                
                iObserver->SlideStatusChangedL( status );
                }
            break;   
        
        case KErrDied:
            User::Leave( KErrDied );
        
        default:
            break;    
        }
    }

// ---------------------------------------------------------------------------
// CAknSlideStatusNotifier::DoCancel
// From class CActive
// Implements cancellation of an outstanding request.
// ---------------------------------------------------------------------------
//
void CAknSlideStatusNotifier::DoCancel()
    {
    iProperty.Cancel();
    }

// ---------------------------------------------------------------------------
// CAknSlideStatusNotifier::RunError
// From class CActive
// Implements error handling of an outstanding request.
// ---------------------------------------------------------------------------
//
TInt CAknSlideStatusNotifier::RunError( TInt /*aError*/ )
    {
    return KErrNone;
    }
// End of file SlideStatusNotifier.cpp
