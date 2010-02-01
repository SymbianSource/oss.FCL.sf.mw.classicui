// Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies).
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
 @test
 @internalComponent - Internal Symbian test code 
*/

#if !defined(__TMULTIPLESCREENS_STEP_H__)
#define __TMULTIPLESCREENS_STEP_H__

#include <coemain.h>
#include <coecntrl.h>
#include <coeaui.h>
#include <test/testexecutestepbase.h>
#include "TConeTestServer.h"
#include "appfwk_test_AppUi.h"
#include <w32std.h>

_LIT(KTMultipleScreensStep,"TMultipleScreens");
_LIT(KExeName, "z:\\sys\\bin\\TMulScreensApp.EXE");
_LIT(KImagePath,"z:\\conetest\\display.mbm");

class CTMultipleScreensStep : public CTmsTestStep
	{
public:
	CTMultipleScreensStep();
	~CTMultipleScreensStep();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CCoeEnv* aCoe);
	};

class CTImageControl : public CCoeControl
	{
public:
	CTImageControl(CFbsBitmap& aBitmap);
	~CTImageControl();
	static CTImageControl* NewL(RWindowGroup& aWindow,CFbsBitmap& aBitmap);
private: // framework
	void ConstructL(RWindowGroup& aWindow);
    void Draw(const TRect& aRect) const;
private:
	CFbsBitmap& iBitmap;
	};

class CTMultipleScreensAppUi : public CTestCoeAppUi
    {
public:
	CTMultipleScreensAppUi(CTmsTestStep* aStep);
	~CTMultipleScreensAppUi();
	void TestDrawOnFirstScreenL();
	void TestDrawOnSecondScreenL();
	void TestNumberOfScreens();
	void StartProcessL(const TDesC8& aTailEnd);
	void TestInvalidScreenNumberL();
    void CompareL(TInt aScreenNumber);
public:	// from CCoeAppUi
	void ConstructL();
private:
	void RunTestStepL(TInt aStepNum);
private:
    TInt iNumScreens;
	CTImageControl* iFstControl;
	CTImageControl* iSndControl;
	CFbsBitmap* iBitmap;
    };

#endif
