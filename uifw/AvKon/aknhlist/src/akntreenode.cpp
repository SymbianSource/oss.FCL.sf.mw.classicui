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
* Description:  Implementation for CAknTreeNode class.
*
*/


#include "akntreenode.h"

const TUint KDefaultNodeFlags = NULL;
const TInt KArrayGranularity = 16;


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Destructor.
// ---------------------------------------------------------------------------
//
CAknTreeNode::~CAknTreeNode()
    {
    iChild.ResetAndDestroy();
    }


// ---------------------------------------------------------------------------
// Returns the number of children.
// ---------------------------------------------------------------------------
//
TInt CAknTreeNode::ChildCount() const
    {
    return iChild.Count();
    }


// ---------------------------------------------------------------------------
// Returns the number of descendants. Current implementation counts the value
// by recursively calling itself to all the child nodes, but the descendant
// count could instead be stored in each node.
// ---------------------------------------------------------------------------
//
TInt CAknTreeNode::DescendantCount() const
    {
    TInt count = iChild.Count();
    CAknTreeNode* node = NULL;
    for ( TInt ii = count - 1; ii >= 0; --ii )
        {
        node = iChild[ii]->Node();
        if ( node )
            {
            count += node->DescendantCount();
            }
        }
    return count;
    }


// ---------------------------------------------------------------------------
// Returns the number of visible descendants.
// ---------------------------------------------------------------------------
//
TInt CAknTreeNode::VisibleDescendantCount() const
    {
    TInt count = IsExpanded() ? iChild.Count() : NULL;
    CAknTreeNode* node = NULL;
    for ( TInt ii = count - 1; ii >= 0; --ii )
        {
        node = iChild[ii]->Node();
        if ( node )
            {
            count += node->VisibleDescendantCount();
            }
        }
    return count;
    }


// ---------------------------------------------------------------------------
// Returns the child with the specified index.
// ---------------------------------------------------------------------------
//
CAknTreeItem* CAknTreeNode::Child( TInt aIndex ) const
    {
    // Panics if index is out of range.
    return iChild[aIndex];
    }


// ---------------------------------------------------------------------------
// Returns the index of the specified child. The error code KErrNotFound is
// returned, if the item is not found.
// ---------------------------------------------------------------------------
//
TInt CAknTreeNode::Index( const CAknTreeItem* aItem ) const
    {
    __ASSERT_DEBUG( aItem, User::Invariant() );
    return iChild.Find( aItem );
    }


// ---------------------------------------------------------------------------
// Adds a child to the node.
// ---------------------------------------------------------------------------
//
void CAknTreeNode::AddChildL( CAknTreeItem* aItem )
    {
    __ASSERT_DEBUG( aItem != this, User::Invariant() );
    __ASSERT_DEBUG( aItem != NULL, User::Invariant() );

    TLinearOrder<CAknTreeItem> order( CAknTreeItem::Compare );
    iChild.InsertInOrderAllowRepeatsL( aItem, order );
    }


void CAknTreeNode::AddChildL( CAknTreeItem* aItem, TInt aPosition )
    {
    __ASSERT_DEBUG( aItem != this, User::Invariant() );
    __ASSERT_DEBUG( aItem != NULL, User::Invariant() );

    iChild.InsertL( aItem, aPosition );
    }


// ---------------------------------------------------------------------------
// Removes the specified item from the set of children.
// ---------------------------------------------------------------------------
//
TInt CAknTreeNode::RemoveChild( CAknTreeItem* aItem )
    {
    TInt index = iChild.Find( aItem );
    if ( index >= 0 )
        {
        iChild.Remove( index );
        return KErrNone;
        }
    else
        {
        return KErrNotFound;
        }
    }


// ---------------------------------------------------------------------------
// Checks whether the node is expanded.
// ---------------------------------------------------------------------------
//
TBool CAknTreeNode::IsExpanded() const
    {
    return ( iFlags & EExpanded ) ? ETrue : EFalse;
    }


// ---------------------------------------------------------------------------
// Sets the node expanded.
// ---------------------------------------------------------------------------
//
void CAknTreeNode::Expand()
    {
    iFlags |= EExpanded;
    }


// ---------------------------------------------------------------------------
// Sets the node collapsed.
// ---------------------------------------------------------------------------
//
void CAknTreeNode::Collapse()
    {
    iFlags &= ~EExpanded;
    }


// ---------------------------------------------------------------------------
// Checks whether the node is empty.
// ---------------------------------------------------------------------------
//
TBool CAknTreeNode::IsEmpty() const
    {
    return ( iChild.Count() == 0 ) && !( iFlags & ENonEmpty );
    }


