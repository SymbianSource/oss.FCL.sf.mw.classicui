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
* Description:  Single column style subtitle row.
*
*/


#ifndef C_AKNSINGLECOLUMNSTYLESUBTITLEROW_H
#define C_AKNSINGLECOLUMNSTYLESUBTITLEROW_H


#include "akntreenode.h"


/**
 *  Single column style subtitle row.
 *
 *  Single column style subtitle rows can contain single row of text,
 *  expanded and collapsed node icons, and one optional icon. Each of these
 *  icons can also have an alternate representation, which is used when the
 *  item is highlighted.
 *
 *  Subtitle row is derived from @c CAknTreeNode class, so other tree items
 *  can be grouped under the subtitle row by adding them to the node.
 *
 *  @lib aknhlist.lib
 *  @since S60 v5.0
 */
NONSHARABLE_CLASS( CAknSingleColumnStyleSubtitleRow ) : public CAknTreeNode
    {

public:

    /** Icon types for single column style subtitle row. */
    enum TIconType
        {
        /** Icon for node's expanded state. */
        EExpandedIcon,
        /** Icon for node's collapsed state. */
        ECollapsedIcon,
        /** Optional marking icon. */
        EOptIcon,
        /** Highlighted icon for node's expanded state. */
        EHighlightedExpandedIcon,
        /** Highlighted icon for node's collapsed state. */
        EHighlightedCollapsedIcon,
        /** Highlighted optional marking icon. */
        EHighlightedOptIcon,
        };

    /**
     * Two phased constructor. Creates an instance of single column style
     * subtitle row and leaves the newly created object in the cleanup
     * stack.
     *
     * @param aText Text for the simple data row.
     *
     * @param aFlags Flags.
     *
     * @return Pointer to the newly created object.
     *
     * @post Pointer to the newly created object is left in cleanup stack.
     *
     * @leave KErrNoMemory Not enough memory.
     */
    static CAknSingleColumnStyleSubtitleRow* NewLC( const TDesC& aText,
        TUint32 aFlags );

    /**
     * Destructor.
     */
    virtual ~CAknSingleColumnStyleSubtitleRow();

    /**
     * Text on simple data row.
     *
     * @return Text.
     */
    const TDesC& Text() const;

    /**
     * Sets the text for the subtitle row. Does not change the position of
     * the row in the tree.
     *
     * @param aText Text.
     *
     * @param aDrawNow @c ETrue to redraw the item after the text is changed.
     *
     * @leave KErrNoMemory Not enough memory.
     */
    void SetTextL( const TDesC& aText, TBool aDrawNow );

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
     * Sets an icon ID for a specified subtitle icon type. The icon ID
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
     * Determines which icon ID is to be used when drawing the subtitle row.
     * The used icon depends on the value of @c aFocused parameter, which
     * icon IDs have been set, and whether the node is expanded or collapsed.
     *
     * @param aFocused @c ETrue, if icon ID for focused item is required.
     *
     * @return Icon ID.
     */
    TInt IconId( TBool aFocused ) const;

    /**
     * Determines which icon ID is to be used for the optional icon when
     * drawing the subtitle  row. The used icon ID depends on the value of
     * @c aFocused parameter, whether node is marked, and which optional
     * icon IDs have been set.
     * 
     * @param aFocused @c ETrue, if icon ID for focused item is required.
     *
     * @return Icon ID for optional icon.
     */
    TInt OptionalIconId( TBool aFocused ) const;

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
     * Draws the subtitle row.
     *
     * @param aGc Graphic context.
     *
     * @param aItemRect A rectangle defining the size and position of the
     *      subtitle row.
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
    CAknSingleColumnStyleSubtitleRow( TUint32 aFlags );

    /**
     * Second phase constructor.
     *
     * @param aText Text.
     */
    void ConstructL( const TDesC& aText );

private: // data

    /**
     * Text.
     * Own.
     */
    HBufC* iText;

    /**
     * Icon ID for expanded node icon.
     */
    TInt iExpandedIcon;

    /**
     * Icon ID for collapsed node icon.
     */
    TInt iCollapsedIcon;

    /**
     * Icon ID for optional marking icon.
     */
    TInt iOptIcon;

    /**
     * Icon ID for highlighted expanded node icon.
     */
    TInt iHighlightedExpandedIcon;

    /**
     * Icon ID for highlighted collapsed node icon.
     */
    TInt iHighlightedCollapsedIcon;

    /**
     * Icon ID for highlighted optional marking icon.
     */
    TInt iHighlightedOptIcon;

    };


#endif // C_AKNSINGLECOLUMNSTYLESUBTITLEROW_H
