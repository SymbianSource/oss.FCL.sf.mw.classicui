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
* Description:  Implementation for CAknSingleStyleTreeList class.
*
*/


#include "aknsinglestyletreelist.h"
#include "aknsinglestyletreenode.h"
#include "aknsinglestyletreeleaf.h"
#include "aknsinglestyletreeordering.h"
#include "akntree.h"
#include "aknhlistlib.h"
#include "akntreelistinternalconstants.h"
#include "akntreelistview.h"

#include <AknTasHook.h> // for testability hooks
/** Set of flags that cannot be set for single style hierarchical list. */
const TInt KRestrictedListFlags = KAknTreeListMarkable;


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
EXPORT_C CAknSingleStyleTreeList* CAknSingleStyleTreeList::NewL()
    {
    CAknSingleStyleTreeList* self = CAknSingleStyleTreeList::NewLC();
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
EXPORT_C CAknSingleStyleTreeList* CAknSingleStyleTreeList::NewLC()
    {
    CAknSingleStyleTreeList* self = new( ELeave ) CAknSingleStyleTreeList;
    CleanupStack::PushL( self );
    self->ConstructL();
    AKNTASHOOK_ADDL( self, "CAknSingleStyleTreeList" );
    return self;
    }


// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
EXPORT_C CAknSingleStyleTreeList* CAknSingleStyleTreeList::NewL(
    const CCoeControl& aContainer )
    {
    CAknSingleStyleTreeList* self
        = CAknSingleStyleTreeList::NewLC( aContainer );
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
EXPORT_C CAknSingleStyleTreeList* CAknSingleStyleTreeList::NewLC(
    const CCoeControl& aContainer )
    {
    CAknSingleStyleTreeList* self = new ( ELeave ) CAknSingleStyleTreeList;
    CleanupStack::PushL( self );
    self->ConstructL( aContainer );
    AKNTASHOOK_ADDL( self, "CAknSingleStyleTreeList" );
    return self;
    }


// ---------------------------------------------------------------------------
// Destructor.
// ---------------------------------------------------------------------------
//
CAknSingleStyleTreeList::~CAknSingleStyleTreeList()
    {
    AKNTASHOOK_REMOVE();
    }


// ---------------------------------------------------------------------------
// Construct and add new leaf to the tree.
// ---------------------------------------------------------------------------
//
EXPORT_C TAknTreeItemID CAknSingleStyleTreeList::AddLeafL(
    TAknTreeItemID aParent, const TDesC& aText, TUint32 aFlags,
    TBool aDrawNow )
    {
    TUint32 flags = NULL;
    if ( aFlags & EPersistent )
        {
        flags |= CAknSingleStyleTreeLeaf::EPersistent;
        }
    if ( aFlags & EMarked )
        {
        flags |= CAknSingleStyleTreeLeaf::EMarked;
        }
     
    CAknSingleStyleTreeLeaf* leaf = 
        CAknSingleStyleTreeLeaf::NewLC( aText, flags );
    TAknTreeItemID id = Tree().AddItemL( leaf, aParent, aDrawNow );
    CleanupStack::Pop( leaf );
    return id;
    }


// ---------------------------------------------------------------------------
// Construct and add new node to the tree.
// ---------------------------------------------------------------------------
//
EXPORT_C TAknTreeItemID CAknSingleStyleTreeList::AddNodeL(
    TAknTreeItemID aParent, const TDesC& aText, TUint32 aFlags,
    TBool aDrawNow )
    {
    TUint32 flags = NULL;
    if ( aFlags & EPersistent )
        {
        flags |= CAknSingleStyleTreeNode::EPersistent;
        }
    if ( aFlags & EMarked )
        {
        flags |= CAknSingleStyleTreeNode::EMarked;
        }
    if ( aFlags & EExpanded )
        {
        flags |= CAknSingleStyleTreeNode::EExpanded;
        }
    if ( aFlags & ENonEmpty )
        {
        flags |= CAknSingleStyleTreeNode::ENonEmpty;
        }
 
    CAknSingleStyleTreeNode* node = 
        CAknSingleStyleTreeNode::NewLC( aText, flags );
    TAknTreeItemID id = Tree().AddItemL( node, aParent, aDrawNow );
    CleanupStack::Pop( node );
    return id;
    }


// ---------------------------------------------------------------------------
// Sorts the list.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknSingleStyleTreeList::SortL( TOrdering aOrdering,
    TBool aDrawNow )
    {
    CAknSingleStyleTreeOrdering::TOrderingType type = 
        CAknSingleStyleTreeOrdering::EAscending;
    if ( aOrdering == EDescendingAlphabeticalOrdering )
        {
        type  = CAknSingleStyleTreeOrdering::EDescending;
        }

    CAknSingleStyleTreeOrdering* ordering = 
        CAknSingleStyleTreeOrdering::NewL( type );
    Tree().SetOrdering( ordering, aDrawNow );
    }


// ---------------------------------------------------------------------------
// Sets the given text for specified tree item.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknSingleStyleTreeList::SetTextL( TAknTreeItemID aItem,
    const TDesC& aText, TBool aDrawNow )
    {
    CAknTreeItem* item = Tree().Item( aItem );
    if ( item->Type() == AknTreeList::KSingleStyleTreeLeaf )
        {
        static_cast<CAknSingleStyleTreeLeaf*>( item )->SetTextL( aText,
            aDrawNow );
        }
    else if ( item->Type() == AknTreeList::KSingleStyleTreeNode )
        {
        static_cast<CAknSingleStyleTreeNode*>( item )->SetTextL( aText,
            aDrawNow );
        }
    else
        {
        Panic( EAknHListPanicInvalidItemType );
        }
    }


