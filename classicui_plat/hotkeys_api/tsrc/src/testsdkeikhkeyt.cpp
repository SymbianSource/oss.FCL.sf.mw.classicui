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
* Description:  test eikhkeyt.h
*
*/



/*
 * INCLUDE FILES
 */
#include <stiftestinterface.h>
#include <settingserverclient.h>
#include <coemain.h>
#include <e32property.h>

#include "testsdkeikhkeyt.h"

_LIT( KModuleName, "testsdkeikhkeyt.dll" );

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKEIKHKEYT::CTestSDKEIKHKEYT
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CTestSDKEIKHKEYT::CTestSDKEIKHKEYT( 
    CTestModuleIf& aTestModuleIf ):
        CScriptBase( aTestModuleIf )
    {
    }

// -----------------------------------------------------------------------------
// CTestSDKEIKHKEYT::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTestSDKEIKHKEYT::ConstructL()
    {
    RSettingServer settingServer;
    CleanupClosePushL( settingServer );
    TInt ret = settingServer.Connect();
    if(ret != KErrNone)
        {
        User::Leave(ret);
        }
    TLoggerSettings loggerSettings; 
    ret = settingServer.GetLoggerSettings(loggerSettings);
    if(ret != KErrNone)
        {
        User::Leave(ret);
        } 
    settingServer.Close();
    CleanupStack::PopAndDestroy( &settingServer );

    TFileName logFileName;
    
    if(loggerSettings.iAddTestCaseTitle)
        {
        TName title;
        TestModuleIf().GetTestCaseTitleL(title);
        logFileName.Format(KtestsdkeikhkeytLogFileWithTitle, &title);
        }
    else
        {
        logFileName.Copy(KtestsdkeikhkeytLogFile);
        }

    iLog = CStifLogger::NewL( KtestsdkeikhkeytLogPath, 
                          logFileName,
                          CStifLogger::ETxt,
                          CStifLogger::EFile,
                          EFalse );
    iOffset = CCoeEnv::Static()->AddResourceFileL(_L("C:\\resource\\testsdkeikhkeyt.rsc"));

    SendTestClassVersion();
    }

// -----------------------------------------------------------------------------
// CTestSDKEIKHKEYT::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTestSDKEIKHKEYT* CTestSDKEIKHKEYT::NewL( 
    CTestModuleIf& aTestModuleIf )
    {
    CTestSDKEIKHKEYT* self = new (ELeave) CTestSDKEIKHKEYT( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );

    return self;

    }

CTestSDKEIKHKEYT::~CTestSDKEIKHKEYT()
    { 

    Delete();

    delete iLog; 

    CCoeEnv::Static()->DeleteResourceFile( iOffset );
    }

//-----------------------------------------------------------------------------
// CTestSDKEIKHKEYT::SendTestClassVersion
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
void CTestSDKEIKHKEYT::SendTestClassVersion()
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
    CTestModuleIf& aTestModuleIf )
    {

    return ( CScriptBase* ) CTestSDKEIKHKEYT::NewL( aTestModuleIf );

    }

/*
 * End of File
 */
