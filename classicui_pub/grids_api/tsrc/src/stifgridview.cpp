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
#include "stifgridview.h"
// -----------------------------------------------------------------------------
// CStifGridView::DoGridModel
// -----------------------------------------------------------------------------
//
CAknGridM* CStifGridView::DoGridModel() const
    {
    return GridModel();
    }

// -----------------------------------------------------------------------------
// CStifGridView::DoDoMoveL
// -----------------------------------------------------------------------------
//
void CStifGridView::DoDoMoveL(TCursorMovement aCursorMovement, TSelectionMode aSelectionMode)
    {
    DoMoveL( aCursorMovement, aSelectionMode );
    }

// -----------------------------------------------------------------------------
// CStifGridView::DoDrawColumnRange
// -----------------------------------------------------------------------------
//
void CStifGridView::DoDrawColumnRange(TInt aStartColIndex, TInt aEndColIndex) const
    {
    DrawColumnRange( aStartColIndex, aEndColIndex );
    }

// -----------------------------------------------------------------------------
// CStifGridView::DoClearUnusedItemSpace
// -----------------------------------------------------------------------------
//
void CStifGridView::DoClearUnusedItemSpace(TInt aStartItemIndex, TInt aEndItemIndex) const
    {
    ClearUnusedItemSpace( aStartItemIndex, aEndItemIndex );
    }

// -----------------------------------------------------------------------------
// CStifGridView::DoUpdateHScrollOffsetBasedOnTopItemIndex
// -----------------------------------------------------------------------------
//
void CStifGridView::DoUpdateHScrollOffsetBasedOnTopItemIndex()
    {
    UpdateHScrollOffsetBasedOnTopItemIndex();
    }

// -----------------------------------------------------------------------------
// CStifGridView::DoItemExists
// -----------------------------------------------------------------------------
//
TBool CStifGridView::DoItemExists(TInt aListBoxIndex) const
    {
    TBool flag = ItemExists( aListBoxIndex );
    return flag;
    }

// -----------------------------------------------------------------------------
// CStifGridView::GetItemHeight
// -----------------------------------------------------------------------------
//
TInt CStifGridView::GetItemHeight()
    {
    return iItemHeight;
    }

// -----------------------------------------------------------------------------
// CStifGridView::GetDataWidth
// -----------------------------------------------------------------------------
//
TInt CStifGridView::GetDataWidth()
    {
    return iDataWidth;
    }

// -----------------------------------------------------------------------------
// CStifGridView::GetiHScrollOffset
// -----------------------------------------------------------------------------
//
TInt CStifGridView::GetiHScrollOffset()
    {
    return iHScrollOffset;
    }
