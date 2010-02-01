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


#include <ganes/HgDoubleTextList.h>
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
// CHgDoubleTextList::NewL()
// -----------------------------------------------------------------------------
//
EXPORT_C CHgDoubleTextList* CHgDoubleTextList::NewL(
        const TRect& aRect, 
        TInt aItemCount, 
        CGulIcon* aDefaultIcon,
        RWsSession* aSession)
    {
    CHgDoubleTextList* self = new ( ELeave ) CHgDoubleTextList( 
            aItemCount, 
            aDefaultIcon );

    CleanupStack::PushL (self );
    self->ConstructL( aRect, aSession );
    CleanupStack::Pop (self );
    return self;
    }

// -----------------------------------------------------------------------------
// CHgDoubleTextList::~CHgDoubleTextList()
// -----------------------------------------------------------------------------
//
EXPORT_C CHgDoubleTextList::~CHgDoubleTextList( )
    {
    
    }

// -----------------------------------------------------------------------------
// CHgDoubleTextList::PreferredImageSize()
// -----------------------------------------------------------------------------
//
EXPORT_C TSize CHgDoubleTextList::PreferredImageSize()
    {
    return TSize(0,0);
    }

// -----------------------------------------------------------------------------
// CHgDoubleTextList::HandleSizeChanged()
// -----------------------------------------------------------------------------
//
void CHgDoubleTextList::HandleSizeChanged()
    {
    // Call base implementation
    CHgList::HandleSizeChanged();

    iLayoutData->SetItemLayout(list_double_pane( 0 ));
    for(TInt i = 0; i <= KMaxNumberOfTitleIndicators; ++i)
        iLayoutData->SetTitleLayout(i, list_double_pane_t1( i ));
    iLayoutData->SetTextLayout(list_double_pane_t2( 2 ));
    iLayoutData->SetFirstIndicatorLayout(list_double_pane_g2(0));
    iLayoutData->SetSecondIndicatorLayout(list_double_pane_g1(1));
    
    // Get the Row rect.
    TAknLayoutRect layout;
    layout.LayoutRect(ListRect(), iLayoutData->ItemLayout());
    iRowHeight = layout.Rect().Height();

    // Indicator Rect.
    TAknLayoutRect indicator;
    indicator.LayoutRect(layout.Rect(), iLayoutData->FirstIndicatorLayout() );
    iIndicatorSize = indicator.Rect().Size();
    
    // Calculate the items on the screen.
    iItemsOnScreen = iHeight / iRowHeight;
    iHeight = iItemsOnScreen * iRowHeight;

    if( iCurrentRow != KErrNotFound )
        FitTopItemToView( iCurrentRow );    
    }

// -----------------------------------------------------------------------------
// CHgDoubleTextList::DrawItem()
// -----------------------------------------------------------------------------
//
void CHgDoubleTextList::DrawItem( TInt aIndex, const TRect& aRect ) const
    {
    // Get the Icon
    CHgItem* item = iItems[aIndex];
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
    
    // Draw the indicators.
    iIndicatorManager->DrawIndicators(
            gc,
            aRect, 
            item->Flags(), 
            iLayoutData->FirstIndicatorLayout(), 
            iLayoutData->SecondIndicatorLayout() );            
    }

// -----------------------------------------------------------------------------
// CHgDoubleTextList::CHgDoubleTextList()
// -----------------------------------------------------------------------------
//
CHgDoubleTextList::CHgDoubleTextList( TInt aItemCount, 
                                            CGulIcon* aDefaultIcon )
: CHgList( aItemCount, aDefaultIcon )
    {
    
    }

