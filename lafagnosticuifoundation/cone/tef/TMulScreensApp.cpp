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
// Negative tests for APIs that enable multiple displays	
// 
//

/**
 @file 
 @test
 @internalComponent - Internal Symbian test code 
*/


#include "TMulScreensApp.h"


const TUid KUidTMulScreensApp = { 0x1020820C }; 

_LIT8(KScreenDevice,"ScreenDevice"); 
_LIT8(KWindowGroup,"WindowGroup");
const TInt KMulScreensAppTestFailed = -666;
const TInt KInvalidScreenNumber = 3;



/*
	----- CMulScreensTestAppUi
**/
void CMulScreensTestAppUi::ConstructL()
    {
    BaseConstructL(ENoAppResourceFile | ENoScreenFurniture);
	}

CMulScreensTestAppUi::~CMulScreensTestAppUi()
	{
	}

void CMulScreensTestAppUi::HandleCommandL(TInt /*aCommand*/)
	{
	}

void CMulScreensTestAppUi::HandleSystemEventL(const TWsEvent& /*aEvent*/)
	{
	}

TBool CMulScreensTestAppUi::ProcessCommandParametersL(CApaCommandLine& aCommandLine)
	{
	TPtrC8 tailEnd = aCommandLine.TailEnd();
	if(tailEnd.Compare(KScreenDevice) == 0)
		{
		RDebug::Print(_L("**** MultipleScreensAppTest - ScreenDevice: This should panic with ECoePanicInvalidScreenNumber"));
		CCoeEnv::Static()->ScreenDevice(KInvalidScreenNumber);	
		}
	else if(tailEnd.Compare(KWindowGroup) == 0)
		{
		RDebug::Print(_L("**** MultipleScreensAppTest - WindowGroup: This should panic with ECoePanicInvalidScreenNumber"));
		CCoeEnv::Static()->RootWin(KInvalidScreenNumber);	
		}
	else
		{
		RDebug::Print(_L("MultipleScreensAppTest - Bad arguments, failing test...."));
		RProcess().Terminate(KMulScreensAppTestFailed);				
		}
	
	return ETrue;
	}	


/*
	----- CMulScreensTestDocument
**/
CMulScreensTestDocument::CMulScreensTestDocument(CEikApplication& aApp)
		: CEikDocument(aApp)
	{
	}

CEikAppUi* CMulScreensTestDocument::CreateAppUiL()
	{
    return new(ELeave) CMulScreensTestAppUi;
	}


/*
	----- CMulScreensTestApp
**/

TUid CMulScreensTestApp::AppDllUid() const
	{
	return KUidTMulScreensApp;
	}


TFileName CMulScreensTestApp::ResourceFileName() const
	{
	return TFileName(); // this app doesn't have a resource file
	}

CApaDocument* CMulScreensTestApp::CreateDocumentL()
	{
	return new (ELeave) CMulScreensTestDocument(*this);
	}


/*
	----- Main
**/

LOCAL_C CApaApplication* NewApplication()
	{
	return new CMulScreensTestApp;
	}

GLDEF_C TInt E32Main()
	{
	return EikStart::RunApplication(NewApplication);
	}//lint !e714 Symbol 'E32Main(void)' not referenced
	