// ---------------------------------------------------------------------------
// Return text for the specified tree item.
// ---------------------------------------------------------------------------
//
EXPORT_C const TDesC& CAknSingleStyleTreeList::Text( TAknTreeItemID aItem ) const
    {
    CAknTreeItem* item = Tree().Item( aItem );
    if ( item->Type() == AknTreeList::KSingleStyleTreeLeaf )
        {
        __ASSERT_DEBUG( item->IsLeaf(), User::Invariant() );
        return static_cast<CAknSingleStyleTreeLeaf*>( item )->Text();
        }
    else if ( item->Type() == AknTreeList::KSingleStyleTreeNode )
        {
        __ASSERT_DEBUG( item->IsNode(), User::Invariant() );
        return static_cast<CAknSingleStyleTreeNode*>( item )->Text();
        }
    else
        {
        return KNullDesC;
        }
    }


// ---------------------------------------------------------------------------
// Set icon for specified item.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknSingleStyleTreeList::SetIcon( const TAknTreeItemID aItem,
    const TIconType aType, const TInt aIconId, const TBool aDrawNow )
    {
    CAknTreeItem* item = Tree().Item( aItem );
    if ( item->Type() == AknTreeList::KSingleStyleTreeLeaf )
        {
        CAknSingleStyleTreeLeaf::TIconType type;
        switch ( aType )
            {
            case ELeaf:
                type = CAknSingleStyleTreeLeaf::EIcon;
                break;

            case EHighlightedLeaf:
                type = CAknSingleStyleTreeLeaf::EHighlightedIcon;
                break;

            case EOptionalIcon1:
                type = CAknSingleStyleTreeLeaf::EOptIcon1;
                break;

            case EHighlightedOptionalIcon1:
                type = CAknSingleStyleTreeLeaf::EHighlightedOptIcon1;
                break;

            case EOptionalIcon2:
                type = CAknSingleStyleTreeLeaf::EOptIcon2;
                break;

            case EHighlightedOptionalIcon2:
                type = CAknSingleStyleTreeLeaf::EHighlightedOptIcon2;
                break;

            default:
                // Invalid icon type for tree leaf.
                Panic( EAknHListPanicInvalidItemType );
                return;
            }
        static_cast<CAknSingleStyleTreeLeaf*>( item )->SetIcon( type,
            aIconId, aDrawNow );
        }

    else if ( item->Type() == AknTreeList::KSingleStyleTreeNode )
        {
        __ASSERT_DEBUG( item->IsNode(), User::Invariant() );
        CAknSingleStyleTreeNode::TIconType type;
        switch ( aType )
            {
            case EExpandedNode:
                type = CAknSingleStyleTreeNode::EExpandedIcon;
                break;

            case EHighlightedExpandedNode:
                type = CAknSingleStyleTreeNode::EHighlightedExpandedIcon;
                break;

            case ECollapsedNode:
                type = CAknSingleStyleTreeNode::ECollapsedIcon;
                break;

            case EHighlightedCollapsedNode:
                type = CAknSingleStyleTreeNode::EHighlightedCollapsedIcon;
                break;

            case EOptionalIcon1:
                type = CAknSingleStyleTreeNode::EOptIcon1;
                break;

             case EHighlightedOptionalIcon1:
                type = CAknSingleStyleTreeNode::EHighlightedOptIcon1;
                break;

            case EOptionalIcon2:
                type = CAknSingleStyleTreeNode::EOptIcon2;
                break;

            case EHighlightedOptionalIcon2:
                type = CAknSingleStyleTreeNode::EHighlightedOptIcon2;
                break;

           default:
                // Invalid icon type for tree node.
                Panic( EAknHListPanicInvalidItemType );
                return;
            }
        static_cast<CAknSingleStyleTreeNode*>( item )->SetIcon( type,
            aIconId, aDrawNow );
        }

    else
        {
        // Invalid item type.
        Panic( EAknHListPanicInvalidItemType );
        }
    }


