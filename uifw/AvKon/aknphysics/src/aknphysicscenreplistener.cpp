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
* Description:  AknPhysics cenrep listener
*
*/


#include <centralrepository.h>

#include "aknphysicscenreplistener.h"

const TUint32 KAknPhysicsPartialKey( 0x00000001 );
const TUint32 KAknPhysicsKeyBitMask( 0xfffffff0 );


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CAknPhysicsCenRepListener::NewL
// ---------------------------------------------------------------------------
//
CAknPhysicsCenRepListener* CAknPhysicsCenRepListener::NewL(
    CRepository* aCenRep, MAknPhysicsCenRepObserver* aObserver )
    {
    CAknPhysicsCenRepListener* self = CAknPhysicsCenRepListener::NewLC(
        aCenRep, aObserver );
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsCenRepListener::NewLC
// ---------------------------------------------------------------------------
//
CAknPhysicsCenRepListener* CAknPhysicsCenRepListener::NewLC(
    CRepository* aCenRep, MAknPhysicsCenRepObserver* aObserver )
    {
    CAknPhysicsCenRepListener* self = new ( ELeave ) CAknPhysicsCenRepListener(
        aCenRep, aObserver );
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsCenRepListener::~CAknPhysicsCenRepListener
// ---------------------------------------------------------------------------
//
CAknPhysicsCenRepListener::~CAknPhysicsCenRepListener()
    {
    Cancel();
    }
    

// ---------------------------------------------------------------------------
// CAknPhysicsCenRepListener::RunL
// ---------------------------------------------------------------------------
//
void CAknPhysicsCenRepListener::RunL()
    {
    if ( iStatus.Int() != KRequestPending )
        {
        iObserver->CenRepValueChanged( iStatus.Int() );        
        }
    RenewRequestL();
    }


// ---------------------------------------------------------------------------
// CAknPhysicsCenRepListener::DoCancel
// ---------------------------------------------------------------------------
//
void CAknPhysicsCenRepListener::DoCancel()
    {
    iCenRep->NotifyCancelAll();
    }


// ---------------------------------------------------------------------------
// CAknPhysicsCenRepListener::CAknPhysicsCenRepListener
// ---------------------------------------------------------------------------
//
CAknPhysicsCenRepListener::CAknPhysicsCenRepListener(
    CRepository* aCenRep, MAknPhysicsCenRepObserver* aObserver )
    :
    CActive( EPriorityStandard ),
    iCenRep( aCenRep ),
    iObserver( aObserver )
    {
    }


// ---------------------------------------------------------------------------
// CAknPhysicsCenRepListener::ConstructL
// ---------------------------------------------------------------------------
//
void CAknPhysicsCenRepListener::ConstructL()
    {
    CActiveScheduler::Add(this);
    RenewRequestL();
    }


// ---------------------------------------------------------------------------
// CAknPhysicsCenRepListener::RenewRequestL
// ---------------------------------------------------------------------------
//
void CAknPhysicsCenRepListener::RenewRequestL()
    {
    User::LeaveIfError( 
        iCenRep->NotifyRequest(
            KAknPhysicsPartialKey,
            KAknPhysicsKeyBitMask, iStatus) );
    SetActive();
    }

