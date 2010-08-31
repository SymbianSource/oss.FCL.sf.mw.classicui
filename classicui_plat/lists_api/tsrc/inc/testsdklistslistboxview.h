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
* Description:  for protected functions of CListBoxView
*
*/


#ifndef C_TESTSDKLISTSLISTBOXVIEW_H
#define C_TESTSDKLISTSLISTBOXVIEW_H

#include <eiklbv.h>

class CTestSDKListsListBoxView : public CListBoxView
{
public:
    // functions for accessing the flags
    /**
     * for test Flags();
     * Gets this view�s flags.
     *
     * These flags are defined by the nested enum @c TFlags (below).
     *
     * @return List box's flags. 
     */
    TInt DoTestFlags() const;

    /**
     * for test SetFlags(TInt aMask)
     * Sets this view�s flags according to a bitmask.
     *
     * These flags are defined by the nested enum @c TFlags (below).
     *
     * @param aMask Sets new flags for the list box.
     */
    void DoTestSetFlags(TInt aMask);

    /**
     * for test ClearFlags(TInt aMask)
     * Clears this view�s flags according to a bitmask.
     *
     * These flags are defined by the nested enum @c TFlags (below).
     *
     * @param aMask Flags to be removed. 
     */
    void DoTestClearFlags(TInt aMask);

    // misc. functions
    /**
     * for test SelectRangeL(TInt aItemIndex1, TInt aItemIndex2)
     * Selects items between given indexes.
     * 
     * @deprecated
     * @param aItemIndex1 First index of selectable range.
     * @param aItemIndex2 Second index of selectable range.
     */
    void DoTestSelectRangeL(TInt aItemIndex1, TInt aItemIndex2);

};

#endif /*C_TESTSDKLISTSLISTBOXVIEW_H*/
