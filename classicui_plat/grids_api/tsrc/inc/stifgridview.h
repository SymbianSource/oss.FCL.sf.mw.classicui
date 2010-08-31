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


#ifndef C_STIFGRIDVIEW_H
#define C_STIFGRIDVIEW_H

/*
 * Include files
 */
#include <akngridview.h>

/*
 * This class inherit from CAknGridView class for testing its protected function
 */
class CStifGridView:public CAknGridView
    {
public:
    /*
     * This function is wrote for testing CAknGridView's protected function
     */
    CAknGridM* DoGridModel() const;
    /*
     * This function is wrote for testing CAknGridView's protected function
     */
    void DoDoMoveL(TCursorMovement aCursorMovement, TSelectionMode aSelectionMode);
    /*
     * This function is wrote for testing CAknGridView's protected function
     */
    void DoDrawColumnRange(TInt aStartColIndex, TInt aEndColIndex) const;
    /*
     * This function is wrote for testing CAknGridView's protected function
     */
    void DoClearUnusedItemSpace(TInt aStartItemIndex, TInt aEndItemIndex) const;
    /*
     * This function is wrote for testing CAknGridView's protected function
     */
    void DoUpdateHScrollOffsetBasedOnTopItemIndex();
    /*
     * This function is wrote for testing CAknGridView's protected function
     */
    TBool DoItemExists(TInt aListBoxIndex) const;
    /*
     * This function is wrote for testing CAknGridView's protected function
     */
    TInt GetItemHeight();
    /*
     * This function is wrote for testing CAknGridView's protected function
     */
    TInt GetDataWidth();
    /*
     * This function is wrote for testing CAknGridView's protected function
     */
    TInt GetiHScrollOffset();
    };
#endif

/*
 * End file
 */
