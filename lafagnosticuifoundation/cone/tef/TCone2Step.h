// Copyright (c) 2007-2010 Nokia Corporation and/or its subsidiary(-ies).
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


#if !defined(__TCONE2STEP_H__)
#define __TCONE2STEP_H__


#include <test/testexecutestepbase.h>
#include "TConeTestServer.h"
#include "appfwk_test_AppUi.h"


class CTCone2Step : public CTmsTestStep
	{
public:
	CTCone2Step();
	~CTCone2Step();
	virtual TVerdict doTestStepL();
	void ConstructCone2AppL(CCoeEnv* aCoe);
private:
	};



//! A CCoeControl Derived Class.\n
/**  A Simple control.\n */

class CTestCone2Control : public CCoeControl
	{
public:
	DECLARE_TYPE_ID(0x10004C77)
	void ConstructL();
	TInt CreateWindow();
private: // from CCoeControl
	void MakeVisible(TBool aVisible);
public:
	TBool iDisplayed;
	};


//! A CCoeControl Derived Class.\n
/**   A container control. Tests container to component interface.\n */

class CTestContainerControl : public CCoeControl
	{
public:
    ~CTestContainerControl();
	void ConstructL();
	TBool IsDialogControlVisible() const;
	CTestCone2Control* GetComponentControl();
private: // from CCoeControl
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt aIndex) const;
private:
	//! Component control of class CTestCone2Control.\n
	CTestCone2Control* iDialogCtrl;
    };

class CTestAppUi;


//! A CBase Derived Class.\n
/**   The CTestDriver class runs a series of tests on timer callback.\n */

class CTestDriver : public CBase
	{
public:
	CTestDriver(CCoeAppUi& aAppUi,CTestStep* aStep);
	~CTestDriver();
	void ConstructL();
public:
	void TestIsDisplayingDialogAndRemoveFromStackAPIsL();
	void TestMakeVisibleOnChildControlsL();
	void TestAppHelpContextAPIL();
	void TestSetAndGetSystemDefaultViewAPIsL();
	void TestCoeControlAPIsL();
	void TestColorUseAPIsL();
	void TestConeMiscAPIsL();
	void TestConeInputCapabilitiesAPIs();
	void TestReadResourceAPIsL();
	void TestSetandGetCCoeControlAPIsL();
	void TestLowMemoryCoeControl();
	inline CTestExecuteLogger& Logger() {return iStep->Logger();}
private:
	//! Handle to AppUi Class.\n
	CCoeAppUi& iAppUi;
	//! Resource File Id.\n
	TInt iResourceFileFlag;
	//! Pointer to CTestStep.\n
	CTestStep* iStep;
	};


//! A CTestCoeAppUi Derived Class.\n

/**   App Ui class for the TCone2Step.\n */

class CCone2TestAppUi : public CTestCoeAppUi
    {
public:
	CCone2TestAppUi(CTmsTestStep* aStep);
    ~CCone2TestAppUi();
    void ConstructL(CTmsTestStep* aStep);
private:
	CTestDriver* iDriver;
	void RunTestStepL(TInt aStepNum);
    };

//! TCone 2 Test Step Name.\n
_LIT(KTCone2Step,"TCone2");

#endif


