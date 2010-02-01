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

#include <gdi.h>
#include <coecntrl.h>

#include "tmultiptrtestchildcontrol.h"



CMultiPtrTestChildControl::CMultiPtrTestChildControl()
: iDoAppUiCallback( ETrue )
	{
	}


CMultiPtrTestChildControl::~CMultiPtrTestChildControl()
	{
 	iCoeEnv->ReleaseScreenFont(iFont);
 	delete iName;
	}
	

void CMultiPtrTestChildControl::ConstructL( const TDesC& aName )
	{
	CMultiPtrTestControlBase::ConstructL();
	iAppUi = static_cast<CConeMultiPtrCompoundTestAppUi*>(ControlEnv()->AppUi());
	
	TFontSpec spec(_L("Arial"),240);
	iFont = iCoeEnv->CreateScreenFontL( spec );
	
	iName = aName.AllocL();
	EnableDragEvents();
	}


void CMultiPtrTestChildControl::WriteName( CWindowGc& aGc, const TDesC& aText ) const 
	{
	TRect rect = Rect();
	rect.Shrink( 3, 3 );
	aGc.UseFont( iFont );
	TInt ascent = ( rect.iBr.iY - rect.iTl.iY-iFont->HeightInPixels() ) / 2 + iFont->AscentInPixels();
	aGc.SetPenColor( KRgbBlack );
	aGc.SetBrushStyle( CGraphicsContext::ESolidBrush );
	aGc.DrawText( aText, rect, ascent, CGraphicsContext::ELeft );	
	aGc.DiscardFont();
	}


void CMultiPtrTestChildControl::Draw( const TRect& ) const
	{
	CWindowGc& gc = SystemGc();
	
	TRect rect = Rect();
	gc.SetBrushColor( KRgbYellow );
	gc.DrawRect( rect );
	
	rect.Shrink( 1, 1 );
	gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
	gc.DrawRect( rect );
	
	WriteName( gc, *iName );
	}	


const TDesC& CMultiPtrTestChildControl::WhoAmI() const
	{
	return *iName;
	}


void CMultiPtrTestChildControl::HandlePointerEventL( const TPointerEvent& aPointerEvent )
	{
	TBuf<256> buf( iName->Des() );	
	RDebug::Print( _L("%S"), &buf );
	
	CMultiPtrTestControlBase::HandlePointerEventL( aPointerEvent );
	}


/**
 PV in CMultiPtrTestControlBase
*/
void CMultiPtrTestChildControl::NotifyControlL( TInt aNotify )
	{
	if( !iDoAppUiCallback )
		{
		return;
		}
	
	switch( aNotify )
		{
	case EMultiPtrTestFailed:
			iAppUi->Failed();
			break;
		
	case EmultiPtrNext:	
			iAppUi->NextSetOfEventsL();
		break;
		
	default:
		User::Leave( KErrArgument );
		break;
		}

	}

void CMultiPtrTestChildControl::SetAppUiCallback( TBool aCallback )
	{
	iDoAppUiCallback = aCallback;
	}
