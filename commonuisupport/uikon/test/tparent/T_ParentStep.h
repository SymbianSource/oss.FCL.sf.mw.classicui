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
// Tests whether container windows have their parents set by default.
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code
*/

#ifndef		__T_ParentSTEP_H
#define		__T_ParentSTEP_H


#include "appfwk_test_AppUi.h"

_LIT(KTestParentStep, "T_Parent");


//!  A CTestBrdrColStep test class. 
/**
 Tests that a control has its parent set to the container window
*/
class CTestParentStep : public CTmsTestStep
	{
public:
	CTestParentStep();
	~CTestParentStep();
	
	virtual TVerdict doTestStepL();
	void ConstructAppL(CEikonEnv* aCoe);
private:
	};


//!  CSimpleControl. 
/**
 A simple control on which all tests are carried out.
*/
class CSimpleParentControl : public CCoeControl
    {
public:
	static CSimpleParentControl* NewL(CCoeControl& aContainer, const TRect& aRect);
    void ConstructL(CCoeControl& aContainer);
	~CSimpleParentControl();

private: // framework
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

	};
//
//
// CParentTestAppView
//
//
//! A CCoeControl derived class.\n

/**   View Class for CParentTestAppView.\n */

class CParentTestAppView : public CCoeControl
    {
public:
	static CParentTestAppView* NewL(const TRect& aRect);
	
	~CParentTestAppView();
	
    inline CSimpleParentControl* GetControl(void) 
    	{
    	return iSimpleParentControl;
    	}
    
protected:
	CCoeControl* ComponentControl(TInt aIndex) const;
	TInt CountComponentControls() const;
private:
	CParentTestAppView();
	void ConstructL(const TRect& aRect);
    // Inherited from CCoeControl
	void Draw(const TRect& /*aRect*/) const;
	
private:
    CSimpleParentControl* iSimpleParentControl;
    
    };
    
//!  CSimpleAppUi. 
/**
 UI class to CTestParentStep test step class.
*/
class CSimpleParentAppUi : public CTestCoeAppUi
    {
public:
	CSimpleParentAppUi(CTmsTestStep* aStep): 
	  CTestCoeAppUi(aStep) {}
    void ConstructL();
	~CSimpleParentAppUi();

private:
 	virtual void RunTestStepL(TInt aNextStep); 
 	
 	CParentTestAppView *iParentAppView;
   };


#endif


