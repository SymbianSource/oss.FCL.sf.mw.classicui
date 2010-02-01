/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Abstract base class for hierarchical list nodes.
*
*/


#ifndef C_AKNTREENODE_H
#define C_AKNTREENODE_H


#include "akntreeitem.h"


/**
 *  Abstract base class for hierarchical list nodes.
 *
 *  The items in tree structure are divided into leaves and nodes. The
 *  division does not represent the dynamic states of the tree items;
 *  nodes are tree items that can have children, while leaves cannot.
 *
 *  @lib aknhlist.lib
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( CAknTreeNode ) : public CAknTreeItem
    {

public:

    /** Tree node flags. */
    enum TAknTreeNodeFlags
        {
        /** Node is marked. */
        EMarked                     = 0x01,
        /** Node has marked descendants. */
        EHasMarkedDescendants       = 0x02,
        /** Node is persistent. */
        EPersistent                 = 0x04,
        /** Node has persistent descendants. */
        EHasPersistenDescendants    = 0x08,
        /** Node is expanded. */
        EExpanded                   = 0x10,
        /** Node appears non-empty, even if it is empty. */
        ENonEmpty                   = 0x20,
        /** Marking change for the node is disabled. */
        EMarkingDisabled            = 0x40
        };

    /**
     * Destructor.
     */
    virtual ~CAknTreeNode();

    /**
     * Returns the number of children the node has.
     *
     * @return Number of children.
     */
    TInt ChildCount() const;

    /**
     * Returs the number of descendants the node has.
     *
     * @return Number of descendants.
     */
    TInt DescendantCount() const;

    /**
     * Returns the number of visible descendants the node has.
     *
     * @return Number of visible descendants.
     */
    TInt VisibleDescendantCount() const;

    /**
     * Returns the child item specified with the index.
     *
     * @param aIndex The index of the child.
     *
     * @return A child.
     */
    CAknTreeItem* Child( TInt aIndex ) const;

    /**
     * Return the index of the specified child. Negative if not found.
     *
     * @return The index of the specified child.
     */
    TInt Index( const CAknTreeItem* aItem ) const;

    /**
     * Adds the child to the node. This does not change the parent of the
     * added child, thus it has to be done separately with the
     * @c CAknTreeItem::SetParent() method. The child are compared
     * to determine the correct position of the item within the array.
     *
     * @param aItem The child item to be added to the node.
     *
     * @leave KErrNoMemory Not enough memory to add the child to the node.
     *
     * @post The ownership of the item is transferred to the parent node.
     */
    void AddChildL( CAknTreeItem* aItem );

    /**
     * Adds the child to the node at a specified position. This does not
     * change the parent of the added child, thus it has to be done
     * separately with the @c CAknTreeItem::SetParent() method.
     *
     * @param aItem The child item to be added to the node.
     *
     * @param aPosition The position of the child within the array. Z
     *
     * @leave KErrNoMemory Not enough memory to add the child to the node.
     *
     * @post The ownership of the item is transferred to the parent node.
     */
    void AddChildL( CAknTreeItem* aItem, TInt aPosition );

    /**
     * Removes the child from the node.
     *
     * @param aItem The child item to be removed from the node.
     *
     * @return @c KErrNotFound, if the specified child is not found, 
     *      otherwise @c KErrNone.
     */
    TInt RemoveChild( CAknTreeItem* aItem );

    /**
     * Checks whether the node is expanded.
     *
     * @return @c ETrue, if the node is expanded.
     */
    TBool IsExpanded() const;

    /**
     * Changes the state of the node to expanded.
     */
    virtual void Expand();

    /**
     * Changes the state of the node to collapsed.
     */
    virtual void Collapse();

    /**
     * Checks whether node is empty. The node is not empty, when it contains
     * children, or is explicitly set non-empty with @c SetNonEmpty method.
     *
     * @return @c ETrue, if the node is empty.
     */
    TBool IsEmpty() const;

    /**
     * Sets the node non-empty. When the node is set non-empty, it can have an
     * appearance of an non-empty node, even if it does not actually contain
     * any children.
     *
     * Note: Setting the node empty with this method does not remove the
     * contents of the node, it only removes the non-empty flag from the node.
     *
     * @param aNonEmpty @c ETrue to set node appear non-empty, @c EFalse to
     *      to remove the flag.
     */
    void SetNonEmpty( TBool aNonEmpty );

    /**
     * Sorts the children of this node.
     */
    void Sort();

// from base class CAknTreeItem

    /**
     * From CAknTreeItem.
     * Returns a pointer to this node.
     *
     * @return @c CAknTreeNode pointer to this object.
     */
    CAknTreeNode* Node();

    /**
     * From CAknTreeItem.
     * Returns a pointer this node.
     *
     * @return @c CAknTreeNode pointer to this object. 
     */
    const CAknTreeNode* Node() const;

    /**
     * From CAknTreeItem.
     * Checks whether the node is marked.
     *
     * @return @c ETrue, if the node is marked.
     */
    TBool IsMarked() const;

    /**
     * From CAknTreeItem.
     * Sets the node marked or unmarked.
     *
     * @param aMarked @c ETrue to set node marked, @c EFalse to unmarked.
     */
    void SetMarked( TBool aMarked );

    /**
     * From CAknTreeItem.
     * Checks whether the node is markable.
     *
     * @return @c ETrue if marking is enabled, otherwise @c EFalse.
     */
    TBool IsMarkable() const;

    /**
     * From CAknTreeItem.
     * Enabled or disables the marking changes for the node. By default,
     * each node is set markable.
     *
     * @param aMarkable @c ETrue to enable marking, @c EFalse to disable it.
     */
    void SetMarkable( TBool aMarkable );

    /**
     * From CAknTreeItem.
     * Checks whether the node is persistent.
     *
     * @return @c ETrue, if the node is persistent.
     */
    TBool IsPersistent() const;

    /**
     * From CAknTreeItem.
     * Sets whether the node is persistent.
     *
     * @param aPersistent @c ETrue to set node persistent, @c EFalse to set
     *      node non-persistent.
     */
    void SetPersistent( TBool aPersistent );

    /**
     * From CAknTreeItem.
     * Checks whether the node has any persistent descendants.
     *
     * @return @c ETrue, if node has persistent descendants.
     */
    TBool HasPersistentDescendants() const;

    /**
     * From CAknTreeItem.
     * Checks whether the item can be removed from the tree when its parent
     * node is being collapsed.
     *
     * Nodes that have been set marked or persistent, or contain marked or
     * persistent descendants cannot be removed from the tree automatically
     * on collapse events.
     * 
     * @return @c ETrue, if the node can be removed from the tree.
     */
    TBool IsRemovableFromCollapsedNode() const;

protected:

    /**
     * Default C++ constructor.
     */
    CAknTreeNode();

    /**
     * C++ constructor.
     *
     * @param aFlags Flags for the tree node. The possible flags are defined
     *      in the @c TAknTreeNodeFlags enumeration.
     */
    CAknTreeNode( TUint32 aFlags );

    /**
     * Returns the flags set for the node.
     *
     * @return Flags.
     */
    TUint32 Flags() const;

    /**
     * Sets flags for the node.
     *
     * @param aFlags Flags for the node. First 16 flags are reserved for use
     *      of @c CAknTreeNode class, but the other 16 flags can be used by
     *      derived classes.
     */
    void SetFlags( TUint32 aFlags );

private: // data

    /**
     * Array for children of the node.
     * Own.
     */
    RPointerArray<CAknTreeItem> iChild;

    /**
     * Flags.
     */
    TUint32 iFlags;

    };


#endif // C_AKNTREENODE_H
