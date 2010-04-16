/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test options_menu_api
 *
*/



// INCLUDE FILES
#include <stiftestinterface.h>
#include <settingserverclient.h>
#include <e32property.h>
#include <coemain.h>
#include <aknenv.h>

#include "testsdkoptionsmenu.h"
#include "testoptionsmenu.h"

_LIT( KModuleName, "testsdkoptionsmenu.dll" );

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctestsdkoptionsmenu::Ctestsdkoptionsmenu
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CTestSDKOptionsMenu::CTestSDKOptionsMenu( CTestModuleIf& aTestModuleIf ):
    CScriptBase( aTestModuleIf )
    {
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::~CTestSDKOptionsMenu
// Destructor.
// -----------------------------------------------------------------------------
//
CTestSDKOptionsMenu::~CTestSDKOptionsMenu()
    {
     //delete logger;
    delete iLog; 
    delete iEikMenuBarTitle;
    delete iEikMenuBar;
    delete iEikMenuPaneTitle;
    delete iEikMenuPaneItem ;
    iLog=NULL;
    iEikMenuBarTitle=NULL;
    iEikMenuBar=NULL;
    iEikMenuPaneTitle=NULL;
    iEikMenuPaneItem=NULL;

    CCoeEnv::Static()->DeleteResourceFile( iOffset );
    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTestSDKOptionsMenu::ConstructL()
    {
    //Read logger settings to check whether test case name is to be
    //appended to log file name.
    RSettingServer settingServer;
    CleanupClosePushL( settingServer );
    TInt ret = settingServer.Connect();
    if ( ret != KErrNone )
        {
        User::Leave(ret);
        }
    // Struct to StifLogger settigs.
    TLoggerSettings loggerSettings; 
    // Parse StifLogger defaults from STIF initialization file.
    ret = settingServer.GetLoggerSettings( loggerSettings );
    if ( ret != KErrNone )
        {
        User::Leave( ret );
        } 
    // Close Setting server session
    settingServer.Close();
    CleanupStack::PopAndDestroy( &settingServer );

    TFileName logFileName;
    
    if ( loggerSettings.iAddTestCaseTitle )
        {
        TName title;
        TestModuleIf().GetTestCaseTitleL( title );
        logFileName.Format( KtestsdkoptionsmenuLogFileWithTitle, &title );
        }
    else
        {
        logFileName.Copy( KtestsdkoptionsmenuLogFile );
        }

    iLog = CStifLogger::NewL( KtestsdkoptionsmenuLogPath, 
                          logFileName,
                          CStifLogger::ETxt,
                          CStifLogger::EFile,
                          EFalse );
    
    SendTestClassVersion();
    
#ifdef __WINSCW__
    iOffset = CCoeEnv::Static()->AddResourceFileL(_L("z:\\resource\\testsdkoptionsmenu.rsc"));
#else                          
    iOffset = CCoeEnv::Static()->AddResourceFileL(_L("C:\\resource\\testsdkoptionsmenu.rsc"));
#endif // __WINSCW__
	
    iEikMenuBarTitle = new ( ELeave )CEikMenuBarTitle();
    iEikMenuBar = new ( ELeave ) CEikMenuBar();
    iEikMenuPaneTitle = new ( ELeave )CEikMenuPaneTitle( iEikMenuBar );
    iEikMenuPaneItem = new ( ELeave )CEikMenuPaneItem();
    TRect rect = CEikonEnv::Static()->AppUiFactory()->ClientRect();
    iContainer = CTestSDKOptionsMenuContainer::NewL( rect );
    CCoeEnv::Static()->AppUi()->AddToStackL( iContainer );

    }

// -----------------------------------------------------------------------------
// CTestSDKOptionsMenu::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTestSDKOptionsMenu* CTestSDKOptionsMenu::NewL( CTestModuleIf& aTestModuleIf )
    {
    CTestSDKOptionsMenu* self = new( ELeave ) CTestSDKOptionsMenu( aTestModuleIf );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;

    }


//-----------------------------------------------------------------------------
// CTestSDKOptionsMenu::SendTestClassVersion
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
void CTestSDKOptionsMenu::SendTestClassVersion()
    {
    TVersion moduleVersion;
    moduleVersion.iMajor = TEST_CLASS_VERSION_MAJOR;
    moduleVersion.iMinor = TEST_CLASS_VERSION_MINOR;
    moduleVersion.iBuild = TEST_CLASS_VERSION_BUILD;
    TFileName moduleName;
    moduleName = KModuleName;
    TBool newVersionOfMethod = ETrue;
    TestModuleIf().SendTestModuleVersion( moduleVersion, moduleName, 
                                                            newVersionOfMethod );
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
    return ( CScriptBase* ) CTestSDKOptionsMenu::NewL( aTestModuleIf );
    }

//  End of File
