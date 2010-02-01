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


#if !defined(__TCONE0STEP_H__)
#define __TCONE0STEP_H__

#include <test/testexecutestepbase.h>
#include "TConeTestServer.h"
#include "appfwk_test_AppUi.h"

//! A CTestStep Derived Class.\n

/**   Incorporates the tests to create a sample application and 
      handle the key events.\n  */

class CTCone0Step : public CTmsTestStep
	{
public:
	CTCone0Step();
	~CTCone0Step();
//	virtual TVerdict doTestStepPreambleL();
//	virtual TVerdict doTestStepPostambleL();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CCoeEnv* aCoe);

private:
	};
//! A CTestCoeAppUi derived Class.\n

/**   App Ui class for the TCone0Step.\n */

class CCone0TestAppUi : public CTestCoeAppUi
    {
public:
	CCone0TestAppUi(CTmsTestStep* aStep);
	~CCone0TestAppUi();
	void ConstructL();
private: // from CCoeAppUi
    TKeyResponse HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
    void HandleForegroundEventL(TBool aForeground);
private: // utility
	void Beep(TInt aFrequency);
	void RunTestStepL(TInt aStepNum);
	void TestStepKeyDownL(TKeyEvent aKeyEvent);
	void TestStepKeyUpL(TKeyEvent aKeyEvent);
    };

//! Cone0 Test Step Name
_LIT(KTCone0Step,"TCone0");

#endif


