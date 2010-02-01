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
* Description:  Implementation for the TAknTreeIterator class.
*
*/


#include "akntreeiterator.h"
#include "akntreenode.h"

/** Flag indicating that the next item is stored in the iterator. */ 
const TUint KNextItemCached = 0x8000;

/** Flag indicating that the previous item is stored in the iterator. */
const TUint KPreviousItemCached = 0x4000;

/** Bitmask specifying which flags can be given as parameters. */
const TUint KAllowedParameters = KAknSkipCollapsedNodeContents;


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Copy constructor.
// ---------------------------------------------------------------------------
//
TAknTreeIterator::TAknTreeIterator( const TAknTreeIterator& aIterator )
    : iCurrent( aIterator.iCurrent ),
      iRoot( aIterator.iRoot ),
      iNext( aIterator.iNext ),
      iPrevious( aIterator.iPrevious ),
      iFlags( aIterator.iFlags )
    {
    }


TBool TAknTreeIterator::HasNext() const
    {
    return FindNext() ? ETrue : EFalse;
    }


CAknTreeItem* TAknTreeIterator::Next()
    {
    CAknTreeItem* next = FindNext();
    
    iPrevious = iCurrent;
    iCurrent = next;
    iFlags = ( iFlags & KAllowedParameters ) | KPreviousItemCached;

    return next;  
    }


TBool TAknTreeIterator::HasPrevious() const
    {
    return FindPrevious() ? ETrue : EFalse;
    }


CAknTreeItem* TAknTreeIterator::Previous()
    {
    CAknTreeItem* previous = FindPrevious();

    iNext = iCurrent;
    iCurrent = previous;
    iFlags = ( iFlags & KAllowedParameters ) | KNextItemCached;

    return previous;
    }


CAknTreeItem* TAknTreeIterator::First() const
    {
    CAknTreeItem* first = NULL;
    if ( iRoot && iRoot->ChildCount() )
        {
        first = iRoot->Child( 0 );
        }
    return first;
    }


CAknTreeItem* TAknTreeIterator::Last() const
    {
    CAknTreeItem* last = NULL;
    if ( iRoot && iRoot->ChildCount() )
        {
        CAknTreeItem* child = iRoot->Child( iRoot->ChildCount() - 1 );
        while ( child->IsNode() && child->Node()->ChildCount() &&
                ( !( iFlags & KAknSkipCollapsedNodeContents ) || 
                  child->Node()->IsExpanded() ) )
            {
            child = child->Node()->Child( child->Node()->ChildCount() - 1 );
            }
        last = child;
        }
    return last;
    }


// ---------------------------------------------------------------------------
// Changes the item iterator is currently pointing at.
// Note: This method does not check that the item is in the iterated subtree!
// ---------------------------------------------------------------------------
//
void TAknTreeIterator::SetCurrent( CAknTreeItem* aCurrent )
    {
    iCurrent = aCurrent;
    // The cached next and previous items are no longer valid.
    iFlags = iFlags & KAllowedParameters;
    }


TAknTreeIterator::TAknTreeIterator( CAknTreeNode* aRoot, TUint aFlags )
    : iCurrent( aRoot ),
      iRoot( aRoot ),
      iNext( NULL ),
      iPrevious( NULL ),
      iFlags( ( aFlags & KAllowedParameters ) | KPreviousItemCached )
    {
    }


// ---------------------------------------------------------------------------
// TAknTreeIterator::FindNext()
// Non-recursive algorithm for searching the next item from the tree.
// The returned value is NULL, if the next item is not found.
// ---------------------------------------------------------------------------
//
CAknTreeItem* TAknTreeIterator::FindNext() const
    {
    CAknTreeItem* next = NULL;
    if ( iFlags & KNextItemCached )
        {
        next = iNext;
        }
    else
        {
        CAknTreeNode* node = iCurrent ? iCurrent->Node() : NULL;
        if ( node && node->ChildCount() && 
            ( node->IsExpanded() || !( iFlags & KAknSkipCollapsedNodeContents ) ) )
            {
            next = node->Child( 0 );
            }
        else
            {
            CAknTreeItem* item = iCurrent;
            TBool found = EFalse;
            while ( item && item != iRoot && !found )
                {
                CAknTreeNode* parent = item->Parent();
                if ( parent )
                    {
                    TInt index = parent->Index( item );
                    if ( index >= 0 && index < parent->ChildCount() - 1 )
                        {
                        next = parent->Child( index + 1 );
                        found = ETrue;
                        }
                    }
                
                item = parent;
                }
            }
        iNext = next;
        iFlags |= KNextItemCached;
        }
    return next;
    }


// ---------------------------------------------------------------------------
// TAknTreeIterator::FindPrevious()
// Non-recursive algorithm for searching the previous item for the tree.
// The returned value is NULL, if the previous item is not found.
// ---------------------------------------------------------------------------
//
CAknTreeItem* TAknTreeIterator::FindPrevious() const
    {
    CAknTreeItem* previous = NULL;
    if ( iFlags & KPreviousItemCached )
        {
        previous = iPrevious;
        }
    else if ( iCurrent )
        {
        CAknTreeItem* item = iCurrent;
        CAknTreeNode* parent = item->Parent();
        if ( parent )
            {
            TInt index = parent->Index( item );
            if ( index > 0 )
                {
                CAknTreeItem* tmp = parent->Child( index - 1 );
                while ( tmp->Node() && tmp->Node()->ChildCount() &&
                        ( tmp->Node()->IsExpanded() ||
                          !( iFlags & KAknSkipCollapsedNodeContents ) ) )
                    {
                    tmp = tmp->Node()->Child( tmp->Node()->ChildCount() - 1 );
                    }
                previous = tmp;
                }
            else
                {
                if ( parent != iRoot )
                    {
                    previous = parent;
                    }
                }
            }
        iPrevious = previous;
        iFlags |= KPreviousItemCached;
        }
    return previous;
    }
