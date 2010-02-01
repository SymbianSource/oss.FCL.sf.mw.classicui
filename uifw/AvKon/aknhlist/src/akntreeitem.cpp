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
* Description:  Implementation for the CAknTreeItem class.
*
*/


#include <aknappui.h>
#include <AknUtils.h>
#include <aknlayoutscalable_avkon.cdl.h>

#include "akntreeitem.h"
#include "akntreenode.h"
#include "akntree.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Destructor.
// ---------------------------------------------------------------------------
//
CAknTreeItem::~CAknTreeItem()
    {
    iParent = NULL;
    }


// ---------------------------------------------------------------------------
// Returns pointer to the parent node.
// ---------------------------------------------------------------------------
//
const CAknTreeNode* CAknTreeItem::Parent() const
    {
    return iParent;
    }


CAknTreeNode* CAknTreeItem::Parent()
    {
    return iParent;
    }


// ---------------------------------------------------------------------------
// Sets the parent node.
// ---------------------------------------------------------------------------
//
void CAknTreeItem::SetParent( CAknTreeNode* aParent )
    {
    __ASSERT_DEBUG( aParent != this, User::Invariant() );
    iParent = aParent;
    }


// ---------------------------------------------------------------------------
// Returns pointer to the tree root.
// ---------------------------------------------------------------------------
//
CAknTree* CAknTreeItem::Root() const
    {
    return iParent ? iParent->Root() : NULL;
    }


TInt CAknTreeItem::Level() const
    {
    return iParent ? iParent->Level() + 1 : 0;
    }


// ---------------------------------------------------------------------------
// These virtual functions are intended for compensating the absence of
// dynamic casting. Default implementations return null pointers.
// ---------------------------------------------------------------------------
//
CAknTreeLeaf* CAknTreeItem::Leaf()
    {
    return NULL;
    }


const CAknTreeLeaf* CAknTreeItem::Leaf() const
    {
    return NULL;
    }


CAknTreeNode* CAknTreeItem::Node()
    {
    return NULL;
    }


const CAknTreeNode* CAknTreeItem::Node() const
    {
    return NULL;
    }


// ---------------------------------------------------------------------------
// Determines whether the object is an intance of CAknTreeLeaf with the
// virtual Leaf() method that should be overriden by CAknTreeLeaf class to
// return pointer to the object instead of null pointer.
// ---------------------------------------------------------------------------
//
TBool CAknTreeItem::IsLeaf() const
    {
    return Leaf() != NULL;
    }


// ---------------------------------------------------------------------------
// Determines whether the object is an instance of CAknTreeNode with the
// virtual Node() method, that should be overriden by CAknTreeNode class to
// return pointer to the object instead of null pointer.
// ---------------------------------------------------------------------------
//
TBool CAknTreeItem::IsNode() const
    {
    return Node() != NULL;
    }


// ---------------------------------------------------------------------------
// Gets the minimum size for the hierarchical list item from the layout data.
// ---------------------------------------------------------------------------
//
TSize CAknTreeItem::MinimumSize() const
    {
    TAknWindowLineLayout lineLayout = 
        AknLayoutScalable_Avkon::aid_size_min_hl_cp1().LayoutLine();
    TRect parentRect = iAvkonAppUi->ApplicationRect(); // Not according to LAF!
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect( parentRect, lineLayout );
    TRect minimumSize = layoutRect.Rect();
    return minimumSize.Size();
    }


// ---------------------------------------------------------------------------
// Empty implementation for pointer event handling.
// ---------------------------------------------------------------------------
//
void CAknTreeItem::HandlePointerEventL( const TPointerEvent& /*aPointerEvent*/,
    const TRect& /*aItemRect*/ )
    {
    }


// ---------------------------------------------------------------------------
// Static comparison function.
// ---------------------------------------------------------------------------
//
TInt CAknTreeItem::Compare( const CAknTreeItem& aFirst,
    const CAknTreeItem& aSecond )
    {
    CAknTree* root = aFirst.Root();
    if ( !root )
        {
        root = aSecond.Root();
        }

    if ( root )
        {
        return root->Compare( aFirst, aSecond );
        }
    else
        {
        return NULL;
        }
    }


// ---------------------------------------------------------------------------
// Default C++ constructor.
// ---------------------------------------------------------------------------
//
CAknTreeItem::CAknTreeItem()
    {
    }


// ---------------------------------------------------------------------------
// Gets specified rectangle from the layout data.
// ---------------------------------------------------------------------------
//
TRect CAknTreeItem::RectFromLayout( const TRect& aParent,
    const TAknWindowComponentLayout& aComponentLayout ) const
    {
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect( aParent, aComponentLayout.LayoutLine() );
    return layoutRect.Rect();
    }


