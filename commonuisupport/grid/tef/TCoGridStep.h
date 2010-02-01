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

#if (!defined __TCOGRID_STEP_H__)
#define __TCOGRID_STEP_H__

#include <basched.h>
#include <coemain.h>
#include <coeaui.h>
#include "COEGRID.H"
#include <grdstd.h>
#include "TESTIMG.H"

#include "TGridTestServer.h"
#include "appfwk_test_AppUi.h"

//! A CTestCoeAppUi Derived Class.\n

/**
  App Ui class for the TCoGridStep.\n
*/
class CTestCoeGridAppUi : public CTestCoeAppUi
	{
public:
	enum {ENoRows=200,ENoCols=200};
	enum {EPageWidthInTwips=5000,EPageHeightInTwips=2000};
public:
	CTestCoeGridAppUi(CTmsTestStep* aStep);
	virtual ~CTestCoeGridAppUi();
    virtual TKeyResponse HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
    virtual void ConstructL();
private:
	CFileStore* CreateStoreLC(RFile &aFile);
	void LoadL();
	void SaveL();
	void SetZoomFactorL(TInt aZoomFactor);
	void ChangeColors(TBool aReset);
	void RunTestStepL(TInt aNumStep);
private:
	CTestCellImg* iTestCellImg;
	CTestLabelImg* iTestLabelImg;	
	CTestGridTable* iGridTable;
	CGridWin *iGridWin;
	TZoomFactor* iZoomFactor;
	CGridLay* iGridLay;
	CGridImg* iGridImg;
	TBool iUndoColors;
	};

//! A CTestStep derived class 
/*!
 	Incorporates the tests on Grid with InDefinite Row Boundaries.\n
*/
class CTCoGridStep : public CTmsTestStep
	{
public:
	CTCoGridStep();
	~CTCoGridStep();
//	virtual TVerdict doTestStepPreambleL();
//	virtual TVerdict doTestStepPostambleL();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CCoeEnv* aEnv);
private:
	};

_LIT(KTCoGridStep,"TCoGrid");
#endif

