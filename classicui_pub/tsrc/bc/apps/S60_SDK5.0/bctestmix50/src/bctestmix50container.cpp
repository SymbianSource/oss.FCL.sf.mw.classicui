/*
* Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies).
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









#include "bctestmix50container.h"

#define KAknAtListGray TRgb( 0xaaaaaa )


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CBCTestMix50Container::CBCTestMix50Container()
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestMix50Container::CBCTestMix50Container()
    {
    }


// ---------------------------------------------------------------------------
// CBCTestMix50Container::~CBCTestMix50Container()
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestMix50Container::~CBCTestMix50Container()
    {
    ResetControl();
    }


// ---------------------------------------------------------------------------
// CBCTestMix50Container::ConstructL()
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestMix50Container::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    ActivateL();
    }


// ---------------------------------------------------------------------------
// CBCTestMix50Container::Draw()
// Fills the window's rectangle
// ---------------------------------------------------------------------------
//
void CBCTestMix50Container::Draw( const TRect& aRect ) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KAknAtListGray );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }


// ---------------------------------------------------------------------------
// CBCTestMix50Container::CountComponentControls()
// 
// ---------------------------------------------------------------------------
//
TInt CBCTestMix50Container::CountComponentControls() const
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
// CBCTestMix50Container::ComponentControl()
// 
// ---------------------------------------------------------------------------
//
CCoeControl* CBCTestMix50Container::ComponentControl( TInt ) const
    {
    return iControl;
    }


// ---------------------------------------------------------------------------
// CBCTestMix50Container::SetControl()
// 
// ---------------------------------------------------------------------------
//
void CBCTestMix50Container::SetControlL( CCoeControl* aControl )
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
// CBCTestMix50Container::ResetControl()
// 
// ---------------------------------------------------------------------------
//
void CBCTestMix50Container::ResetControl()
    {
    delete iControl;
    iControl = NULL;
    }
