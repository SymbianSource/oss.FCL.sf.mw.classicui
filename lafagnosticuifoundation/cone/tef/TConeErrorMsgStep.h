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


#if !defined(__TCONEERRORMSGSTEP_H__)
#define __TCONEERRORMSGSTEP_H__

#include <test/testexecutestepbase.h>
#include "TConeTestServer.h"
#include "appfwk_test_AppUi.h"

//! A CTestStep Derived Class.\n

/**   Incorporates the tests to create a sample application and 
      handle the key events.\n  */

class CTConeErrorMsgStep : public CTmsTestStep
	{
public:
	CTConeErrorMsgStep();
	~CTConeErrorMsgStep();
//	virtual TVerdict doTestStepPreambleL();
//	virtual TVerdict doTestStepPostambleL();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CCoeEnv* aCoe);

private:
	};
//! A CTestCoeAppUi derived Class.\n

/**   App Ui class for the TConeErrorMsgStep.\n */

class CConeErrorMsgTestAppUi : public CTestCoeAppUi
    {
public:
	CConeErrorMsgTestAppUi(CTmsTestStep* aStep);
	~CConeErrorMsgTestAppUi();
	void ConstructL();
private: // utility
	void TestCase01L();
	void TestCase02L();
	void TestCase03L();
	void TestCase04L();
	void TestCase05L();
	void TestCase06L();
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
	void TestLeaveWithErrorTextL(const TDesC& aErrorText, const TDesC* aContextErrorText=NULL, const TBool& aExceedMaxDesc=NULL);
	void ConvertToBmpL(const CFbsBitmap* aBitmap, const TDesC* aFileName);
	TSize CalculateScreenSize();
private:
	RFs iFs;
	RWsSession iWs;
    };

//! TConeErrorMsg Test Step Name
_LIT(KTConeErrorMsgStep,"TConeErrorMsg");

class CTestCoeEnv : public CCoeEnv
	{
	public:
	inline TDes& TestErrorText() 	{ return CCoeEnv::ErrorText(); }
	inline TDes& TestErrorContextText() { return CCoeEnv::ErrorContextText(); }
	};

#endif


