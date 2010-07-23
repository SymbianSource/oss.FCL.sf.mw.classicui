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
* Description:  Abstract base class for hierarchical lists.
*
*/


#ifndef C_AKNTREELIST_H
#define C_AKNTREELIST_H


#include <AknControl.h>
#include <w32std.h>
#include <akntreelistobserver.h>
#include <AknIconUtils.h> // TScaleMode

class CAknTree;
class CAknTreeListView;
class MAknCustomTreeOrdering;
class TAknsItemID;

/** Flag to indicate that hierarchical list is looping. */
const TUint32 KAknTreeListLooping = 0x0001;

/** Flag to indicate that hierarchical list structure lines are not visible. */
const TUint32 KAknTreeListNoStructureLines = 0x0002;

/** Flag to set marquee scrolling on. */
const TUint32 KAknTreeListMarqueeScrolling = 0x0004;

/** Flag to disable indention of hierarchical list items. Setting this flag
    also forces the tree structure lines invisible. */
const TUint32 KAknTreeListNoIndention = 0x0008;

/** Flag to set hierarchical list markable. The list items can always be
    marked by list client with API methods, but when list is set markable,
    it responds to specified pointer and key event by marking/unmarking
    items as required. */
const TUint32 KAknTreeListMarkable = 0x0010;


