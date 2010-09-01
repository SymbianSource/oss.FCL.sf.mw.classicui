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
* Description:  Touch gesture framework central repository listener.
*
*/

#include <centralrepository.h>

#include "akntouchgesturefwcenreplistener.h"

using namespace AknTouchGestureFw;

const TUint32 KAknTouchGestureFwPartialKey( 0x00000001 );
const TUint32 KAknTouchGestureFwKeyBitMask( 0xfffffff0 );


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwCenRepListener* CAknTouchGestureFwCenRepListener::NewL(
    CRepository* aCenRep,
    MAknTouchGestureFwCenRepObserver* aObserver )
    {
    CAknTouchGestureFwCenRepListener* self =
        CAknTouchGestureFwCenRepListener::NewLC( aCenRep, aObserver );
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwCenRepListener* CAknTouchGestureFwCenRepListener::NewLC(
    CRepository* aCenRep,
    MAknTouchGestureFwCenRepObserver* aObserver )
    {
    CAknTouchGestureFwCenRepListener* self =
        new ( ELeave ) CAknTouchGestureFwCenRepListener( aCenRep, aObserver );
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }


// ---------------------------------------------------------------------------
//  Destructor.
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwCenRepListener::~CAknTouchGestureFwCenRepListener()
    {
    Cancel();
    }


// ---------------------------------------------------------------------------
// Handles the request completion, called when an observed
// CenRep value changes.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwCenRepListener::RunL()
    {
    TInt status( iStatus.Int() );
    RenewRequestL();
    iObserver->CenRepValueChanged( status );
    }


// ---------------------------------------------------------------------------
// Cancels an outstanding request.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwCenRepListener::DoCancel()
    {
    iCenRep->NotifyCancelAll();
    }


// ---------------------------------------------------------------------------
// Handles possible leaves on request completion.
// ---------------------------------------------------------------------------
//
TInt CAknTouchGestureFwCenRepListener::RunError( TInt /*aError*/ )
    {
    // Fail silently.
    return KErrNone;
    }


// ---------------------------------------------------------------------------
// C++ constructor.
// ---------------------------------------------------------------------------
//
CAknTouchGestureFwCenRepListener::CAknTouchGestureFwCenRepListener(
    CRepository* aCenRep,
    MAknTouchGestureFwCenRepObserver* aObserver )
    : CActive( EPriorityStandard ),
      iCenRep( aCenRep ),
      iObserver( aObserver )
    {
    }


// ---------------------------------------------------------------------------
// Symbian second-phase constructor.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwCenRepListener::ConstructL()
    {
    CActiveScheduler::Add( this );
    RenewRequestL();
    }


// ---------------------------------------------------------------------------
// Renews the request.
// ---------------------------------------------------------------------------
//
void CAknTouchGestureFwCenRepListener::RenewRequestL()
    {
    User::LeaveIfError(
        iCenRep->NotifyRequest(
                KAknTouchGestureFwPartialKey,
                KAknTouchGestureFwKeyBitMask, iStatus ) );
    SetActive();
    }

// End of File
