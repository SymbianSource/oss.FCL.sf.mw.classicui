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


CCtlSubContainer641::CCtlSubContainer641()
	{	
	}
	
CCtlSubContainer641::~CCtlSubContainer641()
	{
	// kids should be destroyed automatically	
	delete iName;
	}
	
void CCtlSubContainer641::ConstructL( const TDesC& aName )
	{
	CCtlBase641::ConstructL();
	
	// construct the kids, add them to the array.	
	iName = aName.AllocL();
	// Not window-owning
	
	iContainee = new (ELeave) CCtlContainee641;
	InitComponentArrayL();
   	Components().AppendLC( iContainee, KChildOneID ) ;
	iContainee->ConstructL( _L("child1") );
	CleanupStack::Pop( iContainee );
		
	iContainee->SetParent( this );
	}
	
void CCtlSubContainer641::SizeChanged() 
	{
	// set the size of the children
	TRect rect = Rect();
	TSize size = rect.Size();
	TPoint tl = rect.iTl;
	
	
	TInt childCount = CountComponentControls();
	if ( childCount > 0 )
		{
		size.iWidth = (size.iWidth * 5 )/10;
		size.iHeight = ( size.iHeight * 4 )/10;
		
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

void CCtlSubContainer641::Draw( const TRect& /*aRect*/ ) const
	{
	// get a graphics context - outline the control
	CWindowGc& gc=SystemGc();
	TRect rect=Rect();
	gc.SetBrushColor( KRgbCyan );
	DoDraw( gc, rect );
	
	ApplyText();	
	}


/** Draw text using a text-drawer derived from the environment, 
	and a text-drawer instantiated locally.
*/
void CCtlSubContainer641::ApplyText() const
	{
	TInt key = 0;
	// The Inherited text drawer
	XCoeTextDrawer xTextDrawer(TextDrawer( key ));
	
	TRect rect = Rect();
	CCoeEnv* env = ControlEnv();
	
	xTextDrawer.SetClipRect( rect );
	xTextDrawer.SetAlignment( EHRightVBottom );
	xTextDrawer.DrawDisplayOrderedText( SystemGc(), KInheritedTextDrawerText, rect, *env->NormalFont() );
	}



/**  Child controls wanting parents' text-drawer will get one
	 derived by recursing parent controls.
*/
void CCtlSubContainer641::GetTextDrawer( CCoeTextDrawerBase*& /*aTextDrawer*/, const CCoeControl* /*aDrawingControl*/, TInt /*aInt*/ ) const
	{
	}


