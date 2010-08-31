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









#include "bctestEditorcontainer.h"

#define KAknAtListGray TRgb(0xaaaaaa)

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestEditorContainer::CBCTestEditorContainer()
    {    
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestEditorContainer::~CBCTestEditorContainer()
    {
    ResetControl();   
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestEditorContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    ActivateL();
    }

// ----------------------------------------------------------------------------
// CBCTestEditorContainer::Draw
// Fills the window's rectangle.
// ----------------------------------------------------------------------------
//
void CBCTestEditorContainer::Draw( const TRect& aRect ) const
    {    
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KAknAtListGray );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// ---------------------------------------------------------------------------
// CBCTestEditorContainer::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CBCTestEditorContainer::CountComponentControls() const
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
// CBCTestEditorContainer::ComponentControl
// ---------------------------------------------------------------------------
//
CCoeControl* CBCTestEditorContainer::ComponentControl( TInt ) const
    {
    return iControl;
    }
    
// ---------------------------------------------------------------------------
// CBCTestEditorContainer::SetControl
// ---------------------------------------------------------------------------
//
void CBCTestEditorContainer::SetControlL( CCoeControl* aControl )
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
// CBCTestEditorContainer::ResetControl
// ---------------------------------------------------------------------------
//
void CBCTestEditorContainer::ResetControl()
    {
    delete iControl;
    iControl = NULL;        
    }
