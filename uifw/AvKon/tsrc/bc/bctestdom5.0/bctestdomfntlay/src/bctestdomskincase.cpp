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
* Description:  test case
 *
*/


#include <w32std.h>
#include <coecntrl.h>
#include <eikenv.h>
#include <aknsconstants.h>
#include <aknsdrawutils.h>
#include <aknsimageattributedata.h>

#include <aknseffectanim.h>
#include <aknsitemdef.h>
#include <aknspkgid.h>
#include <aknspointerstore.h>
#include <aknsrendererwrapper.h>
#include <aknsskinuid.h>
#include <aknssrvchunklookup.h>
#include <aknssrvclient.h>
#include <aknssrvskininformationpkg.h>

#include "bctestdomskincase.h"
#include "bctestdomfntlaycontainer.h"
#include "bctestdomfntlay.hrh"

class CAknsEffectAnimObserver : public CBase ,public MAknsEffectAnimObserver
    {
    void AnimFrameReady( TInt aError, TInt aAnimId );
    } ;

void CAknsEffectAnimObserver::AnimFrameReady( TInt aError, TInt /* aAnimId */ )
    {
    TBuf<16> strError;
    _LIT( KTxtError, "CAknsEffectAnim Error :" );
    strError.Append( KTxtError );
    strError.AppendNum( aError ) ;
    RDebug::Print( strError );
    }

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//

