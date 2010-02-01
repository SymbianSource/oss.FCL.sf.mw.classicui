// Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies).
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
 @test
 @internalComponent - Internal Symbian test code  
*/

#if (!defined __T_TextResourceUtils_STEP_H__)
#define __T_TextResourceUtils_STEP_H__

#include <tulstringresourcereader.h>
#include "appfwk_test_AppUi.h"

class CT_TextResourceUtilsStep : public CTmsTestStep
	{
public:
	CT_TextResourceUtilsStep();
	~CT_TextResourceUtilsStep();
	virtual TVerdict doTestStepL();
	
private:
	void TestTextResourceUtilsWithoutCoeEnv();
	void ConstructAppL(CEikonEnv* aCoeEnv);
	};

class CT_TextResourceUtilsAppUi  : public CTestAppUi
	{
public:
	CT_TextResourceUtilsAppUi(CT_TextResourceUtilsStep& aStep);
	virtual ~CT_TextResourceUtilsAppUi();
	void ConstructL();

private:
	virtual void RunTestStepL(TInt aStep);
	void TextResourceUtilsCase1();
	void TextResourceUtilsCase2();
	void TextResourceUtilsCase3();
	void TextResourceUtilsCase4();
	void TextResourceUtilsCase5L();
	void TextResourceUtilsCase6();
	void TextResourceUtilsCase7L();
	void TextResourceUtilsCase8L();
	void TestStringResourceReaderCaseL();
	void Reset();

private:
	HBufC* iStringHolder;
	};

_LIT(KT_TextResourceUtilsStep,"t_textresourceutils");

#endif
