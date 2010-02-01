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
// Tests CEikStatusPane APIs.\n
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code
*/

#ifndef __TSPANE_H
#define __TSPANE_H

#include <coecntrl.h>
#include <coeccntx.h>

#include <eikappui.h>
#include <eikapp.h>
#include <eikdoc.h>
#include <e32std.h>
#include <eikspane.h>
#include <techview/eikcmbut.h>
#include <techview/eikgted.h>


#include "appfwk_test_AppUi.h"

//const TUid KUidTspaneApp={ 0x0000012b };

_LIT(KTestSpaneStep, "TSpane");

//! CTspaneContainer
/**
Container control for test step.
*/
class CTspaneContainer : public CCoeControl, public MEikStatusPaneObserver
    {
public:
	enum TAutoTest
		{
		ETotal=-3,
		EOOM,
		EAllNormal,
		EObserver,
			EBackground,
		ENew,
		EReduceRect,
		ESwitchLayout,
		ECaps,
	 
		ERect,
		EControl,
		ESwap,
		EContainer,
		ENumNormalTests
		};
public:
    void ConstructL(const TRect& aRect);
    ~CTspaneContainer();
	
	void AutoTestL(TAutoTest aTestId);
	void ReportState();
	void SwitchVis();
	void SwitchDim();
	void SwitchFade();
	void SwitchLayoutL();
	void BoundingRectOfRegionL();
	void SwitchControlL(TBool aFocus=ETrue);

private:
	void Draw(const TRect& aRect) const;
	void HandleStatusPaneSizeChange();

private:
	void AutoTestOom();
	void AutoTestObserverL();
	void AutoTestReduceL();
	void AutoTestSwitchL();
	void AutoTestCapsL();
	void AutoTestRectL();
	void AutoTestControlL();
	void AutoTestSwapL();
	void AutoTestContainerL();
//FC
void AutoTestBackgroundL();
void SwapBackgroundTestControlL(TInt aControlType);
	void AutoTestNewL();
	void AutoTestAppOverridesL();
	void AutoTestBadDefaultLayoutL();
	void AutoTestBadOverrideLayoutL();
	void AutoTestBadOverridePaneL();

	void CreateStatusPaneL();

private:
	class TSpaneObserver : public MEikStatusPaneObserver
		{
	public:
		TSpaneObserver() : iState(EFalse) {}
		void Reset() { iState = EFalse; }
		TBool Test() { return iState; }
	private:
		void HandleStatusPaneSizeChange() { iState = ETrue; }
	private:
		TBool iState;
		};

private:
	CEikStatusPane* iStatusPane;
	TSpaneObserver iObs1;
	TSpaneObserver iObs2;
	TInt iLayoutNum;
	TInt iControlNum;
    };




//! CTspaneEikDocument
/**
Document class for test step.
*/
class CTspaneEikDocument : public CEikDocument
	{
public:
	void ConstructL();
	CTspaneEikDocument(CEikApplication& aApp): CEikDocument(aApp) { }
	~CTspaneEikDocument() {}
	// Stop doc file being created
	CFileStore* OpenFileL(TBool /*aDoOpen*/,const TDesC& /*aFilename*/,RFs& /*aFs*/) {return NULL;}
private:
	// from CEikDocument
	CEikAppUi* CreateAppUiL();
	};

//! CFloatingSpaneKiller
/**
Floating status pane control.
*/
class CFloatingSpaneKiller : public CEikTextButton, public MCoeControlObserver
	{
public:
	~CFloatingSpaneKiller();
	static CFloatingSpaneKiller* NewL(CEikStatusPane* aSpane, RWindowGroup* aWg);
	void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
private:
	CFloatingSpaneKiller(CEikStatusPane* aSpane, RWindowGroup* aWg);
	void ConstructL();
private:
	CEikStatusPane* iSpane;
	RWindowGroup* iWg;
	};


//! CTspaneAppUi
/**
UI class for test step.
*/
class CTspaneAppUi : public CTestAppUi
    {
public:
	CTspaneAppUi(CTmsTestStep*		aStep);
    void ConstructL();
	~CTspaneAppUi();
private: // from CEikAppUi
	void HandleCommandL(TInt aCommand);
	void CreateNewWindowGroupL();
	void RunTestStepL(TInt aNumStep);
private:
    CTspaneContainer* iAppView;
	CFloatingSpaneKiller*	iFloatingPanel;

    };




//! CTestSpaneStep
/**
Class tests status pane.
*/
class CTestSpaneStep : public CTmsTestStep
	{
public:
	CTestSpaneStep();
	~CTestSpaneStep();
	//virtual TVerdict doTestStepPreambleL();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CEikonEnv* aCoe);
private:
	};


//! CControlStackedGlobalTextEditor
/**
Global text editor control.
*/
class CControlStackedGlobalTextEditor : public CEikGlobalTextEditor
	{
public:
	inline CControlStackedGlobalTextEditor(const TGulBorder& aBorder) :CEikGlobalTextEditor(aBorder) {}
	virtual ~CControlStackedGlobalTextEditor();
	};


#endif
