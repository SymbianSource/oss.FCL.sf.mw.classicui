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


#if !defined(__TCONE1STEP_H__)
#define __TCONE1STEP_H__

#include <coemain.h>
#include <coecntrl.h>
#include <coeaui.h>
#include <e32keys.h>
#include <basched.h>
#include <test/testexecutestepbase.h>
#include "TConeTestServer.h"
#include "appfwk_test_AppUi.h"

//! A CTestStep Derived Class.\n

/**  Incorporates the tests on CCoeControl APIs and handling of 
	 Key and Pointer Events.\n
*/

class CTCone1Step : public CTmsTestStep
	{
public:
	CTCone1Step();
	~CTCone1Step();
//	virtual TVerdict doTestStepPreambleL();
//	virtual TVerdict doTestStepPostambleL();
	virtual TVerdict doTestStepL();
	void ConstructCone1AppL(CCoeEnv* aCoe);

private:
	};

class CCone1TestAppUi;

//! A CCoeControl Derived Class.\n

/**   Incorporates the tests on CCoeControl APIs and handling of 
	  Key and Pointer Events.\n  */

class CTestControl : public CCoeControl
    {
friend class CCone1TestAppUi;
public:
    void ConstructL();
    ~CTestControl();
protected: // framework
    TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
    void HandlePointerEventL(const TPointerEvent& aPointerEvent);
private: // framework
    void Draw(const TRect& aRect) const;
	void FocusChanged(TDrawNow aDrawNow);
private: // new functions
    void CreateFontL();
    void DrawBorder() const;
    void DrawMessage() const;
    void DrawMessageNow() const;
private:
	//! Message to be displayed on the control.\n
    TBuf<40> iMessage;
    //! Font interface for the control.\n
    CFont* iFont;
    };
//! A CTestCoeAppUi Derived Class.\n

/**   App Ui class for the TCone1Step.\n */

class CCone1TestAppUi : public CTestCoeAppUi
    {
public:
	CCone1TestAppUi(CTmsTestStep* aStep);
	~CCone1TestAppUi();
public:	// from CCoeAppUi
	void ConstructL();
private:
	void RunTestStepL(TInt aStepNum);
	void TestKeyDownL();
	void TestButtonDownL();
	void TestDoubleClickL();
	void TestCtrlKeyDownKeyRightArrowL();
	void TestCtrlKeyDownKeyLeftArrowL();
	void TestCtrlKeyDownKeyDownArrowL();
	void TestCtrlKeyDownKeyUpArrowL();
private:
	//! Control used to test CCoeControl APIs.\n
	CTestControl* iControl;
    };

//! TCone1 Test Step Name.\n
_LIT(KTCone1Step,"TCone1");

#endif


