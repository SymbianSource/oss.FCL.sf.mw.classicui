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

#include <eikenv.h>
#include <AknMarqueeControl.h>
#include <aknlayoutscalable_avkon.cdl.h>

#include "bctestdomnotifiercontainer.h"

#define KAknAtListGray TRgb( 0xaaaaaa )


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCDomainTestNotifierContainer::CBCDomainTestNotifierContainer()
    {    
    } 

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCDomainTestNotifierContainer::~CBCDomainTestNotifierContainer()
    {
    ResetControl();   
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCDomainTestNotifierContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    ActivateL();
    }

// ---------------------------------------------------------------------------
// CBCDomainTestNotifierContainer::Draw
// Fills the window's rectangle.
// ---------------------------------------------------------------------------
//
void CBCDomainTestNotifierContainer::Draw( const TRect& aRect ) const
    {     
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KAknAtListGray );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );  
    gc.DrawRect( aRect );
    
    _LIT( KStart, "DRAW" );
    const TBuf<32>  txt( KStart );
    TRect rect( TRect(1,1,99,99) );   
    const CFont* font = CEikonEnv::Static()->NormalFont();
    TAknTextComponentLayout textlayout;
    CAknMarqueeControl* marcontrol = CAknMarqueeControl::NewL();
    CleanupStack::PushL( marcontrol ); 
       
    marcontrol->DrawText( gc, rect, textlayout, txt, font ); 
    CleanupStack::PopAndDestroy();
    
    }

// ---------------------------------------------------------------------------
// CBCDomainTestNotifierContainer::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CBCDomainTestNotifierContainer::CountComponentControls() const
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
// CBCDomainTestNotifierContainer::ComponentControl
// ---------------------------------------------------------------------------
//
CCoeControl* CBCDomainTestNotifierContainer::ComponentControl( TInt ) const
    {
    return iControl;
    }
    
// ---------------------------------------------------------------------------
// CBCDomainTestNotifierContainer::SetControl
// ---------------------------------------------------------------------------
//
void CBCDomainTestNotifierContainer::SetControl( CCoeControl* aControl )
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
// CBCDomainTestNotifierContainer::ResetControl
// ---------------------------------------------------------------------------
//
void CBCDomainTestNotifierContainer::ResetControl()
    {
    delete iControl;
    iControl = NULL;        
    }
