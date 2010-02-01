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
* Description:  test skinnable_clock_api
 *
*/


#include "testdomclockcontainer.h"

// ================================ MEMBER FUNCTIONS ================================

// ---------------------------------------------------------------------------
// CTestSDKOptionsMenuContainer::NewL
// ---------------------------------------------------------------------------
//
CTestDomClockContainer* CTestDomClockContainer::NewL( const TRect& aRect )
    {
    CTestDomClockContainer* self = new ( ELeave ) CTestDomClockContainer;
    CleanupStack::PushL( self );
    self->ConstructL( aRect );
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CTestDomClockContainer::CTestDomClockContainer()
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CTestDomClockContainer::~CTestDomClockContainer()
    {
    ResetControl();
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CTestDomClockContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    ActivateL();
    }

// ----------------------------------------------------------------------------
// CTestDomClockContainer::Draw
// Fills the window's rectangle.
// ----------------------------------------------------------------------------
//
void CTestDomClockContainer::Draw( const TRect& aRect ) const
    {    
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KRgbBlue );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// ---------------------------------------------------------------------------
// CTestDomClockContainer::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CTestDomClockContainer::CountComponentControls() const
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
// CTestDomClockContainer::ComponentControl
// ---------------------------------------------------------------------------
//
CCoeControl* CTestDomClockContainer::ComponentControl( TInt ) const
    {
    return iControl;
    }
    
// ---------------------------------------------------------------------------
// CTestDomClockContainer::SetControl
// ---------------------------------------------------------------------------
//
void CTestDomClockContainer::SetControlL( CCoeControl* aControl )
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
// CTestDomClockContainer::ResetControl
// ---------------------------------------------------------------------------
//
void CTestDomClockContainer::ResetControl()
    {
    delete iControl;
    iControl = NULL;
    }
//End of File
