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

#include "BCTestCmDlgcase.h"
#include "BCTestCmDlgcontainer.h"
#include "BCTestCmDlg.hrh"
#include "streamlogger.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestCmDlgCase* CBCTestCmDlgCase::NewL()
    {
    CBCTestCmDlgCase* self = new( ELeave ) CBCTestCmDlgCase();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestCmDlgCase::CBCTestCmDlgCase():iDlg(0)
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestCmDlgCase::~CBCTestCmDlgCase()
    {  
	delete iDlg;
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestCmDlgCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestCmDlgCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestCmDlgCase::BuildScriptL()
    { 
    // Add script as your need.   
	AddTestL( DELAY(1), TEND);

	for(int i=0; i<EBCTestCmdMemSelDlgEnd - EBCTestCmdMemSelDlgBegin -1; ++i)
		{
		AddTestL( LeftCBA, Right, TEND );
		for(int j=0; j<i; ++j)
			AddTestL( Down, TEND);
		AddTestL( LeftCBA, TEND );	
		AddOKL();
		}
    }
    
void CBCTestCmDlgCase::AddOKL()
	{
	// add dlg response sciprts
	for(int i=0; i<1; ++i)
		AddTestL( WAIT(5), KeyOK, TEND);
	}

void CBCTestCmDlgCase::AddCancelL()
	{
	// add dlg response sciprts
	for(int i=0; i<1; ++i)
		AddTestL( WAIT(5), RightCBA, TEND);
	}

// ---------------------------------------------------------------------------
// CBCTestCmDlgCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestCmDlgCase::RunL( TInt aCmd )
    {
	SetupL();
	switch(aCmd){
	case EBCTestCmdMemSelDlgCreate:
		TestCreateL();
		break;
	case EBCTestCmdMemSelDlgCreateWithRes:
		TestCreateL(0);		//0 indicate to default res
		break;
	case EBCTestCmdMemSelDlgWithRoot:
		TestWithRootL();
		break;
	case EBCTestCmdMemSelDlgQuick:
		TestQuickCreateL();
		break;
	case EBCTestCmdMemSelDlgQuickTitle:
		TestQuickCreateL(_L("a title"));
		break;
	case EBCTestCmdMemSelDlgQuickRes:
		TestQuickCreateL(0);	//0 means default res
		break;
	case EBCTestCmdMemSelDlgSetting:
		TestSettingsL();
		break;
	default:
		break;
	}

    Teardown();
    }

// ---------------------------------------------------------------------------
// CBCTestCmDlgCase::ReleaseCaseL
// ---------------------------------------------------------------------------
//   
void CBCTestCmDlgCase::Teardown()
    {
	delete iDlg;
	iDlg = NULL;
    }

void CBCTestCmDlgCase::TestCreateL()
	{
    iDlg = CAknMemorySelectionDialog::NewL( ECFDDialogTypeNormal, EFalse );

	AssertNotNullL(iDlg, _L("mem sel dlg created"));
	AssertTrueL(iDlg->ExecuteL( iMemory ), _L("User Hit OK"));
	AssertIntL( CAknMemorySelectionDialog::EPhoneMemory, iMemory, _L("Phone memory created"));
	}

void CBCTestCmDlgCase::TestCreateL(TInt aResID)
{
	iDlg = CAknMemorySelectionDialog::NewL( ECFDDialogTypeNormal, aResID, EFalse );

	AssertNotNullL(iDlg, _L("mem sel dlg with resID created"));
	AssertTrueL(CAknMemorySelectionDialog::RunDlgLD(iMemory), _L("Quick create, User hit OK"));
	AssertIntL( CAknMemorySelectionDialog::EPhoneMemory, iMemory, _L("Phone memroy created"));
}

void CBCTestCmDlgCase::TestQuickCreateL()
	{
	AssertTrueL(CAknMemorySelectionDialog::RunDlgLD(iMemory), _L("Quick create, User hit OK"));
	AssertIntL( CAknMemorySelectionDialog::EPhoneMemory, iMemory, _L("Phone memroy created"));
	}

void CBCTestCmDlgCase::TestQuickCreateL(const TDesC &aTitle)
	{
	AssertTrueL(CAknMemorySelectionDialog::RunDlgLD(iMemory, aTitle), _L("Quick create with title, User hit OK"));
	AssertIntL( CAknMemorySelectionDialog::EPhoneMemory, iMemory, _L("Phone memroy created"));
	}

void CBCTestCmDlgCase::TestQuickCreateL(TInt aResID)
	{
	AssertTrueL(CAknMemorySelectionDialog::RunDlgLD(iMemory, aResID), _L("Quick create with ResID, User hit OK"));
	AssertIntL( CAknMemorySelectionDialog::EPhoneMemory, iMemory, _L("Phone memroy created"));
	}

void CBCTestCmDlgCase::SetupL()
	{
	iMemory = CAknMemorySelectionDialog::EPhoneMemory;
	}

void CBCTestCmDlgCase::TestWithRootL()
{
	_LIT( KRootPath,					"C:\\Nokia\\Images\\" );
	_LIT( KDefaultFileName,				"DynamicFilename.jpg" );
	TFileName rootFileName( KRootPath );
	TFileName defaultFileName( KDefaultFileName );
	iDlg = CAknMemorySelectionDialog::NewL( ECFDDialogTypeNormal, EFalse );
	if(TInt res = iDlg->ExecuteL(iMemory, &rootFileName, &defaultFileName))
	{
		TFileName msg(_L("default root: "));
		msg.Append(rootFileName);
		msg.Append(_L(" default file: "));
		msg.Append(defaultFileName);
		msg.ZeroTerminate();
		AssertTrueL(res, msg);
	}
}

void CBCTestCmDlgCase::TestSettingsL()
{
	iDlg = CAknMemorySelectionDialog::NewL( ECFDDialogTypeNormal, EFalse );

	iDlg->SetObserver(NULL);
	AssertTrueL(ETrue, _L("Null Observer set"));

	iDlg->SetTitleL(_L("a title"));
	AssertTrueL(ETrue, _L("title set"));

	iDlg->SetLeftSoftkeyL(_L("left key"));
	AssertTrueL(ETrue, _L("left key text set"));

	iDlg->SetRightSoftkeyL(_L("right key"));
	AssertTrueL(ETrue, _L("right key text set"));
	if(iDlg->ExecuteL(iMemory))
	{
		//get
		TFileName emptyFileName( KNullDesC );
		iDlg->GetItem( iMemory, emptyFileName );
		TFileName msg(_L("item got: "));
		msg.Append(emptyFileName);
		msg.ZeroTerminate();
		AssertTrueL(ETrue, msg);

		_LIT( KRootPath,					"C:\\Nokia\\Images\\" );
		_LIT( KDefaultFileName,				"DynamicFilename.jpg" );
		TFileName rootFileName( KRootPath );
		TFileName defaultFileName( KDefaultFileName );
		iDlg->GetMemories(iMemory, &rootFileName, &defaultFileName);

		msg = (_L("memory got, root: "));
		msg.Append(rootFileName);
		msg.Append(_L(" default file: "));
		msg.Append(defaultFileName);
		msg.ZeroTerminate();
		AssertTrueL(ETrue, msg);
	}
}


// EOF