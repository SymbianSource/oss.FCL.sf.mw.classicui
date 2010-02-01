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
* Description:  Implement test case class
*
*/


#include <avkon.rsg>
#include <bctestdomm3g.rsg>
#include <eikenv.h>
#include <eikappui.h>
#include <cm3gloader.h>
#include <rm3gobject.h>
#include <rm3gkeyframesequence.h>
#include <rm3glight.h>
#include <rm3gimage.h>
#include <rm3gbackground.h>
#include <rm3gappearance.h>
#include <rm3gcompositingmode.h>
#include <rm3gfog.h>
#include <rm3gmaterial.h>
#include <rm3gpolygonmode.h>
#include <rm3gtexture.h>
#include <cm3grenderingcontext.h>
#include <m3genv.h>
#include <rm3gvertexbuffer.h>
#include <rm3gvertexarray.h>
#include <rm3gtrianglestriparray.h>
#include <rm3gindexbuffer.h>
#include <rm3ganimationcontroller.h>
#include <rm3ganimationtrack.h>
#include <rm3gworld.h>
#include <gdi.h>
#include <rm3gcamera.h>

#include "bctestdomm3gcase.h"
#include "bctestdomm3gcontainer.h"
#include "bctestdomm3g.hrh"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomM3gCase* CBCTestDomM3gCase::NewL(
    CBCTestDomM3gContainer* aContainer )
    {
    CBCTestDomM3gCase* self = new( ELeave ) CBCTestDomM3gCase( aContainer );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestDomM3gCase::CBCTestDomM3gCase(
    CBCTestDomM3gContainer* aContainer )
    : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDomM3gCase::~CBCTestDomM3gCase()
    {
    M3GEnv::Release(); //Release env object. Only release one time, or panic.
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomM3gCase::ConstructL()
    {
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCTestDomM3gCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestDomM3gCase::BuildScriptL()
    {
    const TInt scripts[] =
        {
        //outline1
        DELAY( 1 ),// delay between commands is 1*0.1 seconds = 0.1 seconds
        REP( LeftCBA, 3 ),

        //outline2
        REP( LeftCBA, 2 ),
        REP( Down, 1 ),
        LeftCBA,

        //outline3
        REP( LeftCBA, 2 ),
        REP( Down, 2 ),
        LeftCBA,

        //outline4
        REP( LeftCBA, 2 ),
        REP( Down, 3 ),
        LeftCBA,

        //outline5
        REP( LeftCBA, 2 ),
        REP( Down, 4 ),
        LeftCBA,

        //outline6
        REP( LeftCBA, 2 ),
        REP( Down, 5 ),
        LeftCBA,

        //outline7
        REP( LeftCBA, 2 ),
        REP( Down, 6 ),
        LeftCBA,

        //outline8
        REP( LeftCBA, 2 ),
        REP( Down, 7 ),
        LeftCBA,

        //outline9
        REP( LeftCBA, 2 ),
        REP( Down, 8 ),
        LeftCBA,

        //outline10
        REP( LeftCBA, 2 ),
        REP( Down, 9 ),
        LeftCBA,

        //outline11
        REP( LeftCBA, 2 ),
        REP( Down, 10 ),
        LeftCBA,

        //outline12
        REP( LeftCBA, 2 ),
        REP( Down, 11 ),
        LeftCBA

        };
    AddTestScriptL( scripts, sizeof( scripts ) / sizeof( TInt ) );
    }

// ---------------------------------------------------------------------------
// CBCTestDomM3gCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestDomM3gCase::RunL( TInt aCmd )
    {
    if ( ( aCmd < EBCTestCmdOutline01 ) || ( aCmd > EBCTestCmdOutline12 ) )
        {
        return;
        }
    switch ( aCmd )
        {
        case EBCTestCmdOutline01:
            TestCM3gLoaderL();
            TestCM3GRenderingContextL();
            break;
        case EBCTestCmdOutline02:
            TestRM3gObjectL();
            break;
        case EBCTestCmdOutline03:
            TestRM3GBackgroundL();
            break;
        case EBCTestCmdOutline04:
            TestRM3GAppearanceL();
            break;
        case EBCTestCmdOutline05:
            TestRM3GCompositingModeL();
            break;
        case EBCTestCmdOutline06:
            TestRM3GFogL();
            break;
        case EBCTestCmdOutline07:
            TestRM3GMaterialL();
            break;
        case EBCTestCmdOutline08:
            TestRM3GPolygonModeL();
            break;
        case EBCTestCmdOutline09:
            TestRM3GTextureL();
            TestRM3GIndexBufferL();
            break;
        case EBCTestCmdOutline10:
            TestRM3GKeyframeSequenceL();
            TestRM3GTriangleStripArrayL();
            break;
        case EBCTestCmdOutline11:
            TestRM3GVertexBufferL();
            TestRM3GVertexArrayL();
            break;
        case EBCTestCmdOutline12:
            TestRM3GAnimationControllerL();
            TestRM3GImageL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestDomM3gCase::TestCM3gLoaderL
// ---------------------------------------------------------------------------
//
void CBCTestDomM3gCase::TestCM3gLoaderL()
    {
    CM3GLoader* m3gLoader = CM3GLoader::NewLC();
    _LIT( KCM3gLoaderNewLC, "CM3GLoader::NewLC()" );
    AssertTrueL( ETrue, KCM3gLoaderNewLC );

    _LIT( KFileName, "\\BCTestLog\\bctestdomimage.bmp" );
    RM3GImage imageReturn = m3gLoader->LoadImageL( KFileName );
    CleanupClosePushL( imageReturn );
    _LIT( KCM3gLoadLoadImageL, "CM3GLoader::LoadImageL()" );
    AssertTrueL( ETrue, KCM3gLoadLoadImageL );

    RArray<RM3GObject> objects;
    CleanupClosePushL( objects );
    m3gLoader->DecodeL( KFileName, objects );
    _LIT( KCM3gLoadDecodeL, "CM3GLoader::DecodeL()" );
    AssertTrueL( ETrue, KCM3gLoadDecodeL );

    CleanupStack::PopAndDestroy( 3 );//m3gLoader, imageReturn, objects
    }

// ---------------------------------------------------------------------------
// CBCTestDomM3gCase::TestCM3GRenderingContextL
// ---------------------------------------------------------------------------
//
void CBCTestDomM3gCase::TestCM3GRenderingContextL()
    {
    CM3GRenderingContext* m3gContext = CM3GRenderingContext::NewL();
    CleanupStack::PushL( m3gContext );
    _LIT( KCM3GRenderingContext, "CM3GRenderingContext::NewL()" );
    AssertTrueL( ETrue, KCM3GRenderingContext );

    TM3GMatrix m3gNodeMatrix;
    RM3GLight m3gLight;
    CleanupClosePushL( m3gLight );
    m3gLight.OpenL();
    
    RM3GWorld m3gWorld;
    CleanupClosePushL( m3gWorld );
    m3gWorld.OpenL();

    m3gContext->RenderNode( m3gWorld, m3gNodeMatrix );
    _LIT( KCM3GRCRenderNode, "CM3GRenderingContext::RenderNode()" );
    AssertTrueL( ETrue, KCM3GRCRenderNode );

    m3gContext->RenderWorld( m3gWorld );
    _LIT( KCM3GRCRenderWorld, "CM3GRenderingContext::RenderWorld()" );
    AssertTrueL( ETrue, KCM3GRCRenderWorld );

    TInt index = 0;
    m3gContext->SetLight( index, m3gLight, m3gNodeMatrix );
    _LIT( KCM3GRCSetLight, "CM3GRenderingContext::SetLight()" );
    AssertTrueL( ETrue, KCM3GRCSetLight );

    RM3GCamera m3gCamera;
    CleanupClosePushL( m3gCamera );
    m3gCamera.OpenL();

    m3gContext->SetCamera( m3gCamera, m3gNodeMatrix );
    _LIT( KCM3GRCSetCamera, "CM3GRenderingContext::SetCamera()" );
    AssertTrueL( ETrue, KCM3GRCSetCamera );

    TInt mask = 0;
    m3gContext->SetRenderHints( mask );
    _LIT( KCM3GRCSetRenderHints, "CM3GRenderingContext::SetRenderHints()" );
    AssertTrueL( ETrue, KCM3GRCSetRenderHints );

    RM3GImage m3gImage;
    CleanupClosePushL( m3gImage );
    TInt imageWidth = 16;
    TInt imageHeight = 16;
    TInt flag = 0;
    m3gImage.OpenL( RM3GImage::EAlpha,
                    imageWidth,
                    imageHeight,
                    flag );

    m3gContext->BindImageTarget( m3gImage );
    _LIT( KCM3GRCBindImageTarget, "CM3GRenderingContext::BindImageTarget()" );
    AssertTrueL( ETrue, KCM3GRCBindImageTarget );

    CFbsBitmap* bitmap = new ( ELeave ) CFbsBitmap;
    CleanupStack::PushL( bitmap );
    User::LeaveIfError( bitmap->Create( TSize( imageWidth,
                                               imageHeight ),
                                        EColor64K ) );

    m3gContext->BindBitmapTarget( bitmap );
    _LIT( KCM3GRCBindBitmapTarget,
        "CM3GRenderingContext::BindBitmapTarget()" );
    AssertTrueL( ETrue, KCM3GRCBindBitmapTarget );

    RM3GLight m3gLightAdd;
    TM3GMatrix lightMatrix;
    lightMatrix.Unity();
    CleanupClosePushL( m3gLightAdd );
    m3gLightAdd.OpenL();
    
    lightMatrix.Unity();    
    lightMatrix.iClassified = 1;
    lightMatrix.iComplete = 1;
    
    m3gContext->AddLight( m3gLightAdd, lightMatrix );
    _LIT( KCM3GRCAddLight,
        "CM3GRenderingContext::AddLight()" );
    AssertTrueL( ETrue, KCM3GRCAddLight );    

    TUint param = 4029;
    TUint stride = 10;
    TUint userContext = 10;
    m3gContext->BindMemoryTarget( &param,
                                  imageWidth,
                                  imageHeight,
                                  CM3GRenderingContext::EL8,
                                  stride,
                                  userContext );
    _LIT( KCM3GRCBindMemoryTarget,
        "CM3GRenderingContext::BindMemoryTarget()" );
    AssertTrueL( ETrue, KCM3GRCBindMemoryTarget );

    RWindow* window = static_cast<RWindow*> ( iContainer->DrawableWindow() );
    CleanupClosePushL( *window );
    m3gContext->BindWindowTarget( *window );
    _LIT( KCM3GRCBindWindowTarget,
        "CM3GRenderingContext::BindWindowTarget()" );
    AssertTrueL( ETrue, KCM3GRCBindWindowTarget );
    CleanupStack::Pop( window );

    RM3GVertexBuffer m3gVertexBuffer;
    CleanupClosePushL( m3gVertexBuffer );
    m3gVertexBuffer.OpenL();

    RM3GIndexBuffer m3gIndexBuffer;
    CleanupClosePushL( m3gIndexBuffer );
    TInt stripLengths[] = { 4, 5, 6, 7 };
    TInt stripLengthCount = 4;
    TInt firstIndex = 0;
    m3gIndexBuffer.OpenL( firstIndex, stripLengths, stripLengthCount );

    RM3GAppearance m3gAppearance;
    CleanupClosePushL( m3gAppearance );
    m3gAppearance.OpenL();
    TM3GMatrix m3gMatrix;
    TReal32 alphaFactor = 1.0;
    TInt scope = 2;
    m3gContext->Render( m3gVertexBuffer,
                       m3gIndexBuffer,
                       m3gAppearance,
                       m3gMatrix,
                       alphaFactor,
                       scope );
    _LIT( KCM3GRCRender, "CM3GRenderingContext::Render()" );
    AssertTrueL( ETrue, KCM3GRCRender );

    //m3gVertexBuffer, m3gIndexBuffer, m3gAppearance;
    CleanupStack::PopAndDestroy( 3 );

    RM3GBackground m3gBackgroud;
    CleanupClosePushL( m3gBackgroud );
    m3gBackgroud.OpenL();
    m3gContext->Clear( m3gBackgroud );
    _LIT( KCM3GRCClear, "CM3GRenderingContext::Clear()" );
    AssertTrueL( ETrue, KCM3GRCClear );

    m3gContext->ReleaseTarget();
    _LIT( KCM3GRCReleaseTarget, "CM3GRenderingContext::ReleaseTarget()" );
    AssertTrueL( ETrue, KCM3GRCReleaseTarget );

    m3gContext->ResetLights();
    _LIT( KCM3GRCResetLights, "CM3GRenderingContext::ResetLights()" );
    AssertTrueL( ETrue, KCM3GRCResetLights );

    TReal32 near = 1.0;
    TReal32 far = 10.0;
    m3gContext->SetDepthRange( near, far );
    _LIT( KCM3GRCSetDepthRange, "CM3GRenderingContext::SetDepthRange()" );
    AssertTrueL( ETrue, KCM3GRCSetDepthRange );

    TInt x = 0;
    TInt y = 0;
    TInt width = 10;
    TInt height = 10;
    m3gContext->SetClipRect( x, y, width, height );
    _LIT( KCM3GRCSetClipRect, "CM3GRenderingContext::SetClipRect()" );
    AssertTrueL( ETrue, KCM3GRCSetClipRect );

    m3gContext->SetViewport( x, y ,width, height );
    _LIT( KCM3GRCSetViewport, "CM3GRenderingContext::SetViewport()" );
    AssertTrueL( ETrue, KCM3GRCSetViewport );

    //m3gContext, m3gBackgroud, m3gWorld;
    //m3gLight, m3gCamera, m3gImage, bitmap
    //m3gLightAdd
    CleanupStack::PopAndDestroy( 8 );

    }

// ---------------------------------------------------------------------------
// CBCTestDomM3gCase::TestRM3gObjectL
// ---------------------------------------------------------------------------
//
void CBCTestDomM3gCase::TestRM3gObjectL()
    {
    RM3GObject rM3gObject;
    CleanupClosePushL( rM3gObject );
    _LIT( KRM3GObject, "RM3GObject::RM3GObject()" );
    AssertTrueL( ETrue, KRM3GObject );

    CleanupStack::PopAndDestroy();// rM3gObject

    //RM3GLight derived from RM3GObject
    RM3GLight m3gLight;
    CleanupClosePushL( m3gLight );
    m3gLight.OpenL();

    m3gLight.Class();
    _LIT( KRM3GObjectClass, "RM3GObject::Class()" );
    AssertTrueL( ETrue, KRM3GObjectClass );

    RArray<RM3GObject> objects;
    objects.Append( m3gLight );
    CleanupClosePushL( objects );
    m3gLight.DuplicateL( objects );
    _LIT( KRM3GObjectDuplicateL, "RM3GObject::DuplicateL()" );
    AssertTrueL( ETrue, KRM3GObjectDuplicateL );

    m3gLight.GetReferencesL( objects );
    _LIT( KRM3GObjectGetReferencesL, "RM3GObject::GetReferencesL()" );
    AssertTrueL( ETrue, KRM3GObjectGetReferencesL );

    TInt currentId = m3gLight.UserId();
    _LIT( KRM3GObjectUserId, "RM3GObject::UserId()" );
    AssertTrueL( ETrue, KRM3GObjectUserId );

    m3gLight.SetUserId( currentId );
    _LIT( KRM3GObjectSetUserId, "RM3GObject::SetUserId()" );
    AssertTrueL( ETrue, KRM3GObjectSetUserId );

    RM3GObject returnObject = m3gLight.Find( currentId );
    CleanupClosePushL( returnObject );
    _LIT( KRM3GObjectFind, "RM3GObject::Find()" );
    AssertTrueL( ETrue, KRM3GObjectFind );

    RM3GAnimationTrack m3gAnimationT;
    CleanupClosePushL( m3gAnimationT );
    RM3GKeyframeSequence m3gKeyframeSequence;
    CleanupClosePushL( m3gKeyframeSequence );
    const TInt keyframeCount = 1;
    const TInt componentCount = 1;
    m3gKeyframeSequence.OpenL( keyframeCount,
                       componentCount,
                       RM3GKeyframeSequence::ELinear );
    m3gAnimationT.OpenL( m3gKeyframeSequence, RM3GAnimationTrack::EDensity );
    m3gLight.AddAnimationTrack( m3gAnimationT );
    _LIT( KRM3GObjectAddAnimationTrack,
        "RM3GObject::AddAnimationTrack()" );
    AssertTrueL( ETrue, KRM3GObjectAddAnimationTrack );

    TInt animateTime = 20;
    m3gLight.Animate( animateTime );
    _LIT( KRM3GObjectAnimate, "RM3GObject::Animate()" );
    AssertTrueL( ETrue, KRM3GObjectAnimate );

    m3gLight.AnimationTrack( 1 );
    _LIT( KRM3GObjectAnimationTrack,
        "RM3GObject::AnimationTrack()" );
    AssertTrueL( ETrue, KRM3GObjectAnimationTrack );

    m3gLight.AnimationTrackCount();
    _LIT( KRM3GObjectAnimationTrackCount,
        "RM3GObject::AnimationTrackCount()" );
    AssertTrueL( ETrue, KRM3GObjectAnimationTrackCount );

    m3gLight.RemoveAnimationTrack( m3gAnimationT );
    _LIT( KRM3GObjectRemoveAnimationTrack,
        "RM3GObject::RemoveAnimationTrack()" );
    AssertTrueL( ETrue, KRM3GObjectRemoveAnimationTrack );

    //m3gLight, objects, returnObject, m3gAnimationT, m3gKeyframeSequence
    CleanupStack::PopAndDestroy( 5 );

    }

// ---------------------------------------------------------------------------
// CBCTestDomM3gCase::TestRM3GBackgroundL
// ---------------------------------------------------------------------------
//
void CBCTestDomM3gCase::TestRM3GBackgroundL()
    {
    TBool isTure = ETrue;
    RM3GBackground m3gBackGround;
    CleanupClosePushL( m3gBackGround );
    _LIT( KRM3GBg, "RM3GBackground::RM3GBackground()" );
    AssertTrueL( ETrue, KRM3GBg );

    m3gBackGround.OpenL();
    _LIT( KRM3GBgOpenL, "RM3GBackground::OpenL()" );
    AssertTrueL( ETrue, KRM3GBgOpenL );

    TInt bColor = m3gBackGround.Color();
    _LIT( KRM3GBgColor, "RM3GBackground::Color()" );
    AssertTrueL( ETrue, KRM3GBgColor );

    TInt cropHeight = m3gBackGround.CropHeight();
    _LIT( KRM3GBgCropHeight, "RM3GBackground::CropHeight()" );
    AssertTrueL( ETrue, KRM3GBgCropHeight );

    TInt cropWidth = m3gBackGround.CropWidth();
    _LIT( KRM3GBgCropWidth, "RM3GBackground::CropWidth()" );
    AssertTrueL( ETrue, KRM3GBgCropWidth );

    TInt cropX = m3gBackGround.CropX();
    _LIT( KRM3GBgCropX, "RM3GBackground::CropX()" );
    AssertTrueL( ETrue, KRM3GBgCropX );

    TInt cropY = m3gBackGround.CropY();
    _LIT( KRM3GBgCropY, "RM3GBackground::CropY()" );
    AssertTrueL( ETrue, KRM3GBgCropY );

    RM3GImage m3gImage = m3gBackGround.Image();
    CleanupClosePushL( m3gImage );
    _LIT( KRM3GBgImage, "RM3GBackground::Image()" );
    AssertTrueL( ETrue, KRM3GBgImage );

    RM3GBackground::TImageMode imageModeX = m3gBackGround.ImageModeX();
    _LIT( KRM3GBgImageModeX, "RM3GBackground::ImageModeX()" );
    AssertTrueL( ETrue, KRM3GBgImageModeX );

    RM3GBackground::TImageMode imageModeY = m3gBackGround.ImageModeY();
    _LIT( KRM3GBgImageModeY, "RM3GBackground::ImageModeY()" );
    AssertTrueL( ETrue, KRM3GBgImageModeY );

    m3gBackGround.IsColorClearEnabled();
    _LIT( KRM3GBgIsColorClearEnabled,
        "RM3GBackground::IsColorClearEnabled()" );
    AssertTrueL( ETrue, KRM3GBgIsColorClearEnabled );

    m3gBackGround.IsDepthClearEnabled();
    _LIT( KRM3GBgIsDepthClearEnabled,
        "RM3GBackground::IsDepthClearEnabled()" );
    AssertTrueL( ETrue, KRM3GBgIsDepthClearEnabled );

    m3gBackGround.SetColor( bColor );
    _LIT( KRM3GBgSetColor, "RM3GBackground::SetColor()" );
    AssertTrueL( ETrue, KRM3GBgSetColor );

    m3gBackGround.SetColorClearEnable( isTure );
    _LIT( KRM3GBgSetColorClearEnable,
        "RM3GBackground::SetColorClearEnable()" );
    AssertTrueL( ETrue, KRM3GBgSetColorClearEnable );

    m3gBackGround.SetCrop(cropX, cropY, cropWidth, cropHeight);
    _LIT( KRM3GBgSetCrop, "RM3GBackground::SetCrop()" );
    AssertTrueL( ETrue, KRM3GBgSetCrop );

    m3gBackGround.SetDepthClearEnable( isTure );
    _LIT( KRM3GBgSetDepthClearEnable, "RM3GBackground::SetDepthClearEnable()" );
    AssertTrueL( ETrue, KRM3GBgSetDepthClearEnable );

    m3gBackGround.SetImage( m3gImage );
    _LIT( KRM3GBgSetImage, "RM3GBackground::SetImage()" );
    AssertTrueL( ETrue, KRM3GBgSetImage );

    m3gBackGround.SetImageMode( imageModeX, imageModeY );
    _LIT( KRM3GBgSetImageMode, "RM3GBackground::SetImageMode()" );
    AssertTrueL( ETrue, KRM3GBgSetImageMode );

    m3gBackGround.Cast( m3gBackGround );
    _LIT( KRM3GBgCast, "RM3GBackground::Cast()" );
    AssertTrueL( ETrue, KRM3GBgCast );

    CleanupStack::PopAndDestroy( 2 );//m3gBackGround, m3gImage
    }

// ---------------------------------------------------------------------------
// CBCTestDomM3gCase::TestRM3GAppearanceL
// ---------------------------------------------------------------------------
//
void CBCTestDomM3gCase::TestRM3GAppearanceL()
    {
    RM3GAppearance m3gAppearance;
    CleanupClosePushL( m3gAppearance );
    _LIT( KRM3GAppearance, "RM3GAppearance::RM3GAppearance()" );
    AssertTrueL( ETrue, KRM3GAppearance );

    m3gAppearance.OpenL();
    _LIT( KRM3GApOpenL, "RM3GAppearance::OpenL()" );
    AssertTrueL( ETrue, KRM3GApOpenL );

    RM3GCompositingMode m3gCompositingMode = m3gAppearance.CompositingMode();
    _LIT( KRM3GApCompositingMode, "RM3GAppearance::CompositingMode()" );
    AssertTrueL( ETrue, KRM3GApCompositingMode );

    m3gAppearance.SetCompositingMode( m3gCompositingMode );
    _LIT( KRM3GApSetCompositingMode, "RM3GAppearance::SetCompositingMode()" );
    AssertTrueL( ETrue, KRM3GApSetCompositingMode );

    RM3GFog m3gFog = m3gAppearance.Fog();
    _LIT( KRM3GApFog, "RM3GAppearance::Fog()" );
    AssertTrueL( ETrue, KRM3GApFog );

    m3gAppearance.SetFog( m3gFog );
    _LIT( KRM3GApSetFog, "RM3GAppearance::SetFog()" );
    AssertTrueL( ETrue, KRM3GApSetFog );

    TInt layer = m3gAppearance.Layer();
    _LIT( KRM3GApLayer, "RM3GAppearance::Layer()" );
    AssertTrueL( ETrue, KRM3GApLayer );

    m3gAppearance.SetLayer( layer );
    _LIT( KRM3GApSetLayer, "RM3GAppearance::SetLayer()" );
    AssertTrueL( ETrue, KRM3GApSetLayer );

    RM3GMaterial m3gMaterial = m3gAppearance.Material();
    _LIT( KRM3GApMaterial, "RM3GAppearance::Material()" );
    AssertTrueL( ETrue, KRM3GApMaterial );

    m3gAppearance.SetMaterial( m3gMaterial );
    _LIT( KRM3GApSetMaterial, "RM3GAppearance::SetMaterial()" );
    AssertTrueL( ETrue, KRM3GApSetMaterial );

    RM3GPolygonMode m3gPolygonMode = m3gAppearance.PolygonMode();
    _LIT( KRM3GApPolygonMode, "RM3GAppearance::PolygonMode()" );
    AssertTrueL( ETrue, KRM3GApPolygonMode );

    m3gAppearance.SetPolygonMode( m3gPolygonMode );
    _LIT( KRM3GApSetPolygonMode, "RM3GAppearance::SetPolygonMode()" );
    AssertTrueL( ETrue, KRM3GApSetPolygonMode );

    TInt textNum = 1;
    RM3GTexture m3gTexture = m3gAppearance.Texture( textNum );
    _LIT( KRM3GApTexture, "RM3GAppearance::Texture()" );
    AssertTrueL( ETrue, KRM3GApTexture );

    m3gAppearance.SetTexture( textNum, m3gTexture );
    _LIT( KRM3GApSetTexture, "RM3GAppearance::SetTexture()" );
    AssertTrueL( ETrue, KRM3GApSetTexture );

    m3gAppearance.Cast( m3gAppearance );
    _LIT( KRM3GApCast, "RM3GAppearance::Cast()" );
    AssertTrueL( ETrue, KRM3GApCast );

    CleanupStack::PopAndDestroy(); //m3gAppearance
    }

// ---------------------------------------------------------------------------
// CBCTestDomM3gCase::TestRM3GCompositingModeL
// ---------------------------------------------------------------------------
//
void CBCTestDomM3gCase::TestRM3GCompositingModeL()
    {
    RM3GCompositingMode m3gCompositingMode;
    CleanupClosePushL( m3gCompositingMode );
    _LIT( KRM3GCompositingMode,
        "RM3GCompositingMode::RM3GCompositingMode()" );
    AssertTrueL( ETrue, KRM3GCompositingMode );

    m3gCompositingMode.OpenL();
    _LIT( KRM3GCMOpenL, "RM3GCompositingMode::OpenL()" );
    AssertTrueL( ETrue, KRM3GCMOpenL );

    TReal thresShold = m3gCompositingMode.AlphaThreshold();
    _LIT( KRM3GCMAlphaThreshold, "RM3GCompositingMode::AlphaThreshold()" );
    AssertTrueL( ETrue, KRM3GCMAlphaThreshold );

    RM3GCompositingMode::TBlending blend = m3gCompositingMode.Blending();
    _LIT( KRM3GCMBlending, "RM3GCompositingMode::Blending()" );
    AssertTrueL( ETrue, KRM3GCMBlending );

    TReal offsetFactor = m3gCompositingMode.DepthOffsetFactor();
    _LIT( KRM3GCMDepthOffsetFactor,
        "RM3GCompositingMode::DepthOffsetFactor()" );
    AssertTrueL( ETrue, KRM3GCMDepthOffsetFactor );

    TReal offsetUnits = m3gCompositingMode.DepthOffsetUnits();
    _LIT( KRM3GCMDepthOffsetUnits,
        "RM3GCompositingMode::DepthOffsetUnits()" );
    AssertTrueL( ETrue, KRM3GCMDepthOffsetUnits );

    TBool alphaWriteEnabled = m3gCompositingMode.IsAlphaWriteEnabled();
    _LIT( KRM3GCMIsAlphaWriteEnabled,
        "RM3GCompositingMode::IsAlphaWriteEnabled()" );
    AssertTrueL( ETrue, KRM3GCMIsAlphaWriteEnabled );

    TBool colorWriteEnabled = m3gCompositingMode.IsColorWriteEnabled();
    _LIT( KRM3GCMIsColorWriteEnabled,
        "RM3GCompositingMode::IsColorWriteEnabled()" );
    AssertTrueL( ETrue, KRM3GCMIsColorWriteEnabled );

    TBool depthTestEnabled = m3gCompositingMode.IsDepthTestEnabled();
    _LIT( KRM3GCMIsDepthTestEnabled,
        "RM3GCompositingMode::IsDepthTestEnabled()" );
    AssertTrueL( ETrue, KRM3GCMIsDepthTestEnabled );

    TBool depthWriteEnabled = m3gCompositingMode.IsDepthWriteEnabled();
    _LIT( KRM3GCMIsDepthWriteEnabled,
        "RM3GCompositingMode::IsDepthWriteEnabled()" );
    AssertTrueL( ETrue, KRM3GCMIsDepthWriteEnabled );

    m3gCompositingMode.SetAlphaThreshold( thresShold );
    _LIT( KRM3GCMSetAlphaThreshold,
        "RM3GCompositingMode::SetAlphaThreshold()" );
    AssertTrueL( ETrue, KRM3GCMSetAlphaThreshold );

    m3gCompositingMode.SetAlphaWriteEnable( alphaWriteEnabled );
    _LIT( KRM3GCMSetAlphaWriteEnable,
        "RM3GCompositingMode::SetAlphaWriteEnable()" );
    AssertTrueL( ETrue, KRM3GCMSetAlphaWriteEnable );

    m3gCompositingMode.SetBlending( blend );
    _LIT( KRM3GCMSetBlending, "RM3GCompositingMode::SetBlending()" );
    AssertTrueL( ETrue, KRM3GCMSetBlending );

    m3gCompositingMode.SetColorWriteEnable( colorWriteEnabled );
    _LIT( KRM3GCMSetColorWriteEnable,
        "RM3GCompositingMode::SetColorWriteEnable()" );
    AssertTrueL( ETrue, KRM3GCMSetColorWriteEnable );

    m3gCompositingMode.SetDepthOffset( offsetFactor, offsetUnits );
    _LIT( KRM3GCMSetDepthOffset, "RM3GCompositingMode::SetDepthOffset()" );
    AssertTrueL( ETrue, KRM3GCMSetDepthOffset );

    m3gCompositingMode.SetDepthTestEnable( depthTestEnabled );
    _LIT( KRM3GCMSetDepthTestEnable,
        "RM3GCompositingMode::SetDepthTestEnable()" );
    AssertTrueL( ETrue, KRM3GCMSetDepthTestEnable );

    m3gCompositingMode.SetDepthWriteEnable( depthWriteEnabled );
    _LIT( KRM3GCMSetDepthWriteEnable,
        "RM3GCompositingMode::SetDepthWriteEnable()" );
    AssertTrueL( ETrue, KRM3GCMSetDepthWriteEnable );

    m3gCompositingMode.Cast( m3gCompositingMode );
    _LIT( KRM3GCMCast, "RM3GCompositingMode::Cast()" );
    AssertTrueL( ETrue, KRM3GCMCast );

    CleanupStack::PopAndDestroy(); //m3gCompositingMode
    }

// ---------------------------------------------------------------------------
// CBCTestDomM3gCase::TestRM3GFogL
// ---------------------------------------------------------------------------
//
void CBCTestDomM3gCase::TestRM3GFogL()
    {
    RM3GFog m3gFog;
    CleanupClosePushL( m3gFog );
    _LIT( KRM3GFog, "RM3GFog::RM3GFog()" );
    AssertTrueL( ETrue, KRM3GFog );

    m3gFog.OpenL();
    _LIT( KRM3GFogOpenL, "RM3GFog::OpenL()" );
    AssertTrueL( ETrue, KRM3GFogOpenL );

    TInt fogColog = m3gFog.Color();
    _LIT( KRM3GFogColor, "RM3GFog::Color()" );
    AssertTrueL( ETrue, KRM3GFogColor );

    TReal density = m3gFog.Density();
    _LIT( KRM3GFogDensity, "RM3GFog::Density()" );
    AssertTrueL( ETrue, KRM3GFogDensity );

    TReal farDistance = m3gFog.FarDistance();
    _LIT( KRM3GFogFarDistance, "RM3GFog::FarDistance()" );
    AssertTrueL( ETrue, KRM3GFogFarDistance );

    RM3GFog::TMode mode = m3gFog.Mode();
    _LIT( KRM3GFogMode, "RM3GFog::Mode()" );
    AssertTrueL( ETrue, KRM3GFogMode );

    TReal nearDistance = m3gFog.NearDistance();
    _LIT( KRM3GFogNearDistance, "RM3GFog::NearDistance()" );
    AssertTrueL( ETrue, KRM3GFogNearDistance );

    m3gFog.SetColor( fogColog );
    _LIT( KRM3GFogSetColor, "RM3GFog::SetColor()" );
    AssertTrueL( ETrue, KRM3GFogSetColor );

    m3gFog.SetDensity( density );
    _LIT( KRM3GFogSetDensity, "RM3GFog::SetDensity()" );
    AssertTrueL( ETrue, KRM3GFogSetDensity );

    m3gFog.SetLinear( nearDistance, farDistance );
    _LIT( KRM3GFogSetLinear, "RM3GFog::SetLinear()" );
    AssertTrueL( ETrue, KRM3GFogSetLinear );

    m3gFog.SetMode( mode );
    _LIT( KRM3GFogSetMode, "RM3GFog::SetMode()" );
    AssertTrueL( ETrue, KRM3GFogSetMode );

    m3gFog.Cast( m3gFog );
    _LIT( KRM3GFogCast, "RM3GFog::Cast()" );
    AssertTrueL( ETrue, KRM3GFogCast );

    CleanupStack::PopAndDestroy(); //m3gFog
    }

// ---------------------------------------------------------------------------
// CBCTestDomM3gCase::TestRM3GMaterialL
// ---------------------------------------------------------------------------
//
void CBCTestDomM3gCase::TestRM3GMaterialL()
    {
    RM3GMaterial m3gMaterial;
    CleanupClosePushL( m3gMaterial );
    _LIT( KRM3GMaterial, "RM3GMaterial::RM3GMaterial()" );
    AssertTrueL( ETrue, KRM3GMaterial );
    m3gMaterial.OpenL();
    _LIT( KRM3GMaterialOpenL, "RM3GMaterial::OpenL()" );
    AssertTrueL( ETrue, KRM3GMaterialOpenL );

    TInt colorNum = m3gMaterial.Color( RM3GMaterial::ESpecular );
    _LIT( KRM3GMaterialColor, "RM3GMaterial::Color()" );
    AssertTrueL( ETrue, KRM3GMaterialColor );

    m3gMaterial.SetColor( RM3GMaterial::ESpecular, colorNum );
    _LIT( KRM3GMaterialSetColor, "RM3GMaterial::SetColor()" );
    AssertTrueL( ETrue, KRM3GMaterialSetColor );

    TReal shininess = m3gMaterial.Shininess();
    _LIT( KRM3GMaterialShininess, "RM3GMaterial::Shininess()" );
    AssertTrueL( ETrue, KRM3GMaterialShininess );

    TBool isVertex = m3gMaterial.IsVertexColorTrackingEnabled();
    _LIT( KRM3GMaterialIsVertexColorTrackingEnabled,
        "RM3GMaterial::IsVertexColorTrackingEnabled()" );
    AssertTrueL( ETrue, KRM3GMaterialIsVertexColorTrackingEnabled );

    m3gMaterial.SetShininess( shininess );
    _LIT( KRM3GMaterialSetShininess, "RM3GMaterial::SetShininess()" );
    AssertTrueL( ETrue, KRM3GMaterialSetShininess );

    m3gMaterial.SetVertexColorTrackingEnable( isVertex );
    _LIT( KRM3GMaterialSetVertexColorTrackingEnable,
        "RM3GMaterial::SetVertexColorTrackingEnable()" );
    AssertTrueL( ETrue, KRM3GMaterialSetVertexColorTrackingEnable );

    m3gMaterial.Cast( m3gMaterial );
    _LIT( KRM3GMaterialCast, "RM3GMaterial::Cast()" );
    AssertTrueL( ETrue, KRM3GMaterialCast );

    CleanupStack::PopAndDestroy(); //m3gMaterial
    }

// ---------------------------------------------------------------------------
// CBCTestDomM3gCase::TestRM3GPolygonModeL
// ---------------------------------------------------------------------------
//
void CBCTestDomM3gCase::TestRM3GPolygonModeL()
    {
    RM3GPolygonMode m3gPolygonMode;
    CleanupClosePushL( m3gPolygonMode );
    _LIT( KRM3GPolygonMode, "RM3GPolygonMode::RM3GPolygonMode()" );
    AssertTrueL( ETrue, KRM3GPolygonMode );

    m3gPolygonMode.OpenL();
    _LIT( KRM3GPolygonModeOpenL, "RM3GPolygonMode::OpenL()" );
    AssertTrueL( ETrue, KRM3GPolygonModeOpenL );

    RM3GPolygonMode::TCulling culling = m3gPolygonMode.Culling();
    _LIT( KRM3GPolygonModeCulling, "RM3GPolygonMode::Culling()" );
    AssertTrueL( ETrue, KRM3GPolygonModeCulling );

    RM3GPolygonMode::TShading shading = m3gPolygonMode.Shading();
    _LIT( KRM3GPolygonModeShading, "RM3GPolygonMode::Shading()" );
    AssertTrueL( ETrue, KRM3GPolygonModeShading );

    RM3GPolygonMode::TWinding winding = m3gPolygonMode.Winding();
    _LIT( KRM3GPolygonModeWinding, "RM3GPolygonMode::Winding()" );
    AssertTrueL( ETrue, KRM3GPolygonModeWinding );

    TBool isTSLEnabled = m3gPolygonMode.IsTwoSidedLightingEnabled();
    _LIT( KRM3GPolygonModeIsTwoSidedLightingEnabled,
        "RM3GPolygonMode::IsTwoSidedLightingEnabled()" );
    AssertTrueL( ETrue, KRM3GPolygonModeIsTwoSidedLightingEnabled );

    m3gPolygonMode.SetCulling( culling );
    _LIT( KRM3GPolygonModeSetCulling, "RM3GPolygonMode::SetCulling()" );
    AssertTrueL( ETrue, KRM3GPolygonModeSetCulling );

    m3gPolygonMode.SetLocalCameraLightingEnable( isTSLEnabled );
    _LIT( KRM3GPolygonModeSetLocalCameraLightingEnable,
        "RM3GPolygonMode::SetLocalCameraLightingEnable()" );
    AssertTrueL( ETrue, KRM3GPolygonModeSetLocalCameraLightingEnable );

    m3gPolygonMode.SetPerspectiveCorrectionEnable( isTSLEnabled );
    _LIT( KRM3GPolygonModeSetPerspectiveCorrectionEnable,
        "RM3GPolygonMode::SetPerspectiveCorrectionEnable()" );
    AssertTrueL( ETrue, KRM3GPolygonModeSetPerspectiveCorrectionEnable );

    m3gPolygonMode.SetShading( shading );
    _LIT( KRM3GPolygonModeSetShading, "RM3GPolygonMode::SetShading()" );
    AssertTrueL( ETrue, KRM3GPolygonModeSetShading );

    m3gPolygonMode.SetTwoSidedLightingEnable( isTSLEnabled );
    _LIT( KRM3GPolygonModeSetTwoSidedLightingEnable,
        "RM3GPolygonMode::SetTwoSidedLightingEnable()" );
    AssertTrueL( ETrue, KRM3GPolygonModeSetTwoSidedLightingEnable );

    m3gPolygonMode.SetWinding( winding );
    _LIT( KRM3GPolygonModeSetWinding, "RM3GPolygonMode::SetWinding()" );
    AssertTrueL( ETrue, KRM3GPolygonModeSetWinding );

    m3gPolygonMode.Cast( m3gPolygonMode );
    _LIT( KRM3GPolygonModeCast, "RM3GPolygonMode::Cast()" );
    AssertTrueL( ETrue, KRM3GPolygonModeCast );

    CleanupStack::PopAndDestroy(); //m3gPolygonMode
    }

// ---------------------------------------------------------------------------
// CBCTestDomM3gCase::TestRM3GTextureL
// ---------------------------------------------------------------------------
//
void CBCTestDomM3gCase::TestRM3GTextureL()
    {
    RM3GTexture m3gTexture;
    CleanupClosePushL( m3gTexture );
    _LIT( KRM3GTexture, "RM3GTexture::RM3GTexture()" );
    AssertTrueL( ETrue, KRM3GTexture );

    //Construct RM3GImage object;
    RM3GImage m3gImage;
    CleanupClosePushL( m3gImage );
    TUint imageWidth = 16;
    TUint imageHeight = 16;
    TInt flag = 0;
    m3gImage.OpenL( RM3GImage::ERGB,
                    imageWidth,
                    imageHeight,
                    flag );

    m3gTexture.OpenL( m3gImage );
    _LIT( KRM3GTextureOpenL, "RM3GTexture::OpenL()" );
    AssertTrueL( ETrue, KRM3GTextureOpenL );

    TInt bColor = m3gTexture.BlendColor();
    _LIT( KRM3GTextureBlendColor, "RM3GTexture::BlendColor()" );
    AssertTrueL( ETrue, KRM3GTextureBlendColor );

    RM3GTexture::TBlending blending = m3gTexture.Blending();
    _LIT( KRM3GTextureBlending, "RM3GTexture::Blending()" );
    AssertTrueL( ETrue, KRM3GTextureBlending );

    RM3GImage m3gImageCopy = m3gTexture.Image();
    CleanupClosePushL( m3gImageCopy );
    _LIT( KRM3GTextureImage, "RM3GTexture::Image()" );
    AssertTrueL( ETrue, KRM3GTextureImage );

    RM3GTexture::TWrapping wrappingS = m3gTexture.WrappingS();
    _LIT( KRM3GTextureWrappingS, "RM3GTexture::WrappingS()" );
    AssertTrueL( ETrue, KRM3GTextureWrappingS );

    RM3GTexture::TWrapping wrappingT = m3gTexture.WrappingT();
    _LIT( KRM3GTextureWrappingT, "RM3GTexture::WrappingT()" );
    AssertTrueL( ETrue, KRM3GTextureWrappingT );

    m3gTexture.SetBlendColor( bColor );
    _LIT( KRM3GTextureSetBlendColor, "RM3GTexture::SetBlendColor()" );
    AssertTrueL( ETrue, KRM3GTextureSetBlendColor);

    m3gTexture.SetBlending( blending );
    _LIT( KRM3GTextureSetBlending, "RM3GTexture::SetBlending()" );
    AssertTrueL( ETrue, KRM3GTextureSetBlending );

    m3gTexture.SetFiltering( RM3GTexture::EBaseLevel, RM3GTexture::ELinear );
    _LIT( KRM3GTextureSetFiltering, "RM3GTexture::SetFiltering()" );
    AssertTrueL( ETrue, KRM3GTextureSetFiltering );

    m3gTexture.SetImage( m3gImage );
    _LIT( KRM3GTextureSetImage, "RM3GTexture::SetImage()" );
    AssertTrueL( ETrue, KRM3GTextureSetImage);

    m3gTexture.SetWrapping( wrappingS, wrappingT );
    _LIT( KRM3GTextureSetWrapping, "RM3GTexture::SetWrapping()" );
    AssertTrueL( ETrue, KRM3GTextureSetWrapping );

    m3gTexture.Cast( m3gTexture );
    _LIT( KRM3GTextureCast, "RM3GTexture::Cast()" );
    AssertTrueL( ETrue, KRM3GTextureCast );

    CleanupStack::PopAndDestroy( 3 ); //m3gTexture, m3gImage, m3gImageCopy
    }

// ---------------------------------------------------------------------------
// CBCTestDomM3gCase::TestRM3GKeyframeSequenceL
// ---------------------------------------------------------------------------
//
void CBCTestDomM3gCase::TestRM3GKeyframeSequenceL()
    {
    RM3GKeyframeSequence keyFrameSeq;
    CleanupClosePushL( keyFrameSeq );
    _LIT( KRM3GKfSequence, "RM3GKeyframeSequence::RM3GKeyframeSequence()" );
    AssertTrueL( ETrue, KRM3GKfSequence );

    const TInt keyframeCount = 1;
    const TInt componentCount = 1;
    keyFrameSeq.OpenL( keyframeCount,
                       componentCount,
                       RM3GKeyframeSequence::ELinear );
    _LIT( KRM3GKfSequenceOpenL, "RM3GKeyframeSequence::OpenL()" );
    AssertTrueL( ETrue, KRM3GKfSequenceOpenL );

    TInt duration = keyFrameSeq.Duration();
    _LIT( KRM3GKfSequenceDuration, "RM3GKeyframeSequence::Duration()" );
    AssertTrueL( ETrue, KRM3GKfSequenceDuration );

    RM3GKeyframeSequence::TRepeatMode rpMode = keyFrameSeq.RepeatMode();
    _LIT( KRM3GKfSequenceRepeatMode, "RM3GKeyframeSequence::RepeatMode()" );
    AssertTrueL( ETrue, KRM3GKfSequenceRepeatMode );

    keyFrameSeq.SetDuration( duration );
    _LIT( KRM3GKfSequenceSetDuration, "RM3GKeyframeSequence::SetDuration()" );
    AssertTrueL( ETrue, KRM3GKfSequenceSetDuration );

    RArray<TReal> values;
    CleanupClosePushL( values );
    const TInt index = 0;
    const TInt time = 0;
    keyFrameSeq.SetKeyframe( index, time, values );
    _LIT( KRM3GKfSequenceSetKeyframe, "RM3GKeyframeSequence::SetKeyframe()" );
    AssertTrueL( ETrue, KRM3GKfSequenceSetKeyframe );

    keyFrameSeq.SetRepeatMode( rpMode );
    _LIT( KRM3GKfSequenceSetRepeatMode,
        "RM3GKeyframeSequence::SetRepeatMode()" );
    AssertTrueL( ETrue, KRM3GKfSequenceSetRepeatMode );

    const TInt firstNum = 0;
    const TInt SecondNum = 10;
    keyFrameSeq.SetValidRange( firstNum, SecondNum);
    _LIT( KRM3GKfSequenceSetValidRange,
        "RM3GKeyframeSequence::SetValidRange()" );
    AssertTrueL( ETrue, KRM3GKfSequenceSetValidRange );

    keyFrameSeq.Cast( keyFrameSeq );
    _LIT( KRM3GKfSequenceCast, "RM3GKeyframeSequence::Cast()" );
    AssertTrueL( ETrue, KRM3GKfSequenceCast );

    CleanupStack::PopAndDestroy( 2 );// keyFrameSeq, values

    //Test TM3GMatrix::Unity()
    TM3GMatrix m3gMatrix;
    m3gMatrix.Unity();
    _LIT( KTM3GMatrix, "TM3GMatrix::Unity()" );
    AssertTrueL( ETrue, KTM3GMatrix );
    }

// ---------------------------------------------------------------------------
// CBCTestDomM3gCase::TestRM3GVertexBufferL
// ---------------------------------------------------------------------------
//
void CBCTestDomM3gCase::TestRM3GVertexBufferL()
    {
    RM3GVertexBuffer m3gVertexBuffer;
    CleanupClosePushL( m3gVertexBuffer );
    _LIT( KRM3GVertexBuffer, "RM3GVertexBuffer::RM3GVertexBuffer()" );
    AssertTrueL( ETrue, KRM3GVertexBuffer );

    m3gVertexBuffer.OpenL();
    _LIT( KRM3GVBOpenL, "RM3GVertexBuffer::OpenL()" );
    AssertTrueL( ETrue, KRM3GVBOpenL );

    RM3GVertexArray m3gArray = m3gVertexBuffer.Colors();
    CleanupClosePushL( m3gArray );
    _LIT( KRM3GVBColors, "RM3GVertexBuffer::Colors()" );
    AssertTrueL( ETrue, KRM3GVBColors );

    TUint defaultColor = m3gVertexBuffer.DefaultColor();
    _LIT( KRM3GVBDefaultColor, "RM3GVertexBuffer::DefaultColor()" );
    AssertTrueL( ETrue, KRM3GVBDefaultColor );

    RM3GVertexArray normalArray = m3gVertexBuffer.Normals();
    CleanupClosePushL( normalArray );
    _LIT( KRM3GVBNormals, "RM3GVertexBuffer::Normals()" );
    AssertTrueL( ETrue, KRM3GVBNormals );

    RArray<TReal32> scaleBias;
    CleanupClosePushL( scaleBias );
    RM3GVertexArray positionArray = m3gVertexBuffer.Positions( scaleBias );
    CleanupClosePushL( positionArray );
    _LIT( KRM3GVBPositions, "RM3GVertexBuffer::Positions()" );
    AssertTrueL( ETrue, KRM3GVBPositions );

    TInt index = 0;
    RM3GVertexArray textCoords =
        m3gVertexBuffer.TexCoords( index, scaleBias );
    CleanupClosePushL( textCoords );
    _LIT( KRM3GVBTexCoords, "RM3GVertexBuffer::TexCoords()" );
    AssertTrueL( ETrue, KRM3GVBTexCoords );

    m3gVertexBuffer.VertexCount();
    _LIT( KRM3GVBVertexCount, "RM3GVertexBuffer::VertexCount()" );
    AssertTrueL( ETrue, KRM3GVBVertexCount );

    m3gVertexBuffer.SetColors( m3gArray );
    _LIT( KRM3GVBSetColors, "RM3GVertexBuffer::SetColors()" );
    AssertTrueL( ETrue, KRM3GVBSetColors );

    m3gVertexBuffer.SetDefaultColor( defaultColor );
    _LIT( KRM3GVBSetDefaultColor, "RM3GVertexBuffer::SetDefaultColor()" );
    AssertTrueL( ETrue, KRM3GVBSetDefaultColor );

    m3gVertexBuffer.SetNormals( normalArray );
    _LIT( KRM3GVBSetNormals, "RM3GVertexBuffer::SetNormals()" );
    AssertTrueL( ETrue, KRM3GVBSetNormals );

    TM3GVector3 m3gVector3;
    TReal scale = 1.0;
    m3gVertexBuffer.SetPositions( positionArray, scale, m3gVector3 );
    _LIT( KRM3GVBSetPositions, "RM3GVertexBuffer::SetPositions()" );
    AssertTrueL( ETrue, KRM3GVBSetPositions );

    TInt textUint = 1;
    m3gVertexBuffer.SetTexCoords( textUint, textCoords, scale, m3gVector3 );
    _LIT( KRM3GVBSetTexCoordsV3, "RM3GVertexBuffer::SetTexCoords()" );
    AssertTrueL( ETrue, KRM3GVBSetTexCoordsV3 );

    TM3GVector2 m3gVector2;
    m3gVertexBuffer.SetTexCoords( textUint, textCoords, scale, m3gVector2 );
    _LIT( KRM3GVBSetTexCoordsV2, "RM3GVertexBuffer::SetTexCoords()" );
    AssertTrueL( ETrue, KRM3GVBSetTexCoordsV2 );

    m3gVertexBuffer.Cast( m3gVertexBuffer );
    _LIT( KRM3GVBCast, "RM3GVertexBuffer::Cast()" );
    AssertTrueL( ETrue, KRM3GVBCast );

    // m3gVertexBuffer, m3gArray, normalArray,
    // scaleBias, positionArray, textCoords
    CleanupStack::PopAndDestroy( 6, &m3gVertexBuffer );
    }

// ---------------------------------------------------------------------------
// CBCTestDomM3gCase::TestRM3GVertexArrayL
// ---------------------------------------------------------------------------
//
void CBCTestDomM3gCase::TestRM3GVertexArrayL()
    {
    //Test APIS of class RM3GVertexArray as follow.
    RM3GVertexArray m3gVertextArray;
    CleanupClosePushL( m3gVertextArray );
    _LIT( KRM3GVertexArray, "RM3GVertexArray::RM3GVertexArray()" );
    AssertTrueL( ETrue, KRM3GVertexArray );

    TUint vertexCount = 12;
    TUint componentCount = 3;
    m3gVertextArray.OpenL( vertexCount, componentCount, EM3GShort );
    _LIT( KRM3GVertexArrayOpenL, "RM3GVertexArray::OpenL()" );
    AssertTrueL( ETrue, KRM3GVertexArrayOpenL );

    TUint firstVertex = 1;
    TUint aSourceBufferLength = 3;
    TInt8 vertics8 = 2;
    TInt16 vertics16 = 2;
    m3gVertextArray.Set( firstVertex,
                         vertexCount,
                         aSourceBufferLength,
                         &vertics8 );
    _LIT( KRM3GVertexArraySet8, "RM3GVertexArray::Set()" );
    AssertTrueL( ETrue, KRM3GVertexArraySet8 );

    m3gVertextArray.Set( firstVertex,
                         vertexCount,
                         aSourceBufferLength,
                         &vertics16 );
    _LIT( KRM3GVertexArraySet16, "RM3GVertexArray::Set()" );
    AssertTrueL( ETrue, KRM3GVertexArraySet16 );

    m3gVertextArray.Cast( m3gVertextArray );
    _LIT( KRM3GVertexArrayCast, "RM3GVertexArray::Cast()" );
    AssertTrueL( ETrue, KRM3GVertexArrayCast );

    CleanupStack::PopAndDestroy(); //m3gVertextArray
    }

// ---------------------------------------------------------------------------
// CBCTestDomM3gCase::TestRM3GTriangleStripArrayL
// ---------------------------------------------------------------------------
//
void CBCTestDomM3gCase::TestRM3GTriangleStripArrayL()
    {
    //Test APIS of class RM3GTriangleStripArray as follow.
    RM3GTriangleStripArray m3gStripArray;
    CleanupClosePushL( m3gStripArray );
    _LIT( KRM3GTSA, "RM3GTriangleStripArray::RM3GTriangleStripArray()" );
    AssertTrueL( ETrue, KRM3GTSA );

    TInt indices[] = { 4, 1, 0, 3 };
    TInt indexCount = 4;
    TInt stripLengths[] = { 3, 3 };
    TInt stripLengthCount = 2;
    TInt firstIndex = 1;
    m3gStripArray.OpenL( firstIndex,
                         stripLengths,
                         stripLengthCount );
    _LIT( KRM3GTSAOpenLOver, "RM3GTriangleStripArray::OpenL()" );
    AssertTrueL( ETrue, KRM3GTSAOpenLOver );


    RM3GTriangleStripArray m3gStripArray2;
    CleanupClosePushL( m3gStripArray2 );
    TInt err;
    TRAP( err, m3gStripArray2.OpenL( indices,
                                      indexCount,
                                      stripLengths,
                                      stripLengthCount ) );
    _LIT( KRM3GTSAOpenL, "RM3GTriangleStripArray::OpenL()" );
    AssertTrueL( ETrue, KRM3GTSAOpenL );

    CleanupStack::PopAndDestroy( 2 ); //m3gStripArray, m3gStripArray2
    }

// ---------------------------------------------------------------------------
// CBCTestDomM3gCase::TestRM3GIndexBufferL
// ---------------------------------------------------------------------------
//
void CBCTestDomM3gCase::TestRM3GIndexBufferL()
    {
    //Test APIS of class RM3GIndexBuffer as follow.
    RM3GIndexBuffer m3gIndexBuffer;
    CleanupClosePushL( m3gIndexBuffer );
    _LIT( KRM3GIB, "RM3GIndexBuffer::RM3GIndexBuffer()" );
    AssertTrueL( ETrue, KRM3GIB );

    TInt indices[] = { 4, 1, 0, 3 };
    TInt indexCount = 4;
    TInt stripLengths[] = { 3, 3 };
    TInt stripLengthCount = 2;
    TInt firstIndex = 1;
    m3gIndexBuffer.OpenL( firstIndex, stripLengths, stripLengthCount );
    _LIT( KRM3GIndexBufferOpenL, "RM3GIndexBuffer::OpenL()" );
    AssertTrueL( ETrue, KRM3GIndexBufferOpenL );

    RM3GIndexBuffer m3gIndexBuffer2;
    CleanupClosePushL( m3gIndexBuffer2 );
    TInt err;
    TRAP( err, m3gIndexBuffer2.OpenL( indices,
                                       indexCount,
                                       stripLengths,
                                       stripLengthCount ) );
    _LIT( KRM3GIBOpenL, "RM3GIndexBuffer::OpenL()" );
    AssertTrueL( ETrue, KRM3GIBOpenL );


    CleanupStack::PopAndDestroy( 2 ); //m3gIndexBuffer, m3gIndexBuffer2
    }

// ---------------------------------------------------------------------------
// CBCTestDomM3gCase::TestRM3GAnimationControllerL
// ---------------------------------------------------------------------------
//
void CBCTestDomM3gCase::TestRM3GAnimationControllerL()
    {
    RM3GAnimationController m3gAC;
    CleanupClosePushL( m3gAC );
    _LIT( KRM3GAC, "RM3GAnimationController::RM3GAnimationController()" );
    AssertTrueL( ETrue, KRM3GAC );

    m3gAC.OpenL();
    _LIT( KRM3GACOpenL, "RM3GAnimationController::OpenL()" );
    AssertTrueL( ETrue, KRM3GACOpenL );

    TInt start = m3gAC.ActiveIntervalStart();
    _LIT( KRM3GACActiveIntervalStart,
        "RM3GAnimationController::ActiveIntervalStart()" );
    AssertTrueL( ETrue, KRM3GACActiveIntervalStart );

    TInt end = m3gAC.ActiveIntervalEnd();
    _LIT( KRM3GACActiveIntervalEnd,
        "RM3GAnimationController::ActiveIntervalEnd()" );
    AssertTrueL( ETrue, KRM3GACActiveIntervalEnd );

    TInt minT = 1;
    TInt maxT = 10;
    m3gAC.SetActiveInterval( minT, maxT );
    _LIT( KRM3GACSetActiveInterval,
        "RM3GAnimationController::SetActiveInterval()" );
    AssertTrueL( ETrue, KRM3GACSetActiveInterval );

    TReal speed = m3gAC.Speed();
    _LIT( KRM3GACSpeed, "RM3GAnimationController::Speed()" );
    AssertTrueL( ETrue, KRM3GACSpeed );

    TInt worldTime = 10;
    m3gAC.SetSpeed( speed, worldTime );
    _LIT( KRM3GACSetSpeed, "RM3GAnimationController::SetSpeed()" );
    AssertTrueL( ETrue, KRM3GACSetSpeed );

    m3gAC.Position( worldTime );
    _LIT( KRM3GACPosition, "RM3GAnimationController::Position()" );
    AssertTrueL( ETrue, KRM3GACPosition );

    TReal32 sTime = 5.00;
    m3gAC.SetPosition( sTime, worldTime );
    _LIT( KRM3GACSetPosition, "RM3GAnimationController::SetPosition()" );
    AssertTrueL( ETrue, KRM3GACSetPosition );

    TReal weight = m3gAC.Weight();
    _LIT( KRM3GACWeight, "RM3GAnimationController::Weight()" );
    AssertTrueL( ETrue, KRM3GACWeight );

    m3gAC.SetWeight( weight );
    _LIT( KRM3GACSetWeight, "RM3GAnimationController::SetWeight()" );
    AssertTrueL( ETrue, KRM3GACSetWeight );

    m3gAC.Cast( m3gAC );
    _LIT( KRM3GACCast, "RM3GAnimationController::Cast()" );
    AssertTrueL( ETrue, KRM3GACCast );

    CleanupStack::PopAndDestroy(); //m3gAC

    //Test APIS of class RM3GAnimationTrack as follow.
    RM3GAnimationTrack m3gAnimationT;
    CleanupClosePushL( m3gAnimationT );
    _LIT( KRM3GAT, "RM3GAnimationTrack::RM3GAnimationTrack()" );
    AssertTrueL( ETrue, KRM3GAT );

    RM3GKeyframeSequence m3gKeyframeSequence;
    CleanupClosePushL( m3gKeyframeSequence );
    const TInt keyframeCount = 1;
    const TInt componentCount = 1;
    m3gKeyframeSequence.OpenL( keyframeCount,
                       componentCount,
                       RM3GKeyframeSequence::ELinear );
    m3gAnimationT.OpenL( m3gKeyframeSequence, RM3GAnimationTrack::EDensity );
    _LIT( KRM3GATOpenL, "RM3GAnimationTrack::OpenL()" );
    AssertTrueL( ETrue, KRM3GATOpenL );

    RM3GAnimationController copyAController = m3gAnimationT.Controller();
    CleanupClosePushL( copyAController );
    _LIT( KRM3GATController, "RM3GAnimationTrack::Controller()" );
    AssertTrueL( ETrue, KRM3GATController );

    m3gAnimationT.SetController( copyAController );
    _LIT( KRM3GATSetController, "RM3GAnimationTrack::SetController()" );
    AssertTrueL( ETrue, KRM3GATSetController );

    m3gAnimationT.KeyframeSequence();
    _LIT( KRM3GATKeyframeSequence, "RM3GAnimationTrack::KeyframeSequence()" );
    AssertTrueL( ETrue, KRM3GATKeyframeSequence );

    m3gAnimationT.TargetProperty();
    _LIT( KRM3GATTargetProperty, "RM3GAnimationTrack::TargetProperty()" );
    AssertTrueL( ETrue, KRM3GATTargetProperty );

    m3gAnimationT.Cast( m3gAnimationT );
    _LIT( KRM3GATCast, "RM3GAnimationTrack::Cast()" );
    AssertTrueL( ETrue, KRM3GATCast );

    //m3gAnimationT, copyAController, m3gKeyframeSequence.
    CleanupStack::PopAndDestroy( 3 );
    }

// ---------------------------------------------------------------------------
// CBCTestDomM3gCase::TestRM3GImageL
// ---------------------------------------------------------------------------
//
void CBCTestDomM3gCase::TestRM3GImageL()
    {
    RM3GImage m3gImage;
    CleanupClosePushL( m3gImage );
    _LIT( KRM3GImage, "RM3GImage::RM3GImage()" );
    AssertTrueL( ETrue, KRM3GImage );

    TInt imageWidth = 20;
    TInt imageHeight = 20;
    TInt flag = 8;
    m3gImage.OpenL( RM3GImage::ELuminance,
                    imageWidth,
                    imageHeight,
                    flag );
    _LIT( KRM3GImageOpenL, "RM3GImage::OpenL()" );
    AssertTrueL( ETrue, KRM3GImageOpenL );

    TUint param = 4029;
    m3gImage.SetImage( &param );
    _LIT( KRM3GImageSetImage, "RM3GImage::SetImage()" );
    AssertTrueL( ETrue, KRM3GImageSetImage );


    const TUint32 color16array[16] = {
    0x00000000,0x00555555,0x00000080,0x00008080,
    0x00008000,0x000000ff,0x0000ffff,0x0000ff00,
    0x00ff00ff,0x00ff0000,0x00ffff00,0x00800080,
    0x00800000,0x00808000,0x00aaaaaa,0x00ffffff};

    TInt paletteLength = 16;
    m3gImage.SetImagePalette( paletteLength, color16array );
    _LIT( KRM3GImageSetImagePalette, "RM3GImage::SetImagePalette()" );
    AssertTrueL( ETrue, KRM3GImageSetImagePalette );

    TInt line = 1;
    TBool trueAlpha = EFalse;
    m3gImage.SetImageScanLine( line, trueAlpha, &param );
    _LIT( KRM3GImageSetImageScanLine, "RM3GImage::SetImageScanLine()" );
    AssertTrueL( ETrue, KRM3GImageSetImageScanLine );

    TInt x = 0;
    TInt y = 0;
    m3gImage.SetSubImage( x, y, imageWidth,
                          imageHeight, paletteLength, &param );
    _LIT( KRM3GImageSetSubImage, "RM3GImage::SetSubImage()" );
    AssertTrueL( ETrue, KRM3GImageSetSubImage );

    m3gImage.Format();
    _LIT( KRM3GImageFormat, "RM3GImage::Format()" );
    AssertTrueL( ETrue, KRM3GImageFormat );

    m3gImage.Height();
    _LIT( KRM3GImageHeight, "RM3GImage::Height()" );
    AssertTrueL( ETrue, KRM3GImageHeight );

    m3gImage.Width();
    _LIT( KRM3GImageWidth, "RM3GImage::Width()" );
    AssertTrueL( ETrue, KRM3GImageWidth );

    m3gImage.IsMutable();
    _LIT( KRM3GImageIsMutable, "RM3GImage::IsMutable()" );
    AssertTrueL( ETrue, KRM3GImageIsMutable );

    m3gImage.Cast( m3gImage );
    _LIT( KRM3GImageCast, "RM3GImage::Cast()" );
    AssertTrueL( ETrue, KRM3GImageCast);

    CleanupStack::PopAndDestroy();//m3gImage
    }

