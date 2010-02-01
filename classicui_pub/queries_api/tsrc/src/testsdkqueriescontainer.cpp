/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Test queries_api
*
*/

//INCLUDE
#include "testsdkqueriescontainer.h"

// -----------------------------------------------------------------------------
// CTestSDKQueriesContainer::CTestSDKQueriesContainer
// -----------------------------------------------------------------------------
//
CTestSDKQueriesContainer::CTestSDKQueriesContainer( )
    {
    // No implementation required
    }

// -----------------------------------------------------------------------------
// CTestSDKQueriesContainer::~CTestSDKQueriesContainer
// -----------------------------------------------------------------------------
//
CTestSDKQueriesContainer::~CTestSDKQueriesContainer( )
    {
    }

// -----------------------------------------------------------------------------
// CTestSDKQueriesContainer::NewLC
// -----------------------------------------------------------------------------
//
CTestSDKQueriesContainer* CTestSDKQueriesContainer::NewLC(
    const TRect& aRect, const CCoeControl* aParent )
    {
    CTestSDKQueriesContainer* self = new (ELeave)CTestSDKQueriesContainer();
    CleanupStack::PushL( self );
    self->ConstructL( aRect, aParent );
    return self;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueriesContainer::NewL
// -----------------------------------------------------------------------------
//
CTestSDKQueriesContainer* CTestSDKQueriesContainer::NewL(
    const TRect& aRect, const CCoeControl* aParent )
    {
    CTestSDKQueriesContainer* self=CTestSDKQueriesContainer::NewLC( aRect,
        aParent );
    CleanupStack::Pop( ); // self;
    return self;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueriesContainer::ConstructL
// -----------------------------------------------------------------------------
//
void CTestSDKQueriesContainer::ConstructL( const TRect& aRect,
    const CCoeControl* aParent )
    {
    if ( aParent == NULL )
        {
        CreateWindowL( );
        }
    else
        {
        SetContainerWindowL( *aParent );
        }

    SetRect( aRect );
    ActivateL( );
    }

// -----------------------------------------------------------------------------
// CTestSDKQueriesContainer::CountComponentControls
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueriesContainer::CountComponentControls( ) const
    {
    return ( int ) ELastControl;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueriesContainer::ComponentControl
// -----------------------------------------------------------------------------
//
CCoeControl* CTestSDKQueriesContainer::ComponentControl( TInt aIndex ) const
    {
    switch ( aIndex )
        {
        }

    return NULL;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueriesContainer::OfferKeyEventL
// -----------------------------------------------------------------------------
//
TKeyResponse CTestSDKQueriesContainer::OfferKeyEventL(
    const TKeyEvent& aKeyEvent, TEventCode aType )
    {
    return CCoeControl::OfferKeyEventL( aKeyEvent, aType );
    }

// -----------------------------------------------------------------------------
// CTestSDKQueriesContainer::HandleResourceChange
// -----------------------------------------------------------------------------
//
void CTestSDKQueriesContainer::HandleResourceChange( TInt aType )
    {
    CCoeControl::HandleResourceChange( aType );
    }

// -----------------------------------------------------------------------------
// CTestSDKQueriesContainer::SizeChanged
// -----------------------------------------------------------------------------
//
void CTestSDKQueriesContainer::SizeChanged( )
    {
    CCoeControl::SizeChanged( );
    }


// -----------------------------------------------------------------------------
// CTestSDKQueriesContainer::Draw
// -----------------------------------------------------------------------------
//
void CTestSDKQueriesContainer::Draw( const TRect& aRect ) const
    {
    CWindowGc& gc = SystemGc( );
    gc.Clear( aRect );
    }


// -----------------------------------------------------------------------------
// CTestSDKQueriesContainer::ActivateGc
// -----------------------------------------------------------------------------
//
void CTestSDKQueriesContainer::ActivateGc() const
    {
    CCoeControl::ActivateGc();
    }

// -----------------------------------------------------------------------------
// CTestSDKQueriesContainer::DeactivateGc
// -----------------------------------------------------------------------------
//
void CTestSDKQueriesContainer::DeactivateGc() const
    {
    CCoeControl::DeactivateGc();
    }

//End file



