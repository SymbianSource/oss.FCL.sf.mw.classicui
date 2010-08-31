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
* Description:  Single column style core data row.
*
*/


#ifndef C_AKNSINGLECOLUMNSTYLECOREDATAROW_H
#define C_AKNSINGLECOLUMNSTYLECOREDATAROW_H

#include <babitflags.h>

#include "akntreeleaf.h"


/**
 *  Single column style core data row.
 *
 *  Single column style core data rows can contain a single row of text
 *  consisting of up to three three different columns. The number of visible
 *  columns depends on used layout and column list settings. In addition to
 *  the text columns, the row can contain a leaf icon and two optional icons.
 *  Each of these icons can also have an alternate representation, which is
 *  used when the item is highlighted.
 *
 *  As core data row is derived from @c CAknTreeLeaf class, other tree
 *  items cannot be added to it as its children.
 *
 *  @lib aknhlist.lib
 *  @since S60 v5.0
 */
NONSHARABLE_CLASS( CAknSingleColumnStyleCoreDataRow ) : public CAknTreeLeaf
    {

public:

    /** Single style core data row flags. */
    enum TItemFlags
        {
        /** Third text column is enabled. */
        EThirdColumnEnabled = 0x00010000,
        /** Core data row is emphasised. */
        EEmphasis           = 0x00020000
        };

    /** Icon types for single column style core data row. */
    enum TIconType
        {
        /** Leaf icon. */
        EIcon,
        /** First optional icon. */
        EOptIcon1,
        /** Second optional icon. */
        EOptIcon2,
        /** Highlighted leaf icon. */
        EHighlightedIcon,
        /** Highlighted first optional icon. */
        EHighlightedOptIcon1,
        /** Highlighted second optional icon. */
        EHighlightedOptIcon2
        };

    /**
     * Two phased constructor. Creates an instance of single column style
     * core data row and leaves the newly created object in the cleanup
     * stack. Core data rows constucted with this constructor, by default,
     * have third text column disabled.
     *
     * @param aFirstColumn Text for the first column of core data row.
     *
     * @param aSecondColumn Text for the second column of core data row.
     *
     * @param aFlags Flags.
     *
     * @return Pointer to the newly created object.
     *
     * @post Pointer to the newly created object is left in cleanup stack.
     *
     * @leave KErrNoMemory Not enough memory.
     */
    static CAknSingleColumnStyleCoreDataRow* NewLC( const TDesC& aFirstColumn,
        const TDesC& aSecondColumn, TUint32 aFlags );

    /**
     * Two phased constructor. Creates an instance of single column style
     * core data row and leaves the newly created object in the cleanup
     * stack. Core data rows constructed with this constructor, by default,
     * have third text column enabled.
     *
     * @param aFirstColumn Text for the first column of core data row.
     *
     * @param aSecondColumn Text for the second column of core data row.
     *
     * @param aThirdColumn Text for the third column of core data row.
     *
     * @param aFlags Flags.
     *
     * @return Pointer to the newly created object.
     *
     * @post Pointer to the newly created object is left in cleanup stack.
     *
     * @leave KErrNoMemory Not enough memory.
     */
    static CAknSingleColumnStyleCoreDataRow* NewLC( const TDesC& aFirstColumn,
        const TDesC& aSecondColumn, const TDesC& aThirdColumn,
        TUint32 aFlags );

    /**
     * Destructor.
     */
    virtual ~CAknSingleColumnStyleCoreDataRow();

    /**
     * Text on specified core data row text column.
     *
     * @param aColumnIndex Text column index.
     *
     * @return Text.
     */
    const TDesC& Text( TInt aColumnIndex ) const;

    /**
     * Sets the text for the specified column in core data row. Does not
     * change the position of the row in the tree.
     *
     * @param aText Text.
     *
     * @param aColumnIndex Text column index.
     *
     * @param aDrawNow @c ETrue to redraw the item after the text is changed.
     *
     * @leave KErrNoMemory Not enough memory.
     *
     * @leave KErrNotFound Specified column does not exist.
     */
    void SetTextL( const TDesC& aText, TInt aColumnIndex, TBool aDrawNow );

    /**
     * Checks whether core data row is emphasised.
     *
     * @return @c ETrue if row is emphasised, otherwise @c EFalse;
     */
    TBool IsEmphasised() const;

    /**
     * Set emphasis for core data row. When the core data row is emphasised,
     * another layout that emphasises the text is used when drawing the item.
     * By default, each core data row is set emphasised.
     *
     * @param aEmphasis @c ETrue if item is to be emphasised.
     *
     * @param aDrawNow @c ETrue to redraw the item, otherwise @c EFalse.
     */
    void SetEmphasis( TBool aEmphasis, TBool aDrawNow );

    /**
     * Checks whether the third text column is enabled.
     *
     * @return @c ETrue when third text column is enabled.
     */
    TBool IsThirdColumnEnabled() const;

    /**
     * Enables third text column to be used in landscape mode when list has
     * enough space for the third column.
     *
     * @param aEnable @c ETrue to enable third column, @c EFalse to disable it.
     *
     * @param aDrawNow @c ETrue to redraw the item, otherwise @c EFalse.
     */
    void EnableThirdColumn( TBool aEnable, TBool aDrawNow );

    /**
     * Returns the icon ID set for the specified icon type.
     *
     * @param aType Type of the icon.
     *
     * @return The icon ID for the icon of specified type. The value
     *      @c AknTreeListIconID::KDefault is returned, if no icon for the
     *      specified type is set.
     */
    TInt Icon( TIconType aType ) const;

    /**
     * Sets an icon ID for a specified core data row icon type. The icon ID
     * indicates which icon from the tree is used when the icon of specified
     * type is drawn by the tree item.
     *
     * @param aType The icon type for which the icon ID is changed. The type
     *      has to be one of the types defined in @c TIconType enumeration.
     *
     * @param aIconId The new icon ID for the specified icon type. The value
     *      @c AknTreeListIconID::KDefault indicates that the default icon
     *      for the type is to be used.
     *
     * @param aDrawNow @c ETrue to redraw the item after the icon is changed.
     */
    void SetIcon( TIconType aType, TInt aIconId, TBool aDrawNow );

    /**
     * Determines which icon ID is to be used when drawing the row. The used
     * icon depends on the value of @c aFocused parameter, and which icon IDs
     * have been set.
     *
     * @param aFocused @c ETrue, if icon ID for focused item is required.
     *
     * @return Icon ID.
     */
    TInt IconId( TBool aFocused ) const;

    /**
     * Determines which icon ID is to be used for the specified optional icon.
     *
     * @param aIndex Index specifying the optional icon.
     *
     * @param aFocused @c ETrue, if icon ID for focused item is required.
     *
     * @return Icon ID for specified optional icon.
     */
    TInt OptionalIconId( TInt aIndex, TBool aFocused ) const;

    /**
     * Determines which text layout variety should be used for the specified
     * text column.
     *
     * @param aColumnIndex Index specifying the text column.
     *
     * @param aOptIconId1 Icon ID for first optional icon.
     *
     * @param aOptIconId2 Icon ID for second optional icon.
     *
     * @param aThirdColumnEnabled
     * 
     * @return Text variety for specified column, or @c KErrNotFound if
     *      suitable variety is not found.
     */
    TInt TextVariety( TInt aColumnIndex, TInt aOptIconId1,
        TInt aOptIconId2, TBool aThirdColumnEnabled ) const;

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
     * Returns the minimum size required to display the item completely in the
     * view with the current layout.
     *
     * @return Minimum size.
     */
    TSize MinimumSize() const;

    /**
     * From CAknTreeItem.
     * Draws the core data row.
     *
     * @param aGc Graphic context.
     *
     * @param aItemRect A rectangle defining the size and position of the
     *      core data row.
     *
     * @param aRect Rectangle that needs to be redrawn.
     *
     * @param aFocused @c ETrue, when the item is focused.
     */
    void Draw( CWindowGc& aGc, const TRect& aItemRect,
        const TRect& aRect, TBool aFocused ) const;

    /**
     * From CAknTreeItem.
     * Handles pointer events.
     *
     * @param aPointerEvent Pointer event.
     *
     * @param aItemRect Item rectangle.
     */
    void HandlePointerEventL( const TPointerEvent& aPointerEvent,
        const TRect& aItemRect );

private:

    /**
     * C++ constructor.
     *
     * @param aFlags Flags.
     */
    CAknSingleColumnStyleCoreDataRow( TUint32 aFlags );

    /**
     * Second phase constructor.
     *
     * @param aFirstColumn Text for the first text column.
     *
     * @param aSecondColumn Text for the second text column.
     */
    void ConstructL( const TDesC& aFirstColumn, const TDesC& aSecondColumn );

    /**
     * Second phase constructor.
     *
     * @param aFirstColumn Text for the first text column.
     *
     * @param aSecondColumn Text for the second text column.
     *
     * @param aThirdColumn Text for the third text column.
     */
    void ConstructL( const TDesC& aFirstColumn, const TDesC& aSecondColumn,
        const TDesC& aThirdColumn );

private: // data

    /**
     * List item text for the first text column.
     * Own.
     */
    HBufC* iFirstColumn;

    /**
     * List item text for the second text column.
     * Own.
     */
    HBufC* iSecondColumn;

    /**
     * List item text for the third text column.
     * Own.
     */
    HBufC* iThirdColumn;

    /**
     * Icon ID for main core data row icon.
     */
    TInt iIcon;

    /**
     * Icon ID for first optional icon.
     */ 
    TInt iOptIcon1;

    /**
     * Icon ID for second optional icon.
     */
    TInt iOptIcon2;

    /**
     * Icon ID for highlighted main core data row icon.
     */
    TInt iHighlightedIcon;

    /**
     * Icon ID for first highlighted optional icon.
     */
    TInt iHighlightedOptIcon1;

    /**
     * Icon ID for second highlighted optional icon.
     */
    TInt iHighlightedOptIcon2;

    };


#endif // C_AKNSINGLECOLUMNSTYLECOREDATAROW_H
