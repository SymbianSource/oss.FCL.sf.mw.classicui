// Copyright (c) 1999-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#if !defined(__TVWASTEP_H__)
#define __TVWASTEP_H__

#include <e32base.h>
#include <basched.h>

#include <vwsappst.h>
#include <viewcli.h>

#include <coeview.h>
#include <coecntrl.h>

#include <test/testexecutestepbase.h>
#include "TMenuTestServer.h"
#include "appfwk_test_AppUi.h"



/*************************************************************
 **  
 **  CViewActivationObserver  - implements the MCoeViewActivationObserver interface
 **  
 *************************************************************/

class CViewActivationObserver : public CBase, public MCoeViewActivationObserver
	{
public:
	static CViewActivationObserver* NewL(TInt aObserverId);
	~CViewActivationObserver();
private:
	CViewActivationObserver(TInt aObserverId);
public: // From MCoeViewDeactivationObserver.
	void HandleViewActivation (const TVwsViewId& aNewlyActivatedViewId,const TVwsViewId& aViewIdToBeDeactivated);
private:
	TInt iObserverId;
	};



/*************************************************************
 **  
 **  CViewDeactivationObserver - implements the MCoeViewDeactivationObserver interface
 **  
 *************************************************************/

class CViewDeactivationObserver : public CBase, public MCoeViewDeactivationObserver
	{
public:
	static CViewDeactivationObserver* NewL(TInt aObserverId);
	~CViewDeactivationObserver();
private:
	CViewDeactivationObserver(TInt aObserverId);
public: // From MCoeViewDeactivationObserver.
	void HandleViewDeactivation (const TVwsViewId& aViewIdToBeDeactivated,const TVwsViewId& aNewlyActivatedViewId);
private:
	TInt iObserverId;
	};



/*************************************************************
 **  
 **  CViewActivationObserver_Notify  - implements the MCoeViewActivationObserver interface for notifications only
 **  
 *************************************************************/

class CViewActivationObserver_Notify : public CBase, public MCoeViewActivationObserver
	{
public:
	static CViewActivationObserver_Notify* NewL();
	~CViewActivationObserver_Notify();
private:
	CViewActivationObserver_Notify();
public: // From MCoeViewDeactivationObserver.
	void HandleViewActivation (const TVwsViewId& aNewlyActivatedViewId,const TVwsViewId& aViewIdToBeDeactivated);
	};



/*************************************************************
 **  
 **  CViewDeactivationObserver_Notify - implements the MCoeViewDeactivationObserver interface for notifications only
 **  
 *************************************************************/

class CViewDeactivationObserver_Notify : public CBase, public MCoeViewDeactivationObserver
	{
public:
	static CViewDeactivationObserver_Notify* NewL();
	~CViewDeactivationObserver_Notify();
private:
	CViewDeactivationObserver_Notify();
public: // From MCoeViewDeactivationObserver.
	void HandleViewDeactivation (const TVwsViewId& aViewIdToBeDeactivated,const TVwsViewId& aNewlyActivatedViewId);
	};



/*************************************************************
 **  
 **  CTVwaTestControl
 **  
 *************************************************************/
/** 
	The CTVwaTestControl class implements a test control which processes key events and therefore is suitable for testing
    the control stacks of views. 
*/
class CTVwaTestControl : public CCoeControl
    {
public:
	CTVwaTestControl(TVwsViewId& aViewId, TInt aControlId);
    void ConstructL();
    ~CTVwaTestControl();
private: // framework
    TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
private:
	TVwsViewId& iViewId;
    TInt iControlId;
    };



/*************************************************************
 **  
 **  CAppUiTestControl
 **  
 *************************************************************/
/**  
	 The CAppUiTestControl class implements a test control which only processes key events.
     It is designed to be put on the appUi control stack at a low priority.
     It should always receive key events after the normal priority controls in the active view.
*/
class CAppUiTestControl : public CCoeControl
    {
public:
	CAppUiTestControl();
	void ConstructL();
    ~CAppUiTestControl();
private: // framework
    TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
private:
    };


