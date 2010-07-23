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
* Description:  declaration of container
*
*/


#include <w32std.h>

#include "testsdkcontainer.h"

#define KAKNATLISTGRAY TRgb( 0xaaaaaa )


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CTestSDKContainer::CTestSDKContainer()
    {    
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CTestSDKContainer::~CTestSDKContainer()
    {
    ResetControl();   
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CTestSDKContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    ActivateL();
    }

// ---------------------------------------------------------------------------
// CTestSDKContainer::Draw
// Fills the window's rectangle.
// ---------------------------------------------------------------------------
//
void CTestSDKContainer::Draw( const TRect& aRect ) const
    {    
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KAKNATLISTGRAY );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// ---------------------------------------------------------------------------
// CTestSDKContainer::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CTestSDKContainer::CountComponentControls() const
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
// CTestSDKContainer::ComponentControl
// ---------------------------------------------------------------------------
//
CCoeControl* CTestSDKContainer::ComponentControl( TInt ) const
    {
    return iControl;
    }
    
// ---------------------------------------------------------------------------
// CTestSDKContainer::SetControl
// ---------------------------------------------------------------------------
//
void CTestSDKContainer::SetControlL( CCoeControl* aControl )
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
// CTestSDKContainer::ResetControl
// ---------------------------------------------------------------------------
//
void CTestSDKContainer::ResetControl()
    {
    delete iControl;
    iControl = NULL;        
    }

// ---------------------------------------------------------------------------
// CTestSDKContainer::ActivateGc
// ---------------------------------------------------------------------------
//
void CTestSDKContainer::ActivateGc() const
    {
    CCoeControl::ActivateGc();
    }

// ---------------------------------------------------------------------------
// CTestSDKContainer::DeactivateGc
// ---------------------------------------------------------------------------
//
void CTestSDKContainer::DeactivateGc() const
    {
    CCoeControl::DeactivateGc();
    }
//end of file
