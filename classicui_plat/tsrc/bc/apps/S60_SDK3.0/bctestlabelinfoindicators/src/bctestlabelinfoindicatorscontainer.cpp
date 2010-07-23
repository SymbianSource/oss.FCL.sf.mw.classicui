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
* Description:         Implements test bc for labelinfoindicators container.
*
*/









#include "bctestlabelinfoindicatorscontainer.h" 

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestLabelInfoIndicatorsContainer::CBCTestLabelInfoIndicatorsContainer()
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestLabelInfoIndicatorsContainer::~CBCTestLabelInfoIndicatorsContainer()
    {
    ResetControl();
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestLabelInfoIndicatorsContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    ActivateL();
    }

// ----------------------------------------------------------------------------
// CBCTestLabelInfoIndicatorsContainer::Draw
// Fills the window's rectangle.
// ----------------------------------------------------------------------------
//
void CBCTestLabelInfoIndicatorsContainer::Draw( const TRect& aRect ) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KRgbGray );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// ---------------------------------------------------------------------------
// CBCTestLabelInfoIndicatorsContainer::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CBCTestLabelInfoIndicatorsContainer::CountComponentControls() const
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
// CBCTestLabelInfoIndicatorsContainer::ComponentControl
// ---------------------------------------------------------------------------
//
CCoeControl* CBCTestLabelInfoIndicatorsContainer
    ::ComponentControl( TInt ) const
    {
    return iControl;
    }

// ---------------------------------------------------------------------------
// CBCTestLabelInfoIndicatorsContainer::SetControlL
// ---------------------------------------------------------------------------
//
void CBCTestLabelInfoIndicatorsContainer::SetControlL( CCoeControl* aControl )
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
// CBCTestLabelInfoIndicatorsContainer::ResetControl
// ---------------------------------------------------------------------------
//
void CBCTestLabelInfoIndicatorsContainer::ResetControl()
    {
    delete iControl;
    iControl = NULL;
    }
        
CCoeEnv* CBCTestLabelInfoIndicatorsContainer::GetCoeEnv() 
    {
    return iCoeEnv;
    }
