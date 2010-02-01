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


#include "bctestmixmclcontainer.h"

#define KAknAtListGray TRgb( 0xaaaaaa )


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CBCTestMixMCLContainer::CBCTestMixMCLContainer()
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestMixMCLContainer::CBCTestMixMCLContainer()
    {
    }


// ---------------------------------------------------------------------------
// CBCTestMixMCLContainer::~CBCTestMixMCLContainer()
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestMixMCLContainer::~CBCTestMixMCLContainer()
    {
    ResetControl();
    }


// ---------------------------------------------------------------------------
// CBCTestMixMCLContainer::ConstructL()
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestMixMCLContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    ActivateL();
    }


// ---------------------------------------------------------------------------
// CBCTestMixMCLContainer::Draw()
// Fills the window's rectangle
// ---------------------------------------------------------------------------
//
void CBCTestMixMCLContainer::Draw( const TRect& aRect ) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KAknAtListGray );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }


// ---------------------------------------------------------------------------
// CBCTestMixMCLContainer::CountComponentControls()
// 
// ---------------------------------------------------------------------------
//
TInt CBCTestMixMCLContainer::CountComponentControls() const
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
// CBCTestMixMCLContainer::ComponentControl()
// 
// ---------------------------------------------------------------------------
//
CCoeControl* CBCTestMixMCLContainer::ComponentControl( TInt ) const
    {
    return iControl;
    }


// ---------------------------------------------------------------------------
// CBCTestMixMCLContainer::SetControl()
// 
// ---------------------------------------------------------------------------
//
void CBCTestMixMCLContainer::SetControlL( CCoeControl* aControl )
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
// CBCTestMixMCLContainer::ResetControl()
// 
// ---------------------------------------------------------------------------
//
void CBCTestMixMCLContainer::ResetControl()
    {
    delete iControl;
    iControl = NULL;
    }
