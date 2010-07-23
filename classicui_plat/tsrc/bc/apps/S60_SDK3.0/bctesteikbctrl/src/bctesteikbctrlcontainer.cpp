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









#include "bctesteikbctrlcontainer.h"
#include "bctestmiscellcase.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTesteikbctrlContainer::CBCTesteikbctrlContainer()
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTesteikbctrlContainer::~CBCTesteikbctrlContainer()
    {
    ResetControl();
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTesteikbctrlContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    ActivateL();
    }

// ----------------------------------------------------------------------------
// CBCTesteikbctrlContainer::Draw
// Fills the window's rectangle.
// ----------------------------------------------------------------------------
//
void CBCTesteikbctrlContainer::Draw( const TRect& aRect ) const
    {
    CWindowGc& gc = SystemGc();
    
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KRgbGray );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    
    }

// ---------------------------------------------------------------------------
// CBCTesteikbctrlContainer::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CBCTesteikbctrlContainer::CountComponentControls() const
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
// CBCTesteikbctrlContainer::ComponentControl
// ---------------------------------------------------------------------------
//
CCoeControl* CBCTesteikbctrlContainer::ComponentControl( TInt ) const
    {
    return iControl;
    }

// ---------------------------------------------------------------------------
// CBCTesteikbctrlContainer::SetControl
// ---------------------------------------------------------------------------

void CBCTesteikbctrlContainer::SetControl( CCoeControl* aControl )
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
// CBCTesteikbctrlContainer::ResetControl
// ---------------------------------------------------------------------------
//
void CBCTesteikbctrlContainer::ResetControl()
    {
    delete iControl;
    iControl = NULL;
    }

CWindowGc& CBCTesteikbctrlContainer::GetSystemGc()
    {
        return CCoeEnv::Static()->SystemGc();
    }

