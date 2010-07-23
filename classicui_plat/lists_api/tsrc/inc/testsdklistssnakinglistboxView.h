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


#ifndef C_TESTSDKLISTSSNAKINGLISTBOXVIEW_H
#define C_TESTSDKLISTSSNAKINGLISTBOXVIEW_H

#include <eiklbv.h>

class CTestSDKListsSnakingListBoxView : public CSnakingListBoxView
{
public:

    /**
     * for test DrawItemRange(TInt aStartItemIndex, TInt aEndItemIndex)
     */
    void DoTestDrawItemRange(TInt aStartItemIndex, TInt aEndItemIndex) const;

    /**
     * for test DrawColumnRange(TInt aStartColIndex, TInt aEndColIndex)
     */
    void DoTestDrawColumnRange(TInt aStartColIndex, TInt aEndColIndex) const;

    /**
     * for test MoveToPreviousColumnL(TSelectionMode aSelectionMode)
     */
    void DoTestMoveToPreviousColumnL(TSelectionMode aSelectionMode);

    /**
     * for test MoveToNextColumnL(TSelectionMode aSelectionMode)
     */
    void DoTestMoveToNextColumnL(TSelectionMode aSelectionMode);

    /**
     * for test ClearUnusedItemSpace(TInt aStartItemIndex, TInt aEndItemIndex)
     */
    void DoTestClearUnusedItemSpace(TInt aStartItemIndex, TInt aEndItemIndex) const;

    /**
     * for test DUpdateHScrollOffsetBasedOnTopItemIndex()
     */
    void DoTestUpdateHScrollOffsetBasedOnTopItemIndex();
};

#endif /*C_TESTSDKLISTSSNAKINGLISTBOXVIEW_H*/
