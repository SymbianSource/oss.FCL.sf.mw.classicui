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

#include <AknLayout2Def.h>
#include <AknLayout2ScalableDef.h>


#include "bctestdomlayoutdatacase.h"
#include "bctestdomfntlaycontainer.h"
#include "bctestdomfntlay.hrh"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomLayoutDataCase* CBCTestDomLayoutDataCase::NewL()
    {
    CBCTestDomLayoutDataCase* self = new( ELeave ) CBCTestDomLayoutDataCase();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestDomLayoutDataCase::CBCTestDomLayoutDataCase()
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDomLayoutDataCase::~CBCTestDomLayoutDataCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomLayoutDataCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomLayoutDataCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestDomLayoutDataCase::BuildScriptL()
    { 
    // Add script as your need.   
    AddTestL( DELAY(1),
              LeftCBA, REP(Down,2), LeftCBA, LeftCBA,
              LeftCBA, REP(Down,2), LeftCBA, REP(Down,1), LeftCBA,
              LeftCBA, REP(Down,2), LeftCBA, REP(Down,2), LeftCBA,
              TEND );       
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomLayoutDataCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestDomLayoutDataCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestDomCmdOutline13 || aCmd > EBCTestDomCmdOutline15 )
        {
        return;
        }
        
    switch ( aCmd )
        {
        case EBCTestDomCmdOutline13: //AknLayout2Def.h   5
            {
            TestLayout2DefL();                  
            break;
            }
        case EBCTestDomCmdOutline14: //AknLayout2ScalableDef  51
            {
            TestLayout2ScalableDefL();
            break;  
            }
        case EBCTestDomCmdOutline15: //AknLayout2ScalableDef 28 
            {
            TestLayout2ScalableDef2L();
            break;
            }
        default:
            break;
        }
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomLayoutDataCase::TestLayout2DefL
// ---------------------------------------------------------------------------
//
void CBCTestDomLayoutDataCase::TestLayout2DefL()//AknLayout2Def.h   5
    {
    //TAknWindowComponentLayout 3
    TAknWindowComponentLayout winComLayout ;
    TAknWindowLineLayout winLineLayout( winComLayout );  
    _LIT( KTxtTAknWindowLineLayout,
        "TAknWindowLineLayout::TAknWindowLineLayout" );
    AssertTrueL( ETrue, KTxtTAknWindowLineLayout );

    TAknWindowLineLayout winLineLayout2 = winComLayout ;   
    _LIT( KTxtOperatorEqual, "TAknWindowLineLayout::operator=" );
    AssertTrueL( ETrue, KTxtOperatorEqual );

    TAknWindowLineLayout winLineLayout3 = 
        TAknWindowLineLayout::CombineLines(
        winLineLayout, winLineLayout2 );
    _LIT( KTxtCombineLines, "TAknWindowLineLayout::CombineLines" );
    AssertTrueL( ETrue, KTxtCombineLines );

    //TAknTextLineLayout 2
    TAknTextComponentLayout txtComLayout;
    TAknTextLineLayout txtLineLayout( txtComLayout );
    _LIT( KTxtTAknTextLineLayout,
        "TAknTextLineLayout::TAknTextLineLayout" );
    AssertTrueL( ETrue, KTxtTAknTextLineLayout );

    TAknTextLineLayout txtLineLayout2 = txtComLayout;
    _LIT( KTxtOpEqual, "TAknTextLineLayout::operator=" );
    AssertTrueL( ETrue, KTxtOpEqual );   
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomLayoutDataCase::TestLayout2ScalableDefL
// ---------------------------------------------------------------------------
//
void CBCTestDomLayoutDataCase::TestLayout2ScalableDefL() 
    {
    //AknLayout2ScalableDef  51
    //TAknLayoutScalableTableLimits 7
            
    TAknLayoutScalableTableLimits layScaTableLists;
    _LIT( KTxtTAknLayoutScalableTableLimits,
        "TAknLayoutScalableTableLimits::\
        TAknLayoutScalableTableLimits" );
    AssertTrueL( ETrue, KTxtTAknLayoutScalableTableLimits );

    TAknLayoutScalableTableLimits layScaTableLists2( 1, 2 );
    _LIT( KTxtTAknLayoutScalableTableLimits2,
        "TAknLayoutScalableTableLimits::\
        TAknLayoutScalableTableLimits2" );
    AssertTrueL( ETrue, KTxtTAknLayoutScalableTableLimits2 );

    TAknLayoutTableLimits layTableLimits =
        layScaTableLists2.LayoutLimits();
    _LIT( KTxtLayoutLimits,
        "TAknLayoutScalableTableLimits::LayoutLimits" );
    AssertTrueL( ETrue, KTxtLayoutLimits ); 

    layScaTableLists.SetFirstIndex( 1 );
    _LIT( KTxtSetFirstIndex,
        "TAknLayoutScalableTableLimits::SetFirstIndex" );
    AssertTrueL( ETrue, KTxtSetFirstIndex );

    layScaTableLists.SetLastIndex( 2 );
    _LIT( KTxtSetLastIndex,
        "TAknLayoutScalableTableLimits::SetLastIndex" );
    AssertTrueL( ETrue, KTxtSetLastIndex ); 

    TInt firstIndex = layScaTableLists.FirstIndex();
    _LIT( KTxtFirstIndex,
        "TAknLayoutScalableTableLimits::FirstIndex" );
    AssertTrueL( ETrue, KTxtFirstIndex ); 

    TInt lastIndex = layScaTableLists.LastIndex();
    _LIT( KTxtLastIndex,
        "TAknLayoutScalableTableLimits::LastIndex" );
    AssertTrueL( ETrue, KTxtLastIndex );

    //TAknLayoutScalableParameterLimits 13

    TAknLayoutScalableParameterLimits laySCaParamLims;
    _LIT( KTxtTAknLayoutScalableParameterLimits,
        "TAknLayoutScalableParameterLimits::\
        TAknLayoutScalableParameterLimits" );
    AssertTrueL( ETrue, KTxtTAknLayoutScalableParameterLimits );

    TAknLayoutScalableParameterLimits laySCaParamLims2( 1, 
        2, 1, 2, 1, 2 );
    _LIT( KTxtTAknLayoutScalableParameterLimits2,
        "TAknLayoutScalableParameterLimits::\
        TAknLayoutScalableParameterLimits2" );
    AssertTrueL( ETrue, KTxtTAknLayoutScalableParameterLimits2 );

    laySCaParamLims.SetFirstVariety( 1 );
    _LIT( KTxtSetFirstVariety,
        "TAknLayoutScalableParameterLimits::SetFirstVariety" );
    AssertTrueL( ETrue, KTxtSetFirstVariety );

    laySCaParamLims.SetLastVariety( 2 );
    _LIT( KTxtSetLastVariety,
        "TAknLayoutScalableParameterLimits::SetLastVariety" );
    AssertTrueL( ETrue, KTxtSetLastVariety );

    laySCaParamLims.SetFirstColumn( 1 );
    _LIT( KTxtSetFirstColumn,
        "TAknLayoutScalableParameterLimits::SetFirstColumn" );
    AssertTrueL( ETrue, KTxtSetFirstColumn );

    laySCaParamLims.SetLastColumn( 2 );
    _LIT( KTxtSetLastColumn,
        "TAknLayoutScalableParameterLimits::SetLastColumn" );
    AssertTrueL( ETrue, KTxtSetLastColumn );

    laySCaParamLims.SetFirstRow( 1 );
    _LIT( KTxtSetFirstRow,
        "TAknLayoutScalableParameterLimits::SetFirstRow" );
    AssertTrueL( ETrue, KTxtSetFirstRow );

    laySCaParamLims.SetLastRow( 2 );
    _LIT( KTxtSetLastRow,
        "TAknLayoutScalableParameterLimits::SetLastRow" );
    AssertTrueL( ETrue, KTxtSetLastRow );

    TInt ret = laySCaParamLims.FirstVariety();
    _LIT( KTxtFirstVariety,
        "TAknLayoutScalableParameterLimits::FirstVariety" );
    AssertTrueL( ETrue, KTxtFirstVariety );

    ret = laySCaParamLims.LastVariety();
    _LIT( KTxtLastVariety,
        "TAknLayoutScalableParameterLimits::LastVariety" );
    AssertTrueL( ETrue, KTxtLastVariety );

    ret = laySCaParamLims.FirstColumn();
    _LIT( KTxtFirstColumn,
        "TAknLayoutScalableParameterLimits::FirstColumn" );
    AssertTrueL( ETrue, KTxtFirstColumn );  

    ret = laySCaParamLims.LastColumn();
    _LIT( KTxtLastColumn,
        "TAknLayoutScalableParameterLimits::LastColumn" );
    AssertTrueL( ETrue, KTxtLastColumn );

    ret = laySCaParamLims.FirstRow();
    _LIT( KTxtFirstRow,
        "TAknLayoutScalableParameterLimits::FirstRow" );
    AssertTrueL( ETrue, KTxtFirstRow );

    //TAknWindowComponentLayout 31    
    TAknWindowComponentLayout winComLayout;
    _LIT( KTxtTAknWindowComponentLayout,
        "TAknWindowComponentLayout::TAknWindowComponentLayout" );
    AssertTrueL( ETrue, KTxtTAknWindowComponentLayout ); 

    TAknWindowLineLayout winLineLayout = winComLayout.LayoutLine();
    _LIT( KTxtLayoutLine,
        "TAknWindowComponentLayout::LayoutLine" );
    AssertTrueL( ETrue, KTxtLayoutLine );

    TAknWindowLineLayout winLineLayout2 = 
        winComLayout.LayoutLineNoEmptys();
    _LIT( KTxtLayoutLineNoEmptys,
        "TAknWindowComponentLayout::LayoutLineNoEmptys" );
    AssertTrueL( ETrue, KTxtLayoutLineNoEmptys );

    TAknLayoutScalableComponentType layScaComTaype = 
        winComLayout.LayoutComponentType();
    _LIT( KTxtLayoutComponentType,
        "TAknWindowComponentLayout::LayoutComponentType" );
    AssertTrueL( ETrue, KTxtLayoutComponentType );

    TAknWindowComponentLayout winComLayout2;            
    TAknWindowComponentLayout winComLayout3 = 
        TAknWindowComponentLayout::Compose( winComLayout,
        winComLayout2 );
    _LIT( KTxtCompose, "TAknWindowComponentLayout::Compose" );
    AssertTrueL( ETrue, KTxtCompose ); 

    TAknTextComponentLayout txtComLayout12;
    TAknTextComponentLayout txtComLayout13 = 
        TAknWindowComponentLayout::ComposeText( winComLayout,
        txtComLayout12 );
    _LIT( KTxtComposeText,
        "TAknWindowComponentLayout::ComposeText" );
    AssertTrueL( ETrue, KTxtComposeText ); 

    TAknWindowComponentLayout winComLayout4 = 
        TAknWindowComponentLayout::Intersect( winComLayout,
        winComLayout2 );
    _LIT( KTxtIntersect, "TAknWindowComponentLayout::Intersect" );
    AssertTrueL( ETrue, KTxtIntersect );

    TAknWindowComponentLayout winComLayout5 = 
        TAknWindowComponentLayout::Minus( winComLayout,
        winComLayout2 );
    _LIT( KTxtMinust, "TAknWindowComponentLayout::Minus" );
    AssertTrueL( ETrue, KTxtMinust );

    TAknWindowComponentLayout winComLayout13 = 
        TAknWindowComponentLayout::SiblingAsChild( winComLayout,
        winComLayout2 );
    _LIT( KTxtSiblingAsChild,
        "TAknWindowComponentLayout::SiblingAsChild" );
    AssertTrueL( ETrue, KTxtSiblingAsChild );   

    winComLayout.SetZeroSized();
    _LIT( KTxtSetZeroSized,
        "TAknWindowComponentLayout::SetZeroSized" );
    AssertTrueL( ETrue, KTxtSetZeroSized ); 

    TAknWindowComponentLayout winComLayout6 = 
        TAknWindowComponentLayout::Split( winComLayout, 2 );
    _LIT( KTxtSplit, "TAknWindowComponentLayout::Split" );
    AssertTrueL( ETrue, KTxtSplit );

    TAknWindowComponentLayout winComLayout7 = 
        TAknWindowComponentLayout::MultiLineGrid( winComLayout,
        1, 1, 1, 1 );
    _LIT( KTxtMultiLineGrid, 
        "TAknWindowComponentLayout::MultiLineGrid" );
    AssertTrueL( ETrue, KTxtMultiLineGrid );

    TAknWindowComponentLayout winComLayout8 = 
        TAknWindowComponentLayout::MultiLineX( winComLayout,
        1, 1 );
    _LIT( KTxtMultiLineX, "TAknWindowComponentLayout::MultiLineX" );
    AssertTrueL( ETrue, KTxtMultiLineX ); 

    TAknWindowComponentLayout winComLayout9 = 
        TAknWindowComponentLayout::MultiLineY( winComLayout,
        1, 1 );
    _LIT( KTxtMultiLineY, "TAknWindowComponentLayout::MultiLineY" );
    AssertTrueL( ETrue, KTxtMultiLineY );

    TAknWindowComponentLayout::TRangeTriplet rangeTriplet;
    TAknWindowComponentLayout winComLayout10 = 
        TAknWindowComponentLayout::Anim( winComLayout,
        winComLayout2, rangeTriplet );
    _LIT( KTxtAnim, "TAknWindowComponentLayout::Anim" );
    AssertTrueL( ETrue, KTxtAnim );

    TAknWindowComponentLayout winComLayout11( winComLayout2 );
    _LIT( KTxtTAknWindowComponentLayout2,
        "TAknWindowComponentLayout::TAknWindowComponentLayout2" );
    AssertTrueL( ETrue, KTxtTAknWindowComponentLayout2 );

    TAknWindowComponentLayout winComLayout12; 
    winComLayout12 = winLineLayout;
    _LIT( KTxtWinComOptEqual,
        "TAknWindowComponentLayout::operator=" );
    AssertTrueL( ETrue, KTxtWinComOptEqual );
    }

// ---------------------------------------------------------------------------
// CBCTestDomLayoutDataCase::TestLayout2ScalableDef2L
// ---------------------------------------------------------------------------
//
void CBCTestDomLayoutDataCase::TestLayout2ScalableDef2L()
    {
    //AknLayout2ScalableDef 28
    TAknTextComponentLayout txtComLayout;
    _LIT( KTxtTAknTextComponentLayout,
        "TAknTextComponentLayout::TAknTextComponentLayout" );
    AssertTrueL( ETrue, KTxtTAknTextComponentLayout );

    TAknTextLineLayout txtLineLayout = txtComLayout.LayoutLine();
    _LIT( KTxtComLayoutLine, "TAknTextComponentLayout::LayoutLine" );
    AssertTrueL( ETrue, KTxtComLayoutLine );    

    TAknTextComponentLayout txtComLayout8;
    TAknTextComponentLayout txtComLayout9;
    RArray<TAknTextComponentLayout> txtComLayouts;
    CleanupClosePushL( txtComLayouts );
    txtComLayouts.Append( txtComLayout8 );
    txtComLayouts.Append( txtComLayout9 );
    TAknMultiLineTextLayout mulLineTxtlayout = 
        TAknTextComponentLayout::Multiline( txtComLayouts );            
    _LIT( KTxtMultiline, "TAknTextComponentLayout::Multiline" );
    AssertTrueL( ETrue, KTxtMultiline );  

    TAknTextLineLayout txtLineLayout2 =
        txtComLayout.LayoutLineNoEmptys();
    _LIT( KTxtTextLayoutLineNoEmptys,
        "TAknTextComponentLayout::LayoutLineNoEmptys" );
    AssertTrueL( ETrue, KTxtTextLayoutLineNoEmptys ); 

    TAknLayoutScalableComponentType layScaComType = 
        txtComLayout.LayoutComponentType();    
    _LIT( KTxtTextLayoutComponentType,
        "TAknTextComponentLayout::LayoutComponentType" );
    AssertTrueL( ETrue, KTxtTextLayoutComponentType );

    txtComLayout.SetC( 1 );    
    _LIT( KTxtSetC, "TAknTextComponentLayout::SetC" );
    AssertTrueL( ETrue, KTxtSetC );

    txtComLayout.Setl( 2 );    
    _LIT( KTxtSetl, "TAknTextComponentLayout::Setl" );
    AssertTrueL( ETrue, KTxtSetl );

    txtComLayout.Sett( 3 );    
    _LIT( KTxtSett, "TAknTextComponentLayout::Sett" );
    AssertTrueL( ETrue, KTxtSett );

    txtComLayout.Setr( 4 );    
    _LIT( KTxtSetr, "TAknTextComponentLayout::Setr" );
    AssertTrueL( ETrue, KTxtSetr );

    txtComLayout.Setb( 5 );    
    _LIT( KTxtSetb, "TAknTextComponentLayout::Setb" );
    AssertTrueL( ETrue, KTxtSetb );

    txtComLayout.SetW( 6 );    
    _LIT( KTxtSetW, "TAknTextComponentLayout::SetW" );
    AssertTrueL( ETrue, KTxtSetW );

    txtComLayout.SetH( 7 );    
    _LIT( KTxtSetH, "TAknTextComponentLayout::SetH" );
    AssertTrueL( ETrue, KTxtSetH );

    txtComLayout.SetJ( 8 );    
    _LIT( KTxtSetJ, "TAknTextComponentLayout::SetJ" );
    AssertTrueL( ETrue, KTxtSetJ );

    txtComLayout.SetFont( 8 );    
    _LIT( KTxtSetFont, "TAknTextComponentLayout::SetFont" );
    AssertTrueL( ETrue, KTxtSetFont );

    TInt16 chr = txtComLayout.C();    
    _LIT( KTxtC, "TAknTextComponentLayout::C" );
    AssertTrueL( ETrue, KTxtC );

    chr = txtComLayout.l();    
    _LIT( KTxtl, "TAknTextComponentLayout::l" );
    AssertTrueL( ETrue, KTxtl );

    chr = txtComLayout.t();    
    _LIT( KTxtt, "TAknTextComponentLayout::t" );
    AssertTrueL( ETrue, KTxtt );

    chr = txtComLayout.r();    
    _LIT( KTxtr, "TAknTextComponentLayout::r" );
    AssertTrueL( ETrue, KTxtr );

    chr = txtComLayout.b();    
    _LIT( KTxtb, "TAknTextComponentLayout::b" );
    AssertTrueL( ETrue, KTxtb );

    chr = txtComLayout.W();    
    _LIT( KTxtW, "TAknTextComponentLayout::W" );
    AssertTrueL( ETrue, KTxtW );

    chr = txtComLayout.H();    
    _LIT( KTxtH, "TAknTextComponentLayout::H" );
    AssertTrueL( ETrue, KTxtH );

    chr = txtComLayout.J();    
    _LIT( KTxtJ, "TAknTextComponentLayout::J" );
    AssertTrueL( ETrue, KTxtJ );

    TInt32 fon = txtComLayout.Font();    
    _LIT( KTxtFont, "TAknTextComponentLayout::Font" );
    AssertTrueL( ETrue, KTxtFont );

    TAknWindowComponentLayout::TRangeTriplet ranTriplet;
    TAknTextComponentLayout txtComLayout2;
    TAknTextComponentLayout txtComLayout3 =
        TAknTextComponentLayout::Anim( txtComLayout,
        txtComLayout2, ranTriplet );
    _LIT( KTxtextAnim, "TAknTextComponentLayout::Anim" );
    AssertTrueL( ETrue, KTxtextAnim );

    TAknTextComponentLayout txtComLayout4 =
        TAknTextComponentLayout::MultiLineY( txtComLayout, 1, 1 );
    _LIT( KTxtTextMultiLineY, "TAknTextComponentLayout::MultiLineY" );
    AssertTrueL( ETrue, KTxtTextMultiLineY );

    TAknTextComponentLayout txtComLayout5( txtComLayout );
    _LIT( KTxtTAknTextComponentLayout2,
        "TAknTextComponentLayout::TAknTextComponentLayout2" );
    AssertTrueL( ETrue, KTxtTAknTextComponentLayout2 );

    TAknTextComponentLayout txtComLayout6;
    txtComLayout6 = txtLineLayout2;
    _LIT( KTxttTextOptEqual, "TAknTextComponentLayout::operator=" );
    AssertTrueL( ETrue, KTxttTextOptEqual );
    CleanupStack::Pop(); // Pop txtComLayouts;             
    txtComLayouts.Close();    
    }
