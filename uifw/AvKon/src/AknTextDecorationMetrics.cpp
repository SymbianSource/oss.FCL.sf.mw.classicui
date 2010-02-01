/*
* Copyright (c) 2004 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Series 60 text layout metrics
*
*/


// INCLUDE FILES

#include <CdlRefs.h>
#include <avkon.hrh>
#include <gdi.h>
#include <aknenv.h>
#include <aknlayout.cdl.h>
#include <aknappui.h>
#include <aknlayoutscalable_avkon.cdl.h> // Scalable layout API
#include <AknUtils.h>
#include <AknLayout2ScalableDef.h>

#include "AknTextDecorationMetrics.h"
#include <AknFontSpecification.h>
#include <AknLayoutFont.h>

// CONSTANTS

/** 
* constants for setting defaults from screensize
* Some of these are currently estimated using magic numbers:
* - underline thickness
* - underline position
*/

const TInt KUnderLineScreenHeight(400);


//========================== MEMBER FUNCTIONS ===============================

EXPORT_C TAknTextDecorationMetrics::TAknTextDecorationMetrics( TInt aFontId )
    {
    TAknFontSpecification spec( aFontId );
    SetMetricsFromSizeAndBoldness( spec.FontCategory(), spec.TextPaneHeight(), spec.Weight() == EStrokeWeightBold );
    }

EXPORT_C TAknTextDecorationMetrics::TAknTextDecorationMetrics( const CFont* aFont )
    {
    if ( aFont )
        {
        TBool isBold = ( aFont->FontSpecInTwips().iFontStyle.StrokeWeight() != EStrokeWeightNormal );       
        const CAknLayoutFont* aknFont = CAknLayoutFont::AsCAknLayoutFontOrNull( aFont );
        if ( aknFont )
            {
            SetMetricsFromSizeAndBoldness( aknFont->FontCategory(), aknFont->TextPaneHeight(), isBold );              
            }
        else
            {
            SetMetricsFromSizeAndBoldness( EAknFontCategoryUndefined, aFont->FontMaxHeight(), isBold );            
            }
        }
    else
        {
        SetDefaultMetrics( EAknFontCategoryUndefined, EFalse);
        }
    }

EXPORT_C TAknTextDecorationMetrics::TAknTextDecorationMetrics( const TAknFontSpecification& aSpecification )
    {
    TBool isBold = ( aSpecification.Weight() != EStrokeWeightNormal );
    SetMetricsFromSizeAndBoldness( aSpecification.FontCategory(), aSpecification.TextPaneHeight(), isBold );
    }

EXPORT_C void TAknTextDecorationMetrics::GetLeftAndRightMargins( TInt& aLeft, TInt& aRight ) const
    {
    aLeft = iLeftMargin;
    aRight = iRightMargin;
    }

EXPORT_C void TAknTextDecorationMetrics::GetTopAndBottomMargins( TInt&  aTop, TInt& aBottom ) const
    {
    aTop = iTopMargin;
    aBottom = iBottomMargin;
    }

EXPORT_C TInt TAknTextDecorationMetrics::CursorWidth() const
    {
    return iCursorWidth;
    }

EXPORT_C TInt TAknTextDecorationMetrics::BaselineToUnderlineOffset() const
    {
    return iBaselineToUnderlineOffset;
    }

EXPORT_C TInt TAknTextDecorationMetrics::UnderlineHeight() const
    {
    return iUnderlineHeight;
    }

void TAknTextDecorationMetrics::SetMetricsFromSizeAndBoldness( TAknFontCategory aCategory, TInt /*aHeight*/, TBool aIsBold )
    {
    // Currently font height independent
    SetDefaultMetrics( aCategory, aIsBold );
    }

void TAknTextDecorationMetrics::SetDefaultMetrics( TAknFontCategory aCategory, TBool /*aIsBold*/ )
    {
    // Use screen for parent of the highlight and cursor layouts 
    TRect screen = iAvkonAppUi->ApplicationRect();
  
    TAknWindowComponentLayout highlightParentPane;
    TAknTextComponentLayout highlightTextPane;
    TAknWindowComponentLayout highlightPane;

    GetHighlightLayoutsFromCategory( aCategory, highlightParentPane, highlightTextPane, highlightPane );

    TAknWindowLineLayout highlightParentWindowLayout = highlightParentPane.LayoutLine();
    TAknWindowLineLayout highlightWindowLayout = highlightPane.LayoutLine();
    TAknTextLineLayout highlightTextLayout = highlightTextPane.LayoutLine();
           
    // Parent is positioned in the screen. This misses out 2 levels of the layout, but 
    // these are (and are necessarily so) dummy layers which cannot supply any real info.
    TAknLayoutRect highlightParentRect;
    highlightParentRect.LayoutRect( screen, highlightParentWindowLayout );       
    // two subcomponents are positioned in the parent:
    TAknLayoutRect highlightLayoutRect;
    highlightLayoutRect.LayoutRect( highlightParentRect.Rect(), highlightWindowLayout );       
    TAknLayoutText highlightLayoutText;
    highlightLayoutText.LayoutText( highlightParentRect.Rect(), highlightTextLayout, NULL );    
    
    TRect textRect = highlightLayoutText.TextRect();
    TRect highlightRect = highlightLayoutRect.Rect();
    TRect parentRect = highlightParentRect.Rect();
    
    iTopMargin =  textRect.iTl.iY - highlightRect.iTl.iY;
    iBottomMargin = highlightRect.iBr.iY - textRect.iBr.iY;
    iLeftMargin =  textRect.iTl.iX - parentRect.iTl.iX;
    iRightMargin = parentRect.iBr.iX - textRect.iBr.iX;
    
    // Cursor and underlines
    TInt screenWidth = screen.Width();
    TInt screenHeight = screen.Height();

    TAknWindowComponentLayout cursorLayout;
    TAknWindowComponentLayout cursorLayoutGraphic;
    GetCursorLayoutsFromCategory( aCategory, cursorLayout, cursorLayoutGraphic );

    TAknWindowLineLayout graphic = TAknWindowComponentLayout::Compose(cursorLayout, cursorLayoutGraphic).LayoutLine();
    TAknLayoutRect cursor;
    cursor.LayoutRect( screen, graphic );
    iCursorWidth = cursor.Rect().Width();

    //if screen height < 400, underline height is 1, else is 2 pixel;
    iUnderlineHeight = (TInt8) ( screenHeight <= KUnderLineScreenHeight ? 1 : 2 );

    iBaselineToUnderlineOffset = (TInt8) (Max(iBottomMargin,1) + iUnderlineHeight);
    }

