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


#if !defined(__TCLCK1STEP_H__)
#define __TCLCK1STEP_H__


#include <test/testexecutestepbase.h>
#include "TClockTestServer.h"
#include "appfwk_test_AppUi.h"

class CTClck1Step : public CTmsTestStep
	{
public:
	CTClck1Step();
	~CTClck1Step();
//	virtual TVerdict doTestStepPreambleL();
//	virtual TVerdict doTestStepPostambleL();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CCoeEnv* aCoeEnv);

private:
	};


class CClck1DestructableFont : public CBase
	{
public:
	CClck1DestructableFont(CWsScreenDevice* aScreenDevice);
	void ConstructL(const TFontSpec& aFontSpec);
	virtual ~CClck1DestructableFont();
	TInt Handle() const;
private:
	CWsScreenDevice* iScreenDevice; // not owned by this pointer
	CFbsFont* iFont;
	};

//
class CTestClck1Ui;
class CClk1Control : public CCoeControl
	{
friend class CTestClck1Ui;
public:
	CClk1Control();
	void ConstructL();
	virtual ~CClk1Control();
private:
	// functions overriding those in CCoeControl
	virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
	virtual void Draw(const TRect& aRect) const;
	// miscellaneous functions
	void CreateDigitalClocksL();
	void CreateAnalogClocksL();
private:
	TRgb iBackgroundColor;
	RAnimDll iAnimDll;
	RDigitalClock* iDigitalClock0;
	TPoint iDigitalClock0Position;
	TSize iDigitalClock0Size;
	RAnalogClock* iAnalogClock0;
	TPoint iAnalogClock0Position;
	TSize iAnalogClock0Size;
	TInt iUniversalTimeOffset;
	};

class CTestClck1Ui  : public CTestCoeAppUi
	{
public:
	CTestClck1Ui(CTmsTestStep* aStep);
	void ConstructL();
protected:
	CClk1Control* iControl;
protected:
	virtual void RunTestStepL(TInt aStep);
	};

_LIT(KTClck1Step,"TClck1");

#endif
