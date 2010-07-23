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
* Description:  test private_ui_framework_api
*
*/



// INCLUDE FILES
#include <stiftestinterface.h>
#include <settingserverclient.h>
#include <e32property.h>

#include "testsdkprivateuiframework.h"

// CONSTANTS
_LIT( KModuleName, "testsdkprivateuiframework.dll" );

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSdkPrivateUiFramework::CTestSdkPrivateUiFramework
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CTestSdkPrivateUiFramework::CTestSdkPrivateUiFramework( CTestModuleIf& aTestModuleIf ):
    CScriptBase( aTestModuleIf )
    {
    }

// -----------------------------------------------------------------------------
// CTestSdkPrivateUiFramework::~CTestSdkPrivateUiFramework
// Destructor.
// -----------------------------------------------------------------------------
//
CTestSdkPrivateUiFramework::~CTestSdkPrivateUiFramework()
    {
    // Delete logger
    delete iLog; 

    CCoeEnv::Static()->DeleteResourceFile( iOffset );
    }

// -----------------------------------------------------------------------------
// CTestSdkPrivateUiFramework::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTestSdkPrivateUiFramework::ConstructL()
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
        logFileName.Format( KtestsdkprivateuiframeworkLogFileWithTitle, &title );
        }
    else
        {
        logFileName.Copy( KtestsdkprivateuiframeworkLogFile );
        }

    iLog = CStifLogger::NewL( KtestsdkprivateuiframeworkLogPath, 
                          logFileName,
                          CStifLogger::ETxt,
                          CStifLogger::EFile,
                          EFalse );
    
    SendTestClassVersion();
    
    _LIT( KResourceFile, "c:\\resource\\testsdkprivateuiframework.rsc" );
    iOffset = CCoeEnv::Static()->AddResourceFileL( KResourceFile );
    
    }

// -----------------------------------------------------------------------------
// CTestSdkPrivateUiFramework::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTestSdkPrivateUiFramework* CTestSdkPrivateUiFramework::NewL( CTestModuleIf& aTestModuleIf )
    {
    CTestSdkPrivateUiFramework* self = new( ELeave ) CTestSdkPrivateUiFramework( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );

    return self;

    }

//-----------------------------------------------------------------------------
// CTestSdkPrivateUiFramework::SendTestClassVersion
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
void CTestSdkPrivateUiFramework::SendTestClassVersion()
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
    return ( CScriptBase* ) CTestSdkPrivateUiFramework::NewL( aTestModuleIf );
    }
//  End of File


