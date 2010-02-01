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


#ifndef C_AKNPHYSICSRESTRICTOR_H
#define C_AKNPHYSICSRESTRICTOR_H


#include <e32base.h>

class CAknPhysicsParameterProvider;

/**
 *  Physics restrictor
 *
 *  @lib aknphysics
 *  @since S60 v5.0
 */
NONSHARABLE_CLASS( CAknPhysicsRestrictor ) : public CBase
    {

public:

    /**
     * Two-phased constructor.
     */
    static CAknPhysicsRestrictor* NewL( 
        CAknPhysicsParameterProvider* aProvider );

    /**
     * Two-phased constructor.
     */
    static CAknPhysicsRestrictor* NewLC( 
        CAknPhysicsParameterProvider* aProvider );

    /**
     * Destructor.
     */
    virtual ~CAknPhysicsRestrictor();
    
    /**
     * Updates physics environment.
     *
     * @param aWorldSize World size.
     * @param aViewSize View size.
     * @param aLandscape ETrue if physics is in landscape mode.
     */
    void UpdatePhysicsEnvironment( const TSize& aWorldSize,
                                   const TSize& aViewSize,
                                   const TBool& aLandscape );

    /**
     * Returns view top position.
     *
     * @return Top position.
     */
    TInt ViewTopPosition() const;

    /**
     * Returns view bottom position.
     *
     * @return Bottom position.
     */
    TInt ViewBottomPosition() const;

    /**
     * Returns ETrue if view position is such that there is 
     * additional empty space visible.
     *
     * @param aPosition View position to be tested. If there is empty space,
     * to this variable is stored the view position with empty space hidden.
     * @return ETrue if additional empty space is visible with
     * this view position.
     */
    TBool PositionRevealsEmptySpace( TPoint& aPosition );

    /**
     * Returns ETrue if
     * 1) View position is allowed and it should be
     * notified to physics observer or 
     * 2) If position has reached the view limit and the limit position 
     * should be notified to observer. If this is the case, 
     * the new modified (limit) position is saved to aPosition.
     *
     * @param aPosition View position.
     * @return ETrue if position is allowed and it should be notified to 
     * physics observer.
     */
    TBool AllowedViewPosition( TPoint& aPosition );

    /**
     * Adjusts drag point if view position has reached the limit position.
     *
     * @param aDragPoint Drag point.
     */
    void AdjustDragPoint( TPoint& aDragPoint );

    /**
     * Returns world size.
     *
     * @return World size.
     */
    TSize WorldSize() const;

    /**
     * Returns ETrue if physics is in landscape.
     *
     * @return Landscape value.
     */
    TBool WorldInLandscape() const;

    /**
     * Returns physics parameter provider.
     *
     * @return Physics parameter provider.
     */
    CAknPhysicsParameterProvider* ParameterProvider() const;

    /**
     * Modifies aPosition to view top position.
     */
    void PositionToViewTop( TPoint& aPosition ) const;

    /**
     * Modifies aPosition to view bottom position.
     */
    void PositionToViewBottom( TPoint& aPosition ) const;

    /**
     * Returns ETrue if view position is out of world boundaries 
     * when colliding.
     *
     * @param aPosition View position.
     * @param aTopCollision ETrue if collision type is top collision, 
     * EFalse if bottom.
     * @return ETrue if position is out of boundaries.
     */
    TBool PositionIsOutOfBoundaries( const TPoint& aPosition,
                                     const TBool& aTopCollision ) const;

private:

    /**
     * C++ constructor.
     */
    CAknPhysicsRestrictor( CAknPhysicsParameterProvider* aProvider );

    /**
     * Symbian second-phase constructor.
     */
    void ConstructL();

    /**
     * Calculates view limit values.
     */
    void CalculateViewLimits();

    /**
     * Returns ETrue if world fits to view.
     *
     * @return ETrue if world fits to view.
     */
    TBool WorldFitsToView();

private: // data

    /**
     * World size.
     */
    TSize iWorldSize;
    
    /**
     * View size.
     */
    TSize iViewSize;
    
    /**
     * ETrue if physics is in landscape.
     */
    TBool iLandscape;

    /**
     * Physics view position top limit (empty space visible).
     */
    TInt iPositionTopLimit;
    
    /**
     * Physics view position bottom limit (empty space visible).
     */
    TInt iPositionBottomLimit;

    /**
     * Physics empty space area (height/width).
     */
    TInt iEmptySpaceArea;

    /**
     * Physics parameter provider.
     * Not own.
     */
    CAknPhysicsParameterProvider* iProvider;
    
    /**
     * ETrue if view position has reached limit.
     */
    TBool iViewReachedLimit;

    /**
     * ETrue if there are restrictions to empty space.
     */
    TBool iEmptySpaceRestricted;

    };


#endif // C_AKNPHYSICSRESTRICTOR_H
