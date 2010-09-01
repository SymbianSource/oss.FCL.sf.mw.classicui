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
#include <AknLists.h>
#include <aknsettingitemlist.h>
#include <bctestcmdlg.rsg>

#include "BCTestMemSelItem.h"
#include "BCTestCmDlg.hrh"
#include "streamlogger.h"
#include "CVRSettingsDialogMMCSupported.h"

// ======== MEMBER FUNCTIONS ========

const TInt KItemPosition = 5;// Menu position of the test item

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestMemSelSettingItem* CBCTestMemSelSettingItem::NewL()
    {
    CBCTestMemSelSettingItem* self = new( ELeave ) CBCTestMemSelSettingItem();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestMemSelSettingItem::CBCTestMemSelSettingItem():iItem(NULL)
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestMemSelSettingItem::~CBCTestMemSelSettingItem()
    {  
	Teardown();
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestMemSelSettingItem::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestMemSelSettingItem::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestMemSelSettingItem::BuildScriptL()
    { 
	AddTestL( DELAY(1), TEND);

    // Add script as your need.   
	for(int i=0; i<EBCTestCmdMemSelSettingItemEnd - EBCTestCmdMemSelSettingItemBegin -1; ++i)
		{
		AddTestL( LeftCBA, REP( Down, KItemPosition ), Right, TEND );
		for(int j=0; j<i; ++j)
			AddTestL( Down, TEND);
		AddTestL( LeftCBA, TEND );
		if(i == 1)
			{
			AddTestL( LeftCBA, WAIT(2),LeftCBA, WAIT(2), LeftCBA, WAIT(2), RightCBA, TEND);
			}
		AddOKL();
		}
    }
    
void CBCTestMemSelSettingItem::AddOKL()
	{
	// add dlg response sciprts
	for(int i=0; i<1; ++i)
		AddTestL( WAIT(5), KeyOK, TEND);
	}

void CBCTestMemSelSettingItem::AddCancelL()
	{
	// add dlg response sciprts
	for(int i=0; i<1; ++i)
		AddTestL( WAIT(5), RightCBA, TEND);
	}

// ---------------------------------------------------------------------------
// CBCTestMemSelSettingItem::RunL
// ---------------------------------------------------------------------------
//
void CBCTestMemSelSettingItem::RunL( TInt aCmd )
    {
	SetupL();
	switch(aCmd){
	case EBCTestCmdMemSelSettingItemCreate:
		TestCreateL();
		break;
	case EBCTestCmdMemSelSettingItemEdit:
		TestEditL();
		break;
	case EBCTestCmdMemSelSettingItemStore:
		TestStoreL();
		break;
	case EBCTestCmdMemSelSettingItemSetting:
		TestSettingL();
		break;
	default:
		break;
	}
    Teardown();
    }

// ---------------------------------------------------------------------------
// CBCTestMemSelSettingItem::ReleaseCaseL
// ---------------------------------------------------------------------------
//   
void CBCTestMemSelSettingItem::Teardown()
    {
	delete iItem;
	iItem = NULL;
    }

void CBCTestMemSelSettingItem::TestCreateL()
	{
	iItem = new (ELeave) CAknMemorySelectionSettingItem(0, iMemory);
	AssertNotNullL(iItem, _L("Create in Heap"));
	iItem->CompleteConstructionL();
	AssertTrueL(ETrue, _L("complete construction"));
	}

void CBCTestMemSelSettingItem::TestEditL()
	{
	CVRSettingsDialog* settingsDlg = CVRSettingsDialog::NewL();
	settingsDlg->ExecuteLD( R_VR_SETTINGS_DIALOG );
	}

void CBCTestMemSelSettingItem::TestStoreL()
	{
	iItem = new (ELeave) CAknMemorySelectionSettingItem(0, iMemory);
	iItem->StoreL();
	AssertTrueL(ETrue, _L("store"));
	iItem->LoadL();
	AssertTrueL(ETrue, _L("laod"));
	}

void CBCTestMemSelSettingItem::TestSettingL()
	{
	iItem = new (ELeave) CAknMemorySelectionSettingItem(0, iMemory);
	TFileName text(iItem->SettingTextL());
	text.ZeroTerminate();
	AssertTrueL(ETrue, text);
	}

void CBCTestMemSelSettingItem::SetupL()
	{
	iMemory = CAknMemorySelectionDialog::EPhoneMemory;
	}



