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


#include "BCExtendedFontApicontainer.h"

#define KAknAtListGray TRgb( 0xaaaaaa )


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCExtendedFontApiContainer::CBCExtendedFontApiContainer()
    {    
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCExtendedFontApiContainer::~CBCExtendedFontApiContainer()
    {
    ResetControl();   
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCExtendedFontApiContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    ActivateL();
    }

// ---------------------------------------------------------------------------
// CBCExtendedFontApiContainer::Draw
// Fills the window's rectangle.
// ---------------------------------------------------------------------------
//
void CBCExtendedFontApiContainer::Draw( const TRect& aRect ) const
    {    
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KAknAtListGray );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// ---------------------------------------------------------------------------
// CBCExtendedFontApiContainer::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CBCExtendedFontApiContainer::CountComponentControls() const
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
// CBCExtendedFontApiContainer::ComponentControl
// ---------------------------------------------------------------------------
//
CCoeControl* CBCExtendedFontApiContainer::ComponentControl( TInt ) const
    {
    return iControl;
    }
    
// ---------------------------------------------------------------------------
// CBCExtendedFontApiContainer::SetControl
// ---------------------------------------------------------------------------
//
void CBCExtendedFontApiContainer::SetControl( CCoeControl* aControl )
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
// CBCExtendedFontApiContainer::ResetControl
// ---------------------------------------------------------------------------
//
void CBCExtendedFontApiContainer::ResetControl()
    {
    delete iControl;
    iControl = NULL;        
    }
