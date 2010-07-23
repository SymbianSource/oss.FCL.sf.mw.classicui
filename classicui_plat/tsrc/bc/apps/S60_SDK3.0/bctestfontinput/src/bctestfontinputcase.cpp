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
#include <gdi.h>
#include <eikenv.h>
#include <avkon.hrh>

// test header of Api
#include <uiklaf/private/lafenv.h>
#include <aknlayoutfont.h>
#include <aknfontspecification.h>
#include <akntextdecorationmetrics.h>
#include <gulbordr.h>
#include <akniconutils.h>
#include <aknutils.h>
#include <bctestfontinput.rsg>
#include <avkon.mbg>
#include <bctestfontinput_aif.mbg>

#include "bctestfontinputcase.h"
#include "bctestfontinputcontainer.h"
#include "bctestfontinput.hrh"



// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestFontInputCase* CBCTestFontInputCase::NewL(
    CBCTestFontInputContainer* aContainer )
    {
    CBCTestFontInputCase* self = new( ELeave ) CBCTestFontInputCase(
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
CBCTestFontInputCase::CBCTestFontInputCase(
    CBCTestFontInputContainer* aContainer )
    : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestFontInputCase::~CBCTestFontInputCase()
    {

    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestFontInputCase::ConstructL()
    {
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCTestFontInputCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestFontInputCase::BuildScriptL()
    {
    // Add script as your need.
    AddTestL( DELAY( 2 ), LeftCBA, KeyOK,KeyOK,LeftCBA,Down,KeyOK, TEND );
    }

// ---------------------------------------------------------------------------
// CBCTestFontInputCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestFontInputCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestFontSpec || aCmd > EBCTestLafEnv )
        {
        return;
        }    
    switch ( aCmd )
        {
        case EBCTestLafEnv:
            TestLafEnvL();
            break;
        case EBCTestFontSpec:
            TestFontSpecL();
            break;

        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestFontInputCase::TestFontSpecL
// ---------------------------------------------------------------------------
//

void CBCTestFontInputCase::TestFontSpecL()
    {
    // Test some API here
    TAknFontSpecification fontSpec( 3 );
    
    fontSpec.SetExactMatchRequired( ETrue );
    _LIT( stMatch, " Test SetExactMatchRequired() " );
    AssertTrueL( ETrue, stMatch );

    fontSpec.SetTextPaneHeight( TInt( 3 ) );
    _LIT( stPaneHeight, " Test SetTextPaneHeight()" );
    AssertTrueL( ETrue, stPaneHeight );

    fontSpec.SetFontCategory( EAknFontCategoryUndefined );
    _LIT( stFontCate, " Test SetFontCategory() " );
    AssertTrueL( ETrue, stFontCate );

    fontSpec.SetPosture( EPostureUpright );
    _LIT( stPost, " Test SetPosTure() " );
    AssertTrueL( ETrue, stPost );

    fontSpec.SetTextPaneHeightIsDesignHeight( ETrue );
    _LIT( stHeighIsDesHeight, " Test SetTextPaneHeightIsDesignHeight() " );
    AssertTrueL( ETrue, stHeighIsDesHeight );

    fontSpec.SetUnits( TAknFontSpecification::EPixels);
    _LIT( stUnits, " Test SetUnits()" );
    AssertTrueL( ETrue, stUnits );

    fontSpec.SetWeight( EStrokeWeightNormal );
    _LIT( stWeight, " Test SetWeight() " );
    AssertTrueL( ETrue, stWeight );

    TAknTextDecorationMetrics txtDecMetric( 3 );
    
    txtDecMetric.BaselineToUnderlineOffset();
    _LIT( bsLnToUnderLn," Test BaseLineToUnderline)ffset() " );
    AssertTrueL( ETrue, bsLnToUnderLn );

    txtDecMetric.UnderlineHeight();
    _LIT( underLnHeight," Test UnderlineHeight() " );
    AssertTrueL( ETrue, underLnHeight );
     
    TInt lef,rgt,tp,bt;     
    txtDecMetric.GetLeftAndRightMargins( lef, rgt );
    _LIT( gtLeftAndRight, " Test GetLeftAndRightMargins() " );
    AssertTrueL( ETrue, gtLeftAndRight );
          
    txtDecMetric.GetTopAndBottomMargins( tp,bt );
    _LIT( gtTandB, " Test GetTopAndBottomMargins() " );
    AssertTrueL( ETrue, gtTandB );
     
    txtDecMetric.CursorWidth();
    _LIT( CurWidth, " Test CursorWidth() " );
    AssertTrueL( ETrue, CurWidth );
     
    TAknTextDecorationMetrics txtDecMetric1( CCoeEnv::Static()->NormalFont() );
    _LIT( txtDecMetricsFont, " Test TAKnTextDecorationMetrics( Font )" );
    AssertTrueL( ETrue, txtDecMetricsFont );
     
    TAknTextDecorationMetrics txtDecMetric2( fontSpec );
    _LIT( txtDecMetricsSpec," Test TAKnTextDecorationMetrics( Font )" );
    AssertTrueL( ETrue, txtDecMetricsSpec );
    
    const CAknLayoutFont* layoutFont = 
        AknLayoutUtils::LayoutFontFromId( 3 );
        
    TInt maxAscent = layoutFont->MaxAscent();
    _LIT( KLayoutFont1, "CAknLayoutFont::MaxAscent" );
    AssertTrueL( ETrue, KLayoutFont1 );
    
    TAknTextDecorationMetrics metrics = layoutFont->TextDecorationMetrics();
    _LIT( KLayoutFont2, "CAknLayoutFont::TextDecorationMetrics" );
    AssertTrueL( ETrue, KLayoutFont2 );
    }

void CBCTestFontInputCase::TestLafEnvL()
    {
    LafEnv::Beep();
    _LIT( beep," Test Beep() " );
    AssertTrueL( ETrue,beep );

    LafEnv::ClockDllName();
    _LIT( clkName," Test ClockDllName() " );
    AssertTrueL( ETrue,clkName );

    LafEnv::CoctlResourceFile();
    _LIT( ctlResFile," Test CoctlResourceFile() " );
    AssertTrueL( ETrue,ctlResFile );

    LafEnv::CreateTextParserL( TInt( 3 ) );
    _LIT( crtTxtParser," Test CreateTextParserL() " );
    AssertTrueL( ETrue,crtTxtParser);

    LafEnv::DefaultBusyMsgCorner();
    _LIT(defBusyMsg," Test DefaultBusyMsgCorner() " );
    AssertTrueL( ETrue,defBusyMsg );

    LafEnv::IsTaskListDisabledAtInitialization();
    _LIT( isTaskInit," Test IsTaskListDisabledAtInitialization" );
    AssertTrueL( ETrue,isTaskInit );

    LafEnv::EditableControlStandardHeight( CEikonEnv::Static()->LafEnv() );
    _LIT( editHeight," Test EditableControlStandardHeight() " );
    AssertTrueL( ETrue,editHeight );

    LafEnv::IsDefaultKey( EAknSoftkeyBack );
    _LIT( isDefKey," Test IsDefaultKey() " );
    AssertTrueL( ETrue,isDefKey );

    CColorList *clrList = LafEnv::CreateColorListL( *CEikonEnv::Static() );
    _LIT(crtClrList," Test CreateColorListL() " );
    AssertTrueL( ETrue,crtClrList );

    LafEnv::UpdateColorListL( clrList );
    _LIT( upClrList," Test UpdateColorListL() " );
    AssertTrueL( ETrue, upClrList );


    TInt fId = LafEnv::LoadPrivResFileL( *CEikonEnv::Static() );
    _LIT( ldResFile," Test LoadPrivResFileL() " );
    AssertTrueL( ETrue,ldResFile );
    CEikonEnv::Static()->DeleteResourceFile( fId );

    fId = LafEnv::LoadCoreResFileL( *CEikonEnv::Static() );
    CEikonEnv::Static()->DeleteResourceFile( fId );
    _LIT( cResFile," Test LoadCoreResFileL() " );
    AssertTrueL( ETrue,cResFile );

    CArrayPtr<CLafSystemFont> *ftArray = new (ELeave)
        CArrayPtrSeg<CLafSystemFont>(10);
    LafEnv::CreateSystemFontsL( *CEikonEnv::Static(),*ftArray );
    _LIT( crtSysFont," Test CreateSystemFontsL() " );
    AssertTrueL( ETrue,crtSysFont );

    LafEnv::UpdateSystemFontsL( CEikonEnv::Static(),*ftArray );
    _LIT( upSysFont," Test UpdateSystemFontsL() " );
    AssertTrueL( ETrue,upSysFont );

	LafEnv::ReleaseSystemFonts(*ftArray);
    delete ftArray;
    CArrayPtrFlat<CFbsBitmap> *arBitmaps = new
        CArrayPtrFlat<CFbsBitmap>(16);
    LafEnv::CreateSystemBitmapsL( *CEikonEnv::Static(), *arBitmaps);
    _LIT( crtSysBitmap," Test CreateSystemBitmapsL() " );
    AssertTrueL( ETrue,crtSysBitmap );

    LafEnv::UpdateSystemBitmapsL(*CEikonEnv::Static() , *arBitmaps,*clrList );
    _LIT( upSysBitmap," Test UpdateSystemBitmapsL() " );
    AssertTrueL( ETrue,upSysBitmap );

    delete clrList;
    delete arBitmaps;
     
    MEikBusyMsgWin *msgWin = LafEnv::NewBusyMsgWinL( *CCoeEnv::Static());
    msgWin->Release();
    _LIT( newMsgWin," Test NewBusyMsgWinL() " );
    AssertTrueL( ETrue,newMsgWin );
      
    RWindowGroup rWinGrup = CCoeEnv::Static()->RootWin();
    MEikInfoMsgWin* infMsgWin = LafEnv::NewInfoMsgWinL( *CCoeEnv::Static(),
                                                          rWinGrup );
    _LIT( newinfMsgWinGrup," Test NewInfoMsgWinL() " );
    AssertTrueL( ETrue,newinfMsgWinGrup); 
     
    infMsgWin->Release(); 
         
    infMsgWin = LafEnv::NewInfoMsgWinL( *CCoeEnv::Static() );
    _LIT( newinfMsgWin," Test NewInfoMsgWinL() " );
    AssertTrueL( ETrue,newinfMsgWin );
    infMsgWin->Release(); 
         
    LafEnv::DefaultLineSpacingInTwips();
    _LIT( defLnSpaTwip," Test DefaultLineSpaceingInTwinps() " );
    AssertTrueL( ETrue,defLnSpaTwip );
     
    TCharFormat charFormat;
    TCharFormatMask charFormatMask;
     
    LafEnv::PrepareCharFormatAndMask( charFormat,charFormatMask );
    _LIT( preCharFormat," Test PrepareCharFormatAndMask() " );
    AssertTrueL( ETrue,preCharFormat );
     
    TGulBorder tBorder;
    TRect tRect;
    TGulBorder::TColors bColors;
    LafEnv::DrawLogicalBorder( tBorder,CCoeEnv::Static()->SystemGc(),tRect,bColors);
    _LIT( drawLogBoder," Test DrawLogicalBorder()" );
    AssertTrueL( ETrue,drawLogBoder );

    TBuf<32> fPath;
    TUid apUid = { 0x101F84F3 };
    RApaLsSession *rLsSession = new ( ELeave ) RApaLsSession();
    LafEnv::GetDefaultPath( fPath,apUid,*rLsSession,*CCoeEnv::Static() );
    delete rLsSession;

    _LIT(msg1," Alert 1 " );
    _LIT(msg2," Alert 2 " );
    _LIT(disAlert, " Test DisplayAlertAsNotifier() " );
    LafEnv::DisplayAlertAsNotifier( msg1,msg2 );
    AssertTrueL( ETrue,disAlert );
    
    CFbsBitmap* bmp1 = new( ELeave ) CFbsBitmap();
    CleanupStack::PushL( bmp1 );
    CFbsBitmap* bmp2 = new( ELeave ) CFbsBitmap();
    CleanupStack::PushL( bmp2 );
    const TDesC& fileName = AknIconUtils::AvkonIconFileName();
    bmp1->Load( fileName, EMbmAvkonQgn_indi_battery_strength ); 
    bmp2->Load( fileName, EMbmAvkonQgn_prop_battery_icon );
    CArrayPtrFlat<CFbsBitmap>* bmpArray = new( ELeave ) 
        CArrayPtrFlat<CFbsBitmap>( 2 );
    CleanupStack::PushL( bmpArray );
    bmpArray->AppendL( bmp1 );
    bmpArray->AppendL( bmp2 );  
    TUid matchUid = TUid::Uid( KLafUidEikonGrayVal );
    CFbsBitmap* bmp = LafEnv::MatchBitmap( *bmpArray, matchUid );
    _LIT( KMatchBitmap, "LafEnv::MatchBitmap" );
    AssertNotNullL( bmp, KMatchBitmap );    
    CleanupStack::PopAndDestroy( 3 ); // are bmp1, bmp2 and bmpArray
    }
