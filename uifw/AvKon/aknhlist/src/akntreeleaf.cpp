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
* Description:  Implementation for CAknTreeLeaf class.
*
*/


#include "akntreeleaf.h"

const TUint KDefaultLeafFlags = NULL;


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Destructor.
// ---------------------------------------------------------------------------
//
CAknTreeLeaf::~CAknTreeLeaf()
    {
    }


// ---------------------------------------------------------------------------
// From class CAknTreeItem.
// ---------------------------------------------------------------------------
//
CAknTreeLeaf* CAknTreeLeaf::Leaf()
    {
    return this;
    }


const CAknTreeLeaf* CAknTreeLeaf::Leaf() const
    {
    return this;
    }


// ---------------------------------------------------------------------------
// From class CAknTreeItem.
// Checks whether the leaf is set marked.
// ---------------------------------------------------------------------------
//
TBool CAknTreeLeaf::IsMarked() const
    {
    return ( iFlags & EMarked ) ? ETrue : EFalse;
    }


// ---------------------------------------------------------------------------
// From class CAknTreeItem.
// Changes the state of the marked flag, if marking change is not disabled.
// ---------------------------------------------------------------------------
//
void CAknTreeLeaf::SetMarked( TBool aMarked )
    {
    if ( !( iFlags & EMarkingDisabled ) )
        {
        if ( aMarked )
            {
            iFlags |= EMarked;
            }
        else
            {
            iFlags &= ~EMarked;
            }
        }
    }


// ---------------------------------------------------------------------------
// From class CAknTreeItem.
// Checks whether marking is enabled.
// ---------------------------------------------------------------------------
//
TBool CAknTreeLeaf::IsMarkable() const
    {
    return ( iFlags & EMarkingDisabled ) ? EFalse : ETrue;
    }


// ---------------------------------------------------------------------------
// From class CAknTreeItem.
// Changes the state of the marking enabled flag.
// ---------------------------------------------------------------------------
//
void CAknTreeLeaf::SetMarkable( TBool aMarkable )
    {
    if ( aMarkable )
        {
        iFlags &= ~EMarkingDisabled;
        }
    else
        {
        iFlags |= EMarkingDisabled;
        }
    }


// ---------------------------------------------------------------------------
// From class CAknTreeItem.
// Checks whether the leaf is set persistent.
// ---------------------------------------------------------------------------
//
TBool CAknTreeLeaf::IsPersistent() const
    {
    return ( iFlags & EPersistent ) ? ETrue : EFalse;
    }


// ---------------------------------------------------------------------------
// From class CAknTreeItem.
// Changes the state of the persistent flag.
// ---------------------------------------------------------------------------
//
void CAknTreeLeaf::SetPersistent( TBool aPersistent )
    {
    if ( aPersistent )
        {
        iFlags |= EPersistent;
        }
    else
        {
        iFlags &= ~EPersistent;
        }
    }


// ---------------------------------------------------------------------------
// From class CAknTreeItem.
// Implementation for pure virtual function returns always false, as a leaf
// can not have any descendants.
// ---------------------------------------------------------------------------
//
TBool CAknTreeLeaf::HasPersistentDescendants() const
    {
    return EFalse;
    }


// ---------------------------------------------------------------------------
// From class CAknTreeItem.
// Checks whether the item can be removed from the tree when its parent node
// is being collapsed.
// ---------------------------------------------------------------------------
//
TBool CAknTreeLeaf::IsRemovableFromCollapsedNode() const
    {
    return !( IsMarked() || IsPersistent() );
    }


// ---------------------------------------------------------------------------
// Default C++ constructor.
// ---------------------------------------------------------------------------
//
CAknTreeLeaf::CAknTreeLeaf()
    : iFlags( KDefaultLeafFlags )
    {
    }


// ---------------------------------------------------------------------------
// C++ constructor.
// ---------------------------------------------------------------------------
//
CAknTreeLeaf::CAknTreeLeaf( TUint32 aFlags )
    : iFlags( aFlags )
    {
    }


// ---------------------------------------------------------------------------
// Returns flags set for the leaf.
// ---------------------------------------------------------------------------
//
TUint32 CAknTreeLeaf::Flags() const
    {
    return iFlags;
    }


// ---------------------------------------------------------------------------
// Sets flags for the leaf.
// ---------------------------------------------------------------------------
//
void CAknTreeLeaf::SetFlags( TUint32 aFlags )
    {
    iFlags = aFlags;
    }

