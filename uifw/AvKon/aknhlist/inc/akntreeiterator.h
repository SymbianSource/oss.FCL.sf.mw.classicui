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
* Description:  Iterator class for traversing the tree structure.
*
*/


#ifndef T_AKNTREEITERATOR_H
#define T_AKNTREEITERATOR_H


#include <e32def.h>

class CAknTreeItem;
class CAknTreeNode;

/**  Flag indicating that the content of collapsed nodes is not to be
     included in the iteration sequence. */
const TUint KAknSkipCollapsedNodeContents = 0x01;


/**
 *  Iterator class for traversing a tree structure.
 *
 *  The @c CAknTree class is responsible for constructing the iterators for
 *  tree instances. The @c CAknTree::Iterator() method can be used in
 *  retrieving an iterator for the expanded tree structure, or 
 *  @c CAknTree::Iterator( CAknTreeNode*, TUint ) method can be used in
 *  retrieving iterator with specified properties for some specified node.
 *
 *  Each iterator instance stores the root node which is being iterated,
 *  item denoting the current position in the iteration sequence, and flags
 *  affecting the iteration.
 *
 *  @lib aknhlist.lib
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( TAknTreeIterator )
    {

    friend class CAknTree;

public:

    /**
     * Copy constructor.
     *
     * @param aIterator Copied iterator.
     */
    TAknTreeIterator( const TAknTreeIterator& aIterator );

    /**
     * Returns whether the iterator has next tree item.
     *
     * @return @c ETrue, if there is a next item.
     */
    TBool HasNext() const;

    /**
     * Returns a pointer to the next tree item. The returned value is @c NULL,
     * when there is no more items. This changes also the iterator to point
     * to the returned item.
     *
     * @return Pointer to the next tree item.
     */
    CAknTreeItem* Next();

    /**
     * Returns whether the iterator has previous tree item.
     *
     * @return @c ETrue, if there is a previous item.
     */
    TBool HasPrevious() const;

    /**
     * Returns a pointer to the previous tree item. The returned value is
     * @c NULL, if there is no previous tree item. This changes also the
     * iterator to point to the returned item. 
     *
     * @return Pointer to the previous tree item.
     */
    CAknTreeItem* Previous();

    /**
     * Return pointer to the first item in the sequence.
     *
     * @return First item.
     */
    CAknTreeItem* First() const;
    
    /**
     * Returns pointer to the las item in the sequence.
     *
     * @return Last item.
     */ 
    CAknTreeItem* Last() const;

    /**
     * Changes the position of the iterator.
     *
     * Note: This method does not check that the specified position is
     * included in the iterated subtree.
     *
     * @param aCurrent Pointer to the new position of the iterator.
     */
    void SetCurrent( CAknTreeItem* aCurrent );

private:

    /**
     * Default C++ constructor.
     *
     * @param aRoot Root node for the iterated tree (or subtree).
     */
    TAknTreeIterator( CAknTreeNode* aRoot, TUint aFlags );

    /**
     * Assignment operator.
     *
     * @param aIterator Iterator.
     */
    TAknTreeIterator& operator=( const TAknTreeIterator& aIterator );

    /**
     * Returns pointer to the next tree item.
     *
     * @return Pointer to the next tree item. @c NULL, if the next item is not
     *      found.
     */
    CAknTreeItem* FindNext() const;
    
    /**
     * Returns pointer ot the previous tree item.
     *
     * @return Pointer to the previous tree item. @c NULL, if previous item is
     *      not found.
     */
    CAknTreeItem* FindPrevious() const;

private: // data

    /**
     * Current item.
     */
    CAknTreeItem* iCurrent;

    /**
     * Root of the tree (or subtree).
     */
    CAknTreeNode* iRoot;

    /**
     * Next item. Contains a pointer to the cached next item.
     */
    mutable CAknTreeItem* iNext;

    /**
     * Previous item. Contains a pointer to the cached previous item.
     */
    mutable CAknTreeItem* iPrevious;

    /**
     * Flags for the iterator.
     */
    mutable TUint iFlags;

    };


#endif // T_AKNTREEITERATOR_H
