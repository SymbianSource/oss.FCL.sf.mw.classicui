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


#include <ganes/HgDoubleGraphicList.h>
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
// CHgDoubleGraphicList::NewL()
// -----------------------------------------------------------------------------
//
EXPORT_C CHgDoubleGraphicList* CHgDoubleGraphicList::NewL(
        const TRect& aRect, 
        TInt aItemCount, 
        CGulIcon* aDefaultIcon,
        RWsSession* aSession)
    {
    CHgDoubleGraphicList* self = new ( ELeave ) CHgDoubleGraphicList( 
            aItemCount, 
            aDefaultIcon );

    CleanupStack::PushL (self );
    self->ConstructL( aRect, aSession );
    CleanupStack::Pop (self );
    return self;
    }

// -----------------------------------------------------------------------------
// CHgDoubleGraphicList::~CHgDoubleGraphicList()
// -----------------------------------------------------------------------------
//
EXPORT_C CHgDoubleGraphicList::~CHgDoubleGraphicList( )
    {
    delete iIconOverlayIndicator;
    }

// -----------------------------------------------------------------------------
// CHgDoubleGraphicList::PreferredImageSize()
// -----------------------------------------------------------------------------
//
EXPORT_C TSize CHgDoubleGraphicList::PreferredImageSize()
    {
    TAknLayoutRect image;
    image.LayoutRect(TRect(), AknLayoutScalable_Avkon::list_double_large_graphic_pane_g1( 0 ));
    return image.Rect().Size();
    }

// -----------------------------------------------------------------------------
// CHgDoubleGraphicList::PreferredImageSize()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgDoubleGraphicList::SetIconOverlayIndicator( CGulIcon* aIndicator )
    {
    delete iIconOverlayIndicator; 
    iIconOverlayIndicator = aIndicator;
    InitOverlayIcon();
    }

// -----------------------------------------------------------------------------
// CHgDoubleGraphicList::HandleSizeChanged()
// -----------------------------------------------------------------------------
//
void CHgDoubleGraphicList::HandleSizeChanged()
    {
    // Call base implementation
    CHgList::HandleSizeChanged();
    
    iLayoutData->SetItemLayout(list_double_large_graphic_pane( 0 ));
    iLayoutData->SetIconLayout(list_double_large_graphic_pane_g1( 2 ));
    for(TInt i = 0; i <= KMaxNumberOfTitleIndicators; ++i)
        iLayoutData->SetTitleLayout(i, list_double_large_graphic_pane_t1( i ));
    iLayoutData->SetTextLayout(list_double_large_graphic_pane_t2( 2 ));
    iLayoutData->SetFirstIndicatorLayout(list_double_large_graphic_pane_g3(0));
    TInt variety = iScrollbar && !iScrollbar->IsStatic() ? 1 : 0;
    iLayoutData->SetSecondIndicatorLayout(list_double_large_graphic_pane_g2(variety));
    
    // Get the Row rect.
    TAknLayoutRect layout;
    layout.LayoutRect(ListRect(), iLayoutData->ItemLayout());
    iRowHeight = layout.Rect().Height();

    // Icon rect.
    TAknLayoutRect image;
    image.LayoutRect(layout.Rect(), iLayoutData->IconLayout());
    iImageSize = image.Rect().Size();

    InitOverlayIcon();
    
    // Indicator Rect.
    TAknLayoutRect indicator;
    indicator.LayoutRect(layout.Rect(), iLayoutData->FirstIndicatorLayout());
    iIndicatorSize = indicator.Rect().Size();
    
    // Calculate the items on the screen.
    iItemsOnScreen = iHeight / iRowHeight;
    iHeight = iItemsOnScreen * iRowHeight;

    if( iCurrentRow != KErrNotFound )
        FitTopItemToView( iCurrentRow );
    }

// -----------------------------------------------------------------------------
// CHgDoubleGraphicList::DrawItem()
// -----------------------------------------------------------------------------
//
void CHgDoubleGraphicList::DrawItem( TInt aIndex, const TRect& aRect ) const
    {
    // Get the Icon
    CHgItem* item = iItems[aIndex];
    CGulIcon* icon = item->Icon() ? item->Icon() : iDefaultIcon;
    TInt indicators = CHgIndicatorManager::CountIndicators(item->Flags());

    CWindowGc& gc = SystemGc();
    
    // Highlight the row if it's selected
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

        // Draw second line text
        iDrawUtils->DrawTextMarquee(
                gc,
                aRect, 
                iLayoutData->TextLayout(),
                item->Text(),
                color, 1);
        
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

        // Draw second line text
        iDrawUtils->DrawText(
                gc,
                aRect, 
                iLayoutData->TextLayout(),
                item->Text(),
                color);
        }
    
    // Draw the icon
    iDrawUtils->DrawImage(gc, aRect, iLayoutData->IconLayout(), *icon);
    
    // Draw the icon overlay indicator if applicable
    if( item->Flags() & CHgItem::EHgItemFlagsIconOverlayIndicator
            && iIconOverlayIndicator )
        {
        iDrawUtils->DrawImage(
                gc, 
                aRect, 
                iLayoutData->IconLayout(), 
                *iIconOverlayIndicator);
        }
    
    // Draw the indicators.
    iIndicatorManager->DrawIndicators(
            gc,
            aRect, 
            item->Flags(), 
            iLayoutData->FirstIndicatorLayout(), 
            iLayoutData->SecondIndicatorLayout(),
            iFlags & EHgScrollerSelectionMode || iSelectionMode != ENoSelection );            
    }

// -----------------------------------------------------------------------------
// CHgDoubleGraphicList::CHgDoubleGraphicList()
// -----------------------------------------------------------------------------
//
CHgDoubleGraphicList::CHgDoubleGraphicList( TInt aItemCount, 
                                            CGulIcon* aDefaultIcon )
: CHgList( aItemCount, aDefaultIcon )
    {
    
    }

// -----------------------------------------------------------------------------
// CHgDoubleGraphicList::InitOverlayIcon()
// -----------------------------------------------------------------------------
//
void CHgDoubleGraphicList::InitOverlayIcon()
    {
    if( iIconOverlayIndicator && iIconOverlayIndicator->Bitmap() )
        {
        AknIconUtils::SetSize(iIconOverlayIndicator->Bitmap(), iImageSize);
        }
    }

// -----------------------------------------------------------------------------
// CHgDoubleGraphicList::HandleScrollbarVisibilityChange()
// -----------------------------------------------------------------------------
//
void CHgDoubleGraphicList::HandleScrollbarVisibilityChange( TBool aVisible )
    {
    TInt variety = aVisible ? 1 : 0;
    iLayoutData->SetSecondIndicatorLayout(list_double_large_graphic_pane_g2(variety));
    }

// End of file
