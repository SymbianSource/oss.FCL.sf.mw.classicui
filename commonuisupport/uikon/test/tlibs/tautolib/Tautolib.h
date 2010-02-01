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

#ifndef		__TAUTOLIB_H
#define		__TAUTOLIB_H


#include "appfwk_test_AppUi.h"

_LIT(KTestAutoLibStep, "TAutoLib");

//!  A CTestAutoLibStep test class. 
/**
 This class defines the test step being executed.
*/
class CTestAutoLibStep : public CTmsTestStep
	{
public:
	CTestAutoLibStep();
	~CTestAutoLibStep();
	//virtual TVerdict doTestStepPreambleL();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CEikonEnv* aCoe);
private:
	};

#endif

