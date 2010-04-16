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
* Description:  Implement of functions
*
*/



// INCLUDE FILES
#include <stiftestinterface.h>
#include <settingserverclient.h>
#include <e32property.h>
#include <bautils.h>

#include "testsdkuifwutil.h"

// CONSTANTS
_LIT( KModuleName, "testsdkuifwutil.dll" );
_LIT( KResourceFile, "\\resource\\testsdkuifwutil.rsc" );

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::CTestSDKUiFwUtil
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CTestSDKUiFwUtil::CTestSDKUiFwUtil( CTestModuleIf& aTestModuleIf ):
    CScriptBase( aTestModuleIf )
    {
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::~CTestSDKUiFwUtil
// Destructor.
// -----------------------------------------------------------------------------
//
CTestSDKUiFwUtil::~CTestSDKUiFwUtil()
    {
    // Delete logger
    delete iLog;
    if ( iUiFwUtilView )
        {
        delete iUiFwUtilView;
        }

    CCoeEnv::Static()->DeleteResourceFile( iOffset );
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTestSDKUiFwUtil::ConstructL()
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
        logFileName.Format( KtestsdkuifwutilLogFileWithTitle, &title );
        }
    else
        {
        logFileName.Copy( KtestsdkuifwutilLogFile );
        }

    iLog = CStifLogger::NewL( KtestsdkuifwutilLogPath, 
                          logFileName,
                          CStifLogger::ETxt,
                          CStifLogger::EFile,
                          EFalse );
    
    SendTestClassVersion();
    
    iEnv = CEikonEnv::Static();
    
    iFont = iEnv->NormalFont();

    TFileName resourceFile;
    resourceFile.Append( KResourceFile );
    BaflUtils::NearestLanguageFile( iEnv->FsSession(), resourceFile );
    iOffset = iEnv->AddResourceFileL( resourceFile );
    iUiFwUtilView = CTestUiFwUtilView::NewL();
    iContainer = iUiFwUtilView->GetContainer();
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTestSDKUiFwUtil* CTestSDKUiFwUtil::NewL( CTestModuleIf& aTestModuleIf )
    {
    CTestSDKUiFwUtil* self = new( ELeave ) CTestSDKUiFwUtil( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );

    return self;

    }

//-----------------------------------------------------------------------------
// CTestSDKUiFwUtil::SendTestClassVersion
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
void CTestSDKUiFwUtil::SendTestClassVersion()
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
    return ( CScriptBase* ) CTestSDKUiFwUtil::NewL( aTestModuleIf );
    }

//  End of File
