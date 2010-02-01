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

#if !defined(__TMSGWIN0STEP_H__)
#define __TMSGWIN0STEP_H__

#include <clock.h>
#include <coecntrl.h>
#include <test/testexecutestepbase.h>
#include "TClockTestServer.h"
#include "appfwk_test_AppUi.h"

class CTMsgWin0Step : public CTmsTestStep
	{
public:
	CTMsgWin0Step();
	~CTMsgWin0Step();
//	virtual TVerdict doTestStepPreambleL();
//	virtual TVerdict doTestStepPostambleL();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CCoeEnv* aCoe);


private:
	};

enum
	{
	EGapLeftOfMessageWindowText=3,
	EGapRightOfMessageWindowText=3,
	EGapAboveMessageWindowText=4,
	EGapBelowMessageWindowText=2
	};

// classes
class CTMsgWinTestAppUi;

class CClkMsgWinControl : public CCoeControl
	{
friend class CTMsgWinTestAppUi;
public:
	CClkMsgWinControl();
	void ConstructL();
	virtual ~CClkMsgWinControl();
private:
	// functions overriding those in CCoeControl
	virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
	virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	virtual void Draw(const TRect& aRect) const;
	// miscellaneous functions
	TSize WindowSize(const CFbsFont& aFont, const TDesC& aText) const;
private:
	TRgb iBackgroundColor;
	RAnimDll iAnimDll;
	CFbsFont* iFont;
	CCoeControl* iDummy;
	RBlankWindow* iBlankWindow;
	RMessageWindow* iMessageWindow;
	TInt iCounter;
	TPoint iPointerOffset;
	};

class CTMsgWinTestAppUi : public CTestCoeAppUi
    {
public:
	CTMsgWinTestAppUi(CTmsTestStep* aStep);
	void ConstructL();
private:
	CClkMsgWinControl* iControl;
	void RunTestStepL(TInt aStep);
    };

_LIT(KTMsgWin0Step,"TMsgWin0");

#endif
