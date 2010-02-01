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
// Tests border drawing using border colour & style.
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code
*/

#ifndef		__T_NONFOCUSSTEP_H
#define		__T_NONFOCUSSTEP_H


#include "appfwk_test_AppUi.h"

_LIT(KTestNonFocusStep, "T_NonFocus");



//!  A CTestBrdrColStep test class. 
/**
 Tests border drawing using border colour & style.
*/
class CTestNonFocusStep : public CTmsTestStep
	{
public:
	CTestNonFocusStep();
	~CTestNonFocusStep();
	//virtual TVerdict doTestStepPreambleL();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CEikonEnv* aCoe);
private:
	
	
	};


//!  CSimpleControl. 
/**
 A simple control on which all tests are carried out.
*/
class CSimpleNonFocusControl : public CCoeControl
    {
public:
    void ConstructL();
	~CSimpleNonFocusControl();

private: // framework
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

	};

//!  CSimpleAppUi. 
/**
 UI class to CTestFocusStep test step class.
*/
class CSimpleNonFocusAppUi : public CTestCoeAppUi
    {
public:
	CSimpleNonFocusAppUi(CTmsTestStep* aStep):
	  CTestCoeAppUi(aStep) {}
    void ConstructL();
	~CSimpleNonFocusAppUi();
private:
    CSimpleNonFocusControl* iSimpleNonFocusControl;
private:
 	virtual void RunTestStepL(TInt aNextStep); 
   };


#endif


