/*
* Copyright (c) 2003 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Utilities for handling mirrored bitmaps
*    
*
*/


#ifndef __AKNBITMAPMIRRORUTILS_H__
#define __AKNBITMAPMIRRORUTILS_H__

#include <fbs.h> 

#define KWholeBitmapRect TRect(-1,-1,-1,-1)

/**
 * This class contains utility methods for handling mirrored bitmaps. Methods
 * are intended to be used internally in Avkon controls only.
 *
 */
class AknBitmapMirrorUtils
    {
    public:

   /**
    * @deprecated
    */
    static void LoadHorizontalMirroredBitmapL(CFbsBitmap* aBitmap, const TDesC& aFileName,TInt32 aId=0);

   /**
    * @deprecated
    */
    static void LoadPartialBitmapL(CFbsBitmap* aBitmap, const TDesC& aFileName,TInt32 aId, TRect aRect, TBool aMirrorHorizontally);

    /**
    * Creates a new copy of a bitmap and mirrors it horizontally. Leaves in error sitations.
    * Note that for horizontally large bitmaps this method is potentially slow.
    * Note that for SVG icons, AknIconUtils::SetSize() must be called before this function!
    * 
    * @param    aBitmap         Bitmap to be the mirrored. When calling this method this parameter may not be null.
    * @return                   Pointer to mirrored copy of original bitmap    
    */
    static CFbsBitmap* HorizontallyMirrorBitmapL( CFbsBitmap* aBitmap );

    /**
    * Creates a new copy of a specified part of bitmap and mirrors it if required. 
    * Leaves in error situations. Note that for horizontally large bitmaps this method is potentially slow.
    * Note that for SVG icons, AknIconUtils::SetSize() must be called before this function!
    * 
    * @param    aBitmap             Bitmap which will contain the mirrored picture when method returns. When
    *                               calling this method this parameter may not be null.
    * @param    aRect               Rect which specifies the rect of the original bitmap that will be 
    *                               loaded and mirrored. Areas outside rect are discarded from the 
    *                               resulting bitmap. Coordinates are relative to the left top corner
    *                               of the bitmap before mirroring. If special KWholeBitmapRect is used
    *                               as rect, then whole bitmap is used.
    * @param    aMirrorHorizontally If true then mirroring is performed. Otherwise no mirroring is done.
    * @return                       Pointer to new bitmap    
    */
    static CFbsBitmap* PartialBitmapL( CFbsBitmap* aBitmap, TRect aRect, TBool aMirrorHorizontally );    

   /**
    * Creates a new bitmap which has been mirrored. Ownership of the new bitmap is transferred
    * to the caller and ownership of the sourcebitmap remains to the caller. If both
    * mirroring direction parameters are EFalse, then a new bitmap without mirroring 
    * is returned.
    * 
    * @param    aSourceBitmap The sourcebitmap which content will be mirrored.
    * @param    aVerticalMirror ETrue if bitmaps should be mirrored vertically
    * @param    aHorizontalMirror ETrue if bitmaps should be mirrored horizontally
    * @return   New bitmap which content has been mirrored according to given parameters.
    *
    */
    static CFbsBitmap* CreateMirroredBitmapL(CFbsBitmap* aSourceBitmap, TBool aVerticalMirror, TBool aHorizontalMirror); 
    

private:
    
    static CFbsBitmap* CreateBitmapL(CFbsBitmap* aSourceBitmap, TInt aMirrorDirection); 
    static CFbsBitmap* CreateBitmapOptimizedL(CFbsBitmap* aSourceBitmap, TInt aMirrorDirection); 

    };

#endif //  __AKNBITMAPMIRRORUTILS_H__
