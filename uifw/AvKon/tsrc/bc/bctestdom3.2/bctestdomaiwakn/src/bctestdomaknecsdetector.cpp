/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  for testing CAknEcsDetector
*
*/



#include "bctestdomaknecsdetector.h"

 
// ======== MEMBER FUNCTIONS ========


// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomAknEcsDetector* CBCTestDomAknEcsDetector::NewL()
    {
    CBCTestDomAknEcsDetector* self = CBCTestDomAknEcsDetector::NewLC();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomAknEcsDetector* CBCTestDomAknEcsDetector::NewLC()
    {
    CBCTestDomAknEcsDetector* self = new( ELeave ) CBCTestDomAknEcsDetector;
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
EXPORT_C CBCTestDomAknEcsDetector::~CBCTestDomAknEcsDetector()
    {
    
    }

// ---------------------------------------------------------------------------
// From class CAknEcsDetector.
// InitialiseL
// ---------------------------------------------------------------------------
//   
EXPORT_C void CBCTestDomAknEcsDetector::ReportEvent(TState aNewState )
    {
    SetObserver( NULL );
    CAknEcsDetector::ReportEvent( aNewState );
    }    
       
// ---------------------------------------------------------------------------
// From class CAknEcsDetector.
//  
// ---------------------------------------------------------------------------
//
EXPORT_C void CBCTestDomAknEcsDetector::SetState( TState aNewState )
    {
    CAknEcsDetector::SetState( aNewState );    
    }

// ---------------------------------------------------------------------------
// From class CAknEcsDetector.
//  
// ---------------------------------------------------------------------------
//
EXPORT_C TBool CBCTestDomAknEcsDetector::OfferEmergencyCall()
    {
    return CAknEcsDetector::OfferEmergencyCall();
    }

// ---------------------------------------------------------------------------
// From class CAknEcsDetector.
//  
// ---------------------------------------------------------------------------
//
void CBCTestDomAknEcsDetector::HandlePhoneStatusL( const TInt /*aStatus*/ )
    {

    }
    
// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomAknEcsDetector::CBCTestDomAknEcsDetector()
    {

    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomAknEcsDetector::ConstructL()
    {

    }


