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
#include <cdlengine.h>

#include <aknlayout2adaptationdatadef.h> 
#include <aknlayout2datadef.h>
#include <aknlayout2hierarchy.h>
#include <aknlayout2hierarchydef.h>

#include "bctestdomlayoutsystemcase.h"
#include "bctestdomfntlaycontainer.h"
#include "bctestdomfntlay.hrh"
#include "bctestdomadapter.h"

//constant variable define
const TInt KTableIndex( 2 );
const TUint8  KByteCodedData[] = {
// 0x0000 for Screen
0x02,0xfe,0x00,0x00,0xfe,0xfe,0xf0,0xff,0x01,0x40,
// 0x000a for application_window
0x04,0xfe,0x00,0x00,0x00,0x00,0xf0,0xff,0x01,0x40,
// 0x0014 for aid_cell_size_toolbar2
0x06,0xfe,0x00,0x00,0xfe,0xfe,0x20,0x45,
// 0x001c for aid_popup2_width_pane
0x06,0xfe,0x00,0x00,0xfe,0xfe,0xf0,0xf0,
// 0x0024 for aid_size_cell_touch
0x07,0x07,0x01,0xff,0x01,0x00,0x1c,0x01,0x01,0xfe,0x00,0x00,0xfe,0xfe,0x1b,
0xfc,0xfe,0xdb,0x1b,0x1b,0x1b,0xfc,0xfe,0xdb,0x1b,0xfc,0xfe,0xdb,
// 0x0040 for aid_visual_content_pane
0x06,0xfe,0x00,0x28,0xfe,0xfe,0xf0,0xf0,
// 0x0048 for aid_zoom_text_msg_primary
0x06,0xfe,0x00,0x00,0xfe,0xfe,0x3a,0x13,
// 0x0050 for area_bottom_pane
0x07,0x0b,0x01,0xff,0x01,0x10,0x2c,0x01,0x01,0xfe,0x00,0xfe,0xff,0x01,0x25,
0xff,0x01,0x25,0xdb,0xfe,0xdb,0xdb,0xff,0x01,0x25,0xfe,0xdb,0xfe,0x00,0x00,
0xfd,0x00,0x1b,0x1b,0x1b,0x15,0x1b,0x15,0x15,0x1b,0x1b,0x15,0x1b,
// 0x007b for area_side_right_pane
0x07,0x06,0x00,0x01,0x01,0xfe,0xfe,0x00,0x00,0xfe,0x5f,0xfd,0x00,
// 0x0088 for area_top_pane
0x07,0x0b,0x01,0xff,0x01,0xc0,0x2c,0x01,0x01,0xfe,0x00,0x00,0x00,0xff,0x01,
0x2c,0xff,0x01,0x10,0xdb,0xfe,0xfe,0xdb,0xdb,0xff,0x01,0x18,0xff,0x01,0x06,
0xdb,0xff,0x01,0x06,0xfd,0x00,0xfd,0x00,0xfd,0x00,0xfd,0x00,0xfe,0xfd,0x00,
0xfd,0x00,0xfd,0x00,0xfd,0x00,0xfd,0x00,0xfd,0x00,0x14,0x30,0x15,0x6a,0x14,
0x15,0x6a,0x28,0x3a,0x15,0x3a,
// 0x00ca for call_video_uplink_pane
0x07,0x02,0x01,0xff,0x01,0x98,0x08,0x01,0x01,0xfe,0x01,0x11,0x01,0x03,0xfe,
0xfe,0x4a,0x41,0x3d,0x35,
// 0x00de for main_pane
0x07,0x0d,0x01,0xff,0x01,0xd8,0x34,0x01,0x01,0xfe,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x3d,0x00,0x30,0x14,0x00,0x00,0x15,0xfe,0x14,
0x15,0x15,0x28,0x3a,0x15,0x3a,0x00,0x1b,0x1b,0x1b,0x00,0x15,0x1b,0x00,0x15,
0x15,0x1b,0x58,0x15,0x58,0xfd,0x00,0xfd,0x00,0xfd,0x00,0xfd,0x00,0xfd,0x00,
0xfd,0x00,0xfe,0xfd,0x00,0xfd,0x00,0xfd,0x00,0xfd,0x00,0xfe,0xfd,0x00,0xfe,
0xfe,0xfe,0xfd,0x00,0xfe,0xbf,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,
// 0x0136 for popup_fixed_preview_cale_window
0x07,0x01,0x00,0x01,0x01,0xfe,0x00,0xfe,0xfe,0x58,0xfd,0x00,0x00,
// 0x0143 for popup_preview_fixed_window
0x06,0xfe,0xfe,0x15,0x00,0x15,0xc0,0xfe,
// 0x014b for popup_toolbar2_fixed_window_cp01
0x07,0x05,0x01,0xff,0x01,0xd0,0x14,0x01,0x01,0xfe,0x00,0xfe,0x15,0xfe,0x15,
0xfe,0xfe,0x1b,0x15,0x1b,0x15,0x1b,0xfd,0x00,0x3d,0xfd,0x00,0x3d,0xfd,0x00,
0x3d,0xfe,0x3d,0xfe,0x3d,

// 0x016e for touch_pane
0x07,0x0c,0x01,0xff,0x01,0xd0,0x30,0x01,0x01,0xfe,0x00,0x00,0xfe,0x00,0x00,
0x00,0x00,0xfe,0xfe,0x00,0x00,0xfe,0x00,0xfe,0xfe,0x15,0xfe,0xfe,0xfe,0xfe,
0x15,0x15,0xfe,0xfe,0x15,0xfe,0xfd,0x00,0x20,0xfd,0x00,0xfd,0x00,0xfd,0x00,
0xfd,0x00,0x20,0x20,0xfd,0x00,0xfd,0x00,0x20,0xfd,0x00,0x20,0xc6,0x20,0x20,
0x20,0x20,0xc6,0xc6,0x20,0x20,0xc6,0x20,
// 0x01b2 for bg_popup_call_pane_cp05
0x07,0x04,0x00,0x01,0x01,0xfe,0x00,0x00,0x00,0x00,0xfd,0x00,0xfd,0x00,
// 0x01c0 for popup_number_entry_window_t1
0x0b,0x01,0x00,0x01,0x01,0xd7,0x0f,0x26,0x0f,0xfe,0xfd,0xe3,0x1b,0x02,0xfb,
0x83,0x60,0x00,0x03,
// 0x01d3 for popup_number_entry_window_t2
0x0b,0x01,0x00,0x01,0x01,0xd7,0x0f,0xfe,0x0f,0x2b,0xfe,0x19,0x03,0xfb,0x83,
0x20,0x00,0x01
};

