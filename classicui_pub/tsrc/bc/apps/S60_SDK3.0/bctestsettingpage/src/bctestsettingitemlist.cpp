/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         test case
*
*/









#include "bctestsettingitemlist.h"

// -------------------------------
// CAknSettingItem
// -------------------------------
//
// public:

/**
* Default constructor.
*/
EXPORT_C CBCTestSettingItem::CBCTestSettingItem( TInt aIdentifier)
 : CAknSettingItem( aIdentifier )
    {
    }

EXPORT_C CBCTestSettingItem::~CBCTestSettingItem()
    {
    }

// ---------------------------------------
// CAknTextSettingItem
//
//----------------------------------------

EXPORT_C CBCTestTextSettingItem::CBCTestTextSettingItem( TInt aIdentifier, TDes& aText ):
    CAknTextSettingItem( aIdentifier, aText )
    {
    // iInternalTextPtr points to no buffer, so no allocation is done here
    }

EXPORT_C CBCTestTextSettingItem::~CBCTestTextSettingItem()
    {
    }



// ---------------------------------------
// CAknIntegerSettingItem
//
//----------------------------------------

EXPORT_C CBCTestIntegerSettingItem::CBCTestIntegerSettingItem( TInt aIdentifier, TInt& aValue ):
    CAknIntegerSettingItem(aIdentifier, aValue )
    {
    }

EXPORT_C CBCTestIntegerSettingItem::~CBCTestIntegerSettingItem()
    {
    }

void CBCTestIntegerSettingItem::EditItemL( TBool /*aCalledFromMenu */)
{
}

// ---------------------------------------
// CAknPasswordSettingItem
//
//----------------------------------------

EXPORT_C CBCTestPasswordSettingItem::CBCTestPasswordSettingItem( TInt aIdentifier, enum CAknPasswordSettingItem::TAknPasswordSettingItemMode aPasswordMode, TDes& aPassword ):
    CAknPasswordSettingItem( aIdentifier, aPasswordMode, aPassword )
    {
    }

// ---------------------------------------
// CAknVolumeSettingItem
//
//----------------------------------------

EXPORT_C CBCTestVolumeSettingItem::CBCTestVolumeSettingItem( TInt aIdentifier, TInt& aVolume ):
    CAknVolumeSettingItem(aIdentifier, aVolume )
    {
    }

// ---------------------------------------
// CAknSliderSettingItem
//
//----------------------------------------

EXPORT_C CBCTestSliderSettingItem::CBCTestSliderSettingItem( TInt aIdentifier, TInt& aSliderValue ):
    CAknSliderSettingItem( aIdentifier, aSliderValue )
    {
    }

//
// Implementation of CAknEnumeratedTextSettingItem
//
//


EXPORT_C CBCTestEnumeratedTextSettingItem::CBCTestEnumeratedTextSettingItem(
    TInt aIdentifier ):
    CAknEnumeratedTextSettingItem(aIdentifier)
    {
    }

EXPORT_C CBCTestEnumeratedTextSettingItem::~CBCTestEnumeratedTextSettingItem()
    {
    }

//
// Implementation of CAknEnumeratedTextPopupSettingItem
//


EXPORT_C CBCTestEnumeratedTextPopupSettingItem::CBCTestEnumeratedTextPopupSettingItem(
    TInt aIdentifier,
    TInt& aValue ):
    CAknEnumeratedTextPopupSettingItem( aIdentifier, aValue )
    {
    }

EXPORT_C CBCTestEnumeratedTextPopupSettingItem::~CBCTestEnumeratedTextPopupSettingItem()
    {
    }

// ==============================================================================
// CAknBinaryPopupSettingItem
// ==============================================================================


EXPORT_C CBCTestBinaryPopupSettingItem::CBCTestBinaryPopupSettingItem(
    TInt aIdentifier,
    TBool& aBinaryValue ):
    CAknBinaryPopupSettingItem(aIdentifier, aBinaryValue )
    {
    }


/**
* This constructor merely initializes the empty string descriptor required for formatting the
* listbox text
*
*/
EXPORT_C CBCTestBigSettingItemBase::CBCTestBigSettingItemBase( TInt aIdentifier ): CAknBigSettingItemBase( aIdentifier )
    {
    }

//========================================


EXPORT_C CBCTestSettingItemArray::CBCTestSettingItemArray(TInt aGranularity, TBool aIsNumbered, TInt aInitialOrdinal ) :
    CAknSettingItemArray( aGranularity, aIsNumbered, aInitialOrdinal )
    {
    }

EXPORT_C CBCTestSettingItemArray::~CBCTestSettingItemArray()
    {
    }

// -------------------------------
// CAknSettingItemList
// -------------------------------

EXPORT_C CBCTestSettingItemList::CBCTestSettingItemList()
    {
    }

EXPORT_C CBCTestSettingItemList::~CBCTestSettingItemList()
    {

    }


// End of File
