/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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


#include <eikcmbut.h>
#include <eikenv.h>
#include <bctestbuttons.rsg>
#include <barsread.h>

#include "bctestbuttonscontainer.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestButtonsContainer::CBCTestButtonsContainer()
    {    
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestButtonsContainer::~CBCTestButtonsContainer()
    {
    ResetControl();   
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestButtonsContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    ActivateL();
    }

// ----------------------------------------------------------------------------
// CBCTestButtonsContainer::Draw
// Fills the window's rectangle.
// ----------------------------------------------------------------------------
//
void CBCTestButtonsContainer::Draw( const TRect& aRect ) const
    {    
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KRgbGray );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    
	CEikonEnv* env = CEikonEnv::Static();    
    // test CEikTwoPictureCommandButton's PrepareContext()
    CEikTwoPictureCommandButton* test = 
        new( ELeave ) CEikTwoPictureCommandButton();
    CleanupStack::PushL( test );
    MCoeControlContext* context = static_cast< MCoeControlContext* > ( test );
    context->PrepareContext( gc );
    _LIT( KMsg, "CEikTwoPictureCommandButton");
    TBuf<30> info( KMsg );   
	env->InfoMsg( info );			    
    CleanupStack::PopAndDestroy( test );

	// test CEikInverterCommandButton's PrepareContext()
    CEikInverterCommandButton* inverterCommandButton = 
        new( ELeave ) CEikInverterCommandButton();
    CleanupStack::PushL( inverterCommandButton );
    MCoeControlContext* context2 = static_cast< MCoeControlContext* > 
        ( inverterCommandButton );
    context2->PrepareContext( gc );
    _LIT( KMsg2, "CEikInverterCommandButton");
    TBuf<30> info2( KMsg2 );   
	env->InfoMsg( info2 );			    
    CleanupStack::PopAndDestroy( inverterCommandButton );
    
    // test CEikCommandButtonBase's PrepareContext()
    // new CEikCommandButton
    CEikCommandButton* commandButton = new( ELeave )CEikCommandButton();
    CleanupStack::PushL( commandButton );

    // construct from res
    TResourceReader reader1;
    CEikonEnv::Static()->CreateResourceReaderLC( reader1, R_BCTESTBUTTONS_CMBUT );
    commandButton->ConstructFromResourceL( reader1 );
    CleanupStack::PopAndDestroy(); //reader1

    MCoeControlContext* context3 = static_cast< MCoeControlContext* > ( commandButton );
    context3->PrepareContext( gc );
    _LIT( KMsg3, "CEikCommandButtonBase");
    TBuf<30> info3( KMsg3 );   
	env->InfoMsg( info3 );			    
	
    CleanupStack::PopAndDestroy( commandButton );
    
    }

// ---------------------------------------------------------------------------
// CBCTestButtonsContainer::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CBCTestButtonsContainer::CountComponentControls() const
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
// CBCTestButtonsContainer::ComponentControl
// ---------------------------------------------------------------------------
//
CCoeControl* CBCTestButtonsContainer::ComponentControl( TInt ) const
    {
    return iControl;
    }
    
// ---------------------------------------------------------------------------
// CBCTestButtonsContainer::SetControl
// ---------------------------------------------------------------------------
//
void CBCTestButtonsContainer::SetControlL( CCoeControl* aControl )
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
// CBCTestButtonsContainer::ResetControl
// ---------------------------------------------------------------------------
//
void CBCTestButtonsContainer::ResetControl()
    {
    delete iControl;
    iControl = NULL;        
    }


