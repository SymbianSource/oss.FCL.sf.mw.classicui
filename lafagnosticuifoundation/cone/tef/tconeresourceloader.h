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

#if (!defined __T_TConeResourceLoader_STEP_H__)
#define __T_TConeResourceLoader_STEP_H__
#include <coeutils.h>
#include "appfwk_test_AppUi.h"

_LIT(KTConeResourceLoader,"tconeresourceloader");

class CTConeResourceLoaderStep : public CTmsTestStep
	{
public:
	CTConeResourceLoaderStep();
	~CTConeResourceLoaderStep();
	virtual TVerdict doTestStepL();
private:	
	void ConstructAppL(CEikonEnv* aEikEnv);
	};

class CTConeResourceLoaderAppUi : public CTestAppUi
	{
public:
	CTConeResourceLoaderAppUi(CTConeResourceLoaderStep& aStep);
	~CTConeResourceLoaderAppUi();
	// from CCoeAppUi
	void ConstructL();

private:
	void RunTestStepL(TInt aStepNum);
	void TestConeResourceLoader();
	void TestOOMConeResourceLoader();
	};


#endif
