// Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef __COECNTSS_H__
#define __COECNTSS_H__

#include <coemain.h>	// class CCoeStatic

/** Holds global settings for all CCoeControls.

This class is not designed for general use. It is intended to be used
to override certain settings on a system-wide basis at startup. At present, the
only settings it contains are 
1. To set whether or not CCoeControls take focus on
creation. By default, a CCoeControl does take focus - this class can be used to
change that. To use it, CCoeControlStaticSettings::SetFocusedByDefaultL() should
be called from a "start-up" DLL to set the default once. Changing the default on
the fly will almost certainly cause instability.
2. To set whether the CC
@publishedPartner This class should only be used by developers of User Interfaces for Symbian OS phones.
@released
*/
class CCoeControlStaticSettings : public CCoeStatic
	{
public:
	IMPORT_C static void SetFocusedByDefaultL(TBool aFocusedByDefault);
	IMPORT_C static TBool FocusedByDefault();
	IMPORT_C static TBool FocusedByDefault(CCoeEnv* aCoeEnv);
	IMPORT_C static void SetParentByDefaultL(TBool aParentByDefault);	// deprecated
	IMPORT_C static TBool ParentByDefault();	// deprecated
	IMPORT_C static const TDesC& SystemTypeface();
	IMPORT_C static void SetSystemTypefaceL(const TDesC& aTypeface);		
	IMPORT_C static void GetLogicalToPixelFontSizesL(RArray<TInt>& aLogicalToPixelSizes);
	IMPORT_C static void SetLogicalToPixelFontSizesL(const RArray<TInt>& aLogicalToPixelSizes);
	IMPORT_C static void SetOrdinalForAllViewsL(TBool aOrdinalForAllViews);
	IMPORT_C static TBool OrdinalForAllViews();
private:
	CCoeControlStaticSettings();
	~CCoeControlStaticSettings();
	static CCoeControlStaticSettings* Self(CCoeEnv* aCoeEnv=NULL);

    static CCoeControlStaticSettings* NewL();
	void ConstructL();
private:
	TBool iFocusedByDefault;
	TBool iOrdinalForAllViews;
	TTypeface iTypeface;
	RArray<TInt> iLogicalToPixelSizes;
	};

#endif	// __COECNTSS_H__
