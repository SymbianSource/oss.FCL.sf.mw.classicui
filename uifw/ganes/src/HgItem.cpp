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


#include <ganes/HgItem.h>
#include <gulicon.h>

// -----------------------------------------------------------------------------
// CHgItem::NewL()
// -----------------------------------------------------------------------------
//
EXPORT_C CHgItem* CHgItem::NewL(
        TInt aFlags,
        CGulIcon* aIcon,
        const TDesC& aTitle,
        const TDesC& aText )
    {
    CHgItem* self = CHgItem::NewLC( aFlags, aIcon, aTitle, aText );
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CHgItem::NewL()
// -----------------------------------------------------------------------------
//
EXPORT_C CHgItem* CHgItem::NewLC(
        TInt aFlags,
        CGulIcon* aIcon,
        const TDesC& aTitle,
        const TDesC& aText )
    {
    CHgItem* self = new (ELeave) CHgItem( aFlags, aIcon );
    CleanupStack::PushL( self );
    self->ConstructL( aTitle, aText );
    return self;
    }

// -----------------------------------------------------------------------------
// CHgItem::~CHgItem()
// -----------------------------------------------------------------------------
//
EXPORT_C CHgItem::~CHgItem()
    {    
    delete iIcon;
    delete iTitle;
    delete iText;
    }

// -----------------------------------------------------------------------------
// CHgItem::CHgItem()
// -----------------------------------------------------------------------------
//
CHgItem::CHgItem( TInt aFlags, CGulIcon* aIcon ) :
    iIcon( aIcon ),
    iFlags( aFlags )
    {
    iTime.HomeTime();
    }

// -----------------------------------------------------------------------------
// CHgItem::ConstructL()
// -----------------------------------------------------------------------------
//
void CHgItem::ConstructL( const TDesC& aTitle, const TDesC& aText )
    {
    iTitle = aTitle.AllocL();
    iText = aText.AllocL();
    }

// -----------------------------------------------------------------------------
// CHgItem::Icon()
// -----------------------------------------------------------------------------
//
EXPORT_C CGulIcon* CHgItem::Icon() const
    {
    return iIcon;
    }

// -----------------------------------------------------------------------------
// CHgItem::Title()
// -----------------------------------------------------------------------------
//
EXPORT_C const TDesC& CHgItem::Title() const
    {
    return *iTitle;
    }

// -----------------------------------------------------------------------------
// CHgItem::Text()
// -----------------------------------------------------------------------------
//
EXPORT_C const TDesC& CHgItem::Text() const
    {
    return *iText;
    }

// -----------------------------------------------------------------------------
// CHgItem::Time()
// -----------------------------------------------------------------------------
//
EXPORT_C TTime CHgItem::Time() const
    {
    return iTime;
    }

// -----------------------------------------------------------------------------
// CHgItem::SetIcon()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgItem::SetIcon( CGulIcon* aIcon, TInt aFlags )
    {
    delete iIcon;        
    iIcon = aIcon;
    SetFlags( aFlags );
    }

// -----------------------------------------------------------------------------
// CHgItem::SetTitleL()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgItem::SetTitleL( const TDesC& aTitle )
    {
    delete iTitle;
    iTitle = 0;
    iTitle = aTitle.AllocL();
    }

// -----------------------------------------------------------------------------
// CHgItem::SetTextL()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgItem::SetTextL( const TDesC& aText )
    {
    delete iText;
    iText = 0;
    iText = aText.AllocL();
    }

// -----------------------------------------------------------------------------
// CHgItem::SetTime()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgItem::SetTime( TTime aTime )
    {
    iTime = aTime;
    }

// -----------------------------------------------------------------------------
// CHgItem::SetTextL()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgItem::SetFlags( TInt aFlags )
    {
    iFlags |= aFlags;
    }

// -----------------------------------------------------------------------------
// CHgItem::SetTextL()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgItem::ClearFlags( TInt aFlags )
    {
    iFlags &= ~aFlags;
    }

// -----------------------------------------------------------------------------
// CHgItem::SetTextL()
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CHgItem::Flags()
    {
    return iFlags;
    }

// End of file
