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
* Description:  Functions implement
*
*/



// INCLUDE FILES
#include <stiftestinterface.h>
#include <settingserverclient.h>
#include <e32property.h>

#include "testdomstylusactivepopup.h"

// CONSTANTS
_LIT( KModuleName, "testdomstylusactivepopup.dll" );
_LIT( KResourceFile, "c:\\resource\\testdomstylusactivepopup.rsc" );

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomStylusActivePopup::CTestDomStylusActivePopup
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CTestDomStylusActivePopup::CTestDomStylusActivePopup( CTestModuleIf& aTestModuleIf ):
    CScriptBase( aTestModuleIf )
    {
    }

// -----------------------------------------------------------------------------
// CTestDomStylusActivePopup::~CTestDomStylusActivePopup
// Destructor.
// -----------------------------------------------------------------------------
//
CTestDomStylusActivePopup::~CTestDomStylusActivePopup()
    {
    // Delete logger
    delete iLog;
    CCoeEnv::Static()->DeleteResourceFile( iOffset );
    }

// -----------------------------------------------------------------------------
// CTestDomStylusActivePopup::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTestDomStylusActivePopup::ConstructL()
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
        logFileName.Format( KtestdomstylusactivepopupLogFileWithTitle, &title );
        }
    else
        {
        logFileName.Copy( KtestdomstylusactivepopupLogFile );
        }

    iLog = CStifLogger::NewL( KtestdomstylusactivepopupLogPath, 
                          logFileName,
                          CStifLogger::ETxt,
                          CStifLogger::EFile,
                          EFalse );
    TRect rect = CEikonEnv::Static()->AppUiFactory()->ClientRect();
    iContainer = CTestStyleActivePopUpContainer::NewL( rect );
    iOffset = CCoeEnv::Static()->AddResourceFileL( KResourceFile );
    SendTestClassVersion();
    }

// -----------------------------------------------------------------------------
// CTestDomStylusActivePopup::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTestDomStylusActivePopup* CTestDomStylusActivePopup::NewL( CTestModuleIf& aTestModuleIf )
    {
    CTestDomStylusActivePopup* self = new( ELeave ) CTestDomStylusActivePopup( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );

    return self;

    }

//-----------------------------------------------------------------------------
// CTestDomStylusActivePopup::SendTestClassVersion
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
void CTestDomStylusActivePopup::SendTestClassVersion()
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
    return ( CScriptBase* ) CTestDomStylusActivePopup::NewL( aTestModuleIf );
    }
//  End of File
