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
* Description:  implements of container.
*
*/


// INCLUDE
#include <aknappgrid.h>

#include "testdomextanimationcontainer.h"



// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomExtAnimContainer::CTestDomExtAnimContainer
// -----------------------------------------------------------------------------
//
CTestDomExtAnimContainer::CTestDomExtAnimContainer()
: iControl( NULL )
    {
    }

// -----------------------------------------------------------------------------
// CTestDomExtAnimContainer::~CTestDomExtAnimContainer
// -----------------------------------------------------------------------------
//
CTestDomExtAnimContainer::~CTestDomExtAnimContainer()
    {
    ResetControl();
    }

// -----------------------------------------------------------------------------
// CTestDomExtAnimContainer::ConstructL
// -----------------------------------------------------------------------------
//
void CTestDomExtAnimContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    
    SetRect( aRect );

    ActivateL();

    }

// -----------------------------------------------------------------------------
// CTestDomExtAnimContainer::Draw
// Fills the window's rectangle.
// -----------------------------------------------------------------------------
//
void CTestDomExtAnimContainer::Draw( const TRect& aRect ) const
    {    
    CWindowGc& gc = SystemGc();
    
    
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KRgbBlack );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );

    }

// -----------------------------------------------------------------------------
// CTestDomExtAnimContainer::CountComponentControls
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAnimContainer::CountComponentControls() const
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
    
// -----------------------------------------------------------------------------
// CTestDomExtAnimContainer::ComponentControl
// -----------------------------------------------------------------------------
//
CCoeControl* CTestDomExtAnimContainer::ComponentControl( TInt ) const
    {
    return iControl;
    }
    
// -----------------------------------------------------------------------------
// CTestDomExtAnimContainer::SetControlL
// -----------------------------------------------------------------------------
//
void CTestDomExtAnimContainer::SetControlL( CCoeControl* aControl )
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
    
// -----------------------------------------------------------------------------
// CTestDomExtAnimContainer::ResetControl
// -----------------------------------------------------------------------------
//
void CTestDomExtAnimContainer::ResetControl()
    {
    if( iControl )
        {
        delete iControl;
        iControl = NULL;
        }
    }


// [End of File]

