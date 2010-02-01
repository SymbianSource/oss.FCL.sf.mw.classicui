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
// Testing of function CalcTextBaselineOffset introduced by PREQ527
// Testing of function CalcTextBaselineOffset introduced by PREQ527
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code
 @SYMPREQ PREQ527
 @file
 @internalComponent
 @SYMPREQ PREQ527
*/

#if !defined(__TCONE5STEP_H__)
#define __TCONE5STEP_H__

#include <coecntrl.h>
#include <coelayoutman.h>
#include <test/testexecutestepbase.h>
#include "TConeTestServer.h"
#include "appfwk_test_AppUi.h"
//! A CTestStep Derived Class.\n

/**   Incorporates the tests on Control Layout Manager support.\n  */

class CTCone5Step : public CTmsTestStep
	{
public:
	CTCone5Step();
	~CTCone5Step();
	virtual TVerdict doTestStepL();
	void ConstructCone5AppL(CCoeEnv* aCoe);
private:
	};

//! A Class derived from CObject and MCoeLayoutManager interface.\n

/**  Implements the MCoeLayoutManager interface.\n */

class CLayoutTest : public CObject, public MCoeLayoutManager
	{
public:

	~CLayoutTest();

	virtual TBool CanAttach() const;
	virtual void AttachL(CCoeControl& aCompoundControl);
	virtual void Detach(CCoeControl& aCompoundControl);
	virtual TSize CalcMinimumSize(const CCoeControl& aCompoundControl) const;
	virtual void PerformLayout();
	virtual TInt CalcTextBaselineOffset(const CCoeControl& aCompoundControl, 
		const TSize& aSize) const;
	virtual void SetTextBaselineSpacing(TInt aBaselineSpacing);
	virtual TInt TextBaselineSpacing() const;
	virtual void HandleAddedControlL(const CCoeControl& aCompoundControl, const CCoeControl& aAddedControl);
	virtual void HandleRemovedControl(const CCoeControl& aCompoundControl, const CCoeControl& aRemovedControl);
	virtual TInt HandleControlReplaced(const CCoeControl& aOldControl, const CCoeControl& aNewControl);

	TUint LayoutsPerformed() const;
	
private:
	void  LayoutRow(TInt& aCurCtrlIndex);
	void  FindRectangle();
	TInt  LayoutControl(TUint aCurCtrlIndex, TSize aCtrlSize);
	TBool SpaceForControl(TUint aMaxHeight);
	
private:
	//! array containing list of component controls.\n
	RPointerArray<CCoeControl> iCtrlArray;
	//! Index of the Control which owns the Window.\n
	TUint iWinOwningCtrlIndex;
	//! Window size already allocated to controls.\n
	TSize iSizeUsed;
	//! Rectange to be used for allocating Controls.\n
	TRect iLayoutRect;
	//! Boolean to indicate if Layout is in progress.\n 
	TBool iLayoutInProgress;
	//! Number of controls for which layout is done.\n
	TUint iControlsCompleted;
	//! Number of Layouts performed.\n
	TUint iLayoutsPerformed;
	};
	


//
//
// CTest5Control
//
//
//! A CCoeControl derived class.\n

/**   The class is used to create component controls.\n */

class CTest5Control : public CCoeControl
    {
public:
	static CTest5Control* NewL(CLayoutTest* aLayoutMan, 
		CCoeControl& aContainer, const TRect& aRect);
	~CTest5Control();
    
private:
	CTest5Control();
	void ConstructL(CLayoutTest* aLayoutMan, CCoeControl& aContainer, 
    			    const TRect& aRect);
    // Inherited from CCoeControl
	void Draw(const TRect& /*aRect*/) const;
    };


//
//
// CLayoutTestAppView
//
//
//! A CCoeControl derived class.\n

/**   View Class for TCone5Step.\n */

class CLayoutTestAppView : public CCoeControl
    {
public:
	static CLayoutTestAppView* NewL(CLayoutTest* aLayoutMan, const TRect& aRect);
	
	~CLayoutTestAppView();
	virtual TBool RequestRelayout(const CCoeControl* aChildControl);
	const RPointerArray<CTest5Control>& CtrlArray() const;
    
    
protected:
	CCoeControl* ComponentControl(TInt aIndex) const;
	TInt CountComponentControls() const;
private:
	CLayoutTestAppView();
	void ConstructL(CLayoutTest* aLayoutMan, const TRect& aRect);
    // Inherited from CCoeControl
	void Draw(const TRect& /*aRect*/) const;

private:
	//! Array containing list of component controls.\n
	RPointerArray<CTest5Control> iCtrlArray;
    };



//! A CTestCoeAppUi derived class.\n

/**   AppUi Class for TCone5Step.\n */

class CCone5TestAppUi : public CTestCoeAppUi
    {
public:
	CCone5TestAppUi(CTmsTestStep* aStep);
    ~CCone5TestAppUi();
    void ConstructL();
	void DoTestsL();
protected:
	void RunTestStepL(TInt aStepNum);
	
private:
	CLayoutTestAppView* iTestAppView;
	CLayoutTest* 		iLayoutMan;
   	};

//! TCone5 Test Step Name.\n
_LIT(KTCone5Step,"TCone5");

#endif


