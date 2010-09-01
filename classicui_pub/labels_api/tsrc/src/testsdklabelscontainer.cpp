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
* Description:  Test grids_api
*
*/

/*
 * Include files
 */
#include <w32std.h>

#include "testsdklabelscontainer.h"

#define KAKNATLISTGRAY TRgb( 0xaaaaaa )


// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CTestSDKLabelsContainer::CTestSDKLabelsContainer()
    {    
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CTestSDKLabelsContainer::~CTestSDKLabelsContainer()
    {
    ResetControl();   
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CTestSDKLabelsContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    ActivateL();
    }

// ---------------------------------------------------------------------------
// CTestSDKLabelsContainer::Draw
// Fills the window's rectangle.
// ---------------------------------------------------------------------------
//
void CTestSDKLabelsContainer::Draw( const TRect& aRect ) const
    {    
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KAKNATLISTGRAY );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// ---------------------------------------------------------------------------
// CTestSDKLabelsContainer::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CTestSDKLabelsContainer::CountComponentControls() const
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
// CTestSDKLabelsContainer::ComponentControl
// ---------------------------------------------------------------------------
//
CCoeControl* CTestSDKLabelsContainer::ComponentControl( TInt ) const
    {
    return iControl;
    }
    
// ---------------------------------------------------------------------------
// CTestSDKLabelsContainer::SetControl
// ---------------------------------------------------------------------------
//
void CTestSDKLabelsContainer::SetControlL( CCoeControl* aControl )
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
// CTestSDKLabelsContainer::ResetControl
// ---------------------------------------------------------------------------
//
void CTestSDKLabelsContainer::ResetControl()
    {
    delete iControl;
    iControl = NULL;        
    }

// ---------------------------------------------------------------------------
// CTestSDKLabelsContainer::ActivateGc
// ---------------------------------------------------------------------------
//
void CTestSDKLabelsContainer::ActivateGc() const
    {
    CCoeControl::ActivateGc();
    }

// ---------------------------------------------------------------------------
// CTestSDKLabelsContainer::DeactivateGc
// ---------------------------------------------------------------------------
//
void CTestSDKLabelsContainer::DeactivateGc() const
    {
    CCoeControl::DeactivateGc();
    }
//end of file
