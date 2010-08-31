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
* Description:  test skinnable_clock_api
 *
*/



// INCLUDE FILES
#include <stiftestinterface.h>
#include <settingserverclient.h>
#include <e32property.h>

#include "testdomskinnableclock.h"

// CONSTANTS
_LIT( KModuleName, "testdomskinnableclock.dll" );

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomSkinnableClock::CTestDomSkinnableClock
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CTestDomSkinnableClock::CTestDomSkinnableClock( CTestModuleIf& aTestModuleIf ):
    CScriptBase( aTestModuleIf )
    {
    }

// -----------------------------------------------------------------------------
// CTestDomSkinnableClock::~CTestDomSkinnableClock
// Destructor.
// -----------------------------------------------------------------------------
//
CTestDomSkinnableClock::~CTestDomSkinnableClock()
    {
    // Delete logger
    delete iLog; 
    if ( iControl )
        {
        CCoeEnv::Static()->AppUi()->RemoveFromStack( iContainer );
        }
    delete iControl;

    }

// -----------------------------------------------------------------------------
// CTestDomSkinnableClock::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTestDomSkinnableClock::ConstructL()
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
        logFileName.Format( KtestdomskinnableclockLogFileWithTitle, &title );
        }
    else
        {
        logFileName.Copy( KtestdomskinnableclockLogFile );
        }

    iLog = CStifLogger::NewL( KtestdomskinnableclockLogPath, 
                          logFileName,
                          CStifLogger::ETxt,
                          CStifLogger::EFile,
                          EFalse );
    
    SendTestClassVersion();
    TRect rect = CEikonEnv::Static()->AppUiFactory()->ClientRect();
    iContainer = CTestDomClockContainer::NewL( rect );
    CCoeEnv::Static()->AppUi()->AddToStackL( iContainer );
    }

// -----------------------------------------------------------------------------
// CTestDomSkinnableClock::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTestDomSkinnableClock* CTestDomSkinnableClock::NewL( CTestModuleIf& aTestModuleIf )
    {
    CTestDomSkinnableClock* self = new( ELeave ) CTestDomSkinnableClock( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );

    return self;

    }

//-----------------------------------------------------------------------------
// CTestDomSkinnableClock::SendTestClassVersion
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
void CTestDomSkinnableClock::SendTestClassVersion()
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
    return ( CScriptBase* ) CTestDomSkinnableClock::NewL( aTestModuleIf );
    }

//  End of File
