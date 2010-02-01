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

#if (!defined __T_COLOR_STEP_H__)
#define __T_COLOR_STEP_H__
#include <test/testexecutestepbase.h>
#include "TEgulTestServer.h"
#include <gulcolor.h>
#include <coecntrl.h>
#include "appfwk_test_AppUi.h"


class CT_ColorStep : public CTmsTestStep
	{
public:
	enum TTestCase
		{
		ETestColorArray = 1,
		ETestColorList,
		ETestColorUtils,
		ETestColorOom,
		ETestFileLength,
		ETestFileCorrupt
		};
public:
	CT_ColorStep();
	~CT_ColorStep();
	virtual TVerdict doTestStepL();
public:
	void TestColorArrayL();
	CColorList* TestColorListLC();
	void TestColorUtilsL(CColorList& aColorList);
	void TestColorOomL();
	void FileLengthTestL();
	void CorruptFileTestL();
private:
	void ConstructAppL(CEikonEnv*);
	void DoOomTestsL();
	static void SetSystemColorSchemeL(const TDesC8& aBuffer);
private:
	RFs iFs;
	};


class CSimpleColorControl : public CCoeControl
    {
public:
	void ConstructL();
private:
	void Draw(const TRect& aRect) const;
	};

class CTestColorUi  : public CTestAppUi
	{
public:
	CTestColorUi(CT_ColorStep& aStep);
	virtual ~CTestColorUi();
	void ConstructL();
private:
	virtual void RunTestStepL(TInt aStep);
	void DoRunTestStepL(TInt aStep);
private:
	CT_ColorStep& iColorStep;
	CSimpleColorControl* iControl;
	CColorList* iColorList;
	CAutoTestManager::TTestResult iTestResult;
	};

_LIT(KT_ColorStep,"T_Color");
#endif

