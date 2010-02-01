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
* Description:         Implements test bc for note control container.
*
*/









#include "bctestnotecontainer.h"

#define KAknAtListGray TRgb(0xaaaaaa)

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestNoteContainer::CBCTestNoteContainer()
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestNoteContainer::~CBCTestNoteContainer()
    {
    ResetControl();
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestNoteContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    ActivateL();
    }

// ----------------------------------------------------------------------------
// CBCTestNoteContainer::Draw
// Fills the window's rectangle.
// ----------------------------------------------------------------------------
//
void CBCTestNoteContainer::Draw( const TRect& aRect ) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KAknAtListGray );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// ---------------------------------------------------------------------------
// CBCTestNoteContainer::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CBCTestNoteContainer::CountComponentControls() const
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
// CBCTestNoteContainer::ComponentControl
// ---------------------------------------------------------------------------
//
CCoeControl* CBCTestNoteContainer::ComponentControl( TInt ) const
    { 
    return iControl;
    }

// ---------------------------------------------------------------------------
// CBCTestNoteContainer::SetControlL
// ---------------------------------------------------------------------------
//
void CBCTestNoteContainer::SetControlL( CCoeControl* aControl )
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
// CBCTestNoteContainer::ResetControl
// ---------------------------------------------------------------------------
//
void CBCTestNoteContainer::ResetControl()
    {
    delete iControl;
    iControl = NULL;
    }
        
// ---------------------------------------------------------------------------
// CBCTestNoteContainer::GetCoeEnv
// ---------------------------------------------------------------------------
//
CCoeEnv* CBCTestNoteContainer::GetCoeEnv() 
    {
    return iCoeEnv;
    }
