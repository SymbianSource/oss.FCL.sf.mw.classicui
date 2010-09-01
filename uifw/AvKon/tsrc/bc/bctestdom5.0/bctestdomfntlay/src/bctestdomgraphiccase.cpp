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

#include <aknlayout2scalabledatadef.h>
#include <aknlayout2scalabledecode.h> 
#include <akniconconfig.h>

#include "bctestdomgraphiccase.h"
#include "bctestdomfntlaycontainer.h"
#include "bctestdomfntlay.hrh"

//constant variable define

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

0x01c0
};


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomGraphicCase* CBCTestDomGraphicCase::NewL()
    {
    CBCTestDomGraphicCase* self = new( ELeave ) CBCTestDomGraphicCase();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestDomGraphicCase::CBCTestDomGraphicCase()
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDomGraphicCase::~CBCTestDomGraphicCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomGraphicCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomGraphicCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestDomGraphicCase::BuildScriptL()
    { 
    // Add script as your need.   
    AddTestL( DELAY(1),
              LeftCBA, REP(Down,3), LeftCBA, REP(Down,4), LeftCBA,
              LeftCBA, REP(Down,3), LeftCBA, REP(Down,5), LeftCBA,
              TEND ); 
        
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomGraphicCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestDomGraphicCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestDomCmdOutline20 || aCmd > EBCTestDomCmdOutline21 )
        {
        return;
        }
        
    switch ( aCmd )
        {
        case EBCTestDomCmdOutline20: //AknLayout2ScalableDataDef.h 15
            {
            TestLayout2ScalableDataDefL();
            break;
            }
        case EBCTestDomCmdOutline21: //akniconconfig.h 4
            {
            TestIconconfigL();      
            break;
            }   
        default:
            break;
        }
         
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomGraphicCase::TestLayout2ScalableDataDefL
// ---------------------------------------------------------------------------
//
void CBCTestDomGraphicCase::TestLayout2ScalableDataDefL()
    {
    SCompDataImplData compData;
    compData.iDataLookup = KDataLookup;
    compData.iByteCodedData = KByteCodedData;

    TAknWindowComponentLayoutImp winComLayImp;        
    AknLayoutScalableDecodeSupport::WindowLine(
        winComLayImp, &compData );  
    _LIT( KTxtWindowLine,
        "AknLayoutScalableDecodeSupport::WindowLine" );
    AssertTrueL( ETrue, KTxtWindowLine );
    //  
    AknLayoutScalableDecodeSupport::WindowLine(
        winComLayImp, &compData, 0, 0, 0 );  
    _LIT( KTxtWindowLine2,
        "AknLayoutScalableDecodeSupport::WindowLine2" );
    AssertTrueL( ETrue, KTxtWindowLine2 );

    TAknTextComponentLayoutImp txtComLayImp;
    AknLayoutScalableDecodeSupport::TextLine( 
        txtComLayImp, &compData );  
    _LIT( KTxtTextLine,
        "AknLayoutScalableDecodeSupport::TextLine" );
    AssertTrueL( ETrue, KTxtTextLine );

    AknLayoutScalableDecodeSupport::TextLine( 
        txtComLayImp, &compData, 0, 0, 0 );  
    _LIT( KTxtTextLine2,
        "AknLayoutScalableDecodeSupport::TextLine2" );
    AssertTrueL( ETrue, KTxtTextLine2 );

    TAknWindowComponentLayoutImp winComLayImp3;
    AknLayoutScalableDecodeSupport::WindowTable( 
        winComLayImp3, &compData,1 );  
    _LIT( KTxtWindowTable,
        "AknLayoutScalableDecodeSupport::WindowTable" );
    AssertTrueL( ETrue, KTxtWindowTable );

    AknLayoutScalableDecodeSupport::WindowTable( 
        winComLayImp, &compData, 1, 0, 0, 0 );  
    _LIT( KTxtWindowTable2,
        "AknLayoutScalableDecodeSupport::WindowTable2" );
    AssertTrueL( ETrue, KTxtWindowTable2 );

    AknLayoutScalableDecodeSupport::TextTable( 
        txtComLayImp, &compData, 1 );  
    _LIT( KTxtTextTable,
        "AknLayoutScalableDecodeSupport::TextTable" );
    AssertTrueL( ETrue, KTxtTextTable );

    AknLayoutScalableDecodeSupport::TextTable( 
        txtComLayImp, &compData, 1, 0, 0, 0 );  
    _LIT( KTxtTextTable2,
        "AknLayoutScalableDecodeSupport::TextTable2" );
    AssertTrueL( ETrue, KTxtTextTable2 );

    TAknLayoutScalableTableLimits layScaTableLim = 
        AknLayoutScalableDecodeSupport::TableLimits( KDataLookup );    
    _LIT( KTxtTableLimits,
        "AknLayoutScalableDecodeSupport::TableLimits" );
    AssertTrueL( ETrue, KTxtTableLimits );

    TAknLayoutScalableParameterLimitsImp layScaParLim;
    AknLayoutScalableDecodeSupport::ParameterLimits( 
        layScaParLim, &compData, 0 );    
    _LIT( KTxtParameterLimits,
        "AknLayoutScalableDecodeSupport::ParameterLimits" );
    AssertTrueL( ETrue, KTxtParameterLimits );

    AknLayoutScalableDecodeSupport::ParameterLimitsTable( 
        layScaParLim, &compData, 1, 0 );    
    _LIT( KTxtParameterLimitsTable,
        "AknLayoutScalableDecodeSupport::ParameterLimitsTable" );
    AssertTrueL( ETrue, KTxtParameterLimitsTable );

    TAknLayoutScalableComponentType layScaComType;
    AknLayoutScalableDecodeSupport::GetComponentTypeById( 
        layScaComType, &compData, 1 );    
    _LIT( KTxtGetComponentTypeById,
        "AknLayoutScalableDecodeSupport::GetComponentTypeById" );
    AssertTrueL( ETrue, KTxtGetComponentTypeById );

    TAknLayoutScalableParameterLimitsImp layScaParmImp;
    AknLayoutScalableDecodeSupport::GetParamLimitsById( 
        layScaParmImp, &compData, 1, 0 );    
    _LIT( KTxtGetParamLimitsById,
        "AknLayoutScalableDecodeSupport::GetParamLimitsById" );
    AssertTrueL( ETrue, KTxtGetParamLimitsById );

    TAknWindowComponentLayoutImp winComLayImp2;
    AknLayoutScalableDecodeSupport::GetWindowComponentById( 
        winComLayImp2, &compData, 1, 0, 0, 0 );    
    _LIT( KTxtGetWindowComponentById,
        "AknLayoutScalableDecodeSupport::GetWindowComponentById" );
    AssertTrueL( ETrue, KTxtGetWindowComponentById );

    TAknTextComponentLayoutImp txtComLayImp2;
    AknLayoutScalableDecodeSupport::GetTextComponentById( 
        txtComLayImp2, &compData, 18, 0, 0, 0 );    
    _LIT( KTxtGetTextComponentById,
        "AknLayoutScalableDecodeSupport::GetTextComponentById" );
    AssertTrueL( ETrue, KTxtGetTextComponentById );    
    }

// ---------------------------------------------------------------------------
// CBCTestDomGraphicCase::TestIconconfigL
// ---------------------------------------------------------------------------
//
void CBCTestDomGraphicCase::TestIconconfigL()
    {
    AknIconConfig::TPreferredDisplayMode preDisMode;
    AknIconConfig::PreferredDisplayMode( preDisMode,
        AknIconConfig::EImageTypeIcon );
    _LIT( KTxtPreferredDisplayMode,
        "AknIconConfig::PreferredDisplayMode" );
    AssertTrueL( ETrue, KTxtPreferredDisplayMode );

    CFbsBitmap* bitmap = new ( ELeave ) CFbsBitmap();
    CleanupStack::PushL( bitmap );
    AknIconConfig::CompressIfPreferred( bitmap );
    _LIT( KTxtCompressIfPreferred,
        "AknIconConfig::CompressIfPreferred" );
    AssertTrueL( ETrue, KTxtCompressIfPreferred );

    CFbsBitmap* maskBitmap = new ( ELeave ) CFbsBitmap();
    CleanupStack::PushL( maskBitmap );
    AknIconConfig::CompressIfPreferred( bitmap, maskBitmap );
    _LIT( KTxtCompressIfPreferred2,
        "AknIconConfig::CompressIfPreferred2" );
    AssertTrueL( ETrue, KTxtCompressIfPreferred2 );

    AknIconConfig::EnableAknIconSrvCache( ETrue );
    _LIT( KTxtEnableAknIconSrvCache,
        "AknIconConfig::EnableAknIconSrvCache" );
    AssertTrueL( ETrue, KTxtEnableAknIconSrvCache );

    CleanupStack::PopAndDestroy ( maskBitmap );
    CleanupStack::PopAndDestroy ( bitmap );    
    }

