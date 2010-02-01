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


#include <aknappgrid.h>
#include <akncharmap.h>

#include "testdomcontainer.h"
#include "testdomspecialchartab.h"

// CONSTANT
#define KTestListGray TRgb(0xaaaaaa)
#define KAknAtListGray TRgb( 0xaaaaaa )

// ================================ MEMBER FUNCTIONS ================================

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CTestDomContainer::CTestDomContainer()
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CTestDomContainer::~CTestDomContainer()
    {
    ResetControl();   
    delete iAppStyleGrid;
    iAppStyleGrid = NULL;

    }
    

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CTestDomContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    iAppStyleGrid = new( ELeave ) CAknAppStyleGrid();  
    iAppStyleGrid->SetContainerWindowL( *this );        
    iAppStyleGrid->ConstructL( this );   
    ActivateL();   
    }

// ---------------------------------------------------------------------------
// CTestDomContainer::Draw
// Fills the window's rectangle.
// ---------------------------------------------------------------------------
//
void CTestDomContainer::Draw( const TRect& aRect ) const
    {    
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KAknAtListGray );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    iAppStyleGrid->DrawBackgroundAroundGrid( gc, aRect, aRect);
    }

// ---------------------------------------------------------------------------
// CTestDomContainer::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CTestDomContainer::CountComponentControls() const
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
// CTestDomContainer::ComponentControl
// ---------------------------------------------------------------------------
//
CCoeControl* CTestDomContainer::ComponentControl( TInt ) const
    {
    return iControl;
    }
    
// ---------------------------------------------------------------------------
// CTestDomContainer::SetControlL
// ---------------------------------------------------------------------------
//
void CTestDomContainer::SetControlL( CCoeControl* aControl )
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
// CTestDomContainer::ResetControl
// ---------------------------------------------------------------------------
//
void CTestDomContainer::ResetControl()
    {
    delete iControl;
    iControl = NULL;        
    }

// End of File


