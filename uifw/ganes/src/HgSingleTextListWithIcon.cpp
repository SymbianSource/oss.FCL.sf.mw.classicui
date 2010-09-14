/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:
*
*/

#include <ganes/HgSingleTextListWithIcon.h>
#include <ganes/HgItem.h>
#include "HgMarquee.h"
#include "HgLayoutData.h"
#include "HgIndicatorManager.h"
#include "HgDrawUtils.h"
#include "HgScrollbar.h"

#include <AknsUtils.h>
#include <AknUtils.h>
#include <AknsDrawUtils.h>

#include <layoutmetadata.cdl.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <gulicon.h>

using namespace AknLayoutScalable_Avkon;

// -----------------------------------------------------------------------------
// CHgSingleTextListWithIcon::NewL()
// -----------------------------------------------------------------------------
//
EXPORT_C CHgSingleTextListWithIcon* CHgSingleTextListWithIcon::NewL(
        const TRect& aRect, 
        TInt aItemCount, 
        CGulIcon* aDefaultIcon,
        RWsSession* aSession)
    {
    CHgSingleTextListWithIcon* self = new ( ELeave ) CHgSingleTextListWithIcon( 
            aItemCount, 
            aDefaultIcon );

    CleanupStack::PushL (self );
    self->ConstructL( aRect, aSession );
    CleanupStack::Pop (self );
    return self;
    }

// -----------------------------------------------------------------------------
// CHgSingleTextListWithIcon::~CHgSingleTextListWithIcon()
// -----------------------------------------------------------------------------
//
EXPORT_C CHgSingleTextListWithIcon::~CHgSingleTextListWithIcon( )
    {
    delete iGraphicLayoutData;
    }

// -----------------------------------------------------------------------------
// CHgSingleTextListWithIcon::HandleSizeChanged()
// -----------------------------------------------------------------------------
//
void CHgSingleTextListWithIcon::HandleSizeChanged()
    {
    // Init layout for the graphic item
    iGraphicLayoutData->SetItemLayout(list_single_graphic_pane( 0 ));
    iGraphicLayoutData->SetIconLayout(list_single_graphic_pane_g1( 2 ));
    for(TInt i = 0; i <= KMaxNumberOfTitleIndicators; ++i)
        iGraphicLayoutData->SetTitleLayout( i, list_single_graphic_pane_t1( i ));
    iGraphicLayoutData->SetFirstIndicatorLayout(list_single_graphic_pane_g3(0));
    TInt variety = iScrollbar && !iScrollbar->IsStatic() ? 1 : 0;
    iGraphicLayoutData->SetSecondIndicatorLayout(list_single_graphic_pane_g2(variety));

    // Get the Row rect.
    TAknLayoutRect layout;
    layout.LayoutRect(ListRect(), iGraphicLayoutData->ItemLayout());

    // Icon rect.
    TAknLayoutRect image;
    image.LayoutRect(layout.Rect(), iLayoutData->IconLayout());
    iImageSize = image.Rect().Size();

    // Call base implementation
    CHgSingleTextList::HandleSizeChanged();    
    }

// -----------------------------------------------------------------------------
// CHgSingleTextListWithIcon::DrawItem()
// -----------------------------------------------------------------------------
//
void CHgSingleTextListWithIcon::DrawItem( TInt aIndex, const TRect& aRect ) const
    {
    // Get the Icon
    CHgItem* item = iItems[aIndex];
    if( !item->Icon() )
        {
        // Let single text list handle the normal item drawing.
        CHgSingleTextList::DrawItem( aIndex, aRect );
        return;
        }
            
    // Highlight the row if it's selected
    TInt indicators = CHgIndicatorManager::CountIndicators(item->Flags());
    
    CWindowGc& gc = SystemGc();
    
    TRgb color = iColor;
    if( aIndex == iSelectedIndex )
        {
        DrawHighlight( aRect, color );
        
        // Draw first line text
        iDrawUtils->DrawTextMarquee(
                gc,
                aRect, 
                iGraphicLayoutData->TitleLayout(indicators),
                item->Title(),
                color, 0);
        
        ResetClippingRect( gc );
        }
    else
        {
        // Draw first line text
        iDrawUtils->DrawText(
                gc,
                aRect, 
                iGraphicLayoutData->TitleLayout(indicators),
                item->Title(),
                color);
        }

    iDrawUtils->DrawImage(gc, aRect, iGraphicLayoutData->IconLayout(), *item->Icon() );
    
    // Draw the indicators.
    iIndicatorManager->DrawIndicators(
            gc,
            aRect, 
            item->Flags(), 
            iGraphicLayoutData->FirstIndicatorLayout(), 
            iGraphicLayoutData->SecondIndicatorLayout(),
            iFlags & EHgScrollerSelectionMode || iSelectionMode != ENoSelection );  
   }

// -----------------------------------------------------------------------------
// CHgSingleTextListWithIcon::CHgSingleTextList()
// -----------------------------------------------------------------------------
//
CHgSingleTextListWithIcon::CHgSingleTextListWithIcon( TInt aItemCount, 
                                      CGulIcon* aDefaultIcon )
: CHgSingleTextList( aItemCount, aDefaultIcon )
    {
    SetFlags( EHgScrollerFlatStatusPane ); // Set Flat status pane on
    }

// -----------------------------------------------------------------------------
// CHgSingleTextListWithIcon::CHgSingleTextList()
// -----------------------------------------------------------------------------
//
void CHgSingleTextListWithIcon::ConstructL( const TRect& aRect, RWsSession* aSession )
    {
    iGraphicLayoutData = CHgListLayoutData::NewL();
    CHgList::ConstructL( aRect, aSession );
    }

// -----------------------------------------------------------------------------
// CHgSingleTextListWithIcon::HandleScrollbarVisibilityChange()
// -----------------------------------------------------------------------------
//
void CHgSingleTextListWithIcon::HandleScrollbarVisibilityChange( TBool aVisible )
    {
    CHgSingleTextList::HandleScrollbarVisibilityChange(aVisible);
    TInt variety = aVisible ? 1 : 0;
    iGraphicLayoutData->SetSecondIndicatorLayout(list_single_graphic_pane_g2(variety));
    }

// End of file
