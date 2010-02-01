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
* Description:  AknPhysics drag event observer
*
*/


#include <w32std.h>

#include "aknphysicsdragobserver.h"
#include "aknphysicsflicktracker.h"
#include "aknphysicsparameterprovider.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CAknPhysicsDragObserver::NewL
// ---------------------------------------------------------------------------
//
CAknPhysicsDragObserver* CAknPhysicsDragObserver::NewL(
    CAknPhysicsParameterProvider* aProvider )
    {
    CAknPhysicsDragObserver* self = 
        CAknPhysicsDragObserver::NewLC( aProvider );
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsDragObserver::NewLC
// ---------------------------------------------------------------------------
//
CAknPhysicsDragObserver* CAknPhysicsDragObserver::NewLC(
    CAknPhysicsParameterProvider* aProvider )
    {
    CAknPhysicsDragObserver* self 
        = new ( ELeave ) CAknPhysicsDragObserver();
    CleanupStack::PushL( self );
    self->ConstructL( aProvider );
    return self;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsDragObserver::~CAknPhysicsDragObserver
// ---------------------------------------------------------------------------
//
CAknPhysicsDragObserver::~CAknPhysicsDragObserver()
    {
    delete iVerticalTracker;
    delete iHorizontalTracker;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsDragObserver::RegisterEventPosition
// ---------------------------------------------------------------------------
//
void CAknPhysicsDragObserver::RegisterEventPosition( 
    const TPointerEvent* aEvent )
    {
    if ( aEvent->iType == TPointerEvent::EButton1Down || 
         ( !iPointerDown && aEvent->iType == TPointerEvent::EDrag ) )
        {
        HandlePointerDownEvent( aEvent->iPosition );
        iPointerDown = ETrue;
        }
    else if ( aEvent->iType == TPointerEvent::EDrag )
        {
        HandlePointerDragEvent( aEvent->iPosition );
        }
    else if ( aEvent->iType == TPointerEvent::EButton1Up )
        {
        if ( iPointerDown )
            {
            HandlePointerUpEvent( aEvent->iPosition );
            }
        else
            {
            Reset();
            }  
        iPointerDown = EFalse;            
        }
    }


// ---------------------------------------------------------------------------
// CAknPhysicsDragObserver::ChangedDragDistance
// ---------------------------------------------------------------------------
//
TPoint CAknPhysicsDragObserver::ChangedDragDistance() const
    {
    TPoint dragDistance;
    dragDistance.iY = iVerticalTracker->FlickStartCoordinate() - iUpPosition.iY;
    dragDistance.iX = iHorizontalTracker->FlickStartCoordinate() - iUpPosition.iX;
    return dragDistance;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsDragObserver::ChangedVerticalDragMoveTime
// ---------------------------------------------------------------------------
//
TInt CAknPhysicsDragObserver::ChangedVerticalDragMoveTime() const
    {
    if ( iVerticalTracker )
        {
        return iVerticalTracker->FlickMoveTime();
        }
    return 0;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsDragObserver::ChangedHorizontalDragMoveTime
// ---------------------------------------------------------------------------
//
TInt CAknPhysicsDragObserver::ChangedHorizontalDragMoveTime() const
    {
    if ( iHorizontalTracker )
        {
        return iHorizontalTracker->FlickMoveTime();
        }
    return 0;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsDragObserver::DragChanged
// ---------------------------------------------------------------------------
//
TInt CAknPhysicsDragObserver::DragChanged() const
    {
    TBool changed( EFalse );
    if ( iVerticalTracker )
        {
        changed = iVerticalTracker->FlickStartCoordinate() != iDownPosition.iY;
        }
    if ( !changed && iHorizontalTracker )
        {
        changed = iHorizontalTracker->FlickStartCoordinate() != iDownPosition.iX;
        }
    return changed;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsDragObserver::CAknPhysicsDragObserver
// ---------------------------------------------------------------------------
//
CAknPhysicsDragObserver::CAknPhysicsDragObserver()
    {
    }


// ---------------------------------------------------------------------------
// CAknPhysicsDragObserver::ConstructL
// ---------------------------------------------------------------------------
//
void CAknPhysicsDragObserver::ConstructL(
        CAknPhysicsParameterProvider* aProvider )
    {
    iVerticalTracker = CAknPhysicsFlickTracker::NewL( aProvider );
    iHorizontalTracker = CAknPhysicsFlickTracker::NewL( aProvider );
    }


// ---------------------------------------------------------------------------
// CAknPhysicsDragObserver::HandlePointerDownEvent
// ---------------------------------------------------------------------------
//
void CAknPhysicsDragObserver::HandlePointerDownEvent( 
    const TPoint& aPosition )
    {
    iDownPosition = aPosition;
    iUpPosition = TPoint();
    iVerticalTracker->InitTracker( aPosition.iY );
    iHorizontalTracker->InitTracker( aPosition.iX );
    }


// ---------------------------------------------------------------------------
// CAknPhysicsDragObserver::HandlePointerDragEvent
// ---------------------------------------------------------------------------
//
void CAknPhysicsDragObserver::HandlePointerDragEvent( 
    const TPoint& aPosition )
    {
    if ( iVerticalTracker )
        {
        iVerticalTracker->DragChanged( aPosition.iY );
        }
    if ( iHorizontalTracker )
        {
        iHorizontalTracker->DragChanged( aPosition.iX );
        }
    }


// ---------------------------------------------------------------------------
// CAknPhysicsDragObserver::HandlePointerUpEvent
// ---------------------------------------------------------------------------
//
void CAknPhysicsDragObserver::HandlePointerUpEvent( 
    const TPoint& aPosition )
    {
    HandlePointerDragEvent( aPosition );
    iUpPosition = aPosition;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsDragObserver::Reset
// ---------------------------------------------------------------------------
//
void CAknPhysicsDragObserver::Reset()
    {
    iDownPosition.SetXY( 0, 0 );
    iUpPosition.SetXY( 0, 0 );
    iVerticalTracker->InitTracker( 0 );
    iHorizontalTracker->InitTracker( 0 );    
    }

