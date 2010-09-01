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
* Description:  container
*
*/

#include <aknappgrid.h>

#include "bctestdomaiwakncontainer.h"


#define KAknAtListGray TRgb( 0xaaaaaa )


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomAiwAknContainer::CBCTestDomAiwAknContainer()
    {    
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDomAiwAknContainer::~CBCTestDomAiwAknContainer()
    {
    ResetControl();   
    delete iAppStyleGrid;
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomAiwAknContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    
    iAppStyleGrid = 
        new( ELeave ) CAknAppStyleGrid();  
    CleanupStack::PushL( iAppStyleGrid );             
    iAppStyleGrid->SetContainerWindowL( *this );        
    iAppStyleGrid->ConstructL( this );   
    CleanupStack::Pop( iAppStyleGrid ); 
    
    ActivateL();   
    
    }

// ---------------------------------------------------------------------------
// CBCTestDomAiwAknContainer::Draw
// Fills the window's rectangle.
// ---------------------------------------------------------------------------
//
void CBCTestDomAiwAknContainer::Draw( const TRect& aRect ) const
    {    
    CWindowGc& gc = SystemGc();
    
    
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KAknAtListGray );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );  
    
    iAppStyleGrid->DrawBackgroundAroundGrid( gc, aRect, aRect);

    }

// ---------------------------------------------------------------------------
// CBCTestDomAiwAknContainer::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CBCTestDomAiwAknContainer::CountComponentControls() const
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
// CBCTestDomAiwAknContainer::ComponentControl
// ---------------------------------------------------------------------------
//
CCoeControl* CBCTestDomAiwAknContainer::ComponentControl( TInt ) const
    {
    return iControl;
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomAiwAknContainer::SetControl
// ---------------------------------------------------------------------------
//
void CBCTestDomAiwAknContainer::SetControl( CCoeControl* aControl )
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
// CBCTestDomAiwAknContainer::ResetControl
// ---------------------------------------------------------------------------
//
void CBCTestDomAiwAknContainer::ResetControl()
    {
    delete iControl;
    iControl = NULL;        
    }
