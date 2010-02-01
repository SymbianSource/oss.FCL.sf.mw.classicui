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

#ifndef		__T_FOCUSSTEP_H
#define		__T_FOCUSSTEP_H


#include "appfwk_test_AppUi.h"

_LIT(KTestFocusStep, "T_Focus");



//!  A CTestBrdrColStep test class. 
/**
 Tests border drawing using border colour & style.
*/
class CTestFocusStep : public CTmsTestStep
	{
public:
	CTestFocusStep();
	~CTestFocusStep();
	//virtual TVerdict doTestStepPreambleL();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CEikonEnv* aCoe);
private:
	};


//!  CSimpleControl. 
/**
 A simple control on which all tests are carried out.
*/
class CSimpleFocusControl : public CCoeControl
    {
public:
    void ConstructL();
	~CSimpleFocusControl();

private: // framework
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

	};

//!  CSimpleAppUi. 
/**
 UI class to CTestFocusStep test step class.
*/
class CSimpleFocusAppUi : public CTestCoeAppUi
    {
public:
	CSimpleFocusAppUi(CTmsTestStep* aStep):
	  CTestCoeAppUi(aStep) {}
    void ConstructL();
	~CSimpleFocusAppUi();
private:
    CSimpleFocusControl* iSimpleFocusControl;
private:
 	virtual void RunTestStepL(TInt aNextStep); 
   };


#endif


