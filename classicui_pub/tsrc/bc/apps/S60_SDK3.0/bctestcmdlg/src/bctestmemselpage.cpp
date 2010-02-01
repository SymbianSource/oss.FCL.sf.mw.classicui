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

#include "BCTestMemSelPage.h"
#include "BCTestCmDlg.hrh"
#include "streamlogger.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestMemSelSettingPage* CBCTestMemSelSettingPage::NewL()
    {
    CBCTestMemSelSettingPage* self = new( ELeave ) CBCTestMemSelSettingPage();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestMemSelSettingPage::CBCTestMemSelSettingPage():iDlg(0)
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestMemSelSettingPage::~CBCTestMemSelSettingPage()
    {  
	delete iDlg;
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestMemSelSettingPage::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestMemSelSettingPage::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestMemSelSettingPage::BuildScriptL()
    { 
	AddTestL( DELAY(1), TEND);

    // Add script as your need.   
	for(int i=0; i<EBCTestCmdMemSelPageEnd - EBCTestCmdMemSelPageBegin -1; ++i)
		{
		AddTestL( LeftCBA, REP(Down, 1), Right, TEND );
		for(int j=0; j<i; ++j)
			AddTestL( Down, TEND);
		AddTestL( LeftCBA, TEND );	
		AddOKL();
		}
    }
    
void CBCTestMemSelSettingPage::AddOKL()
	{
	// add dlg response sciprts
	for(int i=0; i<1; ++i)
		AddTestL( WAIT(5), KeyOK, TEND);
	}

void CBCTestMemSelSettingPage::AddCancelL()
	{
	// add dlg response sciprts
	for(int i=0; i<1; ++i)
		AddTestL( WAIT(5), RightCBA, TEND);
	}

// ---------------------------------------------------------------------------
// CBCTestMemSelSettingPage::RunL
// ---------------------------------------------------------------------------
//
void CBCTestMemSelSettingPage::RunL( TInt aCmd )
    {
	SetupL();
	switch(aCmd){
	case EBCTestCmdMemSelPageCreate:
		TestCreateL();
		break;
	case EBCTestCmdMemSelPageCreateRes:
		TestCreateL(0);		// 0 is default res id
		break;
	case EBCTestCmdMemSelPageQuickCreate:
		TestQuickCreateL();
		break;
	case EBCTestCmdMemSelPageQuickCreateTitle:
		TestQuickCreateL(_L("a title"));
		break;
	case EBCTestCmdMemSelPageQuickCreateRes:
		TestQuickCreateL(0);	// 0 is the default res id
		break;
	default:
		break;
	}
    Teardown();
    }

// ---------------------------------------------------------------------------
// CBCTestMemSelSettingPage::ReleaseCaseL
// ---------------------------------------------------------------------------
//   
void CBCTestMemSelSettingPage::Teardown()
    {
	delete iDlg;
	iDlg = NULL;
    }

void CBCTestMemSelSettingPage::TestCreateL()
	{
	_LIT( KRootPath,					"C:\\Nokia\\Images\\" );
	_LIT( KDefaultFileName,				"DynamicFilename.jpg" );
	TFileName emptyFileName( KNullDesC );
	TFileName rootFileName( KRootPath );
	TFileName defaultFileName( KDefaultFileName );

	iDlg = CAknMemorySelectionSettingPage::NewL();
	AssertNotNullL(iDlg, _L("mem sel setting page created"));

	TInt returnValue = iDlg->ExecuteL( iMemory, &rootFileName, &defaultFileName );
	iDlg->GetItem( iMemory, emptyFileName );

	TFileName msg;
	msg.Format( _L("User Hit: %d, Memory is: %d, FileName: "), returnValue, iMemory );
	msg.Append( emptyFileName );
	msg.ZeroTerminate();
	AssertTrueL(ETrue, msg);
	msg.Append( _L("Root: ") );
	msg.Append( rootFileName );
	msg.Append( _L(", Default: ") );
	msg.Append( defaultFileName );
	msg.ZeroTerminate();
	AssertTrueL(ETrue, msg);
	}

void CBCTestMemSelSettingPage::TestCreateL(TInt aResID)
	{
	iDlg = CAknMemorySelectionSettingPage::NewL( aResID );
	TInt returnValue = iDlg->ExecuteL( iMemory);
	AssertTrueL( returnValue, _L("Create with Resorce ID"));
	}

void CBCTestMemSelSettingPage::TestQuickCreateL()
	{
	AssertTrueL(CAknMemorySelectionSettingPage::RunDlgLD(iMemory), _L("Quick create, User hit OK"));
	AssertIntL( CAknMemorySelectionSettingPage::EPhoneMemory, iMemory, _L("Phone memroy created"));
	}

void CBCTestMemSelSettingPage::TestQuickCreateL(const TDesC &aTitle)
	{
	AssertTrueL(CAknMemorySelectionSettingPage::RunDlgLD(iMemory, aTitle), _L("Quick create with title, User hit OK"));
	AssertIntL( CAknMemorySelectionSettingPage::EPhoneMemory, iMemory, _L("Phone memroy created"));
	}

void CBCTestMemSelSettingPage::TestQuickCreateL(TInt aResID)
	{
	AssertTrueL(CAknMemorySelectionSettingPage::RunDlgLD(iMemory, aResID), _L("Quick create with ResID, User hit OK"));
	AssertIntL( CAknMemorySelectionSettingPage::EPhoneMemory, iMemory, _L("Phone memroy created"));
	}

void CBCTestMemSelSettingPage::SetupL()
	{
	iMemory = CAknMemorySelectionDialog::EPhoneMemory;
	}

