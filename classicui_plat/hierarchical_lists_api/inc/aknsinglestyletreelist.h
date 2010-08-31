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
* Description:  Single style hierarchical list.
*
*/


#ifndef C_AKNSINGLESTYLETREELIST_H
#define C_AKNSINGLESTYLETREELIST_H


#include <akntreelist.h>


/**
 *  Single style hierarchical list.
 *
 *  Single style hierarchical list is a hierarchical list specialisation for
 *  a list type with simple list items, which contain only a folder or file
 *  icon, single line of text and some optional icons. This class provides
 *  only the specialisation specific APIs for the list usage. The common
 *  hierarchical list APIs are located in its base class.
 *
 *  Here is an example of how an instance of window-owning single style
 *  hierarchical list can be constructed:
 *
 *  @code
 *  // Construct the list, set its size, and make it visible.
 *  CAknSingleStyleTreeList* list = CAknSingleStyleTreeList::NewL();
 *  list->SetRect( rect );
 *  list->MakeVisible( ETrue );
 *  @endcode
 *
 *  Adding items to the constructed list:
 *
 *  @code
 *  // Add a node to the top-most level of the tree.
 *  _LIT( KNodeText, "Node" );
 *  TUint32 flags = CAknSingleStyleTreeList::EPersistent;
 *  TAknTreeItemID node = list->AddNodeL( KAknTreeIIDRoot, KNodeText,
 *      flags, EFalse );
 *
 *  // Add a leaf to the previously added node.
 *  _LIT( KLeafText, "Leaf" );
 *  TAknTreeItemID leaf = list->AddLeafL( node, KLeafText, flags, EFalse );
 *  @endcode
 *
 *  Changing icons for the list items:
 *
 *  @code
 *  // Add icon to the list and set it to existing list item.
 *  TInt iconId = list->AddIconL( KAknsIIDQgnPropBtCarkit,
 *      AknIconUtils::AvkonIconFileName(), EMbmAvkonQgn_prop_bt_carkit,
 *      EMbmAvkonQgn_prop_bt_carkit_mask, EAspectRatioPreserved );
 *  list->SetIcon( leaf, CAknSingleStyleTreeList::ELeaf, iconId, ETrue );
 *  @endcode
 *
 *  @see CAknTreeList
 *
 *  @lib aknhlist.lib
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( CAknSingleStyleTreeList ) : public CAknTreeList
    {

public:

    /** Icon types usable with single style hierarchical list. Normal icons
        are used when the list item is not focused, and highlighted icons are
        used when list item is focused. Normal icons are used also when list
        item is focused, if corresponding highlighted icon is not specified
        for the list item. */
    enum TIconType
        {
        /** Leaf icon. Only usable with tree leaves. */
        ELeaf                       = 0,
        /** Highlighted leaf icon. Only usable with tree leaves. */
        EHighlightedLeaf            = 1,
        /** Expanded node icon. Only usable with tree nodes. */
        EExpandedNode               = 2,
        /** Highlighted expanded node  icon. Only usable with tree nodes. */
        EHighlightedExpandedNode    = 3,
        /** Collapsed node icon. Only usable with tree nodes. */
        ECollapsedNode              = 4,
        /** Highlighted collapsed node icon. Only usable with tree nodes. */
        EHighlightedCollapsedNode   = 5,
        /** First optional icon. */
        EOptionalIcon1              = 6,
        /** First highlighted optional icon. */
        EHighlightedOptionalIcon1   = 7,
        /** Second optional icon. */
        EOptionalIcon2              = 8,
        /** Second highlighted optional icon. */
        EHighlightedOptionalIcon2   = 9
        };

    /** Single style hierarchical list ordering types. */
    enum TOrdering
        {
        /** Ascending alphabetical ordering based on item text fields. */
        EAscendingAlphabeticalOrdering,
        /** Descending alphabetical ordering based on item text fields. */
        EDescendingAlphabeticalOrdering
        };

    /** Flags usable with single style tree items. */
    enum TSingleStyleItemFlags
        {
        /** Item is persistent. */
        EPersistent = 0x01,
        /** Item is marked. */
        EMarked     = 0x02,
        /** Item is expanded. Applicable to nodes only. */
        EExpanded   = 0x04,
        /** Item appears non-empty. Applicable to nodes only. */
        ENonEmpty   = 0x08
        };

    /**
     * Two phased constructor. Creates a new single style hierarchical list
     * instance as window-owning control.
     *
     * @return Newly constructed object.
     *
     * @leave KErrNoMemory Not enough memory.
     */
    IMPORT_C static CAknSingleStyleTreeList* NewL();

    /**
     * Two phased constructor. Creates a new single style hierarchical list
     * instance as non-window-owning component control to the compound control
     * given as parameter.
     *
     * @param aContainer The compound control used as container for the list.
     *
     * @return Newly constructed object.
     *
     * @leave KErrNoMemory Not enough memory.
     */
    IMPORT_C static CAknSingleStyleTreeList* NewL(
        const CCoeControl& aContainer );

    /**
     * Otherwise identical to @c NewL(), but leaves the newly created object
     * in the cleanup stack.
     *
     * @copydoc CAknSingleStyleTreeList::NewL()
     *
     * @post Newly constructed object is left in cleanup stack.
     */
    IMPORT_C static CAknSingleStyleTreeList* NewLC();

    /**
     * Otherwise identical to @c NewL( const CCoeControl& ), but leaves the
     * newly created object in the cleanup stack.
     *
     * @copydoc CAknSingleStyleTreeList::NewL( const CCoeControl& )
     *
     * @post Newly constructed object is left in cleanup stack.
     */
    IMPORT_C static CAknSingleStyleTreeList* NewLC(
        const CCoeControl& aContainer );

    /**
     * Destructor.
     */
    virtual ~CAknSingleStyleTreeList();

    /**
     * Adds new leaf (file) to single style hierarchical list. New leaf with
     * the specified content is created and added to the specified parent node.
     * Constant @c KAknTreeIIDRoot can be used, if the new item is to be added
     * to the top-most level of the hierarchical list.
     *
     * @param aParent The item ID of the parent node.
     *
     * @param aText Text for the added item.
     *
     * @param aFlags Flags for the added item.
     *
     * @param aDrawNow @c ETrue, if the list is to be redrawn after the item
     *      has been added to the list, otherwise @c EFalse.
     *
     * @return The item ID for the added leaf.
     *
     * @leave KErrNoMemory Not enough memory.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     *
     * @panic EAknHListPanicInvalidItemType Specified parent item is not a node.
     */
    IMPORT_C TAknTreeItemID AddLeafL( TAknTreeItemID aParent,
        const TDesC& aText, TUint32 aFlags, TBool aDrawNow );

    /**
     * Adds new node (folder) to single style hierarchical list. New node with
     * the specified content is created and added to the specified parent node.
     * Constant @c KAknTreeIIDRoot can be used, if the new item is to be added
     * to the top-most level of the hierarchical list.
     *
     * @param aParent The item ID of the parent node.
     *
     * @param aText Text for the added node.
     *
     * @param aFlags Flags for the added node.
     *
     * @param aDrawNow @c ETrue to redraw the list after the node has been
     *      added, otherwise @c EFalse.
     *
     * @return The Item ID for the added node.
     *
     * @leave KErrNoMemory Not enough memory.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     *
     * @panic EAknHListPanicInvalidItemType Specified parent item is not a node.
     */
    IMPORT_C TAknTreeItemID AddNodeL( TAknTreeItemID aParent,
        const TDesC& aText, TUint32 aFlags, TBool aDrawNow );

    /**
     * Sorts the hierarchical list according to the given ordering.
     *
     * @param aOrdering Type of ordering.
     *
     * @param aDrawNow @c ETrue to redraw the list after it has been sorted
     *      according the new ordering, otherwise @c EFalse.
     *
     * @leave KErrNoMemory Not enough memory.
     */
    IMPORT_C void SortL( TOrdering aOrdering, TBool aDrawNow );

    /** 
     * Changes the text of the specified item. Note that the change of text
     * might also affect the item's position in the list, when the items are
     * ordered based on their text fields.
     *
     * @param aItem Item ID of modified item.
     *
     * @param aText New text for the item.
     *
     * @param aDrawNow @c ETrue if the list is to be redrawn after the text
     *      has been changed.
     *
     * @leave KErrNoMemory Not enough memory for adding text.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     *
     * @panic EAknHListPanicInvalidItemType Specified item has invalid type.
     */
    IMPORT_C void SetTextL( TAknTreeItemID aItem, const TDesC& aText,
        TBool aDrawNow );

    /**
     * Returns the text field of the specified item.
     *
     * @param aItem Item ID.
     *
     * @return Text of the specified item.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     */ 
    IMPORT_C const TDesC& Text( TAknTreeItemID aItem ) const;

    /**
     * Sets an icon for a list item. Every list item may have several icons,
     * so the correct icon has to be specified with the icon type. Note that
     * the type has to be applicable to the specified list item. Pre-defined
     * icon IDs can be found within @c AknTreeListIconID namespace. Constant
     * @c AknTreeListIconID::KDefault can be used to indicate that default
     * icon is to be used, and constant @c AknTreeListIconID::KNone to
     * indicate that no icon is to be used.
     *
     * @param aItem Item ID of the modified list item.
     *
     * @param aType The type of the icon to be added.
     *
     * @param aIconId Icon ID. Icon ID is the integer value returned by the
     *      @c AddIconL() method when the icon was added to the list.
     *
     * @param aDrawNow @c ETrue to redraw the list after the icon has been
     *      changed, othewise @c EFalse.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     *
     * @panic EAknHListPanicInvalidItemType Specified icon is not applicable
     *      with the item type.
     */
    IMPORT_C void SetIcon( TAknTreeItemID aItem, TIconType aType,
        TInt aIconId, TBool aDrawNow );

    /**
     * Returns the icon ID set for the specified icon of a list item.
     *
     * @param aItem Item ID of a list item.
     *
     * @param aType Type defining the specific icon within list item.
     *
     * @return Icon ID. The value @c AknTreeListIconID::KDefault is returned,
     *      if no icon has been set. Value @c KErrNotFound is returned, if the
     *      item does not contain icon of specified type.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     */
    IMPORT_C TInt Icon( TAknTreeItemID aItem, TIconType aType ) const;

// from base class CAknTreeList

    /**
     * From CAknTreeList.
     * Sets the flags for the single style hierarchical list.
     *
     * @param aFlags Flags.
     */
    void SetFlags( TUint32 aFlags );

private:

    /**
     * Default constructor.
     */
    CAknSingleStyleTreeList();

    /**
     * Second phase constructor.
     */
    void ConstructL();

    /**
     * Second phase constructor.
     *
     * @param aContainer Container for the list.
     */
    void ConstructL( const CCoeControl& aContainer );

    };


#endif // C_AKNSINGLESTYLETREELIST_H