/**
 *  Abstract base class for hierarchical lists.
 *
 *  This class functions as a base class for hierarchical lists. It contains
 *  the APIs common to all hierarchical lists. The internal structure of the
 *  list is not exposed directly to the list clients, instead the structure
 *  can be accessed through the APIs in this class. The items in the list are
 *  referred with item IDs, which are returned to the client when the items
 *  are added to the list.
 *
 *  List items are divided into leaves and nodes, the difference being that
 *  nodes have expand and collapse functionality and can contain other tree
 *  items as child items, whereas leaves cannot contain other list items.
 *  Methods @c IsLeaf() and @c IsNode() can be used for checking if items
 *  belong into these groups.
 *
 *  The expand and collapse events, among other list events, are send to list
 *  observers through @c MAknTreeListObserver interface. This enables that
 *  the whole list does not have to be populated at once, as the content of
 *  each node can be added when the node is expanded. To avoid unnecessary
 *  memory consumption, the content of each node is removed from the list
 *  when the node is collapsed. However, list items can be set persistent,
 *  in which case they are not removed from nodes on collapse events.
 *
 *  As the hierarchical list items are list specialisation specific, the
 *  specialisations of this class have to provide APIs for constructing and
 *  adding new items to the list, and getting and setting specialisation
 *  specific properties of the list items.
 *
 *  All the methods that might affect the appearance of the list view have an
 *  additional @c aDrawNow parameter, which can be used to indicate whether
 *  the list view should be redrawn to correspond to the modified list
 *  structure. This allows consecutive calls to be made without the list view
 *  being updated between every call by setting the @c aDrawNow parameter to
 *  @c EFalse in all of the calls but the last. The normal draw methods 
 *  inherited from @c CCoeControl can also be used to draw the updated view.
 *
 *  @see MAknTreeListObserver
 *
 *  @lib aknhlist.lib
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( CAknTreeList ) : public CAknControl
    {

public:


	// for focus handling after Sort
   enum TFocusBehaviour
            {
            ESaveFocus,
            EMoveFocusToFirstItem
            };

    /**
     * Destructor.
     */
    virtual ~CAknTreeList();

    /**
     * Sets the flags for the hierarchical list.
     *
     * Flags @c KAknTreeListLooping, @c KAknTreeListNoStructureLines,
     * @c KAknTreeListMarqueeScrolling, @c KAknTreeListNoIndention, and
     * @c KAknTreeListMarkable can be used to change the behaviour
     * of the list.
     *
     * Note: Specialisations may override this method in order to restrict the
     * use of some of the flags in specialised list or to handle specialisation
     * specific flags.
     *
     * @param aFlags Flags.
     */
    IMPORT_C virtual void SetFlags( TUint32 aFlags );

    /**
     * Returns the flags set for the list.
     *
     * @return Flags.
     */
    IMPORT_C TUint32 Flags() const;

    /**
     * Moves an existing list item to specified target node. The moved item
     * and the target node have to be specified with the item IDs returned
     * when the items were added to the hierarchical list. The target node
     * cannot be a descendant of the moved node. Otherwise, the moving would
     * break the hierarchical structure. Constant @c KAknTreeIIDRoot can be
     * used as an ID for the target node when the item is to be moved to the
     * top-most level of the list.
     *
     * @param aItem Item ID of the item to be moved.
     *
     * @param aTargetNode ID of the node, where the item is to be moved.
     *
     * @param aDrawNow @c ETrue to redraw the list after the item has been
     *      moved, otherwise @c EFalse.
     *
     * @leave KErrArgument The specified item is the same as the target node
     *      or one of the ancestors of target node. 
     *
     * @leave KErrNoMemory Not enough memory is available for adding the
     *      specified item to the target node.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     *
     * @panic EAknHListPanicInvalidItemType Specified target item is not a node.
     *
     * @pre The moved item and the target node exist in the list, and the
     *      target node is not a descendant of the moved item.
     *
     * @post The item is moved to the specified target node and into a such
     *      position that the children of the target node remain in sorted
     *      order. The updated list is redrawn, if it is requested with the
     *      aDrawNow parameter.
     */
    IMPORT_C void MoveItemL( TAknTreeItemID aItem, TAknTreeItemID aTargetNode,
        TBool aDrawNow );

    /**
     * Removes an item from the hierarchical list. The item to be removed has
     * to be specified with the ID value returned when the item was added to
     * the hierarchical list. If the removed item is a node containing other
     * list items, those items are removed from the list as well. Constant
     * @c KAknTreeIIDRoot can be used to remove every item from the list.
     *
     * @param aItem Item ID of the item to be removed.
     *
     * @param aDrawNow @c ETrue to redraw the list after the item has been
     *      removed, othewise @c EFalse.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     *
     * @pre The specified item exists in the hierarchical list.
     *
     * @post The specified item and all of its descendants are removed from
     *      the list. The updated list is drawn, when it is requested with
     *      the aDrawNow parameter.
     */
    IMPORT_C void RemoveItem( TAknTreeItemID aItem, TBool aDrawNow );

    /**
     * Expands a node in hierarchical list. When a node in the hierarchical
     * list is expanded, either with this method, or with pointer or key
     * event, the observer of the list is notified with respective event.
     * The client of the list can then update the content of the expanded
     * node. Constant @c KAknTreeIIDRoot can be used to expand every node
     * in the tree structure.
     *
     * @param aNode Item ID of the node to be expanded.
     * 
     * @param aDrawNow @c ETrue to redraw the list after the node has been
     *      expanded, otherwise @c EFalse.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     *
     * @panic EAknHListPanicInvalidItemType Specified item is not a node.
     *
     * @pre The specified item exists in the hierarchical list and it is a
     *      node.
     *
     * @post The specified node is expanded. The updated list is drawn, when
     *      it is requested with the aDrawNow parameter.
     */
    IMPORT_C void ExpandNode( TAknTreeItemID aNode, TBool aDrawNow );

    /**
     * Collapses a node in hierarchical list. When a node in the hierarchical
     * list is collapsed, either with this method, or with pointer or key
     * event, all its content that is not set persistent is removed from the
     * list to reduce memory consumption. The observer of the hierarchical
     * list is nofied with the respective event. Constant @c KAknTreeIIDRoot
     * can be used to collapse every node in the tree structure.
     *
     * @param aNode Item ID of the node to be collapsed.
     *
     * @param aDrawNow @c ETrue to redraw the list after the node has been
     *      collapsed, otherwise @c EFalse.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     *
     * @panic EAknHListPanicInvalidItemType Specified item is not a node.
     *
     * @pre The specified item exists in the hierarchical list and it is a
     *      node.
     *
     * @post The specified item is collapsed and all of its children, which are
     *      not set persistent, are removed from the list.
     */
    IMPORT_C void CollapseNode( TAknTreeItemID aNode, TBool aDrawNow );

    /**
     * Checks whether the specified node is expanded.
     *
     * @param aNode Item ID of a node.
     *
     * @return @c ETrue if the node is expanded.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     *
     * @panic EAknHListPanicInvalidItemType Specified item is not a node.
     */
    IMPORT_C TBool IsExpanded( TAknTreeItemID aNode ) const;

    /**
     * Gets the item ID of the focused item.
     *
     * @return Item ID of the focused item. Value @c KAknTreeIIDNone is
     *      returned if no item is focused.
     */
    IMPORT_C TAknTreeItemID FocusedItem() const;

    /**
     * Sets the focused item and its position on the list view. When the
     * focused item is changed, the vertical position of the view is changed
     * so that the position of the focused item on the view matches the given
     * index. The horizontal position of the view is changed so that the
     * the beginning of the focused item is visible.
     *
     * @param aItem Item ID of the item to be focused.
     *
     * @param aIndex The position of the focused item on the list view. If the
     *      index does not refer to any visible view location, that is, the
     *      index is less than zero or greater than or equal to the number of
     *      items in the view, the focused item is changed to specified item,
     *      but the position of the view is not changed.
     *
     * @param aDrawNow @c ETrue to redraw the list after the focused item
     *      has been changed, otherwise @c EFalse.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     */
    IMPORT_C void SetFocusedItem( TAknTreeItemID aItem, TInt aIndex,
        TBool aDrawNow );

    /**
     * Highlight rectangle for the focused item. The returned rectangle is
     * screen relative and it can be used, for example, when positioning
     * pop-up for focused item. If the focused item is not visible, the
     * method returns an empty rectangle.
     *
     * @return Highlight rectangle of focused list item.
     */
    IMPORT_C TRect HighlightRect() const;

    /**
     * Adds a new icon to the list to be used by all list items. The same
     * icon can be used by multiple tree items and its referenced by the
     * ID returned by this function. The given parameters are also stored
     * in the tree list, which enables the tree list to reconstruct the
     * bitmaps on skin change events. If this behaviour is insufficient for
     * the client, it can always replace the existing icons by itself with
     * @c AssignIconL or @c AssignColorIconL method.
     *
     * @param aId Item ID of the icon to be added.
     *
     * @param aFilename Filename to be used to construct the item, 
     *      if no matching item was found in the currently active skin.
     *
     * @param aBitmapId ID of the bitmap in the file. 
     *      Used only if no matching item was found in the currently 
     *      active skin.
     *
     * @param aMaskId ID of the mask in the file.
     *      Used only if no matching item was found in the currently
     *      active skin.
     * 
     * @param aScaleMode Scale mode used when icon's bitmap is resized.
     *
     * @return ID assigned for the added icon.
     *
     * @leave KErrNoMemory Not enough memory.
     */
    IMPORT_C TInt AddIconL( const TAknsItemID& aId, const TDesC& aFilename,
        TInt aBitmapId, TInt aMaskId, TScaleMode aScaleMode );

    /**
     * Adds a new icon to the list. The ownership of given bitmaps is
     * transferred to the list only if specified with @c aTransferOwnership
     * parameter. Note that icons added to the list with this method cannot
     * be reconstructed on skin change events by the list. If necessary,
     * previously added icons can be replaced with @c AssignIconL method.
     *
     * @param aIcon Pointer to the bitmap.
     *
     * @param aMask Pointer to the mask bitmap.
     *
     * @param aTransferOwnership @c ETrue, if ownership of bitmaps is
     * transferred to the list. If the method leaves, it is always on the
     * responsibility of the client code to take care of deleting the bitmaps.
     *
     * @param aScaleMode The scale mode used when the icon is resized.
     *
     * @return ID assigned for the added icon.
     *
     * @leave KErrNoMemory Not enough memory.
     */
    IMPORT_C TInt AddIconL( CFbsBitmap* aIcon, CFbsBitmap* aMask,
        TBool aTransferOwnership, TScaleMode aScaleMode );

    /**
     * Adds a new icon to the list to be used by all list items. The same
     * icon can be used by multiple tree items and it is referenced by the
     * icon ID returned by this function. The given parameters are stored
     * in the tree list, and they are used in reconstructing the bitmaps on
     * skin change events.
     *
     * @param aId Item ID of the icon to be added.
     *
     * @param aColorId Item ID of the color table.
     *
     * @param aColorIndex Index in the color table.
     *
     * @param aFilename Filename to be used to construct the item, 
     *      if no matching item was found in the currently active skin.
     *
     * @param aBitmapId ID of the bitmap in the file. 
     *      Used only if no matching item was found in the currently 
     *      active skin.
     *
     * @param aMaskId ID of the mask in the file.
     *      Used only if no matching item was found in the currently
     *      active skin.
     *
     * @param aDefaultColor Color RGB value to be used, if no color
     *      is found in the currently active skin.
     *
     * @param aScaleMode Scale mode used when icon's bitmap is resized.
     *
     * @return ID assigned for the added icon.
     *
     * @leave KErrNoMemory Not enough memory.
     */
    IMPORT_C TInt AddColorIconL( const TAknsItemID& aId,
        const TAknsItemID& aColorId, TInt aColorIndex, const TDesC& aFilename,
        TInt aBitmapId, TInt aMaskId, TRgb aDefaultColor,
        TScaleMode aScaleMode );

    /**
     * Assigns an icon to the tree list with the specified ID. If an icon
     * with specified ID already exists in the list, the existing icon is
     * replaced with the new one. The given parameters are stored in the
     * tree list, and they are used in reconstructing the bitmaps on skin
     * change events.
     *
     * @param aIconId Icon ID assigned for the icon.
     *
     * @param aId Item ID of the icon to be added.
     *
     * @param aFilename Filename to be used to construct the item, 
     *      if no matching item was found in the currently active skin.
     *
     * @param aBitmapId ID of the bitmap in the file. 
     *      Used only if no matching item was found in the currently 
     *      active skin.
     *
     * @param aMaskId ID of the mask in the file.
     *      Used only if no matching item was found in the currently
     *      active skin.
     *
     * @param aScaleMode Scale mode used when icon's bitmap is resized.
     *
     * @leave KErrNoMemory Not enough memory.
     *
     * @leave KErrArgument Specified icon ID is out of allowed range.
     */
    IMPORT_C void AssignIconL( TInt aIconId, const TAknsItemID& aId,
        const TDesC& aFilename, TInt aBitmapId, TInt aMaskId,
        TScaleMode aScaleMode );

    /**
     * Assigns an icon to the tree list with the specified ID. If an icon
     * with specified ID already exists in the list, the existing icon is
     * replaced with the new one. The ownership of bitmaps is transferred to
     * the list only if so specifed with @c aTransferOnwership parameter.
     * Note that icons added with this method cannot be reconstructed on
     * skin change events by list.
     *
     * @param aIconId Icon ID assigned for the icon.
     *
     * @param aIcon Pointer to the bitmap.
     *
     * @param aMask Pointer to the mask bitmap.
     *
     * @param aTransferOwnership @c ETrue, if ownership of bitmaps is
     *      transferred to the list. If the method leaves, it is always on
     *      the responsibility of the client code to take care of deleting
     *      the bitmaps.
     *
     * @param aScaleMode Scale mode used when icon's bitmap is resized.
     *
     * @leave KErrNoMemory Not enough memory.
     *
     * @leave KErrArgument Specified icon ID is out of allowed range.
     */
    IMPORT_C void AssignIconL( TInt aIconId, CFbsBitmap* aIcon,
        CFbsBitmap* aMask, TBool aTransferOwnership, TScaleMode aScaleMode );

    /**
     * Assigns a color icon to the list with the specified ID. If an icon
     * with specified ID already exists in the list, the existing icon is
     * replaced with the new one. The given parameters are stored in the
     * tree list, and they are used in reconstructing the bitmaps on skin
     * change events.
     *
     * @param aIconId Icon ID assigned for the icon.
     *
     * @param aId Item ID of the icon to be added.
     *
     * @param aColorId Item ID of the color table.
     *
     * @param aColorIndex Index in the color table.
     *
     * @param aFilename Filename to be used to construct the item, 
     *      if no matching item was found in the currently active skin.
     *
     * @param aBitmapId ID of the bitmap in the file. 
     *      Used only if no matching item was found in the currently 
     *      active skin.
     *
     * @param aMaskId ID of the mask in the file.
     *      Used only if no matching item was found in the currently
     *      active skin.
     *
     * @param aDefaultColor Color RGB value to be used, if no color
     *      is found in the currently active skin.
     *
     * @param aScaleMode Scale mode used when icon's bitmap is resized.
     *
     * @leave KErrNoMemory Not enough memory.
     *
     * @leave KErrArgument Specified icon ID is out of allowed range.
     */ 
    IMPORT_C void AssignColorIconL( TInt aIconId, const TAknsItemID& aId,
        const TAknsItemID& aColorId, TInt aColorIndex, const TDesC& aFilename,
        TInt aBitmapId, TInt aMaskId, TRgb aDefaultColor,
        TScaleMode aScaleMode );

    /**
     * Removes the specified icon from the tree list. The specified icon cannot
     * be any of the default tree list icon, in which case the leaves with
     * value @c KErrArgument. If the specified icon is not found, the function
     * does nothing.
     *
     * @param aIconId Icon ID of the removed icon.
     *
     * @leave KErrArgument if specified icon is one of the default icons.
     */
    IMPORT_C void RemoveIconL( TInt aIconId );

    /**
     * Returns the number of children of a hierarchical list node. This method,
     * along with @c Child() method, can be used for enquiring information of
     * the list structure. Constant @c KAknTreeIIDRoot can be used to get the
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
    IMPORT_C TInt ChildCount( TAknTreeItemID aNode ) const;

    /**
     * Gets the item ID of a child of a hierarcical list node. The specific
     * child is specified with an index. The child count for any hierarchical
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
    IMPORT_C TAknTreeItemID Child( TAknTreeItemID aNode, TInt aIndex ) const;

    /**
     * Returns the item ID of the parent of a hierarchical list item. The
     * constant @c KAknTreeIIDRoot is returned for all the items on the
     * top-most level of the tree, and constant @c KaknTereIIDNone for the
     * items that have no parent, that is, the root node.
     *
     * @param aItem Item ID of the item, whose parent is enquiried.
     *
     * @return Item ID of the parent node.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     */
    IMPORT_C TAknTreeItemID Parent( TAknTreeItemID aItem ) const;

    /**
     * Checks whether the hierarchical list contains the list item with
     * specified item ID. The returned value for constant @c KAknTreeIIDRoot
     * will always be @c ETrue, and for constant @c KAknTreeIIDNone @c EFalse.
     *
     * @param aItem Item ID.
     *
     * @return @c ETrue, if the list contains the specified item.
     */
    IMPORT_C TBool Contains( TAknTreeItemID aItem ) const;

    /**
     * Checks whether a hierarchical list item is a node.
     *
     * @param aItem Item ID of checked item.
     *
     * @return @c ETrue, if the specified item is a node.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     */
    IMPORT_C TBool IsNode( TAknTreeItemID aItem ) const;

    /**
     * Checks whether a hierarchical list item is a leaf.
     *
     * @param aItem Item ID of checked item.
     *
     * @return @c ETrue, if the specified item is a leaf.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     */
    IMPORT_C TBool IsLeaf( TAknTreeItemID aItem ) const;

    /** 
     * Checks whether a hierarchical list item is marked.
     *
     * @param aItem Item ID of checked item.
     *
     * @return @c ETrue for marked item.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     */
    IMPORT_C TBool IsMarked( TAknTreeItemID aItem ) const;

    /**
     * Sets an item marked. If the marked item is a node, all of its
     * descendants are also set marked.
     *
     * Note that item marking can be changed with this method, even if the
     * list itself is not set markable. Marking changes can be enabled and
     * disabled with @c EnableMarking() method.
     *
     * @param aItem Item ID of the item to be modified.
     * 
     * @param aMarked @c ETrue to set item marked, @c EFalse to unmarked.
     *
     * @param aDrawNow @c ETrue to redraw the list after the item has been
     *      set marked, otherwise @c EFalse.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     */
    IMPORT_C void SetMarked( TAknTreeItemID aItem, TBool aMarked,
        TBool aDrawNow );

    /**
     * Enables or disables marking of specified list item. By default,
     * marking is enabled for every list item.
     *
     * When marking is enabled for an item, its marking can be changed from
     * unmarked to marked, and vice versa, with SetMarked() method, and for
     * markable list, the marking can also change as a result of user action.
     *
     * When marking is disabled, the item can still be either unmarked or
     * marked, but the marking cannot be changed in any way, until it has
     * been enabled again for the item.
     *
     * @param aItem Item ID of the list item.
     *
     * @param aEnable @c ETrue to enable marking, @c EFalse to disable it.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     */
    IMPORT_C void EnableMarking( TAknTreeItemID aItem, TBool aEnable );

    /**
     * Gets all the marked items from the tree list. The marked items are
     * appended to the end of the array passed as parameter.
     *
     * @param aMarkedItems On return, contains item IDs of all marked items.
     *
     * @leave KErrNoMemory Appending item to the array fails.
     */
    IMPORT_C void GetMarkedItemsL( RArray<TAknTreeItemID>& aMarkedItems ) const;

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
    IMPORT_C void GetMarkedItemsL( TAknTreeItemID aNode,
        RArray<TAknTreeItemID>& aMarkedItems ) const;

    /**
     * Checks whether the specified node is empty. To decrease memory
     * consumption, the descendants of tree nodes can be removed from the
     * hierarchical list when the node is collapsed. As the empty nodes may
     * have different appearances in the list view, the collapsed nodes can be
     * set to appear as non-empty with @c SetNonEmpty() method to indicate that
     * nodes will have some content when expanded.
     *
     * @param aNode Item ID of checked item.
     *
     * @return @c ETrue, if the item has been set non-empty.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     *
     * @panic EAknHListPanicInvalidItemType Specified target item is not a node.
     */
    IMPORT_C TBool IsEmpty( TAknTreeItemID aNode ) const;

    /**
     * Sets a node non-empty.
     *
     * @param aNode Item ID of the item to be modified.
     *
     * @param aNonEmpty @c ETrue to set node non-empty, @c EFalse to empty.
     *
     * @param aDrawNow @c ETrue to redraw the list after the setting has been
     *      change, otherwise @c EFalse.
     *      
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     *
     * @panic EAknHListPanicInvalidItemType Specified target item is not a node.
     */
    IMPORT_C void SetNonEmpty( TAknTreeItemID aNode, TBool aNonEmpty,
        TBool aDrawNow );

    /**
     * Checks if the specified item is set persistent. If an item is set
     * persistent, it is not removed from the list, when its parent or any of
     * its ancestors is collapsed. This means also that a node cannot be
     * automatically removed from the list on collapse event, if any of its
     * descendants is set persistent.
     *
     * @param aItem Item ID.
     *
     * @return @c ETrue, if item is set persistent.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     */
    IMPORT_C TBool IsPersistent( TAknTreeItemID aItem ) const;

    /**
     * Sets an item persistent. If the specified item is a node, the state
     * of all its descendants is also changed accordingly.
     *
     * @param aItem Item ID.
     *
     * @param aPersistent @c ETrue to set item persistent.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     */
    IMPORT_C void SetPersistent( TAknTreeItemID aItem,
        TBool aPersistent );

    /**
     * Sets custom ordering for the hierarchical list and sorts the list
     * with the use of given ordering interface. The given interface is
     * used until it is replaced with some other ordering.
     *
     * Note: Ownership of the interface is not transferred to the list.
     *
     * Note: When custom ordering is set to the list, new items are added
     * to the end of their parent nodes, because the interface cannot
     * be used for determining the position for inserted item, as the
     * client receives its identifier only after it has been inserted.
     * @c Sort(TAknTreeItemID, TBool, TBool) method can be used for sorting
     * the node with custom ordering interface after new items have been
     * inserted in the list.
     *
     * @param aOrdering Custom ordering interface used in list sorting.
     *
     * @param aDrawNow @c ETrue to redraw the list after sorting.
     */
    IMPORT_C void Sort( MAknCustomTreeOrdering* aOrdering, TBool aDrawNow );

    /**
     * Sorts the specified node with the use of previously set ordering
     * interface. The sorting can be restricted to the specified node, or
     * the sorting can be set to include also every descendant node of the
     * specified node. Whole list can be sorted by giving the constant
     * @c KAknTreeIIDRoot as the @c aNode parameter. This method has no
     * effect, if no ordering has been set for the list.
     * 
     * @param aNode Item ID of the node that has to be sorted.
     *
     * @param aSortDescendants @c ETrue to sort the content of the specified
     *      node including the content of its descendant nodes, @c EFalse to
     *      sort only the child items within the specified node.
     *
     * @param aDrawNow @c ETrue to redraw the list after sorting.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     *
     * @panic EAknHListPanicInvalidItemType Specified item is not a node.
     */
    IMPORT_C void Sort( TAknTreeItemID aNode, TBool aSortDescendants,
        TBool aDrawNow );

    /**
     * Adds an observer for the hierarchical list. Notifications of the list
     * events are sent to all observers set with this method. Observers can
     * be removed from the list with @c RemoveObserver() method.
     *
     * Note: Hierarchical list also sends a state changed event on every list
     * event through the usual control observer interface that can be set with
     * @c CCoeControl::SetObserver method.
     *
     * @param aObserver Implementation of the observer interface.
     *
     * @post The given interface is set as the observer of the list. The
     *      ownership of the interface is not transferred to the list.
     */
    IMPORT_C void AddObserverL( MAknTreeListObserver* aObserver );

    /**
     * Removes an observer from the hierarchical list.
     *
     * @param aObserver The observer interface to be removed.
     */
    IMPORT_C void RemoveObserver( MAknTreeListObserver* aObserver );

    /**
     * Notifies all of the tree list observers of the specified event. This
     * method is not exported, as it is intended for internal use only.
     *
     * @param aEvent The event to be notified.
     *
     * @param aItem ID of the tree item related to the event.
     */
    void NotifyObservers( MAknTreeListObserver::TEvent aEvent,
        TAknTreeItemID aItem );

    /**
     * Checks whether tabulator mode function indicators are enabled.
     *
     * @return @c ETrue if tabulator mode is enabled.
     */
    IMPORT_C TBool TabModeFunctionIndicators() const;

    /**
     * Changes the appearance of collapse and expand function indicators. The
     * appearance of default function indicators suggest that left and right
     * arrow keys expand and collapse the focused nodes, but when the list is
     * used with tabulators, those keys are used in changing tabulators.
     * Alternate representation for function indicator can be set by enabling
     * tabulator mode indicator with this method.
     *
     * @param aEnable @c ETrue to enable tabulator mode function indicators,
     *      @c EFalse to use the default function indicators.
     */
    IMPORT_C void EnableTabModeFunctionIndicatorsL( TBool aEnable );
    

    /**
     * Sets the focused item and its position on the list view. 
     * 
     * When the focused item is changed, the vertical position of the view
     * is changed as follows:
     * 
     * If the focused item is set on the first page, view is changed
     * to the beginning of the list.
     * 
     * If the focused item is not set on the first page, view is changed so 
     * that focused item is at the lowest line on the screen.
     * 
     * (In this context first page means actual lines from 0
     * to max. number of visible lines - 1)
     *
     * The horizontal position of the view is changed so that the
     * the beginning of the focused item is visible.
     *
     * @param aItem Item ID of the item to be focused.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     */
 	IMPORT_C void SetFocusedItem( TAknTreeItemID aItem );
 	 	
 	/**
     * Gets the index of the focused item on the screen. Possible values are
     * from 0 to max. number of visible lines - 1. Value -1 is
     * returned if no item is focused or focused item is not visible. 
     *
     * @return index of the focused item on the screen.
     */
 	IMPORT_C TInt FocusedItemIndex() const;
 	
 	/**
     * Gets the index of the item on the screen. Possible values are
     * from 0 to max. number of visible lines - 1. Value -1 is
     * returned if the requested item is not visible on the screen. 
     *
     * @return index of the requested item.
     */
 	IMPORT_C TInt VisibleItemIndex( TAknTreeItemID aItem ) const;

 	
 	/**
     * Sets custom ordering for the hierarchical list and sorts the list
     * with the use of given ordering interface. The given interface is
     * used until it is replaced with some other ordering.
     *
     * @param aOrdering Custom ordering interface used in list sorting.
     *
     * @param aFocusBehaviour Tells how focus should be handled after sorting.
     *      @c ESaveFocus saves focus in the item where it was before sorting, 
     *      @c EMoveFocusToFirstItem changes view to the beginning of the list
     *      and moves focus to the first item.  
     *
     * @param aDrawNow @c ETrue to redraw the list after sorting.
     */
 	IMPORT_C void Sort( MAknCustomTreeOrdering* aOrdering, TFocusBehaviour aFocusBehaviour, TBool aDrawNow );

	/**
     * Sorts the specified node with the use of previously set ordering
     * interface. The sorting can be restricted to the specified node, or
     * the sorting can be set to include also every descendant node of the
     * specified node. Whole list can be sorted by giving the constant
     * @c KAknTreeIIDRoot as the @c aNode parameter. This method has no
     * effect, if no ordering has been set for the list.
     *
     * @param aNode Item ID of the node that has to be sorted.
     * 
     * @param aFocusBehaviour Tells how focus should be handled after sorting.
     *      @c ESaveFocus saves focus in the item where it was before sorting, 
     *      @c EMoveFocusToFirstItem changes view to the beginning of the list
     *      and moves focus to the first item. 
     *
     * @param aSortDescendants @c ETrue to sort the content of the specified
     *      node including the content of its descendant nodes, @c EFalse to
     *      sort only the child items within the specified node.
     *
     * @param aDrawNow @c ETrue to redraw the list after sorting.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     *
     * @panic EAknHListPanicInvalidItemType Specified item is not a node.
     */
   	IMPORT_C void Sort( TAknTreeItemID aNode, TFocusBehaviour aFocusBehaviour, TBool aSortDescendants, TBool aDrawNow );
        
    /**
     * Sets text for the empty list. This text is visible if the list box 
     * has no items.
     *
     * @param aText The text for the empty list.
     */
	IMPORT_C void SetEmptyTextL(const TDesC& aText);


