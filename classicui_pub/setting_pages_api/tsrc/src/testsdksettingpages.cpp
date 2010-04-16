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
* Description:  Test all .h files in settingpages_api
*
*/



// INCLUDE FILES
#include <stiftestinterface.h>
#include <settingserverclient.h>
#include <e32property.h>
#include <coemain.h>

#include "testsdksettingpages.h"

// ============================ MEMBER FUNCTIONS ===============================

// CONSTANTS
_LIT( KModuleName, "testsdksettingpages.dll" );

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctestsdksettingpages::Ctestsdksettingpages
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CTestSDKSettingPages::CTestSDKSettingPages( CTestModuleIf& aTestModuleIf ):
    CScriptBase( aTestModuleIf )
    {
    }

// -----------------------------------------------------------------------------
// Ctestsdksettingpages::~Ctestsdksettingpages
// Destructor.
// -----------------------------------------------------------------------------
//
CTestSDKSettingPages::~CTestSDKSettingPages()
    {
    // Delete logger
    delete iLog; 

    CCoeEnv::Static()->DeleteResourceFile( iOffset );
    }

// -----------------------------------------------------------------------------
// Ctestsdksettingpages::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTestSDKSettingPages::ConstructL()
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
        logFileName.Format( KtestsdksettingpagesLogFileWithTitle, &title );
        }
    else
        {
        logFileName.Copy( KtestsdksettingpagesLogFile );
        }

    iLog = CStifLogger::NewL( KtestsdksettingpagesLogPath, 
                          logFileName,
                          CStifLogger::ETxt,
                          CStifLogger::EFile,
                          EFalse );
                          
#ifdef __WINSCW__
    iOffset = CCoeEnv::Static()->AddResourceFileL(_L("z:\\resource\\testsdksettingpages.rsc"));
#else                          
    iOffset = CCoeEnv::Static()->AddResourceFileL(_L("C:\\resource\\testsdksettingpages.rsc"));
#endif // __WINSCW__
    SendTestClassVersion();
    }

// -----------------------------------------------------------------------------
// Ctestsdksettingpages::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTestSDKSettingPages* CTestSDKSettingPages::NewL( CTestModuleIf& aTestModuleIf )
    {
    CTestSDKSettingPages* self = new( ELeave ) CTestSDKSettingPages( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );

    return self;

    }

//-----------------------------------------------------------------------------
// Ctestsdksettingpages::SendTestClassVersion
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
void CTestSDKSettingPages::SendTestClassVersion()
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
    return ( CScriptBase* ) CTestSDKSettingPages::NewL( aTestModuleIf );
    }
//  End of File
