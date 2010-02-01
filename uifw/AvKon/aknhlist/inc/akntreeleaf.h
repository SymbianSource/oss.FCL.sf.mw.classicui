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
* Description:  Abstract base class for all tree leaves.
*
*/


#ifndef C_AKNTREELEAF_H
#define C_AKNTREELEAF_H


#include "akntreeitem.h"


/**
 *  Abstract base class for all tree leaves.
 *
 *  The items in tree structure are divided into leaves and nodes. The
 *  division does not represent the dynamic states of the tree items; leaves
 *  are tree items that cannot have any children, while nodes can, but do not
 *  necessarily have any.
 *
 *  @lib aknhlist.lib
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( CAknTreeLeaf ) : public CAknTreeItem
    {

public:

    /** Tree leaf flags. These flags can be set to the leaf at the time of
        its construction or with @c SetFlags() method. The first 16 bits
        are used by used by this class, and the other 16 bits can be used
        by derived classes. 
        */
    enum TAknTreeLeafFlags
        {
        /** Leaf is marked. */
        EMarked          = 0x0001,
        /** Leaf is persistent. */
        EPersistent      = 0x0002,
        /** Marking change for the leaf is disabled. */
        EMarkingDisabled = 0x0004        
        };

    /**
     * Destructor.
     */
    virtual ~CAknTreeLeaf();

// from base class CAknTreeItem

    /**
     * From CAknTreeItem.
     * Leaf.
     *
     * @return Pointer to leaf object.
     */
    CAknTreeLeaf* Leaf();

    /**
     * From CAknTreeItem.
     * Leaf.
     *
     * @return Pointer to leaf object.
     */
    const CAknTreeLeaf* Leaf() const;

    /**
     * From CAknTreeItem.
     * Checks whether the leaf is marked.
     *
     * @return @c ETrue, if the leaf is marked.
     */
    TBool IsMarked() const;

    /**
     * From CAknTreeItem.
     * Sets the leaf is marked or unmarked.
     *
     * @param aMarked @c ETrue to set item marked, @c EFalse to unmarked.
     */
    void SetMarked( TBool aMarked );

    /**
     * From CAknTreeItem.
     * Checks whether leaf is markable.
     *
     * @return @c ETrue if marking is enabled, otherwise @c EFalse.
     */
    TBool IsMarkable() const;

    /**
     * From CAknTreeItem.
     * Enabled or disables the marking changes for the leaf. By default,
     * each leaf is set markable.
     * 
     * @param aMarkable @c ETrue to enable marking, @c EFalse to disable it.
     */
    void SetMarkable( TBool aMarkable );

    /**
     * From CAknTreeItem.
     * Checks whether the leaf is set persistent.
     *
     * @return @c ETrue, if the leaf is persistent.
     */
    TBool IsPersistent() const;

    /**
     * From CAknTreeItem.
     * Sets whether the leaf is persistent.
     *
     * @param aPersistent @c ETrue to set item persistent, @c EFalse to set
     *      item non-persistent.
     */
    void SetPersistent( TBool aPersistent );

    /**
     * From CAkntreeItem.
     * Checks whether the item has any persistent descendants. 
     *
     * @return @c EFalse is always returned for a leaf object.
     */
    TBool HasPersistentDescendants() const;

    /**
     * From CAknTreeItem.
     * Checks whether the item can be removed from the tree when its parent
     * node is being collapsed.
     *
     * Leaves that have been set marked or persistent cannot be removed from
     * the tree automatically on collapse events.
     *
     * @return @c ETrue, if the leaf can be removed from the tree.
     */
    TBool IsRemovableFromCollapsedNode() const;

protected:

    /**
     * Default C++ constructor.
     */
    CAknTreeLeaf();

    /**
     * C++ constructor.
     *
     * @param aFlags Flags for the tree leaf. The possible flags are defined
     *      in @c TAknTreeLeafFlags enumeration.
     */
    CAknTreeLeaf( TUint32 aFlags );

    /**
     * Returns the flags set for the leaf.
     *
     * @return Flags.
     */
    TUint32 Flags() const;

    /**
     * Sets flags for the leaf.
     *
     * @param aFlags Flags for the leaf. First 16 flags are reserved for use
     *      of @c CAknTreeLeaf class, but the other 16 flags can be used by
     *      derived classes.
     */
    void SetFlags( TUint32 aFlags );

private: // data

    /**
     * Flags for a leaf.
     */
    TUint32 iFlags;

    };


#endif // C_AKNTREELEAF_H
