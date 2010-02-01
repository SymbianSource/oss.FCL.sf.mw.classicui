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
* Description:  Implement node test case class
*
*/


#include <avkon.rsg>
#include <bctestdomm3g.rsg>
#include <eikenv.h>
#include <eikappui.h>
#include <cm3gloader.h>
#include <rm3gobject.h>
#include <rm3glight.h>
#include <rm3gcamera.h>
#include <rm3gworld.h>
#include <rm3gbackground.h>
#include <rm3gsprite.h>
#include <rm3gappearance.h>
#include <rm3gimage.h>
#include <rm3gnode.h>
#include <rm3gtransformable.h>
#include <rm3gmesh.h>
#include <rm3gindexbuffer.h>
#include <rm3gvertexbuffer.h>
#include <rm3gmorphingmesh.h>
#include <rm3gskinnedmesh.h>

#include "bctestdomm3gnodecase.h"
#include "bctestdomm3gcontainer.h"
#include "bctestdomm3g.hrh"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomM3gNodeCase* CBCTestDomM3gNodeCase::NewL(
    CBCTestDomM3gContainer* aContainer )
    {
    CBCTestDomM3gNodeCase* self =
        new( ELeave ) CBCTestDomM3gNodeCase( aContainer );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestDomM3gNodeCase::CBCTestDomM3gNodeCase(
    CBCTestDomM3gContainer* aContainer )
    : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDomM3gNodeCase::~CBCTestDomM3gNodeCase()
    {
    //M3GEnv::Release(); //Release env object. Only release one time,or panic.
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomM3gNodeCase::ConstructL()
    {
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCTestDomM3gNodeCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestDomM3gNodeCase::BuildScriptL()
    {
    const TInt scripts[] =
        {
        //outline13
        LeftCBA,
        Down,
        REP( LeftCBA, 2 ),

        //outline14
        LeftCBA,
        Down,
        LeftCBA,
        REP( Down, 1 ),
        LeftCBA,

        //outline15
        LeftCBA,
        Down,
        LeftCBA,
        REP( Down, 2 ),
        LeftCBA,

        //outline16
        LeftCBA,
        Down,
        LeftCBA,
        REP( Down, 3 ),
        LeftCBA,

        //outline17
        LeftCBA,
        Down,
        LeftCBA,
        REP( Down, 4 ),
        LeftCBA,

        //outline18
        LeftCBA,
        Down,
        LeftCBA,
        REP( Down, 5 ),
        LeftCBA,

        //outline19
        LeftCBA,
        Down,
        LeftCBA,
        REP( Down, 6 ),
        LeftCBA,

        //outline20
        LeftCBA,
        Down,
        LeftCBA,
        REP( Down, 7 ),
        LeftCBA,

        };
    AddTestScriptL( scripts, sizeof( scripts ) / sizeof( TInt ) );
    }

// ---------------------------------------------------------------------------
// CBCTestDomM3gNodeCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestDomM3gNodeCase::RunL( TInt aCmd )
    {
    if ( ( aCmd < EBCTestCmdOutline13 ) || ( aCmd > EBCTestCmdOutline20 ) )
        {
        return;
        }
    switch ( aCmd )
        {
        case EBCTestCmdOutline13:
            TestRM3GTransformableL();
            break;
        case EBCTestCmdOutline14:
            TestRM3GNodeL();
            break;
        case EBCTestCmdOutline15:
            TestRM3GCameraL();
            break;
        case EBCTestCmdOutline16:
            TestRM3GGroupL();
            break;
        case EBCTestCmdOutline17:
            TestRM3GLightL();
            break;
        case EBCTestCmdOutline18:
            TestRM3MeshL();
            TestRM3GMorphingMeshL();
            TestRM3GSkinnedMeshL();
            break;
        case EBCTestCmdOutline19:
            TestRM3GSpriteL();
            break;
        case EBCTestCmdOutline20:
            TestRM3GWorldL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestDomM3gNodeCase::TestRM3GTransformableL
// ---------------------------------------------------------------------------
//
void CBCTestDomM3gNodeCase::TestRM3GTransformableL()
    {
    //Note:RM3GLight is a sub class of RM3GNode,
    //RM3GNode is a sub class of RM3GTransformable.
    RM3GLight m3gLight;
    CleanupClosePushL( m3gLight );
    m3gLight.OpenL();

    TM3GMatrix transform;
    m3gLight.GetCompositeTransform( transform );
    _LIT( KRM3GTransformable, "RM3GTransformable::RM3GTransformable()" );
    AssertTrueL( ETrue, KRM3GTransformable );

    TM3GVector4 angleAxis;
    m3gLight.GetOrientation( angleAxis );
    _LIT( KRM3GTformableGetOrientation,
        "RM3GTransformable::GetOrientation()" );
    AssertTrueL( ETrue, KRM3GTformableGetOrientation );

    TM3GVector3 translation;
    m3gLight.GetScale( translation );
    _LIT( KRM3GTformableGetScale, "RM3GTransformable::GetScale()" );
    AssertTrueL( ETrue, KRM3GTformableGetScale );

    m3gLight.GetTransform( transform );
    _LIT( KRM3GTformableGetTransform,
        "RM3GTransformable::GetTransform()" );
    AssertTrueL( ETrue, KRM3GTformableGetTransform );

    m3gLight.GetTranslation( translation );
    _LIT( KRM3GTformableGetTranslation,
        "RM3GTransformable::GetTranslation()" );
    AssertTrueL( ETrue, KRM3GTformableGetTranslation );

    TReal32 angle = 1.0;
    TReal32 x = 1.0;
    TReal32 y = 1.0;
    TReal32 z = 1.0;
    m3gLight.PostRotate( angle, x, y, z );
    _LIT( KRM3GTformablePostRotate, "RM3GTransformable::PostRotate()" );
    AssertTrueL( ETrue, KRM3GTformablePostRotate );

    m3gLight.PreRotate( angle, x, y, z );
    _LIT( KRM3GTformablePreRotate, "RM3GTransformable::PreRotate()" );
    AssertTrueL( ETrue, KRM3GTformablePreRotate );

    m3gLight.Scale( x, y, z );
    _LIT( KRM3GTformableScale, "RM3GTransformable::Scale()" );
    AssertTrueL( ETrue, KRM3GTformableScale );

    m3gLight.SetOrientation( angle, x, y, z );
    _LIT( KRM3GTformableSetOrientation,
        "RM3GTransformable::SetOrientation()" );
    AssertTrueL( ETrue, KRM3GTformableSetOrientation );

    m3gLight.SetScale( x, y, z );
    _LIT( KRM3GTformableSetScale, "RM3GTransformable::SetScale()" );
    AssertTrueL( ETrue, KRM3GTformableSetScale );

    m3gLight.SetTransform( transform );
    _LIT( KRM3GTformableSetTransform, "RM3GTransformable::SetTransform()" );
    AssertTrueL( ETrue, KRM3GTformableSetTransform );

    m3gLight.SetTranslation( x, y, z );
    _LIT( KRM3GTformableSetTranslation,
        "RM3GTransformable::SetTranslation()" );
    AssertTrueL( ETrue, KRM3GTformableSetTranslation );

    m3gLight.Translate( x, y, z );
    _LIT( KRM3GTformableTranslate, "RM3GTransformable::Translate()" );
    AssertTrueL( ETrue, KRM3GTformableTranslate );

    CleanupStack::PopAndDestroy();// m3gLight
    }

// ---------------------------------------------------------------------------
// CBCTestDomM3gNodeCase::TestRM3GNodeL
// ---------------------------------------------------------------------------
//
void CBCTestDomM3gNodeCase::TestRM3GNodeL()
    {
    //Note:RM3GLight is a sub class of RM3GNode,
    RM3GLight m3gLight;
    CleanupClosePushL( m3gLight );
    m3gLight.OpenL();

    m3gLight.Align( m3gLight );
    _LIT( KRM3GNodeAlign, "RM3GNode::Align()" );
    AssertTrueL( ETrue, KRM3GNodeAlign );

    TReal factor = m3gLight.AlphaFactor();
    _LIT( KRM3GNodeAlphaFactor, "RM3GNode::AlphaFactor()" );
    AssertTrueL( ETrue, KRM3GNodeAlphaFactor );

    RM3GNode m3gNode = m3gLight.Parent();
    _LIT( KRM3GNodeParent, "RM3GNode::Parent()" );
    AssertTrueL( ETrue, KRM3GNodeParent );
    CleanupClosePushL( m3gNode );

    TInt scope = m3gLight.Scope();
    _LIT( KRM3GNodeScope, "RM3GNode::Scope()" );
    AssertTrueL( ETrue, KRM3GNodeScope );

    TM3GMatrix transform;
    RM3GLight m3gLightPara;
    CleanupClosePushL( m3gLightPara );
    m3gLightPara.OpenL();
    TBool transformFlag = m3gLight.GetTransformTo( m3gLightPara, transform );
    _LIT( KRM3GNodeGetTransformTo, "RM3GNode::GetTransformTo()" );
    AssertTrueL( ETrue, KRM3GNodeGetTransformTo );

    TBool pickingFlag = m3gLight.IsPickingEnabled();
    _LIT( KRM3GNodeIsPickingEnabled, "RM3GNode::IsPickingEnabled()" );
    AssertTrueL( ETrue, KRM3GNodeIsPickingEnabled );

    TBool renderingFlag = m3gLight.IsRenderingEnabled();
    _LIT( KRM3GNodeIsRenderingEnabled, "RM3GNode::IsRenderingEnabled()" );
    AssertTrueL( ETrue, KRM3GNodeIsRenderingEnabled );

    RM3GLight m3gLightZRef;
    CleanupClosePushL( m3gLightZRef );
    m3gLightZRef.OpenL();
    RM3GLight m3gLightYRef;
    CleanupClosePushL( m3gLightYRef );
    m3gLightYRef.OpenL();
    m3gLight.SetAlignment( m3gLightZRef,
                           RM3GNode::EZAxis,
                           m3gLightYRef,
                           RM3GNode::EYAxis );
    _LIT( KRM3GNodeSetAlignment, "RM3GNode::SetAlignment()" );
    AssertTrueL( ETrue, KRM3GNodeSetAlignment );

    m3gLight.SetAlphaFactor( factor );
    _LIT( KRM3GNodeSetAlphaFactor, "RM3GNode::SetAlphaFactor()" );
    AssertTrueL( ETrue, KRM3GNodeSetAlphaFactor );

    m3gLight.SetPickingEnable( pickingFlag );
    _LIT( KRM3GNodeSetPickingEnable, "RM3GNode::SetPickingEnable()" );
    AssertTrueL( ETrue, KRM3GNodeSetPickingEnable );

    m3gLight.SetRenderingEnable( renderingFlag );
    _LIT( KRM3GNodeSetRenderingEnable, "RM3GNode::SetRenderingEnable()" );
    AssertTrueL( ETrue, KRM3GNodeSetRenderingEnable );

    m3gLight.SetScope( scope );
    _LIT( KRM3GNodeSetScope, "RM3GNode::SetScope()" );
    AssertTrueL( ETrue, KRM3GNodeSetScope );

    // m3gLight, m3gNode, m3gLightPara, m3gLightZRef, m3gLightYRef
    CleanupStack::PopAndDestroy( 5 );
    }

// ---------------------------------------------------------------------------
// CBCTestDomM3gNodeCase::TestRM3GLightL
// ---------------------------------------------------------------------------
//
void CBCTestDomM3gNodeCase::TestRM3GLightL()
    {
    RM3GLight m3gLight;
    RM3GLight m3gCastLight;
    CleanupClosePushL( m3gLight );
    CleanupClosePushL( m3gCastLight );
    _LIT( KRM3GLight, "RM3GLight::RM3GLight()" );
    AssertTrueL( ETrue, KRM3GLight );

    m3gLight.OpenL();
    m3gCastLight.OpenL();
    _LIT( KRM3GLightOpenL, "RM3GLight::OpenL()" );
    AssertTrueL( ETrue, KRM3GLightOpenL );

    TInt lightColor = m3gLight.Color();
    _LIT( KRM3GLightColor, "RM3GLight::Color()" );
    AssertTrueL( ETrue, KRM3GLightColor );

    TReal cAttenuation = m3gLight.ConstantAttenuation();
    _LIT( KRM3GLightConstantAttenuation,
        "RM3GLight::ConstantAttenuation()" );
    AssertTrueL( ETrue, KRM3GLightConstantAttenuation );

    TReal intensity = m3gLight.Intensity();
    _LIT( KRM3GLightIntensity, "RM3GLight::Intensity()" );
    AssertTrueL( ETrue, KRM3GLightIntensity );

    TReal lAttenuation = m3gLight.LinearAttenuation();
    _LIT( KRM3GLightLinearAttenuation,
        "RM3GLight::LinearAttenuation()" );
    AssertTrueL( ETrue, KRM3GLightLinearAttenuation );

    RM3GLight::TLightSource lightMode = m3gLight.Mode();
    _LIT( KRM3GLightMode, "RM3GLight::Mode()" );
    AssertTrueL( ETrue, KRM3GLightMode );

    TReal qAttenuation = m3gLight.QuadraticAttenuation();
    _LIT( KRM3GLightQuadraticAttenuation,
        "RM3GLight::QuadraticAttenuation()" );
    AssertTrueL( ETrue, KRM3GLightQuadraticAttenuation );

    TReal angle = m3gLight.SpotAngle();
    _LIT( KRM3GLightSpotAngle, "RM3GLight::SpotAngle()" );
    AssertTrueL( ETrue, KRM3GLightSpotAngle );

    TReal exponent = m3gLight.SpotExponent();
    _LIT( KRM3GLightSpotExponent, "RM3GLight::SpotExponent()" );
    AssertTrueL( ETrue, KRM3GLightSpotExponent );

    m3gLight.SetAttenuation( cAttenuation, lAttenuation, qAttenuation );
    _LIT( KRM3GLightSetAttenuation, "RM3GLight::SetAttenuation()" );
    AssertTrueL( ETrue, KRM3GLightSetAttenuation );

    m3gLight.SetColor( lightColor );
    _LIT( KRM3GLightSetColor, "RM3GLight::SetColor()" );
    AssertTrueL( ETrue, KRM3GLightSetColor );

    m3gLight.SetIntensity( intensity );
    _LIT( KRM3GLightSetIntensity, "RM3GLight::SetIntensity()" );
    AssertTrueL( ETrue, KRM3GLightSetIntensity );

    m3gLight.SetMode( lightMode );
    _LIT( KRM3GLightSetMode, "RM3GLight::SetMode()" );
    AssertTrueL( ETrue, KRM3GLightSetMode );

    m3gLight.SetSpotAngle( angle );
    _LIT( KRM3GLightSetSpotAngle, "RM3GLight::SetSpotAngle()" );
    AssertTrueL( ETrue, KRM3GLightSetSpotAngle );

    m3gLight.SetSpotExponent( exponent );
    _LIT( KRM3GLightSetSpotExponent, "RM3GLight::SetSpotExponent()" );
    AssertTrueL( ETrue, KRM3GLightSetSpotExponent );

    m3gLight.Cast( m3gCastLight );
    _LIT( KRM3GLightCast, "RM3GLight::Cast()" );
    AssertTrueL( ETrue, KRM3GLightCast );

    CleanupStack::PopAndDestroy( 2 );// m3gLight, m3gCastLight

    }

// ---------------------------------------------------------------------------
// CBCTestDomM3gNodeCase::TestRM3GCameraL
// ---------------------------------------------------------------------------
//
void CBCTestDomM3gNodeCase::TestRM3GCameraL()
    {
    RM3GCamera m3gCamera;
    CleanupClosePushL( m3gCamera );
    _LIT( KRM3GCamera, "RM3GCamera::RM3GCamera()" );
    AssertTrueL( ETrue, KRM3GCamera );

    m3gCamera.OpenL();
    _LIT( KRM3GCameraOpenL, "RM3GCamera::OpenL()" );
    AssertTrueL( ETrue, KRM3GCameraOpenL );

    TM3GProjectionParams projectionParams;
    m3gCamera.Projection( projectionParams );
    _LIT( KRM3GCameraProjection, "RM3GCamera::Projection()" );
    AssertTrueL( ETrue, KRM3GCameraProjection );

    TM3GMatrix m3gMatrix;
    m3gCamera.Projection( m3gMatrix );
    _LIT( KRM3GCameraProjectionM, "RM3GCamera::Projection()" );
    AssertTrueL( ETrue, KRM3GCameraProjectionM );

    m3gCamera.SetGeneric( m3gMatrix );
    _LIT( KRM3GCameraSetGeneric, "RM3GCamera::SetGeneric()" );
    AssertTrueL( ETrue, KRM3GCameraSetGeneric );

    TReal32 fovy = 1.0;
    TReal32 aspectRatio = 1.0;
    TReal32 near = 1.0;
    TReal32 far = 2.0;
    m3gCamera.SetParallel( fovy, aspectRatio, near, far );
    _LIT( KRM3GCameraSetParallel, "RM3GCamera::SetParallel()" );
    AssertTrueL( ETrue, KRM3GCameraSetParallel );

    m3gCamera.SetPerspective( fovy, aspectRatio, near, far );
    _LIT( KRM3GCameraSetPerspective, "RM3GCamera::SetPerspective()" );
    AssertTrueL( ETrue, KRM3GCameraSetPerspective );

    m3gCamera.Cast( m3gCamera );
    _LIT( KRM3GCameraCast, "RM3GCamera::Cast()" );
    AssertTrueL( ETrue, KRM3GCameraCast );

    CleanupStack::PopAndDestroy();// m3gCamera
    }

// ---------------------------------------------------------------------------
// CBCTestDomM3gNodeCase::TestRM3GGroupL
// ---------------------------------------------------------------------------
//
void CBCTestDomM3gNodeCase::TestRM3GGroupL()
    {
    RM3GGroup m3gGroup;
    CleanupClosePushL( m3gGroup );
    _LIT( KRM3GGroup, "RM3GGroup::RM3GGroup()" );
    AssertTrueL( ETrue, KRM3GGroup );

    m3gGroup.OpenL();
    _LIT( KRM3GGroupOpenL, "RM3GGroup::OpenL()" );
    AssertTrueL( ETrue, KRM3GGroupOpenL );

    RM3GWorld m3gWorld;
    CleanupClosePushL( m3gWorld );
    m3gWorld.OpenL();
    m3gGroup.AddChild( m3gWorld );
    _LIT( KRM3GGroupAddChild, "RM3GGroup::AddChild()" );
    AssertTrueL( ETrue, KRM3GGroupAddChild );

    TInt index = 0;
    RM3GNode childNode = m3gGroup.Child( index );
    CleanupClosePushL( childNode );
    _LIT( KRM3GGroupChild, "RM3GGroup::Child()" );
    AssertTrueL( ETrue, KRM3GGroupChild );

    m3gGroup.ChildCount();
    _LIT( KRM3GGroupChildCount, "RM3GGroup::ChildCount()" );
    AssertTrueL( ETrue, KRM3GGroupChildCount );

    TInt scope = 10;
    TReal32 x = 0;
    TReal32 y = 0;
    RM3GCamera m3gCamera;
    CleanupClosePushL( m3gCamera );
    m3gCamera.OpenL();
    TM3GRayIntersection ri;
    m3gGroup.Pick( scope, x, y, m3gCamera, ri );
    _LIT( KRM3GGroupPick, "RM3GGroup::Pick()" );
    AssertTrueL( ETrue, KRM3GGroupPick );

    TM3GRay m3gRay;
    TM3GRayIntersection rayIntersection;
    m3gGroup.Pick( scope, m3gRay, rayIntersection );
    _LIT( KRM3GGroupPickCopy, "RM3GGroup::Pick()" );
    AssertTrueL( ETrue, KRM3GGroupPickCopy );

    m3gGroup.RemoveChild( childNode );
    _LIT( KRM3GGroupRemoveChild, "RM3GGroup::RemoveChild()" );
    AssertTrueL( ETrue, KRM3GGroupRemoveChild );

    m3gGroup.Cast( m3gGroup );
    _LIT( KRM3GGroupCast, "RM3GGroup::Cast()" );
    AssertTrueL( ETrue, KRM3GGroupCast );

    // m3gGroup, childNode, m3gCamera, m3gWorld
    CleanupStack::PopAndDestroy( 4 );
    }

// ---------------------------------------------------------------------------
// CBCTestDomM3gNodeCase::TestRM3GWorldL
// ---------------------------------------------------------------------------
//
void CBCTestDomM3gNodeCase::TestRM3GWorldL()
    {
    RM3GWorld m3gWorld;
    CleanupClosePushL( m3gWorld );
    _LIT( KRM3GWorld, "RM3GWorld::RM3GWorld()" );
    AssertTrueL( ETrue, KRM3GWorld );

    m3gWorld.OpenL();
    _LIT( KRM3GWorldOpenL, "RM3GWorld::OpenL()" );
    AssertTrueL( ETrue, KRM3GWorldOpenL );

    RM3GCamera camera = m3gWorld.ActiveCamera();
    _LIT( KRM3GWorldActiveCamera, "RM3GWorld::ActiveCamera()" );
    AssertTrueL( ETrue, KRM3GWorldActiveCamera );
    CleanupClosePushL( camera );

    RM3GBackground backGround = m3gWorld.Background();
    _LIT( KRM3GWorldBackground, "RM3GWorld::Background()" );
    AssertTrueL( ETrue, KRM3GWorldBackground );
    CleanupClosePushL( backGround );

    m3gWorld.SetActiveCamera( camera );
    _LIT( KRM3GWorldSetActiveCamera, "RM3GWorld::SetActiveCamera()" );
    AssertTrueL( ETrue, KRM3GWorldSetActiveCamera );

    m3gWorld.SetBackground( backGround );
    _LIT( KRM3GWorldSetBackground, "RM3GWorld::SetBackground()" );
    AssertTrueL( ETrue, KRM3GWorldSetBackground );

    m3gWorld.Cast( m3gWorld );
    _LIT( KRM3GWorldCast, "RM3GWorld::Cast()" );
    AssertTrueL( ETrue, KRM3GWorldCast );

    CleanupStack::PopAndDestroy( 3 );// m3gWorld, backGround, camera
    }

// ---------------------------------------------------------------------------
// CBCTestDomM3gNodeCase::TestRM3GSpriteL
// ---------------------------------------------------------------------------
//
void CBCTestDomM3gNodeCase::TestRM3GSpriteL()
    {
    RM3GSprite m3gSprite;
    CleanupClosePushL( m3gSprite );
    _LIT( KRM3GSprite, "RM3GSprite::RM3GSprite()" );
    AssertTrueL( ETrue, KRM3GSprite );

    RM3GAppearance m3gAppearance;
    CleanupClosePushL( m3gAppearance );
    m3gAppearance.OpenL();

    RM3GImage m3gImage;
    CleanupClosePushL( m3gImage );
    TInt imageWidth = 20;
    TInt imageHeight = 20;
    TInt flag = 1;
    m3gImage.OpenL( RM3GImage::ELuminance,
                    imageWidth,
                    imageHeight,
                    flag );
    TBool scaled = ETrue;
    m3gSprite.OpenL( m3gAppearance, m3gImage, scaled );
    _LIT( KRM3GSpriteOpenL, "RM3GSprite::OpenL()" );
    AssertTrueL( ETrue, KRM3GSpriteOpenL );

    RM3GAppearance m3gAppearanceReturn = m3gSprite.Appearance();
    CleanupClosePushL( m3gAppearanceReturn );
    _LIT( KRM3GSpriteAppearance, "RM3GSprite::Appearance()" );
    AssertTrueL( ETrue, KRM3GSpriteAppearance );

    TInt cHeight = m3gSprite.CropHeight();
    _LIT( KRM3GSpriteCropHeight, "RM3GSprite::CropHeight()" );
    AssertTrueL( ETrue, KRM3GSpriteCropHeight );

    TInt cWidth = m3gSprite.CropWidth();
    _LIT( KRM3GSpriteCropWidth, "RM3GSprite::CropWidth()" );
    AssertTrueL( ETrue, KRM3GSpriteCropWidth );

    TInt cX = m3gSprite.CropX();
    _LIT( KRM3GSpriteCropX, "RM3GSprite::CropX()" );
    AssertTrueL( ETrue, KRM3GSpriteCropX );

    TInt cY = m3gSprite.CropY();
    _LIT( KRM3GSpriteCropY, "RM3GSprite::CropY()" );
    AssertTrueL( ETrue, KRM3GSpriteCropY );

    RM3GImage m3gImageReturn = m3gSprite.Image();
    CleanupClosePushL( m3gImageReturn );
    _LIT( KRM3GSpriteImage, "RM3GSprite::Image()" );
    AssertTrueL( ETrue, KRM3GSpriteImage );

    scaled = m3gSprite.IsScaled();
    _LIT( KRM3GSpriteIsScaled, "RM3GSprite::IsScaled()" );
    AssertTrueL( ETrue, KRM3GSpriteIsScaled );

    m3gSprite.SetAppearance( m3gAppearanceReturn );
    _LIT( KRM3GSpriteSetAppearance, "RM3GSprite::SetAppearance()" );
    AssertTrueL( ETrue, KRM3GSpriteSetAppearance );

    m3gSprite.SetCrop(cHeight, cWidth, cX, cY );
    _LIT( KRM3GSpriteSetCrop, "RM3GSprite::SetCrop()" );
    AssertTrueL( ETrue, KRM3GSpriteSetCrop );

    m3gSprite.SetImage( m3gImageReturn );
    _LIT( KRM3GSpriteSetImage, "RM3GSprite::SetImage()" );
    AssertTrueL( ETrue, KRM3GSpriteSetImage );

    m3gSprite.Cast( m3gSprite );
    _LIT( KRM3GSpriteCast, "RM3GSprite::Cast()" );
    AssertTrueL( ETrue, KRM3GSpriteCast );

    // m3gSprite, m3gAppearance, m3gImage, m3gAppearanceReturn, m3gImageReturn
    CleanupStack::PopAndDestroy( 5 );
    }

// ---------------------------------------------------------------------------
// CBCTestDomM3gNodeCase::TestRM3MeshL
// ---------------------------------------------------------------------------
//
void CBCTestDomM3gNodeCase::TestRM3MeshL()
    {
    RM3GMesh m3gMesh;
    CleanupClosePushL( m3gMesh );
    _LIT( KRM3Mesh, "RM3Mesh::RM3Mesh()" );
    AssertTrueL( ETrue, KRM3Mesh );

    RM3GIndexBuffer m3gIndexBuffer;
    CleanupClosePushL( m3gIndexBuffer );

    TInt stripLengths[] = { 4, 5, 6, 7 };
    TInt stripLengthCount = 4;
    TInt firstIndex = 0;
    m3gIndexBuffer.OpenL( firstIndex, stripLengths, stripLengthCount );
    _LIT( KRM3GIndexBufferOpenL, "RM3GIndexBuffer::OpenL()" );
    AssertTrueL( ETrue, KRM3GIndexBufferOpenL );

    RM3GVertexBuffer m3gVertexBuffer;
    RM3GAppearance m3gAppearance;
    CleanupClosePushL( m3gVertexBuffer );
    CleanupClosePushL( m3gAppearance );

    m3gVertexBuffer.OpenL();
    m3gAppearance.OpenL();

    m3gMesh.OpenL( m3gVertexBuffer, m3gIndexBuffer, m3gAppearance );
    _LIT( KRM3MeshOpenL, "RM3Mesh::OpenL()" );
    AssertTrueL( ETrue, KRM3MeshOpenL );

    RArray<RM3GIndexBuffer> indexBuffers;
    RArray<RM3GAppearance> appearances;
    CleanupClosePushL( indexBuffers );
    CleanupClosePushL( appearances );
    RM3GMesh m3gMeshCopy;
    CleanupClosePushL( m3gMeshCopy );
    m3gMeshCopy.OpenL( m3gVertexBuffer, indexBuffers, appearances );
    _LIT( KRM3MeshOpenLOver, "RM3Mesh::OpenL()" );
    AssertTrueL( ETrue, KRM3MeshOpenLOver );

    TInt index = 0;
    RM3GAppearance appearanceReturn = m3gMesh.Appearance( index );
    _LIT( KRM3MeshAppearance, "RM3Mesh::Appearance()" );
    AssertTrueL( ETrue, KRM3MeshAppearance );
    CleanupClosePushL( appearanceReturn );

    RM3GIndexBuffer indexBufferReturn = m3gMesh.IndexBuffer( index );
    CleanupClosePushL( indexBufferReturn );
    _LIT( KRM3MeshIndexBuffer, "RM3Mesh::IndexBuffer()" );
    AssertTrueL( ETrue, KRM3MeshIndexBuffer );

    TInt submeshCount = m3gMesh.SubmeshCount();
    _LIT( KRM3MeshSubmeshCount, "RM3Mesh::SubmeshCount()" );
    AssertTrueL( ETrue, KRM3MeshSubmeshCount );

    RM3GVertexBuffer vertexBufferRetrun = m3gMesh.VertexBuffer();
    CleanupClosePushL( vertexBufferRetrun );
    _LIT( KRM3MeshVertexBuffer, "RM3Mesh::VertexBuffer()" );
    AssertTrueL( ETrue, KRM3MeshVertexBuffer );

    m3gMesh.SetAppearance( index, appearanceReturn );
    _LIT( KRM3MeshSetAppearance, "RM3Mesh::SetAppearance()" );
    AssertTrueL( ETrue, KRM3MeshSetAppearance );

    m3gMesh.Cast( m3gMesh );
    _LIT( KRM3MeshCast, "RM3Mesh::Cast()" );
    AssertTrueL( ETrue, KRM3MeshCast );

    //m3gMesh, m3gIndexBuffer, m3gVertexBuffer,
    //m3gAppearance, indexBuffers, appearances, m3gMeshCopy,
    //appearanceReturn, indexBufferReturn, vertexBufferRetrun
    CleanupStack::PopAndDestroy( 10 );
    }

// ---------------------------------------------------------------------------
// CBCTestDomM3gNodeCase::TestRM3GMorphingMeshL
// ---------------------------------------------------------------------------
//
void CBCTestDomM3gNodeCase::TestRM3GMorphingMeshL()
    {
    #ifdef __WINSCW__
    RM3GMorphingMesh m3gMorphingMesh;
    CleanupClosePushL( m3gMorphingMesh );
    _LIT( KRM3GMMesh, "RM3GMorphingMesh::RM3GMorphingMesh()" );
    AssertTrueL( ETrue, KRM3GMMesh );

    RM3GIndexBuffer m3gIndexBuffer;
    CleanupClosePushL( m3gIndexBuffer );
    TInt stripLengths[] = { 4, 5, 6, 7 };
    TInt stripLengthCount = 4;
    TInt firstIndex = 0;
    m3gIndexBuffer.OpenL( firstIndex, stripLengths, stripLengthCount );

    RM3GVertexBuffer m3gVertexBuffer;
    RM3GAppearance m3gAppearance;
    CleanupClosePushL( m3gVertexBuffer );
    CleanupClosePushL( m3gAppearance );

    m3gVertexBuffer.OpenL();
    m3gAppearance.OpenL();

    RArray<RM3GVertexBuffer> targets;
    CleanupClosePushL( targets );
    targets.Append( m3gVertexBuffer );

    m3gMorphingMesh.OpenL( m3gVertexBuffer,
                           targets,
                           m3gIndexBuffer,
                           m3gAppearance );
    _LIT( KRM3GMMeshOpenL, "RM3GMorphingMesh::OpenL()" );
    AssertTrueL( ETrue, KRM3GMMeshOpenL );

    m3gMorphingMesh.Cast( m3gMorphingMesh );
    _LIT( KRM3GMMeshCast, "RM3GMorphingMesh::Cast()" );
    AssertTrueL( ETrue, KRM3GMMeshCast );

    RM3GMorphingMesh m3gMorphingMeshCopy;
    CleanupClosePushL( m3gMorphingMeshCopy );

    RArray<RM3GIndexBuffer> submeshes;
    RArray<RM3GAppearance> appearances;
    CleanupClosePushL( submeshes );
    CleanupClosePushL( appearances );
    submeshes.AppendL( m3gIndexBuffer );
    appearances.AppendL( m3gAppearance );


    m3gMorphingMeshCopy.OpenL( m3gVertexBuffer,
                               targets,
                               submeshes,
                               appearances );
    _LIT( KRM3GMMeshOpenLOver, "RM3GMorphingMesh::OpenL()" );
    AssertTrueL( ETrue, KRM3GMMeshOpenLOver );

    // m3gMorphingMesh, m3gIndexBuffer, m3gVertexBuffer,
    // m3gAppearance, targets, m3gMorphingMeshCopy,
    // submeshes, appearances
    CleanupStack::PopAndDestroy( 8 );
    #endif
    }

// ---------------------------------------------------------------------------
// CBCTestDomM3gNodeCase::TestRM3GSkinnedMeshL
// ---------------------------------------------------------------------------
//
void CBCTestDomM3gNodeCase::TestRM3GSkinnedMeshL()
    {
    RM3GSkinnedMesh m3gSkinnedMesh;
    CleanupClosePushL( m3gSkinnedMesh );
    _LIT( KRM3GSMesh, "RM3GSkinnedMesh::RM3GSkinnedMesh()" );
    AssertTrueL( ETrue, KRM3GSMesh );

    RM3GGroup m3gGroup;
    CleanupClosePushL( m3gGroup );
    m3gGroup.OpenL();

    RM3GIndexBuffer m3gIndexBuffer;
    CleanupClosePushL( m3gIndexBuffer );
    TInt stripLengths[] = { 4, 5, 6, 7 };
    TInt stripLengthCount = 4;
    TInt firstIndex = 0;
    m3gIndexBuffer.OpenL( firstIndex, stripLengths, stripLengthCount );

    RM3GVertexBuffer m3gVertexBuffer;
    RM3GAppearance m3gAppearance;
    CleanupClosePushL( m3gVertexBuffer );
    CleanupClosePushL( m3gAppearance );

    m3gVertexBuffer.OpenL();
    m3gAppearance.OpenL();

    m3gSkinnedMesh.OpenL( m3gVertexBuffer,
                          m3gIndexBuffer,
                          m3gAppearance,
                          m3gGroup);
    _LIT( KRM3GSMeshOpenL, "RM3GSkinnedMesh::OpenL()" );
    AssertTrueL( ETrue, KRM3GSMeshOpenL );

    RM3GSkinnedMesh m3gSkinnedMeshCopy;
    CleanupClosePushL( m3gSkinnedMeshCopy );

    RArray<RM3GIndexBuffer> submeshes;
    RArray<RM3GAppearance> appearances;
    CleanupClosePushL( submeshes );
    CleanupClosePushL( appearances );
    submeshes.AppendL( m3gIndexBuffer );
    appearances.AppendL( m3gAppearance );

    TInt err;
    TRAP( err, m3gSkinnedMeshCopy.OpenL( m3gVertexBuffer,
                              submeshes,
                              appearances,
                              m3gGroup ) );
    _LIT( KRM3GSMeshOpenLOver, "RM3GSkinnedMesh::OpenL()" );
    AssertTrueL( ETrue, KRM3GSMeshOpenLOver );

    m3gSkinnedMesh.Cast( m3gSkinnedMesh );
    _LIT( KRM3GSMeshCast, "RM3GSkinnedMesh::Cast()" );
    AssertTrueL( ETrue, KRM3GSMeshCast );

    TInt weight = 10;
    TInt firstVertex = 0;
    TInt vertexCount = 2;
    m3gSkinnedMesh.AddTransform( m3gSkinnedMesh,
                                 weight,
                                 firstVertex,
                                 vertexCount );
    _LIT( KRM3GSMeshAddTransform, "RM3GSkinnedMesh::AddTransform()" );
    AssertTrueL( ETrue, KRM3GSMeshAddTransform );

    RM3GGroup groupReturn = m3gSkinnedMesh.Skeleton();
    CleanupClosePushL( groupReturn );
    _LIT( KRM3GSMeshSkeleton, "RM3GSkinnedMesh::Skeleton()" );
    AssertTrueL( ETrue, KRM3GSMeshSkeleton );

    // m3gSkinnedMesh, m3gGroup, m3gIndexBuffer,
    // m3gVertexBuffer, m3gAppearance, m3gSkinnedMeshCopy,
    // submeshes, appearances, groupReturn
    CleanupStack::PopAndDestroy( 9 );
    }