class CCoeAppUi;



/*************************************************************
 **  
 **  CTestView
 **  
 *************************************************************/
/**
	The CTestView class implements the MCoeView interface, provides wrappers onto the CCoeAppUi view management methods
    and provides containment for two controls which process key events and test the control stack associated with the view.
*/
class CTestView : public CBase, public MCoeView
	{
public:
	// 'Stub' construction - scondary construction should be delayed until first activation
	CTestView(const TVwsViewId& aViewId,CCoeAppUi& aAppUi);

	void ConstructL();
	~CTestView();
public:	// view activation
	void ActivateViewL(const TVwsViewId& aViewId);
	void ActivateViewL(const TVwsViewId& aViewId,TUid aCustomMessageId,const TDesC16& aCustomMessage);
public: // view management
	void AddToStackL(CCoeControl* aControl,TInt aPriority=ECoeStackPriorityDefault,TInt aStackingFlags=ECoeStackFlagStandard);
	void RemoveFromStack(CCoeControl* aControl);
	void UpdateStackedControlFlags(CCoeControl* aControl,TInt aFlags,TInt aMask);
	void UpdateControlStackingFlags();
	void UpdateControlPriorityL();
public: // From MCoeView.
	TVwsViewId ViewId() const;
private:
	void DoDeactivate();
	void DoActivateNarrowL(const TVwsViewId& aPrevViewId,TUid aCustomMessageId,const TDesC8& aCustomMessage);
	void DoActivateL(const TVwsViewId& aPrevViewId,TUid aCustomMessageId,const TDesC16& aCustomMessage);
private: // From MCoeView.
	void ViewActivatedL(const TVwsViewId& aPrevViewId,TUid aCustomMessageId,const TDesC8& aCustomMessage);
	void ViewDeactivated();
	TVwsViewIdAndMessage ViewScreenDeviceChangedL();
	void ViewConstructL();
private: 
	CCoeAppUi& iAppUi;
	TVwsViewId iViewId;
	CTVwaTestControl* iTopControl;
	CTVwaTestControl* iBottomControl;
	};


class CTestDriver;


/*************************************************************
 **  
 **  CTVwaTestAppUi
 **  
 *************************************************************/
/** 
	The CTVwaTestAppUi class is an appUi that manages an array of CTestViews and provides a method to activate views passing
    a Unicode message descriptor. 
*/
class CTVwaTestAppUi : public CCoeAppUi
    {
public:
	CTVwaTestAppUi();
	~CTVwaTestAppUi();
	void ConstructL(CTmsTestStep* aStep, CCoeAppUi* aPrevious=NULL);
public: // view activation
	void ActivateViewL(const TVwsViewId& aViewId,TUid aCustomMessageId,const TDesC16& aCustomMessage);
public: // view management
	void AddViewL(CTestView* aView);
	void RemoveView(CTestView& aView);
	CTestView* ActiveView() const;
	CTestView* ViewById(const TVwsViewId& aViewId) const;
private:
	TInt TestAppUiViewIndex(CTestView& aView) const;
	TInt TestAppUiViewIndex(const TVwsViewId& aViewId) const;
private: // from CCoeAppUi
    TKeyResponse HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
private:
	CTestDriver* iDriver;
	CArrayPtrFlat<CTestView> iAppViewArray;
	CAppUiTestControl* iControl;
    };




class CPeriodic;

/*************************************************************
 **  
 **  CTestDriver - runs a series of tests on timer callback
 **  
 *************************************************************/

enum TestState
	{
	EInvalid,
	ENext,
	EFinished
	};

const TInt KTVwaStandardAppUiId=0;
const TInt KTVwaEmbeddedAppUiId=1;

const TInt KExitTestNum=0xEEEE;

const TInt KUpdateInterval=100000; // 0.2 seconds