const TUint16 KDataLookup[ ] ={
	
0x0000,	// Screen

0x000a,	// application_window

0x0050,	// area_bottom_pane_ParamLimits

0x0050,	// area_bottom_pane

0x0088,	// area_top_pane_ParamLimits

0x0088,	// area_top_pane

0x00ca,	// call_video_uplink_pane_ParamLimits

0x00ca,	// call_video_uplink_pane

0x00de,	// main_pane_ParamLimits

0x00de,	// main_pane

0x516d,	// context_pane

0x5180,	// navi_pane

0x5190,	// popup_cale_events_window_ParamLimits

0x5190,	// popup_cale_events_window

0x51a7,	// popup_mup_playback_window

0x51af,	// signal_pane

0x2fd0,	// main_browser_pane

0x2fd0,	// main_burst_pane

0x01c0,

0x0001, //19
KTableIndex,
0x016e
};


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomLayoutSystemCase* CBCTestDomLayoutSystemCase::NewL()
    {
    CBCTestDomLayoutSystemCase* self = new( ELeave ) CBCTestDomLayoutSystemCase();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestDomLayoutSystemCase::CBCTestDomLayoutSystemCase()
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDomLayoutSystemCase::~CBCTestDomLayoutSystemCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomLayoutSystemCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomLayoutSystemCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestDomLayoutSystemCase::BuildScriptL()
    { 
    // Add script as your need.   
    AddTestL( DELAY(1),
              LeftCBA, REP(Down,3), LeftCBA, LeftCBA,
              LeftCBA, REP(Down,3), LeftCBA, REP(Down,1), LeftCBA,
              LeftCBA, REP(Down,3), LeftCBA, REP(Down,2), LeftCBA,
              LeftCBA, REP(Down,3), LeftCBA, REP(Down,3), LeftCBA,
              TEND );     
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomLayoutSystemCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestDomLayoutSystemCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestDomCmdOutline16 || aCmd > EBCTestDomCmdOutline19 )
        {
        return;
        }
        
    switch ( aCmd )
        {
        case EBCTestDomCmdOutline16://AknLayout2AdaptationDataDef.h 5 
            {
            TestLayout2AdaptationDataDefL();
            break;
            }
        case EBCTestDomCmdOutline17: // AknLayout2DataDef.h 15
            {
            TestLayout2DataDefL();
            break;  
            }   
        case EBCTestDomCmdOutline18: //aknlayout2hierarchy.h  4
            {
            TestLayout2HierarchyL();
            break;
            }   
        case EBCTestDomCmdOutline19: //aknlayout2hierarchydef  16
            {
            TestLayout2HierarchyDefL();
            break;
            }   
        default:
            break;
        }
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomLayoutSystemCase::TestLayout2AdaptationDataDefL
// ---------------------------------------------------------------------------
//
void CBCTestDomLayoutSystemCase::TestLayout2AdaptationDataDefL()
    {
    
    TRect rect( TPoint( 1, 1 ), TSize( 20, 20 ) );
    CBCTestDomAdapter* testAdapter = CBCTestDomAdapter::NewL();
    CleanupStack::PushL( testAdapter ); 
    TUint* dataLookup = testAdapter->GetAdpDataLookup();  

    TAknTextLineLayout txtLineLayout;
    AknLayoutAdaptationDecodeSupport::MultiLineTextLine(
        txtLineLayout, dataLookup, 4, 1, 2, 3, 4 ); 
    _LIT( KTxtMultiLineTextLine,
        "AknLayoutAdaptationDecodeSupport::MultiLineTextLine" );
    AssertTrueL( ETrue, KTxtMultiLineTextLine );
    
    dataLookup += 1;
    
    TAknWindowLineLayout winLineLayout;
    AknLayoutAdaptationDecodeSupport::WindowTable(
        winLineLayout, dataLookup, 0, 0, 0, 0, 0, 0 ); 
    _LIT( KTxtWindowTable,
        "AknLayoutAdaptationDecodeSupport::WindowTable" );
    AssertTrueL( ETrue, KTxtWindowTable );
       
    AknLayoutAdaptationDecodeSupport::WindowTable(
        winLineLayout, dataLookup, 1, rect, 1, 1, 0, 0, 4 ); 
    _LIT( KTxtWindowTable2,
        "AknLayoutAdaptationDecodeSupport::WindowTable2" );
    AssertTrueL( ETrue, KTxtWindowTable2 ); 

    const TUint * dataLookup2 = dataLookup + 4; 

    AknLayoutAdaptationDecodeSupport::TextTable(
        txtLineLayout, dataLookup2, 1, 1, 1, 0, 0, 0 ); 
    _LIT( KTxtTextTable,
        "AknLayoutAdaptationDecodeSupport::TextTable" );
    AssertTrueL( ETrue, KTxtTextTable );

    TAknLayoutTableLimits layTableLim = 
        AknLayoutAdaptationDecodeSupport::TableLimits( dataLookup2 ); 
    _LIT( KTxtTableLimits,
        "AknLayoutAdaptationDecodeSupport::TableLimits" );
    AssertTrueL( ETrue, KTxtTableLimits );

    CleanupStack::PopAndDestroy( testAdapter ); 
    
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomLayoutSystemCase::TestLayout2DataDefL
// ---------------------------------------------------------------------------
//
void CBCTestDomLayoutSystemCase::TestLayout2DataDefL()
    {
    TRect rect( TPoint( 1, 1 ), TSize( 20, 20 ) );
            
    //TAknWindowLineLayoutImp 1
    TAknWindowLineLayoutImp winLineLayImp ;
    winLineLayImp.SetAllParentOffsets( rect );  
    _LIT( KTxtWinSetAllParentOffsets,
        "TAknWindowLineLayoutImp::SetAllParentOffsets" );
    AssertTrueL( ETrue, KTxtWinSetAllParentOffsets );

    //TAknTextLineLayoutImp  1
    TAknTextLineLayoutImp txtLineLayImp;
    txtLineLayImp.SetAllParentOffsets( rect );  
    _LIT( KTxtSetAllParentOffsets,
        "TAknTextLineLayoutImp::SetAllParentOffsets" );
    AssertTrueL( ETrue, KTxtSetAllParentOffsets );

    SImplData implData; 
    implData.iDataLookup = KDataLookup;
    implData.iByteCodedData = KByteCodedData;

    //AknLayoutDecodeSupport 13
    TAknWindowLineLayoutImp winLineLayImp2;
    AknLayoutDecodeSupport::WindowLine( winLineLayImp2, &implData );
    _LIT( KTxtWindowLine, "AknLayoutDecodeSupport::WindowLine" );
    AssertTrueL( ETrue, KTxtWindowLine );

    AknLayoutDecodeSupport::WindowLine( winLineLayImp2, &implData,
        0, 0, 0, 0, 0 );
    _LIT( KTxtWindowLine2, "AknLayoutDecodeSupport::WindowLine2" );
    AssertTrueL( ETrue, KTxtWindowLine2 );

    AknLayoutDecodeSupport::WindowLine( winLineLayImp2, &implData,
        rect, 0, 0, 0, 0, 0 );
    _LIT( KTxtWindowLine3, "AknLayoutDecodeSupport::WindowLine3" );
    AssertTrueL( ETrue, KTxtWindowLine3 );

    TAknTextLineLayoutImp txtLineLayImp2;
    AknLayoutDecodeSupport::TextLine( txtLineLayImp2, &implData );
    _LIT( KTxtTextLine, "AknLayoutDecodeSupport::TextLine" );
    AssertTrueL( ETrue, KTxtTextLine );

    AknLayoutDecodeSupport::TextLine( txtLineLayImp2, &implData,
        0, 0, 0, 0, 0 );
    _LIT( KTxtTextLine2, "AknLayoutDecodeSupport::TextLine2" );
    AssertTrueL( ETrue, KTxtTextLine2 );

    AknLayoutDecodeSupport::TextLine( txtLineLayImp2, &implData,
        rect, 0, 0, 0, 0, 0 );
    _LIT( KTxtTextLine3, "AknLayoutDecodeSupport::TextLine3" );
    AssertTrueL( ETrue, KTxtTextLine3 );  

    AknLayoutDecodeSupport::MultiLineTextLine( txtLineLayImp2,
        &implData, 0, 0, 0, 0, 0 );
    _LIT( KTxtMultiLineTextLine,
        "AknLayoutDecodeSupport::MultiLineTextLine" );
    AssertTrueL( ETrue, KTxtMultiLineTextLine );

    AknLayoutDecodeSupport::MultiLineTextLine( txtLineLayImp2,
        &implData, rect, 0, 0, 0, 0, 0 );
    _LIT( KTxtMultiLineTextLine2,
        "AknLayoutDecodeSupport::MultiLineTextLine2" );
    AssertTrueL( ETrue, KTxtMultiLineTextLine2 );  

    implData.iDataLookup += 19;
    AknLayoutDecodeSupport::WindowTable( winLineLayImp2,
        &implData, 0, 0, 0, 0, 0, 0 );
    _LIT( KTxtWindowTable,
        "AknLayoutDecodeSupport::WindowTable" );
    AssertTrueL( ETrue, KTxtWindowTable );  

    AknLayoutDecodeSupport::WindowTable( winLineLayImp2,
        &implData, 0, rect, 0, 0, 0, 0, 0 );
    _LIT( KTxtWindowTable2,
        "AknLayoutDecodeSupport::WindowTable2" );
    AssertTrueL( ETrue, KTxtWindowTable2 );  

    AknLayoutDecodeSupport::TextTable( txtLineLayImp2,
        &implData, 0, 0, 0, 0, 0, 0 );
    _LIT( KTxtTextTable,
        "AknLayoutDecodeSupport::TextTable" );
    AssertTrueL( ETrue, KTxtTextTable );

    AknLayoutDecodeSupport::TextTable( txtLineLayImp2,
        &implData, 0, rect, 0, 0, 0, 0, 0 );
    _LIT( KTxtTextTable2,
        "AknLayoutDecodeSupport::TextTable2" );
    AssertTrueL( ETrue, KTxtTextTable2 );   

    TAknLayoutTableLimits layTableLims =
        AknLayoutDecodeSupport::TableLimits( implData.iDataLookup );
    _LIT( KTxtTableLimits,
        "AknLayoutDecodeSupport::TableLimits" );
    AssertTrueL( ETrue, KTxtTableLimits );    
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomLayoutSystemCase::TestLayout2HierarchyL
// ---------------------------------------------------------------------------
//
void CBCTestDomLayoutSystemCase::TestLayout2HierarchyL()
    {
    TAknLayoutHierarchyComponentHandle layHieComhnd(
        KUidAknLayoutSystemId_AknLayout2, 0xA00040A3, 1 );

    TAknLayoutScalableComponentType layScaComType = 
        AknLayout2Hierarchy::GetComponentType( layHieComhnd );
    _LIT( KTxtGetComponentType,
        "AknLayout2Hierarchy::GetComponentType" );
    AssertTrueL( ETrue, KTxtGetComponentType );   

    TAknLayoutScalableParameterLimits layScaParLim = 
        AknLayout2Hierarchy::GetParamLimits( layHieComhnd );
    _LIT( KTxtGetParamLimits,
        "AknLayout2Hierarchy::GetParamLimits" );
    AssertTrueL( ETrue, KTxtGetParamLimits );  

    TAknWindowComponentLayout winComLay = 
        AknLayout2Hierarchy::GetWindowComponentLayout( layHieComhnd );
    _LIT( KTxtGetWindowComponentLayout,
        "AknLayout2Hierarchy::GetWindowComponentLayout" );
    AssertTrueL( ETrue, KTxtGetWindowComponentLayout );  

    TAknTextComponentLayout txtComLay = 
        AknLayout2Hierarchy::GetTextComponentLayout( layHieComhnd );
    _LIT( KTxtGetTextComponentLayout,
        "AknLayout2Hierarchy::GetTextComponentLayout" );
    AssertTrueL( ETrue, KTxtGetTextComponentLayout );     
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomLayoutSystemCase::TestLayout2HierarchyDefL
// ---------------------------------------------------------------------------
//
void CBCTestDomLayoutSystemCase::TestLayout2HierarchyDefL()
    {
    TAknLayoutHierarchyComponentHandle layHieComhnd;
    _LIT( KTxtTAknLayoutHierarchyComponentHandle,
        "TAknLayoutHierarchyComponentHandle::\
        TAknLayoutHierarchyComponentHandle" );
    AssertTrueL( ETrue, KTxtTAknLayoutHierarchyComponentHandle );

    TAknLayoutHierarchyComponentHandle layHieComhnd2(
        KUidAknLayoutSystemId_AknLayout2, 0xA00040A3, 1 );
    _LIT( KTxtTAknLayoutHierarchyComponentHandle2,
        "TAknLayoutHierarchyComponentHandle::\
        TAknLayoutHierarchyComponentHandle2" );
    AssertTrueL( ETrue, KTxtTAknLayoutHierarchyComponentHandle2 ); 

    layHieComhnd.SetLayoutSystemId( 0x102832D1 );
    _LIT( KTxtSetLayoutSystemId,
        "TAknLayoutHierarchyComponentHandle::SetLayoutSystemId" );
    AssertTrueL( ETrue, KTxtSetLayoutSystemId ); 

    layHieComhnd.SetApiId( 0xA00040A3 );
    _LIT( KTxtSetApiId,
        "TAknLayoutHierarchyComponentHandle::SetApiId" );
    AssertTrueL( ETrue, KTxtSetApiId ); 

    layHieComhnd.SetComponentId( 1 );
    _LIT( KTxtSetComponentId,
        "TAknLayoutHierarchyComponentHandle::SetComponentId" );
    AssertTrueL( ETrue, KTxtSetComponentId ); 

    layHieComhnd.SetOptionIndex( 1 );
    _LIT( KTxtSetOptionIndex,
        "TAknLayoutHierarchyComponentHandle::SetOptionIndex" );
    AssertTrueL( ETrue, KTxtSetOptionIndex ); 

    layHieComhnd.SetVarietyIndex( 1 );
    _LIT( KTxtSetVarietyIndex,
        "TAknLayoutHierarchyComponentHandle::SetVarietyIndex" );
    AssertTrueL( ETrue, KTxtSetVarietyIndex ); 

    layHieComhnd.SetColumn( 2 );
    _LIT( KTxtSetColumn,
        "TAknLayoutHierarchyComponentHandle::SetColumn" );
    AssertTrueL( ETrue, KTxtSetColumn ); 

    layHieComhnd.SetRow( 2 );
    _LIT( KTxtSetRow,
        "TAknLayoutHierarchyComponentHandle::SetRow" );
    AssertTrueL( ETrue, KTxtSetRow ); 

    TInt ret = layHieComhnd.LayoutSystemId();
    _LIT( KTxtLayoutSystemId,
        "TAknLayoutHierarchyComponentHandle::LayoutSystemId" );
    AssertTrueL( ETrue, KTxtLayoutSystemId );

    ret = layHieComhnd.ApiId();
    _LIT( KTxtApiId,
        "TAknLayoutHierarchyComponentHandle::ApiId" );
    AssertTrueL( ETrue, KTxtApiId );

    ret = layHieComhnd.ComponentId();
    _LIT( KTxtComponentId,
        "TAknLayoutHierarchyComponentHandle::ComponentId" );
    AssertTrueL( ETrue, KTxtComponentId );

    ret = layHieComhnd.OptionIndex();
    _LIT( KTxtOptionIndex,
        "TAknLayoutHierarchyComponentHandle::OptionIndex" );
    AssertTrueL( ETrue, KTxtOptionIndex );

    ret = layHieComhnd.VarietyIndex();
    _LIT( KTxtVarietyIndex,
        "TAknLayoutHierarchyComponentHandle::VarietyIndex" );
    AssertTrueL( ETrue, KTxtVarietyIndex );

    ret = layHieComhnd.Column();
    _LIT( KTxtColumn,
        "TAknLayoutHierarchyComponentHandle::Column" );
    AssertTrueL( ETrue, KTxtColumn );

    ret = layHieComhnd.Row();
    _LIT( KTxtRow,
        "TAknLayoutHierarchyComponentHandle::Row" );
    AssertTrueL( ETrue, KTxtRow );    
    }
