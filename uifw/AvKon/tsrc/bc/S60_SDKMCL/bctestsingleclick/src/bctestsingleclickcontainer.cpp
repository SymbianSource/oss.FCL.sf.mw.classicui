/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Container class of bctestsingleclick.
*
*/

#include "bctestsingleclickcontainer.h"

#define KAKNATLISTGRAY TRgb( 0xaaaaaa )


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTESTSingleClickContainer::CBCTESTSingleClickContainer()
    {    
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTESTSingleClickContainer::~CBCTESTSingleClickContainer()
    {
    ResetControl();   
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTESTSingleClickContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    ActivateL();
    }

// ---------------------------------------------------------------------------
// CBCTESTSingleClickContainer::Draw
// Fills the window's rectangle.
// ---------------------------------------------------------------------------
//
void CBCTESTSingleClickContainer::Draw( const TRect& aRect ) const
    {    
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KAKNATLISTGRAY );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// ---------------------------------------------------------------------------
// CBCTESTSingleClickContainer::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CBCTESTSingleClickContainer::CountComponentControls() const
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
// CBCTESTSingleClickContainer::ComponentControl
// ---------------------------------------------------------------------------
//
CCoeControl* CBCTESTSingleClickContainer::ComponentControl( TInt ) const
    {
    return iControl;
    }
    
// ---------------------------------------------------------------------------
// CBCTESTSingleClickContainer::SetControlL
// ---------------------------------------------------------------------------
//
void CBCTESTSingleClickContainer::SetControlL( CCoeControl* aControl )
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
// CBCTESTSingleClickContainer::ResetControl
// ---------------------------------------------------------------------------
//
void CBCTESTSingleClickContainer::ResetControl()
    {
    delete iControl;
    iControl = NULL;        
    }
