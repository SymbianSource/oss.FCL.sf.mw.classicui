/*
* Copyright (c) 2004 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Indicator item for double span scroll bar.
*    
*
*/


#ifndef __AKNDOUBLESPANSCROLLINDICATORITEM_H
#define __AKNDOUBLESPANSCROLLINDICATORITEM_H

#include <e32base.h>
#include <AknsItemID.h>

class MAknsSkinInstance;
class CFbsBitmap;

NONSHARABLE_CLASS(CAknDoubleSpanScrollIndicatorItem) : public CBase
	{
public: // public construction and destruction methods
   
   /**
    * Two-phased constructor.
    *
    * @since    2.6
    * @return   Newly constructed object.
    */
    static CAknDoubleSpanScrollIndicatorItem* NewL(TBool aRotated,
        TAknsItemID aTopItem,
        TInt        aTopItemBitmapId,
        TInt        aTopItemMaskId,
        TAknsItemID aMiddleItem,
        TInt        aMiddleItemBitmapId,
        TInt        aMiddleItemMaskId,
        TAknsItemID aBottomItem,
        TInt        aBottomItemBitmapId,
        TInt        aBottomItemMaskId
        );
    
    /**
     * Creates only a container for bitmaps
     *
     * @since   5.0
     * @return  Newly constructed object, with
     *          NULL bitmap pointers.
     */
    static CAknDoubleSpanScrollIndicatorItem* NewL();

   /**
    * Destructor.
    *
    * @since    2.6
    */
	~CAknDoubleSpanScrollIndicatorItem(); 

public: // new methods


private: // new methods

   /**
    * C++ default constructor.
    *
    * @since    2.6
    */
	CAknDoubleSpanScrollIndicatorItem();
    
   /**
    * By default Symbian 2nd phase constructor is private.
    *
    * @since    2.6
    */
    void ConstructL(TBool aRotated,
        TAknsItemID aTopItem,
        TInt        aTopItemBitmapId,
        TInt        aTopItemMaskId,
        TAknsItemID aMiddleItem,
        TInt        aMiddleItemBitmapId,
        TInt        aMiddleItemMaskId,
        TAknsItemID aBottomItem,
        TInt        aBottomItemBitmapId,
        TInt        aBottomItemMaskId
        );


   /**
    * Creates a new bitmap based on the given source bitmap. New bitmap
    * will be rotated 90 degrees agains clock direction if wanted.
    *
    * @since    2.6
    * @param    aSourceBitmap  Bitmap which content is copied to new bitmap
    * @param    aRotated       If ETrue the source bitmap data is rotated
    *                          90 degrees.
    * @return   a pointer to a new bitmap.
    *
    */
    CFbsBitmap* CreateBitmapL(CFbsBitmap* aSourceBitmap, TBool aRotated);

   /**
    * Creates a new bitmap and a mask based on the given skin item id. 
    * New bitmap will be rotated 90 degrees agains clock direction if wanted.
    *
    * @since    2.6
    * @param    aID            Skin item id for the bitmap and mask.
    * @param    aBitmap        When this method returns this will contain a poiter
    *                          to a new bitmap.
    * @param    aMask          When this method returns this will contain a poiter
    *                          to a new mask bitmap.
    * @param    aRotated       If ETrue the skin source bitmap data is rotated
    *                          90 degrees.
    *
    */
    void CreateSkinnedBitmapAndMaskL(MAknsSkinInstance* aInstance, 
        const TAknsItemID& aID,
        CFbsBitmap*& aBitmap, 
        CFbsBitmap*& aMask,
        TBool aRotated);


public: // data
    TAknsItemID iTopId;
    TAknsItemID iMidId;
    TAknsItemID iBottomId;

    CFbsBitmap* iTop;
	CFbsBitmap* iTopMask;
	CFbsBitmap* iMiddle;
	CFbsBitmap* iMiddleMask;
    CFbsBitmap* iBottom;
    CFbsBitmap* iBottomMask;
    TSize       iItemSize;

    };

#endif
