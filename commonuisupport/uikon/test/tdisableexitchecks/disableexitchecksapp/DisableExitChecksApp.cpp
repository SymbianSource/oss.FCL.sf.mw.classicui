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
*/

#include <apgtask.h>
#include <eikenv.h>
#include <eikappui.h>
#include <eikapp.h>
#include <eikdoc.h>
#include <techview/eikmenup.h>

#include <disableexitchecksapp.rsg>
#include "DisableExitChecksApp.hrh"
#include "DisableExitChecksApp.h"

#include <eikstart.h>


_LIT8(KETrue,"ETrue");
_LIT8(KEFalse,"EFalse");
const TInt KTestFailed = -667; //random test failure
const TUid KUidDisableExitChecksApp = { 0x102857AF }; 

/**
 *	constructL method that creates the AppView object
 *	
 */  
void CExampleAppUi::ConstructL()
    {
	BaseConstructL();
	}
	
/**
 *	Destructor 
 *	
 */  
CExampleAppUi::~CExampleAppUi()
	{
	}
	
/**
 *	Handles the Menu events
 *	@param aCommand - command to be passed based on the menu item
 *						selected by the user
 *
 */  
void CExampleAppUi::HandleCommandL(TInt /*aCommand*/)
	{
	}

/**
 *	Processes the command line parameters
 *	@param aCommandLine - command to be passed based on the menu item
 *						selected by the user
 *
 *	This function leaks intentionally some memory and examines the value of the trailing data 
 *	in aCommandLine (expected to be either ETrue or EFalse). According to this value CCoeEnv::DisableExitChecks()
 *	is triggered in order to disable or not the exit checks at kernel resources.
 *	
 */
TBool CExampleAppUi::ProcessCommandParametersL(CApaCommandLine& aCommandLine)
	{
	CEikAppUi* aAppUI = new(ELeave) CExampleAppUi; //intentionally caused memory leak
	TPtrC8 tailEnd = aCommandLine.TailEnd();
	if(tailEnd.Compare(KETrue) == 0)
		{
		RDebug::Print(_L("Disable shutdown checks"));
		iEikonEnv->DisableExitChecks(ETrue);
		}
	else if(tailEnd.Compare(KEFalse) == 0)
		{
		RDebug::Print(_L("Enable shutdown checks"));
		iEikonEnv->DisableExitChecks(EFalse);
		}
	else
		{
		RDebug::Print(_L("Bad arguments, failing test...."));
		RProcess().Terminate(KTestFailed);				
		}
	Exit();
	return ETrue;
	}

/**
 *	Constructor that constructs a new document.
 *	@param aApp - The application instance that is creating the document. 
 *	
 */  
CExampleDocument::CExampleDocument(CEikApplication& aApp)
		: CEikDocument(aApp)
	{
	}
	
/**
 *	Constructs the application UI
 *	@return A partially-constructed application UI object. 
 *	
 */  
CEikAppUi* CExampleDocument::CreateAppUiL()
	{
    return new(ELeave) CExampleAppUi;
	}

/**
 *	Gets the application specific UID.
 *	@return - UID of the DisableExitChecksApp application
 *	
 */  
TUid CExampleApplication::AppDllUid() const
	{
	return KUidDisableExitChecksApp;
	}
	
/**
 *	Creates a document object for the application
 *	@return pointer to the newly created document
 *	
 */  
CApaDocument* CExampleApplication::CreateDocumentL()
	{
	return new (ELeave) CExampleDocument(*this);
	}

/**
 *	Creates and returns the object of the application
 *	@return pointer to the newly created application
 *	
 */  
LOCAL_C CApaApplication* NewApplication()
	{
	return new CExampleApplication;
	}

/**
 *	Entry point for the application
 *	
 */  
GLDEF_C TInt E32Main()
	{
	return EikStart::RunApplication(NewApplication);
	}
