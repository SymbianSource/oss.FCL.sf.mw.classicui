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








#include "bctestsearchfieldcontainer.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestSearchFieldContainer::CBCTestSearchFieldContainer()
    {    
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestSearchFieldContainer::~CBCTestSearchFieldContainer()
    {
    ResetControl();   
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestSearchFieldContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    ActivateL();
    }

// ----------------------------------------------------------------------------
// CBCTestSearchFieldContainer::Draw
// Fills the window's rectangle.
// ----------------------------------------------------------------------------
//
void CBCTestSearchFieldContainer::Draw( const TRect& aRect ) const
    {    
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KRgbGray );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// ---------------------------------------------------------------------------
// CBCTestSearchFieldContainer::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CBCTestSearchFieldContainer::CountComponentControls() const
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
// CBCTestSearchFieldContainer::ComponentControl
// ---------------------------------------------------------------------------
//
CCoeControl* CBCTestSearchFieldContainer::ComponentControl( TInt ) const
    {
    return iControl;
    }
    
// ---------------------------------------------------------------------------
// CBCTestSearchFieldContainer::SetControlL
// ---------------------------------------------------------------------------
//
void CBCTestSearchFieldContainer::SetControlL( CCoeControl* aControl )
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
// CBCTestSearchFieldContainer::ResetControl
// ---------------------------------------------------------------------------
//
void CBCTestSearchFieldContainer::ResetControl()
    {
    delete iControl;
    iControl = NULL;        
    }
    
// ---------------------------------------------------------------------------
// CBCTestPopupsContainer::GetCoeEnv
// ---------------------------------------------------------------------------
//
CCoeEnv* CBCTestSearchFieldContainer::GetCoeEnv() 
    {
    return iCoeEnv;
    }    
