/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:  test case
*
*/


#include <w32std.h>
#include <coecntrl.h>
#include <caknfilenamepromptdialog.h>
#include <MAknFileSelectionObserver.h>
#include <MaknFileFilter.h>

#include "BCTestFileNameDlg.h"
#include "BCTestCmDlg.hrh"
#include "streamlogger.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestFileNameDlg* CBCTestFileNameDlg::NewL()
    {
    CBCTestFileNameDlg* self = new( ELeave ) CBCTestFileNameDlg();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestFileNameDlg::CBCTestFileNameDlg():iDlg(0)
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestFileNameDlg::~CBCTestFileNameDlg()
    {  
	delete iDlg;
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestFileNameDlg::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestFileNameDlg::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestFileNameDlg::BuildScriptL()
    { 
	AddTestL( DELAY(1), TEND);

    // Add script as your need.   
	for(int i=0; i<EBCTestCmdFileNameDlgEnd - EBCTestCmdFileNameDlgBegin -1; ++i)
		{
		AddTestL( LeftCBA, REP(Down, 3), Right, TEND );
		for(int j=0; j<i; ++j)
			AddTestL( Down, TEND);
		AddTestL( LeftCBA, TEND );	
		AddCancelL();		//OK may enter a folder and ask user to select more.
		}
    }
    
void CBCTestFileNameDlg::AddOKL()
	{
	// add dlg response sciprts
	for(int i=0; i<1; ++i)
		AddTestL( WAIT(5), KeyOK, TEND);
	}

void CBCTestFileNameDlg::AddCancelL()
	{
	// add dlg response sciprts
	for(int i=0; i<1; ++i)
		AddTestL( WAIT(5), RightCBA, TEND);
	}

// ---------------------------------------------------------------------------
// CBCTestFileNameDlg::RunL
// ---------------------------------------------------------------------------
//
void CBCTestFileNameDlg::RunL( TInt aCmd )
    {
	SetupL();
	switch(aCmd){
	case EBCTestCmdFileNameDlgCreate:
		TestCreateL();
		break;
	case EBCTestCmdFileNameDlgCreateRes:
		TestCreateL(0);		// 0 is default res id
		break;
	case EBCTestCmdFileNameDlgQuickCreate:
		TestQuickCreateL();
		break;
	case EBCTestCmdFileNameDlgQuickCreateTitle:
		TestQuickCreateL(_L("a title"));
		break;
	case EBCTestCmdFileNameDlgQuickCreateRes:
		TestQuickCreateL(0);	// 0 is the default res id
		break;
	case EBCTestCmdFileNameDlgSettings:
		TestSettingsL();
		break;
	default:
		break;
	}
    Teardown();
    }

// ---------------------------------------------------------------------------
// CBCTestFileNameDlg::ReleaseCaseL
// ---------------------------------------------------------------------------
//   
void CBCTestFileNameDlg::Teardown()
    {
	delete iDlg;
	iDlg = NULL;
    }

void CBCTestFileNameDlg::TestCreateL()
	{
	TFileName emptyFileName(KNullDesC);
	iDlg = CAknFileNamePromptDialog::NewL();
	TInt returnValue = iDlg->ExecuteL( emptyFileName );
	TFileName msg;
	msg.Format(_L("create User hit %d, filename: %s"), returnValue, &emptyFileName );	
	msg.ZeroTerminate();
	AssertTrueL(ETrue, msg);
	}

void CBCTestFileNameDlg::TestCreateL(TInt aResID)
	{
	TFileName emptyFileName(KNullDesC);
	iDlg = CAknFileNamePromptDialog::NewL(aResID);
	TInt returnValue = iDlg->ExecuteL( emptyFileName );
	AssertTrueL(ETrue, _L("Create by res ID"));
	}

void CBCTestFileNameDlg::TestQuickCreateL()
	{
	_LIT(KRootPath, "C:\\Nokia\\Data");
	TFileName defaultFileName;
	TInt returnValue = CAknFileNamePromptDialog::RunDlgLD( defaultFileName, KRootPath );
	AssertTrueL(ETrue, _L("RunDlgLD invoked"));
	}

void CBCTestFileNameDlg::TestQuickCreateL(const TDesC &aTitle)
	{
	_LIT(KRootPath, "C:\\Nokia\\Data");
	TFileName defaultFileName;
	TInt returnValue = CAknFileNamePromptDialog::RunDlgLD( defaultFileName, KRootPath, aTitle );
	AssertTrueL(ETrue, _L("RunDlgLD invoked"));
	}

void CBCTestFileNameDlg::TestQuickCreateL(TInt aResID)
	{
	_LIT(KRootPath, "C:\\Nokia\\Data");
	TFileName defaultFileName;
	TInt returnValue = CAknFileNamePromptDialog::RunDlgLD( defaultFileName, KRootPath, aResID );
	AssertTrueL(ETrue, _L("RunDlgLD invoked"));
	}

void CBCTestFileNameDlg::SetupL()
	{
	}


void CBCTestFileNameDlg::TestSettingsL()
	{
	iDlg = CAknFileNamePromptDialog::NewL();
	iDlg->SetPathL(_L("C:\\"));
	AssertTrueL(ETrue, _L("path set"));

	iDlg->SetTitleL(_L("a title"));
	AssertTrueL(ETrue, _L("title set"));

	iDlg->SetLeftSoftkeyL(_L("left key"));
	AssertTrueL(ETrue, _L("left soft key set"));

	iDlg->SetRightSoftkeyL(_L("right key"));
	AssertTrueL(ETrue, _L("right soft key set"));

	//Add fileter and set Observer
	struct MonkObserver: public MAknFileSelectionObserver{
		TBool OkToExitL( const TDesC& /*aDriveAndPath*/, const TEntry& /*aEntry*/ ){
			return ETrue;
		}
	} monkObserver;
	
	iDlg->SetObserver(&monkObserver);
	AssertTrueL(ETrue, _L("Observer set"));

	TFileName filename;
	iDlg->ExecuteL(filename);
	}
