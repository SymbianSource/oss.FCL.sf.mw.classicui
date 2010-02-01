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

CCtlBase641::CCtlBase641()
	{
	}
	
void CCtlBase641::ConstructL()
	{
	TFontSpec spec(_L("Arial"),240);
	iFont = iCoeEnv->CreateScreenFontL( spec );
	}
	
CCtlBase641::~CCtlBase641()
	{
 	iCoeEnv->ReleaseScreenFont(iFont);
	}
	
void CCtlBase641::WriteName( CWindowGc& aGc, const TDesC& aText ) const 
	{
	TRect rect = Rect();
	rect.Shrink( 3, 3 );
	aGc.UseFont( iFont );
	TInt ascent = ( rect.iBr.iY - rect.iTl.iY-iFont->HeightInPixels() ) / 2 + iFont->AscentInPixels();
	aGc.SetPenColor( KRgbBlack );
	aGc.SetBrushStyle( CGraphicsContext::ESolidBrush );
	aGc.DrawText( aText, rect, ascent, CGraphicsContext::ERight );	
	}
		
void CCtlBase641::DoDraw( CWindowGc& aGc, TRect aRect ) const
	{
	aGc.DrawRect( aRect );
	aRect.Shrink( 1, 1 );
	aGc.SetBrushStyle( CGraphicsContext::ESolidBrush );
	aGc.DrawRect( aRect );
	WriteName( aGc, *iName );
	}

