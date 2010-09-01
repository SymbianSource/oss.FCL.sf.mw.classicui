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
#include <akncolourselectiongrid.h>
#include <akngmsstylegrid.h>
#include <bctestgrids.rsg>

#include "bctestforcolourandgms.h"
#include "bctestgridscontainer.h"
#include "bctestgrids.hrh"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestForColourAndGms* CBCTestForColourAndGms::NewL( 
    CBCTestGridsContainer* aContainer )
    {
    CBCTestForColourAndGms* self = new( ELeave ) CBCTestForColourAndGms( 
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
CBCTestForColourAndGms::CBCTestForColourAndGms( 
    CBCTestGridsContainer* aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestForColourAndGms::~CBCTestForColourAndGms()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestForColourAndGms::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestForColourAndGms::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestForColourAndGms::BuildScriptL()
    { 
    // Add script as your need.   
    AddTestL( LeftCBA, LeftCBA, KeyOK, LeftCBA, TEND );
    AddTestL( LeftCBA, KeyOK, Down, KeyOK, TEND );   
    }
    
// ---------------------------------------------------------------------------
// CBCTestForColourAndGms::RunL
// ---------------------------------------------------------------------------
//
void CBCTestForColourAndGms::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdEmptyOutline || aCmd > EBCTestCmdMaxOutline )
        {
        return;
        }

    switch ( aCmd )  
        {
        case EBCTestForColour:
            TestColourSelectionGridL();
            break;
        case EBCTestForGms:
            TestAknGmsStyleGridL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestForColourAndGms::TestColourSelectionGridL
// ---------------------------------------------------------------------------
//    
void CBCTestForColourAndGms::TestColourSelectionGridL()
    {
    // Test some API here
    CArrayFixFlat<TRgb>* array = new( ELeave ) CArrayFixFlat<TRgb>(1);
    CleanupStack::PushL( array );
    TRgb rgb = ( KRgbRed, KRgbGreen, KRgbBlue );
    array->AppendL( rgb );
    TBool noneChosen = ETrue;
    CAknColourSelectionGrid* colourSelectionGrid = 
        CAknColourSelectionGrid::NewL( array, ETrue, noneChosen, rgb );
    CleanupStack::PushL( colourSelectionGrid );
    _LIT( KNewL, "NewL for CAknColourSelectionGrid test" );
    AssertTrueL( ETrue, KNewL );
    
    TBool executeLD = colourSelectionGrid->ExecuteLD();
    _LIT( KExecuteLD, "ExecuteLD for CAknColourSelectionGrid test" );
    AssertTrueL( ETrue, KExecuteLD);
    
    CleanupStack::Pop( colourSelectionGrid );
    _LIT( KDesCAknColourSelectionGrid, 
        "~CAknColourSelectionGrid for CAknColourSelectionGrid test" );
    AssertTrueL( ETrue, KDesCAknColourSelectionGrid);
    
    CleanupStack::PopAndDestroy( array );
    
    }
// ---------------------------------------------------------------------------
// CBCTestForColourAndGms::TestCAknGMSStyleGridViewL
// ---------------------------------------------------------------------------
// 
void CBCTestForColourAndGms::TestCAknGMSStyleGridViewL()
    {
    CAknGMSStyleGridView* gridView = 
        new( ELeave ) CAknGMSStyleGridView();
    CleanupStack::PushL( gridView );
    _LIT( KTestCAknGMSStyleGridView, "TestCAknGMSStyleGridView test" );
    AssertTrueL( ETrue, KTestCAknGMSStyleGridView );
   
    _LIT( KDraw, "Draw For CAknGMSStyleGridView test" );
    AssertTrueL( ETrue, KDraw );
    
    TRect rect = iContainer->Rect();
    gridView->SetupLayout( rect, EFalse, -1 );
    _LIT( KSetupLayout, "SetupLayout test" );
    AssertTrueL( ETrue, KSetupLayout );
    
    CleanupStack::PopAndDestroy( gridView );
    }

// ---------------------------------------------------------------------------
// CBCTestForColourAndGms::TestCAknGMSStyleGridL
// ---------------------------------------------------------------------------
//     
void CBCTestForColourAndGms::TestCAknGMSStyleGridL()
    {
    CAknGMSStyleGrid* styleGrid = 
        CAknGMSStyleGrid::NewL( iContainer, EFalse );
    CleanupStack::PushL( styleGrid );
    _LIT( KNewL, "NewL For CAknGMSStyleGrid test" );
    AssertTrueL( ETrue, KNewL );
    
    _LIT( KCAknGMSStyleGrid, "CAknGMSStyleGrid test" );
    AssertTrueL( ETrue, KCAknGMSStyleGrid ); 
    
    _LIT( KCAknGMSStyleGrid2, "CAknGMSStyleGrid( TBool ) test" );
    AssertTrueL( ETrue, KCAknGMSStyleGrid2 ); 
    
    _LIT( KConstructL, "ConstructL For CAknGMSStyleGrid test" );
    AssertTrueL( ETrue, KConstructL ); 
    
    styleGrid->SetupLayout();
    _LIT( KSetupLayout, "SetupLayout For CAknGMSStyleGrid test" );
    AssertTrueL( ETrue, KSetupLayout ); 
    
    TPointerEvent pointerEvent = 
        { TPointerEvent::EButton1Up, EModifierAutorepeatable, 
        TPoint( 20, 20 ), TPoint( 0, 0 ) };
    styleGrid->HandlePointerEventL( pointerEvent ); 
    _LIT( KHandlePointerEventL, 
        "HandlePointerEventL For CAknGMSStyleGrid test" );
    AssertTrueL( ETrue, KHandlePointerEventL ); 
    
    styleGrid->SizeChanged();
    _LIT( KSizeChanged, "SizeChanged For CAknGMSStyleGrid test" );
    AssertTrueL( ETrue, KSizeChanged ); 
    
    TSize minimumSize = styleGrid->MinimumSize();
    _LIT( KMinimumSize, "MinimumSize For CAknGMSStyleGrid test" );
    AssertTrueL( ETrue, KMinimumSize ); 
    
    TKeyEvent keyEvent = { EKeyPause, EStdKeySpace, 0, 0  };
    TKeyResponse response = styleGrid->OfferKeyEventL( keyEvent, 
        EEventNull );
    _LIT( KOfferKeyEventL, "OfferKeyEventL For CAknGMSStyleGrid test" );
    AssertTrueL( ETrue, KOfferKeyEventL ); 
    
    TRect rect = iContainer->Rect();
    styleGrid->Draw( rect );
    _LIT( KDraw, "Draw For CAknGMSStyleGrid test" );
    AssertTrueL( ETrue, KDraw );
    
    CListBoxView* listBoxView = styleGrid->MakeViewClassInstanceL();
    CleanupStack::PushL( listBoxView );
    _LIT( KMakeViewClassInstanceL, 
        "MakeViewClassInstanceL For CAknGMSStyleGrid test" );
    AssertTrueL( ETrue, KMakeViewClassInstanceL );
    CleanupStack::PopAndDestroy( listBoxView );
    
    CleanupStack::PopAndDestroy( styleGrid );
    _LIT( KDesCAknGMSStyleGrid, "~CAknGMSStyleGrid test" );
    AssertTrueL( ETrue, KDesCAknGMSStyleGrid ); 
    
    CAknGMSStyleGrid* styleGridForBlock = 
        CAknGMSStyleGrid::NewL( iContainer, ETrue );
    CleanupStack::PushL( styleGridForBlock );
    
    styleGridForBlock->SizeChanged();
    minimumSize = styleGridForBlock->MinimumSize();
    
    CleanupStack::PopAndDestroy( styleGridForBlock );   
    }

// ---------------------------------------------------------------------------
// CBCTestForColourAndGms::TestCAknGMSPopupGridL
// ---------------------------------------------------------------------------
//       
void CBCTestForColourAndGms::TestCAknGMSPopupGridL()
    {
    CAknGMSStyleGrid* styleGrid = 
        CAknGMSStyleGrid::NewL( iContainer, EFalse );
    CleanupStack::PushL( styleGrid );
    CAknGMSPopupGrid* popupGrid = CAknGMSPopupGrid::NewL( styleGrid, 
        R_BCTESTGRIDS_CBA_OPTIONS_NEXT, AknPopupLayouts::EMenuWindow );
    CleanupStack::PushL( popupGrid );
    _LIT( KCAknGMSPopupGrid, "CAknGMSPopupGrid test" );
    AssertTrueL( ETrue, KCAknGMSPopupGrid ); 
    
    popupGrid->SetupWindowLayout( AknPopupLayouts::EMenuWindow );
    popupGrid->SetupWindowLayout( AknPopupLayouts::EMenuGraphicWindow );
    popupGrid->SetupWindowLayout( AknPopupLayouts::EMenuGraphicHeadingWindow );
    popupGrid->SetupWindowLayout( AknPopupLayouts::EMenuDoubleWindow );
    popupGrid->SetupWindowLayout( 
        AknPopupLayouts::EMenuDoubleLargeGraphicWindow );
    popupGrid->SetupWindowLayout( AknPopupLayouts::EPopupSNotePopupWindow );
    popupGrid->SetupWindowLayout( 
        AknPopupLayouts::EMenuUnknownColumnWindow );
    popupGrid->SetupWindowLayout( 
        AknPopupLayouts::EMenuUnknownFormattedCellWindow );
    popupGrid->SetupWindowLayout( AknPopupLayouts::EMenuDoubleWindow );
    
    _LIT( KSetupWindowLayout, 
        "SetupWindowLayout For CAknGMSPopupGrid test" );
    AssertTrueL( ETrue, KSetupWindowLayout ); 
    
    TAknPopupWindowLayoutDef def;
    TRect rect = iContainer->Rect();
    TInt lines = 1;
    popupGrid->CalcPopupGridLargeGraphicWindow( def, rect, lines );
    _LIT( KCalcPopupGridLargeGraphicWindow, 
        "CalcPopupGridLargeGraphicWindow For CAknGMSPopupGrid test" );
    AssertTrueL( ETrue, KCalcPopupGridLargeGraphicWindow ); 
    
    popupGrid->SetupPopupGridLargeGraphicWindow( def, lines, ETrue ); 
	_LIT( KSetupPopupGridLargeGraphicWindow, 
	    "SetupPopupGridLargeGraphicWindow test" );
    AssertTrueL( ETrue, KSetupPopupGridLargeGraphicWindow ); 
    
    popupGrid->PopupGridLargeGraphicGraphics( def );
    _LIT( KPopupGridLargeGraphicGraphics, 
        "PopupGridLargeGraphicGraphics test" );
    AssertTrueL( ETrue, KPopupGridLargeGraphicGraphics );			    
    
    TPointerEvent pointerEvent = 
        { TPointerEvent::EButton1Up, EModifierAutorepeatable, 
        TPoint( 20, 20 ), TPoint( 0, 0 ) };
    popupGrid->HandlePointerEventL( pointerEvent );
    _LIT( KHandlePointerEventL, 
        "HandlePointerEventL For CAknGMSPopupGrid test" );
    AssertTrueL( ETrue, KHandlePointerEventL ); 
       
    CleanupStack::PopAndDestroy( popupGrid );
    CleanupStack::PopAndDestroy( styleGrid );
    }
// ---------------------------------------------------------------------------
// CBCTestForColourAndGms::TestakngmsstylegridL
// ---------------------------------------------------------------------------
//    
void CBCTestForColourAndGms::TestAknGmsStyleGridL()
    {
    TestCAknGMSStyleGridViewL();
    TestCAknGMSStyleGridL();
    TestCAknGMSPopupGridL();
    }
