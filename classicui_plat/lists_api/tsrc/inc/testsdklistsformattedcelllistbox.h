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
* Description:  test protected for CEikFormattedCellListBox
*
*/

#ifndef C_TESTSDKLISTSFORMATTEDCELLLISTBOX_H
#define C_TESTSDKLISTSFORMATTEDCELLLISTBOX_H

#include <eikfrlb.h>

class CTestSDKListsFormattedCellListBox : public CEikFormattedCellListBox
{
public:
    /**
     * C++ default constructor.
     */
    CTestSDKListsFormattedCellListBox();

    /**
     * C++ default constructor.
     */
    virtual ~CTestSDKListsFormattedCellListBox();

    /**
     * Creates item draver for the listbox.
     */
    virtual void CreateItemDrawerL();

    /**
     * From @c CEikListBox.
     *
     * Rounds down the height of the rectangle (if necessary) so that only
     * a whole number of items can be displayed inside the list box.
     *
     * @param aRect The rectangle to be modified.
     * @return The number of pixels reduced.
     */
    virtual TInt AdjustRectHeightToWholeNumberOfItems(TRect &aRect) const;

    /**
     * From @c MObjectProvider.
     *
     * Retrieves an object of the same type as that encapsulated in aId. This 
     * function is used to allow controls to ask their owners for access to 
     * other objects that they own.
     * 
     * @param aId An encapsulated object type ID.
     * @return Encapsulates the pointer to the object provided. 
     *         Note that the encapsulated pointer may be NULL.
     */
    virtual TTypeUid::Ptr MopSupplyObject(TTypeUid aId);
};

#endif /*C_TESTSDKLISTSFORMATTEDCELLLISTBOX_H*/
