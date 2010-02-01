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
* Description:  Implementation for CAknTree class.
*
*/



#include <AknUtils.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <AknsUtils.h>
#include <avkon.mbg>
#include <AknMarqueeControl.h>

#include "akntree.h"
#include "akntreelist.h"
#include "akntreeordering.h"
#include "aknhlistlib.h"
#include "akntreeiterator.h"
#include "akntreelisticon.h"
#include "akncustomtreeordering.h"
#include "akntreelistinternalconstants.h"

const TInt KObserverArrayGranularity = 1;

// Tree flag definitions
enum TAknTreeFlags
    {
    ETabModeFunctionIndicators
    };


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CAknTree* CAknTree::NewL( CAknTreeList& aList, CAknTreeOrdering* aOrdering )
    {
    CAknTree* self = new( ELeave ) CAknTree( aList, aOrdering );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// Destructor.
// ---------------------------------------------------------------------------
//
CAknTree::~CAknTree()
    {
    delete iOrdering; iOrdering = NULL;
    iCustomOrdering = NULL;
    iObservers.Close();
    iItems.Close();
    iIcons.ResetAndDestroy();
    delete iMarquee; iMarquee = NULL;
    iMarqueeItem = NULL;
    }


// ---------------------------------------------------------------------------
// Id for the given item.
// ---------------------------------------------------------------------------
//
TAknTreeItemID CAknTree::Id( const CAknTreeItem* aItem ) const
    {
    if ( aItem == this )
        {
        return KAknTreeIIDRoot;
        }
    else
        {
        return reinterpret_cast<TInt>( aItem );
        }
    }


// ---------------------------------------------------------------------------
// Sets ordering for tree items. Previously set ordering is deleted and
// customized ordering interface discarded.
// ---------------------------------------------------------------------------
//
void CAknTree::SetOrdering( CAknTreeOrdering* aOrdering, TBool aDrawNow )
    {
    delete iOrdering;
    iOrdering = aOrdering;

    iCustomOrdering = NULL;

    Sort( aDrawNow );
    }


// ---------------------------------------------------------------------------
// Sets custom ordering for tree items.
// ---------------------------------------------------------------------------
//
void CAknTree::SetCustomOrdering( MAknCustomTreeOrdering* aOrdering,
    TBool aDrawNow )
    {
    iCustomOrdering = aOrdering;

    delete iOrdering;
    iOrdering = NULL;

    Sort( aDrawNow );
    }


// ---------------------------------------------------------------------------
// Sorts the specified tree node.
// ---------------------------------------------------------------------------
//
void CAknTree::Sort( TAknTreeItemID aNode, TBool aSortDescendants,
    TBool aDrawNow )
    {
    // The sorting can be done only when ordering is set for the tree.
    if ( iCustomOrdering || iOrdering )
        {
        CAknTreeNode* node = Node( aNode );
        node->Sort();
        if ( aSortDescendants )
            {
            // Iterate through the descendants of the node and sort
            // each descendant node separately.
            TAknTreeIterator iterator( node, NULL );
            while ( iterator.HasNext() )
                {
                node = iterator.Next()->Node();
                if ( node )
                    {
                    node->Sort();
                    }
                }
            }
        }

    NotifyObservers( MAknTreeObserver::ETreeSorted, this, aDrawNow );
    }


// ---------------------------------------------------------------------------
// Compares two tree list items.
// ---------------------------------------------------------------------------
//
TInt CAknTree::Compare( const CAknTreeItem& aFirst,
    const CAknTreeItem& aSecond ) const
    {
    TInt value = NULL;
    if ( iCustomOrdering )
        {
        value = iCustomOrdering->Compare( Id( &aFirst ), Id( &aSecond ) );
        }
    else if ( iOrdering )
        {
        value = iOrdering->Compare( aFirst, aSecond );
        }
    else
        {
        TInt first = KMaxTInt;
        TInt second = KMaxTInt;
        if ( aFirst.Parent() )
            {
            first = aFirst.Parent()->Index( &aFirst );
            }
        if  ( aSecond.Parent() )
            {
            second = aSecond.Parent()->Index( &aSecond );
            }
        value = first - second;
        }
    return value;
    }


// ---------------------------------------------------------------------------
// Returns the number of items in the tree.
// ---------------------------------------------------------------------------
//
TInt CAknTree::ItemCount() const
    {
    return iItems.Count();
    }


// ---------------------------------------------------------------------------
// Returns the number of visible items in the tree.
// ---------------------------------------------------------------------------
//
TInt CAknTree::VisibleItemCount() const
    {
    return VisibleDescendantCount();
    }


// ---------------------------------------------------------------------------
// Returns the index of specified item. The index equals to the number of
// tree items in the tree structure before the specified item.
// The value KErrNotFound is returned, if the specified item is not found,
// and this applies also to the root node.
// ---------------------------------------------------------------------------
//
TInt CAknTree::ItemIndex( const CAknTreeItem* aItem ) const
    {
    TInt count = KErrNotFound; // ( -1 )
    if ( iItems.FindInAddressOrder( aItem ) >= 0 )
        {
        const CAknTreeItem* item = aItem;
        const CAknTreeNode* parent = item->Parent();
        while ( parent )
            {
            // Add the number of descendants of each sibling preceeding the
            // item to the count.
            const TInt index = parent->Index( item );
            __ASSERT_DEBUG( index >= 0, User::Invariant() );
            for ( TInt ii = 0; ii < index; ++ii )
                {
                const CAknTreeNode* node = parent->Child( ii )->Node();
                if ( node )
                    {
                    count += node->DescendantCount();
                    }
                }

            // Add the item and its preceeding siblings to the count.
            count += index + 1;

            item = parent;
            parent = item->Parent();
            }
        }
    return count;
    }


// ---------------------------------------------------------------------------
// Similar to ItemIndex, but returns the index from subset of items that
// belong to expanded part of the tree.
// ---------------------------------------------------------------------------
//
TInt CAknTree::VisibleItemIndex( const CAknTreeItem* aItem ) const
    {
    TInt count = KErrNotFound; // ( -1 )
    if ( iItems.FindInAddressOrder( aItem ) >= 0 )
        {
        const CAknTreeItem* item = aItem;
        const CAknTreeNode* parent = item->Parent();
        while ( parent )
            {
            if ( !parent->IsExpanded() )
                {
                return KErrNotFound;
                }

            // Add the number of visible descentants of each sibling preceeding
            // the item to the count.
            const TInt index = parent->Index( item );
            __ASSERT_DEBUG( index >= 0, User::Invariant() );
            for ( TInt ii = 0; ii < index; ++ii )
                {
                const CAknTreeNode* node = parent->Child( ii )->Node();
                if ( node )
                    {
                    count += node->VisibleDescendantCount();
                    }
                }

            // Add the item and its preceeding siblings to the count.
            count += index + 1;

            // All ancestors of specified item has to be expanded in order to
            // the item to be in expanded tree structure.
            if ( parent->IsExpanded() )
                {
                item = parent;
                parent = item->Parent();
                }
            else
                {
                // Specified item is not visible, KErrNotFound returned.
                parent = NULL;
                count = KErrNotFound;
                }
            }
        }
    return count;
    }


// ---------------------------------------------------------------------------
// Returns the tree item at the specified index of the expanded tree.
// ---------------------------------------------------------------------------
//
CAknTreeItem* CAknTree::VisibleItem( TInt aIndex ) const
    {
    if ( aIndex < 0 || aIndex >= iItems.Count() )
        {
        return NULL;
        }

    TAknTreeIterator iterator = Iterator();
    while( aIndex && iterator.HasNext() )
        {
        iterator.Next();
        --aIndex;
        }

    return iterator.Next();
    }


// ---------------------------------------------------------------------------
// Returns the depth of the tree. Iterates through the whole tree structure.
// ---------------------------------------------------------------------------
//
TInt CAknTree::Depth() const
    {
    TAknTreeIterator iterator = Iterator();
    TInt depth = 0;
    while ( iterator.HasNext() )
        {
        CAknTreeItem* item = iterator.Next();
        depth = Max( depth, item->Level() );
        }
    return depth;
    }


// ---------------------------------------------------------------------------
// Finds the specified item from the sorted array of tree items. The constants
// KAknTreeIIDRoot and KAknTreeIIDNone are handled as special cases.
// 
// Note: Recently used items could be cached somehow to eliminate the need to
// lookup them from the table when consecutive calls refer to the same items,
// for example, when adding several items to the same node.
// ---------------------------------------------------------------------------
//
TInt CAknTree::GetItem( TAknTreeItemID aItemId, CAknTreeItem*& aItem ) const
    {
    TInt error = KErrNone;
    if ( aItemId == KAknTreeIIDRoot )
        {
        aItem = const_cast<CAknTree*>( this );
        }
    else if ( aItemId == KAknTreeIIDNone )
        {
        error = KErrNotFound;
        }
    else
        {
        TInt index = iItems.FindInAddressOrder(
            reinterpret_cast<CAknTreeItem*>( aItemId ) );
        if ( index == KErrNotFound )
            {
            error = KErrNotFound;
            }
        else
            {
            aItem = iItems[index];
            }
        }
    return error;
    }


// ---------------------------------------------------------------------------
// Retrieves an item from the tree structure. Panics if the item is not found.
// ---------------------------------------------------------------------------
//
CAknTreeItem* CAknTree::Item( TAknTreeItemID aItemId ) const
    {
    CAknTreeItem* item = NULL;
    TInt error = GetItem( aItemId, item );
    __ASSERT_ALWAYS( item && !error, Panic( EAknHListPanicInvalidItemID ) );
    return item;
    }


// ---------------------------------------------------------------------------
// Retrieves a node from the tree structure. Panics if the node is not found,
// or if the specified item is not a node.
// ---------------------------------------------------------------------------
//
CAknTreeNode* CAknTree::Node( TAknTreeItemID aNodeId ) const
    {
    CAknTreeNode* node = Item( aNodeId )->Node();
    __ASSERT_ALWAYS( node, Panic( EAknHListPanicInvalidItemType ) );
    return node;
    }


// ---------------------------------------------------------------------------
// Adds an item to the tree structure.
// ---------------------------------------------------------------------------
//
TAknTreeItemID CAknTree::AddItemL( CAknTreeItem* aItem,
    TAknTreeItemID aParent, TBool aDrawNow )
    {
    __ASSERT_DEBUG( aItem, User::Invariant() );

    // Add item to the specified parent node.
    CAknTreeNode* parent = Node( aParent );

    if ( iOrdering )
        {
        // Let ordering determine the position of the new child.
        parent->AddChildL( aItem );
        }
    else
        {
        // Append to the end, as custom ordering cannot be used to determine
        // the correct position when inserting new items to the tree.
        parent->AddChildL( aItem, parent->ChildCount() );
        }

    // Store pointer also in lookup table.
    TInt error = iItems.InsertInAddressOrder( aItem );
    if ( error )
        {
        parent->RemoveChild( aItem );
        User::Leave( error );
        }

    aItem->SetParent( parent );

    NotifyObservers( MAknTreeObserver::EItemAdded, aItem, aDrawNow );

    return Id( aItem );
    }


// ---------------------------------------------------------------------------
// Moves the specified item to specified target node. The method has to make
// sure that the target node is not a descendant of the moved item in order
// to keep the tree structure intact.
// ---------------------------------------------------------------------------
//
void CAknTree::MoveItemL( TAknTreeItemID aItem, TAknTreeItemID aTargetNode,
    TBool aDrawNow )
    {
    CAknTreeItem* item = Item( aItem );
    CAknTreeNode* targetNode = Node( aTargetNode );

    // The current parent of the moved item.
    CAknTreeNode* parent = item->Parent();

    // Move is necessary only when target node differs from current node.
    if ( targetNode != parent )
        {
        // Check that the moved item is neither the target node nor an ancestor
        // of target node. This should also ensure that the root is not moved.
        CAknTreeNode* ancestor = targetNode;
        while ( ancestor )
            {
            if ( ancestor == item )
                {
                User::Leave( KErrArgument );
                }
            ancestor = ancestor->Parent();
            }

        // Move the item to the target node.
        targetNode->AddChildL( item );
        item->SetParent( targetNode );
        if ( parent )
            {
            parent->RemoveChild( item );
            }
        
        NotifyObservers( MAknTreeObserver::EItemMoved, item, aDrawNow );
        }
    }


// ---------------------------------------------------------------------------
// Removes an item from the tree structure. If the specified item is not
// found, method is paniced with panic code EAknHListPanicInvalidItemID.
//
// When removed item is a node with descendants, the node and its descendants
// are removed from the list separately and each removal is also reported
// separately to the observers.
//
// Note: Observers are notified of the removal before the item is actually
// removed from the tree and deleted, so that the observers can still query
// the item's position in the tree.
// ---------------------------------------------------------------------------
//
void CAknTree::RemoveItem( TAknTreeItemID aItem, TBool aDrawNow )
    {
    // Get the item from the array.    
    CAknTreeItem* item = Item( aItem );
    
    TBool drawNow( EFalse );

    // Remove from array and delete the descendants of node non-recursively.
    if ( item->IsNode() )
        {
        TAknTreeIterator iterator = Iterator( item->Node(), NULL );
        CAknTreeItem* current = iterator.Last();
        iterator.SetCurrent( current ); 
        while ( current )
            {
            CAknTreeItem* previous = iterator.Previous();
            if ( previous == NULL)
            	{
            	drawNow = aDrawNow;
            	}

            // Notify tree observers of removal before the item is removed.
            NotifyObservers( MAknTreeObserver::EItemRemoveBegin, current, EFalse );

            // Remove item from the table.
            TInt index = iItems.FindInAddressOrder( current );
            __ASSERT_DEBUG( index >= 0, User::Invariant()  );
            iItems.Remove( index );

            // Remove item from its parent node.
            CAknTreeNode* parent = current->Parent();
            __ASSERT_DEBUG( parent, User::Invariant() );
            parent->RemoveChild( current );
            current->SetParent( NULL );

            __ASSERT_DEBUG( current->IsLeaf() || 
                current->Node()->ChildCount() == 0, User::Invariant() );

            // Notify tree observers when the item has been removed.
            NotifyObservers( MAknTreeObserver::EItemRemoveEnd, current, drawNow );

            // Notify also tree list observers of removal.
            iList.NotifyObservers( MAknTreeListObserver::EItemRemoved,
                Id( current ) );

            delete current;
            current = previous;
            }
        }

    // Remove the specified item, unless it is the root node.
    if ( item != this )
        {
        // Notify tree observers before removing the item.
        NotifyObservers( MAknTreeObserver::EItemRemoveBegin, item, EFalse );

        // Remove the item from array and from the tree and delete it.
        TInt index = iItems.FindInAddressOrder( item );
        __ASSERT_DEBUG( index >= 0, User::Invariant() );
        iItems.Remove( index );

        CAknTreeNode* parent = item->Parent();
        __ASSERT_DEBUG( parent, User::Invariant() );
        parent->RemoveChild( item );
        item->SetParent( NULL );

        __ASSERT_DEBUG( item->IsLeaf() || item->Node()->ChildCount() == 0,
            User::Invariant() );

        // Notify tree observers after the item has been removed.
        NotifyObservers( MAknTreeObserver::EItemRemoveEnd, item, aDrawNow );

        // Notify also tree list observers of removal.
        iList.NotifyObservers( MAknTreeListObserver::EItemRemoved,
            Id( item ) );

        delete item;
        }
    }


// ---------------------------------------------------------------------------
// Expands the specified node.
// ---------------------------------------------------------------------------
//
void CAknTree::ExpandNode( TAknTreeItemID aNode, TBool aDrawNow )
    {
    CAknTreeNode* node = Node( aNode );
    DoExpandNode( node, aDrawNow );
    }


// ---------------------------------------------------------------------------
// Collapses the specified node and removes the children from collapsed node
// that are not set perisitent or do not contain any persistent descendants.
// ---------------------------------------------------------------------------
//
void CAknTree::CollapseNode( TAknTreeItemID aNode, TBool aDrawNow )
    {
    CAknTreeNode* node = Node( aNode );

    node->Collapse();
    iList.NotifyObservers( MAknTreeListObserver::ENodeCollapsed, aNode );
    NotifyObservers( MAknTreeObserver::ENodeCollapsed, node, aDrawNow );

    if ( aNode != KAknTreeIIDRoot )
        {
        // Remove all the children from the node that are not persistent or
        // marked and do not contain any persistent or marked descendants.
        for ( TInt ii = node->ChildCount() - 1; ii >= 0; --ii )
            {
            CAknTreeItem* item = node->Child( ii );
            __ASSERT_DEBUG( item, User::Invariant() );
            if ( item->IsRemovableFromCollapsedNode() )
                {
                RemoveItem( Id( item ), EFalse );
                }
            }
        }
    }


// ---------------------------------------------------------------------------
// Checks whether the specified node is expanded.
// ---------------------------------------------------------------------------
//
TBool CAknTree::IsExpanded( TAknTreeItemID aNode ) const
    {
    return Node( aNode )->IsExpanded();
    }


// ---------------------------------------------------------------------------
// Returns the child count for the specified node.
// ---------------------------------------------------------------------------
//
TInt CAknTree::ChildCount( TAknTreeItemID aNode ) const
    {
    return Node( aNode )->ChildCount();
    }


// ---------------------------------------------------------------------------
// Returns the item ID of specified child for a tree node.
// ---------------------------------------------------------------------------
//
TAknTreeItemID CAknTree::Child( TAknTreeItemID aNode, TInt aIndex ) const
    {
    return Id( Node( aNode )->Child( aIndex ) );
    }


// ---------------------------------------------------------------------------
// Returns the item ID of a parent of specified item.
// ---------------------------------------------------------------------------
//
TAknTreeItemID CAknTree::Parent( TAknTreeItemID aItem ) const
    {
    return Id( Item( aItem )->Parent() );
    }


// ---------------------------------------------------------------------------
// Adds a tree observer.
// ---------------------------------------------------------------------------
//
void CAknTree::AddObserverL( MAknTreeObserver* aObserver )
    {
    iObservers.InsertInAddressOrderL( aObserver );
    }


// ---------------------------------------------------------------------------
// Removes a tree observer.
// ---------------------------------------------------------------------------
//
TInt CAknTree::RemoveObserver( MAknTreeObserver* aObserver )
    {
    TInt index = iObservers.FindInAddressOrder( aObserver );
    if ( index != KErrNotFound )
        {
        iObservers.Remove( index );
        return KErrNone;
        }
    else
        {
        return KErrNotFound;
        }
    }


// ---------------------------------------------------------------------------
// Checks whether the specified item is marked.
// ---------------------------------------------------------------------------
//
TBool CAknTree::IsMarked( TAknTreeItemID aItem ) const
    {
    return Item( aItem )->IsMarked();
    }


// ---------------------------------------------------------------------------
// Sets the specified item marked or unmarked.
// ---------------------------------------------------------------------------
//
void CAknTree::SetMarked( TAknTreeItemID aItem, TBool aMarked, TBool aDrawNow )
    {
    CAknTreeItem* item = Item( aItem );
    if ( item->IsMarkable() )
        {        
        if ( item->IsNode() )
            {
            // When specified item is a node, the same marking is set to
            // every descendant as well.
            TAknTreeIterator iterator = Iterator( item->Node(), NULL );
            while ( iterator.HasNext() )
                {
                iterator.Next()->SetMarked( aMarked );
                }
            }

        item->SetMarked( aMarked );
        
        if ( aMarked == EFalse)
        	{
        	CAknTreeNode* parent = item->Parent();
        	if ( parent && parent->IsNode() && parent->IsMarkable() && parent->IsMarked() )
        		{
        		TAknTreeIterator iterator = Iterator( parent->Node(), NULL );
            	TBool marked = EFalse;	
            	
            	while ( iterator.HasNext() )
                	{
                	CAknTreeItem* item = iterator.Next();
                	if ( item->IsMarkable() && item->IsMarked() )
                		{
                		marked = ETrue;
                		break;
                		}
                	}
                // all items under the parent are unmarked, unmark parent	
        		if ( !marked )
        			{
        			parent->SetMarked( EFalse );
        			}
        		
        		}
        	
        	}
        
        iList.NotifyObservers( aMarked ? MAknTreeListObserver::EItemMarked :
            MAknTreeListObserver::EItemUnmarked, Id( item ) );
        NotifyObservers( MAknTreeObserver::EItemModified, item, aDrawNow );        
        }
    }


// ---------------------------------------------------------------------------
// Enables/disables marking for specified list item.
// ---------------------------------------------------------------------------
//
void CAknTree::EnableMarking( TAknTreeItemID aItem, TBool aEnable )
    {
    CAknTreeItem* item = Item( aItem );
    item->SetMarkable( aEnable );
    }


// ---------------------------------------------------------------------------
// Gets all the marked items from the specified node to the given array.
// ---------------------------------------------------------------------------
//
void CAknTree::GetMarkedItemsL( TAknTreeItemID aNode,
    RArray<TAknTreeItemID>& aMarkedItems ) const
    {
    aMarkedItems.Reset();
    if ( aNode == KAknTreeIIDRoot )
        {
        // Get marked items from the tree by iterating through array.
        CAknTreeItem* item = NULL;
        const TInt count = iItems.Count();
        for ( TInt ii = 0; ii < count; ++ii )
            {
            item = iItems[ii];
            __ASSERT_DEBUG( item, User::Invariant() );
            if ( item->IsMarked() )
                {
                aMarkedItems.AppendL( Id( item ) );
                }
            }
        }
    else
        {
        // Get marked items only from the specified node with iterator.
        TAknTreeIterator iterator( Node( aNode ), NULL );
        CAknTreeItem* item = NULL;
        while ( iterator.HasNext() )
            {
            item = iterator.Next();
            __ASSERT_DEBUG( item, User::Invariant() );
            if ( item->IsMarked() )
                {
                aMarkedItems.AppendL( Id( item ) );
                }
            }
        }
    }


// ---------------------------------------------------------------------------
// Checks whether the specified node is empty.
// ---------------------------------------------------------------------------
//
TBool CAknTree::IsEmpty( TAknTreeItemID aNode ) const
    {
    return Node( aNode )->IsEmpty();
    }


// ---------------------------------------------------------------------------
// Sets whether the node appears as non-empty when it is empty.
// ---------------------------------------------------------------------------
//
void CAknTree::SetNonEmpty( TAknTreeItemID aNode, TBool aNonEmpty,
    TBool aDrawNow )
    {
    CAknTreeNode* node = Node( aNode );
    node->SetNonEmpty( aNonEmpty );
    NotifyObservers( MAknTreeObserver::EItemModified, node, aDrawNow );
    }


// ---------------------------------------------------------------------------
// Checks whether the specified item is persistent.
// ---------------------------------------------------------------------------
//
TBool CAknTree::IsPersistent( TAknTreeItemID aItem ) const
    {
    return Item( aItem )->IsPersistent();
    }


// ---------------------------------------------------------------------------
// Sets the specified item persistent or non-persistent.
// ---------------------------------------------------------------------------
//
void CAknTree::SetPersistent( TAknTreeItemID aItem, TBool aPersistent )
    {
    Item( aItem )->SetPersistent( aPersistent );
    }


// ---------------------------------------------------------------------------
// Returns iterator for the expanded tree structure.
// ---------------------------------------------------------------------------
//
TAknTreeIterator CAknTree::Iterator() const
    {
    return TAknTreeIterator( const_cast<CAknTree*>( this ),
        KAknSkipCollapsedNodeContents );
    }


// ---------------------------------------------------------------------------
// Returns iterator for the specified node.
// ---------------------------------------------------------------------------
//
TAknTreeIterator CAknTree::Iterator( CAknTreeNode* aNode, TUint aFlags ) const
    {
    return TAknTreeIterator( aNode, aFlags );
    }


// ---------------------------------------------------------------------------
// Notifies the observers that an item in the tree has been modified.
// ---------------------------------------------------------------------------
//
void CAknTree::ItemModified( CAknTreeItem* aItem )
    {
    NotifyObservers( MAknTreeObserver::EItemModified, aItem, ETrue );
    }


// ---------------------------------------------------------------------------
// Adds an icon to the tree and returns the index of created icon.
// ---------------------------------------------------------------------------
//
TInt CAknTree::AddIconL( const TAknsItemID& aId, const TDesC& aFilename,
    TInt aBitmapId, TInt aMaskId, TScaleMode aScaleMode )
    {
    TInt newIconId = AvailableIconId();
    CAknTreeListIcon* icon = CAknTreeListIcon::NewLC( newIconId, aId,
        aFilename, aBitmapId, aMaskId, aScaleMode );
    AddIconL( icon );
    CleanupStack::Pop( icon );
    return newIconId;
    }


// ---------------------------------------------------------------------------
// Adds an icon to the tree and returns the index of created icon.
// ---------------------------------------------------------------------------
//
TInt CAknTree::AddIconL( CFbsBitmap* aIcon, CFbsBitmap* aMask, 
    TBool aTransferOwnership, TScaleMode aScaleMode )
    {
    TInt newIconId = AvailableIconId();
    CAknTreeListIcon* icon = CAknTreeListIcon::NewLC( newIconId, aIcon, aMask,
        aTransferOwnership, aScaleMode );
    AddIconL( icon );
    CleanupStack::Pop( icon );
    return newIconId;
    }


// ---------------------------------------------------------------------------
// Adds colored icon to the tree.
// ---------------------------------------------------------------------------
//
TInt CAknTree::AddColorIconL( const TAknsItemID& aId,
    const TAknsItemID& aColorId, TInt aColorIndex, const TDesC& aFilename,
    TInt aBitmapId, TInt aMaskId, TRgb aDefaultColor, TScaleMode aScaleMode )
    {
    TInt newIconId = AvailableIconId();
    CAknTreeListIcon* icon = CAknTreeListIcon::NewLC( newIconId, aId,
        aColorId, aColorIndex, aFilename, aBitmapId, aMaskId, aDefaultColor,
        aScaleMode );
    AddIconL( icon );
    CleanupStack::Pop( icon );
    return newIconId;
    }


// ---------------------------------------------------------------------------
// Sets icon for specified ID.
// ---------------------------------------------------------------------------
//
void CAknTree::SetIconL( TInt aIconId, const TAknsItemID& aId,
    const TDesC& aFilename, TInt aBitmapId, TInt aMaskId,
    TScaleMode aScaleMode )
    {
    CAknTreeListIcon* icon = CAknTreeListIcon::NewLC( aIconId, aId, aFilename,
        aBitmapId, aMaskId, aScaleMode );
    AddIconL( icon );
    CleanupStack::Pop( icon );
    }


void CAknTree::SetIconL( TInt aIconId, CFbsBitmap* aIcon, CFbsBitmap* aMask,
    TBool aTransferOwnership, TScaleMode aScaleMode )
    {
    CAknTreeListIcon* icon = CAknTreeListIcon::NewLC( aIconId, aIcon, aMask,
        aTransferOwnership, aScaleMode );
    AddIconL( icon );
    CleanupStack::Pop( icon );
    }


// ---------------------------------------------------------------------------
// Sets color icon for specified ID.
// ---------------------------------------------------------------------------
//
void CAknTree::SetColorIconL( TInt aIconId, const TAknsItemID& aId,
    const TAknsItemID& aColorId, TInt aColorIndex, const TDesC& aFilename,
    TInt aBitmapId, TInt aMaskId, TRgb aDefaultColor, TScaleMode aScaleMode )
    {
    CAknTreeListIcon* icon = CAknTreeListIcon::NewLC( aIconId, aId, aColorId,
        aColorIndex, aFilename, aBitmapId, aMaskId, aDefaultColor,
        aScaleMode );
    AddIconL( icon );
    CleanupStack::Pop( icon );
    }


// ---------------------------------------------------------------------------
// Removes previously added icon from the tree.
// ---------------------------------------------------------------------------
//
void CAknTree::RemoveIconL( TInt aIconId )
    {
    // Pre-defined icons constructed by the tree cannot be removed.
    if ( aIconId <= EPreDefinedIconIdRange )
        {
        User::Leave( KErrArgument );
        }

    TInt index = iIcons.FindInOrder( aIconId, CAknTreeListIcon::CompareId );
    if ( index != KErrNotFound )
        {
        delete iIcons[index];
        iIcons.Remove( index );
        }
    }


// ---------------------------------------------------------------------------
// Returns pointer to the requested icon.
// ---------------------------------------------------------------------------
//
CAknTreeListIcon* CAknTree::Icon( TInt aIconId ) const
    {
    CAknTreeListIcon* icon = NULL;
    TInt index = iIcons.FindInOrder( aIconId, CAknTreeListIcon::CompareId );
    if ( index >= NULL )
        {
        icon = iIcons[index];
        }
    return icon;
    }


// ---------------------------------------------------------------------------
// Draws the specified icon.
// ---------------------------------------------------------------------------
//
TInt CAknTree::DrawIcon( TInt aIconId, const TSize& aSize, CWindowGc& aGc,
    const TPoint& aPoint, const TRect& aSourceRect )
    {
    TInt value = KErrNotFound;
    CAknTreeListIcon* icon = Icon( aIconId );
    if ( icon && icon->Bitmap() )
        {
        icon->SetSize( aSize );
        aGc.BitBltMasked( aPoint, icon->Bitmap(), aSourceRect,
            icon->Mask(), ETrue );
        value = KErrNone;
        }
    return value;
    }


// ---------------------------------------------------------------------------
// Draws the given text string.
// ---------------------------------------------------------------------------
//
void CAknTree::DrawText( CWindowGc& aGc, const TRect& aRect,
    const TAknTextComponentLayout& aTextLayout, const TDesC& aText,
    const CFont* aFont, const CAknTreeItem* aItem, TBool aFocused,
    TBool aMarquee )
    {
    TRgb textColor;
    TAknsQsnTextColorsIndex index = 
        aFocused ? EAknsCIQsnTextColorsCG10 : EAknsCIQsnTextColorsCG6;
    AknsUtils::GetCachedColor( AknsUtils::SkinInstance(), textColor,
        KAknsIIDQsnTextColors, index );

    TAknLayoutText layoutText;
    layoutText.LayoutText( aRect, aTextLayout.LayoutLine(), aFont );

    if ( iMarquee )
        {
        if ( aFocused && aItem != iMarqueeItem )
            {
            iMarqueeItem = aItem;
            iMarquee->Reset();
            }
        else if ( !aFocused && aItem == iMarqueeItem )
            {
            iMarqueeItem = NULL;
            iMarquee->Stop();
            }
        }

    // Marquee scrolling is used when the given text does not fit in the given
    // layout rectangle, but only if text is focused, marquee is allowed to be
    // used with the given text, and marquee is enabled for the list.
    TBool useMarquee = aFocused && aMarquee && iMarquee &&
        iMarquee->IsMarqueeOn() && layoutText.TextRect().Width() < 
            layoutText.Font()->TextWidthInPixels( aText );
    
    if ( !useMarquee || iMarquee->DrawText( aGc, aRect, aTextLayout, aText,
            aFont, textColor ) )
        {
        layoutText.DrawText( aGc, aText, ETrue, textColor );
        }
    }


// ---------------------------------------------------------------------------
// Handles skin change by reconstruction all the used icons.
// ---------------------------------------------------------------------------
//
void CAknTree::HandleSkinChangeL()
    {
    for ( TInt ii = 0; ii < iIcons.Count(); ++ii )
        {
        iIcons[ii]->ReconstructL();
        }
    }


// ---------------------------------------------------------------------------
// Enables or disables marquee scrolling.
// ---------------------------------------------------------------------------
//
void CAknTree::EnableMarquee( TBool aEnable )
    {
    if ( iMarquee )
        {
        iMarquee->EnableMarquee( aEnable );
        }
    }


// ---------------------------------------------------------------------------
// Returns whether marquee scrolling is enabled.
// ---------------------------------------------------------------------------
//
TBool CAknTree::IsMarqueeOn() const
    {
    return iMarquee ? iMarquee->IsMarqueeOn() : EFalse;
    }


// ---------------------------------------------------------------------------
// Redraw request from marquee control.
// ---------------------------------------------------------------------------
//
TInt CAknTree::MarqueeRedrawRequest( TAny* aThis )
    {
    CAknTree* tree = static_cast<CAknTree*>( aThis );
    return tree ? tree->DoMarqueeRedrawRequest() : NULL;
    }


// ---------------------------------------------------------------------------
// Enables tabulator mode expand/collapse function indicators.
// ---------------------------------------------------------------------------
//
void CAknTree::EnableTabModeFunctionIndicatorsL( TBool aEnable )
    {
    if ( iFlags.IsSet( ETabModeFunctionIndicators ) && !aEnable )
        {
        // Change to normal expand/collapse function indicators.
        SetIconL( ECollapseFunctionIndication, KAknsIIDQgnIndiHlColSuper,
            AknIconUtils::AvkonIconFileName(),
            EMbmAvkonQgn_indi_hl_col_super,
            EMbmAvkonQgn_indi_hl_col_super_mask,
            EAspectRatioPreserved );

        SetIconL( EExpandFunctionIndication, KAknsIIDQgnIndiHlExpSuper,
            AknIconUtils::AvkonIconFileName(),
            EMbmAvkonQgn_indi_hl_exp_super,
            EMbmAvkonQgn_indi_hl_exp_super_mask,
            EAspectRatioPreserved );

        iFlags.Clear( ETabModeFunctionIndicators );
        }
    else if ( !iFlags.IsSet( ETabModeFunctionIndicators ) && aEnable )
        {
        // Change to tab mode expand/collapse function indicators.
        SetIconL( ECollapseFunctionIndication, KAknsIIDQgnIndiHlTabColSuper,
            AknIconUtils::AvkonIconFileName(),
            EMbmAvkonQgn_indi_col_super,
            EMbmAvkonQgn_indi_col_super_mask,
            EAspectRatioPreserved );

        SetIconL( EExpandFunctionIndication, KAknsIIDQgnIndiHlTabExpSuper,
            AknIconUtils::AvkonIconFileName(),
            EMbmAvkonQgn_indi_exp_super,
            EMbmAvkonQgn_indi_exp_super_mask,
            EAspectRatioPreserved );

        iFlags.Set( ETabModeFunctionIndicators );
        }
    }


// ---------------------------------------------------------------------------
// Checks whether tabulator mode expand/collapse function indicators are
// enabled.
// ---------------------------------------------------------------------------
//
TBool CAknTree::TabModeFunctionIndicators() const
    {
    return iFlags.IsSet( ETabModeFunctionIndicators );
    }


// ---------------------------------------------------------------------------
// From class CAknTreeItem.
// Returns the type of concrete item class.
// ---------------------------------------------------------------------------
//
TInt CAknTree::Type() const
    {
    return AknTreeList::KTree;
    }


// ---------------------------------------------------------------------------
// From class CAknTreeItem.
// Instance of CAknTree is always set as tree root, so it can just return
// pointer to itself.
// ---------------------------------------------------------------------------
//
CAknTree* CAknTree::Root() const
    {
    return const_cast<CAknTree*>( this );
    }


// ---------------------------------------------------------------------------
// From class CAknTreeNode.
// Changes the state of every node in the tree to expanded.
// ---------------------------------------------------------------------------
//
void CAknTree::Expand()
    {
    TAknTreeIterator iterator( this, NULL );
    while ( iterator.HasNext() )
        {
        CAknTreeItem* item = iterator.Next();
        if ( item->IsNode() )
            {
            DoExpandNode( item->Node(), EFalse );
            }
        }
    }


// ---------------------------------------------------------------------------
// From class CAknTreeNode.
// Changes the state of every node in the tree to collapsed.
// ---------------------------------------------------------------------------
//
void CAknTree::Collapse()
    {
    TAknTreeIterator iterator( this, NULL );
    iterator.SetCurrent( iterator.Last() );
    iterator.Next();
    while( iterator.HasPrevious() )
        {
        CAknTreeItem* item = iterator.Previous();
        if ( item->IsNode() )
            {
            // Note: Might be a good idea to add for internal use an overload
            // accepting the pointer to the collapsed node as parameter.
            CollapseNode( Id( item->Node() ), EFalse );
            }
        }
    }


// ---------------------------------------------------------------------------
// C++ constructor.
// ---------------------------------------------------------------------------
//
CAknTree::CAknTree( CAknTreeList& aList, CAknTreeOrdering* aOrdering )
    : CAknTreeNode( EExpanded ),
      iList( aList ),
      iOrdering( aOrdering ),
      iObservers( KObserverArrayGranularity )
    {
    }


// ---------------------------------------------------------------------------
// Second phase constructor.
// ---------------------------------------------------------------------------
//
void CAknTree::ConstructL()
    {
    TCallBack callBack( CAknTree::MarqueeRedrawRequest, this );
    iMarquee = CAknMarqueeControl::NewL();
    iMarquee->SetRedrawCallBack( callBack );

    SetIconL( ECollapseFunctionIndication, KAknsIIDQgnIndiHlColSuper,
        AknIconUtils::AvkonIconFileName(),
        EMbmAvkonQgn_indi_hl_col_super,
        EMbmAvkonQgn_indi_hl_col_super_mask,
        EAspectRatioPreserved );

    SetIconL( EExpandFunctionIndication, KAknsIIDQgnIndiHlExpSuper,
        AknIconUtils::AvkonIconFileName(),
        EMbmAvkonQgn_indi_hl_exp_super,
        EMbmAvkonQgn_indi_hl_exp_super_mask,
        EAspectRatioPreserved );

    SetIconL( ELineBranchIndication, KAknsIIDQgnIndiHlLineBranch,
        AknIconUtils::AvkonIconFileName(),
        EMbmAvkonQgn_indi_hl_line_branch,
        EMbmAvkonQgn_indi_hl_line_branch,
        EAspectRatioNotPreserved );

    SetIconL( ELineEndIndication, KAknsIIDQgnIndiHlLineEnd,
        AknIconUtils::AvkonIconFileName(),
        EMbmAvkonQgn_indi_hl_line_end,
        EMbmAvkonQgn_indi_hl_line_end_mask,
        EAspectRatioNotPreserved );

    SetIconL( ELineStraightIndication, KAknsIIDQgnIndiHlLineStraight,
        AknIconUtils::AvkonIconFileName(),
        EMbmAvkonQgn_indi_hl_line_straight,
        EMbmAvkonQgn_indi_hl_line_straight_mask,
        EAspectRatioNotPreserved );

    SetIconL( EDefaultFileIndication, KAknsIIDQgnPropHlFile,
        AknIconUtils::AvkonIconFileName(),
        EMbmAvkonQgn_prop_hl_file,
        EMbmAvkonQgn_prop_hl_file_mask,
        EAspectRatioPreserved );

    SetIconL( EClosedFolderIndication, KAknsIIDQgnPropHlFolder,
        AknIconUtils::AvkonIconFileName(),
        EMbmAvkonQgn_prop_hl_folder,
        EMbmAvkonQgn_prop_hl_folder_mask,
        EAspectRatioPreserved );

    SetIconL( EOpenFolderIndication, KAknsIIDQgnPropHlFolderOpen,
        AknIconUtils::AvkonIconFileName(),
        EMbmAvkonQgn_prop_hl_folder_open,
        EMbmAvkonQgn_prop_hl_folder_open_mask,
        EAspectRatioPreserved );

    SetColorIconL( EMarkedIndication, KAknsIIDQgnIndiMarkedAdd,
        KAknsIIDQsnIconColors, EAknsCIQsnIconColorsCG13,
        AknIconUtils::AvkonIconFileName(),
        EMbmAvkonQgn_indi_marked_add,
        EMbmAvkonQgn_indi_marked_add_mask,
        KRgbBlack, EAspectRatioPreserved );

    SetColorIconL( EHighlightedMarkedIndication, KAknsIIDQgnIndiMarkedAdd,
        KAknsIIDQsnIconColors, EAknsCIQsnIconColorsCG16,
        AknIconUtils::AvkonIconFileName(),
        EMbmAvkonQgn_indi_marked_add,
        EMbmAvkonQgn_indi_marked_add_mask,
        KRgbBlack, EAspectRatioPreserved );

    }


// ---------------------------------------------------------------------------
// Sends the specified event to every registered observer.
// ---------------------------------------------------------------------------
//
void CAknTree::NotifyObservers( MAknTreeObserver::TEvent aEvent,
    CAknTreeItem* aItem, TBool aDrawNow )
    {
    const TInt count = iObservers.Count();
    for ( TInt ii = 0; ii < count; ++ii )
        {
        iObservers[ii]->HandleTreeEvent( aEvent, aItem, aDrawNow );
        }
    }


// ---------------------------------------------------------------------------
// Sends notification to tree observers when requested by the marquee control.
// ---------------------------------------------------------------------------
//
TInt CAknTree::DoMarqueeRedrawRequest()
    {
    // Makes sure the tree still contains the scrolled item before sending
    // the notification to the observers.
    CAknTreeItem* item;
    if ( !GetItem( Id( iMarqueeItem ), item ) )
        {
        ItemModified( item );
        return 1;
        }
    return NULL;
    }


// ---------------------------------------------------------------------------
// Searches for available icon ID.
// ---------------------------------------------------------------------------
//
TInt CAknTree::AvailableIconId() const
    {
    const TInt count = iIcons.Count();
    TInt last = count ? iIcons[count - 1]->Id() : NULL;
    TInt next = Max( last, EPreDefinedIconIdRange ) + 1;

    if ( next <= EPreDefinedIconIdRange )
        {
        next = KMaxTInt;
        TBool found = EFalse;
        for ( TInt ii = 0; ii < count - 1 && !found; ++ii )
            {
            if ( iIcons[ii]->Id() < iIcons[ii + 1]->Id() - 1 )
                {
                next = iIcons[ii]->Id() + 1;
                found = ETrue;
                }
            }
        }

    return next;
    }


// ---------------------------------------------------------------------------
// Adds icon to the icon array.
// ---------------------------------------------------------------------------
//
void CAknTree::AddIconL( CAknTreeListIcon* aIcon )
    {
    __ASSERT_DEBUG( aIcon, User::Invariant() );
    TLinearOrder<CAknTreeListIcon> order( CAknTreeListIcon::Compare );
    TInt index = iIcons.FindInOrder( aIcon, order );
    if ( index == KErrNotFound )
        {
        // Add icon to the array.
        iIcons.InsertInOrderL( aIcon, order );
        }
    else
        {
        // Replace existing icon in the array.
        delete iIcons[index];
        iIcons[index] = aIcon;
        }
    }


// ---------------------------------------------------------------------------
// Sorts the list by sorting every node in the tree separately.
// ---------------------------------------------------------------------------
//
void CAknTree::Sort( TBool aDrawNow )
    {
    CAknTreeNode::Sort();
    for ( TInt ii = 0; ii < iItems.Count(); ++ii )
        {
        CAknTreeNode* node = iItems[ii]->Node();
        if ( node )
            {
            node->Sort();
            }
        }

    NotifyObservers( MAknTreeObserver::ETreeSorted, NULL, aDrawNow );
    }


// ---------------------------------------------------------------------------
// Expands the specified node.
// ---------------------------------------------------------------------------
//
void CAknTree::DoExpandNode( CAknTreeNode* aNode, TBool aDrawNow )
    {
    __ASSERT_DEBUG( aNode, User::Invariant() );
    iList.NotifyObservers( MAknTreeListObserver::ENodeExpanded, Id( aNode ) );
    aNode->Expand();
    NotifyObservers( MAknTreeObserver::ENodeExpanded, aNode, aDrawNow );
    }


// ---------------------------------------------------------------------------
// From class CAknTreeItem.
// Empty implementation for the pure virtal function declared in CAknTreeItem.
// ---------------------------------------------------------------------------
//
void CAknTree::Draw( CWindowGc& /*aGc*/, const TRect& /*aItemRect*/,
    const TRect& /*aRect*/, TBool /*aFocused*/ ) const
    {
    // The root node should never be drawn!
    __ASSERT_DEBUG( EFalse, User::Invariant() );
    }

