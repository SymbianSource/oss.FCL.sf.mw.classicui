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
* Description:  Implementation for CAknTreeListIcon class.
*
*/


#include <AknsUtils.h>
#include <AknIconUtils.h>

#include "akntreelisticon.h"

// Flag definitions.
enum TAknTreeListIconFlags
    {
    EFlagColored, // Icon is color skinned.
    EFlagReloadable, // Parameters for reloading the icon are stored in class.
    EFlagBitmapsOwnedExternally
    };


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CAknTreeListIcon* CAknTreeListIcon::NewLC( TInt aIconId, const TAknsItemID& aId,
    const TDesC& aFilename, TInt aBitmapId, TInt aMaskId,
    TScaleMode aScaleMode )
    {
    CAknTreeListIcon* self = new ( ELeave ) CAknTreeListIcon( aIconId, aId,
        aBitmapId, aMaskId, aScaleMode );
    CleanupStack::PushL( self );
    self->ConstructL( aFilename );
    return self;
    }


// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CAknTreeListIcon* CAknTreeListIcon::NewLC( TInt aIconId, CFbsBitmap* aIcon,
    CFbsBitmap* aMask, TBool aTransferOwnership, TScaleMode aScaleMode )
    {
    CAknTreeListIcon* self = new ( ELeave ) CAknTreeListIcon( aIconId,
        aIcon, aMask, aTransferOwnership, aScaleMode );
    CleanupStack::PushL( self );
    return self;
    }


// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CAknTreeListIcon* CAknTreeListIcon::NewLC( TInt aIconId, const TAknsItemID& aId,
    const TAknsItemID& aColorId, TInt aColorIndex, const TDesC& aFilename,
    TInt aBitmapId, TInt aMaskId, TRgb aDefaultColor, TScaleMode aScaleMode )
    {
    CAknTreeListIcon* self = new ( ELeave ) CAknTreeListIcon( aIconId, aId,
        aColorId, aColorIndex, aBitmapId, aMaskId, aDefaultColor, aScaleMode );
    CleanupStack::PushL( self );
    self->ConstructL( aFilename );
    return self;
    }


// ---------------------------------------------------------------------------
// Destructor.
// ---------------------------------------------------------------------------
//
CAknTreeListIcon::~CAknTreeListIcon()
    {
    delete iFilename;

    if ( iFlags.IsClear( EFlagBitmapsOwnedExternally ) )
        {
        delete iBitmap;
        delete iMask;
        }

    iBitmap = NULL;
    iMask = NULL;
    }


// ---------------------------------------------------------------------------
// Compares given two tree list icons.
// ---------------------------------------------------------------------------
//
TInt CAknTreeListIcon::Compare( const CAknTreeListIcon& aFirst,
    const CAknTreeListIcon& aSecond )
    {
    TInt id = aFirst.Id();
    return CompareId( &id, aSecond );
    }


// ---------------------------------------------------------------------------
// Compares icon ID with the one in given tree list icons.
// ---------------------------------------------------------------------------
//
TInt CAknTreeListIcon::CompareId( const TInt* aIconId,
    const CAknTreeListIcon& aIcon )
    {
    TInt value = NULL;
    TInt id1 = *aIconId;
    TInt id2 = aIcon.Id();

    if ( id1 < id2 )
        {
        value = -1;
        }
    else if ( id1 > id2 )
        {
        value = 1;
        }

    return value;
    }


// ---------------------------------------------------------------------------
// Reconstructs the bitmap and mask for the icon.
// ---------------------------------------------------------------------------
//
void CAknTreeListIcon::ReconstructL()
    {
    if ( iFlags.IsSet( EFlagReloadable ) )
        {
        CFbsBitmap* bitmap = NULL;
        CFbsBitmap* mask = NULL;

        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        if ( iFlags.IsSet( EFlagColored ) )
            {
            AknsUtils::CreateColorIconL( skin, iId, iColorId, iColorIndex,
                bitmap, mask, *iFilename, iBitmapId, iMaskId, iDefaultColor,
                iSize, iScaleMode );
            }
        else
            {
            AknsUtils::CreateIconL( skin, iId, bitmap, mask, *iFilename,
                iBitmapId, iMaskId );
            AknIconUtils::SetSize( bitmap, iSize, iScaleMode );
            }

        delete iBitmap;
        iBitmap = bitmap;

        delete iMask;
        iMask = mask;
        }
    }


