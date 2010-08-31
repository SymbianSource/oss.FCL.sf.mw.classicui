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









#include "bctestmisc32container.h"

#define KAknAtListGray TRgb(0xaaaaaa)

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestmisc32Container::CBCTestmisc32Container()
    {    
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestmisc32Container::~CBCTestmisc32Container()
    {
    ResetControl();   
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestmisc32Container::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    ActivateL();
    }

// ----------------------------------------------------------------------------
// CBCTestmisc32Container::Draw
// Fills the window's rectangle.
// ----------------------------------------------------------------------------
//
void CBCTestmisc32Container::Draw( const TRect& aRect ) const
    {    
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KAknAtListGray );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// ---------------------------------------------------------------------------
// CBCTestmisc32Container::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CBCTestmisc32Container::CountComponentControls() const
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
// CBCTestmisc32Container::ComponentControl
// ---------------------------------------------------------------------------
//
CCoeControl* CBCTestmisc32Container::ComponentControl( TInt ) const
    {
    return iControl;
    }
    
// ---------------------------------------------------------------------------
// CBCTestmisc32Container::SetControl
// ---------------------------------------------------------------------------
//
void CBCTestmisc32Container::SetControl( CCoeControl* aControl )
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
// CBCTestmisc32Container::ResetControl
// ---------------------------------------------------------------------------
//
void CBCTestmisc32Container::ResetControl()
    {
    delete iControl;
    iControl = NULL;        
    }
