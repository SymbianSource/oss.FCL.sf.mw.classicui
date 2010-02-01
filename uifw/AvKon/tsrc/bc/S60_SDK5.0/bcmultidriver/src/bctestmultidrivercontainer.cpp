/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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


#include "BCTestMultiDrivercontainer.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CMultiDriverContainer::CMultiDriverContainer()
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CMultiDriverContainer::~CMultiDriverContainer()
    {
    ResetControl();
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CMultiDriverContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    ActivateL();
    }
 
// ----------------------------------------------------------------------------
// CMultiDriverContainer::Draw
// Fills the window's rectangle.
// ----------------------------------------------------------------------------
//
void CMultiDriverContainer::Draw( const TRect& aRect ) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KRgbGray );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// ---------------------------------------------------------------------------
// CMultiDriverContainer::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CMultiDriverContainer::CountComponentControls() const
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
// CMultiDriverContainer::ComponentControl
// ---------------------------------------------------------------------------
//
CCoeControl* CMultiDriverContainer::ComponentControl( TInt ) const
    {
    return iControl;
    }

// ---------------------------------------------------------------------------
// CMultiDriverContainer::SetControl
// ---------------------------------------------------------------------------
//
void CMultiDriverContainer::SetControl( CCoeControl* aControl )
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
// CMultiDriverContainer::ResetControl
// ---------------------------------------------------------------------------
//
void CMultiDriverContainer::ResetControl()
    {
    delete iControl;
    iControl = NULL;
    }

