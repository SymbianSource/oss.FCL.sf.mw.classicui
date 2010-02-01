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
* Description:  Restrictor of AknPhysics
*
*/


#include <e32debug.h>

#include "aknphysicsrestrictor.h"
#include "aknphysicsparameterprovider.h"

const TReal KNotRestrictedSegment( 1.0 );
const TInt KEmptySpaceFactor( 100 );

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CAknPhysicsRestrictor::NewL
// ---------------------------------------------------------------------------
//
CAknPhysicsRestrictor* CAknPhysicsRestrictor::NewL(
    CAknPhysicsParameterProvider* aProvider )
    {
    CAknPhysicsRestrictor* self = CAknPhysicsRestrictor::NewLC( aProvider );
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsRestrictor::NewLC
// ---------------------------------------------------------------------------
//
CAknPhysicsRestrictor* CAknPhysicsRestrictor::NewLC( 
    CAknPhysicsParameterProvider* aProvider )
    {
    CAknPhysicsRestrictor* self = 
        new ( ELeave ) CAknPhysicsRestrictor( aProvider );
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsRestrictor::~CAknPhysicsRestrictor
// ---------------------------------------------------------------------------
//
CAknPhysicsRestrictor::~CAknPhysicsRestrictor()
    {
    }


// ---------------------------------------------------------------------------
// CAknPhysicsRestrictor::UpdatePhysicsEnvironment
// ---------------------------------------------------------------------------
//
void CAknPhysicsRestrictor::UpdatePhysicsEnvironment( const TSize& aWorldSize,
                                                      const TSize& aViewSize,
                                                      const TBool& aLandscape )
    {
    iWorldSize = aWorldSize;
    iViewSize = aViewSize;
    iLandscape = aLandscape;
    CalculateViewLimits();
    }


// -----------------------------------------------------------------------------
// CAknPhysicsRestrictor::ViewTopPosition()
// -----------------------------------------------------------------------------
//
TInt CAknPhysicsRestrictor::ViewTopPosition() const
    {
    TInt topPosition( 0 );

    if ( iLandscape )
        {
        topPosition = iViewSize.iWidth/2;
        }
    else
        {
        topPosition = iViewSize.iHeight/2;
        }
    return topPosition;
    }


// -----------------------------------------------------------------------------
// CAknPhysicsRestrictor::ViewBottomPosition()
// -----------------------------------------------------------------------------
//
TInt CAknPhysicsRestrictor::ViewBottomPosition() const
    {
    TInt bottomPosition( 0 );

    // If world size smaller than view size, bottom position is same as top
    // position
    if ( iLandscape && iViewSize.iWidth >= iWorldSize.iWidth
        || !iLandscape && iViewSize.iHeight >= iWorldSize.iHeight )
        {
        bottomPosition = ViewTopPosition();        
        }
        
    // Otherwise calculate bottom position according to world size
    else
        {
        if ( iLandscape )
            {
            bottomPosition = iWorldSize.iWidth - iViewSize.iWidth / 2;
            }
        else
            {
            bottomPosition = iWorldSize.iHeight - iViewSize.iHeight / 2;
            }   
        }
    return bottomPosition;
    }


// -----------------------------------------------------------------------------
// CAknPhysicsRestrictor::PositionRevealsEmptySpace()
// -----------------------------------------------------------------------------
//
TBool CAknPhysicsRestrictor::PositionRevealsEmptySpace( TPoint& aPosition )
    {
    TInt startTop( ViewTopPosition() );
    TInt endBottom( ViewBottomPosition() );
    TInt* positionCoordinate;

    if ( iLandscape )
        {
        positionCoordinate = &aPosition.iX;
        }
    else
        {
        positionCoordinate = &aPosition.iY;
        }

    if ( aPosition == TPoint()
        || *positionCoordinate >= startTop && *positionCoordinate <= endBottom )
        {
        return EFalse;
        }
    
    if ( *positionCoordinate < startTop || WorldFitsToView() )
        {
        *positionCoordinate = startTop;
        }
    else
        {
        *positionCoordinate = endBottom;
        }
    return ETrue;
    }


// -----------------------------------------------------------------------------
// CAknPhysicsRestrictor::AllowedViewPosition()
// -----------------------------------------------------------------------------
//
TBool CAknPhysicsRestrictor::AllowedViewPosition( TPoint& aPosition )
    {
    // No restrictions to empty space, view position always allowed
    if ( !iEmptySpaceRestricted )
        {
        return ETrue;
        }
    
    TBool allow( EFalse );

    TInt *coord;
    if ( iLandscape )
        {
        coord = &aPosition.iX;
        }
    else
        {
        coord = &aPosition.iY;
        }

    // View position is allowed
    if ( *coord >= iPositionTopLimit && *coord <= iPositionBottomLimit )
        {
        allow = ETrue;
        iViewReachedLimit = EFalse;
        }

    // View has reached the limit for the first time - adjust the position
    // exactly to limit position
    else if ( !iViewReachedLimit )
        {
        allow = ETrue;
        iViewReachedLimit = ETrue;
        if ( *coord < iPositionTopLimit )
            {
            *coord = iPositionTopLimit;
            }
        else
            {
            *coord = iPositionBottomLimit;
            }
        }

    // Else view has already reached the limit, view position is not allowed
    // and no need to notify physics observer

    return allow;
    }


// -----------------------------------------------------------------------------
// CAknPhysicsRestrictor::AdjustDragPoint()
// -----------------------------------------------------------------------------
//
void CAknPhysicsRestrictor::AdjustDragPoint( TPoint& aDragPoint )
    {
    if ( iViewReachedLimit )
        {
        iViewReachedLimit = EFalse;

        TInt *coord;
        if ( iLandscape )
            {
            coord = &aDragPoint.iX;
            }
        else
            {
            coord = &aDragPoint.iY;
            }

        if ( *coord < 0 )
            {
            *coord = -iEmptySpaceArea;
            }
        else
            {
            *coord = iEmptySpaceArea;
            }
        }
    }


// -----------------------------------------------------------------------------
// CAknPhysicsRestrictor::WorldSize()
// -----------------------------------------------------------------------------
//
TSize CAknPhysicsRestrictor::WorldSize() const
    {
    return iWorldSize;
    }


// -----------------------------------------------------------------------------
// CAknPhysicsRestrictor::WorldSize()
// -----------------------------------------------------------------------------
//
TBool CAknPhysicsRestrictor::WorldInLandscape() const
    {
    return iLandscape;
    }


// -----------------------------------------------------------------------------
// CAknPhysicsRestrictor::ParameterProvider()
// -----------------------------------------------------------------------------
//
CAknPhysicsParameterProvider* CAknPhysicsRestrictor::ParameterProvider() const
    {
    return iProvider;
    }


// -----------------------------------------------------------------------------
// CAknPhysicsRestrictor::PositionToViewTop()
// -----------------------------------------------------------------------------
//
void CAknPhysicsRestrictor::PositionToViewTop( TPoint& aPosition ) const
    {
    TInt topPos( ViewTopPosition() );
    if ( iLandscape )
        {
        aPosition.iX = topPos;
        }
    else
        {
        aPosition.iY = topPos;
        }
    }


// -----------------------------------------------------------------------------
// CAknPhysicsRestrictor::PositionToViewBottom()
// -----------------------------------------------------------------------------
//
void CAknPhysicsRestrictor::PositionToViewBottom( TPoint& aPosition ) const
    {
    TInt bottomPos( ViewBottomPosition() );

    if ( iLandscape )
        {
        aPosition.iX = bottomPos;
        }
    else
        {
        aPosition.iY = bottomPos;
        }
    }


// -----------------------------------------------------------------------------
// CAknPhysicsRestrictor::PositionIsOutOfBoundaries()
// -----------------------------------------------------------------------------
//
TBool CAknPhysicsRestrictor::PositionIsOutOfBoundaries( 
    const TPoint& aPosition, const TBool& aTopCollision ) const
    {
    TInt startTop( ViewTopPosition() );
    TInt endBottom( ViewBottomPosition() );
    TInt positionCoordinate;

    if ( iLandscape )
        {
        positionCoordinate = aPosition.iX;
        }
    else
        {
        positionCoordinate = aPosition.iY;
        }
        

    if ( aTopCollision && positionCoordinate > startTop )
        {
        positionCoordinate = startTop;
        return ETrue;
        }
    else if ( !aTopCollision && positionCoordinate < endBottom )
        {
        positionCoordinate = endBottom;
        return ETrue;
        }
    return EFalse;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsRestrictor::CAknPhysicsRestrictor
// ---------------------------------------------------------------------------
//
CAknPhysicsRestrictor::CAknPhysicsRestrictor(
    CAknPhysicsParameterProvider* aProvider )
    : 
    iWorldSize( 0, 0 ),
    iViewSize( 0, 0 ),
    iLandscape( EFalse ),
    iPositionTopLimit( 0 ),
    iPositionBottomLimit( 0 ),
    iEmptySpaceArea( 0 ),
    iProvider( aProvider ),
    iViewReachedLimit( EFalse ),
    iEmptySpaceRestricted( EFalse )
    {
    }


// ---------------------------------------------------------------------------
// CAknPhysicsRestrictor::ConstructL
// ---------------------------------------------------------------------------
//
void CAknPhysicsRestrictor::ConstructL()
    {
    }


// ---------------------------------------------------------------------------
// CAknPhysicsRestrictor::CalculateViewLimits
// ---------------------------------------------------------------------------
//
void CAknPhysicsRestrictor::CalculateViewLimits()
    {
    if ( !iProvider )
        {
        return;
        }
        
    TInt viewHeight( iViewSize.iHeight );
    TInt worldHeight( iWorldSize.iHeight );
    TReal emptySegment( KNotRestrictedSegment );

    if ( iLandscape )
        {
        viewHeight = iViewSize.iWidth;
        worldHeight = iWorldSize.iWidth;
        }
        
    // Calculate bottom limit
    if ( viewHeight > worldHeight )
        {
        emptySegment = 
        	( TReal ) iProvider->ShortListEmptySpace() / KEmptySpaceFactor;
        iEmptySpaceArea = 
            worldHeight * ( emptySegment );
        iPositionBottomLimit = viewHeight / 2 + iEmptySpaceArea;
        }
    else
        {
        emptySegment = 
        	( TReal ) iProvider->LongListEmptySpace() / KEmptySpaceFactor;
        iEmptySpaceArea = 
            viewHeight * ( emptySegment );
        iPositionBottomLimit = worldHeight - viewHeight / 2 + iEmptySpaceArea;
        }

    // Calculate top limit
    iPositionTopLimit = viewHeight / 2 - iEmptySpaceArea;
    
    // Check if empty space is really restricted
    if ( emptySegment == KNotRestrictedSegment )
        {
        iEmptySpaceRestricted = EFalse;
        }
    else
        {
        iEmptySpaceRestricted = ETrue;
        }
    }


// ---------------------------------------------------------------------------
// CAknPhysicsRestrictor::WorldFitsToView
// ---------------------------------------------------------------------------
//
TBool CAknPhysicsRestrictor::WorldFitsToView()
    {
    if ( iLandscape && iWorldSize.iWidth < iViewSize.iWidth )
        {
        return ETrue;
        }
    else if ( !iLandscape && iWorldSize.iHeight < iViewSize.iHeight )
        {
        return ETrue;
        }
    return EFalse;
    }

