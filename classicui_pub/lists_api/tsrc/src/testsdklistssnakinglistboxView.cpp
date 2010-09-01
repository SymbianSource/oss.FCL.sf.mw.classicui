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
* Description:  for test protected functions of CSnakingListBoxView
*
*/


#include "testsdklistssnakinglistboxView.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKListsSnakingListBoxView::DoTestDrawItemRange
// -----------------------------------------------------------------------------
//
void CTestSDKListsSnakingListBoxView::DoTestDrawItemRange(TInt aStartItemIndex,
                                                        TInt aEndItemIndex) const
    {
    DrawItemRange( aStartItemIndex, aEndItemIndex );
    }

// -----------------------------------------------------------------------------
// CTestSDKListsSnakingListBoxView::DoTestDrawColumnRange
// -----------------------------------------------------------------------------
//
void CTestSDKListsSnakingListBoxView::DoTestDrawColumnRange(TInt aStartColIndex,
                                                        TInt aEndColIndex) const
    {
    DrawColumnRange( aStartColIndex, aEndColIndex );
    }

// -----------------------------------------------------------------------------
// CTestSDKListsSnakingListBoxView::DoTestMoveToPreviousColumnL
// -----------------------------------------------------------------------------
//
void CTestSDKListsSnakingListBoxView::
                        DoTestMoveToPreviousColumnL(TSelectionMode aSelectionMode)
    {
    MoveToPreviousColumnL( aSelectionMode );
    }

// -----------------------------------------------------------------------------
// CTestSDKListsSnakingListBoxView::DoTestMoveToNextColumnL
// -----------------------------------------------------------------------------
//
void CTestSDKListsSnakingListBoxView::
                        DoTestMoveToNextColumnL(TSelectionMode aSelectionMode)
    {
    MoveToNextColumnL( aSelectionMode );
    }

// -----------------------------------------------------------------------------
// CTestSDKListsSnakingListBoxView::DoTestClearUnusedItemSpace
// -----------------------------------------------------------------------------
//
void CTestSDKListsSnakingListBoxView::
        DoTestClearUnusedItemSpace(TInt aStartItemIndex, TInt aEndItemIndex) const
    {
    ClearUnusedItemSpace( aStartItemIndex, aEndItemIndex );
    }

// -----------------------------------------------------------------------------
// CTestSDKListsSnakingListBoxView::DoTestUpdateHScrollOffsetBasedOnTopItemIndex
// -----------------------------------------------------------------------------
//
void CTestSDKListsSnakingListBoxView::DoTestUpdateHScrollOffsetBasedOnTopItemIndex()
    {
    UpdateHScrollOffsetBasedOnTopItemIndex();
    }
