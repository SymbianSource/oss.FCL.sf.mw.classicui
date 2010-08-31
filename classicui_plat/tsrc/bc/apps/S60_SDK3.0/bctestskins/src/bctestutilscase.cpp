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
#include <eikenv.h>
#include <aknsutils.h> 
#include <aknswallpaperutils.h> 
#include <gulicon.h> 
#include <aknsdatacontext.h> 

#include "bctestutilscase.h"
#include "bctestskinscontainer.h"
#include "bctestskins.hrh"
#include "bctestskinsapp.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestUtilsCase* CBCTestUtilsCase::NewL( 
    CBCTestSkinsContainer* aContainer )
    {
    CBCTestUtilsCase* self = new( ELeave ) CBCTestUtilsCase( 
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
CBCTestUtilsCase::CBCTestUtilsCase( 
    CBCTestSkinsContainer* aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestUtilsCase::~CBCTestUtilsCase()
    {  
    iSkinInstance = NULL;
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestUtilsCase::ConstructL()
    {    
    BuildScriptL();   
    iSkinInstance = AknsUtils::SkinInstance(); 
    }
    
// ---------------------------------------------------------------------------
// CBCTestUtilsCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestUtilsCase::BuildScriptL()
    { 
   const TInt scripts[] =
        {
        DELAY(1),        // delay between commands is 1*0.1 seconds = 0.1 seconds
        LeftCBA,
        REP(Down, 3),
        LeftCBA
        };
    AddTestScriptL(scripts, sizeof(scripts)/sizeof(TInt));
    }
    
// ---------------------------------------------------------------------------
// CBCTestUtilsCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestUtilsCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline4 || aCmd > EBCTestCmdOutline4 )
        {
        return;
        }

    switch ( aCmd )  
        {
        case EBCTestCmdOutline4:
            TestFunctionL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestUtilsCase::TestFunctionL
// ---------------------------------------------------------------------------
//   
void CBCTestUtilsCase::TestFunctionL()
    {
    // Test AknsUtils APIs
	AknsUtils::SetAvkonSkinEnabledL( ETrue );
    _LIT( KSetSkinEnabled, "AknsUtils::SetAvkonSkinEnabledL" );
    AssertNotNullL( iContainer, KSetSkinEnabled );
    
    AknsUtils::InitSkinSupportL();
    _LIT( KInitSkin, "AknsUtils::InitSkinSupportL" );
    AssertNotNullL( iContainer, KInitSkin );

	AknsUtils::SetAvkonHighlightAnimationEnabledL( ETrue );     
    _LIT( KSetHlAnimEnabled, "AknsUtils::SetAvkonHighlightAnimationEnabledL" );
    AssertNotNullL( iContainer, KSetHlAnimEnabled );

    _LIT( KPath, "z:\\wallpaper.bmp" );
    TBuf<32> path( KPath );
    AknsWallpaperUtils::SetIdleWallpaper( KPath, NULL );
    AssertNotNullL( iContainer, KPath );
    
    TAknsItemID itemID;
    _LIT( KMBMFileName, "\\resource\\apps\\bctestskins.mbm" ); 
    TBuf<32> filename( KMBMFileName );
    TAny* def = AknsUtils::CreateBitmapItemDefL( itemID, filename, 1 );
    _LIT( KCreateBitmapItemDefL, "AknsUtils::CreateBitmapItemDefL" );
    AssertNotNullL( def, KCreateBitmapItemDefL );
    delete def;
    def = NULL;

    TAny* mDef = 
        AknsUtils::CreateMaskedBitmapItemDefL( itemID, filename, 1, 2 );
    _LIT( KCreateMaskedBitmapItemDefL, "AknsUtils::CreateMaskedBitmapItemDefL" );
    AssertNotNullL( mDef, KCreateMaskedBitmapItemDefL );
    delete mDef;
    mDef = NULL;

	MAknsDataContext* context = AknsUtils::DataContext( iContainer );
    _LIT( KDataContext, "AknsUtils::DataContext" );
    AssertNotNullL( context, KDataContext );
    context = NULL;

    MAknsDataContext* dataContext = AknsUtils::CreateDataContextForContainerL(); 
    _LIT( KDataContextContn, "AknsUtils::CreateDataContextForContainerL" );
    AssertNotNullL( dataContext, KDataContextContn );
    // Test MAknsDataContext::SupplyMopObject
    TTypeUid::Ptr ptr = MAknsDataContext::SupplyMopObject ( 
        0x10005a28, dataContext );
    _LIT( KSupplyMopObject, "MAknsDataContext::SupplyMopObject" );
    AssertNotNullL( dataContext, KSupplyMopObject );
    delete dataContext;
    dataContext = NULL;
    
    CFbsBitmap* bitmap = NULL;    
    CFbsBitmap* mask = NULL;    
    AknsUtils::CreateAppIconLC( iSkinInstance, KUidBCTestSkins,
        EAknsAppIconTypeContext, bitmap, mask );        
    CleanupStack::PopAndDestroy( 2 ); // bitmap, mask
    _LIT( KAknsUtils1, "AknsUtils::CreateAppIconLC" );
    AssertTrueL( ETrue, KAknsUtils1 );
    
    TSize  size( 6, 6 );   
    CApaMaskedBitmap* icon = CApaMaskedBitmap::NewLC();    
    _LIT( KIcon, "CApaMaskedBitmap::NewLC invoked in AknsUtils case" );
    AssertNotNullL( icon, KIcon );    
    AknsUtils::GetAppIcon( iSkinInstance, KUidBCTestSkins, size, *icon );
    _LIT( KGetAppIcon, "AknsUtils::GetAppIcon" );
    AssertNotNullL( icon, KGetAppIcon );    
	CleanupStack::PopAndDestroy( icon );
	
    // The following will leave without panic	
    _LIT( KCreateBitmapL, "AknsUtils::CreateBitmapL() invoked" );
    CFbsBitmap* newBitmap(NULL);
    TRAPD(err, newBitmap = AknsUtils::CreateBitmapL( iSkinInstance, itemID ));
    if(err == KErrNone)
        {
        AssertNotNullL( newBitmap, KCreateBitmapL );
        delete newBitmap;
        newBitmap = NULL;
        }
    else
        {
        AssertTrueL(ETrue, KCreateBitmapL);
        }

    _LIT( KCreateMaskedBitmapL, "AknsUtils::CreateMaskedBitmapL() invoked" );
    CApaMaskedBitmap* maskedBmp(NULL);
    TRAP(err, maskedBmp = AknsUtils::CreateMaskedBitmapL( iSkinInstance, itemID ));
    if( err == KErrNone )
        {
        AssertNotNullL( maskedBmp, KCreateMaskedBitmapL );
        delete maskedBmp;
        maskedBmp = NULL;
        }
    else
        {
        AssertTrueL(ETrue, KCreateMaskedBitmapL);
        }
    
    _LIT( KCreateMaskedBitmapL2, "AknsUtils::CreateMaskedBitmapL 2" );
    CApaMaskedBitmap* bmp(NULL);
    TRAP( err, bmp = AknsUtils::CreateMaskedBitmapL( iSkinInstance, itemID, filename, 1, 2 ));
    if( err == KErrNone )
        {
        AssertNotNullL( bmp, KCreateMaskedBitmapL2 );
        delete bmp;
        bmp = NULL;
        }
    else
        {
        AssertTrueL(ETrue, KCreateMaskedBitmapL2);
        }
    
    _LIT( KCreateGulIconL, "AknsUtils::CreateGulIconL() invoked" );
    CGulIcon* gulIcon(NULL); 
    TRAP( err, gulIcon = AknsUtils::CreateGulIconL( iSkinInstance, itemID, ETrue ));
    if( err == KErrNone )
        {
        AssertNotNullL( gulIcon, KCreateGulIconL );
        delete gulIcon;
        gulIcon = NULL;
        }
    else
        {
        AssertTrueL(ETrue, KCreateGulIconL );
        }

    _LIT( KCreateGulIconL2, "AknsUtils::CreateGulIconL() invoked with ETrue arg" ); 
    CGulIcon* maskGulIcon(NULL);
    TRAP( err, maskGulIcon = AknsUtils::CreateGulIconL( iSkinInstance, itemID, ETrue ));
    if( err == KErrNone )
        {
        AssertNotNullL( maskGulIcon, KCreateGulIconL2 );
        delete maskGulIcon;
        maskGulIcon = NULL;
        }
    else
        {
        AssertTrueL(ETrue, KCreateGulIconL2);
        }
  
    _LIT( KCreateGulIconL3, "AknsUtils::CreateGulIconL() invoked with arg 3" );  
    gulIcon=NULL;
    TRAP( err, gulIcon = AknsUtils::CreateGulIconL( iSkinInstance, itemID, filename, 3, 4 ));
    if( err == KErrNone )
        {    
        AssertNotNullL( gulIcon, KCreateGulIconL3 );
        delete gulIcon;
        gulIcon = NULL;    
        }
    else
        {
        AssertTrueL(ETrue, KCreateGulIconL3);
        }
   	}
    
