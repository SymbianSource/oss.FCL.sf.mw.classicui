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
 @internalComponent
*/


#if !defined(__TCONE4STEPEXE_H__)
#define __TCONE4STEPEXE_H__

#include "appfwk_test_AppUi.h"
//! Test Step Name.\n
_LIT(KTCone4StepExe, "TCone4Exe");
//! A CTestStep Derived Class.\n
/**
  Incorporate tests on TConeTestExe.\n
*/
class CTCone4StepExe : public CTmsTestStep
	{
public:
	CTCone4StepExe();
	~CTCone4StepExe();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CCoeEnv* aCoe);
	};

#endif


