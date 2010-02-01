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
* Description:  Single style implementation for the abstract tree leaf class.
*
*/


#ifndef C_AKNSINGLESTYLETREELEAF_H
#define C_AKNSINGLESTYLETREELEAF_H


#include "akntreeleaf.h"


/**
 *  Single style implementation for the abstract tree leaf class.
 *
 *  Single style tree leaves can contain single row of text, leaf icon,
 *  and two optional icons. Each of these icons can also have alternate
 *  representation which is used when the item is highlighted.
 *
 *  @lib aknhlist.lib
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( CAknSingleStyleTreeLeaf ) : public CAknTreeLeaf
    {

public:

    /** Icon types for single style tree leaf. */
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
     * Two phased constructor. Creates a single style tree leaf instance.
     *
     * @param aText Text for the leaf.
     *
     * @param aFlags Flags.
     *
     * @return Pointer to the newly created object.
     *
     * @leave KErrNoMemory Not enough memory.
     */
    static CAknSingleStyleTreeLeaf* NewL( const TDesC& aText, TUint32 aFlags );

    /**
     * Otherwise identical to @c NewL, but leaves the newly created object in
     * the cleanup stack.
     *
     * @copydoc CAknSingleStyleTreeLeaf::NewL( const TDesC&, TUint32 )
     *
     * @post Pointer to the newly created object is left in cleanup stack.
     */
    static CAknSingleStyleTreeLeaf* NewLC( const TDesC& aText, TUint32 aFlags );

    /**
     * Destructor.
     */
    virtual ~CAknSingleStyleTreeLeaf();

    /**
     * Text of the leaf.
     *
     * @return Text.
     */
    const TDesC& Text() const;

    /**
     * Sets the text for the leaf. Does not change the position of the leaf
     * in the tree.
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
     * Sets an icon ID for a specified tree leaf icon type. The icon ID
     * indicates which icon from the tree is used when the icon of specified
     * type is drawn by the leaf.
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
     * Determines which icon ID is to be used when drawing the leaf. The used
     * icon depends on the value of @c aFocused parameter and which icon IDs
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
     * Text variety depending on given optional icon IDs.
     *
     * @param aOptIconId1 Icon ID for first optional icon.
     *
     * @param aOptIconId2 Icon ID for second optional icon.
     *
     * @return Text layout variety.
     */
    TInt TextVariety( TInt aOptIconId1, TInt aOptIconId2 ) const;

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
     * Draws the leaf.
     *
     * @param aGc Graphic context.
     *
     * @param aItemRect Item rectangle.
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
    CAknSingleStyleTreeLeaf( TUint32 aFlags );

    /**
     * Second phase constructor.
     *
     * @param aText Text for the leaf.
     */
    void ConstructL( const TDesC& aText );

private: // data

    /**
     * List item text.
     * Own.
     */
    HBufC* iText;

    /**
     * Icon ID for leaf icon.
     */
    TInt iIcon;

    /**
     * Icon ID for first optional leaf icon.
     */ 
    TInt iOptIcon1;

    /**
     * Icon ID for second optional leaf icon.
     */
    TInt iOptIcon2;

    /**
     * Icon ID for highlighted leaf icon.
     */
    TInt iHighlightedIcon;

    /**
     * Icon ID for first highlighted optional leaf icon.
     */
    TInt iHighlightedOptIcon1;

    /**
     * Icon ID for second highlighted optional leaf icon.
     */
    TInt iHighlightedOptIcon2;

    };


#endif // C_AKNSINGLESTYLETREELEAF_H
