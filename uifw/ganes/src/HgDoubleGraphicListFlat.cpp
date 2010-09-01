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


#include <ganes/HgDoubleGraphicListFlat.h>
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
// CHgDoubleGraphicListFlat::NewL()
// -----------------------------------------------------------------------------
//
EXPORT_C CHgDoubleGraphicListFlat* CHgDoubleGraphicListFlat::NewL(
        const TRect& aRect, 
        TInt aItemCount, 
        CGulIcon* aDefaultIcon,
        RWsSession* aSession)
    {
    CHgDoubleGraphicListFlat* self = new ( ELeave ) CHgDoubleGraphicListFlat( 
            aItemCount, 
            aDefaultIcon );

    CleanupStack::PushL (self );
    self->ConstructL( aRect, aSession );
    CleanupStack::Pop (self );
    return self;
    }

// -----------------------------------------------------------------------------
// CHgDoubleGraphicListFlat::~CHgDoubleGraphicListFlat()
// -----------------------------------------------------------------------------
//
EXPORT_C CHgDoubleGraphicListFlat::~CHgDoubleGraphicListFlat( )
    {
    
    }

// -----------------------------------------------------------------------------
// CHgDoubleGraphicListFlat::PreferredImageSize()
// -----------------------------------------------------------------------------
//
EXPORT_C TSize CHgDoubleGraphicListFlat::PreferredImageSize()
    {
    TAknLayoutRect image;
    image.LayoutRect(TRect(), AknLayoutScalable_Avkon::list_double_large_graphic_pane_g1( 0 ));
    return image.Rect().Size();
    }

// -----------------------------------------------------------------------------
// CHgDoubleGraphicListFlat::HandleSizeChanged()
// -----------------------------------------------------------------------------
//
void CHgDoubleGraphicListFlat::HandleSizeChanged()
    {
    // Call base implementation
    CHgDoubleGraphicList::HandleSizeChanged();

    iHeight = Rect().Height();
    
    if(iHeight % iRowHeight) iItemsOnScreen++;
    
    if( iCurrentRow != KErrNotFound )
        FitTopItemToView( iCurrentRow );
    }

// -----------------------------------------------------------------------------
// CHgDoubleGraphicListFlat::DrawItem()
// -----------------------------------------------------------------------------
//
void CHgDoubleGraphicListFlat::DrawItem( TInt aIndex, const TRect& aRect ) const
    {
    CHgDoubleGraphicList::DrawItem( aIndex, aRect );
    }

// -----------------------------------------------------------------------------
// CHgDoubleGraphicListFlat::CHgDoubleGraphicListFlat()
// -----------------------------------------------------------------------------
//
CHgDoubleGraphicListFlat::CHgDoubleGraphicListFlat( TInt aItemCount, 
                                            CGulIcon* aDefaultIcon )
: CHgDoubleGraphicList( aItemCount, aDefaultIcon )
    {
    SetFlags( EHgScrollerFlatStatusPane ); // Set Flat status pane on
    }

