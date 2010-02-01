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
* Description:  ?Description
*
*/


#include "bctestdomavkonpslncontainer.h"

#define KAKNATLISTGRAY TRgb( 0xaaaaaa )


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomAvkonPslnContainer::CBCTestDomAvkonPslnContainer()
    {    
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDomAvkonPslnContainer::~CBCTestDomAvkonPslnContainer()
    {
    ResetControl();   
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomAvkonPslnContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    ActivateL();
    }

// ---------------------------------------------------------------------------
// CBCTestDomAvkonPslnContainer::Draw
// Fills the window's rectangle.
// ---------------------------------------------------------------------------
//
void CBCTestDomAvkonPslnContainer::Draw( const TRect& aRect ) const
    {    
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KAKNATLISTGRAY );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// ---------------------------------------------------------------------------
// CBCTestDomAvkonPslnContainer::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CBCTestDomAvkonPslnContainer::CountComponentControls() const
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
// CBCTestDomAvkonPslnContainer::ComponentControl
// ---------------------------------------------------------------------------
//
CCoeControl* CBCTestDomAvkonPslnContainer::ComponentControl( TInt ) const
    {
    return iControl;
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomAvkonPslnContainer::SetControl
// ---------------------------------------------------------------------------
//
void CBCTestDomAvkonPslnContainer::SetControl( CCoeControl* aControl )
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
// CBCTestDomAvkonPslnContainer::ResetControl
// ---------------------------------------------------------------------------
//
void CBCTestDomAvkonPslnContainer::ResetControl()
    {
    delete iControl;
    iControl = NULL;        
    }
//end of file
