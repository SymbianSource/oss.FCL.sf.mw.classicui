// Copyright (c) 2008-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
//

#include <techview/eikcmbut.h>
#include "tmultiptrtestchildcontrol.h"
#include "tmultiptrtestcompoundcontrolcontainer.h"


CMultPtrTestCompoundControlContainer::~CMultPtrTestCompoundControlContainer()
    {
    // Deletes the controls. 
    Components().ResetAndDestroy();
    }


CMultPtrTestCompoundControlContainer::CMultPtrTestCompoundControlContainer()
    {
    }


void CMultPtrTestCompoundControlContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
	Window().EnableAdvancedPointers();
    SetBlank();
    
	TRect containerRect(aRect);
	SetRect( containerRect );
	ActivateL();
	//Window().PointerFilter( (EPointerFilterMove | EPointerFilterDrag), 0 );
	InitComponentArrayL();
	
	TRect ourRect = Rect();
	
	
	iChildOne = new(ELeave) CMultiPtrTestChildControl;
	Components().SetControlsOwnedExternally( EFalse );
	const TInt KChildOneID = 1;
   	Components().AppendLC( iChildOne, KChildOneID ) ;
	iChildOne->ConstructL( _L("Child1") );
	CleanupStack::Pop( iChildOne );
		
	iChildOne->SetParent( this );
	iChildOne->SetExtent( TPoint(20,20), TSize(120,120) );
	iChildOne->ActivateL();
	iChildOne->DrawNow();

	
	iChildTwo = new(ELeave) CMultiPtrTestChildControl;
	const TInt KChildTwoID = 2;
   	Components().AppendLC( iChildTwo, KChildTwoID ) ;
   	iChildTwo->ConstructL( _L("Child2") );
	CleanupStack::Pop( iChildTwo );
		
	iChildTwo->SetParent( this );
	iChildTwo->SetExtent( TPoint(80,60), TSize(120,60) );
	iChildTwo->ActivateL();
	iChildTwo->DrawNow();	
    }


void CMultPtrTestCompoundControlContainer::Draw(const TRect& ) const
	{
	const TRect rect=Rect();
	CWindowGc& gc=SystemGc();
	gc.SetPenStyle(CGraphicsContext::ESolidPen );
	gc.SetPenColor( KRgbBlack );
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.SetBrushColor(KRgbBlack);	
	gc.DrawRect( Rect() );
	gc.SetPenStyle(CGraphicsContext::ENullPen );
	
	TRect portionRect( 0,0,0,0 );
	TInt dY = rect.Height() / 5;
	TInt dX = rect.Width() / 10;
	TInt diceY = 0;
	TInt diceX = 0;
	TBool black = ETrue;
	TRgb colourOne( 0x0000FF00, 0x7F );
	TRgb colourTwo( 0x000000FF, 0x7F );
	
	for( diceY = rect.iTl.iY; diceY < rect.Height(); diceY += dY )
		{
		
		for( diceX = rect.iTl.iX; diceX < rect.Width(); diceX += dX )
			{	
			portionRect.iTl.iX = diceX;
			portionRect.iTl.iY = diceY;
			portionRect.iBr.iX = diceX + dX;
			portionRect.iBr.iY = diceY + dY;
			
			if( black )	
				{
				gc.SetBrushColor( colourOne );
				black = EFalse;	
				}
			else
				{
				gc.SetBrushColor( colourTwo );
				black = ETrue;	
				}
				
			gc.DrawRect( portionRect );
			
			}
		
		dX /= 2;
		}
	
	}


void CMultPtrTestCompoundControlContainer::HandlePointerEventL(const TPointerEvent& aPointerEvent)
	{
	CCoeControl::HandlePointerEventL( aPointerEvent );
	}


