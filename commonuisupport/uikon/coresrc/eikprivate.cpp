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

#include "eikprivate.h"
#include <eikenv.h>
#include "eikenvinterface.h"


//
// class TUnlimitedFileName, used by CEikonEnv
//
TUnlimitedFileName* TUnlimitedFileName::NewLC(const TDesC& aString)
	{ // static
	const TInt maxLength = Max(KMaxFileName, aString.Length());
	// Get the mempory required
	TUnlimitedFileName* const fakeFileName = STATIC_CAST(TUnlimitedFileName*, User::AllocLC(_FOFF(TUnlimitedFileName, iBuf[maxLength])));
	// Create the TUnlimitedFileName object inside the memory
	new(fakeFileName) TUnlimitedFileName(aString, maxLength);
	return fakeFileName;
	}



//
// class CEikLafEnv
//
CEikLafEnv::CEikLafEnv () : iEikonEnv_(*CEikonEnv::Static())
	{
	}

TDisplayMode CEikLafEnv::DefaultDisplayMode() const
	{
	return iEikonEnv_.DefaultDisplayMode();
	}

const CFont* CEikLafEnv::Font(const TLogicalFont& aLogicalFont) const
	{
	return iEikonEnv_.Font(aLogicalFont);
	}

const CFbsBitmap* CEikLafEnv::Bitmap(TUid aBmpUid) const
	{
	return iEikonEnv_.Bitmap(aBmpUid);
	}

TRgb CEikLafEnv::ControlColor(TLogicalColor aLogicalColor, const CCoeControl& aControl) const
	{
	return iEikonEnv_.ControlColor(aLogicalColor, aControl);
	}

TRgb CEikLafEnv::Color(TLogicalColor aLogicalColor, TUid aColorListUid) const
	{
	if(aColorListUid!=KNullUid)
		return iEikonEnv_.ColorList().ColorArray(aColorListUid)->Color(aLogicalColor);
	else
		return iEikonEnv_.Color(aLogicalColor);
	}

//
// class CEikLogicalBorder
// Implements the MGulLogicalBorder interface, forwarding any calls to the static LafEnv implementation.
//
void CEikLogicalBorderProxy::Draw(const TGulBorder& aBorder, CGraphicsContext& aGc, const TRect& aRect, const TGulBorder::TColors& aBorderColors) const
	{
	LafEnv::DrawLogicalBorder(aBorder,aGc,aRect,aBorderColors);	
	}

TMargins CEikLogicalBorderProxy::Margins(const TGulBorder& aBorder) const
	{
	return LafEnv::LogicalBorderMargins(aBorder);
	}


//
// class MEikPictureFactory
//

/** Gets the Id of the picture factory.

@return The UID. */
EXPORT_C TUid MEikPictureFactory::Id() const
//
// Only needs to be implemented for factories that may be removed at run-time
//
	{
	return KNullUid;
	}

EXPORT_C void MEikPictureFactory::MEikPictureFactory_Reserved_1()
	{}

EXPORT_C void MEikPictureFactory::MEikPictureFactory_Reserved_2()
	{}



//
// class MEikAlertWin
//
EXPORT_C CCoeControl* MEikAlertWin::AsCoeControl()
	{
	return NULL;
	}
	
EXPORT_C void MEikAlertWin::MEikAlertWin_Reserved2()
	{
	}

EXPORT_C void MEikAlertWin::MEikAlertWin_Reserved3()
	{
	}

//
// class MEikDebugKeys
//
EXPORT_C void MEikDebugKeys::MEikDebugKeys_Reserved1()
	{
	}

EXPORT_C void MEikDebugKeys::MEikDebugKeys_Reserved2()
	{
	}

EXPORT_C void MEikDebugKeys::MEikDebugKeys_Reserved3()
	{
	}


