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
* Description:  Base class for hierarchical list orderings.
*
*/


#ifndef C_AKNTREEORDERING_H
#define C_AKNTREEORDERING_H


#include <e32base.h>

class CAknTreeItem;


/**
 *  Tree ordering.
 *
 *  An instance of @c CAknTreeOrdering class specifies the order of children
 *  of a tree node. The tree can be sorted by applying the ordering to every
 *  node in the tree.
 *
 *  @lib aknhlist.lib
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( CAknTreeOrdering ) : public CBase
    {

public:

    /**
     * Destructor.
     */
    ~CAknTreeOrdering();

    /**
     * Compares to tree items.
     *
     * @param aFirst First item.
     *
     * @param aSecond Second item.
     *
     * @return Positive, if the first item is greater than the second item;
     *      negative, if the first item is less than the second item;
     *      and zero, if the items are equal.
     */
    virtual TInt Compare( const CAknTreeItem& aFirst,
        const CAknTreeItem& aSecond ) = 0;

protected:

    /**
     * Default C++ constructor.
     */
    CAknTreeOrdering();

    };


#endif // C_AKNTREEORDERING_H
