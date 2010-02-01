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
* Description:     
*
*/


#include <ganes/HgVgItem.h>
#include <gulicon.h>

#include "HgVgHelper.h"

// -----------------------------------------------------------------------------
// CHgVgItem::NewL()
// -----------------------------------------------------------------------------
//
EXPORT_C CHgVgItem* CHgVgItem::NewL(
        TInt aFlags,
        CGulIcon* aIcon,
        const TDesC& aTitle,
        const TDesC& aText )
    {
    CHgVgItem* self = CHgVgItem::NewLC( aFlags, aIcon, aTitle, aText );
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CHgVgItem::NewL()
// -----------------------------------------------------------------------------
//
EXPORT_C CHgVgItem* CHgVgItem::NewLC(
        TInt aFlags,
        CGulIcon* aIcon,
        const TDesC& aTitle,
        const TDesC& aText )
    {
    CHgVgItem* self = new (ELeave) CHgVgItem( aFlags, aIcon );
    CleanupStack::PushL( self );
    self->ConstructL( aTitle, aText );
    return self;
    }

// -----------------------------------------------------------------------------
// CHgVgItem::~CHgVgItem()
// -----------------------------------------------------------------------------
//
EXPORT_C CHgVgItem::~CHgVgItem()
    {
    FreeOpenVgImage();    
    }

// -----------------------------------------------------------------------------
// CHgVgItem::SetIcon()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgVgItem::SetIcon( CGulIcon* aIcon, TInt aFlags )
    {
    CHgItem::SetIcon(aIcon, aFlags);    
    ReloadOpenVgImage();
    }


// -----------------------------------------------------------------------------
// CHgVgItem::CHgVgItem()
// -----------------------------------------------------------------------------
//
CHgVgItem::CHgVgItem( TInt aFlags, CGulIcon* aIcon ) : CHgItem(aFlags, aIcon),
    iVgImage( VG_INVALID_HANDLE )
    {
    ReloadOpenVgImage();
    }

// -----------------------------------------------------------------------------
// CHgVgItem::ConstructL()
// -----------------------------------------------------------------------------
//
void CHgVgItem::ConstructL( const TDesC& aTitle, const TDesC& aText )
    {
    CHgItem::ConstructL(aTitle, aText);
    }

// -----------------------------------------------------------------------------
// CHgVgItem::VgImage()
// -----------------------------------------------------------------------------
//
VGImage CHgVgItem::VgImage() const
    {
    return iVgImage;
    }

// -----------------------------------------------------------------------------
// CHgVgItem::ReloadOpenVgImage()
// -----------------------------------------------------------------------------
//
void CHgVgItem::ReloadOpenVgImage()
    {
    FreeOpenVgImage();
    if( iIcon )
        {
        TRAP_IGNORE( iVgImage = HgVgHelper::CreateVgImageFromIconL(*iIcon); )
        }
   }

// -----------------------------------------------------------------------------
// CHgVgItem::FreeOpenVgImage()
// -----------------------------------------------------------------------------
//
void CHgVgItem::FreeOpenVgImage()
    {
    if (iVgImage != VG_INVALID_HANDLE)
        {
        vgDestroyImage(iVgImage);
        iVgImage = VG_INVALID_HANDLE;
        }
    }

// End of File