void TAknTextDecorationMetrics::GetHighlightLayoutsFromCategory( 
    TAknFontCategory aCategory,
    TAknWindowComponentLayout& aHighlightParentPane,
    TAknTextComponentLayout& aHighlightTextPane,
    TAknWindowComponentLayout& aHighlightPane ) const
    {
        
    switch( aCategory )
        {
        case (EAknFontCategoryPrimarySmall):
        aHighlightParentPane = 
            AknLayoutScalable_Avkon::copy_highlight_primary_small_pane();
        aHighlightTextPane = 
            AknLayoutScalable_Avkon::copy_highlight_primary_small_pane_t1(); 
        aHighlightPane = 
        AknLayoutScalable_Avkon::copy_highlight_primary_small_pane_g1();
        break;
        
        case (EAknFontCategorySecondary):
        aHighlightParentPane = 
            AknLayoutScalable_Avkon::copy_highlight_secondary_pane();
        aHighlightTextPane = 
            AknLayoutScalable_Avkon::copy_highlight_secondary_pane_t1(); 
        aHighlightPane = 
        AknLayoutScalable_Avkon::copy_highlight_secondary_pane_g1();
        break;
        
        case (EAknFontCategoryTitle):
        aHighlightParentPane = 
            AknLayoutScalable_Avkon::copy_highlight_title_pane();
        aHighlightTextPane = 
            AknLayoutScalable_Avkon::copy_highlight_title_pane_t1(); 
        aHighlightPane = 
        AknLayoutScalable_Avkon::copy_highlight_title_pane_g1();
        break;
        
        case (EAknFontCategoryDigital):
        aHighlightParentPane = 
            AknLayoutScalable_Avkon::copy_highlight_digital_pane();
        aHighlightTextPane = 
            AknLayoutScalable_Avkon::copy_highlight_digital_pane_t1(); 
        aHighlightPane = 
        AknLayoutScalable_Avkon::copy_highlight_digital_pane_g1();
        break;
        
        case (EAknFontCategoryPrimary): // Fall through
        default: // Use Primary for all other cases
        aHighlightParentPane = 
            AknLayoutScalable_Avkon::copy_highlight_primary_pane();
        aHighlightTextPane = 
            AknLayoutScalable_Avkon::copy_highlight_primary_pane_t1(); 
        aHighlightPane = 
        AknLayoutScalable_Avkon::copy_highlight_primary_pane_g1();
        }
    }
    
void TAknTextDecorationMetrics::GetCursorLayoutsFromCategory( 
    TAknFontCategory aCategory,
    TAknWindowComponentLayout& aCursorLayout,
    TAknWindowComponentLayout& aCursorLayoutGraphic ) const
    {
    switch( aCategory )
        {
        case (EAknFontCategoryPrimarySmall):
        aCursorLayout = AknLayoutScalable_Avkon::cursor_primary_small_pane();
        aCursorLayoutGraphic = AknLayoutScalable_Avkon::cursor_primary_small_pane_g1();       
        break;
        
        case (EAknFontCategorySecondary):
        aCursorLayout = AknLayoutScalable_Avkon::cursor_secondary_pane();
        // secondary uses primary small g1
        aCursorLayoutGraphic = AknLayoutScalable_Avkon::cursor_primary_small_pane_g1();       
        break;

        case (EAknFontCategoryTitle):
        aCursorLayout = AknLayoutScalable_Avkon::cursor_title_pane();
        aCursorLayoutGraphic = AknLayoutScalable_Avkon::cursor_title_pane_g1();       
        break;

        case (EAknFontCategoryDigital):
        aCursorLayout = AknLayoutScalable_Avkon::cursor_digital_pane();
        aCursorLayoutGraphic = AknLayoutScalable_Avkon::cursor_digital_pane_g1();       
        break;
        
        case (EAknFontCategoryPrimary): // Fall through
        default:   // Others default to primary
        aCursorLayout = AknLayoutScalable_Avkon::cursor_primary_pane();
        aCursorLayoutGraphic = AknLayoutScalable_Avkon::cursor_primary_pane_g1();       
        }
    }
 
//  End of File
