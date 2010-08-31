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
* Description:  An interface to the hierarchical list tree structure.
*
*/


#ifndef C_AKNTREE_H
#define C_AKNTREE_H


#include <AknIconUtils.h> // TScaleMode
#include <babitflags.h>

#include "akntreenode.h"
#include "akntreeobserver.h"

class CAknTreeList;
class CAknTreeListIcon;
class CAknTreeOrdering;
class CAknMarqueeControl;
class CFont;
class MAknCustomTreeOrdering;
class TAknsItemID;
class TAknTreeIterator;
class TAknTextComponentLayout;
class TRgb;


/**
 *  Hierarchical list tree structure.
 *
 *  The tree structure is formed from hierarchical list items. These items
 *  can be either leaves or nodes. The names do not refer to their dynamic
 *  state; a leaf is a tree item that cannot ever have children in the tree
 *  structure while node can. @c CAknTree is derived from @c CAknTreeNode
 *  class, which is an abstract base class for all tree nodes. An instance of
 *  @c CAknTree is always set as a root of the tree structure, so that it can
 *  be always reached from all the tree items through parent pointers, or
 *  simply by calling the @c CAknTreeItem::Root() method.
 *
 *  @c CAknTree class provides fast access to all the tree items it contains.
 *  The tree structure should always be modified through this class and not
 *  by directly modifying the related tree items, as this class is responsible
 *  for notifying the tree list view of the occurring tree events.
 *
 *  Furthermore, this class can create an iterator (an instance of
 *  @c CAknTreeIterator) for traversing the tree structure, it stores the
 *  ordering of the tree items, and it can also store the icons shared by
 *  several tree items.
 *
 *  @lib aknhlist.lib
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( CAknTree ) : public CAknTreeNode
    {

public:

    /** Pre-defined IDs for the icons constructed by the tree. */
    enum TTreeListIcon
        {
        ENone                           = AknTreeListIconID::KNone,
        /** Tree structure line with branch. */
        ELineBranchIndication           = AknTreeListIconID::KLineBranchIndication,
        /** Tree structure end line. */
        ELineEndIndication              = AknTreeListIconID::KLineEndIndication,
        /** Tree structure straight line indication. */
        ELineStraightIndication         = AknTreeListIconID::KLineStraightIndication,
        /** Default file indication. */
        EDefaultFileIndication          = AknTreeListIconID::KDefaultFileIndication,
        /** Closed folder indication. */
        EClosedFolderIndication         = AknTreeListIconID::KClosedFolderIndication,
        /** Open folder indication. */
        EOpenFolderIndication           = AknTreeListIconID::KOpenFolderIndication,
        /** Collapse function indication, superimposed. */
        ECollapseFunctionIndication     = AknTreeListIconID::KCollapseFunctionIndication,
        /** Expand function indication, superimposed. */
        EExpandFunctionIndication       = AknTreeListIconID::KExpandFunctionIndication,
        /** Item marked indication. */
        EMarkedIndication               = AknTreeListIconID::KMarkedIndication,
        /** Highlighted item marked indication. */
        EHighlightedMarkedIndication    = AknTreeListIconID::KHighlightedMarkedIndication,
        /** Denotes the range for pre-defined IDs. */
        EPreDefinedIconIdRange
        };

    /**
     * Two-phased constructor.
     *
     * @param aList Reference to the tree list object which owns the created
     *      tree structure.
     *
     * @param aOrdering Ordering for the tree list items. The ownership of
     *      of the ordering is transferred to the tree.
     *
     * @return Newly created tree instance.
     */
    static CAknTree* NewL( CAknTreeList& aList, CAknTreeOrdering* aOrdering );

    /**
     * Destructor.
     */
    virtual ~CAknTree();

    /**
     * Returns the ID assigned for the specified tree item. The constant
     * @c KAknTreeIIDRoot is returned for the tree root, and constant @c
     * KAknTreeIIDNone for null pointer.
     *
     * @param aItem Pointer to a tree item.
     *
     * @return ID of the given tree item.
     */
    TAknTreeItemID Id( const CAknTreeItem* aItem ) const;

    /**
     * Sets the ordering of the tree list.
     * The ordering defines the order of hierarchical list items. The list
     * items are always kept sorted according the set ordering object, and
     * whenever the ordering object is changed, the tree is sorted according
     * the newly set ordering.
     *
     * @param aOrdering Specialisation specific implementation for the
     *      abstract @c CAknTreeListOrdering class. This object defines the
     *      order of hierarchical list items.
     *
     * @param aDrawNow @c ETrue to redraw the list after it has been sorted.
     *
     * @post The list is sorted according to the set ordering.
     */
    void SetOrdering( CAknTreeOrdering* aOrdering, TBool aDrawNow );

    /**
     * Sets custom ordering for the tree.
     *
     * @param aOrdering Implementation for custom ordering interface defining
     *      the order of hierarchical list items.
     *
     * @param aDrawNow @c ETrue to redraw the list after it has been sorted.
     */
    void SetCustomOrdering( MAknCustomTreeOrdering* aOrdering, TBool aDrawNow );

    /**
     * Sorts the specified tree node.
     *
     * @param aNode Item ID of the node that has to be sorted.
     *
     * @param aSortDescendants @c ETrue to sort the content of the specified
     *      node including the content of its descendant nodes, @c EFalse to
     *      to sort only the child items within the specified node.
     *
     * @param aDrawNow @c ETrue to redraw the list after sorting.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     *
     * @panic EAknHListPanicInvalidItemType Specified item is not a node.
     */
    void Sort( TAknTreeItemID aNode, TBool aSortDescendants, TBool aDrawNow );

    /**
     * Compares two tree items.
     *
     * @param aFirst First item.
     *
     * @param aSecond Second item.
     *
     * @return Positive, if the first item is greater than the second item;
     *      negative, if the first item is less than the second item;
     *      and zero, if the items are equal.
     */
    TInt Compare( const CAknTreeItem& aFirst, const CAknTreeItem& aSecond ) const;

    /**
     * Returns the number of items in the tree.
     *
     * @return Number of items.
     */
    TInt ItemCount() const;

    /**
     * Returns the number of visible items in the tree. This excludes all the
     * items in collapsed folders.
     *
     * @return Number of visible items.
     */
    TInt VisibleItemCount() const;

    /**
     * Returns the index of specified item. The index is equal to the number
     * of tree items in the tree structure before the specified item.
     *
     * @param aItem Pointer to tree item.
     *
     * @return The index of specified item. Value @c KErrNotFound is returned
     *      if the specified item is not found.
     */
    TInt ItemIndex( const CAknTreeItem* aItem ) const;

    /**
     * Returns the index from subset of visible items. The index is equal to
     * the number of tree items in the expanded tree structure before the 
     * specified item.
     *
     * @param aItem Pointer to tree item.
     *
     * @return The index of specified item. Value @c KErrNotFound is returned
     *      if the specified item is not found, or not in the expanded tree
     *      structure.
     */
    TInt VisibleItemIndex( const CAknTreeItem* aItem ) const;

    /**
     * Returns visible item based on the given index.
     *
     * @param aIndex Index defining the items position in expanded tree.
     *
     * @return Pointer to tree item. @c NULL, if item with given index is found.
     */ 
    CAknTreeItem* VisibleItem( TInt aIndex ) const;

    /**
     * Returns the depth of the tree, which equals to number of levels in the
     * expanded part of the tree.
     *
     * @return The depth of expanded tree structure.
     */
    TInt Depth() const;

    /**
     * Retrieves the specified item from the tree.
     *
     * @param aItemId ID of the item to be retrieved.
     *
     * @param aItem Reference to a pointer, which is replaced with a pointer
     *      to the specified item, if it is found from the tree.
     *
     * @return @c KErrNone, if the item is found from the tree. The return
     *      value @c KErrNotFound indicates that the item was not found.
     */
    TInt GetItem( TAknTreeItemID aItemId, CAknTreeItem*& aItem ) const;

    /**
     * Retrieves the specified item from the tree structure.
     *
     * @param aItemId ID of the item to be retrieved.
     *
     * @return The retrieved tree item.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     */
    CAknTreeItem* Item( TAknTreeItemID aItemId ) const;

    /**
     * Retrieves the specified node from the tree structure.
     *
     * @param aNodeId ID of the node to be retrieved.
     *
     * @return The retrieved tree node.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     *
     * @panic EAknHListPanicInvalidItemType Specified item is not a node.
     */
    CAknTreeNode* Node( TAknTreeItemID aNodeId ) const;

    /** 
     * Add a new item to the tree. The constant @c KAknTreeIIDRoot is to be
     * used as the ID of parent node, when item is added to the the top-most
     * level of the tree.
     *
     * @param aItem The item to be added to the tree structure.
     *
     * @param aParent ID of the parent node to which the item is to be added.
     *
     * @param aDrawNow @c ETrue, if the view is to be updated after the
     *      item has been added to the tree.
     *
     * @return Item ID assigned for the added item.
     */
    TAknTreeItemID AddItemL( CAknTreeItem* aItem, TAknTreeItemID aParent,
        TBool aDrawNow );

    /**
     * Moves the specified item to the specified target node. The constant
     * @c KAknTreeIIDRoot can be used as the ID of target node, when moving
     * the item to the top-most level of the tree.
     *
     * @param aItem ID of the item to be moved.
     *
     * @param aTargetNode ID of the node, where the item is to be moved.
     *
     * @param aDrawNow @c ETrue, if the view is to be updated after the
     *      item has been moved.
     *
     * @leave KErrArgument The specified item is the same as the target node
     *      or one of the ancestors of target node. 
     *
     * @leave KErrNoMemory Not enough memory is available for adding the
     *      specified item to the target node.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     *
     * @panic EAknHListPanicInvalidItemType Specified target node is not a node.
     */
    void MoveItemL( TAknTreeItemID aItem, TAknTreeItemID aTargetNode,
        TBool aDrawNow );

    /**
     * Remove an existing item from the tree. If the specified item is a node,
     * all of its descendants will be removed from the tree as well.
     *
     * @param aItem The item to be removed from the tree structure.
     *
     * @param aDrawNow @c ETrue, if the view is to be updated after the
     *      item has been removed from the tree.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     */
    void RemoveItem( TAknTreeItemID aItem, TBool aDrawNow );

    /**
     * Changes the state of the specified node to expanded. Using constant
     * @c KAknTreeIIDRoot as the node ID expands every node in the tree.
     *
     * @param aNode Item ID of the node to be expanded.
     *
     * @param aDrawNow @c ETrue, if the view is to be updated after the node
     *      has been expanded.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     *
     * @panic EAknHListPanicInvalidItemType Specified item is not a node.
     */
    void ExpandNode( TAknTreeItemID aNode, TBool aDrawNow );

    /**
     * Changes the state of the specified node to collapsed. All the children
     * that are not set persistent will be deleted. Using constant @c
     * KAknTreeIIDRoot as the node ID collapses every node in the tree.
     *
     * @param aNode Item ID of the node to be collapsed.
     *
     * @param aDrawNow @c ETrue, if the view is to be updated after the node
     *      has been collapsed.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     *
     * @panic EAknHListPanicInvalidItemType Specified item is not a node.
     */
    void CollapseNode( TAknTreeItemID aNode, TBool aDrawNow );

    /**
     * Checks if the specified node is expanded. 
     *
     * @param aNode Item ID of the node.
     *
     * @return @c ETrue, if the node is expanded.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     *
     * @panic EAknHListPanicInvalidItemType Specified item is not a node.
     */
    TBool IsExpanded( TAknTreeItemID aNode ) const;

    /**
     * Returns the number of children of a tree node. This method, along with
     * @c Child() method, can be used for enquiring information of the tree
     * structure. Constant @c KAknTreeIIDRoot can be used to get the
     * item count on the top-most level of the list.
     *
     * @param aNode Item ID of a node.
     *
     * @return Number of children of specified node.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     *
     * @panic EAknHListPanicInvalidItemType Specified item is not a node.
     */
    TInt ChildCount( TAknTreeItemID aNode ) const;

    /**
     * Returns the item ID of a child of a tree node. The specific child is
     * specified with an index. The child count for any hierarchical
     * list node can be get with @c ChildCount() method.
     *
     * @param aNode Item ID of the node, whose child is enquiried.
     *
     * @param aIndex Index of the enquiried child.
     *
     * @return Item ID of the specified child. Value @c KAknTreeIIDNone is
     *      returned, if the child with specified index does not exist.
     * 
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     *
     * @panic EAknHListPanicInvalidItemType Specified item is not a node.
     */
    TAknTreeItemID Child( TAknTreeItemID aNode, TInt aIndex ) const;

    /**
     * Returns the item ID of a parent node of specified tree item.
     * 
     * @param aItem Item ID of the item, whose parent is queried.
     *
     * @return Item ID of the parent node.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     */
    TAknTreeItemID Parent( TAknTreeItemID aItem ) const;
    
    /**
     * Adds new observer for the tree. The ownership of the observer interface
     * is not transferred to the tree.
     *
     * @param aObserver Observer.
     */
    void AddObserverL( MAknTreeObserver* aObserver );

    /**
     * Removes an observer from the tree.
     *
     * @param aObserver Observer to be removed.
     *
     * @return @c KErrNotFound, if the specified observer is not found.
     *      Otherwise, the value @c KErrNone is used.
     */
    TInt RemoveObserver( MAknTreeObserver* aObserver );

    /**
     * Checks whether the specified item is marked.
     *
     * @param aItem Item ID.
     *
     * @return @c ETrue, if the item is marked.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     */
    TBool IsMarked( TAknTreeItemID aItem ) const;

    /**
     * Sets the specified item marked or unmarked.
     *
     * @param aItem Item ID of modified item.
     *
     * @param aMarked @c ETrue to set item marked, @c EFalse to unmarked.
     *
     * @param aDrawNow @c ETrue to redraw the view.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     */
    void SetMarked( TAknTreeItemID aItem, TBool aMarked, TBool aDrawNow );

    /**
     * Enables or disables marking of specified list item.
     *
     * @param aItem Item ID of the list item.
     *
     * @param aEnable @c ETrue to enable marking, @c EFalse to disable it.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     */
    void EnableMarking( TAknTreeItemID aItem, TBool aEnable );

    /**
     * Gets all the marked items from the specified node. The marked items
     * are appended to the end of the array passed as parameter.
     *
     * @param aNode Item ID of a node from where the marked items are
     *      retrieved.
     *
     * @param aMarkedItems On return, contains item IDs of marked items in
     *      the specified node.
     *
     * @leave KErrNoMemory Appending item to the array fails.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     *
     * @panic EAknHListPanicInvalidItemType Specified item is not a node.
     */
    void GetMarkedItemsL( TAknTreeItemID aNode,
        RArray<TAknTreeItemID>& aMarkedItems ) const;

    /**
     * Checks whether the specified node is empty.
     *
     * @param aNode Item ID for a node.
     *
     * @return @c ETrue, if the item is empty.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     *
     * @panic EAknHListPanicInvalidItemType Specified target item is not a node.
     */
    TBool IsEmpty( TAknTreeItemID aNode ) const;

    /**
     * Sets whether the specified node appears as non-empty when empty.
     *
     * @param aNode Item ID for a node.
     *
     * @param aNonEmpty @c ETrue to set node appear non-empty, @c EFalse to
     *      to remove previously set flag.
     *
     * @param aDrawNow @c ETrue to redraw the list.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     *
     * @panic EAknHListPanicInvalidItemType Specified target item is not a node.
     */
    void SetNonEmpty( TAknTreeItemID aNode, TBool aNonEmpty, TBool aDrawNow );

    /**
     * Checks whether the specified item is persistent.
     *
     * @param aItem Item ID.
     *
     * @return @c ETrue, if the item is persistent.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     */
    TBool IsPersistent( TAknTreeItemID aItem ) const;

    /**
     * Sets the specified item persistent or non-persistent.
     *
     * @param aItem Item ID of modified item.
     *
     * @param aPersistent @c ETrue to set item persistent.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     */
    void SetPersistent( TAknTreeItemID aItem, TBool aPersistent );

    /**
     * Creates an iterator for the the expanded tree structure.
     *
     * @return Iterator.
     */
    TAknTreeIterator Iterator() const;

    /**
     * Creates an iterator for traversing the tree structure under the
     * specified tree node.
     *
     * @param aNode Iterated node.
     *
     * @param aFlags Flags for the iterator. The @c KSkipCollapsedNodeContents
     *      flag can be used to skip the contents of all collapsed nodes.
     *
     * @return Iterator.
     */
    TAknTreeIterator Iterator( CAknTreeNode* aNode, TUint aFlags ) const;

    /**
     * Notifies the observers that an item has been modified.
     *
     * @param aItem Modified item.
     */
    void ItemModified( CAknTreeItem* aItem );

    /**
     * Adds icon to the tree. The icon is constructed based on the given
     * parameters and the parameters are stored in the tree, so that the icon
     * can be reconstructed on skin change event.
     *
     * @param aId ID of the masked bitmap to be created.
     *
     * @param aFilename Filename to be used to construct the item, if no
     *      matching item was found in the currently active skin.
     *
     * @param aBitmapId ID of the bitmap in the file. Used only if no matching
     *      item was found in the currently active skin.
     *
     * @param aMaskId ID of the mask in the file. Used only if no matching item
     *      was found in the currently active skin.
     *
     * @param aScaleMode Scale mode used when icon's bitmap is resized.
     *
     * @return Icon ID assigned for the created icon.
     */
    TInt AddIconL( const TAknsItemID& aId, const TDesC& aFilename,
        TInt aBitmapId, TInt aMaskId, TScaleMode aScaleMode );

    /**
     * Adds icon to the tree. Icons added with this method are not
     * reconstructed on skin change events.
     *
     * @param aIcon Pointer to the bitmap.
     *
     * @param aMask Pointer to the mask bitmap.
     *
     * @param aTransferOwnership @c ETrue, if ownership of bitmaps is
     * transferred to the list. If the method leaves, it is always on the
     * responsibility of the client code to take care of deleting the bitmaps.
     *
     * @param aScaleMode Scale mode used when icon's bitmap is resized.
     *
     * @return Icon ID assigned for the created icon.
     */
    TInt AddIconL( CFbsBitmap* aIcon, CFbsBitmap* aMask,
        TBool aTransferOwnership, TScaleMode aScaleMode );

    /**
     * Adds colored icon to the tree. The icon is constructed based on the
     * given parameters and the parameters are stored in the tree, so that the
     * icon can be reconstructed on skin change event
     *
     * @param aId Item ID of the masked bitmap to be created.
     *
     * @param aColorId Item ID of the color table.
     *
     * @param aColorIndex Index in the color table.
     *
     * @param aFilename Filename to be used to construct the item, if no
     *      matching item was found in the currently active skin.
     *
     * @param aBitmapId ID of the bitmap in the file. Used only if no matching
     *      item was found in the currently active skin.
     *
     * @param aMaskId ID of the mask in the file. Used only if no matching item
     *      was found in the currently active skin.
     *
     * @param aDefaultColor Color RGB value to be used, if no color is found in
     *      the currently active skin.
     *
     * @param aScaleMode Scale mode used when icon's bitmap is resized.
     *
     * @return Icon ID assigned for the created icon.
     */
    TInt AddColorIconL( const TAknsItemID& aId, const TAknsItemID& aColorId,
        TInt aColorIndex, const TDesC& aFilename, TInt aBitmapId,
        TInt aMaskId, TRgb aDefaultColor, TScaleMode aScaleMode );

    /**
     * Sets icon to the list with specified icon ID. If icon with the same ID
     * is already added to the tree, the existing icon is replaced with the
     * new.
     *
     * @param aIconId Assigned icon ID for the icon.
     *
     * @param aId Item ID of the masked bitmap to be created.
     *
     * @param aFilename Filename to be used to construct the item, if no
     *      matching item was found in the currently active skin.
     *
     * @param aBitmapId ID of the bitmap in the file. Used only if no matching
     *      item was found in the currently active skin.
     *
     * @param aMaskId ID of the mask in the file. Used only if no matching item
     *      was found in the currently active skin.
     *
     * @param aScaleMode Scale mode used when icon's bitmap is resized.
     */
    void SetIconL( TInt aIconId, const TAknsItemID& aId,
        const TDesC& aFilename, TInt aBitmapId, TInt aMaskId,
        TScaleMode aScaleMode );

    /**
     * Sets icon to the list with specified icon ID. If icon with the same ID
     * is already added to the tree, the existing icon is replaced with the
     * new. This method adds only the bitmaps to the list, and they cannot
     * be reconstructed by the list on skin change events.
     * 
     * @param aIconId Assigned icon ID for the icon.
     *
     * @param aIcon Pointer to the bitmap.
     *
     * @param aMask Pointer to the mask bitmap.
     *
     * @param aTransferOwnership @c ETrue, if ownership of bitmaps is
     * transferred to the list. If the method leaves, it is always on the
     * responsibility of the client code to take care of deleting the bitmaps.
     *
     * @param aScaleMode Scale mode used when icon's bitmap is resized.
     */
    void SetIconL( TInt aIconId, CFbsBitmap* aIcon, CFbsBitmap* aMask, 
        TBool aTransferOwnership, TScaleMode aScaleMode );

    /**
     * Sets color icon to the list with specified icon ID. If icon with the
     * same ID is already added to the tree, the existing icon is replaced with
     * the new.
     *
     * @param aIconId Assigned icon ID for the icon.
     *
     * @param aId Item ID of the masked bitmap to be created.
     *
     * @param aColorId Item ID of the color table.
     *
     * @param aColorIndex Index in the color table.
     *
     * @param aFilename Filename to be used to construct the item, if no
     *      matching item was found in the currently active skin.
     *
     * @param aBitmapId ID of the bitmap in the file. Used only if no matching
     *      item was found in the currently active skin.
     *
     * @param aMaskId ID of the mask in the file. Used only if no matching item
     *      was found in the currently active skin.
     *
     * @param aDefaultColor Color RGB value to be used, if no color is found in
     *      the currently active skin.
     *
     * @param aScaleMode Scale mode used when icon's bitmap is resized.
     */
    void SetColorIconL( TInt aIconId, const TAknsItemID& aId,
        const TAknsItemID& aColorId, TInt aColorIndex, const TDesC& aFilename,
        TInt aBitmapId, TInt aMaskId, TRgb aDefaultColor,
        TScaleMode aScaleMode );

    /**
     * Removes previously added icon from the tree.
     *
     * @param aIconId ID of the removed icon.
     *
     * @leave KErrArgument if specified icon is one of the default icons.
     */
    void RemoveIconL( TInt aIconId );

    /**
     * Gets pointer to the specified tree list icon. The ownership of the
     * icon is not transferred to the caller.
     *
     * @param aIconId Icon ID specifying the requested icon.
     *
     * @return Pointer to the requested icon, or NULL if icon with specified
     *      ID was not found.
     */
    CAknTreeListIcon* Icon( TInt aIconId ) const;

    /**
     * Draws the specified icon. The icon is specified with the ID value,
     * which can be one of the default values in @c CAknTree::TIcon enumeration,
     * or a value returned when the icon was added to the list.
     *
     * @param aIconId Icon ID specifying the icon.
     *
     * @param aSize Size of the icon.
     *
     * @param aGc Graphics context the icon is drawn to.
     *
     * @param aPoint A position for the top left corner of the icon.
     *
     * @param aSourceRect A rectangle defining the piece of the icon to be
     *      drawn, with co-ordinates relative to the top left corner of the
     *      bitmap.
     *
     * @return @c KErrNotFound, if no icon with specified ID is found,
     *      otherwise @c KErrNone.
     */
    TInt DrawIcon( TInt aIconId, const TSize& aSize, CWindowGc& aGc,
        const TPoint& aPoint, const TRect& aSourceRect );

    /**
     * Draws text for tree list item. Text is drawn with marquee scrolling
     * when marquee scrolling is enabled, the text does not fit to the
     * rectangle appointed to it, and the item is focused. Otherwise, when
     * some of the conditions above are not true, text is drawn normally with
     * clipping.
     *
     * @param aGc Graphics context.
     *
     * @param aRect Parent rectangle for the text layout.
     *
     * @param aTextLayout Text layout.
     *
     * @param aText Text.
     *
     * @param aFont Font. @c NULL if the font defined in layout is used.
     *
     * @param aItem Pointer to the tree list item, for which the text is drawn.
     *
     * @param aFocused @c ETrue, if the text is drawn for focused tree list
     *      item, otherwise @c EFalse.
     *
     * @param aMarquee @c ETrue, if marquee can be used for drawing the text
     *      when marquee scrolling is enabled for the list.
     */
     void DrawText( CWindowGc& aGc, const TRect& aRect,
        const TAknTextComponentLayout& aTextLayout, const TDesC& aText,
        const CFont* aFont, const CAknTreeItem* aItem, TBool aFocused,
        TBool aMarquee );

    /**
     * Handles skin change.
     */
    void HandleSkinChangeL();

    /**
     * Enables marquee scrolling.
     *
     * @param aEnable @c ETrue to enable marquee, @c EFalse to disable it.
     */
    void EnableMarquee( TBool aEnable );

    /**
     * Returns whether marquee scrolling is enabled.
     *
     * @return @c ETrue when enabled, otherwise @c EFalse.
     */
    TBool IsMarqueeOn() const;

    /**
     * Callback function for marquee control.
     *
     * @param aThis Pointer to an instance of @c CAknTree.
     */
    static TInt MarqueeRedrawRequest( TAny* aThis );

    /**
     * Enables tabulator mode expand and collapse function indicators.
     *
     * @param @aEnable @c ETrue to enable tabulator mode indicators.
     */
    void EnableTabModeFunctionIndicatorsL( TBool aEnable );

    /**
     * Checks whether tabulator mode expand and collapse function indicators are
     * enabled.
     *
     * @return @c ETrue when enabled, otherwise @c EFalse.
     */
    TBool TabModeFunctionIndicators() const;

