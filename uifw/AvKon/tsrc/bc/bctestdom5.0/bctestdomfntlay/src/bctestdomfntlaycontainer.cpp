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


#include "bctestdomfntlaycontainer.h"

#define  KAKNATLISTGRAY  TRgb(0xaaaaaa)

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomFntlayContainer::CBCTestDomFntlayContainer()
    {    
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDomFntlayContainer::~CBCTestDomFntlayContainer()
    {
    ResetControl();   
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomFntlayContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    ActivateL();
    }

// ----------------------------------------------------------------------------
// CBCTestDomFntlayContainer::Draw
// Fills the window's rectangle.
// ----------------------------------------------------------------------------
//
void CBCTestDomFntlayContainer::Draw( const TRect& aRect ) const
    {    
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KAKNATLISTGRAY );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// ---------------------------------------------------------------------------
// CBCTestDomFntlayContainer::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CBCTestDomFntlayContainer::CountComponentControls() const
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
// CBCTestDomFntlayContainer::ComponentControl
// ---------------------------------------------------------------------------
//
CCoeControl* CBCTestDomFntlayContainer::ComponentControl( TInt ) const
    {
    return iControl;
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomFntlayContainer::SetControlL
// ---------------------------------------------------------------------------
//
void CBCTestDomFntlayContainer::SetControlL( CCoeControl* aControl )
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
// CBCTestDomFntlayContainer::ResetControl
// ---------------------------------------------------------------------------
//
void CBCTestDomFntlayContainer::ResetControl()
    {
    delete iControl;
    iControl = NULL;        
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomFntlayContainer::GetEnv
// ---------------------------------------------------------------------------
//
CCoeEnv* CBCTestDomFntlayContainer::GetEnv()
    {
    return iCoeEnv;    
    }
