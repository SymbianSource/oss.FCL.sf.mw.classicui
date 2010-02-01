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

#if !defined(__TCONEBACKGROUND_H__)
#define __TCONEBACKGROUND_H__

#include <test/testexecutestepbase.h>
#include "TConeTestServer.h"
#include "appfwk_test_AppUi.h"
//! A CTestStep Derived Class.\n

/**   Incorporates the tests on background drawing interface.\n */

class CTConeBackgroundStep : public CTmsTestStep
	{
public:
	CTConeBackgroundStep();
	~CTConeBackgroundStep();
//	virtual TVerdict doTestStepPreambleL();
//	virtual TVerdict doTestStepPostambleL();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CCoeEnv* aCoe);

private:
	};

class CConeBackgroundTestView;

//! A CTestCoeAppUi derived class.\n

/** AppUi Class for TConeBackground test step.\n */

class CConeBackgroundTestAppUi : public CTestCoeAppUi
    {
public:
	CConeBackgroundTestAppUi(CTmsTestStep* aStep);
	~CConeBackgroundTestAppUi();
	void ConstructL();
private: // utility
	void RunTestStepL(TInt aStepNum);

private:
    //! Pointer to the View Object.\n
	CConeBackgroundTestView* iView;
    };

//! Background Test Step name.\n
_LIT(KTBackgroundStep,"TBackground");

#endif