// from base class CAknTreeItem

    /**
     * From CAknTreeItem.
     * Returns the type of the item.
     *
     * @return Item type.
     */
    TInt Type() const;

    /**
     * From CAknTreeItem.
     * Returns pointer to the root of the tree. This implementation will simply
     * return the pointer to this object, as an instance of @c CAknTree will
     * always be set as the root of the tree.
     *
     * @return Pointer to the tree root.
     */
    CAknTree* Root() const;

// from base class CAknTreeNode

    /**
     * From CAknTreeNode.
     * Changes the state of the whole tree, that is, every node, to expanded.
     */
    void Expand();

    /**
     * From CAknTreeNode.
     * Changes the state of the whole tree, that is, every node, to collapsed.
     */
    void Collapse();

private:

    /**
     * Constructor.
     *
     * @param aList The list owning the tree instance.
     *
     * @param aOrdering Ordering for the tree items.
     */
    CAknTree( CAknTreeList& aList, CAknTreeOrdering* aOrdering );

    /**
     * Second phase constructor.
     */
    void ConstructL();

    /**
     * Notifies the observers of the tree of specified tree event.
     *
     * @param aEvent Tree event.
     *
     * @param aItem Pointer to the tree item affected by the tree event.
     *
     * @param aDrawNow @c ETrue, if the view is to be redrawn after the event.
     */
    void NotifyObservers( MAknTreeObserver::TEvent aEvent, CAknTreeItem* aItem,
        TBool aDrawNow );

    /**
     * Used in marquee control callback.
     */
    TInt DoMarqueeRedrawRequest();

    /**
     * Searches for available icon ID.
     *
     * @return Available icon ID.
     */
    TInt AvailableIconId() const;

    /**
     * Adds an icon to the icon array. The icons in the array are kept
     * ordered based on their ID's. If some icon in the array already has the
     * same ID as the added icon, it is replaced with the new icon.
     *
     * @param aIcon Icon.
     */
    void AddIconL( CAknTreeListIcon* aIcon );

    /**
     * Sorts every node in the tree according to set ordering.
     *
     * @param aDrawNow @c ETrue to redraw the list after it has been sorted.
     */
    void Sort( TBool aDrawNow );

    /**
     * Expands the specified node and notifies the observers of the event.
     *
     * @param aNode Pointer to the node to be expanded.
     *
     * @param aDrawNow @c ETrue, if the view is to be redrawn after the node
     *      has been expanded.
     */
    void DoExpandNode( CAknTreeNode* aNode, TBool aDrawNow );

