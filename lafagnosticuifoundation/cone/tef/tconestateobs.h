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
 @internalComponent - Internal Symbian test code
 @test
*/

#if !defined(__TCONESTATEOBS_H__)
#define __TCONESTATEOBS_H__

#include <test/testexecutestepbase.h>
#include "TConeTestServer.h"
#include "COECNTRL.H"
#include "appfwk_test_AppUi.h"
#include "statecon.h"

_LIT(KTConeStateObs,"TConeStateObs");


/**
   Control Enviroment class for the TConeStateObs.
*/
class CStepStateObsEnv : public CCoeEnv, public MCoeControlStateObserver
	{
public:
	inline void SetPassOn(MStatePassOn* aPassOn) {iPassOn=aPassOn;}
	inline void SetReturnObserver(TBool aRetObserver) {iRetObserver=aRetObserver;}
	//Pure virtual function from MCoeControlStateObserver
	TInt HandleControlStateChange(CCoeControl* aControl,MCoeControlStateObserver::TCoeState aState);
	//Pure virtual function from MObjectProvider overridden in CCoeEnv
	TTypeUid::Ptr MopSupplyObject(TTypeUid aId);
private:
	MStatePassOn* iPassOn;	//An object to pass calls from the Mop interface to
	TBool iRetObserver;		//If a control observer should be returned
	};

class CTConeStateObs : public CTmsTestStep
	{
public:
	CTConeStateObs();
	void ConstructL();
	//Pure virtual function form CTestStep
	TVerdict doTestStepL();
private:
	CStepStateObsEnv* iCoe;	//The control enviroment
	};

/**
   App Ui class for the TCone8Step.
*/
class CConeStateObsAppUi : public CTestCoeAppUi
	{
public:
	CConeStateObsAppUi(CTmsTestStep* aStep,CStepStateObsEnv* aCoe);
	~CConeStateObsAppUi();
	void ConstructL();
	void StateObserverTestEnvOnly();
	void StateObserverTestBoth();
	void StateObserverTestBothAtEnv();
protected:
	//Pure virtual function from MAutoTestApp
	void RunTestStepL(TInt aStepNum);
private:
	void DoStateObserverTest();
private:
	CStepStateObsEnv* iCoe;		//The control enviroment
	CStateObserverControl* iStateObCnt;	//The control used for testing
	};

#endif	//__TCONESTATEOBS_H__
