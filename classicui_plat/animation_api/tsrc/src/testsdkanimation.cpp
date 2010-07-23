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
* Description:  Test AknBitmapAnimation.h
*
*/



// INCLUDE FILES
#include <stiftestinterface.h>
#include <settingserverclient.h>
#include <coeaui.h>

#include "testsdkanimation.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKAnimation::CTestSDKAnimation
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
CTestSDKAnimation::CTestSDKAnimation( CTestModuleIf& aTestModuleIf ):
    CScriptBase( aTestModuleIf )
    {
    }

// -----------------------------------------------------------------------------
// CTestSDKAnimation::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
void CTestSDKAnimation::ConstructL()
    {
    //Read logger settings to check whether test case name is to be
    //appended to log file name.
    RSettingServer settingServer;
    CleanupClosePushL( settingServer );
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
    CleanupStack::PopAndDestroy( &settingServer );

    TFileName logFileName;
    
    if(loggerSettings.iAddTestCaseTitle)
        {
        TName title;
        TestModuleIf().GetTestCaseTitleL(title);
        logFileName.Format(KtestsdkanimationLogFileWithTitle, &title);
        }
    else
        {
        logFileName.Copy(KtestsdkanimationLogFile);
        }

    iLog = CStifLogger::NewL( KtestsdkanimationLogPath, 
                          logFileName,
                          CStifLogger::ETxt,
                          CStifLogger::EFile,
                          EFalse );
    _LIT( KFile, "C:\\resource\\testsdkanimation.rsc" );
    iOffset = CCoeEnv::Static()->AddResourceFileL( KFile );
    SendTestClassVersion();
    }

// -----------------------------------------------------------------------------
// CTestSDKAnimation::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
CTestSDKAnimation* CTestSDKAnimation::NewL( CTestModuleIf& aTestModuleIf )
    {
    CTestSDKAnimation* self = new( ELeave ) CTestSDKAnimation( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );

    return self;

    }

// Destructor
CTestSDKAnimation::~CTestSDKAnimation()
    { 

    // Delete resources allocated from test methods
    Delete();

    // Delete logger
    delete iLog; 

    CCoeEnv::Static()->DeleteResourceFile( iOffset );
    }

//-----------------------------------------------------------------------------
// CTestSDKAnimation::SendTestClassVersion
// Method used to send version of test class
//-----------------------------------------------------------------------------
void CTestSDKAnimation::SendTestClassVersion()
    {
    TVersion moduleVersion;
    moduleVersion.iMajor = TEST_CLASS_VERSION_MAJOR;
    moduleVersion.iMinor = TEST_CLASS_VERSION_MINOR;
    moduleVersion.iBuild = TEST_CLASS_VERSION_BUILD;
    
    _LIT( KName, "testsdka.dll" );
    TFileName moduleName( KName );

    TBool newVersionOfMethod = ETrue;
    TestModuleIf().SendTestModuleVersion(moduleVersion, moduleName, newVersionOfMethod);
    }

// ========================== OTHER EXPORTED FUNCTIONS =========================

// -----------------------------------------------------------------------------
// LibEntryL is a polymorphic Dll entry point.
// Returns: CScriptBase: New CScriptBase derived object
// -----------------------------------------------------------------------------
EXPORT_C CScriptBase* LibEntryL( 
    CTestModuleIf& aTestModuleIf ) // Backpointer to STIF Test Framework
    {

    return ( CScriptBase* ) CTestSDKAnimation::NewL( aTestModuleIf );

    }
//  End of File
