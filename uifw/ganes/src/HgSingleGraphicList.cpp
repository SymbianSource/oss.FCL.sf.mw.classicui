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


#include <ganes/HgSingleGraphicList.h>
#include <ganes/HgItem.h>
#include "HgMarquee.h"
#include "HgLayoutData.h"
#include "HgIndicatorManager.h"
#include "HgDrawUtils.h"
#include "HgConstants.h"
#include "HgScrollbar.h"

#include <AknsUtils.h>
#include <AknUtils.h>
#include <AknsDrawUtils.h>

#include <layoutmetadata.cdl.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <gulicon.h>

using namespace AknLayoutScalable_Avkon;

// -----------------------------------------------------------------------------
// CHgSingleGraphicList::NewL()
// -----------------------------------------------------------------------------
//
EXPORT_C CHgSingleGraphicList* CHgSingleGraphicList::NewL(
        const TRect& aRect, 
        TInt aItemCount, 
        CGulIcon* aDefaultIcon,
        RWsSession* aSession)
    {
    CHgSingleGraphicList* self = new ( ELeave ) CHgSingleGraphicList( 
            aItemCount, 
            aDefaultIcon );

    CleanupStack::PushL (self );
    self->ConstructL( aRect, aSession );
    CleanupStack::Pop (self );
    return self;
    }

// -----------------------------------------------------------------------------
// CHgSingleGraphicList::~CHgSingleGraphicList()
// -----------------------------------------------------------------------------
//
EXPORT_C CHgSingleGraphicList::~CHgSingleGraphicList( )
    {
    
    }

// -----------------------------------------------------------------------------
// CHgSingleGraphicList::PreferredImageSize()
// -----------------------------------------------------------------------------
//
EXPORT_C TSize CHgSingleGraphicList::PreferredImageSize()
    {
    TAknLayoutRect image;
    image.LayoutRect(TRect(), AknLayoutScalable_Avkon::list_single_graphic_pane_g1( 0 ));
    return image.Rect().Size();
    }

// -----------------------------------------------------------------------------
// CHgSingleGraphicList::HandleSizeChanged()
// -----------------------------------------------------------------------------
//
void CHgSingleGraphicList::HandleSizeChanged()
    {
    CHgList::HandleSizeChanged();
    
    iLayoutData->SetItemLayout(list_single_graphic_pane( 0 ));
    iLayoutData->SetIconLayout(list_single_graphic_pane_g1( 2 ));
    for(TInt i = 0; i <= KMaxNumberOfTitleIndicators; ++i)
        iLayoutData->SetTitleLayout( i, list_single_graphic_pane_t1( i ));
    iLayoutData->SetFirstIndicatorLayout(list_single_graphic_pane_g3(0));
    TInt variety = iScrollbar && !iScrollbar->IsStatic() ? 1 : 0;
    iLayoutData->SetSecondIndicatorLayout(list_single_graphic_pane_g2(variety));

    // Get the Row rect.
    TAknLayoutRect layout;
    layout.LayoutRect(ListRect(), iLayoutData->ItemLayout());
    iRowHeight = layout.Rect().Height();

    // Icon rect.
    TAknLayoutRect image;
    image.LayoutRect(layout.Rect(), iLayoutData->IconLayout());
    iImageSize = image.Rect().Size();

    // Indicator Rect.
    TAknLayoutRect indicator;
    indicator.LayoutRect(layout.Rect(), iLayoutData->FirstIndicatorLayout());
    iIndicatorSize = indicator.Rect().Size();

    iItemsOnScreen = iHeight / iRowHeight;
    iHeight = iItemsOnScreen * iRowHeight;
    
    if( iCurrentRow != KErrNotFound )
        FitTopItemToView( iCurrentRow );
    }

// -----------------------------------------------------------------------------
// CHgDoubleGraphicList::DrawItem()
// -----------------------------------------------------------------------------
//
void CHgSingleGraphicList::DrawItem( TInt aIndex, const TRect& aRect ) const
    {
    // Get the Icon
    CHgItem* item = iItems[aIndex];
    CGulIcon* icon = item->Icon() ? item->Icon() : iDefaultIcon;
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
                iLayoutData->TitleLayout(indicators),
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
                iLayoutData->TitleLayout(indicators),
                item->Title(),
                color);
        }
    
    // Draw the icon
    iDrawUtils->DrawImage(gc, aRect, iLayoutData->IconLayout(), *icon);
    
    // Draw the indicators.
    iIndicatorManager->DrawIndicators(
            gc,
            aRect, 
            item->Flags(), 
            iLayoutData->FirstIndicatorLayout(), 
            iLayoutData->SecondIndicatorLayout() );            
    }

// -----------------------------------------------------------------------------
// CHgSingleGraphicList::CHgSingleGraphicList()
// -----------------------------------------------------------------------------
//
CHgSingleGraphicList::CHgSingleGraphicList( TInt aItemCount, 
        CGulIcon* aDefaultIcon )
: CHgList( aItemCount, aDefaultIcon )
    {
    
    }

// -----------------------------------------------------------------------------
// CHgSingleGraphicList::HandleScrollbarVisibilityChange()
// -----------------------------------------------------------------------------
//
void CHgSingleGraphicList::HandleScrollbarVisibilityChange( TBool aVisible )
    {
    TInt variety = aVisible ? 1 : 0;
    iLayoutData->SetSecondIndicatorLayout(list_single_graphic_pane_g2(variety));
    }

// End of file
