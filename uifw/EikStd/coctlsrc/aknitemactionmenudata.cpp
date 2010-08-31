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
* Description: Item action menu data.
*
*/

#include <aknstyluspopupmenu.h>
#include <badesca.h>
#include <eikpanic.h>

#include "aknitemactionmenudata.h"

// ---------------------------------------------------------------------------
// CAknItemActionMenuData::NewL
// ---------------------------------------------------------------------------
//
CAknItemActionMenuData* CAknItemActionMenuData::NewL()
    {
    CAknItemActionMenuData* self = new ( ELeave ) CAknItemActionMenuData();
    return self;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenuData::~CAknItemActionMenuData
// ---------------------------------------------------------------------------
//
CAknItemActionMenuData::~CAknItemActionMenuData()
    {
    iMenuData.Close();
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenuData::AddMenuItemToDataArrayL
// ---------------------------------------------------------------------------
//
void CAknItemActionMenuData::AddMenuItemToDataArrayL(
        TInt aCommandId, TInt aCascadeId, const TDesC& aText )
    {
    TAknItemActionMenuData newData;
    newData.iCommandId = aCommandId;
    newData.iCascadeId = aCascadeId;
    newData.iText = aText;
    iMenuData.AppendL( newData );
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenuData::AddMenuItemsToStylusPopupMenuL
// ---------------------------------------------------------------------------
//
void CAknItemActionMenuData::AddMenuItemsToStylusPopupMenuL(
        CAknStylusPopUpMenu* aPopupMenu )
    {
    if ( aPopupMenu )
        {
        for ( TInt i = 0; i < iMenuData.Count(); i++ )
            {
            aPopupMenu->AddMenuItemL( iMenuData[ i ].iText, i + 1 );
            }
        }
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenuData::MenuItemsForQueryDialogL
// ---------------------------------------------------------------------------
//
MDesCArray* CAknItemActionMenuData::MenuItemsForQueryDialogL()
    {
    CDesCArrayFlat* itemArray( NULL );
    TInt itemCount( iMenuData.Count() );
    if ( itemCount )
        {
        itemArray =
            new ( ELeave ) CDesCArrayFlat( itemCount );
        CleanupStack::PushL( itemArray );
        for ( TInt i = 0; i < itemCount; i++ )
            {
            itemArray->AppendL( iMenuData[ i ].iText );
            }
        CleanupStack::Pop( itemArray );
        }
    return itemArray;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenuData::MenuItemCascadeId
// ---------------------------------------------------------------------------
//
TInt CAknItemActionMenuData::MenuItemCascadeId( TInt aIndex )
    {
    aIndex--;
    __ASSERT_ALWAYS(
            ( aIndex >= 0 && aIndex < iMenuData.Count() ),
            Panic( EEikPanicOutOfRange ) );
    return iMenuData[ aIndex ].iCascadeId;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenuData::MenuItemText
// ---------------------------------------------------------------------------
//
TDesC& CAknItemActionMenuData::MenuItemText( TInt aIndex )
    {
    aIndex--;
    __ASSERT_ALWAYS(
            ( aIndex >= 0 && aIndex < iMenuData.Count() ),
            Panic( EEikPanicOutOfRange ) );
    return iMenuData[ aIndex ].iText;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenuData::MenuItemCommandId
// ---------------------------------------------------------------------------
//
TInt CAknItemActionMenuData::MenuItemCommandId( TInt aIndex  )
    {
    aIndex--;
    __ASSERT_ALWAYS(
            ( aIndex >= 0 && aIndex < iMenuData.Count() ),
            Panic( EEikPanicOutOfRange ) );
    return iMenuData[ aIndex ].iCommandId;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenuData::Reset
// ---------------------------------------------------------------------------
//
void CAknItemActionMenuData::Reset()
    {
    iMenuData.Reset();
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenuData::Count
// ---------------------------------------------------------------------------
//
TInt CAknItemActionMenuData::Count() const
    {
    return iMenuData.Count();
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenuData::CAknItemActionMenuData
// ---------------------------------------------------------------------------
//
CAknItemActionMenuData::CAknItemActionMenuData()
    {
    }

// End of File
