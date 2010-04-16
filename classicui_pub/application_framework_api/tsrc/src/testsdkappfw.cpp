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
* Description:  Test application_framework_api
*
*/



// INCLUDE FILES
#include <stiftestinterface.h>
#include <settingserverclient.h>
#include <e32property.h>
#include <coemain.h>
#include <coeaui.h>

#include "testsdkappfw.h"

// CONSTANTS
_LIT( KModuleName, "testsdkappfw.dll" );
_LIT( KResourcePath, "C:\\resource\\testsdkappfw.rsc" );

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKAppFW::CTestSDKAppFW
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CTestSDKAppFW::CTestSDKAppFW( CTestModuleIf& aTestModuleIf ):
    CScriptBase( aTestModuleIf )
    {
    iEikonEnvPointer = CEikonEnv::Static();
    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTestSDKAppFW::ConstructL()
    {
    //Read logger settings to check whether test case name is to be
    //appended to log file name.
    RSettingServer settingServer;
    CleanupClosePushL( settingServer );
    TInt ret = settingServer.Connect();
    if( ret != KErrNone )
        {
        User::Leave( ret );
        }
    // Struct to StifLogger settigs.
    TLoggerSettings loggerSettings; 
    // Parse StifLogger defaults from STIF initialization file.
    ret = settingServer.GetLoggerSettings( loggerSettings );
    if( ret != KErrNone )
        {
        User::Leave(ret);
        } 
    // Close Setting server session
    settingServer.Close();
    CleanupStack::PopAndDestroy( &settingServer );

    TFileName logFileName;
    
    if( loggerSettings.iAddTestCaseTitle )
        {
        TName title;
        TestModuleIf().GetTestCaseTitleL( title );
        logFileName.Format( KtestsdkappfwLogFileWithTitle, &title );
        }
    else
        {
        logFileName.Copy( KtestsdkappfwLogFile );
        }

    iLog = CStifLogger::NewL( KtestsdkappfwLogPath, 
                          logFileName,
                          CStifLogger::ETxt,
                          CStifLogger::EFile,
                          EFalse );
						  
#ifdef __WINSCW__
    iOffset = CCoeEnv::Static()->AddResourceFileL(_L("z:\\resource\\testsdkappfw.rsc"));
#else                          
    iOffset = CCoeEnv::Static()->AddResourceFileL(_L("C:\\resource\\testsdkappfw.rsc"));
#endif // __WINSCW__


    SendTestClassVersion();
    }

// -----------------------------------------------------------------------------
// CTestSDKAppFW::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTestSDKAppFW* CTestSDKAppFW::NewL( CTestModuleIf& aTestModuleIf )
    {
    CTestSDKAppFW* self = new( ELeave ) CTestSDKAppFW( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );

    return self;

    }

// Destructor
CTestSDKAppFW::~CTestSDKAppFW()
    { 

    // Delete resources allocated from test methods
    Delete();

    // Delete logger
    delete iLog; 

    CCoeEnv::Static()->DeleteResourceFile( iOffset );
    }

//-----------------------------------------------------------------------------
// CTestSDKAppFW::SendTestClassVersion
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
void CTestSDKAppFW::SendTestClassVersion()
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
    return ( CScriptBase* ) CTestSDKAppFW::NewL( aTestModuleIf );
    }

//  End of File
