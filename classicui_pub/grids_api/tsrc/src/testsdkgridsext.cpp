/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Test grids_api
*
*/

/*
 * Include files
 */
#include <eiktxlbx.h>
#include <barsread.h>
#include <akngrid.h>
#include <aknlists.h>
#include <eiklbx.h>
#include <w32std.h>

#include "testsdkgridsext.h"
#include "testsdkgrids.h"

// -----------------------------------------------------------------------------
// CAknGridExt::CAknGridExt
// -----------------------------------------------------------------------------
//
CAknGridExt::CAknGridExt()
    {
    
    }

// -----------------------------------------------------------------------------
// CAknGridExt::~CAknGridExt
// -----------------------------------------------------------------------------
//
CAknGridExt::~CAknGridExt()
    {
    
    }
// -----------------------------------------------------------------------------
// CAknGridExt::HorizontalNudgeValue
// -----------------------------------------------------------------------------
//
TInt CAknGridExt::HorizontalNudgeValue() const
    {
    return CAknGrid::HorizontalNudgeValue();
    }

// -----------------------------------------------------------------------------
// CAknGridExt::HorizScrollGranularityInPixels
// -----------------------------------------------------------------------------
//
TInt CAknGridExt::HorizScrollGranularityInPixels() const
    {
    return CAknGrid::HorizScrollGranularityInPixels();
    }

// -----------------------------------------------------------------------------
// CAknGridExt::AdjustTopItemIndex
// -----------------------------------------------------------------------------
//
void CAknGridExt::AdjustTopItemIndex() const
    {
    CAknGrid::AdjustTopItemIndex();
    }

// -----------------------------------------------------------------------------
// CAknGridExt::HandleDragEventL
// -----------------------------------------------------------------------------
//
void CAknGridExt::HandleDragEventL(TPoint aPointerPos)
    {
    CAknGrid::HandleDragEventL( aPointerPos );
    }

// -----------------------------------------------------------------------------
// CAknGridExt::RestoreClientRectFromViewRect
// -----------------------------------------------------------------------------
//
void CAknGridExt::RestoreClientRectFromViewRect(TRect& aClientRect) const
    {
    CAknGrid::RestoreClientRectFromViewRect( aClientRect );
    }

// -----------------------------------------------------------------------------
// CAknGridExt::AdjustRectHeightToWholeNumberOfItems
// -----------------------------------------------------------------------------
//
TInt CAknGridExt::AdjustRectHeightToWholeNumberOfItems(TRect& aRect) const
    {
    return CAknGrid::AdjustRectHeightToWholeNumberOfItems( aRect );
    }

// -----------------------------------------------------------------------------
// CAknGridExt::UpdateScrollBarThumbs
// -----------------------------------------------------------------------------
//
void CAknGridExt::UpdateScrollBarThumbs() const
    {
    CAknGrid::UpdateScrollBarThumbs();
    }

// -----------------------------------------------------------------------------
// CAknGridExt::CountComponentControls
// -----------------------------------------------------------------------------
//
TInt CAknGridExt::CountComponentControls() const
    {
    return CAknGrid::CountComponentControls();
    }

// -----------------------------------------------------------------------------
// CAknGridExt::MoveToNextOrPreviousItemL
// -----------------------------------------------------------------------------
//
void CAknGridExt::MoveToNextOrPreviousItemL(TPoint aPoint)
    {
    CAknGrid::MoveToNextOrPreviousItemL( aPoint );
    }

// -----------------------------------------------------------------------------
// CAknGridExt::CalcGridSizeL
// -----------------------------------------------------------------------------
//
void CAknGridExt::CalcGridSizeL()
    {
    CAknGrid::CalcGridSizeL();
    }

// -----------------------------------------------------------------------------
// CAknGridExt::CreateItemDrawerL
// -----------------------------------------------------------------------------
//
void CAknGridExt::CreateItemDrawerL()
    {
    CAknGrid::CreateItemDrawerL();
    }

// -----------------------------------------------------------------------------
// CAknGridExt::HandleScrollEventL
// -----------------------------------------------------------------------------
//
void CAknGridExt::HandleScrollEventL(CEikScrollBar* aScrollBar, TEikScrollEvent aEventType)
    {
    CAknGrid::HandleScrollEventL( aScrollBar, aEventType );
    }

// -----------------------------------------------------------------------------
// CAknGridExt::MopSupplyObject
// -----------------------------------------------------------------------------
//
TTypeUid::Ptr CAknGridExt::MopSupplyObject(TTypeUid aId)
    {
    return CAknGrid::MopSupplyObject( aId );
    }

