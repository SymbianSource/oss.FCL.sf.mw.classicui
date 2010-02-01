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
* Description:  container
*
*/


#include "bctestdommix50container.h"

#define KAknAtListGray TRgb( 0xaaaaaa )


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CBCTestDomMix50Container::CBCTestDomMix50Container()
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomMix50Container::CBCTestDomMix50Container()
    {
    }


// ---------------------------------------------------------------------------
// CBCTestDomMix50Container::~CBCTestDomMix50Container()
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDomMix50Container::~CBCTestDomMix50Container()
    {
    ResetControl();
    }


// ---------------------------------------------------------------------------
// CBCTestDomMix50Container::ConstructL()
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomMix50Container::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    ActivateL();
    }


// ---------------------------------------------------------------------------
// CBCTestDomMix50Container::Draw()
// Fills the window's rectangle
// ---------------------------------------------------------------------------
//
void CBCTestDomMix50Container::Draw( const TRect& aRect ) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KAknAtListGray );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }


// ---------------------------------------------------------------------------
// CBCTestDomMix50Container::CountComponentControls()
// 
// ---------------------------------------------------------------------------
//
TInt CBCTestDomMix50Container::CountComponentControls() const
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
// CBCTestDomMix50Container::ComponentControl()
// 
// ---------------------------------------------------------------------------
//
CCoeControl* CBCTestDomMix50Container::ComponentControl( TInt ) const
    {
    return iControl;
    }


// ---------------------------------------------------------------------------
// CBCTestDomMix50Container::SetControl()
// 
// ---------------------------------------------------------------------------
//
void CBCTestDomMix50Container::SetControlL( CCoeControl* aControl )
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
// CBCTestDomMix50Container::ResetControl()
// 
// ---------------------------------------------------------------------------
//
void CBCTestDomMix50Container::ResetControl()
    {
    delete iControl;
    iControl = NULL;
    }
