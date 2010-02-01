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

#if !defined(__TSYSCOLOR_H__)
#define	__TSYSCOLOR_H__

#include <eikenv.h>
#include <techview/eikdialg.h>
#include <eikappui.h>
#include <eikapp.h>
#include <eikdoc.h>

#include "uiktestserver.h"
#include "appfwk_test_AppUi.h"

//!  CTSysColorControl
/**
 A simple control on which all tests are carried out.
*/
class CTSysColorControl : public CCoeControl
    {
public:
	void ConstructL(const TRect& aRect);
	};


//!  CTSysColorAppUi
/**
 UI class to CTSysColorStep test step class.
*/
class CTSysColorAppUi : public CTestAppUi
    {
public:
	CTSysColorAppUi(CTmsTestStep* aStep);
	void ConstructL();
	~CTSysColorAppUi();
protected: //from CTestAppUi
 	void RunTestStepL(TInt aNextStep); 
private://test functions
	void TestCaseSetL();
	void TestCaseGetL();
	void TestCaseCreateL();
private:
    CTSysColorControl* iTSysColorControl;
   };


//!  CTSysColorStep
/**
 Tests border drawing using border colour & style.
*/
class CTSysColorStep : public CTmsTestStep
	{
public:
	CTSysColorStep();
	~CTSysColorStep();
	virtual TVerdict doTestStepPreambleL();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CEikonEnv* aEikEnv);
private:
	};


_LIT(KTSysColorStep, "TSysColor");

#endif




