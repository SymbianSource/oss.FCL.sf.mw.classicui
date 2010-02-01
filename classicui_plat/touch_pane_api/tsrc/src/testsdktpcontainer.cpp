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


#include <w32std.h>

#include "testsdktpcontainer.h"

#define KAKNATLISTGRAY TRgb( 0xaaaaaa )


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CTestSDKTPContainer::CTestSDKTPContainer()
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CTestSDKTPContainer::~CTestSDKTPContainer()
    {
    ResetControl();   
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CTestSDKTPContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    ActivateL();
    }

// ---------------------------------------------------------------------------
// CTestSDKTPContainer::Draw
// Fills the window's rectangle.
// ---------------------------------------------------------------------------
//
void CTestSDKTPContainer::Draw( const TRect& aRect ) const
    {    
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KAKNATLISTGRAY );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// ---------------------------------------------------------------------------
// CTestSDKTPContainer::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CTestSDKTPContainer::CountComponentControls() const
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
// CTestSDKTPContainer::ComponentControl
// ---------------------------------------------------------------------------
//
CCoeControl* CTestSDKTPContainer::ComponentControl( TInt ) const
    {
    return iControl;
    }
    
// ---------------------------------------------------------------------------
// CTestSDKTPContainer::SetControl
// ---------------------------------------------------------------------------
//
void CTestSDKTPContainer::SetControlL( CCoeControl* aControl )
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
// CTestSDKTPContainer::ResetControl
// ---------------------------------------------------------------------------
//
void CTestSDKTPContainer::ResetControl()
    {
    delete iControl;
    iControl = NULL;        
    }

// ---------------------------------------------------------------------------
// CTestSDKTPContainer::ActivateGc
// ---------------------------------------------------------------------------
//
void CTestSDKTPContainer::ActivateGc() const
    {
    CCoeControl::ActivateGc();
    }

// ---------------------------------------------------------------------------
// CTestSDKTPContainer::DeactivateGc
// ---------------------------------------------------------------------------
//
void CTestSDKTPContainer::DeactivateGc() const
    {
    CCoeControl::DeactivateGc();
    }

// ---------------------------------------------------------------------------
// CTestSDKTPContainer::TransferEventL
// ---------------------------------------------------------------------------
//
void CTestSDKTPContainer::TransferEventL( TPointerEvent aEvent )
    {
    CCoeControl::HandlePointerEventL(aEvent);
    }
//end of file