// ---------------------------------------------------------------------------
// Returns the icon ID set for the specified tree item.
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CAknSingleStyleTreeList::Icon( TAknTreeItemID aItem,
    TIconType aType ) const
    {
    CAknTreeItem* item = Tree().Item( aItem );
    if ( item->Type() == AknTreeList::KSingleStyleTreeLeaf )
        {
        CAknSingleStyleTreeLeaf::TIconType type;
        switch ( aType )
            {
            case ELeaf:
                type = CAknSingleStyleTreeLeaf::EIcon;
                break;

            case EHighlightedLeaf:
                type = CAknSingleStyleTreeLeaf::EHighlightedIcon;
                break;

            case EOptionalIcon1:
                type = CAknSingleStyleTreeLeaf::EOptIcon1;
                break;

            case EHighlightedOptionalIcon1:
                type = CAknSingleStyleTreeLeaf::EHighlightedOptIcon1;
                break;

            case EOptionalIcon2:
                type = CAknSingleStyleTreeLeaf::EOptIcon2;
                break;

            case EHighlightedOptionalIcon2:
                type = CAknSingleStyleTreeLeaf::EHighlightedOptIcon2;
                break;

            default:
                // Invalid icon type for tree leaf.
                return KErrNotFound;
            }
        return static_cast<CAknSingleStyleTreeLeaf*>( item )->Icon( type );
        }

    else if ( item->Type() == AknTreeList::KSingleStyleTreeNode )
        {
        __ASSERT_DEBUG( item->IsNode(), User::Invariant() );
        CAknSingleStyleTreeNode::TIconType type;
        switch ( aType )
            {
            case EExpandedNode:
                type = CAknSingleStyleTreeNode::EExpandedIcon;
                break;

            case EHighlightedExpandedNode:
                type = CAknSingleStyleTreeNode::EHighlightedExpandedIcon;
                break;

            case ECollapsedNode:
                type = CAknSingleStyleTreeNode::ECollapsedIcon;
                break;

            case EHighlightedCollapsedNode:
                type = CAknSingleStyleTreeNode::EHighlightedCollapsedIcon;
                break;

            case EOptionalIcon1:
                type = CAknSingleStyleTreeNode::EOptIcon1;
                break;

             case EHighlightedOptionalIcon1:
                type = CAknSingleStyleTreeNode::EHighlightedOptIcon1;
                break;

            case EOptionalIcon2:
                type = CAknSingleStyleTreeNode::EOptIcon2;
                break;

            case EHighlightedOptionalIcon2:
                type = CAknSingleStyleTreeNode::EHighlightedOptIcon2;
                break;

           default:
                // Invalid icon type for tree node.
                return KErrNotFound;
            }
        return static_cast<CAknSingleStyleTreeNode*>( item )->Icon( type );
        }

    else
        {
        return KErrNotFound;
        }
    }


// ---------------------------------------------------------------------------
// From class CAknTreeList.
// Sets flags for the list.
// ---------------------------------------------------------------------------
//
void CAknSingleStyleTreeList::SetFlags( TUint32 aFlags )
    {
    aFlags &= ~KRestrictedListFlags;
    CAknTreeList::SetFlags( aFlags );
    }


// ---------------------------------------------------------------------------
// Default C++ constructor.
// ---------------------------------------------------------------------------
//
CAknSingleStyleTreeList::CAknSingleStyleTreeList()
    {
    }


// ---------------------------------------------------------------------------
// Second phase constructor.
// ---------------------------------------------------------------------------
//
void CAknSingleStyleTreeList::ConstructL()
    {
    BaseConstructL();
    }


// ---------------------------------------------------------------------------
// Second phase constructor.
// ---------------------------------------------------------------------------
//
void CAknSingleStyleTreeList::ConstructL( const CCoeControl& aContainer )
    {
    BaseConstructL( aContainer );
    }

