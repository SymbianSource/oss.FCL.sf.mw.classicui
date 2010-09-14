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

#include <ganes/HgSingleTextList.h>
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
// CHgSingleTextList::NewL()
// -----------------------------------------------------------------------------
//
EXPORT_C CHgSingleTextList* CHgSingleTextList::NewL(
        const TRect& aRect, 
        TInt aItemCount, 
        CGulIcon* aDefaultIcon,
        RWsSession* aSession)
    {
    CHgSingleTextList* self = new ( ELeave ) CHgSingleTextList( 
            aItemCount, 
            aDefaultIcon );

    CleanupStack::PushL (self );
    self->ConstructL( aRect, aSession );
    CleanupStack::Pop (self );
    return self;
    }

// -----------------------------------------------------------------------------
// CHgSingleTextList::~CHgSingleTextList()
// -----------------------------------------------------------------------------
//
EXPORT_C CHgSingleTextList::~CHgSingleTextList( )
    {
    }

// -----------------------------------------------------------------------------
// CHgSingleTextList::HandleSizeChanged()
// -----------------------------------------------------------------------------
//
void CHgSingleTextList::HandleSizeChanged()
    {
    // Call base implementation
    CHgList::HandleSizeChanged();
    
    iLayoutData->SetItemLayout(list_single_pane( 0 ));
    for(TInt i = 0; i <= KMaxNumberOfTitleIndicators; ++i)
        iLayoutData->SetTitleLayout( i, list_single_pane_t1( i ) );
    iLayoutData->SetFirstIndicatorLayout(list_single_pane_g2(0));
    TInt variety = iScrollbar && !iScrollbar->IsStatic() ? 1 : 0;
    iLayoutData->SetSecondIndicatorLayout(list_single_pane_g1(variety));

    // Get the Row rect.
    TAknLayoutRect layout;
    layout.LayoutRect(ListRect(), iLayoutData->ItemLayout());
    iRowHeight = layout.Rect().Height();

    // This list type doesn't really visualize any icons.
    iImageSize = TSize(0,0);

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
// CHgSingleTextList::DrawItem()
// -----------------------------------------------------------------------------
//
void CHgSingleTextList::DrawItem( TInt aIndex, const TRect& aRect ) const
    {
    // Get the Icon
    CHgItem* item = iItems[aIndex];
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
// CHgSingleTextList::CHgSingleTextList()
// -----------------------------------------------------------------------------
//
CHgSingleTextList::CHgSingleTextList( TInt aItemCount, 
                                      CGulIcon* aDefaultIcon )
: CHgList( aItemCount, aDefaultIcon )
    {
    
    }

// -----------------------------------------------------------------------------
// CHgSingleTextList::HandleScrollbarVisibilityChange()
// -----------------------------------------------------------------------------
//
void CHgSingleTextList::HandleScrollbarVisibilityChange( TBool aVisible )
    {
    TInt variety = aVisible ? 1 : 0;
    iLayoutData->SetSecondIndicatorLayout(list_single_pane_g1(variety));
    }

// End of file
