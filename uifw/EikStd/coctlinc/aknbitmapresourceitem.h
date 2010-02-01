/*
* Copyright (c) 2008-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Bitmap resource item
*
*/



#ifndef C_AKNBITMAPRESOURCEITEM_H
#define C_AKNBITMAPRESOURCEITEM_H


#include <e32def.h>
#include <e32base.h>

#include "aknresourceitem.h"

class CFbsBitmap;

/**
*  The bitmap resource item class.
*
*  Resource item for storing a RGB bitmap and a bitmap mask.
*  Implements the MAknResourceItem interface.
*
*  @lib eikcoctl
*  @since S60 v5.0
*/
NONSHARABLE_CLASS( CAknBitmapResourceItem ) : public CBase, public MAknResourceItem
    {

public:

    /**
     * NewL.
     * Two-phased constructor.
     * @return a pointer to the created instance of CAknBitmapResourceItem.
     */
    static CAknBitmapResourceItem* NewL( TInt aId );

    /**
     * ~CAknBitmapResourceItem
     * Virtual Destructor.
     */
    virtual ~CAknBitmapResourceItem();

    /**
     * Used to fetch the bitmaps (resources) this item holds.
     * The ownership of the bitmaps changes with this
     * method call, so caller must take care of the bitmaps destruction.
     * @param aBitmap Pointer to RGB bitmap
     * @param aMask Pointer to bitmap mask
     * @return ETrue if the bitmaps were found and valid.
     */
    TBool GetBitmaps( CFbsBitmap*& aBitmap, CFbsBitmap*& aMask );

    /**
     * Sets the bitmaps of this item.
     * The ownership of the parameter bitmaps does not change
     * with this method call, instead new bitmaps are created with parameter
     * bitmaps handles. So caller must take care of the parameter bitmaps
     * destruction.
     * @param aBitmap Pointer to RGB bitmap
     * @param aMask Pointer to bitmap mask
     */
    void SetBitmapsL( CFbsBitmap* aBitmap, CFbsBitmap* aMask );

// from base class MAknResourceItem

    /**
     * From MAknResourceItem.
     * Duplicates the item and the resources it holds
     * and returns the created resource item.
     * @return Duplication result.
     */
    MAknResourceItem* DuplicateL();

    /**
     * From MAknResourceItem.
     * Returns the resource item id.
     * @return Resource item id.
     */
    TInt Id() const;

    /**
     * From MAknResourceItem.
     * Returns ETrue if the aType resource change applies
     * to this resource item. Otherwise EFalse.
     * @param aType Resource change type
     * @return ETrue if resource change applies to 
     * the resource item.
     */
    TBool Invalidate( TInt aType );

private:

    /**
     * CAknBitmapResourceItem.
     * C++ default constructor.
     */
    CAknBitmapResourceItem( TInt aId );

private: // data

    /**
     * Pointer to RGB resource bitmap.
     * Own.
     */
    CFbsBitmap* iBitmap;

    /**
     * Pointer to resource bitmap mask.
     * Own.
     */
    CFbsBitmap* iBitmapMask;

    /**
     * Resource id.
     */
    TInt iId;

    };

#endif // C_AKNBITMAPRESOURCEITEM_H
