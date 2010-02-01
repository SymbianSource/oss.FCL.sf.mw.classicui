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

#ifndef __EIKPRIVATE_H__
#define __EIKPRIVATE_H__

#include <e32std.h>		// class TBufBase16, CBase etc
#include <uiklaf/private/lafenv.h>		// class MLafEnv
#include <graphics/uigraphicsutils/gullogicalborder.h>

//
// class TUnlimitedFileName
//

/** 
This class is used to overcome TFileName's size limit of 256 characters.
Required because CEikAppUi::ProcessCommandParametersL() takes a TFileName reference as argument.
@internalTechnology
*/
NONSHARABLE_CLASS(TUnlimitedFileName) : public TBufBase16 // needs to have the same binary interface as TFileName
	{
public:
	static TUnlimitedFileName* NewLC(const TDesC& aString);
	inline TFileName& AsFileName() { return *REINTERPRET_CAST(TFileName*, this);}
private:
	inline TUnlimitedFileName(const TDesC& aString, TInt aMaxLength) : TBufBase16(aString, aMaxLength) {}
private:
	TUint16 iBuf[1];
	};

//
// class CEikLafEnv
//

/**
@internalTechnology
*/
NONSHARABLE_CLASS(CEikLafEnv) : public CBase, public MLafEnv
	{
public: // from MLafEnv
	CEikLafEnv ();
	const CFont* Font(const TLogicalFont& aLogicalFont) const;
	const CFbsBitmap* Bitmap(TUid aUidBmp) const;
	TRgb ControlColor(TLogicalColor aLogicalColor,const CCoeControl& aControl) const;
	TRgb Color(TLogicalColor aLogicalColor, TUid aColorListUid) const;
	TDisplayMode DefaultDisplayMode() const;
private:
	// the underscore is to prevent a name clash with the iEikonEnv #define
	CEikonEnv& iEikonEnv_;
	};

	
//
// class CEikLogicalBorderProxy
//

/**
@internalTechnology
*/
NONSHARABLE_CLASS(CEikLogicalBorderProxy) : public CBase, public MGulLogicalBorder
	{
public: // from MGulLogicalBorder
	void Draw(const TGulBorder& aBorder,CGraphicsContext& aGc, const TRect& aRect, const TGulBorder::TColors& aBorderColors) const;
	TMargins Margins(const TGulBorder& aBorder) const;
	};
	
	
	
#endif	// __EIKPRIVATE_H__
