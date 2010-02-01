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
* Description:  Implementation for single style tree ordering.
*
*/


#include "aknsinglestyletreeordering.h"
#include "aknsinglestyletreenode.h"
#include "aknsinglestyletreeleaf.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CAknSingleStyleTreeOrdering* CAknSingleStyleTreeOrdering::NewL(
    TOrderingType aType )
    {
    CAknSingleStyleTreeOrdering* self = CAknSingleStyleTreeOrdering::NewLC(
        aType );
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// Two phased constructor.
// ---------------------------------------------------------------------------
//
CAknSingleStyleTreeOrdering* CAknSingleStyleTreeOrdering::NewLC(
    TOrderingType aType )
    {
    CAknSingleStyleTreeOrdering* self = 
        new ( ELeave ) CAknSingleStyleTreeOrdering( aType );
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }


// ---------------------------------------------------------------------------
// Destructor.
// ---------------------------------------------------------------------------
//
CAknSingleStyleTreeOrdering::~CAknSingleStyleTreeOrdering()
    {
    }


// ---------------------------------------------------------------------------
// From class CAknTreeOrdering.
// ---------------------------------------------------------------------------
//
TInt CAknSingleStyleTreeOrdering::Compare( const CAknTreeItem& aFirst,
    const CAknTreeItem& aSecond )
    {
    TInt comparisonValue = NULL;
    if ( aFirst.IsLeaf() && aSecond.IsLeaf() )
        {
        const TDesC& first =
            static_cast<const CAknSingleStyleTreeLeaf&>( aFirst ).Text();

        const TDesC& second =
            static_cast<const CAknSingleStyleTreeLeaf&>( aSecond ).Text();

        comparisonValue = first.CompareC( second );
        }
    else if ( aFirst.IsLeaf() && aSecond.IsNode() )
        {
        comparisonValue = 1;
        }
    else if ( aFirst.IsNode() && aSecond.IsLeaf() )
        {
        comparisonValue = -1;
        }
    else // Both items are nodes
        {
        __ASSERT_DEBUG( aFirst.IsNode(), User::Invariant() );
        __ASSERT_DEBUG( aSecond.IsNode(), User::Invariant() );

        const TDesC& first =
            static_cast<const CAknSingleStyleTreeNode&>( aFirst ).Text();

        const TDesC& second =
            static_cast<const CAknSingleStyleTreeNode&>( aSecond ).Text();

        comparisonValue = first.CompareC( second );
        }

    if ( iType == EDescending )
        {
        comparisonValue *= -1;
        }

    return comparisonValue;
    }


// ---------------------------------------------------------------------------
// Default C++ constructor.
// ---------------------------------------------------------------------------
//
CAknSingleStyleTreeOrdering::CAknSingleStyleTreeOrdering( TOrderingType aType )
    : iType( aType )
    {
    }


// ---------------------------------------------------------------------------
// Second phase constructor.
// ---------------------------------------------------------------------------
//
void CAknSingleStyleTreeOrdering::ConstructL()
    {
    }


