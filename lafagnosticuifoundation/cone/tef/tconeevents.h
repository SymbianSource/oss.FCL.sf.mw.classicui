// Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef __TCONEEVENTS_H__
#define __TCONEEVENTS_H__

#include <test/testexecutestepbase.h>
#include "TConeTestServer.h"
#include "COECNTRL.H"
#include "appfwk_test_AppUi.h"

_LIT(KTConeEvents,"TConeEvents");
_LIT(KTConeEvents2,"TConeEvents2");


/**
 A class to test the recieving of events from WSERV
*/
class CTConeEvents : public CTmsTestStep
	{
public:
	CTConeEvents(TInt aMode);
	void ConstructL(CCoeEnv* aCoe);
	//Pure virtual function form CTestStep
	TVerdict doTestStepL();
private:
	TInt iMode;
	};

/**
 App Ui class for the TConeEvents
*/
class CConeEventsAppUi : public CTestCoeAppUi
	{
public:
	CConeEventsAppUi(CTmsTestStep* aStep,CCoeEnv* aCoe);
	void ConstructL();
	void ManyEvents();
	void ManyRedrawsL();
	//Virtual function from CCoeAppUi
	void HandleWsEventL(const TWsEvent& aEvent,CCoeControl* aDestination);
protected:
	//Pure virtual function from MAutoTestApp
	void RunTestStepL(TInt aStepNum);
private:
	CCoeEnv* iCoe;		//The control enviroment
	TInt iEventCount;
	};

#endif	//__TCONEEVENTS_H__
