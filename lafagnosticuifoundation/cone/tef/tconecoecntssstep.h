// Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#if !defined(__TCONECOECNTSS_H__)
#define __TCONECOECNTSS_H__

#include "TConeTestServer.h"
#include <test/testexecutestepbase.h>
#include "appfwk_test_AppUi.h"


class CTConeCoeCntSSStep : public CTmsTestStep
	{
public:
	CTConeCoeCntSSStep();
	~CTConeCoeCntSSStep();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CCoeEnv* aCoe);
	};


class CTConeCoeCntSSAppUi : public CTestCoeAppUi
    {
public:
	CTConeCoeCntSSAppUi(CTmsTestStep* aStep);
	~CTConeCoeCntSSAppUi();
	void ConstructL();

private: // utility
	void RunTestStepL(TInt aStepNum);

	void TestGetSetLogicalToPixelFontSizesL();
    };




_LIT(KTConeCoeCntSSStep,"TConeCoeCntSS");

#endif
