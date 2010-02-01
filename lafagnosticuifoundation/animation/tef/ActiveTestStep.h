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


#ifndef __ACTIVETESTSTEP_H__
#define __ACTIVETESTSTEP_H__

#include <test/testexecutestepbase.h>
#include "appfwk_tmsteststep.h"

//
//
//
class CActiveTestStep;

class CActiveTestStepLauncher : public CActive
	{
public:
	CActiveTestStepLauncher();
	~CActiveTestStepLauncher();

	void Launch(CActiveTestStep* aStep);
	TVerdict TestStepResult() const { return iVerdict; }
	void SetTestStepResult(TVerdict aVerdict) { iVerdict = aVerdict; }

	// from CActive
	void RunL();
	void DoCancel();
private:
	CActiveTestStep* iStep;
	TVerdict iVerdict;
	};

class CActiveTestStepScheduler;

class CActiveTestStep : public CTmsTestStep
	{
public:
	CActiveTestStep();
	~CActiveTestStep();
	
	void Stop(TInt aError = KErrNone);
	
	virtual TVerdict doActiveTestStepL() = 0;
	// From CTestStep:
	virtual TVerdict doTestStepPreambleL();
	virtual TVerdict doTestStepL();
	virtual TVerdict doTestStepPostambleL();
protected:
	CActiveScheduler * iScheduler;
	CActiveTestStepLauncher * iLauncher;
	};

class CActiveTestStepScheduler : public CActiveScheduler
	{
public:
	void Error(TInt aError) const;
	void SetStep(CActiveTestStep* aStep) { iStep = aStep; }
protected:
	CActiveTestStep* iStep;
	};
	
#endif //__ACTIVETESTSTEP_H__
