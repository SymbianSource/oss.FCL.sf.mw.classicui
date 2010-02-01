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

#if (!defined __T_DIGITWIDTH_STEP_H__)
#define __T_DIGITWIDTH_STEP_H__
#include <test/testexecutestepbase.h>
#include "TEgulTestServer.h"
#include <gulcolor.h>

class CT_DigitWidth : public CTestStep
	{
public:
	CT_DigitWidth();
	~CT_DigitWidth();
	virtual TVerdict doTestStepL();
	void test(TInt aResult);

private:
	void TestFontsL();
	void DoTestsL();
	TInt TestFindWidthOfWidestDigitType(CFont* aFont, TDigitType aDigitType);
	};

_LIT(KTestFontName, "TestFont");

class CTestFont : public CFont
	{
public:
	CTestFont(CT_DigitWidth* aDigitWidth);
	~CTestFont();
	virtual TUid DoTypeUid() const;
	TInt DoHeightInPixels() const;
	TInt DoAscentInPixels() const;
	TInt DoCharWidthInPixels(TChar aChar) const;
	TInt DoTextWidthInPixels(const TDesC& aText) const;
	TInt DoBaselineOffsetInPixels() const;
	TInt DoTextCount(const TDesC& aText,TInt aWidthInPixels) const;
	TInt DoTextCount(const TDesC& aText,TInt aWidthInPixels,TInt& aExcessWidthInPixels) const;
	TInt DoMaxCharWidthInPixels() const;
	TInt DoMaxNormalCharWidthInPixels() const;
	TFontSpec DoFontSpecInTwips() const;
private:
	CT_DigitWidth* iDigitWidth;
	};


_LIT(KT_DigitWidth,"T_DigitWidth");


#endif
