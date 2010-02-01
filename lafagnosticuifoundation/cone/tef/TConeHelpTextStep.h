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


#if !defined(__TCONEHELPTEXTSTEP_H__)
#define __TCONEHELPTEXTSTEP_H__

#include <test/testexecutestepbase.h>
#include "TConeTestServer.h"
#include "appfwk_test_AppUi.h"

//! A CTestStep Derived Class.\n

/**   Incorporates the tests to create a sample application and 
      handle the key events.\n  */

class CTConeHelpTextStep : public CTmsTestStep
	{
public:
	CTConeHelpTextStep();
	~CTConeHelpTextStep();
//	virtual TVerdict doTestStepPreambleL();
//	virtual TVerdict doTestStepPostambleL();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CCoeEnv* aCoe);

private:
	};
//! A CTestCoeAppUi derived Class.\n

/**   App Ui class for the TConeErrorMsgStep.\n */

class CConeHelpTextTestAppUi : public CTestCoeAppUi
    {
public:
	CConeHelpTextTestAppUi(CTmsTestStep* aStep);
	~CConeHelpTextTestAppUi();
	void ConstructL();
private: // utility
	void TestCase01();
	void TestCase02();
	void TestCase03();
	void TestCase04();
	void TestCase05();
	void TestCase06();
	void TestCase07();
	void TestCase08();
	void RunTestStepL(TInt aStepNum);
	void CloseDialogsL();
	void TestErrorDialogL(const TDesC8& aTestCaseName,
			const TDesC& aTestCompareMbm,
			const TDesC* aDbgBmp=NULL,
			const TDesC* aDbgConvBmp=NULL,
			const TDesC* aDbgConvCompBmp=NULL,
			const TDesC* aDbgMbm=NULL);
	void TestLeaveWithErrorText(const TDesC& aErrorText, const TDesC* aContextErrorText=NULL, const TBool& aExceedMaxDesc=NULL);
	void ConvertToBmp(const CFbsBitmap* aBitmap, const TDesC* aFileName);
private:
	RFs iFs;
	RWsSession iWs;
    };

//! TConeErrorMsg Test Step Name
_LIT(KTConeHelpTextStep,"TConeHelpText");


#endif