// From base class CCoeControl

    /**
     * From CCoeControl.
     * Handles key events. The method will return @c EKeyWasNotConsumed, if
     * the list is not focused.
     *
     * @param aKeyEvent The key event.
     *
     * @param aType The type of key event: @c EEventKey, @c EEventKeyUp or 
     *      @c EEventKeyDown.
     */
    TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType );

    /**
     * From CCoeControl.
     * Changes the visibility of the hierarchical list.
     *
     * @param aVisible @c ETrue to make the list visible, @c EFalse to make
     *      it invisible.
     */
    void MakeVisible( TBool aVisible );

    /**
     * From CCoeControl.
     * Sets whether the list is dimmed.
     *
     * @param aDimmed @c ETrue to set list dimmed, otherwise @c EFalse.
     */
    void SetDimmed( TBool aDimmed );

    /**
     * From CCoeControl.
     * Sets the control's containing window by copying it from aContainer.
     *
     * @param aContainer The compound control that is the container for this
     *      control.
     */
    void SetContainerWindowL( const CCoeControl& aContainer );

    /**
     * From CCoeControl.
     * Sets the control as ready to be drawn.
     */
    void ActivateL();

    /**
     * From CCoeControl.
     * Handles resource changes.
     *
     * @param aType
     */
    void HandleResourceChange( TInt aType );

    /**
     * From CCoeControl.
     * Gets the control's input capabilities.
     *
     * @return The control's input capabilities.
     */
    TCoeInputCapabilities InputCapabilities() const;

    /**
     * From CCoeControl.
     * Handles pointer events.
     *
     * @param aPointerEvent Pointer event.
     */
    void HandlePointerEventL( const TPointerEvent& aPointerEvent );

    /**
     * From CCoeControl.
     * Gets the number of controls contained in a compound control.
     *
     * @return The number of component controls contained by this control.
     */
    TInt CountComponentControls() const;

    /**
     * From CCoeControl.
     * Gets an indexed component of a compound control.
     *
     * @param aIndex The index of the control.
     *
     * @return The component control with an index of aIndex.
     */
    CCoeControl* ComponentControl( TInt aIndex ) const;

