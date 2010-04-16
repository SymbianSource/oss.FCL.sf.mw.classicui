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
* Description:  Description
*
*/



// INCLUDE FILES
#include <stiftestinterface.h>
#include <settingserverclient.h>
#include <e32property.h>
#include <coemain.h>

#include "testsdktouchpane.h"
#include "testsdktpview.h"
#include "testsdktpcontainer.h"

// CONSTANTS
_LIT( KModuleName, "testsdktouchpane.dll" );

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctestsdktouchpane::Ctestsdktouchpane
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CTestSDKTouchPane::CTestSDKTouchPane( CTestModuleIf& aTestModuleIf ):
    CScriptBase( aTestModuleIf )
    {
    }

// -----------------------------------------------------------------------------
// Ctestsdktouchpane::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTestSDKTouchPane::ConstructL()
    {
    iView = CTestSDKTPView::NewL();
    iContainer = new( ELeave ) CTestSDKTPContainer();

    iContainer->SetMopParent( iView );
    iContainer->ConstructL( iView->ClientRect() );
    CCoeEnv::Static()->AppUi()->AddToStackL( iContainer );
    iContainer->MakeVisible( ETrue );
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
        logFileName.Format( KtestsdktouchpaneLogFileWithTitle, &title );
        }
    else
        {
        logFileName.Copy( KtestsdktouchpaneLogFile );
        }

    iLog = CStifLogger::NewL( KtestsdktouchpaneLogPath, 
                          logFileName,
                          CStifLogger::ETxt,
                          CStifLogger::EFile,
                          EFalse );
    
    SendTestClassVersion();
    
    iOffset = CCoeEnv::Static()->AddResourceFileL( _L( "C:\\resource\\testsdktouchpane.rsc" ) );
    }

// -----------------------------------------------------------------------------
// Ctestsdktouchpane::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTestSDKTouchPane* CTestSDKTouchPane::NewL( CTestModuleIf& aTestModuleIf )
    {
    CTestSDKTouchPane* self = new( ELeave ) CTestSDKTouchPane( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );

    return self;

    }

// Destructor
CTestSDKTouchPane::~CTestSDKTouchPane()
    { 

    // Delete resources allocated from test methods
    Delete();
    CCoeEnv::Static()->AppUi()->RemoveFromStack( iContainer );
    delete iContainer;
    delete iView;
    // Delete logger
    delete iLog; 

    CCoeEnv::Static()->DeleteResourceFile( iOffset );
    }

//-----------------------------------------------------------------------------
// Ctestsdktouchpane::SendTestClassVersion
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
void CTestSDKTouchPane::SendTestClassVersion()
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
    return ( CScriptBase* ) CTestSDKTouchPane::NewL( aTestModuleIf );
    }
//  End of File
