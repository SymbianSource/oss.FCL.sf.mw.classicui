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









#include "BCTestChoicelistcontainer.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCPopupChoicelistContainer::CBCPopupChoicelistContainer()
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCPopupChoicelistContainer::~CBCPopupChoicelistContainer()
    {
    ResetControl();
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCPopupChoicelistContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    ActivateL();
    }

// ----------------------------------------------------------------------------
// CBCPopupChoicelistContainer::Draw
// Fills the window's rectangle.
// ----------------------------------------------------------------------------
//
void CBCPopupChoicelistContainer::Draw( const TRect& aRect ) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KRgbGray );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// ---------------------------------------------------------------------------
// CBCPopupChoicelistContainer::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CBCPopupChoicelistContainer::CountComponentControls() const
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
// CBCPopupChoicelistContainer::ComponentControl
// ---------------------------------------------------------------------------

CCoeControl* CBCPopupChoicelistContainer::ComponentControl( TInt ) const
    {
    return iControl;
    }

// ---------------------------------------------------------------------------
// CBCPopupChoicelistContainer::SetControl
// ---------------------------------------------------------------------------

void CBCPopupChoicelistContainer::SetControl( CCoeControl* aControl )
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
// CBCPopupChoicelistContainer::ResetControl
// ---------------------------------------------------------------------------

void CBCPopupChoicelistContainer::ResetControl()
    {
    delete iControl;
    iControl = NULL;
    }

