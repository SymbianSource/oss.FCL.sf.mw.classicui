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
* Description:         container
*
*/









#include "bctestnotifiercontainer.h"

#define KAknAtListGray TRgb(0xaaaaaa)

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestNotifierContainer::CBCTestNotifierContainer()
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestNotifierContainer::~CBCTestNotifierContainer()
    {
    ResetControl();
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestNotifierContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    ActivateL();
    }

// ----------------------------------------------------------------------------
// CBCTestSettingPageContainer::Draw
// Fills the window's rectangle.
// ----------------------------------------------------------------------------
//
void CBCTestNotifierContainer::Draw( const TRect& aRect ) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KAknAtListGray );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// ---------------------------------------------------------------------------
// CBCTestSettingPageContainer::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CBCTestNotifierContainer::CountComponentControls() const
    {
    if ( iControl )
        {
        return 1;
        }
    else
        {
        return 0;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestSettingPageContainer::ComponentControl
// ---------------------------------------------------------------------------
//
CCoeControl* CBCTestNotifierContainer::ComponentControl( TInt ) const
    {
    return iControl;
    }

// ---------------------------------------------------------------------------
// CBCTestSettingPageContainer::SetControl
// ---------------------------------------------------------------------------
//
void CBCTestNotifierContainer::SetControl( CCoeControl* aControl )
    {
    iControl = aControl;
    if ( iControl )
        {
        // You can change the position and size
        iControl->SetExtent( Rect().iTl, Rect().Size() );
        iControl->ActivateL();
        DrawNow();
        }
    }

// ---------------------------------------------------------------------------
// CBCTestSettingPageContainer::ResetControl
// ---------------------------------------------------------------------------
//
void CBCTestNotifierContainer::ResetControl()
    {
    if ( iControl ) 
        {
        delete iControl;
        iControl = NULL;
        }
    }
