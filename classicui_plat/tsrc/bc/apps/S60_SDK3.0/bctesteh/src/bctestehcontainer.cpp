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









#include "bctestehcontainer.h"

// ======== MEMBER FUNCTIONS ========
 
// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestEHContainer::CBCTestEHContainer()
    {    
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestEHContainer::~CBCTestEHContainer()
    {
    ResetControl();   
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestEHContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    ActivateL();
    }

// ----------------------------------------------------------------------------
// CBCTestEHContainer::Draw
// Fills the window's rectangle.
// ----------------------------------------------------------------------------
//
void CBCTestEHContainer::Draw( const TRect& aRect ) const
    {    
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KRgbGray );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// ---------------------------------------------------------------------------
// CBCTestEHContainer::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CBCTestEHContainer::CountComponentControls() const
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
// CBCTestEHContainer::ComponentControl
// ---------------------------------------------------------------------------
//
CCoeControl* CBCTestEHContainer::ComponentControl( TInt ) const
    {
    return iControl;
    }
    
// ---------------------------------------------------------------------------
// CBCTestEHContainer::SetControl
// ---------------------------------------------------------------------------
//
void CBCTestEHContainer::SetControl( CCoeControl* aControl )
    {
    iControl = aControl;    
    if ( iControl )
        {  
        // You can change the position and size
        iControl->SetExtent( Rect().iTl, Rect().Size() );
        DrawNow();
        }    
    }
    
// ---------------------------------------------------------------------------
// CBCTestEHContainer::ResetControl
// ---------------------------------------------------------------------------
//
void CBCTestEHContainer::ResetControl()
    {
    delete iControl;
    iControl = NULL;        
    }
    
    
//end of file

