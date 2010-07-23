/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test options_menu_api
 *
*/


#include "testsdkoptionsmenucontainer.h"

#define KBCTestListGray TRgb(0xaaaaaa)

// ================================ MEMBER FUNCTIONS ================================

// ---------------------------------------------------------------------------
// CTestSDKOptionsMenuContainer::NewL
// ---------------------------------------------------------------------------
//
CTestSDKOptionsMenuContainer* CTestSDKOptionsMenuContainer::NewL( const TRect& aRect )
    {
    CTestSDKOptionsMenuContainer* self = new ( ELeave ) CTestSDKOptionsMenuContainer;
    CleanupStack::PushL( self );
    self->ConstructL( aRect );
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CTestSDKOptionsMenuContainer::CTestSDKOptionsMenuContainer()
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CTestSDKOptionsMenuContainer::~CTestSDKOptionsMenuContainer()
    {
    ResetControl();
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CTestSDKOptionsMenuContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    ActivateL();
    }

// ----------------------------------------------------------------------------
// CTestSDKOptionsMenuContainer::Draw
// Fills the window's rectangle.
// ----------------------------------------------------------------------------
//
void CTestSDKOptionsMenuContainer::Draw( const TRect& aRect ) const
    {    
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KBCTestListGray );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// ---------------------------------------------------------------------------
// CTestSDKOptionsMenuContainer::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CTestSDKOptionsMenuContainer::CountComponentControls() const
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
// CTestSDKOptionsMenuContainer::ComponentControl
// ---------------------------------------------------------------------------
//
CCoeControl* CTestSDKOptionsMenuContainer::ComponentControl( TInt ) const
    {
    return iControl;
    }
    
// ---------------------------------------------------------------------------
// CTestSDKOptionsMenuContainer::SetControl
// ---------------------------------------------------------------------------
//
void CTestSDKOptionsMenuContainer::SetControlL( CCoeControl* aControl )
    {
    iControl = aControl;    
    if ( iControl )
        {  
        // You can change the position and size
        iControl->SetExtent( Rect().iTl, Rect().Size() );
        iControl->ActivateL();
        }    
    }
    
// ---------------------------------------------------------------------------
// CTestSDKOptionsMenuContainer::ResetControl
// ---------------------------------------------------------------------------
//
void CTestSDKOptionsMenuContainer::ResetControl()
    {
    delete iControl;
    iControl = NULL;
    }

void CTestSDKOptionsMenuContainer::ActivateGc()
    {
    CCoeControl::ActivateGc();
    }

void CTestSDKOptionsMenuContainer::DeactivateGc()
    {
    CCoeControl::DeactivateGc();
    }

//End of File
