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
 @test
 @internalComponent - Internal Symbian test code
*/

#ifndef		__TERRORAPP_H
#define		__TERRORAPP_H

#include <eikappui.h>
#include <eikapp.h>
#include <eikdoc.h>
#include <eikenv.h>
#include <apgcli.h>
#include <eikon.mbg>
#include <eikstart.h>
#include "eikerror.h"

#include <test/testexecutestepbase.h>
#include <test/appfwk_test_appui.h>
#include <test/appfwk_test_utils.h>


_LIT16(KErrorAppSpecificText, "This is an Application Specific Error");
const TUid KUidErrorApp = {0xA0002129}; 
const TInt KErrorAppId = 1100;


//
//
// CErrorAppUi
//
//
class CErrorAppUi : public CTestAppUi
    {
public:
	CErrorAppUi();
    void ConstructL();
	~CErrorAppUi();
	
private: 
	void RunTestStepL(TInt aNumStep);
	// from CEikAppUi
	void HandleCommandL(TInt aCommand);	

private:
	void AppCleanUpL();
	void TestErrorMessageL();
	};


//
//
// CErrorDocument
//
//
class CErrorDocument : public CEikDocument
	{
public:
	static CErrorDocument* NewL(CEikApplication& aApp);
	CErrorDocument(CEikApplication& aApp);
	void ConstructL();
private: 
	// Inherited from CEikDocument
	CEikAppUi* CreateAppUiL();
	};
	

//
//
// CErrorApplication
//
//
class CErrorApplication : public CEikApplication
	{
private: 
	// Inherited from class CApaApplication
	CApaDocument* CreateDocumentL();
	TUid AppDllUid() const;
	
private:
	CApaDocument* CreateDocumentL(CApaProcess* a) { return CEikApplication::CreateDocumentL(a); }
	};

#endif


