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
* Description:  Implement container class
*
*/


#include "bctestdomm3gcontainer.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomM3gContainer::CBCTestDomM3gContainer()
    {    
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDomM3gContainer::~CBCTestDomM3gContainer()
    {
    ResetControl();   
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomM3gContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    ActivateL();
    }

// ----------------------------------------------------------------------------
// CBCTestDomM3gContainer::Draw
// Fills the window's rectangle.
// ----------------------------------------------------------------------------
//
void CBCTestDomM3gContainer::Draw( const TRect& aRect ) const
    {    
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KRgbGray );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// ---------------------------------------------------------------------------
// CBCTestDomM3gContainer::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CBCTestDomM3gContainer::CountComponentControls() const
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
// CBCTestDomM3gContainer::ComponentControl
// ---------------------------------------------------------------------------
//
CCoeControl* CBCTestDomM3gContainer::ComponentControl( TInt ) const
    {
    return iControl;
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomM3gContainer::SetControlL
// ---------------------------------------------------------------------------
//
void CBCTestDomM3gContainer::SetControlL( CCoeControl* aControl )
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
// CBCTestDomM3gContainer::ResetControl
// ---------------------------------------------------------------------------
//
void CBCTestDomM3gContainer::ResetControl()
    {
    delete iControl;
    iControl = NULL;        
    }
    
// ---------------------------------------------------------------------------
// CBCTestPopupsContainer::GetCoeEnv
// ---------------------------------------------------------------------------
//
CCoeEnv* CBCTestDomM3gContainer::GetCoeEnv() 
    {
    return iCoeEnv;
    }    