// ---------------------------------------------------------------------------
// Returns the ID assigned for the tree list icon.
// ---------------------------------------------------------------------------
//
TInt CAknTreeListIcon::Id() const
    {
    return iIconId;
    }


// ---------------------------------------------------------------------------
// Returns the icon's skin item ID.
// ---------------------------------------------------------------------------
//
const TAknsItemID& CAknTreeListIcon::SkinItemID() const
    {
    return iId;
    }


// ---------------------------------------------------------------------------
// Returns pointer to the bitmap.
// ---------------------------------------------------------------------------
//
CFbsBitmap* CAknTreeListIcon::Bitmap()
    {
    return iBitmap;
    }


// ---------------------------------------------------------------------------
// Returns pointer to the mask.
// ---------------------------------------------------------------------------
//
CFbsBitmap* CAknTreeListIcon::Mask()
    {
    return iMask;
    }


// ---------------------------------------------------------------------------
// Returns the icon's size.
// ---------------------------------------------------------------------------
//
TSize CAknTreeListIcon::Size() const
    {
    return iSize;
    }


// ---------------------------------------------------------------------------
// Returns the icon's scale mode.
// ---------------------------------------------------------------------------
//
TScaleMode CAknTreeListIcon::ScaleMode() const
    {
    return iScaleMode;
    }


// ---------------------------------------------------------------------------
// Sets new icon size and scale mode.
// ---------------------------------------------------------------------------
//
TInt CAknTreeListIcon::SetSize( const TSize& aSize )
    {
    TInt error = KErrNone;
    if ( iSize != aSize )
        {
        iSize = aSize;
        error = AknIconUtils::SetSize( iBitmap, iSize, iScaleMode );
        }
    return error;
    }


// ---------------------------------------------------------------------------
// C++ constructor.
// ---------------------------------------------------------------------------
//
CAknTreeListIcon::CAknTreeListIcon( TInt aIconId, const TAknsItemID& aId,
    TInt aBitmapId, TInt aMaskId, TScaleMode aScaleMode )
    : iIconId( aIconId ),
      iId( aId ),
      iBitmapId( aBitmapId ),
      iMaskId( aMaskId ),
      iScaleMode( aScaleMode )
    {
    iFlags.Set( EFlagReloadable );
    }


// ---------------------------------------------------------------------------
// C++ constructor.
// ---------------------------------------------------------------------------
//
CAknTreeListIcon::CAknTreeListIcon( TInt aIconId, CFbsBitmap* aIcon,
    CFbsBitmap* aMask, TBool aTransferOwnership, TScaleMode aScaleMode )
    : iIconId( aIconId ),
      iId( KAknsIIDNone ),
      iBitmap( aIcon ),
      iMask( aMask ),
      iScaleMode( aScaleMode )
    {
    iFlags.Assign( EFlagBitmapsOwnedExternally, !aTransferOwnership );
    }


// ---------------------------------------------------------------------------
// C++ constructor.
// ---------------------------------------------------------------------------
//
CAknTreeListIcon::CAknTreeListIcon( TInt aIconId, const TAknsItemID& aId,
    const TAknsItemID& aColorId, TInt aColorIndex, TInt aBitmapId,
    TInt aMaskId, TRgb aDefaultColor, TScaleMode aScaleMode )
    : iIconId( aIconId ),
      iId( aId ),
      iColorId( aColorId ),
      iColorIndex( aColorIndex ),
      iBitmapId( aBitmapId ),
      iMaskId( aMaskId ),
      iDefaultColor( aDefaultColor ),
      iScaleMode( aScaleMode )
    {
    iFlags.Set( EFlagReloadable );
    iFlags.Set( EFlagColored );
    }


// ---------------------------------------------------------------------------
// Second phase constructor.
// ---------------------------------------------------------------------------
//
void CAknTreeListIcon::ConstructL( const TDesC& aFilename )
    {
    iFilename = aFilename.AllocL();
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    if ( iFlags.IsSet( EFlagColored ) )
        {
        AknsUtils::CreateColorIconL( skin, iId, iColorId, iColorIndex,
            iBitmap, iMask, *iFilename, iBitmapId, iMaskId, iDefaultColor );
        }
    else
        {
        AknsUtils::CreateIconL( skin, iId, iBitmap, iMask, *iFilename,
            iBitmapId, iMaskId );
        }
    }

