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


#if !defined(__TCLCK0STEP_H__)
#define __TCLCK0STEP_H__


#include <test/testexecutestepbase.h>
#include "TClockTestServer.h"
#include "appfwk_test_AppUi.h"

class CTClck0Step : public CTmsTestStep
	{
public:
	CTClck0Step();
	~CTClck0Step();
//	virtual TVerdict doTestStepPreambleL();
//	virtual TVerdict doTestStepPostambleL();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CCoeEnv* aCoeEnv);

private:
	};

enum TFunction
	{
	ECreateDigitalClockWithNoConstructCall,
	ECreateDigitalClockWithTooManyConstructCalls,
	ECreateDigitalClockWithNoTextSections,
	ECreateDigitalClockWithTooManyTextSections,
	ECreateDigitalClockWithNonNormalizedRect,
	ECreateAnalogClockWithNoConstructCall,
	ECreateAnalogClockWithTooManyConstructCalls,
	ECreateAnalogClockWithNoHands,
	ECreateAnalogClockWithTooManyHands,
	ECreateAnalogClockWithHandWithNoFeatures
	};

//

struct SPanickingFunctionData
	{
	TInt iMainWindowGroup;
	TFunction iFunction;
	};

//

class CDestructableFont : public CBase
	{
public:
	CDestructableFont(CWsScreenDevice* aScreenDevice);
	void ConstructL(const TFontSpec& aFontSpec);
	virtual ~CDestructableFont();
	TInt Handle() const;
private:
	CWsScreenDevice* iScreenDevice; // not owned by this pointer
	CFbsFont* iFont;
	};

//
class CTestClckUi;
class CClkControl : public CCoeControl
	{
friend class CTestClckUi;
public:
	CClkControl();
	void ConstructL();
	virtual ~CClkControl();
private:
	// functions overriding those in CCoeControl
	virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
	virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	virtual void Draw(const TRect& aRect) const;
	// miscellaneous functions
	void TestForDegenerateClockCreationL();
	void TestClosingPartiallyCreatedDigitalClocksL();
	void TestClosingPartiallyCreatedAnalogClocksL();
	static void FireOffNewThreadAndTestForPanicL(TAny* aData);
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

class CTestClckUi  : public CTestCoeAppUi
	{
public:
	CTestClckUi(CTmsTestStep* aStep);
	void ConstructL();
protected:
	CClkControl* iControl;
protected:
	virtual void RunTestStepL(TInt aStep);
	};



_LIT(KTClck0Step,"TClck0");

#endif
