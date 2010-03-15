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
#include "akntrace.h"

// ---------------------------------------------------------------------------
// CAknItemActionMenuData::NewL
// ---------------------------------------------------------------------------
//
CAknItemActionMenuData* CAknItemActionMenuData::NewL()
    {
    _AKNTRACE_FUNC_ENTER;
    CAknItemActionMenuData* self = new ( ELeave ) CAknItemActionMenuData();
    _AKNTRACE_FUNC_EXIT;
    return self;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenuData::~CAknItemActionMenuData
// ---------------------------------------------------------------------------
//
CAknItemActionMenuData::~CAknItemActionMenuData()
    {
    _AKNTRACE_FUNC_ENTER;
    iMenuData.Close();
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenuData::AddMenuItemToDataArrayL
// ---------------------------------------------------------------------------
//
void CAknItemActionMenuData::AddMenuItemToDataArrayL(
        TInt aCommandId, TInt aCascadeId, const TDesC& aText )
    {
    _AKNTRACE_FUNC_ENTER;
    TAknItemActionMenuData newData;
    newData.iCommandId = aCommandId;
    newData.iCascadeId = aCascadeId;
    newData.iText = aText;
    iMenuData.AppendL( newData );
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenuData::AddMenuItemsToStylusPopupMenuL
// ---------------------------------------------------------------------------
//
void CAknItemActionMenuData::AddMenuItemsToStylusPopupMenuL(
        CAknStylusPopUpMenu* aPopupMenu )
    {
    _AKNTRACE_FUNC_ENTER;
    if ( aPopupMenu )
        {
        for ( TInt i = 0; i < iMenuData.Count(); i++ )
            {
            aPopupMenu->AddMenuItemL( iMenuData[ i ].iText, i + 1 );
            }
        }
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenuData::MenuItemsForQueryDialogL
// ---------------------------------------------------------------------------
//
MDesCArray* CAknItemActionMenuData::MenuItemsForQueryDialogL()
    {
    _AKNTRACE_FUNC_ENTER;
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
    _AKNTRACE_FUNC_EXIT;
    return itemArray;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenuData::MenuItemCascadeId
// ---------------------------------------------------------------------------
//
TInt CAknItemActionMenuData::MenuItemCascadeId( TInt aIndex )
    {
    _AKNTRACE_FUNC_ENTER;
    aIndex--;
    __ASSERT_ALWAYS(
            ( aIndex >= 0 && aIndex < iMenuData.Count() ),
            Panic( EEikPanicOutOfRange ) );
    _AKNTRACE_FUNC_EXIT;
    return iMenuData[ aIndex ].iCascadeId;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenuData::MenuItemText
// ---------------------------------------------------------------------------
//
TDesC& CAknItemActionMenuData::MenuItemText( TInt aIndex )
    {
    _AKNTRACE_FUNC_ENTER;
    aIndex--;
    __ASSERT_ALWAYS(
            ( aIndex >= 0 && aIndex < iMenuData.Count() ),
            Panic( EEikPanicOutOfRange ) );
    _AKNTRACE_FUNC_EXIT;
    return iMenuData[ aIndex ].iText;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenuData::MenuItemCommandId
// ---------------------------------------------------------------------------
//
TInt CAknItemActionMenuData::MenuItemCommandId( TInt aIndex  )
    {
    _AKNTRACE_FUNC_ENTER;
    aIndex--;
    __ASSERT_ALWAYS(
            ( aIndex >= 0 && aIndex < iMenuData.Count() ),
            Panic( EEikPanicOutOfRange ) );
    _AKNTRACE_FUNC_EXIT;
    return iMenuData[ aIndex ].iCommandId;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenuData::Reset
// ---------------------------------------------------------------------------
//
void CAknItemActionMenuData::Reset()
    {
    _AKNTRACE_FUNC_ENTER;
    iMenuData.Reset();
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CAknItemActionMenuData::Count
// ---------------------------------------------------------------------------
//
TInt CAknItemActionMenuData::Count() const
    {
    _AKNTRACE_FUNC_ENTER;;
    _AKNTRACE_FUNC_EXIT;
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
