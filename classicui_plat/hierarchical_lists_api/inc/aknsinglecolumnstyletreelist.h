/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Single style hierarchical column list.
*
*/


#ifndef C_AKNSINGLECOLUMNSTYLETREELIST_H
#define C_AKNSINGLECOLUMNSTYLETREELIST_H


#include <akntreelist.h>


/**
 *  Single style hierarchical column list.
 *
 *  Single style hierarchical column list is hierarchical list type that
 *  can contain three types of items: Core data rows, simple data rows, and
 *  subtitle rows.
 *
 *  Core data row is a list item that consists of two text columns in
 *  portrait mode, and in addition to those, it can have an optional
 *  third text column in landscape mode. Core data row can contain one icon
 *  in front of text columns, and up to two optional indicator icons at the
 *  other end of the row.
 *
 *  Simple data row is a list item that consists of single text column, and
 *  can have one leaf icon in front of the text, and one optional icon at
 *  the other end.
 *
 *  Subtitle row is otherwise similar to simple data row, but as core data
 *  row and simple data row are tree leaves that cannot contain other list
 *  items as children, the subtitle row is a tree node that can be used in 
 *  forming the hierarchy for the list. As a node, subtitle row has expand
 *  and collapse functionality, and it can group other tree items, including
 *  other subtitle rows. However, since hierarchical column list does not
 *  support indention of tree items or drawing of tree structure lines,
 *  the hierarchy should be limited to two levels for clarity.
 * 
 *  The @c CAknSingleColumnStyleTreeList class contains only methods for
 *  constructing the list, constructing and adding the list type specific
 *  items to the list, and setting and getting item type specific properties.
 *  Other methods for list usage can be found from its parent class.
 *
 *  @see CAknTreeList
 *
 *  Here is an example of how an instance of window-owning single style
 *  hierarchical column list can be constructed:
 *
 *  @code
 *  // Construct the list, set its size, and make it visible.
 *  CAknSingleColumnStyleTreeList* list
 *      = CAknSingleColumnStyleTreeList::NewL();
 *  list->SetRect( rect );
 *  list->MakeVisible( ETrue );
 *  @endcode
 *
 *  Adding items to the constructed list:
 *
 *  @code  
 *  TUint32 flags = CAknSingleColumnStyleTreeList::EPersistent;
 *  TBool drawNow = EFalse;
 *
 *  // Add simple data row to the top-most level of the tree.
 *  _LIT( KSimpleDataRowText, "Simple data row" );
 *  TAknTreeItemID simpleItem = list->AddSimpleDataRowL( KAknTreeIIDRoot,
 *      KSimpleDataRowText, flags, drawNow );
 *
 *  // Add subtitle row to the to the top-most level of the tree.
 *  _LIT( KSubtitleRowText, "Subtitle row" );
 *  TAknTreeItemID subtitle = list->AddSubtitleRowL( KAknTreeIIDRoot,
 *      KSubtitleRowText, flags, drawNow );
 *
 *  // Add core data row to the previously added subtitle row.
 *  _LIT( KCoreDataRowText, "Core data row" );
 *  TAknTreeItemID coreItem = list->AddCoreDataRowL( subtitle,
 *      KCoreDataRowText, KNulDesC, flags, drawNow );
 *  @endcode
 *
 *  @lib aknhlist.lib
 *  @since S60 v5.0
 */
