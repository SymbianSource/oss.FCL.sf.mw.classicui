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


#ifndef __TVIEW2_H__
#define __TVIEW2_H__

#include <coecntrl.h>
#include <coeccntx.h>
#include <coemain.h>

#include <eikapp.h>
#include <eikdoc.h>
#include <eikenv.h>
#include <techview/eiklbi.h>
#include <techview/eikconso.h>
#include <techview/eikdialg.h>

#include "tvwview.H"
#include "tvwappui.H"

//
// Constants.
//

const TInt KMaxCommandLength=256;
const TInt KNumViewsToActivate=8;


//
// Forward declarations.
//

class CTestDocument;
class CTestView;
class CTestAppUi;



//
// Class CTestViewDeactivationObserver
//

class CTestViewActivationObserver : public CBase, public MCoeViewActivationObserver
    {
public:
	CTestViewActivationObserver(CCoeAppUi& aAppUi);
	void ConstructL();
public:	// from MCoeViewActivationObserver
	void HandleViewActivation(const TVwsViewId& aNewlyActivatedViewId,const TVwsViewId& aViewIdToBeDeactivated);
private:
	CCoeAppUi& iAppUi;
	TInt iActivationCount;
	};

//
// Class CTestViewControl
//

class CTestViewControl : public CCoeControl
    {
public:
    void ConstructL(const TVwsViewId& aViewId);
	~CTestViewControl();
private: // framework
	void Draw(const TRect& aRect) const;
private:
	TVwsViewId iViewId;
    };


//
// CTestView.
//

class CTestView : public CTestVwAppView
	{
public:
	~CTestView();
	CTestView(const TVwsViewId& aViewId,CTestAppUi& aAppUi);
	void ConstructL();
	void InitializeAsDefaultL();
public:	// from CTestVwAppView
	void DoActivateL(const TVwsViewId& aPrevViewId,TUid aCustomMessageId,const TDesC16& aCustomMessage);
	void DoDeactivate();
	void HandleCommandL(TInt aCommand);
	void SetEmphasis(CCoeControl* aMenuControl,TBool aEmphasis);
	void Reset();
	void UnrollDoActivate();
public:
	TBool iDeactivationPanic;
	TBool iSlowDeactivation;
	TBool iSluggishDeactivation;
private:
	TBool iActivated;
	CTestViewControl* iControl;
	};

//
// CTestSwitchDialog.
//

class CTestSwitchDialog : public CEikDialog
	{
public:
	~CTestSwitchDialog();
	CTestSwitchDialog(CTestAppUi& aAppUi);
private: // From CEikDialog.
	virtual TBool OkToExitL(TInt aButtonId);
private:
	CTestAppUi& iAppUi;
	};


//
// CTestAppUi.
//

class CRichText;
class CParaFormatLayer;
class CCharFormatLayer;

class CTestAppUi : public CTestVwAppUi
    {
public:
	CTestAppUi();
    void ConstructL();
	~CTestAppUi();
	void DisplayRichTextDialogL();
	void StartEnduranceTest();
	void DoNextEnduranceTestActivation();
	static TInt EnduranceTestCallBack(TAny* aSelf);
	void IdleExit();
	static TInt IdleExitCallBack(TAny* aSelf);
	void DoExit();
private: // from CEikAppUi
	void HandleCommandL(TInt aCommand);
private:
	void CreateViewsL();
	void DisplaySwitchViewDialogL();
	void DoActivationL();
	void TestActivationOOML();
	void TestSuccesiveAllocFailL();
	void TestWaitingActivationL();
	void TestPanicedActivationL();
	void TestPanicedDeactivationL();
	void TestSlowActivationL();
	void TestSlowDeactivationL();
	void TestStartMissingAppL();
	void TestPanic();
	void AddViewL(const TVwsViewId& aViewId);
private:
	friend class CTestSwitchDialog;
	friend class CTestView;
private:
	CRichText* iRichText;
	CParaFormatLayer* iRichParaFormatLayer;
	CCharFormatLayer* iRichCharFormatLayer;
	TVwsViewId iViewToActivate;
	TBool iViewsCreated;
	HBufC* iCustomMsg;
	CTestViewActivationObserver* iViewActivationObserver;
	CPeriodic* iAutoTestTimer;
	TInt64 iRandSeed;
	CIdle* iIdle;
	};


//
// CTestDocument.
//

class CTestDocument : public CEikDocument
	{
public:
	// construct/destruct
	CTestDocument(CEikApplication& aApp);
private: // from CEikDocument
	CEikAppUi* CreateAppUiL();
	};


//
// CTestApplication.
//

class CTestApplication : public CEikApplication
	{
private: // from CApaApplication
	CApaDocument* CreateDocumentL();
	TUid AppDllUid() const;
private:
	CApaDocument* CreateDocumentL(CApaProcess* a) { return CEikApplication::CreateDocumentL(a); }
	};

#endif
