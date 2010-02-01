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


#include <ganes/HgSingleLargeList.h>
#include <ganes/HgItem.h>
#include "HgMarquee.h"
#include "HgLayoutData.h"
#include "HgIndicatorManager.h"
#include "HgDrawUtils.h"
#include "HgConstants.h"

#include <AknsUtils.h>
#include <AknUtils.h>
#include <AknsDrawUtils.h>

#include <layoutmetadata.cdl.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <gulicon.h>

using namespace AknLayoutScalable_Avkon;

// -----------------------------------------------------------------------------
// CHgSingleLargeList::NewL()
// -----------------------------------------------------------------------------
//
EXPORT_C CHgSingleLargeList* CHgSingleLargeList::NewL(
        const TRect& aRect, 
        TInt aItemCount, 
        CGulIcon* aDefaultIcon,
        RWsSession* aSession)
    {
    CHgSingleLargeList* self = new ( ELeave ) CHgSingleLargeList( 
            aItemCount, 
            aDefaultIcon );

    CleanupStack::PushL (self );
    self->ConstructL( aRect, aSession );
    CleanupStack::Pop (self );
    return self;
    }

// -----------------------------------------------------------------------------
// CHgSingleLargeList::~CHgSingleLargeList()
// -----------------------------------------------------------------------------
//
EXPORT_C CHgSingleLargeList::~CHgSingleLargeList( )
    {
    
    }

// -----------------------------------------------------------------------------
// CHgSingleLargeList::PreferredImageSize()
// -----------------------------------------------------------------------------
//
EXPORT_C TSize CHgSingleLargeList::PreferredImageSize()
    {
    TAknLayoutRect image;
    image.LayoutRect(TRect(), list_single_large_graphic_pane_g1( 0 ));
    return image.Rect().Size();
    }

// -----------------------------------------------------------------------------
// CHgSingleLargeList::HandleSizeChanged()
// -----------------------------------------------------------------------------
//
void CHgSingleLargeList::HandleSizeChanged()
    {
    CHgList::HandleSizeChanged();

    iLayoutData->SetItemLayout(list_single_large_graphic_pane( 0, 0 ));
    iLayoutData->SetIconLayout(list_single_large_graphic_pane_g1( 2 ));
    for(TInt i = 0; i <= KMaxNumberOfTitleIndicators; ++i)
        iLayoutData->SetTitleLayout( i, list_single_large_graphic_pane_t1( i ));
    iLayoutData->SetFirstIndicatorLayout(list_single_large_graphic_pane_g3(0));
    iLayoutData->SetSecondIndicatorLayout(list_single_large_graphic_pane_g2(1));
    
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
void CHgSingleLargeList::DrawItem( TInt aIndex, const TRect& aRect ) const
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
// CHgSingleLargeList::CHgSingleLargeList()
// -----------------------------------------------------------------------------
//
CHgSingleLargeList::CHgSingleLargeList( TInt aItemCount, 
                                        CGulIcon* aDefaultIcon )
: CHgList( aItemCount, aDefaultIcon )
    {
    
    }



// End of file