protected:

    /**
     * Constructor.
     */
    CAknTreeList();

    /**
     * Second phase constructor. Completes the construction of the base class.
     * When this version of @c BaseConstructL() is used, new window is created
     * for the list.
     */
    void BaseConstructL();

    /** 
     * Second phase constructor. Completes the construction of the base class.
     *
     * @param aContainer Container for the list.
     */
    void BaseConstructL( const CCoeControl& aContainer );

    /**
     * Reference to the tree structure.
     *
     * @return Reference to tree structure.
     */
    CAknTree& Tree();

    /**
     * Constant reference to the tree structure.
     *
     * @return Constant reference to tree structure.
     */
    const CAknTree& Tree() const;

    /**
     * Reference to the tree list view.
     *
     * @return Reference to tree list view.
     */
    CAknTreeListView& View();

    /**
     * Constant reference to the tree list view.
     *
     * @return Constant reference to tree list view.
     */
    const CAknTreeListView& View() const;

// from base class CCoeControl

    /**
     * From CCoeControl.
     * Handles focus change.
     *
     * @param aDrawNow @c EDrawNow to redraw the list.
     */
    void FocusChanged( TDrawNow aDrawNow );

    /**
     * From CCoeControl.
     * Responds to changes to the size and position of this control.
     */
    void SizeChanged();

    /**
     * From CCoeControl.
     * Responds to changes in the position of this control.
     */
    void PositionChanged();

    /**
     * From CCoeControl.
     * Retrieves an object of the same type as that encapsulated in aId.
     *
     * @param aId An encapsulated object type ID.
     *
     * @return Encapsulates the pointer to the object provided. Note that the
     *      encapsulated pointer may be NULL
     */
    TTypeUid::Ptr MopSupplyObject( TTypeUid aId );

private:

// from base class CCoeControl
    
    /**
     * From CCoeControl.
     * Draws the list.
     *
     * @param aRect Specifies the area that needs to be redrawn.
     */
    void Draw( const TRect& aRect ) const;

private: // data

    /**
     * Flags.
     */
    TUint32 iFlags;

    /**
     * Tree structure.
     * Own.
     */
    CAknTree* iTree;

    /**
     * Tree list view.
     * Own.
     */
    CAknTreeListView* iView;

    /**
     * Tree list observers.
     * Not own.
     */
    RPointerArray<MAknTreeListObserver> iObservers;

    /**
     * Index to observer array.
     */
    TInt iIndex;

    };


#endif // C_AKNTREELIST_H
