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
* Description:  Test sounds_api 
 *
*/


// INCLUDE FILES
#include <stiftestinterface.h>
#include <settingserverclient.h>
#include <screensaverinternalpskeys.h>
#include <e32property.h>
#include <coemain.h>

#include "testsdksounds.h"

// CONSTANTS
_LIT( KModuleName, "testsdksounds.dll" );

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctestsdksounds::Ctestsdksounds
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CTestSDKSounds::CTestSDKSounds(CTestModuleIf& aTestModuleIf) :
    CScriptBase(aTestModuleIf)
    {
    }

// -----------------------------------------------------------------------------
// Ctestsdksounds::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTestSDKSounds::ConstructL()
    {
    //Read logger settings to check whether test case name is to be
    //appended to log file name.
    RSettingServer settingServer;
    CleanupClosePushL(settingServer);
    TInt ret = settingServer.Connect();
    if (ret != KErrNone)
        {
        User::Leave(ret);
        }
    // Struct to StifLogger settigs.
    TLoggerSettings loggerSettings;
    // Parse StifLogger defaults from STIF initialization file.
    ret = settingServer.GetLoggerSettings(loggerSettings);
    if (ret != KErrNone)
        {
        User::Leave(ret);
        }
    // Close Setting server session
    settingServer.Close();
    CleanupStack::PopAndDestroy( &settingServer);
    
    TFileName logFileName;
    
    if (loggerSettings.iAddTestCaseTitle)
        {
        TName title;
        TestModuleIf().GetTestCaseTitleL(title);
        logFileName.Format(KtestsdksoundsLogFileWithTitle, &title);
        }
    else
        {
        logFileName.Copy(KtestsdksoundsLogFile);
        }
    
    iLog = CStifLogger::NewL(KtestsdksoundsLogPath, logFileName, CStifLogger::ETxt,
            CStifLogger::EFile, EFalse);
    
    SendTestClassVersion();
    
    TurnOffScreenSaver();
    _LIT( KResourceFile, "c:\\resource\\testsdksounds.rsc" );
    iOffset = CCoeEnv::Static()->AddResourceFileL(KResourceFile);
    }

// -----------------------------------------------------------------------------
// Ctestsdksounds::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTestSDKSounds* CTestSDKSounds::NewL(CTestModuleIf& aTestModuleIf)
    {
    CTestSDKSounds* self = new( ELeave ) CTestSDKSounds( aTestModuleIf );
    
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    
    return self;
    
    }

// Destructor
CTestSDKSounds::~CTestSDKSounds()
    {
    
    // Delete resources allocated from test methods
    Delete();
    
    // Delete logger
    delete iLog;
    
    CCoeEnv::Static()->DeleteResourceFile( iOffset );

    RestoreScreenSaver();
    }

//-----------------------------------------------------------------------------
// Ctestsdksounds::SendTestClassVersion
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
void CTestSDKSounds::SendTestClassVersion()
    {
    TVersion moduleVersion;
    moduleVersion.iMajor = TEST_CLASS_VERSION_MAJOR;
    moduleVersion.iMinor = TEST_CLASS_VERSION_MINOR;
    moduleVersion.iBuild = TEST_CLASS_VERSION_BUILD;
    
    TFileName moduleName;
    moduleName = KModuleName;
    
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
    return ( CScriptBase* ) CTestSDKSounds::NewL( aTestModuleIf );
    }

// -----------------------------------------------------------------------------
// Turn off ScreenSaver
// -----------------------------------------------------------------------------
//
void CTestSDKSounds::TurnOffScreenSaver()
    {
    TInt err1 = RProperty::Get(KPSUidScreenSaver, KScreenSaverAllowScreenSaver,
            iOldScreenSaverProperty);
    TInt err2 = RProperty::Set(KPSUidScreenSaver, KScreenSaverAllowScreenSaver,
            KScreenSaverAllowScreenSaver);
    RDebug::Printf("screensaver property=%d err1=%d err2=%d\n", iOldScreenSaverProperty, err1, err2);
    }

// -----------------------------------------------------------------------------
// Restore ScreenSaver
// -----------------------------------------------------------------------------
//
void CTestSDKSounds::RestoreScreenSaver()
    {
    RProperty::Set(KPSUidScreenSaver, KScreenSaverAllowScreenSaver, iOldScreenSaverProperty);
    User::ResetInactivityTime();
    }

//  End of File