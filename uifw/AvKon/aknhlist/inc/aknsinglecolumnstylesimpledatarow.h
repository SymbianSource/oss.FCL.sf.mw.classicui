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
* Description:  Single column style simple data row.
*
*/


#ifndef C_AKNSINGLECOLUMNSTYLESIMPLEDATAROW_H
#define C_AKNSINGLECOLUMNSTYLESIMPLEDATAROW_H


#include "akntreeleaf.h"


/**
 *  Single column style simple data row.
 *
 *  Single column style simple data rows can contain single row of text,
 *  leaf icon, and two optional icons. Each of these icons can also have an
 *  alternate representation, which is used when the item is highlighted.
 *
 *  As simple data row is derived from @c CAknTreeLeaf class, other tree
 *  items cannot be added to it as its children.
 *
 *  @lib aknhlist.lib
 *  @since S60 v5.0
 */
NONSHARABLE_CLASS( CAknSingleColumnStyleSimpleDataRow ) : public CAknTreeLeaf
    {

public:

    /** Icon types for column style simple data row. */
    enum TIconType
        {
        /** Leaf icon. */
        EIcon,
        /** Optional icon. */
        EOptIcon,
        /** Highlighted leaf icon. */
        EHighlightedIcon,
        /** Highlighted optional icon. */
        EHighlightedOptIcon
        };

    /**
     * Two phased constructor. Creates an instance of single column style
     * simple data row and leaves the newly created object in the cleanup
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
    static CAknSingleColumnStyleSimpleDataRow* NewLC( const TDesC& aText,
        TUint32 aFlags );

    /**
     * Destructor.
     */
    virtual ~CAknSingleColumnStyleSimpleDataRow();

    /**
     * Text on simple data row.
     *
     * @return Text.
     */
    const TDesC& Text( ) const;

    /**
     * Sets the text for the simple data row. Does not change the position of
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
     * Sets an icon ID for a specified simple data row icon type. The icon ID
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
     * Determines which icon ID is to be used when drawing the simple data row.
     * The used icon depends on the value of @c aFocused parameter and which
     * icon IDs have been set.
     *
     * @param aFocused @c ETrue, if icon ID for focused item is required.
     *
     * @return Icon ID.
     */
    TInt IconId( TBool aFocused ) const;

    /**
     * Determines which icon ID is to be used for the optional icon when
     * drawing the simple data row. The used icon ID depends on the value of
     * @c aFocused parameter, whether item is marked, and which optional
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
     * Draws the simple data row.
     *
     * @param aGc Graphic context.
     *
     * @param aItemRect A rectangle defining the size and position of the
     *      simple data row.
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
    CAknSingleColumnStyleSimpleDataRow( TUint32 aFlags );

    /**
     * Second phase constructor.
     *
     * @param aText Text for the simle data row.
     */
    void ConstructL( const TDesC& aText );

private: // data

    /**
     * List item text.
     * Own.
     */
    HBufC* iText;

    /**
     * Icon ID for simple data row icon.
     */
    TInt iIcon;

    /**
     * Icon ID for optional simple data row icon.
     */ 
    TInt iOptIcon;

    /**
     * Icon ID for highlighted simple data row icon.
     */
    TInt iHighlightedIcon;

    /**
     * Icon ID for highlighted optional simple data row icon.
     */
    TInt iHighlightedOptIcon;

    };


#endif // C_AKNSINGLECOLUMNSTYLESIMPLEDATAROW_H
