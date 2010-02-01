/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Utility class for passing data between touchpane and toolbar.
*
*/


#include <e32std.h>
#include <coecntrl.h>
#include "touchtoolbardata.h"

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
TInt CTouchToolbarData::SetData( const CCoeControl* aControl, 
                                 TRect aDemarcationRect,
                                 TBool aDemarcationRectSet )
    {
    CTouchToolbarData* self = new CTouchToolbarData;
    if ( !self )
        {
        return KErrNoMemory;
        }
    self->iDemarcationRect = aDemarcationRect;
    self->iDemarcationRectSet = aDemarcationRectSet;
    self->iBetweenRegisterAndBegin = EFalse;
    self->iSelectPressed = EFalse;

    // If there's already data stored for this key, remove and free it.
    TInt key = reinterpret_cast<TInt>( aControl );
    CTouchToolbarData* data = 
        reinterpret_cast<CTouchToolbarData*>( CAknTransitionUtils::GetData( key ) );
    if ( data )
        {
        CAknTransitionUtils::RemoveObserver( data, 0xffffffff );
        CAknTransitionUtils::RemoveData( key );
        delete data;
        }

    return CAknTransitionUtils::SetData( key, reinterpret_cast<TAny*>( self ) );
    }
    
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
CTouchToolbarData* CTouchToolbarData::GetData( const CCoeControl* aControl )
    {
    return ( CTouchToolbarData* )CAknTransitionUtils::GetData( 
                                        reinterpret_cast<TInt>( aControl ) ); 
    }
    
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
TRect& CTouchToolbarData::DemarcationRect()
    {
    return iDemarcationRect;
    }

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
TBool CTouchToolbarData::DemarcationRectSet() const
    {
    return iDemarcationRectSet;
    }
    
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
TBool CTouchToolbarData::BetweenRegisterAndBegin() const
    {
    return iBetweenRegisterAndBegin;
    }
    
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
TBool CTouchToolbarData::SelectPressed() const
    {
    return iSelectPressed;
    }
    
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
void CTouchToolbarData::SetBetweenRegisterAndBegin( TBool aBetweenRegisterAndBegin )
    {
    iBetweenRegisterAndBegin = aBetweenRegisterAndBegin;
    }
    
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
void CTouchToolbarData::SetSelectPressed( TBool aSelectPressed )
    {
    iSelectPressed = aSelectPressed;
    }

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
void CTouchToolbarData::SetFocusedItem( CCoeControl* aItem )
    {
    iFocusedItem = aItem;
    }

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
TInt CTouchToolbarData::AknTransitionCallback(TInt aEvent, TInt /* aState */, 
                                              const TDesC8* aParams)
    {
    if ( iFocusedItem )
        {
        // Show tooltip
        iFocusedItem->SetFocus( EFalse, ENoDrawNow );
        iFocusedItem->PrepareForFocusGainL();
        iFocusedItem->SetFocus( ETrue, EDrawNow );
        }
    const CCoeControl* control = reinterpret_cast<const CCoeControl*>( aParams );
    TInt key = reinterpret_cast<TInt>( aParams );

    GfxTransEffect::Deregister( control );
    
    CTouchToolbarData* data = 
        reinterpret_cast<CTouchToolbarData*>( CAknTransitionUtils::GetData( key ) );
    
    CAknTransitionUtils::RemoveObserver( this, aEvent );
    CAknTransitionUtils::RemoveData( key );
    delete data;
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
CTouchToolbarData::CTouchToolbarData() : iFocusedItem( NULL )
    {
    }
