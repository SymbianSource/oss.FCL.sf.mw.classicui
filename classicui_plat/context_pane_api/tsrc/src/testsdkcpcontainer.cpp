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
* Description:  
*
*/


#include <w32std.h>

#include "testsdkcpcontainer.h"

#define KAKNATLISTGRAY TRgb( 0xaaaaaa )


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CTestSDKCPContainer::CTestSDKCPContainer()
    {    
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CTestSDKCPContainer::~CTestSDKCPContainer()
    {
    ResetControl();   
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CTestSDKCPContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    ActivateL();
    }

// ---------------------------------------------------------------------------
// CTestSDKCPContainer::Draw
// Fills the window's rectangle.
// ---------------------------------------------------------------------------
//
void CTestSDKCPContainer::Draw( const TRect& aRect ) const
    {    
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KAKNATLISTGRAY );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// ---------------------------------------------------------------------------
// CTestSDKCPContainer::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CTestSDKCPContainer::CountComponentControls() const
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
// CTestSDKCPContainer::ComponentControl
// ---------------------------------------------------------------------------
//
CCoeControl* CTestSDKCPContainer::ComponentControl( TInt ) const
    {
    return iControl;
    }
    
// ---------------------------------------------------------------------------
// CTestSDKCPContainer::SetControl
// ---------------------------------------------------------------------------
//
void CTestSDKCPContainer::SetControlL( CCoeControl* aControl )
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
// CTestSDKCPContainer::ResetControl
// ---------------------------------------------------------------------------
//
void CTestSDKCPContainer::ResetControl()
    {
    delete iControl;
    iControl = NULL;        
    }
//end of file
