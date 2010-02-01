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
* Description:  Abstract base class for all tree items.
*
*/


#ifndef C_AKNTREEITEM_H
#define C_AKNTREEITEM_H


#include <e32base.h>
#include <akntreelistconstants.h>

class CAknTreeNode;
class CAknTreeLeaf;
class CAknTree;
class CWindowGc;
class TAknWindowComponentLayout;
struct TPointerEvent; // w32std.h


/**
 *  Abstract base class for all tree items.
 *
 *  @lib aknhlist.lib
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( CAknTreeItem ) : public CBase
    {

public:

    /**
     * Destructor.
     */
    virtual ~CAknTreeItem();

    /**
     * Returns the type of the item. Each concrete class derived from this
     * class must provide implementation for this method that returns the
     * constant defining the type of the concrete item class.
     * 
     * @return Item type.
     */
    virtual TInt Type() const = 0;

    /**
     * Returns a pointer to the item's parent node.
     *
     * @return Parent node. @c NULL, if the parent node has not been set.
     */
    CAknTreeNode* Parent();

    /**
     * Returns a pointer to the items parent node.
     *
     * @return Parent node. @c NULL, if the parent node has not been set.
     */
    const CAknTreeNode* Parent() const;

    /**
     * Sets the items parent node.
     *
     * @param aParent Parent node.
     */
    void SetParent( CAknTreeNode* aParent );

    /**
     * Returns a pointer to the root of the tree.
     *
     * @return Pointer to the root of the tree. @c NULL, if the the parent
     *      chain to root node is broken.
     */
    virtual CAknTree* Root() const;

    /**
     * Returns the level of the item in the tree. The returned value matches the
     * number of parents in the items parent chain.
     *
     * @return The level of the item in the tree.
     */
    TInt Level() const;

    /**
     * Return pointer to leaf object. Returned value is @c NULL, if the item
     * is not derived from @c CAknTreeLeaf.
     *
     * @return @c CAknTreeLeaf pointer, if the item is a leaf.
     */
    virtual CAknTreeLeaf* Leaf();

    /**
     * Return pointer to leaf object. Returned value is @c NULL, if the item
     * is not derived from @c CAknTreeLeaf.
     *
     * @return @c CAknTreeLeaf pointer, if the item is a leaf.
     */
    virtual const CAknTreeLeaf* Leaf() const;

    /**
     * Return pointer to node object. Returned value is @c NULL, if the item
     * is not derived from @c CAknTreeNode.
     *
     * @return @c CAknTreeNode pointer, if the item is a node.
     */
    virtual CAknTreeNode* Node();

    /**
     * Return pointer to node object. Returned value is @c NULL, if the item
     * is not derived from @c CAknTreeNode.
     *
     * @return @c CAknTreeNode pointer, if the item is a node.
     */
    virtual const CAknTreeNode* Node() const;

    /**
     * Checks whether the item is a leaf.
     *
     * @return @c ETrue, if the item is a leaf.
     */
    TBool IsLeaf() const;

    /**
     * Checks whether the item is a node.
     *
     * @return @c ETrue, if the item is a node.
     */
    TBool IsNode() const;

    /**
     * Checks whether the item is marked.
     *
     * Proper implementations for this pure virtual function are provided by
     * @c CAknTreeLeaf and @c CAknTreeNode classes.
     *
     * @return @c ETrue, if the item is marked.
     */
    virtual TBool IsMarked() const = 0;

    /**
     * Sets the item marked or unmarked.
     *
     * Proper implementations for this pure virtual function are provided by
     * @c CAknTreeLeaf and @c CAknTreeNode classes.
     *
     * @param aMarked @c ETrue to set item marked, @c EFalse to unmarked.
     */
    virtual void SetMarked( TBool aMarked ) = 0;

    /**
     * Checks whether item is markable.
     *
     * Proper implementations for this pure virtual function are provided by
     * @c CAknTreeLeaf and @c CAknTreeNode classes.
     *
     * @return @c ETrue if marking is enabled, otherwise @c EFalse.
     */
    virtual TBool IsMarkable() const = 0;

    /**
     * Enables or disables marking changes for the item.
     *
     * Proper implementations for this pure virtual function are provided by
     * @c CAknTreeLeaf and @c CAknTreeNode classes.
     *
     * @param aMarkable @c ETrue to enable marking, @c EFalse to disable it.
     */
    virtual void SetMarkable( TBool aMarkable ) = 0;

    /**
     * Checks whether the item is persistent.
     *
     * Proper implementations for this pure virtual function are provided by
     * @c CAknTreeLeaf and @c CAknTreeNode classes.
     *
     * @return @c ETrue, if the item is persistent.
     */
    virtual TBool IsPersistent() const = 0;

    /**
     * Sets whether the item is persistent.
     *
     * Proper implementations for this pure virtual function are provided by
     * @c CAknTreeLeaf and @c CAknTreeNode classes.
     *
     * @param aPersistent @c ETrue to set item persistent, @c EFalse to set
     *      it non-persistent.
     */
    virtual void SetPersistent( TBool aPersistent ) = 0;

    /**
     * Checks whether the item has any persistent descendants. Implementations
     * for this method are provided by @c CAknTreeLeaf and @c CAknTreeNode
     * classes.
     *
     * @return @c ETrue, if the item has persistent descendants.
     */
    virtual TBool HasPersistentDescendants() const = 0;

    /**
     * Checks whether the item can be removed from the tree when its parent
     * node is being collapsed. Items that have been set marked or persistent,
     * or contain marked or persistent descendants cannot be removed from the
     * tree automatically on collapse events. Implementations for this method
     * are provided by @c CAknTreeLeaf and @c CAknTreeNode classes.
     * 
     * @return @c ETrue, if the item can be removed from the tree.
     */
    virtual TBool IsRemovableFromCollapsedNode() const = 0;

    /**
     * Returns the minimum size required to display the item completely in the
     * view with the current layout.
     *
     * @return Minimum size.
     */
    virtual TSize MinimumSize() const;

    /**
     * Draws the item. This is a pure virtual function that should be
     * implemented by each item specialisation.
     *
     * This method is called by hierarchical list framework to draw the item
     * to specified graphics context, whenever the changes in hierarchical
     * list's view require it. In addition to the graphic context, the item
     * receives a rectangle aItemRect that specifes the size and position of
     * the item, a rectangle aRect that specifies the graphics context area
     * that needs to be redraw. The co-ordinates of the rect should be used
     * when drawing the required part of the item.
     *
     * When this method is called for the item, the framework has already drawn
     * the background and possible highlight for the item, so it not necessary,
     * and not even recommended, to draw every pixel in the specifed rect.
     *
     * Notes:
     *
     * Due to the nature of hierarchical list, the size and position of the
     * item are most likely different each time the item is drawn, so in order
     * to avoid unnecessary memory consumption, they should not be stored in
     * the items.
     *
     * @param aGc The graphic context in which the item should draw itself.
     *
     * @param aItemRect A rectangle defining the size and position of the item.
     *
     * @param aRect A rectangle specifying the part of the item's rectangle
     *      that needs to be redrawn.
     *
     * @param aFocused @c ETrue, if the item is currently focused, that is, it
     *      has highlight in the list view and should be drawn accordingly.
     */
    virtual void Draw( CWindowGc& aGc, const TRect& aItemRect,
        const TRect& aRect, TBool aFocused ) const = 0;

    /**
     * Handles pointer events. Default implementation does nothing.
     *
     * @param aPointerEvent Pointer event.
     *
     * @param aItemRect A rectangle defining the size and position of the item.
     */
    virtual void HandlePointerEventL( const TPointerEvent& aPointerEvent,
        const TRect& aItemRect );

    /**
     * Static function for comparing two tree items.
     *
     * Note: Either one of the items must already be inserted to the tree for
     * the comparison function to work properly.
     *
     * @param aFirst First item.
     *
     * @param aSecond Second item.
     *
     * @return Positive, if the first item is greater than the second item;
     *      negative, if the first item is less than the second item;
     *      and zero, if the items are equal.
     */
    static TInt Compare( const CAknTreeItem& aFirst,
        const CAknTreeItem& aSecond );

protected:

    /**
     * Default C++ constructor.
     */
    CAknTreeItem();

    /**
     * Utility function for acquiring a rectangle for layout component based
     * on the component's parent rectangle and layout data.
     *
     * @param aParent Rectangle of parent layout component.
     *
     * @param aComponentLayout Layout for required component.
     *
     * @return Rectangle for required component.
     */
    TRect RectFromLayout( const TRect& aParent,
        const TAknWindowComponentLayout& aComponentLayout ) const;

private: // data

    /**
     * Pointer to parent node.
     * Not own.
     */
    CAknTreeNode* iParent;

    };


#endif // C_AKNTREEITEM_H
