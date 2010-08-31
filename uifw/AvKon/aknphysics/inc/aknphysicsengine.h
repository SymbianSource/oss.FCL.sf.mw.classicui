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
* Description:  AknPhysics engine
*
*/


#ifndef C_AKNPHYSICSENGINE_H
#define C_AKNPHYSICSENGINE_H


#include <e32base.h>
#include <ode/ode.h>

class CAknPhysics;

/**
 *  Physics engine
 *
 *  @lib aknphysics
 *  @since S60 v5.0
 */
NONSHARABLE_CLASS( CAknPhysicsEngine ) : public CBase
    {

public:

    /**
     * Collision definitions.
     */
    enum TAknPhysicsCollision
        {
        EAknPhysicsNoCollision,
        EAknPhysicsBottomCollision,
        EAknPhysicsTopCollision
        };

    /**
     * Two-phased constructor.
     */
    static CAknPhysicsEngine* NewL( CAknPhysics* aPhysics );

    /**
     * Two-phased constructor.
     */
    static CAknPhysicsEngine* NewLC( CAknPhysics* aPhysics );

    /**
     * Destructor.
     */
    virtual ~CAknPhysicsEngine();
    
    /**
     * Return ETrue if ODE world exists.
     *
     * @return ETrue if ODE world exists.
     */
    TBool WorldExists() const;

    /**
     * Creates ODE world.
     *
     * @param aGravity World gravity factor.
     */
    void CreateWorld( const TInt& aGravity );
    
    /**
     * Creates ODE planes.
     *
     * @param aIh
     * @param aX
     * @param aY
     * @param aR
     */
    void CreatePlanes( const TInt64& aIh,
                       const TInt64& aX,
                       const TInt64& aY,
                       const TInt64& aR );

    /**
     * Creates ODE view body.
     *
     * @param aWidth View width.
     * @param aHeight View height.
     * @param aMass View mass.
     */
    void CreateViewBody( const TInt64& aWidth,
                         const TInt64& aHeight,
                         const TInt64& aMass );

    /**
     * Set view body position.
     *
     * @param aPosition View body position.
     */
    void SetViewBodyPosition( const TPoint& aPosition );

    /**
     * Get view body position.
     *
     * @param aPosition New view body position.
     */
    void GetViewBodyPosition( TPoint& aPosition );

    /**
     * Resets view body force and velocity.
     */
    void ResetViewBodyForceAndVelocity();

    /**
     * Enables view body.
     */
    void EnableViewBody();

    /**
     * Returns ETrue if view body is enabled.
     *
     * @return ETrue if view body is enabled.
     */
    TBool IsViewBodyEnabled() const;

    /**
     * Applies force factor.
     *
     * @param aDrag Dragging distance.
     * @param aMoveTime Dragging move time.
     */
    void ApplyDragForce( const TPoint& aDrag,
                         const TInt& aMoveTime );

    /**
     * Returns collision state.
     *
     * @return Collision state.
     */
    const TAknPhysicsCollision& CollisionState();

    /**
     * Resets collision state.
     */
    void ResetCollisionState();

    /**
     * Takes physics step.
     */
    void TakePhysicsStep();

    /**
     * Deletes physics.
     */
    void DeletePhysics();

    /**
     * Sets friction.
     *
     * @param aFriction New friction value.
     */
    void SetFriction( TReal aFriction );

    /**
     * Resets friction.
     */
    void ResetFriction();
    
    /**
     * Starts FPS logging.
     */
    void StartFpsLogging();
    
    /**
     * Stops FPS logging.
     */
    void StopFpsLogging();

private:

    /**
     * C++ constructor.
     */
    CAknPhysicsEngine( CAknPhysics* aPhysics );

    /**
     * Symbian second-phase constructor.
     */
    void ConstructL();
    
    /**
     * Physics collision step callback function.
     *
     * @param aData Pointer to CAknPhysicsEngine instance.
     * @param o0
     * @param o1
     */
    static void CallbackFunc( void* aData, dGeomID o0, dGeomID o1 );

    /**
     * Physics collision handling function.
     *
     * @param o0
     * @param o1
     */
    void HandleCollisionBetween( dGeomID aObject1, dGeomID aObject2 );

private: // data

    /**
     * ODE world.
     */
    dWorldID iWorldId;

    /**
     * ODE collision space.
     */
    dSpaceID iSpace;

    /**
     * ODE collision contact group.
     */
    dJointGroupID iContactGroup;

    /**
     * ODE top plane.
     */
    dGeomID iPlaneTop;

    /**
     * ODE bottom plane.
     */
    dGeomID iPlaneBottom;

    /**
     * ODE left plane.
     */
    dGeomID iPlaneLeft;

    /**
     * ODE right plane.
     */
    dGeomID iPlaneRight;

    /**
     * ODE friction plane.
     */
    dGeomID iPlaneFriction;

    /**
     * ODE view box geom.
     */
    dGeomID iViewBox;

    /**
     * ODE view box body.
     */
    dBodyID iViewBody;

    /**
     * Collision state.
     */
    TAknPhysicsCollision iCollision;
    
    /**
     * Friction value.
     */
    TReal iFriction;

    /**
     * Pointer to CAknPhysics.
     * Not own.
     */
    CAknPhysics* iPhysics;
    
    /**
     * View position.
     */
    TPoint iViewPosition;
    
    /**
     * Using application's UID. Used for FPS logging.
     */
    TUid iLogUid;
    };

#endif // C_AKNPHYSICSENGINE_H
