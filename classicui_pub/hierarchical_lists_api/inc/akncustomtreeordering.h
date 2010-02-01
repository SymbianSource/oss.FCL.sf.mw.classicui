/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Interface for implementing custom ordering for tree list.
*
*/


#ifndef M_AKNCUSTOMTREEORDERING_H
#define M_AKNCUSTOMTREEORDERING_H


#include <akntreelistconstants.h>


/**
 *  Interface class for implementing custom ordering for hierarchical list.
 *
 *  Implementation of this interface class can be set to hierarchical
 *  list to define the ordering of items in the list. Hierarchical list
 *  then uses the implementation of @c MAknCustomTreeOrdering::Compare
 *  method in sorting the items within each node of the list.
 *
 *  @since S60 v3.2
 */
class MAknCustomTreeOrdering
    {

public:

    /**
     * Compares two tree list items.
     *
     * @param aFirst Item ID of the first compared hierarchical list item.
     *
     * @param aSecond Item ID of the second compared hierarchical list item.
     *
     * @return Positive, if the first item is greater than the second item;
     *      negative, if the first item is less than the second item;
     *      and zero, if the items are equal.
     */
    virtual TInt Compare( TAknTreeItemID aFirst, TAknTreeItemID aSecond ) = 0;

    };


#endif // M_AKNCUSTOMTREEORDERING_H
