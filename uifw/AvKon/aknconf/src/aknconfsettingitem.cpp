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


// INCLUDE FILES
#include "aknconfsettingitem.h"
#include "aknconfsettinglist.h"

// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// CAknConfSettingItem::CAknConfSettingItem()
// -----------------------------------------------------------------------------
//
CAknConfSettingItem::CAknConfSettingItem( CAknConfSettingList* aList,
                                          TInt& aValue,
                                          const TInt& aId,
                                          const TInt& aCenRepKey )
    : CAknIntegerEdwinSettingItem( aId, aValue ),
      iList( aList ),
      iValue( &aValue ),
      iCenRepKey( aCenRepKey )
    {
    }


// -----------------------------------------------------------------------------
// CAknConfSettingItem::~CAknConfSettingItem()
// -----------------------------------------------------------------------------
//
CAknConfSettingItem::~CAknConfSettingItem()
    {
    }


// -----------------------------------------------------------------------------
// CAknConfSettingItem::HandleSettingPageEventL()
// -----------------------------------------------------------------------------
//
void CAknConfSettingItem::HandleSettingPageEventL(
    CAknSettingPage *aSettingPage, TAknSettingPageEvent aEventType)
    {
    CAknIntegerEdwinSettingItem::HandleSettingPageEventL( aSettingPage,
                                                          aEventType );
    TBool okPressed( aEventType == EEventSettingOked );
    if ( aEventType == EEventSettingCancelled
        || aEventType == EEventSettingOked && iList )
        {
        StoreL();
        iList->SettingPageClosed( okPressed,
                                  *iValue,
                                  iCenRepKey );
        }
    }

// -----------------------------------------------------------------------------
// CAknConfBinarySettingItem::CAknConfBinarySettingItem()
// -----------------------------------------------------------------------------
//
CAknConfBinarySettingItem::CAknConfBinarySettingItem( CAknConfSettingList* aList,
                                                      TBool& aValue,
                                                      const TInt& aId,
                                                      const TInt& aCenRepKey )
    : CAknBinaryPopupSettingItem( aId, aValue ),
      iList( aList ),
      iValue( &aValue ),
      iCenRepKey( aCenRepKey )
    {
    }


// -----------------------------------------------------------------------------
// CAknConfBinarySettingItem::~CAknConfBinarySettingItem()
// -----------------------------------------------------------------------------
//
CAknConfBinarySettingItem::~CAknConfBinarySettingItem()
    {
    }


// -----------------------------------------------------------------------------
// CAknConfBinarySettingItem::EditItemL()
// -----------------------------------------------------------------------------
//
void CAknConfBinarySettingItem::EditItemL( TBool aCalledFromMenu )
    {
    CAknBinaryPopupSettingItem::EditItemL( aCalledFromMenu );
    
    // Value has been toggled, send event to list
    if ( !aCalledFromMenu )
        {
        StoreL();
        iList->SettingPageClosed( ETrue,
                                  *iValue,
                                  iCenRepKey );
        }
    }


// -----------------------------------------------------------------------------
// CAknConfBinarySettingItem::HandleSettingPageEventL()
// -----------------------------------------------------------------------------
//
void CAknConfBinarySettingItem::HandleSettingPageEventL(
    CAknSettingPage *aSettingPage, TAknSettingPageEvent aEventType)
    {
    CAknBinaryPopupSettingItem::HandleSettingPageEventL( aSettingPage,
                                                          aEventType );
    TBool okPressed( aEventType == EEventSettingOked );
    if ( aEventType == EEventSettingCancelled
        || aEventType == EEventSettingOked && iList )
        {
        StoreL();
        iList->SettingPageClosed( okPressed,
                                  *iValue,
                                  iCenRepKey );
        }
    }


// -----------------------------------------------------------------------------
// CAknConfSliderSettingItem::CAknConfSliderSettingItem()
// -----------------------------------------------------------------------------
//
CAknConfSliderSettingItem::CAknConfSliderSettingItem( 
    CAknConfSettingList* aList, TInt& aValue, const TInt& aId, 
    const TInt& aCenRepKey )
    : CAknSliderSettingItem( aId, aValue ),
      iList( aList ),
      iValue( &aValue ),
      iCenRepKey( aCenRepKey )
    {
    }


// -----------------------------------------------------------------------------
// CAknConfSliderSettingItem::~CAknConfSliderSettingItem()
// -----------------------------------------------------------------------------
//
CAknConfSliderSettingItem::~CAknConfSliderSettingItem()
    {
    }


// -----------------------------------------------------------------------------
// CAknConfSliderSettingItem::HandleSettingPageEventL()
// -----------------------------------------------------------------------------
//
void CAknConfSliderSettingItem::HandleSettingPageEventL(
    CAknSettingPage *aSettingPage, TAknSettingPageEvent aEventType)
    {
    CAknSliderSettingItem::HandleSettingPageEventL( aSettingPage,
                                                    aEventType );
    TBool okPressed( aEventType == EEventSettingOked );
    if ( aEventType == EEventSettingCancelled
        || aEventType == EEventSettingOked && iList )
        {
        StoreL();
        iList->SettingPageClosed( okPressed,
                                  *iValue,
                                  iCenRepKey );
        }
    }
