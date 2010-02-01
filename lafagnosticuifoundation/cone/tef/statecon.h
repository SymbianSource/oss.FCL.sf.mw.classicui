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

#ifndef __STATECON_H__
#define __STATECON_H__

#include "COECNTRL.H"
#include "Coemop.h"

_LIT(KFontName,"Arial");

class CStepStateObsEnv;


class MStatePassOn
	{
/**
   An interface which allows a provider of the MCoeControlStateObserver to pass calls to
   it on to another class.
 */
public:
	virtual TInt ControlStateChangePassOn(CCoeControl* aControl,MCoeControlStateObserver::TCoeState aState)=0;
	};

class CStateObserverControl : public CCoeControl, public MCoeControlStateObserver, public MStatePassOn
	{
/**
   A control which implements the Mop framework and provides the MCoeControlStateObserver
   interface.  It also provides test functions with check if the MCoeControlStateObserver
   is called or not when it should be or not.
 */
public:
	enum TObserver {ENoObserver,EObserver,ECoeEnvObserver};
public:
	static const TFontSpec iFontSpec;
public:
	~CStateObserverControl();
	void ConstructL();
	inline void SetReturnObserver(TObserver aRetObserver) {iRetObserver=aRetObserver;}
	void SetRecievers(TBool aControlRecieving,TBool aCoeEnvRecieving);
	inline void SetEnv(CStepStateObsEnv* aEnv) {iEnv=aEnv;}
	void ResetCount();
	TInt DoTest();
	//Pure virtual function from MCoeControlStateObserver
	TInt HandleControlStateChange(CCoeControl* aControl,MCoeControlStateObserver::TCoeState aState);
protected:
	//Pure virtual function from MStatePassOn
	TInt ControlStateChangePassOn(CCoeControl* aControl,MCoeControlStateObserver::TCoeState aState);
	//Pure virtual function from MObjectProvider overridden in CCoeControl
	TTypeUid::Ptr MopSupplyObject(TTypeUid aId);
	//Virtual function from CCoeControl
	void Draw(const TRect& aRect) const;
private:
	void inline Flush() {iCoeEnv->WsSession().Flush();}
	void DoSetDimmed(TBool aDimmed);
	void Failed();
	void DoTestStep(MCoeControlStateObserver::TCoeState aStateToChange,TBool aNewState);
	void TestFail(TBool aNotGetting,CCoeControl* aControl
								,MCoeControlStateObserver::TCoeState aState,TBool& aCalled);
private:
	TObserver iRetObserver;		//Specifies what interface should be returned by the Mop framework
	CFbsFont* iFont;			//Font used to draw to the controls window
	CStepStateObsEnv* iEnv;		//A control enviroment which provides the Mop interface MCoeControlStateObserver
	TInt iTestNo;				//A test case number count
	TInt iLastCalled;			//The test case on which the Mop interface was last called
	TInt iFailAt;				//The first test case where there was a test failure
	TBool iControlRecieving;	//If this control should recieve events through the Mop interface
	TBool iCoeEnvRecieving;		//If the control enviroment should recieve events through the Mop interface
	MCoeControlStateObserver::TCoeState iExpectedChange;	//Which state (dimmed or visibility) of the control should have just changed
	TBool iNoChange;			//If the lasted State change call on the control caused a real change
	TBool iShouldBeVisible;		//If the control should be visible
	TBool iShouldBeDimmed;		//If the control should be dimmed
	TBool iEnvCalled;			//If the Mop interface through the control has already been called
	TBool iCntCalled;			//If the Mop interface through the enviroment has already been called
	};

#endif	//__STATECON_H__