NONSHARABLE_CLASS( CAknSingleColumnStyleTreeList ) : public CAknTreeList
    {

public:

    /** Item types used in single style hierarchical column list. The type
        of each item can be get with @c ItemType() method. */
    enum TItemType
        {
        /** No item type. Associated with constant @c KAknTreeIIDNone. */
        ENone           = 0,
        /** Tree root. Associated with constant @c KAknTreeIIDRoot. */
        ETreeRoot       = 1,
        /** Simple data row. */
        ESimpleDataRow  = 2,
        /** Core data row. */
        ECoreDataRow    = 3,
        /** Subtitle row. */
        ESubtitleRow    = 4
        };

    /** Flags usable with single column style tree items. These flags can
        be given, when adding new items to the list. */
    enum TItemFlags
        {
        /** Item is persistent. */
        EPersistent = 0x01,
        /** Item is marked. */
        EMarked     = 0x02,
        /** Item is expanded. Applicable to subtitle rows only. */
        EExpanded   = 0x04,
        /** Item appears non-empty. Applicable to subtitle rows only. */
        ENonEmpty   = 0x08,
        /** Emphasis. Applicable to core data rows only. */
        EEmphasis   = 0x10,
        /** Item is not markable. */
        EMarkingDisabled = 0x20
        };

    /** Icon types usable with single column style hierarchical list.
        Highlighted icons are used when item is focused, and normal icons are
        used when item is not focused, or corresponding highlighted icon is
        not specified for the item. */
    enum TIconType
        {
        /** Leaf icon. 
            Only usable with core data rows and simple data rows. */
        ELeaf                       = 0,
        /** Highlighted leaf icon.
            Only usable with core data rows and simple data rows. */
        EHighlightedLeaf            = 1,
        /** Expanded node icon. Only usable with subtitle rows. */
        EExpandedNode               = 2,
        /** Highlighted expanded node icon. Only usable with subtitle rows. */
        EHighlightedExpandedNode    = 3,
        /** Collapsed node icon. Only usable with subtitle rows. */
        ECollapsedNode              = 4,
        /** Highlighted collapsed node icon. Only usable with subtitle rows. */
        EHighlightedCollapsedNode   = 5,
        /** First optional icon. */
        EOptionalIcon1              = 6,
        /** First highlighted optional icon. */
        EHighlightedOptionalIcon1   = 7,
        /** Second optional icon. Only usable with core data rows. */
        EOptionalIcon2              = 8,
        /** Second highlighted optional icon.
            Only usable with core data rows. */
        EHighlightedOptionalIcon2   = 9
        };

    /**
     * Two phased constructor. Creates a new single style hierarchical column
     * list instance as window-owning control.
     *
     * @return Newly constructed object.
     *
     * @leave KErrNoMemory Not enough memory.
     */
    IMPORT_C static CAknSingleColumnStyleTreeList* NewL();

    /**
     * Two phased constructor. Creates a new single style hierarchical column
     * list instance as non-window-owning component control to the compound
     * control given as parameter.
     *
     * @param aContainer The compound control used as container for the list.
     *
     * @return Newly constructed object.
     *
     * @leave KErrNoMemory Not enough memory.
     */
    IMPORT_C static CAknSingleColumnStyleTreeList* NewL(
        const CCoeControl& aContainer );

    /**
     * Otherwise identical to @c NewL(), but leaves the newly created object
     * in the cleanup stack.
     *
     * @copydoc CAknSingleColumnStyleTreeList::NewL()
     *
     * @post Newly constructed object is left in cleanup stack.
     */
    IMPORT_C static CAknSingleColumnStyleTreeList* NewLC();

    /**
     * Otherwise identical to @c NewL( const CCoeControl& ), but leaves the
     * newly created object in the cleanup stack.
     *
     * @copydoc CAknSingleColumnStyleTreeList::NewL( const CCoeControl& )
     *
     * @post Newly constructed object is left in cleanup stack.
     */
    IMPORT_C static CAknSingleColumnStyleTreeList* NewLC(
        const CCoeControl& aContainer );

    /**
     * Destructor.
     */
    virtual ~CAknSingleColumnStyleTreeList();

    /**
     * Adds new simple data row to single style hierarchical column list. New
     * simple data row with the specified content is constructed and added to
     * the specified parent node. Constant @c KAknTreeIIDRoot can be used as
     * parent node, if the new item is to be added to the top-most level of
     * the hierarchy.
     *
     * @param aParent The item ID of the parent node.
     *
     * @param aText Text for simple data row.
     *
     * @param aFlags Flags for simple data row. Possible flags are defined
     *      in @c CAknSingleColumnStyleTreeList::TItemFlags enumeration.
     *
     * @param aDrawNow @c ETrue, if the list is to be redrawn after the item
     *      has been added to the list, otherwise @c EFalse.
     *
     * @return The Item ID for the added node.
     *
     * @leave KErrNoMemory Not enough memory.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     *
     * @panic EAknHListPanicInvalidItemType Specified parent item is not a node.
     */
    IMPORT_C TAknTreeItemID AddSimpleDataRowL( TAknTreeItemID aParent,
        const TDesC& aText, TUint32 aFlags, TBool aDrawNow );

    /**
     * Adds new core data row to single style hierarchical column list. New
     * core data row containing specified two text columns is constructed and
     * added to the specified parent node. Constant @c KAknTreeIIDRoot can be
     * used as parent node, if the new item is to be added to the top-most
     * level of the hierarchy. By default, the core data row created with this
     * method has its third text column disabled, but it can later be enabled
     * with @c EnableThirdColumn() method.
     *
     * @param aParent The item ID of the parent node.
     *
     * @param aFirstColumn Text for first column of core data row.
     *
     * @param aSecondColumn Text for second column of core data row.
     *
     * @param aFlags Flags for core data row. Possible flags are defined
     *      in @c CAknSingleColumnStyleTreeList::TItemFlags enumeration.
     *
     * @param aDrawNow @c ETrue, if the list is to be redrawn after the item
     *      has been added to the list, otherwise @c EFalse.
     *
     * @return The Item ID for the added node.
     *
     * @leave KErrNoMemory Not enough memory.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     *
     * @panic EAknHListPanicInvalidItemType Specified parent item is not a node.
     */
    IMPORT_C TAknTreeItemID AddCoreDataRowL( TAknTreeItemID aParent,
        const TDesC& aFirstColumn, const TDesC& aSecondColumn, TUint32 aFlags,
        TBool aDrawNow );

    /**
     * Adds new core data row to single style hierarchical column list. New
     * core data row containing the specified three text columns is constructed
     * and added to the specified parent node. Constant @c KAknTreeIIDRoot can
     * be used as parent node, if the new item is to be added to the top-most
     * level of the hierarchy. By default, the core data row created with this
     * method has its third text column enabled, but it can later be disabled
     * with @c EnableThirdColumn() method.
     *
     * @param aParent The item ID of the parent node.
     *
     * @param aFirstColumn Text for first column of core data row.
     *
     * @param aSecondColumn Text for second column of core data row.
     *
     * @param aThirdColumn Text for third column of core data row. The third
     *      column is visible only in landscape mode.
     *
     * @param aFlags Flags for core data row. Possible flags are defined
     *      in @c CAknSingleColumnStyleTreeList::TItemFlags enumeration.
     *
     * @param aDrawNow @c ETrue, if the list is to be redrawn after the item
     *      has been added to the list, otherwise @c EFalse.
     *
     * @leave KErrNoMemory Not enough memory.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     *
     * @panic EAknHListPanicInvalidItemType Specified parent item is not a node.
     */
    IMPORT_C TAknTreeItemID AddCoreDataRowL( TAknTreeItemID aParent,
        const TDesC& aFirstColumnd, const TDesC& aSecondColumn,
        const TDesC& aThirdColumn, TUint32 aFlags, TBool aDrawNow );

    /**
     * Adds new subtitle row to single style hierarchical column list. New row
     * with the given content is constructed and added to the specified parent
     * node. Constant @c KAknTreeIIDRoot can be used as parent node, if the new
     * item is to be added to the top-most level of hierarchy.
     *
     * @param aParent The item ID of the parent node.
     *
     * @param aText Text for subtitle row.
     *
     * @param aFlags Flags for subtitle row. Possible flags are defined
     *      in @c CAknSingleColumnStyleTreeList::TItemFlags enumeration.
     *
     * @param aDrawNow @c ETrue, if the list is to be redrawn after the item
     *      has been added to the list, otherwise @c EFalse.
     *
     * @leave KErrNoMemory Not enough memory.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     *
     * @panic EAknHListPanicInvalidItemType Specified parent item is not a node.
     */
    IMPORT_C TAknTreeItemID AddSubtitleRowL( TAknTreeItemID aParent,
        const TDesC& aText, TUint32 aFlags, TBool aDrawNow );

    /**
     * Returns the text field of the specified list item.
     *
     * @param aItem Item ID.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     */
    IMPORT_C const TDesC& Text( TAknTreeItemID aItem ) const;

    /**
     * Returns the specified text column of specified list item. If the text
     * for specified column is not set, or the specified column does not
     * exist, empty descriptor is returned.
     * 
     * @param aItem Item ID.
     *
     * @param aColumnIndex Column index.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     */
    IMPORT_C const TDesC& Text( TAknTreeItemID aItem, TInt aColumnIndex ) const;

    /**
     * Sets the text for specified hierarchical column list item.
     *
     * @param aItem Item ID.
     *
     * @param aText Text for specified list item.
     *
     * @param aDrawNow @c ETrue, if the list is to be redrawn after the text
     *      has been set, otherwise @c EFalse.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     */
    IMPORT_C void SetTextL( TAknTreeItemID aItem, const TDesC& aText,
        TBool aDrawNow );

    /**
     * Sets the text for specified column of specified hierarchical column
     * list item. Non-zero value for column list can only be used with core
     * data row, as the other row types contain only one text column.
     *
     * @param aItem Item ID.
     *
     * @param aText Text for specified list item.
     *
     * @param aColumnIndex Index specifying the text column.
     *
     * @param aDrawNow @c ETrue, if the list is to be redrawn after the text
     *      has been set, otherwise @c EFalse.
     *
     * @leave KErrNotFound Specified column does not exist.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     *
     * @panic EAknHListPanicInvalidItemType Invalid item type.
     */
    IMPORT_C void SetTextL( TAknTreeItemID aItem, const TDesC& aText,
        TInt aColumnIndex, TBool aDrawNow );

    /**
     * Checks whether the specified core data row is emphasised. When core
     * data row is emphasized, it uses different text layout for emphasising
     * the row.
     *
     * @param aItem Item ID for core data row.
     *
     * @return @c ETrue if item is emphasised, otherwise @c EFalse.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     */
    IMPORT_C TBool IsEmphasised( TAknTreeItemID aItem ) const;

    /** 
     * Sets the emphasis for specified core data row. 
     *
     * @param aItem Item ID of core data row.
     *
     * @param aEmphasis @c ETrue to set emphasis on, @c EFalse to set it off.
     *
     * @param aDrawNow @c ETrue to redraw the list, otherwise @c EFalse.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     *
     * @panic EAknHListPanicInvalidItemType Invalid item type.
     */
    IMPORT_C void SetEmphasis( TAknTreeItemID aItem, TBool aEmphasis,
        TBool aDrawNow );

    /**
     * Checks whether the third text column is enabled for specified core
     * data row. If third text column is enabled, it is shown for the item
     * in landscape mode, when list has enough space for the third column.
     *
     * @param aItem Item ID of core data row.
     *
     * @return @c ETrue if third column is enabled, otherwise @c EFalse.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     */
    IMPORT_C TBool IsThirdColumnEnabled( TAknTreeItemID aItem ) const;

    /**
     * Enables or disables third text column usage in landscape mode for
     * specified core data row. 
     *
     * @param aItem Item ID or core data row.
     *
     * @param aEnable @c ETrue to enable third text column usage, @c EFalse
     *      to disable it.
     *
     * @param aDrawNow @c ETrue to redraw the list, otherwise @c EFalse.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     *
     * @panic EAknHListPanicInvalidItemType Invalid item type.
     */
    IMPORT_C void EnableThirdColumn( TAknTreeItemID aItem, TBool aEnable,
        TBool aDrawNow );

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
     * @param aIconId Icon ID. Icon ID is one of the pre-defined icon IDs, or
     *      an integer value returned by @c AddIconL() or @c AddColorIconL()
     *      methods when new icon was added to the list.
     *
     * @param aDrawNow @c ETrue to redraw the list after the icon has been
     *      changed, otherwise @c EFalse.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     *
     * @panic EAknHListPanicInvalidItemType Specified icon is not applicable
     *      with the item type.
     */
    IMPORT_C void SetIcon( TAknTreeItemID aItem, TIconType aType,
        TInt aIconId, TBool aDrawNow );

    /**
     * Checks the type of the specified list item.
     *
     * @param aItem Item ID specifying the list item.
     *
     * @return Type of the item.
     *
     * @panic EAknHListPanicInvalidItemID Item with specified ID is not found.
     */
    IMPORT_C TItemType ItemType( TAknTreeItemID aItem ) const;

// from base class CAknTreeList

    /**
     * From CAknTreeList.
     * Sets the flags for the single style hierarchical column list.
     *
     * @param aFlags Flags.
     */
    void SetFlags( TUint32 aFlags );

    /**
     * From CAknTreeList.
     * Handles resource changes.
     *
     * @param aType
     */
    void HandleResourceChange( TInt aType );

private:

    /**
     * Default constructor.
     */
    CAknSingleColumnStyleTreeList();

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

    /**
     * Updates indention.
     */
    void UpdateIndention();

private: // data

    };


#endif // C_AKNSINGLECOLUMNSTYLETREELIST_H
