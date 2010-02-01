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


#if !defined(__TCONE6STEP_H__)
#define __TCONE6STEP_H__

#include <test/testexecutestepbase.h>
#include "TConeTestServer.h"
#include "appfwk_test_AppUi.h"
#include <coecntrl.h>

//! A CCoeControl derived Class.\n
/**
  Base class used to derive CCtlContainer and CCtlContainee classes.\n
*/
class CCtlBase : public CCoeControl
	{
public:
	~CCtlBase();
protected:
	CCtlBase();
	void WriteName( CWindowGc& aGc, const TDesC& aText ) const ;
	void ConstructL() ;
	void DoDraw( CWindowGc& aGc, TRect aRect ) const ;	
protected:
	HBufC* iName;
private:
    CFont* iFont;
	};

//! A CTestStep Derived Class.\n
/**
  Incorporates the tests on component-container control interface.\n
*/
class CTCone6Step : public CTmsTestStep
	{
public:
	CTCone6Step();
	~CTCone6Step();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CCoeEnv* aCoe);
	};
	
//! A CCtlBase Derived Class.\n
/**
  Implements the containee class.\n
*/	
class CCtlContainee : public CCtlBase
	{
public:
	CCtlContainee() ;
	~CCtlContainee() ;
	void ConstructL( const TDesC& aName ) ;
	const TDesC& WhoAmI() const ;
private:
	void Draw(const TRect& aRect) const ;
	
	};
	
//! A CCtlContainee Derived Class.\n
/**
  Implements the containee class but cannot get any parent.\n
*/	
class CCtlUnparentableContainee : public CCtlContainee
	{
public: //from CCtlContainee
	TInt SetParent(CCoeControl* /*aParent*/) { return KErrNotSupported; }
	};

//! A CCtlBase Derived Class.\n
/**
  Implements the container class.\n
*/	
class CCtlContainer : public CCtlBase
	{
public:
	CCtlContainer();
	~CCtlContainer();
	void ConstructL(const TDesC& aName);
	TBool TestRemoveControlById();
	TBool TestCleanupL();
	TBool TestGetControlL();
	TBool TestGetControlConstL() const;
	TBool TestGetUnknownControlConstL() const ;
	TBool TestAddDuplicateControlL() ;
	TBool TestRemoveNonExistantById() ;
	TBool TestRemoveControlL() ;
	TBool TestGetUnsetUniqueHandle() ;
	TBool TestSetUniqueHandle() ;
	TBool TestGetUniqueHandle() ;
	TBool TestSetUniqueHandleOOM() ;
	TBool TestInsertAfter(); 
	TBool TestInsertLast();
	TBool TestFailingInsertAfter();
	TBool TestId();
	TBool TestCursor();
	TBool TestFind();
	TBool TestRemove();
	TBool TestReplace();
	TBool TestSetArrayLocked();
	TBool TestSort();
	TBool TestOwnedExternally();
	void TestHandleDestructionOfFocusedItemL();
	static TInt CompareControls(const TCoeControlWithId& aFirst, const TCoeControlWithId& aSecond);	
private:
	virtual void SizeChanged() ;
	void Draw(const TRect& aRect) const ;
private:
	CCtlContainee* iOrphan;
//! Child Control Identifiers.\n
	enum
		{
		KChildOneID,
		KChildTwoID,
		KChildThreeID,
		KChildFourID,
		KChildFiveID,
		KChildSixID
		};
	};

// A MCoeFocusObserver derived class.\n

/**  
  Implements MCoeFocusObserver derived class.\n 
*/
class CTestMCoeFocusObserver : public CBase, public MCoeFocusObserver
	{
public:
	~CTestMCoeFocusObserver();
	CTestMCoeFocusObserver(CCoeControl& aContainer);
	//from MCoeFocusObserver
	void HandleDestructionOfFocusedItem();
	void HandleChangeInFocus();
private:
	CCoeControl& iCtlContainer;
	};

// A CCoecontrol derived class.\n

/**  
  Implements CCoeControl derived class.\n 
*/
class CParentControl : public CCoeControl
	{
public:
	CCoeControlArray& Components() { return CCoeControl::Components(); }
	void InitComponentArrayL() { CCoeControl::InitComponentArrayL(); }
	};
	
//! A CTestCoeAppUi derived class.\n
/**
  AppUi Class for TCone6Step.\n
*/	
class CCone6TestAppUi : public CTestCoeAppUi
    {
public:
	CCone6TestAppUi(CTmsTestStep* aStep);
	~CCone6TestAppUi();
	void ConstructL();
private: // from CCoeAppUi
	TKeyResponse HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
private: // utility
	void RunTestStepL(TInt aStepNum);
	void ReinitializeContainerL();
    //! Pointer to the container control.\n
	CCtlContainer* iContainer ;
    };

//! TCone6 Test Step Name.\n
_LIT(KTCone6Step,"TCone6");

#endif


