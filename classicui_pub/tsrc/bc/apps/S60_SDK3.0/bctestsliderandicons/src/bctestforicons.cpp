/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         test case
*
*/









#include <w32std.h>
#include <coecntrl.h>
#include <akniconsrvclient.h>
#include <avkon.mbg>
#include <akniconutils.h>
#include <fbs.h>
#include <akniconobserver.h>
#include <eikenv.h>

#include "bctestforicons.h"
#include "bctestsliderandiconscontainer.h"
#include "bctestsliderandicons.hrh"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestForIcons* CBCTestForIcons::NewL(
    CBCTestSliderAndIconsContainer* aContainer )
    {
    CBCTestForIcons* self = new( ELeave ) CBCTestForIcons(
        aContainer );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestForIcons::CBCTestForIcons(
    CBCTestSliderAndIconsContainer* aContainer )
    : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestForIcons::~CBCTestForIcons()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestForIcons::ConstructL()
    {
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCTestForIcons::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestForIcons::BuildScriptL()
    {
    // Add script as your need.
    AddTestL( LeftCBA, Down, KeyOK, TEND );
    }

// ---------------------------------------------------------------------------
// CBCTestForIcons::RunL
// ---------------------------------------------------------------------------
//
void CBCTestForIcons::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdEmptyOutline || aCmd > EBCTestCmdMaxOutline )
        {
        return;
        }
    switch ( aCmd )
        {
        case EBCTestIcons:
            TestIconsL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestForIcons::TestAknIconUtils
// ---------------------------------------------------------------------------
//
void CBCTestForIcons::TestAknIconUtilsL()
    {
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;
    AknIconUtils::CreateIconL( bitmap, mask,
        AknIconUtils::AvkonIconFileName(), EMbmAvkonQgn_graf_tab_21,
        EMbmAvkonQgn_graf_tab_21_mask );
    _LIT( KCreateIconL1, "CreateIconL 5 test" );
    AssertTrueL( ETrue, KCreateIconL1 );
    delete bitmap;
    delete mask;

    AknIconUtils::CreateIconLC( bitmap, mask,
        AknIconUtils::AvkonIconFileName(), EMbmAvkonQgn_graf_tab_21,
        EMbmAvkonQgn_graf_tab_21_mask );
    _LIT( KCreateIconLC, "CreateIconLC test" );
    AssertTrueL( ETrue, KCreateIconLC );
    CleanupStack::PopAndDestroy( 2 );

    CFbsBitmap* fbsBitmap = AknIconUtils::CreateIconL(
        AknIconUtils::AvkonIconFileName(), EMbmAvkonQgn_graf_tab_21 );
    _LIT( KCreateIconL2, "CreateIconL 2 test" );
    AssertTrueL( ETrue, KCreateIconL2 );
    delete fbsBitmap;

    CBCTestFileProvider* provider = new( ELeave ) CBCTestFileProvider();
    CleanupStack::PushL( provider );

    AknIconUtils::CreateIconL( bitmap, mask, *provider,
        EMbmAvkonQgn_graf_tab_21, EMbmAvkonQgn_graf_tab_21_mask );
    _LIT( KCreateIconL3, "CreateIconL with provider test" );
    AssertTrueL( ETrue, KCreateIconL3 );
    delete bitmap;
    delete mask;

    AknIconUtils::CreateIconLC( bitmap, mask, *provider,
        EMbmAvkonQgn_graf_tab_21, EMbmAvkonQgn_graf_tab_21_mask );
    _LIT( KCreateIconLC2, "CreateIconLC with provider test" );
    AssertTrueL( ETrue, KCreateIconLC2 );
    //CleanupStack::PopAndDestroy( 2 );

    CFbsBitmap* createIcon4 = AknIconUtils::CreateIconL( *provider,
        EMbmAvkonQgn_graf_tab_21 );
    _LIT( KCreateIconL4, "CreateIconL4 with provider test" );
    AssertTrueL( ETrue, KCreateIconL4 );
    delete createIcon4;



    AknIconUtils::PreserveIconData( bitmap );
    _LIT( KPreserveIconData, "PreserveIconData test" );
    AssertTrueL( ETrue, KPreserveIconData );

    AknIconUtils::DestroyIconData( bitmap );
    _LIT( KDestroyIconData, "DestroyIconData test" );
    AssertTrueL( ETrue, KDestroyIconData );

    TSize size = iContainer->Rect().Size();
    TInt setSize = AknIconUtils::SetSize( bitmap, size,
        EAspectRatioPreserved );
    _LIT( KSetSize, "SetSize test" );
    AssertTrueL( ETrue, KSetSize );

    TInt angle = 30;
    TInt setSizeAndRotation = AknIconUtils::SetSizeAndRotation( bitmap,
        size, EAspectRatioPreserved,  angle );
    _LIT( KSetSizeAndRotation, "SetSizeAndRotation test" );
    AssertTrueL( ETrue, KSetSizeAndRotation );

    CBCTestIconObserver* iconObserver =
        new( ELeave )CBCTestIconObserver();
    CleanupStack::PushL( iconObserver );
    AknIconUtils::SetObserver( bitmap, iconObserver );
    _LIT( KSetObserver, "SetObserver test" );
    AssertTrueL( ETrue, KSetObserver );
    CleanupStack::PopAndDestroy( iconObserver );

    TDesC fileName = AknIconUtils::AvkonIconFileName();
    _LIT( KAvkonIconFileName, "AvkonIconFileName test" );
    AssertTrueL( ETrue, KAvkonIconFileName );

    TInt bitmapId = EMbmAvkonQgn_graf_tab_21;
    TInt maskId = EMbmAvkonQgn_graf_tab_21_mask;
    AknIconUtils::ValidateLogicalAppIconId( fileName, bitmapId, maskId );
    _LIT( KValidateLogicalAppIconId, "ValidateLogicalAppIconId test" );
    AssertTrueL( ETrue, KValidateLogicalAppIconId );

    TBool isMifFile = AknIconUtils::IsMifFile( fileName );
    _LIT( KIsMifFile, "IsMifFile test" );
    AssertTrueL( ETrue, KIsMifFile );

    TBool isMifIcon = AknIconUtils::IsMifIcon( bitmap );
    _LIT( KIsMifIcon, "IsMifIcon test" );
    AssertTrueL( ETrue, KIsMifIcon );

    CFbsBitmap *bitmapForDms = new( ELeave ) CFbsBitmap();
    CleanupStack::PushL( bitmapForDms );
    bitmapForDms->Create( size, ENone );

    TInt dimensions1 = AknIconUtils::GetContentDimensions(
        bitmapForDms, size );
    _LIT( KGetContentDimensions1, "GetContentDimensions1 test" );
    AssertTrueL( ETrue, KGetContentDimensions1 );

    TAknContentDimensions contentDimensions;
    TInt dimensions2 = AknIconUtils::GetContentDimensions(
        bitmapForDms, contentDimensions );
    _LIT( KGetContentDimensions2, "GetContentDimensions2 test" );
    AssertTrueL( ETrue, KGetContentDimensions2 );
    CleanupStack::PopAndDestroy( bitmapForDms );

    CAknIcon* sourceIcon = CAknIcon::NewL();
    CleanupStack::PushL( sourceIcon );

    CFbsBitmap* fbsBitmap2 = NULL;
    CFbsBitmap* fbsBitmapMask2 = NULL;
    AknIconUtils::CreateIconL( fbsBitmap2, fbsBitmapMask2,
        AknIconUtils::AvkonIconFileName(), EMbmAvkonQgn_graf_tab_21,
        EMbmAvkonQgn_graf_tab_21_mask );
    sourceIcon->SetBitmap( fbsBitmap2 );
    sourceIcon->SetMask( fbsBitmapMask2 );

    CAknIcon* createIcon5 = AknIconUtils::CreateIconL( sourceIcon );
    _LIT( KCreateIconL5, "CreateIconL with SourceIcon test" );
    AssertTrueL( ETrue, KCreateIconL5 );
    delete createIcon5;
    CleanupStack::Pop( sourceIcon );

    CFbsBitmap* sourceBitmap = NULL;
    CFbsBitmap* maskBitmap = NULL;
    AknIconUtils::CreateIconLC( sourceBitmap, maskBitmap,
        AknIconUtils::AvkonIconFileName(), EMbmAvkonQgn_graf_tab_21,
        EMbmAvkonQgn_graf_tab_21_mask );

    CFbsBitmap* createIcon6 = AknIconUtils::CreateIconL( sourceBitmap );
    _LIT( KCreateIconL6, "CreateIconL with SourceBitmap test" );
    AssertTrueL( ETrue, KCreateIconL6 );
    CleanupStack::Pop( 2 );
    delete maskBitmap;
    delete createIcon6;

    TRgb color = ( KRgbBlack, KRgbRed, KRgbGreen );
    AknIconUtils::SetIconColor( bitmap, color );
    _LIT( KSetIconColor, "SetIconColor test" );
    AssertTrueL( ETrue, KSetIconColor );
    CleanupStack::PopAndDestroy( 3 );
    }

// ---------------------------------------------------------------------------
// CBCTestForIcons::TestCAknIcon
// ---------------------------------------------------------------------------
//
void CBCTestForIcons::TestCAknIconL()
    {
    CAknIcon* icon = CAknIcon::NewL();
    _LIT( KNewL, "NewL For CAknIcon test" );
    AssertTrueL( ETrue, KNewL );

    CFbsBitmap* fbsBitmap = icon->Bitmap();
    _LIT( KBitmap, "Bitmap For CAknIcon test" );
    AssertTrueL( ETrue, KBitmap );

    CFbsBitmap* fbsBitmapMask = icon->Mask();
    _LIT( KMask, "Mask For CAknIcon test" );
    AssertTrueL( ETrue, KMask );

    icon->SetBitmap( fbsBitmap );
    _LIT( KSetBitmap, "SetBitmap test" );
    AssertTrueL( ETrue, KSetBitmap );

    icon->SetMask( fbsBitmapMask );
    _LIT( KSetMask, "SetMask test" );
    AssertTrueL( ETrue, KSetMask );

    delete icon;
    }
// ---------------------------------------------------------------------------
// CBCTestForIcons::TestIcons
// ---------------------------------------------------------------------------
//
void CBCTestForIcons::TestIconsL()
    {
    //Test for akniconsrvclient.h

    TInt connect = RAknIconSrvClient::Connect();
    _LIT( KConnect, "RAknIconSrvClient::Connect test" );
    AssertTrueL( ETrue, KConnect );

    RAknIconSrvClient::Disconnect();
    _LIT( KDisconnect, "RAknIconSrvClient::Disconnect test" );
    AssertTrueL( ETrue, KDisconnect );

    TestAknIconUtilsL();

    TestCAknIconL();
    }

// ---------------------------------------------------------------------------
//  CBCTestIconObserver::BitmapChanged
// ---------------------------------------------------------------------------
//
void CBCTestIconObserver::BitmapChanged( CFbsBitmap* )
    {
    }

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
//
CBCTestFileProvider::CBCTestFileProvider()
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestFileProvider::~CBCTestFileProvider()
    {
    }

// ---------------------------------------------------------------------------
// implementation of RetrieveIconFileHandleL
// ---------------------------------------------------------------------------
//
void CBCTestFileProvider::RetrieveIconFileHandleL( RFile& aFile,
     const TIconFileType aType )
    {
    if ( !iEnv )
        {
        iEnv = CEikonEnv::Static();
        }
    RFs tempFs = iEnv->FsSession();
    if ( aType == EMbmFile )
        {
        TInt result = aFile.Open( tempFs, AknIconUtils::AvkonIconFileName(),
            EFileShareReadersOnly );

            result = result;
        }
    else
        {
        _LIT( KMifFileName, "z:\\resource\\apps\\avkon2.mif" );
        TInt result = aFile.Open( tempFs, KMifFileName, EFileShareReadersOnly );
        result = result;
        }
    }

// ---------------------------------------------------------------------------
// implementation of Finished
// ---------------------------------------------------------------------------
//
void CBCTestFileProvider::Finished()
    {
    }
