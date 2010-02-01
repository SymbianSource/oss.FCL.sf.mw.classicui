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









#include <aknlists.h> 
#include <barsread.h>
#include <bctestutilities.rsg>

#include "bctestutilitiescontainer.h"
#include "bctestutilitiescase.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestUtilitiesContainer::CBCTestUtilitiesContainer()
    {    
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestUtilitiesContainer::~CBCTestUtilitiesContainer()
    {
    ResetControl();
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestUtilitiesContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    ActivateL();
    }

// ----------------------------------------------------------------------------
// CBCTestUtilitiesContainer::Draw
// Fills the window's rectangle.
// ----------------------------------------------------------------------------
//
void CBCTestUtilitiesContainer::Draw( const TRect& aRect ) const
    {    
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KRgbGray );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// ---------------------------------------------------------------------------
// CBCTestUtilitiesContainer::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CBCTestUtilitiesContainer::CountComponentControls() const
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
// CBCTestUtilitiesContainer::ComponentControl
// ---------------------------------------------------------------------------
//
CCoeControl* CBCTestUtilitiesContainer::ComponentControl( TInt ) const
    {
    return iControl;
    }
    
// ---------------------------------------------------------------------------
// CBCTestUtilitiesContainer::SetControl
// ---------------------------------------------------------------------------
//
void CBCTestUtilitiesContainer::SetControl( CCoeControl* aControl )
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
// CBCTestUtilitiesContainer::ResetControl
// ---------------------------------------------------------------------------
//
void CBCTestUtilitiesContainer::ResetControl()
    {
    delete iControl;
    iControl = NULL;    
    }
