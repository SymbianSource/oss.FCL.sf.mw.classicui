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
* Description:  
*
*/


#ifndef C_AKNTREELISTICON_H
#define C_AKNTREELISTICON_H


#include <e32base.h>
#include <AknsItemID.h>
#include <AknIconUtils.h>
#include <babitflags.h>


/**
 *  Internal class for tree list icon data.
 *
 *  This class encapsulates the paramaters used in constructing a bitmap and
 *  mask for an icon used in tree list, as well as, the bitmap and mask itself.
 *  The stored parameters can then  be used in reconstructing the bitmaps on
 *  skin change events.
 *
 *  @lib aknhlist.lib
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( CAknTreeListIcon ) : public CBase
    {

public:

    /**
     * Two-phased constructor.
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
     *
     * @return Pointer to the newly created object.
     */
    static CAknTreeListIcon* NewLC( TInt aIconId, const TAknsItemID& aId,
        const TDesC& aFilename, TInt aBitmapId, TInt aMaskId,
        TScaleMode aScaleMode );

    /**
     * Two-phased constructor.
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
     *
     * @return Pointer to the newly created object.
     */
    static CAknTreeListIcon* NewLC( TInt aIconId, CFbsBitmap* aIcon,
        CFbsBitmap* aMask, TBool aTransferOwnership, TScaleMode aScaleMode );

    /**
     * Two-phased constructor.
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
     *
     * @return Pointer to the newly created object.
     */
    static CAknTreeListIcon* NewLC( TInt aIconId, const TAknsItemID& aId,
        const TAknsItemID& aColorId, TInt aColorIndex,
        const TDesC& aFilename, TInt aBitmapId, TInt aMaskId,
        TRgb aDefaultColor, TScaleMode aScaleMode );

    /**
     * Destructor.
     */
    ~CAknTreeListIcon();

    /**
     * Determines the order of two CAknTreeListIcon objects based on their IDs.
     *
     * @param aFirst First compared icon.
     *
     * @param aSecond Second compared icon.
     *
     * @return Negative value, if the first has smaller ID; zero, if the icons
     *      have the same ID; and positive value, if second has smaller ID.
     */
    static TInt Compare( const CAknTreeListIcon& aFirst,
        const CAknTreeListIcon& aSecond );

    /**
     * Compares the given ID with the given icon. This function can be used
     * when icons are stored in @c RPointerArray and searched from the array
     * with on their IDs.
     *
     * @param aIconId Compared icon ID.
     *
     * @param aIcon Compared icon.
     *
     * @return Negative value, if the ID is smaller than the one in the icon;
     *      zero, if the IDs match, and positive value if ID is greater than
     *      the one in the icon.
     */
    static TInt CompareId( const TInt* aIconId, const CAknTreeListIcon& aIcon );

    /**
     * Reconstructs the icon's bitmap and mask according to the stored
     * parameters.
     */
    void ReconstructL();

    /**
     * Returns the ID assigned for the icon.
     *
     * @return The tree list icon ID.
     */
    TInt Id() const;

    /**
     * Returns the skin item ID of the contained icon.
     *
     * @return Skin item ID of icon.
     */
    const TAknsItemID& SkinItemID() const;

    /**
     * Returns pointer to the icon's bitmap. Ownership is not transsferred.
     *
     * @return The icon's bitmap.
     */
    CFbsBitmap* Bitmap();

    /**
     * Returns pointer to the icon's mask. Ownership is not transsferred.
     *
     * @return The icon's mask.
     */
    CFbsBitmap* Mask();

    /**
     * Returns the icon's size.
     *
     * @return The icon's size.
     */
    TSize Size() const;

    /**
     * Returns the icon's scale mode.
     *
     * @return The icon's scale mode.
     */
    TScaleMode ScaleMode() const;

    /**
     * Sets new size for the icon.
     *
     * @param aSize Icon size.
     */
    TInt SetSize( const TSize& aSize );

private:

    /**
     * C++ constructor.
     */
    CAknTreeListIcon( TInt aIconId, const TAknsItemID& aId, TInt aBitmapId,
        TInt aMaskId, TScaleMode aScaleMode );

    /**
     * C++ constructor.
     */
    CAknTreeListIcon( TInt aIconId, CFbsBitmap* aIcon, CFbsBitmap* aMask,
        TBool aTransferOwnership, TScaleMode aScaleMode );

    /**
     * C++ constructor.
     */
    CAknTreeListIcon( TInt aIconId, const TAknsItemID& aId,
        const TAknsItemID& aColorId, TInt aColorIndex, TInt aBitmapId,
        TInt aMaskId, TRgb aDefaultColor, TScaleMode aScaleMode );

    /**
     * Second phase constructor.
     *
     * @param aFilename Name of the icon file.
     */
    void ConstructL( const TDesC& aFilename );

private:

    /**
     * Assigned id for tree list icon.
     */
    const TInt iIconId;

    /**
     * Skin item ID of the icon.
     */
    TAknsItemID iId;

    /**
     * Skin item ID for icons color group.
     */
    TAknsItemID iColorId;

    /**
     * Color index for colored item.
     */
    TInt iColorIndex;

    /**
     * Bitmap ID.
     */
    TInt iBitmapId;

    /**
     * Mask ID.
     */
    TInt iMaskId;

    /**
     * Default color for the icon.
     */
    TRgb iDefaultColor;

    /**
     * Filename for icon file.
     * Own.
     */
    HBufC* iFilename;

    /**
     * Bitmap.
     * Own.
     */
    CFbsBitmap* iBitmap;

    /**
     * Mask.
     * Own.
     */
    CFbsBitmap* iMask;

    /**
     * Flags.
     */
    TBitFlags32 iFlags;

    /**
     * Size of the icon.
     */
    TSize iSize;

    /**
     * Icon's scale mode.
     */
    TScaleMode iScaleMode;

    };


#endif // C_AKNTREELISTICON_H
