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









#include "bctestpanecontainer.h"
#include "bctestpanecase.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestPaneContainer::CBCTestPaneContainer()
    {    
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestPaneContainer::~CBCTestPaneContainer()
    {
    ResetControl();   
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestPaneContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    ActivateL();
    }

// ----------------------------------------------------------------------------
// CBCTestPaneContainer::Draw
// Fills the window's rectangle.
// ----------------------------------------------------------------------------
//
void CBCTestPaneContainer::Draw( const TRect& aRect ) const
    {    
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KRgbGray );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    
    if ( iPaneCase )
        {
        TRAP_IGNORE( iPaneCase->DrawCaseL( gc ) );
        }
    }

// ---------------------------------------------------------------------------
// CBCTestPaneContainer::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CBCTestPaneContainer::CountComponentControls() const
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
// CBCTestPaneContainer::ComponentControl
// ---------------------------------------------------------------------------
//
CCoeControl* CBCTestPaneContainer::ComponentControl( TInt ) const
    {
    return iControl;
    }
    
// ---------------------------------------------------------------------------
// CBCTestPaneContainer::SetControl
// ---------------------------------------------------------------------------
//
void CBCTestPaneContainer::SetControl( CCoeControl* aControl )
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
// CBCTestPaneContainer::ResetControl
// ---------------------------------------------------------------------------
//
void CBCTestPaneContainer::ResetControl()
    {
    delete iControl;
    iControl = NULL;        
    }

// ---------------------------------------------------------------------------
// CBCTestPaneContainer::SetPaneCase
// ---------------------------------------------------------------------------
//
void CBCTestPaneContainer::SetPaneCase( CBCTestPaneCase* aCase )
    {
    iPaneCase = aCase;
    DrawNow();    
    }
