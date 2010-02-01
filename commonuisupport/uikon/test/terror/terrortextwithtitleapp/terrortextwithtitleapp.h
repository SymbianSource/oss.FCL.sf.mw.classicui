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

#ifndef		__TERRORCONTEXTAPP_H
#define		__TERRORCONTEXTAPP_H

#include <eikappui.h>
#include <eikapp.h>
#include <eikdoc.h>
#include <eikenv.h>
#include <apgcli.h>
#include <eikon.mbg>
#include <eikstart.h>

#include <test/testexecutestepbase.h>
#include <appfwk_test_appui.h>
#include <appfwk_test_utils.h>

const TUid KUidErrorContextApp = {0xA000335E}; 

// CErrorTextWithTitleAppUi
class CErrorTextWithTitleAppUi : public CTestAppUi
    {
public:
	CErrorTextWithTitleAppUi();
    void ConstructL();
	~CErrorTextWithTitleAppUi();
	
private: 
	void RunTestStepL(TInt aNumStep);
	};

// CErrorTextWithTitleDocument
class CErrorTextWithTitleDocument : public CEikDocument
	{
public:
	static CErrorTextWithTitleDocument* NewL(CEikApplication& aApp);
	CErrorTextWithTitleDocument(CEikApplication& aApp);
	void ConstructL();
private: 
	// Inherited from CEikDocument
	CEikAppUi* CreateAppUiL();
	};
	

// CErrorTextWithTitleApplication
class CErrorTextWithTitleApplication : public CEikApplication
	{
private: 
	// Inherited from class CApaApplication
	CApaDocument* CreateDocumentL();
	TUid AppDllUid() const;
	
private:
	CApaDocument* CreateDocumentL(CApaProcess* aProcess) {return CEikApplication::CreateDocumentL(aProcess);}
	};

#endif

