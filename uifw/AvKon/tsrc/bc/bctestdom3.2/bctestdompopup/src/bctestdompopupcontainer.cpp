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


#include "bctestdompopupcontainer.h"

#define KAknAtListGray TRgb( 0xaaaaaa )


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCDomainTestPopupContainer::CBCDomainTestPopupContainer()
    {    
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCDomainTestPopupContainer::~CBCDomainTestPopupContainer()
    {
    ResetControl();   
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCDomainTestPopupContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    ActivateL();
    }

// ---------------------------------------------------------------------------
// CBCDomainTestPopupContainer::Draw
// Fills the window's rectangle.
// ---------------------------------------------------------------------------
//
void CBCDomainTestPopupContainer::Draw( const TRect& aRect ) const
    {    
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KAknAtListGray );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// ---------------------------------------------------------------------------
// CBCDomainTestPopupContainer::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CBCDomainTestPopupContainer::CountComponentControls() const
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
// CBCDomainTestPopupContainer::ComponentControl
// ---------------------------------------------------------------------------
//
CCoeControl* CBCDomainTestPopupContainer::ComponentControl( TInt ) const
    {
    return iControl;
    }
    
// ---------------------------------------------------------------------------
// CBCDomainTestPopupContainer::SetControl
// ---------------------------------------------------------------------------
//
void CBCDomainTestPopupContainer::SetControl( CCoeControl* aControl )
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
// CBCDomainTestPopupContainer::ResetControl
// ---------------------------------------------------------------------------
//
void CBCDomainTestPopupContainer::ResetControl()
    {
    delete iControl;
    iControl = NULL;        
    }
