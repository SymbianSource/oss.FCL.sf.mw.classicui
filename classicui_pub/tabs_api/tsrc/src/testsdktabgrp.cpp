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
* Description:  test akntabgrp.h
*
*/



// INCLUDE FILES
#include <stiftestinterface.h>
#include <settingserverclient.h>
#include <e32property.h>

#include "testsdktabgrp.h"

// CONSTANTS
_LIT( KModuleName, "testsdktabgrp.dll" );

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKTabGroup::CTestSDKTabGroup
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CTestSDKTabGroup::CTestSDKTabGroup( CTestModuleIf& aTestModuleIf ):
    CScriptBase( aTestModuleIf )
    {
    iEikonEnvPointer = CEikonEnv::Static();
    }

// -----------------------------------------------------------------------------
// CTestSDKTabGroup::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTestSDKTabGroup::ConstructL()
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
        logFileName.Format( KTestSDKTabGroupLogFileWithTitle, &title );
        }
    else
        {
        logFileName.Copy( KTestSDKTabGroupLogFile );
        }

    iLog = CStifLogger::NewL( KTestSDKTabGroupLogPath, 
                          logFileName,
                          CStifLogger::ETxt,
                          CStifLogger::EFile,
                          EFalse );
    
    _LIT( KResourceFile, "C:\\resource\\testsdktabgrp.rsc" );
    iOffset = iEikonEnvPointer->AddResourceFileL( KResourceFile );

    SendTestClassVersion();
    }

// -----------------------------------------------------------------------------
// CTestSDKTabGroup::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTestSDKTabGroup* CTestSDKTabGroup::NewL( CTestModuleIf& aTestModuleIf )
    {
    CTestSDKTabGroup* self = new( ELeave ) CTestSDKTabGroup( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );

    return self;

    }

// Destructor
CTestSDKTabGroup::~CTestSDKTabGroup()
    { 

    // Delete resources allocated from test methods
    Delete();

    // Delete logger
    delete iLog; 

    CCoeEnv::Static()->DeleteResourceFile( iOffset );
    }

//-----------------------------------------------------------------------------
// CTestSDKTabGroup::SendTestClassVersion
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
void CTestSDKTabGroup::SendTestClassVersion()
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
    return ( CScriptBase* ) CTestSDKTabGroup::NewL( aTestModuleIf );
    }

//  End of File
