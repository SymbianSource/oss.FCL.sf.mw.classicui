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
// Contains classes for testing the implementation of this PREQ
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code 
 @SYMPREQ PREQ527
*/

#if !defined(__TCONEZOOMFONT_H__)
#define __TCONEZOOMFONT_H__

#include <test/testexecutestepbase.h>
#include "TConeTestServer.h"
#include "appfwk_test_AppUi.h"

class CTConeZoomFontStep : public CTmsTestStep
	{
public:
	CTConeZoomFontStep();
	~CTConeZoomFontStep();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CCoeEnv* aCoe);

private:
	};

class CConeZoomFontView;

class CConeZoomFontAppUi : public CTestCoeAppUi
    {
public:
	CConeZoomFontAppUi(CTmsTestStep* aStep);
	~CConeZoomFontAppUi();
	void ConstructL();
private: // utility
	void RunTestStepL(TInt aStepNum);

private:
	CConeZoomFontView* iView;
    };


_LIT(KTConeZoomFontStep,"TConeZoomFont");

#endif