// from base class CAknTreeItem

    /**
     * From CAknTreeItem.
     */
    void Draw( CWindowGc& aGc, const TRect& aItemRect, const TRect& aRect,
        TBool aFocused ) const;

private: // data

    /**
     * The tree list owning the tree instance.
     */
    CAknTreeList& iList;

    /**
     * Ordering for the tree.
     * Own.
     */
    CAknTreeOrdering* iOrdering;

    /**
     * Custom ordering for the tree.
     * Not owned.
     */
    MAknCustomTreeOrdering* iCustomOrdering;

    /**
     * Tree observers.
     * Not owned.
     */
    RPointerArray<MAknTreeObserver> iObservers;

    /**
     * Pointer array containin pointers to all tree items.
     * Not owned.
     */
    RPointerArray<CAknTreeItem> iItems;

    /**
     * Pointer array containing pointers to stored icons.
     * Own.
     */
    RPointerArray<CAknTreeListIcon> iIcons;

    /**
     * Marquee control.
     * Own.
     */
    CAknMarqueeControl* iMarquee;

    /**
     * The tree item using the marquee control.
     * Not own.
     */
    const CAknTreeItem* iMarqueeItem;

    /**
     * Flags for tree settings.
     */
    TBitFlags32 iFlags;

    };


#endif // C_AKNTREE_H
