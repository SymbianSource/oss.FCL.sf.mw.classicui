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
* Description:  Description
*
*/


#include <w32std.h>

#include "testsdksearchfieldcontainer.h"

#define KAKNATLISTGRAY TRgb( 0xaaaaaa )


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CTestSDKSearchFieldContainer::CTestSDKSearchFieldContainer() 
    {    
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CTestSDKSearchFieldContainer::~CTestSDKSearchFieldContainer()
    {
    ResetControl();   
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CTestSDKSearchFieldContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    ActivateL();
    }

// ---------------------------------------------------------------------------
// Ctestsdkgridscontainer::Draw
// Fills the window's rectangle.
// ---------------------------------------------------------------------------
//
void CTestSDKSearchFieldContainer::Draw( const TRect& aRect ) const
    {    
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KAKNATLISTGRAY );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// ---------------------------------------------------------------------------
// Ctestsdkgridscontainer::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CTestSDKSearchFieldContainer::CountComponentControls() const
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
// Ctestsdkgridscontainer::ComponentControl
// ---------------------------------------------------------------------------
//
CCoeControl* CTestSDKSearchFieldContainer::ComponentControl( TInt ) const
    {
    return iControl;
    }
    
// ---------------------------------------------------------------------------
// Ctestsdkgridscontainer::SetControl
// ---------------------------------------------------------------------------
//
void CTestSDKSearchFieldContainer::SetControlL( CCoeControl* aControl )
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
// Ctestsdkgridscontainer::ResetControl
// ---------------------------------------------------------------------------
//
void CTestSDKSearchFieldContainer::ResetControl()
    {
    delete iControl;
    iControl = NULL;        
    }
//end of file
