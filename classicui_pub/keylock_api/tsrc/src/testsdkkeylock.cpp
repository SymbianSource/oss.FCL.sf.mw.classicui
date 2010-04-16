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
* Description:  Test AknKeyLock.h
*
*/


// INCLUDE FILES
#include <stiftestinterface.h>
#include <settingserverclient.h>

#include "testsdkkeylock.h"
CTestSDKKeyLock::CTestSDKKeyLock( CTestModuleIf& aTestModuleIf ): 
                 CScriptBase( aTestModuleIf )
    {
    }

// -----------------------------------------------------------------------------
// CTestSDKKeyLock::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTestSDKKeyLock::ConstructL()
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
        User::Leave( ret );
        } 
    // Close Setting server session
    CleanupStack::PopAndDestroy( &settingServer );

    TFileName logFileName;
    
    if( loggerSettings.iAddTestCaseTitle )
        {
        TName title;
        TestModuleIf().GetTestCaseTitleL( title );
        logFileName.Format( KtestsdkkeylockLogFileWithTitle, &title );
        }
    else
        {
        logFileName.Copy( KtestsdkkeylockLogFile );
        }

    iLog = CStifLogger::NewL( KtestsdkkeylockLogPath, 
                          logFileName,
                          CStifLogger::ETxt,
                          CStifLogger::EFile,
                          EFalse );
    
    SendTestClassVersion();
    }

// -----------------------------------------------------------------------------
// CTestSDKKeyLock::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTestSDKKeyLock* CTestSDKKeyLock::NewL( 
    CTestModuleIf& aTestModuleIf )
    {
    CTestSDKKeyLock* self = new(ELeave) CTestSDKKeyLock( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );

    return self;

    }

// Destructor
CTestSDKKeyLock::~CTestSDKKeyLock()
    { 

    // Delete resources allocated from test methods
    Delete();

    // Delete logger
    delete iLog; 

    }

//-----------------------------------------------------------------------------
// CTestSDKKeyLock::SendTestClassVersion
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
void CTestSDKKeyLock::SendTestClassVersion()
    {
    TVersion moduleVersion;
    moduleVersion.iMajor = TEST_CLASS_VERSION_MAJOR;
    moduleVersion.iMinor = TEST_CLASS_VERSION_MINOR;
    moduleVersion.iBuild = TEST_CLASS_VERSION_BUILD;
    
    _LIT( KFileName, "testsdkk.dll" );
    TFileName moduleName( KFileName );

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

    return ( CScriptBase* ) CTestSDKKeyLock::NewL( aTestModuleIf );

    }
//  End of File

