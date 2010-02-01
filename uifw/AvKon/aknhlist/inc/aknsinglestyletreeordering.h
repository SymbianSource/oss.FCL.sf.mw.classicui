/*
* Copyright (c) 2006, 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Ordering for single style hierarchical list.
*
*/


#ifndef C_AKNSINGLESTYLETREEORDERING_H
#define C_AKNSINGLESTYLETREEORDERING_H


#include "akntreeordering.h"


/**
 *  Ordering for single style hierarchical list.
 *
 *  The single style ordering class specifies the ordering of single style
 *  tree items within tree nodes. The alternative types single style ordering
 *  are specified in @c TOrderingType enumeration.
 *
 *  @lib aknhlist.lib
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( CAknSingleStyleTreeOrdering ) : public CAknTreeOrdering
    {

public:

    /** Single styele ordering types. */
    enum TOrderingType
        {
        /** Tree items in ascending alphabetical ordering with the nodes set
            before the leaves. */
        EAscending  = 0,
        /** Tree items in descending alphabetical ordering with the leaves
            set before the nodes. */
        EDescending = 1
        };

    /**
     * Two-phased constructor. Creates a single style ordering instance.
     *
     * @param aType One of the single style ordering types defined in
     *      CAknSingleStyleOrdering::TOrderingType enumeration.
     *
     * @return Pointer to the newly created object.
     */
    static CAknSingleStyleTreeOrdering* NewL( TOrderingType aType );

    /**
     * Otherwise identical to @c NewL(), but leaves the newly created object
     * in the cleanup stack.
     *
     * @copydoc CAknSingleStyleTreeOrdering::NewL()
     *
     * @post Newly constructed object is left in cleanup stack.
     */
    static CAknSingleStyleTreeOrdering* NewLC( TOrderingType aType );

    /**
     * Destructor.
     */
    ~CAknSingleStyleTreeOrdering();

// from base class CAknTreeOrdering

    /**
     * From CAknTreeOrdering.
     * @copydoc CAknTreeOrdering::Compare
     */
    TInt Compare( const CAknTreeItem& aFirst,
        const CAknTreeItem& aSecond );

protected:

    /**
     * C++ constructor.
     *
     * @param aType The ordering type.
     */
    CAknSingleStyleTreeOrdering( TOrderingType aType );

    /**
     * Second phase constructor.
     */
    void ConstructL();

private: // data

    /**
     * Ordering type.
     */
    TOrderingType iType;

    };


#endif // C_AKNSINGLESTYLETREEORDERING_H
