/*
* Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Grid handling the list functionality in fast application swap.
*
*/

// INCLUDE FILES
#include <aknlayoutscalable_avkon.cdl.h>
#include <AknLayout2ScalableDef.h>
#include "AknFastswapWindowGrid.h"
#include "AknFastswapWindowControl.h"
#include "aknlists.h"
#include "AknsUtils.h"
#include "akntrace.h"

// ---------------------------------------------------------
// CAknFastSwapWindowGrid::SizeChanged
// ---------------------------------------------------------
//
void CAknFastSwapWindowGrid::SizeChanged()
    {
    _AKNTRACE_FUNC_ENTER;
    CAknGrid::SizeChanged();

    // this code assumes that Rect() returns the correct rect
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect( Rect(), AknLayoutScalable_Avkon::cell_fast2_pane( 0, 0).LayoutLine() );
    
    TRect cellRect( layoutRect.Rect() );

    View()->ItemDrawer()->SetItemCellSize( cellRect.Size() );
    TRAP_IGNORE( SetItemHeightL( cellRect.Height() ) );

    TPoint empty( ELayoutEmpty, ELayoutEmpty );

    // icon
    //CEikFormattedCellListBox &listBox = *this;
    AknListBoxLayouts::SetupFormGfxCell( 
        *this, 
        ItemDrawer(), 
        0,
        AknLayoutScalable_Avkon::cell_fast2_pane_g3().LayoutLine(),
        empty, 
        empty );   
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// Updates the scrollbar of the fast swap window.
// ---------------------------------------------------------------------------
//
void CAknFastSwapWindowGrid::UpdateScrollBarsL()
    {
    _AKNTRACE_FUNC_ENTER;
    // Overriding CAknGrid::UpdateScrollBarsL()

    // Use TAknDoubleSpanScrollBarModel instead of TEikScrollBarModel.
    TAknDoubleSpanScrollBarModel vSbarModel;

    TInt logicalRow;
    TInt logicalColumn;
    CAknGridView* gridView = GridView();
    gridView->LogicalPosFromListBoxIndex( CurrentDataIndex(),
                                            logicalRow,
                                            logicalColumn );
    logicalRow *= gridView->ItemHeight();
    logicalRow -= gridView->ItemOffsetInPixels();
    
    // Direct manipulation with the variables is not allowed in
    // TAknDoubleSpanScrollBarModel.
    vSbarModel.SetScrollSpan(
        gridView->GridCellDimensions().iHeight * gridView->ItemHeight() );
    vSbarModel.SetWindowSize( gridView->ViewRect().Height() );
    vSbarModel.SetFocusPosition( logicalRow );
    
    ScrollBarFrame()->Tile( &vSbarModel );    
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------
// CAknFastSwapWindowGrid::HandlePointerEventL
// parent CAknGrid handle changing highlight item and open app when tap a highlight item
// and handle draging scroll bar
// ---------------------------------------------------------
//
void CAknFastSwapWindowGrid::HandlePointerEventL(const TPointerEvent &aPointerEvent)
    {
    CAknGrid::HandlePointerEventL(aPointerEvent);
    }

// ---------------------------------------------------------
// CAknFastSwapWindowGrid::CreateItemDrawerL
// Item drawer construction
// ---------------------------------------------------------
//
void CAknFastSwapWindowGrid::CreateItemDrawerL()
    {
    _AKNTRACE_FUNC_ENTER;
    CAknGrid::CreateItemDrawerL();
    // Let the FSW background context control the grid skinning
    ItemDrawer()->FormattedCellData()->SetSkinEnabledL( EFalse );
    _AKNTRACE_FUNC_EXIT;
    }

// ---------------------------------------------------------
// CAknFastSwapWindowGrid::SetupStandardGrid
// Itemdrawer border and color setup
//
// ---------------------------------------------------------
//
void CAknFastSwapWindowGrid::SetupStandardGrid()
    {
    _AKNTRACE_FUNC_ENTER;
    // text colors according LAF (without skin)
    TAknLayoutText layoutText;
    layoutText.LayoutText( 
        Rect(), 
        AknLayoutScalable_Avkon::cell_app_pane_cp2_t1( 0 ).LayoutLine() );

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    TRgb textColor;
    TRgb textColorHighlight;

    // sets the color according the skin LAF
    TInt error = AknsUtils::GetCachedColor( 
        skin, 
        textColor, 
        KAknsIIDQsnTextColors, 
        EAknsCIQsnTextColorsCG9 );

    if ( error != KErrNone )
        {
        textColor = layoutText.Color();
        }

    error = AknsUtils::GetCachedColor( 
        skin, 
        textColorHighlight, 
        KAknsIIDQsnTextColors, 
        EAknsCIQsnTextColorsCG11 );

    if ( error != KErrNone )
        {
        textColorHighlight = layoutText.Color();
        }

    SetBorder( TGulBorder::ENone );
    ItemDrawer()->SetTextColor( textColor );
    ItemDrawer()->SetBackColor( AKN_LAF_COLOR( 0 ) );

    ItemDrawer()->SetHighlightedTextColor( textColorHighlight );
    ItemDrawer()->SetHighlightedBackColor( AKN_LAF_COLOR( 0 ) );
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CAknFastSwapWindowGrid::CEikListBox_Reserved()
    {
    }

//  End of File
