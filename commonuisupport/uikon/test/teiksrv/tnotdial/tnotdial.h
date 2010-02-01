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
 @test
 @internalComponent - Internal Symbian test code
*/

#if !defined(__TNOTDIAL_H__)
#define __TNOTDIAL_H__

#include "uiktestserver.h"

#include <coecntrl.h>
#include <techview/eikdialg.h>
#include <eikdoc.h>
#include <eikapp.h>
#include "TNOTDIAL.HRH"
#include <tnotdial.rsg>
#include "eiksrvc.h"
#include <techview/eikconso.h>
#include <e32base.h>
#include <e32base.h>
#include "appfwk_test_AppUi.h"

//!  CEmptyControl
/**
 An empty background control.
*/
class CEmptyControl : public CCoeControl
	{
public:
	void ConstructL(const TRect& aRect);
	};

//!  CTNotdialAppUi
/**
 UI class for test class CTNotdialStep.
*/
class CTNotdialAppUi : public CTestAppUi
	{
public:
	CTNotdialAppUi(CTmsTestStep* aTestStep);
	void ConstructL();
	~CTNotdialAppUi();
	void RunTestStepL(TInt aNextStep);
	TUid iMyPhoneNotifierUid ;
	TUid iMySmsNotifierUid ;
	TUid iMyEmailNotifierUid ;
	TUid iMyLowBatteryNotifierUid ;
	TUid iMyAgendaAlarmUid ;
private: // framework
	void HandleCommandL(TInt aCommand);
	TKeyResponse HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	void TestStep01L();
	void TestStep02L();
	void TestStep03L();
	void TestStep04L();
	void TestStep05L();
	void TestStep06L();
	void TestStep07L();
	void TestStep08L();
	void TestStep09L();
	void TestStep10L();
	void TestStep11L();
	void TestStep12L();
	void TestStep13L();
	void TestStep14L();
	void TestStep15L();
	void TestStep16L();
	void TestStep17L();
	void TestStep18L();
	void TestStep19L();
	void TestStep20L();
	void TestStep21L();
	void TestStep22L();
	void TestStep23L();
	void TestStep24L();
	void TestStep25L();
	void TestStep26L();
	void TestStep27L();
	void TestStep28L();
	void TestStep29L();
	void TestStep30L();
	void TestStep31L();
	void TestStep32L();
private:
	void AppUpdate(TUid aNotifierUID,const TDesC8& aMessage, CEikonEnv* aEikEnv, TDes8& aResponse);
	static TInt KickOffBatteryNotifierL(TAny* aSimpleAppUi);
	static TInt NotifyFunc(TAny *aPtr);

private:
	CEmptyControl* iEmptyControl;
	RNotifier iNotifier;
	TRgb iColor[2];
	CPeriodic* iBattTimer;
	TInt iNotifierCounter;
	TPtrC iNotifierMessage[5];
	TInt iMessageCounter;
	};
	
_LIT(KTNotdialStep, "TNotdial");

//! A CTNotdialStep test step class
/**
 Test step class for the extended notifier framework.
*/
class CTNotdialStep : public CTmsTestStep
	{
public:
	CTNotdialStep();
	~CTNotdialStep();
	virtual TVerdict doTestStepPreambleL();
	virtual TVerdict doTestStepPostambleL();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CEikonEnv* aEikEnv);
	};

#endif