// ---------------------------------------------------------------------------
// Changes the state of the non-empty flag.
// ---------------------------------------------------------------------------
//
void CAknTreeNode::SetNonEmpty( TBool aNonEmpty )
    {
    if ( aNonEmpty )
        {
        iFlags |= ENonEmpty;
        }
    else
        {
        iFlags &= ~ENonEmpty;
        }
    }


// ---------------------------------------------------------------------------
// Sort.
// ---------------------------------------------------------------------------
//
void CAknTreeNode::Sort()
    {
    TLinearOrder<CAknTreeItem> order( CAknTreeItem::Compare );
    iChild.Sort( order );
    }


// ---------------------------------------------------------------------------
// From class CAknTreeItem.
// Returns pointer to this node.
// ---------------------------------------------------------------------------
//
CAknTreeNode* CAknTreeNode::Node()
    {
    return this;
    }


const CAknTreeNode* CAknTreeNode::Node() const
    {
    return this;
    }


// ---------------------------------------------------------------------------
// From class CAknTreeItem.
// Checks whether then node is set marked.
// ---------------------------------------------------------------------------
//
TBool CAknTreeNode::IsMarked() const
    {
    return ( iFlags & EMarked ) ? ETrue : EFalse;
    }


// ---------------------------------------------------------------------------
// From class CAknTreeItem.
// Changes the state of the marked flag, if marking change is not disabled.
// ---------------------------------------------------------------------------
//
void CAknTreeNode::SetMarked( TBool aMarked )
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
TBool CAknTreeNode::IsMarkable() const
    {
    return ( iFlags & EMarkingDisabled ) ? EFalse : ETrue;
    }


// ---------------------------------------------------------------------------
// From class CAknTreeItem.
// Changes the state of the marking enabled flag.
// ---------------------------------------------------------------------------
//
void CAknTreeNode::SetMarkable( TBool aMarkable )
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
// Checks whether then node is set persistent.
// ---------------------------------------------------------------------------
//
TBool CAknTreeNode::IsPersistent() const
    {
    return ( iFlags & EPersistent ) ? ETrue : EFalse;
    }


// ---------------------------------------------------------------------------
// From class CAknTreeItem.
// Changes the state of the persistent flag.
// ---------------------------------------------------------------------------
//
void CAknTreeNode::SetPersistent( TBool aPersistent )
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
// Checks whether the node has persistent descendants.
// ---------------------------------------------------------------------------
//
TBool CAknTreeNode::HasPersistentDescendants() const
    {
    TBool persistent = EFalse;
    for ( TInt ii = 0; ii < iChild.Count() && !persistent; ++ii )
        {
        if ( iChild[ii]->IsPersistent() )
            {
            persistent = ETrue;
            }
        else if ( iChild[ii]->IsNode() )
            {
            persistent = iChild[ii]->Node()->HasPersistentDescendants();
            }
        }
    return persistent;
    }


// ---------------------------------------------------------------------------
// From class CAknTreeItem.
// Checks whether the item can be removed from the tree when its parent node
// is being collapsed.
// ---------------------------------------------------------------------------
//
TBool CAknTreeNode::IsRemovableFromCollapsedNode() const
    {
    TBool removable = !( IsMarked() || IsPersistent() );
    for ( TInt ii = 0; removable && ii < iChild.Count(); ++ii )
        {
        removable = iChild[ii]->IsRemovableFromCollapsedNode();
        }
    return removable;
    }


// ---------------------------------------------------------------------------
// Default C++ constructor.
// ---------------------------------------------------------------------------
//
CAknTreeNode::CAknTreeNode()
    : iChild( KArrayGranularity ),
      iFlags( KDefaultNodeFlags )
    {
    }


// ---------------------------------------------------------------------------
// C++ constructor.
// ---------------------------------------------------------------------------
//
CAknTreeNode::CAknTreeNode( TUint32 aFlags )
    : iChild( KArrayGranularity ),
      iFlags( aFlags )
    {
    }


// ---------------------------------------------------------------------------
// Returns flags set for the node.
// ---------------------------------------------------------------------------
//
TUint32 CAknTreeNode::Flags() const
    {
    return iFlags;
    }


// ---------------------------------------------------------------------------
// Sets flags for the node.
// ---------------------------------------------------------------------------
//
void CAknTreeNode::SetFlags( TUint32 aFlags )
    {
    iFlags = aFlags;
    }

