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

#if !defined(__TCONE3STEP_H__)
#define __TCONE3STEP_H__

#include <test/testexecutestepbase.h>
#include "COECNTRL.H"
#include "TConeTestServer.h"
#include "appfwk_test_AppUi.h"


//! A CTestStep Derived Class.\n
/**
  Incorporates the tests on Object Provider mechanism.\n
*/

class CTCone3Step : public CTmsTestStep
	{
public:
	CTCone3Step();
	~CTCone3Step();
//	virtual TVerdict doTestStepPreambleL();
//	virtual TVerdict doTestStepPostambleL();
	virtual TVerdict doTestStepL();
	void ConstructCone3AppL(CCoeEnv* aCoe);
private:
	};

//! A CBase Derived Class.\n
/**
  Objects of this class are used as child objects to test 
  object provider mechanism .\n
*/
class CSquareObj : public CBase
	{
public:
	DECLARE_TYPE_ID(0x10004C76)
	~CSquareObj();
	void SetParentClassName(TDesC& aName);
	TPtrC GetParentClassName() const;
private:
	//! Name of the Class.\n
	TPtrC	iName;
	};

//! A CBase Derived Class.\n
/**
  Objects of this class are used as child objects to test 
  object provider mechanism .\n
*/
class COctagonObj : public CBase
	{
public:
	DECLARE_TYPE_ID(0x10004C74)
    ~COctagonObj();
	void SetParentClassName(TDesC& aName);
	TPtrC GetParentClassName() const;
private:
	//! Name of the Class.\n
	TPtrC	iName;
	};

//! A CTestCoeAppUi Derived Class.\n
/**
  App Ui class for the TCone3Step.\n
*/
class CCone3TestAppUi : public CTestCoeAppUi
    {
public:
	CCone3TestAppUi(CTmsTestStep* aStep);
    ~CCone3TestAppUi();
    void ConstructL();
	void DoTestsL();
	void DoMopConstTestsL();
	void DoMopNoChainingTestsL();
	void DoMopNoChainingConstTestsL();
	void DoStateObserverTestL();
protected:
	void RunTestStepL(TInt aStepNum);
	};

//! TCone3 Test Step Name.\n
_LIT(KTCone3Step,"TCone3");

#endif
