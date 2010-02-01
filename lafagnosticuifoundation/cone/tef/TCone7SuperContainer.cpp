// Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
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

/**
 @file
 @internalComponent - Internal Symbian test code 
*/


#include "TCone7Step.h"


CCtlSuperContainer641::CCtlSuperContainer641()
	{	
	}
	
CCtlSuperContainer641::~CCtlSuperContainer641()
	{
	// kids should be destroyed automatically	
	delete iName;
	}
	
void CCtlSuperContainer641::ConstructL( const TDesC& aName )
	{
	CCtlBase641::ConstructL();
	
	// construct the kids, add them to the array.	
	iName = aName.AllocL();
	CreateWindowL();
	
	iSubContainer = new (ELeave) CCtlSubContainer641;
	InitComponentArrayL();
   	Components().AppendLC( iSubContainer, KChildOneID ) ;
	iSubContainer->ConstructL( _L("subcontainer") );
	CleanupStack::Pop( iSubContainer );
		
	iSubContainer->SetParent( this );
	
	ActivateL();
	}

void CCtlSuperContainer641::SizeChanged() 
	{
	// set the size of the children
	TRect rect = Rect();
	TSize size = rect.Size();
	TPoint tl = rect.iTl;
	
	
	TInt childCount = CountComponentControls();
	if ( childCount > 0 )
		{
		size.iWidth = (size.iWidth *5 )/10;
		size.iHeight = ( size.iHeight * 8 )/10;
		
		CCoeControl* child;
		for ( TInt ii = 0; ii < childCount; ++ii )
			{
			child = ComponentControl( ii );
			tl.iX += size.iWidth/10;
			tl.iY += size.iHeight/10;
			child->SetRect( TRect( tl, size ) );
			}	
		}		
	}



void CCtlSuperContainer641::Draw( const TRect& /*aRect*/ ) const
	{
	// get a graphics context - outline the control
	CWindowGc& gc=SystemGc();
	TRect rect=Rect();
	gc.SetBrushColor( KRgbGreen );
	DoDraw( gc, rect );
	
	ApplyText();	
	}



/**  Draw text using a text-drawer derived from the environment, 
	 and a text-drawer instantiated locally.
*/
void CCtlSuperContainer641::ApplyText() const
	{		
	TInt key = 0;
	// The Inherited text drawer
	XCoeTextDrawer xTextDrawer(TextDrawer( key ));
	//Assume reusable	
	
	TRect rect = Rect();
	CCoeEnv* env = ControlEnv();
	
	xTextDrawer.SetClipRect( rect );
	xTextDrawer.SetAlignment( EHRightVBottom );
	xTextDrawer.DrawDisplayOrderedText( SystemGc(), KInheritedTextDrawerText, rect, *env->NormalFont() );
	}


/**  Child controls wanting parents' text-drawer will get this one.
	Derived from the Cone environment
*/
void CCtlSuperContainer641::GetTextDrawer( CCoeTextDrawerBase*& aTextDrawer, const CCoeControl* /*aDrawingControl*/, TInt /*aInt*/ ) const
	{
	aTextDrawer = &iCoeEnv->DefaultTextDrawer();
	aTextDrawer->SetTextColor( KRgbInherited );
	// Assume that the system text-drawer _is_ reusable.
	// See adjusted CoeEnv ConstructL()
	}

