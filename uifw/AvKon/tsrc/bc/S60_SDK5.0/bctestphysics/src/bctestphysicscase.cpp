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
* Description:  container
*
*/

#include <w32std.h>
#include <coecntrl.h>
#include <aknphysics.h>

#include "bctestphysicscase.h"
#include "bctestphysicscontainer.h"
#include "bctestphysics.hrh"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestPhysicsCase* CBCTestPhysicsCase::NewL( CBCTestPhysicsContainer* 
    aContainer )
    {
    CBCTestPhysicsCase* self = new( ELeave ) CBCTestPhysicsCase( 
        aContainer );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestPhysicsCase::CBCTestPhysicsCase( CBCTestPhysicsContainer* 
    aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestPhysicsCase::~CBCTestPhysicsCase()
    {  
    delete iPhysics;
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestPhysicsCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestPhysicsCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestPhysicsCase::BuildScriptL()
    { 
    // Add script as your need.   
    AddTestL( DELAY(1), LeftCBA, KeyOK, TEND );    
    }
    
// ---------------------------------------------------------------------------
// CBCTestPhysicsCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestPhysicsCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline1 || aCmd > EBCTestCmdOutline1 )
        {
        return;
        }
    // Call release before prepare to let container has time to draw the 
    // control created in PrepareCaseL.
    ReleaseCaseL();
    PrepareCaseL( aCmd );
    switch ( aCmd )  
        {
        case EBCTestCmdOutline1:
            TestPhysicsL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestPhysicsCase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCTestPhysicsCase::PrepareCaseL( TInt aCmd )
    {        
    switch ( aCmd )
        {
        case EBCTestCmdOutline1:
            // Here is a simple demo. You should create your control 
            // instead of this.
            iControl = new( ELeave ) CCoeControl();            
            iControl->SetContainerWindowL( *iContainer );
            iControl->MakeVisible( ETrue );
            break;
        default:
            break;
        }
    // Pass the owner of iControl to iContainer.
    iContainer->SetControl( iControl );
    }

// ---------------------------------------------------------------------------
// CBCTestPhysicsCase::ReleaseCaseL
// ---------------------------------------------------------------------------
//   
void CBCTestPhysicsCase::ReleaseCaseL()
    {
    // let container delete the component control.
    iContainer->ResetControl();
    iControl = NULL;
    }

// ---------------------------------------------------------------------------
// CBCTestPhysicsCase::ViewPositionChanged
// ---------------------------------------------------------------------------
//   
void CBCTestPhysicsCase::ViewPositionChanged( const TPoint& aNewPosition,
        TBool aDrawNow,
        TUint aFlags )
	{
	
	}

// ---------------------------------------------------------------------------
// CBCTestPhysicsCase::PhysicEmulationEnded
// ---------------------------------------------------------------------------
//   
void CBCTestPhysicsCase::PhysicEmulationEnded()
	{
	
	}

// ---------------------------------------------------------------------------
// CBCTestPhysicsCase::ViewPosition
// ---------------------------------------------------------------------------
//   
TPoint CBCTestPhysicsCase::ViewPosition() const
    {
    return TPoint( 0, 0 );
    }

// ---------------------------------------------------------------------------
// CBCTestPhysicsCase::TestPhysicsL
// ---------------------------------------------------------------------------
//    
void CBCTestPhysicsCase::TestPhysicsL()
    {
    _LIT( KCAknPhysicsNewL, "CAknPhysics::NewL(MAknPhysicsObserver& \
    		aObserver,CCoeControl* aViewControl) tested" );
    _LIT( KCAknPhysicsCenRepListenerNewL,"CAknPhysicsCenRepListener::NewL(\
    	  CRepository* aCenRep,MAknPhysicsCenRepObserver* aObserver)tested" );
    _LIT( KCAknPhysicsCenRepListenerNewLC,"CAknPhysicsCenRepListener::NewLC(\
    	  CRepository* ,MAknPhysicsCenRepObserver* ) tested" );
    _LIT( KCAknPhysicsConeObserverNewL,"CAknPhysicsConeObserver::NewL(\
    	  CAknPhysics* ,CAknPhysicsRestrictor* ) tested" );
    _LIT( KCAknPhysicsConeObserverNewLC,"CAknPhysicsConeObserver::NewLC(\
    	  CAknPhysics* ,CAknPhysicsRestrictor* ) tested" );
    _LIT( KCAknPhysicsDragObserverNewL, "CAknPhysicsDragObserver::NewL(\
    	  CAknPhysicsParameterProvider* aProvider tested" );
    _LIT( KCAknPhysicsDragObserverNewLC, "CAknPhysicsDragObserver::NewLC(\
    	  CAknPhysicsParameterProvider* aProvider tested" );
    _LIT( KCAknPhysicsEngineNewL, "CAknPhysicsEngine::NewL(\
    	  CAknPhysics* aPhysics) tested" );
    _LIT( KCAknPhysicsEngineNewLC, "CAknPhysicsEngine::NewLC(\
    	  CAknPhysics* aPhysics) tested" );
    _LIT( KCAknPhysicsKeyConsumerNewL, "CAknPhysicsKeyConsumer::NewL(\
    	  CAknPhysicsConeObserver* aConeObserver) tested" );
    _LIT( KCAknPhysicsKeyConsumerNewLC, "CAknPhysicsKeyConsumer::NewLC(\
    	  CAknPhysicsConeObserver* aConeObserver) tested" );
    _LIT( KCAknPhysicsParameterProviderNewL,"CAknPhysicsParameterProvider::\
    	  NewL() tested" );
    _LIT( KCAknPhysicsParameterProviderNewLC,"CAknPhysicsParameterProvider::\
    	  NewL() testedC" );
    _LIT( KCAknPhysicsRestrictorNewL,"CAknPhysicsRestrictor::\
    	  NewL(CAknPhysicsParameterProvider* aProvider) tested" );
    _LIT( KCAknPhysicsRestrictorNewLC,"CAknPhysicsRestrictor::\
    	  NewLC(CAknPhysicsParameterProvider* aProvider) tested" );
    _LIT( KInitPhysicsL, "CAknPhysics::InitPhysicsL() tested" );
    _LIT( KStartPhysics, "CAknPhysics::StartPhysics() tested" );
    _LIT( KOngoingPhysicsAction, "CAknPhysics::OngoingPhysicsAction() \
    		tested" );
    _LIT( KStopPhysics, "CAknPhysics::StopPhysics() tested" );
    _LIT( KRegisterPanningPosition, "CAknPhysics::RegisterPanningPosition\
    	  () tested" );
    _LIT( KSetFriction, "CAknPhysics::SetFriction() tested" );
    _LIT( KResetFriction, "CAknPhysics::ResetFriction() tested" );
    _LIT( KHighlightTimeout, "CAknPhysics::HighlightTimeout() tested" );    
    _LIT( KDragThreshold, "CAknPhysics::DragThreshold() tested" );
    _LIT( KFeatureEnabled, "CAknPhysics::FeatureEnabled() tested" );
    _LIT( KEventHandlingAllowed, "CAknPhysics::EventHandlingAllowed()\
    	  tested" );
    _LIT( KUpdateViewWindowControl, "CAknPhysics::UpdateViewWindowControl()\
    	  tested" );
    
    const TSize worldSize( 640, 360 );
    const TSize viewSize( 640, 360 );
    
    iPhysics = CAknPhysics::NewL( *this, iContainer );
    AssertNotNullL( iPhysics, KCAknPhysicsNewL );
    AssertTrueL( ETrue, KCAknPhysicsCenRepListenerNewL );
    AssertTrueL( ETrue, KCAknPhysicsCenRepListenerNewLC );
    AssertTrueL( ETrue, KCAknPhysicsConeObserverNewL );
    AssertTrueL( ETrue, KCAknPhysicsConeObserverNewLC );
    AssertTrueL( ETrue, KCAknPhysicsDragObserverNewL );
    AssertTrueL( ETrue, KCAknPhysicsDragObserverNewLC );
    AssertTrueL( ETrue, KCAknPhysicsEngineNewL );
    AssertTrueL( ETrue, KCAknPhysicsEngineNewLC );
    AssertTrueL( ETrue, KCAknPhysicsKeyConsumerNewL );
    AssertTrueL( ETrue, KCAknPhysicsKeyConsumerNewLC );
    AssertTrueL( ETrue, KCAknPhysicsParameterProviderNewL );
    AssertTrueL( ETrue, KCAknPhysicsParameterProviderNewLC );
    AssertTrueL( ETrue, KCAknPhysicsRestrictorNewL );
    AssertTrueL( ETrue, KCAknPhysicsRestrictorNewLC );
    
    iPhysics->InitPhysicsL( worldSize, viewSize, EFalse );
    AssertTrueL( ETrue, KInitPhysicsL );
 
    TTime time;
    time.HomeTime();
    time = time + TTimeIntervalSeconds( 2 );
    TPoint dragPosition( 50, 50 );
    iPhysics->StartPhysics( dragPosition, time );
    AssertTrueL( ETrue, KStartPhysics );
    
    iPhysics->OngoingPhysicsAction();
    AssertTrueL( ETrue, KOngoingPhysicsAction );
    
    iPhysics->HighlightTimeout();
    AssertTrueL( ETrue, KHighlightTimeout );
    
    iPhysics->DragThreshold();
    AssertTrueL( ETrue, KDragThreshold );
    
    iPhysics->FeatureEnabled();
    AssertTrueL( ETrue, KFeatureEnabled );
    
    iPhysics->EventHandlingAllowed();
    AssertTrueL( ETrue, KEventHandlingAllowed );
    
    iPhysics->UpdateViewWindowControl();
    AssertTrueL( ETrue, KUpdateViewWindowControl );
    
    iPhysics->ResetFriction();
    AssertTrueL( ETrue, KResetFriction );
    
    iPhysics->SetFriction( 0.1 );
    AssertTrueL( ETrue, KSetFriction );
    
    iPhysics->StopPhysics();
    AssertTrueL( ETrue, KStopPhysics );
    }
    