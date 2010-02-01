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


#if !defined(__TCONEVISIBILITY_H__)
#define __TCONEVISIBILITY_H__

#include <coecntrl.h>
#include <coeccntx.h>
#include <gulgcmap.h>
#include "TConeTestServer.h"
#include "appfwk_test_AppUi.h"


/** Base control drawing class, with standard rectangle fill draw implementation. It carries a status variable to store
	the latest visibility event returned. Note that currently windows server only returns one of EVisible or EHidden.
	@test
*/
class CVisibleControl : public CCoeControl
{
	friend class CVisibilityBackground;	

public:	
	enum 
	{
		ENone=0,		
		EPartiallyVisible=1,
		EHidden=2,
		EPartial=3,
		EFullyVisible=4
	};


	TInt iStatus;
	
	CVisibleControl()
	{
		iStatus = ENone;
	};
	
    void Draw(const TRect& aRect) const;
    
};

/** Parent control, which also acts as background, contains two child controls for manipulation
	@test
*/
class CVisibilityBackground : public CVisibleControl
{
public:
	CVisibleControl *iControl1;
	CVisibleControl *iControl2;
	CVisibilityBackground()
	{
		
	};
	~CVisibilityBackground();
	void ConstructL(void);
		
};

/** Test step class
	@test
*/
class CTConeVisibilityStep : public CTmsTestStep
	{
public:
	CTConeVisibilityStep();
	~CTConeVisibilityStep();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CCoeEnv* aCoe);

private:
	};
	
/**  Test application derived from the MCoeMessageMonitorObserver mix in class to behave as an observer which
	 is implemented as the MonitorWsMessage override
	 @test
*/
class CTConeVisibilityAppUi : public CTestCoeAppUi, MCoeMessageMonitorObserver
    {
    
public:
	CTConeVisibilityAppUi(CTmsTestStep* aStep);
	~CTConeVisibilityAppUi();
	void ConstructL();
private: // from CCoeAppUi
    TKeyResponse HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
    
	virtual void MonitorWsMessage(const TWsEvent& aEvent);
private: // utility
	void RunTestStepL(TInt aStepNum);
protected:
	CVisibilityBackground* iViewControl;			//The main application control
	
    };

_LIT(KTConeVisibilityStep,"TConeVisibility");

#endif


