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

#include <eikstart.h>
#include <fbs.h>
#include <apgwgnam.h>
#include "tcaptiontest.h"

//
//
// CNameTestAppUi
//
//

CNameTestAppUi::CNameTestAppUi() : CTestAppUi(NULL, KNullDesC)
  {
  }

void CNameTestAppUi::ConstructL()
    {
   	CTestAppUi::ConstructL();
	AutoTestManager().StartAutoTest();
    //BaseConstructL();
	}

CNameTestAppUi::~CNameTestAppUi()
	{
	}

void CNameTestAppUi::HandleCommandL(TInt /*aCommand*/)
	{
	}


void CNameTestAppUi::RunTestStepL(TInt /*aNumStep*/)
	{
	RProcess().Terminate(KErrNone);
	}


//
//
// CNameTestDocument
//
//
CNameTestDocument::CNameTestDocument(CEikApplication& aApp)
		: CEikDocument(aApp)
	{
	}

CEikAppUi* CNameTestDocument::CreateAppUiL()
	{
	return new (ELeave) CNameTestAppUi();
    }


//
//
// CNameTestApplication
//
//
TUid CNameTestApplication::AppDllUid() const
	{
	return KUidNameTest;
	}

CApaDocument* CNameTestApplication::CreateDocumentL()
	{
	return new (ELeave) CNameTestDocument(*this);
	}

LOCAL_C CApaApplication* NewApplication()
	{
	return new CNameTestApplication;
	}

GLDEF_C TInt E32Main()
	{
	return EikStart::RunApplication(NewApplication);
	}



