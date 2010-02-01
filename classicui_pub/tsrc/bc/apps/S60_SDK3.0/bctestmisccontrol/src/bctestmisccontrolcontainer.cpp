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
* Description:         Implements test bc for misc control container.
*
*/









#include "bctestmisccontrolcontainer.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestMiscControlContainer::CBCTestMiscControlContainer()
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestMiscControlContainer::~CBCTestMiscControlContainer()
    {
    ResetControl();
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestMiscControlContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    ActivateL();
    }

// ----------------------------------------------------------------------------
// CBCTestMiscControlContainer::Draw
// Fills the window's rectangle.
// ----------------------------------------------------------------------------
//
void CBCTestMiscControlContainer::Draw( const TRect& aRect ) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KRgbGray );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// ---------------------------------------------------------------------------
// CBCTestMiscControlContainer::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CBCTestMiscControlContainer::CountComponentControls() const
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
// CBCTestMiscControlContainer::ComponentControl
// ---------------------------------------------------------------------------
//
CCoeControl* CBCTestMiscControlContainer::ComponentControl( TInt ) const
    {
    return iControl;
    }

// ---------------------------------------------------------------------------
// CBCTestMiscControlContainer::SetControlL
// ---------------------------------------------------------------------------
//
void CBCTestMiscControlContainer::SetControlL( CCoeControl* aControl )
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
// CBCTestMiscControlContainer::ResetControl
// ---------------------------------------------------------------------------
//
void CBCTestMiscControlContainer::ResetControl()
    {
    delete iControl;
    iControl = NULL;
    }
        
// ---------------------------------------------------------------------------
// CBCTestMiscControlContainer::GetCoeEnv
// ---------------------------------------------------------------------------
//
CCoeEnv* CBCTestMiscControlContainer::GetCoeEnv() 
    {
    return iCoeEnv;
    }
