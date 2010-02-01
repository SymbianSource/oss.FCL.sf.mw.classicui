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

// Child

/** Assume container has no background and will supply the  environment's text drawer. */
	
TBool CCtlContainee641::TestContainerTextDrawer()
	{
	// The Inherited text drawer
	XCoeTextDrawer xTextDrawer(TextDrawer());
	// Assume reusable.
	
	TRect rect = Rect();
	CCoeEnv* env = ControlEnv();
	
	ActivateGc();
	
	xTextDrawer.SetClipRect( rect );
	xTextDrawer.SetAlignment( EHRightVBottom );
	xTextDrawer.DrawDisplayOrderedText( SystemGc(), KInheritedTextDrawerText, rect, *env->NormalFont() );

	DeactivateGc();
	iCoeEnv->Flush();
	
	return (KRgbInherited == xTextDrawer->TextColor());
	}

void CCtlContainee641::ApplyText() const
	{	
	TInt key = 0;
	// The Inherited text drawer
	XCoeTextDrawer xTextDrawer(TextDrawer( key ));
	
	TRect rect = Rect();
	CCoeEnv* env = ControlEnv();
	
	xTextDrawer.SetClipRect( rect );
	xTextDrawer.SetAlignment( EHLeftVTop );
	xTextDrawer.DrawDisplayOrderedText( SystemGc(), KInheritedTextDrawerText, rect, *env->NormalFont() );

	// Our local text drawer
	XCoeTextDrawer textDrawer(*CCoePlainTextDrawer::New( KRgbBlue ));
	
	textDrawer.SetClipRect( rect );
	textDrawer.SetAlignment( EHLeftVBottom );
	textDrawer.DrawDisplayOrderedText( SystemGc(), KLocalTextDrawerText, rect, *env->NormalFont() );
	}

CCtlContainee641::CCtlContainee641()
	{
	}
	
CCtlContainee641::~CCtlContainee641()
	{
	delete iName;
	}
	
void CCtlContainee641::ConstructL( const TDesC& aName )
	{
	CCtlBase641::ConstructL();
	iName = aName.AllocL();
	}

void CCtlContainee641::Draw(const TRect& /*aRect*/) const
	{
	CWindowGc& gc=SystemGc();
	TRect rect=Rect();
	gc.SetBrushColor( KRgbYellow );
		
	DoDraw( gc, rect );
	
	//ApplyText();
	}	

const TDesC& CCtlContainee641::WhoAmI() const
	{
	return *iName;
	}
