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
* Description:  AknPhysics flick tracker
*
*/

#include <e32debug.h>

#include "aknphysicsconstants.h"
#include "aknphysicsflicktracker.h"
#include "aknphysicsparameterprovider.h"

const TInt KDistanceFactor( 1000000 );
const TInt KSpeedUpIncrease( 500 );
const TInt KIgnoreSpeedUpEvents( 3 );

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CAknPhysicsFlickTracker::NewL
// ---------------------------------------------------------------------------
//
CAknPhysicsFlickTracker* CAknPhysicsFlickTracker::NewL(
        CAknPhysicsParameterProvider* aProvider )
    {
    CAknPhysicsFlickTracker* self = 
        CAknPhysicsFlickTracker::NewLC( aProvider );
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsFlickTracker::NewLC
// ---------------------------------------------------------------------------
//
CAknPhysicsFlickTracker* CAknPhysicsFlickTracker::NewLC(
        CAknPhysicsParameterProvider* aProvider )
    {
    CAknPhysicsFlickTracker* self 
        = new ( ELeave ) CAknPhysicsFlickTracker( aProvider );
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsFlickTracker::~CAknPhysicsDragObserver
// ---------------------------------------------------------------------------
//
CAknPhysicsFlickTracker::~CAknPhysicsFlickTracker()
    {
    }


// ---------------------------------------------------------------------------
// CAknPhysicsFlickTracker::InitTracker
// ---------------------------------------------------------------------------
//
void CAknPhysicsFlickTracker::InitTracker( const TInt& aCoordinate )
    {
    iDirection = EDirectionNone;
    iCoordinate = aCoordinate;
    InitFlickData( iDirectionData, aCoordinate );
    InitFlickData( iNormalStartData, aCoordinate );
    InitFlickData( iSpeedUpData, aCoordinate );
    InitFlickData( iSpeedUpStartData, aCoordinate );
    iLastDragTime.HomeTime();
    iChangeRegistered = EFalse;
    iSpeedUpRegistered = EFalse;
    iLastDragSpeed = 0;
    iIgnoredEvents = 0;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsFlickTracker::DragChanged
// ---------------------------------------------------------------------------
//
void CAknPhysicsFlickTracker::DragChanged( const TInt& aCoordinate )
    {
    TBool changed( EFalse );
    TBool registered( EFalse );

    // First check if drag direction has changed
    TDirection direction( EDirectionNone );
    if ( aCoordinate > iCoordinate 
        && iDirection != EDirectionForward )
        {
        direction = EDirectionForward;
        }
    else if ( aCoordinate < iCoordinate 
        && iDirection != EDirectionBackward )
        {
        direction = EDirectionBackward;
        }

    if ( direction != EDirectionNone )
        {
        // Direction change only after first direction is saved
        if ( iDirection != EDirectionNone )
            {
            iDirectionData.iCoordinate = aCoordinate;
            iDirectionData.iTime.HomeTime();
            iChangeRegistered = EFalse;
            changed = ETrue;
            }
        iDirection = direction;
        }

    if ( !iChangeRegistered && iDirectionData.iCoordinate != iNormalStartData.iCoordinate )
        {
        TInt distance( iDirectionData.iCoordinate - aCoordinate );
        // Distance from direction change position has exceeded threshold
        // - save the direction changed position as new start position
        if ( Threshold() && Abs( distance ) > Threshold() )
            {
            iNormalStartData = iDirectionData;
            iChangeRegistered = ETrue;
            registered = ETrue;
            }
        }

    // No speed changes are registered when direction has changed
    if ( !changed && !registered )
        {
        SpeedChanged( aCoordinate );    	
        }
    // If direction was changed - reset speed change data
    else if ( registered )
        {
        iSpeedUpData = iNormalStartData;
        iSpeedUpStartData = iNormalStartData;
        iSpeedUpRegistered = EFalse;
        iIgnoredEvents = 0;
        iLastDragSpeed = 0;
        }
    
    iCoordinate = aCoordinate;
    iLastDragTime.HomeTime();
    }


// ---------------------------------------------------------------------------
// CAknPhysicsFlickTracker::FlickStartCoordinate
// ---------------------------------------------------------------------------
//
TInt CAknPhysicsFlickTracker::FlickStartCoordinate() const
    {
    // If move time from flick start point has exceeded flick maximum duration,
    // check if speed has increased and use speed-up position parameters
    if ( NormalFlickMoveTime() > KFlickMaxDuration )
        {
        return iSpeedUpStartData.iCoordinate;
        }
    return iNormalStartData.iCoordinate;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsFlickTracker::FlickMoveTime
// ---------------------------------------------------------------------------
//
TInt CAknPhysicsFlickTracker::FlickMoveTime() const
    {
    // If move time from flick start point has exceeded flick maximum duration,
    // check if speed has increased and use speed-up position parameters
    if ( NormalFlickMoveTime() > KFlickMaxDuration )
        {
        TTime now;
        now.HomeTime();
        return now.MicroSecondsFrom( iSpeedUpStartData.iTime ).Int64();
        }
    return NormalFlickMoveTime();
    }


// ---------------------------------------------------------------------------
// CAknPhysicsFlickTracker::CAknPhysicsFlickTracker
// ---------------------------------------------------------------------------
//
CAknPhysicsFlickTracker::CAknPhysicsFlickTracker( 
        CAknPhysicsParameterProvider* aProvider )
    :
    iDirection( EDirectionNone ),
    iProvider( aProvider )
    {
    }


// ---------------------------------------------------------------------------
// CAknPhysicsFlickTracker::ConstructL
// ---------------------------------------------------------------------------
//
void CAknPhysicsFlickTracker::ConstructL()
    {
    }


// ---------------------------------------------------------------------------
// CAknPhysicsFlickTracker::SpeedChanged
// ---------------------------------------------------------------------------
//
void CAknPhysicsFlickTracker::SpeedChanged( const TInt& aCoordinate )
    {
    TInt newSpeed( DragSpeed( aCoordinate ) );

    // iIgnoreEvents keeps track of such events which speedup positions should
    // be ignored. This is done to calculate speed-up parameters from the first
    // successive speed-up positions
    if ( iIgnoredEvents > 0 )
        {
        iIgnoredEvents--;
        }

    // New speed exceeds the speed threshold - save speed up data
    if ( iIgnoredEvents == 0 
        && iLastDragSpeed && ( newSpeed - iLastDragSpeed > KSpeedUpIncrease )
        && ( ( iDirection == EDirectionForward && aCoordinate > iCoordinate )
        ||  ( iDirection == EDirectionBackward && aCoordinate < iCoordinate ) ) )
        {
        iSpeedUpData.iCoordinate = iCoordinate;
        iSpeedUpData.iTime = iLastDragTime;
        iSpeedUpRegistered = EFalse;
        iIgnoredEvents = KIgnoreSpeedUpEvents;
        iSpeedUpStartData = iNormalStartData;
        }

    // Speed-up hasn't yet been registered - save speed up start data if the
    // drag distance exceeds threshold
    if  ( !iSpeedUpRegistered  && iSpeedUpData.iCoordinate != iSpeedUpStartData.iCoordinate )
        {
        TInt distance( iSpeedUpData.iCoordinate - aCoordinate );
        // Distance from direction change position has exceeded threshold
        // - save the direction changed position as new start position
        if ( Threshold() && Abs( distance ) > Threshold() )
            {
            iSpeedUpStartData = iSpeedUpData;
            iSpeedUpRegistered = ETrue;
            }
        }
    iLastDragSpeed = newSpeed;
    }

// ---------------------------------------------------------------------------
// CAknPhysicsFlickTracker::Threshold
// ---------------------------------------------------------------------------
//
TInt CAknPhysicsFlickTracker::Threshold()
    {
    if ( iProvider )
        {
        return iProvider->DragThreshold();
        }
    return 0;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsFlickTracker::DragSpeed
// ---------------------------------------------------------------------------
//
TInt CAknPhysicsFlickTracker::DragSpeed( const TInt& aNewCoordinate )
    {
    TTime now;
    now.HomeTime();
    TInt moveTime( now.MicroSecondsFrom( iLastDragTime ).Int64() );
    TInt distance( Abs( iCoordinate - aNewCoordinate ) * KDistanceFactor );
    if ( moveTime )
        {
        return ( distance / moveTime ); 
        }
    return 0;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsFlickTracker::InitFlickData
// ---------------------------------------------------------------------------
//
void CAknPhysicsFlickTracker::InitFlickData( TAknPhysicsTrackerData& aData, 
        const TInt& aCoordinate )
    {
    aData.iCoordinate = aCoordinate;
    aData.iTime.HomeTime();
    }


// ---------------------------------------------------------------------------
// CAknPhysicsFlickTracker::NormalFlickMoveTime
// ---------------------------------------------------------------------------
//
TInt CAknPhysicsFlickTracker::NormalFlickMoveTime() const
    {
    TTime now;
    now.HomeTime();
    return now.MicroSecondsFrom( iNormalStartData.iTime ).Int64();
    }
