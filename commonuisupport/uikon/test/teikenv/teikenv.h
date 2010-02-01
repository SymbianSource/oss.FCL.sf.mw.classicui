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

#if (!defined __TEIKENV_H__)
#define __TEIKENV_H__

#include <test/testexecutestepbase.h>
#include "eikdoc.h"
#include "eikapp.h"
#include "appfwk_test_AppUi.h"
#include <coecntrl.h>

//!  A CEikEnvStep test class. 
/**
 The test class exercises uikon classes: CEikEnv, CEikDocument, CEikAppUi.
*/
class CEikEnvStep : public CTmsTestStep
	{
public:
	CEikEnvStep();
	~CEikEnvStep();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CEikonEnv* aEikEnv);
private:
	};

//!  CTestControl 
/**
 A Control class. 
*/
class CTestControl : public CCoeControl
	{
public:
	static CTestControl* NewL();
	virtual ~CTestControl();
private:
	CTestControl();
	void ConstructL();
	// from CCoeControl
	virtual void Draw(const TRect& aRectangle) const;
	};

//!  CTEikEnvAppUi 
/**
 UI class for test class CEikEnvStep.
*/
class CTEikEnvAppUi : public CTestAppUi
    {
public:
	CTEikEnvAppUi(CTmsTestStep* aStep);
    void ConstructL();
    ~CTEikEnvAppUi();
protected: //from CTestAppUi
 	virtual void RunTestStepL(TInt aNumStep);
private://test functions
	void TestEikonEnv();
	void TestEikonEnvPictureFactoryL();
	void TestPopUpMenuL();
	void TestEikonAppUiL();
	void TestREikAppUiSessionApiL();
	void TestMessageApiL();
	void OpenFileL(const TDesC& aFileName);
	void CreateFileL(const TDesC& aFileName);
	void HandleCommandL(TInt aCommand);
	TErrorHandlerResponse HandleError(TInt aError, const SExtendedError& aExtErr,
		TDes& aErrorText, TDes& aContextText);
	static TInt TimerLoop(TAny *); 
	TInt DoTimerLoop();
	void LaunchPopupMenuL();
	void TestCreateBitmapL();
	void TestAddDialogLikeControlToStackL();
	void TestAddAlertDialogLikeControlToStackL();
	void TestFocusL();
	void HandleForegroundEventL(TBool aBool);
	void TestUpdateNameL();
private://test members
	TBool iResponseForHotKey;
	CTestControl *iParentControl;
	CTestControl *iChildControl;
	};

//!  CTPictureFactory 
/**
 A Picture Factory class.
*/
class CTPictureFactory : public CBase, public  MEikPictureFactory, public MPictureFactory 
	{
public:
	CTPictureFactory(RFs aFs, TUid aPictureType) : CBase(), iFs (aFs), iPictureType(aPictureType){}
	~CTPictureFactory() {}
	//from MEikPictureFactory 
	virtual TBool SupportsPictureType(TUid aPictureType) const;
	virtual const MPictureFactory* PictureFactory(TUid aPictureType) const;
	virtual TPictureHeader InsertL(TUid aPictureType,CBase* aData);
	virtual void EditL(const TPictureHeader& aPictureHeader,TBool aReadOnly);
	//from MPictureFactory
	virtual void NewPictureL(TPictureHeader& aHeader,const CStreamStore& aDeferredPictureStore)const;
protected:
	RFs& iFs;
	TUid iPictureType;
	};
/*
class CTestPicture : public CPicture
	{
public:
	static CTestPicture* NewL(RFs& aFs);
	static CTestPicture* NewL(RFs& aFs,const CStreamStore& aStore,TStreamId aStreamId);
	~CTestPicture();
	//legacy
	virtual void Draw(CGraphicsContext& aGc,const TPoint& aTopLeft,const TRect& aClipRect,MGraphicsDeviceMap* aMap) const;
	virtual void ExternalizeL(RWriteStream& aStream) const;
	virtual void GetOriginalSizeInTwips(TSize& aSize) const;
protected:
	CTestPicture(RFs& aFs) : iFs (aFs){}
	void ConstructL();
	void ConstructL(const CStreamStore& aStore,TStreamId aStreamId);
	RFs& iFs;
	};
*/

//!  CTEikEnvDocument 
/**
 Document class for test class CEikEnvStep.
*/
class CTEikEnvDocument : public CEikDocument 
	{
public:
	CTmsTestStep*	iStep;
	CEikAppUi* CreateAppUiL(){return new (ELeave) CTEikEnvAppUi(iStep);}
	CTEikEnvDocument(CEikApplication& aApp) :
		CEikDocument(aApp){}
 	CEikAppUi* AppUi() {return iAppUi;}
	};

//!  CTEikEnvApplication 
/**
 Application class for test class CEikEnvStep.
*/
class CTEikEnvApplication : public CEikApplication
	{
public:
	virtual CApaDocument* CreateDocumentL( );
	virtual TUid AppDllUid()const {return TUid::Null();}
	};

_LIT(KEikEnvStep,"TEikEnv");

#endif
