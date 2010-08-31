/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         container
*
*/









#include <aknsdrawutils.h> 
#include <eikenv.h>

#include "bctestskinscontainer.h"

#define KAknAtListGray TRgb(0xaaaaaa)

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestSkinsContainer::CBCTestSkinsContainer()
    {    
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestSkinsContainer::~CBCTestSkinsContainer()
    {
    ResetControl();   
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestSkinsContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    ActivateL();
	iDrawFlag = false;
    }

// ----------------------------------------------------------------------------
// CBCTestSkinsContainer::Draw
// Fills the window's rectangle.
// ----------------------------------------------------------------------------
//
void CBCTestSkinsContainer::Draw( const TRect& aRect ) const
    {    
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KAknAtListGray );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    
	if( !iDrawFlag ) 
		{
		return;	
		}
    
    // AknsDrawUtils::Background
    TBool boolflag = ETrue;   
    _LIT( KMsg, "Great");
    TBuf<16> info( KMsg );   
    
    _LIT( KErr, "Error");
    TBuf<16> errInfo( KErr );   
    
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );
    if( skin != NULL )    
	    {
		CEikonEnv::Static()->InfoMsg( KMsg );				    	
	    }
    
    boolflag = AknsDrawUtils::Background( skin, cc, gc, aRect );    
    if (boolflag) 
		{
		CEikonEnv::Static()->InfoMsg( info );			
		}
	else
		{
		CEikonEnv::Static()->InfoMsg( errInfo );			
		}
			
    // AknsDrawUtils::BackgroundBetweenRects
    TRect innerRect( 5, 5, 100, 100);    
    boolflag = AknsDrawUtils::BackgroundBetweenRects( skin, cc, gc, aRect, innerRect);
    if (boolflag) 
		{
		CEikonEnv::Static()->InfoMsg( info );			
		}
	else
		{
		CEikonEnv::Static()->InfoMsg( errInfo );			
		}    
	
	boolflag = AknsDrawUtils::DrawFramePart(skin, gc, aRect, KAknsIIDQsnFrSetOptCornerTl, 
	    EAknsFrameIndexCenter );  
    }

void CBCTestSkinsContainer::DrawTest()
	{    
    iDrawFlag = true;
    DrawNow();
    iDrawFlag = false;
	}

// ---------------------------------------------------------------------------
// CBCTestSkinsContainer::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CBCTestSkinsContainer::CountComponentControls() const
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
// CBCTestSkinsContainer::ComponentControl
// ---------------------------------------------------------------------------
//
CCoeControl* CBCTestSkinsContainer::ComponentControl( TInt ) const
    {
    return iControl;
    }
    
// ---------------------------------------------------------------------------
// CBCTestSkinsContainer::SetControl
// ---------------------------------------------------------------------------
//
void CBCTestSkinsContainer::SetControl( CCoeControl* aControl )
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
// CBCTestSkinsContainer::ResetControl
// ---------------------------------------------------------------------------
//
void CBCTestSkinsContainer::ResetControl()
    {
    delete iControl;
    iControl = NULL;    
    }