class CTestDriver : public CBase
	{
public:
	CTestDriver(CCoeAppUi& aAppUi, CTmsTestStep* aStep);
	~CTestDriver();
	void ConstructL();
public: // auto test methods
	TestState DoTestL();
	void RunTestL();
	static TInt UpdateTimerCallBackL(TAny* aThis);
	void Exit();
public:
	CTestExecuteLogger&	Logger() {return iStep->Logger();}
private:
	TInt AddView(const TVwsViewId& aViewId,TInt aAppUiId=KTVwaStandardAppUiId);
	TInt ActivateView(const TVwsViewId& aViewId,TUid aCustomMessageId,const TDesC16& aCustomMessage,TInt aAppUiId=KTVwaStandardAppUiId);
	TInt RemoveView(const TVwsViewId& aViewId,TInt aAppUiId=KTVwaStandardAppUiId);
	TInt SimulateKeyEvent(const TInt aCode);
	TInt NotifyActivation();
	TInt NotifyDeactivation();
	TInt RegisterAndDeregisterView();
	TInt NotifyActivationWithViewId(const TVwsViewId& aViewId);
	TInt NotifyDeactivationWithViewId(const TVwsViewId& aViewId);
	TInt UpdateActiveViewStackingFlags();
	TInt UpdateActiveViewPriorities();
	TInt AddApplicationView();
	TInt ActivateApplicationView();
	TInt AddViewDeactivationObserverOne();
	TInt RemoveViewDeactivationObserverOne();
	TInt AddViewDeactivationObserverTwo();
	TInt DeactivateActiveView();
	TInt AddViewActivationObserverOne();
	TInt RemoveViewActivationObserverOne();
	TInt AddViewActivationObserverTwo();
	TInt RemoveApplicationView();
	TInt SetDefaultView(const TVwsViewId& aViewId,TInt aAppUiId=KTVwaStandardAppUiId);
	TInt GetDefaultView(TVwsViewId& aViewId,TInt aAppUiId=KTVwaStandardAppUiId);
	TInt ActivateTopView(TInt aAppUiId=KTVwaStandardAppUiId);
	TInt ConstructEmbeddedAppUi();
	TInt DestroyEmbeddedAppUi();
	TInt TestActivateViewOOM(const TVwsViewId& aViewId,TUid aCustomMessageId,const TDesC16& aCustomMessage,TInt aAppUiId=KTVwaStandardAppUiId);
	TInt TestAddViewOOML(const TVwsViewId& aViewId,TInt aAppUiId=KTVwaStandardAppUiId);
	TInt TestRemoveViewActivationObserverL();
private:
	inline CTVwaTestAppUi& AppUi(TInt aAppUiId=KTVwaStandardAppUiId); 
private:
	TInt iTestNum;
	CPeriodic* iUpdateTimer;
	CCoeAppUi& iAppUi;
	CCoeAppUi* iAppUiEmbedded;
	CViewActivationObserver* iViewActivationObserverOne;
	CViewDeactivationObserver* iViewDeactivationObserverOne;
	CViewActivationObserver* iViewActivationObserverTwo;
	CViewDeactivationObserver* iViewDeactivationObserverTwo;
	CViewActivationObserver_Notify* iViewActivationObserver_Notify;
	CViewDeactivationObserver_Notify* iViewDeactivationObserver_Notify;
	CTmsTestStep* iStep;
	};

inline CTVwaTestAppUi& CTestDriver::AppUi(TInt aAppUiId)
	{ return (aAppUiId==KTVwaEmbeddedAppUiId) ? STATIC_CAST(CTVwaTestAppUi&,*iAppUiEmbedded) : STATIC_CAST(CTVwaTestAppUi&,iAppUi); } 



/*************************************************************
 **  
 **  CTVwaStep
 **  
 *************************************************************/

class CTVwaStep : public CTmsTestStep
	{
public:
	CTVwaStep();
	~CTVwaStep();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CCoeEnv* aCoe);
private:
	};


_LIT(KTVwaStep,"TVwa");

#endif

