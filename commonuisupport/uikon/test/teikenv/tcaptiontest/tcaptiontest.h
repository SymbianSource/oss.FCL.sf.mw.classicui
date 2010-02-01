// Copyright (c) 2008-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef TTESTAPP_H_
#define TTESTAPP_H_

#include <eikappui.h>
#include <eikapp.h>
#include <eikdoc.h>
#include <eikenv.h>
#include <apgcli.h>
#include <eikon.mbg>

#include <test/testexecutestepbase.h>
#include "appfwk_test_AppUi.h"

const TUid KUidNameTest = {0xA000120E};
//
//
// CNameTestAppUi
//
//
class CNameTestAppUi : public CTestAppUi //CEikAppUi
    {
public:
	CNameTestAppUi();
    void ConstructL();
	~CNameTestAppUi();
private: 
	void RunTestStepL(TInt aNumStep);
	// from CEikAppUi
	void HandleCommandL(TInt aCommand);
	};


//
//
// CNameTestDocument
//
//
class CNameTestDocument : public CEikDocument
	{
public:
	static CNameTestDocument* NewL(CEikApplication& aApp);
	CNameTestDocument(CEikApplication& aApp);
	void ConstructL();

private: 
	// Inherited from CEikDocument
	CEikAppUi* CreateAppUiL();
	};
	

//
//
// CNameTestApplication
//
//
class CNameTestApplication : public CEikApplication
	{
private: 
	// Inherited from class CApaApplication
	CApaDocument* CreateDocumentL();
	TUid AppDllUid() const;

private:
	CApaDocument* CreateDocumentL(CApaProcess* a) { return CEikApplication::CreateDocumentL(a); }
	};

#endif /*TESTAPP_H_*/


