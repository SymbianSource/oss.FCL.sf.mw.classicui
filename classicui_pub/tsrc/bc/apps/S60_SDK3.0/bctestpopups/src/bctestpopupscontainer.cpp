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
* Description:         Implements test bc for popups control container.
*
*/









#include "bctestpopupscontainer.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestPopupsContainer::CBCTestPopupsContainer()
    { 
    } 

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestPopupsContainer::~CBCTestPopupsContainer()
    {
    ResetControl(); 
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestPopupsContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    ActivateL();
    }

// ----------------------------------------------------------------------------
// CBCTestPopupsContainer::Draw
// Fills the window's rectangle.
// ----------------------------------------------------------------------------
//
void CBCTestPopupsContainer::Draw( const TRect& aRect ) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KRgbGray );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// ---------------------------------------------------------------------------
// CBCTestPopupsContainer::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CBCTestPopupsContainer::CountComponentControls() const
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
// CBCTestPopupsContainer::ComponentControl
// ---------------------------------------------------------------------------
//
CCoeControl* CBCTestPopupsContainer::ComponentControl( TInt ) const
    {
    return iControl;
    }

// ---------------------------------------------------------------------------
// CBCTestPopupsContainer::SetControlL  
// ---------------------------------------------------------------------------
//
void CBCTestPopupsContainer::SetControlL( CCoeControl* aControl )
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
// CBCTestPopupsContainer::ResetControl
// ---------------------------------------------------------------------------
//
void CBCTestPopupsContainer::ResetControl()
    {
    delete iControl;
    iControl = NULL;
    }
        
// ---------------------------------------------------------------------------
// CBCTestPopupsContainer::GetCoeEnv
// ---------------------------------------------------------------------------
//
CCoeEnv* CBCTestPopupsContainer::GetCoeEnv() 
    {
    return iCoeEnv;
    }
