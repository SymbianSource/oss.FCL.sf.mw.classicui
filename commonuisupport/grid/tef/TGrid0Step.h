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

#if (!defined __TGRID0_STEP_H__)
#define __TGRID0_STEP_H__
#include <basched.h>
#include <coemain.h>
#include <coeaui.h>
#include "COEGRID.H"
#include <grdstd.h>
#include "TIMG0.H"

#include "TGridTestServer.h"
#include "appfwk_test_AppUi.h"

//! A CTestCoeAppUi derived Class.\n
/**
	 App Ui class for the TGrid0Step.\n
*/

class CTestGridAppUi : public CTestCoeAppUi
	{
public:
	enum
		{
		ENoRows=200,ENoCols=200
		};
	enum
		{
		EGridXPos=40,EGridYPos=40,
		EGridWidth=560,EGridHeight=160
		};
	enum 
		{
		EPageWidthInTwips=5000,EPageHeightInTwips=2000
		};
public:
	CTestGridAppUi(CTmsTestStep* aStep);
	virtual ~CTestGridAppUi();
    virtual TKeyResponse HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
    virtual void ConstructL();
private:
	CFileStore* CreateStoreLC(RFile &aFile);
	TBool LoadL(TCellRef& aCursorPos);
	void SaveL();
	void SetZoomFactorL(TInt aZoomFactor);
	void ChangeColors(TBool aReset);
	void RunTestStepL(TInt aNumStep);
private:
	CSheetCellImg* iSheetCellImg;
	CSheetLabelImg* iSheetLabelImg;	
	MGridTable* iGridTable;
	CGridWin *iGridWin;
	TZoomFactor* iZoomFactor;
	CGridLay* iGridLay;
	CGridImg* iGridImg;
	TBool iUndoColors;
	CTGridQueryDialog* iDialog;
	};

//! A CTestStep derived class 
/*!
	Incorporates the tests on Grid with Definite Row Boundaries.\n
*/

class CTGrid0Step : public CTmsTestStep
	{
public:
	CTGrid0Step();
	~CTGrid0Step();
//	virtual TVerdict doTestStepPreambleL();
//	virtual TVerdict doTestStepPostambleL();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CCoeEnv* aCoe);
private:
	};

_LIT(KTGrid0Step,"TGrid0");
#endif


