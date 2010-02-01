/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies). 
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
* Description: This file contains testclass implementation.
*
*/

// INCLUDE FILES
#include <Stiftestinterface.h>
#include <SettingServerClient.h>
#include <aknappui.h>
#include <aknenv.h>
#include <eikmenub.h>
#include <f32file.h>
#include <eikenv.h>
#include <testdomoptionsmenu.rsg>

#include "testdomoptionsmenu.h"
#include "testoptionsmenu.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKDomMenu::CTestSDKDomMenu
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CTestDomOptionsMenu::CTestDomOptionsMenu( 
    CTestModuleIf& aTestModuleIf ):
        CScriptBase( aTestModuleIf )
    {
    }

// -----------------------------------------------------------------------------
// CTestDomOptionsMenu::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTestDomOptionsMenu::ConstructL()
    {
    //Read logger settings to check whether test case name is to be
    //appended to log file name.
    RSettingServer settingServer;
    TInt ret = settingServer.Connect();
    if(ret != KErrNone)
        {
        User::Leave(ret);
        }
    // Struct to StifLogger settigs.
    TLoggerSettings loggerSettings; 
    // Parse StifLogger defaults from STIF initialization file.
    ret = settingServer.GetLoggerSettings(loggerSettings);
    if(ret != KErrNone)
        {
        User::Leave(ret);
        } 
    // Close Setting server session
    settingServer.Close();

    TFileName logFileName;
    
    if(loggerSettings.iAddTestCaseTitle)
        {
        TName title;
        TestModuleIf().GetTestCaseTitleL(title);
        logFileName.Format(KTestSDKDomMenuLogFileWithTitle, &title);
        }
    else
        {
        logFileName.Copy(KTestSDKDomMenuLogFile);
        }

    iLog = CStifLogger::NewL( KTestSDKDomMenuLogPath, 
                          logFileName,
                          CStifLogger::ETxt,
                          CStifLogger::EFile,
                          EFalse );
    
    SendTestClassVersion();
    
    // This is a really dirty hack. But we can not make STIF support single click, otherwise
    // these single clicke methods can be tested.
    CAknAppUiBase* appui = iAvkonAppUiBase;
    
    TBitFlags* flag = (TBitFlags*)((TInt*)appui + 18);
    flag->Set(14);
    TFindFile find(CCoeEnv::Static()->FsSession());
   
    _LIT( KResourceFile, "\\resource\\testdomoptionsmenu.rsc" );
    _LIT( KResourceDir, "\\resource\\");
    if ( KErrNone == find.FindByDir( KResourceFile, KResourceDir) )
    	{
    	iOffset = CCoeEnv::Static()->AddResourceFileL( find.File() );
    	}
    else
    	{
    	iOffset = CCoeEnv::Static()->AddResourceFileL( KResourceFile );
    	}
    iCollection = new(ELeave) TTestCollection;
    iEikMenuBar = new(ELeave) CEikMenuBar;
    MEikMenuObserver* fepMenuObserver =  CAknEnv::Static()->FepMenuObserver();
    iEikMenuBar->ConstructL( fepMenuObserver, 0, R_MENUTESTMENU_MENUBAR_MAIN );
    iEikMenuBarTitle = new ( ELeave )CEikMenuBarTitle();
    }

// -----------------------------------------------------------------------------
// CTestDomOptionsMenu::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTestDomOptionsMenu* CTestDomOptionsMenu::NewL( 
    CTestModuleIf& aTestModuleIf )
    {
    CTestDomOptionsMenu* self = new (ELeave) CTestDomOptionsMenu( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;

    }

// Destructor
CTestDomOptionsMenu::~CTestDomOptionsMenu()
    { 

    // Delete resources allocated from test methods
    Delete();

    // Delete logger
    delete iLog; 

    }

//-----------------------------------------------------------------------------
// CTestDomOptionsMenu::SendTestClassVersion
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
void CTestDomOptionsMenu::SendTestClassVersion()
	{
	TVersion moduleVersion;
	moduleVersion.iMajor = TEST_CLASS_VERSION_MAJOR;
	moduleVersion.iMinor = TEST_CLASS_VERSION_MINOR;
	moduleVersion.iBuild = TEST_CLASS_VERSION_BUILD;
	
	TFileName moduleName;
	moduleName = _L("TestSDKDomMenu.dll");

	TBool newVersionOfMethod = ETrue;
	TestModuleIf().SendTestModuleVersion(moduleVersion, moduleName, newVersionOfMethod);
	}

// ========================== OTHER EXPORTED FUNCTIONS =========================

// -----------------------------------------------------------------------------
// LibEntryL is a polymorphic Dll entry point.
// Returns: CScriptBase: New CScriptBase derived object
// -----------------------------------------------------------------------------
//
EXPORT_C CScriptBase* LibEntryL( 
    CTestModuleIf& aTestModuleIf ) // Backpointer to STIF Test Framework
    {

    return ( CScriptBase* ) CTestDomOptionsMenu::NewL( aTestModuleIf );

    }


//  End of File
