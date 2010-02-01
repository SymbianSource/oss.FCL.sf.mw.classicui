/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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



#include <AknUtils.h>
#include <fbs.h>

#include "aknbitmapresourceitem.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CAknBitmapResourceItem* CAknBitmapResourceItem::NewL( TInt aId )
    {
    CAknBitmapResourceItem* self = 
        new ( ELeave ) CAknBitmapResourceItem( aId );
    return self;
    }


// ---------------------------------------------------------------------------
// Destructor.
// ---------------------------------------------------------------------------
//
CAknBitmapResourceItem::~CAknBitmapResourceItem()
    {
    delete iBitmap;
    delete iBitmapMask;
    }


// ---------------------------------------------------------------------------
// Used to fetch the bitmaps (resources) this item holds. The ownership of the
// bitmaps changes with this method call, so caller must take care of 
// the destruction of the bitmaps.
// ---------------------------------------------------------------------------
//
TBool CAknBitmapResourceItem::GetBitmaps( CFbsBitmap*& aBitmap,
                                         CFbsBitmap*& aMask )
    {
    if ( iBitmap && iBitmapMask )
        {
        aBitmap = iBitmap;
        aMask = iBitmapMask;

        // not owned anymore by this item -> set pointers to null
        iBitmap = 0;
        iBitmapMask = 0;
        return ETrue;
        }
    return EFalse;
    }


// ---------------------------------------------------------------------------
// Sets the bitmaps of this item. The ownership of the parameter bitmaps 
// does not change with this method call, instead new bitmaps are created with
// parameter bitmaps handles. So caller must take care of the parameter 
// bitmaps destruction.
// ---------------------------------------------------------------------------
//
void CAknBitmapResourceItem::SetBitmapsL( CFbsBitmap* aBitmap,
                                         CFbsBitmap* aMask )
    {
    delete iBitmap;
    delete iBitmapMask;
    iBitmap = 0;
    iBitmapMask = 0;

    iBitmap = new ( ELeave ) CFbsBitmap;
    iBitmap->Duplicate( aBitmap->Handle() );
    iBitmapMask = new ( ELeave ) CFbsBitmap;
    iBitmapMask->Duplicate( aMask->Handle() );
    }


// ---------------------------------------------------------------------------
// Duplicates the item and the resources it holds and 
// returns the created resource item.
// ---------------------------------------------------------------------------
//
MAknResourceItem* CAknBitmapResourceItem::DuplicateL()
    {
    CAknBitmapResourceItem* newItem = CAknBitmapResourceItem::NewL( iId );
    newItem->SetBitmapsL( iBitmap, iBitmapMask );
    return newItem;
    }


// ---------------------------------------------------------------------------
// Returns the resource item id.
// ---------------------------------------------------------------------------
//
TInt CAknBitmapResourceItem::Id() const
    {
    return iId;
    }


// ---------------------------------------------------------------------------
// Returns ETrue if the aType resource change applies to this resource item. 
// Otherwise EFalse.
// ----------------------------------------------------------------------------
//
TBool CAknBitmapResourceItem::Invalidate( TInt aType )
    {
    TBool invalidate = EFalse;
    switch ( aType )
        {
        case KAknsMessageSkinChange:
        case KEikDynamicLayoutVariantSwitch:
            invalidate = ETrue;
            break;
        default:
            invalidate = EFalse;
        }
    return invalidate;
    }


// ---------------------------------------------------------------------------
// C++ default constructor can NOT contain any code that might leave.
// ---------------------------------------------------------------------------
//
CAknBitmapResourceItem::CAknBitmapResourceItem( TInt aId ) 
    : iBitmap( 0 ), iBitmapMask( 0 ), iId( aId )
    {
    }
