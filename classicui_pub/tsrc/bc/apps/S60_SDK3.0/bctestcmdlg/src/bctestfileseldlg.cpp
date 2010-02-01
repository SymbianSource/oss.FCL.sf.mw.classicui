/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         test case
*
*/









#include <w32std.h>
#include <coecntrl.h>
#include <MAknFileSelectionObserver.h>
#include <MaknFileFilter.h>

#include "BCTestFileSelDlg.h"
#include "BCTestCmDlg.hrh"
#include "streamlogger.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestFileSelDlg* CBCTestFileSelDlg::NewL()
    {
    CBCTestFileSelDlg* self = new( ELeave ) CBCTestFileSelDlg();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestFileSelDlg::CBCTestFileSelDlg():iDlg(0)
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestFileSelDlg::~CBCTestFileSelDlg()
    {  
	delete iDlg;
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestFileSelDlg::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestFileSelDlg::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestFileSelDlg::BuildScriptL()
    { 
	AddTestL( DELAY(1), TEND);

    // Add script as your need.   
	for(int i=0; i<EBCTestCmdFileSelDlgEnd - EBCTestCmdFileSelDlgBegin -1; ++i)
		{
		AddTestL( LeftCBA, REP(Down, 2), Right, TEND );
		for(int j=0; j<i; ++j)
			AddTestL( Down, TEND);
		AddTestL( LeftCBA, TEND );	
		AddCancelL();		//OK may enter a folder and ask user to select more.
		}
    }
    
void CBCTestFileSelDlg::AddOKL()
	{
	// add dlg response sciprts
	for(int i=0; i<1; ++i)
		AddTestL( WAIT(5), KeyOK, TEND);
	}

void CBCTestFileSelDlg::AddCancelL()
	{
	// add dlg response sciprts
	for(int i=0; i<1; ++i)
		AddTestL( WAIT(5), RightCBA, TEND);
	}

// ---------------------------------------------------------------------------
// CBCTestFileSelDlg::RunL
// ---------------------------------------------------------------------------
//
void CBCTestFileSelDlg::RunL( TInt aCmd )
    {
	SetupL();
	switch(aCmd){
	case EBCTestCmdFileSelDlgCreate:
		TestCreateL();
		break;
	case EBCTestCmdFileSelDlgCreateRes:
		TestCreateL(0);		// 0 is default res id
		break;
	case EBCTestCmdFileSelDlgQuickCreate:
		TestQuickCreateL();
		break;
	case EBCTestCmdFileSelDlgQuickCreateTitle:
		TestQuickCreateL(_L("a title"));
		break;
	case EBCTestCmdFileSelDlgQuickCreateRes:
		TestQuickCreateL(0);	// 0 is the default res id
		break;
	case EBCTestCmdFileSelDlgSettings:
		TestSettingsL();
		break;
	default:
		break;
	}
    Teardown();
    }

// ---------------------------------------------------------------------------
// CBCTestFileSelDlg::ReleaseCaseL
// ---------------------------------------------------------------------------
//   
void CBCTestFileSelDlg::Teardown()
    {
	delete iDlg;
	iDlg = NULL;
    }

void CBCTestFileSelDlg::TestCreateL()
	{
	_LIT( KRootPath,					"C:\\Data\\" );
	TFileName rootFileName( KRootPath );

	iDlg = CAknFileSelectionDialog::NewL( ECFDDialogTypeSelect );
	AssertNotNullL(iDlg, _L("file sel dialog create"));
	TInt returnValue = iDlg->ExecuteL( rootFileName );
	TFileName msg;
	msg.Format( _L("User hit: %d, selected file: "), returnValue );
	msg.Append( rootFileName );
	msg.ZeroTerminate();
	AssertTrueL(ETrue, msg);
	}

void CBCTestFileSelDlg::TestCreateL(TInt aResID)
	{
	_LIT( KRootPath,					"C:\\Data\\" );
	TFileName rootFileName( KRootPath );

	iDlg = CAknFileSelectionDialog::NewL( ECFDDialogTypeSelect, aResID );
	AssertNotNullL(iDlg, _L("file sel dialog create with Res ID"));
	TInt returnValue = iDlg->ExecuteL( rootFileName );
	TFileName msg;
	msg.Format(_L("User hit: %d, selected file: "), returnValue );
	msg.Append( rootFileName );
	msg.ZeroTerminate();
	AssertTrueL(ETrue, msg);
	}

void CBCTestFileSelDlg::TestQuickCreateL()
	{
	TFileName filename;
	TFileName folder(_L("C:\\Data\\"));
	AssertTrueL(!CAknFileSelectionDialog::RunDlgLD(filename, folder), 
		_L("Quick create, User hit Cancle"));
	}

void CBCTestFileSelDlg::TestQuickCreateL(const TDesC &aTitle)
	{
	TFileName filename;
	TFileName folder(_L("C:\\Data\\"));
	AssertTrueL(!CAknFileSelectionDialog::RunDlgLD(filename, folder, aTitle), 
		_L("Quick create, User hit Cancle"));
	}

void CBCTestFileSelDlg::TestQuickCreateL(TInt aResID)
	{
	TFileName filename;
	TFileName folder(_L("C:\\Data\\"));
	AssertTrueL(!CAknFileSelectionDialog::RunDlgLD(filename, folder, aResID), 
		_L("Quick create, User hit Cancle"));
	}

void CBCTestFileSelDlg::SetupL()
	{
	}


void CBCTestFileSelDlg::TestSettingsL()
{
	iDlg = CAknFileSelectionDialog::NewL( ECFDDialogTypeSelect );
	iDlg->SetDefaultFolderL(_L("C:\\"));
	AssertTrueL(ETrue, _L("default folder set"));

	iDlg->SetTitleL(_L("a title"));
	AssertTrueL(ETrue, _L("title set"));

	iDlg->SetLeftSoftkeyFileL(_L("left fkey"));
	AssertTrueL(ETrue, _L("left soft key file set"));

	iDlg->SetLeftSoftkeyFolderL(_L("left dkey"));
	AssertTrueL(ETrue, _L("left soft key folder set"));

	iDlg->SetRightSoftkeyRootFolderL(_L("right root"));
	AssertTrueL(ETrue, _L("right soft key root set"));

	iDlg->SetRightSoftkeySubfolderL(_L("right sdir"));
	AssertTrueL(ETrue, _L("right soft key sub folder set"));

	//Add fileter and set Observer
	struct MonkObserver: public MAknFileSelectionObserver{
		TBool OkToExitL( const TDesC& /*aDriveAndPath*/, const TEntry& /*aEntry*/ ){
			return ETrue;
		}
	} monkObserver;
	
	iDlg->SetObserver(&monkObserver);
	AssertTrueL(ETrue, _L("Observer set"));

	struct MonkFilter: public MAknFileFilter{
		TBool Accept( const TDesC& /*aDriveAndPath*/, const TEntry& /*aEntry*/ ) const{
			return ETrue;
		}
	};

	iDlg->AddFilterL(new (ELeave) MonkFilter);	//problems, should be push into stack
	AssertTrueL(ETrue, _L("Filter add"));

	TFileName filename;
	iDlg->ExecuteL(filename);
}
