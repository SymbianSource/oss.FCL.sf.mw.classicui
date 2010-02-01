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
// Test adds a control factory function and resource file to the application.\n
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code
*/
#ifndef		__TADDLIB_H
#define		__TADDLIB_H


#include "appfwk_test_AppUi.h"

_LIT(KTestAddLibraryStep, "TAddLibrary");

//!  A CTestAddLibraryStep test class. 
/**
 Test adds a control factory function and resource file to the application.
*/
class CTestAddLibraryStep : public CTmsTestStep
	{
public:
	CTestAddLibraryStep();
	~CTestAddLibraryStep();
	//virtual TVerdict doTestStepPreambleL();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CEikonEnv* aCoe);
private:
	};


//!  A CTestLabel test control class. 
/**
 The class represents the test Label control.
*/
class CTestLabel : public CEikLabel
	{
private: 
	// framework
    void Draw(const TRect& aRect) const;
	};



//!  A CTestContainer  test control class. 
/**
 The class represents the test Container control.
*/
class CTestContainer : public CCoeControl
    {
public:
	enum
		{
		ECtTestLabel = 555
		};
public:
	CTestContainer(CTestAppUi* aAppUi);
    ~CTestContainer();
    void ConstructL(const TRect& aRect);
	virtual TInt CountComponentControls() const;
	virtual CCoeControl* ComponentControl(TInt aIndex) const;
public:
	static SEikControlInfo CreateByTypeL(TInt aControlType);	// Control factory
	void AddLibraryL();
	void RemoveLibrary();
	void RunL();
private: 
    void Draw(const TRect& aRect) const;
	TBool CreateControlL();
private:
	CTestLabel* iLabel;
	TFileName	iResourceFile;
	TInt		iResFileOffset;
	CTestAppUi* iAppUi;
    };


//!  A CTestAddLibraryAppUi test class. 
/**
 The class handles work with resources.
*/
class CTestAddLibraryAppUi : public CTestAppUi
	{
public:
	CTestAddLibraryAppUi(CTmsTestStep*		aStep, const TDesC& aRes);
	~CTestAddLibraryAppUi();
	void ConstructL();
	virtual void HandleCommandL(TInt aCommand);
	void RunTestStepL(TInt aStepNumber);

private:
    CTestContainer* iContainer;
	};

#endif

