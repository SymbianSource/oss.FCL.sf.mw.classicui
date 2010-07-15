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
* Description:    Class to store physics related data in forms.
*
*/




#include "aknformphysics.h"
#include <aknphysics.h>
#include <coecntrl.h>
#include <coemain.h>
#include <eikdpage.h>
#include "akntrace.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CAknFormPhysics::CAknFormPhysics
// ---------------------------------------------------------------------------
//
CAknFormPhysics::CAknFormPhysics( CEikDialogPage& aParent, 
    CAknRecordingGc& aRecordingGc ) : iParent( aParent ), 
    iRecordingGc( aRecordingGc )
    {
    }


// ---------------------------------------------------------------------------
// CAknFormPhysics::ConstructL
// ---------------------------------------------------------------------------
//
void CAknFormPhysics::ConstructL()
    {
    iPhysics = CAknPhysics::NewL( *this, &iParent );
    }


// ---------------------------------------------------------------------------
// CAknFormPhysics::NewL
// ---------------------------------------------------------------------------
//
CAknFormPhysics* CAknFormPhysics::NewL( CEikDialogPage& aParent, 
    CAknRecordingGc& aRecordingGc )
    {
    _AKNTRACE_FUNC_ENTER;
    CAknFormPhysics* self = new ( ELeave ) CAknFormPhysics( aParent, 
        aRecordingGc );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    _AKNTRACE_FUNC_EXIT;    
    return self;
    }


// ---------------------------------------------------------------------------
// CAknFormPhysics::~CAknFormPhysics
// ---------------------------------------------------------------------------
//
CAknFormPhysics::~CAknFormPhysics()
    {
    _AKNTRACE_FUNC_ENTER;
    delete iPhysics;
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CAknFormPhysics::InitPhysicsL
// ---------------------------------------------------------------------------
//
void CAknFormPhysics::InitPhysicsL( const TSize& aWorldSize, 
    const TSize& aViewSize, const TPoint& aViewCenter )
    {
    _AKNTRACE_FUNC_ENTER;
    iPhysics->InitPhysicsL( aWorldSize, aViewSize, EFalse );
    iViewCenter = aViewCenter;
    iWorldSize = aWorldSize;
    iViewSize = aViewSize;
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CAknFormPhysics::Stop
// ---------------------------------------------------------------------------
//
void CAknFormPhysics::Stop()
    {
    _AKNTRACE_FUNC_ENTER;
    iPhysics->StopPhysics();
    iPhysics->ResetFriction();
    _AKNTRACE_FUNC_EXIT;
    }
    

// ---------------------------------------------------------------------------
// CAknFormPhysics::StartFlick
// ---------------------------------------------------------------------------
//
TBool CAknFormPhysics::StartFlick( const TPoint& aLength, 
                                   const TTime& aStartTime )
    {
    _AKNTRACE_FUNC_ENTER;
    TPoint drag( aLength );

    if ( iPhysics->StartPhysics( drag, aStartTime ) )
        {
        return ETrue;
        }

    PhysicEmulationEnded();
    _AKNTRACE_FUNC_EXIT;
    return EFalse;
    }


// ---------------------------------------------------------------------------
// CAknFormPhysics::HighlightDelay
// ---------------------------------------------------------------------------
//
TInt CAknFormPhysics::HighlightDelay() const
    {
    return iPhysics->HighlightTimeout();
    }


// ---------------------------------------------------------------------------
// CAknFormPhysics::DragThreshold
// ---------------------------------------------------------------------------
//
TInt CAknFormPhysics::DragThreshold() const
    {
    return iPhysics->DragThreshold();
    }


// ---------------------------------------------------------------------------
// CAknFormPhysics::WorldSize
// ---------------------------------------------------------------------------
//
TSize CAknFormPhysics::ViewSize() const
    {
    return iViewSize;
    }


// ---------------------------------------------------------------------------
// CAknFormPhysics::SetPanningPosition
// ---------------------------------------------------------------------------
//
void CAknFormPhysics::SetPanningPosition( const TPoint& aDelta )
    {
    _AKNTRACE_FUNC_ENTER;
    if ( iPhysics )
        {
        iPhysics->RegisterPanningPosition( aDelta );
        }
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CAknFormPhysics::ViewPositionChanged
// ---------------------------------------------------------------------------
//
void CAknFormPhysics::ViewPositionChanged( const TPoint& aNewPosition,
                                           TBool aDrawNow,
                                           TUint /*aFlags*/ )
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "The Position of aNewPosition are: ( %d, %d ) ", 
    		aNewPosition.iX, aNewPosition.iY );

    iViewCenter = aNewPosition;
    iParent.ScrollCacheByPixels( iViewCenter.iY, aDrawNow );
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CAknFormPhysics::PhysicEmulationEnded
// ---------------------------------------------------------------------------
//
void CAknFormPhysics::PhysicEmulationEnded()
    {
    _AKNTRACE_FUNC_ENTER;
    iParent.Synchronize();
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CAknFormPhysics::ViewPosition
// ---------------------------------------------------------------------------
//
TPoint CAknFormPhysics::ViewPosition() const
    {
    return iViewCenter;
    }


// ---------------------------------------------------------------------------
// CAknFormPhysics::CanBeStopped
// ---------------------------------------------------------------------------
//
TBool CAknFormPhysics::CanBeStopped() const
    {
    return iPhysics->OngoingPhysicsAction() != 
        CAknPhysics::EAknPhysicsActionBouncing;
    }


// ---------------------------------------------------------------------------
// CAknFormPhysics::OngoingPhysicsAction
// ---------------------------------------------------------------------------
//
TInt CAknFormPhysics::OngoingPhysicsAction() const
    {
    return iPhysics->OngoingPhysicsAction();
    }

/// ---------------------------------------------------------------------------
// CAknFormPhysics::ViewTopY
// ---------------------------------------------------------------------------
//
TInt CAknFormPhysics::ViewTopY() const
    {
    return iViewCenter.iY - iParent.Size().iHeight / 2;
    }


// ---------------------------------------------------------------------------
// CAknFormPhysics::ViewDistance
// ---------------------------------------------------------------------------
//
TInt CAknFormPhysics::ViewCenterDistance() const
    {
    return iParent.Size().iHeight / 2;
    }


// ---------------------------------------------------------------------------
// CAknFormPhysics::SetViewCenter
// ---------------------------------------------------------------------------
//
void CAknFormPhysics::SetViewCenter( const TPoint& aPosition )
    {
    iViewCenter = aPosition;
    }


// ---------------------------------------------------------------------------
// CAknFormPhysics::ViewCenter
// ---------------------------------------------------------------------------
//
TPoint CAknFormPhysics::ViewCenter() const
    {
    return iViewCenter;
    }
	
