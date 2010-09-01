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
* Description:  ?Description
*
*/



// INCLUDE FILES
#include <stiftestinterface.h>
#include <settingserverclient.h>
#include <screensaverinternalpskeys.h>
#include <e32property.h>
#include <coemain.h>
#include <eikclb.h>
#include <coeaui.h>

#include "testdompslnframework.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctestdompslnframework::Ctestdompslnframework
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CTestDOMPSLNFramework::CTestDOMPSLNFramework( 
    CTestModuleIf& aTestModuleIf ):
        CScriptBase( aTestModuleIf )
    {
    }

// -----------------------------------------------------------------------------
// Ctestdompslnframework::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTestDOMPSLNFramework::ConstructL()
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
        logFileName.Format(KtestdompslnframeworkLogFileWithTitle, &title);
        }
    else
        {
        logFileName.Copy(KtestdompslnframeworkLogFile);
        }

    iLog = CStifLogger::NewL( KtestdompslnframeworkLogPath, 
                          logFileName,
                          CStifLogger::ETxt,
                          CStifLogger::EFile,
                          EFalse );
    
    iOffset = CCoeEnv::Static()->AddResourceFileL( KFilePath );
    

    TurnOffScreenSaver();

    SendTestClassVersion();

    }

// -----------------------------------------------------------------------------
// Ctestdompslnframework::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTestDOMPSLNFramework* CTestDOMPSLNFramework::NewL( 
    CTestModuleIf& aTestModuleIf )
    {
    CTestDOMPSLNFramework* self = new (ELeave) CTestDOMPSLNFramework( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;

    }

// Destructor
CTestDOMPSLNFramework::~CTestDOMPSLNFramework()
    { 

    // Delete resources allocated from test methods
    Delete();

    if ( iEikonEnvPointer )
        {
        delete iEikonEnvPointer;
        iEikonEnvPointer = NULL;
        }
    // Delete logger
    delete iLog;
    CCoeEnv::Static()->DeleteResourceFile( iOffset );

    RestoreScreenSaver();

    }

//-----------------------------------------------------------------------------
// Ctestdompslnframework::SendTestClassVersion
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
void CTestDOMPSLNFramework::SendTestClassVersion()
	{
	TVersion moduleVersion;
	moduleVersion.iMajor = TEST_CLASS_VERSION_MAJOR;
	moduleVersion.iMinor = TEST_CLASS_VERSION_MINOR;
	moduleVersion.iBuild = TEST_CLASS_VERSION_BUILD;
	
	TFileName moduleName;
	moduleName = _L("testdompslnframework.dll");

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

    return ( CScriptBase* ) CTestDOMPSLNFramework::NewL( aTestModuleIf );

    }


// -----------------------------------------------------------------------------
// Turn off ScreenSaver
// -----------------------------------------------------------------------------
//
void CTestDOMPSLNFramework::TurnOffScreenSaver()
    {
    TInt err1 = RProperty::Get(KPSUidScreenSaver, KScreenSaverAllowScreenSaver,
        iOldScreenSaverProperty);
    TInt err2 = RProperty::Set(KPSUidScreenSaver, KScreenSaverAllowScreenSaver,
        KScreenSaverAllowScreenSaver);    
    RDebug::Printf("screensaver property=%d err1=%d err2=%d\n",
        iOldScreenSaverProperty, err1, err2);
    }

// -----------------------------------------------------------------------------
// Restore ScreenSaver
// -----------------------------------------------------------------------------
//
void CTestDOMPSLNFramework::RestoreScreenSaver()
    {
    RProperty::Set(KPSUidScreenSaver, KScreenSaverAllowScreenSaver,
        iOldScreenSaverProperty);
    User::ResetInactivityTime();
    }
//  End of File
