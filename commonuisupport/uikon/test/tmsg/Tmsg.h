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
// Tests message windows provided by CEIkonEnv.\n
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code
*/

#ifndef		__TMSG_H
#define		__TMSG_H


#include "appfwk_test_AppUi.h"

_LIT(KTestMsgStep, "TMsg");

//!  A CTestMsgStep test class. 
/**
 Tests message windows provided by CEIkonEnv.
*/
class CTestMsgStep : public CTmsTestStep
	{
public:
	CTestMsgStep();
	~CTestMsgStep();
	//virtual TVerdict doTestStepPreambleL();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CEikonEnv* aCoe);
private:
	};

#endif

