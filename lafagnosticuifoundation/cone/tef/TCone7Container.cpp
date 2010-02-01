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


CCtlContainer641::CCtlContainer641()
	{	
	}

CCtlContainer641::~CCtlContainer641()
	{
	// kids should be destroyed automatically	
	delete iName;
	iContainee = NULL;
	}
	
void CCtlContainer641::ConstructL( const TDesC& aName )
	{
	CCtlBase641::ConstructL();
	
	// construct the kids, add them to the array.	
	iName = aName.AllocL();
	CreateWindowL();
	InitComponentArrayL();
	
	iContainee = new (ELeave) CCtlContainee641;
   	Components().AppendLC( iContainee, KChildOneID ) ;
	iContainee->ConstructL( _L("child1") );
	CleanupStack::Pop(iContainee);
	}

void CCtlContainer641::SizeChanged() 
	{
	// set the size of the children
	const TRect rect = Rect();
	TSize size = rect.Size();
	TPoint tl = rect.iTl;
	
	TInt childCount = CountComponentControls();
	if ( childCount > 0 )
		{
		size.iWidth = (size.iWidth *3 )/10;
		size.iHeight = ( size.iHeight * 8 )/10;
		
		CCoeControl* child = NULL;
		for ( TInt ii = 0; ii < childCount; ++ii )
			{
			child = ComponentControl( ii );
			tl.iX += size.iWidth/10;
			tl.iY += size.iHeight/10;
			child->SetRect( TRect( tl, size ) );
			}
		}
	}


void CCtlContainer641::Draw( const TRect& /*aRect*/ ) const
	{
	// get a graphics context - outline the control
	CWindowGc& gc = SystemGc();
	TRect rect = Rect();
	gc.SetBrushColor( KRgbGreen );
	DoDraw( gc, rect );
	
	ApplyText();	
	}



/**
Draw text using a text-drawer derived from the environment, 
and a text-drawer instantiated locally.
*/
void CCtlContainer641::ApplyText() const
	{
	// The Inherited text drawer
	XCoeTextDrawer xTextDrawer(TextDrawer());
	// Assume IsReusable
	
	const TRect rect = Rect();
	xTextDrawer.SetClipRect( rect );
	xTextDrawer.SetAlignment( EHRightVBottom );
	xTextDrawer.DrawDisplayOrderedText( SystemGc(), KInheritedTextDrawerText, rect, *iEikonEnv->NormalFont() );
	}



/**  Child controls wanting parents' text-drawer will get this one. */

void CCtlContainer641::GetTextDrawer( CCoeTextDrawerBase*& aTextDrawer, const CCoeControl* /*aDrawingControl*/, TInt /*aInt*/ ) const
	{
	aTextDrawer = &iCoeEnv->DefaultTextDrawer();
	aTextDrawer->SetTextColor( KRgbInherited );
	// Assume that the system text-drawer _is_ reusable.
	// See adjusted CoeEnv ConstructL()
	}


