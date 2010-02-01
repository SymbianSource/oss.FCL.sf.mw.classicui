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









#include "bctestlocationcontainer.h"
#include <eikenv.h>

#define KAknAtListGray TRgb(0xaaaaaa)
#define MFNE1_POS   TPoint(10,35)

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestLocationContainer::CBCTestLocationContainer()
    {    
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestLocationContainer::~CBCTestLocationContainer()
    {    
    ResetControl();   
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestLocationContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();    
    SetRect(aRect);
    ActivateL();
    }

// ----------------------------------------------------------------------------
// CBCTestLocationContainer::Draw
// Fills the window's rectangle.
// ----------------------------------------------------------------------------
//
void CBCTestLocationContainer::Draw( const TRect& aRect ) const
    {    
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KAknAtListGray );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );    
    }

// ---------------------------------------------------------------------------
// CBCTestLocationContainer::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CBCTestLocationContainer::CountComponentControls() const
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
// CBCTestLocationContainer::ComponentControl
// ---------------------------------------------------------------------------
//
CCoeControl* CBCTestLocationContainer::ComponentControl( TInt ) const
    {
    return iControl;
    }
    
// ---------------------------------------------------------------------------
// CBCTestLocationContainer::SetControl
// ---------------------------------------------------------------------------
//
void CBCTestLocationContainer::SetControl( CCoeControl* aControl )
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
// CBCTestLocationContainer::ResetControl
// ---------------------------------------------------------------------------
//
void CBCTestLocationContainer::ResetControl()
    {
    delete iControl;
    iControl = NULL;        
    }
