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

#include <e32debug.h>
#include <aknphysics.h>
#include <eikenv.h>
#include <eikappui.h>
#include <eikapp.h>

#include "aknphysicsconstants.h"
#include "aknphysicsengine.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CAknPhysicsEngine::NewL
// ---------------------------------------------------------------------------
//
CAknPhysicsEngine* CAknPhysicsEngine::NewL( CAknPhysics* aPhysics )
    {
    CAknPhysicsEngine* self = CAknPhysicsEngine::NewLC( aPhysics );
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsEngine::NewLC
// ---------------------------------------------------------------------------
//
CAknPhysicsEngine* CAknPhysicsEngine::NewLC( CAknPhysics* aPhysics )
    {
    CAknPhysicsEngine* self = 
        new ( ELeave ) CAknPhysicsEngine( aPhysics );
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsEngine::~CAknPhysicsEngine
// ---------------------------------------------------------------------------
//
CAknPhysicsEngine::~CAknPhysicsEngine()
    {
    DeletePhysics();
    }


// ---------------------------------------------------------------------------
// CAknPhysicsEngine::WorldExists
// ---------------------------------------------------------------------------
//
TBool CAknPhysicsEngine::WorldExists() const
    {
    return iWorldId != NULL;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsEngine::CreateWorld
// ---------------------------------------------------------------------------
//
void CAknPhysicsEngine::CreateWorld( const TInt& aGravity )
    {
    dInitODE();
    iWorldId = dWorldCreate();
    dWorldSetERP( iWorldId, REAL( KErpFactor ) );
    dWorldSetCFM( iWorldId, REAL( KCfmFactor ) );
    dWorldSetGravity( iWorldId, 0, 0, -REAL( aGravity ) );
    dWorldSetAutoDisableFlag(iWorldId, 1);
    iSpace = dSimpleSpaceCreate(0);
    }


// ---------------------------------------------------------------------------
// CAknPhysicsEngine::CreatePlanes
// ---------------------------------------------------------------------------
//
void CAknPhysicsEngine::CreatePlanes( const TInt64& aIh,
                                      const TInt64& aX,
                                      const TInt64& aY,
                                      const TInt64& aR )
    {
    // Create bounding planes
    iPlaneTop = dCreatePlane( iSpace, REAL( aX ), REAL( aY ), 0, REAL( 0 ) );
    iPlaneBottom = dCreatePlane( iSpace, REAL( -aX ), REAL( -aY ), 0, REAL( -aIh ) );
    iPlaneLeft = dCreatePlane( iSpace, REAL( aY ), REAL( aX ), 0, REAL( 0 ) );
    iPlaneRight = dCreatePlane( iSpace,  REAL( -aY ), REAL( -aX ), 0, REAL( -aR ) );

    // create z-plane to apply friction
    // bottom, z axle
    iPlaneFriction = dCreatePlane( iSpace, 0, 0, REAL( 1 ), REAL( -KZDepth ) );
    }



// ---------------------------------------------------------------------------
// CAknPhysicsEngine::CreateViewBody
// ---------------------------------------------------------------------------
//
void CAknPhysicsEngine::CreateViewBody(
    const TInt64& aWidth, const TInt64& aHeight, const TInt64& aMass )
    {
    // create viewbox
    iViewBox = dCreateBox( iSpace, REAL( aWidth ), REAL( aHeight ), REAL( KZDepth ) );
    iViewBody = dBodyCreate( iWorldId );
    
    dBodySetAutoDisableFlag( iViewBody, 1 );
    dGeomSetBody( iViewBox, iViewBody );
    
    // Set mass for body
    dMass mass;
    dMassSetBoxTotal( &mass, 
        REAL( aMass ), REAL( aWidth ), REAL( aHeight ), REAL( KZDepth ) );
    dBodySetMass( iViewBody, &mass );
    
    // Create JointGroup to handle contacts
    iContactGroup = dJointGroupCreate( 0 );
    }


// ---------------------------------------------------------------------------
// CAknPhysicsEngine::SetViewBodyPosition
// ---------------------------------------------------------------------------
//
void CAknPhysicsEngine::SetViewBodyPosition( const TPoint& aPosition )
    {
    if ( iViewBody )
        {
        iViewPosition = aPosition;
        TInt64 x, y;
        x = iViewPosition.iX;
        y = iViewPosition.iY;
        dBodySetPosition( 
            iViewBody, 
            REAL( x ), 
            REAL( y ), 
            REAL( -KZDepth/2 ) );
        }
    }


// ---------------------------------------------------------------------------
// CAknPhysicsEngine::GetViewBodyPosition
// ---------------------------------------------------------------------------
//
void CAknPhysicsEngine::GetViewBodyPosition( TPoint& aPosition )
    {
    const dReal *pos = dBodyGetPosition( iViewBody );
    iViewPosition.iX = dFLOAT( pos[0] );
    iViewPosition.iY = dFLOAT( pos[1] );
    aPosition = iViewPosition;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsEngine::ResetViewBodyForceAndVelocity
// ---------------------------------------------------------------------------
//
void CAknPhysicsEngine::ResetViewBodyForceAndVelocity()
    {
    if ( iViewBody )
        {
        dBodySetForce( iViewBody, 0, 0, 0);
        dBodySetLinearVel( iViewBody, 0, 0, 0 );
        }
    }



// ---------------------------------------------------------------------------
// CAknPhysicsEngine::EnableViewBody
// ---------------------------------------------------------------------------
//
void CAknPhysicsEngine::EnableViewBody()
    {
    if ( iViewBody )
        {
        dBodyEnable( iViewBody );        
        }
    }


// ---------------------------------------------------------------------------
// CAknPhysicsEngine::IsViewBodyEnabled
// ---------------------------------------------------------------------------
//
TBool CAknPhysicsEngine::IsViewBodyEnabled() const
    {
    if ( iViewBody )
        {
        return dBodyIsEnabled( iViewBody );
        }
    return EFalse;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsEngine::ApplyDragForce
// ---------------------------------------------------------------------------
//
void CAknPhysicsEngine::ApplyDragForce( 
    const TPoint& aDrag, const TInt& aMoveTime )
    {
    if ( iViewBody )
        {
        TReal step = aMoveTime * KStepFactor;
        // calculate and apply force from drag
        dVector3 force;
        dWorldImpulseToForce( 
            iWorldId, 
            REAL( step ),
            REAL( TInt64( aDrag.iX / 3 ) ), 
            REAL( TInt64( aDrag.iY / 3 ) ),
            0, 
            force );
        dBodyAddForce( iViewBody, force[0], force[1], force[2] );
        }
    }


// ---------------------------------------------------------------------------
// CAknPhysicsEngine::CollisionState
// ---------------------------------------------------------------------------
//
const CAknPhysicsEngine::TAknPhysicsCollision& CAknPhysicsEngine::CollisionState()
    {
    return iCollision;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsEngine::ResetCollisionState
// ---------------------------------------------------------------------------
//
void CAknPhysicsEngine::ResetCollisionState()
    {
    iCollision = EAknPhysicsNoCollision;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsEngine::TakePhysicsStep
// ---------------------------------------------------------------------------
//
void CAknPhysicsEngine::TakePhysicsStep()
    {
    // Call collision detection (step
    dSpaceCollide ( iSpace, this , &CAknPhysicsEngine::CallbackFunc );

    // Take a simulation step 
    dWorldQuickStep( iWorldId, REAL( 0.1 ) ); 

    // Remove all joints in the contact
    dJointGroupEmpty( iContactGroup );
    }


// ---------------------------------------------------------------------------
// CAknPhysicsEngine::DeletePhysics
// ---------------------------------------------------------------------------
//
void CAknPhysicsEngine::DeletePhysics()
    {
    if(iWorldId)
        {
        // Remove all joints in the contact
        dJointGroupEmpty( iContactGroup );
        
        dJointGroupDestroy( iContactGroup );
        iContactGroup = NULL;
        dBodyDestroy( iViewBody );
        iViewBody = NULL;
        
        dGeomDestroy( iPlaneTop );
        iPlaneTop = NULL;
        dGeomDestroy( iPlaneBottom );
        iPlaneBottom = NULL;
        dGeomDestroy( iPlaneLeft );
        iPlaneLeft = NULL;
        dGeomDestroy( iPlaneRight );
        iPlaneRight = NULL;
        dGeomDestroy( iPlaneFriction );
        iPlaneFriction = NULL;
        dGeomDestroy( iViewBox );
        iViewBox = NULL;
        
        dSpaceDestroy( iSpace );
        iSpace = NULL;
        dWorldDestroy( iWorldId );
        iWorldId = NULL;
        dCloseODE(); // final clean-up;
        }
    }


// ---------------------------------------------------------------------------
// CAknPhysicsEngine::SetFriction
// ---------------------------------------------------------------------------
//
void CAknPhysicsEngine::SetFriction( TReal aFriction )
    {
    iFriction = aFriction;
    }
 
 
// ---------------------------------------------------------------------------
// CAknPhysicsEngine::ResetFriction
// ---------------------------------------------------------------------------
//
void CAknPhysicsEngine::ResetFriction()
    {
    iFriction = KDefaultFriction;
    }


// ---------------------------------------------------------------------------
// CAknPhysicsEngine::StartFpsLogging
// ---------------------------------------------------------------------------
//
void CAknPhysicsEngine::StartFpsLogging()
    {
    //TODO: add fps logging
    }


// ---------------------------------------------------------------------------
// CAknPhysicsEngine::StopFpsLogging
// ---------------------------------------------------------------------------
//
void CAknPhysicsEngine::StopFpsLogging()
    {
    //TODO: stop fps logging
    }


// ---------------------------------------------------------------------------
// CAknPhysicsEngine::CAknPhysicsEngine
// ---------------------------------------------------------------------------
//
CAknPhysicsEngine::CAknPhysicsEngine( CAknPhysics* aPhysics )
    : iWorldId( NULL ),
    iFriction( KDefaultFriction ),
    iPhysics( aPhysics ),
    iLogUid( KNullUid )
    {
    }


// ---------------------------------------------------------------------------
// CAknPhysicsEngine::ConstructL
// ---------------------------------------------------------------------------
//
void CAknPhysicsEngine::ConstructL()
    {
    }


// -----------------------------------------------------------------------------
// CAknPhysicsEngine::CallbackFunc()
// -----------------------------------------------------------------------------
//
void CAknPhysicsEngine::CallbackFunc( void* aData, dGeomID o0, dGeomID o1 )
    {
    static_cast<CAknPhysicsEngine*>( aData )->HandleCollisionBetween( o0,o1 );
    }


// -----------------------------------------------------------------------------
// CAknPhysicsEngine::HandleCollisionBetween()
// -----------------------------------------------------------------------------
//
void CAknPhysicsEngine::HandleCollisionBetween( 
    dGeomID aObject1, dGeomID aObject2 )
    {
    
    TSize viewSize( iPhysics->ViewSize() );
    TSize worldSize( iPhysics->WorldSize() );
    TInt surfaceErp( iPhysics->SurfaceErp() );
    TInt surfaceCfm( iPhysics->SurfaceCfm() );
    
    
    dBodyID b1 = dGeomGetBody(aObject1);
    dBodyID b2 = dGeomGetBody(aObject2);
    dContact contacts[KMaxContacts];
    TInt numc = dCollide(aObject1,
                            aObject2,
                            KMaxContacts,
                            &contacts[0].geom,
                            sizeof(dContact));
    
    for (TInt i = 0 ; i < numc; i++) 
        {
        contacts[i].surface.mode = dContactApprox1;

        if(aObject1 == iPlaneFriction || aObject2 == iPlaneFriction)
            {
            if( iCollision == EAknPhysicsNoCollision )
                {
                contacts[i].surface.mu = REAL( iFriction );                
                }
            else
                {
                contacts[i].surface.mu = 0;                                
                }
            }
        else if(aObject1 == iPlaneTop 
                || aObject2 == iPlaneTop)
            {
            contacts[i].surface.mu = 0; // No friction
            TInt offScreen = 0;
            if( iPhysics->Landscape() )
                {
                offScreen = -(iViewPosition.iX - viewSize.iWidth/2);
                offScreen = 
                    offScreen > viewSize.iWidth ? viewSize.iWidth : offScreen;
                }
            else
                {
                offScreen = -(iViewPosition.iY - viewSize.iHeight/2);
                offScreen = 
                    offScreen > viewSize.iHeight ? viewSize.iHeight : offScreen;
                }
            if( offScreen )
                {
                contacts[i].surface.mode |= dContactSoftCFM | dContactSoftERP; 
                contacts[i].surface.soft_erp = 
                    REAL( TReal( surfaceErp )/offScreen ); 
                contacts[i].surface.soft_cfm = 
                    REAL( TReal( surfaceCfm )/offScreen);
                iCollision = EAknPhysicsTopCollision;
                }
            else
                iCollision = EAknPhysicsNoCollision;
            
            RDebug::Print(_L("TOP COLLISION"));
            }
        else if(aObject1 == iPlaneBottom 
            || aObject2 == iPlaneBottom )
            {
            contacts[i].surface.mu = 0; // No friction
            TInt offScreen = 0;
            if(iPhysics->Landscape())
                {
                offScreen = 
                    (iViewPosition.iX + viewSize.iWidth/2) - viewSize.iWidth;
                offScreen = 
                    offScreen > viewSize.iWidth ? viewSize.iWidth : offScreen;
                }
            else
                {
                offScreen = 
                    (iViewPosition.iY + viewSize.iHeight/2) - worldSize.iHeight;
                offScreen = 
                    offScreen > viewSize.iHeight ? viewSize.iHeight : offScreen;
                }
            
            if( offScreen )
                {
                contacts[i].surface.mode |= dContactSoftCFM | dContactSoftERP; 
                contacts[i].surface.soft_erp = 
                    REAL( TReal( surfaceErp )/offScreen ); 
                contacts[i].surface.soft_cfm = 
                    REAL( TReal( surfaceCfm )/offScreen);
                iCollision = EAknPhysicsBottomCollision;
                }
            else
                iCollision = EAknPhysicsNoCollision;

            RDebug::Print(_L("BOTTOM COLLISION"));
            }
        else
            {
            iCollision = EAknPhysicsNoCollision;
            contacts[i].surface.mu = 0; // No friction
            contacts[i].surface.mode |= 
                dContactBounce | dContactSoftCFM | dContactSoftERP; 
            contacts[i].surface.soft_cfm = REAL(KCfmSoftFactor);
            contacts[i].surface.soft_erp = REAL(KErpFactor);
            contacts[i].surface.bounce = REAL(KBounceFactor); // small bounce
            }

        dJointID c = dJointCreateContact(iWorldId, iContactGroup, &contacts[i]);
        dJointAttach(c,b1,b2);
        }
    }
