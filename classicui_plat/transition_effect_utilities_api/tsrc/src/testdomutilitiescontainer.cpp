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
* Description:  test transition_effect_utilities_api
*
*/


#include "testdomutilitiescontainer.h"


// ================================ MEMBER FUNCTIONS ================================

// ----------------------------------------------------------------------------
// CTestDomUtilitiesContainer::NewL
// ---------------------------------------------------------------------------
//
CTestDomUtilitiesContainer* CTestDomUtilitiesContainer::NewL( const TRect& aRect )
    {
    CTestDomUtilitiesContainer* self = new ( ELeave ) CTestDomUtilitiesContainer;
    CleanupStack::PushL( self );
    self->ConstructL( aRect );
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CTestDomUtilitiesContainer::CTestDomUtilitiesContainer()
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CTestDomUtilitiesContainer::~CTestDomUtilitiesContainer()
    {
    ResetControl();
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CTestDomUtilitiesContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    ActivateL();
    }

// ----------------------------------------------------------------------------
// CTestDomUtilitiesContainer::Draw
// Fills the window's rectangle.
// ----------------------------------------------------------------------------
//
void CTestDomUtilitiesContainer::Draw( const TRect& aRect ) const
    {    
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KRgbBlue );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// ---------------------------------------------------------------------------
// CTestDomUtilitiesContainer::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CTestDomUtilitiesContainer::CountComponentControls() const
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
// CTestDomUtilitiesContainer::ComponentControl
// ---------------------------------------------------------------------------
//
CCoeControl* CTestDomUtilitiesContainer::ComponentControl( TInt ) const
    {
    return iControl;
    }
    
// ---------------------------------------------------------------------------
// CTestDomUtilitiesContainer::SetControl
// ---------------------------------------------------------------------------
//
void CTestDomUtilitiesContainer::SetControlL( CCoeControl* aControl )
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
// CTestDomUtilitiesContainer::ResetControl
// ---------------------------------------------------------------------------
//
void CTestDomUtilitiesContainer::ResetControl()
    {
    delete iControl;
    iControl = NULL;
    }

// End of File