CBCTestDomSkinCase* CBCTestDomSkinCase::NewL( )
    {
    CBCTestDomSkinCase* self = new( ELeave ) CBCTestDomSkinCase();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestDomSkinCase::CBCTestDomSkinCase()
   {
   }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDomSkinCase::~CBCTestDomSkinCase()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomSkinCase::ConstructL()
    {
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCTestDomSkinCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestDomSkinCase::BuildScriptL()
    {
    // Add script as your need.
    AddTestL( DELAY(1),
              LeftCBA, REP(Down,1), LeftCBA, LeftCBA,
              LeftCBA, REP(Down,1), LeftCBA, REP(Down,1), LeftCBA,
              LeftCBA, REP(Down,1), LeftCBA, REP(Down,2), LeftCBA,
              LeftCBA, REP(Down,1), LeftCBA, REP(Down,3), LeftCBA,
              LeftCBA, REP(Down,1), LeftCBA, REP(Down,4), LeftCBA,
              LeftCBA, REP(Down,1), LeftCBA, REP(Down,5), LeftCBA,
              LeftCBA, REP(Down,1), LeftCBA, REP(Down,6), LeftCBA,
              LeftCBA, REP(Down,1), LeftCBA, REP(Down,7), LeftCBA,
              LeftCBA, REP(Down,1), LeftCBA, REP(Down,8), LeftCBA,
              TEND );
    }

// ---------------------------------------------------------------------------
// CBCTestDomSkinCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestDomSkinCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestDomCmdOutline04 || aCmd > EBCTestDomCmdOutline12 )
        {
        return;
        }
    switch ( aCmd )
        {
        case EBCTestDomCmdOutline04: //AknsEffectAnim.h  22
            {
            TestEffectAnimL();
            break;
            }
        case EBCTestDomCmdOutline05: //AknsItemDef.h
            {
            TestItemDefL();
            break;
            }
        case EBCTestDomCmdOutline06: //AknsItemDef.h
            {
            TestItemDef2L();
            break;
            }
        case EBCTestDomCmdOutline07: //AknsPkgID.h 3
            {
            TestPkgIDL();
            break;
            }
        case EBCTestDomCmdOutline08: //AknsPointerStore.h 3
            {
            TestPointerStoreL();
            break;
            }
        case EBCTestDomCmdOutline09: //AknsRendererWrapper.h 1
            {
            TestRendererWrapperL();
            break;
            }
        case EBCTestDomCmdOutline10: //AknsSrvChunkLookup.h
            {
            TestSrvChunkLookupL();
            break;
            }
        case EBCTestDomCmdOutline11: //AknsSrvClient.h 25
            {
            TestSrvClientL();
            break;
            }
        case EBCTestDomCmdOutline12: //AknsSrvSkinInformationPkg.h 15
            {
            TestSrvSkinInformationPkgL();
            break;
            }
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestDomSkinCase::TestEffectAnimL
// ---------------------------------------------------------------------------
//
void CBCTestDomSkinCase::TestEffectAnimL()//AknsEffectAnim.h  22
    {
    CAknsEffectAnimObserver* observer =
        new (ELeave) CAknsEffectAnimObserver();
    CleanupStack::PushL( observer );
    CAknsEffectAnim* effictAnim = CAknsEffectAnim::NewL( observer );
    CleanupStack::PushL( effictAnim );
    _LIT( KTxtNewL, "CAknsEffectAnim::NewL" );
    AssertTrueL( ETrue, KTxtNewL );

    TBool isSuc = effictAnim->ConstructFromSkinL(
        KAknsIIDQgnIndiTpDialler );//
    _LIT( KTxtConstructFromSkinL,
        "CAknsEffectAnim::ConstructFromSkinL" );
    AssertTrueL( ETrue, KTxtConstructFromSkinL );

    TInt ret = effictAnim->Start();
    _LIT( KTxtStart, "CAknsEffectAnim::Start" );
    AssertTrueL( ETrue, KTxtStart );

    ret = effictAnim->Pause();
    _LIT( KTxtPause, "CAknsEffectAnim::Pause" );
    AssertTrueL( ETrue, KTxtPause );

    ret = effictAnim->Continue();
    _LIT( KTxtContinue, "CAknsEffectAnim::Continue" );
    AssertTrueL( ETrue, KTxtContinue );

    ret = effictAnim->Stop();
    _LIT( KTxtStop, "CAknsEffectAnim::Stop" );
    AssertTrueL( ETrue, KTxtStop );

    ret = effictAnim->State();
    _LIT( KTxtState, "CAknsEffectAnim::State" );
    AssertTrueL( ETrue, KTxtState );

    CFbsBitGc* fbsBitgc = CFbsBitGc::NewL();
    CleanupStack::PushL( fbsBitgc );
    isSuc = effictAnim->Render( *fbsBitgc, TRect( 50, 50, 10, 10 ) );
    _LIT( KTxtRender, "CAknsEffectAnim::Render" );
    AssertTrueL( ETrue, KTxtRender );

    CWindowGc& gc = CCoeEnv::Static()->SystemGc();
    isSuc = effictAnim->Render( gc, TRect( 50, 50, 10, 10 ) );
    _LIT( KTxtRender2, "CAknsEffectAnim::Render2" );
    AssertTrueL( ETrue, KTxtRender2 );

    CBitmapContext& bitmapGc = gc;
    isSuc = effictAnim->Render( bitmapGc, TRect( 50, 50, 10, 10 ) );
    _LIT( KTxtRender3, "CAknsEffectAnim::Render3" );
    AssertTrueL( ETrue, KTxtRender3 );

    const CFbsBitmap* fbcBitmap = effictAnim->OutputRgb();
    _LIT( KTxtOutputRgb, "CAknsEffectAnim::OutputRgb" );
    AssertTrueL (ETrue, KTxtOutputRgb );

    fbcBitmap = effictAnim->OutputAlpha();
    _LIT( KTxtOutputAlpha, "CAknsEffectAnim::OutputAlpha" );
    AssertTrueL( ETrue, KTxtOutputAlpha );

    TSize minSize = effictAnim->MinimumSize();
    _LIT( KTxtMinimumSize, "CAknsEffectAnim::MinimumSize" );
    AssertTrueL( ETrue, KTxtMinimumSize );

    minSize = effictAnim->Size();
    _LIT( KTxtSize, "CAknsEffectAnim::Size" );
    AssertTrueL( ETrue, KTxtSize );

    isSuc = effictAnim->NeedsInputLayer();
    _LIT( KTxtNeedsInputLayer, "CAknsEffectAnim::NeedsInputLayer" );
    AssertTrueL( ETrue, KTxtNeedsInputLayer );

    effictAnim->BeginConfigInputLayersL( TSize( 10, 20 ), EFalse );
    _LIT( KTxtBeginConfigInputLayersL,
        "CAknsEffectAnim::BeginConfigInputLayersL" );
    AssertTrueL( ETrue, KTxtBeginConfigInputLayersL );

    CFbsBitGc* fbGc = effictAnim->InputRgbGc();
    _LIT( KTxtInputRgbGc, "CAknsEffectAnim::InputRgbGc" );
    AssertTrueL( ETrue, KTxtInputRgbGc );

    fbGc = effictAnim->InputAlphaGc();
    _LIT( KTxtInputAlphaGc, "CAknsEffectAnim::InputAlphaGc" );
    AssertTrueL( ETrue, KTxtInputAlphaGc );

    effictAnim->EndConfigInputLayersL();
    _LIT( KTxtEndConfigInputLayersL,
        "CAknsEffectAnim::EndConfigInputLayersL" );
    AssertTrueL( ETrue, KTxtEndConfigInputLayersL );

    ret = effictAnim->UpdateOutput();
    _LIT( KTxtUpdateOutput, "CAknsEffectAnim::UpdateOutput" );
    AssertTrueL( ETrue, KTxtUpdateOutput );

    effictAnim->SetIdling( 5 );
    _LIT( KTxtSetIdling, "CAknsEffectAnim::SetIdling" );
    AssertTrueL( ETrue, KTxtSetIdling );

    TBool isidling = effictAnim->IsIdling();
    _LIT( KTxtIsIdling, "CAknsEffectAnim::IsIdling" );
    AssertTrueL( ETrue, KTxtIsIdling );


    CleanupStack::PopAndDestroy( fbsBitgc );
    CleanupStack::PopAndDestroy( effictAnim );
    _LIT( KTxtDelete, "CAknsEffectAnim::~CAknsEffectAnim" );
    AssertTrueL( ETrue, KTxtDelete );

    CleanupStack::PopAndDestroy( observer );
    }

// ---------------------------------------------------------------------------
// CBCTestDomSkinCase::TestItemDefL
// ---------------------------------------------------------------------------
//
void CBCTestDomSkinCase::TestItemDefL() //AknsItemDef.h
    {
    //CAknsItemDef
    CAknsItemDef* itemDef = CAknsItemDef::NewL(
        KAknsIIDQgnIndiTpDialler );
    CleanupStack::PushL( itemDef );
    _LIT( KTxtNewL, "CAknsItemDef::NewL" );
    AssertTrueL( ETrue, KTxtNewL );

    TAknsItemType itemType = itemDef->Type();
    _LIT (KTxtType, "CAknsItemDef::Type" );
    AssertTrueL( ETrue, KTxtType );

    TAknsItemID itemID = itemDef->ID();
    _LIT( KTxtID, "CAknsItemDef::ID" );
    AssertTrueL( ETrue, KTxtID );

    TInt ret = CAknsItemDef::LinearOrder( *itemDef, *itemDef );
    _LIT( KTxtLinearOrder, "CAknsItemDef::LinearOrder" );
    AssertTrueL( ETrue, KTxtLinearOrder );

    CleanupStack::PopAndDestroy( itemDef );
    _LIT( KTxtDelete, "CAknsItemDef::~CAknsItemDef" );
    AssertTrueL( ETrue, KTxtDelete );

    //CAknsImageItemDef
    CAknsImageItemDef* imageItemDef =
        CAknsImageItemDef::NewL( KAknsIIDQgnIndiTpDialler );
    CleanupStack::PushL (imageItemDef );
    _LIT( KTxtImageNewL, "CAknsImageItemDef::NewL" );
    AssertTrueL( ETrue, KTxtImageNewL );

    TAknsImageAttributeData attributeData;
    imageItemDef->SetAttributesL( attributeData );
    _LIT( KTxtSetAttributesL, "CAknsImageItemDef::SetAttributesL" );
    AssertTrueL( ETrue, KTxtSetAttributesL );

    const TAknsImageAttributeData* attriData =
        imageItemDef->Attributes();
    _LIT( KTxtAttributes, "CAknsImageItemDef::Attributes" );
    AssertTrueL( ETrue, KTxtAttributes );

    CleanupStack::PopAndDestroy( imageItemDef );

    //CAknsBitmapItemDef
    _LIT( KTxtFilename, "\\resource\\apps\\BCTestDomfntlay.mbm" );
    CAknsBitmapItemDef* bitmapItemDef =
        CAknsBitmapItemDef::NewL(
        KAknsIIDQgnIndiTpDialler, KTxtFilename, 1 );
    CleanupStack::PushL( bitmapItemDef );
    _LIT( KTxtBitmapNewL ,"CAknsBitmapItemDef::NewL" );
    AssertTrueL( ETrue, KTxtBitmapNewL );

    CAknsBitmapItemDef* bitmapItemDef2 =
        CAknsBitmapItemDef::NewL( KAknsIIDQgnIndiTpDialler );
    CleanupStack::PushL( bitmapItemDef2 );
    _LIT( KTxtBitmapNewL2, "CAknsBitmapItemDef::NewL2" );
    AssertTrueL( ETrue, KTxtBitmapNewL2 );
    CleanupStack::PopAndDestroy( bitmapItemDef2 );

    _LIT( KFileName, "abc.bmp" );
    bitmapItemDef->SetFilename( KFileName );
    _LIT( KTxtSetFilename, "CAknsBitmapItemDef::SetFilename" );
    AssertTrueL( ETrue, KTxtSetFilename );

    bitmapItemDef->SetFilenameL( KFileName );
    _LIT( KTxtSetFilenameL, "CAknsBitmapItemDef::SetFilenameL" );
    AssertTrueL( ETrue, KTxtSetFilenameL );

    const TDesC& filename = bitmapItemDef->Filename();
    _LIT( KTxtBitmapFilename, "CAknsBitmapItemDef::Filename" );
    AssertTrueL( ETrue, KTxtBitmapFilename );

    bitmapItemDef->SetIndex( 1 );
    _LIT( KTxtSetIndex, "CAknsBitmapItemDef::Filename" );
    AssertTrueL( ETrue, KTxtSetIndex );

    TInt index = bitmapItemDef->Index();
    _LIT( KTxtIndex, "CAknsBitmapItemDef::Index" );
    AssertTrueL( ETrue, KTxtIndex );

    CleanupStack::PopAndDestroy( bitmapItemDef );

    //CAknsMaskedBitmapItemDef
    CAknsMaskedBitmapItemDef* mbItemDef =
        CAknsMaskedBitmapItemDef::NewL(
        KAknsIIDQgnIndiTpDialler, KTxtFilename, 1, 2 );
    CleanupStack::PushL( mbItemDef );
    _LIT( KTxtMbitmapNewL ,"CAknsMaskedBitmapItemDef::NewL" );
    AssertTrueL( ETrue, KTxtMbitmapNewL );

    CAknsMaskedBitmapItemDef* mbItemDef2 =
        CAknsMaskedBitmapItemDef::NewL( KAknsIIDQgnIndiTpDialler );
    CleanupStack::PushL( mbItemDef2 );
    _LIT( KTxtMbitmapNewL2, "CAknsMaskedBitmapItemDef::NewL2" );
    AssertTrueL( ETrue, KTxtMbitmapNewL2 );
    CleanupStack::PopAndDestroy( mbItemDef2 );

    mbItemDef->SetMaskIndex( 2 );
    _LIT( KTxtSetMaskIndex, "CAknsMaskedBitmapItemDef::SetMaskIndex" );
    AssertTrueL( ETrue, KTxtSetMaskIndex );

    TInt mIndex = mbItemDef->MaskIndex();
    _LIT( KTxtMaskIndex, "CAknsMaskedBitmapItemDef::MaskIndex" );
    AssertTrueL( ETrue, KTxtMaskIndex );

    CleanupStack::PopAndDestroy( mbItemDef );

    //CAknsColorTableItemDef
    TAknsColorTableEntry ctEntry;
    ctEntry.iIndex = 8 ;
    CAknsColorTableItemDef* ctItemDef = CAknsColorTableItemDef::NewL(
        KAknsIIDQgnIndiTpDialler,1,&ctEntry);
    CleanupStack::PushL( ctItemDef );
    _LIT( KTxtCtNewL ,"CAknsColorTableItemDef::NewL" );
    AssertTrueL( ETrue, KTxtCtNewL );

    CAknsColorTableItemDef* ctItemDef2 =
        CAknsColorTableItemDef::NewL( KAknsIIDQgnIndiTpDialler );
    CleanupStack::PushL( ctItemDef2 );
    _LIT( KTxtCtNewL2, "CAknsColorTableItemDef::NewL2" );
    AssertTrueL( ETrue, KTxtCtNewL2 );
    CleanupStack::PopAndDestroy( ctItemDef2 );

    TAknsColorTableEntry ctSetEntry;
    ctSetEntry.iIndex = 18 ;
    ctItemDef->SetColors( 1, &ctSetEntry );
    _LIT( KTxtSetColors, "CAknsColorTableItemDef::SetColors" );
    AssertTrueL( ETrue, KTxtSetColors );

    ctItemDef->SetColorsL( 1, &ctSetEntry );
    _LIT( KTxtSetColorsL, "CAknsColorTableItemDef::SetColorsL" );
    AssertTrueL( ETrue, KTxtSetColorsL );

    const TAknsColorTableEntry* colorTabEntry = ctItemDef->Colors();
    _LIT( KTxtColors, "CAknsColorTableItemDef::Colors" );
    AssertTrueL( ETrue, KTxtColors );

    TInt counter = ctItemDef->NumberOfColors();
    _LIT( KTxtNumberOfColors,
        "CAknsColorTableItemDef::NumberOfColors" );
    AssertTrueL( ETrue, KTxtNumberOfColors );

    CleanupStack::PopAndDestroy( ctItemDef );

    //CAknsImageTableItemDef
    TAknsItemID itemId;
    itemId.Set( KAknsIIDQgnPropSetAppsLoc );
    CAknsImageTableItemDef* itItemDef = CAknsImageTableItemDef::NewL(
        KAknsIIDQgnIndiTpDialler,1,&itemId);
    CleanupStack::PushL( itItemDef );
    _LIT( KTxtItNewL ,"CAknsImageTableItemDef::NewL" );
    AssertTrueL( ETrue, KTxtItNewL );

    CAknsImageTableItemDef* itItemDef2 =
        CAknsImageTableItemDef::NewL( KAknsIIDQgnIndiTpDialler );
    CleanupStack::PushL( itItemDef2 );
    _LIT( KTxtItNewL2, "CAknsImageTableItemDef::NewL2" );
    AssertTrueL( ETrue, KTxtItNewL2 );
    CleanupStack::PopAndDestroy( itItemDef2 );

    itItemDef->SetImages( 1, &itemId );
    _LIT( KTxtSetImages, "CAknsImageTableItemDef::SetImages" );
    AssertTrueL( ETrue, KTxtSetImages );

    itItemDef->SetImagesL( 1, &itemId );
    _LIT( KTxtSetImagesL, "CAknsImageTableItemDef::SetImagesL" );
    AssertTrueL( ETrue, KTxtSetImagesL );

    const TAknsItemID* imgItemID = itItemDef->Images();
    _LIT( KTxtImages, "CAknsImageTableItemDef::Images" );
    AssertTrueL( ETrue, KTxtImages );

    TInt numImage = itItemDef->NumberOfImages();
    _LIT( KTxtNumberOfImages,
        "CAknsImageTableItemDef::NumberOfImages" );
    AssertTrueL( ETrue, KTxtNumberOfImages );

    CleanupStack::PopAndDestroy( itItemDef );
    }

// ---------------------------------------------------------------------------
// CBCTestDomSkinCase::TestItemDef2L
// ---------------------------------------------------------------------------
//
void CBCTestDomSkinCase::TestItemDef2L() //AknsItemDef.h
    {
    //CAknsBmpAnimItemDef 13
    TAknsItemID itemId;
    itemId.Set( KAknsIIDQgnPropSetAppsLoc );
    TAknsBmpAnimFrameInfo frameInfo;
    frameInfo.iTime = 100;
    frameInfo.iPosX = 50;
    frameInfo.iPosY = 50;
    CAknsBmpAnimItemDef* bmpAnimDef = CAknsBmpAnimItemDef::NewL(
        KAknsIIDQgnIndiTpDialler, 1, &itemId, &frameInfo );
    CleanupStack::PushL( bmpAnimDef );
    _LIT( KTxtbmpAnimNewL ,"CAknsBmpAnimItemDef::NewL" );
    AssertTrueL( ETrue, KTxtbmpAnimNewL );

    CAknsBmpAnimItemDef* bmpAnimDef2 =
        CAknsBmpAnimItemDef::NewL( KAknsIIDQgnIndiTpDialler );
    CleanupStack::PushL( bmpAnimDef2 );
    _LIT( KTxtKTxtbmpAnimNewL2, "CAknsBmpAnimItemDef::NewL2" );
    AssertTrueL( ETrue, KTxtKTxtbmpAnimNewL2 );
    CleanupStack::PopAndDestroy( bmpAnimDef2 );

    bmpAnimDef->SetFrameInfos( &frameInfo );
    _LIT( KTxtSetFrameInfos, "CAknsBmpAnimItemDef::SetFrameInfos" );
    AssertTrueL( ETrue, KTxtSetFrameInfos );

    bmpAnimDef->SetFrameInfosL( &frameInfo );
    _LIT( KTxtSetFrameInfosL, "CAknsBmpAnimItemDef::SetFrameInfosL" );
    AssertTrueL( ETrue, KTxtSetFrameInfosL );

    const TAknsBmpAnimFrameInfo* bmpFrameInfo =
        bmpAnimDef->FrameInfos();
    _LIT( KTxtFrameInfos, "CAknsBmpAnimItemDef::FrameInfos" );
    AssertTrueL( ETrue, KTxtFrameInfos );

    bmpAnimDef->SetLastFrameBackground( ETrue );
    _LIT( KTxtSetLastFrameBackground,
        "CAknsBmpAnimItemDef::SetLastFrameBackground" );
    AssertTrueL( ETrue, KTxtSetLastFrameBackground );

    TBool lastFrame = bmpAnimDef->LastFrameBackground();
    _LIT( KTxtLastFrameBackground,
        "CAknsBmpAnimItemDef::LastFrameBackground" );
    AssertTrueL( ETrue, KTxtLastFrameBackground );

    bmpAnimDef->SetFrameInterval( 8 );
    _LIT( KTxtSetFrameInterval,
        "CAknsBmpAnimItemDef::SetFrameInterval" );
    AssertTrueL( ETrue, KTxtSetFrameInterval );

    TInt16 frameinter = bmpAnimDef->FrameInterval();
    _LIT( KTxtFrameInterval, "CAknsBmpAnimItemDef::FrameInterval" );
    AssertTrueL( ETrue, KTxtFrameInterval );

    bmpAnimDef->SetPlayMode( 1 );
    _LIT( KTxtSetPlayMode, "CAknsBmpAnimItemDef::SetPlayMode" );
    AssertTrueL( ETrue, KTxtSetPlayMode );

    TInt playMode = bmpAnimDef->PlayMode();
    _LIT( KTxtPlayMode, "CAknsBmpAnimItemDef::PlayMode" );
    AssertTrueL( ETrue, KTxtPlayMode );

    bmpAnimDef->SetFlash( EFalse );
    _LIT( KTxtSetFlash, "CAknsBmpAnimItemDef::SetFlash" );
    AssertTrueL( ETrue, KTxtSetFlash );

    TBool isFlash = bmpAnimDef->Flash();
    _LIT( KTxtFlash, "CAknsBmpAnimItemDef::Flash" );
    AssertTrueL( ETrue, KTxtFlash );

    CleanupStack::PopAndDestroy( bmpAnimDef );

    //CAknsStringItemDef 3
    CAknsStringItemDef* strItemDef = CAknsStringItemDef::NewL(
        KAknsIIDQgnIndiTpDialler ) ;
    CleanupStack::PushL( strItemDef );
    _LIT( KTxtStrNewL, "CAknsStringItemDef::NewL" );
    AssertTrueL( ETrue, KTxtStrNewL );

    _LIT( KString, "abcde" );
    strItemDef->SetStringL( KString );
    _LIT( KTxtSetStringL, "CAknsStringItemDef::SetStringL" );
    AssertTrueL( ETrue, KTxtSetStringL );

    const TDesC& string = strItemDef->String();
    _LIT( KTxtString, "CAknsStringItemDef::String" );
    AssertTrueL( ETrue, KTxtString );

    CleanupStack::PopAndDestroy( strItemDef );

    //CAknsEffectParamDef 13
    CAknsEffectParamDef* paramDef = CAknsEffectParamDef::NewL();
    CleanupStack::PushL( paramDef );
    _LIT( KTxtParamNewL, "CAknsEffectParamDef::NewL" );
    AssertTrueL( ETrue, KTxtParamNewL );

    paramDef->SetType( 1 );
    _LIT( KTxtSetType, "CAknsEffectParamDef::SetType" );
    AssertTrueL( ETrue, KTxtSetType );

    TUint32 paramType = paramDef->GetType();
    _LIT( KTxtGetType, "CAknsEffectParamDef::GetType" );
    AssertTrueL( ETrue, KTxtGetType );

    _LIT( kTxtName, "wxyz" );
    paramDef->SetNameL( kTxtName );
    _LIT( KTxtSetNameL, "CAknsEffectParamDef::SetNameL" );
    AssertTrueL( ETrue, KTxtSetNameL );

    const TDesC* paramType2 = paramDef->GetName();
    _LIT( KTxtGetName, "CAknsEffectParamDef::GetName" );
    AssertTrueL( ETrue, KTxtGetName );

    paramDef->SetValue( 1 );
    _LIT( KTxtSetValue ,"CAknsEffectParamDef::SetValue" );
    AssertTrueL( ETrue, KTxtSetValue );

    _LIT( kTxtValue, "abcd" );
    paramDef->SetValueL( kTxtValue );
    _LIT( KTxtSetValueL, "CAknsEffectParamDef::SetValueL" );
    AssertTrueL( ETrue, KTxtSetValueL );

    paramDef->SetValueL( kTxtValue, 1, 2 );
    _LIT( KTxtSetValueL2, "CAknsEffectParamDef::SetValueL2" );
    AssertTrueL( ETrue, KTxtSetValueL2 );

    TUint32 paramNumber = paramDef->GetNumber();
    _LIT( KTxtGetNumber, "CAknsEffectParamDef::GetNumber" );
    AssertTrueL( ETrue, KTxtGetNumber );

    const TDesC* paramString = paramDef->GetString();
    _LIT( KTxtGetString, "CAknsEffectParamDef::GetString" );
    AssertTrueL( ETrue, KTxtGetString );

    const TDesC* fileName = paramDef->GetFilename();
    _LIT( KTxtGetFilename, "CAknsEffectParamDef::GetFilename" );
    AssertTrueL( ETrue, KTxtGetFilename );

    TUint32 bmIndex = paramDef->GetBitmapIndex();
    _LIT( KTxtGetBitmapIndex, "CAknsEffectParamDef::GetBitmapIndex" );
    AssertTrueL( ETrue, KTxtGetBitmapIndex );

    TUint32 maskIndex = paramDef->GetMaskIndex();
    _LIT( KTxtGetMaskIndex, "CAknsEffectParamDef::GetMaskIndex" );
    AssertTrueL( ETrue, KTxtGetMaskIndex );

    CleanupStack::PopAndDestroy( paramDef );

    //CAknsEffectItemDef  7
    CAknsEffectItemDef* effItemDef = CAknsEffectItemDef::NewL();
    CleanupStack::PushL( effItemDef );
    _LIT( KTxtEfNewL, "CAknsEffectItemDef::NewL" );
    AssertTrueL( ETrue, KTxtEfNewL );

    TUid efUid = { 0x1818518 };
    effItemDef->SetEffectUid( efUid );
    _LIT( KTxtSetEffectUid, "CAknsEffectItemDef::SetEffectUid" );
    AssertTrueL( ETrue, KTxtSetEffectUid );

    TUid effectUid = effItemDef->EffectUid();
    _LIT( KTxtEffectUid, "CAknsEffectItemDef::EffectUid" );
    AssertTrueL( ETrue, KTxtEffectUid );

    CAknsEffectParamDef* efffectParDef = CAknsEffectParamDef::NewL();
    CleanupStack::PushL( efffectParDef );
    effItemDef->AddParameterL( efffectParDef );
    CleanupStack::Pop();
    _LIT( KTxtAddParameterL, "CAknsEffectItemDef::AddParameterL" );
    AssertTrueL( ETrue, KTxtAddParameterL );

    CAknsEffectParamDef* effParmDef = effItemDef->GetParameter( 0 );
    _LIT( KTxtGetParameter, "CAknsEffectItemDef::GetParameter" );
    AssertTrueL( ETrue, KTxtGetParameter );

    TInt parmCount = effItemDef->ParameterCount();
    _LIT( KTxtParameterCount, "CAknsEffectItemDef::ParameterCount" );
    AssertTrueL( ETrue, KTxtParameterCount );

    effItemDef->SetLayerIndexesAndModes( 1, 2, 3, 4, 5, 6 );
    _LIT( KTxtSetLayerIndexesAndModes,
        "CAknsEffectItemDef::SetLayerIndexesAndModes" );
    AssertTrueL( ETrue, KTxtSetLayerIndexesAndModes );

    CleanupStack::PopAndDestroy( effItemDef );

    //CAknsEffectQueueItemDef 6
    CAknsEffectQueueItemDef* effQueueDef =
        CAknsEffectQueueItemDef::NewL( KAknsIIDQgnIndiTpDialler );
    CleanupStack::PushL( effQueueDef );
    _LIT( KTxtQueueNewL, "CAknsEffectQueueItemDef::NewL" );
    AssertTrueL( ETrue, KTxtQueueNewL );


    CAknsEffectItemDef* effItemDef2 = CAknsEffectItemDef::NewL();
    CleanupStack::PushL( effItemDef2 );
    effQueueDef->AddEffectL( effItemDef2 );
    CleanupStack::Pop(effItemDef2);
    _LIT( KTxtAddEffectL, "CAknsEffectQueueItemDef::AddEffectL" );
    AssertTrueL( ETrue, KTxtAddEffectL );

    const CAknsEffectItemDef* effItemDef3 =
        effQueueDef->GetEffect( 0 );
    _LIT( KTxtGetEffect, "CAknsEffectQueueItemDef::GetEffect" );
    AssertTrueL( ETrue, KTxtGetEffect );

    TUint32 effCount = effQueueDef->EffectCount();
    _LIT( KTxtEffectCount, "CAknsEffectQueueItemDef::EffectCount" );
    AssertTrueL( ETrue, KTxtEffectCount );


    effQueueDef->SetLayerIndexesAndModes( 1, 2, 3, 4 );
    _LIT( KTxtSetIndexesAndModes,
        "CAknsEffectQueueItemDef::SetLayerIndexesAndModes" );
    AssertTrueL( ETrue, KTxtSetIndexesAndModes );

    TAknsItemID itemQueueId;
    itemQueueId.Set( KAknsIIDQgnPropSetAppsLoc );
    effQueueDef->SetReference( itemQueueId );
    _LIT( KTxtSetReference, "CAknsEffectQueueItemDef::SetReference" );
    AssertTrueL( ETrue, KTxtSetReference );

    CleanupStack::PopAndDestroy(effQueueDef);

    //CAknsSizeBoundParamDef 5
    CAknsSizeBoundParamDef* boundParamDef =
        CAknsSizeBoundParamDef::NewL();
    CleanupStack::PushL( boundParamDef );
    _LIT( KTxtBoundNewL, "CAknsSizeBoundParamDef::NewL" );
    AssertTrueL( ETrue, KTxtBoundNewL );

    _LIT( KTxtBoundName,"abcd");
    boundParamDef->SetDataL( KTxtBoundName, 1, 1 );
    _LIT( KTxtSetDataL, "CAknsSizeBoundParamDef::SetDataL" );
    AssertTrueL( ETrue, KTxtSetDataL );

    const TDesC* boundName = boundParamDef->Name();
    _LIT( KTxtSizeName, "CAknsSizeBoundParamDef::Name" );
    AssertTrueL( ETrue, KTxtSizeName );

    TUint32 boundValueId = boundParamDef->AnimationValueId();
    _LIT( KTxtAnimationValueId,
        "CAknsSizeBoundParamDef::AnimationValueId" );
    AssertTrueL( ETrue, KTxtAnimationValueId );

    TUint32 boundParamFlags = boundParamDef->ParamFlags();
    _LIT( KTxtParamFlags, "CAknsSizeBoundParamDef::ParamFlags" );
    AssertTrueL( ETrue, KTxtParamFlags );

    CleanupStack::PopAndDestroy( boundParamDef );

    //CAknsNamedReferenceDef 4
    CAknsNamedReferenceDef* nameRefDef =
        CAknsNamedReferenceDef::NewL();
    CleanupStack::PushL( nameRefDef );
    _LIT( KTxtNameNewL, "CAknsNamedReferenceDef::NewL" );
    AssertTrueL( ETrue, KTxtNameNewL );

    _LIT( KTxtNameRef,"abcd");
    nameRefDef->SetDataL( KTxtNameRef, 1 );
    _LIT( KTxtRefSetDataL, "CAknsNamedReferenceDef::SetDataL" );
    AssertTrueL( ETrue, KTxtRefSetDataL );

    const TDesC* nameRef = nameRefDef->Name();
    _LIT( KTxtrefName, "CAknsNamedReferenceDef::Name" );
    AssertTrueL( ETrue, KTxtrefName );

    TUint32 refValueId = nameRefDef->AnimationValueId();
    _LIT( KTxtRefAnimationValueId,
        "CAknsNamedReferenceDef::AnimationValueId" );
    AssertTrueL( ETrue, KTxtRefAnimationValueId );

    CleanupStack::PopAndDestroy( nameRefDef );

    //CAknsTimingModelDef 6
    CAknsTimingModelDef* timModelDef = CAknsTimingModelDef::NewL();
    CleanupStack::PushL( timModelDef );
    _LIT( KTxtModelNewL, "CAknsTimingModelDef::NewL" );
    AssertTrueL( ETrue, KTxtModelNewL );

    TUid timeUid = { 0x518 };
    timModelDef->SetTimingModelUid( timeUid );
    _LIT( KTxtSetTimingModelUid,
        "CAknsTimingModelDef::SetTimingModelUid" );
    AssertTrueL( ETrue, KTxtSetTimingModelUid );

    TUid timeUid2 = timModelDef->TimingModelUid();
    _LIT( KTxtTimingModelUid,
        "CAknsTimingModelDef::TimingModelUid" );
    AssertTrueL( ETrue, KTxtTimingModelUid );

    CAknsEffectParamDef* effParmDef3 = CAknsEffectParamDef::NewL();
    CleanupStack::PushL( effParmDef3 );
    timModelDef->AddParameterL( effParmDef3 );
    CleanupStack::Pop( effParmDef3 );
    _LIT( KTxtTimeAddParameterL,
        "CAknsTimingModelDef::AddParameterL" );
    AssertTrueL( ETrue, KTxtTimeAddParameterL );

    CAknsEffectParamDef* effParmDef2 = timModelDef->Parameter( 0 );
    _LIT( KTxtTimeParameter, "CAknsTimingModelDef::Parameter" );
    AssertTrueL( ETrue, KTxtTimeParameter );

    TInt paramCount = timModelDef->ParameterCount();
    _LIT( KTxtTimeParameterCount,
        "CAknsTimingModelDef::ParameterCount" );
    AssertTrueL( ETrue, KTxtTimeParameterCount );

    CleanupStack::PopAndDestroy( timModelDef );

    //CAknsAnimationValueDef 8
    CAknsAnimationValueDef* aniValueDef =
        CAknsAnimationValueDef::NewL();
    CleanupStack::PushL( aniValueDef );
    _LIT( KTxtaniNewL, "CAknsAnimationValueDef::NewL" );
    AssertTrueL( ETrue, KTxtaniNewL );

    TUid aniUid = { 0x519 };
    aniValueDef->SetAnimationValueUid( aniUid );
    _LIT( KTxtSetAnimationValueUid,
        "CAknsAnimationValueDef::SetAnimationValueUid" );
    AssertTrueL( ETrue, KTxtSetAnimationValueUid );

    TUid aniUid2 = aniValueDef->AnimationValueUid();
    _LIT( KTxtAnimationValueUid,
        "CAknsAnimationValueDef::AnimationValueUid" );
    AssertTrueL( ETrue, KTxtAnimationValueUid );

    aniValueDef->SetTimingModelId( 1 );
    _LIT( KTxtSetTimingModelId,
        "CAknsAnimationValueDef::SetTimingModelId" );
    AssertTrueL( ETrue, KTxtSetTimingModelId );

    TUint32  aniModelId = aniValueDef->TimingModelId();
    _LIT( KTxtTimingModelId,
        "CAknsAnimationValueDef::TimingModelId" );
    AssertTrueL( ETrue, KTxtTimingModelId );

    CAknsEffectParamDef* aniParmDef = CAknsEffectParamDef::NewL();
    CleanupStack::PushL(aniParmDef);
    aniValueDef->AddParameterL( aniParmDef );
    CleanupStack::Pop( aniParmDef );
    _LIT( KTxtAniAddParameterL,
        "CAknsAnimationValueDef::AddParameterL" );
    AssertTrueL( ETrue, KTxtAniAddParameterL );

    CAknsEffectParamDef* aniParmDef2 = aniValueDef->Parameter( 0 );
    _LIT( KTxtAniParameter,
        "CAknsAnimationValueDef::Parameter" );
    AssertTrueL( ETrue, KTxtAniParameter );

    TInt aniParmCount = aniValueDef->ParameterCount();
    _LIT( KTxtAniParameterCount,
        "CAknsAnimationValueDef::ParameterCount" );
    AssertTrueL( ETrue, KTxtAniParameterCount );


    CleanupStack::PopAndDestroy( aniValueDef );

    //CAknsAnimationCommandItemDef 4
    CAknsAnimationCommandItemDef* aniCmdDef =
        CAknsAnimationCommandItemDef::NewL();
    CleanupStack::PushL( aniCmdDef );
    _LIT( KTxtaniCmdNewL, "CAknsAnimationCommandItemDef::NewL" );
    AssertTrueL( ETrue, KTxtaniCmdNewL );

    CAknsNamedReferenceDef* namedRefDef =
        CAknsNamedReferenceDef::NewL();
    CleanupStack::PushL( namedRefDef );
    aniCmdDef->AddNamedReferenceL( namedRefDef );
    CleanupStack::Pop( namedRefDef );
    _LIT( KTxtAddNamedReferenceL,
        "CAknsAnimationCommandItemDef::AddNamedReferenceL" );
    AssertTrueL( ETrue, KTxtAddNamedReferenceL );

    CAknsNamedReferenceDef* nameRefDef2 =
        aniCmdDef->NamedReference( 0 );
    _LIT( KTxtNamedReference,
        "CAknsAnimationCommandItemDef::NamedReference" );
    AssertTrueL( ETrue, KTxtNamedReference );

    TInt namedRefCount = aniCmdDef->NamedReferenceCount();
    _LIT( KTxtNamedReferenceCount,
        "CAknsAnimationCommandItemDef::NamedReferenceCount" );
    AssertTrueL( ETrue, KTxtNamedReferenceCount );


    CleanupStack::PopAndDestroy( aniCmdDef );

    //CAknsAnimationItemDef 21
    CAknsAnimationItemDef* aniItemDef =
        CAknsAnimationItemDef::NewL( KAknsIIDQgnIndiTpDialler );
    CleanupStack::PushL( aniItemDef );
    _LIT( KTxtAniItemNewL, "CAknsAnimationItemDef::NewL" );
    AssertTrueL( ETrue, KTxtAniItemNewL );

    aniItemDef->SetLayerIndexesAndModes( 1, 2, 3, 4 );
    _LIT( KTxtAniItemSetLayerModes,
        "CAknsAnimationItemDef::SetLayerIndexesAndModes" );
    AssertTrueL( ETrue, KTxtAniItemSetLayerModes );

    aniItemDef->SetMinInterval( 8 );
    _LIT( KTxtAniItemSetMinInterval,
        "CAknsAnimationItemDef::SetMinInterval" );
    AssertTrueL( ETrue, KTxtAniItemSetMinInterval );

    TUint32 aniMiniInterval = aniItemDef->MinInterval();
    _LIT( KTxtAniItemMinInterval,
        "CAknsAnimationItemDef::MinInterval" );
    AssertTrueL( ETrue, KTxtAniItemMinInterval );

    aniItemDef->SetMorphing( ETrue );
    _LIT( KTxtSetMorphing, "CAknsAnimationItemDef::SetMorphing" );
    AssertTrueL( ETrue, KTxtSetMorphing );

    TBool morphing = aniItemDef->Morphing();
    _LIT( KTxtMorphing, "CAknsAnimationItemDef::Morphing" );
    AssertTrueL( ETrue, KTxtMorphing );

    CAknsEffectItemDef* aniItemEffItemDef =
        CAknsEffectItemDef::NewL();
    CleanupStack::PushL( aniItemEffItemDef );
    aniItemDef->AddPreprocessCommandL( aniItemEffItemDef );
    CleanupStack::Pop( aniItemEffItemDef );
    _LIT( KTxtAddPreprocessCommandL,
        "CAknsAnimationItemDef::AddPreprocessCommandL" );
    AssertTrueL( ETrue, KTxtAddPreprocessCommandL );

    CAknsEffectItemDef* aniItemEffItemDef2 =
        aniItemDef->PreprocessCommand( 0 );
    _LIT( KTxtPreprocessCommand,
        "CAknsAnimationItemDef::PreprocessCommand" );
    AssertTrueL( ETrue, KTxtPreprocessCommand );

    TInt prepCmdCount = aniItemDef->PreprocessCommandCount();
    _LIT( KTxtPreprocessCommandCount,
        "CAknsAnimationItemDef::PreprocessCommandCount" );
    AssertTrueL( ETrue, KTxtPreprocessCommandCount );

    CAknsAnimationCommandItemDef* aniCommandDef =
        CAknsAnimationCommandItemDef::NewL();
    CleanupStack::PushL( aniCommandDef );
    aniItemDef->AddAnimationCommandItemL( aniCommandDef );
    CleanupStack::Pop( aniCommandDef );
    _LIT( KTxtAddAnimationCommandItemL,
        "CAknsAnimationItemDef::AddAnimationCommandItemL" );
    AssertTrueL( ETrue, KTxtAddAnimationCommandItemL );

    CAknsAnimationCommandItemDef* aniCommandDef2 =
        aniItemDef->AnimationCommandItem( 0 );
    _LIT( KTxtAnimationCommandItem,
        "CAknsAnimationItemDef::AnimationCommandItem" );
    AssertTrueL( ETrue, KTxtAnimationCommandItem );

    TInt aniCmdItemCount = aniItemDef->AnimationCommandItemCount();
    _LIT( KTxtAnimationCommandItemCount,
        "CAknsAnimationItemDef::AnimationCommandItemCount" );
    AssertTrueL( ETrue, KTxtAnimationCommandItemCount );

    CAknsAnimationValueDef* animationValueDef =
        CAknsAnimationValueDef::NewL();
    CleanupStack::PushL( animationValueDef );
    aniItemDef->AddAnimationValueL( animationValueDef );
    CleanupStack::Pop( animationValueDef );
    _LIT( KTxtAAddAnimationValueL,
        "CAknsAnimationItemDef::AddAnimationValueL" );
    AssertTrueL( ETrue, KTxtAAddAnimationValueL );

    CAknsAnimationValueDef* aniValueDef2 =
        aniItemDef->AnimationValue( 0 );
    _LIT( KTxtAnimationValue,
        "CAknsAnimationItemDef::AnimationValue" );
    AssertTrueL( ETrue, KTxtAnimationValue );

    TInt aniValueCount = aniItemDef->AnimationValueCount();
    _LIT( KTxtAnimationValueCount,
        "CAknsAnimationItemDef::AnimationValueCount" );
    AssertTrueL( ETrue, KTxtAnimationValueCount );

    CAknsTimingModelDef* aniTimingModeDef =
        CAknsTimingModelDef::NewL();
    CleanupStack::PushL( aniTimingModeDef );
    aniItemDef->AddTimingModelL( aniTimingModeDef );
    CleanupStack::Pop( aniTimingModeDef );
    _LIT( KTxtAddTimingModelL,
        "CAknsAnimationItemDef::AddTimingModelL" );
    AssertTrueL( ETrue, KTxtAddTimingModelL );

    CAknsTimingModelDef* aniTimingModeDef2 =
        aniItemDef->TimingModel( 0 );
    _LIT( KTxtTimingModel,
        "CAknsAnimationItemDef::TimingModel" );
    AssertTrueL( ETrue, KTxtTimingModel );

    TInt aniTimingModelCount = aniItemDef->TimingModelCount();
    _LIT( KTxtTimingModelCount,
        "CAknsAnimationItemDef::TimingModelCount" );
    AssertTrueL( ETrue, KTxtTimingModelCount );

    CAknsSizeBoundParamDef* aniSizeBoundDef =
        CAknsSizeBoundParamDef::NewL();
    CleanupStack::PushL( aniSizeBoundDef );
    aniItemDef->AddSizeBoundParamL( aniSizeBoundDef );
    CleanupStack::Pop( aniSizeBoundDef );
    _LIT( KTxtAddSizeBoundParamL,
        "CAknsAnimationItemDef::AddSizeBoundParamL" );
    AssertTrueL( ETrue, KTxtAddSizeBoundParamL );

    CAknsSizeBoundParamDef* aniSizeBoundDef2 =
        aniItemDef->SizeBoundParam( 0 );
    _LIT( KTxtSizeBoundParam,
        "CAknsAnimationItemDef::SizeBoundParam" );
    AssertTrueL( ETrue, KTxtSizeBoundParam );

    TInt aniSizeBoundCount = aniItemDef->SizeBoundParamCount();
    _LIT( KTxtSizeBoundParamCount,
        "CAknsAnimationItemDef::SizeBoundParamCount" );
    AssertTrueL( ETrue, KTxtSizeBoundParamCount );


    CleanupStack::PopAndDestroy( aniItemDef );
    }

// ---------------------------------------------------------------------------
// CBCTestDomSkinCase::TestPkgIDL
// ---------------------------------------------------------------------------
//
void CBCTestDomSkinCase::TestPkgIDL()//AknsPkgID.h 3
    {
    TAknsPkgID pgkId;
    _LIT( KTxtContent, "123456" );
    pgkId.SetFromDesL( KTxtContent );
    _LIT( KTxtSetFromDesL, "TAknsPkgID::SetFromDesL" );
    AssertTrueL( ETrue, KTxtSetFromDesL );

    TBuf<32> targetContext;
    pgkId.CopyToDes( targetContext );
    _LIT( KTxtCopyToDes, "TAknsPkgID::CopyToDes" );
    AssertTrueL( ETrue, KTxtCopyToDes );

    //specially handle this,because  this API need very long time
    RAknsSrvSession srvSession;
    CleanupClosePushL( srvSession );
    User::LeaveIfError( srvSession.Connect() );

    CDesCArray* array = new (ELeave) CDesC16ArrayFlat( 5 );
    CleanupStack::PushL( array );
    _LIT( KTxtAaa, "aaaa.bmp" );
    array->AppendL( KTxtAaa );
    _LIT( KTxtBbb, "bbbb.bmp" );
    array->AppendL( KTxtBbb );

    TInt ret = srvSession.SetSlideSetWallpaper( *array );
    _LIT( KTxtSetSlideSetWallpaper,
        "RAknsSrvSession::SetSlideSetWallpaper" );
    AssertTrueL( ETrue, KTxtSetSlideSetWallpaper );

    CleanupStack::PopAndDestroy( array );
    CleanupStack::Pop(); // Pop srvSession
    srvSession.Close();
    }

// ---------------------------------------------------------------------------
// CBCTestDomSkinCase::TestPointerStoreL
// ---------------------------------------------------------------------------
//
void CBCTestDomSkinCase::TestPointerStoreL()//AknsPointerStore.h 3
    {
    TInt pointerKey( 1 );
    TInt pointerValue( 2 );
    AknsPointerStore::StorePointerL( &pointerKey, &pointerValue );
    _LIT( KTxtStorePointerL, "AknsPointerStore::StorePointerL" );
    AssertTrueL( ETrue, KTxtStorePointerL );

    TAny* pointer = AknsPointerStore::RetrievePointer( &pointerKey );
    _LIT( KTxtRetrievePointer, "AknsPointerStore::RetrievePointer" );
    AssertTrueL( ETrue, KTxtRetrievePointer );

    AknsPointerStore::RemovePointer( &pointerKey );
    _LIT( KTxtRemovePointer, "AknsPointerStore::RemovePointer" );
    AssertTrueL( ETrue, KTxtRemovePointer );
    }

// ---------------------------------------------------------------------------
// CBCTestDomSkinCase::TestRendererWrapperL
// ---------------------------------------------------------------------------
//
void CBCTestDomSkinCase::TestRendererWrapperL() //AknsRendererWrapper.h 1
    {
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();

    CFbsBitmap* OutRGB = NULL;
    CFbsBitmap* OutAlpha = NULL;
    TRect rect( TPoint( 5, 5 ), TSize( 50, 20 ) );
    CleanupStack::PushL( OutRGB );
    CleanupStack::PushL( OutAlpha );
    AknsRendererWrapper::RenderScalableItemL(
        skin, KAknsIIDQsnBgScreen, OutRGB, OutAlpha, rect, NULL, NULL );
    _LIT( KTxtRenderScalableItemL,
        "AknsRendererWrapper::RenderScalableItemL" );
    AssertTrueL( ETrue, KTxtRenderScalableItemL );
    CleanupStack::Pop();
    delete OutAlpha;
    CleanupStack::Pop();
    delete OutRGB;
    }

// ---------------------------------------------------------------------------
// CBCTestDomSkinCase::TestSrvChunkLookupL
// ---------------------------------------------------------------------------
//
void CBCTestDomSkinCase::TestSrvChunkLookupL()//AknsSrvChunkLookup.h
    {
    RAknsSrvSession srvSession;
    CleanupClosePushL( srvSession );
    User::LeaveIfError( srvSession.Connect() );
    CAknsSrvChunkLookup* srvChunkLookup =
        srvSession.CreateChunkLookupL();
    CleanupStack::PushL( srvChunkLookup );

    TInt morphing( 0 );
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* maskBitmap = NULL;
    CleanupStack::PushL( bitmap );
    CleanupStack::PushL( maskBitmap );
    srvChunkLookup->LookupAndCreateScalableItemL(
        KAknsIIDQgnIndiTpDialler, 1, TSize( 50, 50 ),
        bitmap, maskBitmap, morphing );
    _LIT( KTxtLookupAndCreateScalableItemL,
        "CAknsSrvChunkLookup::LookupAndCreateScalableItemL" );
    AssertTrueL( ETrue, KTxtLookupAndCreateScalableItemL );
    CleanupStack::Pop(); // Pop maskBitmap
    delete maskBitmap;
    CleanupStack::Pop(); // Pop bitmap
    delete bitmap;

    CAknsItemDef* itemDef = NULL;
    itemDef = srvChunkLookup->LookupAndCreateDefL(
        KAknsIIDQgnIndiTpDialler );
    CleanupStack::PushL( itemDef );
    _LIT( KTxtLookupAndCreateDefL,
        "CAknsSrvChunkLookup::LookupAndCreateDefL" );
    AssertTrueL( ETrue, KTxtLookupAndCreateDefL );

    srvChunkLookup->BeginRender();
    _LIT( KTxtBeginRender, "CAknsSrvChunkLookup::BeginRender" );
    AssertTrueL( ETrue, KTxtBeginRender );

    srvChunkLookup->EndRender();
    _LIT( KTxtEndRender, "CAknsSrvChunkLookup::EndRender" );
    AssertTrueL( ETrue, KTxtEndRender );

    CleanupStack::PopAndDestroy( itemDef );
    CleanupStack::PopAndDestroy( srvChunkLookup );
    CleanupStack::Pop();// Pop srvSession
    srvSession.Close();
    }

// ---------------------------------------------------------------------------
// CBCTestDomSkinCase::TestSrvClientL
// ---------------------------------------------------------------------------
//
void CBCTestDomSkinCase::TestSrvClientL()//AknsSrvClient.h 25
    {
    RAknsSrvSession srvSession;
    CleanupClosePushL( srvSession );
    _LIT( KTxtRAknsSrvSession, "RAknsSrvSession::RAknsSrvSession" );
    AssertTrueL( ETrue, KTxtRAknsSrvSession );

    TInt ret;
    User::LeaveIfError( srvSession.Connect() );
    _LIT( KTxtConnect, "RAknsSrvSession::Connect" );
    AssertTrueL( ETrue, KTxtConnect );

    srvSession.EnableSkinChangeNotify();
    _LIT( KTxtEnableSkinChangeNotify,
        "RAknsSrvSession::EnableSkinChangeNotify" );
    AssertTrueL( ETrue, KTxtEnableSkinChangeNotify );

    srvSession.ClientError( 0 );
    _LIT( KTxtClientError,
        "RAknsSrvSession::ClientError" );
    AssertTrueL( ETrue, KTxtClientError );

    ret = srvSession.SetAllDefinitionSets( KAknsPIDS60DefaultSkin ); 
    _LIT( KTxtSetAllDefinitionSets,
        "RAknsSrvSession::SetAllDefinitionSets" );
    AssertTrueL( ETrue, KTxtSetAllDefinitionSets );

    CArrayPtr<CAknsSrvSkinInformationPkg>* skinInfoPgks =
        srvSession.EnumerateSkinPackagesL();
    CleanupStack::PushL( skinInfoPgks );
    _LIT( KTxtEnumerateSkinPackagesL,
        "RAknsSrvSession::EnumerateSkinPackagesL" );
    AssertTrueL( ETrue, KTxtEnumerateSkinPackagesL );

    CAknsSrvChunkLookup* srvChunkLookup =
        srvSession.CreateChunkLookupL();
    CleanupStack::PushL( srvChunkLookup );
    _LIT( KTxtCreateChunkLookupL,
        "RAknsSrvSession::CreateChunkLookupL" );
    AssertTrueL( ETrue, KTxtCreateChunkLookupL );

    _LIT( KTxtFilename, "\\resource\\apps\\aaaa.mbm" );
    ret = srvSession.SetIdleWallpaper(KTxtFilename);
    _LIT( KTxtSetIdleWallpaper,
        "RAknsSrvSession::SetIdleWallpaper" );
    AssertTrueL( ETrue, KTxtSetIdleWallpaper );

    TSize scalableSize( 20, 20 );
    CFbsBitmap* bitmap = new ( ELeave ) CFbsBitmap();
    CleanupStack::PushL( bitmap );
    ret = srvSession.StoreScalableGraphics(
        KAknsIIDQgnIndiTpDialler, 1, scalableSize, bitmap, NULL );
    _LIT( KTxtStoreScalableGraphics,
        "RAknsSrvSession::StoreScalableGraphics" );
    AssertTrueL( ETrue, KTxtStoreScalableGraphics );

    ret = srvSession.CopySkin( KAknsPIDSkin6,
        EAknsSrvPhone, EAknsSrvMMC );
    _LIT( KTxtCopySkin,
        "RAknsSrvSession::CopySkin" );
    AssertTrueL( ETrue, KTxtCopySkin );

    TInt fileHandle( 0 );
    ret = srvSession.OpenBitmapFile( KTxtFilename, fileHandle );
    _LIT( KTxtOpenBitmapFile,
        "RAknsSrvSession::OpenBitmapFile" );
    AssertTrueL( ETrue, KTxtOpenBitmapFile );

    ret = srvSession.OpenInifile( KAknsPIDSkin6,
        EAknsSrvPhone, fileHandle, EFalse );
    _LIT( KTxtOpenInifile,
        "RAknsSrvSession::OpenInifile" );
    AssertTrueL( ETrue, KTxtOpenInifile );


    _LIT(KTxtSource,"abcd");
    _LIT(KTxtTarget,"efgh");
    ret = srvSession.CopySoundFile( KTxtSource, KTxtTarget );
    _LIT( KTxtCopySoundFile,
        "RAknsSrvSession::CopySoundFile" );
    AssertTrueL( ETrue, KTxtCopySoundFile );

    //
    TSize wallSize(-1,-1);
    CFbsBitmap* wallBitmap = NULL;
    CFbsBitmap* wallmaskBitmap = NULL;
    _LIT( KTxtDecodeFinename, "aaaa.svg" );
    CleanupStack::PushL( wallBitmap );
    CleanupStack::PushL( wallmaskBitmap );
    srvSession.DecodeWallpaperImageL( KTxtDecodeFinename,
        wallSize, wallBitmap, wallmaskBitmap );
    _LIT( KTxtDecodeWallpaperImageL,
        "RAknsSrvSession::DecodeWallpaperImageL" );
    AssertTrueL( ETrue, KTxtDecodeWallpaperImageL );
    CleanupStack::Pop();// Pop wallmaskBitmap;
    delete wallmaskBitmap;
    CleanupStack::Pop();// Pop wallBitmap;
    delete wallBitmap;

    TInt imageFileHandle( 0 );
    ret = srvSession.OpenImageInifile(
        EAknsSrvInifileSSWP, imageFileHandle );
    _LIT( KTxtOpenImageInifile,
        "RAknsSrvSession::OpenImageInifile" );
    AssertTrueL( ETrue, KTxtOpenImageInifile );
    //release file handle
    RFile imageFile;
    imageFile.AdoptFromServer( ret, imageFileHandle );
    imageFile.Close();

    srvSession.FreeUnnecessaryLayoutBitmaps( EAknsSrcScrModeNone );
    _LIT( KTxtFreeUnnecessaryLayoutBitmaps,
        "RAknsSrvSession::FreeUnnecessaryLayoutBitmaps" );
    AssertTrueL( ETrue, KTxtFreeUnnecessaryLayoutBitmaps );

    ret = srvSession.DeleteSkin( KAknsPIDSkin6, EAknsSrvPhone );
    _LIT( KTxtDeleteSkin,
        "RAknsSrvSession::DeleteSkin" );
    AssertTrueL( ETrue, KTxtDeleteSkin );

    ret = srvSession.ClearScalableGraphics();
    _LIT( KTxtClearScalableGraphics,
        "RAknsSrvSession::ClearScalableGraphics" );
    AssertTrueL( ETrue, KTxtClearScalableGraphics );

    srvSession.DisableSkinChangeNotify();
    _LIT( KTxtDisableSkinChangeNotify,
        "RAknsSrvSession::DisableSkinChangeNotify" );
    AssertTrueL( ETrue, KTxtDisableSkinChangeNotify );

    TInt skinCount = skinInfoPgks->Count();
    for ( TInt i=0; i < skinCount; i++)
        delete ( *skinInfoPgks )[i];

    CleanupStack::PopAndDestroy ( bitmap );
    CleanupStack::PopAndDestroy( srvChunkLookup );
    CleanupStack::PopAndDestroy( skinInfoPgks );

    CleanupStack::Pop(); // Pop srvSession
    srvSession.Close();
    _LIT( KTxtClose, "RAknsSrvSession::Close" );
    AssertTrueL( ETrue, KTxtClose );
    }

// ---------------------------------------------------------------------------
// CBCTestDomSkinCase::TestSrvSkinInformationPkgL
// ---------------------------------------------------------------------------
//
void CBCTestDomSkinCase::TestSrvSkinInformationPkgL() //AknsSrvSkinInformationPkg.h 15
    {
    RAknsSrvSession srvSession;
    CleanupClosePushL( srvSession );
    User::LeaveIfError( srvSession.Connect() );
    CArrayPtr<CAknsSrvSkinInformationPkg>* skinInfoPgks =
        srvSession.EnumerateSkinPackagesL();
    CleanupStack::PushL( skinInfoPgks );

    CAknsSrvSkinInformationPkg* srvSkinInfoPgk =
        ( *skinInfoPgks )[0];

    TAknsPkgID pkgId = srvSkinInfoPgk->PID();
    _LIT( KTxtPID, "RAknsSrvSession::PID" );
    AssertTrueL( ETrue, KTxtPID );

    TDesC& direct = srvSkinInfoPgk->Directory();
    _LIT( KTxtDirectory, "RAknsSrvSession::Directory" );
    AssertTrueL( ETrue, KTxtDirectory );

    TDesC& iniFileDirect = srvSkinInfoPgk->IniFileDirectory();
    _LIT( KTxtIniFileDirectory,
        "RAknsSrvSession::IniFileDirectory" );
    AssertTrueL( ETrue, KTxtIniFileDirectory );

    TDesC& skinName = srvSkinInfoPgk->Name();
    _LIT( KTxtName, "RAknsSrvSession::Name" );
    AssertTrueL( ETrue, KTxtName );

    TDesC& idleStateWall =
        srvSkinInfoPgk->IdleStateWallPaperImageFileName();
    _LIT( KTxtIdleStateWallPaperImageFileName,
        "RAknsSrvSession::IdleStateWallPaperImageFileName" );
    AssertTrueL( ETrue, KTxtIdleStateWallPaperImageFileName );

    TDesC& pinboarWallPaper =
        srvSkinInfoPgk->PinboarWallPaperImageFileName();
    _LIT( KTxtPinboarWallPaperImageFileName,
        "RAknsSrvSession::PinboarWallPaperImageFileName" );
    AssertTrueL( ETrue, KTxtPinboarWallPaperImageFileName );

    TInt ret = srvSkinInfoPgk->IdleStateWallPaperImageIndex();
    _LIT( KTxtIdleStateWallPaperImageIndex,
        "RAknsSrvSession::IdleStateWallPaperImageIndex" );
    AssertTrueL( ETrue, KTxtIdleStateWallPaperImageIndex );

    ret = srvSkinInfoPgk->PinboardWallPaperImageIndex();
    _LIT( KTxtPinboardWallPaperImageIndex,
        "RAknsSrvSession::PinboardWallPaperImageIndex" );
    AssertTrueL( ETrue, KTxtPinboardWallPaperImageIndex );

    TBool isDel = srvSkinInfoPgk->IsDeletable();
    _LIT( KTxtIsDeletable, "RAknsSrvSession::IsDeletable" );
    AssertTrueL( ETrue, KTxtIsDeletable );

    TBool isCopy = srvSkinInfoPgk->IsCopyable();
    _LIT( KTxtIsCopyable, "RAknsSrvSession::IsCopyable" );
    AssertTrueL( ETrue, KTxtIsCopyable );

    TAknsPkgID colorPid = srvSkinInfoPgk->ColorSchemePID();
    _LIT( KTxtColorSchemePID, "RAknsSrvSession::ColorSchemePID" );
    AssertTrueL( ETrue, KTxtColorSchemePID );

    TBool hasIconset = srvSkinInfoPgk->HasIconset();
    _LIT( KTxtHasIconset, "RAknsSrvSession::HasIconset" );
    AssertTrueL( ETrue, KTxtHasIconset );

    TAknsSkinSrvSkinProtectionType protectType =
        srvSkinInfoPgk->ProtectionType();
    _LIT( KTxtProtectionType, "RAknsSrvSession::ProtectionType" );
    AssertTrueL( ETrue, KTxtProtectionType );

    TBool isCorrupt = srvSkinInfoPgk->IsCorrupted();
    _LIT( KTxtIsCorrupted, "RAknsSrvSession::IsCorrupted" );
    AssertTrueL( ETrue, KTxtIsCorrupted );

    TDesC& fullName = srvSkinInfoPgk->FullName();
    _LIT( KTxtFullName, "RAknsSrvSession::FullName" );
    AssertTrueL( ETrue, KTxtFullName );

    TInt skinCount = skinInfoPgks->Count();
    for ( TInt i=0; i < skinCount; i++ )
        delete ( *skinInfoPgks )[i];

    CleanupStack::PopAndDestroy( skinInfoPgks );
    CleanupStack::Pop(); // Pop srvSession
    srvSession.Close();
    }
