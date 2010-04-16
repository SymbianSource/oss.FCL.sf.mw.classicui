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
* Description:    Test aiw_criteria_api
 *
*/




// INCLUDE FILES
#include <stiftestinterface.h>
#include <settingserverclient.h>
#include <e32property.h>

#include "testsdkaiwcri.h"

_LIT( KResourcePath, "C:\\resource\\testsdkaiwcri.rsc" );

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctestsdkaiwcri::Ctestsdkaiwcri
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CTestSDKAiwCri::CTestSDKAiwCri( CTestModuleIf& aTestModuleIf ) :
    CScriptBase(aTestModuleIf)
    {
    }

// -----------------------------------------------------------------------------
// Ctestsdkaiwcri::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTestSDKAiwCri::ConstructL()
    {
    //Read logger settings to check whether test case name is to be
    //appended to log file name.
    RSettingServer settingServer;
    CleanupClosePushL( settingServer );
    TInt ret = settingServer.Connect();
    if ( ret != KErrNone )
        {
        User::Leave( ret );
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
        logFileName.Format( KtestsdkaiwcriLogFileWithTitle, &title );
        }
    else
        {
        logFileName.Copy( KtestsdkaiwcriLogFile );
        }

    iLog = CStifLogger::NewL( KtestsdkaiwcriLogPath, logFileName,
        CStifLogger::ETxt, CStifLogger::EFile, EFalse );

    iOffset = CCoeEnv::Static()->AddResourceFileL( KResourcePath );

    SendTestClassVersion();
    }

// -----------------------------------------------------------------------------
// Ctestsdkaiwcri::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTestSDKAiwCri* CTestSDKAiwCri::NewL( CTestModuleIf& aTestModuleIf )
    {
    CTestSDKAiwCri* self = new (ELeave) CTestSDKAiwCri( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;

    }

// Destructor
CTestSDKAiwCri::~CTestSDKAiwCri()
    {

    // Delete resources allocated from test methods
    Delete( );

    // Delete logger
    delete iLog;

    CCoeEnv::Static()->DeleteResourceFile( iOffset );
    }

//-----------------------------------------------------------------------------
// Ctestsdkaiwcri::SendTestClassVersion
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
void CTestSDKAiwCri::SendTestClassVersion()
    {
    TVersion moduleVersion;
    moduleVersion.iMajor = TEST_CLASS_VERSION_MAJOR;
    moduleVersion.iMinor = TEST_CLASS_VERSION_MINOR;
    moduleVersion.iBuild = TEST_CLASS_VERSION_BUILD;

    TFileName moduleName;
    moduleName = _L("testsdkaiwcri.dll");

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

    return ( CScriptBase* ) CTestSDKAiwCri::NewL( aTestModuleIf );

    }
//  End of File
