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
    CAknFormPhysics* self = new ( ELeave ) CAknFormPhysics( aParent, 
        aRecordingGc );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// CAknFormPhysics::~CAknFormPhysics
// ---------------------------------------------------------------------------
//
CAknFormPhysics::~CAknFormPhysics()
    {
    delete iPhysics;
    }


// ---------------------------------------------------------------------------
// CAknFormPhysics::InitPhysicsL
// ---------------------------------------------------------------------------
//
void CAknFormPhysics::InitPhysicsL( const TSize& aWorldSize, 
    const TSize& aViewSize, const TPoint& aViewCenter )
    {
    iPhysics->InitPhysicsL( aWorldSize, aViewSize, EFalse );
    iViewCenter = aViewCenter;
    iWorldSize = aWorldSize;
    iViewSize = aViewSize;
    }


// ---------------------------------------------------------------------------
// CAknFormPhysics::Stop
// ---------------------------------------------------------------------------
//
void CAknFormPhysics::Stop()
    {
    iPhysics->StopPhysics();
    iPhysics->ResetFriction();
    }
    

// ---------------------------------------------------------------------------
// CAknFormPhysics::StartFlick
// ---------------------------------------------------------------------------
//
TBool CAknFormPhysics::StartFlick( const TPoint& aLength, 
                                   const TTime& aStartTime )
    {
    if (  PhysicsAllowed() )
        {
        TPoint drag( aLength );
        if ( iPhysics->StartPhysics( drag, aStartTime ) )
            {
            // reset benchmark variables
            iStartTime.HomeTime();
            iFrameCount = 0;
            return ETrue;
            }
        }

    PhysicEmulationEnded();
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
    if (  PhysicsAllowed() && iPhysics )
        {
        iPhysics->RegisterPanningPosition( aDelta );
        }
    }


// ---------------------------------------------------------------------------
// CAknFormPhysics::ViewPositionChanged
// ---------------------------------------------------------------------------
//
void CAknFormPhysics::ViewPositionChanged( const TPoint& aNewPosition,
                                           TBool aDrawNow,
                                           TUint /*aFlags*/ )
    {
    if ( !PhysicsAllowed() )
        {
        return;
        }
    TInt fps = 0;
    iViewCenter = aNewPosition;

    // benchmark / debug part
    if ( iFrameCount != -1 )
        {
        ++iFrameCount;
        TTime now;
        now.HomeTime();
        
        TInt64 duration = now.MicroSecondsFrom( iStartTime ).Int64();
        
        if ( duration > 0 )
            {
            fps = iFrameCount * 1000000 / duration;
            }
        }

    TBuf<128> msg;
    msg.Format( _L( "%dfps" ), fps );

    iParent.ScrollCacheByPixels( iViewCenter.iY, msg, aDrawNow );
    }


// ---------------------------------------------------------------------------
// CAknFormPhysics::PhysicEmulationEnded
// ---------------------------------------------------------------------------
//
void CAknFormPhysics::PhysicEmulationEnded()
    {
    iParent.Synchronize();
    iFrameCount = -1;
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


// ---------------------------------------------------------------------------
// CAknFormPhysics::PhysicsAllowed
// ---------------------------------------------------------------------------
//
TBool CAknFormPhysics::PhysicsAllowed() const
    {
    return ETrue;
    }
